#include "PlotLooper.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <tr1/array>
#include <cmath>
#include "mcSelections.h"
#include "SSB2012.h"
#include "rt/RootTools.h"
#include "rt/is_equal.h"
#include "at/Predicates.h"
#include "at/VtxReweight.h"
#include "at/DileptonHypType.h"
#include "at/DileptonChargeType.h"
#include "SignalRegion.h"
#include "electronSelections.h"
#include "TTbarBreakDown.h"
#include "ScaleFactors.h"
#include "at/PredSummary.h"
#include "at/FakeRatePrediction.h"
#include "at/FlipRatePrediction.h"
#include "SSB2012.h"
#include "CTable.h"
#include "TEfficiency.h"

typedef std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > vecLorentzVector;

using namespace std;
using namespace at;
using namespace ss;

// event list
fstream fout;

// construct:
PlotLooper::PlotLooper
(
    const std::string& root_file_name,
    Sample::value_type sample,
    SignalRegion::value_type signal_region,
    AnalysisType::value_type analysis_type,
    SignalRegionType::value_type signal_region_type,
    const std::string& vtxreweight_file_name,
    const std::string& fake_rate_file_name,
    const std::string& flip_rate_file_name,
    const std::string& event_list_name,
    const unsigned int num_btags,
    const unsigned int num_jets,
    const int charge_option,
    const bool do_scale_factors,
    const bool check_good_lumi,
    const bool do_3lep_veto,
    const bool do_truth_matching,
    const float sparm0,
    const float sparm1,
    const float sparm2,
    const float sparm3,
    const float sf_flip,
    const float fr_unc,
    const float fl_unc,
    const float mc_unc,
    const float lumi,
    //const float l1_min_pt,
    //const float l1_max_pt,
    //const float l2_min_pt,
    //const float l2_max_pt,
    const float min_ht,
    const bool verbose,
    const int FR_option
)
    : at::AnalysisWithHist(root_file_name)
    , m_lumi(lumi)
    , m_verbose(verbose)
    , m_FR_option(FR_option)
    , m_is_data(at::SampleIsData(sample))
    , m_do_vtx_reweight(not vtxreweight_file_name.empty())
    , m_do_scale_factors(do_scale_factors)
    , m_check_good_lumi(check_good_lumi)
    , m_do_3lep_veto(do_3lep_veto)
    , m_do_truth_matching(do_truth_matching)
    , m_nbtags(num_btags)
    , m_njets(num_jets)
    , m_charge_option(charge_option)
    , m_sparm0(sparm0)
    , m_sparm1(sparm1)
    , m_sparm2(sparm2)
    , m_sparm3(sparm3)
    , m_scale1fb(-999999.0)
    , m_xsec(-999999.0)
    , m_nevts(-999999)
    , m_sf_flip(sf_flip)
    , m_fr_unc(fr_unc)
    , m_fl_unc(fl_unc)
    , m_mc_unc(mc_unc)
    //, m_l1_min_pt(l1_min_pt)
    //, m_l1_max_pt(l1_max_pt)
    //, m_l2_min_pt(l2_min_pt)
    //, m_l2_max_pt(l2_max_pt)
    , m_min_ht(min_ht)
    , m_sample(sample)
    , m_signal_region(signal_region)
    , m_analysis_type(analysis_type)
    , m_signal_region_type(signal_region_type)
{
    // set vertex weight file
    if (m_do_vtx_reweight)
    {
        cout << "using vertex reweight file : " << vtxreweight_file_name << endl;
        set_vtxreweight_rootfile(vtxreweight_file_name.c_str(), m_verbose);
    }

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
        case AnalysisType::high_pt_eth:
            mufr_name = "h_mufr40c";
            elfr_name = "h_elfr40c";
            break;
        case AnalysisType::low_pt:
            mufr_name = "h_mufr40c_ewkcor";
            elfr_name = "h_elfr40c_noiso_ewkcor";
            break;
        case AnalysisType::vlow_pt:
            mufr_name = "h_mufr40c_iso_ewkcor";
            elfr_name = "h_elfr40c_noiso_ewkcor";
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
    cout<< " *** CAREFUL *** Using muon FR histogram also for electrons. Can't trust any electron plot"<<endl; // GZ
    elfr_name = mufr_name; //GZ

    h_mufr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get(mufr_name.c_str())->Clone()));
    h_elfr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get(elfr_name.c_str())->Clone()));
    if (not h_mufr) {throw std::runtime_error(Form("ERROR: PlotLooper: %s doesn't exist", mufr_name.c_str()));}
    if (not h_elfr) {throw std::runtime_error(Form("ERROR: PlotLooper: %s doesn't exist", elfr_name.c_str()));}
    h_mufr->SetDirectory(0);
    h_elfr->SetDirectory(0);

    cout << "using mu FR hist : " << h_mufr->GetName() << endl;
    cout << "using el FR hist : " << h_elfr->GetName() << endl;

    // set the flip rate histograms
    std::auto_ptr<TFile> flip_rate_file(rt::OpenRootFile(flip_rate_file_name));
    cout << "using FL file : " << flip_rate_file->GetName() << endl;
    h_flip.reset(dynamic_cast<TH2F*>(flip_rate_file->Get("flipRate")->Clone()));
    if (not h_flip) {throw std::runtime_error("ERROR: PlotLooper: flipRate doesn't exist");}
    h_flip->SetDirectory(0);

    // number of jets/btags
    cout << "Cutting on the number of jets/btags" << endl;
    cout << "nbtags >= " << m_nbtags << endl;
    cout << "njets  >= " << m_njets  << endl;

    // initialize counters
    for (size_t i = 0; i != m_count_ss.size(); i++) {m_count_ss[i]=0.0;}
    for (size_t i = 0; i != m_count_sf.size(); i++) {m_count_sf[i]=0.0;}
    for (size_t i = 0; i != m_count_df.size(); i++) {m_count_df[i]=0.0;}
    for (size_t i = 0; i != m_count_os.size(); i++) {m_count_os[i]=0.0;}

    // event list
    if (!event_list_name.empty())
    {
        fout.open(event_list_name.c_str(), fstream::out);
        if (not fout.is_open())
        {
            throw std::runtime_error(Form("ERROR: PlotLooper: %s cannot be opened", event_list_name.c_str()));
        }
        else
        {
            fout << "Run | LS | Event | channel | " 
                    "Lep1Pt | Lep1Eta | Lep1Phi | Lep1Iso | "
                    "Lep2Pt | Lep2Eta | Lep2Phi | Lep1Iso | "
                    "MET | HT | nJets | nbJets" << endl;
        }
    }

    // binning info for Fake/Flip rate
    m_fr_bin_info = GetFakeRateBinInfo();
    m_fl_bin_info = GetFlipRateBinInfo();

    // begin job
    BeginJob();
}

// destroy:
PlotLooper::~PlotLooper()
{
}
        
// methods:
void PlotLooper::BeginJob()
{
    // book the histograms
    BookHists();
}

void SetFakePredictionAndUncertainty(rt::TH1Container& hc, const string& hist_stem, const string& title, float fr_sys_unc)
{
    const string sf_name = Form("h_%s_sf"  , hist_stem.c_str());
    const string df_name = Form("h_%s_df"  , hist_stem.c_str());
    const string fk_name = Form("h_%s_fake", hist_stem.c_str());

    // fakes 
    hc.Add(dynamic_cast<TH1*>(hc[sf_name]->Clone(fk_name.c_str()))); 
    hc[fk_name]->Add(hc[df_name], -1.0);
    hc[fk_name]->SetTitle(title.c_str());
    rt::SetSystematicUncertainty(hc[fk_name], fr_sys_unc);
}

void SetFlipPredictionAndUncertainty(rt::TH1Container& hc, const string& hist_stem, const string& title, float fl_sys_unc, float fl_scale_factor = 1.0)
{
    const string os_name = Form("h_%s_os"  , hist_stem.c_str());
    const string fl_name = Form("h_%s_flip", hist_stem.c_str());

    // fakes 
    hc.Add(dynamic_cast<TH1*>(hc[os_name]->Clone(fl_name.c_str()))); 
    hc[fl_name]->Scale(fl_scale_factor);
    hc[fl_name]->SetTitle(title.c_str());
    rt::SetSystematicUncertainty(hc[fl_name], fl_sys_unc);
}

void SetMCPredictionAndUncertainty(rt::TH1Container& hc, const string& hist_stem, const string& title, float mc_sys_unc)
{
    const string ss_name = Form("h_%s_ss"  , hist_stem.c_str());

    // fakes 
    hc[ss_name]->SetTitle(title.c_str());
    rt::SetSystematicUncertainty(hc[ss_name], mc_sys_unc);
}

void SetPredictionAndUncertainty
(
    const at::Sample::value_type sample,
    rt::TH1Container& hc, 
    const std::string& hist_stem, 
    const std::string& title, 
    float fr_sys_unc, 
    float fl_sys_unc, 
    float mc_sys_unc, 
    float fl_scale_factor
)
{
    string fake_title = rt::string_replace_all(title, "(X)", "(fake)");
    string flip_title = rt::string_replace_all(title, "(X)", "(flip)");
    string mc_title   = rt::string_replace_all(title, "(X)", "(MC)"  );
    fake_title = rt::string_replace_all(title, "(X,", "(fake,");
    flip_title = rt::string_replace_all(title, "(X,", "(flip,");
    mc_title   = rt::string_replace_all(title, "(X,", "(MC,"  );
    SetFakePredictionAndUncertainty(hc, hist_stem, fake_title, fr_sys_unc);
    SetFlipPredictionAndUncertainty(hc, hist_stem, flip_title, fl_sys_unc, fl_scale_factor);
    if (sample != at::Sample::data)
    {
        SetMCPredictionAndUncertainty(hc, hist_stem, mc_title, mc_sys_unc);
    }
}


