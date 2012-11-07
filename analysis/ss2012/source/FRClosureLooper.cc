#include "FRClosureLooper.h"
#include <iostream>
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

typedef std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > vecLorentzVector;

using namespace std;
using namespace at;
using namespace ss;

// construct:
FRClosureLooper::FRClosureLooper
(
    const std::string& root_file_name,
    at::Sample::value_type sample,
    SignalRegion::value_type signal_region,
    const std::string& vtxreweight_file_name,
    const std::string& fake_rate_file_name,
    const std::string& mufr_hist_name,
    const std::string& elfr_hist_name,
    bool do_scale_factors,
    unsigned int num_btags,
    unsigned int num_jets,
    int charge_option,
    float lumi,
    bool verbose
)
    : at::AnalysisWithHist(root_file_name, false, "")
    , m_lumi(lumi)
    , m_verbose(verbose)
    , m_is_data(at::SampleIsData(sample))
    , m_do_vtx_reweight(not vtxreweight_file_name.empty())
    , m_do_scale_factors(do_scale_factors)
    , m_nbtags(num_btags)
    , m_njets(num_jets)
    , m_charge_option(charge_option)
    , m_sample(sample)
    , m_signal_region(signal_region)
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
    h_mufr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get(mufr_hist_name.c_str())->Clone()));
    if (not h_mufr) {throw std::runtime_error(Form("ERROR: SSAnalysisLooper: %s doesn't exist", mufr_hist_name.c_str()));}
    h_mufr->SetDirectory(0);

    std::auto_ptr<TFile> elfr_file(rt::OpenRootFile("data/fake_rates/ssFR_data_standard_24Sep2012.root"));  // hard coded for now
    h_elfr.reset(dynamic_cast<TH2F*>(elfr_file->Get(elfr_hist_name.c_str())->Clone()));
    if (not h_elfr) {throw std::runtime_error(Form("ERROR: SSAnalysisLooper: %s doesn't exist", elfr_hist_name.c_str()));}
    h_elfr->SetDirectory(0);

    cout << "using mu FR hist : " << h_mufr->GetName() << endl;
    cout << "using el FR hist : " << h_elfr->GetName() << endl;

    // number of jets/btags
    cout << "Cutting on the number of jets/btags" << endl;
    cout << "nbtags >= " << m_nbtags << endl;
    cout << "njets  >= " << m_njets  << endl;

    // begin job
    BeginJob();
}

// destroy:
FRClosureLooper::~FRClosureLooper()
{
    // end  job
    EndJob();
}

// methods:
void FRClosureLooper::BeginJob()
{
    BookHists();
}

