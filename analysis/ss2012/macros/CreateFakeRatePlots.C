#include "rt/RootTools.h"
#include "TChain.h"
#include "TEventList.h"
#include "TCut.h"
#include "CTable.h"
#include <string>

using namespace std;

void CountMuonNumDen(TH1* h_num, TH1* h_den, const std::string& title)
{
    cout << h_num->GetTitle() << ", " << h_den->GetTitle() << endl;
    CTable t;
    t.setTitle(title);
    t.useTitle();
    t.setRowLabel("pT  5-10" , 0);
    t.setRowLabel("pT 10-15" , 1);
    t.setRowLabel("pT 15-20" , 2);
    t.setRowLabel("pT 20-25" , 3);
    t.setRowLabel("pT 25-35" , 4);
    t.setColLabel("eta 0-1"  , 0);
    t.setColLabel("eta 1-1.5", 1);
    t.setColLabel("eta 1.5-2", 2);
    t.setColLabel("eta 2-2.5", 3);
    TH2* h2_num = dynamic_cast<TH2*>(h_num);
    TH2* h2_den = dynamic_cast<TH2*>(h_den);
    int num_total = 0;
    int den_total = 0;
    for (int row = 0; row != h2_num->GetYaxis()->GetNbins(); row++)
    {
        for (int col = 0; col != h2_num->GetXaxis()->GetNbins(); col++)
        {
            int num = static_cast<int>(h2_num->GetBinContent(col+1, row+1));
            int den = static_cast<int>(h2_den->GetBinContent(col+1, row+1));
            string count = Form("(%d, %d)", num, den);
            num_total += num;
            den_total += den;
            t.setCell(count, row, col);
        }
    }
    t.print();
    cout << "Total Numerators:   " << num_total << "\tTotal Denominators: " << den_total << endl;
}

void CountElectronNumDen(TH1* h_num, TH1* h_den, const std::string& title)
{
    cout << h_num->GetTitle() << ", " << h_den->GetTitle() << endl;
    CTable t;
    t.setTitle(title);
    t.useTitle();
    t.setRowLabel("pT 10-15" , 0);
    t.setRowLabel("pT 15-20" , 1);
    t.setRowLabel("pT 20-25" , 2);
    t.setRowLabel("pT 25-35" , 3);
    t.setRowLabel("pT 35-55" , 4);
    t.setColLabel("eta 0-1"  , 0);
    t.setColLabel("eta 1-1.5", 1);
    t.setColLabel("eta 1.5-2", 2);
    t.setColLabel("eta 2-2.5", 3);
    TH2* h2_num = dynamic_cast<TH2*>(h_num);
    TH2* h2_den = dynamic_cast<TH2*>(h_den);
    int num_total = 0;
    int den_total = 0;
    for (int row = 0; row != h2_num->GetYaxis()->GetNbins(); row++)
    {
        for (int col = 0; col != h2_num->GetXaxis()->GetNbins(); col++)
        {
            int num = static_cast<int>(h2_num->GetBinContent(col+1, row+1));
            int den = static_cast<int>(h2_den->GetBinContent(col+1, row+1));
            string count = Form("(%d, %d)", num, den);
            num_total += num;
            den_total += den;
            t.setCell(count, row, col);
        }
    }
    t.print();
    cout << "Total Numerators:   " << num_total << "\tTotal Denominators: " << den_total << endl;
}

