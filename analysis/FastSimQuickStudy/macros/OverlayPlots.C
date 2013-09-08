#include "rt/RootTools.h"
#include <string> 

using namespace std;
using namespace rt;

void AddOverlay
(
    std::map<string, TH1Overlay>& p,
    const TH1Container& hc_fast,
    const TH1Container& hc_full,
    const string hist_name,
    const string draw_option = "",
    const float min = 1,
    const float max = -1,
    const bool do_reldiff = false
)
{
    TH1* h_fast    = hc_fast[hist_name];
    TH1* h_full    = hc_full[hist_name];

    // style
    const Color_t full_color = kBlue;
    const Color_t fast_color = kRed;
    const Color_t rdiff_color = kBlack;
    const string full_title = "FULLSIM";
    const string fast_title = "FASTSIM";
    const Width_t width  = 2.0;
    const Style_t marker = 20;

    // overlay
    const string plot_name  = rt::string_replace_first(hist_name, "h_", "p_");
    const string plot_title = Form("%s;%s;%s", h_full->GetTitle(), h_full->GetXaxis()->GetTitle(), h_full->GetYaxis()->GetTitle());
    p[plot_name] = TH1Overlay(plot_title, draw_option);
    p[plot_name].Add(h_fast, fast_title, fast_color, width, marker);
    p[plot_name].Add(h_full, full_title, full_color, width, marker);
    if (max > min)
    {
        p[plot_name].SetYAxisRange(min, max);
    }

    // relative difference
    if (do_reldiff)
    {
        TH1* h_reldiff = rt::RelativeDiffHists
        (
         h_full, 
         h_fast, 
         Form("%s_reldiff", hist_name.c_str()), 
         Form("%s (full - fast)/full;%s;%s", h_full->GetTitle(), h_full->GetXaxis()->GetTitle(), "Relative Difference of Efficiency (full - fast)/full")
        );

        const string plot_reldiff_name  = plot_name + "_reldiff";
        p[plot_reldiff_name] = TH1Overlay("", "sb::off lg::off");
        p[plot_reldiff_name].Add(h_reldiff, rdiff_color, width, marker);
        p[plot_reldiff_name].SetYAxisRange(-0.25, 0.25);
    }
}


