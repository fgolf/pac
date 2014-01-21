#include "FakeRateBaby.h"
#include "FakeRateBabyLooper.h"
#include "mcSelections.h"
#include "electronSelections.h"
#include "rt/RootTools.h"
#include <iostream>
#include <algorithm>
#include <tr1/array>
#include <cmath>

typedef std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > vecLorentzVector;

// construct:
FakeRateBabyLooper::FakeRateBabyLooper
(
    const std::string& root_file_name,
    fr::Sample::value_type sample,
    const std::string& lepton,
    const ss::FakeRateType::value_type& fr_type,
    bool apply_tight_d0_cut,
    bool use_eth_binning,
    float lumi,
    int charge, 
    bool verbose,
    bool print,
    const std::string& suffix,
    float away_jet_pt,
    float away_jet_dphi,
    float mu_iso_denom,
    bool btag_away_jet,
    bool absolute_iso,
    bool only_invert_isocut_mu,
    bool use_FOpt
    )
    : at::AnalysisWithHist(root_file_name, print, suffix)
    , m_sample(sample)
    , m_lepton(lepton)
    , m_fr_type(fr_type)
    , m_apply_tight_d0_cut(apply_tight_d0_cut)
    , m_use_eth_binning(use_eth_binning)
    , m_lumi(lumi)
    , m_charge(charge)
    , m_verbose(verbose)
    , m_away_jet_pt(away_jet_pt)
    , m_away_jet_dphi(away_jet_dphi)
    , m_mu_iso_denom(mu_iso_denom)
    , m_btag_away_jet(btag_away_jet)
    , m_absolute_iso(absolute_iso)
    , m_only_invert_isocut_mu(only_invert_isocut_mu)
    , m_use_FOpt(use_FOpt)
{
    // begin job
    BeginJob();
}

// destroy:
FakeRateBabyLooper::~FakeRateBabyLooper()
{
}

// methods:
void FakeRateBabyLooper::BeginJob()
{    
    m_fr_bin_info = ss::GetFakeRateBinInfo(m_use_eth_binning);

    // pT cut
    float min_mu_pt = m_fr_bin_info.mu_pt_bins()[0];
    float max_mu_pt = m_fr_bin_info.mu_pt_bins()[m_fr_bin_info.num_mu_pt_bins()];

    std::cout << "\nmuon binning: ";
    std::copy(m_fr_bin_info.vmu_pt_bins.begin(), m_fr_bin_info.vmu_pt_bins.end(), std::ostream_iterator<float>(std::cout, " "));
    printf("\nmin,max muon pt cuts: %4.2f, %4.2f\n", min_mu_pt, max_mu_pt);

    float min_el_pt = m_fr_bin_info.el_pt_bins()[0];
    float max_el_pt = m_fr_bin_info.el_pt_bins()[m_fr_bin_info.num_el_pt_bins()];

    std::cout << "electron binning: ";
    std::copy(m_fr_bin_info.vel_pt_bins.begin(), m_fr_bin_info.vel_pt_bins.end(), std::ostream_iterator<float>(std::cout, " "));
    printf("\nmin,max electron pt cuts: %4.2f, %4.2f\n", min_el_pt, max_el_pt);

    // figure out away jet pt
    if (m_away_jet_pt < 0.)
    {
        if (m_fr_type == ss::FakeRateType::hpt || m_fr_type == ss::FakeRateType::truncated) m_away_jet_pt = 40.;
        else if (m_fr_type == ss::FakeRateType::eth) m_away_jet_pt = 50.;
    }

    assert(not (m_away_jet_pt < 0.));
    printf("minimum away jet pt cut: %4.2f GeV\n", m_away_jet_pt);

    // figure out muon isolation extrapolation
    if (m_mu_iso_denom < 0.)
    {
        if (m_fr_type == ss::FakeRateType::hpt || m_fr_type == ss::FakeRateType::truncated) m_mu_iso_denom = 0.4;
        else if (m_fr_type == ss::FakeRateType::eth) m_mu_iso_denom = 1.0;
    }

    assert(not (m_mu_iso_denom < 0.));
    printf("muon isolation extrapolation: %4.2f\n", m_mu_iso_denom);

    if (m_btag_away_jet)
        printf("require away jet is b-tagged\n");

    // book histos
    BookHists();
}

// selection functions (to be moved to another file maybe)
float iso_corr()
{
    using namespace frb;
    return iso() - ((log(pt()) * evt_nvtxs())/(30 * pt())); 
}

float pfiso03_corr()
{
    using namespace frb;
    return pfiso03() - ((log(pt()) * evt_nvtxs())/(75 * pt())); 
}

float pfiso03_corr_rho()
{
    using namespace frb;
    const float eff_area = fastJetEffArea03_v2(sceta()); 
    return (ch_pfiso03() + max(0.0f, nh_pfiso03() + em_pfiso03() - (max(0.0f, rho())*eff_area)))/pt();
}

float pfiso03_corr_db()
{
    using namespace frb;
    return (ch_pfiso03() + max(0.0f, nh_pfiso03() + em_pfiso03() - (0.5f*pfpupt03())))/pt();
}

float cpfiso03_rho_truncated()
{
    using namespace frb;
    // const float eff_area = fastJetEffArea03_v2(sceta()); 
    // return (ch_pfiso03() + max(0.0f, nh_pfiso03() + em_pfiso03() - (max(0.0f, rho())*eff_area)))/max(20.0f, pt());
    return (cpfiso03_rho()*pt())/max(20.0f, pt());
}

float cpfiso03_db_truncated()
{
    using namespace frb;
    // return (ch_pfiso03() + max(0.0f, nh_pfiso03() + em_pfiso03() - (0.5f*pfpupt03())))/pt();
    return (cpfiso03_db()*pt())/max(20.0f, pt());
}


// end job
void FakeRateBabyLooper::EndJob()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    // muons
    if (m_lepton == "mu")
    {   
        // FR(# vertices)
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num20c_vs_nvtxs"],hc["h_mu_fo20c_vs_nvtxs"], "h_mufr20c_vs_nvtxs", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 20, p_{T} > 20);# vtxs"));
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num40c_vs_nvtxs"],hc["h_mu_fo40c_vs_nvtxs"], "h_mufr40c_vs_nvtxs", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 40, p_{T} > 20);# vtxs"));
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num60c_vs_nvtxs"],hc["h_mu_fo60c_vs_nvtxs"], "h_mufr60c_vs_nvtxs", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 60, p_{T} > 20);# vtxs"));

        // FR(pt)
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num20c"],hc["h_mu_fo20c"], "y", "h_mufr20c_vs_pt", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 20);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num40c"],hc["h_mu_fo40c"], "y", "h_mufr40c_vs_pt", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 40);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num60c"],hc["h_mu_fo60c"], "y", "h_mufr60c_vs_pt", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 60);p_{T}"));
                                                                                                                                                      
        // FR(eta)
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num20c"],hc["h_mu_fo20c"], "x", "h_mufr20c_vs_eta", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 20, p_{T} > 20);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num40c"],hc["h_mu_fo40c"], "x", "h_mufr40c_vs_eta", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 40, p_{T} > 20);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num60c"],hc["h_mu_fo60c"], "x", "h_mufr60c_vs_eta", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 60, p_{T} > 20);|#eta|", 20, 100));

        // FR(eta, pT)
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num20c"],hc["h_mu_fo20c"], "h_mufr20c", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 20);|#eta|;p_{T} (GeV)"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num40c"],hc["h_mu_fo40c"], "h_mufr40c", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 40);|#eta|;p_{T} (GeV)"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num60c"],hc["h_mu_fo60c"], "h_mufr60c", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 60);|#eta|;p_{T} (GeV)"));

//        // FR(# vertices)
//        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num20c_iso_vs_nvtxs"],hc["h_mu_fo20c_iso_vs_nvtxs"], "h_mufr20c_iso_vs_nvtxs", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 20, p_{T} > 5, iso);# vtxs"));
//        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num40c_iso_vs_nvtxs"],hc["h_mu_fo40c_iso_vs_nvtxs"], "h_mufr40c_iso_vs_nvtxs", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 40, p_{T} > 5, iso);# vtxs"));
//        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num60c_iso_vs_nvtxs"],hc["h_mu_fo60c_iso_vs_nvtxs"], "h_mufr60c_iso_vs_nvtxs", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 60, p_{T} > 5, iso);# vtxs"));
//
//        // FR(pt)
//        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num20c_iso"],hc["h_mu_fo20c_iso"], "y", "h_mufr20c_iso_vs_pt", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 20, iso);p_{T}"));
//        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num40c_iso"],hc["h_mu_fo40c_iso"], "y", "h_mufr40c_iso_vs_pt", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 40, iso);p_{T}"));
//        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num60c_iso"],hc["h_mu_fo60c_iso"], "y", "h_mufr60c_iso_vs_pt", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 60, iso);p_{T}"));
//                                                                                                                                                      
//        // FR(eta)
//        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num20c_iso"],hc["h_mu_fo20c_iso"], "x", "h_mufr20c_iso_vs_eta", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 20, p_{T} > 5, iso);|#eta|", 5, 100));
//        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num40c_iso"],hc["h_mu_fo40c_iso"], "x", "h_mufr40c_iso_vs_eta", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 40, p_{T} > 5, iso);|#eta|", 5, 100));
//        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num60c_iso"],hc["h_mu_fo60c_iso"], "x", "h_mufr60c_iso_vs_eta", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 60, p_{T} > 5, iso);|#eta|", 5, 100));
//
//        // FR(eta, pT)
//        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num20c_iso"],hc["h_mu_fo20c_iso"], "h_mufr20c_iso", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 20, iso);|#eta|;p_{T} (GeV)"));
//        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num40c_iso"],hc["h_mu_fo40c_iso"], "h_mufr40c_iso", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 40, iso);|#eta|;p_{T} (GeV)"));
//        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num60c_iso"],hc["h_mu_fo60c_iso"], "h_mufr60c_iso", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 60, iso);|#eta|;p_{T} (GeV)"));
    }

    // electrons
    if (m_lepton == "el")
    {   
        // FR(# vertices)
        hc.Add(rt::MakeEfficiencyPlot(hc["h_el_num20c_vs_nvtxs"],hc["h_el_fo20c_vs_nvtxs"], "h_elfr20c_vs_nvtxs", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 20, p_{T}>20);# vtxs"));
        hc.Add(rt::MakeEfficiencyPlot(hc["h_el_num40c_vs_nvtxs"],hc["h_el_fo40c_vs_nvtxs"], "h_elfr40c_vs_nvtxs", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40, p_{T}>20);# vtxs"));
        hc.Add(rt::MakeEfficiencyPlot(hc["h_el_num60c_vs_nvtxs"],hc["h_el_fo60c_vs_nvtxs"], "h_elfr60c_vs_nvtxs", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 60, p_{T}>20);# vtxs"));

        // FR(pt)
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num20c"],hc["h_el_fo20c"], "y", "h_elfr20c_vs_pt", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 20);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num40c"],hc["h_el_fo40c"], "y", "h_elfr40c_vs_pt", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num60c"],hc["h_el_fo60c"], "y", "h_elfr60c_vs_pt", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 60);p_{T}"));
                                                                                                                                                      
        // FR(eta)
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num20c"],hc["h_el_fo20c"], "x", "h_elfr20c_vs_eta", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 20, p_{T}>20);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num40c"],hc["h_el_fo40c"], "x", "h_elfr40c_vs_eta", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40, p_{T}>20);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num60c"],hc["h_el_fo60c"], "x", "h_elfr60c_vs_eta", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 60, p_{T}>20);|#eta|", 20, 100));

        // FR(eta, pT)
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_el_num20c"],hc["h_el_fo20c"], "h_elfr20c", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 20);|#eta|;p_{T} (GeV)"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_el_num40c"],hc["h_el_fo40c"], "h_elfr40c", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40);|#eta|;p_{T} (GeV)"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_el_num60c"],hc["h_el_fo60c"], "h_elfr60c", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 60);|#eta|;p_{T} (GeV)"));

//        // FR(# vertices)
//        hc.Add(rt::MakeEfficiencyPlot(hc["h_el_num20c_noiso_vs_nvtxs"],hc["h_el_fo20c_noiso_vs_nvtxs"], "h_elfr20c_noiso_vs_nvtxs", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 20, p_{T}>10, no iso);# vtxs"));
//        hc.Add(rt::MakeEfficiencyPlot(hc["h_el_num40c_noiso_vs_nvtxs"],hc["h_el_fo40c_noiso_vs_nvtxs"], "h_elfr40c_noiso_vs_nvtxs", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40, p_{T}>10, no iso);# vtxs"));
//        hc.Add(rt::MakeEfficiencyPlot(hc["h_el_num60c_noiso_vs_nvtxs"],hc["h_el_fo60c_noiso_vs_nvtxs"], "h_elfr60c_noiso_vs_nvtxs", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 60, p_{T}>10, no iso);# vtxs"));
//
//        // FR(pt)
//        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num20c_noiso"],hc["h_el_fo20c_noiso"], "y", "h_elfr20c_noiso_vs_pt", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 20, no iso);p_{T}"));
//        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num40c_noiso"],hc["h_el_fo40c_noiso"], "y", "h_elfr40c_noiso_vs_pt", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40, no iso);p_{T}"));
//        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num60c_noiso"],hc["h_el_fo60c_noiso"], "y", "h_elfr60c_noiso_vs_pt", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 60, no iso);p_{T}"));
//                                                                                                                                                      
//        // FR(eta)
//        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num20c_noiso"],hc["h_el_fo20c_noiso"], "x", "h_elfr20c_noiso_vs_eta", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 20, p_{T}>20, no iso);|#eta|", 10, 100));
//        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num40c_noiso"],hc["h_el_fo40c_noiso"], "x", "h_elfr40c_noiso_vs_eta", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40, p_{T}>20, no iso);|#eta|", 10, 100));
//        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num60c_noiso"],hc["h_el_fo60c_noiso"], "x", "h_elfr60c_noiso_vs_eta", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 60, p_{T}>20, no iso);|#eta|", 10, 100));
//
//        // FR(eta, pT)
//        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_el_num20c_noiso"],hc["h_el_fo20c_noiso"], "h_elfr20c_noiso", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 20, no iso);|#eta|;p_{T} (GeV)"));
//        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_el_num40c_noiso"],hc["h_el_fo40c_noiso"], "h_elfr40c_noiso", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40, no iso);|#eta|;p_{T} (GeV)"));
//        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_el_num60c_noiso"],hc["h_el_fo60c_noiso"], "h_elfr60c_noiso", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 60, no iso);|#eta|;p_{T} (GeV)"));
    }

    //if (m_verbose)
    {
        hc.List();
    }

}

