#include "SSYields.h"
#include <string>
#include <iostream>
#include <cmath>
#include "TString.h" 
#include "rt/RootTools.h" 

using namespace std;

namespace ss
{
    // construct
    Yield::Yield() 
        : ee  (0.0)
        , dee (0.0)
        , see (0.0)
        , mm  (0.0)
        , dmm (0.0)
        , smm (0.0)
        , em  (0.0)
        , dem (0.0)
        , sem (0.0)
        , ll  (0.0)
        , dll (0.0)
        , sll (0.0)
    {}

    Yield::Yield
    (
        const std::pair<float, float> ee_, 
        const std::pair<float, float> mm_, 
        const std::pair<float, float> em_, 
        const std::pair<float, float> ll_ 
    )
        : ee  (ee_.first)
        , dee (ee_.second)
        , see (0.0)
        , mm  (mm_.first)
        , dmm (mm_.second)
        , smm (0.0)
        , em  (em_.first)
        , dem (em_.second)
        , sem (0.0)
        , ll (ll_.first)
        , dll(ll_.second)
        , sll(0.0)
    {}

    Yield::Yield
    (
         float ee_, 
         float dee_, 
         float mm_, 
         float dmm_, 
         float em_, 
         float dem_, 
         float ll_,
         float dll_ 
    )
        : ee  (ee_)
        , dee (dee_) 
        , see (0.0)
        , mm  (mm_)  
        , dmm (dmm_) 
        , smm (0.0)
        , em  (em_)  
        , dem (dem_) 
        , sem (0.0)
        , ll (ll_) 
        , dll(dll_)
        , sll(0.0)
    {}

    Yield::Yield
    (
        float ee_, 
        float dee_, 
        float see_, 
        float mm_, 
        float dmm_, 
        float smm_, 
        float em_, 
        float dem_, 
        float sem_, 
        float ll_,
        float dll_,
        float sll_ 
    )
        : ee  (ee_)
        , dee (dee_) 
        , see (see_)
        , mm  (mm_)  
        , dmm (dmm_) 
        , smm (smm_)
        , em  (em_)  
        , dem (dem_) 
        , sem (sem_)
        , ll (ll_) 
        , dll(dll_)
        , sll(sll_)
    {}

    // methods:
    Yield& Yield::operator+=(const Yield& y)
    {
        Yield temp_yield = (*this) + y;
        *this = temp_yield;
        return *this; 
    }

    Yield& Yield::operator-=(const Yield& y)
    {
        Yield temp_yield = (*this) - y;
        *this = temp_yield;
        return *this; 
    }

    float Yield::tee() const {return (sqrt(see*see + dee*dee));}
    float Yield::tmm() const {return (sqrt(smm*smm + dmm*dmm));}
    float Yield::tem() const {return (sqrt(sem*sem + dem*dem));}
    float Yield::tll() const {return (sqrt(sll*sll + dll*dll));}

    std::string Yield::ee_pm() const {return rt::pm(ee, dee, "1.2");}
    std::string Yield::mm_pm() const {return rt::pm(mm, dmm, "1.2");}
    std::string Yield::em_pm() const {return rt::pm(em, dem, "1.2");}
    std::string Yield::ll_pm() const {return rt::pm(ll, dll, "1.2");}

