#include "FakeRateBaby.h"
#include "FakeRateStudy.h"
#include "mcSelections.h"
#include "rt/RootTools.h"
#include <iostream>
#include <algorithm>
#include <tr1/array>
#include <cmath>
#include "at/VtxReweight.h"
#include "TH3F.h"

typedef std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > vecLorentzVector;

// construct:
FakeRateStudy::FakeRateStudy
(
     const std::string& root_file_name,
     const fr::Sample::value_type& sample,
     const std::string& lepton,
     const std::string& vtxreweight_file_name,
     float lumi,
     //float away_jet_cut,
     int charge, 
     bool verbose,
     bool print,
     const std::string& suffix
)
    : at::AnalysisWithHist(root_file_name, print, suffix)
    , m_sample(sample)
    , m_lepton(lepton)
    , m_lumi(lumi)
    //, m_away_jet_cut(away_jet_cut)
    , m_hist_ratio_evt_nvtxs(*dynamic_cast<TH1F*>(rt::GetHistFromRootFile<TH1F>("data/evt_nvtx.root", "h_ratio_evt_nvtxs_ttbar_fall_ttbar_summer")->Clone()))
    , m_charge(charge)
{
    // set vertex weight file
    if (!vtxreweight_file_name.empty())
    {
        cout << "using vertex reweight file : " << vtxreweight_file_name << endl;
        set_vtxreweight_rootfile(vtxreweight_file_name.c_str(), verbose);
    }

    // begin job
    BeginJob();
}

// destroy:
FakeRateStudy::~FakeRateStudy()
{
    // end  job
    EndJob();
}

// methods:
void FakeRateStudy::BeginJob()
{
    BookHists();
}

