#include "OutreachClosure.h"
#include "OutreachBaby.h"
#include <iostream>
#include <algorithm>
#include <tr1/array>
#include <cmath>
#include "rt/RootTools.h"
#include "rt/is_equal.h"
#include "at/Predicates.h"
#include "ScaleFactors.h"
#include "PredSummary.h"
#include "CTable.h"
#include "TF1.h"

typedef std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > vecLorentzVector;

using namespace std;
using namespace at;
using namespace orb;

// helper functions
// -------------------------------------------------------------------------------------------- //

vector<float> GetFitParameters(TH1* hist)
{
	vector<float> params;

	// get fit function name
	string func_name = "";
	if      (rt::string_contains(hist->GetName(), "btagpt"   )) {func_name = "fitf_btag";}
	else if (rt::string_contains(hist->GetName(), "el_pt"    )) {func_name = "efitf";}
	else if (rt::string_contains(hist->GetName(), "mu_pt"    )) {func_name = "mfitf";}
	else if (rt::string_contains(hist->GetName(), "genmet30" )) {func_name = "fitf1";}
	else if (rt::string_contains(hist->GetName(), "genmet50" )) {func_name = "fitf2";}
	else if (rt::string_contains(hist->GetName(), "genmet120")) {func_name = "fitf3";}
	else if (rt::string_contains(hist->GetName(), "ht200"    )) {func_name = "fitf1";}
	else if (rt::string_contains(hist->GetName(), "ht320"    )) {func_name = "fitf2";}
	else
	{
		cout << "invalid hist (" << hist->GetName() << "). exiting" << endl;
		return params;
	}

	// get parameters
	TF1* func = hist->GetFunction(func_name.c_str());
    double* params_array = func->GetParameters(); 
	int num_params       = func->GetNpar(); 
	for (int i = 0; i != num_params; i++)
	{
		//cout << "parm " << i << " = " << params_array[i] << endl;
        params.push_back(static_cast<float>(params_array[i]));
	}

	return params;
}

float GetPtEfficiencyWeight(float pt, TH1* hist) 
{
    vector<float> pars = GetFitParameters(hist);
    float par0 = pars[0];
    float par1 = pars[1];
    float par2 = pars[2];

    float arg = (pt - 20.) / par2;
    float eff = par0 * TMath::Erf(arg) + par1 * (1. - TMath::Erf(arg));
    return eff;
}

float GetMETEfficiencyWeight(float met, TH1* hist) 
{
    vector<float> pars = GetFitParameters(hist);
    float par0 = pars[0];
    float par1 = pars[1];
    float par2 = pars[2];

    float arg = (met - par1) / par2;
    float eff = 0.5 * par0 * (1 + TMath::Erf(arg));
    return eff;
}

float GetHTEfficiencyWeight(float ht, TH1* hist) 
{
    vector<float> pars = GetFitParameters(hist);
    float par0 = pars[0];
    float par1 = pars[1];
    float par2 = pars[2];

    float arg = (ht - par1) / par2;
    float eff = 0.5 * par0 * (1 + TMath::Erf(arg));
    return eff;
}

float GetBtagEfficiency(float bpt, TH1* hist)
{
//------------------------------
// Stupid function:
// linear up to x1
// flat between x1 and x2
// linear again above x2
//------------------------------
    vector<float> pars = GetFitParameters(hist);
    float par0 = pars[0];
    float par1 = pars[1];
    float par2 = pars[2];

    static float x1  = 90.0;
    static float x2  = 170.0;
    static float eff = 0.0;
    
    if (bpt < x1)
        eff = (bpt - x1) * par0 + par1;
    else if (bpt < x2)
        eff = par1;
    else
        eff = par1 + (bpt - x2) * par2;

    return eff;
}

