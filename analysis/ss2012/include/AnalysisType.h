#ifndef SS_ANALYSISTYPE_H
#define SS_ANALYSISTYPE_H

#include <string>

class TTree;

namespace ss
{
    struct AnalysisType
    {
        enum value_type
        {
            high_pt,
            low_pt,
            vlow_pt,
            high_pt_eth,
            static_size
        };
    };

    // Signal Region Infomation
    struct AnalysisTypeInfo
    {
        std::string name;
        std::string short_name;
        std::string title;
        std::string latex;
    };


    // Get the AnalysisType from a string
    AnalysisType::value_type GetAnalysisTypeFromName(const std::string& analysis_type_name);

    // Get the info for the Signal region
    AnalysisTypeInfo GetAnalysisTypeInfo(const AnalysisType::value_type& analysis_type);
    AnalysisTypeInfo GetAnalysisTypeInfo(const std::string& analysis_type_name);

    // set a ROOT CINT alias
    void SetAnalysisTypeAliases(TTree& tree);

} // namespace ss

#endif // SS_ANALYSISTYPE_H
