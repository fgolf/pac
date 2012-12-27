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
        "# jets #geq 2, H_{T} > 80 GeV, E_{T}^{miss} > 0 GeV",
        // Latex
        "$\\# jets \\geq 2,\\ H_T > 80\\ \\text{GeV},\\ E_T^{miss} > 0\\ \\text{GeV}$"
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
        "# jets #geq 2, H_{T} > 80 GeV, E_{T}^{miss} > 30 GeV, --",
        // Latex
        "$\\# jets \\geq 2,\\ H_T > 80\\ \\text{GeV},\\ E_T^{miss} > 30\\ \\text{GeV},\\ --$"
    },
    {
        // name
        "sr10", 
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
    },
    {
        // name
        "ex_sr5", 
        // ROOT title
        "# jets #geq 4, H_{T} > 320 GeV, E_{T}^{miss} < 50 GeV",
        // Latex
        "$\\# jets \\geq 4,\\ H_T > 320\\ \\text{GeV},\\ E_T^{miss} < 50\\ \\text{GeV}$"
    },

    // place holders for projection plots
    {"sr16", "", ""},
    {"sr17", "", ""},
    {"sr18", "", ""},
    {"sr19", "", ""},
    {"sr20", "", ""},
    {"sr21", "", ""},
    {"sr22", "", ""},
    {"sr23", "", ""},
    {"sr24", "", ""},
    {"sr25", "", ""},
    {"sr26", "", ""},
    {"sr27", "", ""},
    {"sr28", "", ""},
    {"sr29", "", ""},
    {"sr30", "", ""},
    {"sr31", "", ""},
    {"sr32", "", ""},
    {"sr33", "", ""},
    {"sr34", "", ""},
    {"sr35", "", ""},
    {"sr36", "", ""},
    {"sr37", "", ""},
    {"sr38", "", ""},
    {"sr39", "", ""},
    {"sr40", "", ""},
    {"sr41", "", ""},
    {"sr42", "", ""},
    {"sr43", "", ""},
    {"sr44", "", ""},
    {"sr45", "", ""},
    {"sr46", "", ""},
    {"sr47", "", ""},
    {"sr48", "", ""},
    {"sr49", "", ""},
    {"sr50", "", ""},
    {"sr51", "", ""},
    {"sr52", "", ""},
    {"sr53", "", ""},
    {"sr54", "", ""},
    {"sr55", "", ""},
    {"sr56", "", ""},
    {"sr57", "", ""},
    {"sr58", "", ""}
};

