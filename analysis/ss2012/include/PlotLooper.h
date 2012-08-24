#ifndef SS_FAKEPREDLOOPER_HPP
#define SS_FAKEPREDLOOPER_HPP

#include "at/AnalysisWithHist.h"
#include "at/Sample.h"
#include "SignalRegion.h"
#include <string>
#include <tr1/array>
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
             SignalRegion::value_type signal_region = SignalRegion::sr0,
             const std::string& vtxreweight_file_name = "",
             const std::string& fr_file_name = "",
             const std::string& fr_hist_name = "",
             unsigned int num_btags = 0,
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
        unsigned int m_nbtags;
		float m_mass_glu;
		float m_mass_lsp;
		at::Sample::value_type m_sample;
        SignalRegion::value_type m_signal_region;

        // 0 mm, 1 em, 2 ee, 3 all
        std::tr1::array<float, 4> m_count_ss;
};

#endif // SS_FAKEPREDLOOPER_HPP
