#ifndef PLOTLOOPER_H
#define PLOTLOOPER_H

#include "at/AnalysisWithHist.h"
#include "at/Sample.h"
#include "at/DileptonHypType.h"
#include "at/FakeRateBinInfo.h"
#include "at/FlipRateBinInfo.h"
#include "SignalRegion.h"
#include "AnalysisType.h"
#include <string>
#include <tr1/array>
#include <tr1/memory>
#include <vector>
#include "TH2F.h"
#include "FakeRateType.h"
#include "EWKINO2012_SS.h"

class PlotLooper : public at::AnalysisWithHist
{
public:
    // construct:
    PlotLooper
    (
        const std::string& root_file_name,
        at::Sample::value_type sample,
        ewkino::SignalRegion::value_type signal_region = ewkino::SignalRegion::sr0,
        ewkino::AnalysisType::value_type analysis_type = ewkino::AnalysisType::ss,
        ewkino::SignalRegionType::value_type signal_region_type = ewkino::SignalRegionType::inclusive,
        const std::string& vtxreweight_file_name = "",
        const std::string& fake_rate_file_name = "",
        const std::string& flip_rate_file_name = "",
        const std::string& event_list_name = "",
        int charge_option = 0,
        bool do_scale_factors = true,
        bool check_good_lumi = false,
        float sparm0 = -999,
        float sparm1 = -999,
        float sf_flip = 1.0,
        float fr_unc = 0.5,
        float fl_unc = 0.3,
        float mc_unc = 0.5,
        float lumi = 1.0,
        bool use_cp_unc = true,
        bool verbose = false
    );

    // destroy:
    ~PlotLooper();

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
    bool m_do_vtx_reweight;
    bool m_do_scale_factors;
    bool m_check_good_lumi;
    bool m_use_cp_unc;
    int m_charge_option;
    float m_sparm0;
    float m_sparm1;
    float m_scale1fb;
    float m_xsec;
    int m_nevts;
    float m_sf_flip;
    float m_fr_unc;
    float m_fl_unc;
    float m_mc_unc;    
    at::Sample::value_type m_sample;
    ewkino::SignalRegion::value_type m_signal_region;
    ewkino::AnalysisType::value_type m_analysis_type;
    ewkino::SignalRegionType::value_type m_signal_region_type;
    at::FakeRateBinInfo m_fr_bin_info;
    at::FlipRateBinInfo m_fl_bin_info;

    // fake/flip rate hists
    std::tr1::shared_ptr<TH2F> h_mufr;
    std::tr1::shared_ptr<TH2F> h_elfr;
    std::tr1::shared_ptr<TH2F> h_flip;

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

    bool passesMVAJetId(LorentzVector p4, float mva_value, int tightness);    
};

#endif // PLOTLOOPER_HPP
