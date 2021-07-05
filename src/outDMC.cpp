#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include "runDMC.h"

void print_results(
        Prms &p,
        std::map<std::string, std::vector<double> > &resSum) {

    std::cout << "Results Summary:" << "\n";
    std::cout << "\trtCor\tsdRtCor\tperErr\trtErr\tsdRtErr\tperSlow" << "\n";
    std::cout << "comp\t"
              << std::fixed
              << std::setprecision(0) << resSum["resSum_comp"][0] << "\t"
              << std::setprecision(0) << resSum["resSum_comp"][1] << "\t"
              << std::setprecision(2) << resSum["resSum_comp"][2] << "\t"
              << std::setprecision(0) << resSum["resSum_comp"][3] << "\t"
              << std::setprecision(0) << resSum["resSum_comp"][4] << "\t"
              << std::setprecision(1) << resSum["resSum_comp"][5] << "\n";
    std::cout << "incomp\t"
              << std::fixed
              << std::setprecision(0) << resSum["resSum_incomp"][0] << "\t"
              << std::setprecision(0) << resSum["resSum_incomp"][1] << "\t"
              << std::setprecision(2) << resSum["resSum_incomp"][2] << "\t"
              << std::setprecision(0) << resSum["resSum_incomp"][3] << "\t"
              << std::setprecision(0) << resSum["resSum_incomp"][4] << "\t"
              << std::setprecision(1) << resSum["resSum_incomp"][5] << "\n\n";

    // results delta distribution
    std::cout << "Delta Values:\n" << "\t";
    for (int i = 1; i <= p.nDelta; i++)
        std::cout << p.vDelta[i] << "%\t";
    std::cout << "\n";

    std::cout << "comp" << "\t" << std::fixed << std::setprecision(1);
    for (int i = 0; i < p.nDelta; i++)
        std::cout << resSum["delta_pct_comp"][i] << "\t";
    std::cout << "\n";

    std::cout << "incomp" << "\t" << std::fixed << std::setprecision(1);
    for (int i = 0; i < p.nDelta; i++)
        std::cout << resSum["delta_pct_incomp"][i] << "\t";
    std::cout << "\n";

    std::cout << "mean" << "\t" << std::fixed << std::setprecision(1);
    for (int i = 0; i < p.nDelta; i++)
        std::cout << resSum["delta_pct_mean"][i] << "\t";
    std::cout << "\n";

    std::cout << "effect" << "\t" << std::fixed << std::setprecision(1);
    //std::setw(5);
    for (int i = 0; i < p.nDelta; i++)
        std::cout << resSum["delta_pct_delta"][i] << "\t";
    std::cout << "\n\n";

    // results caf
    std::cout << "CAF Values:\n" << "\t";
    for (int i = 0; i < p.nCAF; i++)
        std::cout << static_cast<int>(p.vCAF[i]) << "-" << static_cast<int>(p.vCAF[i+1]) << "%\t";
    std::cout << "\n";

    std::cout << "comp" << "\t" << std::fixed << std::setprecision(3);
    for (int i = 0; i < p.nCAF; i++)
        std::cout << resSum["caf_comp"][i] << "\t";
    std::cout << "\n";
    std::cout << "incomp" << "\t" << std::fixed << std::setprecision(3);
    for (int i = 0; i < p.nCAF; i++)
        std::cout << resSum["caf_incomp"][i] << "\t";
    std::cout << std::endl;

}
