#include "SystematicType.h"
#include "EWKINO2012_SS.h"
#include <string>
#include <stdexcept>
#include "TString.h" 
#include "rt/RootTools.h"
#include "at/MCBtagCount.h"
#include "at/YieldType.h"

namespace ewkino
{
    SystematicType::value_type GetSystematicTypeFromName(const std::string& syst_type_name)
    {
        const std::string st_name = rt::string_lower(syst_type_name);
        if      (syst_type_name == "none" ) {return SystematicType::None;   } 
        else if (syst_type_name == "jes+" ) {return SystematicType::JES_UP; } 
        else if (syst_type_name == "jes-" ) {return SystematicType::JES_DN; } 
        else if (syst_type_name == "jer"  ) {return SystematicType::JER;    } 
        else if (syst_type_name == "met+" ) {return SystematicType::MET_UP; } 
        else if (syst_type_name == "met-" ) {return SystematicType::MET_DN; } 
        else if (syst_type_name == "beff+") {return SystematicType::BEFF_UP;} 
        else if (syst_type_name == "beff-") {return SystematicType::BEFF_DN;} 
        else
        {   
            throw std::invalid_argument(Form("[ss::GetSystematicTypeFromName] ERROR: %s is invalid.", syst_type_name.c_str()));
        }
    }

    // function to return the appropriate related met, ht, # jets, and # btags based on the 
    // systematic flag
    void GetReweightedKinematicVariables
    (
        float& met,
        float& ht,
        int& njets,
        int& nlbtags,
        int& ntbtags,
        const bool do_beff_sf,
        const SystematicType::value_type syst_type,
        const at::Sample::value_type sample,
        const bool is_fast_sim
    )
    {
        if (not ewkino_ss::is_real_data())
        {
            switch (syst_type)
            {
                case SystematicType::None:
                    met    = ewkino_ss::pfmet();
                    ht     = ewkino_ss::ht();
                    njets  = ewkino_ss::njets();
                    nlbtags = (do_beff_sf ? ewkino_ss::nlbtags_reweighted() : ewkino_ss::nlbtags());  // reweighted # btags (random #)
                    ntbtags = (do_beff_sf ? ewkino_ss::ntbtags_reweighted() : ewkino_ss::ntbtags());  // reweighted # btags (random #)
                    break;
                case SystematicType::JES_UP: 
                    met    = ewkino_ss::pfmet_up();  
                    ht     = ewkino_ss::ht_up();
                    njets  = ewkino_ss::njets_up();
                    nlbtags = (do_beff_sf ? ewkino_ss::nlbtags_reweighted_jec_up() : ewkino_ss::nlbtags_up()); // reweighted # btags (random #) using JES+ jets
                    ntbtags = (do_beff_sf ? ewkino_ss::ntbtags_reweighted_jec_up() : ewkino_ss::ntbtags_up()); // reweighted # btags (random #) using JES+ jets
                    break;
                case SystematicType::JES_DN:
                    met    = ewkino_ss::pfmet_dn();
                    ht     = ewkino_ss::ht_dn();
                    njets  = ewkino_ss::njets_dn();
                    nlbtags = (do_beff_sf ? ewkino_ss::nlbtags_reweighted_jec_dn() : ewkino_ss::nlbtags_dn()); // reweighted # btags (random #) using JES- jets
                    ntbtags = (do_beff_sf ? ewkino_ss::ntbtags_reweighted_jec_dn() : ewkino_ss::ntbtags_dn()); // reweighted # btags (random #) using JES- jets
                    break;
                // case SystematicType::JER:
                //     met    = ewkino_ss::pfmet_jer();
                //     ht     = ewkino_ss::ht_jer();
                //     njets  = ewkino_ss::njets_jer();
                //     nbtags = (do_beff_sf ? ewkino_ss::nbtags_reweighted_jer() : ewkino_ss::nbtags_jer()); // reweighted # btags (random #) using JER jets
                //     break;
                // case SystematicType::MET_UP:
                //     met    = ewkino_ss::pfmet_uncl_up();  
                //     ht     = ewkino_ss::ht();
                //     njets  = ewkino_ss::njets();
                //     nbtags = (do_beff_sf ? ewkino_ss::nbtags_reweighted() : ewkino_ss::nbtags()); // reweighted # btags (random #)
                //     break;
                // case SystematicType::MET_DN:
                //     met    = ewkino_ss::pfmet_uncl_dn();  
                //     ht     = ewkino_ss::ht();
                //     njets  = ewkino_ss::njets();
                //     nbtags = (do_beff_sf ? ewkino_ss::nbtags_reweighted() : ewkino_ss::nbtags()); // reweighted # btags (random #)
                //     break;
                // case SystematicType::BEFF_UP:
                //     met    = ewkino_ss::pfmet();
                //     ht     = ewkino_ss::ht();
                //     njets  = ewkino_ss::njets();
                //     //nbtags = ewkino_ss::nbtags_reweighted_up(); // reweighted # btags (random #) scaling up B-tag efficiency
                //     nbtags = at::MCBtagCount(ewkino_ss::vjets_p4(), ewkino_ss::vjets_btagged(), ewkino_ss::vjets_mcflavor_algo(), sample, is_fast_sim, at::YieldType::up, ewkino_ss::evt());
                //     break;
                // case SystematicType::BEFF_DN:
                //     met    = ewkino_ss::pfmet();
                //     ht     = ewkino_ss::ht();
                //     njets  = ewkino_ss::njets();
                //     //nbtags = ewkino_ss::nbtags_reweighted_dn(); // reweighted # btags (random #) scaling down B-tag efficiency
                //     nbtags = at::MCBtagCount(ewkino_ss::vjets_p4(), ewkino_ss::vjets_btagged(), ewkino_ss::vjets_mcflavor_algo(), sample, is_fast_sim, at::YieldType::down, ewkino_ss::evt());
                //     break;
                default:
                    throw std::invalid_argument("[ss::GetReweightedKinematicVariables] Error: SystematicType invalid");
            }
        }
        else
        {
            met     = ewkino_ss::pfmet();
            ht      = ewkino_ss::ht();
            njets   = ewkino_ss::njets();
            nlbtags = ewkino_ss::nlbtags();
            ntbtags = ewkino_ss::ntbtags();
        }

        // done
        return;
    }
}
