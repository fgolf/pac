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
{
    // begin job
    BeginJob();
}

// destroy:
FakeRateBabyLooperETH::~FakeRateBabyLooperETH()
{
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
    return (ch_pfiso03() + max(0.0f, nh_pfiso03() + em_pfiso03() - (max(0.0f, rho())*el_effarea03())))/pt();
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
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num30c_vs_nvtxs"],hc["h_mu_fo30c_vs_nvtxs"], "h_mufr30c_vs_nvtxs", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 30, p_{T} > 20);# vtxs"));
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num50c_vs_nvtxs"],hc["h_mu_fo50c_vs_nvtxs"], "h_mufr50c_vs_nvtxs", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 50, p_{T} > 20);# vtxs"));
        hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_num70c_vs_nvtxs"],hc["h_mu_fo70c_vs_nvtxs"], "h_mufr70c_vs_nvtxs", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 70, p_{T} > 20);# vtxs"));

        // FR(pt)
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num30c"],hc["h_mu_fo30c"], "y", "h_mufr30c_vs_pt", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 30);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num50c"],hc["h_mu_fo50c"], "y", "h_mufr50c_vs_pt", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 50);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num70c"],hc["h_mu_fo70c"], "y", "h_mufr70c_vs_pt", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 70);p_{T}"));
                                                                                                                                                      
        // FR(eta)
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num30c"],hc["h_mu_fo30c"], "x", "h_mufr30c_vs_eta", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 30, p_{T} > 20);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num50c"],hc["h_mu_fo50c"], "x", "h_mufr50c_vs_eta", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 50, p_{T} > 20);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_mu_num70c"],hc["h_mu_fo70c"], "x", "h_mufr70c_vs_eta", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 70, p_{T} > 20);|#eta|", 20, 100));

        // FR(eta, pT)
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num30c"],hc["h_mu_fo30c"], "h_mufr30c", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 30);|#eta|;p_{T} (GeV)"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num50c"],hc["h_mu_fo50c"], "h_mufr50c", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 50);|#eta|;p_{T} (GeV)"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_mu_num70c"],hc["h_mu_fo70c"], "h_mufr70c", "#mu FR cpfiso03 #Delta#beta (0.1, 1.0) (away jet p_{T} > 70);|#eta|;p_{T} (GeV)"));
    }

    // electrons
    if (m_lepton == "el")
    {   
        // FR(# vertices)
        hc.Add(rt::MakeEfficiencyPlot(hc["h_el_num30c_vs_nvtxs"],hc["h_el_fo30c_vs_nvtxs"], "h_elfr30c_vs_nvtxs", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 20, p_{T}>20);# vtxs"));
        hc.Add(rt::MakeEfficiencyPlot(hc["h_el_num50c_vs_nvtxs"],hc["h_el_fo50c_vs_nvtxs"], "h_elfr50c_vs_nvtxs", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40, p_{T}>20);# vtxs"));
        hc.Add(rt::MakeEfficiencyPlot(hc["h_el_num70c_vs_nvtxs"],hc["h_el_fo70c_vs_nvtxs"], "h_elfr70c_vs_nvtxs", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 60, p_{T}>20);# vtxs"));

        // FR(pt)
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num30c"],hc["h_el_fo30c"], "y", "h_elfr30c_vs_pt", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 20);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num50c"],hc["h_el_fo50c"], "y", "h_elfr50c_vs_pt", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40);p_{T}"));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num70c"],hc["h_el_fo70c"], "y", "h_elfr70c_vs_pt", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 60);p_{T}"));
                                                                                                                                                      
        // FR(eta)
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num30c"],hc["h_el_fo30c"], "x", "h_elfr30c_vs_eta", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 20, p_{T}>20);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num50c"],hc["h_el_fo50c"], "x", "h_elfr50c_vs_eta", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40, p_{T}>20);|#eta|", 20, 100));
        hc.Add(rt::MakeEfficiencyProjectionPlot(hc["h_el_num70c"],hc["h_el_fo70c"], "x", "h_elfr70c_vs_eta", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 60, p_{T}>20);|#eta|", 20, 100));

        // FR(eta, pT)
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_el_num30c"],hc["h_el_fo30c"], "h_elfr30c", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 20);|#eta|;p_{T} (GeV)"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_el_num50c"],hc["h_el_fo50c"], "h_elfr50c", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 40);|#eta|;p_{T} (GeV)"));
        hc.Add(rt::MakeEfficiencyPlot2D(hc["h_el_num70c"],hc["h_el_fo70c"], "h_elfr70c", "electron FR cpfiso03 #rho * A_{eff} (0.09, 0.6) (away jet p_{T} > 60);|#eta|;p_{T} (GeV)"));
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
// std::tr1::array<float, 10> mu_pt_bins  = {{5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 50.0, 60.0}};
//std::tr1::array<float, 7> mu_pt_bins   = {{20.0, 25.0, 30.0, 35.0, 40.0, 50.0, 60.0}};
std::tr1::array<float, 6> mu_pt_bins  = {{ 5.0, 10.0, 15.0, 20.0, 25.0, 35.0}};
std::tr1::array<float, 6> el_pt_bins  = {{10.0, 15.0, 20.0, 25.0, 35.0, 55.0}};

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
        hc.Add(new TH1F("h_mu_num30c_vs_nvtxs", "num #mu (away jet p_{T} > 30, cpfiso03 < 0.1 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_num50c_vs_nvtxs", "num #mu (away jet p_{T} > 50, cpfiso03 < 0.1 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_num70c_vs_nvtxs", "num #mu (away jet p_{T} > 70, cpfiso03 < 0.1 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");

        hc.Add(new TH2F("h_mu_num30c", "num #mu (away jet p_{T} > 30, cpfiso03 < 0.1 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_num50c", "num #mu (away jet p_{T} > 50, cpfiso03 < 0.1 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_num70c", "num #mu (away jet p_{T} > 70, cpfiso03 < 0.1 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");

        // denominator
        hc.Add(new TH1F("h_mu_fo30c_vs_nvtxs", "fo #mu (away jet p_{T} > 30, cpfiso03 < 1.0 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_fo50c_vs_nvtxs", "fo #mu (away jet p_{T} > 50, cpfiso03 < 1.0 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_mu_fo70c_vs_nvtxs", "fo #mu (away jet p_{T} > 70, cpfiso03 < 1.0 (#Delta#beta));# vtxs", mu_vtx_bins.size()-1, mu_vtx_bins.data()), "texte");

        hc.Add(new TH2F("h_mu_fo30c", "fo #mu (away jet p_{T} > 30, cpfiso03 < 1.0 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_fo50c", "fo #mu (away jet p_{T} > 50, cpfiso03 < 1.0 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_mu_fo70c", "fo #mu (away jet p_{T} > 70, cpfiso03 < 1.0 (#Delta#beta));|#eta|;p_{T} (GeV)", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()), "texte");
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
        hc.Add(new TH1F("h_el_num30c_vs_nvtxs", "num electron (away jet p_{T} > 20, cpfiso03 < 0.09 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_el_num50c_vs_nvtxs", "num electron (away jet p_{T} > 40, cpfiso03 < 0.09 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_el_num70c_vs_nvtxs", "num electron (away jet p_{T} > 60, cpfiso03 < 0.09 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");

        hc.Add(new TH2F("h_el_num30c", "num electron (away jet p_{T} > 20, cpfiso03 < 0.09 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_el_num50c", "num electron (away jet p_{T} > 40, cpfiso03 < 0.09 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_el_num70c", "num electron (away jet p_{T} > 60, cpfiso03 < 0.09 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");

        // denominator
        hc.Add(new TH1F("h_el_fo30c_vs_nvtxs", "fo electron (away jet p_{T} > 20, cpfiso03 < 0.6 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_el_fo50c_vs_nvtxs", "fo electron (away jet p_{T} > 40, cpfiso03 < 0.6 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");
        hc.Add(new TH1F("h_el_fo70c_vs_nvtxs", "fo electron (away jet p_{T} > 60, cpfiso03 < 0.6 (#rho * A_{eff}));# vtxs", el_vtx_bins.size()-1, el_vtx_bins.data()), "texte");

        hc.Add(new TH2F("h_el_fo30c", "fo electron (away jet p_{T} > 20, cpfiso03 < 0.6 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_el_fo50c", "fo electron (away jet p_{T} > 40, cpfiso03 < 0.6 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");
        hc.Add(new TH2F("h_el_fo70c", "fo electron (away jet p_{T} > 60, cpfiso03 < 0.6 (#rho * A_{eff}));|#eta|;p_{T} (GeV)", el_eta_bins.size()-1, el_eta_bins.data(), el_pt_bins.size()-1, el_pt_bins.data()), "texte");
    }

    hc.Sumw2();
    return;
}

// main analysis function operator 
int FakeRateBabyLooperETH::operator()(long event, const std::string& current_file_name)
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
        bool is_data  = fr::GetSampleInfo(m_sample).type == fr::SampleType::data;
        //bool is_ttbar = m_sample == fr::Sample::ttbar;
        bool is_qcd   = m_sample == fr::Sample::qcd;
        bool is_mu = (m_lepton=="mu") ? abs(id())==13 : false;
        bool is_el = (m_lepton=="el") ? abs(id())==11 : false;

        if (!is_mu && !is_el) return 0;
        
        // qcd muon cuts (for the different qcd samples)
        bool qcd_mu_low  = rt::string_contains(current_file_name, "MuEnrichedPt5"  ) && pt() < 16.0; 
        bool qcd_mu_high = rt::string_contains(current_file_name, "MuEnrichedPt_15") && pt() >= 16.0; 
        if (is_mu && is_qcd && not (qcd_mu_low || qcd_mu_high))
        {
            return 0;
        }

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
        if (is_el && (pt()<10 || pt()>55))
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

        // no additional loose leptons in the event
        if (nvetomus() > 0 || nvetoels() > 0)
        {
            return 0;
        }

        // trigger cuts
        bool trig_cut = false;
        if (is_data && is_mu)
        {
            trig_cut = (mu17_vstar()>0);
        }
        else if(is_data && is_el)
        {
            trig_cut =  (pt() > 17 && (ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar() > 1 || ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar() > 1 ||
                                       ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()  > 1 || ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()  > 1 ));
            trig_cut |= (pt() > 8  && (ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()  > 1 || ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()  > 1 ));
        }


        // away jet cut
        bool jet30c_cut = (ptpfcL1Fj1res() > 30);
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
        bool num_lep_sel_notrig = (num_lep_cut);
        bool fo_lep_sel_notrig  = (fo_lep_cut);
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
                    if (jet30c_cut && pt()>20) { rt::Fill( hc["h_mu_num30c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet50c_cut && pt()>20) { rt::Fill( hc["h_mu_num50c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet70c_cut && pt()>20) { rt::Fill( hc["h_mu_num70c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet30c_cut           ) { rt::Fill2D(hc["h_mu_num30c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet50c_cut           ) { rt::Fill2D(hc["h_mu_num50c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet70c_cut           ) { rt::Fill2D(hc["h_mu_num70c"], fabs(eta()), pt(), evt_weight); } 
                }
            }

            if (fo_lep_sel)
            {                
                if (cpfiso03_db()<1.0)
                {
                    if (jet30c_cut && pt()>20) { rt::Fill( hc["h_mu_fo30c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet50c_cut && pt()>20) { rt::Fill( hc["h_mu_fo50c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet70c_cut && pt()>20) { rt::Fill( hc["h_mu_fo70c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet30c_cut           ) { rt::Fill2D(hc["h_mu_fo30c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet50c_cut           ) { rt::Fill2D(hc["h_mu_fo50c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet70c_cut           ) { rt::Fill2D(hc["h_mu_fo70c"], fabs(eta()), pt(), evt_weight); } 
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
                    if (jet30c_cut && pt()>20) { rt::Fill( hc["h_el_num30c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet50c_cut && pt()>20) { rt::Fill( hc["h_el_num50c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet70c_cut && pt()>20) { rt::Fill( hc["h_el_num70c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet30c_cut           ) { rt::Fill2D(hc["h_el_num30c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet50c_cut           ) { rt::Fill2D(hc["h_el_num50c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet70c_cut           ) { rt::Fill2D(hc["h_el_num70c"], fabs(eta()), pt(), evt_weight); } 
                }
            }

            // denominator 
            if (fo_lep_sel)
            {
                if (cpfiso03_rho()<0.6)
                {
                    if (jet30c_cut && pt()>20) { rt::Fill( hc["h_el_fo30c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet50c_cut && pt()>20) { rt::Fill( hc["h_el_fo50c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 
                    if (jet70c_cut && pt()>20) { rt::Fill( hc["h_el_fo70c_vs_nvtxs"], evt_nvtxs(), evt_weight); } 

                    if (jet30c_cut           ) { rt::Fill2D(hc["h_el_fo30c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet50c_cut           ) { rt::Fill2D(hc["h_el_fo50c"], fabs(eta()), pt(), evt_weight); } 
                    if (jet70c_cut           ) { rt::Fill2D(hc["h_el_fo70c"], fabs(eta()), pt(), evt_weight); } 
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
