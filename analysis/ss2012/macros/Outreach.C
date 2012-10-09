#include "rt/RootTools.h"
#include "CTable.h"
#include "TSystem.h"
#include "TChain.h"
#include "TEventList.h"
#include "TCut.h"
#include "TF1.h"
#include "CTable.h"
#include "TH1F.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TMath.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TLine.h"
#include "TLatex.h"
#include "TLegend.h"
#include <string>

using namespace std;
using namespace rt;

struct bins_t
{
    unsigned int num;
    float min;
    float max;
};


void CreateOutreachHists(const std::string& sample_name)
{
    //  Book histograms...
    // ------------------------------------------------------------------------------------------ //

    // bins
    float pt_bins [10] = {5.0, 10.0, 15.0, 20.0, 25.0, 30.0, 40.0, 50.0, 80.0, 200.0};
    const unsigned int n_pt_bins = 9;
    float bpt_bins[12] = {0.0, 20.0, 40.0, 60.0, 80.0, 100.0, 130.0, 160.0, 200.0, 250.0, 300.0, 400.0};
    const unsigned int n_bpt_bins = 11;
    bins_t met_bins = {25, 0.0, 500.0};
    bins_t ht_bins  = {32, 0.0, 800.0};

    // book
    TH1Container hc;
    hc.Add(new TH1F(Form("h_%s_ht"   , sample_name.c_str()), Form("h_%s_ht;H^{gen}_{T} (GeV)"   , sample_name.c_str()), ht_bins.num, ht_bins.min, ht_bins.max));
    hc.Add(new TH1F(Form("h_%s_ht200", sample_name.c_str()), Form("h_%s_ht200;H^{gen}_{T} (GeV)", sample_name.c_str()), ht_bins.num, ht_bins.min, ht_bins.max));
    hc.Add(new TH1F(Form("h_%s_ht320", sample_name.c_str()), Form("h_%s_ht320;H^{gen}_{T} (GeV)", sample_name.c_str()), ht_bins.num, ht_bins.min, ht_bins.max));

    hc.Add(new TH1F(Form("h_%s_genmet"   , sample_name.c_str()), Form("h_%s_ht;#slash{E}^{gen}_{T} (GeV)"   , sample_name.c_str()), met_bins.num, met_bins.min, met_bins.max));
    hc.Add(new TH1F(Form("h_%s_genmet30" , sample_name.c_str()), Form("h_%s_ht30;#slash{E}^{gen}_{T} (GeV)" , sample_name.c_str()), met_bins.num, met_bins.min, met_bins.max));
    hc.Add(new TH1F(Form("h_%s_genmet50" , sample_name.c_str()), Form("h_%s_ht50;#slash{E}^{gen}_{T} (GeV)" , sample_name.c_str()), met_bins.num, met_bins.min, met_bins.max));
    hc.Add(new TH1F(Form("h_%s_genmet120", sample_name.c_str()), Form("h_%s_ht120;#slash{E}^{gen}_{T} (GeV)", sample_name.c_str()), met_bins.num, met_bins.min, met_bins.max));

    hc.Add(new TH1F(Form("h_%s_btagpt"  , sample_name.c_str()), Form("h_%s_btagpt;p^{gen}_{T} (GeV)"  , sample_name.c_str()), n_bpt_bins, bpt_bins));
    hc.Add(new TH1F(Form("h_%s_btagpt40", sample_name.c_str()), Form("h_%s_btagpt40;p^{gen}_{T} (GeV)", sample_name.c_str()), n_bpt_bins, bpt_bins));

    hc.Add(new TH1F(Form("h_%s_el_pt_den", sample_name.c_str()), Form("h_%s_el_pt_den;p^{gen}_{T} (GeV)", sample_name.c_str()), n_pt_bins, pt_bins));
    hc.Add(new TH1F(Form("h_%s_el_pt_num", sample_name.c_str()), Form("h_%s_el_pt_num;p^{gen}_{T} (GeV)", sample_name.c_str()), n_pt_bins, pt_bins));
    hc.Add(new TH1F(Form("h_%s_mu_pt_den", sample_name.c_str()), Form("h_%s_mu_pt_den;p^{gen}_{T} (GeV)", sample_name.c_str()), n_pt_bins, pt_bins));
    hc.Add(new TH1F(Form("h_%s_mu_pt_num", sample_name.c_str()), Form("h_%s_mu_pt_num;p^{gen}_{T} (GeV)", sample_name.c_str()), n_pt_bins, pt_bins));
    hc.Add(new TH1F(Form("h_%s_el_pt_id" , sample_name.c_str()), Form("h_%s_el_pt_id;p^{gen}_{T} (GeV)" , sample_name.c_str()), n_pt_bins, pt_bins));
    hc.Add(new TH1F(Form("h_%s_mu_pt_id" , sample_name.c_str()), Form("h_%s_mu_pt_id;p^{gen}_{T} (GeV)" , sample_name.c_str()), n_pt_bins, pt_bins));
    hc.Add(new TH1F(Form("h_%s_el_pt_iso", sample_name.c_str()), Form("h_%s_el_pt_iso;p^{gen}_{T} (GeV)", sample_name.c_str()), n_pt_bins, pt_bins));
    hc.Add(new TH1F(Form("h_%s_mu_pt_iso", sample_name.c_str()), Form("h_%s_mu_pt_iso;p^{gen}_{T} (GeV)", sample_name.c_str()), n_pt_bins, pt_bins));
    hc.SetDirectory(gDirectory);
    hc.Sumw2();

    // fill hists
    // ------------------------------------------------------------------------------------------ //

    // get chain
    TChain chain("tree");
    chain.Add(Form("babies_outreach/%s.root", sample_name.c_str()));

    // ht efficieny selection
    TCut ht_eff    = "gen_met > 50.0 && njets >=2";
    TCut ht200_eff = ht_eff && TCut("ht>200.0");
    TCut ht320_eff = ht_eff && TCut("ht>320.0");

    // met selection
    TCut met_eff    = "gen_ht > 200.0 && njets >=2";
    TCut met30_eff  = met_eff && TCut("pfmet>30.0" );
    TCut met50_eff  = met_eff && TCut("pfmet>50.0" );
    TCut met120_eff = met_eff && TCut("pfmet>120.0");

    // b-tagging selection
    TCut btag_eff   = "gen_ht > 200.0 && gen_met > 50.0 && njets >=2";
    TCut btag40_eff = btag_eff && TCut("vbjets_num");

    // lepton selection
    TCut el1_den = "gen_ht > 200.0 && gen_met > 50.0 && njets >=2 && abs(lep1_pdgid==11)";
    TCut el2_den = "gen_ht > 200.0 && gen_met > 50.0 && njets >=2 && abs(lep2_pdgid==11)";
    TCut el1_num = el1_den && TCut("lep1_num");
    TCut el2_num = el2_den && TCut("lep2_num");
    TCut el1_id  = el1_den && TCut("lep1_passes_id");
    TCut el2_id  = el2_den && TCut("lep2_passes_id");
    TCut el1_iso = el1_den && TCut("lep1_passes_iso");
    TCut el2_iso = el2_den && TCut("lep2_passes_iso");

    TCut mu1_den = "gen_ht > 200.0 && gen_met > 50.0 && njets >=2 && abs(lep1_pdgid==13)";
    TCut mu2_den = "gen_ht > 200.0 && gen_met > 50.0 && njets >=2 && abs(lep2_pdgid==13)";
    TCut mu1_num = mu1_den && TCut("lep1_num");
    TCut mu2_num = mu2_den && TCut("lep2_num");
    TCut mu1_id  = mu1_den && TCut("lep1_passes_id");
    TCut mu2_id  = mu2_den && TCut("lep2_passes_id");
    TCut mu1_iso = mu1_den && TCut("lep1_passes_iso");
    TCut mu2_iso = mu2_den && TCut("lep2_passes_iso");

    // draw
    chain.Draw(Form("gen_ht>>h_%s_ht"   , sample_name.c_str()), ht_eff   , "goff");
    chain.Draw(Form("gen_ht>>h_%s_ht200", sample_name.c_str()), ht200_eff, "goff");
    chain.Draw(Form("gen_ht>>h_%s_ht320", sample_name.c_str()), ht320_eff, "goff");

    chain.Draw(Form("gen_met>>h_%s_genmet"   , sample_name.c_str()), met_eff   , "goff");
    chain.Draw(Form("gen_met>>h_%s_genmet30" , sample_name.c_str()), met30_eff , "goff");
    chain.Draw(Form("gen_met>>h_%s_genmet50" , sample_name.c_str()), met50_eff , "goff");
    chain.Draw(Form("gen_met>>h_%s_genmet120", sample_name.c_str()), met120_eff, "goff");

    chain.Draw(Form("vbjets_p4.pt()>>h_%s_btagpt"  , sample_name.c_str()), btag_eff  , "goff");
    chain.Draw(Form("vbjets_p4.pt()>>h_%s_btagpt40", sample_name.c_str()), btag40_eff, "goff");

    chain.Draw(Form("lep1_p4.pt()>>h_%s_el_pt_den" , sample_name.c_str()), el1_den, "goff");
    chain.Draw(Form("lep2_p4.pt()>>+h_%s_el_pt_den", sample_name.c_str()), el2_den, "goff");
    chain.Draw(Form("lep1_p4.pt()>>h_%s_el_pt_num" , sample_name.c_str()), el1_num, "goff");
    chain.Draw(Form("lep2_p4.pt()>>+h_%s_el_pt_num", sample_name.c_str()), el2_num, "goff");

    chain.Draw(Form("lep1_p4.pt()>>h_%s_el_pt_id"  , sample_name.c_str()), el1_id , "goff");
    chain.Draw(Form("lep2_p4.pt()>>+h_%s_el_pt_id" , sample_name.c_str()), el2_id , "goff");
    chain.Draw(Form("lep1_p4.pt()>>h_%s_el_pt_iso" , sample_name.c_str()), el1_iso, "goff");
    chain.Draw(Form("lep2_p4.pt()>>+h_%s_el_pt_iso", sample_name.c_str()), el2_iso, "goff");

    chain.Draw(Form("lep1_p4.pt()>>h_%s_mu_pt_den" , sample_name.c_str()), mu1_den, "goff");
    chain.Draw(Form("lep2_p4.pt()>>+h_%s_mu_pt_den", sample_name.c_str()), mu2_den, "goff");
    chain.Draw(Form("lep1_p4.pt()>>h_%s_mu_pt_num" , sample_name.c_str()), mu1_num, "goff");
    chain.Draw(Form("lep2_p4.pt()>>+h_%s_mu_pt_num", sample_name.c_str()), mu2_num, "goff");

    chain.Draw(Form("lep1_p4.pt()>>h_%s_mu_pt_id"  , sample_name.c_str()), mu1_id , "goff");
    chain.Draw(Form("lep2_p4.pt()>>+h_%s_mu_pt_id" , sample_name.c_str()), mu2_id , "goff");
    chain.Draw(Form("lep1_p4.pt()>>h_%s_mu_pt_iso" , sample_name.c_str()), mu1_iso, "goff");
    chain.Draw(Form("lep2_p4.pt()>>+h_%s_mu_pt_iso", sample_name.c_str()), mu2_iso, "goff");

    // create efficiencies
    hc.Add(MakeEfficiencyPlot(hc[Form("h_%s_ht200", sample_name.c_str())], hc[Form("h_%s_ht", sample_name.c_str())], Form("h_eff_%s_ht200", sample_name.c_str()), "CMS Simulation, #sqrt{s} = 8 TeV;H^{gen}_{T} (GeV);Efficiency"));
    hc.Add(MakeEfficiencyPlot(hc[Form("h_%s_ht320", sample_name.c_str())], hc[Form("h_%s_ht", sample_name.c_str())], Form("h_eff_%s_ht320", sample_name.c_str()), "CMS Simulation, #sqrt{s} = 8 TeV;H^{gen}_{T} (GeV);Efficiency"));

    hc.Add(MakeEfficiencyPlot(hc[Form("h_%s_genmet30" , sample_name.c_str())], hc[Form("h_%s_genmet", sample_name.c_str())],Form("h_eff_%s_genmet30" ,sample_name.c_str()),"CMS Simulation, #sqrt{s} = 8 TeV;#slash{E}^{gen}_{T} (GeV);Efficiency"));
    hc.Add(MakeEfficiencyPlot(hc[Form("h_%s_genmet50" , sample_name.c_str())], hc[Form("h_%s_genmet", sample_name.c_str())],Form("h_eff_%s_genmet50" ,sample_name.c_str()),"CMS Simulation, #sqrt{s} = 8 TeV;#slash{E}^{gen}_{T} (GeV);Efficiency"));
    hc.Add(MakeEfficiencyPlot(hc[Form("h_%s_genmet120", sample_name.c_str())], hc[Form("h_%s_genmet", sample_name.c_str())],Form("h_eff_%s_genmet120",sample_name.c_str()),"CMS Simulation, #sqrt{s} = 8 TeV;#slash{E}^{gen}_{T} (GeV);Efficiency"));

    hc.Add(MakeEfficiencyPlot(hc[Form("h_%s_btagpt40", sample_name.c_str())], hc[Form("h_%s_btagpt", sample_name.c_str())],Form("h_eff_%s_btagpt",sample_name.c_str()),"CMS Simulation, #sqrt{s} = 8 TeV;p^{gen}_{T} (GeV);Efficiency"));

    hc.Add(MakeEfficiencyPlot(hc[Form("h_%s_el_pt_num" , sample_name.c_str())], hc[Form("h_%s_el_pt_den" , sample_name.c_str())],Form("h_eff_%s_el_pt"    ,sample_name.c_str()),"CMS Simulation, #sqrt{s} = 8 TeV;p^{gen}_{T} (GeV);Efficiency"));
    hc.Add(MakeEfficiencyPlot(hc[Form("h_%s_mu_pt_num" , sample_name.c_str())], hc[Form("h_%s_mu_pt_den" , sample_name.c_str())],Form("h_eff_%s_mu_pt"    ,sample_name.c_str()),"CMS Simulation, #sqrt{s} = 8 TeV;p^{gen}_{T} (GeV);Efficiency"));
    hc.Add(MakeEfficiencyPlot(hc[Form("h_%s_el_pt_id"  , sample_name.c_str())], hc[Form("h_%s_el_pt_den" , sample_name.c_str())],Form("h_eff_%s_el_id_pt" ,sample_name.c_str()),"CMS Simulation, #sqrt{s} = 8 TeV;p^{gen}_{T} (GeV);Efficiency"));
    hc.Add(MakeEfficiencyPlot(hc[Form("h_%s_mu_pt_id"  , sample_name.c_str())], hc[Form("h_%s_mu_pt_den" , sample_name.c_str())],Form("h_eff_%s_mu_id_pt" ,sample_name.c_str()),"CMS Simulation, #sqrt{s} = 8 TeV;p^{gen}_{T} (GeV);Efficiency"));
    hc.Add(MakeEfficiencyPlot(hc[Form("h_%s_el_pt_iso" , sample_name.c_str())], hc[Form("h_%s_el_pt_den" , sample_name.c_str())],Form("h_eff_%s_el_iso_pt",sample_name.c_str()),"CMS Simulation, #sqrt{s} = 8 TeV;p^{gen}_{T} (GeV);Efficiency"));
    hc.Add(MakeEfficiencyPlot(hc[Form("h_%s_mu_pt_iso" , sample_name.c_str())], hc[Form("h_%s_mu_pt_den" , sample_name.c_str())],Form("h_eff_%s_mu_iso_pt",sample_name.c_str()),"CMS Simulation, #sqrt{s} = 8 TeV;p^{gen}_{T} (GeV);Efficiency"));


    // write the output
    // ------------------------------------------------------------------------------------------ //
    hc.SetDirectory(NULL);
    hc.Write(Form("plots/outreach/%s_or.root", sample_name.c_str()));
}


