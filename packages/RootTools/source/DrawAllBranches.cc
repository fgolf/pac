#include "rt/DrawAllBranches.h"

// c++ includes
#include <iostream>
#include "TBranch.h"
#include "TBranchElement.h"

// RootTools
#include "rt/MiscTools.h"
#include "rt/TH1Container.h"

using namespace std;

struct BranchInfo
{
    BranchInfo(TBranch* b) : name(b->GetName()), classname(b->GetTitle()) {}
    BranchInfo(TBranchElement* b) : name(b->GetName()), classname(b->GetClassName()) {}
    std::string name;
    std::string classname;
};

bool operator == (const BranchInfo& b1, const BranchInfo& b2) 
{
    return (b1.name == b2.name) && (b1.classname == b2.classname);
}

struct CompareBranchInfo
{
    bool operator () (const BranchInfo& b1, const BranchInfo& b2) const 
	{
		return b1 == b2;
	}
};

namespace rt
{
    // compare the contents of two trees 
    void DrawAllBranches 
    (
        TTree& tree, 
        const std::string& selection,
        const std::string& output_folder,
        long num_entries,
        const std::string& suffix
    )
    {
        TObjArray* array = tree.GetListOfBranches();

        vector<BranchInfo> tree_branches;
        for (int i = 0; i < array->GetEntries(); i++)
        {
            TBranch* b = dynamic_cast<TBranch*>(tree.GetListOfBranches()->At(i));
            if (TBranchElement* be = dynamic_cast<TBranchElement*>(b))
            {
                tree_branches.push_back(BranchInfo(be));
            }
            else
            {
                tree_branches.push_back(BranchInfo(b));
            }
            //cout << tree1_branches.back().name << "\t" << tree1_branches.back().classname << endl;
        }     

        // plot histograms of all the branches 
		rt::TH1Container hc;
        for (size_t i = 0; i != tree_branches.size(); i++)
        {
            const BranchInfo& branch = tree_branches.at(i); 

            // hist names
            string h1_name = string("h1_") + branch.name;

            // fill hist 1
            string h1_draw = Form("%s>>h1_%s", branch.name.c_str(), branch.name.c_str());

            if (string_contains(branch.classname, "ROOT::Math::LorentzVector"))
            {
                h1_draw = Form("%s.mass()>>h1_%s", branch.name.c_str(), branch.name.c_str());
            }

            tree.Draw(h1_draw.c_str(), selection.c_str(), "goff", num_entries);
            hc.Add(dynamic_cast<TH1F*>(gDirectory->Get(h1_name.c_str())));
        }

        // print output 
        if (!output_folder.empty())
        {
            hc.Print(output_folder, suffix);
        }

        // done
        return;
    }

} // namespace rt
