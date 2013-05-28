#include "SignalRegion.h"
#include "AnalysisType.h"
#include "SystematicType.h"
#include "RPVSTOP2012_OS.h"
#include <stdexcept>
#include "at/DileptonHypType.h"

// inclusive signal regions infos
// ---------------------------------------------------------------------------------------------- //

// inclusive
const rpv_stop::SignalRegionInfo s_OsInclSignalRegionInfos[] = 
{
    {
        // name
        "sr0",
        // title
        "baseline",
        // latex
        "baseline"
    },
};

// check that the SignalRegionInfoArray is the same size as the enum
// fails at compile time if it does
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
#define STATIC_ASSERT(expr) typedef char my_static_assert[(expr) ? 1 : -1]
STATIC_ASSERT(ARRAY_SIZE(s_OsInclSignalRegionInfos)      == rpv_stop::SignalRegion::static_size);

namespace rpv_stop
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
            if (analysis_type==AnalysisType::mmbb && signal_region_type==SignalRegionType::inclusive)
            {
                if (string(s_OsInclSignalRegionInfos[i].name) == signal_region_name)
                {
                    signal_region = static_cast<SignalRegion::value_type>(i);
                    break;
                }
            }
        }

        // throw if not found
        if (signal_region == SignalRegion::static_size)
        {
            throw std::domain_error(Form("ERROR: rpv_stop::GetSignalRegionFromName(): signal_region %s not found!", signal_region_name.c_str()));
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
        if (analysis_type==AnalysisType::mmbb && signal_region_type==SignalRegionType::inclusive) {return s_OsInclSignalRegionInfos[signal_region];}

        // if we get here, then the arguments were out of bounds
        throw std::domain_error("ERROR: rpv_stop::GetSignalRegionInfo(): arguments out of bounds!");
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
        const float met,
        const float ht,
        const int njets,
        const int nbtags,
        const float l1_pt,
        const float l2_pt,
        const int l1_id,
        const int l2_id,
        const SignalRegion::value_type& signal_region,
        const AnalysisType::value_type& anal_type,
        const SignalRegionType::value_type& signal_region_type
    )
    {
        switch(anal_type)
        {
            case AnalysisType::mmbb:
                if (l1_pt < 20.0) return false;
                if (l2_pt < 20.0) return false;
                break;
            default:
                return false;
        }

        // SS WH
        if (anal_type==AnalysisType::mmbb)
        {
            const bool baseline = true;

            if (signal_region_type==SignalRegionType::inclusive)
            {
                switch (signal_region)
                {
                case SignalRegion::sr0 : return (baseline);
                };
            }

            return false;
        }
        
        return false;
    }

    // passes signal region
    bool PassesSignalRegion
    (
        const SignalRegion::value_type& signal_region,
        const AnalysisType::value_type& anal_type,
        const SignalRegionType::value_type& signal_region_type,
        const bool do_beff_sf,
        const SystematicType::value_type& syst_type,
        const at::Sample::value_type sample,
        const bool is_fast_sim
    )
    {
        // lepton pt cuts
        const unsigned int l1_id = abs(rpvstop_os::lep1_pdgid());
        const unsigned int l2_id = abs(rpvstop_os::lep2_pdgid());
        const float l1_pt        = rpvstop_os::lep1_p4().pt();
        const float l2_pt        = rpvstop_os::lep2_p4().pt();

        // kinematic variables that define the signal region
        float met   = -999999;
        float ht    = -999999;
        int nbtags  = -999999;
        int njets   = -999999;
        rpv_stop::GetReweightedKinematicVariables(met, ht, njets, nbtags, do_beff_sf, syst_type, sample, is_fast_sim);

        // call main fucntion with this ht/met/njets/nbtags
        return PassesSignalRegion(met, ht, njets, nbtags, l1_pt, l2_pt, l1_id, l2_id, signal_region, anal_type, signal_region_type);
    }

    // set aliases for TTree
    void SetSignalRegionAliases(TTree& tree, const AnalysisType::value_type& anal_type, const bool do_btag_sf)
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

        tree.SetAlias("l2_id"  , "lep2_pdgid"                 ); 
        tree.SetAlias("l2_num" , "lep2_is_num"                ); 
        tree.SetAlias("l2_fo"  , "lep2_is_fo"                 ); 
        tree.SetAlias("l2_pt"  , "lep2_p4.pt()"               ); 
        tree.SetAlias("l2_eta" , "lep2_p4.eta()"              ); 
        tree.SetAlias("l2_aeta", "fabs(lep2_p4.eta())"        ); 
        tree.SetAlias("l2_d0"  , "fabs(lep2_d0)"              ); 
        tree.SetAlias("l2_dz"  , "fabs(lep2_dz)"              ); 

        // truth matched
        tree.SetAlias("lep_is_fromw", "lep1_is_fromw==1 && lep2_is_fromw==1");

        // scale factors
        tree.SetAlias("sf", "sf_dileptrig*sf_lepeff");

        // do btag scale factor
        if (do_btag_sf)
        {
            tree.SetAlias("nbs", "nbtags_reweighted");
        }
        else
        {
            tree.SetAlias("nbs", "nbtags");
        }

        // lepton cuts
        switch (anal_type)
        {
            case AnalysisType::mmbb:
                tree.SetAlias("lep_pt", "lep1_p4.pt()>20 && lep2_p4.pt()>20");
                break;
            case AnalysisType::static_size:
                /*do nothing*/
                break;
        }
        tree.SetAlias("l1_d0_cut", "(l1_id==11 ? 0.01 : 0.005)"); 
        tree.SetAlias("l2_d0_cut", "(l2_id==11 ? 0.01 : 0.005)"); 
        tree.SetAlias("lep_d0", "((is_ss || is_os) && (l1_d0<l1_d0_cut) && (l2_d0_cut)) || ((is_sf) && (l1_num ? l1_d0<l1_d0_cut : l2_d0<l2_d0_cut)");

        // trigger
        switch (anal_type)
        {
            case AnalysisType::mmbb:
                tree.SetAlias("trig", "((em && trig_em) || (mm && trig_mm) || (ee && trig_ee))");
                break;
            case AnalysisType::static_size:
                /*do nothing*/
                break;
        }

        // inclusive
        switch (anal_type)
        {
            case AnalysisType::mmbb:
                tree.SetAlias("sr0" , "lep_pt"); 
                break;
            case AnalysisType::static_size:
                /*do nothing*/
                break;
        }

        // exclusive
        switch (anal_type)
        {
            case AnalysisType::static_size:
                /*do nothing*/
                break;
        }
    }

    void SetSignalRegionAliases(TTree* tree, const AnalysisType::value_type& anal_type, const bool do_btag_sf)
    {
        SetSignalRegionAliases(*tree, anal_type, do_btag_sf);
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
        throw std::domain_error("ERROR: rpv_stop::GetSignalRegionTypeName(): arguments out of bounds!");
    }

    // Get the SignalRegionType from a string
    SignalRegionType::value_type GetSignalRegionTypeFromName(const std::string& signal_region_type_name)
    {
        if (signal_region_type_name == "inclusive") {return SignalRegionType::inclusive;}
        if (signal_region_type_name == "exclusive") {return SignalRegionType::exclusive;}
        throw std::domain_error("ERROR: rpv_stop::GetSignalRegionTypeFromName(): arguments out of bounds!");
    }

} // namespace ewkino
