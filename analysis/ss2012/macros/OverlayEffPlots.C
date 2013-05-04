#include "rt/RootTools.h"
#include "CTable.h"
#include <iostream> 
#include <string> 

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

	const std::string title = "CMS Simulation, #sqrt{s} = 8 TeV";

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

	const std::string title = "CMS Simulation, #sqrt{s} = 8 TeV";

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


void CreateOverlay
(
    std::map<std::string, rt::TH1Overlay>& p,
    const std::string& hist_name,
    const rt::TH1Container& hc_dy,
    const rt::TH1Container& hc_tt,
    const std::string& label = "",
    const std::string& option = "sb::off lg::bottom_right",
    const float min = 0.0,
    const float max = 1.1
)
{
	std::string plot_title = "CMS Simulation, #sqrt{s} = 8 TeV";
	std::string plot_name  = rt::string_replace_first(hist_name, "h_", "p_");

    Color_t cdy   = kRed;
    Color_t ctt   = kBlack;

    std::string dy_title = "DY #rightarrow l^{+}l^{-}";
    std::string tt_title = "t#bar{t}";

    Style_t sdy = 20;
    Style_t stt = 22;

    p[plot_name] = rt::TH1Overlay(plot_title, option);
    p[plot_name].Add(hc_dy[hist_name], dy_title, cdy, 2, sdy);
    p[plot_name].Add(hc_tt[hist_name], tt_title, ctt, 2, stt);
    p[plot_name].SetYAxisRange(min, max);
    p[plot_name].SetLegendOption("p");
    p[plot_name].SetLegendTextSize(0.042);
    if (not label.empty())
    {
        p[plot_name].AddText(label, 0.25, 0.235);
    }

    return;
}

    // el eff pt1 vs pt 

