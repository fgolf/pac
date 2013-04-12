#include "SignalRegion.h"
#include "AnalysisType.h"
#include "EWKINO2012_SS.h"
#include <stdexcept>

// inclusive signal regions infos
// ---------------------------------------------------------------------------------------------- //

// high pT, inclusive
const ewkino::SignalRegionInfo s_SsSignalRegionInfos[] = 
{
    {
        // name
        "sr0",
        // title
        "baseline: # jets #geq 2, # btags #eq 0",
        // latex
        "$\\#jets\\geq2,\\# btags=0$"
    },
    { 
        // name
        "sr1",
        // title
        "sr1: # jets #geq 2, # btags #eq 0, 50 < M_{jj} < 110 GeV",
        // latex
        "$\\#jets\\geq2,\\# btags=0,\\ 50 \\lt M_{jj} \\lt 110 \\text{GeV}$"
    },
};

// check that the SignalRegionInfoArray is the same size as the enum
// fails at compile time if it does
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
#define STATIC_ASSERT(expr) typedef char my_static_assert[(expr) ? 1 : -1]
STATIC_ASSERT(ARRAY_SIZE(s_SsSignalRegionInfos)      == ewkino::SignalRegion::static_size);

namespace ewkino
{
    // wrapper function to get the SignalRegionInfo
    SignalRegion::value_type GetSignalRegionFromName
    (
        const std::string& signal_region_name,
        const std::string& analysis_type_name,
        const std::string& signal_region_type_name
        )
    {
        using namespace std;
        const AnalysisType::value_type analysis_type          = GetAnalysisTypeFromName(analysis_type_name); 
        const SignalRegionType::value_type signal_region_type = GetSignalRegionTypeFromName(signal_region_type_name); 
        SignalRegion::value_type signal_region                = SignalRegion::static_size;
        for (size_t i = 0; i != SignalRegion::static_size; i++)
        {
            if (analysis_type==AnalysisType::ss && signal_region_type==SignalRegionType::inclusive)
            {
                if (string(s_SsSignalRegionInfos[i].name) == signal_region_name)
                {
                    signal_region = static_cast<SignalRegion::value_type>(i);
                    break;
                }
            }
        }

        // throw if not found
        if (signal_region == SignalRegion::static_size)
        {
            throw std::domain_error(Form("ERROR: ewkino::GetSignalRegionFromName(): signal_region %s not found!", signal_region_name.c_str()));
        }

        return signal_region; 
    }

    // wrapper function to get the SignalRegionInfo
    SignalRegionInfo GetSignalRegionInfo
    (
        const SignalRegion::value_type& signal_region,
        const AnalysisType::value_type analysis_type,
        const SignalRegionType::value_type& signal_region_type
        )
    {
        if (analysis_type==AnalysisType::ss     && signal_region_type==SignalRegionType::inclusive) {return s_SsSignalRegionInfos[signal_region];}

        // if we get here, then the arguments were out of bounds
        throw std::domain_error("ERROR: ewkino::GetSignalRegionInfo(): arguments out of bounds!");
    }

    SignalRegionInfo GetSignalRegionInfo
    (
        const std::string& signal_region_name,
        const std::string& analysis_type_name,
        const std::string& signal_region_type_name
        )
    {
        const AnalysisType::value_type analysis_type          = GetAnalysisTypeFromName(analysis_type_name); 
        const SignalRegionType::value_type signal_region_type = GetSignalRegionTypeFromName(signal_region_type_name); 
        const SignalRegion::value_type signal_region          = GetSignalRegionFromName(signal_region_name, analysis_type_name, signal_region_type_name); 
        return GetSignalRegionInfo(signal_region, analysis_type, signal_region_type); 
    }

