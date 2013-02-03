#include "rt/RootTools.h"
#include <string>

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

    p["p_mc3_pt"] = TH1Overlay(Form("%s;#mu matched mother b-quark (direct b) p_{T} (GeV)", title.c_str()), "dt::norm lg::top_right");
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

	p["p_mc3pt_vs_ajetpt"] = rt::TH1Overlay(Form("%s;matched mother parton p_{T} (GeV); away jet p_{T} (GeV);", title.c_str()), "lg::off sb::off box");
	p["p_mc3pt_vs_ajetpt"].Add(hc_qcd["h_mc3pt_vs_ajetpt"], data_title, data_color, width, data_marker);

	p["p_mc3pt_vs_ajetpt_db_btag"] = rt::TH1Overlay(Form("%s;matched mother b-quark (direct b) p_{T} (GeV); away b-tagged jet p_{T} (GeV);", title.c_str()), "lg::off sb::off box");
	p["p_mc3pt_vs_ajetpt_db_btag"].Add(hc_qcd["h_mc3pt_vs_ajetpt_db_btag"], data_title, data_color, width, data_marker);
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

