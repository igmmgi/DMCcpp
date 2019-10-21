#include <chrono>
#include <vector>
#include <utility>
#include <map>
#include <boost/random.hpp>
#include "runDMC.h"

void runDMCsim(
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
        for (auto i = 0u; i < mu_vec.size(); i++) {
            mu_vec[i] = sign * simulation["eq4"][i] * ((p.aaShape - 1) / (i+1) - 1 / p.tau);
        }

        // variable drift rate?
        std::vector<double> dr(p.nTrl, p.mu);
        if (p.varDR) {
            variable_drift_rate(p, dr, dr_mean);
        }

        // variable starting point?
        std::vector<double> sp(p.nTrl);
        if (p.varSP) {
            variable_starting_point(p, sp, sp_mean);
        }

        // run simulation and store rts for correct/incorrect trials
        if (p.fullData) {
            run_simulation(p, activation_sum, trial_matrix, mu_vec, sp, dr, rts, errs);
        } else {
            run_simulation(p, mu_vec, sp, dr, rts, errs);
        }

        simulation["activation_" + comp] = activation_sum;
        simulation["rts_" + comp] = rts;
        trials["trials_" + comp] = trial_matrix;

        calculate_summary(rts, errs, p.nTrl, resSummary, comp);
        calculate_percentile(p.stepDelta, rts, resDelta, comp);
        calculate_caf(rts, errs, p.stepCAF, resCAF, comp);

}

void variable_drift_rate(Prms &p, std::vector<double> &dr, std::vector<double> &dr_mean) {
    typedef boost::mt19937 RNGType;
    const uint32_t s = p.setSeed ? 1 : std::time(nullptr);
    RNGType rng(s);

    boost::random::beta_distribution<> bdDR(p.drShape, p.drShape); // beta distribution with defined shape a, shape b
    boost::variate_generator<RNGType, boost::random::beta_distribution<> > betaDistDR(rng, bdDR);

    for(auto &i : dr) i = betaDistDR() * (p.drLimHigh - p.drLimLow) + p.drLimLow;
    dr_mean.push_back(accumulate(dr.begin(), dr.end(), 0.0) / dr.size());
}

void variable_starting_point(Prms &p, std::vector<double> &sp, std::vector<double> &sp_mean) {
    typedef boost::mt19937 RNGType;
    const uint32_t s = p.setSeed ? 1 : std::time(nullptr);
    RNGType rng(s);

    boost::random::beta_distribution<> bdSP(p.spShape, p.spShape); // beta distribution with defined shape a, shape b
    boost::variate_generator<RNGType, boost::random::beta_distribution<> > betaDistSP(rng, bdSP);

    for(auto &i : sp) i = betaDistSP() * (p.spLimHigh - p.spLimLow) + p.spLimLow;
    sp_mean.push_back(accumulate(sp.begin(), sp.end(), 0.0) / sp.size());
}


