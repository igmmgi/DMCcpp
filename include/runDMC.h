#ifndef CPP_RUNDMCSIM_HPP
#define CPP_RUNDMCSIM_HPP

#include "inDMC.h"
#include <boost/random.hpp>
#include <map>

typedef boost::random::mt19937_64 RNG;

void run_dmc_sim(
    Prms &p, std::map<std::string, std::vector<double>> &rsum,
    std::map<std::string, std::vector<double>> &rsim,
    std::map<std::string, std::vector<std::vector<double>>> &trials);

void run_dmc_sim_ci(
    const Prms &p, std::map<std::string, std::vector<double>> &resSum,
    std::map<std::string, std::vector<double>> &sim,
    std::map<std::string, std::vector<std::vector<double>>> &trials,
    const std::string &comp, int sign);

const std::vector<double> automatic_activation(const Prms &p);
const std::vector<double>
time_dependent_drift(const Prms &p, int sign,
                     std::vector<double> &automatic_activation);

std::vector<double> calculate_summary(const std::vector<double> &rts,
                                      const std::vector<double> &errs,
                                      const std::vector<double> &slows,
                                      unsigned long nTrl);

std::vector<double> calculate_percentile(const std::vector<double> &vDelta,
                                         std::vector<double> &rts, int type);

void calculate_delta(std::map<std::string, std::vector<double>> &resDelta);

const std::vector<double> drift_rate(const Prms &p, RNG &rng);
const std::vector<double> starting_point(const Prms &p, RNG &rng);
const std::vector<double> residual_rt(const Prms &p, RNG &rng);

std::vector<double> calculate_caf(const std::vector<double> &rts,
                                  const std::vector<double> &errs, int nCAF);

void run_simulation(const Prms &p, std::vector<double> &activation_sum,
                    std::vector<std::vector<double>> &trial_matrix,
                    const std::vector<double> &u_vec,
                    const std::vector<double> &sp,
                    const std::vector<double> &dr, std::vector<double> &rts,
                    std::vector<double> &errs, std::vector<double> &slows,
                    RNG rng);

void run_simulation(const Prms &p, const std::vector<double> &u_vec,
                    const std::vector<double> &sp,
                    const std::vector<double> &dr, std::vector<double> &rts,
                    std::vector<double> &errs, std::vector<double> &slows,
                    RNG rng);

#endif // CPP_RUNDMCSIM_HPP
