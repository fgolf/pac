#include "AnalysisLooper.h"

// c++
#include <stdexcept>
#include <algorithm>
#include <fstream>

// cms2
#include "ssSelections.h"
#include "eventSelections.h"
#include "trackSelections.h"
#include "susySelections.h"
#include "mcbtagSFuncert.h"
#include "mcSelections.h"
#include "electronSelections.h"
#include "muonSelections.h"
#include "jetSelections.h"
#include "metSelections.h"
#include "jetcorr/FactorizedJetCorrector.h"
#include "jetcorr/JetCorrectionUncertainty.h"

// Tools
#include "SameSignTree.h"
#include "at/Predicates.h"
#include "at/DileptonHypType.h"
#include "at/DileptonChargeType.h"
#include "at/VtxReweight.h"
#include "at/GoodRun.h"
#include "at/PrintIdIsoInfo.h"
#include "at/MCBtagCount.h"
#include "at/CMS2Tag.h"
#include "rt/RootTools.h"
#include "at/TrackIsoTools.h"
#include "CTable.h"
#include "GenParticleStruct.h"
#include "EfficiencyModelTools.h"
#include "ScaleFactors.h"
#include "TTbarBreakDown.h"
#include "HiggsXsec.h"
#include "SignalBinInfo.h"

// ROOT
#include "Math/LorentzVector.h"
#include "Math/Vector2D.h"
#include "TH2F.h"

// typdefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef std::vector<LorentzVector> vecLorentzVector;

using namespace tas;
using namespace std;
using namespace at;
using namespace ss;

// get the best hyp
struct HypInfo
{
    HypInfo(int i, const at::DileptonChargeType::value_type& c, const at::DileptonHypType::value_type& h);
    int idx;
    at::DileptonChargeType::value_type charge_type;
    at::DileptonHypType::value_type hyp_type;

    // scalar sum pT between the two leptons
    float pt() const;

    // lower means higher priority
    bool operator < (const HypInfo& rhs) const;  
};

HypInfo::HypInfo(int i, const at::DileptonChargeType::value_type& c, const at::DileptonHypType::value_type& h)
    : idx(i)
    , charge_type(c)
    , hyp_type(h)
{
}

float HypInfo::pt() const
{
    if (idx < 0)
    {
        return -999999.0;
    }
    if (static_cast<size_t>(idx) >= hyp_lt_p4().size())
    {
        return -999999.0;
    }
    return (hyp_lt_p4().at(idx).pt() + hyp_ll_p4().at(idx).pt());
}
    
bool HypInfo::operator < (const HypInfo& rhs) const
{
    // charge type
    if (charge_type < rhs.charge_type) {return true;}
    if (charge_type > rhs.charge_type) {return false;}
    
    // hyp type 
    if (hyp_type < rhs.hyp_type) {return true;}
    if (hyp_type > rhs.hyp_type) {return false;}

    // sum pt
    if (pt() > rhs.pt())  {return true;}
    if (pt() <= rhs.pt()) {return false;}

    return false;
}

// check that it passes the ETH fake rate definition
bool passesETHfo(const int lep_id, const int lep_idx, const bool use_el_eta)
{
    if (abs(lep_id) == 13)
    {
        if (!samesign::isGoodLepton(lep_id, lep_idx, use_el_eta)) return false;
        if (muonIsoValuePF2012_deltaBeta(lep_idx) > 1.0) return false;
        return true;
    }
    // NOTE: this is the wrong definition of the electron FO
    // it's here as a place holder
    // see AN-2011/466 v6 for the correct definition
    else if (abs(lep_id) == 11)
    {
        if (!samesign::isGoodLepton(lep_id, lep_idx, use_el_eta)) return false;
        if (samesign::electronIsolationPF2012(lep_idx) > 0.6) return false;
        return true;
    }

    return false;
}

// POG medium working point with pt > 20 and |eta| < 2.4
static const cuts_t electronSelection_pog_medium = 
                       electronSelectionFO_SS_baselineV2   |
                       (1ll<<ELEID_WP2012_MEDIUM_NOISO);

// POG medium working point with pt > 20 and |eta| < 2.4
static const cuts_t electronSelection_pog_loose = 
                       electronSelectionFO_SS_baselineV2   |
                       (1ll<<ELEID_WP2012_LOOSE_NOISO);

// set then numerator bool
bool SSAnalysisLooper::IsNumerator(const int lep_id, const int lep_idx)
{
    return samesign::isNumeratorLepton(lep_id, lep_idx, m_use_el_eta);
}

// set then denominator bool
bool SSAnalysisLooper::IsDenominator(const int lep_id, const int lep_idx)
{
    if (m_analysis_type == AnalysisType::high_pt_eth) 
    {
        return passesETHfo(lep_id, lep_idx, m_use_el_eta);
    }
    else
    {
        return samesign::isDenominatorLepton(lep_id, lep_idx, m_use_el_eta);
    }
}

// set then fake-able object bool
bool SSAnalysisLooper::IsFO(const int lep_id, const int lep_idx)
{
    return IsDenominator(lep_id, lep_idx) && not IsNumerator(lep_id, lep_idx);
}

// use delta R to match
void SetBtagDiscriminator(const vector<LorentzVector>& jets_p4, vector<float>& jets_disc, enum BtagType btag_type)
{
    using namespace tas;

    if (jets_p4.empty())
    {
        return;
    }
    jets_disc.clear();
    const vector<float>& btags = pfjets_combinedSecondaryVertexBJetTag();
    for (size_t j = 0; j < jets_p4.size(); j++)
    {
        for (size_t i = 0; i < pfjets_p4().size(); i++)
        { 
            if (rt::DeltaR(pfjets_p4().at(i), jets_p4.at(j)) < 0.0001) 
            {
                jets_disc.push_back(btags.at(i));
                break;
            }
        }
    }
    return;
}

// void PrintJetInfo(const std::string& label, const vector<LorentzVector>& jets_p4)
// {
//     cout << label << ":" << endl;
//     float sum_pt = 0.0;
//     for (size_t i = 0; i < jets_p4.size(); i++)
//     {
//         LorentzVector jet_p4 = jets_p4.at(i);
//         cout << Form("idx %d, pt %f, eta %f, phi %f", (int)i, jet_p4.pt(), jet_p4.eta(), jet_p4.phi()) << endl;
//         sum_pt += jet_p4.pt();
//     }
//     cout << "sum jet pt = " << sum_pt << endl;
// }


//std::vector<float> GetJetCorrValue(const std::vector<bool>& vjets_flags, jet_corrector)
//{
//    // now impose the pt requirement after applying the extra corrections
//    std::vector<float> final_jets;
//    for (unsigned int jidx = 0; jidx < vjets_flags.size(); jidx++)
//    {
//        if (!vjets_flags.at(jidx))
//        {
//            continue;
//        }
//
//        float jet_cor = 0;
//        if (not jet_corrector)
//        {
//            jet_corrector->setRho(cms2.evt_ww_rho_vor());
//            jet_corrector->setJetA(cms2.pfjets_area().at(jidx));
//            jet_corrector->setJetPt(cms2.pfjets_p4().at(jidx).pt());
//            jet_corrector->setJetEta(cms2.pfjets_p4().at(jidx).eta());        
//            float jet_cor = jet_corrector->getCorrection();
//        }
//        else
//        {
//            jet_cor = (evt_isRealData() ? pfjets_corL1FastL2L3residual().at(jidx) : pfjets_corL1FastL2L3().at(jidx);
//        }
//        final_jets.push_back(vjet);
//    }
//
//    return final_jets;
//}


//std::vector<float> GetJetCorrUncValue(m_evts.vjets_flags, jet_cor_unc.get(), at::YieldType::value_type jes_type)
//{
//    // now impose the pt requirement after applying the extra corrections
//    std::vector<float> final_jets;
//    for (unsigned int jidx = 0; jidx < vjets_flags.size(); jidx++)
//    {
//        if (!vjets_flags.at(jidx))
//        {
//            continue;
//        }
//
//        float jet_unc = 0;
//        const LorentzVector& vjet = cms2.pfjets_p4().at(jidx);
//        if (not jet_corrector)
//        {
//            float jet_cor = jet_corrector->getCorrection();
//            jet_unc->setJetPt(vjet.pt());	 
//            jet_unc->setJetEta(vjet.eta());	 
//        }
//        else
//        {
//            jet_unc = getJetMetSyst(1, vjet.pt(), vjet.eta());
//        }
//        final_jets.push_back(vjet);
//    }
//    return final_jets;
//}


void PrintJetInfo
(
    const std::string& label,
    const vector<LorentzVector>& jets_p4,
    FactorizedJetCorrector* jet_corrector = NULL,
    JetCorrectionUncertainty *jet_unc = NULL,
    at::YieldType::value_type jec_type  = at::YieldType::base,
    at::YieldType::value_type beff_type = at::YieldType::base
)
{
    cout << label << ":" << endl;
    float sum_pt = 0.0;
    for (size_t i = 0; i < jets_p4.size(); i++)
    {
        LorentzVector jet_p4 = jets_p4.at(i);
        cout << Form("idx %d, pt %f, eta %f, phi %f", (int)i, jet_p4.pt(), jet_p4.eta(), jet_p4.phi()) << endl;
        sum_pt += jet_p4.pt();
    }
    cout << "sum jet pt = " << sum_pt << endl;
}


//void PrintJetInfo(const std::string& label, const vector<LorentzVector>& jets_p4, const vector<float>& jets_disc)
//{
//    cout << label << ":" << endl;
//    for (size_t i = 0; i < jets_p4.size(); i++)
//    {
//        LorentzVector jet_p4 = jets_p4.at(i);
//        float disc           = jets_disc.at(i);
//        cout << Form("idx %d, pt %f, eta %f, phi %f, disc %f", (int)i, jet_p4.pt(), jet_p4.eta(), jet_p4.phi(), disc) << endl;
//    }
//}

//void PrintJetInfo(const std::string& label, const vector<LorentzVector>& jets_p4, const vector<LorentzVector>& jets_nearjet_p4,  const vector<float>& jets_nearjet_dr, const vector<float>& jets_disc)
//{
//    cout << Form("%s: (%d, %d, %d)", label.c_str(), (int)jets_p4.size(), (int)jets_nearjet_dr.size(), (int)jets_nearjet_p4.size())  << endl;
//    for (size_t i = 0; i < jets_p4.size(); i++)
//    {
//        LorentzVector jet_p4 = jets_p4.at(i);
//        float disc           = jets_disc.at(i);
//        float nj_pt          = jets_nearjet_p4.at(i).pt();
//        float nj_dr          = jets_nearjet_dr.at(i);
//        cout << Form("idx %d, pt %f, eta %f, phi %f, disc %f, nearjet pt %f, nearjet dr %f", (int)i, jet_p4.pt(), jet_p4.eta(), jet_p4.phi(), disc, nj_pt, nj_dr) << endl;
//    }
//}