// Do the fitting
// --------------------------------------------------------------------------------------- //

double fitf(double* x, double* par) 
{
    double arg = 0;
    if (par[2] != 0)
    {
        arg = (x[0] - par[1])/par[2];
    }
    
    double fitval = 0.5 * par[0] * (TMath::Erf(arg) + 1);
    return fitval;
}


double fitf2(double* x, double* par)
{
    double arg = 0;
    if (par[1] != 0)
    {
        arg = (x[0] - par[0])/par[1];
    }
    
    double fitval = (TMath::Erf(arg) + 1);
    return fitval;
}

// HT fit
void FitHtTurnOnCurve(const std::string& sample_name) 
{
    gStyle->SetOptStat("");
    rt::SetTDRStyle();

    TFile* file = TFile::Open(Form("plots/outreach/%s_or.root", sample_name.c_str()), "UPDATE");
    if (!file || file->IsZombie())
    {
        cout << "FitHtTurnOnCurve: file not found!" << endl;
        return;
    }

    TCanvas* c1 = new TCanvas("c1", "c1"); 
    c1->cd();

    TH1* h1 = dynamic_cast<TH1*>(file->Get(Form("h_eff_%s_ht200", sample_name.c_str()))); 
    h1->SetLineWidth(2);
    h1->SetMarkerStyle(20);
    h1->SetMarkerSize(1.2);
    h1->SetLineColor(kRed);
    h1->SetMarkerColor(h1->GetLineColor());
    h1->GetYaxis()->SetRangeUser(-0.05, 1.1);
    TH1* h2 = dynamic_cast<TH1*>(file->Get(Form("h_eff_%s_ht320", sample_name.c_str()))); 
    h2->SetLineWidth(2);
    h2->SetMarkerStyle(22);
    h2->SetMarkerSize(1.2);
    h2->SetLineColor(kBlue);
    h2->GetYaxis()->SetRangeUser(-0.05, 1.1);
    h2->SetMarkerColor(h2->GetLineColor());

    h1->Draw();
    h2->Draw("sames");

    TF1* func1 = new TF1("fitf1", fitf, 100, 800, 3);
    func1->SetParameters(1.0, 200.0, 10.0);
    func1->SetParNames("offset", "normalization", "constant");
    func1->SetLineColor(kBlack);
    func1->SetLineWidth(2);
    h1->Fit(func1, "r", "same");

    TLine* line = new TLine(200, 0.0, 200, 1.0);
    line->SetLineColor(h1->GetMarkerColor());
    line->SetLineWidth(2);
    line->Draw("sames");

    std::cout << std::endl;
    std::cout << "chi2/ndof: " << func1->GetChisquare() << "/" << func1->GetNDF() << std::endl;
    std::cout << "prob: " << func1->GetProb() << std::endl;
    std::cout << std::endl;

    TF1* func2 = new TF1("fitf2", fitf, 150, 800, 3);
    func2->SetParameters(1.0, 320.0, 15.0);
    func2->SetParNames("offset", "normalization", "constant");
    func2->SetLineColor(kBlack);
    func2->SetLineWidth(2);
    h2->Fit(func2, "r", "same");

    TLine* line2 = new TLine(320, 0.0, 320, 1.0);
    line2->SetLineColor(h2->GetMarkerColor());
    line2->SetLineWidth(2);
    line2->Draw("sames");

    std::cout << std::endl;
    std::cout << "chi2/ndof: " << func2->GetChisquare() << "/" << func2->GetNDF() << std::endl;
    std::cout << "prob: " << func2->GetProb() << std::endl;
    std::cout << std::endl;

    TLegend* legend = new TLegend(0.6, 0.5, 0.9, 0.7);
    legend->AddEntry(h1,"H_{T} > 200 GeV", "p");
    legend->AddEntry(h2,"H_{T} > 320 GeV", "p");
    legend->SetFillColor(0);
    legend->Draw("sames");

    c1->Draw();
    c1->Print(Form("plots/outreach/HtTurnOnCurve_%s.pdf" , sample_name.c_str()));
    c1->Print(Form("plots/outreach/HtTurnOnCurve_%s.root", sample_name.c_str()));

    CTable t1;
    double* params1 = func1->GetParameters(); 
    double* errors1 = func1->GetParErrors(); 
    double* params2 = func2->GetParameters(); 
    double* errors2 = func2->GetParErrors(); 
    t1.useTitle();
    t1.setTitle("HT fit");
    t1.setTable() (                                         "HT > 200",                            "HT > 320")
                  ("eps_infty" , rt::pm(params1[0], errors1[0], "1.3"), rt::pm(params2[0], errors2[0], "1.3"))
                  ("x_1/2 GeV" , rt::pm(params1[1], errors1[1], "1.3"), rt::pm(params2[1], errors2[1], "1.3"))
                  ("sigma, GeV", rt::pm(params1[2], errors1[2], "1.3"), rt::pm(params2[2], errors2[2], "1.3"));
    t1.print();

	// save fits back to file
	file->Write();
	file->Close();
	delete file;

    return;
}


