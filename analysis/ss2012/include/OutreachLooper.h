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

    // reco event level
    float ht;
    float met;
    int nbjets;
    int njets;
    std::vector<LorentzVector> vbjets_p4;
    std::vector<LorentzVector> vjets_p4;
    float sf_dileptrig;
    float sf_lepeff;
    float sf_nbtags;
    int nvtxs;
    float vtxw;
    bool clean;

    // gen event level 
    float gen_met;
    float gen_ht;
    int gen_nbjets;
    int gen_njets;
    std::vector<LorentzVector> gen_vbjets_p4;
    std::vector<LorentzVector> gen_vjets_p4;
    unsigned int gen_dilep_type;

    // gen lepton level
    LorentzVector lep1_gen_p4;
    bool lep1_from_tau;
    bool lep1_gen_id;

    LorentzVector lep2_gen_p4;
    bool lep2_from_tau;
    bool lep2_gen_id;

    // reco lepton level
    LorentzVector lep1_p4;
    int lep1_id;
    bool lep1_passes_id;
    bool lep1_passes_iso;
    float lep1_iso;
    bool lep1_num;

    LorentzVector lep2_p4;
    int lep2_id;
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
            const std::string& cut_string = "",
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
        std::vector<std::string> m_vcuts;

        // cut switches
        bool m_useOS;                             
        bool m_useSS;                             
        //bool m_applyVertexMatching;                
        //bool m_vetoLowMass;                        
        //bool m_vetoJets;                           
        //bool m_vetoMET;                            
        //bool m_vetoHT;                             
        //bool m_requireCleaning;                    
        //bool m_vetoBjets;                          
        //bool m_useVertexReweighting;               
        //bool m_requireDilepHyp;                    
        //bool m_removeLeptonsOverlappingWithPartons;

        // struct to hold tree values
        OutreachTree m_evt;

    private:
        // methods:
};

#endif // OUTREACHLOOPER_H 
