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
            sr0  = 0,  // baseline
            sr1  = 1,  // #btags >= 2, #jets >= 2, HT > 80, MET > 30
            sr2  = 2,  // #btags >= 2, #jets >= 2, HT > 80, MET > 30, ++
            sr3  = 3,  // #btags >= 2, #jets >= 4, HT > 200, MET > 50
            sr4  = 4,  // #btags >= 2, #jets >= 4, HT > 200, MET > 120
            sr5  = 5,  // #btags >= 2, #jets >= 4, HT > 320, MET > 50
            sr6  = 6,  // #btags >= 2, #jets >= 4, HT > 320, MET > 120
            sr7  = 7,  // #btags >= 2, #jets >= 2, HT > 200, MET > 50
            sr8  = 8,  // #btags >= 2, #jets >= 4, HT > 320, no MET cut
            sr9  = 9,  // #btags >= 2, #jets >= 2, HT > 80, MET > 30, --
            sr10 = 10, // not used

            // exclusive
            ex_sr1 = 11, // #btags >= 2, #jets >= 4, 200 < HT < 320, 50 < MET < 120
            ex_sr2 = 12, // #btags >= 2, #jets >= 4, 200 < HT < 320, MET > 120
            ex_sr3 = 13, // #btags >= 2, #jets >= 4, HT > 320, 50 < MET < 120
            ex_sr4 = 14, // #btags >= 2, #jets >= 4, HT > 320, MET > 120
            ex_sr5 = 15, // #btags >= 2, #jets >= 4, HT > 320, MET < 50

            sr16 = 16,  // met1
            sr17 = 17,  // met2
            sr18 = 18,  // met3
            sr19 = 19,  // met3
            sr20 = 20,  // ht1
            sr21 = 21,  // ht2
            sr22 = 22,  // ht3
            sr23 = 23,  // njets1
            sr24 = 24,  // njets2
            sr25 = 25,  // njets3
            sr26 = 26,  // njets4
            sr27 = 27,  // njets5
            sr28 = 28,  // njets6
            sr29 = 29,  // njets7
            sr30 = 30,  // njets8
            sr31 = 31,  // nbtags1
            sr32 = 32,  // nbtags2
            sr33 = 33,  // nbtags3
            sr34 = 34,  // nbtags4
            sr35 = 35,  // nbtags5
            sr36 = 36,  // nbtags6
            sr37 = 37,  // nbtags7
            sr38 = 38,  // nbtags8
            sr39 = 39,  // l1_pt1
            sr40 = 40,  // l1_pt2
            sr41 = 41,  // l1_pt3
            sr42 = 42,  // l1_pt4
            sr43 = 43,  // l1_pt5
            sr44 = 44,  // l1_pt6
            sr45 = 45,  // l1_pt7
            sr46 = 46,  // l1_pt9
            sr47 = 47,  // l1_pt9
            sr48 = 48,  // l1_pt10
            sr49 = 49,  // l2_pt1
            sr50 = 50,  // l2_pt2
            sr51 = 51,  // l2_pt3
            sr52 = 52,  // l2_pt4
            sr53 = 53,  // l2_pt5
            sr54 = 54,  // l2_pt6
            sr55 = 55,  // l2_pt7
            sr56 = 56,  // l2_pt9
            sr57 = 57,  // l2_pt9
            sr58 = 58,  // l2_pt10

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


    // Get the SignalRegion from a string
    SignalRegion::value_type GetSignalRegionFromName(const std::string& signal_region_name);

    // Get the info for the Signal region
    SignalRegionInfo GetSignalRegionInfo(const SignalRegion::value_type& signal_region);
    SignalRegionInfo GetSignalRegionInfo(const std::string& signal_region_name);
    SignalRegionInfo GetSignalRegionInfo(unsigned int signal_region_number);

    // passes signal rgion
    bool PassesSignalRegion(const SignalRegion::value_type& signal_region, int num_btags = 0);
    bool PassesSignalRegion(unsigned int signal_region_number, int num_btags = 0);

	// set aliases for TTree
    void SetSignalRegionAliases(TTree& tree);

} // namespace ss

#endif // SIGNALREGIONS_H
