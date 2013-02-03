#include "rt/RootTools.h"
#include "CTable.h"
#include <string>
#include "TChain.h"
#include "TCut.h"
#include "TEventList.h"

using namespace std;
using namespace rt;

void OverlayFR2011Plots(const string& suffix = "png")
{
    // style
    rt::SetTDRStyle();
    gStyle->SetTitleOffset(1.10, "X");
    gStyle->SetTitleSize(0.06, "XYZ");

    // parameters
    string title = "CMS Preliminary, #sqrt{s} = 7 TeV"; 
    string qcd_title = "QCD MC";
    string ttb_title = "t#bar{t} MC";
    Color_t qcd_color = kRed;
    Color_t ttb_color = kBlue;
    Style_t qcd_marker = 20;
    Style_t ttb_marker = 23;
    Width_t width = 2;

    // histograms
    TH1Container hc_qcd("plots/qcd11/qcd11.root");
    TH1Container hc_ttb("plots/ttbar11/ttbar11.root");

    hc_qcd.SetMarkerStyle(qcd_marker);
    hc_ttb.SetMarkerStyle(ttb_marker);

    // overlays
    // --------------------------------------------------------------------------------------------------------- //

    map<string, TH1Overlay> p;
    TH1Overlay::legend_offset_default    = 0.025;
    TH1Overlay::legend_option_default    = "lep";
    TH1Overlay::legend_text_size_default = 0.05;

    TLatex last_bin (0.6, 0.70, "last bin is overflow");
    TLatex unit_area(0.6, 0.70, "normalized to unit area");
    last_bin.SetTextSize(0.035);
    unit_area.SetTextSize(0.035);

    // kinematics
    p["p_mc3_id"] = TH1Overlay(Form("%s;#mu matched mother parton |pdg ID|", title.c_str()), "hist dt::norm lg::top_right");
    p["p_mc3_id"].Add(hc_qcd["h_mc3_id"], qcd_title, qcd_color, width, qcd_marker);
    p["p_mc3_id"].Add(hc_ttb["h_mc3_id"], ttb_title, ttb_color, width, ttb_marker);
    p["p_mc3_id"].SetLegendOption("L");
    p["p_mc3_id"].AddText(unit_area);

    unit_area.SetX(0.60);
    unit_area.SetY(0.65);

    p["p_mc3_pt"] = TH1Overlay(Form("%s;#mu matched mother parton p_{T} (GeV)", title.c_str()), "dt::norm lg::top_right");
    p["p_mc3_pt"].Add(hc_qcd["h_mc3_pt"], qcd_title, qcd_color, width, qcd_marker);
    p["p_mc3_pt"].Add(hc_ttb["h_mc3_pt"], ttb_title, ttb_color, width, ttb_marker);
    p["p_mc3_pt"].AddText(last_bin);
    p["p_mc3_pt"].AddText(unit_area);

    p["p_mc3_40c_pt"] = TH1Overlay(Form("%s;#mu matched mother parton p_{T} (GeV)", title.c_str()), "dt::norm lg::top_right");
    p["p_mc3_40c_pt"].Add(hc_qcd["h_mc3_40c_pt"], qcd_title, qcd_color, width, qcd_marker);
    p["p_mc3_40c_pt"].Add(hc_ttb["h_mc3_40c_pt"], ttb_title, ttb_color, width, ttb_marker);
    p["p_mc3_40c_pt"].AddText(last_bin);
    p["p_mc3_40c_pt"].AddText(unit_area);

    p["p_mc3_fo_pt"] = TH1Overlay(Form("%s;#mu matched mother parton p_{T} (GeV)", title.c_str()), "dt::norm lg::top_right");
    p["p_mc3_fo_pt"].Add(hc_qcd["h_mc3_fo_pt"], qcd_title, qcd_color, width, qcd_marker);
    p["p_mc3_fo_pt"].Add(hc_ttb["h_mc3_fo_pt"], ttb_title, ttb_color, width, ttb_marker);
    p["p_mc3_fo_pt"].AddText(last_bin);
    p["p_mc3_fo_pt"].AddText(unit_area);


    // isolation 
    TLatex num_label(0.2, 0.85, "num");
    num_label.SetTextSize(0.025);
    num_label.SetTextColor(kGreen+2);
    TLine num_line(0.1, 0.0, 0.1, 0.19); 
    num_line.SetLineColor(kGreen+2); 
    num_line.SetLineStyle(2);
    num_line.SetLineWidth(2);

    TLatex den_label(0.32, 0.85, "den");
    den_label.SetTextSize(0.025);
    den_label.SetTextColor(kBlack);
    TLine den_line(0.4, 0.0, 0.4, 0.19); 
    den_line.SetLineColor(kBlack); 
    den_line.SetLineStyle(2);
    den_line.SetLineWidth(2);

    p["p_reliso_foslice_mc3slice_a"] = TH1Overlay(Form("%s;Relative Isolation of #mu from b-quark", title.c_str()), "hist dt::norm lg::top_right");
    p["p_reliso_foslice_mc3slice_a"].Add(hc_qcd["h_reliso_foslice_mc3slice35_45"], static_cast<Color_t>(kBlue), width, qcd_marker);
    p["p_reliso_foslice_mc3slice_a"].Add(hc_qcd["h_reliso_foslice_mc3slice45_55"], static_cast<Color_t>(kRed ), width, ttb_marker);
    p["p_reliso_foslice_mc3slice_a"].SetYAxisRange(0, 0.2);
    p["p_reliso_foslice_mc3slice_a"].AddLine(num_line);
    p["p_reliso_foslice_mc3slice_a"].AddLine(den_line);
    p["p_reliso_foslice_mc3slice_a"].AddText(num_label);
    p["p_reliso_foslice_mc3slice_a"].AddText(den_label);
    p["p_reliso_foslice_mc3slice_a"].SetLegendOption("L");

    p["p_reliso_foslice_mc3slice_b"] = TH1Overlay(Form("%s;Relative Isolation of #mu from b-quars", title.c_str()), "hist dt::norm lg::top_right");
    p["p_reliso_foslice_mc3slice_b"].Add(hc_qcd["h_reliso_foslice_mc3slice55_65"], static_cast<Color_t>(kBlue), width, qcd_marker);
    p["p_reliso_foslice_mc3slice_b"].Add(hc_qcd["h_reliso_foslice_mc3slice65_75"], static_cast<Color_t>(kRed ), width, ttb_marker);
    p["p_reliso_foslice_mc3slice_b"].SetYAxisRange(0, 0.2);
    p["p_reliso_foslice_mc3slice_b"].AddLine(num_line);
    p["p_reliso_foslice_mc3slice_b"].AddLine(den_line);
    p["p_reliso_foslice_mc3slice_b"].AddText(num_label);
    p["p_reliso_foslice_mc3slice_b"].AddText(den_label);
    p["p_reliso_foslice_mc3slice_b"].SetLegendOption("L");

    // isolation
    p["p_reliso_directb_foslice2"] = TH1Overlay(Form("%s;Relative Isolation of #mu from b-quars", title.c_str()), "dt::norm lg::bottom");
    p["p_reliso_directb_foslice2"].Add(hc_qcd["h_reliso_directb_foslice2"], qcd_title, qcd_color, width, qcd_marker);
    p["p_reliso_directb_foslice2"].Add(hc_ttb["h_reliso_directb_foslice2"], ttb_title, ttb_color, width, ttb_marker);

    p["p_reliso_directb_foslice2_mc3slice5"] = TH1Overlay(Form("%s;Relative Isolation of #mu from b-quars", title.c_str()), "dt::norm lg::bottom");
    p["p_reliso_directb_foslice2_mc3slice5"].Add(hc_qcd["h_reliso_directb_foslice2_mc3slice5"], qcd_title, qcd_color, width, qcd_marker);
    p["p_reliso_directb_foslice2_mc3slice5"].Add(hc_ttb["h_reliso_directb_foslice2_mc3slice5"], ttb_title, ttb_color, width, ttb_marker);

    // original FR
    p["p_mufr40c_vs_pt"] = TH1Overlay(Form("%s;p_{T}^{#mu} (GeV);TL ratio", title.c_str()), "lg::top_right");
    p["p_mufr40c_vs_pt"].Add(hc_qcd["h_mufr40c_vs_pt"], qcd_title, qcd_color, width, qcd_marker);
    p["p_mufr40c_vs_pt"].Add(hc_ttb["h_mufr40c_vs_pt"], ttb_title, ttb_color, width, ttb_marker);
    p["p_mufr40c_vs_pt"].SetYAxisRange(0.0, 0.3);

    p["p_mufr40c_vs_eta"] = TH1Overlay(Form("%s;|#eta^{#mu}|;TL ratio", title.c_str()), "lg::top_right");
    p["p_mufr40c_vs_eta"].Add(hc_qcd["h_mufr40c_vs_eta"], qcd_title, qcd_color, width, qcd_marker);
    p["p_mufr40c_vs_eta"].Add(hc_ttb["h_mufr40c_vs_eta"], ttb_title, ttb_color, width, ttb_marker);
    p["p_mufr40c_vs_eta"].SetYAxisRange(0.0, 0.3);

    // b-quark matched FR
    p["p_mufr40c_directb_vs_pt"] = TH1Overlay(Form("%s;p_{T}^{#mu} (GeV);TL ratio", title.c_str()), "lg::top_right");
    p["p_mufr40c_directb_vs_pt"].Add(hc_qcd["h_mufr40c_directb_vs_pt"], qcd_title, qcd_color, width, qcd_marker);
    p["p_mufr40c_directb_vs_pt"].Add(hc_ttb["h_mufr40c_directb_vs_pt"], ttb_title, ttb_color, width, ttb_marker);
    p["p_mufr40c_directb_vs_pt"].SetYAxisRange(0.0, 0.3);

    p["p_mufr40c_directb_vs_eta"] = TH1Overlay(Form("%s;|#eta^{#mu}|;TL ratio", title.c_str()), "lg::top_right");
    p["p_mufr40c_directb_vs_eta"].Add(hc_qcd["h_mufr40c_directb_vs_eta"], qcd_title, qcd_color, width, qcd_marker);
    p["p_mufr40c_directb_vs_eta"].Add(hc_ttb["h_mufr40c_directb_vs_eta"], ttb_title, ttb_color, width, ttb_marker);
    p["p_mufr40c_directb_vs_eta"].SetYAxisRange(0.0, 0.3);

    // b-quark matched FR
    p["p_mufr40c_directb_slice5_vs_pt"] = TH1Overlay(Form("%s;p_{T}^{#mu} (GeV);TL ratio", title.c_str()), "lg::top_right");
    p["p_mufr40c_directb_slice5_vs_pt"].Add(hc_qcd["h_mufr40c_directb_slice5_vs_pt"], qcd_title, qcd_color, width, qcd_marker);
    p["p_mufr40c_directb_slice5_vs_pt"].Add(hc_ttb["h_mufr40c_directb_slice5_vs_pt"], ttb_title, ttb_color, width, ttb_marker);
    p["p_mufr40c_directb_slice5_vs_pt"].SetYAxisRange(0.0, 0.3);

    p["p_mufr40c_directb_slice5_vs_eta"] = TH1Overlay(Form("%s;|#eta^{#mu}|;TL ratio", title.c_str()), "lg::top_right");
    p["p_mufr40c_directb_slice5_vs_eta"].Add(hc_qcd["h_mufr40c_directb_slice5_vs_eta"], qcd_title, qcd_color, width, qcd_marker);
    p["p_mufr40c_directb_slice5_vs_eta"].Add(hc_ttb["h_mufr40c_directb_slice5_vs_eta"], ttb_title, ttb_color, width, ttb_marker);
    p["p_mufr40c_directb_slice5_vs_eta"].SetYAxisRange(0.0, 0.3);

    // FR(mc3 pt)
    p["p_mufr40c_directb_vs_mc3"] = TH1Overlay(Form("%s;p_{T}^{b} (GeV);TL ratio", title.c_str()), "lg::top_right");
    p["p_mufr40c_directb_vs_mc3"].Add(hc_qcd["h_mufr40c_vs_mc3"], qcd_title, qcd_color, width, qcd_marker);
    p["p_mufr40c_directb_vs_mc3"].Add(hc_ttb["h_mufr40c_vs_mc3"], ttb_title, ttb_color, width, ttb_marker);
    p["p_mufr40c_directb_vs_mc3"].SetYAxisRange(0.0, 0.3);

    //TH1Overlay* p_test = new TH1Overlay(p["p_reliso_foslice_mc3slice_a"]);
    //TH1Overlay* p_test = new TH1Overlay(p["p_mc3_pt"]);
    TH1Overlay* p_test = new TH1Overlay(p["p_mufr40c_vs_eta"]);
    p_test->Draw();

    // print
    Print(p, "plots/fr_note", suffix);
}