void OverlayEffPlots(const bool tex = false, const std::string& suffix = "png")
{
/*     OverlayElectronEffPlots(tex, suffix); */
/*     OverlayMuonEffPlots(tex, suffix); */
/*     return; */

	rt::TH1Container hc_dy("plots/mceff/dy/plots_1M_v3.root");
	rt::TH1Container hc_tt("plots/mceff/ttjets/plots_1M_v3.root");
/* 	rt::TH1Container hc_dy("plots/mceff/dy/plots_1M_v2.root"); */
/* 	rt::TH1Container hc_tt("plots/mceff/ttjets/plots_1M_v2.root"); */
/* 	rt::TH1Container hc_dy("plots/mceff/dy/plots_1M.root"); */
/* 	rt::TH1Container hc_tt("plots/mceff/ttjets/plots_1M.root"); */
/* 	rt::TH1Container hc_dy("plots/mceff/dy/plots_test.root"); */
/* 	rt::TH1Container hc_tt("plots/mceff/dy/plots_test.root"); */
    rt::TH1Container hc;
/*     std::string path = "plots/mceff/overlay2"; */
    std::string path = "plots/mceff/overlay3";


	std::map<std::string, rt::TH1Overlay> p;

	// set style
	rt::SetTDRStyle();
	gStyle->SetTitleBorderSize(0);
    hc.SetMarkerSize(1.8);

    // relative difference
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_el"             ], hc_tt["h_eff_el"             ], "h_eff_el_rel_diff"              , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (electron);|#eta|;p_{T} (GeV)"       ));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_el_vs_eta"      ], hc_tt["h_eff_el_vs_eta"      ], "h_eff_el_rel_diff_vs_eta"       , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (electron);|#eta|"                   ));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_el_vs_pt"       ], hc_tt["h_eff_el_vs_pt"       ], "h_eff_el_rel_diff_vs_pt"        , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (electron);p_{T} (GeV)"              ));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_el_vs_pt_barrel"], hc_tt["h_eff_el_vs_pt_barrel"], "h_eff_el_rel_diff_vs_pt_barrel" , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (electron; |#eta| < 1.4);p_{T} (GeV)"));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_el_vs_pt_endcap"], hc_tt["h_eff_el_vs_pt_endcap"], "h_eff_el_rel_diff_vs_pt_endcap" , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (electron; |#eta| > 1.6);p_{T} (GeV)"));

    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_el_id"             ], hc_tt["h_eff_el_id"             ], "h_eff_el_id_rel_diff"              , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (electron ID);|#eta|;p_{T} (GeV)"       ));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_el_id_vs_eta"      ], hc_tt["h_eff_el_id_vs_eta"      ], "h_eff_el_id_rel_diff_vs_eta"       , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (electron ID);|#eta|"                   ));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_el_id_vs_pt"       ], hc_tt["h_eff_el_id_vs_pt"       ], "h_eff_el_id_rel_diff_vs_pt"        , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (electron ID);p_{T} (GeV)"              ));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_el_id_vs_pt_barrel"], hc_tt["h_eff_el_id_vs_pt_barrel"], "h_eff_el_id_rel_diff_vs_pt_barrel" , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (electron ID; |#eta| < 1.4);p_{T} (GeV)"));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_el_id_vs_pt_endcap"], hc_tt["h_eff_el_id_vs_pt_endcap"], "h_eff_el_id_rel_diff_vs_pt_endcap" , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (electron ID; |#eta| > 1.6);p_{T} (GeV)"));

    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_el_iso"             ], hc_tt["h_eff_el_iso"             ], "h_eff_el_iso_rel_diff"              , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (electron Iso);|#eta|;p_{T} (GeV)"       ));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_el_iso_vs_eta"      ], hc_tt["h_eff_el_iso_vs_eta"      ], "h_eff_el_iso_rel_diff_vs_eta"       , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (electron Iso);|#eta|"                   ));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_el_iso_vs_pt"       ], hc_tt["h_eff_el_iso_vs_pt"       ], "h_eff_el_iso_rel_diff_vs_pt"        , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (electron Iso);p_{T} (GeV)"              ));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_el_iso_vs_pt_barrel"], hc_tt["h_eff_el_iso_vs_pt_barrel"], "h_eff_el_iso_rel_diff_vs_pt_barrel" , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (electron Iso; |#eta| < 1.4);p_{T} (GeV)"));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_el_iso_vs_pt_endcap"], hc_tt["h_eff_el_iso_vs_pt_endcap"], "h_eff_el_iso_rel_diff_vs_pt_endcap" , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (electron Iso; |#eta| > 1.6);p_{T} (GeV)"));

    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_mu"             ], hc_tt["h_eff_mu"             ], "h_eff_mu_rel_diff"              , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (#mu);|#eta|;p_{T} (GeV)"       ));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_mu_vs_eta"      ], hc_tt["h_eff_mu_vs_eta"      ], "h_eff_mu_rel_diff_vs_eta"       , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (#mu);|#eta|"                   ));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_mu_vs_pt"       ], hc_tt["h_eff_mu_vs_pt"       ], "h_eff_mu_rel_diff_vs_pt"        , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (#mu);p_{T} (GeV)"              ));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_mu_vs_pt_barrel"], hc_tt["h_eff_mu_vs_pt_barrel"], "h_eff_mu_rel_diff_vs_pt_barrel" , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (#mu; |#eta| < 1.2);p_{T} (GeV)"));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_mu_vs_pt_endcap"], hc_tt["h_eff_mu_vs_pt_endcap"], "h_eff_mu_rel_diff_vs_pt_endcap" , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (#mu; |#eta| > 1.2);p_{T} (GeV)"));

    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_mu_id"             ], hc_tt["h_eff_mu_id"             ], "h_eff_mu_id_rel_diff"              , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (#mu ID);|#eta|;p_{T} (GeV)"       ));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_mu_id_vs_eta"      ], hc_tt["h_eff_mu_id_vs_eta"      ], "h_eff_mu_id_rel_diff_vs_eta"       , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (#mu ID);|#eta|"                   ));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_mu_id_vs_pt"       ], hc_tt["h_eff_mu_id_vs_pt"       ], "h_eff_mu_id_rel_diff_vs_pt"        , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (#mu ID);p_{T} (GeV)"              ));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_mu_id_vs_pt_barrel"], hc_tt["h_eff_mu_id_vs_pt_barrel"], "h_eff_mu_id_rel_diff_vs_pt_barrel" , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (#mu ID; |#eta| < 1.2);p_{T} (GeV)"));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_mu_id_vs_pt_endcap"], hc_tt["h_eff_mu_id_vs_pt_endcap"], "h_eff_mu_id_rel_diff_vs_pt_endcap" , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (#mu ID; |#eta| > 1.2);p_{T} (GeV)"));

    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_mu_iso"             ], hc_tt["h_eff_mu_iso"             ], "h_eff_mu_iso_rel_diff"              , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (#mu Iso);|#eta|;p_{T} (GeV)"       ));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_mu_iso_vs_eta"      ], hc_tt["h_eff_mu_iso_vs_eta"      ], "h_eff_mu_iso_rel_diff_vs_eta"       , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (#mu Iso);|#eta|"                   ));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_mu_iso_vs_pt"       ], hc_tt["h_eff_mu_iso_vs_pt"       ], "h_eff_mu_iso_rel_diff_vs_pt"        , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (#mu Iso);p_{T} (GeV)"              ));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_mu_iso_vs_pt_barrel"], hc_tt["h_eff_mu_iso_vs_pt_barrel"], "h_eff_mu_iso_rel_diff_vs_pt_barrel" , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (#mu Iso; |#eta| < 1.2);p_{T} (GeV)"));
    hc.Add(rt::RelativeDiffHists(hc_dy["h_eff_mu_iso_vs_pt_endcap"], hc_tt["h_eff_mu_iso_vs_pt_endcap"], "h_eff_mu_iso_rel_diff_vs_pt_endcap" , "(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY} (#mu Iso; |#eta| > 1.2);p_{T} (GeV)"));

    // cross check
    hc_dy.Add(rt::AddHists(hc_dy["h_reco_el_id_vs_pt_barrel"], hc_dy["h_reco_el_id_vs_pt_endcap"], "h_reco_el_id_vs_pt_barrel_endcap", "sum N barrel + endcap"));
    hc_dy.Add(rt::AddHists(hc_dy["h_mc_el_vs_pt_barrel"     ], hc_dy["h_mc_el_vs_pt_endcap"     ], "h_mc_el_vs_pt_barrel_endcap"        , "sum D barrel + endcap"));
    hc_tt.Add(rt::AddHists(hc_tt["h_reco_el_id_vs_pt_barrel"], hc_tt["h_reco_el_id_vs_pt_endcap"], "h_reco_el_id_vs_pt_barrel_endcap", "sum N barrel + endcap"));
    hc_tt.Add(rt::AddHists(hc_tt["h_mc_el_vs_pt_barrel"     ], hc_tt["h_mc_el_vs_pt_endcap"     ], "h_mc_el_vs_pt_barrel_endcap"        , "sum D barrel + endcap"));
    hc_dy.Add(rt::MakeEfficiencyPlot(hc_dy["h_reco_el_id_vs_pt_barrel_endcap" ], hc_dy["h_mc_el_vs_pt_barrel_endcap"], "h_eff_el_id_vs_pt_barrel_endcap" , "electron ID efficiency;p_{T} (GeV)" ));
    hc_tt.Add(rt::MakeEfficiencyPlot(hc_tt["h_reco_el_id_vs_pt_barrel_endcap" ], hc_tt["h_mc_el_vs_pt_barrel_endcap"], "h_eff_el_id_vs_pt_barrel_endcap" , "electron ID efficiency;p_{T} (GeV)" ));

