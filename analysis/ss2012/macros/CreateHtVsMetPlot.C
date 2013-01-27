#include <string>
#include <iostream>
#include "TCut.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TChain.h"
#include "TGraph.h"
#include "TH2F.h"
#include "rt/TDRStyle.h"
#include "rt/RootTools.h"
#include "SignalRegion.h"
#include "AnalysisType.h"

using namespace std;

//void PrintSummaryYields
void CreateHtVsMetPlot
(
    const std::string& output_path,
    const std::string& signal_region_name, 
    const std::string& analysis_type_name, 
    const std::string& suffix = "png"
)
{
    // set TDR style
    rt::SetTDRStyle();

    // lumi
    const float lumi = 19.5; // fb^-1

    //const ss::SignalRegionType::value_type srt = ss::GetSignalRegionTypeFromName(signal_region_type_name);
    const ss::AnalysisType::value_type at      = ss::GetAnalysisTypeFromName(analysis_type_name);
    const ss::AnalysisTypeInfo at_info         = ss::GetAnalysisTypeInfo(analysis_type_name);
    const ss::SignalRegionInfo sr_info         = ss::GetSignalRegionInfo(signal_region_name, analysis_type_name, "inclusive");

    TChain e1("tree");
    e1.Add(Form("babies/%s/data.root", at_info.short_name.c_str()));
    ss::SetSignalRegionAliases(e1, at);

    // book
    TH2F* h2_ht_vs_pfmet_baseline_njlt4_mm = new TH2F("h2_ht_vs_pfmet_baseline_njlt4_mm", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_njlt4_em = new TH2F("h2_ht_vs_pfmet_baseline_njlt4_em", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_njlt4_ee = new TH2F("h2_ht_vs_pfmet_baseline_njlt4_ee", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_njge4_mm = new TH2F("h2_ht_vs_pfmet_baseline_njge4_mm", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_njge4_em = new TH2F("h2_ht_vs_pfmet_baseline_njge4_em", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_njge4_ee = new TH2F("h2_ht_vs_pfmet_baseline_njge4_ee", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);

    // slection
    TCut selection = Form("is_ss && is_good_lumi && lep_pt && trig && %s", sr_info.name.c_str());

    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_njlt4_mm", selection && "mm && njets<4" , "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_njlt4_em", selection && "em && njets<4" , "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_njlt4_ee", selection && "ee && njets<4" , "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_njge4_mm", selection && "mm && njets>=4", "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_njge4_em", selection && "em && njets>=4", "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_njge4_ee", selection && "ee && njets>=4", "goff");

    // set style
    h2_ht_vs_pfmet_baseline_njlt4_ee->SetMarkerColor(kBlack);
    h2_ht_vs_pfmet_baseline_njlt4_em->SetMarkerColor(kRed);
    h2_ht_vs_pfmet_baseline_njlt4_mm->SetMarkerColor(kBlue);
    h2_ht_vs_pfmet_baseline_njlt4_ee->SetMarkerStyle(24);
    h2_ht_vs_pfmet_baseline_njlt4_em->SetMarkerStyle(25);
    h2_ht_vs_pfmet_baseline_njlt4_mm->SetMarkerStyle(26);
    h2_ht_vs_pfmet_baseline_njlt4_ee->SetMarkerSize(1.7);
    h2_ht_vs_pfmet_baseline_njlt4_em->SetMarkerSize(1.7);
    h2_ht_vs_pfmet_baseline_njlt4_mm->SetMarkerSize(1.7);
    h2_ht_vs_pfmet_baseline_njlt4_ee->SetLineWidth(2);
    h2_ht_vs_pfmet_baseline_njlt4_em->SetLineWidth(2);
    h2_ht_vs_pfmet_baseline_njlt4_mm->SetLineWidth(2);
    h2_ht_vs_pfmet_baseline_njlt4_ee->SetStats(false);
    h2_ht_vs_pfmet_baseline_njlt4_em->SetStats(false);
    h2_ht_vs_pfmet_baseline_njlt4_mm->SetStats(false);

    h2_ht_vs_pfmet_baseline_njge4_ee->SetMarkerColor(kBlack);
    h2_ht_vs_pfmet_baseline_njge4_em->SetMarkerColor(kRed);
    h2_ht_vs_pfmet_baseline_njge4_mm->SetMarkerColor(kBlue);
    h2_ht_vs_pfmet_baseline_njge4_ee->SetMarkerStyle(20);
    h2_ht_vs_pfmet_baseline_njge4_em->SetMarkerStyle(21);
    h2_ht_vs_pfmet_baseline_njge4_mm->SetMarkerStyle(22);
    h2_ht_vs_pfmet_baseline_njge4_ee->SetMarkerSize(1.7);
    h2_ht_vs_pfmet_baseline_njge4_em->SetMarkerSize(1.7);
    h2_ht_vs_pfmet_baseline_njge4_mm->SetMarkerSize(1.7);
    h2_ht_vs_pfmet_baseline_njge4_ee->SetLineWidth(2);
    h2_ht_vs_pfmet_baseline_njge4_em->SetLineWidth(2);
    h2_ht_vs_pfmet_baseline_njge4_mm->SetLineWidth(2);
    h2_ht_vs_pfmet_baseline_njge4_ee->SetStats(false);
    h2_ht_vs_pfmet_baseline_njge4_em->SetStats(false);
    h2_ht_vs_pfmet_baseline_njge4_mm->SetStats(false);

    // draw the hists
    TCanvas* c1 = new TCanvas("c1", "c1");
    h2_ht_vs_pfmet_baseline_njlt4_ee->Draw();
    h2_ht_vs_pfmet_baseline_njlt4_em->Draw("sames");
    h2_ht_vs_pfmet_baseline_njlt4_mm->Draw("sames");
    h2_ht_vs_pfmet_baseline_njge4_ee->Draw("sames");
    h2_ht_vs_pfmet_baseline_njge4_em->Draw("sames");
    h2_ht_vs_pfmet_baseline_njge4_mm->Draw("sames");

    // legend
    TLegend* l1 = new TLegend(0.65, 0.50, 0.95, 0.88);
    l1->SetFillColor(0);  // 0 makes it the background clear on the pad
    l1->SetFillStyle(0);
    l1->SetBorderSize(0);
    //l1->SetTextSize(0.1);
    l1->AddEntry(h2_ht_vs_pfmet_baseline_njlt4_ee, "ee (2 #leq # jets < 4)"    , "p");
    l1->AddEntry(h2_ht_vs_pfmet_baseline_njlt4_em, "e#mu (2 #leq # jets < 4)"  , "p");
    l1->AddEntry(h2_ht_vs_pfmet_baseline_njlt4_mm, "#mu#mu (2 #leq # jets < 4)", "p");
    l1->AddEntry(h2_ht_vs_pfmet_baseline_njge4_ee, "ee (# jets #geq 4)"        , "p");
    l1->AddEntry(h2_ht_vs_pfmet_baseline_njge4_em, "e#mu (# jets #geq 4)"      , "p");
    l1->AddEntry(h2_ht_vs_pfmet_baseline_njge4_mm, "#mu#mu (# jets #geq 4)"    , "p");
    l1->Draw();

    // cut out region
    const int n1 = 12;
    const float ht_baseline = at==ss::AnalysisType::high_pt ? 80.0 : 250;
    float x1[n1], y1[n1];
    for (Int_t i=0;i<n1;i++)
    {
        x1[i] = ht_baseline; 
        y1[i] = i*50;
    }
    TGraph* g1 = new TGraph(n1,x1,y1);
    g1->SetLineColor(kWhite);
    g1->SetLineWidth(0);
    g1->SetLineWidth(7500);
    g1->SetFillStyle(3005);
    g1->Draw();

    //const int n2=13;
    //float x2[n2], y2[n2];
    //for (Int_t i=0;i<n2;i++)
    //{
    //    x2[i] = i*100;
    //  y2[i] = 30; 
    //  cout << Form("x2 %f y2 %f", x2[i], y2[i]) << endl;
    //}
    //TGraph* g2 = new TGraph(n2,x2,y2);
    //g2->SetLineColor(kBlack);
    //g2->SetFillColor(kBlack);
    //g2->SetLineWidth(0);
    ////g2->SetLineWidth(7500);
    //g2->SetFillStyle(3005);
    //g2->Draw();

    cout << "ee nj2 entried = " << h2_ht_vs_pfmet_baseline_njlt4_ee->GetEntries() << endl;
    cout << "em nj2 entried = " << h2_ht_vs_pfmet_baseline_njlt4_em->GetEntries() << endl;
    cout << "mm nj2 entried = " << h2_ht_vs_pfmet_baseline_njlt4_mm->GetEntries() << endl;
    cout << "ee nj4 entried = " << h2_ht_vs_pfmet_baseline_njge4_ee->GetEntries() << endl;
    cout << "em nj4 entried = " << h2_ht_vs_pfmet_baseline_njge4_em->GetEntries() << endl;
    cout << "mm nj4 entried = " << h2_ht_vs_pfmet_baseline_njge4_mm->GetEntries() << endl;
    cout << "ll entried = " << (h2_ht_vs_pfmet_baseline_njlt4_ee->GetEntries() + h2_ht_vs_pfmet_baseline_njge4_ee->GetEntries() +
                                h2_ht_vs_pfmet_baseline_njlt4_em->GetEntries() + h2_ht_vs_pfmet_baseline_njge4_em->GetEntries() +
                                h2_ht_vs_pfmet_baseline_njlt4_mm->GetEntries() + h2_ht_vs_pfmet_baseline_njge4_mm->GetEntries()) << endl;

    if (!suffix.empty())
    {
        const char* file = Form("plots/%s/%s/%s/HtVsMET_%s_%s.%s", output_path.c_str(), at_info.name.c_str(), "inclusive", at_info.short_name.c_str(), sr_info.name.c_str(), suffix.c_str()); 
        c1->Print(file);
    }
}
