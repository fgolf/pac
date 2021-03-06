#include "at/JetInfo.h"
#include "at/DorkyEventIdentifier.h"
#include "at/ConvertHypIndexToVectors.h"
#include "rt/is_equal.h"
#include "rt/MiscTools.h"
#include "jetSelections.h"
#include "Math/GenVector/VectorUtil.h"
#include "Math/Vector2D.h"
#include "TRandom3.h"

using namespace std;

namespace at
{
    // ----------------------------------------------------------------------------- //
    // A simple class to hold the Jet object information 
    // ----------------------------------------------------------------------------- //

    // construct
    JetInfo::JetInfo()
        : m_p4(0, 0, 0, 0)
        , m_corr_p4(0, 0, 0, 0)
        , m_mc3_p4(0, 0, 0, 0)
        , m_is_btagged(false)
        , m_btag_disc(-999999.0)
        , m_mc_flavor_algo(-999999)
        , m_mc_flavor_phys(-999999)
        , m_mc3_id(-999999)
        , m_mom_id(-999999)
    {
    }

    // construct
    JetInfo::JetInfo
    (
         LorentzVector p4,
         LorentzVector corr_p4, 
         LorentzVector mc3_p4, 
         bool is_btagged,
         float btag_disc,
         int mc_flavor_algo,
         int mc_flavor_phys,
         int mc3_id,
         int mom_id
    )
        : m_p4(p4)
        , m_corr_p4(corr_p4)
        , m_mc3_p4(mc3_p4)
        , m_is_btagged(is_btagged)
        , m_btag_disc(btag_disc)
        , m_mc_flavor_algo(mc_flavor_algo)
        , m_mc_flavor_phys(mc_flavor_phys)
        , m_mc3_id(mc3_id)
        , m_mom_id(mom_id)
    {
    }

    // methods
    const LorentzVector& JetInfo::P4()     const {return m_p4;            } 
    const LorentzVector& JetInfo::CorrP4() const {return m_corr_p4;       } 
    const LorentzVector& JetInfo::MC3P4()  const {return m_mc3_p4;        } 
    float JetInfo::Pt()                    const {return m_p4.pt();       } 
    float JetInfo::CorrPt()                const {return m_corr_p4.pt();  } 
    float JetInfo::Eta()                   const {return m_p4.eta();      } 
    float JetInfo::Phi()                   const {return m_p4.phi();      } 
    float JetInfo::BtagDisc()              const {return m_btag_disc;     } 
    bool JetInfo::IsBtagged()              const {return m_is_btagged;    } 
    int JetInfo::MCFlavorAlgo()            const {return m_mc_flavor_algo;} 
    int JetInfo::MCFlavorPhys()            const {return m_mc_flavor_phys;} 
    int JetInfo::MC3Id()                   const {return m_mc3_id;        } 
    int JetInfo::MomId()                   const {return m_mom_id;        } 

    // non member methods

    // determine equality
    bool operator == (const JetInfo& lhs, const JetInfo& rhs)
    {
        bool result = (lhs.P4() == rhs.P4());
        result = result && (lhs.CorrP4()       == rhs.CorrP4()       ); 
        result = result && (lhs.MC3P4()        == rhs.MC3P4()        ); 
        result = result && (lhs.IsBtagged()    == rhs.IsBtagged()    ); 
        result = result && (lhs.MCFlavorAlgo() == rhs.MCFlavorAlgo() ); 
        result = result && (lhs.MCFlavorPhys() == rhs.MCFlavorPhys() ); 
        result = result && (lhs.MC3Id()        == rhs.MC3Id()        ); 
        result = result && (lhs.MomId()        == rhs.MomId()        ); 
        result = result && (rt::is_equal(lhs.BtagDisc(), rhs.BtagDisc()));
        return result;
    }

    // define less than
    bool operator < (const JetInfo& lhs, const JetInfo& rhs)
    {
        return (lhs.CorrPt() < rhs.CorrPt());
    }

    std::ostream& operator << (std::ostream& os, const JetInfo& jet_info)
    {
        os << "JetInfo:" << endl;
        os << "jet_pt             = " << jet_info.Pt()           << endl;
        os << "jet_corr_pt        = " << jet_info.CorrPt()       << endl;
        os << "jet_eta            = " << jet_info.CorrP4().eta() << endl;
        os << "jet_phi            = " << jet_info.CorrP4().phi() << endl;
        os << "jet_is_btagged     = " << jet_info.IsBtagged()    << endl;
        os << "jet_btag_disc      = " << jet_info.BtagDisc()     << endl;
        os << "jet_mc_flavor_aglo = " << jet_info.MCFlavorAlgo() << endl;
        os << "jet_mc_flavor_phys = " << jet_info.MCFlavorPhys() << endl;
        os << "jet_mc3_id         = " << jet_info.MC3Id()        << endl;
        os << "jet_mom_id         = " << jet_info.MomId()        << endl;
        return os;
    }

