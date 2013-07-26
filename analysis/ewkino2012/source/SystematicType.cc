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
        float& mt,
        float& mt2j,
        float& mljj,
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
            float mt_lep1 = 0.;
            float mt_lep2 = 0.;            

            switch (syst_type)
            {
                case SystematicType::None:
                    met     = ewkino_ss::pfmet();
                    mt      = std::max(ewkino_ss::lep1_mt(), ewkino_ss::lep2_mt());
                    mt2j    = ewkino_ss::mt2j();
                    mljj    = ewkino_ss::jjl_p4().mass();
                    njets   = ewkino_ss::njets_pv_tight0();
                    nlbtags = (do_beff_sf ? ewkino_ss::nlbtags_pv_reweighted() : ewkino_ss::nlbtags());  // reweighted # btags (random #)
                    ntbtags = (do_beff_sf ? ewkino_ss::ntbtags_pv_reweighted() : ewkino_ss::ntbtags());  // reweighted # btags (random #)
                    break;
                case SystematicType::JES_UP: 
                    met     = ewkino_ss::pfmet_up();
                    mt_lep1 = rt::Mt(ewkino_ss::lep1_p4(), ewkino_ss::pfmet_up(), ewkino_ss::pfmet_phi_up());
                    mt_lep2 = rt::Mt(ewkino_ss::lep2_p4(), ewkino_ss::pfmet_up(), ewkino_ss::pfmet_phi_up());
                    mt      = std::max(mt_lep1, mt_lep2);
                    mt2j    = ewkino_ss::mt2j_up();
                    mljj    = ewkino_ss::jjl_p4_up().mass();
                    njets   = ewkino_ss::njets_pv_tight0_up();
                    nlbtags = (do_beff_sf ? ewkino_ss::nlbtags_pv_reweighted_jec_up() : ewkino_ss::nlbtags_up()); // reweighted # btags (random #) using JES+ jets
                    ntbtags = (do_beff_sf ? ewkino_ss::ntbtags_pv_reweighted_jec_up() : ewkino_ss::ntbtags_up()); // reweighted # btags (random #) using JES+ jets
                    break;
                case SystematicType::JES_DN:
                    met     = ewkino_ss::pfmet_dn();
                    mt_lep1 = rt::Mt(ewkino_ss::lep1_p4(), ewkino_ss::pfmet_dn(), ewkino_ss::pfmet_phi_dn());
                    mt_lep2 = rt::Mt(ewkino_ss::lep2_p4(), ewkino_ss::pfmet_dn(), ewkino_ss::pfmet_phi_dn());
                    mt      = std::max(mt_lep1, mt_lep2);
                    mt2j    = ewkino_ss::mt2j_dn();
                    mljj    = ewkino_ss::jjl_p4_dn().mass();
                    njets   = ewkino_ss::njets_pv_tight0_dn();
                    nlbtags = (do_beff_sf ? ewkino_ss::nlbtags_pv_reweighted_jec_dn() : ewkino_ss::nlbtags_dn()); // reweighted # btags (random #) using JES- jets
                    ntbtags = (do_beff_sf ? ewkino_ss::ntbtags_pv_reweighted_jec_dn() : ewkino_ss::ntbtags_dn()); // reweighted # btags (random #) using JES- jets
                    break;
                case SystematicType::JER:
                    met     = ewkino_ss::pfmet_jer();
                    mt_lep1 = rt::Mt(ewkino_ss::lep1_p4(), ewkino_ss::pfmet_jer(), ewkino_ss::pfmet_phi_jer());
                    mt_lep2 = rt::Mt(ewkino_ss::lep2_p4(), ewkino_ss::pfmet_jer(), ewkino_ss::pfmet_phi_jer());
                    mt      = std::max(mt_lep1, mt_lep2);
                    mt2j    = ewkino_ss::mt2j_jer();
                    mljj    = ewkino_ss::jjl_p4_jer().mass();
                    njets   = ewkino_ss::njets_pv_tight0_jer();
                    nlbtags = (do_beff_sf ? ewkino_ss::nlbtags_pv_reweighted_jer() : ewkino_ss::nlbtags_jer()); // reweighted # btags (random #) using JER jets
                    ntbtags = (do_beff_sf ? ewkino_ss::ntbtags_pv_reweighted_jer() : ewkino_ss::ntbtags_jer()); // reweighted # btags (random #) using JER jets
                    break;
                case SystematicType::BEFF_UP:
                    met     = ewkino_ss::pfmet();
                    mt      = std::max(ewkino_ss::lep1_mt(), ewkino_ss::lep2_mt());
                    mt2j    = ewkino_ss::mt2j();
                    mljj    = ewkino_ss::jjl_p4().mass();
                    njets   = ewkino_ss::njets();
                    nlbtags = ewkino_ss::nlbtags_pv_reweighted_up(); // reweighted # btags (random #) scaling up B-tag efficiency
                    ntbtags = ewkino_ss::ntbtags_pv_reweighted_up(); // reweighted # btags (random #) scaling up B-tag efficiency
                    break;
                case SystematicType::BEFF_DN:
                    met     = ewkino_ss::pfmet();
                    mt      = std::max(ewkino_ss::lep1_mt(), ewkino_ss::lep2_mt());
                    mt2j    = ewkino_ss::mt2j();
                    mljj    = ewkino_ss::jjl_p4().mass();
                    njets   = ewkino_ss::njets();
                    nlbtags = ewkino_ss::nlbtags_pv_reweighted_dn(); // reweighted # btags (random #) scaling down B-tag efficiency
                    ntbtags = ewkino_ss::ntbtags_pv_reweighted_dn(); // reweighted # btags (random #) scaling down B-tag efficiency
                    break;
                default:
                    throw std::invalid_argument("[ss::GetReweightedKinematicVariables] Error: SystematicType invalid");
            }
        }
        else
        {
            met     = ewkino_ss::pfmet();
            mt      = std::max(ewkino_ss::lep1_mt(), ewkino_ss::lep2_mt());
            mt2j    = ewkino_ss::mt2j();
            mljj    = ewkino_ss::jjl_p4().mass();
            njets   = ewkino_ss::njets_pv_tight0();
            int tmp_nlbtags = 0;
            int tmp_ntbtags = 0;
            for (size_t idx = 0; idx < ewkino_ss::vjets_p4().size(); idx++)
            {
                if (!ewkino_ss::vjets_matched_pv().at(idx)) continue;
                if (ewkino_ss::vjets_lbtagged().at(idx)) ++tmp_nlbtags;
                if (ewkino_ss::vjets_tbtagged().at(idx)) ++tmp_ntbtags;
            }
            nlbtags = tmp_nlbtags;
            ntbtags = tmp_ntbtags;
        }

        // done
        return;
    }
}
