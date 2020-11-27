#include <vector>
#include <map>
#include <boost/random.hpp>
#include <thread>
#include <mutex>
#include "runDMC.h"

std::mutex m;

void run_dmc_sim(
        Prms &p,
        std::map<std::string, std::vector<double>> &resSum,
        std::map<std::string, std::vector<double>> &sim,
        std::map<std::string, std::vector<std::vector<double>>> &trials) {

    // values for delta/CAF
    if (!p.pDelta.empty()) {
        p.vDelta = p.pDelta;  // take specific values
        p.vDelta.insert(p.vDelta.begin(), 0);
        p.vDelta.push_back(100);
    } else {  // equally spaced range of values
        p.vDelta = linspace(0, 100, p.nDelta + 2);
    }
    p.vCAF = linspace(0, 100, p.nCAF + 1);

    // equation 4
    std::vector<double> eq4(p.tmax);
    for (unsigned int i = 1; i <= p.tmax; i++)
        eq4[i - 1] = (p.amp * exp(-(i / p.tau))) * pow(((exp(1) * i / (p.aaShape - 1) / p.tau)), (p.aaShape - 1));
    sim["eq4"] = eq4;

    // run comp and incomp
    std::vector<std::thread> threads(2);
    std::vector<std::string> compatibility{"comp", "incomp"};
    std::vector<int> sign{1, -1};
    for (int i = 0; i < 2; i++) {
        threads.emplace_back(run_dmc_sim_ci,
                             std::ref(p),
                             std::ref(resSum),
                             std::ref(sim),
                             std::ref(trials),
                             std::ref(compatibility[i]),
                             std::ref(sign[i]));
    }

    for (auto &thread : threads)
        if (thread.joinable()) thread.join();

    calculate_delta(resSum);  // finalize results requiring both comp/incomp

}

void run_dmc_sim_ci(
        Prms &p,
        std::map<std::string, std::vector<double>> &resSum,
        std::map<std::string, std::vector<double>> &sim,
        std::map<std::string, std::vector<std::vector<double>>> &trials,
        const std::string &comp,
        int sign) {

    std::vector<double> rts;
    std::vector<double> errs;
    std::vector<double> slows;
    std::vector<double> activation_sum(p.tmax);
    std::vector<std::vector<double>> trl_mat(p.nTrlData, std::vector<double>(p.tmax));  // needed if plotting individual trials

    std::vector<double> u_vec(p.tmax);
    for (auto i = 0u; i < u_vec.size(); i++)
        u_vec[i] = sign * sim["eq4"][i] * ((p.aaShape - 1) / (i + 1) - 1 / p.tau);

    // variable drift rate/starting point?
    std::vector<double> dr(p.nTrl, p.drc);
    if (p.varDR) variable_drift_rate(p, dr, sign);
    std::vector<double> sp(p.nTrl);
    if (p.varSP) variable_starting_point(p, sp, sign);

    // run simulation and store rts for correct/incorrect trials
    if (p.fullData) {
        run_simulation(p, activation_sum, trl_mat, u_vec, sp, dr, rts, errs, slows, sign);
        trials[comp] = trl_mat;
    } else {
        run_simulation(p, u_vec, sp, dr, rts, errs, slows, sign);
    }

    m.lock();
    sim["activation_" + comp] = activation_sum;
    sim["rts_" + comp] = rts;
    sim["errs_" + comp] = errs;
    sim["slows_" + comp] = slows;

    // results summary
    resSum["resSum_" + comp] = calculate_summary(rts, errs, slows, p.nTrl);
    resSum["delta_pct_" + comp] = calculate_percentile(p.vDelta, rts);
    resSum["caf_" + comp] = calculate_caf(rts, errs, p.nCAF);
    m.unlock();

}

void variable_drift_rate(Prms &p, std::vector<double> &dr, int sign) {

    const uint32_t s = p.setSeed ? 1 : std::time(nullptr);
    boost::random::mt19937_64 rng(s + sign);
    boost::random::beta_distribution<double> bdDR(p.drShape, p.drShape);

    for (auto &i : dr) i = bdDR(rng) * (p.drLimHigh - p.drLimLow) + p.drLimLow;

}

