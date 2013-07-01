#ifndef JETINFO_H
#define JETINFO_H

#include <string>
#include <vector>
#include <ostream>
#include "Math/LorentzVector.h"
#include "jetcorr/FactorizedJetCorrector.h"
#include "jetcorr/JetCorrectionUncertainty.h"

// ----------------------------------------------------------------------------- //
// Declarations 
// ----------------------------------------------------------------------------- //

// forward declaration
class TTree;

// typedefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef std::vector<LorentzVector> vecLorentzVector;
typedef std::vector<float> vecd;
typedef std::vector<int> veci;


// ----------------------------------------------------------------------------- //
// A simple class to hold the Jet object information 
// ----------------------------------------------------------------------------- //


namespace at
{
    // basic jet type
    struct JetType
    {
        enum value_type
        {
            PF_FAST_CORR,  // for data, residual correction is implied
            PF_CORR,
            PF_UNCORR,
            static_size
        };
    };
    
    struct JetBtagType
    {
        enum value_type
        {
            NONE,
            CSVL,
            CSVM,
            CSVT,
            static_size
        };
    };

    struct JetScaleType
    {
        enum value_type
        {
            NONE        = 0,
            DOWN        = -1,
            UP          = 1,
            static_size = 3
        };
    };

    // JetInfo class
    class JetInfo
    {
        public:
            // construct
            JetInfo();
            JetInfo
            (
                LorentzVector p4,
                LorentzVector corr_p4, 
                LorentzVector mc3_p4, 
                LorentzVector nearjet_p4, 
                LorentzVector nearlep_p4, 
                bool is_btagged,
                float btag_disc,
                int mc_flavor_algo,
                int mc_flavor_phys,
                int mc3_id,
                int mom_id
            );
            
            // methods
            LorentzVector P4()        const; 
            LorentzVector CorrP4()    const; 
            LorentzVector MC3P4()     const; 
            LorentzVector NearjetP4() const; 
            LorentzVector NearlepP4() const; 
            float Pt()                const; 
            float CorrPt()            const; 
            float Eta()               const; 
            float Phi()               const; 
            float BtagDisc()          const; 
            float NearjetDr()         const;
            float NearlepDr()         const;
            bool IsBtagged()          const; 
            int MCFlavorAlgo()        const;
            int MCFlavorPhys()        const;
            int MC3Id()               const;
            int MomId()               const;

        private:
    
            LorentzVector m_p4;
            LorentzVector m_corr_p4; 
            LorentzVector m_mc3_p4;
            LorentzVector m_nearjet_p4;
            LorentzVector m_nearlep_p4;
            bool m_is_btagged;
            bool m_is_vtx_matched;
            float m_btag_disc;
            int m_mc_flavor_algo;
            int m_mc_flavor_phys;
            int m_mc3_id;
            int m_mom_id;
    };
    
    // non-member methods

    // operators 
    bool operator == (const JetInfo& lhs, const JetInfo& rhs);
    bool operator <  (const JetInfo& lhs, const JetInfo& rhs);
    
    // determine if btagged (needed for boost::bind)
    bool IsBtagged(const JetInfo& jet_info);

    // sorting
    struct SortByCorrPt 
    {
        bool operator () (const JetInfo& lhs, const JetInfo& rhs) const 
        {
            return lhs.CorrPt() > rhs.CorrPt();
        }
    };
    

// ----------------------------------------------------------------------------- //
// A selection class to hold the base jet selection requirements 
// ----------------------------------------------------------------------------- //


    // arguments struct for the map to hold the JetInfo results if the arguments are the same
    struct JetBaseSelectionArgs 
    {
        // construct
        JetBaseSelectionArgs();

        // constuct:
        JetBaseSelectionArgs
        (
            JetType::value_type jet_type_,          // jet type (from jetSelection.h)
            JetBtagType::value_type btag_type_,     // btag type (from jetSelections.h)
            JetScaleType::value_type scale_type_,   // JEC scale type (from jetSelection.h)
            float dr_,                              // the minimum DeltaR(jet, lepton)
            float min_pt_,                          // jet pt requirement: jet pt > min_pt
            float max_eta_                          // jet eta requirement: |jet eta| < max_eta
        );

        JetBaseSelectionArgs
        (
            FactorizedJetCorrector* jet_corrector,  // jet corrector pointer does not own pointer
            JetCorrectionUncertainty* jet_unc,      // jet uncertainty pointer does not own pointer
            JetType::value_type jet_type_,          // jet type (from jetSelection.h)
            JetBtagType::value_type btag_type_,     // btag type (from jetSelections.h)
            JetScaleType::value_type scale_type_,   // JEC scale type (from jetSelection.h)
            float dr_,                              // the minimum DeltaR(jet, lepton)
            float min_pt_,                          // jet pt requirement: jet pt > min_pt
            float max_eta_                          // jet eta requirement: |jet eta| < max_eta
        );

        // members
        FactorizedJetCorrector* jet_corrector;  // does not own pointer
        JetCorrectionUncertainty* jet_unc;      // does not own pointer
        JetType::value_type jet_type; 
        JetBtagType::value_type btag_type;
        JetScaleType::value_type scale_type; 
        float deltaR; 
        float min_pt;
        float max_eta;
    };

    // non member methods

