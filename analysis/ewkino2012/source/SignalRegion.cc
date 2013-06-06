#include "SignalRegion.h"
#include "AnalysisType.h"
#include "SystematicType.h"
#include "EWKINO2012_SS.h"
#include <stdexcept>
#include "at/DileptonHypType.h"
#include "rt/RootTools.h"

// inclusive signal regions infos
// ---------------------------------------------------------------------------------------------- //

// SS, inclusive
const ewkino::SignalRegionInfo s_SsInclSignalRegionInfos[] = 
{
    {
        // name
        "sr0",
        // title
        "baseline",
        // latex
        "baseline"
    },
    { 
        // name
        "sr1",
        // title
        "sr1: baseline + iso track veto + tau veto + jet-PV matching",
        // latex
        "SR1"
    },
    { 
        // name
        "sr2",
        // title
        "sr2: sr1 + mjj < 120 GeV",
        // latex
        "SR1 + $M_{jj} < 120$ GeV"
    },
    { 
        // name
        "sr3",
        // title
        "sr3: sr2 + not 76 < mee < 106 GeV",
        // latex
        "SR2 + $M_{ee} < 76 || M_{ee} > 106$ GeV"
    },
    { 
        // name
        "sr4",
        // title
        "sr4: sr3 + njets==2",
        // latex
        "SR3 + njets==2"
    },
    { 
        // name
        "sr5",
        // title
        "sr5: sr3 + no loose btags",
        // latex
        "SR3 + no loose btags"
    },
    { 
        // name
        "sr6",
        // title
        "sr6: sr5 + HT < 200 GeV + met > 30 GeV",
        // latex
        "SR5 + $H_{T} < 200$ GeV + met $> 30$ GeV"
    },
    { 
        // name
        "sr7",
        // title
        "sr7: sr6 + no third muon",
        // latex
        "SR6 + no third muon"
    },
    { 
        // name
        "sr8",
        // title
        "sr8: sr7 + |#Delta#eta_{ll}| < 2.0",
        // latex
        "SR7 + $\\abs{\\Delta\\eta_{\\ell\\ell}} < 2.0$"
    },
    { 
        // name
        "sr9",
        // title
        "sr9: sr8 + max(pt1,pt2)>30 GeV",
        // latex
        "SR8 + max$(p^{l1}_{T},p^{l2}_{T}) > 30$ GeV"
    },
    { 
        // name
        "sr10",
        // title
        "sr10: sr9 + HT < 160 GeV",
        // latex
        "SR9 + $H_{T} < 160$ GeV"
    },
    { 
        // name
        "sr11",
        // title
        "sr11: sr10 + pfmet > 90 GeV",
        // latex
        "SR10 + $met > 90$ GeV"
    },
};