// end job
void FRClosureLooper::EndJob()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    if (m_verbose)
    {
        hc.List();
    }

    // 0 ee, 1 mm, 2 em, 3 ll
    std::tr1::array<float, 4> yield_ss;
    yield_ss[0] = rt::Integral(hc["h_yield_ee"]);
    yield_ss[1] = rt::Integral(hc["h_yield_mm"]);
    yield_ss[2] = rt::Integral(hc["h_yield_em"]);
    yield_ss[3] = rt::Integral(hc["h_yield_ll"]);

    // set the error to the lumi*scale1fb if the yield < weight*0.5 
    float weight = (m_lumi * m_scale1fb);
    if (rt::Integral(hc["h_yield_ee"]) < (weight * 0.5)) {hc["h_yield_ee"]->SetBinError(2, weight);}
    if (rt::Integral(hc["h_yield_mm"]) < (weight * 0.5)) {hc["h_yield_mm"]->SetBinError(2, weight);}
    if (rt::Integral(hc["h_yield_em"]) < (weight * 0.5)) {hc["h_yield_em"]->SetBinError(2, weight);}
    if (rt::Integral(hc["h_yield_ll"]) < (weight * 0.5)) {hc["h_yield_ll"]->SetBinError(2, weight);}

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
    hc.Add(new TH1F("h_sf_pred_raw", "SF prediction, raw", 4, 0, 4));
    hc["h_sf_pred_raw"]->SetBinContent(1, sf_raw.ee.value);
    hc["h_sf_pred_raw"]->SetBinContent(2, sf_raw.mm.value);
    hc["h_sf_pred_raw"]->SetBinContent(3, sf_raw.em.value);
    hc["h_sf_pred_raw"]->SetBinContent(4, sf_raw.ll.value);
    hc["h_sf_pred_raw"]->SetBinError(1, sf_raw.ee.error);
    hc["h_sf_pred_raw"]->SetBinError(2, sf_raw.mm.error);
    hc["h_sf_pred_raw"]->SetBinError(3, sf_raw.em.error);
    hc["h_sf_pred_raw"]->SetBinError(4, sf_raw.ll.error);

    // DF
    PredSummary df = frp.GetDoubleFakePrediction();
    hc.Add(new TH1F("h_df_pred", "DF prediction", 4, 0, 4));
    hc["h_df_pred"]->SetBinContent(1, df.ee.value);
    hc["h_df_pred"]->SetBinContent(2, df.mm.value);
    hc["h_df_pred"]->SetBinContent(3, df.em.value);
    hc["h_df_pred"]->SetBinContent(4, df.ll.value);
    hc["h_df_pred"]->SetBinError(1, df.ee.error);
    hc["h_df_pred"]->SetBinError(2, df.mm.error);
    hc["h_df_pred"]->SetBinError(3, df.em.error);
    hc["h_df_pred"]->SetBinError(4, df.ll.error);

    // SF 
    PredSummary sf = frp.GetSingleFakePrediction();
    hc.Add(new TH1F("h_sf_pred", "SF prediction", 4, 0, 4));
    hc["h_sf_pred"]->SetBinContent(1, sf.ee.value);
    hc["h_sf_pred"]->SetBinContent(2, sf.mm.value);
    hc["h_sf_pred"]->SetBinContent(3, sf.em.value);
    hc["h_sf_pred"]->SetBinContent(4, sf.ll.value);
    hc["h_sf_pred"]->SetBinError(1, sf.ee.error);
    hc["h_sf_pred"]->SetBinError(2, sf.mm.error);
    hc["h_sf_pred"]->SetBinError(3, sf.em.error);
    hc["h_sf_pred"]->SetBinError(4, sf.ll.error);

    // Fakes 
    PredSummary fake = frp.GetFakePrediction();
    hc.Add(new TH1F("h_fake_pred", "fake prediction", 4, 0, 4));
    hc["h_fake_pred"]->SetBinContent(1, fake.ee.value);
    hc["h_fake_pred"]->SetBinContent(2, fake.mm.value);
    hc["h_fake_pred"]->SetBinContent(3, fake.em.value);
    hc["h_fake_pred"]->SetBinContent(4, fake.ll.value);
    hc["h_fake_pred"]->SetBinError(1, fake.ee.error);
    hc["h_fake_pred"]->SetBinError(2, fake.mm.error);
    hc["h_fake_pred"]->SetBinError(3, fake.em.error);
    hc["h_fake_pred"]->SetBinError(4, fake.ll.error);

    // print the output
    CTable t_yields;
    t_yields.useTitle();
    t_yields.setTitle("yields table");
    string f = "1.2";
    t_yields.setTable() (                      "ee",            "mm",            "em",            "ll")
                        ("SF raw" , sf_raw.ee.str(f), sf_raw.mm.str(f), sf_raw.em.str(f), sf_raw.ll.str(f))
                        ("SF"     ,     sf.ee.str(f),     sf.mm.str(f),     sf.em.str(f),     sf.ll.str(f))
                        ("DF"     ,     df.ee.str(f),     df.mm.str(f),     df.em.str(f),     df.ll.str(f))
                        ("Fakes"  ,   fake.ee.str(f),   fake.mm.str(f),   fake.em.str(f),   fake.ll.str(f))
                        ("yield"  ,      yield_ss[0],      yield_ss[1],      yield_ss[2],      yield_ss[3]);
    t_yields.print();
}

