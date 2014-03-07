#include "rt/RootTools.h"

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
}
