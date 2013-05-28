#ifndef SKIMCHAINOS_H
#define SKIMCHAINOS_H

// C++
#include <string>

// ROOT
class TChain;

// a test analysis
bool SkimChainOSTestSelection(long event);

// Peform an analysis on a chain.
template <typename Function>
int SkimChainOS
(
    TChain* chain, 
    const std::string& output_file_name,
    const std::string& goodrun_file_name = "",
    Function selected = SkimChainOSTestSelection, 
    long num_events = -1, 
    bool do_duplicate_removal = true,
    bool verbose = false
    );

#include "SkimChainOS.impl.h"

#endif // SKIMCHAINOS_H
