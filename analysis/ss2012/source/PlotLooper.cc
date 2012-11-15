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
PlotLooper::PlotLooper
(
    const std::string& root_file_name,
    at::Sample::value_type sample,
    SignalRegion::value_type signal_region,
    const std::string& vtxreweight_file_name,
    const std::string& fake_rate_file_name,
    const std::string& flip_rate_file_name,
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
    , m_njets(num_jets)
    , m_charge_option(charge_option)
    , m_sparm0(sparm0)
    , m_sparm1(sparm1)
    , m_sparm2(sparm2)
    , m_sparm3(sparm3)
    , m_sf_flip(sf_flip)
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

    // number of jets/btags
    cout << "Cutting on the number of jets/btags" << endl;
    cout << "nbtags >= " << m_nbtags << endl;
    cout << "njets  >= " << m_njets  << endl;

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
    hc["h_flip_pred"]->SetBinContent(1, flip.ee.value);
    hc["h_flip_pred"]->SetBinContent(2, flip.mm.value);
    hc["h_flip_pred"]->SetBinContent(3, flip.em.value);
    hc["h_flip_pred"]->SetBinContent(4, flip.ll.value);
    hc["h_flip_pred"]->SetBinError(1, flip.ee.error);
    hc["h_flip_pred"]->SetBinError(2, flip.mm.error);
    hc["h_flip_pred"]->SetBinError(3, flip.em.error);
    hc["h_flip_pred"]->SetBinError(4, flip.ll.error);


    // SS kinematic plots (fake prediction)
    // TODO -- propagate the errors on these
    hc.Add(dynamic_cast<TH1*>(hc["h_nvtxs_sf"      ]->Clone("h_nvtxs_fake"       ))); 
    hc.Add(dynamic_cast<TH1*>(hc["h_pt1_sf"        ]->Clone("h_pt1_fake"         ))); 
    hc.Add(dynamic_cast<TH1*>(hc["h_pt2_sf"        ]->Clone("h_pt2_fake"         ))); 
    hc.Add(dynamic_cast<TH1*>(hc["h_pt1_el_sf"     ]->Clone("h_pt1_el_fake"      ))); 
    hc.Add(dynamic_cast<TH1*>(hc["h_pt2_el_sf"     ]->Clone("h_pt2_el_fake"      ))); 
    hc.Add(dynamic_cast<TH1*>(hc["h_pt1_mu_sf"     ]->Clone("h_pt1_mu_fake"      ))); 
    hc.Add(dynamic_cast<TH1*>(hc["h_pt2_mu_sf"     ]->Clone("h_pt2_mu_fake"      ))); 
    hc.Add(dynamic_cast<TH1*>(hc["h_ht_sf"         ]->Clone("h_ht_fake"          ))); 
    hc.Add(dynamic_cast<TH1*>(hc["h_mt_sf"         ]->Clone("h_mt_fake"          ))); 
    hc.Add(dynamic_cast<TH1*>(hc["h_met_sf"        ]->Clone("h_met_fake"         ))); 
    hc.Add(dynamic_cast<TH1*>(hc["h_nbtags_sf"     ]->Clone("h_nbtags_fake"      ))); 
    hc.Add(dynamic_cast<TH1*>(hc["h_njets_sf"      ]->Clone("h_njets_fake"       ))); 
    hc.Add(dynamic_cast<TH1*>(hc["h_lepdphi_sf"    ]->Clone("h_lepdphi_fake"     ))); 
    hc.Add(dynamic_cast<TH1*>(hc["h_lepdeta_sf"    ]->Clone("h_lepdeta_fake"     ))); 
    hc.Add(dynamic_cast<TH1*>(hc["h_lepdr_sf"      ]->Clone("h_lepdr_fake"       ))); 
    hc.Add(dynamic_cast<TH1*>(hc["h_drlepb_sf"     ]->Clone("h_drlepb_fake"      ))); 
    hc.Add(dynamic_cast<TH1*>(hc["h_btagdr_sf"     ]->Clone("h_btagdr_fake"      ))); 
    hc.Add(dynamic_cast<TH1*>(hc["h_drjetb_sf"     ]->Clone("h_drjetb_fake"      ))); 
    hc.Add(dynamic_cast<TH1*>(hc["h_ptjetlep_sf"   ]->Clone("h_ptjetlep_fake"    ))); 
    hc.Add(dynamic_cast<TH1*>(hc["h_drlep3rdlep_sf"]->Clone("h_drlep3rdlep_fake" ))); 
    hc.Add(dynamic_cast<TH1*>(hc["h_ml3l_sf"       ]->Clone("h_ml3l_fake"        ))); 
    hc["h_nvtxs_fake"      ]->Add(hc["h_nvtxs_df"      ], -1.0);
    hc["h_pt1_fake"        ]->Add(hc["h_pt1_df"        ], -1.0);
    hc["h_pt2_fake"        ]->Add(hc["h_pt2_df"        ], -1.0);
    hc["h_pt1_el_fake"     ]->Add(hc["h_pt1_el_df"     ], -1.0);
    hc["h_pt2_el_fake"     ]->Add(hc["h_pt2_el_df"     ], -1.0);
    hc["h_pt1_mu_fake"     ]->Add(hc["h_pt1_mu_df"     ], -1.0);
    hc["h_pt2_mu_fake"     ]->Add(hc["h_pt2_mu_df"     ], -1.0);
    hc["h_ht_fake"         ]->Add(hc["h_ht_df"         ], -1.0);
    hc["h_mt_fake"         ]->Add(hc["h_mt_df"         ], -1.0);
    hc["h_met_fake"        ]->Add(hc["h_met_df"        ], -1.0);
    hc["h_nbtags_fake"     ]->Add(hc["h_nbtags_df"     ], -1.0);
    hc["h_njets_fake"      ]->Add(hc["h_njets_df"      ], -1.0);
    hc["h_lepdphi_fake"    ]->Add(hc["h_lepdphi_df"    ], -1.0);
    hc["h_lepdeta_fake"    ]->Add(hc["h_lepdeta_df"    ], -1.0);
    hc["h_lepdr_fake"      ]->Add(hc["h_lepdr_df"      ], -1.0);
    hc["h_drlepb_fake"     ]->Add(hc["h_drlepb_df"     ], -1.0);
    hc["h_btagdr_fake"     ]->Add(hc["h_btagdr_df"     ], -1.0);
    hc["h_drjetb_fake"     ]->Add(hc["h_drjetb_df"     ], -1.0);
    hc["h_ptjetlep_fake"   ]->Add(hc["h_ptjetlep_df"   ], -1.0);
    hc["h_drlep3rdlep_fake"]->Add(hc["h_drlep3rdlep_df"], -1.0);
    hc["h_ml3l_fake"       ]->Add(hc["h_ml3l_df"       ], -1.0);
    hc["h_nvtxs_fake"      ]->SetTitle("# vtxs (fake); #vtxs;Events"                                       );
    hc["h_pt1_fake"        ]->SetTitle("Higher p_{T} lepton (fake);p_{T} (GeV);Events"                     );
    hc["h_pt2_fake"        ]->SetTitle("Lower p_{T} lepton (fake);p_{T} (GeV);Events"                      );
    hc["h_pt1_el_fake"     ]->SetTitle("Higher p_{T} electron (fake);p_{T} (GeV);Events"                   );
    hc["h_pt2_el_fake"     ]->SetTitle("Lower p_{T} electron (fake);p_{T} (GeV);Events"                    );
    hc["h_pt1_mu_fake"     ]->SetTitle("Higher p_{T} electron (fake);p_{T} (GeV);Events"                   );
    hc["h_pt2_mu_fake"     ]->SetTitle("Lower p_{T} electron (fake);p_{T} (GeV);Events"                    );
    hc["h_ht_fake"         ]->SetTitle("H_{T};H_{T} (GeV) (fake);Events"                                   );
    hc["h_mt_fake"         ]->SetTitle("m_{T};m_{T} (GeV) (fake);Events"                                   );
    hc["h_met_fake"        ]->SetTitle("MET;E_{T}^{miss} (GeV) (fake);Events"                              );
    hc["h_nbtags_fake"     ]->SetTitle("# btags;# btags (fake);Events"                                     );
    hc["h_njets_fake"      ]->SetTitle("# jets (fake);# jets;Events"                                       );
    hc["h_lepdphi_fake"    ]->SetTitle("#Delta#Phi(lep1,lep2);Delta#Phi(lep1,lep2);Events"                 );
    hc["h_lepdeta_fake"    ]->SetTitle("#Delta#eta(lep1,lep2);Delta#eta(lep1,lep2);Events"                 );
    hc["h_lepdr_fake"      ]->SetTitle("#DeltaR(lep1,lep2);#DeltaR(lep1,lep2);Events"                      );
    hc["h_drlepb_fake"     ]->SetTitle("#DeltaR(lep,btag);#DeltaR(lep,btag);Events"                        );
    hc["h_btagdr_fake"     ]->SetTitle("#DeltaR(btag1,btag2);#DeltaR(btag1,btag2);Events"                  );
    hc["h_drjetb_fake"     ]->SetTitle("#DeltaR(btag,jet);#DeltaR(btag,jet);Events"                        );
    hc["h_ptjetlep_fake"   ]->SetTitle("p_{T}^{jet}/p)_{T}^{lep} - 1.;p_{T}^{jet}/p)_{T}^{lep} - 1.;Events");
    hc["h_drlep3rdlep_fake"]->SetTitle("#DeltaR(lep, 3rd lep);#DeltaR(lep,lep3);Events"                    );
    hc["h_ml3l_fake"       ]->SetTitle("M(lep, 3rd lep);M(l,3l);Events"                                    );

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
                        ("Flips"  ,    flip.ee.str(),    flip.mm.str(),    flip.em.str(),    flip.ll.str())
                        ("yield"  ,      yield_ss[0],      yield_ss[1],      yield_ss[2],      yield_ss[3]);
    t_yields.print();
}

