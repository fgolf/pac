#ifndef SIGNALREGIONS_H
#define SIGNALREGIONS_H

#include <string>

namespace ss
{
    struct SignalRegion
    {
        enum value_type
        {
            sr0, // baseline
            sr1, // HT > 80, MET > 30
            sr2, // HT > 80, MET > 30, ++
            sr3, // HT > 200, MET > 50
            sr4, // HT > 200, MET > 120
            sr5, // HT > 320, MET > 50
            sr6, // HT > 320, MET > 120
            sr7, // HT > 200, MET > 50, # btags >= 3
            sr8, // HT > 320, no MET cut
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
    bool PassesSignalRegion(const SignalRegion::value_type& signal_region);
    bool PassesSignalRegion(unsigned int signal_region_number);

} // namespace ss

#endif // SIGNALREGIONS_H