// binning contants
std::tr1::array<float, 5> el_eta_bins      = {{0.0, 1.0, 1.479, 2.0, 2.5}};
std::tr1::array<float, 5> mu_eta_bins      = {{0.0, 1.0, 1.479, 2.0, 2.5}};
std::tr1::array<float, 6> el_pt_bins       = {{10.0, 15.0, 20.0, 25.0, 35.0, 55.0}};
std::tr1::array<float, 6> mu_pt_bins       = {{ 5.0, 10.0, 15.0, 20.0, 25.0, 35.0}};
std::tr1::array<float, 9> mu_vtx_bins      = {{ 0.0,  3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0, 30.0}};
std::tr1::array<float, 9> el_vtx_bins      = {{ 0.0,  3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0, 30.0}};
std::tr1::array<float, 9> el_flip_eta_bins = {{ 0.0, 0.5, 1.0, 1.479, 1.8, 2.0, 2.1, 2.2, 2.4 }};
std::tr1::array<float, 18> el_flip_pt_bins = {{ 10., 20., 25., 30., 35., 40., 45., 50., 55., 60., 65., 70., 75., 80., 85., 90., 95., 100. }};
//std::tr1::array<float, 13>  ht_bins        = {{ 0, 100, 150, 200, 250, 300, 350, 400, 450, 500, 600, 700, 1000 }};
//std::tr1::array<float, 6> met_bins         = {{ 0, 50, 100, 150, 200, 400 }};

// book hists 
void FRClosureLooper::BookHists()
{
    try
    {
        // convenience alias
        rt::TH1Container& hc = m_hist_container;
        TH1::SetDefaultSumw2(true);

        hc.Add(new TH1F("h_lumi"   , "integrated lumi used for these plots", 10000, 0, 100));

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
            hc.Add(new TH2F(Form("h_df_fo_pt_vs_eta%s", ns.c_str()), Form("DF FO p_{T} vs |#eta|%s;|#eta|;p_{T} (GeV)", ts.c_str()), 20, 0, 20, 20, 0, 20));
        }

        // OS plots (for flip pred)
        hc.Add(new TH2F("h_os_fo_pt_vs_eta_ee", "OS FO (ee ) p_{T} vs |#eta|;|#eta|;p_{T} (GeV)" , 136, 0, 136, 136, 0, 136)); 
        hc.Add(new TH2F("h_os_fo_pt_vs_eta_em", "OS FO (e#mu) p_{T} vs |#eta|;|#eta|;p_{T} (GeV)", el_flip_eta_bins.size()-1,el_flip_eta_bins.data(),el_flip_pt_bins.size()-1,el_flip_pt_bins.data()));

        return;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }
}

