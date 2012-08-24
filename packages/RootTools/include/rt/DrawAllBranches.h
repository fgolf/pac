#ifndef RT_DRAWALLBRANCHES_H
#define RT_DRAWALLBRANCHES_H

#include <string>
#include "TTree.h"

namespace rt
{
    // compare the contents of two trees 
    void DrawAllBranches 
    (
        TTree& tree, 
		const std::string& selection = "", 
        const std::string& output_folder = "", 
        long num_entries = 1000000000,
        const std::string& suffix = "png"
    );

} // namespace rt

#endif // RT_DRAWALLBRANCHES_H
