#include <map>
#include <vector>
#include "inDMC.h"
#include "outDMC.h"
#include "runDMC.h"
#include <thread>
#include <boost/random.hpp>

int main(int argc, char *argv[]) {

    Prms p;
    bool argProblem = false;
    processInputArgs(argc, argv, p, argProblem);

    if (argProblem) return 0;
    if (p.printInputArgs) printInputArgs(p);

    std::map<std::string, std::vector<double> > resSummary;
    std::map<std::string, std::vector<double> > resDelta;
    std::map<std::string, std::vector<double> > resCAF;
    std::map<std::string, std::vector<double> > simulation;
    std::map<std::string, std::vector<std::vector<double>> > trials;

    // equation 4
    std::vector<double> eq4(p.tmax);
    for (unsigned int i = 1; i <= p.tmax; i++) {
        eq4[i-1] = (p.amp * exp(-(i / p.tau))) * pow(((exp(1) * i / (p.aaShape - 1) / p.tau)), (p.aaShape - 1));
    }
    simulation["eq4"] = eq4;

    // variable drift-rate and starting point means
    std::vector<double> dr_mean(2);
    std::vector<double> sp_mean(2);

    // run comp and incomp simulation on different thread
    std::vector<std::thread> threads(2);
    std::vector <std::string> compatibility{"comp", "incomp"};
    std::vector <int> sign{1, -1};
    for (int i = 0; i < 2; i++) {
        threads.emplace_back(runDMCsim,
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
    for (auto & thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    // finalize results requiring both comp/incomp
    calculate_delta(resDelta);

    // just keep average drift rate/starting point across both comp/incomp trials
    simulation["dr_sp"].push_back(!p.varDR ? p.mu : (dr_mean[0] + dr_mean[1]) / 2);
    simulation["dr_sp"].push_back(!p.varSP ?    0 : (sp_mean[0] + sp_mean[1]) / 2);

    if (p.printResults) printResults(p, resSummary, resDelta, resCAF);

    return 0;

}
