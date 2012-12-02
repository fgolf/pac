#include "AnalysisLooper.h"

// c++
#include <stdexcept>
#include <algorithm>
#include <fstream>

// cms2
//#include "CMS2.h"
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

// Tools
#include "SameSignTree.h"
#include "at/Predicates.h"
#include "at/DileptonHypType.h"
#include "at/DileptonChargeType.h"
#include "at/VtxReweight.h"
#include "at/GoodRun.h"
#include "at/PrintIdIsoInfo.h"
#include "rt/RootTools.h"
#include "CTable.h"
#include "GenParticleStruct.h"
#include "EfficiencyModelTools.h"
#include "ScaleFactors.h"
#include "TTbarBreakDown.h"

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
    if (-1 < idx && static_cast<unsigned int>(idx) >= hyp_lt_p4().size())
    {
        return -999999.0;
    }
    else
    {
        return (hyp_lt_p4().at(idx).pt() + hyp_ll_p4().at(idx).pt());
    }
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

void CompareHyps(std::pair<size_t, DileptonChargeType::value_type>& best_hyp, size_t hyp_idx, const DileptonChargeType::value_type& new_type)
{
    short current_type = best_hyp.second;
    float new_pt       = hyp_lt_p4().at(hyp_idx).pt() + hyp_ll_p4().at(hyp_idx).pt();
    float current_pt   = hyp_lt_p4().at(best_hyp.first).pt() + hyp_ll_p4().at(best_hyp.first).pt();

    if (current_type == DileptonChargeType::static_size)
    {
        goto use_new_hyp;
    }
    else if (new_type < current_type)
    {
        goto use_new_hyp;
    }
    else if (new_type > current_type)
    {
        return;
    }
    else 
    {
        if (new_pt > current_pt)
        {
            goto use_new_hyp;
        }
        else
        {
            return;
        }
    }
use_new_hyp:
    {
        best_hyp = make_pair(hyp_idx, new_type);    
        return;
    }
}

// set then numerator bool
//bool IsNumerator(std::pair<size_t, DileptonChargeType::value_type>& hyp, bool is_lt)
bool IsNumerator(const HypInfo& hyp, bool is_lt)
{
    if (hyp.charge_type == DileptonChargeType::static_size)
    {
        return false;
    }
    switch (hyp.charge_type)
    {
    case DileptonChargeType::DF: return false; break;
    case DileptonChargeType::SS: return true; break;
    case DileptonChargeType::SF: 
    {
        bool lt_num = samesign::isNumeratorLepton(cms2.hyp_lt_id().at(hyp.idx), cms2.hyp_lt_index().at(hyp.idx));
        bool ll_num = samesign::isNumeratorLepton(cms2.hyp_ll_id().at(hyp.idx), cms2.hyp_ll_index().at(hyp.idx));
        if (lt_num && !ll_num)
        {
            return is_lt ? true : false;
        }
        if (!lt_num && ll_num)
        {
            return is_lt ? false : true;
        }
        break;
    }
    default: return false;
    }
    return false;
}

//bool IsDenominator(std::pair<size_t, DileptonChargeType::value_type>& hyp, bool is_lt)
bool IsDenominator(const HypInfo& hyp, bool is_lt)
{
    if (hyp.charge_type == DileptonChargeType::static_size)
    {
        return false;
    }
    switch (hyp.charge_type)
    {
    case DileptonChargeType::DF: return true; break;
    case DileptonChargeType::SS: return false; break;
    case DileptonChargeType::SF: 
    {
        bool lt_num = samesign::isNumeratorLepton(cms2.hyp_lt_id().at(hyp.idx), cms2.hyp_lt_index().at(hyp.idx));
        bool ll_num = samesign::isNumeratorLepton(cms2.hyp_ll_id().at(hyp.idx), cms2.hyp_ll_index().at(hyp.idx));
        if (lt_num && !ll_num)
        {
            return is_lt ? false : true;
        }
        if (!lt_num && ll_num)
        {
            return is_lt ? true : false;
        }
        break;
    }
    default: return false;
    }
    return false;
}

float EffectiveArea03(int id, int idx)
{
    if (abs(id)!=11)
        return -999990.0;

    float etaAbs = fabs(els_etaSC()[idx]);

    // get effective area
    float AEff = 0.;
    if (etaAbs <= 1.0) AEff = 0.10;
    else if (etaAbs > 1.0 && etaAbs <= 1.479) AEff = 0.12;
    else if (etaAbs > 1.479 && etaAbs <= 2.0) AEff = 0.085;
    else if (etaAbs > 2.0 && etaAbs <= 2.2) AEff = 0.11;
    else if (etaAbs > 2.2 && etaAbs <= 2.3) AEff = 0.12;
    else if (etaAbs > 2.3 && etaAbs <= 2.4) AEff = 0.12;
    else if (etaAbs > 2.4) AEff = 0.13;
    return AEff;
}

