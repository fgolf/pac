#include <vector>
#include <string>
#include "rt/RootTools.h"
#include "TColor.h"
#include "CTable.h"
#include "TStyle.h"

using namespace rt;
using namespace std;

struct sample_t
{
    sample_t(const string& n, const string& t, Color_t c, Style_t m) : name(n), title(t), color(c), marker(m), yield(0) {}
    string name;
    string title;
    Color_t color;
    Style_t marker;
    float yield;
};

void OverlayPlots(bool sbottom = false, float scale = 1.0, int signal_region = 0, const std::string& out_path = "", const std::string& suffix = "png")
{
    // samples to overlay
    std::vector<sample_t> samples;
    //samples.push_back(sample_t("t1tttt_mglu1100_mlsp100", "T1tttt (m_{glu} = 1100, m_{LSP} = 100)", kBlack    )); 
    //samples.push_back(sample_t("t1tttt_mglu600_mlsp100" , "T1tttt (m_{glu} = 600, m_{LSP} = 100)" , kRed      )); 
    //samples.push_back(sample_t("t1tttt_mglu600_mlsp0"   , "T1tttt (600, 0)" , kRed      , 22)); 
    //samples.push_back(sample_t("t1tttt_mglu1100_mlsp0"  , "T1tttt (1100, 0)"  , kBlack    , 20)); 
    //samples.push_back(sample_t("t1tttt_mglu1100_mlsp600", "T1tttt (1100, 600)", kRed      , 22)); 
	if (sbottom)
	{
		samples.push_back(sample_t("sbottomtop_msb460_mlsp140" , "#tilde{b}t (460, 140)", kBlack, 20)); 
		samples.push_back(sample_t("sbottomtop_msb380_mlsp140" , "#tilde{b}t (380, 140)", kRed  , 22)); 
	}
	else
	{
		samples.push_back(sample_t("t1tttt_mglu900_mlsp550"    , "T1tttt (900, 550)"    , kBlack, 20)); 
		samples.push_back(sample_t("t1tttt_mglu950_mlsp50"     , "T1tttt (950, 50)"     , kRed  , 22)); 
	}
    samples.push_back(sample_t("ttw"                       , "t#bar{t}W"            , kBlue-7   ,  0));
    samples.push_back(sample_t("ttz"                       , "t#bar{t}Z"            , kGreen+2  ,  0));
    samples.push_back(sample_t("ttjets"                    , "t#bar{t}+jets"        , kYellow-7 ,  0));
    samples.push_back(sample_t("wz"                        , "WZ"                   , kCyan-5   ,  0));
    samples.push_back(sample_t("zz"                        , "ZZ"                   , kOrange-3 ,  0));

    // hists
    gStyle->SetOptStat("i");
    vector<TH1Container> hcs;
    string sr = Form("sr%d", signal_region);
	string postfix = Form("%s_%s", sbottom ? "sb" : "t1tttt", sr.c_str());
    for (size_t i = 0; i != samples.size(); i++)
    {
        hcs.push_back(TH1Container(Form("plots/%s/%s/%s.root", out_path.c_str(), sr.c_str(), samples[i].name.c_str())));
        //hcs[i].Scale(scale);
    }

    // overlay
    map<string, TH1Overlay> p;
    p["p_pt1_"   +postfix] = TH1Overlay("higher p_{T} lepton;p_{T}^{lep1} (GeV)", "sb::off lg::top_right dt::stack");
    p["p_pt2_"   +postfix] = TH1Overlay("lower p_{T} lepton;p_{T}^{lep2} (GeV)" , "sb::off lg::top_right dt::stack");
    p["p_mt_"    +postfix] = TH1Overlay("m_{T};m_{T} (GeV)"                     , "sb::off lg::top_right dt::stack");
    p["p_ht_"    +postfix] = TH1Overlay("H_{T};H_{T} (GeV)"                     , "sb::off lg::top_right dt::stack");
    p["p_met_"   +postfix] = TH1Overlay("E_{T}^{miss};E_{T}^{miss} (GeV)"       , "sb::off lg::top_right dt::stack");
    p["p_njets_" +postfix] = TH1Overlay("# jets;# jets"                         , "sb::off lg::top_right dt::stack");
    p["p_nbtags_"+postfix] = TH1Overlay("# btags;# btags"                       , "sb::off lg::top_right dt::stack");

    float bkgd_yield = 0;
    for (size_t i = 0; i != hcs.size(); i++)
    {
        TH1Container& hc = hcs.at(i);
        string& name     = samples[i].name;
        string& title    = samples[i].title;
        Color_t& color   = samples[i].color;
        Style_t& marker  = samples[i].marker;
        bool signal      = string_contains(name, "t1tttt") || string_contains(name, "sbottom");
        samples[i].yield = rt::Integral(hc["h_pt1_ss"]);
        if (!signal)
        {
            bkgd_yield      += samples[i].yield;
        }

        // pt1
        p["p_pt1_"   +postfix].Add(hc["h_pt1_ss"   ], signal, title, color, 2, marker);
        p["p_pt2_"   +postfix].Add(hc["h_pt2_ss"   ], signal, title, color, 2, marker);
        p["p_mt_"    +postfix].Add(hc["h_mt_ss"    ], signal, title, color, 2, marker);
        p["p_ht_"    +postfix].Add(hc["h_ht_ss"    ], signal, title, color, 2, marker);
        p["p_met_"   +postfix].Add(hc["h_met_ss"   ], signal, title, color, 2, marker);
        p["p_njets_" +postfix].Add(hc["h_njets_ss" ], signal, title, color, 2, marker);
        p["p_nbtags_"+postfix].Add(hc["h_nbtags_ss"], signal, title, color, 2, marker);
    }

    // simple figure of merit
    float fom1 = samples[0].yield / (bkgd_yield); 
    float fom2 = samples[1].yield / (bkgd_yield); 

    // print yields
    CTable t_yields;
    t_yields.useTitle();
    t_yields.setTitle(Form("yields scaled to %2.0f /fb", scale));
    t_yields.setColLabel("yield", 0);
    for (size_t i = 0; i != samples.size(); i++)
    {
        t_yields.setRowLabel(samples[i].name , i);
        t_yields.setCell(Form("%1.1f", samples[i].yield), i, 0);
    }
    t_yields.setRowLabel("total bkgd",samples.size());
    t_yields.setCell(Form("%1.1f", bkgd_yield), samples.size(), 0);
    t_yields.setRowLabel(Form("Signal/Background (%s)", samples[0].name.c_str()), samples.size()+1);
    t_yields.setCell(Form("%1.2f", fom1), samples.size()+1, 0);
    t_yields.setRowLabel(Form("Signal/Background (%s)", samples[1].name.c_str()), samples.size()+2);
    t_yields.setCell(Form("%1.2f", fom2), samples.size()+2, 0);
    t_yields.print();

    // write
    Print(p, Form("plots/overlays/%s/sr%d", out_path.c_str(), signal_region), suffix);
}
