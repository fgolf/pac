#ifndef AT_ANALYSIWITHTREE_H
#define AT_ANALYSIWITHTREE_H

// c++
#include <string>
#include "at/AnalysisBase.h"
#include "TTree.h"

namespace at
{
    class AnalysisWithTree : public AnalysisBase
    {
        public:
            // construct:
            AnalysisWithTree
            (
                const std::string& root_file_name, 
                const std::string& tree_name, 
                const std::string& tree_title = "" 
            );

            // destory (this writes the hists to a file):
            virtual ~AnalysisWithTree();

            // function operator:
            virtual int operator () (long event);

            // methods:
            virtual void EndJob();

        protected:
            // members:
            TTree* m_tree;
    };

} // namespace at

#endif // AT_ANALYSISWITHTREEH
