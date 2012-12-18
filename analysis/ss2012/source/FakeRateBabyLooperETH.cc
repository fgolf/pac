#include "FakeRateBaby.h"
#include "FakeRateBabyLooperETH.h"
#include "mcSelections.h"
#include "rt/RootTools.h"
#include <iostream>
#include <algorithm>
#include <tr1/array>
#include <cmath>

typedef std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > vecLorentzVector;

// construct:
FakeRateBabyLooperETH::FakeRateBabyLooperETH
(
    const std::string& root_file_name,
    const std::string& dataset,
    const std::string& lepton,
    float lumi,
    int charge, 
    bool verbose,
    bool print,
    const std::string& suffix
    )
    : at::AnalysisWithHist(root_file_name, print, suffix)
    , m_dataset(dataset)
    , m_lepton(lepton)
    , m_lumi(lumi)
    , m_charge(charge)
{
    // begin job
    BeginJob();
}

// destroy:
FakeRateBabyLooperETH::~FakeRateBabyLooperETH()
{
    // end  job
    EndJob();
}

// methods:
void FakeRateBabyLooperETH::BeginJob()
{
    BookHists();
}

// selection functions (to be moved to another file maybe)
float isocorr()
{
    using namespace frb;
    return iso() - ((log(pt()) * evt_nvtxs())/(30 * pt())); 
}

float pfiso03_corr()
{
    using namespace frb;
    return pfiso03() - ((log(pt()) * evt_nvtxs())/(75 * pt())); 
}

float pfiso03_rho()
{
    using namespace frb;
    return (ch_pfiso03() + max(0.0f, nh_pfiso03() + em_pfiso03() - (max(0.0f, rho())*el_effarea())))/pt();
}

float pfiso03_dB()
{
    using namespace frb;
    return (ch_pfiso03() + max(0.0f, nh_pfiso03() + em_pfiso03() - (0.5f*pfpupt03())))/pt();
}

bool passesETHdenomNoIso ()
{
    using namespace frb;
    if (!num_mu_ssV5_noIso()) return false;
    // if (fabs(d0PV_wwV1()) > 0.02) return false;
    // if (mu_nchi2() > 10.) return false;
    // if (mu_ecal_veto_dep() > 4) return false;
    // if (mu_hcal_veto_dep() > 6) return false;
    return true;
}

// end job
void FakeRateBabyLooperETH::EndJob()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    // muons
    if (m_lepton == "mu")
    {   
        // FR(# vertices)
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num20c_vs_nvtxs"],hc["h_mu_fo20c_vs_nvtxs"], "h_mufr30c_vs_nvtxs", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 30, p_{T} > 20);# vtxs"));
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num40c_vs_nvtxs"],hc["h_mu_fo40c_vs_nvtxs"], "h_mufr50c_vs_nvtxs", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 50, p_{T} > 20);# vtxs"));
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num60c_vs_nvtxs"],hc["h_mu_fo60c_vs_nvtxs"], "h_mufr70c_vs_nvtxs", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 70, p_{T} > 20);# vtxs"));

        // FR(pt)
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num20c"],hc["h_mu_fo20c"], "y", "h_mufr20c_vs_pt", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 30);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num40c"],hc["h_mu_fo40c"], "y", "h_mufr40c_vs_pt", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 50);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num60c"],hc["h_mu_fo60c"], "y", "h_mufr60c_vs_pt", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 70);p_{T}"));
                                                                                                                                                      
        // FR(eta)
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num20c"],hc["h_mu_fo20c"], "x", "h_mufr20c_vs_eta", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 30, p_{T} > 20);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num40c"],hc["h_mu_fo40c"], "x", "h_mufr40c_vs_eta", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 50, p_{T} > 20);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num60c"],hc["h_mu_fo60c"], "x", "h_mufr60c_vs_eta", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 70, p_{T} > 20);|#eta|", 20, 100));

        // FR(eta, pT)
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num20c"],hc["h_mu_fo20c"], "h_mufr20c", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 30);|#eta|;p_{T} (GeV)"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num40c"],hc["h_mu_fo40c"], "h_mufr40c", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 50);|#eta|;p_{T} (GeV)"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num60c"],hc["h_mu_fo60c"], "h_mufr60c", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 70);|#eta|;p_{T} (GeV)"));
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
    }

    //if (m_verbose)
    {
        hc.List();
    }

}

