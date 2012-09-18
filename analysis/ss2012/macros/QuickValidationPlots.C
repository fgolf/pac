{
	//TChain e1("tree");
	//e1.Add("/home/users/rwkelley/Data/hadoop/babies/ss2012/17Sep/DoubleMu_Run2012C-PromptReco-v2_AOD/merged_ntuple_198934_0.root");
	//rt::DrawAllBranches(e1,    "", "plots/validation/data"    );
	//DrawAllBranches(TTree& tree, const string& selection = "", const string& output_folder = "", long num_entries = 1000000000, const string& suffix = "png")
	
	TChain e2("tree");
	//e2.Add("/home/users/rwkelley/Data/hadoop/babies/ss2012/53X/v1/TTWJets_8TeV-madgraph_Summer12_DR53X-PU_S10_START53_V7A-v1/merged_ntuple_1.root");
	e2.Add("output/test_mc.root");
	ss::SetSignalRegionAliases(e2);
	rt::DrawAllBranches(e2,    "", "plots/validation/mc"    );
	rt::DrawAllBranches(e2, "sr0", "plots/validation/mc_sr0");
}
