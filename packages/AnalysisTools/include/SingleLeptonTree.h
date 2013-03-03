#ifndef SINGLELEPTONTREE_H
#define SINGLELEPTONTREE_H

#include <string>
#include "Math/LorentzVector.h"

// forward declaration
class TTree;

// typedefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

class SingleLeptonTree
{
public:
    SingleLeptonTree ();
    SingleLeptonTree (const std::string &prefix);
    virtual ~SingleLeptonTree () {}

    void Reset ();
    void SetBranches (TTree &tree);
    void SetAliases (TTree &tree) const;
    void FillCommon (int id, int idx);

private:

    std::string prefix_;

public:    

    //
    // lepton reco info
    //
    LorentzVector p4;
    bool passes_id;
    bool passes_iso;
    bool is_num;
    bool is_den;
    bool is_fo;
    int is_fromw;
    int charge;
    int pdgid;
    int type;
    float d0;
    float d0err;
    float dz;
    float dzerr;
    float ip3d;
    float ip3derr;
    float mt;
    float corpfiso;
    float pfiso;
    float chiso;
    float emiso;
    float nhiso;
    float corpfiso04;
    float pfiso04;
    float chiso04;
    float emiso04;
    float nhiso04;
    float cordetiso;
    float detiso;
    float trkiso;
    float ecaliso;
    float hcaliso;
    float cordetiso04;
    float detiso04;
    float trkiso04;
    float ecaliso04;
    float hcaliso04;
    float effarea;
    float effarea04;
    float dbeta;
    float dbeta04;
    float sf_lepeff;
    float sf_trig;

    //
    // lepton gen info
    //
    LorentzVector mcp4;
    LorentzVector mc3p4;
    LorentzVector mc_momp4;
    int mcid;
    int mc3id;
    int momid;
    int mc3_momid;

    //
    // electron specific info
    //
    LorentzVector gsf_p4;
    LorentzVector ctf_p4;
    LorentzVector sc_p4;
    bool q3agree;
    bool is_conv;
    int qsc;
    int qctf;
    int qgsf;
    int nmhits;
    int eleid_veto;
    int eleid_loose;
    int eleid_medium;
    int eleid_tight;
    float dphiin;
    float detain;
    float sieie;
    float hoe;
    float ooemoop;
    float conv_dist;
    float conv_dcot;
    
    //
    // muon specific info
    //
    LorentzVector gfit_p4;
    bool is_global;
    bool is_tracker;
    bool is_stamu;
    bool is_pfmu;
    bool is_loosemu;
    bool is_tightmu;
    int npixelhits;
    int nsihits;    
    int nsilayers;
    int nstahits;
    int nstations;
    float chi2;
    float ndof;
    float pterr;
    float ecal_vetodep;
    float hcal_vetodep;    
};

#endif
