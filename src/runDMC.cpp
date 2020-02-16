#include <chrono>
#include <vector>
#include <utility>
#include <map>
#include <boost/random.hpp>
#include <thread>
#include "runDMC.h"
#include <random>

void runDMCsim(
        Prms &p,
        std::map<std::string, std::vector<double> > &resSummary,
        std::map<std::string, std::vector<double> > &resDelta,
        std::map<std::string, std::vector<double> > &resCAF,
        std::map<std::string, std::vector<double> > &simulation,
        std::map<std::string, std::vector<std::vector<double> > > &trials
) {

    // equation 4
    std::vector<double> eq4(p.tmax);
    for (unsigned int i = 1; i <= p.tmax; i++)
        eq4[i - 1] = (p.amp * exp(-(i / p.tau))) * pow(((exp(1) * i / (p.aaShape - 1) / p.tau)), (p.aaShape - 1));
    simulation["eq4"] = eq4;

    // variable drift-rate and starting point means
    std::vector<double> dr_mean(2);
    std::vector<double> sp_mean(2);

    // run comp and incomp simulation on different thread
    std::vector<std::thread> threads(2);
    std::vector<std::string> compatibility{"comp", "incomp"};
    std::vector<int> sign{1, -1};
    for (int i = 0; i < 2; i++) {
        threads.emplace_back(runDMCsim_t,
                             std::ref(p),
                             std::ref(resSummary),
                             std::ref(resDelta),
                             std::ref(resCAF),
                             std::ref(simulation),
                             std::ref(trials),
                             std::ref(compatibility[i]),
                             std::ref(sign[i]),
                             std::ref(dr_mean),
                             std::ref(sp_mean));
    }
    for (auto &thread : threads) {
        if (thread.joinable()) thread.join();
    }

    // finalize results requiring both comp/incomp
    calculate_delta(resDelta);

    // just keep average drift rate/starting point across both comp/incomp trials
    simulation["dr_sp"].push_back(!p.varDR ? p.mu : (dr_mean[0] + dr_mean[1]) / 2);
    simulation["dr_sp"].push_back(!p.varSP ? 0 : (sp_mean[0] + sp_mean[1]) / 2);
}


void runDMCsim_t(
        Prms &p,
        std::map<std::string, std::vector<double> > &resSummary,
        std::map<std::string, std::vector<double> > &resDelta,
        std::map<std::string, std::vector<double> > &resCAF,
        std::map<std::string, std::vector<double> > &simulation,
        std::map<std::string, std::vector<std::vector<double> > > &trials,
        const std::string& comp,
        int sign,
        std::vector<double> dr_mean,
        std::vector<double> sp_mean
) {

    std::vector<double> rts;
    std::vector<double> errs;
    std::vector<double> activation_sum(p.tmax);
    std::vector<std::vector<double>> trial_matrix(p.nTrlData, std::vector<double>(p.tmax));  // needed if plotting individual trials

    std::vector<double> mu_vec(p.tmax);
    for (auto i = 0u; i < mu_vec.size(); i++)
        mu_vec[i] = sign * simulation["eq4"][i] * ((p.aaShape - 1) / (i + 1) - 1 / p.tau);

    // variable drift rate?
    std::vector<double> dr(p.nTrl, p.mu);
    if (p.varDR) variable_drift_rate(p, dr, dr_mean, sign);

    // variable starting point?
    std::vector<double> sp(p.nTrl);
    if (p.varSP) variable_starting_point(p, sp, sp_mean, sign);

    // run simulation and store rts for correct/incorrect trials
    if (p.fullData)
        run_simulation(p, activation_sum, trial_matrix, mu_vec, sp, dr, rts, errs, sign);
    else
        run_simulation(p, mu_vec, sp, dr, rts, errs, sign);

    simulation["activation_" + comp] = activation_sum;
    simulation["rts_" + comp] = rts;
    simulation["errs_" + comp] = errs;
    trials["trials_" + comp] = trial_matrix;

    calculate_summary(rts, errs, p.nTrl, resSummary, comp);
    calculate_percentile(p.stepDelta, rts, resDelta, comp);
    calculate_caf(rts, errs, p.stepCAF, resCAF, comp);

}

void variable_drift_rate(Prms &p, std::vector<double> &dr, std::vector<double> &dr_mean, int sign) {

    const uint32_t s = p.setSeed ? 1 : std::time(nullptr); 

    boost::random::mt19937_64 rng(s + sign);
    boost::random::beta_distribution<double> bdDR(p.drShape, p.drShape);

    for (auto &i : dr) i = bdDR(rng) * (p.drLimHigh - p.drLimLow) + p.drLimLow;
    dr_mean.push_back(accumulate(dr.begin(), dr.end(), 0.0) / dr.size());
}

void variable_starting_point(Prms &p, std::vector<double> &sp, std::vector<double> &sp_mean, int sign) {

    const uint32_t s = p.setSeed ? 1 : std::time(nullptr); 

    boost::random::mt19937_64 rng(s + sign);
    boost::random::beta_distribution<double> bdSP(p.spShape, p.spShape);

    for (auto &i : sp) i = bdSP(rng) * (p.spLimHigh - p.spLimLow) + p.spLimLow;
    sp_mean.push_back(accumulate(sp.begin(), sp.end(), 0.0) / sp.size());
}