    std::string Yield::GetLatex(const std::string& title, const std::string& latex, bool print_sys_err) const
    {
        string result;
        if (rt::string_contains(title, "data"))
        {
            const char* format = "%35s & %5.0f & %5.0f & %5.0f & %5.0f";
            result = Form(format, not latex.empty() ? latex.c_str() : title.c_str(), ee, mm, em, ll);
        }
        else
        {
            if (print_sys_err)
            {
                const char* format = "%35s & %5.2f $\\pm$ %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f $\\pm$ %5.2f";
                result = Form(format, not latex.empty() ? latex.c_str() : title.c_str(), ee, dee, see, mm, dmm, smm, em, dem, sem, ll, dll, sll);
                if (rt::string_contains(title, "Flip"))
                {
                    format = "%35s & %5.2f $\\pm$ %5.2f $\\pm$ %5.2f & - $\\pm$ - $\\pm$ - & %5.2f $\\pm$ %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f $\\pm$ %5.2f";
                    result = Form(format, not latex.empty() ? latex.c_str() : title.c_str(), ee, dee, see, em, dem, sem, ll, dll, sll);
                }
            }
            else
            {
                const char* format = "%35s & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f";
                result = Form(format, not latex.empty() ? latex.c_str() : title.c_str(), ee, tee(), mm, tmm(), em, tem(), ll, tll());
                if (rt::string_contains(title, "Flip"))
                {
                    format = "%35s & %5.2f $\\pm$ %5.2f & - $\\pm$ - & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f";
                    result = Form(format, not latex.empty() ? latex.c_str() : title.c_str(), ee, tee(), mm, tmm(), em, tem(), ll, tll());
                }
            }

        }
        return result;
    }

    void Yield::Print(const std::string& title, bool print_sys_err) const
    {
        if (rt::string_contains(title, "data"))
        {
            const char* format = "%15s ee: %15.0f mm: %15.0f em: %15.0f ll: %15.0f";
            cout << Form(format, title.c_str(), ee, mm, em, ll) << endl;
        }
        else
        {
            if (print_sys_err)
            {
                const char* format = "%15s ee: %2.2f +/- %2.2f +/- %2.2f mm: %2.2f +/- %2.2f +/- %2.2f em: %2.2f +/- %2.2f +/- %2.2f ll: %2.2f +/- %2.2f +/- %2.2f";
                cout << Form(format, title.c_str(), ee, dee, see, mm, dmm, smm, em, dem, sem, ll, dll, sll) << endl;
            }
            else
            {
                const char* format = "%15s ee: %2.2f +/- %2.2f mm: %2.2f +/- %2.2f em: %2.2f +/- %2.2f ll: %2.2f +/- %2.2f";
                cout << Form(format, title.c_str(), ee, dee, mm, dmm, em, dem, ll, dll) << endl;
            }
        }
    }

    // non member methods
    void SetErrorsToBogus(Yield& y)
    {
        y.dee = 999;
        y.dmm = 999;
        y.dem = 999;
        y.dll = 999;
    }

    void SetSysUncertainties(Yield& y, float percent)
    {
        y.see = y.ee * percent;
        y.smm = y.mm * percent;
        y.sem = y.em * percent;
        y.sll = y.ll * percent;
    }

    float DetermineError(float v1, float v2, float e1, float e2)
    {
        // test for zero yield condition
        if (rt::is_zero(v1) && rt::is_zero(v2))
        {
            return std::max(e1, e2);    
        }
        else if (rt::is_zero(v1) && not rt::is_zero(v2))
        {
            return e2;
        }
        else if (not rt::is_zero(v1) && rt::is_zero(v2))
        {
            return e1;
        }
        else
        {
            return sqrt(e1*e1 + e2*e2);
        }
    }

    // add the uncertainties not worrying about whether the value is zero
    Yield AddUncertaintiesAbsolute(const Yield& y1, const Yield& y2)
    {
        Yield result(y1.ee + y2.ee, sqrt(y1.dee*y1.dee + y2.dee*y2.dee), sqrt(y1.see*y1.see + y2.see*y2.see), 
                     y1.mm + y2.mm, sqrt(y1.dmm*y1.dmm + y2.dmm*y2.dmm), sqrt(y1.smm*y1.smm + y2.smm*y2.smm), 
                     y1.em + y2.em, sqrt(y1.dem*y1.dem + y2.dem*y2.dem), sqrt(y1.sem*y1.sem + y2.sem*y2.sem), 
                     y1.ll + y2.ll, sqrt(y1.dll*y1.dll + y2.dll*y2.dll), sqrt(y1.sll*y1.sll + y2.sll*y2.sll));
        return result; 
    }

