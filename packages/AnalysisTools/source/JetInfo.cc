#include "at/JetInfo.h"
#include "at/DorkyEventIdentifier.h"
#include "at/ConvertHypIndexToVectors.h"
#include "rt/is_equal.h"
#include "rt/MiscTools.h"
#include "jetSelections.h"
#include "Math/GenVector/VectorUtil.h"

namespace at
{
    // ----------------------------------------------------------------------------- //
    // A simple class to hold the Jet object information 
    // ----------------------------------------------------------------------------- //

    // construct
    JetInfo::JetInfo()
        : m_p4(0, 0, 0, 0)
        , m_corr_p4(0, 0, 0, 0)
        , m_is_btagged(false)
        , m_btag_disc(-999999.0)
        , m_mc_flavor_algo(-999999)
        , m_mc_flavor_phys(-999999)
    {
    }

    // construct
    JetInfo::JetInfo
    (
        LorentzVector p4,
        LorentzVector corr_p4, 
        bool is_btagged,
        float btag_disc,
        int mc_flavor_algo,
        int mc_flavor_phys
    )
        : m_p4(p4)
        , m_corr_p4(corr_p4)
        , m_is_btagged(is_btagged)
        , m_btag_disc(btag_disc)
        , m_mc_flavor_algo(mc_flavor_algo)
        , m_mc_flavor_phys(mc_flavor_phys)
    {
    }

    // methods
    LorentzVector JetInfo::P4()     const {return m_p4;             } 
    LorentzVector JetInfo::CorrP4() const {return m_corr_p4;        } 
    float JetInfo::Pt()             const {return m_p4.pt();        } 
    float JetInfo::CorrPt()         const {return m_corr_p4.pt();   } 
    float JetInfo::Eta()            const {return m_p4.eta();       } 
    float JetInfo::Phi()            const {return m_p4.phi();       } 
    float JetInfo::BtagDisc()       const {return m_btag_disc;      } 
    bool JetInfo::IsBtagged()       const {return m_is_btagged;     } 
    int JetInfo::MCFlavorAlgo()     const {return m_mc_flavor_algo; } 
    int JetInfo::MCFlavorPhys()     const {return m_mc_flavor_phys; } 

    // non member methods

    // determine equality
    bool operator == (const JetInfo& lhs, const JetInfo& rhs)
    {
        bool result = (lhs.P4() == rhs.P4());
        result = result && (lhs.CorrP4()       == rhs.CorrP4());
        result = result && (lhs.IsBtagged()    == rhs.IsBtagged());
        result = result && (lhs.MCFlavorAlgo() == rhs.MCFlavorAlgo());
        result = result && (lhs.MCFlavorPhys() == rhs.MCFlavorPhys());
        result = result && (rt::is_equal(lhs.BtagDisc(), rhs.BtagDisc()));
        return result;
    }
    
    // define less than
    bool operator < (const JetInfo& lhs, const JetInfo& rhs)
    {
        return (lhs.CorrPt() < rhs.CorrPt());
    }
    
    // determine if btagged (needed for boost::bind)
    bool IsBtagged(const JetInfo& jet_info)
    {
        return jet_info.IsBtagged();
    }

// ----------------------------------------------------------------------------- //
// A selection class to hold the base jet selection requirements 
// ----------------------------------------------------------------------------- //

    // arguments struct for the map to hold the JetInfo results if the arguments are the same
    JetBaseSelectionArgs::JetBaseSelectionArgs()
        : jet_corrector(NULL)
        , jet_unc(NULL)
        , jet_type(JetType::static_size)
        , btag_type(JetBtagType::static_size) 
        , scale_type(JetScaleType::NONE) 
        , mu_indices()
        , el_indices()
        , deltaR(0.0)
        , min_pt(0.0)
        , max_eta(5.0)
    {
    }

    JetBaseSelectionArgs::JetBaseSelectionArgs
    (
        JetType::value_type jet_type_,
        JetBtagType::value_type btag_type_,           
        JetScaleType::value_type scale_type_,      
        std::vector<int> mu_indices_,  
        std::vector<int> el_indices_,  
        float dr_,                     
        float min_pt_,                 
        float max_eta_                 
    )
        : jet_corrector(NULL)
        , jet_unc(NULL)
        , jet_type(jet_type_)
        , btag_type(btag_type_) 
        , scale_type(scale_type_) 
        , mu_indices(mu_indices_)
        , el_indices(el_indices_)
        , deltaR(dr_)
        , min_pt(min_pt_)
        , max_eta(max_eta_)
    {
    }

