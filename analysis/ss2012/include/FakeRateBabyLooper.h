#ifndef SS_FAKERATEBABYLOOPER_H
#define SS_FAKERATEBABYLOOPER_H

#include "FakeRateType.h"
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
        const std::string& suffix = "png"
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
    int m_charge;
    float m_lumi;
    bool m_verbose;
    bool m_use_eth_binning;
    ss::FakeRateBinInfo m_fr_bin_info;
};

#endif // SS_FAKERATEBABYLOOPER_HPP
