#ifndef SAMESIGNTREE_H
#define SAMESIGNTREE_H

#include "at/Sample.h"
#include <vector> 
#include "Math/LorentzVector.h"
#include "at/DileptonHypType.h"
#include "DileptonTree.h"
#include "EventInfoTree.h"
#include "LooperTypes.h"

// forward declaration
class TTree;

// typedefs
typedef std::vector<LorentzVector> vecLorentzVector;
typedef std::vector<float> vecd;
typedef std::vector<int> veci;

struct SameSignTree : public DileptonTree
{
    struct Selection 
    {
        enum value_type
        {
            Lep1FullSelection = 1UL<<0,  	// lepton 1 passes the full analysis selection
            Lep1FakeSelection = 1UL<<1,  	// lepon 1 passes the FO selection
            Lep2FullSelection = 1UL<<2,  	// lepton 2 passes the full analysis selection
            Lep2FakeSelection = 1UL<<3,  	// lepton 2 passes the FO selection
            Lep3Pt5           = 1UL<<4,         // event has no third lepton with pt > 5 GeV
            Lep3Pt10          = 1UL<<5,         // event has no third lepton with pt > 10 GeV
            PassesExtraZVeto  = 1UL<<6,  	// hypothesis passes extra Z veto
            TwoJets           = 1UL<<7,  	// at least 2 jets passing selections
            ThreeJets         = 1UL<<8, 	// at least 3 jets passing selections
            ZeroBtags         = 1UL<<9, 	// 0 jet passing CVS medium working point
            Trigger           = 1UL<<10, 	// passes trigger (always true for MC)
            DijetMass         = 1UL<<11,        // di-jet mass < 120 GeV
            TauVeto           = 1UL<<12,        // no hadronic tau
            IsoTrackVeto      = 1UL<<13,        // no isolated track
            ZeeVeto           = 1UL<<14,        // veto ee events with 76 < M_ee < 106 GeV
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

    // method to tell whether it passes a selection
    bool PassSelection(const SameSignTree::Selection& sel) const;

    // set event level selection bit mask
    void SetBitMask ();

public:

    //
    // event level info
    //
    EventInfoTree event_info;
    uint64 selection;
    bool is_good_lumi;
    int charge_type;
    int njets;
    int nlbtags;
    int nmbtags;
    int ntbtags;
    int ttbar_bkdn;
    float vtxw;
    float mt;
    float mt2;
    float mt2j;
    float mt2j_up;
    float mt2j_dn;
    float mt2j_jer;
    float ht;
    float rho;
    float rho_iso;
    float sf_dileptrig;
    float sf_lepeff;
    bool trig_mm;
    bool trig_em;
    bool trig_ee;
    bool trig_mm_mu17_mu8;
    bool trig_ee_el17_el8_id_iso;
    bool trig_em_mu17_el8_id_iso;
    bool trig_em_mu8_el17_id_iso;

    //
    // for JES and JER sysetmatics
    //
    int njets_dn;
    int njets_up;
    int njets_jer;
    int nlbtags_dn;
    int nlbtags_up;
    int nlbtags_jer;
    int nlbtags_reweighted;
    int nlbtags_reweighted_dn;
    int nlbtags_reweighted_up;
    int nlbtags_reweighted_jer;
    int nlbtags_reweighted_jec_up;
    int nlbtags_reweighted_jec_dn;
    int nmbtags_dn;
    int nmbtags_up;
    int nmbtags_jer;
    int nmbtags_reweighted;
    int nmbtags_reweighted_dn;
    int nmbtags_reweighted_up;
    int nmbtags_reweighted_jer;
    int nmbtags_reweighted_jec_up;
    int nmbtags_reweighted_jec_dn;
    int ntbtags_dn;
    int ntbtags_up;
    int ntbtags_jer;
    int ntbtags_reweighted;
    int ntbtags_reweighted_dn;
    int ntbtags_reweighted_up;
    int ntbtags_reweighted_jer;
    int ntbtags_reweighted_jec_up;
    int ntbtags_reweighted_jec_dn;
    int nlbtags_pv_reweighted;
    int nlbtags_pv_reweighted_dn;
    int nlbtags_pv_reweighted_up;
    int nlbtags_pv_reweighted_jer;
    int nlbtags_pv_reweighted_jec_up;
    int nlbtags_pv_reweighted_jec_dn;
    int nmbtags_pv_dn;
    int nmbtags_pv_up;
    int nmbtags_pv_jer;
    int nmbtags_pv_reweighted;
    int nmbtags_pv_reweighted_dn;
    int nmbtags_pv_reweighted_up;
    int nmbtags_pv_reweighted_jer;
    int nmbtags_pv_reweighted_jec_up;
    int nmbtags_pv_reweighted_jec_dn;
    int ntbtags_pv_dn;
    int ntbtags_pv_up;
    int ntbtags_pv_jer;
    int ntbtags_pv_reweighted;
    int ntbtags_pv_reweighted_dn;
    int ntbtags_pv_reweighted_up;
    int ntbtags_pv_reweighted_jer;
    int ntbtags_pv_reweighted_jec_up;
    int ntbtags_pv_reweighted_jec_dn;
    float ht_dn;
    float ht_up;
    float ht_jer;
    float pfmet_dn;
    float pfmet_up;
    float pfmet_jer;
    float pfmet_phi_dn;
    float pfmet_phi_up;
    float pfmet_phi_jer;

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
    bool em_mufo;
    bool em_elfo;