/*     rt::MaskHist2D(hc_dy["h_reco_el"], "x", 1.444, 1.566); */
/*     rt::MaskHist2D(hc_dy["h_mc_el"  ], "x", 1.444, 1.566); */
/*     rt::MaskHist2D(hc_tt["h_reco_el"], "x", 1.444, 1.566); */
/*     rt::MaskHist2D(hc_tt["h_mc_el"  ], "x", 1.444, 1.566); */
    hc_dy.Add(rt::MakeEfficiencyProjectionPlot(hc_dy["h_reco_el" ], hc_dy["h_mc_el"], "x", "h_eff_el_vs_eta_zoom1", "electron efficiency (30-50 bin);|#eta|", 30, 50));
    hc_tt.Add(rt::MakeEfficiencyProjectionPlot(hc_tt["h_reco_el" ], hc_tt["h_mc_el"], "x", "h_eff_el_vs_eta_zoom1", "electron efficiency (30-50 bin);|#eta|", 30, 50));
    hc_dy.Add(dynamic_cast<TH1*>(hc_dy["h_reco_el"]->Clone("h_reco_el_mask2")));
    hc_dy.Add(dynamic_cast<TH1*>(hc_dy["h_mc_el"  ]->Clone("h_mc_el_mask2"  )));
    hc_tt.Add(dynamic_cast<TH1*>(hc_tt["h_reco_el"]->Clone("h_reco_el_mask2")));
    hc_tt.Add(dynamic_cast<TH1*>(hc_tt["h_mc_el"  ]->Clone("h_mc_el_mask2"  )));
    rt::MaskHist2D(hc_dy["h_reco_el_mask2"], "y", 30, 50);
    rt::MaskHist2D(hc_dy["h_mc_el_mask2"  ], "y", 30, 50);
    rt::MaskHist2D(hc_tt["h_reco_el_mask2"], "y", 30, 50);
    rt::MaskHist2D(hc_tt["h_mc_el_mask2"  ], "y", 30, 50);
    hc_dy.Add(rt::MakeEfficiencyProjectionPlot(hc_dy["h_reco_el_mask2"], hc_dy["h_mc_el_mask2"], "x", "h_eff_el_vs_eta_zoom2", "electron efficiency (not 30-50 bin);|#eta|"));
    hc_tt.Add(rt::MakeEfficiencyProjectionPlot(hc_tt["h_reco_el_mask2"], hc_tt["h_mc_el_mask2"], "x", "h_eff_el_vs_eta_zoom2", "electron efficiency (not 30-50 bin);|#eta|"));

    // overlay
    CreateOverlay(p, "h_mc_el_vs_pt_barrel_endcap"     , hc_dy, hc_tt, "electrons", "sb::off dt::norm lg::top_right", 1, -1);
    CreateOverlay(p, "h_reco_el_id_vs_pt_barrel_endcap", hc_dy, hc_tt, "electrons", "sb::off dt::norm lg::top_right", 1, -1);
    CreateOverlay(p, "h_eff_el_id_vs_pt_barrel_endcap" , hc_dy, hc_tt, "electrons", "sb::off lg::bottom", 0, 1.1);
    CreateOverlay(p, "h_eff_el_vs_eta_zoom1"           , hc_dy, hc_tt, "electrons", "sb::off lg::bottom", 0, 1.1);
    CreateOverlay(p, "h_eff_el_vs_eta_zoom2"           , hc_dy, hc_tt, "electrons", "sb::off lg::bottom", 0, 1.1);

    // eff vs eta 
    p["p_reco_el_id_vs_pt_dy_reco_barrrel_endcap_compare"] = rt::TH1Overlay("matched electron", "sb::off lg::bottom_right");
    p["p_reco_el_id_vs_pt_dy_reco_barrrel_endcap_compare"].Add(hc_dy["h_reco_el_id_vs_pt_barrel"], "DY barrel");
    p["p_reco_el_id_vs_pt_dy_reco_barrrel_endcap_compare"].Add(hc_dy["h_reco_el_id_vs_pt_endcap"], "DY endcap");
    p["p_reco_el_id_vs_pt_dy_reco_barrrel_endcap_compare"].SetLegendOption("p");
    p["p_reco_el_id_vs_pt_dy_reco_barrrel_endcap_compare"].SetLegendTextSize(0.042);
    p["p_reco_el_id_vs_pt_dy_reco_barrrel_endcap_compare"].AddText("electrons", 0.25, 0.235);

    p["p_mc_el_vs_pt_dy_barrrel_endcap_compare"] = rt::TH1Overlay("electron MC", "sb::off lg::bottom_right");
    p["p_mc_el_vs_pt_dy_barrrel_endcap_compare"].Add(hc_dy["h_mc_el_vs_pt_barrel"], "DY barrel");
    p["p_mc_el_vs_pt_dy_barrrel_endcap_compare"].Add(hc_dy["h_mc_el_vs_pt_endcap"], "DY endcap");
    p["p_mc_el_vs_pt_dy_barrrel_endcap_compare"].SetLegendOption("p");
    p["p_mc_el_vs_pt_dy_barrrel_endcap_compare"].SetLegendTextSize(0.042);
    p["p_mc_el_vs_pt_dy_barrrel_endcap_compare"].AddText("electrons", 0.25, 0.235);

    p["p_reco_el_id_vs_pt_tt_reco_barrrel_endcap_compare"] = rt::TH1Overlay("matched electron", "sb::off lg::bottom_right");
    p["p_reco_el_id_vs_pt_tt_reco_barrrel_endcap_compare"].Add(hc_tt["h_reco_el_id_vs_pt_barrel"], "tt barrel");
    p["p_reco_el_id_vs_pt_tt_reco_barrrel_endcap_compare"].Add(hc_tt["h_reco_el_id_vs_pt_endcap"], "tt endcap");
    p["p_reco_el_id_vs_pt_tt_reco_barrrel_endcap_compare"].SetLegendOption("p");
    p["p_reco_el_id_vs_pt_tt_reco_barrrel_endcap_compare"].SetLegendTextSize(0.042);
    p["p_reco_el_id_vs_pt_tt_reco_barrrel_endcap_compare"].AddText("electrons", 0.25, 0.235);

    p["p_mc_el_vs_pt_tt_barrrel_endcap_compare"] = rt::TH1Overlay("electron MC", "sb::off lg::bottom_right");
    p["p_mc_el_vs_pt_tt_barrrel_endcap_compare"].Add(hc_tt["h_mc_el_vs_pt_barrel"], "tt barrel");
    p["p_mc_el_vs_pt_tt_barrrel_endcap_compare"].Add(hc_tt["h_mc_el_vs_pt_endcap"], "tt endcap");
    p["p_mc_el_vs_pt_tt_barrrel_endcap_compare"].SetLegendOption("p");
    p["p_mc_el_vs_pt_tt_barrrel_endcap_compare"].SetLegendTextSize(0.042);
    p["p_mc_el_vs_pt_tt_barrrel_endcap_compare"].AddText("electrons", 0.25, 0.235);

    p["p_reco_el_vs_pt_compare"] = rt::TH1Overlay("matched electron", "sb::off lg::bottom_right");
    p["p_reco_el_vs_pt_compare"].Add(hc_dy["h_reco_el_vs_pt"], "DY");
    p["p_reco_el_vs_pt_compare"].Add(hc_tt["h_reco_el_vs_pt"], "tt");
    p["p_reco_el_vs_pt_compare"].SetLegendOption("p");
    p["p_reco_el_vs_pt_compare"].SetLegendTextSize(0.042);
    p["p_reco_el_vs_pt_compare"].AddText("electrons", 0.25, 0.235);

    p["p_mc_el_vs_pt_compare"] = rt::TH1Overlay("MC electron", "sb::off lg::bottom_right");
    p["p_mc_el_vs_pt_compare"].Add(hc_dy["h_mc_el_vs_pt"], "DY");
    p["p_mc_el_vs_pt_compare"].Add(hc_tt["h_mc_el_vs_pt"], "tt");
    p["p_mc_el_vs_pt_compare"].SetLegendOption("p");
    p["p_mc_el_vs_pt_compare"].SetLegendTextSize(0.042);
    p["p_mc_el_vs_pt_compare"].AddText("electrons", 0.25, 0.235);