TH1* ScaleFactorHist(TH1* h_mc, TH1* h_data, const std::string& name = "h_sf", const std::string& title = "scale factor")
{
	//h_mc->SetAxisRange(20, 34, "X");
	//h_data->SetAxisRange(20, 34, "X");
	h_mc->SetAxisRange(0.0, 2.5, "Y");
	h_data->SetAxisRange(0.0, 2.5, "Y");
	TH1* h_sf = dynamic_cast<TH1*>(h_data->Clone(name.c_str()));
	h_sf->SetTitle(title.c_str());
	h_sf->Divide(h_mc);
	return h_sf;
}

void OverlayFR2012Plots(const string& suffix = "png")
{
    // style
    rt::SetTDRStyle();

    // parameters
    string title = "CMS Preliminary, #sqrt{s} = 8 TeV"; 
    string data_title = "data";
    string qcd_title  = "QCD MC";
    string ttb_title  = "t#bar{t} MC";
    Color_t data_color = kBlack;
    Color_t qcd_color  = kRed;
    Color_t ttb_color  = kBlue;
    Style_t data_marker = 20;
    Style_t qcd_marker  = 23;
    Style_t ttb_marker  = 24;
    Width_t width = 2;

    // histograms
    TH1Container hc_qcd ("plots/qcd/qcd.root");
    TH1Container hc_ttb ("plots/ttbar/ttbar.root");
    TH1Container hc_data("plots/data/data.root");

    hc_qcd.SetMarkerStyle(qcd_marker);
    hc_ttb.SetMarkerStyle(ttb_marker);

    // overlays
    // --------------------------------------------------------------------------------------------------------- //

    map<string, TH1Overlay> p;
    TH1Overlay::legend_offset_default    = 0.025;
    TH1Overlay::legend_option_default    = "lep";
    TH1Overlay::legend_text_size_default = 0.05;

	// jet40, dphi 2.5 (with btag)
	p["p_mufr40c_dphi2p5_btag_vs_pt"] = rt::TH1Overlay(Form("%s;p_{T} (GeV); TL Ratio", title.c_str()), "lg::top_right");
	p["p_mufr40c_dphi2p5_btag_vs_pt"].Add(hc_data["h_mufr_dphi2p5_btag_vs_pt"], data_title, data_color, width, data_marker);
	p["p_mufr40c_dphi2p5_btag_vs_pt"].Add(hc_qcd ["h_mufr_dphi2p5_btag_vs_pt"], qcd_title , qcd_color , width, qcd_marker );
	p["p_mufr40c_dphi2p5_btag_vs_pt"].SetYAxisRange(0, 0.35);
	p["p_mufr40c_dphi2p5_btag_vs_pt"].AddText("#mu FR (away jet p_{T}> 40 GeV, b-tagged, #Delta#phi > 2.5)", 0.2, 0.75);

	// data fr with and wo btag 
	p["p_mufr40c_btag_vs_nobtag_data_vs_pt"] = rt::TH1Overlay(Form("%s;p_{T} (GeV); TL Ratio", title.c_str()), "lg::top_right");
	p["p_mufr40c_btag_vs_nobtag_data_vs_pt"].Add(hc_data["h_mufr40c_vs_pt"     ], "original", kBlack, width, 20);
	p["p_mufr40c_btag_vs_nobtag_data_vs_pt"].Add(hc_data["h_mufr40c_btag_vs_pt"], "b-tagged", kRed  , width, 23);
	p["p_mufr40c_btag_vs_nobtag_data_vs_pt"].SetYAxisRange(0, 0.5);
	p["p_mufr40c_btag_vs_nobtag_data_vs_pt"].AddText("#mu FR (away jet p_{T} > 40 GeV)", 0.4, 0.75);

	p["p_dphi_compare"] = rt::TH1Overlay(Form("%s;#Delta#phi", title.c_str()), "lg::top_left dt::norm");
	p["p_dphi_compare"].Add(hc_data["h_dphi"], data_title, data_color, width, data_marker);
	p["p_dphi_compare"].Add(hc_qcd ["h_dphi"], qcd_title , qcd_color , width, qcd_marker );
	p["p_dphi_compare"].AddText("#Delta#phi(#mu, away jet) (away jet p_{T} > 40 GeV)", 0.2, 0.73, 0.04);
	p["p_dphi_compare"].AddText("normalized to unit area", 0.2, 0.67, 0.04);

	p["p_njets40"] = rt::TH1Overlay(Form("%s;number of jets", title.c_str()), "lg::top_right dt::norm");
	p["p_njets40"].Add(hc_data["h_njets40"], data_title, data_color, width, data_marker);
	p["p_njets40"].Add(hc_qcd ["h_njets40"], qcd_title , qcd_color , width, qcd_marker );
	p["p_njets40"].AddText("#mu FR (away jet p_{T} > 40 GeV, #Delta#phi > 2.5)", 0.45, 0.70, 0.035);

	TH1* h_sf = ScaleFactorHist(hc_qcd["h_mufr_dphi2p5_btag_vs_pt"], hc_data["h_mufr_dphi2p5_btag_vs_pt"], "h_mu40csf_dphi2p5_btag_vs_pt", "data/MC scale factor (away jet > 40, #Delta#Phi > 2.5);p_{T}");
    h_sf->Draw();

	p["p_mu40sf_dphi2p5_btag_vs_pt"] = rt::TH1Overlay(Form("%s;p_{T} (GeV); data/MC ratio", title.c_str()), "lg::off");
	p["p_mu40sf_dphi2p5_btag_vs_pt"].Add(h_sf, data_title, data_color, width, data_marker);
	p["p_mu40sf_dphi2p5_btag_vs_pt"].AddText("data/MC scale factor (away jet p_{T} > 40 GeV, btag, #Delta#phi > 2.5)", 0.25, 0.25);

	p["p_mc3pt_vs_ajetpt"] = rt::TH1Overlay(Form("%s;matched b-quark p_{T} (GeV); away b-tagged jet p_{T} (GeV);", title.c_str()), "lg::off sb::off box");
	p["p_mc3pt_vs_ajetpt"].Add(hc_qcd["h_mc3pt_vs_ajetpt_db_btag"], data_title, data_color, width, data_marker);
	//p["p_mc3pt_vs_ajetpt"].AddText("data/MC scale factor (away jet p_{T} > 40 GeV, btag, #Delta#phi > 2.5)", 0.25, 0.25);

    TH1* h_mufr40c_ttbar_rescaled_vs_pt = dynamic_cast<TH1*>(hc_ttb["h_mufr40c_vs_pt"]->Clone("h_mufr40c_ttbar_rescaled_vs_pt"));
    h_mufr40c_ttbar_rescaled_vs_pt->Multiply(h_sf);

    hc_ttb["h_mufr40c_vs_pt"]->GetXaxis()->SetRangeUser(20, 34.99);
    h_mufr40c_ttbar_rescaled_vs_pt->GetXaxis()->SetRangeUser(20, 34.99);

    // reduce range
    TH1F h1("h1", "h1", 3, 20, 35);
    h1.SetBinContent(1, hc_ttb["h_mufr40c_vs_pt"]->GetBinContent(1));
    h1.SetBinContent(2, hc_ttb["h_mufr40c_vs_pt"]->GetBinContent(2));
    h1.SetBinContent(3, hc_ttb["h_mufr40c_vs_pt"]->GetBinContent(3));
    h1.SetBinError(1, hc_ttb["h_mufr40c_vs_pt"]->GetBinError(1));
    h1.SetBinError(2, hc_ttb["h_mufr40c_vs_pt"]->GetBinError(2));
    h1.SetBinError(3, hc_ttb["h_mufr40c_vs_pt"]->GetBinError(3));

    TH1F h2("h2", "h2", 3, 20, 35);
    h2.SetBinContent(1, h_mufr40c_ttbar_rescaled_vs_pt->GetBinContent(1));
    h2.SetBinContent(2, h_mufr40c_ttbar_rescaled_vs_pt->GetBinContent(2));
    h2.SetBinContent(3, h_mufr40c_ttbar_rescaled_vs_pt->GetBinContent(3));
    h2.SetBinError(1, h_mufr40c_ttbar_rescaled_vs_pt->GetBinError(1));
    h2.SetBinError(2, h_mufr40c_ttbar_rescaled_vs_pt->GetBinError(2));
    h2.SetBinError(3, h_mufr40c_ttbar_rescaled_vs_pt->GetBinError(3));

    TH1F h3("h3", "h3", 3, 20, 35);
    h3.SetBinContent(1, hc_qcd["h_mufr_dphi2p5_btag_vs_pt"]->GetBinContent(1));
    h3.SetBinContent(2, hc_qcd["h_mufr_dphi2p5_btag_vs_pt"]->GetBinContent(2));
    h3.SetBinContent(3, hc_qcd["h_mufr_dphi2p5_btag_vs_pt"]->GetBinContent(3));
    h3.SetBinError(1, hc_qcd["h_mufr_dphi2p5_btag_vs_pt"]->GetBinError(1));
    h3.SetBinError(2, hc_qcd["h_mufr_dphi2p5_btag_vs_pt"]->GetBinError(2));
    h3.SetBinError(3, hc_qcd["h_mufr_dphi2p5_btag_vs_pt"]->GetBinError(3));

    TH1F h4("h4", "h4", 3, 20, 35);
    h4.SetBinContent(1, hc_data["h_mufr_dphi2p5_btag_vs_pt"]->GetBinContent(1));
    h4.SetBinContent(2, hc_data["h_mufr_dphi2p5_btag_vs_pt"]->GetBinContent(2));
    h4.SetBinContent(3, hc_data["h_mufr_dphi2p5_btag_vs_pt"]->GetBinContent(3));
    h4.SetBinError(1, hc_data["h_mufr_dphi2p5_btag_vs_pt"]->GetBinError(1));
    h4.SetBinError(2, hc_data["h_mufr_dphi2p5_btag_vs_pt"]->GetBinError(2));
    h4.SetBinError(3, hc_data["h_mufr_dphi2p5_btag_vs_pt"]->GetBinError(3));

    TH1F h5("h5", "h5", 3, 20, 35);
    h5.SetBinContent(1, h_sf->GetBinContent(1));
    h5.SetBinContent(2, h_sf->GetBinContent(2));
    h5.SetBinContent(3, h_sf->GetBinContent(3));
    h5.SetBinError(1, h_sf->GetBinError(1));
    h5.SetBinError(2, h_sf->GetBinError(2));
    h5.SetBinError(3, h_sf->GetBinError(3));

	p["p_mufr40c_dphi2p5_vs_pt_ttbar"] = rt::TH1Overlay(Form("%s;p_{T} (GeV); TL Ratio", title.c_str()), "lg::top_right");
	p["p_mufr40c_dphi2p5_vs_pt_ttbar"].Add(&h1, ttb_title        , ttb_color, width, ttb_marker);
	p["p_mufr40c_dphi2p5_vs_pt_ttbar"].Add(&h2, "t#bar{t} MC SF" , kGreen+2 , width, 23);
	p["p_mufr40c_dphi2p5_vs_pt_ttbar"].AddText("#mu Fake Rate", 0.25, 0.45, 0.05);

	p["p_mufr40c_dphi2p5_vs_pt_compare"] = rt::TH1Overlay(Form("%s;p_{T} (GeV); TL Ratio", title.c_str()), "lg::bottom_left");
	p["p_mufr40c_dphi2p5_vs_pt_compare"].Add(&h1, ttb_title        , ttb_color, width, ttb_marker);
	p["p_mufr40c_dphi2p5_vs_pt_compare"].Add(&h2, "t#bar{t} MC SF" , kGreen+2 , width, 22);
	p["p_mufr40c_dphi2p5_vs_pt_compare"].Add(&h3, "QCD MC"         , qcd_color, width, qcd_marker);
	p["p_mufr40c_dphi2p5_vs_pt_compare"].AddText("#mu Fake Rate", 0.25, 0.45, 0.05);

	p["p_mufr40c_dphi2p5_vs_pt_before"] = rt::TH1Overlay(Form("%s;p_{T} (GeV); TL Ratio", title.c_str()), "lg::bottom_left");
	p["p_mufr40c_dphi2p5_vs_pt_before"].Add(&h4, data_title,  data_color, width, data_marker);
	p["p_mufr40c_dphi2p5_vs_pt_before"].Add(&h1,  ttb_title,   ttb_color, width,  ttb_marker);
	p["p_mufr40c_dphi2p5_vs_pt_before"].Add(&h3,  qcd_title,   qcd_color, width,  qcd_marker);
	p["p_mufr40c_dphi2p5_vs_pt_before"].AddText("#mu Fake Rate", 0.25, 0.45, 0.05);

	p["p_sf"] = rt::TH1Overlay(Form("%s;p_{T} (GeV); data/QCD MC scale factor", title.c_str()), "lg::off sb::off box");
	p["p_sf"].Add(&h5, data_title, data_color, width, data_marker);
	p["p_sf"].SetYAxisRange(0.0, 2.0);

    TH1Overlay* p_test = new TH1Overlay(p["p_mufr40c_dphi2p5_vs_pt_ttbar"]);
    p_test->Draw();

    // print
    Print(p, "plots/fr_note", suffix);
}

