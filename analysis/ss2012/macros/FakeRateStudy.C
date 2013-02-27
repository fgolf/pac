#include "rt/RootTools.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;
using namespace rt;

void FakeRateStudy(const std::string& suffix = "png")
{
    rt::TH1Container hc_nc("plots/fake_rates/noncoriso/combined_noncoriso.root");
    rt::TH1Container hc_ci("data/fake_rates/ssFR_data_standard_24Sep2012.root");
    string path = "plots/fake_rates/compare_iso";

	// set style
	rt::SetTDRStyle();
	gStyle->SetTitleBorderSize(0);
    float max = 0.5;

    map<string, TH1Overlay> p;

    // muons
    p["p_mufr40c_vs_pt_compare"] = TH1Overlay("#mu FR (away jet p_{T} > 40 GeV);p_{T} (GeV);TL ratio", "sb::off lg::top"); 
    p["p_mufr40c_vs_pt_compare"].Add(hc_ci["h_mufr40c_vs_pt"], "corrected"    , kBlue, 2, 20);
    p["p_mufr40c_vs_pt_compare"].Add(hc_nc["h_mufr40c_vs_pt"], "no correction", kRed , 2, 22);
    p["p_mufr40c_vs_pt_compare"].SetYAxisRange(0, max);
    p["p_mufr40c_vs_pt_compare"].SetLegendOption("p");
    p["p_mufr40c_vs_pt_compare"].SetLegendTextSize(0.042);
    p["p_mufr40c_vs_pt_compare"].AddText("Muons", 0.25, 0.835);

    p["p_mufr40c_vs_nvtx_compare"] = TH1Overlay("#mu FR (away jet p_{T} > 40 GeV);Number of Vertices;TL ratio", "sb::off lg::top"); 
    p["p_mufr40c_vs_nvtx_compare"].Add(hc_ci["h_mufr40c_vs_nvtxs"], "corrected"    , kBlue, 2, 20);
    p["p_mufr40c_vs_nvtx_compare"].Add(hc_nc["h_mufr40c_vs_nvtxs"], "no correction", kRed , 2, 22);
    p["p_mufr40c_vs_nvtx_compare"].SetYAxisRange(0, max);
    p["p_mufr40c_vs_nvtx_compare"].SetLegendOption("p");
    p["p_mufr40c_vs_nvtx_compare"].SetLegendTextSize(0.042);
    p["p_mufr40c_vs_nvtx_compare"].AddText("Muons", 0.25, 0.835);

    p["p_mufr40c_vs_eta_compare"] = TH1Overlay("#mu FR (away jet p_{T} > 40 GeV);|#eta|;TL ratio", "sb::off lg::top"); 
    p["p_mufr40c_vs_eta_compare"].Add(hc_ci["h_mufr40c_vs_eta"], "corrected"    , kBlue, 2, 20);
    p["p_mufr40c_vs_eta_compare"].Add(hc_nc["h_mufr40c_vs_eta"], "no correction", kRed , 2, 22);
    p["p_mufr40c_vs_eta_compare"].SetYAxisRange(0, max);
    p["p_mufr40c_vs_eta_compare"].SetLegendOption("p");
    p["p_mufr40c_vs_eta_compare"].SetLegendTextSize(0.042);
    p["p_mufr40c_vs_eta_compare"].AddText("Muons", 0.25, 0.835);

    // electrons
    p["p_elfr40c_vs_pt_compare"] = TH1Overlay("electron FR (away jet p_{T} > 40 GeV);p_{T} (GeV);TL ratio", "sb::off lg::top"); 
    p["p_elfr40c_vs_pt_compare"].Add(hc_ci["h_elfr40c_vs_pt"], "corrected"    , kBlue, 2, 20);
    p["p_elfr40c_vs_pt_compare"].Add(hc_nc["h_elfr40c_vs_pt"], "no correction", kRed , 2, 22);
    p["p_elfr40c_vs_pt_compare"].SetYAxisRange(0, max);
    p["p_elfr40c_vs_pt_compare"].SetLegendOption("p");
    p["p_elfr40c_vs_pt_compare"].SetLegendTextSize(0.042);
    p["p_elfr40c_vs_pt_compare"].AddText("Electrons", 0.25, 0.835);

    p["p_elfr40c_vs_nvtx_compare"] = TH1Overlay("electron FR (away jet p_{T} > 40 GeV);Number of Vertices;TL ratio", "sb::off lg::top"); 
    p["p_elfr40c_vs_nvtx_compare"].Add(hc_ci["h_elfr40c_vs_nvtxs"], "corrected"    , kBlue, 2, 20);
    p["p_elfr40c_vs_nvtx_compare"].Add(hc_nc["h_elfr40c_vs_nvtxs"], "no correction", kRed , 2, 22);
    p["p_elfr40c_vs_nvtx_compare"].SetYAxisRange(0, max);
    p["p_elfr40c_vs_nvtx_compare"].SetLegendOption("p");
    p["p_elfr40c_vs_nvtx_compare"].SetLegendTextSize(0.042);
    p["p_elfr40c_vs_nvtx_compare"].AddText("Electrons", 0.25, 0.835);

    p["p_elfr40c_vs_eta_compare"] = TH1Overlay("electron FR (away jet p_{T} > 40 GeV);|#eta|;TL ratio", "sb::off lg::top"); 
    p["p_elfr40c_vs_eta_compare"].Add(hc_ci["h_elfr40c_vs_eta"], "corrected"    , kBlue, 2, 20);
    p["p_elfr40c_vs_eta_compare"].Add(hc_nc["h_elfr40c_vs_eta"], "no correction", kRed , 2, 22);
    p["p_elfr40c_vs_eta_compare"].SetYAxisRange(0, max);
    p["p_elfr40c_vs_eta_compare"].SetLegendOption("p");
    p["p_elfr40c_vs_eta_compare"].SetLegendTextSize(0.042);
    p["p_elfr40c_vs_eta_compare"].AddText("Electrons", 0.25, 0.835);

    // print
    if (suffix=="all")
    {
        rt::Print(p, path, "png");
        rt::Print(p, path, "pdf");
        rt::Print(p, path, "eps");
    }
    else if (!suffix.empty())
    {
        rt::Print(p, path, suffix);
    }
}