void run_simulation(
        Prms &p,
        std::vector<double> &mu_vec,
        std::vector<double> &sp,
        std::vector<double> &dr,
        std::vector<double> &rts,
        std::vector<double> &errs,
        int sign
) {

    const uint32_t s = p.setSeed ? 1 : std::time(nullptr); 

    boost::random::mt19937_64 rng(s + sign);
    boost::random::normal_distribution<double> snd(0.0, 1.0);
    boost::random::normal_distribution<double> nd_mean_sd(p.resMean, p.resSD);

    double activation_trial;
    for (auto trl = 0u; trl < p.nTrl; trl++) {
        activation_trial = sp[trl];
        for (auto i = 0u; i < p.tmax; i++) {
            activation_trial += (mu_vec[i] + dr[trl] + (p.sigma * snd(rng)));
            if (fabs(activation_trial) > p.bnds) {
                (activation_trial > p.bnds ? rts : errs).push_back((i + nd_mean_sd(rng) + 1)); // zero index
                break;
            }
        }
    }
}

void run_simulation(
        Prms &p,
        std::vector<double> &activation_sum,
        std::vector<std::vector<double>> &trial_matrix,
        std::vector<double> &mu_vec,
        std::vector<double> &sp,
        std::vector<double> &dr,
        std::vector<double> &rts,
        std::vector<double> &errs,
        int sign
) {

    const uint32_t s = p.setSeed ? 1 : std::time(nullptr); 

    boost::random::mt19937_64 rng(s + sign);
    boost::random::normal_distribution<double> snd(0.0, 1.0);
    boost::random::normal_distribution<double> nd_mean_sd(p.resMean, p.resSD);

    std::vector<double> activation_trial(p.tmax);
    bool criterion;
    for (auto trl = 0u; trl < p.nTrl; trl++) {
        criterion = false;
        activation_trial[0] = mu_vec[0] + sp[trl] + dr[trl] + (p.sigma * snd(rng));
        activation_sum[0] += activation_trial[0];
        for (auto i = 1u; i < activation_trial.size(); i++) {
            activation_trial[i] = activation_trial[i - 1] + mu_vec[i] + dr[trl] + (p.sigma * snd(rng));
            if (!criterion && fabs(activation_trial[i]) > p.bnds) {
                (activation_trial[i] > p.bnds ? rts : errs).push_back(i + nd_mean_sd(rng) + 1); // zero index
                criterion = true;
            }
            if (trl < p.nTrlData) trial_matrix[trl][i] = activation_trial[i];
            activation_sum[i] += activation_trial[i];
        }
    }
    for (auto i = 0u; i < p.tmax; i++)
        activation_sum[i] /= p.nTrl;
}


void calculate_summary(
        std::vector<double> &rts,
        std::vector<double> &errs,
        unsigned long nTrl,
        std::map<std::string, std::vector<double> > &resSummary,
        const std::string& condition
) {

    // rtCor, sdRtCor, perErr, rtErr, sdRtErr
    std::vector<double> res(5);
    res[0] = accumulate(rts.begin(), rts.end(), 0.0) / rts.size();
    res[1] = std::sqrt(std::inner_product(rts.begin(), rts.end(), rts.begin(), 0.0) / rts.size() - res[0] * res[0]);
    res[2] = (errs.size() / static_cast<float>(nTrl)) * 100;
    res[3] = accumulate(errs.begin(), errs.end(), 0.0) / errs.size();
    res[4] = std::sqrt(std::inner_product(errs.begin(), errs.end(), errs.begin(), 0.0) / errs.size() - res[3] * res[3]);

    resSummary["resSum_" + condition] = res;

}


void calculate_percentile(
        int stepDelta,
        std::vector<double> &rts,
        std::map<std::string, std::vector<double> > &resDelta,
        const std::string& condition
) {

    std::sort(rts.begin(), rts.end());

    float pct_idx;
    int pct_idx_int;
    float pct_idx_dec;
    for (auto step = stepDelta; step < 100; step += stepDelta) {

        pct_idx     = (step / 100.0) * (rts.size()); 
        pct_idx_int = int(pct_idx);
        pct_idx_dec = pct_idx - pct_idx_int; 

        resDelta["delta_pct_" + condition].push_back(
                rts[pct_idx_int] + ((rts[pct_idx_int + 1] - rts[pct_idx_int]) * pct_idx_dec));

    }

}

void calculate_delta(std::map<std::string, std::vector<double> > &resDelta) {
    for (auto i = 0u; i < resDelta["delta_pct_comp"].size(); i++) {
        resDelta["delta_pct_mean"].push_back((resDelta["delta_pct_comp"][i]   + resDelta["delta_pct_incomp"][i]) / 2);
        resDelta["delta_pct_delta"].push_back(resDelta["delta_pct_incomp"][i] - resDelta["delta_pct_comp"][i]);
    }
}

void calculate_caf(
        std::vector<double> &rts,
        std::vector<double> &errs,
        int stepCAF,
        std::map<std::string, std::vector<double> > &resCAF,
        const std::string& condition
) {

    std::vector<std::pair<double, bool> > comb;
    comb.reserve(rts.size() + errs.size());
    for (double & rt : rts)
        comb.emplace_back(std::make_pair(rt, false));
    for (double & err : errs)
        comb.emplace_back(std::make_pair(err, true));

    std::sort(comb.begin(), comb.end());
    std::vector<int> bins(comb.size());
    int nBins = 100 / stepCAF;
    for (auto i = 0u; i < comb.size(); i++)
        bins[i] = int(nBins * (i) / comb.size());

    std::vector<long int> countErr(nBins, 0);
    std::vector<long int> countCor(nBins, 0);
    for (auto i = 0u; i < bins.size(); i++)
        (comb[i].second == 0) ? countCor[bins[i]]++ : countErr[bins[i]]++;

    for (auto i = 0u; i < countCor.size(); i++)
        resCAF["caf_" + condition].push_back(1 - (countErr[i] / float(countCor[i] + countErr[i])));

}

