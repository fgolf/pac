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
    float lumi,
    int charge, 
    bool verbose,
    bool print,
    const std::string& suffix
    )
    : at::AnalysisWithHist(root_file_name, print, suffix)
    , m_sample(sample)
    , m_lepton(lepton)
    , m_lumi(lumi)
    , m_charge(charge)
    , m_verbose(verbose)
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
    const float eff_area = fastJetEffArea03_v2(eta()); 
    return (ch_pfiso03() + max(0.0f, nh_pfiso03() + em_pfiso03() - (max(0.0f, rho())*eff_area)))/pt();
}

float pfiso03_corr_dB()
{
    using namespace frb;
    return (ch_pfiso03() + max(0.0f, nh_pfiso03() + em_pfiso03() - (0.5f*pfpupt03())))/pt();
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

        // FR(# vertices)
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num20c_iso_vs_nvtxs"],hc["h_mu_fo20c_iso_vs_nvtxs"], "h_mufr20c_iso_vs_nvtxs", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 20, p_{T} > 20, iso);# vtxs"));
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num40c_iso_vs_nvtxs"],hc["h_mu_fo40c_iso_vs_nvtxs"], "h_mufr40c_iso_vs_nvtxs", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 40, p_{T} > 20, iso);# vtxs"));
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num60c_iso_vs_nvtxs"],hc["h_mu_fo60c_iso_vs_nvtxs"], "h_mufr60c_iso_vs_nvtxs", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 60, p_{T} > 20, iso);# vtxs"));

        // FR(pt)
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num20c_iso"],hc["h_mu_fo20c_iso"], "y", "h_mufr20c_iso_vs_pt", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 20, iso);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num40c_iso"],hc["h_mu_fo40c_iso"], "y", "h_mufr40c_iso_vs_pt", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 40, iso);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num60c_iso"],hc["h_mu_fo60c_iso"], "y", "h_mufr60c_iso_vs_pt", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 60, iso);p_{T}"));
                                                                                                                                                      
        // FR(eta)
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num20c_iso"],hc["h_mu_fo20c_iso"], "x", "h_mufr20c_iso_vs_eta", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 20, p_{T} > 20, iso);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num40c_iso"],hc["h_mu_fo40c_iso"], "x", "h_mufr40c_iso_vs_eta", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 40, p_{T} > 20, iso);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num60c_iso"],hc["h_mu_fo60c_iso"], "x", "h_mufr60c_iso_vs_eta", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 60, p_{T} > 20, iso);|#eta|", 20, 100));

        // FR(eta, pT)
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num20c_iso"],hc["h_mu_fo20c_iso"], "h_mufr20c_iso", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 20, iso);|#eta|;p_{T} (GeV)"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num40c_iso"],hc["h_mu_fo40c_iso"], "h_mufr40c_iso", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 40, iso);|#eta|;p_{T} (GeV)"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num60c_iso"],hc["h_mu_fo60c_iso"], "h_mufr60c_iso", "#mu FR cpfiso03 #Delta#beta (0.1, 0.4) (away jet p_{T} > 60, iso);|#eta|;p_{T} (GeV)"));
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

        // FR(# vertices)
        hc.Add(rt::MakeEfficiencyPlot(hc["h_el_num20c_noiso_vs_nvtxs"],hc["h_el_fo20c_noiso_vs_nvtxs"], "h_elfr20c_noiso_vs_nvtxs", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 20, p_{T}>20, no iso);# vtxs"));
        hc.Add(rt::MakeEfficiencyPlot(hc["h_el_num40c_noiso_vs_nvtxs"],hc["h_el_fo40c_noiso_vs_nvtxs"], "h_elfr40c_noiso_vs_nvtxs", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40, p_{T}>20, no iso);# vtxs"));
        hc.Add(rt::MakeEfficiencyPlot(hc["h_el_num60c_noiso_vs_nvtxs"],hc["h_el_fo60c_noiso_vs_nvtxs"], "h_elfr60c_noiso_vs_nvtxs", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 60, p_{T}>20, no iso);# vtxs"));

        // FR(pt)
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num20c_noiso"],hc["h_el_fo20c_noiso"], "y", "h_elfr20c_noiso_vs_pt", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 20, no iso);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num40c_noiso"],hc["h_el_fo40c_noiso"], "y", "h_elfr40c_noiso_vs_pt", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40, no iso);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num60c_noiso"],hc["h_el_fo60c_noiso"], "y", "h_elfr60c_noiso_vs_pt", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 60, no iso);p_{T}"));
                                                                                                                                                      
        // FR(eta)
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num20c_noiso"],hc["h_el_fo20c_noiso"], "x", "h_elfr20c_noiso_vs_eta", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 20, p_{T}>20, no iso);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num40c_noiso"],hc["h_el_fo40c_noiso"], "x", "h_elfr40c_noiso_vs_eta", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40, p_{T}>20, no iso);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num60c_noiso"],hc["h_el_fo60c_noiso"], "x", "h_elfr60c_noiso_vs_eta", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 60, p_{T}>20, no iso);|#eta|", 20, 100));

        // FR(eta, pT)
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_el_num20c_noiso"],hc["h_el_fo20c_noiso"], "h_elfr20c_noiso", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 20, no iso);|#eta|;p_{T} (GeV)"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_el_num40c_noiso"],hc["h_el_fo40c_noiso"], "h_elfr40c_noiso", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40, no iso);|#eta|;p_{T} (GeV)"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_el_num60c_noiso"],hc["h_el_fo60c_noiso"], "h_elfr60c_noiso", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 60, no iso);|#eta|;p_{T} (GeV)"));
    }

    //if (m_verbose)
    {
        hc.List();
    }

}