// Overlay Fake Rate comparision
// d0 cut study
//void FakeRateStudy(const std::string& suffix = "png")
//{
//    rt::TH1Container hc_data  ("data/fake_rates/ssFR_data_standard_16Dec2012.root");
//    rt::TH1Container hc_qcd   ("plots/fake_rates/qcd/ssFR_qcd_standard_qcd.root"  );
//    rt::TH1Container hc_dy    ("plots/fake_rates/qcd/ssFR_qcd_standard_qcd.root"  );
//    rt::TH1Container hc_wjets ("plots/fake_rates/qcd/ssFR_qcd_standard_qcd.root"  );
//
//	// set style
//	rt::SetTDRStyle();
//	gStyle->SetTitleBorderSize(0);
//    float max = 0.5;
//
//    map<string, TH1Overlay> p;
//    p["p_elfr40c_vs_pt_data"] = TH1Overlay("electron FR (away jet p_{T} > 40 GeV);p_{T} (GeV);TL ratio", "sb::off lg::top"); 
//
//    p["p_elfr40c_vs_pt_compare"] = TH1Overlay("electron FR (away jet p_{T} > 40 GeV);p_{T} (GeV);TL ratio", "sb::off lg::top"); 
//    p["p_elfr40c_vs_pt_compare"].Add(hc_ci["h_elfr40c_vs_pt"], "corrected"    , kBlue, 2, 20);
//    p["p_elfr40c_vs_pt_compare"].Add(hc_nc["h_elfr40c_vs_pt"], "no correction", kRed , 2, 22);
//    p["p_elfr40c_vs_pt_compare"].SetYAxisRange(0, max);
//    p["p_elfr40c_vs_pt_compare"].SetLegendOption("p");
//    p["p_elfr40c_vs_pt_compare"].SetLegendTextSize(0.042);
//    p["p_elfr40c_vs_pt_compare"].AddText("Electrons", 0.25, 0.835);
//
//    p["p_elfr40c_vs_nvtx_compare"] = TH1Overlay("electron FR (away jet p_{T} > 40 GeV);Number of Vertices;TL ratio", "sb::off lg::top"); 
//    p["p_elfr40c_vs_nvtx_compare"].Add(hc_ci["h_elfr40c_vs_nvtxs"], "corrected"    , kBlue, 2, 20);
//    p["p_elfr40c_vs_nvtx_compare"].Add(hc_nc["h_elfr40c_vs_nvtxs"], "no correction", kRed , 2, 22);
//    p["p_elfr40c_vs_nvtx_compare"].SetYAxisRange(0, max);
//    p["p_elfr40c_vs_nvtx_compare"].SetLegendOption("p");
//    p["p_elfr40c_vs_nvtx_compare"].SetLegendTextSize(0.042);
//    p["p_elfr40c_vs_nvtx_compare"].AddText("Electrons", 0.25, 0.835);
//
//    p["p_elfr40c_vs_eta_compare"] = TH1Overlay("electron FR (away jet p_{T} > 40 GeV);|#eta|;TL ratio", "sb::off lg::top"); 
//    p["p_elfr40c_vs_eta_compare"].Add(hc_ci["h_elfr40c_vs_eta"], "corrected"    , kBlue, 2, 20);
//    p["p_elfr40c_vs_eta_compare"].Add(hc_nc["h_elfr40c_vs_eta"], "no correction", kRed , 2, 22);
//    p["p_elfr40c_vs_eta_compare"].SetYAxisRange(0, max);
//    p["p_elfr40c_vs_eta_compare"].SetLegendOption("p");
//    p["p_elfr40c_vs_eta_compare"].SetLegendTextSize(0.042);
//    p["p_elfr40c_vs_eta_compare"].AddText("Electrons", 0.25, 0.835);
//
//    // print
//    string path = "plots/fake_rates/d0study";
//    rt::Print(p, path, suffix);
//}