// end job
void FakeRateStudy::EndJob()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    // muons
    if (m_lepton == "mu")
    {   
        // FR(# vertices)
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num20c_vs_nvtxs"],hc["h_mu_fo20c_vs_nvtxs"], "h_mufr20c_vs_nvtxs", "#mu FR (away jet p_{T} > 20, p_{T} > 20);# vtxs"));
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num40c_vs_nvtxs"],hc["h_mu_fo40c_vs_nvtxs"], "h_mufr40c_vs_nvtxs", "#mu FR (away jet p_{T} > 40, p_{T} > 20);# vtxs"));
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num60c_vs_nvtxs"],hc["h_mu_fo60c_vs_nvtxs"], "h_mufr60c_vs_nvtxs", "#mu FR (away jet p_{T} > 60, p_{T} > 20);# vtxs"));

        // FR(pt)
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num20c"],hc["h_mu_fo20c"], "y", "h_mufr20c_vs_pt", "#mu FR (away jet p_{T} > 20);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num40c"],hc["h_mu_fo40c"], "y", "h_mufr40c_vs_pt", "#mu FR (away jet p_{T} > 40);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num60c"],hc["h_mu_fo60c"], "y", "h_mufr60c_vs_pt", "#mu FR (away jet p_{T} > 60);p_{T}"));

        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num40c_directb"       ],hc["h_mu_fo40c_directb"       ], "y", "h_mufr40c_directb_vs_pt"      , "#mu FR (away jet p_{T} > 40);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num40c_directb_slice2"],hc["h_mu_fo40c_directb_slice2"], "y", "h_mufr40c_directb_slice2_vs_pt", "#mu FR (away jet p_{T} > 40);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num40c_directb_slice5"],hc["h_mu_fo40c_directb_slice5"], "y", "h_mufr40c_directb_slice5_vs_pt", "#mu FR (away jet p_{T} > 40);p_{T}"));

        // FR(eta)
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num20c"],hc["h_mu_fo20c"], "x", "h_mufr20c_vs_eta", "#mu FR (away jet p_{T} > 20, p_{T} > 20);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num40c"],hc["h_mu_fo40c"], "x", "h_mufr40c_vs_eta", "#mu FR (away jet p_{T} > 40, p_{T} > 20);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num60c"],hc["h_mu_fo60c"], "x", "h_mufr60c_vs_eta", "#mu FR (away jet p_{T} > 60, p_{T} > 20);|#eta|", 20, 100));

        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num40c_directb"       ],hc["h_mu_fo40c_directb"       ], "x", "h_mufr40c_directb_vs_eta"      , "#mu FR (away jet p_{T} > 40);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num40c_directb_slice2"],hc["h_mu_fo40c_directb_slice2"], "x", "h_mufr40c_directb_slice2_vs_eta", "#mu FR (away jet p_{T} > 40);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num40c_directb_slice5"],hc["h_mu_fo40c_directb_slice5"], "x", "h_mufr40c_directb_slice5_vs_eta", "#mu FR (away jet p_{T} > 40);|#eta|", 20, 100));

        // FR(eta, pT)
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num20c"],hc["h_mu_fo20c"], "h_mufr20c", "#mu FR (away jet p_{T} > 20);|#eta|;p_{T} (GeV)"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num40c"],hc["h_mu_fo40c"], "h_mufr40c", "#mu FR (away jet p_{T} > 40);|#eta|;p_{T} (GeV)"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num60c"],hc["h_mu_fo60c"], "h_mufr60c", "#mu FR (away jet p_{T} > 60);|#eta|;p_{T} (GeV)"));

        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num40c_directb"       ],hc["h_mu_fo40c_directb"       ], "h_mufr40c_directb"      , "#mu FR (away jet p_{T} > 40);|#eta|;p_{T} (GeV)"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num40c_directb_slice2"],hc["h_mu_fo40c_directb_slice2"], "h_mufr40c_directb_slice2", "#mu FR (away jet p_{T} > 40);|#eta|;p_{T} (GeV)"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num40c_directb_slice5"],hc["h_mu_fo40c_directb_slice5"], "h_mufr40c_directb_slice5", "#mu FR (away jet p_{T} > 40);|#eta|;p_{T} (GeV)"));

        // FR(mc3 pt)
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num40c_vs_mc3"],hc["h_mu_fo40c_vs_mc3"], "h_mufr40c_vs_mc3", "#mu FR;p_{T}^{b}"));

        // FR(eta, mc3 pt)
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num40c_eta_mc3"],hc["h_mu_fo40c_eta_mc3"], "h_mufr40c_eta_mc3", "#mu FR;|#eta^{fo}|;p_{T}^{b}"));

        // FR(pt, mc3 pt)
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num40c_pt_mc3"],hc["h_mu_fo40c_pt_mc3"], "h_mufr40c_pt_mc3", "#mu FR;|p_{T}^{fo}|;p_{T}^{b}"));

        // FR(fo pt, fo eta, mc3 pt)
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num40c_eta_pt_mc3"],hc["h_mu_fo40c_eta_pt_mc3"], "h_mufr40c_eta_pt_mc3", "#mu FR;|#eta^{fo}|;p_{T}^{fo};p_{T}^{b}"));
    }

    // electrons
    if (m_lepton == "el")
    {   
        // FR(# vertices)
        hc.Add(rt::MakeEfficiencyPlot(hc["h_el_num20c_vs_nvtxs"],hc["h_el_fo20c_vs_nvtxs"], "h_elfr20c_vs_nvtxs", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 20, p_{T}>20);# vtxs"));
        hc.Add(rt::MakeEfficiencyPlot(hc["h_el_num40c_vs_nvtxs"],hc["h_el_fo40c_vs_nvtxs"], "h_elfr40c_vs_nvtxs", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40, p_{T}>20);# vtxs"));
        hc.Add(rt::MakeEfficiencyPlot(hc["h_el_num60c_vs_nvtxs"],hc["h_el_fo60c_vs_nvtxs"], "h_elfr60c_vs_nvtxs", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 60, p_{T}>20);# vtxs"));

        // FR(pt)
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num20c"],hc["h_el_fo20c"], "y", "h_elfr20c_vs_pt", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 20);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num40c"],hc["h_el_fo40c"], "y", "h_elfr40c_vs_pt", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num60c"],hc["h_el_fo60c"], "y", "h_elfr60c_vs_pt", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 60);p_{T}"));
                                                                                                                                                      
        // FR(eta)
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num20c"],hc["h_el_fo20c"], "x", "h_elfr20c_vs_eta", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 20, p_{T}>20);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num40c"],hc["h_el_fo40c"], "x", "h_elfr40c_vs_eta", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40, p_{T}>20);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num60c"],hc["h_el_fo60c"], "x", "h_elfr60c_vs_eta", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 60, p_{T}>20);|#eta|", 20, 100));

        // FR(eta, pT)
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_el_num20c"],hc["h_el_fo20c"], "h_elfr20c", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 20);|#eta|;p_{T} (GeV)"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_el_num40c"],hc["h_el_fo40c"], "h_elfr40c", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40);|#eta|;p_{T} (GeV)"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_el_num60c"],hc["h_el_fo60c"], "h_elfr60c", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 60);|#eta|;p_{T} (GeV)"));
    }

    //if (m_verbose)
    {
        hc.List();
    }
}

