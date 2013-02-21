#include "InterpLooper.h"
#include <iostream>
#include <fstream>
#include <algorithm>
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
#include "TTbarBreakDown.h"
#include "ScaleFactors.h"
#include "SignalBinInfo.h"
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
InterpLooper::InterpLooper
(
    const std::string& root_file_name,
    Sample::value_type sample,
    SignalRegion::value_type signal_region,
    AnalysisType::value_type analysis_type,
    SignalRegionType::value_type signal_region_type,
    at::YieldType::value_type yield_type,
    const std::string& fake_rate_file_name,
    const std::string& flip_rate_file_name,
    bool do_scale_factors,
    float sparm0,
    float sparm1,
    float sparm2,
    float sparm3,
    float sf_flip,
    float fr_unc,
    float fl_unc,
    float mc_unc,
    float lumi,
    bool verbose
)
    : at::AnalysisWithHist(root_file_name)
    , m_lumi(lumi)
    , m_verbose(verbose)
    , m_is_data(at::SampleIsData(sample))
    , m_do_scale_factors(do_scale_factors)
    , m_sparm0(sparm0)
    , m_sparm1(sparm1)
    , m_sparm2(sparm2)
    , m_sparm3(sparm3)
    , m_scale1fb(-999999.0)
    , m_nevts(-999999)
    , m_sf_flip(sf_flip)
    , m_fr_unc(fr_unc)
    , m_fl_unc(fl_unc)
    , m_mc_unc(mc_unc)
    , m_sample(sample)
    , m_signal_region(signal_region)
    , m_analysis_type(analysis_type)
    , m_signal_region_type(signal_region_type)
    , m_yield_type(yield_type)
{
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
            mufr_name = "h_mufr40c";
            elfr_name = "h_elfr40c_noiso";
            break;
        case AnalysisType::vlow_pt:
            mufr_name = "h_mufr40c_iso";
            elfr_name = "h_elfr40c_noiso";
            break;
        default:
            mufr_name = "h_mufr40c";
            elfr_name = "h_elfr40c";
            break;
    }
    h_mufr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get(mufr_name.c_str())->Clone()));
    h_elfr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get(elfr_name.c_str())->Clone()));
    if (not h_mufr) {throw std::runtime_error(Form("ERROR: InterpLooper: %s doesn't exist", mufr_name.c_str()));}
    if (not h_elfr) {throw std::runtime_error(Form("ERROR: InterpLooper: %s doesn't exist", elfr_name.c_str()));}
    h_mufr->SetDirectory(0);
    h_elfr->SetDirectory(0);

    cout << "using mu FR hist : " << h_mufr->GetName() << endl;
    cout << "using el FR hist : " << h_elfr->GetName() << endl;

    // set the fake rate histograms
    std::auto_ptr<TFile> flip_rate_file(rt::OpenRootFile(flip_rate_file_name));
    cout << "using FL file : " << flip_rate_file->GetName() << endl;
    h_flip.reset(dynamic_cast<TH2F*>(flip_rate_file->Get("flipRate")->Clone()));
    if (not h_flip) {throw std::runtime_error("ERROR: InterpLooper: flipRate doesn't exist");}
    h_flip->SetDirectory(0);

    // initialize counters
    for (size_t i = 0; i != m_count_ss.size(); i++) {m_count_ss[i]=0.0;}
    for (size_t i = 0; i != m_count_sf.size(); i++) {m_count_sf[i]=0.0;}
    for (size_t i = 0; i != m_count_df.size(); i++) {m_count_df[i]=0.0;}
    for (size_t i = 0; i != m_count_os.size(); i++) {m_count_os[i]=0.0;}

    // fake and flip rate binning
    m_fr_bin_info = GetFakeRateBinInfo();
    m_fl_bin_info = GetFlipRateBinInfo();

    // begin job
    BeginJob();
}

// destroy:
InterpLooper::~InterpLooper()
{
}
        
// methods:
void InterpLooper::BeginJob()
{
    // book the histograms
    BookHists();
}

