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
    template <typename NtupleClass, typename Function>
    int ScanChain
    (
        TChain* chain, 
        Function analyze, 
        NtupleClass& ntuple_class,
        long num_events = -1, 
        const std::string& goodrun_file_name = "",
        bool fast = true,
        bool verbose = false
     );

    // Peform an analysis on a chain.
    // Same as ScanChain except we pass the file name to the analysis object 
    template <typename NtupleClass, typename Function>
    int ScanChainWithFilename
    (
        TChain* chain, 
        Function analyze, 
        NtupleClass& ntuple_class,
        long num_events = -1, 
        const std::string& goodrun_file_name = "",
        bool fast = true,
        bool verbose = false
     );

} // namespace at

#include "ScanChain.impl.h"

#endif // AT_SCANCHAIN_H
