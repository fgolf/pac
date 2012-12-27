#ifndef PLOTLOOPER_H
#define PLOTLOOPER_H

#include "at/AnalysisWithHist.h"
#include "at/Sample.h"
#include "at/DileptonHypType.h"
#include "SignalRegion.h"
#include "AnalysisType.h"
#include <string>
#include <tr1/array>
#include <tr1/memory>
#include <vector>
#include "TH2F.h"

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
             const std::string& vtxreweight_file_name = "",
             const std::string& fake_rate_file_name = "",
             const std::string& flip_rate_file_name = "",
             const std::string& event_list_name = "",
             unsigned int num_btags = 0,
             unsigned int num_jets = 0,
             int charge_option = 0,
             bool do_scale_factors = true,
             bool bheck_good_lumi = false,
             float sparm0 = -999,
             float sparm1 = -999,
             float sparm2 = -999,
             float sparm3 = -999,
             float sf_flip = 1.0,
             float lumi = 1.0,
             float min_pt = 20.0,
             float max_pt = 10000000.0,
             float min_ht = 80.0,
             bool verbose = false,
             bool print = false,
             const std::string& suffix = "png"
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
        unsigned int m_nbtags;
        unsigned int m_njets;
        int m_charge_option;
        float m_sparm0;
        float m_sparm1;
        float m_sparm2;
        float m_sparm3;
        float m_scale1fb;
        float m_sf_flip;
        float m_min_pt;
        float m_max_pt;
        float m_min_ht;
        at::Sample::value_type m_sample;
        ss::SignalRegion::value_type m_signal_region;
        ss::AnalysisType::value_type m_analysis_type;

        // fake/flip rate hists
        std::tr1::shared_ptr<TH2F> h_mufr;
        std::tr1::shared_ptr<TH2F> h_elfr;
        std::tr1::shared_ptr<TH2F> h_flip;

        // methods
        float GetFakeRateValue(int lep_id, float pt, float eta) const;
        float GetFakeRateError(int lep_id, float pt, float eta) const;

        float GetFlipRateValue(int lep_id, float pt, float eta) const; 
        float GetFlipRateError(int lep_id, float pt, float eta) const; 
};

#endif // PLOTLOOPER_HPP