void OverlayPlots(const string& suffix = "png")
{
    // input plots
    const string input_filename_fast = "plots/dy_fastsim/dy_fastsim_plots.root";
    TH1Container hc_fast(input_filename_fast);

    const string input_filename_full = "plots/dy_fullsim/dy_fullsim_plots.root"; 
    TH1Container hc_full(input_filename_full);

    const float eff_min = 0.2;
    const float eff_max = 1.1;

    // overlay electron plots 
    std::map<string, TH1Overlay> p;
    AddOverlay(p , hc_fast , hc_full , "h_el_den_vs_nvtxs"  , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_el_id_vs_nvtxs"   , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_el_iso_vs_nvtxs"  , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_el_both_vs_nvtxs" , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_el_den_vs_pt"     , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_el_id_vs_pt"      , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_el_iso_vs_pt"     , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_el_both_vs_pt"    , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_el_den_vs_eta"    , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_el_id_vs_eta"     , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_el_iso_vs_eta"    , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_el_both_vs_eta"   , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_el_den_vs_pt"     , "sb::off dt::norm lg::top_right");

    AddOverlay(p , hc_fast , hc_full , "h_el_eff_id_vs_nvtxs"   , "sb::off lg::bottom_right" , eff_min , eff_max, /*do_reldiff=*/true);
    AddOverlay(p , hc_fast , hc_full , "h_el_eff_iso_vs_nvtxs"  , "sb::off lg::bottom_right" , eff_min , eff_max, /*do_reldiff=*/true);
    AddOverlay(p , hc_fast , hc_full , "h_el_eff_both_vs_nvtxs" , "sb::off lg::bottom_right" , eff_min , eff_max, /*do_reldiff=*/true);
    AddOverlay(p , hc_fast , hc_full , "h_el_eff_id_vs_pt"      , "sb::off lg::bottom_right" , eff_min , eff_max, /*do_reldiff=*/true);
    AddOverlay(p , hc_fast , hc_full , "h_el_eff_iso_vs_pt"     , "sb::off lg::bottom_right" , eff_min , eff_max, /*do_reldiff=*/true);
    AddOverlay(p , hc_fast , hc_full , "h_el_eff_both_vs_pt"    , "sb::off lg::bottom_right" , eff_min , eff_max, /*do_reldiff=*/true);
    AddOverlay(p , hc_fast , hc_full , "h_el_eff_id_vs_eta"     , "sb::off lg::bottom_right" , eff_min , eff_max, /*do_reldiff=*/true);
    AddOverlay(p , hc_fast , hc_full , "h_el_eff_iso_vs_eta"    , "sb::off lg::bottom_right" , eff_min , eff_max, /*do_reldiff=*/true);
    AddOverlay(p , hc_fast , hc_full , "h_el_eff_both_vs_eta"   , "sb::off lg::bottom_right" , eff_min , eff_max, /*do_reldiff=*/true);

    // overlay muon plots 
    AddOverlay(p , hc_fast , hc_full , "h_mu_den_vs_nvtxs"  , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_mu_id_vs_nvtxs"   , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_mu_iso_vs_nvtxs"  , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_mu_both_vs_nvtxs" , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_mu_den_vs_pt"     , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_mu_id_vs_pt"      , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_mu_iso_vs_pt"     , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_mu_both_vs_pt"    , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_mu_den_vs_eta"    , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_mu_id_vs_eta"     , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_mu_iso_vs_eta"    , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_mu_both_vs_eta"   , "sb::off dt::norm lg::top_right");
    AddOverlay(p , hc_fast , hc_full , "h_mu_den_vs_pt"     , "sb::off dt::norm lg::top_right");

    AddOverlay(p , hc_fast , hc_full , "h_mu_eff_id_vs_nvtxs"   , "sb::off lg::bottom_right" , eff_min , eff_max, /*do_reldiff=*/true);
    AddOverlay(p , hc_fast , hc_full , "h_mu_eff_iso_vs_nvtxs"  , "sb::off lg::bottom_right" , eff_min , eff_max, /*do_reldiff=*/true);
    AddOverlay(p , hc_fast , hc_full , "h_mu_eff_both_vs_nvtxs" , "sb::off lg::bottom_right" , eff_min , eff_max, /*do_reldiff=*/true);
    AddOverlay(p , hc_fast , hc_full , "h_mu_eff_id_vs_pt"      , "sb::off lg::bottom_right" , eff_min , eff_max, /*do_reldiff=*/true);
    AddOverlay(p , hc_fast , hc_full , "h_mu_eff_iso_vs_pt"     , "sb::off lg::bottom_right" , eff_min , eff_max, /*do_reldiff=*/true);
    AddOverlay(p , hc_fast , hc_full , "h_mu_eff_both_vs_pt"    , "sb::off lg::bottom_right" , eff_min , eff_max, /*do_reldiff=*/true);
    AddOverlay(p , hc_fast , hc_full , "h_mu_eff_id_vs_eta"     , "sb::off lg::bottom_right" , eff_min , eff_max, /*do_reldiff=*/true);
    AddOverlay(p , hc_fast , hc_full , "h_mu_eff_iso_vs_eta"    , "sb::off lg::bottom_right" , eff_min , eff_max, /*do_reldiff=*/true);
    AddOverlay(p , hc_fast , hc_full , "h_mu_eff_both_vs_eta"   , "sb::off lg::bottom_right" , eff_min , eff_max, /*do_reldiff=*/true);

    // output
    rt::SetStyle();
    const string output_path = "plots/compare/" + suffix;
    Print(p, output_path, suffix);
}