void Rescale(TH1* h_sf, TH2* h_fr2D)
{
    for (int xbin = 1; xbin != h_fr2D->GetNbinsX()+1; xbin++)
    {
        for (int ybin = 1; ybin != h_fr2D->GetNbinsY()+1; ybin++)
        {
            float value = h_fr2D->GetBinContent(xbin, ybin);
            float sf    = h_sf->GetBinContent(ybin);
            h_fr2D->SetBinContent(xbin, ybin, value * sf);
        }
    }
}

void CreateTTbarFakeRateFile()
{
	rt::TH1Container hc_data ("plots/data/data_pt35.root");
	rt::TH1Container hc_qcd  ("plots/qcd/qcd_pt35.root");
	rt::TH1Container hc_ttbar("plots/ttbar/ttbar_pt35.root");
	rt::TH1Container hc_el   ("../ss2012/data/fake_rates/ssFR_data_standard_23May2012.root");
	rt::TH1Container hc;

	std::map<std::string, rt::TH1Overlay> p;

	hc.Add(ScaleFactorHist(hc_qcd["h_mufr_dphi2p5_btag_vs_pt"], hc_data["h_mufr_dphi2p5_btag_vs_pt"], "h_musf40c_dphi2p5_btag_vs_pt", "data/QCD scale factor (away jet > 40, #Delta#Phi > 2.5);p_{T}"));
    hc.Add(dynamic_cast<TH1*>(hc_ttbar["h_mufr40c_vs_pt"]->Clone("h_mufr40c_ttbar_rescaled_vs_pt")));
    hc["h_mufr40c_ttbar_rescaled_vs_pt"]->Multiply(hc["h_musf40c_dphi2p5_btag_vs_pt"]);

    hc.Add(dynamic_cast<TH1*>(hc_ttbar["h_mufr40c"]->Clone("h_mufr40c_ttbar_rescaled")));
    Rescale(hc["h_musf40c_dphi2p5_btag_vs_pt"], dynamic_cast<TH2*>(hc["h_mufr40c_ttbar_rescaled"]));

    // keep the standard FR(pt, eta)
    hc.Add(dynamic_cast<TH1*>(hc_data ["h_mufr40c"]->Clone("h_mufr40c_data" )));
    hc.Add(dynamic_cast<TH1*>(hc_qcd  ["h_mufr40c"]->Clone("h_mufr40c_qcd"  )));
    hc.Add(dynamic_cast<TH1*>(hc_ttbar["h_mufr40c"]->Clone("h_mufr40c_ttbar")));
    hc.Add(dynamic_cast<TH1*>(hc_data ["h_mufr40c_vs_pt"]->Clone("h_mufr40c_data_pt" )));
    hc.Add(dynamic_cast<TH1*>(hc_qcd  ["h_mufr40c_vs_pt"]->Clone("h_mufr40c_qcd_pt"  )));
    hc.Add(dynamic_cast<TH1*>(hc_ttbar["h_mufr40c_vs_pt"]->Clone("h_mufr40c_ttbar_pt")));
    hc.Add(hc_el["h_elfr40c"]);
    hc.Add(hc_el["h_mufr40c"]);

    // keep the new FR(pt)
    hc.Add(dynamic_cast<TH1*>(hc_data ["h_mufr_dphi2p5_btag_vs_pt"]->Clone("h_mufr40c_dphi2p5_btag_data_vs_pt")));
    hc.Add(dynamic_cast<TH1*>(hc_qcd  ["h_mufr_dphi2p5_btag_vs_pt"]->Clone("h_mufr40c_dphi2p5_btag_qcd_vs_pt" )));
    hc.Add(dynamic_cast<TH1*>(hc_ttbar["h_mufr40c_vs_pt"          ]->Clone("h_mufr40c_ttbar_vs_pt"            )));
	
    // keep the new FR(eta, pt)
    hc.Add(dynamic_cast<TH1*>(hc_data ["h_mufr_dphi2p5_btag"]->Clone("h_mufr40c_dphi2p5_btag_data")));
    hc.Add(dynamic_cast<TH1*>(hc_qcd  ["h_mufr_dphi2p5_btag"]->Clone("h_mufr40c_dphi2p5_btag_qcd" )));
	
	// print
    hc.Write("plots/ttbar/ttbar_sf.root", "", "RECREATE");
}

void CreateTTbarFakeRateFile2()
{
	rt::TH1Container hc_data ("plots/data/data_pt55.root");
	rt::TH1Container hc_qcd  ("plots/qcd/qcd_pt55.root");
	rt::TH1Container hc_ttbar("plots/ttbar/ttbar_pt55.root");
	rt::TH1Container hc_dy   ("plots/dy/dy_pt55.root");
	rt::TH1Container hc_wjets("plots/wjets/wjets_pt55.root");
	//rt::TH1Container hc_data ("plots/data/data_pt35.root");
	//rt::TH1Container hc_qcd  ("plots/qcd/qcd_pt35.root");
	//rt::TH1Container hc_ttbar("plots/ttbar/ttbar_pt35.root");
	//rt::TH1Container hc_dy   ("plots/dy/dy_pt35.root");
	//rt::TH1Container hc_wjets("plots/wjets/wjets_pt35.root");
	rt::TH1Container hc_el   ("../ss2012/data/fake_rates/ssFR_data_standard_23May2012.root");
	rt::TH1Container hc;

	std::map<std::string, rt::TH1Overlay> p;

    TH2F* h_mufr_ttbar = dynamic_cast<TH2F*>(hc_ttbar["h_mufr_dphi2p5_btag"]->Clone("h_mufr_ttbar"));
    TH2F* h_mufr_qcd   = dynamic_cast<TH2F*>(hc_qcd  ["h_mufr_dphi2p5_btag"]->Clone("h_mufr_qcd"  ));
    TH2F* h_mufr_data  = dynamic_cast<TH2F*>(hc_data ["h_mufr_dphi2p5_btag"]->Clone("h_mufr_data" ));
    TH2F* h_mufr_dy    = dynamic_cast<TH2F*>(hc_dy   ["h_mufr_dphi2p5_btag"]->Clone("h_mufr_dy"   ));
    TH2F* h_mufr_wjets = dynamic_cast<TH2F*>(hc_wjets["h_mufr_dphi2p5_btag"]->Clone("h_mufr_wjets"));

    TH2F* h_num = dynamic_cast<TH2F*>(hc_qcd["h_mu_num_dphi2p5_btag"]->Clone("h_mu_num_dphi2p5_btag"));
    h_num->Add(hc_dy   ["h_mu_num_dphi2p5_btag"]);
    h_num->Add(hc_wjets["h_mu_num_dphi2p5_btag"]);

    TH2F* h_den = dynamic_cast<TH2F*>(hc_qcd["h_mu_fo_dphi2p5_btag"]->Clone("h_mu_num_dphi2p5_btag"));
    h_den->Add(hc_dy   ["h_mu_fo_dphi2p5_btag"]);
    h_den->Add(hc_wjets["h_mu_fo_dphi2p5_btag"]);

    TH2* h_mc_mufr       = rt::MakeEfficiencyPlot2D(h_num, h_den, "h_mc_mufr");
    TH1* h_mc_mufr_vs_pt = rt::MakeEfficiencyProjectionPlot(h_num, h_den, "y", "h_mc_mufr_vs_pt");

    TH1* h_sf = ScaleFactorHist(h_mc_mufr_vs_pt, hc_data["h_mufr_dphi2p5_btag_vs_pt"], "h_musf40c_dphi2p5_btag_vs_pt", "data/MC scale factor (away jet > 40, #Delta#Phi > 2.5)");
    h_sf->Draw("texte");
    // create MC fakerate


	//hc.Add(ScaleFactorHist(hc_qcd["h_mufr_dphi2p5_btag_vs_pt"], hc_data["h_mufr_dphi2p5_btag_vs_pt"], "h_musf40c_dphi2p5_btag_vs_pt", "data/QCD scale factor (away jet > 40, #Delta#Phi > 2.5);p_{T}"  ));
    //hc.Add(dynamic_cast<TH1*>(hc_ttbar["h_mufr40c_vs_pt"]->Clone("h_mufr40c_ttbar_rescaled_vs_pt")));
    //hc["h_mufr40c_ttbar_rescaled_vs_pt"]->Multiply(hc["h_musf40c_dphi2p5_btag_vs_pt"]);

    //hc.Add(dynamic_cast<TH1*>(hc_ttbar["h_mufr40c"]->Clone("h_mufr40c_ttbar_rescaled")));
    //Rescale(hc["h_musf40c_dphi2p5_btag_vs_pt"], dynamic_cast<TH2*>(hc["h_mufr40c_ttbar_rescaled"]));

    //// keep the standard FR(pt, eta)
    //hc.Add(dynamic_cast<TH1*>(hc_data ["h_mufr40c"]->Clone("h_mufr40c_data" )));
    //hc.Add(dynamic_cast<TH1*>(hc_qcd  ["h_mufr40c"]->Clone("h_mufr40c_qcd"  )));
    //hc.Add(dynamic_cast<TH1*>(hc_ttbar["h_mufr40c"]->Clone("h_mufr40c_ttbar")));
    //hc.Add(dynamic_cast<TH1*>(hc_data ["h_mufr40c_vs_pt"]->Clone("h_mufr40c_data_pt" )));
    //hc.Add(dynamic_cast<TH1*>(hc_qcd  ["h_mufr40c_vs_pt"]->Clone("h_mufr40c_qcd_pt"  )));
    //hc.Add(dynamic_cast<TH1*>(hc_ttbar["h_mufr40c_vs_pt"]->Clone("h_mufr40c_ttbar_pt")));
    //hc.Add(hc_el["h_elfr40c"]);
    //hc.Add(hc_el["h_mufr40c"]);

    //// keep the new FR(pt)
    //hc.Add(dynamic_cast<TH1*>(hc_data ["h_mufr_dphi2p5_btag_vs_pt"]->Clone("h_mufr40c_dphi2p5_btag_data_vs_pt")));
    //hc.Add(dynamic_cast<TH1*>(hc_qcd  ["h_mufr_dphi2p5_btag_vs_pt"]->Clone("h_mufr40c_dphi2p5_btag_qcd_vs_pt" )));
    //hc.Add(dynamic_cast<TH1*>(hc_ttbar["h_mufr40c_vs_pt"          ]->Clone("h_mufr40c_ttbar_vs_pt"            )));
	//
    //// keep the new FR(eta, pt)
    //hc.Add(dynamic_cast<TH1*>(hc_data ["h_mufr_dphi2p5_btag"]->Clone("h_mufr40c_dphi2p5_btag_data")));
    //hc.Add(dynamic_cast<TH1*>(hc_qcd  ["h_mufr_dphi2p5_btag"]->Clone("h_mufr40c_dphi2p5_btag_qcd" )));
	
	// print
    hc.Write("plots/ttbar/ttbar_sf.root", "", "RECREATE");
}

