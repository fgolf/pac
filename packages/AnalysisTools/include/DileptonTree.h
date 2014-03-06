#ifndef DILEPTONTREE_H
#define DILEPTONTREE_H

#include <string>
#include "Math/LorentzVector.h"
#include "SingleLeptonTree.h"
#include "at/DileptonHypType.h"

class DileptonTree
{
public:
    DileptonTree ();
    DileptonTree (const std::string &prefix);
    virtual ~DileptonTree () {}

    // enums 
    struct Fiduciality 
    {
        enum value_type
        {
            BB,  // both leptons are barrel
            BE,  // one lepton barrel, one endcap 
            EE,  // both leptons are endcap 
            static_size
        };
    };

    void Reset ();
    void SetBranches (TTree &tree);
    void SetAliases (TTree &tree) const;
    void FillCommon (int idx);
    static Fiduciality::value_type GetFiduciality (const LorentzVector &v1, const LorentzVector &v2);

protected:
    
    std::string prefix_;

public:

    //
    // create objects for lepton 1, lepton 2
    //
    SingleLeptonTree lep1;
    SingleLeptonTree lep2;

    //
    // dilepton specific info
    //

    // dilep type
    LorentzVector dilep_p4;
    bool os;
    bool ss;
    bool mm;
    bool ee;
    bool em;
    at::DileptonHypType::value_type dilep_type;
    Fiduciality::value_type fiduciality;
    float dilep_mass;
    float dilep_dphi;
    float dilep_deta;
    float dilep_dr;    

    // gen lep1 info
    LorentzVector gen_lep1_p4;
    int gen_lep1_pdgid;
    
    // gen lep2 info
    LorentzVector gen_lep2_p4;
    int gen_lep2_pdgid;
    
    // gen dilep hyp info
    LorentzVector gen_dilep_p4;
    bool gen_os;
    bool gen_ss;
    bool gen_mm;
    bool gen_ee;
    bool gen_em;
    at::DileptonHypType::value_type gen_dilep_type;
    float gen_dilep_mass;
    float gen_dilep_dphi;
    float gen_dilep_deta;
    float gen_dilep_dr;
};

#endif