void FakeRateD0Compare(const std::string& suffix = "png")
{
    rt::TH1Container hc_data ("data/fake_rates/ssFR_data_standard_29Jan2013.root"      );
    rt::TH1Container hc_d0cut("data/fake_rates/ssFR_data_standard_29Jan2013_d0cut.root");
    string path = "plots/fake_rates/compare_d0";

    // set style
    rt::SetTDRStyle();
    gStyle->SetTitleBorderSize(0);
    float max = 0.5;

    hc_data.SetMarkerSize(1.5);
    hc_d0cut.SetMarkerSize(1.5);

    map<string, TH1Overlay> p;

    // muons
    p["p_mufr40c_vs_pt_compare"] = TH1Overlay("Muon FR (away jet p_{T} > 40 GeV);p_{T} (GeV);TL ratio", "sb::off lg::top"); 
    p["p_mufr40c_vs_pt_compare"].Add(hc_data ["h_mufr40c_vs_pt"], "original"    , kBlue, 2, 20);
    p["p_mufr40c_vs_pt_compare"].Add(hc_d0cut["h_mufr40c_vs_pt"], "d0 < 50 #mum", kRed , 2, 22);
    p["p_mufr40c_vs_pt_compare"].SetYAxisRange(0, max);
    p["p_mufr40c_vs_pt_compare"].SetLegendOption("p");
    p["p_mufr40c_vs_pt_compare"].SetLegendTextSize(0.042);
    p["p_mufr40c_vs_pt_compare"].AddText("Muons", 0.25, 0.835);

    p["p_mufr40c_vs_nvtxs_compare"] = TH1Overlay("Muon FR (away jet p_{T} > 40 GeV);Number of Vertices;TL ratio", "sb::off lg::top"); 
    p["p_mufr40c_vs_nvtxs_compare"].Add(hc_data ["h_mufr40c_vs_nvtxs"], "original"    , kBlue, 2, 20);
    p["p_mufr40c_vs_nvtxs_compare"].Add(hc_d0cut["h_mufr40c_vs_nvtxs"], "d0 < 50 #mum", kRed , 2, 22);
    p["p_mufr40c_vs_nvtxs_compare"].SetYAxisRange(0, max);
    p["p_mufr40c_vs_nvtxs_compare"].SetLegendOption("p");
    p["p_mufr40c_vs_nvtxs_compare"].SetLegendTextSize(0.042);
    p["p_mufr40c_vs_nvtxs_compare"].AddText("Muons", 0.25, 0.835);

    p["p_mufr40c_vs_eta_compare"] = TH1Overlay("Muon FR (away jet p_{T} > 40 GeV);|#eta|;TL ratio", "sb::off lg::top"); 
    p["p_mufr40c_vs_eta_compare"].Add(hc_data ["h_mufr40c_vs_eta"], "original"    , kBlue, 2, 20);
    p["p_mufr40c_vs_eta_compare"].Add(hc_d0cut["h_mufr40c_vs_eta"], "d0 < 50 #mum", kRed , 2, 22);
    p["p_mufr40c_vs_eta_compare"].SetYAxisRange(0, max);
    p["p_mufr40c_vs_eta_compare"].SetLegendOption("p");
    p["p_mufr40c_vs_eta_compare"].SetLegendTextSize(0.042);
    p["p_mufr40c_vs_eta_compare"].AddText("Muons", 0.25, 0.835);

    // electrons
    p["p_elfr40c_vs_pt_compare"] = TH1Overlay("electron FR (away jet p_{T} > 40 GeV);p_{T} (GeV);TL ratio", "sb::off lg::top"); 
    p["p_elfr40c_vs_pt_compare"].Add(hc_data ["h_elfr40c_vs_pt"], "original"     , kBlue, 2, 20);
    p["p_elfr40c_vs_pt_compare"].Add(hc_d0cut["h_elfr40c_vs_pt"], "d0 < 100 #mum", kRed , 2, 22);
    p["p_elfr40c_vs_pt_compare"].SetYAxisRange(0, max);
    p["p_elfr40c_vs_pt_compare"].SetLegendOption("p");
    p["p_elfr40c_vs_pt_compare"].SetLegendTextSize(0.042);
    p["p_elfr40c_vs_pt_compare"].AddText("Electrons", 0.25, 0.835);

    p["p_elfr40c_vs_nvtxs_compare"] = TH1Overlay("electron FR (away jet p_{T} > 40 GeV);Number of Vertices;TL ratio", "sb::off lg::top"); 
    p["p_elfr40c_vs_nvtxs_compare"].Add(hc_data ["h_elfr40c_vs_nvtxs"], "original"     , kBlue, 2, 20);
    p["p_elfr40c_vs_nvtxs_compare"].Add(hc_d0cut["h_elfr40c_vs_nvtxs"], "d0 < 100 #mum", kRed , 2, 22);
    p["p_elfr40c_vs_nvtxs_compare"].SetYAxisRange(0, max);
    p["p_elfr40c_vs_nvtxs_compare"].SetLegendOption("p");
    p["p_elfr40c_vs_nvtxs_compare"].SetLegendTextSize(0.042);
    p["p_elfr40c_vs_nvtxs_compare"].AddText("Electrons", 0.25, 0.835);

    p["p_elfr40c_vs_eta_compare"] = TH1Overlay("electron FR (away jet p_{T} > 40 GeV);|#eta|;TL ratio", "sb::off lg::top"); 
    p["p_elfr40c_vs_eta_compare"].Add(hc_data ["h_elfr40c_vs_eta"], "original"     , kBlue, 2, 20);
    p["p_elfr40c_vs_eta_compare"].Add(hc_d0cut["h_elfr40c_vs_eta"], "d0 < 100 #mum", kRed , 2, 22);
    p["p_elfr40c_vs_eta_compare"].SetYAxisRange(0, max);
    p["p_elfr40c_vs_eta_compare"].SetLegendOption("p");
    p["p_elfr40c_vs_eta_compare"].SetLegendTextSize(0.042);
    p["p_elfr40c_vs_eta_compare"].AddText("Electrons", 0.25, 0.835);

    // print
    rt::Print(p, path, suffix);
}


