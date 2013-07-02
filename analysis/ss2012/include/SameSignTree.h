#ifndef SAMESIGNTREE_H
#define SAMESIGNTREE_H

#include "at/Sample.h"
#include <vector> 
#include "Math/LorentzVector.h"
#include "at/DileptonHypType.h"
#include "DileptonTree.h"
#include "EventInfoTree.h"
#include "JetInfoTree.h"
#include "LooperTypes.h"

// forward declaration
class TTree;

// typedefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef std::vector<LorentzVector> vecLorentzVector;
typedef std::vector<float> vecd;
typedef std::vector<int> veci;

struct SameSignTree : public DileptonTree
{
    struct Selection 
    {
        enum value_type
        {
            Baseline          = 1UL<<0,  	// passes baseline selection, to be defined
            GoodLumi          = 1UL<<1,  	// passes good run list
            BasicCleaning     = 1UL<<2,  	// passes cleaning_standardNovember2011()
            VertexMatched     = 1UL<<3,  	// leptons matched to vertex
            Lep1FullSelection = 1UL<<4,  	// lepton 1 passes the full analysis selection
            Lep1FakeSelection = 1UL<<5,  	// lepon 1 passes the FO selection
            Lep2FullSelection = 1UL<<6,  	// lepton 2 passes the full analysis selection
            Lep2FakeSelection = 1UL<<7,  	// lepton 2 passes the FO selection
            PassesExtraZVeto  = 1UL<<8,  	// hypothesis passes extra Z veto
            TwoJets           = 1UL<<9,  	// at least 2 jets passing selections
            TwoBtags          = 1UL<<10, 	// at least 2 btags passing selections
            ThreeBtags        = 1UL<<11, 	// at least 3 btags passing selections
            Trigger           = 1UL<<12, 	// passes trigger (always true for MC)
            SR0               = 1UL<<13, 	// passes signal region 0
            SR1               = 1UL<<14, 	// passes signal region 1
            SR2               = 1UL<<15, 	// passes signal region 2
            SR3               = 1UL<<16, 	// passes signal region 3
            SR4               = 1UL<<17, 	// passes signal region 4
            SR5               = 1UL<<18, 	// passes signal region 5
            SR6               = 1UL<<19, 	// passes signal region 6
            SR7               = 1UL<<20, 	// passes signal region 7
            SR8               = 1UL<<21,	// passes signal region 8
            static_size
        };
    };

    //
    // constructors and destructor
    //
    SameSignTree ();
    SameSignTree (const std::string &prefix);
    virtual ~SameSignTree () {}

    void Reset();
    void SetBranches(TTree& tree);
    void SetAliases(TTree& tree) const;

    // method to tell where it passes a selection
    bool PassSelection(const SameSignTree::Selection& sel) const;

public:

    //
    // event level info
    //
    EventInfoTree event_info;
    uint64 selection;
    int anal_type;
    bool is_good_lumi;
    int charge_type;
    int ttbar_bkdn;
    int higgs_bkdn;
    int higgs_decay;
    float vtxw;
    float mt;
    float rho;
    float rho_iso;
    float sf_dileptrig;
    float sf_dileptrig_hpt;
    float sf_dileptrig_lpt;
    float sf_dileptrig_vpt;
    float sf_dilepeff;
    bool trig_mm;
    bool trig_em;
    bool trig_ee;
    bool trig_hpt;
    bool trig_lpt;
    bool trig_lpt_isomu;
    bool trig_mm_mu17_mu8;
    bool trig_mm_dmu8_m8_pfht175;
    bool trig_mm_dmu8_m8_pfnopuht175;
    bool trig_mm_dreliso1p0mu5_m8_pfht175;
    bool trig_mm_dreliso1p0mu5_m8_pfnopuht175;
    bool trig_ee_el17_el8_id_iso;
    bool trig_ee_del8_id_m8_pfht175;
    bool trig_ee_del8_id_m8_pfnopuht175;
    bool trig_em_mu17_el8_id_iso;
    bool trig_em_mu8_el17_id_iso;
    bool trig_em_mu8_el8_id_m8_pfht175;
    bool trig_em_mu8_el8_id_m8_pfnopuht175;
    bool trig_em_riso1p0mu5_el8_id_m8_pfht175;
    bool trig_em_riso1p0mu5_el8_id_m8_pfnopuht175;

