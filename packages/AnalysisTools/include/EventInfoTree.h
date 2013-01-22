#ifndef EVENTINFOTREE_H
#define EVENTINFOTREE_H

#include <string>
#include "at/Sample.h"

// forward declaration
class TTree;

class EventInfoTree
{
public:
    EventInfoTree ();
    EventInfoTree (const std::string &prefix);
    virtual ~EventInfoTree () {}

    void Reset ();
    void SetBranches (TTree &tree);
    void SetAliases (TTree &tree) const;
    void FillCommon (at::Sample::value_type sample_, const std::string& root_file_name = "");

private:

    std::string prefix_;

public:

    //
    // general event level info
    //
    unsigned int run;
    unsigned int ls;
    unsigned int evt;
    at::Sample::value_type sample;
    TString dataset;
    TString filename;
    bool is_real_data;

    //
    // some reco event level info
    //
    int nvtxs;
    int vtx_idx;
    float pfmet;
    float pfmet_phi;
    float uncorpfmet;
    float uncorpfmet_phi;    
    int pu_nvtxs;
    float pu_ntrueint;

    //
    // met filters 
    //
	bool filt_csc;
    bool filt_hbhe;
    bool filt_hcallaser;
    bool filt_ecaltp;
    bool filt_trkfail;
    bool filt_eebadsc;
    bool filt_hbhenew;

    //
    // some gen event level info
    //
    float scale1fb;
    float xsec;
    float kfactor;
    float gen_met;
    float gen_met_phi;
};

#endif