void FakeRateNewEffArea(const std::string& suffix = "png")
{
    rt::TH1Container hc_data("data/fake_rates/ssFR_data_standard_16Dec2012.root");
    rt::TH1Container hc_aeff("data/fake_rates/ssFR_data_standard_29Jan2013.root");
    string path = "plots/fake_rates/compare_aeff";

    // set style
    rt::SetTDRStyle();
    gStyle->SetTitleBorderSize(0);
    float max = 0.5;

    hc_data.SetMarkerSize(1.8);
    hc_aeff.SetMarkerSize(1.8);

    map<string, TH1Overlay> p;

    // electrons
    p["p_elfr40c_vs_pt_compare"] = TH1Overlay("electron FR (away jet p_{T} > 40 GeV);p_{T} (GeV);TL ratio", "sb::off lg::top"); 
    p["p_elfr40c_vs_pt_compare"].Add(hc_data["h_elfr40c_vs_pt"], "original"    , kBlue, 2, 20);
    p["p_elfr40c_vs_pt_compare"].Add(hc_aeff["h_elfr40c_vs_pt"], "new A_{eff}", kRed , 2, 22);
    p["p_elfr40c_vs_pt_compare"].SetYAxisRange(0, max);
    p["p_elfr40c_vs_pt_compare"].SetLegendOption("p");
    p["p_elfr40c_vs_pt_compare"].SetLegendTextSize(0.042);
    p["p_elfr40c_vs_pt_compare"].AddText("Electrons", 0.25, 0.835);

    p["p_elfr40c_vs_nvtxs_compare"] = TH1Overlay("electron FR (away jet p_{T} > 40 GeV);Number of Vertices;TL ratio", "sb::off lg::top"); 
    p["p_elfr40c_vs_nvtxs_compare"].Add(hc_data["h_elfr40c_vs_nvtxs"], "original"   , kBlue, 2, 20);
    p["p_elfr40c_vs_nvtxs_compare"].Add(hc_aeff["h_elfr40c_vs_nvtxs"], "new A_{eff}", kRed , 2, 22);
    p["p_elfr40c_vs_nvtxs_compare"].SetYAxisRange(0, max);
    p["p_elfr40c_vs_nvtxs_compare"].SetLegendOption("p");
    p["p_elfr40c_vs_nvtxs_compare"].SetLegendTextSize(0.042);
    p["p_elfr40c_vs_nvtxs_compare"].AddText("Electrons", 0.25, 0.835);

    p["p_elfr40c_vs_eta_compare"] = TH1Overlay("electron FR (away jet p_{T} > 40 GeV);|#eta|;TL ratio", "sb::off lg::top"); 
    p["p_elfr40c_vs_eta_compare"].Add(hc_data["h_elfr40c_vs_eta"], "original"   , kBlue, 2, 20);
    p["p_elfr40c_vs_eta_compare"].Add(hc_aeff["h_elfr40c_vs_eta"], "new A_{eff}", kRed , 2, 22);
    p["p_elfr40c_vs_eta_compare"].SetYAxisRange(0, max);
    p["p_elfr40c_vs_eta_compare"].SetLegendOption("p");
    p["p_elfr40c_vs_eta_compare"].SetLegendTextSize(0.042);
    p["p_elfr40c_vs_eta_compare"].AddText("Electrons", 0.25, 0.835);

    // print
    rt::Print(p, path, suffix);
}