// end job
void PlotLooper::EndJob()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    if (m_verbose)
    {
        //hc.List();
    }
    cout << "\nScale1fb = "           << m_scale1fb << endl;
    cout << "Cross Section = "        << m_xsec     << endl;
    cout << "Num Events Generated = " << m_nevts    << endl;

    // set the error to the lumi * scale1fb * ClopperPearsonUncertainty
    if (m_sample != at::Sample::data && m_nevts > 0)
    {
        const float weight = (m_lumi * m_scale1fb);
        hc["h_yield_mm"]->SetBinError(2, weight * rt::GetClopperPearsonUncertainty(static_cast<int>(hc["h_yield_mm"]->GetEntries()), m_nevts));
        hc["h_yield_ee"]->SetBinError(2, weight * rt::GetClopperPearsonUncertainty(static_cast<int>(hc["h_yield_ee"]->GetEntries()), m_nevts));
        hc["h_yield_em"]->SetBinError(2, weight * rt::GetClopperPearsonUncertainty(static_cast<int>(hc["h_yield_em"]->GetEntries()), m_nevts));
        hc["h_yield_ll"]->SetBinError(2, weight * rt::GetClopperPearsonUncertainty(static_cast<int>(hc["h_yield_ll"]->GetEntries()), m_nevts));

        // yields in a signal used for overlaying
        hc["h_yield_ss"]->SetBinError(2, weight * rt::GetClopperPearsonUncertainty(static_cast<int>(hc["h_yield_ss"]->GetEntries()), m_nevts));
        hc["h_yield_ss"]->SetBinError(3, weight * rt::GetClopperPearsonUncertainty(static_cast<int>(hc["h_yield_ss"]->GetEntries()), m_nevts));
        hc["h_yield_ss"]->SetBinError(4, weight * rt::GetClopperPearsonUncertainty(static_cast<int>(hc["h_yield_ss"]->GetEntries()), m_nevts));
        hc["h_yield_ss"]->SetBinError(5, weight * rt::GetClopperPearsonUncertainty(static_cast<int>(hc["h_yield_ss"]->GetEntries()), m_nevts));
    }

    // 0 ee, 1 mm, 2 em, 3 ll
    //std::tr1::array<float, 4> yield_ss;
    //yield_ss[0] = rt::Integral(hc["h_yield_mm"]);
    //yield_ss[1] = rt::Integral(hc["h_yield_ee"]);
    //yield_ss[2] = rt::Integral(hc["h_yield_em"]);
    //yield_ss[3] = rt::Integral(hc["h_yield_ll"]);

    PredSummary yield;
    yield.mm.value = rt::IntegralAndError(hc["h_yield_mm"]).first;
    yield.ee.value = rt::IntegralAndError(hc["h_yield_ee"]).first;
    yield.em.value = rt::IntegralAndError(hc["h_yield_em"]).first;
    yield.ll.value = rt::IntegralAndError(hc["h_yield_ll"]).first;
    yield.mm.error = rt::IntegralAndError(hc["h_yield_mm"]).second;
    yield.ee.error = rt::IntegralAndError(hc["h_yield_ee"]).second;
    yield.em.error = rt::IntegralAndError(hc["h_yield_em"]).second;
    yield.ll.error = rt::IntegralAndError(hc["h_yield_ll"]).second;

    // Fake predictions
    // -----------------------------------------------------------------------------//
    at::FakeRatePrediction frp(h_mufr.get(), h_elfr.get());
    frp.ComputeAllFakePredictions
    (
        static_cast<TH2F*>(hc["h_sf_elfo_pt_vs_eta_ee"]),
        static_cast<TH2F*>(hc["h_sf_mufo_pt_vs_eta_mm"]),
        static_cast<TH2F*>(hc["h_sf_elfo_pt_vs_eta_em"]),
        static_cast<TH2F*>(hc["h_sf_mufo_pt_vs_eta_em"]),
        static_cast<TH2F*>(hc["h_df_fo_pt_vs_eta_ee"  ]),
        static_cast<TH2F*>(hc["h_df_fo_pt_vs_eta_mm"  ]),
        static_cast<TH2F*>(hc["h_df_fo_pt_vs_eta_em"  ])
    );

    // SF (raw)
    PredSummary sf_raw = frp.GetSingleFakePredictionRaw();
    hc.Add(new TH1F("h_sf_pred_raw", "SF prediction, raw", 6, 0, 6));
    hc["h_sf_pred_raw"]->SetBinContent(1, sf_raw.mm.value);
    hc["h_sf_pred_raw"]->SetBinContent(2, sf_raw.ee.value);
    hc["h_sf_pred_raw"]->SetBinContent(3, sf_raw.em.value);
    hc["h_sf_pred_raw"]->SetBinContent(4, sf_raw.ll.value);
    hc["h_sf_pred_raw"]->SetBinContent(5, sf_raw.em_mufo.value);
    hc["h_sf_pred_raw"]->SetBinContent(6, sf_raw.em_elfo.value);
    hc["h_sf_pred_raw"]->SetBinError(1, sf_raw.mm.error);
    hc["h_sf_pred_raw"]->SetBinError(2, sf_raw.ee.error);
    hc["h_sf_pred_raw"]->SetBinError(3, sf_raw.em.error);
    hc["h_sf_pred_raw"]->SetBinError(4, sf_raw.ll.error);
    hc["h_sf_pred_raw"]->SetBinError(5, sf_raw.em_mufo.error);
    hc["h_sf_pred_raw"]->SetBinError(6, sf_raw.em_elfo.error);

    // DF
    PredSummary df = frp.GetDoubleFakePrediction();
    hc.Add(new TH1F("h_df_pred", "DF prediction", 4, 0, 4));
    hc["h_df_pred"]->SetBinContent(1, df.mm.value);
    hc["h_df_pred"]->SetBinContent(2, df.ee.value);
    hc["h_df_pred"]->SetBinContent(3, df.em.value);
    hc["h_df_pred"]->SetBinContent(4, df.ll.value);
    hc["h_df_pred"]->SetBinError(1, df.mm.error);
    hc["h_df_pred"]->SetBinError(2, df.ee.error);
    hc["h_df_pred"]->SetBinError(3, df.em.error);
    hc["h_df_pred"]->SetBinError(4, df.ll.error);

    // SF 
    PredSummary sf = frp.GetSingleFakePrediction();
    hc.Add(new TH1F("h_sf_pred", "SF prediction", 4, 0, 4));
    hc["h_sf_pred"]->SetBinContent(1, sf.mm.value);
    hc["h_sf_pred"]->SetBinContent(2, sf.ee.value);
    hc["h_sf_pred"]->SetBinContent(3, sf.em.value);
    hc["h_sf_pred"]->SetBinContent(4, sf.ll.value);
    hc["h_sf_pred"]->SetBinError(1, sf.mm.error);
    hc["h_sf_pred"]->SetBinError(2, sf.ee.error);
    hc["h_sf_pred"]->SetBinError(3, sf.em.error);
    hc["h_sf_pred"]->SetBinError(4, sf.ll.error);

    // Fakes 
    PredSummary fake = frp.GetFakePrediction();
    hc.Add(new TH1F("h_fake_pred", "fake prediction", 4, 0, 4));
    hc["h_fake_pred"]->SetBinContent(1, fake.mm.value);
    hc["h_fake_pred"]->SetBinContent(2, fake.ee.value);
    hc["h_fake_pred"]->SetBinContent(3, fake.em.value);
    hc["h_fake_pred"]->SetBinContent(4, fake.ll.value);
    if (m_sample != at::Sample::data)
    {
        // if this is MC, then we are using it for signal contamination
        // 1. apply 50% uncertainty since this is MC 
        // 2. manually select error to maxed out at 100%
        fake.mm.error = (fake.mm.error < fake.mm.value ? sqrt(fake.mm.error*fake.mm.error + 0.25*fake.mm.value*fake.mm.value) : fake.mm.value);
        fake.ee.error = (fake.ee.error < fake.ee.value ? sqrt(fake.ee.error*fake.ee.error + 0.25*fake.ee.value*fake.ee.value) : fake.ee.value);
        fake.em.error = (fake.em.error < fake.em.value ? sqrt(fake.em.error*fake.em.error + 0.25*fake.em.value*fake.em.value) : fake.em.value);
        fake.ll.error = (fake.ll.error < fake.ll.value ? sqrt(fake.ll.error*fake.ll.error + 0.25*fake.ll.value*fake.ll.value) : fake.ll.value);
    }
    hc["h_fake_pred"]->SetBinError(1, fake.mm.error);
    hc["h_fake_pred"]->SetBinError(2, fake.ee.error);
    hc["h_fake_pred"]->SetBinError(3, fake.em.error);
    hc["h_fake_pred"]->SetBinError(4, fake.ll.error);

    // Flip predictions
    // -----------------------------------------------------------------------------//

    FlipRatePrediction flp(h_flip.get(), m_lumi);
    flp.ComputeAllFlipPredictions
    (
        static_cast<TH2F*>(hc["h_os_fo_pt_vs_eta_ee"]),
        static_cast<TH2F*>(hc["h_os_fo_pt_vs_eta_em"])
    );

    // Flip 
    PredSummary flip = flp.GetFlipPrediction(m_sf_flip);
    hc.Add(new TH1F("h_flip_pred", "flip prediction", 4, 0, 4));
    hc["h_flip_pred"]->SetBinContent(1, flip.mm.value);
    hc["h_flip_pred"]->SetBinContent(2, flip.ee.value);
    hc["h_flip_pred"]->SetBinContent(3, flip.em.value);
    hc["h_flip_pred"]->SetBinContent(4, flip.ll.value);
    hc["h_flip_pred"]->SetBinError(1, flip.mm.error);
    hc["h_flip_pred"]->SetBinError(2, flip.ee.error);
    hc["h_flip_pred"]->SetBinError(3, flip.em.error);
    hc["h_flip_pred"]->SetBinError(4, flip.ll.error);

    // SS kinematic plots (prediction and systematic uncertainty)
    // -----------------------------------------------------------------------------//

    // This is an approximation.
    // This does not have the full fake and flip rate errors' propogated properly.
    // This is a small effect and is ignored in the plots since they cannot be seen easily 
    // with the naked eye.
    SetPredictionAndUncertainty(m_sample, hc, "nvtxs"             ,"# vtxs (X); #vtxs;Events"                                             , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "dilep_mass"        ,"Dilepton Mass (X); M_{ll} (GeV);Events"                               , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "dilep_mass_nj0"    ,"Dilepton Mass (X, # jets=0); M_{ll} (GeV);Events"                     , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "dilep_mass_nj1"    ,"Dilepton Mass (X, # jets=1); M_{ll} (GeV);Events"                     , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "dilep_mass_nj2"    ,"Dilepton Mass (X, # jets#geq2); M_{ll} (GeV);Events"                  , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pt1"               ,"Higher p_{T} lepton (X);p_{T} (GeV);Events"                           , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pt2"               ,"Lower p_{T} lepton (X);p_{T} (GeV);Events"                            , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pt1_el"            ,"Higher p_{T} electron (X);p_{T} (GeV);Events"                         , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pt2_el"            ,"Lower p_{T} electron (X);p_{T} (GeV);Events"                          , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pt1_mu"            ,"Higher p_{T} electron (X);p_{T} (GeV);Events"                         , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pt2_mu"            ,"Lower p_{T} electron (X);p_{T} (GeV);Events"                          , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "ht"                ,"H_{T};H_{T} (GeV) (X);Events"                                         , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "mt"                ,"m_{T};m_{T} (GeV) (X);Events"                                         , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "met"               ,"MET;E_{T}^{miss} (GeV) (X);Events"                                    , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "nbtags"            ,"# btags;# btags (X);Events"                                           , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "njets"             ,"# jets (X);# jets;Events"                                             , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "lepdphi"           ,"#Delta#Phi(lep1,lep2) (X);Delta#Phi(lep1,lep2);Events"                , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "lepdeta"           ,"#Delta#eta(lep1,lep2) (X);Delta#eta(lep1,lep2);Events"                , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "lepdr"             ,"#DeltaR(lep1,lep2) (X);#DeltaR(lep1,lep2);Events"                     , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "drlepb"            ,"#DeltaR(lep,btag) (X);#DeltaR(lep,btag);Events"                       , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "btagdr"            ,"#DeltaR(btag1,btag2) (X);#DeltaR(btag1,btag2);Events"                 , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "drjetb"            ,"#DeltaR(btag,jet) (X);#DeltaR(btag,jet);Events"                       , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "ptjetlep"          ,"p_{T}^{jet}/p)_{T}^{lep} - 1 (X);p_{T}^{jet}/p)_{T}^{lep} - 1;Events" , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "drlep3rdlep"       ,"#DeltaR(lep, 3rd lep) (X);#DeltaR(lep,lep3);Events"                   , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "ml3l"              ,"M(lep, 3rd lep) (X);M(l,3l);Events"                                   , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pas_ht"            ,"H_{T};H_{T} (GeV);Events"                                             , 0.0, 0.0, 0.0, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pas_met"           ,"MET;E_{T}^{miss} (GeV);Events"                                        , 0.0, 0.0, 0.0, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pas_nbtags"        ,"# btags;# btags;Events"                                               , 0.0, 0.0, 0.0, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pas_njets"         ,"# jets;# jets;Events"                                                 , 0.0, 0.0, 0.0, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pas_pt1"           ,"Higher p_{T} lepton (X);p_{T} (GeV);Events"                           , 0.0, 0.0, 0.0, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pas_pt2"           ,"Lower p_{T} lepton (X);p_{T} (GeV);Events"                            , 0.0, 0.0, 0.0, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pas_htlow_ht"      ,"H_{T};H_{T} (GeV);Events"                                             , 0.0, 0.0, 0.0, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pas_htlow_met"     ,"MET;E_{T}^{miss} (GeV);Events"                                        , 0.0, 0.0, 0.0, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pas_htlow_nbtags"  ,"# btags;# btags;Events"                                               , 0.0, 0.0, 0.0, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pas_htlow_njets"   ,"# jets;# jets;Events"                                                 , 0.0, 0.0, 0.0, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pas_htlow_pt1"     ,"Higher p_{T} lepton (X);p_{T} (GeV);Events"                           , 0.0, 0.0, 0.0, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pas_htlow_pt2"     ,"Lower p_{T} lepton (X);p_{T} (GeV);Events"                            , 0.0, 0.0, 0.0, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pas_hthigh_ht"     ,"H_{T};H_{T} (GeV);Events"                                             , 0.0, 0.0, 0.0, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pas_hthigh_met"    ,"MET;E_{T}^{miss} (GeV);Events"                                        , 0.0, 0.0, 0.0, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pas_hthigh_nbtags" ,"# btags;# btags;Events"                                               , 0.0, 0.0, 0.0, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pas_hthigh_njets"  ,"# jets;# jets;Events"                                                 , 0.0, 0.0, 0.0, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pas_hthigh_pt1"    ,"Higher p_{T} lepton (X);p_{T} (GeV);Events"                           , 0.0, 0.0, 0.0, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pas_hthigh_pt2"    ,"Lower p_{T} lepton (X);p_{T} (GeV);Events"                            , 0.0, 0.0, 0.0, m_sf_flip);

    for (size_t i = 1; i != at::DileptonHypType::static_size; i++)
    {
        at::DileptonHypType::value_type hyp_type = static_cast<at::DileptonHypType::value_type>(i);

        // name and title suffixes
        string hn = Form("_%s" ,  GetDileptonHypTypeName(hyp_type).c_str());
        string ht = Form(" (%s)",  GetDileptonHypTypeTitle(hyp_type).c_str());

        SetPredictionAndUncertainty(m_sample, hc, "dilep_mass"+hn, Form("Dilepton Mass (X, %s); M_{ll} (GeV);Events"    ,ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
        SetPredictionAndUncertainty(m_sample, hc, "pt1"       +hn, Form("Higher p_{T} lepton (X, %s);p_{T} (GeV);Events",ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
        SetPredictionAndUncertainty(m_sample, hc, "pt2"       +hn, Form("Lower p_{T} lepton (X, %s);p_{T} (GeV);Events" ,ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
        SetPredictionAndUncertainty(m_sample, hc, "ht"        +hn, Form("H_{T};H_{T} (GeV) (X, %s);Events"              ,ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
        SetPredictionAndUncertainty(m_sample, hc, "mt"        +hn, Form("m_{T};m_{T} (GeV) (X, %s);Events"              ,ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
        SetPredictionAndUncertainty(m_sample, hc, "met"       +hn, Form("MET;E_{T}^{miss} (GeV) (X, %s);Events"         ,ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
        SetPredictionAndUncertainty(m_sample, hc, "nbtags"    +hn, Form("# btags;# btags (X, %s);Events"                ,ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
        SetPredictionAndUncertainty(m_sample, hc, "njets"     +hn, Form("# jets (X, %s);# jets;Events"                  ,ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);

        // plots for avi
        SetPredictionAndUncertainty(m_sample, hc, "dilep_mass_nj0"+hn,Form("Dilepton Mass (X, %s, # jets=0); M_{ll} (GeV);Events"   ,ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
        SetPredictionAndUncertainty(m_sample, hc, "dilep_mass_nj1"+hn,Form("Dilepton Mass (X, %s, # jets=1); M_{ll} (GeV);Events"   ,ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
        SetPredictionAndUncertainty(m_sample, hc, "dilep_mass_nj2"+hn,Form("Dilepton Mass (X, %s, # jets#geq2); M_{ll} (GeV);Events",ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    }

    // yield handled seperately
    // this uses the full Fake and Flip rate production from above

    // fakes 
    hc.Add(dynamic_cast<TH1*>(hc["h_yield_sf"]->Clone("h_yield_fake"))); 
    hc["h_yield_fake"]->SetTitle("fake prediction (with sys unc)");
    hc["h_yield_fake"]->SetBinContent(1, fake.mm.value);
    hc["h_yield_fake"]->SetBinContent(2, fake.ee.value);
    hc["h_yield_fake"]->SetBinContent(3, fake.em.value);
    hc["h_yield_fake"]->SetBinContent(4, fake.ll.value);
    hc["h_yield_fake"]->SetBinError  (1, sqrt(m_fr_unc*m_fr_unc*fake.mm.value*fake.mm.value + fake.mm.error*fake.mm.error));
    hc["h_yield_fake"]->SetBinError  (2, sqrt(m_fr_unc*m_fr_unc*fake.ee.value*fake.ee.value + fake.ee.error*fake.ee.error));
    hc["h_yield_fake"]->SetBinError  (3, sqrt(m_fr_unc*m_fr_unc*fake.em.value*fake.em.value + fake.em.error*fake.em.error));
    hc["h_yield_fake"]->SetBinError  (4, sqrt(m_fr_unc*m_fr_unc*fake.ll.value*fake.ll.value + fake.ll.error*fake.ll.error));

    // flips
    hc.Add(dynamic_cast<TH1*>(hc["h_yield_os"]->Clone("h_yield_flip"))); 
    hc["h_yield_flip"]->SetTitle("flip prediction (with sys unc)");
    hc["h_yield_flip"]->SetBinContent(1, flip.mm.value);
    hc["h_yield_flip"]->SetBinContent(2, flip.ee.value);
    hc["h_yield_flip"]->SetBinContent(3, flip.em.value);
    hc["h_yield_flip"]->SetBinContent(4, flip.ll.value);
    hc["h_yield_flip"]->SetBinError  (1, sqrt(m_fl_unc*m_fl_unc*flip.mm.value*flip.mm.value + flip.mm.error*flip.mm.error));
    hc["h_yield_flip"]->SetBinError  (2, sqrt(m_fl_unc*m_fl_unc*flip.ee.value*flip.ee.value + flip.ee.error*flip.ee.error));
    hc["h_yield_flip"]->SetBinError  (3, sqrt(m_fl_unc*m_fl_unc*flip.em.value*flip.em.value + flip.em.error*flip.em.error));
    hc["h_yield_flip"]->SetBinError  (4, sqrt(m_fl_unc*m_fl_unc*flip.ll.value*flip.ll.value + flip.ll.error*flip.ll.error));

    // mc (fold in the systematic uncertainty)
    if (m_sample != at::Sample::data)
    {
        SetMCPredictionAndUncertainty(hc, "yield", "yield (MC);yield;Events", m_mc_unc);
    }


    // print the output
    // -----------------------------------------------------------------------------//


    CTable t_yields;
    t_yields.useTitle();
    t_yields.setTitle("yields table");
    string f = "1.4";
    t_yields.setTable() (                       "mm",            "ee",            "em",               "ll")
                        ("SF raw" , sf_raw.mm.str(f), sf_raw.ee.str(f), sf_raw.em.str(f), sf_raw.ll.str(f))
                        ("SF"     ,     sf.mm.str(f),     sf.ee.str(f),     sf.em.str(f),     sf.ll.str(f))
                        ("DF"     ,     df.mm.str(f),     df.ee.str(f),     df.em.str(f),     df.ll.str(f))
                        ("Fakes"  ,   fake.mm.str(f),   fake.ee.str(f),   fake.em.str(f),   fake.ll.str(f))
                        ("Flips"  ,             "NA",   flip.ee.str(f),   flip.em.str(f),   flip.ll.str(f))
                        ("yield"  ,  yield.mm.str(f),  yield.ee.str(f),  yield.em.str(f),  yield.ll.str(f));
                        //("yield"  ,   yield.mm.value,   yield.ee.value,   yield.em.value,   yield.ll.value)
    cout << endl;
    t_yields.print();

    // print the output
    CTable t_em_breakdown;
    t_em_breakdown.useTitle();
    t_em_breakdown.setTitle("SF breakdown table");
    t_em_breakdown.setTable() (                                       "pred")
                              ("SF raw ee"           , sf_raw.ee.str(f)     )
                              ("SF raw mm"           , sf_raw.mm.str(f)     )
                              ("SF raw em"           , sf_raw.em.str(f)     )
                              ("SF raw em (mu fake)" , sf_raw.em_mufo.str(f))
                              ("SF raw em (el fake)" , sf_raw.em_elfo.str(f))
                              ("SF raw ll"           , sf_raw.ll.str(f)     );
    cout << endl;
    t_em_breakdown.print();


    // print raw yields
    CTable t_counts;
    t_counts.setTitle("counts for SS Analysis 2012");
    t_counts.useTitle();
    t_counts.setTable() (                      "mm",          "em",          "ee",         "all")
                           ("count ss" , m_count_ss[0], m_count_ss[1], m_count_ss[2], m_count_ss[3]) 
                           ("count sf" , m_count_sf[0], m_count_sf[1], m_count_sf[2], m_count_sf[3]) 
                           ("count df" , m_count_df[0], m_count_df[1], m_count_df[2], m_count_df[3])
                           ("count os" , m_count_os[0], m_count_os[1], m_count_os[2], m_count_os[3]); 
    cout << endl;
    t_counts.print();

    // close the event list file
    if (fout.is_open())
    {
        fout.close();   

        // sort it
    }
}

// book hists 
void PlotLooper::BookHists()
{
    try
    {
        // convenience alias
        rt::TH1Container& hc = m_hist_container;
        TH1::SetDefaultSumw2(true);

        hc.Add(new TH1F("h_lumi", "integrated lumi used for these plots (/fb)", 10000, 0, 100));

        // basic yield plots
        for (size_t i = 0; i != at::DileptonHypType::static_size; i++)
        {
            at::DileptonHypType::value_type hyp_type       = static_cast<at::DileptonHypType::value_type>(i);

            // name and title suffixes
            string ns = Form("_%s" ,  GetDileptonHypTypeName(hyp_type).c_str());
            string ts = Form(" (%s)",  GetDileptonHypTypeTitle(hyp_type).c_str());

            // yields
            hc.Add(new TH1F(Form("h_yield%s", ns.c_str()), Form("yields%s;yield;Events", ts.c_str()), 3, 0, 3));

            // SF plots
            hc.Add(new TH2F(Form("h_sf_mufo_pt_vs_eta%s", ns.c_str()), Form("#mu FO p_{T} vs |#eta|%s;|#eta|;p_{T} (GeV)"     , ts.c_str()),m_fr_bin_info.num_mu_eta_bins(),m_fr_bin_info.mu_eta_bins(),m_fr_bin_info.num_mu_pt_bins(),m_fr_bin_info.mu_pt_bins()));
            hc.Add(new TH2F(Form("h_sf_elfo_pt_vs_eta%s", ns.c_str()), Form("electron FO p_{T} vs |#eta|%s;|#eta|;p_{T} (GeV)", ts.c_str()),m_fr_bin_info.num_el_eta_bins(),m_fr_bin_info.el_eta_bins(),m_fr_bin_info.num_el_pt_bins(),m_fr_bin_info.el_pt_bins()));

            // DF plots
            unsigned int xdim = 0;
            unsigned int ydim = 0;
            if (hyp_type == at::DileptonHypType::MUMU) {xdim=m_fr_bin_info.num_mu_eta_bins()*m_fr_bin_info.num_mu_pt_bins(); ydim=xdim;}
            if (hyp_type == at::DileptonHypType::EE)   {xdim=m_fr_bin_info.num_el_eta_bins()*m_fr_bin_info.num_el_pt_bins(); ydim=xdim;}
            if (hyp_type == at::DileptonHypType::EMU)  {xdim=m_fr_bin_info.num_mu_eta_bins()*m_fr_bin_info.num_mu_pt_bins(); ydim=m_fr_bin_info.num_el_eta_bins()*m_fr_bin_info.num_el_pt_bins();}
            if (hyp_type == at::DileptonHypType::ALL)  {xdim=std::max(m_fr_bin_info.num_mu_eta_bins()*m_fr_bin_info.num_mu_pt_bins(),m_fr_bin_info.num_el_eta_bins()*m_fr_bin_info.num_el_pt_bins()); ydim=xdim;}
            hc.Add(new TH2F(Form("h_df_fo_pt_vs_eta%s", ns.c_str()), Form("DF FO p_{T} vs |#eta|%s;|#eta|;p_{T} (GeV)", ts.c_str()), xdim, 0, xdim, ydim, 0, ydim));
        }

        // OS plots (for flip pred)
        int num_double_flip_bins = (m_fl_bin_info.num_pt_bins()*m_fl_bin_info.num_eta_bins());
        hc.Add(new TH2F("h_os_fo_pt_vs_eta_ee", "OS (ee ) (special binning)"                    , num_double_flip_bins, 0, num_double_flip_bins, num_double_flip_bins, 0, num_double_flip_bins)); 
        hc.Add(new TH2F("h_os_fo_pt_vs_eta_em", "OS (e#mu) p_{T} vs |#eta|;|#eta|;p_{T} (GeV)"  , m_fl_bin_info.num_eta_bins(),m_fl_bin_info.eta_bins(),m_fl_bin_info.num_pt_bins(),m_fl_bin_info.pt_bins()));

        hc.Add(new TH2F("h_os_pt1_vs_eta1_mm", "OS (#mu#mu) #mu1 p_{T} vs |#eta|;|#eta|;p_{T} (GeV)", m_fl_bin_info.num_eta_bins(),m_fl_bin_info.eta_bins(),m_fl_bin_info.num_pt_bins(),m_fl_bin_info.pt_bins()));
        hc.Add(new TH2F("h_os_pt2_vs_eta2_mm", "OS (#mu#mu) #mu2 p_{T} vs |#eta|;|#eta|;p_{T} (GeV)", m_fl_bin_info.num_eta_bins(),m_fl_bin_info.eta_bins(),m_fl_bin_info.num_pt_bins(),m_fl_bin_info.pt_bins()));

        // kinematic plots
        for (size_t i = 0; i != at::DileptonChargeType::static_size; i++)
        {
            at::DileptonChargeType::value_type charge_type  = static_cast<at::DileptonChargeType::value_type>(i);

            // name and title suffixes
            string ns = Form("_%s"  ,  GetDileptonChargeTypeName(charge_type).c_str());
            string ts = Form(" (%s)",  GetDileptonChargeTypeTitle(charge_type).c_str());

            // yield plot
            hc.Add(new TH1F(Form("h_yield%s", ns.c_str()), Form("yields%s;yield;Events", ts.c_str()), 4, 0.5, 4.5));
            hc["h_yield"+ns]->GetXaxis()->SetBinLabel(1, "#mu#mu");
            hc["h_yield"+ns]->GetXaxis()->SetBinLabel(2, "ee"    );
            hc["h_yield"+ns]->GetXaxis()->SetBinLabel(3, "e#mu"  );
            hc["h_yield"+ns]->GetXaxis()->SetBinLabel(4, "ll"    );

            // SS kinematic plots
            hc.Add(new TH1F(Form("h_dilep_mass%s"    , ns.c_str()), Form("dilepton mass%s;mass (GeV);Events"                             , ts.c_str()), 125, 0   , 250 ));
            hc.Add(new TH1F(Form("h_dilep_mass_nj0%s", ns.c_str()), Form("dilepton mass%s;mass (GeV);Events"                             , ts.c_str()), 125, 0   , 250 ));
            hc.Add(new TH1F(Form("h_dilep_mass_nj1%s", ns.c_str()), Form("dilepton mass%s;mass (GeV);Events"                             , ts.c_str()), 125, 0   , 250 ));
            hc.Add(new TH1F(Form("h_dilep_mass_nj2%s", ns.c_str()), Form("dilepton mass%s;mass (GeV);Events"                             , ts.c_str()), 125, 0   , 250 ));
            hc.Add(new TH1F(Form("h_pt1%s"           , ns.c_str()), Form("Higher p_{T} lepton%s;p_{T} (GeV);Events"                      , ts.c_str()), 20 , 0   , 200 ));
            hc.Add(new TH1F(Form("h_pt2%s"           , ns.c_str()), Form("Lower p_{T} lepton%s;p_{T} (GeV);Events"                       , ts.c_str()), 20 , 0   , 200 ));
            hc.Add(new TH1F(Form("h_ht%s"            , ns.c_str()), Form("H_{T}%s;H_{T} (GeV);Events"                                    , ts.c_str()), 20 , 0   , 1000));
            hc.Add(new TH1F(Form("h_mt%s"            , ns.c_str()), Form("m_{T}%s;m_{T} (GeV);Events"                                    , ts.c_str()), 20 , 0   , 400 ));
            hc.Add(new TH1F(Form("h_met%s"           , ns.c_str()), Form("MET%s;E_{T}^{miss} (GeV);Events"                               , ts.c_str()), 20 , 0   , 400 ));
            hc.Add(new TH1F(Form("h_nbtags%s"        , ns.c_str()), Form("# btags%s;# btags;Events"                                      , ts.c_str()), 7  , -0.5, 6.5 ));
            hc.Add(new TH1F(Form("h_njets%s"         , ns.c_str()), Form("# jets%s;# jets;Events"                                        , ts.c_str()), 10 , -0.5, 9.5 ));
            hc.Add(new TH1F(Form("h_lepdphi%s"       , ns.c_str()), Form("#Delta#Phi(lep1, lep2)%s;#Delta#Phi(lep1, lep2);Events"        , ts.c_str()), 32 , 0   , 3.2 ));
            hc.Add(new TH1F(Form("h_lepdeta%s"       , ns.c_str()), Form("#Delta#eta(lep1, lep2)%s;#Delta#eta(lep1, lep2);Events"        , ts.c_str()), 25 , -2.5, 2.5 ));
            hc.Add(new TH1F(Form("h_lepdr%s"         , ns.c_str()), Form("#DeltaR(lep1, lep2)%s;#DeltaR(lep1, lep2);Events"              , ts.c_str()), 40 , 0   , 4.  ));
            hc.Add(new TH1F(Form("h_drlepb%s"        , ns.c_str()), Form("#DeltaR(lep, btag)%s;#DeltaR(lep, btag);Events"                , ts.c_str()), 40 , 0   , 4.  ));
            hc.Add(new TH1F(Form("h_btagdr%s"        , ns.c_str()), Form("#DeltaR(btag1, btag2)%s;#DeltaR(btag1, btag2);Events"          , ts.c_str()), 40 , 0   , 4.  ));
            hc.Add(new TH1F(Form("h_drjetb%s"        , ns.c_str()), Form("#DeltaR(btag, jet)%s;#DeltaR(btag, jet);Events"                , ts.c_str()), 40 , 0   , 4.  ));
            hc.Add(new TH1F(Form("h_ml3l%s"          , ns.c_str()), Form("M(lep,3rd lep)%s;M(l,3l);Events"                               , ts.c_str()), 10 , 0.  , 50. ));
            hc.Add(new TH1F(Form("h_drlep3rdlep%s"   , ns.c_str()), Form("#DeltaR(lep, lep3)%s:#DeltaR(lep, 3rd lep);Events"             , ts.c_str()), 40 , 0   , 4.  ));
            hc.Add(new TH1F(Form("h_ptjetlep%s"      , ns.c_str()), Form("jet p_{T} / lep p_{T} - 1%s;p_{T}^{jet}/p_{T}^{lep} - 1;Events", ts.c_str()), 50 , 0.  , 5.0 ));
            hc.Add(new TH1F(Form("h_nvtxs%s"         , ns.c_str()), Form("# vtxs%s; #vtxs;Events"                                        , ts.c_str()), 20 , 0   , 40  ));
            hc.Add(new TH1F(Form("h_pt1_el%s"        , ns.c_str()), Form("Higher p_{T} electron%s;p_{T} (GeV);Events"                    , ts.c_str()), 20 , 0   , 200 ));
            hc.Add(new TH1F(Form("h_pt2_el%s"        , ns.c_str()), Form("Lower p_{T} electron%s;p_{T} (GeV);Events"                     , ts.c_str()), 20 , 0   , 200 ));
            hc.Add(new TH1F(Form("h_pt1_mu%s"        , ns.c_str()), Form("Higher p_{T} muons%s;p_{T} (GeV);Events"                       , ts.c_str()), 20 , 0   , 200 ));
            hc.Add(new TH1F(Form("h_pt2_mu%s"        , ns.c_str()), Form("Lower p_{T} muons%s;p_{T} (GeV);Events"                        , ts.c_str()), 20 , 0   , 200 ));

            // plots for the PAS
            hc.Add(new TH1F(Form("h_pas_ht%s"     , ns.c_str()), Form("H_{T}%s;H_{T} (GeV);Events"              , ts.c_str()), 13 , 80.0 , 600.0));
            hc.Add(new TH1F(Form("h_pas_met%s"    , ns.c_str()), Form("MET%s;E_{T}^{miss} (GeV);Events"         , ts.c_str()), 10 , 0.0  , 250.0));
            hc.Add(new TH1F(Form("h_pas_njets%s"  , ns.c_str()), Form("# jets%s;# jets;Events"                  , ts.c_str()), 7  , 2.0  , 9.0  ));
            hc.Add(new TH1F(Form("h_pas_nbtags%s" , ns.c_str()), Form("# btags%s;# btags;Events"                , ts.c_str()), 5  , 0.0  , 5.0  ));
            hc.Add(new TH1F(Form("h_pas_pt1%s"    , ns.c_str()), Form("Higher p_{T} lepton%s;p_{T} (GeV);Events", ts.c_str()), 20 , 0.0  , 200.0));
            hc.Add(new TH1F(Form("h_pas_pt2%s"    , ns.c_str()), Form("Lower p_{T} lepton%s;p_{T} (GeV);Events" , ts.c_str()), 10 , 0.0  , 100.0));

            hc.Add(new TH1F(Form("h_pas_htlow_ht%s"     , ns.c_str()), Form("H_{T}%s (H_{T} < 200 GeV);H_{T} (GeV);Events"              , ts.c_str()), 13 , 80.0 , 600.0));
            hc.Add(new TH1F(Form("h_pas_htlow_met%s"    , ns.c_str()), Form("MET%s (H_{T} < 200 GeV);E_{T}^{miss} (GeV);Events"         , ts.c_str()), 10 , 0.0  , 250.0));
            hc.Add(new TH1F(Form("h_pas_htlow_njets%s"  , ns.c_str()), Form("# jets%s (H_{T} < 200 GeV);# jets;Events"                  , ts.c_str()), 7  , 2.0  , 9.0  ));
            hc.Add(new TH1F(Form("h_pas_htlow_nbtags%s" , ns.c_str()), Form("# btags%s (H_{T} < 200 GeV);# btags;Events"                , ts.c_str()), 5  , 0.0  , 5.0  ));
            hc.Add(new TH1F(Form("h_pas_htlow_pt1%s"    , ns.c_str()), Form("Higher p_{T} lepton%s (H_{T} < 200 GeV);p_{T} (GeV);Events", ts.c_str()), 20 , 0.0  , 200.0));
            hc.Add(new TH1F(Form("h_pas_htlow_pt2%s"    , ns.c_str()), Form("Lower p_{T} lepton%s (H_{T} < 200 GeV);p_{T} (GeV);Events" , ts.c_str()), 10 , 0.0  , 100.0));

            hc.Add(new TH1F(Form("h_pas_hthigh_ht%s"    , ns.c_str()), Form("H_{T}%s (H_{T} > 200 GeV);H_{T} (GeV);Events"              , ts.c_str()), 13 , 80.0 , 600.0));
            hc.Add(new TH1F(Form("h_pas_hthigh_met%s"   , ns.c_str()), Form("MET%s (H_{T} > 200 GeV);E_{T}^{miss} (GeV);Events"         , ts.c_str()), 10 , 0.0  , 250.0));
            hc.Add(new TH1F(Form("h_pas_hthigh_njets%s" , ns.c_str()), Form("# jets%s (H_{T} > 200 GeV);# jets;Events"                  , ts.c_str()), 7  , 2.0  , 9.0  ));
            hc.Add(new TH1F(Form("h_pas_hthigh_nbtags%s", ns.c_str()), Form("# btags%s (H_{T} > 200 GeV);# btags;Events"                , ts.c_str()), 5  , 0.0  , 5.0  ));
            hc.Add(new TH1F(Form("h_pas_hthigh_pt1%s"   , ns.c_str()), Form("Higher p_{T} lepton%s (H_{T} > 200 GeV);p_{T} (GeV);Events", ts.c_str()), 20 , 0.0  , 200.0));
            hc.Add(new TH1F(Form("h_pas_hthigh_pt2%s"   , ns.c_str()), Form("Lower p_{T} lepton%s (H_{T} > 200 GeV);p_{T} (GeV);Events" , ts.c_str()), 10 , 0.0  , 100.0));

            for (size_t i = 1; i != at::DileptonHypType::static_size; i++)
            {
                at::DileptonHypType::value_type hyp_type = static_cast<at::DileptonHypType::value_type>(i);

                // name and title suffixes
                string hn = Form("_%s" ,  GetDileptonHypTypeName(hyp_type).c_str());
                string ht = Form(" (%s)",  GetDileptonHypTypeTitle(hyp_type).c_str());

                hc.Add(new TH1F(Form("h_dilep_mass%s%s"    , hn.c_str(), ns.c_str()), Form("dilepton mass%s%s;mass (GeV);Events"       , ts.c_str(), ht.c_str()), 125, 0   , 250 ));
                hc.Add(new TH1F(Form("h_dilep_mass_nj0%s%s", hn.c_str(), ns.c_str()), Form("dilepton mass%s%s;mass (GeV);Events"       , ts.c_str(), ht.c_str()), 125, 0   , 250 ));
                hc.Add(new TH1F(Form("h_dilep_mass_nj1%s%s", hn.c_str(), ns.c_str()), Form("dilepton mass%s%s;mass (GeV);Events"       , ts.c_str(), ht.c_str()), 125, 0   , 250 ));
                hc.Add(new TH1F(Form("h_dilep_mass_nj2%s%s", hn.c_str(), ns.c_str()), Form("dilepton mass%s%s;mass (GeV);Events"       , ts.c_str(), ht.c_str()), 125, 0   , 250 ));
                hc.Add(new TH1F(Form("h_pt1%s%s"           , hn.c_str(), ns.c_str()), Form("Higher p_{T} lepton%s%s;p_{T} (GeV);Events", ts.c_str(), ht.c_str()), 20 , 0   , 200 ));
                hc.Add(new TH1F(Form("h_pt2%s%s"           , hn.c_str(), ns.c_str()), Form("Lower p_{T} lepton%s%s;p_{T} (GeV);Events" , ts.c_str(), ht.c_str()), 20 , 0   , 200 ));
                hc.Add(new TH1F(Form("h_ht%s%s"            , hn.c_str(), ns.c_str()), Form("H_{T}%s%s;H_{T} (GeV);Events"              , ts.c_str(), ht.c_str()), 20 , 0   , 1000));
                hc.Add(new TH1F(Form("h_mt%s%s"            , hn.c_str(), ns.c_str()), Form("m_{T}%s%s;m_{T} (GeV);Events"              , ts.c_str(), ht.c_str()), 20 , 0   , 400 ));
                hc.Add(new TH1F(Form("h_met%s%s"           , hn.c_str(), ns.c_str()), Form("MET%s%s;E_{T}^{miss} (GeV);Events"         , ts.c_str(), ht.c_str()), 20 , 0   , 400 ));
                hc.Add(new TH1F(Form("h_nbtags%s%s"        , hn.c_str(), ns.c_str()), Form("# btags%s%s;# btags;Events"                , ts.c_str(), ht.c_str()), 7  , -0.5, 6.5 ));
                hc.Add(new TH1F(Form("h_njets%s%s"         , hn.c_str(), ns.c_str()), Form("# jets%s%s;# jets;Events"                  , ts.c_str(), ht.c_str()), 10 , -0.5, 9.5 ));
            }
        }
            
        return;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }
}

// main analysis function operator 
int PlotLooper::operator()(long event)
{
    using namespace std;
    using namespace ssb;

    try
    {
        // base analysis
        at::AnalysisWithHist::operator()(event);

        // convenience alias
        rt::TH1Container& hc = m_hist_container;

        hc["h_lumi"]->Fill(m_lumi);

        // selections 
        // ---------------------------------------------------------------------------------------------------------------------------- //

        // only keep good lumi (data only) -- is_good_lumi branch not set
        if (m_check_good_lumi && is_real_data() && not is_good_lumi())
        {
            if (m_verbose) {cout << "failing good run list" << endl;}
            return 0;
        }

        // only keep MC matched events (MC only)
        const bool true_ss_event = not is_real_data() ? ((lep1_is_fromw()==1) && (lep2_is_fromw()==1) && (lep1_mc3id()*lep2_mc3id()>0)) : false;
        const bool not_from_borc = not is_real_data() ? ((lep1_is_fromw()>=0) && (lep2_is_fromw()>=0) && (lep1_mc3id()*lep2_mc3id()>0)) : false;
        const bool is_rare_mc    = (at::GetSampleInfo(m_sample).type == at::SampleType::rare);
        const bool is_signal_mc  = (at::GetSampleInfo(m_sample).type == at::SampleType::susy);
        const bool is_mc_matched = (m_sample==at::Sample::ttg ? not_from_borc : true_ss_event);
        if (m_do_truth_matching)
        {
            if ((not is_real_data()) && (not is_mc_matched) && (is_rare_mc || is_signal_mc))
            {
                if (m_verbose) {cout << "failing MC truth matching" << endl;}
                return 0;
            }
        }

	// GZ: modify num and denom definition
	// change is_ss() to is_ss_mod, etc
	bool is_ss_mod = is_ss();
	bool is_sf_mod = is_sf();
	bool is_df_mod = is_df();
	bool is_os_mod = is_os();
	if (m_FR_option == 1 && abs(lep1_pdgid())==13 && abs(lep2_pdgid())==13) {  // Use absolute isolation 2 GeV in numerator (muon only)
	  if (is_ss_mod && (lep1_corpfiso()*lep1_p4().pt() > 2 || lep2_corpfiso()*lep2_p4().pt() > 2 ) ) {is_ss_mod=false; is_sf_mod=true;} // downgrade from SS to SF
	  if (is_sf_mod && (lep1_corpfiso()*lep1_p4().pt() > 2 && lep2_corpfiso()*lep2_p4().pt() > 2 ) ) {is_sf_mod=false; is_df_mod=true;} // downgrade from SF to DF
	  if (is_os_mod && (lep1_corpfiso()*lep1_p4().pt() > 2 || lep2_corpfiso()*lep2_p4().pt() > 2 ) ) {is_os_mod=false; }
	}
	if (m_FR_option == 2 && abs(lep1_pdgid())==13 && abs(lep2_pdgid())==13) {  // Require ID cuts in FO selection (muon only)
	  if ( (is_sf_mod || is_df_mod) && (!lep1_passes_id() || !lep2_passes_id()) ) {is_sf_mod=false; is_df_mod=false;} // remove event from FO
	}
	if (m_FR_option == 3 && abs(lep1_pdgid())==13 && abs(lep2_pdgid())==13) {  // Require ID cuts in FO selection AND abs iso in numerator (muon only)
	  if (is_ss_mod && (lep1_corpfiso()*lep1_p4().pt() > 2 || lep2_corpfiso()*lep2_p4().pt() > 2 ) ) {is_ss_mod=false; is_sf_mod=true;} 
	  if (is_sf_mod && (lep1_corpfiso()*lep1_p4().pt() > 2 && lep2_corpfiso()*lep2_p4().pt() > 2 ) ) {is_sf_mod=false; is_df_mod=true;}
	  if (is_os_mod && (lep1_corpfiso()*lep1_p4().pt() > 2 || lep2_corpfiso()*lep2_p4().pt() > 2 ) ) {is_os_mod=false; }
	  if ( (is_sf_mod || is_df_mod) && (!lep1_passes_id() || !lep2_passes_id()) ) {is_sf_mod=false; is_df_mod=false;}
	}


        // charge type
        DileptonChargeType::value_type charge_type = DileptonChargeType::static_size;
        if (is_ss_mod) {charge_type = DileptonChargeType::SS;}
        if (is_sf_mod) {charge_type = DileptonChargeType::SF;}
        if (is_df_mod) {charge_type = DileptonChargeType::DF;}
        if (is_os_mod) {charge_type = DileptonChargeType::OS;}
        if (ssb::charge_type() < 0)
        {
            if (m_verbose) {cout << "failing valid hypothesis requirement" << endl;}
            return 0;
        }
        //if (charge_type == DileptonChargeType::static_size)
        //{
        //    if (m_verbose) {cout << "failing valid charge type" << endl;}
        //    return 0;
        //}

        // dilepton hyp type: 1 mm, 2 em, 3ee
        const DileptonHypType::value_type hyp_type = static_cast<DileptonHypType::value_type>(dilep_type());
        if (hyp_type == DileptonHypType::static_size)
        {
            if (m_verbose) {cout << "failing valid hyp type" << endl;}
            return 0;
        }

        // lepton PT requirement
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
        if (lep1_p4().pt() < (abs(lep1_pdgid()==11) ? el_min_pt : mu_min_pt))
        {
            if (m_verbose) {cout << "failing minimum lep1 pT" << endl;}
            return 0;
        }
        if (lep2_p4().pt() < (abs(lep2_pdgid()==11) ? el_min_pt : mu_min_pt))
        {
            if (m_verbose) {cout << "failing minimum lep2 pT" << endl;}
            return 0;
        }

        // third lepton veto
        if (m_do_3lep_veto)
        {
            if (not passes_3lep_veto())
            {
                if (m_verbose) {cout << "failing 3rd lepton veto" << endl;}
                return 0;
            }
        }

        // HT cut
        if (ht() < m_min_ht)
        {
            if (m_verbose) {cout << Form("failing minimum hT: %f < %f", ht(), m_min_ht) << endl;}
            return 0;
        }

        // charge option (1 == ++, -1 == --)
        switch (m_charge_option)
        {
            case  1: if (not is_pp()) return 0; break;
            case -1: if (not is_mm()) return 0; break;
            default: {/*do nothing*/}
        }

        // check that it passes the trigger requirement
        if (is_real_data())
        {
            bool passes_trigger = true;
            switch (hyp_type)
            {
                case DileptonHypType::MUMU: passes_trigger = trig_mm(); break;
                case DileptonHypType::EMU : passes_trigger = trig_em(); break;
                case DileptonHypType::EE  : passes_trigger = trig_ee(); break;
                default: passes_trigger = false; break;
            };
            // return if fails trigger
            if (not passes_trigger)
            {
                if (m_verbose) {cout << "failing trigger requirement" << endl;}
                return 0;
            }
        }

        // two jet events
        if (njets() < static_cast<int>(m_njets))
        {
            if (m_verbose) {cout << "failing # jets cut" << endl;}
            return 0;
        }

        // two btagged jets
        const unsigned int num_btags = ((not is_real_data() && m_do_scale_factors) ? nbtags_reweighted() : nbtags());
        if (num_btags < m_nbtags)
        {
            if (m_verbose) {cout << "failing # btags cut" << endl;}
            return 0;
        }

        // passes signal region
        if (not PassesSignalRegion(m_signal_region, m_analysis_type, m_signal_region_type, m_do_scale_factors))
        {
            if (m_verbose) {cout << "failing signal region cut" << endl;}
            return 0;
        }

        // if the value of m_m_sparm0 negative, this check is skipped
        if (m_sparm0 >= 0.0f && not rt::is_equal(m_sparm0, sparm0()))
        {
            if (m_verbose) {cout << Form("fails the sparm0 check: %s, %1.2f != %1.2f", sparm0_name().Data(), m_sparm0, sparm0()) << endl;}
            return 0;
        }

        // if the value of m_sparm1 is negative, this check is skipped
        if (m_sparm1 >= 0.0f && not rt::is_equal(m_sparm1, sparm1()))
        {
            if (m_verbose) {cout << Form("fails the sparm1 check: %s, %1.2f != %1.2f", sparm1_name().Data(), m_sparm1, sparm1()) << endl;}
            return 0;
        }

        // if the value of m_sparm2 is negative, this check is skipped
        if (m_sparm2 >= 0.0f && not rt::is_equal(m_sparm2, sparm2()))
        {
            if (m_verbose) {cout << Form("fails the sparm2 check: %s, %1.2f != %1.2f", sparm2_name().Data(), m_sparm2, sparm2()) << endl;}
            return 0;
        }

        // if the value of m_sparm3 is negative, this check is skipped
        if (m_sparm3 >= 0.0f && not rt::is_equal(m_sparm3, sparm3()))
        {
            if (m_verbose) {cout << Form("fails the sparm3 check: %s, %1.2f != %1.2f", sparm3_name().Data(), m_sparm3, sparm3()) << endl;}
            return 0;
        }

        // scale 1b (set before cuts) 
        m_scale1fb = (is_real_data() ? 1.0 : scale1fb());
        // fix to wgstar's scale1fb
        if (m_sample == Sample::wgstar2m) {m_scale1fb = 0.00638;}
        if (m_sample == Sample::wgstar2t) {m_scale1fb = 0.00672;}
        m_xsec     = xsec();
        m_nevts    = static_cast<int>((xsec()*1000)/scale1fb());

        // ttbar breakdown 
        switch (m_sample)
        {
            //case at::Sample::ttdil: if (ttbar_bkdn() != TTbarBreakDown::TTDIL) result = false; break; 
            //case at::Sample::ttotr: if (ttbar_bkdn() != TTbarBreakDown::TTOTR) result = false; break;
            //case at::Sample::ttslb: if (ttbar_bkdn() != TTbarBreakDown::TTSLB) result = false; break;
            //case at::Sample::ttslo: if (ttbar_bkdn() != TTbarBreakDown::TTSLO) result = false; break;
            case at::Sample::ttdil:
                if (GetTTbarBreakDown(m_sample, lep1_is_fromw(), lep2_is_fromw()) != TTbarBreakDown::TTDIL)
                {
                    if (m_verbose) {cout << "failing ttbar breakdown requirement" << endl;} 
                    return 0;
                }
                break; 
            case at::Sample::ttotr: 
                if (GetTTbarBreakDown(m_sample, lep1_is_fromw(), lep2_is_fromw()) != TTbarBreakDown::TTOTR)
                {
                    if (m_verbose) {cout << "failing ttbar breakdown requirement" << endl;} 
                    return 0;
                }
                break; 
            case at::Sample::ttslb:
                if (GetTTbarBreakDown(m_sample, lep1_is_fromw(), lep2_is_fromw()) != TTbarBreakDown::TTSLB)
                {
                    if (m_verbose) {cout << "failing ttbar breakdown requirement" << endl;} 
                    return 0;
                }
                break; 
            case at::Sample::ttslo: 
                if (GetTTbarBreakDown(m_sample, lep1_is_fromw(), lep2_is_fromw()) != TTbarBreakDown::TTSLO)
                {
                    if (m_verbose) {cout << "failing ttbar breakdown requirement" << endl;} 
                    return 0;
                }
                break; 
            default: {/*do nothing*/}
        }
        

        // count events
        if (dilep_type()==DileptonHypType::MUMU)
        {
            if(is_ss_mod) m_count_ss[0] += 1.0;
            if(is_sf_mod) m_count_sf[0] += 1.0;
            if(is_df_mod) m_count_df[0] += 1.0;
            if(is_os_mod) m_count_os[0] += 1.0;
        }
        else if (dilep_type()==DileptonHypType::EMU)
        {
            if(is_ss_mod) m_count_ss[1] += 1.0;
            if(is_sf_mod) m_count_sf[1] += 1.0;
            if(is_df_mod) m_count_df[1] += 1.0;
            if(is_os_mod) m_count_os[1] += 1.0;
        }
        else if (dilep_type()==DileptonHypType::EE)
        {
            if(is_ss_mod) m_count_ss[2] += 1.0;
            if(is_sf_mod) m_count_sf[2] += 1.0;
            if(is_df_mod) m_count_df[2] += 1.0;
            if(is_os_mod) m_count_os[2] += 1.0;
        }
        // count all 
        {
            if(is_ss_mod) m_count_ss[3] += 1.0;
            if(is_sf_mod) m_count_sf[3] += 1.0;
            if(is_df_mod) m_count_df[3] += 1.0;
            if(is_os_mod) m_count_os[3] += 1.0;
        }

        // Weight Factors
        // ----------------------------------------------------------------------------------------------------------------------------//

        // xsec and luminosity scale factors
        float evt_weight = is_real_data() ? 1.0 : m_lumi * m_scale1fb;

        // apply scale factors
        if (m_do_scale_factors && not is_real_data())
        {
            // lepton efficiencies
            const float eta1 = (abs(lep1_pdgid()) == 13 ? lep1_p4().eta() : lep1_sc_p4().eta());
            const float eta2 = (abs(lep2_pdgid()) == 13 ? lep2_p4().eta() : lep2_sc_p4().eta());
            evt_weight *= DileptonTagAndProbeScaleFactor(lep1_pdgid(), lep1_p4().pt(), eta1, lep2_pdgid(), lep2_p4().pt(), eta2);

            // trigger scale factor
            evt_weight *= DileptonTriggerScaleFactor(hyp_type, m_analysis_type, lep2_p4());  
        }

        // Fill hists
        // ------------------------------------------------------------------------------------//

        // name and title suffixes
        string hs = Form("_%s", GetDileptonHypTypeName(hyp_type).c_str());
        string qs = Form("_%s", GetDileptonChargeTypeName(charge_type).c_str());

        // SS
        if (is_ss_mod)
        {
            rt::Fill(hc["h_yield_ll"], 1, evt_weight);
            rt::Fill(hc["h_yield"+hs], 1, evt_weight);

            if (fout.is_open())
            {
                string channel;
                switch (hyp_type)
                {
                    case DileptonHypType::MUMU : channel = "MuMu"; break;
                    case DileptonHypType::EMU  : channel = "EMu" ; break;
                    case DileptonHypType::EE   : channel = "EE"  ; break;
                    default                    : channel = "none"; 
                }
                channel.append(":");
                //fout << Form("%-6s %-7u %-5u %-15u %-2u %-2u %-6.3f %-6.3f", channel.c_str(), run(), ls(), evt(), njets(), nbtags(), ht(), pfmet()) << endl;
                fout << Form("%6u | %3u | %12u | %s | %4.3f | %2.3f | %2.3f | %4.3f | %4.3f | %2.3f | %2.3f | %4.3f | %4.3f | %4.3f | %u | %u",
                     run(), ls(), evt(),
                     channel.c_str(),
                     lep1_p4().pt(), lep1_p4().eta(), lep1_p4().phi(), lep1_corpfiso(),
                     lep2_p4().pt(), lep2_p4().eta(), lep2_p4().phi(), lep2_corpfiso(),
                     pfmet(),
                     ht(),
                     njets(),
                     num_btags) << endl;
            }
        }

        // SF 
        if (is_sf_mod)
        {
            const LorentzVector& p4  = lep1_is_fo() ? lep1_p4()    : lep2_p4();
            const int id             = lep1_is_fo() ? lep1_pdgid() : lep2_pdgid();
            if (is_real_data() || (!is_real_data() && is_mc_matched))
            {
                if (abs(id)==13) {rt::Fill2D(hc["h_sf_mufo_pt_vs_eta"+ hs], fabs(p4.eta()), p4.pt(), evt_weight);}
                if (abs(id)==11) {rt::Fill2D(hc["h_sf_elfo_pt_vs_eta"+ hs], fabs(p4.eta()), p4.pt(), evt_weight);}
            }
        }

        // DF 
        if (is_df_mod)
        {
            const LorentzVector& l1_p4 = lep1_p4();
            const LorentzVector& l2_p4 = lep2_p4();
            const int l1_id            = lep1_pdgid();
            const int l2_id            = lep2_pdgid();
            if (is_real_data() || (!is_real_data() && is_mc_matched))
            {
                at::FillDoubleFakeHist(*dynamic_cast<TH2F*>(hc["h_df_fo_pt_vs_eta_ll"]), *h_mufr, *h_elfr, hyp_type, l1_id, l1_p4.pt(), l1_p4.eta(), l2_id, l2_p4.pt(), l2_p4.eta(), evt_weight);
                at::FillDoubleFakeHist(*dynamic_cast<TH2F*>(hc["h_df_fo_pt_vs_eta"+hs]), *h_mufr, *h_elfr, hyp_type, l1_id, l1_p4.pt(), l1_p4.eta(), l2_id, l2_p4.pt(), l2_p4.eta(), evt_weight);
            }
        }

        // OS
        if (is_os_mod)
        {

            const LorentzVector& l1_p4 = lep1_p4();
            const LorentzVector& l2_p4 = lep2_p4();
            int l1_id                  = lep1_pdgid();
            int l2_id                  = lep2_pdgid();

            float weight = (m_signal_region != SignalRegion::sr31 || m_signal_region != SignalRegion::sr35) ? evt_weight : 0.5*evt_weight;
            if (hyp_type == DileptonHypType::EE) 
            {
                at::FillDoubleFlipHist(*dynamic_cast<TH2F*>(hc["h_os_fo_pt_vs_eta_ee"]), *h_flip, l1_p4.pt(), l1_p4.eta(), l2_p4.pt(), l2_p4.eta(), weight);
            }
            else if (hyp_type == DileptonHypType::EMU) 
            {
                if      (abs(l1_id) == 11) {rt::Fill2D(hc["h_os_fo_pt_vs_eta_em"], fabs(l1_p4.eta()), l1_p4.pt(), weight);}
                else if (abs(l2_id) == 11) {rt::Fill2D(hc["h_os_fo_pt_vs_eta_em"], fabs(l2_p4.eta()), l2_p4.pt(), weight);}
            }
            else if (hyp_type == DileptonHypType::MUMU) 
            {
                rt::Fill2D(hc["h_os_pt1_vs_eta1_mm"], fabs(l1_p4.eta()), l1_p4.pt(), weight);
                rt::Fill2D(hc["h_os_pt2_vs_eta2_mm"], fabs(l2_p4.eta()), l2_p4.pt(), weight);
            }
        }

        //// dont't fill hists for MC if they are not truth matched (SS or DF only)
        //if ((not is_real_data()) && (not is_mc_matched) && (is_sf_mod || is_df_mod))
        //{
        //    if (m_verbose) {cout << "leptons failing truth matching (MC only)" << endl;}
        //    //return 0;
        //}

        // fake rate and flip factor for kinematic plots
        float fr1 = 0.0;
        float fr2 = 0.0;
        float fl1 = 0.0;
        float fl2 = 0.0;
        switch(charge_type)
        {
            case DileptonChargeType::SS: 
                break;
            case DileptonChargeType::SF: 
                fr1 = lep1_is_fo() * GetFakeRateValue(lep1_pdgid(), lep1_p4().pt(), lep1_p4().eta());
                fr2 = lep2_is_fo() * GetFakeRateValue(lep2_pdgid(), lep2_p4().pt(), lep2_p4().eta());
                evt_weight *= fr1/(1.0 - fr1) + fr2/(1.0 - fr2); 
                break;
            case DileptonChargeType::DF:
                fr1 = GetFakeRateValue(lep1_pdgid(), lep1_p4().pt(), lep1_p4().eta());
                fr2 = GetFakeRateValue(lep2_pdgid(), lep2_p4().pt(), lep2_p4().eta());
                evt_weight *= fr1/(1.0 - fr1) * fr2/(1.0 - fr2); 
                break;
            case DileptonChargeType::OS:
                fl1 = GetFlipRateValue(lep1_pdgid(), lep1_p4().pt(), lep1_p4().eta());
                fl2 = GetFlipRateValue(lep2_pdgid(), lep2_p4().pt(), lep2_p4().eta());
                evt_weight *= fl1/(1.0 - fl1) + fl2/(1.0 - fl2); 
                break;
            default:
                break;
        };

        // yield: fill once per channel and bin 4 for the total
        int hyp_bin = -1; 
        switch(hyp_type)
        {
            case DileptonHypType::MUMU: hyp_bin = 1; break;
            case DileptonHypType::EE  : hyp_bin = 2; break;
            case DileptonHypType::EMU : hyp_bin = 3; break; 
            default: {/*do nothing*/}
        }
        rt::Fill(hc["h_yield"+qs], hyp_bin, evt_weight);
        rt::Fill(hc["h_yield"+qs], 4      , evt_weight);

        // SS kinematic plots
        const LorentzVector& p41 = lep1_p4();
        const LorentzVector& p42 = lep2_p4();

        rt::Fill(hc["h_nvtxs" +qs], nvtxs()     , evt_weight);
        rt::Fill(hc["h_pt1"   +qs], p41.pt()    , evt_weight);
        rt::Fill(hc["h_pt2"   +qs], p42.pt()    , evt_weight);
        rt::Fill(hc["h_ht"    +qs], ht()        , evt_weight);
        rt::Fill(hc["h_mt"    +qs], lep1_mt()   , evt_weight);
        rt::Fill(hc["h_met"   +qs], pfmet()     , evt_weight);
        rt::Fill(hc["h_nbtags"+qs], num_btags   , evt_weight);
        rt::Fill(hc["h_njets" +qs], njets()     , evt_weight);

        rt::Fill(hc["h_pt1"   +hs+qs], p41.pt()    , evt_weight);
        rt::Fill(hc["h_pt2"   +hs+qs], p42.pt()    , evt_weight);
        rt::Fill(hc["h_ht"    +hs+qs], ht()        , evt_weight);
        rt::Fill(hc["h_mt"    +hs+qs], lep1_mt()   , evt_weight);
        rt::Fill(hc["h_met"   +hs+qs], pfmet()     , evt_weight);
        rt::Fill(hc["h_nbtags"+hs+qs], num_btags   , evt_weight);
        rt::Fill(hc["h_njets" +hs+qs], njets()     , evt_weight);

        // PAS plots
        rt::Fill(hc["h_pas_ht"    +qs], ht()     , evt_weight);
        rt::Fill(hc["h_pas_met"   +qs], pfmet()  , evt_weight);
        rt::Fill(hc["h_pas_njets" +qs], njets()  , evt_weight);
        rt::Fill(hc["h_pas_nbtags"+qs], num_btags, evt_weight);
        rt::Fill(hc["h_pas_pt1"   +qs], p41.pt() , evt_weight);
        rt::Fill(hc["h_pas_pt2"   +qs], p42.pt() , evt_weight);
        if (ht() > 200) // because UFL didn't keep the right triggers
        {
            rt::Fill(hc["h_pas_hthigh_ht"    +qs], ht()     , evt_weight);
            rt::Fill(hc["h_pas_hthigh_met"   +qs], pfmet()  , evt_weight);
            rt::Fill(hc["h_pas_hthigh_njets" +qs], njets()  , evt_weight);
            rt::Fill(hc["h_pas_hthigh_nbtags"+qs], num_btags, evt_weight);
            rt::Fill(hc["h_pas_hthigh_pt1"   +qs], p41.pt() , evt_weight);
            rt::Fill(hc["h_pas_hthigh_pt2"   +qs], p42.pt() , evt_weight);
        }
        if (ht() < 200) // because UFL didn't keep the right triggers
        {
            rt::Fill(hc["h_pas_htlow_ht"    +qs], ht()     , evt_weight);
            rt::Fill(hc["h_pas_htlow_met"   +qs], pfmet()  , evt_weight);
            rt::Fill(hc["h_pas_htlow_njets" +qs], njets()  , evt_weight);
            rt::Fill(hc["h_pas_htlow_nbtags"+qs], num_btags, evt_weight);
            rt::Fill(hc["h_pas_htlow_pt1"   +qs], p41.pt() , evt_weight);
            rt::Fill(hc["h_pas_htlow_pt2"   +qs], p42.pt() , evt_weight);
        }

        // dilep
        hc["h_dilep_mass"+qs   ]->Fill(dilep_mass(), evt_weight);
        hc["h_dilep_mass"+hs+qs]->Fill(dilep_mass(), evt_weight);
        if (njets()==0) 
        {
            hc["h_dilep_mass_nj0"+qs   ]->Fill(dilep_mass(), evt_weight);
            hc["h_dilep_mass_nj0"+hs+qs]->Fill(dilep_mass(), evt_weight);
        }
        if (njets()==1) 
        {
            hc["h_dilep_mass_nj1"+qs   ]->Fill(dilep_mass(), evt_weight);
            hc["h_dilep_mass_nj1"+hs+qs]->Fill(dilep_mass(), evt_weight);
        }
        if (njets()>=2) 
        {
            hc["h_dilep_mass_nj2"+qs   ]->Fill(dilep_mass(), evt_weight);
            hc["h_dilep_mass_nj2"+hs+qs]->Fill(dilep_mass(), evt_weight);
        }

        double dphi_lep = fabs(ROOT::Math::VectorUtil::DeltaPhi(p41, p42));
        rt::Fill(hc["h_lepdphi"+qs], dphi_lep, evt_weight);
        
        double deta_lep = fabs(p41.eta() - p42.eta());
        rt::Fill(hc["h_lepdeta"+qs], deta_lep, evt_weight);
        
        double dr_lep = ROOT::Math::VectorUtil::DeltaR(p41, p42);
        rt::Fill(hc["h_lepdr"+qs], dr_lep, evt_weight);

        rt::Fill(hc["h_drlepb"+qs], lep1_nearbjet_dr(), evt_weight);
        rt::Fill(hc["h_drlepb"+qs], lep2_nearbjet_dr(), evt_weight);
        
        rt::Fill(hc["h_btagdr"+qs], bjets_dr12(), evt_weight);

        for (unsigned int idx = 0; idx < vbjets_nearjet_dr().size(); idx++) 
        {
            rt::Fill(hc["h_drjetb"+qs], vbjets_nearjet_dr().at(idx), evt_weight);
        }

        double rlep1 = (lep1_nearjet_p4().pt() / p41.pt()) - 1.;
        rt::Fill(hc["h_ptjetlep"+qs], rlep1, evt_weight);

        double rlep2 = (lep2_nearjet_p4().pt() / p42.pt()) - 1.;
        rt::Fill(hc["h_ptjetlep"+qs], rlep2, evt_weight);
        
        if (lep1_nearlep_dr() > -1.) {
            rt::Fill(hc["h_drlep3rdlep"+qs], lep1_nearlep_dr(), evt_weight);
            LorentzVector gsp4 = lep1_p4() + lep1_nearlep_p4();
            rt::Fill(hc["h_ml3l"+qs], gsp4.mass(), evt_weight);
        }

        if (lep2_nearlep_dr() > -1.) {
            rt::Fill(hc["h_drlep3rdlep"+qs], lep2_nearlep_dr(), evt_weight);        
            LorentzVector gsp4 = lep2_p4() + lep2_nearlep_p4();
            rt::Fill(hc["h_ml3l"+qs], gsp4.mass(), evt_weight);
        }

        if (abs(lep1_pdgid())==13) 
        {
            rt::Fill(hc["h_pt1_mu"+qs], p41.pt(), evt_weight);
        }
        if (abs(lep2_pdgid())==13) 
        {
            rt::Fill(hc["h_pt2_mu"+qs], p42.pt(), evt_weight);
        }
        if (abs(lep1_pdgid())==11)
        {
            rt::Fill(hc["h_pt1_el"+qs], p41.pt(), evt_weight);
        }
        if (abs(lep2_pdgid())==11)
        {
            rt::Fill(hc["h_pt2_el"+qs], p42.pt(), evt_weight);
        }

    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
    }

    // analysis end
    return 0;
} 

float PlotLooper::GetFakeRateValue(int lep_id, float pt, float eta) const 
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
        float max_pt = h_mufr->GetYaxis()->GetXmax()-0.01;
        int pt_bin   = h_mufr->GetYaxis()->FindBin(min(pt, max_pt));
        int eta_bin  = h_mufr->GetXaxis()->FindBin(fabs(eta));
        return h_mufr->GetBinContent(eta_bin, pt_bin);
    }
    else if (abs(lep_id)==11) 
    {
        float max_pt = h_elfr->GetYaxis()->GetXmax()-0.01;
        int pt_bin   = h_elfr->GetYaxis()->FindBin(min(pt, max_pt));
        int eta_bin  = h_elfr->GetXaxis()->FindBin(fabs(eta));
        return h_elfr->GetBinContent(eta_bin, pt_bin);
    }
    return 0.0;
}

float PlotLooper::GetFakeRateError(int lep_id, float pt, float eta) const 
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
        float max_pt = h_mufr->GetYaxis()->GetXmax()-0.01;
        int pt_bin   = h_mufr->GetYaxis()->FindBin(min(pt, max_pt));
        int eta_bin  = h_mufr->GetXaxis()->FindBin(fabs(eta));
        return h_mufr->GetBinError(eta_bin, pt_bin);
    }
    else if (abs(lep_id)==11) 
    {
        float max_pt = h_elfr->GetYaxis()->GetXmax()-0.01;
        int pt_bin   = h_elfr->GetYaxis()->FindBin(min(pt, max_pt));
        int eta_bin  = h_elfr->GetXaxis()->FindBin(fabs(eta));
        return h_elfr->GetBinError(eta_bin, pt_bin);
    }
    return 0.0;
}

float PlotLooper::GetFlipRateValue(int lep_id, float pt, float eta) const 
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

    float max_pt = h_flip->GetYaxis()->GetXmax()-0.01;
    int pt_bin   = h_flip->GetYaxis()->FindBin(min(pt, max_pt));
    int eta_bin  = h_flip->GetXaxis()->FindBin(fabs(eta));
    return h_flip->GetBinContent(eta_bin, pt_bin);
}

float PlotLooper::GetFlipRateError(int lep_id, float pt, float eta) const 
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

    float max_pt = h_flip->GetYaxis()->GetXmax()-0.01;
    int pt_bin   = h_flip->GetYaxis()->FindBin(min(pt, max_pt));
    int eta_bin  = h_flip->GetXaxis()->FindBin(fabs(eta));
    return h_flip->GetBinError(eta_bin, pt_bin);
}

at::FakeRateBinInfo PlotLooper::GetFakeRateBinInfo() const
{
    const size_t num_mu_eta_bins = h_mufr->GetNbinsX();
    const float *mu_eta_bins = rt::ConvertDoubleArrayToFloatArray(h_mufr->GetXaxis()->GetXbins()->GetArray(), num_mu_eta_bins+1);

    const size_t num_mu_pt_bins = h_mufr->GetNbinsY();
    const float *mu_pt_bins = rt::ConvertDoubleArrayToFloatArray(h_mufr->GetYaxis()->GetXbins()->GetArray(), num_mu_pt_bins+1);

    const size_t num_el_eta_bins = h_elfr->GetNbinsX();
    const float *el_eta_bins = rt::ConvertDoubleArrayToFloatArray(h_elfr->GetXaxis()->GetXbins()->GetArray(), num_el_eta_bins+1);

    const size_t num_el_pt_bins = h_elfr->GetNbinsY();
    const float *el_pt_bins = rt::ConvertDoubleArrayToFloatArray(h_elfr->GetYaxis()->GetXbins()->GetArray(), num_el_pt_bins+1);

    at::FakeRateBinInfo tmp;
    tmp.vel_eta_bins.assign(el_eta_bins, el_eta_bins+num_el_eta_bins+1);
    tmp.vel_pt_bins .assign(el_pt_bins , el_pt_bins +num_el_pt_bins+1 );

    tmp.vmu_eta_bins.assign(mu_eta_bins, mu_eta_bins+num_mu_eta_bins+1);
    tmp.vmu_pt_bins .assign(mu_pt_bins , mu_pt_bins +num_mu_pt_bins+1 );

    return tmp;
}

at::FlipRateBinInfo PlotLooper::GetFlipRateBinInfo() const
{
    const size_t num_eta_bins = h_flip->GetNbinsX();
    const float *eta_bins = rt::ConvertDoubleArrayToFloatArray(h_flip->GetXaxis()->GetXbins()->GetArray(), num_eta_bins+1);

    const size_t num_pt_bins = h_flip->GetNbinsY();
    const float *pt_bins = rt::ConvertDoubleArrayToFloatArray(h_flip->GetYaxis()->GetXbins()->GetArray(), num_pt_bins+1);

    at::FlipRateBinInfo tmp;
    tmp.v_eta_bins.assign(eta_bins, eta_bins+num_eta_bins+1);
    tmp.v_pt_bins .assign(pt_bins , pt_bins +num_pt_bins+1 );

    return tmp;
}
