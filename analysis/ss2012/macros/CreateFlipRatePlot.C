#include "rt/RootTools.h"
<<<<<<< HEAD

void PrintFlipRatePlots(const std::string& suffix = "png")
{
	TH2F* h_flip = rt::GetHistFromRootFile("data/flip_rates/ssFL_data_standard_02222013.root", "flipRate");
    h_flip->Draw();
    std::string path = "plots/flip_rates/thesis";
	float lumi = 19.5;

/* 	std::map<std::string, rt::TH1Overlay> p; */
/*  */
/* 	// set style */
/* 	rt::SetTDRStyle(); */
/* 	gStyle->SetCanvasDefH(600); */
/* 	gStyle->SetCanvasDefW(600); */
/* 	gStyle->SetTitleBorderSize(0); */
/*     hc.SetMarkerSize(1.8); */
/*  */
/* 	//std::string title = Form("CMS Preliminary, #sqrt{s} = 8 TeV, #scale[0.6]{#int}Ldt = %3.1f fb^{-1}", lumi); */
/* 	std::string title = Form("Electron Charge Flip Rate, #sqrt{s} = 8 TeV, L_{int} = %3.1f fb^{-1}", lumi); */
/*  */
/*     // FR(#vetices), FR(pt), FR(eta) -- cpfiso03_db */
/*     p["p_flip_vs_pt"] = rt::TH1Overlay(Form("%s;p_{T} (GeV);Charge Flip Rate", title.c_str()), "sb::off lg::top"); */
/*     p["p_flip_vs_pt"].Add(h_flip, kBlue, 2, 20); */
/*     p["p_flip_vs_pt"].SetLegendOption("p"); */
/*     p["p_flip_vs_pt"].SetLegendTextSize(0.042); */

    // cleanup
/*     delete h_flip; */

    // print
    if (suffix=="all")
    {
        rt::Print(p, path, "png");
        rt::Print(p, path, "pdf");
        rt::Print(p, path, "eps");
    }
    else
    {
        rt::Print(p, path, suffix);
    }
=======
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
>>>>>>> 3b3013840b1f7f3d71405ed661c5659a191cb7dd
}
