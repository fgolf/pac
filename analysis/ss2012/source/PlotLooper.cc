#include "PlotLooper.h"
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
#include "SSB2012.h"
#include "CTable.h"

typedef std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > vecLorentzVector;

using namespace std;
using namespace at;
using namespace ss;

// construct:
PlotLooper::PlotLooper
(
    const std::string& root_file_name,
    at::Sample::value_type sample,
    SignalRegion::value_type signal_region,
    const std::string& vtxreweight_file_name,
    const std::string& fake_rate_file_name,
    const std::string& flip_rate_file_name,
    unsigned int num_btags,
    bool do_scale_factors,
    bool check_good_lumi,
    float mass_glu,
    float mass_lsp,
    float lumi,
    bool verbose,
    bool print,
    const std::string& suffix
)
    : at::AnalysisWithHist(root_file_name, print, suffix)
    , m_lumi(lumi)
    , m_verbose(verbose)
    , m_is_data(at::SampleIsData(sample))
    , m_do_vtx_reweight(not vtxreweight_file_name.empty())
    , m_do_scale_factors(do_scale_factors)
    , m_check_good_lumi(check_good_lumi)
    , m_nbtags(num_btags)
    , m_mass_glu(mass_glu)
    , m_mass_lsp(mass_lsp)
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
    h_mufr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get("h_mufr40c")->Clone()));
    h_elfr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get("h_elfr40c")->Clone()));
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
PlotLooper::~PlotLooper()
{
    // end  job
    EndJob();
}

// methods:
void PlotLooper::BeginJob()
{
    BookHists();
}

