#ifndef OSTREE_H
#define OSTREE_H

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

struct OSTree : public DileptonTree
{
    struct Selection 
    {
        enum value_type
        {
            Lep1LooseSelection = 1UL<<0,  	// lepton 1 passes the full analysis selection
            Lep1TightSelection = 1UL<<1,  	// lepon 1 passes the FO selection
            Lep2LooseSelection = 1UL<<2,  	// lepton 2 passes the full analysis selection
            Lep2TightSelection = 1UL<<3,  	// lepton 2 passes the FO selection
            Lep3Pt5            = 1UL<<4,        // event has no third lepton with pt > 5 GeV
            Lep3Pt10           = 1UL<<5,        // event has no third lepton with pt > 10 GeV
            Trigger            = 1UL<<6, 	// passes trigger (always true for MC)
            static_size
        };
    };

    //
    // constructors and destructor
    //
    OSTree ();
    OSTree (const std::string &prefix);
    virtual ~OSTree () {}

    void Reset();
    void SetBranches(TTree& tree);
    void SetAliases(TTree& tree) const;

    // method to tell whether it passes a selection
    bool PassSelection(const OSTree::Selection& sel) const;

    // set event level selection bit mask
    void SetBitMask ();

public:

    //
    // event level info
    //
    EventInfoTree event_info;
    uint64 selection;
    bool is_good_lumi;
    int njets;
    int nbtags_loose;
    int nbtags_medium;
    int nbtags_tight;
    int ttbar_bkdn;
    float vtxw;
    float mt2;
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
    // for JES sysetmatics
    //
    int njets_dn;
    int njets_up;
    int nbtags_dn;
    int nbtags_up;
    int nbtags_reweighted;
    int nbtags_reweighted_dn;
    int nbtags_reweighted_up;
    int nbtags_reweighted_jec_up;
    int nbtags_reweighted_jec_dn;
    float ht_dn;
    float ht_up;
    float pfmet_dn;
    float pfmet_up;
    float pfmet_phi_dn;
    float pfmet_phi_up;
    float pfmet_uncl_up;
    float pfmet_uncl_dn;

    //
    // for JER systematics
    //
    int njets_jer;
    int nbtags_jer;
    int nbtags_reweighted_jer;
    float ht_jer;
    float pfmet_jer;
    float pfmet_jer_phi;

    //
    // hyp level info
    //
    bool clean;
    bool hyp_good_vtx;
    bool presel;

    //
    // gen level info
    //
    int gen_nbtags; 
    int gen_njets; 
    float gen_ht;

    //
    // reco lepton 1 info
    //
    LorentzVector lep1_nearb_p4;
    LorentzVector lep1_nearlep_p4;
    float lep1_nearb_dr;
    float lep1_nearlep_dr;
    int lep1_nearlep_id;

    //
    // reco lepton 2 info
    //
    LorentzVector lep2_nearb_p4;
    LorentzVector lep2_nearlep_p4;
    float lep2_nearb_dr;
    float lep2_nearlep_dr;
    int lep2_nearlep_id;

    //
    // jet info
    //
    vecLorentzVector vjets_p4;
    vecLorentzVector vjets_p4_up;
    vecLorentzVector vjets_p4_dn;
    vecLorentzVector vjets_mc3p4;
    vecLorentzVector vgenjets_p4;
    vecLorentzVector vgenbs_p4;
    std::vector<bool> vjets_btagged_loose;
    std::vector<bool> vjets_btagged_loose_up;
    std::vector<bool> vjets_btagged_loose_dn;
    std::vector<bool> vjets_btagged_medium;
    std::vector<bool> vjets_btagged_medium_up;
    std::vector<bool> vjets_btagged_medium_dn;
    std::vector<bool> vjets_btagged_tight;
    std::vector<bool> vjets_btagged_tight_up;
    std::vector<bool> vjets_btagged_tight_dn;
    veci vjets_mcflavor_phys;
    veci vjets_mcflavor_algo;
    veci vjets_mcflavor_phys_up;
    veci vjets_mcflavor_algo_up;
    veci vjets_mcflavor_phys_dn;
    veci vjets_mcflavor_algo_dn;
    vecd vjets_bdisc;
    vecd vjets_bdisc_up;
    vecd vjets_bdisc_dn;
    veci vjets_momid;
    veci vjets_mc3id;

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
    vecd pfjets_mvaBeta;

    //
    // store info for third lepton (choose highest pt, separated from hyp leptons by dR=0.1)
    //
    SingleLeptonTree lep3;

    //
    // add branches for convenience
    //
    int njets_pv_tight0;
    int njets_pv_tight1;
    int njets_pv_tight2;
};

#endif
