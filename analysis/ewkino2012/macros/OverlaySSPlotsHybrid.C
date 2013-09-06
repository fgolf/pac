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
const std::string rare_bkgds[] = {
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
    "wh_zh_tth_hww",
    "wh_zh_tth_hzz",
    "wh_zh_tth_htt"
};

const Int_t colors[] = {2,3,4,5,6,7,8,9,28,30,38,40,41,42,46,kRed+2,kGreen+2,kBlue+2,kMagenta+2,kCyan+2};
const Int_t markers[] = {1, 2, 3, 4, 5, 6};

bool my_sort_function_lin(TH1* h1, TH1* h2)
{
    return (h1->Integral() > h2->Integral());
}

bool my_sort_function_log(TH1* h1, TH1* h2)
{
    return (h1->Integral() < h2->Integral());
}

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
    rt::TH1Container& hc_data, 
    std::vector<rt::TH1Container>& vhc_rare,
    std::vector<std::string>& vhc_rare_names,
    std::vector<rt::TH1Container>& vhc_signal,
    std::vector<std::string>& vhc_signal_names,
    const std::string& hist_stem,
    const std::string& title,
    std::string option = "sb::off dt::stack lg::top_right"
    )
{
    // legend tweaks
    rt::TH1Overlay::legend_width_default            = 0.25;
    rt::TH1Overlay::legend_height_per_entry_default = 0.035;
    rt::TH1Overlay::legend_text_size_default        = 0.025;
    rt::TH1Overlay::legend_offset_default           = 0.010;

    // colors
    const Color_t signal_color  = kBlack;
    const Color_t fake_color    = kRed-6;
    const Color_t flip_color    = kOrange-8;
    const float line_size       = 4;
    const Style_t shade_style   = 3335;
    const string flip_legend    = "Charge Mismeasurement";
    const string fake_legend    = "Fake Leptons";
    const string unc_legend     = "Total Uncertainty";

    TH1* h_fake  = hc_data[Form("h_%s_fake", hist_stem.c_str())];
    TH1* h_flip  = hc_data[Form("h_%s_flip", hist_stem.c_str())];   
    TH1* h_spil  = NULL;
    for (unsigned int idx = 0; idx < vhc_rare.size(); idx++)
    {
       TH1* hist_temp = vhc_rare.at(idx)[Form("h_%s_fake", hist_stem.c_str())];
       if (idx == 0)
       {
           h_spil = dynamic_cast<TH1*>(hist_temp->Clone());
       }
       else
       {
           h_spil->Add(hist_temp);
       }
    }
    assert(h_spil != NULL);
    h_fake->Add(h_spil, -1.0);    

    std::vector<TH1*> vsignals;
    for (unsigned int idx = 0; idx < vhc_signal.size(); idx++)
    {
        vsignals.push_back(vhc_signal.at(idx)[Form("h_%s_ss", hist_stem.c_str())]);
    }
    assert(vsignals.size() == vhc_signal_names.size());
    
    std::vector<TH1*> vrares;
    TH1* h_rare = NULL;
    for (unsigned int idx = 0; idx < vhc_rare.size(); idx++)
    {
       TH1* hist_temp = vhc_rare.at(idx)[Form("h_%s_ss", hist_stem.c_str())];
       vrares.push_back(hist_temp);
       if (idx == 0)
       {
           h_rare = dynamic_cast<TH1*>(hist_temp->Clone());
       }
       else
       {
           h_rare->Add(hist_temp);
       }
    }
    assert(h_rare != NULL); 
    assert(vrares.size() == vhc_rare_names.size());

    TH1* h_pred = GetTotalPredHist(h_fake, h_flip, h_rare);

    if (hist_stem == "yield")
    {
        option.append(" B");
        const float width = 0.6;
        const float offset = 0.2;
        const float label_size = 0.07;

        h_fake->SetBarWidth(width);
        h_flip->SetBarWidth(width);
        h_rare->SetBarWidth(width);
        h_pred->SetBarWidth(width);
        h_fake->SetBarOffset(offset);
        h_flip->SetBarOffset(offset);
        h_rare->SetBarOffset(offset);
        h_pred->SetBarOffset(offset);
        h_fake->SetLabelSize(label_size);
        h_flip->SetLabelSize(label_size);
        h_rare->SetLabelSize(label_size);
        h_pred->SetLabelSize(label_size);

        for (unsigned int idx = 0; idx < vsignals.size(); idx++)
        {
            vsignals.at(idx)->SetBarWidth(width);
            vsignals.at(idx)->SetBarOffset(offset);
            vsignals.at(idx)->SetLabelSize(label_size);
        }

        for (unsigned int idx = 0; idx < vrares.size(); idx++)
        {
            vrares.at(idx)->SetBarWidth(width);
            vrares.at(idx)->SetBarOffset(offset);
            vrares.at(idx)->SetLabelSize(label_size);
        }
    }

    rt::TH1Overlay p(title, option);

    for (unsigned int idx = 0; idx < vrares.size(); idx++)
    {
        p.Add(vrares.at(idx), vhc_rare_names.at(idx), colors[idx]);
    }

    p.Add(h_fake, fake_legend, fake_color);
    p.Add(h_flip, flip_legend, flip_color);

    for (unsigned int idx = 0; idx < vsignals.size(); idx++)
    {
        TH1* hist_temp = vsignals.at(idx);
        std::string hist_option = (hist_stem == "yield") ? "" : "hist";
        hist_temp->SetOption(hist_option.c_str());
        p.Add(hist_temp, /*no_stack=*/true, vhc_signal_names.at(idx), signal_color, line_size, markers[idx]);
    }

    p.Add(h_pred, /*no_stack=*/true, unc_legend, 1, 2, 1, shade_style); 
    p.SetYAxisRange(0.0, h_pred->GetMaximum());
    return p;
}

