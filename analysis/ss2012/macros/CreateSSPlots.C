#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "TChain.h"
#include "THStack.h"
#include "TH1.h"
#include "rt/TDRStyle.h"
#include "rt/TH1Container.h"
#include "rt/TH1Overlay.h"
#include "rt/MiscTools.h"

using namespace std;

struct bins_t
{
    int nbins;
    float min;
    float max;
};

void SetAliases(TChain& chain)
{
    chain.SetAlias("pt1"     , "lep1_p4.pt()"     ); 
    chain.SetAlias("pt2"     , "lep2_p4.pt()"     ); 
    chain.SetAlias("eta1"    , "lep1_p4.eta()"    ); 
    chain.SetAlias("eta2"    , "lep2_p4.eta()"    ); 
    chain.SetAlias("phi1"    , "lep1_p4.Phi()"    ); 
    chain.SetAlias("phi2"    , "lep2_p4.Phi()"    ); 
    chain.SetAlias("l1_pt"   , "lep1_p4.pt()"     ); 
    chain.SetAlias("l2_pt"   , "lep2_p4.pt()"     ); 
    chain.SetAlias("l1_eta"  , "lep1_p4.eta()"    ); 
    chain.SetAlias("l2_eta"  , "lep2_p4.eta()"    ); 
    chain.SetAlias("l1_phi"  , "lep1_p4.phi()"    ); 
    chain.SetAlias("l2_phi"  , "lep2_p4.phi()"    ); 
    chain.SetAlias("l1_z0"   , "lep1_dz"          ); 
    chain.SetAlias("l2_z0"   , "lep2_dz"          ); 
    chain.SetAlias("deta"    , "dilep_deta"       ); 
    chain.SetAlias("dphi"    , "dilep_dphi"       ); 
    chain.SetAlias("dr"      , "dilep_dr"         ); 
    chain.SetAlias("dr_l1_bj", "lep1_nearbjet_dr" ); 
    chain.SetAlias("dr_l2_bj", "lep2_nearbjet_dr" ); 
    chain.SetAlias("dr_b1_b2", "bjets_dr12"        ); 
    chain.SetAlias("dr_bj_nj", "vbjets_nearjet_dr" ); 
    return;
}

void AddHist(TH1* h_result, TH1* h1, TH1* h2, float w1 = 1.0, float w2 = 1.0)
{
	for (int bin = 1; bin != h1->GetNbinsX()+1; bin++)
	{
		float v1 = w1*h1->GetBinContent(bin);
		float v2 = w2*h2->GetBinContent(bin);
		float result = std::max(0.0f, v1 + v2);
		h_result->SetBinContent(bin, result);
	}
	return;
}

struct sample_t
{
    sample_t(const string& n, const string& t, Color_t c, Style_t m) : name(n), title(t), color(c), marker(m), chain(new TChain("tree")) {}
    string name;
    string title;
    Color_t color;
    Style_t marker;
    TChain* chain;
};

void InitChain(sample_t sample)
{
    sample.chain->Add(Form("babies/52X/%s.root", sample.name.c_str())); 
}