// binning contants
std::tr1::array<float, 9> mu_vtx_bins = {{ 0.0,  3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0, 30.0}};
std::tr1::array<float, 9> el_vtx_bins = {{ 0.0,  3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0, 30.0}};
std::tr1::array<float, 6> mu_pt_bins  = {{ 5.0, 10.0, 15.0, 20.0, 25.0, 35.0}};
//std::tr1::array<float, 6> mu_pt_bins  = {{ 20.0, 25.0, 30.0, 35.0, 45.0, 55.0}};
//std::tr1::array<float, 4> mu_pt_bins  = {{ 20.0, 25.0, 30.0, 35.0}};
//std::tr1::array<float, 4> mu_pt_bins  = {{20.0, 25.0, 30.0, 35.0}};
std::tr1::array<float, 6> el_pt_bins  = {{10.0, 15.0, 20.0, 25.0, 35.0, 55.0}};
std::tr1::array<float, 5> mu_eta_bins = {{0.0, 1.0, 1.479, 2.0, 2.5}};
std::tr1::array<float, 5> el_eta_bins = {{0.0, 1.0, 1.479, 2.0, 2.5}};

//std::tr1::array<float, 37> mc3_pt_bins = 
//{{
//    20, 22, 24, 26, 28, 
//    30, 32, 34, 36, 38, 
//    40, 42, 44, 46, 48, 
//    50, 52, 54, 56, 58, 
//    60, 62, 64, 66, 68, 
//    70, 72, 74, 76, 78, 
//    80, 82, 84, 86, 88, 
//    90, 100 
//}};
//std::tr1::array<float, 43> mc3_pt_bins = 
//{{
//    20, 22, 24, 26, 28, 
//    30, 32, 34, 36, 38, 
//    40, 45, 
//    50, 55,
//    60, 65,
//    70, 75,
//    80, 85,
//    90, 95,
//    100,105,
//    110,115,
//    120,125,
//    130,135,
//    140,145,
//    150,155,
//    160,165,
//    170,175,
//    180,185,
//    190,195,
//    200
//}};
//std::tr1::array<float, 14> mc3_pt_bins        = {{5.00, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40, 45, 50, 60, 70, 80, 100}};
//std::tr1::array<float, 14> mc3_pt_bins_coarse = {{5.00, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40, 45, 50, 60, 70, 80, 100}};
//std::tr1::array<float, 11> mc3_pt_bins = {{0.00, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 100.0, 150}};
std::tr1::array<float, 8> mc3_pt_bins = {{0.00, 20.0, 30.0, 40.0, 50.0, 60.0, 80.0, 150}};
//std::tr1::array<float, 13> mc3_pt_bins = {{0.00, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110, 130}};