// Overlay the kinematic plots
void OverlaySSPlotsHybrid
(
    float lumi, 
    const std::string& output_name, 
    const std::string& signal_region_name, 
    const std::string& analysis_type_name,
    const std::string& signal_samples,
    bool combine_signals = false,
    bool categorize_rare = false,
    bool combine_rare = false,
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

    rt::TH1Container hc_data(Form("%s/data%s.root", plots_path.c_str(), charge_stem.c_str()));

    std::vector<std::string> vsignals;
    if (!signal_samples.empty()) {vsignals = rt::string_split(signal_samples);}    
    if (vsignals.empty()) {std::cout << "No signal samples provided." << std::endl;}

    std::vector<std::string> vrares;
    vrares.assign(rare_bkgds, rare_bkgds + arraysize(rare_bkgds));    

    rt::TH1Container hc_mc;
    rt::TH1Container hc_top_bkgd;
    rt::TH1Container hc_vv_bkgd;
    rt::TH1Container hc_vvv_bkgd;
    rt::TH1Container hc_qqww_bkgd;
    rt::TH1Container hc_higgs_bkgd;

    std::vector<rt::TH1Container> vhc_rare;
    std::vector<std::string> vrare_names;    
    if (combine_rare)
    {
        for (unsigned int idx = 0; idx < vrares.size(); idx++)
        {
            hc_mc += rt::TH1Container(Form("%s/%s%s.root", plots_path.c_str(), vrares.at(idx).c_str(), charge_stem.c_str()));
        }

        vhc_rare.push_back(hc_mc);
        vrare_names.push_back("Genuine SM SS");
    }
    else if (categorize_rare)
    {
        for (unsigned int idx = 0; idx < vrares.size(); idx++)
        {
            hc_mc = rt::TH1Container(Form("%s/%s%s.root", plots_path.c_str(), vrares.at(idx).c_str(), charge_stem.c_str()));

            if (vrares.at(idx).compare("wz") == 0 || vrares.at(idx).compare("zz") == 0 ||
                vrares.at(idx).compare("wgstar2m") == 0 || vrares.at(idx).compare("wgstar2t") == 0 ||
                vrares.at(idx).compare("ww_ds") == 0)
            {
                hc_vv_bkgd += hc_mc;
            }
            else if (vrares.at(idx).compare("www") == 0 || vrares.at(idx).compare("wwz") == 0 || vrares.at(idx).compare("wzz") == 0 ||
                     vrares.at(idx).compare("zzz") == 0 || vrares.at(idx).compare("wwg") == 0)
            {
                hc_vvv_bkgd += hc_mc;
            }
            else if (vrares.at(idx).compare("wpwpqq") == 0 || vrares.at(idx).compare("wmwmqq") == 0)
            {
                hc_qqww_bkgd += hc_mc;
            }
            else if (vrares.at(idx).compare("ttw") == 0 || vrares.at(idx).compare("ttz") == 0 || vrares.at(idx).compare("tbz") == 0 ||
                     vrares.at(idx).compare("ttg") == 0 || vrares.at(idx).compare("ttww") == 0)
            {
                hc_top_bkgd += hc_mc;
            }
            else if (rt::string_contains(vrares.at(idx), "wh_zh_tth"))
            {
                hc_higgs_bkgd += hc_mc;
            }
            else
            {
                std::cout << "Found a rare sample that I don't know how to categorize!" << endl;
            }
        }

        vhc_rare.push_back(hc_vv_bkgd);
        vrare_names.push_back("VV");

        vhc_rare.push_back(hc_top_bkgd);
        vrare_names.push_back("top");

        vhc_rare.push_back(hc_vvv_bkgd);
        vrare_names.push_back("VVV");

        vhc_rare.push_back(hc_qqww_bkgd);
        vrare_names.push_back("qqWW");

        vhc_rare.push_back(hc_higgs_bkgd);
        vrare_names.push_back("higgs");
    }
    else
    {
        for (unsigned int idx = 0; idx < vrares.size(); idx++)
        {
            hc_mc.Clear();
            hc_mc = rt::TH1Container(Form("%s/%s%s.root", plots_path.c_str(), vrares.at(idx).c_str(), charge_stem.c_str()));
            vhc_rare.push_back(hc_mc);
        }
            
        vrare_names = vrares;
    }

    std::vector<rt::TH1Container> vhc_signals;
    rt::TH1Container hc_signal;
    if (!vsignals.empty())
    {       
        if (combine_signals)
        {
            for (unsigned int idx = 0; idx < vsignals.size(); idx++)
            {
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
    for (unsigned int idx = 0; idx < vrares.size(); idx++)
        std::cout << "\t" << vrares.at(idx) << std::endl;
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

    std::string loption = Form("sb::off %s lg::top_left" , normalize ? "dt::stack_norm" : "dt::stack");
    std::string roption = Form("sb::off %s lg::top_right", normalize ? "dt::stack_norm" : "dt::stack");

    // overlays
    map<string, rt::TH1Overlay> p;
    rt::TH1Overlay::profile_marker_size_default = 10.0;
    p["p_yield"           ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "yield"           , Form("%s;channel;Events"                              , title.c_str()), loption);
    p["p_dilep_mass"      ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "dilep_mass"      , Form("%s;m_{ll} [GeV];Events"                         , title.c_str()), roption);
    p["p_pt1"             ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "pt1"             , Form("%s;p^{lep1}_{T} [GeV];Events"                   , title.c_str()), roption);
    p["p_pt2"             ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "pt2"             , Form("%s;p^{lep2}_{T} [GeV];Events"                   , title.c_str()), roption);
    p["p_pt1_el"          ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "pt1_el"          , Form("%s;p^{lep1}_{T} [GeV];Events"                   , title.c_str()), roption);
    p["p_pt2_el"          ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "pt2_el"          , Form("%s;p^{lep2}_{T} [GeV];Events"                   , title.c_str()), roption);
    p["p_pt1_mu"          ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "pt1_mu"          , Form("%s;p^{lep1}_{T} [GeV];Events"                   , title.c_str()), roption);
    p["p_pt2_mu"          ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "pt2_mu"          , Form("%s;p^{lep2}_{T} [GeV];Events"                   , title.c_str()), roption);
    p["p_met"             ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "met"             , Form("%s;E^{miss}_{T} [GeV];Events"                   , title.c_str()), roption);
    p["p_ht"              ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "ht"              , Form("%s;H_{T} [GeV];Events"                          , title.c_str()), roption);
    p["p_mt"              ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "mt"              , Form("%s;m_{T} [GeV];Events"                          , title.c_str()), roption);
    p["p_njets"           ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "njets"           , Form("%s;number of jets;Events"                       , title.c_str()), roption);
    p["p_lepdphi"         ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "lepdphi"         , Form("%s;#Delta#Phi(lep1, lep2);Events"               , title.c_str()), roption);
    p["p_lepdeta"         ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "lepdeta"         , Form("%s;#Delta#eta(lep1, lep2);Events"               , title.c_str()), roption);
    p["p_lepdr"           ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "lepdr"           , Form("%s;#DeltaR(lep1, lep2);Events"                  , title.c_str()), roption);
    p["p_ptjetlep"        ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "ptjetlep"        , Form("%s;jet p_{T} / lep p_{T} - 1;Events"            , title.c_str()), roption);
    p["p_ml3l"            ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "ml3l"            , Form("%s;M(l,3l);Events"                              , title.c_str()), roption);
    p["p_ml3ldr"          ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "ml3ldr"          , Form("%s;#DeltaR(l,3l);Events"                        , title.c_str()), roption);
    p["p_jet1_pt"         ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "jet1_pt"         , Form("%s;p^{jet1}_{T} [GeV];Events"                   , title.c_str()), roption);    
    p["p_jet2_pt"         ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "jet2_pt"         , Form("%s;p^{jet2}_{T} [GeV];Events"                   , title.c_str()), roption);    
    p["p_jet3_pt"         ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "jet3_pt"         , Form("%s;p^{jet3}_{T} [GeV];Events"                   , title.c_str()), roption);        
    p["p_mjj"             ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "mjj"             , Form("%s;M_{jj} [GeV];Events"                         , title.c_str()), loption);
    p["p_dijet_dphi"      ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "dijet_dphi"      , Form("%s;#Delta#phi_{jj};Events"                      , title.c_str()), roption);
    p["p_dijet_deta"      ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "dijet_deta"      , Form("%s;#Delta#eta_{jj};Events"                      , title.c_str()), roption);
    p["p_dijet_dr"        ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "dijet_dr"        , Form("%s;#DeltaR_{jj};Events"                         , title.c_str()), roption);
    p["p_nlbtags"         ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "nlbtags"         , Form("%s;# CSVL btags;Events"                         , title.c_str()), roption);
    p["p_nmbtags"         ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "nmbtags"         , Form("%s;# CSVM btags;Events"                         , title.c_str()), roption);
    p["p_ntbtags"         ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "ntbtags"         , Form("%s;# CSVT btags;Events"                         , title.c_str()), roption);
    p["p_htpv"            ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "htpv"            , Form("%s;PV H_{T} [GeV];Events"                       , title.c_str()), roption);
    p["p_mt2"             ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "mt2"             , Form("%s;m_{T2} [GeV];Events"                         , title.c_str()), roption);
    p["p_mt2j"            ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "mt2j"            , Form("%s;m_{T2J} [GeV];Events"                        , title.c_str()), roption);
    p["p_lep1_mt"         ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "lep1_mt"         , Form("%s;lep1 m_{T} [GeV];Events"                     , title.c_str()), roption);
    p["p_lep2_mt"         ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "lep2_mt"         , Form("%s;lep2 m_{T} [GeV];Events"                     , title.c_str()), roption);
    p["p_dijet_pt"        ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "dijet_pt"        , Form("%s;p^{jj}_{T} [GeV];Events"                     , title.c_str()), roption);
    p["p_dijet_eta"       ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "dijet_eta"       , Form("%s;#eta_{jj};Events"                            , title.c_str()), roption);
    p["p_pt3"             ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "pt3"             , Form("%s;p^{lep3}_{T} [GeV];Events"                   , title.c_str()), roption);
    p["p_pt3_el"          ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "pt3_el"          , Form("%s;p^{lep3}_{T} [GeV];Events"                   , title.c_str()), roption);
    p["p_pt3_mu"          ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "pt3_mu"          , Form("%s;p^{lep3}_{T} [GeV];Events"                   , title.c_str()), roption);
    p["p_dilep_pt"        ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "dilep_pt"        , Form("%s;p^{ll}_{T} [GeV];Events"                     , title.c_str()), roption);
    p["p_dilep_eta"       ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "dilep_eta"       , Form("%s;#eta_{ll};Events"                            , title.c_str()), roption);
    p["p_dijet_pt_mass"   ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "dijet_pt_mass"   , Form("%s;p^{jj}_{T}/M_{jj};Events"                    , title.c_str()), roption);
    p["p_max_mt"          ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "max_mt"          , Form("%s;m_{T} [GeV];Events"                          , title.c_str()), loption);
    p["p_isotrk_veto"     ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "isotrk_veto"     , Form("%s;iso trk veto;Events"                         , title.c_str()), loption);
    p["p_tau_veto"        ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "tau_veto"        , Form("%s;tau veto;Events"                             , title.c_str()), loption);
    p["p_dphi_met_ll"     ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "dphi_met_ll"     , Form("%s;#Delta#phi(ll,met);Events"                   , title.c_str()), loption);
    p["p_dphi_met_jj"     ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "dphi_met_jj"     , Form("%s;#Delta#phi(jj,met);Events"                   , title.c_str()), loption);
    p["p_min_dphi_met_lep"] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "min_dphi_met_lep", Form("%s;min #Delta#phi(lep,met);Events"              , title.c_str()), roption);
    p["p_max_dphi_met_lep"] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "max_dphi_met_lep", Form("%s;max #Delta#phi(lep,met);Events"              , title.c_str()), loption);
    p["p_min_dphi_met_jet"] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "min_dphi_met_jet", Form("%s;min #Delta#phi(jet,met);Events"              , title.c_str()), roption);
    p["p_max_dphi_met_jet"] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "max_dphi_met_jet", Form("%s;max #Delta#phi(jet,met);Events"              , title.c_str()), loption);
    p["p_didphi"          ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "didphi"          , Form("%s;#Delta#phi(ll,jj);Events"                    , title.c_str()), roption);
    p["p_dideta"          ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "dideta"          , Form("%s;#Delta#eta(ll,jj);Events"                    , title.c_str()), roption);
    p["p_didr"            ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "didr"            , Form("%s;#DeltaR(ll,jj);Events"                       , title.c_str()), roption);
    p["p_dijet_mass_pt_dr"] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "dijet_mass_pt_dr", Form("%s;M_{jj}/p^{jj}_{T}/#DeltaR_{jj};Events"       , title.c_str()), roption);
    p["p_minjpt_jjpt"     ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "minjpt_jjpt"     , Form("%s;min(p^{j1}_{T},p^{j2}_{t})/p^{jj}_{T};Events", title.c_str()), roption);
    p["p_dijet_lep_mass"  ] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "dijet_lep_mass"  , Form("%s;M_{jjl} [GeV];Events"                        , title.c_str()), roption);
    p["p_min_dijet_lep_mass"] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "min_dijet_lep_mass"  , Form("%s;min M_{jjl} [GeV];Events"              , title.c_str()), roption);

    // overlay individual channels
    for (size_t i = 1; i != at::DileptonHypType::static_size; i++)
    {
        at::DileptonHypType::value_type hyp_type = static_cast<at::DileptonHypType::value_type>(i);

        // name and title suffixes
        string hn = Form("_%s" ,  GetDileptonHypTypeName(hyp_type).c_str());

        p["p_dilep_mass"+hn] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "dilep_mass"+hn , Form("%s;m_{ll} [GeV];Events"      , title.c_str()), roption);
        p["p_pt1"       +hn] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "pt1"       +hn , Form("%s;p^{lep1}_{T} [GeV];Events", title.c_str()), roption);
        p["p_pt2"       +hn] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "pt2"       +hn , Form("%s;p^{lep2}_{T} [GeV];Events", title.c_str()), roption);
        p["p_met"       +hn] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "met"       +hn , Form("%s;E^{miss}_{T} [GeV];Events", title.c_str()), roption);
        p["p_ht"        +hn] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "ht"        +hn , Form("%s;H_{T} [GeV];Events"       , title.c_str()), roption);
        p["p_mt"        +hn] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "mt"        +hn , Form("%s;m_{T} [GeV];Events"       , title.c_str()), roption);
        p["p_lep1_mt"   +hn] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "lep1_mt"   +hn , Form("%s;lep1 m_{T} [GeV];Events"  , title.c_str()), roption);
        p["p_lep2_mt"   +hn] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "lep2_mt"   +hn , Form("%s;lep2 m_{T} [GeV];Events"  , title.c_str()), roption);
        p["p_pt3"       +hn] = CreateOverlay(hc_data, vhc_rare, vrare_names, vhc_signals, vsignals, "pt3"       +hn , Form("%s;p^{lep3}_{T} [GeV];Events", title.c_str()), roption);
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
    std::string plots_subdir = normalize ? "kin_hybrid_norm" : "kin_hybrid";
    rt::Print(p, Form("%s/%s", plots_path.c_str(), plots_subdir.c_str()), suffix, /*option = */"", /*logy = */false);

    // print yield explicitly
    // this is a kludge to the the x error bars the right size for the yeild plot
    gStyle->SetErrorX(0.3);
    rt::Print(p["p_yield"], Form("%s/%s/p_yield", plots_path.c_str(), plots_subdir.c_str()), suffix, /*option = */"", /*logy = */false);
    gStyle->SetErrorX();
}
