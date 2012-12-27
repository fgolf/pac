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

// combine the contributions for the background predictions
TH1F* GetTotalPredHist(TH1* h_fake, TH1* h_flip, TH1* h_mc)
{
    string hist_name = rt::string_replace_all(h_fake->GetName(), "_fake", "_pred");
    TH1F* h_pred = dynamic_cast<TH1F*>(h_fake->Clone(hist_name.c_str()));
    h_pred->Add(h_flip);
    h_pred->Add(h_mc);
    h_pred->SetLineColor(kWhite);
    h_pred->SetFillColor(kBlack);
    h_pred->SetFillStyle(3335);
    h_pred->SetDrawOption("hist E2");
    return h_pred;
}

rt::TH1Overlay CreateOverlay
(
    rt::TH1Container& hc_data, 
    rt::TH1Container& hc_rare, 
    const std::string& hist_stem, 
    const std::string& title, 
    std::string option = "sb::off dt::stack lg::top_right"
)
{
	// colors
    //static Color_t data_color = kBlack;
    //static Color_t mc_color   = kCyan-5;
    //static Color_t fake_color = kRed-6;
    //static Color_t flip_color = kBlue-8;
    const Color_t data_color  = kBlack;
    const Color_t rare_color  = kCyan-5;
    const Color_t fake_color  = kRed-6;
    const Color_t flip_color  = kOrange-8;
    const Style_t data_marker = 20;
    //const float text_size     = 0.035;
    const float marker_size   = 1.5;
    const Style_t shade_style = 3335;
    const string flip_legend  = "Charge-flip";
    const string fake_legend  = "Fakes";
    const string rare_legend  = "Rare MC";
    const string data_legend  = "Observed";
    const string unc_legend   = "Total Uncertainty";

    TH1* h_data  = hc_data[Form("h_%s_ss"  , hist_stem.c_str())];
    TH1* h_fake  = hc_data[Form("h_%s_fake", hist_stem.c_str())];
    TH1* h_flip  = hc_data[Form("h_%s_flip", hist_stem.c_str())];
    TH1* h_rare  = hc_rare[Form("h_%s_ss"  , hist_stem.c_str())];
    TH1* h_pred = GetTotalPredHist(h_fake, h_flip, h_rare);
    h_data->SetMarkerSize(marker_size);

    //if (hist_stem == "yield")
    //{
    //    option.append(" hist B");
    //    h_data->SetBarWidth(0.6);
    //    h_fake->SetBarWidth(0.6);
    //    h_flip->SetBarWidth(0.6);
    //    h_rare->SetBarWidth(0.6);
    //    h_pred->SetBarWidth(0.6);
    //    h_data->SetBarOffset(0.2);
    //    h_fake->SetBarOffset(0.2);
    //    h_flip->SetBarOffset(0.2);
    //    h_rare->SetBarOffset(0.2);
    //    h_pred->SetBarOffset(0.2);
    //    //h_fake->SetOption("hist B");
    //    //h_flip->SetOption("hist B");
    //    //h_rare->SetOption("hist B");
    //    //h_pred->SetOption("hist B");
    //}

    rt::TH1Overlay p(title, option);
    p.Add(h_data, /*no_stack=*/true, data_legend, data_color, 2, data_marker);
    p.Add(h_fake, fake_legend, fake_color);
    p.Add(h_flip, flip_legend, flip_color);
    p.Add(h_rare, rare_legend, rare_color);
    p.Add(h_pred, /*no_stack=*/true, unc_legend, 1, 2, 1, shade_style); 

    return p;
}

