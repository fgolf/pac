#include "rt/RootTools.h"
#include <string>

using namespace std;
using namespace rt;

void CombineEWKAndQCD()
{
    rt::TH1Container hc_qcd  ("plots/qcd/qcd_pt35.root");
    rt::TH1Container hc_dy   ("plots/dy/dy_pt35.root");
    rt::TH1Container hc_wjets("plots/wjets/wjets_pt35.root");
    rt::TH1Container hc;

    hc.Add(dynamic_cast<TH2F*>(hc_qcd["h_mu_num40c"]->Clone()));
    hc["h_mu_num40c"]->Add(hc_dy["h_mu_num40c"]);
    hc["h_mu_num40c"]->Add(hc_wjets["h_mu_num40c"]);

    hc.Add(dynamic_cast<TH2F*>(hc_qcd["h_mu_fo40c" ]->Clone()));
    hc["h_mu_fo40c"]->Add(hc_dy["h_mu_fo40c"]);
    hc["h_mu_fo40c"]->Add(hc_wjets["h_mu_fo40c"]);


    // FR(pt, eta)
    hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num40c"],hc["h_mu_fo40c"], "h_mufr40c", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 40);|#eta|;p_{T} (GeV)"));

    // FR(pt);
    hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num40c"],hc["h_mu_fo40c"], "y", "h_mufr40c_vs_pt", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 40);p_{T}"));


    // done
    hc.Write("plots/qcd/qcd_ewk_pt35.root");
}

