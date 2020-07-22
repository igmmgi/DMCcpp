#ifndef CPP_INPUTS_HPP
#define CPP_INPUTS_HPP
#include <chrono>
#include <vector>


struct Prms {
    double amp = 20;
    double tau = 30;
    double aaShape = 2;
    double mu = 0.5;
    double sigma = 4;
    double bnds = 75;
    double resMean = 300;
    double resSD = 30;
    unsigned long nTrl = 100000;
    unsigned int tmax = 1000;
    bool varSP = false;
    double spShape = 3;
    double spLimLow = -75;
    double spLimHigh = 75;
    bool varDR = false;
    double drShape = 3;
    double drLimLow = 0.1;
    double drLimHigh = 0.7;
    bool fullData = false;
    unsigned long nTrlData = 5;
    int nDelta = 19;
    std::vector<double> vDelta;
    int nCAF = 5;
    std::vector<double> vCAF;
    bool printInputArgs = true;
    bool printResults = true;
    bool setSeed = false; // if true, use RNGType rng(1) called

};

void show_help();
void print_input_args(Prms &p);
void process_input_args(
        int argc,
        char** argv,
        Prms &p,
        bool &argProblem
);

#endif //CPP_INPUTS_HPP
