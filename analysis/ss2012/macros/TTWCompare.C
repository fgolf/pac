#include <vector>
//#include <tr1/array>
#include <string>
#include "rt/RootTools.h"
#include "TColor.h"
#include "CTable.h"
#include "TStyle.h"

using namespace rt;
using namespace std;

struct sample_t
{
    sample_t(const string& n, const string& t, Color_t c, Style_t m) 
        : name(n)
        , title(t)
        , color(c)
        , marker(m)
        , yield(0)
        , error(0) 
    {}
    string name;
    string title;
    Color_t color;
    Style_t marker;
    float yield;
    float error;
};

void TTWCompare(float scale = 1.0, int signal_region = 0, const std::string& suffix = "png")
{
    // samples to overlay
    vector<sample_t> samples; 
    samples.push_back(sample_t("ttw"         , "52X"                 , kBlue   , 20));
    samples.push_back(sample_t("ttw_53X"     , "53X"                 , kRed    , 22));
    //samples.push_back(sample_t("ttw_53X_vtxw", "53X (vtx reweighted)", kGreen+2, 24));

    // hists
    //gStyle->SetOptStat("i");
    vector<TH1Container> hcs;
    for (size_t i = 0; i != samples.size(); i++)
    {
        hcs.push_back(TH1Container(Form("plots/sr%u/%s.root", signal_region, samples[i].name.c_str())));
        hcs[i].Scale(scale);
    }
    //vector<TH1Container> hcs_nosio;
    //for (size_t i = 0; i != samples.size(); i++)
    //{
    //    hcs.push_back(TH1Container(Form("plots/sr%u/%s_noiso.root", signal_region, samples[i].name.c_str())));
    //    hcs[i].Scale(scale);
    //}

    // overlay
    map<string, TH1Overlay> p;
    p["p_nvtxs"  ] = TH1Overlay("", "dt::norm sb::off lg::top_right");
    p["p_pt1"    ] = TH1Overlay("", "dt::norm sb::off lg::top_right");
    p["p_pt2"    ] = TH1Overlay("", "dt::norm sb::off lg::top_right");
    p["p_eta1"   ] = TH1Overlay("", "dt::norm sb::off lg::top_right");
    p["p_eta2"   ] = TH1Overlay("", "dt::norm sb::off lg::top_right");
    p["p_phi1"   ] = TH1Overlay("", "dt::norm sb::off lg::bottom"   );
    p["p_phi2"   ] = TH1Overlay("", "dt::norm sb::off lg::bottom"   );
    p["p_d01"    ] = TH1Overlay("", "dt::norm sb::off lg::top_right logy");
    p["p_d02"    ] = TH1Overlay("", "dt::norm sb::off lg::top_right logy");
    p["p_dz1"    ] = TH1Overlay("", "dt::norm sb::off lg::top_right logy");
    p["p_dz2"    ] = TH1Overlay("", "dt::norm sb::off lg::top_right logy");
    p["p_ht"     ] = TH1Overlay("", "dt::norm sb::off lg::top_right");
    p["p_mt"     ] = TH1Overlay("", "dt::norm sb::off lg::top_right");
    p["p_met"    ] = TH1Overlay("", "dt::norm sb::off lg::top_right");
    p["p_nbtags" ] = TH1Overlay("", "dt::norm sb::off lg::top_right");
    p["p_njets"  ] = TH1Overlay("", "dt::norm sb::off lg::top_right");
    p["p_pt1_mu" ] = TH1Overlay("", "dt::norm sb::off lg::top_right");
    p["p_pt2_mu" ] = TH1Overlay("", "dt::norm sb::off lg::top_right");
    p["p_eta1_mu"] = TH1Overlay("", "dt::norm sb::off lg::top_right");
    p["p_eta2_mu"] = TH1Overlay("", "dt::norm sb::off lg::top_right");
    p["p_phi1_mu"] = TH1Overlay("", "dt::norm sb::off lg::bottom"   );
    p["p_phi2_mu"] = TH1Overlay("", "dt::norm sb::off lg::bottom"   );
    p["p_d01_mu" ] = TH1Overlay("", "dt::norm sb::off lg::top_right logy");
    p["p_d02_mu" ] = TH1Overlay("", "dt::norm sb::off lg::top_right logy");
    p["p_dz1_mu" ] = TH1Overlay("", "dt::norm sb::off lg::top_right logy");
    p["p_dz2_mu" ] = TH1Overlay("", "dt::norm sb::off lg::top_right logy");
    p["p_iso1_mu"] = TH1Overlay("", "dt::norm sb::off lg::top_right logy");
    p["p_iso2_mu"] = TH1Overlay("", "dt::norm sb::off lg::top_right logy");
    p["p_pt1_el" ] = TH1Overlay("", "dt::norm sb::off lg::top_right");
    p["p_pt2_el" ] = TH1Overlay("", "dt::norm sb::off lg::top_right");
    p["p_eta1_el"] = TH1Overlay("", "dt::norm sb::off lg::top_right");
    p["p_eta2_el"] = TH1Overlay("", "dt::norm sb::off lg::top_right");
    p["p_phi1_el"] = TH1Overlay("", "dt::norm sb::off lg::bottom"   );
    p["p_phi2_el"] = TH1Overlay("", "dt::norm sb::off lg::bottom"   );
    p["p_d01_el" ] = TH1Overlay("", "dt::norm sb::off lg::top_right logy");
    p["p_d02_el" ] = TH1Overlay("", "dt::norm sb::off lg::top_right logy");
    p["p_dz1_el" ] = TH1Overlay("", "dt::norm sb::off lg::top_right logy");
    p["p_dz2_el" ] = TH1Overlay("", "dt::norm sb::off lg::top_right logy");
    p["p_iso1_el"] = TH1Overlay("", "dt::norm sb::off lg::top_right logy");
    p["p_iso2_el"] = TH1Overlay("", "dt::norm sb::off lg::top_right logy");

    for (size_t i = 0; i != hcs.size(); i++)
    {
        TH1Container& hc = hcs.at(i);
        //string& name     = samples[i].name;
        string& title    = samples[i].title;
        Color_t& color   = samples[i].color;
        Style_t& marker  = samples[i].marker;
        std::pair<float, float> yield = rt::IntegralAndError(hc["h_pt1"]);
        samples[i].yield = yield.first;
        samples[i].error = yield.second; 

        // pt1
        p["p_nvtxs"  ].Add(hc["h_nvtxs"  ], title, color, 2, marker);
        p["p_pt1"    ].Add(hc["h_pt1"    ], title, color, 2, marker);
        p["p_pt2"    ].Add(hc["h_pt2"    ], title, color, 2, marker);
        p["p_eta1"   ].Add(hc["h_eta1"   ], title, color, 2, marker);
        p["p_eta2"   ].Add(hc["h_eta2"   ], title, color, 2, marker);
        p["p_phi1"   ].Add(hc["h_phi1"   ], title, color, 2, marker);
        p["p_phi2"   ].Add(hc["h_phi2"   ], title, color, 2, marker);
        p["p_d01"    ].Add(hc["h_d01"    ], title, color, 2, marker);
        p["p_d02"    ].Add(hc["h_d02"    ], title, color, 2, marker);
        p["p_dz1"    ].Add(hc["h_dz1"    ], title, color, 2, marker);
        p["p_dz2"    ].Add(hc["h_dz2"    ], title, color, 2, marker);
        p["p_ht"     ].Add(hc["h_ht"     ], title, color, 2, marker);
        p["p_mt"     ].Add(hc["h_mt"     ], title, color, 2, marker);
        p["p_met"    ].Add(hc["h_met"    ], title, color, 2, marker);
        p["p_nbtags" ].Add(hc["h_nbtags" ], title, color, 2, marker);
        p["p_njets"  ].Add(hc["h_njets"  ], title, color, 2, marker);
        p["p_pt1_mu" ].Add(hc["h_pt1_mu" ], title, color, 2, marker);
        p["p_pt2_mu" ].Add(hc["h_pt2_mu" ], title, color, 2, marker);
        p["p_eta1_mu"].Add(hc["h_eta1_mu"], title, color, 2, marker);
        p["p_eta2_mu"].Add(hc["h_eta2_mu"], title, color, 2, marker);
        p["p_phi1_mu"].Add(hc["h_phi1_mu"], title, color, 2, marker);
        p["p_phi2_mu"].Add(hc["h_phi2_mu"], title, color, 2, marker);
        p["p_d01_mu" ].Add(hc["h_d01_mu" ], title, color, 2, marker);
        p["p_d02_mu" ].Add(hc["h_d02_mu" ], title, color, 2, marker);
        p["p_dz1_mu" ].Add(hc["h_dz1_mu" ], title, color, 2, marker);
        p["p_dz2_mu" ].Add(hc["h_dz2_mu" ], title, color, 2, marker);
        p["p_iso1_mu"].Add(hc["h_iso1_mu"], title, color, 2, marker);
        p["p_iso2_mu"].Add(hc["h_iso2_mu"], title, color, 2, marker);
        p["p_pt1_el" ].Add(hc["h_pt1_el" ], title, color, 2, marker);
        p["p_pt2_el" ].Add(hc["h_pt2_el" ], title, color, 2, marker);
        p["p_eta1_el"].Add(hc["h_eta1_el"], title, color, 2, marker);
        p["p_eta2_el"].Add(hc["h_eta2_el"], title, color, 2, marker);
        p["p_phi1_el"].Add(hc["h_phi1_el"], title, color, 2, marker);
        p["p_phi2_el"].Add(hc["h_phi2_el"], title, color, 2, marker);
        p["p_d01_el" ].Add(hc["h_d01_el" ], title, color, 2, marker);
        p["p_d02_el" ].Add(hc["h_d02_el" ], title, color, 2, marker);
        p["p_dz1_el" ].Add(hc["h_dz1_el" ], title, color, 2, marker);
        p["p_dz2_el" ].Add(hc["h_dz2_el" ], title, color, 2, marker);
        p["p_iso1_el"].Add(hc["h_iso1_el"], title, color, 2, marker);
        p["p_iso2_el"].Add(hc["h_iso2_el"], title, color, 2, marker);
    }

    // print yields
    CTable t_yields;
    t_yields.useTitle();
    t_yields.setTitle(Form("yields scaled to %1.0f /fb", scale));
    t_yields.setColLabel("yield", 0);
    for (size_t i = 0; i != samples.size(); i++)
    {
        t_yields.setRowLabel(samples[i].name , i);
        t_yields.setCell(rt::pm(samples[i].yield, samples[i].error, "1.4"), i, 0);
    }
    t_yields.print();

    // write
    Print(p, Form("plots/overlays/ttw_compare/sr%u", signal_region), suffix);
}
