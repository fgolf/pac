#include "rt/RootTools.h"
#include "SignalRegion.h"
#include "AnalysisType.h"
#include "CTable.h"

void EffStudy2012D
(
)
{
	using namespace ss;

	TChain e("tree");
    //e.Add("babies/data_dmu_*.root");
    e.Add("babies/data_del_*.root");

	// book
	//rt::TH1Container hc;
	//hc.Add(new TH1F("h_dilep_mass", "dilepton mass", 100, 0, 200));

	// selection
	//const TCut sel = Form("is_ss && trig && %s", sr_info.name.c_str());
	//const TCut sel = "is_os && trig && 76 < dilep_mass && dilep_mass < 106 && ee";
	//const TCut sel = "is_os && trig && 76 < dilep_mass && dilep_mass < 106 && mm";
	//const TCut sel = "is_os && 76 < dilep_mass && dilep_mass < 106 && mm";
	const TCut z         = "is_os && 76 < dilep_mass && dilep_mass < 106";
    const TCut lep_pt    = "lep1_p4.pt()>20 && lep2_p4.pt()>20";
    const TCut lep_eta   = "abs(lep1_p4.eta())<2.4 && abs(lep2_p4.eta())<2.4";
    const TCut lep_id    = "lep1_passes_id && lep2_passes_id";
    const TCut lep_iso   = "lep1_corpfiso < 0.09 && lep2_corpfiso < 0.09";
    //const TCut lep_iso   = "lep1_corpfiso < 0.1 && lep2_corpfiso < 0.1";
    const TCut ee        = "ee";
    const TCut mm        = "mm";
    const TCut trig      = "trig";
	const TCut run_2012a = "dataset.Contains(\"Run2012A\")";
	const TCut run_2012b = "dataset.Contains(\"Run2012B\")";
	const TCut run_2012c = "dataset.Contains(\"Run2012C\")";
	const TCut run_2012d = "dataset.Contains(\"Run2012D\")";
    //const TCut sel       = z && lep_pt && lep_eta && lep_id && lep_iso && ee && trig;
    const TCut sel       = z && lep_pt && lep_eta && lep_id && lep_iso && mm && trig;

	// counts 
	float y[6];
	y[0] = e.GetEntries(sel);
	y[1] = e.GetEntries(sel && run_2012a);
	y[2] = e.GetEntries(sel && run_2012b);
	y[3] = e.GetEntries(sel && run_2012c);
	y[4] = e.GetEntries(sel && run_2012d);
	y[5] = e.GetEntries(sel && !run_2012d);

	float yerr[6];
	yerr[0] = sqrt(y[0]);
	yerr[1] = sqrt(y[1]);
	yerr[2] = sqrt(y[2]);
	yerr[3] = sqrt(y[3]);
	yerr[4] = sqrt(y[4]);
	yerr[5] = sqrt(y[5]);

	// lumi
	float lumi[6];
	lumi[0] = 19.47; 
	lumi[1] = 0.89; 
	lumi[2] = 4.40; 
	lumi[3] = 6.90; 
	lumi[4] = 7.27; 
	lumi[5] = 19.47-7.27; 

	const float lumi_unc = 0.044;
	float lerr[6];
	lerr[0] = lumi[0] * lumi_unc; 
	lerr[1] = lumi[1] * lumi_unc; 
	lerr[2] = lumi[2] * lumi_unc; 
	lerr[3] = lumi[3] * lumi_unc; 
	lerr[4] = lumi[4] * lumi_unc; 
	lerr[5] = lumi[5] * lumi_unc; 

	// ratio
	float ratio[6];
	ratio[0] = y[0]/(1000*lumi[0]);
	ratio[1] = y[1]/(1000*lumi[1]);
	ratio[2] = y[2]/(1000*lumi[2]);
	ratio[3] = y[3]/(1000*lumi[3]);
	ratio[4] = y[4]/(1000*lumi[4]);
	ratio[5] = y[5]/(1000*lumi[5]);

	float rstats[6];
	rstats[0] = ratio[0] * sqrt( (yerr[0]*yerr[0])/(y[0]*y[0]) + (0));
	rstats[1] = ratio[1] * sqrt( (yerr[1]*yerr[1])/(y[1]*y[1]) + (0));
	rstats[2] = ratio[2] * sqrt( (yerr[2]*yerr[2])/(y[2]*y[2]) + (0));
	rstats[3] = ratio[3] * sqrt( (yerr[3]*yerr[3])/(y[3]*y[3]) + (0));
	rstats[4] = ratio[4] * sqrt( (yerr[4]*yerr[4])/(y[4]*y[4]) + (0));
	rstats[5] = ratio[5] * sqrt( (yerr[5]*yerr[5])/(y[5]*y[5]) + (0));

	float rsys[6];
	rsys[0] = ratio[0] * sqrt( (0) + (lerr[0]*lerr[0])/(lumi[0]*lumi[0]));
	rsys[1] = ratio[1] * sqrt( (0) + (lerr[1]*lerr[1])/(lumi[1]*lumi[1]));
	rsys[2] = ratio[2] * sqrt( (0) + (lerr[2]*lerr[2])/(lumi[2]*lumi[2]));
	rsys[3] = ratio[3] * sqrt( (0) + (lerr[3]*lerr[3])/(lumi[3]*lumi[3]));
	rsys[4] = ratio[4] * sqrt( (0) + (lerr[4]*lerr[4])/(lumi[4]*lumi[4]));
	rsys[5] = ratio[5] * sqrt( (0) + (lerr[5]*lerr[5])/(lumi[5]*lumi[5]));

	// pm string
	string ys[6];
	ys[0] = rt::pm_latex(y[0], yerr[0], "1.0");	
	ys[1] = rt::pm_latex(y[1], yerr[1], "1.0");	
	ys[2] = rt::pm_latex(y[2], yerr[2], "1.0");	
	ys[3] = rt::pm_latex(y[3], yerr[3], "1.0");	
	ys[4] = rt::pm_latex(y[4], yerr[4], "1.0");	
	ys[5] = rt::pm_latex(y[5], yerr[5], "1.0");	

	string ls[6];
	ls[0] = rt::pm_latex(lumi[0], lerr[0], "1.2");	
	ls[1] = rt::pm_latex(lumi[1], lerr[1], "1.2");	
	ls[2] = rt::pm_latex(lumi[2], lerr[2], "1.2");	
	ls[3] = rt::pm_latex(lumi[3], lerr[3], "1.2");	
	ls[4] = rt::pm_latex(lumi[4], lerr[4], "1.2");	
	ls[5] = rt::pm_latex(lumi[5], lerr[5], "1.2");	

	string rs[6];
	//rs[0] = rt::pm(ratio[0], rerr[0]);	
	//rs[1] = rt::pm(ratio[1], rerr[1]);	
	//rs[2] = rt::pm(ratio[2], rerr[2]);	
	//rs[3] = rt::pm(ratio[3], rerr[3]);	
	//rs[4] = rt::pm(ratio[4], rerr[4]);	
	//rs[5] = rt::pm(ratio[5], rerr[5]);	
	rs[0] = Form("%1.3f $\\pm$ %1.3f $\\pm$ %1.3f", ratio[0], rstats[0], rsys[0]);	
	rs[1] = Form("%1.3f $\\pm$ %1.3f $\\pm$ %1.3f", ratio[1], rstats[1], rsys[1]);	
	rs[2] = Form("%1.3f $\\pm$ %1.3f $\\pm$ %1.3f", ratio[2], rstats[2], rsys[2]);	
	rs[3] = Form("%1.3f $\\pm$ %1.3f $\\pm$ %1.3f", ratio[3], rstats[3], rsys[3]);	
	rs[4] = Form("%1.3f $\\pm$ %1.3f $\\pm$ %1.3f", ratio[4], rstats[4], rsys[4]);	
	rs[5] = Form("%1.3f $\\pm$ %1.3f $\\pm$ %1.3f", ratio[5], rstats[5], rsys[5]);	


	CTable t1;
	t1.useTitle();
	t1.setTitle("efficiency numbers z selection");
	t1.setTable() (                 "yields", "luminosity ($fb^{-1}$)", "yield/$pb^{-1}$")
				  ("run 2012A"     ,    ys[1],                   ls[1],             rs[1])  
				  ("run 2012B"     ,    ys[2],                   ls[2],             rs[2])  
				  ("run 2012C"     ,    ys[3],                   ls[3],             rs[3])  
				  ("run 2012D"     ,    ys[4],                   ls[4],             rs[4])  
				  ("run 2012ABC"   ,    ys[5],                   ls[5],             rs[5])  
				  ("run 2012 (all)",    ys[0],                   ls[0],             rs[0]);
	t1.printTex();
}


