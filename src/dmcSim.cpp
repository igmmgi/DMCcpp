#include <map>
#include <vector>
#include <string>
#include "inDMC.h"
#include "outDMC.h"
#include "runDMC.h"

int main(const int argc, char *argv[]) {

    Prms p;
    bool argProb = false;
    process_input_args(argc, argv, p, argProb);

    if (argProb) return 0;
    if (p.printInputArgs) print_input_args(p);

    std::map<std::string, std::vector<double>> rsum;
    std::map<std::string, std::vector<double>> rsim;
    std::map<std::string, std::vector<std::vector<double>>> trials;

    run_dmc_sim(p, rsum, rsim, trials);

    if (p.printResults) print_results(p, rsum);

    return 0;

}
