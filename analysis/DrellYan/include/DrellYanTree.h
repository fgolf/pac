#ifndef DRELLYABTREE_H
#define DRELLYABTREE_H

// #include "at/Sample.h"
// #include <vector> 
#include "Math/LorentzVector.h"
#include "at/DileptonHypType.h"
#include "DileptonTree.h"
#include "EventInfoTree.h"

// forward declaration
class TTree;

// typedefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef std::vector<LorentzVector> vecLorentzVector;
typedef std::vector<float> vecd;
typedef std::vector<int> veci;

struct DrellYanTree : public DileptonTree
{
    // constructors and destructor
    DrellYanTree ();
    virtual ~DrellYanTree () {}

    void Reset();
    void SetBranches(TTree& tree);
    void SetAliases(TTree& tree) const;

public:

    // event level info
    EventInfoTree event_info;
    int charge_type;
    float vtxw;
    float rho;
    float rho_iso;
    bool is_mm;
    bool is_ee;
    bool trig_mm;
    bool trig_ee;

    // DY specific info 
    bool is_gen_z;
    LorentzVector gen_z_p4;
    LorentzVector gen_d1_p4;
    LorentzVector gen_d2_p4;
    at::DileptonHypType::value_type gen_z_type;
    int gen_d1_pdgid;
    int gen_d2_pdgid;
    bool is_z_ee;
    bool is_z_mm;
    bool is_z_tt;
    bool is_acc;
    bool is_acc_ee;
    bool is_acc_mm;
};

#endif
