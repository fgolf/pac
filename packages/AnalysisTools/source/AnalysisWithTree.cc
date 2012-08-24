#include "at/AnalysisWithTree.h"
#include "at/AnalysisBase.h"
#include "rt/MiscTools.h"
#include <iostream>

using namespace std;

namespace at
{
    // construct:
    AnalysisWithTree::AnalysisWithTree
    (
         const std::string& root_file_name, 
         const std::string& tree_name, 
         const std::string& tree_title 
    )
        : AnalysisBase(root_file_name) 
        , m_tree(new TTree(tree_name.c_str(), tree_title.c_str()))
    {
		m_tree->SetDirectory(m_root_file.get());

        // begin job
        BeginJob();
    }

    // destroy:
    AnalysisWithTree::~AnalysisWithTree()
    {
        // end job
        EndJob();

        // write output
        cout << "Writing ntuple root file to:    " << m_root_file->GetName() << endl;
		cout << "TTree " << m_tree->GetName() << " has " << m_tree->GetEntries() << " entries" << endl;
        m_root_file->cd();
        m_tree->Write();
    }

    // function operator
    int AnalysisWithTree::operator () (long event)
    {
        return 0;
    }

    // methods:

} // namespace at