double fitf_met(double* x, double* par) 
{
    double arg = 0;
    if (par[2] != 0)
    {
        arg = (x[0] - par[1])/par[2];
    }
    
    double fitval = 0.5 * par[0] * (TMath::Erf(arg) + 1);
    return fitval;
}

// MET fit
void FitMetTurnOnCurve(const std::string& sample_name) 
{
    gStyle->SetOptStat("");
    rt::SetTDRStyle();

    TFile* file = TFile::Open(Form("plots/outreach/%s_or.root", sample_name.c_str()), "UPDATE");
    if (!file || file->IsZombie())
    {
        cout << "FitHtTurnOnCurve: file not found!" << endl;
        return;
    }

    TCanvas* c1 = new TCanvas("c1", "c1"); 
    c1->cd();

    TH1* h1 = dynamic_cast<TH1*>(file->Get(Form("h_eff_%s_genmet30", sample_name.c_str()))); 
    h1->SetLineWidth(2);
    h1->SetMarkerStyle(20);
    h1->SetMarkerSize(1.2);
    h1->SetLineColor(kRed);
    h1->SetMarkerColor(h1->GetLineColor());
    h1->GetYaxis()->SetRangeUser(-0.05, 1.1);
    TH1* h2 = dynamic_cast<TH1*>(file->Get(Form("h_eff_%s_genmet50", sample_name.c_str()))); 
    h2->SetLineWidth(2);
    h2->SetMarkerStyle(22);
    h2->SetMarkerSize(1.2);
    h2->SetLineColor(kBlue);
    h2->SetMarkerColor(h2->GetLineColor());
    h2->GetYaxis()->SetRangeUser(-0.05, 1.1);
    TH1* h3 = dynamic_cast<TH1*>(file->Get(Form("h_eff_%s_genmet120", sample_name.c_str()))); 
    h3->SetLineWidth(2);
    h3->SetMarkerStyle(24);
    h3->SetMarkerSize(1.2);
    h3->SetLineColor(kBlack);
    h3->SetMarkerColor(h3->GetLineColor());
    h3->GetYaxis()->SetRangeUser(-0.05, 1.1);

    h1->Draw();
    h2->Draw("sames");
    h3->Draw("sames");

    TF1* func1 = new TF1("fitf1", fitf_met, 0, 500, 3);
    func1->SetParameters(1.0, 30.0, 20.0);
    func1->SetParNames("normalization", "offset", "constant");
    func1->SetLineColor(kBlack);
    func1->SetLineWidth(2);
    h1->Fit(func1, "r", "same");

    TLine* line = new TLine(30.0, 0.0, 30, 1.0);
    line->SetLineColor(h1->GetLineColor());
    line->SetLineWidth(h1->GetLineWidth());
    line->Draw("sames");

    std::cout << std::endl;
    std::cout << "chi2/ndof: " << func1->GetChisquare() << "/" << func1->GetNDF() << std::endl;
    std::cout << "prob: " << func1->GetProb() << std::endl;
    std::cout << std::endl;

    TF1* func2 = new TF1("fitf2", fitf_met, 0, 500, 3);
    func2->SetParameters(1.0, 50.0, 20.0);
    func2->SetParNames("normalization", "offset", "constant");
    func2->SetLineColor(kBlack);
    func2->SetLineWidth(2);
    h2->Fit(func2, "r", "same");

    TLine* line2 = new TLine(50.0, 0.0, 50, 1.0);
    line2->SetLineColor(h2->GetLineColor());
    line2->SetLineWidth(h2->GetLineWidth());
    line2->Draw("sames");

    std::cout << std::endl;
    std::cout << "chi2/ndof: " << func2->GetChisquare() << "/" << func2->GetNDF() << std::endl;
    std::cout << "prob: " << func2->GetProb() << std::endl;
    std::cout << std::endl;

    TF1* func3 = new TF1("fitf3", fitf_met, 0, 500, 3);
    func3->SetParameters(1.0, 120.0, 20.0);
    func3->SetParNames("normalization", "offset", "constant");
    func3->SetLineColor(kBlack);
    func3->SetLineWidth(2);
    h3->Fit(func3, "r", "same");

    TLine* line3 = new TLine(120.0, 0.0, 120, 1.0);
    line3->SetLineColor(h3->GetLineColor());
    line3->SetLineWidth(h3->GetLineWidth());
    line3->Draw("sames");

    std::cout << std::endl;
    std::cout << "chi2/ndof: " << func3->GetChisquare() << "/" << func3->GetNDF() << std::endl;
    std::cout << "prob: " << func3->GetProb() << std::endl;
    std::cout << std::endl;

    TLegend* legend = new TLegend(0.6, 0.5, 0.9, 0.7);
    legend->AddEntry(h1,"#slash{E}_{T} > 30 GeV" , "p");
    legend->AddEntry(h2,"#slash{E}_{T} > 50 GeV" , "p");
    legend->AddEntry(h3,"#slash{E}_{T} > 120 GeV", "p");
    legend->SetFillColor(0);
    legend->Draw("sames");

    CTable t1;
    double* params1 = func1->GetParameters(); 
    double* errors1 = func1->GetParErrors(); 
    double* params2 = func2->GetParameters(); 
    double* errors2 = func2->GetParErrors(); 
    double* params3 = func3->GetParameters(); 
    double* errors3 = func3->GetParErrors(); 
    t1.useTitle();
    t1.setTitle("MET fit");
    t1.setTable() (                                         "MET > 30",                            "MET > 50",                           "MET > 120")
                  ("eps_infty" , rt::pm(params1[0], errors1[0], "1.3"), rt::pm(params2[0], errors2[0], "1.3"), rt::pm(params3[0], errors3[0], "1.3"))
                  ("x_1/2 GeV" , rt::pm(params1[1], errors1[1], "1.3"), rt::pm(params2[1], errors2[1], "1.3"), rt::pm(params3[1], errors3[1], "1.3"))
                  ("sigma, GeV", rt::pm(params1[2], errors1[2], "1.3"), rt::pm(params2[2], errors2[2], "1.3"), rt::pm(params3[2], errors3[2], "1.3"));
    t1.print();

    c1->Draw();
    c1->Print(Form("plots/outreach/MetTurnOnCurve_%s.pdf" , sample_name.c_str()));
    c1->Print(Form("plots/outreach/MetTurnOnCurve_%s.root", sample_name.c_str()));

	// save fits back to file
	file->Write();
	file->Close();
	delete file;

    return;
}