    //
    // sysetmatics (most of the JEC +/- are handled in the JetInfoTree)
    //
    int njets_jer;
    int nbtags_jer;
    int nbtags_reweighted_jer;
    float ht_jer;
    float pfmet_jec_dn;
    float pfmet_jec_up;
    float pfmet_phi_jec_dn;
    float pfmet_phi_jec_up;
    float pfmet_jer;
    float pfmet_jer_phi;
    float pfmet_uncl_up;
    float pfmet_uncl_dn;

    //
    // susy parameters
    //
    float sparm0;
    float sparm1;
    float sparm2;
    float sparm3;
    TString sparm0_name;
    TString sparm1_name;
    TString sparm2_name;
    TString sparm3_name;

    //
    // hyp level info
    //
    bool is_pp;
    bool is_mm;
    bool is_ss;
    bool is_sf;
    bool is_df;
    bool is_os;
    bool no_extraz;
    bool no_extrag;
    bool clean;
    bool hyp_good_vtx;
    bool presel;
    //bool ee;
    //bool mm;
    //bool em;
    bool em_mufo;
    bool em_elfo;

    //
    // gen level info
    //
    bool is_gen_pp;
    bool is_gen_mm;

    //
    // reco lepton 1 info
    //
    LorentzVector lep1_nearbjet_p4;
    LorentzVector lep1_nearjet_p4;
    LorentzVector lep1_nearlep_p4;
    float lep1_wfr;
    float lep1_wflip;
    float lep1_nearbjet_dr;
    float lep1_nearjet_dr;
    float lep1_nearlep_dr;
    int lep1_nearlep_id;

    //
    // reco lepton 2 info
    //
    LorentzVector lep2_nearbjet_p4;
    LorentzVector lep2_nearjet_p4;
    LorentzVector lep2_nearlep_p4;
    float lep2_wfr;
    float lep2_wflip;
    float lep2_nearbjet_dr;
    float lep2_nearjet_dr;
    float lep2_nearlep_dr;
    int lep2_nearlep_id;

    //
    // eff and scale factors
    //
    float sf_nbtag;
    float sf_nbtag3;
    float sf_unc_nbtag;
    float sf_unc_nbtag3;

    // 
    // new jet info
    // 
    JetInfoTree jet_info;
    JetInfoTree jet_info_up;
    JetInfoTree jet_info_dn;
    JetInfoTree jet_info_pt30;

    //
    // gen lep1 info
    //
    LorentzVector gen_lep1_p4;
    int gen_lep1_pdgid;
    
    //
    // gen lep2 info
    //
    LorentzVector gen_lep2_p4;
    int gen_lep2_pdgid;
    
    //
    // gen dilep hyp info
    //
    LorentzVector gen_dilep_p4;
    at::DileptonHypType::value_type gen_dilep_type;
    float gen_dilep_mass;
    float gen_dilep_dphi;
    float gen_dilep_deta;
    float gen_dilep_dr;

    //
    // store info for third lepton (choose highest pt, separated from hyp leptons by dR=0.1)
    //
    SingleLeptonTree lep3;
    float lep3_wfr;
    float lep3_wflip;
    bool passes_3lep_veto;

    //
    // tau info
    //
    int pfTau15_leadPtcandID;
    int pfTau_leadPtcandID;
    int pfTauLoose_leadPtcandID;
    LorentzVector pfTau15;
    LorentzVector pfTau15_leadPtcand;
    LorentzVector pfTau;
    LorentzVector pfTau_leadPtcand;
    LorentzVector pfTauLoose;
    LorentzVector pfTauLoose_leadPtcand;
    bool passes_tau_veto;

    // track iso veto 
    bool passes_isotrk_veto;
};

#endif
