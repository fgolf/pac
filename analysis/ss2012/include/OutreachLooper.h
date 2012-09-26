#ifndef OUTREACHLOOPER_H 
#define OUTREACHLOOPER_H

#include "at/AnalysisWithTree.h"
//#include "Math/LorentzVector.h"
//#include <tr1/array>
//#include <tr1/memory>
//#include <vector>
#include "at/Sample.h"
#include <string>
//#include "SameSignTree.h"

//#include <vector> 
#include "Math/LorentzVector.h"
#include "at/DileptonHypType.h"
#include "EventInfoTree.h"

// typdefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
//typedef std::vector<LorentzVector> vecLorentzVector;
//typedef std::vector<float> vecd;

// forward declaration
class TTree;

// simple class for the Outreach baby
struct OutreachTree 
{
    // construct:
    OutreachTree (); 

    // mehtods:
    void Reset();
    void SetBranches(TTree& tree);

public:

    // event level info
    EventInfoTree event_info;

    // event level
    float ht;
    float met;
    int nbtags;
    int njets;
    int nbjets_num;
    int njets_num;
    float gen_ht;
    unsigned int dilep_type;
    std::vector<LorentzVector> vbjets_p4;
    std::vector<bool> vbjets_num;
    std::vector<LorentzVector> vjets_p4;
    std::vector<bool> vjets_num;
    float sf_dileptrig;
    float sf_lepeff;
    float sf_nbtag;
    float sf_nbtag3;
    int nvtxs;
    float vtxw;
    bool clean;

    // lepton level
    LorentzVector lep1_p4;
    LorentzVector lep1_gen_p4;
    int lep1_pdgid;
    bool lep1_matched;
    bool lep1_from_tau;
    bool lep1_passes_id;
    bool lep1_passes_iso;
    float lep1_iso;
    bool lep1_num;

    LorentzVector lep2_p4;
    LorentzVector lep2_gen_p4;
    bool lep2_matched;
    int lep2_pdgid;
    bool lep2_from_tau;
    bool lep2_passes_id;
    bool lep2_passes_iso;
    float lep2_iso;
    bool lep2_num;
};

class OutreachLooper : public at::AnalysisWithTree
{
    public:
        // construct:
        OutreachLooper
        (
            const std::string& root_file_name,
            const at::Sample::value_type& sample,
            double luminosity = 1.0,
            const std::string& vtxreweight_file_name = "",
            bool is_fast_sim = false,
            bool verbose = false
        );

        // destroy:
        ~OutreachLooper();

        // function operator:
        int operator() (long event);

        // members:
        virtual void BeginJob();
        virtual void EndJob();
        int Analyze(long event);

    private:
        // members:
        at::Sample::value_type m_sample;
        double m_lumi;
        bool m_verbose;
        bool m_is_fastsim;

        // struct to hold tree values
        OutreachTree m_evt;

    private:
        // methods:
};

#endif // OUTREACHLOOPER_H 
