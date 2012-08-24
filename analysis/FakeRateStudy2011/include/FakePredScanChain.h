#ifndef FAKERATESCANCHAIN_H
#define FAKERATESCANCHAIN_H

// C++
#include <string>

// ROOT
class TChain;

 // a test analysis
int FakePredScanChainTestAnalysis(long event);

// Peform an analysis on a chain.
template <typename Function>
int FakePredScanChain
(
    TChain* chain, 
    Function analyze = FakePredScanChainTestAnalysis, 
    long num_events = -1, 
    bool is_data = true,
    bool verbose = false
 );

#include "FakePredScanChain.impl.h"

#endif // FAKERATESCANCHAIN_H
