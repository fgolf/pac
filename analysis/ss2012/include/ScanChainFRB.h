#ifndef SCANCHAINFRB_H
#define SCANCHAINFRB_H

// C++
#include <string>

// ROOT
class TChain;

 // a test analysis
int ScanChainFRBTestAnalysis(long event);

// Peform an analysis on a chain.
template <typename Function>
int ScanChainFRB
(
    TChain* chain, 
    Function analyze = ScanChainFRBTestAnalysis, 
    long num_events = -1, 
    bool fast = true,
    bool verbose = false
 );

#include "ScanChainFRB.impl.h"

#endif // SCANCHAINFRB_H
