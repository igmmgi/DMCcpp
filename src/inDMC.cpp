#include <iostream>
#include <iomanip>
#include <getopt.h>
#include <string.h>
#include "inDMC.h"

void show_help() {
    std::cout << "DMC model simulation\n"
                 "Ulrich, R., Schröter, H., Leuthold, H., & Birngruber, T. (2015).\n"
                 "Automatic and controlled stimulus processing in conflict tasks: Superimposed\n"
                 "diffusion processes and delta functions. Cognitive Psychology, 78, 148-174.\n"
                 "Code adapted from Appendix C. Basic Matlab Code\n\n"
                 "Inputs:\n"
                 "amp: amplitude of automatic activation\n"
                 "tau: time to peak of automatic activation\n"
                 "aaShape: shape parameter of automatic activation\n"
                 "drc: drift rate of controlled processes\n"
                 "bnds: +- response barrier\n"
                 "resMean: mean of non-decisional component\n"
                 "resSD: standard deviation of non-decisional component\n"
                 "rtMax: limit on simulated RT (decision + non-decisional component)\n"
                 "nTrl: number of trials to simulate\n"
                 "tmax: the number of timepoints per trial\n"
                 "varSP: variable start point\n"
                 "spShape: shape parameter of starting point distribution\n"
                 "spLimLow: lower limit of starting point distribution\n"
                 "spLimHigh: higher limit of starting point distribution\n"
                 "varDR: variable drift rate\n"
                 "drLim: limit range of distribution of drift rate\n"
                 "drShape: shape parameter of drift rate\n"
                 "drLimLow: lower limit of drift rate distribution\n"
                 "drLimHigh: higher limit of drift rate point distribution\n"
                 "fullData: option to return all data required for plots when used within Rcpp\n"
                 "nTrlData: option to plot n trials when used within Rcpp\n"
                 "nDelta: number of bins for rt distribution analysis\n"
                 "pDelta: alternative to nDelta, giving specific percentile values (enter as --pDelta 25,50,75)\n"
                 "nCAF: number of bins for conditional accuracy function analysis\n"
                 "printInputArgs: 0/1 print input arguments to console\n"
                 "printResults: 0/1 print results summary to console\n\n"
                 "Examples:\n"
                 "./dmcSim           // Results from Figure 3\n"
                 "./dmcSim --tau 150 // Results from Figure 4\n"
                 "./dmcSim --tau 90  // Results from Figure 5\n"
                 "./dmcSim --varDR 1 // Results from Figure 6\n"
                 "./dmcSim --varSP 1 // Results from Figure 7" << std::endl;
}

