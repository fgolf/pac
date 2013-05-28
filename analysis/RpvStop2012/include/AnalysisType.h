#ifndef RPVSTOP_ANALYSISTYPE_H
#define RPVSTOP_ANALYSISTYPE_H

#include <string>

class TTree;

namespace rpv_stop
{
    struct AnalysisType
    {
        enum value_type
        {
            mmbb,
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

} // namespace rpv_stop

#endif // RPVSTOP_ANALYSISTYPE_H
