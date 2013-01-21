#ifndef SIGNALREGIONS_H
#define SIGNALREGIONS_H

#include <string>
#include "AnalysisType.h"
#include "TTree.h"

namespace ss
{
    struct SignalRegion
    {
        enum value_type
        {
            // inclusive
            sr0  = 0,  // baseline:  #jets>=2, if HT<500 then MET>30, HT>80/250 (high/low pT analysis)
            sr1  = 1,  // baseline + #jets>=2, #btags>=0, MET[50-120], HT[200-400]
            sr2  = 2,  // baseline + #jets>=2, #btags>=0, MET[50-120], HT>400
            sr3  = 3,  // baseline + #jets>=4, #btags>=0, MET[50-120], HT[200-400]
            sr4  = 4,  // baseline + #jets>=4, #btags>=0, MET[50-120], HT>400
            sr5  = 5,  // baseline + #jets>=2, #btags>=0, MET>120, HT[200-400]
            sr6  = 6,  // baseline + #jets>=2, #btags>=0, MET>120, HT>400
            sr7  = 7,  // baseline + #jets>=4, #btags>=0, MET>120, HT[200-400]
            sr8  = 8,  // baseline + #jets>=4, #btags>=0, MET>120, HT>400
            sr9  = 9,  // not used
            sr10 = 10, // baseline:  #jets>=2, #btags>=1, if HT<500 then MET>30, HT>80/250 (high/low pT analysis)
            sr11 = 11, // baseline + #jets>=2, #btags>=1, MET[50-120], HT[200-400]
            sr12 = 12, // baseline + #jets>=2, #btags>=1, MET[50-120], HT>400
            sr13 = 13, // baseline + #jets>=4, #btags>=1, MET[50-120], HT[200-400]
            sr14 = 14, // baseline + #jets>=4, #btags>=1, MET[50-120], HT>400
            sr15 = 15, // baseline + #jets>=2, #btags>=1, MET>120, HT[200-400]
            sr16 = 16, // baseline + #jets>=2, #btags>=1, MET>120, HT>400
            sr17 = 17, // baseline + #jets>=4, #btags>=1, MET>120, HT[200-400]
            sr18 = 18, // baseline + #jets>=4, #btags>=1, MET>120, HT>400
            sr19 = 19, // not used
            sr20 = 20, // baseline:  #jets>=2, #btags>=2, if HT<500 then MET>30, HT>80/250 (high/low pT analysis)
            sr21 = 21, // baseline + #jets>=2, #btags>=2, MET[50-120], HT[200-400]
            sr22 = 22, // baseline + #jets>=2, #btags>=2, MET[50-120], HT>400
            sr23 = 23, // baseline + #jets>=4, #btags>=2, MET[50-120], HT[200-400]
            sr24 = 24, // baseline + #jets>=4, #btags>=2, MET[50-120], HT>400
            sr25 = 25, // baseline + #jets>=2, #btags>=2, MET>120, HT[200-400]
            sr26 = 26, // baseline + #jets>=2, #btags>=2, MET>120, HT>400
            sr27 = 27, // baseline + #jets>=4, #btags>=2, MET>120, HT[200-400]
            sr28 = 28, // baseline + #jets>=4, #btags>=2, MET>120, HT>400

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
        const AnalysisType::value_type anal_type,
        const SignalRegionType::value_type& signal_region_type = SignalRegionType::inclusive
    );

    // set aliases for TTree
    //void SetSignalRegionAliases(TTree& tree);
    //void SetSignalRegionAliases(TTree* tree);

    // function to test the root titles
    //void TestSignalRegionTitles
    //(
    //    const AnalysisType::value_type& at, 
    //    const SignalRegionType::value_type& srt = SignalRegionType::inclusive
    //);

} // namespace ss

#endif // SIGNALREGIONS_H