// check that the SignalRegionInfoArray is the same size as the enum
// fails at compile time if it does
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
#define STATIC_ASSERT(expr) typedef char my_static_assert[(expr) ? 1 : -1]
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
            throw std::domain_error("ERROR: at::GetSignalRegionInfo(std::string): signal_region not found!");
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
        float pt1 = lep1_p4().pt();
        float pt2 = lep2_p4().pt();
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
            case SignalRegion::sr9  : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80  && pfmet() > 30 && is_pp());
            case SignalRegion::sr10 : return false; // not used

            // exclusive
            case SignalRegion::ex_sr1 : return (nbtags() >= num_btags && njets() >= 4 && (200 < ht() && ht() < 320) && (50 < pfmet() && pfmet() < 120));
            case SignalRegion::ex_sr2 : return (nbtags() >= num_btags && njets() >= 4 && (200 < ht() && ht() < 320) && (pfmet() > 120                ));
            case SignalRegion::ex_sr3 : return (nbtags() >= num_btags && njets() >= 4 && (ht() > 320              ) && (50 < pfmet() && pfmet() < 120));
            case SignalRegion::ex_sr4 : return (nbtags() >= num_btags && njets() >= 4 && (ht() > 320              ) && (pfmet() > 120                ));
            case SignalRegion::ex_sr5 : return (nbtags() >= num_btags && njets() >= 4 && (ht() > 320              ) && (0  < pfmet() && pfmet() < 50 ));

            // bogus signal regions for projection plots
            case SignalRegion::sr16 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && 0   < pfmet() && pfmet() < 30.00);
            case SignalRegion::sr17 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && 30  < pfmet() && pfmet() < 50.00);
            case SignalRegion::sr18 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && 50  < pfmet() && pfmet() < 120.0);
            case SignalRegion::sr19 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && 120 < pfmet() && pfmet() < 200.0);

            case SignalRegion::sr20 : return (nbtags() >= num_btags && njets() >= 2 && 80  < ht() && ht() < 200);
            case SignalRegion::sr21 : return (nbtags() >= num_btags && njets() >= 2 && 200 < ht() && ht() < 320);
            case SignalRegion::sr22 : return (nbtags() >= num_btags && njets() >= 2 && 320 < ht() && ht() < 800);

            case SignalRegion::sr23 : return (nbtags() >= num_btags && njets() == 2 && ht() > 80);
            case SignalRegion::sr24 : return (nbtags() >= num_btags && njets() == 3 && ht() > 80);
            case SignalRegion::sr25 : return (nbtags() >= num_btags && njets() == 4 && ht() > 80);
            case SignalRegion::sr26 : return (nbtags() >= num_btags && njets() == 5 && ht() > 80);
            case SignalRegion::sr27 : return (nbtags() >= num_btags && njets() == 6 && ht() > 80);
            case SignalRegion::sr28 : return (nbtags() >= num_btags && njets() == 7 && ht() > 80);
            case SignalRegion::sr29 : return (nbtags() >= num_btags && njets() == 8 && ht() > 80);
            case SignalRegion::sr30 : return (nbtags() >= num_btags && njets() >= 9 && ht() > 80);

            case SignalRegion::sr31 : return (nbtags() == 0 && njets() >= 2 && ht() > 80);
            case SignalRegion::sr32 : return (nbtags() == 1 && njets() >= 2 && ht() > 80);
            case SignalRegion::sr33 : return (nbtags() == 2 && njets() >= 2 && ht() > 80);
            case SignalRegion::sr34 : return (nbtags() == 3 && njets() >= 2 && ht() > 80);
            case SignalRegion::sr35 : return (nbtags() == 4 && njets() >= 2 && ht() > 80);
            case SignalRegion::sr36 : return (nbtags() == 5 && njets() >= 2 && ht() > 80);
            case SignalRegion::sr37 : return (nbtags() == 6 && njets() >= 2 && ht() > 80);
            case SignalRegion::sr38 : return (nbtags() == 7 && njets() >= 2 && ht() > 80);

            case SignalRegion::sr39 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && (  0 < pt1 && pt1 <  20));
            case SignalRegion::sr40 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && ( 20 < pt1 && pt1 <  40));
            case SignalRegion::sr41 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && ( 40 < pt1 && pt1 <  60));
            case SignalRegion::sr42 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && ( 60 < pt1 && pt1 <  80));
            case SignalRegion::sr43 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && ( 80 < pt1 && pt1 < 100));
            case SignalRegion::sr44 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && (100 < pt1 && pt1 < 120));
            case SignalRegion::sr45 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && (120 < pt1 && pt1 < 140));
            case SignalRegion::sr46 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && (140 < pt1 && pt1 < 160));
            case SignalRegion::sr47 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && (160 < pt1 && pt1 < 180));
            case SignalRegion::sr48 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && (180 < pt1             ));

            case SignalRegion::sr49 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && (  0 < pt2 && pt2 <  20));
            case SignalRegion::sr50 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && ( 20 < pt2 && pt2 <  40));
            case SignalRegion::sr51 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && ( 40 < pt2 && pt2 <  60));
            case SignalRegion::sr52 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && ( 60 < pt2 && pt2 <  80));
            case SignalRegion::sr53 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && ( 80 < pt2 && pt2 < 100));
            case SignalRegion::sr54 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && (100 < pt2 && pt2 < 120));
            case SignalRegion::sr55 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && (120 < pt2 && pt2 < 140));
            case SignalRegion::sr56 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && (140 < pt2 && pt2 < 160));
            case SignalRegion::sr57 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && (160 < pt2 && pt2 < 180));
            case SignalRegion::sr58 : return (nbtags() >= num_btags && njets() >= 2 && ht() > 80 && (180 < pt2             ));

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