// book hists 
void FakeRateBabyLooper::BookHists()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    // binning for MET, MT histograms
    const unsigned int nbins = 20;
    const float min_val = 0.;
    const float max_val = 100.;

    // muons
    // --------------------------------------------------------------------------------------------------------------------------- //    

    // muon FR vs # vertices 
    if (m_lepton == "mu")
    {
        // numerator
        hc.Add(new TH1F("h_mu_num20c_vs_nvtxs", "num #mu (away jet p_{T} > 20, cpfiso03 < 0.1 (#Delta#beta));# vtxs", m_fr_bin_info.num_mu_vtx_bins(), m_fr_bin_info.mu_vtx_bins()), "texte");
        hc.Add(new TH1F("h_mu_num40c_vs_nvtxs", "num #mu (away jet p_{T} > 40, cpfiso03 < 0.1 (#Delta#beta));# vtxs", m_fr_bin_info.num_mu_vtx_bins(), m_fr_bin_info.mu_vtx_bins()), "texte");
        hc.Add(new TH1F("h_mu_num60c_vs_nvtxs", "num #mu (away jet p_{T} > 60, cpfiso03 < 0.1 (#Delta#beta));# vtxs", m_fr_bin_info.num_mu_vtx_bins(), m_fr_bin_info.mu_vtx_bins()), "texte");

        hc.Add(new TH2F("h_mu_num20c", "num #mu (away jet p_{T} > 20, cpfiso03 < 0.1 (#Delta#beta));|#eta|;p_{T} (GeV)", m_fr_bin_info.num_mu_eta_bins(), m_fr_bin_info.mu_eta_bins(), m_fr_bin_info.num_mu_pt_bins(), m_fr_bin_info.mu_pt_bins()), "texte");
        hc.Add(new TH2F("h_mu_num40c", "num #mu (away jet p_{T} > 40, cpfiso03 < 0.1 (#Delta#beta));|#eta|;p_{T} (GeV)", m_fr_bin_info.num_mu_eta_bins(), m_fr_bin_info.mu_eta_bins(), m_fr_bin_info.num_mu_pt_bins(), m_fr_bin_info.mu_pt_bins()), "texte");
        hc.Add(new TH2F("h_mu_num60c", "num #mu (away jet p_{T} > 60, cpfiso03 < 0.1 (#Delta#beta));|#eta|;p_{T} (GeV)", m_fr_bin_info.num_mu_eta_bins(), m_fr_bin_info.mu_eta_bins(), m_fr_bin_info.num_mu_pt_bins(), m_fr_bin_info.mu_pt_bins()), "texte");

        // denominator
        hc.Add(new TH1F("h_mu_fo20c_vs_nvtxs", "fo #mu (away jet p_{T} > 20, cpfiso03 < 0.4 (#Delta#beta));# vtxs", m_fr_bin_info.num_mu_vtx_bins(), m_fr_bin_info.mu_vtx_bins()), "texte");
        hc.Add(new TH1F("h_mu_fo40c_vs_nvtxs", "fo #mu (away jet p_{T} > 40, cpfiso03 < 0.4 (#Delta#beta));# vtxs", m_fr_bin_info.num_mu_vtx_bins(), m_fr_bin_info.mu_vtx_bins()), "texte");
        hc.Add(new TH1F("h_mu_fo60c_vs_nvtxs", "fo #mu (away jet p_{T} > 60, cpfiso03 < 0.4 (#Delta#beta));# vtxs", m_fr_bin_info.num_mu_vtx_bins(), m_fr_bin_info.mu_vtx_bins()), "texte");

        hc.Add(new TH2F("h_mu_fo20c", "fo #mu (away jet p_{T} > 20, cpfiso03 < 0.4 (#Delta#beta));|#eta|;p_{T} (GeV)", m_fr_bin_info.num_mu_eta_bins(), m_fr_bin_info.mu_eta_bins(), m_fr_bin_info.num_mu_pt_bins(), m_fr_bin_info.mu_pt_bins()), "texte");
        hc.Add(new TH2F("h_mu_fo40c", "fo #mu (away jet p_{T} > 40, cpfiso03 < 0.4 (#Delta#beta));|#eta|;p_{T} (GeV)", m_fr_bin_info.num_mu_eta_bins(), m_fr_bin_info.mu_eta_bins(), m_fr_bin_info.num_mu_pt_bins(), m_fr_bin_info.mu_pt_bins()), "texte");
        hc.Add(new TH2F("h_mu_fo60c", "fo #mu (away jet p_{T} > 60, cpfiso03 < 0.4 (#Delta#beta));|#eta|;p_{T} (GeV)", m_fr_bin_info.num_mu_eta_bins(), m_fr_bin_info.mu_eta_bins(), m_fr_bin_info.num_mu_pt_bins(), m_fr_bin_info.mu_pt_bins()), "texte");

        // numerator (iso)
        hc.Add(new TH1F("h_mu_num20c_iso_vs_nvtxs", "num #mu (away jet p_{T} > 20, cpfiso03 < 0.1 (#Delta#beta), iso);# vtxs", m_fr_bin_info.num_mu_vtx_bins(), m_fr_bin_info.mu_vtx_bins()), "texte");
        hc.Add(new TH1F("h_mu_num40c_iso_vs_nvtxs", "num #mu (away jet p_{T} > 40, cpfiso03 < 0.1 (#Delta#beta), iso);# vtxs", m_fr_bin_info.num_mu_vtx_bins(), m_fr_bin_info.mu_vtx_bins()), "texte");
        hc.Add(new TH1F("h_mu_num60c_iso_vs_nvtxs", "num #mu (away jet p_{T} > 60, cpfiso03 < 0.1 (#Delta#beta), iso);# vtxs", m_fr_bin_info.num_mu_vtx_bins(), m_fr_bin_info.mu_vtx_bins()), "texte");

        hc.Add(new TH2F("h_mu_num20c_iso", "num #mu (away jet p_{T} > 20, cpfiso03 < 0.1 (#Delta#beta), iso);|#eta|;p_{T} (GeV)", m_fr_bin_info.num_mu_eta_bins(), m_fr_bin_info.mu_eta_bins(), m_fr_bin_info.num_mu_pt_bins(), m_fr_bin_info.mu_pt_bins()), "texte");
        hc.Add(new TH2F("h_mu_num40c_iso", "num #mu (away jet p_{T} > 40, cpfiso03 < 0.1 (#Delta#beta), iso);|#eta|;p_{T} (GeV)", m_fr_bin_info.num_mu_eta_bins(), m_fr_bin_info.mu_eta_bins(), m_fr_bin_info.num_mu_pt_bins(), m_fr_bin_info.mu_pt_bins()), "texte");
        hc.Add(new TH2F("h_mu_num60c_iso", "num #mu (away jet p_{T} > 60, cpfiso03 < 0.1 (#Delta#beta), iso);|#eta|;p_{T} (GeV)", m_fr_bin_info.num_mu_eta_bins(), m_fr_bin_info.mu_eta_bins(), m_fr_bin_info.num_mu_pt_bins(), m_fr_bin_info.mu_pt_bins()), "texte");

        // denominator (iso)
        hc.Add(new TH1F("h_mu_fo20c_iso_vs_nvtxs", "fo #mu (away jet p_{T} > 20, cpfiso03 < 0.4 (#Delta#beta), iso);# vtxs", m_fr_bin_info.num_mu_vtx_bins(), m_fr_bin_info.mu_vtx_bins()), "texte");
        hc.Add(new TH1F("h_mu_fo40c_iso_vs_nvtxs", "fo #mu (away jet p_{T} > 40, cpfiso03 < 0.4 (#Delta#beta), iso);# vtxs", m_fr_bin_info.num_mu_vtx_bins(), m_fr_bin_info.mu_vtx_bins()), "texte");
        hc.Add(new TH1F("h_mu_fo60c_iso_vs_nvtxs", "fo #mu (away jet p_{T} > 60, cpfiso03 < 0.4 (#Delta#beta), iso);# vtxs", m_fr_bin_info.num_mu_vtx_bins(), m_fr_bin_info.mu_vtx_bins()), "texte");

        hc.Add(new TH2F("h_mu_fo20c_iso", "fo #mu (away jet p_{T} > 20, cpfiso03 < 0.4 (#Delta#beta), iso);|#eta|;p_{T} (GeV)", m_fr_bin_info.num_mu_eta_bins(), m_fr_bin_info.mu_eta_bins(), m_fr_bin_info.num_mu_pt_bins(), m_fr_bin_info.mu_pt_bins()), "texte");
        hc.Add(new TH2F("h_mu_fo40c_iso", "fo #mu (away jet p_{T} > 40, cpfiso03 < 0.4 (#Delta#beta), iso);|#eta|;p_{T} (GeV)", m_fr_bin_info.num_mu_eta_bins(), m_fr_bin_info.mu_eta_bins(), m_fr_bin_info.num_mu_pt_bins(), m_fr_bin_info.mu_pt_bins()), "texte");
        hc.Add(new TH2F("h_mu_fo60c_iso", "fo #mu (away jet p_{T} > 60, cpfiso03 < 0.4 (#Delta#beta), iso);|#eta|;p_{T} (GeV)", m_fr_bin_info.num_mu_eta_bins(), m_fr_bin_info.mu_eta_bins(), m_fr_bin_info.num_mu_pt_bins(), m_fr_bin_info.mu_pt_bins()), "texte");


	// GZ
        hc.Add(new TH1F("h_mu_fo_iso", "fo muon; cpfiso03 (#Delta#beta)",50,0,5), "texte");
        hc.Add(new TH1F("h_mu_fo_isoGeV", "fo muon; cpfiso03 (#Delta#beta) (GeV)",100,0,10), "texte");
        hc.Add(new TH1F("h_mu_fo_chiso", "fo muon; chiso03",50,0,5), "texte");
        hc.Add(new TH1F("h_mu_fo_caloiso", "fo muon; caloiso03(#Delta#beta)",50,0,5), "texte");
        hc.Add(new TH1F("h_mu_fo_chisoGeV", "fo muon; chiso03 (GeV)",100,0,10), "texte");
        hc.Add(new TH1F("h_mu_fo_caloisoGeV", "fo muon; caloiso03(#Delta#beta) (GeV)",50,0,5), "texte");
        hc.Add(new TH1F("h_mu_fo_d0", "fo muon; d_{0}",50,0,0.25), "texte");
        hc.Add(new TH1F("h_mu_fo_jetPt", "fo muon; p_{T}^{jet}",50,0,250), "texte");
        hc.Add(new TH1F("h_mu_fo_lepPt", "fo muon; p_{T}^{lep}",50,0,150), "texte");
        hc.Add(new TH2F("h_mu_fo_iso_vs_chiso", "fo muon; chiso03;cpfiso03 (#Delta#beta);",50,0,5, 50,0,5), "texte");
        hc.Add(new TH2F("h_mu_fo_iso_vs_caloiso", "fo muon; caloiso03(#Delta#beta);cpfiso03 (#Delta#beta);",50,0,5, 50,0,5), "texte");
        hc.Add(new TH2F("h_mu_fo_chiso_vs_caloiso", "fo muon; caloiso03(#Delta#beta);chiso03;",50,0,5, 50,0,5), "texte");
        hc.Add(new TH2F("h_mu_fo_chisoGeV_vs_caloisoGeV", "fo muon; caloiso03(#Delta#beta);chiso03;",100,0,10, 100,0,10), "texte");
        hc.Add(new TH2F("h_mu_fo_iso_vs_jetPt", "fo muon; p_{T}^{jet} (GeV);cpfiso03 (#Delta#beta);",50,0,250, 50,0,5), "texte");
        hc.Add(new TH2F("h_mu_fo_isoGeV_vs_jetPt", "fo muon; p_{T}^{jet} (GeV);cpfiso03 (#Delta#beta) (GeV);",50,0,250, 100,0,10), "texte");
        hc.Add(new TH2F("h_mu_fo_chiso_vs_jetPt", "fo muon; p_{T}^{jet} (GeV);chiso03;",50,0,250, 50,0,5), "texte");
        hc.Add(new TH2F("h_mu_fo_caloiso_vs_jetPt", "fo muon; p_{T}^{jet} (GeV);caloiso03(#Delta#beta);",50,0,250, 50,0,5), "texte");
        hc.Add(new TH2F("h_mu_fo_chisoGeV_vs_jetPt", "fo muon; p_{T}^{jet} (GeV);chiso03 (GeV);",50,0,250, 100,0,10), "texte");
        hc.Add(new TH2F("h_mu_fo_caloisoGeV_vs_jetPt", "fo muon; p_{T}^{jet} (GeV);caloiso03(#Delta#beta) (GeV);",50,0,250, 100,0,10), "texte");
        hc.Add(new TH2F("h_mu_fo_chiso_vs_jetPt_caloiso01", "fo muon; p_{T}^{jet} (GeV);chiso03;",50,0,250, 50,0,5), "texte");
        hc.Add(new TH2F("h_mu_fo_caloiso_vs_jetPt_chiso01", "fo muon; p_{T}^{jet} (GeV);caloiso03(#Delta#beta);",50,0,250, 50,0,5), "texte");
        hc.Add(new TH2F("h_mu_fo_chisoGeV_vs_jetPt_caloiso2", "fo muon; p_{T}^{jet} (GeV);chiso03 (GeV);",50,0,250, 100,0,10), "texte");
        hc.Add(new TH2F("h_mu_fo_caloisoGeV_vs_jetPt_chiso2", "fo muon; p_{T}^{jet} (GeV);caloiso03(#Delta#beta) (GeV);",50,0,250, 100,0,10), "texte");
        hc.Add(new TH2F("h_mu_fo_iso_vs_lepPt", "fo muon; p_{T}^{lep} (GeV);cpfiso03 (#Delta#beta);",50,0,150, 50,0,5), "texte");
        hc.Add(new TH2F("h_mu_fo_isoGeV_vs_lepPt", "fo muon; p_{T}^{lep} (GeV);cpfiso03 (#Delta#beta) (GeV);",50,0,150, 100,0,10), "texte");
        hc.Add(new TH2F("h_mu_fo_chiso_vs_lepPt", "fo muon; p_{T}^{lep} (GeV);chiso03;",50,0,150, 50,0,5), "texte");
        hc.Add(new TH2F("h_mu_fo_caloiso_vs_lepPt", "fo muon; p_{T}^{lep} (GeV);caloiso03(#Delta#beta);",50,0,150, 50,0,5), "texte");
        hc.Add(new TH2F("h_mu_fo_chisoGeV_vs_lepPt", "fo muon; p_{T}^{lep} (GeV);chiso03 (GeV);",50,0,150, 100,0,10), "texte");
        hc.Add(new TH2F("h_mu_fo_caloisoGeV_vs_lepPt", "fo muon; p_{T}^{lep} (GeV);caloiso03(#Delta#beta) (GeV);",50,0,150, 100,0,10), "texte");
        hc.Add(new TH2F("h_mu_fo_d0_vs_jetPt", "fo muon;p_{T}^{jet} (GeV);d_{0};", 50,0,250,50,0,0.25), "texte");
        hc.Add(new TH2F("h_mu_fo_d0_vs_jetPt_iso04", "fo muon;p_{T}^{jet} (GeV);d_{0};", 50,0,250,50,0,0.25), "texte");
        hc.Add(new TH2F("h_mu_fo_d0_vs_iso", "fo muon;p_{T}^{jet} (GeV);d_{0};", 50,0,5,50,0,0.25), "texte");

	hc.Add(new TH2F("h_mu_fo_ecal_vs_jetPt", "fo muon; p_{T}^{jet} (GeV);ecal (GeV);",50,0,250, 50,0,50), "texte");
	hc.Add(new TH2F("h_mu_fo_hcal_vs_jetPt", "fo muon; p_{T}^{jet} (GeV);hcal (GeV);",50,0,250, 50,0,50), "texte");
	hc.Add(new TH2F("h_mu_fo_ecal_vs_iso", "fo muon; cpfiso03 (#Delta#beta);ecal (GeV);",50,0,5, 50,0,50), "texte");
	hc.Add(new TH2F("h_mu_fo_hcal_vs_iso", "fo muon; cpfiso03 (#Delta#beta);hcal (GeV);",50,0,5, 50,0,50), "texte");
	hc.Add(new TH1F("h_mu_fo_ecal","ecal (GeV);", 50,0,50), "texte");
	hc.Add(new TH1F("h_mu_fo_hcal","ecal (GeV);", 50,0,50), "texte");
	
	hc.Add(new TH1F("h_mu_fo_jetPt_num"             , "fo muon; p_{T}^{jet}",50,0,250), "texte");
	hc.Add(new TH1F("h_mu_fo_jetPt_num_iso01"	, "fo muon; p_{T}^{jet}",100,0,250), "texte");
	hc.Add(new TH1F("h_mu_fo_jetPt_num_iso04"	, "fo muon; p_{T}^{jet}",100,0,250), "texte");
	hc.Add(new TH1F("h_mu_fo_qPt_num_iso01"	        , "fo muon; p_{T}^{mother}",100,0,250), "texte");
	hc.Add(new TH1F("h_mu_fo_qPt_num_iso04"	        , "fo muon; p_{T}^{mother}",100,0,250), "texte");
	hc.Add(new TH1F("h_mu_fo_jetPt_num_iso02"	, "fo muon; p_{T}^{jet}",50,0,250), "texte");
	hc.Add(new TH1F("h_mu_fo_jetPt_num_iso03"	, "fo muon; p_{T}^{jet}",50,0,250), "texte");
	hc.Add(new TH1F("h_mu_fo_jetPt_num_iso04_ch01"	, "fo muon; p_{T}^{jet}",50,0,250), "texte");
	hc.Add(new TH1F("h_mu_fo_jetPt_num_iso04_nu01"	, "fo muon; p_{T}^{jet}",50,0,250), "texte");
	hc.Add(new TH1F("h_mu_fo_jetPt_num_iso04_chnu01", "fo muon; p_{T}^{jet}",50,0,250), "texte");
	hc.Add(new TH1F("h_mu_fo_jetPt_nonum"           , "fo muon; p_{T}^{jet}",50,0,250), "texte");
	hc.Add(new TH1F("h_mu_fo_jetPt_nonum_iso01"	, "fo muon; p_{T}^{jet}",100,0,250), "texte");
	hc.Add(new TH1F("h_mu_fo_jetPt_nonum_iso04"	, "fo muon; p_{T}^{jet}",100,0,250), "texte");
	hc.Add(new TH1F("h_mu_fo_qPt_nonum_iso01"	, "fo muon; p_{T}^{mother}",100,0,250), "texte");
	hc.Add(new TH1F("h_mu_fo_qPt_nonum_iso04"	, "fo muon; p_{T}^{mother}",100,0,250), "texte");
	hc.Add(new TH1F("h_mu_fo_jetPt_iso01"		, "fo muon; p_{T}^{jet}",50,0,250), "texte");
	hc.Add(new TH1F("h_mu_fo_jetPt_iso04"		, "fo muon; p_{T}^{jet}",50,0,250), "texte");
	hc.Add(new TH1F("h_mu_fo_jetPt_nonum_iso04_d0"	, "fo muon; p_{T}^{jet}",50,0,250), "texte");
	hc.Add(new TH1F("h_mu_fo_jetPt_nonum_iso04_nod0", "fo muon; p_{T}^{jet}",50,0,250), "texte");
	hc.Add(new TH1F("h_mu_fo_jetPt_nonum_iso04_MIP"	, "fo muon; p_{T}^{jet}",50,0,250), "texte");
	hc.Add(new TH1F("h_mu_fo_jetPt_nonum_iso04_noMIP", "fo muon; p_{T}^{jet}",50,0,250), "texte");

	hc.Add(new TH1F("h_mu_fojet_jetPt_num_iso01"	, "fo muonjet; p_{T}^{jet}",100,0,250), "texte");
	hc.Add(new TH1F("h_mu_fojet_jetPt_num_iso04"	, "fo muonjet; p_{T}^{jet}",100,0,250), "texte");
	hc.Add(new TH1F("h_mu_fojet_jetPt_nonum_iso01"	, "fo muonjet; p_{T}^{jet}",100,0,250), "texte");
	hc.Add(new TH1F("h_mu_fojet_jetPt_nonum_iso04"	, "fo muonjet; p_{T}^{jet}",100,0,250), "texte");
	hc.Add(new TH1F("h_mu_fojet_qPt_num_iso01"      , "fo muonjet; p_{T}^{mother}",100,0,250), "texte");
	hc.Add(new TH1F("h_mu_fojet_qPt_num_iso04"      , "fo muonjet; p_{T}^{mother}",100,0,250), "texte");
	hc.Add(new TH1F("h_mu_fojet_qPt_nonum_iso01"	, "fo muonjet; p_{T}^{mother}",100,0,250), "texte");
	hc.Add(new TH1F("h_mu_fojet_qPt_nonum_iso04"	, "fo muonjet; p_{T}^{mother}",100,0,250), "texte");

	hc.Add(new TH1F("h_mu_fojet20_qPt_num_iso01"      , "fo muonjet, 20 GeV; p_{T}^{mother}",100,0,250), "texte");
	hc.Add(new TH1F("h_mu_fojet20_qPt_num_iso04"      , "fo muonjet, 20 GeV; p_{T}^{mother}",100,0,250), "texte");
	hc.Add(new TH1F("h_mu_fojet40_qPt_num_iso01"      , "fo muonjet, 40 GeV; p_{T}^{mother}",100,0,250), "texte");
	hc.Add(new TH1F("h_mu_fojet40_qPt_num_iso04"      , "fo muonjet, 40 GeV; p_{T}^{mother}",100,0,250), "texte");
	hc.Add(new TH1F("h_mu_fojet60_qPt_num_iso01"      , "fo muonjet, 60 GeV; p_{T}^{mother}",100,0,250), "texte");
	hc.Add(new TH1F("h_mu_fojet60_qPt_num_iso04"      , "fo muonjet, 60 GeV; p_{T}^{mother}",100,0,250), "texte");

	hc.Add(new TH1F("h_mu_fo_ecal_denominator"	, "fo muon; ecal (GeV)",50,0,50), "texte");
	hc.Add(new TH1F("h_mu_fo_hcal_denominator"	, "fo muon; hcal (GeV)",50,0,50), "texte");
	hc.Add(new TH1F("h_mu_fo_ecal_numerator"	, "num muon; ecal (GeV)",50,0,50), "texte");
	hc.Add(new TH1F("h_mu_fo_hcal_numerator"	, "num muon; hcal (GeV)",50,0,50), "texte");






	// End GZ

        // MET distribution denominator
        hc.Add(new TH1F("h_mu_fo20c_met", "h_mu_fo20c_met", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_fo40c_met", "h_mu_fo40c_met", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_fo60c_met", "h_mu_fo60c_met", nbins, min_val, max_val));

        // MT distribution denominator, MET > 30 GeV
        hc.Add(new TH1F("h_mu_fo20c_mt_met30gt", "h_mu_fo20c_mt_met30gt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_fo40c_mt_met30gt", "h_mu_fo40c_mt_met30gt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_fo60c_mt_met30gt", "h_mu_fo60c_mt_met30gt", nbins, min_val, max_val));

        // MT distribution denominator, MET < 20 GeV
        hc.Add(new TH1F("h_mu_fo20c_mt_met20lt", "h_mu_fo20c_mt_met20lt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_fo40c_mt_met20lt", "h_mu_fo40c_mt_met20lt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_fo60c_mt_met20lt", "h_mu_fo60c_mt_met20lt", nbins, min_val, max_val));

        // muon FO pt distribution
        hc.Add(new TH1F("h_mu_fo20c_pt", "h_mu_fo20c_pt", m_fr_bin_info.num_mu_pt_bins(), m_fr_bin_info.mu_pt_bins()));
        hc.Add(new TH1F("h_mu_fo40c_pt", "h_mu_fo40c_pt", m_fr_bin_info.num_mu_pt_bins(), m_fr_bin_info.mu_pt_bins()));
        hc.Add(new TH1F("h_mu_fo60c_pt", "h_mu_fo60c_pt", m_fr_bin_info.num_mu_pt_bins(), m_fr_bin_info.mu_pt_bins()));

        // muon FO eta distribution
        hc.Add(new TH1F("h_mu_fo20c_eta", "h_mu_fo20c_eta", 10, -2.5, 2.5));
        hc.Add(new TH1F("h_mu_fo40c_eta", "h_mu_fo40c_eta", 10, -2.5, 2.5));
        hc.Add(new TH1F("h_mu_fo60c_eta", "h_mu_fo60c_eta", 10, -2.5, 2.5));

        // MET distribution numerator
        hc.Add(new TH1F("h_mu_num20c_met", "h_mu_num20c_met", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_num40c_met", "h_mu_num40c_met", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_num60c_met", "h_mu_num60c_met", nbins, min_val, max_val));

        // MT distribution numerator
        hc.Add(new TH1F("h_mu_num20c_mt_met30gt", "h_mu_num20c_mt_met30gt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_num40c_mt_met30gt", "h_mu_num40c_mt_met30gt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_num60c_mt_met30gt", "h_mu_num60c_mt_met30gt", nbins, min_val, max_val));

        // MT distribution denominator, MET < 20 GeV
        hc.Add(new TH1F("h_mu_num20c_mt_met20lt", "h_mu_num20c_mt_met20lt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_num40c_mt_met20lt", "h_mu_num40c_mt_met20lt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_num60c_mt_met20lt", "h_mu_num60c_mt_met20lt", nbins, min_val, max_val));

        // muon NUM pt distribution
        hc.Add(new TH1F("h_mu_num20c_pt", "h_mu_num20c_pt", m_fr_bin_info.num_mu_pt_bins(), m_fr_bin_info.mu_pt_bins()));
        hc.Add(new TH1F("h_mu_num40c_pt", "h_mu_num40c_pt", m_fr_bin_info.num_mu_pt_bins(), m_fr_bin_info.mu_pt_bins()));
        hc.Add(new TH1F("h_mu_num60c_pt", "h_mu_num60c_pt", m_fr_bin_info.num_mu_pt_bins(), m_fr_bin_info.mu_pt_bins()));

        // muon NUM eta distribution
        hc.Add(new TH1F("h_mu_num20c_eta", "h_mu_num20c_eta", 10, -2.5, 2.5));
        hc.Add(new TH1F("h_mu_num40c_eta", "h_mu_num40c_eta", 10, -2.5, 2.5));
        hc.Add(new TH1F("h_mu_num60c_eta", "h_mu_num60c_eta", 10, -2.5, 2.5));

        // (iso mu triggers) MET distribution denominator
        hc.Add(new TH1F("h_mu_iso_fo20c_met", "h_mu_iso_fo20c_met", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_iso_fo40c_met", "h_mu_iso_fo40c_met", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_iso_fo60c_met", "h_mu_iso_fo60c_met", nbins, min_val, max_val));

        // (iso mu triggers) MT distribution denominator, MET > 30 GeV
        hc.Add(new TH1F("h_mu_iso_fo20c_mt_met30gt", "h_mu_iso_fo20c_mt_met30gt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_iso_fo40c_mt_met30gt", "h_mu_iso_fo40c_mt_met30gt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_iso_fo60c_mt_met30gt", "h_mu_iso_fo60c_mt_met30gt", nbins, min_val, max_val));

        // (iso mu triggers) MT distribution denominator, MET < 20 GeV
        hc.Add(new TH1F("h_mu_iso_fo20c_mt_met20lt", "h_mu_iso_fo20c_mt_met20lt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_iso_fo40c_mt_met20lt", "h_mu_iso_fo40c_mt_met20lt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_iso_fo60c_mt_met20lt", "h_mu_iso_fo60c_mt_met20lt", nbins, min_val, max_val));

        // (iso mu triggers) muon FO pt distribution
        hc.Add(new TH1F("h_mu_iso_fo20c_pt", "h_mu_iso_fo20c_pt", 12, 0., 60.));
        hc.Add(new TH1F("h_mu_iso_fo40c_pt", "h_mu_iso_fo40c_pt", 12, 0., 60.));
        hc.Add(new TH1F("h_mu_iso_fo60c_pt", "h_mu_iso_fo60c_pt", 12, 0., 60.));

        // (iso mu triggers) muon FO eta distribution
        hc.Add(new TH1F("h_mu_iso_fo20c_eta", "h_mu_iso_fo20c_eta", 10, -2.5, 2.5));
        hc.Add(new TH1F("h_mu_iso_fo40c_eta", "h_mu_iso_fo40c_eta", 10, -2.5, 2.5));
        hc.Add(new TH1F("h_mu_iso_fo60c_eta", "h_mu_iso_fo60c_eta", 10, -2.5, 2.5));

        // (iso mu triggers) MET distribution numerator
        hc.Add(new TH1F("h_mu_iso_num20c_met", "h_mu_iso_num20c_met", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_iso_num40c_met", "h_mu_iso_num40c_met", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_iso_num60c_met", "h_mu_iso_num60c_met", nbins, min_val, max_val));

        // (iso mu triggers) MT distribution numerator
        hc.Add(new TH1F("h_mu_iso_num20c_mt_met30gt", "h_mu_iso_num20c_mt_met30gt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_iso_num40c_mt_met30gt", "h_mu_iso_num40c_mt_met30gt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_iso_num60c_mt_met30gt", "h_mu_iso_num60c_mt_met30gt", nbins, min_val, max_val));

        // (iso mu triggers) MT distribution denominator, MET < 20 GeV
        hc.Add(new TH1F("h_mu_iso_num20c_mt_met20lt", "h_mu_iso_num20c_mt_met20lt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_iso_num40c_mt_met20lt", "h_mu_iso_num40c_mt_met20lt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_mu_iso_num60c_mt_met20lt", "h_mu_iso_num60c_mt_met20lt", nbins, min_val, max_val));

        // (iso mu triggers) muon NUM pt distribution
        hc.Add(new TH1F("h_mu_iso_num20c_pt", "h_mu_iso_num20c_pt", 12, 0., 60.));
        hc.Add(new TH1F("h_mu_iso_num40c_pt", "h_mu_iso_num40c_pt", 12, 0., 60.));
        hc.Add(new TH1F("h_mu_iso_num60c_pt", "h_mu_iso_num60c_pt", 12, 0., 60.));

        // (iso mu triggers) muon NUM eta distribution
        hc.Add(new TH1F("h_mu_iso_num20c_eta", "h_mu_iso_num20c_eta", 10, -2.5, 2.5));
        hc.Add(new TH1F("h_mu_iso_num40c_eta", "h_mu_iso_num40c_eta", 10, -2.5, 2.5));
        hc.Add(new TH1F("h_mu_iso_num60c_eta", "h_mu_iso_num60c_eta", 10, -2.5, 2.5));



    }

    // electrons
    // --------------------------------------------------------------------------------------------------------------------------- //
    
    // electron FR vs # vertices 
    if (m_lepton == "el")
    {
        // numerator
        hc.Add(new TH1F("h_el_num20c_vs_nvtxs", "num electron (away jet p_{T} > 20, cpfiso03 < 0.09 (#rho * A_{eff}));# vtxs", m_fr_bin_info.num_el_vtx_bins(), m_fr_bin_info.el_vtx_bins()), "texte");
        hc.Add(new TH1F("h_el_num40c_vs_nvtxs", "num electron (away jet p_{T} > 40, cpfiso03 < 0.09 (#rho * A_{eff}));# vtxs", m_fr_bin_info.num_el_vtx_bins(), m_fr_bin_info.el_vtx_bins()), "texte");
        hc.Add(new TH1F("h_el_num60c_vs_nvtxs", "num electron (away jet p_{T} > 60, cpfiso03 < 0.09 (#rho * A_{eff}));# vtxs", m_fr_bin_info.num_el_vtx_bins(), m_fr_bin_info.el_vtx_bins()), "texte");

        hc.Add(new TH2F("h_el_num20c", "num electron (away jet p_{T} > 20, cpfiso03 < 0.09 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", m_fr_bin_info.num_el_eta_bins(), m_fr_bin_info.el_eta_bins(), m_fr_bin_info.num_el_pt_bins(), m_fr_bin_info.el_pt_bins()), "texte");
        hc.Add(new TH2F("h_el_num40c", "num electron (away jet p_{T} > 40, cpfiso03 < 0.09 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", m_fr_bin_info.num_el_eta_bins(), m_fr_bin_info.el_eta_bins(), m_fr_bin_info.num_el_pt_bins(), m_fr_bin_info.el_pt_bins()), "texte");
        hc.Add(new TH2F("h_el_num60c", "num electron (away jet p_{T} > 60, cpfiso03 < 0.09 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", m_fr_bin_info.num_el_eta_bins(), m_fr_bin_info.el_eta_bins(), m_fr_bin_info.num_el_pt_bins(), m_fr_bin_info.el_pt_bins()), "texte");

        // denominator
        hc.Add(new TH1F("h_el_fo20c_vs_nvtxs", "fo electron (away jet p_{T} > 20, cpfiso03 < 0.6 (#rho * A_{eff}));# vtxs", m_fr_bin_info.num_el_vtx_bins(), m_fr_bin_info.el_vtx_bins()), "texte");
        hc.Add(new TH1F("h_el_fo40c_vs_nvtxs", "fo electron (away jet p_{T} > 40, cpfiso03 < 0.6 (#rho * A_{eff}));# vtxs", m_fr_bin_info.num_el_vtx_bins(), m_fr_bin_info.el_vtx_bins()), "texte");
        hc.Add(new TH1F("h_el_fo60c_vs_nvtxs", "fo electron (away jet p_{T} > 60, cpfiso03 < 0.6 (#rho * A_{eff}));# vtxs", m_fr_bin_info.num_el_vtx_bins(), m_fr_bin_info.el_vtx_bins()), "texte");

        hc.Add(new TH2F("h_el_fo20c", "fo electron (away jet p_{T} > 20, cpfiso03 < 0.6 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", m_fr_bin_info.num_el_eta_bins(), m_fr_bin_info.el_eta_bins(), m_fr_bin_info.num_el_pt_bins(), m_fr_bin_info.el_pt_bins()), "texte");
        hc.Add(new TH2F("h_el_fo40c", "fo electron (away jet p_{T} > 40, cpfiso03 < 0.6 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", m_fr_bin_info.num_el_eta_bins(), m_fr_bin_info.el_eta_bins(), m_fr_bin_info.num_el_pt_bins(), m_fr_bin_info.el_pt_bins()), "texte");
        hc.Add(new TH2F("h_el_fo60c", "fo electron (away jet p_{T} > 60, cpfiso03 < 0.6 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", m_fr_bin_info.num_el_eta_bins(), m_fr_bin_info.el_eta_bins(), m_fr_bin_info.num_el_pt_bins(), m_fr_bin_info.el_pt_bins()), "texte");


        hc.Add(new TH1F("h_el_fo_iso", "fo electron; cpfiso03 (#rho * A_{eff})",50,0,5), "texte");
        hc.Add(new TH1F("h_el_fo_chiso", "fo electron; chiso03",50,0,5), "texte");
        hc.Add(new TH1F("h_el_fo_caloiso", "fo electron; caloiso03(#rho * A_{eff})",50,0,5), "texte");
        hc.Add(new TH1F("h_el_fo_chisoGeV", "fo electron; chiso03 (GeV)",100,0,10), "texte");
        hc.Add(new TH1F("h_el_fo_caloisoGeV", "fo electron; caloiso03(#rho * A_{eff}) (GeV)",100,0,10), "texte");
        hc.Add(new TH1F("h_el_fo_d0", "fo electron; d_{0}",50,0,1), "texte");
        hc.Add(new TH1F("h_el_fo_jetPt", "fo electron; p_{T}^{jet}",50,0,250), "texte");
	hc.Add(new TH1F("h_el_fo_jetPt_q5_15","fo electron; p_{T}^{jet}",50,0,250), "texte");
	hc.Add(new TH1F("h_el_fo_jetPt_q15_30","fo electron; p_{T}^{jet}",50,0,250), "texte");
	hc.Add(new TH1F("h_el_fo_jetPt_q30_50","fo electron; p_{T}^{jet}",50,0,250), "texte");
	hc.Add(new TH1F("h_el_fo_jetPt_q50_80","fo electron; p_{T}^{jet}",50,0,250), "texte");
	hc.Add(new TH1F("h_el_fo_jetPt_q80_120","fo electron; p_{T}^{jet}",50,0,250), "texte");
	hc.Add(new TH1F("h_el_fo_jetPt_q120_170","fo electron; p_{T}^{jet}",50,0,250), "texte");
	hc.Add(new TH1F("h_el_fo_jetPt_q170_300","fo electron; p_{T}^{jet}",50,0,250), "texte");

        hc.Add(new TH2F("h_el_fo_iso_vs_chiso", "fo electron; chiso03;cpfiso03 (#rho * A_{eff});",50,0,5, 50,0,5), "texte");
        hc.Add(new TH2F("h_el_fo_iso_vs_caloiso", "fo electron; caloiso03(#rho * A_{eff});cpfiso03 (#rho * A_{eff});",50,0,5, 50,0,5), "texte");
        hc.Add(new TH2F("h_el_fo_chiso_vs_caloiso", "fo electron; caloiso03(#rho * A_{eff});chiso03;",50,0,5, 50,0,5), "texte");
        hc.Add(new TH2F("h_el_fo_chisoGeV_vs_caloisoGeV", "fo electron; caloiso03(#rho * A_{eff}) (GeV);chiso03 (GeV);",100,0,10, 100,0,10), "texte");
        hc.Add(new TH2F("h_el_fo_iso_vs_jetPt", "fo electron; p_{T}^{jet} (GeV);cpfiso03 (#rho * A_{eff});",50,0,250, 50,0,5), "texte");
        hc.Add(new TH2F("h_el_fo_chiso_vs_jetPt", "fo electron; p_{T}^{jet} (GeV);chiso03;",50,0,250, 50,0,5), "texte");
        hc.Add(new TH2F("h_el_fo_caloiso_vs_jetPt", "fo electron; p_{T}^{jet} (GeV);caloiso03(#rho * A_{eff});",50,0,250, 50,0,5), "texte");
        hc.Add(new TH2F("h_el_fo_chisoGeV_vs_jetPt", "fo electron; p_{T}^{jet} (GeV);chiso03 (GeV);",50,0,250, 100,0,10), "texte");
        hc.Add(new TH2F("h_el_fo_caloisoGeV_vs_jetPt", "fo electron; p_{T}^{jet} (GeV);caloiso03(#rho * A_{eff}) (GeV);",50,0,250, 100,0,10), "texte");
        hc.Add(new TH2F("h_el_fo_iso_vs_lepPt", "fo electron; p_{T}^{lep} (GeV);cpfiso03 (#rho * A_{eff});",50,0,250, 50,0,5), "texte");
        hc.Add(new TH2F("h_el_fo_chiso_vs_lepPt", "fo electron; p_{T}^{lep} (GeV);chiso03;",50,0,250, 50,0,5), "texte");
        hc.Add(new TH2F("h_el_fo_caloiso_vs_lepPt", "fo electron; p_{T}^{lep} (GeV);caloiso03(#rho * A_{eff});",50,0,250, 50,0,5), "texte");
        hc.Add(new TH2F("h_el_fo_chisoGeV_vs_lepPt", "fo electron; p_{T}^{lep} (GeV);chiso03 (GeV);",50,0,250, 100,0,10), "texte");
        hc.Add(new TH2F("h_el_fo_caloisoGeV_vs_lepPt", "fo electron; p_{T}^{lep} (GeV);caloiso03(#rho * A_{eff}) (GeV);",50,0,250, 100,0,10), "texte");
        hc.Add(new TH2F("h_el_fo_d0_vs_jetPt", "fo electron;p_{T}^{jet} (GeV);d_{0};", 50,0,250,50,0,1), "texte");

        // numerator (no iso)
        hc.Add(new TH1F("h_el_num20c_noiso_vs_nvtxs", "num electron (away jet p_{T} > 20, no iso, cpfiso03 < 0.09 (#rho * A_{eff}));# vtxs", m_fr_bin_info.num_el_vtx_bins(), m_fr_bin_info.el_vtx_bins()), "texte");
        hc.Add(new TH1F("h_el_num40c_noiso_vs_nvtxs", "num electron (away jet p_{T} > 40, no iso, cpfiso03 < 0.09 (#rho * A_{eff}));# vtxs", m_fr_bin_info.num_el_vtx_bins(), m_fr_bin_info.el_vtx_bins()), "texte");
        hc.Add(new TH1F("h_el_num60c_noiso_vs_nvtxs", "num electron (away jet p_{T} > 60, no iso, cpfiso03 < 0.09 (#rho * A_{eff}));# vtxs", m_fr_bin_info.num_el_vtx_bins(), m_fr_bin_info.el_vtx_bins()), "texte");

        hc.Add(new TH2F("h_el_num20c_noiso", "num electron (away jet p_{T} > 20, no iso, cpfiso03 < 0.09 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", m_fr_bin_info.num_el_eta_bins(), m_fr_bin_info.el_eta_bins(), m_fr_bin_info.num_el_pt_bins(), m_fr_bin_info.el_pt_bins()), "texte");
        hc.Add(new TH2F("h_el_num40c_noiso", "num electron (away jet p_{T} > 40, no iso, cpfiso03 < 0.09 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", m_fr_bin_info.num_el_eta_bins(), m_fr_bin_info.el_eta_bins(), m_fr_bin_info.num_el_pt_bins(), m_fr_bin_info.el_pt_bins()), "texte");
        hc.Add(new TH2F("h_el_num60c_noiso", "num electron (away jet p_{T} > 60, no iso, cpfiso03 < 0.09 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", m_fr_bin_info.num_el_eta_bins(), m_fr_bin_info.el_eta_bins(), m_fr_bin_info.num_el_pt_bins(), m_fr_bin_info.el_pt_bins()), "texte");

        // denominator (no iso)
        hc.Add(new TH1F("h_el_fo20c_noiso_vs_nvtxs", "fo electron (away jet p_{T} > 20, no iso, cpfiso03 < 0.6 (#rho * A_{eff}));# vtxs", m_fr_bin_info.num_el_vtx_bins(), m_fr_bin_info.el_vtx_bins()), "texte");
        hc.Add(new TH1F("h_el_fo40c_noiso_vs_nvtxs", "fo electron (away jet p_{T} > 40, no iso, cpfiso03 < 0.6 (#rho * A_{eff}));# vtxs", m_fr_bin_info.num_el_vtx_bins(), m_fr_bin_info.el_vtx_bins()), "texte");
        hc.Add(new TH1F("h_el_fo60c_noiso_vs_nvtxs", "fo electron (away jet p_{T} > 60, no iso, cpfiso03 < 0.6 (#rho * A_{eff}));# vtxs", m_fr_bin_info.num_el_vtx_bins(), m_fr_bin_info.el_vtx_bins()), "texte");

        hc.Add(new TH2F("h_el_fo20c_noiso", "fo electron (away jet p_{T} > 20, no iso, cpfiso03 < 0.6 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", m_fr_bin_info.num_el_eta_bins(), m_fr_bin_info.el_eta_bins(), m_fr_bin_info.num_el_pt_bins(), m_fr_bin_info.el_pt_bins()), "texte");
        hc.Add(new TH2F("h_el_fo40c_noiso", "fo electron (away jet p_{T} > 40, no iso, cpfiso03 < 0.6 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", m_fr_bin_info.num_el_eta_bins(), m_fr_bin_info.el_eta_bins(), m_fr_bin_info.num_el_pt_bins(), m_fr_bin_info.el_pt_bins()), "texte");
        hc.Add(new TH2F("h_el_fo60c_noiso", "fo electron (away jet p_{T} > 60, no iso, cpfiso03 < 0.6 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", m_fr_bin_info.num_el_eta_bins(), m_fr_bin_info.el_eta_bins(), m_fr_bin_info.num_el_pt_bins(), m_fr_bin_info.el_pt_bins()), "texte");

        // MET distribution denominator
        hc.Add(new TH1F("h_el_fo20c_met", "h_el_fo20c_met", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_fo40c_met", "h_el_fo40c_met", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_fo60c_met", "h_el_fo60c_met", nbins, min_val, max_val));

        // MT distribution denominator, MET > 30
        hc.Add(new TH1F("h_el_fo20c_mt_met30gt", "h_el_fo20c_mt_met30gt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_fo40c_mt_met30gt", "h_el_fo40c_mt_met30gt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_fo60c_mt_met30gt", "h_el_fo60c_mt_met30gt", nbins, min_val, max_val));

        // MT distribution denominator, MET < 20 GeV
        hc.Add(new TH1F("h_el_fo20c_mt_met20lt", "h_el_fo20c_mt_met20lt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_fo40c_mt_met20lt", "h_el_fo40c_mt_met20lt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_fo60c_mt_met20lt", "h_el_fo60c_mt_met20lt", nbins, min_val, max_val));

        // electron FO pt distribution
        hc.Add(new TH1F("h_el_fo20c_pt", "h_el_fo20c_pt", 12, 0., 60.));
        hc.Add(new TH1F("h_el_fo40c_pt", "h_el_fo40c_pt", 12, 0., 60.));
        hc.Add(new TH1F("h_el_fo60c_pt", "h_el_fo60c_pt", 12, 0., 60.));

        // electron FO eta distribution
        hc.Add(new TH1F("h_el_fo20c_eta", "h_el_fo20c_eta", 10, -2.5, 2.5));
        hc.Add(new TH1F("h_el_fo40c_eta", "h_el_fo40c_eta", 10, -2.5, 2.5));
        hc.Add(new TH1F("h_el_fo60c_eta", "h_el_fo60c_eta", 10, -2.5, 2.5));

        // MET distribution numerator
        hc.Add(new TH1F("h_el_num20c_met", "h_el_num20c_met", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_num40c_met", "h_el_num40c_met", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_num60c_met", "h_el_num60c_met", nbins, min_val, max_val));

        // MT distribution numerator
        hc.Add(new TH1F("h_el_num20c_mt_met30gt", "h_el_num20c_mt_met30gt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_num40c_mt_met30gt", "h_el_num40c_mt_met30gt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_num60c_mt_met30gt", "h_el_num60c_mt_met30gt", nbins, min_val, max_val));

        // MT distribution denominator, MET < 20 GeV
        hc.Add(new TH1F("h_el_num20c_mt_met20lt", "h_el_num20c_mt_met20lt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_num40c_mt_met20lt", "h_el_num40c_mt_met20lt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_num60c_mt_met20lt", "h_el_num60c_mt_met20lt", nbins, min_val, max_val));

        // electron NUM pt distribution
        hc.Add(new TH1F("h_el_num20c_pt", "h_el_num20c_pt", 12, 0., 60.));
        hc.Add(new TH1F("h_el_num40c_pt", "h_el_num40c_pt", 12, 0., 60.));
        hc.Add(new TH1F("h_el_num60c_pt", "h_el_num60c_pt", 12, 0., 60.));

        // electron NUM eta distribution
        hc.Add(new TH1F("h_el_num20c_eta", "h_el_num20c_eta", 10, -2.5, 2.5));
        hc.Add(new TH1F("h_el_num40c_eta", "h_el_num40c_eta", 10, -2.5, 2.5));
        hc.Add(new TH1F("h_el_num60c_eta", "h_el_num60c_eta", 10, -2.5, 2.5));

        // (electron noiso triggers) MET distribution denominator
        hc.Add(new TH1F("h_el_noiso_fo20c_met", "h_el_noiso_fo20c_met", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_noiso_fo40c_met", "h_el_noiso_fo40c_met", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_noiso_fo60c_met", "h_el_noiso_fo60c_met", nbins, min_val, max_val));

        // (electron noiso triggers) MT distribution denominator, MET > 30
        hc.Add(new TH1F("h_el_noiso_fo20c_mt_met30gt", "h_el_noiso_fo20c_mt_met30gt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_noiso_fo40c_mt_met30gt", "h_el_noiso_fo40c_mt_met30gt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_noiso_fo60c_mt_met30gt", "h_el_noiso_fo60c_mt_met30gt", nbins, min_val, max_val));

        // (electron noiso triggers) MT distribution denominator, MET < 20 GeV
        hc.Add(new TH1F("h_el_noiso_fo20c_mt_met20lt", "h_el_noiso_fo20c_mt_met20lt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_noiso_fo40c_mt_met20lt", "h_el_noiso_fo40c_mt_met20lt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_noiso_fo60c_mt_met20lt", "h_el_noiso_fo60c_mt_met20lt", nbins, min_val, max_val));

        // (electron noiso triggers) electron FO pt distribution
        hc.Add(new TH1F("h_el_noiso_fo20c_pt", "h_el_noiso_fo20c_pt", 12, 0., 60.));
        hc.Add(new TH1F("h_el_noiso_fo40c_pt", "h_el_noiso_fo40c_pt", 12, 0., 60.));
        hc.Add(new TH1F("h_el_noiso_fo60c_pt", "h_el_noiso_fo60c_pt", 12, 0., 60.));

        // (electron noiso triggers) electron FO eta distribution
        hc.Add(new TH1F("h_el_noiso_fo20c_eta", "h_el_noiso_fo20c_eta", 10, -2.5, 2.5));
        hc.Add(new TH1F("h_el_noiso_fo40c_eta", "h_el_noiso_fo40c_eta", 10, -2.5, 2.5));
        hc.Add(new TH1F("h_el_noiso_fo60c_eta", "h_el_noiso_fo60c_eta", 10, -2.5, 2.5));

        // (electron noiso triggers) MET distribution numerator
        hc.Add(new TH1F("h_el_noiso_num20c_met", "h_el_noiso_num20c_met", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_noiso_num40c_met", "h_el_noiso_num40c_met", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_noiso_num60c_met", "h_el_noiso_num60c_met", nbins, min_val, max_val));

        // (electron noiso triggers) MT distribution numerator
        hc.Add(new TH1F("h_el_noiso_num20c_mt_met30gt", "h_el_noiso_num20c_mt_met30gt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_noiso_num40c_mt_met30gt", "h_el_noiso_num40c_mt_met30gt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_noiso_num60c_mt_met30gt", "h_el_noiso_num60c_mt_met30gt", nbins, min_val, max_val));

        // (electron noiso triggers) MT distribution denominator, MET < 20 GeV
        hc.Add(new TH1F("h_el_noiso_num20c_mt_met20lt", "h_el_noiso_num20c_mt_met20lt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_noiso_num40c_mt_met20lt", "h_el_noiso_num40c_mt_met20lt", nbins, min_val, max_val));
        hc.Add(new TH1F("h_el_noiso_num60c_mt_met20lt", "h_el_noiso_num60c_mt_met20lt", nbins, min_val, max_val));

        // (electron noiso triggers) electron NUM pt distribution
        hc.Add(new TH1F("h_el_noiso_num20c_pt", "h_el_noiso_num20c_pt", 12, 0., 60.));
        hc.Add(new TH1F("h_el_noiso_num40c_pt", "h_el_noiso_num40c_pt", 12, 0., 60.));
        hc.Add(new TH1F("h_el_noiso_num60c_pt", "h_el_noiso_num60c_pt", 12, 0., 60.));

        // (electron noiso triggers) electron NUM eta distribution
        hc.Add(new TH1F("h_el_noiso_num20c_eta", "h_el_noiso_num20c_eta", 10, -2.5, 2.5));
        hc.Add(new TH1F("h_el_noiso_num40c_eta", "h_el_noiso_num40c_eta", 10, -2.5, 2.5));
        hc.Add(new TH1F("h_el_noiso_num60c_eta", "h_el_noiso_num60c_eta", 10, -2.5, 2.5));
    }

    hc.Sumw2();
    return;
}