void FakeRateTruncIso(const std::string& suffix = "png")
{
    rt::TH1Container hc_data("data/fake_rates/ssFR_data_standard_29Jan2013_d0cut.root");
    rt::TH1Container hc_trun("data/fake_rates/ssFR_data_standard_29Jan2013_trunc.root");
    //rt::TH1Container hc_trun("data/fake_rates/ssFR_data_standard_16Dec2012.root");
    string path = "plots/fake_rates/compare_trunc";

    // set style
    rt::SetTDRStyle();
    gStyle->SetTitleBorderSize(0);
    float max = 0.5;

    hc_data.SetMarkerSize(1.5);
    hc_trun.SetMarkerSize(1.5);

    map<string, TH1Overlay> p;

    // muons
    p["p_mufr40c_vs_pt_compare"] = TH1Overlay("Muon FR (away jet p_{T} > 40 GeV);p_{T} (GeV);TL ratio", "sb::off lg::top"); 
    p["p_mufr40c_vs_pt_compare"].Add(hc_data["h_mufr40c_vs_pt"], "original iso" , kBlue, 2, 20);
    p["p_mufr40c_vs_pt_compare"].Add(hc_trun["h_mufr40c_vs_pt"], "truncated iso", kRed , 2, 22);
    p["p_mufr40c_vs_pt_compare"].SetYAxisRange(0, max);
    p["p_mufr40c_vs_pt_compare"].SetLegendOption("p");
    p["p_mufr40c_vs_pt_compare"].SetLegendTextSize(0.042);
    p["p_mufr40c_vs_pt_compare"].AddText("Muons", 0.25, 0.835);

    p["p_mufr40c_vs_nvtxs_compare"] = TH1Overlay("Muon FR (away jet p_{T} > 40 GeV);Number of Vertices;TL ratio", "sb::off lg::top"); 
    p["p_mufr40c_vs_nvtxs_compare"].Add(hc_data["h_mufr40c_vs_nvtxs"], "original iso" , kBlue, 2, 20);
    p["p_mufr40c_vs_nvtxs_compare"].Add(hc_trun["h_mufr40c_vs_nvtxs"], "truncated iso", kRed , 2, 22);
    p["p_mufr40c_vs_nvtxs_compare"].SetYAxisRange(0, max);
    p["p_mufr40c_vs_nvtxs_compare"].SetLegendOption("p");
    p["p_mufr40c_vs_nvtxs_compare"].SetLegendTextSize(0.042);
    p["p_mufr40c_vs_nvtxs_compare"].AddText("Muons", 0.25, 0.835);

    p["p_mufr40c_vs_eta_compare"] = TH1Overlay("Muon FR (away jet p_{T} > 40 GeV);|#eta|;TL ratio", "sb::off lg::top"); 
    p["p_mufr40c_vs_eta_compare"].Add(hc_data["h_mufr40c_vs_eta"], "original iso" , kBlue, 2, 20);
    p["p_mufr40c_vs_eta_compare"].Add(hc_trun["h_mufr40c_vs_eta"], "truncated iso", kRed , 2, 22);
    p["p_mufr40c_vs_eta_compare"].SetYAxisRange(0, max);
    p["p_mufr40c_vs_eta_compare"].SetLegendOption("p");
    p["p_mufr40c_vs_eta_compare"].SetLegendTextSize(0.042);
    p["p_mufr40c_vs_eta_compare"].AddText("Muons", 0.25, 0.835);

    // electrons
    p["p_elfr40c_vs_pt_compare"] = TH1Overlay("electron FR (away jet p_{T} > 40 GeV);p_{T} (GeV);TL ratio", "sb::off lg::top"); 
    p["p_elfr40c_vs_pt_compare"].Add(hc_data["h_elfr40c_vs_pt"], "original iso" , kBlue, 2, 20);
    p["p_elfr40c_vs_pt_compare"].Add(hc_trun["h_elfr40c_vs_pt"], "truncated iso", kRed , 2, 22);
    p["p_elfr40c_vs_pt_compare"].SetYAxisRange(0, max);
    p["p_elfr40c_vs_pt_compare"].SetLegendOption("p");
    p["p_elfr40c_vs_pt_compare"].SetLegendTextSize(0.042);
    p["p_elfr40c_vs_pt_compare"].AddText("Electrons", 0.25, 0.835);

    p["p_elfr40c_vs_nvtxs_compare"] = TH1Overlay("electron FR (away jet p_{T} > 40 GeV);Number of Vertices;TL ratio", "sb::off lg::top"); 
    p["p_elfr40c_vs_nvtxs_compare"].Add(hc_data["h_elfr40c_vs_nvtxs"], "original iso" , kBlue, 2, 20);
    p["p_elfr40c_vs_nvtxs_compare"].Add(hc_trun["h_elfr40c_vs_nvtxs"], "truncated iso", kRed , 2, 22);
    p["p_elfr40c_vs_nvtxs_compare"].SetYAxisRange(0, max);
    p["p_elfr40c_vs_nvtxs_compare"].SetLegendOption("p");
    p["p_elfr40c_vs_nvtxs_compare"].SetLegendTextSize(0.042);
    p["p_elfr40c_vs_nvtxs_compare"].AddText("Electrons", 0.25, 0.835);

    p["p_elfr40c_vs_eta_compare"] = TH1Overlay("electron FR (away jet p_{T} > 40 GeV);|#eta|;TL ratio", "sb::off lg::top"); 
    p["p_elfr40c_vs_eta_compare"].Add(hc_data["h_elfr40c_vs_eta"], "original iso" , kBlue, 2, 20);
    p["p_elfr40c_vs_eta_compare"].Add(hc_trun["h_elfr40c_vs_eta"], "truncated iso", kRed , 2, 22);
    p["p_elfr40c_vs_eta_compare"].SetYAxisRange(0, max);
    p["p_elfr40c_vs_eta_compare"].SetLegendOption("p");
    p["p_elfr40c_vs_eta_compare"].SetLegendTextSize(0.042);
    p["p_elfr40c_vs_eta_compare"].AddText("Electrons", 0.25, 0.835);

    // print
    rt::Print(p, path, suffix);
}


