#include "inDMC.h"
#include <cstring>
#include <getopt.h>
#include <iomanip>
#include <iostream>

void show_help() {
  std::cout
      << "DMC model simulation\n"
         "Ulrich, R., Schröter, H., Leuthold, H., & Birngruber, T. (2015).\n"
         "Automatic and controlled stimulus processing in conflict tasks: "
         "Superimposed\n"
         "diffusion processes and delta functions. Cognitive Psychology, 78, "
         "148-174.\n"
         "Code adapted from Appendix C. Basic Matlab Code\n\n"
         "Inputs:\n"
         "amp: amplitude of automatic activation\n"
         "tau: time to peak of automatic activation\n"
         "aaShape: shape parameter of automatic activation\n"
         "drc: drift rate of controlled processes\n"
         "bnds: +- response barrier\n"
         "resDist: distribution of the non-decisional component (1 = normal "
         "vs. 2 = uniform)\n"
         "resMean: mean of non-decisional component\n"
         "resSD: standard deviation of non-decisional component \n"
         "rtMax: limit on simulated RT (decision + non-decisional component)\n"
         "nTrl: number of trials to simulate\n"
         "tmax: the number of timepoints per trial\n"
         "spDist: distribution of the starting point (0 = constant, 1 = beta "
         "vs. 2 = uniform)\n"
         "spShape: shape parameter of starting point distribution\n"
         "spLimLow: lower limit of starting point distribution\n"
         "spLimHigh: higher limit of starting point distribution\n"
         "spBias: starting point bias\n"
         "drDist: distribution of the drift rate (0 = constant, 1 = beta vs. 2 "
         "= uniform)\n"
         "drLim: limit range of distribution of drift rate\n"
         "drShape: shape parameter of drift rate\n"
         "drLimLow: lower limit of drift rate distribution\n"
         "drLimHigh: higher limit of drift rate point distribution\n"
         "fullData: option to return all data required for plots when used "
         "within Rcpp\n"
         "nTrlData: option to plot n trials when used within Rcpp\n"
         "nDelta: number of bins for rt distribution analysis\n"
         "pDelta: alternative to nDelta, giving specific percentile values "
         "(enter as --pDelta 25,50,75)\n"
         "tDelta: type of delta calculate (1 = direct percentile, 2 = "
         "percentile bin bounds averaging)\n"
         "nCAF: number of bins for conditional accuracy function analysis\n"
         "printInputArgs: 0/1 print input arguments to console\n"
         "printResults: 0/1 print results summary to console\n\n"
         "Examples:\n"
         "./dmcSim            // Results from Figure 3\n"
         "./dmcSim --tau 150  // Results from Figure 4\n"
         "./dmcSim --tau 90   // Results from Figure 5\n"
         "./dmcSim --drDist 1 // Results from Figure 6\n"
         "./dmcSim --spDist 1 // Results from Figure 7"
      << std::endl;
}