// main analysis function operator 
int FakeRateBabyLooper::operator()(long event, const std::string& current_file_name)
{
    using namespace std;
    using namespace frb;

    try
    {
        // base analysis
        at::AnalysisWithHist::operator()(event);

        // convenience alias
        rt::TH1Container& hc = m_hist_container;

        // FO selection cuts
        // ----------------------------------------------------------------------------------------------------------------------------//

        // which dataset
        const bool is_data  = (fr::GetSampleInfo(m_sample).type == fr::SampleType::data);
        const bool is_qcd   = (m_sample==fr::Sample::qcd);
        const bool is_ttbar = (m_sample==fr::Sample::ttbar);
        const bool is_ttbarhad = (m_sample==fr::Sample::tthad);
        const bool is_mu    = ((m_lepton=="mu") ? abs(id())==13 : false);
        const bool is_el    = ((m_lepton=="el") ? abs(id())==11 : false);
        const bool is_wjets = (m_sample==fr::Sample::wjets);
        const bool is_dy    = (m_sample==fr::Sample::dy);

        if (!is_mu && !is_el) return 0;

        if ((is_wjets || is_dy || is_ttbar) && leptonIsFromW()<1)
        {
            if (m_verbose) {cout << "fails prompt lepton cut" << endl;}
            return 0;
        }

        // qcd muon cuts (for the different qcd samples)
        const bool qcd_mu_low  = rt::string_contains(current_file_name, "MuEnrichedPt5"  ) && pt() < 16.0; 
        const bool qcd_mu_high = rt::string_contains(current_file_name, "MuEnrichedPt_15") && pt() >= 16.0; 
        const bool qcd_el      = not (qcd_mu_low or qcd_mu_high); 
        if (is_mu && is_qcd && not (qcd_mu_low || qcd_mu_high))
        {
            return 0;
        }
        else if (is_el && is_qcd && not qcd_el)
        {
            return 0;
        }

	// Get rid of useless samples with no statistics at all.
	if (rt::string_contains(current_file_name, "5to15_TuneZ2star")  || rt::string_contains(current_file_name, "15to30_TuneZ2star")  )
	  return 0;


        // check the charge
        switch (m_charge)
        {
            case  1: if (id()>0) {return 0;} break; // 11/13   --> e-/mu- (reject)
            case -1: if (id()<0) {return 0;} break; // -11/-13 --> e+/mu+ (reject)
            case  0: /*do nothing*/ break;
            default: /*do nothing*/ break;
        };

        // pT cut
        float min_mu_pt = m_fr_bin_info.mu_pt_bins()[0];
	float max_mu_pt = m_fr_bin_info.mu_pt_bins()[m_fr_bin_info.num_mu_pt_bins()];
	//float min_mu_pt = 20.0;
	//float max_mu_pt = 150.0;
        float min_el_pt = m_fr_bin_info.el_pt_bins()[0];
        float max_el_pt = m_fr_bin_info.el_pt_bins()[m_fr_bin_info.num_el_pt_bins()];

        if (is_mu && (pt()<min_mu_pt || pt()>max_mu_pt))
        {
            if (m_verbose) {cout << "fails pt cut with pt " << pt() << endl;}
            return 0;
        }
        if (is_el && (pt()<min_el_pt || pt()>max_el_pt))
        {
            if (m_verbose) {cout << "fails pt cut with pt " << pt() << endl;}
            return 0;
        }

        // eta cut
        if (fabs(eta()) > 2.4)
        {
            if (m_verbose) {cout << "fails eta cut" << endl;}
            return 0;
        }

        // trigger cuts
        bool trig_cut       = (is_data ? false : true);
        bool trig_cut_noiso = (is_data ? false : true);  // electron non-isolated triggers
        bool trig_cut_iso   = (is_data ? false : true);  // muon isolated triggers
        if (m_fr_type == ss::FakeRateType::eth)
        {
            if (is_data && is_mu)
            {
                trig_cut = (mu17_vstar()>0);
            }
            else if(is_data && is_el)
            {
                trig_cut = ((pt()>17 && (ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()> 1 || ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()> 1 ||
                                         ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()> 1  || ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()> 1 ))
                            || (pt()>8 && (ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()>1 || ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()>1)));
            }            
        }
        else
        {
            if (is_data && is_mu)
            {
                // trigger without isolation
                trig_cut = ((pt() > 24 && (mu24_eta2p1_vstar() > 1 || mu17_vstar()>1 || mu8_vstar()>1)) || 
                            (pt() > 17 && (mu17_vstar()>1 || mu8_vstar()>1)) || 
                            (pt() > 8  && (mu8_vstar()>1)));

                // trigger with isolation
                trig_cut_iso = ((pt() > 20 && (relIso1p0Mu20_vstar()>1 || relIso1p0Mu5_vstar()>1)) || 
                                (pt() > 5  && (relIso1p0Mu5_vstar()>1)));
            }
            else if(is_data && is_el)
            {
                // triggers with isolation
                trig_cut = ((pt()>17 && (ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()> 1 || ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()> 1 ||
                                         ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()> 1  || ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()> 1 ))
                            || (pt()>8 && (ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()>1 || ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()>1)));

                // triggers without isolation
                trig_cut_noiso = (pt() > 8 && (ele8_CaloIdT_TrkIdVL_Jet30_vstar()>1 || ele8_CaloIdT_TrkIdVL_vstar()>1));
            }
        }

        // away jet cut
        bool jet_dwn_cut = false;
        bool jet_cut = false;
        bool jet_up_cut = false;
        if (m_btag_away_jet)
        {
            jet_dwn_cut = is_data ? (ptbtagpfcL1Fj1res() > m_away_jet_pt-20.) : (ptbtagpfcL1Fj1() > m_away_jet_pt-20.);
            jet_cut     = is_data ? (ptbtagpfcL1Fj1res() > m_away_jet_pt)     : (ptbtagpfcL1Fj1() > m_away_jet_pt);
            jet_up_cut  = is_data ? (ptbtagpfcL1Fj1res() > m_away_jet_pt+20.) : (ptbtagpfcL1Fj1() > m_away_jet_pt+20.);
        }
        else
        {
            jet_dwn_cut = is_data ? (ptpfcL1Fj1res() > m_away_jet_pt-20.) : (ptpfcL1Fj1() > m_away_jet_pt-20.);
            jet_cut     = is_data ? (ptpfcL1Fj1res() > m_away_jet_pt)     : (ptpfcL1Fj1() > m_away_jet_pt);
            jet_up_cut  = is_data ? (ptpfcL1Fj1res() > m_away_jet_pt+20.) : (ptpfcL1Fj1() > m_away_jet_pt+20.);
        }

        bool jet_dphi_cut = is_data ? (dphipfcL1Fj1res() > m_away_jet_dphi) : (dphipfcL1Fj1() > m_away_jet_dphi);

        if (m_fr_type == ss::FakeRateType::eth && rt::is_equal(m_away_jet_pt, 50.f))
        {
            jet_cut = is_data ? (npfc50L1Fj1res_eth() > 0) : (npfc50L1Fj1_eth() > 0); // actually a jet 50 cut
        }

        if (is_ttbar || is_ttbarhad)
        {
            jet_dwn_cut  = true;
            jet_cut      = true;
            jet_up_cut   = true;
            jet_dphi_cut = true;
        }

        if (not jet_dphi_cut)
        {
            if (m_verbose) {cout << "fails jet dphi cut" << endl;}
            return 0;
        }

        // no resonance's (Z or upsilon), no extra leptons in event
        if (m_fr_type == ss::FakeRateType::eth)
        {
            if (nvetomus()>0 || nvetoels()>0)
            {
                if (m_verbose) {printf("fails no veto lepton cut.  found %d veto muons and %d veto electrons.\n", nvetomus(), nvetoels());}
                return 0;
            }
        }
        else
        {
            if (is_mu && ((76<mz_fo_ctf() && mz_fo_ctf()<106) || (8<mupsilon_fo_mu() && mupsilon_fo_mu()<12)))
            {
                if (m_verbose) {cout << "fails no Z cut" << endl;}
                return 0;
            }
            else if (is_el && (76<mz_fo_gsf() && mz_fo_gsf()<106))
            {
                if (m_verbose) {cout << "fails no Z cut" << endl;}
                return 0;
            }

            // no additional FO's in event
            if (is_mu && (nFOmus()>0))
            {
                if (m_verbose) {cout << "fails no addition muon FO cut" << endl;}
                return 0;
            }
            else if(is_el && (nFOels()>0))
            {
                if (m_verbose) {cout << "fails no addition FO cut" << endl;}
                return 0;
            }
        }

        // numerator cut
        bool num_lep_cut = false;
        if (is_mu)
        {
            num_lep_cut = num_mu_ssV5_noIso();
            if (m_apply_tight_d0_cut) num_lep_cut = num_lep_cut && (fabs(d0()) < 0.005);
        }
        else if(is_el)
        {
            num_lep_cut = num_el_ssV7_noIso();
            if (m_apply_tight_d0_cut) num_lep_cut = num_lep_cut && (fabs(d0()) < 0.01);
        }

        // denominator cut
        bool fo_lep_cut = false;
        if (is_mu)
        {
            fo_lep_cut = ((m_fr_type == ss::FakeRateType::eth) ? num_mu_ssV5_noIso() : fo_mu_ssV5_noIso());
        }
        else if(is_el)
        {
            fo_lep_cut = ((m_fr_type == ss::FakeRateType::eth) ? v3_el_ssV7() : v3_el_ssV7()); // THIS IS WRONG!!! STILL NEED TO IMPLEMENT ETH FO DEFINITION FOR ELECTRONS
        }

        // passes selection (no isolaiton)
        bool num_lep_sel_notrig     = (num_lep_cut);
        bool fo_lep_sel_notrig      = (fo_lep_cut);
        bool num_lep_sel            = (trig_cut && num_lep_sel_notrig); 
        bool fo_lep_sel             = (trig_cut && fo_lep_sel_notrig); 
        bool num_lep_sel_trig_noiso = (trig_cut_noiso && num_lep_sel_notrig);
        bool fo_lep_sel_trig_noiso  = (trig_cut_noiso && fo_lep_sel_notrig);
        bool num_lep_sel_trig_iso   = (trig_cut_iso && num_lep_sel_notrig);
        bool fo_lep_sel_trig_iso    = (trig_cut_iso && fo_lep_sel_notrig);

        // skip if not FO
        if (!fo_lep_sel_notrig)
        {
            if (m_verbose) {cout << "fails FO ID cut" << endl;}
            return 0;
        }

        // vertex reweight for ttbar
        float evt_weight = (is_data ? 1.0 : (weight() * m_lumi));
	// Fix wrong normalization in specific sample
	if (rt::string_contains(current_file_name, "15to30_TuneZ2star") && !is_data) {
	  //cout<<"Found event in file "<<current_file_name<<": adjusting weight. Old weight "<<evt_weight;
	  evt_weight *= ( 9.8828742E8 / 4.2639499E10 );
	  //cout<<" new weight "<<evt_weight<<endl;
	}

        // isolation
        float iso = ((m_lepton == "mu") ? cpfiso03_db() : pfiso03_corr_rho()); // new effective area
        // float iso = ((m_lepton == "mu") ? cpfiso03_db() : cpfiso03_rho());  // old effective area
        // float iso = ((m_lepton == "mu") ? cpfiso03_db_truncated() : cpfiso03_rho_truncated()); // new effective area
	float chiso =  ch_pfiso03()/pt(); // (all isolations are relative. probably a good idea for the pT one)
	float chisoGeV =  ch_pfiso03(); 
	float caloiso =  iso - chiso;
	float caloisoGeV = iso*pt() - chisoGeV;
	float isoGeV = iso*pt();


        float num_mu_iso_cut = 0.1;
        float den_mu_iso_cut = m_mu_iso_denom;

        float num_el_iso_cut = 0.09;
        float den_el_iso_cut = ((m_fr_type == ss::FakeRateType::eth) ? 1.0 : 0.6);
	
	float num_mu_iso_cutAbs = 2.0;
	float den_mu_iso_cutAbs = 8.0;
	
	bool isNumIso = false;
	bool isDenIso = false;
	if (m_lepton == "mu") {
	  isNumIso = m_absolute_iso ? isoGeV < num_mu_iso_cutAbs : iso < num_mu_iso_cut;
	  //isDenIso = m_absolute_iso ? isoGeV < den_mu_iso_cutAbs : iso < den_mu_iso_cut;
	  isDenIso =  iso < den_mu_iso_cut;
	}

        
        // Fill some plots
        // -------------------------------------------------------------------------------------- //

        if (m_lepton == "mu")
        {
            // numerator
            if (num_lep_sel)
            {
                if (isNumIso)
                {
                    if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_mu_num20c_met"], pfmet(), evt_weight); }
                    if (jet_cut     && pt() > 20) { rt::Fill( hc["h_mu_num40c_met"], pfmet(), evt_weight); }
                    if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_mu_num60c_met"], pfmet(), evt_weight); }

                    if (pfmet() > 30)
                    {
                        if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_mu_num20c_mt_met30gt"], pfmt(), evt_weight); }
                        if (jet_cut     && pt() > 20) { rt::Fill( hc["h_mu_num40c_mt_met30gt"], pfmt(), evt_weight); }
                        if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_mu_num60c_mt_met30gt"], pfmt(), evt_weight); }
                    }

                    if (pfmet() < 20)
                    {
                        if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_mu_num20c_mt_met20lt"], pfmt(), evt_weight); }
                        if (jet_cut     && pt() > 20) { rt::Fill( hc["h_mu_num40c_mt_met20lt"], pfmt(), evt_weight); }
                        if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_mu_num60c_mt_met20lt"], pfmt(), evt_weight); }                        
                    }
                }
            }
            if (fo_lep_sel)
            {
	      if ( (num_lep_sel || !m_only_invert_isocut_mu)  && isDenIso) // if "m_only_invert_isocut_mu", require the numerator selection to pass
                {
                    if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_mu_fo20c_met"], pfmet(), evt_weight); }
                    if (jet_cut     && pt() > 20) { rt::Fill( hc["h_mu_fo40c_met"], pfmet(), evt_weight); }
                    if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_mu_fo60c_met"], pfmet(), evt_weight); }

                    if (pfmet() > 30)
                    {
                        if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_mu_fo20c_mt_met30gt"], pfmt(), evt_weight); }
                        if (jet_cut     && pt() > 20) { rt::Fill( hc["h_mu_fo40c_mt_met30gt"], pfmt(), evt_weight); }
                        if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_mu_fo60c_mt_met30gt"], pfmt(), evt_weight); }                        
                    }

                    if (pfmet() < 20)
                    {
                        if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_mu_fo20c_mt_met20lt"], pfmt(), evt_weight); }
                        if (jet_cut     && pt() > 20) { rt::Fill( hc["h_mu_fo40c_mt_met20lt"], pfmt(), evt_weight); }
                        if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_mu_fo60c_mt_met20lt"], pfmt(), evt_weight); }                        
                    }
                }
            }
            // numerator
            if (num_lep_sel_trig_iso)
            {
                if (iso < num_mu_iso_cut)
                {
                    if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_mu_iso_num20c_met"], pfmet(), evt_weight); }
                    if (jet_cut     && pt() > 20) { rt::Fill( hc["h_mu_iso_num40c_met"], pfmet(), evt_weight); }
                    if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_mu_iso_num60c_met"], pfmet(), evt_weight); }

                    if (pfmet() > 30)
                    {
                        if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_mu_iso_num20c_mt_met30gt"], pfmt(), evt_weight); }
                        if (jet_cut     && pt() > 20) { rt::Fill( hc["h_mu_iso_num40c_mt_met30gt"], pfmt(), evt_weight); }
                        if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_mu_iso_num60c_mt_met30gt"], pfmt(), evt_weight); }
                    }

                    if (pfmet() < 20)
                    {
                        if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_mu_iso_num20c_mt_met20lt"], pfmt(), evt_weight); }
                        if (jet_cut     && pt() > 20) { rt::Fill( hc["h_mu_iso_num40c_mt_met20lt"], pfmt(), evt_weight); }
                        if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_mu_iso_num60c_mt_met20lt"], pfmt(), evt_weight); }                        
                    }
                }
            }
            if (fo_lep_sel_trig_iso)
            {
                if (iso < den_mu_iso_cut)
                {
                    if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_mu_iso_fo20c_met"], pfmet(), evt_weight); }
                    if (jet_cut     && pt() > 20) { rt::Fill( hc["h_mu_iso_fo40c_met"], pfmet(), evt_weight); }
                    if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_mu_iso_fo60c_met"], pfmet(), evt_weight); }

                    if (pfmet() > 30)
                    {
                        if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_mu_iso_fo20c_mt_met30gt"], pfmt(), evt_weight); }
                        if (jet_cut     && pt() > 20) { rt::Fill( hc["h_mu_iso_fo40c_mt_met30gt"], pfmt(), evt_weight); }
                        if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_mu_iso_fo60c_mt_met30gt"], pfmt(), evt_weight); }                        
                    }

                    if (pfmet() < 20)
                    {
                        if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_mu_iso_fo20c_mt_met20lt"], pfmt(), evt_weight); }
                        if (jet_cut     && pt() > 20) { rt::Fill( hc["h_mu_iso_fo40c_mt_met20lt"], pfmt(), evt_weight); }
                        if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_mu_iso_fo60c_mt_met20lt"], pfmt(), evt_weight); }                        
                    }
                }
            }
        }
        if (m_lepton == "el")
        {
            // numerator
            if (num_lep_sel)
            {
                if (iso < num_el_iso_cut)
                {
                    if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_el_num20c_met"], pfmet(), evt_weight); }
                    if (jet_cut     && pt() > 20) { rt::Fill( hc["h_el_num40c_met"], pfmet(), evt_weight); }
                    if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_el_num60c_met"], pfmet(), evt_weight); }

                    if (pfmet() > 30)
                    {
                        if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_el_num20c_mt_met30gt"], pfmt(), evt_weight); }
                        if (jet_cut     && pt() > 20) { rt::Fill( hc["h_el_num40c_mt_met30gt"], pfmt(), evt_weight); }
                        if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_el_num60c_mt_met30gt"], pfmt(), evt_weight); }
                    }

                    if (pfmet() < 20)
                    {
                        if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_el_num20c_mt_met20lt"], pfmt(), evt_weight); }
                        if (jet_cut     && pt() > 20) { rt::Fill( hc["h_el_num40c_mt_met20lt"], pfmt(), evt_weight); }
                        if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_el_num60c_mt_met20lt"], pfmt(), evt_weight); }                        
                    }
                }
            }
            if (fo_lep_sel)
            {
                if (iso < den_el_iso_cut)
                {
                    if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_el_fo20c_met"], pfmet(), evt_weight); }
                    if (jet_cut     && pt() > 20) { rt::Fill( hc["h_el_fo40c_met"], pfmet(), evt_weight); }
                    if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_el_fo60c_met"], pfmet(), evt_weight); }

                    if (pfmet() > 30)
                    {
                        if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_el_fo20c_mt_met30gt"], pfmt(), evt_weight); }
                        if (jet_cut     && pt() > 20) { rt::Fill( hc["h_el_fo40c_mt_met30gt"], pfmt(), evt_weight); }
                        if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_el_fo60c_mt_met30gt"], pfmt(), evt_weight); }                        
                    }
                    if (pfmet() < 20)
                    {
                        if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_el_fo20c_mt_met20lt"], pfmt(), evt_weight); }
                        if (jet_cut     && pt() > 20) { rt::Fill( hc["h_el_fo40c_mt_met20lt"], pfmt(), evt_weight); }
                        if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_el_fo60c_mt_met20lt"], pfmt(), evt_weight); }                        
                    }
                }
            }
            // numerator
            if (num_lep_sel_trig_noiso)
            {
                if (iso < num_el_iso_cut)
                {
                    if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_el_noiso_num20c_met"], pfmet(), evt_weight); }
                    if (jet_cut     && pt() > 20) { rt::Fill( hc["h_el_noiso_num40c_met"], pfmet(), evt_weight); }
                    if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_el_noiso_num60c_met"], pfmet(), evt_weight); }

                    if (pfmet() > 30)
                    {
                        if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_el_noiso_num20c_mt_met30gt"], pfmt(), evt_weight); }
                        if (jet_cut     && pt() > 20) { rt::Fill( hc["h_el_noiso_num40c_mt_met30gt"], pfmt(), evt_weight); }
                        if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_el_noiso_num60c_mt_met30gt"], pfmt(), evt_weight); }
                    }

                    if (pfmet() < 20)
                    {
                        if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_el_noiso_num20c_mt_met20lt"], pfmt(), evt_weight); }
                        if (jet_cut     && pt() > 20) { rt::Fill( hc["h_el_noiso_num40c_mt_met20lt"], pfmt(), evt_weight); }
                        if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_el_noiso_num60c_mt_met20lt"], pfmt(), evt_weight); }                        
                    }
                }
            }
            if (fo_lep_sel_trig_noiso)
            {
                if (iso < den_el_iso_cut)
                {
                    if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_el_noiso_fo20c_met"], pfmet(), evt_weight); }
                    if (jet_cut     && pt() > 20) { rt::Fill( hc["h_el_noiso_fo40c_met"], pfmet(), evt_weight); }
                    if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_el_noiso_fo60c_met"], pfmet(), evt_weight); }

                    if (pfmet() > 30)
                    {
                        if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_el_noiso_fo20c_mt_met30gt"], pfmt(), evt_weight); }
                        if (jet_cut     && pt() > 20) { rt::Fill( hc["h_el_noiso_fo40c_mt_met30gt"], pfmt(), evt_weight); }
                        if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_el_noiso_fo60c_mt_met30gt"], pfmt(), evt_weight); }                        
                    }
                    if (pfmet() < 20)
                    {
                        if (jet_dwn_cut && pt() > 20) { rt::Fill( hc["h_el_noiso_fo20c_mt_met20lt"], pfmt(), evt_weight); }
                        if (jet_cut     && pt() > 20) { rt::Fill( hc["h_el_noiso_fo40c_mt_met20lt"], pfmt(), evt_weight); }
                        if (jet_up_cut  && pt() > 20) { rt::Fill( hc["h_el_noiso_fo60c_mt_met20lt"], pfmt(), evt_weight); }                        
                    }
                }
            }
        }

        // no W (MET and m_T cuts)
        // float mt_cut = ((m_fr_type == ss::FakeRateType::eth) ? 20. : 25.);
        float mt_cut = 20.;
        if (pfmet()>20 || pfmt()>mt_cut)
        {
            if (m_verbose) {cout << "fails no W cut" << endl;}
            return 0;
        }

        // muons after MET and WmT cuts
        // ----------------------------------------------------------------------------------------------------------------------------//

        // Fill Fake Rates
        if (m_lepton == "mu")
        {
            // numerator
            if (num_lep_sel)
            {
                if (isNumIso)
                {
                    if (jet_dwn_cut && pt()>20) { rt::Fill( hc["h_mu_num20c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet_cut     && pt()>20) { rt::Fill( hc["h_mu_num40c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet_up_cut  && pt()>20) { rt::Fill( hc["h_mu_num60c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet_dwn_cut           ) { rt::Fill2D(hc["h_mu_num20c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet_cut               ) { rt::Fill2D(hc["h_mu_num40c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet_up_cut            ) { rt::Fill2D(hc["h_mu_num60c"], fabs(eta()), pt(), evt_weight); }

                    if (jet_dwn_cut ) { rt::Fill( hc["h_mu_num20c_pt"], pt(), evt_weight); }
                    if (jet_cut     ) { rt::Fill( hc["h_mu_num40c_pt"], pt(), evt_weight); }
                    if (jet_up_cut  ) { rt::Fill( hc["h_mu_num60c_pt"], pt(), evt_weight); }

                    if (jet_dwn_cut ) { rt::Fill( hc["h_mu_num20c_eta"], eta(), evt_weight); }
                    if (jet_cut     ) { rt::Fill( hc["h_mu_num40c_eta"], eta(), evt_weight); }
                    if (jet_up_cut  ) { rt::Fill( hc["h_mu_num60c_eta"], eta(), evt_weight); }
                }
            }

            // denominator
            if (fo_lep_sel)
            {
	      if (pt() > 20.0 && pt() < 22.0) {		
		rt::Fill( hc["h_mu_fo_iso"], iso, evt_weight);
		rt::Fill( hc["h_mu_fo_isoGeV"], isoGeV, evt_weight);
		rt::Fill( hc["h_mu_fo_chiso"], chiso, evt_weight);
		rt::Fill( hc["h_mu_fo_chisoGeV"], chisoGeV, evt_weight);
		rt::Fill( hc["h_mu_fo_caloiso"], caloiso, evt_weight);
		rt::Fill( hc["h_mu_fo_caloisoGeV"], caloisoGeV, evt_weight);
		rt::Fill( hc["h_mu_fo_d0"], fabs(d0()), evt_weight);
		rt::Fill( hc["h_mu_fo_jetPt"], ptpfcL1Fj1(), evt_weight);

		rt::Fill( hc["h_mu_fo_ecal"], mu_ecal_veto_dep(), evt_weight);
		rt::Fill( hc["h_mu_fo_hcal"], mu_hcal_veto_dep(), evt_weight);
		rt::Fill2D( hc["h_mu_fo_ecal_vs_jetPt"], ptpfcL1Fj1(), mu_ecal_veto_dep(), evt_weight);
		rt::Fill2D( hc["h_mu_fo_hcal_vs_jetPt"], ptpfcL1Fj1(), mu_hcal_veto_dep(), evt_weight);
		rt::Fill2D( hc["h_mu_fo_ecal_vs_iso"], iso, mu_ecal_veto_dep(), evt_weight);
		rt::Fill2D( hc["h_mu_fo_hcal_vs_iso"], iso, mu_hcal_veto_dep(), evt_weight);

		bool isoNum = (iso < 0.1);
		bool isoDen = (iso > 0.1 && iso < 0.4);
		bool chisoNum = chiso < 0.1;
		bool caloisoNum = caloiso < 0.1;
		bool d0num = fabs(d0()) < 0.005;
		bool hcal = (mu_hcal_veto_dep() < 6.0);
		bool ecal = (mu_ecal_veto_dep() < 4.0);

		if (num_lep_sel) rt::Fill( hc["h_mu_fo_jetPt_num"], ptpfcL1Fj1(), evt_weight);
		if (num_lep_sel && isoNum) rt::Fill( hc["h_mu_fo_jetPt_num_iso01"], ptpfcL1Fj1(), evt_weight);
		if (num_lep_sel && isoDen) rt::Fill( hc["h_mu_fo_jetPt_num_iso04"], ptpfcL1Fj1(), evt_weight);
		if (num_lep_sel && isoNum) rt::Fill( hc["h_mu_fo_qPt_num_iso01"], mc3pt(), evt_weight);
		if (num_lep_sel && isoDen) rt::Fill( hc["h_mu_fo_qPt_num_iso04"], mc3pt(), evt_weight);
		if (num_lep_sel && !isoNum && iso < 0.2) rt::Fill( hc["h_mu_fo_jetPt_num_iso02"], ptpfcL1Fj1(), evt_weight);
		if (num_lep_sel && !isoNum && iso < 0.3) rt::Fill( hc["h_mu_fo_jetPt_num_iso03"], ptpfcL1Fj1(), evt_weight);
		if (num_lep_sel && isoDen && chisoNum) rt::Fill( hc["h_mu_fo_jetPt_num_iso04_ch01"], ptpfcL1Fj1(), evt_weight); // pass ID, fail iso, low charged iso
		if (num_lep_sel && isoDen && caloisoNum) rt::Fill( hc["h_mu_fo_jetPt_num_iso04_nu01"], ptpfcL1Fj1(), evt_weight); // pass ID, fail iso, low neutral iso
		if (num_lep_sel && isoDen && (chisoNum || caloisoNum)) rt::Fill( hc["h_mu_fo_jetPt_num_iso04_chnu01"], ptpfcL1Fj1(), evt_weight); // pass ID, fail iso, low charged or neutral iso
		if (!num_lep_sel) rt::Fill( hc["h_mu_fo_jetPt_nonum"], ptpfcL1Fj1(), evt_weight);
		if (!num_lep_sel && isoNum) rt::Fill( hc["h_mu_fo_jetPt_nonum_iso01"], ptpfcL1Fj1(), evt_weight);
		if (!num_lep_sel && isoDen) rt::Fill( hc["h_mu_fo_jetPt_nonum_iso04"], ptpfcL1Fj1(), evt_weight);
		if (!num_lep_sel && isoNum) rt::Fill( hc["h_mu_fo_qPt_nonum_iso01"], mc3pt(), evt_weight);
		if (!num_lep_sel && isoDen) rt::Fill( hc["h_mu_fo_qPt_nonum_iso04"], mc3pt(), evt_weight);
		if (isoNum) rt::Fill( hc["h_mu_fo_jetPt_iso01"], ptpfcL1Fj1(), evt_weight);
		if (isoDen) rt::Fill( hc["h_mu_fo_jetPt_iso04"], ptpfcL1Fj1(), evt_weight);
		if (!num_mu_ssV5_noIso() && isoDen && d0num) rt::Fill( hc["h_mu_fo_jetPt_nonum_iso04_d0"], ptpfcL1Fj1(), evt_weight);
		if (!num_mu_ssV5_noIso() && isoDen && !d0num) rt::Fill( hc["h_mu_fo_jetPt_nonum_iso04_nod0"], ptpfcL1Fj1(), evt_weight);
		if (!num_mu_ssV5_noIso() && isoDen && hcal && ecal) rt::Fill( hc["h_mu_fo_jetPt_nonum_iso04_MIP"], ptpfcL1Fj1(), evt_weight);
		if (!num_mu_ssV5_noIso() && isoDen && !(hcal && ecal)) rt::Fill( hc["h_mu_fo_jetPt_nonum_iso04_noMIP"], ptpfcL1Fj1(), evt_weight);

		if ( !(num_lep_sel && isoNum) && isoDen ) rt::Fill( hc["h_mu_fo_ecal_denominator"	 ], mu_ecal_veto_dep(), evt_weight);
		if ( !(num_lep_sel && isoNum) && isoDen ) rt::Fill( hc["h_mu_fo_hcal_denominator"	 ], mu_hcal_veto_dep(), evt_weight);
		if ( num_lep_sel && isoNum ) rt::Fill( hc["h_mu_fo_ecal_numerator"	 ], mu_ecal_veto_dep(), evt_weight);
		if ( num_lep_sel && isoNum ) rt::Fill( hc["h_mu_fo_hcal_numerator"	 ], mu_hcal_veto_dep(), evt_weight);
		
		//cout<<"num_lep_sel "<<num_lep_sel<<" , num_mu_ssV5_noIso "<<num_mu_ssV5_noIso()<<" , d0num "<<d0num<<" , hcal "<<hcal<<" , ecal "<<ecal<<" , tric_cut "<<trig_cut<<endl;


		rt::Fill( hc["h_mu_fo_lepPt"], pt(), evt_weight);
		rt::Fill2D( hc["h_mu_fo_iso_vs_chiso"], chiso, iso, evt_weight);
		rt::Fill2D( hc["h_mu_fo_iso_vs_caloiso"], caloiso, iso, evt_weight);
		rt::Fill2D( hc["h_mu_fo_chiso_vs_caloiso"], caloiso, chiso, evt_weight);
		rt::Fill2D( hc["h_mu_fo_chisoGeV_vs_caloisoGeV"], caloisoGeV, chisoGeV, evt_weight);
		rt::Fill2D( hc["h_mu_fo_iso_vs_jetPt"], ptpfcL1Fj1(), iso, evt_weight);
		rt::Fill2D( hc["h_mu_fo_isoGeV_vs_jetPt"], ptpfcL1Fj1(), isoGeV, evt_weight);
		rt::Fill2D( hc["h_mu_fo_caloiso_vs_jetPt"], ptpfcL1Fj1(), caloiso, evt_weight);
		rt::Fill2D( hc["h_mu_fo_chisoGeV_vs_jetPt"], ptpfcL1Fj1(), chisoGeV, evt_weight);
		rt::Fill2D( hc["h_mu_fo_caloisoGeV_vs_jetPt"], ptpfcL1Fj1(), caloisoGeV, evt_weight);
		if (caloiso < 0.1) rt::Fill2D( hc["h_mu_fo_chiso_vs_jetPt_caloiso01"], ptpfcL1Fj1(), chiso, evt_weight);
		if (chiso < 0.1) rt::Fill2D( hc["h_mu_fo_caloiso_vs_jetPt_chiso01"], ptpfcL1Fj1(), caloiso, evt_weight);
		if (caloisoGeV < 2.0) rt::Fill2D( hc["h_mu_fo_chisoGeV_vs_jetPt_caloiso2"], ptpfcL1Fj1(), chisoGeV, evt_weight);
		if (chisoGeV < 2.0) rt::Fill2D( hc["h_mu_fo_caloisoGeV_vs_jetPt_chiso2"], ptpfcL1Fj1(), caloisoGeV, evt_weight);
		rt::Fill2D( hc["h_mu_fo_iso_vs_lepPt"], pt(), iso, evt_weight);
		rt::Fill2D( hc["h_mu_fo_isoGeV_vs_lepPt"], pt(), isoGeV, evt_weight);
		rt::Fill2D( hc["h_mu_fo_chiso_vs_lepPt"], pt(), chiso, evt_weight);
		rt::Fill2D( hc["h_mu_fo_caloiso_vs_lepPt"], pt(), caloiso, evt_weight);
		rt::Fill2D( hc["h_mu_fo_chisoGeV_vs_lepPt"], pt(), chisoGeV, evt_weight);
		rt::Fill2D( hc["h_mu_fo_caloisoGeV_vs_lepPt"], pt(), caloisoGeV, evt_weight);
		rt::Fill2D( hc["h_mu_fo_d0_vs_jetPt"], ptpfcL1Fj1(), fabs(d0()), evt_weight);
		if (isoDen) rt::Fill2D( hc["h_mu_fo_d0_vs_jetPt_iso04"], ptpfcL1Fj1(), fabs(d0()), evt_weight);
		rt::Fill2D( hc["h_mu_fo_d0_vs_iso"], iso, fabs(d0()), evt_weight);
	      }

	      // Special plots, based on comparing a muon pT bin with a FO pT bin, where the FO pT can be defined in different ways		
	      float FOpt = pt() + (iso-0.1)*pt();// + max(0.0, mu_ecal_veto_dep() - 4.0) + max(0.0, mu_ecal_veto_dep() - 6.0);
	      // _B_:  pt() + iso*pt() + max(0.0, mu_ecal_veto_dep() - 4.0) + max(0.0, mu_ecal_veto_dep() - 6.0);
	      // _C_:  pt() + iso*pt();
	      bool hcal = (mu_hcal_veto_dep() < 6.0);
	      bool ecal = (mu_ecal_veto_dep() < 4.0);
	      // _D_: added hcal and ecal num requirements to denom
	      // _E_: added !qcd_mu_low to avoid skewed sample (but this limits pT down to 16 GeV, while it should go down to 14.3
	      // _F_: pt() + (iso-0.1)*pt()
	      if ( (num_lep_sel && iso < 0.1 && pt() > 20.0 && pt() < 22.0) || ( iso < 0.4 && !(num_lep_sel && iso < 0.1) && FOpt > 20.0 && FOpt < 22.0 && ecal && hcal && !qcd_mu_low) ) {
		bool isoNum = (iso < 0.1);
		bool isoDen = (iso > 0.1 && iso < 0.4);
		if ( num_lep_sel && isoNum ) rt::Fill( hc["h_mu_fojet_jetPt_num_iso01"	 ], ptpfcL1Fj1(), evt_weight);
		if ( num_lep_sel && isoDen ) rt::Fill( hc["h_mu_fojet_jetPt_num_iso04"	 ], ptpfcL1Fj1(), evt_weight);
		if (!num_lep_sel && isoNum ) rt::Fill( hc["h_mu_fojet_jetPt_nonum_iso01" ], ptpfcL1Fj1(), evt_weight);
		if (!num_lep_sel && isoDen ) rt::Fill( hc["h_mu_fojet_jetPt_nonum_iso04" ], ptpfcL1Fj1(), evt_weight);
		if ( num_lep_sel && isoNum ) rt::Fill( hc["h_mu_fojet_qPt_num_iso01"     ], mc3pt(), evt_weight);
		if ( num_lep_sel && isoDen ) rt::Fill( hc["h_mu_fojet_qPt_num_iso04"     ], mc3pt(), evt_weight);
		if (!num_lep_sel && isoNum ) rt::Fill( hc["h_mu_fojet_qPt_nonum_iso01"	 ], mc3pt(), evt_weight);
		if (!num_lep_sel && isoDen ) rt::Fill( hc["h_mu_fojet_qPt_nonum_iso04"	 ], mc3pt(), evt_weight);

		if ( num_lep_sel && isoNum && jet_dwn_cut) rt::Fill( hc["h_mu_fojet20_qPt_num_iso01"     ], mc3pt(), evt_weight);
		if ( num_lep_sel && isoDen && jet_dwn_cut) rt::Fill( hc["h_mu_fojet20_qPt_num_iso04"     ], mc3pt(), evt_weight);
		if ( num_lep_sel && isoNum && jet_cut) rt::Fill( hc["h_mu_fojet40_qPt_num_iso01"     ], mc3pt(), evt_weight);
		if ( num_lep_sel && isoDen && jet_cut) rt::Fill( hc["h_mu_fojet40_qPt_num_iso04"     ], mc3pt(), evt_weight);
		if ( num_lep_sel && isoNum && jet_up_cut) rt::Fill( hc["h_mu_fojet60_qPt_num_iso01"     ], mc3pt(), evt_weight);
		if ( num_lep_sel && isoDen && jet_up_cut) rt::Fill( hc["h_mu_fojet60_qPt_num_iso04"     ], mc3pt(), evt_weight);


	      } // end of special FOpt plots
	      
	      //	      if (iso < den_mu_iso_cut)
	      if ( (num_lep_sel || !m_only_invert_isocut_mu)  && isDenIso) // if "m_only_invert_isocut_mu", require the numerator selection to pass
                {
		  if (jet_dwn_cut && pt()>20) { rt::Fill( hc["h_mu_fo20c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
		  if (jet_cut     && pt()>20) { rt::Fill( hc["h_mu_fo40c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
		  if (jet_up_cut  && pt()>20) { rt::Fill( hc["h_mu_fo60c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
		  
		  if (!m_use_FOpt) {
		    if (jet_dwn_cut           ) { rt::Fill2D(hc["h_mu_fo20c"], fabs(eta()), pt(), evt_weight); } 
		    if (jet_cut               ) { rt::Fill2D(hc["h_mu_fo40c"], fabs(eta()), pt(), evt_weight); } 
		    if (jet_up_cut            ) { rt::Fill2D(hc["h_mu_fo60c"], fabs(eta()), pt(), evt_weight); } 
		    if (jet_dwn_cut ) { rt::Fill( hc["h_mu_fo20c_pt"], pt(), evt_weight); }
		    if (jet_cut     ) { rt::Fill( hc["h_mu_fo40c_pt"], pt(), evt_weight); }
		    if (jet_up_cut  ) { rt::Fill( hc["h_mu_fo60c_pt"], pt(), evt_weight); }
		  }
		  else {
		    if (jet_dwn_cut           ) { rt::Fill2D(hc["h_mu_fo20c"], fabs(eta()), isNumIso ? pt() : FOpt, evt_weight); } 
		    if (jet_cut               ) { rt::Fill2D(hc["h_mu_fo40c"], fabs(eta()), isNumIso ? pt() : FOpt, evt_weight); } 
		    if (jet_up_cut            ) { rt::Fill2D(hc["h_mu_fo60c"], fabs(eta()), isNumIso ? pt() : FOpt, evt_weight); } 
		    if (jet_dwn_cut ) { rt::Fill( hc["h_mu_fo20c_pt"], isNumIso ? pt() : FOpt, evt_weight); }
		    if (jet_cut     ) { rt::Fill( hc["h_mu_fo40c_pt"], isNumIso ? pt() : FOpt, evt_weight); }
		    if (jet_up_cut  ) { rt::Fill( hc["h_mu_fo60c_pt"], isNumIso ? pt() : FOpt, evt_weight); }
		  }

		  
		  if (jet_dwn_cut ) { rt::Fill( hc["h_mu_fo20c_eta"], eta(), evt_weight); }
		  if (jet_cut     ) { rt::Fill( hc["h_mu_fo40c_eta"], eta(), evt_weight); }
		  if (jet_up_cut  ) { rt::Fill( hc["h_mu_fo60c_eta"], eta(), evt_weight); }
                }
            }

            // numerator (with iso)
            if (num_lep_sel_trig_iso)
            {
                if (iso < num_mu_iso_cut)
                {
                    if (jet_dwn_cut && pt()>5) { rt::Fill( hc["h_mu_num20c_iso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet_cut     && pt()>5) { rt::Fill( hc["h_mu_num40c_iso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet_up_cut  && pt()>5) { rt::Fill( hc["h_mu_num60c_iso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet_dwn_cut           ) { rt::Fill2D(hc["h_mu_num20c_iso"], fabs(eta()), pt(), evt_weight); } 
                    if (jet_cut               ) { rt::Fill2D(hc["h_mu_num40c_iso"], fabs(eta()), pt(), evt_weight); } 
                    if (jet_up_cut            ) { rt::Fill2D(hc["h_mu_num60c_iso"], fabs(eta()), pt(), evt_weight); } 

                    if (jet_dwn_cut ) { rt::Fill( hc["h_mu_iso_num20c_pt"], pt(), evt_weight); }
                    if (jet_cut     ) { rt::Fill( hc["h_mu_iso_num40c_pt"], pt(), evt_weight); }
                    if (jet_up_cut  ) { rt::Fill( hc["h_mu_iso_num60c_pt"], pt(), evt_weight); }

                    if (jet_dwn_cut ) { rt::Fill( hc["h_mu_iso_num20c_eta"], eta(), evt_weight); }
                    if (jet_cut     ) { rt::Fill( hc["h_mu_iso_num40c_eta"], eta(), evt_weight); }
                    if (jet_up_cut  ) { rt::Fill( hc["h_mu_iso_num60c_eta"], eta(), evt_weight); }
                }
            }

            // denominator (with iso)
            if (fo_lep_sel_trig_iso)
            {
                if (iso < den_mu_iso_cut)
                {
                    if (jet_dwn_cut && pt()>5) { rt::Fill( hc["h_mu_fo20c_iso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet_cut     && pt()>5) { rt::Fill( hc["h_mu_fo40c_iso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet_up_cut  && pt()>5) { rt::Fill( hc["h_mu_fo60c_iso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet_dwn_cut           ) { rt::Fill2D(hc["h_mu_fo20c_iso"], fabs(eta()), pt(), evt_weight); } 
                    if (jet_cut               ) { rt::Fill2D(hc["h_mu_fo40c_iso"], fabs(eta()), pt(), evt_weight); } 
                    if (jet_up_cut            ) { rt::Fill2D(hc["h_mu_fo60c_iso"], fabs(eta()), pt(), evt_weight); } 

                    if (jet_dwn_cut ) { rt::Fill( hc["h_mu_iso_fo20c_pt"], pt(), evt_weight); }
                    if (jet_cut     ) { rt::Fill( hc["h_mu_iso_fo40c_pt"], pt(), evt_weight); }
                    if (jet_up_cut  ) { rt::Fill( hc["h_mu_iso_fo60c_pt"], pt(), evt_weight); }

                    if (jet_dwn_cut ) { rt::Fill( hc["h_mu_iso_fo20c_eta"], eta(), evt_weight); }
                    if (jet_cut     ) { rt::Fill( hc["h_mu_iso_fo40c_eta"], eta(), evt_weight); }
                    if (jet_up_cut  ) { rt::Fill( hc["h_mu_iso_fo60c_eta"], eta(), evt_weight); }
                }
            }
        }


        // Electrons after MET and WmT cuts
        // ----------------------------------------------------------------------------------------------------------------------------//

        // Fill Fake Rates 
        if (m_lepton == "el")
        {
            // numerator
            if (num_lep_sel)
            {
                if (iso < num_el_iso_cut)
                {
                    if (jet_dwn_cut && pt()>20) { rt::Fill( hc["h_el_num20c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet_cut     && pt()>20) { rt::Fill( hc["h_el_num40c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet_up_cut  && pt()>20) { rt::Fill( hc["h_el_num60c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet_dwn_cut           ) { rt::Fill2D(hc["h_el_num20c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet_cut               ) { rt::Fill2D(hc["h_el_num40c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet_up_cut            ) { rt::Fill2D(hc["h_el_num60c"], fabs(eta()), pt(), evt_weight); } 

                    if (jet_dwn_cut ) { rt::Fill( hc["h_el_num20c_pt"], pt(), evt_weight); }
                    if (jet_cut     ) { rt::Fill( hc["h_el_num40c_pt"], pt(), evt_weight); }
                    if (jet_up_cut  ) { rt::Fill( hc["h_el_num60c_pt"], pt(), evt_weight); }

                    if (jet_dwn_cut ) { rt::Fill( hc["h_el_num20c_eta"], eta(), evt_weight); }
                    if (jet_cut     ) { rt::Fill( hc["h_el_num40c_eta"], eta(), evt_weight); }
                    if (jet_up_cut  ) { rt::Fill( hc["h_el_num60c_eta"], eta(), evt_weight); }
                }

            }

            // denominator 
            if (fo_lep_sel)
            {
	      // GZ // Very basic start: Plot recoil jet pT for different values of isolation
	      // Actually, easier to make 2D plot first
	      rt::Fill( hc["h_el_fo_iso"], iso, evt_weight);
	      rt::Fill( hc["h_el_fo_chiso"], chiso, evt_weight);
	      rt::Fill( hc["h_el_fo_caloiso"], caloiso, evt_weight);
	      rt::Fill( hc["h_el_fo_d0"], fabs(d0()), evt_weight);
	      if (rt::string_contains(current_file_name, "5to15_TuneZ2star")  )  rt::Fill( hc["h_el_fo_jetPt_q5_15"], ptpfcL1Fj1(), evt_weight);
	      if (rt::string_contains(current_file_name, "15to30_TuneZ2star")  ) rt::Fill( hc["h_el_fo_jetPt_q15_30"], ptpfcL1Fj1(), evt_weight);
	      if (rt::string_contains(current_file_name, "30to50_TuneZ2star")  ) rt::Fill( hc["h_el_fo_jetPt_q30_50"], ptpfcL1Fj1(), evt_weight);
	      if (rt::string_contains(current_file_name, "50to80_TuneZ2star")  ) rt::Fill( hc["h_el_fo_jetPt_q50_80"], ptpfcL1Fj1(), evt_weight);
	      if (rt::string_contains(current_file_name, "80to120_TuneZ2star") ) rt::Fill (hc["h_el_fo_jetPt_q80_120"], ptpfcL1Fj1(), evt_weight);
	      if (rt::string_contains(current_file_name, "120to170_TuneZ2star")) rt::Fill( hc["h_el_fo_jetPt_q120_170"], ptpfcL1Fj1(), evt_weight);
	      if (rt::string_contains(current_file_name, "170to300_TuneZ2star")) rt::Fill( hc["h_el_fo_jetPt_q170_300"], ptpfcL1Fj1(), evt_weight);
	      rt::Fill2D( hc["h_el_fo_iso_vs_chiso"], chiso, iso, evt_weight);
	      rt::Fill2D( hc["h_el_fo_iso_vs_caloiso"], caloiso, iso, evt_weight);
	      rt::Fill2D( hc["h_el_fo_chiso_vs_caloiso"], caloiso, chiso, evt_weight);
	      rt::Fill2D( hc["h_el_fo_iso_vs_jetPt"], ptpfcL1Fj1(), iso, evt_weight);
	      rt::Fill2D( hc["h_el_fo_chiso_vs_jetPt"], ptpfcL1Fj1(), chiso, evt_weight);
	      rt::Fill2D( hc["h_el_fo_caloiso_vs_jetPt"], ptpfcL1Fj1(), caloiso, evt_weight);
	      rt::Fill2D( hc["h_el_fo_d0_vs_jetPt"], ptpfcL1Fj1(), fabs(d0()), evt_weight);
	      
	      //TString pTisoName = h_el_fo_jetPt_iso;
	      //pTisoName += (Long_t) iso;
	      


                if (iso < den_el_iso_cut)
                {
                    if (jet_dwn_cut && pt()>20) { rt::Fill( hc["h_el_fo20c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet_cut     && pt()>20) { rt::Fill( hc["h_el_fo40c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet_up_cut  && pt()>20) { rt::Fill( hc["h_el_fo60c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet_dwn_cut           ) { rt::Fill2D(hc["h_el_fo20c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet_cut               ) { rt::Fill2D(hc["h_el_fo40c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet_up_cut            ) { rt::Fill2D(hc["h_el_fo60c"], fabs(eta()), pt(), evt_weight); } 

                    if (jet_dwn_cut ) { rt::Fill( hc["h_el_fo20c_pt"], pt(), evt_weight); }
                    if (jet_cut     ) { rt::Fill( hc["h_el_fo40c_pt"], pt(), evt_weight); }
                    if (jet_up_cut  ) { rt::Fill( hc["h_el_fo60c_pt"], pt(), evt_weight); }

                    if (jet_dwn_cut ) { rt::Fill( hc["h_el_fo20c_eta"], eta(), evt_weight); }
                    if (jet_cut     ) { rt::Fill( hc["h_el_fo40c_eta"], eta(), evt_weight); }
                    if (jet_up_cut  ) { rt::Fill( hc["h_el_fo60c_eta"], eta(), evt_weight); }
                }
            }

            if (num_lep_sel_trig_noiso)
            {

                if (iso < num_el_iso_cut)
                {
                    if (jet_dwn_cut && pt()>10) { rt::Fill( hc["h_el_num20c_noiso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet_cut     && pt()>10) { rt::Fill( hc["h_el_num40c_noiso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet_up_cut  && pt()>10) { rt::Fill( hc["h_el_num60c_noiso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet_dwn_cut           ) { rt::Fill2D(hc["h_el_num20c_noiso"], fabs(eta()), pt(), evt_weight); } 
                    if (jet_cut               ) { rt::Fill2D(hc["h_el_num40c_noiso"], fabs(eta()), pt(), evt_weight); } 
                    if (jet_up_cut            ) { rt::Fill2D(hc["h_el_num60c_noiso"], fabs(eta()), pt(), evt_weight); } 

                    if (jet_dwn_cut ) { rt::Fill( hc["h_el_noiso_num20c_pt"], pt(), evt_weight); }
                    if (jet_cut     ) { rt::Fill( hc["h_el_noiso_num40c_pt"], pt(), evt_weight); }
                    if (jet_up_cut  ) { rt::Fill( hc["h_el_noiso_num60c_pt"], pt(), evt_weight); }

                    if (jet_dwn_cut ) { rt::Fill( hc["h_el_noiso_num20c_eta"], eta(), evt_weight); }
                    if (jet_cut     ) { rt::Fill( hc["h_el_noiso_num40c_eta"], eta(), evt_weight); }
                    if (jet_up_cut  ) { rt::Fill( hc["h_el_noiso_num60c_eta"], eta(), evt_weight); }
                }
            }

            // denominator 
            if (fo_lep_sel_trig_noiso)
            {
                if (iso < den_el_iso_cut)
                {
                    if (jet_dwn_cut && pt()>10) { rt::Fill( hc["h_el_fo20c_noiso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet_cut     && pt()>10) { rt::Fill( hc["h_el_fo40c_noiso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet_up_cut  && pt()>10) { rt::Fill( hc["h_el_fo60c_noiso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet_dwn_cut           ) { rt::Fill2D(hc["h_el_fo20c_noiso"], fabs(eta()), pt(), evt_weight); } 
                    if (jet_cut               ) { rt::Fill2D(hc["h_el_fo40c_noiso"], fabs(eta()), pt(), evt_weight); } 
                    if (jet_up_cut            ) { rt::Fill2D(hc["h_el_fo60c_noiso"], fabs(eta()), pt(), evt_weight); } 

                    if (jet_dwn_cut ) { rt::Fill( hc["h_el_noiso_fo20c_pt"], pt(), evt_weight); }
                    if (jet_cut     ) { rt::Fill( hc["h_el_noiso_fo40c_pt"], pt(), evt_weight); }
                    if (jet_up_cut  ) { rt::Fill( hc["h_el_noiso_fo60c_pt"], pt(), evt_weight); }

                    if (jet_dwn_cut ) { rt::Fill( hc["h_el_noiso_fo20c_eta"], eta(), evt_weight); }
                    if (jet_cut     ) { rt::Fill( hc["h_el_noiso_fo40c_eta"], eta(), evt_weight); }
                    if (jet_up_cut  ) { rt::Fill( hc["h_el_noiso_fo60c_eta"], eta(), evt_weight); }
                }
            }
        }

    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
    }

    // analysis end
    return 0;
} 
