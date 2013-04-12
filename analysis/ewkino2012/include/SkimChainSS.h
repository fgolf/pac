#ifndef SKIMCHAINSSB_H
#define SKIMCHAINSSB_H

// C++
#include <string>

// ROOT
class TChain;

 // a test analysis
bool SkimChainSSBTestSelection(long event);

// Peform an analysis on a chain.
template <typename Function>
int SkimChainSSB
(
    TChain* chain, 
	const std::string& output_file_name,
	const std::string& goodrun_file_name = "",
    Function selected = SkimChainSSBTestSelection, 
    long num_events = -1, 
    bool do_duplicate_removal = true,
    bool verbose = false
 );

#include "SkimChainSSB.impl.h"

#endif // SKIMCHAINSSB_H