    // passes signal region
    bool PassesSignalRegion
    (
        const SignalRegion::value_type& signal_region,
        const AnalysisType::value_type& anal_type,
        const SignalRegionType::value_type& signal_region_type,
        const at::YieldType::value_type& jec_yield_type,
        const at::YieldType::value_type& btag_yield_type,
        const bool do_btag_sf
        )
    {
        switch(anal_type)
        {
        case AnalysisType::ss:
            if (max(ewkino_ss::lep1_pdgid(),ewkino_ss::lep2_pdgid()) < 20.0) return false;
            if (min(ewkino_ss::lep1_pdgid(),ewkino_ss::lep2_pdgid()) < 20.0) return false;
            break;
        default:
            return false;
        }

        // kinematic variables that define the signal region
        int njets   = -1;
        float ht    = -1;
        float met   = -1;
        int nbtags  = -1;

        // apply the btag scale factor
        switch(anal_type)
        {
        case AnalysisType::ss:
            if (not ewkino_ss::is_real_data() && do_btag_sf)
            {
                nbtags = ewkino_ss::nbtags_reweighted();
            }
            if (ewkino_ss::is_real_data())
            {
                // jet scale up/down
                switch(jec_yield_type)
                {
                case at::YieldType::up:
                    njets  = ewkino_ss::njets_up();
                    nbtags = ewkino_ss::nbtags_reweighted_jec_up();
                    ht     = ewkino_ss::ht_up();
                    met    = ewkino_ss::pfmet_up();
                    break;
                case at::YieldType::down:
                    njets  = ewkino_ss::njets_dn();
                    nbtags = ewkino_ss::nbtags_reweighted_jec_dn();
                    ht     = ewkino_ss::ht_dn();
                    met    = ewkino_ss::pfmet_dn();
                    break;
                case at::YieldType::base:
                    njets  = ewkino_ss::njets();
                    nbtags = (do_btag_sf ? ewkino_ss::nbtags_reweighted() : ewkino_ss::nbtags());
                    ht     = ewkino_ss::ht();
                    met    = ewkino_ss::pfmet();
                    break;
                default:
                    njets  = ewkino_ss::njets();
                    nbtags = (do_btag_sf ? ewkino_ss::nbtags_reweighted() : ewkino_ss::nbtags());
                    ht     = ewkino_ss::ht();
                    met    = ewkino_ss::pfmet();
                    break;
                }
            }
            if (not ewkino_ss::is_real_data())
            {
 
                // btag scale up/down
                // this will overide the nbtags setting above
                switch(btag_yield_type)
                {
                case at::YieldType::up:
                    nbtags = ewkino_ss::nbtags_reweighted_up();
                    break;
                case at::YieldType::down:
                    nbtags = ewkino_ss::nbtags_reweighted_dn();
                    break;
                case at::YieldType::base:
                    nbtags = (do_btag_sf ? ewkino_ss::nbtags_reweighted() : ewkino_ss::nbtags());
                    break;
                default:
                    nbtags = (do_btag_sf ? ewkino_ss::nbtags_reweighted() : ewkino_ss::nbtags());
                    break;
                }
            }
            break;
        default:
            return false;
        } // end anal_type switch

        // ss
        if (anal_type==AnalysisType::ss)
        {
            const bool baseline = (njets>=2 && nbtags==0);

            if (signal_region_type==SignalRegionType::inclusive)
            {
                switch (signal_region)
                {
                case SignalRegion::sr0 : return (baseline);
                case SignalRegion::sr1 : return (baseline && ewkino_ss::dijet_mass() > 50. && ewkino_ss::dijet_mass() < 110.);
                };
            }
            return false;
        }
        return false;
    }

