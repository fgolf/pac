#ifndef SSANALYSISLOOPER_H 
#define SSANALYSISLOOPER_H

#include "at/AnalysisWithTreeAndHist.h"
#include "Math/LorentzVector.h"
#include <memory>
#include <vector>
#include <string>
#include "SameSignTree.h"
#include "AnalysisType.h"
#include "metSelections.h"
#include "jetcorr/FactorizedJetCorrector.h"
#include "jetcorr/JetCorrectionUncertainty.h"
#include "boost/shared_ptr.hpp"

class TH2F;

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
        const std::string apply_jec_unc = "",
        const double jet_pt_cut = -1,
        const bool switch_signs = false
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
    float m_jet_pt_cut;
    bool m_switch_signs;
    int m_hyp_count;

    // fake rate hists
    boost::shared_ptr<TH2F> h_mufr;
    boost::shared_ptr<TH2F> h_elfr;
    boost::shared_ptr<TH2F> h_flip;

    // on-the-fly JEC
    boost::shared_ptr<FactorizedJetCorrector> m_jet_corrector;
    boost::shared_ptr<MetCorrector> m_met_corrector;
    boost::shared_ptr<JetCorrectionUncertainty> m_jet_corr_unc;
    std::vector<std::string> m_list_of_jec_filenames;

    // 0 mm, 1 em, 2 ee
    float m_count_ss[4];
    float m_count_sf[4];
    float m_count_df[4];
    float m_count_os[4];

    float m_count_nobtag_ss[4];
    float m_count_nobtag_sf[4];
    float m_count_nobtag_df[4];
    float m_count_nobtag_os[4];

    // struct to hold tree values
    SameSignTree m_evt;

private:

    // methods:
    bool IsNumerator(const int lep_id, const int lep_idx);
    bool IsDenominator(const int lep_id, const int lep_idx);
    bool IsFO(const int lep_id, const int lep_idx);

    float GetFakeRateValue(const int lep_id, const int lep_idx) const;
    float GetFlipRateValue(const int lep_id, const int lep_idx) const;

    bool PassesIsoTrkVeto(const LorentzVector& l1_p4, const LorentzVector& l2_p4) const;
    bool PassesTauVeto() const;

    // members:
    at::JetBaseSelectionArgs m_jet_args;
    at::JetBaseSelectionArgs m_jet_args_jec_up;
    at::JetBaseSelectionArgs m_jet_args_jec_dn;
    at::JetBaseSelectionArgs m_jet_args_jer;
    at::JetBaseSelectionArgs m_jet_args_pt30;
    at::JetBaseSelectionArgs m_uncorrected_jet_args;
};

#endif // SSANALYSISLOOPER_H 