void EffAreaPlot(const std::string& suffix = "eps")
{
    
    // get effective area
    ///if      (etaAbs <= 1.0                  ) {return 0.10; }
    ///else if (etaAbs > 1.0 && etaAbs <= 1.479) {return 0.12; }
    ///else if (etaAbs > 1.479 && etaAbs <= 2.0) {return 0.085;}
    ///else if (etaAbs > 2.0 && etaAbs <= 2.2  ) {return 0.11; }
    ///else if (etaAbs > 2.2 && etaAbs <= 2.3  ) {return 0.12; }
    ///else if (etaAbs > 2.3 && etaAbs <= 2.4  ) {return 0.12; }
    ///else if (etaAbs > 2.4                   ) {return 0.13; }

    ///// get effective area
    ///if      (etaAbs <= 1.0                  ) {return 0.13;}
    ///else if (etaAbs > 1.0 && etaAbs <= 1.479) {return 0.14;}
    ///else if (etaAbs > 1.479 && etaAbs <= 2.0) {return 0.07;}
    ///else if (etaAbs > 2.0 && etaAbs <= 2.2  ) {return 0.09;}
    ///else if (etaAbs > 2.2 && etaAbs <= 2.3  ) {return 0.11;}
    ///else if (etaAbs > 2.3 && etaAbs <= 2.4  ) {return 0.11;}
    ///else if (etaAbs > 2.4                   ) {return 0.14;}

    const float bins[] = {0.0, 1.0, 1.479, 2.0, 2.2, 2.3, 2.4, 2.5};
    const short nbins  = 7; 

    TH1F h_old_aeff("h_old_aedd", "old A_{eff};|#eta|", nbins, bins);
    h_old_aeff.SetBinContent(1, 0.10 ); h_old_aeff.SetBinError(1, 0.001);
    h_old_aeff.SetBinContent(2, 0.12 ); h_old_aeff.SetBinError(2, 0.002);
    h_old_aeff.SetBinContent(3, 0.085); h_old_aeff.SetBinError(3, 0.001);
    h_old_aeff.SetBinContent(4, 0.11 ); h_old_aeff.SetBinError(4, 0.001);
    h_old_aeff.SetBinContent(5, 0.12 ); h_old_aeff.SetBinError(5, 0.002);
    h_old_aeff.SetBinContent(6, 0.12 ); h_old_aeff.SetBinError(6, 0.003);
    h_old_aeff.SetBinContent(7, 0.13 ); h_old_aeff.SetBinError(7, 0.004);

    TH1F h_new_aeff("h_new_aedd", "new A_{eff};|#eta|", nbins, bins);
    h_new_aeff.SetBinContent(1, 0.13); h_new_aeff.SetBinError(1, 0.001);
    h_new_aeff.SetBinContent(2, 0.14); h_new_aeff.SetBinError(2, 0.002);
    h_new_aeff.SetBinContent(3, 0.07); h_new_aeff.SetBinError(3, 0.001);
    h_new_aeff.SetBinContent(4, 0.09); h_new_aeff.SetBinError(4, 0.001);
    h_new_aeff.SetBinContent(5, 0.11); h_new_aeff.SetBinError(5, 0.002);
    h_new_aeff.SetBinContent(6, 0.11); h_new_aeff.SetBinError(6, 0.003);
    h_new_aeff.SetBinContent(7, 0.14); h_new_aeff.SetBinError(7, 0.004);
    
    TH1Overlay p("electron A_{eff};|#eta|", "sb::off lg::top"); 
    p.Add(&h_old_aeff, "old", kBlue, 2, 20);
    p.Add(&h_new_aeff, "new", kRed , 2, 22);
    p.SetYAxisRange(0, 0.2);
    p.SetLegendOption("p");
    p.SetLegendTextSize(0.042);

    // print
    rt::Print(p, "plots/effective_area", suffix);
}

