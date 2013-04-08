#include "SystematicType.h"
#include "SSB2012.h"
#include "rt/RootTools.h"
#include <string>
#include <stdexcept>
#include "TString.h" 

namespace ss
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
        int& nbtags,
        const bool do_beff_sf,
        const SystematicType::value_type syst_type
    )
    {
        if (not ssb::is_real_data())
        {
            switch (syst_type)
            {
                case SystematicType::None:
                    met    = ssb::pfmet();
                    ht     = ssb::ht();
                    njets  = ssb::njets();
                    nbtags = (do_beff_sf ? ssb::nbtags_reweighted() : ssb::nbtags());  // reweighted # btags (random #)
                    break;
                case SystematicType::JES_UP: 
                    met    = ssb::pfmet_up();  
                    ht     = ssb::ht_up();
                    njets  = ssb::njets_up();
                    nbtags = (do_beff_sf ? ssb::nbtags_reweighted_jec_up() : ssb::nbtags_up()); // reweighted # btags (random #) using JES+ jets
                    break;
                case SystematicType::JES_DN:
                    met    = ssb::pfmet_dn();
                    ht     = ssb::ht_dn();
                    njets  = ssb::njets_dn();
                    nbtags = (do_beff_sf ? ssb::nbtags_reweighted_jec_dn() : ssb::nbtags_dn()); // reweighted # btags (random #) using JES- jets
                    break;
                case SystematicType::JER:
                    met    = ssb::pfmet_jer();
                    ht     = ssb::ht_jer();
                    njets  = ssb::njets_jer();
                    nbtags = (do_beff_sf ? ssb::nbtags_reweighted_jer() : ssb::nbtags_jer()); // reweighted # btags (random #) using JER jets
                    break;
                case SystematicType::MET_UP:
                    met    = ssb::pfmet_uncl_up();  
                    ht     = ssb::ht();
                    njets  = ssb::njets();
                    nbtags = (do_beff_sf ? ssb::nbtags_reweighted() : ssb::nbtags()); // reweighted # btags (random #)
                    break;
                case SystematicType::MET_DN:
                    met    = ssb::pfmet_uncl_dn();  
                    ht     = ssb::ht();
                    njets  = ssb::njets();
                    nbtags = (do_beff_sf ? ssb::nbtags_reweighted() : ssb::nbtags()); // reweighted # btags (random #)
                    break;
                case SystematicType::BEFF_UP:
                    met    = ssb::pfmet();
                    ht     = ssb::ht();
                    njets  = ssb::njets();
                    nbtags = ssb::nbtags_reweighted_up(); // reweighted # btags (random #) scaling up B-tag efficiency
                    break;
                case SystematicType::BEFF_DN:
                    met    = ssb::pfmet();
                    ht     = ssb::ht();
                    njets  = ssb::njets();
                    nbtags = ssb::nbtags_reweighted_dn(); // reweighted # btags (random #) scaling down B-tag efficiency
                    break;
                default:
                    throw std::invalid_argument("[ss::GetReweightedKinematicVariables] Error: SystematicType invalid");
            }
        }
        else
        {
            met    = ssb::pfmet();
            ht     = ssb::ht();
            njets  = ssb::njets();
            nbtags = ssb::nbtags();
        }

        // done
        return;
    }
}