// end job
void PlotLooper::EndJob()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    if (m_verbose)
    {
        hc.List();
    }

    // 0 ee, 2 em, 2 mm, 3 ll
    std::tr1::array<int, 4> yield_ss;
    yield_ss[0] = static_cast<int>(hc["h_yield_ee"]->GetEntries());
    yield_ss[1] = static_cast<int>(hc["h_yield_em"]->GetEntries());
    yield_ss[2] = static_cast<int>(hc["h_yield_mm"]->GetEntries());
    yield_ss[3] = static_cast<int>(hc["h_yield_ll"]->GetEntries());

    // DF prediction (raw)
    hc.Add(dynamic_cast<TH1F*>(GetDoubleFakePred().Clone()));  // this is poor -- fix it later
    std::tr1::array<float, 4> df_pred;
    std::tr1::array<float, 4> df_err;
    std::tr1::array<string, 4> df;
    for (size_t i = 0; i != df_pred.size(); i++)
    {
        df_pred[i] = hc["h_df_pred"]->GetBinContent(i+1);
        df_err[i]  = hc["h_df_pred"]->GetBinError(i+1);
        df[i]      = rt::pm(df_pred[i], df_err[i]);
    }

    // SF prediction (raw)
    hc.Add(dynamic_cast<TH1F*>(GetSingleFakePredRaw().Clone()));  // this is poor -- fix it later
    std::tr1::array<float, 4> sf_raw_pred;
    std::tr1::array<float, 4> sf_raw_err;
    std::tr1::array<string, 4> sf_raw;
    for (size_t i = 0; i != sf_raw_pred.size(); i++)
    {
        sf_raw_pred[i] = hc["h_sf_pred_raw"]->GetBinContent(i+1);
        sf_raw_err[i]  = hc["h_sf_pred_raw"]->GetBinError(i+1);
        sf_raw[i]      = rt::pm(sf_raw_pred[i], sf_raw_err[i]);
    }

    // SF prediction
    std::tr1::array<float, 4> sf_pred;
    std::tr1::array<float, 4> sf_err;
    std::tr1::array<string, 4> sf;
    hc.Add(new TH1F("h_sf_pred", "SF prediction", 4, 0, 4));
    for (size_t i = 0; i != sf_pred.size(); i++)
    {
        sf_pred[i] = sf_raw_pred[i] - 2.0*df_pred[i]; 
        sf_err[i] = sqrt(pow(sf_raw_err[i], 2) + pow(2.0*df_err[i], 2)); 
        hc["h_sf_pred"]->SetBinContent(i+1, sf_pred[i]);
        hc["h_sf_pred"]->SetBinError(i+1, sf_err[i]);
        sf[i] = rt::pm(sf_pred[i], sf_err[i]);
    }

    // Fake prediction
    std::tr1::array<float, 4> fake_pred;
    std::tr1::array<float, 4> fake_err;
    std::tr1::array<string, 4> fake;
    for (size_t i = 0; i != df_pred.size(); i++)
    {
    fake_pred[i] = sf_pred[i] + df_pred[i]; 
    fake_err[i] = sqrt(pow(sf_err[i], 2) + pow(df_err[i], 2)); 
    fake[i] = rt::pm(fake_pred[i], fake_err[i]);
    }

    // Flip prediction
    std::tr1::array<std::pair<float, float>, 4> flip_pred_err;
    flip_pred_err[0] = rt::IntegralAndError(hc["h_flip_pred_ee"]);
    flip_pred_err[1] = rt::IntegralAndError(hc["h_flip_pred_em"]);
    flip_pred_err[2] = rt::IntegralAndError(hc["h_flip_pred_mm"]);
    flip_pred_err[3] = rt::IntegralAndError(hc["h_flip_pred_ll"]);
    std::tr1::array<string, 4> flip;
    for (size_t i = 0; i != df_pred.size(); i++)
    {
        flip[i] = rt::pm(flip_pred_err[i].first, flip_pred_err[i].second);
    }

    // SS kinematic plots (fake prediction)
    // TODO -- propagate the errors on these
    hc.Add(dynamic_cast<TH1*>(hc["h_nvtxs_sf" ]->Clone("h_nvtxs_fake" )));
    hc.Add(dynamic_cast<TH1*>(hc["h_pt1_sf"   ]->Clone("h_pt1_fake"   )));
    hc.Add(dynamic_cast<TH1*>(hc["h_pt2_sf"   ]->Clone("h_pt2_fake"   )));
    hc.Add(dynamic_cast<TH1*>(hc["h_pt1_el_sf"]->Clone("h_pt1_el_fake")));
    hc.Add(dynamic_cast<TH1*>(hc["h_pt2_el_sf"]->Clone("h_pt2_el_fake")));
    hc.Add(dynamic_cast<TH1*>(hc["h_pt1_mu_sf"]->Clone("h_pt1_mu_fake")));
    hc.Add(dynamic_cast<TH1*>(hc["h_pt2_mu_sf"]->Clone("h_pt2_mu_fake")));
    hc.Add(dynamic_cast<TH1*>(hc["h_ht_sf"    ]->Clone("h_ht_fake"    )));
    hc.Add(dynamic_cast<TH1*>(hc["h_mt_sf"    ]->Clone("h_mt_fake"    )));
    hc.Add(dynamic_cast<TH1*>(hc["h_met_sf"   ]->Clone("h_met_fake"   )));
    hc.Add(dynamic_cast<TH1*>(hc["h_nbtags_sf"]->Clone("h_nbtags_fake")));
    hc.Add(dynamic_cast<TH1*>(hc["h_njets_sf" ]->Clone("h_njets_fake" )));
    hc["h_nvtxs_fake" ]->Add(hc["h_nvtxs_df" ], -1.0);
    hc["h_pt1_fake"   ]->Add(hc["h_pt1_df"   ], -1.0);
    hc["h_pt2_fake"   ]->Add(hc["h_pt2_df"   ], -1.0);
    hc["h_pt1_el_fake"]->Add(hc["h_pt1_el_df"], -1.0);
    hc["h_pt2_el_fake"]->Add(hc["h_pt2_el_df"], -1.0);
    hc["h_pt1_mu_fake"]->Add(hc["h_pt1_mu_df"], -1.0);
    hc["h_pt2_mu_fake"]->Add(hc["h_pt2_mu_df"], -1.0);
    hc["h_ht_fake"    ]->Add(hc["h_ht_df"    ], -1.0);
    hc["h_mt_fake"    ]->Add(hc["h_mt_df"    ], -1.0);
    hc["h_met_fake"   ]->Add(hc["h_met_df"   ], -1.0);
    hc["h_nbtags_fake"]->Add(hc["h_nbtags_df"], -1.0);
    hc["h_njets_fake" ]->Add(hc["h_njets_df" ], -1.0);
    hc["h_nvtxs_fake" ]->SetTitle("# vtxs (fake); #vtxs;Events"                    );
    hc["h_pt1_fake"   ]->SetTitle("Higher p_{T} lepton (fake);p_{T} (GeV);Events"  );
    hc["h_pt2_fake"   ]->SetTitle("Lower p_{T} lepton (fake);p_{T} (GeV);Events"   );
    hc["h_pt1_el_fake"]->SetTitle("Higher p_{T} electron (fake);p_{T} (GeV);Events");
    hc["h_pt2_el_fake"]->SetTitle("Lower p_{T} electron (fake);p_{T} (GeV);Events" );
    hc["h_pt1_mu_fake"]->SetTitle("Higher p_{T} electron (fake);p_{T} (GeV);Events");
    hc["h_pt2_mu_fake"]->SetTitle("Lower p_{T} electron (fake);p_{T} (GeV);Events" );
    hc["h_ht_fake"    ]->SetTitle("H_{T};H_{T} (GeV) (fake);Events"                );
    hc["h_mt_fake"    ]->SetTitle("m_{T};m_{T} (GeV) (fake);Events"                );
    hc["h_met_fake"   ]->SetTitle("MET;E_{T}^{miss} (GeV) (fake);Events"           );
    hc["h_nbtags_fake"]->SetTitle("# btags;# btags (fake);Events"                  );
    hc["h_njets_fake" ]->SetTitle("# jets (fake);# jets;Events"                    );

    // print the output
    CTable t_yields;
    t_yields.useTitle();
    t_yields.setTitle("yields table");
    t_yields.setTable() (                 "ee",        "mm",        "em",        "ll")
                        ("SF raw" ,   sf_raw[0],   sf_raw[2],   sf_raw[1],   sf_raw[3])
                        ("DF"     ,       df[0],       df[2],       df[1],       df[3])
                        ("SF"     ,       sf[0],       sf[2],       sf[1],       sf[3])
                        ("SF + DF",     fake[0],     fake[2],     fake[1],     fake[3])
                        ("flips"  ,     flip[0],     flip[2],     flip[1],     flip[3])
                        ("yield"  , yield_ss[0], yield_ss[2], yield_ss[1], yield_ss[3]);
    t_yields.print();
    //hc.List();
}

