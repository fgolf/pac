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
#include "SignalRegion.h"

using namespace std;

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
    sample_t(const string& n, const string& t) : name(n), title(t) {}
    string name;
    string title;
};

TH1F* GetTotalPredHist(TH1* h_fake, TH1* h_flip, TH1* h_mc)
{
    string hist_name = rt::string_replace_all(h_fake->GetName(), "_fake", "_pred");
    TH1F* h_pred = dynamic_cast<TH1F*>(h_fake->Clone(hist_name.c_str()));
    h_pred->Add(h_flip);
    h_pred->Add(h_mc);
    h_pred->SetLineColor(kWhite);
    h_pred->SetFillColor(kBlack);
    h_pred->SetFillStyle(3004);
    h_pred->SetDrawOption("hist E2");
    return h_pred;
}

void OverlaySSPlots(float lumi = 1.0, unsigned int signal_region_num = 0, const std::string& path = "", const std::string& suffix = "png")
{
    ss::SignalRegionInfo sr = ss::GetSignalRegionInfo(signal_region_num);

    rt::TH1Container hc_data(Form("plots/%s/%s/data.root", path.c_str(), sr.name.c_str()));
    rt::TH1Container hc_mc;
    hc_mc += rt::TH1Container(Form("plots/%s/%s/wz.root" , path.c_str(), sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/zz.root" , path.c_str(), sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/ttw.root", path.c_str(), sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/ttz.root", path.c_str(), sr.name.c_str()));
    
    rt::mkdir(Form("plots/%s/%s/kin/", path.c_str(), sr.name.c_str()), true);

	// set style
	//rt::SetTDRStyle();
	//gStyle->SetTitleBorderSize(0);
	//gStyle->SetHistFillColor(kBlack);

    // title
	std::string title = Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %3.3f fb^{-1}", lumi);

    Color_t data_color = kBlack;
    Color_t mc_color   = kCyan-5;
    Color_t fake_color = kRed-6;
    Color_t flip_color = kBlue-8;

    //TLatex t1(0.35, 0.83, "H_{T} > 80 GeV"); 
    //t1.SetTextSize(0.035);
    //TLatex t1(0.35, 0.83, Form("%s: %s", sr.name.c_str(), sr.title.c_str())); 
    TLatex t1(0.20, 0.83, Form("%s: %s", sr.name.c_str(), sr.title.c_str())); 
    t1.SetTextSize(0.035);

    // overlays
    map<string, rt::TH1Overlay> p;
    rt::TH1Overlay::profile_marker_size_default = 10.0;

    TCanvas c1("c1", "c1");
    p["p_pt1"] = rt::TH1Overlay(Form("%s;p^{lep1}_{T} (GeV);Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_pt1"].Add(hc_data["h_pt1_ss"  ], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_pt1"].Add(hc_data["h_pt1_os"  ], "flips", flip_color);
    p["p_pt1"].Add(hc_data["h_pt1_fake"], "fakes", fake_color);
    p["p_pt1"].Add(hc_mc  ["h_pt1_ss"  ], "MC"   , mc_color  );
    p["p_pt1"].AddText(t1);
    p["p_pt1"].Draw();
    TH1F* h_pred = GetTotalPredHist(hc_data["h_pt1_fake"], hc_data["h_pt1_os"], hc_mc["h_pt1_ss"]);
    h_pred->SetStats(false);
    h_pred->Draw("same E2");
    c1.Print(Form("plots/%s/%s/kin/%s.%s", path.c_str(), sr.name.c_str(), "p_pt1", suffix.c_str()));
    delete h_pred;


    p["p_pt2"] = rt::TH1Overlay(Form("%s;p^{lep2}_{T} (GeV);Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_pt2"].Add(hc_data["h_pt2_ss"  ], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_pt2"].Add(hc_data["h_pt2_os"  ], "flips", flip_color);
    p["p_pt2"].Add(hc_data["h_pt2_fake"], "fakes", fake_color);
    p["p_pt2"].Add(hc_mc  ["h_pt2_ss"  ], "MC"   , mc_color);
    p["p_pt2"].AddText(t1);
    p["p_pt2"].Draw();
    h_pred = GetTotalPredHist(hc_data["h_pt2_fake"], hc_data["h_pt2_os"], hc_mc["h_pt2_ss"]);
    h_pred->SetStats(false);
    h_pred->Draw("same E2");
    c1.Print(Form("plots/%s/%s/kin/%s.%s", path.c_str(), sr.name.c_str(), "p_pt2", suffix.c_str()));
    delete h_pred;

    p["p_met"] = rt::TH1Overlay(Form("%s;E^{miss}_{T} (GeV);Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_met"].Add(hc_data["h_met_ss"  ], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_met"].Add(hc_data["h_met_os"  ], "flips", flip_color);
    p["p_met"].Add(hc_data["h_met_fake"], "fakes", fake_color);
    p["p_met"].Add(hc_mc  ["h_met_ss"  ], "MC"   , mc_color);
    p["p_met"].AddText(t1);
    p["p_met"].Draw();
    h_pred = GetTotalPredHist(hc_data["h_met_fake"], hc_data["h_met_os"], hc_mc["h_met_ss"]);
    h_pred->SetStats(false);
    h_pred->Draw("same E2");
    c1.Print(Form("plots/%s/%s/kin/%s.%s", path.c_str(), sr.name.c_str(), "p_met", suffix.c_str()));
    delete h_pred;

    p["p_ht"] = rt::TH1Overlay(Form("%s;H_{T} (GeV);Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_ht"].Add(hc_data["h_ht_ss"  ], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_ht"].Add(hc_data["h_ht_os"  ], "flips", flip_color);
    p["p_ht"].Add(hc_data["h_ht_fake"], "fakes", fake_color);
    p["p_ht"].Add(hc_mc  ["h_ht_ss"  ], "MC"   , mc_color);
    p["p_ht"].AddText(t1);
    p["p_ht"].Draw();
    h_pred = GetTotalPredHist(hc_data["h_ht_fake"], hc_data["h_ht_os"], hc_mc["h_ht_ss"]);
    h_pred->SetStats(false);
    h_pred->Draw("same E2");
    c1.Print(Form("plots/%s/%s/kin/%s.%s", path.c_str(), sr.name.c_str(), "p_ht", suffix.c_str()));
    delete h_pred;

    t1.SetX(0.65); t1.SetY(0.6);
    p["p_nbtags"] = rt::TH1Overlay(Form("%s;# btags;Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_nbtags"].Add(hc_data["h_nbtags_ss"  ], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_nbtags"].Add(hc_data["h_nbtags_os"  ], "flips", flip_color);
    p["p_nbtags"].Add(hc_data["h_nbtags_fake"], "fakes", fake_color);
    p["p_nbtags"].Add(hc_mc  ["h_nbtags_ss"  ], "MC"   , mc_color);
    p["p_nbtags"].AddText(t1);
    p["p_nbtags"].Draw();
    h_pred = GetTotalPredHist(hc_data["h_nbtags_fake"], hc_data["h_nbtags_os"], hc_mc["h_nbtags_ss"]);
    h_pred->SetStats(false);
    h_pred->Draw("same E2");
    c1.Print(Form("plots/%s/%s/kin/%s.%s", path.c_str(), sr.name.c_str(), "p_nbtags", suffix.c_str()));
    delete h_pred;

    t1.SetX(0.65); t1.SetY(0.6);
    p["p_njets"] = rt::TH1Overlay(Form("%s;# jets;Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_njets"].Add(hc_data["h_njets_ss"  ], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_njets"].Add(hc_data["h_njets_os"  ], "flips", flip_color);
    p["p_njets"].Add(hc_data["h_njets_fake"], "fakes", fake_color);
    p["p_njets"].Add(hc_mc  ["h_njets_ss"  ], "MC"   , mc_color);
    p["p_njets"].AddText(t1);
    p["p_njets"].Draw();
    h_pred = GetTotalPredHist(hc_data["h_njets_fake"], hc_data["h_njets_os"], hc_mc["h_njets_ss"]);
    h_pred->SetStats(false);
    h_pred->Draw("same E2");
    c1.Print(Form("plots/%s/%s/kin/%s.%s", path.c_str(), sr.name.c_str(), "p_njets", suffix.c_str()));
    delete h_pred;

    t1.SetX(0.65); t1.SetY(0.6);
    p["p_lepdphi"] = rt::TH1Overlay(Form("%s;#Delta#Phi(lep1, lep2);Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_lepdphi"].Add(hc_data["h_lepdphi_ss"  ], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_lepdphi"].Add(hc_data["h_lepdphi_os"  ], "flips", flip_color);
    p["p_lepdphi"].Add(hc_data["h_lepdphi_fake"], "fakes", fake_color);
    p["p_lepdphi"].Add(hc_mc  ["h_lepdphi_ss"  ], "MC"   , mc_color);
    p["p_lepdphi"].AddText(t1);
    p["p_lepdphi"].Draw();
    h_pred = GetTotalPredHist(hc_data["h_lepdphi_fake"], hc_data["h_lepdphi_os"], hc_mc["h_lepdphi_ss"]);
    h_pred->SetStats(false);
    h_pred->Draw("same E2");
    c1.Print(Form("plots/%s/%s/kin/%s.%s", path.c_str(), sr.name.c_str(), "p_lepdphi", suffix.c_str()));
    delete h_pred;

    t1.SetX(0.65); t1.SetY(0.6);
    p["p_lepdeta"] = rt::TH1Overlay(Form("%s;#Delta#eta(lep1, lep2);Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_lepdeta"].Add(hc_data["h_lepdeta_ss"  ], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_lepdeta"].Add(hc_data["h_lepdeta_os"  ], "flips", flip_color);
    p["p_lepdeta"].Add(hc_data["h_lepdeta_fake"], "fakes", fake_color);
    p["p_lepdeta"].Add(hc_mc  ["h_lepdeta_ss"  ], "MC"   , mc_color);
    p["p_lepdeta"].AddText(t1);
    p["p_lepdeta"].Draw();
    h_pred = GetTotalPredHist(hc_data["h_lepdeta_fake"], hc_data["h_lepdeta_os"], hc_mc["h_lepdeta_ss"]);
    h_pred->SetStats(false);
    h_pred->Draw("same E2");
    c1.Print(Form("plots/%s/%s/kin/%s.%s", path.c_str(), sr.name.c_str(), "p_lepdeta", suffix.c_str()));
    delete h_pred;

    t1.SetX(0.65); t1.SetY(0.6);
    p["p_lepdr"] = rt::TH1Overlay(Form("%s;#DeltaR(lep1, lep2);Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_lepdr"].Add(hc_data["h_lepdr_ss"  ], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_lepdr"].Add(hc_data["h_lepdr_os"  ], "flips", flip_color);
    p["p_lepdr"].Add(hc_data["h_lepdr_fake"], "fakes", fake_color);
    p["p_lepdr"].Add(hc_mc  ["h_lepdr_ss"  ], "MC"   , mc_color);
    p["p_lepdr"].AddText(t1);
    p["p_lepdr"].Draw();
    h_pred = GetTotalPredHist(hc_data["h_lepdr_fake"], hc_data["h_lepdr_os"], hc_mc["h_lepdr_ss"]);
    h_pred->SetStats(false);
    h_pred->Draw("same E2");
    c1.Print(Form("plots/%s/%s/kin/%s.%s", path.c_str(), sr.name.c_str(), "p_lepdr", suffix.c_str()));
    delete h_pred;

    t1.SetX(0.65); t1.SetY(0.6);
    p["p_drlepb"] = rt::TH1Overlay(Form("%s;#DeltaR(lep, btag);Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_drlepb"].Add(hc_data["h_drlepb_ss"  ], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_drlepb"].Add(hc_data["h_drlepb_os"  ], "flips", flip_color);
    p["p_drlepb"].Add(hc_data["h_drlepb_fake"], "fakes", fake_color);
    p["p_drlepb"].Add(hc_mc  ["h_drlepb_ss"  ], "MC"   , mc_color);
    p["p_drlepb"].AddText(t1);
    p["p_drlepb"].Draw();
    h_pred = GetTotalPredHist(hc_data["h_drlepb_fake"], hc_data["h_drlepb_os"], hc_mc["h_drlepb_ss"]);
    h_pred->SetStats(false);
    h_pred->Draw("same E2");
    c1.Print(Form("plots/%s/%s/kin/%s.%s", path.c_str(), sr.name.c_str(), "p_drlepb", suffix.c_str()));
    delete h_pred;

    t1.SetX(0.65); t1.SetY(0.6);
    p["p_btagdr"] = rt::TH1Overlay(Form("%s;#DeltaR(btag1, btag2);Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_btagdr"].Add(hc_data["h_btagdr_ss"  ], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_btagdr"].Add(hc_data["h_btagdr_os"  ], "flips", flip_color);
    p["p_btagdr"].Add(hc_data["h_btagdr_fake"], "fakes", fake_color);
    p["p_btagdr"].Add(hc_mc  ["h_btagdr_ss"  ], "MC"   , mc_color);
    p["p_btagdr"].AddText(t1);
    p["p_btagdr"].Draw();
    h_pred = GetTotalPredHist(hc_data["h_btagdr_fake"], hc_data["h_btagdr_os"], hc_mc["h_btagdr_ss"]);
    h_pred->SetStats(false);
    h_pred->Draw("same E2");
    c1.Print(Form("plots/%s/%s/kin/%s.%s", path.c_str(), sr.name.c_str(), "p_btagdr", suffix.c_str()));
    delete h_pred;

    t1.SetX(0.65); t1.SetY(0.6);
    p["p_drjetb"] = rt::TH1Overlay(Form("%s;#DeltaR(btag, jet);Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_drjetb"].Add(hc_data["h_drjetb_ss"  ], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_drjetb"].Add(hc_data["h_drjetb_os"  ], "flips", flip_color);
    p["p_drjetb"].Add(hc_data["h_drjetb_fake"], "fakes", fake_color);
    p["p_drjetb"].Add(hc_mc  ["h_drjetb_ss"  ], "MC"   , mc_color);
    p["p_drjetb"].AddText(t1);
    p["p_drjetb"].Draw();
    h_pred = GetTotalPredHist(hc_data["h_drjetb_fake"], hc_data["h_drjetb_os"], hc_mc["h_drjetb_ss"]);
    h_pred->SetStats(false);
    h_pred->Draw("same E2");
    c1.Print(Form("plots/%s/%s/kin/%s.%s", path.c_str(), sr.name.c_str(), "p_drjetb", suffix.c_str()));
    delete h_pred;

    t1.SetX(0.65); t1.SetY(0.6);
    p["p_ptjetlep"] = rt::TH1Overlay(Form("%s;jet p_{T} / lep p_{T} - 1;Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_ptjetlep"].Add(hc_data["h_ptjetlep_ss"  ], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_ptjetlep"].Add(hc_data["h_ptjetlep_os"  ], "flips", flip_color);
    p["p_ptjetlep"].Add(hc_data["h_ptjetlep_fake"], "fakes", fake_color);
    p["p_ptjetlep"].Add(hc_mc  ["h_ptjetlep_ss"  ], "MC"   , mc_color);
    p["p_ptjetlep"].AddText(t1);
    p["p_ptjetlep"].Draw();
    h_pred = GetTotalPredHist(hc_data["h_ptjetlep_fake"], hc_data["h_ptjetlep_os"], hc_mc["h_ptjetlep_ss"]);
    h_pred->SetStats(false);
    h_pred->Draw("same E2");
    c1.Print(Form("plots/%s/%s/kin/%s.%s", path.c_str(), sr.name.c_str(), "p_ptjetlep", suffix.c_str()));
    delete h_pred;

    // write
//    rt::Print(p, Form("plots/%s/%s/kin", path.c_str(), sr.name.c_str()), suffix);
}
