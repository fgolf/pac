#include "RootTools.h"
#include "LanguageTools.h"
#include "TCanvas.h"
#include <limits>
#include <string>
#include <iostream>

TH1F* DrawHist(TChain& chain, const std::string& hist_name, long num_events = std::numeric_limits<long>::max())
{
    std::cout << "Beginning " << hist_name << " on " << chain.GetEntries() << " events..." << std::endl; 
    TH1F* const hist = new TH1F(hist_name.c_str(), "Invariant Dilepton Mass m_{#mu#mu}; m_{#mu#mu} (GeV); # Events", 60, 60, 120);
    hist->Sumw2();
    hist->SetLineWidth(2);
    hist->SetMarkerSize(0.8);
    hist->SetMarkerStyle(20);
    hist->SetMarkerColor(kBlack);
    chain.Draw(Form("hyp_p4.mass()>>%s", hist_name.c_str()), "hyp_type==0 && hyp_lt_charge!=hyp_ll_charge", "goff", num_events);
    std::cout << "Complete " << hist_name << "...\n" << std::endl; 
    return hist;
}

void create_mll_plot()
{
    // get data
    TChain ch_dyll("Events");
    ch_dyll.Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-23/merged_ntuple_1[0-9].root");

    TChain ch_data("Events");
    ch_data.Add("/hadoop/cms/store/group/snt/papers2012/Data2012/CMSSW_5_3_2_patch4_V05-03-24/SingleMu_Run2012A-recover-06Aug2012-v1_AOD/merged/*.root");

    TChain ch_wjets("Events");
    ch_wjets.Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1/V05-03-28/merged_ntuple_1[0-9].root");

    TChain ch_ttjets("Events");
    ch_ttjets.Add("/hadoop/cms/store/group/snt/papers2012/Summer12_53X_MC/TTJets_SemiLeptMGDecays_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A_ext-v1/V05-03-24/merged_ntuple_1[0-9].root");

    // get hists
    rt::TH1Container hc;
    hc.Add(DrawHist(ch_data  , "h_mmm_data"  ));
    hc.Add(DrawHist(ch_dyll  , "h_mmm_dyll"  ));
    hc.Add(DrawHist(ch_wjets , "h_mmm_wjets" ));
    hc.Add(DrawHist(ch_ttjets, "h_mmm_ttjets"));

    // write output
    hc.Write("mll_plots.root");
}

void create_overlay()
{
    rt::TH1Container hc("mll_plots.root");
    
    rt::TH1Overlay p("Invariant Dilepton Mass m_{#mu#mu}; m_{#mu#mu} (GeV); # Events (normalized to unity)", "sb::top lg::right dt::norm");
    p.Add(hc["h_mmm_data"  ], "data"                           , kBlack  );
    p.Add(hc["h_mmm_dyll"  ], "DY #rightarrow ll"              , kRed    );
    p.Add(hc["h_mmm_wjets" ], "W + jets"                       , kBlue   );
    p.Add(hc["h_mmm_ttjets"], "t#bar{t} + jets #right arrow 2l", kGreen+2);

    TCanvas c1("c1", "c1");
    p.Draw();
    c1.Print("mll.png");
}