void IsoComparePlot(const std::string& suffix = "eps")
{
    rt::TH1Container hc_old("plots/fake_rates/iso_old.root");
    rt::TH1Container hc_new("plots/fake_rates/iso_new.root");
    string path = "plots/fake_rates/compare_iso";

    // set style
    rt::SetTDRStyle();
    gStyle->SetTitleBorderSize(0);

    hc_old.SetMarkerSize(1.5);
    hc_new.SetMarkerSize(1.5);

    TH1Overlay p("electron corrected iso;iso", "sb::off lg::top dt::norm logy"); 
    p.Add(hc_old["h_iso_old"], "old A_{eff}", kBlue, 2, 20);
    p.Add(hc_new["h_iso_new"], "new A_{eff}", kRed , 2, 22);
    p.SetYAxisRange(0.001, 1.0);
    p.SetLegendOption("p");
    p.SetLegendTextSize(0.042);

    // print
    rt::Print(p, "plots/fake_rates/compare_iso/iso_aeff_compare", suffix);
}

void EwkPlots()
{
    rt::TH1Container hc_data ("plots/fake_rates/iso_old.root");
    rt::TH1Container hc_dy   ("plots/fake_rates/iso_new.root");
    rt::TH1Container hc_wjets("plots/fake_rates/iso_new.root");
    string path = "plots/fake_rates/compare_iso";
}

