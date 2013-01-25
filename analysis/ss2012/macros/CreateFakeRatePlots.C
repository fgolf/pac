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
    t.setColLabel("pT  5-10" , 0);
    t.setColLabel("pT 10-15" , 1);
    t.setColLabel("pT 15-20" , 2);
    t.setColLabel("pT 20-25" , 3);
    t.setColLabel("pT 25-35" , 4);
    t.setRowLabel("eta 0-1"  , 0);
    t.setRowLabel("eta 1-1.5", 1);
    t.setRowLabel("eta 1.5-2", 2);
    t.setRowLabel("eta 2-2.5", 3);
    TH2* h2_num = dynamic_cast<TH2*>(h_num);
    TH2* h2_den = dynamic_cast<TH2*>(h_den);
    int num_total = 0;
    int den_total = 0;
    for (int row = 0; row != h2_num->GetXaxis()->GetNbins(); row++)
    {
        for (int col = 0; col != h2_num->GetYaxis()->GetNbins(); col++)
        {
            int num = static_cast<int>(h2_num->GetBinContent(row+1, col+1));
            int den = static_cast<int>(h2_den->GetBinContent(row+1, col+1));
            string count = Form("(%d, %d)", num, den);
            num_total += num;
            den_total += den;
            t.setCell(count, row, col);
        }
    }
    t.print();
    cout << "Total Numerators:   " << num_total << "\tTotal Denominators: " << den_total << endl;
    cout << endl;
}

void CountElectronNumDen(TH1* h_num, TH1* h_den, const std::string& title)
{
    cout << h_num->GetTitle() << ", " << h_den->GetTitle() << endl;
    CTable t;
    t.setTitle(title);
    t.useTitle();
    t.setColLabel("pT 10-15"   , 0);
    t.setColLabel("pT 15-20"   , 1);
    t.setColLabel("pT 20-25"   , 2);
    t.setColLabel("pT 25-35"   , 3);
    t.setColLabel("pT 35-55"   , 4);
    t.setRowLabel("eta 0-1"    , 0);
    t.setRowLabel("eta 1-1.479", 1);
    t.setRowLabel("eta 1.479-2", 2);
    t.setRowLabel("eta 2-2.5"  , 3);
    TH2* h2_num = dynamic_cast<TH2*>(h_num);
    TH2* h2_den = dynamic_cast<TH2*>(h_den);
    int num_total = 0;
    int den_total = 0;
    for (int row = 0; row != h2_num->GetXaxis()->GetNbins(); row++)
    {
        for (int col = 0; col != h2_num->GetYaxis()->GetNbins(); col++)
        {
            int num = static_cast<int>(h2_num->GetBinContent(row+1, col+1));
            int den = static_cast<int>(h2_den->GetBinContent(row+1, col+1));
            string count = Form("(%d, %d)", num, den);
            num_total += num;
            den_total += den;
            t.setCell(count, row, col);
        }
    }
    t.print();
    cout << "Total Numerators:   " << num_total << "\tTotal Denominators: " << den_total << endl;
    cout << endl;
}