void variable_starting_point(Prms &p, std::vector<double> &sp, int sign) {

    const uint32_t s = p.setSeed ? 1 : std::time(nullptr);
    boost::random::mt19937_64 rng(s + sign);
    boost::random::beta_distribution<double> bdSP(p.spShape, p.spShape);

    for (auto &i : sp) i = bdSP(rng) * (p.spLimHigh - p.spLimLow) + p.spLimLow;

}

void run_simulation(
        Prms &p,
        std::vector<double> &u_vec,
        std::vector<double> &sp,
        std::vector<double> &dr,
        std::vector<double> &rts,
        std::vector<double> &errs,
        std::vector<double> &slows,
        int sign) {

    const uint32_t s = p.setSeed ? 1 : std::time(nullptr);
    boost::random::mt19937_64 rng(s + sign);
    boost::random::normal_distribution<double> snd(0.0, 1.0);
    boost::random::normal_distribution<double> nd_mean_sd(p.resMean, p.resSD);

    double activation_trial;
    double value;
    for (auto trl = 0u; trl < p.nTrl; trl++) {
        activation_trial = sp[trl];
        for (auto i = 0u; i < p.tmax; i++) {
            activation_trial += (u_vec[i] + dr[trl] + (p.sigma * snd(rng)));
            if (activation_trial > p.bnds) {
                value = i + nd_mean_sd(rng) + 1;
                (value < p.rtMax ? rts : slows).push_back(value);
                break;
            } else if (activation_trial < -p.bnds) {
                value = i + nd_mean_sd(rng) + 1;
                (value < p.rtMax ? errs : slows).push_back(value);
                break;
            }
        }
    }

    // if (p.varSP) {
    //     double meanSP = accumulate(sp.begin(), sp.end(), 0.0) / sp.size();
    //     double sdSP = std::sqrt( std::inner_product(sp.begin(), sp.end(), sp.begin(), 0.0) / sp.size() - meanSP * meanSP);
    //     std::cout << "Mean/SD SP: " << meanSP << "/" << sdSP << std::endl << std::endl;
    // }

    // if (p.varDR) {
    //     double meanDR = accumulate(dr.begin(), dr.end(), 0.0) / dr.size();
    //     double sdDR = std::sqrt( std::inner_product(dr.begin(), dr.end(), dr.begin(), 0.0) / dr.size() - meanDR * meanDR);
    //     std::cout << "Mean/SD DR: " << meanDR << "/" << sdDR << std::endl << std::endl;
    // }

}

void run_simulation(
        Prms &p,
        std::vector<double> &activation_sum,
        std::vector<std::vector<double>> &trial_matrix,
        std::vector<double> &u_vec,
        std::vector<double> &sp,
        std::vector<double> &dr,
        std::vector<double> &rts,
        std::vector<double> &errs,
        std::vector<double> &slows,
        int sign) {

    const uint32_t s = p.setSeed ? 1 : std::time(nullptr);
    boost::random::mt19937_64 rng(s + sign);
    boost::random::normal_distribution<double> snd(0.0, 1.0);
    boost::random::normal_distribution<double> nd_mean_sd(p.resMean, p.resSD);

    double activation_trial;
    bool criterion;
    double value;
    for (auto trl = 0u; trl < p.nTrl; trl++) {
        criterion = false;
        activation_trial = sp[trl];
        for (auto i = 0u; i < activation_sum.size(); i++) {
            activation_trial += u_vec[i] + dr[trl] + (p.sigma * snd(rng));
            if (!criterion && activation_trial > p.bnds) {
                value = i + nd_mean_sd(rng) + 1;
                (value < p.rtMax ? rts : slows).push_back(value);
                criterion = true;
            } else if (!criterion && activation_trial < -p.bnds) {
                value = i + nd_mean_sd(rng) + 1;
                (value < p.rtMax ? errs : slows).push_back(value);
                criterion = true;
            }
            if (trl < p.nTrlData) trial_matrix[trl][i] = activation_trial;
            activation_sum[i] += activation_trial;
        }
    }
    for (auto i = 0u; i < p.tmax; i++)
        activation_sum[i] /= static_cast<double>(p.nTrl);
}


