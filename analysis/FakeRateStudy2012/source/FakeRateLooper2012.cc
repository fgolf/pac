#include "FakeRateBaby.h"
#include "FakeRateLooper2012.h"
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
FakeRateLooper2012::FakeRateLooper2012
(
     const std::string& root_file_name,
     const fr::Sample::value_type& sample,
     const std::string& lepton,
     const std::string& vtxreweight_file_name,
     float lumi,
     float away_jet_cut,
     int charge, 
     bool verbose,
     bool print,
     const std::string& suffix
)
    : at::AnalysisWithHist(root_file_name, print, suffix)
    , m_sample(sample)
    , m_lepton(lepton)
    , m_lumi(lumi)
    , m_away_jet_cut(away_jet_cut)
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
FakeRateLooper2012::~FakeRateLooper2012()
{
    // end  job
    //EndJob();
}

// methods:
void FakeRateLooper2012::BeginJob()
{
    BookHists();
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
//std::tr1::array<float, 5> mu_eta_bins = {{0.0, 1.0, 1.5, 2.0, 2.4}};
std::tr1::array<float, 5> el_eta_bins = {{0.0, 1.0, 1.479, 2.0, 2.5}};

// end job
void FakeRateLooper2012::EndJob()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    // muons
    if (m_lepton == "mu")
    {   
        // FR(# vertices)
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num20c_vs_nvtxs"],hc["h_mu_fo20c_vs_nvtxs"], "h_mufr20c_vs_nvtxs", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 20, p_{T} > 20);# vtxs"));
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num40c_vs_nvtxs"],hc["h_mu_fo40c_vs_nvtxs"], "h_mufr40c_vs_nvtxs", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 40, p_{T} > 20);# vtxs"));
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num60c_vs_nvtxs"],hc["h_mu_fo60c_vs_nvtxs"], "h_mufr60c_vs_nvtxs", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 60, p_{T} > 20);# vtxs"));

        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num40c_dphi2p5_vs_nvtxs"],hc["h_mu_fo40c_dphi2p5_vs_nvtxs"], "h_mufr40c_dphi2p5_vs_nvtxs", "#mu FR cpfiso03 (away jet p_{T} > 40, #Delta#Phi > 2.5);# vtxs"));
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num40c_dphi2p5_btag_vs_nvtxs"],hc["h_mu_fo40c_dphi2p5_btag_vs_nvtxs"], "h_mufr40c_dphi2p5_btag_vs_nvtxs", "#mu FR cpfiso03 (away jet p_{T} > 40, #Delta#Phi > 2.5, btag);# vtxs"));

        // FR(pt)
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num20c"],hc["h_mu_fo20c"], "y", "h_mufr20c_vs_pt", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 20);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num40c"],hc["h_mu_fo40c"], "y", "h_mufr40c_vs_pt", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 40);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num60c"],hc["h_mu_fo60c"], "y", "h_mufr60c_vs_pt", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 60);p_{T}"));

        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num40c_btag"],hc["h_mu_fo40c_btag"], "y", "h_mufr40c_btag_vs_pt", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (btag, away jet p_{T} > 40);p_{T}"));

        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num_dphi2p5"],hc["h_mu_fo_dphi2p5"], "y", "h_mufr_dphi2p5_vs_pt", "#mu FR (#Delta#Phi(#mu, bjet) > 2.5);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num_dphi2p8"],hc["h_mu_fo_dphi2p8"], "y", "h_mufr_dphi2p8_vs_pt", "#mu FR (#Delta#Phi(#mu, bjet) > 2.8);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num_dphi3p0"],hc["h_mu_fo_dphi3p0"], "y", "h_mufr_dphi3p0_vs_pt", "#mu FR (#Delta#Phi(#mu, bjet) > 3.0);p_{T}"));
                                                                                                                                                      
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num_dphi2p5_btag"],hc["h_mu_fo_dphi2p5_btag"], "y", "h_mufr_dphi2p5_btag_vs_pt", "#mu FR (btag, #Delta#Phi(#mu, bjet) > 2.5);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num_dphi2p8_btag"],hc["h_mu_fo_dphi2p8_btag"], "y", "h_mufr_dphi2p8_btag_vs_pt", "#mu FR (btag, #Delta#Phi(#mu, bjet) > 2.8);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num_dphi3p0_btag"],hc["h_mu_fo_dphi3p0_btag"], "y", "h_mufr_dphi3p0_btag_vs_pt", "#mu FR (btag, #Delta#Phi(#mu, bjet) > 3.0);p_{T}"));
                                                                                                                                                      
        // FR(eta)
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num20c"],hc["h_mu_fo20c"], "x", "h_mufr20c_vs_eta", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 20, p_{T} > 20);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num40c"],hc["h_mu_fo40c"], "x", "h_mufr40c_vs_eta", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 40, p_{T} > 20);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num60c"],hc["h_mu_fo60c"], "x", "h_mufr60c_vs_eta", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 60, p_{T} > 20);|#eta|", 20, 100));

        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num40c_btag"],hc["h_mu_fo40c_btag"], "x", "h_mufr40c_btag_vs_eta", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (btag, away jet p_{T} > 40, p_{T} > 20);|#eta|", 20, 100));

        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num_dphi2p5"],hc["h_mu_fo_dphi2p5"], "x", "h_mufr_dphi2p5_vs_eta", "#mu FR (#Delta#Phi(#mu, bjet) > 2.5);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num_dphi2p8"],hc["h_mu_fo_dphi2p8"], "x", "h_mufr_dphi2p8_vs_eta", "#mu FR (#Delta#Phi(#mu, bjet) > 2.8);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num_dphi3p0"],hc["h_mu_fo_dphi3p0"], "x", "h_mufr_dphi3p0_vs_eta", "#mu FR (#Delta#Phi(#mu, bjet) > 3.0);|#eta|", 20, 100));

        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num_dphi2p5_btag"],hc["h_mu_fo_dphi2p5_btag"], "x", "h_mufr_dphi2p5_btag_vs_eta", "#mu FR (btag, #Delta#Phi(#mu, bjet) > 2.5);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num_dphi2p8_btag"],hc["h_mu_fo_dphi2p8_btag"], "x", "h_mufr_dphi2p8_btag_vs_eta", "#mu FR (btag, #Delta#Phi(#mu, bjet) > 2.8);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num_dphi3p0_btag"],hc["h_mu_fo_dphi3p0_btag"], "x", "h_mufr_dphi3p0_btag_vs_eta", "#mu FR (btag, #Delta#Phi(#mu, bjet) > 3.0);|#eta|", 20, 100));

        // FR(eta, pT)
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num20c"],hc["h_mu_fo20c"], "h_mufr20c", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 20);|#eta|;p_{T} (GeV)"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num40c"],hc["h_mu_fo40c"], "h_mufr40c", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 40);|#eta|;p_{T} (GeV)"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num60c"],hc["h_mu_fo60c"], "h_mufr60c", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 60);|#eta|;p_{T} (GeV)"));

        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num40c_btag"],hc["h_mu_fo40c_btag"], "h_mufr40c_btag", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (btag, away jet p_{T} > 40);|#eta|;p_{T} (GeV)"));

        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num_dphi2p5"],hc["h_mu_fo_dphi2p5"], "h_mufr_dphi2p5", "#mu FR (#Delta#Phi(#mu, bjet) > 2.5);|#eta|;p_{T}"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num_dphi2p8"],hc["h_mu_fo_dphi2p8"], "h_mufr_dphi2p8", "#mu FR (#Delta#Phi(#mu, bjet) > 2.8);|#eta|;p_{T}"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num_dphi3p0"],hc["h_mu_fo_dphi3p0"], "h_mufr_dphi3p0", "#mu FR (#Delta#Phi(#mu, bjet) > 3.0);|#eta|;p_{T}"));

        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num_dphi2p5_btag"],hc["h_mu_fo_dphi2p5_btag"], "h_mufr_dphi2p5_btag", "#mu FR (#Delta#Phi(#mu, bjet) > 2.5);|#eta|;p_{T}"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num_dphi2p8_btag"],hc["h_mu_fo_dphi2p8_btag"], "h_mufr_dphi2p8_btag", "#mu FR (#Delta#Phi(#mu, bjet) > 2.8);|#eta|;p_{T}"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num_dphi3p0_btag"],hc["h_mu_fo_dphi3p0_btag"], "h_mufr_dphi3p0_btag", "#mu FR (#Delta#Phi(#mu, bjet) > 3.0);|#eta|;p_{T}"));
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
void FakeRateLooper2012::BookHists()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    // muons
    // --------------------------------------------------------------------------------------------------------------------------- //
        
    hc.Add(new TH1F("h_nvtxs"           , "# vertices;# vtxs", 40, 0, 40));
    hc.Add(new TH1F("h_nvtxs_reweighted", "# vertices;# vtxs", 40, 0, 40));
    
    hc.Add(new TH1F("h_dphi"             , "#Delta#phi;#Delta#phi", 35 , 0 , 3.5));

    hc.Add(new TH1F("h_ajet_pt_ptlt35", "away jet p_{T} (FO p_{T} < 35);p{T}", 25, 0, 100));
    hc.Add(new TH1F("h_nvtxs_ptlt35"  , "# vtxs (FO p_{T} < 35);# vtxs"      , 40, 0,  40));
    hc.Add(new TH1F("h_pfiso_ptlt35"  , "pfiso (FO p_{T} < 35);pfiso"        , 10, 0, 0.5));
    
    hc.Add(new TH1F("h_ajet_pt_ptgt35", "away jet p_{T} (FO p_{T} > 35);p{T}", 25, 0, 100));
    hc.Add(new TH1F("h_nvtxs_ptgt35"  , "# vtxs (FO p_{T} > 35);# vtxs"      , 40, 0,  40));
    hc.Add(new TH1F("h_pfiso_ptgt35"  , "pfiso (FO p_{T} > 35);pfiso"        , 10, 0, 0.5));


	hc.Add(new TH2F("h_mc3pt_vs_ajetpt"        , "mc3 pT vs away jet pT;mc3 pT;ajet pT"           , 100, 0, 100, 100, 0, 100)); 
	hc.Add(new TH2F("h_mc3pt_vs_ajetpt_btag"   , "mc3 pT vs away jet pT (btag);mc3 pT;ajet pT"    , 100, 0, 100, 100, 0, 100)); 
	hc.Add(new TH2F("h_mc3pt_vs_ajetpt_db_btag", "mc3 pT vs away jet pT (btag, db);mc3 pT;ajet pT", 100, 0, 100, 100, 0, 100)); 

    // muon FR vs # vertices 
    if (m_lepton == "mu")
    {
        // analysis
        hc.Add(new TH1F("h_mt"           , "m_{T};m_{T}"                , 25 , 0 , 100));
        hc.Add(new TH1F("h_mt_nobtag"    , "m_{T} (no btag);m_{T}"      , 25 , 0 , 100));
        hc.Add(new TH1F("h_mt_1stisobin" , "m_{T} (cpfiso < 0.1);m_{T}" , 25 , 0 , 100));
        hc.Add(new TH1F("h_mt_2ndisobin" , "m_{T} (cpfiso < 0.2);m_{T}" , 25 , 0 , 100));

        hc.Add(new TH1F("h_dbeta"            , "#Delta#beta;d#beta"   , 50 , 0 , 50));
        hc.Add(new TH1F("h_dbeta_nvtxs11-13" , "#Delta#beta;d#beta"   , 50 , 0 , 50));
        hc.Add(new TH1F("h_dbeta_nvtxs14-16" , "#Delta#beta;d#beta"   , 50 , 0 , 50));
        hc.Add(new TH1F("h_dbeta_nvtxs17-19" , "#Delta#beta;d#beta"   , 50 , 0 , 50));
        hc.Add(new TH2F("h_dbeta_vs_nvtxs"   , "#Delta#beta vs # vertices;# vtxs;d#beta", 40, 0, 40, 50, 0, 50));
        hc.Add(new TH1F("h_ecal_iso" , "ECAL iso;iso", 10, 0, 0.5));

        hc.Add(new TH1F("h_cpfiso", "cpfiso;cpfiso"    , 10, 0, 10));
        hc.Add(new TH1F("h_pfiso" , "pfiso;pfiso"       , 10, 0, 10));
        hc.Add(new TH1F("h_chiso" , "ch pfiso;ch pfiso" , 10, 0, 10));
        hc.Add(new TH1F("h_nhiso" , "nh pfiso;nh pfiso" , 10, 0, 10));
        hc.Add(new TH1F("h_emiso" , "em pfiso;em pfiso" , 10, 0, 10));

        hc.Add(new TH1F("h_pfiso_over_pt"                    , "pfiso/p_{T};pfiso/p_{T}"                                                               , 4 ,   -0, 0.4));
        hc.Add(new TH1F("h_cpfiso_over_pt"                   , "cpfiso/p_{T};cpfiso/p_{T}"                                                             , 4 ,   -0, 0.4));
        hc.Add(new TH1F("h_chiso_over_pt"                    , "ch pfiso/p_{T};ch pfiso/p_{T}"                                                         , 4 ,   -0, 0.4));
        hc.Add(new TH1F("h_nhiso_over_pt"                    , "nh pfiso/p_{T};nh pfiso/p_{T}"                                                         , 4 ,   -0, 0.4));
        hc.Add(new TH1F("h_emiso_over_pt"                    , "em pfiso/p_{T};em pfiso/p_{T}"                                                         , 4 ,   -0, 0.4));
        hc.Add(new TH1F("h_pfiso_over_pt_nvtxs14-16"         , "pfiso/p_{T} (14 <= # vtxs <= 16);pfiso/p_{T}"                                          , 4 ,   -0, 0.4));
        hc.Add(new TH1F("h_chiso_over_pt_nvtxs14-16"         , "ch pfiso/p_{T} (14 <= # vtxs <= 16);ch pfiso/p_{T}"                                    , 4 ,   -0, 0.4));
        hc.Add(new TH1F("h_nhiso_over_pt_nvtxs14-16"         , "nh pfiso/p_{T} (14 <= # vtxs <= 16);nh pfiso/p_{T}"                                    , 4 ,   -0, 0.4));
        hc.Add(new TH1F("h_emiso_over_pt_nvtxs14-16"         , "em pfiso/p_{T} (14 <= # vtxs <= 16);em pfiso/p_{T}"                                    , 4 ,   -0, 0.4));
        hc.Add(new TH1F("h_nhiso_plus_emiso_over_pt"         , "nh_pfiso/p_{T} + em_pfiso/p_{T};nh_pfiso/p_{T} + em_pfiso/p_{T}"                       , 4 ,   -0, 0.4));
        hc.Add(new TH1F("h_nhiso_plus_emiso_over_pt_corr"    , "(nh_pfiso/p_{T} + em_pfiso/p_{T}) - dB;(nh_pfiso/p_{T} + em_pfiso/p_{T}) - dB"         , 7 , -0.3, 0.4));
        hc.Add(new TH1F("h_max_nhiso_plus_emiso_over_pt_corr", "max(0, (nh_pfiso/p_{T} + em_pfiso/p_{T}) - dB);(nh_pfiso/p_{T} + em_pfiso/p_{T}) - dB" , 4 ,   -0, 0.4));

        hc.Add(new TH1F("h_njets10", "# jets > 10 with dR >=1.0;# jets", 10, -0.5, 9.5));
        hc.Add(new TH1F("h_njets30", "# jets > 30 with dR >=1.0;# jets",  5, -0.5, 4.5));
        hc.Add(new TH1F("h_njets40", "# jets > 40 with dR >=1.0;# jets",  5, -0.5, 4.5));

        // numerator
        hc.Add(new TH1F("h_mu_num20c_vs_nvtxs", "num #mu (away jet p_{T} > 20, cpfiso03 < 0.1 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_num40c_vs_nvtxs", "num #mu (away jet p_{T} > 40, cpfiso03 < 0.1 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_num60c_vs_nvtxs", "num #mu (away jet p_{T} > 60, cpfiso03 < 0.1 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");

        hc.Add(new TH2F("h_mu_num20c", "num #mu (away jet p_{T} > 20, cpfiso03 < 0.1 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_num40c", "num #mu (away jet p_{T} > 40, cpfiso03 < 0.1 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_num60c", "num #mu (away jet p_{T} > 60, cpfiso03 < 0.1 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");

        hc.Add(new TH2F("h_mu_num40c_btag", "num #mu (btag, away jet p_{T} > 40, cpfiso03 < 0.1 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        
        hc.Add(new TH2F("h_mu_num_dphi2p5", "num #mu (#Delta#Phi > 2.5);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_num_dphi2p8", "num #mu (#Delta#Phi > 2.8);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_num_dphi3p0", "num #mu (#Delta#Phi > 3.0);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");

        hc.Add(new TH2F("h_mu_num_dphi2p5_btag", "num #mu (btag, #Delta#Phi > 2.5);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_num_dphi2p8_btag", "num #mu (btag, #Delta#Phi > 2.8);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_num_dphi3p0_btag", "num #mu (btag, #Delta#Phi > 3.0);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");

        hc.Add(new TH1F("h_mu_num40c_dphi2p5_vs_nvtxs", "num #mu (away jet p_{T} > 40, #Delta#Phi > 2.5);# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_num40c_dphi2p5_btag_vs_nvtxs", "num #mu (away jet p_{T} > 40, #Delta#Phi > 2.5, btag);# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");

        // denominator
        hc.Add(new TH1F("h_mu_fo20c_vs_nvtxs", "fo #mu (away jet p_{T} > 20, cpfiso03 < 0.4 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_fo40c_vs_nvtxs", "fo #mu (away jet p_{T} > 40, cpfiso03 < 0.4 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_fo60c_vs_nvtxs", "fo #mu (away jet p_{T} > 60, cpfiso03 < 0.4 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");

        hc.Add(new TH2F("h_mu_fo20c", "fo #mu (away jet p_{T} > 20, cpfiso03 < 0.4 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_fo40c", "fo #mu (away jet p_{T} > 40, cpfiso03 < 0.4 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_fo60c", "fo #mu (away jet p_{T} > 60, cpfiso03 < 0.4 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");

        hc.Add(new TH2F("h_mu_fo40c_btag", "fo #mu (btag, away jet p_{T} > 40, cpfiso03 < 0.4 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");

        hc.Add(new TH2F("h_mu_fo_dphi2p5", "fo #mu (#Delta#Phi > 2.5);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_fo_dphi2p8", "fo #mu (#Delta#Phi > 2.8);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_fo_dphi3p0", "fo #mu (#Delta#Phi > 3.0);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");

        hc.Add(new TH2F("h_mu_fo_dphi2p5_btag", "fo #mu (btag, #Delta#Phi > 2.5);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_fo_dphi2p8_btag", "fo #mu (btag, #Delta#Phi > 2.8);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_fo_dphi3p0_btag", "fo #mu (btag, #Delta#Phi > 3.0);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");

        hc.Add(new TH1F("h_mu_fo40c_dphi2p5_vs_nvtxs"     , "fo #mu (away jet p_{T} > 40, #Delta#Phi > 2.5);# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_fo40c_dphi2p5_btag_vs_nvtxs", "fo #mu (away jet p_{T} > 40, #Delta#Phi > 2.5, btag);# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
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
int FakeRateLooper2012::operator()(long event, const std::string& current_file_name)
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
        bool is_data  = (m_sample==fr::Sample::data);
        bool is_qcd   = (m_sample==fr::Sample::qcd);
        bool is_ttbar = (m_sample==fr::Sample::ttbar);
        //bool is_dy    = (m_sample==fr::Sample::dy);
        //bool is_wjets = (m_sample==fr::Sample::wjets);
        bool is_mu    = (m_lepton=="mu") ? abs(id())==13 : false;
        bool is_el    = (m_lepton=="el") ? abs(id())==11 : false;

        // Fill # vertex histograms
        // ----------------------------------------------------------------------------------------------------------------------------//
        
        // vertex reweight for ttbar
        //float vtxw  = is_data ? 1.0 : vtxweight_n(evt_nvtxs(), is_data, false);
        //float evt_weight = m_lumi * weight() * vtxw;
        //float evt_weight = vtxw;
        float vtxw = 1.0;
        float evt_weight = weight() * vtxw;
        //float evt_weight = 1.0;

        rt::Fill(hc["h_nvtxs"           ], evt_nvtxs(), evt_weight);
        rt::Fill(hc["h_nvtxs_reweighted"], evt_nvtxs(), evt_weight);//* vtxw);

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

        // qcd muon cuts (for the different qcd samples)
        bool qcd_mu_low  = rt::string_contains(current_file_name, "MuEnrichedPt5"  ) && pt() < 16.0; 
        bool qcd_mu_high = rt::string_contains(current_file_name, "MuEnrichedPt_15") && pt() >= 16.0; 
        if (is_mu && is_qcd && not (qcd_mu_low || qcd_mu_high))
        {
            return 0;
        }

        // pT cut
        if (is_mu && (pt()<5 || pt()>35))
        //if (is_mu && (pt()<20 || pt()>55))
        //if (is_mu && (pt()<20 || pt()>35))
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
        bool no_w = pfmet()<20 && pfmt()<25;

        // no resonance's (Z or upsilon)
        if (is_mu && ((76<mz_fo_ctf() && mz_fo_ctf()<106) || (8<mupsilon_fo_mu() && mupsilon_fo_mu()<12)))
        {
            return 0;
        }
        else if (is_el && (76<mz_fo_gsf() && mz_fo_gsf()<106))
        {
            return 0;
        }

        // trigger cuts
        bool trig_cut = false;
        if (is_data && is_mu)
        {
            //trig_cut = ((pt() > 30 && (mu15_eta2p1_vstar() > 1 || mu24_eta2p1_vstar() > 1 || mu30_eta2p1_vstar() > 1)) || 
            //            (pt() > 24 && (mu15_eta2p1_vstar() > 1 || mu24_eta2p1_vstar() > 1)) || 
            //            (pt() > 15 && mu15_eta2p1_vstar() > 1) ||
            //            (pt() > 8  && mu8_vstar() > 1));
            trig_cut = ((pt() > 30 && (mu30_eta2p1_vstar() > 1 || mu24_eta2p1_vstar() > 1 || mu17_vstar()>1 || mu8_vstar()>1)) || 
            			(pt() > 24 && (mu24_eta2p1_vstar() > 1 || mu17_vstar()>1 || mu8_vstar()>1)) || 
            			(pt() > 17 && (mu17_vstar()>1 || mu8_vstar()>1)) || 
            			(pt() > 8  && (mu8_vstar()>1)));
        }
        else if (is_data && is_el)
        {
			//trig_cut = ((pt() > 17 && (ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()>1 || ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()>1   || 
                                        //ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()>1 ||  ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()>1)) ||
                        //(pt() > 8  && (ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()>1  || ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()>1)));
            trig_cut =  (pt() > 17 && (ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar() > 1 || ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar() > 1 ||
                                       ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()  > 1 || ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()  > 1 ));
            trig_cut |= (pt() > 8  && (ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()  > 1 || ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()  > 1 ));
        }
        else if (not is_data)
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

        // num jetshttp://en.wikipedia.org/wiki/Cat_behavior
        int njets10 = is_data ? npfcL1Fj1res()   : npfcL1Fj1();
        int njets30 = is_data ? npfc30L1Fj1res() : npfc30L1Fj1();
        int njets40 = is_data ? npfc40L1Fj1res() : npfc40L1Fj1();
        
        // away jet is btagged
        bool btag = is_data ? btagpfcL1Fres() : btagpfcL1F();
        if (not (is_data || is_qcd))
        {
            btag=true;
        }

        // dphi between away jet and lepton
        float ajet_dphi = is_data ? dphipfcL1Fj1res() : dphipfcL1Fj1();
        //float ajet_dr   = is_data ? drpfcL1Fj1res() : drpfcL1Fj1();
        bool dphi2p5_cut = (ajet_dphi > 2.5);
        bool dphi2p8_cut = (ajet_dphi > 2.8);
        bool dphi3p0_cut = (ajet_dphi > 3.0);
        // only apply dphi cut for data and qcd (to get back-to-back)
        //if (not (is_data || is_qcd))
        if (is_ttbar)
        {
            dphi2p5_cut = true;
            dphi2p8_cut = true;
            dphi3p0_cut = true;
        }

        // # bjets
        //bool njets40eq1 = (njets40==1); 

        // away jet cut
        float ajet_pt = is_data ? ptpfcL1Fj1res() : ptpfcL1Fj1();
        bool jet20c_cut      = (ajet_pt > 20);
        bool jet40c_cut      = (ajet_pt > 40);
        bool jet60c_cut      = (ajet_pt > 60);
        //bool jet_cut         = (ajet_pt > m_away_jet_cut && njets40eq1);
        bool jet_cut         = (ajet_pt > m_away_jet_cut);
        bool jet_pt_gt_mu_pt = (ajet_pt > pt());
        //if (not (is_data || is_qcd))
        if (is_ttbar)
        {
            jet20c_cut = true;
            jet40c_cut = true;
            jet60c_cut = true;
            jet_cut=true;
        }

        // single pt and away pt bin
        //if (not ((ajet_pt >= 48 && ajet_pt <= 52) && (pt()>=20 && pt()<=22)))
        //{
        //    return 0;
        //}

        // additional selections
        bool not_from_w = is_ttbar ? leptonIsFromW()<1 : true;
        //bool not_from_w = not (is_data || is_qcd) ? leptonIsFromW()<1 : true;
        //bool not_from_w = is_ttbar ? leptonIsFromW()==-1 : true;
        //bool not_from_w = is_ttbar ? (leptonIsFromW()<1 && leptonIsFromW()!=-1) : true;

        // numerator cut
        bool num_lep_cut = false;
        if (is_mu)
        {
            num_lep_cut = (abs(id()) == 13 && num_mu_ssV5_noIso() && cpfiso03_db()<0.1);
        }
        else if(is_el)
        {
            num_lep_cut = (abs(id()) == 11 && num_el_ssV7_noIso() && cpfiso03_rho()<0.09);
        }

        // denominator cut
        bool fo_lep_cut = false;
        if (is_mu)
        {
            fo_lep_cut = (is_mu && fo_mu_ssV5_noIso() && cpfiso03_db()<0.4);
        }
        else if(is_el)
        {
            fo_lep_cut = (is_el && v3_el_ssV7() && cpfiso03_rho()<0.6);
        }

        // passes selection (no isolaiton)
        //bool num_lep_sel_notrig = (nFOcut && num_lep_cut && btag && not_from_w);
        //bool fo_lep_sel_notrig  = (nFOcut && fo_lep_cut && btag && not_from_w);
        bool num_lep_sel_notrig = (nFOcut && num_lep_cut && not_from_w && no_w);
        bool fo_lep_sel_notrig  = (nFOcut && fo_lep_cut && not_from_w && no_w);
        bool num_lep_sel        = (trig_cut && num_lep_sel_notrig);
        bool fo_lep_sel         = (trig_cut && fo_lep_sel_notrig);

        //if (pt() < 35 && fo_lep_sel && dphi2p5_cut && btag && njets40eq1) { rt::Fill(hc["h_ajet_pt_ptlt35"], ajet_pt    , evt_weight); }
        if (pt() < 35 && fo_lep_sel && dphi2p5_cut && btag)            { rt::Fill(hc["h_ajet_pt_ptlt35"], ajet_pt    , evt_weight); }
        if (pt() < 35 && fo_lep_sel && jet_cut && dphi2p5_cut && btag) { rt::Fill(hc["h_nvtxs_ptlt35"  ], evt_nvtxs(), evt_weight); }

        if (pt() > 35 && fo_lep_sel && dphi2p5_cut && btag)            { rt::Fill(hc["h_ajet_pt_ptgt35"], ajet_pt    , evt_weight); }
        if (pt() > 35 && fo_lep_sel && jet_cut && dphi2p5_cut && btag) { rt::Fill(hc["h_nvtxs_ptgt35"  ], evt_nvtxs(), evt_weight); }

        // mt plots
        if (is_mu && fo_mu_ssV5_noIso() && pfmet()<20 && trig_cut && jet_cut && dphi2p5_cut) 
        { 
            rt::Fill(hc["h_mt_nobtag"], pfmt(), evt_weight);
            if (btag)                        { rt::Fill(hc["h_mt"          ], pfmt(), evt_weight); }
            if (btag && cpfiso03_db() < 0.1) { rt::Fill(hc["h_mt_1stisobin"], pfmt(), evt_weight); }
            if (btag && cpfiso03_db() < 0.2) { rt::Fill(hc["h_mt_2ndisobin"], pfmt(), evt_weight); }
        }

		bool mc3_matched = (mc3id() != -999);
		bool direct_b    = (mc3_matched && abs(mc3id())==5 && idIsBeauty(mcmotherid()) && not_from_w && (pt()<mc3pt()));

        if (fo_lep_sel) 
        { 
            rt::Fill(hc["h_dphi"], ajet_dphi, evt_weight);
            if (mc3_matched)
            {
                rt::Fill2D(hc["h_mc3pt_vs_ajetpt"], mc3pt(), ajet_pt); 
                if (btag)             {rt::Fill2D(hc["h_mc3pt_vs_ajetpt_btag"   ], mc3pt(), ajet_pt);}
                if (btag && direct_b) {rt::Fill2D(hc["h_mc3pt_vs_ajetpt_db_btag"], mc3pt(), ajet_pt);}
            }
        }

        if (no_w && is_mu && fo_mu_ssV5_noIso() && trig_cut && jet_cut && dphi2p5_cut && btag) 
        { 
            if (pt() > 35) {hc["h_pfiso_ptgt35"]->Fill(cpfiso03_db()  , evt_weight);}
            if (pt() < 35) {hc["h_pfiso_ptlt35"]->Fill(cpfiso03_db()  , evt_weight);}

            hc["h_cpfiso_over_pt"                   ]->Fill(cpfiso03_db()                                                       , evt_weight);
            hc["h_pfiso_over_pt"                    ]->Fill(pfiso03()                                                           , evt_weight);
            hc["h_chiso_over_pt"                    ]->Fill(ch_pfiso03()/pt()                                                   , evt_weight);
            hc["h_nhiso_over_pt"                    ]->Fill(nh_pfiso03()/pt()                                                   , evt_weight);
            hc["h_emiso_over_pt"                    ]->Fill(em_pfiso03()/pt()                                                   , evt_weight);
            hc["h_nhiso_plus_emiso_over_pt"         ]->Fill(nh_pfiso03()/pt() + em_pfiso03()/pt()                               , evt_weight);
            hc["h_nhiso_plus_emiso_over_pt_corr"    ]->Fill((nh_pfiso03()/pt() + em_pfiso03()/pt()) - pfpupt03()                , evt_weight);
            hc["h_max_nhiso_plus_emiso_over_pt_corr"]->Fill(std::max(0.0f, (nh_pfiso03()/pt() + em_pfiso03()/pt()) - pfpupt03()), evt_weight);

            hc["h_ecal_iso"]->Fill(ecal_iso()/pt()   , evt_weight);
            hc["h_pfiso"   ]->Fill(pfiso03()*pt()    , evt_weight);
            hc["h_cpfiso"  ]->Fill(cpfiso03_db()*pt(), evt_weight);
            hc["h_chiso"   ]->Fill(ch_pfiso03()      , evt_weight);
            hc["h_nhiso"   ]->Fill(nh_pfiso03()      , evt_weight);
            hc["h_emiso"   ]->Fill(em_pfiso03()      , evt_weight);

            if (evt_nvtxs() >= 14 && evt_nvtxs() <= 16) { hc["h_pfiso_over_pt_nvtxs14-16"]->Fill(cpfiso03_db()    , evt_weight); }
            if (evt_nvtxs() >= 14 && evt_nvtxs() <= 16) { hc["h_chiso_over_pt_nvtxs14-16"]->Fill(ch_pfiso03()/pt(), evt_weight); }
            if (evt_nvtxs() >= 14 && evt_nvtxs() <= 16) { hc["h_nhiso_over_pt_nvtxs14-16"]->Fill(nh_pfiso03()/pt(), evt_weight); }
            if (evt_nvtxs() >= 14 && evt_nvtxs() <= 16) { hc["h_emiso_over_pt_nvtxs14-16"]->Fill(em_pfiso03()/pt(), evt_weight); }
        }

		// skip if not FO
        if (!fo_lep_sel)
        {
            return 0;
        }

        // muons
        // ----------------------------------------------------------------------------------------------------------------------------//
       
        // Fill Fake Rates 
        if (m_lepton == "mu")
        {

            if (jet_cut && dphi2p5_cut && btag)
            {
                rt::Fill(hc["h_dbeta"], pfpupt03(), evt_weight);
                if (evt_nvtxs() >= 11 && evt_nvtxs() <= 13) { rt::Fill(hc["h_dbeta_nvtxs11-13" ], pfpupt03(), evt_weight); }
                if (evt_nvtxs() >= 14 && evt_nvtxs() <= 16) { rt::Fill(hc["h_dbeta_nvtxs14-16" ], pfpupt03(), evt_weight); }
                if (evt_nvtxs() >= 17 && evt_nvtxs() <= 19) { rt::Fill(hc["h_dbeta_nvtxs17-19" ], pfpupt03(), evt_weight); }

                rt::Fill2D(hc["h_dbeta_vs_nvtxs"], evt_nvtxs(), pfpupt03(), evt_weight);

                rt::Fill(hc["h_njets10"], njets10, evt_weight);
                rt::Fill(hc["h_njets30"], njets30, evt_weight);
                rt::Fill(hc["h_njets40"], njets40, evt_weight);
            }
            

            // numerator
            if (num_lep_sel)
            {
                if (jet20c_cut && pt()>20) { rt::Fill( hc["h_mu_num20c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                if (jet40c_cut && pt()>20) { rt::Fill( hc["h_mu_num40c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                if (jet60c_cut && pt()>20) { rt::Fill( hc["h_mu_num60c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                if (jet20c_cut) { rt::Fill2D(hc["h_mu_num20c"], fabs(eta()), pt(), evt_weight); } 
                if (jet40c_cut) { rt::Fill2D(hc["h_mu_num40c"], fabs(eta()), pt(), evt_weight); } 
                if (jet60c_cut) { rt::Fill2D(hc["h_mu_num60c"], fabs(eta()), pt(), evt_weight); } 
                
                if (jet40c_cut && btag) { rt::Fill2D(hc["h_mu_num40c_btag"], fabs(eta()), pt(), evt_weight); } 
                
                if (jet40c_cut && dphi2p5_cut) { rt::Fill2D(hc["h_mu_num_dphi2p5"], fabs(eta()), pt(), evt_weight); } 
                if (jet40c_cut && dphi2p8_cut) { rt::Fill2D(hc["h_mu_num_dphi2p8"], fabs(eta()), pt(), evt_weight); } 
                if (jet40c_cut && dphi3p0_cut) { rt::Fill2D(hc["h_mu_num_dphi3p0"], fabs(eta()), pt(), evt_weight); } 

                if (jet40c_cut && dphi2p5_cut && btag) { rt::Fill2D(hc["h_mu_num_dphi2p5_btag"], fabs(eta()), pt(), evt_weight); } 
                if (jet40c_cut && dphi2p8_cut && btag) { rt::Fill2D(hc["h_mu_num_dphi2p8_btag"], fabs(eta()), pt(), evt_weight); } 
                if (jet40c_cut && dphi3p0_cut && btag) { rt::Fill2D(hc["h_mu_num_dphi3p0_btag"], fabs(eta()), pt(), evt_weight); } 

                if (jet40c_cut && dphi2p5_cut && jet_pt_gt_mu_pt && pt()>20)         { rt::Fill( hc["h_mu_num40c_dphi2p5_vs_nvtxs"     ], evt_nvtxs(), evt_weight); } 
                if (jet40c_cut && dphi2p5_cut && jet_pt_gt_mu_pt && pt()>20 && btag) { rt::Fill( hc["h_mu_num40c_dphi2p5_btag_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
            }

            if (fo_lep_sel)
            {
                
                if (jet20c_cut && pt()>20) { rt::Fill( hc["h_mu_fo20c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                if (jet40c_cut && pt()>20) { rt::Fill( hc["h_mu_fo40c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                if (jet60c_cut && pt()>20) { rt::Fill( hc["h_mu_fo60c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                if (jet20c_cut) { rt::Fill2D(hc["h_mu_fo20c"], fabs(eta()), pt(), evt_weight); } 
                if (jet40c_cut) { rt::Fill2D(hc["h_mu_fo40c"], fabs(eta()), pt(), evt_weight); } 
                if (jet60c_cut) { rt::Fill2D(hc["h_mu_fo60c"], fabs(eta()), pt(), evt_weight); } 
                
                if (jet40c_cut && btag) { rt::Fill2D(hc["h_mu_fo40c_btag"], fabs(eta()), pt(), evt_weight); } 

                if (jet40c_cut && dphi2p5_cut) { rt::Fill2D(hc["h_mu_fo_dphi2p5"], fabs(eta()), pt(), evt_weight); } 
                if (jet40c_cut && dphi2p8_cut) { rt::Fill2D(hc["h_mu_fo_dphi2p8"], fabs(eta()), pt(), evt_weight); } 
                if (jet40c_cut && dphi3p0_cut) { rt::Fill2D(hc["h_mu_fo_dphi3p0"], fabs(eta()), pt(), evt_weight); } 

                if (jet40c_cut && dphi2p5_cut && btag) { rt::Fill2D(hc["h_mu_fo_dphi2p5_btag"], fabs(eta()), pt(), evt_weight); } 
                if (jet40c_cut && dphi2p8_cut && btag) { rt::Fill2D(hc["h_mu_fo_dphi2p8_btag"], fabs(eta()), pt(), evt_weight); } 
                if (jet40c_cut && dphi3p0_cut && btag) { rt::Fill2D(hc["h_mu_fo_dphi3p0_btag"], fabs(eta()), pt(), evt_weight); } 

                if (jet40c_cut && dphi2p5_cut && jet_pt_gt_mu_pt && pt()>20)         { rt::Fill( hc["h_mu_fo40c_dphi2p5_vs_nvtxs"     ], evt_nvtxs(), evt_weight); } 
                if (jet40c_cut && dphi2p5_cut && jet_pt_gt_mu_pt && pt()>20 && btag) { rt::Fill( hc["h_mu_fo40c_dphi2p5_btag_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
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

                if (cpfiso03_rho()<0.09 )
                {
                    if (jet20c_cut && pt()>20) { rt::Fill( hc["h_el_num20c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet40c_cut && pt()>20) { rt::Fill( hc["h_el_num40c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet60c_cut && pt()>20) { rt::Fill( hc["h_el_num60c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet20c_cut           ) { rt::Fill2D(hc["h_el_num20c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet40c_cut           ) { rt::Fill2D(hc["h_el_num40c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet60c_cut           ) { rt::Fill2D(hc["h_el_num60c"], fabs(eta()), pt(), evt_weight); } 
                }
            }

            // denominator 
            if (fo_lep_sel)
            {
                if (cpfiso03_rho()<0.6)
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

    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
    }

    // analysis end
    return 0;
} 
