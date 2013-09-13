#include "rt/RootTools.h"
#include "TCanvas.h"

void PrintFlipRatePlots(const std::string& suffix = "png")
{
	TH2F* h_flip = rt::GetHistFromRootFile<TH2F>("data/flip_rates/ssFL_data_standard_02222013.root", "flipRate");
    h_flip->Draw();
    std::string path = "plots/flip_rates/thesis";
	float lumi = 19.5;
/* 	const std::string title = Form("CMS Preliminary, #sqrt{s} = 8 TeV, #scale[0.6]{#int}Ldt = %3.1f fb^{-1}", lumi); */
	const std::string title = Form("Electron Charge Flip Rate, #sqrt{s} = 8 TeV, L_{int} = %3.1f fb^{-1}", lumi);

	// set style
	rt::SetStyle();
	gStyle->SetTitleOffset(1.5, "y");
	gStyle->SetPadLeftMargin(0.15);
	gStyle->SetPadRightMargin(0.05);
	gStyle->SetLabelSize(0.025, "y");

    // projections
    rt::TH1Container hc;
	hc.Add(rt::MakeProjectionPlot(h_flip, "y", "h_flip_vs_pt" , Form("%s;p_{T} (GeV);Charge Flip Rate", title.c_str())));
	hc.Add(rt::MakeProjectionPlot(h_flip, "x", "h_flip_vs_eta", Form("%s;#eta ;Charge Flip Rate"      , title.c_str())));
    hc.SetMarkerSize(1.3);
    hc.SetMarkerColor(kBlue);
    hc.SetLineColor(kBlack);
    hc.SetMarkerStyle(20);
    hc.SetStats(false);

    // output
    rt::mkdir(path, /*force=*/true);

    TCanvas* c1 = new TCanvas("c1", "c1");
    hc["h_flip_vs_pt"]->Draw();
    c1->Print(Form("%s/%s.%s", path.c_str(), hc["h_flip_vs_pt" ]->GetName(), suffix.c_str()));
    hc["h_flip_vs_eta"]->Draw();
    c1->Print(Form("%s/%s.%s", path.c_str(), hc["h_flip_vs_eta"]->GetName(), suffix.c_str()));
}
