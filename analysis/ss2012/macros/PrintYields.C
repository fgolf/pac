#include "rt/RootTools.h"
#include "at/Sample.h"
#include "SignalRegion.h"
#include "SSYields.h"
#include "CTable.h"

using namespace std;
using namespace ss;

// systematic uncertainties
const float fake_sys_unc = 0.5;
const float rare_sys_unc = 0.5;
const float flip_sys_unc = 0.2;

// print the yields
void PrintYields
(
    const std::string& output_path, 
    const std::string& signal_region_name, 
    const std::string& analysis_type_name, 
    const std::string& signal_region_type_name = "inclusive", 
    const int charge_option = 0, 
    const bool print_latex = false
)
{
    using namespace at;

    const ss::AnalysisType::value_type analysis_type          = ss::GetAnalysisTypeFromName(analysis_type_name);
    const ss::SignalRegionType::value_type signal_region_type = ss::GetSignalRegionTypeFromName(signal_region_type_name);
    const ss::SignalRegion::value_type signal_region          = ss::GetSignalRegionFromName(signal_region_name, analysis_type_name, signal_region_type_name);
    const ss::SignalRegionInfo sr_info                        = ss::GetSignalRegionInfo(signal_region_name, analysis_type_name, signal_region_type_name);

    // get the yields
    std::map<std::string, ss::Yield> m_yield = GetYieldsMap(string("ss") , signal_region, analysis_type, signal_region_type, charge_option, output_path);
    std::map<std::string, ss::Yield> m_fake  = GetYieldsMap("fake", signal_region, analysis_type, signal_region_type, charge_option, output_path);
    ss::Yield yield_data = m_yield["data"];
    ss::Yield yield_rare = m_yield["rare"];
    ss::Yield yield_mc   = m_yield["mc"  ];
    ss::Yield yield_spil = m_fake ["rare"];
    ss::Yield yield_sf   = ss::GetSFYield  (Sample::data, signal_region, analysis_type, signal_region_type, charge_option, output_path); 
    ss::Yield yield_df   = ss::GetDFYield  (Sample::data, signal_region, analysis_type, signal_region_type, charge_option, output_path); 
    ss::Yield yield_fake = ss::GetFakeYield(Sample::data, signal_region, analysis_type, signal_region_type, charge_option, output_path);
    ss::Yield yield_flip = ss::GetFlipYield(Sample::data, signal_region, analysis_type, signal_region_type, charge_option, output_path); 

    // subtract the spillage from the rare MC
    ss::Yield yield_cfake = (yield_fake - yield_spil);

    // set systematic uncertainties
    ss::SetSysUncertainties(yield_rare , rare_sys_unc);
    ss::SetSysUncertainties(yield_cfake, fake_sys_unc);
    ss::SetSysUncertainties(yield_flip , flip_sys_unc);

    // total prediction
    ss::Yield yield_pred = yield_rare;
    yield_pred += yield_cfake;
    yield_pred += yield_flip;

    if (print_latex)
    {
        // before table
        //string latex("\\begin{table}[ht!]\n"                                       ); 
        //latex.append("\\begin{center}\n"                                           ); 
        //latex.append("\\begin{tabular}{l|cccc} \\hline\\hline\n"                   ); 
        string latex("\\begin{tabular}{l|cccc} \\hline\\hline\n"                   ); 
        latex.append("source & $ee$ & $\\mu\\mu$ & $e\\mu$ & $\\ell\\ell $ \\\\\n" ); 
        latex.append("\\hline\n"                                                   ); 
        latex.append(Form("%s \\\\\n", m_yield["ttdil"  ].GetLatex("ttdil"       , GetSampleInfo(Sample::ttdil  ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["ttslb"  ].GetLatex("ttslb"       , GetSampleInfo(Sample::ttslb  ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["ttslo"  ].GetLatex("ttslo"       , GetSampleInfo(Sample::ttslo  ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["ttotr"  ].GetLatex("ttotr"       , GetSampleInfo(Sample::ttotr  ).latex, /*print_sys_error*/false).c_str()));
        latex.append("\\hline\n");
        latex.append(Form("%s \\\\\n", m_yield["t_schan"].GetLatex("t_schan"     , GetSampleInfo(Sample::t_schan).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["t_tchan"].GetLatex("t_tchan"     , GetSampleInfo(Sample::t_tchan).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["t_tw"   ].GetLatex("t_tw"        , GetSampleInfo(Sample::t_tw   ).latex, /*print_sys_error*/false).c_str()));
        latex.append("\\hline\n");
        latex.append(Form("%s \\\\\n", m_yield["dy"     ].GetLatex("dy"          , GetSampleInfo(Sample::dy     ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["wjets"  ].GetLatex("wjets"       , GetSampleInfo(Sample::wjets  ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["ww"     ].GetLatex("ww"          , GetSampleInfo(Sample::ww     ).latex, /*print_sys_error*/false).c_str()));
        latex.append("\\hline\n");
        latex.append(Form("%s \\\\\n", m_yield["wgstar" ].GetLatex("wgstar"      , GetSampleInfo(Sample::wgstar ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["wz"     ].GetLatex("wz"          , GetSampleInfo(Sample::wz     ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["zz"     ].GetLatex("zz"          , GetSampleInfo(Sample::zz     ).latex, /*print_sys_error*/false).c_str()));
        latex.append("\\hline\n");
        latex.append(Form("%s \\\\\n", m_yield["ttg"    ].GetLatex("ttg"         , GetSampleInfo(Sample::ttg    ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["ttw"    ].GetLatex("ttw"         , GetSampleInfo(Sample::ttw    ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["ttz"    ].GetLatex("ttz"         , GetSampleInfo(Sample::ttz    ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["tbz"    ].GetLatex("tbz"         , GetSampleInfo(Sample::tbz    ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["ttww"   ].GetLatex("ttww"        , GetSampleInfo(Sample::ttww   ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["wwg"    ].GetLatex("wwg"         , GetSampleInfo(Sample::wwg    ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["www"    ].GetLatex("www"         , GetSampleInfo(Sample::www    ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["wwz"    ].GetLatex("wwz"         , GetSampleInfo(Sample::wwz    ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["wzz"    ].GetLatex("wzz"         , GetSampleInfo(Sample::wzz    ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["zzz"    ].GetLatex("zzz"         , GetSampleInfo(Sample::zzz    ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["wwqq"   ].GetLatex("wwqq"        , GetSampleInfo(Sample::wwqq   ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["ww_ds"  ].GetLatex("ww_ds"       , GetSampleInfo(Sample::ww_ds  ).latex, /*print_sys_error*/false).c_str()));
        latex.append("\\hline\\hline\n");
        latex.append(Form("%s \\\\\n", yield_mc.GetLatex          ("mc"          , "Total MC"                          , /*print_sys_error*/false).c_str()));
        latex.append("\\hline\n");
        latex.append(Form("%s \\\\\n", yield_sf.GetLatex          ("sf"          , "SF"                                , /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", yield_df.GetLatex          ("df"          , "DF"                                , /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", yield_spil.GetLatex        ("sc"          , "SC"                                , /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", yield_fake.GetLatex        ("fake"        , "SF + DF"                           , /*print_sys_error*/false).c_str()));
        latex.append("\\hline\n");
        latex.append(Form("%s \\\\\n", yield_cfake.GetLatex       ("cfake"       , "SF + DF - SC"                      , /*print_sys_error*/true ).c_str()));
        latex.append("\\hline\\hline\n");
        latex.append(Form("%s \\\\\n", yield_flip.GetLatex        ("flip"        , "Charge Flips"                      , /*print_sys_error*/true ).c_str()));
        latex.append("\\hline\n");
        latex.append(Form("%s \\\\\n", yield_rare.GetLatex        ("pred"        , "MC Pred"                           , /*print_sys_error*/true ).c_str()));
        latex.append("\\hline\n");
        latex.append(Form("%s \\\\\n", yield_pred.GetLatex        ("total pred"  , "Total Pred"                        , /*print_sys_error*/true ).c_str()));
        latex.append("\\hline\\hline\n");
        latex.append(Form("%s \\\\\n", yield_data.GetLatex        ("data"        , "Data"                              , /*print_sys_error*/true ).c_str()));
        latex.append("\\hline\\hline\n" ); 
        latex.append("\\end{tabular}\n" ); 
        //latex.append("\\end{center}\n"  ); 
        //latex.append("\\end{table}"     ); 
        cout << latex << endl;
    }
    else
    {
        // make the table
        CTable t_yields;
        t_yields.useTitle();
        t_yields.setTitle(Form("yields for SS 2012 %s (%s)", sr_info.name.c_str(), sr_info.title.c_str()));
        t_yields.setColLabel("ee", 0);
        t_yields.setColLabel("mm", 1);
        t_yields.setColLabel("em", 2);
        t_yields.setColLabel("ll", 3);
        t_yields.setTable()
        (                                                            "ee",                        "mm",                        "em",                       "ll")
        (GetSampleInfo(Sample::ttdil   ).name, m_yield["ttdil"    ] .ee_pm() , m_yield["ttdil"    ] .mm_pm() , m_yield["ttdil"    ] .em_pm() , m_yield["ttdil"    ] .ll_pm())
        (GetSampleInfo(Sample::ttslb   ).name, m_yield["ttslb"    ] .ee_pm() , m_yield["ttslb"    ] .mm_pm() , m_yield["ttslb"    ] .em_pm() , m_yield["ttslb"    ] .ll_pm())
        (GetSampleInfo(Sample::ttslo   ).name, m_yield["ttslo"    ] .ee_pm() , m_yield["ttslo"    ] .mm_pm() , m_yield["ttslo"    ] .em_pm() , m_yield["ttslo"    ] .ll_pm())
        (GetSampleInfo(Sample::ttotr   ).name, m_yield["ttotr"    ] .ee_pm() , m_yield["ttotr"    ] .mm_pm() , m_yield["ttotr"    ] .em_pm() , m_yield["ttotr"    ] .ll_pm())
        (GetSampleInfo(Sample::t_schan ).name, m_yield["t_schan"  ] .ee_pm() , m_yield["t_schan"  ] .mm_pm() , m_yield["t_schan"  ] .em_pm() , m_yield["t_schan"  ] .ll_pm())
        (GetSampleInfo(Sample::t_tchan ).name, m_yield["t_tchan"  ] .ee_pm() , m_yield["t_tchan"  ] .mm_pm() , m_yield["t_tchan"  ] .em_pm() , m_yield["t_tchan"  ] .ll_pm())
        (GetSampleInfo(Sample::t_tw    ).name, m_yield["t_tw"     ] .ee_pm() , m_yield["t_tw"     ] .mm_pm() , m_yield["t_tw"     ] .em_pm() , m_yield["t_tw"     ] .ll_pm())
        (GetSampleInfo(Sample::dy      ).name, m_yield["dy"       ] .ee_pm() , m_yield["dy"       ] .mm_pm() , m_yield["dy"       ] .em_pm() , m_yield["dy"       ] .ll_pm())
        (GetSampleInfo(Sample::wjets   ).name, m_yield["wjets"    ] .ee_pm() , m_yield["wjets"    ] .mm_pm() , m_yield["wjets"    ] .em_pm() , m_yield["wjets"    ] .ll_pm())
        (GetSampleInfo(Sample::ww      ).name, m_yield["ww"       ] .ee_pm() , m_yield["ww"       ] .mm_pm() , m_yield["ww"       ] .em_pm() , m_yield["ww"       ] .ll_pm())
        //(GetSampleInfo(Sample::wgstar ).name, m_yield["wgstar"  ] .ee_pm() , m_yield["wgstar"   ] .mm_pm() , m_yield["wgstar"   ] .em_pm() , m_yield["wgstar"   ] .ll_pm())
        (GetSampleInfo(Sample::wgstar2e).name, m_yield["wgstar2e" ] .ee_pm() , m_yield["wgstar2e" ] .mm_pm() , m_yield["wgstar2e" ] .em_pm() , m_yield["wgstar2e" ] .ll_pm())
        (GetSampleInfo(Sample::wgstar2m).name, m_yield["wgstar2m" ] .ee_pm() , m_yield["wgstar2m" ] .mm_pm() , m_yield["wgstar2m" ] .em_pm() , m_yield["wgstar2m" ] .ll_pm())
        (GetSampleInfo(Sample::wgstar2t).name, m_yield["wgstar2t" ] .ee_pm() , m_yield["wgstar2t" ] .mm_pm() , m_yield["wgstar2t" ] .em_pm() , m_yield["wgstar2t" ] .ll_pm())
        (GetSampleInfo(Sample::wz      ).name, m_yield["wz"       ] .ee_pm() , m_yield["wz"       ] .mm_pm() , m_yield["wz"       ] .em_pm() , m_yield["wz"       ] .ll_pm())
        (GetSampleInfo(Sample::zz      ).name, m_yield["zz"       ] .ee_pm() , m_yield["zz"       ] .mm_pm() , m_yield["zz"       ] .em_pm() , m_yield["zz"       ] .ll_pm())
        (GetSampleInfo(Sample::ttg     ).name, m_yield["ttg"      ] .ee_pm() , m_yield["ttg"      ] .mm_pm() , m_yield["ttg"      ] .em_pm() , m_yield["ttg"      ] .ll_pm())
        (GetSampleInfo(Sample::ttw     ).name, m_yield["ttw"      ] .ee_pm() , m_yield["ttw"      ] .mm_pm() , m_yield["ttw"      ] .em_pm() , m_yield["ttw"      ] .ll_pm())
        (GetSampleInfo(Sample::ttz     ).name, m_yield["ttz"      ] .ee_pm() , m_yield["ttz"      ] .mm_pm() , m_yield["ttz"      ] .em_pm() , m_yield["ttz"      ] .ll_pm())
        (GetSampleInfo(Sample::tbz     ).name, m_yield["tbz"      ] .ee_pm() , m_yield["tbz"      ] .mm_pm() , m_yield["tbz"      ] .em_pm() , m_yield["tbz"      ] .ll_pm())
        (GetSampleInfo(Sample::ttww    ).name, m_yield["ttww"     ] .ee_pm() , m_yield["ttww"     ] .mm_pm() , m_yield["ttww"     ] .em_pm() , m_yield["ttww"     ] .ll_pm())
        (GetSampleInfo(Sample::wwg     ).name, m_yield["wwg"      ] .ee_pm() , m_yield["wwg"      ] .mm_pm() , m_yield["wwg"      ] .em_pm() , m_yield["wwg"      ] .ll_pm())
        (GetSampleInfo(Sample::www     ).name, m_yield["www"      ] .ee_pm() , m_yield["www"      ] .mm_pm() , m_yield["www"      ] .em_pm() , m_yield["www"      ] .ll_pm())
        (GetSampleInfo(Sample::wwz     ).name, m_yield["wwz"      ] .ee_pm() , m_yield["wwz"      ] .mm_pm() , m_yield["wwz"      ] .em_pm() , m_yield["wwz"      ] .ll_pm())
        (GetSampleInfo(Sample::wzz     ).name, m_yield["wzz"      ] .ee_pm() , m_yield["wzz"      ] .mm_pm() , m_yield["wzz"      ] .em_pm() , m_yield["wzz"      ] .ll_pm())
        (GetSampleInfo(Sample::zzz     ).name, m_yield["zzz"      ] .ee_pm() , m_yield["zzz"      ] .mm_pm() , m_yield["zzz"      ] .em_pm() , m_yield["zzz"      ] .ll_pm())
        //(GetSampleInfo(Sample::wwqq   ).name, m_yield["wwqq"    ] .ee_pm() , m_yield["wwqq"     ] .mm_pm() , m_yield["wwqq"     ] .em_pm() , m_yield["wwqq"     ] .ll_pm())
        (GetSampleInfo(Sample::wpwpqq  ).name, m_yield["wpwpqq"   ] .ee_pm() , m_yield["wpwpqq"   ] .mm_pm() , m_yield["wpwpqq"   ] .em_pm() , m_yield["wpwpqq"   ] .ll_pm())
        (GetSampleInfo(Sample::wmwmqq  ).name, m_yield["wmwmqq"   ] .ee_pm() , m_yield["wmwmqq"   ] .mm_pm() , m_yield["wmwmqq"   ] .em_pm() , m_yield["wmwmqq"   ] .ll_pm())
        (GetSampleInfo(Sample::ww_ds   ).name, m_yield["ww_ds"    ] .ee_pm() , m_yield["ww_ds"    ] .mm_pm() , m_yield["ww_ds"    ] .em_pm() , m_yield["ww_ds"    ] .ll_pm())
        ("Total MC"                          , yield_mc.ee_pm()              , yield_mc.mm_pm()              , yield_mc.em_pm()              , yield_mc.ll_pm()             ) 
        ("SF"                                , yield_sf.ee_pm()              , yield_sf.mm_pm()              , yield_sf.em_pm()              , yield_sf.ll_pm()             ) 
        ("DF"                                , yield_df.ee_pm()              , yield_df.mm_pm()              , yield_df.em_pm()              , yield_df.ll_pm()             ) 
        ("SC"                                , yield_spil.ee_pm()            , yield_spil.mm_pm()            , yield_spil.em_pm()            , yield_spil.ll_pm()           ) 
        ("SF + DF"                           , yield_fake.ee_pm()            , yield_fake.mm_pm()            , yield_fake.em_pm()            , yield_fake.ll_pm()           ) 
        ("SF + DF - SC"                      , yield_cfake.ee_pm()           , yield_cfake.mm_pm()           , yield_cfake.em_pm()           , yield_cfake.ll_pm()          ) 
        ("Charge Flips"                      , yield_flip.ee_pm()            , yield_flip.mm_pm()            , yield_flip.em_pm()            , yield_flip.ll_pm()           ) 
        ("MC Pred"                           , yield_rare.ee_pm()            , yield_rare.mm_pm()            , yield_rare.em_pm()            , yield_rare.ll_pm()           ) 
        ("Total Pred"                        , yield_pred.ee_pm()            , yield_pred.mm_pm()            , yield_pred.em_pm()            , yield_pred.ll_pm()           ) 
        ("data"                              , (int)yield_data.ee            , (int)yield_data.mm            , (int)yield_data.em            , (int)yield_data.ll           );

        // print it
        t_yields.print();
    }
}


// print the rare MC sideband contamination 
void PrintSidebandContamination
(
    const std::string& output_path, 
    const std::string& signal_region_name, 
    const std::string& analysis_type_name, 
    const std::string& signal_region_type_name = "inclusive", 
    int charge_option = 0, 
    bool print_latex = false
)
{
    using namespace at;

    const ss::AnalysisType::value_type analysis_type          = ss::GetAnalysisTypeFromName(analysis_type_name);
    const ss::SignalRegionType::value_type signal_region_type = ss::GetSignalRegionTypeFromName(signal_region_type_name);
    const ss::SignalRegion::value_type signal_region          = ss::GetSignalRegionFromName(signal_region_name, analysis_type_name, signal_region_type_name);
    const ss::SignalRegionInfo sr_info                        = ss::GetSignalRegionInfo(signal_region_name, analysis_type_name, signal_region_type_name);

    // get the yields
    std::map<std::string, ss::Yield> m_yield = GetYieldsMap("ss"  , signal_region, analysis_type, signal_region_type, charge_option, output_path);
    std::map<std::string, ss::Yield> m_fake  = GetYieldsMap("fake", signal_region, analysis_type, signal_region_type, charge_option, output_path);
    ss::Yield yield_mc   = m_fake["mc"  ];
    ss::Yield yield_spil = m_fake["rare"];

    if (print_latex)
    {
        // before table
        //string latex("\\begin{table}[ht!]\n"                                       ); 
        //latex.append("\\begin{center}\n"                                           ); 
        //latex.append("\\begin{tabular}{l|cccc} \\hline\\hline\n"                   ); 
        string latex("\\begin{tabular}{l|cccc} \\hline\\hline\n"                   ); 
        latex.append("source & $ee$ & $\\mu\\mu$ & $e\\mu$ & $\\ell\\ell $ \\\\\n" ); 
        latex.append("\\hline\n"                                                   ); 
        latex.append(Form("%s \\\\\n", m_fake["ttdil"  ].GetLatex("ttdil"       , GetSampleInfo(Sample::ttdil  ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_fake["ttslb"  ].GetLatex("ttslb"       , GetSampleInfo(Sample::ttslb  ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_fake["ttslo"  ].GetLatex("ttslo"       , GetSampleInfo(Sample::ttslo  ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_fake["ttotr"  ].GetLatex("ttotr"       , GetSampleInfo(Sample::ttotr  ).latex, /*print_sys_error*/false).c_str()));
        latex.append("\\hline\n");
        latex.append(Form("%s \\\\\n", m_fake["t_schan"].GetLatex("t_schan"     , GetSampleInfo(Sample::t_schan).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_fake["t_tchan"].GetLatex("t_tchan"     , GetSampleInfo(Sample::t_tchan).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_fake["t_tw"   ].GetLatex("t_tw"        , GetSampleInfo(Sample::t_tw   ).latex, /*print_sys_error*/false).c_str()));
        latex.append("\\hline\n");
        latex.append(Form("%s \\\\\n", m_fake["dy"     ].GetLatex("dy"          , GetSampleInfo(Sample::dy     ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_fake["wjets"  ].GetLatex("wjets"       , GetSampleInfo(Sample::wjets  ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_fake["ww"     ].GetLatex("ww"          , GetSampleInfo(Sample::ww     ).latex, /*print_sys_error*/false).c_str()));
        latex.append("\\hline\n");
        latex.append(Form("%s \\\\\n", m_fake["wgstar" ].GetLatex("wgstar"      , GetSampleInfo(Sample::wgstar ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_fake["wz"     ].GetLatex("wz"          , GetSampleInfo(Sample::wz     ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_fake["zz"     ].GetLatex("zz"          , GetSampleInfo(Sample::zz     ).latex, /*print_sys_error*/false).c_str()));
        latex.append("\\hline\n");
        latex.append(Form("%s \\\\\n", m_fake["ttg"    ].GetLatex("ttg"         , GetSampleInfo(Sample::ttg    ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_fake["ttw"    ].GetLatex("ttw"         , GetSampleInfo(Sample::ttw    ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_fake["ttz"    ].GetLatex("ttz"         , GetSampleInfo(Sample::ttz    ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_fake["tbz"    ].GetLatex("tbz"         , GetSampleInfo(Sample::tbz    ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_fake["ttww"   ].GetLatex("ttww"        , GetSampleInfo(Sample::ttww   ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_fake["wwg"    ].GetLatex("wwg"         , GetSampleInfo(Sample::wwg    ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_fake["www"    ].GetLatex("www"         , GetSampleInfo(Sample::www    ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_fake["wwz"    ].GetLatex("wwz"         , GetSampleInfo(Sample::wwz    ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_fake["wzz"    ].GetLatex("wzz"         , GetSampleInfo(Sample::wzz    ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_fake["zzz"    ].GetLatex("zzz"         , GetSampleInfo(Sample::zzz    ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_fake["wwqq"   ].GetLatex("wwqq"        , GetSampleInfo(Sample::wwqq   ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_fake["ww_ds"  ].GetLatex("ww_ds"       , GetSampleInfo(Sample::ww_ds  ).latex, /*print_sys_error*/false).c_str()));
        latex.append("\\hline\\hline\n");
        latex.append(Form("%s \\\\\n", yield_mc.GetLatex          ("mc"          , "Total MC"                          , /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", yield_spil.GetLatex        ("pc"          , "Total rare MC"                     , /*print_sys_error*/false).c_str()));
        latex.append("\\hline\\hline\n" ); 
        latex.append("\\end{tabular}\n" ); 
        //latex.append("\\end{center}\n"  ); 
        //latex.append("\\end{table}"     ); 
        cout << latex << endl;
    }
    else
    {
        // make the table
        CTable t_yields;
        t_yields.useTitle();
        t_yields.setTitle(Form("sideband contamination %s (%s)", sr_info.name.c_str(), sr_info.title.c_str()));
        t_yields.setColLabel("ee", 0);
        t_yields.setColLabel("mm", 1);
        t_yields.setColLabel("em", 2);
        t_yields.setColLabel("ll", 3);
        t_yields.setTable()
        (                                                           "ee",                       "mm",                       "em",                      "ll")
        (GetSampleInfo(Sample::ttdil  ).name, m_fake["ttdil"  ].ee_pm() , m_fake["ttdil"  ].mm_pm() , m_fake["ttdil"  ].em_pm() , m_fake["ttdil"  ].ll_pm())
        (GetSampleInfo(Sample::ttslb  ).name, m_fake["ttslb"  ].ee_pm() , m_fake["ttslb"  ].mm_pm() , m_fake["ttslb"  ].em_pm() , m_fake["ttslb"  ].ll_pm())
        (GetSampleInfo(Sample::ttslo  ).name, m_fake["ttslo"  ].ee_pm() , m_fake["ttslo"  ].mm_pm() , m_fake["ttslo"  ].em_pm() , m_fake["ttslo"  ].ll_pm())
        (GetSampleInfo(Sample::ttotr  ).name, m_fake["ttotr"  ].ee_pm() , m_fake["ttotr"  ].mm_pm() , m_fake["ttotr"  ].em_pm() , m_fake["ttotr"  ].ll_pm())
        (GetSampleInfo(Sample::t_schan).name, m_fake["t_schan"].ee_pm() , m_fake["t_schan"].mm_pm() , m_fake["t_schan"].em_pm() , m_fake["t_schan"].ll_pm())
        (GetSampleInfo(Sample::t_tchan).name, m_fake["t_tchan"].ee_pm() , m_fake["t_tchan"].mm_pm() , m_fake["t_tchan"].em_pm() , m_fake["t_tchan"].ll_pm())
        (GetSampleInfo(Sample::t_tw   ).name, m_fake["t_tw"   ].ee_pm() , m_fake["t_tw"   ].mm_pm() , m_fake["t_tw"   ].em_pm() , m_fake["t_tw"   ].ll_pm())
        (GetSampleInfo(Sample::dy     ).name, m_fake["dy"     ].ee_pm() , m_fake["dy"     ].mm_pm() , m_fake["dy"     ].em_pm() , m_fake["dy"     ].ll_pm())
        (GetSampleInfo(Sample::wjets  ).name, m_fake["wjets"  ].ee_pm() , m_fake["wjets"  ].mm_pm() , m_fake["wjets"  ].em_pm() , m_fake["wjets"  ].ll_pm())
        (GetSampleInfo(Sample::ww     ).name, m_fake["ww"     ].ee_pm() , m_fake["ww"     ].mm_pm() , m_fake["ww"     ].em_pm() , m_fake["ww"     ].ll_pm())
        (GetSampleInfo(Sample::wgstar ).name, m_fake["wgstar" ].ee_pm() , m_fake["wgstar" ].mm_pm() , m_fake["wgstar" ].em_pm() , m_fake["wgstar" ].ll_pm())
        (GetSampleInfo(Sample::wz     ).name, m_fake["wz"     ].ee_pm() , m_fake["wz"     ].mm_pm() , m_fake["wz"     ].em_pm() , m_fake["wz"     ].ll_pm())
        (GetSampleInfo(Sample::zz     ).name, m_fake["zz"     ].ee_pm() , m_fake["zz"     ].mm_pm() , m_fake["zz"     ].em_pm() , m_fake["zz"     ].ll_pm())
        (GetSampleInfo(Sample::ttg    ).name, m_fake["ttg"    ].ee_pm() , m_fake["ttg"    ].mm_pm() , m_fake["ttg"    ].em_pm() , m_fake["ttg"    ].ll_pm())
        (GetSampleInfo(Sample::ttw    ).name, m_fake["ttw"    ].ee_pm() , m_fake["ttw"    ].mm_pm() , m_fake["ttw"    ].em_pm() , m_fake["ttw"    ].ll_pm())
        (GetSampleInfo(Sample::ttz    ).name, m_fake["ttz"    ].ee_pm() , m_fake["ttz"    ].mm_pm() , m_fake["ttz"    ].em_pm() , m_fake["ttz"    ].ll_pm())
        (GetSampleInfo(Sample::tbz    ).name, m_fake["tbz"    ].ee_pm() , m_fake["tbz"    ].mm_pm() , m_fake["tbz"    ].em_pm() , m_fake["tbz"    ].ll_pm())
        (GetSampleInfo(Sample::ttww   ).name, m_fake["ttww"   ].ee_pm() , m_fake["ttww"   ].mm_pm() , m_fake["ttww"   ].em_pm() , m_fake["ttww"   ].ll_pm())
        (GetSampleInfo(Sample::wwg    ).name, m_fake["wwg"    ].ee_pm() , m_fake["wwg"    ].mm_pm() , m_fake["wwg"    ].em_pm() , m_fake["wwg"    ].ll_pm())
        (GetSampleInfo(Sample::www    ).name, m_fake["www"    ].ee_pm() , m_fake["www"    ].mm_pm() , m_fake["www"    ].em_pm() , m_fake["www"    ].ll_pm())
        (GetSampleInfo(Sample::wwz    ).name, m_fake["wwz"    ].ee_pm() , m_fake["wwz"    ].mm_pm() , m_fake["wwz"    ].em_pm() , m_fake["wwz"    ].ll_pm())
        (GetSampleInfo(Sample::wzz    ).name, m_fake["wzz"    ].ee_pm() , m_fake["wzz"    ].mm_pm() , m_fake["wzz"    ].em_pm() , m_fake["wzz"    ].ll_pm())
        (GetSampleInfo(Sample::zzz    ).name, m_fake["zzz"    ].ee_pm() , m_fake["zzz"    ].mm_pm() , m_fake["zzz"    ].em_pm() , m_fake["zzz"    ].ll_pm())
        (GetSampleInfo(Sample::wwqq   ).name, m_fake["wwqq"   ].ee_pm() , m_fake["wwqq"   ].mm_pm() , m_fake["wwqq"   ].em_pm() , m_fake["wwqq"   ].ll_pm())
        (GetSampleInfo(Sample::ww_ds  ).name, m_fake["ww_ds"  ].ee_pm() , m_fake["ww_ds"  ].mm_pm() , m_fake["ww_ds"  ].em_pm() , m_fake["ww_ds"  ].ll_pm())
        ("Total MC"                         , yield_mc.ee_pm()          , yield_mc.mm_pm()          , yield_mc.em_pm()          , yield_mc.ll_pm()         ) 
        ("Total Rare MC"                    , yield_spil.ee_pm()        , yield_spil.mm_pm()        , yield_spil.em_pm()        , yield_spil.ll_pm()       ) ;


        // print it
        t_yields.print();
    }
}


// print the yields
void PrintETHCard
(
    const std::string& output_path, 
    const std::string& analysis_type_name, 
    const std::string& signal_region_type_name = "inclusive" 
)
{
    using namespace at;

    const ss::AnalysisType::value_type analysis_type          = ss::GetAnalysisTypeFromName(analysis_type_name);
    const ss::SignalRegionType::value_type signal_region_type = ss::GetSignalRegionTypeFromName(signal_region_type_name);
    // can be paramerized if needed (for now hard coded)
    const int charge_option = 0; 
    
    //for (size_t sr_num = 0; sr_num != ss::SignalRegion::static_size; sr_num++)
    for (size_t sr_num = 0; sr_num != 29; sr_num++)
    {
        const string signal_region_name    = Form("sr%lu", sr_num);
        const ss::SignalRegion::value_type signal_region = ss::GetSignalRegionFromName(signal_region_name, analysis_type_name, signal_region_type_name); 
        const ss::SignalRegionInfo sr_info = ss::GetSignalRegionInfo(signal_region_name, analysis_type_name, signal_region_type_name);

        // get the yields
        std::map<std::string, ss::Yield> m_yield = GetYieldsMap("ss"  , signal_region, analysis_type, signal_region_type, charge_option, output_path);
        std::map<std::string, ss::Yield> m_fake  = GetYieldsMap("fake", signal_region, analysis_type, signal_region_type, charge_option, output_path);
        ss::Yield yield_data = m_yield["data"];
        ss::Yield yield_rare = m_yield["rare"];
        ss::Yield yield_spil = m_fake ["rare"];
        ss::Yield yield_fake = ss::GetFakeYield(Sample::data, signal_region, analysis_type, signal_region_type, charge_option, output_path);
        ss::Yield yield_flip = ss::GetFlipYield(Sample::data, signal_region, analysis_type, signal_region_type, charge_option, output_path); 

        // subtract the spillage from the rare MC
        ss::Yield yield_cfake = (yield_fake - yield_spil);

        // set systematic uncertainties
        ss::SetSysUncertainties(yield_rare , rare_sys_unc);
        ss::SetSysUncertainties(yield_cfake, fake_sys_unc);
        ss::SetSysUncertainties(yield_flip , flip_sys_unc);

        // total prediction
        ss::Yield yield_pred = yield_rare;
        yield_pred += yield_cfake;
        yield_pred += yield_flip;

        // print the table
        const string sr_name = Form((sr_num < 10 ? "SR0%lu" : "SR%lu"), sr_num);

        if (sr_num == 0)
        {
            cout << "{" << endl;
        }
        cout << Form("'%s':{", sr_name.c_str()) << endl;
        cout << Form("'f': %1.3f, 'fstat': %1.3f, 'fsyst': %1.3f,", yield_cfake.ll, yield_cfake.dll, yield_cfake.sll) << endl;
        cout << Form("'c': %1.3f, 'cstat': %1.3f, 'csyst': %1.3f,", yield_flip.ll , yield_flip.dll , yield_flip.sll ) << endl;
        cout << Form("'r': %1.3f, 'rstat': %1.3f, 'rsyst': %1.3f,", yield_rare.ll , yield_rare.dll , yield_rare.sll ) << endl;
        cout << Form("'o': %u", static_cast<unsigned int>(yield_data.ll)) << endl;
        if (sr_num == (ss::SignalRegion::static_size - 1))
        {
            cout << "}" << endl;
            cout << "}" << endl;
        }
        else
        {
            cout << "}," << endl;
        }
    }
}

// print the summary table 
void PrintSummaryYields
(
  const std::string& output_path,
  const std::string& analysis_type_name, 
  const std::string& signal_region_type_name, 
  bool print_latex = false
)
{
    using namespace at;

    const int charge_option = 0;
    const ss::AnalysisType::value_type analysis_type          = ss::GetAnalysisTypeFromName(analysis_type_name);
    const ss::SignalRegionType::value_type signal_region_type = ss::GetSignalRegionTypeFromName(signal_region_type_name);

    // table for output
    CTable t_yields_1;
    t_yields_1.useTitle();
    t_yields_1.setTitle("summary table for SS 2012 yields and background predictions (sr0-sr8)");

    CTable t_yields_2;
    t_yields_2.useTitle();
    t_yields_2.setTitle("summary table for SS 2012 yields and background predictions (sr10-sr18)");

    CTable t_yields_3;
    t_yields_3.useTitle();
    t_yields_3.setTitle("summary table for SS 2012 yields and background predictions (sr20-sr28)");

    // fill the columns
    for (unsigned int signal_region_num = 0; signal_region_num != ss::SignalRegion::static_size; signal_region_num++)
    {
        // no using these SRs
        if (signal_region_num==9 or signal_region_num==19) {continue;} 

        // which table are we using?
        CTable* temp_ptr = NULL;
        unsigned int column = signal_region_num;
        if (signal_region_num <= 8)                             {temp_ptr = &t_yields_1;}
        if (10 <= signal_region_num && signal_region_num <= 18) {temp_ptr = &t_yields_2; column -=10;}
        if (20 <= signal_region_num && signal_region_num <= 28) {temp_ptr = &t_yields_3; column -=20;}
        if (not temp_ptr) {continue;}
        CTable& t_yields = *temp_ptr;

        // signal region info
        const string signal_region_name = Form("sr%u", signal_region_num);
        const ss::SignalRegion::value_type signal_region = ss::GetSignalRegionFromName(signal_region_name, analysis_type_name, signal_region_type_name); 
        const ss::SignalRegionInfo sr_info = ss::GetSignalRegionInfo(signal_region_name, analysis_type_name, signal_region_type_name);

        // get the yields
        std::map<std::string, ss::Yield> m_yield = GetYieldsMap("ss"  , signal_region, analysis_type, signal_region_type, charge_option, output_path);
        std::map<std::string, ss::Yield> m_fake  = GetYieldsMap("fake", signal_region, analysis_type, signal_region_type, charge_option, output_path);
        ss::Yield yield_data = m_yield["data"];
        ss::Yield yield_rare = m_yield["rare"];
        ss::Yield yield_spil = m_fake ["rare"];
        ss::Yield yield_fake = ss::GetFakeYield(Sample::data, signal_region, analysis_type, signal_region_type, charge_option, output_path);
        ss::Yield yield_flip = ss::GetFlipYield(Sample::data, signal_region, analysis_type, signal_region_type, charge_option, output_path); 

        // subtract the spillage from the rare MC
        ss::Yield yield_cfake = (yield_fake - yield_spil);

        // set systematic uncertainties
        ss::SetSysUncertainties(yield_rare , rare_sys_unc);
        ss::SetSysUncertainties(yield_cfake, fake_sys_unc);
        ss::SetSysUncertainties(yield_flip , flip_sys_unc);

        // total prediction
        ss::Yield yield_pred = yield_rare;
        yield_pred += yield_cfake;
        yield_pred += yield_flip;

        // print the table
        int row = 0;
        t_yields.setColLabel(Form("sr%u", signal_region_num), column);
        if (print_latex)
        {
            //t_yields.setRowLabel("Fake BG"    , ++row); t_yields.setCell(Form("%1.2f$\\pm$%1.2f$\\pm$%1.2f", yield_cfake.ll, yield_cfake.dll, yield_cfake.sll), row, column);
            //t_yields.setRowLabel("Flip BG"    , ++row); t_yields.setCell(Form("%1.2f$\\pm$%1.2f$\\pm$%1.2f", yield_flip.ll , yield_flip.dll , yield_flip.sll ), row, column);
            //t_yields.setRowLabel("Rare MC"    , ++row); t_yields.setCell(Form("%1.2f$\\pm$%1.2f$\\pm$%1.2f", yield_rare.ll , yield_rare.dll , yield_rare.sll ), row, column);
            //t_yields.setRowLabel("Total BG"   , ++row); t_yields.setCell(Form("%1.2f$\\pm$%1.2f$\\pm$%1.2f", yield_pred.ll , yield_pred.dll , yield_pred.sll ), row, column);
            t_yields.setRowLabel("Fake BG"    , ++row); t_yields.setCell(Form("%1.2f$\\pm$%1.2f", yield_cfake.ll, yield_cfake.tll()), row, column);
            t_yields.setRowLabel("Flip BG"    , ++row); t_yields.setCell(Form("%1.2f$\\pm$%1.2f", yield_flip.ll , yield_flip.tll() ), row, column);
            t_yields.setRowLabel("Rare MC"    , ++row); t_yields.setCell(Form("%1.2f$\\pm$%1.2f", yield_rare.ll , yield_rare.tll() ), row, column);
            t_yields.setRowLabel("Total BG"   , ++row); t_yields.setCell(Form("%1.2f$\\pm$%1.2f", yield_pred.ll , yield_pred.tll() ), row, column);
            t_yields.setRowLabel("Event Yield", ++row); t_yields.setCell(static_cast<int>(yield_data.ll)                            , row, column);
        }
        else
        {
            //t_yields.setRowLabel("Fake BG"    , ++row); t_yields.setCell(Form("%1.2f +/- %1.2f +/- %1.2f", yield_cfake.ll, yield_cfake.dll, yield_cfake.sll), row, column);
            //t_yields.setRowLabel("Flip BG"    , ++row); t_yields.setCell(Form("%1.2f +/- %1.2f +/- %1.2f", yield_flip.ll , yield_flip.dll , yield_flip.sll ), row, column);
            //t_yields.setRowLabel("Rare MC"    , ++row); t_yields.setCell(Form("%1.2f +/- %1.2f +/- %1.2f", yield_rare.ll , yield_rare.dll , yield_rare.sll ), row, column);
            //t_yields.setRowLabel("Total BG"   , ++row); t_yields.setCell(Form("%1.2f +/- %1.2f +/- %1.2f", yield_pred.ll , yield_pred.dll , yield_pred.sll ), row, column);
            t_yields.setRowLabel("Fake BG"    , ++row); t_yields.setCell(Form("%1.2f +/- %1.2f", yield_cfake.ll, yield_cfake.tll()), row, column);
            t_yields.setRowLabel("Flip BG"    , ++row); t_yields.setCell(Form("%1.2f +/- %1.2f", yield_flip.ll , yield_flip.tll() ), row, column);
            t_yields.setRowLabel("Rare MC"    , ++row); t_yields.setCell(Form("%1.2f +/- %1.2f", yield_rare.ll , yield_rare.tll() ), row, column);
            t_yields.setRowLabel("Total BG"   , ++row); t_yields.setCell(Form("%1.2f +/- %1.2f", yield_pred.ll , yield_pred.tll() ), row, column);
            t_yields.setRowLabel("Event Yield", ++row); t_yields.setCell(static_cast<int>(yield_data.ll)                           , row, column);
        }
    } // loop over SRs

    // print the table
    if (print_latex)
    {
        t_yields_1.printTex();
        t_yields_2.printTex();
        t_yields_3.printTex();
    }
    else
    {
        t_yields_1.print();
        t_yields_2.print();
        t_yields_3.print();
    }
}
