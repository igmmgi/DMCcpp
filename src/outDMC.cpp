#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <cmath>
#include "inDMC.h"

void print_results(
        Prms &p,
        std::map<std::string, std::vector<double> > &resSum) {
   
    std::cout << "Results Summary:" << std::endl;
    std::cout << "\trtCor\tsdRtCor\tperErr\trtErr\tsdRtErr" << std::endl;
    std::cout << "comp\t"
        << std::fixed
        << std::setprecision(0) << resSum["resSum_comp"][0] << "\t"
        << std::setprecision(0) << resSum["resSum_comp"][1] << "\t"
        << std::setprecision(2) << resSum["resSum_comp"][2] << "\t"
        << std::setprecision(0) << resSum["resSum_comp"][3] << "\t"
        << std::setprecision(0) << resSum["resSum_comp"][4] << "\n";
    std::cout << "incomp\t"
        << std::fixed
        << std::setprecision(0) << resSum["resSum_incomp"][0] << "\t"
        << std::setprecision(0) << resSum["resSum_incomp"][1] << "\t"
        << std::setprecision(2) << resSum["resSum_incomp"][2] << "\t"
        << std::setprecision(0) << resSum["resSum_incomp"][3] << "\t"
        << std::setprecision(0) << resSum["resSum_incomp"][4] << "\n";
    std::cout << std::endl;

    // results delta distribution
    std::cout << "Delta Values:\n" << "\t";
    for (auto step = p.stepDelta; step < 100; step += p.stepDelta)
        std::cout << step << "%\t";
    std::cout << std::endl;
    
    std::cout << "comp" << "\t" << std::fixed << std::setprecision(1);
    for (unsigned int i = 0; i < resSum["delta_pct_comp"].size(); i++)
        std::cout << resSum["delta_pct_comp"][i] << "\t";
    std::cout << std::endl;

    std::cout << "incomp" << "\t" << std::fixed << std::setprecision(1);
    for (unsigned int i = 0; i < resSum["delta_pct_incomp"].size(); i++)
        std::cout << resSum["delta_pct_incomp"][i] << "\t";
    std::cout << std::endl;

    std::cout << "mean" << "\t" << std::fixed << std::setprecision(1);  
    for (unsigned int i = 0; i < resSum["delta_pct_mean"].size(); i++)
        std::cout << resSum["delta_pct_mean"][i] << "\t";
    std::cout << std::endl;

    std::cout << "effect" << "\t" << std::fixed << std::setprecision(1); 
    for (unsigned int i = 0; i < resSum["delta_pct_delta"].size(); i++)
        std::cout << std::setw(5) << resSum["delta_pct_delta"][i] << "\t";
    std::cout << std::endl;
    std::cout << std::endl;

    // results caf
    std::cout << "CAF Values:\n" << "\t"; 
    for (auto step = 0; step < 100; step += p.stepCAF)
        std::cout << std::setw(3) << step << "-" << (step + p.stepCAF) << "%\t";
    std::cout << std::endl;

    std::cout << "comp" << "\t" << std::fixed << std::setprecision(3); 
    for (unsigned int i = 0; i < resSum["caf_comp"].size(); i++)
        std::cout << std::setw(7) << resSum["caf_comp"][i] << "\t";
    std::cout << std::endl;
    std::cout << "incomp" << "\t" << std::fixed << std::setprecision(3); 
    for (unsigned int i = 0; i < resSum["caf_incomp"].size(); i++)
        std::cout << std::setw(7) << resSum["caf_incomp"][i] << "\t";
    std::cout << std::endl;

}