    // set aliases for TTree
    void SetSignalRegionAliases(TTree& tree, const AnalysisType::value_type& anal_type)
    {

        // kinematic variable aliases
        tree.SetAlias("l1_id"  , "lep1_pdgid"                 ); 
        tree.SetAlias("l1_num" , "lep1_is_num"                ); 
        tree.SetAlias("l1_fo"  , "lep1_is_fo"                 ); 
        tree.SetAlias("l1_pt"  , "lep1_p4.pt()"               ); 
        tree.SetAlias("l1_eta" , "lep1_p4.eta()"              ); 
        tree.SetAlias("l1_aeta", "fabs(lep1_p4.eta())"        ); 
        tree.SetAlias("l1_d0"  , "fabs(lep1_d0)"              ); 
        tree.SetAlias("l1_dz"  , "fabs(lep1_dz)"              ); 
        tree.SetAlias("fr1"    , "lep1_wfr/(1.0-lep1_wfr)"    ); 
        tree.SetAlias("fl1"    , "lep1_wflip/(1.0-lep1_wflip)"); 

        tree.SetAlias("l2_id"  , "lep2_pdgid"                 ); 
        tree.SetAlias("l2_num" , "lep2_is_num"                ); 
        tree.SetAlias("l2_fo"  , "lep2_is_fo"                 ); 
        tree.SetAlias("l2_pt"  , "lep2_p4.pt()"               ); 
        tree.SetAlias("l2_eta" , "lep2_p4.eta()"              ); 
        tree.SetAlias("l2_aeta", "fabs(lep2_p4.eta())"        ); 
        tree.SetAlias("l2_d0"  , "fabs(lep2_d0)"              ); 
        tree.SetAlias("fr2"    , "lep1_wfr/(1.0-lep2_wfr)"    ); 
        tree.SetAlias("fl2"    , "lep2_wflip/(1.0-lep2_wflip)"); 
        tree.SetAlias("l2_dz"  , "fabs(lep2_dz)"              ); 

        tree.SetAlias("sfw", "l1_fo*fr1 + l2_fo*fr2");
        tree.SetAlias("dfw", "fr1*fr2");

        // lepton cuts
        switch (anal_type)
        {
        case AnalysisType::ss:
            tree.SetAlias("lep_pt", "lep1_p4.pt()>20 && lep2_p4.pt()>20");
            break;
            /*do nothing*/
            break;
        }
        tree.SetAlias("l1_d0_cut", "(l1_id==11 ? 0.01 : 0.005)"); 
        tree.SetAlias("l2_d0_cut", "(l2_id==11 ? 0.01 : 0.005)"); 
        tree.SetAlias("lep_d0", "((is_ss || is_os) && (l1_d0<l1_d0_cut) && (l2_d0_cut)) || ((is_sf) && (l1_num ? l1_d0<l1_d0_cut : l2_d0<l2_d0_cut)");

        // trigger
        switch (anal_type)
        {
        case AnalysisType::ss:
            tree.SetAlias("trig", "((em && trig_em) || (mm && trig_mm) || (ee && trig_ee))");
            break;
        case AnalysisType::static_size:
            /*do nothing*/
            break;
        }

        // inclusive
        switch (anal_type)
        {
        case AnalysisType::ss:
            tree.SetAlias("sr0" , "nbtags==0 && njets>=2"); 
            tree.SetAlias("sr1" , "nbtags==0 && njets>=2 && dijet_mass > 50. && dijet_mass < 110.");
            break;
        case AnalysisType::static_size:
            /*do nothing*/
            break;
        }

        // exclusive
        switch (anal_type)
        {
        case AnalysisType::ss:
            tree.SetAlias("sr0" , "nbtags==0 && njets>=2"); 
            tree.SetAlias("sr1" , "nbtags==0 && njets>=2 && dijet_mass > 50. && dijet_mass < 110."); 
            break;
        case AnalysisType::static_size:
            /*do nothing*/
            break;
        }
    }

    void SetSignalRegionAliases(TTree* tree, const AnalysisType::value_type& anal_type)
    {
        SetSignalRegionAliases(*tree, anal_type);
    }

    // Get the name of the SignalRegionTyp
    std::string GetSignalRegionTypeName(const SignalRegionType::value_type& signal_region_type)
    {
        switch(signal_region_type)
        {
        case SignalRegionType::inclusive: return "inclusive"; break;
        case SignalRegionType::exclusive: return "exclusive"; break;
        default: {/*do nothing*/}
        };
        throw std::domain_error("ERROR: ewkino::GetSignalRegionTypeName(): arguments out of bounds!");
    }

    // Get the SignalRegionType from a string
    SignalRegionType::value_type GetSignalRegionTypeFromName(const std::string& signal_region_type_name)
    {
        if (signal_region_type_name == "inclusive") {return SignalRegionType::inclusive;}
        if (signal_region_type_name == "exclusive") {return SignalRegionType::exclusive;}
        throw std::domain_error("ERROR: ewkino::GetSignalRegionTypeFromName(): arguments out of bounds!");
    }

} // namespace ewkino
