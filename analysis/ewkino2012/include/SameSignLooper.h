#ifndef EWKINOSSANALYSISLOOPER_H 
#define EWKINOSSANALYSISLOOPER_H

#include "at/AnalysisWithTreeAndHist.h"
#include "Math/LorentzVector.h"
#include <tr1/array>
#include <tr1/memory>
#include <vector>
#include <string>
#include "SameSignTree.h"
#include "AnalysisType.h"
#include "metSelections.h"
#include "jetcorr/FactorizedJetCorrector.h"
#include "jetcorr/JetCorrectionUncertainty.h"

class TH2F;

// typdefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

class EwkinoSSAnalysisLooper : public at::AnalysisWithTreeAndHist
{
public:
    // construct:
    EwkinoSSAnalysisLooper
    (
        const std::string& root_file_name,
        const at::Sample::value_type& sample,
        const ewkino::AnalysisType::value_type& analysis_type,
        const std::string& fake_rate_file_name,
        const std::string& flip_rate_file_name,
        const std::string& vtxreweight_file_name = "",
        const std::string& goodrun_file_name = "",
        const double luminosity = 1.0,
        const int njets = 0,
        const bool sparms = false,
        const int jetMetScale = 0,
        const bool is_fast_sim = false,
        const bool sync_print = false,
        const bool verbose = false,
        const std::string apply_jec_otf = "",
        const std::string apply_jec_unc = "",
        const double jet_pt_cut = -1
    );

    // destroy:
    ~EwkinoSSAnalysisLooper();

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
    ewkino::AnalysisType::value_type m_analysis_type;
    double m_lumi;
    int  m_njets;
    bool m_sparms;
    int  m_jetMetScale;
    bool m_is_fast_sim;
    bool m_filter_bad_runs;
    bool m_sync_print;
    bool m_verbose;
    float m_jet_pt_cut;
    int m_hyp_count;

    // fake rate hists
    std::tr1::shared_ptr<TH2F> h_mufr;
    std::tr1::shared_ptr<TH2F> h_elfr;
    std::tr1::shared_ptr<TH2F> h_flip;

    // on-the-fly JEC
    std::tr1::shared_ptr<FactorizedJetCorrector> m_jet_corrector;
    std::tr1::shared_ptr<MetCorrector> m_met_corrector;
    std::tr1::shared_ptr<JetCorrectionUncertainty> m_jet_corr_unc;
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

    // struct for sorting
    struct SortByPt 
    {
        bool operator () (const LorentzVector& lhs, const LorentzVector& rhs) 
        {
            return lhs.pt() > rhs.pt();
        }
        
        bool operator () (const std::pair<LorentzVector, int>& lhs, const std::pair<LorentzVector, int>& rhs) 
        {
            return lhs.first.pt() > rhs.first.pt();
        }

        bool operator () (const std::pair<LorentzVector, bool>& lhs, const std::pair<LorentzVector, bool>& rhs) 
        {
            return lhs.first.pt() > rhs.first.pt();
        }
    };

private:
    // methods:
    bool IsNumerator(const int lep_id, const int lep_idx);
    bool IsDenominator(const int lep_id, const int lep_idx);
    bool IsFO(const int lep_id, const int lep_idx);

    float GetFakeRateValue(const int lep_id, const int lep_idx) const;
    float GetFlipRateValue(const int lep_id, const int lep_idx) const;

    bool passesIsoTrkVeto();
    bool passesTauVeto();
    bool passesMVAJetId(LorentzVector p4, float mva_value, int tightness);

    std::vector<int> getJetMcAlgoMatch(const unsigned int best_hyp_idx, int systFlag, bool sort_by_pt = true);
    std::vector<int> getJetMcPhysMatch(const unsigned int best_hyp_idx, int systFlag, bool sort_by_pt = true);

    std::vector<bool> sortBtaggedFlags(const std::vector<LorentzVector>& all_jet_p4s, const std::vector<bool>& all_jet_flags, const std::vector<bool>& all_bjet_flags);
};

#endif // EWKINOSSANALYSISLOOPER_H 
