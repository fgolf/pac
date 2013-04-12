#ifndef SIGNALREGION_H
#define SIGNALREGION_H

#include <string>
#include "at/YieldType.h"
#include "AnalysisType.h"
#include "TTree.h"

namespace ewkino
{
    struct SignalRegion
    {
        enum value_type
        {
            // inclusive
            sr0  = 0,  // baseline:  #jets>=2, #btags==0
            sr1  = 1,  // baseline + 50 < M_jj < 110

            // keep track of the size
            static_size
        };
    };

    // Signal Region Infomation
    struct SignalRegionInfo
    {
        std::string name;
        std::string title;
        std::string latex;
    };

    // Signal Region type (exclusive vs inclusive)
    struct SignalRegionType
    {
        enum value_type
        {
            inclusive, // inclusive signal region type
            exclusive, // exclusive signal region type
            static_size
        };
    };

    // Get the SignalRegion from a string
    SignalRegion::value_type GetSignalRegionFromName
    (
        const std::string& signal_region_name,
        const std::string& analysis_type_name,
        const std::string& signal_region_type_name = "inclusive"
    );

    // Get the info for the Signal region
    SignalRegionInfo GetSignalRegionInfo
    (
        const SignalRegion::value_type& signal_region,
        const AnalysisType::value_type anal_type,
        const SignalRegionType::value_type& signal_region_type = SignalRegionType::inclusive 
    );

    SignalRegionInfo GetSignalRegionInfo
    (
        const std::string& signal_region_name,
        const std::string& analysis_type_name,
        const std::string& signal_region_type_name = "inclusive" 
    );

    // Get the name of the SignalRegionType
    std::string GetSignalRegionTypeName(const SignalRegionType::value_type& signal_region_type);

    // Get the SignalRegionType from a string
    SignalRegionType::value_type GetSignalRegionTypeFromName(const std::string& signal_region_type_name);

    // passes signal rgion
    bool PassesSignalRegion
    (
        const SignalRegion::value_type& signal_region,
        const AnalysisType::value_type& anal_type,
        const SignalRegionType::value_type& signal_region_type = SignalRegionType::inclusive,
        const at::YieldType::value_type& jec_yield_type = at::YieldType::base,
        const at::YieldType::value_type& btag_yield_type = at::YieldType::base,
        const bool do_btag_sf = true  // applied for MC only
    );

    // set aliases for TTree
    void SetSignalRegionAliases(TTree& tree, const AnalysisType::value_type& anal_type);
    void SetSignalRegionAliases(TTree* tree, const AnalysisType::value_type& anal_type);

} // namespace ewkino

#endif // SIGNALREGION_H
