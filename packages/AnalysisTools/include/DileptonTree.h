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
    LorentzVector dilep_p4;
    bool is_os;
    bool is_ss;
    at::DileptonHypType::value_type dilep_type;
    at::DileptonHypType::value_type dilep_gen_type;
    Fiduciality::value_type fiduciality;
    float dilep_mass;
    float dilep_dphi;
    float dilep_deta;
    float dilep_dr;    
};

#endif
