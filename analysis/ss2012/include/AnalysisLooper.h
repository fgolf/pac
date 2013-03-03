#ifndef SSANALYSISLOOPER_H 
#define SSANALYSISLOOPER_H

#include "at/AnalysisWithTreeAndHist.h"
#include "Math/LorentzVector.h"
#include <tr1/array>
#include <tr1/memory>
#include <vector>
#include <string>
#include "SameSignTree.h"
#include "AnalysisType.h"

class TH2F;
class FactorizedJetCorrector;
class MetCorrector;

// typdefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

class SSAnalysisLooper : public at::AnalysisWithTreeAndHist
{
public:
    // construct:
    SSAnalysisLooper
    (
        const std::string& root_file_name,
        const at::Sample::value_type& sample,
        const ss::AnalysisType::value_type& analysis_type,
        const std::string& fake_rate_file_name,
        const std::string& flip_rate_file_name,
        const std::string& vtxreweight_file_name = "",
        const std::string& goodrun_file_name = "",
        const double luminosity = 1.0,
        const int njets = 0,
        const bool sparms = false,
        const int jetMetScale = 0,
        const bool is_fast_sim = false,
        const bool use_el_eta = true,
        const bool sync_print = false,
        const bool verbose = false,
        const std::string apply_jec_otf = "",
        const double jet_pt_cut = -1
    );

    // destroy:
    ~SSAnalysisLooper();

    // function operator:
    int operator() (long event, const std::string& filename);

    // members:
    virtual void BeginJob();
    virtual void EndJob();
    virtual void BookHists();
    int Analyze(const long event, const std::string& filename);
    int SetJetCorrector(std::vector<std::string>& list_of_filenames);

private:
    // members:
    at::Sample::value_type m_sample;
    ss::AnalysisType::value_type m_analysis_type;
    double m_lumi;
    int  m_njets;
    bool m_sparms;
    int  m_jetMetScale;
    bool m_is_fast_sim;
    bool m_use_el_eta;
    bool m_filter_bad_runs;
    bool m_sync_print;
    bool m_verbose;
    double m_jet_pt_cut;
    int m_hyp_count;

    // fake rate hists
    std::tr1::shared_ptr<TH2F> h_mufr;
    std::tr1::shared_ptr<TH2F> h_elfr;
    std::tr1::shared_ptr<TH2F> h_flip;

    // on-the-fly JEC
    FactorizedJetCorrector* m_jet_corrector;
    MetCorrector* m_met_corrector;
    std::vector<std::string> m_list_of_jec_filenames;

    // 0 mm, 1 em, 2 ee
    std::tr1::array<float, 4> m_count_ss;
    std::tr1::array<float, 4> m_count_sf;
    std::tr1::array<float, 4> m_count_df;
    std::tr1::array<float, 4> m_count_os;

    std::tr1::array<float, 4> m_count_nobtag_ss;
    std::tr1::array<float, 4> m_count_nobtag_sf;
    std::tr1::array<float, 4> m_count_nobtag_df;
    std::tr1::array<float, 4> m_count_nobtag_os;

    // struct to hold tree values
    SameSignTree m_evt;

private:
    // methods:
    bool IsNumerator(const int lep_id, const int lep_idx);
    bool IsDenominator(const int lep_id, const int lep_idx);
    bool IsFO(const int lep_id, const int lep_idx);

    float GetFakeRateValue(const int lep_id, const int lep_idx) const;
    float GetFlipRateValue(const int lep_id, const int lep_idx) const;
};

#endif // SSANALYSISLOOPER_H 