// check that the SignalRegionInfoArray is the same size as the enum
// fails at compile time if it does
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
#define STATIC_ASSERT(expr) typedef char my_static_assert[(expr) ? 1 : -1]
STATIC_ASSERT(ARRAY_SIZE(s_SsInclSignalRegionInfos)      == ewkino::SignalRegion::static_size);

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
                if (string(s_SsInclSignalRegionInfos[i].name) == signal_region_name)
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
        if (analysis_type==AnalysisType::ss && signal_region_type==SignalRegionType::inclusive) {return s_SsInclSignalRegionInfos[signal_region];}

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
            case AnalysisType::ss:
                if (l1_pt < 20.0) return false;
                if (l2_pt < 20.0) return false;
                break;
            default:
                return false;
        }

        // SS WH
        if (anal_type==AnalysisType::ss)
        {
            const bool baseline      = (ewkino_ss::nbtags()==0 && min(ewkino_ss::lep1_p4().pt(), ewkino_ss::lep2_p4().pt()) > 20.);
            const bool pass_zee_veto = (not (ewkino_ss::dilep_type() == at::DileptonHypType::EE && ewkino_ss::dilep_mass() > 76. && ewkino_ss::dilep_mass() < 106.));
            const bool pass_sr0      = (baseline && (ewkino_ss::njets()==2 || ewkino_ss::njets()==3));
            const bool pass_sr1      = (baseline && ewkino_ss::passes_isotrk_veto() && ewkino_ss::passes_tau_veto() && (ewkino_ss::njets_pv_tight0() == 2 || ewkino_ss::njets_pv_tight0()==3));
            const bool pass_sr2      = (pass_sr1 && ewkino_ss::dijet_mass() < 120.);
            const bool pass_sr3      = (pass_sr2 && pass_zee_veto);
            const bool pass_sr4      = (pass_sr3 && ewkino_ss::njets_pv_tight0()==2);
            const bool pass_sr5      = (pass_sr3 && ewkino_ss::nbtags_loose()==0);
            const bool pass_sr6      = (pass_sr5 && ewkino_ss::ht() < 200 && ewkino_ss::pfmet() > 30);
            const bool pass_sr7      = (pass_sr6 && not ((abs(ewkino_ss::lep3_pdgid())==13 && ewkino_ss::lep3_p4().pt()>5.) || (abs(ewkino_ss::lep3_pdgid())==11 && ewkino_ss::lep3_p4().pt()>10.)));
            const bool pass_sr8      = (pass_sr7 && (rt::DeltaEta(ewkino_ss::lep1_p4(), ewkino_ss::lep2_p4()) < 2.0));
            const bool pass_sr9      = (pass_sr8 && (ewkino_ss::lep1_p4().pt()>30. || ewkino_ss::lep2_p4().pt()>30.));
            const bool pass_sr10     = (pass_sr9 && ewkino_ss::ht() < 160);
            const bool pass_sr11     = (pass_sr10 && ewkino_ss::pfmet() > 90);

            if (signal_region_type==SignalRegionType::inclusive)
            {
                switch (signal_region)
                {
                case SignalRegion::sr0 : return (pass_sr0);
                case SignalRegion::sr1 : return (pass_sr1);
                case SignalRegion::sr2 : return (pass_sr2);
                case SignalRegion::sr3 : return (pass_sr3);
                case SignalRegion::sr4 : return (pass_sr4);
                case SignalRegion::sr5 : return (pass_sr5);
                case SignalRegion::sr6 : return (pass_sr6);
                case SignalRegion::sr7 : return (pass_sr7);
                case SignalRegion::sr8 : return (pass_sr8);
                case SignalRegion::sr9 : return (pass_sr9);
                case SignalRegion::sr10 : return (pass_sr10);
                case SignalRegion::sr11 : return (pass_sr11);
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
        const unsigned int l1_id = abs(ewkino_ss::lep1_pdgid());
        const unsigned int l2_id = abs(ewkino_ss::lep2_pdgid());
        const float l1_pt        = ewkino_ss::lep1_p4().pt();
        const float l2_pt        = ewkino_ss::lep2_p4().pt();

        // kinematic variables that define the signal region
        float met   = -999999;
        float ht    = -999999;
        int nbtags  = -999999;
        int njets   = -999999;
        ewkino::GetReweightedKinematicVariables(met, ht, njets, nbtags, do_beff_sf, syst_type, sample, is_fast_sim);

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

        tree.SetAlias("l3_id", "lep3_pdgid"  );
        tree.SetAlias("l3_pt", "lep3_p4.pt()");

        // truth matched
        tree.SetAlias("is_ss_mc3"   , "lep1_mc3id*lep2_mc3id>0"             );
        tree.SetAlias("lep_is_fromw", "lep1_is_fromw==1 && lep2_is_fromw==1");
        tree.SetAlias("mc_matched"  , "is_ss_mc3 && lep_is_fromw"           );

        // fake rates
        tree.SetAlias("sfw", "l1_fo*fr1 + l2_fo*fr2");
        tree.SetAlias("dfw", "fr1*fr2");

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
            case AnalysisType::ss:
                tree.SetAlias("lep_pt", "lep1_p4.pt()>20 && lep2_p4.pt()>20");
                break;
            case AnalysisType::static_size:
                /*do nothing*/
                break;
        }
        tree.SetAlias("l1_d0_cut", "(l1_id==11 ? 0.01 : 0.005)"); 
        tree.SetAlias("l2_d0_cut", "(l2_id==11 ? 0.01 : 0.005)"); 
        tree.SetAlias("lep_d0", "((is_ss || is_os) && (l1_d0<l1_d0_cut) && (l2_d0_cut)) || ((is_sf) && (l1_num ? l1_d0<l1_d0_cut : l2_d0<l2_d0_cut)");

        tree.SetAlias("pass_zee_veto", "!(dilep_type==3 && dilep_mass>76. && dilep_mass<106.)");

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
                tree.SetAlias("sr0" , "lep_pt && nbs==0 && (njets==2 || njets==3)"); 
                tree.SetAlias("sr1" , "lep_pt && nbs==0 && passes_isotrk_veto && passes_tau_veto && (njets_pv_tight0==2 || njets_pv_tight0==3)"); 
                tree.SetAlias("sr2" , "sr1 && dijet_mass<120.");
                tree.SetAlias("sr3" , "sr2 && pass_zee_veto");
                tree.SetAlias("sr4" , "sr3 && njets_pv_tight0==2");
                tree.SetAlias("sr5" , "sr3 && nbtags_loose==2");
                tree.SetAlias("sr6" , "sr5 && ht < 200 && pfmet > 30");
                tree.SetAlias("sr7" , "sr6 && !((abs(l3_id)==13) && l3_pt>5) && !((abs(l3_id)==11) && l3_pt>15)");
                tree.SetAlias("sr8" , "sr7 && abs(l1_eta-l2_eta) < 2.0");
                tree.SetAlias("sr9" , "sr8 && max(l1_pt,l2_pt)>30.");
                tree.SetAlias("sr10" , "sr9 && pfmet > 90");
                tree.SetAlias("sr11" , "sr10 && ht < 160");
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
