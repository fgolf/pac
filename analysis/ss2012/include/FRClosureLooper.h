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

class FRClosureLooper : public at::AnalysisWithHist
{
    public:
        // construct:
        FRClosureLooper
        (
             const std::string& root_file_name,
             at::Sample::value_type sample,
             ss::SignalRegion::value_type signal_region = ss::SignalRegion::sr0,
             const std::string& vtxreweight_file_name = "",
             const std::string& fake_rate_file_name = "",
             const std::string& mufr_hist_name = "",
             const std::string& elfr_hist_name = "",
             bool do_scale_factors = true,
             unsigned int num_btags = 0,
             unsigned int num_jets = 0,
             int charge_option = 0,
             float lumi = 1.0,
             bool verbose = false
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
        bool m_is_data;
        bool m_do_vtx_reweight;
        bool m_do_scale_factors;
        unsigned int m_nbtags;
        unsigned int m_njets;
        int m_charge_option;
        at::Sample::value_type m_sample;
        ss::SignalRegion::value_type m_signal_region;
        float m_scale1fb;

        // fake/flip rate hists
        std::tr1::shared_ptr<TH2F> h_mufr;
        std::tr1::shared_ptr<TH2F> h_elfr;

        // methods
        float GetFakeRateValue(int lep_id, float pt, float eta) const;
        float GetFakeRateError(int lep_id, float pt, float eta) const;
};

#endif // FRCLOSURELOOPER_HPP