// binning contants
std::tr1::array<float, 9> el_vtx_bins = {{ 0.0,  3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0, 30.0}};
std::tr1::array<float, 5> el_eta_bins = {{0.0, 1.0, 1.479, 2.0, 2.5}};
std::tr1::array<float, 9> mu_vtx_bins = {{ 0.0,  3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0, 30.0}};
std::tr1::array<float, 5> mu_eta_bins = {{0.0, 1.0, 1.479, 2.0, 2.5}};
std::tr1::array<float, 6> mu_pt_bins  = {{ 5.0, 10.0, 15.0, 20.0, 25.0, 35.0}};
std::tr1::array<float, 6> el_pt_bins  = {{10.0, 15.0, 20.0, 25.0, 35.0, 55.0}};

// book hists 
void FakeRateBabyLooper::BookHists()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    // muons
    // --------------------------------------------------------------------------------------------------------------------------- //
    
    // muon FR vs # vertices 
    if (m_lepton == "mu")
    {
        //int   mu_vtx_bin = 10;
        //float mu_vtx_min = 0;
        //float mu_vtx_max = 30;

        // numerator
        hc.Add(new TH1F("h_mu_num20c_vs_nvtxs", "num #mu (away jet p_{T} > 20, cpfiso03 < 0.1 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_num40c_vs_nvtxs", "num #mu (away jet p_{T} > 40, cpfiso03 < 0.1 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_num60c_vs_nvtxs", "num #mu (away jet p_{T} > 60, cpfiso03 < 0.1 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");

        hc.Add(new TH2F("h_mu_num20c", "num #mu (away jet p_{T} > 20, cpfiso03 < 0.1 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_num40c", "num #mu (away jet p_{T} > 40, cpfiso03 < 0.1 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_num60c", "num #mu (away jet p_{T} > 60, cpfiso03 < 0.1 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");

        // denominator
        hc.Add(new TH1F("h_mu_fo20c_vs_nvtxs", "fo #mu (away jet p_{T} > 20, cpfiso03 < 0.4 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_fo40c_vs_nvtxs", "fo #mu (away jet p_{T} > 40, cpfiso03 < 0.4 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_fo60c_vs_nvtxs", "fo #mu (away jet p_{T} > 60, cpfiso03 < 0.4 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");

        hc.Add(new TH2F("h_mu_fo20c", "fo #mu (away jet p_{T} > 20, cpfiso03 < 0.4 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_fo40c", "fo #mu (away jet p_{T} > 40, cpfiso03 < 0.4 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_fo60c", "fo #mu (away jet p_{T} > 60, cpfiso03 < 0.4 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");

        // numerator (iso)
        hc.Add(new TH1F("h_mu_num20c_iso_vs_nvtxs", "num #mu (away jet p_{T} > 20, cpfiso03 < 0.1 (#Delta#beta), iso);# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_num40c_iso_vs_nvtxs", "num #mu (away jet p_{T} > 40, cpfiso03 < 0.1 (#Delta#beta), iso);# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_num60c_iso_vs_nvtxs", "num #mu (away jet p_{T} > 60, cpfiso03 < 0.1 (#Delta#beta), iso);# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");

        hc.Add(new TH2F("h_mu_num20c_iso", "num #mu (away jet p_{T} > 20, cpfiso03 < 0.1 (#Delta#beta), iso);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_num40c_iso", "num #mu (away jet p_{T} > 40, cpfiso03 < 0.1 (#Delta#beta), iso);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_num60c_iso", "num #mu (away jet p_{T} > 60, cpfiso03 < 0.1 (#Delta#beta), iso);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");

        // denominator (iso)
        hc.Add(new TH1F("h_mu_fo20c_iso_vs_nvtxs", "fo #mu (away jet p_{T} > 20, cpfiso03 < 0.4 (#Delta#beta), iso);# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_fo40c_iso_vs_nvtxs", "fo #mu (away jet p_{T} > 40, cpfiso03 < 0.4 (#Delta#beta), iso);# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_fo60c_iso_vs_nvtxs", "fo #mu (away jet p_{T} > 60, cpfiso03 < 0.4 (#Delta#beta), iso);# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");

        hc.Add(new TH2F("h_mu_fo20c_iso", "fo #mu (away jet p_{T} > 20, cpfiso03 < 0.4 (#Delta#beta), iso);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_fo40c_iso", "fo #mu (away jet p_{T} > 40, cpfiso03 < 0.4 (#Delta#beta), iso);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_fo60c_iso", "fo #mu (away jet p_{T} > 60, cpfiso03 < 0.4 (#Delta#beta), iso);|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
    }

    // electrons
    // --------------------------------------------------------------------------------------------------------------------------- //
    
    // electron FR vs # vertices 
    if (m_lepton == "el")
    {
        //int   el_vtx_bin = 10;
        //float el_vtx_min = 0;
        //float el_vtx_max = 30;

        // numerator
        hc.Add(new TH1F("h_el_num20c_vs_nvtxs", "num electron (away jet p_{T} > 20, cpfiso03 < 0.09 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_el_num40c_vs_nvtxs", "num electron (away jet p_{T} > 40, cpfiso03 < 0.09 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_el_num60c_vs_nvtxs", "num electron (away jet p_{T} > 60, cpfiso03 < 0.09 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");

        hc.Add(new TH2F("h_el_num20c", "num electron (away jet p_{T} > 20, cpfiso03 < 0.09 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_el_num40c", "num electron (away jet p_{T} > 40, cpfiso03 < 0.09 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_el_num60c", "num electron (away jet p_{T} > 60, cpfiso03 < 0.09 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");

        // denominator
        hc.Add(new TH1F("h_el_fo20c_vs_nvtxs", "fo electron (away jet p_{T} > 20, cpfiso03 < 0.6 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_el_fo40c_vs_nvtxs", "fo electron (away jet p_{T} > 40, cpfiso03 < 0.6 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_el_fo60c_vs_nvtxs", "fo electron (away jet p_{T} > 60, cpfiso03 < 0.6 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");

        hc.Add(new TH2F("h_el_fo20c", "fo electron (away jet p_{T} > 20, cpfiso03 < 0.6 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_el_fo40c", "fo electron (away jet p_{T} > 40, cpfiso03 < 0.6 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_el_fo60c", "fo electron (away jet p_{T} > 60, cpfiso03 < 0.6 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");

        // numerator (no iso)
        hc.Add(new TH1F("h_el_num20c_noiso_vs_nvtxs", "num electron (away jet p_{T} > 20, no iso, cpfiso03 < 0.09 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_el_num40c_noiso_vs_nvtxs", "num electron (away jet p_{T} > 40, no iso, cpfiso03 < 0.09 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_el_num60c_noiso_vs_nvtxs", "num electron (away jet p_{T} > 60, no iso, cpfiso03 < 0.09 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");

        hc.Add(new TH2F("h_el_num20c_noiso", "num electron (away jet p_{T} > 20, no iso, cpfiso03 < 0.09 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_el_num40c_noiso", "num electron (away jet p_{T} > 40, no iso, cpfiso03 < 0.09 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_el_num60c_noiso", "num electron (away jet p_{T} > 60, no iso, cpfiso03 < 0.09 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");

        // denominator (no iso)
        hc.Add(new TH1F("h_el_fo20c_noiso_vs_nvtxs", "fo electron (away jet p_{T} > 20, no iso, cpfiso03 < 0.6 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_el_fo40c_noiso_vs_nvtxs", "fo electron (away jet p_{T} > 40, no iso, cpfiso03 < 0.6 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_el_fo60c_noiso_vs_nvtxs", "fo electron (away jet p_{T} > 60, no iso, cpfiso03 < 0.6 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");

        hc.Add(new TH2F("h_el_fo20c_noiso", "fo electron (away jet p_{T} > 20, no iso, cpfiso03 < 0.6 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_el_fo40c_noiso", "fo electron (away jet p_{T} > 40, no iso, cpfiso03 < 0.6 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_el_fo60c_noiso", "fo electron (away jet p_{T} > 60, no iso, cpfiso03 < 0.6 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");
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
        const bool is_mu    = ((m_lepton=="mu") ? abs(id())==13 : false);
        const bool is_el    = ((m_lepton=="el") ? abs(id())==11 : false);

        // qcd muon cuts (for the different qcd samples)
        const bool qcd_mu_low  = rt::string_contains(current_file_name, "MuEnrichedPt5"  ) && pt() < 16.0; 
        const bool qcd_mu_high = rt::string_contains(current_file_name, "MuEnrichedPt_15") && pt() >= 16.0; 
        if (is_mu && is_qcd && not (qcd_mu_low || qcd_mu_high))
        {
            return 0;
        }

        // check the charge
        switch (m_charge)
        {
            case  1: if (id()>0) {return 0;} break; // 11/13   --> e-/mu- (reject)
            case -1: if (id()<0) {return 0;} break; // -11/-13 --> e+/mu+ (reject)
            case  0: /*do nothing*/ break;
            default: /*do nothing*/ break;
        };

        // pT cut
        if (is_mu && (pt()<5 || pt()>35))
        {
            if (m_verbose) {cout << "fails pt cut" << endl;}
            return 0;
        }
        if (is_el && (pt()<10 || pt()>55))
        {
            if (m_verbose) {cout << "fails pt cut" << endl;}
            return 0;
        }

        // eta cut
        if (fabs(eta()) > 2.4)
        {
            if (m_verbose) {cout << "fails eta cut" << endl;}
            return 0;
        }

        // no W (MET and m_T cuts)
        if (pfmet()>20 || pfmt()>25)
        {
            if (m_verbose) {cout << "fails no W cut" << endl;}
            return 0;
        }

        // no resonance's (Z or upsilon)
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

        // trigger cuts
        bool trig_cut       = (is_data ? false : true);
        bool trig_cut_noiso = (is_data ? false : true);  // electron non-isolated triggers
        bool trig_cut_iso   = (is_data ? false : true);  // muon isolated triggers
        if (is_data && is_mu)
        {
            // trigger without isolation
            trig_cut = ((pt() > 30 && (mu30_eta2p1_vstar() > 1 || mu24_eta2p1_vstar() > 1 || mu17_vstar()>1 || mu8_vstar()>1)) || 
                        (pt() > 24 && (mu24_eta2p1_vstar() > 1 || mu17_vstar()>1 || mu8_vstar()>1)) || 
                        (pt() > 17 && (mu17_vstar()>1 || mu8_vstar()>1)) || 
                        (pt() > 8  && (mu8_vstar()>1)));

            // trigger with isolaiont
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

        // no additional FO's in event
        bool nFOcut = false;
        if (is_mu)
        {
            nFOcut = (nFOmus() == 0);
        }
        else if(is_el)
        {
            nFOcut = (nFOels() == 0);
        }

        // away jet cut
        bool jet20c_cut = is_data ? (ptpfcL1Fj1res() > 20) : (ptpfcL1Fj1() > 20);
        bool jet40c_cut = is_data ? (ptpfcL1Fj1res() > 40) : (ptpfcL1Fj1() > 40);
        bool jet60c_cut = is_data ? (ptpfcL1Fj1res() > 60) : (ptpfcL1Fj1() > 60);
        //if (not is_data)
        if (is_ttbar)
        {
            jet20c_cut = true;
            jet40c_cut = true;
            jet60c_cut = true;
        }

        // numerator cut
        bool num_lep_cut = false;
        if (is_mu)
        {
            num_lep_cut = num_mu_ssV5_noIso();
            //num_lep_cut = (num_mu_ssV5_noIso() && (fabs(d0()) < 0.005));
        }
        else if(is_el)
        {
            num_lep_cut = num_el_ssV7_noIso();
            //num_lep_cut = (num_el_ssV7_noIso() && (fabs(d0()) < 0.010));
        }

        // denominator cut
        bool fo_lep_cut = false;
        if (is_mu)
        {
            fo_lep_cut = fo_mu_ssV5_noIso();
        }
        else if(is_el)
        {
            fo_lep_cut = v3_el_ssV7();
        }

        // not for W
        bool not_fromw = is_ttbar ? leptonIsFromW()<1 : true;

        // passes selection (no isolaiton)
        bool num_lep_sel_notrig     = (nFOcut && num_lep_cut && not_fromw);
        bool fo_lep_sel_notrig      = (nFOcut && fo_lep_cut && not_fromw);
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
        float evt_weight = (weight() * m_lumi);
        //float evt_weight = 1.0; 

        // isolation
        float iso = ((m_lepton == "mu") ? cpfiso03_db() : pfiso03_corr_rho()); // new effective area
        //float iso = ((m_lepton == "mu") ? cpfiso03_db() : cpfiso03_rho());  // old effective area

        // muons
        // ----------------------------------------------------------------------------------------------------------------------------//

        // Fill Fake Rates 
        if (m_lepton == "mu")
        {
            // numerator
            if (num_lep_sel)
            {
                if (iso < 0.1)
                {
                    if (jet20c_cut && pt()>20) { rt::Fill( hc["h_mu_num20c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet40c_cut && pt()>20) { rt::Fill( hc["h_mu_num40c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet60c_cut && pt()>20) { rt::Fill( hc["h_mu_num60c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet20c_cut           ) { rt::Fill2D(hc["h_mu_num20c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet40c_cut           ) { rt::Fill2D(hc["h_mu_num40c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet60c_cut           ) { rt::Fill2D(hc["h_mu_num60c"], fabs(eta()), pt(), evt_weight); } 
                }
            }

            // denominator
            if (fo_lep_sel)
            {
                if (iso < 0.4)
                {
                    if (jet20c_cut && pt()>20) { rt::Fill( hc["h_mu_fo20c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet40c_cut && pt()>20) { rt::Fill( hc["h_mu_fo40c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet60c_cut && pt()>20) { rt::Fill( hc["h_mu_fo60c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet20c_cut           ) { rt::Fill2D(hc["h_mu_fo20c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet40c_cut           ) { rt::Fill2D(hc["h_mu_fo40c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet60c_cut           ) { rt::Fill2D(hc["h_mu_fo60c"], fabs(eta()), pt(), evt_weight); } 
                }
            }

            // numerator (with iso)
            if (num_lep_sel_trig_iso)
            {
                if (iso < 0.1)
                {
                    if (jet20c_cut && pt()>20) { rt::Fill( hc["h_mu_num20c_iso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet40c_cut && pt()>20) { rt::Fill( hc["h_mu_num40c_iso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet60c_cut && pt()>20) { rt::Fill( hc["h_mu_num60c_iso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet20c_cut           ) { rt::Fill2D(hc["h_mu_num20c_iso"], fabs(eta()), pt(), evt_weight); } 
                    if (jet40c_cut           ) { rt::Fill2D(hc["h_mu_num40c_iso"], fabs(eta()), pt(), evt_weight); } 
                    if (jet60c_cut           ) { rt::Fill2D(hc["h_mu_num60c_iso"], fabs(eta()), pt(), evt_weight); } 
                }
            }

            // denominator (with iso)
            if (fo_lep_sel_trig_iso)
            {
                if (iso < 0.4)
                {
                    if (jet20c_cut && pt()>20) { rt::Fill( hc["h_mu_fo20c_iso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet40c_cut && pt()>20) { rt::Fill( hc["h_mu_fo40c_iso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet60c_cut && pt()>20) { rt::Fill( hc["h_mu_fo60c_iso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (m_verbose) {cout << "passing lepton" << endl;}
                    if (jet20c_cut           ) { rt::Fill2D(hc["h_mu_fo20c_iso"], fabs(eta()), pt(), evt_weight); } 
                    if (jet40c_cut           ) { rt::Fill2D(hc["h_mu_fo40c_iso"], fabs(eta()), pt(), evt_weight); } 
                    if (jet60c_cut           ) { rt::Fill2D(hc["h_mu_fo60c_iso"], fabs(eta()), pt(), evt_weight); } 
                }
            }
        }


        // Electrons
        // ----------------------------------------------------------------------------------------------------------------------------//

        // Fill Fake Rates 
        if (m_lepton == "el")
        {
            // numerator
            if (num_lep_sel)
            {
                if (iso < 0.09)
                {
                    if (jet20c_cut && pt()>20) { rt::Fill( hc["h_el_num20c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet40c_cut && pt()>20) { rt::Fill( hc["h_el_num40c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet60c_cut && pt()>20) { rt::Fill( hc["h_el_num60c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet20c_cut           ) { rt::Fill2D(hc["h_el_num20c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet40c_cut           ) { rt::Fill2D(hc["h_el_num40c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet60c_cut           ) { rt::Fill2D(hc["h_el_num60c"], fabs(eta()), pt(), evt_weight); } 
                }
            }

            // denominator 
            if (fo_lep_sel)
            {
                if (iso < 0.6)
                {
                    if (jet20c_cut && pt()>20) { rt::Fill( hc["h_el_fo20c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet40c_cut && pt()>20) { rt::Fill( hc["h_el_fo40c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet60c_cut && pt()>20) { rt::Fill( hc["h_el_fo60c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet20c_cut           ) { rt::Fill2D(hc["h_el_fo20c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet40c_cut           ) { rt::Fill2D(hc["h_el_fo40c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet60c_cut           ) { rt::Fill2D(hc["h_el_fo60c"], fabs(eta()), pt(), evt_weight); } 
                }
            }

            if (num_lep_sel_trig_noiso)
            {

                if (iso < 0.09)
                {
                    if (jet20c_cut && pt()>20) { rt::Fill( hc["h_el_num20c_noiso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet40c_cut && pt()>20) { rt::Fill( hc["h_el_num40c_noiso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet60c_cut && pt()>20) { rt::Fill( hc["h_el_num60c_noiso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet20c_cut           ) { rt::Fill2D(hc["h_el_num20c_noiso"], fabs(eta()), pt(), evt_weight); } 
                    if (jet40c_cut           ) { rt::Fill2D(hc["h_el_num40c_noiso"], fabs(eta()), pt(), evt_weight); } 
                    if (jet60c_cut           ) { rt::Fill2D(hc["h_el_num60c_noiso"], fabs(eta()), pt(), evt_weight); } 
                }
            }

            // denominator 
            if (fo_lep_sel_trig_noiso)
            {
                if (iso < 0.6)
                {
                    if (jet20c_cut && pt()>20) { rt::Fill( hc["h_el_fo20c_noiso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet40c_cut && pt()>20) { rt::Fill( hc["h_el_fo40c_noiso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet60c_cut && pt()>20) { rt::Fill( hc["h_el_fo60c_noiso_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet20c_cut           ) { rt::Fill2D(hc["h_el_fo20c_noiso"], fabs(eta()), pt(), evt_weight); } 
                    if (jet40c_cut           ) { rt::Fill2D(hc["h_el_fo40c_noiso"], fabs(eta()), pt(), evt_weight); } 
                    if (jet60c_cut           ) { rt::Fill2D(hc["h_el_fo60c_noiso"], fabs(eta()), pt(), evt_weight); } 
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
