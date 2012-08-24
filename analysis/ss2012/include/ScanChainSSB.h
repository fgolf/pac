#ifndef SCANCHAINSSB_H
#define SCANCHAINSSB_H

// C++
#include <string>

// ROOT
class TChain;

 // a test analysis
int ScanChainSSBTestAnalysis(long event);

// Peform an analysis on a chain.
template <typename Function>
int ScanChainSSB
(
    TChain* chain, 
    Function analyze = ScanChainSSBTestAnalysis, 
    long num_events = -1, 
    bool do_duplicate_removal = true,
    bool verbose = false
 );

#include "ScanChainSSB.impl.h"

#endif // SCANCHAINSSB_H
