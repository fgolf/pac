#ifndef RT_COMPARECONTENTSOFTTREES_H
#define RT_COMPARECONTENTSOFTTREES_H

#include <string>
#include "TTree.h"

namespace rt
{
    // compare the contents of two trees 
    void CompareContentOfTTrees
    (
        TTree* const tree1, 
        TTree* const tree2, 
        const std::string& output_folder = "", 
        const std::string& tree1_label = "tree1", 
        const std::string& tree2_label = "tree2", 
        long num_entries = 1000000000,
        const std::string& suffix = "png"
    );

} // namespace rt

#endif // RT_COMPARECONTENTSOFTTREES_H