    // container getter 
    rt::TH1Container GetSampleHists
    (
    	const at::Sample::value_type sample, 
    	const ss::SignalRegion::value_type signal_region, 
    	const ss::AnalysisType::value_type analysis_type, 
    	const ss::SignalRegionType::value_type signal_region_type, 
    	int charge_option, 
    	const std::string& output_path
    )
    {
        // charge option (1 == ++, -1 == --)
        std::string charge_stem = "";
        switch (charge_option)
        {
            case  1: charge_stem = "_pp"; break;
            case -1: charge_stem = "_mm"; break;
            default: {/*do nothing*/}
        }

    	const std::string& sample_name             = at::GetSampleInfo(sample).name;
    	const std::string& analysis_type_name      = ss::GetAnalysisTypeInfo(analysis_type).name;
    	const std::string& signal_region_type_name = ss::GetSignalRegionTypeName(signal_region_type);
    	const std::string& signal_region_name      = ss::GetSignalRegionInfo(signal_region, analysis_type, signal_region_type).name;
    
        // hists  
        rt::TH1Container hc(Form("plots/%s/%s/%s/%s/%s%s.root",
    							  output_path.c_str(),
    							  analysis_type_name.c_str(),
    							  signal_region_type_name.c_str(),
    							  signal_region_name.c_str(),
    							  sample_name.c_str(),
    							  charge_stem.c_str()));
        return hc;
    }

    // get the yields per sample
    Yield GetSSYield
    (
    	const at::Sample::value_type sample, 
    	const ss::SignalRegion::value_type signal_region, 
    	const ss::AnalysisType::value_type analysis_type, 
    	const ss::SignalRegionType::value_type signal_region_type, 
    	int charge_option, 
    	const std::string& output_path
    )
    {
        // hists  
        rt::TH1Container hc = GetSampleHists(sample, signal_region, analysis_type, signal_region_type, charge_option, output_path);
        pair<double, double> ee = rt::IntegralAndError(hc["h_yield_ee"]);
        pair<double, double> mm = rt::IntegralAndError(hc["h_yield_mm"]);
        pair<double, double> em = rt::IntegralAndError(hc["h_yield_em"]);
        pair<double, double> ll = rt::IntegralAndError(hc["h_yield_ll"]);
        Yield yield(ee, mm, em, ll);
    
        // done
        return yield;
    }
    
    // get the fake yields per sample
    Yield GetDFYield
    (
    	const at::Sample::value_type sample, 
    	const ss::SignalRegion::value_type signal_region, 
    	const ss::AnalysisType::value_type analysis_type, 
    	const ss::SignalRegionType::value_type signal_region_type, 
    	int charge_option, 
    	const std::string& output_path
    )
    {
        // hists  
        rt::TH1Container hc = GetSampleHists(sample, signal_region, analysis_type, signal_region_type, charge_option, output_path);
        pair<double, double> mm(hc["h_df_pred"]->GetBinContent(1), hc["h_df_pred"]->GetBinError(1));
        pair<double, double> ee(hc["h_df_pred"]->GetBinContent(2), hc["h_df_pred"]->GetBinError(2));
        pair<double, double> em(hc["h_df_pred"]->GetBinContent(3), hc["h_df_pred"]->GetBinError(3));
        pair<double, double> ll(hc["h_df_pred"]->GetBinContent(4), hc["h_df_pred"]->GetBinError(4));
        Yield yield(ee, mm, em, ll);
    
        // done
        return yield;
    }
    
