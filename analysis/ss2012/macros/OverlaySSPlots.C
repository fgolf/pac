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
#include "at/DileptonHypType.h"
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
    h_pred->SetDrawOption("hist E5");
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
    const Color_t data_color  = kBlack;
    const Color_t rare_color  = kCyan-5;
    const Color_t fake_color  = kRed-6;
    const Color_t flip_color  = kOrange-8;
    const Style_t data_marker = 20;
    const float marker_size   = 0.9;
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
    TH1* h_spil  = hc_rare[Form("h_%s_fake", hist_stem.c_str())];
    h_fake->Add(h_spil, -1.0);
    TH1* h_pred = GetTotalPredHist(h_fake, h_flip, h_rare);
    h_data->SetMarkerSize(marker_size);


    if (hist_stem == "yield")
    {
        option.append(" B");
        const float width = 0.6;
        const float offset = 0.2;
        const float label_size = 0.07;
        h_data->SetBarWidth(width);
        h_fake->SetBarWidth(width);
        h_flip->SetBarWidth(width);
        h_rare->SetBarWidth(width);
        h_pred->SetBarWidth(width);
        h_data->SetBarOffset(offset);
        h_fake->SetBarOffset(offset);
        h_flip->SetBarOffset(offset);
        h_rare->SetBarOffset(offset);
        h_pred->SetBarOffset(offset);
        h_data->SetLabelSize(label_size);
        h_fake->SetLabelSize(label_size);
        h_flip->SetLabelSize(label_size);
        h_rare->SetLabelSize(label_size);
        h_pred->SetLabelSize(label_size);
    }

    rt::TH1Overlay p(title, option);
    const float max = std::max(h_data->GetMaximum(), h_pred->GetMaximum());
    p.Add(h_data, /*no_stack=*/true, data_legend, data_color, 2, data_marker);
    p.Add(h_fake, fake_legend, fake_color);
    p.Add(h_flip, flip_legend, flip_color);
    p.Add(h_rare, rare_legend, rare_color);
    p.Add(h_pred, /*no_stack=*/true, unc_legend, 1, 2, 1, shade_style);
    p.SetYAxisRange(0.0, max);
    return p;
}