    JetBaseSelectionArgs::JetBaseSelectionArgs
    (
        FactorizedJetCorrector* jet_corrector,
        JetCorrectionUncertainty *jet_unc,
        JetType::value_type jet_type_,
        JetBtagType::value_type btag_type_,           
        JetScaleType::value_type scale_type_,      
        std::vector<int> mu_indices_,  
        std::vector<int> el_indices_,  
        float dr_,                     
        float min_pt_,                 
        float max_eta_                 
    )
        : jet_corrector(jet_corrector)
        , jet_unc(jet_unc)
        , jet_type(jet_type_)
        , btag_type(btag_type_) 
        , scale_type(scale_type_) 
        , mu_indices(mu_indices_)
        , el_indices(el_indices_)
        , deltaR(dr_)
        , min_pt(min_pt_)
        , max_eta(max_eta_)
    {
    }

    JetBaseSelectionArgs::JetBaseSelectionArgs
    (
        JetType::value_type jet_type_,
        JetBtagType::value_type btag_type_,           
        JetScaleType::value_type scale_type_,      
        int hyp_index_,
        float dr_,                     
        float min_pt_,                 
        float max_eta_                 
    )
        : jet_corrector(NULL)
        , jet_unc(NULL)
        , jet_type(jet_type_)
        , btag_type(btag_type_) 
        , scale_type(scale_type_) 
        , mu_indices()
        , el_indices()
        , deltaR(dr_)
        , min_pt(min_pt_)
        , max_eta(max_eta_)
    {
        at::ConvertHypIndexToVectors(hyp_index_, mu_indices, el_indices);
    }

    JetBaseSelectionArgs::JetBaseSelectionArgs
    (
        FactorizedJetCorrector* jet_corrector,
        JetCorrectionUncertainty *jet_unc,
        JetType::value_type jet_type_,
        JetBtagType::value_type btag_type_,           
        JetScaleType::value_type scale_type_,      
        int hyp_index_,
        float dr_,                     
        float min_pt_,                 
        float max_eta_                 
    )
        : jet_corrector(jet_corrector)
        , jet_unc(jet_unc)
        , jet_type(jet_type_)
        , btag_type(btag_type_) 
        , scale_type(scale_type_) 
        , mu_indices()
        , el_indices()
        , deltaR(dr_)
        , min_pt(min_pt_)
        , max_eta(max_eta_)
    {
        at::ConvertHypIndexToVectors(hyp_index_, mu_indices, el_indices);
    }

    JetBaseSelectionArgs::JetBaseSelectionArgs
    (
        JetType::value_type jet_type_,
        JetBtagType::value_type btag_type_,           
        JetScaleType::value_type scale_type_,      
        float dr_,                     
        float min_pt_,                 
        float max_eta_                 
    )
        : jet_corrector(NULL)
        , jet_unc(NULL)
        , jet_type(jet_type_)
        , btag_type(btag_type_) 
        , scale_type(scale_type_) 
        , mu_indices()
        , el_indices()
        , deltaR(dr_)
        , min_pt(min_pt_)
        , max_eta(max_eta_)
    {
    }

    JetBaseSelectionArgs::JetBaseSelectionArgs
    (
        FactorizedJetCorrector* jet_corrector,
        JetCorrectionUncertainty *jet_unc,
        JetType::value_type jet_type_,
        JetBtagType::value_type btag_type_,           
        JetScaleType::value_type scale_type_,      
        float dr_,                     
        float min_pt_,                 
        float max_eta_                 
    )
        : jet_corrector(jet_corrector)
        , jet_unc(jet_unc)
        , jet_type(jet_type_)
        , btag_type(btag_type_) 
        , scale_type(scale_type_) 
        , mu_indices()
        , el_indices()
        , deltaR(dr_)
        , min_pt(min_pt_)
        , max_eta(max_eta_)
    {
    }

    // non members
    bool operator == (const JetBaseSelectionArgs& lhs, const JetBaseSelectionArgs& rhs)
    {
        bool result; 
        result = lhs.jet_corrector == rhs.jet_corrector;
        result = result && lhs.jet_unc    == rhs.jet_unc;     
        result = result && lhs.scale_type == rhs.scale_type; 
        result = result && lhs.jet_type   == rhs.jet_type; 
        result = result && lhs.btag_type  == rhs.btag_type;
        result = result && lhs.el_indices == rhs.el_indices;
        result = result && lhs.mu_indices == rhs.mu_indices;
        result = result && rt::is_equal(lhs.deltaR  , rhs.deltaR); 
        result = result && rt::is_equal(lhs.min_pt  , rhs.min_pt);
        result = result && rt::is_equal(lhs.max_eta , rhs.max_eta);
        return result;
    }

