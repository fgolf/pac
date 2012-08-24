#ifndef SS_FAKERATESTUDY_H
#define SS_FAKERATESTUDY_H

#include "at/AnalysisWithHist.h"
#include <string>
#include "Sample.h"

class FakeRateStudy : public at::AnalysisWithHist
{
    public:
        // construct:
        FakeRateStudy
        (
             const std::string& root_file_name,
             const fr::Sample::value_type& sample,
             const std::string& lepton,
             const std::string& vtxreweight_file_name = "",
			 float lumi = 1.0,
             //float away_jet_cut = 40.0,
             int charge = 0,
             bool verbose = false,
             bool print = false,
             const std::string& suffix = "png"
        );

        // destroy:
        ~FakeRateStudy();

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
        std::string m_;
		float m_lumi;
        //float m_away_jet_cut;
		TH1F m_hist_ratio_evt_nvtxs;
        int m_charge;
};

#endif // SS_FAKERATESTUDY_H