// main analysis function operator 
int FRClosureLooper::operator()(long event)
{
    using namespace std;
    using namespace ssb;

    try
    {
        // base analysis
        at::AnalysisWithHist::operator()(event);

        // convenience alias
        rt::TH1Container& hc = m_hist_container;

        // good lumi
        if (is_real_data())
        {
            if (not is_good_lumi())
            {
                return 0;
            }
        }

        // scale 1b (set before cuts) 
        m_scale1fb = scale1fb();

        // selections 
        // ---------------------------------------------------------------------------------------------------------------------------- //

        // charge type
        DileptonChargeType::value_type charge_type = DileptonChargeType::static_size;
        if (is_ss()) {charge_type = DileptonChargeType::SS;}
        if (is_sf()) {charge_type = DileptonChargeType::SF;}
        if (is_df()) {charge_type = DileptonChargeType::DF;}
        //if (is_os()) {charge_type = DileptonChargeType::OS;}
        if (charge_type == DileptonChargeType::static_size)
        {
            return 0;
        }

        // dilepton hyp type: 1 mm, 2 em, 3ee
        DileptonHypType::value_type hyp_type = static_cast<DileptonHypType::value_type>(dilep_type());
        if (hyp_type == DileptonHypType::static_size)
        {
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
        //bool passes_trigger = false;
        //switch (hyp_type)
        //{
        //    case DileptonHypType::MUMU: passes_trigger = trig_mm(); break;
        //    case DileptonHypType::EMU : passes_trigger = trig_em(); break;
        //    case DileptonHypType::EE  : passes_trigger = trig_ee(); break;
        //    default: passes_trigger = false; break;
        //};
        //if (not passes_trigger)
        //{
        //    //cout << "fails trigger" << endl;
        //    return 0;
        //}

        // two jet events
        //if (njets() < static_cast<int>(m_njets))
        if (njets() < 2)
        {
            return 0;
        }

        // two btagged jets
        if (nbtags() < static_cast<int>(m_nbtags))
        {
            return 0;
        }

        // passes signal region
        //if (not PassesSignalRegion(m_signal_region, m_nbtags))
        //{
        //    return 0;
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

        // Weight Factors
        // ----------------------------------------------------------------------------------------------------------------------------//

        // scale
        //float vtxw = 1.0;
        //if (m_do_vtx_reweight)
        //{
        //    vtxw = is_real_data() ? 1.0 : vtxweight_n(nvtxs(), is_real_data(), false);
        //}
        //m_lumi = is_real_data() ? 1.0 : m_lumi;
        //float evt_weight = m_lumi * scale1fb() * vtxw;
        float evt_weight = 1.0; 

        // apply scale factors
        //if (m_do_scale_factors && !is_real_data())
        //{
        //    evt_weight *= sf_lepeff();
        //    // evt_weight *= sf_dileptrig();  // applying trigger cut now on MC
        //    evt_weight *= dilepTriggerScaleFactor(hyp_type);  // applying trigger cut now on MC
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

        bool mc3_matched = is_real_data() ? true : (lep1_mc3id()!=-999 && lep2_mc3id()!=-999);
		bool direct_b_l1 = is_real_data() ? true : (mc3_matched && abs(lep1_mc3id())==5 && idIsBeauty(lep1_mc3_momid()) && lep1_is_fromw()<1);
		bool direct_b_l2 = is_real_data() ? true : (mc3_matched && abs(lep2_mc3id())==5 && idIsBeauty(lep2_mc3_momid()) && lep2_is_fromw()<1);
		bool fromw_l1    = is_real_data() ? true : (lep1_is_fromw()==1);
		bool fromw_l2    = is_real_data() ? true : (lep1_is_fromw()==1);

        // SS
        if (is_ss())
        {
            //if ((fromw_l1 && !fromw_l2) || (!fromw_l1 && fromw_l2))
            //if (fromw_l1 || fromw_l2)
            {
                rt::Fill(hc["h_yield_ll"], 1, evt_weight);
                rt::Fill(hc["h_yield"+hs], 1, evt_weight);
            }
        }

        // SF 
        if (is_sf())
        {
            const LorentzVector& p4 = lep1_is_fo() ? lep1_p4()    : lep2_p4();
            int id                  = lep1_is_fo() ? lep1_pdgid() : lep2_pdgid();
            //if (!fromw_l1 || !fromw_l2)
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
            int l1_id                  = lep1_pdgid();
            int l2_id                  = lep2_pdgid();
            //if (!fromw_l1 && !fromw_l2)
            {
                at::FillDoubleFakeHist(*dynamic_cast<TH2F*>(hc["h_df_fo_pt_vs_eta_ll"]), *h_mufr, *h_elfr, hyp_type, l1_id, l1_p4.pt(), l1_p4.eta(), l2_id, l2_p4.pt(), l2_p4.eta(), evt_weight);
                at::FillDoubleFakeHist(*dynamic_cast<TH2F*>(hc["h_df_fo_pt_vs_eta"+hs]), *h_mufr, *h_elfr, hyp_type, l1_id, l1_p4.pt(), l1_p4.eta(), l2_id, l2_p4.pt(), l2_p4.eta(), evt_weight);
            }
        }
    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
    }

    // analysis end
    return 0;
} 

float FRClosureLooper::GetFakeRateValue(int lep_id, float pt, float eta) const 
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

float FRClosureLooper::GetFakeRateError(int lep_id, float pt, float eta) const 
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
