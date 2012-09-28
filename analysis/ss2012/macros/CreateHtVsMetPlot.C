#include <string>
#include <iostream>
#include "TCut.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TChain.h"
#include "TGraph.h"
#include "TH2F.h"
#include "rt/TDRStyle.h"

using namespace std;

void CreateHtVsMetPlot(bool btag2 = true, const std::string& suffix = "png")
{
    // set TDR style
    rt::SetTDRStyle();

    float lumi = 10.45; // fb^-1

    TChain e1("tree");
    e1.Add("babies/data.root");

    TH2F* h2_ht_vs_pfmet_baseline_mm = new TH2F("h2_ht_vs_pfmet_baseline_mm", Form("CMS Preliminary #sqrt{s} = 8 TeV, L_{int} = %2.2f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1000, 0, 1000, 250, 0, 250);
    TH2F* h2_ht_vs_pfmet_baseline_em = new TH2F("h2_ht_vs_pfmet_baseline_em", Form("CMS Preliminary #sqrt{s} = 8 TeV, L_{int} = %2.2f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1000, 0, 1000, 250, 0, 250);
    TH2F* h2_ht_vs_pfmet_baseline_ee = new TH2F("h2_ht_vs_pfmet_baseline_ee", Form("CMS Preliminary #sqrt{s} = 8 TeV, L_{int} = %2.2f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1000, 0, 1000, 250, 0, 250);

    TCut selection = btag2 ? "is_ss && njets>=2 && nbtags>=2 && is_good_lumi" : "is_ss && njets>=2 && is_good_lumi";

    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_mm", selection && "dilep_type==1", "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_em", selection && "dilep_type==2", "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_ee", selection && "dilep_type==3", "goff");

    // set style
    h2_ht_vs_pfmet_baseline_ee->SetMarkerColor(kBlack);
    h2_ht_vs_pfmet_baseline_em->SetMarkerColor(kRed);
    h2_ht_vs_pfmet_baseline_mm->SetMarkerColor(kBlue);
    h2_ht_vs_pfmet_baseline_ee->SetMarkerStyle(20);
    h2_ht_vs_pfmet_baseline_em->SetMarkerStyle(21);
    h2_ht_vs_pfmet_baseline_mm->SetMarkerStyle(22);
    h2_ht_vs_pfmet_baseline_ee->SetMarkerSize(1.6);
    h2_ht_vs_pfmet_baseline_em->SetMarkerSize(1.6);
    h2_ht_vs_pfmet_baseline_mm->SetMarkerSize(1.6);
    h2_ht_vs_pfmet_baseline_ee->SetStats(false);
    h2_ht_vs_pfmet_baseline_em->SetStats(false);
    h2_ht_vs_pfmet_baseline_mm->SetStats(false);

    // draw the hists
    TCanvas* c1 = new TCanvas("c1", "c1");
    h2_ht_vs_pfmet_baseline_ee->Draw();
    h2_ht_vs_pfmet_baseline_em->Draw("same");
    h2_ht_vs_pfmet_baseline_mm->Draw("same");

    // legend
    TLegend* l1 = new TLegend(0.75, 0.65, 0.89, 0.84);
    l1->SetFillColor(0);  // 0 makes it the background clear on the pad
    l1->SetFillStyle(0);
    l1->SetBorderSize(0);
    //l1->SetTextSize(0.1);
    l1->AddEntry(h2_ht_vs_pfmet_baseline_ee, "ee"    , "p");
    l1->AddEntry(h2_ht_vs_pfmet_baseline_em, "e#mu"  , "p");
    l1->AddEntry(h2_ht_vs_pfmet_baseline_mm, "#mu#mu", "p");
    l1->Draw();

    // cut out region
    const int n=6;
    float x1[n], y1[n];
    for (Int_t i=0;i<n;i++)
    {
        x1[i] = 80.0; 
        y1[i] = i*50;
    }
    TGraph* g_implied = new TGraph(n,x1,y1);
    g_implied->SetLineColor(kWhite);
    g_implied->SetLineWidth(0);
    g_implied->SetLineWidth(7500);
    g_implied->SetFillStyle(3005);
    g_implied->Draw();

    cout << "ee entried = " << h2_ht_vs_pfmet_baseline_ee->GetEntries() << endl;
    cout << "em entried = " << h2_ht_vs_pfmet_baseline_em->GetEntries() << endl;
    cout << "mm entried = " << h2_ht_vs_pfmet_baseline_mm->GetEntries() << endl;
    cout << "ll entried = " << (h2_ht_vs_pfmet_baseline_ee->GetEntries() + 
                                h2_ht_vs_pfmet_baseline_em->GetEntries() +
                                h2_ht_vs_pfmet_baseline_mm->GetEntries()) << endl;

    if (!suffix.empty())
    {
        c1->Print(Form("plots/note/HtVsMET_%s.%s", (btag2 ? "baseline" : "ht30met30"), suffix.c_str()));
    }
}
