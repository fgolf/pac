#ifndef AT_ANALYSISBASE_H
#define AT_ANALYSISBASE_H

#include <string>
#include "boost/shared_ptr.hpp"
#include "TFile.h"

namespace at
{
    class AnalysisBase
    {
        public:
            // construct:
            AnalysisBase(const std::string& root_file_name);

            // destory (this writes the hists to a file):
            virtual ~AnalysisBase();

            // function operator:
            virtual int operator () (long event);
            virtual int operator () (long event, const std::string& filename);

            // methods
            virtual void BeginJob();
            virtual void EndJob();
            virtual int Analyze(long event);
            virtual int Analyze(long event, const std::string& filename);

        protected:
            // members:
            boost::shared_ptr<TFile> m_root_file;
    };

} // namespace at

#endif // AT_ANALYSISBASE_H