void OverlayFRPlots(const string& suffix = "png")
{

    rt::TH1Container hc_data ("../ss2012/data/fake_rates/ssFR_data_standard_24Sep2012.root");
    rt::TH1Container hc_qcd  ("plots/qcd/qcd_pt35.root");
    rt::TH1Container hc_ewk  ("plots/qcd/qcd_ewk_pt35.root");
    rt::TH1Container hc_dy   ("plots/dy/dy_pt35.root");
    rt::TH1Container hc_wjets("plots/wjets/wjets_pt35.root");
    rt::TH1Container hc_ttb  ("plots/ttbar/ttbar_pt35.root");
    rt::TH1Container hc_com  ("plots/ttbar/ttbar_pt35.root");
    string path = "plots/ewk";

	// set style
	rt::SetTDRStyle();
	gStyle->SetTitleBorderSize(0);
    float max = 0.5;

    map<string, TH1Overlay> p;

    string data_name  = "data";
    string qcd_name   = "QCD";
    string ewk_name   = "QCD + EWK";
    string ttb_name   = "t#bar{t}";
    string wjets_name = "W+jets";
    string dy_name    = "DY+jets";

    Color_t data_color  = kBlack;
    Color_t ewk_color   = kRed;
    Color_t qcd_color   = kBlue; 
    Color_t ttb_color   = kMagenta+2; 
    Color_t wjets_color = kBlue; 
    Color_t dy_color    = kGreen+2; 

    Style_t data_marker  = 20; 
    Style_t qcd_marker   = 22; 
    Style_t ewk_marker   = 26; 
    Style_t ttb_marker   = 22; 
    Style_t wjets_marker = 24; 
    Style_t dy_marker    = 26; 

    // muons
    p["p_mufr40c_vs_pt_overlay"] = TH1Overlay("#mu FR (away jet p_{T} > 40 GeV);p_{T} (GeV);TL ratio", "sb::off lg::top"); 
    p["p_mufr40c_vs_pt_overlay"].Add(hc_data ["h_mufr40c_vs_pt"], data_name , data_color , 2, data_marker);
    p["p_mufr40c_vs_pt_overlay"].Add(hc_qcd  ["h_mufr40c_vs_pt"], qcd_name  , qcd_color  , 2, qcd_marker );
    p["p_mufr40c_vs_pt_overlay"].Add(hc_ewk  ["h_mufr40c_vs_pt"], ewk_name  , ewk_color  , 2, ewk_marker );
    //p["p_mufr40c_vs_pt_overlay"].Add(hc_wjets["h_mufr40c_vs_pt"], wjets_name, wjets_color, 2, wjets_marker);
    //p["p_mufr40c_vs_pt_overlay"].Add(hc_dy   ["h_mufr40c_vs_pt"], dy_name   , dy_color   , 2, dy_marker   );
    p["p_mufr40c_vs_pt_overlay"].SetYAxisRange(0, max);
    p["p_mufr40c_vs_pt_overlay"].SetLegendOption("p");
    p["p_mufr40c_vs_pt_overlay"].SetLegendTextSize(0.042);
    p["p_mufr40c_vs_pt_overlay"].AddText("Muons", 0.25, 0.835);

    //p["p_mufr40c_vs_nvtx_compare"] = TH1Overlay("#mu FR (away jet p_{T} > 40 GeV);Number of Vertices;TL ratio", "sb::off lg::top"); 
    //p["p_mufr40c_vs_nvtx_compare"].Add(hc_ci["h_mufr40c_vs_nvtxs"], "corrected"    , kBlue, 2, 20);
    //p["p_mufr40c_vs_nvtx_compare"].Add(hc_nc["h_mufr40c_vs_nvtxs"], "no correction", kRed , 2, 22);
    //p["p_mufr40c_vs_nvtx_compare"].SetYAxisRange(0, max);
    //p["p_mufr40c_vs_nvtx_compare"].SetLegendOption("p");
    //p["p_mufr40c_vs_nvtx_compare"].SetLegendTextSize(0.042);
    //p["p_mufr40c_vs_nvtx_compare"].AddText("Muons", 0.25, 0.835);

    //p["p_mufr40c_vs_eta_compare"] = TH1Overlay("#mu FR (away jet p_{T} > 40 GeV);|#eta|;TL ratio", "sb::off lg::top"); 
    //p["p_mufr40c_vs_eta_compare"].Add(hc_ci["h_mufr40c_vs_eta"], "corrected"    , kBlue, 2, 20);
    //p["p_mufr40c_vs_eta_compare"].Add(hc_nc["h_mufr40c_vs_eta"], "no correction", kRed , 2, 22);
    //p["p_mufr40c_vs_eta_compare"].SetYAxisRange(0, max);
    //p["p_mufr40c_vs_eta_compare"].SetLegendOption("p");
    //p["p_mufr40c_vs_eta_compare"].SetLegendTextSize(0.042);
    //p["p_mufr40c_vs_eta_compare"].AddText("Muons", 0.25, 0.835);

    //// electrons
    //p["p_elfr40c_vs_pt_compare"] = TH1Overlay("electron FR (away jet p_{T} > 40 GeV);p_{T} (GeV);TL ratio", "sb::off lg::top"); 
    //p["p_elfr40c_vs_pt_compare"].Add(hc_ci["h_elfr40c_vs_pt"], "corrected"    , kBlue, 2, 20);
    //p["p_elfr40c_vs_pt_compare"].Add(hc_nc["h_elfr40c_vs_pt"], "no correction", kRed , 2, 22);
    //p["p_elfr40c_vs_pt_compare"].SetYAxisRange(0, max);
    //p["p_elfr40c_vs_pt_compare"].SetLegendOption("p");
    //p["p_elfr40c_vs_pt_compare"].SetLegendTextSize(0.042);
    //p["p_elfr40c_vs_pt_compare"].AddText("Electrons", 0.25, 0.835);

    //p["p_elfr40c_vs_nvtx_compare"] = TH1Overlay("electron FR (away jet p_{T} > 40 GeV);Number of Vertices;TL ratio", "sb::off lg::top"); 
    //p["p_elfr40c_vs_nvtx_compare"].Add(hc_ci["h_elfr40c_vs_nvtxs"], "corrected"    , kBlue, 2, 20);
    //p["p_elfr40c_vs_nvtx_compare"].Add(hc_nc["h_elfr40c_vs_nvtxs"], "no correction", kRed , 2, 22);
    //p["p_elfr40c_vs_nvtx_compare"].SetYAxisRange(0, max);
    //p["p_elfr40c_vs_nvtx_compare"].SetLegendOption("p");
    //p["p_elfr40c_vs_nvtx_compare"].SetLegendTextSize(0.042);
    //p["p_elfr40c_vs_nvtx_compare"].AddText("Electrons", 0.25, 0.835);

    //p["p_elfr40c_vs_eta_compare"] = TH1Overlay("electron FR (away jet p_{T} > 40 GeV);|#eta|;TL ratio", "sb::off lg::top"); 
    //p["p_elfr40c_vs_eta_compare"].Add(hc_ci["h_elfr40c_vs_eta"], "corrected"    , kBlue, 2, 20);
    //p["p_elfr40c_vs_eta_compare"].Add(hc_nc["h_elfr40c_vs_eta"], "no correction", kRed , 2, 22);
    //p["p_elfr40c_vs_eta_compare"].SetYAxisRange(0, max);
    //p["p_elfr40c_vs_eta_compare"].SetLegendOption("p");
    //p["p_elfr40c_vs_eta_compare"].SetLegendTextSize(0.042);
    //p["p_elfr40c_vs_eta_compare"].AddText("Electrons", 0.25, 0.835);

    // print
    rt::Print(p, path, suffix);
}
