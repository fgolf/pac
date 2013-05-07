#include "TChain.h"
#include "TFile.h"
#include "rt/MiscTools.h"
#include <string>
#include <iostream>

using namespace std;

namespace rt
{
    // merged a TChain
    void MergedTChain(const std::string& input_path, const std::string& merged_file, const std::string& tree_name, const std::string& option)
    {
        cout << Form("merging %s to %s", input_path.c_str(), merged_file.c_str()) << endl;
        rt::mkdir(rt::dirname(merged_file), /*force=*/true);
        TTree::SetMaxTreeSize(5368709120); // 5GB
        TChain* chain = rt::CreateTChainFromCommaSeperatedList(input_path, tree_name);
        chain->Merge(merged_file.c_str(), option.c_str());
        chain->Merge(merged_file.c_str(), option.c_str());
        cout << "complete." << endl; 
        delete chain;
    }

} // namespace rt
