#include "PlotLooper.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include "mcSelections.h"
#include "EWKINO2012_SS.h"
#include "rt/RootTools.h"
#include "rt/is_equal.h"
#include "at/Predicates.h"
#include "at/VtxReweight.h"
#include "at/DileptonHypType.h"
#include "at/DileptonChargeType.h"
#include "SignalRegion.h"
#include "TTbarBreakDown.h"
#include "ScaleFactors.h"
#include "at/PredSummary.h"
#include "at/FakeRatePrediction.h"
#include "at/FlipRatePrediction.h"
#include "CTable.h"
#include "TEfficiency.h"
#include "electronSelections.h"

typedef std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > vecLorentzVector;

using namespace std;
using namespace at;
using namespace ewkino_ss;
using namespace ewkino;

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
    int charge_option,
    bool do_scale_factors,
    bool check_good_lumi,
    float sparm0,
    float sparm1,
    float sf_flip,
    float fr_unc,
    float fl_unc,
    float mc_unc,
    float lumi,
    bool use_cp_unc,
    bool verbose
)
    : at::AnalysisWithHist(root_file_name)
    , m_lumi(lumi)
    , m_verbose(verbose)
    , m_is_data(at::SampleIsData(sample))
    , m_do_vtx_reweight(not vtxreweight_file_name.empty())
    , m_do_scale_factors(do_scale_factors)
    , m_check_good_lumi(check_good_lumi)
    , m_use_cp_unc(use_cp_unc)
    , m_charge_option(charge_option)
    , m_sparm0(sparm0)
    , m_sparm1(sparm1)
    , m_scale1fb(-999999.0)
    , m_xsec(-999999.0)
    , m_nevts(-999999)
    , m_sf_flip(sf_flip)
    , m_fr_unc(fr_unc)
    , m_fl_unc(fl_unc)
    , m_mc_unc(mc_unc)
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
        case AnalysisType::ss:
            mufr_name = (m_is_data) ? "h_mufr40c_ewkcor" : "h_mufr40c";
            elfr_name = (m_is_data) ? "h_elfr40c_ewkcor" : "h_elfr40c";
            break;
        default:
            mufr_name = "h_mufr40c";
            elfr_name = "h_elfr40c";
            break;
    }
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

    // initialize counters
    for (size_t i = 0; i != 4; i++) {m_count_ss[i]=0.0;}
    for (size_t i = 0; i != 4; i++) {m_count_sf[i]=0.0;}
    for (size_t i = 0; i != 4; i++) {m_count_df[i]=0.0;}
    for (size_t i = 0; i != 4; i++) {m_count_os[i]=0.0;}

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
                    "MET | HT | nJets | weight" << endl;
        }
    }

    if (m_sample == at::Sample::data) m_do_scale_factors = false;

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
    m_fr_bin_info = GetFakeRateBinInfo();
    m_fl_bin_info = GetFlipRateBinInfo();
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
        if (m_use_cp_unc)
        {
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
        else
        {
            if (rt::Integral(hc["h_yield_mm"]) < (weight * 0.5)) {hc["h_yield_mm"]->SetBinError(2, weight);}
            if (rt::Integral(hc["h_yield_ee"]) < (weight * 0.5)) {hc["h_yield_ee"]->SetBinError(2, weight);}
            if (rt::Integral(hc["h_yield_em"]) < (weight * 0.5)) {hc["h_yield_em"]->SetBinError(2, weight);}
            if (rt::Integral(hc["h_yield_ll"]) < (weight * 0.5)) {hc["h_yield_ll"]->SetBinError(2, weight);}

            // yields in a signal used for overlaying
            if (hc["h_yield_ss"]->GetBinContent(2) < (weight * 0.5)) {hc["h_yield_ss"]->SetBinError(2, weight);}
            if (hc["h_yield_ss"]->GetBinContent(3) < (weight * 0.5)) {hc["h_yield_ss"]->SetBinError(3, weight);}
            if (hc["h_yield_ss"]->GetBinContent(4) < (weight * 0.5)) {hc["h_yield_ss"]->SetBinError(4, weight);}
            if (hc["h_yield_ss"]->GetBinContent(5) < (weight * 0.5)) {hc["h_yield_ss"]->SetBinError(5, weight);}        
        }
    }

    // 0 ee, 1 mm, 2 em, 3 ll
    const float yield_ss[4] = 
    {
        rt::Integral(hc["h_yield_mm"]),
        rt::Integral(hc["h_yield_ee"]),
        rt::Integral(hc["h_yield_em"]),
        rt::Integral(hc["h_yield_ll"])
    };

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
    SetPredictionAndUncertainty(m_sample, hc, "pt1"               ,"Higher p_{T} lepton (X);p_{T} (GeV);Events"                           , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pt2"               ,"Lower p_{T} lepton (X);p_{T} (GeV);Events"                            , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pt1_el"            ,"Higher p_{T} electron (X);p_{T} (GeV);Events"                         , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pt2_el"            ,"Lower p_{T} electron (X);p_{T} (GeV);Events"                          , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pt1_mu"            ,"Higher p_{T} muon (X);p_{T} (GeV);Events"                             , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pt2_mu"            ,"Lower p_{T} muon (X);p_{T} (GeV);Events"                              , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "ht"                ,"H_{T};H_{T} (GeV) (X);Events"                                         , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "mt"                ,"m_{T};m_{T} (GeV) (X);Events"                                         , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "met"               ,"MET;E_{T}^{miss} (GeV) (X);Events"                                    , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "njets"             ,"# jets (X);# jets;Events"                                             , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "lepdphi"           ,"#Delta#Phi(lep1,lep2) (X);Delta#Phi(lep1,lep2);Events"                , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "lepdeta"           ,"#Delta#eta(lep1,lep2) (X);Delta#eta(lep1,lep2);Events"                , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "lepdr"             ,"#DeltaR(lep1,lep2) (X);#DeltaR(lep1,lep2);Events"                     , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "ptjetlep"          ,"p_{T}^{jet}/p)_{T}^{lep} - 1 (X);p_{T}^{jet}/p)_{T}^{lep} - 1;Events" , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "drlep3rdlep"       ,"#DeltaR(lep, 3rd lep) (X);#DeltaR(lep,lep3);Events"                   , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "ml3l"              ,"M(lep, 3rd lep) (X);M(l,3l);Events"                                   , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "ml3ldr"            ,"#DeltaR(lep, 3rd lep) (X);#DeltaR(l,3l);Events"                       , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "jet1_pt"           ,"Highest p_{T} jet (X);p_{T};Events"                                   , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "jet2_pt"           ,"2nd Highest p_{T} jet (X);p_{T};Events"                               , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "jet3_pt"           ,"3rd Highest p_{T} jet (X);p_{T};Events"                               , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "mjj"               ,"dijet mass (X);M_{jj};Events"                                         , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "dijet_dphi"        ,"dijet #Delta#phi; #Delta#phi_{jj};Events"                             , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "dijet_deta"        ,"dijet #Delta#eta; #Delta#eta_{jj};Events"                             , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "dijet_dr"          ,"dijet #DeltaR; #DeltaR_{jj};Events"                                   , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "nlbtags"           ,"# CSVL btags;# CSVL btags;Events"                                     , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "nmbtags"           ,"# CSVM btags;# CSVM btags;Events"                                     , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "ntbtags"           ,"# CSVT btags;# CSVT btags;Events"                                     , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "htpv"              ,"PV H_{T} (X);PV H_{T} (GeV);Events"                                   , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "mt2"               ,"m_{T2} (X);m_{T2} (GeV);Events"                                       , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "mt2j"              ,"m_{T2J} (X);m_{T2} (GeV);Events"                                      , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "lep1_mt"           ,"lep1 m_{T} (X);m_{T} (GeV);Events"                                    , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "lep2_mt"           ,"lep2 m_{T} (X);m_{T} (GeV);Events"                                    , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "dijet_pt"          ,"dijet p_{T} (X);p^{jj}_{T} (GeV);Events"                              , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "dijet_eta"         ,"dijet #eta; #eta_{jj};Events"                                         , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pt3"               ,"Third lepton p_{T} (X);p_{T} (GeV);Events"                            , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pt3_el"            ,"Extra electron p_{T} (X);p_{T} (GeV);Events"                          , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pt3_mu"            ,"Extra muon p_{T} (X);p_{T} (GeV);Events"                              , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "dilep_pt"          ,"dilepton p_{T} (X);p^{ll}_{T} (GeV);Events"                           , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "dilep_eta"         ,"dilepton #eta;#eta_{ll};Events"                                       , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "dijet_pt_mass"     ,"dijet p_{T}/mass;p^{jj}_{T}/M_{jj};Events"                            , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "max_mt"            ,"max m_{T} (X);m_{T} (GeV);Events"                                     , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "isotrk_veto"       ,"iso trk veto;iso trk veto;Events"                                     , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "tau_veto"          ,"tau veto;tau veto;Events"                                             , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "dphi_met_ll"       ,"#Delta#phi(ll,met);#Delta#phi(ll,met);Events"                         , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "dphi_met_jj"       ,"#Delta#phi(jj,met);#Delta#phi(jj,met);Events"                         , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "min_dphi_met_lep"  ,"min #Delta#phi(lep,met);min #Delta#phi(lep,met);Events"               , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "max_dphi_met_lep"  ,"max #Delta#phi(lep,met);max #Delta#phi(lep,met);Events"               , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "min_dphi_met_jet"  ,"min #Delta#phi(jet,met);min #Delta#phi(jet,met);Events"               , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "max_dphi_met_jet"  ,"max #Delta#phi(jet,met);max #Delta#phi(jet,met);Events"               , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "dideta"            ,"#Delta#eta(ll,jj);#Delta#eta(ll,jj);Events"                           , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "didphi"            ,"#Delta#phi(ll,jj);#Delta#phi(ll,jj);Events"                           , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "didr"              ,"#DeltaR(ll,jj);#DeltaR(ll,jj);Events"                                 , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "min_iso"           ,"min lep iso; min lep iso;Events"                                      , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "max_iso"           ,"max lep iso; max lep iso;Events"                                      , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "dijet_lep_mass"    ,"M_{jjl} (X);M_{jjl} (GeV);Events"                                     , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "min_dijet_lep_mass","min M_{jjl} (X);min M_{jjl} (GeV);Events"                             , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);

    SetPredictionAndUncertainty(m_sample, hc, "pas_ht"            ,"H_{T};H_{T} (GeV);Events"                                             , 0.0, 0.0, 0.0, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pas_met"           ,"MET;E_{T}^{miss} (GeV);Events"                                        , 0.0, 0.0, 0.0, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pas_njets"         ,"# jets;# jets;Events"                                                 , 0.0, 0.0, 0.0, m_sf_flip);


    SetPredictionAndUncertainty(m_sample, hc, "minjpt_jjpt"       ,"min(p^{j1}_{T},p^{j2}_{t})/p^{jj}_{T}%s;min(p^{j1}_{T},p^{j2}_{t})/p^{jj}_{T};Events", m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "dijet_mass_pt_dr"  ,"M_{jj}/p^{jj}_{T}/#DeltaR_{jj};M_{jj}/p^{jj}_{T}/#DeltaR_{jj};Events"                , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);

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
        SetPredictionAndUncertainty(m_sample, hc, "njets"     +hn, Form("# jets (X, %s);# jets;Events"                  ,ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
        SetPredictionAndUncertainty(m_sample, hc, "lep1_mt"   +hn, Form("lep1 m_{T};lep1 m_{T} (GeV) (X, %s);Events"    ,ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
        SetPredictionAndUncertainty(m_sample, hc, "lep2_mt"   +hn, Form("lep2 m_{T};lep2 m_{T} (GeV) (X, %s);Events"    ,ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
        SetPredictionAndUncertainty(m_sample, hc, "pt3"       +hn, Form("Third lepton p_{T} (X, %s);p_{T} (GeV);Events" ,ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
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
            hc.Add(new TH1F(Form("h_dilep_mass%s"      , ns.c_str()), Form("dilepton mass%s;mass (GeV);Events"                             , ts.c_str()), 25 , 0   , 250 ));
            hc.Add(new TH1F(Form("h_pt1%s"             , ns.c_str()), Form("Higher p_{T} lepton%s;p_{T} (GeV);Events"                      , ts.c_str()), 20 , 0   , 200 ));
            hc.Add(new TH1F(Form("h_pt2%s"             , ns.c_str()), Form("Lower p_{T} lepton%s;p_{T} (GeV);Events"                       , ts.c_str()), 10 , 0   , 100 ));
            hc.Add(new TH1F(Form("h_ht%s"              , ns.c_str()), Form("H_{T}%s;H_{T} (GeV);Events"                                    , ts.c_str()), 20 , 0   , 400 ));
            hc.Add(new TH1F(Form("h_mt%s"              , ns.c_str()), Form("m_{T}%s;m_{T} (GeV);Events"                                    , ts.c_str()), 20 , 0   , 200 ));
            hc.Add(new TH1F(Form("h_met%s"             , ns.c_str()), Form("MET%s;E_{T}^{miss} (GeV);Events"                               , ts.c_str()), 10 , 0   , 200 ));
            hc.Add(new TH1F(Form("h_njets%s"           , ns.c_str()), Form("# jets%s;# jets;Events"                                        , ts.c_str()), 10 , -0.5, 9.5 ));
            hc.Add(new TH1F(Form("h_lepdphi%s"         , ns.c_str()), Form("#Delta#Phi(lep1, lep2)%s;#Delta#Phi(lep1, lep2);Events"        , ts.c_str()), 32 , 0   , 3.2 ));
            hc.Add(new TH1F(Form("h_lepdeta%s"         , ns.c_str()), Form("#Delta#eta(lep1, lep2)%s;#Delta#eta(lep1, lep2);Events"        , ts.c_str()), 20 , 0   , 4.0 ));
            hc.Add(new TH1F(Form("h_lepdr%s"           , ns.c_str()), Form("#DeltaR(lep1, lep2)%s;#DeltaR(lep1, lep2);Events"              , ts.c_str()), 30 , 0   , 6.0 ));
            hc.Add(new TH1F(Form("h_ml3l%s"            , ns.c_str()), Form("M(lep,3rd lep)%s;M(l,3l);Events"                               , ts.c_str()), 10 , 0.  , 50. ));
            hc.Add(new TH1F(Form("h_ml3ldr%s"          , ns.c_str()), Form("#DeltaR(lep,3rd lep)%s;#DeltaR(l,3l);Events"                   , ts.c_str()), 30 , 0.  , 6.0 ));
            hc.Add(new TH1F(Form("h_drlep3rdlep%s"     , ns.c_str()), Form("#DeltaR(lep, lep3)%s:#DeltaR(lep, 3rd lep);Events"             , ts.c_str()), 30 , 0   , 6.0 ));
            hc.Add(new TH1F(Form("h_ptjetlep%s"        , ns.c_str()), Form("jet p_{T} / lep p_{T} - 1%s;p_{T}^{jet}/p_{T}^{lep} - 1;Events", ts.c_str()), 50 , 0.  , 5.0 ));
            hc.Add(new TH1F(Form("h_nvtxs%s"           , ns.c_str()), Form("# vtxs%s; #vtxs;Events"                                        , ts.c_str()), 20 , 0   , 40  ));
            hc.Add(new TH1F(Form("h_pt1_el%s"          , ns.c_str()), Form("Higher p_{T} electron%s;p_{T} (GeV);Events"                    , ts.c_str()), 20 , 0   , 200 ));
            hc.Add(new TH1F(Form("h_pt2_el%s"          , ns.c_str()), Form("Lower p_{T} electron%s;p_{T} (GeV);Events"                     , ts.c_str()), 20 , 0   , 200 ));
            hc.Add(new TH1F(Form("h_pt1_mu%s"          , ns.c_str()), Form("Higher p_{T} muons%s;p_{T} (GeV);Events"                       , ts.c_str()), 20 , 0   , 200 ));
            hc.Add(new TH1F(Form("h_pt2_mu%s"          , ns.c_str()), Form("Lower p_{T} muons%s;p_{T} (GeV);Events"                        , ts.c_str()), 20 , 0   , 200 ));
            hc.Add(new TH1F(Form("h_jet1_pt%s"         , ns.c_str()), Form("Highest p_{T} jet%s;p_{T} (GeV);Events"                        , ts.c_str()), 25 , 0   , 250 ));
            hc.Add(new TH1F(Form("h_jet2_pt%s"         , ns.c_str()), Form("2nd Highest p_{T} jet%s;p_{T} (GeV);Events"                    , ts.c_str()), 25 , 0   , 250 ));
            hc.Add(new TH1F(Form("h_jet3_pt%s"         , ns.c_str()), Form("3rd Highest p_{T} jet%s;p_{T} (GeV);Events"                    , ts.c_str()), 25 , 0   , 250 ));
            hc.Add(new TH1F(Form("h_mjj%s"             , ns.c_str()), Form("dijet mass%s;M_{jj} (GeV);Events"                              , ts.c_str()), 20 , 0   , 300 ));
            hc.Add(new TH1F(Form("h_dijet_dphi%s"      , ns.c_str()), Form("dijet #Delta#phi%s;#Delta#phi_{jj};Events"                     , ts.c_str()), 32 , 0   , 3.2 ));
            hc.Add(new TH1F(Form("h_dijet_deta%s"      , ns.c_str()), Form("dijet #Delta#eta%s;#Delta#eta_{jj};Events"                     , ts.c_str()), 20 , 0   , 4.0 ));
            hc.Add(new TH1F(Form("h_dijet_dr%s"        , ns.c_str()), Form("dijet #DeltaR%s;#DeltaR_{jj};Events"                           , ts.c_str()), 30 , 0   , 6.0 ));
            hc.Add(new TH1F(Form("h_nlbtags%s"         , ns.c_str()), Form("# CSVL btags%s;# CVSL btags;Events"                            , ts.c_str()), 4  , -0.5, 3.5 ));
            hc.Add(new TH1F(Form("h_nmbtags%s"         , ns.c_str()), Form("# CSVM btags%s;# CVSM btags;Events"                            , ts.c_str()), 4  , -0.5, 3.5 ));
            hc.Add(new TH1F(Form("h_ntbtags%s"         , ns.c_str()), Form("# CSVT btags%s;# CVST btags;Events"                            , ts.c_str()), 4  , -0.5, 3.5 ));
            hc.Add(new TH1F(Form("h_htpv%s"            , ns.c_str()), Form("PV H_{T}%s; PV H_{T} (GeV);Events"                             , ts.c_str()), 20 , 0   , 400 ));
            hc.Add(new TH1F(Form("h_mt2%s"             , ns.c_str()), Form("m_{T2}%s;m_{T2} (GeV);Events"                                  , ts.c_str()), 20 , 0   , 200 ));
            hc.Add(new TH1F(Form("h_mt2j%s"            , ns.c_str()), Form("m_{T2J}%s;m_{T2J} (GeV);Events"                                , ts.c_str()), 20 , 0   , 400 ));
            hc.Add(new TH1F(Form("h_lep1_mt%s"         , ns.c_str()), Form("lep1 m_{T}%s;m_{T} (GeV);Events"                               , ts.c_str()), 20 , 0   , 200 ));
            hc.Add(new TH1F(Form("h_lep2_mt%s"         , ns.c_str()), Form("lep2 m_{T}%s;m_{T} (GeV);Events"                               , ts.c_str()), 20 , 0   , 200 ));
            hc.Add(new TH1F(Form("h_dijet_pt%s"        , ns.c_str()), Form("dijet p_{T}%s;p^{jj}_{T} (GeV);Events"                         , ts.c_str()), 20 , 0   , 400 ));
            hc.Add(new TH1F(Form("h_dijet_eta%s"       , ns.c_str()), Form("dijet #eta%s;#eta_{jj};Events"                                 , ts.c_str()), 15 , 0   , 3.0 ));
            hc.Add(new TH1F(Form("h_pt3%s"             , ns.c_str()), Form("3rd lepton p_{T}%s;p_{T} (GeV);Events"                         , ts.c_str()), 10 , 0   , 100 ));
            hc.Add(new TH1F(Form("h_pt3_el%s"          , ns.c_str()), Form("Extra electron p_{T}%s;p_{T} (GeV);Events"                     , ts.c_str()), 10 , 0   , 100 ));
            hc.Add(new TH1F(Form("h_pt3_mu%s"          , ns.c_str()), Form("Extra muon p_{T}%s;p_{T} (GeV);Events"                         , ts.c_str()), 10 , 0   , 100 ));
            hc.Add(new TH1F(Form("h_dilep_pt%s"        , ns.c_str()), Form("dilepton p_{T}%s;p^{ll}_{T} (GeV);Events"                      , ts.c_str()), 20 , 0   , 200 ));
            hc.Add(new TH1F(Form("h_dilep_eta%s"       , ns.c_str()), Form("dilepton #eta%s;#eta_{ll};Events"                              , ts.c_str()), 30 , -3.0, 3.0 ));
            hc.Add(new TH1F(Form("h_dijet_pt_mass%s"   , ns.c_str()), Form("dijet p_{T}/mass%s;p^{jJ}_{T}/M_{jj};Events"                   , ts.c_str()), 30 , 0   , 3.0 ));            
            hc.Add(new TH1F(Form("h_max_mt%s"          , ns.c_str()), Form("max m_{T}%s;m_{T} (GeV);Events"                                , ts.c_str()), 30 , 0   , 300 ));
            hc.Add(new TH1F(Form("h_isotrk_veto%s"     , ns.c_str()), Form("iso trk veto%s;iso trk veto;Events"                            , ts.c_str()), 4  , -1.5, 2.5 ));
            hc.Add(new TH1F(Form("h_tau_veto%s"        , ns.c_str()), Form("tau veto%s;tau veto;Events"                                    , ts.c_str()), 4  , -1.5, 2.5 ));
            hc.Add(new TH1F(Form("h_dideta%s"          , ns.c_str()), Form("#Delta#eta(ll,jj)%s;#Delta#eta(ll,jj);Events"                  , ts.c_str()), 20 ,    0, 4.0 ));
            hc.Add(new TH1F(Form("h_didphi%s"          , ns.c_str()), Form("#Delta#phi(ll,jj)%s;#Delta#phi(ll,jj);Events"                  , ts.c_str()), 32 ,    0, 3.2 ));
            hc.Add(new TH1F(Form("h_didr%s"            , ns.c_str()), Form("#DeltaR(ll,jj)%s;#DeltaR(ll,jj);Events"                        , ts.c_str()), 30 ,    0, 6.0 ));
            hc.Add(new TH1F(Form("h_dphi_met_ll%s"     , ns.c_str()), Form("#Delta#phi(ll,met)%s;#Delta#phi(ll,met);Events"                , ts.c_str()), 32 ,    0, 3.2 ));
            hc.Add(new TH1F(Form("h_dphi_met_jj%s"     , ns.c_str()), Form("#Delta#phi(jj,met)%s;#Delta#phi(jj,met);Events"                , ts.c_str()), 32 ,    0, 3.2 ));
            hc.Add(new TH1F(Form("h_min_dphi_met_lep%s", ns.c_str()), Form("min #Delta#phi(lep,met)%s;min #Delta#phi(lep,met);Events"      , ts.c_str()), 32 ,    0, 3.2 ));
            hc.Add(new TH1F(Form("h_max_dphi_met_lep%s", ns.c_str()), Form("max #Delta#phi(lep,met)%s;max #Delta#phi(lep,met);Events"      , ts.c_str()), 32 ,    0, 3.2 ));
            hc.Add(new TH1F(Form("h_min_dphi_met_jet%s", ns.c_str()), Form("min #Delta#phi(jet,met)%s;min #Delta#phi(jet,met);Events"      , ts.c_str()), 32 ,    0, 3.2 ));
            hc.Add(new TH1F(Form("h_max_dphi_met_jet%s", ns.c_str()), Form("max #Delta#phi(jet,met)%s;max #Delta#phi(jet,met);Events"      , ts.c_str()), 32 ,    0, 3.2 ));
            hc.Add(new TH1F(Form("h_min_iso%s"         , ns.c_str()), Form("min(lep1_iso,lep2_iso)%s;min(lep1_iso,lep2_iso);Events"        , ts.c_str()), 15 ,    0, 0.15));
            hc.Add(new TH1F(Form("h_max_iso%s"         , ns.c_str()), Form("max(lep1_iso,lep2_iso)%s;max(lep1_iso,lep2_iso);Events"        , ts.c_str()), 15 ,    0, 0.15));
            hc.Add(new TH1F(Form("h_dijet_lep_mass%s"    , ns.c_str()), Form("M_{jjl}%s;M_{jjl};Events"                                    , ts.c_str()), 35 ,    0, 700 ));
            hc.Add(new TH1F(Form("h_min_dijet_lep_mass%s", ns.c_str()), Form("min M_{jjl}%s;min M_{jjl};Events"                            , ts.c_str()), 35 ,    0, 700 ));

            hc.Add(new TH1F(Form("h_minjpt_jjpt%s"     , ns.c_str()), Form("min(p^{j1}_{T},p^{j2}_{t})/p^{jj}_{T}%s;min(p^{j1}_{T},p^{j2}_{t})/p^{jj}_{T};Events", ts.c_str()), 20 , 0   , 4 ));
            hc.Add(new TH1F(Form("h_dijet_mass_pt_dr%s", ns.c_str()), Form("M_{jj}/p^{jj}_{T}/#DeltaR_{jj}%s;M_{jj}/p^{jj}_{T}/#DeltaR_{jj};Events",               ts.c_str()), 20 , 0   , 4 ));

            // plots for the PAS
            hc.Add(new TH1F(Form("h_pas_ht%s"     , ns.c_str()), Form("H_{T}%s;H_{T} (GeV);Events"     , ts.c_str()), 13 , 80.0 , 600.0));
            hc.Add(new TH1F(Form("h_pas_met%s"    , ns.c_str()), Form("MET%s;E_{T}^{miss} (GeV);Events", ts.c_str()), 10 , 0.0  , 250.0));
            hc.Add(new TH1F(Form("h_pas_njets%s"  , ns.c_str()), Form("# jets%s;# jets;Events"         , ts.c_str()), 7  , 2.0  , 9.0  ));


            for (size_t i = 1; i != at::DileptonHypType::static_size; i++)
            {
                at::DileptonHypType::value_type hyp_type = static_cast<at::DileptonHypType::value_type>(i);

                // name and title suffixes
                string hn = Form("_%s" ,  GetDileptonHypTypeName(hyp_type).c_str());
                string ht = Form(" (%s)",  GetDileptonHypTypeTitle(hyp_type).c_str());

                hc.Add(new TH1F(Form("h_dilep_mass%s%s"    , hn.c_str(), ns.c_str()), Form("dilepton mass%s%s;mass (GeV);Events"       , ts.c_str(), ht.c_str()), 25 , 0   , 250 ));
                hc.Add(new TH1F(Form("h_pt1%s%s"           , hn.c_str(), ns.c_str()), Form("Higher p_{T} lepton%s%s;p_{T} (GeV);Events", ts.c_str(), ht.c_str()), 20 , 0   , 200 ));
                hc.Add(new TH1F(Form("h_pt2%s%s"           , hn.c_str(), ns.c_str()), Form("Lower p_{T} lepton%s%s;p_{T} (GeV);Events" , ts.c_str(), ht.c_str()), 20 , 0   , 200 ));
                hc.Add(new TH1F(Form("h_ht%s%s"            , hn.c_str(), ns.c_str()), Form("H_{T}%s%s;H_{T} (GeV);Events"              , ts.c_str(), ht.c_str()), 20 , 0   , 400 ));
                hc.Add(new TH1F(Form("h_mt%s%s"            , hn.c_str(), ns.c_str()), Form("m_{T}%s%s;m_{T} (GeV);Events"              , ts.c_str(), ht.c_str()), 20 , 0   , 200 ));
                hc.Add(new TH1F(Form("h_met%s%s"           , hn.c_str(), ns.c_str()), Form("MET%s%s;E_{T}^{miss} (GeV);Events"         , ts.c_str(), ht.c_str()), 20 , 0   , 200 ));
                hc.Add(new TH1F(Form("h_njets%s%s"         , hn.c_str(), ns.c_str()), Form("# jets%s%s;# jets;Events"                  , ts.c_str(), ht.c_str()), 10 , -0.5, 9.5 ));
                hc.Add(new TH1F(Form("h_lep1_mt%s%s"       , hn.c_str(), ns.c_str()), Form("lep1 m_{T}%s%s;m_{T} (GeV);Events"         , ts.c_str(), ht.c_str()), 20 , 0   , 200 ));
                hc.Add(new TH1F(Form("h_lep2_mt%s%s"       , hn.c_str(), ns.c_str()), Form("lep2 m_{T}%s%s;m_{T} (GeV);Events"         , ts.c_str(), ht.c_str()), 20 , 0   , 200 ));
                hc.Add(new TH1F(Form("h_pt3%s%s"           , hn.c_str(), ns.c_str()), Form("Third lepton p_{T}%s%s;p_{T} (GeV);Events" , ts.c_str(), ht.c_str()), 10 , 0   , 100  ));
                hc.Add(new TH1F(Form("h_max_mt%s%s"        , hn.c_str(), ns.c_str()), Form("max m_{T}%s%s;m_{T} (GeV);Events"          , ts.c_str(), ht.c_str()), 20 , 0   , 200 ));
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
    using namespace ewkino_ss;

    try
    {
        // base analysis
        at::AnalysisWithHist::operator()(event);

        // convenience alias
        rt::TH1Container& hc = m_hist_container;

        // fix to wgstar's scale1fb
        if (m_sample == Sample::wgstar2m) {m_scale1fb = 0.00638;}
        if (m_sample == Sample::wgstar2t) {m_scale1fb = 0.00672;}

        m_xsec     = xsec();
        m_nevts    = static_cast<int>((xsec()*1000)/scale1fb());
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

        // if the value of m_m_sparm0 negative, this check is skipped
        if (is_signal_mc && m_sparm0 >= 0.0f && not rt::is_equal(m_sparm0, sparm0()))
        {
            if (m_verbose) {cout << Form("fails the sparm0 check: %s, %1.2f != %1.2f", sparm0_name().Data(), m_sparm0, sparm0()) << endl;}
            return 0;
        }

        // if the value of m_sparm1 is negative, this check is skipped
        if (is_signal_mc && m_sparm1 >= 0.0f && not rt::is_equal(m_sparm1, sparm1()))
        {
            if (m_verbose) {cout << Form("fails the sparm1 check: %s, %1.2f != %1.2f", sparm1_name().Data(), m_sparm1, sparm1()) << endl;}
            return 0;
        }

        // scale 1b (set before cuts) 
        m_scale1fb = (is_real_data() ? 1.0 : scale1fb());

        if ((not is_real_data()) && (not is_mc_matched) && (is_rare_mc || is_signal_mc))
        {
            if (m_verbose) {cout << "failing MC truth matching" << endl;}
            return 0;
        }

        // charge type
        DileptonChargeType::value_type charge_type = DileptonChargeType::static_size;
        if (is_ss()) {charge_type = DileptonChargeType::SS;}
        if (is_sf()) {charge_type = DileptonChargeType::SF;}
        if (is_df()) {charge_type = DileptonChargeType::DF;}
        if (is_os()) {charge_type = DileptonChargeType::OS;}
        if (ewkino_ss::charge_type() < 0)
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
            case AnalysisType::ss:
                mu_min_pt = 20.0;
                el_min_pt = 20.0;
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

        // charge option (1 == ++, -1 == --)
        switch (m_charge_option)
        {
//             case  1: if (not is_pp()) return 0; break;
//             case -1: if (not is_mm()) return 0; break;
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

        // passes signal region
        if (not PassesSignalRegion(m_signal_region, m_analysis_type, m_signal_region_type, m_do_scale_factors))
        {
            if (m_verbose) {cout << "failing signal region cut" << endl;}
            return 0;
        }

        // ttbar breakdown 
        switch (m_sample)
        {
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
            if(is_ss()) m_count_ss[0] += 1.0;
            if(is_sf()) m_count_sf[0] += 1.0;
            if(is_df()) m_count_df[0] += 1.0;
            if(is_os()) m_count_os[0] += 1.0;
        }
        else if (dilep_type()==DileptonHypType::EMU)
        {
            if(is_ss()) m_count_ss[1] += 1.0;
            if(is_sf()) m_count_sf[1] += 1.0;
            if(is_df()) m_count_df[1] += 1.0;
            if(is_os()) m_count_os[1] += 1.0;
        }
        else if (dilep_type()==DileptonHypType::EE)
        {
            if(is_ss()) m_count_ss[2] += 1.0;
            if(is_sf()) m_count_sf[2] += 1.0;
            if(is_df()) m_count_df[2] += 1.0;
            if(is_os()) m_count_os[2] += 1.0;
        }
        // count all 
        {
            if(is_ss()) m_count_ss[3] += 1.0;
            if(is_sf()) m_count_sf[3] += 1.0;
            if(is_df()) m_count_df[3] += 1.0;
            if(is_os()) m_count_os[3] += 1.0;
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
        if (is_ss())
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
                fout << Form("%6u | %3u | %12u | %s | %4.3f | %2.3f | %2.3f | %4.3f | %4.3f | %2.3f | %2.3f | %4.3f | %4.3f | %4.3f | %u | %4.3f",
                             run(), ls(), evt(),
                             channel.c_str(),
                             lep1_p4().pt(), lep1_p4().eta(), lep1_p4().phi(), lep1_corpfiso(),
                             lep2_p4().pt(), lep2_p4().eta(), lep2_p4().phi(), lep2_corpfiso(),
                             pfmet(),
                             ht(),
                             njets(),
                             scale1fb()) << endl;
            }
        }

        // SF 
        if (is_sf())
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
        if (is_df())
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
        if (is_os())
        {

            const LorentzVector& l1_p4 = lep1_p4();
            const LorentzVector& l2_p4 = lep2_p4();
            int l1_id                  = lep1_pdgid();
            int l2_id                  = lep2_pdgid();

            float weight = evt_weight;
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

        rt::Fill(hc["h_nvtxs"  +qs], nvtxs()     , evt_weight);
        rt::Fill(hc["h_pt1"    +qs], p41.pt()    , evt_weight);
        rt::Fill(hc["h_pt2"    +qs], p42.pt()    , evt_weight);
        rt::Fill(hc["h_ht"     +qs], ht()        , evt_weight);
        rt::Fill(hc["h_mt"     +qs], mt()        , evt_weight);
        rt::Fill(hc["h_met"    +qs], pfmet()     , evt_weight);
        rt::Fill(hc["h_njets"  +qs], njets_pv_tight0()     , evt_weight);
        rt::Fill(hc["h_lep1_mt"+qs], lep1_mt()  , evt_weight);
        rt::Fill(hc["h_lep2_mt"+qs], lep2_mt()  , evt_weight);
        rt::Fill(hc["h_max_mt" +qs], std::max(lep1_mt(),lep2_mt()), evt_weight);

        rt::Fill(hc["h_pt1"    +hs+qs], p41.pt()    , evt_weight);
        rt::Fill(hc["h_pt2"    +hs+qs], p42.pt()    , evt_weight);
        rt::Fill(hc["h_ht"     +hs+qs], ht()        , evt_weight);
        rt::Fill(hc["h_mt"     +hs+qs], mt()        , evt_weight);
        rt::Fill(hc["h_met"    +hs+qs], pfmet()     , evt_weight);
        rt::Fill(hc["h_njets"  +hs+qs], njets_pv_tight0()     , evt_weight);
        rt::Fill(hc["h_lep1_mt"+hs+qs], lep1_mt()  , evt_weight);
        rt::Fill(hc["h_lep2_mt"+hs+qs], lep2_mt()  , evt_weight);
        rt::Fill(hc["h_max_mt" +hs+qs], std::max(lep1_mt(),lep2_mt()), evt_weight);

        rt::Fill(hc["h_dilep_pt"+qs], dilep_p4().pt(), evt_weight);
        rt::Fill(hc["h_dilep_eta"+qs], dilep_p4().eta(), evt_weight);

        // PAS plots
        rt::Fill(hc["h_pas_ht"    +qs], ht()     , evt_weight);
        rt::Fill(hc["h_pas_met"   +qs], pfmet()  , evt_weight);
        rt::Fill(hc["h_pas_njets" +qs], njets_pv_tight0()  , evt_weight);

        rt::Fill(hc["h_dphi_met_ll"+qs], rt::DeltaPhi(dilep_p4().phi(), pfmet_phi()), evt_weight);
        rt::Fill(hc["h_min_dphi_met_lep"+qs], std::min(rt::DeltaPhi(lep1_p4().phi(), pfmet_phi()), rt::DeltaPhi(lep2_p4().phi(), pfmet_phi())), evt_weight);
        rt::Fill(hc["h_max_dphi_met_lep"+qs], std::max(rt::DeltaPhi(lep1_p4().phi(), pfmet_phi()), rt::DeltaPhi(lep2_p4().phi(), pfmet_phi())), evt_weight);

        rt::Fill(hc["h_min_iso"+qs], min(lep1_corpfiso(), lep2_corpfiso()), evt_weight);
        rt::Fill(hc["h_max_iso"+qs], max(lep1_corpfiso(), lep2_corpfiso()), evt_weight);

        if (abs(lep3_pdgid()) == 11)
        {
            using namespace wp2012;
            electronIdComponent_t passAllVetoCuts = DETAIN | DPHIIN | SIGMAIETAIETA | HOE | DZVTX;
            if ((passAllVetoCuts & lep3_eleid_medium()) == passAllVetoCuts)
            {
                rt::Fill(hc["h_pt3"    +hs+qs], lep3_p4().pt(), evt_weight);
                rt::Fill(hc["h_pt3"    +qs], lep3_p4().pt(), evt_weight);
            }
        }
        if (abs(lep3_pdgid()) == 13 && lep3_is_tightmu())
        {
            rt::Fill(hc["h_pt3"    +hs+qs], lep3_p4().pt(), evt_weight);
            rt::Fill(hc["h_pt3"    +qs], lep3_p4().pt(), evt_weight);
        }

        // dilep
        hc["h_dilep_mass"+qs   ]->Fill(dilep_mass(), evt_weight);
        hc["h_dilep_mass"+hs+qs]->Fill(dilep_mass(), evt_weight);

        double dphi_lep = fabs(ROOT::Math::VectorUtil::DeltaPhi(p41, p42));
        rt::Fill(hc["h_lepdphi"+qs], dphi_lep, evt_weight);
        
        double deta_lep = fabs(p41.eta() - p42.eta());
        rt::Fill(hc["h_lepdeta"+qs], deta_lep, evt_weight);
        
        double dr_lep = ROOT::Math::VectorUtil::DeltaR(p41, p42);
        rt::Fill(hc["h_lepdr"+qs], dr_lep, evt_weight);

        double rlep1 = (lep1_nearjet_p4().pt() / p41.pt()) - 1.;
        rt::Fill(hc["h_ptjetlep"+qs], rlep1, evt_weight);

        double rlep2 = (lep2_nearjet_p4().pt() / p42.pt()) - 1.;
        rt::Fill(hc["h_ptjetlep"+qs], rlep2, evt_weight);
        
        if (lep1_nearlep_dr() > -1.) {
            LorentzVector gsp4 = lep1_p4() + lep1_nearlep_p4();
            rt::Fill(hc["h_ml3l"+qs], gsp4.mass(), evt_weight);
            rt::Fill(hc["h_ml3ldr"+qs], lep1_nearlep_dr(), evt_weight);
        }

        if (lep2_nearlep_dr() > -1.) {
            LorentzVector gsp4 = lep2_p4() + lep2_nearlep_p4();
            rt::Fill(hc["h_ml3l"+qs], gsp4.mass(), evt_weight);
            rt::Fill(hc["h_ml3ldr"+qs], lep2_nearlep_dr(), evt_weight);
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
        if (abs(lep3_pdgid()) == 11)
        {
            rt::Fill(hc["h_pt3_el"+qs], lep3_p4().pt(), evt_weight);
        }
        if (abs(lep3_pdgid()) == 13)
        {
            rt::Fill(hc["h_pt3_mu"+qs], lep3_p4().pt(), evt_weight);
        }

        //
        // fill pt of "good" jets
        //
        std::vector<LorentzVector> matched_jets_p4;
        for (unsigned int idx = 0; idx < vjets_p4().size(); idx++)
        {
            if (!vjets_matched_pv().at(idx)) continue;
            matched_jets_p4.push_back(vjets_p4().at(idx));
            std::string jet_string = Form("h_jet%d_pt", (int)matched_jets_p4.size());
            rt::Fill(hc[jet_string+qs], vjets_p4().at(idx).pt(), evt_weight);
        }

        if (matched_jets_p4.size() > 1)
        {
            LorentzVector dijet_p4 = matched_jets_p4.at(0) + matched_jets_p4.at(1);
            rt::Fill(hc["h_mjj"+qs], dijet_p4.mass(), evt_weight);
            rt::Fill(hc["h_dijet_pt"+qs], dijet_p4.pt(), evt_weight);
            rt::Fill(hc["h_dijet_eta"+qs], fabs(dijet_p4.eta()), evt_weight);
            rt::Fill(hc["h_dijet_dphi"+qs], rt::DeltaPhi(matched_jets_p4.at(0).phi(), matched_jets_p4.at(1).phi()), evt_weight);
            rt::Fill(hc["h_dijet_deta"+qs], rt::DeltaEta(matched_jets_p4.at(0), matched_jets_p4.at(1)), evt_weight);
            rt::Fill(hc["h_dijet_dr"+qs], rt::DeltaR(matched_jets_p4.at(0), matched_jets_p4.at(1)), evt_weight);
            rt::Fill(hc["h_dijet_pt_mass"+qs], dijet_p4.pt()/dijet_p4.mass(), evt_weight);

            //
            // fill min(jet1 pt, jet2 pt) / pt(jj)
            //
            float min_jet_pt = std::min(matched_jets_p4.at(0).pt(), matched_jets_p4.at(1).pt());
            rt::Fill(hc["h_minjpt_jjpt"+qs], min_jet_pt/dijet_p4.pt(), evt_weight);

            rt::Fill(hc["h_dijet_mass_pt_dr"+qs], dijet_p4.mass() / dijet_p4.pt() / rt::DeltaR(matched_jets_p4.at(0), matched_jets_p4.at(1)), evt_weight);


            rt::Fill(hc["h_dphi_met_jj"+qs], rt::DeltaPhi(dijet_p4.phi(), pfmet_phi()), evt_weight);

            rt::Fill(hc["h_didphi"+qs], rt::DeltaPhi(dilep_p4().phi(), dijet_p4.phi()), evt_weight);
            rt::Fill(hc["h_dideta"+qs], rt::DeltaEta(dilep_p4(), dijet_p4), evt_weight);
            rt::Fill(hc["h_didr"+qs], rt::DeltaR(dilep_p4(), dijet_p4), evt_weight);

            LorentzVector dijet_lep1_p4 = dijet_p4 + lep1_p4();
            LorentzVector dijet_lep2_p4 = dijet_p4 + lep2_p4();
            rt::Fill(hc["h_min_dijet_lep_mass"+qs], min(dijet_lep1_p4.mass(), dijet_lep2_p4.mass()), evt_weight);

            LorentzVector dijet_lep_p4 = LorentzVector(0,0,0,0);
            rt::DeltaR(dijet_p4, lep1_p4()) < rt::DeltaR(dijet_p4, lep2_p4()) ? dijet_lep_p4 = dijet_lep1_p4 : dijet_lep_p4 = dijet_lep2_p4;
            rt::Fill(hc["h_dijet_lep_mass"+qs], dijet_lep_p4.mass(), evt_weight);
        }

        if (matched_jets_p4.size() > 1)
        {
            rt::Fill(hc["h_min_dphi_met_jet"+qs], std::min(rt::DeltaPhi(matched_jets_p4.at(0).phi(), pfmet_phi()), rt::DeltaPhi(matched_jets_p4.at(1).phi(), pfmet_phi())), evt_weight);
            rt::Fill(hc["h_max_dphi_met_jet"+qs], std::max(rt::DeltaPhi(matched_jets_p4.at(0).phi(), pfmet_phi()), rt::DeltaPhi(matched_jets_p4.at(1).phi(), pfmet_phi())), evt_weight);
        }

        float htpv = 0.;
        for (unsigned int idx = 0; idx < matched_jets_p4.size(); idx++)
            htpv += matched_jets_p4.at(idx).pt();

        rt::Fill(hc["h_htpv"+qs], htpv, evt_weight);

        //
        // fill mt2
        //
        rt::Fill(hc["h_mt2"+qs], mt2(), evt_weight);
        rt::Fill(hc["h_mt2j"+qs], mt2j(), evt_weight);

        rt::Fill(hc["h_isotrk_veto"+qs], passes_isotrk_veto(), evt_weight);
        rt::Fill(hc["h_tau_veto"+qs], passes_tau_veto(), evt_weight);

        //
        // number of btags
        //
        if (m_is_data)
        {
            rt::Fill(hc["h_nlbtags"+qs], nlbtags_pv(), evt_weight);
            rt::Fill(hc["h_nmbtags"+qs], nmbtags_pv(), evt_weight);
            rt::Fill(hc["h_ntbtags"+qs], ntbtags_pv(), evt_weight);
        }
        else
        {
            rt::Fill(hc["h_nlbtags"+qs], nlbtags_pv_reweighted(), evt_weight);
            rt::Fill(hc["h_nmbtags"+qs], nmbtags_pv_reweighted(), evt_weight);
            rt::Fill(hc["h_ntbtags"+qs], ntbtags_pv_reweighted(), evt_weight);
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

bool PlotLooper::passesMVAJetId(LorentzVector p4, float mva_value, int tightness)
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
