#include "rt/RootTools.h"
#include <string>
#include <map>

using namespace std;

const size_t npt_bins  = 6; const float pt_bins [] = {10, 15, 20, 30, 40, 50, 200};
const size_t neta_bins = 5; const float eta_bins[] = {0, 0.8, 1.4442, 1.566, 2.0, 2.5};

//void Overlay(const std::string& filename = "plots/fits/egamma_orig_v10/both/results.root", const std::string& suffix = "eps")
void Overlay(const std::string& filename = "plots/fits/SameSign_orig_v1/both/results.root", const std::string& suffix = "eps")
{
    rt::TH1Container hc(filename);
    hc.List();

    map<string, rt::TH1Overlay*> p;

    // make eff projection plots
    for (size_t pt_bin = 0; pt_bin != npt_bins; pt_bin++)
    {
        const float pt_min = pt_bins[pt_bin];
        const float pt_max = pt_bins[pt_bin+1];
        const string plot_name  = Form("p_eff_vs_eta_pt%lu", pt_bin);
        const string plot_title = Form("Efficiency (%1.0f GeV < p_{T} < %1.0f GeV);|#eta|;#varepsilon", pt_min, pt_max);
        p[plot_name] = new rt::TH1Overlay(plot_title, "lg::bottom_right sb::off");
        p[plot_name]->Add(hc[Form("h_data_eff_vs_eta_pt%lu", pt_bin)], "data", kBlue, 2, 20);
        p[plot_name]->Add(hc[Form("h_mc_eff_vs_eta_pt%lu"  , pt_bin)], "MC"  , kRed , 2, 22);
    
    }
    for (size_t eta_bin = 0; eta_bin != neta_bins; eta_bin++)
    {
        const float eta_min = eta_bins[eta_bin];
        const float eta_max = eta_bins[eta_bin+1];
        const string plot_name  = Form("p_eff_vs_pt_eta%lu", eta_bin);
        const string plot_title = Form("Efficiency (%1.2f < |\\eta| < %1.2f);p_{T} (GeV);#varepsilon", eta_min, eta_max);
        p[plot_name] = new rt::TH1Overlay(plot_title, "lg::bottom_right sb::off");
        p[plot_name]->Add(hc[Form("h_data_eff_vs_pt_eta%lu", eta_bin)] , "data", kBlue, 2, 20);
        p[plot_name]->Add(hc[Form("h_mc_eff_vs_pt_eta%lu"  , eta_bin)], "MC"  , kRed , 2, 22);
    }

    hc.SetLineColor(kBlue);
    hc.SetLineWidth(2);
    hc.SetMinMax(0.5, 1.1);

    // write the output
    rt::Print(p, rt::dirname(filename) + "/overlays", suffix);
    hc.Print(rt::dirname(filename) + "/overlays", suffix);
}
