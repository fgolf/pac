#include "SignalRegion.h"
#include "SSB2012.h"
#include <stdexcept>

ss::SignalRegionInfo s_SignalRegionInfos[] = 
{
    // inclusive
    {
        // name
        "sr0", 
        // ROOT title
        "baseline",
        // ROOT title
        "baseline"
    },
    {
        // name
        "sr1", 
        // ROOT title
        "# jets #geq 2, H_{T} > 80 GeV, E_{T}^{miss} > 30 GeV",
        // Latex
        "$\\# jets \\geq 2,\\ H_T > 80\\ \\text{GeV},\\ E_T^{miss} > 30\\ \\text{GeV}$"
    },
    {
        // name
        "sr2", 
        // ROOT title
        "# jets #geq 2, H_{T} > 80 GeV, E_{T}^{miss} > 30 GeV, ++",
        // Latex
        "$\\# jets \\geq 2,\\ H_T > 80\\ \\text{GeV},\\ E_T^{miss} > 30\\ \\text{GeV},\\ ++$"
    },
    {
        // name
        "sr3", 
        // ROOT title
        "# jets #geq 4, H_{T} > 200 GeV, E_{T}^{miss} > 120 GeV",
        // Latex
        "$\\# jets \\geq 4,\\ H_T > 200\\ \\text{GeV},\\ E_T^{miss} > 120\\ \\text{GeV}$"
    },
    {
        // name
        "sr4", 
        // ROOT title
        "# jets #geq 4, H_{T} > 200 GeV, E_{T}^{miss} > 50 GeV",
        // Latex
        "$\\# jets \\geq 4,\\ H_T > 200\\ \\text{GeV},\\ E_T^{miss} > 50\\ \\text{GeV}$"
    },
    {
        // name
        "sr5", 
        // ROOT title
        "# jets #geq 4, H_{T} > 320 GeV, E_{T}^{miss} > 50 GeV",
        // Latex
        "$\\# jets \\geq 4,\\ H_T > 320\\ \\text{GeV},\\ E_T^{miss} > 50\\ \\text{GeV}$"
    },
    {
        // name
        "sr6", 
        // ROOT title
        "# jets #geq 4, H_{T} > 320 GeV, E_{T}^{miss} > 120 GeV",
        // Latex
        "$\\# jets \\geq 4,\\ H_T > 320\\ \\text{GeV},\\ E_T^{miss} > 120\\ \\text{GeV}$"
    },
    {
        // name
        "sr7", 
        // ROOT title
        "# btags #geq 3, # jets #geq 2, H_{T} > 200 GeV, E_{T}^{miss} > 50 GeV",
        // Latex
        "$\\# btags \\geq 3,\\ \\# jets \\geq 4,\\ H_T > 200\\ \\text{GeV},\\ E_T^{miss} > 50\\ \\text{GeV}$"
    },
    {
        // name
        "sr8", 
        // ROOT title
        "# jets #geq 4, H_{T} > 320 GeV, E_{T}^{miss} > 0 GeV",
        // Latex
        "$\\# jets \\geq 4,\\ H_T > 320\\ \\text{GeV},\\ E_T^{miss} > 0\\ \\text{GeV}$"
    },
    {
        // name
        "sr9", 
        // ROOT title
        "not used",
        // Latex
        "not used"
    },
    {
        // name
        "sr9", 
        // ROOT title
        "not used",
        // Latex
        "not used"
    },


    // exclusive
    {
        // name
        "ex_sr1", 
        // ROOT title
        "# jets #geq 4, 200 < H_{T} < 320 GeV, 50 < E_{T}^{miss} < 120 GeV",
        // Latex
        "$\\# jets \\geq 4,\\ 200 < H_T < 320\\ \\text{GeV},\\ 50 < E_T^{miss} < 120\\ \\text{GeV}$"
    },
    {
        // name
        "ex_sr2", 
        // ROOT title
        "# jets #geq 4, 200 < H_{T} < 320 GeV, E_{T}^{miss} > 120 GeV",
        // Latex
        "$\\# jets \\geq 4,\\ 200 < H_T < 320\\ \\text{GeV},\\ E_T^{miss} > 120\\ \\text{GeV}$"
    },
    {
        // name
        "ex_sr3", 
        // ROOT title
        "# jets #geq 4, H_{T} > 320 GeV, 50 < E_{T}^{miss} < 120 GeV",
        // Latex
        "$\\# jets \\geq 4,\\ H_T > 320\\ \\text{GeV},\\ 50 < E_T^{miss} < 120\\ \\text{GeV}$"
    },
    {
        // name
        "ex_sr4", 
        // ROOT title
        "# jets #geq 4, H_{T} > 320 GeV, E_{T}^{miss} > 120 GeV",
        // Latex
        "$\\# jets \\geq 4,\\ H_T > 320\\ \\text{GeV},\\ E_T^{miss} > 120\\ \\text{GeV}$"
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
    bool PassesSignalRegion(const SignalRegion::value_type& signal_region, int num_btags)
    {
        using namespace ssb;
        switch (signal_region)
        {
            // inclusive
            case SignalRegion::sr0  : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80  && pfmet() > 0  );
            case SignalRegion::sr1  : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80  && pfmet() > 30 );
            case SignalRegion::sr2  : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80  && pfmet() > 30 && is_pp());
            case SignalRegion::sr3  : return (nbtags() >= num_btags && njets() >= 4 && ht() > 200 && pfmet() > 120);
            case SignalRegion::sr4  : return (nbtags() >= num_btags && njets() >= 4 && ht() > 200 && pfmet() > 50 );
            case SignalRegion::sr5  : return (nbtags() >= num_btags && njets() >= 4 && ht() > 320 && pfmet() > 50 );
            case SignalRegion::sr6  : return (nbtags() >= num_btags && njets() >= 4 && ht() > 320 && pfmet() > 120);
            case SignalRegion::sr7  : return (nbtags() >= 3         && njets() >= 2 && ht() > 200 && pfmet() > 50 );
            case SignalRegion::sr8  : return (nbtags() >= num_btags && njets() >= 4 && ht() > 320 && pfmet() > 0  );
            case SignalRegion::sr9  : return false; 
            case SignalRegion::sr10 : return false; 

            // exclusive
            case SignalRegion::ex_sr1 : return (nbtags() >= num_btags && njets() >= 4 && (200 < ht() && ht() < 320) && (50 < pfmet() && pfmet() < 120));
            case SignalRegion::ex_sr2 : return (nbtags() >= num_btags && njets() >= 4 && (200 < ht() && ht() < 320) && (pfmet() > 120                ));
            case SignalRegion::ex_sr3 : return (nbtags() >= num_btags && njets() >= 4 && (ht() > 320              ) && (50 < pfmet() && pfmet() < 120));
            case SignalRegion::ex_sr4 : return (nbtags() >= num_btags && njets() >= 4 && (ht() > 320              ) && (pfmet() > 120                ));
            //case SignalRegion::ex_sr1 : return (nbtags() >= num_btags && njets() >= 4 && (((80  < ht() && ht() < 200) && (0  < pfmet() && pfmet() < 50 )) ||
            //                                                                              ((200 < ht() && ht() < 320) && (0  < pfmet() && pfmet() < 50 )) ||
            //                                                                              ((80  < ht() && ht() < 200) && (50 < pfmet() && pfmet() < 120)));
            //case SignalRegion::ex_sr1 : return (nbtags() >= num_btags && njets() >= 4 && (((80  < ht() && ht() < 200) && (0  < pfmet() && pfmet() < 50 )) ||
            //                                                                              ((200 < ht() && ht() < 320) && (0  < pfmet() && pfmet() < 50 )) ||
            //                                                                              ((80  < ht() && ht() < 200) && (50 < pfmet() && pfmet() < 120)));

            default: return false;
        }
        return false;
    }

    bool PassesSignalRegion(unsigned int signal_region_number, int num_btags)
    {
        return PassesSignalRegion(static_cast<SignalRegion::value_type>(signal_region_number), num_btags);
    }

	// set aliases for TTree
    void SetSignalRegionAliases(TTree& tree)
    {
        // inclusive
        tree.SetAlias("sr0", "nbtags>=2 && njets>=2 && ht > 80   && pfmet > 0"          ); 
        tree.SetAlias("sr1", "nbtags>=2 && njets>=2 && ht > 80   && pfmet > 30"         ); 
        tree.SetAlias("sr2", "nbtags>=2 && njets>=2 && ht > 80   && pfmet > 30 && is_pp"); 
        tree.SetAlias("sr3", "nbtags>=2 && njets>=4 && ht > 200  && pfmet > 120"        ); 
        tree.SetAlias("sr4", "nbtags>=2 && njets>=4 && ht > 200  && pfmet > 50"         ); 
        tree.SetAlias("sr5", "nbtags>=2 && njets>=4 && ht > 320  && pfmet > 50"         ); 
        tree.SetAlias("sr6", "nbtags>=2 && njets>=4 && ht > 320  && pfmet > 120"        ); 
        tree.SetAlias("sr7", "nbtags>=2 && njets>=2 && ht > 200  && pfmet > 50"         ); 
        tree.SetAlias("sr8", "nbtags>=2 && njets>=4 && ht > 320"                        ); 

        // exclusive
        tree.SetAlias("ex_sr1", "nbtags>=2 && njets>=4 && (200 < ht && ht < 320) && (50 < pfmet && pfmet < 120)"); 
        tree.SetAlias("ex_sr2", "nbtags>=2 && njets>=4 && (200 < ht && ht < 320) && (pfmet > 120)"              ); 
        tree.SetAlias("ex_sr3", "nbtags>=2 && njets>=4 && (ht > 320) && (50 < pfmet && pfmet < 120)"            ); 
        tree.SetAlias("ex_sr4", "nbtags>=2 && njets>=4 && (ht > 320) && (pfmet > 120)"                          ); 
    }

    void SetSignalRegionAliases(TTree* tree)
    {
        SetSignalRegionAliases(*tree);
    }

} // namespace ss
