#include "at/AnalysisWithHist.h"
#include "at/AnalysisBase.h"
#include "rt/MiscTools.h"
#include <iostream>

using namespace std;

namespace at
{
    // construct:
    AnalysisWithHist::AnalysisWithHist
    (
         const std::string& root_file_name, 
         bool print,
         const std::string& suffix
    )
        : AnalysisBase(root_file_name) 
        , m_print(print)
        , m_suffix(suffix)
    {
        BookHists();
    }

    // destroy:
    AnalysisWithHist::~AnalysisWithHist()
    {
        // write output
        cout << "Writing histogram root file to: " << m_root_file->GetName() << endl;
        m_hist_container.Write(m_root_file.get());
        if (m_print)
        {
            std::string output_print_path = rt::dirname(m_root_file->GetName()) + "/" + m_suffix;
            m_hist_container.Print(output_print_path, m_suffix);
        }
    }

    // function operator
    int AnalysisWithHist::operator () (long event)
    {
        // convenince alias
        rt::TH1Container& h = m_hist_container;

        // count the number of entries
        rt::Fill(h["h_count"], 1.0); 

        return 0;
    }

    // methods:
    void AnalysisWithHist::BookHists()
    {
        rt::TH1Container& h = m_hist_container;

        h.Add(new TH1D("h_count","# of events", 3, -0.5, 2.5));
    }

} // namespace at

