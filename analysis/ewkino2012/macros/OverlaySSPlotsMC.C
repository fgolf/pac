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

#define arraysize(ar)  (sizeof(ar) / sizeof(ar[0]))
const std::string bkgds_all[] = {
    // "data",
    "ww",
    "wz",
    "zz",
    "ttg",
    "ttw",
    "ttz",
    "tbz",
    "ttww",
    "wwg",
    "www",
    "wwz",
    "wzz",
    "zzz",
    "wmwmqq",
    "wpwpqq",
    // "wgstar2e",
    "wgstar2m",
    "wgstar2t",
    "ww_ds",
    "dyjets",
    "wjets",
    "ttdil",
    "ttotr",
    "ttslb",
    "ttslo",
    "t_schan",
    "t_tchan",
    "t_tw",
    "wh_zh_tth_hww",
    "wh_zh_tth_hzz",
    "wh_zh_tth_htt"
};

// const Int_t colors[] = {2,3,4,5,6,7,8,9,28,30,38,40,41,42,46,102,152,103,153,104,154,105,155,106,156,107,157,108,158,109,159};
const Int_t colors[] = {2,3,4,5,6,7,8,9,28,30,38,40,41,42,46,kRed+2,kRed-7,kGreen+2,kGreen-7,kBlue+2,kBlue-7,kMagenta+2,kMagenta-7,kCyan+2,kCyan-7,kViolet+2,kViolet-7,kBlue-6,kGreen+2,kMagenta+2,kRed-4};
const Int_t markers[] = {20, 21, 22, 23, 24, 25, 26};

bool my_sort_function_lin(TH1* h1, TH1* h2)
{
    return (h1->Integral() > h2->Integral());
}

bool my_sort_function_log(TH1* h1, TH1* h2)
{
    return (h1->Integral() < h2->Integral());
}

// combine the contributions for the background predictions
TH1F* GetTotalPredHist(std::vector<TH1*> vhists)
{
    if (vhists.empty()) {return 0;}
    string hist_name = rt::string_replace_all(vhists.at(0)->GetName(), "_ss", "_pred");
    TH1F* h_pred = dynamic_cast<TH1F*>(vhists.at(0)->Clone(hist_name.c_str()));

    for (unsigned int idx = 1; idx < vhists.size(); idx++)
    {
        h_pred->Add(vhists.at(idx));
    }

    h_pred->SetLineColor(kWhite);
    h_pred->SetFillColor(kBlack);
    h_pred->SetFillStyle(3335);
    h_pred->SetDrawOption("hist E5");
    return h_pred;
}

rt::TH1Overlay CreateOverlay
(
    std::vector<rt::TH1Container>& vhc_signal,
    std::vector<std::string>& vhc_signal_names,
    std::vector<rt::TH1Container>& vhc_bkgd,
    std::vector<std::string>& vhc_bkgd_names,
    const std::string& hist_stem, 
    const std::string& title, 
    std::string option = "sb::off dt::stack lg::top_right"
    )
{
    // colors
    const Color_t data_color  = kBlack;
    

    const Style_t data_marker = 20;
    const float marker_size   = 0.9;
    const Style_t shade_style = 3335;
    const string unc_legend   = "Total Uncertainty";

    std::vector<TH1*> vsignals;
    for (unsigned int idx = 0; idx < vhc_signal.size(); idx++)
    {
        vsignals.push_back(vhc_signal.at(idx)[Form("h_%s_ss", hist_stem.c_str())]);
    }

    assert(vsignals.size() == vhc_signal_names.size());
    
    std::vector<TH1*> vbkgds;
    for (unsigned int idx = 0; idx < vhc_bkgd.size(); idx++)
    {
        vbkgds.push_back(vhc_bkgd.at(idx)[Form("h_%s_ss", hist_stem.c_str())]);
    }

    assert(vbkgds.size() == vhc_bkgd_names.size());

    TH1* h_pred = GetTotalPredHist(vbkgds);

    // if (hist_stem == "yield")
    // {
    //     option.append(" B");
    //     const float width = 0.6;
    //     const float offset = 0.2;
    //     const float label_size = 0.07;
    //     h_data->SetBarWidth(width);
    //     h_rare->SetBarWidth(width);
    //     h_pred->SetBarWidth(width);
    //     h_data->SetBarOffset(offset);
    //     h_rare->SetBarOffset(offset);
    //     h_pred->SetBarOffset(offset);
    //     h_data->SetLabelSize(label_size);
    //     h_rare->SetLabelSize(label_size);
    //     h_pred->SetLabelSize(label_size);
    // }

    rt::TH1Overlay p(title, option);
    for (unsigned int idx = 0; idx < vsignals.size(); idx++)
    {
        p.Add(vsignals.at(idx), /*no_stack=*/true, vhc_signal_names.at(idx), data_color, 2, markers[idx]);
    }

    for (unsigned int idx = 0; idx < vbkgds.size(); idx++)
    {
        p.Add(vbkgds.at(idx), vhc_bkgd_names.at(idx), colors[idx]);
    }

    p.Add(h_pred, /*no_stack=*/true, unc_legend, 1, 2, 1, shade_style); 
    return p;
}