    // determine if btagged (needed for boost::bind)
    bool IsBtagged(const JetInfo& jet_info)
    {
        return jet_info.IsBtagged();
    }

    // find the jet corresponding the p4, return (0,0,0,0) if not found 
    bool JetCorrespondsToP4(const JetInfo& jet_info, const LorentzVector& p4)
    {
        //return (p4 == jet_info.CorrP4());
        return (rt::DeltaR(jet_info.CorrP4(), p4) < 0.0001);
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
         float dr_,
         float min_pt_,
         float max_eta_
    )
        : jet_corrector(NULL)
        , jet_unc(NULL)
        , jet_type(jet_type_)
        , btag_type(btag_type_) 
        , scale_type(scale_type_) 
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
          , deltaR(dr_)
          , min_pt(min_pt_)
          , max_eta(max_eta_)
    {
    }

    // non members
    bool operator == (const JetBaseSelectionArgs& lhs, const JetBaseSelectionArgs& rhs)
    {
        bool result = (lhs.jet_corrector == rhs.jet_corrector)
            && (lhs.jet_unc    == rhs.jet_unc)
            && (lhs.scale_type == rhs.scale_type)
            && (lhs.jet_type   == rhs.jet_type) 
            && (lhs.btag_type  == rhs.btag_type)
            && (rt::is_equal(lhs.deltaR  , rhs.deltaR)) 
            && (rt::is_equal(lhs.min_pt  , rhs.min_pt))
            && (rt::is_equal(lhs.max_eta , rhs.max_eta));
        return result;
    }

    bool operator != (const JetBaseSelectionArgs& lhs, const JetBaseSelectionArgs& rhs)
    {
        return not (lhs==rhs);
    }

    bool operator < (const JetBaseSelectionArgs& lhs, const JetBaseSelectionArgs& rhs)
    {
        if (lhs.jet_corrector != rhs.jet_corrector)      {return lhs.jet_corrector < rhs.jet_corrector; }
        if (lhs.jet_unc    != rhs.jet_unc)               {return lhs.jet_unc    < rhs.jet_unc;          }
        if (lhs.scale_type != rhs.scale_type)            {return lhs.scale_type < rhs.scale_type;       }
        if (lhs.jet_type   != rhs.jet_type)              {return lhs.jet_type   < rhs.jet_type;         }
        if (lhs.btag_type  != rhs.btag_type)             {return lhs.btag_type  < rhs.btag_type;        }
        if (not rt::is_equal(lhs.deltaR  , rhs.deltaR))  {return lhs.deltaR  < rhs.deltaR;              }
        if (not rt::is_equal(lhs.min_pt  , rhs.min_pt))  {return lhs.min_pt  < rhs.min_pt;              }
        if (not rt::is_equal(lhs.max_eta , rhs.max_eta)) {return lhs.max_eta < rhs.max_eta;             }
        return false;
    }

    std::ostream& operator << (std::ostream& os, const JetBaseSelectionArgs& ja)
    {
        os << "jet_corrector = " << ja.jet_corrector << endl;
        os << "jet_unc       = " << ja.jet_unc       << endl;
        os << "scale_type    = " << ja.scale_type    << endl;
        os << "jet_type      = " << ja.jet_type      << endl;
        os << "btag_type     = " << ja.btag_type     << endl;
        os << "deltaR        = " << ja.deltaR        << endl;
        os << "min pt        = " << ja.min_pt        << endl;
        os << "max eta       = " << ja.max_eta       << endl;
        return os;
    }

    // ----------------------------------------------------------------------------- //
    // functions to return the JetInfo collections 
    // ----------------------------------------------------------------------------- //

    // b-tag working points
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

            // max eta --> using corrected p4
            if (fabs(jet_info.CorrP4().eta()) > m_ja.max_eta)
            {
                return false;
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
        static std::map<JetBaseSelectionArgs, std::vector<at::JetInfo> > results_map;

        // keep track if we changed events.  If so, then clear the "results_map".
        static at::DorkyEventIdentifier stored_event = {99999, 99999, 99999};
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
                ja.jet_type != JetType::PF_FAST_CORR && 
                ja.jet_type != JetType::PF_CORR &&
                ja.jet_type != JetType::PF_UNCORR
           )
        {
            throw std::invalid_argument("Only particle flow jets are supported for use with a jet uncertainty corrector!");
        }

