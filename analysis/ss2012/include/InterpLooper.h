#ifndef PLOTLOOPER_H
#define PLOTLOOPER_H

#include "at/AnalysisWithHist.h"
#include "at/Sample.h"
#include "at/DileptonHypType.h"
#include "at/FakeRateBinInfo.h"
#include "at/FlipRateBinInfo.h"
#include "at/YieldType.h"
#include "SignalRegion.h"
#include "AnalysisType.h"
#include <string>
#include <tr1/array>
#include <tr1/memory>
#include <vector>
#include "TH2F.h"
#include "FakeRateType.h"

class InterpLooper : public at::AnalysisWithHist
{
public:
    // construct:
    InterpLooper
    (
        const std::string& root_file_name,
        at::Sample::value_type sample,
        //ss::SignalRegion::value_type signal_region = ss::SignalRegion::sr0,
        ss::AnalysisType::value_type analysis_type = ss::AnalysisType::high_pt,
        ss::SignalRegionType::value_type signal_region_type = ss::SignalRegionType::inclusive,
        //at::YieldType::value_type yield_type = at::YieldType::base,
        const std::string& fake_rate_file_name = "",
        const std::string& flip_rate_file_name = "",
        const std::string& den_hist_file_name = "",
        bool do_scale_factors = true,
        float sparm0 = -999999.0,
        float sparm1 = -999999.0,
        float sparm2 = -999999.0,
        float sparm3 = -999999.0,
        float sf_flip = 1.0,
        float fr_unc = 0.5,
        float fl_unc = 0.3,
        float mc_unc = 0.5,
        float lumi = 1.0,
        bool verbose = false
    );

    // destroy:
    ~InterpLooper();

    // function operator:
    int operator()(long event);

    // members
    virtual void BeginJob();
    virtual void EndJob();
    virtual void BookHists();

private:
    // members
    float m_lumi;
    bool m_verbose;
    bool m_is_data;
    bool m_do_scale_factors;
    float m_sparm0;
    float m_sparm1;
    float m_sparm2;
    float m_sparm3;
    float m_scale1fb;
    int m_nevts;
    float m_sf_flip;
    float m_fr_unc;
    float m_fl_unc;
    float m_mc_unc;
    at::Sample::value_type m_sample;
    //ss::SignalRegion::value_type m_signal_region;
    ss::AnalysisType::value_type m_analysis_type;
    ss::SignalRegionType::value_type m_signal_region_type;
    //at::YieldType::value_type m_yield_type;
    at::FakeRateBinInfo m_fr_bin_info;
    at::FlipRateBinInfo m_fl_bin_info;

    // fake/flip rate hists
    std::tr1::shared_ptr<TH2F> h_mufr;
    std::tr1::shared_ptr<TH2F> h_elfr;
    std::tr1::shared_ptr<TH2F> h_flip;

    // den
    std::tr1::shared_ptr<TH2F> h_den;

    // quick count check
    std::tr1::array<float, 4> m_count_ss;
    std::tr1::array<float, 4> m_count_sf;
    std::tr1::array<float, 4> m_count_df;
    std::tr1::array<float, 4> m_count_os;

    // methods
    float GetFakeRateValue(int lep_id, float pt, float eta) const;
    float GetFakeRateError(int lep_id, float pt, float eta) const;
    at::FakeRateBinInfo GetFakeRateBinInfo() const;

    float GetFlipRateValue(int lep_id, float pt, float eta) const; 
    float GetFlipRateError(int lep_id, float pt, float eta) const; 
    at::FlipRateBinInfo GetFlipRateBinInfo() const;

    // systematics
    void SetJESSystematic();
    void SetBtagSystematic();
    void SetTotalSystematic();
    void SetTotalSignalContamination();
    void CalculateEfficiency();
    
};

#endif // PLOTLOOPER_HPP
