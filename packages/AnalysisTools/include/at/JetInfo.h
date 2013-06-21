#ifndef JETINFO_H
#define JETINFO_H

#include <string>
#include <vector>
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
            PF_FAST_CORR_RESIDUAL,
            PF_FAST_CORR,
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
                bool is_btagged,
                float btag_disc,
                int mc_flavor_algo,
                int mc_flavor_phys
            );
            
            // methods
            LorentzVector P4()     const; 
            LorentzVector CorrP4() const; 
            float Pt()             const; 
            float CorrPt()         const; 
            float Eta()            const; 
            float Phi()            const; 
            float BtagDisc()       const; 
            bool IsBtagged()       const; 
            int MCFlavorAlgo()     const;
            int MCFlavorPhys()     const;

        private:
    
            LorentzVector m_p4;
            LorentzVector m_corr_p4; 
            bool m_is_btagged;
            float m_btag_disc;
            int m_mc_flavor_algo;
            int m_mc_flavor_phys;
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

        // constuct: general list of els/mus
        JetBaseSelectionArgs
        (
            JetType::value_type jet_type_,          // jet type (from jetSelection.h)
            JetBtagType::value_type btag_type_,     // btag type (from jetSelections.h)
            JetScaleType::value_type scale_type_,   // JEC scale type (from jetSelection.h)
            std::vector<int> mu_indices_,           // monns indices to veto from the event
            std::vector<int> el_indices_,           // electron indices to veto from the event
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
            std::vector<int> mu_indices_,           // monns indices to veto from the event
            std::vector<int> el_indices_,           // electron indices to veto from the event
            float dr_,                              // the minimum DeltaR(jet, lepton)
            float min_pt_,                          // jet pt requirement: jet pt > min_pt
            float max_eta_                          // jet eta requirement: |jet eta| < max_eta
        );

        // constuct: hyp index 
        JetBaseSelectionArgs
        (
            JetType::value_type jet_type_,          // jet type (from jetSelection.h)
            JetBtagType::value_type btag_type_,     // btag type (from jetSelections.h)
            JetScaleType::value_type scale_type_,   // JEC scale type (from jetSelection.h)
            int hyp_index_,                         // hypothesis index 
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
            int hyp_index_,                         // hypothesis index 
            float dr_,                              // the minimum DeltaR(jet, lepton)
            float min_pt_,                          // jet pt requirement: jet pt > min_pt
            float max_eta_                          // jet eta requirement: |jet eta| < max_eta
        );

        // constuct: no selection lepton removal 
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
        std::vector<int> mu_indices;
        std::vector<int> el_indices;
        float deltaR; 
        float min_pt;
        float max_eta;
    };

    // non member methods

    // operators
    bool operator == (const JetBaseSelectionArgs& lhs, const JetBaseSelectionArgs& rhs);
    bool operator != (const JetBaseSelectionArgs& lhs, const JetBaseSelectionArgs& rhs);

    // comparison (needed by map)
    struct JetBaseSelectionArgsCompare
    {
        bool operator () (const JetBaseSelectionArgs& lhs, const JetBaseSelectionArgs& rhs) const
        {
            return (lhs == rhs);
        }
    };

// ----------------------------------------------------------------------------- //
// functions to return the JetInfo collections 
// ----------------------------------------------------------------------------- //

    std::vector<at::JetInfo> GetJetInfos(const JetBaseSelectionArgs& jet_sel_args);

// ----------------------------------------------------------------------------- //
// functions to return the indivdual components in the form of a std::vector 
// ----------------------------------------------------------------------------- //

    // always returns true 
    bool NoSelection(const JetInfo&);

    // get the jet corrected p4
    template <typename Function>
    std::vector<LorentzVector> GetJets(const JetBaseSelectionArgs& jet_fun_args, Function Selection);

    // get the number of jets 
    template <typename Function>
    unsigned int NumJets(const JetBaseSelectionArgs& jet_fun_args, Function Selection);

    // get the jet corrected p4
    template <typename Function>
    std::vector<LorentzVector> GetBtaggedJets(const JetBaseSelectionArgs& jet_fun_args, Function Selection);

    // get the number of btagged jets 
    template <typename Function>
    unsigned int NumBtaggedJets(const JetBaseSelectionArgs& jet_fun_args, Function Selection);

} // namespace at

#include "JetInfo.impl.h"

#endif // JETINFO_H
