#ifndef TRILEPTONZANALYSISLOOPER_H 
#define TRILEPTONZANALYSISLOOPER_H

#include "at/AnalysisWithTree.h"
#include "Math/LorentzVector.h"
#include <tr1/array>
#include <tr1/memory>
#include <vector>
#include <string>
#include "TrileptonZTree.h"

class TH2F;
class FactorizedJetCorrector;
class MetCorrector;
class EGammaMvaEleEstimator;

// typdefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

class TrileptonZAnalysisLooper : public at::AnalysisWithTree
{
public:
    // construct:
    TrileptonZAnalysisLooper
    (
        const std::string& root_file_name,
        const at::Sample::value_type& sample,
        const std::string& fake_rate_file_name,
        const std::string& mfake_rate_hist_name = "h_mufr40c",
        const std::string& efake_rate_hist_name = "h_elfr40c",
        const std::string& vtxreweight_file_name = "",
        const std::string& goodrun_file_name = "",
        double luminosity = 1.0,
        int njets = 0,
        int nbtags = 0,
        int jetMetScale = 0,
        bool sync_print = false,
        bool verbose = false,
        const std::string apply_jec_otf = "",
        const std::string ele_mva_path = "/home/users/pac/analysis/ttv2012/data/electron_mva/"
        );

    // destroy:
    ~TrileptonZAnalysisLooper();

    // function operator:
    int operator() (long event);

    // members:
    virtual void BeginJob();
    virtual void EndJob();
    int Analyze(long event);
    int SetJetCorrector(std::vector<std::string> &list_of_filenames);
    int SetTriggeringElectronMVA(std::vector<std::string> &list_of_filenames);
    int SetNonTriggeringElectronMVA(std::vector<std::string> &list_of_filenames);

private:
    // members:
    at::Sample::value_type m_sample;
    double m_lumi;
    int  m_njets;
    int  m_nbtags;
    int  m_jetMetScale;
    bool m_filter_bad_runs;
    bool m_sync_print;
    bool m_verbose;

    // 0 eee, 1 eem, 2 mme, 3 mmm, 4 eme, 5 emm
    std::tr1::array<float, 7> m_count;
    std::tr1::array<float, 7> m_count_sf;
    std::tr1::array<float, 7> m_count_df;
    std::tr1::array<float, 7> m_count_tf;

    std::tr1::array<float, 7> m_count_nobtag;
    std::tr1::array<float, 7> m_count_nobtag_sf;
    std::tr1::array<float, 7> m_count_nobtag_df;
    std::tr1::array<float, 7> m_count_nobtag_tf;

    // fake rate hists
    std::tr1::shared_ptr<TH2F> h_mufr;
    std::tr1::shared_ptr<TH2F> h_elfr;

    // struct to hold tree values
    TrileptonZTree m_evt;

    // on-the-fly JEC
    FactorizedJetCorrector *jet_corrector;
    MetCorrector *met_corrector;

    // electron ID MVA
    EGammaMvaEleEstimator* trigEleMVA;
    EGammaMvaEleEstimator* nontrigEleMVA;

    std::vector<std::string> m_list_of_jec_filenames;
private:
    // methods:
    float GetFakeRateValue(int lep_id, int lep_idx) const;
    int GetGenTrilepHyp (float zwin = 15.);
    bool LepPassesEta (int id, int index);
    const float zmass;
    const float mu_eta;
    const float ele_eta;
};

#endif // TRILEPTONZANALYSISLOOPER_H 
