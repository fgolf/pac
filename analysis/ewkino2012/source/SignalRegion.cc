#include "SignalRegion.h"
#include "AnalysisType.h"
#include "SystematicType.h"
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
        "SR1",
        // latex
        "SR1"
    },
    { 
        // name
        "sr2",
        // title
        "SR2",
        // latex
        "SR2"
    },
    { 
        // name
        "sr3",
        // title
        "SR3",
        // latex
        "SR3"
    },
    { 
        // name
        "sr4",
        // title
        "SR4",
        // latex
        "SR4"
    },
};

// check that the SignalRegionInfoArray is the same size as the enum
// fails at compile time if it does
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
#define STATIC_ASSERT(expr) typedef char my_static_assert[(expr) ? 1 : -1]
STATIC_ASSERT(ARRAY_SIZE(s_SsInclSignalRegionInfos)      == ewkino::SignalRegion::static_size);

namespace ewkino
{
    using namespace ewkino_ss;

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
        const float mt,
        const float mt2j,
        const float mljj,
        const int njets,
        const int nlbtags,
        const int ntbtags,
        const SignalRegion::value_type& signal_region,
        const AnalysisType::value_type& anal_type,
        const SignalRegionType::value_type& signal_region_type
    )
    {
        switch(anal_type)
        {
            case AnalysisType::ss:
                if (lep1_p4().pt() < 20.0) return false;
                if (lep2_p4().pt() < 20.0) return false;
                break;
            default:
                return false;
        }


        float max_ml3l = 0.;
        if (lep1_nearlep_dr() > -1)
        {
            LorentzVector tmp_p4 = lep1_p4() + lep1_nearlep_p4();
            max_ml3l = tmp_p4.mass();
        }
        if (lep2_nearlep_dr() > -1)
        {
            LorentzVector tmp_p4 = lep2_p4() + lep2_nearlep_p4();
            max_ml3l = max(tmp_p4.mass(), max_ml3l);
        }

        // SS WH
        if (anal_type==AnalysisType::ss)
        {
            const bool baseline      = (min(lep1_p4().pt(), lep2_p4().pt()) > 20.);
            const bool pass_sr0      = (baseline && (njets == 2 || njets == 3) && met > 40);
            const bool pass_sr1      = (pass_sr0 && mt > 110 && ntbtags == 0 && nlbtags < 2 && max_ml3l < 30 && passes_tau_veto() && rt::DeltaEta(lep1_p4(),lep2_p4()) < 1.6 && mt2j > 100);
            const bool pass_sr2      = (pass_sr1 && mljj < 120);
            const bool pass_sr3      = (pass_sr1 && mljj >= 120);
            const bool pass_sr4      = (pass_sr0 && mt > 110 && ntbtags == 0 && nlbtags < 2 && max_ml3l < 30 && passes_tau_veto() && rt::DeltaEta(lep1_p4(),lep2_p4()) < 1.6 && mljj < 120);
            
            if (signal_region_type==SignalRegionType::inclusive)
            {
                switch (signal_region)
                {
                case SignalRegion::sr0 : return (pass_sr0);
                case SignalRegion::sr1 : return (pass_sr1);
                case SignalRegion::sr2 : return (pass_sr2);
                case SignalRegion::sr3 : return (pass_sr3);
                case SignalRegion::sr4 : return (pass_sr4);
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
        // kinematic variables that define the signal region
        float met   = -999999;
        float mt    = -999999;
        float mt2j  = -999999;
        float mljj  = -999999;
        int nlbtags = -999999;
        int ntbtags = -999999;
        int njets   = -999999;
        ewkino::GetReweightedKinematicVariables(met, mt, mt2j, mljj, njets, nlbtags, ntbtags, do_beff_sf, syst_type, sample, is_fast_sim);

        // call main fucntion with this ht/met/njets/nbtags
        return PassesSignalRegion(met, mt, mt2j, mljj, njets, nlbtags, ntbtags, signal_region, anal_type, signal_region_type);
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
                tree.SetAlias("lep_eta", "abs(lep1_p4.eta())<2.4 && abs(lep2_p4.eta())<2.4");
                break;
            case AnalysisType::static_size:
                /*do nothing*/
                break;
        }
        tree.SetAlias("l1_d0_cut", "(l1_id==11 ? 0.01 : 0.005)"); 
        tree.SetAlias("l2_d0_cut", "(l2_id==11 ? 0.01 : 0.005)"); 
        tree.SetAlias("lep_d0", "((is_ss || is_os) && (l1_d0<l1_d0_cut) && (l2_d0_cut)) || ((is_sf) && (l1_num ? l1_d0<l1_d0_cut : l2_d0<l2_d0_cut)");

        tree.SetAlias("pass_zee_veto", "!(dilep_type==3 && dilep_mass>76. && dilep_mass<106.)");

        tree.SetAlias("min_jet_pt_over_mass", "min(vjets_p4.at(0).pt(),vjets_p4.at(1).pt())/dijet_mass");

        tree.SetAlias("max_ml3l_lep1","lep1_nearlep_dr > -1 ? sqrt(pow(lep1_p4.E()+lep1_nearlep_p4.E(),2) - pow(lep1_p4.pz()+lep1_nearlep_p4.pz(),2) - pow(lep1_p4.py()+lep1_nearlep_p4.py(),2) - pow(lep1_p4.px()+lep1_nearlep_p4.px(),2)) : -1");
        tree.SetAlias("max_ml3l_lep2","lep2_nearlep_dr > -1 ? sqrt(pow(lep2_p4.E()+lep2_nearlep_p4.E(),2) - pow(lep2_p4.pz()+lep2_nearlep_p4.pz(),2) - pow(lep2_p4.py()+lep2_nearlep_p4.py(),2) - pow(lep2_p4.px()+lep2_nearlep_p4.px(),2)) : -1");
        tree.SetAlias("max_ml3l", "max(max_ml3l_lep1,max_ml3l_lep2)");

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
                tree.SetAlias("sr0" , "lep_pt && (njets_pv_tight0==2 || njets_pv_tight0==3) && pfmet > 40"); 
                tree.SetAlias("sr1" , "sr0 && max(lep1_mt,lep2_mt) > 110 && nlbtags_pv_reweighted < 2 && ntbtags_pv_reweighted == 0 && passes_tau_veto && abs(lep1_p4.eta()-lep2_p4.eta()) < 1.6 && mt2j > 100 && max_ml3l < 30."); 
                tree.SetAlias("sr2" , "sr1 && jjl_p4.mass() < 120.");
                tree.SetAlias("sr3" , "sr1 && jjl_p4.mass() > 120.");
                tree.SetAlias("sr4" , "sr0 && max(lep1_mt,lep2_mt) > 110 && nlbtags_pv_reweighted < 2 && ntbtags_pv_reweighted == 0 && passes_tau_veto && abs(lep1_p4.eta()-lep2_p4.eta()) < 1.6 && max_ml3l < 30. && jjl_p4.mass() < 120."); 
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

    // match jet to PV
    bool passesMVAJetId(LorentzVector p4, float mva_value, int tightness)
    {
        if (tightness < 0 || tightness > 2)
        {
            std::cout << "ERROR : tightness should be 0, 1, or 2. " << std::endl;
            return false;
        }

        float fMVACut[3][4][4];

        /*
        // working points from full_53x_wp defined in 
        // http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/CMG/CMGTools/External/python/JetIdParams_cfi.py?revision=1.12&view=markup

        //Tight Id
        fMVACut[0][0][0] = -0.83; fMVACut[0][0][1] = -0.81; fMVACut[0][0][2] = -0.74; fMVACut[0][0][3] = -0.81;
        fMVACut[0][1][0] = -0.83; fMVACut[0][1][1] = -0.81; fMVACut[0][1][2] = -0.74; fMVACut[0][1][3] = -0.81;
        fMVACut[0][2][0] = -0.38; fMVACut[0][2][1] = -0.32; fMVACut[0][2][2] = -0.14; fMVACut[0][2][3] = -0.48;
        fMVACut[0][3][0] = -0.38; fMVACut[0][3][1] = -0.32; fMVACut[0][3][2] = -0.14; fMVACut[0][3][3] = -0.48;
        //Medium id
        fMVACut[1][0][0] = -0.83; fMVACut[1][0][1] = -0.92; fMVACut[1][0][2] = -0.90; fMVACut[1][0][3] = -0.92;
        fMVACut[1][1][0] = -0.83; fMVACut[1][1][1] = -0.92; fMVACut[1][1][2] = -0.90; fMVACut[1][1][3] = -0.92;
        fMVACut[1][2][0] = -0.40; fMVACut[1][2][1] = -0.49; fMVACut[1][2][2] = -0.50; fMVACut[1][2][3] = -0.65;
        fMVACut[1][3][0] = -0.40; fMVACut[1][3][1] = -0.49; fMVACut[1][3][2] = -0.50; fMVACut[1][3][3] = -0.65;
        //Loose Id 
        fMVACut[2][0][0] = -0.95; fMVACut[2][0][1] = -0.96; fMVACut[2][0][2] = -0.94; fMVACut[2][0][3] = -0.95;
        fMVACut[2][1][0] = -0.95; fMVACut[2][1][1] = -0.96; fMVACut[2][1][2] = -0.94; fMVACut[2][1][3] = -0.95;
        fMVACut[2][2][0] = -0.80; fMVACut[2][2][1] = -0.74; fMVACut[2][2][2] = -0.68; fMVACut[2][2][3] = -0.77;
        fMVACut[2][3][0] = -0.80; fMVACut[2][3][1] = -0.74; fMVACut[2][3][2] = -0.68; fMVACut[2][3][3] = -0.77;
        */

        // working points from full_5x_wp defined in 
        // http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/CMG/CMGTools/External/python/JetIdParams_cfi.py?revision=1.12&view=markup
        //Tight Id                                                                                                                                                                       
        fMVACut[0][0][0] = -0.47; fMVACut[0][0][1] = -0.92; fMVACut[0][0][2] = -0.92; fMVACut[0][0][3] = -0.94;
        fMVACut[0][1][0] = -0.47; fMVACut[0][1][1] = -0.92; fMVACut[0][1][2] = -0.92; fMVACut[0][1][3] = -0.94;
        fMVACut[0][2][0] = +0.32; fMVACut[0][2][1] = -0.49; fMVACut[0][2][2] = -0.61; fMVACut[0][2][3] = -0.74;
        fMVACut[0][3][0] = +0.32; fMVACut[0][3][1] = -0.49; fMVACut[0][3][2] = -0.61; fMVACut[0][3][3] = -0.74;
        //Medium id
        fMVACut[1][0][0] = -0.83; fMVACut[1][0][1] = -0.96; fMVACut[1][0][2] = -0.95; fMVACut[1][0][3] = -0.96;
        fMVACut[1][1][0] = -0.83; fMVACut[1][1][1] = -0.96; fMVACut[1][1][2] = -0.95; fMVACut[1][1][3] = -0.96;
        fMVACut[1][2][0] = -0.40; fMVACut[1][2][1] = -0.74; fMVACut[1][2][2] = -0.76; fMVACut[1][2][3] = -0.81;
        fMVACut[1][3][0] = -0.40; fMVACut[1][3][1] = -0.74; fMVACut[1][3][2] = -0.76; fMVACut[1][3][3] = -0.81;
        //Loose Id 
        fMVACut[2][0][0] = -0.95; fMVACut[2][0][1] = -0.97; fMVACut[2][0][2] = -0.97; fMVACut[2][0][3] = -0.97;
        fMVACut[2][1][0] = -0.95; fMVACut[2][1][1] = -0.97; fMVACut[2][1][2] = -0.97; fMVACut[2][1][3] = -0.97;
        fMVACut[2][2][0] = -0.80; fMVACut[2][2][1] = -0.85; fMVACut[2][2][2] = -0.84; fMVACut[2][2][3] = -0.85;
        fMVACut[2][3][0] = -0.80; fMVACut[2][3][1] = -0.85; fMVACut[2][3][2] = -0.84; fMVACut[2][3][3] = -0.85;


        // pT categorization
        int ptId = 0;
        if (p4.pt() > 10 && p4.pt() < 20) ptId = 1;
        if (p4.pt() > 20 && p4.pt() < 30) ptId = 2;
        if (p4.pt() > 30                ) ptId = 3;

        // eta categorization
        int etaId = 0;
        if (fabs(p4.eta()) > 2.5  && fabs(p4.eta()) < 2.75) etaId = 1;
        if (fabs(p4.eta()) > 2.75 && fabs(p4.eta()) < 3.0 ) etaId = 2;
        if (fabs(p4.eta()) > 3.0  && fabs(p4.eta()) < 5.0 ) etaId = 3;

        // return  
        if (mva_value > fMVACut[tightness][ptId][etaId]) return true;
        return false;
    }

    std::vector<LorentzVector> getMatchedJets(int tightness)
    {
        std::vector<LorentzVector> ret;
        for (unsigned int idx = 0; idx < vjets_p4().size(); idx++)
        {
            if (!passesMVAJetId(vjets_p4().at(idx), pfjets_mva5xPUid().at(idx), tightness));
            ret.push_back(vjets_p4().at(idx));                
        }

        return ret;
    }

    int nMatchedBtags(int mva_tightness, int btag_tightness)
    {
        int ret = 0;
        for (unsigned int idx = 0; idx < vjets_p4().size(); idx++)
        {
            if (!passesMVAJetId(vjets_p4().at(idx), pfjets_mva5xPUid().at(idx), mva_tightness));
            if (btag_tightness == 0 && vjets_bdisc().at(idx) > 0.244) ++ret;
            else if (btag_tightness == 1 && vjets_bdisc().at(idx) > 0.679) ++ret;
            else if (btag_tightness == 2 && vjets_bdisc().at(idx) > 0.898) ++ret;
        }

        return ret;
        
    }

} // Namespace ewkino