    // operators
    bool operator == (const JetBaseSelectionArgs& lhs, const JetBaseSelectionArgs& rhs);
    bool operator != (const JetBaseSelectionArgs& lhs, const JetBaseSelectionArgs& rhs);
    bool operator <  (const JetBaseSelectionArgs& lhs, const JetBaseSelectionArgs& rhs);
    std::ostream& operator << (std::ostream& os, const JetBaseSelectionArgs& ja);

// ----------------------------------------------------------------------------- //
// functions to return the JetInfo collections 
// ----------------------------------------------------------------------------- //

    std::vector<at::JetInfo> GetJetInfos(const JetBaseSelectionArgs& jet_sel_args);

// ----------------------------------------------------------------------------- //
// functions to return the indivdual components 
// ----------------------------------------------------------------------------- //

    // always returns true 
    bool NoSelection(const JetInfo&);

    // get the jet corrected p4
    template <typename Function>
    std::vector<LorentzVector> GetJetsP4(const JetBaseSelectionArgs& jet_fun_args, Function Selection);

    template <typename Function>
    std::vector<LorentzVector> GetBtaggedJetsP4(const JetBaseSelectionArgs& jet_fun_args, Function Selection);

    // get the number of jets 
    template <typename Function>
    unsigned int NumJets(const JetBaseSelectionArgs& jet_fun_args, Function Selection);

    template <typename Function>
    unsigned int NumBtaggedJets(const JetBaseSelectionArgs& jet_fun_args, Function Selection);

    // get the deltaR between j1 and j2 
    template <typename Function>
    float JetsDr12(const JetBaseSelectionArgs& jet_fun_args, Function Selection);

    template <typename Function>
    float BJetsDr12(const JetBaseSelectionArgs& jet_fun_args, Function Selection);

    // get the jet mc3 p4
    template <typename Function>
    std::vector<LorentzVector> GetJetsMC3P4(const JetBaseSelectionArgs& jet_fun_args, Function Selection);

    template <typename Function>
    std::vector<LorentzVector> GetBtaggedJetsMC3P4(const JetBaseSelectionArgs& jet_fun_args, Function Selection);

    // get the nearest jet p4
    template <typename Function>
    std::vector<LorentzVector> GetJetsNearjetP4(const JetBaseSelectionArgs& jet_args, Function jet_selection);

    template <typename Function>
    std::vector<LorentzVector> GetBtaggedJetsNearjetP4(const JetBaseSelectionArgs& jet_args, Function jet_selection);

    // get the nearest jet DeltaR 
    template <typename Function>
    std::vector<float> GetJetsNearjetDr(const JetBaseSelectionArgs& jet_args, Function jet_selection);

    template <typename Function>
    std::vector<float> GetBtaggedJetsNearjetDr(const JetBaseSelectionArgs& jet_args, Function jet_selection);

    // get the nearest lepton p4
    template <typename Function>
    std::vector<LorentzVector> GetJetsNearlepP4(const JetBaseSelectionArgs& jet_args, Function jet_selection);

    template <typename Function>
    std::vector<LorentzVector> GetBtaggedJetsNearlepP4(const JetBaseSelectionArgs& jet_args, Function jet_selection);

    // get the nearest lepton DeltaR 
    template <typename Function>
    std::vector<float> GetJetsNearlepDr(const JetBaseSelectionArgs& jet_args, Function jet_selection);

    template <typename Function>
    std::vector<float> GetBtaggedJetsNearlepDr(const JetBaseSelectionArgs& jet_args, Function jet_selection);

    // get the b-tag discriminator value
    template <typename Function>
    std::vector<float> GetJetsDisc(const JetBaseSelectionArgs& jet_args, Function jet_selection);

    template <typename Function>
    std::vector<float> GetBtaggedJetsDisc(const JetBaseSelectionArgs& jet_args, Function jet_selection);

    // get the bools for whether the jet is b-tagged
    template <typename Function>
    std::vector<bool> GetJetsBtagged(const JetBaseSelectionArgs& jet_args, Function jet_selection);

    // get the MC flavor physics
    template <typename Function>
    std::vector<int> GetJetsMCFlavorPhys(const JetBaseSelectionArgs& jet_args, Function jet_selection);

    template <typename Function>
    std::vector<int> GetBtaggedJetsMCFlavorPhys(const JetBaseSelectionArgs& jet_args, Function jet_selection);

    // get the MC flavor algorithm
    template <typename Function>
    std::vector<int> GetJetsMCFlavorAlgo(const JetBaseSelectionArgs& jet_args, Function jet_selection);

    template <typename Function>
    std::vector<int> GetBtaggedJetsMCFlavorAlgo(const JetBaseSelectionArgs& jet_args, Function jet_selection);

    // get the MC matched ID 
    template <typename Function>
    std::vector<int> GetJetsMC3Id(const JetBaseSelectionArgs& jet_args, Function jet_selection);

    template <typename Function>
    std::vector<int> GetBtaggedJetsMC3Id(const JetBaseSelectionArgs& jet_args, Function jet_selection);

    // get the MC matched mother ID
    template <typename Function>
    std::vector<int> GetJetsMomId(const JetBaseSelectionArgs& jet_args, Function jet_selection);

    template <typename Function>
    std::vector<int> GetBtaggedJetsMomId(const JetBaseSelectionArgs& jet_args, Function jet_selection);

} // namespace at

#include "JetInfo.impl.h"

#endif // JETINFO_H