        // PF jets 
        if (JetType::PF_CORR or JetType::PF_UNCORR or JetType::PF_FAST_CORR)
        {
            for (size_t jidx = 0; jidx != pfjets_p4().size(); jidx++)
            {
                // does this jet pass the ID?
                if (not passesPFJetID(jidx)) 
                {
                    continue;
                }

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
                        case JetType::PF_CORR:      jet_corr = pfjets_cor().at(jidx);                   break;
                        case JetType::PF_UNCORR:    jet_corr = 1.0; break;
                        case JetType::PF_FAST_CORR: 
                                                    jet_corr = (evt_isRealData() ? pfjets_corL1FastL2L3residual().at(jidx) : pfjets_corL1FastL2L3().at(jidx)); 
                                                    break;
                        default:                    jet_corr = 1.0;
                    }
                }
                LorentzVector jet_corr_p4 = jet_p4 * jet_corr; 

                // JEC uncertainty correction is not defined above |eta| > 5.0
                // never really care about jets above 5.0 anyway
                if (fabs(jet_corr_p4.eta()) > 4.999999)
                {
                    continue;
                }

                // jet uncertainty up/down
                if (ja.scale_type == JetScaleType::JEC_UP or ja.scale_type == JetScaleType::JEC_DOWN)  // if pointer not NULL, use the OTF JEC uncertainty
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

