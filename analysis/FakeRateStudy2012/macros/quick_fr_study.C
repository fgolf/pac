{
    TChain e("tree");
	//e.Add("~/Data/babies/fr/FakeRate15Nov2012/DoubleElectron_Run2012A-13Jul2012-v1_AOD/*.root");
	//e.Add("~/Data/babies/fr/FakeRate15Nov2012/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/*.root");
	//e.Add("~/Data/babies/fr/FakeRate15Nov2012/DoubleElectron_Run2012B-13Jul2012-v1_AOD/*.root");
	//e.Add("~/Data/babies/fr/FakeRate15Nov2012/DoubleElectron_Run2012C-24Aug2012-v1_AOD/*.root");
	//e.Add("~/Data/babies/fr/FakeRate15Nov2012/DoubleElectron_Run2012C-PromptReco-v2_AOD/*.root");
	//e.Add("~/Data/babies/fr/FakeRate15Nov2012/DoubleMu_Run2012A-13Jul2012-v1_AOD/*.root");
	//e.Add("~/Data/babies/fr/FakeRate15Nov2012/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root");
	e.Add("~/Data/babies/fr/FakeRate15Nov2012/DoubleMu_Run2012B-13Jul2012-v4_AOD/*.root");
	//e.Add("~/Data/babies/fr/FakeRate15Nov2012/DoubleMu_Run2012C-24Aug2012-v1_AOD/*.root");
	//e.Add("~/Data/babies/fr/FakeRate15Nov2012/DoubleMu_Run2012C-PromptReco-v2_AOD/*.root");
	//e.Add("~/Data/babies/fr/FakeRate15Nov2012/SingleMu_Run2012A-13Jul2012-v1_AOD/*.root");
	//e.Add("~/Data/babies/fr/FakeRate15Nov2012/SingleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root");
	//e.Add("~/Data/babies/fr/FakeRate15Nov2012/SingleMu_Run2012B-13Jul2012-v1_AOD/*.root");
	//e.Add("~/Data/babies/fr/FakeRate15Nov2012/SingleMu_Run2012C-24Aug2012-v1_AOD/*.root");
	//e.Add("~/Data/babies/fr/FakeRate15Nov2012/SingleMu_Run2012C-PromptReco-v2_AOD/*.root");

    //TCut el_count   = "abs(id)==11"; 
    //TCut el_kin     = "pt>10 && pt<55 && abs(eta)<2.4";
    //TCut el_pt20    = "pt>20";
    //TCut el_wveto   = "pfmet<20 && pfmt<25";
    //TCut el_zveto   = "mz_fo_gsf<76.0 || mz_fo_gsf>106.0";
    //TCut el_nFO     = "nFOels==0";
    //TCut el_awayj20 = "ptpfcL1Fj1>20";
    //TCut el_awayj40 = "ptpfcL1Fj1>40";
    //TCut el_foid    = "v3_el_ssV7";
    //TCut el_foiso   = "pfiso03_rho<0.6";
    //TCut el_numid   = "num_el_ssV7_noIso";
    //TCut el_numiso  = "pfiso03_rho<0.09";

    //TCut ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_cut         = "pt>8  && ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar>1";
    //TCut ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_cut   = "pt>8  && ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar>1";
    //TCut ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_cut        = "pt>17 && ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar>1";
    //TCut ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_cut  = "pt>17 && ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar>1";
    //TCut ele8_CaloIdT_TrkIdVL_cut                            = "pt>8  && ele8_CaloIdT_TrkIdVL_Jet30_vstar>1";
    //TCut ele8_CaloIdT_TrkIdVL_Jet30_cut                      = "pt>8  && ele8_CaloIdT_TrkIdVL_vstar>1";

    // set event list
    //e1.Draw(">>evt_list", passes_den_noiso, "goff", num_entries);
    //TEventList* list = dynamic_cast<TEventList*>(gDirectory->Get("evt_list"));
    //e1.SetEventList(list);

    // 2012 mu 
    TCut mu_count   = "abs(id)==13"; 
    TCut mu_kin     = "pt>5 && pt<35 && abs(eta)<2.4";
    TCut mu_pt20    = "pt>20";
    TCut mu_wveto   = "pfmet<20 && pfmt<25";
    TCut mu_zveto   = "(mz_fo_ctf<76.0 || mz_fo_ctf>106.0) && (mupsilon_fo_mu<8.0 || mupsilon_fo_mu>12.0)";
    TCut mu_nFO     = "nFOmus==0";
    TCut mu_j20     = "ptpfcL1Fj1>20";
    TCut mu_j40     = "ptpfcL1Fj1>40";
    TCut mu_foid    = "fo_mu_ssV5_noIso";
    TCut mu_foiso   = "pfiso03_db<0.6";
    TCut mu_numid   = "num_mu_ssV5_noIso";
    TCut mu_numiso  = "nt_iso<0.1";
    TCut mu_numiso  = "pfiso03_db<0.1";
    TCut mc_matched = "mc3id!=-999";
    TCut fo_no_iso  = mu_count && mu_kin && mu_wveto && mu_zveto && mu_nFO && mu_foid && mu_j40;

    TCut mu5_cut           = "pt>5  && mu5_vstar>1";
    TCut mu8_cut           = "pt>8  && mu8_vstar>1";
    TCut mu12_cut          = "pt>12 && mu12_vstar>1";
    TCut mu17_cut          = "pt>17 && mu17_vstar>1";
    TCut mu15_eta2p1_cut   = "pt>15 && mu15e21_vstar>1";
    TCut mu24_eta2p1_cut   = "pt>24 && mu24e21_vstar>1";
    TCut mu30_eta2p1_cut   = "pt>30 && mu30e21_vstar>1";
    TCut relIso1p0Mu17_cut = "pt>17 && relIso1p0Mu17_vstar>1";
    TCut relIso1p0Mu20_cut = "pt>20 && relIso1p0Mu20_vstar>1";
    TCut relIso1p0Mu5_cut  = "pt>5 && relIso1p0Mu5_vstar>1";

    //TChain e("tree");
    //e.Add("/Users/rwk7t/Data/fr2/QCD_Pt-15to20_MuPt5Enriched_TuneZ2_7TeV-pythia6_Summer11-PU_S3_START42_V11-v2_frbaby/merged_output_files/*.root");
    //e.Add("/Users/rwk7t/Data/fr2/QCD_Pt-20to30_MuPt5Enriched_TuneZ2_7TeV-pythia6_Summer11-PU_S3_START42_V11-v2_frbaby/merged_output_files/*.root");
    //e.Add("/Users/rwk7t/Data/fr2/QCD_Pt-30to50_MuPt5Enriched_TuneZ2_7TeV-pythia6_Summer11-PU_S3_START42_V11-v2_frbaby/merged_output_files/*.root");
    //e.Add("/Users/rwk7t/Data/fr2/QCD_Pt-50to80_MuPt5Enriched_TuneZ2_7TeV-pythia6_Summer11-PU_S4_START42_V11-v1_frbaby/merged_output_files/*.root");
    //e.Add("/Users/rwk7t/Data/fr2/QCD_Pt-80to120_MuPt5Enriched_TuneZ2_7TeV-pythia6_Summer11-PU_S4_START42_V11-v1_frbaby/merged_output_files/*.root");
    //e.Add("/Users/rwk7t/Data/fr2/QCD_Pt-20_MuEnrichedPt-10_TuneZ2_7TeV-pythia6_Summer11-PU_S3_START42_V11-v2_frbaby/merged_output_files/*.root");
    //TChain e3("tree"); e3.Add("/Users/rwk7t/Data/fr2/QCD_Pt-20_MuEnrichedPt-15_TuneZ2_7TeV-pythia6_Summer11-PU_S4_START42_V11-v1_frbaby/merged_output_files/*.root");

    // 2011 SSB
    //TCut mu_count   = "abs(id)==13"; 
    //TCut mu_kin     = "pt>5 && pt<35 && abs(eta)<2.4";
    //TCut mu_pt20    = "pt>20";
    //TCut mu_wveto   = "pfmet<20 && pfmt<25";
    //TCut mu_zveto   = "(mz_fo_ctf<76.0 || mz_fo_ctf>106.0) && (mupsilon_fo_mu<8.0 || mupsilon_fo_mu>12.0)";
    //TCut mu_nFO     = "nFOels==0";
    //TCut mu_j20     = "ptpfcL1Fj1>20";
    //TCut mu_j40     = "ptpfcL1Fj1>40";
    //TCut mu_foid    = "fo_mussV4_noIso";
    //TCut mu_foiso   = "nt_iso<0.4";
    //TCut mu_numid   = "numNomSSv4noIso";
    //TCut mu_numiso  = "nt_iso<0.1";
    //TCut mc_matched = "mc3id!=-999";
    //TCut fo_no_iso  = mu_count && mu_kin && mu_wveto && mu_zveto && mu_nFO && mu_foid && mu_j40;

    //TCut mc_matched = 
   

}
