#ifndef AT_ANALYSIWITHTREEANDHIST_H
#define AT_ANALYSIWITHTREEANDHIST_H

// c++
#include <string>
#include <tr1/memory>
#include "TTree.h"
#include "at/AnalysisBase.h"
#include "rt/TH1Container.h"

namespace at
{
    class AnalysisWithTreeAndHist : public AnalysisBase
    {
        public:
            // construct:
            AnalysisWithTreeAndHist
            (
                const std::string& root_file_name, 
                const std::string& tree_name, 
                const std::string& tree_title = "",
                const bool print = false,
                const std::string& suffix = "png"
            );

            // destory (this writes the hists to a file):
            virtual ~AnalysisWithTreeAndHist();

            // function operator:
            virtual int operator () (long event);

            // methods:
            virtual void BeginJob();
            virtual void BookHists();
            virtual void EndJob();

        protected:
            // members:
            bool m_print;
            std::string m_suffix;
            rt::TH1Container m_hist_container;
            TTree* m_tree; // owned by the root file
    };

} // namespace at

#endif // AT_ANALYSISWITHTREEANDHIST_H
