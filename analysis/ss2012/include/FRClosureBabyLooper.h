#ifndef FRCLOSUREBABYLOOPER_H 
#define FRCLOSUREBABYLOOPER_H

#include "at/AnalysisWithTree.h"
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

class FRClosureBabyLooper : public at::AnalysisWithTree
{
public:
    // construct:
    FRClosureBabyLooper
    (
        const std::string& root_file_name,
        const at::Sample::value_type& sample,
        const ss::AnalysisType::value_type& analysis_type,
        const std::string& fake_rate_file_name,
        const std::string& fake_rate_hist_name = "h_mufr40c",
        const std::string& vtxreweight_file_name = "",
        int njets = 0,
        int jetMetScale = 0,
        bool use_el_eta = false,
        bool verbose = false,
        const std::string apply_jec_otf = "",
        double jet_pt_cut = -1
    );

    // destroy:
    ~FRClosureBabyLooper();

    // function operator:
    int operator() (long event, const std::string& filename);

    // members:
    virtual void BeginJob();
    virtual void EndJob();
    virtual void BookHists();
    int Analyze(long event, const std::string& filename);
    int SetJetCorrector(std::vector<std::string> &list_of_filenames);

private:
    // members:
    at::Sample::value_type m_sample;
    ss::AnalysisType::value_type m_analysis_type;
    double m_lumi;
    int  m_njets;
    int  m_jetMetScale;
    bool m_use_el_eta;
    bool m_verbose;
    double m_jet_pt_cut;
    int m_hyp_count;

    // fake rate hists
    std::tr1::shared_ptr<TH2F> h_mufr;
    std::tr1::shared_ptr<TH2F> h_elfr;

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

    // jet args
    at::JetBaseSelectionArgs m_jet_args;

private:
    // methods:
    float GetFakeRateValue(int lep_id, int lep_idx) const;
};

#endif // FRCLOSUREBABYLOOPER_H 
