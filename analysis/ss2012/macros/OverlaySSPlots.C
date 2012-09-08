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

void OverlaySSPlots(float lumi = 1.0, unsigned int signal_region_num = 0, const std::string& path = "", const std::string& suffix = "png")
{
    // get the datasets
    // samples to overlay
    //std::vector<sample_t> samples;
    //samples.push_back(sample_t("data" , "data"           ));
    //samples.push_back(sample_t("wz"   , "WZ"             ));
    //samples.push_back(sample_t("zz"   , "ZZ"             ));
    //samples.push_back(sample_t("ttg"  , "t#bar{t}#gamma" ));
    //samples.push_back(sample_t("ttw"  , "t#bar{t}W"      ));
    //samples.push_back(sample_t("ttww" , "t#bar{t}WW"     ));
    //samples.push_back(sample_t("ttz"  , "t#bar{t}Z"      ));
    //samples.push_back(sample_t("wwg"  , "WW#gamma"       ));
    //samples.push_back(sample_t("www"  , "www"            ));
    //samples.push_back(sample_t("wwz"  , "wwz"            ));
    //samples.push_back(sample_t("wzz"  , "wzz"            ));
    //samples.push_back(sample_t("wzz"  , "wzz"            ));

    ss::SignalRegionInfo sr = ss::GetSignalRegionInfo(signal_region_num);

    rt::TH1Container hc_data(Form("plots/%s/%s/data.root", path.c_str(), sr.name.c_str()));
    rt::TH1Container hc_mc;
    hc_mc += rt::TH1Container(Form("plots/%s/%s/wz.root" , path.c_str(), sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/zz.root" , path.c_str(), sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/ttw.root", path.c_str(), sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/ttz.root", path.c_str(), sr.name.c_str()));

    map<string, rt::TH1Overlay> p;
    rt::TH1Overlay::profile_marker_size_default = 10.0;

	// set style
	rt::SetTDRStyle();
	gStyle->SetTitleBorderSize(0);

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
    p["p_pt1"] = rt::TH1Overlay(Form("%s;p^{lep1}_{T} (GeV);Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_pt1"].Add(hc_data["h_pt1_ss"  ], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_pt1"].Add(hc_data["h_pt1_os"  ], "flips", flip_color);
    p["p_pt1"].Add(hc_data["h_pt1_fake"], "fakes", fake_color);
    p["p_pt1"].Add(hc_mc  ["h_pt1_ss"  ], "MC", mc_color);
    p["p_pt1"].AddText(t1);

    p["p_pt2"] = rt::TH1Overlay(Form("%s;p^{lep2}_{T} (GeV);Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_pt2"].Add(hc_data["h_pt2_ss"  ], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_pt2"].Add(hc_data["h_pt2_os"  ], "flips", flip_color);
    p["p_pt2"].Add(hc_data["h_pt2_fake"], "fakes", fake_color);
    p["p_pt2"].Add(hc_mc  ["h_pt2_ss"  ], "MC", mc_color);
    p["p_pt2"].AddText(t1);

    p["p_met"] = rt::TH1Overlay(Form("%s;E^{miss}_{T} (GeV);Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_met"].Add(hc_data["h_met_ss"  ], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_met"].Add(hc_data["h_met_os"  ], "flips", flip_color);
    p["p_met"].Add(hc_data["h_met_fake"], "fakes", fake_color);
    p["p_met"].Add(hc_mc  ["h_met_ss"  ], "MC", mc_color);
    p["p_met"].AddText(t1);

    p["p_ht"] = rt::TH1Overlay(Form("%s;H_{T} (GeV);Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_ht"].Add(hc_data["h_ht_ss"  ], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_ht"].Add(hc_data["h_ht_os"  ], "flips", flip_color);
    p["p_ht"].Add(hc_data["h_ht_fake"], "fakes", fake_color);
    p["p_ht"].Add(hc_mc  ["h_ht_ss"  ], "MC", mc_color);
    p["p_ht"].AddText(t1);

    t1.SetX(0.65); t1.SetY(0.6);
    p["p_nbtags"] = rt::TH1Overlay(Form("%s;# btags;Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_nbtags"].Add(hc_data["h_nbtags_ss"  ], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_nbtags"].Add(hc_data["h_nbtags_os"  ], "flips", flip_color);
    p["p_nbtags"].Add(hc_data["h_nbtags_fake"], "fakes", fake_color);
    p["p_nbtags"].Add(hc_mc  ["h_nbtags_ss"  ], "MC", mc_color);
    p["p_nbtags"].AddText(t1);

    t1.SetX(0.65); t1.SetY(0.6);
    p["p_njets"] = rt::TH1Overlay(Form("%s;# jets;Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_njets"].Add(hc_data["h_njets_ss"  ], /*is_data=*/true, "data", data_color, 2, 20);
    p["p_njets"].Add(hc_data["h_njets_os"  ], "flips", flip_color);
    p["p_njets"].Add(hc_data["h_njets_fake"], "fakes", fake_color);
    p["p_njets"].Add(hc_mc  ["h_njets_ss"  ], "MC", mc_color);
    p["p_njets"].AddText(t1);

    // write
    rt::Print(p, Form("plots/%s/%s/kin", path.c_str(), sr.name.c_str()), suffix);
}
