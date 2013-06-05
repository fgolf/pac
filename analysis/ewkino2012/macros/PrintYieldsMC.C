#include "rt/RootTools.h"
#include "at/Sample.h"
#include "SignalRegion.h"
#include "SSYields.h"
#include "CTable.h"

using namespace std;
using namespace ewkino;

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
    // "dy",
    "dyjets",
    "wjets",
    "ttjets",
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

// print the yields
void PrintYieldsMC
(
    const std::string& output_path, 
    const std::string& signal_region_name, 
    const std::string& analysis_type_name, 
    const std::string& signal_samples,
    const std::string& bkgd_samples = "all",  
    bool combine_signals = false,
    bool combine_bkgds = false,
    const std::string& signal_region_type_name = "inclusive", 
    const int charge_option = 0, 
    bool print_latex = false,
    bool do_caption = false
    )
{
    using namespace at;
    bool mc_only = true;

    const ewkino::AnalysisType::value_type analysis_type          = ewkino::GetAnalysisTypeFromName(analysis_type_name);
    const ewkino::SignalRegionType::value_type signal_region_type = ewkino::GetSignalRegionTypeFromName(signal_region_type_name);
    const ewkino::SignalRegion::value_type signal_region          = ewkino::GetSignalRegionFromName(signal_region_name, analysis_type_name, signal_region_type_name);
    const ewkino::SignalRegionInfo sr_info                        = ewkino::GetSignalRegionInfo(signal_region_name, analysis_type_name, signal_region_type_name);

    // get the yields
    std::map<std::string, ewkino_ss::Yield> m_yield = ewkino_ss::GetYieldsMap("ss"  , signal_region, analysis_type, signal_region_type, mc_only, charge_option, output_path);
    ewkino_ss::Yield yield_rare = m_yield["rare"];
    ewkino_ss::Yield yield_mc   = m_yield["mc"  ];

    // total prediction
    ewkino_ss::Yield yield_pred = yield_mc;

    // now let's also get the signal yields
    std::vector<std::string> vsignals;
    if (!signal_samples.empty()) {vsignals = rt::string_split(signal_samples);}
    for (unsigned int sidx = 0; sidx < vsignals.size(); sidx++)
    {
        at::Sample::value_type tmp_sample = at::GetSampleFromName(vsignals.at(sidx));
        m_yield[vsignals.at(sidx)] = ewkino_ss::GetYield("ss", tmp_sample, signal_region, analysis_type, signal_region_type, charge_option, output_path);
    }

    if (print_latex)
    {
        string latex;
        latex.append(do_caption ? Form("\\caption{%s}\n", sr_info.latex.c_str()) : "");
        latex.append("\\begin{tabular}{l|cccc} \\hline\\hline\n"                   ); 
        latex.append("source & $ee$ & $\\mu\\mu$ & $e\\mu$ & $\\ell\\ell $ \\\\\n" ); 
        latex.append("\\hline\n"                                                   ); 
        latex.append(Form("%s \\\\\n", m_yield["ttdil"        ].GetLatex("ttdil"        , GetSampleInfo(Sample::ttdil        ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["ttslb"        ].GetLatex("ttslb"        , GetSampleInfo(Sample::ttslb        ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["ttslo"        ].GetLatex("ttslo"        , GetSampleInfo(Sample::ttslo        ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["ttotr"        ].GetLatex("ttotr"        , GetSampleInfo(Sample::ttotr        ).latex, /*print_sys_error*/false).c_str()));
        latex.append("\\hline\n");                                                      
        latex.append(Form("%s \\\\\n", m_yield["t_schan"      ].GetLatex("t_schan"      , GetSampleInfo(Sample::t_schan      ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["t_tchan"      ].GetLatex("t_tchan"      , GetSampleInfo(Sample::t_tchan      ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["t_tw"         ].GetLatex("t_tw"         , GetSampleInfo(Sample::t_tw         ).latex, /*print_sys_error*/false).c_str()));
        latex.append("\\hline\n");                                                      
        latex.append(Form("%s \\\\\n", m_yield["dyjets"       ].GetLatex("dyjets"       , GetSampleInfo(Sample::dyjets       ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["wjets"        ].GetLatex("wjets"        , GetSampleInfo(Sample::wjets        ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["ww"           ].GetLatex("ww"           , GetSampleInfo(Sample::ww           ).latex, /*print_sys_error*/false).c_str()));
        latex.append("\\hline\n");                                                      
        latex.append(Form("%s \\\\\n", m_yield["wgstar2m"     ].GetLatex("wgstar2m"     , GetSampleInfo(Sample::wgstar2m     ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["wgstar2t"     ].GetLatex("wgstar2t"     , GetSampleInfo(Sample::wgstar2t     ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["wz"           ].GetLatex("wz"           , GetSampleInfo(Sample::wz           ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["zz"           ].GetLatex("zz"           , GetSampleInfo(Sample::zz           ).latex, /*print_sys_error*/false).c_str()));
        latex.append("\\hline\n");                                                      
        latex.append(Form("%s \\\\\n", m_yield["ttg"          ].GetLatex("ttg"          , GetSampleInfo(Sample::ttg          ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["ttw"          ].GetLatex("ttw"          , GetSampleInfo(Sample::ttw          ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["ttz"          ].GetLatex("ttz"          , GetSampleInfo(Sample::ttz          ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["tbz"          ].GetLatex("tbz"          , GetSampleInfo(Sample::tbz          ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["ttww"         ].GetLatex("ttww"         , GetSampleInfo(Sample::ttww         ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["wwg"          ].GetLatex("wwg"          , GetSampleInfo(Sample::wwg          ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["www"          ].GetLatex("www"          , GetSampleInfo(Sample::www          ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["wwz"          ].GetLatex("wwz"          , GetSampleInfo(Sample::wwz          ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["wzz"          ].GetLatex("wzz"          , GetSampleInfo(Sample::wzz          ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["zzz"          ].GetLatex("zzz"          , GetSampleInfo(Sample::zzz          ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["wwqq"         ].GetLatex("wwqq"         , GetSampleInfo(Sample::wwqq         ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["ww_ds"        ].GetLatex("ww_ds"        , GetSampleInfo(Sample::ww_ds        ).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["wh_zh_tth_hww"].GetLatex("wh_zh_tth_hww", GetSampleInfo(Sample::wh_zh_tth_hww).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["wh_zh_tth_hzz"].GetLatex("wh_zh_tth_hzz", GetSampleInfo(Sample::wh_zh_tth_hzz).latex, /*print_sys_error*/false).c_str()));
        latex.append(Form("%s \\\\\n", m_yield["wh_zh_tth_htt"].GetLatex("wh_zh_tth_htt", GetSampleInfo(Sample::wh_zh_tth_htt).latex, /*print_sys_error*/false).c_str()));
        latex.append("\\hline\\hline\n");
        latex.append(Form("%s \\\\\n", yield_mc.GetLatex                ("mc"           , "Total MC"                                , /*print_sys_error*/false).c_str()));
        latex.append("\\hline\n");                                
        latex.append(Form("%s \\\\\n", yield_rare.GetLatex              ("pred"         , "MC Pred"                                 , /*print_sys_error*/true ).c_str()));
        latex.append("\\hline\n");                                
        latex.append(Form("%s \\\\\n", yield_pred.GetLatex              ("total pred"   , "Total Pred"                              , /*print_sys_error*/true ).c_str()));

        for (unsigned int sidx = 0; sidx < vsignals.size(); sidx++)
        {
            if (sidx == 0)
                latex.append("\\hline\n");                                

            latex.append(Form("%s \\\\\n", m_yield[vsignals.at(sidx)].GetLatex(vsignals.at(sidx), GetSampleInfo(vsignals.at(sidx)).latex, /*print_sys_error*/false).c_str()));
        }
 
        latex.append("\\hline\\hline\n" ); 
        latex.append("\\end{tabular}\n" ); 
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
            (                                                                    "ee",                               "mm",                               "em",                              "ll")
            (GetSampleInfo(Sample::ttdil        ).name, m_yield["ttdil"        ] .ee_pm() , m_yield["ttdil"        ] .mm_pm() , m_yield["ttdil"        ] .em_pm() , m_yield["ttdil"        ] .ll_pm())
            (GetSampleInfo(Sample::ttslb        ).name, m_yield["ttslb"        ] .ee_pm() , m_yield["ttslb"        ] .mm_pm() , m_yield["ttslb"        ] .em_pm() , m_yield["ttslb"        ] .ll_pm())
            (GetSampleInfo(Sample::ttslo        ).name, m_yield["ttslo"        ] .ee_pm() , m_yield["ttslo"        ] .mm_pm() , m_yield["ttslo"        ] .em_pm() , m_yield["ttslo"        ] .ll_pm())
            (GetSampleInfo(Sample::ttotr        ).name, m_yield["ttotr"        ] .ee_pm() , m_yield["ttotr"        ] .mm_pm() , m_yield["ttotr"        ] .em_pm() , m_yield["ttotr"        ] .ll_pm())
            (GetSampleInfo(Sample::t_schan      ).name, m_yield["t_schan"      ] .ee_pm() , m_yield["t_schan"      ] .mm_pm() , m_yield["t_schan"      ] .em_pm() , m_yield["t_schan"      ] .ll_pm())
            (GetSampleInfo(Sample::t_tchan      ).name, m_yield["t_tchan"      ] .ee_pm() , m_yield["t_tchan"      ] .mm_pm() , m_yield["t_tchan"      ] .em_pm() , m_yield["t_tchan"      ] .ll_pm())
            (GetSampleInfo(Sample::t_tw         ).name, m_yield["t_tw"         ] .ee_pm() , m_yield["t_tw"         ] .mm_pm() , m_yield["t_tw"         ] .em_pm() , m_yield["t_tw"         ] .ll_pm())
            (GetSampleInfo(Sample::dyjets       ).name, m_yield["dyjets"       ] .ee_pm() , m_yield["dyjets"       ] .mm_pm() , m_yield["dyjets"       ] .em_pm() , m_yield["dyjets"       ] .ll_pm())
            (GetSampleInfo(Sample::wjets        ).name, m_yield["wjets"        ] .ee_pm() , m_yield["wjets"        ] .mm_pm() , m_yield["wjets"        ] .em_pm() , m_yield["wjets"        ] .ll_pm())
            (GetSampleInfo(Sample::ww           ).name, m_yield["ww"           ] .ee_pm() , m_yield["ww"           ] .mm_pm() , m_yield["ww"           ] .em_pm() , m_yield["ww"           ] .ll_pm())
            (GetSampleInfo(Sample::wgstar2m     ).name, m_yield["wgstar2m"     ] .ee_pm() , m_yield["wgstar2m"     ] .mm_pm() , m_yield["wgstar2m"     ] .em_pm() , m_yield["wgstar2m"     ] .ll_pm())
            (GetSampleInfo(Sample::wgstar2t     ).name, m_yield["wgstar2t"     ] .ee_pm() , m_yield["wgstar2t"     ] .mm_pm() , m_yield["wgstar2t"     ] .em_pm() , m_yield["wgstar2t"     ] .ll_pm())
            (GetSampleInfo(Sample::wz           ).name, m_yield["wz"           ] .ee_pm() , m_yield["wz"           ] .mm_pm() , m_yield["wz"           ] .em_pm() , m_yield["wz"           ] .ll_pm())
            (GetSampleInfo(Sample::zz           ).name, m_yield["zz"           ] .ee_pm() , m_yield["zz"           ] .mm_pm() , m_yield["zz"           ] .em_pm() , m_yield["zz"           ] .ll_pm())
            (GetSampleInfo(Sample::ttg          ).name, m_yield["ttg"          ] .ee_pm() , m_yield["ttg"          ] .mm_pm() , m_yield["ttg"          ] .em_pm() , m_yield["ttg"          ] .ll_pm())
            (GetSampleInfo(Sample::ttw          ).name, m_yield["ttw"          ] .ee_pm() , m_yield["ttw"          ] .mm_pm() , m_yield["ttw"          ] .em_pm() , m_yield["ttw"          ] .ll_pm())
            (GetSampleInfo(Sample::ttz          ).name, m_yield["ttz"          ] .ee_pm() , m_yield["ttz"          ] .mm_pm() , m_yield["ttz"          ] .em_pm() , m_yield["ttz"          ] .ll_pm())
            (GetSampleInfo(Sample::tbz          ).name, m_yield["tbz"          ] .ee_pm() , m_yield["tbz"          ] .mm_pm() , m_yield["tbz"          ] .em_pm() , m_yield["tbz"          ] .ll_pm())
            (GetSampleInfo(Sample::ttww         ).name, m_yield["ttww"         ] .ee_pm() , m_yield["ttww"         ] .mm_pm() , m_yield["ttww"         ] .em_pm() , m_yield["ttww"         ] .ll_pm())
            (GetSampleInfo(Sample::wwg          ).name, m_yield["wwg"          ] .ee_pm() , m_yield["wwg"          ] .mm_pm() , m_yield["wwg"          ] .em_pm() , m_yield["wwg"          ] .ll_pm())
            (GetSampleInfo(Sample::www          ).name, m_yield["www"          ] .ee_pm() , m_yield["www"          ] .mm_pm() , m_yield["www"          ] .em_pm() , m_yield["www"          ] .ll_pm())
            (GetSampleInfo(Sample::wwz          ).name, m_yield["wwz"          ] .ee_pm() , m_yield["wwz"          ] .mm_pm() , m_yield["wwz"          ] .em_pm() , m_yield["wwz"          ] .ll_pm())
            (GetSampleInfo(Sample::wzz          ).name, m_yield["wzz"          ] .ee_pm() , m_yield["wzz"          ] .mm_pm() , m_yield["wzz"          ] .em_pm() , m_yield["wzz"          ] .ll_pm())
            (GetSampleInfo(Sample::zzz          ).name, m_yield["zzz"          ] .ee_pm() , m_yield["zzz"          ] .mm_pm() , m_yield["zzz"          ] .em_pm() , m_yield["zzz"          ] .ll_pm())
            (GetSampleInfo(Sample::wpwpqq       ).name, m_yield["wpwpqq"       ] .ee_pm() , m_yield["wpwpqq"       ] .mm_pm() , m_yield["wpwpqq"       ] .em_pm() , m_yield["wpwpqq"       ] .ll_pm())
            (GetSampleInfo(Sample::wmwmqq       ).name, m_yield["wmwmqq"       ] .ee_pm() , m_yield["wmwmqq"       ] .mm_pm() , m_yield["wmwmqq"       ] .em_pm() , m_yield["wmwmqq"       ] .ll_pm())
            (GetSampleInfo(Sample::ww_ds        ).name, m_yield["ww_ds"        ] .ee_pm() , m_yield["ww_ds"        ] .mm_pm() , m_yield["ww_ds"        ] .em_pm() , m_yield["ww_ds"        ] .ll_pm())
            (GetSampleInfo(Sample::wh_zh_tth_hww).name, m_yield["wh_zh_tth_hww"] .ee_pm() , m_yield["wh_zh_tth_hww"] .mm_pm() , m_yield["wh_zh_tth_hww"] .em_pm() , m_yield["wh_zh_tth_hww"] .ll_pm())
            (GetSampleInfo(Sample::wh_zh_tth_hzz).name, m_yield["wh_zh_tth_hzz"] .ee_pm() , m_yield["wh_zh_tth_hzz"] .mm_pm() , m_yield["wh_zh_tth_hzz"] .em_pm() , m_yield["wh_zh_tth_hzz"] .ll_pm())
            (GetSampleInfo(Sample::wh_zh_tth_htt).name, m_yield["wh_zh_tth_htt"] .ee_pm() , m_yield["wh_zh_tth_htt"] .mm_pm() , m_yield["wh_zh_tth_htt"] .em_pm() , m_yield["wh_zh_tth_htt"] .ll_pm())
            ("Total MC"                               , yield_mc.ee_pm()                  , yield_mc.mm_pm()                  , yield_mc.em_pm()                  , yield_mc.ll_pm()                 ) 
            ("MC Pred"                                , yield_rare.ee_syst_pm()           , yield_rare.mm_syst_pm()           , yield_rare.em_syst_pm()           , yield_rare.ll_syst_pm()          )            
            ("Total Pred"                             , yield_pred.ee_syst_pm()           , yield_pred.mm_syst_pm()           , yield_pred.em_syst_pm()           , yield_pred.ll_syst_pm()          );
        
        // print it
        t_yields.print();
    }
}