// Overlay the kinematic plots
void OverlaySSPlots
(
    float lumi, 
    const std::string& output_name, 
    const std::string& signal_region_name, 
    const std::string& analysis_type_name, 
    const std::string& signal_region_type_name = "inclusive", 
    int charge_type = 0, 
    const std::string& suffix = "png"
)
{
    ss::SignalRegionInfo sr = ss::GetSignalRegionInfo(signal_region_name, analysis_type_name, signal_region_type_name);

    // charge type
    string charge_stem = "";
    switch (charge_type)
    {
        case 0 : charge_stem = ""; break;
        case 1 : charge_stem = "_pp"; break;
        case -1: charge_stem = "_mm"; break;
    }

    const string plots_path = Form("plots/%s/%s/%s/%s", output_name.c_str(), analysis_type_name.c_str(), signal_region_type_name.c_str(), sr.name.c_str());

    rt::TH1Container hc_data(Form("%s/data%s.root", plots_path.c_str(), charge_stem.c_str()));
    rt::TH1Container hc_mc;
    hc_mc += rt::TH1Container(Form("%s/wgstar2t%s.root"     , plots_path.c_str(), charge_stem.c_str()));
    hc_mc += rt::TH1Container(Form("%s/wgstar2m%s.root"     , plots_path.c_str(), charge_stem.c_str()));
    hc_mc += rt::TH1Container(Form("%s/wz%s.root"           , plots_path.c_str(), charge_stem.c_str()));
    hc_mc += rt::TH1Container(Form("%s/zz%s.root"           , plots_path.c_str(), charge_stem.c_str()));
    hc_mc += rt::TH1Container(Form("%s/ttg%s.root"          , plots_path.c_str(), charge_stem.c_str()));
    hc_mc += rt::TH1Container(Form("%s/ttw%s.root"          , plots_path.c_str(), charge_stem.c_str()));
    hc_mc += rt::TH1Container(Form("%s/ttz%s.root"          , plots_path.c_str(), charge_stem.c_str()));
    hc_mc += rt::TH1Container(Form("%s/tbz%s.root"          , plots_path.c_str(), charge_stem.c_str()));
    hc_mc += rt::TH1Container(Form("%s/ttww%s.root"         , plots_path.c_str(), charge_stem.c_str()));
    hc_mc += rt::TH1Container(Form("%s/wwg%s.root"          , plots_path.c_str(), charge_stem.c_str()));
    hc_mc += rt::TH1Container(Form("%s/www%s.root"          , plots_path.c_str(), charge_stem.c_str()));
    hc_mc += rt::TH1Container(Form("%s/wwz%s.root"          , plots_path.c_str(), charge_stem.c_str()));
    hc_mc += rt::TH1Container(Form("%s/wzz%s.root"          , plots_path.c_str(), charge_stem.c_str()));
    hc_mc += rt::TH1Container(Form("%s/zzz%s.root"          , plots_path.c_str(), charge_stem.c_str()));
    hc_mc += rt::TH1Container(Form("%s/wmwmqq%s.root"       , plots_path.c_str(), charge_stem.c_str()));
    hc_mc += rt::TH1Container(Form("%s/wpwpqq%s.root"       , plots_path.c_str(), charge_stem.c_str()));
    hc_mc += rt::TH1Container(Form("%s/ww_ds%s.root"        , plots_path.c_str(), charge_stem.c_str()));
    hc_mc += rt::TH1Container(Form("%s/wh_zh_tth_hww%s.root", plots_path.c_str(), charge_stem.c_str()));
    hc_mc += rt::TH1Container(Form("%s/wh_zh_tth_hzz%s.root", plots_path.c_str(), charge_stem.c_str()));
    hc_mc += rt::TH1Container(Form("%s/wh_zh_tth_htt%s.root", plots_path.c_str(), charge_stem.c_str()));
    
    // set style
    rt::SetTDRStyle();
    gStyle->SetHatchesSpacing(1.00);

    // title
    string charge_title = "";
    switch (charge_type)
    {
        case 0 : charge_title = ""; break;
        case 1 : charge_title = ", (++)"; break;
        case -1: charge_title = ", (--)"; break;
    }
    std::string title = Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %3.1f fb^{-1}%s", lumi, charge_title.c_str());

    // overlays
    map<string, rt::TH1Overlay> p;
    rt::TH1Overlay::profile_marker_size_default = 10.0;
    p["p_yield"       ] = CreateOverlay(hc_data, hc_mc, "yield"      , Form("%s;channel;Events"                  , title.c_str()), "sb::off dt::stack lg::left" );
    p["p_dilep_mass"  ] = CreateOverlay(hc_data, hc_mc, "dilep_mass" , Form("%s;m_{ll} (GeV);Events"             , title.c_str()), "sb::off dt::stack lg::right");
    p["p_pt1"         ] = CreateOverlay(hc_data, hc_mc, "pt1"        , Form("%s;p^{lep1}_{T} (GeV);Events"       , title.c_str()), "sb::off dt::stack lg::right");
    p["p_pt2"         ] = CreateOverlay(hc_data, hc_mc, "pt2"        , Form("%s;p^{lep2}_{T} (GeV);Events"       , title.c_str()), "sb::off dt::stack lg::right");
    p["p_met"         ] = CreateOverlay(hc_data, hc_mc, "met"        , Form("%s;E^{miss}_{T} (GeV);Events"       , title.c_str()), "sb::off dt::stack lg::right");
    p["p_ht"          ] = CreateOverlay(hc_data, hc_mc, "ht"         , Form("%s;H_{T} (GeV);Events"              , title.c_str()), "sb::off dt::stack lg::right");
    p["p_mt"          ] = CreateOverlay(hc_data, hc_mc, "mt"         , Form("%s;m_{T} (GeV);Events"              , title.c_str()), "sb::off dt::stack lg::right");
    p["p_nbtags"      ] = CreateOverlay(hc_data, hc_mc, "nbtags"     , Form("%s;number of b-tagged jets;Events"  , title.c_str()), "sb::off dt::stack lg::right");
    p["p_njets"       ] = CreateOverlay(hc_data, hc_mc, "njets"      , Form("%s;number of jets;Events"           , title.c_str()), "sb::off dt::stack lg::right");
    p["p_lepdphi"     ] = CreateOverlay(hc_data, hc_mc, "lepdphi"    , Form("%s;#Delta#Phi(lep1, lep2);Events"   , title.c_str()), "sb::off dt::stack lg::right");
    p["p_lepdeta"     ] = CreateOverlay(hc_data, hc_mc, "lepdeta"    , Form("%s;#Delta#eta(lep1, lep2);Events"   , title.c_str()), "sb::off dt::stack lg::right");
    p["p_lepdr"       ] = CreateOverlay(hc_data, hc_mc, "lepdr"      , Form("%s;#DeltaR(lep1, lep2);Events"      , title.c_str()), "sb::off dt::stack lg::right");
    p["p_drlepb"      ] = CreateOverlay(hc_data, hc_mc, "drlepb"     , Form("%s;#DeltaR(lep, btag);Events"       , title.c_str()), "sb::off dt::stack lg::right");
    p["p_btagdr"      ] = CreateOverlay(hc_data, hc_mc, "btagdr"     , Form("%s;#DeltaR(btag1, btag2);Events"    , title.c_str()), "sb::off dt::stack lg::right");
    p["p_drjetb"      ] = CreateOverlay(hc_data, hc_mc, "drjetb"     , Form("%s;#DeltaR(btag, jet);Events"       , title.c_str()), "sb::off dt::stack lg::right");
    p["p_ptjetlep"    ] = CreateOverlay(hc_data, hc_mc, "ptjetlep"   , Form("%s;jet p_{T} / lep p_{T} - 1;Events", title.c_str()), "sb::off dt::stack lg::right");
    p["p_drlep3rdlep" ] = CreateOverlay(hc_data, hc_mc, "drlep3rdlep", Form("%s;#DeltaR(lep, 3rd lep);Events"    , title.c_str()), "sb::off dt::stack lg::right");

    // for pass
    p["p_pas_met"   ] = CreateOverlay(hc_data, hc_mc, "pas_met"   , Form("%s;E^{miss}_{T} (GeV);Events"       , title.c_str()), "sb::off dt::stack lg::right"    );
    p["p_pas_ht"    ] = CreateOverlay(hc_data, hc_mc, "pas_ht"    , Form("%s;H_{T} (GeV);Events"              , title.c_str()), "sb::off dt::stack lg::top_right");
    p["p_pas_nbtags"] = CreateOverlay(hc_data, hc_mc, "pas_nbtags", Form("%s;number of b-tagged jets;Events"  , title.c_str()), "sb::off dt::stack lg::right"    );
    p["p_pas_njets" ] = CreateOverlay(hc_data, hc_mc, "pas_njets" , Form("%s;number of jets;Events"           , title.c_str()), "sb::off dt::stack lg::right"    );

    // keep the legend off the label the top
    p["p_pas_ht"    ].SetLegendOffset(0.031);
    p["p_pas_met"   ].SetLegendOffset(0.031);
    p["p_pas_nbtags"].SetLegendOffset(0.031);
    p["p_pas_njets" ].SetLegendOffset(0.031);

    p["p_pas_ht"    ].SetLegendTextSize(0.025);
    p["p_pas_met"   ].SetLegendTextSize(0.025);
    p["p_pas_nbtags"].SetLegendTextSize(0.025);
    p["p_pas_njets" ].SetLegendTextSize(0.025);

    p["p_dilep_mass_nj0"] = CreateOverlay(hc_data, hc_mc, "dilep_mass_nj0" , Form("%s;m_{ll} (GeV);Events"             , title.c_str()), "sb::off dt::stack lg::right");
    p["p_dilep_mass_nj1"] = CreateOverlay(hc_data, hc_mc, "dilep_mass_nj1" , Form("%s;m_{ll} (GeV);Events"             , title.c_str()), "sb::off dt::stack lg::right");
    p["p_dilep_mass_nj2"] = CreateOverlay(hc_data, hc_mc, "dilep_mass_nj2" , Form("%s;m_{ll} (GeV);Events"             , title.c_str()), "sb::off dt::stack lg::right");

    // overlay individual channels
    for (size_t i = 1; i != at::DileptonHypType::static_size; i++)
    {
        at::DileptonHypType::value_type hyp_type = static_cast<at::DileptonHypType::value_type>(i);

        // name and title suffixes
        string hn = Form("_%s" ,  GetDileptonHypTypeName(hyp_type).c_str());
        //string ht = Form(" (%s)",  GetDileptonHypTypeTitle(hyp_type).c_str());

        p["p_dilep_mass"+hn] = CreateOverlay(hc_data, hc_mc, "dilep_mass"+hn , Form("%s;m_{ll} (GeV);Events"             , title.c_str()), "sb::off dt::stack lg::right");
        p["p_pt1"       +hn] = CreateOverlay(hc_data, hc_mc, "pt1"       +hn , Form("%s;p^{lep1}_{T} (GeV);Events"       , title.c_str()), "sb::off dt::stack lg::right");
        p["p_pt2"       +hn] = CreateOverlay(hc_data, hc_mc, "pt2"       +hn , Form("%s;p^{lep2}_{T} (GeV);Events"       , title.c_str()), "sb::off dt::stack lg::right");
        p["p_met"       +hn] = CreateOverlay(hc_data, hc_mc, "met"       +hn , Form("%s;E^{miss}_{T} (GeV);Events"       , title.c_str()), "sb::off dt::stack lg::right");
        p["p_ht"        +hn] = CreateOverlay(hc_data, hc_mc, "ht"        +hn , Form("%s;H_{T} (GeV);Events"              , title.c_str()), "sb::off dt::stack lg::right");
        p["p_mt"        +hn] = CreateOverlay(hc_data, hc_mc, "mt"        +hn , Form("%s;m_{T} (GeV);Events"              , title.c_str()), "sb::off dt::stack lg::right");
        p["p_nbtags"    +hn] = CreateOverlay(hc_data, hc_mc, "nbtags"    +hn , Form("%s;number of b-tagged jets;Events"  , title.c_str()), "sb::off dt::stack lg::right");
        p["p_njets"     +hn] = CreateOverlay(hc_data, hc_mc, "njets"     +hn , Form("%s;number of jets;Events"           , title.c_str()), "sb::off dt::stack lg::right");

        p["p_dilep_mass_nj0"+hn] = CreateOverlay(hc_data, hc_mc, "dilep_mass_nj0"+hn , Form("%s;m_{ll} (GeV);Events", title.c_str()), "sb::off dt::stack lg::right");
        p["p_dilep_mass_nj1"+hn] = CreateOverlay(hc_data, hc_mc, "dilep_mass_nj1"+hn , Form("%s;m_{ll} (GeV);Events", title.c_str()), "sb::off dt::stack lg::right");
        p["p_dilep_mass_nj2"+hn] = CreateOverlay(hc_data, hc_mc, "dilep_mass_nj2"+hn , Form("%s;m_{ll} (GeV);Events", title.c_str()), "sb::off dt::stack lg::right");
    }

    // SR label
    TLatex t1_upper_left (0.18, 0.86, Form("%s: %s", sr.name.c_str(), sr.title.c_str())); 
    TLatex t1_upper_right(0.18, 0.86, Form("%s: %s", sr.name.c_str(), sr.title.c_str())); 
    t1_upper_left.SetTextSize(0.0225);
    t1_upper_right.SetTextSize(0.0225);
    for (map<string, rt::TH1Overlay>::iterator p_iter = p.begin(); p_iter != p.end(); p_iter++)
    {
        if (p_iter->first == "p_yield")
        {
            p_iter->second.AddText(t1_upper_right);
        }
        else
        {
            p_iter->second.AddText(t1_upper_left);
        }
    }

     // write
    rt::Print(p, Form("%s/kin", plots_path.c_str()), suffix);

    // print yield explicitly
    // this is a kludge to the the x error bars the right size for the yeild plot
    gStyle->SetErrorX(0.3);
    rt::Print(p["p_yield"], Form("%s/kin/p_yield", plots_path.c_str()), suffix);
    gStyle->SetErrorX();
}