float GetBtagEfficiencyWeight(const std::vector<LorentzVector>& vgbs,  TH1* hist) 
{

    if (vgbs.size() == 2) 
    {
        float e0 = GetBtagEfficiency(vgbs.at(0).pt(), hist);
        float e1 = GetBtagEfficiency(vgbs.at(1).pt(), hist);
        float ineff = (1 - e0) * (1 - e1) + e0 * (1 - e1) + (1 - e0) * e1;

        return (1 - ineff);
    }
    else if (vgbs.size() == 3) 
    {
        float e0 = GetBtagEfficiency(vgbs.at(0).pt(), hist);
        float e1 = GetBtagEfficiency(vgbs.at(1).pt(), hist);
        float e2 = GetBtagEfficiency(vgbs.at(2).pt(), hist);
        float ineff = (1 - e0) * (1 - e1) * (1 - e2) 
            + e0 * (1 - e1) * (1 - e2) 
            + (1 - e0) * e1 * (1 - e2) 
            + (1 - e0) * (1 - e1) * e2;

        return (1 - ineff);
    }
    else if (vgbs.size() == 4) 
    {
        float e0 = GetBtagEfficiency(vgbs.at(0).pt(), hist);
        float e1 = GetBtagEfficiency(vgbs.at(1).pt(), hist);
        float e2 = GetBtagEfficiency(vgbs.at(2).pt(), hist);
        float e3 = GetBtagEfficiency(vgbs.at(3).pt(), hist);
        float ineff = (1 - e0) * (1 - e1) * (1 - e2) * (1 - e3) 
            + e0 * (1 - e1) * (1 - e2) * (1 - e3) 
            + (1 - e0) * e1 * (1 - e2) * (1 - e3) 
            + (1 - e0) * (1 - e1) * e2 * (1 - e3) 
            + (1 - e0) * (1 - e1) * (1 - e2) * e3;

        return (1 - ineff);
    }
    else if (vgbs.size() > 4) 
    {
        // std::cout << "FOUND AN EVENT WITH MORE THAN 4 B PARTONS AT STATUS 3!!!" << std::endl;
        return 1.0;
    }

    return 0.0;
}

// class implementation
// -------------------------------------------------------------------------------------------- //

// construct:

OutreachClosure::OutreachClosure
(
    const std::string& root_file_name,
    at::Sample::value_type sample,
    const std::string& fit_eff_file,
    bool verbose,
    bool print,
    const std::string& suffix
)
    : at::AnalysisWithHist(root_file_name, print, suffix)
    , m_sample(sample)
    , m_fit_sample_name(rt::string_remove_all(rt::basename(fit_eff_file), "_or"))
    , m_verbose(verbose)
{
    // setting the histogram pointers
    cout << "running on sample: " << GetSampleInfo(m_sample).name << endl;
    cout << "filling fit functions with " << fit_eff_file << endl;
    rt::TH1Container hc_temp(fit_eff_file);

    // btag
    h_btagpt.reset(dynamic_cast<TH1F*>(hc_temp[Form("h_eff_%s_btagpt", m_fit_sample_name.c_str())]->Clone())); 

    // lepton
    h_el_pt.reset(dynamic_cast<TH1F*>(hc_temp[Form("h_eff_%s_el_pt", m_fit_sample_name.c_str())]->Clone())); 
    h_mu_pt.reset(dynamic_cast<TH1F*>(hc_temp[Form("h_eff_%s_mu_pt", m_fit_sample_name.c_str())]->Clone())); 

    // met
    h_genmet30.reset( dynamic_cast<TH1F*>(hc_temp[Form("h_eff_%s_genmet30" , m_fit_sample_name.c_str())]->Clone())); 
    h_genmet50.reset( dynamic_cast<TH1F*>(hc_temp[Form("h_eff_%s_genmet50" , m_fit_sample_name.c_str())]->Clone()));
    h_genmet120.reset(dynamic_cast<TH1F*>(hc_temp[Form("h_eff_%s_genmet120", m_fit_sample_name.c_str())]->Clone())); 

    // ht
    h_ht200.reset(dynamic_cast<TH1F*>(hc_temp[Form("h_eff_%s_ht200", m_fit_sample_name.c_str())]->Clone())); 
    h_ht320.reset(dynamic_cast<TH1F*>(hc_temp[Form("h_eff_%s_ht320", m_fit_sample_name.c_str())]->Clone())); 

    // take ownership
    h_btagpt->SetDirectory(NULL);
    h_el_pt->SetDirectory(NULL);
    h_mu_pt->SetDirectory(NULL);
    h_genmet30->SetDirectory(NULL);
    h_genmet50->SetDirectory(NULL);
    h_genmet120->SetDirectory(NULL);
    h_ht200->SetDirectory(NULL);
    h_ht320->SetDirectory(NULL);

    // begin job
    BeginJob();
}