    //
    // gen level info
    //
    bool is_gen_pp;
    bool is_gen_mm;
    int gen_nbtags; 
    int gen_njets; 
    float gen_ht;

    //
    // reco lepton 1 info
    //
    LorentzVector lep1_nearjet_p4;
    LorentzVector lep1_nearlep_p4;
    LorentzVector lep1_jj_p4;
    float lep1_wfr;
    float lep1_wflip;
    float lep1_nearjet_dr;
    float lep1_nearlep_dr;
    int lep1_nearlep_id;
    bool lep1_isFromH;

    //
    // reco lepton 2 info
    //
    LorentzVector lep2_nearjet_p4;
    LorentzVector lep2_nearlep_p4;
    LorentzVector lep2_jj_p4;
    float lep2_wfr;
    float lep2_wflip;
    float lep2_nearjet_dr;
    float lep2_nearlep_dr;
    int lep2_nearlep_id;
    bool lep2_isFromH;

    //
    // jet info
    //
    vecLorentzVector vjets_p4;
    vecLorentzVector vjets_p4_up;
    vecLorentzVector vjets_p4_dn;
    vecLorentzVector vjets_p4_jer;
    vecLorentzVector vjets_mc3p4;
    vecLorentzVector vgenjets_p4;
    std::vector<bool> vjets_lbtagged;
    std::vector<bool> vjets_mbtagged;
    std::vector<bool> vjets_tbtagged;
    std::vector<bool> vjets_matched_pv;
    std::vector<bool> vjets_matched_pv_up;
    std::vector<bool> vjets_matched_pv_dn;
    std::vector<bool> vjets_matched_pv_jer;
    std::vector<bool> vjets_qgdisc;
    std::vector<bool> vjets_qgdisc_up;
    std::vector<bool> vjets_qgdisc_dn;
    std::vector<bool> vjets_qgdisc_jer;
    vecLorentzVector vjets_nearjet_p4;
    vecd vjets_nearjet_dr;
    veci vjets_mcflavor_phys;
    veci vjets_mcflavor_algo;
    veci vjets_mcflavor_phys_up;
    veci vjets_mcflavor_algo_up;
    veci vjets_mcflavor_phys_dn;
    veci vjets_mcflavor_algo_dn;
    veci vjets_mcflavor_phys_jer;
    veci vjets_mcflavor_algo_jer;
    vecd vjets_bdisc;
    vecd vjets_bdisc_up;
    vecd vjets_bdisc_dn;
    vecd vjets_bdisc_jer;
    veci vjets_momid;
    veci vjets_mc3id;
    float jets_dr12;
    float dijet_mass;
    float dijet_mass_pv;
    LorentzVector jjl_p4;
    LorentzVector jjl_p4_up;
    LorentzVector jjl_p4_dn;
    LorentzVector jjl_p4_jer;

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
    // gen lep3 info
    //
    LorentzVector gen_lep3_p4;
    int gen_lep3_pdgid;
    
    //
    // gen dilep hyp info
    //
    LorentzVector gen_dilep_p4;
    at::DileptonHypType::value_type gen_dilep_type;
    float gen_dilep_mass;
    float gen_dilep_dphi;
    float gen_dilep_deta;
    float gen_dilep_dr;

    // isolated track vars
    float trkpt5;
    float mleptrk5;
    float trkreliso5;
    float trkpt10;
    float mleptrk10;
    float trkreliso10;

    float trkpt5loose;
    float trkreliso5loose;
    float trkpt10loose;
    float trkreliso10loose;

