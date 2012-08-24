#ifndef AT_SCANCHAIN_H
#define AT_SCANCHAIN_H

// C++
#include <string>

// ROOT
class TChain;

namespace at
{
     // a test analysis
    int ScanChainTestAnalysis(long event);

    // Peform an analysis on a chain.
    template <typename Function>
    int ScanChainCMS2
    (
        TChain* chain, 
        Function analyze, 
        long num_events = -1, 
        const std::string& goodrun_file_name = "",
        bool fast = true,
        bool verbose = false
     );

} // namespace at

#include "ScanChain.impl.h"

#endif // AT_SCANCHAIN_H