// destroy:
OutreachClosure::~OutreachClosure()
{
    // end  job
    EndJob();
}

// methods:
void OutreachClosure::BeginJob()
{
    BookHists();
}

// end job
void OutreachClosure::EndJob()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    float ht200_obs   = rt::Integral(hc["h_ht200_obs" ]);
    float ht320_obs   = rt::Integral(hc["h_ht320_obs" ]);
    float ht200_pred  = rt::Integral(hc["h_ht200_pred"]);
    float ht320_pred  = rt::Integral(hc["h_ht320_pred"]);
    float ht200_ratio = ht200_obs/ht200_pred;
    float ht320_ratio = ht320_obs/ht320_pred;

    float met30_obs    = rt::Integral(hc["h_met30_obs"  ]);
    float met50_obs    = rt::Integral(hc["h_met50_obs"  ]);
    float met120_obs   = rt::Integral(hc["h_met120_obs" ]);
    float met30_pred   = rt::Integral(hc["h_met30_pred" ]);
    float met50_pred   = rt::Integral(hc["h_met50_pred" ]);
    float met120_pred  = rt::Integral(hc["h_met120_pred"]);
    float met30_ratio  = met30_obs /met30_pred;
    float met50_ratio  = met50_obs /met50_pred;
    float met120_ratio = met120_obs/met120_pred;

    float nbtags_obs   = rt::Integral(hc["h_nbtags_obs"  ]);
    float nbtags_pred  = rt::Integral(hc["h_nbtags_pred" ]);
    float nbtags_ratio = nbtags_obs/nbtags_pred;

    //float pt1_obs   = rt::Integral(hc["h_pt1_obs"  ]);
    //float pt1_pred  = rt::Integral(hc["h_pt1_pred" ]);
    //float pt1_ratio = pt1_obs/pt1_pred;
    //float pt2_obs   = rt::Integral(hc["h_pt2_obs"  ]);
    //float pt2_pred  = rt::Integral(hc["h_pt2_pred" ]);
    //float pt2_ratio = pt2_obs/pt2_pred;
    float pt_obs   = rt::Integral(hc["h_pt_obs"  ]);
    float pt_pred  = rt::Integral(hc["h_pt_pred" ]);
    float pt_ratio = pt_obs/pt_pred;

    float total_obs   = rt::Integral(hc["h_total_obs" ]);
    float total_pred  = rt::Integral(hc["h_total_pred"]);
    float total_ratio = total_obs/total_pred;

    // print the output
    CTable t_closure;
    t_closure.useTitle();
    t_closure.setTitle("outreach obs/pred table");
    t_closure.setTable() (              "obs",        "pred",      "ratio")
                         ("ht200"  , ht200_obs , ht200_pred ,  ht200_ratio)
                         ("ht320"  , ht320_obs , ht320_pred ,  ht320_ratio)
                         ("met30"  , met30_obs , met30_pred ,  met30_ratio)
                         ("met50"  , met50_obs , met50_pred ,  met50_ratio)
                         ("met120" , met120_obs, met120_pred, met120_ratio)
                         ("nbtags" , nbtags_obs, nbtags_pred, nbtags_ratio)
                         ("leptons", pt_obs    , pt_pred    , pt_ratio    )
                         ("total"  , total_obs , total_pred , total_ratio );
    t_closure.print();
    cout << endl;
    t_closure.printTex();

    // ratio plots
    hc.Add(rt::MakeEfficiencyPlot2D(hc["h_sparm_obs_v1"], hc["h_sparm_pred_v1"], "h_sparm_ratio_v1", "direct sbottom obs/pred"));
    hc.Add(rt::MakeEfficiencyPlot2D(hc["h_sparm_obs_v2"], hc["h_sparm_pred_v2"], "h_sparm_ratio_v2", "glustop obs/pred"       ));
    hc.Add(rt::MakeEfficiencyPlot2D(hc["h_sparm_obs_v3"], hc["h_sparm_pred_v3"], "h_sparm_ratio_v3", "glusbottom obs/pred"    ));
}