void PrintForSync
(
    int ihyp,
    float mu_min_pt,
    float el_min_pt,
    enum JetType jet_type,
    int jet_met_scale,
    bool use_el_eta = true,
    FactorizedJetCorrector *jet_corrector = NULL,
    MetCorrector *met_corrector = NULL
)
{
    // convenience
    const LorentzVector& lt_p4 = hyp_lt_p4().at(ihyp);
    const LorentzVector& ll_p4 = hyp_ll_p4().at(ihyp);
    const int lt_id            = hyp_lt_id().at(ihyp);
    const int ll_id            = hyp_ll_id().at(ihyp);
    const int lt_idx           = hyp_lt_index().at(ihyp);
    const int ll_idx           = hyp_ll_index().at(ihyp);
    const bool lt_passes_id    = samesign::isGoodLepton(lt_id, lt_idx, use_el_eta);
    const bool ll_passes_id    = samesign::isGoodLepton(ll_id, ll_idx, use_el_eta);
    const float lt_iso         = samesign::leptonIsolation(lt_id, lt_idx);
    const float ll_iso         = samesign::leptonIsolation(ll_id, ll_idx);
    const float inv_mass       = (lt_p4 + ll_p4).M();

    // channel names
    const size_t n_channel_names = 4; 
    const std::string channel_names[n_channel_names] = {"All", "MM", "EM", "EE"};

    int num_jets = 0;
    int num_btags = 0;
    float ht = 0.;
    float met = evt_pfmet_type1cor();
    vector<LorentzVector> jets_p4;
    if (not jet_corrector)
    {
        num_jets  = samesign::nJets(ihyp, jet_type                       , /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
        jets_p4   = samesign::getJets(ihyp, jet_type                     , /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
        num_btags = samesign::nBtaggedJets(ihyp, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
        ht        = samesign::sumJetPt(ihyp, jet_type                    , /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, jet_met_scale);
        met       = evt_pfmet_type1cor();
    }
    else
    {
        num_jets  = samesign::nJets(ihyp, jet_corrector, jet_type                       , /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
        jets_p4   = samesign::getJets(ihyp, jet_corrector, jet_type                     , /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
        num_btags = samesign::nBtaggedJets(ihyp, jet_corrector, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
        ht        = samesign::sumJetPt(ihyp, jet_corrector, jet_type                    , /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, jet_met_scale);
        met       = met_corrector->getCorrectedMET().first;
    }

    // print the leptons sorted by pT
    LorentzVector l1_p4        = lt_p4;
    float         l1_pt        = lt_p4.pt();
    int           l1_id        = lt_id;
    int           l1_idx       = lt_idx;
    float         l1_iso       = lt_iso;
    bool          l1_passes_id = lt_passes_id;
    LorentzVector l2_p4        = ll_p4;
    float         l2_pt        = ll_p4.pt();
    int           l2_id        = ll_id;
    int           l2_idx       = ll_idx;
    float         l2_iso       = ll_iso;
    bool          l2_passes_id = ll_passes_id;
    if (l2_pt > l1_pt)
    {
        std::swap(l1_p4        ,l2_p4       );
        std::swap(l1_pt        ,l2_pt       );
        std::swap(l1_id        ,l2_id       );
        std::swap(l1_idx       ,l2_idx      );
        std::swap(l1_iso       ,l2_iso      );
        std::swap(l1_passes_id ,l2_passes_id);
    }

    int type  = at::hyp_typeToHypType(hyp_type().at(ihyp));

    //printf("%11d %7.3f  %6.3f  %5.3f %11d %7.3f %6.3f  %5.3f %13.3f %5d %6d %11.3f \n", ll_id, ll_p4.pt(), ll_p4.eta(), ll_iso, lt_id, lt_p4.pt(), lt_p4.eta(), lt_iso, met, num_jets, num_btags, ht);

    if (samesign::isNumeratorHypothesis(ihyp), use_el_eta)
        //if (samesign::isDenominatorHypothesis(ihyp))
    {
        //cout << "Run | LS | Event | channel | Lep1Pt | Lep1Eta | Lep1Phi | Lep1ID | Lep1Iso | Lep2Pt | Lep2Eta | Lep2Phi | Lep2ID | Lep1Iso | MET | HT | nJets | nbJets" << endl;
        cout << Form("%6u | %3u | %12u | %s | %4.3f | %4.3f | %2.3f | %2.3f | %u | %4.3f | %4.3f | %2.3f | %2.3f | %u | %4.3f | %4.3f | %4.3f | %u | %u",
                     evt_run(), evt_lumiBlock(), evt_event(),
                     channel_names[type].c_str(),
                     inv_mass,
                     l1_p4.pt(), l1_p4.eta(), l1_p4.phi(), l1_passes_id, l1_iso,
                     l2_p4.pt(), l2_p4.eta(), l2_p4.phi(), l2_passes_id, l2_iso,
                     met,
                     ht,
                     num_jets,
                     num_btags) << endl;
    }
    else
    {
        cout << Form("%6u | %3u | %12u | %s | %4.3f | %4.3f | %2.3f | %2.3f | %u | %4.3f | %4.3f | %2.3f | %2.3f | %u | %4.3f | %4.3f | %s | %s | %s",
                     evt_run(), evt_lumiBlock(), evt_event(),
                     channel_names[type].c_str(),
                     inv_mass,
                     l1_p4.pt(), l1_p4.eta(), l1_p4.phi(), l1_passes_id, l1_iso,
                     l2_p4.pt(), l2_p4.eta(), l2_p4.phi(), l2_passes_id, l2_iso,
                     met,
                     "-",
                     "-",
                     "-") << endl;
    }

    //{
    //  cout << "ID lepton 1: "; PrintIdInfo(l1_id, l1_idx, true);
    //  //cout << "ID iso 1: "; PrintIsoInfo(l1_id, l1_idx);
    //  cout << "ID lepton 2: "; PrintIdInfo(l2_id, l2_idx, true);
    //  //cout << "ID iso 2: "; PrintIsoInfo(l2_id, l2_idx);
    //}
    //PrintJetInfo(Form("passing jets for hyp %d", ihyp), jets_p4);
}

// construct:
SSAnalysisLooper::SSAnalysisLooper
(
    const std::string& root_file_name,
    const Sample::value_type& sample,
    const AnalysisType::value_type& analysis_type,
    const std::string& fake_rate_file_name,
    const std::string& flip_rate_file_name,
    const std::string& vtxreweight_file_name,
    const std::string& goodrun_file_name,
    const double luminosity,
    const int njets,
    const bool sparms,
    const int jetMetScale,
    const bool is_fast_sim,
    const bool use_el_eta,
    const bool sync_print,
    const bool verbose,
    const std::string apply_jec_otf,
    const std::string apply_jec_unc,
    const double jet_pt_cut,
    const bool switch_signs
)
    : AnalysisWithTreeAndHist(root_file_name, "tree", "baby tree for SS2012 analysis")
    , m_sample(sample)
    , m_analysis_type(analysis_type)
    , m_lumi(luminosity)
    , m_njets(njets)
    , m_sparms(sparms)
    , m_jetMetScale(jetMetScale)
    , m_is_fast_sim(is_fast_sim)
    , m_use_el_eta(use_el_eta)
    , m_filter_bad_runs(false)
    , m_sync_print(sync_print)
    , m_verbose(verbose || sync_print)
    , m_jet_pt_cut(jet_pt_cut) 
    , m_switch_signs(switch_signs)
    , m_hyp_count(0)
{
    // set vertex weight file
    if (!vtxreweight_file_name.empty())
    {
        cout << "using vertex reweight file : " << vtxreweight_file_name << endl;
        set_vtxreweight_rootfile(vtxreweight_file_name.c_str(), m_verbose);
    }

    // set the "good run" list 
    if (!goodrun_file_name.empty())
    {
        m_filter_bad_runs = true;
        set_goodrun_file(goodrun_file_name.c_str());
        //set_goodrun_file_json(goodrun_file_name.c_str());
    }

    // set the "on-the-fly" JEC
    if (!apply_jec_otf.empty())
    {
        m_list_of_jec_filenames.clear();

        std::string temp_jec_string = rt::string_upper(apply_jec_otf);
        temp_jec_string = rt::string_remove_all(temp_jec_string, "::ALL");
        const at::SampleType::value_type sample_type = at::GetSampleInfo(m_sample).type;

        std::string path = rt::getenv("CMS2CORE");
        if (!path.empty())
        {
            path += "/jetcorr/data/";
            m_list_of_jec_filenames.push_back(Form("%s/%s_L1FastJet_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            m_list_of_jec_filenames.push_back(Form("%s/%s_L2Relative_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            m_list_of_jec_filenames.push_back(Form("%s/%s_L3Absolute_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            if (sample_type == at::SampleType::data)
            {
                m_list_of_jec_filenames.push_back(Form("%s/%s_L2L3Residual_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            }
        }
        else
        {
            path = "./";
            m_list_of_jec_filenames.push_back(Form("%s/%s_L1FastJet_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            m_list_of_jec_filenames.push_back(Form("%s/%s_L2Relative_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            m_list_of_jec_filenames.push_back(Form("%s/%s_L3Absolute_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            if (sample_type == at::SampleType::data)
            {
                m_list_of_jec_filenames.push_back(Form("%s/%s_L2L3Residual_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            }
        }

        printf("[SSAnalysisLooper] making jet and MET correctors with: \n");
        for (unsigned int idx = 0; idx < m_list_of_jec_filenames.size(); idx++)
        {
            if (rt::exists(m_list_of_jec_filenames.at(idx)))
            {
                printf("\t%s\n", m_list_of_jec_filenames.at(idx).c_str());
            }
            else
            {
                printf("\tFILE %s doesn't exist.\n", m_list_of_jec_filenames.at(idx).c_str());
            }
        }
        
        m_jet_corrector.reset(makeJetCorrector(m_list_of_jec_filenames));
        if (not m_jet_corrector)
        {
            throw std::runtime_error("ERROR: SSAnalysisLooper: unable to create jet_corrector");
        }
        m_met_corrector.reset(new MetCorrector(m_list_of_jec_filenames));
        if (not m_met_corrector)
        {
            throw std::runtime_error("ERROR: SSAnalysisLooper: unable to create met_corrector");
        }
    }

    // set the "on-the-fly" Uncertainty
    if (!apply_jec_unc.empty())
    {
        std::string temp_jec_string = rt::string_upper(apply_jec_unc);
        temp_jec_string = rt::string_remove_all(temp_jec_string, "::ALL");

        std::string path = rt::getenv("CMS2CORE");
        if (!path.empty())
        {
            path += "/jetcorr/data";
        }
        else
        {
            path = "./";
        }
        printf("[SSAnalysisLooper] making jet and MET correctors uncertainties with: \n");
        const string jes_unc_file = Form("%s/%s_Uncertainty_AK5PF.txt", path.c_str(), temp_jec_string.c_str());
        if (rt::exists(jes_unc_file))
        {
            printf("\t%s\n", jes_unc_file.c_str());
        }
        else
        {
            printf("\tFILE %s doesn't exist.\nUsing default values hard coded in jetSelections.cc", jes_unc_file.c_str());
        }
        m_jet_corr_unc.reset(new JetCorrectionUncertainty(jes_unc_file));
        if (not m_jet_corr_unc)
        {
            throw std::runtime_error("ERROR: SSAnalysisLooper: unable to create jet_corr_unc");
        }
    }

    // initialize counters
    for (size_t i = 0; i != m_count_ss.size(); i++) {m_count_ss[i]=0.0;}
    for (size_t i = 0; i != m_count_sf.size(); i++) {m_count_sf[i]=0.0;}
    for (size_t i = 0; i != m_count_df.size(); i++) {m_count_df[i]=0.0;}
    for (size_t i = 0; i != m_count_os.size(); i++) {m_count_os[i]=0.0;}

    for (size_t i = 0; i != m_count_nobtag_ss.size(); i++) {m_count_nobtag_ss[i]=0.0;}
    for (size_t i = 0; i != m_count_nobtag_sf.size(); i++) {m_count_nobtag_sf[i]=0.0;}
    for (size_t i = 0; i != m_count_nobtag_df.size(); i++) {m_count_nobtag_df[i]=0.0;}
    for (size_t i = 0; i != m_count_nobtag_os.size(); i++) {m_count_nobtag_os[i]=0.0;}

    // set the fake rate histograms
    std::auto_ptr<TFile> fake_rate_file(rt::OpenRootFile(fake_rate_file_name));
    cout << "using FR file : " << fake_rate_file->GetName() << endl;
    string mufr_name = "";
    string elfr_name = "";
    switch (m_analysis_type)
    {
        case AnalysisType::high_pt:
            mufr_name = "h_mufr40c_ewkcor";
            elfr_name = "h_elfr40c_ewkcor";
            break;
        case AnalysisType::low_pt:
            mufr_name = "h_mufr40c_ewkcor";
            elfr_name = "h_elfr40c_noiso_ewkcor";
            break;
        case AnalysisType::vlow_pt:
            mufr_name = "h_mufr40c_iso_ewkcor";
            elfr_name = "h_elfr40c_noiso_ewkcor";
            break;
        case AnalysisType::high_pt_eth:
            mufr_name = "h_mufr40c";
            elfr_name = "h_elfr40c";
            break;
        case AnalysisType::higgsino:
            mufr_name = "h_mufr40c_ewkcor";
            elfr_name = "h_elfr40c_ewkcor";
            break;
        default:
            mufr_name = "h_mufr40c";
            elfr_name = "h_elfr40c";
            break;
    }
    h_mufr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get(mufr_name.c_str())->Clone()));
    h_elfr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get(elfr_name.c_str())->Clone()));
    if (not h_mufr) {throw std::runtime_error(Form("ERROR: SSAnalysisLooper: %s doesn't exist", mufr_name.c_str()));}
    if (not h_elfr) {throw std::runtime_error(Form("ERROR: SSAnalysisLooper: %s doesn't exist", elfr_name.c_str()));}
    h_mufr->SetDirectory(0);
    h_elfr->SetDirectory(0);

    cout << "[SSAnalysisLooper] using mu FR hist : " << h_mufr->GetName() << endl;
    cout << "[SSAnalysisLooper] using el FR hist : " << h_elfr->GetName() << endl;

    // set the flip rate histograms
    std::auto_ptr<TFile> flip_rate_file(rt::OpenRootFile(flip_rate_file_name));
    cout << "[SSAnalysisLooper] using FL file : " << flip_rate_file->GetName() << endl;
    h_flip.reset(dynamic_cast<TH2F*>(flip_rate_file->Get("flipRate")->Clone()));
    if (not h_flip) {throw std::runtime_error("ERROR: SSAnalysisLooper: flipRate doesn't exist");}
    h_flip->SetDirectory(0);

    cout << "[SSAnalysisLooper] using FL hist : " << h_flip->GetName() << endl;

    // get jet pt cut
    if (m_jet_pt_cut < 0.0f)
    {
        if (m_analysis_type == ss::AnalysisType::higgsino) m_jet_pt_cut = 20.0f;
        else m_jet_pt_cut = 40.0f;
    }
    cout << "[SSAnalysisLooper] using jet pT cut : " << m_jet_pt_cut << endl;

    // are we flipping th sign?
    if (m_switch_signs)
    {
        cout << "[SSAnalysisLooper] switching the meaing of SS and OS (for OS selection)" << endl;
    }

    // begin job
    BeginJob();
}

// destroy:
SSAnalysisLooper::~SSAnalysisLooper()
{
//     delete m_jet_corrector;
//     delete m_met_corrector;
}

// function operator: operate on each event
int SSAnalysisLooper::operator() (long event, const std::string& filename)
{
    // call base class operator
    return Analyze(event, filename);
}

// members:
void SSAnalysisLooper::BeginJob()
{
    // initialize hists
    BookHists();

    // initialize branches
    m_evt.Reset();
    m_evt.SetBranches(*m_tree);

    if (m_sync_print)
    {
        cout << "Run | LS | Event | channel | dilep Mass | " 
                "Lep1Pt | Lep1Eta | Lep1Phi | Lep1ID | Lep1Iso | "
                "Lep2Pt | Lep2Eta | Lep2Phi | Lep2ID | Lep1Iso | "
                "MET | HT | nJets | nbJets" 
             << endl;
    }
}

void SSAnalysisLooper::BookHists()
{
    rt::TH1Container& hc = m_hist_container;

    // generated event count hist
    if (m_sparms)
    {
        ss::SignalBinInfo bin_info = ss::GetSignalBinInfo(m_sample);
        const std::string title = Form("# of Generated Events - %s", ss::GetSignalBinHistLabel(m_sample).c_str());
        hc.Add(new TH2F("h_gen_count", title.c_str(), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    }
}


void SSAnalysisLooper::EndJob()
{
    cout << "Number of dilepton hypotheses passing pT > 20, 20; |eta| < 2.4, 2.4; SS:\t" << m_hyp_count << endl;

    CTable yield_table;
    yield_table.setTitle("yields for SS Analysis 2012 (# btags >= 2)");
    yield_table.useTitle();
    yield_table.setTable() (                      "mm",          "em",          "ee",         "all")
                           ("count ss" , m_count_ss[0], m_count_ss[1], m_count_ss[2], m_count_ss[3]) 
                           ("count sf" , m_count_sf[0], m_count_sf[1], m_count_sf[2], m_count_sf[3]) 
                           ("count df" , m_count_df[0], m_count_df[1], m_count_df[2], m_count_df[3])
                           ("count os" , m_count_os[0], m_count_os[1], m_count_os[2], m_count_os[3]); 
    yield_table.print();

    CTable yield_table2;
    yield_table2.setTitle("yields for SS Analysis 2012 (no btags req)");
    yield_table2.useTitle();
    yield_table2.setTable() (                             "mm",                "em",                 "ee",                "all")
                            ("count ss" , m_count_nobtag_ss[0], m_count_nobtag_ss[1], m_count_nobtag_ss[2], m_count_nobtag_ss[3]) 
                            ("count sf" , m_count_nobtag_sf[0], m_count_nobtag_sf[1], m_count_nobtag_sf[2], m_count_nobtag_sf[3]) 
                            ("count df" , m_count_nobtag_df[0], m_count_nobtag_df[1], m_count_nobtag_df[2], m_count_nobtag_df[3])
                            ("count os" , m_count_nobtag_os[0], m_count_nobtag_os[1], m_count_nobtag_os[2], m_count_nobtag_os[3]); 
    yield_table2.print();

    // call base class end job
    rt::TH1Container& hc = m_hist_container;
    if (m_verbose)
    {
        hc.List();
    }
    
    AnalysisWithTreeAndHist::EndJob();
}

int SSAnalysisLooper::SetJetCorrector(std::vector<std::string> &list_of_filenames)
{
    printf("[SSAnalysisLooper] making jet corrector with: \n");
    for (unsigned int idx = 0; idx < list_of_filenames.size(); idx++)
    {
        printf("\t%s\n", list_of_filenames.at(idx).c_str());
    }

    m_jet_corrector.reset(makeJetCorrector(list_of_filenames));
    m_met_corrector.reset(new MetCorrector(list_of_filenames));
    if (!m_jet_corrector && !m_met_corrector) {return 1;}
    return 0;
}

int SSAnalysisLooper::Analyze(const long event, const std::string& filename)
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    try
    {
        // Reset Tree Variables
        // --------------------------------------------------------------------------------------------------------- //

        m_evt.Reset();

        // set good good runs 
        // --------------------------------------------------------------------------------------------------------- //

        // default is true since it means we're not applying a good run list
        if (m_filter_bad_runs)
        {
            if (tas::evt_isRealData())
            {
                // check for good run and events
                if(!goodrun(tas::evt_run(), tas::evt_lumiBlock())) 
                    //if(!goodrun_json(tas::evt_run(), tas::evt_lumiBlock())) 
                {
                    //if (m_verbose) {cout << "Bad run and lumi:\t" << tas::evt_run() << ", " << tas::evt_lumiBlock() << endl;}
                    //return 0;
                    m_evt.is_good_lumi = false;
                }
                else
                {
                    //if (m_verbose) {cout << "Good run and lumi:\t" << tas::evt_run() << ", " << tas::evt_lumiBlock() << endl;}
                    m_evt.is_good_lumi = true;
                }
            }
        }

        // event logic variables 
        // --------------------------------------------------------------------------------------------------------- //

        // trigger options 
        int trigger_option = -999999;
        switch (m_analysis_type)
        {
            case AnalysisType::high_pt    : trigger_option = 0; break;
            case AnalysisType::high_pt_eth: trigger_option = 0; break;
            case AnalysisType::hcp        : trigger_option = 0; break;
            case AnalysisType::low_pt     : trigger_option = 1; break;
            case AnalysisType::vlow_pt    : trigger_option = 2; break;
            case AnalysisType::higgsino   : trigger_option = 0; break;
            case AnalysisType::static_size: break; // no default is intentional so that compiler issues a warning if you don't handle all the cases
        }

        // lepton pT cut values
        float mu_min_pt = 0.0;
        float el_min_pt = 0.0;
        switch(m_analysis_type)
        {
            case AnalysisType::high_pt:
                mu_min_pt = 20.0;
                el_min_pt = 20.0;
                break;
            case AnalysisType::high_pt_eth:
                mu_min_pt = 20.0;
                el_min_pt = 20.0;
                break;
            case AnalysisType::hcp:
                mu_min_pt = 20.0;
                el_min_pt = 20.0;
                break;
            case AnalysisType::low_pt:
                mu_min_pt = 10.0;
                el_min_pt = 10.0;
                break;
            case AnalysisType::vlow_pt:
                mu_min_pt = 5.0;
                el_min_pt = 10.0;
                break;
            case AnalysisType::higgsino:
                mu_min_pt = 10.;
                el_min_pt = 10.;
                break;
            default:
                mu_min_pt = 20.0;
                el_min_pt = 20.0;
                break;
        }
        const float min_pt = std::min(mu_min_pt, el_min_pt);

        // gen level  
        // --------------------------------------------------------------------------------------------------------- //

        if (not evt_isRealData())
        {
            // xsec is a special case for the higgs backgrounds
            if (m_sample == Sample::wh_zh_tth_hzz || m_sample == Sample::wh_zh_tth_hww || m_sample == Sample::wh_zh_tth_htt)
            {
                const ss::HiggsProduction::value_type higgs_production = ss::GetHiggsProduction();
                const ss::HiggsDecay::value_type higgs_decay           = ss::GetHiggsDecay();
                m_evt.higgs_bkdn          = static_cast<int>(higgs_production);
                m_evt.higgs_decay         = static_cast<int>(higgs_decay);
//                 m_evt.event_info.xsec     = ss::GetHiggsXsec(higgs_production, higgs_decay);
//                 m_evt.event_info.scale1fb = ss::GetHiggsScale1fb(m_sample, higgs_production, higgs_decay, m_evt.event_info.nevts);

                if (m_verbose) {cout << "AnalysisLooper: Higgs Process = " << higgs_production << endl;} 
                if (m_verbose) {cout << "AnalysisLooper: Higgs Decay = "   << higgs_decay      << endl;} 
            }

            // sparms parameters
            if (m_sparms) 
            {
                const size_t n_sparms = sparm_values().size();
                if (n_sparms > 0) {m_evt.sparm0 = sparm_values().at(0); m_evt.sparm0_name = static_cast<TString>(sparm_names().at(0));}
                if (n_sparms > 1) {m_evt.sparm1 = sparm_values().at(1); m_evt.sparm1_name = static_cast<TString>(sparm_names().at(1));}
                if (n_sparms > 2) {m_evt.sparm2 = sparm_values().at(2); m_evt.sparm2_name = static_cast<TString>(sparm_names().at(2));}
                if (n_sparms > 3) {m_evt.sparm3 = sparm_values().at(3); m_evt.sparm3_name = static_cast<TString>(sparm_names().at(3));}

                // fill the generated event count
                // --------------------------------------------------------------------------------------------------------- //
                hc["h_gen_count"]->Fill(m_evt.sparm0, m_evt.sparm1);
            }

            // lepton variables
            std::pair<GenParticleStruct, GenParticleStruct> best_gen_hyp = efftools::getGenHyp(min_pt, min_pt, DileptonChargeType::static_size);
            if (best_gen_hyp.first.id_ == 0 || best_gen_hyp.second.id_ == 0)
            {
                if (m_verbose) {cout << "AnalysisLooper: does not have a good gen hyp" << endl;} 
                m_evt.gen_dilep_type = at::DileptonHypType::static_size; 
            }
            else
            {
                int   id1  = abs(best_gen_hyp.first.id_ ) == 15 ? best_gen_hyp.first.did_   : best_gen_hyp.first.id_;
                int   idx1 = abs(best_gen_hyp.first.id_ ) == 15 ? best_gen_hyp.first.didx_  : best_gen_hyp.first.idx_;
                int   id2  = abs(best_gen_hyp.second.id_) == 15 ? best_gen_hyp.second.did_  : best_gen_hyp.second.id_;
                int   idx2 = abs(best_gen_hyp.second.id_) == 15 ? best_gen_hyp.second.didx_ : best_gen_hyp.second.idx_;

                // get LorenzVectors
                LorentzVector p41;
                if (abs(best_gen_hyp.first.id_) == 15)
                { 
                    p41 = genps_lepdaughter_p4().at(best_gen_hyp.first.idx_).at(idx1);
                }
                else
                {
                    p41 = genps_p4().at(idx1);
                }

                LorentzVector p42;
                if (abs(best_gen_hyp.second.id_) == 15)
                {
                    p42 = genps_lepdaughter_p4().at(best_gen_hyp.second.idx_).at(idx2);
                }
                else
                {
                    p42 = genps_p4().at(idx2);
                }

                m_evt.is_gen_pp      = id1<0 && id2<0;  // -11 is a positron, 11 is an electron
                m_evt.is_gen_mm      = id1>0 && id2>0;  // -11 is a positron, 11 is an electron
                m_evt.gen_lep1_p4    = p41.pt() > p42.pt() ? p41 : p42;
                m_evt.gen_lep1_pdgid = p41.pt() > p42.pt() ? id1 : id1;
                m_evt.gen_lep2_p4    = p41.pt() > p42.pt() ? p42 : p41;
                m_evt.gen_lep2_pdgid = p41.pt() > p42.pt() ? id2 : id1;
                m_evt.gen_dilep_p4   = (p41 + p42);
                m_evt.gen_dilep_type = efftools::getHypType(id1, id2);
                m_evt.gen_dilep_mass = m_evt.gen_dilep_p4.mass();
                m_evt.gen_dilep_dphi = rt::DeltaPhi(p41, p42); 
                m_evt.gen_dilep_deta = rt::DeltaEta(p41, p42); 
                m_evt.gen_dilep_dr   = rt::DeltaR(p41, p42); 
            }

            // gen jets
            m_evt.vgenb_p4    = efftools::getGenBjets(m_jet_pt_cut, 2.4);
            m_evt.vgenjets_p4 = efftools::getGenJets(m_jet_pt_cut, 2.4);
            m_evt.gen_ht      = efftools::getGenHT(m_jet_pt_cut, 2.4);
            m_evt.gen_nbtags  = m_evt.vgenb_p4.size();
            m_evt.gen_njets   = m_evt.vgenjets_p4.size();
        }
        

        // Event Cleaning
        // --------------------------------------------------------------------------------------------------------- //

        // require at least 3 tracks in the event
        //if (trks_trk_p4().size() < 3)
        //{
        //    if (m_verbose) {std::cout << "fails # trks >= 3 requirement" << std::endl;}
        //    return 0;
        //}

        // require standard cleaning 
        if (!cleaning_standardNovember2011()) 
        {
            if (m_verbose) {std::cout << "fails November2011 cleaning requirement" << std::endl;}
            m_tree->Fill();
            return 0;
        }

        // Analysis Selections
        // --------------------------------------------------------------------------------------------------------- //

        // jet type
        JetType jet_type = evt_isRealData() ? JETS_TYPE_PF_FAST_CORR_RESIDUAL : JETS_TYPE_PF_FAST_CORR;

        if (m_sync_print)
        {
            cout << "number of dilep pairs: " << hyp_type().size() << endl;
        }

        // loop over hypotheses
        HypInfo best_hyp((hyp_type().empty() ? -1 : 0), DileptonChargeType::static_size, DileptonHypType::static_size);
        for (size_t ihyp = 0; ihyp != hyp_type().size(); ihyp++)
        {                
            // leptons variables
            const LorentzVector& lt_p4 = hyp_lt_p4().at(ihyp);
            const LorentzVector& ll_p4 = hyp_ll_p4().at(ihyp);
            int lt_id                  = hyp_lt_id().at(ihyp);
            int ll_id                  = hyp_ll_id().at(ihyp);
            int lt_idx                 = hyp_lt_index().at(ihyp);
            int ll_idx                 = hyp_ll_index().at(ihyp);

            const float lt_min_pt = abs(lt_id)==11 ? el_min_pt : mu_min_pt;
            const float ll_min_pt = abs(ll_id)==11 ? el_min_pt : mu_min_pt;

            // print for syncing
            if (m_sync_print)
            {
                cout << "printing for hyp index " << ihyp << endl;
                PrintForSync(ihyp, mu_min_pt, el_min_pt, jet_type, m_jetMetScale, m_use_el_eta, m_jet_corrector.get(), m_met_corrector.get());
            }

            // check if hyp passes lepton kinematics
            if (fabs(lt_p4.Eta())>2.4 || lt_p4.pt()<lt_min_pt) 
            {
                if (m_verbose) {std::cout << "lt fails lepton kinematics cut" << std::endl;}
                continue;
            }
            if (fabs(ll_p4.Eta())>2.4 || ll_p4.pt()<ll_min_pt) 
            {
                if (m_verbose) {std::cout << "ll fails lepton kinematics cut" << std::endl;}
                continue;
            }

            // check hyp mass (no low mass resonances)
            float dilep_mass = sqrt(fabs(hyp_p4().at(ihyp).mass2()));
            if (dilep_mass < 8.0) 
            {
                if (m_verbose) {std::cout << "fails dilepton invariant mass requirement" << std::endl;}
                continue;
            }

            // check if hyp passes trigger
            if (evt_isRealData() && !samesign::passesTrigger(hyp_type().at(ihyp), trigger_option))
            {
                if (m_verbose) {std::cout << "fails trigger requirement" << std::endl;}
                continue;
            }            

            // check that leptons are from the same vertex
            if (!hypsFromFirstGoodVertex(ihyp))
            {
                if (m_verbose) {std::cout << "fails leptons are from the first good vertex requirement" << std::endl;}
                continue;
            }

            // check extra Z veto
            if (samesign::makesExtraZ(ihyp))
            {
                if (m_verbose) {std::cout << "fails extra Z veto requirement" << std::endl;}
                continue;
            }

            // check if event passes num_jet cut (hard coded)
            int num_jets = samesign::nJets(ihyp, jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
            if (evt_isRealData() && num_jets < m_njets)
            {
                if (m_verbose) {std::cout << "fails # jets >= " << 2 << " requirement with " << num_jets << " jets" << std::endl;}
                continue;
            }

            // check extra Gamma* veto
            if (samesign::makesExtraGammaStar(ihyp) && m_analysis_type != ss::AnalysisType::higgsino)
            {
                if (m_verbose) {std::cout << "fails extra Gamma* veto requirement" << std::endl;}
                continue;
            }

            // skip if both are not denominators
            if (m_analysis_type == AnalysisType::high_pt_eth)
            {
                if (not passesETHfo(lt_id, lt_idx, m_use_el_eta) || not passesETHfo(ll_id, ll_idx, m_use_el_eta))
                {
                    if (m_verbose) {std::cout << "fails both leptons are at least ETH denominator requirement" << std::endl;}
                    continue;
                }                    
            }
            else
            {
                if (!samesign::isDenominatorHypothesis(ihyp, m_use_el_eta))
                {
                    if (m_verbose) {std::cout << "fails both leptons are at least denominator requirement" << std::endl;}
                    continue;
                }
            }

            // get the hyp type
            DileptonHypType::value_type type = hyp_typeToHypType(hyp_type().at(ihyp));

            // OS (Here a kludge by Claudio to quickly change the meaning of SS and OS .... useful for ttbar as sstop)
            int dummy = (m_switch_signs ? -1 : 1);
            int hyp_q = dummy * hyp_lt_charge().at(ihyp) * hyp_ll_charge().at(ihyp);
            if (hyp_q < 0)
            {
                if (m_verbose) {std::cout << "selected OS hyp" << std::endl;}
                if (!samesign::isNumeratorHypothesis(ihyp, m_use_el_eta))
                {
                    if (m_verbose) {std::cout << "OS hyp doesn't pass ID/ISO requirement" << std::endl;}
                    continue; 
                }
                best_hyp = std::min(best_hyp, HypInfo(ihyp, DileptonChargeType::OS, type));
            }
            else if (hyp_q > 0)
            {
                // same sign event (SS)
                if (samesign::isNumeratorHypothesis(ihyp, m_use_el_eta))
                {
                    m_hyp_count++;
                    if (m_verbose) {std::cout << "selected SS hyp" << std::endl;}
                    best_hyp = std::min(best_hyp, HypInfo(ihyp, DileptonChargeType::SS, type));
                }
                // single fake event (SF)
                else if (samesign::isNumeratorLepton(lt_id, lt_idx, m_use_el_eta) || samesign::isNumeratorLepton(ll_id, ll_idx, m_use_el_eta))
                {
                    if (m_verbose) {std::cout << "selected SF hyp" << std::endl;}
                    best_hyp = std::min(best_hyp, HypInfo(ihyp, DileptonChargeType::SF, type));
                }
                // double fake event (DF)
                else
                {
                    if (m_verbose) {std::cout << "selected DF hyp" << std::endl;}
                    best_hyp = std::min(best_hyp, HypInfo(ihyp, DileptonChargeType::DF, type));
                }
            }

        } // end looper over hypothesis
        
        if (m_verbose) {std::cout << "end of hypothesis loop" << std::endl;}

        // Set Tree Variables
        // --------------------------------------------------------------------------------------------------------- //

        // best hyp index
        int hyp_idx = best_hyp.idx;
        const DileptonChargeType::value_type charge_type = best_hyp.charge_type;

        // all: 0, mm: 1, em: 2, ee: 3
        const DileptonHypType::value_type dilepton_type = ((hyp_idx < 0 or hyp_p4().empty()) ? DileptonHypType::static_size : hyp_typeToHypType(hyp_type().at(hyp_idx)));

        // write events to the tree for book keeping
        if (charge_type == DileptonChargeType::static_size)
        {
            if (m_verbose) {std::cout << "fails good event type requirement" << std::endl;}

            // fill event level info 
            m_evt.dilep_type = DileptonHypType::static_size;
            m_evt.charge_type = -999999;
            m_evt.event_info.FillCommon(m_sample, filename);

            // fill the dilepton analysis independent variables 
            if (not hyp_p4().empty())
            {
                m_evt.FillCommon(hyp_idx);

                // ttbar breakdown: ttdil = 0, ttotr = 1, ttslb = 2, ttslo = 3, not set = 4
                m_evt.ttbar_bkdn = GetTTbarBreakDown(m_sample, m_evt.lep1.is_fromw, m_evt.lep2.is_fromw); 
            }

            // fill the tree with what we have
            m_tree->Fill();

            // go to the next event
            return 0;
        }
        else
        {
            if (m_verbose) {std::cout << "passes good dilepton type requirement: " << at::GetDileptonHypTypeName(dilepton_type) << std::endl;}
            if (m_verbose) {std::cout << "passes good charge type requirement:  "  << at::GetDileptonChargeTypeName(charge_type) << std::endl;}
            if (m_verbose) {std::cout << "good hyp index is : " << hyp_idx << std::endl;}
        }

        // convenience trigger info
        switch(m_analysis_type)
        {
            case AnalysisType::high_pt:
                m_evt.trig_mm = passUnprescaledHLTTriggerPattern("HLT_Mu17_Mu8_v");
                m_evt.trig_em = passUnprescaledHLTTriggerPattern("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v") || 
                                passUnprescaledHLTTriggerPattern("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
                m_evt.trig_ee = passUnprescaledHLTTriggerPattern("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
                break;
            case AnalysisType::high_pt_eth:
                m_evt.trig_mm = passUnprescaledHLTTriggerPattern("HLT_Mu17_Mu8_v");
                m_evt.trig_em = passUnprescaledHLTTriggerPattern("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v") || 
                                passUnprescaledHLTTriggerPattern("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
                m_evt.trig_ee = passUnprescaledHLTTriggerPattern("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
                break;
            case AnalysisType::hcp:
                m_evt.trig_mm = passUnprescaledHLTTriggerPattern("HLT_Mu17_Mu8_v");
                m_evt.trig_em = passUnprescaledHLTTriggerPattern("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v") || 
                                passUnprescaledHLTTriggerPattern("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
                m_evt.trig_ee = passUnprescaledHLTTriggerPattern("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
                break;
            case AnalysisType::low_pt:
                m_evt.trig_mm = passUnprescaledHLTTriggerPattern("HLT_DoubleMu8_Mass8_PFNoPUHT175_v") ||
                                passUnprescaledHLTTriggerPattern("HLT_DoubleMu8_Mass8_PFHT175_v");
                m_evt.trig_ee = passUnprescaledHLTTriggerPattern("HLT_DoubleEle8_CaloIdT_TrkIdVL_Mass8_PFNoPUHT175_v") ||
                                passUnprescaledHLTTriggerPattern("HLT_DoubleEle8_CaloIdT_TrkIdVL_Mass8_PFHT175_v");
                m_evt.trig_em = passUnprescaledHLTTriggerPattern("HLT_Mu8_Ele8_CaloIdT_TrkIdVL_Mass8_PFNoPUHT175_v") ||
                                passUnprescaledHLTTriggerPattern("HLT_Mu8_Ele8_CaloIdT_TrkIdVL_Mass8_PFHT175_v");
                break;
            case AnalysisType::vlow_pt:
                m_evt.trig_mm = passUnprescaledHLTTriggerPattern("HLT_DoubleRelIso1p0Mu5_Mass8_PFNoPUHT175_v") ||
                                passUnprescaledHLTTriggerPattern("HLT_DoubleRelIso1p0Mu5_Mass8_PFHT175_v");
                m_evt.trig_ee = passUnprescaledHLTTriggerPattern("HLT_DoubleEle8_CaloIdT_TrkIdVL_Mass8_PFNoPUHT175_v") ||
                                passUnprescaledHLTTriggerPattern("HLT_DoubleEle8_CaloIdT_TrkIdVL_Mass8_PFHT175_v");
                m_evt.trig_em = passUnprescaledHLTTriggerPattern("HLT_RelIso1p0Mu5_Ele8_CaloIdT_TrkIdVL_Mass8_PFHT175_v") ||
                                passUnprescaledHLTTriggerPattern("HLT_RelIso1p0Mu5_Ele8_CaloIdT_TrkIdVL_Mass8_PFNoPUHT175_v");
                break;
            case AnalysisType::higgsino:
                m_evt.trig_mm = passUnprescaledHLTTriggerPattern("HLT_Mu17_Mu8_v");
                m_evt.trig_em = passUnprescaledHLTTriggerPattern("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v") || 
                                passUnprescaledHLTTriggerPattern("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
                m_evt.trig_ee = passUnprescaledHLTTriggerPattern("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
                break;
            default: {/*do nothing*/}
        }

        // individual triggers: mm
        m_evt.trig_mm_mu17_mu8                     = passUnprescaledHLTTriggerPattern("HLT_Mu17_Mu8_v"                            );
        m_evt.trig_mm_dmu8_m8_pfht175              = passUnprescaledHLTTriggerPattern("HLT_DoubleMu8_Mass8_PFHT175_v"             );
        m_evt.trig_mm_dmu8_m8_pfnopuht175          = passUnprescaledHLTTriggerPattern("HLT_DoubleMu8_Mass8_PFNoPUHT175_v"         );
        m_evt.trig_mm_dreliso1p0mu5_m8_pfht175     = passUnprescaledHLTTriggerPattern("HLT_DoubleRelIso1p0Mu5_Mass8_PFHT175_v"    );
        m_evt.trig_mm_dreliso1p0mu5_m8_pfnopuht175 = passUnprescaledHLTTriggerPattern("HLT_DoubleRelIso1p0Mu5_Mass8_PFNoPUHT175_v");

        // individual triggers: ee
        m_evt.trig_ee_el17_el8_id_iso        = passUnprescaledHLTTriggerPattern("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
        m_evt.trig_ee_del8_id_m8_pfnopuht175 = passUnprescaledHLTTriggerPattern("HLT_DoubleEle8_CaloIdT_TrkIdVL_Mass8_PFNoPUHT175_v"                                    );
        m_evt.trig_ee_del8_id_m8_pfht175     = passUnprescaledHLTTriggerPattern("HLT_DoubleEle8_CaloIdT_TrkIdVL_Mass8_PFHT175_v"                                        );

        // individual triggers: em
        m_evt.trig_em_mu17_el8_id_iso                  = passUnprescaledHLTTriggerPattern("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v"       );
        m_evt.trig_em_mu8_el17_id_iso                  = passUnprescaledHLTTriggerPattern("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v"       );
        m_evt.trig_em_mu8_el8_id_m8_pfht175            = passUnprescaledHLTTriggerPattern("HLT_Mu8_Ele8_CaloIdT_TrkIdVL_Mass8_PFHT175_v"             );
        m_evt.trig_em_mu8_el8_id_m8_pfnopuht175        = passUnprescaledHLTTriggerPattern("HLT_Mu8_Ele8_CaloIdT_TrkIdVL_Mass8_PFNoPUHT175_v"         );
        m_evt.trig_em_riso1p0mu5_el8_id_m8_pfht175     = passUnprescaledHLTTriggerPattern("HLT_RelIso1p0Mu5_Ele8_CaloIdT_TrkIdVL_Mass8_PFHT175_v"    );
        m_evt.trig_em_riso1p0mu5_el8_id_m8_pfnopuht175 = passUnprescaledHLTTriggerPattern("HLT_RelIso1p0Mu5_Ele8_CaloIdT_TrkIdVL_Mass8_PFNoPUHT175_v");


        // convenience
        switch (dilepton_type)
        {
            case DileptonHypType::MUMU: m_evt.trig_hpt = m_evt.trig_mm; break;
            case DileptonHypType::EMU : m_evt.trig_hpt = m_evt.trig_em; break;
            case DileptonHypType::EE  : m_evt.trig_hpt = m_evt.trig_ee; break;
            default: {/*do nothing*/}
        };
        switch (dilepton_type)
        {
            case DileptonHypType::MUMU: m_evt.trig_lpt = (m_evt.trig_mm_dmu8_m8_pfnopuht175 || m_evt.trig_mm_dmu8_m8_pfht175)             ; break;
            case DileptonHypType::EMU : m_evt.trig_lpt = (m_evt.trig_em_mu8_el8_id_m8_pfnopuht175 || m_evt.trig_em_mu8_el8_id_m8_pfht175) ; break;
            case DileptonHypType::EE  : m_evt.trig_lpt = (m_evt.trig_ee_del8_id_m8_pfnopuht175 || m_evt.trig_ee_del8_id_m8_pfht175)       ; break;
            default: {/*do nothing*/}
        };
        switch (dilepton_type)
        {
            case DileptonHypType::MUMU: m_evt.trig_lpt_isomu = (m_evt.trig_mm_dreliso1p0mu5_m8_pfnopuht175 || m_evt.trig_mm_dreliso1p0mu5_m8_pfht175)         ; break;
            case DileptonHypType::EMU : m_evt.trig_lpt_isomu = (m_evt.trig_em_riso1p0mu5_el8_id_m8_pfnopuht175 || m_evt.trig_em_riso1p0mu5_el8_id_m8_pfht175) ; break;
            case DileptonHypType::EE  : m_evt.trig_lpt_isomu = (m_evt.trig_ee_del8_id_m8_pfnopuht175 || m_evt.trig_ee_del8_id_m8_pfht175)                     ; break;
            default: {/*do nothing*/}
        };

        // event wieghts 

        //float vtxw  = evt_isRealData() ? 1.0 : vtxweight_n(numberOfGoodVertices(), evt_isRealData(), false);
        float vtxw  = 1.0;
        const float scale1fb = evt_isRealData() ? 1.0 : m_evt.event_info.scale1fb;
        float scale          = evt_isRealData() ? 1.0 : m_lumi * scale1fb * vtxw; 

        // fill event level info 
        m_evt.event_info.FillCommon(m_sample, filename);

        // fill the dilepton analysis independent variables 
        m_evt.FillCommon(hyp_idx);

        // ttbar breakdown: ttdil = 0, ttotr = 1, ttslb = 2, ttslo = 3, not set = 4
        m_evt.ttbar_bkdn = GetTTbarBreakDown(m_sample, m_evt.lep1.is_fromw, m_evt.lep2.is_fromw); 

        // fill analysis specific branches 
        m_evt.vtxw = vtxw;

        // event level info
        if (not m_jet_corrector)
        {
            m_evt.event_info.pfmet          = evt_pfmet_type1cor();  // do we ever use the uncorrected pfmet?
            m_evt.event_info.pfmet_phi      = evt_pfmetPhi_type1cor();
        }
        else
        {
            std::pair<float, float> pcor_met = m_met_corrector->getCorrectedMET();
            m_evt.event_info.pfmet = pcor_met.first;
            m_evt.event_info.pfmet_phi = pcor_met.second;
        }
        m_evt.event_info.uncorpfmet     = evt_pfmet();
        m_evt.event_info.uncorpfmet_phi = evt_pfmetPhi();
        const float met                 = m_evt.event_info.pfmet;
        const float met_phi             = m_evt.event_info.pfmet_phi;
        
        // SS specific event level info
        m_evt.mt           = rt::Mt(m_evt.lep1.p4, met, met_phi);  // calculated against the higher pT lepton
        m_evt.no_extraz    = (not samesign::makesExtraZ(hyp_idx));

        if (not m_jet_corrector)
        {
            m_evt.ht           = samesign::sumJetPt    (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.ht20         = samesign::sumJetPt    (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.ht30         = samesign::sumJetPt    (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.njets        = samesign::nJets       (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.njets20      = samesign::nJets       (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.njets30      = samesign::nJets       (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nbtags       = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nbtags20     = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nbtags30     = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nbtags_csvl  = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVL, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
        }
        else
        {
            FactorizedJetCorrector* const jc = m_jet_corrector.get();
            m_evt.ht           = samesign::sumJetPt    (hyp_idx, jc, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.ht20         = samesign::sumJetPt    (hyp_idx, jc, jet_type,                /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.ht30         = samesign::sumJetPt    (hyp_idx, jc, jet_type,                /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.njets        = samesign::nJets       (hyp_idx, jc, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.njets20      = samesign::nJets       (hyp_idx, jc, jet_type,                /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.njets30      = samesign::nJets       (hyp_idx, jc, jet_type,                /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nbtags       = samesign::nBtaggedJets(hyp_idx, jc, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nbtags20     = samesign::nBtaggedJets(hyp_idx, jc, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nbtags30     = samesign::nBtaggedJets(hyp_idx, jc, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nbtags_csvl  = samesign::nBtaggedJets(hyp_idx, jc, jet_type, JETS_BTAG_CSVL,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
        }

        m_evt.no_extrag    = (not samesign::makesExtraGammaStar(hyp_idx));
        m_evt.hyp_good_vtx = hypsFromFirstGoodVertex(hyp_idx);
        m_evt.clean        = cleaning_standardNovember2011(); 
        m_evt.presel       = (m_evt.no_extraz && m_evt.no_extrag && m_evt.clean && m_evt.hyp_good_vtx);

        // set lepton info (lep1 is higher pT lepton, lep2 is lower pT lepton)
        int lt_id  = cms2.hyp_lt_id().at(hyp_idx);
        int lt_idx = cms2.hyp_lt_index().at(hyp_idx); 
        float lt_pt = hyp_lt_p4().at(hyp_idx).pt();
        int ll_id  = cms2.hyp_ll_id().at(hyp_idx);
        int ll_idx = cms2.hyp_ll_index().at(hyp_idx); 
        float ll_pt = hyp_ll_p4().at(hyp_idx).pt();

        bool lt_num = IsNumerator(lt_id, lt_idx);  
        bool lt_den = IsDenominator(lt_id, lt_idx);
        bool lt_fo  = IsFO(lt_id, lt_idx);
        bool ll_num = IsNumerator(ll_id, ll_idx);  
        bool ll_den = IsDenominator(ll_id, ll_idx);
        bool ll_fo  = IsFO(ll_id, ll_idx);

        int lep1_id;
        int lep1_idx;
        int lep2_id;
        int lep2_idx;
        bool lep1_fo = false;
        bool lep1_num = false;
        bool lep1_den = false;
        bool lep2_fo = false;
        bool lep2_num = false;
        bool lep2_den = false;
        if (lt_pt > ll_pt)
        {
            lep1_id  = cms2.hyp_lt_id().at(hyp_idx);
            lep1_idx = cms2.hyp_lt_index().at(hyp_idx); 
            lep1_fo  = lt_fo;
            lep1_num = lt_num;
            lep1_den = lt_den;
            lep2_id  = cms2.hyp_ll_id().at(hyp_idx);    
            lep2_idx = cms2.hyp_ll_index().at(hyp_idx); 
            lep2_fo  = ll_fo;
            lep2_num = ll_num;
            lep2_den = ll_den;
        }
        else
        {
            lep1_id  = cms2.hyp_ll_id().at(hyp_idx);
            lep1_idx = cms2.hyp_ll_index().at(hyp_idx); 
            lep1_fo  = ll_fo;
            lep1_num = ll_num;
            lep1_den = ll_den;
            lep2_id  = cms2.hyp_lt_id().at(hyp_idx);    
            lep2_idx = cms2.hyp_lt_index().at(hyp_idx); 
            lep2_fo  = lt_fo;
            lep2_num = lt_num;
            lep2_den = lt_den;
        }
        bool lep1_is_mu = (abs(lep1_id)==13);
        bool lep1_is_el = (abs(lep1_id)==11);
        bool lep2_is_mu = (abs(lep2_id)==13);
        bool lep2_is_el = (abs(lep2_id)==11);

        m_evt.lep1.cordetiso   = m_evt.lep1.detiso   - (log(m_evt.lep1.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep1.p4.pt()); // check that I have the correct formula 
        m_evt.lep1.cordetiso04 = m_evt.lep1.detiso04 - (log(m_evt.lep1.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep1.p4.pt()); // check that I have the correct formula 
        m_evt.lep1.corpfiso    = samesign::leptonIsolation(lep1_id, lep1_idx);
        m_evt.lep1.corpfiso04  = (lep1_is_el) ? samesign::electronIsolationPF2012_cone04(lep1_idx) : -999999.0;  
        m_evt.lep1.effarea     = samesign::EffectiveArea03(lep1_id, lep1_idx); 
        m_evt.lep1.effarea04   = samesign::EffectiveArea04(lep1_id, lep1_idx);
        m_evt.lep1.dbeta       = (lep1_is_mu) ? mus_isoR03_pf_PUPt().at(lep1_idx) : -99999.0;
        m_evt.lep1.dbeta04     = (lep1_is_mu) ? mus_isoR04_pf_PUPt().at(lep1_idx) : -99999.0;
        m_evt.lep1.is_fo       = lep1_fo;
        m_evt.lep1.is_num      = lep1_num;
        m_evt.lep1.is_den      = lep1_den;
        //m_evt.lep1.is_conv     = false; 
        m_evt.lep1.mt          = rt::Mt(m_evt.lep1.p4, met, met_phi);
        m_evt.lep1.passes_id   = samesign::isGoodLepton(lep1_id, lep1_idx, m_use_el_eta);
        m_evt.lep1.passes_iso  = samesign::isIsolatedLepton(lep1_id, lep1_idx);
        m_evt.lep1_wfr         = GetFakeRateValue(lep1_id, lep1_idx);
        m_evt.lep1_wflip       = GetFlipRateValue(lep1_id, lep1_idx);

        m_evt.lep2.cordetiso   = m_evt.lep2.detiso   - (log(m_evt.lep2.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep2.p4.pt()); // check that I have the correct formula 
        m_evt.lep2.cordetiso04 = m_evt.lep2.detiso04 - (log(m_evt.lep2.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep2.p4.pt()); // check that I have the correct formula 
        m_evt.lep2.corpfiso    = samesign::leptonIsolation(lep2_id, lep2_idx);
        m_evt.lep2.corpfiso04  = (lep2_is_el) ? samesign::electronIsolationPF2012_cone04(lep2_idx) : -999999.0;  
        m_evt.lep2.effarea     = samesign::EffectiveArea03(lep2_id, lep2_idx);
        m_evt.lep2.effarea04   = samesign::EffectiveArea04(lep2_id, lep2_idx);
        m_evt.lep2.dbeta       = (lep2_is_mu) ? mus_isoR03_pf_PUPt().at(lep2_idx) : -99999.0;
        m_evt.lep2.dbeta04     = (lep2_is_mu) ? mus_isoR04_pf_PUPt().at(lep2_idx) : -99999.0;
        m_evt.lep2.is_fo       = lep2_fo; 
        m_evt.lep2.is_num      = lep2_num;
        m_evt.lep2.is_den      = lep2_den;
        //m_evt.lep2.is_conv     = false; 
        m_evt.lep2.mt          = rt::Mt(m_evt.lep2.p4, met, met_phi);
        m_evt.lep2.passes_id   = samesign::isGoodLepton(lep2_id, lep2_idx, m_use_el_eta);
        m_evt.lep2.passes_iso  = samesign::isIsolatedLepton(lep2_id, lep2_idx);
        m_evt.lep2_wfr         = GetFakeRateValue(lep2_id, lep2_idx);
        m_evt.lep2_wflip       = GetFlipRateValue(lep2_id, lep2_idx);


        // njets, nbtags, HT and MET for JES systematics
        if (!evt_isRealData()) 
        {
            if (not m_jet_corrector || not m_met_corrector)
            {
                if (not m_jet_corr_unc)
                {
                    m_evt.ht_up       = samesign::sumJetPt    (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                    m_evt.ht20_up     = samesign::sumJetPt    (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                    m_evt.ht30_up     = samesign::sumJetPt    (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                    m_evt.njets_up    = samesign::nJets       (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                    m_evt.njets20_up  = samesign::nJets       (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                    m_evt.njets30_up  = samesign::nJets       (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                    m_evt.nbtags_up   = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                    m_evt.nbtags20_up = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                    m_evt.nbtags30_up = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);

                    m_evt.ht_dn       = samesign::sumJetPt    (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.ht20_dn     = samesign::sumJetPt    (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.ht30_dn     = samesign::sumJetPt    (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.njets_dn    = samesign::nJets       (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.njets20_dn  = samesign::nJets       (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.njets30_dn  = samesign::nJets       (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.nbtags_dn   = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.nbtags20_dn = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.nbtags30_dn = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                }
                else
                {
                    JetCorrectionUncertainty* jcu = m_jet_corr_unc.get();
                    enum JetScaleType scale_up = JETS_SCALE_UP;
                    enum JetScaleType scale_dn = JETS_SCALE_DOWN;

                    m_evt.ht_up       = samesign::sumJetPt    (hyp_idx, jcu, scale_up, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.ht20_up     = samesign::sumJetPt    (hyp_idx, jcu, scale_up, jet_type,                 /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.ht30_up     = samesign::sumJetPt    (hyp_idx, jcu, scale_up, jet_type,                 /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.njets_up    = samesign::nJets       (hyp_idx, jcu, scale_up, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.njets20_up  = samesign::nJets       (hyp_idx, jcu, scale_up, jet_type,                 /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.njets30_up  = samesign::nJets       (hyp_idx, jcu, scale_up, jet_type,                 /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.nbtags_up   = samesign::nBtaggedJets(hyp_idx, jcu, scale_up, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.nbtags20_up = samesign::nBtaggedJets(hyp_idx, jcu, scale_up, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.nbtags30_up = samesign::nBtaggedJets(hyp_idx, jcu, scale_up, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);

                    m_evt.ht_dn       = samesign::sumJetPt    (hyp_idx, jcu, scale_dn, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.ht20_dn     = samesign::sumJetPt    (hyp_idx, jcu, scale_dn, jet_type,                 /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.ht30_dn     = samesign::sumJetPt    (hyp_idx, jcu, scale_dn, jet_type,                 /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.njets_dn    = samesign::nJets       (hyp_idx, jcu, scale_dn, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.njets20_dn  = samesign::nJets       (hyp_idx, jcu, scale_dn, jet_type,                 /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.njets30_dn  = samesign::nJets       (hyp_idx, jcu, scale_dn, jet_type,                 /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.nbtags_dn   = samesign::nBtaggedJets(hyp_idx, jcu, scale_dn, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.nbtags20_dn = samesign::nBtaggedJets(hyp_idx, jcu, scale_dn, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.nbtags30_dn = samesign::nBtaggedJets(hyp_idx, jcu, scale_dn, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                }

                ROOT::Math::XYVector cmet_up;
                ROOT::Math::XYVector cmet_dn;
                float metx_up = evt_pfmet_type1cor() * cos(evt_pfmetPhi_type1cor());
                float metx_dn = evt_pfmet_type1cor() * cos(evt_pfmetPhi_type1cor());
                float mety_up = evt_pfmet_type1cor() * sin(evt_pfmetPhi_type1cor());
                float mety_dn = evt_pfmet_type1cor() * sin(evt_pfmetPhi_type1cor());
                // get uncorrected jets
                vector<LorentzVector> ujets = samesign::getJets(hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/10.0, /*|eta|<*/5.0, mu_min_pt, el_min_pt, 1.0, 0);
                for (size_t u = 0; u != ujets.size(); u++) 
                {
                    float px   = ujets.at(u).px();
                    float py   = ujets.at(u).py();
                    float pt   = ujets.at(u).pt();
                    float eta  = ujets.at(u).eta();
                    float corr_up = 0.0;
                    float corr_dn = 0.0;
                    if (m_jet_corr_unc)
                    {
                        m_jet_corr_unc->setJetPt(pt);	 
                        m_jet_corr_unc->setJetEta(eta);	 
                        float jet_cor_unc = m_jet_corr_unc->getUncertainty(true);	 
                        corr_up = (1. + jet_cor_unc);
                        corr_dn = (1. - jet_cor_unc);
                    }
                    else
                    {
                        corr_up = getJetMetSyst(/*jetMetScale=*/ 1, pt, eta);
                        corr_dn = getJetMetSyst(/*jetMetScale=*/-1, pt, eta);
                    }
                    metx_up = metx_up - (corr_up-1.0)*px;
                    mety_up = mety_up - (corr_up-1.0)*py;
                    metx_dn = metx_dn - (corr_dn-1.0)*px;
                    mety_dn = mety_dn - (corr_dn-1.0)*py;
                }
                cmet_up.SetXY(metx_up, mety_up);
                cmet_dn.SetXY(metx_dn, mety_dn);
                m_evt.pfmet_up     = cmet_up.r(); 
                m_evt.pfmet_phi_up = cmet_up.phi();
                m_evt.pfmet_dn     = cmet_dn.r(); 
                m_evt.pfmet_phi_dn = cmet_dn.phi();
            }
            else
            {
                if (not m_jet_corr_unc)
                {
                    m_evt.ht_up       = samesign::sumJetPt    (hyp_idx, m_jet_corrector.get(), jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                    m_evt.ht20_up     = samesign::sumJetPt    (hyp_idx, m_jet_corrector.get(), jet_type,                 /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                    m_evt.ht30_up     = samesign::sumJetPt    (hyp_idx, m_jet_corrector.get(), jet_type,                 /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                    m_evt.njets_up    = samesign::nJets       (hyp_idx, m_jet_corrector.get(), jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                    m_evt.njets20_up  = samesign::nJets       (hyp_idx, m_jet_corrector.get(), jet_type,                 /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                    m_evt.njets30_up  = samesign::nJets       (hyp_idx, m_jet_corrector.get(), jet_type,                 /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                    m_evt.nbtags_up   = samesign::nBtaggedJets(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                    m_evt.nbtags20_up = samesign::nBtaggedJets(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                    m_evt.nbtags30_up = samesign::nBtaggedJets(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);

                    m_evt.ht_dn       = samesign::sumJetPt    (hyp_idx, m_jet_corrector.get(), jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.ht20_dn     = samesign::sumJetPt    (hyp_idx, m_jet_corrector.get(), jet_type,                 /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.ht30_dn     = samesign::sumJetPt    (hyp_idx, m_jet_corrector.get(), jet_type,                 /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.njets_dn    = samesign::nJets       (hyp_idx, m_jet_corrector.get(), jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.njets20_dn  = samesign::nJets       (hyp_idx, m_jet_corrector.get(), jet_type,                 /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.njets30_dn  = samesign::nJets       (hyp_idx, m_jet_corrector.get(), jet_type,                 /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.nbtags_dn   = samesign::nBtaggedJets(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.nbtags20_dn = samesign::nBtaggedJets(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.nbtags30_dn = samesign::nBtaggedJets(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                }
                else
                {
                    FactorizedJetCorrector* jc    = m_jet_corrector.get();
                    JetCorrectionUncertainty* jcu = m_jet_corr_unc.get();
                    enum JetScaleType scale_up = JETS_SCALE_UP;
                    enum JetScaleType scale_dn = JETS_SCALE_DOWN;

                    m_evt.ht_up       = samesign::sumJetPt    (hyp_idx, jc, jcu, scale_up, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.ht20_up     = samesign::sumJetPt    (hyp_idx, jc, jcu, scale_up, jet_type,                 /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.ht30_up     = samesign::sumJetPt    (hyp_idx, jc, jcu, scale_up, jet_type,                 /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.njets_up    = samesign::nJets       (hyp_idx, jc, jcu, scale_up, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.njets20_up  = samesign::nJets       (hyp_idx, jc, jcu, scale_up, jet_type,                 /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.njets30_up  = samesign::nJets       (hyp_idx, jc, jcu, scale_up, jet_type,                 /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.nbtags_up   = samesign::nBtaggedJets(hyp_idx, jc, jcu, scale_up, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.nbtags20_up = samesign::nBtaggedJets(hyp_idx, jc, jcu, scale_up, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.nbtags30_up = samesign::nBtaggedJets(hyp_idx, jc, jcu, scale_up, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);

                    m_evt.ht_dn       = samesign::sumJetPt    (hyp_idx, jc, jcu, scale_dn, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.ht20_dn     = samesign::sumJetPt    (hyp_idx, jc, jcu, scale_dn, jet_type,                 /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.ht30_dn     = samesign::sumJetPt    (hyp_idx, jc, jcu, scale_dn, jet_type,                 /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.njets_dn    = samesign::nJets       (hyp_idx, jc, jcu, scale_dn, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.njets20_dn  = samesign::nJets       (hyp_idx, jc, jcu, scale_dn, jet_type,                 /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.njets30_dn  = samesign::nJets       (hyp_idx, jc, jcu, scale_dn, jet_type,                 /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.nbtags_dn   = samesign::nBtaggedJets(hyp_idx, jc, jcu, scale_dn, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.nbtags20_dn = samesign::nBtaggedJets(hyp_idx, jc, jcu, scale_dn, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.nbtags30_dn = samesign::nBtaggedJets(hyp_idx, jc, jcu, scale_dn, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                }

                // MET
                ROOT::Math::XYVector cmet_up;
                ROOT::Math::XYVector cmet_dn;
                float metx_up = met * cos(met_phi);
                float metx_dn = met * cos(met_phi);
                float mety_up = met * sin(met_phi);
                float mety_dn = met * sin(met_phi);
                // get uncorrected jets
                vector<LorentzVector> ujets = samesign::getJets(hyp_idx, m_jet_corrector.get(), jet_type, /*dR=*/0.4, /*jet_pt>*/10.0, /*|eta|<*/5.0, mu_min_pt, el_min_pt, 1.0, 0);
                for (size_t u = 0; u != ujets.size(); u++) 
                {
                    float px   = ujets.at(u).px();
                    float py   = ujets.at(u).py();
                    float pt   = ujets.at(u).pt();
                    float eta  = ujets.at(u).eta();
                    float corr_up = 0.0;
                    float corr_dn = 0.0;
                    if (m_jet_corr_unc)
                    {
                        m_jet_corr_unc->setJetPt(pt);	 
                        m_jet_corr_unc->setJetEta(eta);	 
                        float jet_cor_unc = m_jet_corr_unc->getUncertainty(true);	 
                        corr_up = (1. + jet_cor_unc);
                        corr_dn = (1. - jet_cor_unc);
                    }
                    else
                    {
                        corr_up = getJetMetSyst(/*jetMetScale=*/ 1, pt, eta);
                        corr_dn = getJetMetSyst(/*jetMetScale=*/-1, pt, eta);
                    }
                    metx_up = metx_up - (corr_up-1.0)*px;
                    mety_up = mety_up - (corr_up-1.0)*py;
                    metx_dn = metx_dn - (corr_dn-1.0)*px;
                    mety_dn = mety_dn - (corr_dn-1.0)*py;
                }
                cmet_up.SetXY(metx_up, mety_up);
                cmet_dn.SetXY(metx_dn, mety_dn);
                m_evt.pfmet_up     = cmet_up.r();
                m_evt.pfmet_phi_up = cmet_up.phi();
                m_evt.pfmet_dn     = cmet_dn.r();
                m_evt.pfmet_phi_dn = cmet_dn.phi();
            }
        }

        // only keep m_njets events
        if (evt_isRealData())
        {
            if (m_evt.njets < m_njets)
            {
                if (m_verbose) {std::cout << "fails # jets >= " << m_njets << " cut" << std::endl;}
                return 0;
            }
        }
        else
        {
            bool pass_njets_cut = (m_evt.njets_up >= m_njets || m_evt.njets_dn >= m_njets || m_evt.njets >= m_njets);
            if (not pass_njets_cut)
            {
                if (m_verbose) {std::cout << "fails # jets >= " << m_njets << " cut" << std::endl;}
                return 0;
            }
        }

        // classification
        m_evt.is_ss       = (charge_type==DileptonChargeType::SS);
        m_evt.is_sf       = (charge_type==DileptonChargeType::SF);
        m_evt.is_df       = (charge_type==DileptonChargeType::DF);
        m_evt.is_os       = (charge_type==DileptonChargeType::OS);
        m_evt.charge_type = charge_type;
        m_evt.em_mufo     = m_evt.em && ((lep1_fo && lep1_is_mu) || (lep2_fo && lep2_is_mu));  
        m_evt.em_elfo     = m_evt.em && ((lep1_fo && lep1_is_el) || (lep2_fo && lep2_is_el));
        m_evt.is_pp       = hyp_lt_charge().at(hyp_idx)>0 && hyp_ll_charge().at(hyp_idx)>0; 
        m_evt.is_mm       = hyp_lt_charge().at(hyp_idx)<0 && hyp_ll_charge().at(hyp_idx)<0; 

        // selected only triggered events
        if (not((m_evt.ee && m_evt.trig_ee) || (m_evt.em && m_evt.trig_em) || (m_evt.mm && m_evt.trig_mm)))
        {
            if (m_verbose) {cout << "fails trigger selection" << endl;}
            //return 0;
        }

        // electron isolation correction variables
        m_evt.rho_iso = evt_kt6pf_foregiso_rho();
        m_evt.rho     = evt_ww_rho_vor(); 

        // eff and scale factors
        if (!evt_isRealData())
        {
            // scale factor for trigger efficiency
            m_evt.sf_dileptrig     = DileptonTriggerScaleFactor(dilepton_type, m_analysis_type      , m_evt.lep2.p4);
            m_evt.sf_dileptrig_hpt = DileptonTriggerScaleFactor(dilepton_type, AnalysisType::high_pt, m_evt.lep2.p4);
            m_evt.sf_dileptrig_lpt = DileptonTriggerScaleFactor(dilepton_type, AnalysisType::low_pt , m_evt.lep2.p4);
            m_evt.sf_dileptrig_vpt = DileptonTriggerScaleFactor(dilepton_type, AnalysisType::vlow_pt, m_evt.lep2.p4);
            m_evt.lep1.sf_trig   = -999999; // not done 
            m_evt.lep2.sf_trig   = -999999; // not done

            // scale factor for lepton reconstruction efficiency
            const float eta1 = (abs(lep1_id) == 13 ? m_evt.lep1.p4.eta() : m_evt.lep1.sc_p4.eta());
            const float eta2 = (abs(lep2_id) == 13 ? m_evt.lep2.p4.eta() : m_evt.lep2.sc_p4.eta());
            m_evt.sf_dilepeff    = DileptonTagAndProbeScaleFactor(lep1_id, m_evt.lep1.p4.pt(), eta1, lep2_id, m_evt.lep2.p4.pt(), eta2);
            m_evt.lep1.sf_lepeff = TagAndProbeScaleFactor(lep1_id, m_evt.lep1.p4.pt(), eta1); 
            m_evt.lep2.sf_lepeff = TagAndProbeScaleFactor(lep2_id, m_evt.lep2.p4.pt(), eta2);

            // scale factor for # btags 
            vector<LorentzVector> bjets;
            if (not m_jet_corrector)
            {
                bjets = samesign::getBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
            }
            else
            {
                bjets = samesign::getBtaggedJets(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
            }

            std::sort(bjets.begin(), bjets.end(), SortByPt<LorentzVector>());
            if (m_evt.nbtags == 2) 
            {
                m_evt.sf_nbtag = btagEventWeight(m_evt.nbtags, bjets.at(0).pt(), bjets.at(1).pt(), 0., 0., m_is_fast_sim);
            }
            else if (m_evt.nbtags == 3) 
            {
                m_evt.sf_nbtag  = btagEventWeight (m_evt.nbtags, bjets.at(0).pt(), bjets.at(1).pt(), bjets.at(2).pt(), 0., m_is_fast_sim);
                m_evt.sf_nbtag3 = btagEventWeight3(m_evt.nbtags, bjets.at(0).pt(), bjets.at(1).pt(), bjets.at(2).pt(), 0., m_is_fast_sim);
            }
            else if (m_evt.nbtags > 3) 
            {
                m_evt.sf_nbtag  = btagEventWeight (4, bjets.at(0).pt(), bjets.at(1).pt(), bjets.at(2).pt(), bjets.at(3).pt(), m_is_fast_sim);
                m_evt.sf_nbtag3 = btagEventWeight3(4, bjets.at(0).pt(), bjets.at(1).pt(), bjets.at(2).pt(), bjets.at(3).pt(), m_is_fast_sim);
            }

            // Added the btag scale factor uncertainty (Claudio)
            // Note: pt and eta cuts, as necessary, will be made inside the code that calculates the scale factors
            // When there arent enough bquarks we put in some nominal bullshit value 
            std::vector<LorentzVector> gen_bjets = efftools::getGenBjets(/*pt_cut=*/0.001, /*eta_cut=*/2.5);
            std::sort(gen_bjets.begin(), gen_bjets.end(), SortByPt<LorentzVector>());
            if ( gen_bjets.size()==0) 
            {
                m_evt.sf_unc_nbtag   = btagEventUncertainty (2, 50.0, 0., 50.0, 0.0, 50.0, 0.0, 50.0, 0, m_is_fast_sim);
                m_evt.sf_unc_nbtag3  = btagEventUncertainty3(3, 50.0, 0., 50.0, 0.0, 50.0, 0.0, 50.0, 0, m_is_fast_sim);
            } 
            else if ( gen_bjets.size()==1) 
            {
                m_evt.sf_unc_nbtag  = btagEventUncertainty (2, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), 50.0, 0.0, 50.0, 0.0, 50.0, 0, m_is_fast_sim);
                m_evt.sf_unc_nbtag3 = btagEventUncertainty3(3, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), 50.0, 0.0, 50.0, 0.0, 50.0, 0, m_is_fast_sim);
            } 
            else if ( gen_bjets.size()==2) 
            {
                m_evt.sf_unc_nbtag  = btagEventUncertainty (2, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), gen_bjets.at(1).pt(), gen_bjets.at(1).eta(), 50.0, 0.0, 50.0, 0, m_is_fast_sim);
                m_evt.sf_unc_nbtag3 = btagEventUncertainty3(3, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), gen_bjets.at(1).pt(), gen_bjets.at(1).eta(), 50.0, 0.0, 50.0, 0, m_is_fast_sim);
            } 
            else if ( gen_bjets.size()==3) 
            {
                m_evt.sf_unc_nbtag  = btagEventUncertainty (3, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), gen_bjets.at(1).pt(), gen_bjets.at(1).eta(),
                                                               gen_bjets.at(2).pt(), gen_bjets.at(2).eta(), 50., 0, m_is_fast_sim);
                m_evt.sf_unc_nbtag3 = btagEventUncertainty3(3, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), gen_bjets.at(1).pt(), gen_bjets.at(1).eta(),
                                                               gen_bjets.at(2).pt(), gen_bjets.at(2).eta(), 50., 0, m_is_fast_sim);
            }
            else if ( gen_bjets.size()>3)
            {
                m_evt.sf_unc_nbtag  = btagEventUncertainty (4, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), gen_bjets.at(1).pt(), gen_bjets.at(1).eta(),
                                                               gen_bjets.at(2).pt(), gen_bjets.at(2).eta(), gen_bjets.at(3).pt(), gen_bjets.at(3).eta(), m_is_fast_sim);
                m_evt.sf_unc_nbtag3 = btagEventUncertainty3(4, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), gen_bjets.at(1).pt(), gen_bjets.at(1).eta(),
                                                               gen_bjets.at(2).pt(), gen_bjets.at(2).eta(), gen_bjets.at(3).pt(), gen_bjets.at(3).eta(), m_is_fast_sim);
            }
        }

        // jet/bjet info 
        if (not m_jet_corrector)
        {
            m_evt.vbjets_p4           = samesign::getBtaggedJets       (hyp_idx, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale); 
            m_evt.vjets_p4            = samesign::getJets              (hyp_idx, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale); 
            m_evt.vjets_mcflavor_phys = samesign::getJetMcPhysMatch    (hyp_idx, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
            m_evt.vjets_mcflavor_algo = samesign::getJetMcAlgoMatch    (hyp_idx, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
            m_evt.vjets_btagged       = samesign::getSortedBtaggedFlags(hyp_idx, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
            if (not m_jet_corr_unc)
            {
                m_evt.vbjets_p4_up           = samesign::getBtaggedJets       (hyp_idx, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 1 ); 
                m_evt.vjets_p4_up            = samesign::getJets              (hyp_idx, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 1 ); 
                m_evt.vjets_mcflavor_phys_up = samesign::getJetMcPhysMatch    (hyp_idx, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 1 );
                m_evt.vjets_mcflavor_algo_up = samesign::getJetMcAlgoMatch    (hyp_idx, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 1 );
                m_evt.vjets_btagged_up       = samesign::getSortedBtaggedFlags(hyp_idx, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 1 );

                m_evt.vbjets_p4_dn           = samesign::getBtaggedJets       (hyp_idx, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, -1); 
                m_evt.vjets_p4_dn            = samesign::getJets              (hyp_idx, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, -1); 
                m_evt.vjets_mcflavor_phys_dn = samesign::getJetMcPhysMatch    (hyp_idx, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, -1);
                m_evt.vjets_mcflavor_algo_dn = samesign::getJetMcAlgoMatch    (hyp_idx, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, -1);
                m_evt.vjets_btagged_dn       = samesign::getSortedBtaggedFlags(hyp_idx, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, -1);
            }
            else
            {
                JetCorrectionUncertainty* jcu = m_jet_corr_unc.get();
                enum JetScaleType scale_up = JETS_SCALE_UP;
                enum JetScaleType scale_dn = JETS_SCALE_DOWN;

                m_evt.vbjets_p4_up           = samesign::getBtaggedJets       (hyp_idx, jcu, scale_up, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt); 
                m_evt.vjets_p4_up            = samesign::getJets              (hyp_idx, jcu, scale_up, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt); 
                m_evt.vjets_mcflavor_phys_up = samesign::getJetMcPhysMatch    (hyp_idx, jcu, scale_up, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                m_evt.vjets_mcflavor_algo_up = samesign::getJetMcAlgoMatch    (hyp_idx, jcu, scale_up, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                m_evt.vjets_btagged_up       = samesign::getSortedBtaggedFlags(hyp_idx, jcu, scale_up, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);

                m_evt.vbjets_p4_dn           = samesign::getBtaggedJets       (hyp_idx, jcu, scale_dn, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt); 
                m_evt.vjets_p4_dn            = samesign::getJets              (hyp_idx, jcu, scale_dn, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt); 
                m_evt.vjets_mcflavor_phys_dn = samesign::getJetMcPhysMatch    (hyp_idx, jcu, scale_dn, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                m_evt.vjets_mcflavor_algo_dn = samesign::getJetMcAlgoMatch    (hyp_idx, jcu, scale_dn, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                m_evt.vjets_btagged_dn       = samesign::getSortedBtaggedFlags(hyp_idx, jcu, scale_dn, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
            }
        }
        else
        {
            m_evt.vbjets_p4           = samesign::getBtaggedJets       (hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale); 
            m_evt.vjets_p4            = samesign::getJets              (hyp_idx, m_jet_corrector.get(), jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale); 
            m_evt.vjets_mcflavor_phys = samesign::getJetMcPhysMatch    (hyp_idx, m_jet_corrector.get(), jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
            m_evt.vjets_mcflavor_algo = samesign::getJetMcAlgoMatch    (hyp_idx, m_jet_corrector.get(), jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
            m_evt.vjets_btagged       = samesign::getSortedBtaggedFlags(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
            if (not m_jet_corr_unc)
            {
                m_evt.vbjets_p4_up           = samesign::getBtaggedJets       (hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 1 ); 
                m_evt.vjets_p4_up            = samesign::getJets              (hyp_idx, m_jet_corrector.get(), jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 1 ); 
                m_evt.vjets_mcflavor_phys_up = samesign::getJetMcPhysMatch    (hyp_idx, m_jet_corrector.get(), jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 1 );
                m_evt.vjets_mcflavor_algo_up = samesign::getJetMcAlgoMatch    (hyp_idx, m_jet_corrector.get(), jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 1 );
                m_evt.vjets_btagged_up       = samesign::getSortedBtaggedFlags(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 1 );

                m_evt.vbjets_p4_dn           = samesign::getBtaggedJets       (hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, -1); 
                m_evt.vjets_p4_dn            = samesign::getJets              (hyp_idx, m_jet_corrector.get(), jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, -1); 
                m_evt.vjets_mcflavor_phys_dn = samesign::getJetMcPhysMatch    (hyp_idx, m_jet_corrector.get(), jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, -1);
                m_evt.vjets_mcflavor_algo_dn = samesign::getJetMcAlgoMatch    (hyp_idx, m_jet_corrector.get(), jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, -1);
                m_evt.vjets_btagged_dn       = samesign::getSortedBtaggedFlags(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, -1);
            }
            else
            {
                FactorizedJetCorrector* jc    = m_jet_corrector.get();
                JetCorrectionUncertainty* jcu = m_jet_corr_unc.get();
                enum JetScaleType scale_up = JETS_SCALE_UP;
                enum JetScaleType scale_dn = JETS_SCALE_DOWN;

                m_evt.vbjets_p4_up           = samesign::getBtaggedJets       (hyp_idx, jc, jcu, scale_up, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt); 
                m_evt.vjets_p4_up            = samesign::getJets              (hyp_idx, jc, jcu, scale_up, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt); 
                m_evt.vjets_mcflavor_phys_up = samesign::getJetMcPhysMatch    (hyp_idx, jc, jcu, scale_up, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                m_evt.vjets_mcflavor_algo_up = samesign::getJetMcAlgoMatch    (hyp_idx, jc, jcu, scale_up, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                m_evt.vjets_btagged_up       = samesign::getSortedBtaggedFlags(hyp_idx, jc, jcu, scale_up, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt); 

                m_evt.vbjets_p4_dn           = samesign::getBtaggedJets       (hyp_idx, jc, jcu, scale_dn, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt); 
                m_evt.vjets_p4_dn            = samesign::getJets              (hyp_idx, jc, jcu, scale_dn, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt); 
                m_evt.vjets_mcflavor_phys_dn = samesign::getJetMcPhysMatch    (hyp_idx, jc, jcu, scale_dn, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                m_evt.vjets_mcflavor_algo_dn = samesign::getJetMcAlgoMatch    (hyp_idx, jc, jcu, scale_dn, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                m_evt.vjets_btagged_dn       = samesign::getSortedBtaggedFlags(hyp_idx, jc, jcu, scale_dn, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt); 
            }
        }

        // set the seed
        const unsigned int seed = evt_event();

        // calculate the "reweighted" MC btag yields
        const CMS2Tag cms2_tag = at::GetCMS2Tag();
        if (not evt_isRealData() && (cms2_tag.version > 21))
        {
            // # btags reweighted
            m_evt.nbtags_reweighted    = at::MCBtagCount(m_evt.vjets_p4, m_evt.vjets_btagged, m_evt.vjets_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            m_evt.nbtags_reweighted_up = at::MCBtagCount(m_evt.vjets_p4, m_evt.vjets_btagged, m_evt.vjets_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::up  , seed);
            m_evt.nbtags_reweighted_dn = at::MCBtagCount(m_evt.vjets_p4, m_evt.vjets_btagged, m_evt.vjets_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::down, seed);

            // # btags reweighted and JES +/-
            m_evt.nbtags_reweighted_jec_up = at::MCBtagCount(m_evt.vjets_p4_up, m_evt.vjets_btagged_up, m_evt.vjets_mcflavor_algo_up, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            m_evt.nbtags_reweighted_jec_dn = at::MCBtagCount(m_evt.vjets_p4_dn, m_evt.vjets_btagged_dn, m_evt.vjets_mcflavor_algo_dn, m_sample, m_is_fast_sim, at::YieldType::base, seed);
        }

        // scale the JER 
        if (not evt_isRealData() && (cms2_tag.version > 21))
        {
            // set initial values
            m_evt.ht_jer        = m_evt.ht;
            m_evt.pfmet_jer     = met;
            m_evt.pfmet_jer_phi = met_phi;
            vector<LorentzVector> vjets_jer_p4  = m_evt.vjets_p4;
            vector<LorentzVector> vbjets_jer_p4 = m_evt.vbjets_p4; 

            // update the values by scaling the JER
            samesign::smearJETScaleJetsMetHt(vjets_jer_p4, m_evt.pfmet_jer, m_evt.pfmet_jer_phi, m_evt.ht_jer, hyp_idx, jet_type, seed, /*dR=*/0.4, /*jet_pt>*/40, /*|eta|<*/2.4, /*mu_pt>*/mu_min_pt, /*el_pt>*/el_min_pt);
            vector<LorentzVector> vbjets_reweighted_jer_p4 = at::RecountedBjets(m_evt.vjets_p4, m_evt.vjets_btagged, m_evt.vjets_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            samesign::smearJETScaleJets(vbjets_jer_p4, seed);
            samesign::smearJETScaleJets(vbjets_reweighted_jer_p4, seed);

            // set the branches 
            m_evt.njets_jer             = vjets_jer_p4.size();
            m_evt.nbtags_jer            = vbjets_jer_p4.size();
            m_evt.nbtags_reweighted_jer = vbjets_reweighted_jer_p4.size();
        }

        // scale the unclustered MET
        m_evt.pfmet_uncl_up = samesign::scaleMET(met, met_phi, hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/15, /*|eta|<*/2.5, /*mu_pt>*/mu_min_pt, /*el_pt>*/el_min_pt, /*scale_type=*/1 , /*scale=*/0.1);
        m_evt.pfmet_uncl_dn = samesign::scaleMET(met, met_phi, hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/15, /*|eta|<*/2.5, /*mu_pt>*/mu_min_pt, /*el_pt>*/el_min_pt, /*scale_type=*/-1, /*scale=*/0.1);

        //SetBtagDiscriminator(m_evt.bjets_p4, m_evt.bjets_csv, JETS_BTAG_CSVM);
        //SetBtagDiscriminator(m_evt.vjets_p4, m_evt.bjets_csv, JETS_BTAG_CSVM);

        m_evt.bjets_dr12 = (m_evt.nbtags>=2) ? rt::DeltaR(m_evt.vbjets_p4.at(0), m_evt.vbjets_p4.at(1)) : -999999.0;
        m_evt.jets_dr12  = (m_evt.njets>=2 ) ? rt::DeltaR(m_evt.vjets_p4.at(0) , m_evt.vjets_p4.at(1) ) : -999999.0;

        vector<LorentzVector> temp_bjets_p4 = m_evt.vbjets_p4;
        if (!temp_bjets_p4.empty())
        {
            // nearest to lep1
            std::sort(temp_bjets_p4.begin(), temp_bjets_p4.begin(), SortByDeltaR<LorentzVector>(m_evt.lep1.p4));
            m_evt.lep1_nearbjet_p4 = temp_bjets_p4.front();
            m_evt.lep1_nearbjet_dr = rt::DeltaR(m_evt.lep1.p4, temp_bjets_p4.front());

            // nearest to lep2
            std::sort(temp_bjets_p4.begin(), temp_bjets_p4.begin(), SortByDeltaR<LorentzVector>(m_evt.lep2.p4));
            m_evt.lep2_nearbjet_p4 = temp_bjets_p4.front();
            m_evt.lep2_nearbjet_dr = rt::DeltaR(m_evt.lep2.p4, temp_bjets_p4.front());
        }

        // get the list of selected jets with lower pT theshold
        //vector<LorentzVector> temp_jets_p4 = tas::pfjets_p4();
        //vector<float>& temp_jets_csv = pfjets_combinedSecondaryVertexBJetTag();
        //vector<LorentzVector> temp_jets_p4  = samesign::getJets(hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale); 
        //vector<float> temp_jets_csv;
        //SetBtagDiscriminator(temp_jets_p4, temp_jets_csv, JETS_BTAG_CSVM);
        
        vector<LorentzVector> temp_jets_p4 = m_evt.vjets_p4;  
        //vector<float> temp_jets_csv        = m_evt.vjets_csv;

        // get the untagged jets
        vector<LorentzVector> temp_jets_nontagged_p4;
        for (size_t i = 0; i != temp_jets_p4.size(); i++)
        {
            //temp_jets_p4.at(i) *= evt_isRealData() ? pfjets_corL1FastL2L3residual().at(i) : pfjets_corL1FastL2L3().at(i);
            if (not m_evt.vjets_btagged.at(i))
            {
                temp_jets_nontagged_p4.push_back(temp_jets_p4.at(i));
            }
        }

        if (!temp_jets_p4.empty())
        {
            // nearest untagged jet to the btags
            for (size_t i = 0; i != m_evt.vbjets_p4.size(); i++)
            {
                const LorentzVector& p4 = m_evt.vbjets_p4.at(i);
                if (temp_jets_nontagged_p4.empty()) 
                {
                    m_evt.vbjets_nearjet_p4.push_back(LorentzVector(0,0,0,0));
                    m_evt.vbjets_nearjet_dr.push_back(-999999.0);
                    continue;
                }
                std::sort(temp_jets_nontagged_p4.begin(), temp_jets_nontagged_p4.end(), SortByDeltaR<LorentzVector>(p4));
                m_evt.vbjets_nearjet_p4.push_back(temp_jets_nontagged_p4.front());
                m_evt.vbjets_nearjet_dr.push_back(rt::DeltaR(p4, temp_jets_nontagged_p4.front()));
            }

            // nearest jet to the selected jet
            for (size_t i = 0; i != m_evt.vjets_p4.size(); i++)
            {
                if (temp_jets_nontagged_p4.empty()) 
                {
                    m_evt.vjets_nearjet_p4.push_back(LorentzVector(0,0,0,0));
                    m_evt.vjets_nearjet_dr.push_back(-999999.0);
                    continue;
                }
                const LorentzVector& p4 = m_evt.vjets_p4.at(i);
                std::sort(temp_jets_nontagged_p4.begin(), temp_jets_nontagged_p4.end(), SortByDeltaR<LorentzVector>(p4));

                // check if closest is the same jet?
                if (rt::DeltaR(temp_jets_nontagged_p4.front(), p4) < 0.0001)
                {
                    if (temp_jets_nontagged_p4.size()>=2)
                    {
                        m_evt.vjets_nearjet_p4.push_back(temp_jets_nontagged_p4.at(1));
                        m_evt.vjets_nearjet_dr.push_back(rt::DeltaR(p4, temp_jets_nontagged_p4.at(1)));
                    }
                    else // fill with dummy values
                    {
                        m_evt.vjets_nearjet_p4.push_back(LorentzVector(0,0,0,0));
                        m_evt.vjets_nearjet_dr.push_back(-999999.0);
                    }
                }
                else
                {
                    m_evt.vjets_nearjet_p4.push_back(temp_jets_nontagged_p4.front());
                    m_evt.vjets_nearjet_dr.push_back(rt::DeltaR(p4, temp_jets_nontagged_p4.front()));
                }
            }
            
            // nearest to lep1
            std::sort(temp_jets_p4.begin(), temp_jets_p4.end(), SortByDeltaR<LorentzVector>(m_evt.lep1.p4));
            m_evt.lep1_nearjet_p4 = temp_jets_p4.front();
            m_evt.lep1_nearjet_dr = rt::DeltaR(m_evt.lep1.p4, temp_jets_p4.front());

            // nearest to lep2
            std::sort(temp_jets_p4.begin(), temp_jets_p4.end(), SortByDeltaR<LorentzVector>(m_evt.lep2.p4));
            m_evt.lep2_nearjet_p4 = temp_jets_p4.front();
            m_evt.lep2_nearjet_dr = rt::DeltaR(m_evt.lep2.p4, temp_jets_p4.front());
        }

        if (abs(m_evt.lep1.pdgid) == 11) {
            std::pair<int,double> closest_el = std::make_pair(-1, 99.);
            for (unsigned int eidx = 0; eidx < cms2.els_p4().size(); eidx++) {
                
                if (cms2.els_p4().at(eidx).pt() < 5.) continue;
                if (fabs(cms2.els_p4().at(eidx).eta()) > 2.5) continue;
                if (m_evt.lep1.charge * cms2.els_charge().at(eidx) > 0) continue;

                double iso_val = samesign::electronIsolationPF2012(eidx);
                if (iso_val > 0.2) continue;

                using namespace wp2012;
                electronIdComponent_t passAllVetoCuts = DETAIN | DPHIIN | SIGMAIETAIETA | HOE | D0VTX | DZVTX;
                electronIdComponent_t vetoid = electronId_WP2012(eidx, VETO);
                if ((passAllVetoCuts & vetoid) != passAllVetoCuts)
                    continue;

                double dr = rt::DeltaR(cms2.els_p4().at(eidx), m_evt.lep1.p4);
                if (dr < closest_el.second)
                    closest_el = std::make_pair(eidx, dr);
            }

            if (closest_el.first >= 0) {
                m_evt.lep1_nearlep_p4 = cms2.els_p4().at(closest_el.first);
                m_evt.lep1_nearlep_id = -11 * cms2.els_charge().at(closest_el.first);
                m_evt.lep1_nearlep_dr = closest_el.second;
            }                
        }

        if (abs(m_evt.lep2.pdgid) == 11) {
            std::pair<int,double> closest_el = std::make_pair(-1, 99.);
            for (unsigned int eidx = 0; eidx < cms2.els_p4().size(); eidx++) {
                
                if (cms2.els_p4().at(eidx).pt() < 5.) continue;
                if (fabs(cms2.els_p4().at(eidx).eta()) > 2.5) continue;
                if (m_evt.lep2.charge * cms2.els_charge().at(eidx) > 0) continue;

                double iso_val = samesign::electronIsolationPF2012(eidx);
                if (iso_val > 0.2) continue;

                using namespace wp2012;
                electronIdComponent_t passAllVetoCuts = DETAIN | DPHIIN | SIGMAIETAIETA | HOE | D0VTX | DZVTX;
                electronIdComponent_t vetoid = electronId_WP2012(eidx, VETO);
                if ((passAllVetoCuts & vetoid) != passAllVetoCuts)
                    continue;

                double dr = rt::DeltaR(cms2.els_p4().at(eidx), m_evt.lep2.p4);
                if (dr < closest_el.second)
                    closest_el = std::make_pair(eidx, dr);
            }

            if (closest_el.first >= 0) {
                m_evt.lep2_nearlep_p4 = cms2.els_p4().at(closest_el.first);
                m_evt.lep2_nearlep_id = -11 * cms2.els_charge().at(closest_el.first);
                m_evt.lep2_nearlep_dr = closest_el.second;
            }                
        }

        if (abs(m_evt.lep1.pdgid) == 13) {
            std::pair<int,double> closest_mu = std::make_pair(-1, 99.);
            for (unsigned int midx = 0; midx < cms2.mus_p4().size(); midx++) {
                
                if (cms2.mus_p4().at(midx).pt() < 5.) continue;
                if (fabs(cms2.mus_p4().at(midx).eta()) > 2.5) continue;
                if (m_evt.lep1.charge * cms2.mus_charge().at(midx) > 0) continue;

                double iso_val = muonIsoValuePF2012_deltaBeta(midx);
                if (iso_val > 0.2) continue;

                if (!passes_muid_wp2012(midx, mu2012_tightness::LOOSE))
                    continue;

                double dr = rt::DeltaR(cms2.mus_p4().at(midx), m_evt.lep1.p4);
                if (dr < closest_mu.second)
                    closest_mu = std::make_pair(midx, dr);
            }

            if (closest_mu.first >= 0) {
                m_evt.lep1_nearlep_p4 = cms2.mus_p4().at(closest_mu.first);
                m_evt.lep1_nearlep_id = -13 * cms2.mus_charge().at(closest_mu.first);
                m_evt.lep1_nearlep_dr = closest_mu.second;
            }                
        }

        if (abs(m_evt.lep2.pdgid) == 13) {
            std::pair<int,double> closest_mu = std::make_pair(-1, 99.);
            for (unsigned int midx = 0; midx < cms2.mus_p4().size(); midx++) {
                
                if (cms2.mus_p4().at(midx).pt() < 5.) continue;
                if (fabs(cms2.mus_p4().at(midx).eta()) > 2.5) continue;
                if (m_evt.lep2.charge * cms2.mus_charge().at(midx) > 0) continue;

                double iso_val = muonIsoValuePF2012_deltaBeta(midx);
                if (iso_val > 0.2) continue;

                if (!passes_muid_wp2012(midx, mu2012_tightness::LOOSE))
                    continue;

                double dr = rt::DeltaR(cms2.mus_p4().at(midx), m_evt.lep2.p4);
                if (dr < closest_mu.second)
                    closest_mu = std::make_pair(midx, dr);
            }

            if (closest_mu.first >= 0) {
                m_evt.lep2_nearlep_p4 = cms2.mus_p4().at(closest_mu.first);
                m_evt.lep2_nearlep_id = -13 * cms2.mus_charge().at(closest_mu.first);
                m_evt.lep2_nearlep_dr = closest_mu.second;
            }                
        }

        // match njets/btags to MC truth
        if (not tas::evt_isRealData())
        {
            // jets
            for (size_t i = 0; i != m_evt.vjets_p4.size(); i++)
            {
                const LorentzVector jet_p4 = m_evt.vjets_p4.at(i);
                int idx = efftools::getGenParton(jet_p4, /*use status3 =*/true);
                int mc3id = idx>= 0 ? tas::genps_id().at(idx) : -999999;
                int momid = idx>= 0 ? tas::genps_id_mother().at(idx) : -999999;
                LorentzVector mc3p4 = idx>= 0 ? tas::genps_p4().at(idx) : LorentzVector(0,0,0,0);
                m_evt.vjets_mc3id.push_back(mc3id);
                m_evt.vjets_momid.push_back(momid);
                m_evt.vjets_mc3p4.push_back(mc3p4);
            }

            // b-tagged jets
            for (size_t i = 0; i != m_evt.vbjets_p4.size(); i++)
            {
                const LorentzVector bjet_p4 = m_evt.vbjets_p4.at(i);
                int idx = efftools::getGenParton(bjet_p4, /*use status3 =*/true);
                int mc3id = idx>= 0 ? tas::genps_id().at(idx) : -999999;
                int momid = idx>= 0 ? tas::genps_id_mother().at(idx) : -999999;
                LorentzVector mc3p4 = idx>= 0 ? tas::genps_p4().at(idx) : LorentzVector(0,0,0,0);
                m_evt.vbjets_mc3id.push_back(mc3id);
                m_evt.vbjets_momid.push_back(momid);
                m_evt.vbjets_mc3p4.push_back(mc3p4);
            }
        }

        //----------------------------------------
        // store info for third lepton (choose highest pt, separated from hyp leptons by dR=0.1)
        //----------------------------------------
        int el3_idx  = -1;
        int el3_id   = 0;
        float el3_pt = -999999.0;
        LorentzVector el3_medium_p4(0, 0, 0, 0);
        LorentzVector el3_loose_p4(0, 0, 0, 0);
        LorentzVector el3_ssv7_p4(0, 0, 0, 0);
        for (size_t el_idx = 0; el_idx != els_p4().size(); el_idx++)
        {
            const LorentzVector& el_p4 = els_p4().at(el_idx);

            if (el_p4.pt() < el_min_pt)            {continue;}
            if (lep1_is_el and el_idx == lep1_idx) {continue;}
            if (lep2_is_el and el_idx == lep2_idx) {continue;}

            // set 3rd electron vars
            if (el_p4.pt() > el3_pt)
            {
                el3_idx = el_idx;
                el3_id  = -11 * els_charge().at(el_idx);
                el3_pt  = el_p4.pt();
            }

            // medium WP
            if (pass_electronSelection(el_idx, electronSelection_pog_medium) and (el_p4.pt() > el3_medium_p4.pt()))
            {
                el3_medium_p4 = el_p4; 
            }

            // loose WP
            if (pass_electronSelection(el_idx, electronSelection_pog_loose) and (el_p4.pt() > el3_loose_p4.pt()))
            {
                el3_loose_p4 = el_p4; 
            }

            // full ss2012 selection
            if (samesign::isGoodLepton(11, el_idx) and (el_p4.pt() > el3_ssv7_p4.pt()))
            {
                el3_ssv7_p4 = el_p4; 
            }
        }
        m_evt.el_elid_loose_p4  = el3_loose_p4;
        m_evt.el_elid_medium_p4 = el3_medium_p4;
        m_evt.el_elid_ssv7_p4   = el3_ssv7_p4;

//         m_evt.el3.FillCommon(el3_id, el3_idx);
//         if (el3_idx >= 0)
//         {
//             m_evt.el3.cordetiso   = m_evt.el3.detiso   - (log(m_evt.el3.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.el3.p4.pt()); // check that I have the correct formula 
//             m_evt.el3.cordetiso04 = m_evt.el3.detiso04 - (log(m_evt.el3.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.el3.p4.pt()); // check that I have the correct formula 
//             m_evt.el3.corpfiso    = samesign::leptonIsolation(el3_id, el3_idx);
//             m_evt.el3.corpfiso04  = samesign::electronIsolationPF2012_cone04(el3_idx);
//             m_evt.el3.effarea     = samesign::EffectiveArea03(el3_id, el3_idx);
//             m_evt.el3.effarea04   = samesign::EffectiveArea04(el3_id, el3_idx);
//             m_evt.el3.is_fo       = IsFO(el3_id, el3_idx); 
//             m_evt.el3.is_num      = IsNumerator(el3_id, el3_idx);
//             m_evt.el3.is_den      = IsDenominator(el3_id, el3_idx);
//             m_evt.el3.mt          = rt::Mt(m_evt.el3.p4, met, met_phi);
//             m_evt.el3.passes_id   = samesign::isGoodLepton(el3_id, el3_idx, m_use_el_eta);
//             m_evt.el3.passes_iso  = samesign::isIsolatedLepton(el3_id, el3_idx);
//         }

        int mu3_idx  = -1;
        int mu3_id   = 0;
        float mu3_pt = -999999.0;
        LorentzVector mu3_tight_p4(0, 0, 0, 0);
        LorentzVector mu3_loose_p4(0, 0, 0, 0);
        LorentzVector mu3_ssv5_p4(0, 0, 0, 0);
        for (size_t mu_idx = 0; mu_idx != mus_p4().size(); mu_idx++)
        {
            const LorentzVector& mu_p4 = mus_p4().at(mu_idx);

            if (mu_p4.pt() < mu_min_pt)             {continue;}
            if (lep1_is_mu and mu_idx == lep1_idx) {continue;}
            if (lep2_is_mu and mu_idx == lep2_idx) {continue;}

            // set 3rd muon vars
            if (mu_p4.pt() > mu3_pt)
            {
                mu3_idx = mu_idx;
                mu3_id  = -13 * mus_charge().at(mu_idx);
                mu3_pt  = mu_p4.pt();
            }

            // tight WP
            if (passes_muid_wp2012(mu_idx, mu2012_tightness::TIGHT) and (mu_p4.pt() > mu3_tight_p4.pt()))
            {
                mu3_tight_p4 = mu_p4; 
            }

            // loose WP
            if (passes_muid_wp2012(mu_idx, mu2012_tightness::LOOSE) and (mu_p4.pt() > mu3_loose_p4.pt()))
            {
                mu3_loose_p4 = mu_p4; 
            }

            // full ss2012 selection
            if (samesign::isGoodLepton(13, mu_idx) and (mu_p4.pt() > mu3_ssv5_p4.pt()))
            {
                mu3_ssv5_p4 = mu_p4; 
            }
        }
        m_evt.mu_muid_loose_p4 = mu3_loose_p4;
        m_evt.mu_muid_tight_p4 = mu3_tight_p4;
        m_evt.mu_muid_ssv5_p4  = mu3_ssv5_p4;
//         m_evt.mu3.FillCommon(mu3_id, mu3_idx);
//         if (mu3_idx >= 0)
//         {
//             m_evt.mu3.cordetiso   = m_evt.mu3.detiso   - (log(m_evt.mu3.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.mu3.p4.pt()); // check that I have the correct formula 
//             m_evt.mu3.cordetiso04 = m_evt.mu3.detiso04 - (log(m_evt.mu3.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.mu3.p4.pt()); // check that I have the correct formula 
//             m_evt.mu3.corpfiso    = samesign::leptonIsolation(mu3_id, mu3_idx);
//             m_evt.mu3.effarea     = samesign::EffectiveArea03(mu3_id, mu3_idx);
//             m_evt.mu3.effarea04   = samesign::EffectiveArea04(mu3_id, mu3_idx);
//             m_evt.mu3.dbeta       = mus_isoR03_pf_PUPt().at(mu3_idx);
//             m_evt.mu3.dbeta04     = mus_isoR04_pf_PUPt().at(mu3_idx);
//             m_evt.mu3.is_fo       = IsFO(mu3_id, mu3_idx); 
//             m_evt.mu3.is_num      = IsNumerator(mu3_id, mu3_idx);
//             m_evt.mu3.is_den      = IsDenominator(mu3_id, mu3_idx);
//             m_evt.mu3.mt          = rt::Mt(m_evt.mu3.p4, met, met_phi);
//             m_evt.mu3.passes_id   = samesign::isGoodLepton(mu3_id, mu3_idx, m_use_el_eta);
//             m_evt.mu3.passes_iso  = samesign::isIsolatedLepton(mu3_id, mu3_idx);
//         }

        // fill common branches for lep3
        int lep3_idx  = (mu3_pt > el3_pt ? mu3_idx : el3_idx); 
        int lep3_id   = (mu3_pt > el3_pt ? mu3_id  : el3_id ); 
        m_evt.lep3.FillCommon(lep3_id, lep3_idx);
        if (lep3_idx >= 0)
        {
            const bool lep3_is_mu  = abs(lep3_id)==13;
            const bool lep3_is_el  = abs(lep3_id)==11;
            m_evt.lep3.cordetiso   = m_evt.lep3.detiso   - (log(m_evt.lep3.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep3.p4.pt()); // check that I have the correct formula 
            m_evt.lep3.cordetiso04 = m_evt.lep3.detiso04 - (log(m_evt.lep3.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep3.p4.pt()); // check that I have the correct formula 
            m_evt.lep3.corpfiso    = samesign::leptonIsolation(lep3_id, lep3_idx);
            m_evt.lep3.corpfiso04  = (lep3_is_el) ? samesign::electronIsolationPF2012_cone04(lep3_idx) : -999999.0;  
            m_evt.lep3.effarea     = samesign::EffectiveArea03(lep3_id, lep3_idx);
            m_evt.lep3.effarea04   = samesign::EffectiveArea04(lep3_id, lep3_idx);
            m_evt.lep3.dbeta       = (lep3_is_mu) ? mus_isoR03_pf_PUPt().at(lep3_idx) : -99999.0;
            m_evt.lep3.dbeta04     = (lep3_is_mu) ? mus_isoR04_pf_PUPt().at(lep3_idx) : -99999.0;
            m_evt.lep3.is_fo       = IsFO(lep3_id, lep3_idx); 
            m_evt.lep3.is_num      = IsNumerator(lep3_id, lep3_idx);
            m_evt.lep3.is_den      = IsDenominator(lep3_id, lep3_idx);
            m_evt.lep3.mt          = rt::Mt(m_evt.lep3.p4, met, met_phi);
            m_evt.lep3.passes_id   = samesign::isGoodLepton(lep3_id, lep3_idx, m_use_el_eta);
            m_evt.lep3.passes_iso  = samesign::isIsolatedLepton(lep3_id, lep3_idx);
            m_evt.lep3_wfr         = GetFakeRateValue(lep3_id, lep3_idx);
            m_evt.lep3_wflip       = GetFlipRateValue(lep3_id, lep3_idx);
        }

        //----------------------------------------
        // TAU
        //----------------------------------------

        int indexTauMax = -1;
        double ptTauMax = 0.0;

        int indexTauLooseMax = -1;
        double ptTauLooseMax = 0.0;

        int indexTauMax15 = -1;
        double ptTauMax15 = 0.0;


        for (unsigned int itau = 0; itau < cms2.taus_pf_p4().size(); itau++)
        {
            if(cms2.taus_pf_p4().at(itau).pt() < 15) {continue;}

            ///
            bool isHypLepton = false;
            if (rt::DeltaR(cms2.taus_pf_p4().at(itau), m_evt.lep1.p4) < 0.4) {isHypLepton = true;}
            if (rt::DeltaR(cms2.taus_pf_p4().at(itau), m_evt.lep2.p4) < 0.4) {isHypLepton = true;}

            if (isHypLepton) {continue;}
            if (!cms2.taus_pf_byDecayModeFinding().at(itau)) {continue;}

            // isolation Medium ; pt > 15
            if (cms2.taus_pf_byMediumIsolationMVA2().at(itau))
            {
                if (cms2.taus_pf_p4().at(itau).pt() > ptTauMax15)
                {
                    ptTauMax15 = cms2.taus_pf_p4().at(itau).pt();
                    indexTauMax15 = itau;
                }	
            }

            if (cms2.taus_pf_p4().at(itau).pt() < 20) {continue;}

            // isolation Medium ; pt > 20    
            if (cms2.taus_pf_byMediumIsolationMVA2().at(itau))
            {
                if (cms2.taus_pf_p4().at(itau).pt() > ptTauMax)
                {
                    ptTauMax = cms2.taus_pf_p4().at(itau).pt();
                    indexTauMax = itau;
                }	
            }

            // isolation Loose ; pt > 20
            if (taus_pf_byLooseIsolationMVA2().at(itau))
            {
                if (taus_pf_p4().at(itau).pt() > ptTauLooseMax)
                {
                    ptTauLooseMax = cms2.taus_pf_p4().at(itau).pt();
                    indexTauLooseMax = itau;
                }	
            }
        }

        if (indexTauMax15 != -1)
        {
            m_evt.pfTau15 = cms2.taus_pf_p4().at(indexTauMax15);
            if (cms2.taus_pf_pfcandIndicies().at(indexTauMax15).size() > 0)
            {
                int leadingPtCand_index = cms2.taus_pf_pfcandIndicies().at(indexTauMax15).front();
                m_evt.pfTau15_leadPtcand = cms2.pfcands_p4().at(leadingPtCand_index);
                m_evt.pfTau15_leadPtcandID = cms2.pfcands_particleId().at(leadingPtCand_index);
            }
        }

        if (indexTauMax != -1)
        {
            m_evt.pfTau = cms2.taus_pf_p4().at(indexTauMax);
            if (cms2.taus_pf_pfcandIndicies().at(indexTauMax).size() > 0)
            {
                int leadingPtCand_index = cms2.taus_pf_pfcandIndicies().at(indexTauMax).front();
                m_evt.pfTau_leadPtcand = cms2.pfcands_p4().at(leadingPtCand_index);
                m_evt.pfTau_leadPtcandID = cms2.pfcands_particleId().at(leadingPtCand_index);
            }
        }

        if (indexTauLooseMax != -1)
        {
            m_evt.pfTauLoose = cms2.taus_pf_p4().at(indexTauLooseMax);
            if (cms2.taus_pf_pfcandIndicies().at(indexTauLooseMax).size() > 0)
            {
                int leadingPtCand_index = cms2.taus_pf_pfcandIndicies().at(indexTauLooseMax).front();
                m_evt.pfTauLoose_leadPtcand = cms2.pfcands_p4().at(leadingPtCand_index);
                m_evt.pfTauLoose_leadPtcandID = cms2.pfcands_particleId().at(leadingPtCand_index);
            }
        }        

        // tau veto
        m_evt.passes_tau_veto = PassesTauVeto(); 

        // track iso veto
        m_evt.passes_isotrk_veto = PassesIsoTrkVeto(m_evt.lep1.p4, m_evt.lep2.p4); 

        // Fill the tree
        m_tree->Fill();

        if (m_sync_print)
        {
            PrintJetInfo(Form("passing jets for hyp %d"     , hyp_idx), m_evt.vjets_p4   );
            PrintJetInfo(Form("passing jets JES+ for hyp %d", hyp_idx), m_evt.vjets_p4_up);
            PrintJetInfo(Form("passing jets JES- for hyp %d", hyp_idx), m_evt.vjets_p4_dn);
        }


        // printout
        if (m_evt.is_good_lumi && m_evt.njets >= 2)
        {
            scale = 1.0;
            if (dilepton_type==DileptonHypType::MUMU)
            {
                if(m_verbose) {cout << "type == mm" << endl;}
                if(charge_type==DileptonChargeType::SS) m_count_nobtag_ss[0] += scale;
                if(charge_type==DileptonChargeType::SF) m_count_nobtag_sf[0] += scale;
                if(charge_type==DileptonChargeType::DF) m_count_nobtag_df[0] += scale;
                if(charge_type==DileptonChargeType::OS) m_count_nobtag_os[0] += scale;
                if(charge_type==DileptonChargeType::SS && m_evt.nbtags > 1) m_count_ss[0] += scale;
                if(charge_type==DileptonChargeType::SF && m_evt.nbtags > 1) m_count_sf[0] += scale;
                if(charge_type==DileptonChargeType::DF && m_evt.nbtags > 1) m_count_df[0] += scale;
                if(charge_type==DileptonChargeType::OS && m_evt.nbtags > 1) m_count_os[0] += scale;
            }
            if (dilepton_type==DileptonHypType::EMU)
            {
                if(m_verbose) {cout << "type == em" << endl;}
                if(charge_type==DileptonChargeType::SS) m_count_nobtag_ss[1] += scale;
                if(charge_type==DileptonChargeType::SF) m_count_nobtag_sf[1] += scale;
                if(charge_type==DileptonChargeType::DF) m_count_nobtag_df[1] += scale;
                if(charge_type==DileptonChargeType::OS) m_count_nobtag_os[1] += scale;
                if(charge_type==DileptonChargeType::SS && m_evt.nbtags > 1) m_count_ss[1] += scale;
                if(charge_type==DileptonChargeType::SF && m_evt.nbtags > 1) m_count_sf[1] += scale;
                if(charge_type==DileptonChargeType::DF && m_evt.nbtags > 1) m_count_df[1] += scale;
                if(charge_type==DileptonChargeType::OS && m_evt.nbtags > 1) m_count_os[1] += scale;
            }
            if (dilepton_type==DileptonHypType::EE)
            {
                if(m_verbose) {cout << "type == ee" << endl;}
                if(charge_type==DileptonChargeType::SS) m_count_nobtag_ss[2] += scale;
                if(charge_type==DileptonChargeType::SF) m_count_nobtag_sf[2] += scale;
                if(charge_type==DileptonChargeType::DF) m_count_nobtag_df[2] += scale;
                if(charge_type==DileptonChargeType::OS) m_count_nobtag_os[2] += scale;
                if(charge_type==DileptonChargeType::SS && m_evt.nbtags > 1) m_count_ss[2] += scale;
                if(charge_type==DileptonChargeType::SF && m_evt.nbtags > 1) m_count_sf[2] += scale;
                if(charge_type==DileptonChargeType::DF && m_evt.nbtags > 1) m_count_df[2] += scale;
                if(charge_type==DileptonChargeType::OS && m_evt.nbtags > 1) m_count_os[2] += scale;
            }
            // count all 
            {
                if(charge_type==DileptonChargeType::SS) m_count_nobtag_ss[3] += scale;
                if(charge_type==DileptonChargeType::SF) m_count_nobtag_sf[3] += scale;
                if(charge_type==DileptonChargeType::DF) m_count_nobtag_df[3] += scale;
                if(charge_type==DileptonChargeType::OS) m_count_nobtag_os[3] += scale;
                if(charge_type==DileptonChargeType::SS && m_evt.nbtags > 1) m_count_ss[3] += scale;
                if(charge_type==DileptonChargeType::SF && m_evt.nbtags > 1) m_count_sf[3] += scale;
                if(charge_type==DileptonChargeType::DF && m_evt.nbtags > 1) m_count_df[3] += scale;
                if(charge_type==DileptonChargeType::OS && m_evt.nbtags > 1) m_count_os[3] += scale;
            }
        }
    }
    catch (std::exception& e)
    {
        cout << Form("Fatal error on run %d, ls %d, event %d", evt_run(), evt_lumiBlock(), evt_event()) << endl;
        cout << e.what() << endl;
        cout << "Exiting..." << endl;
        exit(1);
    }

    // done
    return 0;
}

float SSAnalysisLooper::GetFakeRateValue(const int lep_id, const int lep_idx) const 
{
    using namespace tas;

    if (!h_mufr)
    {
        if (m_verbose) {std::cout << "h_mufr is NULL! returing zero..." << std::endl;}
        return 0.0;
    }

    if (!h_elfr)
    {
        if (m_verbose) {std::cout << "h_elfr is NULL! returing zero..." << std::endl;}
        return 0.0;
    }

    if (abs(lep_id)==13) 
    {
        float pt     = mus_p4().at(lep_idx).pt();
        float eta    = mus_p4().at(lep_idx).eta();
        float max_pt = h_mufr->GetYaxis()->GetXmax()-0.01;
        int pt_bin   = h_mufr->GetYaxis()->FindBin(min(pt, max_pt));
        int eta_bin  = h_mufr->GetXaxis()->FindBin(fabs(eta));
        return h_mufr->GetBinContent(eta_bin, pt_bin);
    }
    else if (abs(lep_id)==11) 
    {
        float pt     = els_p4().at(lep_idx).pt();
        float eta    = els_p4().at(lep_idx).eta();
        float max_pt = h_elfr->GetYaxis()->GetXmax()-0.01;
        int pt_bin   = h_elfr->GetYaxis()->FindBin(min(pt, max_pt));
        int eta_bin  = h_elfr->GetXaxis()->FindBin(fabs(eta));
        return h_elfr->GetBinContent(eta_bin, pt_bin);
    }
    return 0.0;
}

float SSAnalysisLooper::GetFlipRateValue(const int lep_id, const int lep_idx) const 
{
    using namespace tas;

    // only applies to electrons
    if (abs(lep_id) != 11)
    {
        return 0.0;
    }

    if (!h_flip)
    {
        if (m_verbose) {std::cout << "h_flip is NULL! returing zero..." << std::endl;}
        return 0.0;
    }

    float pt     = els_p4().at(lep_idx).pt();
    float eta    = els_p4().at(lep_idx).eta();
    float max_pt = h_flip->GetYaxis()->GetXmax()-0.01;
    int pt_bin   = h_flip->GetYaxis()->FindBin(min(pt, max_pt));
    int eta_bin  = h_flip->GetXaxis()->FindBin(fabs(eta));
    return h_flip->GetBinContent(eta_bin, pt_bin);
}

bool SSAnalysisLooper::PassesIsoTrkVeto(const LorentzVector& l1_p4, const LorentzVector& l2_p4) const
{
    //------------------------------------------------------
    // track isolation variable definition
    //------------------------------------------------------
    const float dz_cut = 0.1;

    //------------------------------------------------------
    // store pt and iso for most isolated track (pt>10 GeV) and (pt>5 GeV)
    //------------------------------------------------------

    float pfcandiso5looseZ    = -9999;
    float pfcandpt5looseZ     = -9999;
    int pfcandid5looseZ       = -9999;
    float pfcandisoOS10looseZ = -9999;
    float pfcandptOS10looseZ  = -9999;
    int pfcandidOS10looseZ    = -9999;

    std::vector<LorentzVector> goodLeptons;
    if (l1_p4.pt() > 0.01) goodLeptons.push_back(l1_p4);
    if (l2_p4.pt() > 0.01) goodLeptons.push_back(l2_p4);

    for (size_t ipf = 0; ipf < cms2.pfcands_p4().size(); ipf++)
    {
        if (cms2.pfcands_p4().at(ipf).pt() < 5) {continue;}
        if (cms2.pfcands_charge().at(ipf) == 0) {continue;}

        at::myTrackIso myTrackIso = at::trackIso(ipf);

        bool isGoodLepton = false;
        for (int ilep = 0; ilep < (int)goodLeptons.size(); ilep++)
        {
            if (ROOT::Math::VectorUtil::DeltaR(cms2.pfcands_p4().at(ipf), goodLeptons.at(ilep)) < 0.1) {isGoodLepton = true;}
        }

        // this is with the OS requirement
        float charge = (cms2.pfcands_particleId().at(ipf) * m_evt.lep1.charge);

        // charge < 0 is a SS , charge > 0 is a OS for e/mu; need to flip for pions
        if ((abs(cms2.pfcands_particleId().at(ipf)) != 11) && (abs(cms2.pfcands_particleId().at(ipf)) != 13))
        {
            charge *= (-1); 
        }

        //////////

        int itrk = -1;
        float mindz = 999;

        if (abs(cms2.pfcands_particleId().at(ipf)) != 11)
        {
            itrk = cms2.pfcands_trkidx().at(ipf);
            if (itrk >= (int)cms2.trks_trk_p4().size() || itrk < 0) continue;
            mindz = trks_dz_pv(itrk,0).first;
        }

        if (abs(cms2.pfcands_particleId().at(ipf)) == 11 && cms2.pfcands_pfelsidx().at(ipf) >= 0)
        {
            itrk = cms2.els_gsftrkidx().at(cms2.pfcands_pfelsidx().at(ipf));
            if (itrk >= (int)cms2.gsftrks_p4().size() || itrk < 0) continue;
            mindz = gsftrks_dz_pv(itrk,0).first;
        }

        // start with loose dz cut
        if (fabs(mindz) > dz_cut) {continue;}

        // store loose definition to compare with previous results
        float iso = myTrackIso.iso_dr03_dz010_pt00 / cms2.pfcands_p4().at(ipf).pt();

        if (cms2.pfcands_p4().at(ipf).pt() >= 5 && iso < pfcandiso5looseZ && !isGoodLepton)
        {
            pfcandiso5looseZ = iso;
            pfcandpt5looseZ  = cms2.pfcands_p4().at(ipf).pt();
            pfcandid5looseZ  = cms2.pfcands_particleId().at(ipf);
        }

        if (cms2.pfcands_p4().at(ipf).pt() >= 10 && iso < pfcandisoOS10looseZ && !isGoodLepton && charge > 0)
        {
            pfcandisoOS10looseZ = iso;
            pfcandptOS10looseZ  = cms2.pfcands_p4().at(ipf).pt();
            pfcandidOS10looseZ  = cms2.pfcands_particleId().at(ipf);
        }
    }

    // pass isolated track veto
    // We want to check for the generic track only there is now good e/mu candidate
    if (pfcandptOS10looseZ > 0.0 && abs(pfcandid5looseZ) != 13 && abs(pfcandid5looseZ) != 11 && pfcandisoOS10looseZ < 0.1) {return false;}
    if (pfcandpt5looseZ    > 0.0 && abs(pfcandid5looseZ) == 13 && pfcandiso5looseZ < 0.2)                                  {return false;}
    if (pfcandpt5looseZ    > 0.0 && abs(pfcandid5looseZ) == 11 && pfcandiso5looseZ < 0.2)                                  {return false;}

    // if here then return true
    return true;
}


bool SSAnalysisLooper::PassesTauVeto() const
{
    if(m_evt.pfTau_leadPtcandID != -999999) {return false;}
    return true;
}