//------------------------------
// Stupid function:
// linear up to x1
// flat between x1 and x2
// linear again above x2
//------------------------------
Double_t fitf_btag(Double_t *x, Double_t *par) 
{
    Double_t x1 = 90.;
    Double_t x2 = 170.;
    Double_t ytop = par[1];
    Double_t fitval=0.;
    if (x[0] < x1) 
    {
        fitval = (x[0]-x1)*par[0]+par[1];
    } 
    else if (x[0] < x2) 
    {
        fitval = ytop;
    } 
    else 
    {
        fitval = ytop + (x[0]-x2)*par[2];
    }
    return fitval;
}

// Btag fit
void FitBtagEfficiencyCurve(const std::string& sample_name) 
{
    //gStyle->SetStatBorderSize(1);
    //gStyle->SetStatColor(0);
    //gStyle->SetStatX(0.90);
    //gStyle->SetStatY(0.86);
    //gStyle->SetStatW(0.18);
    //gStyle->SetStatH(0.13);
    //gStyle->SetOptFit(0000);
    //gStyle->SetFitFormat("5.4f");

    gStyle->SetOptStat("");
    rt::SetTDRStyle();

    TFile* file = TFile::Open(Form("plots/outreach/%s_or.root", sample_name.c_str()), "UPDATE");
    if (!file || file->IsZombie())
    {
        cout << "FitHtTurnOnCurve: file not found!" << endl;
        return;
    }
    file->ls();

    TCanvas* c1 = new TCanvas("c1", "c1"); 
    c1->cd();

    TH1* h1 = dynamic_cast<TH1*>(file->Get(Form("h_eff_%s_btagpt", sample_name.c_str()))); 
    h1->SetLineWidth(2);
    h1->SetMarkerStyle(22);
    h1->SetMarkerSize(1.2);
    h1->SetLineColor(kRed);
    h1->SetMarkerColor(h1->GetLineColor());
    h1->GetYaxis()->SetRangeUser(-0.05, 1.1);
    h1->Draw();

    TF1* bfunc = new TF1("fitf_btag", fitf_btag, 40, 400, 3);
    bfunc->SetParameters(0, 0.5, 40);
    bfunc->SetParNames("p0", "p1", "p2");
    bfunc->SetLineColor(kBlack);
    bfunc->SetLineWidth(h1->GetLineWidth());
    h1->Fit(bfunc, "r", "same");

    std::cout << std::endl;
    std::cout << "chi2/ndof: " << bfunc->GetChisquare() << "/" << bfunc->GetNDF() << std::endl;
    std::cout << "prob: " << bfunc->GetProb() << std::endl;
    std::cout << std::endl;

    CTable t1;
    double* params1 = bfunc->GetParameters(); 
    double* errors1 = bfunc->GetParErrors(); 
    t1.useTitle();
    t1.setTitle("Btag Eff fit");
    t1.setTable() (                                    "value")
                  ("p0", rt::pm(params1[0], errors1[0], "1.4"))
                  ("p1", rt::pm(params1[1], errors1[1], "1.4"))
                  ("p2", rt::pm(params1[2], errors1[2], "1.4"));
    t1.print();

    c1->Draw();
    c1->Print(Form("plots/outreach/btagEfficiency_%s.pdf" , sample_name.c_str()));
    c1->Print(Form("plots/outreach/btagEfficiency_%s.root", sample_name.c_str()));

	// save fits back to file
	file->Write();
	file->Close();

    return;
}


