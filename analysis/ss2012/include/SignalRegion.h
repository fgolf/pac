#ifndef SIGNALREGIONS_H
#define SIGNALREGIONS_H

#include <string>

struct SignalRegion
{
    enum value_type
    {
        sr0,
        sr1,
        sr2,
        sr3,
        sr4,
        sr5,
        sr6,
        sr7,
        sr8,
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

#endif // SIGNALREGIONS_H
