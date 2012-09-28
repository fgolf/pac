#ifndef SIGNALREGIONS_H
#define SIGNALREGIONS_H

#include <string>
#include "TTree.h"

namespace ss
{
    struct SignalRegion
    {
        enum value_type
        {
            // inclusive
            sr0, // baseline
            sr1, // #btags >= 2, #jets >= 2, HT > 80, MET > 30
            sr2, // #btags >= 2, #jets >= 2, HT > 80, MET > 30, ++
            sr3, // #btags >= 2, #jets >= 4, HT > 200, MET > 50
            sr4, // #btags >= 2, #jets >= 4, HT > 200, MET > 120
            sr5, // #btags >= 2, #jets >= 4, HT > 320, MET > 50
            sr6, // #btags >= 2, #jets >= 4, HT > 320, MET > 120
            sr7, // #btags >= 2, #jets >= 2, HT > 200, MET > 50
            sr8, // #btags >= 2, #jets >= 4, HT > 320, no MET cut
            static_size
        };
    };

    // Signal Region Infomation
    struct SignalRegionInfo
    {
        std::string name;
        std::string title;
    };


    // Get the SignalRegion from a string
    SignalRegion::value_type GetSignalRegionFromName(const std::string& signal_region_name);

    // Get the info for the Singal region
    SignalRegionInfo GetSignalRegionInfo(const SignalRegion::value_type& signal_region);
    SignalRegionInfo GetSignalRegionInfo(const std::string& signal_region_name);
    SignalRegionInfo GetSignalRegionInfo(unsigned int signal_region_number);

    // passes signal rgion
    bool PassesSignalRegion(const SignalRegion::value_type& signal_region, int num_btags = 0);
    bool PassesSignalRegion(unsigned int signal_region_number, int num_btags = 0);

    //bool PassesSignalRegionExclusive(const SignalRegion::value_type& signal_region, int num_btags = 0);
    //bool PassesSignalRegionExclusive(unsigned int signal_region_number, int num_btags = 0);

	// set aliases for TTree
    void SetSignalRegionAliases(TTree& tree);

} // namespace ss

#endif // SIGNALREGIONS_H