double efitf (double* x, double* par) 
{
    double arg = 0;
    if (par[2] != 0)
    {
        arg = (x[0] - 20.)/par[2];
    }

    double fitval = par[0]*TMath::Erf(arg)+par[1]*(1.-TMath::Erf(arg));
    return fitval;
}

double mfitf (double* x, double* par)
{
    double arg = 0;
    if (par[2] != 0)
    {
        arg = (x[0] - 20.)/par[2];
    }

    double fitval = par[0]*TMath::Erf(arg)+par[1]*(1.-TMath::Erf(arg));
    return fitval;
}

// lep eff fit
void FitLepEfficiencyCurve(const std::string& sample_name) 
{
    gStyle->SetOptStat("");
    rt::SetTDRStyle();

    TFile* file = TFile::Open(Form("plots/outreach/%s_or.root", sample_name.c_str()), "UPDATE");
    if (!file || file->IsZombie())
    {
        cout << "FitHtTurnOnCurve: file not found!" << endl;
        return;
    }
    file->ls();

    TCanvas* c1 = new TCanvas("c1", "c1"); 
    c1->cd();

    TH1* h1 = dynamic_cast<TH1*>(file->Get(Form("h_eff_%s_mu_pt", sample_name.c_str()))); 
    h1->SetLineWidth(2);
    h1->SetMarkerStyle(20);
    h1->SetMarkerSize(1.2);
    h1->SetLineColor(kRed);
    h1->SetMarkerColor(h1->GetLineColor());
    h1->GetYaxis()->SetRangeUser(-0.05, 1.1);
    TH1* h2 = dynamic_cast<TH1*>(file->Get(Form("h_eff_%s_el_pt", sample_name.c_str()))); 
    h2->SetLineWidth(2);
    h2->SetMarkerStyle(22);
    h2->SetMarkerSize(1.2);
    h2->SetLineColor(kBlue);
    h2->SetMarkerColor(h2->GetLineColor());
    h2->GetYaxis()->SetRangeUser(-0.05, 1.1);

    h1->Draw();
    h2->Draw("sames");

    std::cout << "fitting first histo...\n";

    TF1* mfunc = new TF1("mfitf", mfitf, 20, 200, 3);
    mfunc->SetParameters(0.5, 0.5, 20);
    mfunc->SetLineColor(kBlack);
    mfunc->SetLineWidth(2);
    mfunc->SetParNames("offset", "normalization", "constant");
    h1->Fit(mfunc, "r", "same");

    std::cout << std::endl;
    std::cout << "chi2/ndof: " << mfunc->GetChisquare() << "/" << mfunc->GetNDF() << std::endl;
    std::cout << "prob: " << mfunc->GetProb() << std::endl;
    std::cout << std::endl;

    std::cout << "fitting second histo...\n";

    TF1* efunc = new TF1("efitf", efitf, 20, 200, 3);
    efunc->SetParameters(0.7, 0.5, 10);
    efunc->SetLineColor(kBlack);
    efunc->SetLineWidth(2);
    efunc->SetParNames("offset", "normalization", "constant");
    h2->Fit(efunc, "r", "same");

    std::cout << std::endl;
    std::cout << "chi2/ndof: " << efunc->GetChisquare() << "/" << efunc->GetNDF() << std::endl;
    std::cout << "prob: " << efunc->GetProb() << std::endl;
    std::cout << std::endl;

    std::cout << "saving histo...\n";

    TLegend* legend = new TLegend(0.6, 0.3, 0.9, 0.5);
    legend->AddEntry(h1, "Muons"    , "p");
    legend->AddEntry(h2, "Electrons", "p");
    legend->SetFillColor(0);
    legend->Draw("sames");

    CTable t1;
    double* params1 = efunc->GetParameters(); 
    double* errors1 = efunc->GetParErrors(); 
    double* params2 = mfunc->GetParameters(); 
    double* errors2 = mfunc->GetParErrors(); 
    t1.useTitle();
    t1.setTitle("lepton eff fit");
    t1.setTable() (                                        "Electrons",                               "Muons")
                  ("eps_infty" , rt::pm(params1[0], errors1[0], "1.3"), rt::pm(params2[0], errors2[0], "1.3"))
                  ("eps_C"     , rt::pm(params1[1], errors1[1], "1.3"), rt::pm(params2[1], errors2[1], "1.3"))
                  ("sigma, GeV", rt::pm(params1[2], errors1[2], "1.3"), rt::pm(params2[2], errors2[2], "1.3"));
    t1.print();

    c1->Draw();
    c1->Print(Form("plots/outreach/lepEfficiency_%s.pdf" , sample_name.c_str()));
    c1->Print(Form("plots/outreach/lepEfficiency_%s.root", sample_name.c_str()));

	// save fits back to file
	file->Write();
	file->Close();
}

