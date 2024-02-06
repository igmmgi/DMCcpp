#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include "runDMC.h"

void print_results(
        const Prms &p,
        std::map<std::string, std::vector<double> > &rsum) {

    std::cout << "Results Summary:" << "\n";
    std::cout << "\trtCor\tsdRtCor\tperErr\trtErr\tsdRtErr\tperSlow" << "\n";
    std::cout << "comp\t"
              << std::fixed
              << std::setprecision(0) << rsum["comp"][0] << "\t"
              << std::setprecision(0) << rsum["comp"][1] << "\t"
              << std::setprecision(2) << rsum["comp"][2] << "\t"
              << std::setprecision(0) << rsum["comp"][3] << "\t"
              << std::setprecision(0) << rsum["comp"][4] << "\t"
              << std::setprecision(1) << rsum["comp"][5] << "\n";
    std::cout << "incomp\t"
              << std::fixed
              << std::setprecision(0) << rsum["incomp"][0] << "\t"
              << std::setprecision(0) << rsum["incomp"][1] << "\t"
              << std::setprecision(2) << rsum["incomp"][2] << "\t"
              << std::setprecision(0) << rsum["incomp"][3] << "\t"
              << std::setprecision(0) << rsum["incomp"][4] << "\t"
              << std::setprecision(1) << rsum["incomp"][5] << "\n\n";

    // results delta distribution
    for (int ce = 0; ce < 2; ce++) {
        std::string t;
        if (ce == 0) {
            std::cout << "Delta Values (Correct):\n" << "\t";
            t = "correct";
        } else if (ce == 1) {
            std::cout << "Delta Values (Errors):\n" << "\t";
            t = "errors";
        }

        if (p.tDelta == 1) {
            for (int i = 1; i <= p.nDelta; i++)
                std::cout << p.vDelta[i] << "%\t";
            std::cout << "\n";
        } else if (p.tDelta == 2) {
            for (int i = 1; i <= p.nDelta; i++)
                std::cout << "Bin " << i << "\t";
            std::cout << "\n";
        }

        std::cout << "comp" << "\t" << std::fixed << std::setprecision(1);
        for (int i = 0; i < p.nDelta; i++)
            std::cout << rsum["delta_" + t + "_comp"][i] << "\t";
        std::cout << "\n";

        std::cout << "incomp" << "\t" << std::fixed << std::setprecision(1);
        for (int i = 0; i < p.nDelta; i++)
            std::cout << rsum["delta_" + t + "_incomp"][i] << "\t";
        std::cout << "\n";

        std::cout << "mean" << "\t" << std::fixed << std::setprecision(1);
        for (int i = 0; i < p.nDelta; i++)
            std::cout << rsum["delta_" + t + "_mean"][i] << "\t";
        std::cout << "\n";

        std::cout << "effect" << "\t" << std::fixed << std::setprecision(1);
        for (int i = 0; i < p.nDelta; i++)
            std::cout << rsum["delta_" + t + "_delta"][i] << "\t";
        std::cout << "\n\n";

    }

    // results caf
    std::cout << "CAF Values:\n" << "\t";
    for (int i = 0; i < p.nCAF; i++)
        std::cout << static_cast<int>(p.vCAF[i]) << "-" << static_cast<int>(p.vCAF[i+1]) << "%\t";
    std::cout << "\n";

    std::cout << "comp" << "\t" << std::fixed << std::setprecision(3);
    for (int i = 0; i < p.nCAF; i++)
        std::cout << rsum["caf_comp"][i] << "\t";
    std::cout << "\n";
    std::cout << "incomp" << "\t" << std::fixed << std::setprecision(3);
    for (int i = 0; i < p.nCAF; i++)
        std::cout << rsum["caf_incomp"][i] << "\t";
    std::cout << std::endl;

}
