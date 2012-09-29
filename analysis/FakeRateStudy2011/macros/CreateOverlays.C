//#include "Sample.h"
#include "rt/RootTools.h"
#include <map>
#include <string>

void CreateFROverlays(const std::string& suffix = "png")
{
	// set TDR style
	//rt::SetTDRStyle();

	//rt::TH1Container hc_qcd  ("plots/qcd/qcd_test.root");
	//rt::TH1Container hc_ttbar("plots/ttbar/ttbar_test.root");
	rt::TH1Container hc_qcd  ("plots/qcd/qcd_orig.root");
	rt::TH1Container hc_ttbar("plots/ttbar/ttbar_orig.root");

	// overlays
	std::map<std::string, rt::TH1Overlay> p;

	std::string title = "CMS Preliminary, #sqrt{s} = 7";
	float fr_max = 0.3;

	// mc3 plot
	p["p_mc3_id"] = rt::TH1Overlay(Form("%s;parton |id|", title.c_str()), "dt::norm hist");
	p["p_mc3_id"].Add(hc_qcd  ["h_mc3_id"], "QCD"     , kRed , 2, 20);
	p["p_mc3_id"].Add(hc_ttbar["h_mc3_id"], "t#bar{t}", kBlue, 2, 22);
	
	p["p_mc3_pt"] = rt::TH1Overlay(Form("%s;parton p_{T} (GeV)", title.c_str()), "dt::norm");
	p["p_mc3_pt"].Add(hc_qcd  ["h_mc3_pt"], "QCD"     , kRed , 2, 20);
	p["p_mc3_pt"].Add(hc_ttbar["h_mc3_pt"], "t#bar{t}", kBlue, 2, 22);

	// isolation plots
	p["p_reliso"] = rt::TH1Overlay(Form("%s;iso_{rel}", title.c_str()), "dt::norm sb::off");
	p["p_reliso"].Add(hc_qcd  ["h_reliso"], "QCD"     , kRed , 2, 20);
	p["p_reliso"].Add(hc_ttbar["h_reliso"], "t#bar{t}", kBlue, 2, 22);
	
	p["p_reliso_foslice2"] = rt::TH1Overlay(Form("%s;iso_{rel}", title.c_str()), "dt::norm sb::off");
	p["p_reliso_foslice2"].Add(hc_qcd  ["h_reliso_foslice2"], "QCD"     , kRed , 2, 20);
	p["p_reliso_foslice2"].Add(hc_ttbar["h_reliso_foslice2"], "t#bar{t}", kBlue, 2, 22);
	
	p["p_reliso_directb"] = rt::TH1Overlay(Form("%s;iso_{rel}", title.c_str()), "dt::norm sb::off");
	p["p_reliso_directb"].Add(hc_qcd  ["h_reliso_directb"], "QCD"     , kRed , 2, 20);
	p["p_reliso_directb"].Add(hc_ttbar["h_reliso_directb"], "t#bar{t}", kBlue, 2, 22);

	p["p_reliso_directb_foslice2"] = rt::TH1Overlay(Form("%s;iso_{rel}", title.c_str()), "dt::norm sb::off");
	p["p_reliso_directb_foslice2"].Add(hc_qcd  ["h_reliso_directb_foslice2"], "QCD"     , kRed , 2, 20);
	p["p_reliso_directb_foslice2"].Add(hc_ttbar["h_reliso_directb_foslice2"], "t#bar{t}", kBlue, 2, 22);

	p["p_reliso_directb_foslice2_mc3slice2"] = rt::TH1Overlay(Form("%s;iso_{rel}", title.c_str()), "dt::norm sb::off");
	p["p_reliso_directb_foslice2_mc3slice2"].Add(hc_qcd  ["h_reliso_directb_foslice2_mc3slice2"], "QCD"     , kRed , 2, 20);
	p["p_reliso_directb_foslice2_mc3slice2"].Add(hc_ttbar["h_reliso_directb_foslice2_mc3slice2"], "t#bar{t}", kBlue, 2, 22);

	p["p_reliso_directb_foslice2_mc3slice5"] = rt::TH1Overlay(Form("%s;iso_{rel}", title.c_str()), "dt::norm sb::off");
	p["p_reliso_directb_foslice2_mc3slice5"].Add(hc_qcd  ["h_reliso_directb_foslice2_mc3slice5"], "QCD"     , kRed , 2, 20);
	p["p_reliso_directb_foslice2_mc3slice5"].Add(hc_ttbar["h_reliso_directb_foslice2_mc3slice5"], "t#bar{t}", kBlue, 2, 22);

	// vtx plot
	p["p_nvtxs"] = rt::TH1Overlay(Form("%s;# vertices", title.c_str()), "dt::norm");
	p["p_nvtxs"].Add(hc_qcd  ["h_nvtxs"], "QCD"     , kRed , 2, 20);
	p["p_nvtxs"].Add(hc_ttbar["h_nvtxs"], "t#bar{t}", kBlue, 2, 22);
	
	p["p_nvtxs_fo"] = rt::TH1Overlay(Form("%s;# vertices", title.c_str()), "dt::norm");
	p["p_nvtxs_fo"].Add(hc_qcd  ["h_nvtxs_fo"], "QCD"     , kRed , 2, 20);
	p["p_nvtxs_fo"].Add(hc_ttbar["h_nvtxs_fo"], "t#bar{t}", kBlue, 2, 22);
	
	p["p_nvtxs_reweighted"] = rt::TH1Overlay(Form("%s;# vertices", title.c_str()), "dt::norm");
	p["p_nvtxs_reweighted"].Add(hc_qcd  ["h_nvtxs_reweighted"], "QCD"     , kRed, 2, 20);
	p["p_nvtxs_reweighted"].Add(hc_ttbar["h_nvtxs_reweighted"], "t#bar{t}", kBlue, 2, 22);

	// ajet40
	p["p_mufr40c_vs_pt"] = rt::TH1Overlay(Form("%s;p_{T} (GeV);TL ratio", title.c_str()));
	p["p_mufr40c_vs_pt"].Add(hc_qcd  ["h_mufr40c_vs_pt"], "QCD"     , kRed , 2, 20);
	p["p_mufr40c_vs_pt"].Add(hc_ttbar["h_mufr40c_vs_pt"], "t#bar{t}", kBlue, 2, 22);
	p["p_mufr40c_vs_pt"].SetYAxisRange(0, fr_max);

	p["p_mufr40c_vs_eta"] = rt::TH1Overlay(Form("%s;|#eta|;TL ratio", title.c_str()));
	p["p_mufr40c_vs_eta"].Add(hc_qcd  ["h_mufr40c_vs_eta"], "QCD"     , kRed , 2, 20);
	p["p_mufr40c_vs_eta"].Add(hc_ttbar["h_mufr40c_vs_eta"], "t#bar{t}", kBlue, 2, 22);
	p["p_mufr40c_vs_eta"].SetYAxisRange(0, fr_max);

	// ajet40 directb
	p["p_mufr40c_directb_vs_pt"] = rt::TH1Overlay(Form("%s;p_{T} (GeV);TL ratio", title.c_str()));
	p["p_mufr40c_directb_vs_pt"].Add(hc_qcd  ["h_mufr40c_directb_vs_pt"], "QCD"     , kRed , 2, 20);
	p["p_mufr40c_directb_vs_pt"].Add(hc_ttbar["h_mufr40c_directb_vs_pt"], "t#bar{t}", kBlue, 2, 22);
	p["p_mufr40c_directb_vs_pt"].SetYAxisRange(0, fr_max);

	p["p_mufr40c_directb_vs_eta"] = rt::TH1Overlay(Form("%s;|#eta|;TL ratio", title.c_str()));
	p["p_mufr40c_directb_vs_eta"].Add(hc_qcd  ["h_mufr40c_directb_vs_eta"], "QCD"     , kRed , 2, 20);
	p["p_mufr40c_directb_vs_eta"].Add(hc_ttbar["h_mufr40c_directb_vs_eta"], "t#bar{t}", kBlue, 2, 22);
	p["p_mufr40c_directb_vs_eta"].SetYAxisRange(0, fr_max);

	p["p_mufr40c_directb_vs_mc3"] = rt::TH1Overlay(Form("%s;p_{T}^{b} (GeV);TL ratio", title.c_str()));
	p["p_mufr40c_directb_vs_mc3"].Add(hc_qcd  ["h_mufr40c_vs_mc3"], "QCD"     , kRed , 2, 20);
	p["p_mufr40c_directb_vs_mc3"].Add(hc_ttbar["h_mufr40c_vs_mc3"], "t#bar{t}", kBlue, 2, 22);
	p["p_mufr40c_directb_vs_mc3"].SetYAxisRange(0, fr_max*1.5);

	// ajet40 directb slice2
	p["p_mufr40c_directb_slice2_vs_pt"] = rt::TH1Overlay(Form("%s;p_{T} (GeV);TL ratio", title.c_str()));
	p["p_mufr40c_directb_slice2_vs_pt"].Add(hc_qcd  ["h_mufr40c_directb_slice2_vs_pt"], "QCD"     , kRed , 2, 20);
	p["p_mufr40c_directb_slice2_vs_pt"].Add(hc_ttbar["h_mufr40c_directb_slice2_vs_pt"], "t#bar{t}", kBlue, 2, 22);
	p["p_mufr40c_directb_slice2_vs_pt"].SetYAxisRange(0, fr_max);

	p["p_mufr40c_directb_slice2_vs_eta"] = rt::TH1Overlay(Form("%s;|#eta|;TL ratio", title.c_str()));
	p["p_mufr40c_directb_slice2_vs_eta"].Add(hc_qcd  ["h_mufr40c_directb_slice2_vs_eta"], "QCD"     , kRed , 2, 20);
	p["p_mufr40c_directb_slice2_vs_eta"].Add(hc_ttbar["h_mufr40c_directb_slice2_vs_eta"], "t#bar{t}", kBlue, 2, 22);
	p["p_mufr40c_directb_slice2_vs_eta"].SetYAxisRange(0, fr_max);

	// ajet40 directb slice5
	p["p_mufr40c_directb_slice5_vs_pt"] = rt::TH1Overlay(Form("%s;p_{T} (GeV);TL ratio", title.c_str()));
	p["p_mufr40c_directb_slice5_vs_pt"].Add(hc_qcd  ["h_mufr40c_directb_slice5_vs_pt"], "QCD"     , kRed , 2, 20);
	p["p_mufr40c_directb_slice5_vs_pt"].Add(hc_ttbar["h_mufr40c_directb_slice5_vs_pt"], "t#bar{t}", kBlue, 2, 22);
	p["p_mufr40c_directb_slice5_vs_pt"].SetYAxisRange(0, fr_max);

	p["p_mufr40c_directb_slice5_vs_eta"] = rt::TH1Overlay(Form("%s;|#eta|;TL ratio", title.c_str()));
	p["p_mufr40c_directb_slice5_vs_eta"].Add(hc_qcd  ["h_mufr40c_directb_slice5_vs_eta"], "QCD"     , kRed , 2, 20);
	p["p_mufr40c_directb_slice5_vs_eta"].Add(hc_ttbar["h_mufr40c_directb_slice5_vs_eta"], "t#bar{t}", kBlue, 2, 22);
	p["p_mufr40c_directb_slice5_vs_eta"].SetYAxisRange(0, fr_max);

	// print
	rt::Print(p, "plots/an/", suffix);
}