void PrintMuonFakeRatePlots(const std::string& suffix = "png")
{
	//rt::TH1Container hc("plots/fake_rates/muons_920pb/muons_920pb.root");
    //std::string path = "plots/fake_rates/muons_920pb";
	//float lumi = 0.920;

	//rt::TH1Container hc("plots/fake_rates/muons_5p1/muons_5p1.root");
    //std::string path = "plots/fake_rates/muons_5p1";
	//float lumi = 5.1;

	//rt::TH1Container hc("plots/fake_rates/muons_2012ABr/muons_2012ABr.root");
    //std::string path = "plots/fake_rates/muons_2012ABr";
	//float lumi = 5.2;

	//rt::TH1Container hc("plots/fake_rates/muons_2012Cv2/muons_2012Cv2.root");
    //std::string path = "plots/fake_rates/muons_2012Cv2";
	//float lumi = 3.0;

	//rt::TH1Container hc("plots/fake_rates/muons_8p8fb/muons_8p8fb.root");
    //std::string path = "plots/fake_rates/muons_8p8fb";
	//float lumi = 8.8;

	//rt::TH1Container hc("data/fake_rates/ssFR_data_standard_24Sep2012.root");
    //std::string path = "plots/fake_rates/muons_10p45fb";
	//float lumi = 10.5;

	rt::TH1Container hc("data/fake_rates/ssFR_data_standard_16Dec2012.root");
    std::string path = "plots/fake_rates/muons_19p5fb";
	float lumi = 19.5;

	//rt::TH1Container hc("plots/fake_rates/qcd/qcd_pt35.root");
    //std::string path = "plots/fake_rates/qcd";
	//float lumi = 15.9;

	std::map<std::string, rt::TH1Overlay> p;

	// set style
	rt::SetTDRStyle();
	gStyle->SetTitleBorderSize(0);

	//std::string title = Form("QCD derived FR, #sqrt{s} = 8 TeV", lumi);
	std::string title = Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %3.1f fb^{-1}", lumi);
	//std::string title = Form("#mu^{+} fake rate, #sqrt{s} = 8 TeV, L_{int} = %3.1f fb^{-1}", lumi);
	//std::string title = Form("#mu^{-} fake rate, #sqrt{s} = 8 TeV, L_{int} = %3.1f fb^{-1}", lumi);

    // Fake Rates
    float max = 0.5;
    Color_t c20 = kRed;
    Color_t c40 = kBlack;
    Color_t c60 = kBlue;

    Style_t s20 = 20;
    Style_t s40 = 22;
    Style_t s60 = 24;

    // FR(#vetices), FR(pt), FR(eta) -- cpfiso03_db
    p["p_mufr_vs_nvtxs"] = rt::TH1Overlay(Form("%s;number of vertices;TL ratio", title.c_str()), "sb::off lg::top");
    p["p_mufr_vs_nvtxs"].Add(hc["h_mufr20c_vs_nvtxs"], "away jet p_{T} > 20 GeV", c20, 2, s20);
    p["p_mufr_vs_nvtxs"].Add(hc["h_mufr40c_vs_nvtxs"], "away jet p_{T} > 40 GeV", c40, 2, s40);
    p["p_mufr_vs_nvtxs"].Add(hc["h_mufr60c_vs_nvtxs"], "away jet p_{T} > 60 GeV", c60, 2, s60);
    p["p_mufr_vs_nvtxs"].SetYAxisRange(0, max);
    p["p_mufr_vs_nvtxs"].SetLegendOption("p");
    p["p_mufr_vs_nvtxs"].SetLegendTextSize(0.042);
    p["p_mufr_vs_nvtxs"].AddText("Muons"               , 0.25, 0.835);
    p["p_mufr_vs_nvtxs"].AddText("p^{#mu}_{T} > 20 GeV", 0.25, 0.775);

    p["p_mufr_vs_pt"] = rt::TH1Overlay(Form("%s;p_{T} (GeV);TL ratio", title.c_str()), "sb::off lg::top");
    p["p_mufr_vs_pt"].Add(hc["h_mufr20c_vs_pt"], "away jet p_{T} > 20 GeV", c20, 2, s20);
    p["p_mufr_vs_pt"].Add(hc["h_mufr40c_vs_pt"], "away jet p_{T} > 40 GeV", c40, 2, s40);
    p["p_mufr_vs_pt"].Add(hc["h_mufr60c_vs_pt"], "away jet p_{T} > 60 GeV", c60, 2, s60);
    p["p_mufr_vs_pt"].SetYAxisRange(0, max);
    p["p_mufr_vs_pt"].SetLegendOption("p");
    p["p_mufr_vs_pt"].SetLegendTextSize(0.042);
    p["p_mufr_vs_pt"].AddText("Muons", 0.25, 0.835);

    p["p_mufr_vs_eta"] = rt::TH1Overlay(Form("%s;|#eta|;TL ratio", title.c_str()), "sb::off lg::top");
    p["p_mufr_vs_eta"].Add(hc["h_mufr20c_vs_eta"], "away jet p_{T} > 20 GeV", c20, 2, s20);
    p["p_mufr_vs_eta"].Add(hc["h_mufr40c_vs_eta"], "away jet p_{T} > 40 GeV", c40, 2, s40);
    p["p_mufr_vs_eta"].Add(hc["h_mufr60c_vs_eta"], "away jet p_{T} > 60 GeV", c60, 2, s60);
    p["p_mufr_vs_eta"].SetYAxisRange(0, max);
    p["p_mufr_vs_eta"].SetLegendOption("p");
    p["p_mufr_vs_eta"].SetLegendTextSize(0.042);
    p["p_mufr_vs_eta"].AddText("Muons"               , 0.25, 0.835);
    p["p_mufr_vs_eta"].AddText("p^{#mu}_{T} > 20 GeV", 0.25, 0.775);

    cout << endl;
    CountMuonNumDen(hc["h_mu_num20c"], hc["h_mu_fo20c"], "#mu count (num, den), away jet p_{T} > 20");
    CountMuonNumDen(hc["h_mu_num40c"], hc["h_mu_fo40c"], "#mu count (num, den), away jet p_{T} > 40");
    CountMuonNumDen(hc["h_mu_num60c"], hc["h_mu_fo60c"], "#mu count (num, den), away jet p_{T} > 60");
    cout << endl;

    //p["p_mufr_iso_vs_nvtxs"] = rt::TH1Overlay(Form("%s;number of vertices;TL ratio", title.c_str()), "sb::off lg::top");
    //p["p_mufr_iso_vs_nvtxs"].Add(hc["h_mufr20c_iso_vs_nvtxs"], "away jet p_{T} > 20 GeV", c20, 2, s20);
    //p["p_mufr_iso_vs_nvtxs"].Add(hc["h_mufr40c_iso_vs_nvtxs"], "away jet p_{T} > 40 GeV", c40, 2, s40);
    //p["p_mufr_iso_vs_nvtxs"].Add(hc["h_mufr60c_iso_vs_nvtxs"], "away jet p_{T} > 60 GeV", c60, 2, s60);
    //p["p_mufr_iso_vs_nvtxs"].SetYAxisRange(0, max);
    //p["p_mufr_iso_vs_nvtxs"].SetLegendOption("p");
    //p["p_mufr_iso_vs_nvtxs"].SetLegendTextSize(0.042);
    //p["p_mufr_iso_vs_nvtxs"].AddText("Muons"               , 0.25, 0.835);
    //p["p_mufr_iso_vs_nvtxs"].AddText("p^{#mu}_{T} > 20 GeV", 0.25, 0.775);

    //p["p_mufr_iso_vs_pt"] = rt::TH1Overlay(Form("%s;p_{T} (GeV);TL ratio", title.c_str()), "sb::off lg::top");
    //p["p_mufr_iso_vs_pt"].Add(hc["h_mufr20c_iso_vs_pt"], "away jet p_{T} > 20 GeV", c20, 2, s20);
    //p["p_mufr_iso_vs_pt"].Add(hc["h_mufr40c_iso_vs_pt"], "away jet p_{T} > 40 GeV", c40, 2, s40);
    //p["p_mufr_iso_vs_pt"].Add(hc["h_mufr60c_iso_vs_pt"], "away jet p_{T} > 60 GeV", c60, 2, s60);
    //p["p_mufr_iso_vs_pt"].SetYAxisRange(0, max);
    //p["p_mufr_iso_vs_pt"].SetLegendOption("p");
    //p["p_mufr_iso_vs_pt"].SetLegendTextSize(0.042);
    //p["p_mufr_iso_vs_pt"].AddText("Muons", 0.25, 0.835);

    //p["p_mufr_iso_vs_eta"] = rt::TH1Overlay(Form("%s;|#eta|;TL ratio", title.c_str()), "sb::off lg::top");
    //p["p_mufr_iso_vs_eta"].Add(hc["h_mufr20c_iso_vs_eta"], "away jet p_{T} > 20 GeV", c20, 2, s20);
    //p["p_mufr_iso_vs_eta"].Add(hc["h_mufr40c_iso_vs_eta"], "away jet p_{T} > 40 GeV", c40, 2, s40);
    //p["p_mufr_iso_vs_eta"].Add(hc["h_mufr60c_iso_vs_eta"], "away jet p_{T} > 60 GeV", c60, 2, s60);
    //p["p_mufr_iso_vs_eta"].SetYAxisRange(0, max);
    //p["p_mufr_iso_vs_eta"].SetLegendOption("p");
    //p["p_mufr_iso_vs_eta"].SetLegendTextSize(0.042);
    //p["p_mufr_iso_vs_eta"].AddText("Muons"               , 0.25, 0.835);
    //p["p_mufr_iso_vs_eta"].AddText("p^{#mu}_{T} > 20 GeV", 0.25, 0.775);

    //cout << endl;
    //CountMuonNumDen(hc["h_mu_num20c_iso"], hc["h_mu_fo20c_iso"], "#mu count (num, den), away jet p_{T} > 20, iso triggers");
    //CountMuonNumDen(hc["h_mu_num40c_iso"], hc["h_mu_fo40c_iso"], "#mu count (num, den), away jet p_{T} > 40, iso triggers");
    //CountMuonNumDen(hc["h_mu_num60c_iso"], hc["h_mu_fo60c_iso"], "#mu count (num, den), away jet p_{T} > 60, iso triggers");
    //cout << endl;

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

void PrintMuonFakeRatePlotsETH(const std::string& suffix = "png")
{
	rt::TH1Container hc("plots/fake_rates/eth/fakerate_eth.root");
    std::string path = "plots/fake_rates/compare_eth";
	float lumi = 10.5;

	std::map<std::string, rt::TH1Overlay> p;

	// set style
	rt::SetTDRStyle();
	gStyle->SetTitleBorderSize(0);

	//std::string title = Form("QCD derived FR, #sqrt{s} = 8 TeV", lumi);
	std::string title = Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %3.1f fb^{-1}", lumi);
	//std::string title = Form("#mu^{+} fake rate, #sqrt{s} = 8 TeV, L_{int} = %3.1f fb^{-1}", lumi);
	//std::string title = Form("#mu^{-} fake rate, #sqrt{s} = 8 TeV, L_{int} = %3.1f fb^{-1}", lumi);

    // Fake Rates
    float max = 0.5;
    Color_t c30 = kRed;
    Color_t c50 = kBlack;
    Color_t c70 = kBlue;

    Style_t s30 = 20;
    Style_t s50 = 22;
    Style_t s70 = 24;

    hc.SetMarkerSize(1.1);

    // FR(#vetices), FR(pt), FR(eta) -- cpfiso03_db
    p["p_mufr_vs_nvtxs"] = rt::TH1Overlay(Form("%s;number of vertices;TL ratio", title.c_str()), "sb::off lg::top");
    p["p_mufr_vs_nvtxs"].Add(hc["h_mufr30c_vs_nvtxs"], "away jet p_{T} > 30 GeV", c30, 2, s30);
    p["p_mufr_vs_nvtxs"].Add(hc["h_mufr50c_vs_nvtxs"], "away jet p_{T} > 50 GeV", c50, 2, s50);
    p["p_mufr_vs_nvtxs"].Add(hc["h_mufr70c_vs_nvtxs"], "away jet p_{T} > 70 GeV", c70, 2, s70);
    p["p_mufr_vs_nvtxs"].SetYAxisRange(0, max);
    p["p_mufr_vs_nvtxs"].SetLegendOption("p");
    p["p_mufr_vs_nvtxs"].SetLegendTextSize(0.042);
    p["p_mufr_vs_nvtxs"].AddText("Muons"               , 0.25, 0.835);
    p["p_mufr_vs_nvtxs"].AddText("p^{#mu}_{T} > 20 GeV", 0.25, 0.775);

    p["p_mufr_vs_pt"] = rt::TH1Overlay(Form("%s;p_{T} (GeV);TL ratio", title.c_str()), "sb::off lg::top");
    p["p_mufr_vs_pt"].Add(hc["h_mufr30c_vs_pt"], "away jet p_{T} > 30 GeV", c30, 2, s30);
    p["p_mufr_vs_pt"].Add(hc["h_mufr50c_vs_pt"], "away jet p_{T} > 50 GeV", c50, 2, s50);
    p["p_mufr_vs_pt"].Add(hc["h_mufr70c_vs_pt"], "away jet p_{T} > 70 GeV", c70, 2, s70);
    p["p_mufr_vs_pt"].SetYAxisRange(0, max);
    p["p_mufr_vs_pt"].SetLegendOption("p");
    p["p_mufr_vs_pt"].SetLegendTextSize(0.042);
    p["p_mufr_vs_pt"].AddText("Muons", 0.25, 0.835);

    p["p_mufr_vs_eta"] = rt::TH1Overlay(Form("%s;|#eta|;TL ratio", title.c_str()), "sb::off lg::top");
    p["p_mufr_vs_eta"].Add(hc["h_mufr30c_vs_eta"], "away jet p_{T} > 30 GeV", c30, 2, s30);
    p["p_mufr_vs_eta"].Add(hc["h_mufr50c_vs_eta"], "away jet p_{T} > 50 GeV", c50, 2, s50);
    p["p_mufr_vs_eta"].Add(hc["h_mufr70c_vs_eta"], "away jet p_{T} > 70 GeV", c70, 2, s70);
    p["p_mufr_vs_eta"].SetYAxisRange(0, max);
    p["p_mufr_vs_eta"].SetLegendOption("p");
    p["p_mufr_vs_eta"].SetLegendTextSize(0.042);
    p["p_mufr_vs_eta"].AddText("Muons"               , 0.25, 0.835);
    p["p_mufr_vs_eta"].AddText("p^{#mu}_{T} > 20 GeV", 0.25, 0.775);

    cout << endl;
    CountMuonNumDen(hc["h_mu_num30c"], hc["h_mu_fo30c"], "#mu count (num, den), away jet p_{T} > 30");
    CountMuonNumDen(hc["h_mu_num50c"], hc["h_mu_fo50c"], "#mu count (num, den), away jet p_{T} > 50");
    CountMuonNumDen(hc["h_mu_num70c"], hc["h_mu_fo70c"], "#mu count (num, den), away jet p_{T} > 70");
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
	//rt::TH1Container hc("data/fake_rates/ssFR_data_standard_24Sep2012.root");
    //std::string path = "plots/fake_rates/electrons_10p45fb";
	//float lumi = 10.5;

	rt::TH1Container hc("data/fake_rates/ssFR_data_standard_16Dec2012.root");
    std::string path = "plots/fake_rates/electrons_19p5fb";
	float lumi = 19.5;

	//rt::TH1Container hc("plots/fake_rates/qcd/qcd_pt35.root");
    //std::string path = "plots/fake_rates/qcd";
	//float lumi = 15.9;

	//rt::TH1Container hc("plots/fake_rates/eth/fakerate_eth.root");
    //std::string path = "plots/fake_rates/compare_eth";
	//float lumi = 10.5;

	// set style
	rt::SetTDRStyle();
	gStyle->SetTitleBorderSize(0);

	//std::string title = "QCD derived FR, #sqrt{s} = 8 TeV";
	std::string title = Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %3.1f fb^{-1}", lumi);
	//std::string title = Form("e^{+} fake rate, #sqrt{s} = 8 TeV, L_{int} = %3.1f fb^{-1}", lumi);
	//std::string title = Form("e^{-} fake rate, #sqrt{s} = 8 TeV, L_{int} = %3.1f fb^{-1}", lumi);

    // Fake Rates
    float max = 0.6;
    Color_t c20 = kRed;
    Color_t c40 = kBlack;
    Color_t c60 = kBlue;

    Style_t s20 = 20;
    Style_t s40 = 22;
    Style_t s60 = 24;

    hc.SetMarkerSize(1.1);

    // FR(#vetices), FR(pt), FR(eta) -- cpfiso03_db
	std::map<std::string, rt::TH1Overlay> p;
    p["p_elfr_vs_nvtxs"] = rt::TH1Overlay(Form("%s;number of vertices;TL ratio", title.c_str()), "sb::off lg::top");
    p["p_elfr_vs_nvtxs"].Add(hc["h_elfr20c_vs_nvtxs"], "away jet p_{T} > 20 GeV", c20, 2, s20);
    p["p_elfr_vs_nvtxs"].Add(hc["h_elfr40c_vs_nvtxs"], "away jet p_{T} > 40 GeV", c40, 2, s40);
    p["p_elfr_vs_nvtxs"].Add(hc["h_elfr60c_vs_nvtxs"], "away jet p_{T} > 60 GeV", c60, 2, s60);
    p["p_elfr_vs_nvtxs"].SetYAxisRange(0, max);
    p["p_elfr_vs_nvtxs"].SetLegendOption("p");
    p["p_elfr_vs_nvtxs"].SetLegendTextSize(0.042);
    p["p_elfr_vs_nvtxs"].AddText("Electrons"         , 0.25, 0.835);
    p["p_elfr_vs_nvtxs"].AddText("p^{e}_{T} > 20 GeV", 0.25, 0.775);

    p["p_elfr_vs_pt"] = rt::TH1Overlay(Form("%s;p_{T} (GeV);TL ratio", title.c_str()), "sb::off lg::top");
    p["p_elfr_vs_pt"].Add(hc["h_elfr20c_vs_pt"], "away jet p_{T} > 20 GeV", c20, 2, s20);
    p["p_elfr_vs_pt"].Add(hc["h_elfr40c_vs_pt"], "away jet p_{T} > 40 GeV", c40, 2, s40);
    p["p_elfr_vs_pt"].Add(hc["h_elfr60c_vs_pt"], "away jet p_{T} > 60 GeV", c60, 2, s60);
    p["p_elfr_vs_pt"].SetYAxisRange(0, max);
    p["p_elfr_vs_pt"].SetLegendOption("p");
    p["p_elfr_vs_pt"].SetLegendTextSize(0.042);
    p["p_elfr_vs_pt"].AddText("Electrons", 0.25, 0.835);

    p["p_elfr_vs_eta"] = rt::TH1Overlay(Form("%s;|#eta|;TL ratio", title.c_str()), "sb::off lg::top");
    p["p_elfr_vs_eta"].Add(hc["h_elfr20c_vs_eta"], "away jet p_{T} > 20 GeV", c20, 2, s20);
    p["p_elfr_vs_eta"].Add(hc["h_elfr40c_vs_eta"], "away jet p_{T} > 40 GeV", c40, 2, s40);
    p["p_elfr_vs_eta"].Add(hc["h_elfr60c_vs_eta"], "away jet p_{T} > 60 GeV", c60, 2, s60);
    p["p_elfr_vs_eta"].SetYAxisRange(0, max);
    p["p_elfr_vs_eta"].SetLegendOption("p");
    p["p_elfr_vs_eta"].SetLegendTextSize(0.042);
    p["p_elfr_vs_eta"].AddText("Electrons"         , 0.25, 0.835);
    p["p_elfr_vs_eta"].AddText("p^{e}_{T} > 20 GeV", 0.25, 0.775);

    CountElectronNumDen(hc["h_el_num20c"], hc["h_el_fo20c"], "electron count (num, den), radial iso (E_T > 0.5), away jet p_{T} > 20");
    CountElectronNumDen(hc["h_el_num40c"], hc["h_el_fo40c"], "electron count (num, den), radial iso (E_T > 0.5), away jet p_{T} > 40");
    CountElectronNumDen(hc["h_el_num60c"], hc["h_el_fo60c"], "electron count (num, den), radial iso (E_T > 0.5), away jet p_{T} > 60");

    p["p_elfr_trig_noiso_vs_nvtxs"] = rt::TH1Overlay(Form("%s;number of vertices;TL ratio", title.c_str()), "sb::off lg::top");
    p["p_elfr_trig_noiso_vs_nvtxs"].Add(hc["h_elfr20c_noiso_vs_nvtxs"], "away jet p_{T} > 20 GeV", c20, 2, s20);
    p["p_elfr_trig_noiso_vs_nvtxs"].Add(hc["h_elfr40c_noiso_vs_nvtxs"], "away jet p_{T} > 40 GeV", c40, 2, s40);
    p["p_elfr_trig_noiso_vs_nvtxs"].Add(hc["h_elfr60c_noiso_vs_nvtxs"], "away jet p_{T} > 60 GeV", c60, 2, s60);
    p["p_elfr_trig_noiso_vs_nvtxs"].SetYAxisRange(0, max);
    p["p_elfr_trig_noiso_vs_nvtxs"].SetLegendOption("p");
    p["p_elfr_trig_noiso_vs_nvtxs"].SetLegendTextSize(0.042);
    p["p_elfr_trig_noiso_vs_nvtxs"].AddText("Electrons"         , 0.25, 0.835);
    p["p_elfr_trig_noiso_vs_nvtxs"].AddText("p^{e}_{T} > 20 GeV", 0.25, 0.775);

    p["p_elfr_trig_noiso_vs_pt"] = rt::TH1Overlay(Form("%s;p_{T} (GeV);TL ratio", title.c_str()), "sb::off lg::top");
    p["p_elfr_trig_noiso_vs_pt"].Add(hc["h_elfr20c_noiso_vs_pt"], "away jet p_{T} > 20 GeV", c20, 2, s20);
    p["p_elfr_trig_noiso_vs_pt"].Add(hc["h_elfr40c_noiso_vs_pt"], "away jet p_{T} > 40 GeV", c40, 2, s40);
    p["p_elfr_trig_noiso_vs_pt"].Add(hc["h_elfr60c_noiso_vs_pt"], "away jet p_{T} > 60 GeV", c60, 2, s60);
    p["p_elfr_trig_noiso_vs_pt"].SetYAxisRange(0, max);
    p["p_elfr_trig_noiso_vs_pt"].SetLegendOption("p");
    p["p_elfr_trig_noiso_vs_pt"].SetLegendTextSize(0.042);
    p["p_elfr_trig_noiso_vs_pt"].AddText("Electrons", 0.25, 0.835);

    p["p_elfr_trig_noiso_vs_eta"] = rt::TH1Overlay(Form("%s;|#eta|;TL ratio", title.c_str()), "sb::off lg::top");
    p["p_elfr_trig_noiso_vs_eta"].Add(hc["h_elfr20c_noiso_vs_eta"], "away jet p_{T} > 20 GeV", c20, 2, s20);
    p["p_elfr_trig_noiso_vs_eta"].Add(hc["h_elfr40c_noiso_vs_eta"], "away jet p_{T} > 40 GeV", c40, 2, s40);
    p["p_elfr_trig_noiso_vs_eta"].Add(hc["h_elfr60c_noiso_vs_eta"], "away jet p_{T} > 60 GeV", c60, 2, s60);
    p["p_elfr_trig_noiso_vs_eta"].SetYAxisRange(0, max);
    p["p_elfr_trig_noiso_vs_eta"].SetLegendOption("p");
    p["p_elfr_trig_noiso_vs_eta"].SetLegendTextSize(0.042);
    p["p_elfr_trig_noiso_vs_eta"].AddText("Electrons"         , 0.25, 0.835);
    p["p_elfr_trig_noiso_vs_eta"].AddText("p^{e}_{T} > 20 GeV", 0.25, 0.775);

    CountElectronNumDen(hc["h_el_num20c_noiso"], hc["h_el_fo20c_noiso"], "electron count (num, den), radial iso (E_T > 0.5), away jet p_{T} > 20, no iso on trigger");
    CountElectronNumDen(hc["h_el_num40c_noiso"], hc["h_el_fo40c_noiso"], "electron count (num, den), radial iso (E_T > 0.5), away jet p_{T} > 40, no iso on trigger");
    CountElectronNumDen(hc["h_el_num60c_noiso"], hc["h_el_fo60c_noiso"], "electron count (num, den), radial iso (E_T > 0.5), away jet p_{T} > 60, no iso on trigger");

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


void PrintElectronFakeRatePlotsETH(const std::string& suffix = "png")
{
	rt::TH1Container hc("plots/fake_rates/eth/fakerate_eth.root");
    std::string path = "plots/fake_rates/compare_eth";
	float lumi = 10.5;

	std::map<std::string, rt::TH1Overlay> p;

	// set style
	rt::SetTDRStyle();
	gStyle->SetTitleBorderSize(0);

	//std::string title = Form("QCD derived FR, #sqrt{s} = 8 TeV", lumi);
	std::string title = Form("CMS Preliminary, #sqrt{s} = 8 TeV, L_{int} = %3.1f fb^{-1}", lumi);
	//std::string title = Form("#el^{+} fake rate, #sqrt{s} = 8 TeV, L_{int} = %3.1f fb^{-1}", lumi);
	//std::string title = Form("#el^{-} fake rate, #sqrt{s} = 8 TeV, L_{int} = %3.1f fb^{-1}", lumi);

    // Fake Rates
    float max = 0.5;
    Color_t c30 = kRed;
    Color_t c50 = kBlack;
    Color_t c70 = kBlue;

    Style_t s30 = 20;
    Style_t s50 = 22;
    Style_t s70 = 24;

    // FR(#vetices), FR(pt), FR(eta) -- cpfiso03_db
    p["p_elfr_vs_nvtxs"] = rt::TH1Overlay(Form("%s;number of vertices;TL ratio", title.c_str()), "sb::off lg::top");
    p["p_elfr_vs_nvtxs"].Add(hc["h_elfr30c_vs_nvtxs"], "away jet p_{T} > 30 GeV", c30, 2, s30);
    p["p_elfr_vs_nvtxs"].Add(hc["h_elfr50c_vs_nvtxs"], "away jet p_{T} > 50 GeV", c50, 2, s50);
    p["p_elfr_vs_nvtxs"].Add(hc["h_elfr70c_vs_nvtxs"], "away jet p_{T} > 70 GeV", c70, 2, s70);
    p["p_elfr_vs_nvtxs"].SetYAxisRange(0, max);
    p["p_elfr_vs_nvtxs"].SetLegendOption("p");
    p["p_elfr_vs_nvtxs"].SetLegendTextSize(0.042);
    p["p_elfr_vs_nvtxs"].AddText("Electrons"               , 0.25, 0.835);
    p["p_elfr_vs_nvtxs"].AddText("p^{e}_{T} > 20 GeV", 0.25, 0.775);

    p["p_elfr_vs_pt"] = rt::TH1Overlay(Form("%s;p_{T} (GeV);TL ratio", title.c_str()), "sb::off lg::top");
    p["p_elfr_vs_pt"].Add(hc["h_elfr30c_vs_pt"], "away jet p_{T} > 30 GeV", c30, 2, s30);
    p["p_elfr_vs_pt"].Add(hc["h_elfr50c_vs_pt"], "away jet p_{T} > 50 GeV", c50, 2, s50);
    p["p_elfr_vs_pt"].Add(hc["h_elfr70c_vs_pt"], "away jet p_{T} > 70 GeV", c70, 2, s70);
    p["p_elfr_vs_pt"].SetYAxisRange(0, max);
    p["p_elfr_vs_pt"].SetLegendOption("p");
    p["p_elfr_vs_pt"].SetLegendTextSize(0.042);
    p["p_elfr_vs_pt"].AddText("Electrons", 0.25, 0.835);

    p["p_elfr_vs_eta"] = rt::TH1Overlay(Form("%s;|#eta|;TL ratio", title.c_str()), "sb::off lg::top");
    p["p_elfr_vs_eta"].Add(hc["h_elfr30c_vs_eta"], "away jet p_{T} > 30 GeV", c30, 2, s30);
    p["p_elfr_vs_eta"].Add(hc["h_elfr50c_vs_eta"], "away jet p_{T} > 50 GeV", c50, 2, s50);
    p["p_elfr_vs_eta"].Add(hc["h_elfr70c_vs_eta"], "away jet p_{T} > 70 GeV", c70, 2, s70);
    p["p_elfr_vs_eta"].SetYAxisRange(0, max);
    p["p_elfr_vs_eta"].SetLegendOption("p");
    p["p_elfr_vs_eta"].SetLegendTextSize(0.042);
    p["p_elfr_vs_eta"].AddText("Electrons"               , 0.25, 0.835);
    p["p_elfr_vs_eta"].AddText("p^{e}_{T} > 20 GeV", 0.25, 0.775);

    cout << endl;
    CountMuonNumDen(hc["h_el_num30c"], hc["h_el_fo30c"], "#el count (num, den), away jet p_{T} > 30");
    CountMuonNumDen(hc["h_el_num50c"], hc["h_el_fo50c"], "#el count (num, den), away jet p_{T} > 50");
    CountMuonNumDen(hc["h_el_num70c"], hc["h_el_fo70c"], "#el count (num, den), away jet p_{T} > 70");
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

            printf("%s%.3f%s%.3f", colsep.c_str(), fr, pmSign.c_str(), frerr);
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
    rt::TH1Container hc("data/fake_rates/ssFR_data_standard_16Dec2012.root");
    //rt::TH1Container hc("data/fake_rates/ssFR_data_standard_24Sep2012.root");
	//rt::TH1Container hc("plots/fake_rates/eth/fakerate_eth.root");
    if (lepton=="mu")
    {
        TH2F* h_mufr40c = dynamic_cast<TH2F*>(hc["h_mufr40c"]);
        printFRtable(h_mufr40c);

        TH2F* h_mufr40c_iso = dynamic_cast<TH2F*>(hc["h_mufr40c_iso"]);
        printFRtable(h_mufr40c_iso);
    }
    if (lepton=="el")
    {
        TH2F* h_elfr40c = dynamic_cast<TH2F*>(hc["h_elfr40c"]);
        printFRtable(h_elfr40c);

        TH2F* h_elfr40c_noiso = dynamic_cast<TH2F*>(hc["h_elfr40c_noiso"]);
        printFRtable(h_elfr40c_noiso);
    }
}


void PrintFRRatioPlot(const std::string& suffix = "png")
{
    float max = 1.2;
	float min = 0.8;
    string path = "plots/fake_rates/compare_19p5";

	// set style
	rt::SetTDRStyle();
	gStyle->SetTitleBorderSize(0);
    gStyle->SetMarkerSize(1.0);

    // muons
	rt::TH1Container hc1("data/fake_rates/ssFR_data_standard_24Sep2012.root");
	rt::TH1Container hc2("data/fake_rates/ssFR_data_standard_16Dec2012.root");
	rt::TH1Container hc;

    float lumi1 = 10.5;
    float lumi2 = 19.5;

    string mu_title = Form("ratio of #mu fake rates (%1.1f FR / %1.1f FR)"     , lumi2, lumi1);
    string el_title = Form("ratio of electron fake rates (%1.1f FR / %1.1f FR)", lumi2, lumi1);

	hc.Add(dynamic_cast<TH1*>(hc2["h_mufr40c_vs_pt"]->Clone("h_mufr_ratio_vs_pt")));
	hc["h_mufr_ratio_vs_pt"]->SetTitle(Form("%s;p_{T} (GeV)", mu_title.c_str()));
	hc["h_mufr_ratio_vs_pt"]->Divide(hc1["h_mufr40c_vs_pt"]);
	hc["h_mufr_ratio_vs_pt"]->GetYaxis()->SetRangeUser(min, max);
	hc["h_mufr_ratio_vs_pt"]->SetMarkerSize(1.4);
	hc["h_mufr_ratio_vs_pt"]->SetMarkerStyle(20);
	hc["h_mufr_ratio_vs_pt"]->SetLineWidth(2);
	hc["h_mufr_ratio_vs_pt"]->Draw();

	hc.Add(dynamic_cast<TH1*>(hc2["h_mufr40c_vs_eta"]->Clone("h_mufr_ratio_vs_eta")));
	hc["h_mufr_ratio_vs_eta"]->SetTitle(Form("%s;|#eta|", mu_title.c_str()));
	hc["h_mufr_ratio_vs_eta"]->Divide(hc1["h_mufr40c_vs_eta"]);
	hc["h_mufr_ratio_vs_eta"]->GetYaxis()->SetRangeUser(min, max);
	hc["h_mufr_ratio_vs_eta"]->SetMarkerSize(1.4);
	hc["h_mufr_ratio_vs_eta"]->SetMarkerStyle(20);
	hc["h_mufr_ratio_vs_eta"]->SetLineWidth(2);
	hc["h_mufr_ratio_vs_eta"]->Draw();

	hc.Add(dynamic_cast<TH1*>(hc2["h_mufr40c_vs_nvtxs"]->Clone("h_mufr_ratio_vs_nvtxs")));
	hc["h_mufr_ratio_vs_nvtxs"]->SetTitle(Form("%s;# vertices", mu_title.c_str()));
	hc["h_mufr_ratio_vs_nvtxs"]->Divide(hc1["h_mufr40c_vs_nvtxs"]);
	hc["h_mufr_ratio_vs_nvtxs"]->GetYaxis()->SetRangeUser(min, max);
	hc["h_mufr_ratio_vs_nvtxs"]->SetMarkerSize(1.4);
	hc["h_mufr_ratio_vs_nvtxs"]->SetMarkerStyle(20);
	hc["h_mufr_ratio_vs_nvtxs"]->SetLineWidth(2);
	hc["h_mufr_ratio_vs_nvtxs"]->Draw();

	hc.Add(dynamic_cast<TH1*>(hc2["h_elfr40c_vs_pt"]->Clone("h_elfr_ratio_vs_pt")));
	hc["h_elfr_ratio_vs_pt"]->SetTitle(Form("%s5 FR);p_{T} (GeV)", el_title.c_str()));
	hc["h_elfr_ratio_vs_pt"]->Divide(hc1["h_elfr40c_vs_pt"]);
	hc["h_elfr_ratio_vs_pt"]->GetYaxis()->SetRangeUser(min, max);
	hc["h_elfr_ratio_vs_pt"]->SetMarkerSize(1.4);
	hc["h_elfr_ratio_vs_pt"]->SetMarkerStyle(20);
	hc["h_elfr_ratio_vs_pt"]->SetLineWidth(2);
	hc["h_elfr_ratio_vs_pt"]->Draw();

	hc.Add(dynamic_cast<TH1*>(hc2["h_elfr40c_vs_eta"]->Clone("h_elfr_ratio_vs_eta")));
	hc["h_elfr_ratio_vs_eta"]->SetTitle(Form("%s5 FR);|#eta|", el_title.c_str()));
	hc["h_elfr_ratio_vs_eta"]->Divide(hc1["h_elfr40c_vs_eta"]);
	hc["h_elfr_ratio_vs_eta"]->GetYaxis()->SetRangeUser(min, max);
	hc["h_elfr_ratio_vs_eta"]->SetMarkerSize(1.4);
	hc["h_elfr_ratio_vs_eta"]->SetMarkerStyle(20);
	hc["h_elfr_ratio_vs_eta"]->SetLineWidth(2);
	hc["h_elfr_ratio_vs_eta"]->Draw();

	hc.Add(dynamic_cast<TH1*>(hc2["h_elfr40c_vs_nvtxs"]->Clone("h_elfr_ratio_vs_nvtxs")));
	hc["h_elfr_ratio_vs_nvtxs"]->SetTitle(Form("%s5 FR);# vertices", el_title.c_str()));
	hc["h_elfr_ratio_vs_nvtxs"]->Divide(hc1["h_elfr40c_vs_nvtxs"]);
	hc["h_elfr_ratio_vs_nvtxs"]->GetYaxis()->SetRangeUser(min, max);
	hc["h_elfr_ratio_vs_nvtxs"]->SetMarkerSize(1.4);
	hc["h_elfr_ratio_vs_nvtxs"]->SetMarkerStyle(20);
	hc["h_elfr_ratio_vs_nvtxs"]->SetLineWidth(2);
	hc["h_elfr_ratio_vs_nvtxs"]->Draw();

    // overlay
	//std::map<std::string, rt::TH1Overlay> p;
    //p["p_fr_ratio_vs_pt"] = rt::TH1Overlay("ratio of fake rates (12.3 FR / 10.5 FR);p_{T} (GeV)", "sb::off lg::top_left");
    //p["p_fr_ratio_vs_pt"].Add(hc["h_mufr_ratio_vs_pt"], "muons"    , kBlue, 2, 20);
    //p["p_fr_ratio_vs_pt"].Add(hc["h_elfr_ratio_vs_pt"], "electrons", kRed , 2, 22);
    //p["p_fr_ratio_vs_pt"].SetYAxisRange(min, max);
    //p["p_fr_ratio_vs_pt"].SetLegendOption("p");
    //p["p_fr_ratio_vs_pt"].SetLegendTextSize(0.042);

    //p["p_fr_ratio_vs_nvtxs"] = rt::TH1Overlay("ratio of fake rates (12.3 FR / 10.5 FR);# vertices", "sb::off lg::top_left");
    //p["p_fr_ratio_vs_nvtxs"].Add(hc["h_mufr_ratio_vs_nvtxs"], "muons"    , kBlue, 2, 20);
    //p["p_fr_ratio_vs_nvtxs"].Add(hc["h_elfr_ratio_vs_nvtxs"], "electrons", kRed , 2, 22);
    //p["p_fr_ratio_vs_nvtxs"].SetYAxisRange(min, max);
    //p["p_fr_ratio_vs_nvtxs"].SetLegendOption("p");
    //p["p_fr_ratio_vs_nvtxs"].SetLegendTextSize(0.042);
    //p["p_fr_ratio_vs_nvtxs"].AddText("p^{l}_{T} > 20 GeV", 0.60, 0.835);

    //p["p_fr_ratio_vs_eta"] = rt::TH1Overlay("ratio of fake rates (12.3 FR / 10.5 FR);|#eta|", "sb::off lg::top_left");
    //p["p_fr_ratio_vs_eta"].Add(hc["h_mufr_ratio_vs_eta"], "muons"    , kBlue, 2, 20);
    //p["p_fr_ratio_vs_eta"].Add(hc["h_elfr_ratio_vs_eta"], "electrons", kRed , 2, 22);
    //p["p_fr_ratio_vs_eta"].SetYAxisRange(min, max);
    //p["p_fr_ratio_vs_eta"].SetLegendOption("p");
    //p["p_fr_ratio_vs_eta"].SetLegendTextSize(0.042);
    //p["p_fr_ratio_vs_eta"].AddText("p^{l}_{T} > 20 GeV", 0.60, 0.835);


    // print
    hc.Print(path, suffix);
    //rt::Print(p, path, suffix);
}

void PrintFRDiffPlot(const std::string& suffix = "png")
{
    float max = 0.1;
    float min = -0.1;
    string path = "plots/fake_rates/compare_19p5";

	// set style
	rt::SetTDRStyle();
	gStyle->SetTitleBorderSize(0);

	rt::TH1Container hc1("data/fake_rates/ssFR_data_standard_24Sep2012.root");
	rt::TH1Container hc2("data/fake_rates/ssFR_data_standard_16Dec2012.root");
	rt::TH1Container hc;

    float lumi1 = 10.5;
    float lumi2 = 19.5;

    string mu_title = Form("Difference of #mu fake rates (%1.1f FR - %1.1f FR)/%1.1f FR"     , lumi2, lumi1, lumi2);
    string el_title = Form("Difference of electron fake rates (%1.1f FR - %1.1f FR)/%1.1f FR", lumi2, lumi1, lumi2);

	hc.Add(dynamic_cast<TH1*>(hc2["h_mufr40c_vs_pt"]->Clone("h_mufr_diff_vs_pt")));
	hc["h_mufr_diff_vs_pt"]->SetTitle(Form("%s;p_{T} (GeV)", mu_title.c_str()));
	hc["h_mufr_diff_vs_pt"]->Add(hc1["h_mufr40c_vs_pt"], -1.0);
	hc["h_mufr_diff_vs_pt"]->Divide(hc2["h_mufr40c_vs_pt"]);
	hc["h_mufr_diff_vs_pt"]->GetYaxis()->SetRangeUser(min, max);
	hc["h_mufr_diff_vs_pt"]->SetMarkerSize(1.4);
	hc["h_mufr_diff_vs_pt"]->SetMarkerStyle(20);
	hc["h_mufr_diff_vs_pt"]->SetLineWidth(2);
	hc["h_mufr_diff_vs_pt"]->Draw();

	hc.Add(dynamic_cast<TH1*>(hc2["h_mufr40c_vs_eta"]->Clone("h_mufr_diff_vs_eta")));
	hc["h_mufr_diff_vs_eta"]->SetTitle(Form("%s;|#eta|", mu_title.c_str()));
	hc["h_mufr_diff_vs_eta"]->Add(hc1["h_mufr40c_vs_eta"], -1.0);
	hc["h_mufr_diff_vs_eta"]->Divide(hc2["h_mufr40c_vs_eta"]);
	hc["h_mufr_diff_vs_eta"]->GetYaxis()->SetRangeUser(min, max);
	hc["h_mufr_diff_vs_eta"]->SetMarkerSize(1.4);
	hc["h_mufr_diff_vs_eta"]->SetMarkerStyle(20);
	hc["h_mufr_diff_vs_eta"]->SetLineWidth(2);
	hc["h_mufr_diff_vs_eta"]->Draw();

	hc.Add(dynamic_cast<TH1*>(hc2["h_mufr40c_vs_nvtxs"]->Clone("h_mufr_diff_vs_nvtxs")));
	hc["h_mufr_diff_vs_nvtxs"]->SetTitle(Form("%s;# vertices", mu_title.c_str()));
	hc["h_mufr_diff_vs_nvtxs"]->Add(hc1["h_mufr40c_vs_nvtxs"], -1.0);
	hc["h_mufr_diff_vs_nvtxs"]->Divide(hc2["h_mufr40c_vs_nvtxs"]);
	hc["h_mufr_diff_vs_nvtxs"]->GetYaxis()->SetRangeUser(min, max);
	hc["h_mufr_diff_vs_nvtxs"]->SetMarkerSize(1.4);
	hc["h_mufr_diff_vs_nvtxs"]->SetMarkerStyle(20);
	hc["h_mufr_diff_vs_nvtxs"]->SetLineWidth(2);
	hc["h_mufr_diff_vs_nvtxs"]->Draw();

	hc.Add(dynamic_cast<TH1*>(hc2["h_elfr40c_vs_pt"]->Clone("h_elfr_diff_vs_pt")));
	hc["h_elfr_diff_vs_pt"]->SetTitle(Form("%s;p_{T} (GeV)", el_title.c_str()));
	hc["h_elfr_diff_vs_pt"]->Add(hc1["h_elfr40c_vs_pt"], -1.0);
	hc["h_elfr_diff_vs_pt"]->Divide(hc2["h_elfr40c_vs_pt"]);
	hc["h_elfr_diff_vs_pt"]->GetYaxis()->SetRangeUser(min, max);
	hc["h_elfr_diff_vs_pt"]->SetMarkerSize(1.4);
	hc["h_elfr_diff_vs_pt"]->SetMarkerStyle(20);
	hc["h_elfr_diff_vs_pt"]->SetLineWidth(2);
	hc["h_elfr_diff_vs_pt"]->Draw();

	hc.Add(dynamic_cast<TH1*>(hc2["h_elfr40c_vs_eta"]->Clone("h_elfr_diff_vs_eta")));
	hc["h_elfr_diff_vs_eta"]->SetTitle(Form("%s;|#eta|", el_title.c_str()));
	hc["h_elfr_diff_vs_eta"]->Add(hc1["h_elfr40c_vs_eta"], -1.0);
	hc["h_elfr_diff_vs_eta"]->Divide(hc2["h_elfr40c_vs_eta"]);
	hc["h_elfr_diff_vs_eta"]->GetYaxis()->SetRangeUser(min, max);
	hc["h_elfr_diff_vs_eta"]->SetMarkerSize(1.4);
	hc["h_elfr_diff_vs_eta"]->SetMarkerStyle(20);
	hc["h_elfr_diff_vs_eta"]->SetLineWidth(2);
	hc["h_elfr_diff_vs_eta"]->Draw();

	hc.Add(dynamic_cast<TH1*>(hc2["h_elfr40c_vs_nvtxs"]->Clone("h_elfr_diff_vs_nvtxs")));
	hc["h_elfr_diff_vs_nvtxs"]->SetTitle(Form("%s;# vertices", el_title.c_str()));
	hc["h_elfr_diff_vs_nvtxs"]->Add(hc1["h_elfr40c_vs_nvtxs"], -1.0);
	hc["h_elfr_diff_vs_nvtxs"]->Divide(hc2["h_elfr40c_vs_nvtxs"]);
	hc["h_elfr_diff_vs_nvtxs"]->GetYaxis()->SetRangeUser(min, max);
	hc["h_elfr_diff_vs_nvtxs"]->SetMarkerSize(1.4);
	hc["h_elfr_diff_vs_nvtxs"]->SetMarkerStyle(20);
	hc["h_elfr_diff_vs_nvtxs"]->SetLineWidth(2);
	hc["h_elfr_diff_vs_nvtxs"]->Draw();

    // overlay
	//std::map<std::string, rt::TH1Overlay> p;
    //p["p_fr_diff_vs_pt"] = rt::TH1Overlay("diff of fake rates (12.3 FR - 10.5 FR);p_{T} (GeV)", "sb::off lg::top_left");
    //p["p_fr_diff_vs_pt"].Add(hc["h_mufr_diff_vs_pt"], "muons"    , kBlue, 2, 20);
    //p["p_fr_diff_vs_pt"].Add(hc["h_elfr_diff_vs_pt"], "electrons", kRed , 2, 22);
    //p["p_fr_diff_vs_pt"].SetYAxisRange(min, max);
    //p["p_fr_diff_vs_pt"].SetLegendOption("p");
    //p["p_fr_diff_vs_pt"].SetLegendTextSize(0.042);

    //p["p_fr_diff_vs_nvtxs"] = rt::TH1Overlay("diff of fake rates (12.3 FR - 10.5 FR);# vertices", "sb::off lg::top_left");
    //p["p_fr_diff_vs_nvtxs"].Add(hc["h_mufr_diff_vs_nvtxs"], "muons"    , kBlue, 2, 20);
    //p["p_fr_diff_vs_nvtxs"].Add(hc["h_elfr_diff_vs_nvtxs"], "electrons", kRed , 2, 22);
    //p["p_fr_diff_vs_nvtxs"].SetYAxisRange(min, max);
    //p["p_fr_diff_vs_nvtxs"].SetLegendOption("p");
    //p["p_fr_diff_vs_nvtxs"].SetLegendTextSize(0.042);
    //p["p_fr_diff_vs_nvtxs"].AddText("p^{l}_{T} > 20 GeV", 0.60, 0.835);

    //p["p_fr_diff_vs_eta"] = rt::TH1Overlay("diff of fake rates (12.3 FR - 10.5 FR);|#eta|", "sb::off lg::top_left");
    //p["p_fr_diff_vs_eta"].Add(hc["h_mufr_diff_vs_eta"], "muons"    , kBlue, 2, 20);
    //p["p_fr_diff_vs_eta"].Add(hc["h_elfr_diff_vs_eta"], "electrons", kRed , 2, 22);
    //p["p_fr_diff_vs_eta"].SetYAxisRange(min, max);
    //p["p_fr_diff_vs_eta"].SetLegendOption("p");
    //p["p_fr_diff_vs_eta"].SetLegendTextSize(0.042);
    //p["p_fr_diff_vs_eta"].AddText("p^{l}_{T} > 20 GeV", 0.60, 0.835);

    // print
    hc.Print(path, suffix);
    //rt::Print(p, path, suffix);
}