TCut FromBHadron()
{
    TCut from_bhadron = ""
    "abs(mcmotherid) == 5       ||"
    "abs(mcmotherid) == 511     ||"
    "abs(mcmotherid) == 521     ||"
    "abs(mcmotherid) == 10511   ||"
    "abs(mcmotherid) == 10521   ||"
    "abs(mcmotherid) == 513     ||"
    "abs(mcmotherid) == 523     ||"
    "abs(mcmotherid) == 10513   ||"
    "abs(mcmotherid) == 10523   ||"
    "abs(mcmotherid) == 20513   ||"
    "abs(mcmotherid) == 20523   ||"
    "abs(mcmotherid) == 515     ||"
    "abs(mcmotherid) == 525     ||"
    "abs(mcmotherid) == 531     ||"
    "abs(mcmotherid) == 10531   ||"
    "abs(mcmotherid) == 533     ||"
    "abs(mcmotherid) == 10533   ||"
    "abs(mcmotherid) == 20533   ||"
    "abs(mcmotherid) == 535     ||"
    "abs(mcmotherid) == 541     ||"
    "abs(mcmotherid) == 10541   ||"
    "abs(mcmotherid) == 543     ||"
    "abs(mcmotherid) == 10543   ||"
    "abs(mcmotherid) == 20543   ||"
    "abs(mcmotherid) == 545     ||"
    "abs(mcmotherid) == 551     ||"
    "abs(mcmotherid) == 10551   ||"
    "abs(mcmotherid) == 100551  ||"
    "abs(mcmotherid) == 110551  ||"
    "abs(mcmotherid) == 200551  ||"
    "abs(mcmotherid) == 210551  ||"
    "abs(mcmotherid) == 553     ||"
    "abs(mcmotherid) == 10553   ||"
    "abs(mcmotherid) == 20553   ||"
    "abs(mcmotherid) == 30553   ||"
    "abs(mcmotherid) == 100553  ||"
    "abs(mcmotherid) == 110553  ||"
    "abs(mcmotherid) == 120553  ||"
    "abs(mcmotherid) == 130553  ||"
    "abs(mcmotherid) == 200553  ||"
    "abs(mcmotherid) == 210553  ||"
    "abs(mcmotherid) == 220553  ||"
    "abs(mcmotherid) == 300553  ||"
    "abs(mcmotherid) == 9000553 ||"
    "abs(mcmotherid) == 9010553 ||"
    "abs(mcmotherid) == 555     ||"
    "abs(mcmotherid) == 10555   ||"
    "abs(mcmotherid) == 20555   ||"
    "abs(mcmotherid) == 100555  ||"
    "abs(mcmotherid) == 110555  ||"
    "abs(mcmotherid) == 120555  ||"
    "abs(mcmotherid) == 200555  ||"
    "abs(mcmotherid) == 557     ||"
    "abs(mcmotherid) == 100557  ||"
    "abs(mcmotherid) == 5122    ||" 
    "abs(mcmotherid) == 5112    ||"
    "abs(mcmotherid) == 5212    ||"
    "abs(mcmotherid) == 5222    ||"
    "abs(mcmotherid) == 5114    ||"
    "abs(mcmotherid) == 5214    ||"
    "abs(mcmotherid) == 5224    ||"
    "abs(mcmotherid) == 5132    ||"
    "abs(mcmotherid) == 5232    ||"
    "abs(mcmotherid) == 5312    ||"
    "abs(mcmotherid) == 5322    ||"
    "abs(mcmotherid) == 5314    ||"
    "abs(mcmotherid) == 5324    ||"
    "abs(mcmotherid) == 5332    ||"
    "abs(mcmotherid) == 5334    ||"
    "abs(mcmotherid) == 5142    ||"
    "abs(mcmotherid) == 5242    ||"
    "abs(mcmotherid) == 5412    ||"
    "abs(mcmotherid) == 5422    ||"
    "abs(mcmotherid) == 5414    ||"
    "abs(mcmotherid) == 5424    ||"
    "abs(mcmotherid) == 5342    ||"
    "abs(mcmotherid) == 5432    ||"
    "abs(mcmotherid) == 5434    ||"
    "abs(mcmotherid) == 5442    ||"
    "abs(mcmotherid) == 5444    ||"
    "abs(mcmotherid) == 5512    ||"
    "abs(mcmotherid) == 5522    ||"
    "abs(mcmotherid) == 5514    ||"
    "abs(mcmotherid) == 5524    ||"
    "abs(mcmotherid) == 5532    ||"
    "abs(mcmotherid) == 5534    ||"
    "abs(mcmotherid) == 5542    ||"
    "abs(mcmotherid) == 5544    ||"
    "abs(mcmotherid) == 5554";

    return from_bhadron;
}

TCut FromCHadron()
{
    TCut from_chadron = ""
    "abs(mcmotherid) == 4       ||"
    "abs(mcmotherid) == 411     ||"
    "abs(mcmotherid) == 421     ||"
    "abs(mcmotherid) == 10411   ||"
    "abs(mcmotherid) == 10421   ||"
    "abs(mcmotherid) == 413     ||"
    "abs(mcmotherid) == 423     ||"
    "abs(mcmotherid) == 10413   ||"
    "abs(mcmotherid) == 10423   ||"
    "abs(mcmotherid) == 20413   ||"
    "abs(mcmotherid) == 20423   ||"
    "abs(mcmotherid) == 415     ||"
    "abs(mcmotherid) == 425     ||"
    "abs(mcmotherid) == 431     ||"
    "abs(mcmotherid) == 10431   ||"
    "abs(mcmotherid) == 433     ||"
    "abs(mcmotherid) == 10433   ||"
    "abs(mcmotherid) == 20433   ||"
    "abs(mcmotherid) == 435     ||"
    "abs(mcmotherid) == 441     ||"
    "abs(mcmotherid) == 10441   ||"
    "abs(mcmotherid) == 100441  ||"
    "abs(mcmotherid) == 443     ||"
    "abs(mcmotherid) == 10443   ||"
    "abs(mcmotherid) == 20443   ||"
    "abs(mcmotherid) == 100443  ||"
    "abs(mcmotherid) == 30443   ||"
    "abs(mcmotherid) == 9000443 ||"
    "abs(mcmotherid) == 9010443 ||"
    "abs(mcmotherid) == 9020443 ||"
    "abs(mcmotherid) == 445     ||"
    "abs(mcmotherid) == 9000445 ||"
    "abs(mcmotherid) == 4122    ||"
    "abs(mcmotherid) == 4222    ||"
    "abs(mcmotherid) == 4212    ||"
    "abs(mcmotherid) == 4112    ||"
    "abs(mcmotherid) == 4224    ||"
    "abs(mcmotherid) == 4214    ||"
    "abs(mcmotherid) == 4114    ||"
    "abs(mcmotherid) == 4232    ||"
    "abs(mcmotherid) == 4132    ||"
    "abs(mcmotherid) == 4322    ||"
    "abs(mcmotherid) == 4312    ||"
    "abs(mcmotherid) == 4324    ||"
    "abs(mcmotherid) == 4314    ||"
    "abs(mcmotherid) == 4332    ||"
    "abs(mcmotherid) == 4334    ||"
    "abs(mcmotherid) == 4412    ||"
    "abs(mcmotherid) == 4422    ||"
    "abs(mcmotherid) == 4414    ||"
    "abs(mcmotherid) == 4424    ||"
    "abs(mcmotherid) == 4432    ||"
    "abs(mcmotherid) == 4434    ||"
    "abs(mcmotherid) == 4444";

    return from_chadron;
}