void process_input_args(const int argc, char **argv, Prms &p, bool &argProblem) {

  const struct option long_opts[] = {
      {"amp", 1, nullptr, 0},
      {"tau", 1, nullptr, 1},
      {"aaShape", 1, nullptr, 2},
      {"drc", 1, nullptr, 3},
      {"bnds", 1, nullptr, 4},
      {"resDist", 1, nullptr, 5},
      {"resMean", 1, nullptr, 6},
      {"resSD", 1, nullptr, 7},
      {"rtMax", 1, nullptr, 8},
      {"nTrl", 1, nullptr, 9},
      {"tmax", 1, nullptr, 10},
      {"spDist", 1, nullptr, 11},
      {"spShape", 1, nullptr, 12},
      {"spLimLow", 1, nullptr, 13},
      {"spLimHigh", 1, nullptr, 14},
      {"spBias", 1, nullptr, 15},
      {"drDist", 1, nullptr, 16},
      {"drLimLow", 1, nullptr, 17},
      {"drLimHigh", 1, nullptr, 18},
      {"drShape", 1, nullptr, 19},
      {"fullData", 1, nullptr, 20}, // when used from within Rcpp
      {"nTrlData", 1, nullptr, 21}, // when used from within Rcpp to plot
                                    // individual trials (lower left plot)
      {"nDelta", 1, nullptr, 22},
      {"pDelta", 1, nullptr, 23},
      {"tDelta", 1, nullptr, 24},
      {"nCAF", 1, nullptr, 25},
      {"printInputArgs", 1, nullptr, 26},
      {"printResults", 1, nullptr, 27},
      {"setSeed", 1, nullptr, 28},
      {"seedValue", 1, nullptr, 29},
      {"help", 0, nullptr, 30},
      {nullptr, 0, nullptr, 0},
  };

  //int option;
  int idxOption = 0;
  try {
    int option;
    while ((option = getopt_long(argc, argv, "", long_opts, &idxOption)) !=
           -1) {
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
        p.resDist = std::stod(optarg);
        break;
      case 6:
        p.resMean = std::stod(optarg);
        break;
      case 7:
        p.resSD = std::stod(optarg);
        break;
      case 8:
        p.rtMax = std::stod(optarg);
        break;
      case 9:
        p.nTrl = std::stoul(optarg);
        break;
      case 10:
        p.tmax = static_cast<unsigned int>(std::stoi(optarg));
        break;
      case 11:
        p.spDist = std::stod(optarg);
        break;
      case 12:
        p.spShape = std::stod(optarg);
        break;
      case 13:
        p.spLimLow = std::stod(optarg);
        break;
      case 14:
        p.spLimHigh = std::stod(optarg);
        break;
      case 15:
        p.spBias = std::stod(optarg);
        break;
      case 16:
        p.drDist = std::stod(optarg);
        break;
      case 17:
        p.drLimLow = std::stod(optarg);
        break;
      case 18:
        p.drLimHigh = std::stod(optarg);
        break;
      case 19:
        p.drShape = std::stod(optarg);
        break;
      case 20:
        p.fullData = static_cast<bool>(std::stoi(optarg));
        break;
      case 21:
        p.nTrlData = static_cast<unsigned long>(std::stoi(optarg));
        break;
      case 22:
        p.nDelta = std::stoi(optarg);
        break;
      case 23: {
        const char *token = strtok(optarg, ",");
        while (token != nullptr) {
          const int pval = std::stoi(token);
          if (pval >= 0 && pval <= 100) {
            p.pDelta.push_back(pval);
          } else {
            std::cout << "Requested percentile problem: 0 <= " << pval
                      << " <= 100 "
                      << "\n";
          }
          token = strtok(nullptr, ",");
        }
        p.nDelta = p.pDelta.size();
        break;
      }
      case 24:
        p.tDelta = std::stoi(optarg);
        break;
      case 25:
        p.nCAF = std::stoi(optarg);
        break;
      case 26:
        p.printInputArgs = static_cast<bool>(std::stoi(optarg));
        break;
      case 27:
        p.printResults = static_cast<bool>(std::stoi(optarg));
        break;
      case 28:
        p.setSeed = static_cast<bool>(std::stoi(optarg));
        break;
      case 29:
        p.seedValue = static_cast<unsigned long>(std::stoi(optarg));
        break;
      case 30:
        show_help();
        argProblem = true;
        break;
      default:
        std::cout << "Input option not recognized!:" << option << "\n";
        argProblem = true;
      }
    }
  } catch (...) {
    std::cout << "Input option not recognized:" << long_opts[idxOption].name
              << ":" << optarg << std::endl;
    argProblem = true;
  }

  // values for delta/CAF
  if (!p.pDelta.empty()) {
    p.vDelta = p.pDelta; // take specific values
    p.vDelta.insert(p.vDelta.begin(), 0);
    p.vDelta.push_back(100);
  } else { // equally spaced range of values
    p.vDelta = linspace(0, 100, p.nDelta + 2 - (p.tDelta - 1));
  }
  p.vCAF = linspace(0, 100, p.nCAF + 1);
}

void print_input_args(const Prms &p) {
  std::cout << "\nDMC Parameters:"
            << "\n";
  std::cout << "amp: " << p.amp << std::setw(12);
  std::cout << "tau: " << p.tau << std::setw(12);
  std::cout << "aaShape: " << p.aaShape << std::setw(12);
  std::cout << "drc: " << p.drc << std::setw(12);
  std::cout << "bnds: " << p.bnds << std::setw(12);
  std::cout << "resMean: " << p.resMean << std::setw(12);
  std::cout << "resSD: " << p.resSD << std::setw(12);
  if (p.spDist != 0)
    std::cout << "spShape: " << p.spShape << std::setw(12);
  if (p.spBias != 0)
    std::cout << "spBias: " << p.spBias << std::setw(12);
  if (p.drDist != 0)
    std::cout << "drShape: " << p.drShape << std::setw(12);
  std::cout << "\n\n";
}

std::vector<double> linspace(const int start, const int end, const int n) {
  const double step = (end - start) / static_cast<double>(n - 1);
  std::vector<double> out(n);
  double val = start;
  for (int i = 0; i < n; i++) {
    out[i] = val;
    val += step;
  }
  return out;
}
