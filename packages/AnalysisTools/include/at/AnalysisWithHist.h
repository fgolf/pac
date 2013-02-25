#ifndef AT_ANALYSIWITHHIST_H
#define AT_ANALYSIWITHHIST_H

// c++
#include <string>
#include "at/AnalysisBase.h"
#include "rt/TH1Container.h"

namespace at
{
    class AnalysisWithHist : public AnalysisBase
    {
        public:
            // construct:
            AnalysisWithHist
            (
                 const std::string& root_file_name, 
                 const bool print = false,
                 const std::string& suffix = "png"
            );

            // destory (this writes the hists to a file):
            virtual ~AnalysisWithHist();

            // function operator:
            virtual int operator () (long event);

        protected:
            // members:
            bool m_print;
            std::string m_suffix;
            rt::TH1Container m_hist_container;

        protected:
            // methods 
            virtual void BookHists(); 
    };

} // namespace at

#endif // AT_ANALYSISWITHHISTH