struct bins_t
{
    unsigned int num;
    float min;
    float max;
};

// book hists 
void OutreachClosure::BookHists()
{
    try
    {
        // convenience alias
        rt::TH1Container& hc = m_hist_container;
        TH1::SetDefaultSumw2(true);

        // bins
        float pt_bins [10] = {5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 40.0, 50.0, 80.0, 200.0};
        const unsigned int n_pt_bins = 9;
        float bpt_bins[12] = {0.0, 20.0, 40.0, 60.0, 80.0, 100.0, 130.0, 160.0, 200.0, 250.0, 300.0, 400.0};
        const unsigned int n_bpt_bins = 11;
        bins_t met_bins  = {25, 0.0, 500.0};
        bins_t ht_bins   = {32, 0.0, 800.0};
        //bins_t mglu_bins = {40, 320, 1120};
        //bins_t mst_bins  = {40, 200, 1000};
        //bins_t msb_bins  = {25, 360, 1110};
        //bins_t mchi_bins = {12, 130, 370};

        // book
        hc.Add(new TH1F("h_ht200_obs" , "h_ht200_obs;H^{gen}_{T} (GeV)" , ht_bins.num, ht_bins.min, ht_bins.max));
        hc.Add(new TH1F("h_ht320_obs" , "h_ht320_obs;H^{gen}_{T} (GeV)" , ht_bins.num, ht_bins.min, ht_bins.max));
        hc.Add(new TH1F("h_ht200_pred", "h_ht200_pred;H^{gen}_{T} (GeV)", ht_bins.num, ht_bins.min, ht_bins.max));
        hc.Add(new TH1F("h_ht320_pred", "h_ht320_pred;H^{gen}_{T} (GeV)", ht_bins.num, ht_bins.min, ht_bins.max));

        hc.Add(new TH1F("h_met30_obs"  , "h_gen30_obs;#slash{E}^{gen}_{T} (GeV)"  , met_bins.num, met_bins.min, met_bins.max));
        hc.Add(new TH1F("h_met50_obs"  , "h_gen50_obs;#slash{E}^{gen}_{T} (GeV)"  , met_bins.num, met_bins.min, met_bins.max));
        hc.Add(new TH1F("h_met120_obs" , "h_gen120_obs;#slash{E}^{gen}_{T} (GeV)" , met_bins.num, met_bins.min, met_bins.max));
        hc.Add(new TH1F("h_met30_pred" , "h_gen30_pred;#slash{E}^{gen}_{T} (GeV)" , met_bins.num, met_bins.min, met_bins.max));
        hc.Add(new TH1F("h_met50_pred" , "h_gen50_pred;#slash{E}^{gen}_{T} (GeV)" , met_bins.num, met_bins.min, met_bins.max));
        hc.Add(new TH1F("h_met120_pred", "h_gen120_pred;#slash{E}^{gen}_{T} (GeV)", met_bins.num, met_bins.min, met_bins.max));

        hc.Add(new TH1F("h_nbtags_obs"  , "h_nbtag_obs;p^{gen}_{T} (GeV)" , n_bpt_bins, bpt_bins));
        hc.Add(new TH1F("h_nbtags_pred" , "h_nbtag_pred;p^{gen}_{T} (GeV)", n_bpt_bins, bpt_bins));

        hc.Add(new TH1F("h_pt1_obs" , "h_pt1_obs;p^{gen}_{T} (GeV)" , n_pt_bins, pt_bins));
        hc.Add(new TH1F("h_pt2_obs" , "h_pt2_obs;p^{gen}_{T} (GeV)" , n_pt_bins, pt_bins));
        hc.Add(new TH1F("h_pt_obs"  , "h_pt_obs;p^{gen}_{T} (GeV)"  , n_pt_bins, pt_bins));
        hc.Add(new TH1F("h_pt1_pred", "h_pt1_pred;p^{gen}_{T} (GeV)", n_pt_bins, pt_bins));
        hc.Add(new TH1F("h_pt2_pred", "h_pt2_pred;p^{gen}_{T} (GeV)", n_pt_bins, pt_bins));
        hc.Add(new TH1F("h_pt_pred" , "h_pt_pred;p^{gen}_{T} (GeV)" , n_pt_bins, pt_bins));

        hc.Add(new TH1F("h_total_obs" , "h_total_obs" , 3, -0.5, 2.5));
        hc.Add(new TH1F("h_total_pred", "h_total_pred", 3, -0.5, 2.5));

        // sbottomtop (m_chi vs m_sb)
        hc.Add(new TH2F("h_sparm_obs_v1" , "CMS #sqrt{s} = 8 TeV, L_{int} = 10.5 fb^{-1};m(#tilde{b}_{1}) GeV;m(#tilde{#chi}^{#pm}_{1}) GeV", 26, 245, 505, 12, 130, 370));
        hc.Add(new TH2F("h_sparm_pred_v1", "CMS #sqrt{s} = 8 TeV, L_{int} = 10.5 fb^{-1};m(#tilde{b}_{1}) GeV;m(#tilde{#chi}^{#pm}_{1}) GeV", 26, 245, 505, 12, 130, 370));

        // glustop (m_g vs m_stop)
        hc.Add(new TH2F("h_sparm_obs_v2" , "CMS #sqrt{s} = 8 TeV, L_{int} = 10.5 fb^{-1};m(#tilde{g}) GeV; m(#tilde{t}_{1}) GeV", 7, 675, 1125, 16, 225, 1025));
        hc.Add(new TH2F("h_sparm_pred_v2", "CMS #sqrt{s} = 8 TeV, L_{int} = 10.5 fb^{-1};m(#tilde{g}) GeV; m(#tilde{t}_{1}) GeV", 7, 675, 1125, 16, 225, 1025));

        // glusbottom (m_g vs m_sb)
        hc.Add(new TH2F("h_sparm_obs_v3" , "CMS #sqrt{s} = 8 TeV, L_{int} = 10.5 fb^{-1};m(#tilde{g}) GeV; m(#tilde{b}_{1}) GeV", 16, 325, 1125, 22, 325, 1425));
        hc.Add(new TH2F("h_sparm_pred_v3", "CMS #sqrt{s} = 8 TeV, L_{int} = 10.5 fb^{-1};m(#tilde{g}) GeV; m(#tilde{b}_{1}) GeV", 16, 325, 1125, 22, 325, 1425));

        return;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }
}

