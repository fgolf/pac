#include "SignalRegion.h"
#include "SSB2012.h"
#include <stdexcept>

ss::SignalRegionInfo s_SignalRegionInfos[] = 
{
    {
        // name
        "sr0", 
        // ROOT title
        "baseline"
    },
    {
        // name
        "sr1", 
        // ROOT title
        "H_{T} > 80 GeV, E_{T}^{miss} > 30 GeV"
    },
    {
        // name
        "sr2", 
        // ROOT title
        "H_{T} > 80 GeV, E_{T}^{miss} > 30 GeV, ++"
    },
    {
        // name
        "sr3", 
        // ROOT title
        "H_{T} > 200 GeV, E_{T}^{miss} > 120 GeV"
    },
    {
        // name
        "sr4", 
        // ROOT title
        "H_{T} > 200 GeV, E_{T}^{miss} > 50 GeV"
    },
    {
        // name
        "sr5", 
        // ROOT title
        "H_{T} > 320 GeV, E_{T}^{miss} > 50 GeV"
    },
    {
        // name
        "sr6", 
        // ROOT title
        "H_{T} > 320 GeV, E_{T}^{miss} > 120 GeV"
    },
    {
        // name
        "sr7", 
        // ROOT title
        "H_{T} > 200 GeV, E_{T}^{miss} > 50 GeV, # btags #geq 3"
    },
    {
        // name
        "sr8", 
        // ROOT title
        "H_{T} > 320 GeV, E_{T}^{miss} > 0 GeV"
    }
};

// check that the SignalRegionInfoArray is the same size as the enum
// fails at compile time if it does
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
#define STATIC_ASSERT(expr) typedef char static_assert[(expr) ? 1 : -1]
STATIC_ASSERT(ARRAY_SIZE(s_SignalRegionInfos) == ss::SignalRegion::static_size);

namespace ss
{
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
            case SignalRegion::sr3 : return (ht() > 200.0  && pfmet() > 120.0);
            case SignalRegion::sr4 : return (ht() > 200.0  && pfmet() > 50.0 );
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

	// set aliases for TTree
    void SetSignalRegionAliases(TTree& tree, int nbtags, int njets)
    {
		string cut = Form("is_ss && nbtags>=%d && njets>=%d");
        tree.SetAlias("sr0", (cut + " && ht > 80.0   && pfmet >  0.0"             ).c_str()); 
        tree.SetAlias("sr1", (cut + " && ht > 80.0   && pfmet > 30.0"             ).c_str()); 
        tree.SetAlias("sr2", (cut + " && ht > 80.0   && pfmet > 30.0 && is_pp"    ).c_str()); 
        tree.SetAlias("sr3", (cut + " && ht > 200.0  && pfmet > 120.0"            ).c_str()); 
        tree.SetAlias("sr4", (cut + " && ht > 200.0  && pfmet > 50.0"             ).c_str()); 
        tree.SetAlias("sr5", (cut + " && ht > 320.0  && pfmet > 50.0"             ).c_str()); 
        tree.SetAlias("sr6", (cut + " && ht > 320.0  && pfmet > 120.0"            ).c_str()); 
        tree.SetAlias("sr7", (cut + " && ht > 200.0  && pfmet > 50.0 && nbtags>=3").c_str()); 
        tree.SetAlias("sr8", (cut + " && ht > 320.0"                              ).c_str()); 
    }

} // namespace ss