void TestFakeRate(const std::string sample = "ttbar", long num_entries = 100000000000)
{
    // cuts
    TCut pt_cut           = "(pt>5 && pt<35) && abs(eta)<2.4";
    TCut vtx_cut          = "evt_nvtxs>=3 && evt_nvtxs<=8";
    TCut w_cut            = "pfmet<20 && pfmt<25";
    TCut z_cut            = "(mz_fo_ctf<76.0 || mz_fo_ctf>106.0) && (mupsilon_fo_mu<8.0 || mupsilon_fo_mu>12.0)";
    TCut nFOmus           = "nFOmus==0";
    TCut den_base         = TCut("fo_mussV4_noIso && abs(id)==13 && nt_iso < 0.4") && pt_cut && w_cut && z_cut;
    TCut den_base_noiso   = TCut("fo_mussV4_noIso && abs(id)==13"                ) && pt_cut && w_cut && z_cut;
    TCut num_base         = TCut("fo_mussV4_noIso && abs(id)==13 && nt_iso < 0.1") && pt_cut && w_cut && z_cut;
    TCut num_base_noiso   = TCut("fo_mussV4_noIso && abs(id)==13"                ) && pt_cut && w_cut && z_cut;
    TCut lep_not_from_W   = "leptonIsFromW < 1";
    TCut mc3_matched      = TCut("abs(mc3id)!=999");
    TCut mc3_direct_b     = TCut("abs(mc3id)==5 && abs(mcid)==13" ) && FromBHadron();
    TCut mc3_direct_c     = TCut("abs(mc3id)==4 && abs(mcid)==13" ) && FromCHadron();
    TCut mc3_g_bb_mu      = TCut("abs(mc3id)==21 && abs(mcid)==13") && FromBHadron();
    TCut mc3_b_c_mu       = TCut("abs(mc3id)==21 && abs(mcid)==13") && FromCHadron();
    TCut mc3_mis_id       = TCut("abs(mcid)!=13") && mc3_matched;
    TCut mc3_K_mu         = TCut("abs(mcid)==13 && ((300 < abs(mcmotherid) && abs(mcmotherid)< 400) || (3000 < abs(mcmotherid) && abs(mcmotherid)< 4000))");
    TCut mc3_Ktrue_mu     = TCut("abs(mcid)==13 && abs(mcmotherid)==321");
    TCut fo_bin           = "pt>=20.0 && pt<=25.0";
    TCut weight           = "weight";
    TCut passes_num       = num_base       && lep_not_from_W && nFOmus;
    TCut passes_den       = den_base       && lep_not_from_W && nFOmus;
    TCut passes_num_noiso = num_base_noiso && lep_not_from_W && nFOmus;
    TCut passes_den_noiso = den_base_noiso && lep_not_from_W && nFOmus;
    TCut mu_pt_1          = "pt < 11.0";
    TCut mu_pt_2          = "pt >= 11.0 && pt < 16.0";
    TCut mu_pt_3          = "pt >= 16.0";

    // chain and event list
    TChain e1("tree");
    TChain e2("tree");
    TChain e3("tree");
    if (sample == "ttbar")
    {
        e1.Add("/Users/rwk7t/Data/fr2/TTJets_TuneZ2_7TeV-madgraph-tauola_Fall11-PU_S6_START42_V14B-v2_frbaby/merged_output_files/merged_frbaby*.root");
        e1.Draw(">>evt_list", passes_den, "goff", num_entries); 
        TEventList* list = dynamic_cast<TEventList*>(gDirectory->Get("evt_list")); 
        e1.SetEventList(list);
    }
    else
    {
        e1.Add("/Users/rwk7t/Data/fr2//QCD_Pt-15to20_MuPt5Enriched_TuneZ2_7TeV-pythia6_Summer11-PU_S3_START42_V11-v2_frbaby/merged_output_files/*.root");
        e1.Add("/Users/rwk7t/Data/fr2//QCD_Pt-20to30_MuPt5Enriched_TuneZ2_7TeV-pythia6_Summer11-PU_S3_START42_V11-v2_frbaby/merged_output_files/*.root");
        e1.Add("/Users/rwk7t/Data/fr2//QCD_Pt-30to50_MuPt5Enriched_TuneZ2_7TeV-pythia6_Summer11-PU_S3_START42_V11-v2_frbaby/merged_output_files/*.root");
        e1.Add("/Users/rwk7t/Data/fr2//QCD_Pt-50to80_MuPt5Enriched_TuneZ2_7TeV-pythia6_Summer11-PU_S4_START42_V11-v1_frbaby/merged_output_files/*.root");
        e1.Add("/Users/rwk7t/Data/fr2/QCD_Pt-80to120_MuPt5Enriched_TuneZ2_7TeV-pythia6_Summer11-PU_S4_START42_V11-v1_frbaby/merged_output_files/*.root");
        e2.Add("/Users/rwk7t/Data/fr2/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6_Summer11-PU_S3_START42_V11-v2_frbaby/merged_output_files/*.root"   );
        e3.Add("/Users/rwk7t/Data/fr2/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6_Summer11-PU_S4_START42_V11-v1_frbaby/merged_output_files/*.root"   );    

        e1.Draw(">>evt_list1", passes_den && mu_pt_1, "goff", num_entries); 
        TEventList* list1 = dynamic_cast<TEventList*>(gDirectory->Get("evt_list1")); 
        e1.SetEventList(list1);

        e2.Draw(">>evt_list2", passes_den && mu_pt_2, "goff", num_entries); 
        TEventList* list2 = dynamic_cast<TEventList*>(gDirectory->Get("evt_list2")); 
        e2.SetEventList(list2);

        e3.Draw(">>evt_list3", passes_den && mu_pt_3, "goff", num_entries); 
        TEventList* list3 = dynamic_cast<TEventList*>(gDirectory->Get("evt_list3")); 
        e3.SetEventList(list3);
    }
    rt::PrintFilesFromTChain(e1);
    rt::PrintFilesFromTChain(e2);
    rt::PrintFilesFromTChain(e3);


    // book
    //rt::TH1Container hc;
    //TH1F* h_mc3id = new TH1F("h_mc3id", "mc3 id", 30, -0.5, 29.5);
    //TH1F* h_momid = new TH1F("h_momid", "mom id", 6000, -0.5, 5999.5);

    // draw
    //hc.SetDirectory(gDirectory);
    //e1.Draw("abs(mcmotherid)>>h_momid", passes_den               , "goff", num_entries);
    //e1.Draw("abs(mc3id)>>h_mc3id"     , passes_den && mc3_matched, "goff", num_entries);
    ////hc.SetDirectory(NULL);
    ////hc.Add((TH1F*)gDirectory->Get("h_mc3id"));
    //h_mc3id->Draw();
    //h_momid->Draw();

    //TH2F* h_num    = new TH2F("h_num"   , "#mu numerator;|#eta|;p_{T} (GeV)"  , 10, 0, 2.5, 10, 5, 55);
    //TH2F* h_den    = new TH2F("h_den"   , "#mu denominator;|#eta|;p_{T} (GeV)", 10, 0, 2.5, 10, 5, 55);
    //e1.Draw("pt:abs(eta)>>h_num" , passes_num, "goff", num_entries);
    //e1.Draw("pt:abs(eta)>>h_den" , passes_den, "goff", num_entries);
    //e2.Draw("pt:abs(eta)>>+h_num", passes_num, "goff", num_entries);
    //e2.Draw("pt:abs(eta)>>+h_den", passes_den, "goff", num_entries);
    //e3.Draw("pt:abs(eta)>>+h_num", passes_num, "goff", num_entries);
    //e3.Draw("pt:abs(eta)>>+h_den", passes_den, "goff", num_entries);

    // fake rate 
    //TH1* h_mufr = rt::MakeEfficiencyProjectionPlot(h_num, h_den, "Y", "h_mufr");
    //h_mufr->Draw();
    

    float num_count          = e1.GetEntries(passes_num                ) + e2.GetEntries(passes_num                ) + e3.GetEntries(passes_num                );
    float num_count_matched  = e1.GetEntries(passes_num && mc3_matched ) + e2.GetEntries(passes_num && mc3_matched ) + e3.GetEntries(passes_num && mc3_matched );
    float num_count_direct_b = e1.GetEntries(passes_num && mc3_direct_b) + e2.GetEntries(passes_num && mc3_direct_b) + e3.GetEntries(passes_num && mc3_direct_b);
    float num_count_direct_c = e1.GetEntries(passes_num && mc3_direct_c) + e2.GetEntries(passes_num && mc3_direct_c) + e3.GetEntries(passes_num && mc3_direct_c);
    float num_count_g_bb_mu  = e1.GetEntries(passes_num && mc3_g_bb_mu ) + e2.GetEntries(passes_num && mc3_g_bb_mu ) + e3.GetEntries(passes_num && mc3_g_bb_mu );
    float num_count_b_c_mu   = e1.GetEntries(passes_num && mc3_b_c_mu  ) + e2.GetEntries(passes_num && mc3_b_c_mu  ) + e3.GetEntries(passes_num && mc3_b_c_mu  );
    float num_count_mis_id   = e1.GetEntries(passes_num && mc3_mis_id  ) + e2.GetEntries(passes_num && mc3_mis_id  ) + e3.GetEntries(passes_num && mc3_mis_id  );
    float num_count_K_mu     = e1.GetEntries(passes_num && mc3_K_mu    ) + e2.GetEntries(passes_num && mc3_K_mu    ) + e3.GetEntries(passes_num && mc3_K_mu    );
    float num_count_Ktrue_mu = e1.GetEntries(passes_num && mc3_Ktrue_mu) + e2.GetEntries(passes_num && mc3_Ktrue_mu) + e3.GetEntries(passes_num && mc3_Ktrue_mu);

    float ratio_num_count          = num_count            / num_count;
    float ratio_num_count_matched  = num_count_matched    / num_count;
    float ratio_num_count_direct_b = num_count_direct_b   / num_count_matched;
    float ratio_num_count_direct_c = num_count_direct_c   / num_count_matched;
    float ratio_num_count_g_bb_mu  = num_count_g_bb_mu    / num_count_matched;
    float ratio_num_count_b_c_mu   = num_count_b_c_mu     / num_count_matched;
    float ratio_num_count_mis_id   = num_count_mis_id     / num_count_matched;
    float ratio_num_count_K_mu     = num_count_K_mu       / num_count_matched;
    float ratio_num_count_Ktrue_mu = num_count_Ktrue_mu   / num_count_matched;


    CTable t1;
    t1.useTitle();
    t1.setTitle("num breakdown");
    t1.setTable() ("num"              ,                                            "percent")
                  ("total"            , num_count          , 100.0*ratio_num_count          ) 
                  ("total mc3 matched", num_count_matched  , 100.0*ratio_num_count_matched  ) 
                  ("direct b"         , num_count_direct_b , 100.0*ratio_num_count_direct_b ) 
                  ("direct c"         , num_count_direct_c , 100.0*ratio_num_count_direct_c ) 
                  ("g --> bb (b-->mu)", num_count_g_bb_mu  , 100.0*ratio_num_count_g_bb_mu  ) 
                  ("b --> c --> mu"   , num_count_b_c_mu   , 100.0*ratio_num_count_b_c_mu   ) 
                  ("mis id"           , num_count_mis_id   , 100.0*ratio_num_count_mis_id   )
                  ("K hadron --> mu"  , num_count_K_mu     , 100.0*ratio_num_count_K_mu     )
                  ("K --> mu"         , num_count_Ktrue_mu , 100.0*ratio_num_count_Ktrue_mu );
    t1.print();

    float den_count          = e1.GetEntries(passes_den                ) + e2.GetEntries(passes_den                ) + e3.GetEntries(passes_den                );
    float den_count_matched  = e1.GetEntries(passes_den && mc3_matched ) + e2.GetEntries(passes_den && mc3_matched ) + e3.GetEntries(passes_den && mc3_matched );
    float den_count_direct_b = e1.GetEntries(passes_den && mc3_direct_b) + e2.GetEntries(passes_den && mc3_direct_b) + e3.GetEntries(passes_den && mc3_direct_b);
    float den_count_direct_c = e1.GetEntries(passes_den && mc3_direct_c) + e2.GetEntries(passes_den && mc3_direct_c) + e3.GetEntries(passes_den && mc3_direct_c);
    float den_count_g_bb_mu  = e1.GetEntries(passes_den && mc3_g_bb_mu ) + e2.GetEntries(passes_den && mc3_g_bb_mu ) + e3.GetEntries(passes_den && mc3_g_bb_mu );
    float den_count_b_c_mu   = e1.GetEntries(passes_den && mc3_b_c_mu  ) + e2.GetEntries(passes_den && mc3_b_c_mu  ) + e3.GetEntries(passes_den && mc3_b_c_mu  );
    float den_count_mis_id   = e1.GetEntries(passes_den && mc3_mis_id  ) + e2.GetEntries(passes_den && mc3_mis_id  ) + e3.GetEntries(passes_den && mc3_mis_id  );
    float den_count_K_mu     = e1.GetEntries(passes_den && mc3_K_mu    ) + e2.GetEntries(passes_den && mc3_K_mu    ) + e3.GetEntries(passes_den && mc3_K_mu    );
    float den_count_Ktrue_mu = e1.GetEntries(passes_den && mc3_Ktrue_mu) + e2.GetEntries(passes_den && mc3_Ktrue_mu) + e3.GetEntries(passes_den && mc3_Ktrue_mu);

    float ratio_den_count          = den_count            / den_count;
    float ratio_den_count_matched  = den_count_matched    / den_count;
    float ratio_den_count_direct_b = den_count_direct_b   / den_count_matched;
    float ratio_den_count_direct_c = den_count_direct_c   / den_count_matched;
    float ratio_den_count_g_bb_mu  = den_count_g_bb_mu    / den_count_matched;
    float ratio_den_count_b_c_mu   = den_count_b_c_mu     / den_count_matched;
    float ratio_den_count_mis_id   = den_count_mis_id     / den_count_matched;
    float ratio_den_count_K_mu     = den_count_K_mu       / den_count_matched;
    float ratio_den_count_Ktrue_mu = den_count_Ktrue_mu   / den_count_matched;

    CTable t2;
    t2.useTitle();
    t2.setTitle("den breakdown");
    t2.setTable() ("den"              ,                                            "percent")
                  ("total"            , den_count          , 100.0*ratio_den_count          ) 
                  ("total mc3 matched", den_count_matched  , 100.0*ratio_den_count_matched  ) 
                  ("direct b"         , den_count_direct_b , 100.0*ratio_den_count_direct_b ) 
                  ("direct c"         , den_count_direct_c , 100.0*ratio_den_count_direct_c ) 
                  ("g --> bb (b-->mu)", den_count_g_bb_mu  , 100.0*ratio_den_count_g_bb_mu  ) 
                  ("b --> c --> mu"   , den_count_b_c_mu   , 100.0*ratio_den_count_b_c_mu   ) 
                  ("mis id"           , den_count_mis_id   , 100.0*ratio_den_count_mis_id   )
                  ("K hadron --> mu"  , den_count_K_mu     , 100.0*ratio_den_count_K_mu     )
                  ("K --> mu"         , den_count_Ktrue_mu , 100.0*ratio_den_count_Ktrue_mu );
    t2.print();

    // draw the hists
    //TCanvas* c1 = new TCanvas("c1", "c1", 1000, 500); 
    //c1->Divide(2,1); 
    //c1->cd(1); h_mc3id->Draw();
    //c1->cd(2); h_reliso->Draw();
    // set event list
    //e1.Draw(">>evt_list", passes_den_noiso, "goff", num_entries);
    //TEventList* list = dynamic_cast<TEventList*>(gDirectory->Get("evt_list"));
    //e1->SetEventList(list);

    // book
    //rt::TH1Container hc;
    //hc.Add(new TH1F("h_reliso_mc3_25_35_ttbar", "Rel Iso;reliso", 40, 0.0, 2.0));
    //hc.Add(new TH1F("h_reliso_mc3_35_45_ttbar", "Rel Iso;reliso", 40, 0.0, 2.0));

    //// draw
    //e1->Draw("min(nt_iso, 1.99)>>h_reliso_mc3_25_35_ttbar" , fo_bin + "(mc3pt>25 && mc3pt<35)", "goff", num_entries);
    //e1->Draw("min(nt_iso, 1.99)>>h_reliso_mc3_35_45_ttbar" , fo_bin + "(mc3pt>35 && mc3pt<45)", "goff", num_entries);

    //// ouput
    //rt::TH1Overlay* p2 = new rt::TH1Overlay("Relative Isolation (14 < FO p_{T} < 16);reliso", "dt::norm");
    //p2->Add(hc["h_reliso_mc3_25_35_ttbar"], "25 < p_{T}(b) < 35", kBlue, 2);
    //p2->Add(hc["h_reliso_mc3_35_45_ttbar"], "35 < p_{T}(b) < 45", kRed , 2);
    //TCanvas* c1 = dynamic_cast<TCanvas*>(gPad);
    //c1->Print("plots/FakeRateMaker/04042012/p_reliso_25_45_ttbar.eps");


    //TH1F* h_reliso = new TH1F("h_reliso", "#mu isolation;reliso"              , 20, 0,   2);
    //TH1F* h_mc3id  = new TH1F("h_mc3id" , "FO matched mc3 id; |id|"           , 32, -0.5, 31.5);


    //e1.Draw("nt_iso>>h_reliso", fo_bin, "goff", num_entries);
    //e1.Draw("mc3id>>h_mc3id"  , den_base && lep_not_from_W, "goff", num_entries);
    
    //cout << (den_base && lep_not_from_W) << endl;

    // reliso 
    //pair<double, double> ttbar_pair = IntegralRatioWithUncertainty(h_reliso, 0.1, 0.4);
    //double ttbar     = ttbar_pair.first;
    //double ttbar_err = ttbar_pair.second; 

}