// main analysis function operator 
int OutreachClosure::operator()(long event)
{
    using namespace std;
    using namespace orb;

    try
    {
        // base analysis
        at::AnalysisWithHist::operator()(event);

        // convenience alias
        rt::TH1Container& hc = m_hist_container;

        // simple selections

        if (gen_dilep_type()>3)
        {
            if (m_verbose) {cout << "OutreachClosure: fails the gen dilep type < 4 cut" << endl;}
            return 0;
        }

        // ht test
        if (gen_njets()>1 && gen_met()>50.0)
        {
            float ht200_weight = GetHTEfficiencyWeight(gen_ht(), h_ht200.get()); 
            float ht320_weight = GetHTEfficiencyWeight(gen_ht(), h_ht320.get()); 

            if (reco_ht() > 200) {rt::Fill(hc["h_ht200_obs"], gen_ht(), 1.0);}
            if (reco_ht() > 320) {rt::Fill(hc["h_ht320_obs"], gen_ht(), 1.0);}
            rt::Fill(hc["h_ht200_pred"], gen_ht(), ht200_weight);
            rt::Fill(hc["h_ht320_pred"], gen_ht(), ht320_weight);
        }

        // met test
        if (gen_njets()>1 && gen_ht()>200.0)
        {
            float met30_weight  = GetMETEfficiencyWeight(gen_met(), h_genmet30.get()); 
            float met50_weight  = GetMETEfficiencyWeight(gen_met(), h_genmet50.get()); 
            float met120_weight = GetMETEfficiencyWeight(gen_met(), h_genmet120.get()); 

            if (reco_met() > 30 ) {rt::Fill(hc["h_met30_obs" ], gen_met(), 1.0);}
            if (reco_met() > 50 ) {rt::Fill(hc["h_met50_obs" ], gen_met(), 1.0);}
            if (reco_met() > 120) {rt::Fill(hc["h_met120_obs"], gen_met(), 1.0);}
            rt::Fill(hc["h_met30_pred" ], gen_met(), met30_weight);
            rt::Fill(hc["h_met50_pred" ], gen_met(), met50_weight);
            rt::Fill(hc["h_met120_pred"], gen_met(), met120_weight);
        }

        // btag eff test
        if (gen_njets()>1 && gen_ht()>200.0 && gen_met()>50.0 && gen_nbtags()>=2)
        {
            float btag_weight  = GetBtagEfficiencyWeight(gen_vbjets_p4(), h_btagpt.get()); 

            if (reco_nbtags() >=2 ) 
            {
                rt::Fill(hc["h_nbtags_obs"], gen_nbtags(), 1.0);
            }
            rt::Fill(hc["h_nbtags_pred"], gen_nbtags(), btag_weight);
        }

        // lepton eff test
        if (gen_njets()>1 && gen_ht()>200.0 && gen_met()>50.0)
        {
            float l1_pt = lep1_gen_p4().pt();
            float l2_pt = lep2_gen_p4().pt();

            float l1_pt_weight = abs(lep1_gen_pdgid())==11 ? GetPtEfficiencyWeight(l1_pt, h_el_pt.get())
                                                           : GetPtEfficiencyWeight(l1_pt, h_mu_pt.get()); 
            float l2_pt_weight = abs(lep2_gen_pdgid())==11 ? GetPtEfficiencyWeight(l2_pt, h_el_pt.get())
                                                           : GetPtEfficiencyWeight(l2_pt, h_mu_pt.get()); 

            if (lep1_num()) 
            {
                rt::Fill(hc["h_pt1_obs"], lep1_gen_p4().pt(), 1.0);
            //    rt::Fill(hc["h_pt_obs" ], lep1_gen_p4().pt(), 1.0);
            }
            rt::Fill(hc["h_pt1_pred"], lep1_gen_p4().pt(), l1_pt_weight);
            //rt::Fill(hc["h_pt_pred" ], lep1_gen_p4().pt(), l2_pt_weight);

            if (lep2_num()) 
            {
                rt::Fill(hc["h_pt2_obs"], lep2_gen_p4().pt(), 1.0);
            //    rt::Fill(hc["h_pt_obs" ], lep2_gen_p4().pt(), 1.0);
            }
            rt::Fill(hc["h_pt2_pred"], lep2_gen_p4().pt(), l2_pt_weight);
            //rt::Fill(hc["h_pt_pred" ], lep2_gen_p4().pt(), l2_pt_weight);

            if (lep1_num() && lep2_num()) 
            {
                rt::Fill(hc["h_pt_obs"], 1.0, 1.0);
            }
            rt::Fill(hc["h_pt_pred"], 1.0, l1_pt_weight * l2_pt_weight);
        }

        // total
        if (reco_nbtags()>1 && reco_ht()>200.0 && reco_met()>50.0 && lep1_num() && lep2_num())
        {
            rt::Fill(hc["h_total_obs"], 1.0, 1.0);
        }
        {
            float l1_pt = lep1_gen_p4().pt();
            float l2_pt = lep2_gen_p4().pt();

            float met50_weight = GetMETEfficiencyWeight(gen_met(), h_genmet50.get()); 
            float ht200_weight = GetHTEfficiencyWeight(gen_ht(), h_ht200.get()); 
            float l1_pt_weight = abs(lep1_gen_pdgid())==11 ? GetPtEfficiencyWeight(l1_pt, h_el_pt.get())
                                                           : GetPtEfficiencyWeight(l1_pt, h_mu_pt.get()); 
            float l2_pt_weight = abs(lep2_gen_pdgid())==11 ? GetPtEfficiencyWeight(l2_pt, h_el_pt.get())
                                                           : GetPtEfficiencyWeight(l2_pt, h_mu_pt.get()); 
            float btag_weight  = GetBtagEfficiencyWeight(gen_vbjets_p4(), h_btagpt.get()); 
            float weight       = btag_weight * ht200_weight * met50_weight * l1_pt_weight * l2_pt_weight;

            rt::Fill(hc["h_total_pred"], 1.0, weight);
        }

        // sparms projection 
        if (m_sample == at::Sample::sbottomtop) // lsp == 50.0
        {
            if (not rt::is_equal(sparm2(), 50.0f))
            {
                return 0;
            }
        }
        else if (m_sample == at::Sample::glustop)  // lsp == 50.0
        {
            if (not rt::is_equal(sparm2(), 50.0f))
            {
                return 0;
            }
        }
        else if (m_sample == at::Sample::glusbottom)  // m_chi = 150, m_lsp = 50
        {
            if (not rt::is_equal(sparm2(), 150.0f) && rt::is_equal(sparm3(), 50.0f))
            {
                return 0;
            }
        }

        if (reco_nbtags()>1 && reco_ht()>200.0 && reco_met()>50.0 && lep1_num() && lep2_num())
        {
            rt::Fill2D(hc["h_sparm_obs_v1"], sparm0(), sparm1(), 1.0);
            rt::Fill2D(hc["h_sparm_obs_v2"], sparm0(), sparm1(), 1.0);
            rt::Fill2D(hc["h_sparm_obs_v3"], sparm0(), sparm1(), 1.0);
        }
        {
            float l1_pt = lep1_gen_p4().pt();
            float l2_pt = lep2_gen_p4().pt();

            float met50_weight = GetMETEfficiencyWeight(gen_met(), h_genmet50.get()); 
            float ht200_weight = GetHTEfficiencyWeight(gen_ht(), h_ht200.get()); 
            float l1_pt_weight = abs(lep1_gen_pdgid())==11 ? GetPtEfficiencyWeight(l1_pt, h_el_pt.get())
                                                           : GetPtEfficiencyWeight(l1_pt, h_mu_pt.get()); 
            float l2_pt_weight = abs(lep2_gen_pdgid())==11 ? GetPtEfficiencyWeight(l2_pt, h_el_pt.get())
                                                           : GetPtEfficiencyWeight(l2_pt, h_mu_pt.get()); 
            float btag_weight  = GetBtagEfficiencyWeight(gen_vbjets_p4(), h_btagpt.get()); 
            float weight       = btag_weight * ht200_weight * met50_weight * l1_pt_weight * l2_pt_weight;

            rt::Fill2D(hc["h_sparm_pred_v1"], sparm0(), sparm1(), weight);
            rt::Fill2D(hc["h_sparm_pred_v2"], sparm0(), sparm1(), weight);
            rt::Fill2D(hc["h_sparm_pred_v3"], sparm0(), sparm1(), weight);
        }

    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
    }

    // analysis end
    return 0;
} 