    bool operator != (const JetBaseSelectionArgs& lhs, const JetBaseSelectionArgs& rhs)
    {
        return not (lhs==rhs);
    }

// ----------------------------------------------------------------------------- //
// functions to return the JetInfo collections 
// ----------------------------------------------------------------------------- //

    // Btag working points
    static float JetBtagWP[JetBtagType::static_size] = 
    {
        /*JetBtagType::NONE WP = */-999999.0f, 
        /*JetBtagType::CSVL WP = */0.244f, 
        /*JetBtagType::CSVM WP = */0.679f, 
        /*JetBtagType::CSVL WP = */0.898f
    };
    
    // apply base selection
    struct JetPassesSelection
    {

        JetPassesSelection(const JetBaseSelectionArgs& jet_sel_args) : m_ja(jet_sel_args) {}

        bool operator() (const JetInfo& jet_info) const
        {
            // min pt --> using corrected p4
            if (jet_info.CorrPt() < m_ja.min_pt)
            {
                return false;
            }

            // min pt --> using corrected p4
            if (fabs(jet_info.CorrP4().eta()) > m_ja.max_eta)
            {   
                return false;
            }

            // selected muons
            for (size_t i = 0; i != m_ja.mu_indices.size(); i++)
            {
                const LorentzVector& mu_p4 = tas::mus_p4().at(m_ja.mu_indices.at(i));
                const float dr = ROOT::Math::VectorUtil::DeltaR(jet_info.CorrP4(), mu_p4);
                if (dr < m_ja.deltaR) {return false;}
            }

            // selected electrons
            for (size_t i = 0; i != m_ja.el_indices.size(); i++)
            {
                const LorentzVector& el_p4 = tas::els_p4().at(m_ja.el_indices.at(i));
                const float dr = ROOT::Math::VectorUtil::DeltaR(jet_info.CorrP4(), el_p4);
                if (dr < m_ja.deltaR) {return false;}
            }

            // if we're here then the jet is good 
            return true;
        }

        // members
        JetBaseSelectionArgs m_ja;
    };

