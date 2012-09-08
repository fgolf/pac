#ifndef AT_SKIMCHAIN_H
#define AT_SKIMCHAIN_H

// C++
#include <string>

// ROOT
class TChain;

namespace at
{
     // a test analysis
    int SkimChainTestSelection(long event);

    // Peform an analysis on a chain.
    template <typename Function>
    int SkimChainCMS2
    (
        TChain* chain, 
	    const std::string& output_file_name,
	    const std::string& goodrun_file_name = "",
        Function selected = SkimChainTestSelection, 
        long num_events = -1, 
        bool do_duplicate_removal = true,
        bool verbose = false
    );

} // namespace at

#include "SkimChain.impl.h"

#endif // AT_SKIMCHAIN_H
