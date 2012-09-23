#ifndef SSANALYSISLOOPER_H 
#define SSANALYSISLOOPER_H

#include "at/AnalysisWithTree.h"
#include "Math/LorentzVector.h"
#include <tr1/array>
#include <tr1/memory>
#include <vector>
#include <string>
#include "SameSignTree.h"

class TH2F;

// typdefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

class SSAnalysisLooper : public at::AnalysisWithTree
{
    public:
        // construct:
        SSAnalysisLooper
        (
            const std::string& root_file_name,
            const at::Sample::value_type& sample,
            const std::string& fake_rate_file_name,
            const std::string& flip_rate_file_name,
            const std::string& fake_rate_hist_name = "h_mufr40c",
            const std::string& vtxreweight_file_name = "",
            const std::string& goodrun_file_name = "",
            double luminosity = 1.0,
            int njets = 0,
            bool sparms = false,
            int jetMetScale = 0,
            bool is_fast_sim = false,
			bool sync_print = false,
            bool verbose = false
        );

        // destroy:
        ~SSAnalysisLooper();

        // function operator:
        int operator() (long event);

        // members:
        virtual void BeginJob();
        virtual void EndJob();
        int Analyze(long event);

    private:
        // members:
        at::Sample::value_type m_sample;
        double m_lumi;
        int  m_njets;
        int  m_jetMetScale;
        bool m_is_fast_sim;
        bool m_filter_bad_runs;
        bool m_sparms;
		bool m_sync_print;
        bool m_verbose;

        // 0 mm, 1 em, 2 ee
        std::tr1::array<float, 4> m_count_ss;
        std::tr1::array<float, 4> m_count_sf;
        std::tr1::array<float, 4> m_count_df;
        std::tr1::array<float, 4> m_count_os;

        std::tr1::array<float, 4> m_count_nobtag_ss;
        std::tr1::array<float, 4> m_count_nobtag_sf;
        std::tr1::array<float, 4> m_count_nobtag_df;
        std::tr1::array<float, 4> m_count_nobtag_os;

        // fake rate hists
        std::tr1::shared_ptr<TH2F> h_mufr;
        std::tr1::shared_ptr<TH2F> h_elfr;
        std::tr1::shared_ptr<TH2F> h_flip;

        // struct to hold tree values
        SameSignTree m_evt;

    private:
        // methods:
        float GetFakeRateValue(int lep_id, int lep_idx) const;
        float GetFlipRateValue(int lep_id, int lep_idx) const;
};

#endif // SSANALYSISLOOPER_H 