    // function to build the vector of JetInfos
    std::vector<at::JetInfo> GetJetInfos(const JetBaseSelectionArgs& jet_sel_args)
    {
        using namespace tas;

        // used interally to cache the results of the GetJetInfos()
        static std::map<JetBaseSelectionArgs, std::vector<at::JetInfo>, JetBaseSelectionArgsCompare> results_map;

        // keep track if we changed events.  If so, then clear the "results_map".
        static at::DorkyEventIdentifier stored_event = {-99999, -99999, -99999};
        at::DorkyEventIdentifier current_event = {evt_run(), evt_lumiBlock(), evt_event()};
        if (not(stored_event == current_event))
        {
            results_map.clear();
            stored_event = current_event;
        }

        // determine if the result is already in the map?
        if (results_map.find(jet_sel_args) != results_map.end())
        {
             return results_map[jet_sel_args];
        }

        // doesn't already exist, now create the JetInfos
        // -------------------------------------//

        std::vector<JetInfo> jet_infos;

        // convenience
        const JetBaseSelectionArgs& ja = jet_sel_args;

        // Factorized Jet corrector only for PF jets
        if (
                ja.jet_corrector != NULL &&
                ja.jet_type != JetType::PF_FAST_CORR_RESIDUAL && 
                ja.jet_type != JetType::PF_FAST_CORR && 
                ja.jet_type != JetType::PF_CORR && 
                ja.jet_type != JetType::PF_UNCORR
           )
        {
            throw std::invalid_argument("Only particle flow jets are supported for use with a jet corrector!");
        }

        // Factorized Jet Uncertainty Corrector only for PF jets
        if (
                ja.jet_unc != NULL &&
                ja.jet_type != JetType::PF_FAST_CORR_RESIDUAL && 
                ja.jet_type != JetType::PF_FAST_CORR && 
                ja.jet_type != JetType::PF_CORR && 
                ja.jet_type != JetType::PF_UNCORR
           )
        {
            throw std::invalid_argument("Only particle flow jets are supported for use with a jet uncertainty corrector!");
        }

        // PF jets 
        if (JetType::PF_CORR or JetType::PF_UNCORR or JetType::PF_FAST_CORR or JetType::PF_FAST_CORR_RESIDUAL)
        {
            for (size_t jidx = 0; jidx != pfjets_p4().size(); jidx++)
            {
                // uncorrected p4
                const LorentzVector& jet_p4 = pfjets_p4().at(jidx);

                // corrected p4
                double jet_corr = 1.0;
                if (ja.jet_corrector)  // if pointer not NULL, use the OTF JEC
                {
                    ja.jet_corrector->setRho(evt_ww_rho_vor());
                    ja.jet_corrector->setJetA(pfjets_area().at(jidx));
                    ja.jet_corrector->setJetPt(pfjets_p4().at(jidx).pt());
                    ja.jet_corrector->setJetEta(pfjets_p4().at(jidx).eta());        
                    jet_corr = ja.jet_corrector->getCorrection();
                }
                else  // else, take it from the ntuple
                {
                    switch (ja.jet_type)
                    {
                        case JetType::PF_CORR:               jet_corr = 1.0;                                     break;
                        case JetType::PF_UNCORR:             jet_corr = pfjets_cor().at(jidx);                   break;
                        case JetType::PF_FAST_CORR:          jet_corr = pfjets_corL1FastL2L3().at(jidx);         break;
                        case JetType::PF_FAST_CORR_RESIDUAL: jet_corr = pfjets_corL1FastL2L3residual().at(jidx); break;
                        default:                             jet_corr = 1.0;
                    }
                }
                LorentzVector jet_corr_p4 = jet_p4 * jet_corr; 

                // jet uncertainty up/down
                if (ja.scale_type == JetScaleType::UP or ja.scale_type == JetScaleType::DOWN)  // if pointer not NULL, use the OTF JEC uncertainty
                {
                    if (ja.jet_unc)
                    {
                        ja.jet_unc->setJetPt(jet_corr_p4.pt());    
                        ja.jet_unc->setJetEta(jet_corr_p4.eta());  
                        const double jet_corr_unc = (1.0 + ja.jet_unc->getUncertainty(true) * ja.scale_type);    
                        jet_corr_p4 *= jet_corr_unc; 
                    }
                    else // else, take it from the ntuple
                    {
                        const double jet_corr_unc = getJetMetSyst(static_cast<int>(ja.scale_type), jet_corr_p4.pt(), jet_p4.eta());
                        jet_corr_p4 *= jet_corr_unc; 
                    }
                }


                // btag info
                const float jet_btag_wp = JetBtagWP[ja.btag_type];
                float jet_btag_disc = -999999.0;
                switch (ja.btag_type)
                {
                    case JetBtagType::NONE: jet_btag_disc = 999999.0;                                         break;
                    case JetBtagType::CSVL: jet_btag_disc = pfjets_combinedSecondaryVertexBJetTag().at(jidx); break;
                    case JetBtagType::CSVM: jet_btag_disc = pfjets_combinedSecondaryVertexBJetTag().at(jidx); break;
                    case JetBtagType::CSVT: jet_btag_disc = pfjets_combinedSecondaryVertexBJetTag().at(jidx); break;
                    default:                jet_btag_disc = 999999.0;
                }
                const bool jet_is_btagged = (jet_btag_disc > jet_btag_wp);

                // MC flavor
                const int mc_flavor_algo = pfjets_mcflavorAlgo().at(jidx);
                const int mc_flavor_phys = pfjets_mcflavorPhys().at(jidx);

                // create jet infos
                JetInfo jet_info(jet_p4, jet_corr_p4, jet_is_btagged, jet_btag_disc, mc_flavor_algo, mc_flavor_phys);

                // select
                if (JetPassesSelection(ja)(jet_info))
                {
                    jet_infos.push_back(jet_info);
                }
            }

        }
        // invalid jet type -- throw an exception
        else
        {
            throw std::invalid_argument("[at::GetJetInfos] - unsupported JetType given.");
        }

        // sort by corrected pt
        std::sort(jet_infos.begin(), jet_infos.end(), SortByCorrPt()); 

        // push into the map:
        results_map[jet_sel_args] = jet_infos;

        // done
        return jet_infos;
    }

    bool NoSelection(const JetInfo&)
    {
        return true;
    }
    
} // namespace at

