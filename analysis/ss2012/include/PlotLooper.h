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

class PlotLooper : public at::AnalysisWithHist
{
public:
    // construct:
    PlotLooper
    (
        const std::string& root_file_name,
        at::Sample::value_type sample,
        ss::SignalRegion::value_type signal_region = ss::SignalRegion::sr0,
        ss::AnalysisType::value_type analysis_type = ss::AnalysisType::high_pt,
        ss::SignalRegionType::value_type signal_region_type = ss::SignalRegionType::inclusive,
        const std::string& vtxreweight_file_name = "",
        const std::string& fake_rate_file_name = "",
        const std::string& flip_rate_file_name = "",
        const std::string& event_list_name = "",
        const unsigned int num_btags = 0,
        const unsigned int num_jets = 0,
        const int charge_option = 0,
        const bool do_scale_factors = true,
        const bool check_good_lumi = false,
        const bool do_3lep_veto = false,
        const float sparm0 = -999,
        const float sparm1 = -999,
        const float sparm2 = -999,
        const float sparm3 = -999,
        const float sf_flip = 1.0,
        const float fr_unc = 0.5,
        const float fl_unc = 0.2,
        const float mc_unc = 0.5,
        const float lumi = 1.0,
        //const float l1_min_pt = 20.0,
        //const float l1_max_pt = 10000000.0,
        //const float l2_min_pt = 20.0,
        //const float l2_max_pt = 10000000.0,
        const float min_ht = 80.0,
        const bool verbose = false
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
    const bool m_verbose;
    const bool m_is_data;
    const bool m_do_vtx_reweight;
    const bool m_do_scale_factors;
    const bool m_check_good_lumi;
    const bool m_do_3lep_veto;
    const unsigned int m_nbtags;
    const unsigned int m_njets;
    const int m_charge_option;
    const float m_sparm0;
    const float m_sparm1;
    const float m_sparm2;
    const float m_sparm3;
    float m_scale1fb;
    float m_xsec;
    int m_nevts;
    const float m_sf_flip;
    const float m_fr_unc;
    const float m_fl_unc;
    const float m_mc_unc;
    //float m_l1_min_pt;
    //float m_l1_max_pt;
    //float m_l2_min_pt;
    //float m_l2_max_pt;
    const float m_min_ht;
    const at::Sample::value_type m_sample;
    const ss::SignalRegion::value_type m_signal_region;
    const ss::AnalysisType::value_type m_analysis_type;
    const ss::SignalRegionType::value_type m_signal_region_type;
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

    bool Passes3rdLeptonSelection() const;
};

#endif // PLOTLOOPER_HPP
