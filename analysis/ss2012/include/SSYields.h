#ifndef SS_YIELDS_H
#define SS_YIELDS_H

#include <string>
#include "rt/TH1Container.h"
#include "SignalRegion.h"
#include "AnalysisType.h"
#include "at/Sample.h"

namespace ss
{
    // simple class to hold the yield values
    struct Yield
    {
        // construct
        Yield();
        Yield
        (
             const std::pair<float, float> ee_, 
             const std::pair<float, float> mm_, 
             const std::pair<float, float> em_, 
             const std::pair<float, float> ll_ 
        );
        Yield
        (
             float ee_, 
             float dee_, 
             float mm_, 
             float dmm_, 
             float em_, 
             float dem_, 
             float ll_,
             float dll_ 
        );
        Yield
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
        );

        // members
        float ee;
        float dee;
        float see;
        float mm;
        float dmm;
        float smm;
        float em;
        float dem;
        float sem;
        float ll;
        float dll;
        float sll;

        // methods:
        Yield& operator+=(const Yield& y);
        Yield& operator-=(const Yield& y);

        float tee() const;
        float tmm() const;
        float tem() const;
        float tll() const;

        std::string ee_pm() const;
        std::string mm_pm() const;
        std::string em_pm() const;
        std::string ll_pm() const;

        std::string ee_syst_pm() const;
        std::string mm_syst_pm() const;
        std::string em_syst_pm() const;
        std::string ll_syst_pm() const;

        std::string GetLatex(const std::string& title, const std::string& latex = "", bool print_sys_err = false) const;
        void Print(const std::string& title, bool print_sys_err = false) const;
    };

    // non member methods

    void SetErrorsToBogus(Yield& y);
    void SetSysUncertainties(Yield& y, float percent);
    float DetermineError(float v1, float v2, float e1, float e2);

    // add the uncertainties not worrying about whether the value is zero
    Yield AddUncertaintiesAbsolute(const Yield& y1, const Yield& y2);

    // container getter 
    rt::TH1Container GetSampleHists
    (
    	const at::Sample::value_type sample, 
    	const ss::SignalRegion::value_type signal_region, 
    	const ss::AnalysisType::value_type analysis_type, 
    	const ss::SignalRegionType::value_type signal_region_type, 
    	const int charge_option, 
    	const std::string& output_path
    );

    // get the SS yields per sample
    Yield GetSSYield
    (
    	const at::Sample::value_type sample, 
    	const ss::SignalRegion::value_type signal_region, 
    	const ss::AnalysisType::value_type analysis_type, 
    	const ss::SignalRegionType::value_type signal_region_type, 
    	const int charge_option, 
    	const std::string& output_path
    );
    
    // get the fake yields per sample
    Yield GetDFYield
    (
    	const at::Sample::value_type sample, 
    	const ss::SignalRegion::value_type signal_region, 
    	const ss::AnalysisType::value_type analysis_type, 
    	const ss::SignalRegionType::value_type signal_region_type, 
    	const int charge_option, 
    	const std::string& output_path
    );

    // get the fake yields per sample
    Yield GetSFYield
    (
    	const at::Sample::value_type sample, 
    	const ss::SignalRegion::value_type signal_region, 
    	const ss::AnalysisType::value_type analysis_type, 
    	const ss::SignalRegionType::value_type signal_region_type, 
    	const int charge_option, 
    	const std::string& output_path
    );

    // get the fake yields per sample
    Yield GetFakeYield
    (
    	const at::Sample::value_type sample, 
    	const ss::SignalRegion::value_type signal_region, 
    	const ss::AnalysisType::value_type analysis_type, 
    	const ss::SignalRegionType::value_type signal_region_type, 
    	const int charge_option, 
    	const std::string& output_path
    );
    
    // get the fake yields per sample
    Yield GetFlipYield
    (
    	const at::Sample::value_type sample, 
    	const ss::SignalRegion::value_type signal_region, 
    	const ss::AnalysisType::value_type analysis_type, 
    	const ss::SignalRegionType::value_type signal_region_type, 
    	const int charge_option, 
    	const std::string& output_path
    );

    // get the yields per sample (switch to determine if signal or bg prediction)
    Yield GetYield
    (
    	std::string option, 
    	const at::Sample::value_type sample, 
    	const ss::SignalRegion::value_type signal_region, 
    	const ss::AnalysisType::value_type analysis_type, 
    	const ss::SignalRegionType::value_type signal_region_type, 
    	const int charge_option, 
    	const std::string& output_path
    );

    // return a map of all the Yields for data and MC
    std::map<std::string, ss::Yield> GetYieldsMap
    (
        const std::string& option,
        const ss::SignalRegion::value_type signal_region, 
        const ss::AnalysisType::value_type analysis_type, 
        const ss::SignalRegionType::value_type signal_region_type, 
        const int charge_option = 0, 
        const std::string& output_path = "test"
    );

} // namespace ss

// non-members
ss::Yield operator-(const ss::Yield& y1, const ss::Yield& y2);
ss::Yield operator+(const ss::Yield& y1, const ss::Yield& y2);
ss::Yield operator*(float scale, const ss::Yield& y);


#endif // SS_YIELDS_H

