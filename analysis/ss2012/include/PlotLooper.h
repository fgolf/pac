#ifndef SS_FAKEPREDLOOPER_HPP
#define SS_FAKEPREDLOOPER_HPP

#include "at/AnalysisWithHist.h"
#include "at/Sample.h"
#include "at/DileptonHypType.h"
#include "SignalRegion.h"
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
             const std::string& vtxreweight_file_name = "",
             const std::string& fake_rate_file_name = "",
             const std::string& flip_rate_file_name = "",
             unsigned int num_btags = 0,
             bool do_scale_factors = true,
             bool bheck_good_lumi = false,
			 float mass_glu = 1000,
			 float mass_lsp = 100,
			 float lumi = 1.0,
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
		float m_mass_glu;
		float m_mass_lsp;
		at::Sample::value_type m_sample;
        ss::SignalRegion::value_type m_signal_region;

        // fake/flip rate hists
        std::tr1::shared_ptr<TH2F> h_mufr;
        std::tr1::shared_ptr<TH2F> h_elfr;
        std::tr1::shared_ptr<TH2F> h_flip;

        // methods
        float GetFakeRateValue(int lep_id, float pt, float eta) const;
        float GetFakeRateError(int lep_id, float pt, float eta) const;

        float GetFlipRateValue(int lep_id, float pt, float eta) const; 
        float GetFlipRateError(int lep_id, float pt, float eta) const; 

        TH1F GetSingleFakePredRaw() const;
        TH1F GetDoubleFakePred() const;

        void FillDoubleFakeHist();
        void FillDoubleFakeHist
        (
            TH2F* hist, 
            const at::DileptonHypType::value_type& hyp, 
            int id1, 
            float pt1, 
            float eta1, 
            int id2, 
            float pt2, 
            float eta2, 
            float weight
        );
};

#endif // SS_FAKEPREDLOOPER_HPP