    // get the fake yields per sample
    Yield GetSFYield
    (
    	const at::Sample::value_type sample, 
    	const ss::SignalRegion::value_type signal_region, 
    	const ss::AnalysisType::value_type analysis_type, 
    	const ss::SignalRegionType::value_type signal_region_type, 
    	int charge_option, 
    	const std::string& output_path
    )
    {
        // hists  
        rt::TH1Container hc = GetSampleHists(sample, signal_region, analysis_type, signal_region_type, charge_option, output_path);
        pair<double, double> mm(hc["h_sf_pred"]->GetBinContent(1), hc["h_sf_pred"]->GetBinError(1));
        pair<double, double> ee(hc["h_sf_pred"]->GetBinContent(2), hc["h_sf_pred"]->GetBinError(2));
        pair<double, double> em(hc["h_sf_pred"]->GetBinContent(3), hc["h_sf_pred"]->GetBinError(3));
        pair<double, double> ll(hc["h_sf_pred"]->GetBinContent(4), hc["h_sf_pred"]->GetBinError(4));
        Yield yield(ee, mm, em, ll);
    
        // done
        return yield;
    }
    
    // get the fake yields per sample
    Yield GetFakeYield
    (
    	const at::Sample::value_type sample, 
    	const ss::SignalRegion::value_type signal_region, 
    	const ss::AnalysisType::value_type analysis_type, 
    	const ss::SignalRegionType::value_type signal_region_type, 
    	int charge_option, 
    	const std::string& output_path
    )
    {
        // hists  
        rt::TH1Container hc = GetSampleHists(sample, signal_region, analysis_type, signal_region_type, charge_option, output_path);
        pair<double, double> mm(hc["h_fake_pred"]->GetBinContent(1), hc["h_fake_pred"]->GetBinError(1));
        pair<double, double> ee(hc["h_fake_pred"]->GetBinContent(2), hc["h_fake_pred"]->GetBinError(2));
        pair<double, double> em(hc["h_fake_pred"]->GetBinContent(3), hc["h_fake_pred"]->GetBinError(3));
        pair<double, double> ll(hc["h_fake_pred"]->GetBinContent(4), hc["h_fake_pred"]->GetBinError(4));
        Yield yield(ee, mm, em, ll);
    
        // done
        return yield;
    }
    
    // get the fake yields per sample
    Yield GetFlipYield
    (
    	const at::Sample::value_type sample, 
    	const ss::SignalRegion::value_type signal_region, 
    	const ss::AnalysisType::value_type analysis_type, 
    	const ss::SignalRegionType::value_type signal_region_type, 
    	int charge_option, 
    	const std::string& output_path
    )
    {
        // hists  
        rt::TH1Container hc = GetSampleHists(sample, signal_region, analysis_type, signal_region_type, charge_option, output_path);
        pair<double, double> mm(hc["h_flip_pred"]->GetBinContent(1), hc["h_flip_pred"]->GetBinError(1));
        pair<double, double> ee(hc["h_flip_pred"]->GetBinContent(2), hc["h_flip_pred"]->GetBinError(2));
        pair<double, double> em(hc["h_flip_pred"]->GetBinContent(3), hc["h_flip_pred"]->GetBinError(3));
        pair<double, double> ll(hc["h_flip_pred"]->GetBinContent(4), hc["h_flip_pred"]->GetBinError(4));
        Yield yield(ee, mm, em, ll);
    
        // done
        return yield;
    }

    // get the yields per sample (switch to determine if signal or bg prediction)
    Yield GetYield
    (
    	std::string option, 
    	const at::Sample::value_type sample, 
    	const ss::SignalRegion::value_type signal_region, 
    	const ss::AnalysisType::value_type analysis_type, 
    	const ss::SignalRegionType::value_type signal_region_type, 
    	int charge_option, 
    	const std::string& output_path
    )
    {
        option = rt::string_lower(option);
        if      (option == "ss"  ) {return GetSSYield  (sample, signal_region, analysis_type, signal_region_type, charge_option, output_path);}
        else if (option == "sf"  ) {return GetSFYield  (sample, signal_region, analysis_type, signal_region_type, charge_option, output_path);}
        else if (option == "df"  ) {return GetDFYield  (sample, signal_region, analysis_type, signal_region_type, charge_option, output_path);}
        else if (option == "fake") {return GetFakeYield(sample, signal_region, analysis_type, signal_region_type, charge_option, output_path);}
        else if (option == "flip") {return GetFlipYield(sample, signal_region, analysis_type, signal_region_type, charge_option, output_path);}
        else
        {
            throw std::invalid_argument(Form("[ss::GetYield] invalid option %s", option.c_str()));
        }
    }