std::vector<double> calculate_summary(
        std::vector<double> &rts,
        std::vector<double> &errs,
        std::vector<double> &slows,
        unsigned long nTrl) {

    // rtCor, sdRtCor, perErr, rtErr, sdRtErr
    std::vector<double> res(6);
    if (rts.size() > 0) {
        res[0] = accumulate(rts.begin(), rts.end(), 0.0) / rts.size();
        res[1] = std::sqrt(std::inner_product(rts.begin(), rts.end(), rts.begin(), 0.0) / rts.size() - res[0] * res[0]);
    }
    res[2] = (errs.size() / static_cast<double>(nTrl)) * 100;
    if (errs.size() > 0) {
        res[3] = accumulate(errs.begin(), errs.end(), 0.0) / errs.size();
        res[4] = std::sqrt(std::inner_product(errs.begin(), errs.end(), errs.begin(), 0.0) / errs.size() - res[3] * res[3]);
    }
    res[5] = (slows.size() / static_cast<double>(nTrl)) * 100;

    return res;

}


std::vector<double> calculate_percentile(
        std::vector<double> vDelta,
        std::vector<double> &rts) {

    int nDelta = vDelta.size() - 2;
    std::vector<double> res(nDelta, 0);
    if (rts.size() != 0) {

        std::sort(rts.begin(), rts.end());

        double pct_idx;
        int pct_idx_int;
        double pct_idx_dec;

        for (int i = 0; i < nDelta; i++) {
            pct_idx = (vDelta[i] / 100.0) * (rts.size() - 1);
            pct_idx_int = int(pct_idx);
            pct_idx_dec = pct_idx - static_cast<double>(pct_idx_int);
            res[i] = rts[pct_idx_int] + ((rts[pct_idx_int + 1] - rts[pct_idx_int]) * pct_idx_dec);
        }

    }

    return res;

}

void calculate_delta(std::map<std::string, std::vector<double> > &resDelta) {
    for (auto i = 0u; i < resDelta["delta_pct_comp"].size(); i++) {
        resDelta["delta_pct_mean"].push_back((resDelta["delta_pct_comp"][i] + resDelta["delta_pct_incomp"][i]) / 2);
        resDelta["delta_pct_delta"].push_back(resDelta["delta_pct_incomp"][i] - resDelta["delta_pct_comp"][i]);
    }
}

std::vector<double> calculate_caf(
        std::vector<double> &rts,
        std::vector<double> &errs,
        int nCAF) {

    std::vector<double> res(nCAF, 0);

    std::vector<std::pair<double, bool> > comb;
    comb.reserve(rts.size() + errs.size());

    if (comb.size() != 0) {

        for (double &rt : rts) comb.emplace_back(std::make_pair(rt, false));
        for (double &err : errs) comb.emplace_back(std::make_pair(err, true));

        std::sort(comb.begin(), comb.end());
        std::vector<int> bins(comb.size());
        for (auto i = 0u; i < comb.size(); i++) bins[i] = int(nCAF * (i) / comb.size());

        std::vector<long int> countErr(nCAF, 0);
        std::vector<long int> countCor(nCAF, 0);
        for (auto i = 0u; i < bins.size(); i++) (comb[i].second == 0) ? countCor[bins[i]]++ : countErr[bins[i]]++;
        for (auto i = 0u; i < countCor.size(); i++) res[i] = 1 - (countErr[i] / float(countCor[i] + countErr[i]));

    }

    return res;

}

std::vector<double> linspace(int start, int end, int n) {
    double step = (end - start) / double(n-1);
    std::vector<double> out(n);
    double val = start;
    for (int i = 0; i < n; i++) {
        out[i] = val;
        val += step;
    }
    return out;
}
