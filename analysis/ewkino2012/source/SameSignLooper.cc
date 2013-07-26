#include "SameSignLooper.h"

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
#include "MT2/MT2.h"

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
#include "at/TrackIsoTools.h"
#include "rt/RootTools.h"
#include "CTable.h"
#include "GenParticleStruct.h"
#include "EfficiencyModelTools.h"
#include "ScaleFactors.h"
#include "TTbarBreakDown.h"
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
// using namespace at;
using namespace ewkino;

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

// set then numerator bool
bool EwkinoSSAnalysisLooper::IsNumerator(const int lep_id, const int lep_idx)
{
    return samesign::isNumeratorLepton(lep_id, lep_idx, false);
}

// set then denominator bool
bool EwkinoSSAnalysisLooper::IsDenominator(const int lep_id, const int lep_idx)
{
    return samesign::isDenominatorLepton(lep_id, lep_idx, false);
}

// set then fake-able object bool
bool EwkinoSSAnalysisLooper::IsFO(const int lep_id, const int lep_idx)
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

void PrintJetInfo(const std::string& label, const vector<LorentzVector>& jets_p4)
{
    cout << label << ":" << endl;
    for (size_t i = 0; i < jets_p4.size(); i++)
    {
        LorentzVector jet_p4 = jets_p4.at(i);
        cout << Form("idx %d, pt %f, eta %f, phi %f", (int)i, jet_p4.pt(), jet_p4.eta(), jet_p4.phi()) << endl;
    }
}