void process_input_args(int argc, char **argv, Prms &p, bool &argProblem) {

    const struct option long_opts[] = {
            {"amp",            1, nullptr, 0},
            {"tau",            1, nullptr, 1},
            {"aaShape",        1, nullptr, 2},
            {"drc",            1, nullptr, 3},
            {"bnds",           1, nullptr, 4},
            {"resMean",        1, nullptr, 5},
            {"resSD",          1, nullptr, 6},
            {"rtMax",          1, nullptr, 7},
            {"nTrl",           1, nullptr, 8},
            {"tmax",           1, nullptr, 9},
            {"varSP",          1, nullptr, 10},
            {"spShape",        1, nullptr, 11},
            {"spLimLow",       1, nullptr, 12},
            {"spLimHigh",      1, nullptr, 13},
            {"varDR",          1, nullptr, 14},
            {"drLimLow",       1, nullptr, 15},
            {"drLimHigh",      1, nullptr, 16},
            {"drShape",        1, nullptr, 17},
            {"fullData",       1, nullptr, 18},  // when used from within Rcpp
            {"nTrlData",       1, nullptr, 19},  // when used from within Rcpp to plot individual trials (lower left plot)
            {"nDelta",         1, nullptr, 20},
            {"pDelta",         1, nullptr, 21},
            {"nCAF",           1, nullptr, 22},
            {"printInputArgs", 1, nullptr, 23},
            {"printResults",   1, nullptr, 24},
            {"setSeed",        1, nullptr, 25},
            {"help",           0, nullptr, 26},
            {nullptr,          0, nullptr, 0},
    };

    int option;
    int idxOption = 0;
    try {
        while ((option = getopt_long(argc, argv, "", long_opts, &idxOption)) != -1) {
            switch (option) {
                case 0:
                    p.amp = std::stod(optarg);
                    break;
                case 1:
                    p.tau = std::stod(optarg);
                    break;
                case 2:
                    p.aaShape = std::stod(optarg);
                    break;
                case 3:
                    p.drc = std::stod(optarg);
                    break;
                case 4:
                    p.bnds = std::stoi(optarg);
                    break;
                case 5:
                    p.resMean = std::stod(optarg);
                    break;
                case 6:
                    p.resSD = std::stod(optarg);
                    break;
                case 7:
                    p.rtMax = std::stod(optarg);
                    break;
                case 8:
                    p.nTrl = std::stoul(optarg);
                    break;
                case 9:
                    p.tmax = static_cast<unsigned int>(std::stoi(optarg));
                    break;
                case 10:
                    p.varSP = static_cast<bool>(std::stoi(optarg));
                    break;
                case 11:
                    p.spShape = std::stod(optarg);
                    break;
                case 12:
                    p.spLimLow = std::stod(optarg);
                    break;
                case 13:
                    p.spLimHigh = std::stod(optarg);
                    break;
                case 14:
                    p.varDR = static_cast<bool>(std::stoi(optarg));
                    break;
                case 15:
                    p.drLimLow = std::stod(optarg);
                    break;
                case 16:
                    p.drLimHigh = std::stod(optarg);
                    break;
                case 17:
                    p.drShape = std::stod(optarg);
                    break;
                case 18:
                    p.fullData = static_cast<bool>(std::stoi(optarg));
                    break;
                case 19:
                    p.nTrlData = static_cast<unsigned long>(std::stoi(optarg));
                    break;
                case 20:
                    p.nDelta = std::stoi(optarg);
                    break;
                case 21:
                    {
                        char* token = strtok(optarg, ",");
                        int pval;
                        while (token != NULL) {
                            pval = std::stoi(token);
                            if (pval >= 0 && pval <= 100) {
                                p.pDelta.push_back(pval);
                            } else {
                                std::cout << "Requested percentile problem: 0 <= " << pval << " <= 100 " << "\n";
                            }
                            token = strtok(NULL, ",");
                        }
                        p.nDelta = p.pDelta.size();
                        break;
                    }
                case 22:
                    p.nCAF = std::stoi(optarg);
                    break;
                case 23:
                    p.printInputArgs = static_cast<bool>(std::stoi(optarg));
                    break;
                case 24:
                    p.printResults = static_cast<bool>(std::stoi(optarg));
                    break;
                case 25:
                    p.setSeed = static_cast<bool>(std::stoi(optarg));
                    break;
                case 26:
                    show_help();
                    argProblem = true;
                    break;
                default:
                    std::cout << "Input option not recognized!:" << option << "\n";
                    argProblem = true;
            }
        }
    } catch (...) {
        std::cout << "Input option not recognized:" << long_opts[idxOption].name << ":" << optarg << std::endl;
        argProblem = true;
    }
}

void print_input_args(Prms &p) {
    std::cout << "\nDMC Parameters:" << "\n";
    std::cout << "amp: " << p.amp << std::setw(12);
    std::cout << "tau: " << p.tau << std::setw(12);
    std::cout << "aaShape: " << p.aaShape << std::setw(12);
    std::cout << "drc: " << p.drc << std::setw(12);
    std::cout << "bnds: " << p.bnds << std::setw(12);
    std::cout << "resMean: " << p.resMean << std::setw(12);
    std::cout << "resSD: " << p.resSD << std::setw(12);
    if (p.varSP) std::cout << "spShape: " << p.spShape << std::setw(12);
    if (p.varDR) std::cout << "drShape: " << p.drShape << std::setw(12);
    std::cout << "\n\n";
}