// binning contants
std::tr1::array<float, 9>  el_vtx_bins = {{ 0.0,  3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0, 30.0}};
std::tr1::array<float, 5>  el_eta_bins = {{0.0, 1.0, 1.479, 2.0, 2.5}};
std::tr1::array<float, 9>  mu_vtx_bins = {{ 0.0,  3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0, 30.0}};
std::tr1::array<float, 6>  mu_eta_bins = {{0.0, 0.5, 1.0, 1.5, 2.0, 2.5}};
//std::tr1::array<float, 10> mu_pt_bins  = {{5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 50.0, 60.0}};
std::tr1::array<float, 7> mu_pt_bins  = {{20.0, 25.0, 30.0, 35.0, 40.0, 50.0, 60.0}};
std::tr1::array<float, 6>  el_pt_bins  = {{10.0, 15.0, 20.0, 25.0, 35.0, 55.0}};

// book hists 
void FakeRateBabyLooperETH::BookHists()
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
        hc.Add(new TH1F("h_mu_num20c_vs_nvtxs", "num #mu (away jet p_{T} > 30, cpfiso03 < 0.1 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_num40c_vs_nvtxs", "num #mu (away jet p_{T} > 50, cpfiso03 < 0.1 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_num60c_vs_nvtxs", "num #mu (away jet p_{T} > 70, cpfiso03 < 0.1 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");

        hc.Add(new TH2F("h_mu_num20c", "num #mu (away jet p_{T} > 30, cpfiso03 < 0.1 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_num40c", "num #mu (away jet p_{T} > 50, cpfiso03 < 0.1 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_num60c", "num #mu (away jet p_{T} > 70, cpfiso03 < 0.1 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");

        // denominator
        hc.Add(new TH1F("h_mu_fo20c_vs_nvtxs", "fo #mu (away jet p_{T} > 30, cpfiso03 < 1.0 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_fo40c_vs_nvtxs", "fo #mu (away jet p_{T} > 50, cpfiso03 < 1.0 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_fo60c_vs_nvtxs", "fo #mu (away jet p_{T} > 70, cpfiso03 < 1.0 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");

        hc.Add(new TH2F("h_mu_fo20c", "fo #mu (away jet p_{T} > 30, cpfiso03 < 1.0 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_fo40c", "fo #mu (away jet p_{T} > 50, cpfiso03 < 1.0 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_fo60c", "fo #mu (away jet p_{T} > 70, cpfiso03 < 1.0 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
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
    }

    hc.Sumw2();
    return;
}

// main analysis function operator 
int FakeRateBabyLooperETH::operator()(long event)
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
        //
        // which dataset
        bool is_data = rt::string_contains(m_dataset, "data");
        bool is_mu = (m_lepton=="mu") ? abs(id())==13 : false;
        bool is_el = (m_lepton=="el") ? abs(id())==11 : false;

        // quit for these runs 
        //if (run() > 202016) // just for preapproval for HCP
        //{
        //    return 0;
        //}
        
        // check the charge
        switch (m_charge)
        {
        case  1: if (id()>0) {return 0;} break; // 11/13   --> e-/mu- (reject)
        case -1: if (id()<0) {return 0;} break; // -11/-13 --> e+/mu+ (reject)
        case  0: /* do nothing*/ break;
        default: /*do nothing*/ break;
        };

        // pT cut
        if (is_mu && (pt()<20 || pt()>60))
        {
            return 0;
        }
        if (is_el && (pt()<20 || pt()>55))
        {
            return 0;
        }

        // eta cut
        if (fabs(eta()) > 2.4)
        {
            return 0;
        }

        // no W (MET and m_T cuts)
        if (pfmet()>20 || pfmt()>20)
        {
            return 0;
        }

        // no additional loose leptons
        // if (nFOmus() > 0 || nFOels() > 0)
        // {
        //     return 0;
        // }
        // if (is_mu && ((76<mz_fo_ctf() && mz_fo_ctf()<106) || (8<mupsilon_fo_mu() && mupsilon_fo_mu()>12)))
        // {
        //     return 0;
        // }
        // else if (is_el && (76<mz_fo_gsf() && mz_fo_gsf()<106))
        // {
        //     return 0;
        // }

        // trigger cuts
        bool trig_cut = false;
        if (is_data && is_mu)
        {
            //trig_cut = ((pt() > 30 && (mu15_eta2p1_vstar() > 1 || mu24_eta2p1_vstar() > 1 || mu30_eta2p1_vstar() > 1)) || 
            //            (pt() > 24 && (mu15_eta2p1_vstar() > 1 || mu24_eta2p1_vstar() > 1)) || 
            //            (pt() > 15 && mu15_eta2p1_vstar() > 1) ||
            //            (pt() > 8  && mu8_vstar() > 1));
            trig_cut = (mu17_vstar()>0 || mu8_vstar()>0);
        }
        else if(is_data && is_el)
        {
            //trig_cut = ((pt() > 17 && (ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()>1 || ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()>1   || 
            //ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()>1 ||  ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()>1)) ||
            //(pt() > 8  && (ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()>1  || ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()>1)));
            trig_cut =  (pt() > 17 && (ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar() > 1 || ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar() > 1 ||
                                       ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()  > 1 || ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()  > 1 ));
            trig_cut |= (pt() > 8  && (ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()  > 1 || ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()  > 1 ));
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
        bool jet30c_cut = (ptpfcL1Fj1res() > 30);
        // bool jet50c_cut = (ptpfcL1Fj1res() > 50);
        bool jet50c_cut = (npfc50L1Fj1_eth() > 0);
        bool jet70c_cut = (ptpfcL1Fj1res() > 70);

        // numerator cut
        bool num_lep_cut = false;
        if (is_mu)
        {
            num_lep_cut = (abs(id()) == 13 && num_mu_ssV5_noIso());
        }
        else if(is_el)
        {
            num_lep_cut = (abs(id()) == 11 && num_el_ssV7_noIso());
        }

        // denominator cut
        bool fo_lep_cut = false;
        if (is_mu)
        {
            fo_lep_cut = (abs(id()) == 13 && passesETHdenomNoIso());
        }
        else if(is_el)
        {
            fo_lep_cut = (abs(id()) == 11 && v3_el_ssV7());
        }

        // passes selection (no isolation)
        bool num_lep_sel_notrig = (nFOcut && num_lep_cut);
        bool fo_lep_sel_notrig  = (nFOcut && fo_lep_cut);
        bool num_lep_sel        = (trig_cut && num_lep_sel_notrig);
        bool fo_lep_sel         = (trig_cut && fo_lep_sel_notrig);

        // skip if not FO
        if (!fo_lep_sel)
        {
            return 0;
        }

        // vertex reweight for ttbar
        float evt_weight = weight();

        // muons
        // ----------------------------------------------------------------------------------------------------------------------------//
       
        // Fill Fake Rates 
        if (m_lepton == "mu")
        {
            // numerator
            if (num_lep_sel)
            {

                if (cpfiso03_db()<0.1)
                {
                    if (jet30c_cut && pt()>20) { rt::Fill( hc["h_mu_num20c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet50c_cut && pt()>20) { rt::Fill( hc["h_mu_num40c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet70c_cut && pt()>20) { rt::Fill( hc["h_mu_num60c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet30c_cut           ) { rt::Fill2D(hc["h_mu_num20c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet50c_cut           ) { rt::Fill2D(hc["h_mu_num40c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet70c_cut           ) { rt::Fill2D(hc["h_mu_num60c"], fabs(eta()), pt(), evt_weight); } 
                }
            }

            if (fo_lep_sel)
            {                
                if (cpfiso03_db()<1.0)
                {
                    if (jet30c_cut && pt()>20) { rt::Fill( hc["h_mu_fo20c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet50c_cut && pt()>20) { rt::Fill( hc["h_mu_fo40c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet70c_cut && pt()>20) { rt::Fill( hc["h_mu_fo60c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet30c_cut           ) { rt::Fill2D(hc["h_mu_fo20c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet50c_cut           ) { rt::Fill2D(hc["h_mu_fo40c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet70c_cut           ) { rt::Fill2D(hc["h_mu_fo60c"], fabs(eta()), pt(), evt_weight); } 
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

                if (cpfiso03_rho()<0.09)
                {
                    if (jet30c_cut && pt()>20) { rt::Fill( hc["h_el_num20c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet50c_cut && pt()>20) { rt::Fill( hc["h_el_num40c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet70c_cut && pt()>20) { rt::Fill( hc["h_el_num60c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet30c_cut           ) { rt::Fill2D(hc["h_el_num20c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet50c_cut           ) { rt::Fill2D(hc["h_el_num40c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet70c_cut           ) { rt::Fill2D(hc["h_el_num60c"], fabs(eta()), pt(), evt_weight); } 
                }
            }

            // denominator 
            if (fo_lep_sel)
            {
                if (cpfiso03_rho()<0.6)
                {
                    if (jet30c_cut && pt()>20) { rt::Fill( hc["h_el_fo20c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet50c_cut && pt()>20) { rt::Fill( hc["h_el_fo40c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet70c_cut && pt()>20) { rt::Fill( hc["h_el_fo60c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet30c_cut           ) { rt::Fill2D(hc["h_el_fo20c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet50c_cut           ) { rt::Fill2D(hc["h_el_fo40c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet70c_cut           ) { rt::Fill2D(hc["h_el_fo60c"], fabs(eta()), pt(), evt_weight); } 
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
