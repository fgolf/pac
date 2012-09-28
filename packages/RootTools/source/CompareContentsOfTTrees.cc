#include "rt/CompareContentsOfTTrees.h"

// c++ includes
#include <iostream>

// Root includes
#include "TBranch.h"
#include "TBranchElement.h"

// RootTools
#include "rt/TH1Overlay.h"
#include "rt/MiscTools.h"

using namespace std;

namespace rt
{
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
        bool operator () (const BranchInfo& b1, const BranchInfo& b2) const {return b1 == b2;}
    };


    // compare the contents of two trees 
    void CompareContentOfTTrees
    (
        TTree* const tree1, 
        TTree* const tree2, 
        const std::string& output_folder,
        const std::string& tree1_label,
        const std::string& tree2_label,
        const std::string& selection, 
        const std::string& option, 
        long num_entries,
        const std::string& suffix
    )
    {
        TObjArray* array1 = tree1->GetListOfBranches();
        TObjArray* array2 = tree2->GetListOfBranches();

        cout << "rt::CompareContentOfTTrees:" << endl;
        cout << tree1_label << ": " << tree1->GetName() << "\t# entries:  " << tree1->GetEntries() << endl;
        cout << tree1_label << " has " << array1->GetEntries() << " branches" << endl; 
        cout << tree2_label << ": " << tree2->GetName() << "\t# entries:  " << tree2->GetEntries() << endl;
        cout << tree2_label << " has " << array2->GetEntries() << " branches" << endl; 

        vector<BranchInfo> tree1_branches;
        for (int i = 0; i < array1->GetEntries(); i++)
        {
            TBranch* b = dynamic_cast<TBranch*>(tree1->GetListOfBranches()->At(i));
            if (TBranchElement* be = dynamic_cast<TBranchElement*>(b))
            {
                tree1_branches.push_back(BranchInfo(be));
            }
            else
            {
                tree1_branches.push_back(BranchInfo(b));
            }
            //cout << tree1_branches.back().name << "\t" << tree1_branches.back().classname << endl;
        }     
        vector<BranchInfo> tree2_branches;
        for (int i = 0; i < array2->GetEntries(); i++)
        {
            TBranch* b = dynamic_cast<TBranch*>(tree2->GetListOfBranches()->At(i));
            if (TBranchElement* be = dynamic_cast<TBranchElement*>(b))
            {
                tree2_branches.push_back(BranchInfo(be));
            }
            else
            {
                tree2_branches.push_back(BranchInfo(b));
            }
            //cout << tree2_branches.back().name << "\t" << tree2_branches.back().classname << endl;
        }     

        // compare sizes of branches
        if (tree1_branches.size() != tree2_branches.size())
        {
            cout << "rt::CompareContentsOfTTrees WARNING: tree #1 and tree #2 "
                    "do not have the same number of branches" << endl;
        }

        // intersection of branches
        vector<BranchInfo> tree_branches_intersection;
        std::set_intersection
        (
            tree1_branches.begin(), tree1_branches.end(), 
            tree2_branches.begin(), tree2_branches.end(), 
            std::back_inserter(tree_branches_intersection),
            CompareBranchInfo()
        );

        cout << "branch set intersection:" << endl;
        cout << "intersection has " << tree_branches_intersection.size() << " branches" << endl; 
        for (size_t i = 0; i != tree_branches_intersection.size(); i++)
        {
            const BranchInfo& branch = tree_branches_intersection.at(i); 
            cout << "\t" << branch.name << "  \t" << branch.classname << endl;
        }

        // branches in tree1 not in intersection of tree1 and tree2 
        vector<BranchInfo> tree1_branches_diff;
        if (tree1_branches.size() > tree_branches_intersection.size())
        {
            std::set_difference
            (
                 tree1_branches.begin(), tree1_branches.end(), 
                 tree_branches_intersection.begin(), tree_branches_intersection.end(), 
                 std::back_inserter(tree1_branches_diff),
                 CompareBranchInfo()
            );

            cout << tree1_label << " has " << tree1_branches.size() << " branches" << endl; 
            cout << tree1_label << " - set intersection(tree 1, tree 2):" << endl;
            for (size_t i = 0; i != tree1_branches_diff.size(); i++)
            {
                const BranchInfo& branch = tree1_branches_diff.at(i); 
                cout << "\t" << branch.name << "  \t" << branch.classname << endl;
            }
        }

        // branches in tree2 not in intersection of tree1 and tree2 
        vector<BranchInfo> tree2_branches_diff;
        if (tree2_branches.size() > tree_branches_intersection.size())
        {
            std::set_difference
            (
                 tree2_branches.begin(), tree2_branches.end(), 
                 tree_branches_intersection.begin(), tree_branches_intersection.end(), 
                 std::back_inserter(tree2_branches_diff),
                 CompareBranchInfo()
            );

            cout << tree2_label << " has " << tree2_branches.size() << " branches" << endl; 
            cout << tree2_label << " - set intersection(tree 1, tree 2):" << endl;
            for (size_t i = 0; i != tree2_branches_diff.size(); i++)
            {
                const BranchInfo& branch = tree2_branches_diff.at(i); 
                cout << "\t" << branch.name << "  \t" << branch.classname << endl;
            }
        }

        // plot histograms of all the branches 
        std::map<std::string, TH1Overlay> p_intersection;
        for (size_t i = 0; i != tree_branches_intersection.size(); i++)
        {
            const BranchInfo& branch = tree_branches_intersection.at(i); 

            // hist names
            string h1_name = string("h1_") + branch.name;
            string h2_name = string("h2_") + branch.name;

            // fill hist 1
            string h1_draw = Form("%s>>h1_%s", branch.name.c_str(), branch.name.c_str());
            if (string_contains(branch.classname, "ROOT::Math::LorentzVector"))
            {
                h1_draw = Form("%s.mass()>>h1_%s", branch.name.c_str(), branch.name.c_str());
            }
            tree1->Draw(h1_draw.c_str(), selection.c_str(), "goff", num_entries);
            TH1F* h1 = dynamic_cast<TH1F*>(gDirectory->Get(h1_name.c_str()));

            // fill hist 2
            string h2_draw = Form("%s>>h2_%s", branch.name.c_str(), branch.name.c_str());
            if (string_contains(branch.classname, "ROOT::Math::LorentzVector"))
            {
                h2_draw = Form("%s.mass()>>h2_%s", branch.name.c_str(), branch.name.c_str());
            }
            tree2->Draw(h2_draw.c_str(), selection.c_str(), "goff", num_entries);
            TH1F* h2 = dynamic_cast<TH1F*>(gDirectory->Get(h2_name.c_str()));

            string overlay_name = string("p_" ) + branch.name;
            p_intersection[overlay_name] = TH1Overlay("", option.c_str());
            p_intersection[overlay_name].Add(h1, tree1_label, kBlue, 2);
            p_intersection[overlay_name].Add(h2, tree2_label, kRed , 2);

            delete h1;
            delete h2;
        }

        // plot the tree1 difference
        std::map<std::string, TH1Overlay> p_tree1;
        for (size_t i = 0; i != tree1_branches_diff.size(); i++)
        {
            const BranchInfo& branch = tree1_branches_diff.at(i); 

            // hist names
            string h1_name = string("h1_") + branch.name;

            // fill hist 1
            string h1_draw = Form("%s>>h1_%s", branch.name.c_str(), branch.name.c_str());
            if (string_contains(branch.classname, "ROOT::Math::LorentzVector"))
            {
                h1_draw = Form("%s.mass()>>h1_%s", branch.name.c_str(), branch.name.c_str());
            }
            tree1->Draw(h1_draw.c_str(), selection.c_str(), "goff", num_entries);
            TH1F* h1 = dynamic_cast<TH1F*>(gDirectory->Get(h1_name.c_str()));

            string overlay_name = string("p_" ) + branch.name;
            p_tree1[overlay_name] = TH1Overlay("", option.c_str());
            p_tree1[overlay_name].Add(h1, tree1_label, kBlue, 2);

            delete h1;
        }

        // plot the tree1 difference
        std::map<std::string, TH1Overlay> p_tree2;
        for (size_t i = 0; i != tree2_branches_diff.size(); i++)
        {
            const BranchInfo& branch = tree2_branches_diff.at(i); 

            // hist names
            string h2_name = string("h2_") + branch.name;

            // fill hist 1
            string h2_draw = Form("%s>>h2_%s", branch.name.c_str(), branch.name.c_str());
            if (string_contains(branch.classname, "ROOT::Math::LorentzVector"))
            {
                h2_draw = Form("%s.mass()>>h2_%s", branch.name.c_str(), branch.name.c_str());
            }
            tree1->Draw(h2_draw.c_str(), selection.c_str(), "goff", num_entries);
            TH1F* h2 = dynamic_cast<TH1F*>(gDirectory->Get(h2_name.c_str()));

            string overlay_name = string("p_" ) + branch.name;
            p_tree2[overlay_name] = TH1Overlay("", option.c_str());
            p_tree2[overlay_name].Add(h2, tree2_label, kRed, 2);

            delete h2;
        }

        // print output 
        if (!output_folder.empty())
        {
            rt::Print(p_intersection, output_folder + "/intersection"  , suffix);
            rt::Print(p_tree1       , output_folder + "/" + tree1_label, suffix);
            rt::Print(p_tree2       , output_folder + "/" + tree2_label, suffix);
        }

        // done
        return;
    }

} // namespace rt
