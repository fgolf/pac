#ifndef FAKERATESCANCHAIN_H
#define FAKERATESCANCHAIN_H

// C++
#include <string>

// ROOT
class TChain;

 // a test analysis
int FakeRateScanChainTestAnalysis(long event);

// Peform an analysis on a chain.
template <typename Function>
int FakeRateScanChain
(
    TChain* chain, 
    Function analyze = FakeRateScanChainTestAnalysis, 
    long num_events = -1, 
    bool is_data = true,
    bool verbose = false
 );

#include "FakeRateScanChain.impl.h"

#endif // FAKERATESCANCHAIN_H
