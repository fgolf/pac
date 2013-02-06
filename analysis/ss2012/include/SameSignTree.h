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
    bool is_good_lumi;
    int njets;
    int njets20;
    int njets30;
    int nbtags;
    int nbtags20;
    int nbtags30;
    int ttbar_bkdn;
    float vtxw;
    float mt;
    float ht;
    float ht20;
    float ht30;    
    float rho;
    float rho_iso;
    float sf_dileptrig;
    float sf_lepeff;
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
	bool met_filters; 

    //
    // for JES sysetmatics
    //
    int njets_dn;
    int njets_up;
    int nbtags_dn;
    int nbtags_up;
    float ht_dn;
    float ht_up;
    int njets20_dn;
    int njets20_up;
    int nbtags20_dn;
    int nbtags20_up;
    float ht20_dn;
    float ht20_up;
    int njets30_dn;
    int njets30_up;
    int nbtags30_dn;
    int nbtags30_up;
    float ht30_dn;
    float ht30_up;
    float pfmet_dn;
    float pfmet_up;
    float pfmet_phi_dn;
    float pfmet_phi_up;

    //
    // susy parameters
    //
    float sparm0;
    float sparm1;
    float sparm2;
    float sparm3;

    //
    // hyp level info
    //
    bool is_pp;
    bool is_mm;
    bool is_sf;
    bool is_df;
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
    vecLorentzVector vgenb_p4;
    bool is_gen_pp;
    bool is_gen_mm;
    int gen_nbtags; 
    int gen_njets; 
    float gen_ht;
    int gen_nleps;

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
    // jet info
    //
    vecLorentzVector vjets_p4;
    vecLorentzVector vjets_mc3p4;
    vecLorentzVector vgenjets_p4;
    vecLorentzVector vjets_nearjet_p4;
    std::vector<bool> vjets_btagged;
    float jets_dr12;
    vecd vjets_nearjet_dr;
    veci vjets_mcflavor_phys;
    veci vjets_mcflavor_algo;
    vecd vbjets_disc;
    veci vjets_momid;
    veci vjets_mc3id;

    //
    // bjet info
    //
    vecLorentzVector vbjets_p4;
    vecLorentzVector vbjets_mc3p4;
    vecLorentzVector vbjets_nearjet_p4;
    vecd vbjets_nearjet_dr;
    veci vbjets_mcflavor_phys;
    veci vbjets_mcflavor_algo;
    veci vbjets_mc3id;
    veci vbjets_momid;
    float bjets_dr12;

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
};

#endif