// place holder until I figure out the right thing
float EffectiveArea04(int, int)
{
    return -99999.0;
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
//
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

void PrintForSync(int ihyp, float mu_min_pt, float el_min_pt, enum JetType jet_type, int jet_met_scale, FactorizedJetCorrector *jet_corrector = NULL, MetCorrector *met_corrector = NULL)
{
    // convenience
    const LorentzVector& lt_p4 = hyp_lt_p4().at(ihyp);
    const LorentzVector& ll_p4 = hyp_ll_p4().at(ihyp);
    int lt_id                  = hyp_lt_id().at(ihyp);
    int ll_id                  = hyp_ll_id().at(ihyp);
    int lt_idx                 = hyp_lt_index().at(ihyp);
    int ll_idx                 = hyp_ll_index().at(ihyp);
    bool lt_passes_id          = samesign::isGoodLepton(lt_id, lt_idx);
    bool ll_passes_id          = samesign::isGoodLepton(ll_id, ll_idx);
    float lt_iso               = samesign::leptonIsolation(lt_id, lt_idx);
    float ll_iso               = samesign::leptonIsolation(ll_id, ll_idx);

    // channel names
    const size_t n_channel_names = 4; 
    const std::string channel_names[n_channel_names] = {"All", "MM", "EM", "EE"};

    int num_jets = 0;
    int num_btags = 0;
    float ht = 0.;
    float met = evt_pfmet_type1cor();
    if (not jet_corrector)
    {
        num_jets  = samesign::nJets(ihyp, jet_type                       , /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
        num_btags = samesign::nBtaggedJets(ihyp, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
        ht        = samesign::sumJetPt(ihyp, jet_type                    , /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, jet_met_scale);
        met       = evt_pfmet_type1cor();
    }
    else
    {
        num_jets  = samesign::nJets(ihyp, jet_corrector, jet_type                       , /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
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

    //if (samesign::isNumeratorHypothesis(ihyp))
    //if (samesign::isNumeratorHypothesis(ihyp))
    //if (samesign::isDenominatorHypothesis(ihyp))
    {
        //cout << "Run | LS | Event | channel | Lep1Pt | Lep1Eta | Lep1Phi | Lep1ID | Lep1Iso | Lep2Pt | Lep2Eta | Lep2Phi | Lep2ID | Lep1Iso | MET | HT | nJets | nbJets" << endl;
        cout << Form("%6u | %3u | %12u | %s | %4.3f | %2.3f | %2.3f | %u | %4.3f | %4.3f | %2.3f | %2.3f | %u | %4.3f | %4.3f | %4.3f | %u | %u",
                     evt_run(), evt_lumiBlock(), evt_event(),
                     channel_names[type].c_str(),
                     l1_p4.pt(), l1_p4.eta(), l1_p4.phi(), l1_passes_id, l1_iso,
                     l2_p4.pt(), l2_p4.eta(), l2_p4.phi(), l2_passes_id, l2_iso,
                     met,
                     ht,
                     num_jets,
                     num_btags) << endl;
    }
    //else
    //{
    //    cout << Form("%6u | %3u | %12u | %s | %4.3f | %2.3f | %2.3f | %u | %4.3f | %4.3f | %2.3f | %2.3f | %u | %4.3f | %4.3f | %s | %s | %s",
    //                 evt_run(), evt_lumiBlock(), evt_event(),
    //                 channel_names[type].c_str(),
    //                 l1_p4.pt(), l1_p4.eta(), l1_p4.phi(), l1_passes_id, l1_iso,
    //                 l2_p4.pt(), l2_p4.eta(), l2_p4.phi(), l2_passes_id, l2_iso,
    //                 met,
    //                 "-",
    //                 "-",
    //                 "-") << endl;
    //}

    //if (evt_run() == 191247 && evt_lumiBlock() == 189 && evt_event() == 281392234)
    //if (evt_run() == 191247 && evt_lumiBlock() == 59 && evt_event() == 91075424)
    //if ((evt_run() == 191247 && evt_lumiBlock() == 59 && evt_event() == 91551153))
    //if ((evt_run() == 191247 && evt_lumiBlock() == 59 && evt_event() == 90509753))
    //if ((evt_run() == 190736 && evt_lumiBlock() == 143 && evt_event() == 147343009))
    //if ((evt_run() == 190736 && evt_lumiBlock() == 143 && evt_event() == 147655281))
    //if ((evt_run() == 191247 && evt_lumiBlock() == 60 && evt_event() == 93008232))
    //if ((evt_run() == 191247 && evt_lumiBlock() == 60 && evt_event() == 92441355))
    //if ((evt_run() == 191247 && evt_lumiBlock() == 60 && evt_event() == 93455346))
    //if ((evt_run() == 191247 && evt_lumiBlock() == 66 && evt_event() == 102084731))
    //if ((evt_run() == 190736  && evt_lumiBlock() == 144 && evt_event() == 148335250))
    //{
    //	cout << "ID lepton 1: "; PrintIdInfo(l1_id, l1_idx);
    //	cout << "ID lepton 2: "; PrintIdInfo(l2_id, l2_idx);
    //	cout << "ID iso 1: "; PrintIsoInfo(l1_id, l1_idx);
    //	cout << "ID iso 2: "; PrintIsoInfo(l2_id, l2_idx);
    //}
}

// construct:
SSAnalysisLooper::SSAnalysisLooper
(
    const std::string& root_file_name,
    const Sample::value_type& sample,
    const AnalysisType::value_type& analysis_type,
    const std::string& fake_rate_file_name,
    const std::string& flip_rate_file_name,
    const std::string& fake_rate_hist_name,
    const std::string& goodrun_file_name,
    const std::string& vtxreweight_file_name,
    double luminosity,
    int njets,
    bool sparms,
    int jetMetScale,
    bool is_fast_sim,
    bool sync_print,
    bool verbose,
    const std::string apply_jec_otf
)
    : AnalysisWithTree(root_file_name, "tree", "baby tree for SS2012 analysis")
    , m_sample(sample)
    , m_analysis_type(analysis_type)
    , m_lumi(luminosity)
    , m_njets(njets)
    , m_jetMetScale(jetMetScale)
    , m_is_fast_sim(is_fast_sim)
    , m_sparms(sparms)
    , m_sync_print(sync_print)
    , m_verbose(verbose)
    , hyp_count(0)
    //, good_lep_count(0)
    //, iso_lep_count(0)
    //, num_lep_count(0)
    , jet_corrector(NULL)
    , met_corrector(NULL)
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

        std::string path = rt::getenv("PAC");
        if (!path.empty())
        {
            path += "/externals/source/cms2_core/HEAD/CORE/jetcorr/data/";
            m_list_of_jec_filenames.push_back(Form("%s/%s_L1FastJet_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            m_list_of_jec_filenames.push_back(Form("%s/%s_L2Relative_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            m_list_of_jec_filenames.push_back(Form("%s/%s_L3Absolute_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            if (m_sample <= at::Sample::datame)
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
            if (m_sample <= at::Sample::datame)
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
        
        jet_corrector = makeJetCorrector(m_list_of_jec_filenames);
        if (not jet_corrector)
        {
            throw std::runtime_error("ERROR: SSAnalysisLooper: unable to create jet_corrector");
        }
        met_corrector = new MetCorrector(m_list_of_jec_filenames);
        if (not met_corrector)
        {
            throw std::runtime_error("ERROR: SSAnalysisLooper: unable to create met_corrector");
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
    //h_mufr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get(fake_rate_hist_name.c_str())->Clone()));
    if (m_analysis_type == ss::AnalysisType::high_pt)
    {
        h_mufr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get("h_mufr40c")->Clone()));
        h_elfr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get("h_elfr40c")->Clone()));
    }
    else if (m_analysis_type == ss::AnalysisType::low_pt)
    {
        h_mufr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get("h_mufr40c_iso"  )->Clone()));
        h_elfr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get("h_elfr40c_noiso")->Clone()));
    }
    if (not h_mufr) {throw std::runtime_error("ERROR: SSAnalysisLooper: h_mufr40c doesn't exist");}
    h_mufr->SetDirectory(0);
    if (not h_elfr) {throw std::runtime_error("ERROR: SSAnalysisLooper: h_elfr40c doesn't exist");}
    h_elfr->SetDirectory(0);

    cout << "using mu FR hist : " << h_mufr->GetName() << endl;
    cout << "using el FR hist : " << h_elfr->GetName() << endl;

    // set the fake rate histograms
    std::auto_ptr<TFile> flip_rate_file(rt::OpenRootFile(flip_rate_file_name));
    cout << "using FL file : " << flip_rate_file->GetName() << endl;
    h_flip.reset(dynamic_cast<TH2F*>(flip_rate_file->Get("flipRate")->Clone()));
    if (not h_flip) {throw std::runtime_error("ERROR: SSAnalysisLooper: flipRate doesn't exist");}
    h_flip->SetDirectory(0);

    // begin job
    BeginJob();
}

// destroy:
SSAnalysisLooper::~SSAnalysisLooper()
{
    delete jet_corrector;
    delete met_corrector;
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
    // initialize branches
    m_evt.Reset();
    m_evt.SetBranches(*m_tree);

    if (m_sync_print)
    {
        cout << "Run | LS | Event | channel | " 
                "Lep1Pt | Lep1Eta | Lep1Phi | Lep1ID | Lep1Iso | "
                "Lep2Pt | Lep2Eta | Lep2Phi | Lep2ID | Lep1Iso | "
                "MET | HT | nJets | nbJets" << endl;
    }
}


void SSAnalysisLooper::EndJob()
{
    cout << "Number of dilepton hypotheses passing pT > 20, 20; |eta| < 2.4, 2.4; SS:\t" << hyp_count << endl;
    //cout << "Number of dilepton hypotheses passing above and goodLepton:\t" << good_lep_count << endl;
    //cout << "Number of dilepton hypotheses passing above and isoLepton:\t" << iso_lep_count << endl;
    //cout << "Number of dilepton hypotheses passing above and numLepton:\t" << num_lep_count << endl;

    CTable yield_table;
    yield_table.setTitle("yields for SS Analysis 2012 (# btags >= 2)");
    yield_table.useTitle();
    yield_table.setTable() (   "mm",         "em",          "ee",          "all")
                           ("count ss" , m_count_ss[0], m_count_ss[1], m_count_ss[2], m_count_ss[3]) 
                           ("count sf" , m_count_sf[0], m_count_sf[1], m_count_sf[2], m_count_sf[3]) 
                           ("count df" , m_count_df[0], m_count_df[1], m_count_df[2], m_count_df[3])
                           ("count os" , m_count_os[0], m_count_os[1], m_count_os[2], m_count_os[3]); 
    yield_table.print();

    CTable yield_table2;
    yield_table2.setTitle("yields for SS Analysis 2012 (no btags req)");
    yield_table2.useTitle();
    yield_table2.setTable() (          "mm",                "em",                 "ee",                "all")
                            ("count ss" , m_count_nobtag_ss[0], m_count_nobtag_ss[1], m_count_nobtag_ss[2], m_count_nobtag_ss[3]) 
                            ("count sf" , m_count_nobtag_sf[0], m_count_nobtag_sf[1], m_count_nobtag_sf[2], m_count_nobtag_sf[3]) 
                            ("count df" , m_count_nobtag_df[0], m_count_nobtag_df[1], m_count_nobtag_df[2], m_count_nobtag_df[3])
                            ("count os" , m_count_nobtag_os[0], m_count_nobtag_os[1], m_count_nobtag_os[2], m_count_nobtag_os[3]); 
    yield_table2.print();

    // call base class end job
    AnalysisWithTree::EndJob();
}

int SSAnalysisLooper::SetJetCorrector(std::vector<std::string> &list_of_filenames)
{
    printf("[SSAnalysisLooper] making jet corrector with: \n");
    for (unsigned int idx = 0; idx < list_of_filenames.size(); idx++)
    {
        printf("\t%s\n", list_of_filenames.at(idx).c_str());
    }

    jet_corrector = makeJetCorrector(list_of_filenames);
    met_corrector = new MetCorrector(list_of_filenames);
    if (!jet_corrector && !met_corrector) return 1;
    return 0;
}

int SSAnalysisLooper::Analyze(long event, const std::string& filename)
{
    try
    {
        // select specific events
        //if (!(evt_run() == 1 && evt_lumiBlock() == 5145 && evt_event() == 1542975))
        //if (!(evt_run() == 1 && evt_lumiBlock() == 15021 && evt_event() == 4505298))
        //if (!(evt_event() ==  2413713))
        //{
        //    return 0;
        //}
        //{
        //    cout << "\n-----------------------------------------" << endl; 
        //    cout << Form("running on run %d, ls %d, event %d", evt_run(), evt_lumiBlock(), evt_event()) << endl;
        //}

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

        // gen level  
        // --------------------------------------------------------------------------------------------------------- //
        //bool is_low_pt  = (m_analysis_type == AnalysisType::low_pt );
        bool is_high_pt = (m_analysis_type == AnalysisType::high_pt);

        // lepton pT cut values
        float mu_min_pt = is_high_pt ? 20.0 : 5.0;
        float el_min_pt = is_high_pt ? 20.0 : 10.0;
        float min_pt    = std::min(mu_min_pt, el_min_pt);

        // gen jet info
        if (!evt_isRealData())
        {

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
            m_evt.vgenb_p4       = efftools::getGenBjets(40.0, 2.4);
            m_evt.vgenjets_p4    = efftools::getGenJets(40.0, 2.4);
            m_evt.gen_nbtags     = m_evt.vgenb_p4.size();
            m_evt.gen_njets      = m_evt.vgenjets_p4.size();
            m_evt.gen_ht         = efftools::getGenHT(40.0, 2.4);
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
            return 0;
        }

        // Analysis Selections
        // --------------------------------------------------------------------------------------------------------- //

        // jet type
        JetType jet_type = evt_isRealData() ? JETS_TYPE_PF_FAST_CORR_RESIDUAL : JETS_TYPE_PF_FAST_CORR;

        // loop over hypotheses
        HypInfo best_hyp(0, DileptonChargeType::static_size, DileptonHypType::static_size);
        for (size_t ihyp = 0; ihyp != hyp_type().size(); ihyp++)
        {                
            // leptons variables
            const LorentzVector& lt_p4 = hyp_lt_p4().at(ihyp);
            const LorentzVector& ll_p4 = hyp_ll_p4().at(ihyp);
            int lt_id                  = hyp_lt_id().at(ihyp);
            int ll_id                  = hyp_ll_id().at(ihyp);
            int lt_idx                 = hyp_lt_index().at(ihyp);
            int ll_idx                 = hyp_ll_index().at(ihyp);

            float lt_min_pt = abs(lt_id)==11 ? el_min_pt : mu_min_pt;
            float ll_min_pt = abs(ll_id)==11 ? el_min_pt : mu_min_pt;

            // print for syncing
            if (m_sync_print)
            {
                cout << "printing for hyp index " << ihyp << endl;
                PrintForSync(ihyp, mu_min_pt, el_min_pt, jet_type, m_jetMetScale, jet_corrector, met_corrector);
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

            // check that leptons are from the same vertex
            if (!hypsFromFirstGoodVertex(ihyp))
            {
                if (m_verbose) {std::cout << "fails leptons are from the first good vertex requirement" << std::endl;}
                continue;
            }

            // check if hyp passes trigger
            if (evt_isRealData() && !samesign::passesTrigger(hyp_type().at(ihyp), is_high_pt))
            {
                if (m_verbose) {std::cout << "fails trigger requirement" << std::endl;}
                continue;
            }            // check that leptons are from the same vertex
            if (!hypsFromFirstGoodVertex(ihyp))
            {
                if (m_verbose) {std::cout << "fails leptons are from the first good vertex requirement" << std::endl;}
                continue;
            }

            // check extra Z veto
            if (samesign::makesExtraZ(ihyp))
            {
                if (m_verbose) {std::cout << "fails btag extra Z veto requirement" << std::endl;}
                continue;
            }

            // check if event passes num_jet cut
            int num_jets = samesign::nJets(ihyp, jet_type, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
            if (num_jets < m_njets)
            {
                if (m_verbose) {std::cout << "fails # jets >= " << m_njets << " requirement with " << num_jets << " jets" << std::endl;}
                continue;
            }

            // check extra Gamma* veto
            if (samesign::makesExtraGammaStar(ihyp))
            {
                if (m_verbose) {std::cout << "fails extra Gamma* veto requirement" << std::endl;}
                continue;
            }

            // skip if both are not numerators
            if (!samesign::isDenominatorHypothesis(ihyp))
            {
                if (m_verbose) {std::cout << "fails both leptons are at least denominator requirement" << std::endl;}
                continue;
            }

            // get the hyp type
            DileptonHypType::value_type type = hyp_typeToHypType(hyp_type().at(ihyp));

            // OS (Here a kludge by Claudio to quickly change the meaning of SS and OS .... useful for ttbar as sstop)
            int dummy = 1;
            //if (m_switchSigns) dummy=-1;
            int hyp_q = dummy * hyp_lt_charge().at(ihyp) * hyp_ll_charge().at(ihyp);
            if (hyp_q < 0)
            {
                if (m_verbose) {std::cout << "selected OS hyp" << std::endl;}
                if (!samesign::isNumeratorHypothesis(ihyp))
                {
                    if (m_verbose) {std::cout << "OS hyp doesn't pass ID/ISO requirement" << std::endl;}
                    continue; 
                }
                best_hyp = std::min(best_hyp, HypInfo(ihyp, DileptonChargeType::OS, type));
            }
            else if (hyp_q > 0)
            {
                // same sign event (SS)
                if (samesign::isNumeratorHypothesis(ihyp))
                {
                    hyp_count++;
                    if (m_verbose) {std::cout << "selected SS hyp" << std::endl;}
                    best_hyp = std::min(best_hyp, HypInfo(ihyp, DileptonChargeType::SS, type));
                }
                //else
                //{
                //    if (m_verbose) {std::cout << "SS hyp doesn't pass ID/ISO requirement" << std::endl;}
                //}
                //if (samesign::isGoodLepton(lt_id, lt_idx) && samesign::isGoodLepton(ll_id, ll_idx))
                //{
                //    good_lep_count++;
                //}
                //if (samesign::isIsolatedLepton(lt_id, lt_idx) && samesign::isIsolatedLepton(ll_id, ll_idx))
                //{
                //    iso_lep_count++;
                //}
                //if (samesign::isNumeratorLepton(lt_id, lt_idx) && samesign::isNumeratorLepton(ll_id, ll_idx))
                //{
                //    num_lep_count++;
                //}
                // single fake event (SF)
                else if (samesign::isNumeratorLepton(lt_id, lt_idx) || samesign::isNumeratorLepton(ll_id, ll_idx))
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
        unsigned int hyp_idx = best_hyp.idx;
        DileptonChargeType::value_type event_type = best_hyp.charge_type;

        // all: 0, mm: 1, em: 2, ee: 3
        DileptonHypType::value_type dilepton_type = hyp_p4().empty() ? DileptonHypType::static_size : hyp_typeToHypType(hyp_type().at(hyp_idx));

        // don't write events to the tree that don't pass hypothesis
        if (event_type == DileptonChargeType::static_size)
        {
            if (m_verbose) {std::cout << "fails good event type requirement" << std::endl;}

            // fill event level info 
            m_evt.event_info.FillCommon(m_sample, filename);
            m_evt.dilep_type = DileptonHypType::static_size;

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
            if (m_verbose) {std::cout << "passes good charege type requirement:  " << at::GetDileptonChargeTypeName(event_type) << std::endl;}
            if (m_verbose) {std::cout << "good hyp index is : " << hyp_idx << std::endl;}
        }

        // trigger info
        if (is_high_pt)
        {
            m_evt.trig_mm = passUnprescaledHLTTriggerPattern("HLT_Mu17_Mu8_v");
            m_evt.trig_em = passUnprescaledHLTTriggerPattern("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v") || 
                            passUnprescaledHLTTriggerPattern("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
            m_evt.trig_ee = passUnprescaledHLTTriggerPattern("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
        }
        else
        {

            m_evt.trig_mm = passUnprescaledHLTTriggerPattern("HLT_DoubleMu14_Mass8_PFMET40_v"            ) ||
                            passUnprescaledHLTTriggerPattern("HLT_DoubleMu14_Mass8_PFMET50_v"            ) ||
                            passUnprescaledHLTTriggerPattern("HLT_DoubleMu8_Mass8_PFNoPUHT175_v"         ) ||
                            passUnprescaledHLTTriggerPattern("HLT_DoubleMu8_Mass8_PFNoPUHT225_v"         ) ||
                            passUnprescaledHLTTriggerPattern("HLT_DoubleRelIso1p0Mu5_Mass8_PFNoPUHT175_v") ||
                            passUnprescaledHLTTriggerPattern("HLT_DoubleRelIso1p0Mu5_Mass8_PFNoPUHT225_v") ||
                            passUnprescaledHLTTriggerPattern("HLT_DoubleMu8_Mass8_PFHT175_v"             ) ||
                            passUnprescaledHLTTriggerPattern("HLT_DoubleMu8_Mass8_PFHT225_v"             ) ||
                            passUnprescaledHLTTriggerPattern("HLT_DoubleRelIso1p0Mu5_Mass8_PFHT175_v"    ) ||
                            passUnprescaledHLTTriggerPattern("HLT_DoubleRelIso1p0Mu5_Mass8_PFHT225_v"    );
            m_evt.trig_ee = passUnprescaledHLTTriggerPattern("HLT_DoubleEle8_CaloIdT_TrkIdVL_Mass8_PFNoPUHT175_v") ||
                            passUnprescaledHLTTriggerPattern("HLT_DoubleEle8_CaloIdT_TrkIdVL_Mass8_PFNoPUHT175_v") ||
                            passUnprescaledHLTTriggerPattern("HLT_DoubleEle8_CaloIdT_TrkIdVL_Mass8_PFNoPUHT225_v") ||
                            passUnprescaledHLTTriggerPattern("HLT_DoubleEle8_CaloIdT_TrkIdVL_Mass8_PFHT175_v"    ) ||
                            passUnprescaledHLTTriggerPattern("HLT_DoubleEle8_CaloIdT_TrkIdVL_Mass8_PFHT225_v"    ) ||
                            passUnprescaledHLTTriggerPattern("HLT_DoubleEle14_CaloIdT_TrkIdVL_Mass8_PFMET40_v"   ) ||
                            passUnprescaledHLTTriggerPattern("HLT_DoubleEle14_CaloIdT_TrkIdVL_Mass8_PFMET50_v"   );
            m_evt.trig_em = passUnprescaledHLTTriggerPattern("HLT_Mu14_Ele14_CaloIdT_TrkIdVL_Mass8_PFMET40_v8"           ) ||
                            passUnprescaledHLTTriggerPattern("HLT_Mu14_Ele14_CaloIdT_TrkIdVL_Mass8_PFMET50_v8"           ) ||
                            passUnprescaledHLTTriggerPattern("HLT_Mu8_Ele8_CaloIdT_TrkIdVL_Mass8_PFNoPUHT175_v4"         ) ||
                            passUnprescaledHLTTriggerPattern("HLT_Mu8_Ele8_CaloIdT_TrkIdVL_Mass8_PFNoPUHT225_v4"         ) ||
                            passUnprescaledHLTTriggerPattern("HLT_RelIso1p0Mu5_Ele8_CaloIdT_TrkIdVL_Mass8_PFNoPUHT175_v4") ||
                            passUnprescaledHLTTriggerPattern("HLT_RelIso1p0Mu5_Ele8_CaloIdT_TrkIdVL_Mass8_PFNoPUHT225_v4") ||
                            passUnprescaledHLTTriggerPattern("HLT_Mu8_Ele8_CaloIdT_TrkIdVL_Mass8_PFHT175_v4"             ) ||
                            passUnprescaledHLTTriggerPattern("HLT_Mu8_Ele8_CaloIdT_TrkIdVL_Mass8_PFHT225_v4"             ) ||
                            passUnprescaledHLTTriggerPattern("HLT_RelIso1p0Mu5_Ele8_CaloIdT_TrkIdVL_Mass8_PFHT175_v4"    ) ||
                            passUnprescaledHLTTriggerPattern("HLT_RelIso1p0Mu5_Ele8_CaloIdT_TrkIdVL_Mass8_PFHT225_v4"    );

        }

        // event wieghts 
        //float vtxw  = evt_isRealData() ? 1.0 : vtxweight_n(numberOfGoodVertices(), evt_isRealData(), false);
        float vtxw  = 1.0;
        float xsec  = evt_isRealData() ? 1.0 : evt_scale1fb();
        float scale = evt_isRealData() ? 1.0 : m_lumi * xsec * vtxw; 

        // fill event level info 
        m_evt.event_info.FillCommon(m_sample, filename);

        // fill the dilepton analysis independent variables 
        m_evt.FillCommon(hyp_idx);

        // ttbar breakdown: ttdil = 0, ttotr = 1, ttslb = 2, ttslo = 3, not set = 4
        m_evt.ttbar_bkdn = GetTTbarBreakDown(m_sample, m_evt.lep1.is_fromw, m_evt.lep2.is_fromw); 

        // fill analysis specific branches 
        m_evt.vtxw = vtxw;

        // sparms parameters
        if (m_sparms) 
        {
            int n_sparms = sparm_values().size();
            if (n_sparms > 0) m_evt.sparm0 = sparm_values().at(0);
            if (n_sparms > 1) m_evt.sparm1 = sparm_values().at(1);
            if (n_sparms > 2) m_evt.sparm2 = sparm_values().at(2);
            if (n_sparms > 3) m_evt.sparm3 = sparm_values().at(3);
        }

        // event level info
        if (not jet_corrector)
        {
            m_evt.event_info.pfmet          = evt_pfmet_type1cor();  // do we ever use the uncorrected pfmet?
            m_evt.event_info.pfmet_phi      = evt_pfmetPhi_type1cor();
        }
        else
        {
            std::pair<float, float> pcor_met = met_corrector->getCorrectedMET();
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

        if (not jet_corrector)
        {
            m_evt.ht           = samesign::sumJetPt(hyp_idx, jet_type,                     /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.ht20         = samesign::sumJetPt(hyp_idx, jet_type,                     /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.ht30         = samesign::sumJetPt(hyp_idx, jet_type,                     /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.njets        = samesign::nJets(hyp_idx, jet_type,                        /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.njets20      = samesign::nJets(hyp_idx, jet_type,                        /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.njets30      = samesign::nJets(hyp_idx, jet_type,                        /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nbtags       = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nbtags20     = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nbtags30     = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
        }
        else
        {
            m_evt.ht           = samesign::sumJetPt(hyp_idx, jet_corrector, jet_type,                     /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.ht20         = samesign::sumJetPt(hyp_idx, jet_corrector, jet_type,                     /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.ht30         = samesign::sumJetPt(hyp_idx, jet_corrector, jet_type,                     /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.njets        = samesign::nJets(hyp_idx, jet_corrector, jet_type,                        /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.njets20      = samesign::nJets(hyp_idx, jet_corrector, jet_type,                        /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.njets30      = samesign::nJets(hyp_idx, jet_corrector, jet_type,                        /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nbtags       = samesign::nBtaggedJets(hyp_idx, jet_corrector, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nbtags20     = samesign::nBtaggedJets(hyp_idx, jet_corrector, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nbtags30     = samesign::nBtaggedJets(hyp_idx, jet_corrector, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
        }

        m_evt.no_extrag    = (not samesign::makesExtraGammaStar(hyp_idx));
        m_evt.hyp_good_vtx = hypsFromFirstGoodVertex(hyp_idx);
        m_evt.clean        = cleaning_standardNovember2011(); 
        m_evt.presel       = (m_evt.no_extraz && m_evt.no_extrag && m_evt.clean && m_evt.hyp_good_vtx);

        // set lepton info (lep1 is higher pT lepton, lep2 is lower pT lepton)
        float lt_pt = hyp_lt_p4().at(hyp_idx).pt();
        float ll_pt = hyp_ll_p4().at(hyp_idx).pt();
        bool lt_fo  = IsDenominator(best_hyp, /*is_lt=*/true);  
        bool lt_num = IsNumerator  (best_hyp, /*is_lt=*/true);  
        bool ll_fo  = IsDenominator(best_hyp, /*is_lt=*/false);  
        bool ll_num = IsNumerator  (best_hyp, /*is_lt=*/false);  

        int lep1_id;
        int lep1_idx;
        int lep2_id;
        int lep2_idx;
        bool lep1_fo = false;
        bool lep1_num = false;
        bool lep2_fo = false;
        bool lep2_num = false;
        if (lt_pt > ll_pt)
        {
            lep1_id  = cms2.hyp_lt_id().at(hyp_idx);
            lep1_idx = cms2.hyp_lt_index().at(hyp_idx); 
            lep1_fo  = lt_fo;
            lep1_num = lt_num;
            lep2_id  = cms2.hyp_ll_id().at(hyp_idx);    
            lep2_idx = cms2.hyp_ll_index().at(hyp_idx); 
            lep2_fo  = ll_fo;
            lep2_num = ll_num;
        }
        else
        {
            lep1_id  = cms2.hyp_ll_id().at(hyp_idx);
            lep1_idx = cms2.hyp_ll_index().at(hyp_idx); 
            lep1_fo  = ll_fo;
            lep1_num = ll_num;
            lep2_id  = cms2.hyp_lt_id().at(hyp_idx);    
            lep2_idx = cms2.hyp_lt_index().at(hyp_idx); 
            lep2_fo  = lt_fo;
            lep2_num = lt_num;
        }

        m_evt.lep1.cordetiso   = m_evt.lep1.detiso   - (log(m_evt.lep1.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep1.p4.pt()); // check that I have the correct formula 
        m_evt.lep1.cordetiso04 = m_evt.lep1.detiso04 - (log(m_evt.lep1.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep1.p4.pt()); // check that I have the correct formula 
        m_evt.lep1.corpfiso    = samesign::leptonIsolation(lep1_id, lep1_idx);
        m_evt.lep1.corpfiso04  = -999999.0;   // this is not implemented yet 
        m_evt.lep1.effarea     = EffectiveArea03(lep1_id, lep1_idx);  // is there a diffenece for different cone sizes? 
        m_evt.lep1.effarea04   = -999999.0;   // is there a diffenece for different cone sizes?
        m_evt.lep1.dbeta       = (abs(lep1_id)==13) ? mus_isoR03_pf_PUPt().at(lep1_idx) : -99999.0;
        m_evt.lep1.dbeta04     = (abs(lep1_id)==13) ? mus_isoR04_pf_PUPt().at(lep1_idx) : -99999.0;
        m_evt.lep1.is_fo       = lep1_fo;
        m_evt.lep1.is_num      = lep1_num;
        //m_evt.lep1.is_conv     = false; 
        m_evt.lep1.mt          = rt::Mt(m_evt.lep1.p4, met, met_phi);
        m_evt.lep1.mt          = rt::Mt(m_evt.lep1.p4, evt_pfmet(), evt_pfmetPhi());
        m_evt.lep1.passes_id   = samesign::isGoodLepton(lep1_id, lep1_idx);
        m_evt.lep1.passes_iso  = samesign::isIsolatedLepton(lep1_id, lep1_idx);
        m_evt.lep1_wfr         = GetFakeRateValue(lep1_id, lep1_idx);
        m_evt.lep1_wflip       = GetFlipRateValue(lep1_id, lep1_idx);

        m_evt.lep2.cordetiso   = m_evt.lep2.detiso   - (log(m_evt.lep2.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep2.p4.pt()); // check that I have the correct formula 
        m_evt.lep2.cordetiso04 = m_evt.lep2.detiso04 - (log(m_evt.lep2.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep2.p4.pt()); // check that I have the correct formula 
        m_evt.lep2.corpfiso    = samesign::leptonIsolation(lep2_id, lep2_idx);
        m_evt.lep2.corpfiso04  = -999999.0;   // this is not implemented yet 
        m_evt.lep2.effarea     = EffectiveArea03(lep2_id, lep2_idx);  // is there a diffenece for different cone sizes? 
        m_evt.lep2.effarea04   = -999999.0;   // is there a diffenece for different cone sizes?
        m_evt.lep2.dbeta       = (abs(lep2_id)==13) ? mus_isoR03_pf_PUPt().at(lep2_idx) : -99999.0;
        m_evt.lep2.dbeta04     = (abs(lep2_id)==13) ? mus_isoR04_pf_PUPt().at(lep2_idx) : -99999.0;
        m_evt.lep2.is_fo       = lep2_fo; 
        m_evt.lep2.is_num      = lep2_num;
        //m_evt.lep2.is_conv     = false; 
        m_evt.lep2.mt          = rt::Mt(m_evt.lep2.p4, met, met_phi);
        m_evt.lep2.passes_id   = samesign::isGoodLepton(lep2_id, lep2_idx);
        m_evt.lep2.passes_iso  = samesign::isIsolatedLepton(lep2_id, lep2_idx);
        m_evt.lep2_wfr         = GetFakeRateValue(lep2_id, lep2_idx);
        m_evt.lep2_wflip       = GetFlipRateValue(lep2_id, lep2_idx);


        // njets, nbtags, HT and MET for JES systematics
        if (!evt_isRealData()) 
        {
            if (not jet_corrector || not met_corrector)
            {
                m_evt.ht_up       = samesign::sumJetPt(hyp_idx, jet_type,                     /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                m_evt.ht20_up     = samesign::sumJetPt(hyp_idx, jet_type,                     /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                m_evt.ht30_up     = samesign::sumJetPt(hyp_idx, jet_type,                     /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                m_evt.njets_up    = samesign::nJets(hyp_idx, jet_type,                        /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                m_evt.njets20_up  = samesign::nJets(hyp_idx, jet_type,                        /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                m_evt.njets30_up  = samesign::nJets(hyp_idx, jet_type,                        /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                m_evt.nbtags_up   = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                m_evt.nbtags20_up = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                m_evt.nbtags30_up = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);

                m_evt.ht_dn       = samesign::sumJetPt(hyp_idx, jet_type,                     /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                m_evt.ht20_dn     = samesign::sumJetPt(hyp_idx, jet_type,                     /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                m_evt.ht30_dn     = samesign::sumJetPt(hyp_idx, jet_type,                     /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                m_evt.njets_dn    = samesign::nJets(hyp_idx, jet_type,                        /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                m_evt.njets20_dn  = samesign::nJets(hyp_idx, jet_type,                        /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                m_evt.njets30_dn  = samesign::nJets(hyp_idx, jet_type,                        /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                m_evt.nbtags_dn   = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                m_evt.nbtags20_dn = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                m_evt.nbtags30_dn = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);

                // MET
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
                    float eta  = ujets.at(u).pt();
                    float corr_up = getJetMetSyst(/*jetMetScale=*/ 1, pt, eta);
                    float corr_dn = getJetMetSyst(/*jetMetScale=*/-1, pt, eta);
                    metx_up = metx_up - (corr_up-1.0)*px;
                    mety_up = mety_up - (corr_up-1.0)*py;
                    metx_dn = metx_dn - (corr_dn-1.0)*px;
                    mety_dn = mety_dn - (corr_dn-1.0)*py;
                }
                cmet_up.SetXY(metx_up, mety_up);
                cmet_dn.SetXY(metx_dn, mety_dn);
                m_evt.pfmet_up = cmet_up.r(); 
                //m_evt.pfmet_phi_up  = cmet_up.phi();
                m_evt.pfmet_dn = cmet_dn.r(); 
                //m_evt.pfmet_phidn = cmet_dn.phi();
            }
            else
            {
                m_evt.ht_up       = samesign::sumJetPt(hyp_idx, jet_corrector, jet_type,                     /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                m_evt.ht20_up     = samesign::sumJetPt(hyp_idx, jet_corrector, jet_type,                     /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                m_evt.ht30_up     = samesign::sumJetPt(hyp_idx, jet_corrector, jet_type,                     /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                m_evt.njets_up    = samesign::nJets(hyp_idx, jet_corrector, jet_type,                        /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                m_evt.njets20_up  = samesign::nJets(hyp_idx, jet_corrector, jet_type,                        /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                m_evt.njets30_up  = samesign::nJets(hyp_idx, jet_corrector, jet_type,                        /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                m_evt.nbtags_up   = samesign::nBtaggedJets(hyp_idx, jet_corrector, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                m_evt.nbtags20_up = samesign::nBtaggedJets(hyp_idx, jet_corrector, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                m_evt.nbtags30_up = samesign::nBtaggedJets(hyp_idx, jet_corrector, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);

                m_evt.ht_dn       = samesign::sumJetPt(hyp_idx, jet_corrector, jet_type,                     /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                m_evt.ht20_dn     = samesign::sumJetPt(hyp_idx, jet_corrector, jet_type,                     /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                m_evt.ht30_dn     = samesign::sumJetPt(hyp_idx, jet_corrector, jet_type,                     /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                m_evt.njets_dn    = samesign::nJets(hyp_idx, jet_corrector, jet_type,                        /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                m_evt.njets20_dn  = samesign::nJets(hyp_idx, jet_corrector, jet_type,                        /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                m_evt.njets30_dn  = samesign::nJets(hyp_idx, jet_corrector, jet_type,                        /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                m_evt.nbtags_dn   = samesign::nBtaggedJets(hyp_idx, jet_corrector, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                m_evt.nbtags20_dn = samesign::nBtaggedJets(hyp_idx, jet_corrector, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                m_evt.nbtags30_dn = samesign::nBtaggedJets(hyp_idx, jet_corrector, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);

                // MET
                ROOT::Math::XYVector cmet_up;
                ROOT::Math::XYVector cmet_dn;
                float metx_up = met * cos(met_phi);
                float metx_dn = met * cos(met_phi);
                float mety_up = met * sin(met_phi);
                float mety_dn = met * sin(met_phi);
                // get uncorrected jets
                vector<LorentzVector> ujets = samesign::getJets(hyp_idx, jet_corrector, jet_type, /*dR=*/0.4, /*jet_pt>*/10.0, /*|eta|<*/5.0, 20.0, 20.0, 1.0, 0);
                for (size_t u = 0; u != ujets.size(); u++) 
                {
                    float px   = ujets.at(u).px();
                    float py   = ujets.at(u).py();
                    float pt   = ujets.at(u).pt();
                    float eta  = ujets.at(u).pt();
                    float corr_up = getJetMetSyst(/*jetMetScale=*/ 1, pt, eta);
                    float corr_dn = getJetMetSyst(/*jetMetScale=*/-1, pt, eta);
                    metx_up = metx_up - (corr_up-1.0)*px;
                    mety_up = mety_up - (corr_up-1.0)*py;
                    metx_dn = metx_dn - (corr_dn-1.0)*px;
                    mety_dn = mety_dn - (corr_dn-1.0)*py;
                }
                cmet_up.SetXY(metx_up, mety_up);
                cmet_dn.SetXY(metx_dn, mety_dn);
                m_evt.pfmet_up = cmet_up.r(); 
                //m_evt.pfmet_phi_up  = cmet_up.phi();
                m_evt.pfmet_dn = cmet_dn.r(); 
                //m_evt.pfmet_phidn = cmet_dn.phi();
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
                if (m_verbose) {std::cout << "fails # jets >= 2 cut" << std::endl;}
                return 0;
            }
        }

        // Gen level info
        // NOTE: we fill the gen block if and only if BOTH leptons are matched 
        if (!evt_isRealData())
        {
            // gen Lep p4
            std::pair<GenParticleStruct, GenParticleStruct> gen_hyp = efftools::getGenHyp(/*pt1=*/mu_min_pt, /*pt2=*/el_min_pt, DileptonChargeType::SS);
            if (gen_hyp.first.idx_!=999999 && gen_hyp.second.idx_!=999999)
            {
                m_evt.is_gen_mm = gen_hyp.first.id_>0 && gen_hyp.second.id_>0;
                m_evt.is_gen_pp = gen_hyp.first.id_<0 && gen_hyp.second.id_<0;

                // gen HT
                m_evt.gen_ht = efftools::getGenHT(/*pt_cut=*/40.0, /*eta_cut=*/2.4);

                // gen b quarks
                std::vector<LorentzVector> gen_bjets = efftools::getGenBjets(/*pt_cut=*/40.0, /*eta_cut=*/2.4);
                m_evt.gen_nbtags = gen_bjets.size();
                m_evt.vgenb_p4   = gen_bjets;

                // gen jets 
                std::vector<LorentzVector> gen_jets = efftools::getGenJets(/*pt_cut=*/40.0, /*eta_cut=*/2.4);
                m_evt.gen_njets   = gen_jets.size();
                m_evt.vgenjets_p4 = gen_jets;

                // gen dilep hyp
                m_evt.gen_lep1_p4    = (abs(gen_hyp.first.id_) == 15) ? cms2.genps_lepdaughter_p4().at(gen_hyp.first.idx_).at(gen_hyp.first.didx_) : cms2.genps_p4().at(gen_hyp.first.idx_);
                m_evt.gen_lep1_pdgid = (abs(gen_hyp.first.id_) == 15) ? gen_hyp.first.did_ : gen_hyp.first.id_;

                m_evt.gen_lep2_p4    = (abs(gen_hyp.second.id_) == 15) ? cms2.genps_lepdaughter_p4().at(gen_hyp.second.idx_).at(gen_hyp.second.didx_) : cms2.genps_p4().at(gen_hyp.second.idx_);
                m_evt.gen_lep2_pdgid = (abs(gen_hyp.second.id_) == 15) ? gen_hyp.second.did_ : gen_hyp.second.id_;

                m_evt.gen_dilep_p4 = m_evt.gen_lep1_p4 + m_evt.gen_lep2_p4;
                m_evt.gen_dilep_mass = m_evt.gen_dilep_p4.mass();

                if (abs(m_evt.gen_lep1_pdgid*m_evt.gen_lep2_pdgid) == 121)
                    m_evt.gen_dilep_type = at::DileptonHypType::EE;
                else if (abs(m_evt.gen_lep1_pdgid*m_evt.gen_lep2_pdgid) == 169)
                    m_evt.gen_dilep_type = at::DileptonHypType::MUMU;
                else if (abs(m_evt.gen_lep1_pdgid*m_evt.gen_lep2_pdgid) == 143)
                    m_evt.gen_dilep_type = at::DileptonHypType::EMU;

                m_evt.gen_dilep_dphi = rt::DeltaPhi(m_evt.gen_lep1_p4, m_evt.gen_lep2_p4);
                m_evt.gen_dilep_deta = rt::DeltaEta(m_evt.gen_lep1_p4, m_evt.gen_lep2_p4);
                m_evt.gen_dilep_dr   = rt::DeltaR(m_evt.gen_lep1_p4, m_evt.gen_lep2_p4);
            }
        }
        
        // classification
        m_evt.is_ss = (event_type==DileptonChargeType::SS);
        m_evt.is_sf = (event_type==DileptonChargeType::SF);
        m_evt.is_df = (event_type==DileptonChargeType::DF);
        m_evt.is_os = (event_type==DileptonChargeType::OS);
        m_evt.is_pp = hyp_lt_charge().at(hyp_idx)>0 && hyp_ll_charge().at(hyp_idx)>0; 
        m_evt.is_mm = hyp_lt_charge().at(hyp_idx)<0 && hyp_ll_charge().at(hyp_idx)<0; 

        // electron isolation correction variables
        m_evt.rho     = evt_kt6pf_foregiso_rho();
        m_evt.rho_iso = -999999.0;

        // eff and scale factors
        if (!evt_isRealData())
        {
            // scale factor for trigger efficiency
            m_evt.sf_dileptrig     = dilepTriggerScaleFactor(hyp_idx);
            //m_evt.lep1.sf_trig   = triggerScaleFactor(TrigEffType::LeadDbl, lep1_id, m_evt.lep1.p4);  // this doesn't seem right
            //m_evt.lep2.sf_trig   = triggerScaleFactor(TrigEffType::LeadDbl, lep2_id, m_evt.lep2.p4);  // this doesn't seem right

            // scale factor for lepton reconstruction efficiency
            m_evt.sf_lepeff      = dileptonTagAndProbeScaleFactor(hyp_idx);
            m_evt.lep1.sf_lepeff = tagAndProbeScaleFactor(lep1_id, m_evt.lep1.p4.pt(), m_evt.lep1.p4.eta()); 
            m_evt.lep2.sf_lepeff = tagAndProbeScaleFactor(lep2_id, m_evt.lep2.p4.pt(), m_evt.lep2.p4.eta());

            // scale factor for # btags 
            vector<LorentzVector> bjets;
            if (not jet_corrector)
                bjets = samesign::getBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
            else
                bjets = samesign::getBtaggedJets(hyp_idx, jet_corrector, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);

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
        if (not jet_corrector)
        {
            m_evt.vbjets_p4 = samesign::getBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM,     /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale); 
            m_evt.vjets_p4  = samesign::getJets(hyp_idx, jet_type,                            /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale); 
            m_evt.vbtags    = samesign::getBtaggedJetFlags(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
        }
        else
        {
            m_evt.vbjets_p4 = samesign::getBtaggedJets(hyp_idx, jet_corrector, jet_type, JETS_BTAG_CSVM,     /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale); 
            m_evt.vjets_p4  = samesign::getJets(hyp_idx, jet_corrector, jet_type,                            /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale); 
            m_evt.vbtags    = samesign::getBtaggedJetFlags(hyp_idx, jet_corrector, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
        }

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
            if (not m_evt.vbtags.at(i))
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

        // Fill the tree
        m_tree->Fill();

        // printout
        if (m_evt.is_good_lumi && m_evt.njets >= 2)
        {
            scale = 1.0;
            if (dilepton_type==DileptonHypType::MUMU)
            {
                if(m_verbose) {cout << "type == mm" << endl;}
                if(event_type==DileptonChargeType::SS) m_count_nobtag_ss[0] += scale;
                if(event_type==DileptonChargeType::SF) m_count_nobtag_sf[0] += scale;
                if(event_type==DileptonChargeType::DF) m_count_nobtag_df[0] += scale;
                if(event_type==DileptonChargeType::OS) m_count_nobtag_os[0] += scale;
                if(event_type==DileptonChargeType::SS && m_evt.nbtags > 1) m_count_ss[0] += scale;
                if(event_type==DileptonChargeType::SF && m_evt.nbtags > 1) m_count_sf[0] += scale;
                if(event_type==DileptonChargeType::DF && m_evt.nbtags > 1) m_count_df[0] += scale;
                if(event_type==DileptonChargeType::OS && m_evt.nbtags > 1) m_count_os[0] += scale;
            }
            if (dilepton_type==DileptonHypType::EMU)
            {
                if(m_verbose) {cout << "type == em" << endl;}
                if(event_type==DileptonChargeType::SS) m_count_nobtag_ss[1] += scale;
                if(event_type==DileptonChargeType::SF) m_count_nobtag_sf[1] += scale;
                if(event_type==DileptonChargeType::DF) m_count_nobtag_df[1] += scale;
                if(event_type==DileptonChargeType::OS) m_count_nobtag_os[1] += scale;
                if(event_type==DileptonChargeType::SS && m_evt.nbtags > 1) m_count_ss[1] += scale;
                if(event_type==DileptonChargeType::SF && m_evt.nbtags > 1) m_count_sf[1] += scale;
                if(event_type==DileptonChargeType::DF && m_evt.nbtags > 1) m_count_df[1] += scale;
                if(event_type==DileptonChargeType::OS && m_evt.nbtags > 1) m_count_os[1] += scale;
            }
            if (dilepton_type==DileptonHypType::EE)
            {
                if(m_verbose) {cout << "type == ee" << endl;}
                if(event_type==DileptonChargeType::SS) m_count_nobtag_ss[2] += scale;
                if(event_type==DileptonChargeType::SF) m_count_nobtag_sf[2] += scale;
                if(event_type==DileptonChargeType::DF) m_count_nobtag_df[2] += scale;
                if(event_type==DileptonChargeType::OS) m_count_nobtag_os[2] += scale;
                if(event_type==DileptonChargeType::SS && m_evt.nbtags > 1) m_count_ss[2] += scale;
                if(event_type==DileptonChargeType::SF && m_evt.nbtags > 1) m_count_sf[2] += scale;
                if(event_type==DileptonChargeType::DF && m_evt.nbtags > 1) m_count_df[2] += scale;
                if(event_type==DileptonChargeType::OS && m_evt.nbtags > 1) m_count_os[2] += scale;
            }
            // count all 
            {
                if(event_type==DileptonChargeType::SS) m_count_nobtag_ss[3] += scale;
                if(event_type==DileptonChargeType::SF) m_count_nobtag_sf[3] += scale;
                if(event_type==DileptonChargeType::DF) m_count_nobtag_df[3] += scale;
                if(event_type==DileptonChargeType::OS) m_count_nobtag_os[3] += scale;
                if(event_type==DileptonChargeType::SS && m_evt.nbtags > 1) m_count_ss[3] += scale;
                if(event_type==DileptonChargeType::SF && m_evt.nbtags > 1) m_count_sf[3] += scale;
                if(event_type==DileptonChargeType::DF && m_evt.nbtags > 1) m_count_df[3] += scale;
                if(event_type==DileptonChargeType::OS && m_evt.nbtags > 1) m_count_os[3] += scale;
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

float SSAnalysisLooper::GetFakeRateValue(int lep_id, int lep_idx) const 
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

float SSAnalysisLooper::GetFlipRateValue(int lep_id, int lep_idx) const 
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
