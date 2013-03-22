#include "rt/RootTools.h"
#include "CTable.h"
#include <iostream> 

using namespace std;
	
const float lumi = 19.5;

void OverlayElectronEffPlots(const bool tex = false, const std::string& suffix = "png")
{
	rt::TH1Container hc_dy("plots/mceff/dy/plots_large.root");
	rt::TH1Container hc_tt("plots/mceff/ttjets/plots_large.root");
    std::string path = "plots/mceff/overlay";

    rt::TH1Container hc;

	std::map<std::string, rt::TH1Overlay> p;

	// set style
	rt::SetTDRStyle();
	gStyle->SetTitleBorderSize(0);
    hc.SetMarkerSize(1.8);

    // difference
    hc.Add(rt::SubtractHists(hc_dy["h_eff_el_pt1_vs_pt" ], hc_tt["h_eff_el_pt1_vs_pt" ], "h_eff_el_diff_pt1_vs_pt" , "#varepsilon_{DY} - #varepsilon_{t#bar{t}} (higher p_{T} electron);p_{T} (GeV)"));
    hc.Add(rt::SubtractHists(hc_dy["h_eff_el_pt2_vs_pt" ], hc_tt["h_eff_el_pt2_vs_pt" ], "h_eff_el_diff_pt2_vs_pt" , "#varepsilon_{DY} - #varepsilon_{t#bar{t}} (lower p_{T} electron);p_{T} (GeV)" ));
    hc.Add(rt::SubtractHists(hc_dy["h_eff_el_vs_pt"     ], hc_tt["h_eff_el_vs_pt"     ], "h_eff_el_diff_vs_pt"     , "#varepsilon_{DY} - #varepsilon_{t#bar{t}} (electron);p_{T} (GeV)"             ));
    hc.Add(rt::SubtractHists(hc_dy["h_eff_el_pt1_vs_eta"], hc_tt["h_eff_el_pt1_vs_eta"], "h_eff_el_diff_pt1_vs_eta", "#varepsilon_{DY} - #varepsilon_{t#bar{t}} (higher p_{T} electron);|#eta|"));
    hc.Add(rt::SubtractHists(hc_dy["h_eff_el_pt2_vs_eta"], hc_tt["h_eff_el_pt2_vs_eta"], "h_eff_el_diff_pt2_vs_eta", "#varepsilon_{DY} - #varepsilon_{t#bar{t}} (lower p_{T} electron);|#eta|" ));
    hc.Add(rt::SubtractHists(hc_dy["h_eff_el_vs_eta"    ], hc_tt["h_eff_el_vs_eta"    ], "h_eff_el_diff_vs_eta"    , "#varepsilon_{DY} - #varepsilon_{t#bar{t}} (electron);|#eta|"             ));
    hc.Add(rt::SubtractHists(hc_dy["h_eff_el"           ], hc_tt["h_eff_el"           ], "h_eff_el"                , "#varepsilon_{DY} - #varepsilon_{t#bar{t}} (electron);|#eta|;p_{T} (GeV)" ));

    // overlay

	std::string title = Form("CMS Simulation, #sqrt{s} = 8 TeV, L_{int} = %3.1f fb^{-1}", lumi);

    float max = 1.1;
    float min = 0.0;

    Color_t cdy   = kRed;
    Color_t ctt   = kBlack;

    string dy_title = "DY #rightarrow l^{+}l^{-}";
    string tt_title = "t#bar{t}";

    Style_t sdy = 20;
    Style_t stt = 22;

    // el eff pt1 vs pt 
    p["p_eff_el_pt1_vs_pt"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_el_pt1_vs_pt"].Add(hc_dy["h_eff_el_pt1_vs_pt"], dy_title, cdy, 2, sdy);
    p["p_eff_el_pt1_vs_pt"].Add(hc_tt["h_eff_el_pt1_vs_pt"], tt_title, ctt, 2, stt);
    p["p_eff_el_pt1_vs_pt"].SetYAxisRange(min, max);
    p["p_eff_el_pt1_vs_pt"].SetLegendOption("p");
    p["p_eff_el_pt1_vs_pt"].SetLegendTextSize(0.042);
    p["p_eff_el_pt1_vs_pt"].AddText("Electron", 0.25, 0.235);

    // el eff pt2 vs pt 
    p["p_eff_el_pt2_vs_pt"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_el_pt2_vs_pt"].Add(hc_dy["h_eff_el_pt2_vs_pt"], dy_title, cdy, 2, sdy);
    p["p_eff_el_pt2_vs_pt"].Add(hc_tt["h_eff_el_pt2_vs_pt"], tt_title, ctt, 2, stt);
    p["p_eff_el_pt2_vs_pt"].SetYAxisRange(min, max);
    p["p_eff_el_pt2_vs_pt"].SetLegendOption("p");
    p["p_eff_el_pt2_vs_pt"].SetLegendTextSize(0.042);
    p["p_eff_el_pt2_vs_pt"].AddText("Electron", 0.25, 0.235);

    // el eff vs pt 
    p["p_eff_el_vs_pt"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_el_vs_pt"].Add(hc_dy["h_eff_el_vs_pt"], dy_title, cdy, 2, sdy);
    p["p_eff_el_vs_pt"].Add(hc_tt["h_eff_el_vs_pt"], tt_title, ctt, 2, stt);
    p["p_eff_el_vs_pt"].SetYAxisRange(min, max);
    p["p_eff_el_vs_pt"].SetLegendOption("p");
    p["p_eff_el_vs_pt"].SetLegendTextSize(0.042);
    p["p_eff_el_vs_pt"].AddText("Electron", 0.25, 0.235);

    // el eff pt1 vs pt 
    p["p_eff_el_pt1_vs_eta"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_el_pt1_vs_eta"].Add(hc_dy["h_eff_el_pt1_vs_eta"], dy_title, cdy, 2, sdy);
    p["p_eff_el_pt1_vs_eta"].Add(hc_tt["h_eff_el_pt1_vs_eta"], tt_title, ctt, 2, stt);
    p["p_eff_el_pt1_vs_eta"].SetYAxisRange(min, max);
    p["p_eff_el_pt1_vs_eta"].SetLegendOption("p");
    p["p_eff_el_pt1_vs_eta"].SetLegendTextSize(0.042);
    p["p_eff_el_pt1_vs_eta"].AddText("Electron", 0.25, 0.235);

    // el eff pt2 vs eta 
    p["p_eff_el_pt2_vs_eta"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_el_pt2_vs_eta"].Add(hc_dy["h_eff_el_pt2_vs_eta"], dy_title, cdy, 2, sdy);
    p["p_eff_el_pt2_vs_eta"].Add(hc_tt["h_eff_el_pt2_vs_eta"], tt_title, ctt, 2, stt);
    p["p_eff_el_pt2_vs_eta"].SetYAxisRange(min, max);
    p["p_eff_el_pt2_vs_eta"].SetLegendOption("p");
    p["p_eff_el_pt2_vs_eta"].SetLegendTextSize(0.042);
    p["p_eff_el_pt2_vs_eta"].AddText("Electron", 0.25, 0.235);

    // el eff vs eta 
    p["p_eff_el_vs_eta"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_el_vs_eta"].Add(hc_dy["h_eff_el_vs_eta"], dy_title, cdy, 2, sdy);
    p["p_eff_el_vs_eta"].Add(hc_tt["h_eff_el_vs_eta"], tt_title, ctt, 2, stt);
    p["p_eff_el_vs_eta"].SetYAxisRange(min, max);
    p["p_eff_el_vs_eta"].SetLegendOption("p");
    p["p_eff_el_vs_eta"].SetLegendTextSize(0.042);
    p["p_eff_el_vs_eta"].AddText("Electron", 0.25, 0.235);

    // table
    CTable t = rt::CreateTableFromHist(hc["h_eff_el"],"eff DY - eff ttbar", "$\\eta$", "$p_{T}$", "", "GeV", "1.3", "1.2", "1.0");                                                                         
    if (tex)
    {
        t.printTex();
    }
    else
    {
        t.print();
    }

    cout << endl;

    // print
    if (suffix=="all")
    {
        hc.Print(path, "png");
        hc.Print(path, "pdf");
        hc.Print(path, "eps");
        rt::Print(p, path, "png");
        rt::Print(p, path, "pdf");
        rt::Print(p, path, "eps");
    }
    else
    {
        hc.Print(path, suffix);
        rt::Print(p, path, suffix);
    }
}

void OverlayMuonEffPlots(const bool tex = false, const std::string& suffix = "png")
{
	rt::TH1Container hc_dy("plots/mceff/dy/plots_large.root");
	rt::TH1Container hc_tt("plots/mceff/ttjets/plots_large.root");
    std::string path = "plots/mceff/overlay";

    rt::TH1Container hc;

	std::map<std::string, rt::TH1Overlay> p;

	// set style
	rt::SetTDRStyle();
	gStyle->SetTitleBorderSize(0);
    hc.SetMarkerSize(1.8);

    // difference
    hc.Add(rt::SubtractHists(hc_dy["h_eff_mu_pt1_vs_pt" ], hc_tt["h_eff_mu_pt1_vs_pt" ], "h_eff_mu_diff_pt1_vs_pt" , "#varepsilon_{DY} - #varepsilon_{t#bar{t}} (higher p_{T} #mu);p_{T} (GeV)"));
    hc.Add(rt::SubtractHists(hc_dy["h_eff_mu_pt2_vs_pt" ], hc_tt["h_eff_mu_pt2_vs_pt" ], "h_eff_mu_diff_pt2_vs_pt" , "#varepsilon_{DY} - #varepsilon_{t#bar{t}} (lower p_{T} #mu);p_{T} (GeV)" ));
    hc.Add(rt::SubtractHists(hc_dy["h_eff_mu_vs_pt"     ], hc_tt["h_eff_mu_vs_pt"     ], "h_eff_mu_diff_vs_pt"     , "#varepsilon_{DY} - #varepsilon_{t#bar{t}} (#mu);p_{T} (GeV)"             ));
    hc.Add(rt::SubtractHists(hc_dy["h_eff_mu_pt1_vs_eta"], hc_tt["h_eff_mu_pt1_vs_eta"], "h_eff_mu_diff_pt1_vs_eta", "#varepsilon_{DY} - #varepsilon_{t#bar{t}} (higher p_{T} #mu);|#eta|"));
    hc.Add(rt::SubtractHists(hc_dy["h_eff_mu_pt2_vs_eta"], hc_tt["h_eff_mu_pt2_vs_eta"], "h_eff_mu_diff_pt2_vs_eta", "#varepsilon_{DY} - #varepsilon_{t#bar{t}} (lower p_{T} #mu);|#eta|" ));
    hc.Add(rt::SubtractHists(hc_dy["h_eff_mu_vs_eta"    ], hc_tt["h_eff_mu_vs_eta"    ], "h_eff_mu_diff_vs_eta"    , "#varepsilon_{DY} - #varepsilon_{t#bar{t}} (#mu);|#eta|"             ));
    hc.Add(rt::SubtractHists(hc_dy["h_eff_mu"           ], hc_tt["h_eff_mu"           ], "h_eff_mu"                , "#varepsilon_{DY} - #varepsilon_{t#bar{t}} (#mu);|#eta|;p_{T} (GeV)" ));

    // overlay

	std::string title = Form("CMS Simulation, #sqrt{s} = 8 TeV, L_{int} = %3.1f fb^{-1}", lumi);

    float max = 1.1;
    float min = 0.0;

    Color_t cdy   = kRed;
    Color_t ctt   = kBlack;

    string dy_title = "DY #rightarrow l^{+}l^{-}";
    string tt_title = "t#bar{t}";

    Style_t sdy = 20;
    Style_t stt = 22;

    // mu eff pt1 vs pt 
    p["p_eff_mu_pt1_vs_pt"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_mu_pt1_vs_pt"].Add(hc_dy["h_eff_mu_pt1_vs_pt"], dy_title, cdy, 2, sdy);
    p["p_eff_mu_pt1_vs_pt"].Add(hc_tt["h_eff_mu_pt1_vs_pt"], tt_title, ctt, 2, stt);
    p["p_eff_mu_pt1_vs_pt"].SetYAxisRange(min, max);
    p["p_eff_mu_pt1_vs_pt"].SetLegendOption("p");
    p["p_eff_mu_pt1_vs_pt"].SetLegendTextSize(0.042);
    p["p_eff_mu_pt1_vs_pt"].AddText("Muon", 0.25, 0.235);

    // mu eff pt2 vs pt 
    p["p_eff_mu_pt2_vs_pt"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_mu_pt2_vs_pt"].Add(hc_dy["h_eff_mu_pt2_vs_pt"], dy_title, cdy, 2, sdy);
    p["p_eff_mu_pt2_vs_pt"].Add(hc_tt["h_eff_mu_pt2_vs_pt"], tt_title, ctt, 2, stt);
    p["p_eff_mu_pt2_vs_pt"].SetYAxisRange(min, max);
    p["p_eff_mu_pt2_vs_pt"].SetLegendOption("p");
    p["p_eff_mu_pt2_vs_pt"].SetLegendTextSize(0.042);
    p["p_eff_mu_pt2_vs_pt"].AddText("Muon", 0.25, 0.235);

    // mu eff vs pt 
    p["p_eff_mu_vs_pt"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_mu_vs_pt"].Add(hc_dy["h_eff_mu_vs_pt"], dy_title, cdy, 2, sdy);
    p["p_eff_mu_vs_pt"].Add(hc_tt["h_eff_mu_vs_pt"], tt_title, ctt, 2, stt);
    p["p_eff_mu_vs_pt"].SetYAxisRange(min, max);
    p["p_eff_mu_vs_pt"].SetLegendOption("p");
    p["p_eff_mu_vs_pt"].SetLegendTextSize(0.042);
    p["p_eff_mu_vs_pt"].AddText("Muon", 0.25, 0.235);

    // mu eff pt1 vs pt 
    p["p_eff_mu_pt1_vs_eta"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_mu_pt1_vs_eta"].Add(hc_dy["h_eff_mu_pt1_vs_eta"], dy_title, cdy, 2, sdy);
    p["p_eff_mu_pt1_vs_eta"].Add(hc_tt["h_eff_mu_pt1_vs_eta"], tt_title, ctt, 2, stt);
    p["p_eff_mu_pt1_vs_eta"].SetYAxisRange(min, max);
    p["p_eff_mu_pt1_vs_eta"].SetLegendOption("p");
    p["p_eff_mu_pt1_vs_eta"].SetLegendTextSize(0.042);
    p["p_eff_mu_pt1_vs_eta"].AddText("Muon", 0.25, 0.235);

    // mu eff pt2 vs eta 
    p["p_eff_mu_pt2_vs_eta"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_mu_pt2_vs_eta"].Add(hc_dy["h_eff_mu_pt2_vs_eta"], dy_title, cdy, 2, sdy);
    p["p_eff_mu_pt2_vs_eta"].Add(hc_tt["h_eff_mu_pt2_vs_eta"], tt_title, ctt, 2, stt);
    p["p_eff_mu_pt2_vs_eta"].SetYAxisRange(min, max);
    p["p_eff_mu_pt2_vs_eta"].SetLegendOption("p");
    p["p_eff_mu_pt2_vs_eta"].SetLegendTextSize(0.042);
    p["p_eff_mu_pt2_vs_eta"].AddText("Muon", 0.25, 0.235);

    // mu eff vs eta 
    p["p_eff_mu_vs_eta"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_mu_vs_eta"].Add(hc_dy["h_eff_mu_vs_eta"], dy_title, cdy, 2, sdy);
    p["p_eff_mu_vs_eta"].Add(hc_tt["h_eff_mu_vs_eta"], tt_title, ctt, 2, stt);
    p["p_eff_mu_vs_eta"].SetYAxisRange(min, max);
    p["p_eff_mu_vs_eta"].SetLegendOption("p");
    p["p_eff_mu_vs_eta"].SetLegendTextSize(0.042);
    p["p_eff_mu_vs_eta"].AddText("Muon", 0.25, 0.235);

    // table
    CTable t = rt::CreateTableFromHist(hc["h_eff_mu"],"eff DY - eff ttbar", "$\\eta$", "$p_{T}$", "", "GeV", "1.3", "1.2", "1.0");                                                                         
    if (tex)
    {
        t.printTex();
    }
    else
    {
        t.print();
    }

    cout << endl;

    // print
    if (suffix=="all")
    {
        hc.Print(path, "png");
        hc.Print(path, "pdf");
        hc.Print(path, "eps");
        rt::Print(p, path, "png");
        rt::Print(p, path, "pdf");
        rt::Print(p, path, "eps");
    }
    else
    {
        hc.Print(path, suffix);
        rt::Print(p, path, suffix);
    }
}

