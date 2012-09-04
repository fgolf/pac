#include "SignalRegion.h"
#include "SSB2012.h"
#include <stdexcept>

SignalRegionInfo s_SignalRegionInfos[] = 
{
    {
        // name
        "sr0", 
        // title,
        "baseline" 
    },
    {
        // name
        "sr1", 
        // title,
        "ht80met30" 
    },
    {
        // name
        "sr2", 
        // title,
        "ht80met30pp" 
    },
    {
        // name
        "sr3", 
        // title,
        "ht200met50" 
    },
    {
        // name
        "sr4", 
        // title,
        "ht200met120" 
    },
    {
        // name
        "sr5", 
        // title,
        "ht320met50" 
    },
    {
        // name
        "sr6", 
        // title,
        "ht320met120" 
    },
    {
        // name
        "sr7", 
        // title,
        "ht200met50gte3btag" 
    },
    {
        // name
        "sr8", 
        // title,
        "ht320nomet" 
    }
};

// check that the SignalRegionInfoArray is the same size as the enum
// fails at compile time if it does
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
#define STATIC_ASSERT(expr) typedef char static_assert[(expr) ? 1 : -1]
STATIC_ASSERT(ARRAY_SIZE(s_SignalRegionInfos) == SignalRegion::static_size);

// wrapper function to get the SignalRegionInfo
SignalRegion::value_type GetSignalRegionFromName(const std::string& signal_region_name)
{
    using namespace std;
    SignalRegion::value_type signal_region = SignalRegion::static_size;
    for (size_t i = 0; i != SignalRegion::static_size; i++)
    {
        if (string(s_SignalRegionInfos[i].name) == signal_region_name)
        {
            signal_region = static_cast<SignalRegion::value_type>(i);
            break;
        }
    }

    // throw if not found
    if (signal_region == SignalRegion::static_size)
    {
        throw std::domain_error("ERROR: at::GetSignalRegionInfo(std::string): signa_region not found!");
    }

    return signal_region; 
}

// wrapper function to get the SignalRegionInfo
SignalRegionInfo GetSignalRegionInfo(const SignalRegion::value_type& signal_region)
{
    return s_SignalRegionInfos[signal_region]; 
}

SignalRegionInfo GetSignalRegionInfo(const std::string& signal_region_name)
{
    SignalRegion::value_type signal_region = GetSignalRegionFromName(signal_region_name); 
    return GetSignalRegionInfo(signal_region); 
}

SignalRegionInfo GetSignalRegionInfo(unsigned int signal_region_number)
{
    SignalRegion::value_type signal_region = static_cast<SignalRegion::value_type>(signal_region_number); 
    return GetSignalRegionInfo(signal_region); 
}

// passes signal region
bool PassesSignalRegion(const SignalRegion::value_type& signal_region)
{
    using namespace ssb;
    switch (signal_region)
    {
        case SignalRegion::sr0 : return (ht() > 80.0   && pfmet() >  0.0 );
        case SignalRegion::sr1 : return (ht() > 80.0   && pfmet() > 30.0 );
        case SignalRegion::sr2 : return (ht() > 80.0   && pfmet() > 30.0 && is_pp());
        case SignalRegion::sr3 : return (ht() > 200.0  && pfmet() > 50.0 );
        case SignalRegion::sr4 : return (ht() > 200.0  && pfmet() > 120.0);
        case SignalRegion::sr5 : return (ht() > 320.0  && pfmet() > 50.0 );
        case SignalRegion::sr6 : return (ht() > 320.0  && pfmet() > 120.0);
        case SignalRegion::sr7 : return (ht() > 200.0  && pfmet() > 50.0 && nbtags()>=3);
        case SignalRegion::sr8 : return (ht() > 320.0);
        default: return false;
    }
    return false;
}

bool PassesSignalRegion(unsigned int signal_region_number)
{
    return PassesSignalRegion(static_cast<SignalRegion::value_type>(signal_region_number));
}
