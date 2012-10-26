#ifndef TRILEPTONZTREE_H
#define TRILEPTONZTREE_H

#include "at/Sample.h"
#include <vector> 
#include "Math/LorentzVector.h"
#include "at/DileptonHypType.h"
#include "DileptonTree.h"
#include "EventInfoTree.h"
#include "LooperTypes.h"
#include "EventTypes.h"

// forward declaration
class TTree;

// typedefs
typedef std::vector<LorentzVector> vecLorentzVector;
typedef std::vector<float> vecd;

struct TrileptonZTree
{
    struct Selection 
    {
        enum value_type
        {
            Baseline             = 1UL<<0,  	// passes baseline selection, to be defined
            GoodLumi             = 1UL<<1,  	// passes good run list
            BasicCleaning        = 1UL<<2,  	// passes cleaning_standardNovember2011()
            VertexMatched        = 1UL<<3,  	// leptons matched to vertex
            Lep1FullSelection    = 1UL<<4,  	// lepton 1 passes the full analysis selection
            Lep1FakeSelection    = 1UL<<5,  	// lepton 1 passes the FO selection
            Lep2FullSelection    = 1UL<<6,  	// lepton 2 passes the full analysis selection
            Lep2FakeSelection    = 1UL<<7,  	// lepton 2 passes the FO selection
            Lep3FullSelection    = 1UL<<8,      // lepton 3 passes the full analysis selection
            Lep3FakeSelection    = 1UL<<9,      // lepton 3 passes the full analysis selection
            FourJets             = 1UL<<11,  	// at least 4 jets passing selections
            OneLooseBtag         = 1UL<<11,     // at least 1 btag passing loose selections
            OneTightBtag         = 1UL<<11,     // at least 1 btag passing tight selections
            TwoLooseBtags        = 1UL<<12, 	// at least 2 btags passing loose selections
            TwoTightBtags        = 1UL<<12, 	// at least 2 btags passing tight selections
            OneLooseOneTightBtag = 1UL<<12, 	// at least 1 btag passing loose selections and 1 passing tight selections
            Trigger              = 1UL<<14, 	// passes trigger (always true for MC)
            SYNC                 = 1UL<<15, 	// sync selection
            PRESEL               = 1UL<<16,     // pre-selection
            SR0                  = 1UL<<17,     // signal selection
            static_size
        };
    };

    struct LeptonType
    {
        enum value_type
        {
            TRIGGER,
            LOOSE_DENOM,
            TIGHT_DENOM,
            LOOSE_NUM,
            TIGHT_NUM,
            LOOSE_MVA_NUM,
            TIGHT_MVA_NUM,
            static_size
        };
    };

    //
    // constructors and destructor
    //
    TrileptonZTree ();
    TrileptonZTree (const std::string &prefix);
    virtual ~TrileptonZTree () {}

    void Reset();
    void SetBranches(TTree& tree);
    void SetAliases(TTree& tree) const;

    // method to tell where it passes a selection
    bool PassSelection(const TrileptonZTree::Selection& sel) const;

private:

    std::string prefix_;

public:
    //
    // let's get the leptons first
    //
    EventInfoTree event_info;
    DileptonTree dilep;
    SingleLeptonTree lep3;

    //
    // event level info
    //
    bool clean;
    uint64 selection;
    bool is_good_lumi;
    int njets30;
    int njets15;
    int nbtags_loose;
    int nbtags_tight;
    float vtxw;
    float ht;
    float rho;
    float rho_iso;
    float sf_dileptrig;
    float sf_lepeff;
    bool trig_mm;
    bool trig_em;
    bool trig_ee;
    ttv2012::EventType::value_type event_type;

    //
    // for JES sysetmatics
    //
    int njets30_dn;
    int njets30_up;
    int njets15_dn;
    int njets15_up;
    int nbtags_loose_dn;
    int nbtags_loose_up;
    int nbtags_tight_dn;
    int nbtags_tight_up;
    float ht_dn;
    float ht_up;
    float pfmet_dn;
    float pfmet_up;
    float pfmet_phi_dn;
    float pfmet_phi_up;

    //
    // Z hyp level info
    //
    // for now we select our trilepton events
    // as a dilepton Z candidate (OS, SF)
    // plus a 3rd lepton
    //
    // all of the info we need for the Z candidate
    // is already stored in the dilepton tree
    //

    //
    // reco lepton 1 info
    //
    LorentzVector lep1_nearbjet_p4;
    LorentzVector lep1_nearjet_p4;
    LorentzVector lep1_nearlep_p4;
    float lep1_nearbjet_dr;
    float lep1_nearjet_dr;
    float lep1_nearlep_dr;
    float lep1_wfr;
    float lep1_ele_mva_trig;
    float lep1_ele_mva_nontrig;
    int lep1_nearlep_id;
    int lep1_id_bitmask;

    //
    // reco lepton 2 info
    //
    LorentzVector lep2_nearbjet_p4;
    LorentzVector lep2_nearjet_p4;
    LorentzVector lep2_nearlep_p4;
    float lep2_nearbjet_dr;
    float lep2_nearjet_dr;
    float lep2_nearlep_dr;
    float lep2_wfr;
    float lep2_ele_mva_trig;
    float lep2_ele_mva_nontrig;
    int lep2_nearlep_id;
    int lep2_id_bitmask;

    //
    // 3rd lepton candidate
    // i.e. W lepton candidate
    //

    //
    // reco lepton 3 info
    //
    LorentzVector lep3_nearbjet_p4;
    LorentzVector lep3_nearjet_p4;
    LorentzVector lep3_nearlep_p4;
    float lep3_nearbjet_dr;
    float lep3_nearjet_dr;
    float lep3_nearlep_dr;
    float lep3_wfr;
    float lep3_ele_mva_trig;
    float lep3_ele_mva_nontrig;
    int lep3_nearlep_id;
    int lep3_id_bitmask;

    //
    // gen level info
    //
    vecLorentzVector vgenb_p4;
    int gen_nbtags; 
    int gen_njets; 
    float gen_ht;
    int gen_nleps;

    //
    // eff and scale factors
    //
    float sf_nbtag;
    float sf_unc_nbtag;
    float sf_nbtag2;
    float sf_unc_nbtag2;

    //
    // jet info
    //
    vecLorentzVector vjets_p4;
    vecLorentzVector vgenjets_p4;
    vecd vbjets_disc;

    //
    // bjet info
    //
    vecLorentzVector vbjets_p4;
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
    // gen lep3 info
    //
    LorentzVector gen_lep3_p4;
    int gen_lep3_pdgid;

    //
    // dilep gen info
    //
    LorentzVector gen_dilep_p4;
    at::DileptonHypType::value_type gen_dilep_type;
    float gen_dilep_mass;
    float gen_dilep_dphi;
    float gen_dilep_deta;
    float gen_dilep_dr;
    bool is_gen_z;   

    //
    // 3rd lep gen info
    //
    float gen_mt;
    bool is_gen_w;
};

#endif
