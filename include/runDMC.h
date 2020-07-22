#ifndef CPP_RUNDMCSIM_HPP
#define CPP_RUNDMCSIM_HPP

#include "inDMC.h"

void run_dmc_sim(
        Prms &p,
        std::map<std::string, std::vector<double>> &resSum,
        std::map<std::string, std::vector<double>> &sim,
        std::map<std::string, std::vector<std::vector<double>>> &trials
);

void run_dmc_sim_ci(
        Prms &p,
        std::map<std::string, std::vector<double>> &resSum,
        std::map<std::string, std::vector<double>> &sim,
        std::map<std::string, std::vector<std::vector<double>>> &trials,
        const std::string& comp,
        int sign
);

std::vector<double> calculate_summary(
        std::vector<double> &rts,
        std::vector<double> &errs,
        unsigned long nTrl
);

std::vector<double> calculate_percentile(
        std::vector<double> vDelta,
        std::vector<double> &rts
);

void calculate_delta(
        std::map<std::string,
        std::vector<double>> &resDelta
);

void variable_drift_rate(
        Prms &p,
        std::vector<double> &dr,
        int sign
);

void variable_starting_point(
        Prms &p,
        std::vector<double> &sp,
        int sign
);

std::vector<double> calculate_caf(
        std::vector<double> &rts,
        std::vector<double> &errs,
        int nBins
);

std::vector<double> linspace(int start, int end, int n);

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
);

void run_simulation(
        Prms &p,
        std::vector<double> &mu_vec,
        std::vector<double> &sp,
        std::vector<double> &dr,
        std::vector<double> &rts,
        std::vector<double> &errs,
        int sign
);

#endif //CPP_RUNDMCSIM_HPP