// lep eff ID fit
void FitLepIdEfficiencyCurve(const std::string& sample_name) 
{
    gStyle->SetOptStat("");
    rt::SetTDRStyle();

    TFile* file = TFile::Open(Form("plots/outreach/%s_or.root", sample_name.c_str()), "UPDATE");
    if (!file || file->IsZombie())
    {
        cout << "FitHtTurnOnCurve: file not found!" << endl;
        return;
    }
    file->ls();

    TCanvas* c1 = new TCanvas("c1", "c1"); 
    c1->cd();

    TH1* h1 = dynamic_cast<TH1*>(file->Get(Form("h_eff_%s_mu_id_pt", sample_name.c_str()))); 
    h1->SetLineWidth(2);
    h1->SetMarkerStyle(20);
    h1->SetMarkerSize(1.2);
    h1->SetLineColor(kRed);
    h1->SetMarkerColor(h1->GetLineColor());
    h1->GetYaxis()->SetRangeUser(-0.05, 1.1);
    TH1* h2 = dynamic_cast<TH1*>(file->Get(Form("h_eff_%s_el_id_pt", sample_name.c_str()))); 
    h2->SetLineWidth(2);
    h2->SetMarkerStyle(22);
    h2->SetMarkerSize(1.2);
    h2->SetLineColor(kBlue);
    h2->SetMarkerColor(h2->GetLineColor());
    h2->GetYaxis()->SetRangeUser(-0.05, 1.1);

    h1->Draw();
    h2->Draw("sames");

    std::cout << "fitting first histo...\n";

    TF1* mfunc = new TF1("mfitf", mfitf, 20, 200, 3);
    mfunc->SetParameters(0.5, 0.5, 20);
    mfunc->SetLineColor(kBlack);
    mfunc->SetLineWidth(2);
    mfunc->SetParNames("offset", "normalization", "constant");
    h1->Fit(mfunc, "r", "same");

    std::cout << std::endl;
    std::cout << "chi2/ndof: " << mfunc->GetChisquare() << "/" << mfunc->GetNDF() << std::endl;
    std::cout << "prob: " << mfunc->GetProb() << std::endl;
    std::cout << std::endl;

    std::cout << "fitting second histo...\n";

    TF1* efunc = new TF1("efitf", efitf, 20, 200, 3);
    efunc->SetParameters(0.7, 0.25, 10);
    efunc->SetLineColor(kBlack);
    efunc->SetLineWidth(2);
    efunc->SetParNames("offset", "normalization", "constant");
    h2->Fit(efunc, "r", "same");

    std::cout << std::endl;
    std::cout << "chi2/ndof: " << efunc->GetChisquare() << "/" << efunc->GetNDF() << std::endl;
    std::cout << "prob: " << efunc->GetProb() << std::endl;
    std::cout << std::endl;

    std::cout << "saving histo...\n";

    TLegend* legend = new TLegend(0.6, 0.3, 0.9, 0.5);
    legend->AddEntry(h1, "muons"    , "p");
    legend->AddEntry(h2, "electrons", "p");
    legend->SetFillColor(0);
    legend->Draw("sames");

    CTable t1;
    double* params1 = efunc->GetParameters(); 
    double* errors1 = efunc->GetParErrors(); 
    double* params2 = mfunc->GetParameters(); 
    double* errors2 = mfunc->GetParErrors(); 
    t1.useTitle();
    t1.setTitle("lepton ID eff fit");
    t1.setTable() (                                        "Electrons",                               "Muons")
                  ("eps_infty" , rt::pm(params1[0], errors1[0], "1.3"), rt::pm(params2[0], errors2[0], "1.3"))
                  ("eps_C"     , rt::pm(params1[1], errors1[1], "1.3"), rt::pm(params2[1], errors2[1], "1.3"))
                  ("sigma, GeV", rt::pm(params1[2], errors1[2], "1.3"), rt::pm(params2[2], errors2[2], "1.3"));
    t1.print();

    c1->Draw();
    c1->Print(Form("plots/outreach/lepIdEfficiency_%s.pdf" , sample_name.c_str()));
    c1->Print(Form("plots/outreach/lepIdEfficiency_%s.root", sample_name.c_str()));

	// save fits back to file
	file->Write();
	file->Close();
}