void IsoPlotTTbar(long num_entries = 100000000000)
{
    // cuts
    TCut pt_cut         = "pt>20 && abs(eta)<2.4";
    //TCut muid_7tev      = "abs(id)==13 && num_mussV4_noIso";
    TCut muid_7tev      = "abs(id)==13 && numNomSSv4noIso";
    TCut elid_7tev      = "abs(id)==11 && num_el_ssV6_noIso";
    TCut muid_8tev      = "abs(id)==13 && num_mu_ssV5_noIso";
    TCut elid_8tev      = "abs(id)==11 && num_el_ssV7_noIso";
    TCut lep_from_W     = "leptonIsFromW == 1";
    TCut lep_not_from_W = "leptonIsFromW < 1";
    TCut el_matched     = "abs(mcid)==11";

    // chain and event list
    TChain e1("tree"); // 7TeV
    e1.Add("/Users/rwk7t/Data/fr2/TTJets_TuneZ2_7TeV-madgraph-tauola_Fall11-PU_S6_START42_V14B-v2_frbaby/merged_output_files/merged_frbaby*.root");

    TChain e2("tree"); // 8TeV
    e2.Add("/Users/rwk7t/Data/babies/fr/FakeRate20May2012_mc/TTJets_TuneZ2star_8TeV-madgraph-tauola_Summer12-PU_S7_START52_V9-v1/*.root");

    // muons (set event list)
    e1.Draw(">>evt_mu_list1", muid_7tev && pt_cut, "goff", num_entries); 
    TEventList* evt_mu_list1 = dynamic_cast<TEventList*>(gDirectory->Get("evt_mu_list1")); 

    e2.Draw(">>evt_mu_list2", muid_8tev && pt_cut, "goff", num_entries); 
    TEventList* evt_mu_list2 = dynamic_cast<TEventList*>(gDirectory->Get("evt_mu_list2")); 

    // electrons (set event list)
    e1.Draw(">>evt_el_list1", elid_7tev && pt_cut, "goff", num_entries); 
    TEventList* evt_el_list1 = dynamic_cast<TEventList*>(gDirectory->Get("evt_el_list1")); 

    e2.Draw(">>evt_el_list2", elid_8tev && pt_cut, "goff", num_entries); 
    TEventList* evt_el_list2 = dynamic_cast<TEventList*>(gDirectory->Get("evt_el_list2")); 

    // book hists
    rt::TH1Container hc;
    hc.Add(new TH1F("h_el_fake_diso_7tev"  , "electron det isolation (7 TeV);relative det Iso" , 100, 0, 0.6));
    hc.Add(new TH1F("h_el_fake_diso_8tev"  , "electron det isolation (8 TeV);relative det Iso" , 100, 0, 0.6));
    hc.Add(new TH1F("h_el_fake_pfiso_8tev" , "electron pf isolation (8 TeV);relative pf Iso"   , 100, 0, 0.6));
    hc.Add(new TH1F("h_el_fake_cpfiso_8tev", "electron cpf isolation (8 TeV);relative cpf Iso" , 100, 0, 0.6));
    hc.Add(new TH1F("h_el_real_diso_7tev"  , "electron det isolation (7 TeV);relative det Iso" , 100, 0, 0.6));
    hc.Add(new TH1F("h_el_real_pfiso_8tev" , "electron pf isolation (8 TeV);relative pf Iso"   , 100, 0, 0.6));
    hc.Add(new TH1F("h_el_real_diso_8tev"  , "electron det isolation (8 TeV);relative det Iso" , 100, 0, 0.6));
    hc.Add(new TH1F("h_el_real_cpfiso_8tev", "electron cpf isolation (8 TeV);relative cpf Iso" , 100, 0, 0.6));

    hc.Add(new TH1F("h_mu_fake_diso_7tev"  , "muon det isolation (7 TeV);relative det Iso" , 100, 0, 1.0));
    hc.Add(new TH1F("h_mu_fake_diso_8tev"  , "muon det isolation (8 TeV);relative det Iso" , 100, 0, 1.0));
    hc.Add(new TH1F("h_mu_fake_pfiso_8tev" , "muon pf isolation (8 TeV);relative pf Iso"   , 100, 0, 1.0));
    hc.Add(new TH1F("h_mu_fake_cpfiso_8tev", "muon cpf isolation (8 TeV);relative cpf Iso" , 100, 0, 1.0));
    hc.Add(new TH1F("h_mu_real_diso_7tev"  , "muon det isolation (7 TeV);relative det Iso" , 100, 0, 1.0));
    hc.Add(new TH1F("h_mu_real_pfiso_8tev" , "muon pf isolation (8 TeV);relative pf Iso"   , 100, 0, 1.0));
    hc.Add(new TH1F("h_mu_real_diso_8tev"  , "muon det isolation (8 TeV);relative det Iso" , 100, 0, 1.0));
    hc.Add(new TH1F("h_mu_real_cpfiso_8tev", "muon cpf isolation (8 TeV);relative cpf Iso" , 100, 0, 1.0));

    hc.Add(new TH1F("h_el_fake_diso_7tev_zoom"  , "electron det isolation (7 TeV);relative det Iso" , 10, 0, 0.1));
    hc.Add(new TH1F("h_el_fake_diso_8tev_zoom"  , "electron det isolation (8 TeV);relative det Iso" , 10, 0, 0.1));
    hc.Add(new TH1F("h_el_fake_pfiso_8tev_zoom" , "electron pf isolation (8 TeV);relative pf Iso"   , 10, 0, 0.1));
    hc.Add(new TH1F("h_el_fake_cpfiso_8tev_zoom", "electron cpf isolation (8 TeV);relative cpf Iso" , 10, 0, 0.1));
    hc.Add(new TH1F("h_el_real_diso_7tev_zoom"  , "electron det isolation (7 TeV);relative det Iso" , 10, 0, 0.1));
    hc.Add(new TH1F("h_el_real_pfiso_8tev_zoom" , "electron pf isolation (8 TeV);relative pf Iso"   , 10, 0, 0.1));
    hc.Add(new TH1F("h_el_real_diso_8tev_zoom"  , "electron det isolation (8 TeV);relative det Iso" , 10, 0, 0.1));
    hc.Add(new TH1F("h_el_real_cpfiso_8tev_zoom", "electron cpf isolation (8 TeV);relative cpf Iso" , 10, 0, 0.1));

    hc.Add(new TH1F("h_mu_fake_diso_7tev_zoom"  , "muon det isolation (7 TeV);relative det Iso" , 10, 0, 0.1));
    hc.Add(new TH1F("h_mu_fake_diso_8tev_zoom"  , "muon det isolation (8 TeV);relative det Iso" , 10, 0, 0.1));
    hc.Add(new TH1F("h_mu_fake_pfiso_8tev_zoom" , "muon pf isolation (8 TeV);relative pf Iso"   , 10, 0, 0.1));
    hc.Add(new TH1F("h_mu_fake_cpfiso_8tev_zoom", "muon cpf isolation (8 TeV);relative cpf Iso" , 10, 0, 0.1));
    hc.Add(new TH1F("h_mu_real_diso_7tev_zoom"  , "muon det isolation (7 TeV);relative det Iso" , 10, 0, 0.1));
    hc.Add(new TH1F("h_mu_real_pfiso_8tev_zoom" , "muon pf isolation (8 TeV);relative pf Iso"   , 10, 0, 0.1));
    hc.Add(new TH1F("h_mu_real_diso_8tev_zoom"  , "muon det isolation (8 TeV);relative det Iso" , 10, 0, 0.1));
    hc.Add(new TH1F("h_mu_real_cpfiso_8tev_zoom", "muon cpf isolation (8 TeV);relative cpf Iso" , 10, 0, 0.1));

    hc.Add(new TH1F("h_mu_real_ch_pfiso_8tev", "muon charged hadron pf isolation (8 TeV);relative cpf Iso" , 100, 0, 1.0));
    hc.Add(new TH1F("h_mu_real_nh_pfiso_8tev", "muon neugral hadron pf isolation (8 TeV);relative cpf Iso" , 100, 0, 1.0));
    hc.Add(new TH1F("h_mu_real_em_pfiso_8tev", "muon EM pf isolation (8 TeV);relative cpf Iso"             , 100, 0, 1.0));
    hc.Add(new TH1F("h_mu_fake_ch_pfiso_8tev", "muon charged hadron pf isolation (8 TeV);relative cpf Iso" , 100, 0, 1.0));
    hc.Add(new TH1F("h_mu_fake_nh_pfiso_8tev", "muon neutral hadron pf isolation (8 TeV);relative cpf Iso" , 100, 0, 1.0));
    hc.Add(new TH1F("h_mu_fake_em_pfiso_8tev", "muon EM pf isolation (8 TeV);relative cpf Iso"             , 100, 0, 1.0));
    hc.Add(new TH1F("h_mu_fake_nu_pfiso_8tev", "muon neutral isolation (8 TeV);relative cpf Iso"           , 100, 0, 1.0));
    hc.Add(new TH1F("h_mu_fake_trk_iso_8tev" , "muon track isolation (8 TeV);relative trk Iso"             , 100, 0, 1.0));
    hc.Add(new TH1F("h_mu_fake_trk_iso_7tev" , "muon track isolation (7 TeV);relative trk Iso"             , 100, 0, 1.0));

    hc.Add(new TH1F("h_el_real_ch_pfiso_8tev", "electron charged hadron pf isolation (8 TeV);relative cpf Iso" , 100, 0, 0.6));
    hc.Add(new TH1F("h_el_real_nh_pfiso_8tev", "electron neugral hadron pf isolation (8 TeV);relative cpf Iso" , 100, 0, 0.6));
    hc.Add(new TH1F("h_el_real_em_pfiso_8tev", "electron EM pf isolation (8 TeV);relative cpf Iso"             , 100, 0, 0.6));
    hc.Add(new TH1F("h_el_fake_ch_pfiso_8tev", "electron charged hadron pf isolation (8 TeV);relative cpf Iso" , 100, 0, 0.6));
    hc.Add(new TH1F("h_el_fake_nh_pfiso_8tev", "electron neutral hadron pf isolation (8 TeV);relative cpf Iso" , 100, 0, 0.6));
    hc.Add(new TH1F("h_el_fake_em_pfiso_8tev", "electron EM pf isolation (8 TeV);relative cpf Iso"             , 100, 0, 0.6));
    hc.Add(new TH1F("h_el_fake_nu_pfiso_8tev", "electron neutral isolation (8 TeV);relative cpf Iso"           , 100, 0, 0.6));
    hc.Add(new TH1F("h_el_fake_trk_iso_8tev" , "electron track isolation (8 TeV);relative trk Iso"             , 100, 0, 0.6));
    hc.Add(new TH1F("h_el_fake_trk_iso_7tev" , "electron track isolation (7 TeV);relative trk Iso"             , 100, 0, 0.6));

    // draw
    hc.SetDirectory(gDirectory);
    e1.SetEventList(evt_el_list1); e1.Draw("nt_iso      >>h_el_fake_diso_7tev"  , lep_not_from_W, "goff", num_entries);
    e2.SetEventList(evt_el_list2); e2.Draw("pfiso03     >>h_el_fake_pfiso_8tev" , lep_not_from_W, "goff", num_entries);
    e2.SetEventList(evt_el_list2); e2.Draw("cpfiso03_rho>>h_el_fake_cpfiso_8tev", lep_not_from_W, "goff", num_entries);
    e2.SetEventList(evt_el_list2); e2.Draw("iso         >>h_el_fake_diso_8tev"  , lep_not_from_W, "goff", num_entries);
    e1.SetEventList(evt_el_list1); e1.Draw("nt_iso      >>h_el_real_diso_7tev"  , lep_from_W    , "goff", num_entries);
    e2.SetEventList(evt_el_list2); e2.Draw("pfiso03     >>h_el_real_pfiso_8tev" , lep_from_W    , "goff", num_entries);
    e2.SetEventList(evt_el_list2); e2.Draw("cpfiso03_rho>>h_el_real_cpfiso_8tev", lep_from_W    , "goff", num_entries);
    e2.SetEventList(evt_el_list2); e2.Draw("iso         >>h_el_real_diso_8tev"  , lep_from_W    , "goff", num_entries);

    e1.SetEventList(evt_mu_list1); e1.Draw("nt_iso     >>h_mu_fake_diso_7tev"  , lep_not_from_W, "goff", num_entries);
    e2.SetEventList(evt_mu_list2); e2.Draw("pfiso03    >>h_mu_fake_pfiso_8tev" , lep_not_from_W, "goff", num_entries);
    e2.SetEventList(evt_mu_list2); e2.Draw("cpfiso03_db>>h_mu_fake_cpfiso_8tev", lep_not_from_W, "goff", num_entries);
    e2.SetEventList(evt_mu_list2); e2.Draw("iso        >>h_mu_fake_diso_8tev"  , lep_not_from_W, "goff", num_entries);
    e1.SetEventList(evt_mu_list1); e1.Draw("nt_iso     >>h_mu_real_diso_7tev"  , lep_from_W    , "goff", num_entries);
    e2.SetEventList(evt_mu_list2); e2.Draw("pfiso03    >>h_mu_real_pfiso_8tev" , lep_from_W    , "goff", num_entries);
    e2.SetEventList(evt_mu_list2); e2.Draw("cpfiso03_db>>h_mu_real_cpfiso_8tev", lep_from_W    , "goff", num_entries);

    e2.SetEventList(evt_mu_list2); e2.Draw("iso        >>h_mu_real_diso_8tev_zoom"   , lep_from_W    , "goff", num_entries);
    e1.SetEventList(evt_el_list1); e1.Draw("nt_iso      >>h_el_fake_diso_7tev_zoom"  , lep_not_from_W, "goff", num_entries);
    e2.SetEventList(evt_el_list2); e2.Draw("pfiso03     >>h_el_fake_pfiso_8tev_zoom" , lep_not_from_W, "goff", num_entries);
    e2.SetEventList(evt_el_list2); e2.Draw("cpfiso03_rho>>h_el_fake_cpfiso_8tev_zoom", lep_not_from_W, "goff", num_entries);
    e2.SetEventList(evt_el_list2); e2.Draw("iso         >>h_el_fake_diso_8tev_zoom"  , lep_not_from_W, "goff", num_entries);
    e1.SetEventList(evt_el_list1); e1.Draw("nt_iso      >>h_el_real_diso_7tev_zoom"  , lep_from_W    , "goff", num_entries);
    e2.SetEventList(evt_el_list2); e2.Draw("pfiso03     >>h_el_real_pfiso_8tev_zoom" , lep_from_W    , "goff", num_entries);
    e2.SetEventList(evt_el_list2); e2.Draw("cpfiso03_rho>>h_el_real_cpfiso_8tev_zoom", lep_from_W    , "goff", num_entries);
    e2.SetEventList(evt_el_list2); e2.Draw("iso         >>h_el_real_diso_8tev_zoom"  , lep_from_W    , "goff", num_entries);

    e1.SetEventList(evt_mu_list1); e1.Draw("nt_iso     >>h_mu_fake_diso_7tev_zoom"  , lep_not_from_W, "goff", num_entries);
    e2.SetEventList(evt_mu_list2); e2.Draw("pfiso03    >>h_mu_fake_pfiso_8tev_zoom" , lep_not_from_W, "goff", num_entries);
    e2.SetEventList(evt_mu_list2); e2.Draw("cpfiso03_db>>h_mu_fake_cpfiso_8tev_zoom", lep_not_from_W, "goff", num_entries);
    e2.SetEventList(evt_mu_list2); e2.Draw("iso        >>h_mu_fake_diso_8tev_zoom"  , lep_not_from_W, "goff", num_entries);
    e1.SetEventList(evt_mu_list1); e1.Draw("nt_iso     >>h_mu_real_diso_7tev_zoom"  , lep_from_W    , "goff", num_entries);
    e2.SetEventList(evt_mu_list2); e2.Draw("pfiso03    >>h_mu_real_pfiso_8tev_zoom" , lep_from_W    , "goff", num_entries);
    e2.SetEventList(evt_mu_list2); e2.Draw("cpfiso03_db>>h_mu_real_cpfiso_8tev_zoom", lep_from_W    , "goff", num_entries);
    e2.SetEventList(evt_mu_list2); e2.Draw("iso        >>h_mu_real_diso_8tev_zoom"  , lep_from_W    , "goff", num_entries);

    // 8 TeV ind components
    e2.SetEventList(evt_mu_list2); 
    e2.Draw("ch_pfiso03/pt>>h_mu_real_ch_pfiso_8tev"                , lep_from_W     , "goff" , num_entries);
    e2.Draw("nh_pfiso03/pt>>h_mu_real_nh_pfiso_8tev"                , lep_from_W     , "goff" , num_entries);
    e2.Draw("em_pfiso03/pt>>h_mu_real_em_pfiso_8tev"                , lep_from_W     , "goff" , num_entries);
    e2.Draw("ch_pfiso03/pt>>h_mu_fake_ch_pfiso_8tev"                , lep_not_from_W , "goff" , num_entries);
    e2.Draw("nh_pfiso03/pt>>h_mu_fake_nh_pfiso_8tev"                , lep_not_from_W , "goff" , num_entries);
    e2.Draw("(nh_pfiso03 + em_pfiso03)/pt>>h_mu_fake_nu_pfiso_8tev" , lep_not_from_W , "goff" , num_entries);
    e2.Draw("em_pfiso03/pt>>h_mu_fake_em_pfiso_8tev"                , lep_not_from_W , "goff" , num_entries);
    e2.Draw("trck_iso/pt>>h_mu_fake_trk_iso_8tev"                   , lep_not_from_W , "goff" , num_entries);

    e2.SetEventList(evt_el_list2);
    e2.Draw("ch_pfiso03/pt>>h_el_real_ch_pfiso_8tev"                , lep_from_W     , "goff" , num_entries);
    e2.Draw("nh_pfiso03/pt>>h_el_real_nh_pfiso_8tev"                , lep_from_W     , "goff" , num_entries);
    e2.Draw("em_pfiso03/pt>>h_el_real_em_pfiso_8tev"                , lep_from_W     , "goff" , num_entries);
    e2.Draw("ch_pfiso03/pt>>h_el_fake_ch_pfiso_8tev"                , lep_not_from_W , "goff" , num_entries);
    e2.Draw("nh_pfiso03/pt>>h_el_fake_nh_pfiso_8tev"                , lep_not_from_W , "goff" , num_entries);
    e2.Draw("em_pfiso03/pt>>h_el_fake_em_pfiso_8tev"                , lep_not_from_W , "goff" , num_entries);
    e2.Draw("trck_iso/pt>>h_el_fake_trk_iso_8tev"                   , lep_not_from_W , "goff" , num_entries);
    e2.Draw("(nh_pfiso03 + em_pfiso03)/pt>>h_el_fake_nu_pfiso_8tev" , lep_not_from_W , "goff" , num_entries);

    e1.SetEventList(evt_mu_list1); e1.Draw("trck_iso/pt>>h_mu_fake_trk_iso_7tev", lep_not_from_W , "goff" , num_entries);
    e1.SetEventList(evt_el_list1); e1.Draw("trck_iso/pt>>h_el_fake_trk_iso_7tev", lep_not_from_W , "goff" , num_entries);

    hc.SetDirectory(NULL);

    // save
    hc.Write("plots/iso_study/iso_study.root", "", "RECREATE");

    // cleanup
    delete evt_el_list1;
    delete evt_el_list2;
    delete evt_mu_list1;
    delete evt_mu_list2;
}