// binning contants
std::tr1::array<float, 5> el_eta_bins      = {{0.0, 1.0, 1.479, 2.0, 2.5}};
std::tr1::array<float, 5> mu_eta_bins      = {{0.0, 1.0, 1.479, 2.0, 2.5}};
std::tr1::array<float, 6> el_pt_bins       = {{10.0, 15.0, 20.0, 25.0, 35.0, 55.0}};
std::tr1::array<float, 6> mu_pt_bins       = {{ 5.0, 10.0, 15.0, 20.0, 25.0, 35.0}};
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

        // kinematic plots
        for (size_t i = 0; i != at::DileptonChargeType::static_size; i++)
        {
            at::DileptonChargeType::value_type charge_type  = static_cast<at::DileptonChargeType::value_type>(i);

            // name and title suffixes
            string ns = Form("_%s"  ,  GetDileptonChargeTypeName(charge_type).c_str());
            string ts = Form(" (%s)",  GetDileptonChargeTypeTitle(charge_type).c_str());

            // SS kinematic plots
            hc.Add(new TH1F(Form("h_nvtxs%s"      , ns.c_str()), Form("# vtxs%s; #vtxs;Events"                                        , ts.c_str()), 20 , 0   , 40  ));
            hc.Add(new TH1F(Form("h_pt1%s"        , ns.c_str()), Form("Higher p_{T} lepton%s;p_{T} (GeV);Events"                      , ts.c_str()), 25 , 0   , 250 ));
            hc.Add(new TH1F(Form("h_pt2%s"        , ns.c_str()), Form("Lower p_{T} lepton%s;p_{T} (GeV);Events"                       , ts.c_str()), 25 , 0   , 250 ));
            hc.Add(new TH1F(Form("h_pt1_el%s"     , ns.c_str()), Form("Higher p_{T} electron%s;p_{T} (GeV);Events"                    , ts.c_str()), 25 , 0   , 250 ));
            hc.Add(new TH1F(Form("h_pt2_el%s"     , ns.c_str()), Form("Lower p_{T} electron%s;p_{T} (GeV);Events"                     , ts.c_str()), 25 , 0   , 250 ));
            hc.Add(new TH1F(Form("h_pt1_mu%s"     , ns.c_str()), Form("Higher p_{T} electron%s;p_{T} (GeV);Events"                    , ts.c_str()), 25 , 0   , 250 ));
            hc.Add(new TH1F(Form("h_pt2_mu%s"     , ns.c_str()), Form("Lower p_{T} electron%s;p_{T} (GeV);Events"                     , ts.c_str()), 25 , 0   , 250 ));
            //hc.Add(new TH1F(Form("h_ht%s"         , ns.c_str()), Form("H_{T}%s;H_{T} (GeV);Events"                                    , ts.c_str()), ht_bins.size()-1, ht_bins.data()));
            hc.Add(new TH1F(Form("h_ht%s"         , ns.c_str()), Form("H_{T}%s;H_{T} (GeV);Events"                                    , ts.c_str()), 20 , 0   , 1000));
            hc.Add(new TH1F(Form("h_mt%s"         , ns.c_str()), Form("m_{T}%s;m_{T} (GeV);Events"                                    , ts.c_str()), 8  , 0   , 400 ));
            //hc.Add(new TH1F(Form("h_met%s"        , ns.c_str()), Form("MET%s;E_{T}^{miss} (GeV);Events"                               , ts.c_str()), met_bins.size()-1, met_bins.data()));
            hc.Add(new TH1F(Form("h_met%s"        , ns.c_str()), Form("MET%s;E_{T}^{miss} (GeV);Events"                               , ts.c_str()), 8  , 0   , 400 ));
            hc.Add(new TH1F(Form("h_nbtags%s"     , ns.c_str()), Form("# btags%s;# btags;Events"                                      , ts.c_str()), 10 , 0   , 10  ));
            hc.Add(new TH1F(Form("h_njets%s"      , ns.c_str()), Form("# jets%s;# jets;Events"                                        , ts.c_str()), 10 , 0   , 10  ));
            hc.Add(new TH1F(Form("h_lepdphi%s"    , ns.c_str()), Form("#Delta#Phi(lep1, lep2)%s;#Delta#Phi(lep1, lep2);Events"        , ts.c_str()), 32 , 0   , 3.2 ));
            hc.Add(new TH1F(Form("h_lepdeta%s"    , ns.c_str()), Form("#Delta#eta(lep1, lep2)%s;#Delta#eta(lep1, lep2);Events"        , ts.c_str()), 25 , -2.5, 2.5 ));
            hc.Add(new TH1F(Form("h_lepdr%s"      , ns.c_str()), Form("#DeltaR(lep1, lep2)%s;#DeltaR(lep1, lep2);Events"              , ts.c_str()), 40 , 0   , 4.  ));
            hc.Add(new TH1F(Form("h_drlepb%s"     , ns.c_str()), Form("#DeltaR(lep, btag)%s;#DeltaR(lep, btag);Events"                , ts.c_str()), 40 , 0   , 4.  ));
            hc.Add(new TH1F(Form("h_btagdr%s"     , ns.c_str()), Form("#DeltaR(btag1, btag2)%s;#DeltaR(btag1, btag2);Events"          , ts.c_str()), 40 , 0   , 4.  ));
            hc.Add(new TH1F(Form("h_drjetb%s"     , ns.c_str()), Form("#DeltaR(btag, jet)%s;#DeltaR(btag, jet);Events"                , ts.c_str()), 40 , 0   , 4.  ));
            hc.Add(new TH1F(Form("h_ml3l%s"       , ns.c_str()), Form("M(lep,3rd lep)%s;M(l,3l);Events"                               , ts.c_str()), 10 , 0.  , 50. ));
            hc.Add(new TH1F(Form("h_drlep3rdlep%s", ns.c_str()), Form("#DeltaR(lep, lep3)%s:#DeltaR(lep, 3rd lep);Events"             , ts.c_str()), 40 , 0   , 4.  ));
            hc.Add(new TH1F(Form("h_ptjetlep%s"   , ns.c_str()), Form("jet p_{T} / lep p_{T} - 1%s;p_{T}^{jet}/p_{T}^{lep} - 1;Events", ts.c_str()), 50 , 0.  , 5.0 ));
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

        // selections 
        // ---------------------------------------------------------------------------------------------------------------------------- //

        // ichep uppper run
        //if (run() > 195947)
        //{
        //    return 0;
        //}

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
        bool passes_trigger = false;
        switch (hyp_type)
        {
            case DileptonHypType::MUMU: passes_trigger = trig_mm(); break;
            case DileptonHypType::EMU : passes_trigger = trig_em(); break;
            case DileptonHypType::EE  : passes_trigger = trig_ee(); break;
            default: passes_trigger = false; break;
        };
        if (not passes_trigger)
        {
            //cout << "fails trigger" << endl;
            return 0;
        }

        // two jet events
        if (njets() < static_cast<int>(m_njets))
        {
            return 0;
        }

        // two btagged jets
        if (nbtags() < static_cast<int>(m_nbtags))
        {
            return 0;
        }

        // passes signal region
        if (not PassesSignalRegion(m_signal_region, m_nbtags))
        {
            return 0;
        }

        // apply gamma*/upsilon veto
        bool has_gamma_cand = false;
        if (has_gamma_cand)
        {
            return 0;
        }

        // select m_gluino and m_lsp
        if 
		(
			m_sample == at::Sample::t1tttt || 
		    m_sample == at::Sample::t1tttt_fastsim ||
		    m_sample == at::Sample::sbottomtop
		)
        {
            if (!rt::is_equal(m_sparm0, sparm0()) || !rt::is_equal(m_sparm1, sparm1()))
            {
                return 0;
            }
        }

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
        float vtxw = 1.0;
        if (m_do_vtx_reweight)
        {
            vtxw = is_real_data() ? 1.0 : vtxweight_n(nvtxs(), is_real_data(), false);
        }
        m_lumi = is_real_data() ? 1.0 : m_lumi;
        //float evt_weight = m_lumi * scale1fb() * vtxw;
        float evt_weight = m_lumi * vtxw;

		// T1tttt is not scaled properly (need make this automatic) 
        if (m_sample == at::Sample::t1tttt || m_sample == at::Sample::t1tttt_fastsim)
        {
			if (rt::is_equal(sparm0(), 900.0f)) {evt_weight *= (0.060276 *1000)/10000.0;}
			if (rt::is_equal(sparm0(), 950.0f)) {evt_weight *= (0.0381246*1000)/10000.0;}
		}
		// SBottomTop is not scaled properl (need make this automatic)
        else if (m_sample == at::Sample::sbottomtop)
        {
			//evt_weight /= scale1fb();
			if (rt::is_equal(sparm0(), 460.0f)) {evt_weight *= (0.152*1000)/10000.0;}
			if (rt::is_equal(sparm0(), 380.0f)) {evt_weight *= (0.506*1000)/10000.0;}
		}
        else
        {
            evt_weight *= scale1fb();
        }

        // apply scale factors
        if (m_do_scale_factors && !is_real_data())
        {
            evt_weight *= sf_lepeff();
            // evt_weight *= sf_dileptrig();  // applying trigger cut now on MC
            evt_weight *= dilepTriggerScaleFactor(hyp_type);  // applying trigger with scale factor 
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

            at::FillDoubleFakeHist(*dynamic_cast<TH2F*>(hc["h_df_fo_pt_vs_eta_ll"]), *h_mufr, *h_elfr, hyp_type, l1_id, l1_p4.pt(), l1_p4.eta(), l2_id, l2_p4.pt(), l2_p4.eta(), evt_weight);
            at::FillDoubleFakeHist(*dynamic_cast<TH2F*>(hc["h_df_fo_pt_vs_eta"+hs]), *h_mufr, *h_elfr, hyp_type, l1_id, l1_p4.pt(), l1_p4.eta(), l2_id, l2_p4.pt(), l2_p4.eta(), evt_weight);
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
