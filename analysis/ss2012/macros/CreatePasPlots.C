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
#include "SSYields.h"
#include "ScaleFactors.h"

using namespace std;

// combine the contributions for the background predictions
TH1F* GetTotalPredHist(TH1* h_fake, TH1* h_flip, TH1* h_mc)
{
    string hist_name = rt::string_replace_all(h_fake->GetName(), "_fake", "_pred");
    TH1F* h_pred = dynamic_cast<TH1F*>(h_fake->Clone(hist_name.c_str()));
    h_pred->Add(h_flip);
    h_pred->Add(h_mc);
    return h_pred;
}

rt::TH1Container GetPasPlots
(
    rt::TH1Container& hc_data, 
    rt::TH1Container& hc_rare, 
    const std::string& hist_stem, 
    const std::string& title_stem 
)
{
    TH1* h_data  = hc_data[Form("h_%s_ss"  , hist_stem.c_str())];
    TH1* h_fake  = hc_data[Form("h_%s_fake", hist_stem.c_str())];
    TH1* h_flip  = hc_data[Form("h_%s_flip", hist_stem.c_str())];
    TH1* h_rare  = hc_rare[Form("h_%s_ss"  , hist_stem.c_str())];
    TH1* h_spil  = hc_rare[Form("h_%s_fake", hist_stem.c_str())];
    h_fake->Add(h_spil, -1.0);
    TH1* h_pred = GetTotalPredHist(h_fake, h_flip, h_rare);

    h_data->SetNameTitle(Form("uc_da_histo%s", title_stem.c_str()), Form("uc_da_histo%s", title_stem.c_str()));
    h_fake->SetNameTitle(Form("uc_fa_histo%s", title_stem.c_str()), Form("uc_fa_histo%s", title_stem.c_str()));
    h_rare->SetNameTitle(Form("uc_ra_histo%s", title_stem.c_str()), Form("uc_ra_histo%s", title_stem.c_str()));
    h_flip->SetNameTitle(Form("uc_ch_histo%s", title_stem.c_str()), Form("uc_ch_histo%s", title_stem.c_str()));
    h_pred->SetNameTitle(Form("uc_bk_histo%s", title_stem.c_str()), Form("uc_bk_histo%s", title_stem.c_str()));

    rt::TH1Container hc_result;
    hc_result.Add(h_data);
    hc_result.Add(h_fake);
    hc_result.Add(h_rare);
    hc_result.Add(h_flip);
    hc_result.Add(h_pred);
    return hc_result;
}

// Overlay the kinematic plots
void CreatePasPlots
(
    float lumi, 
    const std::string& output_name, 
    const std::string& signal_region_name, 
    const std::string& analysis_type_name, 
    const std::string& signal_region_type_name = "exclusive", 
    int charge_type = 0 
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

    // handle ttg seperately because of SF
    rt::TH1Container hc_ttg(Form("%s/ttg%s.root", plots_path.c_str(), charge_stem.c_str()));
    
    const ss::SignalRegion::value_type signal_region          = ss::GetSignalRegionFromName(signal_region_name, analysis_type_name, signal_region_type_name); 
    const ss::AnalysisType::value_type analysis_type          = ss::GetAnalysisTypeFromName(analysis_type_name);
    const ss::SignalRegionType::value_type signal_region_type = ss::GetSignalRegionTypeFromName(signal_region_type_name); 
    const bool apply_ttg_sf = (((0 < signal_region && signal_region < 36 and analysis_type == ss::AnalysisType::high_pt) or 
                               (0 < signal_region && signal_region < 29 and (analysis_type == ss::AnalysisType::low_pt or analysis_type == ss::AnalysisType::vlow_pt))) and
                               (signal_region_type == ss::SignalRegionType::exclusive));
    if (apply_ttg_sf)
    {
        const ss::Yield ttg_sr0 = ss::GetYield("ss", at::Sample::ttg, ss::SignalRegion::sr0, analysis_type, signal_region_type, 0, output_name);
        const ss::Yield ttg_srn = ss::GetYield("ss", at::Sample::ttg, signal_region        , analysis_type, signal_region_type, 0, output_name);

        // assign value
        const float ttg_sf = (ttg_sr0.ll > 0 ? ApplyTTGammaScaleFactor(signal_region, analysis_type, ttg_sr0.ll, ttg_sr0.dll).first : ttg_srn.ll)/ttg_srn.ll; 

        // scale the predictions with the scale factor
        hc_ttg.Scale(ttg_sf);
    }
    hc_mc += hc_ttg;
    
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

    // for PAS
    rt::TH1Container hc_result;
    hc_result += GetPasPlots(hc_data, hc_mc, "pas_met"   , "MET");
    hc_result += GetPasPlots(hc_data, hc_mc, "pas_ht"    , "HT" );
    hc_result += GetPasPlots(hc_data, hc_mc, "pas_nbtags", "NBJ");
    hc_result += GetPasPlots(hc_data, hc_mc, "pas_njets" , "NJ" );
    hc_result += GetPasPlots(hc_data, hc_mc, "pas_pt1"   , "PT1");
    hc_result += GetPasPlots(hc_data, hc_mc, "pas_pt2"   , "PT2");

    rt::TH1Container hc_result_htlow;
    hc_result_htlow += GetPasPlots(hc_data, hc_mc, "pas_htlow_met"   , "MET");
    hc_result_htlow += GetPasPlots(hc_data, hc_mc, "pas_htlow_ht"    , "HT" );
    hc_result_htlow += GetPasPlots(hc_data, hc_mc, "pas_htlow_nbtags", "NBJ");
    hc_result_htlow += GetPasPlots(hc_data, hc_mc, "pas_htlow_njets" , "NJ" );
    hc_result_htlow += GetPasPlots(hc_data, hc_mc, "pas_htlow_pt1"   , "PT1");
    hc_result_htlow += GetPasPlots(hc_data, hc_mc, "pas_htlow_pt2"   , "PT2");

    rt::TH1Container hc_result_hthigh;
    hc_result_hthigh += GetPasPlots(hc_data, hc_mc, "pas_hthigh_met"   , "MET");
    hc_result_hthigh += GetPasPlots(hc_data, hc_mc, "pas_hthigh_ht"    , "HT" );
    hc_result_hthigh += GetPasPlots(hc_data, hc_mc, "pas_hthigh_nbtags", "NBJ");
    hc_result_hthigh += GetPasPlots(hc_data, hc_mc, "pas_hthigh_njets" , "NJ" );
    hc_result_hthigh += GetPasPlots(hc_data, hc_mc, "pas_hthigh_pt1"   , "PT1");
    hc_result_hthigh += GetPasPlots(hc_data, hc_mc, "pas_hthigh_pt2"   , "PT2");

    // results
    hc_result.Write       (Form("plots/pas_3lep_veto/pas_3lep_veto_%s_%s_%s.root"        , analysis_type_name.c_str(), signal_region_type_name.c_str(), signal_region_name.c_str()));
    hc_result_hthigh.Write(Form("plots/pas_3lep_veto/pas_3lep_veto_high_ht_%s_%s_%s.root", analysis_type_name.c_str(), signal_region_type_name.c_str(), signal_region_name.c_str()));
    hc_result_htlow.Write (Form("plots/pas_3lep_veto/pas_3lep_veto_low_ht_%s_%s_%s.root" , analysis_type_name.c_str(), signal_region_type_name.c_str(), signal_region_name.c_str()));
}