/* 	std::string plot_title = "CMS Simulation, #sqrt{s} = 8 TeV"; */

    p["p_eff_el_rel_diff_vs_pt_compare"] = rt::TH1Overlay("(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY};p_{T} (GeV)", "sb::off lg::top_right");
    p["p_eff_el_rel_diff_vs_pt_compare"].Add(hc["h_eff_el_rel_diff_vs_pt_barrel"], "barrel", kBlue, 2, 20);
    p["p_eff_el_rel_diff_vs_pt_compare"].Add(hc["h_eff_el_rel_diff_vs_pt_endcap"], "endcap", kRed , 2, 22);
    p["p_eff_el_rel_diff_vs_pt_compare"].SetYAxisRange(-0.20, 0.10);
    p["p_eff_el_rel_diff_vs_pt_compare"].SetLegendOption("p");
    p["p_eff_el_rel_diff_vs_pt_compare"].SetLegendTextSize(0.042);
    p["p_eff_el_rel_diff_vs_pt_compare"].AddText("electrons", 0.55, 0.835);

    p["p_eff_el_rel_diff_vs_eta"] = rt::TH1Overlay("(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY};|#eta|", "sb::off lg::off");
    p["p_eff_el_rel_diff_vs_eta"].Add(hc["h_eff_el_rel_diff_vs_eta"], "", kBlue, 2, 20);
    p["p_eff_el_rel_diff_vs_eta"].SetYAxisRange(0.00, 0.10);
    p["p_eff_el_rel_diff_vs_eta"].SetLegendOption("p");
    p["p_eff_el_rel_diff_vs_eta"].SetLegendTextSize(0.042);
    p["p_eff_el_rel_diff_vs_eta"].AddText("electrons", 0.55, 0.835);

    p["p_eff_mu_rel_diff_vs_pt_compare"] = rt::TH1Overlay("(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY};p_{T} (GeV)", "sb::off lg::top_right");
    p["p_eff_mu_rel_diff_vs_pt_compare"].Add(hc["h_eff_mu_rel_diff_vs_pt_barrel"], "barrel", kBlue, 2, 20);
    p["p_eff_mu_rel_diff_vs_pt_compare"].Add(hc["h_eff_mu_rel_diff_vs_pt_endcap"], "endcap", kRed , 2, 22);
    p["p_eff_mu_rel_diff_vs_pt_compare"].SetYAxisRange(-0.15, 0.0);
    p["p_eff_mu_rel_diff_vs_pt_compare"].SetLegendOption("p");
    p["p_eff_mu_rel_diff_vs_pt_compare"].SetLegendTextSize(0.042);
    p["p_eff_mu_rel_diff_vs_pt_compare"].AddText("muons", 0.55, 0.835);

    p["p_eff_mu_rel_diff_vs_eta"] = rt::TH1Overlay("(#varepsilon_{DY} - #varepsilon_{t#bar{t}})/#varepsilon_{DY};|#eta|", "sb::off lg::off");
    p["p_eff_mu_rel_diff_vs_eta"].Add(hc["h_eff_mu_rel_diff_vs_eta"], "", kBlue, 2, 20);
    p["p_eff_mu_rel_diff_vs_eta"].SetYAxisRange(0.00, 0.10);
    p["p_eff_mu_rel_diff_vs_eta"].SetLegendOption("p");
    p["p_eff_mu_rel_diff_vs_eta"].SetLegendTextSize(0.042);
    p["p_eff_mu_rel_diff_vs_eta"].AddText("muons", 0.55, 0.835);

    CreateOverlay(p, "h_eff_el_vs_eta"           , hc_dy, hc_tt, "electrons");
    CreateOverlay(p, "h_eff_el_vs_eta"           , hc_dy, hc_tt, "electrons");
    CreateOverlay(p, "h_eff_el_vs_pt"            , hc_dy, hc_tt, "electrons");
    CreateOverlay(p, "h_eff_el_vs_pt_barrel"     , hc_dy, hc_tt, "electrons");
    CreateOverlay(p, "h_eff_el_vs_pt_endcap"     , hc_dy, hc_tt, "electrons");
    CreateOverlay(p, "h_eff_el_id_vs_eta"        , hc_dy, hc_tt, "electrons");
    CreateOverlay(p, "h_eff_el_id_vs_pt"         , hc_dy, hc_tt, "electrons");
    CreateOverlay(p, "h_eff_el_id_vs_pt_barrel"  , hc_dy, hc_tt, "electrons");
    CreateOverlay(p, "h_eff_el_id_vs_pt_endcap"  , hc_dy, hc_tt, "electrons");
    CreateOverlay(p, "h_eff_el_iso_vs_eta"       , hc_dy, hc_tt, "electrons");
    CreateOverlay(p, "h_eff_el_iso_vs_pt"        , hc_dy, hc_tt, "electrons");
    CreateOverlay(p, "h_eff_el_iso_vs_pt_barrel" , hc_dy, hc_tt, "electrons");
    CreateOverlay(p, "h_eff_el_iso_vs_pt_endcap" , hc_dy, hc_tt, "electrons");

    CreateOverlay(p, "h_eff_mu_vs_eta"           , hc_dy, hc_tt, "muons");
    CreateOverlay(p, "h_eff_mu_vs_pt"            , hc_dy, hc_tt, "muons");
    CreateOverlay(p, "h_eff_mu_vs_pt_barrel"     , hc_dy, hc_tt, "muons");
    CreateOverlay(p, "h_eff_mu_vs_pt_endcap"     , hc_dy, hc_tt, "muons");
    CreateOverlay(p, "h_eff_mu_id_vs_eta"        , hc_dy, hc_tt, "muons");
    CreateOverlay(p, "h_eff_mu_id_vs_pt"         , hc_dy, hc_tt, "muons");
    CreateOverlay(p, "h_eff_mu_id_vs_pt_barrel"  , hc_dy, hc_tt, "muons");
    CreateOverlay(p, "h_eff_mu_id_vs_pt_endcap"  , hc_dy, hc_tt, "muons");
    CreateOverlay(p, "h_eff_mu_iso_vs_eta"       , hc_dy, hc_tt, "muons");
    CreateOverlay(p, "h_eff_mu_iso_vs_pt"        , hc_dy, hc_tt, "muons");
    CreateOverlay(p, "h_eff_mu_iso_vs_pt_barrel" , hc_dy, hc_tt, "muons");
    CreateOverlay(p, "h_eff_mu_iso_vs_pt_endcap" , hc_dy, hc_tt, "muons");

    // table
    CTable t_el_rdiff = rt::CreateTableFromHist(hc["h_eff_el_rel_diff"],"(eff DY - eff ttbar)/eff DY", "$\\eta$", "$p_{T}$", "", "GeV", "1.3", "1.2", "1.0");                                                                         
    CTable t_mu_rdiff = rt::CreateTableFromHist(hc["h_eff_mu_rel_diff"],"(eff DY - eff ttbar)/eff DY", "$\\eta$", "$p_{T}$", "", "GeV", "1.3", "1.2", "1.0");                                                                         
    if (tex)
    {
        t_el_rdiff.printTex();
        t_mu_rdiff.printTex();
    }
    else
    {
        t_el_rdiff.print();
        t_mu_rdiff.print();
    }

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