// book hists 
 void FakeRateStudy::BookHists()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    // muons
    // --------------------------------------------------------------------------------------------------------------------------- //
        
    hc.Add(new TH1F("h_nvtxs"           , "# vertices;# vtxs", 40, 0, 40));
    hc.Add(new TH1F("h_nvtxs_fo"        , "# vertices;# vtxs", 40, 0, 40));
    hc.Add(new TH1F("h_nvtxs_reweighted", "# vertices;# vtxs", 40, 0, 40));
    
    // muon FR vs # vertices 
    if (m_lepton == "mu")
    {
        // analysis
		hc.Add(new TH1F("h_mc3_id", "FO's matched parton's id;|id|"          , 30, 0,  30));
		hc.Add(new TH1F("h_mc3_pt", "FO's matched parton's p_{T};p_{T} (GeV)", 30, 0, 150));

        //hc.Add(new TH1F("h_reliso"                           , "reliso;reliso"                                     , 4, 0, 0.4));
        //hc.Add(new TH1F("h_reliso_foslice2"                  , "reliso;reliso (fo slice2)"                         , 4, 0, 0.4));
        //hc.Add(new TH1F("h_reliso_directb"                   , "reliso (direct b);reliso"                          , 4, 0, 0.4));
        //hc.Add(new TH1F("h_reliso_directb_foslice2"          , "reliso (direct b and fo slice2);reliso"            , 4, 0, 0.4));
        //hc.Add(new TH1F("h_reliso_directb_foslice2_mc3slice2", "reliso (direct b and fo slice2, mc3 slice2);reliso", 4, 0, 0.4));
        //hc.Add(new TH1F("h_reliso_directb_foslice2_mc3slice5", "reliso (direct b and fo slice2, mc3 slice5);reliso", 4, 0, 0.4));
        hc.Add(new TH1F("h_reliso"                           , "reliso;reliso"                                     , 20, 0, 2.0));
        hc.Add(new TH1F("h_reliso_foslice2"                  , "reliso;reliso (fo slice2)"                         , 20, 0, 2.0));
        hc.Add(new TH1F("h_reliso_directb"                   , "reliso (direct b);reliso"                          , 20, 0, 2.0));
        hc.Add(new TH1F("h_reliso_directb_foslice2"          , "reliso (direct b and fo slice2);reliso"            , 20, 0, 2.0));
        hc.Add(new TH1F("h_reliso_directb_foslice2_mc3slice2", "reliso (direct b and fo slice2, mc3 slice2);reliso", 20, 0, 2.0));
        hc.Add(new TH1F("h_reliso_directb_foslice2_mc3slice5", "reliso (direct b and fo slice2, mc3 slice5);reliso", 20, 0, 2.0));

        hc.Add(new TH1F("h_fopt", "FO pT;FO pT", 100, 0, 100)); 
        hc.Add(new TH2F("h_fopt_vs_mc3pt"  , "FO pT vs mc3 pT;FO pT;mc3 pT"        , 100, 0, 100, 100, 0, 100)); 
        hc.Add(new TH2F("h_fopt_vs_ajetpt" , "FO pT vs away jet pT;FO pT;ajet pT"  , 100, 0, 100, 100, 0, 100));
        hc.Add(new TH2F("h_mc3pt_vs_ajetpt", "mc3 pT vs away jet pT;mc3 pT;ajet pT", 100, 0, 100, 100, 0, 100)); 
        hc.Add(new TH2F("h_mc3pt_vs_ajetpt_btag"     , "mc3 pT vs away jet pT;mc3 pT;ajet pT", 100, 0, 100, 100, 0, 100)); 
        hc.Add(new TH2F("h_mc3pt_vs_ajetpt_btag_dphi", "mc3 pT vs away jet pT;mc3 pT;ajet pT", 100, 0, 100, 100, 0, 100)); 

        // numerator
        hc.Add(new TH1F("h_mu_num20c_vs_nvtxs", "num #mu (away jet p_{T} > 20);# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_num40c_vs_nvtxs", "num #mu (away jet p_{T} > 40);# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_num60c_vs_nvtxs", "num #mu (away jet p_{T} > 60);# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");

        hc.Add(new TH2F("h_mu_num20c", "num #mu (away jet p_{T} > 20);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_num40c", "num #mu (away jet p_{T} > 40);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_num60c", "num #mu (away jet p_{T} > 60);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        
        hc.Add(new TH2F("h_mu_num40c_directb"       , "num #mu (away jet p_{T} > 40);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_num40c_directb_slice2", "num #mu (away jet p_{T} > 40);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_num40c_directb_slice5", "num #mu (away jet p_{T} > 40);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");

        hc.Add(new TH1F("h_mu_num40c_vs_mc3"    , "num #mu;p_{T}^{b} (GeV)"            , mc3_pt_bins.size()-1, mc3_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_num40c_eta_mc3"   , "num #mu;|#eta^{fo}|;p_{T}^{b} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mc3_pt_bins.size()-1, mc3_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_num40c_pt_mc3"    , "num #mu;|p_{T}{fo}|;p_{T}^{b} (GeV)", mu_pt_bins.size()-1 , mu_pt_bins.data() , mc3_pt_bins.size()-1, mc3_pt_bins.data()), "texte");
        hc.Add(new TH3F("h_mu_num40c_eta_pt_mc3", "num #mu;|#eta^{fo}|;p_{T}^{b} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data(), mc3_pt_bins.size()-1, mc3_pt_bins.data()), "texte");

        // denominator
        hc.Add(new TH1F("h_mu_fo20c_vs_nvtxs", "fo #mu (away jet p_{T} > 20);# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_fo40c_vs_nvtxs", "fo #mu (away jet p_{T} > 40);# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_fo60c_vs_nvtxs", "fo #mu (away jet p_{T} > 60);# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");

        hc.Add(new TH2F("h_mu_fo20c", "fo #mu (away jet p_{T} > 20);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_fo40c", "fo #mu (away jet p_{T} > 40);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_fo60c", "fo #mu (away jet p_{T} > 60);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");

        hc.Add(new TH2F("h_mu_fo40c_directb"      , "fo #mu (away jet p_{T} > 40);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_fo40c_directb_slice2", "fo #mu (away jet p_{T} > 40);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_fo40c_directb_slice5", "fo #mu (away jet p_{T} > 40);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");

        hc.Add(new TH1F("h_mu_fo40c_vs_mc3"    , "fo #mu;p_{T}^{b} (GeV)"            , mc3_pt_bins.size()-1, mc3_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_fo40c_eta_mc3"   , "fo #mu;|#eta^{fo}|;p_{T}^{b} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mc3_pt_bins.size()-1, mc3_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_fo40c_pt_mc3"    , "fo #mu;|p_{T}{fo}|;p_{T}^{b} (GeV)", mu_pt_bins.size()-1 , mu_pt_bins.data() , mc3_pt_bins.size()-1, mc3_pt_bins.data()), "texte");
        hc.Add(new TH3F("h_mu_fo40c_eta_pt_mc3", "fo #mu;|#eta^{fo}|;p_{T}^{b} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data(), mc3_pt_bins.size()-1, mc3_pt_bins.data()), "texte");
    }

    // electrons
    // --------------------------------------------------------------------------------------------------------------------------- //
    
    // electron FR vs # vertices 
    if (m_lepton == "el")
    {
        // numerator
        hc.Add(new TH1F("h_el_num20c_vs_nvtxs", "num electron (away jet p_{T} > 20, cpfiso03 < 0.09 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_el_num40c_vs_nvtxs", "num electron (away jet p_{T} > 40, cpfiso03 < 0.09 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_el_num60c_vs_nvtxs", "num electron (away jet p_{T} > 60, cpfiso03 < 0.09 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");

        hc.Add(new TH2F("h_el_num20c", "num electron (away jet p_{T} > 20, cpfiso03 < 0.09 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_el_num40c", "num electron (away jet p_{T} > 40, cpfiso03 < 0.09 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_el_num60c", "num electron (away jet p_{T} > 60, cpfiso03 < 0.09 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");

        // denominator
        hc.Add(new TH1F("h_el_fo20c_vs_nvtxs", "fo electron (away jet p_{T} > 20, cpfiso03 < 0.6 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_el_fo40c_vs_nvtxs", "fo electron (away jet p_{T} > 40, cpfiso03 < 0.6 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_el_fo60c_vs_nvtxs", "fo electron (away jet p_{T} > 60, cpfiso03 < 0.6 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");

        hc.Add(new TH2F("h_el_fo20c", "fo electron (away jet p_{T} > 20, cpfiso03 < 0.6 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_el_fo40c", "fo electron (away jet p_{T} > 40, cpfiso03 < 0.6 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_el_fo60c", "fo electron (away jet p_{T} > 60, cpfiso03 < 0.6 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");
    }

    hc.Sumw2();
    return;
}

    // main analysis function operator 
int FakeRateStudy::operator()(long event, const std::string& current_file_name)
{
    using namespace std;
    using namespace frb;

    try
    {
        // base analysis
        at::AnalysisWithHist::operator()(event);

        // convenience alias
        rt::TH1Container& hc = m_hist_container;

        // which dataset
        bool is_data  = false; 
        bool is_qcd   = (m_sample==fr::Sample::qcd11);
        bool is_ttbar = (m_sample==fr::Sample::ttbar11);
        bool is_mu    = (m_lepton=="mu") ? abs(id())==13 : false;
        bool is_el    = (m_lepton=="el") ? abs(id())==11 : false;

        // qcd mu cuts
        // ----------------------------------------------------------------------------------------------------------------------------//

        bool qcd_mu_low  = rt::string_contains(current_file_name, "MuPt5Enriched"  ) && pt() < 11.0; 
        bool qcd_mu_med  = rt::string_contains(current_file_name, "MuEnrichedPt-10") && pt() >= 11.0 && pt() < 16.0; 
        bool qcd_mu_high = rt::string_contains(current_file_name, "MuEnrichedPt-15") && pt() >= 16.0; 

        // qcd muon cuts (for the different qcd samples)
        if (is_qcd && not (qcd_mu_low || qcd_mu_med || qcd_mu_high))
        {
            return 0;
        }

        // Fill # vertex histograms
        // ----------------------------------------------------------------------------------------------------------------------------//
        
        // vertex reweight for ttbar
        float vtxw  = 1.0;
		if (is_qcd)
		{
			vtxw = m_hist_ratio_evt_nvtxs.GetBinContent(m_hist_ratio_evt_nvtxs.FindBin(evt_nvtxs()));
		}
        float evt_weight = vtxw;

        rt::Fill(hc["h_nvtxs"           ], evt_nvtxs(), 1.0 );
        rt::Fill(hc["h_nvtxs_reweighted"], evt_nvtxs(), vtxw);

        bool passes_vtx_cut = evt_nvtxs() >= 3 && evt_nvtxs() <= 8;
        //bool passes_vtx_cut = (evt_nvtxs() <= 14);

        // FO selection cuts
        // ----------------------------------------------------------------------------------------------------------------------------//

        // check the charge
        switch (m_charge)
        {
            case  1: if (id()>0) {return 0;} break; // 11/13   --> e-/mu- (reject)
            case -1: if (id()<0) {return 0;} break; // -11/-13 --> e+/mu+ (reject)
            case  0: /* do nothing*/ break;
            default: /*do nothing*/ break;
        };

        // pT cut
        //if (is_mu && (pt()<5 || pt()>35))
        if (is_mu && pt()<5)
		{
            return 0;
		}
		if (is_el && (pt()<10 || pt()>55))
		{
            return 0;
        }

        // eta cut
        if (fabs(eta()) > 2.4)
        {
            return 0;
        }

        // no W (MET and m_T cuts)
        if (pfmet()>20 || pfmt()>25)
        {
            return 0;
        }

        // no resonance's (Z or upsilon)
        if (is_mu && ((76<mz_fo_ctf() && mz_fo_ctf()<106) || (8<mupsilon_fo_mu() && mupsilon_fo_mu()>12)))
        {
            return 0;
        }
        else if (is_el && (76<mz_fo_gsf() && mz_fo_gsf()<106))
        {
            return 0;
        }

        // trigger cuts
        bool trig_cut = false;
        //if (is_data && is_mu)
        //{
        //    trig_cut = ((pt() > 30 && (mu30_eta2p1_vstar() > 1 || mu24_eta2p1_vstar() > 1 || mu17_vstar()>1 || mu8_vstar()>1)) || 
        //    			(pt() > 24 && (mu24_eta2p1_vstar() > 1 || mu17_vstar()>1 || mu8_vstar()>1)) || 
        //    			(pt() > 17 && (mu17_vstar()>1 || mu8_vstar()>1)) || 
        //    			(pt() > 8  && (mu8_vstar()>1)));
        //}
        //else if (is_data && is_el)
        //{
        //    trig_cut =  (pt() > 17 && (ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar() > 1 || ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar() > 1 ||
        //                               ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()  > 1 || ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()  > 1 ));
        //    trig_cut |= (pt() > 8  && (ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()  > 1 || ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()  > 1 ));
        //}
        //else if (not is_data)
        if (not is_data)
        {
            // use default true for MC
            trig_cut = true;
        }

		// no additional FO's in event
		bool nFOcut = false;
		if (is_mu)
        {
			nFOcut = (nFOmus() == 0);
		}
        else if(is_el)
        {
			nFOcut = (nFOels() == 0);
		}

        // away jet cut
        //float ajet_pt = is_data ? ptpfcL1Fj1res() : ptpfcL1Fj1();
        float ajet_pt = ptpfcL1Fj1();
        bool jet20c_cut = (ajet_pt > 20);
        bool jet40c_cut = (ajet_pt > 40);
        bool jet60c_cut = (ajet_pt > 60);
        if (is_ttbar)  // don't apply away jet cut for ttbar
        {
            jet20c_cut = true;
            jet40c_cut = true;
            jet60c_cut = true;
        }

        // additional selections
        //bool not_from_w = is_ttbar ? leptonIsFromW()<1 : true;
        bool not_from_w = leptonIsFromW()<1;

        // numerator cut
        bool num_lep_cut = false;
        if (is_mu)
        {
            //num_lep_cut = (is_mu && numNomSSv4noIso() && nt_iso()<0.1);
            num_lep_cut = (is_mu && numNomSSv4noIso());
        }
        else if(is_el)
        {
            //num_lep_cut = (abs(id()) == 11 && num_el_ssV7_noIso() && cpfiso03_rho()<0.09);
        }

        // denominator cut
        bool fo_lep_cut = false;
        if (is_mu)
        {
            fo_lep_cut = (is_mu && fo_mussV4_noIso());
        }
        else if(is_el)
        {
            //fo_lep_cut = (is_el && v3_el_ssV7() && cpfiso03_rho()<0.6);
        }

        // passes selection (no isolaiton)
        //bool num_lep_sel_notrig = (nFOcut && num_lep_cut && btag && not_from_w);
        //bool fo_lep_sel_notrig  = (nFOcut && fo_lep_cut && btag && not_from_w);
        bool num_lep_sel_notrig = (nFOcut && num_lep_cut && not_from_w);
        bool fo_lep_sel_notrig  = (nFOcut && fo_lep_cut && not_from_w);
        bool num_lep_sel        = (trig_cut && num_lep_sel_notrig);
        bool fo_lep_sel         = (trig_cut && fo_lep_sel_notrig);

		// mc matching
		bool mc3_matched = (mc3id() != -999);
		bool direct_b    = (mc3_matched && abs(mc3id())==5 && idIsBeauty(mcmotherid()) && not_from_w && (pt()<mc3pt()));

		// mc3 pt slice
		bool mc3_slice5 = mc3_matched && (55.0 < mc3pt() && mc3pt() < 60.0);
		bool mc3_slice2 = mc3_matched && (47.0 < mc3pt() && mc3pt() < 49.0);

		// FO pt slice
		bool fo_slice2 = (20.0 < pt() && pt() < 22.0);

        // awway jet is btagged
        bool btag = btagpfcL1F();

        // dphi between away jet and lepton
        float ajet_dphi = dphipfcL1Fj1();
        bool dphi2p5_cut = (ajet_dphi > 2.5);
        bool dphi2p8_cut = (ajet_dphi > 2.8);
        bool dphi3p0_cut = (ajet_dphi > 3.0);

        // only apply dphi cut for data and qcd (to get back-to-back)
        if (not (is_data || is_qcd))
        {
            dphi2p5_cut = true;
            dphi2p8_cut = true;
            dphi3p0_cut = true;
        }
		// skip if not FO
        if (!fo_lep_sel)
        {
            return 0;
        }

        // # vertices for FO's before cut
        rt::Fill(hc["h_nvtxs_fo"], evt_nvtxs(), 1.0 );

        if (mc3_matched)
        {
            rt::Fill(hc["h_fopt"  ], pt()); 
            rt::Fill2D(hc["h_fopt_vs_mc3pt"  ], pt()   , mc3pt()); 
            rt::Fill2D(hc["h_fopt_vs_ajetpt" ], pt()   , ajet_pt);
            rt::Fill2D(hc["h_mc3pt_vs_ajetpt"], mc3pt(), ajet_pt); 
            if (btag)                {rt::Fill2D(hc["h_mc3pt_vs_ajetpt_btag"     ], mc3pt(), ajet_pt);}
            if (btag && dphi2p5_cut) {rt::Fill2D(hc["h_mc3pt_vs_ajetpt_btag_dphi"], mc3pt(), ajet_pt);}
        }

        if (is_mu && (pt()<5 || pt()>35))
		{
            return 0;
		}
        
        // apply vertex cut
        if (!passes_vtx_cut)
        {
            return 0;
        }

        // muons
        // ----------------------------------------------------------------------------------------------------------------------------//

		// kinematics
        if (m_lepton == "mu")
        {
			//if (mc3_matched && nt_iso()<0.4) 
			if (num_lep_sel && mc3_matched) 
			{
				rt::Fill(hc["h_mc3_id"], abs(mc3id()), evt_weight); 
				rt::Fill(hc["h_mc3_pt"], mc3pt()     , evt_weight); 
			}

			if (jet40c_cut && pt()>20)
			{
				                                         {hc["h_reliso"                           ]->Fill(nt_iso(), evt_weight);} 
				if (fo_slice2)                           {hc["h_reliso_foslice2"                  ]->Fill(nt_iso(), evt_weight);} 
				if (direct_b)                            {hc["h_reliso_directb"                   ]->Fill(nt_iso(), evt_weight);} 
				if (direct_b && fo_slice2)               {hc["h_reliso_directb_foslice2"          ]->Fill(nt_iso(), evt_weight);} 
				if (direct_b && fo_slice2 && mc3_slice2) {hc["h_reliso_directb_foslice2_mc3slice2"]->Fill(nt_iso(), evt_weight);} 
				if (direct_b && fo_slice2 && mc3_slice5) {hc["h_reliso_directb_foslice2_mc3slice5"]->Fill(nt_iso(), evt_weight);} 
			}
		}
       
        // Fill Fake Rates 
        if (m_lepton == "mu")
        {
            // numerator
            if (num_lep_sel)
            {
				if (nt_iso()<0.1)
				{
					if (jet20c_cut && pt()>20) { rt::Fill( hc["h_mu_num20c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
					if (jet40c_cut && pt()>20) { rt::Fill( hc["h_mu_num40c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
					if (jet60c_cut && pt()>20) { rt::Fill( hc["h_mu_num60c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

					if (jet20c_cut) { rt::Fill2D(hc["h_mu_num20c"], fabs(eta()), pt(), evt_weight); } 
					if (jet40c_cut) { rt::Fill2D(hc["h_mu_num40c"], fabs(eta()), pt(), evt_weight); } 
					if (jet60c_cut) { rt::Fill2D(hc["h_mu_num60c"], fabs(eta()), pt(), evt_weight); } 

					if (jet40c_cut && direct_b) { rt::Fill2D(hc["h_mu_num40c_directb"], fabs(eta()), pt(), evt_weight); } 
					if (jet40c_cut && direct_b && mc3_slice5) { rt::Fill2D(hc["h_mu_num40c_directb_slice5"], fabs(eta()), pt(), evt_weight); } 
					if (jet40c_cut && direct_b && mc3_slice2) { rt::Fill2D(hc["h_mu_num40c_directb_slice2"], fabs(eta()), pt(), evt_weight); } 
        
                    if (jet40c_cut && direct_b)
                    {
                        rt::Fill(  hc["h_mu_num40c_vs_mc3"    ], mc3pt(), evt_weight);
                        rt::Fill2D(hc["h_mu_num40c_eta_mc3"   ], fabs(eta()), mc3pt(), evt_weight);
                        rt::Fill2D(hc["h_mu_num40c_pt_mc3"    ], pt(), mc3pt(), evt_weight);
                        rt::Fill3D(hc["h_mu_num40c_eta_pt_mc3"], fabs(eta()), pt(), mc3pt(), evt_weight);
                    }
				}
            }

            if (fo_lep_sel)
            {
				if (nt_iso()<0.4)
				{
					if (jet20c_cut && pt()>20) { rt::Fill( hc["h_mu_fo20c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
					if (jet40c_cut && pt()>20) { rt::Fill( hc["h_mu_fo40c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
					if (jet60c_cut && pt()>20) { rt::Fill( hc["h_mu_fo60c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

					if (jet20c_cut) { rt::Fill2D(hc["h_mu_fo20c"], fabs(eta()), pt(), evt_weight); } 
					if (jet40c_cut) { rt::Fill2D(hc["h_mu_fo40c"], fabs(eta()), pt(), evt_weight); } 
					if (jet60c_cut) { rt::Fill2D(hc["h_mu_fo60c"], fabs(eta()), pt(), evt_weight); } 

					if (jet40c_cut && direct_b) { rt::Fill2D(hc["h_mu_fo40c_directb"], fabs(eta()), pt(), evt_weight); } 
					if (jet40c_cut && direct_b && mc3_slice5) { rt::Fill2D(hc["h_mu_fo40c_directb_slice5"], fabs(eta()), pt(), evt_weight); } 
					if (jet40c_cut && direct_b && mc3_slice2) { rt::Fill2D(hc["h_mu_fo40c_directb_slice2"], fabs(eta()), pt(), evt_weight); } 

                    if (jet40c_cut && direct_b)
                    {
                        rt::Fill(  hc["h_mu_fo40c_vs_mc3"    ], mc3pt(), evt_weight);
                        rt::Fill2D(hc["h_mu_fo40c_eta_mc3"   ], fabs(eta()), mc3pt(), evt_weight);
                        rt::Fill2D(hc["h_mu_fo40c_pt_mc3"    ], pt(), mc3pt(), evt_weight);
                        rt::Fill3D(hc["h_mu_fo40c_eta_pt_mc3"], fabs(eta()), pt(), mc3pt(), evt_weight);
                    }
				}
            }
        }
        

        // Electrons
        // ----------------------------------------------------------------------------------------------------------------------------//
       
        // Fill Fake Rates 
        if (m_lepton == "el")
        {
            // numerator
            if (num_lep_sel)
			{

				if (jet20c_cut && pt()>20) { rt::Fill( hc["h_el_num20c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
				if (jet40c_cut && pt()>20) { rt::Fill( hc["h_el_num40c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
				if (jet60c_cut && pt()>20) { rt::Fill( hc["h_el_num60c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

				if (jet20c_cut           ) { rt::Fill2D(hc["h_el_num20c"], fabs(eta()), pt(), evt_weight); } 
				if (jet40c_cut           ) { rt::Fill2D(hc["h_el_num40c"], fabs(eta()), pt(), evt_weight); } 
				if (jet60c_cut           ) { rt::Fill2D(hc["h_el_num60c"], fabs(eta()), pt(), evt_weight); } 
			}

            // denominator 
            if (fo_lep_sel)
			{
				if (jet20c_cut && pt()>20) { rt::Fill( hc["h_el_fo20c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
				if (jet40c_cut && pt()>20) { rt::Fill( hc["h_el_fo40c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
				if (jet60c_cut && pt()>20) { rt::Fill( hc["h_el_fo60c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

				if (jet20c_cut           ) { rt::Fill2D(hc["h_el_fo20c"], fabs(eta()), pt(), evt_weight); } 
				if (jet40c_cut           ) { rt::Fill2D(hc["h_el_fo40c"], fabs(eta()), pt(), evt_weight); } 
				if (jet60c_cut           ) { rt::Fill2D(hc["h_el_fo60c"], fabs(eta()), pt(), evt_weight); } 
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
