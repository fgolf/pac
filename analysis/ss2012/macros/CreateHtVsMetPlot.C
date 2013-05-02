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
    ss::SetSignalRegionAliases(e1, at, /*apply beff sf*/false);

    // book
    TH2F* h2_ht_vs_pfmet_baseline_njlt4_mm = new TH2F("h2_ht_vs_pfmet_baseline_njlt4_mm", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_njlt4_em = new TH2F("h2_ht_vs_pfmet_baseline_njlt4_em", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_njlt4_ee = new TH2F("h2_ht_vs_pfmet_baseline_njlt4_ee", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_njge4_mm = new TH2F("h2_ht_vs_pfmet_baseline_njge4_mm", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_njge4_em = new TH2F("h2_ht_vs_pfmet_baseline_njge4_em", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_njge4_ee = new TH2F("h2_ht_vs_pfmet_baseline_njge4_ee", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);

    TH2F* h2_ht_vs_pfmet_baseline_njlt4_nb0 = new TH2F("h2_ht_vs_pfmet_baseline_njlt4_nb0", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_njlt4_nb1 = new TH2F("h2_ht_vs_pfmet_baseline_njlt4_nb1", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_njlt4_nb2 = new TH2F("h2_ht_vs_pfmet_baseline_njlt4_nb2", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_njge4_nb0 = new TH2F("h2_ht_vs_pfmet_baseline_njge4_nb0", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_njge4_nb1 = new TH2F("h2_ht_vs_pfmet_baseline_njge4_nb1", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_njge4_nb2 = new TH2F("h2_ht_vs_pfmet_baseline_njge4_nb2", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);

    TH2F* h2_ht_vs_pfmet_baseline_nb0_mm = new TH2F("h2_ht_vs_pfmet_baseline_nb0_mm", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_nb0_em = new TH2F("h2_ht_vs_pfmet_baseline_nb0_em", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_nb0_ee = new TH2F("h2_ht_vs_pfmet_baseline_nb0_ee", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_nb1_mm = new TH2F("h2_ht_vs_pfmet_baseline_nb1_mm", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_nb1_em = new TH2F("h2_ht_vs_pfmet_baseline_nb1_em", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_nb1_ee = new TH2F("h2_ht_vs_pfmet_baseline_nb1_ee", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_nb2_mm = new TH2F("h2_ht_vs_pfmet_baseline_nb2_mm", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_nb2_em = new TH2F("h2_ht_vs_pfmet_baseline_nb2_em", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);
    TH2F* h2_ht_vs_pfmet_baseline_nb2_ee = new TH2F("h2_ht_vs_pfmet_baseline_nb2_ee", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi), 1500, 0, 1500, 550, 0, 550);

    // slection
    TCut selection = Form("is_ss && lep_pt && %s", sr_info.name.c_str());

    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_njlt4_mm", selection && "mm && njets<4" , "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_njlt4_em", selection && "em && njets<4" , "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_njlt4_ee", selection && "ee && njets<4" , "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_njge4_mm", selection && "mm && njets>=4", "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_njge4_em", selection && "em && njets>=4", "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_njge4_ee", selection && "ee && njets>=4", "goff");

    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_nb0_mm", selection && "mm && nbtags==0", "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_nb0_em", selection && "em && nbtags==0", "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_nb0_ee", selection && "ee && nbtags==0", "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_nb1_mm", selection && "mm && nbtags==1", "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_nb1_em", selection && "em && nbtags==1", "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_nb1_ee", selection && "ee && nbtags==1", "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_nb2_mm", selection && "mm && nbtags>=2", "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_nb2_em", selection && "em && nbtags>=2", "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_nb2_ee", selection && "ee && nbtags>=2", "goff");

    TH2F* h2_ht_vs_pfmet_baseline_nb0 = dynamic_cast<TH2F*>(rt::AddHists(h2_ht_vs_pfmet_baseline_nb0_mm, h2_ht_vs_pfmet_baseline_nb0_em, h2_ht_vs_pfmet_baseline_nb0_ee, "h2_ht_vs_pfmet_baseline_nb0", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi)));
    TH2F* h2_ht_vs_pfmet_baseline_nb1 = dynamic_cast<TH2F*>(rt::AddHists(h2_ht_vs_pfmet_baseline_nb1_mm, h2_ht_vs_pfmet_baseline_nb1_em, h2_ht_vs_pfmet_baseline_nb1_ee, "h2_ht_vs_pfmet_baseline_nb1", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi)));
    TH2F* h2_ht_vs_pfmet_baseline_nb2 = dynamic_cast<TH2F*>(rt::AddHists(h2_ht_vs_pfmet_baseline_nb2_mm, h2_ht_vs_pfmet_baseline_nb2_em, h2_ht_vs_pfmet_baseline_nb2_ee, "h2_ht_vs_pfmet_baseline_nb2", Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %2.1f fb^{-1};H_{T} (GeV); E_{T}^{miss} (GeV)", lumi)));

    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_njlt4_nb0", selection && "njets<4  && nbtags==0", "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_njlt4_nb1", selection && "njets<4  && nbtags==1", "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_njlt4_nb2", selection && "njets<4  && nbtags>=2", "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_njge4_nb0", selection && "njets>=4 && nbtags==0", "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_njge4_nb1", selection && "njets>=4 && nbtags==1", "goff");
    e1.Draw("pfmet:ht>>h2_ht_vs_pfmet_baseline_njge4_nb2", selection && "njets>=4 && nbtags>=2", "goff");

    // set style
    const float marker_size        = 1.6; 
    const unsigned int line_width  = 2; 

    h2_ht_vs_pfmet_baseline_njlt4_ee->SetMarkerColor(kBlack);
    h2_ht_vs_pfmet_baseline_njlt4_em->SetMarkerColor(kRed);
    h2_ht_vs_pfmet_baseline_njlt4_mm->SetMarkerColor(kBlue);
    h2_ht_vs_pfmet_baseline_njlt4_ee->SetMarkerStyle(24);
    h2_ht_vs_pfmet_baseline_njlt4_em->SetMarkerStyle(25);
    h2_ht_vs_pfmet_baseline_njlt4_mm->SetMarkerStyle(26);
    h2_ht_vs_pfmet_baseline_njlt4_ee->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_njlt4_em->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_njlt4_mm->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_njlt4_ee->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_njlt4_em->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_njlt4_mm->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_njlt4_ee->SetStats(false);
    h2_ht_vs_pfmet_baseline_njlt4_em->SetStats(false);
    h2_ht_vs_pfmet_baseline_njlt4_mm->SetStats(false);

    h2_ht_vs_pfmet_baseline_njge4_ee->SetMarkerColor(kBlack);
    h2_ht_vs_pfmet_baseline_njge4_em->SetMarkerColor(kRed);
    h2_ht_vs_pfmet_baseline_njge4_mm->SetMarkerColor(kBlue);
    h2_ht_vs_pfmet_baseline_njge4_ee->SetMarkerStyle(20);
    h2_ht_vs_pfmet_baseline_njge4_em->SetMarkerStyle(21);
    h2_ht_vs_pfmet_baseline_njge4_mm->SetMarkerStyle(22);
    h2_ht_vs_pfmet_baseline_njge4_ee->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_njge4_em->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_njge4_mm->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_njge4_ee->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_njge4_em->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_njge4_mm->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_njge4_ee->SetStats(false);
    h2_ht_vs_pfmet_baseline_njge4_em->SetStats(false);
    h2_ht_vs_pfmet_baseline_njge4_mm->SetStats(false);

    h2_ht_vs_pfmet_baseline_nb0_ee->SetMarkerColor(kBlack);
    h2_ht_vs_pfmet_baseline_nb0_em->SetMarkerColor(kRed);
    h2_ht_vs_pfmet_baseline_nb0_mm->SetMarkerColor(kBlue);
    h2_ht_vs_pfmet_baseline_nb0_ee->SetMarkerStyle(24);
    h2_ht_vs_pfmet_baseline_nb0_em->SetMarkerStyle(25);
    h2_ht_vs_pfmet_baseline_nb0_mm->SetMarkerStyle(26);
    h2_ht_vs_pfmet_baseline_nb0_ee->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_nb0_em->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_nb0_mm->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_nb0_ee->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_nb0_em->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_nb0_mm->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_nb0_ee->SetStats(false);
    h2_ht_vs_pfmet_baseline_nb0_em->SetStats(false);
    h2_ht_vs_pfmet_baseline_nb0_mm->SetStats(false);

    h2_ht_vs_pfmet_baseline_nb1_ee->SetMarkerColor(kBlack);
    h2_ht_vs_pfmet_baseline_nb1_em->SetMarkerColor(kRed);
    h2_ht_vs_pfmet_baseline_nb1_mm->SetMarkerColor(kBlue);
    h2_ht_vs_pfmet_baseline_nb1_ee->SetMarkerStyle(20);
    h2_ht_vs_pfmet_baseline_nb1_em->SetMarkerStyle(21);
    h2_ht_vs_pfmet_baseline_nb1_mm->SetMarkerStyle(22);
    h2_ht_vs_pfmet_baseline_nb1_ee->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_nb1_em->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_nb1_mm->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_nb1_ee->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_nb1_em->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_nb1_mm->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_nb1_ee->SetStats(false);
    h2_ht_vs_pfmet_baseline_nb1_em->SetStats(false);
    h2_ht_vs_pfmet_baseline_nb1_mm->SetStats(false);

    h2_ht_vs_pfmet_baseline_nb2_ee->SetMarkerColor(kGray+2);
    h2_ht_vs_pfmet_baseline_nb2_em->SetMarkerColor(kRed+3);
    h2_ht_vs_pfmet_baseline_nb2_mm->SetMarkerColor(kAzure+7);
    h2_ht_vs_pfmet_baseline_nb2_ee->SetMarkerStyle(20);
    h2_ht_vs_pfmet_baseline_nb2_em->SetMarkerStyle(21);
    h2_ht_vs_pfmet_baseline_nb2_mm->SetMarkerStyle(22);
    h2_ht_vs_pfmet_baseline_nb2_ee->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_nb2_em->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_nb2_mm->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_nb2_ee->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_nb2_em->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_nb2_mm->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_nb2_ee->SetStats(false);
    h2_ht_vs_pfmet_baseline_nb2_em->SetStats(false);
    h2_ht_vs_pfmet_baseline_nb2_mm->SetStats(false);

    h2_ht_vs_pfmet_baseline_nb0->SetMarkerColor(kBlack);
    h2_ht_vs_pfmet_baseline_nb1->SetMarkerColor(kRed);
    h2_ht_vs_pfmet_baseline_nb2->SetMarkerColor(kBlue);
    h2_ht_vs_pfmet_baseline_nb0->SetMarkerStyle(20);
    h2_ht_vs_pfmet_baseline_nb1->SetMarkerStyle(21);
    h2_ht_vs_pfmet_baseline_nb2->SetMarkerStyle(22);
    h2_ht_vs_pfmet_baseline_nb0->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_nb1->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_nb2->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_nb0->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_nb1->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_nb2->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_nb0->SetStats(false);
    h2_ht_vs_pfmet_baseline_nb1->SetStats(false);
    h2_ht_vs_pfmet_baseline_nb2->SetStats(false);

    h2_ht_vs_pfmet_baseline_njlt4_nb0->SetMarkerColor(kBlack);
    h2_ht_vs_pfmet_baseline_njlt4_nb1->SetMarkerColor(kRed);
    h2_ht_vs_pfmet_baseline_njlt4_nb2->SetMarkerColor(kBlue);
    h2_ht_vs_pfmet_baseline_njlt4_nb0->SetMarkerStyle(24);
    h2_ht_vs_pfmet_baseline_njlt4_nb1->SetMarkerStyle(25);
    h2_ht_vs_pfmet_baseline_njlt4_nb2->SetMarkerStyle(26);
    h2_ht_vs_pfmet_baseline_njlt4_nb0->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_njlt4_nb1->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_njlt4_nb2->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_njlt4_nb0->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_njlt4_nb1->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_njlt4_nb2->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_njlt4_nb0->SetStats(false);
    h2_ht_vs_pfmet_baseline_njlt4_nb1->SetStats(false);
    h2_ht_vs_pfmet_baseline_njlt4_nb2->SetStats(false);

    h2_ht_vs_pfmet_baseline_njge4_nb0->SetMarkerColor(kBlack);
    h2_ht_vs_pfmet_baseline_njge4_nb1->SetMarkerColor(kRed);
    h2_ht_vs_pfmet_baseline_njge4_nb2->SetMarkerColor(kBlue);
    h2_ht_vs_pfmet_baseline_njge4_nb0->SetMarkerStyle(20);
    h2_ht_vs_pfmet_baseline_njge4_nb1->SetMarkerStyle(21);
    h2_ht_vs_pfmet_baseline_njge4_nb2->SetMarkerStyle(22);
    h2_ht_vs_pfmet_baseline_njge4_nb0->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_njge4_nb1->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_njge4_nb2->SetMarkerSize(marker_size);
    h2_ht_vs_pfmet_baseline_njge4_nb0->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_njge4_nb1->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_njge4_nb2->SetLineWidth(line_width);
    h2_ht_vs_pfmet_baseline_njge4_nb0->SetStats(false);
    h2_ht_vs_pfmet_baseline_njge4_nb1->SetStats(false);
    h2_ht_vs_pfmet_baseline_njge4_nb2->SetStats(false);

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

    TLegend* l2 = new TLegend(0.70, 0.50, 0.95, 0.88);
    l2->SetFillColor(0);  // 0 makes it the background clear on the pad
    l2->SetFillStyle(0);
    l2->SetBorderSize(0);
    //l2->SetTextSize(0.1);
    l2->AddEntry(h2_ht_vs_pfmet_baseline_nb0_ee, "ee (# btags = 0)"       , "p");
    l2->AddEntry(h2_ht_vs_pfmet_baseline_nb0_em, "e#mu (# btags = 0)"     , "p");
    l2->AddEntry(h2_ht_vs_pfmet_baseline_nb0_mm, "#mu#mu (# btags = 0)"   , "p");
    l2->AddEntry(h2_ht_vs_pfmet_baseline_nb1_ee, "ee (# btags = 1)"       , "p");
    l2->AddEntry(h2_ht_vs_pfmet_baseline_nb1_em, "e#mu (# btags = 1)"     , "p");
    l2->AddEntry(h2_ht_vs_pfmet_baseline_nb1_mm, "#mu#mu (# btags = 1)"   , "p");
    l2->AddEntry(h2_ht_vs_pfmet_baseline_nb2_ee, "ee (# btags #geq 2)"    , "p");
    l2->AddEntry(h2_ht_vs_pfmet_baseline_nb2_em, "e#mu (# btags #geq 2)"  , "p");
    l2->AddEntry(h2_ht_vs_pfmet_baseline_nb2_mm, "#mu#mu (# btags #geq 2)", "p");

    TLegend* l3 = new TLegend(0.75, 0.72, 0.95, 0.88);
    l3->SetFillColor(0);  // 0 makes it the background clear on the pad
    l3->SetFillStyle(0);
    l3->SetBorderSize(0);
    //l2->SetTextSize(0.1);
    l3->AddEntry(h2_ht_vs_pfmet_baseline_nb0, "# btags = 0"   , "p");
    l3->AddEntry(h2_ht_vs_pfmet_baseline_nb1, "# btags = 1"   , "p");
    l3->AddEntry(h2_ht_vs_pfmet_baseline_nb2, "# btags #geq 2", "p");

    TLegend* l4 = new TLegend(0.65, 0.50, 0.95, 0.88);
    l4->SetFillColor(0);  // 0 makes it the background clear on the pad
    l4->SetFillStyle(0);
    l4->SetBorderSize(0);
    //l4->SetTextSize(0.1);
    l4->AddEntry(h2_ht_vs_pfmet_baseline_njlt4_nb0, "# btags = 0, 2 #leq # jets < 4"   , "p");
    l4->AddEntry(h2_ht_vs_pfmet_baseline_njlt4_nb1, "# btags = 1, 2 #leq # jets < 4"   , "p");
    l4->AddEntry(h2_ht_vs_pfmet_baseline_njlt4_nb2, "# btags #geq 2, 2 #leq # jets < 4", "p");
    l4->AddEntry(h2_ht_vs_pfmet_baseline_njge4_nb0, "# btags = 0, # jets #geq 4"       , "p");
    l4->AddEntry(h2_ht_vs_pfmet_baseline_njge4_nb1, "# btags = 1, # jets #geq 4"       , "p");
    l4->AddEntry(h2_ht_vs_pfmet_baseline_njge4_nb2, "# btags #geq 2, # jets #geq 4"     , "p");

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
    g1->SetFillColor(kBlack);
    g1->SetLineWidth(7500);
    g1->SetFillStyle(3005);
    g1->Draw();

    const int n2=6;
    float x2[n2], y2[n2];
    for (Int_t i=0;i<n2;i++)
    {
        x2[i] = i*100;
        y2[i] = 30; 
        //cout << Form("x2 %f y2 %f", x2[i], y2[i]) << endl;
    }
    TGraph* g2 = new TGraph(n2,x2,y2);
    g2->SetLineColor(kWhite);
    g2->SetFillColor(kBlack);
    g2->SetLineWidth(-7500);
    g2->SetFillStyle(3005);
    g2->Draw();

    // draw the hists
    TCanvas* c1 = new TCanvas("c1", "c1");
    h2_ht_vs_pfmet_baseline_njlt4_ee->Draw();
    h2_ht_vs_pfmet_baseline_njlt4_em->Draw("sames");
    h2_ht_vs_pfmet_baseline_njlt4_mm->Draw("sames");
    h2_ht_vs_pfmet_baseline_njge4_ee->Draw("sames");
    h2_ht_vs_pfmet_baseline_njge4_em->Draw("sames");
    h2_ht_vs_pfmet_baseline_njge4_mm->Draw("sames");
    g1->Draw();
    g2->Draw();
    l1->Draw();

    TCanvas* c2 = new TCanvas("c2", "c2");
    h2_ht_vs_pfmet_baseline_nb0_ee->Draw();
    h2_ht_vs_pfmet_baseline_nb0_em->Draw("sames");
    h2_ht_vs_pfmet_baseline_nb0_mm->Draw("sames");
    h2_ht_vs_pfmet_baseline_nb1_ee->Draw("sames");
    h2_ht_vs_pfmet_baseline_nb1_em->Draw("sames");
    h2_ht_vs_pfmet_baseline_nb1_mm->Draw("sames");
    h2_ht_vs_pfmet_baseline_nb2_ee->Draw("sames");
    h2_ht_vs_pfmet_baseline_nb2_em->Draw("sames");
    h2_ht_vs_pfmet_baseline_nb2_mm->Draw("sames");
    g1->Draw();
    g2->Draw();
    l2->Draw();

    TCanvas* c3 = new TCanvas("c3", "c3");
    h2_ht_vs_pfmet_baseline_nb0->Draw();
    h2_ht_vs_pfmet_baseline_nb1->Draw("sames");
    h2_ht_vs_pfmet_baseline_nb2->Draw("sames");
    g1->Draw();
    g2->Draw();
    l3->Draw();

    // draw the hists
    TCanvas* c4 = new TCanvas("c4", "c4");
    h2_ht_vs_pfmet_baseline_njlt4_nb0->Draw();
    h2_ht_vs_pfmet_baseline_njlt4_nb1->Draw("sames");
    h2_ht_vs_pfmet_baseline_njlt4_nb2->Draw("sames");
    h2_ht_vs_pfmet_baseline_njge4_nb0->Draw("sames");
    h2_ht_vs_pfmet_baseline_njge4_nb1->Draw("sames");
    h2_ht_vs_pfmet_baseline_njge4_nb2->Draw("sames");
    g1->Draw();
    g2->Draw();
    l4->Draw();

    cout << "ee nj2 entried = " << h2_ht_vs_pfmet_baseline_njlt4_ee->GetEntries() << endl;
    cout << "em nj2 entried = " << h2_ht_vs_pfmet_baseline_njlt4_em->GetEntries() << endl;
    cout << "mm nj2 entried = " << h2_ht_vs_pfmet_baseline_njlt4_mm->GetEntries() << endl;
    cout << "ee nj4 entried = " << h2_ht_vs_pfmet_baseline_njge4_ee->GetEntries() << endl;
    cout << "em nj4 entried = " << h2_ht_vs_pfmet_baseline_njge4_em->GetEntries() << endl;
    cout << "mm nj4 entried = " << h2_ht_vs_pfmet_baseline_njge4_mm->GetEntries() << endl;
    cout << "ll entried = " << (h2_ht_vs_pfmet_baseline_njlt4_ee->GetEntries() + h2_ht_vs_pfmet_baseline_njge4_ee->GetEntries() +
                                h2_ht_vs_pfmet_baseline_njlt4_em->GetEntries() + h2_ht_vs_pfmet_baseline_njge4_em->GetEntries() +
                                h2_ht_vs_pfmet_baseline_njlt4_mm->GetEntries() + h2_ht_vs_pfmet_baseline_njge4_mm->GetEntries()) << endl;

    cout << "ee nb0 entried = " << h2_ht_vs_pfmet_baseline_nb0_ee->GetEntries() << endl;
    cout << "em nb0 entried = " << h2_ht_vs_pfmet_baseline_nb0_em->GetEntries() << endl;
    cout << "mm nb0 entried = " << h2_ht_vs_pfmet_baseline_nb0_mm->GetEntries() << endl;
    cout << "ee nb1 entried = " << h2_ht_vs_pfmet_baseline_nb1_ee->GetEntries() << endl;
    cout << "em nb1 entried = " << h2_ht_vs_pfmet_baseline_nb1_em->GetEntries() << endl;
    cout << "mm nb1 entried = " << h2_ht_vs_pfmet_baseline_nb1_mm->GetEntries() << endl;
    cout << "ee nb0 entried = " << h2_ht_vs_pfmet_baseline_nb2_ee->GetEntries() << endl;
    cout << "em nb0 entried = " << h2_ht_vs_pfmet_baseline_nb2_em->GetEntries() << endl;
    cout << "mm nb0 entried = " << h2_ht_vs_pfmet_baseline_nb2_mm->GetEntries() << endl;
    cout << "ll entried = " << (h2_ht_vs_pfmet_baseline_nb0_ee->GetEntries() + h2_ht_vs_pfmet_baseline_nb1_ee->GetEntries() + h2_ht_vs_pfmet_baseline_nb2_ee->GetEntries() +
                                h2_ht_vs_pfmet_baseline_nb0_em->GetEntries() + h2_ht_vs_pfmet_baseline_nb1_em->GetEntries() + h2_ht_vs_pfmet_baseline_nb2_em->GetEntries() +
                                h2_ht_vs_pfmet_baseline_nb0_mm->GetEntries() + h2_ht_vs_pfmet_baseline_nb1_mm->GetEntries() + h2_ht_vs_pfmet_baseline_nb2_mm->GetEntries()) << endl;

    cout << "nb0 entried = " << h2_ht_vs_pfmet_baseline_nb0->GetEntries() << endl;
    cout << "nb1 entried = " << h2_ht_vs_pfmet_baseline_nb1->GetEntries() << endl;
    cout << "nb2 entried = " << h2_ht_vs_pfmet_baseline_nb2->GetEntries() << endl;
    cout << "ll entried = " << (h2_ht_vs_pfmet_baseline_nb0->GetEntries() + h2_ht_vs_pfmet_baseline_nb1->GetEntries() + h2_ht_vs_pfmet_baseline_nb2->GetEntries()) << endl;

    if (!suffix.empty())
    {
        c1->Print(Form("plots/%s/%s/%s/HtVsMET_%s_%s_njs.%s"   , output_path.c_str(), at_info.name.c_str(), "inclusive", at_info.short_name.c_str(), sr_info.name.c_str(), suffix.c_str()));
        c2->Print(Form("plots/%s/%s/%s/HtVsMET_%s_%s_nbs_v1.%s", output_path.c_str(), at_info.name.c_str(), "inclusive", at_info.short_name.c_str(), sr_info.name.c_str(), suffix.c_str()));
        c3->Print(Form("plots/%s/%s/%s/HtVsMET_%s_%s_nbs_v2.%s", output_path.c_str(), at_info.name.c_str(), "inclusive", at_info.short_name.c_str(), sr_info.name.c_str(), suffix.c_str()));
        c4->Print(Form("plots/%s/%s/%s/HtVsMET_%s_%s_nbs_v3.%s", output_path.c_str(), at_info.name.c_str(), "inclusive", at_info.short_name.c_str(), sr_info.name.c_str(), suffix.c_str()));
    }
}

void CreateAllHtVsMetPlots()
{
    CreateHtVsMetPlot("AN_draft_19p5fb_v4", "sr0" , "high_pt", "pdf");
    CreateHtVsMetPlot("AN_draft_19p5fb_v4", "sr20", "high_pt", "pdf");
    CreateHtVsMetPlot("AN_draft_19p5fb_v4", "sr0" , "low_pt" , "pdf");
    CreateHtVsMetPlot("AN_draft_19p5fb_v4", "sr20", "low_pt" , "pdf");
    CreateHtVsMetPlot("AN_draft_19p5fb_v4", "sr0" , "vlow_pt", "pdf");
    CreateHtVsMetPlot("AN_draft_19p5fb_v4", "sr20", "vlow_pt", "pdf");
}
