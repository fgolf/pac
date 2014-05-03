{
  
  // Required setup:
  // cd /Users/giovannizevidellaporta/UCSD/FakeRate/pac
  // source tools/env.sh
  
  gROOT->ProcessLine(".x $PAC/tools/load_pac.C");
  gROOT->ProcessLine(".L macros/CreateFakeRatePlots.C++");
//  PrintMuonFakeRatePlots("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/6Jan14/testQCDmuNormal.root", "plots/fake_rates/6Jan14norm");
//  PrintMuonFakeRatePlots("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/6Jan14/testQCDmuAbsIso.root", "plots/fake_rates/6Jan14absiso");
//  PrintMuonFakeRatePlots("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/6Jan14/testQCDmuInvIsoOnly.root", "plots/fake_rates/6Jan14invisoonly");
//  PrintMuonFakeRatePlots("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/6Jan14/testQCDmuAbsIso_InvIsoOnly.root", "plots/fake_rates/6Jan14absiso_invisoonly");
//  // Why are the ones below slightly different? Maybe something like JetDeltaPhi. Actually it's just that. Should probably redo everything without the DeltaPhi requirement, even though it makes very little difference.
////  PrintMuonFakeRatePlots("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/8Jan14/7Jan2014normal/ssFR_qcd_standard_7Jan2014normal.root", "plots/fake_rates/6Jan14norm2");
////  PrintMuonFakeRatePlots("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/8Jan14/7Jan2014abs/ssFR_qcd_standard_7Jan2014abs.root", "plots/fake_rates/6Jan14absiso2");
////  PrintMuonFakeRatePlots("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/8Jan14/7Jan2014onlyiso/ssFR_qcd_standard_7Jan2014onlyiso.root", "plots/fake_rates/6Jan14invisoonly2");
////  PrintMuonFakeRatePlots("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/8Jan14/7Jan2014absonlyiso/ssFR_qcd_standard_7Jan2014absonlyiso.root", "plots/fake_rates/6Jan14absiso_invisoonly2");
//  
//  PrintFakeRatePlotsEWKCor("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/8Jan14/ssFR_data_ewkcor_7Jan2014normal.root", "plots/fake_rates/7Jan14normEWK");
//  PrintFakeRatePlotsEWKCor("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/8Jan14/ssFR_data_ewkcor_7Jan2014abs.root", "plots/fake_rates/7Jan14absisoEWK");
//  PrintFakeRatePlotsEWKCor("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/8Jan14/ssFR_data_ewkcor_7Jan2014onlyiso.root", "plots/fake_rates/7Jan14invisoonlyEWK");
//  PrintFakeRatePlotsEWKCor("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/8Jan14/ssFR_data_ewkcor_7Jan2014absonlyiso.root", "plots/fake_rates/7Jan14absiso_invisoonlyEWK");

//  Talk on Jan 24th
//  PrintMuonFakeRatePlots("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/20Jan14/testQCDmu2025_23Jan14.root", "plots/fake_rates/23Jan14norm");
//  PrintMuonFakeRatePlots("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/20Jan14/testQCDmu2025_isoOnly_23Jan14.root", "plots/fake_rates/23Jan14isoonly");
//  PrintMuonFakeRatePlots("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/20Jan14/testQCDmu2025_isoOnlyFOpt_23Jan14.root", "plots/fake_rates/23Jan14isoonlyFOpt");
//
//  
//  PrintFakeRatePlotsEWKCor("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/20Jan14/ssFR_data_ewkcor_23Jan2014B.root", "plots/fake_rates/23Jan14normEWK");
//  PrintFakeRatePlotsEWKCor("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/20Jan14/ssFR_data_ewkcor_23Jan2014Bonlyiso.root", "plots/fake_rates/23Jan14isoonlyEWK");
//  PrintFakeRatePlotsEWKCor("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/20Jan14/ssFR_data_ewkcor_23Jan2014BonlyisoFOpt.root", "plots/fake_rates/23Jan14isoonlyFOptEWK");
//  PrintFakeRatePlotsEWKCor("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/20Jan14/ssFR_data_ewkcor_23Jan2014ConlyisoFOpt.root", "plots/fake_rates/23Jan14CisoonlyFOptEWK");
//
  
// PrintMuonFakeRatePlots("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/27Jan14/ssFR_qcd_standard_27Jan2014onlyisoFOpt.root", "plots/fake_rates/27Jan14onlyisoFOptQCD");
//  PrintFakeRatePlotsEWKCor("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/27Jan14/ssFR_data_ewkcor_27Jan2014onlyisoFOpt.root", "plots/fake_rates/27Jan14onlyisoFOptEWK");
//  PrintFakeRatePlotsEWKCor("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/27Jan14/ssFR_data_ewkcor_27Jan2014onlyisoFOpt8GeV.root", "plots/fake_rates/27Jan14onlyisoFOptEWK8GeV");

//  PrintMuonFakeRatePlots("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/27Jan14/ssFR_qcd_standard_28Jan2014onlyisoFOpt.root", "plots/fake_rates/28Jan14onlyisoFOptQCD");
//  PrintMuonFakeRatePlots("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/27Jan14/ssFR_qcd_standard_28Jan2014.root", "plots/fake_rates/28Jan14QCD");
//  PrintFakeRatePlotsEWKCor("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/27Jan14/ssFR_data_ewkcor_28Jan2014onlyisoFOpt.root", "plots/fake_rates/28Jan14onlyisoFOptEWK");
//  PrintFakeRatePlotsEWKCor("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/27Jan14/ssFR_data_ewkcor_28Jan2014.root", "plots/fake_rates/28Jan14EWK");

  // Starting to play with electrons
//  PrintElectronFakeRatePlots("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/27Jan14/ssFR_qcd_standard_30Jan2014onlyisoFOpt.root", "plots/fake_rates/30Jan14onlyisoFOptQCD");
//  PrintElectronFakeRatePlots("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/27Jan14/ssFR_qcd_standard_30Jan2014.root", "plots/fake_rates/30Jan14QCD");
//  PrintFakeRatePlotsEWKCor("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/27Jan14/ssFR_data_ewkcor_30Jan2014onlyisoFOpt.root", "plots/fake_rates/30Jan14onlyisoFOptEWK");
//  PrintFakeRatePlotsEWKCor("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/27Jan14/ssFR_data_ewkcor_30Jan2014onlyisoFOpt8GeV.root", "plots/fake_rates/30Jan14onlyisoFOpt8GeVEWK");
//  PrintFakeRatePlotsEWKCor("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/27Jan14/ssFR_data_ewkcor_30Jan2014.root", "plots/fake_rates/30Jan14EWK");
//  PrintFakeRatePlotsEWKCor("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/27Jan14/ssFR_data_ewkcor_31Jan2014onlyisoFOpt.root", "plots/fake_rates/31Jan14onlyisoFOptEWK");
//  PrintFakeRatePlotsEWKCor("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/27Jan14/ssFR_data_ewkcor_31Jan2014onlyisoFOpt8GeV.root", "plots/fake_rates/31Jan14onlyisoFOpt8GeVEWK");
//  PrintFakeRatePlotsEWKCor("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/test/27Jan14/ssFR_data_ewkcor_31Jan2014.root", "plots/fake_rates/31Jan14EWK");

  
  // 2D Plots

  Print2DFakeRatePlots("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/synchronization/rootfiles/ssFR_data_ewkcor_sync16Apr2014f.root", 
                        "h_mufr40c", "/Users/giovannizevidellaporta/UCSD/FakeRate/synchronization/plots/data");
  Print2DFakeRatePlots("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/synchronization/rootfiles/ssFR_qcd_standard_sync16Apr2014f.root", 
                       "h_mufr40c", "/Users/giovannizevidellaporta/UCSD/FakeRate/synchronization/plots/qcd");
  Print2DFakeRatePlots("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/synchronization/rootfiles/ssFR_data_ewkcor_sync16Apr2014f.root", 
                       "h_mufr40c_fullMC", "/Users/giovannizevidellaporta/UCSD/FakeRate/synchronization/plots/mc");
  Print2DFakeRatePlots("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/synchronization/rootfiles/ssFR_data_ewkcor_sync16Apr2014f.root", 
                       "h_mufr40c_ewkcor", "/Users/giovannizevidellaporta/UCSD/FakeRate/synchronization/plots/dataewkcor");
  PrintMuonSynchPlots("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/synchronization/rootfiles/ssFR_data_ewkcor_sync16Apr2014f.root", 
                      "/Users/giovannizevidellaporta/UCSD/FakeRate/synchronization/plots/");
//  PrintFakeRatePlotsEWKCor("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/synchronization/rootfiles/ssFR_data_ewkcor_sync.root", "/Users/giovannizevidellaporta/UCSD/FakeRate/synchronization/plots/");
//  PrintFakeRatePlotsEWKCor("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/synchronization/rootfiles/ssFR_data_ewkcor_syncFOpt.root", "/Users/giovannizevidellaporta/UCSD/FakeRate/synchronization/plots/FOpt");
//  PrintFakeRatePlotsEWKCor("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/synchronization/rootfiles/ssFR_data_ewkcor_syncFOpt04.root", "/Users/giovannizevidellaporta/UCSD/FakeRate/synchronization/plots/FOpt04");
  Print1DFakeRatePlots("pdf", "/Users/giovannizevidellaporta/UCSD/FakeRate/synchronization/rootfiles/ssFR_qcd_standard_sync16Apr2014f.root", 
                       "h_mufr40c_vs_pt", "/Users/giovannizevidellaporta/UCSD/FakeRate/synchronization/plots/");
}