// Overlay the kinematic plots
void OverlaySSPlots(float lumi = 1.0, unsigned int signal_region_num = 0, const std::string& output_name = "", const std::string& suffix = "png")
{
    ss::SignalRegionInfo sr = ss::GetSignalRegionInfo(signal_region_num);

    rt::TH1Container hc_data(Form("plots/%s/%s/data.root", output_name.c_str(), sr.name.c_str()));
    rt::TH1Container hc_mc;
    hc_mc += rt::TH1Container(Form("plots/%s/%s/wgstar2t.root" , output_name.c_str() , sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/wgstar2m.root" , output_name.c_str() , sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/wgstar2e.root" , output_name.c_str() , sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/wz.root"       , output_name.c_str() , sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/zz.root"       , output_name.c_str() , sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/ttg.root"      , output_name.c_str() , sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/ttw.root"      , output_name.c_str() , sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/ttz.root"      , output_name.c_str() , sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/tbz.root"      , output_name.c_str() , sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/ttww.root"     , output_name.c_str() , sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/wwg.root"      , output_name.c_str() , sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/www.root"      , output_name.c_str() , sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/wwz.root"      , output_name.c_str() , sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/wzz.root"      , output_name.c_str() , sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/zzz.root"      , output_name.c_str() , sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/wmwmqq.root"   , output_name.c_str() , sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/wpwpqq.root"   , output_name.c_str() , sr.name.c_str()));
    hc_mc += rt::TH1Container(Form("plots/%s/%s/ww_ds.root"    , output_name.c_str() , sr.name.c_str()));
    
	// set style
	rt::SetTDRStyle();
    gStyle->SetHatchesSpacing(1.00);

    // title
	std::string title = Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %3.1f fb^{-1}", lumi);

    // overlays
    map<string, rt::TH1Overlay> p;
    rt::TH1Overlay::profile_marker_size_default = 10.0;
    p["p_yield"       ] = CreateOverlay(hc_data, hc_mc, "yield"      , Form("%s;channel;Events"                  , title.c_str()), "sb::off dt::stack lg::top_left" );
    p["p_pt1"         ] = CreateOverlay(hc_data, hc_mc, "pt1"        , Form("%s;p^{lep1}_{T} (GeV);Events"       , title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_pt2"         ] = CreateOverlay(hc_data, hc_mc, "pt2"        , Form("%s;p^{lep2}_{T} (GeV);Events"       , title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_met"         ] = CreateOverlay(hc_data, hc_mc, "met"        , Form("%s;E^{miss}_{T} (GeV);Events"       , title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_ht"          ] = CreateOverlay(hc_data, hc_mc, "ht"         , Form("%s;H_{T} (GeV);Events"              , title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_nbtags"      ] = CreateOverlay(hc_data, hc_mc, "nbtags"     , Form("%s;number of b-tagged jets;Events"  , title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_njets"       ] = CreateOverlay(hc_data, hc_mc, "njets"      , Form("%s;number of jets;Events"           , title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_lepdphi"     ] = CreateOverlay(hc_data, hc_mc, "lepdphi"    , Form("%s;#Delta#Phi(lep1, lep2);Events"   , title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_lepdeta"     ] = CreateOverlay(hc_data, hc_mc, "lepdeta"    , Form("%s;#Delta#eta(lep1, lep2);Events"   , title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_lepdr"       ] = CreateOverlay(hc_data, hc_mc, "lepdr"      , Form("%s;#DeltaR(lep1, lep2);Events"      , title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_drlepb"      ] = CreateOverlay(hc_data, hc_mc, "drlepb"     , Form("%s;#DeltaR(lep, btag);Events"       , title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_btagdr"      ] = CreateOverlay(hc_data, hc_mc, "btagdr"     , Form("%s;#DeltaR(btag1, btag2);Events"    , title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_drjetb"      ] = CreateOverlay(hc_data, hc_mc, "drjetb"     , Form("%s;#DeltaR(btag, jet);Events"       , title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_ptjetlep"    ] = CreateOverlay(hc_data, hc_mc, "ptjetlep"   , Form("%s;jet p_{T} / lep p_{T} - 1;Events", title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_drlep3rdlep" ] = CreateOverlay(hc_data, hc_mc, "drlep3rdlep", Form("%s;#DeltaR(lep, 3rd lep);Events"    , title.c_str()), "sb::off dt::stack lg::top_right");


	// SR label
    TLatex t1(0.18, 0.84, Form("%s: %s", sr.name.c_str(), sr.title.c_str())); 
    t1.SetTextSize(0.028);
    for (map<string, rt::TH1Overlay>::iterator p_iter = p.begin(); p_iter != p.end(); p_iter++)
    {
        p_iter->second.AddText(t1);
    }

     // write
 	rt::CopyIndexPhp(Form("plots/%s/%s/kin", output_name.c_str(), sr.name.c_str()));
    rt::Print(p, Form("plots/%s/%s/kin", output_name.c_str(), sr.name.c_str()), suffix);
}
