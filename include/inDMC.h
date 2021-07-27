#ifndef CPP_INPUTS_HPP
#define CPP_INPUTS_HPP
#include <vector>
#include <string>


struct Prms {
    double amp = 20;
    double tau = 30;
    double aaShape = 2;
    double drc = 0.5;
    double sigma = 4;
    double bnds = 75;
    int resDist = 1;
    double resMean = 300;
    double resSD = 30;
    unsigned int rtMax = 5000;
    unsigned long nTrl = 100000;
    unsigned int tmax = 1000;
    bool varSP = false;
    int spDist = 1;
    double spShape = 3;
    double spLimLow = -75;
    double spLimHigh = 75;
    bool varDR = false;
    int drDist = 1;
    double drShape = 3;
    double drLimLow = 0.1;
    double drLimHigh = 0.7;
    bool fullData = false;
    unsigned long nTrlData = 5;
    int nDelta = 19;
    std::vector<double> vDelta;
    std::vector<double> pDelta;
    int tDelta = 1;
    int nCAF = 5;
    std::vector<double> vCAF;
    bool printInputArgs = true;
    bool printResults = true;
    bool setSeed = false; // if true, seed set to seed value
    unsigned long seedValue = 1; 

};

void show_help();
void print_input_args(Prms &p);
void process_input_args(
        int argc,
        char** argv,
        Prms &p,
        bool &argProblem
);

std::vector<double> linspace(int start, int end, int n);

#endif //CPP_INPUTS_HPP