void run_simulation(
        Prms &p,
        std::vector<double> &mu_vec,
        std::vector<double> &sp,
        std::vector<double> &dr,
        std::vector<double> &rts,
        std::vector<double> &errs
        ) {

    typedef boost::mt19937 RNGType;
    const uint32_t s = p.setSeed ? 1 : std::time(nullptr);
    RNGType rng(s);

    boost::normal_distribution<> snd(0.0, 1.0);  // standard normal distribution
    boost::normal_distribution<> nd_mean_sd(p.resMean, p.resSD);   // normal distribution with given mean/SD
    boost::variate_generator<RNGType, boost::normal_distribution<> > randDist(rng, snd);
    boost::variate_generator<RNGType, boost::normal_distribution<> > resDist(rng, nd_mean_sd);

    double activation_trial = 0;
    for (auto trl = 0u; trl < p.nTrl; trl++) {
        activation_trial = sp[0];
        for (auto i = 0u; i < p.tmax; i++) {
            activation_trial += mu_vec[i] + dr[trl] + (p.sigma * randDist());
            if (fabs(activation_trial) > p.bnds) {
                (activation_trial > p.bnds ? rts : errs).push_back(i + resDist() + 1); // zero index
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
        std::vector<double> &errs
        ) {

     typedef boost::mt19937 RNGType;
     const uint32_t s = p.setSeed ? 1 : std::time(nullptr);
     RNGType rng(s);

     boost::normal_distribution<> snd(0.0, 1.0);  // standard normal distributoin
     boost::normal_distribution<> nd_mean_sd(p.resMean, p.resSD);   // normal distribution with given mean/SD
     boost::variate_generator<RNGType, boost::normal_distribution<> > randDist(rng, snd);
     boost::variate_generator<RNGType, boost::normal_distribution<> > resDist(rng, nd_mean_sd);

    std::vector<double> activation_trial(p.tmax);
    bool criterion;
     for (auto trl = 0u; trl < p.nTrl; trl++) {
         criterion = false;
         activation_trial[0] = mu_vec[0] + sp[trl] + dr[trl] + (p.sigma * randDist());
         activation_sum[0] += activation_trial[0];
         for (auto i = 1u; i < activation_trial.size(); i++) {
             activation_trial[i] = activation_trial[i - 1] + mu_vec[i] + dr[trl] + (p.sigma * randDist());
             if (!criterion && fabs(activation_trial[i]) > p.bnds) {
                 (activation_trial[i] > p.bnds ? rts : errs).push_back(i + resDist() + 1); // zero index
                 criterion = true;
             }
             if (trl < p.nTrlData) trial_matrix[trl][i] = activation_trial[i];
             activation_sum[i] += activation_trial[i];
         }
     }
    for (auto i = 0u; i < p.tmax; i++) {
        activation_sum[i] /= p.nTrl;
    }
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
    res[0] = accumulate(rts.begin(), rts.end(), 0.0)/rts.size();
    res[1] = std::sqrt(std::inner_product(rts.begin(), rts.end(), rts.begin(), 0.0) / rts.size() - res[0] * res[0]);
    res[2] = (errs.size() / static_cast<float>(nTrl)) * 100;
    res[3] = accumulate(errs.begin(), errs.end(), 0.0)/errs.size();
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
    for (auto step = stepDelta; step < 100; step+= stepDelta) {

        pct_idx = step/100.0 * (rts.size()+1);
        pct_idx_int = int(pct_idx);
        pct_idx_dec = pct_idx - int(pct_idx);

        resDelta["delta_pct_" + condition].push_back(rts[pct_idx_int + ((rts[pct_idx_int+1]-rts[pct_idx_int])*pct_idx_dec)]);

    }

}


void calculate_delta(std::map<std::string, std::vector<double> > &resDelta) {
     for (auto i = 0u; i < resDelta["delta_pct_comp"].size(); i++){
         resDelta["delta_pct_mean"].push_back((resDelta["delta_pct_comp"][i]   + resDelta["delta_pct_incomp"][i])/2);
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

    std::vector<bool> is_err(rts.size(), false);
    std::vector<bool> tmp(errs.size(), true);

    is_err.insert(is_err.end(), tmp.begin(), tmp.end());
    rts.insert(rts.end(), errs.begin(), errs.end());

    std::vector<std::pair<double, bool> > comb;
    for (auto i = 0u; i < rts.size(); i++) {
        comb.emplace_back(std::make_pair(rts[i], is_err[i]));
    }

    std::sort(comb.begin(), comb.end());
    std::vector<int> bins(comb.size());
    int nBins = 100/stepCAF;
    for (auto i = 0u; i < comb.size(); i++){
        bins[i] = int(nBins * (i)/comb.size());
    }

    std::vector<long int> countErr(nBins, 0);
    std::vector<long int> countCor(nBins, 0);
    for (auto i = 0u; i < bins.size(); i++) {
        (comb[i].second == 0) ? countCor[bins[i]]++ : countErr[bins[i]]++;
    }

    for (auto i = 0u; i < countCor.size(); i++){
        resCAF["caf_" + condition].push_back(1 - (countErr[i]/float(countCor[i]+countErr[i])));
    }

}

