#ifndef SS_FAKERATEBABYLOOPER_H
#define SS_FAKERATEBABYLOOPER_H

#include "FakeRateType.h"
#include "at/FakeRateBinInfo.h"
#include "at/AnalysisWithHist.h"
#include "fr/Sample.h"
#include <string>

class FakeRateBabyLooper : public at::AnalysisWithHist
{
public:
    // construct:
    FakeRateBabyLooper
    (
        const std::string& root_file_name,
        fr::Sample::value_type sample,
        const std::string& lepton,
        const ss::FakeRateType::value_type& fr_type,
        bool apply_tight_d0_cut = true,
        bool use_eth_binning = false,
        float lumi = 1.0,
        int charge = 0,
        bool verbose = false,
        bool print = false,
        const std::string& suffix = "png",
        float away_jet_pt = -1.,
        float away_jet_dphi = -1.,
        float mu_iso_denom = -1.
        );

    // destroy:
    ~FakeRateBabyLooper();

    // function operator:
    int operator()(long event, const std::string& current_file_name = "");

    // members
    virtual void BeginJob();
    virtual void EndJob();
    virtual void BookHists();    

private:
    // members
    fr::Sample::value_type m_sample;
    std::string m_lepton;
    ss::FakeRateType::value_type m_fr_type;
    bool m_apply_tight_d0_cut;
    bool m_use_eth_binning;
    float m_lumi;
    int m_charge;
    bool m_verbose;
    at::FakeRateBinInfo m_fr_bin_info;
    float m_away_jet_pt;
    float m_away_jet_dphi;
    float m_mu_iso_denom;
};

#endif // SS_FAKERATEBABYLOOPER_HPP