void CreateSSPlots(float lumi = 1.0, unsigned int signal_region_num = 0, const std::string& suffix = "png")
{
	// set style
    rt::SetStyle();

    // get the datasets
    // samples to overlay
    std::vector<sample_t> samples;
    samples.push_back(sample_t("data" , "data"           , kOrange-3 , 0));
    samples.push_back(sample_t("wz"   , "WZ"             , kCyan-5   , 0));
    samples.push_back(sample_t("zz"   , "ZZ"             , kOrange-3 , 0));
    samples.push_back(sample_t("ttg"  , "t#bar{t}#gamma" , kBlue-7   , 0));
    samples.push_back(sample_t("ttw"  , "t#bar{t}W"      , kBlue-7   , 0));
    samples.push_back(sample_t("ttww" , "t#bar{t}WW"     , kBlue-7   , 0));
    samples.push_back(sample_t("ttz"  , "t#bar{t}Z"      , kGreen+2  , 0));
    samples.push_back(sample_t("wwg"  , "WW#gamma"       , kOrange-3 , 0));
    samples.push_back(sample_t("www"  , "www"            , kOrange-3 , 0));
    samples.push_back(sample_t("wwz"  , "wwz"            , kOrange-3 , 0));
    samples.push_back(sample_t("wzz"  , "wzz"            , kOrange-3 , 0));
    samples.push_back(sample_t("wzz"  , "wzz"            , kOrange-3 , 0));

    // set the chains
    for (size_t i = 0; i != samples.size(); i++)
    {
        InitChain(samples[i]);
    }


    // bins
    bins_t pt_bins     = {25,    0,  250};
    bins_t eta_bins    = {10, -2.5,  2.5};
    bins_t phi_bins    = {14, -3.5,  3.5};
    bins_t deta_bins   = {10,    0,  5.0};
    bins_t dphi_bins   = { 7,    0,  3.5};
    bins_t dr_bins     = {11,    0,  5.5};
    bins_t met_bins    = {25,    0,  300};
    bins_t ht_bins     = {20,    0,  800};
    bins_t nbtags_bins = { 6, -0.5,  5.5};
    bins_t njets_bins  = { 8, -0.5,  7.5};
    bins_t z0_bins     = {40, -0.2,  0.2};

    // book hists
    rt::TH1Container hc;
    hc.Add(new TH1F("h_data_pt1"     , "lepton1 p_{T} (data); p_{T} (GeV)"                                 , pt_bins.nbins     , pt_bins.min     , pt_bins.max     )); 
    hc.Add(new TH1F("h_data_pt2"     , "lepton2 p_{T} (data); p_{T} (GeV)"                                 , pt_bins.nbins     , pt_bins.min     , pt_bins.max     )); 
    hc.Add(new TH1F("h_data_eta1"    , "lepton1 #eta (data); #eta"                                         , eta_bins.nbins    , eta_bins.min    , eta_bins.max    )); 
    hc.Add(new TH1F("h_data_eta2"    , "lepton2 #eta (data); #eta"                                         , eta_bins.nbins    , eta_bins.min    , eta_bins.max    )); 
    hc.Add(new TH1F("h_data_phi1"    , "lepton1 #phi (data); #phi"                                         , phi_bins.nbins    , phi_bins.min    , phi_bins.max    )); 
    hc.Add(new TH1F("h_data_phi2"    , "lepton2 #phi (data); #phi"                                         , phi_bins.nbins    , phi_bins.min    , phi_bins.max    )); 
    hc.Add(new TH1F("h_data_z01"     , "lepton1 z_{0} (data); z_{0}"                                       , z0_bins.nbins     , z0_bins.min     , z0_bins.max     )); 
    hc.Add(new TH1F("h_data_z02"     , "lepton2 z_{0} (data); z_{0}"                                       , z0_bins.nbins     , z0_bins.min     , z0_bins.max     )); 
    hc.Add(new TH1F("h_data_deta"    , "lepton2 #Delta#eta (data); |#Delta#eta|"                           , deta_bins.nbins   , deta_bins.min   , deta_bins.max   )); 
    hc.Add(new TH1F("h_data_dphi"    , "lepton2 #Delta#phi (data); |#Delta#phi|"                           , dphi_bins.nbins   , dphi_bins.min   , dphi_bins.max   )); 
    hc.Add(new TH1F("h_data_dr"      , "lepton2 #DeltaR (data); |#DeltaR|"                                 , dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_data_met"     , "missing E_{T} (data); E^{miss}_{T} (GeV)"                          , met_bins.nbins    , met_bins.min    , met_bins.max    )); 
    hc.Add(new TH1F("h_data_ht"      , "H_{T} (data); H_{T} (GeV)"                                         , ht_bins.nbins     , ht_bins.min     , ht_bins.max     )); 
    hc.Add(new TH1F("h_data_nbtags"  , "# btags (data); # btags"                                           , nbtags_bins.nbins , nbtags_bins.min , nbtags_bins.max )); 
    hc.Add(new TH1F("h_data_njets"   , "# jets (data); # jets"                                             , njets_bins.nbins  , njets_bins.min  , njets_bins.max  )); 
    hc.Add(new TH1F("h_data_dr_l1_bj", "#DeltaR(lepton1, nearest bjet) (data); #DeltaR(lep1, nearest bjet)", dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_data_dr_l2_bj", "#DeltaR(lepton2, nearest bjet) (data); #DeltaR(lep1, nearest bjet)", dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_data_dr_b1_b2", "#DeltaR(bjet1, bjet2) (data); #DeltaR(bjet1, bjet2)"               , dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_data_dr_bj_nj", "#DeltaR(bjet, nontagged jet) (data); #DeltaR(bjet, nontagged jet)" , dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Sumw2();
        
    hc.Add(new TH1F("h_fake_pt1"     , "lepton1 p_{T} (fake); p_{T} (GeV)"                                 , pt_bins.nbins     , pt_bins.min     , pt_bins.max     )); 
    hc.Add(new TH1F("h_fake_pt2"     , "lepton2 p_{T} (fake); p_{T} (GeV)"                                 , pt_bins.nbins     , pt_bins.min     , pt_bins.max     )); 
    hc.Add(new TH1F("h_fake_eta1"    , "lepton1 #eta (fake); #eta"                                         , eta_bins.nbins    , eta_bins.min    , eta_bins.max    )); 
    hc.Add(new TH1F("h_fake_eta2"    , "lepton2 #eta (fake); #eta"                                         , eta_bins.nbins    , eta_bins.min    , eta_bins.max    )); 
    hc.Add(new TH1F("h_fake_phi1"    , "lepton1 #phi (fake); #phi"                                         , phi_bins.nbins    , phi_bins.min    , phi_bins.max    )); 
    hc.Add(new TH1F("h_fake_phi2"    , "lepton2 #phi (fake); #phi"                                         , phi_bins.nbins    , phi_bins.min    , phi_bins.max    )); 
    hc.Add(new TH1F("h_fake_z01"     , "lepton1 z_{0} (fake); z_{0}"                                       , z0_bins.nbins     , z0_bins.min     , z0_bins.max     )); 
    hc.Add(new TH1F("h_fake_z02"     , "lepton2 z_{0} (fake); z_{0}"                                       , z0_bins.nbins     , z0_bins.min     , z0_bins.max     )); 
    hc.Add(new TH1F("h_fake_deta"    , "lepton2 #Delta#eta (fake); |#Delta#eta|"                           , deta_bins.nbins   , deta_bins.min   , deta_bins.max   )); 
    hc.Add(new TH1F("h_fake_dphi"    , "lepton2 #Delta#phi (fake); |#Delta#phi|"                           , dphi_bins.nbins   , dphi_bins.min   , dphi_bins.max   )); 
    hc.Add(new TH1F("h_fake_dr"      , "lepton2 #DeltaR (fake); |#DeltaR|"                                 , dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_fake_met"     , "missing E_{T} (fake); E^{miss}_{T} (GeV)"                          , met_bins.nbins    , met_bins.min    , met_bins.max    )); 
    hc.Add(new TH1F("h_fake_ht"      , "H_{T} (fake); H_{T} (GeV)"                                         , ht_bins.nbins     , ht_bins.min     , ht_bins.max     )); 
    hc.Add(new TH1F("h_fake_nbtags"  , "# btags (fake); # btags"                                           , nbtags_bins.nbins , nbtags_bins.min , nbtags_bins.max )); 
    hc.Add(new TH1F("h_fake_njets"   , "# jets (fake); # jets"                                             , njets_bins.nbins  , njets_bins.min  , njets_bins.max  )); 
    hc.Add(new TH1F("h_fake_dr_l1_bj", "#DeltaR(lepton1, nearest bjet) (fake); #DeltaR(lep1, nearest bjet)", dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_fake_dr_l2_bj", "#DeltaR(lepton2, nearest bjet) (fake); #DeltaR(lep1, nearest bjet)", dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_fake_dr_b1_b2", "#DeltaR(bjet1, bjet2) (fake); #DeltaR(bjet1, bjet2)"               , dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_fake_dr_bj_nj", "#DeltaR(bjet, nontagged jet) (fake); #DeltaR(bjet, nontagged jet)" , dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 

    hc.Add(new TH1F("h_sf_pt1"     , "lepton1 p_{T} (sf); p_{T} (GeV)"                                 , pt_bins.nbins     , pt_bins.min     , pt_bins.max     )); 
    hc.Add(new TH1F("h_sf_pt2"     , "lepton2 p_{T} (sf); p_{T} (GeV)"                                 , pt_bins.nbins     , pt_bins.min     , pt_bins.max     )); 
    hc.Add(new TH1F("h_sf_eta1"    , "lepton1 #eta (sf); #eta"                                         , eta_bins.nbins    , eta_bins.min    , eta_bins.max    )); 
    hc.Add(new TH1F("h_sf_eta2"    , "lepton2 #eta (sf); #eta"                                         , eta_bins.nbins    , eta_bins.min    , eta_bins.max    )); 
    hc.Add(new TH1F("h_sf_phi1"    , "lepton1 #phi (sf); #phi"                                         , phi_bins.nbins    , phi_bins.min    , phi_bins.max    )); 
    hc.Add(new TH1F("h_sf_phi2"    , "lepton2 #phi (sf); #phi"                                         , phi_bins.nbins    , phi_bins.min    , phi_bins.max    )); 
    hc.Add(new TH1F("h_sf_z01"     , "lepton1 z_{0} (sf); z_{0}"                                       , z0_bins.nbins     , z0_bins.min     , z0_bins.max     )); 
    hc.Add(new TH1F("h_sf_z02"     , "lepton2 z_{0} (sf); z_{0}"                                       , z0_bins.nbins     , z0_bins.min     , z0_bins.max     )); 
    hc.Add(new TH1F("h_sf_deta"    , "lepton2 #Delta#eta (sf); |#Delta#eta|"                           , deta_bins.nbins   , deta_bins.min   , deta_bins.max   )); 
    hc.Add(new TH1F("h_sf_dphi"    , "lepton2 #Delta#phi (sf); |#Delta#phi|"                           , dphi_bins.nbins   , dphi_bins.min   , dphi_bins.max   )); 
    hc.Add(new TH1F("h_sf_dr"      , "lepton2 #DeltaR (sf); |#DeltaR|"                                 , dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_sf_met"     , "missing E_{T} (sf); E^{miss}_{T} (GeV)"                          , met_bins.nbins    , met_bins.min    , met_bins.max    )); 
    hc.Add(new TH1F("h_sf_ht"      , "H_{T} (sf); H_{T} (GeV)"                                         , ht_bins.nbins     , ht_bins.min     , ht_bins.max     )); 
    hc.Add(new TH1F("h_sf_nbtags"  , "# btags (sf); # btags"                                           , nbtags_bins.nbins , nbtags_bins.min , nbtags_bins.max )); 
    hc.Add(new TH1F("h_sf_njets"   , "# jets (sf); # jets"                                             , njets_bins.nbins  , njets_bins.min  , njets_bins.max  )); 
    hc.Add(new TH1F("h_sf_dr_l1_bj", "#DeltaR(lepton1, nearest bjet) (sf); #DeltaR(lep1, nearest bjet)", dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_sf_dr_l2_bj", "#DeltaR(lepton2, nearest bjet) (sf); #DeltaR(lep1, nearest bjet)", dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_sf_dr_b1_b2", "#DeltaR(bjet1, bjet2) (sf); #DeltaR(bjet1, bjet2)"               , dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_sf_dr_bj_nj", "#DeltaR(bjet, nontagged jet) (sf); #DeltaR(bjet, nontagged jet)" , dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 

    hc.Add(new TH1F("h_df_pt1"     , "lepton1 p_{T} (df); p_{T} (GeV)"                                 , pt_bins.nbins     , pt_bins.min     , pt_bins.max     )); 
    hc.Add(new TH1F("h_df_pt2"     , "lepton2 p_{T} (df); p_{T} (GeV)"                                 , pt_bins.nbins     , pt_bins.min     , pt_bins.max     )); 
    hc.Add(new TH1F("h_df_eta1"    , "lepton1 #eta (df); #eta"                                         , eta_bins.nbins    , eta_bins.min    , eta_bins.max    )); 
    hc.Add(new TH1F("h_df_eta2"    , "lepton2 #eta (df); #eta"                                         , eta_bins.nbins    , eta_bins.min    , eta_bins.max    )); 
    hc.Add(new TH1F("h_df_phi1"    , "lepton1 #phi (df); #phi"                                         , phi_bins.nbins    , phi_bins.min    , phi_bins.max    )); 
    hc.Add(new TH1F("h_df_phi2"    , "lepton2 #phi (df); #phi"                                         , phi_bins.nbins    , phi_bins.min    , phi_bins.max    )); 
    hc.Add(new TH1F("h_df_z01"     , "lepton1 z_{0} (df); z_{0}"                                       , z0_bins.nbins     , z0_bins.min     , z0_bins.max     )); 
    hc.Add(new TH1F("h_df_z02"     , "lepton2 z_{0} (df); z_{0}"                                       , z0_bins.nbins     , z0_bins.min     , z0_bins.max     )); 
    hc.Add(new TH1F("h_df_deta"    , "lepton2 #Delta#eta (df); |#Delta#eta|"                           , deta_bins.nbins   , deta_bins.min   , deta_bins.max   )); 
    hc.Add(new TH1F("h_df_dphi"    , "lepton2 #Delta#phi (df); |#Delta#phi|"                           , dphi_bins.nbins   , dphi_bins.min   , dphi_bins.max   )); 
    hc.Add(new TH1F("h_df_dr"      , "lepton2 #DeltaR (df); |#DeltaR|"                                 , dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_df_met"     , "missing E_{T} (df); E^{miss}_{T} (GeV)"                          , met_bins.nbins    , met_bins.min    , met_bins.max    )); 
    hc.Add(new TH1F("h_df_ht"      , "H_{T} (df); H_{T} (GeV)"                                         , ht_bins.nbins     , ht_bins.min     , ht_bins.max     )); 
    hc.Add(new TH1F("h_df_nbtags"  , "# btags (df); # btags"                                           , nbtags_bins.nbins , nbtags_bins.min , nbtags_bins.max )); 
    hc.Add(new TH1F("h_df_njets"   , "# jets (df); # jets"                                             , njets_bins.nbins  , njets_bins.min  , njets_bins.max  )); 
    hc.Add(new TH1F("h_df_dr_l1_bj", "#DeltaR(lepton1, nearest bjet) (df); #DeltaR(lep1, nearest bjet)", dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_df_dr_l2_bj", "#DeltaR(lepton2, nearest bjet) (df); #DeltaR(lep1, nearest bjet)", dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_df_dr_b1_b2", "#DeltaR(bjet1, bjet2) (df); #DeltaR(bjet1, bjet2)"               , dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_df_dr_bj_nj", "#DeltaR(bjet, nontagged jet) (df); #DeltaR(bjet, nontagged jet)" , dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 

    hc.Add(new TH1F("h_flip_pt1"     , "lepton1 p_{T} (flip); p_{T} (GeV)"                                 , pt_bins.nbins     , pt_bins.min     , pt_bins.max     )); 
    hc.Add(new TH1F("h_flip_pt2"     , "lepton2 p_{T} (flip); p_{T} (GeV)"                                 , pt_bins.nbins     , pt_bins.min     , pt_bins.max     )); 
    hc.Add(new TH1F("h_flip_eta1"    , "lepton1 #eta (flip); #eta"                                         , eta_bins.nbins    , eta_bins.min    , eta_bins.max    )); 
    hc.Add(new TH1F("h_flip_eta2"    , "lepton2 #eta (flip); #eta"                                         , eta_bins.nbins    , eta_bins.min    , eta_bins.max    )); 
    hc.Add(new TH1F("h_flip_phi1"    , "lepton1 #phi (flip); #phi"                                         , phi_bins.nbins    , phi_bins.min    , phi_bins.max    )); 
    hc.Add(new TH1F("h_flip_phi2"    , "lepton2 #phi (flip); #phi"                                         , phi_bins.nbins    , phi_bins.min    , phi_bins.max    )); 
    hc.Add(new TH1F("h_flip_z01"     , "lepton1 z_{0} (flip); z_{0}"                                       , z0_bins.nbins     , z0_bins.min     , z0_bins.max     )); 
    hc.Add(new TH1F("h_flip_z02"     , "lepton2 z_{0} (flip); z_{0}"                                       , z0_bins.nbins     , z0_bins.min     , z0_bins.max     )); 
    hc.Add(new TH1F("h_flip_deta"    , "lepton2 #Delta#eta (flip); |#Delta#eta|"                           , deta_bins.nbins   , deta_bins.min   , deta_bins.max   )); 
    hc.Add(new TH1F("h_flip_dphi"    , "lepton2 #Delta#phi (flip); |#Delta#phi|"                           , dphi_bins.nbins   , dphi_bins.min   , dphi_bins.max   )); 
    hc.Add(new TH1F("h_flip_dr"      , "lepton2 #DeltaR (flip); |#DeltaR|"                                 , dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_flip_met"     , "missing E_{T} (flip); E^{miss}_{T} (GeV)"                          , met_bins.nbins    , met_bins.min    , met_bins.max    )); 
    hc.Add(new TH1F("h_flip_ht"      , "H_{T} (flip); H_{T} (GeV)"                                         , ht_bins.nbins     , ht_bins.min     , ht_bins.max     )); 
    hc.Add(new TH1F("h_flip_nbtags"  , "# btags (flip); # btags"                                           , nbtags_bins.nbins , nbtags_bins.min , nbtags_bins.max )); 
    hc.Add(new TH1F("h_flip_njets"   , "# jets (flip); # jets"                                             , njets_bins.nbins  , njets_bins.min  , njets_bins.max  )); 
    hc.Add(new TH1F("h_flip_dr_l1_bj", "#DeltaR(lepton1, nearest bjet) (flip); #DeltaR(lep1, nearest bjet)", dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_flip_dr_l2_bj", "#DeltaR(lepton2, nearest bjet) (flip); #DeltaR(lep1, nearest bjet)", dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_flip_dr_b1_b2", "#DeltaR(bjet1, bjet2) (flip); #DeltaR(bjet1, bjet2)"               , dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_flip_dr_bj_nj", "#DeltaR(bjet, nontagged jet) (flip); #DeltaR(bjet, nontagged jet)" , dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 

    hc.Add(new TH1F("h_mc_pt1"     , "lepton1 p_{T} (mc); p_{T} (GeV)"                                 , pt_bins.nbins     , pt_bins.min     , pt_bins.max     )); 
    hc.Add(new TH1F("h_mc_pt2"     , "lepton2 p_{T} (mc); p_{T} (GeV)"                                 , pt_bins.nbins     , pt_bins.min     , pt_bins.max     )); 
    hc.Add(new TH1F("h_mc_eta1"    , "lepton1 #eta (mc); #eta"                                         , eta_bins.nbins    , eta_bins.min    , eta_bins.max    )); 
    hc.Add(new TH1F("h_mc_eta2"    , "lepton2 #eta (mc); #eta"                                         , eta_bins.nbins    , eta_bins.min    , eta_bins.max    )); 
    hc.Add(new TH1F("h_mc_phi1"    , "lepton1 #phi (mc); #phi"                                         , phi_bins.nbins    , phi_bins.min    , phi_bins.max    )); 
    hc.Add(new TH1F("h_mc_phi2"    , "lepton2 #phi (mc); #phi"                                         , phi_bins.nbins    , phi_bins.min    , phi_bins.max    )); 
    hc.Add(new TH1F("h_mc_z01"     , "lepton1 z_{0} (mc); z_{0}"                                       , z0_bins.nbins     , z0_bins.min     , z0_bins.max     )); 
    hc.Add(new TH1F("h_mc_z02"     , "lepton2 z_{0} (mc); z_{0}"                                       , z0_bins.nbins     , z0_bins.min     , z0_bins.max     )); 
    hc.Add(new TH1F("h_mc_deta"    , "lepton2 #Delta#eta (mc); |#Delta#eta|"                           , deta_bins.nbins   , deta_bins.min   , deta_bins.max   )); 
    hc.Add(new TH1F("h_mc_dphi"    , "lepton2 #Delta#phi (mc); |#Delta#phi|"                           , dphi_bins.nbins   , dphi_bins.min   , dphi_bins.max   )); 
    hc.Add(new TH1F("h_mc_dr"      , "lepton2 #DeltaR (mc); |#DeltaR|"                                 , dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_mc_met"     , "missing E_{T} (mc); E^{miss}_{T} (GeV)"                          , met_bins.nbins    , met_bins.min    , met_bins.max    )); 
    hc.Add(new TH1F("h_mc_ht"      , "H_{T} (mc); H_{T} (GeV)"                                         , ht_bins.nbins     , ht_bins.min     , ht_bins.max     )); 
    hc.Add(new TH1F("h_mc_nbtags"  , "# btags (mc); # btags"                                           , nbtags_bins.nbins , nbtags_bins.min , nbtags_bins.max )); 
    hc.Add(new TH1F("h_mc_njets"   , "# jets (mc); # jets"                                             , njets_bins.nbins  , njets_bins.min  , njets_bins.max  )); 
    hc.Add(new TH1F("h_mc_dr_l1_bj", "#DeltaR(lepton1, nearest bjet) (mc); #DeltaR(lep1, nearest bjet)", dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_mc_dr_l2_bj", "#DeltaR(lepton2, nearest bjet) (mc); #DeltaR(lep1, nearest bjet)", dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_mc_dr_b1_b2", "#DeltaR(bjet1, bjet2) (mc); #DeltaR(bjet1, bjet2)"               , dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    hc.Add(new TH1F("h_mc_dr_bj_nj", "#DeltaR(bjet, nontagged jet) (mc); #DeltaR(bjet, nontagged jet)" , dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 

    for (size_t i = 1; i != samples.size(); i++)
    {
        const string& name  = samples[i].name.c_str();
        const string& title = samples[i].title.c_str();

        hc.Add(new TH1F(Form("h_%s_pt1"     , name.c_str()), Form("lepton1 p_{T} (%s); p_{T} (GeV)"                                 , title.c_str()), pt_bins.nbins     , pt_bins.min     , pt_bins.max     )); 
        hc.Add(new TH1F(Form("h_%s_pt2"     , name.c_str()), Form("lepton2 p_{T} (%s); p_{T} (GeV)"                                 , title.c_str()), pt_bins.nbins     , pt_bins.min     , pt_bins.max     )); 
        hc.Add(new TH1F(Form("h_%s_eta1"    , name.c_str()), Form("lepton1 #eta (%s); #eta"                                         , title.c_str()), eta_bins.nbins    , eta_bins.min    , eta_bins.max    )); 
        hc.Add(new TH1F(Form("h_%s_eta2"    , name.c_str()), Form("lepton2 #eta (%s); #eta"                                         , title.c_str()), eta_bins.nbins    , eta_bins.min    , eta_bins.max    )); 
        hc.Add(new TH1F(Form("h_%s_phi1"    , name.c_str()), Form("lepton1 #phi (%s); #phi"                                         , title.c_str()), phi_bins.nbins    , phi_bins.min    , phi_bins.max    )); 
        hc.Add(new TH1F(Form("h_%s_phi2"    , name.c_str()), Form("lepton2 #phi (%s); #phi"                                         , title.c_str()), phi_bins.nbins    , phi_bins.min    , phi_bins.max    )); 
        hc.Add(new TH1F(Form("h_%s_z01"     , name.c_str()), Form("lepton1 z_{0} (%s); z_{0}"                                       , title.c_str()), z0_bins.nbins     , z0_bins.min     , z0_bins.max     )); 
        hc.Add(new TH1F(Form("h_%s_z02"     , name.c_str()), Form("lepton2 z_{0} (%s); z_{0}"                                       , title.c_str()), z0_bins.nbins     , z0_bins.min     , z0_bins.max     )); 
        hc.Add(new TH1F(Form("h_%s_deta"    , name.c_str()), Form("lepton2 #Delta#eta (%s); |#Delta#eta|"                           , title.c_str()), deta_bins.nbins   , deta_bins.min   , deta_bins.max   )); 
        hc.Add(new TH1F(Form("h_%s_dphi"    , name.c_str()), Form("lepton2 #Delta#phi (%s); |#Delta#phi|"                           , title.c_str()), dphi_bins.nbins   , dphi_bins.min   , dphi_bins.max   )); 
        hc.Add(new TH1F(Form("h_%s_dr"      , name.c_str()), Form("lepton2 #DeltaR (%s); |#DeltaR|"                                 , title.c_str()), dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
        hc.Add(new TH1F(Form("h_%s_met"     , name.c_str()), Form("missing E_{T} (%s); E^{miss}_{T} (GeV)"                          , title.c_str()), met_bins.nbins    , met_bins.min    , met_bins.max    )); 
        hc.Add(new TH1F(Form("h_%s_ht"      , name.c_str()), Form("H_{T} (%s); H_{T} (GeV)"                                         , title.c_str()), ht_bins.nbins     , ht_bins.min     , ht_bins.max     )); 
        hc.Add(new TH1F(Form("h_%s_nbtags"  , name.c_str()), Form("# btags (%s); # btags"                                           , title.c_str()), nbtags_bins.nbins , nbtags_bins.min , nbtags_bins.max )); 
        hc.Add(new TH1F(Form("h_%s_njets"   , name.c_str()), Form("# jets (%s); # jets"                                             , title.c_str()), njets_bins.nbins  , njets_bins.min  , njets_bins.max  )); 
        hc.Add(new TH1F(Form("h_%s_dr_l1_bj", name.c_str()), Form("#DeltaR(lepton1, nearest bjet) (%s); #DeltaR(lep1, nearest bjet)", title.c_str()), dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
        hc.Add(new TH1F(Form("h_%s_dr_l2_bj", name.c_str()), Form("#DeltaR(lepton2, nearest bjet) (%s); #DeltaR(lep1, nearest bjet)", title.c_str()), dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
        hc.Add(new TH1F(Form("h_%s_dr_b1_b2", name.c_str()), Form("#DeltaR(bjet1, bjet2) (%s); #DeltaR(bjet1, bjet2)"               , title.c_str()), dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
        hc.Add(new TH1F(Form("h_%s_dr_bj_nj", name.c_str()), Form("#DeltaR(bjet, nontagged jet) (%s); #DeltaR(bjet, nontagged jet)" , title.c_str()), dr_bins.nbins     , dr_bins.min     , dr_bins.max     )); 
    }

    // selections
    string ss_selection = "is_ss && nbtags>1";
    switch (signal_region_num)
    {
        case 0: ss_selection + " && ht>80 && pfmet>0"                ; break; 
        case 1: ss_selection + " && ht>80 && pfmet>30"               ; break; 
        case 2: ss_selection + " && ht>80 && pfmet>30 && is_pp"      ; break; 
        case 3: ss_selection + " && ht>200 && pfmet>50"              ; break; 
        case 4: ss_selection + " && ht>200 && pfmet>120"             ; break; 
        case 5: ss_selection + " && ht>320 && pfmet>50"              ; break; 
        case 6: ss_selection + " && ht>320 && pfmet>120"             ; break; 
        case 7: ss_selection + " && ht>200 && pfmet>50 && nbtags>=3" ; break; 
        case 8: ss_selection + " && ht>320 && pfmet>0"               ; break; 
        default: 
            cout << "invalid signal region.  quiting" << endl;
            return;
    };
    string sel_3jets = ss_selection + " && njets==3";
    //string mc_scale  = Form("%1.4f*scale1fb*sf_trig*sf_nbtag*sf_lepeff", lumi);
    string mc_scale  = Form("%1.4f*scale1fb", lumi);
    
    // fill hists
    // mc
    for (size_t i = 1; i != samples.size(); i++)
    {
        TChain& chain = *samples[i].chain; 
        string name = samples[i].name;
        SetAliases(chain);
        //cout << "get entries mc = " << name << "\t" << chain.GetEntries(ss_selection.c_str()) << endl;

        chain.Draw(Form("min(l1_pt, %f)>>h_%s_pt1"        , pt_bins.max    , name.c_str()), Form("(%s)*%s", ss_selection.c_str(), mc_scale.c_str()), "goff");
        chain.Draw(Form("min(l2_pt, %f)>>h_%s_pt2"        , pt_bins.max    , name.c_str()), Form("(%s)*%s", ss_selection.c_str(), mc_scale.c_str()), "goff");
        chain.Draw(Form("min(l1_eta, %f)>>h_%s_eta1"      , eta_bins.max   , name.c_str()), Form("(%s)*%s", ss_selection.c_str(), mc_scale.c_str()), "goff");
        chain.Draw(Form("min(l2_eta, %f)>>h_%s_eta2"      , eta_bins.max   , name.c_str()), Form("(%s)*%s", ss_selection.c_str(), mc_scale.c_str()), "goff");
        chain.Draw(Form("min(l1_phi, %f)>>h_%s_phi1"      , phi_bins.max   , name.c_str()), Form("(%s)*%s", ss_selection.c_str(), mc_scale.c_str()), "goff");
        chain.Draw(Form("min(l2_phi, %f)>>h_%s_phi2"      , phi_bins.max   , name.c_str()), Form("(%s)*%s", ss_selection.c_str(), mc_scale.c_str()), "goff");
        chain.Draw(Form("min(l1_z0, %f)>>h_%s_z01"        , z0_bins.max    , name.c_str()), Form("(%s)*%s", ss_selection.c_str(), mc_scale.c_str()), "goff");
        chain.Draw(Form("min(l2_z0, %f)>>h_%s_z02"        , z0_bins.max    , name.c_str()), Form("(%s)*%s", ss_selection.c_str(), mc_scale.c_str()), "goff");
        chain.Draw(Form("min(deta, %f)>>h_%s_deta"        , deta_bins.max  , name.c_str()), Form("(%s)*%s", ss_selection.c_str(), mc_scale.c_str()), "goff");
        chain.Draw(Form("min(dphi, %f)>>h_%s_dphi"        , dphi_bins.max  , name.c_str()), Form("(%s)*%s", ss_selection.c_str(), mc_scale.c_str()), "goff");
        chain.Draw(Form("min(dr, %f)>>h_%s_dr"            , dr_bins.max    , name.c_str()), Form("(%s)*%s", ss_selection.c_str(), mc_scale.c_str()), "goff");
        chain.Draw(Form("min(pfmet, %f)>>h_%s_met"        , met_bins.max   , name.c_str()), Form("(%s)*%s", ss_selection.c_str(), mc_scale.c_str()), "goff");
        chain.Draw(Form("min(ht, %f)>>h_%s_ht"            , ht_bins.max    , name.c_str()), Form("(%s)*%s", ss_selection.c_str(), mc_scale.c_str()), "goff");
        chain.Draw(Form("min(nbtags, %f)>>h_%s_nbtags"    , nbtags_bins.max, name.c_str()), Form("(%s)*%s", ss_selection.c_str(), mc_scale.c_str()), "goff");
        chain.Draw(Form("min(njets, %f)>>h_%s_njets"      , njets_bins.max , name.c_str()), Form("(%s)*%s", ss_selection.c_str(), mc_scale.c_str()), "goff");
        chain.Draw(Form("min(dr_l1_bj, %f)>>h_%s_dr_l1_bj", dr_bins.max    , name.c_str()), Form("(%s)*%s", ss_selection.c_str(), mc_scale.c_str()), "goff");
        chain.Draw(Form("min(dr_l2_bj, %f)>>h_%s_dr_l2_bj", dr_bins.max    , name.c_str()), Form("(%s)*%s", ss_selection.c_str(), mc_scale.c_str()), "goff");
        chain.Draw(Form("min(dr_b1_b2, %f)>>h_%s_dr_b1_b2", dr_bins.max    , name.c_str()), Form("(%s)*%s", ss_selection.c_str(), mc_scale.c_str()), "goff");
        chain.Draw(Form("min(dr_bj_nj, %f)>>h_%s_dr_bj_nj", dr_bins.max    , name.c_str()), Form("(%s)*%s", sel_3jets.c_str(), mc_scale.c_str())   , "goff");
    }

    // data
    ss_selection.append(" && is_good_lumi");
    sel_3jets.append(" && is_good_lumi");
    TChain& chain = *samples.front().chain; 
    SetAliases(chain);
    cout << chain.GetEntries(ss_selection.c_str()) << endl;;
    chain.Draw(Form("min(l1_pt, %f)>>h_data_pt1"        , pt_bins.max    ), ss_selection.c_str(), "goff");
    chain.Draw(Form("min(l1_pt, %f)>>h_data_pt1"        , pt_bins.max    ), ss_selection.c_str(), "goff");
    chain.Draw(Form("min(l2_pt, %f)>>h_data_pt2"        , pt_bins.max    ), ss_selection.c_str(), "goff");
    chain.Draw(Form("min(l1_eta, %f)>>h_data_eta1"      , eta_bins.max   ), ss_selection.c_str(), "goff");
    chain.Draw(Form("min(l2_eta, %f)>>h_data_eta2"      , eta_bins.max   ), ss_selection.c_str(), "goff");
    chain.Draw(Form("min(l1_phi, %f)>>h_data_phi1"      , phi_bins.max   ), ss_selection.c_str(), "goff");
    chain.Draw(Form("min(l2_phi, %f)>>h_data_phi2"      , phi_bins.max   ), ss_selection.c_str(), "goff");
    chain.Draw(Form("min(l1_z0, %f)>>h_data_z01"        , z0_bins.max    ), ss_selection.c_str(), "goff");
    chain.Draw(Form("min(l2_z0, %f)>>h_data_z02"        , z0_bins.max    ), ss_selection.c_str(), "goff");
    chain.Draw(Form("min(deta, %f)>>h_data_deta"        , deta_bins.max  ), ss_selection.c_str(), "goff");
    chain.Draw(Form("min(dphi, %f)>>h_data_dphi"        , dphi_bins.max  ), ss_selection.c_str(), "goff");
    chain.Draw(Form("min(dr, %f)>>h_data_dr"            , dr_bins.max    ), ss_selection.c_str(), "goff");
    chain.Draw(Form("min(pfmet, %f)>>h_data_met"        , met_bins.max   ), ss_selection.c_str(), "goff");
    chain.Draw(Form("min(ht, %f)>>h_data_ht"            , ht_bins.max    ), ss_selection.c_str(), "goff");
    chain.Draw(Form("min(nbtags, %f)>>h_data_nbtags"    , nbtags_bins.max), ss_selection.c_str(), "goff");
    chain.Draw(Form("min(njets, %f)>>h_data_njets"      , njets_bins.max ), ss_selection.c_str(), "goff");
    chain.Draw(Form("min(dr_l1_bj, %f)>>h_data_dr_l1_bj", dr_bins.max    ), ss_selection.c_str(), "goff");
    chain.Draw(Form("min(dr_l2_bj, %f)>>h_data_dr_l2_bj", dr_bins.max    ), ss_selection.c_str(), "goff");
    chain.Draw(Form("min(dr_b1_b2, %f)>>h_data_dr_b1_b2", dr_bins.max    ), ss_selection.c_str(), "goff");
    chain.Draw(Form("min(dr_bj_nj, %f)>>h_data_dr_bj_nj", dr_bins.max    ), sel_3jets.c_str()   , "goff");

    // fakes
    chain.SetAlias("fr1", "lep1_wfr/(1.0-lep1_wfr)");
    chain.SetAlias("fr2", "lep1_wfr/(1.0-lep2_wfr)");
    string sf_selection = rt::string_replace_all(ss_selection, "is_ss", "is_sf");
    string df_selection = rt::string_replace_all(ss_selection, "is_ss", "is_df");
    string sf_sel_3jets = sf_selection + " && njets==3";
    string df_sel_3jets = df_selection + " && njets==3";
    string sf_scale     = "(is_sf ? lep1_is_fo*fr1 + lep2_is_fo*fr2 : 0.0)";
    string df_scale     = "(is_df ? fr1*fr2 : 0.0)";

    chain.Draw(Form("min(l1_pt, %f)>>h_sf_pt1"        , pt_bins.max    ), Form("(%s)*%s", sf_selection.c_str(), sf_scale.c_str()), "goff");
    chain.Draw(Form("min(l2_pt, %f)>>h_sf_pt2"        , pt_bins.max    ), Form("(%s)*%s", sf_selection.c_str(), sf_scale.c_str()), "goff");
    chain.Draw(Form("min(l1_eta, %f)>>h_sf_eta1"      , eta_bins.max   ), Form("(%s)*%s", sf_selection.c_str(), sf_scale.c_str()), "goff");
    chain.Draw(Form("min(l2_eta, %f)>>h_sf_eta2"      , eta_bins.max   ), Form("(%s)*%s", sf_selection.c_str(), sf_scale.c_str()), "goff");
    chain.Draw(Form("min(l1_phi, %f)>>h_sf_phi1"      , phi_bins.max   ), Form("(%s)*%s", sf_selection.c_str(), sf_scale.c_str()), "goff");
    chain.Draw(Form("min(l2_phi, %f)>>h_sf_phi2"      , phi_bins.max   ), Form("(%s)*%s", sf_selection.c_str(), sf_scale.c_str()), "goff");
    chain.Draw(Form("min(l1_z0, %f)>>h_sf_z01"        , z0_bins.max    ), Form("(%s)*%s", sf_selection.c_str(), sf_scale.c_str()), "goff");
    chain.Draw(Form("min(l2_z0, %f)>>h_sf_z02"        , z0_bins.max    ), Form("(%s)*%s", sf_selection.c_str(), sf_scale.c_str()), "goff");
    chain.Draw(Form("min(deta, %f)>>h_sf_deta"        , deta_bins.max  ), Form("(%s)*%s", sf_selection.c_str(), sf_scale.c_str()), "goff");
    chain.Draw(Form("min(dphi, %f)>>h_sf_dphi"        , dphi_bins.max  ), Form("(%s)*%s", sf_selection.c_str(), sf_scale.c_str()), "goff");
    chain.Draw(Form("min(dr, %f)>>h_sf_dr"            , dr_bins.max    ), Form("(%s)*%s", sf_selection.c_str(), sf_scale.c_str()), "goff");
    chain.Draw(Form("min(pfmet, %f)>>h_sf_met"        , met_bins.max   ), Form("(%s)*%s", sf_selection.c_str(), sf_scale.c_str()), "goff");
    chain.Draw(Form("min(ht, %f)>>h_sf_ht"            , ht_bins.max    ), Form("(%s)*%s", sf_selection.c_str(), sf_scale.c_str()), "goff");
    chain.Draw(Form("min(nbtags, %f)>>h_sf_nbtags"    , nbtags_bins.max), Form("(%s)*%s", sf_selection.c_str(), sf_scale.c_str()), "goff");
    chain.Draw(Form("min(njets, %f)>>h_sf_njets"      , njets_bins.max ), Form("(%s)*%s", sf_selection.c_str(), sf_scale.c_str()), "goff");
    chain.Draw(Form("min(dr_l1_bj, %f)>>h_sf_dr_l1_bj", dr_bins.max    ), Form("(%s)*%s", sf_selection.c_str(), sf_scale.c_str()), "goff");
    chain.Draw(Form("min(dr_l2_bj, %f)>>h_sf_dr_l2_bj", dr_bins.max    ), Form("(%s)*%s", sf_selection.c_str(), sf_scale.c_str()), "goff");
    chain.Draw(Form("min(dr_b1_b2, %f)>>h_sf_dr_b1_b2", dr_bins.max    ), Form("(%s)*%s", sf_selection.c_str(), sf_scale.c_str()), "goff");
    chain.Draw(Form("min(dr_bj_nj, %f)>>h_sf_dr_bj_nj", dr_bins.max    ), Form("(%s)*%s", sf_sel_3jets.c_str(), sf_scale.c_str()), "goff");

    chain.Draw(Form("min(l1_pt, %f)>>h_df_pt1"        , pt_bins.max    ), Form("(%s)*%s", df_selection.c_str(), df_scale.c_str()), "goff");
    chain.Draw(Form("min(l2_pt, %f)>>h_df_pt2"        , pt_bins.max    ), Form("(%s)*%s", df_selection.c_str(), df_scale.c_str()), "goff");
    chain.Draw(Form("min(l1_eta, %f)>>h_df_eta1"      , eta_bins.max   ), Form("(%s)*%s", df_selection.c_str(), df_scale.c_str()), "goff");
    chain.Draw(Form("min(l2_eta, %f)>>h_df_eta2"      , eta_bins.max   ), Form("(%s)*%s", df_selection.c_str(), df_scale.c_str()), "goff");
    chain.Draw(Form("min(l1_phi, %f)>>h_df_phi1"      , phi_bins.max   ), Form("(%s)*%s", df_selection.c_str(), df_scale.c_str()), "goff");
    chain.Draw(Form("min(l2_phi, %f)>>h_df_phi2"      , phi_bins.max   ), Form("(%s)*%s", df_selection.c_str(), df_scale.c_str()), "goff");
    chain.Draw(Form("min(l1_z0, %f)>>h_df_z01"        , z0_bins.max    ), Form("(%s)*%s", df_selection.c_str(), df_scale.c_str()), "goff");
    chain.Draw(Form("min(l2_z0, %f)>>h_df_z02"        , z0_bins.max    ), Form("(%s)*%s", df_selection.c_str(), df_scale.c_str()), "goff");
    chain.Draw(Form("min(deta, %f)>>h_df_deta"        , deta_bins.max  ), Form("(%s)*%s", df_selection.c_str(), df_scale.c_str()), "goff");
    chain.Draw(Form("min(dphi, %f)>>h_df_dphi"        , dphi_bins.max  ), Form("(%s)*%s", df_selection.c_str(), df_scale.c_str()), "goff");
    chain.Draw(Form("min(dr, %f)>>h_df_dr"            , dr_bins.max    ), Form("(%s)*%s", df_selection.c_str(), df_scale.c_str()), "goff");
    chain.Draw(Form("min(pfmet, %f)>>h_df_met"        , met_bins.max   ), Form("(%s)*%s", df_selection.c_str(), df_scale.c_str()), "goff");
    chain.Draw(Form("min(ht, %f)>>h_df_ht"            , ht_bins.max    ), Form("(%s)*%s", df_selection.c_str(), df_scale.c_str()), "goff");
    chain.Draw(Form("min(nbtags, %f)>>h_df_nbtags"    , nbtags_bins.max), Form("(%s)*%s", df_selection.c_str(), df_scale.c_str()), "goff");
    chain.Draw(Form("min(njets, %f)>>h_df_njets"      , njets_bins.max ), Form("(%s)*%s", df_selection.c_str(), df_scale.c_str()), "goff");
    chain.Draw(Form("min(dr_l1_bj, %f)>>h_df_dr_l1_bj", dr_bins.max    ), Form("(%s)*%s", df_selection.c_str(), df_scale.c_str()), "goff");
    chain.Draw(Form("min(dr_l2_bj, %f)>>h_df_dr_l2_bj", dr_bins.max    ), Form("(%s)*%s", df_selection.c_str(), df_scale.c_str()), "goff");
    chain.Draw(Form("min(dr_b1_b2, %f)>>h_df_dr_b1_b2", dr_bins.max    ), Form("(%s)*%s", df_selection.c_str(), df_scale.c_str()), "goff");
    chain.Draw(Form("min(dr_bj_nj, %f)>>h_df_dr_bj_nj", dr_bins.max    ), Form("(%s)*%s", df_sel_3jets.c_str(), df_scale.c_str()), "goff");

    // flips
    chain.SetAlias("fl1", "lep1_wflip/(1.0-lep1_wflip)");
    chain.SetAlias("fl2", "lep2_wflip/(1.0-lep2_wflip)");
    string flip_selection = rt::string_replace_all(ss_selection, "is_ss", "is_os");
    string flip_sel_3jets = flip_selection + " && njets==3";
    string flip_scale     = "(is_os ? fl1 + fl2 : 0.0)";

    chain.Draw(Form("min(l1_pt, %f)>>h_flip_pt1"        , pt_bins.max    ), Form("(%s)*%s", flip_selection.c_str(), flip_scale.c_str()), "goff");
    chain.Draw(Form("min(l2_pt, %f)>>h_flip_pt2"        , pt_bins.max    ), Form("(%s)*%s", flip_selection.c_str(), flip_scale.c_str()), "goff");
    chain.Draw(Form("min(l1_eta, %f)>>h_flip_eta1"      , eta_bins.max   ), Form("(%s)*%s", flip_selection.c_str(), flip_scale.c_str()), "goff");
    chain.Draw(Form("min(l2_eta, %f)>>h_flip_eta2"      , eta_bins.max   ), Form("(%s)*%s", flip_selection.c_str(), flip_scale.c_str()), "goff");
    chain.Draw(Form("min(l1_phi, %f)>>h_flip_phi1"      , phi_bins.max   ), Form("(%s)*%s", flip_selection.c_str(), flip_scale.c_str()), "goff");
    chain.Draw(Form("min(l2_phi, %f)>>h_flip_phi2"      , phi_bins.max   ), Form("(%s)*%s", flip_selection.c_str(), flip_scale.c_str()), "goff");
    chain.Draw(Form("min(l1_z0, %f)>>h_flip_z01"        , z0_bins.max    ), Form("(%s)*%s", flip_selection.c_str(), flip_scale.c_str()), "goff");
    chain.Draw(Form("min(l2_z0, %f)>>h_flip_z02"        , z0_bins.max    ), Form("(%s)*%s", flip_selection.c_str(), flip_scale.c_str()), "goff");
    chain.Draw(Form("min(deta, %f)>>h_flip_deta"        , deta_bins.max  ), Form("(%s)*%s", flip_selection.c_str(), flip_scale.c_str()), "goff");
    chain.Draw(Form("min(dphi, %f)>>h_flip_dphi"        , dphi_bins.max  ), Form("(%s)*%s", flip_selection.c_str(), flip_scale.c_str()), "goff");
    chain.Draw(Form("min(dr, %f)>>h_flip_dr"            , dr_bins.max    ), Form("(%s)*%s", flip_selection.c_str(), flip_scale.c_str()), "goff");
    chain.Draw(Form("min(pfmet, %f)>>h_flip_met"        , met_bins.max   ), Form("(%s)*%s", flip_selection.c_str(), flip_scale.c_str()), "goff");
    chain.Draw(Form("min(ht, %f)>>h_flip_ht"            , ht_bins.max    ), Form("(%s)*%s", flip_selection.c_str(), flip_scale.c_str()), "goff");
    chain.Draw(Form("min(nbtags, %f)>>h_flip_nbtags"    , nbtags_bins.max), Form("(%s)*%s", flip_selection.c_str(), flip_scale.c_str()), "goff");
    chain.Draw(Form("min(njets, %f)>>h_flip_njets"      , njets_bins.max ), Form("(%s)*%s", flip_selection.c_str(), flip_scale.c_str()), "goff");
    chain.Draw(Form("min(dr_l1_bj, %f)>>h_flip_dr_l1_bj", dr_bins.max    ), Form("(%s)*%s", flip_selection.c_str(), flip_scale.c_str()), "goff");
    chain.Draw(Form("min(dr_l2_bj, %f)>>h_flip_dr_l2_bj", dr_bins.max    ), Form("(%s)*%s", flip_selection.c_str(), flip_scale.c_str()), "goff");
    chain.Draw(Form("min(dr_b1_b2, %f)>>h_flip_dr_b1_b2", dr_bins.max    ), Form("(%s)*%s", flip_selection.c_str(), flip_scale.c_str()), "goff");
    chain.Draw(Form("min(dr_bj_nj, %f)>>h_flip_dr_bj_nj", dr_bins.max    ), Form("(%s)*%s", flip_sel_3jets.c_str(), flip_scale.c_str()), "goff");

    // subtact the SF from the DF 
    AddHist(hc["h_fake_pt1"     ], hc["h_sf_pt1"     ], hc["h_df_pt1"     ], 1.0, -1.0);
    AddHist(hc["h_fake_pt2"     ], hc["h_sf_pt2"     ], hc["h_df_pt2"     ], 1.0, -1.0);
    AddHist(hc["h_fake_eta1"    ], hc["h_sf_eta1"    ], hc["h_df_eta1"    ], 1.0, -1.0);
    AddHist(hc["h_fake_eta2"    ], hc["h_sf_eta2"    ], hc["h_df_eta2"    ], 1.0, -1.0);
    AddHist(hc["h_fake_phi1"    ], hc["h_sf_phi1"    ], hc["h_df_phi1"    ], 1.0, -1.0);
    AddHist(hc["h_fake_phi2"    ], hc["h_sf_phi2"    ], hc["h_df_phi2"    ], 1.0, -1.0);
    AddHist(hc["h_fake_z01"     ], hc["h_sf_z01"     ], hc["h_df_z01"     ], 1.0, -1.0);
    AddHist(hc["h_fake_z02"     ], hc["h_sf_z02"     ], hc["h_df_z02"     ], 1.0, -1.0);
    AddHist(hc["h_fake_deta"    ], hc["h_sf_deta"    ], hc["h_df_deta"    ], 1.0, -1.0);
    AddHist(hc["h_fake_dphi"    ], hc["h_sf_dphi"    ], hc["h_df_dphi"    ], 1.0, -1.0);
    AddHist(hc["h_fake_dr"      ], hc["h_sf_dr"      ], hc["h_df_dr"      ], 1.0, -1.0);
    AddHist(hc["h_fake_met"     ], hc["h_sf_met"     ], hc["h_df_met"     ], 1.0, -1.0);
    AddHist(hc["h_fake_ht"      ], hc["h_sf_ht"      ], hc["h_df_ht"      ], 1.0, -1.0);
    AddHist(hc["h_fake_nbtags"  ], hc["h_sf_nbtags"  ], hc["h_df_nbtags"  ], 1.0, -1.0);
    AddHist(hc["h_fake_njets"   ], hc["h_sf_njets"   ], hc["h_df_njets"   ], 1.0, -1.0);
    AddHist(hc["h_fake_dr_l1_bj"], hc["h_sf_dr_l1_bj"], hc["h_df_dr_l1_bj"], 1.0, -1.0);
    AddHist(hc["h_fake_dr_l2_bj"], hc["h_sf_dr_l2_bj"], hc["h_df_dr_l2_bj"], 1.0, -1.0);
    AddHist(hc["h_fake_dr_b1_b2"], hc["h_sf_dr_b1_b2"], hc["h_df_dr_b1_b2"], 1.0, -1.0);
    AddHist(hc["h_fake_dr_bj_nj"], hc["h_sf_dr_bj_nj"], hc["h_df_dr_bj_nj"], 1.0, -1.0);

    // add the MC hists
    for (size_t i = 0; i != samples.size(); i++)
    {
        const string& name = samples[i].name.c_str();

        hc["h_mc_pt1"     ]->Add(hc["h_mc_pt1"     ], hc[Form("h_%s_pt1"     , name.c_str())], 1.0, 1.0);
        hc["h_mc_pt2"     ]->Add(hc["h_mc_pt2"     ], hc[Form("h_%s_pt2"     , name.c_str())], 1.0, 1.0);
        hc["h_mc_eta1"    ]->Add(hc["h_mc_eta1"    ], hc[Form("h_%s_eta1"    , name.c_str())], 1.0, 1.0);
        hc["h_mc_eta2"    ]->Add(hc["h_mc_eta2"    ], hc[Form("h_%s_eta2"    , name.c_str())], 1.0, 1.0);
        hc["h_mc_phi1"    ]->Add(hc["h_mc_phi1"    ], hc[Form("h_%s_phi1"    , name.c_str())], 1.0, 1.0);
        hc["h_mc_phi2"    ]->Add(hc["h_mc_phi2"    ], hc[Form("h_%s_phi2"    , name.c_str())], 1.0, 1.0);
        hc["h_mc_z01"     ]->Add(hc["h_mc_z01"     ], hc[Form("h_%s_z01"     , name.c_str())], 1.0, 1.0);
        hc["h_mc_z02"     ]->Add(hc["h_mc_z02"     ], hc[Form("h_%s_z02"     , name.c_str())], 1.0, 1.0);
        hc["h_mc_deta"    ]->Add(hc["h_mc_deta"    ], hc[Form("h_%s_deta"    , name.c_str())], 1.0, 1.0);
        hc["h_mc_dphi"    ]->Add(hc["h_mc_dphi"    ], hc[Form("h_%s_dphi"    , name.c_str())], 1.0, 1.0);
        hc["h_mc_dr"      ]->Add(hc["h_mc_dr"      ], hc[Form("h_%s_dr"      , name.c_str())], 1.0, 1.0);
        hc["h_mc_met"     ]->Add(hc["h_mc_met"     ], hc[Form("h_%s_met"     , name.c_str())], 1.0, 1.0);
        hc["h_mc_ht"      ]->Add(hc["h_mc_ht"      ], hc[Form("h_%s_ht"      , name.c_str())], 1.0, 1.0);
        hc["h_mc_nbtags"  ]->Add(hc["h_mc_nbtags"  ], hc[Form("h_%s_nbtags"  , name.c_str())], 1.0, 1.0);
        hc["h_mc_njets"   ]->Add(hc["h_mc_njets"   ], hc[Form("h_%s_njets"   , name.c_str())], 1.0, 1.0);
        hc["h_mc_dr_l1_bj"]->Add(hc["h_mc_dr_l1_bj"], hc[Form("h_%s_dr_l1_bj", name.c_str())], 1.0, 1.0);
        hc["h_mc_dr_l2_bj"]->Add(hc["h_mc_dr_l2_bj"], hc[Form("h_%s_dr_l2_bj", name.c_str())], 1.0, 1.0);
        hc["h_mc_dr_b1_b2"]->Add(hc["h_mc_dr_b1_b2"], hc[Form("h_%s_dr_b1_b2", name.c_str())], 1.0, 1.0);
        hc["h_mc_dr_bj_nj"]->Add(hc["h_mc_dr_bj_nj"], hc[Form("h_%s_dr_bj_nj", name.c_str())], 1.0, 1.0);
    }

    // write hists 
    if (!suffix.empty())
    {
        hc.Print(Form("plots/sr%d/kin/individual", signal_region_num), suffix);
    }
    hc.Write(Form("plots/sr%d/kin/kin.root", signal_region_num));

    return;
}

void StackSSPlots(unsigned int signal_region_num = 0, const std::string& suffix = "png")
{
    rt::TH1Container hc(Form("plots/sr%d/kin/kin.root", signal_region_num));
    map<string, rt::TH1Overlay> p;
    rt::TH1Overlay::profile_marker_size_default = 10.0;

	// set style
	rt::SetTDRStyle();
	gStyle->SetTitleBorderSize(0);

    // title
	//float lumi = 3.95;
    float lumi = 5.098;
	std::string title = Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %3.3f fb^{-1}", lumi);

    Color_t data_color = kBlack;
    Color_t mc_color   = kCyan-5;
    Color_t fake_color = kRed-6;
    Color_t flip_color = kBlue-8;

    //TLatex t1(0.35, 0.83, "H_{T} > 80 GeV"); 
    //t1.SetTextSize(0.035);
    TLatex t1(0.35, 0.83, Form("SR%d", signal_region_num)); 
    t1.SetTextSize(0.035);
    //TLatex t2(0.35, 0.77, "E^{miss}_{T} > 30 GeV, N_{btags} #geq 2");
    TLatex t2(0.35, 0.77, "");
    t2.SetTextSize(0.035);

    // overlays
    p["p_pt1"] = rt::TH1Overlay(Form("%s;p^{lep1}_{T} (GeV);Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_pt1"].Add(hc["h_data_pt1"], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_pt1"].Add(hc["h_flip_pt1"], "flips", flip_color);
    p["p_pt1"].Add(hc["h_fake_pt1"], "fakes", fake_color);
    p["p_pt1"].Add(hc["h_mc_pt1"  ], "MC"   , mc_color  );
    p["p_pt1"].AddText(t1);
    p["p_pt1"].AddText(t2);

    p["p_pt2"] = rt::TH1Overlay(Form("%s;p^{lep2}_{T} (GeV);Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_pt2"].Add(hc["h_data_pt2"], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_pt2"].Add(hc["h_flip_pt2"], "flips", flip_color);
    p["p_pt2"].Add(hc["h_fake_pt2"], "fakes", fake_color);
    p["p_pt2"].Add(hc["h_mc_pt2"  ], "MC"   , mc_color  );
    p["p_pt2"].AddText(t1);
    p["p_pt2"].AddText(t2);

    p["p_eta1"] = rt::TH1Overlay(Form("%s;#eta^{lep1};Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_eta1"].Add(hc["h_data_eta1"], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_eta1"].Add(hc["h_flip_eta1"], "flips", flip_color);
    p["p_eta1"].Add(hc["h_fake_eta1"], "fakes", fake_color);
    p["p_eta1"].Add(hc["h_mc_eta1"  ], "MC"   , mc_color  );
    p["p_eta1"].SetYAxisRange(0, 4);
    p["p_eta1"].AddText(t1);
    p["p_eta1"].AddText(t2);

    p["p_eta2"] = rt::TH1Overlay(Form("%s;#eta^{lep2};Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_eta2"].Add(hc["h_data_eta2"], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_eta2"].Add(hc["h_flip_eta2"], "flips", flip_color);
    p["p_eta2"].Add(hc["h_fake_eta2"], "fakes", fake_color);
    p["p_eta2"].Add(hc["h_mc_eta2"  ], "MC"   , mc_color  );
    p["p_eta2"].SetYAxisRange(0, 4);
    p["p_eta2"].AddText(t1);
    p["p_eta2"].AddText(t2);

    p["p_phi1"] = rt::TH1Overlay(Form("%s;#phi^{lep1};Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_phi1"].Add(hc["h_data_phi1"], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_phi1"].Add(hc["h_flip_phi1"], "flips", flip_color);
    p["p_phi1"].Add(hc["h_fake_phi1"], "fakes", fake_color);
    p["p_phi1"].Add(hc["h_mc_phi1"  ], "MC"   , mc_color  );
    p["p_phi1"].SetYAxisRange(0, 4);
    p["p_phi1"].AddText(t1);
    p["p_phi1"].AddText(t2);

    p["p_phi2"] = rt::TH1Overlay(Form("%s;#phi^{lep2};Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_phi2"].Add(hc["h_data_phi2"], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_phi2"].Add(hc["h_flip_phi2"], "flips", flip_color);
    p["p_phi2"].Add(hc["h_fake_phi2"], "fakes", fake_color);
    p["p_phi2"].Add(hc["h_mc_phi2"  ], "MC"   , mc_color  );
    p["p_phi2"].SetYAxisRange(0, 4);
    p["p_phi2"].AddText(t1);
    p["p_phi2"].AddText(t2);

    p["p_z01"] = rt::TH1Overlay(Form("%s;z^{lep1}_{0};Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_z01"].Add(hc["h_data_z01"], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_z01"].Add(hc["h_flip_z01"], "flips", flip_color);
    p["p_z01"].Add(hc["h_fake_z01"], "fakes", fake_color);
    p["p_z01"].Add(hc["h_mc_z01"  ], "MC"   , mc_color  );
    p["p_z01"].SetYAxisRange(0.0, 7.0);
    p["p_z01"].AddText(t1);
    p["p_z01"].AddText(t2);

    p["p_z02"] = rt::TH1Overlay(Form("%s;z^{lep2}_{0};Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_z02"].Add(hc["h_data_z02"], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_z02"].Add(hc["h_flip_z02"], "flips", flip_color);
    p["p_z02"].Add(hc["h_fake_z02"], "fakes", fake_color);
    p["p_z02"].Add(hc["h_mc_z02"  ], "MC"   , mc_color  );
    p["p_z02"].SetYAxisRange(0.0, 7.0);
    p["p_z02"].AddText(t1);
    p["p_z02"].AddText(t2);

    p["p_deta"] = rt::TH1Overlay(Form("%s;#Delta#eta;Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_deta"].Add(hc["h_data_deta"], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_deta"].Add(hc["h_flip_deta"], "flips", flip_color);
    p["p_deta"].Add(hc["h_fake_deta"], "fakes", fake_color);
    p["p_deta"].Add(hc["h_mc_deta"  ], "MC"   , mc_color  );
    p["p_deta"].SetYAxisRange(0, 4);
    p["p_deta"].AddText(t1);
    p["p_deta"].AddText(t2);

    p["p_dphi"] = rt::TH1Overlay(Form("%s;#Delta#phi;Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_dphi"].Add(hc["h_data_dphi"], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_dphi"].Add(hc["h_flip_dphi"], "flips", flip_color);
    p["p_dphi"].Add(hc["h_fake_dphi"], "fakes", fake_color);
    p["p_dphi"].Add(hc["h_mc_dphi"  ], "MC"   , mc_color  );
    p["p_dphi"].SetYAxisRange(0, 4);
    p["p_dphi"].AddText(t1);
    p["p_dphi"].AddText(t2);

    p["p_dr"] = rt::TH1Overlay(Form("%s;#DeltaR;Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_dr"].Add(hc["h_data_dr"], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_dr"].Add(hc["h_flip_dr"], "flips", flip_color);
    p["p_dr"].Add(hc["h_fake_dr"], "fakes", fake_color);
    p["p_dr"].Add(hc["h_mc_dr"  ], "MC"   , mc_color  );
    p["p_dr"].SetYAxisRange(0, 4);
    p["p_dr"].AddText(t1);
    p["p_dr"].AddText(t2);

    p["p_met"] = rt::TH1Overlay(Form("%s;E^{miss}_{T} (GeV);Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_met"].Add(hc["h_data_met"], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_met"].Add(hc["h_flip_met"], "flips", flip_color);
    p["p_met"].Add(hc["h_fake_met"], "fakes", fake_color);
    p["p_met"].Add(hc["h_mc_met"  ], "MC"   , mc_color  );
    p["p_met"].AddText(t1);
    p["p_met"].AddText(t2);

    p["p_ht"] = rt::TH1Overlay(Form("%s;H_{T} (GeV);Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_ht"].Add(hc["h_data_ht"], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_ht"].Add(hc["h_flip_ht"], "flips", flip_color);
    p["p_ht"].Add(hc["h_fake_ht"], "fakes", fake_color);
    p["p_ht"].Add(hc["h_mc_ht"  ], "MC"   , mc_color  );
    p["p_ht"].AddText(t1);
    p["p_ht"].AddText(t2);

    p["p_dr_b1_b2"] = rt::TH1Overlay(Form("%s;#DeltaR(bjet1, bjet2);Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_dr_b1_b2"].Add(hc["h_data_dr_b1_b2"], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_dr_b1_b2"].Add(hc["h_flip_dr_b1_b2"], "flips", flip_color);
    p["p_dr_b1_b2"].Add(hc["h_fake_dr_b1_b2"], "fakes", fake_color);
    p["p_dr_b1_b2"].Add(hc["h_mc_dr_b1_b2"  ], "MC"   , mc_color  );
    p["p_dr_b1_b2"].AddText(t1);
    p["p_dr_b1_b2"].AddText(t2);

    TLatex t3(0.35, 0.71, "N_{jets} = 3");
    t3.SetTextSize(0.035);
    p["p_dr_bj_nj"] = rt::TH1Overlay(Form("%s;#DeltaR(bjet, nearest nontagged jet);Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_dr_bj_nj"].Add(hc["h_data_dr_bj_nj"], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_dr_bj_nj"].Add(hc["h_flip_dr_bj_nj"], "flips", flip_color);
    p["p_dr_bj_nj"].Add(hc["h_fake_dr_bj_nj"], "fakes", fake_color);
    p["p_dr_bj_nj"].Add(hc["h_mc_dr_bj_nj"  ], "MC"   , mc_color  );
    p["p_dr_bj_nj"].AddText(t1);
    p["p_dr_bj_nj"].AddText(t2);
    p["p_dr_bj_nj"].AddText(t3);

    p["p_dr_l1_bj"] = rt::TH1Overlay(Form("%s;#DeltaR(lepton1, nearest bjet);Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_dr_l1_bj"].Add(hc["h_data_dr_l1_bj"], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_dr_l1_bj"].Add(hc["h_flip_dr_l1_bj"], "flips", flip_color);
    p["p_dr_l1_bj"].Add(hc["h_fake_dr_l1_bj"], "fakes", fake_color);
    p["p_dr_l1_bj"].Add(hc["h_mc_dr_l1_bj"  ], "MC"   , mc_color  );
    p["p_dr_l1_bj"].AddText(t1);
    p["p_dr_l1_bj"].AddText(t2);

    p["p_dr_l2_bj"] = rt::TH1Overlay(Form("%s;#DeltaR(lepton2, nearest bjet);Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_dr_l2_bj"].Add(hc["h_data_dr_l2_bj"], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_dr_l2_bj"].Add(hc["h_flip_dr_l2_bj"], "flips", flip_color);
    p["p_dr_l2_bj"].Add(hc["h_fake_dr_l2_bj"], "fakes", fake_color);
    p["p_dr_l2_bj"].Add(hc["h_mc_dr_l2_bj"  ], "MC"   , mc_color  );
    p["p_dr_l2_bj"].AddText(t1);
    p["p_dr_l2_bj"].AddText(t2);

    t1.SetX(0.65); t1.SetY(0.6);
    t2.SetX(0.65); t2.SetY(0.54);
    p["p_nbtags"] = rt::TH1Overlay(Form("%s;# btags;Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_nbtags"].Add(hc["h_data_nbtags"], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_nbtags"].Add(hc["h_flip_nbtags"], "flips", flip_color);
    p["p_nbtags"].Add(hc["h_fake_nbtags"], "fakes", fake_color);
    p["p_nbtags"].Add(hc["h_mc_nbtags"  ], "MC"   , mc_color  );
    p["p_nbtags"].AddText(t1);
    p["p_nbtags"].AddText(t2);

    t1.SetX(0.65); t1.SetY(0.6);
    t2.SetX(0.65); t2.SetY(0.54);
    p["p_njets"] = rt::TH1Overlay(Form("%s;# jets;Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_njets"].Add(hc["h_data_njets"], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_njets"].Add(hc["h_flip_njets"], "flips", flip_color);
    p["p_njets"].Add(hc["h_fake_njets"], "fakes", fake_color);
    p["p_njets"].Add(hc["h_mc_njets"  ], "MC"   , mc_color  );
    p["p_njets"].AddText(t1);
    p["p_njets"].AddText(t2);

    // write
    rt::Print(p, Form("plots/sr%d/kin", signal_region_num), suffix);
}