// binning contants
std::tr1::array<float, 5> el_eta_bins = {{0.0, 1.0, 1.479, 2.0, 2.5}};
std::tr1::array<float, 5> mu_eta_bins = {{0.0, 1.0, 1.479, 2.0, 2.5}};
std::tr1::array<float, 6> el_pt_bins  = {{10.0, 15.0, 20.0, 25.0, 35.0, 55.0}};
std::tr1::array<float, 6> mu_pt_bins  = {{ 5.0, 10.0, 15.0, 20.0, 25.0, 35.0}};
//std::tr1::array<float, 9> mu_vtx_bins = {{ 0.0,  3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0, 30.0}};
//std::tr1::array<float, 9> el_vtx_bins = {{ 0.0,  3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0, 30.0}};

// book hists 
 void PlotLooper::BookHists()
{
    try
    {
        // convenience alias
        rt::TH1Container& hc = m_hist_container;
        TH1::SetDefaultSumw2(true);

        hc.Add(new TH1F("h_lumi"   , "integrated lumi used for these plots", 10000, 0, 100));

        for (size_t i = 0; i != at::DileptonHypType::static_size; i++)
        {
            at::DileptonHypType::value_type hyp_type       = static_cast<at::DileptonHypType::value_type>(i);

            // name and title suffixes
            string ns = Form("_%s" ,  GetDileptonHypTypeName(hyp_type).c_str());
            string ts = Form(" (%s)",  GetDileptonHypTypeTitle(hyp_type).c_str());

            // yields
            hc.Add(new TH1F(Form("h_yield%s", ns.c_str()), Form("yields%s;yield;Events", ts.c_str()), 3, 0, 3));

            // SF plots
            hc.Add(new TH2F(Form("h_sf_mufo_pt_vs_eta%s", ns.c_str()), Form("#mu FO p_{T} vs |#eta|%s;|#eta|;p_{T};Events"     , ts.c_str()),mu_eta_bins.size()-1,mu_eta_bins.data(),mu_pt_bins.size()-1,mu_pt_bins.data()));
            hc.Add(new TH2F(Form("h_sf_elfo_pt_vs_eta%s", ns.c_str()), Form("electron FO p_{T} vs |#eta|%s;|#eta|;p_{T};Events", ts.c_str()),el_eta_bins.size()-1,el_eta_bins.data(),el_pt_bins.size()-1,el_pt_bins.data()));

            // DF plots
            hc.Add(new TH2F(Form("h_df_fo_pt_vs_eta%s", ns.c_str()), Form("DF FO p_{T} vs |#eta|%s;|#eta|;p_{T}Events", ts.c_str()), 20, 0, 20, 20, 0, 20));

            // DF plots
            hc.Add(new TH1F(Form("h_flip_pred%s", ns.c_str()), Form("OS flip prediction%s;yield;Events", ts.c_str()), 3, 0, 3));
        }

        for (size_t i = 0; i != at::DileptonChargeType::static_size; i++)
        {
            at::DileptonChargeType::value_type charge_type  = static_cast<at::DileptonChargeType::value_type>(i);

            // name and title suffixes
            string ns = Form("_%s"  ,  GetDileptonChargeTypeName(charge_type).c_str());
            string ts = Form(" (%s)",  GetDileptonChargeTypeTitle(charge_type).c_str());

            // SS kinematic plots
            hc.Add(new TH1F(Form("h_nvtxs%s" , ns.c_str()), Form("# vtxs%s; #vtxs;Events"                    , ts.c_str()), 20 , 0     ,  40 ));
            hc.Add(new TH1F(Form("h_pt1%s"   , ns.c_str()), Form("Higher p_{T} lepton%s;p_{T} (GeV);Events"  , ts.c_str()), 25 , 0     , 250 ));
            hc.Add(new TH1F(Form("h_pt2%s"   , ns.c_str()), Form("Lower p_{T} lepton%s;p_{T} (GeV);Events"   , ts.c_str()), 25 , 0     , 250 ));
            hc.Add(new TH1F(Form("h_pt1_el%s", ns.c_str()), Form("Higher p_{T} electron%s;p_{T} (GeV);Events", ts.c_str()), 25 , 0     , 250 ));
            hc.Add(new TH1F(Form("h_pt2_el%s", ns.c_str()), Form("Lower p_{T} electron%s;p_{T} (GeV);Events" , ts.c_str()), 25 , 0     , 250 ));
            hc.Add(new TH1F(Form("h_pt1_mu%s", ns.c_str()), Form("Higher p_{T} electron%s;p_{T} (GeV);Events", ts.c_str()), 25 , 0     , 250 ));
            hc.Add(new TH1F(Form("h_pt2_mu%s", ns.c_str()), Form("Lower p_{T} electron%s;p_{T} (GeV);Events" , ts.c_str()), 25 , 0     , 250 ));
            hc.Add(new TH1F(Form("h_ht%s"    , ns.c_str()), Form("H_{T};H_{T} (GeV)%s;Events"                , ts.c_str()), 20 , 0     , 1000));
            hc.Add(new TH1F(Form("h_mt%s"    , ns.c_str()), Form("m_{T};m_{T} (GeV)%s;Events"                , ts.c_str()), 16 , 0     , 800 ));
            hc.Add(new TH1F(Form("h_met%s"   , ns.c_str()), Form("MET;E_{T}^{miss} (GeV)%s;Events"           , ts.c_str()), 16 , 0     , 800 ));
            hc.Add(new TH1F(Form("h_nbtags%s", ns.c_str()), Form("# btags;# btags%s;Events"                  , ts.c_str()), 10 , 0     , 10  ));
            hc.Add(new TH1F(Form("h_njets%s" , ns.c_str()), Form("# jets%s;# jets;Events"                    , ts.c_str()), 10 , 0     , 10  ));
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

        // which dataset

        // selections 
        // ---------------------------------------------------------------------------------------------------------------------------- //

        // only keep good lumi (data only) -- is_good_lumi branch not set
        if (m_check_good_lumi && is_real_data() && not is_good_lumi())
        {
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
            return 0;
        }

        // dilepton hyp type: 1 mm, 2 em, 3ee
        DileptonHypType::value_type hyp_type = static_cast<DileptonHypType::value_type>(dilep_type());
        //if (hyp_type != DileptonHypType::EMU)
        //{
        //    return 0;
        //}

        // two jet events
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
        if (not PassesSignalRegion(m_signal_region))
        {
            return 0;
        }


        // select m_gluino and m_lsp
        //if (m_sample == at::Sample::t1tttt)
        //{
        //    if (!rt::is_equal(m_mass_glu, sparm0()) || !rt::is_equal(m_mass_lsp, sparm1()))
        //    {
        //        return 0;
        //    }
        //    //cout << Form("sparm0 %f m_glu %f", sparm0(), m_mass_glu) << endl;;
        //    //cout << Form("sparm1 %f m_lsp %f", sparm1(), m_mass_lsp) << endl;;
        //}

        // Weight Factors
        // ----------------------------------------------------------------------------------------------------------------------------//

        // scale
        float vtxw = 1.0;
        if (m_do_vtx_reweight)
        {
            vtxw = is_real_data() ? 1.0 : vtxweight_n(nvtxs(), is_real_data(), false);
        }
        m_lumi = is_real_data() ? 1.0 : m_lumi;
        float evt_weight = m_lumi * scale1fb() * vtxw;

        // apply scale factors
        if (m_do_scale_factors && !is_real_data())
        {
            evt_weight *= sf_lepeff();
            if (m_nbtags>=2)
            {
                if (m_signal_region == SignalRegion::sr7)
                {
                    evt_weight *= (nbtags() >= 3 ? sf_nbtag3() : 1.0);
                }
                else
                {
                    evt_weight *= (nbtags() >= 2 ? sf_nbtag() : 1.0);
                }
            }
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
        }

        // SF 
        if (is_sf())
        {
            const LorentzVector& p4 = lep1_is_fo() ? lep1_p4()    : lep2_p4();
            int id                  = lep1_is_fo() ? lep1_pdgid() : lep2_pdgid();
            if (abs(id)==13) {rt::Fill2D(hc["h_sf_mufo_pt_vs_eta"+ hs], fabs(p4.eta()), p4.pt(), evt_weight);}
            if (abs(id)==11) {rt::Fill2D(hc["h_sf_elfo_pt_vs_eta"+ hs], fabs(p4.eta()), p4.pt(), evt_weight);}
        }

        // DF 
        if (is_df())
        {
            const LorentzVector& l1_p4 = lep1_p4();
            const LorentzVector& l2_p4 = lep2_p4();
            int l1_id                  = lep1_pdgid();
            int l2_id                  = lep2_pdgid();

            FillDoubleFakeHist(dynamic_cast<TH2F*>(hc["h_df_fo_pt_vs_eta_ll"]), hyp_type, l1_id, l1_p4.pt(), l1_p4.eta(), l2_id, l2_p4.pt(), l2_p4.eta(), evt_weight);
            FillDoubleFakeHist(dynamic_cast<TH2F*>(hc["h_df_fo_pt_vs_eta"+hs]), hyp_type, l1_id, l1_p4.pt(), l1_p4.eta(), l2_id, l2_p4.pt(), l2_p4.eta(), evt_weight);
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

        // OS
        if (is_os())
        {
            rt::Fill(hc["h_flip_pred"+hs], 1, evt_weight);  
            rt::Fill(hc["h_flip_pred_ll"], 1, evt_weight);  
        }

        // SS kinematic plots
        const LorentzVector& p41 = lep1_p4();
        const LorentzVector& p42 = lep2_p4();

        rt::Fill(hc["h_nvtxs" +qs], nvtxs()   , evt_weight);
        rt::Fill(hc["h_pt1"   +qs], p41.pt()  , evt_weight);
        rt::Fill(hc["h_pt2"   +qs], p42.pt()  , evt_weight);
        rt::Fill(hc["h_ht"    +qs], ht()      , evt_weight);
        rt::Fill(hc["h_mt"    +qs], lep1_mt() , evt_weight);
        rt::Fill(hc["h_met"   +qs], pfmet()   , evt_weight);
        rt::Fill(hc["h_nbtags"+qs], nbtags()  , evt_weight);
        rt::Fill(hc["h_njets" +qs], njets()   , evt_weight);
        
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

// book keeping struct
struct singlefake_t
{
    singlefake_t(int id_, float raw_, float err_, TH2F* h_)
        : id(id_)
          , raw(raw_)
          , err(err_)
          , h(h_)
    {}
    int id;
    float raw;
    float err;
    TH2F* h;
};

TH1F PlotLooper::GetSingleFakePredRaw() const
{
    // convenience alias
    const rt::TH1Container& hc = m_hist_container;

    // SF prediction (pt, eta) 
    TH1F h_sf_pred("h_sf_pred_raw", "SF prediction, raw", 4, 0, 4);

    std::vector<singlefake_t> sfs;
    sfs.push_back(singlefake_t(11, 0.0, 0.0, static_cast<TH2F*>(hc["h_sf_elfo_pt_vs_eta_ee"])));
    sfs.push_back(singlefake_t(13, 0.0, 0.0, static_cast<TH2F*>(hc["h_sf_mufo_pt_vs_eta_mm"])));
    sfs.push_back(singlefake_t(11, 0.0, 0.0, static_cast<TH2F*>(hc["h_sf_elfo_pt_vs_eta_em"])));
    sfs.push_back(singlefake_t(13, 0.0, 0.0, static_cast<TH2F*>(hc["h_sf_mufo_pt_vs_eta_em"])));

    // get the prediction
    for (size_t i = 0; i != sfs.size(); i++)
    {
        TH2F& h_sf = *sfs.at(i).h;
        //float nfo_sf = h_sf.GetEntries();
        float sf_raw = 0.0;
        float sf_err = 0.0;
        for (int ptbin = 1; ptbin != h_sf.GetNbinsY()+1; ptbin++)
        {  
            for (int etabin = 1; etabin != h_sf.GetNbinsX()+1; etabin++)
            {  
                float bin_count = h_sf.GetBinContent(etabin, ptbin);
                float bin_err   = h_sf.GetBinError(etabin, ptbin);
                float pt  = h_sf.GetYaxis()->GetBinCenter(ptbin);
                float eta = h_sf.GetXaxis()->GetBinCenter(etabin);
                float f = GetFakeRateValue(sfs.at(i).id, pt, eta);
                float e = GetFakeRateError(sfs.at(i).id, pt, eta);
                f = f / (1.0 - f);
                e = e / pow(1.0 - f, 2);
                float bin_pred = (bin_count * f); 
                float bin_pred_err = pow(bin_count*f,2) * (pow(e/f, 2) + pow(bin_err/bin_count, 2)); 
                sf_raw += bin_pred; 
                sf_err += !rt::is_zero(bin_pred) ? bin_pred_err : 0.0;
                //if (!rt::is_zero(bin_count))
                //{
                //    cout << Form("id %u pt %f eta %f f %f e %f bin_count %f sf_raw %f", sfs.at(i).id, pt, eta, f, e, bin_count, sf_raw) << endl;
                //}
            }
        }
        sfs.at(i).raw = sf_raw;

        if (!rt::is_zero(sf_err))
        {
            sfs.at(i).err = sqrt(sf_err);
        }
        else 
        {
            float el_max = h_elfr->GetMaximum();
            float mu_max = h_mufr->GetMaximum();
            //if (abs(sfs.at(i).id)==13)
            //{
            //    sfs.at(i).err = pow((mu_max/(1.0 - mu_max)), 2);
            //}
            //else if (abs(sfs.at(i).id)==11)
            //{
            //    sfs.at(i).err = pow((el_max/(1.0 - el_max)), 2);
            //}
            //else
            //{
            //    sfs.at(i).err = 0.0;
            //}
            switch(i)
            {
                case 0 : sfs.at(i).err = pow((el_max/(1.0 - el_max)), 2); break;
                case 1 : sfs.at(i).err = pow((mu_max/(1.0 - mu_max)), 2); break;
                case 2 : sfs.at(i).err = pow((el_max/(1.0 - el_max)), 2); break; 
                case 3 : sfs.at(i).err = pow((mu_max/(1.0 - mu_max)), 2); break;
                default: sfs.at(i).err = 0.00;                            break;
            }
            sfs.at(i).err = sqrt(sfs.at(i).err);
        }
    }

    // translate indices (0 ee, 1 em, 2 mm, 3 ll)

    // mm
    std::tr1::array<float, 4> sf_raw = {{0, 0, 0, 0}};
    sf_raw[0] = sfs[0].raw;
    sf_raw[2] = sfs[1].raw;

    // ee
    std::tr1::array<float, 4> sf_err = {{0, 0, 0, 0}};
    sf_err[0] = sfs[0].err;
    sf_err[2] = sfs[1].err;

    // combine for el 
    sf_raw[1] = sfs[2].raw + sfs[3].raw;
    if (not rt::is_zero(sfs[2].err) && not rt::is_zero(sfs[3].err))
    {
        sf_err[1] = sqrt(pow(sfs[2].err,2) + pow(sfs[3].err,2));
    }
    else if (not rt::is_zero(sfs[2].err))
    {
        sf_err[1] = sfs[2].err;
    }
    else if (not rt::is_zero(sfs[3].err))
    {
        sf_err[1] = sfs[3].err;
    }
    else
    {
        sf_err[1] = std::max(sfs[2].err, sfs[3].err);
    }

    // combine for ll
    sf_raw[3] = sf_raw[0] + sf_raw[1] + sf_raw[2];
    if (not rt::is_zero(sf_raw[3])) 
    {
        sf_err[3] += not rt::is_zero(sf_raw[0]) ? pow(sf_err[0], 2) : 0.0;
        sf_err[3] += not rt::is_zero(sf_raw[1]) ? pow(sf_err[1], 2) : 0.0;
        sf_err[3] += not rt::is_zero(sf_raw[2]) ? pow(sf_err[2], 2) : 0.0;
        sf_err[3] = sqrt(sf_err[3]); 
    }
    else       
    {
        sf_err[3] = std::max(std::max(sf_err[1], sf_err[2]), sf_err[3]);
    }

    h_sf_pred.SetBinContent(1, sf_raw[0]); h_sf_pred.SetBinError(1, sf_err[0]);
    h_sf_pred.SetBinContent(2, sf_raw[1]); h_sf_pred.SetBinError(2, sf_err[1]);
    h_sf_pred.SetBinContent(3, sf_raw[2]); h_sf_pred.SetBinError(3, sf_err[2]);
    h_sf_pred.SetBinContent(4, sf_raw[3]); h_sf_pred.SetBinError(4, sf_err[3]);
    return h_sf_pred;
}

// book keeping struct
//struct doublefake_t
//{
//    doublefake_t(float pred_, float err_, TH2F* h_)
//        , pred(pred_)
//        , err(err_)
//        , h(h_)
//    {}
//    float pred;
//    float err;
//    TH2F* h;
//};

TH1F PlotLooper::GetDoubleFakePred() const
{
    // convenience alias
    const rt::TH1Container& hc = m_hist_container;

    // DF prediction (pt, eta) 
    std::tr1::array<float, 4> df_pred     = {{0, 0, 0, 0}};
    std::tr1::array<float, 4> df_pred_err = {{0, 0, 0, 0}};

    // DF pt/eta distribtution
    for (unsigned int i = 1; i != at::DileptonHypType::static_size; i++)
    {
        const at::DileptonHypType::value_type hyp = static_cast<at::DileptonHypType::value_type>(i);
        string ns = Form("_%s",  GetDileptonHypTypeName(hyp).c_str());
        TH2F& h_df = *dynamic_cast<TH2F*>(hc["h_df_fo_pt_vs_eta"+ns]);

        const unsigned int xbin_min  = 1;
        const unsigned int ybin_min  = 1;
        const unsigned int xbin_max  = h_df.GetXaxis()->GetNbins()+1;
        const unsigned int ybin_max  = h_df.GetYaxis()->GetNbins()+1;
        const unsigned int neta_bins = el_eta_bins.size()-1;

        static TH2F h_mu_bins("h_mu_bins", "h_mu_bins", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data());
        static TH2F h_el_bins("h_el_bins", "h_el_bins", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data());
        TH2F* h_l1_bins = NULL;
        TH2F* h_l2_bins = NULL; 
        switch (hyp)
        {
            case DileptonHypType::EE  : h_l1_bins = &h_el_bins; h_l2_bins = &h_el_bins; break;
            case DileptonHypType::MUMU: h_l1_bins = &h_mu_bins; h_l2_bins = &h_mu_bins; break;
            case DileptonHypType::EMU : h_l1_bins = &h_el_bins; h_l2_bins = &h_mu_bins; break;
            default:
                throw std::domain_error("ERROR PlotLooper::GetDoubleFakePred -- hyp type invalid");
                break;
        };

        Float_t pred_total       = 0.0;
        Float_t pred_error_total = 0.0;
        for (unsigned int xbin = xbin_min; xbin < xbin_max; xbin++) 
        {
            for (unsigned int ybin = ybin_min; ybin < ybin_max; ybin++) 
            {
                int xbin1 = ((xbin - xbin_min) % neta_bins) + 1;
                int ybin1 = ((xbin - xbin1 + 1 - xbin_min) / neta_bins) + 1;
                int xbin2 = ((ybin - ybin_min) % neta_bins) + 1;
                int ybin2 = ((ybin - xbin2 + 1 - ybin_min) / neta_bins) + 1;

                float eta1 = h_l1_bins->GetXaxis()->GetBinCenter(xbin1);
                float eta2 = h_l2_bins->GetXaxis()->GetBinCenter(xbin2);
                float pt1  = h_l1_bins->GetYaxis()->GetBinCenter(ybin1);
                float pt2  = h_l2_bins->GetYaxis()->GetBinCenter(ybin2);

                float nFO     = h_df.GetBinContent(xbin, ybin);      // number of denominator not numerator objects for this eta, pt bin
                float nFO_err = h_df.GetBinError(xbin, ybin);        // number error on number of of denominator not numerator objects for this eta, pt bin
                float f1 = 0.0;                                         // get value of fake rate 1 for this eta, pt bin
                float f2 = 0.0;                                         // get error on fake rate 1 for this eta, pt bin
                float e1 = 0.0;                                         // get value of fake rate 2 for this eta, pt bin
                float e2 = 0.0;                                         // get error on fake rate 2 for this eta, pt bin

                int bin1 = 0;
                int bin2 = 0;
                switch (hyp)
                {
                    case DileptonHypType::EE: 
                        f1 = GetFakeRateValue(11, pt1, eta1); 
                        f2 = GetFakeRateValue(11, pt2, eta2); 
                        bin1 = h_elfr->GetBin(xbin1, xbin2);
                        bin2 = h_elfr->GetBin(xbin1, xbin2);
                        break;
                    case DileptonHypType::MUMU: 
                        f1 = GetFakeRateValue(13, pt1, eta1); 
                        f2 = GetFakeRateValue(13, pt2, eta2); 
                        bin1 = h_mufr->GetBin(xbin1, xbin2);
                        bin2 = h_mufr->GetBin(xbin1, xbin2);
                        break;
                    case DileptonHypType::EMU: 
                        f1 = GetFakeRateValue(11, pt1, eta1); 
                        f2 = GetFakeRateValue(13, pt2, eta2); 
                        bin1 = h_elfr->GetBin(xbin1, xbin2);
                        bin2 = h_mufr->GetBin(xbin1, xbin2);
                        break;
                    default:
                        break;
                };

                // ok, have all of the inputs, calculate prediction and error for this bin
                // start with calculating fr/(1-fr) for this bin for each fake rate
                f1 = f1 / (1.0 - f1);
                f2 = f2 / (1.0 - f2);
                Float_t pred = f1 * f2 * nFO;

                // now, need to get errors on these terms, be careful
                // start with hardest part, error on f
                //
                // start with basic equation: (sigma_f/f)^2 = (sigma_num/num)^2 + (sigma_den/den)^2 - 2 * (sigma_num/num) * (sigma_den/den) * rho_num_den
                // f is the value fr from above
                // num is the value f from above
                // den is 1 - f
                //
                // sigma_num is the value fake rate error from above
                // sigma_den is also the value FRerror from above (the error on 1 - A is just the error on A)
                // 
                // the numerator and denominator are completely anti-correlated, so rho_num_den is -1
                // 
                // combining all of this we can simplify the above to be
                //
                // (sigma_z/z)^2 = (sigma_num/num)^2 + (sigma_num/(1-num))^2 + 2 * sigma_num^2 * (1/num) * (1/(1-num))
                // (sigma_z/z)^2 = sigma_num^2 * [1/num + 1/(1-num)]^2
                // sigma_z = z * sigma_num * (1/(num * (1-num)))
                // sigma_z = sigma_num * (1 - num)^{-2}
                //
                e1 = e1 * pow((1.0 - f1), -2);
                e2 = e2 * pow((1.0 - f2), -2);

                // if we have a same flavor final state (either EE or MM)
                // and both leptons are in the same eta, pt bin
                // then the FR for each leg will come from the same bin
                // and thus the two FR factors will be completely correlated.
                // We need to account for this in the uncertainty calculation.
                float pred_error;
                if (nFO == 0)
                {
                    pred_error = 0.0;
                }
                else if (hyp == DileptonHypType::EMU || bin1 != bin2) 
                {             
                    // now that we have the error on fr/(1-fr), the error on the prediction is just the sum of this error and the error on FO count added in quadrature
                    // (sigma_pred/pred)^2 = (sigma_fr/fr)^2 + (sigma_fo/fo)^2
                    pred_error = pred * sqrt(pow(e1/f1, 2) + pow(e2/f2, 2) + pow(nFO_err/nFO, 2));
                }
                else 
                {
                    float totalFRfactor = f1 * f2;

                    // now that we have the error on each factor of fr/(1-fr), the error on the product when they are completely correlated is
                    // define FRprod = (FR_1 / (1 - FR_1)) * (FR_2 / (1 - FR_2)) = fr1 * fr2
                    // (sigma_FRprod/FRprod)^2 = (sigma_fr1/fr)^2 + (sigma_fr2/fr2)^2 + 2 * (sigma_fr1/fr1) * (sigma_fr2/fr2) * rho_fr1_fr2
                    // since the terms are completely correlated, rho_fr1_fr2 = 1, and thus
                    //
                    // (sigma_FRprod/FRprod)^2 = (sigma_fr1/fr1 + sigma_fr2/fr2)^2
                    // sigma_FRprod = FRprod * (sigma_fr1/fr1 + sigma_fr2/fr2) = fr2 * sigma_fr1 + fr1 *sigma_fr2
                    float totalFRerror  = (f2 * e1 + f1 * e2);
                    pred_error = pred * sqrt(pow(totalFRerror/totalFRfactor, 2) + pow(nFO_err/nFO, 2));
                }

                // now increment the total values
                pred_total += pred;
                pred_error_total += pow(pred_error, 2);
            }
        }

        // finish the error
        if (!rt::is_zero(pred_total))
        {
            pred_error_total = sqrt(pred_error_total);
        }
        else 
        {
            float el_max = h_elfr->GetMaximum();
            float mu_max = h_mufr->GetMaximum();
            switch (hyp)
            {
                case DileptonHypType::EE: 
                    pred_error_total = pow((el_max/(1.0 - el_max)), 2);        
                    break;
                case DileptonHypType::MUMU: 
                    pred_error_total = pow((mu_max/(1.0 - mu_max)), 2);
                    break;
                case DileptonHypType::EMU: 
                    pred_error_total = (mu_max/(1.0 - mu_max) * el_max/(1.0 - el_max));
                    break;
                default:
                    pred_error_total = 0.0; 
                    break;
            };
        }
        df_pred[hyp]     = pred_total; 
        df_pred_err[hyp] = pred_error_total;
    }

    // combine for ll
    df_pred[DileptonHypType::ALL] = df_pred[1] + df_pred[2] + df_pred[3]; 
    if (not rt::is_zero(df_pred[DileptonHypType::ALL])) 
    {
        df_pred_err[DileptonHypType::ALL] += not rt::is_zero(df_pred[1]) ? pow(df_pred_err[1], 2) : 0.0;
        df_pred_err[DileptonHypType::ALL] += not rt::is_zero(df_pred[2]) ? pow(df_pred_err[2], 2) : 0.0;
        df_pred_err[DileptonHypType::ALL] += not rt::is_zero(df_pred[3]) ? pow(df_pred_err[3], 2) : 0.0;
        df_pred_err[DileptonHypType::ALL] = sqrt(df_pred_err[DileptonHypType::ALL]); 
    }
    else       
    {
        df_pred_err[DileptonHypType::ALL] = std::max(std::max(df_pred_err[1], df_pred_err[2]), df_pred_err[3]);
    }

    // switching from hyp indices (ll 0, mm 1, em 2, ee 3) --> (ee 0, em 1, mm 2, ll 3) 
    TH1F h_df_pred("h_df_pred", "DF prediction", 4, 0, 4);
    h_df_pred.SetBinContent(1, df_pred[3]); h_df_pred.SetBinError(1, df_pred_err[3]);
    h_df_pred.SetBinContent(2, df_pred[2]); h_df_pred.SetBinError(2, df_pred_err[2]);
    h_df_pred.SetBinContent(3, df_pred[1]); h_df_pred.SetBinError(3, df_pred_err[1]);
    h_df_pred.SetBinContent(4, df_pred[0]); h_df_pred.SetBinError(4, df_pred_err[0]);
    return h_df_pred;
}

//void CombinedFakePred()
//{
//    TH1F& h_df_pred     = *hc["h_df_pred"    ];
//    TH1F& h_sf_pred_raw = *hc["h_sf_pred_raw"];
//    TH1F h_df_pred("h_sf_pred", "SF prediction", 4, 0, 4);
//    h_df_pred.SetBinContent(1, sf_pred_raw.GetBinContent(1) - 2 * df_pred.GetBinContent(1)); 
//    h_df_pred.SetBinContent(2, sf_pred_raw.GetBinContent(2) - 2 * df_pred.GetBinContent(2)); 
//    h_df_pred.SetBinContent(3, sf_pred_raw.GetBinContent(3) - 2 * df_pred.GetBinContent(3)); 
//    h_df_pred.SetBinContent(4, sf_pred_raw.GetBinContent(4) - 2 * df_pred.GetBinContent(4)); 
//
//    h_df_pred.SetBinContent(1, sf_pred_raw.GetBinContent(1) - df_pred.GetBinContent(1)); 
//    h_df_pred.SetBinContent(2, sf_pred_raw.GetBinContent(2) - df_pred.GetBinContent(2)); 
//    h_df_pred.SetBinContent(3, sf_pred_raw.GetBinContent(3) - df_pred.GetBinContent(3)); 
//    h_df_pred.SetBinContent(4, sf_pred_raw.GetBinContent(4) - df_pred.GetBinContent(4)); 
//}

int DoubleFakeBinLookup(int id, float pt, float eta)
{
    id  = abs(id);
    eta = fabs(eta);

    float max_pt  = (id == 11 ? el_pt_bins.back()   : mu_pt_bins.back() );
    float min_pt  = (id == 11 ? el_pt_bins.front()  : mu_pt_bins.front());
    float max_eta = (id == 11 ? el_eta_bins.back()  : mu_eta_bins.back());
    float min_eta = (id == 11 ? el_eta_bins.front() : mu_eta_bins.front());

    eta = eta >= max_eta ? max_eta-0.001 : eta;
    pt  = pt  >= max_pt  ? max_pt-0.001  : pt;
    if (pt < min_pt || eta > max_eta || eta < min_eta+0.001)
    {
        return -1;
    }
   
    static TH2F h_mu_bins("h_mu_bins", "h_mu_bins", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data());
    static TH2F h_el_bins("h_el_bins", "h_el_bins", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data());
    TH2F& h_l_bins = id==11 ? h_el_bins : h_mu_bins;

    int etabin = h_l_bins.GetXaxis()->FindBin(eta);
    int ptbin  = h_l_bins.GetYaxis()->FindBin(pt);

    if(ptbin <= 0)  {throw std::domain_error("ERROR: PlotLooper::DoubleFakeBinLookup: ptbin <= 0" );}
    if(etabin <= 0) {throw std::domain_error("ERROR: PlotLooper::DoubleFakeBinLookup: etabin <= 0");}

    int bin = (ptbin-1) * h_l_bins.GetNbinsX() + etabin;
    //cout << Form("id %u pt %f eta %f pt_bin %u eta_bin %u", id, pt, eta, ptbin, etabin) << endl;
    return bin;
}

void PlotLooper::FillDoubleFakeHist
(
    TH2F* hist, 
    const at::DileptonHypType::value_type& hyp, 
    int id1, 
    float pt1, 
    float eta1, 
    int id2, 
    float pt2, 
    float eta2, 
    float weight
)
{
    std::pair<int, int> bins(DoubleFakeBinLookup(id1, pt1, eta1), DoubleFakeBinLookup(id2, pt2, eta2));
    if (hyp == at::DileptonHypType::EMU && abs(id1) == 13)
    {
        bins = std::make_pair(DoubleFakeBinLookup(id2, pt2, eta2), DoubleFakeBinLookup(id1, pt1, eta1));
    }
    float value = hist->GetBinContent(bins.first, bins.second);

    value += weight;
    hist->SetBinContent(bins.first, bins.second, value);
    hist->SetBinError(bins.first, bins.second, weight * sqrt(value/weight));
    //cout << GetDileptonHypTypeName(hyp) << "\t" << bins.first << "\t" << bins.second << "\t" << value << "\t" << weight * sqrt(value/weight) << endl;
}