//void SetFakePredictionAndUncertainty(rt::TH1Container& hc, const string& hist_stem, const string& title, float fr_sys_unc)
//{
//    const string sf_name = Form("h_%s_sf"  , hist_stem.c_str());
//    const string df_name = Form("h_%s_df"  , hist_stem.c_str());
//    const string fk_name = Form("h_%s_fake", hist_stem.c_str());
//
//    // fakes 
//    hc.Add(dynamic_cast<TH1*>(hc[sf_name]->Clone(fk_name.c_str()))); 
//    hc[fk_name]->Add(hc[df_name], -1.0);
//    hc[fk_name]->SetTitle(title.c_str());
//    rt::SetSystematicUncertainty(hc[fk_name], fr_sys_unc);
//}
//
//void SetFlipPredictionAndUncertainty(rt::TH1Container& hc, const string& hist_stem, const string& title, float fl_sys_unc, float fl_scale_factor = 1.0)
//{
//    const string os_name = Form("h_%s_os"  , hist_stem.c_str());
//    const string fl_name = Form("h_%s_flip", hist_stem.c_str());
//
//    // fakes 
//    hc.Add(dynamic_cast<TH1*>(hc[os_name]->Clone(fl_name.c_str()))); 
//    hc[fl_name]->Scale(fl_scale_factor);
//    hc[fl_name]->SetTitle(title.c_str());
//    rt::SetSystematicUncertainty(hc[fl_name], fl_sys_unc);
//}
//
//void SetMCPredictionAndUncertainty(rt::TH1Container& hc, const string& hist_stem, const string& title, float mc_sys_unc)
//{
//    const string ss_name = Form("h_%s_ss"  , hist_stem.c_str());
//
//    // fakes 
//    hc[ss_name]->SetTitle(title.c_str());
//    rt::SetSystematicUncertainty(hc[ss_name], mc_sys_unc);
//}
//
//void SetPredictionAndUncertainty
//(
//    const at::Sample::value_type sample,
//    rt::TH1Container& hc, 
//    const std::string& hist_stem, 
//    const std::string& title, 
//    float fr_sys_unc, 
//    float fl_sys_unc, 
//    float mc_sys_unc, 
//    float fl_scale_factor
//)
//{
//    string fake_title = rt::string_replace_all(title, "(X)", "(fake)");
//    string flip_title = rt::string_replace_all(title, "(X)", "(flip)");
//    string mc_title   = rt::string_replace_all(title, "(X)", "(MC)"  );
//    fake_title = rt::string_replace_all(title, "(X,", "(fake,");
//    flip_title = rt::string_replace_all(title, "(X,", "(flip,");
//    mc_title   = rt::string_replace_all(title, "(X,", "(MC,"  );
//    SetFakePredictionAndUncertainty(hc, hist_stem, fake_title, fr_sys_unc);
//    SetFlipPredictionAndUncertainty(hc, hist_stem, flip_title, fl_sys_unc, fl_scale_factor);
//    if (sample != at::Sample::data)
//    {
//        SetMCPredictionAndUncertainty(hc, hist_stem, mc_title, mc_sys_unc);
//    }
//}


// end job
void InterpLooper::EndJob()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    if (m_verbose)
    {
        hc.List();
    }
    cout << "\nScale1fb = "           << m_scale1fb << endl;
    cout << "Num Events Generated = " << m_nevts << endl;

