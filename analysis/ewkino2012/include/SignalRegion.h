#ifndef SIGNALREGIONS_H
#define SIGNALREGIONS_H

#include <string>
#include "at/Sample.h"
#include "at/YieldType.h"
#include "AnalysisType.h"
#include "SystematicType.h"
#include "TTree.h"

namespace ewkino
{
    struct SignalRegion
    {
        enum value_type
        {
            // inclusive
            sr0  = 0,  // baseline:  SS (20/20), #btags==0 (pt>30), #jets==2,3
            sr1  = 1,  // baseline + iso track veto (stop), tau veto (stop), jet-PV matching
            sr2  = 2,  // sr1 + mjj < 120
            sr3  = 3,  // sr2 + veto 76 < M_ee < 106
            sr4  = 4,  // sr3 + exactly 2 jets
            sr5  = 5,  // sr3 + no loose btags
            sr6  = 6,  // sr5 + ht < 200 && pfmet > 30
            sr7  = 7,  // sr6 + no third muon w/ pt > 5
            sr8  = 8,  // sr7 + |deta(lep1,lep2)| < 2.0
            sr9  = 9,  // sr8 + max(pt1,pt2) > 30
            sr10 = 10,  // sr9 + ht < 160
            sr11 = 11,  // sr10 + pfmet > 90
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

    // passes signal region
    // automatically determine which met/ht/njets/nbtags to use
    bool PassesSignalRegion
    (
        const SignalRegion::value_type& signal_region,
        const AnalysisType::value_type& anal_type,
        const SignalRegionType::value_type& signal_region_type = SignalRegionType::inclusive,
        const bool do_beff_sf = true, // applied for MC only
        const SystematicType::value_type& syst_type = SystematicType::None,
        const at::Sample::value_type sample = at::Sample::data,
        const bool is_fast_sim = false
    );

    // passes signal region
    bool PassesSignalRegion
    (
        const float met,
        const float ht,
        const int njets,
        const int nbtags,
        const float l1_pt,
        const float l2_pt,
        const int l1_id,
        const int l2_id,
        const SignalRegion::value_type& signal_region,
        const AnalysisType::value_type& anal_type,
        const SignalRegionType::value_type& signal_region_type = SignalRegionType::inclusive
    );

    // set aliases for TTree
    void SetSignalRegionAliases(TTree& tree, const AnalysisType::value_type& anal_type, const bool do_btag_sf = true);
    void SetSignalRegionAliases(TTree* tree, const AnalysisType::value_type& anal_type, const bool do_btag_sf = true);

} // namespace ss

#endif // SIGNALREGIONS_H