    //min pt cut on particles 
    //included in the isolation
    float trkpt10pt0p1;
    float trkreliso10pt0p1;
    float trkpt10pt0p2;
    float trkreliso10pt0p2;
    float trkpt10pt0p3;
    float trkreliso10pt0p3;
    float trkpt10pt0p4;
    float trkreliso10pt0p4;
    float trkpt10pt0p5;
    float trkreliso10pt0p5;
    float trkpt10pt0p6;
    float trkreliso10pt0p6;
    float trkpt10pt0p7;
    float trkreliso10pt0p7;
    float trkpt10pt0p8;
    float trkreliso10pt0p8;
    float trkpt10pt0p9;
    float trkreliso10pt0p9;
    float trkpt10pt1p0;
    float trkreliso10pt1p0;

    // extra pfcand vars 
    int pfcandid5;     
    int pfcandid10;     
    int pfcanddirid10;     
    int pfcandvetoid10;     
    int pfcandvetoLid10;     
    int pfcandidOS10;  
    int pfcandidOS10looseZ;  
    int pfcandid5looseZ;     

    float pfcandiso5;     
    float pfcandiso10;     
    float pfcanddiriso10;     
    float pfcandvetoiso10;     
    float pfcandvetoLiso10;     
    float pfcandisoOS10;     
    float pfcandisoOS10looseZ;     
    float pfcandiso5looseZ;     

    float pfcandpt5;
    float pfcandpt10;
    float pfcanddirpt10;
    float pfcandvetopt10;
    float pfcandvetoLpt10;
    float pfcandptOS10;
    float pfcandptOS10looseZ;
    float pfcandpt5looseZ;

    float pfcanddz5;
    float pfcanddz10;
    float pfcanddirdz10;
    float pfcandvetodz10;
    float pfcandvetoLdz10;
    float pfcanddzOS10;
    float pfcanddzOS10looseZ;
    float pfcanddz5looseZ;

    float pfcandmindrj5;
    float pfcandmindrj10;
    float pfcanddirmindrj10;
    float pfcandvetomindrj10;
    float pfcandvetoLmindrj10;

    float pfcandpt10pt0p1;
    float pfcandiso10pt0p1;
    float pfcandpt10pt0p2;
    float pfcandiso10pt0p2;
    float pfcandpt10pt0p3;
    float pfcandiso10pt0p3;
    float pfcandpt10pt0p4;
    float pfcandiso10pt0p4;
    float pfcandpt10pt0p5;
    float pfcandiso10pt0p5;
    float pfcandpt10pt0p6;
    float pfcandiso10pt0p6;
    float pfcandpt10pt0p7;
    float pfcandiso10pt0p7;
    float pfcandpt10pt0p8;
    float pfcandiso10pt0p8;
    float pfcandpt10pt0p9;
    float pfcandiso10pt0p9;
    float pfcandpt10pt1p0;
    float pfcandiso10pt1p0;

    LorentzVector  pfcand5;
    LorentzVector  pfcand10;
    LorentzVector  pfcanddir10;
    LorentzVector  pfcandveto10;
    LorentzVector  pfcandvetoL10;
    LorentzVector  pfcandOS10;
    LorentzVector  pfcandOS10looseZ;
    LorentzVector  pfcand5looseZ;

    int pfTau15_leadPtcandID;
    int pfTau_leadPtcandID;
    int pfTauLoose_leadPtcandID;

    LorentzVector pfTau15;
    LorentzVector pfTau15_leadPtcand;
    LorentzVector pfTau;
    LorentzVector pfTau_leadPtcand;
    LorentzVector pfTauLoose;
    LorentzVector pfTauLoose_leadPtcand;

    //
    // jet-vertex matching
    //
    vecd pfjets_beta;
    vecd pfjets_beta2;
    vecd pfjets_beta_0p1;
    vecd pfjets_beta_0p2;
    vecd pfjets_beta2_0p1;
    vecd pfjets_beta2_0p5;
    vecd pfjets_mvaPUid;
    vecd pfjets_mva5xPUid;
    vecd pfjets_up_mva5xPUid;
    vecd pfjets_dn_mva5xPUid;
    vecd pfjets_jer_mva5xPUid;
    vecd pfjets_mvaBeta;

    //
    // store info for third lepton (choose highest pt that passes loose ID, separated from hyp leptons by dR=0.1)
    //
    SingleLeptonTree lep3;

    //
    // add branches for convenience
    //
    bool passes_isotrk_veto;
    bool passes_tau_veto;
    int njets_pv_tight0;
    int njets_pv_tight0_up;
    int njets_pv_tight0_dn;
    int njets_pv_tight0_jer;
    int njets_pv_tight1;
    int njets_pv_tight2;

    //
    // extra branches for off-shell W
    //
    bool leptonic_offshell_w;
    bool hadronic_offshell_w;
};

#endif
