#include "PlotLooper.h"
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
    unsigned int num_btags,
    unsigned int num_jets,
    int charge_option,
    bool do_scale_factors,
    bool check_good_lumi,
    float sparm0,
    float sparm1,
    float sparm2,
    float sparm3,
    float sf_flip,
    float fr_unc,
    float fl_unc,
    float mc_unc,
    float lumi,
    float l1_min_pt,
    float l1_max_pt,
    float l2_min_pt,
    float l2_max_pt,
    float min_ht,
    bool verbose
)
    : at::AnalysisWithHist(root_file_name)
    , m_lumi(lumi)
    , m_verbose(verbose)
    , m_is_data(at::SampleIsData(sample))
    , m_do_vtx_reweight(not vtxreweight_file_name.empty())
    , m_do_scale_factors(do_scale_factors)
    , m_check_good_lumi(check_good_lumi)
    , m_nbtags(num_btags)
    , m_njets(num_jets)
    , m_charge_option(charge_option)
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
    , m_l1_min_pt(l1_min_pt)
    , m_l1_max_pt(l1_max_pt)
    , m_l2_min_pt(l2_min_pt)
    , m_l2_max_pt(l2_max_pt)
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
            //mufr_name = "h_mufr40c";
            //elfr_name = "h_elfr40c";
            break;
        case AnalysisType::high_pt_eth:
            mufr_name = "h_mufr50c";
            elfr_name = "h_elfr50c";
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
    if (not h_mufr) {throw std::runtime_error(Form("ERROR: PlotLooper: %s doesn't exist", mufr_name.c_str()));}
    if (not h_elfr) {throw std::runtime_error(Form("ERROR: PlotLooper: %s doesn't exist", elfr_name.c_str()));}
    h_mufr->SetDirectory(0);
    h_elfr->SetDirectory(0);

    cout << "using mu FR hist : " << h_mufr->GetName() << endl;
    cout << "using el FR hist : " << h_elfr->GetName() << endl;

    // set the fake rate histograms
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

    // set the error to the lumi*scale1fb if the yield < weight*0.5 
    if (m_sample != at::Sample::data)
    {
        float weight = (m_lumi * m_scale1fb);
        if (rt::Integral(hc["h_yield_mm"]) < (weight * 0.5)) {hc["h_yield_mm"]->SetBinError(2, weight);}
        if (rt::Integral(hc["h_yield_ee"]) < (weight * 0.5)) {hc["h_yield_ee"]->SetBinError(2, weight);}
        if (rt::Integral(hc["h_yield_em"]) < (weight * 0.5)) {hc["h_yield_em"]->SetBinError(2, weight);}
        if (rt::Integral(hc["h_yield_ll"]) < (weight * 0.5)) {hc["h_yield_ll"]->SetBinError(2, weight);}

        // yields in a signal used for overlaying
        cout << "wieght = " << weight << endl;
        if (hc["h_yield_ss"]->GetBinContent(2) < (weight * 0.5)) {hc["h_yield_ss"]->SetBinError(2, weight);}
        if (hc["h_yield_ss"]->GetBinContent(3) < (weight * 0.5)) {hc["h_yield_ss"]->SetBinError(3, weight);}
        if (hc["h_yield_ss"]->GetBinContent(4) < (weight * 0.5)) {hc["h_yield_ss"]->SetBinError(4, weight);}
        if (hc["h_yield_ss"]->GetBinContent(5) < (weight * 0.5)) {hc["h_yield_ss"]->SetBinError(5, weight);}
    }

    // 0 ee, 1 mm, 2 em, 3 ll
    std::tr1::array<float, 4> yield_ss;
    yield_ss[0] = rt::Integral(hc["h_yield_mm"]);
    yield_ss[1] = rt::Integral(hc["h_yield_ee"]);
    yield_ss[2] = rt::Integral(hc["h_yield_em"]);
    yield_ss[3] = rt::Integral(hc["h_yield_ll"]);


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
    SetPredictionAndUncertainty(m_sample, hc, "nvtxs"         ,"# vtxs (X); #vtxs;Events"                                             , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "dilep_mass"    ,"Dilepton Mass (X); M_{ll} (GeV);Events"                               , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "dilep_mass_nj0","Dilepton Mass (X, # jets=0); M_{ll} (GeV);Events"                     , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "dilep_mass_nj1","Dilepton Mass (X, # jets=1); M_{ll} (GeV);Events"                     , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "dilep_mass_nj2","Dilepton Mass (X, # jets#geq2); M_{ll} (GeV);Events"                  , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pt1"           ,"Higher p_{T} lepton (X);p_{T} (GeV);Events"                           , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pt2"           ,"Lower p_{T} lepton (X);p_{T} (GeV);Events"                            , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pt1_el"        ,"Higher p_{T} electron (X);p_{T} (GeV);Events"                         , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pt2_el"        ,"Lower p_{T} electron (X);p_{T} (GeV);Events"                          , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pt1_mu"        ,"Higher p_{T} electron (X);p_{T} (GeV);Events"                         , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "pt2_mu"        ,"Lower p_{T} electron (X);p_{T} (GeV);Events"                          , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "ht"            ,"H_{T};H_{T} (GeV) (X);Events"                                         , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "mt"            ,"m_{T};m_{T} (GeV) (X);Events"                                         , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "met"           ,"MET;E_{T}^{miss} (GeV) (X);Events"                                    , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "nbtags"        ,"# btags;# btags (X);Events"                                           , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "njets"         ,"# jets (X);# jets;Events"                                             , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "lepdphi"       ,"#Delta#Phi(lep1,lep2) (X);Delta#Phi(lep1,lep2);Events"                , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "lepdeta"       ,"#Delta#eta(lep1,lep2) (X);Delta#eta(lep1,lep2);Events"                , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "lepdr"         ,"#DeltaR(lep1,lep2) (X);#DeltaR(lep1,lep2);Events"                     , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "drlepb"        ,"#DeltaR(lep,btag) (X);#DeltaR(lep,btag);Events"                       , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "btagdr"        ,"#DeltaR(btag1,btag2) (X);#DeltaR(btag1,btag2);Events"                 , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "drjetb"        ,"#DeltaR(btag,jet) (X);#DeltaR(btag,jet);Events"                       , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "ptjetlep"      ,"p_{T}^{jet}/p)_{T}^{lep} - 1 (X);p_{T}^{jet}/p)_{T}^{lep} - 1;Events" , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "drlep3rdlep"   ,"#DeltaR(lep, 3rd lep) (X);#DeltaR(lep,lep3);Events"                   , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);
    SetPredictionAndUncertainty(m_sample, hc, "ml3l"          ,"M(lep, 3rd lep) (X);M(l,3l);Events"                                   , m_fr_unc, m_fl_unc, m_mc_unc, m_sf_flip);

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
    string f = "1.3";
    t_yields.setTable() (                      "mm",            "ee",            "em",                "ll")
                        ("SF raw" , sf_raw.mm.str(f), sf_raw.ee.str(f), sf_raw.em.str(f), sf_raw.ll.str(f))
                        ("SF"     ,     sf.mm.str(f),     sf.ee.str(f),     sf.em.str(f),     sf.ll.str(f))
                        ("DF"     ,     df.mm.str(f),     df.ee.str(f),     df.em.str(f),     df.ll.str(f))
                        ("Fakes"  ,   fake.mm.str(f),   fake.ee.str(f),   fake.em.str(f),   fake.ll.str(f))
                        ("Flips"  ,             "NA",   flip.ee.str(f),   flip.em.str(f),   flip.ll.str(f))
                        ("yield"  ,      yield_ss[0],      yield_ss[1],      yield_ss[2],      yield_ss[3]);
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
    //Pred y_sf_ee(rt::EntriesAndError(hc["h_sf_elfo_pt_vs_eta_ee"]));
    //Pred y_sf_em(rt::AddWithError(rt::EntriesAndError(hc["h_sf_elfo_pt_vs_eta_em"]), rt::EntriesAndError(hc["h_sf_mufo_pt_vs_eta_em"])));
    //Pred y_sf_mm(rt::EntriesAndError(hc["h_sf_mufo_pt_vs_eta_mm"]));
    //Pred y_df_ee(rt::EntriesAndError(hc["h_df_fo_pt_vs_eta_ee"]));
    //Pred y_df_em(rt::EntriesAndError(hc["h_df_fo_pt_vs_eta_mm"]));
    //Pred y_df_mm(rt::EntriesAndError(hc["h_df_fo_pt_vs_eta_em"]));
    //Pred y_os_ee(rt::EntriesAndError(hc["h_os_fo_pt_vs_eta_ee"]));
    //Pred y_os_em(rt::EntriesAndError(hc["h_os_fo_pt_vs_eta_em"]));
    //Pred y_os_mm(rt::EntriesAndError(hc["h_os_pt1_vs_eta1_mm"]));

    //PredSummary y_sf(y_sf_ee, y_sf_mm, y_sf_em);
    //PredSummary y_df(y_df_ee, y_df_mm, y_df_em);
    //PredSummary y_os(y_os_ee, y_os_mm, y_os_em);

    //CTable t_counts;
    //t_counts.useTitle();
    //t_counts.setTitle("counts table");
    //t_counts.setTable() (               "mm",          "ee",          "em",          "ll")
    //                    ("SF", y_sf.mm.value, y_sf.ee.value, y_sf.em.value, y_sf.ll.value)
    //                    ("DF", y_df.mm.value, y_df.ee.value, y_df.em.value, y_df.ll.value)
    //                    ("OS", y_os.mm.value, y_os.ee.value, y_os.em.value, y_os.ll.value)
    //                    ("SS",    yield_ss[0],  yield_ss[1],   yield_ss[2],   yield_ss[3]);
    //cout << endl;
    //t_counts.print();
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

// binning contants
std::tr1::array<float, 5> el_eta_bins      = {{0.0, 1.0, 1.479, 2.0, 2.5}};
std::tr1::array<float, 5> mu_eta_bins      = {{0.0, 1.0, 1.479, 2.0, 2.5}};
std::tr1::array<float, 6> el_pt_bins       = {{10.0, 15.0, 20.0, 25.0, 35.0, 55.0}};
std::tr1::array<float, 6> mu_pt_bins       = {{ 5.0, 10.0, 15.0, 20.0, 25.0, 35.0}};
std::tr1::array<float, 18> lep_pt_bins     = {{0.0, 5.0, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110.0, 120.0, 130.0, 140.0, 160.0, 200.0}};
//std::tr1::array<float, 9> mu_vtx_bins    = {{ 0.0,  3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0, 30.0}};
//std::tr1::array<float, 9> el_vtx_bins    = {{ 0.0,  3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0, 30.0}};
std::tr1::array<float, 9> el_flip_eta_bins = {{ 0.0, 0.5, 1.0, 1.479, 1.8, 2.0, 2.1, 2.2, 2.4 }};
std::tr1::array<float, 18> el_flip_pt_bins = {{ 10., 20., 25., 30., 35., 40., 45., 50., 55., 60., 65., 70., 75., 80., 85., 90., 95., 100. }};
std::tr1::array<float, 13>  ht_bins        = {{ 0, 100, 150, 200, 250, 300, 350, 400, 450, 500, 600, 700, 1000 }};
std::tr1::array<float, 6> met_bins         = {{ 0, 50, 100, 150, 200, 400 }};

// book hists 
void PlotLooper::BookHists()
{
    try
    {
        // convenience alias
        rt::TH1Container& hc = m_hist_container;
        TH1::SetDefaultSumw2(true);

        hc.Add(new TH1F("h_lumi", "integrated lumi used for these plots", 10000, 0, 100));

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
            hc.Add(new TH2F(Form("h_sf_mufo_pt_vs_eta%s", ns.c_str()), Form("#mu FO p_{T} vs |#eta|%s;|#eta|;p_{T} (GeV)"     , ts.c_str()),mu_eta_bins.size()-1,mu_eta_bins.data(),mu_pt_bins.size()-1,mu_pt_bins.data()));
            hc.Add(new TH2F(Form("h_sf_elfo_pt_vs_eta%s", ns.c_str()), Form("electron FO p_{T} vs |#eta|%s;|#eta|;p_{T} (GeV)", ts.c_str()),el_eta_bins.size()-1,el_eta_bins.data(),el_pt_bins.size()-1,el_pt_bins.data()));

            // DF plots
            hc.Add(new TH2F(Form("h_df_fo_pt_vs_eta%s", ns.c_str()), Form("DF FO (%s) (special binning)", ts.c_str()), 20, 0, 20, 20, 0, 20));
        }

        // OS plots (for flip pred)
        hc.Add(new TH2F("h_os_fo_pt_vs_eta_ee", "OS (ee ) (special binning)"                    , 136, 0, 136, 136, 0, 136)); 
        hc.Add(new TH2F("h_os_fo_pt_vs_eta_em", "OS (e#mu) p_{T} vs |#eta|;|#eta|;p_{T} (GeV)"  , el_flip_eta_bins.size()-1,el_flip_eta_bins.data(),el_flip_pt_bins.size()-1,el_flip_pt_bins.data()));

        hc.Add(new TH2F("h_os_pt1_vs_eta1_mm", "OS (#mu#mu) #mu1 p_{T} vs |#eta|;|#eta|;p_{T} (GeV)", el_flip_eta_bins.size()-1,el_flip_eta_bins.data(),el_flip_pt_bins.size()-1,el_flip_pt_bins.data()));
        hc.Add(new TH2F("h_os_pt2_vs_eta2_mm", "OS (#mu#mu) #mu2 p_{T} vs |#eta|;|#eta|;p_{T} (GeV)", el_flip_eta_bins.size()-1,el_flip_eta_bins.data(),el_flip_pt_bins.size()-1,el_flip_pt_bins.data()));

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

        // scale 1b (set before cuts) 
        m_scale1fb = scale1fb();
        //m_nevts    = nevts();       
        m_nevts    = -999999; 

        // which analysis type
        //bool is_high_pt = (m_analysis_type==ss::AnalysisType::high_pt);

        //  if (
        //        evt()==136681113  ||
        //        evt()==420345732  ||
        //        evt()==232659600  ||
        //        evt()==50299158   ||
        //        evt()==1016031539 ||
        //        evt()==582319467  ||
        //        evt()==333466094  ||
        //        evt()==421855042  ||
        //        evt()==946339219  ||
        //        evt()==979576990  ||
        //        evt()==621112830  ||
        //        evt()==178599734
        //       )
        //DileptonHypType::value_type hyp_type = static_cast<DileptonHypType::value_type>(dilep_type());
        //if (evt()==221637477)
        //{
        //    string channel;
        //    switch (hyp_type)
        //    {
        //        case DileptonHypType::MUMU : channel = "MuMu"; break;
        //        case DileptonHypType::EMU  : channel = "EMu" ; break;
        //        case DileptonHypType::EE   : channel = "EE"  ; break;
        //        default                    : channel = "none"; 
        //    }
        //    channel.append(":");
        //    //fout << Form("%-6s %-7u %-5u %-15u %-2u %-2u %-6.3f %-6.3f", channel.c_str(), run(), ls(), evt(), njets(), nbtags(), ht(), pfmet()) << endl;
        //      cout << "hyp_type = " << hyp_type << "\t" << channel << endl;
        //    cout << Form("%6u | %3u | %12u | %s | %d | %4.3f | %2.3f | %2.3f | %4.3f | %4.3f | %d | %4.3f | %2.3f | %2.3f | %4.3f | %4.3f | %4.3f | %4.3f | %u | %u",
        //           run(), ls(), evt(),
        //           channel.c_str(),
        //           lep1_pdgid(), lep1_p4().pt(), lep1_p4().eta(), lep1_p4().phi(), lep1_corpfiso(), lep1_d0(),
        //           lep2_pdgid(), lep2_p4().pt(), lep2_p4().eta(), lep2_p4().phi(), lep2_corpfiso(), lep2_d0(),
        //           pfmet(),
        //           ht(),
        //           njets(),
        //           nbtags()) << endl;
        //}
        //else
        //{
        //    return 0;
        //}

        // selections 
        // ---------------------------------------------------------------------------------------------------------------------------- //

        // only keep good lumi (data only) -- is_good_lumi branch not set
        if (m_check_good_lumi && is_real_data() && not is_good_lumi())
        {
            if (m_verbose) {cout << "faling good run list" << endl;}
            return 0;
        }

        // charge type
        DileptonChargeType::value_type charge_type = DileptonChargeType::static_size;
        if (is_ss()) {charge_type = DileptonChargeType::SS;}
        if (is_sf()) {charge_type = DileptonChargeType::SF;}
        if (is_df()) {charge_type = DileptonChargeType::DF;}
        if (is_os()) {charge_type = DileptonChargeType::OS;}
        if (charge_type == DileptonChargeType::static_size)
        {
            if (m_verbose) {cout << "failing valid charge type" << endl;}
            return 0;
        }

        // dilepton hyp type: 1 mm, 2 em, 3ee
        DileptonHypType::value_type hyp_type = static_cast<DileptonHypType::value_type>(dilep_type());
        if (hyp_type == DileptonHypType::static_size)
        {
            if (m_verbose) {cout << "failing valid hyp type" << endl;}
            return 0;
        }

        // lepton PT requirement
        if (lep2_p4().pt() < m_l2_min_pt || lep2_p4().pt() > m_l2_max_pt)
        {
            if (m_verbose) {cout << "failing minimum/maximum lep2 pT" << endl;}
            return 0;
        }
        if (lep1_p4().pt() < m_l1_min_pt || lep1_p4().pt() > m_l1_max_pt)
        {
            if (m_verbose) {cout << "failing minimum/maximum lep1 pT" << endl;}
            return 0;
        }

        // d0 requirement
        //if ((is_ss() || is_os()) && abs(lep1_d0()) > (abs(lep1_pdgid())==11 ? 0.01 : 0.005))
        //{
        //    if (m_verbose) {cout << "lep1 failing minimum d0 cut" << endl;}
        //    return 0;
        //}
        //if ((is_ss() || is_os()) && abs(lep2_d0()) > (abs(lep2_pdgid())==11 ? 0.01 : 0.005))
        //{
        //    if (m_verbose) {cout << "lep1 failing minimum d0 cut" << endl;}
        //    return 0;
        //}

        // ioslation
        //if (is_ss() && (lep1_corpfiso() > 0.08 || lep2_corpfiso() > 0.08))
        //{
        //    return 0;
        //}
        //if (is_sf() && ((lep1_is_num() && lep1_corpfiso() > 0.08) || (lep2_is_num() && lep2_corpfiso() > 0.08)))
        //{
        //    return 0;
        //}
        //if (is_os() && (lep1_corpfiso() > 0.08 || lep2_corpfiso() > 0.08))
        //{
        //    return 0;
        //}

        // MET
        //if (pfmet() < 30)
        //{
        //    return 0;
        //}

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
            if (m_verbose) {cout << "faling # jets cut" << endl;}
            return 0;
        }

        // two btagged jets
        if (nbtags() < static_cast<int>(m_nbtags))
        {
            if (m_verbose) {cout << "faling # btags cut" << endl;}
            return 0;
        }

        // passes signal region
        if (not PassesSignalRegion(m_signal_region, m_analysis_type, m_signal_region_type))
        {
            if (m_verbose) {cout << "faling signal region cut" << endl;}
            return 0;
        }

        // apply gamma*/upsilon veto
        //bool has_gamma_cand = false;
        //if (has_gamma_cand)
        //{
        //    return 0;
        //}

        // select m_gluino and m_lsp
        //if 
        //(
        //  m_sample == at::Sample::t1tttt || 
        //    m_sample == at::Sample::t1tttt_fastsim ||
        //    m_sample == at::Sample::sbottomtop
        //)
        //{
        //    if (!rt::is_equal(m_sparm0, sparm0()) || !rt::is_equal(m_sparm1, sparm1()))
        //    {
        //        return 0;
        //    }
        //}

        // ttbar breakdown 
        switch (m_sample)
        {
            case at::Sample::ttdil: if (ttbar_bkdn() != TTbarBreakDown::TTDIL) return 0; break; 
            case at::Sample::ttotr: if (ttbar_bkdn() != TTbarBreakDown::TTOTR) return 0; break;
            case at::Sample::ttslb: if (ttbar_bkdn() != TTbarBreakDown::TTSLB) return 0; break;
            case at::Sample::ttslo: if (ttbar_bkdn() != TTbarBreakDown::TTSLO) return 0; break;
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

        // no scale factors
        float evt_weight = is_real_data() ? 1.0 : m_lumi * scale1fb();

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

        // name and title suffixes
        string hs = Form("_%s", GetDileptonHypTypeName(hyp_type).c_str());
        string qs = Form("_%s", GetDileptonChargeTypeName(charge_type).c_str());
        const bool true_ss_event = not is_real_data() ? ((lep1_is_fromw()>0) && (lep2_is_fromw()>0) && (lep1_mc3id()*lep2_mc3id()>0)) : false;
        //const bool true_ss_event = true; 

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
                fout << Form("%6u | %3u | %12u | %s | %4.3f | %2.3f | %2.3f | %4.3f | %4.3f | %2.3f | %2.3f | %4.3f | %4.3f | %4.3f | %u | %u",
                     run(), ls(), evt(),
                     channel.c_str(),
                     lep1_p4().pt(), lep1_p4().eta(), lep1_p4().phi(), lep1_corpfiso(),
                     lep2_p4().pt(), lep2_p4().eta(), lep2_p4().phi(), lep2_corpfiso(),
                     pfmet(),
                     ht(),
                     njets(),
                     nbtags()) << endl;
            }
        }

        // SF 
        if (is_sf())
        {
            const LorentzVector& p4  = lep1_is_fo() ? lep1_p4()    : lep2_p4();
            const int id             = lep1_is_fo() ? lep1_pdgid() : lep2_pdgid();
            if (is_real_data() || (!is_real_data() && true_ss_event))
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
            if (is_real_data() || (!is_real_data() && true_ss_event))
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

            float weight = (m_signal_region != SignalRegion::sr2) ? evt_weight : 0.5*evt_weight;
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

        // dont't fill hists for MC if they are not truth matched (SS or DF only)
        if ((not is_real_data()) && (not true_ss_event) && (is_sf() || is_df()))
        {
            if (m_verbose) {cout << "leptons failing truth matching (MC only)" << endl;}
            return 0;
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

        rt::Fill(hc["h_nvtxs" +qs], nvtxs()     , evt_weight);
        rt::Fill(hc["h_pt1"   +qs], p41.pt()    , evt_weight);
        rt::Fill(hc["h_pt2"   +qs], p42.pt()    , evt_weight);
        rt::Fill(hc["h_ht"    +qs], ht()        , evt_weight);
        rt::Fill(hc["h_mt"    +qs], lep1_mt()   , evt_weight);
        rt::Fill(hc["h_met"   +qs], pfmet()     , evt_weight);
        rt::Fill(hc["h_nbtags"+qs], nbtags()    , evt_weight);
        rt::Fill(hc["h_njets" +qs], njets()     , evt_weight);

        rt::Fill(hc["h_pt1"   +hs+qs], p41.pt()    , evt_weight);
        rt::Fill(hc["h_pt2"   +hs+qs], p42.pt()    , evt_weight);
        rt::Fill(hc["h_ht"    +hs+qs], ht()        , evt_weight);
        rt::Fill(hc["h_mt"    +hs+qs], lep1_mt()   , evt_weight);
        rt::Fill(hc["h_met"   +hs+qs], pfmet()     , evt_weight);
        rt::Fill(hc["h_nbtags"+hs+qs], nbtags()    , evt_weight);
        rt::Fill(hc["h_njets" +hs+qs], njets()     , evt_weight);

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