void PrintMuonFakeRatePlots(const std::string& suffix = "png")
{
	//rt::TH1Container hc("plots/fake_rates/muons_920pb/muons_920pb.root");
    //std::string path = "plots/fake_rates/muons_920pb";
	//float lumi = 0.920;

	//rt::TH1Container hc("plots/fake_rates/muons_5p1/muons_5p1.root");
    //std::string path = "plots/fake_rates/muons_5p1";
	//float lumi = 5.1;

	rt::TH1Container hc("plots/fake_rates/muons_2012ABr/muons_2012ABr.root");
    std::string path = "plots/fake_rates/muons_2012ABr";
	float lumi = 5.2;

	//rt::TH1Container hc("plots/fake_rates/muons_2012Cv2/muons_2012Cv2.root");
    //std::string path = "plots/fake_rates/muons_2012Cv2";
	//float lumi = 3.0;

	//rt::TH1Container hc("plots/fake_rates/muons_8p8fb/muons_8p8fb.root");
    //std::string path = "plots/fake_rates/muons_8p8fb";
	//float lumi = 8.8;

    //std::string path = "plots/fake_rates/data/23May";
	//rt::TH1Container hc("plots/mu_plus/data/mu_plus.root");
    //std::string path = "plots/fake_rates/data/mu_plus";
	//rt::TH1Container hc("plots/mu_minus/data/mu_minus.root");
    //std::string path = "plots/fake_rates/data/mu_minus";
	//rt::TH1Container hc("plots/muons_3p95/data/muons_3p95.root");
    //std::string path = "plots/fake_rates/data/20Jun";
	std::map<std::string, rt::TH1Overlay> p;

	// set style
	rt::SetTDRStyle();
	gStyle->SetTitleBorderSize(0);

	//float lumi = 3.95;
	std::string title = Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %3.2f fb^{-1}", lumi);
	//std::string title = Form("#mu^{+} fake rate, #sqrt{s} = 8 TeV, L_{int} = %3.2f fb^{-1}", lumi);
	//std::string title = Form("#mu^{-} fake rate, #sqrt{s} = 8 TeV, L_{int} = %3.2f fb^{-1}", lumi);

    // Fake Rates
    float max = 0.5;
    Color_t c20 = kRed;
    Color_t c40 = kBlack;
    Color_t c60 = kBlue;

    Style_t s20 = 20;
    Style_t s40 = 22;
    Style_t s60 = 24;

    // FR(#vetices), FR(pt), FR(eta) -- cpfiso03_db
    p["p_mufr_vs_nvtxs"] = rt::TH1Overlay(Form("%s;# vtxs;TL ratio", title.c_str()), "sb::off lg::top_left");
    p["p_mufr_vs_nvtxs"].Add(hc["h_mufr20c_vs_nvtxs"], "away jet p_{T} > 20 GeV", c20, 2, s20);
    p["p_mufr_vs_nvtxs"].Add(hc["h_mufr40c_vs_nvtxs"], "away jet p_{T} > 40 GeV", c40, 2, s40);
    p["p_mufr_vs_nvtxs"].Add(hc["h_mufr60c_vs_nvtxs"], "away jet p_{T} > 60 GeV", c60, 2, s60);
    p["p_mufr_vs_nvtxs"].SetYAxisRange(0, max);
    p["p_mufr_vs_nvtxs"].SetLegendOption("p");
    p["p_mufr_vs_nvtxs"].SetLegendTextSize(0.042);
    p["p_mufr_vs_nvtxs"].AddText("Muons"               , 0.75, 0.835);
    p["p_mufr_vs_nvtxs"].AddText("p^{#mu}_{T} > 20 GeV", 0.75, 0.775);

    p["p_mufr_vs_pt"] = rt::TH1Overlay(Form("%s;p_{T} (GeV);TL ratio", title.c_str()), "sb::off lg::top_left");
    p["p_mufr_vs_pt"].Add(hc["h_mufr20c_vs_pt"], "away jet p_{T} > 20 GeV", c20, 2, s20);
    p["p_mufr_vs_pt"].Add(hc["h_mufr40c_vs_pt"], "away jet p_{T} > 40 GeV", c40, 2, s40);
    p["p_mufr_vs_pt"].Add(hc["h_mufr60c_vs_pt"], "away jet p_{T} > 60 GeV", c60, 2, s60);
    p["p_mufr_vs_pt"].SetYAxisRange(0, max);
    p["p_mufr_vs_pt"].SetLegendOption("p");
    p["p_mufr_vs_pt"].SetLegendTextSize(0.042);
    p["p_mufr_vs_pt"].AddText("Muons", 0.75, 0.835);

    p["p_mufr_vs_eta"] = rt::TH1Overlay(Form("%s;|#eta|;TL ratio", title.c_str()), "sb::off lg::top_left");
    p["p_mufr_vs_eta"].Add(hc["h_mufr20c_vs_eta"], "away jet p_{T} > 20 GeV", c20, 2, s20);
    p["p_mufr_vs_eta"].Add(hc["h_mufr40c_vs_eta"], "away jet p_{T} > 40 GeV", c40, 2, s40);
    p["p_mufr_vs_eta"].Add(hc["h_mufr60c_vs_eta"], "away jet p_{T} > 60 GeV", c60, 2, s60);
    p["p_mufr_vs_eta"].SetYAxisRange(0, max);
    p["p_mufr_vs_eta"].SetLegendOption("p");
    p["p_mufr_vs_eta"].SetLegendTextSize(0.042);
    p["p_mufr_vs_eta"].AddText("Muons"               , 0.75, 0.835);
    p["p_mufr_vs_eta"].AddText("p^{#mu}_{T} > 20 GeV", 0.75, 0.775);

    cout << endl;
    CountMuonNumDen(hc["h_mu_num20c"], hc["h_mu_fo20c"], "#mu count (num, den), away jet p_{T} > 20");
    CountMuonNumDen(hc["h_mu_num40c"], hc["h_mu_fo40c"], "#mu count (num, den), away jet p_{T} > 40");
    CountMuonNumDen(hc["h_mu_num60c"], hc["h_mu_fo60c"], "#mu count (num, den), away jet p_{T} > 60");
    cout << endl;

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

void PrintElectronFakeRatePlots(const std::string& suffix = "png")
{
	//rt::TH1Container hc("plots/electrons/data/electrons.root");
    //std::string path = "plots/fake_rates/data/23May";
	//rt::TH1Container hc("plots/el_plus/data/el_plus.root");
    //std::string path = "plots/fake_rates/data/el_plus";
	//rt::TH1Container hc("plots/el_minus/data/el_minus.root");
    //std::string path = "plots/fake_rates/data/el_minus";
	//rt::TH1Container hc("plots/electrons_3p95/data/electrons_3p95.root");
    //std::string path = "plots/fake_rates/data/20Jun";

	//rt::TH1Container hc("plots/fake_rates/electrons_920pb/electrons_920pb.root");
    //std::string path = "plots/fake_rates/electrons_920pb";
	//float lumi = 0.920;

	//rt::TH1Container hc("plots/fake_rates/electrons_5p1fb/electrons_5p1fb.root");
    //std::string path = "plots/fake_rates/electrons_5p1fb";
	//float lumi = 5.1;

	rt::TH1Container hc("plots/fake_rates/electrons_2012ABr/electrons_2012ABr.root");
    std::string path = "plots/fake_rates/electrons_2012ABr";
	float lumi = 5.2;

	//rt::TH1Container hc("plots/fake_rates/electrons_2012Cv2/electrons_2012Cv2.root");
    //std::string path = "plots/fake_rates/electrons_2012Cv2";
	//float lumi = 3.0;

	//rt::TH1Container hc("plots/fake_rates/electrons_8p8fb/electrons_8p8fb.root");
    //std::string path = "plots/fake_rates/electrons_8p8fb";
	//float lumi = 8.8;


	// set style
	rt::SetTDRStyle();
	gStyle->SetTitleBorderSize(0);

	std::string title = Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %3.2f fb^{-1}", lumi);
	//std::string title = Form("e^{+} fake rate, #sqrt{s} = 8 TeV, L_{int} = %3.2f fb^{-1}", lumi);
	//std::string title = Form("e^{-} fake rate, #sqrt{s} = 8 TeV, L_{int} = %3.2f fb^{-1}", lumi);

    // Fake Rates
    float max = 0.6;
    Color_t c20 = kRed;
    Color_t c40 = kBlack;
    Color_t c60 = kBlue;

    Style_t s20 = 20;
    Style_t s40 = 22;
    Style_t s60 = 24;

    // FR(#vetices), FR(pt), FR(eta) -- cpfiso03_db
	std::map<std::string, rt::TH1Overlay> p;
    p["p_elfr_vs_nvtxs"] = rt::TH1Overlay(Form("%s;# vtxs;TL ratio", title.c_str()), "sb::off lg::top_left");
    p["p_elfr_vs_nvtxs"].Add(hc["h_elfr20c_vs_nvtxs"], "away jet p_{T} > 20 GeV", c20, 2, s20);
    p["p_elfr_vs_nvtxs"].Add(hc["h_elfr40c_vs_nvtxs"], "away jet p_{T} > 40 GeV", c40, 2, s40);
    p["p_elfr_vs_nvtxs"].Add(hc["h_elfr60c_vs_nvtxs"], "away jet p_{T} > 60 GeV", c60, 2, s60);
    p["p_elfr_vs_nvtxs"].SetYAxisRange(0, max);
    p["p_elfr_vs_nvtxs"].SetLegendOption("p");
    p["p_elfr_vs_nvtxs"].SetLegendTextSize(0.042);
    p["p_elfr_vs_nvtxs"].AddText("Electrons"         , 0.75, 0.835);
    p["p_elfr_vs_nvtxs"].AddText("p^{e}_{T} > 20 GeV", 0.75, 0.775);

    p["p_elfr_vs_pt"] = rt::TH1Overlay(Form("%s;p_{T} (GeV);TL ratio", title.c_str()), "sb::off lg::top_left");
    p["p_elfr_vs_pt"].Add(hc["h_elfr20c_vs_pt"], "away jet p_{T} > 20 GeV", c20, 2, s20);
    p["p_elfr_vs_pt"].Add(hc["h_elfr40c_vs_pt"], "away jet p_{T} > 40 GeV", c40, 2, s40);
    p["p_elfr_vs_pt"].Add(hc["h_elfr60c_vs_pt"], "away jet p_{T} > 60 GeV", c60, 2, s60);
    p["p_elfr_vs_pt"].SetYAxisRange(0, max);
    p["p_elfr_vs_pt"].SetLegendOption("p");
    p["p_elfr_vs_pt"].SetLegendTextSize(0.042);
    p["p_elfr_vs_pt"].AddText("Electrons", 0.75, 0.835);

    p["p_elfr_vs_eta"] = rt::TH1Overlay(Form("%s;|#eta|;TL ratio", title.c_str()), "sb::off lg::top_left");
    p["p_elfr_vs_eta"].Add(hc["h_elfr20c_vs_eta"], "away jet p_{T} > 20 GeV", c20, 2, s20);
    p["p_elfr_vs_eta"].Add(hc["h_elfr40c_vs_eta"], "away jet p_{T} > 40 GeV", c40, 2, s40);
    p["p_elfr_vs_eta"].Add(hc["h_elfr60c_vs_eta"], "away jet p_{T} > 60 GeV", c60, 2, s60);
    p["p_elfr_vs_eta"].SetYAxisRange(0, max);
    p["p_elfr_vs_eta"].SetLegendOption("p");
    p["p_elfr_vs_eta"].SetLegendTextSize(0.042);
    p["p_elfr_vs_eta"].AddText("Electrons"         , 0.75, 0.835);
    p["p_elfr_vs_eta"].AddText("p^{e}_{T} > 20 GeV", 0.75, 0.775);

    CountElectronNumDen(hc["h_el_num20c"], hc["h_el_fo20c"], "electron count (num, den), radial iso (E_T > 0.5), away jet p_{T} > 20");
    CountElectronNumDen(hc["h_el_num40c"], hc["h_el_fo40c"], "electron count (num, den), radial iso (E_T > 0.5), away jet p_{T} > 40");
    CountElectronNumDen(hc["h_el_num60c"], hc["h_el_fo60c"], "electron count (num, den), radial iso (E_T > 0.5), away jet p_{T} > 60");

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

void printFRtable(TH2F* hist) 
{
    // some commonly used charactors for printing table
    std::string colsep = " & ";
    std::string pmSign = " $\\pm$ ";
    std::string endL   = " \\\\ \\hline";

    // print out header stuff for latex table
    std::cout << "\\begin{table}[htb]" << std::endl;
    std::cout << "\\begin{center}" << std::endl;
    std::cout << "\\caption{}" << std::endl;
    std::cout << "\\begin{tabular}{c|ccccc}" << std::endl;
    std::cout << "\\hline" << std::endl;
    std::cout << "\\backslashbox{$|\\eta|$}{$p_T$}";

    int nbinsx = hist->GetNbinsX(); // number of bins along x axis
    int nbinsy = hist->GetNbinsY(); // number of bins along y axis

    // first, print pt ranges
    for (int ny = 1; ny < nbinsy+1; ny++) {
        float lowedge  = hist->GetYaxis()->GetBinLowEdge(ny);
        float width    = hist->GetYaxis()->GetBinWidth(ny);

        printf("%s%.3f%s%.3f", colsep.c_str(), lowedge, " -- ", lowedge+width);
    }

    std::cout << endL << "\\hline" << std::endl;

    // loop over bins
    for (int nx = 1; nx < nbinsx+1; nx++) {
        for (int ny = 1; ny < nbinsy+1; ny++) {

            int nbin = hist->GetBin(nx, ny);

            // if first bin in column, print out eta range
            if (ny == 1) {
                float lowedge  = hist->GetXaxis()->GetBinLowEdge(nx);
                float width    = hist->GetXaxis()->GetBinWidth(nx);		 

                printf("%.3f%s%.3f", lowedge, " -- ", lowedge+width);
            }

            float fr    = hist->GetBinContent(nbin);
            float frerr = hist->GetBinError(nbin);

            printf("%s%.4f%s%.4f", colsep.c_str(), fr, pmSign.c_str(), frerr);
        }

        std::cout << endL << std::endl;
    }

    // print out final header stuff for table
    std::cout << "\\end{tabular}" << std::endl;
    std::cout << "\\end{center}" << std::endl;
    std::cout << "\\end{table}" << std::endl;
}

void PrintFRTables(const std::string lepton="mu")
{
    rt::TH1Container hc("plots/fake_rates/data/ssFR_data_standard_20June2012.root");
    if (lepton=="mu")
    {
        TH2F* h_mufr40c = dynamic_cast<TH2F*>(hc["h_mufr40c"]);
        printFRtable(h_mufr40c);
    }
    if (lepton=="el")
    {
        TH2F* h_elfr40c = dynamic_cast<TH2F*>(hc["h_elfr40c"]);
        printFRtable(h_elfr40c);
    }
}


void PrintFRRatioPlot(const std::string& suffix = "png")
{
    float max = 1.5;
    string path = "plots/fake_rates/compare";

	// set style
	rt::SetTDRStyle();
	gStyle->SetTitleBorderSize(0);
    gStyle->SetMarkerSize(1.0);

    // muons
	rt::TH1Container hc_mu0p92("data/fake_rates/ssFR_data_standard_23May2012.root");
	rt::TH1Container hc_mu8p80("plots/fake_rates/muons_8p8fb/muons_8p8fb.root"      );
	rt::TH1Container hc;

	hc.Add(dynamic_cast<TH1*>(hc_mu8p80["h_mufr40c_vs_pt"]->Clone("h_mufr_ratio_vs_pt")));
	hc["h_mufr_ratio_vs_pt"]->SetTitle("ratio of #mu fake rates (8.8 FR/0.92 FR);p_{T} (GeV)");
	hc["h_mufr_ratio_vs_pt"]->Divide(hc_mu0p92["h_mufr40c_vs_pt"]);
	hc["h_mufr_ratio_vs_pt"]->GetYaxis()->SetRangeUser(0, max);
	hc["h_mufr_ratio_vs_pt"]->SetMarkerSize(1.0);
	hc["h_mufr_ratio_vs_pt"]->SetMarkerStyle(20);
	hc["h_mufr_ratio_vs_pt"]->SetLineWidth(2);
	hc["h_mufr_ratio_vs_pt"]->Draw();

	hc.Add(dynamic_cast<TH1*>(hc_mu8p80["h_mufr40c_vs_eta"]->Clone("h_mufr_ratio_vs_eta")));
	hc["h_mufr_ratio_vs_eta"]->SetTitle("ratio of #mu fake rates (8.8 FR/0.92 FR);|#eta|");
	hc["h_mufr_ratio_vs_eta"]->Divide(hc_mu0p92["h_mufr40c_vs_eta"]);
	hc["h_mufr_ratio_vs_eta"]->GetYaxis()->SetRangeUser(0, max);
	hc["h_mufr_ratio_vs_eta"]->SetMarkerSize(1.0);
	hc["h_mufr_ratio_vs_eta"]->SetMarkerStyle(20);
	hc["h_mufr_ratio_vs_eta"]->SetLineWidth(2);
	hc["h_mufr_ratio_vs_eta"]->Draw();

	hc.Add(dynamic_cast<TH1*>(hc_mu8p80["h_mufr40c_vs_nvtxs"]->Clone("h_mufr_ratio_vs_nvtxs")));
	hc["h_mufr_ratio_vs_nvtxs"]->SetTitle("ratio of #mu fake rates (8.8 FR/0.92 FR);# vertices");
	hc["h_mufr_ratio_vs_nvtxs"]->Divide(hc_mu0p92["h_mufr40c_vs_nvtxs"]);
	hc["h_mufr_ratio_vs_nvtxs"]->GetYaxis()->SetRangeUser(0, max);
	hc["h_mufr_ratio_vs_nvtxs"]->SetMarkerSize(1.0);
	hc["h_mufr_ratio_vs_nvtxs"]->SetMarkerStyle(20);
	hc["h_mufr_ratio_vs_nvtxs"]->SetLineWidth(2);
	hc["h_mufr_ratio_vs_nvtxs"]->Draw();

    // electrons
	rt::TH1Container hc_el0p92("data/fake_rates/ssFR_data_standard_23May2012.root"      );
	rt::TH1Container hc_el8p80("plots/fake_rates/electrons_8p8fb/electrons_8p8fb.root");

	hc.Add(dynamic_cast<TH1*>(hc_el8p80["h_elfr40c_vs_pt"]->Clone("h_elfr_ratio_vs_pt")));
	hc["h_elfr_ratio_vs_pt"]->SetTitle("ratio of electron fake rates (8.8 FR/0.92 FR);p_{T} (GeV)");
	hc["h_elfr_ratio_vs_pt"]->Divide(hc_el0p92["h_elfr40c_vs_pt"]);
	hc["h_elfr_ratio_vs_pt"]->GetYaxis()->SetRangeUser(0, max);
	hc["h_elfr_ratio_vs_pt"]->SetMarkerSize(1.0);
	hc["h_elfr_ratio_vs_pt"]->SetMarkerStyle(20);
	hc["h_elfr_ratio_vs_pt"]->SetLineWidth(2);
	hc["h_elfr_ratio_vs_pt"]->Draw();

	hc.Add(dynamic_cast<TH1*>(hc_el8p80["h_elfr40c_vs_eta"]->Clone("h_elfr_ratio_vs_eta")));
	hc["h_elfr_ratio_vs_eta"]->SetTitle("ratio of electron fake rates (8.8 FR/0.92 FR);|#eta|");
	hc["h_elfr_ratio_vs_eta"]->Divide(hc_el0p92["h_elfr40c_vs_eta"]);
	hc["h_elfr_ratio_vs_eta"]->GetYaxis()->SetRangeUser(0, max);
	hc["h_elfr_ratio_vs_eta"]->SetMarkerSize(1.0);
	hc["h_elfr_ratio_vs_eta"]->SetMarkerStyle(20);
	hc["h_elfr_ratio_vs_eta"]->SetLineWidth(2);
	hc["h_elfr_ratio_vs_eta"]->Draw();

	hc.Add(dynamic_cast<TH1*>(hc_el8p80["h_elfr40c_vs_nvtxs"]->Clone("h_elfr_ratio_vs_nvtxs")));
	hc["h_elfr_ratio_vs_nvtxs"]->SetTitle("ratio of electron fake rates (8.8 FR/0.92 FR);# vertices");
	hc["h_elfr_ratio_vs_nvtxs"]->Divide(hc_el0p92["h_elfr40c_vs_nvtxs"]);
	hc["h_elfr_ratio_vs_nvtxs"]->GetYaxis()->SetRangeUser(0, max);
	hc["h_elfr_ratio_vs_nvtxs"]->SetMarkerSize(1.0);
	hc["h_elfr_ratio_vs_nvtxs"]->SetMarkerStyle(20);
	hc["h_elfr_ratio_vs_nvtxs"]->SetLineWidth(2);
	hc["h_elfr_ratio_vs_nvtxs"]->Draw();

    // overlay
	std::map<std::string, rt::TH1Overlay> p;
    p["p_fr_ratio_vs_pt"] = rt::TH1Overlay("ratio of fake rates (8.8 FR/0.92 FR);p_{T} (GeV)", "sb::off lg::top_left");
    p["p_fr_ratio_vs_pt"].Add(hc["h_mufr_ratio_vs_pt"], "muons"    , kBlue, 2, 20);
    p["p_fr_ratio_vs_pt"].Add(hc["h_elfr_ratio_vs_pt"], "electrons", kRed , 2, 22);
    p["p_fr_ratio_vs_pt"].SetYAxisRange(0, max);
    p["p_fr_ratio_vs_pt"].SetLegendOption("p");
    p["p_fr_ratio_vs_pt"].SetLegendTextSize(0.042);

    p["p_fr_ratio_vs_nvtxs"] = rt::TH1Overlay("ratio of fake rates (8.8 FR/0.92 FR);# vertices", "sb::off lg::top_left");
    p["p_fr_ratio_vs_nvtxs"].Add(hc["h_mufr_ratio_vs_nvtxs"], "muons"    , kBlue, 2, 20);
    p["p_fr_ratio_vs_nvtxs"].Add(hc["h_elfr_ratio_vs_nvtxs"], "electrons", kRed , 2, 22);
    p["p_fr_ratio_vs_nvtxs"].SetYAxisRange(0, max);
    p["p_fr_ratio_vs_nvtxs"].SetLegendOption("p");
    p["p_fr_ratio_vs_nvtxs"].SetLegendTextSize(0.042);
    p["p_fr_ratio_vs_nvtxs"].AddText("p^{l}_{T} > 20 GeV", 0.60, 0.835);

    p["p_fr_ratio_vs_eta"] = rt::TH1Overlay("ratio of fake rates (8.8 FR/0.92 FR);|#eta|", "sb::off lg::top_left");
    p["p_fr_ratio_vs_eta"].Add(hc["h_mufr_ratio_vs_eta"], "muons"    , kBlue, 2, 20);
    p["p_fr_ratio_vs_eta"].Add(hc["h_elfr_ratio_vs_eta"], "electrons", kRed , 2, 22);
    p["p_fr_ratio_vs_eta"].SetYAxisRange(0, max);
    p["p_fr_ratio_vs_eta"].SetLegendOption("p");
    p["p_fr_ratio_vs_eta"].SetLegendTextSize(0.042);
    p["p_fr_ratio_vs_eta"].AddText("p^{l}_{T} > 20 GeV", 0.60, 0.835);

    // print
    hc.Print(path, suffix);
    rt::Print(p, path, suffix);
}

void PrintFRDiffPlot(const std::string& suffix = "png")
{
    float max = 0.2;
    float min = -0.2;
    string path = "plots/fake_rates/compare";

	// set style
	rt::SetTDRStyle();
	gStyle->SetTitleBorderSize(0);

    // muons
	rt::TH1Container hc_mu0p92("data/fake_rates/ssFR_data_standard_23May2012.root");
	rt::TH1Container hc_mu8p80("plots/fake_rates/muons_8p8fb/muons_8p8fb.root"      );
	rt::TH1Container hc;

	hc.Add(dynamic_cast<TH1*>(hc_mu8p80["h_mufr40c_vs_pt"]->Clone("h_mufr_diff_vs_pt")));
	hc["h_mufr_diff_vs_pt"]->SetTitle("diff of #mu fake rates (8.8 FR - 0.92 FR);p_{T} (GeV)");
	hc["h_mufr_diff_vs_pt"]->Add(hc_mu0p92["h_mufr40c_vs_pt"], -1.0);
	hc["h_mufr_diff_vs_pt"]->GetYaxis()->SetRangeUser(min, max);
	hc["h_mufr_diff_vs_pt"]->SetMarkerSize(1.0);
	hc["h_mufr_diff_vs_pt"]->SetMarkerStyle(20);
	hc["h_mufr_diff_vs_pt"]->SetLineWidth(2);
	hc["h_mufr_diff_vs_pt"]->Draw();

	hc.Add(dynamic_cast<TH1*>(hc_mu8p80["h_mufr40c_vs_eta"]->Clone("h_mufr_diff_vs_eta")));
	hc["h_mufr_diff_vs_eta"]->SetTitle("diff of #mu fake rates (8.8 FR - 0.92 FR);|#eta|");
	hc["h_mufr_diff_vs_eta"]->Add(hc_mu0p92["h_mufr40c_vs_eta"], -1.0);
	hc["h_mufr_diff_vs_eta"]->GetYaxis()->SetRangeUser(min, max);
	hc["h_mufr_diff_vs_eta"]->SetMarkerSize(1.0);
	hc["h_mufr_diff_vs_eta"]->SetMarkerStyle(20);
	hc["h_mufr_diff_vs_eta"]->SetLineWidth(2);
	hc["h_mufr_diff_vs_eta"]->Draw();

	hc.Add(dynamic_cast<TH1*>(hc_mu8p80["h_mufr40c_vs_nvtxs"]->Clone("h_mufr_diff_vs_nvtxs")));
	hc["h_mufr_diff_vs_nvtxs"]->SetTitle("diff of #mu fake rates (8.8 FR - 0.92 FR);# vertices");
	hc["h_mufr_diff_vs_nvtxs"]->Add(hc_mu0p92["h_mufr40c_vs_nvtxs"], -1.0);
	hc["h_mufr_diff_vs_nvtxs"]->GetYaxis()->SetRangeUser(min, max);
	hc["h_mufr_diff_vs_nvtxs"]->SetMarkerSize(1.0);
	hc["h_mufr_diff_vs_nvtxs"]->SetMarkerStyle(20);
	hc["h_mufr_diff_vs_nvtxs"]->SetLineWidth(2);
	hc["h_mufr_diff_vs_nvtxs"]->Draw();

    // electrons
	rt::TH1Container hc_el0p92("data/fake_rates/ssFR_data_standard_23May2012.root"      );
	rt::TH1Container hc_el8p80("plots/fake_rates/electrons_8p8fb/electrons_8p8fb.root");

	hc.Add(dynamic_cast<TH1*>(hc_el8p80["h_elfr40c_vs_pt"]->Clone("h_elfr_diff_vs_pt")));
	hc["h_elfr_diff_vs_pt"]->SetTitle("diff of electron fake rates (8.8 FR - 0.92 FR);p_{T} (GeV)");
	hc["h_elfr_diff_vs_pt"]->Add(hc_el0p92["h_elfr40c_vs_pt"], -1.0);
	hc["h_elfr_diff_vs_pt"]->GetYaxis()->SetRangeUser(min, max);
	hc["h_elfr_diff_vs_pt"]->SetMarkerSize(1.0);
	hc["h_elfr_diff_vs_pt"]->SetMarkerStyle(20);
	hc["h_elfr_diff_vs_pt"]->SetLineWidth(2);
	hc["h_elfr_diff_vs_pt"]->Draw();

	hc.Add(dynamic_cast<TH1*>(hc_el8p80["h_elfr40c_vs_eta"]->Clone("h_elfr_diff_vs_eta")));
	hc["h_elfr_diff_vs_eta"]->SetTitle("diff of electron fake rates (8.8 FR - 0.92 FR);|#eta|");
	hc["h_elfr_diff_vs_eta"]->Add(hc_el0p92["h_elfr40c_vs_eta"], -1.0);
	hc["h_elfr_diff_vs_eta"]->GetYaxis()->SetRangeUser(min, max);
	hc["h_elfr_diff_vs_eta"]->SetMarkerSize(1.0);
	hc["h_elfr_diff_vs_eta"]->SetMarkerStyle(20);
	hc["h_elfr_diff_vs_eta"]->SetLineWidth(2);
	hc["h_elfr_diff_vs_eta"]->Draw();

	hc.Add(dynamic_cast<TH1*>(hc_el8p80["h_elfr40c_vs_nvtxs"]->Clone("h_elfr_diff_vs_nvtxs")));
	hc["h_elfr_diff_vs_nvtxs"]->SetTitle("diff of electron fake rates (8.8 FR - 0.92 FR);# vertices");
	hc["h_elfr_diff_vs_nvtxs"]->Add(hc_el0p92["h_elfr40c_vs_nvtxs"], -1.0);
	hc["h_elfr_diff_vs_nvtxs"]->GetYaxis()->SetRangeUser(min, max);
	hc["h_elfr_diff_vs_nvtxs"]->SetMarkerSize(1.0);
	hc["h_elfr_diff_vs_nvtxs"]->SetMarkerStyle(20);
	hc["h_elfr_diff_vs_nvtxs"]->SetLineWidth(2);
	hc["h_elfr_diff_vs_nvtxs"]->Draw();

    // overlay
	std::map<std::string, rt::TH1Overlay> p;
    p["p_fr_diff_vs_pt"] = rt::TH1Overlay("diff of fake rates (8.8 FR - 0.92 FR);p_{T} (GeV)", "sb::off lg::top_left");
    p["p_fr_diff_vs_pt"].Add(hc["h_mufr_diff_vs_pt"], "muons"    , kBlue, 2, 20);
    p["p_fr_diff_vs_pt"].Add(hc["h_elfr_diff_vs_pt"], "electrons", kRed , 2, 22);
    p["p_fr_diff_vs_pt"].SetYAxisRange(min, max);
    p["p_fr_diff_vs_pt"].SetLegendOption("p");
    p["p_fr_diff_vs_pt"].SetLegendTextSize(0.042);

    p["p_fr_diff_vs_nvtxs"] = rt::TH1Overlay("diff of fake rates (8.8 FR - 0.92 FR);# vertices", "sb::off lg::top_left");
    p["p_fr_diff_vs_nvtxs"].Add(hc["h_mufr_diff_vs_nvtxs"], "muons"    , kBlue, 2, 20);
    p["p_fr_diff_vs_nvtxs"].Add(hc["h_elfr_diff_vs_nvtxs"], "electrons", kRed , 2, 22);
    p["p_fr_diff_vs_nvtxs"].SetYAxisRange(min, max);
    p["p_fr_diff_vs_nvtxs"].SetLegendOption("p");
    p["p_fr_diff_vs_nvtxs"].SetLegendTextSize(0.042);
    p["p_fr_diff_vs_nvtxs"].AddText("p^{l}_{T} > 20 GeV", 0.60, 0.835);

    p["p_fr_diff_vs_eta"] = rt::TH1Overlay("diff of fake rates (8.8 FR - 0.92 FR);|#eta|", "sb::off lg::top_left");
    p["p_fr_diff_vs_eta"].Add(hc["h_mufr_diff_vs_eta"], "muons"    , kBlue, 2, 20);
    p["p_fr_diff_vs_eta"].Add(hc["h_elfr_diff_vs_eta"], "electrons", kRed , 2, 22);
    p["p_fr_diff_vs_eta"].SetYAxisRange(min, max);
    p["p_fr_diff_vs_eta"].SetLegendOption("p");
    p["p_fr_diff_vs_eta"].SetLegendTextSize(0.042);
    p["p_fr_diff_vs_eta"].AddText("p^{l}_{T} > 20 GeV", 0.60, 0.835);

    // print
    hc.Print(path, suffix);
    rt::Print(p, path, suffix);
}