void FitLepIsoEfficiencyCurve(const std::string& sample_name) 
{
    gStyle->SetOptStat("");
    rt::SetTDRStyle();

    TFile* file = TFile::Open(Form("plots/outreach/%s_or.root", sample_name.c_str()), "UPDATE");
    if (!file || file->IsZombie())
    {
        cout << "FitHtTurnOnCurve: file not found!" << endl;
        return;
    }
    file->ls();

    TCanvas* c1 = new TCanvas("c1", "c1"); 
    c1->cd();

    TH1* h1 = dynamic_cast<TH1*>(file->Get(Form("h_eff_%s_mu_iso_pt", sample_name.c_str()))); 
    h1->SetLineWidth(2);
    h1->SetMarkerStyle(20);
    h1->SetMarkerSize(1.2);
    h1->SetLineColor(kRed);
    h1->SetMarkerColor(h1->GetLineColor());
    h1->GetYaxis()->SetRangeUser(-0.05, 1.1);
    TH1* h2 = dynamic_cast<TH1*>(file->Get(Form("h_eff_%s_el_iso_pt", sample_name.c_str()))); 
    h2->SetLineWidth(2);
    h2->SetMarkerStyle(22);
    h2->SetMarkerSize(1.2);
    h2->SetLineColor(kBlue);
    h2->SetMarkerColor(h2->GetLineColor());
    h2->GetYaxis()->SetRangeUser(-0.05, 1.1);

    h1->Draw();
    h2->Draw("sames");

    std::cout << "fitting first histo...\n";

    TF1* mfunc = new TF1("mfitf", mfitf, 20, 200, 3);
    mfunc->SetParameters(0.5, 0.5, 20);
    mfunc->SetLineColor(kBlack);
    mfunc->SetLineWidth(2);
    mfunc->SetParNames("offset", "normalization", "constant");
    h1->Fit(mfunc, "r", "same");

    std::cout << std::endl;
    std::cout << "chi2/ndof: " << mfunc->GetChisquare() << "/" << mfunc->GetNDF() << std::endl;
    std::cout << "prob: " << mfunc->GetProb() << std::endl;
    std::cout << std::endl;

    std::cout << "fitting second histo...\n";

    TF1* efunc = new TF1("efitf", efitf, 20, 200, 3);
    efunc->SetParameters(0.7, 0.25, 10);
    efunc->SetLineColor(kBlack);
    efunc->SetLineWidth(2);
    efunc->SetParNames("offset", "normalization", "constant");
    h2->Fit(efunc, "r", "same");

    std::cout << std::endl;
    std::cout << "chi2/ndof: " << efunc->GetChisquare() << "/" << efunc->GetNDF() << std::endl;
    std::cout << "prob: " << efunc->GetProb() << std::endl;
    std::cout << std::endl;

    std::cout << "saving histo...\n";

    TLegend* legend = new TLegend(0.6, 0.3, 0.9, 0.5);
    legend->AddEntry(h1, "muons"    , "p");
    legend->AddEntry(h2, "electrons", "p");
    legend->SetFillColor(0);
    legend->Draw("sames");

    CTable t1;
    double* params1 = efunc->GetParameters(); 
    double* errors1 = efunc->GetParErrors(); 
    double* params2 = mfunc->GetParameters(); 
    double* errors2 = mfunc->GetParErrors(); 
    t1.useTitle();
    t1.setTitle("lepton Iso eff fit");
    t1.setTable() (                                        "Electrons",                               "Muons")
                  ("eps_infty" , rt::pm(params1[0], errors1[0], "1.3"), rt::pm(params2[0], errors2[0], "1.3"))
                  ("eps_C"     , rt::pm(params1[1], errors1[1], "1.3"), rt::pm(params2[1], errors2[1], "1.3"))
                  ("sigma, GeV", rt::pm(params1[2], errors1[2], "1.3"), rt::pm(params2[2], errors2[2], "1.3"));
    t1.print();

    c1->Draw();
    c1->Print(Form("plots/outreach/lepIsoEfficiency_%s.pdf" , sample_name.c_str()));
    c1->Print(Form("plots/outreach/lepIsoEfficiency_%s.root", sample_name.c_str()));

	// save fits back to file
	file->Write();
	file->Close();
}


void CreateOutreachPlots(const std::string& sample_name)
{
    CreateOutreachHists(sample_name);
    FitHtTurnOnCurve(sample_name);
    FitMetTurnOnCurve(sample_name);
    FitBtagEfficiencyCurve(sample_name);
    FitLepEfficiencyCurve(sample_name);
    FitLepIdEfficiencyCurve(sample_name);
    FitLepIsoEfficiencyCurve(sample_name);
}