// Overlay the kinematic plots
void OverlaySSPlotsMC
(
    float lumi, 
    const std::string& output_name, 
    const std::string& signal_region_name, 
    const std::string& analysis_type_name,
    const std::string& signal_samples,
    const std::string& bkgd_samples = "all",  
    bool combine_signals = false,
    bool combine_bkgds = false,
    bool normalize = false,
    const std::string& signal_region_type_name = "inclusive", 
    int charge_type = 0, 
    const std::string& suffix = "png"
    )
{
    ewkino::SignalRegionInfo sr = ewkino::GetSignalRegionInfo(signal_region_name, analysis_type_name, signal_region_type_name);

    // charge type
    string charge_stem = "";
    switch (charge_type)
    {
    case 0 : charge_stem = ""; break;
    case 1 : charge_stem = "_pp"; break;
    case -1: charge_stem = "_mm"; break;
    }

    const string plots_path = Form("plots/%s/%s/%s/%s", output_name.c_str(), analysis_type_name.c_str(), signal_region_type_name.c_str(), sr.name.c_str());

    std::vector<std::string> vsignals;
    if (!signal_samples.empty()) {vsignals = rt::string_split(signal_samples);}    
    if (vsignals.empty()) {std::cout << "No signal samples provided." << std::endl;}

    std::vector<std::string> vbkgds;
    if (!bkgd_samples.empty() && bkgd_samples != "all") {vbkgds = rt::string_split(bkgd_samples);}
    else vbkgds.assign(bkgds_all, bkgds_all + arraysize(bkgds_all));    
    int num_bkgds = vbkgds.size();

    rt::TH1Container hc_bkgd;
    rt::TH1Container hc_top_bkgd;
    rt::TH1Container hc_vv_bkgd;
    rt::TH1Container hc_vvv_bkgd;
    rt::TH1Container hc_rare_top_bkgd;
    rt::TH1Container hc_qqww_bkgd;
    rt::TH1Container hc_higgs_bkgd;
    float total_bkgd = 0.;

    rt::TH1Container tmp_fake_container = rt::TH1Container(Form("%s/data%s.root", plots_path.c_str(), charge_stem.c_str()));

    for (unsigned int idx = 0; idx < vbkgds.size(); idx++)
    {
        if (std::find(vsignals.begin(), vsignals.end(), vbkgds.at(idx)) != vsignals.end()) continue;
        rt::TH1Container tmp_hist_container = rt::TH1Container(Form("%s/%s%s.root", plots_path.c_str(), vbkgds.at(idx).c_str(), charge_stem.c_str()));        
        total_bkgd += tmp_hist_container["h_yield_ll"]->Integral();
    }

    

    std::vector<std::string> vbkgd_names;
    if (!combine_bkgds) vbkgd_names = vbkgds;

    std::vector<rt::TH1Container> vhc_bkgds;
    if (!vbkgds.empty())
    {
        if (combine_bkgds)
        {
            for (unsigned int idx = 0; idx < vbkgds.size(); idx++)
            {
                if (std::find(vsignals.begin(), vsignals.end(), vbkgds.at(idx)) != vsignals.end()) continue;

                hc_bkgd = rt::TH1Container(Form("%s/%s%s.root", plots_path.c_str(), vbkgds.at(idx).c_str(), charge_stem.c_str()));

                if (normalize)
                    hc_bkgd.Scale(1./total_bkgd);

                if (vbkgds.at(idx).compare("ttdil") == 0 || vbkgds.at(idx).compare("ttslb") == 0 || vbkgds.at(idx).compare("ttslo") == 0 ||
                    vbkgds.at(idx).compare("ttotr") == 0 || vbkgds.at(idx).compare("t_tw") == 0 || vbkgds.at(idx).compare("t_schan") == 0 ||
                    vbkgds.at(idx).compare("t_tchan") == 0)
                    hc_top_bkgd += hc_bkgd;
                else if (vbkgds.at(idx).compare("ww") == 0 || vbkgds.at(idx).compare("wz") == 0 || vbkgds.at(idx).compare("zz") == 0 ||
                         vbkgds.at(idx).compare("wgstar2m") == 0 || vbkgds.at(idx).compare("wgstar2t") == 0)
                    hc_vv_bkgd += hc_bkgd;
                else if (vbkgds.at(idx).compare("www") == 0 || vbkgds.at(idx).compare("wwz") == 0 || vbkgds.at(idx).compare("wzz") == 0 ||
                         vbkgds.at(idx).compare("zzz") == 0 || vbkgds.at(idx).compare("wwg") == 0)
                    hc_vvv_bkgd += hc_bkgd;                    
                else if (vbkgds.at(idx).compare("wpwpqq") == 0 || vbkgds.at(idx).compare("wmwmqq") == 0 || vbkgds.at(idx).compare("ww_ds") == 0)
                    hc_qqww_bkgd += hc_bkgd;
                else if (vbkgds.at(idx).compare("ttw") == 0 || vbkgds.at(idx).compare("ttz") == 0 || vbkgds.at(idx).compare("tbz") == 0 ||
                         vbkgds.at(idx).compare("ttg") == 0 || vbkgds.at(idx).compare("ttww") == 0)
                    hc_rare_top_bkgd += hc_bkgd;
                else if (rt::string_contains(vbkgds.at(idx), "wh_zh_tth"))
                    hc_higgs_bkgd += hc_bkgd;
                else
                {
                    vhc_bkgds.push_back(hc_bkgd);
                    vbkgd_names.push_back(vbkgds.at(idx));
                }
            }

            vhc_bkgds.push_back(hc_vv_bkgd);
            vbkgd_names.push_back("VV");

            vhc_bkgds.push_back(hc_top_bkgd);
            vbkgd_names.push_back("top");

            vhc_bkgds.push_back(hc_vvv_bkgd);
            vbkgd_names.push_back("VVV");

            vhc_bkgds.push_back(hc_qqww_bkgd);
            vbkgd_names.push_back("qqWW");

            vhc_bkgds.push_back(hc_rare_top_bkgd);
            vbkgd_names.push_back("rare top");

            vhc_bkgds.push_back(hc_higgs_bkgd);
            vbkgd_names.push_back("higgs");
        }
        else
        {
            for (unsigned int idx = 0; idx < vbkgds.size(); idx++)
            {
                hc_bkgd.Clear();
                hc_bkgd = rt::TH1Container(Form("%s/%s%s.root", plots_path.c_str(), vbkgds.at(idx).c_str(), charge_stem.c_str()));
                if (normalize)
                    hc_bkgd.Scale(1./total_bkgd);
                vhc_bkgds.push_back(hc_bkgd);
            }
        }
    }
    else
    {
        if (combine_bkgds)
        {
            for (unsigned int idx = 0; idx < vbkgds.size(); idx++)
            {
                if (std::find(vsignals.begin(), vsignals.end(), vbkgds.at(idx)) != vsignals.end()) continue;

                hc_bkgd = rt::TH1Container(Form("%s/%s%s.root", plots_path.c_str(), vbkgds.at(idx).c_str(), charge_stem.c_str()));

                if (normalize)
                    hc_bkgd.Scale(1./total_bkgd);

                if (vbkgds.at(idx).compare("ttdil") == 0 || vbkgds.at(idx).compare("ttslb") == 0 || vbkgds.at(idx).compare("ttslo") == 0 ||
                    vbkgds.at(idx).compare("ttotr") == 0 || vbkgds.at(idx).compare("t_tw") == 0 || vbkgds.at(idx).compare("t_schan") == 0 ||
                    vbkgds.at(idx).compare("t_tchan") == 0)
                    hc_top_bkgd += hc_bkgd;
                else if (vbkgds.at(idx).compare("ww") == 0 || vbkgds.at(idx).compare("wz") == 0 || vbkgds.at(idx).compare("zz") == 0 ||
                         vbkgds.at(idx).compare("wgstar2m") == 0 || vbkgds.at(idx).compare("wgstar2t") == 0)
                    hc_vv_bkgd += hc_bkgd;
                else if (vbkgds.at(idx).compare("www") == 0 || vbkgds.at(idx).compare("wwz") == 0 || vbkgds.at(idx).compare("wzz") == 0 ||
                         vbkgds.at(idx).compare("zzz") == 0 || vbkgds.at(idx).compare("wwg") == 0)
                    hc_vvv_bkgd += hc_bkgd;                    
                else if (vbkgds.at(idx).compare("wpwpqq") == 0 || vbkgds.at(idx).compare("wmwmqq") == 0 || vbkgds.at(idx).compare("ww_ds") == 0)
                    hc_qqww_bkgd += hc_bkgd;
                else if (vbkgds.at(idx).compare("ttw") == 0 || vbkgds.at(idx).compare("ttz") == 0 || vbkgds.at(idx).compare("tbz") == 0 ||
                         vbkgds.at(idx).compare("ttg") == 0 || vbkgds.at(idx).compare("ttww") == 0)
                    hc_rare_top_bkgd += hc_bkgd;
                else if (rt::string_contains(vbkgds.at(idx), "wh_zh_tth"))
                    hc_higgs_bkgd += hc_bkgd;
                else
                {
                    vhc_bkgds.push_back(hc_bkgd);
                    vbkgd_names.push_back(vbkgds.at(idx));
                }
            }

            vhc_bkgds.push_back(hc_vv_bkgd);
            vbkgd_names.push_back("VV");

            vhc_bkgds.push_back(hc_top_bkgd);
            vbkgd_names.push_back("top");

            vhc_bkgds.push_back(hc_vvv_bkgd);
            vbkgd_names.push_back("VVV");

            vhc_bkgds.push_back(hc_qqww_bkgd);
            vbkgd_names.push_back("qqWW");

            vhc_bkgds.push_back(hc_rare_top_bkgd);
            vbkgd_names.push_back("rare top");

            vhc_bkgds.push_back(hc_higgs_bkgd);
            vbkgd_names.push_back("higgs");
        }
        else
        {
            std::vector<std::string> vbkgds_tmp(vbkgds);
            for (unsigned int idx = 0; idx < vbkgds_tmp.size(); idx++)
            {
                if (std::find(vsignals.begin(), vsignals.end(), vbkgds_tmp.at(idx)) != vsignals.end())
                {
                    vbkgds.erase(std::find(vbkgds.begin(), vbkgds.end(), vbkgds_tmp.at(idx)));
                    continue;
                }
                hc_bkgd.Clear();
                hc_bkgd = rt::TH1Container(Form("%s/%s%s.root", plots_path.c_str(), vbkgds_tmp.at(idx).c_str(), charge_stem.c_str()));
                if (normalize)
                    hc_bkgd.Scale(1./total_bkgd);
                vhc_bkgds.push_back(hc_bkgd);
            }
        }
    }

    std::vector<rt::TH1Container> vhc_signals;
    rt::TH1Container hc_signal;
    if (!vsignals.empty())
    {       
        if (combine_signals)
        {
            float tmp_integral = 0.;
            for (unsigned int idx = 0; idx < vsignals.size(); idx++)
            {
                rt::TH1Container tmp_hist_container = rt::TH1Container(Form("%s/%s%s.root", plots_path.c_str(), vsignals.at(0).c_str(), charge_stem.c_str()));
                tmp_integral += tmp_hist_container["h_yield_ll"]->Integral();
            }

            for (unsigned int idx = 0; idx < vsignals.size(); idx++)
            {
                if (normalize)
                {
                    rt::TH1Container tmp_hist_container = rt::TH1Container(Form("%s/%s%s.root", plots_path.c_str(), vsignals.at(0).c_str(), charge_stem.c_str()));
                    tmp_hist_container.Scale(1./tmp_integral);
                    hc_signal += tmp_hist_container;
                }
                else
                    hc_signal += rt::TH1Container(Form("%s/%s%s.root", plots_path.c_str(), vsignals.at(idx).c_str(), charge_stem.c_str()));
            }
            vhc_signals.push_back(hc_signal);
        }
        else
        {
            for (unsigned int idx = 0; idx < vsignals.size(); idx++)
            {
                hc_signal.Clear();
                hc_signal = rt::TH1Container(Form("%s/%s%s.root", plots_path.c_str(), vsignals.at(idx).c_str(), charge_stem.c_str()));
                if (normalize)
                {
                    // hc_signal.Normalize();
                    float tmp_integral = hc_signal["h_yield_ll"]->Integral();
                    hc_signal.Scale(1./tmp_integral);
                }
                vhc_signals.push_back(hc_signal);
            }
        }
    }

    std::cout << std::endl;
    std::cout << "Considering the following signals:" << std::endl;
    for (unsigned int idx = 0; idx < vsignals.size(); idx++)
        std::cout << "\t" << vsignals.at(idx) << std::endl;
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "Considering the following backgrounds:" << std::endl;
    for (unsigned int idx = 0; idx < vbkgds.size(); idx++)
        std::cout << "\t" << vbkgds.at(idx) << std::endl;
    std::cout << std::endl;
        
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
    p["p_yield"             ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "yield"             , Form("%s;channel;Events"                    , title.c_str()), "sb::off dt::stack lg::left" );
    p["p_dilep_mass"        ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "dilep_mass"        , Form("%s;m_{ll} (GeV);Events"               , title.c_str()), "sb::off dt::stack lg::right");
    p["p_pt1"               ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "pt1"               , Form("%s;p^{lep1}_{T} (GeV);Events"         , title.c_str()), "sb::off dt::stack lg::right");
    p["p_pt2"               ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "pt2"               , Form("%s;p^{lep2}_{T} (GeV);Events"         , title.c_str()), "sb::off dt::stack lg::right");
    p["p_pt1_el"            ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "pt1_el"            , Form("%s;p^{lep1}_{T} (GeV);Events"         , title.c_str()), "sb::off dt::stack lg::right");
    p["p_pt2_el"            ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "pt2_el"            , Form("%s;p^{lep2}_{T} (GeV);Events"         , title.c_str()), "sb::off dt::stack lg::right");
    p["p_pt1_mu"            ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "pt1_mu"            , Form("%s;p^{lep1}_{T} (GeV);Events"         , title.c_str()), "sb::off dt::stack lg::right");
    p["p_pt2_mu"            ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "pt2_mu"            , Form("%s;p^{lep2}_{T} (GeV);Events"         , title.c_str()), "sb::off dt::stack lg::right");
    p["p_met"               ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "met"               , Form("%s;E^{miss}_{T} (GeV);Events"         , title.c_str()), "sb::off dt::stack lg::right");
    p["p_ht"                ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "ht"                , Form("%s;H_{T} (GeV);Events"                , title.c_str()), "sb::off dt::stack lg::right");
    p["p_mt"                ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "mt"                , Form("%s;m_{T} (GeV);Events"                , title.c_str()), "sb::off dt::stack lg::right");
    p["p_njets"             ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "njets"             , Form("%s;number of jets;Events"             , title.c_str()), "sb::off dt::stack lg::right");
    p["p_lepdphi"           ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "lepdphi"           , Form("%s;#Delta#Phi(lep1, lep2);Events"     , title.c_str()), "sb::off dt::stack lg::right");
    p["p_lepdeta"           ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "lepdeta"           , Form("%s;#Delta#eta(lep1, lep2);Events"     , title.c_str()), "sb::off dt::stack lg::right");
    p["p_lepdr"             ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "lepdr"             , Form("%s;#DeltaR(lep1, lep2);Events"        , title.c_str()), "sb::off dt::stack lg::right");
    p["p_ptjetlep"          ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "ptjetlep"          , Form("%s;jet p_{T} / lep p_{T} - 1;Events"  , title.c_str()), "sb::off dt::stack lg::right");
    p["p_ml3l"              ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "ml3l"              , Form("%s;M(l,3l);Events"                    , title.c_str()), "sb::off dt::stack lg::right");
    p["p_ml3ldr"            ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "ml3ldr"            , Form("%s;#DeltaR(l,3l);Events"              , title.c_str()), "sb::off dt::stack lg::right");
    p["p_jet1_pt"           ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "jet1_pt"           , Form("%s;p^{jet1}_{T} (GeV);Events"         , title.c_str()), "sb::off dt::stack lg::right");    
    p["p_jet2_pt"           ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "jet2_pt"           , Form("%s;p^{jet2}_{T} (GeV);Events"         , title.c_str()), "sb::off dt::stack lg::right");    
    p["p_jet3_pt"           ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "jet3_pt"           , Form("%s;p^{jet3}_{T} (GeV);Events"         , title.c_str()), "sb::off dt::stack lg::right");        
    p["p_mjj"               ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "mjj"               , Form("%s;M_{jj} (GeV);Events"               , title.c_str()), "sb::off dt::stack lg::right");        
    p["p_dijet_dphi"        ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "dijet_dphi"        , Form("%s;#Delta#phi_{jj};Events"            , title.c_str()), "sb::off dt::stack lg::right");
    p["p_dijet_deta"        ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "dijet_deta"        , Form("%s;#Delta#eta_{jj};Events"            , title.c_str()), "sb::off dt::stack lg::right");
    p["p_dijet_dr"          ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "dijet_dr"          , Form("%s;#DeltaR_{jj};Events"               , title.c_str()), "sb::off dt::stack lg::right");
    p["p_nlbtags"           ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "nlbtags"           , Form("%s;number of loose btags;Events"      , title.c_str()), "sb::off dt::stack lg::right");
    p["p_nmbtags"           ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "nmbtags"           , Form("%s;number of medium btags;Events"     , title.c_str()), "sb::off dt::stack lg::right");
    p["p_ntbtags"           ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "ntbtags"           , Form("%s;number of tight btags;Events"      , title.c_str()), "sb::off dt::stack lg::right");
    p["p_htpv"              ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "htpv"              , Form("%s;PV H_{T} (GeV);Events"             , title.c_str()), "sb::off dt::stack lg::right");
    p["p_mt2"               ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "mt2"               , Form("%s;m_{T2} (GeV);Events"               , title.c_str()), "sb::off dt::stack lg::right");
    p["p_lep1_mt"           ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "lep1_mt"           , Form("%s;lep1 m_{T} (GeV);Events"           , title.c_str()), "sb::off dt::stack lg::right");
    p["p_lep2_mt"           ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "lep2_mt"           , Form("%s;lep2 m_{T} (GeV);Events"           , title.c_str()), "sb::off dt::stack lg::right");
    p["p_dijet_pt"          ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "dijet_pt"          , Form("%s;p^{jj}_{T} (GeV);Events"           , title.c_str()), "sb::off dt::stack lg::right");
    p["p_dijet_eta"         ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "dijet_eta"         , Form("%s;#eta_{jj};Events"                  , title.c_str()), "sb::off dt::stack lg::right");
    p["p_pt3"               ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "pt3"               , Form("%s;p^{lep3}_{T} (GeV);Events"         , title.c_str()), "sb::off dt::stack lg::right");
    p["p_pt3_el"            ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "pt3_el"            , Form("%s;p^{lep3}_{T} (GeV);Events"         , title.c_str()), "sb::off dt::stack lg::right");
    p["p_pt3_mu"            ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "pt3_mu"            , Form("%s;p^{lep3}_{T} (GeV);Events"         , title.c_str()), "sb::off dt::stack lg::right");
    p["p_dilep_pt"          ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "dilep_pt"          , Form("%s;p^{ll}_{T} (GeV);Events"           , title.c_str()), "sb::off dt::stack lg::right");
    p["p_dilep_eta"         ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "dilep_eta"         , Form("%s;#eta_{ll};Events"                  , title.c_str()), "sb::off dt::stack lg::right");
    p["p_dijet_pt_mass"     ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "dijet_pt_mass"     , Form("%s;p^{jj}_{T}/M_{jj};Events"          , title.c_str()), "sb::off dt::stack lg::right");
    p["p_max_mt"            ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "max_mt"            , Form("%s;m_{T} (GeV);Events"                , title.c_str()), "sb::off dt::stack lg::right");
    p["p_isotrk_veto"       ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "isotrk_veto"       , Form("%s;iso trk veto;Events"               , title.c_str()), "sb::off dt::stack lg::right");
    p["p_tau_veto"          ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "tau_veto"          , Form("%s;tau veto;Events"                   , title.c_str()), "sb::off dt::stack lg::right");
    p["p_dphi_met_ll"       ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "dphi_met_ll"       , Form("%s;#Delta#phi(ll,met);Events"         , title.c_str()), "sb::off dt::stack lg::right");
    p["p_dphi_met_jj"       ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "dphi_met_jj"       , Form("%s;#Delta#phi(jj,met);Events"         , title.c_str()), "sb::off dt::stack lg::right");
    p["p_min_dphi_met_lep"  ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "min_dphi_met_lep"  , Form("%s;min #Delta#phi(lep,met);Events"    , title.c_str()), "sb::off dt::stack lg::right");
    p["p_max_dphi_met_lep"  ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "max_dphi_met_lep"  , Form("%s;max #Delta#phi(lep,met);Events"    , title.c_str()), "sb::off dt::stack lg::right");
    p["p_min_dphi_met_jet"  ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "min_dphi_met_jet"  , Form("%s;min #Delta#phi(jet,met);Events"    , title.c_str()), "sb::off dt::stack lg::right");
    p["p_max_dphi_met_jet"  ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "max_dphi_met_jet"  , Form("%s;max #Delta#phi(jet,met);Events"    , title.c_str()), "sb::off dt::stack lg::right");
    p["p_didphi"            ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "didphi"            , Form("%s;#Delta#phi(ll,jj);Events"          , title.c_str()), "sb::off dt::stack lg::right");
    p["p_dideta"            ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "dideta"            , Form("%s;#Delta#eta(ll,jj);Events"          , title.c_str()), "sb::off dt::stack lg::right");
    p["p_didr"              ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "didr"              , Form("%s;#DeltaR(ll,jj);Events"             , title.c_str()), "sb::off dt::stack lg::right");
    p["p_dijet_lep_mass"    ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "dijet_lep_mass"    , Form("%s;M_{jjl} (GeV);Events"              , title.c_str()), "sb::off dt::stack lg::right");
    p["p_min_dijet_lep_mass"] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "min_dijet_lep_mass", Form("%s;min M_{jjl} (GeV);Events"          , title.c_str()), "sb::off dt::stack lg::right");
    p["p_dijet_mass_pt_dr"  ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "dijet_mass_pt_dr"  , Form("%s;M_{jj}/p^{jj}_{T}/#DeltaR_{jj};Events"       , title.c_str()), "sb::off dt::stack lg::right");
    p["p_minjpt_jjpt"       ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "minjpt_jjpt"       , Form("%s;min(p^{j1}_{T},p^{j2}_{t})/p^{jj}_{T};Events", title.c_str()), "sb::off dt::stack lg::right");
    p["p_dijet_mass_pt_dr"  ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "dijet_mass_pt_dr"  , Form("%s;M_{jj}/p^{jj}_{T}/#DeltaR_{jj};Events"       , title.c_str()), "sb::off dt::stack lg::right");
    p["p_minjpt_jjpt"       ] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "minjpt_jjpt"       , Form("%s;min(p^{j1}_{T},p^{j2}_{t})/p^{jj}_{T};Events", title.c_str()), "sb::off dt::stack lg::right");

    // overlay individual channels
    for (size_t i = 1; i != at::DileptonHypType::static_size; i++)
    {
        at::DileptonHypType::value_type hyp_type = static_cast<at::DileptonHypType::value_type>(i);

        // name and title suffixes
        string hn = Form("_%s" ,  GetDileptonHypTypeName(hyp_type).c_str());
        //string ht = Form(" (%s)",  GetDileptonHypTypeTitle(hyp_type).c_str());

        p["p_dilep_mass"+hn] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "dilep_mass"+hn , Form("%s;m_{ll} (GeV);Events"             , title.c_str()), "sb::off dt::stack lg::right");
        p["p_pt1"       +hn] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "pt1"       +hn , Form("%s;p^{lep1}_{T} (GeV);Events"       , title.c_str()), "sb::off dt::stack lg::right");
        p["p_pt2"       +hn] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "pt2"       +hn , Form("%s;p^{lep2}_{T} (GeV);Events"       , title.c_str()), "sb::off dt::stack lg::right");
        p["p_met"       +hn] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "met"       +hn , Form("%s;E^{miss}_{T} (GeV);Events"       , title.c_str()), "sb::off dt::stack lg::right");
        p["p_ht"        +hn] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "ht"        +hn , Form("%s;H_{T} (GeV);Events"              , title.c_str()), "sb::off dt::stack lg::right");
        p["p_mt"        +hn] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "mt"        +hn , Form("%s;m_{T} (GeV);Events"              , title.c_str()), "sb::off dt::stack lg::right");
        p["p_lep1_mt"   +hn] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "lep1_mt"   +hn , Form("%s;lep1 m_{T} (GeV);Events"         , title.c_str()), "sb::off dt::stack lg::right");
        p["p_lep2_mt"   +hn] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "lep2_mt"   +hn , Form("%s;lep2 m_{T} (GeV);Events"         , title.c_str()), "sb::off dt::stack lg::right");
        p["p_pt3"       +hn] = CreateOverlay(vhc_signals, vsignals, vhc_bkgds, vbkgd_names, "pt3"       +hn , Form("%s;p^{lep3}_{T} (GeV);Events"       , title.c_str()), "sb::off dt::stack lg::right");
    }

    // SR label
    TLatex t1_upper_left (0.17, 0.85, Form("%s: %s", sr.name.c_str(), sr.title.c_str())); 
    TLatex t1_upper_right(0.17, 0.85, Form("%s: %s", sr.name.c_str(), sr.title.c_str())); 
    t1_upper_left.SetTextSize(0.027);
    t1_upper_right.SetTextSize(0.027);
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
    std::string plots_subdir = normalize ? "kin_mc_norm" : "kin_mc";
    rt::Print(p, Form("%s/%s", plots_path.c_str(), plots_subdir.c_str()), suffix, /*option = */"", /*logy = */false);
    // rt::Print(p, Form("%s/%s", plots_path.c_str(), plots_subdir.c_str()), suffix, /*option = */"", /*logy = */false, /*normalize = */normalize);

    // print yield explicitly
    // this is a kludge to the the x error bars the right size for the yeild plot
    gStyle->SetErrorX(0.3);
    rt::Print(p["p_yield"], Form("%s/%s/p_yield", plots_path.c_str(), plots_subdir.c_str()), suffix, /*option = */"", /*logy = */false);
    gStyle->SetErrorX();
}
