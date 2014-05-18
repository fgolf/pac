#ifndef FRCLOSURELOOPER_HPP
#define FRCLOSURELOOPER_HPP

#include "at/AnalysisWithHist.h"
#include "at/Sample.h"
#include "at/DileptonHypType.h"
#include "SignalRegion.h"
#include <string>
#include <tr1/array>
#include <tr1/memory>
#include <vector>
#include "TH2F.h"
#include "FakeRateType.h"

class FRClosureLooper : public at::AnalysisWithHist
{
public:
    // construct:
    FRClosureLooper
    (
        const std::string& root_file_name,
        const at::Sample::value_type sample,
        const ss::SignalRegion::value_type signal_region = ss::SignalRegion::sr0,
        const ss::AnalysisType::value_type analysis_type = ss::AnalysisType::high_pt,
        const ss::SignalRegionType::value_type signal_region_type = ss::SignalRegionType::inclusive,
        const std::string& vtxreweight_file_name = "",
        const std::string& fake_rate_file_name = "",
        const std::string& mufr_hist_name = "",
        const std::string& elfr_hist_name = "",
        const bool do_scale_factors = true,
        const bool do_scale1fb = false,
        const unsigned int num_btags = 0,
        const unsigned int num_jets = 2,
        const float met_cut = -99999,
        const float ht_cut = -99999,
        const int charge_option = 0,
        const float lumi = 1.0,
        const bool verbose = false,
	const int  FR_option = 0,
	const int truth_match_option = 0,
	const bool do_mc_trigger = false
    );

    // destroy:
    ~FRClosureLooper();

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
    int  m_FR_option;
    bool m_is_data;
    bool m_do_vtx_reweight;
    bool m_do_scale_factors;
    bool m_do_scale1fb;
    unsigned int m_nbtags;
    unsigned int m_njets;
    float m_met_cut;
    float m_ht_cut;
    int m_charge_option;
    at::Sample::value_type m_sample;
    ss::SignalRegion::value_type m_signal_region;
    ss::AnalysisType::value_type m_analysis_type;
    ss::SignalRegionType::value_type m_signal_region_type;
    float m_scale1fb;
    at::FakeRateBinInfo m_fr_bin_info;
    int m_truth_match_option;
    bool m_do_mc_trigger; 

    // fake/flip rate hists
    std::tr1::shared_ptr<TH2F> h_mufr;
    std::tr1::shared_ptr<TH2F> h_elfr;

    // methods
    float GetFakeRateValue(int lep_id, float pt, float eta) const;
    float GetFakeRateError(int lep_id, float pt, float eta) const;
    at::FakeRateBinInfo GetFakeRateBinInfo();
};

#endif // FRCLOSURELOOPER_HPP