void PrintForSync(int ihyp, float mu_min_pt, float el_min_pt, enum JetType jet_type, int jet_met_scale, FactorizedJetCorrector *jet_corrector = NULL, MetCorrector *met_corrector = NULL)
{
    // convenience
    const LorentzVector& lt_p4 = hyp_lt_p4().at(ihyp);
    const LorentzVector& ll_p4 = hyp_ll_p4().at(ihyp);
    const int lt_id            = hyp_lt_id().at(ihyp);
    const int ll_id            = hyp_ll_id().at(ihyp);
    const int lt_idx           = hyp_lt_index().at(ihyp);
    const int ll_idx           = hyp_ll_index().at(ihyp);
    const bool lt_passes_id    = samesign::isGoodLepton(lt_id, lt_idx, false);
    const bool ll_passes_id    = samesign::isGoodLepton(ll_id, ll_idx, false);
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
        num_jets  = samesign::nJets(ihyp, jet_type                       , /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
        jets_p4   = samesign::getJets(ihyp, jet_type                     , /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
        num_btags = samesign::nBtaggedJets(ihyp, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
        ht        = samesign::sumJetPt(ihyp, jet_type                    , /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, jet_met_scale);
        met       = evt_pfmet_type1cor();
    }
    else
    {
        num_jets  = samesign::nJets(ihyp, jet_corrector, jet_type                       , /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
        jets_p4   = samesign::getJets(ihyp, jet_corrector, jet_type                     , /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
        num_btags = samesign::nBtaggedJets(ihyp, jet_corrector, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
        ht        = samesign::sumJetPt(ihyp, jet_corrector, jet_type                    , /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, jet_met_scale);
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

    if (samesign::isNumeratorHypothesis(ihyp), false)
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
    PrintJetInfo(Form("passing jets for hyp %d", ihyp), jets_p4);
}

// construct:
EwkinoSSAnalysisLooper::EwkinoSSAnalysisLooper
(
    const std::string& root_file_name,
    const at::Sample::value_type& sample,
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
    const bool sync_print,
    const bool verbose,
    const std::string apply_jec_otf,
    const std::string apply_jec_unc,
    const double jet_pt_cut
)
    : AnalysisWithTreeAndHist(root_file_name, "tree", "baby tree for EWKINO 2012 SS analysis")
    , m_sample(sample)
    , m_analysis_type(analysis_type)
    , m_lumi(luminosity)
    , m_njets(njets)
    , m_sparms(sparms)
    , m_jetMetScale(jetMetScale)
    , m_is_fast_sim(is_fast_sim)
    , m_filter_bad_runs(false)
    , m_sync_print(sync_print)
    , m_verbose(verbose || sync_print)
    , m_jet_pt_cut(jet_pt_cut) 
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

        std::string path = rt::getenv("CMS2_CORE");
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

        printf("[EwkinoSSAnalysisLooper] making jet and MET correctors with: \n");
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
            throw std::runtime_error("ERROR: EwkinoSSAnalysisLooper: unable to create jet_corrector");
        }
        m_met_corrector.reset(new MetCorrector(m_list_of_jec_filenames));
        if (not m_met_corrector)
        {
            throw std::runtime_error("ERROR: EwkinoSSAnalysisLooper: unable to create met_corrector");
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
        printf("[EwkinoSSAnalysisLooper] making jet and MET correctors uncertainties with: \n");
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
            throw std::runtime_error("ERROR: EwkinoSSAnalysisLooper: unable to create jet_corr_unc");
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

    cout << "sample: " << m_sample << endl;
    cout << "analysis: " << m_analysis_type << endl;
    cout.flush();

    // set the fake rate histograms
    std::auto_ptr<TFile> fake_rate_file(rt::OpenRootFile(fake_rate_file_name));
    cout << "using FR file : " << fake_rate_file->GetName() << endl;
    string mufr_name = "";
    string elfr_name = "";

    if (m_sample == at::Sample::data)
    {
        switch (m_analysis_type)
        {
        case AnalysisType::ss:
            mufr_name = "h_mufr40c_ewkcor";
            elfr_name = "h_elfr40c_ewkcor";
            break;
        default:
            mufr_name = "h_mufr40c";
            elfr_name = "h_elfr40c";
            break;
        }
    }
    else
    {
        switch (m_analysis_type)
        {
        case AnalysisType::ss:
            mufr_name = "h_mufr40c";
            elfr_name = "h_elfr40c";
            break;
        default:
            mufr_name = "h_mufr40c";
            elfr_name = "h_elfr40c";
            break;
        }
    }

    h_mufr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get(mufr_name.c_str())->Clone()));
    h_elfr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get(elfr_name.c_str())->Clone()));
    if (not h_mufr) {throw std::runtime_error(Form("ERROR: EwkinoSSAnalysisLooper: %s doesn't exist", mufr_name.c_str()));}
    if (not h_elfr) {throw std::runtime_error(Form("ERROR: EwkinoSSAnalysisLooper: %s doesn't exist", elfr_name.c_str()));}
    h_mufr->SetDirectory(0);
    h_elfr->SetDirectory(0);

    cout << "[EwkinoSSAnalysisLooper] using mu FR hist : " << h_mufr->GetName() << endl;
    cout << "[EwkinoSSAnalysisLooper] using el FR hist : " << h_elfr->GetName() << endl;

    // set the flip rate histograms
    std::auto_ptr<TFile> flip_rate_file(rt::OpenRootFile(flip_rate_file_name));
    cout << "[EwkinoSSAnalysisLooper] using FL file : " << flip_rate_file->GetName() << endl;
    h_flip.reset(dynamic_cast<TH2F*>(flip_rate_file->Get("flipRate")->Clone()));
    if (not h_flip) {throw std::runtime_error("ERROR: EwkinoSSAnalysisLooper: flipRate doesn't exist");}
    h_flip->SetDirectory(0);

    cout << "[EwkinoSSAnalysisLooper] using FL hist : " << h_flip->GetName() << endl;

    // get jet pt cut
    if (m_jet_pt_cut < 0.0f)
    {
        m_jet_pt_cut = 30.0f;
    }

    cout << "[EwkinoSSAnalysisLooper] using jet pT cut : " << m_jet_pt_cut << endl;

    // begin job
    BeginJob();
}

// destroy:
EwkinoSSAnalysisLooper::~EwkinoSSAnalysisLooper()
{
//     delete m_jet_corrector;
//     delete m_met_corrector;
}

// function operator: operate on each event
int EwkinoSSAnalysisLooper::operator() (long event, const std::string& filename)
{
    // call base class operator
    return Analyze(event, filename);
}

// members:
void EwkinoSSAnalysisLooper::BeginJob()
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

void EwkinoSSAnalysisLooper::BookHists()
{
    rt::TH1Container& hc = m_hist_container;

    // generated event count hist
    if (m_sparms)
    {
        ewkino::SignalBinInfo bin_info = ewkino::GetSignalBinInfo(m_sample);
        const std::string title = Form("# of Generated Events - %s", ewkino::GetSignalBinHistLabel(m_sample).c_str());
        hc.Add(new TH2F("h_gen_count", title.c_str(), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    }
}


void EwkinoSSAnalysisLooper::EndJob()
{
    cout << "Number of dilepton hypotheses passing pT > 20, 20; |eta| < 2.4, 2.4; SS:\t" << m_hyp_count << endl;

    CTable yield_table;
    yield_table.setTitle("yields for EWKINO 2012 SS Analysis (baseline)");
    yield_table.useTitle();
    yield_table.setTable() (                      "mm",          "em",          "ee",         "all")
                           ("count ss" , m_count_ss[0], m_count_ss[1], m_count_ss[2], m_count_ss[3]) 
                           ("count sf" , m_count_sf[0], m_count_sf[1], m_count_sf[2], m_count_sf[3]) 
                           ("count df" , m_count_df[0], m_count_df[1], m_count_df[2], m_count_df[3])
                           ("count os" , m_count_os[0], m_count_os[1], m_count_os[2], m_count_os[3]); 
    yield_table.print();

    CTable yield_table2;
    yield_table2.setTitle("yields for EWKINO 2012 SS Analysis (baseline + mass req)");
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

int EwkinoSSAnalysisLooper::SetJetCorrector(std::vector<std::string> &list_of_filenames)
{
    printf("[EwkinoSSAnalysisLooper] making jet corrector with: \n");
    for (unsigned int idx = 0; idx < list_of_filenames.size(); idx++)
    {
        printf("\t%s\n", list_of_filenames.at(idx).c_str());
    }

    m_jet_corrector.reset(makeJetCorrector(list_of_filenames));
    m_met_corrector.reset(new MetCorrector(list_of_filenames));
    if (!m_jet_corrector && !m_met_corrector) return 1;
    return 0;
}

int EwkinoSSAnalysisLooper::Analyze(const long event, const std::string& filename)
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
            case AnalysisType::ss    : trigger_option = 0; break;
            case AnalysisType::static_size: break; // no default is intentional so that compiler issues a warning if you don't handle all the cases
        }

        // lepton pT cut values
        float mu_min_pt = 0.0;
        float el_min_pt = 0.0;
        switch(m_analysis_type)
        {
            case AnalysisType::ss:
                mu_min_pt = 10.0;
                el_min_pt = 10.0;
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
            // if sample is tchiwh, figure out which W from Higgs decayed leptonically, which hadronically
            if (m_sample == at::Sample::tchiwh)
            {
                bool found_higgs = false;
                std::vector<int> w_indices;
                std::vector<std::pair<int, int> > w_daughter_indices;
                for (unsigned int idx = 0; idx < genps_p4().size(); idx++)
                {
                    if (genps_status().at(idx) != 3) continue;
                    if (abs(genps_id().at(idx)) == 24) w_indices.push_back(idx);
                    if (abs(genps_id().at(idx)) != 25 && !found_higgs) continue;
                    if (abs(genps_id().at(idx)) == 25)
                    {
                        found_higgs = true;
                        continue;
                    }
                    if ((abs(genps_id().at(idx)) > 0 && abs(genps_id().at(idx)) < 6) || (abs(genps_id().at(idx)) > 10 && abs(genps_id().at(idx)) < 17))
                    {
                        w_daughter_indices.push_back(std::make_pair(idx, idx+1));
                        ++idx;
                    }                    
                }

                
                if (w_indices.size() > 1 && fabs(genps_p4().at(w_indices.at(1)).mass() - 80.) > 10.)
                {
                    if (abs(genps_id().at(w_daughter_indices.at(1).first)) > 10 && abs(genps_id().at(w_daughter_indices.at(1).first)) < 17)
                    {
                        m_evt.leptonic_offshell_w = true;
                    }
                    else if (abs(genps_id().at(w_daughter_indices.at(1).first)) > 0 && abs(genps_id().at(w_daughter_indices.at(1).first)) < 6)
                    {
                        m_evt.hadronic_offshell_w = true;
                    }
                }

                if (w_indices.size() > 2 && fabs(genps_p4().at(w_indices.at(2)).mass() - 80.) > 10.)
                {
                    if (abs(genps_id().at(w_daughter_indices.at(2).first)) > 10 && abs(genps_id().at(w_daughter_indices.at(2).first)) < 17)
                    {
                        m_evt.leptonic_offshell_w = true;
                    }
                    else if (abs(genps_id().at(w_daughter_indices.at(2).first)) > 0 && abs(genps_id().at(w_daughter_indices.at(2).first)) < 6)
                    {
                        m_evt.hadronic_offshell_w = true;
                    }
                }
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
            std::pair<GenParticleStruct, GenParticleStruct> best_gen_hyp = efftools::getGenHyp(min_pt, min_pt, at::DileptonChargeType::static_size);
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

                //
                // store info for third gen lepton, if it exists
                //
                for (unsigned int gidx = 0; gidx < cms2.genps_p4().size(); gidx++)
                {
                    if (gidx == idx1 || gidx == idx2) continue;
                    if (cms2.genps_status().at(gidx) != 3) continue;
                    if (cms2.genps_p4().at(gidx).pt() < m_evt.gen_lep3_p4.pt()) continue;
                    unsigned int gid = abs(cms2.genps_id().at(gidx));
                    if (gid != 11 && gid != 13 && gid != 15) continue;
                    if (gid == 15)
                    {
                        float pt = -999.;
                        int good_idx = -1;
                        for (unsigned int didx = 0; didx < cms2.genps_lepdaughter_p4().at(gidx).size(); didx++)
                        {
                            unsigned int did = abs(cms2.genps_lepdaughter_id().at(gidx).at(didx));
                            if (did != 11 && did != 13) continue;
                            if (cms2.genps_lepdaughter_p4().at(gidx).at(didx).pt() > pt)
                            {
                                pt = cms2.genps_lepdaughter_p4().at(gidx).at(didx).pt();
                                good_idx = didx;
                            }
                        }
                        if (good_idx >= 0)
                        {
                            m_evt.gen_lep3_pdgid = cms2.genps_lepdaughter_id().at(gidx).at(good_idx);
                            m_evt.gen_lep3_p4    = cms2.genps_lepdaughter_p4().at(gidx).at(good_idx);
                        }
                    }

                    m_evt.gen_lep3_pdgid = cms2.genps_id().at(gidx);
                    m_evt.gen_lep3_p4    = cms2.genps_p4().at(gidx);
                }
            }

            // gen jets
            m_evt.vgenjets_p4 = efftools::getGenJets(m_jet_pt_cut, 2.4);
            m_evt.gen_ht      = efftools::getGenHT(m_jet_pt_cut, 2.4);
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
        HypInfo best_hyp((hyp_type().empty() ? -1 : 0), at::DileptonChargeType::static_size, at::DileptonHypType::static_size);
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
                PrintForSync(ihyp, mu_min_pt, el_min_pt, jet_type, m_jetMetScale, m_jet_corrector.get(), m_met_corrector.get());
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
            if (samesign::makesExtraGammaStar(ihyp))
            {
                if (m_verbose) {std::cout << "fails extra Gamma* veto requirement" << std::endl;}
                continue;
            }

            // skip if both are not denominators
            if (!samesign::isDenominatorHypothesis(ihyp, false))
            {
                if (m_verbose) {std::cout << "fails both leptons are at least denominator requirement" << std::endl;}
                continue;
            }

            // get the hyp type
            at::DileptonHypType::value_type type = at::hyp_typeToHypType(hyp_type().at(ihyp));

            // OS (Here a kludge by Claudio to quickly change the meaning of SS and OS .... useful for ttbar as sstop)
            int dummy = 1;
            //if (m_switchSigns) dummy=-1;
            int hyp_q = dummy * hyp_lt_charge().at(ihyp) * hyp_ll_charge().at(ihyp);
            if (hyp_q < 0)
            {
                if (m_verbose) {std::cout << "selected OS hyp" << std::endl;}
                if (!samesign::isNumeratorHypothesis(ihyp, false))
                {
                    if (m_verbose) {std::cout << "OS hyp doesn't pass ID/ISO requirement" << std::endl;}
                    continue; 
                }
                best_hyp = std::min(best_hyp, HypInfo(ihyp, at::DileptonChargeType::OS, type));
            }
            else if (hyp_q > 0)
            {
                // same sign event (SS)
                if (samesign::isNumeratorHypothesis(ihyp, false))
                {
                    m_hyp_count++;
                    if (m_verbose) {std::cout << "selected SS hyp" << std::endl;}
                    best_hyp = std::min(best_hyp, HypInfo(ihyp, at::DileptonChargeType::SS, type));
                }
                // single fake event (SF)
                else if (samesign::isNumeratorLepton(lt_id, lt_idx, false) || samesign::isNumeratorLepton(ll_id, ll_idx, false))
                {
                    if (m_verbose) {std::cout << "selected SF hyp" << std::endl;}
                    best_hyp = std::min(best_hyp, HypInfo(ihyp, at::DileptonChargeType::SF, type));
                }
                // double fake event (DF)
                else
                {
                    if (m_verbose) {std::cout << "selected DF hyp" << std::endl;}
                    best_hyp = std::min(best_hyp, HypInfo(ihyp, at::DileptonChargeType::DF, type));
                }
            }

        } // end looper over hypothesis
        
        if (m_verbose) {std::cout << "end of hypothesis loop" << std::endl;}

        // Set Tree Variables
        // --------------------------------------------------------------------------------------------------------- //

        // best hyp index
        int hyp_idx = best_hyp.idx;
        at::DileptonChargeType::value_type charge_type = best_hyp.charge_type;

        // all: 0, mm: 1, em: 2, ee: 3
        const at::DileptonHypType::value_type dilepton_type = ((hyp_idx < 0 or hyp_p4().empty()) ? at::DileptonHypType::static_size : at::hyp_typeToHypType(hyp_type().at(hyp_idx)));

        // write events to the tree for book keeping
        if (charge_type == at::DileptonChargeType::static_size)
        {
            if (m_verbose) {std::cout << "fails good event type requirement" << std::endl;}

            // fill event level info 
            m_evt.dilep_type = at::DileptonHypType::static_size;
            m_evt.charge_type = -999999;
            m_evt.event_info.FillCommon(m_sample, filename);

            // fill the dilepton analysis independent variables 
            if (not hyp_p4().empty())
            {
                m_evt.FillCommon(hyp_idx);

                // ttbar breakdown: ttdil = 0, ttotr = 1, ttslb = 2, ttslo = 3, not set = 4
                m_evt.ttbar_bkdn = GetTTbarBreakDown(m_sample, m_evt.lep1.is_fromw, m_evt.lep2.is_fromw); 
            }

            // set the selection bit mask
            m_evt.SetBitMask();

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
            case AnalysisType::ss:
                m_evt.trig_mm = passUnprescaledHLTTriggerPattern("HLT_Mu17_Mu8_v");
                m_evt.trig_em = passUnprescaledHLTTriggerPattern("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v") || 
                                passUnprescaledHLTTriggerPattern("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
                m_evt.trig_ee = passUnprescaledHLTTriggerPattern("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
                break;
            default: {/*do nothing*/}
        }

        // individual triggers: mm
        m_evt.trig_mm_mu17_mu8                     = passUnprescaledHLTTriggerPattern("HLT_Mu17_Mu8_v"                            );

        // individual triggers: ee
        m_evt.trig_ee_el17_el8_id_iso        = passUnprescaledHLTTriggerPattern("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");

        // individual triggers: em
        m_evt.trig_em_mu17_el8_id_iso                  = passUnprescaledHLTTriggerPattern("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v"       );
        m_evt.trig_em_mu8_el17_id_iso                  = passUnprescaledHLTTriggerPattern("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v"       );

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
        m_evt.mt           = min(rt::Mt(m_evt.lep1.p4, met, met_phi), rt::Mt(m_evt.lep2.p4, met, met_phi));  // calculated against the higher pT lepton
        //
        // to calculate MT2, need mass of invisible particle
        //
        m_evt.mt2          = MT2(met, met_phi, m_evt.lep1.p4, m_evt.lep2.p4);
        m_evt.no_extraz    = (not samesign::makesExtraZ(hyp_idx));

        if (not m_jet_corrector)
        {
            m_evt.ht           = samesign::sumJetPt    (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.njets        = samesign::nJets       (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nlbtags      = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVL, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nmbtags      = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.ntbtags      = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVT, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
        }
        else
        {
            FactorizedJetCorrector* const jc = m_jet_corrector.get();
            m_evt.ht           = samesign::sumJetPt    (hyp_idx, jc, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.njets        = samesign::nJets       (hyp_idx, jc, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nlbtags      = samesign::nBtaggedJets(hyp_idx, jc, jet_type, JETS_BTAG_CSVL,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nmbtags      = samesign::nBtaggedJets(hyp_idx, jc, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.ntbtags      = samesign::nBtaggedJets(hyp_idx, jc, jet_type, JETS_BTAG_CSVT,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
        }

        m_evt.no_extrag    = (not samesign::makesExtraGammaStar(hyp_idx));
        m_evt.hyp_good_vtx = hypsFromFirstGoodVertex(hyp_idx);
        m_evt.clean        = cleaning_standardNovember2011(); 
        m_evt.presel       = (m_evt.no_extraz && m_evt.no_extrag && m_evt.clean && m_evt.hyp_good_vtx);

        // set lepton info (lep1 is higher pT lepton, lep2 is lower pT lepton)
        int lt_id   = cms2.hyp_lt_id().at(hyp_idx);
        int lt_idx  = cms2.hyp_lt_index().at(hyp_idx); 
        float lt_pt = hyp_lt_p4().at(hyp_idx).pt();
        int ll_id   = cms2.hyp_ll_id().at(hyp_idx);
        int ll_idx  = cms2.hyp_ll_index().at(hyp_idx); 
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
        m_evt.lep1.passes_id   = samesign::isGoodLepton(lep1_id, lep1_idx, false);
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
        m_evt.lep2.passes_id   = samesign::isGoodLepton(lep2_id, lep2_idx, false);
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
                    m_evt.njets_up    = samesign::nJets       (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                    m_evt.nlbtags_up  = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVL, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                    m_evt.nmbtags_up  = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                    m_evt.ntbtags_up  = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVT, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);

                    m_evt.ht_dn       = samesign::sumJetPt    (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.njets_dn    = samesign::nJets       (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.nlbtags_dn  = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVL, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.nmbtags_dn  = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.ntbtags_dn  = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVT, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                }
                else
                {
                    JetCorrectionUncertainty* jcu = m_jet_corr_unc.get();
                    enum JetScaleType scale_up = JETS_SCALE_UP;
                    enum JetScaleType scale_dn = JETS_SCALE_DOWN;

                    m_evt.ht_up       = samesign::sumJetPt    (hyp_idx, jcu, scale_up, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.njets_up    = samesign::nJets       (hyp_idx, jcu, scale_up, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.nlbtags_up  = samesign::nBtaggedJets(hyp_idx, jcu, scale_up, jet_type, JETS_BTAG_CSVL, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.nmbtags_up  = samesign::nBtaggedJets(hyp_idx, jcu, scale_up, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.ntbtags_up  = samesign::nBtaggedJets(hyp_idx, jcu, scale_up, jet_type, JETS_BTAG_CSVT, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);

                    m_evt.ht_dn       = samesign::sumJetPt    (hyp_idx, jcu, scale_dn, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.njets_dn    = samesign::nJets       (hyp_idx, jcu, scale_dn, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.nlbtags_dn  = samesign::nBtaggedJets(hyp_idx, jcu, scale_dn, jet_type, JETS_BTAG_CSVL, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.nmbtags_dn  = samesign::nBtaggedJets(hyp_idx, jcu, scale_dn, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.ntbtags_dn  = samesign::nBtaggedJets(hyp_idx, jcu, scale_dn, jet_type, JETS_BTAG_CSVT, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
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
                        float jet_cor = m_jet_corr_unc->getUncertainty(true);	 
                        corr_up = (1. + jet_cor);
                        corr_dn = (1. - jet_cor);
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
                    m_evt.njets_up    = samesign::nJets       (hyp_idx, m_jet_corrector.get(), jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                    m_evt.nlbtags_up  = samesign::nBtaggedJets(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVL, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                    m_evt.nmbtags_up  = samesign::nBtaggedJets(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);
                    m_evt.ntbtags_up  = samesign::nBtaggedJets(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVT, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/1);

                    m_evt.ht_dn       = samesign::sumJetPt    (hyp_idx, m_jet_corrector.get(), jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.njets_dn    = samesign::nJets       (hyp_idx, m_jet_corrector.get(), jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.nlbtags_dn  = samesign::nBtaggedJets(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVL, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.nmbtags_dn  = samesign::nBtaggedJets(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                    m_evt.ntbtags_dn  = samesign::nBtaggedJets(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVT, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, /*jetMetScale*/-1);
                }
                else
                {
                    FactorizedJetCorrector* jc    = m_jet_corrector.get();
                    JetCorrectionUncertainty* jcu = m_jet_corr_unc.get();
                    enum JetScaleType scale_up = JETS_SCALE_UP;
                    enum JetScaleType scale_dn = JETS_SCALE_DOWN;

                    m_evt.ht_up       = samesign::sumJetPt    (hyp_idx, jc, jcu, scale_up, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.njets_up    = samesign::nJets       (hyp_idx, jc, jcu, scale_up, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.nlbtags_up  = samesign::nBtaggedJets(hyp_idx, jc, jcu, scale_up, jet_type, JETS_BTAG_CSVL, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.nmbtags_up  = samesign::nBtaggedJets(hyp_idx, jc, jcu, scale_up, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.ntbtags_up  = samesign::nBtaggedJets(hyp_idx, jc, jcu, scale_up, jet_type, JETS_BTAG_CSVT, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);

                    m_evt.ht_dn       = samesign::sumJetPt    (hyp_idx, jc, jcu, scale_dn, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.njets_dn    = samesign::nJets       (hyp_idx, jc, jcu, scale_dn, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.nlbtags_dn  = samesign::nBtaggedJets(hyp_idx, jc, jcu, scale_dn, jet_type, JETS_BTAG_CSVL, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.nmbtags_dn  = samesign::nBtaggedJets(hyp_idx, jc, jcu, scale_dn, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
                    m_evt.ntbtags_dn  = samesign::nBtaggedJets(hyp_idx, jc, jcu, scale_dn, jet_type, JETS_BTAG_CSVT, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
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
                        float jet_cor = m_jet_corr_unc->getUncertainty(true);	 
                        corr_up = (1. + jet_cor);
                        corr_dn = (1. - jet_cor);
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

        // Gen level info
        // NOTE: we fill the gen block if and only if BOTH leptons are matched 
        if (!evt_isRealData())
        {
            // gen Lep p4
            std::pair<GenParticleStruct, GenParticleStruct> gen_hyp = efftools::getGenHyp(/*pt1=*/mu_min_pt, /*pt2=*/el_min_pt, at::DileptonChargeType::SS);
            if (gen_hyp.first.idx_!=999999 && gen_hyp.second.idx_!=999999)
            {
                m_evt.is_gen_mm = gen_hyp.first.id_>0 && gen_hyp.second.id_>0;
                m_evt.is_gen_pp = gen_hyp.first.id_<0 && gen_hyp.second.id_<0;

                // gen HT
                m_evt.gen_ht = efftools::getGenHT(/*pt_cut=*/m_jet_pt_cut, /*eta_cut=*/2.4);

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
        m_evt.is_ss   = (charge_type==at::DileptonChargeType::SS);
        m_evt.is_sf   = (charge_type==at::DileptonChargeType::SF);
        m_evt.is_df   = (charge_type==at::DileptonChargeType::DF);
        m_evt.is_os   = (charge_type==at::DileptonChargeType::OS);
        m_evt.em_mufo = m_evt.em && ((lep1_fo && lep1_is_mu) || (lep2_fo && lep2_is_mu));  
        m_evt.em_elfo = m_evt.em && ((lep1_fo && lep1_is_el) || (lep2_fo && lep2_is_el));
        m_evt.is_pp   = hyp_lt_charge().at(hyp_idx)>0 && hyp_ll_charge().at(hyp_idx)>0; 
        m_evt.is_mm   = hyp_lt_charge().at(hyp_idx)<0 && hyp_ll_charge().at(hyp_idx)<0; 

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
            m_evt.sf_dileptrig   = DileptonTriggerScaleFactor(dilepton_type, m_analysis_type, m_evt.lep2.p4);
            m_evt.lep1.sf_trig   = -999999; // not done 
            m_evt.lep2.sf_trig   = -999999; // not done

            // scale factor for lepton reconstruction efficiency
            const float eta1 = (abs(lep1_id) == 13 ? m_evt.lep1.p4.eta() : m_evt.lep1.sc_p4.eta());
            const float eta2 = (abs(lep2_id) == 13 ? m_evt.lep2.p4.eta() : m_evt.lep2.sc_p4.eta());
            m_evt.sf_lepeff      = DileptonTagAndProbeScaleFactor(lep1_id, m_evt.lep1.p4.pt(), eta1, lep2_id, m_evt.lep2.p4.pt(), eta2);
            m_evt.lep1.sf_lepeff = TagAndProbeScaleFactor(lep1_id, m_evt.lep1.p4.pt(), eta1); 
            m_evt.lep2.sf_lepeff = TagAndProbeScaleFactor(lep2_id, m_evt.lep2.p4.pt(), eta2);
        }

        // jet/bjet info 
        vector<bool> jet_flags;
        vector<bool> jet_flags_up;
        vector<bool> jet_flags_dn;
        vector<LorentzVector> bjets;
        vector<bool> bjet_flags;
        vector<bool> bjet_flags_up;
        vector<bool> bjet_flags_dn;
        vector<LorentzVector> all_jet_p4s;
        vector<LorentzVector> all_jet_p4s_up;
        vector<LorentzVector> all_jet_p4s_dn;
        bool sort_all_jet_pts = false;
        if (not m_jet_corrector)
        {
            all_jet_p4s           = samesign::getAllCorrectedJets(jet_type, m_jetMetScale, sort_all_jet_pts);
            all_jet_p4s_up        = samesign::getAllCorrectedJets(jet_type, 1, sort_all_jet_pts);
            all_jet_p4s_dn        = samesign::getAllCorrectedJets(jet_type, -1, sort_all_jet_pts);
            m_evt.vjets_p4        = samesign::getJets           (hyp_idx, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale); 
            jet_flags             = samesign::getJetFlags       (hyp_idx, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
            jet_flags_up          = samesign::getJetFlags       (hyp_idx, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 1 );
            jet_flags_dn          = samesign::getJetFlags       (hyp_idx, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, -1);
            m_evt.vjets_p4_up     = samesign::getJets           (hyp_idx, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 1 ); 
            m_evt.vjets_p4_dn     = samesign::getJets           (hyp_idx, jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, -1);
            bjets                 = samesign::getBtaggedJets    (hyp_idx, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
            bjet_flags            = samesign::getBtaggedJetFlags(hyp_idx, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
            bjet_flags_up         = samesign::getBtaggedJetFlags(hyp_idx, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 1 );
            bjet_flags_dn         = samesign::getBtaggedJetFlags(hyp_idx, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, -1);
            m_evt.vjets_bdisc     = samesign::getJetBtagDiscriminators(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
            m_evt.vjets_bdisc_up  = samesign::getJetBtagDiscriminators(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 1);
            m_evt.vjets_bdisc_dn  = samesign::getJetBtagDiscriminators(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, -1);
        }
        else
        {
            all_jet_p4s           = samesign::getAllCorrectedJets(jet_type, m_jet_corrector.get(), m_jetMetScale, sort_all_jet_pts);
            all_jet_p4s_up        = samesign::getAllCorrectedJets(jet_type, m_jet_corrector.get(), 1, sort_all_jet_pts);
            all_jet_p4s_dn        = samesign::getAllCorrectedJets(jet_type, m_jet_corrector.get(), -1, sort_all_jet_pts);
            m_evt.vjets_p4        = samesign::getJets           (hyp_idx, m_jet_corrector.get(), jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale); 
            jet_flags             = samesign::getJetFlags       (hyp_idx, m_jet_corrector.get(), jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
            jet_flags_up          = samesign::getJetFlags       (hyp_idx, m_jet_corrector.get(), jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 1 );
            jet_flags_dn          = samesign::getJetFlags       (hyp_idx, m_jet_corrector.get(), jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, -1);
            m_evt.vjets_p4_up     = samesign::getJets           (hyp_idx, m_jet_corrector.get(), jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 1 ); 
            m_evt.vjets_p4_dn     = samesign::getJets           (hyp_idx, m_jet_corrector.get(), jet_type,                /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, -1);
            bjets                 = samesign::getBtaggedJets(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
            bjet_flags            = samesign::getBtaggedJetFlags(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
            bjet_flags_up         = samesign::getBtaggedJetFlags(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 1 );
            bjet_flags_dn         = samesign::getBtaggedJetFlags(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, -1);
            m_evt.vjets_bdisc     = samesign::getJetBtagDiscriminators(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
            m_evt.vjets_bdisc_up  = samesign::getJetBtagDiscriminators(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 1);
            m_evt.vjets_bdisc_dn  = samesign::getJetBtagDiscriminators(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, -1);
        }

        assert(jet_flags.size() == bjet_flags.size());
        assert(jet_flags_up.size() == bjet_flags_up.size());
        assert(jet_flags_dn.size() == bjet_flags_dn.size());

        assert(m_evt.vjets_bdisc.size() == m_evt.vjets_p4.size());
        assert(m_evt.vjets_bdisc_up.size() == m_evt.vjets_p4_up.size());
        assert(m_evt.vjets_bdisc_dn.size() == m_evt.vjets_p4_dn.size());

        // fill dijet_mass
        if (m_evt.vjets_p4.size() > 1)
        {
            LorentzVector dijet_p4 = m_evt.vjets_p4.at(0) + m_evt.vjets_p4.at(1);
            m_evt.dijet_mass = sqrt(fabs(dijet_p4.mass2()));
        }

        //cout << jet_flags.size() << "\t" << bjet_flags.size() << endl;
        // jet btag flag and mc flavor matching
        const at::CMS2Tag cms2_tag = at::GetCMS2Tag();
        if (cms2_tag.version > 21 && not evt_isRealData())
        {
            if (not m_jet_corrector)
            {
                m_evt.vjets_mcflavor_phys = samesign::getJetMcPhysMatch(hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
                m_evt.vjets_mcflavor_algo = samesign::getJetMcAlgoMatch(hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);

                m_evt.vjets_mcflavor_phys_up = samesign::getJetMcPhysMatch(hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 1);
                m_evt.vjets_mcflavor_algo_up = samesign::getJetMcAlgoMatch(hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 1);

                m_evt.vjets_mcflavor_phys_dn = samesign::getJetMcPhysMatch(hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, -1);
                m_evt.vjets_mcflavor_algo_dn = samesign::getJetMcAlgoMatch(hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, -1);
            }
            else
            {
                m_evt.vjets_mcflavor_phys = samesign::getJetMcPhysMatch(hyp_idx, m_jet_corrector.get(), jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
                m_evt.vjets_mcflavor_algo = samesign::getJetMcAlgoMatch(hyp_idx, m_jet_corrector.get(), jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);

                m_evt.vjets_mcflavor_phys_up = samesign::getJetMcPhysMatch(hyp_idx, m_jet_corrector.get(), jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 1);
                m_evt.vjets_mcflavor_algo_up = samesign::getJetMcAlgoMatch(hyp_idx, m_jet_corrector.get(), jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 1);

                m_evt.vjets_mcflavor_phys_dn = samesign::getJetMcPhysMatch(hyp_idx, m_jet_corrector.get(), jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, -1);
                m_evt.vjets_mcflavor_algo_dn = samesign::getJetMcAlgoMatch(hyp_idx, m_jet_corrector.get(), jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, -1);
            }

            assert(m_evt.vjets_mcflavor_algo.size() == m_evt.vjets_p4.size());
            assert(m_evt.vjets_mcflavor_algo_up.size() == m_evt.vjets_p4_up.size());
            assert(m_evt.vjets_mcflavor_algo_dn.size() == m_evt.vjets_p4_dn.size());
        }

        // set the seed
        const unsigned int seed = evt_event();

        // calculate the "reweighted" MC btag yields
        std::vector<bool> tmp_vjets_lbtagged;
        std::vector<bool> tmp_vjets_mbtagged;
        std::vector<bool> tmp_vjets_tbtagged;
        for (unsigned int idx = 0; idx < m_evt.vjets_p4.size(); idx++)
        {
            bool is_loose_btag  = (m_evt.vjets_bdisc.at(idx) > 0.244);
            bool is_medium_btag = (m_evt.vjets_bdisc.at(idx) > 0.679);
            bool is_tight_btag  = (m_evt.vjets_bdisc.at(idx) > 0.898);
            
            tmp_vjets_lbtagged.push_back(is_loose_btag);
            tmp_vjets_mbtagged.push_back(is_medium_btag);
            tmp_vjets_tbtagged.push_back(is_tight_btag);
        }

        m_evt.vjets_lbtagged = tmp_vjets_lbtagged;
        m_evt.vjets_mbtagged = tmp_vjets_mbtagged;
        m_evt.vjets_tbtagged = tmp_vjets_tbtagged;

        std::vector<bool> vjets_lbtagged_up;
        std::vector<bool> vjets_mbtagged_up;
        std::vector<bool> vjets_tbtagged_up;
        for (unsigned int idx = 0; idx < m_evt.vjets_p4_up.size(); idx++)
        {
            bool is_loose_btag  = (m_evt.vjets_bdisc_up.at(idx) > 0.244);
            bool is_medium_btag = (m_evt.vjets_bdisc_up.at(idx) > 0.679);
            bool is_tight_btag  = (m_evt.vjets_bdisc_up.at(idx) > 0.898);
            
            vjets_lbtagged_up.push_back(is_loose_btag);
            vjets_mbtagged_up.push_back(is_medium_btag);
            vjets_tbtagged_up.push_back(is_tight_btag);
        }

        std::vector<bool> vjets_lbtagged_dn;
        std::vector<bool> vjets_mbtagged_dn;
        std::vector<bool> vjets_tbtagged_dn;
        for (unsigned int idx = 0; idx < m_evt.vjets_p4_dn.size(); idx++)
        {
            bool is_loose_btag  = (m_evt.vjets_bdisc_dn.at(idx) > 0.244);
            bool is_medium_btag = (m_evt.vjets_bdisc_dn.at(idx) > 0.679);
            bool is_tight_btag  = (m_evt.vjets_bdisc_dn.at(idx) > 0.898);
            
            vjets_lbtagged_dn.push_back(is_loose_btag);
            vjets_mbtagged_dn.push_back(is_medium_btag);
            vjets_tbtagged_dn.push_back(is_tight_btag);
        }

        if (not evt_isRealData() && (cms2_tag.version > 21))
        {
            // # btags reweighted
            m_evt.nlbtags_reweighted    = at::MCBtagCount(JETS_BTAG_CSVL, m_evt.vjets_p4, m_evt.vjets_lbtagged, m_evt.vjets_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            m_evt.nlbtags_reweighted_up = at::MCBtagCount(JETS_BTAG_CSVL, m_evt.vjets_p4, m_evt.vjets_lbtagged, m_evt.vjets_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::up  , seed);
            m_evt.nlbtags_reweighted_dn = at::MCBtagCount(JETS_BTAG_CSVL, m_evt.vjets_p4, m_evt.vjets_lbtagged, m_evt.vjets_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::down, seed);

            m_evt.nmbtags_reweighted    = at::MCBtagCount(JETS_BTAG_CSVM, m_evt.vjets_p4, m_evt.vjets_mbtagged, m_evt.vjets_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            m_evt.nmbtags_reweighted_up = at::MCBtagCount(JETS_BTAG_CSVM, m_evt.vjets_p4, m_evt.vjets_mbtagged, m_evt.vjets_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::up  , seed);
            m_evt.nmbtags_reweighted_dn = at::MCBtagCount(JETS_BTAG_CSVM, m_evt.vjets_p4, m_evt.vjets_mbtagged, m_evt.vjets_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::down, seed);

            m_evt.ntbtags_reweighted    = at::MCBtagCount(JETS_BTAG_CSVT, m_evt.vjets_p4, m_evt.vjets_tbtagged, m_evt.vjets_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            m_evt.ntbtags_reweighted_up = at::MCBtagCount(JETS_BTAG_CSVT, m_evt.vjets_p4, m_evt.vjets_tbtagged, m_evt.vjets_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::up  , seed);
            m_evt.ntbtags_reweighted_dn = at::MCBtagCount(JETS_BTAG_CSVT, m_evt.vjets_p4, m_evt.vjets_tbtagged, m_evt.vjets_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::down, seed);

            // # btags reweighted and JES +/-
            m_evt.nlbtags_reweighted_jec_up = at::MCBtagCount(JETS_BTAG_CSVL, m_evt.vjets_p4_up, vjets_lbtagged_up, m_evt.vjets_mcflavor_algo_up, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            m_evt.nlbtags_reweighted_jec_dn = at::MCBtagCount(JETS_BTAG_CSVL, m_evt.vjets_p4_dn, vjets_lbtagged_dn, m_evt.vjets_mcflavor_algo_dn, m_sample, m_is_fast_sim, at::YieldType::base, seed);

            m_evt.nmbtags_reweighted_jec_up = at::MCBtagCount(JETS_BTAG_CSVM, m_evt.vjets_p4_up, vjets_mbtagged_up, m_evt.vjets_mcflavor_algo_up, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            m_evt.nmbtags_reweighted_jec_dn = at::MCBtagCount(JETS_BTAG_CSVM, m_evt.vjets_p4_dn, vjets_mbtagged_dn, m_evt.vjets_mcflavor_algo_dn, m_sample, m_is_fast_sim, at::YieldType::base, seed);

            m_evt.ntbtags_reweighted_jec_up = at::MCBtagCount(JETS_BTAG_CSVT, m_evt.vjets_p4_up, vjets_tbtagged_up, m_evt.vjets_mcflavor_algo_up, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            m_evt.ntbtags_reweighted_jec_dn = at::MCBtagCount(JETS_BTAG_CSVT, m_evt.vjets_p4_dn, vjets_tbtagged_dn, m_evt.vjets_mcflavor_algo_dn, m_sample, m_is_fast_sim, at::YieldType::base, seed);
        }

        // scale the JER 
        if (not evt_isRealData() && (cms2_tag.version > 21))
        {
            // set initial values
            m_evt.ht_jer        = m_evt.ht;
            m_evt.pfmet_jer     = met;
            m_evt.pfmet_phi_jer = met_phi;
            vector<LorentzVector> vjets_jer_p4  = m_evt.vjets_p4;
            vector<LorentzVector> tmp_vlbjets_p4;
            vector<LorentzVector> tmp_vmbjets_p4;
            vector<LorentzVector> tmp_vtbjets_p4;
            for (unsigned int ib = 0; ib < m_evt.vjets_p4.size(); ib++)
            {
                if (m_evt.vjets_lbtagged.at(ib)) tmp_vlbjets_p4.push_back(m_evt.vjets_p4.at(ib));
                if (m_evt.vjets_mbtagged.at(ib)) tmp_vmbjets_p4.push_back(m_evt.vjets_p4.at(ib));
                if (m_evt.vjets_tbtagged.at(ib)) tmp_vtbjets_p4.push_back(m_evt.vjets_p4.at(ib));
            }
            vector<LorentzVector> vlbjets_jer_p4 = tmp_vlbjets_p4;
            vector<LorentzVector> vmbjets_jer_p4 = tmp_vmbjets_p4;
            vector<LorentzVector> vtbjets_jer_p4 = tmp_vtbjets_p4;

            // update the values by scaling the JER
            samesign::smearJETScaleJetsMetHt(vjets_jer_p4, m_evt.pfmet_jer, m_evt.pfmet_phi_jer, m_evt.ht_jer, hyp_idx, jet_type, seed, /*dR=*/0.4, /*jet_pt>*/30, /*|eta|<*/2.4, /*mu_pt>*/mu_min_pt, /*el_pt>*/el_min_pt);            
            vector<LorentzVector> vlbjets_reweighted_jer_p4 = at::RecountedBjets(JETS_BTAG_CSVL, m_evt.vjets_p4, m_evt.vjets_lbtagged, m_evt.vjets_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            vector<LorentzVector> vmbjets_reweighted_jer_p4 = at::RecountedBjets(JETS_BTAG_CSVM, m_evt.vjets_p4, m_evt.vjets_mbtagged, m_evt.vjets_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            vector<LorentzVector> vtbjets_reweighted_jer_p4 = at::RecountedBjets(JETS_BTAG_CSVT, m_evt.vjets_p4, m_evt.vjets_tbtagged, m_evt.vjets_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            samesign::smearJETScaleJets(vlbjets_jer_p4, seed, m_jet_pt_cut);
            samesign::smearJETScaleJets(vlbjets_reweighted_jer_p4, seed, m_jet_pt_cut);
            samesign::smearJETScaleJets(vmbjets_jer_p4, seed, m_jet_pt_cut);
            samesign::smearJETScaleJets(vmbjets_reweighted_jer_p4, seed, m_jet_pt_cut);
            samesign::smearJETScaleJets(vtbjets_jer_p4, seed, m_jet_pt_cut);
            samesign::smearJETScaleJets(vtbjets_reweighted_jer_p4, seed, m_jet_pt_cut);

            // set the branches 
            m_evt.njets_jer              = vjets_jer_p4.size();
            m_evt.nlbtags_jer            = vlbjets_jer_p4.size();
            m_evt.nmbtags_jer            = vmbjets_jer_p4.size();
            m_evt.ntbtags_jer            = vtbjets_jer_p4.size();
            m_evt.nlbtags_reweighted_jer = vlbjets_reweighted_jer_p4.size();
            m_evt.nmbtags_reweighted_jer = vmbjets_reweighted_jer_p4.size();
            m_evt.ntbtags_reweighted_jer = vtbjets_reweighted_jer_p4.size();
            m_evt.vjets_p4_jer           = vjets_jer_p4;
        }

        // scale the unclustered MET
        float pfmet_uncl    = samesign::scaleMET(met, met_phi, hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/15, /*|eta|<*/2.5, /*mu_pt>*/mu_min_pt, /*el_pt>*/el_min_pt, /*scale_type=*/1 , /*scale=*/0.0);
        float pfmet_uncl_up = samesign::scaleMET(met, met_phi, hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/15, /*|eta|<*/2.5, /*mu_pt>*/mu_min_pt, /*el_pt>*/el_min_pt, /*scale_type=*/1 , /*scale=*/0.1);
        float pfmet_uncl_dn = samesign::scaleMET(met, met_phi, hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/15, /*|eta|<*/2.5, /*mu_pt>*/mu_min_pt, /*el_pt>*/el_min_pt, /*scale_type=*/-1, /*scale=*/0.1);

        m_evt.pfmet_up = m_evt.pfmet_up + pfmet_uncl - pfmet_uncl_up;
        m_evt.pfmet_dn = m_evt.pfmet_dn + pfmet_uncl - pfmet_uncl_dn;

        m_evt.jets_dr12  = (m_evt.njets>=2 ) ? rt::DeltaR(m_evt.vjets_p4.at(0) , m_evt.vjets_p4.at(1) ) : -999999.0;
        
        vector<LorentzVector> temp_jets_p4 = m_evt.vjets_p4;

        // get the untagged jets
        vector<LorentzVector> temp_jets_nontagged_p4;
        for (size_t i = 0; i != temp_jets_p4.size(); i++)
        {
            temp_jets_nontagged_p4.push_back(temp_jets_p4.at(i));
        }

        if (!temp_jets_p4.empty())
        {
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
                std::sort(temp_jets_nontagged_p4.begin(), temp_jets_nontagged_p4.end(), at::SortByDeltaR<LorentzVector>(p4));

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
            std::sort(temp_jets_p4.begin(), temp_jets_p4.end(), at::SortByDeltaR<LorentzVector>(m_evt.lep1.p4));
            m_evt.lep1_nearjet_p4 = temp_jets_p4.front();
            m_evt.lep1_nearjet_dr = rt::DeltaR(m_evt.lep1.p4, temp_jets_p4.front());

            // nearest to lep2
            std::sort(temp_jets_p4.begin(), temp_jets_p4.end(), at::SortByDeltaR<LorentzVector>(m_evt.lep2.p4));
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
        }

        //------------------------------------------------------
        // track isolation variable definition
        //------------------------------------------------------
        float dz_cut = 0.05;
        float dz_cut_loose = 0.1;

        //------------------------------------------------------
        // store pt and iso for most isolated track (pt>10 GeV) and (pt>5 GeV)
        //------------------------------------------------------
        float miniso5  = 999;
        float miniso10 = 999;

        std::vector<LorentzVector> goodLeptons;
        if (m_evt.lep1.p4.pt() > 0.01) goodLeptons.push_back(m_evt.lep1.p4);
        if (m_evt.lep2.p4.pt() > 0.01) goodLeptons.push_back(m_evt.lep2.p4);

        for (unsigned int ipf = 0; ipf < cms2.pfcands_p4().size(); ipf++)
        {
            if (cms2.pfcands_p4().at(ipf).pt() < 5) continue;
            if (cms2.pfcands_charge().at(ipf) == 0) continue;

            struct at::myTrackIso myTrackIso = at::trackIso(ipf);
	
            bool isGoodLepton = false;
            for (int ilep = 0; ilep < (int)goodLeptons.size(); ilep++)
            {
                if (ROOT::Math::VectorUtil::DeltaR(cms2.pfcands_p4().at(ipf), goodLeptons.at(ilep)) < 0.1) isGoodLepton = true;                    
            }

            // this is with the OS requirement
            float charge = (cms2.pfcands_particleId().at(ipf) * m_evt.lep1.charge);
            // charge < 0 is a SS , charge > 0 is a OS for e/mu; need to flip for pions
            if ((abs(cms2.pfcands_particleId().at(ipf)) != 11) && (abs(cms2.pfcands_particleId().at(ipf)) != 13)) charge *= (-1); 

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
            if (fabs(mindz) > dz_cut_loose) continue;

            //store loose definition to compare with previous results
            float iso = myTrackIso.iso_dr03_dz010_pt00 / cms2.pfcands_p4().at(ipf).pt();

            if (cms2.pfcands_p4().at(ipf).pt() >= 10 && iso < m_evt.trkreliso10loose && !isGoodLepton)
            {
                m_evt.trkpt10loose     = cms2.pfcands_p4().at(ipf).pt();
                m_evt.trkreliso10loose = iso;
            }

            if (cms2.pfcands_p4().at(ipf).pt() >= 5 && iso < m_evt.trkreliso5loose && !isGoodLepton)
            {
                m_evt.trkpt5loose     = cms2.pfcands_p4().at(ipf).pt();
                m_evt.trkreliso5loose = iso;
            }

            if (cms2.pfcands_p4().at(ipf).pt() >= 5 && iso < m_evt.pfcandiso5looseZ && !isGoodLepton)
            {
                m_evt.pfcandiso5looseZ = iso;
                m_evt.pfcanddz5looseZ  = mindz;
                m_evt.pfcandpt5looseZ  = cms2.pfcands_p4().at(ipf).pt();
                m_evt.pfcand5looseZ    = cms2.pfcands_p4().at(ipf);
                m_evt.pfcandid5looseZ  = cms2.pfcands_particleId().at(ipf);
            }

            if (cms2.pfcands_p4().at(ipf).pt() >= 10 && iso < m_evt.pfcandisoOS10looseZ && !isGoodLepton && charge > 0)
            {
                m_evt.pfcandisoOS10looseZ = iso;
                m_evt.pfcanddzOS10looseZ  = mindz;
                m_evt.pfcandptOS10looseZ  = cms2.pfcands_p4().at(ipf).pt();
                m_evt.pfcandOS10looseZ    = cms2.pfcands_p4().at(ipf);
                m_evt.pfcandidOS10looseZ  = cms2.pfcands_particleId().at(ipf);
            }

            //tighten dz cut
            if (fabs(mindz) > dz_cut) continue;

            iso = myTrackIso.isoDir_dr03_dz005_pt00 / cms2.pfcands_p4().at(ipf).pt();

            if (cms2.pfcands_p4().at(ipf).pt() >= 10 && iso < m_evt.pfcanddiriso10 && !isGoodLepton)
            {
                m_evt.pfcanddiriso10 = iso;
                m_evt.pfcanddirpt10  = cms2.pfcands_p4().at(ipf).pt();
                m_evt.pfcanddir10    = cms2.pfcands_p4().at(ipf);
                m_evt.pfcanddirid10  = cms2.pfcands_particleId().at(ipf);
            }

            // with veto cone
            iso = myTrackIso.iso_dr0503_dz005_pt00 / cms2.pfcands_p4().at(ipf).pt();

            if (cms2.pfcands_p4().at(ipf).pt() >= 10 && iso < m_evt.pfcandvetoiso10 && !isGoodLepton)
            {
                m_evt.pfcandvetoiso10 = iso;
                m_evt.pfcandvetopt10  = cms2.pfcands_p4().at(ipf).pt();
                m_evt.pfcandveto10    = cms2.pfcands_p4().at(ipf);
                m_evt.pfcandvetoid10  = cms2.pfcands_particleId().at(ipf);
            }

            // with veto cone
            iso = myTrackIso.iso_dr01503_dz005_pt00 / cms2.pfcands_p4().at(ipf).pt();

            if (cms2.pfcands_p4().at(ipf).pt() >= 10 && iso < m_evt.pfcandvetoLiso10 && !isGoodLepton)
            {
                m_evt.pfcandvetoLiso10 = iso;
                m_evt.pfcandvetoLpt10  = cms2.pfcands_p4().at(ipf).pt();
                m_evt.pfcandvetoL10    = cms2.pfcands_p4().at(ipf);
                m_evt.pfcandvetoLid10  = cms2.pfcands_particleId().at(ipf);
            }

            //recalculated definition of the isolation with the default values
            iso = myTrackIso.iso_dr03_dz005_pt00 / cms2.pfcands_p4().at(ipf).pt();

            if (cms2.pfcands_p4().at(ipf).pt()>=10 && iso < miniso10 && !isGoodLepton)
            {
                miniso10          = iso;
                m_evt.trkpt10     = cms2.pfcands_p4().at(ipf).pt();
                // m_evt.mleptrk10   = (maxpt_p4 + cms2.pfcands_p4().at(ipf)).pt();
                m_evt.trkreliso10 = iso;
            }

            if (cms2.pfcands_p4().at(ipf).pt()>=5 && iso < miniso5 && !isGoodLepton)
            {
                miniso5          = iso;
                m_evt.trkpt5     = cms2.pfcands_p4().at(ipf).pt();
                // m_evt.mleptrk5   = (maxpt_p4 + cms2.pfcands_p4().at(ipf)).pt();
                m_evt.trkreliso5 = iso;
            }

            if (isGoodLepton) continue;

            if (cms2.pfcands_p4().at(ipf).pt() >= 5 && iso < m_evt.pfcandiso5)
            {
                m_evt.pfcandiso5 = iso;
                m_evt.pfcanddz5  = mindz;
                m_evt.pfcandpt5  = cms2.pfcands_p4().at(ipf).pt();
                m_evt.pfcand5    = cms2.pfcands_p4().at(ipf);
                m_evt.pfcandid5  = cms2.pfcands_particleId().at(ipf);
            }

            if (cms2.pfcands_p4().at(ipf).pt() < 10) continue;

            if (iso < m_evt.pfcandisoOS10 && charge > 0)
            {
                m_evt.pfcandisoOS10 = iso;
                m_evt.pfcanddzOS10  = mindz;
                m_evt.pfcandptOS10  = cms2.pfcands_p4().at(ipf).pt();
                m_evt.pfcandOS10    = cms2.pfcands_p4().at(ipf);
                m_evt.pfcandidOS10  = cms2.pfcands_particleId().at(ipf);
            }

            /// this is the default case Track with dz<0.05 ; pt>10 ; notLeadingLepton
            if (iso < m_evt.pfcandiso10 )
            {
                m_evt.pfcandiso10 = iso;
                m_evt.pfcanddz10  = mindz;
                m_evt.pfcandpt10  = cms2.pfcands_p4().at(ipf).pt();
                m_evt.pfcand10    = cms2.pfcands_p4().at(ipf);
                m_evt.pfcandid10  = cms2.pfcands_particleId().at(ipf);
            }

            /// Pt scan

            float iso0p1 = myTrackIso.iso_dr03_dz005_pt01 / cms2.pfcands_p4().at(ipf).pt();

            if (iso0p1 < m_evt.trkreliso10pt0p1 && !isGoodLepton)
            {
                m_evt.trkpt10pt0p1     = cms2.pfcands_p4().at(ipf).pt();
                m_evt.trkreliso10pt0p1 = iso0p1;
            }

            if (iso0p1 < m_evt.pfcandiso10pt0p1)
            {
                m_evt.pfcandpt10pt0p1  = cms2.pfcands_p4().at(ipf).pt();
                m_evt.pfcandiso10pt0p1 = iso0p1;
            }

            float iso0p2 = myTrackIso.iso_dr03_dz005_pt02  / cms2.pfcands_p4().at(ipf).pt();

            if (iso0p2 < m_evt.trkreliso10pt0p2 && !isGoodLepton)
            {
                m_evt.trkpt10pt0p2     = cms2.pfcands_p4().at(ipf).pt();
                m_evt.trkreliso10pt0p2 = iso0p2;
            }

            if (iso0p2 < m_evt.pfcandiso10pt0p2)
            {
                m_evt.pfcandpt10pt0p2  = cms2.pfcands_p4().at(ipf).pt();
                m_evt.pfcandiso10pt0p2 = iso0p2;
            }

            float iso0p3 = myTrackIso.iso_dr03_dz005_pt03  / cms2.pfcands_p4().at(ipf).pt();

            if (iso0p3 < m_evt.trkreliso10pt0p3 && !isGoodLepton)
            {
                m_evt.trkpt10pt0p3     = cms2.pfcands_p4().at(ipf).pt();
                m_evt.trkreliso10pt0p3 = iso0p3;
            }

            if (iso0p3 < m_evt.pfcandiso10pt0p3)
            {
                m_evt.pfcandpt10pt0p3  = cms2.pfcands_p4().at(ipf).pt();
                m_evt.pfcandiso10pt0p3 = iso0p3;
            }

            float iso0p4 = myTrackIso.iso_dr03_dz005_pt04  / cms2.pfcands_p4().at(ipf).pt();

            if (iso0p4 < m_evt.trkreliso10pt0p4 && !isGoodLepton)
            {
                m_evt.trkpt10pt0p4     = cms2.pfcands_p4().at(ipf).pt();
                m_evt.trkreliso10pt0p4 = iso0p4;
            }

            if (iso0p4 < m_evt.pfcandiso10pt0p4)
            {
                m_evt.pfcandpt10pt0p4  = cms2.pfcands_p4().at(ipf).pt();
                m_evt.pfcandiso10pt0p4 = iso0p4;
            }

            float iso0p5 = myTrackIso.iso_dr03_dz005_pt05  / cms2.pfcands_p4().at(ipf).pt();

            if (iso0p5 < m_evt.trkreliso10pt0p5 && !isGoodLepton)
            {
                m_evt.trkpt10pt0p5     = cms2.pfcands_p4().at(ipf).pt();
                m_evt.trkreliso10pt0p5 = iso0p5;
            }

            if (iso0p5 < m_evt.pfcandiso10pt0p5)
            {
                m_evt.pfcandpt10pt0p5  = cms2.pfcands_p4().at(ipf).pt();
                m_evt.pfcandiso10pt0p5 = iso0p5;
            }

            float iso0p6 = myTrackIso.iso_dr03_dz005_pt06  / cms2.pfcands_p4().at(ipf).pt();

            if (iso0p6 < m_evt.trkreliso10pt0p6 && !isGoodLepton)
            {
                m_evt.trkpt10pt0p6     = cms2.pfcands_p4().at(ipf).pt();
                m_evt.trkreliso10pt0p6 = iso0p6;
            }

            if (iso0p6 < m_evt.pfcandiso10pt0p6)
            {
                m_evt.pfcandpt10pt0p6  = cms2.pfcands_p4().at(ipf).pt();
                m_evt.pfcandiso10pt0p6 = iso0p6;
            }

            float iso0p7 = myTrackIso.iso_dr03_dz005_pt07  / cms2.pfcands_p4().at(ipf).pt();

            if (iso0p7 < m_evt.trkreliso10pt0p7 && !isGoodLepton)
            {
                m_evt.trkpt10pt0p7     = cms2.pfcands_p4().at(ipf).pt();
                m_evt.trkreliso10pt0p7 = iso0p7;
            }

            if (iso0p7 < m_evt.pfcandiso10pt0p7)
            {
                m_evt.pfcandpt10pt0p7  = cms2.pfcands_p4().at(ipf).pt();
                m_evt.pfcandiso10pt0p7 = iso0p7;
            }

            float iso0p8 = myTrackIso.iso_dr03_dz005_pt08  / cms2.pfcands_p4().at(ipf).pt();

            if (iso0p8 < m_evt.trkreliso10pt0p8 && !isGoodLepton)
            {
                m_evt.trkpt10pt0p8     = cms2.pfcands_p4().at(ipf).pt();
                m_evt.trkreliso10pt0p8 = iso0p8;
            }

            if (iso0p8 < m_evt.pfcandiso10pt0p8)
            {
                m_evt.pfcandpt10pt0p8  = cms2.pfcands_p4().at(ipf).pt();
                m_evt.pfcandiso10pt0p8 = iso0p8;
            }

            float iso0p9 = myTrackIso.iso_dr03_dz005_pt09  / cms2.pfcands_p4().at(ipf).pt();

            if (iso0p9 < m_evt.trkreliso10pt0p9 && !isGoodLepton)
            {
                m_evt.trkpt10pt0p9     = cms2.pfcands_p4().at(ipf).pt();
                m_evt.trkreliso10pt0p9 = iso0p9;
            }

            if (iso0p9 < m_evt.pfcandiso10pt0p9)
            {
                m_evt.pfcandpt10pt0p9  = cms2.pfcands_p4().at(ipf).pt();
                m_evt.pfcandiso10pt0p9 = iso0p9;
            }

            float iso1p0 = myTrackIso.iso_dr03_dz005_pt10  / cms2.pfcands_p4().at(ipf).pt();

            if (iso1p0 < m_evt.trkreliso10pt1p0 && !isGoodLepton)
            {
                m_evt.trkpt10pt1p0     = cms2.pfcands_p4().at(ipf).pt();
                m_evt.trkreliso10pt1p0 = iso1p0;
            }

            if (iso1p0 < m_evt.pfcandiso10pt1p0 )
            {
                m_evt.pfcandpt10pt1p0  = cms2.pfcands_p4().at(ipf).pt();
                m_evt.pfcandiso10pt1p0 = iso1p0;
            }
        }


        //----------------------------------------
        // TAU
        //----------------------------------------

        int indexTauMax=-1;
        double ptTauMax=0.;

        int indexTauLooseMax=-1;
        double ptTauLooseMax=0.;

        int indexTauMax15=-1;
        double ptTauMax15=0.;


        if (cms2_tag.version > 13)
        {
            for (unsigned int itau = 0; itau < cms2.taus_pf_p4().size(); itau++)
            {
                if(cms2.taus_pf_p4().at(itau).pt() < 15) continue;
                // /// Use only OS charge
                // if((taus_pf_charge().at(itau)*id1_)>0) continue;

                ///
                bool isHypLepton = false;
                if (rt::DeltaR(cms2.taus_pf_p4().at(itau), m_evt.lep1.p4) < 0.4) isHypLepton = true;
                if (rt::DeltaR(cms2.taus_pf_p4().at(itau), m_evt.lep2.p4) < 0.4) isHypLepton = true;

                if (isHypLepton) continue;
                if (!cms2.taus_pf_byDecayModeFinding().at(itau)) continue;

                // isolation Medium ; pt > 15
                if (cms2.taus_pf_byMediumIsolationMVA2().at(itau))
                {
                    if (cms2.taus_pf_p4().at(itau).pt() > ptTauMax15)
                    {
                        ptTauMax15 = cms2.taus_pf_p4().at(itau).pt();
                        indexTauMax15 = itau;
                    }	
                }

                if (cms2.taus_pf_p4().at(itau).pt() < 20) continue;

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
                    int leadingPtCand_index = cms2.taus_pf_pfcandIndicies().at(indexTauMax15).at(0);
                    m_evt.pfTau15_leadPtcand = cms2.pfcands_p4().at(leadingPtCand_index);
                    m_evt.pfTau15_leadPtcandID = cms2.pfcands_particleId().at(leadingPtCand_index);
                }
            }

            if (indexTauMax!=-1)
            {
                m_evt.pfTau = cms2.taus_pf_p4().at(indexTauMax);
                if (cms2.taus_pf_pfcandIndicies().at(indexTauMax).size() > 0)
                {
                    int leadingPtCand_index = cms2.taus_pf_pfcandIndicies().at(indexTauMax).at(0);
                    m_evt.pfTau_leadPtcand = cms2.pfcands_p4().at(leadingPtCand_index);
                    m_evt.pfTau_leadPtcandID = cms2.pfcands_particleId().at(leadingPtCand_index);
                }
            }

            if (indexTauLooseMax != -1)
            {
                m_evt.pfTauLoose = cms2.taus_pf_p4().at(indexTauLooseMax);
                if (cms2.taus_pf_pfcandIndicies().at(indexTauLooseMax).size() > 0)
                {
                    int leadingPtCand_index = cms2.taus_pf_pfcandIndicies().at(indexTauLooseMax).at(0);
                    m_evt.pfTauLoose_leadPtcand = cms2.pfcands_p4().at(leadingPtCand_index);
                    m_evt.pfTauLoose_leadPtcandID = cms2.pfcands_particleId().at(leadingPtCand_index);
                }
            }
        }

        //
        // jet-PV matching
        //
        if (cms2_tag.version > 13)
        {
            m_evt.pfjets_mvaPUid      = sortJetValues(jet_flags    , all_jet_p4s , cms2.pfjets_full53xmvavalue());
            m_evt.pfjets_mva5xPUid    = sortJetValues(jet_flags    , all_jet_p4s , cms2.pfjets_full5xmvavalue() );
            m_evt.pfjets_up_mva5xPUid = sortJetValues(jet_flags_up , all_jet_p4s , cms2.pfjets_full5xmvavalue() );
            m_evt.pfjets_dn_mva5xPUid = sortJetValues(jet_flags_dn , all_jet_p4s , cms2.pfjets_full5xmvavalue() );
            m_evt.pfjets_mvaBeta      = sortJetValues(jet_flags    , all_jet_p4s , cms2.pfjets_full53xmva_beta());
        }

        vecd tmp_pfjets_beta;
        vecd tmp_pfjets_beta2;
        vecd tmp_pfjets_beta_0p1;
        vecd tmp_pfjets_beta_0p2;
        vecd tmp_pfjets_beta2_0p1;
        vecd tmp_pfjets_beta2_0p5;
        for (size_t pfjidx = 0; pfjidx < all_jet_p4s.size(); pfjidx++)
        {
            tmp_pfjets_beta     .push_back ( pfjet_beta( pfjidx, 1)       );
            tmp_pfjets_beta2    .push_back ( pfjet_beta( pfjidx, 2)       );
            tmp_pfjets_beta_0p1 .push_back ( pfjet_beta( pfjidx, 1, 0.1 ) );
            tmp_pfjets_beta_0p2 .push_back ( pfjet_beta( pfjidx, 1, 0.2 ) );
            tmp_pfjets_beta2_0p1.push_back ( pfjet_beta( pfjidx, 2, 0.1 ) );
            tmp_pfjets_beta2_0p5.push_back ( pfjet_beta( pfjidx, 2, 0.5 ) );
        }

        m_evt.pfjets_beta      = sortJetValues(jet_flags, all_jet_p4s, tmp_pfjets_beta     );
        m_evt.pfjets_beta2     = sortJetValues(jet_flags, all_jet_p4s, tmp_pfjets_beta2    );
        m_evt.pfjets_beta_0p1  = sortJetValues(jet_flags, all_jet_p4s, tmp_pfjets_beta_0p1 );
        m_evt.pfjets_beta_0p2  = sortJetValues(jet_flags, all_jet_p4s, tmp_pfjets_beta_0p2 );
        m_evt.pfjets_beta2_0p1 = sortJetValues(jet_flags, all_jet_p4s, tmp_pfjets_beta2_0p1);
        m_evt.pfjets_beta2_0p5 = sortJetValues(jet_flags, all_jet_p4s, tmp_pfjets_beta2_0p5);
        
        //
        // store info for third lepton (choose highest pt, separated from hyp leptons by dR=0.1)
        //
        int lep3idx = -1;
        int lep3id  = 0;
        float lep3pt = -999999.;
        for (unsigned int el3idx = 0; el3idx < cms2.els_p4().size(); el3idx++)
        {
            if (cms2.els_p4().at(el3idx).pt() < 5.) continue;
            if (rt::DeltaR(cms2.els_p4().at(el3idx),m_evt.lep1.p4) < 0.1) continue;
            if (rt::DeltaR(cms2.els_p4().at(el3idx),m_evt.lep2.p4) < 0.1) continue;
            if (cms2.els_p4().at(el3idx).pt() > lep3pt)
            {
                lep3idx = el3idx;
                lep3id  = -11 * cms2.els_charge().at(el3idx);
                lep3pt  = cms2.els_p4().at(el3idx).pt();
            }
        }

        for (unsigned int mu3idx = 0; mu3idx < cms2.mus_p4().size(); mu3idx++)
        {
            if (cms2.mus_p4().at(mu3idx).pt() < 5.) continue;
            if (rt::DeltaR(cms2.mus_p4().at(mu3idx),m_evt.lep1.p4) < 0.1) continue;
            if (rt::DeltaR(cms2.mus_p4().at(mu3idx),m_evt.lep2.p4) < 0.1) continue;
            if (cms2.mus_p4().at(mu3idx).pt() > lep3pt)
            {
                lep3idx = mu3idx;
                lep3id  = -13 * cms2.mus_charge().at(mu3idx);
                lep3pt  = cms2.mus_p4().at(mu3idx).pt();
            }
        }

        m_evt.lep3.FillCommon(lep3id, lep3idx);

        //
        // get matching info for jets after JER smearing
        //
        std::vector<LorentzVector> all_pfjets = samesign::getAllCorrectedJets(jet_type);
        vecd tmp_pfjets_jer_mva5xPUid;
        for (size_t jidx = 0; jidx < m_evt.vjets_p4_jer.size(); jidx++)
        {
            LorentzVector jer_p4 = m_evt.vjets_p4_jer.at(jidx);

            for (size_t kidx = 0; kidx < all_pfjets.size(); kidx++)
            {
                if (rt::DeltaR(jer_p4, all_pfjets.at(kidx)) > 0.01) continue;
                tmp_pfjets_jer_mva5xPUid.push_back(cms2.pfjets_full5xmvavalue().at(kidx));
            }
        }

        m_evt.pfjets_jer_mva5xPUid = tmp_pfjets_jer_mva5xPUid;
        assert(m_evt.pfjets_jer_mva5xPUid.size() == m_evt.vjets_p4_jer.size());

        //
        // add branches for convenience
        //
        m_evt.passes_isotrk_veto = passesIsoTrkVeto();
        m_evt.passes_tau_veto    = passesTauVeto();
        int njets_pv_tmp0     = 0;
        int njets_pv_up_tmp0  = 0;
        int njets_pv_dn_tmp0  = 0;
        int njets_pv_jer_tmp0 = 0;
        int njets_pv_tmp1     = 0;
        int njets_pv_tmp2     = 0;
        std::vector<bool> tmp_vjets_matched_pv;
        std::vector<bool> tmp_vjets_matched_pv_up;
        std::vector<bool> tmp_vjets_matched_pv_dn;
        std::vector<bool> tmp_vjets_matched_pv_jer;
        if (cms2_tag.version > 13)
        {
            for (unsigned int jetpvidx = 0; jetpvidx < m_evt.vjets_p4.size(); jetpvidx++)
            {
                bool jet_is_matched = passesMVAJetId(m_evt.vjets_p4.at(jetpvidx), m_evt.pfjets_mva5xPUid.at(jetpvidx), 0);
                tmp_vjets_matched_pv.push_back(jet_is_matched);
                if (jet_is_matched) ++njets_pv_tmp0;
                if (passesMVAJetId(m_evt.vjets_p4.at(jetpvidx), m_evt.pfjets_mva5xPUid.at(jetpvidx), 1)) ++njets_pv_tmp1;
                if (passesMVAJetId(m_evt.vjets_p4.at(jetpvidx), m_evt.pfjets_mva5xPUid.at(jetpvidx), 2)) ++njets_pv_tmp2;                
            }
            m_evt.vjets_matched_pv = tmp_vjets_matched_pv;

            for (unsigned int jetpvidx = 0; jetpvidx < m_evt.vjets_p4_up.size(); jetpvidx++)
            {
                bool jet_is_matched = passesMVAJetId(m_evt.vjets_p4_up.at(jetpvidx), m_evt.pfjets_up_mva5xPUid.at(jetpvidx), 0);
                tmp_vjets_matched_pv_up.push_back(jet_is_matched);
                if (jet_is_matched) ++njets_pv_up_tmp0;
            }
            m_evt.vjets_matched_pv_up = tmp_vjets_matched_pv_up;

            for (unsigned int jetpvidx = 0; jetpvidx < m_evt.vjets_p4_dn.size(); jetpvidx++)
            {
                bool jet_is_matched = passesMVAJetId(m_evt.vjets_p4_dn.at(jetpvidx), m_evt.pfjets_up_mva5xPUid.at(jetpvidx), 0);
                tmp_vjets_matched_pv_dn.push_back(jet_is_matched);
                if (jet_is_matched) ++njets_pv_dn_tmp0;
            }
            m_evt.vjets_matched_pv_dn = tmp_vjets_matched_pv_dn;

            for (unsigned int jetpvidx = 0; jetpvidx < m_evt.vjets_p4_jer.size(); jetpvidx++)
            {
                bool jet_is_matched = passesMVAJetId(m_evt.vjets_p4_jer.at(jetpvidx), m_evt.pfjets_jer_mva5xPUid.at(jetpvidx), 0);
                tmp_vjets_matched_pv_jer.push_back(jet_is_matched);
                if (jet_is_matched) ++njets_pv_jer_tmp0;
            }
            m_evt.vjets_matched_pv_jer = tmp_vjets_matched_pv_jer;
        }

        m_evt.njets_pv_tight0 = njets_pv_tmp0;
        m_evt.njets_pv_tight1 = njets_pv_tmp1;
        m_evt.njets_pv_tight2 = njets_pv_tmp2;
        m_evt.njets_pv_tight0_up = njets_pv_up_tmp0;
        m_evt.njets_pv_tight0_dn = njets_pv_dn_tmp0;
        m_evt.njets_pv_tight0_jer = njets_pv_jer_tmp0;

        std::vector<LorentzVector> vjets_matched_p4;
        std::vector<LorentzVector> vjets_matched_p4_up;
        std::vector<LorentzVector> vjets_matched_p4_dn;
        std::vector<LorentzVector> vjets_matched_p4_jer;
        for (unsigned int idx = 0; idx < m_evt.vjets_p4.size(); idx++)
        {
            if (!m_evt.vjets_matched_pv.at(idx)) continue;
            vjets_matched_p4.push_back(m_evt.vjets_p4.at(idx));
        }

        for (unsigned int idx = 0; idx < m_evt.vjets_p4_up.size(); idx++)
        {
            if (!m_evt.vjets_matched_pv_up.at(idx)) continue;
            vjets_matched_p4_up.push_back(m_evt.vjets_p4_up.at(idx));
        }

        for (unsigned int idx = 0; idx < m_evt.vjets_p4_dn.size(); idx++)
        {
            if (!m_evt.vjets_matched_pv_dn.at(idx)) continue;
            vjets_matched_p4_dn.push_back(m_evt.vjets_p4_dn.at(idx));
        }

        for (unsigned int idx = 0; idx < m_evt.vjets_p4_jer.size(); idx++)
        {
            if (!m_evt.vjets_matched_pv_jer.at(idx)) continue;
            vjets_matched_p4_jer.push_back(m_evt.vjets_p4_jer.at(idx));
        }

        if (vjets_matched_p4.size() > 1)
        {
            LorentzVector p4_dijet = vjets_matched_p4.at(0) + vjets_matched_p4.at(1);
            m_evt.mt2j          = MT2J(met, met_phi, m_evt.lep1.p4, m_evt.lep2.p4, vjets_matched_p4);
            m_evt.dijet_mass_pv = p4_dijet.mass();
        }

        if (vjets_matched_p4_up.size() > 1)
        {
            LorentzVector p4_dijet = vjets_matched_p4_up.at(0) + vjets_matched_p4_up.at(1);
            m_evt.mt2j_up       = MT2J(m_evt.pfmet_up, m_evt.pfmet_phi_up, m_evt.lep1.p4, m_evt.lep2.p4, vjets_matched_p4_up);
        }

        if (vjets_matched_p4_dn.size() > 1)
        {
            LorentzVector p4_dijet = vjets_matched_p4_dn.at(0) + vjets_matched_p4_dn.at(1);
            m_evt.mt2j_dn       = MT2J(m_evt.pfmet_dn, m_evt.pfmet_phi_dn, m_evt.lep1.p4, m_evt.lep2.p4, vjets_matched_p4_dn);
        }

        if (vjets_matched_p4_jer.size() > 1)
        {
            LorentzVector p4_dijet = vjets_matched_p4_jer.at(0) + vjets_matched_p4_jer.at(1);
            m_evt.mt2j_jer      = MT2J(m_evt.pfmet_jer, m_evt.pfmet_phi_jer, m_evt.lep1.p4, m_evt.lep2.p4, vjets_matched_p4_jer);
        }

        // get invariant mass between leptons and two leading jets in the event
        if (m_evt.vjets_p4.size() > 1)
        {
            LorentzVector dijet_p4 = m_evt.vjets_p4.at(0) + m_evt.vjets_p4.at(1);
            m_evt.lep1_jj_p4 = dijet_p4 + m_evt.lep1.p4;
            m_evt.lep2_jj_p4 = dijet_p4 + m_evt.lep2.p4;
            m_evt.jjl_p4 = (rt::DeltaR(dijet_p4, m_evt.lep1.p4) < rt::DeltaR(dijet_p4, m_evt.lep2.p4)) ? m_evt.lep1_jj_p4 : m_evt.lep2_jj_p4;            
        }

        if (m_evt.vjets_p4_up.size() > 1)
        {
            LorentzVector dijet_p4 = m_evt.vjets_p4_up.at(0) + m_evt.vjets_p4_up.at(1);
            LorentzVector tmp_lep1_jj_p4 = dijet_p4 + m_evt.lep1.p4;
            LorentzVector tmp_lep2_jj_p4 = dijet_p4 + m_evt.lep2.p4;
            m_evt.jjl_p4_up = (rt::DeltaR(dijet_p4, m_evt.lep1.p4) < rt::DeltaR(dijet_p4, m_evt.lep2.p4)) ? tmp_lep1_jj_p4 : tmp_lep2_jj_p4;            
        }

        if (m_evt.vjets_p4_dn.size() > 1)
        {
            LorentzVector dijet_p4 = m_evt.vjets_p4_dn.at(0) + m_evt.vjets_p4_dn.at(1);
            LorentzVector tmp_lep1_jj_p4 = dijet_p4 + m_evt.lep1.p4;
            LorentzVector tmp_lep2_jj_p4 = dijet_p4 + m_evt.lep2.p4;
            m_evt.jjl_p4_dn = (rt::DeltaR(dijet_p4, m_evt.lep1.p4) < rt::DeltaR(dijet_p4, m_evt.lep2.p4)) ? tmp_lep1_jj_p4 : tmp_lep2_jj_p4;            
        }

        if (m_evt.vjets_p4_jer.size() > 1)
        {
            LorentzVector dijet_p4 = m_evt.vjets_p4_jer.at(0) + m_evt.vjets_p4_jer.at(1);
            LorentzVector tmp_lep1_jj_p4 = dijet_p4 + m_evt.lep1.p4;
            LorentzVector tmp_lep2_jj_p4 = dijet_p4 + m_evt.lep2.p4;
            m_evt.jjl_p4_jer = (rt::DeltaR(dijet_p4, m_evt.lep1.p4) < rt::DeltaR(dijet_p4, m_evt.lep2.p4)) ? tmp_lep1_jj_p4 : tmp_lep2_jj_p4;            
        }

        //
        // now let's do the same things for btags matched to the PV
        //
        if (not evt_isRealData() && (cms2_tag.version > 21))
        {
            // calculate the "reweighted" MC btag yields
            std::vector<bool> tmp_vjets_pv_lbtagged;
            std::vector<bool> tmp_vjets_pv_mbtagged;
            std::vector<bool> tmp_vjets_pv_tbtagged;
            veci tmp_vjets_pv_mcflavor_algo;
            for (unsigned int idx = 0; idx < m_evt.vjets_p4.size(); idx++)
            {           
                if (!m_evt.vjets_matched_pv.at(idx)) continue;

                bool is_loose_btag  = (m_evt.vjets_bdisc.at(idx) > 0.244);
                bool is_medium_btag = (m_evt.vjets_bdisc.at(idx) > 0.679);
                bool is_tight_btag  = (m_evt.vjets_bdisc.at(idx) > 0.898);

                tmp_vjets_pv_mcflavor_algo.push_back(m_evt.vjets_mcflavor_algo.at(idx));
            
                tmp_vjets_pv_lbtagged.push_back(is_loose_btag);
                tmp_vjets_pv_mbtagged.push_back(is_medium_btag);
                tmp_vjets_pv_tbtagged.push_back(is_tight_btag);
            }

            std::vector<bool> vjets_pv_lbtagged_up;
            std::vector<bool> vjets_pv_mbtagged_up;
            std::vector<bool> vjets_pv_tbtagged_up;
            veci vjets_pv_mcflavor_algo_up;
            for (unsigned int idx = 0; idx < m_evt.vjets_p4_up.size(); idx++)
            {
                if (!m_evt.vjets_matched_pv_up.at(idx)) continue;

                bool is_loose_btag  = (m_evt.vjets_bdisc_up.at(idx) > 0.244);
                bool is_medium_btag = (m_evt.vjets_bdisc_up.at(idx) > 0.679);
                bool is_tight_btag  = (m_evt.vjets_bdisc_up.at(idx) > 0.898);

                vjets_pv_mcflavor_algo_up.push_back(m_evt.vjets_mcflavor_algo_up.at(idx));
            
                vjets_pv_lbtagged_up.push_back(is_loose_btag);
                vjets_pv_mbtagged_up.push_back(is_medium_btag);
                vjets_pv_tbtagged_up.push_back(is_tight_btag);
            }

            std::vector<bool> vjets_pv_lbtagged_dn;
            std::vector<bool> vjets_pv_mbtagged_dn;
            std::vector<bool> vjets_pv_tbtagged_dn;
            veci vjets_pv_mcflavor_algo_dn;
            for (unsigned int idx = 0; idx < m_evt.vjets_p4_dn.size(); idx++)
            {
                if (!m_evt.vjets_matched_pv_dn.at(idx)) continue;

                bool is_loose_btag  = (m_evt.vjets_bdisc_dn.at(idx) > 0.244);
                bool is_medium_btag = (m_evt.vjets_bdisc_dn.at(idx) > 0.679);
                bool is_tight_btag  = (m_evt.vjets_bdisc_dn.at(idx) > 0.898);

                vjets_pv_mcflavor_algo_dn.push_back(m_evt.vjets_mcflavor_algo_dn.at(idx));
            
                vjets_pv_lbtagged_dn.push_back(is_loose_btag);
                vjets_pv_mbtagged_dn.push_back(is_medium_btag);
                vjets_pv_tbtagged_dn.push_back(is_tight_btag);
            }

            // # btags reweighted
            m_evt.nlbtags_pv_reweighted    = at::MCBtagCount(JETS_BTAG_CSVL, vjets_matched_p4, tmp_vjets_pv_lbtagged, tmp_vjets_pv_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            m_evt.nlbtags_pv_reweighted_up = at::MCBtagCount(JETS_BTAG_CSVL, vjets_matched_p4, tmp_vjets_pv_lbtagged, tmp_vjets_pv_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::up  , seed);
            m_evt.nlbtags_pv_reweighted_dn = at::MCBtagCount(JETS_BTAG_CSVL, vjets_matched_p4, tmp_vjets_pv_lbtagged, tmp_vjets_pv_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::down, seed);

            m_evt.nmbtags_pv_reweighted    = at::MCBtagCount(JETS_BTAG_CSVM, vjets_matched_p4, tmp_vjets_pv_mbtagged, tmp_vjets_pv_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            m_evt.nmbtags_pv_reweighted_up = at::MCBtagCount(JETS_BTAG_CSVM, vjets_matched_p4, tmp_vjets_pv_mbtagged, tmp_vjets_pv_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::up  , seed);
            m_evt.nmbtags_pv_reweighted_dn = at::MCBtagCount(JETS_BTAG_CSVM, vjets_matched_p4, tmp_vjets_pv_mbtagged, tmp_vjets_pv_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::down, seed);

            m_evt.ntbtags_pv_reweighted    = at::MCBtagCount(JETS_BTAG_CSVT, vjets_matched_p4, tmp_vjets_pv_tbtagged, tmp_vjets_pv_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            m_evt.ntbtags_pv_reweighted_up = at::MCBtagCount(JETS_BTAG_CSVT, vjets_matched_p4, tmp_vjets_pv_tbtagged, tmp_vjets_pv_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::up  , seed);
            m_evt.ntbtags_pv_reweighted_dn = at::MCBtagCount(JETS_BTAG_CSVT, vjets_matched_p4, tmp_vjets_pv_tbtagged, tmp_vjets_pv_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::down, seed);

            // # btags reweighted and JES +/-
            m_evt.nlbtags_pv_reweighted_jec_up = at::MCBtagCount(JETS_BTAG_CSVL, vjets_matched_p4_up, vjets_pv_lbtagged_up, vjets_pv_mcflavor_algo_up, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            m_evt.nlbtags_pv_reweighted_jec_dn = at::MCBtagCount(JETS_BTAG_CSVL, vjets_matched_p4_dn, vjets_pv_lbtagged_dn, vjets_pv_mcflavor_algo_dn, m_sample, m_is_fast_sim, at::YieldType::base, seed);

            m_evt.nmbtags_pv_reweighted_jec_up = at::MCBtagCount(JETS_BTAG_CSVM, vjets_matched_p4_up, vjets_pv_mbtagged_up, vjets_pv_mcflavor_algo_up, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            m_evt.nmbtags_pv_reweighted_jec_dn = at::MCBtagCount(JETS_BTAG_CSVM, vjets_matched_p4_dn, vjets_pv_mbtagged_dn, vjets_pv_mcflavor_algo_dn, m_sample, m_is_fast_sim, at::YieldType::base, seed);

            m_evt.ntbtags_pv_reweighted_jec_up = at::MCBtagCount(JETS_BTAG_CSVT, vjets_matched_p4_up, vjets_pv_tbtagged_up, vjets_pv_mcflavor_algo_up, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            m_evt.ntbtags_pv_reweighted_jec_dn = at::MCBtagCount(JETS_BTAG_CSVT, vjets_matched_p4_dn, vjets_pv_tbtagged_dn, vjets_pv_mcflavor_algo_dn, m_sample, m_is_fast_sim, at::YieldType::base, seed);

            // set initial values
            float tmp_ht = m_evt.ht;
            float tmp_pfmet = met;
            float tmp_pfmet_phi = met_phi;
            vector<LorentzVector> vjets_jer_p4  = vjets_matched_p4;
            vector<LorentzVector> tmp_vlbjets_p4;
            vector<LorentzVector> tmp_vmbjets_p4;
            vector<LorentzVector> tmp_vtbjets_p4;
            for (unsigned int ib = 0; ib < vjets_matched_p4.size(); ib++)
            {
                if (tmp_vjets_pv_lbtagged.at(ib)) tmp_vlbjets_p4.push_back(vjets_matched_p4.at(ib));
                if (tmp_vjets_pv_mbtagged.at(ib)) tmp_vmbjets_p4.push_back(vjets_matched_p4.at(ib));
                if (tmp_vjets_pv_tbtagged.at(ib)) tmp_vtbjets_p4.push_back(vjets_matched_p4.at(ib));
            }
            vector<LorentzVector> vlbjets_jer_p4 = tmp_vlbjets_p4;
            vector<LorentzVector> vmbjets_jer_p4 = tmp_vmbjets_p4;
            vector<LorentzVector> vtbjets_jer_p4 = tmp_vtbjets_p4;

            // update the values by scaling the JER
            samesign::smearJETScaleJetsMetHt(vjets_jer_p4, tmp_pfmet, tmp_pfmet_phi, tmp_ht, hyp_idx, jet_type, seed, /*dR=*/0.4, /*jet_pt>*/30, /*|eta|<*/2.4, /*mu_pt>*/mu_min_pt, /*el_pt>*/el_min_pt);            
            vector<LorentzVector> vlbjets_reweighted_jer_p4 = at::RecountedBjets(JETS_BTAG_CSVL, vjets_matched_p4, tmp_vjets_pv_lbtagged, tmp_vjets_pv_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            vector<LorentzVector> vmbjets_reweighted_jer_p4 = at::RecountedBjets(JETS_BTAG_CSVM, vjets_matched_p4, tmp_vjets_pv_mbtagged, tmp_vjets_pv_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            vector<LorentzVector> vtbjets_reweighted_jer_p4 = at::RecountedBjets(JETS_BTAG_CSVT, vjets_matched_p4, tmp_vjets_pv_tbtagged, tmp_vjets_pv_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            samesign::smearJETScaleJets(vlbjets_reweighted_jer_p4, seed, m_jet_pt_cut);
            samesign::smearJETScaleJets(vmbjets_reweighted_jer_p4, seed, m_jet_pt_cut);
            samesign::smearJETScaleJets(vtbjets_reweighted_jer_p4, seed, m_jet_pt_cut);

            // set the branches 
            m_evt.nlbtags_pv_reweighted_jer = vlbjets_reweighted_jer_p4.size();
            m_evt.nmbtags_pv_reweighted_jer = vmbjets_reweighted_jer_p4.size();
            m_evt.ntbtags_pv_reweighted_jer = vtbjets_reweighted_jer_p4.size();
        }

        // Fill the tree
        m_tree->Fill();

        // printout
        if (m_evt.is_good_lumi && m_evt.njets >= 2)
        {
            scale = 1.0;
            if (dilepton_type==at::DileptonHypType::MUMU)
            {
                if (m_verbose) {cout << "type == mm" << endl;}
                if (charge_type==at::DileptonChargeType::SS) m_count_ss[0] += scale;
                if (charge_type==at::DileptonChargeType::SF) m_count_sf[0] += scale;
                if (charge_type==at::DileptonChargeType::DF) m_count_df[0] += scale;
                if (charge_type==at::DileptonChargeType::OS) m_count_os[0] += scale;
                if (charge_type==at::DileptonChargeType::SS && m_evt.ntbtags == 0 && m_evt.nlbtags < 2) m_count_nobtag_ss[0] += scale;
                if (charge_type==at::DileptonChargeType::SF && m_evt.ntbtags == 0 && m_evt.nlbtags < 2) m_count_nobtag_sf[0] += scale;
                if (charge_type==at::DileptonChargeType::DF && m_evt.ntbtags == 0 && m_evt.nlbtags < 2) m_count_nobtag_df[0] += scale;
                if (charge_type==at::DileptonChargeType::OS && m_evt.ntbtags == 0 && m_evt.nlbtags < 2) m_count_nobtag_os[0] += scale;
            }
            if (dilepton_type==at::DileptonHypType::EMU)
            {
                if (m_verbose) {cout << "type == em" << endl;}
                if (charge_type==at::DileptonChargeType::SS) m_count_ss[1] += scale;
                if (charge_type==at::DileptonChargeType::SF) m_count_sf[1] += scale;
                if (charge_type==at::DileptonChargeType::DF) m_count_df[1] += scale;
                if (charge_type==at::DileptonChargeType::OS) m_count_os[1] += scale;
                if (charge_type==at::DileptonChargeType::SS && m_evt.ntbtags == 0 && m_evt.nlbtags < 2) m_count_nobtag_ss[1] += scale;
                if (charge_type==at::DileptonChargeType::SF && m_evt.ntbtags == 0 && m_evt.nlbtags < 2) m_count_nobtag_sf[1] += scale;
                if (charge_type==at::DileptonChargeType::DF && m_evt.ntbtags == 0 && m_evt.nlbtags < 2) m_count_nobtag_df[1] += scale;
                if (charge_type==at::DileptonChargeType::OS && m_evt.ntbtags == 0 && m_evt.nlbtags < 2) m_count_nobtag_os[1] += scale;
            }
            if (dilepton_type==at::DileptonHypType::EE)
            {
                if (m_verbose) {cout << "type == ee" << endl;}
                if (charge_type==at::DileptonChargeType::SS) m_count_ss[2] += scale;
                if (charge_type==at::DileptonChargeType::SF) m_count_sf[2] += scale;
                if (charge_type==at::DileptonChargeType::DF) m_count_df[2] += scale;
                if (charge_type==at::DileptonChargeType::OS) m_count_os[2] += scale;
                if (charge_type==at::DileptonChargeType::SS && m_evt.ntbtags == 0 && m_evt.nlbtags < 2) m_count_nobtag_ss[2] += scale;
                if (charge_type==at::DileptonChargeType::SF && m_evt.ntbtags == 0 && m_evt.nlbtags < 2) m_count_nobtag_sf[2] += scale;
                if (charge_type==at::DileptonChargeType::DF && m_evt.ntbtags == 0 && m_evt.nlbtags < 2) m_count_nobtag_df[2] += scale;
                if (charge_type==at::DileptonChargeType::OS && m_evt.ntbtags == 0 && m_evt.nlbtags < 2) m_count_nobtag_os[2] += scale;
            }
            // count all 
            {
                if (charge_type==at::DileptonChargeType::SS) m_count_ss[3] += scale;
                if (charge_type==at::DileptonChargeType::SF) m_count_sf[3] += scale;
                if (charge_type==at::DileptonChargeType::DF) m_count_df[3] += scale;
                if (charge_type==at::DileptonChargeType::OS) m_count_os[3] += scale;
                if (charge_type==at::DileptonChargeType::SS && m_evt.ntbtags == 0 && m_evt.nlbtags < 2) m_count_nobtag_ss[3] += scale;
                if (charge_type==at::DileptonChargeType::SF && m_evt.ntbtags == 0 && m_evt.nlbtags < 2) m_count_nobtag_sf[3] += scale;
                if (charge_type==at::DileptonChargeType::DF && m_evt.ntbtags == 0 && m_evt.nlbtags < 2) m_count_nobtag_df[3] += scale;
                if (charge_type==at::DileptonChargeType::OS && m_evt.ntbtags == 0 && m_evt.nlbtags < 2) m_count_nobtag_os[3] += scale;
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

float EwkinoSSAnalysisLooper::GetFakeRateValue(const int lep_id, const int lep_idx) const 
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

float EwkinoSSAnalysisLooper::GetFlipRateValue(const int lep_id, const int lep_idx) const 
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

bool EwkinoSSAnalysisLooper::passesIsoTrkVeto()
{
    //pass isolated track veto
    //unfortunately changed default value to 9999.
    // We want to check for the generic track only there is now good e/mu candidate
    if (m_evt.pfcandptOS10looseZ < 9998. && abs(m_evt.pfcandid5looseZ) != 13 && abs(m_evt.pfcandid5looseZ) != 11 && m_evt.pfcandisoOS10looseZ < 0.1) return false;
    if (m_evt.pfcandpt5looseZ    < 9998. && abs(m_evt.pfcandid5looseZ) == 13 && m_evt.pfcandiso5looseZ < 0.2) return false;
    if (m_evt.pfcandpt5looseZ    < 9998. && abs(m_evt.pfcandid5looseZ) == 11 && m_evt.pfcandiso5looseZ < 0.2) return false;
    return true;
}

bool EwkinoSSAnalysisLooper::passesTauVeto()
{
    if(m_evt.pfTau_leadPtcandID != -999999) return false;
    return true;
}
bool EwkinoSSAnalysisLooper::passesMVAJetId(LorentzVector p4, float mva_value, int tightness)
{
    if (tightness < 0 || tightness > 2)
    {
        std::cout << "ERROR : tightness should be 0, 1, or 2. " << std::endl;
        return false;
    }

    float fMVACut[3][4][4];

    /*
    // working points from full_53x_wp defined in 
    // http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/CMG/CMGTools/External/python/JetIdParams_cfi.py?revision=1.12&view=markup

    //Tight Id
    fMVACut[0][0][0] = -0.83; fMVACut[0][0][1] = -0.81; fMVACut[0][0][2] = -0.74; fMVACut[0][0][3] = -0.81;
    fMVACut[0][1][0] = -0.83; fMVACut[0][1][1] = -0.81; fMVACut[0][1][2] = -0.74; fMVACut[0][1][3] = -0.81;
    fMVACut[0][2][0] = -0.38; fMVACut[0][2][1] = -0.32; fMVACut[0][2][2] = -0.14; fMVACut[0][2][3] = -0.48;
    fMVACut[0][3][0] = -0.38; fMVACut[0][3][1] = -0.32; fMVACut[0][3][2] = -0.14; fMVACut[0][3][3] = -0.48;
    //Medium id
    fMVACut[1][0][0] = -0.83; fMVACut[1][0][1] = -0.92; fMVACut[1][0][2] = -0.90; fMVACut[1][0][3] = -0.92;
    fMVACut[1][1][0] = -0.83; fMVACut[1][1][1] = -0.92; fMVACut[1][1][2] = -0.90; fMVACut[1][1][3] = -0.92;
    fMVACut[1][2][0] = -0.40; fMVACut[1][2][1] = -0.49; fMVACut[1][2][2] = -0.50; fMVACut[1][2][3] = -0.65;
    fMVACut[1][3][0] = -0.40; fMVACut[1][3][1] = -0.49; fMVACut[1][3][2] = -0.50; fMVACut[1][3][3] = -0.65;
    //Loose Id 
    fMVACut[2][0][0] = -0.95; fMVACut[2][0][1] = -0.96; fMVACut[2][0][2] = -0.94; fMVACut[2][0][3] = -0.95;
    fMVACut[2][1][0] = -0.95; fMVACut[2][1][1] = -0.96; fMVACut[2][1][2] = -0.94; fMVACut[2][1][3] = -0.95;
    fMVACut[2][2][0] = -0.80; fMVACut[2][2][1] = -0.74; fMVACut[2][2][2] = -0.68; fMVACut[2][2][3] = -0.77;
    fMVACut[2][3][0] = -0.80; fMVACut[2][3][1] = -0.74; fMVACut[2][3][2] = -0.68; fMVACut[2][3][3] = -0.77;
    */

    // working points from full_5x_wp defined in 
    // http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/CMG/CMGTools/External/python/JetIdParams_cfi.py?revision=1.12&view=markup
    //Tight Id                                                                                                                                                                       
    fMVACut[0][0][0] = -0.47; fMVACut[0][0][1] = -0.92; fMVACut[0][0][2] = -0.92; fMVACut[0][0][3] = -0.94;
    fMVACut[0][1][0] = -0.47; fMVACut[0][1][1] = -0.92; fMVACut[0][1][2] = -0.92; fMVACut[0][1][3] = -0.94;
    fMVACut[0][2][0] = +0.32; fMVACut[0][2][1] = -0.49; fMVACut[0][2][2] = -0.61; fMVACut[0][2][3] = -0.74;
    fMVACut[0][3][0] = +0.32; fMVACut[0][3][1] = -0.49; fMVACut[0][3][2] = -0.61; fMVACut[0][3][3] = -0.74;
    //Medium id
    fMVACut[1][0][0] = -0.83; fMVACut[1][0][1] = -0.96; fMVACut[1][0][2] = -0.95; fMVACut[1][0][3] = -0.96;
    fMVACut[1][1][0] = -0.83; fMVACut[1][1][1] = -0.96; fMVACut[1][1][2] = -0.95; fMVACut[1][1][3] = -0.96;
    fMVACut[1][2][0] = -0.40; fMVACut[1][2][1] = -0.74; fMVACut[1][2][2] = -0.76; fMVACut[1][2][3] = -0.81;
    fMVACut[1][3][0] = -0.40; fMVACut[1][3][1] = -0.74; fMVACut[1][3][2] = -0.76; fMVACut[1][3][3] = -0.81;
    //Loose Id 
    fMVACut[2][0][0] = -0.95; fMVACut[2][0][1] = -0.97; fMVACut[2][0][2] = -0.97; fMVACut[2][0][3] = -0.97;
    fMVACut[2][1][0] = -0.95; fMVACut[2][1][1] = -0.97; fMVACut[2][1][2] = -0.97; fMVACut[2][1][3] = -0.97;
    fMVACut[2][2][0] = -0.80; fMVACut[2][2][1] = -0.85; fMVACut[2][2][2] = -0.84; fMVACut[2][2][3] = -0.85;
    fMVACut[2][3][0] = -0.80; fMVACut[2][3][1] = -0.85; fMVACut[2][3][2] = -0.84; fMVACut[2][3][3] = -0.85;


    // pT categorization
    int ptId = 0;
    if (p4.pt() > 10 && p4.pt() < 20) ptId = 1;
    if (p4.pt() > 20 && p4.pt() < 30) ptId = 2;
    if (p4.pt() > 30                ) ptId = 3;

    // eta categorization
    int etaId = 0;
    if (fabs(p4.eta()) > 2.5  && fabs(p4.eta()) < 2.75) etaId = 1;
    if (fabs(p4.eta()) > 2.75 && fabs(p4.eta()) < 3.0 ) etaId = 2;
    if (fabs(p4.eta()) > 3.0  && fabs(p4.eta()) < 5.0 ) etaId = 3;

    // return  
    if (mva_value > fMVACut[tightness][ptId][etaId]) return true;
    return false;
}

std::vector<float> EwkinoSSAnalysisLooper::sortJetValues(const std::vector<bool>& all_jet_flags, const std::vector<LorentzVector>& all_jet_p4s, const std::vector<float>& vals_to_sort)
{
    assert(all_jet_flags.size() == all_jet_p4s.size());

    std::vector<std::pair<LorentzVector, float> > tmp_vec_p4_val;
    for (unsigned int idx = 0; idx < all_jet_flags.size(); idx++)
    {
        if (!all_jet_flags.at(idx)) continue;
        tmp_vec_p4_val.push_back(std::make_pair(all_jet_p4s.at(idx), vals_to_sort.at(idx)));
    }

    sort(tmp_vec_p4_val.begin(), tmp_vec_p4_val.end(), SortByPt());

    std::vector<float> ret;
    for (unsigned int idx = 0; idx < tmp_vec_p4_val.size(); idx++)
    {
        ret.push_back(tmp_vec_p4_val.at(idx).second);
    }

    return ret;
}