void OverlayIsoPlots(const std::string& suffix = "png")
{
    TH1Container hc("plots/iso_study/iso_study.root");
    rt::SetTDRStyle();
    rt::TH1Overlay::legend_offset_default = 0.025;
    float min_y = 0.0001;

    map<string, TH1Overlay> p;
    p["p_el_iso"] = TH1Overlay("relative electron isolation; rel iso (GeV)", "sb::off lg::top dt::norm logy");
    p["p_el_iso"].Add(hc["h_el_fake_diso_7tev" ], "7 TeV non-prompt (det)", kBlue-6, 2);
    p["p_el_iso"].Add(hc["h_el_real_diso_7tev" ], "7 TeV prompt (det)"    , kBlue  , 2);
    p["p_el_iso"].Add(hc["h_el_fake_pfiso_8tev"], "8 TeV non-prompt (PF)" , kRed-6 , 2);
    p["p_el_iso"].Add(hc["h_el_real_pfiso_8tev"], "8 TeV prompt (PF)"     , kRed   , 2);
    p["p_el_iso"].SetYAxisRange(min_y, 1.0);

    p["p_mu_iso"] = TH1Overlay("relative muon isolation; rel iso (GeV)", "sb::off lg::top dt::norm logy");
    p["p_mu_iso"].Add(hc["h_mu_fake_diso_7tev" ], "7 TeV non-prompt (det)", kBlue-6, 2);
    p["p_mu_iso"].Add(hc["h_mu_real_diso_7tev" ], "7 TeV prompt (det)"    , kBlue  , 2);
    p["p_mu_iso"].Add(hc["h_mu_fake_pfiso_8tev"], "8 TeV non-prompt (PF)" , kRed-6 , 2);
    p["p_mu_iso"].Add(hc["h_mu_real_pfiso_8tev"], "8 TeV prompt (PF)"     , kRed   , 2);
    p["p_mu_iso"].SetYAxisRange(min_y, 1.0);

    p["p_el_iso_zoom"] = TH1Overlay("relative electron isolation (zoom in); rel iso (GeV)", "sb::off lg::top dt::norm");
    p["p_el_iso_zoom"].Add(hc["h_el_fake_diso_7tev_zoom"  ], "7 TeV non-prompt (det)", kBlue-6, 2);
    p["p_el_iso_zoom"].Add(hc["h_el_real_diso_7tev_zoom"  ], "7 TeV prompt (det)"    , kBlue  , 2);
    p["p_el_iso_zoom"].Add(hc["h_el_fake_cpfiso_8tev_zoom"], "8 TeV non-prompt (PF)" , kRed-6 , 2);
    p["p_el_iso_zoom"].Add(hc["h_el_real_cpfiso_8tev_zoom"], "8 TeV prompt (PF)"     , kRed   , 2);
    p["p_el_iso_zoom"].SetYAxisRange(min_y, 1.0);

    p["p_mu_iso_zoom"] = TH1Overlay("relative muon isolation (zoom in); rel iso (GeV)", "sb::off lg::top dt::norm");
    p["p_mu_iso_zoom"].Add(hc["h_mu_fake_diso_7tev_zoom"  ], "7 TeV non-prompt (det)", kBlue-6, 2);
    p["p_mu_iso_zoom"].Add(hc["h_mu_real_diso_7tev_zoom"  ], "7 TeV prompt (det)"    , kBlue  , 2);
    p["p_mu_iso_zoom"].Add(hc["h_mu_fake_cpfiso_8tev_zoom"], "8 TeV non-prompt (PF)" , kRed-6 , 2);
    p["p_mu_iso_zoom"].Add(hc["h_mu_real_cpfiso_8tev_zoom"], "8 TeV prompt (PF)"     , kRed   , 2);
    p["p_mu_iso_zoom"].SetYAxisRange(min_y, 1.0);

    p["p_el_iso_corr"] = TH1Overlay("relative electron isolation; rel iso (GeV)", "sb::off lg::top dt::norm logy");
    p["p_el_iso_corr"].Add(hc["h_el_fake_diso_7tev"  ], "7 TeV non-prompt (det)"     , kBlue-6, 2);
    p["p_el_iso_corr"].Add(hc["h_el_real_diso_7tev"  ], "7 TeV prompt (det)"         , kBlue  , 2);
    p["p_el_iso_corr"].Add(hc["h_el_fake_cpfiso_8tev"], "8 TeV non-prompt (corr PF)" , kRed-6 , 2);
    p["p_el_iso_corr"].Add(hc["h_el_real_cpfiso_8tev"], "8 TeV prompt (corr PF)"     , kRed   , 2);
    p["p_el_iso_corr"].SetYAxisRange(min_y, 1.0);

    p["p_mu_iso_corr"] = TH1Overlay("relative muon isolation; rel iso (GeV)", "sb::off lg::top dt::norm logy");
    p["p_mu_iso_corr"].Add(hc["h_mu_fake_diso_7tev"  ], "7 TeV non-prompt (det)"     , kBlue-6, 2);
    p["p_mu_iso_corr"].Add(hc["h_mu_real_diso_7tev"  ], "7 TeV prompt (det)"         , kBlue  , 2);
    p["p_mu_iso_corr"].Add(hc["h_mu_fake_cpfiso_8tev"], "8 TeV non-prompt (corr PF)" , kRed-6 , 2);
    p["p_mu_iso_corr"].Add(hc["h_mu_real_cpfiso_8tev"], "8 TeV prompt (corr PF)"     , kRed   , 2);
    p["p_mu_iso_corr"].SetYAxisRange(min_y, 1.0);

    p["p_el_fake_iso"] = TH1Overlay("relative electron isolation (fakes); rel iso (GeV)", "sb::off lg::top_right dt::norm logy");
    p["p_el_fake_iso"].Add(hc["h_el_fake_pfiso_8tev" ], "8 TeV (pf iso)" , kBlue    , 2);
    p["p_el_fake_iso"].Add(hc["h_el_fake_cpfiso_8tev"], "8 TeV (cpf iso)", kGreen+2 , 2);
    p["p_el_fake_iso"].Add(hc["h_el_fake_diso_8tev"  ], "8 TeV (det iso)", kRed     , 2);
    p["p_el_fake_iso"].Add(hc["h_el_fake_diso_7tev"  ], "7 TeV (det iso)", kBlack   , 2);
    p["p_el_fake_iso"].SetYAxisRange(min_y, 1.0);

    p["p_el_real_iso"] = TH1Overlay("relative electron isolation (real); rel iso (GeV)", "sb::off lg::top_right dt::norm logy");
    p["p_el_real_iso"].Add(hc["h_el_real_pfiso_8tev" ], "8 TeV (pf iso)" , kBlue    , 2);
    p["p_el_real_iso"].Add(hc["h_el_real_cpfiso_8tev"], "8 TeV (cpf iso)", kGreen+2 , 2);
    p["p_el_real_iso"].Add(hc["h_el_real_diso_8tev"  ], "8 TeV (det iso)", kRed     , 2);
    p["p_el_real_iso"].Add(hc["h_el_real_diso_7tev"  ], "7 TeV (det iso)", kBlack   , 2);
    p["p_el_real_iso"].SetYAxisRange(min_y, 1.0);

    p["p_mu_fake_iso"] = TH1Overlay("relative muons isolation (fakes); rel iso (GeV)", "sb::off lg::top_right dt::norm logy");
    p["p_mu_fake_iso"].Add(hc["h_mu_fake_pfiso_8tev" ], "8 TeV (pf iso)" , kBlue    , 2);
    p["p_mu_fake_iso"].Add(hc["h_mu_fake_cpfiso_8tev"], "8 TeV (cpf iso)", kGreen+2 , 2);
    p["p_mu_fake_iso"].Add(hc["h_mu_fake_diso_8tev"  ], "8 TeV (det iso)", kRed     , 2);
    p["p_mu_fake_iso"].Add(hc["h_mu_fake_diso_7tev"  ], "7 TeV (det iso)", kBlack   , 2);
    p["p_mu_fake_iso"].SetYAxisRange(min_y, 1.0);

    p["p_mu_real_iso"] = TH1Overlay("relative muons isolation (real); rel iso (GeV)", "sb::off lg::top_right dt::norm logy");
    p["p_mu_real_iso"].Add(hc["h_mu_real_pfiso_8tev" ], "8 TeV (pf iso)" , kBlue    , 2);
    p["p_mu_real_iso"].Add(hc["h_mu_real_cpfiso_8tev"], "8 TeV (cpf iso)", kGreen+2 , 2);
    p["p_mu_real_iso"].Add(hc["h_mu_real_diso_8tev"  ], "8 TeV (det iso)", kRed     , 2);
    p["p_mu_real_iso"].Add(hc["h_mu_real_diso_7tev"  ], "7 TeV (det iso)", kBlack   , 2);
    p["p_mu_real_iso"].SetYAxisRange(min_y, 1.0);

    p["p_mu_fake_pfiso_indiv"] = TH1Overlay("relative muons isolation (non-prompt); rel iso (GeV)", "sb::off lg::top dt::norm logy");
    p["p_mu_fake_pfiso_indiv"].Add(hc["h_mu_fake_cpfiso_8tev"], "8 TeV (cpf iso)"           , kGreen+2, 2);
    p["p_mu_fake_pfiso_indiv"].Add(hc["h_mu_fake_pfiso_8tev" ], "8 TeV (pf iso)"            , kBlue   , 2);
    p["p_mu_fake_pfiso_indiv"].Add(hc["h_mu_fake_ch_pfiso_8tev" ], "8 TeV (charged hadron)" , kRed    , 2);
    p["p_mu_fake_pfiso_indiv"].Add(hc["h_mu_fake_nh_pfiso_8tev" ], "8 TeV (neutral hadron)" , kBlack  , 2);
    p["p_mu_fake_pfiso_indiv"].Add(hc["h_mu_fake_em_pfiso_8tev" ], "8 TeV (E&M)"            , kOrange , 2);
    p["p_mu_fake_pfiso_indiv"].SetYAxisRange(min_y, 1.0);

    p["p_el_fake_pfiso_indiv"] = TH1Overlay("relative electrons isolation (non-prompt); rel iso (GeV)", "sb::off lg::top dt::norm logy");
    p["p_el_fake_pfiso_indiv"].Add(hc["h_el_fake_cpfiso_8tev"], "8 TeV (cpf iso)"           , kGreen+2, 2);
    p["p_el_fake_pfiso_indiv"].Add(hc["h_el_fake_pfiso_8tev" ], "8 TeV (pf iso)"            , kBlue   , 2);
    p["p_el_fake_pfiso_indiv"].Add(hc["h_el_fake_ch_pfiso_8tev" ], "8 TeV (charged hadron)" , kRed    , 2);
    p["p_el_fake_pfiso_indiv"].Add(hc["h_el_fake_nh_pfiso_8tev" ], "8 TeV (neutral hadron)" , kBlack  , 2);
    p["p_el_fake_pfiso_indiv"].Add(hc["h_el_fake_em_pfiso_8tev" ], "8 TeV (E&M)"            , kOrange , 2);
    p["p_el_fake_pfiso_indiv"].SetYAxisRange(min_y, 1.0);

    p["p_mu_real_pfiso_indiv"] = TH1Overlay("relative muons isolation (prompt); rel iso (GeV)", "sb::off lg::top dt::norm logy");
    p["p_mu_real_pfiso_indiv"].Add(hc["h_mu_real_cpfiso_8tev"], "8 TeV (cpf iso)"           , kGreen+2, 2);
    p["p_mu_real_pfiso_indiv"].Add(hc["h_mu_real_pfiso_8tev" ], "8 TeV (pf iso)"            , kBlue   , 2);
    p["p_mu_real_pfiso_indiv"].Add(hc["h_mu_real_ch_pfiso_8tev" ], "8 TeV (charged hadron)" , kRed    , 2);
    p["p_mu_real_pfiso_indiv"].Add(hc["h_mu_real_nh_pfiso_8tev" ], "8 TeV (neutral hadron)" , kBlack  , 2);
    p["p_mu_real_pfiso_indiv"].Add(hc["h_mu_real_em_pfiso_8tev" ], "8 TeV (E&M)"            , kOrange , 2);
    p["p_mu_real_pfiso_indiv"].SetYAxisRange(min_y, 1.0);

    p["p_el_real_pfiso_indiv"] = TH1Overlay("relative electrons isolation (prompt); rel iso (GeV)", "sb::off lg::top dt::norm logy");
    p["p_el_real_pfiso_indiv"].Add(hc["h_el_real_cpfiso_8tev"], "8 TeV (cpf iso)"           , kGreen+2, 2);
    p["p_el_real_pfiso_indiv"].Add(hc["h_el_real_pfiso_8tev" ], "8 TeV (pf iso)"            , kBlue   , 2);
    p["p_el_real_pfiso_indiv"].Add(hc["h_el_real_ch_pfiso_8tev" ], "8 TeV (charged hadron)" , kRed    , 2);
    p["p_el_real_pfiso_indiv"].Add(hc["h_el_real_nh_pfiso_8tev" ], "8 TeV (neutral hadron)" , kBlack  , 2);
    p["p_el_real_pfiso_indiv"].Add(hc["h_el_real_em_pfiso_8tev" ], "8 TeV (E&M)"            , kOrange , 2);
    p["p_el_real_pfiso_indiv"].SetYAxisRange(min_y, 1.0);

    p["p_mu_fake_ch_trk_iso"] = TH1Overlay("relative muons isolation (non-prompt); rel iso (GeV)", "sb::off lg::top_right dt::norm logy");
    p["p_mu_fake_ch_trk_iso"].Add(hc["h_mu_fake_ch_pfiso_8tev"], "8 TeV (ch pfiso)" , kBlue, 2);
    p["p_mu_fake_ch_trk_iso"].Add(hc["h_mu_fake_trk_iso_8tev" ], "8 TeV (track iso)", kRed , 2);
    p["p_mu_fake_ch_trk_iso"].SetYAxisRange(min_y, 1.0);

    p["p_el_fake_ch_trk_iso"] = TH1Overlay("relative electrons isolation (non-prompt); rel iso (GeV)", "sb::off lg::top_right dt::norm logy");
    p["p_el_fake_ch_trk_iso"].Add(hc["h_el_fake_ch_pfiso_8tev"], "8 TeV (ch pfiso)" , kBlue, 2);
    p["p_el_fake_ch_trk_iso"].Add(hc["h_el_fake_trk_iso_8tev" ], "8 TeV (track iso)", kRed , 2);
    p["p_el_fake_ch_trk_iso"].SetYAxisRange(min_y, 1.0);

    p["p_mu_fake_pfiso_indiv_eth"] = TH1Overlay("relative muons isolation (non-prompt); rel iso (GeV)", "sb::off lg::top_right dt::norm logy");
    p["p_mu_fake_pfiso_indiv_eth"].Add(hc["h_mu_fake_cpfiso_8tev"   ], "8 TeV (cpf iso)" , kBlue+2 , 2);
    p["p_mu_fake_pfiso_indiv_eth"].Add(hc["h_mu_fake_ch_pfiso_8tev" ], "8 TeV (charged)" , kRed    , 2);
    p["p_mu_fake_pfiso_indiv_eth"].Add(hc["h_mu_fake_nu_pfiso_8tev" ], "8 TeV (neutral)" , kGreen+2, 2);
    p["p_mu_fake_pfiso_indiv_eth"].SetYAxisRange(min_y, 1.0);

    p["p_el_fake_pfiso_indiv_eth"] = TH1Overlay("relative electrons isolation (non-prompt); rel iso (GeV)", "sb::off lg::top_right dt::norm logy");
    p["p_el_fake_pfiso_indiv_eth"].Add(hc["h_el_fake_cpfiso_8tev"   ], "8 TeV (cpf iso)" , kBlue+2 , 2);
    p["p_el_fake_pfiso_indiv_eth"].Add(hc["h_el_fake_ch_pfiso_8tev" ], "8 TeV (charged)" , kRed    , 2);
    p["p_el_fake_pfiso_indiv_eth"].Add(hc["h_el_fake_nu_pfiso_8tev" ], "8 TeV (neutral)" , kGreen+2, 2);
    p["p_el_fake_pfiso_indiv_eth"].SetYAxisRange(min_y, 1.0);

    p["p_mu_fake_trk_iso_compare"] = TH1Overlay("relative muons isolation (non-prompt); rel iso (GeV)", "sb::off lg::top_right dt::norm logy");
    p["p_mu_fake_trk_iso_compare"].Add(hc["h_mu_fake_trk_iso_8tev" ], "8 TeV (track iso)", kRed  , 2);
    p["p_mu_fake_trk_iso_compare"].Add(hc["h_mu_fake_trk_iso_7tev" ], "7 TeV (track iso)", kBlack, 2);
    p["p_mu_fake_trk_iso_compare"].SetYAxisRange(min_y, 1.0);

    p["p_el_fake_trk_iso_compare"] = TH1Overlay("relative electrons isolation (non-prompt); rel iso (GeV)", "sb::off lg::top_right dt::norm logy");
    p["p_el_fake_trk_iso_compare"].Add(hc["h_el_fake_trk_iso_8tev" ], "8 TeV (track iso)", kRed  , 2);
    p["p_el_fake_trk_iso_compare"].Add(hc["h_el_fake_trk_iso_7tev" ], "7 TeV (track iso)", kBlack, 2);
    p["p_el_fake_trk_iso_compare"].SetYAxisRange(min_y, 1.0);

    rt::Print(p, "plots/iso_study", suffix);

    // numbers
    cout << "muon iso==0.1 / iso==0.4 = " << rt::Integral(hc["h_mu_fake_cpfiso_8tev"], 0, 0.10)/rt::Integral(hc["h_mu_fake_cpfiso_8tev"], 0, 0.4) << endl;
    cout << "el iso==0.09 / iso==0.6  = " << rt::Integral(hc["h_el_fake_cpfiso_8tev"], 0, 0.09)/rt::Integral(hc["h_el_fake_cpfiso_8tev"], 0, 0.6) << endl;

}