    std::map<std::string, ss::Yield> GetYieldsMap
    (
        const std::string& option,
        const ss::SignalRegion::value_type signal_region, 
        const ss::AnalysisType::value_type analysis_type, 
        const ss::SignalRegionType::value_type signal_region_type, 
        int charge_option, 
        const std::string& output_path
    )
    {
        using namespace at;
        std::map<std::string, ss::Yield> m;
    
        // data
        m["data"] = GetYield(option, Sample::data, signal_region, analysis_type, signal_region_type, charge_option, output_path);
    
        // for display only
        m["ttdil"  ] = GetYield(option, Sample::ttdil  , signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["ttslb"  ] = GetYield(option, Sample::ttslb  , signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["ttslo"  ] = GetYield(option, Sample::ttslo  , signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["ttotr"  ] = GetYield(option, Sample::ttotr  , signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["t_schan"] = GetYield(option, Sample::t_schan, signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["t_tchan"] = GetYield(option, Sample::t_tchan, signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["t_tw"   ] = GetYield(option, Sample::t_tw   , signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["dy"     ] = GetYield(option, Sample::dy     , signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["wjets"  ] = GetYield(option, Sample::wjets  , signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["ww"     ] = GetYield(option, Sample::ww     , signal_region, analysis_type, signal_region_type, charge_option, output_path);
    
        // to include in prediction
        // wgstar;
        m["wgstar"]  = GetYield(option, Sample::wgstar2e, signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["wgstar"] += GetYield(option, Sample::wgstar2m, signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["wgstar"] += GetYield(option, Sample::wgstar2t, signal_region, analysis_type, signal_region_type, charge_option, output_path);
    
        // wwqq;
        m["wwqq"] += GetYield(option, Sample::wmwmqq, signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["wwqq"] += GetYield(option, Sample::wpwpqq, signal_region, analysis_type, signal_region_type, charge_option, output_path);
                                    
        // the rest of the rare MC
        m["wz"   ] = GetYield(option, Sample::wz   , signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["zz"   ] = GetYield(option, Sample::zz   , signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["ttg"  ] = GetYield(option, Sample::ttg  , signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["ttw"  ] = GetYield(option, Sample::ttw  , signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["ttz"  ] = GetYield(option, Sample::ttz  , signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["tbz"  ] = GetYield(option, Sample::tbz  , signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["ttww" ] = GetYield(option, Sample::ttww , signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["wwg"  ] = GetYield(option, Sample::wwg  , signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["www"  ] = GetYield(option, Sample::www  , signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["wwz"  ] = GetYield(option, Sample::wwz  , signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["wzz"  ] = GetYield(option, Sample::wzz  , signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["zzz"  ] = GetYield(option, Sample::zzz  , signal_region, analysis_type, signal_region_type, charge_option, output_path);
        m["ww_ds"] = GetYield(option, Sample::ww_ds, signal_region, analysis_type, signal_region_type, charge_option, output_path);
    
        // want the total of the MC
        ss::Yield yield_mc;
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["ttdil"  ]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["ttslb"  ]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["ttslo"  ]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["ttotr"  ]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["t_schan"]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["t_tchan"]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["t_tw"   ]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["dy"     ]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["wjets"  ]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["ww"     ]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["wgstar" ]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["wwqq"   ]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["wz"     ]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["zz"     ]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["ttg"    ]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["ttw"    ]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["ttz"    ]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["tbz"    ]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["ttww"   ]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["wwg"    ]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["www"    ]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["wwz"    ]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["wzz"    ]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["zzz"    ]); 
        yield_mc = AddUncertaintiesAbsolute(yield_mc, m["ww_ds"  ]); 
        m["mc"] = yield_mc;
    
     
        // want the rare MC only for the prediction
        ss::Yield yield_rare;
        yield_rare = AddUncertaintiesAbsolute(yield_rare, m["wgstar"]); 
        yield_rare = AddUncertaintiesAbsolute(yield_rare, m["wwqq"  ]); 
        yield_rare = AddUncertaintiesAbsolute(yield_rare, m["wz"    ]); 
        yield_rare = AddUncertaintiesAbsolute(yield_rare, m["zz"    ]); 
        yield_rare = AddUncertaintiesAbsolute(yield_rare, m["ttg"   ]); 
        yield_rare = AddUncertaintiesAbsolute(yield_rare, m["ttw"   ]); 
        yield_rare = AddUncertaintiesAbsolute(yield_rare, m["ttz"   ]); 
        yield_rare = AddUncertaintiesAbsolute(yield_rare, m["tbz"   ]); 
        yield_rare = AddUncertaintiesAbsolute(yield_rare, m["ttww"  ]); 
        yield_rare = AddUncertaintiesAbsolute(yield_rare, m["wwg"   ]); 
        yield_rare = AddUncertaintiesAbsolute(yield_rare, m["www"   ]); 
        yield_rare = AddUncertaintiesAbsolute(yield_rare, m["wwz"   ]); 
        yield_rare = AddUncertaintiesAbsolute(yield_rare, m["wzz"   ]); 
        yield_rare = AddUncertaintiesAbsolute(yield_rare, m["zzz"   ]); 
        yield_rare = AddUncertaintiesAbsolute(yield_rare, m["ww_ds" ]); 
        m["rare"] = yield_rare;
     
        // done
        return m;
    }
} // namespace ss


// non-member methods
ss::Yield operator*(float scale, const ss::Yield& y)
{
    using namespace ss;
    Yield result(scale * y.ee, scale * y.dee, 
                 scale * y.mm, scale * y.dmm, 
                 scale * y.em, scale * y.dem, 
                 scale * y.ll, scale * y.dll);
    return result; 
}

ss::Yield operator-(const ss::Yield& y1, const ss::Yield& y2)
{
    using namespace ss;
    Yield result(y1.ee - y2.ee, DetermineError(y1.ee, y2.ee, y1.dee, y2.dee), DetermineError(y1.ee, y2.ee, y1.see, y2.see), 
                 y1.mm - y2.mm, DetermineError(y1.mm, y2.mm, y1.dmm, y2.dmm), DetermineError(y1.mm, y2.mm, y1.smm, y2.smm), 
                 y1.em - y2.em, DetermineError(y1.em, y2.em, y1.dem, y2.dem), DetermineError(y1.em, y2.em, y1.sem, y2.sem), 
                 y1.ll - y2.ll, DetermineError(y1.ll, y2.ll, y1.dll, y2.dll), DetermineError(y1.ll, y2.ll, y1.sll, y2.sll));
    return result; 
}

ss::Yield operator+(const ss::Yield& y1, const ss::Yield& y2)
{
    using namespace ss;
    Yield result(y1.ee + y2.ee, DetermineError(y1.ee, y2.ee, y1.dee, y2.dee), DetermineError(y1.ee, y2.ee, y1.see, y2.see), 
                 y1.mm + y2.mm, DetermineError(y1.mm, y2.mm, y1.dmm, y2.dmm), DetermineError(y1.mm, y2.mm, y1.smm, y2.smm), 
                 y1.em + y2.em, DetermineError(y1.em, y2.em, y1.dem, y2.dem), DetermineError(y1.em, y2.em, y1.sem, y2.sem), 
                 y1.ll + y2.ll, DetermineError(y1.ll, y2.ll, y1.dll, y2.dll), DetermineError(y1.ll, y2.ll, y1.sll, y2.sll));
    return result; 
}