void FakeRateEWK(const std::string& suffix = "png")
{
    rt::TH1Container hc("data/fake_rates/ssFR_data_ewkcor_13Feb2013.root");
    string path = "plots/fake_rates/compare_ewkcor";
    //hc.List();

    // set style
    rt::SetTDRStyle();
    hc.SetMarkerSize(1.5);
    gStyle->SetTitleBorderSize(0);
    float max = 0.5;

    map<string, TH1Overlay> p;

    // muons
    p["p_mufr40c_vs_pt_compare_ewkcor"] = TH1Overlay("Muon FR (away jet p_{T} > 40 GeV);p_{T} (GeV);TL ratio", "sb::off lg::top"); 
    p["p_mufr40c_vs_pt_compare_ewkcor"].Add(hc["h_mufr40c_vs_pt"       ], "uncorrected"  , kBlue, 2, 20);
    p["p_mufr40c_vs_pt_compare_ewkcor"].Add(hc["h_mufr40c_vs_pt_ewkcor"], "ewk corrected", kRed , 2, 22);
    p["p_mufr40c_vs_pt_compare_ewkcor"].SetYAxisRange(0, max);
    p["p_mufr40c_vs_pt_compare_ewkcor"].SetLegendOption("p");
    p["p_mufr40c_vs_pt_compare_ewkcor"].SetLegendTextSize(0.042);
    p["p_mufr40c_vs_pt_compare_ewkcor"].AddText("Muons", 0.25, 0.835);

    //p["p_mufr40c_vs_nvtxs_compare_ewkcor"] = TH1Overlay("Muon FR (away jet p_{T} > 40 GeV);Number of Vertices;TL ratio", "sb::off lg::top"); 
    //p["p_mufr40c_vs_nvtxs_compare_ewkcor"].Add(hc["h_mufr40c_vs_nvtxs"       ], "uncorrected"  , kBlue, 2, 20);
    //p["p_mufr40c_vs_nvtxs_compare_ewkcor"].Add(hc["h_mufr40c_vs_nvtxs_ewkcor"], "ewk corrected", kRed , 2, 22);
    //p["p_mufr40c_vs_nvtxs_compare_ewkcor"].SetYAxisRange(0, max);
    //p["p_mufr40c_vs_nvtxs_compare_ewkcor"].SetLegendOption("p");
    //p["p_mufr40c_vs_nvtxs_compare_ewkcor"].SetLegendTextSize(0.042);
    //p["p_mufr40c_vs_nvtxs_compare_ewkcor"].AddText("Muons", 0.25, 0.835);

    p["p_mufr40c_vs_eta_compare_ewkcor"] = TH1Overlay("Muon FR (away jet p_{T} > 40 GeV);|#eta|;TL ratio", "sb::off lg::top"); 
    p["p_mufr40c_vs_eta_compare_ewkcor"].Add(hc["h_mufr40c_vs_eta"       ], "uncorrected"  , kBlue, 2, 20);
    p["p_mufr40c_vs_eta_compare_ewkcor"].Add(hc["h_mufr40c_vs_eta_ewkcor"], "ewk corrected", kRed , 2, 22);
    p["p_mufr40c_vs_eta_compare_ewkcor"].SetYAxisRange(0, max);
    p["p_mufr40c_vs_eta_compare_ewkcor"].SetLegendOption("p");
    p["p_mufr40c_vs_eta_compare_ewkcor"].SetLegendTextSize(0.042);
    p["p_mufr40c_vs_eta_compare_ewkcor"].AddText("Muons", 0.25, 0.835);

    // electrons
    p["p_elfr40c_vs_pt_compare_ewkcor"] = TH1Overlay("electron FR (away jet p_{T} > 40 GeV);p_{T} (GeV);TL ratio", "sb::off lg::top"); 
    p["p_elfr40c_vs_pt_compare_ewkcor"].Add(hc["h_elfr40c_vs_pt"       ], "uncorrected"  , kBlue, 2, 20);
    p["p_elfr40c_vs_pt_compare_ewkcor"].Add(hc["h_elfr40c_vs_pt_ewkcor"], "ewk corrected", kRed , 2, 22);
    p["p_elfr40c_vs_pt_compare_ewkcor"].SetYAxisRange(0, max);
    p["p_elfr40c_vs_pt_compare_ewkcor"].SetLegendOption("p");
    p["p_elfr40c_vs_pt_compare_ewkcor"].SetLegendTextSize(0.042);
    p["p_elfr40c_vs_pt_compare_ewkcor"].AddText("Electrons", 0.25, 0.835);

    //p["p_elfr40c_vs_nvtxs_compare_ewkcor"] = TH1Overlay("electron FR (away jet p_{T} > 40 GeV);Number of Vertices;TL ratio", "sb::off lg::top"); 
    //p["p_elfr40c_vs_nvtxs_compare_ewkcor"].Add(hc["h_elfr40c_vs_nvtxs"       ], "uncorrected"  , kBlue, 2, 20);
    //p["p_elfr40c_vs_nvtxs_compare_ewkcor"].Add(hc["h_elfr40c_vs_nvtxs_ewkcor"], "ewk corrected", kRed , 2, 22);
    //p["p_elfr40c_vs_nvtxs_compare_ewkcor"].SetYAxisRange(0, max);
    //p["p_elfr40c_vs_nvtxs_compare_ewkcor"].SetLegendOption("p");
    //p["p_elfr40c_vs_nvtxs_compare_ewkcor"].SetLegendTextSize(0.042);
    //p["p_elfr40c_vs_nvtxs_compare_ewkcor"].AddText("Electrons", 0.25, 0.835);

    p["p_elfr40c_vs_eta_compare_ewkcor"] = TH1Overlay("electron FR (away jet p_{T} > 40 GeV);|#eta|;TL ratio", "sb::off lg::top"); 
    p["p_elfr40c_vs_eta_compare_ewkcor"].Add(hc["h_elfr40c_vs_eta"       ], "uncorrected"  , kBlue, 2, 20);
    p["p_elfr40c_vs_eta_compare_ewkcor"].Add(hc["h_elfr40c_vs_eta_ewkcor"], "ewk corrected", kRed , 2, 22);
    p["p_elfr40c_vs_eta_compare_ewkcor"].SetYAxisRange(0, max);
    p["p_elfr40c_vs_eta_compare_ewkcor"].SetLegendOption("p");
    p["p_elfr40c_vs_eta_compare_ewkcor"].SetLegendTextSize(0.042);
    p["p_elfr40c_vs_eta_compare_ewkcor"].AddText("Electrons", 0.25, 0.835);

    // print
    rt::Print(p, path, suffix);
}


