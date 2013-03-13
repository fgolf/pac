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
    const std::string& den_hist_file_name,
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

    // denominator hist
    //std::auto_ptr<TFile> den_hist_file(rt::OpenRootFile(den_hist_file_name));
    //cout << "using den hist file : " << den_hist_file->GetName() << endl;
    //h_den.reset(dynamic_cast<TH2F*>(den_hist_file->Get("h_gen_count")->Clone("h_den")));
    //if (not h_den) {throw std::runtime_error("ERROR: InterpLooper: h_den doesn't exist");}
    //h_den->SetDirectory(0);

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

// end job
void InterpLooper::EndJob()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    if (m_verbose)
    {
        hc.List();
    }

    // Get the systematic uncertainty
    SetTotalSystematic();

    // Calcluate Efficiency
    CalculateEfficiency();

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
}

// book hists 
void InterpLooper::BookHists()
{
    try
    {
        // convenience alias
        rt::TH1Container& hc = m_hist_container;

        // add denominator count
        //hc.Add(dynamic_cast<TH2F*>(h_den->Clone()));

        // integrated liminositry
        hc.Add(new TH1F("h_lumi", "integrated lumi used for these plots", 10000, 0, 100));

        // Prefix comes from the sample and it is passed to the scanning function
        // Suffix is "ee" "em" "em" "all" which depends on the final state
        // For example: histogram named tt_hnJet_ee would be the Njet distribution
        // for the ee final state in the ttbar sample.
        // MAKE SURE TO CAL SUMW2 FOR EACH 1D HISTOGRAM BEFORE FILLING!!!!!!
        TH1::SetDefaultSumw2(true);

        // bin and label the axes
        SignalBinInfo bin_info = GetSignalBinInfo(m_sample);
        const string bin_label = GetSignalBinHistLabel(m_sample);

        hc.Add(new TH2F("h_den"                , ("h_den "           + bin_label).c_str(), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_den_unweighted"     , ("h_den_unweighted "+ bin_label).c_str(), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_num"                , ("h_num "           + bin_label).c_str(), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_jup"                , ("h_jup "           + bin_label).c_str(), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_jdown"              , ("h_jdown "         + bin_label).c_str(), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_bup"                , ("h_bup "           + bin_label).c_str(), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_bdown"              , ("h_bdown "         + bin_label).c_str(), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_sf"                 , ("h_sf "            + bin_label).c_str(), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_df"                 , ("h_df "            + bin_label).c_str(), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_fakes"              , ("h_fakes "         + bin_label).c_str(), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));    
        hc.Add(new TH2F("h_eff"                , ("h_eff "           + bin_label).c_str(), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_syst"               , ("h_syst "          + bin_label).c_str(), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_syst_jec"           , ("h_syst_jec "      + bin_label).c_str(), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_syst_btag"          , ("h_syst_btag "     + bin_label).c_str(), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_syst_met"           , ("h_syst_met "      + bin_label).c_str(), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_exp"                , ("h_exp "           + bin_label).c_str(), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc.Add(new TH2F("h_obs"                , ("h_obs "           + bin_label).c_str(), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));

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
        m_nevts    = nevts();

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
           
        // dilepton hyp type: 1 mm, 2 em, 3 ee
        const at::DileptonHypType::value_type hyp_type = static_cast<at::DileptonHypType::value_type>(dilep_type());

        // Weight Factors
        // ----------------------------------------------------------------------------------------------------------------------------//

        // no scale factors
        //const float evt_weight = (is_real_data() ? 1.0 : m_lumi * scale1fb());
        float evt_weight = 1.0; 

        // scale
        float vtxw = 1.0;
        //if (m_do_vtx_reweight)
        //{
        //    vtxw = is_real_data() ? 1.0 : vtxweight_n(nvtxs(), is_real_data(), false);
        //}
        evt_weight *= vtxw;

        // apply scale factors
        if (m_do_scale_factors && not is_real_data())
        {
            // lepton efficiencies
            evt_weight *= DileptonTagAndProbeScaleFactor(lep1_pdgid(), lep1_p4(), lep2_pdgid(), lep2_p4());

            // trigger scale factor
            evt_weight *= DileptonTriggerScaleFactor(hyp_type, m_analysis_type, lep2_p4());  
        }

        // fill denominator (event vounts)
        // ---------------------------------------------------------------------------------------------------------------------------- //

        rt::Fill2D(hc["h_den"           ], m0, m12, evt_weight);
        rt::Fill2D(hc["h_den_unweighted"], m0, m12, 1.0       );

        // selections 
        // ---------------------------------------------------------------------------------------------------------------------------- //

        if (hyp_type == DileptonHypType::static_size)
        {
            if (m_verbose) {cout << "failing valid hyp type" << endl;}
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

        // only keep MC matched events (MC only)
        const bool true_ss_event = ((lep1_is_fromw()>0) && (lep2_is_fromw()>0) && (lep1_mc3id()*lep2_mc3id()>0));
        if (not true_ss_event)
        {
            if (m_verbose) {cout << "failing MC truth matching" << endl;}
            return 0;
        }

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

        // Fill hists
        // ------------------------------------------------------------------------------------//

        if (is_ss()) 
        {
            // unscaled numerator counts
            if (PassesSignalRegion(m_signal_region, m_analysis_type, m_signal_region_type, YieldType::base))
            {
                rt::Fill2D(hc["h_num"], m0, m12, evt_weight);
            }

            // JEC scale up/scale down
            if (PassesSignalRegion(m_signal_region, m_analysis_type, m_signal_region_type, /*JEC=*/YieldType::up))
            {
                rt::Fill2D(hc["h_jup"], m0, m12, evt_weight);
            }

            if (PassesSignalRegion(m_signal_region, m_analysis_type, m_signal_region_type, /*JEC=*/YieldType::down))
            {
                rt::Fill2D(hc["h_jdown"], m0, m12, evt_weight);
            }

            // Btag scale up/down
            if (PassesSignalRegion(m_signal_region, m_analysis_type, m_signal_region_type, /*JEC=*/YieldType::base, /*Btag=*/YieldType::up))
            {
                rt::Fill2D(hc["h_bup"], m0, m12, evt_weight);
            }

            if (PassesSignalRegion(m_signal_region, m_analysis_type, m_signal_region_type, /*JEC=*/YieldType::base, /*Btag=*/YieldType::down))
            {
                rt::Fill2D(hc["h_bdown"], m0, m12, evt_weight);
            }

        }
        else if (is_sf())
        {
            if (true_ss_event && PassesSignalRegion(m_signal_region, m_analysis_type, m_signal_region_type, YieldType::base))
            {
                const float fr1 = lep1_is_fo() * GetFakeRateValue(lep1_pdgid(), lep1_p4().pt(), lep1_p4().eta());
                const float fr2 = lep2_is_fo() * GetFakeRateValue(lep2_pdgid(), lep2_p4().pt(), lep2_p4().eta());
                const float sf_weight = fr1/(1.0 - fr1) + fr2/(1.0 - fr2); 
                rt::Fill2D(hc["h_sf"], m0, m12, evt_weight * sf_weight);
            }
        }
        else if (true_ss_event && is_df())
        {
            if (PassesSignalRegion(m_signal_region, m_analysis_type, m_signal_region_type, YieldType::base))
            {
                const float fr1 = GetFakeRateValue(lep1_pdgid(), lep1_p4().pt(), lep1_p4().eta());
                const float fr2 = GetFakeRateValue(lep2_pdgid(), lep2_p4().pt(), lep2_p4().eta());
                const float df_weight = fr1/(1.0 - fr1) * fr2/(1.0 - fr2); 
                rt::Fill2D(hc["h_df"], m0, m12, evt_weight * df_weight);
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

void InterpLooper::SetJESSystematic()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    unsigned int nbinsx = hc["h_num"]->GetNbinsX()+1;
    unsigned int nbinsy = hc["h_num"]->GetNbinsY()+1;
    for (unsigned int ix = 1; ix < nbinsx; ix++) 
    {
        for (unsigned int iy = 1; iy < nbinsy; iy++) 
        {
            const float num      = hc["h_num"  ]->GetBinContent(ix, iy);
            const float num_up   = hc["h_jup"  ]->GetBinContent(ix, iy);
            const float num_down = hc["h_jdown"]->GetBinContent(ix, iy);            
            const float den      = hc["h_den"  ]->GetBinContent(ix, iy);

            float jec_syst = 0.0f;
            if (den > 0 && num > 0) 
            {
                const float up   = fabs(num-num_up) / num;
                const float down = fabs(num-num_down) / num;
                jec_syst = std::max(up, down);              
            }
            hc["h_syst_jec"]->SetBinContent(ix, iy, jec_syst);
        }
    }
    return;
}

// NOT SURE if this is right -- ask FG
void InterpLooper::SetBtagSystematic()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    unsigned int nbinsx = hc["h_num"]->GetNbinsX()+1;
    unsigned int nbinsy = hc["h_num"]->GetNbinsY()+1;
    for (unsigned int ix = 1; ix < nbinsx; ix++)
    {
        for (unsigned int iy = 1; iy < nbinsy; iy++)
        {
            const float num      = hc["h_num"  ]->GetBinContent(ix, iy);
            const float num_up   = hc["h_bup"  ]->GetBinContent(ix, iy);
            const float num_down = hc["h_bdown"]->GetBinContent(ix, iy);            
            const float den      = hc["h_den"  ]->GetBinContent(ix, iy);

            float btag_syst = 0.0f;
            if (den > 0 && num > 0) 
            {
                const float up   = fabs(num-num_up) / num;
                const float down = fabs(num-num_down) / num;
                btag_syst = std::max(up, down);              
            }
            hc["h_syst_btag"]->SetBinContent(ix, iy, btag_syst);
        }
    }
    return;
}

void InterpLooper::SetTotalSystematic()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    SetJESSystematic();
    SetBtagSystematic();

    // taken as constant
    const double lumi = 0.045;
    const double lep  = 0.11;
    const double pdf  = 0.02;

    unsigned int nbinsx = hc["h_num"]->GetNbinsX()+1;
    unsigned int nbinsy = hc["h_num"]->GetNbinsY()+1;
    for (unsigned int ix = 1; ix < nbinsx; ix++)
    {
        for (unsigned int iy = 1; iy < nbinsy; iy++)
        {
            const float jes_syst  = hc["h_syst_jec" ]->GetBinContent(ix, iy);
            const float btag_syst = hc["h_syst_btag"]->GetBinContent(ix, iy);
            const float syst = std::sqrt(pow(lumi, 2) + pow(lep, 2) + pow(pdf, 2) + pow(jes_syst, 2) + pow(btag_syst, 2));
            hc["h_syst"]->SetBinContent(ix, iy, syst);

            if (m_verbose) {cout << "jes, btag, total: " << jes_syst << ", " << btag_syst << ", " << syst << endl;}
        }
    }
    return;
}

void InterpLooper::SetTotalSignalContamination()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    // Total signal contamination from fakes
    // total fakes = SF - DF
    hc["h_fakes"]->Add(hc["h_sf"], hc["h_df"], 1.0, -1.0);
    return;
}

void InterpLooper::CalculateEfficiency()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    // get signal contamination
    SetTotalSignalContamination();

    unsigned int nbinsx = hc["h_den_unweighted"]->GetNbinsX()+1;
    unsigned int nbinsy = hc["h_den_unweighted"]->GetNbinsY()+1;
    for (unsigned int ix = 1; ix < nbinsx; ix++)
    {
        for (unsigned int iy = 1; iy < nbinsy; iy++)
        {
            const float num   = hc["h_num"           ]->GetBinContent(ix, iy);
            const float fakes = hc["h_fakes"         ]->GetBinContent(ix ,iy);
            const float den   = hc["h_den_unweighted"]->GetBinContent(ix ,iy);

            if (den > 0.0) 
            {
                float eff = 0.0;
                if (num >= 0.0)
                {
                    eff = fabs(num - fakes) / den;  // central value of eps*A*BR
                }
                hc["h_eff"]->SetBinContent(ix, iy, eff);
            }
            else
            {
                hc["h_eff"]->SetBinContent(ix, iy, 0.0);
            }
        }
    }
    return;
}

//void makeTextFile::getUpperLimits (enum SignalRegion signal_region) {
//
//    unsigned int sid = (unsigned int)signal_region;
//    if (signal_region == HIGH_M0)
//        sid = (unsigned int)LOW_M0;
//    else if (signal_region == LOW_M0)
//        sid = (unsigned int)HIGH_M0;
//    sid++;
//    
//    unsigned int nbinsx = hsyst->GetNbinsX()+1;
//    unsigned int nbinsy = hsyst->GetNbinsY()+1;
//    for (unsigned int ix = 1; ix < nbinsx; ix++) {
//        for (unsigned int iy = 1; iy < nbinsy; iy++) {
//            
//            float syst = hsyst->GetBinContent(ix, iy);
//
//            float exp = getLimitSSb(sid, syst, false);
//            float obs = getLimitSSb(sid, syst, true);
//
//            hexp->SetBinContent(ix, iy, exp);
//            hobs->SetBinContent(ix, iy, obs);
//        }
//    }
//    
//    return;    
//}

