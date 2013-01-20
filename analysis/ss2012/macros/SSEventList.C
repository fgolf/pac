#include "rt/RootTools.h"
#include "AnalysisType.h"
#include "SignalRegion.h"
#include "SSB2012.h"
#include "CTable.h"
#include <string>
#include "TCut.h"
#include "TChain.h"
#include "TEventList.h"

using namespace ssb;

void PrintEventList()
{
    //TChain chain("tree"); 
    //chain.Add("babies/hpt/data.root");
	//samesignbtag.Init(&chain);

	//for (long entry = 0; entry != chain.GetEntries(); entry++)
	//{
	//	// intialize event
	//	samesignbtag.GetEntry(entry);
	//	
	//	cout << Form("run: %d, ls: %d, event: %d", run(), ls(), evt()) << endl;
	//	
	//}
}

void SSEventCounts
(
	const ss::AnalysisType::value_type& anal_type     = ss::AnalysisType::high_pt,
	const ss::SignalRegion::value_type& signal_region = ss::SignalRegion::sr0
	bool do_lists = false;
)
{
	ss::AnalysisTypeInfo at_info = ss::GetAnalysisTypeInfo(anal_type);
	ss::SignalRegionInfo sr_info = ss::GetSignalRegionInfo(signal_region);
    TChain chain("tree"); 
    //chain.Add(Form("babies/%s/data.root", at_info.short_name.c_str()));
    chain.Add("output/alex_sync.root");
	ss::SetSignalRegionAliases(chain);
	//cout << chain.GetEntries() << endl;

	//TCut sel = Form("%s && njets>1 && (is_real_data ? is_good_lumi : 1)", sr_info.name.c_str());
	//TCut sel = "njets>1 && (is_real_data ? is_good_lumi : 1)";
	TCut sel = "njets>1 && dilep_type!=4";
	chain.Draw(">>event_list", sel, "goff");
	TEventList* event_list = dynamic_cast<TEventList*>(gDirectory->Get("event_list"));
	chain.SetEventList(event_list);

	TCut mm = "dilep_type==1";
	TCut em = "dilep_type==2";
	TCut ee = "dilep_type==3";
	TCut ss = "is_ss";
	TCut os = "is_os";
	TCut sf = "is_sf";
	TCut df = "is_df";

	// yields                              ee,                       mm,                       em,                     ll
	float y_ss[4] = {chain.GetEntries(ss&&ee), chain.GetEntries(ss&&mm), chain.GetEntries(ss&&em), chain.GetEntries(ss)};
	float y_sf[4] = {chain.GetEntries(sf&&ee), chain.GetEntries(sf&&mm), chain.GetEntries(sf&&em), chain.GetEntries(sf)};
	float y_df[4] = {chain.GetEntries(df&&ee), chain.GetEntries(df&&mm), chain.GetEntries(df&&em), chain.GetEntries(df)};
	float y_os[4] = {chain.GetEntries(os&&ee), chain.GetEntries(os&&mm), chain.GetEntries(os&&em), chain.GetEntries(os)};

	// print tables
	CTable t1;
	t1.setTitle(Form("yields for %s, signal region %s", at_info.title.c_str(), sr_info.name.c_str()));
	t1.useTitle();
	t1.setTable() (         "ee",    "mm",    "em",    "ll")
				  ("SF", y_sf[0], y_sf[1], y_sf[2], y_sf[3])
				  ("DF", y_df[0], y_df[1], y_df[2], y_df[3])
				  ("OS", y_os[0], y_os[1], y_os[2], y_os[3])
				  ("SS", y_ss[0], y_ss[1], y_ss[2], y_ss[3]);
	t1.print();

	// printing lists
	if (not do_lists)
	{
		return;
	}

	Scan("run:ls:evt:lep1_pdgid:lep1_p4.pt():lep1_p4.eta():lep1_corpfiso:lep2_pdgid:lep2_p4.pt():lep2_p4.eta():lep2_corpfiso:pfmet:ht:njets:nbtags", "is_ss && njets>=2", "precision=5 col=3:4:12:10:10:11:13:10:10:11:13:6:5:5:6")
}