                // jet energy resolution smearing
                if (ja.scale_type == JetScaleType::JER)
                {
                    // JER doesn't work at |eta| > 2.5 (gives nan)
                    if (fabs(jet_corr_p4.eta()) > 2.499999)
                    {
                        continue;
                    }

                    const unsigned int seed = evt_event();
                    jet_corr_p4 = RescaleJetP4JER(jet_corr_p4, seed);
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
                const int jet_mc_flavor_algo = (evt_isRealData() ? -999999 : pfjets_mcflavorAlgo().at(jidx));
                const int jet_mc_flavor_phys = (evt_isRealData() ? -999999 : pfjets_mcflavorPhys().at(jidx));

                // match to MC truth

                LorentzVector jet_mc3_p4; 
                int jet_mc3_id = -999999;
                int jet_mom_id = -999999;
                if (not tas::evt_isRealData())
                {
                    float tmp_gen_dr = 999999.0;
                    int tmp_gen_idx  = -999999;
                    for (size_t gen_idx = 0; gen_idx != genps_p4().size(); gen_idx++) 
                    {
                        if (genps_status().at(gen_idx) != 3)                           {continue;}
                        if (fabs(genps_p4().at(gen_idx).eta()) > jet_sel_args.max_eta) {continue;}
                        if (genps_p4().at(gen_idx).pt() < jet_sel_args.min_pt)         {continue;}
                        if (rt::DeltaR(genps_p4().at(gen_idx), jet_corr_p4) < tmp_gen_dr)
                        {
                            tmp_gen_dr  = rt::DeltaR(genps_p4().at(gen_idx), jet_corr_p4);
                            tmp_gen_idx = gen_idx;
                        }
                    }
                    jet_mc3_id = (tmp_gen_idx>= 0 ? tas::genps_id().at(tmp_gen_idx)        : -999999               );
                    jet_mom_id = (tmp_gen_idx>= 0 ? tas::genps_id_mother().at(tmp_gen_idx) : -999999               );
                    jet_mc3_p4 = (tmp_gen_idx>= 0 ? tas::genps_p4().at(tmp_gen_idx)        : LorentzVector(0,0,0,0));
                }
                else
                {
                    jet_mc3_id = -999999;
                    jet_mom_id = -999999;
                    jet_mc3_p4 = LorentzVector(0,0,0,0);
                }

                // create jet infos
                JetInfo jet_info
                (
                     jet_p4,
                     jet_corr_p4,
                     jet_mc3_p4,
                     jet_is_btagged,
                     jet_btag_disc,
                     jet_mc_flavor_algo,
                     jet_mc_flavor_phys,
                     jet_mc3_id,
                     jet_mom_id
                );

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

    // ----------------------------------------------------------------------------- //
    // rescale the jet energy resolution (JER) 
    // ----------------------------------------------------------------------------- //

    // function that returns the sigma(pT)*pT of the MC jets. those numbers are old,
    // but at least they are in an understandable format.
    // -----------------------------------------------------------------------------
    float getErrPt(const float pt, const float eta)
    {
        float InvPerr2;
        float N = 0.0;
        float S = 0.0;
        float C = 0.0;
        float m = 0.0;
        if(fabs(eta) < 0.5)
        {
            N = 3.96859;
            S = 0.18348;
            C = 0.;
            m = 0.62627;
        } 
        else if(fabs(eta) < 1.0)
        {
            N = 3.55226;
            S = 0.24026;
            C = 0.;
            m = 0.52571;
        } 
        else if(fabs(eta) < 1.5) 
        {
            N = 4.54826;
            S = 0.22652;
            C = 0.;
            m = 0.58963;
        }
        else if(fabs(eta) < 2.0)
        {
            N = 4.62622;
            S = 0.23664;
            C = 0.;
            m = 0.48738;
        }
        else if(fabs(eta) < 2.5)
        {
            N = 2.53324;
            S = 0.34306;
            C = 0.;
            m = 0.28662;
        }
        else if(fabs(eta) < 3.0)
        {
            N = -3.33814;
            S = 0.73360;
            C = 0.;
            m = 0.08264;
        }
        else if(fabs(eta) < 5.0)
        {
            N = 2.95397;
            S = 0.11619;
            C = 0.;
            m = 0.96086;
        }

        // this is the absolute resolution (squared), not sigma(pt)/pt
        // so have to multiply by pt^2, thats why m+1 instead of m-1
        InvPerr2 = (N * fabs(N) ) + (S * S) * pow(pt, m+1) + (C * C) * pt * pt;

        return sqrt(InvPerr2);
    }

    // function to get the jer scale factors. values taken from the twiki: 
    // https://twiki.cern.ch/twiki/bin/view/CMS/JetResolution
    // -------------------------------------------------------------------
    float getJERScale(const float jet_eta)
    {
        const float aeta = fabs(jet_eta);
        if      (aeta < 0.5) {return 1.052;}
        else if (aeta < 1.1) {return 1.057;}
        else if (aeta < 1.7) {return 1.096;}
        else if (aeta < 2.3) {return 1.134;}
        else                 {return 1.288;}

    }

    // smear p4's by the jet energy resolution (JER)
    // note: gives some bogus values for eta > 2.5 (not sure why)
    LorentzVector RescaleJetP4JER(const LorentzVector& jet_p4, const unsigned int seed)
    {
        static TRandom3 random(seed);

        // rescale the jet pt
        const float jer_scale    = getJERScale(jet_p4.eta());
        const float sigma_mc     = getErrPt(jet_p4.pt(), jet_p4.eta())/jet_p4.pt();
        const float jet_rescaled = random.Gaus(1.0, sqrt(jer_scale*jer_scale-1.0)*sigma_mc);
        LorentzVector new_jet_p4 = (jet_p4 * jet_rescaled);

        return new_jet_p4;
    }

    // smear MET's by the jet energy resolution (JER)
    void RescaleMETJER
    (
        float& met,
        float& met_phi,
        const unsigned int seed,
        FactorizedJetCorrector* const jc,
        JetCorrectionUncertainty* const jcu,
        at::JetType::value_type jet_type
    ) 
    {
        static at::JetBaseSelectionArgs jet_args(jc, jcu, jet_type, at::JetBtagType::CSVM, at::JetScaleType::NONE, /*dr=*/0.4, /*min_pt=*/15.0, /*max_eta=*/2.4);
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_args);
        ROOT::Math::XYVector cmet(met*cos(met_phi), met*sin(met_phi));
        for (size_t jidx = 0; jidx != jet_infos.size(); jidx++)
        {
            const LorentzVector& jet_p4     = jet_infos.at(jidx).CorrP4();
            const LorentzVector& new_jet_p4 = RescaleJetP4JER(jet_p4, seed*(jidx+1));

            // propogate to the met
            ROOT::Math::XYVector old_jet(jet_p4.px(), jet_p4.py());
            ROOT::Math::XYVector new_jet(new_jet_p4.px(), new_jet_p4.py());
            cmet = cmet - new_jet + old_jet;

            // rescale the met
            ROOT::Math::XYVector cmet(met*cos(met_phi), met*sin(met_phi));
        }

        // set the new met
        met     = cmet.r();
        met_phi = cmet.phi();

        // done
        return;
    }

} // namespace at