//    // set the error to the lumi*scale1fb if the yield < weight*0.5 
//    if (m_sample != at::Sample::data)
//    {
//        const float weight = (m_lumi * m_scale1fb);
//        hc["h_yield_mm"]->SetBinError(2, weight * rt::GetClopperPearsonUncertainty(static_cast<int>(hc["h_yield_mm"]->GetEntries()), m_nevts));
//        hc["h_yield_ee"]->SetBinError(2, weight * rt::GetClopperPearsonUncertainty(static_cast<int>(hc["h_yield_ee"]->GetEntries()), m_nevts));
//        hc["h_yield_em"]->SetBinError(2, weight * rt::GetClopperPearsonUncertainty(static_cast<int>(hc["h_yield_em"]->GetEntries()), m_nevts));
//        hc["h_yield_ll"]->SetBinError(2, weight * rt::GetClopperPearsonUncertainty(static_cast<int>(hc["h_yield_ll"]->GetEntries()), m_nevts));
//
//        // yields in a signal used for overlaying
//        hc["h_yield_ss"]->SetBinError(2, weight * rt::GetClopperPearsonUncertainty(static_cast<int>(hc["h_yield_ss"]->GetEntries()), m_nevts));
//        hc["h_yield_ss"]->SetBinError(3, weight * rt::GetClopperPearsonUncertainty(static_cast<int>(hc["h_yield_ss"]->GetEntries()), m_nevts));
//        hc["h_yield_ss"]->SetBinError(4, weight * rt::GetClopperPearsonUncertainty(static_cast<int>(hc["h_yield_ss"]->GetEntries()), m_nevts));
//        hc["h_yield_ss"]->SetBinError(5, weight * rt::GetClopperPearsonUncertainty(static_cast<int>(hc["h_yield_ss"]->GetEntries()), m_nevts));
//    }
//
//    // 0 ee, 1 mm, 2 em, 3 ll
//    std::tr1::array<float, 4> yield_ss;
//    yield_ss[0] = rt::Integral(hc["h_yield_mm"]);
//    yield_ss[1] = rt::Integral(hc["h_yield_ee"]);
//    yield_ss[2] = rt::Integral(hc["h_yield_em"]);
//    yield_ss[3] = rt::Integral(hc["h_yield_ll"]);
//
//
//    // Fake predictions
//    // -----------------------------------------------------------------------------//
//    at::FakeRatePrediction frp(h_mufr.get(), h_elfr.get());
//    frp.ComputeAllFakePredictions
//    (
//        static_cast<TH2F*>(hc["h_sf_elfo_pt_vs_eta_ee"]),
//        static_cast<TH2F*>(hc["h_sf_mufo_pt_vs_eta_mm"]),
//        static_cast<TH2F*>(hc["h_sf_elfo_pt_vs_eta_em"]),
//        static_cast<TH2F*>(hc["h_sf_mufo_pt_vs_eta_em"]),
//        static_cast<TH2F*>(hc["h_df_fo_pt_vs_eta_ee"  ]),
//        static_cast<TH2F*>(hc["h_df_fo_pt_vs_eta_mm"  ]),
//        static_cast<TH2F*>(hc["h_df_fo_pt_vs_eta_em"  ])
//    );
//
//    // SF (raw)
//    PredSummary sf_raw = frp.GetSingleFakePredictionRaw();
//    hc.Add(new TH1F("h_sf_pred_raw", "SF prediction, raw", 6, 0, 6));
//    hc["h_sf_pred_raw"]->SetBinContent(1, sf_raw.mm.value);
//    hc["h_sf_pred_raw"]->SetBinContent(2, sf_raw.ee.value);
//    hc["h_sf_pred_raw"]->SetBinContent(3, sf_raw.em.value);
//    hc["h_sf_pred_raw"]->SetBinContent(4, sf_raw.ll.value);
//    hc["h_sf_pred_raw"]->SetBinContent(5, sf_raw.em_mufo.value);
//    hc["h_sf_pred_raw"]->SetBinContent(6, sf_raw.em_elfo.value);
//    hc["h_sf_pred_raw"]->SetBinError(1, sf_raw.mm.error);
//    hc["h_sf_pred_raw"]->SetBinError(2, sf_raw.ee.error);
//    hc["h_sf_pred_raw"]->SetBinError(3, sf_raw.em.error);
//    hc["h_sf_pred_raw"]->SetBinError(4, sf_raw.ll.error);
//    hc["h_sf_pred_raw"]->SetBinError(5, sf_raw.em_mufo.error);
//    hc["h_sf_pred_raw"]->SetBinError(6, sf_raw.em_elfo.error);
//
//    // DF
//    PredSummary df = frp.GetDoubleFakePrediction();
//    hc.Add(new TH1F("h_df_pred", "DF prediction", 4, 0, 4));
//    hc["h_df_pred"]->SetBinContent(1, df.mm.value);
//    hc["h_df_pred"]->SetBinContent(2, df.ee.value);
//    hc["h_df_pred"]->SetBinContent(3, df.em.value);
//    hc["h_df_pred"]->SetBinContent(4, df.ll.value);
//    hc["h_df_pred"]->SetBinError(1, df.mm.error);
//    hc["h_df_pred"]->SetBinError(2, df.ee.error);
//    hc["h_df_pred"]->SetBinError(3, df.em.error);
//    hc["h_df_pred"]->SetBinError(4, df.ll.error);
//
//    // SF 
//    PredSummary sf = frp.GetSingleFakePrediction();
//    hc.Add(new TH1F("h_sf_pred", "SF prediction", 4, 0, 4));
//    hc["h_sf_pred"]->SetBinContent(1, sf.mm.value);
//    hc["h_sf_pred"]->SetBinContent(2, sf.ee.value);
//    hc["h_sf_pred"]->SetBinContent(3, sf.em.value);
//    hc["h_sf_pred"]->SetBinContent(4, sf.ll.value);
//    hc["h_sf_pred"]->SetBinError(1, sf.mm.error);
//    hc["h_sf_pred"]->SetBinError(2, sf.ee.error);
//    hc["h_sf_pred"]->SetBinError(3, sf.em.error);
//    hc["h_sf_pred"]->SetBinError(4, sf.ll.error);
//
//    // Fakes 
//    PredSummary fake = frp.GetFakePrediction();
//    hc.Add(new TH1F("h_fake_pred", "fake prediction", 4, 0, 4));
//    hc["h_fake_pred"]->SetBinContent(1, fake.mm.value);
//    hc["h_fake_pred"]->SetBinContent(2, fake.ee.value);
//    hc["h_fake_pred"]->SetBinContent(3, fake.em.value);
//    hc["h_fake_pred"]->SetBinContent(4, fake.ll.value);
//    hc["h_fake_pred"]->SetBinError(1, fake.mm.error);
//    hc["h_fake_pred"]->SetBinError(2, fake.ee.error);
//    hc["h_fake_pred"]->SetBinError(3, fake.em.error);
//    hc["h_fake_pred"]->SetBinError(4, fake.ll.error);
//
//    // Flip predictions
//    // -----------------------------------------------------------------------------//
//
//    FlipRatePrediction flp(h_flip.get(), m_lumi);
//    flp.ComputeAllFlipPredictions
//    (
//        static_cast<TH2F*>(hc["h_os_fo_pt_vs_eta_ee"]),
//        static_cast<TH2F*>(hc["h_os_fo_pt_vs_eta_em"])
//    );
//
//    // Flip 
//    PredSummary flip = flp.GetFlipPrediction(m_sf_flip);
//    hc.Add(new TH1F("h_flip_pred", "flip prediction", 4, 0, 4));
//    hc["h_flip_pred"]->SetBinContent(1, flip.mm.value);
//    hc["h_flip_pred"]->SetBinContent(2, flip.ee.value);
//    hc["h_flip_pred"]->SetBinContent(3, flip.em.value);
//    hc["h_flip_pred"]->SetBinContent(4, flip.ll.value);
//    hc["h_flip_pred"]->SetBinError(1, flip.mm.error);
//    hc["h_flip_pred"]->SetBinError(2, flip.ee.error);
//    hc["h_flip_pred"]->SetBinError(3, flip.em.error);
//    hc["h_flip_pred"]->SetBinError(4, flip.ll.error);
//
//    // SS kinematic plots (prediction and systematic uncertainty)
//    // -----------------------------------------------------------------------------//
//
//    // This is an approximation.
//    // This does not have the full fake and flip rate errors' propogated properly.
//    // This is a small effect and is ignored in the plots since they cannot be seen easily 
//    // with the naked eye.
//    SetPredictionAndUncertainty(m_sample, hc, "nvtxs"         ,"# vtxs (X); #vtxs;Events"                                             , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "dilep_mass"    ,"Dilepton Mass (X); M_{ll} (GeV);Events"                               , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "dilep_mass_nj0","Dilepton Mass (X, # jets=0); M_{ll} (GeV);Events"                     , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "dilep_mass_nj1","Dilepton Mass (X, # jets=1); M_{ll} (GeV);Events"                     , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "dilep_mass_nj2","Dilepton Mass (X, # jets#geq2); M_{ll} (GeV);Events"                  , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "pt1"           ,"Higher p_{T} lepton (X);p_{T} (GeV);Events"                           , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "pt2"           ,"Lower p_{T} lepton (X);p_{T} (GeV);Events"                            , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "pt1_el"        ,"Higher p_{T} electron (X);p_{T} (GeV);Events"                         , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "pt2_el"        ,"Lower p_{T} electron (X);p_{T} (GeV);Events"                          , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "pt1_mu"        ,"Higher p_{T} electron (X);p_{T} (GeV);Events"                         , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "pt2_mu"        ,"Lower p_{T} electron (X);p_{T} (GeV);Events"                          , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "ht"            ,"H_{T};H_{T} (GeV) (X);Events"                                         , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "mt"            ,"m_{T};m_{T} (GeV) (X);Events"                                         , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "met"           ,"MET;E_{T}^{miss} (GeV) (X);Events"                                    , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "nbtags"        ,"# btags;# btags (X);Events"                                           , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "njets"         ,"# jets (X);# jets;Events"                                             , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "lepdphi"       ,"#Delta#Phi(lep1,lep2) (X);Delta#Phi(lep1,lep2);Events"                , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "lepdeta"       ,"#Delta#eta(lep1,lep2) (X);Delta#eta(lep1,lep2);Events"                , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "lepdr"         ,"#DeltaR(lep1,lep2) (X);#DeltaR(lep1,lep2);Events"                     , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "drlepb"        ,"#DeltaR(lep,btag) (X);#DeltaR(lep,btag);Events"                       , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "btagdr"        ,"#DeltaR(btag1,btag2) (X);#DeltaR(btag1,btag2);Events"                 , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "drjetb"        ,"#DeltaR(btag,jet) (X);#DeltaR(btag,jet);Events"                       , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "ptjetlep"      ,"p_{T}^{jet}/p)_{T}^{lep} - 1 (X);p_{T}^{jet}/p)_{T}^{lep} - 1;Events" , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "drlep3rdlep"   ,"#DeltaR(lep, 3rd lep) (X);#DeltaR(lep,lep3);Events"                   , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    SetPredictionAndUncertainty(m_sample, hc, "ml3l"          ,"M(lep, 3rd lep) (X);M(l,3l);Events"                                   , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//
//    for (size_t i = 1; i != at::DileptonHypType::static_size; i++)
//    {
//        at::DileptonHypType::value_type hyp_type = static_cast<at::DileptonHypType::value_type>(i);
//
//        // name and title suffixes
//        string hn = Form("_%s" ,  GetDileptonHypTypeName(hyp_type).c_str());
//        string ht = Form(" (%s)",  GetDileptonHypTypeTitle(hyp_type).c_str());
//
//        SetPredictionAndUncertainty(m_sample, hc, "dilep_mass"+hn, Form("Dilepton Mass (X, %s); M_{ll} (GeV);Events"    ,ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//        SetPredictionAndUncertainty(m_sample, hc, "pt1"       +hn, Form("Higher p_{T} lepton (X, %s);p_{T} (GeV);Events",ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//        SetPredictionAndUncertainty(m_sample, hc, "pt2"       +hn, Form("Lower p_{T} lepton (X, %s);p_{T} (GeV);Events" ,ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//        SetPredictionAndUncertainty(m_sample, hc, "ht"        +hn, Form("H_{T};H_{T} (GeV) (X, %s);Events"              ,ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//        SetPredictionAndUncertainty(m_sample, hc, "mt"        +hn, Form("m_{T};m_{T} (GeV) (X, %s);Events"              ,ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//        SetPredictionAndUncertainty(m_sample, hc, "met"       +hn, Form("MET;E_{T}^{miss} (GeV) (X, %s);Events"         ,ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//        SetPredictionAndUncertainty(m_sample, hc, "nbtags"    +hn, Form("# btags;# btags (X, %s);Events"                ,ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//        SetPredictionAndUncertainty(m_sample, hc, "njets"     +hn, Form("# jets (X, %s);# jets;Events"                  ,ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//
//        // plots for avi
//        SetPredictionAndUncertainty(m_sample, hc, "dilep_mass_nj0"+hn,Form("Dilepton Mass (X, %s, # jets=0); M_{ll} (GeV);Events"   ,ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//        SetPredictionAndUncertainty(m_sample, hc, "dilep_mass_nj1"+hn,Form("Dilepton Mass (X, %s, # jets=1); M_{ll} (GeV);Events"   ,ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//        SetPredictionAndUncertainty(m_sample, hc, "dilep_mass_nj2"+hn,Form("Dilepton Mass (X, %s, # jets#geq2); M_{ll} (GeV);Events",ht.c_str()), m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
//    }
//
//    // yield handled seperately
//    // this uses the full Fake and Flip rate production from above
//
//    // fakes 
//    hc.Add(dynamic_cast<TH1*>(hc["h_yield_sf"]->Clone("h_yield_fake"))); 
//    hc["h_yield_fake"]->SetTitle("fake prediction (with sys unc)");
//    hc["h_yield_fake"]->SetBinContent(1, fake.mm.value);
//    hc["h_yield_fake"]->SetBinContent(2, fake.ee.value);
//    hc["h_yield_fake"]->SetBinContent(3, fake.em.value);
//    hc["h_yield_fake"]->SetBinContent(4, fake.ll.value);
//    hc["h_yield_fake"]->SetBinError  (1, sqrt(m_fr_unc*m_fr_unc*fake.mm.value*fake.mm.value + fake.mm.error*fake.mm.error));
//    hc["h_yield_fake"]->SetBinError  (2, sqrt(m_fr_unc*m_fr_unc*fake.ee.value*fake.ee.value + fake.ee.error*fake.ee.error));
//    hc["h_yield_fake"]->SetBinError  (3, sqrt(m_fr_unc*m_fr_unc*fake.em.value*fake.em.value + fake.em.error*fake.em.error));
//    hc["h_yield_fake"]->SetBinError  (4, sqrt(m_fr_unc*m_fr_unc*fake.ll.value*fake.ll.value + fake.ll.error*fake.ll.error));
//
//    // flips
//    hc.Add(dynamic_cast<TH1*>(hc["h_yield_os"]->Clone("h_yield_flip"))); 
//    hc["h_yield_flip"]->SetTitle("flip prediction (with sys unc)");
//    hc["h_yield_flip"]->SetBinContent(1, flip.mm.value);
//    hc["h_yield_flip"]->SetBinContent(2, flip.ee.value);
//    hc["h_yield_flip"]->SetBinContent(3, flip.em.value);
//    hc["h_yield_flip"]->SetBinContent(4, flip.ll.value);
//    hc["h_yield_flip"]->SetBinError  (1, sqrt(m_fl_unc*m_fl_unc*flip.mm.value*flip.mm.value + flip.mm.error*flip.mm.error));
//    hc["h_yield_flip"]->SetBinError  (2, sqrt(m_fl_unc*m_fl_unc*flip.ee.value*flip.ee.value + flip.ee.error*flip.ee.error));
//    hc["h_yield_flip"]->SetBinError  (3, sqrt(m_fl_unc*m_fl_unc*flip.em.value*flip.em.value + flip.em.error*flip.em.error));
//    hc["h_yield_flip"]->SetBinError  (4, sqrt(m_fl_unc*m_fl_unc*flip.ll.value*flip.ll.value + flip.ll.error*flip.ll.error));
//
//    // mc (fold in the systematic uncertainty)
//    if (m_sample != at::Sample::data)
//    {
//        SetMCPredictionAndUncertainty(hc, "yield", "yield (MC);yield;Events", m_mc_unc);
//    }
//
//
//    // print the output
//    // -----------------------------------------------------------------------------//
//
//    CTable t_yields;
//    t_yields.useTitle();
//    t_yields.setTitle("yields table");
//    string f = "1.3";
//    t_yields.setTable() (                      "mm",            "ee",            "em",                "ll")
//                        ("SF raw" , sf_raw.mm.str(f), sf_raw.ee.str(f), sf_raw.em.str(f), sf_raw.ll.str(f))
//                        ("SF"     ,     sf.mm.str(f),     sf.ee.str(f),     sf.em.str(f),     sf.ll.str(f))
//                        ("DF"     ,     df.mm.str(f),     df.ee.str(f),     df.em.str(f),     df.ll.str(f))
//                        ("Fakes"  ,   fake.mm.str(f),   fake.ee.str(f),   fake.em.str(f),   fake.ll.str(f))
//                        ("Flips"  ,             "NA",   flip.ee.str(f),   flip.em.str(f),   flip.ll.str(f))
//                        ("yield"  ,      yield_ss[0],      yield_ss[1],      yield_ss[2],      yield_ss[3]);
//    cout << endl;
//    t_yields.print();
//
//    // print the output
//    CTable t_em_breakdown;
//    t_em_breakdown.useTitle();
//    t_em_breakdown.setTitle("SF breakdown table");
//    t_em_breakdown.setTable() (                                       "pred")
//                              ("SF raw ee"           , sf_raw.ee.str(f)     )
//                              ("SF raw mm"           , sf_raw.mm.str(f)     )
//                              ("SF raw em"           , sf_raw.em.str(f)     )
//                              ("SF raw em (mu fake)" , sf_raw.em_mufo.str(f))
//                              ("SF raw em (el fake)" , sf_raw.em_elfo.str(f))
//                              ("SF raw ll"           , sf_raw.ll.str(f)     );
//    cout << endl;
//    t_em_breakdown.print();


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
void InterpLooper::BookHists()
{
    try
    {
        // convenience alias
        rt::TH1Container& hc = m_hist_container;
        TH1::SetDefaultSumw2(true);

        hc.Add(new TH1F("h_lumi", "integrated lumi used for these plots", 10000, 0, 100));

        // Prefix comes from the sample and it is passed to the scanning function
        // Suffix is "ee" "em" "em" "all" which depends on the final state
        // For example: histogram named tt_hnJet_ee would be the Njet distribution
        // for the ee final state in the ttbar sample.
        // MAKE SURE TO CAL SUMW2 FOR EACH 1D HISTOGRAM BEFORE FILLING!!!!!!
        SignalBinInfo bin_info = GetSignalBinInfo(m_sample);
        hc.Add(new TH2F("h_den"                , "h_den"                , bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_den_unweighted"     , "h_den_unweighted"     , bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_den_total_weighted" , "h_den_total_weighted" , bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_num"                , "h_num"                , bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_eff"                , "h_eff"                , bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_syst"               , "h_syst"               , bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_syst_jec"           , "h_syst_jec"           , bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_syst_btag"          , "h_syst_btag"          , bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_jup"                , "h_jup"                , bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_jdown"              , "h_jdown"              , bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_bup"                , "h_bup"                , bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_exp"                , "h_exp"                , bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_obs"                , "h_obs"                , bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_sf"                 , "h_sf"                 , bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_df"                 , "h_df"                 , bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_fakes"              , "h_fakes"              , bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));    

        return;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }
}

// main analysis function operator 
int InterpLooper::operator()(long event)
{
    using namespace std;
    using namespace ssb;

    try
    {
        // base analysis
        at::AnalysisWithHist::operator()(event);

        // convenience alias
        rt::TH1Container& hc = m_hist_container;

        // scale 1b (set before cuts) 
        m_scale1fb = scale1fb();
        m_nevts    = static_cast<int>((xsec()*1000)/scale1fb());

        // print susy point for the event
        if (m_verbose)
        {
            cout << "SUSY point:" << endl; 
            if (sparm0_name().Length()>0) {cout << Form("%s = %1.2f", sparm0_name().Data(), sparm0()) << endl;}
            if (sparm1_name().Length()>0) {cout << Form("%s = %1.2f", sparm1_name().Data(), sparm1()) << endl;}
            if (sparm2_name().Length()>0) {cout << Form("%s = %1.2f", sparm2_name().Data(), sparm2()) << endl;}
            if (sparm3_name().Length()>0) {cout << Form("%s = %1.2f", sparm3_name().Data(), sparm3()) << endl;}
            cout << endl;
        }

        float mchi, m0, m12, mlsp;
        switch(m_sample)
        {
            case Sample::t1tttt:
                m0   = sparm0();
                m12  = sparm1();
                mlsp = sparm1();
                break;
            case Sample::sbottomtop:
                m0   = sparm0();
                m12  = sparm1();
                mchi = sparm1();
                mlsp = sparm2();
                break;
            case Sample::glusbottom:
                m0   = sparm0();
                m12  = sparm1();
                mchi = sparm2();
                mlsp = sparm3();
                break;
            case Sample::glustop:
                m0   = sparm0();
                m12  = sparm1();
                mchi = sparm2();
                mlsp = sparm2();
                break;
            default:
                m0   = -999999.0; 
                m12  = -999999.0;
                mchi = -999999.0;
                mlsp = -999999.0;
        }


        // selections 
        // ---------------------------------------------------------------------------------------------------------------------------- //

        // selected sparms 

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

        // no scale factors
        //const float evt_weight = (is_real_data() ? 1.0 : m_lumi * scale1fb());
        float weight = 1.0; 

        // scale
        //float vtxw = 1.0;
        //if (m_do_vtx_reweight)
        //{
        //    vtxw = is_real_data() ? 1.0 : vtxweight_n(nvtxs(), is_real_data(), false);
        //}
        //m_lumi = is_real_data() ? 1.0 : m_lumi;
        ////float evt_weight = m_lumi * scale1fb() * vtxw;
        //float evt_weight = m_lumi * vtxw;

        //// T1tttt is not scaled properly (need make this automatic) 
        //if (m_sample == at::Sample::t1tttt || m_sample == at::Sample::t1tttt_fastsim)
        //{
        //    if (rt::is_equal(sparm0(), 900.0f)) {evt_weight *= (0.060276 *1000)/10000.0;}
        //    if (rt::is_equal(sparm0(), 950.0f)) {evt_weight *= (0.0381246*1000)/10000.0;}
        //}
        //// SBottomTop is not scaled properl (need make this automatic)
        //else if (m_sample == at::Sample::sbottomtop)
        //{
        //    //evt_weight /= scale1fb();
        //    if (rt::is_equal(sparm0(), 460.0f)) {evt_weight *= (0.152*1000)/10000.0;}
        //    if (rt::is_equal(sparm0(), 380.0f)) {evt_weight *= (0.506*1000)/10000.0;}
        //}
        //else
        //{
        //    evt_weight *= scale1fb();
        //}

        //// apply scale factors
        //if (m_do_scale_factors && !is_real_data())
        //{
        //    evt_weight *= sf_lepeff();
        //    // evt_weight *= sf_dileptrig();  // applying trigger cut now on MC
        //    evt_weight *= dilepTriggerScaleFactor(hyp_type);  // applying trigger with scale factor 
        //    if (m_nbtags>=2)
        //    {
        //        if (m_signal_region == SignalRegion::sr7)
        //        {
        //            evt_weight *= (nbtags() >= 3 ? sf_nbtag3() : 1.0);
        //        }
        //        else
        //        {
        //            evt_weight *= (nbtags() >= 2 ? sf_nbtag() : 1.0);
        //        }
        //    }
        //}

        // Fill hists
        // ------------------------------------------------------------------------------------//

        // fill denominator
        rt::Fill2D(hc["h_den"           ], m0, m12, weight);
        rt::Fill2D(hc["h_den_unweighted"], m0, m12, 1.0   );

        if (is_ss()) 
        {
            if (PassesSignalRegion(m_signal_region, m_analysis_type, m_signal_region_type, YieldType::base))
            {
                rt::Fill2D(hc["h_num"], m0, m12, weight);
                //rt::Fill2D(hc["h_bup"], m0, m12, weight * sf_unc_nbtag());
                rt::Fill2D(hc["h_bup"], m0, m12, weight);
            }

            if (PassesSignalRegion(m_signal_region, m_analysis_type, m_signal_region_type, YieldType::up))
            {
                const float new_btag_sf = 1.0; //GetBtagScaleFactor(nbtags_up(), signal_region);
                rt::Fill2D(hc["h_jup"], m0, m12, weight * new_btag_sf);
            }

            if (PassesSignalRegion(m_signal_region, m_analysis_type, m_signal_region_type, YieldType::down))
            {
                const float new_btag_sf = 1.0; //GetBtagScaleFactor(nbtags_dn(), signal_region);
                rt::Fill2D(hc["h_jdown"], m0, m12, weight * new_btag_sf);
            }

        }
        else if (is_sf())
        {
            if (PassesSignalRegion(m_signal_region, m_analysis_type, m_signal_region_type, YieldType::base))
            {
                const float fr1 = lep1_is_fo() * GetFakeRateValue(lep1_pdgid(), lep1_p4().pt(), lep1_p4().eta());
                const float fr2 = lep2_is_fo() * GetFakeRateValue(lep2_pdgid(), lep2_p4().pt(), lep2_p4().eta());
                const float sf_weight = fr1/(1.0 - fr1) + fr2/(1.0 - fr2); 
                rt::Fill2D(hc["h_sf"], m0, m12, weight * sf_weight);
            }
        }
        else if (is_df())
        {
            if (PassesSignalRegion(m_signal_region, m_analysis_type, m_signal_region_type, YieldType::base))
            {
                const float fr1 = GetFakeRateValue(lep1_pdgid(), lep1_p4().pt(), lep1_p4().eta());
                const float fr2 = GetFakeRateValue(lep2_pdgid(), lep2_p4().pt(), lep2_p4().eta());
                const float df_weight = fr1/(1.0 - fr1) * fr2/(1.0 - fr2); 
                rt::Fill2D(hc["h_df"], m0, m12, weight * df_weight);
            }
        }

        // done with event loop
    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
    }

    // analysis end
    return 0;
} 

float InterpLooper::GetFakeRateValue(int lep_id, float pt, float eta) const 
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

float InterpLooper::GetFakeRateError(int lep_id, float pt, float eta) const 
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

float InterpLooper::GetFlipRateValue(int lep_id, float pt, float eta) const 
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

float InterpLooper::GetFlipRateError(int lep_id, float pt, float eta) const 
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

at::FakeRateBinInfo InterpLooper::GetFakeRateBinInfo() const
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

at::FlipRateBinInfo InterpLooper::GetFlipRateBinInfo() const
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

//float GetBtagScaleFactor(int nbjets, enum SignalRegion signal_region)
//{    
//    return btagEventWeight(std::min(nbjets,4), 200., 200., 200., 200., true);
//}

