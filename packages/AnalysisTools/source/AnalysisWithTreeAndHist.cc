#include "at/AnalysisWithTreeAndHist.h"
#include "at/AnalysisBase.h"
#include "rt/MiscTools.h"
#include <iostream>

using namespace std;

namespace at
{
    // construct:
    AnalysisWithTreeAndHist::AnalysisWithTreeAndHist
    (
         const std::string& root_file_name, 
         const std::string& tree_name, 
         const std::string& tree_title,
         const bool print,
         const std::string& suffix
    )
        : AnalysisBase(root_file_name) 
        , m_tree(new TTree(tree_name.c_str(), tree_title.c_str()))
    {
		m_tree->SetDirectory(m_root_file.get());

        // begin job
        BeginJob();
    }

    // destroy:
    AnalysisWithTreeAndHist::~AnalysisWithTreeAndHist()
    {
    }

    // function operator
    int AnalysisWithTreeAndHist::operator () (long event)
    {
        return 0;
    }

    void AnalysisWithTreeAndHist::BeginJob()
    {
        // book the histograms
        BookHists();
    }

    void AnalysisWithTreeAndHist::EndJob()
    {
        // write output
        cout << "Writing tree and histograms to root file:    " << m_root_file->GetName() << endl;
		cout << "TTree " << m_tree->GetName() << " has " << m_tree->GetEntries() << " entries" << endl;
        m_hist_container.Write(m_root_file.get());
        m_root_file->cd();
        m_tree->Write();

        // write output
        if (m_print)
        {
            std::string output_print_path = rt::dirname(m_root_file->GetName()) + "/" + m_suffix;
            m_hist_container.Print(output_print_path, m_suffix);
        }

        // call base classes EndJob
        AnalysisBase::EndJob();
    }

    // methods:
    void AnalysisWithTreeAndHist::BookHists()
    {
        rt::TH1Container& h = m_hist_container;

        h.Add(new TH1F("h_count","# of events", 3, -0.5, 2.5));
    }

} // namespace at

