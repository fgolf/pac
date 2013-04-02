#include "rt/RootTools.h"
#include "CTable.h"
#include <iostream> 

using namespace std;
	
const float lumi = 19.5;

void OverlayElectronEffPlots(const bool tex = false, const std::string& suffix = "png")
{
/* 	rt::TH1Container hc_dy("plots/mceff/dy/plots.root"); */
/* 	rt::TH1Container hc_tt("plots/mceff/ttjets/plots.root"); */
	rt::TH1Container hc_dy("plots/mceff/dy/plots_1M.root");
	rt::TH1Container hc_tt("plots/mceff/ttjets/plots_1M.root");
    std::string path = "plots/mceff/overlay";

    rt::TH1Container hc;

	std::map<std::string, rt::TH1Overlay> p;

	// set style
	rt::SetTDRStyle();
	gStyle->SetTitleBorderSize(0);
    hc.SetMarkerSize(1.8);

    // more projections
    hc_dy.Add(rt::MakeEfficiencyProjectionPlot(hc_dy["h_reco_el_nocrack"    ], hc_dy["h_mc_el"], "y", "h_eff_el_vs_pt_nocrack"     , "electron efficiency (no crack);p_{T} (GeV)"    ));
    hc_tt.Add(rt::MakeEfficiencyProjectionPlot(hc_tt["h_reco_el_nocrack"    ], hc_tt["h_mc_el"], "y", "h_eff_el_vs_pt_nocrack"     , "electron efficiency (no crack);p_{T} (GeV)"    ));
    hc_dy.Add(rt::MakeEfficiencyProjectionPlot(hc_dy["h_reco_el_id_nocrack" ], hc_dy["h_mc_el"], "y", "h_eff_el_id_vs_pt_nocrack"  , "electron id efficiency (no crack);p_{T} (GeV)" ));
    hc_tt.Add(rt::MakeEfficiencyProjectionPlot(hc_tt["h_reco_el_id_nocrack" ], hc_tt["h_mc_el"], "y", "h_eff_el_id_vs_pt_nocrack"  , "electron id efficiency (no crack);p_{T} (GeV)" ));
    hc_dy.Add(rt::MakeEfficiencyProjectionPlot(hc_dy["h_reco_el_iso_nocrack"], hc_dy["h_mc_el"], "y", "h_eff_el_iso_vs_pt_nocrack" , "electron iso efficiency (no crack);p_{T} (GeV)"));
    hc_tt.Add(rt::MakeEfficiencyProjectionPlot(hc_tt["h_reco_el_iso_nocrack"], hc_tt["h_mc_el"], "y", "h_eff_el_iso_vs_pt_nocrack" , "electron iso efficiency (no crack);p_{T} (GeV)"));
    hc_dy.Add(rt::MakeEfficiencyProjectionPlot(hc_dy["h_reco_el_id_nocrack" ], hc_dy["h_mc_el"], "x", "h_eff_el_id_vs_eta_nocrack" , "electron id efficiency (no crack);|#eta|"      ));
    hc_tt.Add(rt::MakeEfficiencyProjectionPlot(hc_tt["h_reco_el_id_nocrack" ], hc_tt["h_mc_el"], "x", "h_eff_el_id_vs_eta_nocrack" , "electron id efficiency (no crack);|#eta|"      ));

    hc_dy.Add(rt::MakeEfficiencyProjectionPlot(hc_dy["h_reco_el_id"], hc_dy["h_mc_el"], "y", "h_eff_el_id_vs_pt_barrel" , "electron id efficiency (barrel);p_{T} (GeV)",     0, 1.4));
    hc_tt.Add(rt::MakeEfficiencyProjectionPlot(hc_tt["h_reco_el_id"], hc_tt["h_mc_el"], "y", "h_eff_el_id_vs_pt_barrel" , "electron id efficiency (barrel);p_{T} (GeV)",     0, 1.4));
    hc_dy.Add(rt::MakeEfficiencyProjectionPlot(hc_dy["h_reco_el_id"], hc_dy["h_mc_el"], "y", "h_eff_el_id_vs_pt_endcap" , "electron id efficiency (endcap);p_{T} (GeV)", 1.6,    2.5));
    hc_tt.Add(rt::MakeEfficiencyProjectionPlot(hc_tt["h_reco_el_id"], hc_tt["h_mc_el"], "y", "h_eff_el_id_vs_pt_endcap" , "electron id efficiency (endcap);p_{T} (GeV)", 1.6,    2.5));

    hc_dy.Add(rt::MakeEfficiencyProjectionPlot(hc_dy["h_reco_el_id_nocrack"], hc_dy["h_mc_el"], "y", "h_eff_el_id_vs_pt_nocrack_barrel" , "electron id efficiency (barrel);p_{T} (GeV)",     0, 1.4));
    hc_tt.Add(rt::MakeEfficiencyProjectionPlot(hc_tt["h_reco_el_id_nocrack"], hc_tt["h_mc_el"], "y", "h_eff_el_id_vs_pt_nocrack_barrel" , "electron id efficiency (barrel);p_{T} (GeV)",     0, 1.4));
    hc_dy.Add(rt::MakeEfficiencyProjectionPlot(hc_dy["h_reco_el_id_nocrack"], hc_dy["h_mc_el"], "y", "h_eff_el_id_vs_pt_nocrack_endcap" , "electron id efficiency (endcap);p_{T} (GeV)", 1.6,    2.5));
    hc_tt.Add(rt::MakeEfficiencyProjectionPlot(hc_tt["h_reco_el_id_nocrack"], hc_tt["h_mc_el"], "y", "h_eff_el_id_vs_pt_nocrack_endcap" , "electron id efficiency (endcap);p_{T} (GeV)", 1.6,    2.5));

    hc_dy.Add(rt::MakeEfficiencyProjectionPlot(hc_dy["h_reco_el_iso"], hc_dy["h_mc_el"], "y", "h_eff_el_iso_vs_pt_barrel" , "electron iso efficiency (barrel);p_{T} (GeV)",     0, 1.4442));
    hc_tt.Add(rt::MakeEfficiencyProjectionPlot(hc_tt["h_reco_el_iso"], hc_tt["h_mc_el"], "y", "h_eff_el_iso_vs_pt_barrel" , "electron iso efficiency (barrel);p_{T} (GeV)",     0, 1.4442));
    hc_dy.Add(rt::MakeEfficiencyProjectionPlot(hc_dy["h_reco_el_iso"], hc_dy["h_mc_el"], "y", "h_eff_el_iso_vs_pt_endcap" , "electron iso efficiency (endcap);p_{T} (GeV)", 1.566,    2.5));
    hc_tt.Add(rt::MakeEfficiencyProjectionPlot(hc_tt["h_reco_el_iso"], hc_tt["h_mc_el"], "y", "h_eff_el_iso_vs_pt_endcap" , "electron iso efficiency (endcap);p_{T} (GeV)", 1.566,    2.5));

    // difference
    hc.Add(rt::SubtractHists(hc_dy["h_eff_el_pt1_vs_pt" ], hc_tt["h_eff_el_pt1_vs_pt" ], "h_eff_el_diff_pt1_vs_pt" , "#varepsilon_{DY} - #varepsilon_{t#bar{t}} (higher p_{T} electron);p_{T} (GeV)"));
    hc.Add(rt::SubtractHists(hc_dy["h_eff_el_pt2_vs_pt" ], hc_tt["h_eff_el_pt2_vs_pt" ], "h_eff_el_diff_pt2_vs_pt" , "#varepsilon_{DY} - #varepsilon_{t#bar{t}} (lower p_{T} electron);p_{T} (GeV)" ));
    hc.Add(rt::SubtractHists(hc_dy["h_eff_el_vs_pt"     ], hc_tt["h_eff_el_vs_pt"     ], "h_eff_el_diff_vs_pt"     , "#varepsilon_{DY} - #varepsilon_{t#bar{t}} (electron);p_{T} (GeV)"             ));
    hc.Add(rt::SubtractHists(hc_dy["h_eff_el_pt1_vs_eta"], hc_tt["h_eff_el_pt1_vs_eta"], "h_eff_el_diff_pt1_vs_eta", "#varepsilon_{DY} - #varepsilon_{t#bar{t}} (higher p_{T} electron);|#eta|"));
    hc.Add(rt::SubtractHists(hc_dy["h_eff_el_pt2_vs_eta"], hc_tt["h_eff_el_pt2_vs_eta"], "h_eff_el_diff_pt2_vs_eta", "#varepsilon_{DY} - #varepsilon_{t#bar{t}} (lower p_{T} electron);|#eta|" ));
    hc.Add(rt::SubtractHists(hc_dy["h_eff_el_vs_eta"    ], hc_tt["h_eff_el_vs_eta"    ], "h_eff_el_diff_vs_eta"    , "#varepsilon_{DY} - #varepsilon_{t#bar{t}} (electron);|#eta|"             ));
    hc.Add(rt::SubtractHists(hc_dy["h_eff_el"           ], hc_tt["h_eff_el"           ], "h_eff_el_diff"           , "#varepsilon_{DY} - #varepsilon_{t#bar{t}} (electron);|#eta|;p_{T} (GeV)" ));

    // relative difference
    hc.Add(rt::DivideHists(hc["h_eff_el_diff_pt1_vs_pt" ], hc_dy["h_eff_el_pt1_vs_pt" ], "h_eff_el_rel_diff_pt1_vs_pt" , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (higher p_{T} electron);p_{T} (GeV)"));
    hc.Add(rt::DivideHists(hc["h_eff_el_diff_pt2_vs_pt" ], hc_dy["h_eff_el_pt2_vs_pt" ], "h_eff_el_rel_diff_pt2_vs_pt" , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (lower p_{T} electron);p_{T} (GeV)" ));
    hc.Add(rt::DivideHists(hc["h_eff_el_diff_vs_pt"     ], hc_dy["h_eff_el_vs_pt"     ], "h_eff_el_rel_diff_vs_pt"     , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (electron);p_{T} (GeV)"             ));
    hc.Add(rt::DivideHists(hc["h_eff_el_diff_pt1_vs_eta"], hc_dy["h_eff_el_pt1_vs_eta"], "h_eff_el_rel_diff_pt1_vs_eta", "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (higher p_{T} electron);|#eta|"));
    hc.Add(rt::DivideHists(hc["h_eff_el_diff_pt2_vs_eta"], hc_dy["h_eff_el_pt2_vs_eta"], "h_eff_el_rel_diff_pt2_vs_eta", "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (lower p_{T} electron);|#eta|" ));
    hc.Add(rt::DivideHists(hc["h_eff_el_diff_vs_eta"    ], hc_dy["h_eff_el_vs_eta"    ], "h_eff_el_rel_diff_vs_eta"    , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (electron);|#eta|"             ));
    hc.Add(rt::DivideHists(hc["h_eff_el_diff"           ], hc_dy["h_eff_el"           ], "h_eff_el_rel_diff"           , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (electron);|#eta|;p_{T} (GeV)" ));

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

    p["p_eff_el_vs_pt_nocrack"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_el_vs_pt_nocrack"].Add(hc_dy["h_eff_el_vs_pt_nocrack"], dy_title, cdy, 2, sdy);
    p["p_eff_el_vs_pt_nocrack"].Add(hc_tt["h_eff_el_vs_pt_nocrack"], tt_title, ctt, 2, stt);
    p["p_eff_el_vs_pt_nocrack"].SetYAxisRange(min, max);
    p["p_eff_el_vs_pt_nocrack"].SetLegendOption("p");
    p["p_eff_el_vs_pt_nocrack"].SetLegendTextSize(0.042);
    p["p_eff_el_vs_pt_nocrack"].AddText("Electron", 0.25, 0.235);

    // el ISO eff vs pt 
    p["p_eff_el_iso_vs_pt"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_el_iso_vs_pt"].Add(hc_dy["h_eff_el_iso_vs_pt_nocrack"], dy_title, cdy, 2, sdy);
    p["p_eff_el_iso_vs_pt"].Add(hc_tt["h_eff_el_iso_vs_pt_nocrack"], tt_title, ctt, 2, stt);
    p["p_eff_el_iso_vs_pt"].SetYAxisRange(min, max);
    p["p_eff_el_iso_vs_pt"].SetLegendOption("p");
    p["p_eff_el_iso_vs_pt"].SetLegendTextSize(0.042);
    p["p_eff_el_iso_vs_pt"].AddText("Electron", 0.25, 0.235);

    p["p_eff_el_iso_vs_pt_barrel"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_el_iso_vs_pt_barrel"].Add(hc_dy["h_eff_el_iso_vs_pt_barrel"], dy_title, cdy, 2, sdy);
    p["p_eff_el_iso_vs_pt_barrel"].Add(hc_tt["h_eff_el_iso_vs_pt_barrel"], tt_title, ctt, 2, stt);
    p["p_eff_el_iso_vs_pt_barrel"].SetYAxisRange(min, max);
    p["p_eff_el_iso_vs_pt_barrel"].SetLegendOption("p");
    p["p_eff_el_iso_vs_pt_barrel"].SetLegendTextSize(0.042);
    p["p_eff_el_iso_vs_pt_barrel"].AddText("|#eta| < 1.4442", 0.25, 0.275);
    p["p_eff_el_iso_vs_pt_barrel"].AddText("Electron"       , 0.25, 0.235);

    p["p_eff_el_iso_vs_pt_endcap"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_el_iso_vs_pt_endcap"].Add(hc_dy["h_eff_el_iso_vs_pt_endcap"], dy_title, cdy, 2, sdy);
    p["p_eff_el_iso_vs_pt_endcap"].Add(hc_tt["h_eff_el_iso_vs_pt_endcap"], tt_title, ctt, 2, stt);
    p["p_eff_el_iso_vs_pt_endcap"].SetYAxisRange(min, max);
    p["p_eff_el_iso_vs_pt_endcap"].SetLegendOption("p");
    p["p_eff_el_iso_vs_pt_endcap"].SetLegendTextSize(0.042);
    p["p_eff_el_iso_vs_pt_endcap"].AddText("|#eta| > 1.566", 0.25, 0.275);
    p["p_eff_el_iso_vs_pt_endcap"].AddText("Electron"      , 0.25, 0.235);

    // el ISO eff vs eta 
    p["p_eff_el_iso_vs_eta"] = rt::TH1Overlay(title, "sb::off lg::top_right");
    p["p_eff_el_iso_vs_eta"].Add(hc_dy["h_eff_el_iso_vs_eta"], dy_title, cdy, 2, sdy);
    p["p_eff_el_iso_vs_eta"].Add(hc_tt["h_eff_el_iso_vs_eta"], tt_title, ctt, 2, stt);
    p["p_eff_el_iso_vs_eta"].SetYAxisRange(min, max);
    p["p_eff_el_iso_vs_eta"].SetLegendOption("p");
    p["p_eff_el_iso_vs_eta"].SetLegendTextSize(0.042);
    p["p_eff_el_iso_vs_eta"].AddText("Electron", 0.25, 0.235);

    // el ID eff vs pt 
    p["p_eff_el_id_vs_pt"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_el_id_vs_pt"].Add(hc_dy["h_eff_el_id_vs_pt_nocrack"], dy_title, cdy, 2, sdy);
    p["p_eff_el_id_vs_pt"].Add(hc_tt["h_eff_el_id_vs_pt_nocrack"], tt_title, ctt, 2, stt);
    p["p_eff_el_id_vs_pt"].SetYAxisRange(min, max);
    p["p_eff_el_id_vs_pt"].SetLegendOption("p");
    p["p_eff_el_id_vs_pt"].SetLegendTextSize(0.042);
    p["p_eff_el_id_vs_pt"].AddText("Electron", 0.25, 0.235);

    p["p_eff_el_id_vs_pt_barrel"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_el_id_vs_pt_barrel"].Add(hc_dy["h_eff_el_id_vs_pt_barrel"], dy_title, cdy, 2, sdy);
    p["p_eff_el_id_vs_pt_barrel"].Add(hc_tt["h_eff_el_id_vs_pt_barrel"], tt_title, ctt, 2, stt);
    p["p_eff_el_id_vs_pt_barrel"].SetYAxisRange(min, max);
    p["p_eff_el_id_vs_pt_barrel"].SetLegendOption("p");
    p["p_eff_el_id_vs_pt_barrel"].SetLegendTextSize(0.042);
    p["p_eff_el_id_vs_pt_barrel"].AddText("|#eta| < 1.4442", 0.25, 0.275);
    p["p_eff_el_id_vs_pt_barrel"].AddText("Electron"       , 0.25, 0.235);

    p["p_eff_el_id_vs_pt_endcap"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_el_id_vs_pt_endcap"].Add(hc_dy["h_eff_el_id_vs_pt_endcap"], dy_title, cdy, 2, sdy);
    p["p_eff_el_id_vs_pt_endcap"].Add(hc_tt["h_eff_el_id_vs_pt_endcap"], tt_title, ctt, 2, stt);
    p["p_eff_el_id_vs_pt_endcap"].SetYAxisRange(min, max);
    p["p_eff_el_id_vs_pt_endcap"].SetLegendOption("p");
    p["p_eff_el_id_vs_pt_endcap"].SetLegendTextSize(0.042);
    p["p_eff_el_id_vs_pt_endcap"].AddText("|#eta| > 1.566", 0.25, 0.275);
    p["p_eff_el_id_vs_pt_endcap"].AddText("Electron"      , 0.25, 0.235);

    p["p_eff_el_id_vs_pt_nocrack_barrel"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_el_id_vs_pt_nocrack_barrel"].Add(hc_dy["h_eff_el_id_vs_pt_nocrack_barrel"], dy_title, cdy, 2, sdy);
    p["p_eff_el_id_vs_pt_nocrack_barrel"].Add(hc_tt["h_eff_el_id_vs_pt_nocrack_barrel"], tt_title, ctt, 2, stt);
    p["p_eff_el_id_vs_pt_nocrack_barrel"].SetYAxisRange(min, max);
    p["p_eff_el_id_vs_pt_nocrack_barrel"].SetLegendOption("p");
    p["p_eff_el_id_vs_pt_nocrack_barrel"].SetLegendTextSize(0.042);
    p["p_eff_el_id_vs_pt_nocrack_barrel"].AddText("|#eta| < 1.4442", 0.25, 0.275);
    p["p_eff_el_id_vs_pt_nocrack_barrel"].AddText("Electron"       , 0.25, 0.235);
                                
    p["p_eff_el_id_vs_pt_nocrack_endcap"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_el_id_vs_pt_nocrack_endcap"].Add(hc_dy["h_eff_el_id_vs_pt_nocrack_endcap"], dy_title, cdy, 2, sdy);
    p["p_eff_el_id_vs_pt_nocrack_endcap"].Add(hc_tt["h_eff_el_id_vs_pt_nocrack_endcap"], tt_title, ctt, 2, stt);
    p["p_eff_el_id_vs_pt_nocrack_endcap"].SetYAxisRange(min, max);
    p["p_eff_el_id_vs_pt_nocrack_endcap"].SetLegendOption("p");
    p["p_eff_el_id_vs_pt_nocrack_endcap"].SetLegendTextSize(0.042);
    p["p_eff_el_id_vs_pt_nocrack_endcap"].AddText("|#eta| > 1.566", 0.25, 0.275);
    p["p_eff_el_id_vs_pt_nocrack_endcap"].AddText("Electron"      , 0.25, 0.235);

    // el ID eff vs eta 
    p["p_eff_el_id_vs_eta"] = rt::TH1Overlay(title, "sb::off lg::top_right");
    p["p_eff_el_id_vs_eta"].Add(hc_dy["h_eff_el_id_vs_eta"], dy_title, cdy, 2, sdy);
    p["p_eff_el_id_vs_eta"].Add(hc_tt["h_eff_el_id_vs_eta"], tt_title, ctt, 2, stt);
    p["p_eff_el_id_vs_eta"].SetYAxisRange(min, max);
    p["p_eff_el_id_vs_eta"].SetLegendOption("p");
    p["p_eff_el_id_vs_eta"].SetLegendTextSize(0.042);
    p["p_eff_el_id_vs_eta"].AddText("Electron", 0.25, 0.235);

    p["p_eff_el_id_vs_eta_nocrack"] = rt::TH1Overlay(title, "sb::off lg::top_right");
    p["p_eff_el_id_vs_eta_nocrack"].Add(hc_dy["h_eff_el_id_vs_eta_nocrack"], dy_title, cdy, 2, sdy);
    p["p_eff_el_id_vs_eta_nocrack"].Add(hc_tt["h_eff_el_id_vs_eta_nocrack"], tt_title, ctt, 2, stt);
    p["p_eff_el_id_vs_eta_nocrack"].SetYAxisRange(min, max);
    p["p_eff_el_id_vs_eta_nocrack"].SetLegendOption("p");
    p["p_eff_el_id_vs_eta_nocrack"].SetLegendTextSize(0.042);
    p["p_eff_el_id_vs_eta_nocrack"].AddText("Electron", 0.25, 0.235);

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
    CTable t_diff  = rt::CreateTableFromHist(hc["h_eff_el_diff"    ],"eff DY - eff ttbar"         , "$\\eta$", "$p_{T}$", "", "GeV", "1.3", "1.2", "1.0");                                                                         
    CTable t_rdiff = rt::CreateTableFromHist(hc["h_eff_el_rel_diff"],"(eff DY - eff ttbar)/eff DY", "$\\eta$", "$p_{T}$", "", "GeV", "1.3", "1.2", "1.0");                                                                         
    if (tex)
    {
        t_diff.printTex();
        t_rdiff.printTex();
    }
    else
    {
        t_diff.print();
        t_rdiff.print();
    }

    cout << endl;

    // print
    if (suffix=="all")
    {
        hc.Print(path + "/png", "png");
        hc.Print(path + "/png", "pdf");
        hc.Print(path + "/png", "eps");
        rt::Print(p, path + "/png", "png");
        rt::Print(p, path + "/png", "pdf");
        rt::Print(p, path + "/png", "eps");
    }
    else
    {
        hc.Print(path + "/" + suffix, suffix);
        rt::Print(p, path + "/" + suffix, suffix);
    }
}

void OverlayMuonEffPlots(const bool tex = false, const std::string& suffix = "png")
{
/* 	rt::TH1Container hc_dy("plots/mceff/dy/plots.root"); */
/* 	rt::TH1Container hc_tt("plots/mceff/ttjets/plots.root"); */
	rt::TH1Container hc_dy("plots/mceff/dy/plots_1M.root");
	rt::TH1Container hc_tt("plots/mceff/ttjets/plots_1M.root");
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
    hc.Add(rt::SubtractHists(hc_dy["h_eff_mu"           ], hc_tt["h_eff_mu"           ], "h_eff_mu_diff"           , "#varepsilon_{DY} - #varepsilon_{t#bar{t}} (#mu);|#eta|;p_{T} (GeV)" ));

    // relative difference
    hc.Add(rt::DivideHists(hc["h_eff_mu_diff_pt1_vs_pt" ], hc_dy["h_eff_mu_pt1_vs_pt" ], "h_eff_mu_rel_diff_pt1_vs_pt" , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (higher p_{T} muon);p_{T} (GeV)"));
    hc.Add(rt::DivideHists(hc["h_eff_mu_diff_pt2_vs_pt" ], hc_dy["h_eff_mu_pt2_vs_pt" ], "h_eff_mu_rel_diff_pt2_vs_pt" , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (lower p_{T} muon);p_{T} (GeV)" ));
    hc.Add(rt::DivideHists(hc["h_eff_mu_diff_vs_pt"     ], hc_dy["h_eff_mu_vs_pt"     ], "h_eff_mu_rel_diff_vs_pt"     , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (muon);p_{T} (GeV)"             ));
    hc.Add(rt::DivideHists(hc["h_eff_mu_diff_pt1_vs_eta"], hc_dy["h_eff_mu_pt1_vs_eta"], "h_eff_mu_rel_diff_pt1_vs_eta", "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (higher p_{T} muon);|#eta|"));
    hc.Add(rt::DivideHists(hc["h_eff_mu_diff_pt2_vs_eta"], hc_dy["h_eff_mu_pt2_vs_eta"], "h_eff_mu_rel_diff_pt2_vs_eta", "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (lower p_{T} muon);|#eta|" ));
    hc.Add(rt::DivideHists(hc["h_eff_mu_diff_vs_eta"    ], hc_dy["h_eff_mu_vs_eta"    ], "h_eff_mu_rel_diff_vs_eta"    , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (muon);|#eta|"             ));
    hc.Add(rt::DivideHists(hc["h_eff_mu_diff"           ], hc_dy["h_eff_mu"           ], "h_eff_mu_rel_diff"           , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (muon);|#eta|;p_{T} (GeV)" ));

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

    // mu ID eff vs pt 
    p["p_eff_mu_iso_vs_pt"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_mu_iso_vs_pt"].Add(hc_dy["h_eff_mu_iso_vs_pt"], dy_title, cdy, 2, sdy);
    p["p_eff_mu_iso_vs_pt"].Add(hc_tt["h_eff_mu_iso_vs_pt"], tt_title, ctt, 2, stt);
    p["p_eff_mu_iso_vs_pt"].SetYAxisRange(min, max);
    p["p_eff_mu_iso_vs_pt"].SetLegendOption("p");
    p["p_eff_mu_iso_vs_pt"].SetLegendTextSize(0.042);
    p["p_eff_mu_iso_vs_pt"].AddText("Muon", 0.25, 0.235);

    // mu ID eff vs eta 
    p["p_eff_mu_iso_vs_eta"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_mu_iso_vs_eta"].Add(hc_dy["h_eff_mu_iso_vs_eta"], dy_title, cdy, 2, sdy);
    p["p_eff_mu_iso_vs_eta"].Add(hc_tt["h_eff_mu_iso_vs_eta"], tt_title, ctt, 2, stt);
    p["p_eff_mu_iso_vs_eta"].SetYAxisRange(min, max);
    p["p_eff_mu_iso_vs_eta"].SetLegendOption("p");
    p["p_eff_mu_iso_vs_eta"].SetLegendTextSize(0.042);
    p["p_eff_mu_iso_vs_eta"].AddText("Muon", 0.25, 0.235);

    // mu id eff vs pt 
    p["p_eff_mu_id_vs_pt"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_mu_id_vs_pt"].Add(hc_dy["h_eff_mu_id_vs_pt"], dy_title, cdy, 2, sdy);
    p["p_eff_mu_id_vs_pt"].Add(hc_tt["h_eff_mu_id_vs_pt"], tt_title, ctt, 2, stt);
    p["p_eff_mu_id_vs_pt"].SetYAxisRange(min, max);
    p["p_eff_mu_id_vs_pt"].SetLegendOption("p");
    p["p_eff_mu_id_vs_pt"].SetLegendTextSize(0.042);
    p["p_eff_mu_id_vs_pt"].AddText("Muon", 0.25, 0.235);

    // mu id eff vs eta 
    p["p_eff_mu_id_vs_eta"] = rt::TH1Overlay(title, "sb::off lg::bottom_right");
    p["p_eff_mu_id_vs_eta"].Add(hc_dy["h_eff_mu_id_vs_eta"], dy_title, cdy, 2, sdy);
    p["p_eff_mu_id_vs_eta"].Add(hc_tt["h_eff_mu_id_vs_eta"], tt_title, ctt, 2, stt);
    p["p_eff_mu_id_vs_eta"].SetYAxisRange(min, max);
    p["p_eff_mu_id_vs_eta"].SetLegendOption("p");
    p["p_eff_mu_id_vs_eta"].SetLegendTextSize(0.042);
    p["p_eff_mu_id_vs_eta"].AddText("Muon", 0.25, 0.235);

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
    CTable t_diff  = rt::CreateTableFromHist(hc["h_eff_mu_diff"    ],"eff DY - eff ttbar"         , "$\\eta$", "$p_{T}$", "", "GeV", "1.3", "1.2", "1.0");                                                                         
    CTable t_rdiff = rt::CreateTableFromHist(hc["h_eff_mu_rel_diff"],"(eff DY - eff ttbar)/eff DY", "$\\eta$", "$p_{T}$", "", "GeV", "1.3", "1.2", "1.0");                                                                         
    if (tex)
    {
        t_diff.printTex();
        t_rdiff.printTex();
    }
    else
    {
        t_diff.print();
        t_rdiff.print();
    }

    cout << endl;

    // print
    if (suffix=="all")
    {
        hc.Print(path + "/png", "png");
        hc.Print(path + "/png", "pdf");
        hc.Print(path + "/png", "eps");
        rt::Print(p, path + "/png", "png");
        rt::Print(p, path + "/png", "pdf");
        rt::Print(p, path + "/png", "eps");
    }
    else
    {
        hc.Print(path + "/" + suffix, suffix);
        rt::Print(p, path + "/" + suffix, suffix);
    }
}

void OverlayEffPlots(const bool tex = false, const std::string& suffix = "png")
{
    OverlayElectronEffPlots(tex, suffix);
    OverlayMuonEffPlots(tex, suffix);
    return;
}

