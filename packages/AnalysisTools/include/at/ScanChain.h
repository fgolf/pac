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
        const long num_events = -1, 
        const std::string& goodrun_file_name = "",
        const bool fast = true,
        const bool verbose = false,
        const int evt_run = -1,
        const int evt_lumi = -1,
        const int evt_event = -1,
	const bool remove_duplicate = true
     );

    // Peform an analysis on a chain.
    // Same as ScanChain except we pass the file name to the analysis object 
    template <typename NtupleClass, typename Function>
    int ScanChainWithFilename
    (
        TChain* chain, 
        Function analyze, 
        NtupleClass& ntuple_class,
        const long num_events = -1, 
        const std::string& goodrun_file_name = "",
        const bool fast = true,
        const bool verbose = false,
        const int evt_run = -1,
        const int evt_lumi = -1,
        const int evt_event = -1,
	const bool remove_duplicate = true
     );

} // namespace at

#include "ScanChain.impl.h"

#endif // AT_SCANCHAIN_H
