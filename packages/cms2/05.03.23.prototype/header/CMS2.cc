#ifndef CMS2_USE_CMSSW
#include "CMS2.h"
#else
#include "CMS2/NtupleMacrosHeader/interface/CMS2.h"
#endif // CMS2_USE_CMSSW

#include <iostream>

// global object
CMS2 cms2;

// ################################################################################################# //
// CMSSW independent
// ################################################################################################# //
#ifndef CMS2_USE_CMSSW

// implementation of CMS2
// ---------------------------------------------------------------------------------------------- //

CMS2::CMS2()
    : hlt_bits_handle("TBits_hltMaker_hltbits_CMS2.obj")
    , evt_CMS2tag_handle("TStrings_eventMaker_evtCMS2tag_CMS2.obj")
    , evt_dataset_handle("TStrings_eventMaker_evtdataset_CMS2.obj")
    , hlt_trigNames_handle("TStrings_hltMaker_hlttrigNames_CMS2.obj")
    , l1_techtrigNames_handle("TStrings_l1Maker_l1techtrigNames_CMS2.obj")
    , l1_trigNames_handle("TStrings_l1Maker_l1trigNames_CMS2.obj")
    , evt_errCategory_handle("TStrings_recoErrorLogMaker_evterrCategory_CMS2.obj")
    , evt_errModule_handle("TStrings_recoErrorLogMaker_evterrModule_CMS2.obj")
    , evt_errSeverity_handle("TStrings_recoErrorLogMaker_evterrSeverity_CMS2.obj")
    , sparm_comment_handle("TStrings_sParmMaker_sparmcomment_CMS2.obj")
    , sparm_names_handle("TStrings_sParmMaker_sparmnames_CMS2.obj")
    , evt_eventHasHalo_handle("bool_beamHaloMaker_evteventHasHalo_CMS2.obj")
    , hcalnoise_HasBadRBXTS4TS5_handle("bool_hcalNoiseSummaryMaker_hcalnoiseHasBadRBXTS4TS5_CMS2.obj")
    , ls_isValid_handle("bool_luminosityMaker_lsisValid_CMS2.obj")
    , filt_ecalBE_handle("bool_metFilterMaker_filtecalBE_CMS2.obj")
    , filt_ecalDR_handle("bool_metFilterMaker_filtecalDR_CMS2.obj")
    , filt_ecalLaser_handle("bool_metFilterMaker_filtecalLaser_CMS2.obj")
    , filt_ecalTP_handle("bool_metFilterMaker_filtecalTP_CMS2.obj")
    , filt_eeBadSc_handle("bool_metFilterMaker_filteeBadSc_CMS2.obj")
    , filt_greedyMuon_handle("bool_metFilterMaker_filtgreedyMuon_CMS2.obj")
    , filt_hcalLaser_handle("bool_metFilterMaker_filthcalLaser_CMS2.obj")
    , filt_inconsistentMuon_handle("bool_metFilterMaker_filtinconsistentMuon_CMS2.obj")
    , filt_jetIDFailure_handle("bool_metFilterMaker_filtjetIDFailure_CMS2.obj")
    , filt_multiEvent_handle("bool_metFilterMaker_filtmultiEvent_CMS2.obj")
    , filt_trackingFailure_handle("bool_metFilterMaker_filttrackingFailure_CMS2.obj")
    , evt_hbheFilter_handle("bool_metMaker_evthbheFilter_CMS2.obj")
    , els_conv_vtx_flag_handle("bools_electronMaker_elsconvvtxflag_CMS2.obj")
    , els_passingMvaPreselection_handle("bools_electronMaker_elspassingMvaPreselection_CMS2.obj")
    , els_passingPflowPreselection_handle("bools_electronMaker_elspassingPflowPreselection_CMS2.obj")
    , mus_isRPCMuon_handle("bools_muonMaker_musisRPCMuon_CMS2.obj")
    , mus_tightMatch_handle("bools_muonMaker_mustightMatch_CMS2.obj")
    , mus_updatedSta_handle("bools_muonMaker_musupdatedSta_CMS2.obj")
    , pfcands_isMuIso_handle("bools_pfCandidateMaker_pfcandsisMuIso_CMS2.obj")
    , photons_haspixelSeed_handle("bools_photonMaker_photonshaspixelSeed_CMS2.obj")
    , jets_closestElectron_DR_handle("doubles_jetToElAssMaker_jetsclosestElectronDR_CMS2.obj")
    , jets_closestMuon_DR_handle("doubles_jetToMuAssMaker_jetsclosestMuonDR_CMS2.obj")
    , evt_bs_Xwidth_handle("float_beamSpotMaker_evtbsXwidth_CMS2.obj")
    , evt_bs_XwidthErr_handle("float_beamSpotMaker_evtbsXwidthErr_CMS2.obj")
    , evt_bs_Ywidth_handle("float_beamSpotMaker_evtbsYwidth_CMS2.obj")
    , evt_bs_YwidthErr_handle("float_beamSpotMaker_evtbsYwidthErr_CMS2.obj")
    , evt_bs_dxdz_handle("float_beamSpotMaker_evtbsdxdz_CMS2.obj")
    , evt_bs_dxdzErr_handle("float_beamSpotMaker_evtbsdxdzErr_CMS2.obj")
    , evt_bs_dydz_handle("float_beamSpotMaker_evtbsdydz_CMS2.obj")
    , evt_bs_dydzErr_handle("float_beamSpotMaker_evtbsdydzErr_CMS2.obj")
    , evt_bs_sigmaZ_handle("float_beamSpotMaker_evtbssigmaZ_CMS2.obj")
    , evt_bs_sigmaZErr_handle("float_beamSpotMaker_evtbssigmaZErr_CMS2.obj")
    , evt_bs_xErr_handle("float_beamSpotMaker_evtbsxErr_CMS2.obj")
    , evt_bs_yErr_handle("float_beamSpotMaker_evtbsyErr_CMS2.obj")
    , evt_bs_zErr_handle("float_beamSpotMaker_evtbszErr_CMS2.obj")
    , evt_bField_handle("float_eventMaker_evtbField_CMS2.obj")
    , evt_rho_handle("float_fastJetMaker_evtrho_CMS2.obj")
    , evt_rhoJEC_handle("float_fastJetMaker_evtrhoJEC_CMS2.obj")
    , evt_fixgrid_all_rho_handle("float_fixedGridRhoAllMaker_evtfixgridallrho_CMS2.obj")
    , evt_fixgridfastjet_all_rho_handle("float_fixedGridRhoFastJetAllMaker_evtfixgridfastjetallrho_CMS2.obj")
    , evt_kfactor_handle("evtkfactor")
    , evt_scale1fb_handle("evtscale1fb")
    , evt_xsec_excl_handle("evtxsecexcl")
    , evt_xsec_incl_handle("evtxsecincl")
    , gen_met_handle("float_genMaker_genmet_CMS2.obj")
    , gen_metPhi_handle("float_genMaker_genmetPhi_CMS2.obj")
    , genps_alphaQCD_handle("float_genMaker_genpsalphaQCD_CMS2.obj")
    , genps_pthat_handle("float_genMaker_genpspthat_CMS2.obj")
    , genps_qScale_handle("float_genMaker_genpsqScale_CMS2.obj")
    , genps_weight_handle("float_genMaker_genpsweight_CMS2.obj")
    , gen_sumEt_handle("float_genMaker_gensumEt_CMS2.obj")
    , hcalnoise_GetRecHitEnergy_handle("float_hcalNoiseSummaryMaker_hcalnoiseGetRecHitEnergy_CMS2.obj")
    , hcalnoise_GetRecHitEnergy15_handle("float_hcalNoiseSummaryMaker_hcalnoiseGetRecHitEnergy15_CMS2.obj")
    , hcalnoise_GetTotalCalibCharge_handle("float_hcalNoiseSummaryMaker_hcalnoiseGetTotalCalibCharge_CMS2.obj")
    , hcalnoise_TS4TS5NoiseSumE_handle("float_hcalNoiseSummaryMaker_hcalnoiseTS4TS5NoiseSumE_CMS2.obj")
    , hcalnoise_TS4TS5NoiseSumEt_handle("float_hcalNoiseSummaryMaker_hcalnoiseTS4TS5NoiseSumEt_CMS2.obj")
    , hcalnoise_eventChargeFraction_handle("float_hcalNoiseSummaryMaker_hcalnoiseeventChargeFraction_CMS2.obj")
    , hcalnoise_eventEMEnergy_handle("float_hcalNoiseSummaryMaker_hcalnoiseeventEMEnergy_CMS2.obj")
    , hcalnoise_eventEMFraction_handle("float_hcalNoiseSummaryMaker_hcalnoiseeventEMFraction_CMS2.obj")
    , hcalnoise_eventHadEnergy_handle("float_hcalNoiseSummaryMaker_hcalnoiseeventHadEnergy_CMS2.obj")
    , hcalnoise_eventTrackEnergy_handle("float_hcalNoiseSummaryMaker_hcalnoiseeventTrackEnergy_CMS2.obj")
    , hcalnoise_flatNoiseSumE_handle("float_hcalNoiseSummaryMaker_hcalnoiseflatNoiseSumE_CMS2.obj")
    , hcalnoise_flatNoiseSumEt_handle("float_hcalNoiseSummaryMaker_hcalnoiseflatNoiseSumEt_CMS2.obj")
    , hcalnoise_isolatedNoiseSumE_handle("float_hcalNoiseSummaryMaker_hcalnoiseisolatedNoiseSumE_CMS2.obj")
    , hcalnoise_isolatedNoiseSumEt_handle("float_hcalNoiseSummaryMaker_hcalnoiseisolatedNoiseSumEt_CMS2.obj")
    , hcalnoise_max10GeVHitTime_handle("float_hcalNoiseSummaryMaker_hcalnoisemax10GeVHitTime_CMS2.obj")
    , hcalnoise_max25GeVHitTime_handle("float_hcalNoiseSummaryMaker_hcalnoisemax25GeVHitTime_CMS2.obj")
    , hcalnoise_maxE10TS_handle("float_hcalNoiseSummaryMaker_hcalnoisemaxE10TS_CMS2.obj")
    , hcalnoise_maxE2Over10TS_handle("float_hcalNoiseSummaryMaker_hcalnoisemaxE2Over10TS_CMS2.obj")
    , hcalnoise_maxE2TS_handle("float_hcalNoiseSummaryMaker_hcalnoisemaxE2TS_CMS2.obj")
    , hcalnoise_min10GeVHitTime_handle("float_hcalNoiseSummaryMaker_hcalnoisemin10GeVHitTime_CMS2.obj")
    , hcalnoise_min25GeVHitTime_handle("float_hcalNoiseSummaryMaker_hcalnoisemin25GeVHitTime_CMS2.obj")
    , hcalnoise_minE10TS_handle("float_hcalNoiseSummaryMaker_hcalnoiseminE10TS_CMS2.obj")
    , hcalnoise_minE2Over10TS_handle("float_hcalNoiseSummaryMaker_hcalnoiseminE2Over10TS_CMS2.obj")
    , hcalnoise_minE2TS_handle("float_hcalNoiseSummaryMaker_hcalnoiseminE2TS_CMS2.obj")
    , hcalnoise_minHPDEMF_handle("float_hcalNoiseSummaryMaker_hcalnoiseminHPDEMF_CMS2.obj")
    , hcalnoise_minRBXEMF_handle("float_hcalNoiseSummaryMaker_hcalnoiseminRBXEMF_CMS2.obj")
    , hcalnoise_rms10GeVHitTime_handle("float_hcalNoiseSummaryMaker_hcalnoiserms10GeVHitTime_CMS2.obj")
    , hcalnoise_rms25GeVHitTime_handle("float_hcalNoiseSummaryMaker_hcalnoiserms25GeVHitTime_CMS2.obj")
    , hcalnoise_spikeNoiseSumE_handle("float_hcalNoiseSummaryMaker_hcalnoisespikeNoiseSumE_CMS2.obj")
    , hcalnoise_spikeNoiseSumEt_handle("float_hcalNoiseSummaryMaker_hcalnoisespikeNoiseSumEt_CMS2.obj")
    , hcalnoise_triangleNoiseSumE_handle("float_hcalNoiseSummaryMaker_hcalnoisetriangleNoiseSumE_CMS2.obj")
    , hcalnoise_triangleNoiseSumEt_handle("float_hcalNoiseSummaryMaker_hcalnoisetriangleNoiseSumEt_CMS2.obj")
    , evt_kt6calo_central_rho_handle("float_kt6CaloJetsCentralRhoMaker_evtkt6calocentralrho_CMS2.obj")
    , evt_kt6calo_muhlt_rho_handle("float_kt6CaloJetsForMuHLTRhoMaker_evtkt6calomuhltrho_CMS2.obj")
    , evt_kt6calo_rho_handle("float_kt6CaloJetsRhoMaker_evtkt6calorho_CMS2.obj")
    , evt_kt6pf_ctrChargedPU_rho_handle("float_kt6PFJetsCentralChargedPileUpRhoMaker_evtkt6pfctrChargedPUrho_CMS2.obj")
    , evt_kt6pf_ctrNeutral_rho_handle("float_kt6PFJetsCentralNeutralRhoMaker_evtkt6pfctrNeutralrho_CMS2.obj")
    , evt_kt6pf_ctrNeutralTight_rho_handle("float_kt6PFJetsCentralNeutralTightRhoMaker_evtkt6pfctrNeutralTightrho_CMS2.obj")
    , evt_kt6pf_foregiso_rho_handle("float_kt6PFJetsForEGIsolationRhoMaker_evtkt6pfforegisorho_CMS2.obj")
    , l1_met_etTot_handle("float_l1Maker_l1metetTot_CMS2.obj")
    , l1_met_met_handle("float_l1Maker_l1metmet_CMS2.obj")
    , l1_mht_htTot_handle("float_l1Maker_l1mhthtTot_CMS2.obj")
    , l1_mht_mht_handle("float_l1Maker_l1mhtmht_CMS2.obj")
    , ls_avgInsDelLumi_handle("float_luminosityMaker_lsavgInsDelLumi_CMS2.obj")
    , ls_avgInsDelLumiErr_handle("float_luminosityMaker_lsavgInsDelLumiErr_CMS2.obj")
    , ls_avgInsRecLumi_handle("float_luminosityMaker_lsavgInsRecLumi_CMS2.obj")
    , ls_avgInsRecLumiErr_handle("float_luminosityMaker_lsavgInsRecLumiErr_CMS2.obj")
    , ls_deadFrac_handle("float_luminosityMaker_lsdeadFrac_CMS2.obj")
    , ls_intgDelLumi_handle("float_luminosityMaker_lsintgDelLumi_CMS2.obj")
    , ls_intgRecLumi_handle("float_luminosityMaker_lsintgRecLumi_CMS2.obj")
    , ls_lumiSectionLength_handle("float_luminosityMaker_lslumiSectionLength_CMS2.obj")
    , evt_ecalendcapm_met_handle("float_metMaker_evtecalendcapmmet_CMS2.obj")
    , evt_ecalendcapm_metPhi_handle("float_metMaker_evtecalendcapmmetPhi_CMS2.obj")
    , evt_ecalendcapp_met_handle("float_metMaker_evtecalendcappmet_CMS2.obj")
    , evt_ecalendcapp_metPhi_handle("float_metMaker_evtecalendcappmetPhi_CMS2.obj")
    , evt_ecalmet_handle("float_metMaker_evtecalmet_CMS2.obj")
    , evt_ecalmetPhi_handle("float_metMaker_evtecalmetPhi_CMS2.obj")
    , evt_endcapm_met_handle("float_metMaker_evtendcapmmet_CMS2.obj")
    , evt_endcapm_metPhi_handle("float_metMaker_evtendcapmmetPhi_CMS2.obj")
    , evt_endcapp_met_handle("float_metMaker_evtendcappmet_CMS2.obj")
    , evt_endcapp_metPhi_handle("float_metMaker_evtendcappmetPhi_CMS2.obj")
    , evt_hcalendcapm_met_handle("float_metMaker_evthcalendcapmmet_CMS2.obj")
    , evt_hcalendcapm_metPhi_handle("float_metMaker_evthcalendcapmmetPhi_CMS2.obj")
    , evt_hcalendcapp_met_handle("float_metMaker_evthcalendcappmet_CMS2.obj")
    , evt_hcalendcapp_metPhi_handle("float_metMaker_evthcalendcappmetPhi_CMS2.obj")
    , evt_hcalmet_handle("float_metMaker_evthcalmet_CMS2.obj")
    , evt_hcalmetPhi_handle("float_metMaker_evthcalmetPhi_CMS2.obj")
    , evt_met_handle("float_metMaker_evtmet_CMS2.obj")
    , evt_met_EtGt3_handle("float_metMaker_evtmetEtGt3_CMS2.obj")
    , evt_metHO_handle("float_metMaker_evtmetHO_CMS2.obj")
    , evt_metHOPhi_handle("float_metMaker_evtmetHOPhi_CMS2.obj")
    , evt_metHOSig_handle("float_metMaker_evtmetHOSig_CMS2.obj")
    , evt_metMuonCorr_handle("float_metMaker_evtmetMuonCorr_CMS2.obj")
    , evt_metMuonCorrPhi_handle("float_metMaker_evtmetMuonCorrPhi_CMS2.obj")
    , evt_metMuonCorrSig_handle("float_metMaker_evtmetMuonCorrSig_CMS2.obj")
    , evt_metMuonJESCorr_handle("float_metMaker_evtmetMuonJESCorr_CMS2.obj")
    , evt_metMuonJESCorrPhi_handle("float_metMaker_evtmetMuonJESCorrPhi_CMS2.obj")
    , evt_metMuonJESCorrSig_handle("float_metMaker_evtmetMuonJESCorrSig_CMS2.obj")
    , evt_metNoHF_handle("float_metMaker_evtmetNoHF_CMS2.obj")
    , evt_metNoHFHO_handle("float_metMaker_evtmetNoHFHO_CMS2.obj")
    , evt_metNoHFHOPhi_handle("float_metMaker_evtmetNoHFHOPhi_CMS2.obj")
    , evt_metNoHFHOSig_handle("float_metMaker_evtmetNoHFHOSig_CMS2.obj")
    , evt_metNoHFPhi_handle("float_metMaker_evtmetNoHFPhi_CMS2.obj")
    , evt_metNoHFSig_handle("float_metMaker_evtmetNoHFSig_CMS2.obj")
    , evt_metOpt_handle("float_metMaker_evtmetOpt_CMS2.obj")
    , evt_metOptHO_handle("float_metMaker_evtmetOptHO_CMS2.obj")
    , evt_metOptHOPhi_handle("float_metMaker_evtmetOptHOPhi_CMS2.obj")
    , evt_metOptHOSig_handle("float_metMaker_evtmetOptHOSig_CMS2.obj")
    , evt_metOptNoHF_handle("float_metMaker_evtmetOptNoHF_CMS2.obj")
    , evt_metOptNoHFHO_handle("float_metMaker_evtmetOptNoHFHO_CMS2.obj")
    , evt_metOptNoHFHOPhi_handle("float_metMaker_evtmetOptNoHFHOPhi_CMS2.obj")
    , evt_metOptNoHFHOSig_handle("float_metMaker_evtmetOptNoHFHOSig_CMS2.obj")
    , evt_metOptNoHFPhi_handle("float_metMaker_evtmetOptNoHFPhi_CMS2.obj")
    , evt_metOptNoHFSig_handle("float_metMaker_evtmetOptNoHFSig_CMS2.obj")
    , evt_metOptPhi_handle("float_metMaker_evtmetOptPhi_CMS2.obj")
    , evt_metOptSig_handle("float_metMaker_evtmetOptSig_CMS2.obj")
    , evt_metPhi_handle("float_metMaker_evtmetPhi_CMS2.obj")
    , evt_metPhi_EtGt3_handle("float_metMaker_evtmetPhiEtGt3_CMS2.obj")
    , evt_metSig_handle("float_metMaker_evtmetSig_CMS2.obj")
    , evt_sumet_handle("float_metMaker_evtsumet_CMS2.obj")
    , evt_sumet_EtGt3_handle("float_metMaker_evtsumetEtGt3_CMS2.obj")
    , evt_sumetHO_handle("float_metMaker_evtsumetHO_CMS2.obj")
    , evt_sumetMuonCorr_handle("float_metMaker_evtsumetMuonCorr_CMS2.obj")
    , evt_sumetMuonJESCorr_handle("float_metMaker_evtsumetMuonJESCorr_CMS2.obj")
    , evt_sumetNoHF_handle("float_metMaker_evtsumetNoHF_CMS2.obj")
    , evt_sumetNoHFHO_handle("float_metMaker_evtsumetNoHFHO_CMS2.obj")
    , evt_sumetOpt_handle("float_metMaker_evtsumetOpt_CMS2.obj")
    , evt_sumetOptHO_handle("float_metMaker_evtsumetOptHO_CMS2.obj")
    , evt_sumetOptNoHF_handle("float_metMaker_evtsumetOptNoHF_CMS2.obj")
    , evt_sumetOptNoHFHO_handle("float_metMaker_evtsumetOptNoHFHO_CMS2.obj")
    , pdfinfo_pdf1_handle("float_pdfinfoMaker_pdfinfopdf1_CMS2.obj")
    , pdfinfo_pdf2_handle("float_pdfinfoMaker_pdfinfopdf2_CMS2.obj")
    , pdfinfo_scale_handle("float_pdfinfoMaker_pdfinfoscale_CMS2.obj")
    , pdfinfo_x1_handle("float_pdfinfoMaker_pdfinfox1_CMS2.obj")
    , pdfinfo_x2_handle("float_pdfinfoMaker_pdfinfox2_CMS2.obj")
    , evt_fixgrid_rho_all_handle("float_pfCandidateMaker_evtfixgridrhoall_CMS2.obj")
    , evt_fixgrid_rho_ctr_handle("float_pfCandidateMaker_evtfixgridrhoctr_CMS2.obj")
    , evt_fixgrid_rho_fwd_handle("float_pfCandidateMaker_evtfixgridrhofwd_CMS2.obj")
    , evt_pfmet_handle("float_pfmetMaker_evtpfmet_CMS2.obj")
    , evt_pfmetPhi_handle("float_pfmetMaker_evtpfmetPhi_CMS2.obj")
    , evt_pfmetPhi_type1cor_handle("float_pfmetMaker_evtpfmetPhitype1cor_CMS2.obj")
    , evt_pfmetSig_handle("float_pfmetMaker_evtpfmetSig_CMS2.obj")
    , evt_pfmetSignificance_handle("float_pfmetMaker_evtpfmetSignificance_CMS2.obj")
    , evt_pfmet_type1cor_handle("float_pfmetMaker_evtpfmettype1cor_CMS2.obj")
    , evt_pfsumet_handle("float_pfmetMaker_evtpfsumet_CMS2.obj")
    , sparm_filterEfficiency_handle("float_sParmMaker_sparmfilterEfficiency_CMS2.obj")
    , sparm_pdfScale_handle("float_sParmMaker_sparmpdfScale_CMS2.obj")
    , sparm_pdfWeight1_handle("float_sParmMaker_sparmpdfWeight1_CMS2.obj")
    , sparm_pdfWeight2_handle("float_sParmMaker_sparmpdfWeight2_CMS2.obj")
    , sparm_weight_handle("float_sParmMaker_sparmweight_CMS2.obj")
    , sparm_xsec_handle("float_sParmMaker_sparmxsec_CMS2.obj")
    , evt_pf_tcmet_handle("float_tcmetMaker_evtpftcmet_CMS2.obj")
    , evt_pf_tcmetPhi_handle("float_tcmetMaker_evtpftcmetPhi_CMS2.obj")
    , evt_pf_tcmetSig_handle("float_tcmetMaker_evtpftcmetSig_CMS2.obj")
    , evt_pf_tcsumet_handle("float_tcmetMaker_evtpftcsumet_CMS2.obj")
    , evt_tcmet_handle("float_tcmetMaker_evttcmet_CMS2.obj")
    , evt_tcmetPhi_handle("float_tcmetMaker_evttcmetPhi_CMS2.obj")
    , evt_tcmetSig_handle("float_tcmetMaker_evttcmetSig_CMS2.obj")
    , evt_tcsumet_handle("float_tcmetMaker_evttcsumet_CMS2.obj")
    , evt_ww_rho_act_handle("float_wwRhoActiveAreaMaker_evtwwrhoact_CMS2.obj")
    , evt_ww_rho_handle("float_wwRhoDefaultMaker_evtwwrho_CMS2.obj")
    , evt_ww_rho_rnd_handle("float_wwRhoRandomMaker_evtwwrhornd_CMS2.obj")
    , evt_ww_rho_vor_handle("float_wwRhoVoronoiMaker_evtwwrhovor_CMS2.obj")
    , evt_bsp4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVector_beamSpotMaker_evtbsp4_CMS2.obj")
    , l1_met_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVector_l1Maker_l1metp4_CMS2.obj")
    , l1_mht_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVector_l1Maker_l1mhtp4_CMS2.obj")
    , els_mc_motherp4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_candToGenAssMaker_elsmcmotherp4_CMS2.obj")
    , els_mc_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_candToGenAssMaker_elsmcp4_CMS2.obj")
    , jets_mc_gp_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_candToGenAssMaker_jetsmcgpp4_CMS2.obj")
    , jets_mc_motherp4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_candToGenAssMaker_jetsmcmotherp4_CMS2.obj")
    , jets_mc_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_candToGenAssMaker_jetsmcp4_CMS2.obj")
    , mus_mc_motherp4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_candToGenAssMaker_musmcmotherp4_CMS2.obj")
    , mus_mc_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_candToGenAssMaker_musmcp4_CMS2.obj")
    , pfjets_mc_gp_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_candToGenAssMaker_pfjetsmcgpp4_CMS2.obj")
    , pfjets_mc_motherp4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_candToGenAssMaker_pfjetsmcmotherp4_CMS2.obj")
    , pfjets_mc_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_candToGenAssMaker_pfjetsmcp4_CMS2.obj")
    , photons_mc_motherp4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_candToGenAssMaker_photonsmcmotherp4_CMS2.obj")
    , photons_mc_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_candToGenAssMaker_photonsmcp4_CMS2.obj")
    , trk_mcp4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_candToGenAssMaker_trkmcp4_CMS2.obj")
    , els_conv_pos_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_electronMaker_elsconvposp4_CMS2.obj")
    , els_inner_position_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_electronMaker_elsinnerposition_CMS2.obj")
    , els_outer_position_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_electronMaker_elsouterposition_CMS2.obj")
    , els_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_electronMaker_elsp4_CMS2.obj")
    , els_p4In_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_electronMaker_elsp4In_CMS2.obj")
    , els_p4Out_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_electronMaker_elsp4Out_CMS2.obj")
    , els_trk_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_electronMaker_elstrkp4_CMS2.obj")
    , els_vertex_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_electronMaker_elsvertexp4_CMS2.obj")
    , genjets_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_genJetMaker_genjetsp4_CMS2.obj")
    , genps_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_genMaker_genpsp4_CMS2.obj")
    , genps_prod_vtx_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_genMaker_genpsprodvtx_CMS2.obj")
    , gsftrks_inner_position_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_gsfTrackMaker_gsftrksinnerposition_CMS2.obj")
    , gsftrks_outer_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_gsfTrackMaker_gsftrksouterp4_CMS2.obj")
    , gsftrks_outer_position_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_gsfTrackMaker_gsftrksouterposition_CMS2.obj")
    , gsftrks_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_gsfTrackMaker_gsftrksp4_CMS2.obj")
    , gsftrks_vertex_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_gsfTrackMaker_gsftrksvertexp4_CMS2.obj")
    , hyp_ll_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_hypDilepMaker_hypllp4_CMS2.obj")
    , hyp_ll_trk_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_hypDilepMaker_hyplltrkp4_CMS2.obj")
    , hyp_lt_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_hypDilepMaker_hypltp4_CMS2.obj")
    , hyp_lt_trk_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_hypDilepMaker_hyplttrkp4_CMS2.obj")
    , hyp_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_hypDilepMaker_hypp4_CMS2.obj")
    , hyp_FVFit_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_hypDilepVertexMaker_hypFVFitp4_CMS2.obj")
    , hyp_FVFit_v4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_hypDilepVertexMaker_hypFVFitv4_CMS2.obj")
    , hyp_ll_mc_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_hypGenMaker_hypllmcp4_CMS2.obj")
    , hyp_lt_mc_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_hypGenMaker_hypltmcp4_CMS2.obj")
    , jets_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_jetMaker_jetsp4_CMS2.obj")
    , jets_vertex_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_jetMaker_jetsvertexp4_CMS2.obj")
    , l1_emiso_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_l1Maker_l1emisop4_CMS2.obj")
    , l1_emnoiso_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_l1Maker_l1emnoisop4_CMS2.obj")
    , l1_jetsc_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_l1Maker_l1jetscp4_CMS2.obj")
    , l1_jetsf_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_l1Maker_l1jetsfp4_CMS2.obj")
    , l1_jetst_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_l1Maker_l1jetstp4_CMS2.obj")
    , l1_mus_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_l1Maker_l1musp4_CMS2.obj")
    , mus_ecalpos_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_muonMaker_musecalposp4_CMS2.obj")
    , mus_fitpicky_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_muonMaker_musfitpickyp4_CMS2.obj")
    , mus_fittev_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_muonMaker_musfittevp4_CMS2.obj")
    , mus_fittpfms_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_muonMaker_musfittpfmsp4_CMS2.obj")
    , mus_gfit_outerPos_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_muonMaker_musgfitouterPosp4_CMS2.obj")
    , mus_gfit_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_muonMaker_musgfitp4_CMS2.obj")
    , mus_gfit_vertex_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_muonMaker_musgfitvertexp4_CMS2.obj")
    , mus_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_muonMaker_musp4_CMS2.obj")
    , mus_pfp4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_muonMaker_muspfp4_CMS2.obj")
    , mus_pfposAtEcal_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_muonMaker_muspfposAtEcalp4_CMS2.obj")
    , mus_sta_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_muonMaker_musstap4_CMS2.obj")
    , mus_sta_vertex_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_muonMaker_musstavertexp4_CMS2.obj")
    , mus_trk_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_muonMaker_mustrkp4_CMS2.obj")
    , mus_vertex_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_muonMaker_musvertexp4_CMS2.obj")
    , pfcands_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_pfCandidateMaker_pfcandsp4_CMS2.obj")
    , pfcands_posAtEcal_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_pfCandidateMaker_pfcandsposAtEcalp4_CMS2.obj")
    , pfels_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_pfElectronMaker_pfelsp4_CMS2.obj")
    , pfels_posAtEcal_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_pfElectronMaker_pfelsposAtEcalp4_CMS2.obj")
    , pfjets_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_pfJetMaker_pfjetsp4_CMS2.obj")
    , pfmus_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_pfMuonMaker_pfmusp4_CMS2.obj")
    , pfmus_posAtEcal_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_pfMuonMaker_pfmusposAtEcalp4_CMS2.obj")
    , taus_pf_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_pftauMaker_tauspfp4_CMS2.obj")
    , photons_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_photonMaker_photonsp4_CMS2.obj")
    , convs_refitPairMom_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_recoConversionMaker_convsrefitPairMomp4_CMS2.obj")
    , convs_vtxpos_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_recoConversionMaker_convsvtxpos_CMS2.obj")
    , scs_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_scMaker_scsp4_CMS2.obj")
    , scs_pos_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_scMaker_scsposp4_CMS2.obj")
    , scs_vtx_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_scMaker_scsvtxp4_CMS2.obj")
    , svs_flight_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_secondaryVertexMaker_svsflight_CMS2.obj")
    , svs_mc3_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_secondaryVertexMaker_svsmc3p4_CMS2.obj")
    , svs_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_secondaryVertexMaker_svsp4_CMS2.obj")
    , svs_position_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_secondaryVertexMaker_svsposition_CMS2.obj")
    , svs_refitp4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_secondaryVertexMaker_svsrefitp4_CMS2.obj")
    , trks_inner_position_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_trackMaker_trksinnerposition_CMS2.obj")
    , trks_outer_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_trackMaker_trksouterp4_CMS2.obj")
    , trks_outer_position_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_trackMaker_trksouterposition_CMS2.obj")
    , trks_trk_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_trackMaker_trkstrkp4_CMS2.obj")
    , trks_vertex_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_trackMaker_trksvertexp4_CMS2.obj")
    , trkjets_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_trkJetMaker_trkjetsp4_CMS2.obj")
    , vtxs_position_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_vertexMaker_vtxsposition_CMS2.obj")
    , bsvtxs_position_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectors_vertexMakerWithBS_bsvtxsposition_CMS2.obj")
    , els_convs_pos_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectorss_electronMaker_elsconvsposp4_CMS2.obj")
    , genps_lepdaughter_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectorss_genMaker_genpslepdaughterp4_CMS2.obj")
    , hlt_trigObjs_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectorss_hltMaker_hlttrigObjsp4_CMS2.obj")
    , hyp_jets_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectorss_hypDilepMaker_hypjetsp4_CMS2.obj")
    , hyp_other_jets_p4_handle("floatROOTMathPxPyPzE4DROOTMathLorentzVectorss_hypDilepMaker_hypotherjetsp4_CMS2.obj")
    , jpts_combinedSecondaryVertexBJetTag_handle("floats_bTagJPTJetMaker_jptscombinedSecondaryVertexBJetTag_CMS2.obj")
    , jpts_combinedSecondaryVertexMVABJetTag_handle("floats_bTagJPTJetMaker_jptscombinedSecondaryVertexMVABJetTag_CMS2.obj")
    , jpts_jetBProbabilityBJetTag_handle("floats_bTagJPTJetMaker_jptsjetBProbabilityBJetTag_CMS2.obj")
    , jpts_jetProbabilityBJetTag_handle("floats_bTagJPTJetMaker_jptsjetProbabilityBJetTag_CMS2.obj")
    , jpts_simpleSecondaryVertexBJetTag_handle("floats_bTagJPTJetMaker_jptssimpleSecondaryVertexBJetTag_CMS2.obj")
    , jpts_simpleSecondaryVertexHighEffBJetTag_handle("floats_bTagJPTJetMaker_jptssimpleSecondaryVertexHighEffBJetTag_CMS2.obj")
    , jpts_simpleSecondaryVertexHighPurBJetTags_handle("floats_bTagJPTJetMaker_jptssimpleSecondaryVertexHighPurBJetTag_CMS2.obj")
    , jpts_softElectronByIP3dBJetTag_handle("floats_bTagJPTJetMaker_jptssoftElectronByIP3dBJetTag_CMS2.obj")
    , jpts_softElectronByPtBJetTag_handle("floats_bTagJPTJetMaker_jptssoftElectronByPtBJetTag_CMS2.obj")
    , jpts_softElectronTag_handle("floats_bTagJPTJetMaker_jptssoftElectronTag_CMS2.obj")
    , jpts_softMuonBJetTag_handle("floats_bTagJPTJetMaker_jptssoftMuonBJetTag_CMS2.obj")
    , jpts_softMuonByIP3dBJetTag_handle("floats_bTagJPTJetMaker_jptssoftMuonByIP3dBJetTag_CMS2.obj")
    , jpts_softMuonByPtBJetTag_handle("floats_bTagJPTJetMaker_jptssoftMuonByPtBJetTag_CMS2.obj")
    , jpts_trackCountingHighEffBJetTag_handle("floats_bTagJPTJetMaker_jptstrackCountingHighEffBJetTag_CMS2.obj")
    , jpts_trackCountingHighPurBJetTag_handle("floats_bTagJPTJetMaker_jptstrackCountingHighPurBJetTag_CMS2.obj")
    , jets_combinedSecondaryVertexBJetTag_handle("floats_bTagMaker_jetscombinedSecondaryVertexBJetTag_CMS2.obj")
    , jets_combinedSecondaryVertexMVABJetTag_handle("floats_bTagMaker_jetscombinedSecondaryVertexMVABJetTag_CMS2.obj")
    , jets_jetBProbabilityBJetTag_handle("floats_bTagMaker_jetsjetBProbabilityBJetTag_CMS2.obj")
    , jets_jetProbabilityBJetTag_handle("floats_bTagMaker_jetsjetProbabilityBJetTag_CMS2.obj")
    , jets_simpleSecondaryVertexBJetTag_handle("floats_bTagMaker_jetssimpleSecondaryVertexBJetTag_CMS2.obj")
    , jets_simpleSecondaryVertexHighEffBJetTag_handle("floats_bTagMaker_jetssimpleSecondaryVertexHighEffBJetTag_CMS2.obj")
    , jets_simpleSecondaryVertexHighPurBJetTags_handle("floats_bTagMaker_jetssimpleSecondaryVertexHighPurBJetTag_CMS2.obj")
    , jets_softElectronByIP3dBJetTag_handle("floats_bTagMaker_jetssoftElectronByIP3dBJetTag_CMS2.obj")
    , jets_softElectronByPtBJetTag_handle("floats_bTagMaker_jetssoftElectronByPtBJetTag_CMS2.obj")
    , jets_softElectronTag_handle("floats_bTagMaker_jetssoftElectronTag_CMS2.obj")
    , jets_softMuonBJetTag_handle("floats_bTagMaker_jetssoftMuonBJetTag_CMS2.obj")
    , jets_softMuonByIP3dBJetTag_handle("floats_bTagMaker_jetssoftMuonByIP3dBJetTag_CMS2.obj")
    , jets_softMuonByPtBJetTag_handle("floats_bTagMaker_jetssoftMuonByPtBJetTag_CMS2.obj")
    , jets_trackCountingHighEffBJetTag_handle("floats_bTagMaker_jetstrackCountingHighEffBJetTag_CMS2.obj")
    , jets_trackCountingHighPurBJetTag_handle("floats_bTagMaker_jetstrackCountingHighPurBJetTag_CMS2.obj")
    , pfjets_combinedSecondaryVertexBJetTag_handle("floats_bTagPFJetMaker_pfjetscombinedSecondaryVertexBJetTag_CMS2.obj")
    , pfjets_combinedSecondaryVertexMVABJetTag_handle("floats_bTagPFJetMaker_pfjetscombinedSecondaryVertexMVABJetTag_CMS2.obj")
    , pfjets_jetBProbabilityBJetTag_handle("floats_bTagPFJetMaker_pfjetsjetBProbabilityBJetTag_CMS2.obj")
    , pfjets_jetProbabilityBJetTag_handle("floats_bTagPFJetMaker_pfjetsjetProbabilityBJetTag_CMS2.obj")
    , pfjets_simpleSecondaryVertexBJetTag_handle("floats_bTagPFJetMaker_pfjetssimpleSecondaryVertexBJetTag_CMS2.obj")
    , pfjets_simpleSecondaryVertexHighEffBJetTag_handle("floats_bTagPFJetMaker_pfjetssimpleSecondaryVertexHighEffBJetTag_CMS2.obj")
    , pfjets_simpleSecondaryVertexHighPurBJetTags_handle("floats_bTagPFJetMaker_pfjetssimpleSecondaryVertexHighPurBJetTag_CMS2.obj")
    , pfjets_softElectronByIP3dBJetTag_handle("floats_bTagPFJetMaker_pfjetssoftElectronByIP3dBJetTag_CMS2.obj")
    , pfjets_softElectronByPtBJetTag_handle("floats_bTagPFJetMaker_pfjetssoftElectronByPtBJetTag_CMS2.obj")
    , pfjets_softElectronTag_handle("floats_bTagPFJetMaker_pfjetssoftElectronTag_CMS2.obj")
    , pfjets_softMuonBJetTag_handle("floats_bTagPFJetMaker_pfjetssoftMuonBJetTag_CMS2.obj")
    , pfjets_softMuonByIP3dBJetTag_handle("floats_bTagPFJetMaker_pfjetssoftMuonByIP3dBJetTag_CMS2.obj")
    , pfjets_softMuonByPtBJetTag_handle("floats_bTagPFJetMaker_pfjetssoftMuonByPtBJetTag_CMS2.obj")
    , pfjets_trackCountingHighEffBJetTag_handle("floats_bTagPFJetMaker_pfjetstrackCountingHighEffBJetTag_CMS2.obj")
    , pfjets_trackCountingHighPurBJetTag_handle("floats_bTagPFJetMaker_pfjetstrackCountingHighPurBJetTag_CMS2.obj")
    , trkjets_combinedSecondaryVertexBJetTag_handle("floats_bTagTrkMaker_trkjetscombinedSecondaryVertexBJetTag_CMS2.obj")
    , trkjets_combinedSecondaryVertexMVABJetTag_handle("floats_bTagTrkMaker_trkjetscombinedSecondaryVertexMVABJetTag_CMS2.obj")
    , trkjets_jetBProbabilityBJetTag_handle("floats_bTagTrkMaker_trkjetsjetBProbabilityBJetTag_CMS2.obj")
    , trkjets_jetProbabilityBJetTag_handle("floats_bTagTrkMaker_trkjetsjetProbabilityBJetTag_CMS2.obj")
    , trkjets_simpleSecondaryVertexBJetTag_handle("floats_bTagTrkMaker_trkjetssimpleSecondaryVertexBJetTag_CMS2.obj")
    , trkjets_simpleSecondaryVertexHighEffBJetTag_handle("floats_bTagTrkMaker_trkjetssimpleSecondaryVertexHighEffBJetTag_CMS2.obj")
    , trkjets_simpleSecondaryVertexHighPurBJetTags_handle("floats_bTagTrkMaker_trkjetssimpleSecondaryVertexHighPurBJetTag_CMS2.obj")
    , trkjets_softElectronByIP3dBJetTag_handle("floats_bTagTrkMaker_trkjetssoftElectronByIP3dBJetTag_CMS2.obj")
    , trkjets_softElectronByPtBJetTag_handle("floats_bTagTrkMaker_trkjetssoftElectronByPtBJetTag_CMS2.obj")
    , trkjets_softElectronTag_handle("floats_bTagTrkMaker_trkjetssoftElectronTag_CMS2.obj")
    , trkjets_softMuonBJetTag_handle("floats_bTagTrkMaker_trkjetssoftMuonBJetTag_CMS2.obj")
    , trkjets_softMuonByIP3dBJetTag_handle("floats_bTagTrkMaker_trkjetssoftMuonByIP3dBJetTag_CMS2.obj")
    , trkjets_softMuonByPtBJetTag_handle("floats_bTagTrkMaker_trkjetssoftMuonByPtBJetTag_CMS2.obj")
    , trkjets_trackCountingHighEffBJetTag_handle("floats_bTagTrkMaker_trkjetstrackCountingHighEffBJetTag_CMS2.obj")
    , trkjets_trackCountingHighPurBJetTag_handle("floats_bTagTrkMaker_trkjetstrackCountingHighPurBJetTag_CMS2.obj")
    , evt_bs_covMatrix_handle("floats_beamSpotMaker_evtbscovMatrix_CMS2.obj")
    , els_mc3dr_handle("floats_candToGenAssMaker_elsmc3dr_CMS2.obj")
    , els_mcdr_handle("floats_candToGenAssMaker_elsmcdr_CMS2.obj")
    , jets_mc3dr_handle("floats_candToGenAssMaker_jetsmc3dr_CMS2.obj")
    , jets_mcdr_handle("floats_candToGenAssMaker_jetsmcdr_CMS2.obj")
    , jets_mc_emEnergy_handle("floats_candToGenAssMaker_jetsmcemEnergy_CMS2.obj")
    , jets_mc_gpdr_handle("floats_candToGenAssMaker_jetsmcgpdr_CMS2.obj")
    , jets_mc_hadEnergy_handle("floats_candToGenAssMaker_jetsmchadEnergy_CMS2.obj")
    , jets_mc_invEnergy_handle("floats_candToGenAssMaker_jetsmcinvEnergy_CMS2.obj")
    , jets_mc_otherEnergy_handle("floats_candToGenAssMaker_jetsmcotherEnergy_CMS2.obj")
    , mus_mc3dr_handle("floats_candToGenAssMaker_musmc3dr_CMS2.obj")
    , mus_mcdr_handle("floats_candToGenAssMaker_musmcdr_CMS2.obj")
    , pfjets_mc3dr_handle("floats_candToGenAssMaker_pfjetsmc3dr_CMS2.obj")
    , pfjets_mcdr_handle("floats_candToGenAssMaker_pfjetsmcdr_CMS2.obj")
    , pfjets_mc_emEnergy_handle("floats_candToGenAssMaker_pfjetsmcemEnergy_CMS2.obj")
    , pfjets_mc_gpdr_handle("floats_candToGenAssMaker_pfjetsmcgpdr_CMS2.obj")
    , pfjets_mc_hadEnergy_handle("floats_candToGenAssMaker_pfjetsmchadEnergy_CMS2.obj")
    , pfjets_mc_invEnergy_handle("floats_candToGenAssMaker_pfjetsmcinvEnergy_CMS2.obj")
    , pfjets_mc_otherEnergy_handle("floats_candToGenAssMaker_pfjetsmcotherEnergy_CMS2.obj")
    , photons_mc3dr_handle("floats_candToGenAssMaker_photonsmc3dr_CMS2.obj")
    , photons_mcdr_handle("floats_candToGenAssMaker_photonsmcdr_CMS2.obj")
    , trk_mc3dr_handle("floats_candToGenAssMaker_trkmc3dr_CMS2.obj")
    , trk_mcdr_handle("floats_candToGenAssMaker_trkmcdr_CMS2.obj")
    , els_ecalJuraIso_handle("floats_elCaloIsoMaker_elsecalJuraIso_CMS2.obj")
    , els_ecalJuraTowerIso_handle("floats_elCaloIsoMaker_elsecalJuraTowerIso_CMS2.obj")
    , els_hcalConeIso_handle("floats_elCaloIsoMaker_elshcalConeIso_CMS2.obj")
    , els_tkJuraIso_handle("floats_elTkJuraIsoMaker_elstkJuraIso_CMS2.obj")
    , els_jetdr_handle("floats_elToJetAssMaker_elsjetdr_CMS2.obj")
    , els_musdr_handle("floats_elToMuAssMaker_elsmusdr_CMS2.obj")
    , els_isoR03_chpf_radial_handle("floats_electronIsolationMaker_elsisoR03chpfradial_CMS2.obj")
    , els_isoR03_chpf_radialTight_handle("floats_electronIsolationMaker_elsisoR03chpfradialTight_CMS2.obj")
    , els_isoR03_chpf_radialTight_bv_handle("floats_electronIsolationMaker_elsisoR03chpfradialTightbv_CMS2.obj")
    , els_isoR03_chpf_radial_bv_handle("floats_electronIsolationMaker_elsisoR03chpfradialbv_CMS2.obj")
    , els_isoR03_empf_radial_handle("floats_electronIsolationMaker_elsisoR03empfradial_CMS2.obj")
    , els_isoR03_empf_radialTight_handle("floats_electronIsolationMaker_elsisoR03empfradialTight_CMS2.obj")
    , els_isoR03_empf_radialTight_bv_handle("floats_electronIsolationMaker_elsisoR03empfradialTightbv_CMS2.obj")
    , els_isoR03_empf_radial_bv_handle("floats_electronIsolationMaker_elsisoR03empfradialbv_CMS2.obj")
    , els_isoR03_nhpf_radial_handle("floats_electronIsolationMaker_elsisoR03nhpfradial_CMS2.obj")
    , els_isoR03_nhpf_radialTight_handle("floats_electronIsolationMaker_elsisoR03nhpfradialTight_CMS2.obj")
    , els_isoR03_nhpf_radialTight_bv_handle("floats_electronIsolationMaker_elsisoR03nhpfradialTightbv_CMS2.obj")
    , els_isoR03_nhpf_radial_bv_handle("floats_electronIsolationMaker_elsisoR03nhpfradialbv_CMS2.obj")
    , els_isoR03_pf2012n0p5_ch_handle("floats_electronIsolationMaker_elsisoR03pf2012n0p5ch_CMS2.obj")
    , els_isoR03_pf2012n0p5_em_handle("floats_electronIsolationMaker_elsisoR03pf2012n0p5em_CMS2.obj")
    , els_isoR03_pf2012n0p5_nh_handle("floats_electronIsolationMaker_elsisoR03pf2012n0p5nh_CMS2.obj")
    , els_isoR03_pf_radial_handle("floats_electronIsolationMaker_elsisoR03pfradial_CMS2.obj")
    , els_isoR03_pf_radialTight_handle("floats_electronIsolationMaker_elsisoR03pfradialTight_CMS2.obj")
    , els_isoR03_pf_radialTight_bv_handle("floats_electronIsolationMaker_elsisoR03pfradialTightbv_CMS2.obj")
    , els_isoR03_pf_radial_bv_handle("floats_electronIsolationMaker_elsisoR03pfradialbv_CMS2.obj")
    , els_chi2_handle("floats_electronMaker_elschi2_CMS2.obj")
    , els_ckf_chi2_handle("floats_electronMaker_elsckfchi2_CMS2.obj")
    , els_ckf_ndof_handle("floats_electronMaker_elsckfndof_CMS2.obj")
    , els_conv_dcot_handle("floats_electronMaker_elsconvdcot_CMS2.obj")
    , els_conv_dist_handle("floats_electronMaker_elsconvdist_CMS2.obj")
    , els_conv_old_dcot_handle("floats_electronMaker_elsconvolddcot_CMS2.obj")
    , els_conv_old_dist_handle("floats_electronMaker_elsconvolddist_CMS2.obj")
    , els_conv_old_radius_handle("floats_electronMaker_elsconvoldradius_CMS2.obj")
    , els_conv_radius_handle("floats_electronMaker_elsconvradius_CMS2.obj")
    , els_d0_handle("floats_electronMaker_elsd0_CMS2.obj")
    , els_d0Err_handle("floats_electronMaker_elsd0Err_CMS2.obj")
    , els_d0corr_handle("floats_electronMaker_elsd0corr_CMS2.obj")
    , els_dEtaIn_handle("floats_electronMaker_elsdEtaIn_CMS2.obj")
    , els_dEtaOut_handle("floats_electronMaker_elsdEtaOut_CMS2.obj")
    , els_dPhiIn_handle("floats_electronMaker_elsdPhiIn_CMS2.obj")
    , els_dPhiInPhiOut_handle("floats_electronMaker_elsdPhiInPhiOut_CMS2.obj")
    , els_dPhiOut_handle("floats_electronMaker_elsdPhiOut_CMS2.obj")
    , els_deltaEtaEleClusterTrackAtCalo_handle("floats_electronMaker_elsdeltaEtaEleClusterTrackAtCalo_CMS2.obj")
    , els_deltaPhiEleClusterTrackAtCalo_handle("floats_electronMaker_elsdeltaPhiEleClusterTrackAtCalo_CMS2.obj")
    , els_e1x5_handle("floats_electronMaker_else1x5_CMS2.obj")
    , els_e2x5Max_handle("floats_electronMaker_else2x5Max_CMS2.obj")
    , els_e3x3_handle("floats_electronMaker_else3x3_CMS2.obj")
    , els_e5x5_handle("floats_electronMaker_else5x5_CMS2.obj")
    , els_eMax_handle("floats_electronMaker_elseMax_CMS2.obj")
    , els_eOverPIn_handle("floats_electronMaker_elseOverPIn_CMS2.obj")
    , els_eOverPOut_handle("floats_electronMaker_elseOverPOut_CMS2.obj")
    , els_eSC_handle("floats_electronMaker_elseSC_CMS2.obj")
    , els_eSCPresh_handle("floats_electronMaker_elseSCPresh_CMS2.obj")
    , els_eSCRaw_handle("floats_electronMaker_elseSCRaw_CMS2.obj")
    , els_eSeed_handle("floats_electronMaker_elseSeed_CMS2.obj")
    , els_eSeedOverPIn_handle("floats_electronMaker_elseSeedOverPIn_CMS2.obj")
    , els_eSeedOverPOut_handle("floats_electronMaker_elseSeedOverPOut_CMS2.obj")
    , els_ecalEnergy_handle("floats_electronMaker_elsecalEnergy_CMS2.obj")
    , els_ecalEnergyError_handle("floats_electronMaker_elsecalEnergyError_CMS2.obj")
    , els_ecalIso_handle("floats_electronMaker_elsecalIso_CMS2.obj")
    , els_ecalIso04_handle("floats_electronMaker_elsecalIso04_CMS2.obj")
    , els_etaErr_handle("floats_electronMaker_elsetaErr_CMS2.obj")
    , els_etaSC_handle("floats_electronMaker_elsetaSC_CMS2.obj")
    , els_etaSCwidth_handle("floats_electronMaker_elsetaSCwidth_CMS2.obj")
    , els_fbrem_handle("floats_electronMaker_elsfbrem_CMS2.obj")
    , els_hOverE_handle("floats_electronMaker_elshOverE_CMS2.obj")
    , els_hcalDepth1OverEcal_handle("floats_electronMaker_elshcalDepth1OverEcal_CMS2.obj")
    , els_hcalDepth1TowerSumEt_handle("floats_electronMaker_elshcalDepth1TowerSumEt_CMS2.obj")
    , els_hcalDepth1TowerSumEt04_handle("floats_electronMaker_elshcalDepth1TowerSumEt04_CMS2.obj")
    , els_hcalDepth2OverEcal_handle("floats_electronMaker_elshcalDepth2OverEcal_CMS2.obj")
    , els_hcalDepth2TowerSumEt_handle("floats_electronMaker_elshcalDepth2TowerSumEt_CMS2.obj")
    , els_hcalDepth2TowerSumEt04_handle("floats_electronMaker_elshcalDepth2TowerSumEt04_CMS2.obj")
    , els_hcalIso_handle("floats_electronMaker_elshcalIso_CMS2.obj")
    , els_hcalIso04_handle("floats_electronMaker_elshcalIso04_CMS2.obj")
    , els_ip3d_handle("floats_electronMaker_elsip3d_CMS2.obj")
    , els_ip3derr_handle("floats_electronMaker_elsip3derr_CMS2.obj")
    , els_iso03_pf_handle("floats_electronMaker_elsiso03pf_CMS2.obj")
    , els_iso03_pf2012_ch_handle("floats_electronMaker_elsiso03pf2012ch_CMS2.obj")
    , els_iso03_pf2012_em_handle("floats_electronMaker_elsiso03pf2012em_CMS2.obj")
    , els_iso03_pf2012ext_ch_handle("floats_electronMaker_elsiso03pf2012extch_CMS2.obj")
    , els_iso03_pf2012ext_em_handle("floats_electronMaker_elsiso03pf2012extem_CMS2.obj")
    , els_iso03_pf2012ext_nh_handle("floats_electronMaker_elsiso03pf2012extnh_CMS2.obj")
    , els_iso03_pf2012_nh_handle("floats_electronMaker_elsiso03pf2012nh_CMS2.obj")
    , els_iso03_pf_ch_handle("floats_electronMaker_elsiso03pfch_CMS2.obj")
    , els_iso03_pf_gamma05_handle("floats_electronMaker_elsiso03pfgamma05_CMS2.obj")
    , els_iso03_pf_nhad05_handle("floats_electronMaker_elsiso03pfnhad05_CMS2.obj")
    , els_iso04_pf_handle("floats_electronMaker_elsiso04pf_CMS2.obj")
    , els_iso04_pf2012_ch_handle("floats_electronMaker_elsiso04pf2012ch_CMS2.obj")
    , els_iso04_pf2012_em_handle("floats_electronMaker_elsiso04pf2012em_CMS2.obj")
    , els_iso04_pf2012ext_ch_handle("floats_electronMaker_elsiso04pf2012extch_CMS2.obj")
    , els_iso04_pf2012ext_em_handle("floats_electronMaker_elsiso04pf2012extem_CMS2.obj")
    , els_iso04_pf2012ext_nh_handle("floats_electronMaker_elsiso04pf2012extnh_CMS2.obj")
    , els_iso04_pf2012_nh_handle("floats_electronMaker_elsiso04pf2012nh_CMS2.obj")
    , els_iso04_pf_ch_handle("floats_electronMaker_elsiso04pfch_CMS2.obj")
    , els_iso04_pf_gamma05_handle("floats_electronMaker_elsiso04pfgamma05_CMS2.obj")
    , els_iso04_pf_nhad05_handle("floats_electronMaker_elsiso04pfnhad05_CMS2.obj")
    , els_layer1_charge_handle("floats_electronMaker_elslayer1charge_CMS2.obj")
    , els_lh_handle("floats_electronMaker_elslh_CMS2.obj")
    , els_mva_handle("floats_electronMaker_elsmva_CMS2.obj")
    , els_ndof_handle("floats_electronMaker_elsndof_CMS2.obj")
    , els_pfChargedHadronIso_handle("floats_electronMaker_elspfChargedHadronIso_CMS2.obj")
    , els_pfNeutralHadronIso_handle("floats_electronMaker_elspfNeutralHadronIso_CMS2.obj")
    , els_pfPhotonIso_handle("floats_electronMaker_elspfPhotonIso_CMS2.obj")
    , els_phiErr_handle("floats_electronMaker_elsphiErr_CMS2.obj")
    , els_phiSC_handle("floats_electronMaker_elsphiSC_CMS2.obj")
    , els_phiSCwidth_handle("floats_electronMaker_elsphiSCwidth_CMS2.obj")
    , els_ptErr_handle("floats_electronMaker_elsptErr_CMS2.obj")
    , els_r9_handle("floats_electronMaker_elsr9_CMS2.obj")
    , els_sigmaEtaEta_handle("floats_electronMaker_elssigmaEtaEta_CMS2.obj")
    , els_sigmaIEtaIEta_handle("floats_electronMaker_elssigmaIEtaIEta_CMS2.obj")
    , els_sigmaIEtaIEtaSC_handle("floats_electronMaker_elssigmaIEtaIEtaSC_CMS2.obj")
    , els_sigmaIEtaIPhi_handle("floats_electronMaker_elssigmaIEtaIPhi_CMS2.obj")
    , els_sigmaIPhiIPhi_handle("floats_electronMaker_elssigmaIPhiIPhi_CMS2.obj")
    , els_sigmaIPhiIPhiSC_handle("floats_electronMaker_elssigmaIPhiIPhiSC_CMS2.obj")
    , els_sigmaIphiIphi_handle("floats_electronMaker_elssigmaIphiIphi_CMS2.obj")
    , els_sigmaPhiPhi_handle("floats_electronMaker_elssigmaPhiPhi_CMS2.obj")
    , els_tkIso_handle("floats_electronMaker_elstkIso_CMS2.obj")
    , els_tkIso04_handle("floats_electronMaker_elstkIso04_CMS2.obj")
    , els_trackMomentumError_handle("floats_electronMaker_elstrackMomentumError_CMS2.obj")
    , els_trkdr_handle("floats_electronMaker_elstrkdr_CMS2.obj")
    , els_trkshFrac_handle("floats_electronMaker_elstrkshFrac_CMS2.obj")
    , els_z0_handle("floats_electronMaker_elsz0_CMS2.obj")
    , els_z0Err_handle("floats_electronMaker_elsz0Err_CMS2.obj")
    , els_z0corr_handle("floats_electronMaker_elsz0corr_CMS2.obj")
    , gsftrks_chi2_handle("floats_gsfTrackMaker_gsftrkschi2_CMS2.obj")
    , gsftrks_d0_handle("floats_gsfTrackMaker_gsftrksd0_CMS2.obj")
    , gsftrks_d0Err_handle("floats_gsfTrackMaker_gsftrksd0Err_CMS2.obj")
    , gsftrks_d0corr_handle("floats_gsfTrackMaker_gsftrksd0corr_CMS2.obj")
    , gsftrks_d0corrPhi_handle("floats_gsfTrackMaker_gsftrksd0corrPhi_CMS2.obj")
    , gsftrks_d0phiCov_handle("floats_gsfTrackMaker_gsftrksd0phiCov_CMS2.obj")
    , gsftrks_etaErr_handle("floats_gsfTrackMaker_gsftrksetaErr_CMS2.obj")
    , gsftrks_layer1_charge_handle("floats_gsfTrackMaker_gsftrkslayer1charge_CMS2.obj")
    , gsftrks_ndof_handle("floats_gsfTrackMaker_gsftrksndof_CMS2.obj")
    , gsftrks_phiErr_handle("floats_gsfTrackMaker_gsftrksphiErr_CMS2.obj")
    , gsftrks_ptErr_handle("floats_gsfTrackMaker_gsftrksptErr_CMS2.obj")
    , gsftrks_z0_handle("floats_gsfTrackMaker_gsftrksz0_CMS2.obj")
    , gsftrks_z0Err_handle("floats_gsfTrackMaker_gsftrksz0Err_CMS2.obj")
    , gsftrks_z0corr_handle("floats_gsfTrackMaker_gsftrksz0corr_CMS2.obj")
    , hyp_Ht_handle("floats_hypDilepMaker_hypHt_CMS2.obj")
    , hyp_dPhi_nJet_metMuonJESCorr_handle("floats_hypDilepMaker_hypdPhinJetmetMuonJESCorr_CMS2.obj")
    , hyp_dPhi_nJet_muCorrMet_handle("floats_hypDilepMaker_hypdPhinJetmuCorrMet_CMS2.obj")
    , hyp_dPhi_nJet_tcMet_handle("floats_hypDilepMaker_hypdPhinJettcMet_CMS2.obj")
    , hyp_dPhi_nJet_unCorrMet_handle("floats_hypDilepMaker_hypdPhinJetunCorrMet_CMS2.obj")
    , hyp_ll_chi2_handle("floats_hypDilepMaker_hypllchi2_CMS2.obj")
    , hyp_ll_d0_handle("floats_hypDilepMaker_hyplld0_CMS2.obj")
    , hyp_ll_d0Err_handle("floats_hypDilepMaker_hyplld0Err_CMS2.obj")
    , hyp_ll_d0corr_handle("floats_hypDilepMaker_hyplld0corr_CMS2.obj")
    , hyp_ll_dPhi_metMuonJESCorr_handle("floats_hypDilepMaker_hyplldPhimetMuonJESCorr_CMS2.obj")
    , hyp_ll_dPhi_muCorrMet_handle("floats_hypDilepMaker_hyplldPhimuCorrMet_CMS2.obj")
    , hyp_ll_dPhi_tcMet_handle("floats_hypDilepMaker_hyplldPhitcMet_CMS2.obj")
    , hyp_ll_dPhi_unCorrMet_handle("floats_hypDilepMaker_hyplldPhiunCorrMet_CMS2.obj")
    , hyp_ll_etaErr_handle("floats_hypDilepMaker_hyplletaErr_CMS2.obj")
    , hyp_ll_ndof_handle("floats_hypDilepMaker_hypllndof_CMS2.obj")
    , hyp_ll_phiErr_handle("floats_hypDilepMaker_hypllphiErr_CMS2.obj")
    , hyp_ll_ptErr_handle("floats_hypDilepMaker_hypllptErr_CMS2.obj")
    , hyp_ll_z0_handle("floats_hypDilepMaker_hypllz0_CMS2.obj")
    , hyp_ll_z0Err_handle("floats_hypDilepMaker_hypllz0Err_CMS2.obj")
    , hyp_ll_z0corr_handle("floats_hypDilepMaker_hypllz0corr_CMS2.obj")
    , hyp_lt_chi2_handle("floats_hypDilepMaker_hypltchi2_CMS2.obj")
    , hyp_lt_d0_handle("floats_hypDilepMaker_hypltd0_CMS2.obj")
    , hyp_lt_d0Err_handle("floats_hypDilepMaker_hypltd0Err_CMS2.obj")
    , hyp_lt_d0corr_handle("floats_hypDilepMaker_hypltd0corr_CMS2.obj")
    , hyp_lt_dPhi_metMuonJESCorr_handle("floats_hypDilepMaker_hypltdPhimetMuonJESCorr_CMS2.obj")
    , hyp_lt_dPhi_muCorrMet_handle("floats_hypDilepMaker_hypltdPhimuCorrMet_CMS2.obj")
    , hyp_lt_dPhi_tcMet_handle("floats_hypDilepMaker_hypltdPhitcMet_CMS2.obj")
    , hyp_lt_dPhi_unCorrMet_handle("floats_hypDilepMaker_hypltdPhiunCorrMet_CMS2.obj")
    , hyp_lt_etaErr_handle("floats_hypDilepMaker_hypltetaErr_CMS2.obj")
    , hyp_lt_ndof_handle("floats_hypDilepMaker_hypltndof_CMS2.obj")
    , hyp_lt_phiErr_handle("floats_hypDilepMaker_hypltphiErr_CMS2.obj")
    , hyp_lt_ptErr_handle("floats_hypDilepMaker_hypltptErr_CMS2.obj")
    , hyp_lt_z0_handle("floats_hypDilepMaker_hypltz0_CMS2.obj")
    , hyp_lt_z0Err_handle("floats_hypDilepMaker_hypltz0Err_CMS2.obj")
    , hyp_lt_z0corr_handle("floats_hypDilepMaker_hypltz0corr_CMS2.obj")
    , hyp_mt2_metMuonJESCorr_handle("floats_hypDilepMaker_hypmt2metMuonJESCorr_CMS2.obj")
    , hyp_mt2_muCorrMet_handle("floats_hypDilepMaker_hypmt2muCorrMet_CMS2.obj")
    , hyp_mt2_tcMet_handle("floats_hypDilepMaker_hypmt2tcMet_CMS2.obj")
    , hyp_sumJetPt_handle("floats_hypDilepMaker_hypsumJetPt_CMS2.obj")
    , hyp_FVFit_chi2ndf_handle("floats_hypDilepVertexMaker_hypFVFitchi2ndf_CMS2.obj")
    , hyp_FVFit_prob_handle("floats_hypDilepVertexMaker_hypFVFitprob_CMS2.obj")
    , hyp_FVFit_v4cxx_handle("floats_hypDilepVertexMaker_hypFVFitv4cxx_CMS2.obj")
    , hyp_FVFit_v4cxy_handle("floats_hypDilepVertexMaker_hypFVFitv4cxy_CMS2.obj")
    , hyp_FVFit_v4cyy_handle("floats_hypDilepVertexMaker_hypFVFitv4cyy_CMS2.obj")
    , hyp_FVFit_v4czx_handle("floats_hypDilepVertexMaker_hypFVFitv4czx_CMS2.obj")
    , hyp_FVFit_v4czy_handle("floats_hypDilepVertexMaker_hypFVFitv4czy_CMS2.obj")
    , hyp_FVFit_v4czz_handle("floats_hypDilepVertexMaker_hypFVFitv4czz_CMS2.obj")
    , jets_approximatefHPD_handle("floats_jetMaker_jetsapproximatefHPD_CMS2.obj")
    , jets_approximatefRBX_handle("floats_jetMaker_jetsapproximatefRBX_CMS2.obj")
    , jets_cor_handle("floats_jetMaker_jetscor_CMS2.obj")
    , jets_corL1FastL2L3_handle("floats_jetMaker_jetscorL1FastL2L3_CMS2.obj")
    , jets_corL1L2L3_handle("floats_jetMaker_jetscorL1L2L3_CMS2.obj")
    , jets_emFrac_handle("floats_jetMaker_jetsemFrac_CMS2.obj")
    , jets_fHPD_handle("floats_jetMaker_jetsfHPD_CMS2.obj")
    , jets_fRBX_handle("floats_jetMaker_jetsfRBX_CMS2.obj")
    , jets_fSubDetector1_handle("floats_jetMaker_jetsfSubDetector1_CMS2.obj")
    , jets_fSubDetector2_handle("floats_jetMaker_jetsfSubDetector2_CMS2.obj")
    , jets_fSubDetector3_handle("floats_jetMaker_jetsfSubDetector3_CMS2.obj")
    , jets_fSubDetector4_handle("floats_jetMaker_jetsfSubDetector4_CMS2.obj")
    , jets_hitsInN90_handle("floats_jetMaker_jetshitsInN90_CMS2.obj")
    , jets_n90Hits_handle("floats_jetMaker_jetsn90Hits_CMS2.obj")
    , jets_nECALTowers_handle("floats_jetMaker_jetsnECALTowers_CMS2.obj")
    , jets_nHCALTowers_handle("floats_jetMaker_jetsnHCALTowers_CMS2.obj")
    , jets_restrictedEMF_handle("floats_jetMaker_jetsrestrictedEMF_CMS2.obj")
    , mus_met_deltax_handle("floats_metMaker_musmetdeltax_CMS2.obj")
    , mus_met_deltay_handle("floats_metMaker_musmetdeltay_CMS2.obj")
    , mus_eledr_handle("floats_muToElsAssMaker_museledr_CMS2.obj")
    , mus_jetdr_handle("floats_muToJetAssMaker_musjetdr_CMS2.obj")
    , mus_isoR03_chpf_radial_handle("floats_muonIsolationMaker_musisoR03chpfradial_CMS2.obj")
    , mus_isoR03_chpf_radialTight_handle("floats_muonIsolationMaker_musisoR03chpfradialTight_CMS2.obj")
    , mus_isoR03_empf_radial_handle("floats_muonIsolationMaker_musisoR03empfradial_CMS2.obj")
    , mus_isoR03_empf_radialTight_handle("floats_muonIsolationMaker_musisoR03empfradialTight_CMS2.obj")
    , mus_isoR03_nhpf_radial_handle("floats_muonIsolationMaker_musisoR03nhpfradial_CMS2.obj")
    , mus_isoR03_nhpf_radialTight_handle("floats_muonIsolationMaker_musisoR03nhpfradialTight_CMS2.obj")
    , mus_isoR03_pf_radial_handle("floats_muonIsolationMaker_musisoR03pfradial_CMS2.obj")
    , mus_isoR03_pf_radialTight_handle("floats_muonIsolationMaker_musisoR03pfradialTight_CMS2.obj")
    , mus_backToBackCompat_handle("floats_muonMaker_musbackToBackCompat_CMS2.obj")
    , mus_caloCompatibility_handle("floats_muonMaker_muscaloCompatibility_CMS2.obj")
    , mus_chi2_handle("floats_muonMaker_muschi2_CMS2.obj")
    , mus_chi2LocalMomentum_handle("floats_muonMaker_muschi2LocalMomentum_CMS2.obj")
    , mus_chi2LocalPosition_handle("floats_muonMaker_muschi2LocalPosition_CMS2.obj")
    , mus_cosmicCompat_handle("floats_muonMaker_muscosmicCompat_CMS2.obj")
    , mus_d0_handle("floats_muonMaker_musd0_CMS2.obj")
    , mus_d0Err_handle("floats_muonMaker_musd0Err_CMS2.obj")
    , mus_d0corr_handle("floats_muonMaker_musd0corr_CMS2.obj")
    , mus_e_em_handle("floats_muonMaker_museem_CMS2.obj")
    , mus_e_emS9_handle("floats_muonMaker_museemS9_CMS2.obj")
    , mus_e_had_handle("floats_muonMaker_musehad_CMS2.obj")
    , mus_e_hadS9_handle("floats_muonMaker_musehadS9_CMS2.obj")
    , mus_e_ho_handle("floats_muonMaker_museho_CMS2.obj")
    , mus_e_hoS9_handle("floats_muonMaker_musehoS9_CMS2.obj")
    , mus_etaErr_handle("floats_muonMaker_musetaErr_CMS2.obj")
    , mus_gfit_chi2_handle("floats_muonMaker_musgfitchi2_CMS2.obj")
    , mus_gfit_d0_handle("floats_muonMaker_musgfitd0_CMS2.obj")
    , mus_gfit_d0Err_handle("floats_muonMaker_musgfitd0Err_CMS2.obj")
    , mus_gfit_d0corr_handle("floats_muonMaker_musgfitd0corr_CMS2.obj")
    , mus_gfit_ndof_handle("floats_muonMaker_musgfitndof_CMS2.obj")
    , mus_gfit_qoverp_handle("floats_muonMaker_musgfitqoverp_CMS2.obj")
    , mus_gfit_qoverpError_handle("floats_muonMaker_musgfitqoverpError_CMS2.obj")
    , mus_gfit_z0_handle("floats_muonMaker_musgfitz0_CMS2.obj")
    , mus_gfit_z0Err_handle("floats_muonMaker_musgfitz0Err_CMS2.obj")
    , mus_gfit_z0corr_handle("floats_muonMaker_musgfitz0corr_CMS2.obj")
    , mus_glbKink_handle("floats_muonMaker_musglbKink_CMS2.obj")
    , mus_glbTrackProbability_handle("floats_muonMaker_musglbTrackProbability_CMS2.obj")
    , mus_globalDeltaEtaPhi_handle("floats_muonMaker_musglobalDeltaEtaPhi_CMS2.obj")
    , mus_ip3d_handle("floats_muonMaker_musip3d_CMS2.obj")
    , mus_ip3derr_handle("floats_muonMaker_musip3derr_CMS2.obj")
    , mus_iso03_emEt_handle("floats_muonMaker_musiso03emEt_CMS2.obj")
    , mus_iso03_hadEt_handle("floats_muonMaker_musiso03hadEt_CMS2.obj")
    , mus_iso03_hoEt_handle("floats_muonMaker_musiso03hoEt_CMS2.obj")
    , mus_iso03_pf_handle("floats_muonMaker_musiso03pf_CMS2.obj")
    , mus_iso03_sumPt_handle("floats_muonMaker_musiso03sumPt_CMS2.obj")
    , mus_iso04_pf_handle("floats_muonMaker_musiso04pf_CMS2.obj")
    , mus_iso05_emEt_handle("floats_muonMaker_musiso05emEt_CMS2.obj")
    , mus_iso05_hadEt_handle("floats_muonMaker_musiso05hadEt_CMS2.obj")
    , mus_iso05_hoEt_handle("floats_muonMaker_musiso05hoEt_CMS2.obj")
    , mus_iso05_sumPt_handle("floats_muonMaker_musiso05sumPt_CMS2.obj")
    , mus_isoR03_pf_ChargedHadronPt_handle("floats_muonMaker_musisoR03pfChargedHadronPt_CMS2.obj")
    , mus_isoR03_pf_ChargedParticlePt_handle("floats_muonMaker_musisoR03pfChargedParticlePt_CMS2.obj")
    , mus_isoR03_pf_NeutralHadronEt_handle("floats_muonMaker_musisoR03pfNeutralHadronEt_CMS2.obj")
    , mus_isoR03_pf_NeutralHadronEtHighThreshold_handle("floats_muonMaker_musisoR03pfNeutralHadronEtHighThreshold_CMS2.obj")
    , mus_isoR03_pf_PUPt_handle("floats_muonMaker_musisoR03pfPUPt_CMS2.obj")
    , mus_isoR03_pf_PhotonEt_handle("floats_muonMaker_musisoR03pfPhotonEt_CMS2.obj")
    , mus_isoR03_pf_PhotonEtHighThreshold_handle("floats_muonMaker_musisoR03pfPhotonEtHighThreshold_CMS2.obj")
    , mus_isoR04_pf_ChargedHadronPt_handle("floats_muonMaker_musisoR04pfChargedHadronPt_CMS2.obj")
    , mus_isoR04_pf_ChargedParticlePt_handle("floats_muonMaker_musisoR04pfChargedParticlePt_CMS2.obj")
    , mus_isoR04_pf_NeutralHadronEt_handle("floats_muonMaker_musisoR04pfNeutralHadronEt_CMS2.obj")
    , mus_isoR04_pf_NeutralHadronEtHighThreshold_handle("floats_muonMaker_musisoR04pfNeutralHadronEtHighThreshold_CMS2.obj")
    , mus_isoR04_pf_PUPt_handle("floats_muonMaker_musisoR04pfPUPt_CMS2.obj")
    , mus_isoR04_pf_PhotonEt_handle("floats_muonMaker_musisoR04pfPhotonEt_CMS2.obj")
    , mus_isoR04_pf_PhotonEtHighThreshold_handle("floats_muonMaker_musisoR04pfPhotonEtHighThreshold_CMS2.obj")
    , mus_iso_ecalvetoDep_handle("floats_muonMaker_musisoecalvetoDep_CMS2.obj")
    , mus_iso_hcalvetoDep_handle("floats_muonMaker_musisohcalvetoDep_CMS2.obj")
    , mus_iso_hovetoDep_handle("floats_muonMaker_musisohovetoDep_CMS2.obj")
    , mus_iso_trckvetoDep_handle("floats_muonMaker_musisotrckvetoDep_CMS2.obj")
    , mus_localDistance_handle("floats_muonMaker_muslocalDistance_CMS2.obj")
    , mus_ndof_handle("floats_muonMaker_musndof_CMS2.obj")
    , mus_overlapCompat_handle("floats_muonMaker_musoverlapCompat_CMS2.obj")
    , mus_pfdeltaP_handle("floats_muonMaker_muspfdeltaP_CMS2.obj")
    , mus_pfecalE_handle("floats_muonMaker_muspfecalE_CMS2.obj")
    , mus_pfhcalE_handle("floats_muonMaker_muspfhcalE_CMS2.obj")
    , mus_pfmva_emu_handle("floats_muonMaker_muspfmvaemu_CMS2.obj")
    , mus_pfmva_epi_handle("floats_muonMaker_muspfmvaepi_CMS2.obj")
    , mus_pfmva_nothing_gamma_handle("floats_muonMaker_muspfmvanothinggamma_CMS2.obj")
    , mus_pfmva_nothing_nh_handle("floats_muonMaker_muspfmvanothingnh_CMS2.obj")
    , mus_pfmva_pimu_handle("floats_muonMaker_muspfmvapimu_CMS2.obj")
    , mus_pfpS1E_handle("floats_muonMaker_muspfpS1E_CMS2.obj")
    , mus_pfpS2E_handle("floats_muonMaker_muspfpS2E_CMS2.obj")
    , mus_pfrawEcalE_handle("floats_muonMaker_muspfrawEcalE_CMS2.obj")
    , mus_pfrawHcalE_handle("floats_muonMaker_muspfrawHcalE_CMS2.obj")
    , mus_phiErr_handle("floats_muonMaker_musphiErr_CMS2.obj")
    , mus_ptErr_handle("floats_muonMaker_musptErr_CMS2.obj")
    , mus_qoverp_handle("floats_muonMaker_musqoverp_CMS2.obj")
    , mus_qoverpError_handle("floats_muonMaker_musqoverpError_CMS2.obj")
    , mus_segmCompatibility_handle("floats_muonMaker_mussegmCompatibility_CMS2.obj")
    , mus_staRelChi2_handle("floats_muonMaker_musstaRelChi2_CMS2.obj")
    , mus_sta_chi2_handle("floats_muonMaker_musstachi2_CMS2.obj")
    , mus_sta_d0_handle("floats_muonMaker_musstad0_CMS2.obj")
    , mus_sta_d0Err_handle("floats_muonMaker_musstad0Err_CMS2.obj")
    , mus_sta_d0corr_handle("floats_muonMaker_musstad0corr_CMS2.obj")
    , mus_sta_ndof_handle("floats_muonMaker_musstandof_CMS2.obj")
    , mus_sta_qoverp_handle("floats_muonMaker_musstaqoverp_CMS2.obj")
    , mus_sta_qoverpError_handle("floats_muonMaker_musstaqoverpError_CMS2.obj")
    , mus_sta_z0_handle("floats_muonMaker_musstaz0_CMS2.obj")
    , mus_sta_z0Err_handle("floats_muonMaker_musstaz0Err_CMS2.obj")
    , mus_sta_z0corr_handle("floats_muonMaker_musstaz0corr_CMS2.obj")
    , mus_timeAtIpInOut_handle("floats_muonMaker_mustimeAtIpInOut_CMS2.obj")
    , mus_timeAtIpInOutErr_handle("floats_muonMaker_mustimeAtIpInOutErr_CMS2.obj")
    , mus_timeAtIpOutIn_handle("floats_muonMaker_mustimeAtIpOutIn_CMS2.obj")
    , mus_timeAtIpOutInErr_handle("floats_muonMaker_mustimeAtIpOutInErr_CMS2.obj")
    , mus_timeCompat_handle("floats_muonMaker_mustimeCompat_CMS2.obj")
    , mus_trkKink_handle("floats_muonMaker_mustrkKink_CMS2.obj")
    , mus_trkRelChi2_handle("floats_muonMaker_mustrkRelChi2_CMS2.obj")
    , mus_vertexCompat_handle("floats_muonMaker_musvertexCompat_CMS2.obj")
    , mus_vertexphi_handle("floats_muonMaker_musvertexphi_CMS2.obj")
    , mus_z0_handle("floats_muonMaker_musz0_CMS2.obj")
    , mus_z0Err_handle("floats_muonMaker_musz0Err_CMS2.obj")
    , mus_z0corr_handle("floats_muonMaker_musz0corr_CMS2.obj")
    , pfjets_mvavalue_handle("floats_mvaJetIdMaker_pfjetsmvavalue_CMS2.obj")
    , pfjets_full53xmva_beta_handle("floats_mvaJetIdMakerFull53x_pfjetsfull53xmvabeta_CMS2.obj")
    , pfjets_full53xmva_betaStar_handle("floats_mvaJetIdMakerFull53x_pfjetsfull53xmvabetaStar_CMS2.obj")
    , pfjets_full53xmva_d0_handle("floats_mvaJetIdMakerFull53x_pfjetsfull53xmvad0_CMS2.obj")
    , pfjets_full53xmva_dRMean_handle("floats_mvaJetIdMakerFull53x_pfjetsfull53xmvadRMean_CMS2.obj")
    , pfjets_full53xmva_dZ_handle("floats_mvaJetIdMakerFull53x_pfjetsfull53xmvadZ_CMS2.obj")
    , pfjets_full53xmva_frac01_handle("floats_mvaJetIdMakerFull53x_pfjetsfull53xmvafrac01_CMS2.obj")
    , pfjets_full53xmva_frac02_handle("floats_mvaJetIdMakerFull53x_pfjetsfull53xmvafrac02_CMS2.obj")
    , pfjets_full53xmva_frac03_handle("floats_mvaJetIdMakerFull53x_pfjetsfull53xmvafrac03_CMS2.obj")
    , pfjets_full53xmva_frac04_handle("floats_mvaJetIdMakerFull53x_pfjetsfull53xmvafrac04_CMS2.obj")
    , pfjets_full53xmva_frac05_handle("floats_mvaJetIdMakerFull53x_pfjetsfull53xmvafrac05_CMS2.obj")
    , pfjets_full53xmva_nCharged_handle("floats_mvaJetIdMakerFull53x_pfjetsfull53xmvanCharged_CMS2.obj")
    , pfjets_full53xmva_nNeutrals_handle("floats_mvaJetIdMakerFull53x_pfjetsfull53xmvanNeutrals_CMS2.obj")
    , pfjets_full53xmva_nvtx_handle("floats_mvaJetIdMakerFull53x_pfjetsfull53xmvanvtx_CMS2.obj")
    , pfjets_full53xmvavalue_handle("floats_mvaJetIdMakerFull53x_pfjetsfull53xmvavalue_CMS2.obj")
    , pfjets_full5xmvavalue_handle("floats_mvaJetIdMakerFull5x_pfjetsfull5xmvavalue_CMS2.obj")
    , trkjet_met_handle("floats_myTrkJetMetMaker_trkjetmet_CMS2.obj")
    , trkjet_metPhi_handle("floats_myTrkJetMetMaker_trkjetmetPhi_CMS2.obj")
    , trkjet_sumet_handle("floats_myTrkJetMetMaker_trkjetsumet_CMS2.obj")
    , trk_met_handle("floats_myTrkMetMaker_trkmet_CMS2.obj")
    , trk_metPhi_handle("floats_myTrkMetMaker_trkmetPhi_CMS2.obj")
    , trk_sumet_handle("floats_myTrkMetMaker_trksumet_CMS2.obj")
    , pfcands_deltaP_handle("floats_pfCandidateMaker_pfcandsdeltaP_CMS2.obj")
    , pfcands_ecalE_handle("floats_pfCandidateMaker_pfcandsecalE_CMS2.obj")
    , pfcands_hcalE_handle("floats_pfCandidateMaker_pfcandshcalE_CMS2.obj")
    , pfcands_mva_emu_handle("floats_pfCandidateMaker_pfcandsmvaemu_CMS2.obj")
    , pfcands_mva_epi_handle("floats_pfCandidateMaker_pfcandsmvaepi_CMS2.obj")
    , pfcands_mva_nothing_gamma_handle("floats_pfCandidateMaker_pfcandsmvanothinggamma_CMS2.obj")
    , pfcands_mva_nothing_nh_handle("floats_pfCandidateMaker_pfcandsmvanothingnh_CMS2.obj")
    , pfcands_mva_pimu_handle("floats_pfCandidateMaker_pfcandsmvapimu_CMS2.obj")
    , pfcands_pS1E_handle("floats_pfCandidateMaker_pfcandspS1E_CMS2.obj")
    , pfcands_pS2E_handle("floats_pfCandidateMaker_pfcandspS2E_CMS2.obj")
    , pfcands_rawEcalE_handle("floats_pfCandidateMaker_pfcandsrawEcalE_CMS2.obj")
    , pfcands_rawHcalE_handle("floats_pfCandidateMaker_pfcandsrawHcalE_CMS2.obj")
    , pfels_deltaP_handle("floats_pfElectronMaker_pfelsdeltaP_CMS2.obj")
    , pfels_ecalE_handle("floats_pfElectronMaker_pfelsecalE_CMS2.obj")
    , pfels_hcalE_handle("floats_pfElectronMaker_pfelshcalE_CMS2.obj")
    , pfels_iso04ChargedHadrons_handle("floats_pfElectronMaker_pfelsiso04ChargedHadrons_CMS2.obj")
    , pfels_iso04NeutralHadrons_handle("floats_pfElectronMaker_pfelsiso04NeutralHadrons_CMS2.obj")
    , pfels_iso04Photons_handle("floats_pfElectronMaker_pfelsiso04Photons_CMS2.obj")
    , pfels_isoChargedHadrons_handle("floats_pfElectronMaker_pfelsisoChargedHadrons_CMS2.obj")
    , pfels_isoNeutralHadrons_handle("floats_pfElectronMaker_pfelsisoNeutralHadrons_CMS2.obj")
    , pfels_isoPhotons_handle("floats_pfElectronMaker_pfelsisoPhotons_CMS2.obj")
    , pfels_mva_emu_handle("floats_pfElectronMaker_pfelsmvaemu_CMS2.obj")
    , pfels_mva_epi_handle("floats_pfElectronMaker_pfelsmvaepi_CMS2.obj")
    , pfels_mva_nothing_gamma_handle("floats_pfElectronMaker_pfelsmvanothinggamma_CMS2.obj")
    , pfels_mva_nothing_nh_handle("floats_pfElectronMaker_pfelsmvanothingnh_CMS2.obj")
    , pfels_mva_pimu_handle("floats_pfElectronMaker_pfelsmvapimu_CMS2.obj")
    , pfels_pS1E_handle("floats_pfElectronMaker_pfelspS1E_CMS2.obj")
    , pfels_pS2E_handle("floats_pfElectronMaker_pfelspS2E_CMS2.obj")
    , pfels_rawEcalE_handle("floats_pfElectronMaker_pfelsrawEcalE_CMS2.obj")
    , pfels_rawHcalE_handle("floats_pfElectronMaker_pfelsrawHcalE_CMS2.obj")
    , pfjets_area_handle("floats_pfJetMaker_pfjetsarea_CMS2.obj")
    , pfjets_chargedEmE_handle("floats_pfJetMaker_pfjetschargedEmE_CMS2.obj")
    , pfjets_chargedHadronE_handle("floats_pfJetMaker_pfjetschargedHadronE_CMS2.obj")
    , pfjets_cor_handle("floats_pfJetMaker_pfjetscor_CMS2.obj")
    , pfjets_corL1Fast_handle("floats_pfJetMaker_pfjetscorL1Fast_CMS2.obj")
    , pfjets_corL1FastL2L3_handle("floats_pfJetMaker_pfjetscorL1FastL2L3_CMS2.obj")
    , pfjets_corL1FastL2L3residual_handle("floats_pfJetMaker_pfjetscorL1FastL2L3residual_CMS2.obj")
    , pfjets_corL1L2L3_handle("floats_pfJetMaker_pfjetscorL1L2L3_CMS2.obj")
    , pfjets_electronE_handle("floats_pfJetMaker_pfjetselectronE_CMS2.obj")
    , pfjets_hfEmE_handle("floats_pfJetMaker_pfjetshfEmE_CMS2.obj")
    , pfjets_hfHadronE_handle("floats_pfJetMaker_pfjetshfHadronE_CMS2.obj")
    , pfjets_muonE_handle("floats_pfJetMaker_pfjetsmuonE_CMS2.obj")
    , pfjets_neutralEmE_handle("floats_pfJetMaker_pfjetsneutralEmE_CMS2.obj")
    , pfjets_neutralHadronE_handle("floats_pfJetMaker_pfjetsneutralHadronE_CMS2.obj")
    , pfjets_photonE_handle("floats_pfJetMaker_pfjetsphotonE_CMS2.obj")
    , pfmus_deltaP_handle("floats_pfMuonMaker_pfmusdeltaP_CMS2.obj")
    , pfmus_ecalE_handle("floats_pfMuonMaker_pfmusecalE_CMS2.obj")
    , pfmus_hcalE_handle("floats_pfMuonMaker_pfmushcalE_CMS2.obj")
    , pfmus_iso04ChargedHadrons_handle("floats_pfMuonMaker_pfmusiso04ChargedHadrons_CMS2.obj")
    , pfmus_iso04NeutralHadrons_handle("floats_pfMuonMaker_pfmusiso04NeutralHadrons_CMS2.obj")
    , pfmus_iso04Photons_handle("floats_pfMuonMaker_pfmusiso04Photons_CMS2.obj")
    , pfmus_isoChargedHadrons_handle("floats_pfMuonMaker_pfmusisoChargedHadrons_CMS2.obj")
    , pfmus_isoNeutralHadrons_handle("floats_pfMuonMaker_pfmusisoNeutralHadrons_CMS2.obj")
    , pfmus_isoPhotons_handle("floats_pfMuonMaker_pfmusisoPhotons_CMS2.obj")
    , pfmus_mva_emu_handle("floats_pfMuonMaker_pfmusmvaemu_CMS2.obj")
    , pfmus_mva_epi_handle("floats_pfMuonMaker_pfmusmvaepi_CMS2.obj")
    , pfmus_mva_nothing_gamma_handle("floats_pfMuonMaker_pfmusmvanothinggamma_CMS2.obj")
    , pfmus_mva_nothing_nh_handle("floats_pfMuonMaker_pfmusmvanothingnh_CMS2.obj")
    , pfmus_mva_pimu_handle("floats_pfMuonMaker_pfmusmvapimu_CMS2.obj")
    , pfmus_pS1E_handle("floats_pfMuonMaker_pfmuspS1E_CMS2.obj")
    , pfmus_pS2E_handle("floats_pfMuonMaker_pfmuspS2E_CMS2.obj")
    , pfmus_rawEcalE_handle("floats_pfMuonMaker_pfmusrawEcalE_CMS2.obj")
    , pfmus_rawHcalE_handle("floats_pfMuonMaker_pfmusrawHcalE_CMS2.obj")
    , taus_pf_againstElectronDeadECAL_handle("floats_pftauMaker_tauspfagainstElectronDeadECAL_CMS2.obj")
    , taus_pf_againstElectronLoose_handle("floats_pftauMaker_tauspfagainstElectronLoose_CMS2.obj")
    , taus_pf_againstElectronLooseMVA2_handle("floats_pftauMaker_tauspfagainstElectronLooseMVA2_CMS2.obj")
    , taus_pf_againstElectronLooseMVA3_handle("floats_pftauMaker_tauspfagainstElectronLooseMVA3_CMS2.obj")
    , taus_pf_againstElectronMVA_handle("floats_pftauMaker_tauspfagainstElectronMVA_CMS2.obj")
    , taus_pf_againstElectronMVA2category_handle("floats_pftauMaker_tauspfagainstElectronMVA2category_CMS2.obj")
    , taus_pf_againstElectronMVA2raw_handle("floats_pftauMaker_tauspfagainstElectronMVA2raw_CMS2.obj")
    , taus_pf_againstElectronMVA3category_handle("floats_pftauMaker_tauspfagainstElectronMVA3category_CMS2.obj")
    , taus_pf_againstElectronMVA3raw_handle("floats_pftauMaker_tauspfagainstElectronMVA3raw_CMS2.obj")
    , taus_pf_againstElectronMedium_handle("floats_pftauMaker_tauspfagainstElectronMedium_CMS2.obj")
    , taus_pf_againstElectronMediumMVA2_handle("floats_pftauMaker_tauspfagainstElectronMediumMVA2_CMS2.obj")
    , taus_pf_againstElectronMediumMVA3_handle("floats_pftauMaker_tauspfagainstElectronMediumMVA3_CMS2.obj")
    , taus_pf_againstElectronTight_handle("floats_pftauMaker_tauspfagainstElectronTight_CMS2.obj")
    , taus_pf_againstElectronTightMVA2_handle("floats_pftauMaker_tauspfagainstElectronTightMVA2_CMS2.obj")
    , taus_pf_againstElectronTightMVA3_handle("floats_pftauMaker_tauspfagainstElectronTightMVA3_CMS2.obj")
    , taus_pf_againstElectronVLooseMVA2_handle("floats_pftauMaker_tauspfagainstElectronVLooseMVA2_CMS2.obj")
    , taus_pf_againstElectronVTightMVA3_handle("floats_pftauMaker_tauspfagainstElectronVTightMVA3_CMS2.obj")
    , taus_pf_againstMuonLoose_handle("floats_pftauMaker_tauspfagainstMuonLoose_CMS2.obj")
    , taus_pf_againstMuonLoose2_handle("floats_pftauMaker_tauspfagainstMuonLoose2_CMS2.obj")
    , taus_pf_againstMuonMedium_handle("floats_pftauMaker_tauspfagainstMuonMedium_CMS2.obj")
    , taus_pf_againstMuonMedium2_handle("floats_pftauMaker_tauspfagainstMuonMedium2_CMS2.obj")
    , taus_pf_againstMuonTight_handle("floats_pftauMaker_tauspfagainstMuonTight_CMS2.obj")
    , taus_pf_againstMuonTight2_handle("floats_pftauMaker_tauspfagainstMuonTight2_CMS2.obj")
    , taus_pf_byCombinedIsolationDeltaBetaCorrRaw_handle("floats_pftauMaker_tauspfbyCombinedIsolationDeltaBetaCorrRaw_CMS2.obj")
    , taus_pf_byCombinedIsolationDeltaBetaCorrRaw3Hits_handle("floats_pftauMaker_tauspfbyCombinedIsolationDeltaBetaCorrRaw3Hits_CMS2.obj")
    , taus_pf_byDecayModeFinding_handle("floats_pftauMaker_tauspfbyDecayModeFinding_CMS2.obj")
    , taus_pf_byIsolationMVA2raw_handle("floats_pftauMaker_tauspfbyIsolationMVA2raw_CMS2.obj")
    , taus_pf_byIsolationMVAraw_handle("floats_pftauMaker_tauspfbyIsolationMVAraw_CMS2.obj")
    , taus_pf_byLooseCombinedIsolationDeltaBetaCorr_handle("floats_pftauMaker_tauspfbyLooseCombinedIsolationDeltaBetaCorr_CMS2.obj")
    , taus_pf_byLooseCombinedIsolationDeltaBetaCorr3Hits_handle("floats_pftauMaker_tauspfbyLooseCombinedIsolationDeltaBetaCorr3Hits_CMS2.obj")
    , taus_pf_byLooseIsolationMVA_handle("floats_pftauMaker_tauspfbyLooseIsolationMVA_CMS2.obj")
    , taus_pf_byLooseIsolationMVA2_handle("floats_pftauMaker_tauspfbyLooseIsolationMVA2_CMS2.obj")
    , taus_pf_byMediumCombinedIsolationDeltaBetaCorr_handle("floats_pftauMaker_tauspfbyMediumCombinedIsolationDeltaBetaCorr_CMS2.obj")
    , taus_pf_byMediumCombinedIsolationDeltaBetaCorr3Hits_handle("floats_pftauMaker_tauspfbyMediumCombinedIsolationDeltaBetaCorr3Hits_CMS2.obj")
    , taus_pf_byMediumIsolationMVA_handle("floats_pftauMaker_tauspfbyMediumIsolationMVA_CMS2.obj")
    , taus_pf_byMediumIsolationMVA2_handle("floats_pftauMaker_tauspfbyMediumIsolationMVA2_CMS2.obj")
    , taus_pf_byTightCombinedIsolationDeltaBetaCorr_handle("floats_pftauMaker_tauspfbyTightCombinedIsolationDeltaBetaCorr_CMS2.obj")
    , taus_pf_byTightCombinedIsolationDeltaBetaCorr3Hits_handle("floats_pftauMaker_tauspfbyTightCombinedIsolationDeltaBetaCorr3Hits_CMS2.obj")
    , taus_pf_byTightIsolationMVA_handle("floats_pftauMaker_tauspfbyTightIsolationMVA_CMS2.obj")
    , taus_pf_byTightIsolationMVA2_handle("floats_pftauMaker_tauspfbyTightIsolationMVA2_CMS2.obj")
    , taus_pf_byVLooseCombinedIsolationDeltaBetaCorr_handle("floats_pftauMaker_tauspfbyVLooseCombinedIsolationDeltaBetaCorr_CMS2.obj")
    , photons_e1x5_handle("floats_photonMaker_photonse1x5_CMS2.obj")
    , photons_e2x5Max_handle("floats_photonMaker_photonse2x5Max_CMS2.obj")
    , photons_e3x3_handle("floats_photonMaker_photonse3x3_CMS2.obj")
    , photons_e5x5_handle("floats_photonMaker_photonse5x5_CMS2.obj")
    , photons_ecalIso03_handle("floats_photonMaker_photonsecalIso03_CMS2.obj")
    , photons_ecalIso04_handle("floats_photonMaker_photonsecalIso04_CMS2.obj")
    , photons_hOverE_handle("floats_photonMaker_photonshOverE_CMS2.obj")
    , photons_hcalDepth1TowerSumEtBcConeDR03_handle("floats_photonMaker_photonshcalDepth1TowerSumEtBcConeDR03_CMS2.obj")
    , photons_hcalDepth1TowerSumEtBcConeDR04_handle("floats_photonMaker_photonshcalDepth1TowerSumEtBcConeDR04_CMS2.obj")
    , photons_hcalDepth2TowerSumEtBcConeDR03_handle("floats_photonMaker_photonshcalDepth2TowerSumEtBcConeDR03_CMS2.obj")
    , photons_hcalDepth2TowerSumEtBcConeDR04_handle("floats_photonMaker_photonshcalDepth2TowerSumEtBcConeDR04_CMS2.obj")
    , photons_hcalIso03_handle("floats_photonMaker_photonshcalIso03_CMS2.obj")
    , photons_hcalIso04_handle("floats_photonMaker_photonshcalIso04_CMS2.obj")
    , photons_hcalTowerSumEtBcConeDR03_handle("floats_photonMaker_photonshcalTowerSumEtBcConeDR03_CMS2.obj")
    , photons_hcalTowerSumEtBcConeDR04_handle("floats_photonMaker_photonshcalTowerSumEtBcConeDR04_CMS2.obj")
    , photons_ntkIsoHollow03_handle("floats_photonMaker_photonsntkIsoHollow03_CMS2.obj")
    , photons_ntkIsoHollow04_handle("floats_photonMaker_photonsntkIsoHollow04_CMS2.obj")
    , photons_ntkIsoSolid03_handle("floats_photonMaker_photonsntkIsoSolid03_CMS2.obj")
    , photons_ntkIsoSolid04_handle("floats_photonMaker_photonsntkIsoSolid04_CMS2.obj")
    , photons_sigmaEtaEta_handle("floats_photonMaker_photonssigmaEtaEta_CMS2.obj")
    , photons_sigmaIEtaIEta_handle("floats_photonMaker_photonssigmaIEtaIEta_CMS2.obj")
    , photons_swissSeed_handle("floats_photonMaker_photonsswissSeed_CMS2.obj")
    , photons_tkIsoHollow03_handle("floats_photonMaker_photonstkIsoHollow03_CMS2.obj")
    , photons_tkIsoHollow04_handle("floats_photonMaker_photonstkIsoHollow04_CMS2.obj")
    , photons_tkIsoSolid03_handle("floats_photonMaker_photonstkIsoSolid03_CMS2.obj")
    , photons_tkIsoSolid04_handle("floats_photonMaker_photonstkIsoSolid04_CMS2.obj")
    , puInfo_trueNumInteractions_handle("floats_puSummaryInfoMaker_puInfotrueNumInteractions_CMS2.obj")
    , convs_chi2_handle("floats_recoConversionMaker_convschi2_CMS2.obj")
    , convs_dl_handle("floats_recoConversionMaker_convsdl_CMS2.obj")
    , convs_ndof_handle("floats_recoConversionMaker_convsndof_CMS2.obj")
    , sparm_values_handle("floats_sParmMaker_sparmvalues_CMS2.obj")
    , scs_clustersSize_handle("floats_scMaker_scsclustersSize_CMS2.obj")
    , scs_crystalsSize_handle("floats_scMaker_scscrystalsSize_CMS2.obj")
    , scs_e1x3_handle("floats_scMaker_scse1x3_CMS2.obj")
    , scs_e1x5_handle("floats_scMaker_scse1x5_CMS2.obj")
    , scs_e2nd_handle("floats_scMaker_scse2nd_CMS2.obj")
    , scs_e2x2_handle("floats_scMaker_scse2x2_CMS2.obj")
    , scs_e2x5Max_handle("floats_scMaker_scse2x5Max_CMS2.obj")
    , scs_e3x1_handle("floats_scMaker_scse3x1_CMS2.obj")
    , scs_e3x2_handle("floats_scMaker_scse3x2_CMS2.obj")
    , scs_e3x3_handle("floats_scMaker_scse3x3_CMS2.obj")
    , scs_e4x4_handle("floats_scMaker_scse4x4_CMS2.obj")
    , scs_e5x5_handle("floats_scMaker_scse5x5_CMS2.obj")
    , scs_eMax_handle("floats_scMaker_scseMax_CMS2.obj")
    , scs_eSeed_handle("floats_scMaker_scseSeed_CMS2.obj")
    , scs_energy_handle("floats_scMaker_scsenergy_CMS2.obj")
    , scs_eta_handle("floats_scMaker_scseta_CMS2.obj")
    , scs_hoe_handle("floats_scMaker_scshoe_CMS2.obj")
    , scs_laserCorMax_handle("floats_scMaker_scslaserCorMax_CMS2.obj")
    , scs_laserCorMean_handle("floats_scMaker_scslaserCorMean_CMS2.obj")
    , scs_laserCorSeed_handle("floats_scMaker_scslaserCorSeed_CMS2.obj")
    , scs_phi_handle("floats_scMaker_scsphi_CMS2.obj")
    , scs_preshowerEnergy_handle("floats_scMaker_scspreshowerEnergy_CMS2.obj")
    , scs_rawEnergy_handle("floats_scMaker_scsrawEnergy_CMS2.obj")
    , scs_sigmaEtaEta_handle("floats_scMaker_scssigmaEtaEta_CMS2.obj")
    , scs_sigmaEtaPhi_handle("floats_scMaker_scssigmaEtaPhi_CMS2.obj")
    , scs_sigmaIEtaIEta_handle("floats_scMaker_scssigmaIEtaIEta_CMS2.obj")
    , scs_sigmaIEtaIEtaSC_handle("floats_scMaker_scssigmaIEtaIEtaSC_CMS2.obj")
    , scs_sigmaIEtaIPhi_handle("floats_scMaker_scssigmaIEtaIPhi_CMS2.obj")
    , scs_sigmaIEtaIPhiSC_handle("floats_scMaker_scssigmaIEtaIPhiSC_CMS2.obj")
    , scs_sigmaIPhiIPhi_handle("floats_scMaker_scssigmaIPhiIPhi_CMS2.obj")
    , scs_sigmaIPhiIPhiSC_handle("floats_scMaker_scssigmaIPhiIPhiSC_CMS2.obj")
    , scs_sigmaPhiPhi_handle("floats_scMaker_scssigmaPhiPhi_CMS2.obj")
    , scs_timeSeed_handle("floats_scMaker_scstimeSeed_CMS2.obj")
    , svs_anglePV_handle("floats_secondaryVertexMaker_svsanglePV_CMS2.obj")
    , svs_chi2_handle("floats_secondaryVertexMaker_svschi2_CMS2.obj")
    , svs_dist3Dsig_handle("floats_secondaryVertexMaker_svsdist3Dsig_CMS2.obj")
    , svs_dist3Dval_handle("floats_secondaryVertexMaker_svsdist3Dval_CMS2.obj")
    , svs_distXYsig_handle("floats_secondaryVertexMaker_svsdistXYsig_CMS2.obj")
    , svs_distXYval_handle("floats_secondaryVertexMaker_svsdistXYval_CMS2.obj")
    , svs_ndof_handle("floats_secondaryVertexMaker_svsndof_CMS2.obj")
    , svs_prob_handle("floats_secondaryVertexMaker_svsprob_CMS2.obj")
    , svs_xError_handle("floats_secondaryVertexMaker_svsxError_CMS2.obj")
    , svs_yError_handle("floats_secondaryVertexMaker_svsyError_CMS2.obj")
    , svs_zError_handle("floats_secondaryVertexMaker_svszError_CMS2.obj")
    , mus_tcmet_deltax_handle("floats_tcmetMaker_mustcmetdeltax_CMS2.obj")
    , mus_tcmet_deltay_handle("floats_tcmetMaker_mustcmetdeltay_CMS2.obj")
    , pfcands_dzpv_handle("floats_trackIsolationMaker_pfcandsdzpv_CMS2.obj")
    , pfcands_trkiso_handle("floats_trackIsolationMaker_pfcandstrkiso_CMS2.obj")
    , trks_chi2_handle("floats_trackMaker_trkschi2_CMS2.obj")
    , trks_d0_handle("floats_trackMaker_trksd0_CMS2.obj")
    , trks_d0Err_handle("floats_trackMaker_trksd0Err_CMS2.obj")
    , trks_d0corr_handle("floats_trackMaker_trksd0corr_CMS2.obj")
    , trks_d0corrPhi_handle("floats_trackMaker_trksd0corrPhi_CMS2.obj")
    , trks_d0phiCov_handle("floats_trackMaker_trksd0phiCov_CMS2.obj")
    , trks_etaErr_handle("floats_trackMaker_trksetaErr_CMS2.obj")
    , trks_layer1_charge_handle("floats_trackMaker_trkslayer1charge_CMS2.obj")
    , trks_ndof_handle("floats_trackMaker_trksndof_CMS2.obj")
    , trks_phiErr_handle("floats_trackMaker_trksphiErr_CMS2.obj")
    , trks_ptErr_handle("floats_trackMaker_trksptErr_CMS2.obj")
    , trks_validFraction_handle("floats_trackMaker_trksvalidFraction_CMS2.obj")
    , trks_z0_handle("floats_trackMaker_trksz0_CMS2.obj")
    , trks_z0Err_handle("floats_trackMaker_trksz0Err_CMS2.obj")
    , trks_z0corr_handle("floats_trackMaker_trksz0corr_CMS2.obj")
    , trkjets_cor_handle("floats_trkJetMaker_trkjetscor_CMS2.obj")
    , trks_d0Errvtx_handle("floats_trkToVtxAssMaker_trksd0Errvtx_CMS2.obj")
    , trks_d0vtx_handle("floats_trkToVtxAssMaker_trksd0vtx_CMS2.obj")
    , vtxs_chi2_handle("floats_vertexMaker_vtxschi2_CMS2.obj")
    , vtxs_ndof_handle("floats_vertexMaker_vtxsndof_CMS2.obj")
    , vtxs_sumpt_handle("floats_vertexMaker_vtxssumpt_CMS2.obj")
    , vtxs_xError_handle("floats_vertexMaker_vtxsxError_CMS2.obj")
    , vtxs_yError_handle("floats_vertexMaker_vtxsyError_CMS2.obj")
    , vtxs_zError_handle("floats_vertexMaker_vtxszError_CMS2.obj")
    , bsvtxs_chi2_handle("floats_vertexMakerWithBS_bsvtxschi2_CMS2.obj")
    , bsvtxs_ndof_handle("floats_vertexMakerWithBS_bsvtxsndof_CMS2.obj")
    , bsvtxs_sumpt_handle("floats_vertexMakerWithBS_bsvtxssumpt_CMS2.obj")
    , bsvtxs_xError_handle("floats_vertexMakerWithBS_bsvtxsxError_CMS2.obj")
    , bsvtxs_yError_handle("floats_vertexMakerWithBS_bsvtxsyError_CMS2.obj")
    , bsvtxs_zError_handle("floats_vertexMakerWithBS_bsvtxszError_CMS2.obj")
    , els_convs_dcot_handle("floatss_electronMaker_elsconvsdcot_CMS2.obj")
    , els_convs_dist_handle("floatss_electronMaker_elsconvsdist_CMS2.obj")
    , els_convs_radius_handle("floatss_electronMaker_elsconvsradius_CMS2.obj")
    , mus_stationShowerDeltaR_handle("floatss_muonMaker_musstationShowerDeltaR_CMS2.obj")
    , mus_stationShowerSizeT_handle("floatss_muonMaker_musstationShowerSizeT_CMS2.obj")
    , puInfo_instLumi_handle("floatss_puSummaryInfoMaker_puInfoinstLumi_CMS2.obj")
    , puInfo_sump_highpt_handle("floatss_puSummaryInfoMaker_puInfosumpthighpt_CMS2.obj")
    , puInfo_sumpt_lowpt_handle("floatss_puSummaryInfoMaker_puInfosumptlowpt_CMS2.obj")
    , puInfo_zpositions_handle("floatss_puSummaryInfoMaker_puInfozpositions_CMS2.obj")
    , vtxs_covMatrix_handle("floatss_vertexMaker_vtxscovMatrix_CMS2.obj")
    , bsvtxs_covMatrix_handle("floatss_vertexMakerWithBS_bsvtxscovMatrix_CMS2.obj")
    , evt_cscLooseHaloId_handle("int_beamHaloMaker_evtcscLooseHaloId_CMS2.obj")
    , evt_cscTightHaloId_handle("int_beamHaloMaker_evtcscTightHaloId_CMS2.obj")
    , evt_ecalLooseHaloId_handle("int_beamHaloMaker_evtecalLooseHaloId_CMS2.obj")
    , evt_ecalTightHaloId_handle("int_beamHaloMaker_evtecalTightHaloId_CMS2.obj")
    , evt_extremeTightHaloId_handle("int_beamHaloMaker_evtextremeTightHaloId_CMS2.obj")
    , evt_globalLooseHaloId_handle("int_beamHaloMaker_evtglobalLooseHaloId_CMS2.obj")
    , evt_globalTightHaloId_handle("int_beamHaloMaker_evtglobalTightHaloId_CMS2.obj")
    , evt_hcalLooseHaloId_handle("int_beamHaloMaker_evthcalLooseHaloId_CMS2.obj")
    , evt_hcalTightHaloId_handle("int_beamHaloMaker_evthcalTightHaloId_CMS2.obj")
    , evt_looseHaloId_handle("int_beamHaloMaker_evtlooseHaloId_CMS2.obj")
    , evt_nHaloLikeTracks_handle("int_beamHaloMaker_evtnHaloLikeTracks_CMS2.obj")
    , evt_nHaloTriggerCandidates_handle("int_beamHaloMaker_evtnHaloTriggerCandidates_CMS2.obj")
    , evt_tightHaloId_handle("int_beamHaloMaker_evttightHaloId_CMS2.obj")
    , evt_bsType_handle("int_beamSpotMaker_evtbsType_CMS2.obj")
    , evt_bunchCrossing_handle("int_eventMaker_evtbunchCrossing_CMS2.obj")
    , evt_experimentType_handle("int_eventMaker_evtexperimentType_CMS2.obj")
    , evt_isRealData_handle("int_eventMaker_evtisRealData_CMS2.obj")
    , evt_orbitNumber_handle("int_eventMaker_evtorbitNumber_CMS2.obj")
    , evt_storeNumber_handle("int_eventMaker_evtstoreNumber_CMS2.obj")
    , hcalnoise_GetRecHitCount_handle("int_hcalNoiseSummaryMaker_hcalnoiseGetRecHitCount_CMS2.obj")
    , hcalnoise_GetRecHitCount15_handle("int_hcalNoiseSummaryMaker_hcalnoiseGetRecHitCount15_CMS2.obj")
    , hcalnoise_maxHPDHits_handle("int_hcalNoiseSummaryMaker_hcalnoisemaxHPDHits_CMS2.obj")
    , hcalnoise_maxHPDNoOtherHits_handle("int_hcalNoiseSummaryMaker_hcalnoisemaxHPDNoOtherHits_CMS2.obj")
    , hcalnoise_maxRBXHits_handle("int_hcalNoiseSummaryMaker_hcalnoisemaxRBXHits_CMS2.obj")
    , hcalnoise_maxZeros_handle("int_hcalNoiseSummaryMaker_hcalnoisemaxZeros_CMS2.obj")
    , hcalnoise_noiseFilterStatus_handle("int_hcalNoiseSummaryMaker_hcalnoisenoiseFilterStatus_CMS2.obj")
    , hcalnoise_noiseType_handle("int_hcalNoiseSummaryMaker_hcalnoisenoiseType_CMS2.obj")
    , hcalnoise_num10GeVHits_handle("int_hcalNoiseSummaryMaker_hcalnoisenum10GeVHits_CMS2.obj")
    , hcalnoise_num25GeVHits_handle("int_hcalNoiseSummaryMaker_hcalnoisenum25GeVHits_CMS2.obj")
    , hcalnoise_numFlatNoiseChannels_handle("int_hcalNoiseSummaryMaker_hcalnoisenumFlatNoiseChannels_CMS2.obj")
    , hcalnoise_numIsolatedNoiseChannels_handle("int_hcalNoiseSummaryMaker_hcalnoisenumIsolatedNoiseChannels_CMS2.obj")
    , hcalnoise_numProblematicRBXs_handle("int_hcalNoiseSummaryMaker_hcalnoisenumProblematicRBXs_CMS2.obj")
    , hcalnoise_numSpikeNoiseChannels_handle("int_hcalNoiseSummaryMaker_hcalnoisenumSpikeNoiseChannels_CMS2.obj")
    , hcalnoise_numTS4TS5NoiseChannels_handle("int_hcalNoiseSummaryMaker_hcalnoisenumTS4TS5NoiseChannels_CMS2.obj")
    , hcalnoise_numTriangleNoiseChannels_handle("int_hcalNoiseSummaryMaker_hcalnoisenumTriangleNoiseChannels_CMS2.obj")
    , hcalnoise_passHighLevelNoiseFilter_handle("int_hcalNoiseSummaryMaker_hcalnoisepassHighLevelNoiseFilter_CMS2.obj")
    , hcalnoise_passLooseNoiseFilter_handle("int_hcalNoiseSummaryMaker_hcalnoisepassLooseNoiseFilter_CMS2.obj")
    , hcalnoise_passTightNoiseFilter_handle("int_hcalNoiseSummaryMaker_hcalnoisepassTightNoiseFilter_CMS2.obj")
    , l1_nemiso_handle("int_l1Maker_l1nemiso_CMS2.obj")
    , l1_nemnoiso_handle("int_l1Maker_l1nemnoiso_CMS2.obj")
    , l1_njetsc_handle("int_l1Maker_l1njetsc_CMS2.obj")
    , l1_njetsf_handle("int_l1Maker_l1njetsf_CMS2.obj")
    , l1_njetst_handle("int_l1Maker_l1njetst_CMS2.obj")
    , l1_nmus_handle("int_l1Maker_l1nmus_CMS2.obj")
    , ls_lumiSecQual_handle("int_luminosityMaker_lslumiSecQual_CMS2.obj")
    , pdfinfo_id1_handle("int_pdfinfoMaker_pdfinfoid1_CMS2.obj")
    , pdfinfo_id2_handle("int_pdfinfoMaker_pdfinfoid2_CMS2.obj")
    , sparm_subProcessId_handle("int_sParmMaker_sparmsubProcessId_CMS2.obj")
    , evt_ecaliPhiSuspects_handle("ints_beamHaloMaker_evtecaliPhiSuspects_CMS2.obj")
    , evt_globaliPhiSuspects_handle("ints_beamHaloMaker_evtglobaliPhiSuspects_CMS2.obj")
    , evt_hcaliPhiSuspects_handle("ints_beamHaloMaker_evthcaliPhiSuspects_CMS2.obj")
    , els_mc3_id_handle("ints_candToGenAssMaker_elsmc3id_CMS2.obj")
    , els_mc3idx_handle("ints_candToGenAssMaker_elsmc3idx_CMS2.obj")
    , els_mc3_motherid_handle("ints_candToGenAssMaker_elsmc3motherid_CMS2.obj")
    , els_mc3_motheridx_handle("ints_candToGenAssMaker_elsmc3motheridx_CMS2.obj")
    , els_mc_id_handle("ints_candToGenAssMaker_elsmcid_CMS2.obj")
    , els_mcidx_handle("ints_candToGenAssMaker_elsmcidx_CMS2.obj")
    , els_mc_motherid_handle("ints_candToGenAssMaker_elsmcmotherid_CMS2.obj")
    , jets_mc3_id_handle("ints_candToGenAssMaker_jetsmc3id_CMS2.obj")
    , jets_mc3idx_handle("ints_candToGenAssMaker_jetsmc3idx_CMS2.obj")
    , jets_mc_gpidx_handle("ints_candToGenAssMaker_jetsmcgpidx_CMS2.obj")
    , jets_mc_id_handle("ints_candToGenAssMaker_jetsmcid_CMS2.obj")
    , jets_mcidx_handle("ints_candToGenAssMaker_jetsmcidx_CMS2.obj")
    , jets_mc_motherid_handle("ints_candToGenAssMaker_jetsmcmotherid_CMS2.obj")
    , mus_mc3_id_handle("ints_candToGenAssMaker_musmc3id_CMS2.obj")
    , mus_mc3idx_handle("ints_candToGenAssMaker_musmc3idx_CMS2.obj")
    , mus_mc3_motherid_handle("ints_candToGenAssMaker_musmc3motherid_CMS2.obj")
    , mus_mc3_motheridx_handle("ints_candToGenAssMaker_musmc3motheridx_CMS2.obj")
    , mus_mc_id_handle("ints_candToGenAssMaker_musmcid_CMS2.obj")
    , mus_mcidx_handle("ints_candToGenAssMaker_musmcidx_CMS2.obj")
    , mus_mc_motherid_handle("ints_candToGenAssMaker_musmcmotherid_CMS2.obj")
    , pfjets_mc3_id_handle("ints_candToGenAssMaker_pfjetsmc3id_CMS2.obj")
    , pfjets_mc3idx_handle("ints_candToGenAssMaker_pfjetsmc3idx_CMS2.obj")
    , pfjets_mc_gpidx_handle("ints_candToGenAssMaker_pfjetsmcgpidx_CMS2.obj")
    , pfjets_mc_id_handle("ints_candToGenAssMaker_pfjetsmcid_CMS2.obj")
    , pfjets_mcidx_handle("ints_candToGenAssMaker_pfjetsmcidx_CMS2.obj")
    , pfjets_mc_motherid_handle("ints_candToGenAssMaker_pfjetsmcmotherid_CMS2.obj")
    , photons_mc3_id_handle("ints_candToGenAssMaker_photonsmc3id_CMS2.obj")
    , photons_mc3idx_handle("ints_candToGenAssMaker_photonsmc3idx_CMS2.obj")
    , photons_mc3_motherid_handle("ints_candToGenAssMaker_photonsmc3motherid_CMS2.obj")
    , photons_mc3_motheridx_handle("ints_candToGenAssMaker_photonsmc3motheridx_CMS2.obj")
    , photons_mc_id_handle("ints_candToGenAssMaker_photonsmcid_CMS2.obj")
    , photons_mcidx_handle("ints_candToGenAssMaker_photonsmcidx_CMS2.obj")
    , photons_mc_motherid_handle("ints_candToGenAssMaker_photonsmcmotherid_CMS2.obj")
    , trk_mc3_id_handle("ints_candToGenAssMaker_trkmc3id_CMS2.obj")
    , trk_mc3idx_handle("ints_candToGenAssMaker_trkmc3idx_CMS2.obj")
    , trk_mc3_motherid_handle("ints_candToGenAssMaker_trkmc3motherid_CMS2.obj")
    , trk_mc3_motheridx_handle("ints_candToGenAssMaker_trkmc3motheridx_CMS2.obj")
    , trk_mc_id_handle("ints_candToGenAssMaker_trkmcid_CMS2.obj")
    , trk_mcidx_handle("ints_candToGenAssMaker_trkmcidx_CMS2.obj")
    , trk_mc_motherid_handle("ints_candToGenAssMaker_trkmcmotherid_CMS2.obj")
    , els_closestJet_handle("ints_elToJetAssMaker_elsclosestJet_CMS2.obj")
    , els_closestMuon_handle("ints_elToMuAssMaker_elsclosestMuon_CMS2.obj")
    , els_pfelsidx_handle("ints_elToPFElAssMaker_elspfelsidx_CMS2.obj")
    , els_category_handle("ints_electronMaker_elscategory_CMS2.obj")
    , els_charge_handle("ints_electronMaker_elscharge_CMS2.obj")
    , els_ckf_laywithmeas_handle("ints_electronMaker_elsckflaywithmeas_CMS2.obj")
    , els_class_handle("ints_electronMaker_elsclass_CMS2.obj")
    , els_conv_delMissHits_handle("ints_electronMaker_elsconvdelMissHits_CMS2.obj")
    , els_conv_flag_handle("ints_electronMaker_elsconvflag_CMS2.obj")
    , els_conv_gsftkidx_handle("ints_electronMaker_elsconvgsftkidx_CMS2.obj")
    , els_conv_old_delMissHits_handle("ints_electronMaker_elsconvolddelMissHits_CMS2.obj")
    , els_conv_old_flag_handle("ints_electronMaker_elsconvoldflag_CMS2.obj")
    , els_conv_old_gsftkidx_handle("ints_electronMaker_elsconvoldgsftkidx_CMS2.obj")
    , els_conv_old_tkidx_handle("ints_electronMaker_elsconvoldtkidx_CMS2.obj")
    , els_conv_tkidx_handle("ints_electronMaker_elsconvtkidx_CMS2.obj")
    , els_exp_innerlayers_handle("ints_electronMaker_elsexpinnerlayers_CMS2.obj")
    , els_exp_outerlayers_handle("ints_electronMaker_elsexpouterlayers_CMS2.obj")
    , els_fiduciality_handle("ints_electronMaker_elsfiduciality_CMS2.obj")
    , els_gsftrkidx_handle("ints_electronMaker_elsgsftrkidx_CMS2.obj")
    , els_layer1_det_handle("ints_electronMaker_elslayer1det_CMS2.obj")
    , els_layer1_layer_handle("ints_electronMaker_elslayer1layer_CMS2.obj")
    , els_layer1_sizerphi_handle("ints_electronMaker_elslayer1sizerphi_CMS2.obj")
    , els_layer1_sizerz_handle("ints_electronMaker_elslayer1sizerz_CMS2.obj")
    , els_lostHits_handle("ints_electronMaker_elslostHits_CMS2.obj")
    , els_lost_pixelhits_handle("ints_electronMaker_elslostpixelhits_CMS2.obj")
    , els_nSeed_handle("ints_electronMaker_elsnSeed_CMS2.obj")
    , els_sccharge_handle("ints_electronMaker_elssccharge_CMS2.obj")
    , els_scindex_handle("ints_electronMaker_elsscindex_CMS2.obj")
    , els_trk_charge_handle("ints_electronMaker_elstrkcharge_CMS2.obj")
    , els_trkidx_handle("ints_electronMaker_elstrkidx_CMS2.obj")
    , els_type_handle("ints_electronMaker_elstype_CMS2.obj")
    , els_validHits_handle("ints_electronMaker_elsvalidHits_CMS2.obj")
    , els_valid_pixelhits_handle("ints_electronMaker_elsvalidpixelhits_CMS2.obj")
    , genps_id_handle("ints_genMaker_genpsid_CMS2.obj")
    , genps_id_mother_handle("ints_genMaker_genpsidmother_CMS2.obj")
    , genps_status_handle("ints_genMaker_genpsstatus_CMS2.obj")
    , gsftrks_charge_handle("ints_gsfTrackMaker_gsftrkscharge_CMS2.obj")
    , gsftrks_exp_innerlayers_handle("ints_gsfTrackMaker_gsftrksexpinnerlayers_CMS2.obj")
    , gsftrks_exp_outerlayers_handle("ints_gsfTrackMaker_gsftrksexpouterlayers_CMS2.obj")
    , gsftrks_layer1_det_handle("ints_gsfTrackMaker_gsftrkslayer1det_CMS2.obj")
    , gsftrks_layer1_layer_handle("ints_gsfTrackMaker_gsftrkslayer1layer_CMS2.obj")
    , gsftrks_layer1_sizerphi_handle("ints_gsfTrackMaker_gsftrkslayer1sizerphi_CMS2.obj")
    , gsftrks_layer1_sizerz_handle("ints_gsfTrackMaker_gsftrkslayer1sizerz_CMS2.obj")
    , gsftrks_lostHits_handle("ints_gsfTrackMaker_gsftrkslostHits_CMS2.obj")
    , gsftrks_lost_pixelhits_handle("ints_gsfTrackMaker_gsftrkslostpixelhits_CMS2.obj")
    , gsftrks_nlayers_handle("ints_gsfTrackMaker_gsftrksnlayers_CMS2.obj")
    , gsftrks_nlayers3D_handle("ints_gsfTrackMaker_gsftrksnlayers3D_CMS2.obj")
    , gsftrks_nlayersLost_handle("ints_gsfTrackMaker_gsftrksnlayersLost_CMS2.obj")
    , gsftrks_validHits_handle("ints_gsfTrackMaker_gsftrksvalidHits_CMS2.obj")
    , gsftrks_valid_pixelhits_handle("ints_gsfTrackMaker_gsftrksvalidpixelhits_CMS2.obj")
    , hyp_ll_charge_handle("ints_hypDilepMaker_hypllcharge_CMS2.obj")
    , hyp_ll_id_handle("ints_hypDilepMaker_hypllid_CMS2.obj")
    , hyp_ll_index_handle("ints_hypDilepMaker_hypllindex_CMS2.obj")
    , hyp_ll_lostHits_handle("ints_hypDilepMaker_hyplllostHits_CMS2.obj")
    , hyp_ll_validHits_handle("ints_hypDilepMaker_hypllvalidHits_CMS2.obj")
    , hyp_lt_charge_handle("ints_hypDilepMaker_hypltcharge_CMS2.obj")
    , hyp_lt_id_handle("ints_hypDilepMaker_hypltid_CMS2.obj")
    , hyp_lt_index_handle("ints_hypDilepMaker_hypltindex_CMS2.obj")
    , hyp_lt_lostHits_handle("ints_hypDilepMaker_hypltlostHits_CMS2.obj")
    , hyp_lt_validHits_handle("ints_hypDilepMaker_hypltvalidHits_CMS2.obj")
    , hyp_njets_handle("ints_hypDilepMaker_hypnjets_CMS2.obj")
    , hyp_nojets_handle("ints_hypDilepMaker_hypnojets_CMS2.obj")
    , hyp_type_handle("ints_hypDilepMaker_hyptype_CMS2.obj")
    , hyp_FVFit_ndf_handle("ints_hypDilepVertexMaker_hypFVFitndf_CMS2.obj")
    , hyp_FVFit_status_handle("ints_hypDilepVertexMaker_hypFVFitstatus_CMS2.obj")
    , hyp_ll_mc_id_handle("ints_hypGenMaker_hypllmcid_CMS2.obj")
    , hyp_ll_mc_motherid_handle("ints_hypGenMaker_hypllmcmotherid_CMS2.obj")
    , hyp_lt_mc_id_handle("ints_hypGenMaker_hypltmcid_CMS2.obj")
    , hyp_lt_mc_motherid_handle("ints_hypGenMaker_hypltmcmotherid_CMS2.obj")
    , pfjets_mcflavorAlgo_handle("ints_jetFlavorMaker_pfjetsmcflavorAlgo_CMS2.obj")
    , pfjets_mcflavorPhys_handle("ints_jetFlavorMaker_pfjetsmcflavorPhys_CMS2.obj")
    , jets_closestElectron_handle("ints_jetToElAssMaker_jetsclosestElectron_CMS2.obj")
    , jets_closestMuon_handle("ints_jetToMuAssMaker_jetsclosestMuon_CMS2.obj")
    , l1_emiso_ieta_handle("ints_l1Maker_l1emisoieta_CMS2.obj")
    , l1_emiso_iphi_handle("ints_l1Maker_l1emisoiphi_CMS2.obj")
    , l1_emiso_rawId_handle("ints_l1Maker_l1emisorawId_CMS2.obj")
    , l1_emiso_type_handle("ints_l1Maker_l1emisotype_CMS2.obj")
    , l1_emnoiso_ieta_handle("ints_l1Maker_l1emnoisoieta_CMS2.obj")
    , l1_emnoiso_iphi_handle("ints_l1Maker_l1emnoisoiphi_CMS2.obj")
    , l1_emnoiso_rawId_handle("ints_l1Maker_l1emnoisorawId_CMS2.obj")
    , l1_emnoiso_type_handle("ints_l1Maker_l1emnoisotype_CMS2.obj")
    , l1_jetsc_ieta_handle("ints_l1Maker_l1jetscieta_CMS2.obj")
    , l1_jetsc_iphi_handle("ints_l1Maker_l1jetsciphi_CMS2.obj")
    , l1_jetsc_rawId_handle("ints_l1Maker_l1jetscrawId_CMS2.obj")
    , l1_jetsc_type_handle("ints_l1Maker_l1jetsctype_CMS2.obj")
    , l1_jetsf_ieta_handle("ints_l1Maker_l1jetsfieta_CMS2.obj")
    , l1_jetsf_iphi_handle("ints_l1Maker_l1jetsfiphi_CMS2.obj")
    , l1_jetsf_rawId_handle("ints_l1Maker_l1jetsfrawId_CMS2.obj")
    , l1_jetsf_type_handle("ints_l1Maker_l1jetsftype_CMS2.obj")
    , l1_jetst_ieta_handle("ints_l1Maker_l1jetstieta_CMS2.obj")
    , l1_jetst_iphi_handle("ints_l1Maker_l1jetstiphi_CMS2.obj")
    , l1_jetst_rawId_handle("ints_l1Maker_l1jetstrawId_CMS2.obj")
    , l1_jetst_type_handle("ints_l1Maker_l1jetsttype_CMS2.obj")
    , l1_mus_flags_handle("ints_l1Maker_l1musflags_CMS2.obj")
    , l1_mus_q_handle("ints_l1Maker_l1musq_CMS2.obj")
    , l1_mus_qual_handle("ints_l1Maker_l1musqual_CMS2.obj")
    , l1_mus_qualFlags_handle("ints_l1Maker_l1musqualFlags_CMS2.obj")
    , mus_met_flag_handle("ints_metMaker_musmetflag_CMS2.obj")
    , mus_closestEle_handle("ints_muToElsAssMaker_musclosestEle_CMS2.obj")
    , mus_closestJet_handle("ints_muToJetAssMaker_musclosestJet_CMS2.obj")
    , mus_pfmusidx_handle("ints_muToPFMuAssMaker_muspfmusidx_CMS2.obj")
    , mus_charge_handle("ints_muonMaker_muscharge_CMS2.obj")
    , mus_gfit_validHits_handle("ints_muonMaker_musgfitvalidHits_CMS2.obj")
    , mus_gfit_validSTAHits_handle("ints_muonMaker_musgfitvalidSTAHits_CMS2.obj")
    , mus_gfit_validSiHits_handle("ints_muonMaker_musgfitvalidSiHits_CMS2.obj")
    , mus_goodmask_handle("ints_muonMaker_musgoodmask_CMS2.obj")
    , mus_iso03_ntrk_handle("ints_muonMaker_musiso03ntrk_CMS2.obj")
    , mus_iso05_ntrk_handle("ints_muonMaker_musiso05ntrk_CMS2.obj")
    , mus_lostHits_handle("ints_muonMaker_muslostHits_CMS2.obj")
    , mus_muonBestTrackType_handle("ints_muonMaker_musmuonBestTrackType_CMS2.obj")
    , mus_nOverlaps_handle("ints_muonMaker_musnOverlaps_CMS2.obj")
    , mus_nmatches_handle("ints_muonMaker_musnmatches_CMS2.obj")
    , mus_numberOfMatchedStations_handle("ints_muonMaker_musnumberOfMatchedStations_CMS2.obj")
    , mus_overlap0_handle("ints_muonMaker_musoverlap0_CMS2.obj")
    , mus_overlap1_handle("ints_muonMaker_musoverlap1_CMS2.obj")
    , mus_pfcharge_handle("ints_muonMaker_muspfcharge_CMS2.obj")
    , mus_pfflag_handle("ints_muonMaker_muspfflag_CMS2.obj")
    , mus_pfparticleId_handle("ints_muonMaker_muspfparticleId_CMS2.obj")
    , mus_pid_PFMuon_handle("ints_muonMaker_muspidPFMuon_CMS2.obj")
    , mus_pid_TM2DCompatibilityLoose_handle("ints_muonMaker_muspidTM2DCompatibilityLoose_CMS2.obj")
    , mus_pid_TM2DCompatibilityTight_handle("ints_muonMaker_muspidTM2DCompatibilityTight_CMS2.obj")
    , mus_pid_TMLastStationLoose_handle("ints_muonMaker_muspidTMLastStationLoose_CMS2.obj")
    , mus_pid_TMLastStationTight_handle("ints_muonMaker_muspidTMLastStationTight_CMS2.obj")
    , mus_sta_validHits_handle("ints_muonMaker_musstavalidHits_CMS2.obj")
    , mus_timeDirection_handle("ints_muonMaker_mustimeDirection_CMS2.obj")
    , mus_timeNumStationsUsed_handle("ints_muonMaker_mustimeNumStationsUsed_CMS2.obj")
    , mus_trk_charge_handle("ints_muonMaker_mustrkcharge_CMS2.obj")
    , mus_trkidx_handle("ints_muonMaker_mustrkidx_CMS2.obj")
    , mus_type_handle("ints_muonMaker_mustype_CMS2.obj")
    , mus_validHits_handle("ints_muonMaker_musvalidHits_CMS2.obj")
    , pfcands_charge_handle("ints_pfCandidateMaker_pfcandscharge_CMS2.obj")
    , pfcands_flag_handle("ints_pfCandidateMaker_pfcandsflag_CMS2.obj")
    , pfcands_particleId_handle("ints_pfCandidateMaker_pfcandsparticleId_CMS2.obj")
    , pfcands_pfelsidx_handle("ints_pfCandidateMaker_pfcandspfelsidx_CMS2.obj")
    , pfcands_pfmusidx_handle("ints_pfCandidateMaker_pfcandspfmusidx_CMS2.obj")
    , pfcands_trkidx_handle("ints_pfCandidateMaker_pfcandstrkidx_CMS2.obj")
    , pfcands_vtxidx_handle("ints_pfCandidateMaker_pfcandsvtxidx_CMS2.obj")
    , pfels_elsidx_handle("ints_pfElToElAssMaker_pfelselsidx_CMS2.obj")
    , pfels_charge_handle("ints_pfElectronMaker_pfelscharge_CMS2.obj")
    , pfels_flag_handle("ints_pfElectronMaker_pfelsflag_CMS2.obj")
    , pfels_particleId_handle("ints_pfElectronMaker_pfelsparticleId_CMS2.obj")
    , pfjets_chargedHadronMultiplicity_handle("ints_pfJetMaker_pfjetschargedHadronMultiplicity_CMS2.obj")
    , pfjets_chargedMultiplicity_handle("ints_pfJetMaker_pfjetschargedMultiplicity_CMS2.obj")
    , pfjets_electronMultiplicity_handle("ints_pfJetMaker_pfjetselectronMultiplicity_CMS2.obj")
    , pfjets_hfEmMultiplicity_handle("ints_pfJetMaker_pfjetshfEmMultiplicity_CMS2.obj")
    , pfjets_hfHadronMultiplicity_handle("ints_pfJetMaker_pfjetshfHadronMultiplicity_CMS2.obj")
    , pfjets_muonMultiplicity_handle("ints_pfJetMaker_pfjetsmuonMultiplicity_CMS2.obj")
    , pfjets_neutralHadronMultiplicity_handle("ints_pfJetMaker_pfjetsneutralHadronMultiplicity_CMS2.obj")
    , pfjets_neutralMultiplicity_handle("ints_pfJetMaker_pfjetsneutralMultiplicity_CMS2.obj")
    , pfjets_photonMultiplicity_handle("ints_pfJetMaker_pfjetsphotonMultiplicity_CMS2.obj")
    , pfmus_musidx_handle("ints_pfMuToMuAssMaker_pfmusmusidx_CMS2.obj")
    , pfmus_charge_handle("ints_pfMuonMaker_pfmuscharge_CMS2.obj")
    , pfmus_flag_handle("ints_pfMuonMaker_pfmusflag_CMS2.obj")
    , pfmus_particleId_handle("ints_pfMuonMaker_pfmusparticleId_CMS2.obj")
    , taus_pf_charge_handle("ints_pftauMaker_tauspfcharge_CMS2.obj")
    , taus_pf_pfjetIndex_handle("ints_pftauMaker_tauspfpfjetIndex_CMS2.obj")
    , photons_fiduciality_handle("ints_photonMaker_photonsfiduciality_CMS2.obj")
    , photons_scindex_handle("ints_photonMaker_photonsscindex_CMS2.obj")
    , puInfo_bunchCrossing_handle("ints_puSummaryInfoMaker_puInfobunchCrossing_CMS2.obj")
    , puInfo_nPUvertices_handle("ints_puSummaryInfoMaker_puInfonPUvertices_CMS2.obj")
    , convs_algo_handle("ints_recoConversionMaker_convsalgo_CMS2.obj")
    , convs_isConverted_handle("ints_recoConversionMaker_convsisConverted_CMS2.obj")
    , convs_quality_handle("ints_recoConversionMaker_convsquality_CMS2.obj")
    , scs_detIdSeed_handle("ints_scMaker_scsdetIdSeed_CMS2.obj")
    , scs_elsidx_handle("ints_scMaker_scselsidx_CMS2.obj")
    , scs_severitySeed_handle("ints_scMaker_scsseveritySeed_CMS2.obj")
    , svs_isKs_handle("ints_secondaryVertexMaker_svsisKs_CMS2.obj")
    , svs_isLambda_handle("ints_secondaryVertexMaker_svsisLambda_CMS2.obj")
    , svs_mc3_id_handle("ints_secondaryVertexMaker_svsmc3id_CMS2.obj")
    , svs_nTrks_handle("ints_secondaryVertexMaker_svsnTrks_CMS2.obj")
    , mus_tcmet_flag_handle("ints_tcmetMaker_mustcmetflag_CMS2.obj")
    , trks_algo_handle("ints_trackMaker_trksalgo_CMS2.obj")
    , trks_charge_handle("ints_trackMaker_trkscharge_CMS2.obj")
    , trks_exp_innerlayers_handle("ints_trackMaker_trksexpinnerlayers_CMS2.obj")
    , trks_exp_outerlayers_handle("ints_trackMaker_trksexpouterlayers_CMS2.obj")
    , trks_layer1_det_handle("ints_trackMaker_trkslayer1det_CMS2.obj")
    , trks_layer1_layer_handle("ints_trackMaker_trkslayer1layer_CMS2.obj")
    , trks_layer1_sizerphi_handle("ints_trackMaker_trkslayer1sizerphi_CMS2.obj")
    , trks_layer1_sizerz_handle("ints_trackMaker_trkslayer1sizerz_CMS2.obj")
    , trks_lostHits_handle("ints_trackMaker_trkslostHits_CMS2.obj")
    , trks_lost_pixelhits_handle("ints_trackMaker_trkslostpixelhits_CMS2.obj")
    , trks_nLoops_handle("ints_trackMaker_trksnLoops_CMS2.obj")
    , trks_nlayers_handle("ints_trackMaker_trksnlayers_CMS2.obj")
    , trks_nlayers3D_handle("ints_trackMaker_trksnlayers3D_CMS2.obj")
    , trks_nlayersLost_handle("ints_trackMaker_trksnlayersLost_CMS2.obj")
    , trks_pvidx0_handle("ints_trackMaker_trkspvidx0_CMS2.obj")
    , trks_pvidx1_handle("ints_trackMaker_trkspvidx1_CMS2.obj")
    , trks_qualityMask_handle("ints_trackMaker_trksqualityMask_CMS2.obj")
    , trks_validHits_handle("ints_trackMaker_trksvalidHits_CMS2.obj")
    , trks_valid_pixelhits_handle("ints_trackMaker_trksvalidpixelhits_CMS2.obj")
    , trks_elsidx_handle("ints_trackToElsAssMaker_trkselsidx_CMS2.obj")
    , trk_musidx_handle("ints_trackToMuonAssMaker_trkmusidx_CMS2.obj")
    , trkjets_ntrks_handle("ints_trkJetMaker_trkjetsntrks_CMS2.obj")
    , trkjets_vtxs_idx_handle("ints_trkJetMaker_trkjetsvtxsidx_CMS2.obj")
    , vtxs_isFake_handle("ints_vertexMaker_vtxsisFake_CMS2.obj")
    , vtxs_isValid_handle("ints_vertexMaker_vtxsisValid_CMS2.obj")
    , vtxs_tracksSize_handle("ints_vertexMaker_vtxstracksSize_CMS2.obj")
    , bsvtxs_isFake_handle("ints_vertexMakerWithBS_bsvtxsisFake_CMS2.obj")
    , bsvtxs_isValid_handle("ints_vertexMakerWithBS_bsvtxsisValid_CMS2.obj")
    , bsvtxs_tracksSize_handle("ints_vertexMakerWithBS_bsvtxstracksSize_CMS2.obj")
    , els_convs_delMissHits_handle("intss_electronMaker_elsconvsdelMissHits_CMS2.obj")
    , els_convs_flag_handle("intss_electronMaker_elsconvsflag_CMS2.obj")
    , els_convs_gsftkidx_handle("intss_electronMaker_elsconvsgsftkidx_CMS2.obj")
    , els_convs_tkidx_handle("intss_electronMaker_elsconvstkidx_CMS2.obj")
    , genps_lepdaughter_id_handle("intss_genMaker_genpslepdaughterid_CMS2.obj")
    , genps_lepdaughter_idx_handle("intss_genMaker_genpslepdaughteridx_CMS2.obj")
    , hlt_trigObjs_id_handle("intss_hltMaker_hlttrigObjsid_CMS2.obj")
    , hyp_jets_idx_handle("intss_hypDilepMaker_hypjetsidx_CMS2.obj")
    , hyp_other_jets_idx_handle("intss_hypDilepMaker_hypotherjetsidx_CMS2.obj")
    , mus_nStationCorrelatedHits_handle("intss_muonMaker_musnStationCorrelatedHits_CMS2.obj")
    , mus_nStationHits_handle("intss_muonMaker_musnStationHits_CMS2.obj")
    , pfjets_pfcandIndicies_handle("intss_pfJetMaker_pfjetspfcandIndicies_CMS2.obj")
    , taus_pf_pfcandIndicies_handle("intss_pftauMaker_tauspfpfcandIndicies_CMS2.obj")
    , puInfo_ntrks_highpt_handle("intss_puSummaryInfoMaker_puInfontrkshighpt_CMS2.obj")
    , puInfo_ntrks_lowpt_handle("intss_puSummaryInfoMaker_puInfontrkslowpt_CMS2.obj")
    , convs_nHitsBeforeVtx_handle("intss_recoConversionMaker_convsnHitsBeforeVtx_CMS2.obj")
    , convs_tkalgo_handle("intss_recoConversionMaker_convstkalgo_CMS2.obj")
    , convs_tkidx_handle("intss_recoConversionMaker_convstkidx_CMS2.obj")
    , els_HLT_Ele17_Ele8_L1sL1DoubleEG137_version_handle("uint_elToTrigAssMaker_elsHLTEle17Ele8L1sL1DoubleEG137version_CMS2.obj")
    , els_HLT_Ele17_Ele8_LeadingLeg_version_handle("uint_elToTrigAssMaker_elsHLTEle17Ele8LeadingLegversion_CMS2.obj")
    , els_HLT_Ele17_Ele8_Mass50_LeadingLeg_version_handle("uint_elToTrigAssMaker_elsHLTEle17Ele8Mass50LeadingLegversion_CMS2.obj")
    , els_HLT_Ele17_Ele8_Mass50_TrailingLeg_version_handle("uint_elToTrigAssMaker_elsHLTEle17Ele8Mass50TrailingLegversion_CMS2.obj")
    , els_HLT_Ele17_Ele8_TrailingLeg_version_handle("uint_elToTrigAssMaker_elsHLTEle17Ele8TrailingLegversion_CMS2.obj")
    , els_HLT_Ele17_Ele8_version_handle("uint_elToTrigAssMaker_elsHLTEle17Ele8version_CMS2.obj")
    , els_HLT_Ele20_SC4_Mass50_LeadingLeg_version_handle("uint_elToTrigAssMaker_elsHLTEle20SC4Mass50LeadingLegversion_CMS2.obj")
    , els_HLT_Ele20_SC4_Mass50_TrailingLeg_version_handle("uint_elToTrigAssMaker_elsHLTEle20SC4Mass50TrailingLegversion_CMS2.obj")
    , els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_version_handle("uint_elToTrigAssMaker_elsHLTEle27WP80L1sL1SingleEG20ORL1SingleEG22version_CMS2.obj")
    , els_HLT_Ele27_WP80_version_handle("uint_elToTrigAssMaker_elsHLTEle27WP80version_CMS2.obj")
    , els_HLT_Ele32_SC17_Mass50_LeadingLeg_version_handle("uint_elToTrigAssMaker_elsHLTEle32SC17Mass50LeadingLegversion_CMS2.obj")
    , els_HLT_Ele32_SC17_Mass50_TrailingLeg_version_handle("uint_elToTrigAssMaker_elsHLTEle32SC17Mass50TrailingLegversion_CMS2.obj")
    , els_HLT_Mu17_Ele8_TrailingLeg_version_handle("uint_elToTrigAssMaker_elsHLTMu17Ele8TrailingLegversion_CMS2.obj")
    , els_HLT_Mu17_Ele8_version_handle("uint_elToTrigAssMaker_elsHLTMu17Ele8version_CMS2.obj")
    , els_HLT_Mu8_Ele17_version_handle("uint_elToTrigAssMaker_elsHLTMu8Ele17version_CMS2.obj")
    , evt_nels_handle("uint_electronMaker_evtnels_CMS2.obj")
    , evt_detectorStatus_handle("uint_eventMaker_evtdetectorStatus_CMS2.obj")
    , evt_event_handle("uint_eventMaker_evtevent_CMS2.obj")
    , evt_lumiBlock_handle("uint_eventMaker_evtlumiBlock_CMS2.obj")
    , evt_run_handle("uint_eventMaker_evtrun_CMS2.obj")
    , genps_flavorHistoryFilterResult_handle("uint_flavorHistoryMaker_genpsflavorHistoryFilterResult_CMS2.obj")
    , evt_ngenjets_handle("uint_genJetMaker_evtngenjets_CMS2.obj")
    , genps_signalProcessID_handle("uint_genMaker_genpssignalProcessID_CMS2.obj")
    , evt_njets_handle("uint_jetMaker_evtnjets_CMS2.obj")
    , l1_bits1_handle("uint_l1Maker_l1bits1_CMS2.obj")
    , l1_bits2_handle("uint_l1Maker_l1bits2_CMS2.obj")
    , l1_bits3_handle("uint_l1Maker_l1bits3_CMS2.obj")
    , l1_bits4_handle("uint_l1Maker_l1bits4_CMS2.obj")
    , l1_techbits1_handle("uint_l1Maker_l1techbits1_CMS2.obj")
    , l1_techbits2_handle("uint_l1Maker_l1techbits2_CMS2.obj")
    , ls_lsNumber_handle("uint_luminosityMaker_lslsNumber_CMS2.obj")
    , ls_numOrbit_handle("uint_luminosityMaker_lsnumOrbit_CMS2.obj")
    , ls_startOrbit_handle("uint_luminosityMaker_lsstartOrbit_CMS2.obj")
    , mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_version_handle("uint_muToTrigAssMaker_musHLTIsoMu24eta2p1L1sMu16Eta2p1version_CMS2.obj")
    , mus_HLT_IsoMu24_eta2p1_version_handle("uint_muToTrigAssMaker_musHLTIsoMu24eta2p1version_CMS2.obj")
    , mus_HLT_Mu17_Ele8_LeadingLeg_version_handle("uint_muToTrigAssMaker_musHLTMu17Ele8LeadingLegversion_CMS2.obj")
    , mus_HLT_Mu17_Ele8_version_handle("uint_muToTrigAssMaker_musHLTMu17Ele8version_CMS2.obj")
    , mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_version_handle("uint_muToTrigAssMaker_musHLTMu17Mu8L1sL1DoubleMu10MuOpenversion_CMS2.obj")
    , mus_HLT_Mu17_Mu8_LeadingLeg_version_handle("uint_muToTrigAssMaker_musHLTMu17Mu8LeadingLegversion_CMS2.obj")
    , mus_HLT_Mu17_Mu8_TrailingLeg_version_handle("uint_muToTrigAssMaker_musHLTMu17Mu8TrailingLegversion_CMS2.obj")
    , mus_HLT_Mu17_Mu8_version_handle("uint_muToTrigAssMaker_musHLTMu17Mu8version_CMS2.obj")
    , mus_HLT_Mu17_TkMu8_LeadingLeg_version_handle("uint_muToTrigAssMaker_musHLTMu17TkMu8LeadingLegversion_CMS2.obj")
    , mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_version_handle("uint_muToTrigAssMaker_musHLTMu17TkMu8TrailingLegTrkFilteredversion_CMS2.obj")
    , mus_HLT_Mu17_TkMu8_TrailingLeg_version_handle("uint_muToTrigAssMaker_musHLTMu17TkMu8TrailingLegversion_CMS2.obj")
    , mus_HLT_Mu17_TkMu8_version_handle("uint_muToTrigAssMaker_musHLTMu17TkMu8version_CMS2.obj")
    , mus_HLT_Mu8_Ele17_TrailingLeg_version_handle("uint_muToTrigAssMaker_musHLTMu8Ele17TrailingLegversion_CMS2.obj")
    , mus_HLT_Mu8_Ele17_version_handle("uint_muToTrigAssMaker_musHLTMu8Ele17version_CMS2.obj")
    , evt_nphotons_handle("uint_photonMaker_evtnphotons_CMS2.obj")
    , evt_ecalRecoStatus_handle("uint_scMaker_evtecalrecostatus_CMS2.obj")
    , evt_nscs_handle("uint_scMaker_evtnscs_CMS2.obj")
    , evt_ntrkjets_handle("uint_trkJetMaker_evtntrkjets_CMS2.obj")
    , evt_nvtxs_handle("uint_vertexMaker_evtnvtxs_CMS2.obj")
    , evt_nbsvtxs_handle("uint_vertexMakerWithBS_evtnbsvtxs_CMS2.obj")
    , els_HLT_Ele17_Ele8_handle("uints_elToTrigAssMaker_elsHLTEle17Ele8_CMS2.obj")
    , els_HLT_Ele17_Ele8_L1sL1DoubleEG137_handle("uints_elToTrigAssMaker_elsHLTEle17Ele8L1sL1DoubleEG137_CMS2.obj")
    , els_HLT_Ele17_Ele8_LeadingLeg_handle("uints_elToTrigAssMaker_elsHLTEle17Ele8LeadingLeg_CMS2.obj")
    , els_HLT_Ele17_Ele8_Mass50_LeadingLeg_handle("uints_elToTrigAssMaker_elsHLTEle17Ele8Mass50LeadingLeg_CMS2.obj")
    , els_HLT_Ele17_Ele8_Mass50_TrailingLeg_handle("uints_elToTrigAssMaker_elsHLTEle17Ele8Mass50TrailingLeg_CMS2.obj")
    , els_HLT_Ele17_Ele8_TrailingLeg_handle("uints_elToTrigAssMaker_elsHLTEle17Ele8TrailingLeg_CMS2.obj")
    , els_HLT_Ele20_SC4_Mass50_LeadingLeg_handle("uints_elToTrigAssMaker_elsHLTEle20SC4Mass50LeadingLeg_CMS2.obj")
    , els_HLT_Ele20_SC4_Mass50_TrailingLeg_handle("uints_elToTrigAssMaker_elsHLTEle20SC4Mass50TrailingLeg_CMS2.obj")
    , els_HLT_Ele27_WP80_handle("uints_elToTrigAssMaker_elsHLTEle27WP80_CMS2.obj")
    , els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_handle("uints_elToTrigAssMaker_elsHLTEle27WP80L1sL1SingleEG20ORL1SingleEG22_CMS2.obj")
    , els_HLT_Ele32_SC17_Mass50_LeadingLeg_handle("uints_elToTrigAssMaker_elsHLTEle32SC17Mass50LeadingLeg_CMS2.obj")
    , els_HLT_Ele32_SC17_Mass50_TrailingLeg_handle("uints_elToTrigAssMaker_elsHLTEle32SC17Mass50TrailingLeg_CMS2.obj")
    , els_HLT_Mu17_Ele8_handle("uints_elToTrigAssMaker_elsHLTMu17Ele8_CMS2.obj")
    , els_HLT_Mu17_Ele8_TrailingLeg_handle("uints_elToTrigAssMaker_elsHLTMu17Ele8TrailingLeg_CMS2.obj")
    , els_HLT_Mu8_Ele17_handle("uints_elToTrigAssMaker_elsHLTMu8Ele17_CMS2.obj")
    , els_id2012ext_loose_handle("uints_electronMaker_elsid2012extloose_CMS2.obj")
    , els_id2012ext_medium_handle("uints_electronMaker_elsid2012extmedium_CMS2.obj")
    , els_id2012ext_tight_handle("uints_electronMaker_elsid2012exttight_CMS2.obj")
    , els_id2012ext_veto_handle("uints_electronMaker_elsid2012extveto_CMS2.obj")
    , els_id2012_loose_handle("uints_electronMaker_elsid2012loose_CMS2.obj")
    , els_id2012_medium_handle("uints_electronMaker_elsid2012medium_CMS2.obj")
    , els_id2012_tight_handle("uints_electronMaker_elsid2012tight_CMS2.obj")
    , els_id2012_veto_handle("uints_electronMaker_elsid2012veto_CMS2.obj")
    , hlt_prescales_handle("uints_hltMaker_hltprescales_CMS2.obj")
    , l1_prescales_handle("uints_l1Maker_l1prescales_CMS2.obj")
    , l1_techtrigprescales_handle("uints_l1Maker_l1techtrigprescales_CMS2.obj")
    , mus_HLT_IsoMu24_eta2p1_handle("uints_muToTrigAssMaker_musHLTIsoMu24eta2p1_CMS2.obj")
    , mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_handle("uints_muToTrigAssMaker_musHLTIsoMu24eta2p1L1sMu16Eta2p1_CMS2.obj")
    , mus_HLT_Mu17_Ele8_handle("uints_muToTrigAssMaker_musHLTMu17Ele8_CMS2.obj")
    , mus_HLT_Mu17_Ele8_LeadingLeg_handle("uints_muToTrigAssMaker_musHLTMu17Ele8LeadingLeg_CMS2.obj")
    , mus_HLT_Mu17_Mu8_handle("uints_muToTrigAssMaker_musHLTMu17Mu8_CMS2.obj")
    , mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_handle("uints_muToTrigAssMaker_musHLTMu17Mu8L1sL1DoubleMu10MuOpen_CMS2.obj")
    , mus_HLT_Mu17_Mu8_LeadingLeg_handle("uints_muToTrigAssMaker_musHLTMu17Mu8LeadingLeg_CMS2.obj")
    , mus_HLT_Mu17_Mu8_TrailingLeg_handle("uints_muToTrigAssMaker_musHLTMu17Mu8TrailingLeg_CMS2.obj")
    , mus_HLT_Mu17_TkMu8_handle("uints_muToTrigAssMaker_musHLTMu17TkMu8_CMS2.obj")
    , mus_HLT_Mu17_TkMu8_LeadingLeg_handle("uints_muToTrigAssMaker_musHLTMu17TkMu8LeadingLeg_CMS2.obj")
    , mus_HLT_Mu17_TkMu8_TrailingLeg_handle("uints_muToTrigAssMaker_musHLTMu17TkMu8TrailingLeg_CMS2.obj")
    , mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_handle("uints_muToTrigAssMaker_musHLTMu17TkMu8TrailingLegTrkFiltered_CMS2.obj")
    , mus_HLT_Mu8_Ele17_handle("uints_muToTrigAssMaker_musHLTMu8Ele17_CMS2.obj")
    , mus_HLT_Mu8_Ele17_TrailingLeg_handle("uints_muToTrigAssMaker_musHLTMu8Ele17TrailingLeg_CMS2.obj")
    , evt_timestamp_handle("ullong_eventMaker_evttimestamp_CMS2.obj")
    , evt_nEvts_handle("evtnEvts")
    , evt_filt_eff_handle("evtfilteff")
{
}

void CMS2::Init(TTree& tree)
{
    hlt_bits_handle.Init(tree);
    evt_CMS2tag_handle.Init(tree);
    evt_dataset_handle.Init(tree);
    hlt_trigNames_handle.Init(tree);
    l1_techtrigNames_handle.Init(tree);
    l1_trigNames_handle.Init(tree);
    evt_errCategory_handle.Init(tree);
    evt_errModule_handle.Init(tree);
    evt_errSeverity_handle.Init(tree);
    sparm_comment_handle.Init(tree);
    sparm_names_handle.Init(tree);
    evt_eventHasHalo_handle.Init(tree);
    hcalnoise_HasBadRBXTS4TS5_handle.Init(tree);
    ls_isValid_handle.Init(tree);
    filt_ecalBE_handle.Init(tree);
    filt_ecalDR_handle.Init(tree);
    filt_ecalLaser_handle.Init(tree);
    filt_ecalTP_handle.Init(tree);
    filt_eeBadSc_handle.Init(tree);
    filt_greedyMuon_handle.Init(tree);
    filt_hcalLaser_handle.Init(tree);
    filt_inconsistentMuon_handle.Init(tree);
    filt_jetIDFailure_handle.Init(tree);
    filt_multiEvent_handle.Init(tree);
    filt_trackingFailure_handle.Init(tree);
    evt_hbheFilter_handle.Init(tree);
    els_conv_vtx_flag_handle.Init(tree);
    els_passingMvaPreselection_handle.Init(tree);
    els_passingPflowPreselection_handle.Init(tree);
    mus_isRPCMuon_handle.Init(tree);
    mus_tightMatch_handle.Init(tree);
    mus_updatedSta_handle.Init(tree);
    pfcands_isMuIso_handle.Init(tree);
    photons_haspixelSeed_handle.Init(tree);
    jets_closestElectron_DR_handle.Init(tree);
    jets_closestMuon_DR_handle.Init(tree);
    evt_bs_Xwidth_handle.Init(tree);
    evt_bs_XwidthErr_handle.Init(tree);
    evt_bs_Ywidth_handle.Init(tree);
    evt_bs_YwidthErr_handle.Init(tree);
    evt_bs_dxdz_handle.Init(tree);
    evt_bs_dxdzErr_handle.Init(tree);
    evt_bs_dydz_handle.Init(tree);
    evt_bs_dydzErr_handle.Init(tree);
    evt_bs_sigmaZ_handle.Init(tree);
    evt_bs_sigmaZErr_handle.Init(tree);
    evt_bs_xErr_handle.Init(tree);
    evt_bs_yErr_handle.Init(tree);
    evt_bs_zErr_handle.Init(tree);
    evt_bField_handle.Init(tree);
    evt_rho_handle.Init(tree);
    evt_rhoJEC_handle.Init(tree);
    evt_fixgrid_all_rho_handle.Init(tree);
    evt_fixgridfastjet_all_rho_handle.Init(tree);
    evt_kfactor_handle.Init(tree);
    evt_scale1fb_handle.Init(tree);
    evt_xsec_excl_handle.Init(tree);
    evt_xsec_incl_handle.Init(tree);
    gen_met_handle.Init(tree);
    gen_metPhi_handle.Init(tree);
    genps_alphaQCD_handle.Init(tree);
    genps_pthat_handle.Init(tree);
    genps_qScale_handle.Init(tree);
    genps_weight_handle.Init(tree);
    gen_sumEt_handle.Init(tree);
    hcalnoise_GetRecHitEnergy_handle.Init(tree);
    hcalnoise_GetRecHitEnergy15_handle.Init(tree);
    hcalnoise_GetTotalCalibCharge_handle.Init(tree);
    hcalnoise_TS4TS5NoiseSumE_handle.Init(tree);
    hcalnoise_TS4TS5NoiseSumEt_handle.Init(tree);
    hcalnoise_eventChargeFraction_handle.Init(tree);
    hcalnoise_eventEMEnergy_handle.Init(tree);
    hcalnoise_eventEMFraction_handle.Init(tree);
    hcalnoise_eventHadEnergy_handle.Init(tree);
    hcalnoise_eventTrackEnergy_handle.Init(tree);
    hcalnoise_flatNoiseSumE_handle.Init(tree);
    hcalnoise_flatNoiseSumEt_handle.Init(tree);
    hcalnoise_isolatedNoiseSumE_handle.Init(tree);
    hcalnoise_isolatedNoiseSumEt_handle.Init(tree);
    hcalnoise_max10GeVHitTime_handle.Init(tree);
    hcalnoise_max25GeVHitTime_handle.Init(tree);
    hcalnoise_maxE10TS_handle.Init(tree);
    hcalnoise_maxE2Over10TS_handle.Init(tree);
    hcalnoise_maxE2TS_handle.Init(tree);
    hcalnoise_min10GeVHitTime_handle.Init(tree);
    hcalnoise_min25GeVHitTime_handle.Init(tree);
    hcalnoise_minE10TS_handle.Init(tree);
    hcalnoise_minE2Over10TS_handle.Init(tree);
    hcalnoise_minE2TS_handle.Init(tree);
    hcalnoise_minHPDEMF_handle.Init(tree);
    hcalnoise_minRBXEMF_handle.Init(tree);
    hcalnoise_rms10GeVHitTime_handle.Init(tree);
    hcalnoise_rms25GeVHitTime_handle.Init(tree);
    hcalnoise_spikeNoiseSumE_handle.Init(tree);
    hcalnoise_spikeNoiseSumEt_handle.Init(tree);
    hcalnoise_triangleNoiseSumE_handle.Init(tree);
    hcalnoise_triangleNoiseSumEt_handle.Init(tree);
    evt_kt6calo_central_rho_handle.Init(tree);
    evt_kt6calo_muhlt_rho_handle.Init(tree);
    evt_kt6calo_rho_handle.Init(tree);
    evt_kt6pf_ctrChargedPU_rho_handle.Init(tree);
    evt_kt6pf_ctrNeutral_rho_handle.Init(tree);
    evt_kt6pf_ctrNeutralTight_rho_handle.Init(tree);
    evt_kt6pf_foregiso_rho_handle.Init(tree);
    l1_met_etTot_handle.Init(tree);
    l1_met_met_handle.Init(tree);
    l1_mht_htTot_handle.Init(tree);
    l1_mht_mht_handle.Init(tree);
    ls_avgInsDelLumi_handle.Init(tree);
    ls_avgInsDelLumiErr_handle.Init(tree);
    ls_avgInsRecLumi_handle.Init(tree);
    ls_avgInsRecLumiErr_handle.Init(tree);
    ls_deadFrac_handle.Init(tree);
    ls_intgDelLumi_handle.Init(tree);
    ls_intgRecLumi_handle.Init(tree);
    ls_lumiSectionLength_handle.Init(tree);
    evt_ecalendcapm_met_handle.Init(tree);
    evt_ecalendcapm_metPhi_handle.Init(tree);
    evt_ecalendcapp_met_handle.Init(tree);
    evt_ecalendcapp_metPhi_handle.Init(tree);
    evt_ecalmet_handle.Init(tree);
    evt_ecalmetPhi_handle.Init(tree);
    evt_endcapm_met_handle.Init(tree);
    evt_endcapm_metPhi_handle.Init(tree);
    evt_endcapp_met_handle.Init(tree);
    evt_endcapp_metPhi_handle.Init(tree);
    evt_hcalendcapm_met_handle.Init(tree);
    evt_hcalendcapm_metPhi_handle.Init(tree);
    evt_hcalendcapp_met_handle.Init(tree);
    evt_hcalendcapp_metPhi_handle.Init(tree);
    evt_hcalmet_handle.Init(tree);
    evt_hcalmetPhi_handle.Init(tree);
    evt_met_handle.Init(tree);
    evt_met_EtGt3_handle.Init(tree);
    evt_metHO_handle.Init(tree);
    evt_metHOPhi_handle.Init(tree);
    evt_metHOSig_handle.Init(tree);
    evt_metMuonCorr_handle.Init(tree);
    evt_metMuonCorrPhi_handle.Init(tree);
    evt_metMuonCorrSig_handle.Init(tree);
    evt_metMuonJESCorr_handle.Init(tree);
    evt_metMuonJESCorrPhi_handle.Init(tree);
    evt_metMuonJESCorrSig_handle.Init(tree);
    evt_metNoHF_handle.Init(tree);
    evt_metNoHFHO_handle.Init(tree);
    evt_metNoHFHOPhi_handle.Init(tree);
    evt_metNoHFHOSig_handle.Init(tree);
    evt_metNoHFPhi_handle.Init(tree);
    evt_metNoHFSig_handle.Init(tree);
    evt_metOpt_handle.Init(tree);
    evt_metOptHO_handle.Init(tree);
    evt_metOptHOPhi_handle.Init(tree);
    evt_metOptHOSig_handle.Init(tree);
    evt_metOptNoHF_handle.Init(tree);
    evt_metOptNoHFHO_handle.Init(tree);
    evt_metOptNoHFHOPhi_handle.Init(tree);
    evt_metOptNoHFHOSig_handle.Init(tree);
    evt_metOptNoHFPhi_handle.Init(tree);
    evt_metOptNoHFSig_handle.Init(tree);
    evt_metOptPhi_handle.Init(tree);
    evt_metOptSig_handle.Init(tree);
    evt_metPhi_handle.Init(tree);
    evt_metPhi_EtGt3_handle.Init(tree);
    evt_metSig_handle.Init(tree);
    evt_sumet_handle.Init(tree);
    evt_sumet_EtGt3_handle.Init(tree);
    evt_sumetHO_handle.Init(tree);
    evt_sumetMuonCorr_handle.Init(tree);
    evt_sumetMuonJESCorr_handle.Init(tree);
    evt_sumetNoHF_handle.Init(tree);
    evt_sumetNoHFHO_handle.Init(tree);
    evt_sumetOpt_handle.Init(tree);
    evt_sumetOptHO_handle.Init(tree);
    evt_sumetOptNoHF_handle.Init(tree);
    evt_sumetOptNoHFHO_handle.Init(tree);
    pdfinfo_pdf1_handle.Init(tree);
    pdfinfo_pdf2_handle.Init(tree);
    pdfinfo_scale_handle.Init(tree);
    pdfinfo_x1_handle.Init(tree);
    pdfinfo_x2_handle.Init(tree);
    evt_fixgrid_rho_all_handle.Init(tree);
    evt_fixgrid_rho_ctr_handle.Init(tree);
    evt_fixgrid_rho_fwd_handle.Init(tree);
    evt_pfmet_handle.Init(tree);
    evt_pfmetPhi_handle.Init(tree);
    evt_pfmetPhi_type1cor_handle.Init(tree);
    evt_pfmetSig_handle.Init(tree);
    evt_pfmetSignificance_handle.Init(tree);
    evt_pfmet_type1cor_handle.Init(tree);
    evt_pfsumet_handle.Init(tree);
    sparm_filterEfficiency_handle.Init(tree);
    sparm_pdfScale_handle.Init(tree);
    sparm_pdfWeight1_handle.Init(tree);
    sparm_pdfWeight2_handle.Init(tree);
    sparm_weight_handle.Init(tree);
    sparm_xsec_handle.Init(tree);
    evt_pf_tcmet_handle.Init(tree);
    evt_pf_tcmetPhi_handle.Init(tree);
    evt_pf_tcmetSig_handle.Init(tree);
    evt_pf_tcsumet_handle.Init(tree);
    evt_tcmet_handle.Init(tree);
    evt_tcmetPhi_handle.Init(tree);
    evt_tcmetSig_handle.Init(tree);
    evt_tcsumet_handle.Init(tree);
    evt_ww_rho_act_handle.Init(tree);
    evt_ww_rho_handle.Init(tree);
    evt_ww_rho_rnd_handle.Init(tree);
    evt_ww_rho_vor_handle.Init(tree);
    evt_bsp4_handle.Init(tree);
    l1_met_p4_handle.Init(tree);
    l1_mht_p4_handle.Init(tree);
    els_mc_motherp4_handle.Init(tree);
    els_mc_p4_handle.Init(tree);
    jets_mc_gp_p4_handle.Init(tree);
    jets_mc_motherp4_handle.Init(tree);
    jets_mc_p4_handle.Init(tree);
    mus_mc_motherp4_handle.Init(tree);
    mus_mc_p4_handle.Init(tree);
    pfjets_mc_gp_p4_handle.Init(tree);
    pfjets_mc_motherp4_handle.Init(tree);
    pfjets_mc_p4_handle.Init(tree);
    photons_mc_motherp4_handle.Init(tree);
    photons_mc_p4_handle.Init(tree);
    trk_mcp4_handle.Init(tree);
    els_conv_pos_p4_handle.Init(tree);
    els_inner_position_handle.Init(tree);
    els_outer_position_handle.Init(tree);
    els_p4_handle.Init(tree);
    els_p4In_handle.Init(tree);
    els_p4Out_handle.Init(tree);
    els_trk_p4_handle.Init(tree);
    els_vertex_p4_handle.Init(tree);
    genjets_p4_handle.Init(tree);
    genps_p4_handle.Init(tree);
    genps_prod_vtx_handle.Init(tree);
    gsftrks_inner_position_handle.Init(tree);
    gsftrks_outer_p4_handle.Init(tree);
    gsftrks_outer_position_handle.Init(tree);
    gsftrks_p4_handle.Init(tree);
    gsftrks_vertex_p4_handle.Init(tree);
    hyp_ll_p4_handle.Init(tree);
    hyp_ll_trk_p4_handle.Init(tree);
    hyp_lt_p4_handle.Init(tree);
    hyp_lt_trk_p4_handle.Init(tree);
    hyp_p4_handle.Init(tree);
    hyp_FVFit_p4_handle.Init(tree);
    hyp_FVFit_v4_handle.Init(tree);
    hyp_ll_mc_p4_handle.Init(tree);
    hyp_lt_mc_p4_handle.Init(tree);
    jets_p4_handle.Init(tree);
    jets_vertex_p4_handle.Init(tree);
    l1_emiso_p4_handle.Init(tree);
    l1_emnoiso_p4_handle.Init(tree);
    l1_jetsc_p4_handle.Init(tree);
    l1_jetsf_p4_handle.Init(tree);
    l1_jetst_p4_handle.Init(tree);
    l1_mus_p4_handle.Init(tree);
    mus_ecalpos_p4_handle.Init(tree);
    mus_fitpicky_p4_handle.Init(tree);
    mus_fittev_p4_handle.Init(tree);
    mus_fittpfms_p4_handle.Init(tree);
    mus_gfit_outerPos_p4_handle.Init(tree);
    mus_gfit_p4_handle.Init(tree);
    mus_gfit_vertex_p4_handle.Init(tree);
    mus_p4_handle.Init(tree);
    mus_pfp4_handle.Init(tree);
    mus_pfposAtEcal_p4_handle.Init(tree);
    mus_sta_p4_handle.Init(tree);
    mus_sta_vertex_p4_handle.Init(tree);
    mus_trk_p4_handle.Init(tree);
    mus_vertex_p4_handle.Init(tree);
    pfcands_p4_handle.Init(tree);
    pfcands_posAtEcal_p4_handle.Init(tree);
    pfels_p4_handle.Init(tree);
    pfels_posAtEcal_p4_handle.Init(tree);
    pfjets_p4_handle.Init(tree);
    pfmus_p4_handle.Init(tree);
    pfmus_posAtEcal_p4_handle.Init(tree);
    taus_pf_p4_handle.Init(tree);
    photons_p4_handle.Init(tree);
    convs_refitPairMom_p4_handle.Init(tree);
    convs_vtxpos_handle.Init(tree);
    scs_p4_handle.Init(tree);
    scs_pos_p4_handle.Init(tree);
    scs_vtx_p4_handle.Init(tree);
    svs_flight_handle.Init(tree);
    svs_mc3_p4_handle.Init(tree);
    svs_p4_handle.Init(tree);
    svs_position_handle.Init(tree);
    svs_refitp4_handle.Init(tree);
    trks_inner_position_handle.Init(tree);
    trks_outer_p4_handle.Init(tree);
    trks_outer_position_handle.Init(tree);
    trks_trk_p4_handle.Init(tree);
    trks_vertex_p4_handle.Init(tree);
    trkjets_p4_handle.Init(tree);
    vtxs_position_handle.Init(tree);
    bsvtxs_position_handle.Init(tree);
    els_convs_pos_p4_handle.Init(tree);
    genps_lepdaughter_p4_handle.Init(tree);
    hlt_trigObjs_p4_handle.Init(tree);
    hyp_jets_p4_handle.Init(tree);
    hyp_other_jets_p4_handle.Init(tree);
    jpts_combinedSecondaryVertexBJetTag_handle.Init(tree);
    jpts_combinedSecondaryVertexMVABJetTag_handle.Init(tree);
    jpts_jetBProbabilityBJetTag_handle.Init(tree);
    jpts_jetProbabilityBJetTag_handle.Init(tree);
    jpts_simpleSecondaryVertexBJetTag_handle.Init(tree);
    jpts_simpleSecondaryVertexHighEffBJetTag_handle.Init(tree);
    jpts_simpleSecondaryVertexHighPurBJetTags_handle.Init(tree);
    jpts_softElectronByIP3dBJetTag_handle.Init(tree);
    jpts_softElectronByPtBJetTag_handle.Init(tree);
    jpts_softElectronTag_handle.Init(tree);
    jpts_softMuonBJetTag_handle.Init(tree);
    jpts_softMuonByIP3dBJetTag_handle.Init(tree);
    jpts_softMuonByPtBJetTag_handle.Init(tree);
    jpts_trackCountingHighEffBJetTag_handle.Init(tree);
    jpts_trackCountingHighPurBJetTag_handle.Init(tree);
    jets_combinedSecondaryVertexBJetTag_handle.Init(tree);
    jets_combinedSecondaryVertexMVABJetTag_handle.Init(tree);
    jets_jetBProbabilityBJetTag_handle.Init(tree);
    jets_jetProbabilityBJetTag_handle.Init(tree);
    jets_simpleSecondaryVertexBJetTag_handle.Init(tree);
    jets_simpleSecondaryVertexHighEffBJetTag_handle.Init(tree);
    jets_simpleSecondaryVertexHighPurBJetTags_handle.Init(tree);
    jets_softElectronByIP3dBJetTag_handle.Init(tree);
    jets_softElectronByPtBJetTag_handle.Init(tree);
    jets_softElectronTag_handle.Init(tree);
    jets_softMuonBJetTag_handle.Init(tree);
    jets_softMuonByIP3dBJetTag_handle.Init(tree);
    jets_softMuonByPtBJetTag_handle.Init(tree);
    jets_trackCountingHighEffBJetTag_handle.Init(tree);
    jets_trackCountingHighPurBJetTag_handle.Init(tree);
    pfjets_combinedSecondaryVertexBJetTag_handle.Init(tree);
    pfjets_combinedSecondaryVertexMVABJetTag_handle.Init(tree);
    pfjets_jetBProbabilityBJetTag_handle.Init(tree);
    pfjets_jetProbabilityBJetTag_handle.Init(tree);
    pfjets_simpleSecondaryVertexBJetTag_handle.Init(tree);
    pfjets_simpleSecondaryVertexHighEffBJetTag_handle.Init(tree);
    pfjets_simpleSecondaryVertexHighPurBJetTags_handle.Init(tree);
    pfjets_softElectronByIP3dBJetTag_handle.Init(tree);
    pfjets_softElectronByPtBJetTag_handle.Init(tree);
    pfjets_softElectronTag_handle.Init(tree);
    pfjets_softMuonBJetTag_handle.Init(tree);
    pfjets_softMuonByIP3dBJetTag_handle.Init(tree);
    pfjets_softMuonByPtBJetTag_handle.Init(tree);
    pfjets_trackCountingHighEffBJetTag_handle.Init(tree);
    pfjets_trackCountingHighPurBJetTag_handle.Init(tree);
    trkjets_combinedSecondaryVertexBJetTag_handle.Init(tree);
    trkjets_combinedSecondaryVertexMVABJetTag_handle.Init(tree);
    trkjets_jetBProbabilityBJetTag_handle.Init(tree);
    trkjets_jetProbabilityBJetTag_handle.Init(tree);
    trkjets_simpleSecondaryVertexBJetTag_handle.Init(tree);
    trkjets_simpleSecondaryVertexHighEffBJetTag_handle.Init(tree);
    trkjets_simpleSecondaryVertexHighPurBJetTags_handle.Init(tree);
    trkjets_softElectronByIP3dBJetTag_handle.Init(tree);
    trkjets_softElectronByPtBJetTag_handle.Init(tree);
    trkjets_softElectronTag_handle.Init(tree);
    trkjets_softMuonBJetTag_handle.Init(tree);
    trkjets_softMuonByIP3dBJetTag_handle.Init(tree);
    trkjets_softMuonByPtBJetTag_handle.Init(tree);
    trkjets_trackCountingHighEffBJetTag_handle.Init(tree);
    trkjets_trackCountingHighPurBJetTag_handle.Init(tree);
    evt_bs_covMatrix_handle.Init(tree);
    els_mc3dr_handle.Init(tree);
    els_mcdr_handle.Init(tree);
    jets_mc3dr_handle.Init(tree);
    jets_mcdr_handle.Init(tree);
    jets_mc_emEnergy_handle.Init(tree);
    jets_mc_gpdr_handle.Init(tree);
    jets_mc_hadEnergy_handle.Init(tree);
    jets_mc_invEnergy_handle.Init(tree);
    jets_mc_otherEnergy_handle.Init(tree);
    mus_mc3dr_handle.Init(tree);
    mus_mcdr_handle.Init(tree);
    pfjets_mc3dr_handle.Init(tree);
    pfjets_mcdr_handle.Init(tree);
    pfjets_mc_emEnergy_handle.Init(tree);
    pfjets_mc_gpdr_handle.Init(tree);
    pfjets_mc_hadEnergy_handle.Init(tree);
    pfjets_mc_invEnergy_handle.Init(tree);
    pfjets_mc_otherEnergy_handle.Init(tree);
    photons_mc3dr_handle.Init(tree);
    photons_mcdr_handle.Init(tree);
    trk_mc3dr_handle.Init(tree);
    trk_mcdr_handle.Init(tree);
    els_ecalJuraIso_handle.Init(tree);
    els_ecalJuraTowerIso_handle.Init(tree);
    els_hcalConeIso_handle.Init(tree);
    els_tkJuraIso_handle.Init(tree);
    els_jetdr_handle.Init(tree);
    els_musdr_handle.Init(tree);
    els_isoR03_chpf_radial_handle.Init(tree);
    els_isoR03_chpf_radialTight_handle.Init(tree);
    els_isoR03_chpf_radialTight_bv_handle.Init(tree);
    els_isoR03_chpf_radial_bv_handle.Init(tree);
    els_isoR03_empf_radial_handle.Init(tree);
    els_isoR03_empf_radialTight_handle.Init(tree);
    els_isoR03_empf_radialTight_bv_handle.Init(tree);
    els_isoR03_empf_radial_bv_handle.Init(tree);
    els_isoR03_nhpf_radial_handle.Init(tree);
    els_isoR03_nhpf_radialTight_handle.Init(tree);
    els_isoR03_nhpf_radialTight_bv_handle.Init(tree);
    els_isoR03_nhpf_radial_bv_handle.Init(tree);
    els_isoR03_pf2012n0p5_ch_handle.Init(tree);
    els_isoR03_pf2012n0p5_em_handle.Init(tree);
    els_isoR03_pf2012n0p5_nh_handle.Init(tree);
    els_isoR03_pf_radial_handle.Init(tree);
    els_isoR03_pf_radialTight_handle.Init(tree);
    els_isoR03_pf_radialTight_bv_handle.Init(tree);
    els_isoR03_pf_radial_bv_handle.Init(tree);
    els_chi2_handle.Init(tree);
    els_ckf_chi2_handle.Init(tree);
    els_ckf_ndof_handle.Init(tree);
    els_conv_dcot_handle.Init(tree);
    els_conv_dist_handle.Init(tree);
    els_conv_old_dcot_handle.Init(tree);
    els_conv_old_dist_handle.Init(tree);
    els_conv_old_radius_handle.Init(tree);
    els_conv_radius_handle.Init(tree);
    els_d0_handle.Init(tree);
    els_d0Err_handle.Init(tree);
    els_d0corr_handle.Init(tree);
    els_dEtaIn_handle.Init(tree);
    els_dEtaOut_handle.Init(tree);
    els_dPhiIn_handle.Init(tree);
    els_dPhiInPhiOut_handle.Init(tree);
    els_dPhiOut_handle.Init(tree);
    els_deltaEtaEleClusterTrackAtCalo_handle.Init(tree);
    els_deltaPhiEleClusterTrackAtCalo_handle.Init(tree);
    els_e1x5_handle.Init(tree);
    els_e2x5Max_handle.Init(tree);
    els_e3x3_handle.Init(tree);
    els_e5x5_handle.Init(tree);
    els_eMax_handle.Init(tree);
    els_eOverPIn_handle.Init(tree);
    els_eOverPOut_handle.Init(tree);
    els_eSC_handle.Init(tree);
    els_eSCPresh_handle.Init(tree);
    els_eSCRaw_handle.Init(tree);
    els_eSeed_handle.Init(tree);
    els_eSeedOverPIn_handle.Init(tree);
    els_eSeedOverPOut_handle.Init(tree);
    els_ecalEnergy_handle.Init(tree);
    els_ecalEnergyError_handle.Init(tree);
    els_ecalIso_handle.Init(tree);
    els_ecalIso04_handle.Init(tree);
    els_etaErr_handle.Init(tree);
    els_etaSC_handle.Init(tree);
    els_etaSCwidth_handle.Init(tree);
    els_fbrem_handle.Init(tree);
    els_hOverE_handle.Init(tree);
    els_hcalDepth1OverEcal_handle.Init(tree);
    els_hcalDepth1TowerSumEt_handle.Init(tree);
    els_hcalDepth1TowerSumEt04_handle.Init(tree);
    els_hcalDepth2OverEcal_handle.Init(tree);
    els_hcalDepth2TowerSumEt_handle.Init(tree);
    els_hcalDepth2TowerSumEt04_handle.Init(tree);
    els_hcalIso_handle.Init(tree);
    els_hcalIso04_handle.Init(tree);
    els_ip3d_handle.Init(tree);
    els_ip3derr_handle.Init(tree);
    els_iso03_pf_handle.Init(tree);
    els_iso03_pf2012_ch_handle.Init(tree);
    els_iso03_pf2012_em_handle.Init(tree);
    els_iso03_pf2012ext_ch_handle.Init(tree);
    els_iso03_pf2012ext_em_handle.Init(tree);
    els_iso03_pf2012ext_nh_handle.Init(tree);
    els_iso03_pf2012_nh_handle.Init(tree);
    els_iso03_pf_ch_handle.Init(tree);
    els_iso03_pf_gamma05_handle.Init(tree);
    els_iso03_pf_nhad05_handle.Init(tree);
    els_iso04_pf_handle.Init(tree);
    els_iso04_pf2012_ch_handle.Init(tree);
    els_iso04_pf2012_em_handle.Init(tree);
    els_iso04_pf2012ext_ch_handle.Init(tree);
    els_iso04_pf2012ext_em_handle.Init(tree);
    els_iso04_pf2012ext_nh_handle.Init(tree);
    els_iso04_pf2012_nh_handle.Init(tree);
    els_iso04_pf_ch_handle.Init(tree);
    els_iso04_pf_gamma05_handle.Init(tree);
    els_iso04_pf_nhad05_handle.Init(tree);
    els_layer1_charge_handle.Init(tree);
    els_lh_handle.Init(tree);
    els_mva_handle.Init(tree);
    els_ndof_handle.Init(tree);
    els_pfChargedHadronIso_handle.Init(tree);
    els_pfNeutralHadronIso_handle.Init(tree);
    els_pfPhotonIso_handle.Init(tree);
    els_phiErr_handle.Init(tree);
    els_phiSC_handle.Init(tree);
    els_phiSCwidth_handle.Init(tree);
    els_ptErr_handle.Init(tree);
    els_r9_handle.Init(tree);
    els_sigmaEtaEta_handle.Init(tree);
    els_sigmaIEtaIEta_handle.Init(tree);
    els_sigmaIEtaIEtaSC_handle.Init(tree);
    els_sigmaIEtaIPhi_handle.Init(tree);
    els_sigmaIPhiIPhi_handle.Init(tree);
    els_sigmaIPhiIPhiSC_handle.Init(tree);
    els_sigmaIphiIphi_handle.Init(tree);
    els_sigmaPhiPhi_handle.Init(tree);
    els_tkIso_handle.Init(tree);
    els_tkIso04_handle.Init(tree);
    els_trackMomentumError_handle.Init(tree);
    els_trkdr_handle.Init(tree);
    els_trkshFrac_handle.Init(tree);
    els_z0_handle.Init(tree);
    els_z0Err_handle.Init(tree);
    els_z0corr_handle.Init(tree);
    gsftrks_chi2_handle.Init(tree);
    gsftrks_d0_handle.Init(tree);
    gsftrks_d0Err_handle.Init(tree);
    gsftrks_d0corr_handle.Init(tree);
    gsftrks_d0corrPhi_handle.Init(tree);
    gsftrks_d0phiCov_handle.Init(tree);
    gsftrks_etaErr_handle.Init(tree);
    gsftrks_layer1_charge_handle.Init(tree);
    gsftrks_ndof_handle.Init(tree);
    gsftrks_phiErr_handle.Init(tree);
    gsftrks_ptErr_handle.Init(tree);
    gsftrks_z0_handle.Init(tree);
    gsftrks_z0Err_handle.Init(tree);
    gsftrks_z0corr_handle.Init(tree);
    hyp_Ht_handle.Init(tree);
    hyp_dPhi_nJet_metMuonJESCorr_handle.Init(tree);
    hyp_dPhi_nJet_muCorrMet_handle.Init(tree);
    hyp_dPhi_nJet_tcMet_handle.Init(tree);
    hyp_dPhi_nJet_unCorrMet_handle.Init(tree);
    hyp_ll_chi2_handle.Init(tree);
    hyp_ll_d0_handle.Init(tree);
    hyp_ll_d0Err_handle.Init(tree);
    hyp_ll_d0corr_handle.Init(tree);
    hyp_ll_dPhi_metMuonJESCorr_handle.Init(tree);
    hyp_ll_dPhi_muCorrMet_handle.Init(tree);
    hyp_ll_dPhi_tcMet_handle.Init(tree);
    hyp_ll_dPhi_unCorrMet_handle.Init(tree);
    hyp_ll_etaErr_handle.Init(tree);
    hyp_ll_ndof_handle.Init(tree);
    hyp_ll_phiErr_handle.Init(tree);
    hyp_ll_ptErr_handle.Init(tree);
    hyp_ll_z0_handle.Init(tree);
    hyp_ll_z0Err_handle.Init(tree);
    hyp_ll_z0corr_handle.Init(tree);
    hyp_lt_chi2_handle.Init(tree);
    hyp_lt_d0_handle.Init(tree);
    hyp_lt_d0Err_handle.Init(tree);
    hyp_lt_d0corr_handle.Init(tree);
    hyp_lt_dPhi_metMuonJESCorr_handle.Init(tree);
    hyp_lt_dPhi_muCorrMet_handle.Init(tree);
    hyp_lt_dPhi_tcMet_handle.Init(tree);
    hyp_lt_dPhi_unCorrMet_handle.Init(tree);
    hyp_lt_etaErr_handle.Init(tree);
    hyp_lt_ndof_handle.Init(tree);
    hyp_lt_phiErr_handle.Init(tree);
    hyp_lt_ptErr_handle.Init(tree);
    hyp_lt_z0_handle.Init(tree);
    hyp_lt_z0Err_handle.Init(tree);
    hyp_lt_z0corr_handle.Init(tree);
    hyp_mt2_metMuonJESCorr_handle.Init(tree);
    hyp_mt2_muCorrMet_handle.Init(tree);
    hyp_mt2_tcMet_handle.Init(tree);
    hyp_sumJetPt_handle.Init(tree);
    hyp_FVFit_chi2ndf_handle.Init(tree);
    hyp_FVFit_prob_handle.Init(tree);
    hyp_FVFit_v4cxx_handle.Init(tree);
    hyp_FVFit_v4cxy_handle.Init(tree);
    hyp_FVFit_v4cyy_handle.Init(tree);
    hyp_FVFit_v4czx_handle.Init(tree);
    hyp_FVFit_v4czy_handle.Init(tree);
    hyp_FVFit_v4czz_handle.Init(tree);
    jets_approximatefHPD_handle.Init(tree);
    jets_approximatefRBX_handle.Init(tree);
    jets_cor_handle.Init(tree);
    jets_corL1FastL2L3_handle.Init(tree);
    jets_corL1L2L3_handle.Init(tree);
    jets_emFrac_handle.Init(tree);
    jets_fHPD_handle.Init(tree);
    jets_fRBX_handle.Init(tree);
    jets_fSubDetector1_handle.Init(tree);
    jets_fSubDetector2_handle.Init(tree);
    jets_fSubDetector3_handle.Init(tree);
    jets_fSubDetector4_handle.Init(tree);
    jets_hitsInN90_handle.Init(tree);
    jets_n90Hits_handle.Init(tree);
    jets_nECALTowers_handle.Init(tree);
    jets_nHCALTowers_handle.Init(tree);
    jets_restrictedEMF_handle.Init(tree);
    mus_met_deltax_handle.Init(tree);
    mus_met_deltay_handle.Init(tree);
    mus_eledr_handle.Init(tree);
    mus_jetdr_handle.Init(tree);
    mus_isoR03_chpf_radial_handle.Init(tree);
    mus_isoR03_chpf_radialTight_handle.Init(tree);
    mus_isoR03_empf_radial_handle.Init(tree);
    mus_isoR03_empf_radialTight_handle.Init(tree);
    mus_isoR03_nhpf_radial_handle.Init(tree);
    mus_isoR03_nhpf_radialTight_handle.Init(tree);
    mus_isoR03_pf_radial_handle.Init(tree);
    mus_isoR03_pf_radialTight_handle.Init(tree);
    mus_backToBackCompat_handle.Init(tree);
    mus_caloCompatibility_handle.Init(tree);
    mus_chi2_handle.Init(tree);
    mus_chi2LocalMomentum_handle.Init(tree);
    mus_chi2LocalPosition_handle.Init(tree);
    mus_cosmicCompat_handle.Init(tree);
    mus_d0_handle.Init(tree);
    mus_d0Err_handle.Init(tree);
    mus_d0corr_handle.Init(tree);
    mus_e_em_handle.Init(tree);
    mus_e_emS9_handle.Init(tree);
    mus_e_had_handle.Init(tree);
    mus_e_hadS9_handle.Init(tree);
    mus_e_ho_handle.Init(tree);
    mus_e_hoS9_handle.Init(tree);
    mus_etaErr_handle.Init(tree);
    mus_gfit_chi2_handle.Init(tree);
    mus_gfit_d0_handle.Init(tree);
    mus_gfit_d0Err_handle.Init(tree);
    mus_gfit_d0corr_handle.Init(tree);
    mus_gfit_ndof_handle.Init(tree);
    mus_gfit_qoverp_handle.Init(tree);
    mus_gfit_qoverpError_handle.Init(tree);
    mus_gfit_z0_handle.Init(tree);
    mus_gfit_z0Err_handle.Init(tree);
    mus_gfit_z0corr_handle.Init(tree);
    mus_glbKink_handle.Init(tree);
    mus_glbTrackProbability_handle.Init(tree);
    mus_globalDeltaEtaPhi_handle.Init(tree);
    mus_ip3d_handle.Init(tree);
    mus_ip3derr_handle.Init(tree);
    mus_iso03_emEt_handle.Init(tree);
    mus_iso03_hadEt_handle.Init(tree);
    mus_iso03_hoEt_handle.Init(tree);
    mus_iso03_pf_handle.Init(tree);
    mus_iso03_sumPt_handle.Init(tree);
    mus_iso04_pf_handle.Init(tree);
    mus_iso05_emEt_handle.Init(tree);
    mus_iso05_hadEt_handle.Init(tree);
    mus_iso05_hoEt_handle.Init(tree);
    mus_iso05_sumPt_handle.Init(tree);
    mus_isoR03_pf_ChargedHadronPt_handle.Init(tree);
    mus_isoR03_pf_ChargedParticlePt_handle.Init(tree);
    mus_isoR03_pf_NeutralHadronEt_handle.Init(tree);
    mus_isoR03_pf_NeutralHadronEtHighThreshold_handle.Init(tree);
    mus_isoR03_pf_PUPt_handle.Init(tree);
    mus_isoR03_pf_PhotonEt_handle.Init(tree);
    mus_isoR03_pf_PhotonEtHighThreshold_handle.Init(tree);
    mus_isoR04_pf_ChargedHadronPt_handle.Init(tree);
    mus_isoR04_pf_ChargedParticlePt_handle.Init(tree);
    mus_isoR04_pf_NeutralHadronEt_handle.Init(tree);
    mus_isoR04_pf_NeutralHadronEtHighThreshold_handle.Init(tree);
    mus_isoR04_pf_PUPt_handle.Init(tree);
    mus_isoR04_pf_PhotonEt_handle.Init(tree);
    mus_isoR04_pf_PhotonEtHighThreshold_handle.Init(tree);
    mus_iso_ecalvetoDep_handle.Init(tree);
    mus_iso_hcalvetoDep_handle.Init(tree);
    mus_iso_hovetoDep_handle.Init(tree);
    mus_iso_trckvetoDep_handle.Init(tree);
    mus_localDistance_handle.Init(tree);
    mus_ndof_handle.Init(tree);
    mus_overlapCompat_handle.Init(tree);
    mus_pfdeltaP_handle.Init(tree);
    mus_pfecalE_handle.Init(tree);
    mus_pfhcalE_handle.Init(tree);
    mus_pfmva_emu_handle.Init(tree);
    mus_pfmva_epi_handle.Init(tree);
    mus_pfmva_nothing_gamma_handle.Init(tree);
    mus_pfmva_nothing_nh_handle.Init(tree);
    mus_pfmva_pimu_handle.Init(tree);
    mus_pfpS1E_handle.Init(tree);
    mus_pfpS2E_handle.Init(tree);
    mus_pfrawEcalE_handle.Init(tree);
    mus_pfrawHcalE_handle.Init(tree);
    mus_phiErr_handle.Init(tree);
    mus_ptErr_handle.Init(tree);
    mus_qoverp_handle.Init(tree);
    mus_qoverpError_handle.Init(tree);
    mus_segmCompatibility_handle.Init(tree);
    mus_staRelChi2_handle.Init(tree);
    mus_sta_chi2_handle.Init(tree);
    mus_sta_d0_handle.Init(tree);
    mus_sta_d0Err_handle.Init(tree);
    mus_sta_d0corr_handle.Init(tree);
    mus_sta_ndof_handle.Init(tree);
    mus_sta_qoverp_handle.Init(tree);
    mus_sta_qoverpError_handle.Init(tree);
    mus_sta_z0_handle.Init(tree);
    mus_sta_z0Err_handle.Init(tree);
    mus_sta_z0corr_handle.Init(tree);
    mus_timeAtIpInOut_handle.Init(tree);
    mus_timeAtIpInOutErr_handle.Init(tree);
    mus_timeAtIpOutIn_handle.Init(tree);
    mus_timeAtIpOutInErr_handle.Init(tree);
    mus_timeCompat_handle.Init(tree);
    mus_trkKink_handle.Init(tree);
    mus_trkRelChi2_handle.Init(tree);
    mus_vertexCompat_handle.Init(tree);
    mus_vertexphi_handle.Init(tree);
    mus_z0_handle.Init(tree);
    mus_z0Err_handle.Init(tree);
    mus_z0corr_handle.Init(tree);
    pfjets_mvavalue_handle.Init(tree);
    pfjets_full53xmva_beta_handle.Init(tree);
    pfjets_full53xmva_betaStar_handle.Init(tree);
    pfjets_full53xmva_d0_handle.Init(tree);
    pfjets_full53xmva_dRMean_handle.Init(tree);
    pfjets_full53xmva_dZ_handle.Init(tree);
    pfjets_full53xmva_frac01_handle.Init(tree);
    pfjets_full53xmva_frac02_handle.Init(tree);
    pfjets_full53xmva_frac03_handle.Init(tree);
    pfjets_full53xmva_frac04_handle.Init(tree);
    pfjets_full53xmva_frac05_handle.Init(tree);
    pfjets_full53xmva_nCharged_handle.Init(tree);
    pfjets_full53xmva_nNeutrals_handle.Init(tree);
    pfjets_full53xmva_nvtx_handle.Init(tree);
    pfjets_full53xmvavalue_handle.Init(tree);
    pfjets_full5xmvavalue_handle.Init(tree);
    trkjet_met_handle.Init(tree);
    trkjet_metPhi_handle.Init(tree);
    trkjet_sumet_handle.Init(tree);
    trk_met_handle.Init(tree);
    trk_metPhi_handle.Init(tree);
    trk_sumet_handle.Init(tree);
    pfcands_deltaP_handle.Init(tree);
    pfcands_ecalE_handle.Init(tree);
    pfcands_hcalE_handle.Init(tree);
    pfcands_mva_emu_handle.Init(tree);
    pfcands_mva_epi_handle.Init(tree);
    pfcands_mva_nothing_gamma_handle.Init(tree);
    pfcands_mva_nothing_nh_handle.Init(tree);
    pfcands_mva_pimu_handle.Init(tree);
    pfcands_pS1E_handle.Init(tree);
    pfcands_pS2E_handle.Init(tree);
    pfcands_rawEcalE_handle.Init(tree);
    pfcands_rawHcalE_handle.Init(tree);
    pfels_deltaP_handle.Init(tree);
    pfels_ecalE_handle.Init(tree);
    pfels_hcalE_handle.Init(tree);
    pfels_iso04ChargedHadrons_handle.Init(tree);
    pfels_iso04NeutralHadrons_handle.Init(tree);
    pfels_iso04Photons_handle.Init(tree);
    pfels_isoChargedHadrons_handle.Init(tree);
    pfels_isoNeutralHadrons_handle.Init(tree);
    pfels_isoPhotons_handle.Init(tree);
    pfels_mva_emu_handle.Init(tree);
    pfels_mva_epi_handle.Init(tree);
    pfels_mva_nothing_gamma_handle.Init(tree);
    pfels_mva_nothing_nh_handle.Init(tree);
    pfels_mva_pimu_handle.Init(tree);
    pfels_pS1E_handle.Init(tree);
    pfels_pS2E_handle.Init(tree);
    pfels_rawEcalE_handle.Init(tree);
    pfels_rawHcalE_handle.Init(tree);
    pfjets_area_handle.Init(tree);
    pfjets_chargedEmE_handle.Init(tree);
    pfjets_chargedHadronE_handle.Init(tree);
    pfjets_cor_handle.Init(tree);
    pfjets_corL1Fast_handle.Init(tree);
    pfjets_corL1FastL2L3_handle.Init(tree);
    pfjets_corL1FastL2L3residual_handle.Init(tree);
    pfjets_corL1L2L3_handle.Init(tree);
    pfjets_electronE_handle.Init(tree);
    pfjets_hfEmE_handle.Init(tree);
    pfjets_hfHadronE_handle.Init(tree);
    pfjets_muonE_handle.Init(tree);
    pfjets_neutralEmE_handle.Init(tree);
    pfjets_neutralHadronE_handle.Init(tree);
    pfjets_photonE_handle.Init(tree);
    pfmus_deltaP_handle.Init(tree);
    pfmus_ecalE_handle.Init(tree);
    pfmus_hcalE_handle.Init(tree);
    pfmus_iso04ChargedHadrons_handle.Init(tree);
    pfmus_iso04NeutralHadrons_handle.Init(tree);
    pfmus_iso04Photons_handle.Init(tree);
    pfmus_isoChargedHadrons_handle.Init(tree);
    pfmus_isoNeutralHadrons_handle.Init(tree);
    pfmus_isoPhotons_handle.Init(tree);
    pfmus_mva_emu_handle.Init(tree);
    pfmus_mva_epi_handle.Init(tree);
    pfmus_mva_nothing_gamma_handle.Init(tree);
    pfmus_mva_nothing_nh_handle.Init(tree);
    pfmus_mva_pimu_handle.Init(tree);
    pfmus_pS1E_handle.Init(tree);
    pfmus_pS2E_handle.Init(tree);
    pfmus_rawEcalE_handle.Init(tree);
    pfmus_rawHcalE_handle.Init(tree);
    taus_pf_againstElectronDeadECAL_handle.Init(tree);
    taus_pf_againstElectronLoose_handle.Init(tree);
    taus_pf_againstElectronLooseMVA2_handle.Init(tree);
    taus_pf_againstElectronLooseMVA3_handle.Init(tree);
    taus_pf_againstElectronMVA_handle.Init(tree);
    taus_pf_againstElectronMVA2category_handle.Init(tree);
    taus_pf_againstElectronMVA2raw_handle.Init(tree);
    taus_pf_againstElectronMVA3category_handle.Init(tree);
    taus_pf_againstElectronMVA3raw_handle.Init(tree);
    taus_pf_againstElectronMedium_handle.Init(tree);
    taus_pf_againstElectronMediumMVA2_handle.Init(tree);
    taus_pf_againstElectronMediumMVA3_handle.Init(tree);
    taus_pf_againstElectronTight_handle.Init(tree);
    taus_pf_againstElectronTightMVA2_handle.Init(tree);
    taus_pf_againstElectronTightMVA3_handle.Init(tree);
    taus_pf_againstElectronVLooseMVA2_handle.Init(tree);
    taus_pf_againstElectronVTightMVA3_handle.Init(tree);
    taus_pf_againstMuonLoose_handle.Init(tree);
    taus_pf_againstMuonLoose2_handle.Init(tree);
    taus_pf_againstMuonMedium_handle.Init(tree);
    taus_pf_againstMuonMedium2_handle.Init(tree);
    taus_pf_againstMuonTight_handle.Init(tree);
    taus_pf_againstMuonTight2_handle.Init(tree);
    taus_pf_byCombinedIsolationDeltaBetaCorrRaw_handle.Init(tree);
    taus_pf_byCombinedIsolationDeltaBetaCorrRaw3Hits_handle.Init(tree);
    taus_pf_byDecayModeFinding_handle.Init(tree);
    taus_pf_byIsolationMVA2raw_handle.Init(tree);
    taus_pf_byIsolationMVAraw_handle.Init(tree);
    taus_pf_byLooseCombinedIsolationDeltaBetaCorr_handle.Init(tree);
    taus_pf_byLooseCombinedIsolationDeltaBetaCorr3Hits_handle.Init(tree);
    taus_pf_byLooseIsolationMVA_handle.Init(tree);
    taus_pf_byLooseIsolationMVA2_handle.Init(tree);
    taus_pf_byMediumCombinedIsolationDeltaBetaCorr_handle.Init(tree);
    taus_pf_byMediumCombinedIsolationDeltaBetaCorr3Hits_handle.Init(tree);
    taus_pf_byMediumIsolationMVA_handle.Init(tree);
    taus_pf_byMediumIsolationMVA2_handle.Init(tree);
    taus_pf_byTightCombinedIsolationDeltaBetaCorr_handle.Init(tree);
    taus_pf_byTightCombinedIsolationDeltaBetaCorr3Hits_handle.Init(tree);
    taus_pf_byTightIsolationMVA_handle.Init(tree);
    taus_pf_byTightIsolationMVA2_handle.Init(tree);
    taus_pf_byVLooseCombinedIsolationDeltaBetaCorr_handle.Init(tree);
    photons_e1x5_handle.Init(tree);
    photons_e2x5Max_handle.Init(tree);
    photons_e3x3_handle.Init(tree);
    photons_e5x5_handle.Init(tree);
    photons_ecalIso03_handle.Init(tree);
    photons_ecalIso04_handle.Init(tree);
    photons_hOverE_handle.Init(tree);
    photons_hcalDepth1TowerSumEtBcConeDR03_handle.Init(tree);
    photons_hcalDepth1TowerSumEtBcConeDR04_handle.Init(tree);
    photons_hcalDepth2TowerSumEtBcConeDR03_handle.Init(tree);
    photons_hcalDepth2TowerSumEtBcConeDR04_handle.Init(tree);
    photons_hcalIso03_handle.Init(tree);
    photons_hcalIso04_handle.Init(tree);
    photons_hcalTowerSumEtBcConeDR03_handle.Init(tree);
    photons_hcalTowerSumEtBcConeDR04_handle.Init(tree);
    photons_ntkIsoHollow03_handle.Init(tree);
    photons_ntkIsoHollow04_handle.Init(tree);
    photons_ntkIsoSolid03_handle.Init(tree);
    photons_ntkIsoSolid04_handle.Init(tree);
    photons_sigmaEtaEta_handle.Init(tree);
    photons_sigmaIEtaIEta_handle.Init(tree);
    photons_swissSeed_handle.Init(tree);
    photons_tkIsoHollow03_handle.Init(tree);
    photons_tkIsoHollow04_handle.Init(tree);
    photons_tkIsoSolid03_handle.Init(tree);
    photons_tkIsoSolid04_handle.Init(tree);
    puInfo_trueNumInteractions_handle.Init(tree);
    convs_chi2_handle.Init(tree);
    convs_dl_handle.Init(tree);
    convs_ndof_handle.Init(tree);
    sparm_values_handle.Init(tree);
    scs_clustersSize_handle.Init(tree);
    scs_crystalsSize_handle.Init(tree);
    scs_e1x3_handle.Init(tree);
    scs_e1x5_handle.Init(tree);
    scs_e2nd_handle.Init(tree);
    scs_e2x2_handle.Init(tree);
    scs_e2x5Max_handle.Init(tree);
    scs_e3x1_handle.Init(tree);
    scs_e3x2_handle.Init(tree);
    scs_e3x3_handle.Init(tree);
    scs_e4x4_handle.Init(tree);
    scs_e5x5_handle.Init(tree);
    scs_eMax_handle.Init(tree);
    scs_eSeed_handle.Init(tree);
    scs_energy_handle.Init(tree);
    scs_eta_handle.Init(tree);
    scs_hoe_handle.Init(tree);
    scs_laserCorMax_handle.Init(tree);
    scs_laserCorMean_handle.Init(tree);
    scs_laserCorSeed_handle.Init(tree);
    scs_phi_handle.Init(tree);
    scs_preshowerEnergy_handle.Init(tree);
    scs_rawEnergy_handle.Init(tree);
    scs_sigmaEtaEta_handle.Init(tree);
    scs_sigmaEtaPhi_handle.Init(tree);
    scs_sigmaIEtaIEta_handle.Init(tree);
    scs_sigmaIEtaIEtaSC_handle.Init(tree);
    scs_sigmaIEtaIPhi_handle.Init(tree);
    scs_sigmaIEtaIPhiSC_handle.Init(tree);
    scs_sigmaIPhiIPhi_handle.Init(tree);
    scs_sigmaIPhiIPhiSC_handle.Init(tree);
    scs_sigmaPhiPhi_handle.Init(tree);
    scs_timeSeed_handle.Init(tree);
    svs_anglePV_handle.Init(tree);
    svs_chi2_handle.Init(tree);
    svs_dist3Dsig_handle.Init(tree);
    svs_dist3Dval_handle.Init(tree);
    svs_distXYsig_handle.Init(tree);
    svs_distXYval_handle.Init(tree);
    svs_ndof_handle.Init(tree);
    svs_prob_handle.Init(tree);
    svs_xError_handle.Init(tree);
    svs_yError_handle.Init(tree);
    svs_zError_handle.Init(tree);
    mus_tcmet_deltax_handle.Init(tree);
    mus_tcmet_deltay_handle.Init(tree);
    pfcands_dzpv_handle.Init(tree);
    pfcands_trkiso_handle.Init(tree);
    trks_chi2_handle.Init(tree);
    trks_d0_handle.Init(tree);
    trks_d0Err_handle.Init(tree);
    trks_d0corr_handle.Init(tree);
    trks_d0corrPhi_handle.Init(tree);
    trks_d0phiCov_handle.Init(tree);
    trks_etaErr_handle.Init(tree);
    trks_layer1_charge_handle.Init(tree);
    trks_ndof_handle.Init(tree);
    trks_phiErr_handle.Init(tree);
    trks_ptErr_handle.Init(tree);
    trks_validFraction_handle.Init(tree);
    trks_z0_handle.Init(tree);
    trks_z0Err_handle.Init(tree);
    trks_z0corr_handle.Init(tree);
    trkjets_cor_handle.Init(tree);
    trks_d0Errvtx_handle.Init(tree);
    trks_d0vtx_handle.Init(tree);
    vtxs_chi2_handle.Init(tree);
    vtxs_ndof_handle.Init(tree);
    vtxs_sumpt_handle.Init(tree);
    vtxs_xError_handle.Init(tree);
    vtxs_yError_handle.Init(tree);
    vtxs_zError_handle.Init(tree);
    bsvtxs_chi2_handle.Init(tree);
    bsvtxs_ndof_handle.Init(tree);
    bsvtxs_sumpt_handle.Init(tree);
    bsvtxs_xError_handle.Init(tree);
    bsvtxs_yError_handle.Init(tree);
    bsvtxs_zError_handle.Init(tree);
    els_convs_dcot_handle.Init(tree);
    els_convs_dist_handle.Init(tree);
    els_convs_radius_handle.Init(tree);
    mus_stationShowerDeltaR_handle.Init(tree);
    mus_stationShowerSizeT_handle.Init(tree);
    puInfo_instLumi_handle.Init(tree);
    puInfo_sump_highpt_handle.Init(tree);
    puInfo_sumpt_lowpt_handle.Init(tree);
    puInfo_zpositions_handle.Init(tree);
    vtxs_covMatrix_handle.Init(tree);
    bsvtxs_covMatrix_handle.Init(tree);
    evt_cscLooseHaloId_handle.Init(tree);
    evt_cscTightHaloId_handle.Init(tree);
    evt_ecalLooseHaloId_handle.Init(tree);
    evt_ecalTightHaloId_handle.Init(tree);
    evt_extremeTightHaloId_handle.Init(tree);
    evt_globalLooseHaloId_handle.Init(tree);
    evt_globalTightHaloId_handle.Init(tree);
    evt_hcalLooseHaloId_handle.Init(tree);
    evt_hcalTightHaloId_handle.Init(tree);
    evt_looseHaloId_handle.Init(tree);
    evt_nHaloLikeTracks_handle.Init(tree);
    evt_nHaloTriggerCandidates_handle.Init(tree);
    evt_tightHaloId_handle.Init(tree);
    evt_bsType_handle.Init(tree);
    evt_bunchCrossing_handle.Init(tree);
    evt_experimentType_handle.Init(tree);
    evt_isRealData_handle.Init(tree);
    evt_orbitNumber_handle.Init(tree);
    evt_storeNumber_handle.Init(tree);
    hcalnoise_GetRecHitCount_handle.Init(tree);
    hcalnoise_GetRecHitCount15_handle.Init(tree);
    hcalnoise_maxHPDHits_handle.Init(tree);
    hcalnoise_maxHPDNoOtherHits_handle.Init(tree);
    hcalnoise_maxRBXHits_handle.Init(tree);
    hcalnoise_maxZeros_handle.Init(tree);
    hcalnoise_noiseFilterStatus_handle.Init(tree);
    hcalnoise_noiseType_handle.Init(tree);
    hcalnoise_num10GeVHits_handle.Init(tree);
    hcalnoise_num25GeVHits_handle.Init(tree);
    hcalnoise_numFlatNoiseChannels_handle.Init(tree);
    hcalnoise_numIsolatedNoiseChannels_handle.Init(tree);
    hcalnoise_numProblematicRBXs_handle.Init(tree);
    hcalnoise_numSpikeNoiseChannels_handle.Init(tree);
    hcalnoise_numTS4TS5NoiseChannels_handle.Init(tree);
    hcalnoise_numTriangleNoiseChannels_handle.Init(tree);
    hcalnoise_passHighLevelNoiseFilter_handle.Init(tree);
    hcalnoise_passLooseNoiseFilter_handle.Init(tree);
    hcalnoise_passTightNoiseFilter_handle.Init(tree);
    l1_nemiso_handle.Init(tree);
    l1_nemnoiso_handle.Init(tree);
    l1_njetsc_handle.Init(tree);
    l1_njetsf_handle.Init(tree);
    l1_njetst_handle.Init(tree);
    l1_nmus_handle.Init(tree);
    ls_lumiSecQual_handle.Init(tree);
    pdfinfo_id1_handle.Init(tree);
    pdfinfo_id2_handle.Init(tree);
    sparm_subProcessId_handle.Init(tree);
    evt_ecaliPhiSuspects_handle.Init(tree);
    evt_globaliPhiSuspects_handle.Init(tree);
    evt_hcaliPhiSuspects_handle.Init(tree);
    els_mc3_id_handle.Init(tree);
    els_mc3idx_handle.Init(tree);
    els_mc3_motherid_handle.Init(tree);
    els_mc3_motheridx_handle.Init(tree);
    els_mc_id_handle.Init(tree);
    els_mcidx_handle.Init(tree);
    els_mc_motherid_handle.Init(tree);
    jets_mc3_id_handle.Init(tree);
    jets_mc3idx_handle.Init(tree);
    jets_mc_gpidx_handle.Init(tree);
    jets_mc_id_handle.Init(tree);
    jets_mcidx_handle.Init(tree);
    jets_mc_motherid_handle.Init(tree);
    mus_mc3_id_handle.Init(tree);
    mus_mc3idx_handle.Init(tree);
    mus_mc3_motherid_handle.Init(tree);
    mus_mc3_motheridx_handle.Init(tree);
    mus_mc_id_handle.Init(tree);
    mus_mcidx_handle.Init(tree);
    mus_mc_motherid_handle.Init(tree);
    pfjets_mc3_id_handle.Init(tree);
    pfjets_mc3idx_handle.Init(tree);
    pfjets_mc_gpidx_handle.Init(tree);
    pfjets_mc_id_handle.Init(tree);
    pfjets_mcidx_handle.Init(tree);
    pfjets_mc_motherid_handle.Init(tree);
    photons_mc3_id_handle.Init(tree);
    photons_mc3idx_handle.Init(tree);
    photons_mc3_motherid_handle.Init(tree);
    photons_mc3_motheridx_handle.Init(tree);
    photons_mc_id_handle.Init(tree);
    photons_mcidx_handle.Init(tree);
    photons_mc_motherid_handle.Init(tree);
    trk_mc3_id_handle.Init(tree);
    trk_mc3idx_handle.Init(tree);
    trk_mc3_motherid_handle.Init(tree);
    trk_mc3_motheridx_handle.Init(tree);
    trk_mc_id_handle.Init(tree);
    trk_mcidx_handle.Init(tree);
    trk_mc_motherid_handle.Init(tree);
    els_closestJet_handle.Init(tree);
    els_closestMuon_handle.Init(tree);
    els_pfelsidx_handle.Init(tree);
    els_category_handle.Init(tree);
    els_charge_handle.Init(tree);
    els_ckf_laywithmeas_handle.Init(tree);
    els_class_handle.Init(tree);
    els_conv_delMissHits_handle.Init(tree);
    els_conv_flag_handle.Init(tree);
    els_conv_gsftkidx_handle.Init(tree);
    els_conv_old_delMissHits_handle.Init(tree);
    els_conv_old_flag_handle.Init(tree);
    els_conv_old_gsftkidx_handle.Init(tree);
    els_conv_old_tkidx_handle.Init(tree);
    els_conv_tkidx_handle.Init(tree);
    els_exp_innerlayers_handle.Init(tree);
    els_exp_outerlayers_handle.Init(tree);
    els_fiduciality_handle.Init(tree);
    els_gsftrkidx_handle.Init(tree);
    els_layer1_det_handle.Init(tree);
    els_layer1_layer_handle.Init(tree);
    els_layer1_sizerphi_handle.Init(tree);
    els_layer1_sizerz_handle.Init(tree);
    els_lostHits_handle.Init(tree);
    els_lost_pixelhits_handle.Init(tree);
    els_nSeed_handle.Init(tree);
    els_sccharge_handle.Init(tree);
    els_scindex_handle.Init(tree);
    els_trk_charge_handle.Init(tree);
    els_trkidx_handle.Init(tree);
    els_type_handle.Init(tree);
    els_validHits_handle.Init(tree);
    els_valid_pixelhits_handle.Init(tree);
    genps_id_handle.Init(tree);
    genps_id_mother_handle.Init(tree);
    genps_status_handle.Init(tree);
    gsftrks_charge_handle.Init(tree);
    gsftrks_exp_innerlayers_handle.Init(tree);
    gsftrks_exp_outerlayers_handle.Init(tree);
    gsftrks_layer1_det_handle.Init(tree);
    gsftrks_layer1_layer_handle.Init(tree);
    gsftrks_layer1_sizerphi_handle.Init(tree);
    gsftrks_layer1_sizerz_handle.Init(tree);
    gsftrks_lostHits_handle.Init(tree);
    gsftrks_lost_pixelhits_handle.Init(tree);
    gsftrks_nlayers_handle.Init(tree);
    gsftrks_nlayers3D_handle.Init(tree);
    gsftrks_nlayersLost_handle.Init(tree);
    gsftrks_validHits_handle.Init(tree);
    gsftrks_valid_pixelhits_handle.Init(tree);
    hyp_ll_charge_handle.Init(tree);
    hyp_ll_id_handle.Init(tree);
    hyp_ll_index_handle.Init(tree);
    hyp_ll_lostHits_handle.Init(tree);
    hyp_ll_validHits_handle.Init(tree);
    hyp_lt_charge_handle.Init(tree);
    hyp_lt_id_handle.Init(tree);
    hyp_lt_index_handle.Init(tree);
    hyp_lt_lostHits_handle.Init(tree);
    hyp_lt_validHits_handle.Init(tree);
    hyp_njets_handle.Init(tree);
    hyp_nojets_handle.Init(tree);
    hyp_type_handle.Init(tree);
    hyp_FVFit_ndf_handle.Init(tree);
    hyp_FVFit_status_handle.Init(tree);
    hyp_ll_mc_id_handle.Init(tree);
    hyp_ll_mc_motherid_handle.Init(tree);
    hyp_lt_mc_id_handle.Init(tree);
    hyp_lt_mc_motherid_handle.Init(tree);
    pfjets_mcflavorAlgo_handle.Init(tree);
    pfjets_mcflavorPhys_handle.Init(tree);
    jets_closestElectron_handle.Init(tree);
    jets_closestMuon_handle.Init(tree);
    l1_emiso_ieta_handle.Init(tree);
    l1_emiso_iphi_handle.Init(tree);
    l1_emiso_rawId_handle.Init(tree);
    l1_emiso_type_handle.Init(tree);
    l1_emnoiso_ieta_handle.Init(tree);
    l1_emnoiso_iphi_handle.Init(tree);
    l1_emnoiso_rawId_handle.Init(tree);
    l1_emnoiso_type_handle.Init(tree);
    l1_jetsc_ieta_handle.Init(tree);
    l1_jetsc_iphi_handle.Init(tree);
    l1_jetsc_rawId_handle.Init(tree);
    l1_jetsc_type_handle.Init(tree);
    l1_jetsf_ieta_handle.Init(tree);
    l1_jetsf_iphi_handle.Init(tree);
    l1_jetsf_rawId_handle.Init(tree);
    l1_jetsf_type_handle.Init(tree);
    l1_jetst_ieta_handle.Init(tree);
    l1_jetst_iphi_handle.Init(tree);
    l1_jetst_rawId_handle.Init(tree);
    l1_jetst_type_handle.Init(tree);
    l1_mus_flags_handle.Init(tree);
    l1_mus_q_handle.Init(tree);
    l1_mus_qual_handle.Init(tree);
    l1_mus_qualFlags_handle.Init(tree);
    mus_met_flag_handle.Init(tree);
    mus_closestEle_handle.Init(tree);
    mus_closestJet_handle.Init(tree);
    mus_pfmusidx_handle.Init(tree);
    mus_charge_handle.Init(tree);
    mus_gfit_validHits_handle.Init(tree);
    mus_gfit_validSTAHits_handle.Init(tree);
    mus_gfit_validSiHits_handle.Init(tree);
    mus_goodmask_handle.Init(tree);
    mus_iso03_ntrk_handle.Init(tree);
    mus_iso05_ntrk_handle.Init(tree);
    mus_lostHits_handle.Init(tree);
    mus_muonBestTrackType_handle.Init(tree);
    mus_nOverlaps_handle.Init(tree);
    mus_nmatches_handle.Init(tree);
    mus_numberOfMatchedStations_handle.Init(tree);
    mus_overlap0_handle.Init(tree);
    mus_overlap1_handle.Init(tree);
    mus_pfcharge_handle.Init(tree);
    mus_pfflag_handle.Init(tree);
    mus_pfparticleId_handle.Init(tree);
    mus_pid_PFMuon_handle.Init(tree);
    mus_pid_TM2DCompatibilityLoose_handle.Init(tree);
    mus_pid_TM2DCompatibilityTight_handle.Init(tree);
    mus_pid_TMLastStationLoose_handle.Init(tree);
    mus_pid_TMLastStationTight_handle.Init(tree);
    mus_sta_validHits_handle.Init(tree);
    mus_timeDirection_handle.Init(tree);
    mus_timeNumStationsUsed_handle.Init(tree);
    mus_trk_charge_handle.Init(tree);
    mus_trkidx_handle.Init(tree);
    mus_type_handle.Init(tree);
    mus_validHits_handle.Init(tree);
    pfcands_charge_handle.Init(tree);
    pfcands_flag_handle.Init(tree);
    pfcands_particleId_handle.Init(tree);
    pfcands_pfelsidx_handle.Init(tree);
    pfcands_pfmusidx_handle.Init(tree);
    pfcands_trkidx_handle.Init(tree);
    pfcands_vtxidx_handle.Init(tree);
    pfels_elsidx_handle.Init(tree);
    pfels_charge_handle.Init(tree);
    pfels_flag_handle.Init(tree);
    pfels_particleId_handle.Init(tree);
    pfjets_chargedHadronMultiplicity_handle.Init(tree);
    pfjets_chargedMultiplicity_handle.Init(tree);
    pfjets_electronMultiplicity_handle.Init(tree);
    pfjets_hfEmMultiplicity_handle.Init(tree);
    pfjets_hfHadronMultiplicity_handle.Init(tree);
    pfjets_muonMultiplicity_handle.Init(tree);
    pfjets_neutralHadronMultiplicity_handle.Init(tree);
    pfjets_neutralMultiplicity_handle.Init(tree);
    pfjets_photonMultiplicity_handle.Init(tree);
    pfmus_musidx_handle.Init(tree);
    pfmus_charge_handle.Init(tree);
    pfmus_flag_handle.Init(tree);
    pfmus_particleId_handle.Init(tree);
    taus_pf_charge_handle.Init(tree);
    taus_pf_pfjetIndex_handle.Init(tree);
    photons_fiduciality_handle.Init(tree);
    photons_scindex_handle.Init(tree);
    puInfo_bunchCrossing_handle.Init(tree);
    puInfo_nPUvertices_handle.Init(tree);
    convs_algo_handle.Init(tree);
    convs_isConverted_handle.Init(tree);
    convs_quality_handle.Init(tree);
    scs_detIdSeed_handle.Init(tree);
    scs_elsidx_handle.Init(tree);
    scs_severitySeed_handle.Init(tree);
    svs_isKs_handle.Init(tree);
    svs_isLambda_handle.Init(tree);
    svs_mc3_id_handle.Init(tree);
    svs_nTrks_handle.Init(tree);
    mus_tcmet_flag_handle.Init(tree);
    trks_algo_handle.Init(tree);
    trks_charge_handle.Init(tree);
    trks_exp_innerlayers_handle.Init(tree);
    trks_exp_outerlayers_handle.Init(tree);
    trks_layer1_det_handle.Init(tree);
    trks_layer1_layer_handle.Init(tree);
    trks_layer1_sizerphi_handle.Init(tree);
    trks_layer1_sizerz_handle.Init(tree);
    trks_lostHits_handle.Init(tree);
    trks_lost_pixelhits_handle.Init(tree);
    trks_nLoops_handle.Init(tree);
    trks_nlayers_handle.Init(tree);
    trks_nlayers3D_handle.Init(tree);
    trks_nlayersLost_handle.Init(tree);
    trks_pvidx0_handle.Init(tree);
    trks_pvidx1_handle.Init(tree);
    trks_qualityMask_handle.Init(tree);
    trks_validHits_handle.Init(tree);
    trks_valid_pixelhits_handle.Init(tree);
    trks_elsidx_handle.Init(tree);
    trk_musidx_handle.Init(tree);
    trkjets_ntrks_handle.Init(tree);
    trkjets_vtxs_idx_handle.Init(tree);
    vtxs_isFake_handle.Init(tree);
    vtxs_isValid_handle.Init(tree);
    vtxs_tracksSize_handle.Init(tree);
    bsvtxs_isFake_handle.Init(tree);
    bsvtxs_isValid_handle.Init(tree);
    bsvtxs_tracksSize_handle.Init(tree);
    els_convs_delMissHits_handle.Init(tree);
    els_convs_flag_handle.Init(tree);
    els_convs_gsftkidx_handle.Init(tree);
    els_convs_tkidx_handle.Init(tree);
    genps_lepdaughter_id_handle.Init(tree);
    genps_lepdaughter_idx_handle.Init(tree);
    hlt_trigObjs_id_handle.Init(tree);
    hyp_jets_idx_handle.Init(tree);
    hyp_other_jets_idx_handle.Init(tree);
    mus_nStationCorrelatedHits_handle.Init(tree);
    mus_nStationHits_handle.Init(tree);
    pfjets_pfcandIndicies_handle.Init(tree);
    taus_pf_pfcandIndicies_handle.Init(tree);
    puInfo_ntrks_highpt_handle.Init(tree);
    puInfo_ntrks_lowpt_handle.Init(tree);
    convs_nHitsBeforeVtx_handle.Init(tree);
    convs_tkalgo_handle.Init(tree);
    convs_tkidx_handle.Init(tree);
    els_HLT_Ele17_Ele8_L1sL1DoubleEG137_version_handle.Init(tree);
    els_HLT_Ele17_Ele8_LeadingLeg_version_handle.Init(tree);
    els_HLT_Ele17_Ele8_Mass50_LeadingLeg_version_handle.Init(tree);
    els_HLT_Ele17_Ele8_Mass50_TrailingLeg_version_handle.Init(tree);
    els_HLT_Ele17_Ele8_TrailingLeg_version_handle.Init(tree);
    els_HLT_Ele17_Ele8_version_handle.Init(tree);
    els_HLT_Ele20_SC4_Mass50_LeadingLeg_version_handle.Init(tree);
    els_HLT_Ele20_SC4_Mass50_TrailingLeg_version_handle.Init(tree);
    els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_version_handle.Init(tree);
    els_HLT_Ele27_WP80_version_handle.Init(tree);
    els_HLT_Ele32_SC17_Mass50_LeadingLeg_version_handle.Init(tree);
    els_HLT_Ele32_SC17_Mass50_TrailingLeg_version_handle.Init(tree);
    els_HLT_Mu17_Ele8_TrailingLeg_version_handle.Init(tree);
    els_HLT_Mu17_Ele8_version_handle.Init(tree);
    els_HLT_Mu8_Ele17_version_handle.Init(tree);
    evt_nels_handle.Init(tree);
    evt_detectorStatus_handle.Init(tree);
    evt_event_handle.Init(tree);
    evt_lumiBlock_handle.Init(tree);
    evt_run_handle.Init(tree);
    genps_flavorHistoryFilterResult_handle.Init(tree);
    evt_ngenjets_handle.Init(tree);
    genps_signalProcessID_handle.Init(tree);
    evt_njets_handle.Init(tree);
    l1_bits1_handle.Init(tree);
    l1_bits2_handle.Init(tree);
    l1_bits3_handle.Init(tree);
    l1_bits4_handle.Init(tree);
    l1_techbits1_handle.Init(tree);
    l1_techbits2_handle.Init(tree);
    ls_lsNumber_handle.Init(tree);
    ls_numOrbit_handle.Init(tree);
    ls_startOrbit_handle.Init(tree);
    mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_version_handle.Init(tree);
    mus_HLT_IsoMu24_eta2p1_version_handle.Init(tree);
    mus_HLT_Mu17_Ele8_LeadingLeg_version_handle.Init(tree);
    mus_HLT_Mu17_Ele8_version_handle.Init(tree);
    mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_version_handle.Init(tree);
    mus_HLT_Mu17_Mu8_LeadingLeg_version_handle.Init(tree);
    mus_HLT_Mu17_Mu8_TrailingLeg_version_handle.Init(tree);
    mus_HLT_Mu17_Mu8_version_handle.Init(tree);
    mus_HLT_Mu17_TkMu8_LeadingLeg_version_handle.Init(tree);
    mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_version_handle.Init(tree);
    mus_HLT_Mu17_TkMu8_TrailingLeg_version_handle.Init(tree);
    mus_HLT_Mu17_TkMu8_version_handle.Init(tree);
    mus_HLT_Mu8_Ele17_TrailingLeg_version_handle.Init(tree);
    mus_HLT_Mu8_Ele17_version_handle.Init(tree);
    evt_nphotons_handle.Init(tree);
    evt_ecalRecoStatus_handle.Init(tree);
    evt_nscs_handle.Init(tree);
    evt_ntrkjets_handle.Init(tree);
    evt_nvtxs_handle.Init(tree);
    evt_nbsvtxs_handle.Init(tree);
    els_HLT_Ele17_Ele8_handle.Init(tree);
    els_HLT_Ele17_Ele8_L1sL1DoubleEG137_handle.Init(tree);
    els_HLT_Ele17_Ele8_LeadingLeg_handle.Init(tree);
    els_HLT_Ele17_Ele8_Mass50_LeadingLeg_handle.Init(tree);
    els_HLT_Ele17_Ele8_Mass50_TrailingLeg_handle.Init(tree);
    els_HLT_Ele17_Ele8_TrailingLeg_handle.Init(tree);
    els_HLT_Ele20_SC4_Mass50_LeadingLeg_handle.Init(tree);
    els_HLT_Ele20_SC4_Mass50_TrailingLeg_handle.Init(tree);
    els_HLT_Ele27_WP80_handle.Init(tree);
    els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_handle.Init(tree);
    els_HLT_Ele32_SC17_Mass50_LeadingLeg_handle.Init(tree);
    els_HLT_Ele32_SC17_Mass50_TrailingLeg_handle.Init(tree);
    els_HLT_Mu17_Ele8_handle.Init(tree);
    els_HLT_Mu17_Ele8_TrailingLeg_handle.Init(tree);
    els_HLT_Mu8_Ele17_handle.Init(tree);
    els_id2012ext_loose_handle.Init(tree);
    els_id2012ext_medium_handle.Init(tree);
    els_id2012ext_tight_handle.Init(tree);
    els_id2012ext_veto_handle.Init(tree);
    els_id2012_loose_handle.Init(tree);
    els_id2012_medium_handle.Init(tree);
    els_id2012_tight_handle.Init(tree);
    els_id2012_veto_handle.Init(tree);
    hlt_prescales_handle.Init(tree);
    l1_prescales_handle.Init(tree);
    l1_techtrigprescales_handle.Init(tree);
    mus_HLT_IsoMu24_eta2p1_handle.Init(tree);
    mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_handle.Init(tree);
    mus_HLT_Mu17_Ele8_handle.Init(tree);
    mus_HLT_Mu17_Ele8_LeadingLeg_handle.Init(tree);
    mus_HLT_Mu17_Mu8_handle.Init(tree);
    mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_handle.Init(tree);
    mus_HLT_Mu17_Mu8_LeadingLeg_handle.Init(tree);
    mus_HLT_Mu17_Mu8_TrailingLeg_handle.Init(tree);
    mus_HLT_Mu17_TkMu8_handle.Init(tree);
    mus_HLT_Mu17_TkMu8_LeadingLeg_handle.Init(tree);
    mus_HLT_Mu17_TkMu8_TrailingLeg_handle.Init(tree);
    mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_handle.Init(tree);
    mus_HLT_Mu8_Ele17_handle.Init(tree);
    mus_HLT_Mu8_Ele17_TrailingLeg_handle.Init(tree);
    evt_timestamp_handle.Init(tree);
    evt_nEvts_handle.Init(tree);
    evt_filt_eff_handle.Init(tree);

}

void CMS2::Init(TTree* const tree)
{
    Init(*tree);
}

void CMS2::GetEntry(const unsigned int entry)
{
    hlt_bits_handle.GetEntry(entry);
    evt_CMS2tag_handle.GetEntry(entry);
    evt_dataset_handle.GetEntry(entry);
    hlt_trigNames_handle.GetEntry(entry);
    l1_techtrigNames_handle.GetEntry(entry);
    l1_trigNames_handle.GetEntry(entry);
    evt_errCategory_handle.GetEntry(entry);
    evt_errModule_handle.GetEntry(entry);
    evt_errSeverity_handle.GetEntry(entry);
    sparm_comment_handle.GetEntry(entry);
    sparm_names_handle.GetEntry(entry);
    evt_eventHasHalo_handle.GetEntry(entry);
    hcalnoise_HasBadRBXTS4TS5_handle.GetEntry(entry);
    ls_isValid_handle.GetEntry(entry);
    filt_ecalBE_handle.GetEntry(entry);
    filt_ecalDR_handle.GetEntry(entry);
    filt_ecalLaser_handle.GetEntry(entry);
    filt_ecalTP_handle.GetEntry(entry);
    filt_eeBadSc_handle.GetEntry(entry);
    filt_greedyMuon_handle.GetEntry(entry);
    filt_hcalLaser_handle.GetEntry(entry);
    filt_inconsistentMuon_handle.GetEntry(entry);
    filt_jetIDFailure_handle.GetEntry(entry);
    filt_multiEvent_handle.GetEntry(entry);
    filt_trackingFailure_handle.GetEntry(entry);
    evt_hbheFilter_handle.GetEntry(entry);
    els_conv_vtx_flag_handle.GetEntry(entry);
    els_passingMvaPreselection_handle.GetEntry(entry);
    els_passingPflowPreselection_handle.GetEntry(entry);
    mus_isRPCMuon_handle.GetEntry(entry);
    mus_tightMatch_handle.GetEntry(entry);
    mus_updatedSta_handle.GetEntry(entry);
    pfcands_isMuIso_handle.GetEntry(entry);
    photons_haspixelSeed_handle.GetEntry(entry);
    jets_closestElectron_DR_handle.GetEntry(entry);
    jets_closestMuon_DR_handle.GetEntry(entry);
    evt_bs_Xwidth_handle.GetEntry(entry);
    evt_bs_XwidthErr_handle.GetEntry(entry);
    evt_bs_Ywidth_handle.GetEntry(entry);
    evt_bs_YwidthErr_handle.GetEntry(entry);
    evt_bs_dxdz_handle.GetEntry(entry);
    evt_bs_dxdzErr_handle.GetEntry(entry);
    evt_bs_dydz_handle.GetEntry(entry);
    evt_bs_dydzErr_handle.GetEntry(entry);
    evt_bs_sigmaZ_handle.GetEntry(entry);
    evt_bs_sigmaZErr_handle.GetEntry(entry);
    evt_bs_xErr_handle.GetEntry(entry);
    evt_bs_yErr_handle.GetEntry(entry);
    evt_bs_zErr_handle.GetEntry(entry);
    evt_bField_handle.GetEntry(entry);
    evt_rho_handle.GetEntry(entry);
    evt_rhoJEC_handle.GetEntry(entry);
    evt_fixgrid_all_rho_handle.GetEntry(entry);
    evt_fixgridfastjet_all_rho_handle.GetEntry(entry);
    evt_kfactor_handle.GetEntry(entry);
    evt_scale1fb_handle.GetEntry(entry);
    evt_xsec_excl_handle.GetEntry(entry);
    evt_xsec_incl_handle.GetEntry(entry);
    gen_met_handle.GetEntry(entry);
    gen_metPhi_handle.GetEntry(entry);
    genps_alphaQCD_handle.GetEntry(entry);
    genps_pthat_handle.GetEntry(entry);
    genps_qScale_handle.GetEntry(entry);
    genps_weight_handle.GetEntry(entry);
    gen_sumEt_handle.GetEntry(entry);
    hcalnoise_GetRecHitEnergy_handle.GetEntry(entry);
    hcalnoise_GetRecHitEnergy15_handle.GetEntry(entry);
    hcalnoise_GetTotalCalibCharge_handle.GetEntry(entry);
    hcalnoise_TS4TS5NoiseSumE_handle.GetEntry(entry);
    hcalnoise_TS4TS5NoiseSumEt_handle.GetEntry(entry);
    hcalnoise_eventChargeFraction_handle.GetEntry(entry);
    hcalnoise_eventEMEnergy_handle.GetEntry(entry);
    hcalnoise_eventEMFraction_handle.GetEntry(entry);
    hcalnoise_eventHadEnergy_handle.GetEntry(entry);
    hcalnoise_eventTrackEnergy_handle.GetEntry(entry);
    hcalnoise_flatNoiseSumE_handle.GetEntry(entry);
    hcalnoise_flatNoiseSumEt_handle.GetEntry(entry);
    hcalnoise_isolatedNoiseSumE_handle.GetEntry(entry);
    hcalnoise_isolatedNoiseSumEt_handle.GetEntry(entry);
    hcalnoise_max10GeVHitTime_handle.GetEntry(entry);
    hcalnoise_max25GeVHitTime_handle.GetEntry(entry);
    hcalnoise_maxE10TS_handle.GetEntry(entry);
    hcalnoise_maxE2Over10TS_handle.GetEntry(entry);
    hcalnoise_maxE2TS_handle.GetEntry(entry);
    hcalnoise_min10GeVHitTime_handle.GetEntry(entry);
    hcalnoise_min25GeVHitTime_handle.GetEntry(entry);
    hcalnoise_minE10TS_handle.GetEntry(entry);
    hcalnoise_minE2Over10TS_handle.GetEntry(entry);
    hcalnoise_minE2TS_handle.GetEntry(entry);
    hcalnoise_minHPDEMF_handle.GetEntry(entry);
    hcalnoise_minRBXEMF_handle.GetEntry(entry);
    hcalnoise_rms10GeVHitTime_handle.GetEntry(entry);
    hcalnoise_rms25GeVHitTime_handle.GetEntry(entry);
    hcalnoise_spikeNoiseSumE_handle.GetEntry(entry);
    hcalnoise_spikeNoiseSumEt_handle.GetEntry(entry);
    hcalnoise_triangleNoiseSumE_handle.GetEntry(entry);
    hcalnoise_triangleNoiseSumEt_handle.GetEntry(entry);
    evt_kt6calo_central_rho_handle.GetEntry(entry);
    evt_kt6calo_muhlt_rho_handle.GetEntry(entry);
    evt_kt6calo_rho_handle.GetEntry(entry);
    evt_kt6pf_ctrChargedPU_rho_handle.GetEntry(entry);
    evt_kt6pf_ctrNeutral_rho_handle.GetEntry(entry);
    evt_kt6pf_ctrNeutralTight_rho_handle.GetEntry(entry);
    evt_kt6pf_foregiso_rho_handle.GetEntry(entry);
    l1_met_etTot_handle.GetEntry(entry);
    l1_met_met_handle.GetEntry(entry);
    l1_mht_htTot_handle.GetEntry(entry);
    l1_mht_mht_handle.GetEntry(entry);
    ls_avgInsDelLumi_handle.GetEntry(entry);
    ls_avgInsDelLumiErr_handle.GetEntry(entry);
    ls_avgInsRecLumi_handle.GetEntry(entry);
    ls_avgInsRecLumiErr_handle.GetEntry(entry);
    ls_deadFrac_handle.GetEntry(entry);
    ls_intgDelLumi_handle.GetEntry(entry);
    ls_intgRecLumi_handle.GetEntry(entry);
    ls_lumiSectionLength_handle.GetEntry(entry);
    evt_ecalendcapm_met_handle.GetEntry(entry);
    evt_ecalendcapm_metPhi_handle.GetEntry(entry);
    evt_ecalendcapp_met_handle.GetEntry(entry);
    evt_ecalendcapp_metPhi_handle.GetEntry(entry);
    evt_ecalmet_handle.GetEntry(entry);
    evt_ecalmetPhi_handle.GetEntry(entry);
    evt_endcapm_met_handle.GetEntry(entry);
    evt_endcapm_metPhi_handle.GetEntry(entry);
    evt_endcapp_met_handle.GetEntry(entry);
    evt_endcapp_metPhi_handle.GetEntry(entry);
    evt_hcalendcapm_met_handle.GetEntry(entry);
    evt_hcalendcapm_metPhi_handle.GetEntry(entry);
    evt_hcalendcapp_met_handle.GetEntry(entry);
    evt_hcalendcapp_metPhi_handle.GetEntry(entry);
    evt_hcalmet_handle.GetEntry(entry);
    evt_hcalmetPhi_handle.GetEntry(entry);
    evt_met_handle.GetEntry(entry);
    evt_met_EtGt3_handle.GetEntry(entry);
    evt_metHO_handle.GetEntry(entry);
    evt_metHOPhi_handle.GetEntry(entry);
    evt_metHOSig_handle.GetEntry(entry);
    evt_metMuonCorr_handle.GetEntry(entry);
    evt_metMuonCorrPhi_handle.GetEntry(entry);
    evt_metMuonCorrSig_handle.GetEntry(entry);
    evt_metMuonJESCorr_handle.GetEntry(entry);
    evt_metMuonJESCorrPhi_handle.GetEntry(entry);
    evt_metMuonJESCorrSig_handle.GetEntry(entry);
    evt_metNoHF_handle.GetEntry(entry);
    evt_metNoHFHO_handle.GetEntry(entry);
    evt_metNoHFHOPhi_handle.GetEntry(entry);
    evt_metNoHFHOSig_handle.GetEntry(entry);
    evt_metNoHFPhi_handle.GetEntry(entry);
    evt_metNoHFSig_handle.GetEntry(entry);
    evt_metOpt_handle.GetEntry(entry);
    evt_metOptHO_handle.GetEntry(entry);
    evt_metOptHOPhi_handle.GetEntry(entry);
    evt_metOptHOSig_handle.GetEntry(entry);
    evt_metOptNoHF_handle.GetEntry(entry);
    evt_metOptNoHFHO_handle.GetEntry(entry);
    evt_metOptNoHFHOPhi_handle.GetEntry(entry);
    evt_metOptNoHFHOSig_handle.GetEntry(entry);
    evt_metOptNoHFPhi_handle.GetEntry(entry);
    evt_metOptNoHFSig_handle.GetEntry(entry);
    evt_metOptPhi_handle.GetEntry(entry);
    evt_metOptSig_handle.GetEntry(entry);
    evt_metPhi_handle.GetEntry(entry);
    evt_metPhi_EtGt3_handle.GetEntry(entry);
    evt_metSig_handle.GetEntry(entry);
    evt_sumet_handle.GetEntry(entry);
    evt_sumet_EtGt3_handle.GetEntry(entry);
    evt_sumetHO_handle.GetEntry(entry);
    evt_sumetMuonCorr_handle.GetEntry(entry);
    evt_sumetMuonJESCorr_handle.GetEntry(entry);
    evt_sumetNoHF_handle.GetEntry(entry);
    evt_sumetNoHFHO_handle.GetEntry(entry);
    evt_sumetOpt_handle.GetEntry(entry);
    evt_sumetOptHO_handle.GetEntry(entry);
    evt_sumetOptNoHF_handle.GetEntry(entry);
    evt_sumetOptNoHFHO_handle.GetEntry(entry);
    pdfinfo_pdf1_handle.GetEntry(entry);
    pdfinfo_pdf2_handle.GetEntry(entry);
    pdfinfo_scale_handle.GetEntry(entry);
    pdfinfo_x1_handle.GetEntry(entry);
    pdfinfo_x2_handle.GetEntry(entry);
    evt_fixgrid_rho_all_handle.GetEntry(entry);
    evt_fixgrid_rho_ctr_handle.GetEntry(entry);
    evt_fixgrid_rho_fwd_handle.GetEntry(entry);
    evt_pfmet_handle.GetEntry(entry);
    evt_pfmetPhi_handle.GetEntry(entry);
    evt_pfmetPhi_type1cor_handle.GetEntry(entry);
    evt_pfmetSig_handle.GetEntry(entry);
    evt_pfmetSignificance_handle.GetEntry(entry);
    evt_pfmet_type1cor_handle.GetEntry(entry);
    evt_pfsumet_handle.GetEntry(entry);
    sparm_filterEfficiency_handle.GetEntry(entry);
    sparm_pdfScale_handle.GetEntry(entry);
    sparm_pdfWeight1_handle.GetEntry(entry);
    sparm_pdfWeight2_handle.GetEntry(entry);
    sparm_weight_handle.GetEntry(entry);
    sparm_xsec_handle.GetEntry(entry);
    evt_pf_tcmet_handle.GetEntry(entry);
    evt_pf_tcmetPhi_handle.GetEntry(entry);
    evt_pf_tcmetSig_handle.GetEntry(entry);
    evt_pf_tcsumet_handle.GetEntry(entry);
    evt_tcmet_handle.GetEntry(entry);
    evt_tcmetPhi_handle.GetEntry(entry);
    evt_tcmetSig_handle.GetEntry(entry);
    evt_tcsumet_handle.GetEntry(entry);
    evt_ww_rho_act_handle.GetEntry(entry);
    evt_ww_rho_handle.GetEntry(entry);
    evt_ww_rho_rnd_handle.GetEntry(entry);
    evt_ww_rho_vor_handle.GetEntry(entry);
    evt_bsp4_handle.GetEntry(entry);
    l1_met_p4_handle.GetEntry(entry);
    l1_mht_p4_handle.GetEntry(entry);
    els_mc_motherp4_handle.GetEntry(entry);
    els_mc_p4_handle.GetEntry(entry);
    jets_mc_gp_p4_handle.GetEntry(entry);
    jets_mc_motherp4_handle.GetEntry(entry);
    jets_mc_p4_handle.GetEntry(entry);
    mus_mc_motherp4_handle.GetEntry(entry);
    mus_mc_p4_handle.GetEntry(entry);
    pfjets_mc_gp_p4_handle.GetEntry(entry);
    pfjets_mc_motherp4_handle.GetEntry(entry);
    pfjets_mc_p4_handle.GetEntry(entry);
    photons_mc_motherp4_handle.GetEntry(entry);
    photons_mc_p4_handle.GetEntry(entry);
    trk_mcp4_handle.GetEntry(entry);
    els_conv_pos_p4_handle.GetEntry(entry);
    els_inner_position_handle.GetEntry(entry);
    els_outer_position_handle.GetEntry(entry);
    els_p4_handle.GetEntry(entry);
    els_p4In_handle.GetEntry(entry);
    els_p4Out_handle.GetEntry(entry);
    els_trk_p4_handle.GetEntry(entry);
    els_vertex_p4_handle.GetEntry(entry);
    genjets_p4_handle.GetEntry(entry);
    genps_p4_handle.GetEntry(entry);
    genps_prod_vtx_handle.GetEntry(entry);
    gsftrks_inner_position_handle.GetEntry(entry);
    gsftrks_outer_p4_handle.GetEntry(entry);
    gsftrks_outer_position_handle.GetEntry(entry);
    gsftrks_p4_handle.GetEntry(entry);
    gsftrks_vertex_p4_handle.GetEntry(entry);
    hyp_ll_p4_handle.GetEntry(entry);
    hyp_ll_trk_p4_handle.GetEntry(entry);
    hyp_lt_p4_handle.GetEntry(entry);
    hyp_lt_trk_p4_handle.GetEntry(entry);
    hyp_p4_handle.GetEntry(entry);
    hyp_FVFit_p4_handle.GetEntry(entry);
    hyp_FVFit_v4_handle.GetEntry(entry);
    hyp_ll_mc_p4_handle.GetEntry(entry);
    hyp_lt_mc_p4_handle.GetEntry(entry);
    jets_p4_handle.GetEntry(entry);
    jets_vertex_p4_handle.GetEntry(entry);
    l1_emiso_p4_handle.GetEntry(entry);
    l1_emnoiso_p4_handle.GetEntry(entry);
    l1_jetsc_p4_handle.GetEntry(entry);
    l1_jetsf_p4_handle.GetEntry(entry);
    l1_jetst_p4_handle.GetEntry(entry);
    l1_mus_p4_handle.GetEntry(entry);
    mus_ecalpos_p4_handle.GetEntry(entry);
    mus_fitpicky_p4_handle.GetEntry(entry);
    mus_fittev_p4_handle.GetEntry(entry);
    mus_fittpfms_p4_handle.GetEntry(entry);
    mus_gfit_outerPos_p4_handle.GetEntry(entry);
    mus_gfit_p4_handle.GetEntry(entry);
    mus_gfit_vertex_p4_handle.GetEntry(entry);
    mus_p4_handle.GetEntry(entry);
    mus_pfp4_handle.GetEntry(entry);
    mus_pfposAtEcal_p4_handle.GetEntry(entry);
    mus_sta_p4_handle.GetEntry(entry);
    mus_sta_vertex_p4_handle.GetEntry(entry);
    mus_trk_p4_handle.GetEntry(entry);
    mus_vertex_p4_handle.GetEntry(entry);
    pfcands_p4_handle.GetEntry(entry);
    pfcands_posAtEcal_p4_handle.GetEntry(entry);
    pfels_p4_handle.GetEntry(entry);
    pfels_posAtEcal_p4_handle.GetEntry(entry);
    pfjets_p4_handle.GetEntry(entry);
    pfmus_p4_handle.GetEntry(entry);
    pfmus_posAtEcal_p4_handle.GetEntry(entry);
    taus_pf_p4_handle.GetEntry(entry);
    photons_p4_handle.GetEntry(entry);
    convs_refitPairMom_p4_handle.GetEntry(entry);
    convs_vtxpos_handle.GetEntry(entry);
    scs_p4_handle.GetEntry(entry);
    scs_pos_p4_handle.GetEntry(entry);
    scs_vtx_p4_handle.GetEntry(entry);
    svs_flight_handle.GetEntry(entry);
    svs_mc3_p4_handle.GetEntry(entry);
    svs_p4_handle.GetEntry(entry);
    svs_position_handle.GetEntry(entry);
    svs_refitp4_handle.GetEntry(entry);
    trks_inner_position_handle.GetEntry(entry);
    trks_outer_p4_handle.GetEntry(entry);
    trks_outer_position_handle.GetEntry(entry);
    trks_trk_p4_handle.GetEntry(entry);
    trks_vertex_p4_handle.GetEntry(entry);
    trkjets_p4_handle.GetEntry(entry);
    vtxs_position_handle.GetEntry(entry);
    bsvtxs_position_handle.GetEntry(entry);
    els_convs_pos_p4_handle.GetEntry(entry);
    genps_lepdaughter_p4_handle.GetEntry(entry);
    hlt_trigObjs_p4_handle.GetEntry(entry);
    hyp_jets_p4_handle.GetEntry(entry);
    hyp_other_jets_p4_handle.GetEntry(entry);
    jpts_combinedSecondaryVertexBJetTag_handle.GetEntry(entry);
    jpts_combinedSecondaryVertexMVABJetTag_handle.GetEntry(entry);
    jpts_jetBProbabilityBJetTag_handle.GetEntry(entry);
    jpts_jetProbabilityBJetTag_handle.GetEntry(entry);
    jpts_simpleSecondaryVertexBJetTag_handle.GetEntry(entry);
    jpts_simpleSecondaryVertexHighEffBJetTag_handle.GetEntry(entry);
    jpts_simpleSecondaryVertexHighPurBJetTags_handle.GetEntry(entry);
    jpts_softElectronByIP3dBJetTag_handle.GetEntry(entry);
    jpts_softElectronByPtBJetTag_handle.GetEntry(entry);
    jpts_softElectronTag_handle.GetEntry(entry);
    jpts_softMuonBJetTag_handle.GetEntry(entry);
    jpts_softMuonByIP3dBJetTag_handle.GetEntry(entry);
    jpts_softMuonByPtBJetTag_handle.GetEntry(entry);
    jpts_trackCountingHighEffBJetTag_handle.GetEntry(entry);
    jpts_trackCountingHighPurBJetTag_handle.GetEntry(entry);
    jets_combinedSecondaryVertexBJetTag_handle.GetEntry(entry);
    jets_combinedSecondaryVertexMVABJetTag_handle.GetEntry(entry);
    jets_jetBProbabilityBJetTag_handle.GetEntry(entry);
    jets_jetProbabilityBJetTag_handle.GetEntry(entry);
    jets_simpleSecondaryVertexBJetTag_handle.GetEntry(entry);
    jets_simpleSecondaryVertexHighEffBJetTag_handle.GetEntry(entry);
    jets_simpleSecondaryVertexHighPurBJetTags_handle.GetEntry(entry);
    jets_softElectronByIP3dBJetTag_handle.GetEntry(entry);
    jets_softElectronByPtBJetTag_handle.GetEntry(entry);
    jets_softElectronTag_handle.GetEntry(entry);
    jets_softMuonBJetTag_handle.GetEntry(entry);
    jets_softMuonByIP3dBJetTag_handle.GetEntry(entry);
    jets_softMuonByPtBJetTag_handle.GetEntry(entry);
    jets_trackCountingHighEffBJetTag_handle.GetEntry(entry);
    jets_trackCountingHighPurBJetTag_handle.GetEntry(entry);
    pfjets_combinedSecondaryVertexBJetTag_handle.GetEntry(entry);
    pfjets_combinedSecondaryVertexMVABJetTag_handle.GetEntry(entry);
    pfjets_jetBProbabilityBJetTag_handle.GetEntry(entry);
    pfjets_jetProbabilityBJetTag_handle.GetEntry(entry);
    pfjets_simpleSecondaryVertexBJetTag_handle.GetEntry(entry);
    pfjets_simpleSecondaryVertexHighEffBJetTag_handle.GetEntry(entry);
    pfjets_simpleSecondaryVertexHighPurBJetTags_handle.GetEntry(entry);
    pfjets_softElectronByIP3dBJetTag_handle.GetEntry(entry);
    pfjets_softElectronByPtBJetTag_handle.GetEntry(entry);
    pfjets_softElectronTag_handle.GetEntry(entry);
    pfjets_softMuonBJetTag_handle.GetEntry(entry);
    pfjets_softMuonByIP3dBJetTag_handle.GetEntry(entry);
    pfjets_softMuonByPtBJetTag_handle.GetEntry(entry);
    pfjets_trackCountingHighEffBJetTag_handle.GetEntry(entry);
    pfjets_trackCountingHighPurBJetTag_handle.GetEntry(entry);
    trkjets_combinedSecondaryVertexBJetTag_handle.GetEntry(entry);
    trkjets_combinedSecondaryVertexMVABJetTag_handle.GetEntry(entry);
    trkjets_jetBProbabilityBJetTag_handle.GetEntry(entry);
    trkjets_jetProbabilityBJetTag_handle.GetEntry(entry);
    trkjets_simpleSecondaryVertexBJetTag_handle.GetEntry(entry);
    trkjets_simpleSecondaryVertexHighEffBJetTag_handle.GetEntry(entry);
    trkjets_simpleSecondaryVertexHighPurBJetTags_handle.GetEntry(entry);
    trkjets_softElectronByIP3dBJetTag_handle.GetEntry(entry);
    trkjets_softElectronByPtBJetTag_handle.GetEntry(entry);
    trkjets_softElectronTag_handle.GetEntry(entry);
    trkjets_softMuonBJetTag_handle.GetEntry(entry);
    trkjets_softMuonByIP3dBJetTag_handle.GetEntry(entry);
    trkjets_softMuonByPtBJetTag_handle.GetEntry(entry);
    trkjets_trackCountingHighEffBJetTag_handle.GetEntry(entry);
    trkjets_trackCountingHighPurBJetTag_handle.GetEntry(entry);
    evt_bs_covMatrix_handle.GetEntry(entry);
    els_mc3dr_handle.GetEntry(entry);
    els_mcdr_handle.GetEntry(entry);
    jets_mc3dr_handle.GetEntry(entry);
    jets_mcdr_handle.GetEntry(entry);
    jets_mc_emEnergy_handle.GetEntry(entry);
    jets_mc_gpdr_handle.GetEntry(entry);
    jets_mc_hadEnergy_handle.GetEntry(entry);
    jets_mc_invEnergy_handle.GetEntry(entry);
    jets_mc_otherEnergy_handle.GetEntry(entry);
    mus_mc3dr_handle.GetEntry(entry);
    mus_mcdr_handle.GetEntry(entry);
    pfjets_mc3dr_handle.GetEntry(entry);
    pfjets_mcdr_handle.GetEntry(entry);
    pfjets_mc_emEnergy_handle.GetEntry(entry);
    pfjets_mc_gpdr_handle.GetEntry(entry);
    pfjets_mc_hadEnergy_handle.GetEntry(entry);
    pfjets_mc_invEnergy_handle.GetEntry(entry);
    pfjets_mc_otherEnergy_handle.GetEntry(entry);
    photons_mc3dr_handle.GetEntry(entry);
    photons_mcdr_handle.GetEntry(entry);
    trk_mc3dr_handle.GetEntry(entry);
    trk_mcdr_handle.GetEntry(entry);
    els_ecalJuraIso_handle.GetEntry(entry);
    els_ecalJuraTowerIso_handle.GetEntry(entry);
    els_hcalConeIso_handle.GetEntry(entry);
    els_tkJuraIso_handle.GetEntry(entry);
    els_jetdr_handle.GetEntry(entry);
    els_musdr_handle.GetEntry(entry);
    els_isoR03_chpf_radial_handle.GetEntry(entry);
    els_isoR03_chpf_radialTight_handle.GetEntry(entry);
    els_isoR03_chpf_radialTight_bv_handle.GetEntry(entry);
    els_isoR03_chpf_radial_bv_handle.GetEntry(entry);
    els_isoR03_empf_radial_handle.GetEntry(entry);
    els_isoR03_empf_radialTight_handle.GetEntry(entry);
    els_isoR03_empf_radialTight_bv_handle.GetEntry(entry);
    els_isoR03_empf_radial_bv_handle.GetEntry(entry);
    els_isoR03_nhpf_radial_handle.GetEntry(entry);
    els_isoR03_nhpf_radialTight_handle.GetEntry(entry);
    els_isoR03_nhpf_radialTight_bv_handle.GetEntry(entry);
    els_isoR03_nhpf_radial_bv_handle.GetEntry(entry);
    els_isoR03_pf2012n0p5_ch_handle.GetEntry(entry);
    els_isoR03_pf2012n0p5_em_handle.GetEntry(entry);
    els_isoR03_pf2012n0p5_nh_handle.GetEntry(entry);
    els_isoR03_pf_radial_handle.GetEntry(entry);
    els_isoR03_pf_radialTight_handle.GetEntry(entry);
    els_isoR03_pf_radialTight_bv_handle.GetEntry(entry);
    els_isoR03_pf_radial_bv_handle.GetEntry(entry);
    els_chi2_handle.GetEntry(entry);
    els_ckf_chi2_handle.GetEntry(entry);
    els_ckf_ndof_handle.GetEntry(entry);
    els_conv_dcot_handle.GetEntry(entry);
    els_conv_dist_handle.GetEntry(entry);
    els_conv_old_dcot_handle.GetEntry(entry);
    els_conv_old_dist_handle.GetEntry(entry);
    els_conv_old_radius_handle.GetEntry(entry);
    els_conv_radius_handle.GetEntry(entry);
    els_d0_handle.GetEntry(entry);
    els_d0Err_handle.GetEntry(entry);
    els_d0corr_handle.GetEntry(entry);
    els_dEtaIn_handle.GetEntry(entry);
    els_dEtaOut_handle.GetEntry(entry);
    els_dPhiIn_handle.GetEntry(entry);
    els_dPhiInPhiOut_handle.GetEntry(entry);
    els_dPhiOut_handle.GetEntry(entry);
    els_deltaEtaEleClusterTrackAtCalo_handle.GetEntry(entry);
    els_deltaPhiEleClusterTrackAtCalo_handle.GetEntry(entry);
    els_e1x5_handle.GetEntry(entry);
    els_e2x5Max_handle.GetEntry(entry);
    els_e3x3_handle.GetEntry(entry);
    els_e5x5_handle.GetEntry(entry);
    els_eMax_handle.GetEntry(entry);
    els_eOverPIn_handle.GetEntry(entry);
    els_eOverPOut_handle.GetEntry(entry);
    els_eSC_handle.GetEntry(entry);
    els_eSCPresh_handle.GetEntry(entry);
    els_eSCRaw_handle.GetEntry(entry);
    els_eSeed_handle.GetEntry(entry);
    els_eSeedOverPIn_handle.GetEntry(entry);
    els_eSeedOverPOut_handle.GetEntry(entry);
    els_ecalEnergy_handle.GetEntry(entry);
    els_ecalEnergyError_handle.GetEntry(entry);
    els_ecalIso_handle.GetEntry(entry);
    els_ecalIso04_handle.GetEntry(entry);
    els_etaErr_handle.GetEntry(entry);
    els_etaSC_handle.GetEntry(entry);
    els_etaSCwidth_handle.GetEntry(entry);
    els_fbrem_handle.GetEntry(entry);
    els_hOverE_handle.GetEntry(entry);
    els_hcalDepth1OverEcal_handle.GetEntry(entry);
    els_hcalDepth1TowerSumEt_handle.GetEntry(entry);
    els_hcalDepth1TowerSumEt04_handle.GetEntry(entry);
    els_hcalDepth2OverEcal_handle.GetEntry(entry);
    els_hcalDepth2TowerSumEt_handle.GetEntry(entry);
    els_hcalDepth2TowerSumEt04_handle.GetEntry(entry);
    els_hcalIso_handle.GetEntry(entry);
    els_hcalIso04_handle.GetEntry(entry);
    els_ip3d_handle.GetEntry(entry);
    els_ip3derr_handle.GetEntry(entry);
    els_iso03_pf_handle.GetEntry(entry);
    els_iso03_pf2012_ch_handle.GetEntry(entry);
    els_iso03_pf2012_em_handle.GetEntry(entry);
    els_iso03_pf2012ext_ch_handle.GetEntry(entry);
    els_iso03_pf2012ext_em_handle.GetEntry(entry);
    els_iso03_pf2012ext_nh_handle.GetEntry(entry);
    els_iso03_pf2012_nh_handle.GetEntry(entry);
    els_iso03_pf_ch_handle.GetEntry(entry);
    els_iso03_pf_gamma05_handle.GetEntry(entry);
    els_iso03_pf_nhad05_handle.GetEntry(entry);
    els_iso04_pf_handle.GetEntry(entry);
    els_iso04_pf2012_ch_handle.GetEntry(entry);
    els_iso04_pf2012_em_handle.GetEntry(entry);
    els_iso04_pf2012ext_ch_handle.GetEntry(entry);
    els_iso04_pf2012ext_em_handle.GetEntry(entry);
    els_iso04_pf2012ext_nh_handle.GetEntry(entry);
    els_iso04_pf2012_nh_handle.GetEntry(entry);
    els_iso04_pf_ch_handle.GetEntry(entry);
    els_iso04_pf_gamma05_handle.GetEntry(entry);
    els_iso04_pf_nhad05_handle.GetEntry(entry);
    els_layer1_charge_handle.GetEntry(entry);
    els_lh_handle.GetEntry(entry);
    els_mva_handle.GetEntry(entry);
    els_ndof_handle.GetEntry(entry);
    els_pfChargedHadronIso_handle.GetEntry(entry);
    els_pfNeutralHadronIso_handle.GetEntry(entry);
    els_pfPhotonIso_handle.GetEntry(entry);
    els_phiErr_handle.GetEntry(entry);
    els_phiSC_handle.GetEntry(entry);
    els_phiSCwidth_handle.GetEntry(entry);
    els_ptErr_handle.GetEntry(entry);
    els_r9_handle.GetEntry(entry);
    els_sigmaEtaEta_handle.GetEntry(entry);
    els_sigmaIEtaIEta_handle.GetEntry(entry);
    els_sigmaIEtaIEtaSC_handle.GetEntry(entry);
    els_sigmaIEtaIPhi_handle.GetEntry(entry);
    els_sigmaIPhiIPhi_handle.GetEntry(entry);
    els_sigmaIPhiIPhiSC_handle.GetEntry(entry);
    els_sigmaIphiIphi_handle.GetEntry(entry);
    els_sigmaPhiPhi_handle.GetEntry(entry);
    els_tkIso_handle.GetEntry(entry);
    els_tkIso04_handle.GetEntry(entry);
    els_trackMomentumError_handle.GetEntry(entry);
    els_trkdr_handle.GetEntry(entry);
    els_trkshFrac_handle.GetEntry(entry);
    els_z0_handle.GetEntry(entry);
    els_z0Err_handle.GetEntry(entry);
    els_z0corr_handle.GetEntry(entry);
    gsftrks_chi2_handle.GetEntry(entry);
    gsftrks_d0_handle.GetEntry(entry);
    gsftrks_d0Err_handle.GetEntry(entry);
    gsftrks_d0corr_handle.GetEntry(entry);
    gsftrks_d0corrPhi_handle.GetEntry(entry);
    gsftrks_d0phiCov_handle.GetEntry(entry);
    gsftrks_etaErr_handle.GetEntry(entry);
    gsftrks_layer1_charge_handle.GetEntry(entry);
    gsftrks_ndof_handle.GetEntry(entry);
    gsftrks_phiErr_handle.GetEntry(entry);
    gsftrks_ptErr_handle.GetEntry(entry);
    gsftrks_z0_handle.GetEntry(entry);
    gsftrks_z0Err_handle.GetEntry(entry);
    gsftrks_z0corr_handle.GetEntry(entry);
    hyp_Ht_handle.GetEntry(entry);
    hyp_dPhi_nJet_metMuonJESCorr_handle.GetEntry(entry);
    hyp_dPhi_nJet_muCorrMet_handle.GetEntry(entry);
    hyp_dPhi_nJet_tcMet_handle.GetEntry(entry);
    hyp_dPhi_nJet_unCorrMet_handle.GetEntry(entry);
    hyp_ll_chi2_handle.GetEntry(entry);
    hyp_ll_d0_handle.GetEntry(entry);
    hyp_ll_d0Err_handle.GetEntry(entry);
    hyp_ll_d0corr_handle.GetEntry(entry);
    hyp_ll_dPhi_metMuonJESCorr_handle.GetEntry(entry);
    hyp_ll_dPhi_muCorrMet_handle.GetEntry(entry);
    hyp_ll_dPhi_tcMet_handle.GetEntry(entry);
    hyp_ll_dPhi_unCorrMet_handle.GetEntry(entry);
    hyp_ll_etaErr_handle.GetEntry(entry);
    hyp_ll_ndof_handle.GetEntry(entry);
    hyp_ll_phiErr_handle.GetEntry(entry);
    hyp_ll_ptErr_handle.GetEntry(entry);
    hyp_ll_z0_handle.GetEntry(entry);
    hyp_ll_z0Err_handle.GetEntry(entry);
    hyp_ll_z0corr_handle.GetEntry(entry);
    hyp_lt_chi2_handle.GetEntry(entry);
    hyp_lt_d0_handle.GetEntry(entry);
    hyp_lt_d0Err_handle.GetEntry(entry);
    hyp_lt_d0corr_handle.GetEntry(entry);
    hyp_lt_dPhi_metMuonJESCorr_handle.GetEntry(entry);
    hyp_lt_dPhi_muCorrMet_handle.GetEntry(entry);
    hyp_lt_dPhi_tcMet_handle.GetEntry(entry);
    hyp_lt_dPhi_unCorrMet_handle.GetEntry(entry);
    hyp_lt_etaErr_handle.GetEntry(entry);
    hyp_lt_ndof_handle.GetEntry(entry);
    hyp_lt_phiErr_handle.GetEntry(entry);
    hyp_lt_ptErr_handle.GetEntry(entry);
    hyp_lt_z0_handle.GetEntry(entry);
    hyp_lt_z0Err_handle.GetEntry(entry);
    hyp_lt_z0corr_handle.GetEntry(entry);
    hyp_mt2_metMuonJESCorr_handle.GetEntry(entry);
    hyp_mt2_muCorrMet_handle.GetEntry(entry);
    hyp_mt2_tcMet_handle.GetEntry(entry);
    hyp_sumJetPt_handle.GetEntry(entry);
    hyp_FVFit_chi2ndf_handle.GetEntry(entry);
    hyp_FVFit_prob_handle.GetEntry(entry);
    hyp_FVFit_v4cxx_handle.GetEntry(entry);
    hyp_FVFit_v4cxy_handle.GetEntry(entry);
    hyp_FVFit_v4cyy_handle.GetEntry(entry);
    hyp_FVFit_v4czx_handle.GetEntry(entry);
    hyp_FVFit_v4czy_handle.GetEntry(entry);
    hyp_FVFit_v4czz_handle.GetEntry(entry);
    jets_approximatefHPD_handle.GetEntry(entry);
    jets_approximatefRBX_handle.GetEntry(entry);
    jets_cor_handle.GetEntry(entry);
    jets_corL1FastL2L3_handle.GetEntry(entry);
    jets_corL1L2L3_handle.GetEntry(entry);
    jets_emFrac_handle.GetEntry(entry);
    jets_fHPD_handle.GetEntry(entry);
    jets_fRBX_handle.GetEntry(entry);
    jets_fSubDetector1_handle.GetEntry(entry);
    jets_fSubDetector2_handle.GetEntry(entry);
    jets_fSubDetector3_handle.GetEntry(entry);
    jets_fSubDetector4_handle.GetEntry(entry);
    jets_hitsInN90_handle.GetEntry(entry);
    jets_n90Hits_handle.GetEntry(entry);
    jets_nECALTowers_handle.GetEntry(entry);
    jets_nHCALTowers_handle.GetEntry(entry);
    jets_restrictedEMF_handle.GetEntry(entry);
    mus_met_deltax_handle.GetEntry(entry);
    mus_met_deltay_handle.GetEntry(entry);
    mus_eledr_handle.GetEntry(entry);
    mus_jetdr_handle.GetEntry(entry);
    mus_isoR03_chpf_radial_handle.GetEntry(entry);
    mus_isoR03_chpf_radialTight_handle.GetEntry(entry);
    mus_isoR03_empf_radial_handle.GetEntry(entry);
    mus_isoR03_empf_radialTight_handle.GetEntry(entry);
    mus_isoR03_nhpf_radial_handle.GetEntry(entry);
    mus_isoR03_nhpf_radialTight_handle.GetEntry(entry);
    mus_isoR03_pf_radial_handle.GetEntry(entry);
    mus_isoR03_pf_radialTight_handle.GetEntry(entry);
    mus_backToBackCompat_handle.GetEntry(entry);
    mus_caloCompatibility_handle.GetEntry(entry);
    mus_chi2_handle.GetEntry(entry);
    mus_chi2LocalMomentum_handle.GetEntry(entry);
    mus_chi2LocalPosition_handle.GetEntry(entry);
    mus_cosmicCompat_handle.GetEntry(entry);
    mus_d0_handle.GetEntry(entry);
    mus_d0Err_handle.GetEntry(entry);
    mus_d0corr_handle.GetEntry(entry);
    mus_e_em_handle.GetEntry(entry);
    mus_e_emS9_handle.GetEntry(entry);
    mus_e_had_handle.GetEntry(entry);
    mus_e_hadS9_handle.GetEntry(entry);
    mus_e_ho_handle.GetEntry(entry);
    mus_e_hoS9_handle.GetEntry(entry);
    mus_etaErr_handle.GetEntry(entry);
    mus_gfit_chi2_handle.GetEntry(entry);
    mus_gfit_d0_handle.GetEntry(entry);
    mus_gfit_d0Err_handle.GetEntry(entry);
    mus_gfit_d0corr_handle.GetEntry(entry);
    mus_gfit_ndof_handle.GetEntry(entry);
    mus_gfit_qoverp_handle.GetEntry(entry);
    mus_gfit_qoverpError_handle.GetEntry(entry);
    mus_gfit_z0_handle.GetEntry(entry);
    mus_gfit_z0Err_handle.GetEntry(entry);
    mus_gfit_z0corr_handle.GetEntry(entry);
    mus_glbKink_handle.GetEntry(entry);
    mus_glbTrackProbability_handle.GetEntry(entry);
    mus_globalDeltaEtaPhi_handle.GetEntry(entry);
    mus_ip3d_handle.GetEntry(entry);
    mus_ip3derr_handle.GetEntry(entry);
    mus_iso03_emEt_handle.GetEntry(entry);
    mus_iso03_hadEt_handle.GetEntry(entry);
    mus_iso03_hoEt_handle.GetEntry(entry);
    mus_iso03_pf_handle.GetEntry(entry);
    mus_iso03_sumPt_handle.GetEntry(entry);
    mus_iso04_pf_handle.GetEntry(entry);
    mus_iso05_emEt_handle.GetEntry(entry);
    mus_iso05_hadEt_handle.GetEntry(entry);
    mus_iso05_hoEt_handle.GetEntry(entry);
    mus_iso05_sumPt_handle.GetEntry(entry);
    mus_isoR03_pf_ChargedHadronPt_handle.GetEntry(entry);
    mus_isoR03_pf_ChargedParticlePt_handle.GetEntry(entry);
    mus_isoR03_pf_NeutralHadronEt_handle.GetEntry(entry);
    mus_isoR03_pf_NeutralHadronEtHighThreshold_handle.GetEntry(entry);
    mus_isoR03_pf_PUPt_handle.GetEntry(entry);
    mus_isoR03_pf_PhotonEt_handle.GetEntry(entry);
    mus_isoR03_pf_PhotonEtHighThreshold_handle.GetEntry(entry);
    mus_isoR04_pf_ChargedHadronPt_handle.GetEntry(entry);
    mus_isoR04_pf_ChargedParticlePt_handle.GetEntry(entry);
    mus_isoR04_pf_NeutralHadronEt_handle.GetEntry(entry);
    mus_isoR04_pf_NeutralHadronEtHighThreshold_handle.GetEntry(entry);
    mus_isoR04_pf_PUPt_handle.GetEntry(entry);
    mus_isoR04_pf_PhotonEt_handle.GetEntry(entry);
    mus_isoR04_pf_PhotonEtHighThreshold_handle.GetEntry(entry);
    mus_iso_ecalvetoDep_handle.GetEntry(entry);
    mus_iso_hcalvetoDep_handle.GetEntry(entry);
    mus_iso_hovetoDep_handle.GetEntry(entry);
    mus_iso_trckvetoDep_handle.GetEntry(entry);
    mus_localDistance_handle.GetEntry(entry);
    mus_ndof_handle.GetEntry(entry);
    mus_overlapCompat_handle.GetEntry(entry);
    mus_pfdeltaP_handle.GetEntry(entry);
    mus_pfecalE_handle.GetEntry(entry);
    mus_pfhcalE_handle.GetEntry(entry);
    mus_pfmva_emu_handle.GetEntry(entry);
    mus_pfmva_epi_handle.GetEntry(entry);
    mus_pfmva_nothing_gamma_handle.GetEntry(entry);
    mus_pfmva_nothing_nh_handle.GetEntry(entry);
    mus_pfmva_pimu_handle.GetEntry(entry);
    mus_pfpS1E_handle.GetEntry(entry);
    mus_pfpS2E_handle.GetEntry(entry);
    mus_pfrawEcalE_handle.GetEntry(entry);
    mus_pfrawHcalE_handle.GetEntry(entry);
    mus_phiErr_handle.GetEntry(entry);
    mus_ptErr_handle.GetEntry(entry);
    mus_qoverp_handle.GetEntry(entry);
    mus_qoverpError_handle.GetEntry(entry);
    mus_segmCompatibility_handle.GetEntry(entry);
    mus_staRelChi2_handle.GetEntry(entry);
    mus_sta_chi2_handle.GetEntry(entry);
    mus_sta_d0_handle.GetEntry(entry);
    mus_sta_d0Err_handle.GetEntry(entry);
    mus_sta_d0corr_handle.GetEntry(entry);
    mus_sta_ndof_handle.GetEntry(entry);
    mus_sta_qoverp_handle.GetEntry(entry);
    mus_sta_qoverpError_handle.GetEntry(entry);
    mus_sta_z0_handle.GetEntry(entry);
    mus_sta_z0Err_handle.GetEntry(entry);
    mus_sta_z0corr_handle.GetEntry(entry);
    mus_timeAtIpInOut_handle.GetEntry(entry);
    mus_timeAtIpInOutErr_handle.GetEntry(entry);
    mus_timeAtIpOutIn_handle.GetEntry(entry);
    mus_timeAtIpOutInErr_handle.GetEntry(entry);
    mus_timeCompat_handle.GetEntry(entry);
    mus_trkKink_handle.GetEntry(entry);
    mus_trkRelChi2_handle.GetEntry(entry);
    mus_vertexCompat_handle.GetEntry(entry);
    mus_vertexphi_handle.GetEntry(entry);
    mus_z0_handle.GetEntry(entry);
    mus_z0Err_handle.GetEntry(entry);
    mus_z0corr_handle.GetEntry(entry);
    pfjets_mvavalue_handle.GetEntry(entry);
    pfjets_full53xmva_beta_handle.GetEntry(entry);
    pfjets_full53xmva_betaStar_handle.GetEntry(entry);
    pfjets_full53xmva_d0_handle.GetEntry(entry);
    pfjets_full53xmva_dRMean_handle.GetEntry(entry);
    pfjets_full53xmva_dZ_handle.GetEntry(entry);
    pfjets_full53xmva_frac01_handle.GetEntry(entry);
    pfjets_full53xmva_frac02_handle.GetEntry(entry);
    pfjets_full53xmva_frac03_handle.GetEntry(entry);
    pfjets_full53xmva_frac04_handle.GetEntry(entry);
    pfjets_full53xmva_frac05_handle.GetEntry(entry);
    pfjets_full53xmva_nCharged_handle.GetEntry(entry);
    pfjets_full53xmva_nNeutrals_handle.GetEntry(entry);
    pfjets_full53xmva_nvtx_handle.GetEntry(entry);
    pfjets_full53xmvavalue_handle.GetEntry(entry);
    pfjets_full5xmvavalue_handle.GetEntry(entry);
    trkjet_met_handle.GetEntry(entry);
    trkjet_metPhi_handle.GetEntry(entry);
    trkjet_sumet_handle.GetEntry(entry);
    trk_met_handle.GetEntry(entry);
    trk_metPhi_handle.GetEntry(entry);
    trk_sumet_handle.GetEntry(entry);
    pfcands_deltaP_handle.GetEntry(entry);
    pfcands_ecalE_handle.GetEntry(entry);
    pfcands_hcalE_handle.GetEntry(entry);
    pfcands_mva_emu_handle.GetEntry(entry);
    pfcands_mva_epi_handle.GetEntry(entry);
    pfcands_mva_nothing_gamma_handle.GetEntry(entry);
    pfcands_mva_nothing_nh_handle.GetEntry(entry);
    pfcands_mva_pimu_handle.GetEntry(entry);
    pfcands_pS1E_handle.GetEntry(entry);
    pfcands_pS2E_handle.GetEntry(entry);
    pfcands_rawEcalE_handle.GetEntry(entry);
    pfcands_rawHcalE_handle.GetEntry(entry);
    pfels_deltaP_handle.GetEntry(entry);
    pfels_ecalE_handle.GetEntry(entry);
    pfels_hcalE_handle.GetEntry(entry);
    pfels_iso04ChargedHadrons_handle.GetEntry(entry);
    pfels_iso04NeutralHadrons_handle.GetEntry(entry);
    pfels_iso04Photons_handle.GetEntry(entry);
    pfels_isoChargedHadrons_handle.GetEntry(entry);
    pfels_isoNeutralHadrons_handle.GetEntry(entry);
    pfels_isoPhotons_handle.GetEntry(entry);
    pfels_mva_emu_handle.GetEntry(entry);
    pfels_mva_epi_handle.GetEntry(entry);
    pfels_mva_nothing_gamma_handle.GetEntry(entry);
    pfels_mva_nothing_nh_handle.GetEntry(entry);
    pfels_mva_pimu_handle.GetEntry(entry);
    pfels_pS1E_handle.GetEntry(entry);
    pfels_pS2E_handle.GetEntry(entry);
    pfels_rawEcalE_handle.GetEntry(entry);
    pfels_rawHcalE_handle.GetEntry(entry);
    pfjets_area_handle.GetEntry(entry);
    pfjets_chargedEmE_handle.GetEntry(entry);
    pfjets_chargedHadronE_handle.GetEntry(entry);
    pfjets_cor_handle.GetEntry(entry);
    pfjets_corL1Fast_handle.GetEntry(entry);
    pfjets_corL1FastL2L3_handle.GetEntry(entry);
    pfjets_corL1FastL2L3residual_handle.GetEntry(entry);
    pfjets_corL1L2L3_handle.GetEntry(entry);
    pfjets_electronE_handle.GetEntry(entry);
    pfjets_hfEmE_handle.GetEntry(entry);
    pfjets_hfHadronE_handle.GetEntry(entry);
    pfjets_muonE_handle.GetEntry(entry);
    pfjets_neutralEmE_handle.GetEntry(entry);
    pfjets_neutralHadronE_handle.GetEntry(entry);
    pfjets_photonE_handle.GetEntry(entry);
    pfmus_deltaP_handle.GetEntry(entry);
    pfmus_ecalE_handle.GetEntry(entry);
    pfmus_hcalE_handle.GetEntry(entry);
    pfmus_iso04ChargedHadrons_handle.GetEntry(entry);
    pfmus_iso04NeutralHadrons_handle.GetEntry(entry);
    pfmus_iso04Photons_handle.GetEntry(entry);
    pfmus_isoChargedHadrons_handle.GetEntry(entry);
    pfmus_isoNeutralHadrons_handle.GetEntry(entry);
    pfmus_isoPhotons_handle.GetEntry(entry);
    pfmus_mva_emu_handle.GetEntry(entry);
    pfmus_mva_epi_handle.GetEntry(entry);
    pfmus_mva_nothing_gamma_handle.GetEntry(entry);
    pfmus_mva_nothing_nh_handle.GetEntry(entry);
    pfmus_mva_pimu_handle.GetEntry(entry);
    pfmus_pS1E_handle.GetEntry(entry);
    pfmus_pS2E_handle.GetEntry(entry);
    pfmus_rawEcalE_handle.GetEntry(entry);
    pfmus_rawHcalE_handle.GetEntry(entry);
    taus_pf_againstElectronDeadECAL_handle.GetEntry(entry);
    taus_pf_againstElectronLoose_handle.GetEntry(entry);
    taus_pf_againstElectronLooseMVA2_handle.GetEntry(entry);
    taus_pf_againstElectronLooseMVA3_handle.GetEntry(entry);
    taus_pf_againstElectronMVA_handle.GetEntry(entry);
    taus_pf_againstElectronMVA2category_handle.GetEntry(entry);
    taus_pf_againstElectronMVA2raw_handle.GetEntry(entry);
    taus_pf_againstElectronMVA3category_handle.GetEntry(entry);
    taus_pf_againstElectronMVA3raw_handle.GetEntry(entry);
    taus_pf_againstElectronMedium_handle.GetEntry(entry);
    taus_pf_againstElectronMediumMVA2_handle.GetEntry(entry);
    taus_pf_againstElectronMediumMVA3_handle.GetEntry(entry);
    taus_pf_againstElectronTight_handle.GetEntry(entry);
    taus_pf_againstElectronTightMVA2_handle.GetEntry(entry);
    taus_pf_againstElectronTightMVA3_handle.GetEntry(entry);
    taus_pf_againstElectronVLooseMVA2_handle.GetEntry(entry);
    taus_pf_againstElectronVTightMVA3_handle.GetEntry(entry);
    taus_pf_againstMuonLoose_handle.GetEntry(entry);
    taus_pf_againstMuonLoose2_handle.GetEntry(entry);
    taus_pf_againstMuonMedium_handle.GetEntry(entry);
    taus_pf_againstMuonMedium2_handle.GetEntry(entry);
    taus_pf_againstMuonTight_handle.GetEntry(entry);
    taus_pf_againstMuonTight2_handle.GetEntry(entry);
    taus_pf_byCombinedIsolationDeltaBetaCorrRaw_handle.GetEntry(entry);
    taus_pf_byCombinedIsolationDeltaBetaCorrRaw3Hits_handle.GetEntry(entry);
    taus_pf_byDecayModeFinding_handle.GetEntry(entry);
    taus_pf_byIsolationMVA2raw_handle.GetEntry(entry);
    taus_pf_byIsolationMVAraw_handle.GetEntry(entry);
    taus_pf_byLooseCombinedIsolationDeltaBetaCorr_handle.GetEntry(entry);
    taus_pf_byLooseCombinedIsolationDeltaBetaCorr3Hits_handle.GetEntry(entry);
    taus_pf_byLooseIsolationMVA_handle.GetEntry(entry);
    taus_pf_byLooseIsolationMVA2_handle.GetEntry(entry);
    taus_pf_byMediumCombinedIsolationDeltaBetaCorr_handle.GetEntry(entry);
    taus_pf_byMediumCombinedIsolationDeltaBetaCorr3Hits_handle.GetEntry(entry);
    taus_pf_byMediumIsolationMVA_handle.GetEntry(entry);
    taus_pf_byMediumIsolationMVA2_handle.GetEntry(entry);
    taus_pf_byTightCombinedIsolationDeltaBetaCorr_handle.GetEntry(entry);
    taus_pf_byTightCombinedIsolationDeltaBetaCorr3Hits_handle.GetEntry(entry);
    taus_pf_byTightIsolationMVA_handle.GetEntry(entry);
    taus_pf_byTightIsolationMVA2_handle.GetEntry(entry);
    taus_pf_byVLooseCombinedIsolationDeltaBetaCorr_handle.GetEntry(entry);
    photons_e1x5_handle.GetEntry(entry);
    photons_e2x5Max_handle.GetEntry(entry);
    photons_e3x3_handle.GetEntry(entry);
    photons_e5x5_handle.GetEntry(entry);
    photons_ecalIso03_handle.GetEntry(entry);
    photons_ecalIso04_handle.GetEntry(entry);
    photons_hOverE_handle.GetEntry(entry);
    photons_hcalDepth1TowerSumEtBcConeDR03_handle.GetEntry(entry);
    photons_hcalDepth1TowerSumEtBcConeDR04_handle.GetEntry(entry);
    photons_hcalDepth2TowerSumEtBcConeDR03_handle.GetEntry(entry);
    photons_hcalDepth2TowerSumEtBcConeDR04_handle.GetEntry(entry);
    photons_hcalIso03_handle.GetEntry(entry);
    photons_hcalIso04_handle.GetEntry(entry);
    photons_hcalTowerSumEtBcConeDR03_handle.GetEntry(entry);
    photons_hcalTowerSumEtBcConeDR04_handle.GetEntry(entry);
    photons_ntkIsoHollow03_handle.GetEntry(entry);
    photons_ntkIsoHollow04_handle.GetEntry(entry);
    photons_ntkIsoSolid03_handle.GetEntry(entry);
    photons_ntkIsoSolid04_handle.GetEntry(entry);
    photons_sigmaEtaEta_handle.GetEntry(entry);
    photons_sigmaIEtaIEta_handle.GetEntry(entry);
    photons_swissSeed_handle.GetEntry(entry);
    photons_tkIsoHollow03_handle.GetEntry(entry);
    photons_tkIsoHollow04_handle.GetEntry(entry);
    photons_tkIsoSolid03_handle.GetEntry(entry);
    photons_tkIsoSolid04_handle.GetEntry(entry);
    puInfo_trueNumInteractions_handle.GetEntry(entry);
    convs_chi2_handle.GetEntry(entry);
    convs_dl_handle.GetEntry(entry);
    convs_ndof_handle.GetEntry(entry);
    sparm_values_handle.GetEntry(entry);
    scs_clustersSize_handle.GetEntry(entry);
    scs_crystalsSize_handle.GetEntry(entry);
    scs_e1x3_handle.GetEntry(entry);
    scs_e1x5_handle.GetEntry(entry);
    scs_e2nd_handle.GetEntry(entry);
    scs_e2x2_handle.GetEntry(entry);
    scs_e2x5Max_handle.GetEntry(entry);
    scs_e3x1_handle.GetEntry(entry);
    scs_e3x2_handle.GetEntry(entry);
    scs_e3x3_handle.GetEntry(entry);
    scs_e4x4_handle.GetEntry(entry);
    scs_e5x5_handle.GetEntry(entry);
    scs_eMax_handle.GetEntry(entry);
    scs_eSeed_handle.GetEntry(entry);
    scs_energy_handle.GetEntry(entry);
    scs_eta_handle.GetEntry(entry);
    scs_hoe_handle.GetEntry(entry);
    scs_laserCorMax_handle.GetEntry(entry);
    scs_laserCorMean_handle.GetEntry(entry);
    scs_laserCorSeed_handle.GetEntry(entry);
    scs_phi_handle.GetEntry(entry);
    scs_preshowerEnergy_handle.GetEntry(entry);
    scs_rawEnergy_handle.GetEntry(entry);
    scs_sigmaEtaEta_handle.GetEntry(entry);
    scs_sigmaEtaPhi_handle.GetEntry(entry);
    scs_sigmaIEtaIEta_handle.GetEntry(entry);
    scs_sigmaIEtaIEtaSC_handle.GetEntry(entry);
    scs_sigmaIEtaIPhi_handle.GetEntry(entry);
    scs_sigmaIEtaIPhiSC_handle.GetEntry(entry);
    scs_sigmaIPhiIPhi_handle.GetEntry(entry);
    scs_sigmaIPhiIPhiSC_handle.GetEntry(entry);
    scs_sigmaPhiPhi_handle.GetEntry(entry);
    scs_timeSeed_handle.GetEntry(entry);
    svs_anglePV_handle.GetEntry(entry);
    svs_chi2_handle.GetEntry(entry);
    svs_dist3Dsig_handle.GetEntry(entry);
    svs_dist3Dval_handle.GetEntry(entry);
    svs_distXYsig_handle.GetEntry(entry);
    svs_distXYval_handle.GetEntry(entry);
    svs_ndof_handle.GetEntry(entry);
    svs_prob_handle.GetEntry(entry);
    svs_xError_handle.GetEntry(entry);
    svs_yError_handle.GetEntry(entry);
    svs_zError_handle.GetEntry(entry);
    mus_tcmet_deltax_handle.GetEntry(entry);
    mus_tcmet_deltay_handle.GetEntry(entry);
    pfcands_dzpv_handle.GetEntry(entry);
    pfcands_trkiso_handle.GetEntry(entry);
    trks_chi2_handle.GetEntry(entry);
    trks_d0_handle.GetEntry(entry);
    trks_d0Err_handle.GetEntry(entry);
    trks_d0corr_handle.GetEntry(entry);
    trks_d0corrPhi_handle.GetEntry(entry);
    trks_d0phiCov_handle.GetEntry(entry);
    trks_etaErr_handle.GetEntry(entry);
    trks_layer1_charge_handle.GetEntry(entry);
    trks_ndof_handle.GetEntry(entry);
    trks_phiErr_handle.GetEntry(entry);
    trks_ptErr_handle.GetEntry(entry);
    trks_validFraction_handle.GetEntry(entry);
    trks_z0_handle.GetEntry(entry);
    trks_z0Err_handle.GetEntry(entry);
    trks_z0corr_handle.GetEntry(entry);
    trkjets_cor_handle.GetEntry(entry);
    trks_d0Errvtx_handle.GetEntry(entry);
    trks_d0vtx_handle.GetEntry(entry);
    vtxs_chi2_handle.GetEntry(entry);
    vtxs_ndof_handle.GetEntry(entry);
    vtxs_sumpt_handle.GetEntry(entry);
    vtxs_xError_handle.GetEntry(entry);
    vtxs_yError_handle.GetEntry(entry);
    vtxs_zError_handle.GetEntry(entry);
    bsvtxs_chi2_handle.GetEntry(entry);
    bsvtxs_ndof_handle.GetEntry(entry);
    bsvtxs_sumpt_handle.GetEntry(entry);
    bsvtxs_xError_handle.GetEntry(entry);
    bsvtxs_yError_handle.GetEntry(entry);
    bsvtxs_zError_handle.GetEntry(entry);
    els_convs_dcot_handle.GetEntry(entry);
    els_convs_dist_handle.GetEntry(entry);
    els_convs_radius_handle.GetEntry(entry);
    mus_stationShowerDeltaR_handle.GetEntry(entry);
    mus_stationShowerSizeT_handle.GetEntry(entry);
    puInfo_instLumi_handle.GetEntry(entry);
    puInfo_sump_highpt_handle.GetEntry(entry);
    puInfo_sumpt_lowpt_handle.GetEntry(entry);
    puInfo_zpositions_handle.GetEntry(entry);
    vtxs_covMatrix_handle.GetEntry(entry);
    bsvtxs_covMatrix_handle.GetEntry(entry);
    evt_cscLooseHaloId_handle.GetEntry(entry);
    evt_cscTightHaloId_handle.GetEntry(entry);
    evt_ecalLooseHaloId_handle.GetEntry(entry);
    evt_ecalTightHaloId_handle.GetEntry(entry);
    evt_extremeTightHaloId_handle.GetEntry(entry);
    evt_globalLooseHaloId_handle.GetEntry(entry);
    evt_globalTightHaloId_handle.GetEntry(entry);
    evt_hcalLooseHaloId_handle.GetEntry(entry);
    evt_hcalTightHaloId_handle.GetEntry(entry);
    evt_looseHaloId_handle.GetEntry(entry);
    evt_nHaloLikeTracks_handle.GetEntry(entry);
    evt_nHaloTriggerCandidates_handle.GetEntry(entry);
    evt_tightHaloId_handle.GetEntry(entry);
    evt_bsType_handle.GetEntry(entry);
    evt_bunchCrossing_handle.GetEntry(entry);
    evt_experimentType_handle.GetEntry(entry);
    evt_isRealData_handle.GetEntry(entry);
    evt_orbitNumber_handle.GetEntry(entry);
    evt_storeNumber_handle.GetEntry(entry);
    hcalnoise_GetRecHitCount_handle.GetEntry(entry);
    hcalnoise_GetRecHitCount15_handle.GetEntry(entry);
    hcalnoise_maxHPDHits_handle.GetEntry(entry);
    hcalnoise_maxHPDNoOtherHits_handle.GetEntry(entry);
    hcalnoise_maxRBXHits_handle.GetEntry(entry);
    hcalnoise_maxZeros_handle.GetEntry(entry);
    hcalnoise_noiseFilterStatus_handle.GetEntry(entry);
    hcalnoise_noiseType_handle.GetEntry(entry);
    hcalnoise_num10GeVHits_handle.GetEntry(entry);
    hcalnoise_num25GeVHits_handle.GetEntry(entry);
    hcalnoise_numFlatNoiseChannels_handle.GetEntry(entry);
    hcalnoise_numIsolatedNoiseChannels_handle.GetEntry(entry);
    hcalnoise_numProblematicRBXs_handle.GetEntry(entry);
    hcalnoise_numSpikeNoiseChannels_handle.GetEntry(entry);
    hcalnoise_numTS4TS5NoiseChannels_handle.GetEntry(entry);
    hcalnoise_numTriangleNoiseChannels_handle.GetEntry(entry);
    hcalnoise_passHighLevelNoiseFilter_handle.GetEntry(entry);
    hcalnoise_passLooseNoiseFilter_handle.GetEntry(entry);
    hcalnoise_passTightNoiseFilter_handle.GetEntry(entry);
    l1_nemiso_handle.GetEntry(entry);
    l1_nemnoiso_handle.GetEntry(entry);
    l1_njetsc_handle.GetEntry(entry);
    l1_njetsf_handle.GetEntry(entry);
    l1_njetst_handle.GetEntry(entry);
    l1_nmus_handle.GetEntry(entry);
    ls_lumiSecQual_handle.GetEntry(entry);
    pdfinfo_id1_handle.GetEntry(entry);
    pdfinfo_id2_handle.GetEntry(entry);
    sparm_subProcessId_handle.GetEntry(entry);
    evt_ecaliPhiSuspects_handle.GetEntry(entry);
    evt_globaliPhiSuspects_handle.GetEntry(entry);
    evt_hcaliPhiSuspects_handle.GetEntry(entry);
    els_mc3_id_handle.GetEntry(entry);
    els_mc3idx_handle.GetEntry(entry);
    els_mc3_motherid_handle.GetEntry(entry);
    els_mc3_motheridx_handle.GetEntry(entry);
    els_mc_id_handle.GetEntry(entry);
    els_mcidx_handle.GetEntry(entry);
    els_mc_motherid_handle.GetEntry(entry);
    jets_mc3_id_handle.GetEntry(entry);
    jets_mc3idx_handle.GetEntry(entry);
    jets_mc_gpidx_handle.GetEntry(entry);
    jets_mc_id_handle.GetEntry(entry);
    jets_mcidx_handle.GetEntry(entry);
    jets_mc_motherid_handle.GetEntry(entry);
    mus_mc3_id_handle.GetEntry(entry);
    mus_mc3idx_handle.GetEntry(entry);
    mus_mc3_motherid_handle.GetEntry(entry);
    mus_mc3_motheridx_handle.GetEntry(entry);
    mus_mc_id_handle.GetEntry(entry);
    mus_mcidx_handle.GetEntry(entry);
    mus_mc_motherid_handle.GetEntry(entry);
    pfjets_mc3_id_handle.GetEntry(entry);
    pfjets_mc3idx_handle.GetEntry(entry);
    pfjets_mc_gpidx_handle.GetEntry(entry);
    pfjets_mc_id_handle.GetEntry(entry);
    pfjets_mcidx_handle.GetEntry(entry);
    pfjets_mc_motherid_handle.GetEntry(entry);
    photons_mc3_id_handle.GetEntry(entry);
    photons_mc3idx_handle.GetEntry(entry);
    photons_mc3_motherid_handle.GetEntry(entry);
    photons_mc3_motheridx_handle.GetEntry(entry);
    photons_mc_id_handle.GetEntry(entry);
    photons_mcidx_handle.GetEntry(entry);
    photons_mc_motherid_handle.GetEntry(entry);
    trk_mc3_id_handle.GetEntry(entry);
    trk_mc3idx_handle.GetEntry(entry);
    trk_mc3_motherid_handle.GetEntry(entry);
    trk_mc3_motheridx_handle.GetEntry(entry);
    trk_mc_id_handle.GetEntry(entry);
    trk_mcidx_handle.GetEntry(entry);
    trk_mc_motherid_handle.GetEntry(entry);
    els_closestJet_handle.GetEntry(entry);
    els_closestMuon_handle.GetEntry(entry);
    els_pfelsidx_handle.GetEntry(entry);
    els_category_handle.GetEntry(entry);
    els_charge_handle.GetEntry(entry);
    els_ckf_laywithmeas_handle.GetEntry(entry);
    els_class_handle.GetEntry(entry);
    els_conv_delMissHits_handle.GetEntry(entry);
    els_conv_flag_handle.GetEntry(entry);
    els_conv_gsftkidx_handle.GetEntry(entry);
    els_conv_old_delMissHits_handle.GetEntry(entry);
    els_conv_old_flag_handle.GetEntry(entry);
    els_conv_old_gsftkidx_handle.GetEntry(entry);
    els_conv_old_tkidx_handle.GetEntry(entry);
    els_conv_tkidx_handle.GetEntry(entry);
    els_exp_innerlayers_handle.GetEntry(entry);
    els_exp_outerlayers_handle.GetEntry(entry);
    els_fiduciality_handle.GetEntry(entry);
    els_gsftrkidx_handle.GetEntry(entry);
    els_layer1_det_handle.GetEntry(entry);
    els_layer1_layer_handle.GetEntry(entry);
    els_layer1_sizerphi_handle.GetEntry(entry);
    els_layer1_sizerz_handle.GetEntry(entry);
    els_lostHits_handle.GetEntry(entry);
    els_lost_pixelhits_handle.GetEntry(entry);
    els_nSeed_handle.GetEntry(entry);
    els_sccharge_handle.GetEntry(entry);
    els_scindex_handle.GetEntry(entry);
    els_trk_charge_handle.GetEntry(entry);
    els_trkidx_handle.GetEntry(entry);
    els_type_handle.GetEntry(entry);
    els_validHits_handle.GetEntry(entry);
    els_valid_pixelhits_handle.GetEntry(entry);
    genps_id_handle.GetEntry(entry);
    genps_id_mother_handle.GetEntry(entry);
    genps_status_handle.GetEntry(entry);
    gsftrks_charge_handle.GetEntry(entry);
    gsftrks_exp_innerlayers_handle.GetEntry(entry);
    gsftrks_exp_outerlayers_handle.GetEntry(entry);
    gsftrks_layer1_det_handle.GetEntry(entry);
    gsftrks_layer1_layer_handle.GetEntry(entry);
    gsftrks_layer1_sizerphi_handle.GetEntry(entry);
    gsftrks_layer1_sizerz_handle.GetEntry(entry);
    gsftrks_lostHits_handle.GetEntry(entry);
    gsftrks_lost_pixelhits_handle.GetEntry(entry);
    gsftrks_nlayers_handle.GetEntry(entry);
    gsftrks_nlayers3D_handle.GetEntry(entry);
    gsftrks_nlayersLost_handle.GetEntry(entry);
    gsftrks_validHits_handle.GetEntry(entry);
    gsftrks_valid_pixelhits_handle.GetEntry(entry);
    hyp_ll_charge_handle.GetEntry(entry);
    hyp_ll_id_handle.GetEntry(entry);
    hyp_ll_index_handle.GetEntry(entry);
    hyp_ll_lostHits_handle.GetEntry(entry);
    hyp_ll_validHits_handle.GetEntry(entry);
    hyp_lt_charge_handle.GetEntry(entry);
    hyp_lt_id_handle.GetEntry(entry);
    hyp_lt_index_handle.GetEntry(entry);
    hyp_lt_lostHits_handle.GetEntry(entry);
    hyp_lt_validHits_handle.GetEntry(entry);
    hyp_njets_handle.GetEntry(entry);
    hyp_nojets_handle.GetEntry(entry);
    hyp_type_handle.GetEntry(entry);
    hyp_FVFit_ndf_handle.GetEntry(entry);
    hyp_FVFit_status_handle.GetEntry(entry);
    hyp_ll_mc_id_handle.GetEntry(entry);
    hyp_ll_mc_motherid_handle.GetEntry(entry);
    hyp_lt_mc_id_handle.GetEntry(entry);
    hyp_lt_mc_motherid_handle.GetEntry(entry);
    pfjets_mcflavorAlgo_handle.GetEntry(entry);
    pfjets_mcflavorPhys_handle.GetEntry(entry);
    jets_closestElectron_handle.GetEntry(entry);
    jets_closestMuon_handle.GetEntry(entry);
    l1_emiso_ieta_handle.GetEntry(entry);
    l1_emiso_iphi_handle.GetEntry(entry);
    l1_emiso_rawId_handle.GetEntry(entry);
    l1_emiso_type_handle.GetEntry(entry);
    l1_emnoiso_ieta_handle.GetEntry(entry);
    l1_emnoiso_iphi_handle.GetEntry(entry);
    l1_emnoiso_rawId_handle.GetEntry(entry);
    l1_emnoiso_type_handle.GetEntry(entry);
    l1_jetsc_ieta_handle.GetEntry(entry);
    l1_jetsc_iphi_handle.GetEntry(entry);
    l1_jetsc_rawId_handle.GetEntry(entry);
    l1_jetsc_type_handle.GetEntry(entry);
    l1_jetsf_ieta_handle.GetEntry(entry);
    l1_jetsf_iphi_handle.GetEntry(entry);
    l1_jetsf_rawId_handle.GetEntry(entry);
    l1_jetsf_type_handle.GetEntry(entry);
    l1_jetst_ieta_handle.GetEntry(entry);
    l1_jetst_iphi_handle.GetEntry(entry);
    l1_jetst_rawId_handle.GetEntry(entry);
    l1_jetst_type_handle.GetEntry(entry);
    l1_mus_flags_handle.GetEntry(entry);
    l1_mus_q_handle.GetEntry(entry);
    l1_mus_qual_handle.GetEntry(entry);
    l1_mus_qualFlags_handle.GetEntry(entry);
    mus_met_flag_handle.GetEntry(entry);
    mus_closestEle_handle.GetEntry(entry);
    mus_closestJet_handle.GetEntry(entry);
    mus_pfmusidx_handle.GetEntry(entry);
    mus_charge_handle.GetEntry(entry);
    mus_gfit_validHits_handle.GetEntry(entry);
    mus_gfit_validSTAHits_handle.GetEntry(entry);
    mus_gfit_validSiHits_handle.GetEntry(entry);
    mus_goodmask_handle.GetEntry(entry);
    mus_iso03_ntrk_handle.GetEntry(entry);
    mus_iso05_ntrk_handle.GetEntry(entry);
    mus_lostHits_handle.GetEntry(entry);
    mus_muonBestTrackType_handle.GetEntry(entry);
    mus_nOverlaps_handle.GetEntry(entry);
    mus_nmatches_handle.GetEntry(entry);
    mus_numberOfMatchedStations_handle.GetEntry(entry);
    mus_overlap0_handle.GetEntry(entry);
    mus_overlap1_handle.GetEntry(entry);
    mus_pfcharge_handle.GetEntry(entry);
    mus_pfflag_handle.GetEntry(entry);
    mus_pfparticleId_handle.GetEntry(entry);
    mus_pid_PFMuon_handle.GetEntry(entry);
    mus_pid_TM2DCompatibilityLoose_handle.GetEntry(entry);
    mus_pid_TM2DCompatibilityTight_handle.GetEntry(entry);
    mus_pid_TMLastStationLoose_handle.GetEntry(entry);
    mus_pid_TMLastStationTight_handle.GetEntry(entry);
    mus_sta_validHits_handle.GetEntry(entry);
    mus_timeDirection_handle.GetEntry(entry);
    mus_timeNumStationsUsed_handle.GetEntry(entry);
    mus_trk_charge_handle.GetEntry(entry);
    mus_trkidx_handle.GetEntry(entry);
    mus_type_handle.GetEntry(entry);
    mus_validHits_handle.GetEntry(entry);
    pfcands_charge_handle.GetEntry(entry);
    pfcands_flag_handle.GetEntry(entry);
    pfcands_particleId_handle.GetEntry(entry);
    pfcands_pfelsidx_handle.GetEntry(entry);
    pfcands_pfmusidx_handle.GetEntry(entry);
    pfcands_trkidx_handle.GetEntry(entry);
    pfcands_vtxidx_handle.GetEntry(entry);
    pfels_elsidx_handle.GetEntry(entry);
    pfels_charge_handle.GetEntry(entry);
    pfels_flag_handle.GetEntry(entry);
    pfels_particleId_handle.GetEntry(entry);
    pfjets_chargedHadronMultiplicity_handle.GetEntry(entry);
    pfjets_chargedMultiplicity_handle.GetEntry(entry);
    pfjets_electronMultiplicity_handle.GetEntry(entry);
    pfjets_hfEmMultiplicity_handle.GetEntry(entry);
    pfjets_hfHadronMultiplicity_handle.GetEntry(entry);
    pfjets_muonMultiplicity_handle.GetEntry(entry);
    pfjets_neutralHadronMultiplicity_handle.GetEntry(entry);
    pfjets_neutralMultiplicity_handle.GetEntry(entry);
    pfjets_photonMultiplicity_handle.GetEntry(entry);
    pfmus_musidx_handle.GetEntry(entry);
    pfmus_charge_handle.GetEntry(entry);
    pfmus_flag_handle.GetEntry(entry);
    pfmus_particleId_handle.GetEntry(entry);
    taus_pf_charge_handle.GetEntry(entry);
    taus_pf_pfjetIndex_handle.GetEntry(entry);
    photons_fiduciality_handle.GetEntry(entry);
    photons_scindex_handle.GetEntry(entry);
    puInfo_bunchCrossing_handle.GetEntry(entry);
    puInfo_nPUvertices_handle.GetEntry(entry);
    convs_algo_handle.GetEntry(entry);
    convs_isConverted_handle.GetEntry(entry);
    convs_quality_handle.GetEntry(entry);
    scs_detIdSeed_handle.GetEntry(entry);
    scs_elsidx_handle.GetEntry(entry);
    scs_severitySeed_handle.GetEntry(entry);
    svs_isKs_handle.GetEntry(entry);
    svs_isLambda_handle.GetEntry(entry);
    svs_mc3_id_handle.GetEntry(entry);
    svs_nTrks_handle.GetEntry(entry);
    mus_tcmet_flag_handle.GetEntry(entry);
    trks_algo_handle.GetEntry(entry);
    trks_charge_handle.GetEntry(entry);
    trks_exp_innerlayers_handle.GetEntry(entry);
    trks_exp_outerlayers_handle.GetEntry(entry);
    trks_layer1_det_handle.GetEntry(entry);
    trks_layer1_layer_handle.GetEntry(entry);
    trks_layer1_sizerphi_handle.GetEntry(entry);
    trks_layer1_sizerz_handle.GetEntry(entry);
    trks_lostHits_handle.GetEntry(entry);
    trks_lost_pixelhits_handle.GetEntry(entry);
    trks_nLoops_handle.GetEntry(entry);
    trks_nlayers_handle.GetEntry(entry);
    trks_nlayers3D_handle.GetEntry(entry);
    trks_nlayersLost_handle.GetEntry(entry);
    trks_pvidx0_handle.GetEntry(entry);
    trks_pvidx1_handle.GetEntry(entry);
    trks_qualityMask_handle.GetEntry(entry);
    trks_validHits_handle.GetEntry(entry);
    trks_valid_pixelhits_handle.GetEntry(entry);
    trks_elsidx_handle.GetEntry(entry);
    trk_musidx_handle.GetEntry(entry);
    trkjets_ntrks_handle.GetEntry(entry);
    trkjets_vtxs_idx_handle.GetEntry(entry);
    vtxs_isFake_handle.GetEntry(entry);
    vtxs_isValid_handle.GetEntry(entry);
    vtxs_tracksSize_handle.GetEntry(entry);
    bsvtxs_isFake_handle.GetEntry(entry);
    bsvtxs_isValid_handle.GetEntry(entry);
    bsvtxs_tracksSize_handle.GetEntry(entry);
    els_convs_delMissHits_handle.GetEntry(entry);
    els_convs_flag_handle.GetEntry(entry);
    els_convs_gsftkidx_handle.GetEntry(entry);
    els_convs_tkidx_handle.GetEntry(entry);
    genps_lepdaughter_id_handle.GetEntry(entry);
    genps_lepdaughter_idx_handle.GetEntry(entry);
    hlt_trigObjs_id_handle.GetEntry(entry);
    hyp_jets_idx_handle.GetEntry(entry);
    hyp_other_jets_idx_handle.GetEntry(entry);
    mus_nStationCorrelatedHits_handle.GetEntry(entry);
    mus_nStationHits_handle.GetEntry(entry);
    pfjets_pfcandIndicies_handle.GetEntry(entry);
    taus_pf_pfcandIndicies_handle.GetEntry(entry);
    puInfo_ntrks_highpt_handle.GetEntry(entry);
    puInfo_ntrks_lowpt_handle.GetEntry(entry);
    convs_nHitsBeforeVtx_handle.GetEntry(entry);
    convs_tkalgo_handle.GetEntry(entry);
    convs_tkidx_handle.GetEntry(entry);
    els_HLT_Ele17_Ele8_L1sL1DoubleEG137_version_handle.GetEntry(entry);
    els_HLT_Ele17_Ele8_LeadingLeg_version_handle.GetEntry(entry);
    els_HLT_Ele17_Ele8_Mass50_LeadingLeg_version_handle.GetEntry(entry);
    els_HLT_Ele17_Ele8_Mass50_TrailingLeg_version_handle.GetEntry(entry);
    els_HLT_Ele17_Ele8_TrailingLeg_version_handle.GetEntry(entry);
    els_HLT_Ele17_Ele8_version_handle.GetEntry(entry);
    els_HLT_Ele20_SC4_Mass50_LeadingLeg_version_handle.GetEntry(entry);
    els_HLT_Ele20_SC4_Mass50_TrailingLeg_version_handle.GetEntry(entry);
    els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_version_handle.GetEntry(entry);
    els_HLT_Ele27_WP80_version_handle.GetEntry(entry);
    els_HLT_Ele32_SC17_Mass50_LeadingLeg_version_handle.GetEntry(entry);
    els_HLT_Ele32_SC17_Mass50_TrailingLeg_version_handle.GetEntry(entry);
    els_HLT_Mu17_Ele8_TrailingLeg_version_handle.GetEntry(entry);
    els_HLT_Mu17_Ele8_version_handle.GetEntry(entry);
    els_HLT_Mu8_Ele17_version_handle.GetEntry(entry);
    evt_nels_handle.GetEntry(entry);
    evt_detectorStatus_handle.GetEntry(entry);
    evt_event_handle.GetEntry(entry);
    evt_lumiBlock_handle.GetEntry(entry);
    evt_run_handle.GetEntry(entry);
    genps_flavorHistoryFilterResult_handle.GetEntry(entry);
    evt_ngenjets_handle.GetEntry(entry);
    genps_signalProcessID_handle.GetEntry(entry);
    evt_njets_handle.GetEntry(entry);
    l1_bits1_handle.GetEntry(entry);
    l1_bits2_handle.GetEntry(entry);
    l1_bits3_handle.GetEntry(entry);
    l1_bits4_handle.GetEntry(entry);
    l1_techbits1_handle.GetEntry(entry);
    l1_techbits2_handle.GetEntry(entry);
    ls_lsNumber_handle.GetEntry(entry);
    ls_numOrbit_handle.GetEntry(entry);
    ls_startOrbit_handle.GetEntry(entry);
    mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_version_handle.GetEntry(entry);
    mus_HLT_IsoMu24_eta2p1_version_handle.GetEntry(entry);
    mus_HLT_Mu17_Ele8_LeadingLeg_version_handle.GetEntry(entry);
    mus_HLT_Mu17_Ele8_version_handle.GetEntry(entry);
    mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_version_handle.GetEntry(entry);
    mus_HLT_Mu17_Mu8_LeadingLeg_version_handle.GetEntry(entry);
    mus_HLT_Mu17_Mu8_TrailingLeg_version_handle.GetEntry(entry);
    mus_HLT_Mu17_Mu8_version_handle.GetEntry(entry);
    mus_HLT_Mu17_TkMu8_LeadingLeg_version_handle.GetEntry(entry);
    mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_version_handle.GetEntry(entry);
    mus_HLT_Mu17_TkMu8_TrailingLeg_version_handle.GetEntry(entry);
    mus_HLT_Mu17_TkMu8_version_handle.GetEntry(entry);
    mus_HLT_Mu8_Ele17_TrailingLeg_version_handle.GetEntry(entry);
    mus_HLT_Mu8_Ele17_version_handle.GetEntry(entry);
    evt_nphotons_handle.GetEntry(entry);
    evt_ecalRecoStatus_handle.GetEntry(entry);
    evt_nscs_handle.GetEntry(entry);
    evt_ntrkjets_handle.GetEntry(entry);
    evt_nvtxs_handle.GetEntry(entry);
    evt_nbsvtxs_handle.GetEntry(entry);
    els_HLT_Ele17_Ele8_handle.GetEntry(entry);
    els_HLT_Ele17_Ele8_L1sL1DoubleEG137_handle.GetEntry(entry);
    els_HLT_Ele17_Ele8_LeadingLeg_handle.GetEntry(entry);
    els_HLT_Ele17_Ele8_Mass50_LeadingLeg_handle.GetEntry(entry);
    els_HLT_Ele17_Ele8_Mass50_TrailingLeg_handle.GetEntry(entry);
    els_HLT_Ele17_Ele8_TrailingLeg_handle.GetEntry(entry);
    els_HLT_Ele20_SC4_Mass50_LeadingLeg_handle.GetEntry(entry);
    els_HLT_Ele20_SC4_Mass50_TrailingLeg_handle.GetEntry(entry);
    els_HLT_Ele27_WP80_handle.GetEntry(entry);
    els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_handle.GetEntry(entry);
    els_HLT_Ele32_SC17_Mass50_LeadingLeg_handle.GetEntry(entry);
    els_HLT_Ele32_SC17_Mass50_TrailingLeg_handle.GetEntry(entry);
    els_HLT_Mu17_Ele8_handle.GetEntry(entry);
    els_HLT_Mu17_Ele8_TrailingLeg_handle.GetEntry(entry);
    els_HLT_Mu8_Ele17_handle.GetEntry(entry);
    els_id2012ext_loose_handle.GetEntry(entry);
    els_id2012ext_medium_handle.GetEntry(entry);
    els_id2012ext_tight_handle.GetEntry(entry);
    els_id2012ext_veto_handle.GetEntry(entry);
    els_id2012_loose_handle.GetEntry(entry);
    els_id2012_medium_handle.GetEntry(entry);
    els_id2012_tight_handle.GetEntry(entry);
    els_id2012_veto_handle.GetEntry(entry);
    hlt_prescales_handle.GetEntry(entry);
    l1_prescales_handle.GetEntry(entry);
    l1_techtrigprescales_handle.GetEntry(entry);
    mus_HLT_IsoMu24_eta2p1_handle.GetEntry(entry);
    mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_handle.GetEntry(entry);
    mus_HLT_Mu17_Ele8_handle.GetEntry(entry);
    mus_HLT_Mu17_Ele8_LeadingLeg_handle.GetEntry(entry);
    mus_HLT_Mu17_Mu8_handle.GetEntry(entry);
    mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_handle.GetEntry(entry);
    mus_HLT_Mu17_Mu8_LeadingLeg_handle.GetEntry(entry);
    mus_HLT_Mu17_Mu8_TrailingLeg_handle.GetEntry(entry);
    mus_HLT_Mu17_TkMu8_handle.GetEntry(entry);
    mus_HLT_Mu17_TkMu8_LeadingLeg_handle.GetEntry(entry);
    mus_HLT_Mu17_TkMu8_TrailingLeg_handle.GetEntry(entry);
    mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_handle.GetEntry(entry);
    mus_HLT_Mu8_Ele17_handle.GetEntry(entry);
    mus_HLT_Mu8_Ele17_TrailingLeg_handle.GetEntry(entry);
    evt_timestamp_handle.GetEntry(entry);
    evt_nEvts_handle.GetEntry(entry);
    evt_filt_eff_handle.GetEntry(entry);

}

void CMS2::LoadAllBranches()
{
    hlt_bits_handle.Load();
    evt_CMS2tag_handle.Load();
    evt_dataset_handle.Load();
    hlt_trigNames_handle.Load();
    l1_techtrigNames_handle.Load();
    l1_trigNames_handle.Load();
    evt_errCategory_handle.Load();
    evt_errModule_handle.Load();
    evt_errSeverity_handle.Load();
    sparm_comment_handle.Load();
    sparm_names_handle.Load();
    evt_eventHasHalo_handle.Load();
    hcalnoise_HasBadRBXTS4TS5_handle.Load();
    ls_isValid_handle.Load();
    filt_ecalBE_handle.Load();
    filt_ecalDR_handle.Load();
    filt_ecalLaser_handle.Load();
    filt_ecalTP_handle.Load();
    filt_eeBadSc_handle.Load();
    filt_greedyMuon_handle.Load();
    filt_hcalLaser_handle.Load();
    filt_inconsistentMuon_handle.Load();
    filt_jetIDFailure_handle.Load();
    filt_multiEvent_handle.Load();
    filt_trackingFailure_handle.Load();
    evt_hbheFilter_handle.Load();
    els_conv_vtx_flag_handle.Load();
    els_passingMvaPreselection_handle.Load();
    els_passingPflowPreselection_handle.Load();
    mus_isRPCMuon_handle.Load();
    mus_tightMatch_handle.Load();
    mus_updatedSta_handle.Load();
    pfcands_isMuIso_handle.Load();
    photons_haspixelSeed_handle.Load();
    jets_closestElectron_DR_handle.Load();
    jets_closestMuon_DR_handle.Load();
    evt_bs_Xwidth_handle.Load();
    evt_bs_XwidthErr_handle.Load();
    evt_bs_Ywidth_handle.Load();
    evt_bs_YwidthErr_handle.Load();
    evt_bs_dxdz_handle.Load();
    evt_bs_dxdzErr_handle.Load();
    evt_bs_dydz_handle.Load();
    evt_bs_dydzErr_handle.Load();
    evt_bs_sigmaZ_handle.Load();
    evt_bs_sigmaZErr_handle.Load();
    evt_bs_xErr_handle.Load();
    evt_bs_yErr_handle.Load();
    evt_bs_zErr_handle.Load();
    evt_bField_handle.Load();
    evt_rho_handle.Load();
    evt_rhoJEC_handle.Load();
    evt_fixgrid_all_rho_handle.Load();
    evt_fixgridfastjet_all_rho_handle.Load();
    evt_kfactor_handle.Load();
    evt_scale1fb_handle.Load();
    evt_xsec_excl_handle.Load();
    evt_xsec_incl_handle.Load();
    gen_met_handle.Load();
    gen_metPhi_handle.Load();
    genps_alphaQCD_handle.Load();
    genps_pthat_handle.Load();
    genps_qScale_handle.Load();
    genps_weight_handle.Load();
    gen_sumEt_handle.Load();
    hcalnoise_GetRecHitEnergy_handle.Load();
    hcalnoise_GetRecHitEnergy15_handle.Load();
    hcalnoise_GetTotalCalibCharge_handle.Load();
    hcalnoise_TS4TS5NoiseSumE_handle.Load();
    hcalnoise_TS4TS5NoiseSumEt_handle.Load();
    hcalnoise_eventChargeFraction_handle.Load();
    hcalnoise_eventEMEnergy_handle.Load();
    hcalnoise_eventEMFraction_handle.Load();
    hcalnoise_eventHadEnergy_handle.Load();
    hcalnoise_eventTrackEnergy_handle.Load();
    hcalnoise_flatNoiseSumE_handle.Load();
    hcalnoise_flatNoiseSumEt_handle.Load();
    hcalnoise_isolatedNoiseSumE_handle.Load();
    hcalnoise_isolatedNoiseSumEt_handle.Load();
    hcalnoise_max10GeVHitTime_handle.Load();
    hcalnoise_max25GeVHitTime_handle.Load();
    hcalnoise_maxE10TS_handle.Load();
    hcalnoise_maxE2Over10TS_handle.Load();
    hcalnoise_maxE2TS_handle.Load();
    hcalnoise_min10GeVHitTime_handle.Load();
    hcalnoise_min25GeVHitTime_handle.Load();
    hcalnoise_minE10TS_handle.Load();
    hcalnoise_minE2Over10TS_handle.Load();
    hcalnoise_minE2TS_handle.Load();
    hcalnoise_minHPDEMF_handle.Load();
    hcalnoise_minRBXEMF_handle.Load();
    hcalnoise_rms10GeVHitTime_handle.Load();
    hcalnoise_rms25GeVHitTime_handle.Load();
    hcalnoise_spikeNoiseSumE_handle.Load();
    hcalnoise_spikeNoiseSumEt_handle.Load();
    hcalnoise_triangleNoiseSumE_handle.Load();
    hcalnoise_triangleNoiseSumEt_handle.Load();
    evt_kt6calo_central_rho_handle.Load();
    evt_kt6calo_muhlt_rho_handle.Load();
    evt_kt6calo_rho_handle.Load();
    evt_kt6pf_ctrChargedPU_rho_handle.Load();
    evt_kt6pf_ctrNeutral_rho_handle.Load();
    evt_kt6pf_ctrNeutralTight_rho_handle.Load();
    evt_kt6pf_foregiso_rho_handle.Load();
    l1_met_etTot_handle.Load();
    l1_met_met_handle.Load();
    l1_mht_htTot_handle.Load();
    l1_mht_mht_handle.Load();
    ls_avgInsDelLumi_handle.Load();
    ls_avgInsDelLumiErr_handle.Load();
    ls_avgInsRecLumi_handle.Load();
    ls_avgInsRecLumiErr_handle.Load();
    ls_deadFrac_handle.Load();
    ls_intgDelLumi_handle.Load();
    ls_intgRecLumi_handle.Load();
    ls_lumiSectionLength_handle.Load();
    evt_ecalendcapm_met_handle.Load();
    evt_ecalendcapm_metPhi_handle.Load();
    evt_ecalendcapp_met_handle.Load();
    evt_ecalendcapp_metPhi_handle.Load();
    evt_ecalmet_handle.Load();
    evt_ecalmetPhi_handle.Load();
    evt_endcapm_met_handle.Load();
    evt_endcapm_metPhi_handle.Load();
    evt_endcapp_met_handle.Load();
    evt_endcapp_metPhi_handle.Load();
    evt_hcalendcapm_met_handle.Load();
    evt_hcalendcapm_metPhi_handle.Load();
    evt_hcalendcapp_met_handle.Load();
    evt_hcalendcapp_metPhi_handle.Load();
    evt_hcalmet_handle.Load();
    evt_hcalmetPhi_handle.Load();
    evt_met_handle.Load();
    evt_met_EtGt3_handle.Load();
    evt_metHO_handle.Load();
    evt_metHOPhi_handle.Load();
    evt_metHOSig_handle.Load();
    evt_metMuonCorr_handle.Load();
    evt_metMuonCorrPhi_handle.Load();
    evt_metMuonCorrSig_handle.Load();
    evt_metMuonJESCorr_handle.Load();
    evt_metMuonJESCorrPhi_handle.Load();
    evt_metMuonJESCorrSig_handle.Load();
    evt_metNoHF_handle.Load();
    evt_metNoHFHO_handle.Load();
    evt_metNoHFHOPhi_handle.Load();
    evt_metNoHFHOSig_handle.Load();
    evt_metNoHFPhi_handle.Load();
    evt_metNoHFSig_handle.Load();
    evt_metOpt_handle.Load();
    evt_metOptHO_handle.Load();
    evt_metOptHOPhi_handle.Load();
    evt_metOptHOSig_handle.Load();
    evt_metOptNoHF_handle.Load();
    evt_metOptNoHFHO_handle.Load();
    evt_metOptNoHFHOPhi_handle.Load();
    evt_metOptNoHFHOSig_handle.Load();
    evt_metOptNoHFPhi_handle.Load();
    evt_metOptNoHFSig_handle.Load();
    evt_metOptPhi_handle.Load();
    evt_metOptSig_handle.Load();
    evt_metPhi_handle.Load();
    evt_metPhi_EtGt3_handle.Load();
    evt_metSig_handle.Load();
    evt_sumet_handle.Load();
    evt_sumet_EtGt3_handle.Load();
    evt_sumetHO_handle.Load();
    evt_sumetMuonCorr_handle.Load();
    evt_sumetMuonJESCorr_handle.Load();
    evt_sumetNoHF_handle.Load();
    evt_sumetNoHFHO_handle.Load();
    evt_sumetOpt_handle.Load();
    evt_sumetOptHO_handle.Load();
    evt_sumetOptNoHF_handle.Load();
    evt_sumetOptNoHFHO_handle.Load();
    pdfinfo_pdf1_handle.Load();
    pdfinfo_pdf2_handle.Load();
    pdfinfo_scale_handle.Load();
    pdfinfo_x1_handle.Load();
    pdfinfo_x2_handle.Load();
    evt_fixgrid_rho_all_handle.Load();
    evt_fixgrid_rho_ctr_handle.Load();
    evt_fixgrid_rho_fwd_handle.Load();
    evt_pfmet_handle.Load();
    evt_pfmetPhi_handle.Load();
    evt_pfmetPhi_type1cor_handle.Load();
    evt_pfmetSig_handle.Load();
    evt_pfmetSignificance_handle.Load();
    evt_pfmet_type1cor_handle.Load();
    evt_pfsumet_handle.Load();
    sparm_filterEfficiency_handle.Load();
    sparm_pdfScale_handle.Load();
    sparm_pdfWeight1_handle.Load();
    sparm_pdfWeight2_handle.Load();
    sparm_weight_handle.Load();
    sparm_xsec_handle.Load();
    evt_pf_tcmet_handle.Load();
    evt_pf_tcmetPhi_handle.Load();
    evt_pf_tcmetSig_handle.Load();
    evt_pf_tcsumet_handle.Load();
    evt_tcmet_handle.Load();
    evt_tcmetPhi_handle.Load();
    evt_tcmetSig_handle.Load();
    evt_tcsumet_handle.Load();
    evt_ww_rho_act_handle.Load();
    evt_ww_rho_handle.Load();
    evt_ww_rho_rnd_handle.Load();
    evt_ww_rho_vor_handle.Load();
    evt_bsp4_handle.Load();
    l1_met_p4_handle.Load();
    l1_mht_p4_handle.Load();
    els_mc_motherp4_handle.Load();
    els_mc_p4_handle.Load();
    jets_mc_gp_p4_handle.Load();
    jets_mc_motherp4_handle.Load();
    jets_mc_p4_handle.Load();
    mus_mc_motherp4_handle.Load();
    mus_mc_p4_handle.Load();
    pfjets_mc_gp_p4_handle.Load();
    pfjets_mc_motherp4_handle.Load();
    pfjets_mc_p4_handle.Load();
    photons_mc_motherp4_handle.Load();
    photons_mc_p4_handle.Load();
    trk_mcp4_handle.Load();
    els_conv_pos_p4_handle.Load();
    els_inner_position_handle.Load();
    els_outer_position_handle.Load();
    els_p4_handle.Load();
    els_p4In_handle.Load();
    els_p4Out_handle.Load();
    els_trk_p4_handle.Load();
    els_vertex_p4_handle.Load();
    genjets_p4_handle.Load();
    genps_p4_handle.Load();
    genps_prod_vtx_handle.Load();
    gsftrks_inner_position_handle.Load();
    gsftrks_outer_p4_handle.Load();
    gsftrks_outer_position_handle.Load();
    gsftrks_p4_handle.Load();
    gsftrks_vertex_p4_handle.Load();
    hyp_ll_p4_handle.Load();
    hyp_ll_trk_p4_handle.Load();
    hyp_lt_p4_handle.Load();
    hyp_lt_trk_p4_handle.Load();
    hyp_p4_handle.Load();
    hyp_FVFit_p4_handle.Load();
    hyp_FVFit_v4_handle.Load();
    hyp_ll_mc_p4_handle.Load();
    hyp_lt_mc_p4_handle.Load();
    jets_p4_handle.Load();
    jets_vertex_p4_handle.Load();
    l1_emiso_p4_handle.Load();
    l1_emnoiso_p4_handle.Load();
    l1_jetsc_p4_handle.Load();
    l1_jetsf_p4_handle.Load();
    l1_jetst_p4_handle.Load();
    l1_mus_p4_handle.Load();
    mus_ecalpos_p4_handle.Load();
    mus_fitpicky_p4_handle.Load();
    mus_fittev_p4_handle.Load();
    mus_fittpfms_p4_handle.Load();
    mus_gfit_outerPos_p4_handle.Load();
    mus_gfit_p4_handle.Load();
    mus_gfit_vertex_p4_handle.Load();
    mus_p4_handle.Load();
    mus_pfp4_handle.Load();
    mus_pfposAtEcal_p4_handle.Load();
    mus_sta_p4_handle.Load();
    mus_sta_vertex_p4_handle.Load();
    mus_trk_p4_handle.Load();
    mus_vertex_p4_handle.Load();
    pfcands_p4_handle.Load();
    pfcands_posAtEcal_p4_handle.Load();
    pfels_p4_handle.Load();
    pfels_posAtEcal_p4_handle.Load();
    pfjets_p4_handle.Load();
    pfmus_p4_handle.Load();
    pfmus_posAtEcal_p4_handle.Load();
    taus_pf_p4_handle.Load();
    photons_p4_handle.Load();
    convs_refitPairMom_p4_handle.Load();
    convs_vtxpos_handle.Load();
    scs_p4_handle.Load();
    scs_pos_p4_handle.Load();
    scs_vtx_p4_handle.Load();
    svs_flight_handle.Load();
    svs_mc3_p4_handle.Load();
    svs_p4_handle.Load();
    svs_position_handle.Load();
    svs_refitp4_handle.Load();
    trks_inner_position_handle.Load();
    trks_outer_p4_handle.Load();
    trks_outer_position_handle.Load();
    trks_trk_p4_handle.Load();
    trks_vertex_p4_handle.Load();
    trkjets_p4_handle.Load();
    vtxs_position_handle.Load();
    bsvtxs_position_handle.Load();
    els_convs_pos_p4_handle.Load();
    genps_lepdaughter_p4_handle.Load();
    hlt_trigObjs_p4_handle.Load();
    hyp_jets_p4_handle.Load();
    hyp_other_jets_p4_handle.Load();
    jpts_combinedSecondaryVertexBJetTag_handle.Load();
    jpts_combinedSecondaryVertexMVABJetTag_handle.Load();
    jpts_jetBProbabilityBJetTag_handle.Load();
    jpts_jetProbabilityBJetTag_handle.Load();
    jpts_simpleSecondaryVertexBJetTag_handle.Load();
    jpts_simpleSecondaryVertexHighEffBJetTag_handle.Load();
    jpts_simpleSecondaryVertexHighPurBJetTags_handle.Load();
    jpts_softElectronByIP3dBJetTag_handle.Load();
    jpts_softElectronByPtBJetTag_handle.Load();
    jpts_softElectronTag_handle.Load();
    jpts_softMuonBJetTag_handle.Load();
    jpts_softMuonByIP3dBJetTag_handle.Load();
    jpts_softMuonByPtBJetTag_handle.Load();
    jpts_trackCountingHighEffBJetTag_handle.Load();
    jpts_trackCountingHighPurBJetTag_handle.Load();
    jets_combinedSecondaryVertexBJetTag_handle.Load();
    jets_combinedSecondaryVertexMVABJetTag_handle.Load();
    jets_jetBProbabilityBJetTag_handle.Load();
    jets_jetProbabilityBJetTag_handle.Load();
    jets_simpleSecondaryVertexBJetTag_handle.Load();
    jets_simpleSecondaryVertexHighEffBJetTag_handle.Load();
    jets_simpleSecondaryVertexHighPurBJetTags_handle.Load();
    jets_softElectronByIP3dBJetTag_handle.Load();
    jets_softElectronByPtBJetTag_handle.Load();
    jets_softElectronTag_handle.Load();
    jets_softMuonBJetTag_handle.Load();
    jets_softMuonByIP3dBJetTag_handle.Load();
    jets_softMuonByPtBJetTag_handle.Load();
    jets_trackCountingHighEffBJetTag_handle.Load();
    jets_trackCountingHighPurBJetTag_handle.Load();
    pfjets_combinedSecondaryVertexBJetTag_handle.Load();
    pfjets_combinedSecondaryVertexMVABJetTag_handle.Load();
    pfjets_jetBProbabilityBJetTag_handle.Load();
    pfjets_jetProbabilityBJetTag_handle.Load();
    pfjets_simpleSecondaryVertexBJetTag_handle.Load();
    pfjets_simpleSecondaryVertexHighEffBJetTag_handle.Load();
    pfjets_simpleSecondaryVertexHighPurBJetTags_handle.Load();
    pfjets_softElectronByIP3dBJetTag_handle.Load();
    pfjets_softElectronByPtBJetTag_handle.Load();
    pfjets_softElectronTag_handle.Load();
    pfjets_softMuonBJetTag_handle.Load();
    pfjets_softMuonByIP3dBJetTag_handle.Load();
    pfjets_softMuonByPtBJetTag_handle.Load();
    pfjets_trackCountingHighEffBJetTag_handle.Load();
    pfjets_trackCountingHighPurBJetTag_handle.Load();
    trkjets_combinedSecondaryVertexBJetTag_handle.Load();
    trkjets_combinedSecondaryVertexMVABJetTag_handle.Load();
    trkjets_jetBProbabilityBJetTag_handle.Load();
    trkjets_jetProbabilityBJetTag_handle.Load();
    trkjets_simpleSecondaryVertexBJetTag_handle.Load();
    trkjets_simpleSecondaryVertexHighEffBJetTag_handle.Load();
    trkjets_simpleSecondaryVertexHighPurBJetTags_handle.Load();
    trkjets_softElectronByIP3dBJetTag_handle.Load();
    trkjets_softElectronByPtBJetTag_handle.Load();
    trkjets_softElectronTag_handle.Load();
    trkjets_softMuonBJetTag_handle.Load();
    trkjets_softMuonByIP3dBJetTag_handle.Load();
    trkjets_softMuonByPtBJetTag_handle.Load();
    trkjets_trackCountingHighEffBJetTag_handle.Load();
    trkjets_trackCountingHighPurBJetTag_handle.Load();
    evt_bs_covMatrix_handle.Load();
    els_mc3dr_handle.Load();
    els_mcdr_handle.Load();
    jets_mc3dr_handle.Load();
    jets_mcdr_handle.Load();
    jets_mc_emEnergy_handle.Load();
    jets_mc_gpdr_handle.Load();
    jets_mc_hadEnergy_handle.Load();
    jets_mc_invEnergy_handle.Load();
    jets_mc_otherEnergy_handle.Load();
    mus_mc3dr_handle.Load();
    mus_mcdr_handle.Load();
    pfjets_mc3dr_handle.Load();
    pfjets_mcdr_handle.Load();
    pfjets_mc_emEnergy_handle.Load();
    pfjets_mc_gpdr_handle.Load();
    pfjets_mc_hadEnergy_handle.Load();
    pfjets_mc_invEnergy_handle.Load();
    pfjets_mc_otherEnergy_handle.Load();
    photons_mc3dr_handle.Load();
    photons_mcdr_handle.Load();
    trk_mc3dr_handle.Load();
    trk_mcdr_handle.Load();
    els_ecalJuraIso_handle.Load();
    els_ecalJuraTowerIso_handle.Load();
    els_hcalConeIso_handle.Load();
    els_tkJuraIso_handle.Load();
    els_jetdr_handle.Load();
    els_musdr_handle.Load();
    els_isoR03_chpf_radial_handle.Load();
    els_isoR03_chpf_radialTight_handle.Load();
    els_isoR03_chpf_radialTight_bv_handle.Load();
    els_isoR03_chpf_radial_bv_handle.Load();
    els_isoR03_empf_radial_handle.Load();
    els_isoR03_empf_radialTight_handle.Load();
    els_isoR03_empf_radialTight_bv_handle.Load();
    els_isoR03_empf_radial_bv_handle.Load();
    els_isoR03_nhpf_radial_handle.Load();
    els_isoR03_nhpf_radialTight_handle.Load();
    els_isoR03_nhpf_radialTight_bv_handle.Load();
    els_isoR03_nhpf_radial_bv_handle.Load();
    els_isoR03_pf2012n0p5_ch_handle.Load();
    els_isoR03_pf2012n0p5_em_handle.Load();
    els_isoR03_pf2012n0p5_nh_handle.Load();
    els_isoR03_pf_radial_handle.Load();
    els_isoR03_pf_radialTight_handle.Load();
    els_isoR03_pf_radialTight_bv_handle.Load();
    els_isoR03_pf_radial_bv_handle.Load();
    els_chi2_handle.Load();
    els_ckf_chi2_handle.Load();
    els_ckf_ndof_handle.Load();
    els_conv_dcot_handle.Load();
    els_conv_dist_handle.Load();
    els_conv_old_dcot_handle.Load();
    els_conv_old_dist_handle.Load();
    els_conv_old_radius_handle.Load();
    els_conv_radius_handle.Load();
    els_d0_handle.Load();
    els_d0Err_handle.Load();
    els_d0corr_handle.Load();
    els_dEtaIn_handle.Load();
    els_dEtaOut_handle.Load();
    els_dPhiIn_handle.Load();
    els_dPhiInPhiOut_handle.Load();
    els_dPhiOut_handle.Load();
    els_deltaEtaEleClusterTrackAtCalo_handle.Load();
    els_deltaPhiEleClusterTrackAtCalo_handle.Load();
    els_e1x5_handle.Load();
    els_e2x5Max_handle.Load();
    els_e3x3_handle.Load();
    els_e5x5_handle.Load();
    els_eMax_handle.Load();
    els_eOverPIn_handle.Load();
    els_eOverPOut_handle.Load();
    els_eSC_handle.Load();
    els_eSCPresh_handle.Load();
    els_eSCRaw_handle.Load();
    els_eSeed_handle.Load();
    els_eSeedOverPIn_handle.Load();
    els_eSeedOverPOut_handle.Load();
    els_ecalEnergy_handle.Load();
    els_ecalEnergyError_handle.Load();
    els_ecalIso_handle.Load();
    els_ecalIso04_handle.Load();
    els_etaErr_handle.Load();
    els_etaSC_handle.Load();
    els_etaSCwidth_handle.Load();
    els_fbrem_handle.Load();
    els_hOverE_handle.Load();
    els_hcalDepth1OverEcal_handle.Load();
    els_hcalDepth1TowerSumEt_handle.Load();
    els_hcalDepth1TowerSumEt04_handle.Load();
    els_hcalDepth2OverEcal_handle.Load();
    els_hcalDepth2TowerSumEt_handle.Load();
    els_hcalDepth2TowerSumEt04_handle.Load();
    els_hcalIso_handle.Load();
    els_hcalIso04_handle.Load();
    els_ip3d_handle.Load();
    els_ip3derr_handle.Load();
    els_iso03_pf_handle.Load();
    els_iso03_pf2012_ch_handle.Load();
    els_iso03_pf2012_em_handle.Load();
    els_iso03_pf2012ext_ch_handle.Load();
    els_iso03_pf2012ext_em_handle.Load();
    els_iso03_pf2012ext_nh_handle.Load();
    els_iso03_pf2012_nh_handle.Load();
    els_iso03_pf_ch_handle.Load();
    els_iso03_pf_gamma05_handle.Load();
    els_iso03_pf_nhad05_handle.Load();
    els_iso04_pf_handle.Load();
    els_iso04_pf2012_ch_handle.Load();
    els_iso04_pf2012_em_handle.Load();
    els_iso04_pf2012ext_ch_handle.Load();
    els_iso04_pf2012ext_em_handle.Load();
    els_iso04_pf2012ext_nh_handle.Load();
    els_iso04_pf2012_nh_handle.Load();
    els_iso04_pf_ch_handle.Load();
    els_iso04_pf_gamma05_handle.Load();
    els_iso04_pf_nhad05_handle.Load();
    els_layer1_charge_handle.Load();
    els_lh_handle.Load();
    els_mva_handle.Load();
    els_ndof_handle.Load();
    els_pfChargedHadronIso_handle.Load();
    els_pfNeutralHadronIso_handle.Load();
    els_pfPhotonIso_handle.Load();
    els_phiErr_handle.Load();
    els_phiSC_handle.Load();
    els_phiSCwidth_handle.Load();
    els_ptErr_handle.Load();
    els_r9_handle.Load();
    els_sigmaEtaEta_handle.Load();
    els_sigmaIEtaIEta_handle.Load();
    els_sigmaIEtaIEtaSC_handle.Load();
    els_sigmaIEtaIPhi_handle.Load();
    els_sigmaIPhiIPhi_handle.Load();
    els_sigmaIPhiIPhiSC_handle.Load();
    els_sigmaIphiIphi_handle.Load();
    els_sigmaPhiPhi_handle.Load();
    els_tkIso_handle.Load();
    els_tkIso04_handle.Load();
    els_trackMomentumError_handle.Load();
    els_trkdr_handle.Load();
    els_trkshFrac_handle.Load();
    els_z0_handle.Load();
    els_z0Err_handle.Load();
    els_z0corr_handle.Load();
    gsftrks_chi2_handle.Load();
    gsftrks_d0_handle.Load();
    gsftrks_d0Err_handle.Load();
    gsftrks_d0corr_handle.Load();
    gsftrks_d0corrPhi_handle.Load();
    gsftrks_d0phiCov_handle.Load();
    gsftrks_etaErr_handle.Load();
    gsftrks_layer1_charge_handle.Load();
    gsftrks_ndof_handle.Load();
    gsftrks_phiErr_handle.Load();
    gsftrks_ptErr_handle.Load();
    gsftrks_z0_handle.Load();
    gsftrks_z0Err_handle.Load();
    gsftrks_z0corr_handle.Load();
    hyp_Ht_handle.Load();
    hyp_dPhi_nJet_metMuonJESCorr_handle.Load();
    hyp_dPhi_nJet_muCorrMet_handle.Load();
    hyp_dPhi_nJet_tcMet_handle.Load();
    hyp_dPhi_nJet_unCorrMet_handle.Load();
    hyp_ll_chi2_handle.Load();
    hyp_ll_d0_handle.Load();
    hyp_ll_d0Err_handle.Load();
    hyp_ll_d0corr_handle.Load();
    hyp_ll_dPhi_metMuonJESCorr_handle.Load();
    hyp_ll_dPhi_muCorrMet_handle.Load();
    hyp_ll_dPhi_tcMet_handle.Load();
    hyp_ll_dPhi_unCorrMet_handle.Load();
    hyp_ll_etaErr_handle.Load();
    hyp_ll_ndof_handle.Load();
    hyp_ll_phiErr_handle.Load();
    hyp_ll_ptErr_handle.Load();
    hyp_ll_z0_handle.Load();
    hyp_ll_z0Err_handle.Load();
    hyp_ll_z0corr_handle.Load();
    hyp_lt_chi2_handle.Load();
    hyp_lt_d0_handle.Load();
    hyp_lt_d0Err_handle.Load();
    hyp_lt_d0corr_handle.Load();
    hyp_lt_dPhi_metMuonJESCorr_handle.Load();
    hyp_lt_dPhi_muCorrMet_handle.Load();
    hyp_lt_dPhi_tcMet_handle.Load();
    hyp_lt_dPhi_unCorrMet_handle.Load();
    hyp_lt_etaErr_handle.Load();
    hyp_lt_ndof_handle.Load();
    hyp_lt_phiErr_handle.Load();
    hyp_lt_ptErr_handle.Load();
    hyp_lt_z0_handle.Load();
    hyp_lt_z0Err_handle.Load();
    hyp_lt_z0corr_handle.Load();
    hyp_mt2_metMuonJESCorr_handle.Load();
    hyp_mt2_muCorrMet_handle.Load();
    hyp_mt2_tcMet_handle.Load();
    hyp_sumJetPt_handle.Load();
    hyp_FVFit_chi2ndf_handle.Load();
    hyp_FVFit_prob_handle.Load();
    hyp_FVFit_v4cxx_handle.Load();
    hyp_FVFit_v4cxy_handle.Load();
    hyp_FVFit_v4cyy_handle.Load();
    hyp_FVFit_v4czx_handle.Load();
    hyp_FVFit_v4czy_handle.Load();
    hyp_FVFit_v4czz_handle.Load();
    jets_approximatefHPD_handle.Load();
    jets_approximatefRBX_handle.Load();
    jets_cor_handle.Load();
    jets_corL1FastL2L3_handle.Load();
    jets_corL1L2L3_handle.Load();
    jets_emFrac_handle.Load();
    jets_fHPD_handle.Load();
    jets_fRBX_handle.Load();
    jets_fSubDetector1_handle.Load();
    jets_fSubDetector2_handle.Load();
    jets_fSubDetector3_handle.Load();
    jets_fSubDetector4_handle.Load();
    jets_hitsInN90_handle.Load();
    jets_n90Hits_handle.Load();
    jets_nECALTowers_handle.Load();
    jets_nHCALTowers_handle.Load();
    jets_restrictedEMF_handle.Load();
    mus_met_deltax_handle.Load();
    mus_met_deltay_handle.Load();
    mus_eledr_handle.Load();
    mus_jetdr_handle.Load();
    mus_isoR03_chpf_radial_handle.Load();
    mus_isoR03_chpf_radialTight_handle.Load();
    mus_isoR03_empf_radial_handle.Load();
    mus_isoR03_empf_radialTight_handle.Load();
    mus_isoR03_nhpf_radial_handle.Load();
    mus_isoR03_nhpf_radialTight_handle.Load();
    mus_isoR03_pf_radial_handle.Load();
    mus_isoR03_pf_radialTight_handle.Load();
    mus_backToBackCompat_handle.Load();
    mus_caloCompatibility_handle.Load();
    mus_chi2_handle.Load();
    mus_chi2LocalMomentum_handle.Load();
    mus_chi2LocalPosition_handle.Load();
    mus_cosmicCompat_handle.Load();
    mus_d0_handle.Load();
    mus_d0Err_handle.Load();
    mus_d0corr_handle.Load();
    mus_e_em_handle.Load();
    mus_e_emS9_handle.Load();
    mus_e_had_handle.Load();
    mus_e_hadS9_handle.Load();
    mus_e_ho_handle.Load();
    mus_e_hoS9_handle.Load();
    mus_etaErr_handle.Load();
    mus_gfit_chi2_handle.Load();
    mus_gfit_d0_handle.Load();
    mus_gfit_d0Err_handle.Load();
    mus_gfit_d0corr_handle.Load();
    mus_gfit_ndof_handle.Load();
    mus_gfit_qoverp_handle.Load();
    mus_gfit_qoverpError_handle.Load();
    mus_gfit_z0_handle.Load();
    mus_gfit_z0Err_handle.Load();
    mus_gfit_z0corr_handle.Load();
    mus_glbKink_handle.Load();
    mus_glbTrackProbability_handle.Load();
    mus_globalDeltaEtaPhi_handle.Load();
    mus_ip3d_handle.Load();
    mus_ip3derr_handle.Load();
    mus_iso03_emEt_handle.Load();
    mus_iso03_hadEt_handle.Load();
    mus_iso03_hoEt_handle.Load();
    mus_iso03_pf_handle.Load();
    mus_iso03_sumPt_handle.Load();
    mus_iso04_pf_handle.Load();
    mus_iso05_emEt_handle.Load();
    mus_iso05_hadEt_handle.Load();
    mus_iso05_hoEt_handle.Load();
    mus_iso05_sumPt_handle.Load();
    mus_isoR03_pf_ChargedHadronPt_handle.Load();
    mus_isoR03_pf_ChargedParticlePt_handle.Load();
    mus_isoR03_pf_NeutralHadronEt_handle.Load();
    mus_isoR03_pf_NeutralHadronEtHighThreshold_handle.Load();
    mus_isoR03_pf_PUPt_handle.Load();
    mus_isoR03_pf_PhotonEt_handle.Load();
    mus_isoR03_pf_PhotonEtHighThreshold_handle.Load();
    mus_isoR04_pf_ChargedHadronPt_handle.Load();
    mus_isoR04_pf_ChargedParticlePt_handle.Load();
    mus_isoR04_pf_NeutralHadronEt_handle.Load();
    mus_isoR04_pf_NeutralHadronEtHighThreshold_handle.Load();
    mus_isoR04_pf_PUPt_handle.Load();
    mus_isoR04_pf_PhotonEt_handle.Load();
    mus_isoR04_pf_PhotonEtHighThreshold_handle.Load();
    mus_iso_ecalvetoDep_handle.Load();
    mus_iso_hcalvetoDep_handle.Load();
    mus_iso_hovetoDep_handle.Load();
    mus_iso_trckvetoDep_handle.Load();
    mus_localDistance_handle.Load();
    mus_ndof_handle.Load();
    mus_overlapCompat_handle.Load();
    mus_pfdeltaP_handle.Load();
    mus_pfecalE_handle.Load();
    mus_pfhcalE_handle.Load();
    mus_pfmva_emu_handle.Load();
    mus_pfmva_epi_handle.Load();
    mus_pfmva_nothing_gamma_handle.Load();
    mus_pfmva_nothing_nh_handle.Load();
    mus_pfmva_pimu_handle.Load();
    mus_pfpS1E_handle.Load();
    mus_pfpS2E_handle.Load();
    mus_pfrawEcalE_handle.Load();
    mus_pfrawHcalE_handle.Load();
    mus_phiErr_handle.Load();
    mus_ptErr_handle.Load();
    mus_qoverp_handle.Load();
    mus_qoverpError_handle.Load();
    mus_segmCompatibility_handle.Load();
    mus_staRelChi2_handle.Load();
    mus_sta_chi2_handle.Load();
    mus_sta_d0_handle.Load();
    mus_sta_d0Err_handle.Load();
    mus_sta_d0corr_handle.Load();
    mus_sta_ndof_handle.Load();
    mus_sta_qoverp_handle.Load();
    mus_sta_qoverpError_handle.Load();
    mus_sta_z0_handle.Load();
    mus_sta_z0Err_handle.Load();
    mus_sta_z0corr_handle.Load();
    mus_timeAtIpInOut_handle.Load();
    mus_timeAtIpInOutErr_handle.Load();
    mus_timeAtIpOutIn_handle.Load();
    mus_timeAtIpOutInErr_handle.Load();
    mus_timeCompat_handle.Load();
    mus_trkKink_handle.Load();
    mus_trkRelChi2_handle.Load();
    mus_vertexCompat_handle.Load();
    mus_vertexphi_handle.Load();
    mus_z0_handle.Load();
    mus_z0Err_handle.Load();
    mus_z0corr_handle.Load();
    pfjets_mvavalue_handle.Load();
    pfjets_full53xmva_beta_handle.Load();
    pfjets_full53xmva_betaStar_handle.Load();
    pfjets_full53xmva_d0_handle.Load();
    pfjets_full53xmva_dRMean_handle.Load();
    pfjets_full53xmva_dZ_handle.Load();
    pfjets_full53xmva_frac01_handle.Load();
    pfjets_full53xmva_frac02_handle.Load();
    pfjets_full53xmva_frac03_handle.Load();
    pfjets_full53xmva_frac04_handle.Load();
    pfjets_full53xmva_frac05_handle.Load();
    pfjets_full53xmva_nCharged_handle.Load();
    pfjets_full53xmva_nNeutrals_handle.Load();
    pfjets_full53xmva_nvtx_handle.Load();
    pfjets_full53xmvavalue_handle.Load();
    pfjets_full5xmvavalue_handle.Load();
    trkjet_met_handle.Load();
    trkjet_metPhi_handle.Load();
    trkjet_sumet_handle.Load();
    trk_met_handle.Load();
    trk_metPhi_handle.Load();
    trk_sumet_handle.Load();
    pfcands_deltaP_handle.Load();
    pfcands_ecalE_handle.Load();
    pfcands_hcalE_handle.Load();
    pfcands_mva_emu_handle.Load();
    pfcands_mva_epi_handle.Load();
    pfcands_mva_nothing_gamma_handle.Load();
    pfcands_mva_nothing_nh_handle.Load();
    pfcands_mva_pimu_handle.Load();
    pfcands_pS1E_handle.Load();
    pfcands_pS2E_handle.Load();
    pfcands_rawEcalE_handle.Load();
    pfcands_rawHcalE_handle.Load();
    pfels_deltaP_handle.Load();
    pfels_ecalE_handle.Load();
    pfels_hcalE_handle.Load();
    pfels_iso04ChargedHadrons_handle.Load();
    pfels_iso04NeutralHadrons_handle.Load();
    pfels_iso04Photons_handle.Load();
    pfels_isoChargedHadrons_handle.Load();
    pfels_isoNeutralHadrons_handle.Load();
    pfels_isoPhotons_handle.Load();
    pfels_mva_emu_handle.Load();
    pfels_mva_epi_handle.Load();
    pfels_mva_nothing_gamma_handle.Load();
    pfels_mva_nothing_nh_handle.Load();
    pfels_mva_pimu_handle.Load();
    pfels_pS1E_handle.Load();
    pfels_pS2E_handle.Load();
    pfels_rawEcalE_handle.Load();
    pfels_rawHcalE_handle.Load();
    pfjets_area_handle.Load();
    pfjets_chargedEmE_handle.Load();
    pfjets_chargedHadronE_handle.Load();
    pfjets_cor_handle.Load();
    pfjets_corL1Fast_handle.Load();
    pfjets_corL1FastL2L3_handle.Load();
    pfjets_corL1FastL2L3residual_handle.Load();
    pfjets_corL1L2L3_handle.Load();
    pfjets_electronE_handle.Load();
    pfjets_hfEmE_handle.Load();
    pfjets_hfHadronE_handle.Load();
    pfjets_muonE_handle.Load();
    pfjets_neutralEmE_handle.Load();
    pfjets_neutralHadronE_handle.Load();
    pfjets_photonE_handle.Load();
    pfmus_deltaP_handle.Load();
    pfmus_ecalE_handle.Load();
    pfmus_hcalE_handle.Load();
    pfmus_iso04ChargedHadrons_handle.Load();
    pfmus_iso04NeutralHadrons_handle.Load();
    pfmus_iso04Photons_handle.Load();
    pfmus_isoChargedHadrons_handle.Load();
    pfmus_isoNeutralHadrons_handle.Load();
    pfmus_isoPhotons_handle.Load();
    pfmus_mva_emu_handle.Load();
    pfmus_mva_epi_handle.Load();
    pfmus_mva_nothing_gamma_handle.Load();
    pfmus_mva_nothing_nh_handle.Load();
    pfmus_mva_pimu_handle.Load();
    pfmus_pS1E_handle.Load();
    pfmus_pS2E_handle.Load();
    pfmus_rawEcalE_handle.Load();
    pfmus_rawHcalE_handle.Load();
    taus_pf_againstElectronDeadECAL_handle.Load();
    taus_pf_againstElectronLoose_handle.Load();
    taus_pf_againstElectronLooseMVA2_handle.Load();
    taus_pf_againstElectronLooseMVA3_handle.Load();
    taus_pf_againstElectronMVA_handle.Load();
    taus_pf_againstElectronMVA2category_handle.Load();
    taus_pf_againstElectronMVA2raw_handle.Load();
    taus_pf_againstElectronMVA3category_handle.Load();
    taus_pf_againstElectronMVA3raw_handle.Load();
    taus_pf_againstElectronMedium_handle.Load();
    taus_pf_againstElectronMediumMVA2_handle.Load();
    taus_pf_againstElectronMediumMVA3_handle.Load();
    taus_pf_againstElectronTight_handle.Load();
    taus_pf_againstElectronTightMVA2_handle.Load();
    taus_pf_againstElectronTightMVA3_handle.Load();
    taus_pf_againstElectronVLooseMVA2_handle.Load();
    taus_pf_againstElectronVTightMVA3_handle.Load();
    taus_pf_againstMuonLoose_handle.Load();
    taus_pf_againstMuonLoose2_handle.Load();
    taus_pf_againstMuonMedium_handle.Load();
    taus_pf_againstMuonMedium2_handle.Load();
    taus_pf_againstMuonTight_handle.Load();
    taus_pf_againstMuonTight2_handle.Load();
    taus_pf_byCombinedIsolationDeltaBetaCorrRaw_handle.Load();
    taus_pf_byCombinedIsolationDeltaBetaCorrRaw3Hits_handle.Load();
    taus_pf_byDecayModeFinding_handle.Load();
    taus_pf_byIsolationMVA2raw_handle.Load();
    taus_pf_byIsolationMVAraw_handle.Load();
    taus_pf_byLooseCombinedIsolationDeltaBetaCorr_handle.Load();
    taus_pf_byLooseCombinedIsolationDeltaBetaCorr3Hits_handle.Load();
    taus_pf_byLooseIsolationMVA_handle.Load();
    taus_pf_byLooseIsolationMVA2_handle.Load();
    taus_pf_byMediumCombinedIsolationDeltaBetaCorr_handle.Load();
    taus_pf_byMediumCombinedIsolationDeltaBetaCorr3Hits_handle.Load();
    taus_pf_byMediumIsolationMVA_handle.Load();
    taus_pf_byMediumIsolationMVA2_handle.Load();
    taus_pf_byTightCombinedIsolationDeltaBetaCorr_handle.Load();
    taus_pf_byTightCombinedIsolationDeltaBetaCorr3Hits_handle.Load();
    taus_pf_byTightIsolationMVA_handle.Load();
    taus_pf_byTightIsolationMVA2_handle.Load();
    taus_pf_byVLooseCombinedIsolationDeltaBetaCorr_handle.Load();
    photons_e1x5_handle.Load();
    photons_e2x5Max_handle.Load();
    photons_e3x3_handle.Load();
    photons_e5x5_handle.Load();
    photons_ecalIso03_handle.Load();
    photons_ecalIso04_handle.Load();
    photons_hOverE_handle.Load();
    photons_hcalDepth1TowerSumEtBcConeDR03_handle.Load();
    photons_hcalDepth1TowerSumEtBcConeDR04_handle.Load();
    photons_hcalDepth2TowerSumEtBcConeDR03_handle.Load();
    photons_hcalDepth2TowerSumEtBcConeDR04_handle.Load();
    photons_hcalIso03_handle.Load();
    photons_hcalIso04_handle.Load();
    photons_hcalTowerSumEtBcConeDR03_handle.Load();
    photons_hcalTowerSumEtBcConeDR04_handle.Load();
    photons_ntkIsoHollow03_handle.Load();
    photons_ntkIsoHollow04_handle.Load();
    photons_ntkIsoSolid03_handle.Load();
    photons_ntkIsoSolid04_handle.Load();
    photons_sigmaEtaEta_handle.Load();
    photons_sigmaIEtaIEta_handle.Load();
    photons_swissSeed_handle.Load();
    photons_tkIsoHollow03_handle.Load();
    photons_tkIsoHollow04_handle.Load();
    photons_tkIsoSolid03_handle.Load();
    photons_tkIsoSolid04_handle.Load();
    puInfo_trueNumInteractions_handle.Load();
    convs_chi2_handle.Load();
    convs_dl_handle.Load();
    convs_ndof_handle.Load();
    sparm_values_handle.Load();
    scs_clustersSize_handle.Load();
    scs_crystalsSize_handle.Load();
    scs_e1x3_handle.Load();
    scs_e1x5_handle.Load();
    scs_e2nd_handle.Load();
    scs_e2x2_handle.Load();
    scs_e2x5Max_handle.Load();
    scs_e3x1_handle.Load();
    scs_e3x2_handle.Load();
    scs_e3x3_handle.Load();
    scs_e4x4_handle.Load();
    scs_e5x5_handle.Load();
    scs_eMax_handle.Load();
    scs_eSeed_handle.Load();
    scs_energy_handle.Load();
    scs_eta_handle.Load();
    scs_hoe_handle.Load();
    scs_laserCorMax_handle.Load();
    scs_laserCorMean_handle.Load();
    scs_laserCorSeed_handle.Load();
    scs_phi_handle.Load();
    scs_preshowerEnergy_handle.Load();
    scs_rawEnergy_handle.Load();
    scs_sigmaEtaEta_handle.Load();
    scs_sigmaEtaPhi_handle.Load();
    scs_sigmaIEtaIEta_handle.Load();
    scs_sigmaIEtaIEtaSC_handle.Load();
    scs_sigmaIEtaIPhi_handle.Load();
    scs_sigmaIEtaIPhiSC_handle.Load();
    scs_sigmaIPhiIPhi_handle.Load();
    scs_sigmaIPhiIPhiSC_handle.Load();
    scs_sigmaPhiPhi_handle.Load();
    scs_timeSeed_handle.Load();
    svs_anglePV_handle.Load();
    svs_chi2_handle.Load();
    svs_dist3Dsig_handle.Load();
    svs_dist3Dval_handle.Load();
    svs_distXYsig_handle.Load();
    svs_distXYval_handle.Load();
    svs_ndof_handle.Load();
    svs_prob_handle.Load();
    svs_xError_handle.Load();
    svs_yError_handle.Load();
    svs_zError_handle.Load();
    mus_tcmet_deltax_handle.Load();
    mus_tcmet_deltay_handle.Load();
    pfcands_dzpv_handle.Load();
    pfcands_trkiso_handle.Load();
    trks_chi2_handle.Load();
    trks_d0_handle.Load();
    trks_d0Err_handle.Load();
    trks_d0corr_handle.Load();
    trks_d0corrPhi_handle.Load();
    trks_d0phiCov_handle.Load();
    trks_etaErr_handle.Load();
    trks_layer1_charge_handle.Load();
    trks_ndof_handle.Load();
    trks_phiErr_handle.Load();
    trks_ptErr_handle.Load();
    trks_validFraction_handle.Load();
    trks_z0_handle.Load();
    trks_z0Err_handle.Load();
    trks_z0corr_handle.Load();
    trkjets_cor_handle.Load();
    trks_d0Errvtx_handle.Load();
    trks_d0vtx_handle.Load();
    vtxs_chi2_handle.Load();
    vtxs_ndof_handle.Load();
    vtxs_sumpt_handle.Load();
    vtxs_xError_handle.Load();
    vtxs_yError_handle.Load();
    vtxs_zError_handle.Load();
    bsvtxs_chi2_handle.Load();
    bsvtxs_ndof_handle.Load();
    bsvtxs_sumpt_handle.Load();
    bsvtxs_xError_handle.Load();
    bsvtxs_yError_handle.Load();
    bsvtxs_zError_handle.Load();
    els_convs_dcot_handle.Load();
    els_convs_dist_handle.Load();
    els_convs_radius_handle.Load();
    mus_stationShowerDeltaR_handle.Load();
    mus_stationShowerSizeT_handle.Load();
    puInfo_instLumi_handle.Load();
    puInfo_sump_highpt_handle.Load();
    puInfo_sumpt_lowpt_handle.Load();
    puInfo_zpositions_handle.Load();
    vtxs_covMatrix_handle.Load();
    bsvtxs_covMatrix_handle.Load();
    evt_cscLooseHaloId_handle.Load();
    evt_cscTightHaloId_handle.Load();
    evt_ecalLooseHaloId_handle.Load();
    evt_ecalTightHaloId_handle.Load();
    evt_extremeTightHaloId_handle.Load();
    evt_globalLooseHaloId_handle.Load();
    evt_globalTightHaloId_handle.Load();
    evt_hcalLooseHaloId_handle.Load();
    evt_hcalTightHaloId_handle.Load();
    evt_looseHaloId_handle.Load();
    evt_nHaloLikeTracks_handle.Load();
    evt_nHaloTriggerCandidates_handle.Load();
    evt_tightHaloId_handle.Load();
    evt_bsType_handle.Load();
    evt_bunchCrossing_handle.Load();
    evt_experimentType_handle.Load();
    evt_isRealData_handle.Load();
    evt_orbitNumber_handle.Load();
    evt_storeNumber_handle.Load();
    hcalnoise_GetRecHitCount_handle.Load();
    hcalnoise_GetRecHitCount15_handle.Load();
    hcalnoise_maxHPDHits_handle.Load();
    hcalnoise_maxHPDNoOtherHits_handle.Load();
    hcalnoise_maxRBXHits_handle.Load();
    hcalnoise_maxZeros_handle.Load();
    hcalnoise_noiseFilterStatus_handle.Load();
    hcalnoise_noiseType_handle.Load();
    hcalnoise_num10GeVHits_handle.Load();
    hcalnoise_num25GeVHits_handle.Load();
    hcalnoise_numFlatNoiseChannels_handle.Load();
    hcalnoise_numIsolatedNoiseChannels_handle.Load();
    hcalnoise_numProblematicRBXs_handle.Load();
    hcalnoise_numSpikeNoiseChannels_handle.Load();
    hcalnoise_numTS4TS5NoiseChannels_handle.Load();
    hcalnoise_numTriangleNoiseChannels_handle.Load();
    hcalnoise_passHighLevelNoiseFilter_handle.Load();
    hcalnoise_passLooseNoiseFilter_handle.Load();
    hcalnoise_passTightNoiseFilter_handle.Load();
    l1_nemiso_handle.Load();
    l1_nemnoiso_handle.Load();
    l1_njetsc_handle.Load();
    l1_njetsf_handle.Load();
    l1_njetst_handle.Load();
    l1_nmus_handle.Load();
    ls_lumiSecQual_handle.Load();
    pdfinfo_id1_handle.Load();
    pdfinfo_id2_handle.Load();
    sparm_subProcessId_handle.Load();
    evt_ecaliPhiSuspects_handle.Load();
    evt_globaliPhiSuspects_handle.Load();
    evt_hcaliPhiSuspects_handle.Load();
    els_mc3_id_handle.Load();
    els_mc3idx_handle.Load();
    els_mc3_motherid_handle.Load();
    els_mc3_motheridx_handle.Load();
    els_mc_id_handle.Load();
    els_mcidx_handle.Load();
    els_mc_motherid_handle.Load();
    jets_mc3_id_handle.Load();
    jets_mc3idx_handle.Load();
    jets_mc_gpidx_handle.Load();
    jets_mc_id_handle.Load();
    jets_mcidx_handle.Load();
    jets_mc_motherid_handle.Load();
    mus_mc3_id_handle.Load();
    mus_mc3idx_handle.Load();
    mus_mc3_motherid_handle.Load();
    mus_mc3_motheridx_handle.Load();
    mus_mc_id_handle.Load();
    mus_mcidx_handle.Load();
    mus_mc_motherid_handle.Load();
    pfjets_mc3_id_handle.Load();
    pfjets_mc3idx_handle.Load();
    pfjets_mc_gpidx_handle.Load();
    pfjets_mc_id_handle.Load();
    pfjets_mcidx_handle.Load();
    pfjets_mc_motherid_handle.Load();
    photons_mc3_id_handle.Load();
    photons_mc3idx_handle.Load();
    photons_mc3_motherid_handle.Load();
    photons_mc3_motheridx_handle.Load();
    photons_mc_id_handle.Load();
    photons_mcidx_handle.Load();
    photons_mc_motherid_handle.Load();
    trk_mc3_id_handle.Load();
    trk_mc3idx_handle.Load();
    trk_mc3_motherid_handle.Load();
    trk_mc3_motheridx_handle.Load();
    trk_mc_id_handle.Load();
    trk_mcidx_handle.Load();
    trk_mc_motherid_handle.Load();
    els_closestJet_handle.Load();
    els_closestMuon_handle.Load();
    els_pfelsidx_handle.Load();
    els_category_handle.Load();
    els_charge_handle.Load();
    els_ckf_laywithmeas_handle.Load();
    els_class_handle.Load();
    els_conv_delMissHits_handle.Load();
    els_conv_flag_handle.Load();
    els_conv_gsftkidx_handle.Load();
    els_conv_old_delMissHits_handle.Load();
    els_conv_old_flag_handle.Load();
    els_conv_old_gsftkidx_handle.Load();
    els_conv_old_tkidx_handle.Load();
    els_conv_tkidx_handle.Load();
    els_exp_innerlayers_handle.Load();
    els_exp_outerlayers_handle.Load();
    els_fiduciality_handle.Load();
    els_gsftrkidx_handle.Load();
    els_layer1_det_handle.Load();
    els_layer1_layer_handle.Load();
    els_layer1_sizerphi_handle.Load();
    els_layer1_sizerz_handle.Load();
    els_lostHits_handle.Load();
    els_lost_pixelhits_handle.Load();
    els_nSeed_handle.Load();
    els_sccharge_handle.Load();
    els_scindex_handle.Load();
    els_trk_charge_handle.Load();
    els_trkidx_handle.Load();
    els_type_handle.Load();
    els_validHits_handle.Load();
    els_valid_pixelhits_handle.Load();
    genps_id_handle.Load();
    genps_id_mother_handle.Load();
    genps_status_handle.Load();
    gsftrks_charge_handle.Load();
    gsftrks_exp_innerlayers_handle.Load();
    gsftrks_exp_outerlayers_handle.Load();
    gsftrks_layer1_det_handle.Load();
    gsftrks_layer1_layer_handle.Load();
    gsftrks_layer1_sizerphi_handle.Load();
    gsftrks_layer1_sizerz_handle.Load();
    gsftrks_lostHits_handle.Load();
    gsftrks_lost_pixelhits_handle.Load();
    gsftrks_nlayers_handle.Load();
    gsftrks_nlayers3D_handle.Load();
    gsftrks_nlayersLost_handle.Load();
    gsftrks_validHits_handle.Load();
    gsftrks_valid_pixelhits_handle.Load();
    hyp_ll_charge_handle.Load();
    hyp_ll_id_handle.Load();
    hyp_ll_index_handle.Load();
    hyp_ll_lostHits_handle.Load();
    hyp_ll_validHits_handle.Load();
    hyp_lt_charge_handle.Load();
    hyp_lt_id_handle.Load();
    hyp_lt_index_handle.Load();
    hyp_lt_lostHits_handle.Load();
    hyp_lt_validHits_handle.Load();
    hyp_njets_handle.Load();
    hyp_nojets_handle.Load();
    hyp_type_handle.Load();
    hyp_FVFit_ndf_handle.Load();
    hyp_FVFit_status_handle.Load();
    hyp_ll_mc_id_handle.Load();
    hyp_ll_mc_motherid_handle.Load();
    hyp_lt_mc_id_handle.Load();
    hyp_lt_mc_motherid_handle.Load();
    pfjets_mcflavorAlgo_handle.Load();
    pfjets_mcflavorPhys_handle.Load();
    jets_closestElectron_handle.Load();
    jets_closestMuon_handle.Load();
    l1_emiso_ieta_handle.Load();
    l1_emiso_iphi_handle.Load();
    l1_emiso_rawId_handle.Load();
    l1_emiso_type_handle.Load();
    l1_emnoiso_ieta_handle.Load();
    l1_emnoiso_iphi_handle.Load();
    l1_emnoiso_rawId_handle.Load();
    l1_emnoiso_type_handle.Load();
    l1_jetsc_ieta_handle.Load();
    l1_jetsc_iphi_handle.Load();
    l1_jetsc_rawId_handle.Load();
    l1_jetsc_type_handle.Load();
    l1_jetsf_ieta_handle.Load();
    l1_jetsf_iphi_handle.Load();
    l1_jetsf_rawId_handle.Load();
    l1_jetsf_type_handle.Load();
    l1_jetst_ieta_handle.Load();
    l1_jetst_iphi_handle.Load();
    l1_jetst_rawId_handle.Load();
    l1_jetst_type_handle.Load();
    l1_mus_flags_handle.Load();
    l1_mus_q_handle.Load();
    l1_mus_qual_handle.Load();
    l1_mus_qualFlags_handle.Load();
    mus_met_flag_handle.Load();
    mus_closestEle_handle.Load();
    mus_closestJet_handle.Load();
    mus_pfmusidx_handle.Load();
    mus_charge_handle.Load();
    mus_gfit_validHits_handle.Load();
    mus_gfit_validSTAHits_handle.Load();
    mus_gfit_validSiHits_handle.Load();
    mus_goodmask_handle.Load();
    mus_iso03_ntrk_handle.Load();
    mus_iso05_ntrk_handle.Load();
    mus_lostHits_handle.Load();
    mus_muonBestTrackType_handle.Load();
    mus_nOverlaps_handle.Load();
    mus_nmatches_handle.Load();
    mus_numberOfMatchedStations_handle.Load();
    mus_overlap0_handle.Load();
    mus_overlap1_handle.Load();
    mus_pfcharge_handle.Load();
    mus_pfflag_handle.Load();
    mus_pfparticleId_handle.Load();
    mus_pid_PFMuon_handle.Load();
    mus_pid_TM2DCompatibilityLoose_handle.Load();
    mus_pid_TM2DCompatibilityTight_handle.Load();
    mus_pid_TMLastStationLoose_handle.Load();
    mus_pid_TMLastStationTight_handle.Load();
    mus_sta_validHits_handle.Load();
    mus_timeDirection_handle.Load();
    mus_timeNumStationsUsed_handle.Load();
    mus_trk_charge_handle.Load();
    mus_trkidx_handle.Load();
    mus_type_handle.Load();
    mus_validHits_handle.Load();
    pfcands_charge_handle.Load();
    pfcands_flag_handle.Load();
    pfcands_particleId_handle.Load();
    pfcands_pfelsidx_handle.Load();
    pfcands_pfmusidx_handle.Load();
    pfcands_trkidx_handle.Load();
    pfcands_vtxidx_handle.Load();
    pfels_elsidx_handle.Load();
    pfels_charge_handle.Load();
    pfels_flag_handle.Load();
    pfels_particleId_handle.Load();
    pfjets_chargedHadronMultiplicity_handle.Load();
    pfjets_chargedMultiplicity_handle.Load();
    pfjets_electronMultiplicity_handle.Load();
    pfjets_hfEmMultiplicity_handle.Load();
    pfjets_hfHadronMultiplicity_handle.Load();
    pfjets_muonMultiplicity_handle.Load();
    pfjets_neutralHadronMultiplicity_handle.Load();
    pfjets_neutralMultiplicity_handle.Load();
    pfjets_photonMultiplicity_handle.Load();
    pfmus_musidx_handle.Load();
    pfmus_charge_handle.Load();
    pfmus_flag_handle.Load();
    pfmus_particleId_handle.Load();
    taus_pf_charge_handle.Load();
    taus_pf_pfjetIndex_handle.Load();
    photons_fiduciality_handle.Load();
    photons_scindex_handle.Load();
    puInfo_bunchCrossing_handle.Load();
    puInfo_nPUvertices_handle.Load();
    convs_algo_handle.Load();
    convs_isConverted_handle.Load();
    convs_quality_handle.Load();
    scs_detIdSeed_handle.Load();
    scs_elsidx_handle.Load();
    scs_severitySeed_handle.Load();
    svs_isKs_handle.Load();
    svs_isLambda_handle.Load();
    svs_mc3_id_handle.Load();
    svs_nTrks_handle.Load();
    mus_tcmet_flag_handle.Load();
    trks_algo_handle.Load();
    trks_charge_handle.Load();
    trks_exp_innerlayers_handle.Load();
    trks_exp_outerlayers_handle.Load();
    trks_layer1_det_handle.Load();
    trks_layer1_layer_handle.Load();
    trks_layer1_sizerphi_handle.Load();
    trks_layer1_sizerz_handle.Load();
    trks_lostHits_handle.Load();
    trks_lost_pixelhits_handle.Load();
    trks_nLoops_handle.Load();
    trks_nlayers_handle.Load();
    trks_nlayers3D_handle.Load();
    trks_nlayersLost_handle.Load();
    trks_pvidx0_handle.Load();
    trks_pvidx1_handle.Load();
    trks_qualityMask_handle.Load();
    trks_validHits_handle.Load();
    trks_valid_pixelhits_handle.Load();
    trks_elsidx_handle.Load();
    trk_musidx_handle.Load();
    trkjets_ntrks_handle.Load();
    trkjets_vtxs_idx_handle.Load();
    vtxs_isFake_handle.Load();
    vtxs_isValid_handle.Load();
    vtxs_tracksSize_handle.Load();
    bsvtxs_isFake_handle.Load();
    bsvtxs_isValid_handle.Load();
    bsvtxs_tracksSize_handle.Load();
    els_convs_delMissHits_handle.Load();
    els_convs_flag_handle.Load();
    els_convs_gsftkidx_handle.Load();
    els_convs_tkidx_handle.Load();
    genps_lepdaughter_id_handle.Load();
    genps_lepdaughter_idx_handle.Load();
    hlt_trigObjs_id_handle.Load();
    hyp_jets_idx_handle.Load();
    hyp_other_jets_idx_handle.Load();
    mus_nStationCorrelatedHits_handle.Load();
    mus_nStationHits_handle.Load();
    pfjets_pfcandIndicies_handle.Load();
    taus_pf_pfcandIndicies_handle.Load();
    puInfo_ntrks_highpt_handle.Load();
    puInfo_ntrks_lowpt_handle.Load();
    convs_nHitsBeforeVtx_handle.Load();
    convs_tkalgo_handle.Load();
    convs_tkidx_handle.Load();
    els_HLT_Ele17_Ele8_L1sL1DoubleEG137_version_handle.Load();
    els_HLT_Ele17_Ele8_LeadingLeg_version_handle.Load();
    els_HLT_Ele17_Ele8_Mass50_LeadingLeg_version_handle.Load();
    els_HLT_Ele17_Ele8_Mass50_TrailingLeg_version_handle.Load();
    els_HLT_Ele17_Ele8_TrailingLeg_version_handle.Load();
    els_HLT_Ele17_Ele8_version_handle.Load();
    els_HLT_Ele20_SC4_Mass50_LeadingLeg_version_handle.Load();
    els_HLT_Ele20_SC4_Mass50_TrailingLeg_version_handle.Load();
    els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_version_handle.Load();
    els_HLT_Ele27_WP80_version_handle.Load();
    els_HLT_Ele32_SC17_Mass50_LeadingLeg_version_handle.Load();
    els_HLT_Ele32_SC17_Mass50_TrailingLeg_version_handle.Load();
    els_HLT_Mu17_Ele8_TrailingLeg_version_handle.Load();
    els_HLT_Mu17_Ele8_version_handle.Load();
    els_HLT_Mu8_Ele17_version_handle.Load();
    evt_nels_handle.Load();
    evt_detectorStatus_handle.Load();
    evt_event_handle.Load();
    evt_lumiBlock_handle.Load();
    evt_run_handle.Load();
    genps_flavorHistoryFilterResult_handle.Load();
    evt_ngenjets_handle.Load();
    genps_signalProcessID_handle.Load();
    evt_njets_handle.Load();
    l1_bits1_handle.Load();
    l1_bits2_handle.Load();
    l1_bits3_handle.Load();
    l1_bits4_handle.Load();
    l1_techbits1_handle.Load();
    l1_techbits2_handle.Load();
    ls_lsNumber_handle.Load();
    ls_numOrbit_handle.Load();
    ls_startOrbit_handle.Load();
    mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_version_handle.Load();
    mus_HLT_IsoMu24_eta2p1_version_handle.Load();
    mus_HLT_Mu17_Ele8_LeadingLeg_version_handle.Load();
    mus_HLT_Mu17_Ele8_version_handle.Load();
    mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_version_handle.Load();
    mus_HLT_Mu17_Mu8_LeadingLeg_version_handle.Load();
    mus_HLT_Mu17_Mu8_TrailingLeg_version_handle.Load();
    mus_HLT_Mu17_Mu8_version_handle.Load();
    mus_HLT_Mu17_TkMu8_LeadingLeg_version_handle.Load();
    mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_version_handle.Load();
    mus_HLT_Mu17_TkMu8_TrailingLeg_version_handle.Load();
    mus_HLT_Mu17_TkMu8_version_handle.Load();
    mus_HLT_Mu8_Ele17_TrailingLeg_version_handle.Load();
    mus_HLT_Mu8_Ele17_version_handle.Load();
    evt_nphotons_handle.Load();
    evt_ecalRecoStatus_handle.Load();
    evt_nscs_handle.Load();
    evt_ntrkjets_handle.Load();
    evt_nvtxs_handle.Load();
    evt_nbsvtxs_handle.Load();
    els_HLT_Ele17_Ele8_handle.Load();
    els_HLT_Ele17_Ele8_L1sL1DoubleEG137_handle.Load();
    els_HLT_Ele17_Ele8_LeadingLeg_handle.Load();
    els_HLT_Ele17_Ele8_Mass50_LeadingLeg_handle.Load();
    els_HLT_Ele17_Ele8_Mass50_TrailingLeg_handle.Load();
    els_HLT_Ele17_Ele8_TrailingLeg_handle.Load();
    els_HLT_Ele20_SC4_Mass50_LeadingLeg_handle.Load();
    els_HLT_Ele20_SC4_Mass50_TrailingLeg_handle.Load();
    els_HLT_Ele27_WP80_handle.Load();
    els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_handle.Load();
    els_HLT_Ele32_SC17_Mass50_LeadingLeg_handle.Load();
    els_HLT_Ele32_SC17_Mass50_TrailingLeg_handle.Load();
    els_HLT_Mu17_Ele8_handle.Load();
    els_HLT_Mu17_Ele8_TrailingLeg_handle.Load();
    els_HLT_Mu8_Ele17_handle.Load();
    els_id2012ext_loose_handle.Load();
    els_id2012ext_medium_handle.Load();
    els_id2012ext_tight_handle.Load();
    els_id2012ext_veto_handle.Load();
    els_id2012_loose_handle.Load();
    els_id2012_medium_handle.Load();
    els_id2012_tight_handle.Load();
    els_id2012_veto_handle.Load();
    hlt_prescales_handle.Load();
    l1_prescales_handle.Load();
    l1_techtrigprescales_handle.Load();
    mus_HLT_IsoMu24_eta2p1_handle.Load();
    mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_handle.Load();
    mus_HLT_Mu17_Ele8_handle.Load();
    mus_HLT_Mu17_Ele8_LeadingLeg_handle.Load();
    mus_HLT_Mu17_Mu8_handle.Load();
    mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_handle.Load();
    mus_HLT_Mu17_Mu8_LeadingLeg_handle.Load();
    mus_HLT_Mu17_Mu8_TrailingLeg_handle.Load();
    mus_HLT_Mu17_TkMu8_handle.Load();
    mus_HLT_Mu17_TkMu8_LeadingLeg_handle.Load();
    mus_HLT_Mu17_TkMu8_TrailingLeg_handle.Load();
    mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_handle.Load();
    mus_HLT_Mu8_Ele17_handle.Load();
    mus_HLT_Mu8_Ele17_TrailingLeg_handle.Load();
    evt_timestamp_handle.Load();
    evt_nEvts_handle.Load();
    evt_filt_eff_handle.Load();

}

// branch accessor methods:
const TBits& CMS2::hlt_bits() {return hlt_bits_handle.get();}
const std::vector<TString>& CMS2::evt_CMS2tag() {return evt_CMS2tag_handle.get();}
const std::vector<TString>& CMS2::evt_dataset() {return evt_dataset_handle.get();}
const std::vector<TString>& CMS2::hlt_trigNames() {return hlt_trigNames_handle.get();}
const std::vector<TString>& CMS2::l1_techtrigNames() {return l1_techtrigNames_handle.get();}
const std::vector<TString>& CMS2::l1_trigNames() {return l1_trigNames_handle.get();}
const std::vector<TString>& CMS2::evt_errCategory() {return evt_errCategory_handle.get();}
const std::vector<TString>& CMS2::evt_errModule() {return evt_errModule_handle.get();}
const std::vector<TString>& CMS2::evt_errSeverity() {return evt_errSeverity_handle.get();}
const std::vector<TString>& CMS2::sparm_comment() {return sparm_comment_handle.get();}
const std::vector<TString>& CMS2::sparm_names() {return sparm_names_handle.get();}
const bool& CMS2::evt_eventHasHalo() {return evt_eventHasHalo_handle.get();}
const bool& CMS2::hcalnoise_HasBadRBXTS4TS5() {return hcalnoise_HasBadRBXTS4TS5_handle.get();}
const bool& CMS2::ls_isValid() {return ls_isValid_handle.get();}
const bool& CMS2::filt_ecalBE() {return filt_ecalBE_handle.get();}
const bool& CMS2::filt_ecalDR() {return filt_ecalDR_handle.get();}
const bool& CMS2::filt_ecalLaser() {return filt_ecalLaser_handle.get();}
const bool& CMS2::filt_ecalTP() {return filt_ecalTP_handle.get();}
const bool& CMS2::filt_eeBadSc() {return filt_eeBadSc_handle.get();}
const bool& CMS2::filt_greedyMuon() {return filt_greedyMuon_handle.get();}
const bool& CMS2::filt_hcalLaser() {return filt_hcalLaser_handle.get();}
const bool& CMS2::filt_inconsistentMuon() {return filt_inconsistentMuon_handle.get();}
const bool& CMS2::filt_jetIDFailure() {return filt_jetIDFailure_handle.get();}
const bool& CMS2::filt_multiEvent() {return filt_multiEvent_handle.get();}
const bool& CMS2::filt_trackingFailure() {return filt_trackingFailure_handle.get();}
const bool& CMS2::evt_hbheFilter() {return evt_hbheFilter_handle.get();}
const std::vector<bool>& CMS2::els_conv_vtx_flag() {return els_conv_vtx_flag_handle.get();}
const std::vector<bool>& CMS2::els_passingMvaPreselection() {return els_passingMvaPreselection_handle.get();}
const std::vector<bool>& CMS2::els_passingPflowPreselection() {return els_passingPflowPreselection_handle.get();}
const std::vector<bool>& CMS2::mus_isRPCMuon() {return mus_isRPCMuon_handle.get();}
const std::vector<bool>& CMS2::mus_tightMatch() {return mus_tightMatch_handle.get();}
const std::vector<bool>& CMS2::mus_updatedSta() {return mus_updatedSta_handle.get();}
const std::vector<bool>& CMS2::pfcands_isMuIso() {return pfcands_isMuIso_handle.get();}
const std::vector<bool>& CMS2::photons_haspixelSeed() {return photons_haspixelSeed_handle.get();}
const std::vector<double>& CMS2::jets_closestElectron_DR() {return jets_closestElectron_DR_handle.get();}
const std::vector<double>& CMS2::jets_closestMuon_DR() {return jets_closestMuon_DR_handle.get();}
const float& CMS2::evt_bs_Xwidth() {return evt_bs_Xwidth_handle.get();}
const float& CMS2::evt_bs_XwidthErr() {return evt_bs_XwidthErr_handle.get();}
const float& CMS2::evt_bs_Ywidth() {return evt_bs_Ywidth_handle.get();}
const float& CMS2::evt_bs_YwidthErr() {return evt_bs_YwidthErr_handle.get();}
const float& CMS2::evt_bs_dxdz() {return evt_bs_dxdz_handle.get();}
const float& CMS2::evt_bs_dxdzErr() {return evt_bs_dxdzErr_handle.get();}
const float& CMS2::evt_bs_dydz() {return evt_bs_dydz_handle.get();}
const float& CMS2::evt_bs_dydzErr() {return evt_bs_dydzErr_handle.get();}
const float& CMS2::evt_bs_sigmaZ() {return evt_bs_sigmaZ_handle.get();}
const float& CMS2::evt_bs_sigmaZErr() {return evt_bs_sigmaZErr_handle.get();}
const float& CMS2::evt_bs_xErr() {return evt_bs_xErr_handle.get();}
const float& CMS2::evt_bs_yErr() {return evt_bs_yErr_handle.get();}
const float& CMS2::evt_bs_zErr() {return evt_bs_zErr_handle.get();}
const float& CMS2::evt_bField() {return evt_bField_handle.get();}
const float& CMS2::evt_rho() {return evt_rho_handle.get();}
const float& CMS2::evt_rhoJEC() {return evt_rhoJEC_handle.get();}
const float& CMS2::evt_fixgrid_all_rho() {return evt_fixgrid_all_rho_handle.get();}
const float& CMS2::evt_fixgridfastjet_all_rho() {return evt_fixgridfastjet_all_rho_handle.get();}
const float& CMS2::evt_kfactor() {return evt_kfactor_handle.get();}
const float& CMS2::evt_scale1fb() {return evt_scale1fb_handle.get();}
const float& CMS2::evt_xsec_excl() {return evt_xsec_excl_handle.get();}
const float& CMS2::evt_xsec_incl() {return evt_xsec_incl_handle.get();}
const float& CMS2::gen_met() {return gen_met_handle.get();}
const float& CMS2::gen_metPhi() {return gen_metPhi_handle.get();}
const float& CMS2::genps_alphaQCD() {return genps_alphaQCD_handle.get();}
const float& CMS2::genps_pthat() {return genps_pthat_handle.get();}
const float& CMS2::genps_qScale() {return genps_qScale_handle.get();}
const float& CMS2::genps_weight() {return genps_weight_handle.get();}
const float& CMS2::gen_sumEt() {return gen_sumEt_handle.get();}
const float& CMS2::hcalnoise_GetRecHitEnergy() {return hcalnoise_GetRecHitEnergy_handle.get();}
const float& CMS2::hcalnoise_GetRecHitEnergy15() {return hcalnoise_GetRecHitEnergy15_handle.get();}
const float& CMS2::hcalnoise_GetTotalCalibCharge() {return hcalnoise_GetTotalCalibCharge_handle.get();}
const float& CMS2::hcalnoise_TS4TS5NoiseSumE() {return hcalnoise_TS4TS5NoiseSumE_handle.get();}
const float& CMS2::hcalnoise_TS4TS5NoiseSumEt() {return hcalnoise_TS4TS5NoiseSumEt_handle.get();}
const float& CMS2::hcalnoise_eventChargeFraction() {return hcalnoise_eventChargeFraction_handle.get();}
const float& CMS2::hcalnoise_eventEMEnergy() {return hcalnoise_eventEMEnergy_handle.get();}
const float& CMS2::hcalnoise_eventEMFraction() {return hcalnoise_eventEMFraction_handle.get();}
const float& CMS2::hcalnoise_eventHadEnergy() {return hcalnoise_eventHadEnergy_handle.get();}
const float& CMS2::hcalnoise_eventTrackEnergy() {return hcalnoise_eventTrackEnergy_handle.get();}
const float& CMS2::hcalnoise_flatNoiseSumE() {return hcalnoise_flatNoiseSumE_handle.get();}
const float& CMS2::hcalnoise_flatNoiseSumEt() {return hcalnoise_flatNoiseSumEt_handle.get();}
const float& CMS2::hcalnoise_isolatedNoiseSumE() {return hcalnoise_isolatedNoiseSumE_handle.get();}
const float& CMS2::hcalnoise_isolatedNoiseSumEt() {return hcalnoise_isolatedNoiseSumEt_handle.get();}
const float& CMS2::hcalnoise_max10GeVHitTime() {return hcalnoise_max10GeVHitTime_handle.get();}
const float& CMS2::hcalnoise_max25GeVHitTime() {return hcalnoise_max25GeVHitTime_handle.get();}
const float& CMS2::hcalnoise_maxE10TS() {return hcalnoise_maxE10TS_handle.get();}
const float& CMS2::hcalnoise_maxE2Over10TS() {return hcalnoise_maxE2Over10TS_handle.get();}
const float& CMS2::hcalnoise_maxE2TS() {return hcalnoise_maxE2TS_handle.get();}
const float& CMS2::hcalnoise_min10GeVHitTime() {return hcalnoise_min10GeVHitTime_handle.get();}
const float& CMS2::hcalnoise_min25GeVHitTime() {return hcalnoise_min25GeVHitTime_handle.get();}
const float& CMS2::hcalnoise_minE10TS() {return hcalnoise_minE10TS_handle.get();}
const float& CMS2::hcalnoise_minE2Over10TS() {return hcalnoise_minE2Over10TS_handle.get();}
const float& CMS2::hcalnoise_minE2TS() {return hcalnoise_minE2TS_handle.get();}
const float& CMS2::hcalnoise_minHPDEMF() {return hcalnoise_minHPDEMF_handle.get();}
const float& CMS2::hcalnoise_minRBXEMF() {return hcalnoise_minRBXEMF_handle.get();}
const float& CMS2::hcalnoise_rms10GeVHitTime() {return hcalnoise_rms10GeVHitTime_handle.get();}
const float& CMS2::hcalnoise_rms25GeVHitTime() {return hcalnoise_rms25GeVHitTime_handle.get();}
const float& CMS2::hcalnoise_spikeNoiseSumE() {return hcalnoise_spikeNoiseSumE_handle.get();}
const float& CMS2::hcalnoise_spikeNoiseSumEt() {return hcalnoise_spikeNoiseSumEt_handle.get();}
const float& CMS2::hcalnoise_triangleNoiseSumE() {return hcalnoise_triangleNoiseSumE_handle.get();}
const float& CMS2::hcalnoise_triangleNoiseSumEt() {return hcalnoise_triangleNoiseSumEt_handle.get();}
const float& CMS2::evt_kt6calo_central_rho() {return evt_kt6calo_central_rho_handle.get();}
const float& CMS2::evt_kt6calo_muhlt_rho() {return evt_kt6calo_muhlt_rho_handle.get();}
const float& CMS2::evt_kt6calo_rho() {return evt_kt6calo_rho_handle.get();}
const float& CMS2::evt_kt6pf_ctrChargedPU_rho() {return evt_kt6pf_ctrChargedPU_rho_handle.get();}
const float& CMS2::evt_kt6pf_ctrNeutral_rho() {return evt_kt6pf_ctrNeutral_rho_handle.get();}
const float& CMS2::evt_kt6pf_ctrNeutralTight_rho() {return evt_kt6pf_ctrNeutralTight_rho_handle.get();}
const float& CMS2::evt_kt6pf_foregiso_rho() {return evt_kt6pf_foregiso_rho_handle.get();}
const float& CMS2::l1_met_etTot() {return l1_met_etTot_handle.get();}
const float& CMS2::l1_met_met() {return l1_met_met_handle.get();}
const float& CMS2::l1_mht_htTot() {return l1_mht_htTot_handle.get();}
const float& CMS2::l1_mht_mht() {return l1_mht_mht_handle.get();}
const float& CMS2::ls_avgInsDelLumi() {return ls_avgInsDelLumi_handle.get();}
const float& CMS2::ls_avgInsDelLumiErr() {return ls_avgInsDelLumiErr_handle.get();}
const float& CMS2::ls_avgInsRecLumi() {return ls_avgInsRecLumi_handle.get();}
const float& CMS2::ls_avgInsRecLumiErr() {return ls_avgInsRecLumiErr_handle.get();}
const float& CMS2::ls_deadFrac() {return ls_deadFrac_handle.get();}
const float& CMS2::ls_intgDelLumi() {return ls_intgDelLumi_handle.get();}
const float& CMS2::ls_intgRecLumi() {return ls_intgRecLumi_handle.get();}
const float& CMS2::ls_lumiSectionLength() {return ls_lumiSectionLength_handle.get();}
const float& CMS2::evt_ecalendcapm_met() {return evt_ecalendcapm_met_handle.get();}
const float& CMS2::evt_ecalendcapm_metPhi() {return evt_ecalendcapm_metPhi_handle.get();}
const float& CMS2::evt_ecalendcapp_met() {return evt_ecalendcapp_met_handle.get();}
const float& CMS2::evt_ecalendcapp_metPhi() {return evt_ecalendcapp_metPhi_handle.get();}
const float& CMS2::evt_ecalmet() {return evt_ecalmet_handle.get();}
const float& CMS2::evt_ecalmetPhi() {return evt_ecalmetPhi_handle.get();}
const float& CMS2::evt_endcapm_met() {return evt_endcapm_met_handle.get();}
const float& CMS2::evt_endcapm_metPhi() {return evt_endcapm_metPhi_handle.get();}
const float& CMS2::evt_endcapp_met() {return evt_endcapp_met_handle.get();}
const float& CMS2::evt_endcapp_metPhi() {return evt_endcapp_metPhi_handle.get();}
const float& CMS2::evt_hcalendcapm_met() {return evt_hcalendcapm_met_handle.get();}
const float& CMS2::evt_hcalendcapm_metPhi() {return evt_hcalendcapm_metPhi_handle.get();}
const float& CMS2::evt_hcalendcapp_met() {return evt_hcalendcapp_met_handle.get();}
const float& CMS2::evt_hcalendcapp_metPhi() {return evt_hcalendcapp_metPhi_handle.get();}
const float& CMS2::evt_hcalmet() {return evt_hcalmet_handle.get();}
const float& CMS2::evt_hcalmetPhi() {return evt_hcalmetPhi_handle.get();}
const float& CMS2::evt_met() {return evt_met_handle.get();}
const float& CMS2::evt_met_EtGt3() {return evt_met_EtGt3_handle.get();}
const float& CMS2::evt_metHO() {return evt_metHO_handle.get();}
const float& CMS2::evt_metHOPhi() {return evt_metHOPhi_handle.get();}
const float& CMS2::evt_metHOSig() {return evt_metHOSig_handle.get();}
const float& CMS2::evt_metMuonCorr() {return evt_metMuonCorr_handle.get();}
const float& CMS2::evt_metMuonCorrPhi() {return evt_metMuonCorrPhi_handle.get();}
const float& CMS2::evt_metMuonCorrSig() {return evt_metMuonCorrSig_handle.get();}
const float& CMS2::evt_metMuonJESCorr() {return evt_metMuonJESCorr_handle.get();}
const float& CMS2::evt_metMuonJESCorrPhi() {return evt_metMuonJESCorrPhi_handle.get();}
const float& CMS2::evt_metMuonJESCorrSig() {return evt_metMuonJESCorrSig_handle.get();}
const float& CMS2::evt_metNoHF() {return evt_metNoHF_handle.get();}
const float& CMS2::evt_metNoHFHO() {return evt_metNoHFHO_handle.get();}
const float& CMS2::evt_metNoHFHOPhi() {return evt_metNoHFHOPhi_handle.get();}
const float& CMS2::evt_metNoHFHOSig() {return evt_metNoHFHOSig_handle.get();}
const float& CMS2::evt_metNoHFPhi() {return evt_metNoHFPhi_handle.get();}
const float& CMS2::evt_metNoHFSig() {return evt_metNoHFSig_handle.get();}
const float& CMS2::evt_metOpt() {return evt_metOpt_handle.get();}
const float& CMS2::evt_metOptHO() {return evt_metOptHO_handle.get();}
const float& CMS2::evt_metOptHOPhi() {return evt_metOptHOPhi_handle.get();}
const float& CMS2::evt_metOptHOSig() {return evt_metOptHOSig_handle.get();}
const float& CMS2::evt_metOptNoHF() {return evt_metOptNoHF_handle.get();}
const float& CMS2::evt_metOptNoHFHO() {return evt_metOptNoHFHO_handle.get();}
const float& CMS2::evt_metOptNoHFHOPhi() {return evt_metOptNoHFHOPhi_handle.get();}
const float& CMS2::evt_metOptNoHFHOSig() {return evt_metOptNoHFHOSig_handle.get();}
const float& CMS2::evt_metOptNoHFPhi() {return evt_metOptNoHFPhi_handle.get();}
const float& CMS2::evt_metOptNoHFSig() {return evt_metOptNoHFSig_handle.get();}
const float& CMS2::evt_metOptPhi() {return evt_metOptPhi_handle.get();}
const float& CMS2::evt_metOptSig() {return evt_metOptSig_handle.get();}
const float& CMS2::evt_metPhi() {return evt_metPhi_handle.get();}
const float& CMS2::evt_metPhi_EtGt3() {return evt_metPhi_EtGt3_handle.get();}
const float& CMS2::evt_metSig() {return evt_metSig_handle.get();}
const float& CMS2::evt_sumet() {return evt_sumet_handle.get();}
const float& CMS2::evt_sumet_EtGt3() {return evt_sumet_EtGt3_handle.get();}
const float& CMS2::evt_sumetHO() {return evt_sumetHO_handle.get();}
const float& CMS2::evt_sumetMuonCorr() {return evt_sumetMuonCorr_handle.get();}
const float& CMS2::evt_sumetMuonJESCorr() {return evt_sumetMuonJESCorr_handle.get();}
const float& CMS2::evt_sumetNoHF() {return evt_sumetNoHF_handle.get();}
const float& CMS2::evt_sumetNoHFHO() {return evt_sumetNoHFHO_handle.get();}
const float& CMS2::evt_sumetOpt() {return evt_sumetOpt_handle.get();}
const float& CMS2::evt_sumetOptHO() {return evt_sumetOptHO_handle.get();}
const float& CMS2::evt_sumetOptNoHF() {return evt_sumetOptNoHF_handle.get();}
const float& CMS2::evt_sumetOptNoHFHO() {return evt_sumetOptNoHFHO_handle.get();}
const float& CMS2::pdfinfo_pdf1() {return pdfinfo_pdf1_handle.get();}
const float& CMS2::pdfinfo_pdf2() {return pdfinfo_pdf2_handle.get();}
const float& CMS2::pdfinfo_scale() {return pdfinfo_scale_handle.get();}
const float& CMS2::pdfinfo_x1() {return pdfinfo_x1_handle.get();}
const float& CMS2::pdfinfo_x2() {return pdfinfo_x2_handle.get();}
const float& CMS2::evt_fixgrid_rho_all() {return evt_fixgrid_rho_all_handle.get();}
const float& CMS2::evt_fixgrid_rho_ctr() {return evt_fixgrid_rho_ctr_handle.get();}
const float& CMS2::evt_fixgrid_rho_fwd() {return evt_fixgrid_rho_fwd_handle.get();}
const float& CMS2::evt_pfmet() {return evt_pfmet_handle.get();}
const float& CMS2::evt_pfmetPhi() {return evt_pfmetPhi_handle.get();}
const float& CMS2::evt_pfmetPhi_type1cor() {return evt_pfmetPhi_type1cor_handle.get();}
const float& CMS2::evt_pfmetSig() {return evt_pfmetSig_handle.get();}
const float& CMS2::evt_pfmetSignificance() {return evt_pfmetSignificance_handle.get();}
const float& CMS2::evt_pfmet_type1cor() {return evt_pfmet_type1cor_handle.get();}
const float& CMS2::evt_pfsumet() {return evt_pfsumet_handle.get();}
const float& CMS2::sparm_filterEfficiency() {return sparm_filterEfficiency_handle.get();}
const float& CMS2::sparm_pdfScale() {return sparm_pdfScale_handle.get();}
const float& CMS2::sparm_pdfWeight1() {return sparm_pdfWeight1_handle.get();}
const float& CMS2::sparm_pdfWeight2() {return sparm_pdfWeight2_handle.get();}
const float& CMS2::sparm_weight() {return sparm_weight_handle.get();}
const float& CMS2::sparm_xsec() {return sparm_xsec_handle.get();}
const float& CMS2::evt_pf_tcmet() {return evt_pf_tcmet_handle.get();}
const float& CMS2::evt_pf_tcmetPhi() {return evt_pf_tcmetPhi_handle.get();}
const float& CMS2::evt_pf_tcmetSig() {return evt_pf_tcmetSig_handle.get();}
const float& CMS2::evt_pf_tcsumet() {return evt_pf_tcsumet_handle.get();}
const float& CMS2::evt_tcmet() {return evt_tcmet_handle.get();}
const float& CMS2::evt_tcmetPhi() {return evt_tcmetPhi_handle.get();}
const float& CMS2::evt_tcmetSig() {return evt_tcmetSig_handle.get();}
const float& CMS2::evt_tcsumet() {return evt_tcsumet_handle.get();}
const float& CMS2::evt_ww_rho_act() {return evt_ww_rho_act_handle.get();}
const float& CMS2::evt_ww_rho() {return evt_ww_rho_handle.get();}
const float& CMS2::evt_ww_rho_rnd() {return evt_ww_rho_rnd_handle.get();}
const float& CMS2::evt_ww_rho_vor() {return evt_ww_rho_vor_handle.get();}
const LorentzVector & CMS2::evt_bsp4() {return evt_bsp4_handle.get();}
const LorentzVector & CMS2::l1_met_p4() {return l1_met_p4_handle.get();}
const LorentzVector & CMS2::l1_mht_p4() {return l1_mht_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::els_mc_motherp4() {return els_mc_motherp4_handle.get();}
const std::vector<LorentzVector >& CMS2::els_mc_p4() {return els_mc_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::jets_mc_gp_p4() {return jets_mc_gp_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::jets_mc_motherp4() {return jets_mc_motherp4_handle.get();}
const std::vector<LorentzVector >& CMS2::jets_mc_p4() {return jets_mc_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_mc_motherp4() {return mus_mc_motherp4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_mc_p4() {return mus_mc_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::pfjets_mc_gp_p4() {return pfjets_mc_gp_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::pfjets_mc_motherp4() {return pfjets_mc_motherp4_handle.get();}
const std::vector<LorentzVector >& CMS2::pfjets_mc_p4() {return pfjets_mc_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::photons_mc_motherp4() {return photons_mc_motherp4_handle.get();}
const std::vector<LorentzVector >& CMS2::photons_mc_p4() {return photons_mc_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::trk_mcp4() {return trk_mcp4_handle.get();}
const std::vector<LorentzVector >& CMS2::els_conv_pos_p4() {return els_conv_pos_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::els_inner_position() {return els_inner_position_handle.get();}
const std::vector<LorentzVector >& CMS2::els_outer_position() {return els_outer_position_handle.get();}
const std::vector<LorentzVector >& CMS2::els_p4() {return els_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::els_p4In() {return els_p4In_handle.get();}
const std::vector<LorentzVector >& CMS2::els_p4Out() {return els_p4Out_handle.get();}
const std::vector<LorentzVector >& CMS2::els_trk_p4() {return els_trk_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::els_vertex_p4() {return els_vertex_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::genjets_p4() {return genjets_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::genps_p4() {return genps_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::genps_prod_vtx() {return genps_prod_vtx_handle.get();}
const std::vector<LorentzVector >& CMS2::gsftrks_inner_position() {return gsftrks_inner_position_handle.get();}
const std::vector<LorentzVector >& CMS2::gsftrks_outer_p4() {return gsftrks_outer_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::gsftrks_outer_position() {return gsftrks_outer_position_handle.get();}
const std::vector<LorentzVector >& CMS2::gsftrks_p4() {return gsftrks_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::gsftrks_vertex_p4() {return gsftrks_vertex_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::hyp_ll_p4() {return hyp_ll_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::hyp_ll_trk_p4() {return hyp_ll_trk_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::hyp_lt_p4() {return hyp_lt_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::hyp_lt_trk_p4() {return hyp_lt_trk_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::hyp_p4() {return hyp_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::hyp_FVFit_p4() {return hyp_FVFit_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::hyp_FVFit_v4() {return hyp_FVFit_v4_handle.get();}
const std::vector<LorentzVector >& CMS2::hyp_ll_mc_p4() {return hyp_ll_mc_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::hyp_lt_mc_p4() {return hyp_lt_mc_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::jets_p4() {return jets_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::jets_vertex_p4() {return jets_vertex_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::l1_emiso_p4() {return l1_emiso_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::l1_emnoiso_p4() {return l1_emnoiso_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::l1_jetsc_p4() {return l1_jetsc_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::l1_jetsf_p4() {return l1_jetsf_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::l1_jetst_p4() {return l1_jetst_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::l1_mus_p4() {return l1_mus_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_ecalpos_p4() {return mus_ecalpos_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_fitpicky_p4() {return mus_fitpicky_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_fittev_p4() {return mus_fittev_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_fittpfms_p4() {return mus_fittpfms_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_gfit_outerPos_p4() {return mus_gfit_outerPos_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_gfit_p4() {return mus_gfit_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_gfit_vertex_p4() {return mus_gfit_vertex_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_p4() {return mus_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_pfp4() {return mus_pfp4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_pfposAtEcal_p4() {return mus_pfposAtEcal_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_sta_p4() {return mus_sta_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_sta_vertex_p4() {return mus_sta_vertex_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_trk_p4() {return mus_trk_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_vertex_p4() {return mus_vertex_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::pfcands_p4() {return pfcands_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::pfcands_posAtEcal_p4() {return pfcands_posAtEcal_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::pfels_p4() {return pfels_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::pfels_posAtEcal_p4() {return pfels_posAtEcal_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::pfjets_p4() {return pfjets_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::pfmus_p4() {return pfmus_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::pfmus_posAtEcal_p4() {return pfmus_posAtEcal_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::taus_pf_p4() {return taus_pf_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::photons_p4() {return photons_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::convs_refitPairMom_p4() {return convs_refitPairMom_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::convs_vtxpos() {return convs_vtxpos_handle.get();}
const std::vector<LorentzVector >& CMS2::scs_p4() {return scs_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::scs_pos_p4() {return scs_pos_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::scs_vtx_p4() {return scs_vtx_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::svs_flight() {return svs_flight_handle.get();}
const std::vector<LorentzVector >& CMS2::svs_mc3_p4() {return svs_mc3_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::svs_p4() {return svs_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::svs_position() {return svs_position_handle.get();}
const std::vector<LorentzVector >& CMS2::svs_refitp4() {return svs_refitp4_handle.get();}
const std::vector<LorentzVector >& CMS2::trks_inner_position() {return trks_inner_position_handle.get();}
const std::vector<LorentzVector >& CMS2::trks_outer_p4() {return trks_outer_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::trks_outer_position() {return trks_outer_position_handle.get();}
const std::vector<LorentzVector >& CMS2::trks_trk_p4() {return trks_trk_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::trks_vertex_p4() {return trks_vertex_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::trkjets_p4() {return trkjets_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::vtxs_position() {return vtxs_position_handle.get();}
const std::vector<LorentzVector >& CMS2::bsvtxs_position() {return bsvtxs_position_handle.get();}
const std::vector<std::vector<LorentzVector > >& CMS2::els_convs_pos_p4() {return els_convs_pos_p4_handle.get();}
const std::vector<std::vector<LorentzVector > >& CMS2::genps_lepdaughter_p4() {return genps_lepdaughter_p4_handle.get();}
const std::vector<std::vector<LorentzVector > >& CMS2::hlt_trigObjs_p4() {return hlt_trigObjs_p4_handle.get();}
const std::vector<std::vector<LorentzVector > >& CMS2::hyp_jets_p4() {return hyp_jets_p4_handle.get();}
const std::vector<std::vector<LorentzVector > >& CMS2::hyp_other_jets_p4() {return hyp_other_jets_p4_handle.get();}
const std::vector<float>& CMS2::jpts_combinedSecondaryVertexBJetTag() {return jpts_combinedSecondaryVertexBJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_combinedSecondaryVertexMVABJetTag() {return jpts_combinedSecondaryVertexMVABJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_jetBProbabilityBJetTag() {return jpts_jetBProbabilityBJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_jetProbabilityBJetTag() {return jpts_jetProbabilityBJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_simpleSecondaryVertexBJetTag() {return jpts_simpleSecondaryVertexBJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_simpleSecondaryVertexHighEffBJetTag() {return jpts_simpleSecondaryVertexHighEffBJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_simpleSecondaryVertexHighPurBJetTags() {return jpts_simpleSecondaryVertexHighPurBJetTags_handle.get();}
const std::vector<float>& CMS2::jpts_softElectronByIP3dBJetTag() {return jpts_softElectronByIP3dBJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_softElectronByPtBJetTag() {return jpts_softElectronByPtBJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_softElectronTag() {return jpts_softElectronTag_handle.get();}
const std::vector<float>& CMS2::jpts_softMuonBJetTag() {return jpts_softMuonBJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_softMuonByIP3dBJetTag() {return jpts_softMuonByIP3dBJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_softMuonByPtBJetTag() {return jpts_softMuonByPtBJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_trackCountingHighEffBJetTag() {return jpts_trackCountingHighEffBJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_trackCountingHighPurBJetTag() {return jpts_trackCountingHighPurBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_combinedSecondaryVertexBJetTag() {return jets_combinedSecondaryVertexBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_combinedSecondaryVertexMVABJetTag() {return jets_combinedSecondaryVertexMVABJetTag_handle.get();}
const std::vector<float>& CMS2::jets_jetBProbabilityBJetTag() {return jets_jetBProbabilityBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_jetProbabilityBJetTag() {return jets_jetProbabilityBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_simpleSecondaryVertexBJetTag() {return jets_simpleSecondaryVertexBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_simpleSecondaryVertexHighEffBJetTag() {return jets_simpleSecondaryVertexHighEffBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_simpleSecondaryVertexHighPurBJetTags() {return jets_simpleSecondaryVertexHighPurBJetTags_handle.get();}
const std::vector<float>& CMS2::jets_softElectronByIP3dBJetTag() {return jets_softElectronByIP3dBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_softElectronByPtBJetTag() {return jets_softElectronByPtBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_softElectronTag() {return jets_softElectronTag_handle.get();}
const std::vector<float>& CMS2::jets_softMuonBJetTag() {return jets_softMuonBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_softMuonByIP3dBJetTag() {return jets_softMuonByIP3dBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_softMuonByPtBJetTag() {return jets_softMuonByPtBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_trackCountingHighEffBJetTag() {return jets_trackCountingHighEffBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_trackCountingHighPurBJetTag() {return jets_trackCountingHighPurBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_combinedSecondaryVertexBJetTag() {return pfjets_combinedSecondaryVertexBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_combinedSecondaryVertexMVABJetTag() {return pfjets_combinedSecondaryVertexMVABJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_jetBProbabilityBJetTag() {return pfjets_jetBProbabilityBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_jetProbabilityBJetTag() {return pfjets_jetProbabilityBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_simpleSecondaryVertexBJetTag() {return pfjets_simpleSecondaryVertexBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_simpleSecondaryVertexHighEffBJetTag() {return pfjets_simpleSecondaryVertexHighEffBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_simpleSecondaryVertexHighPurBJetTags() {return pfjets_simpleSecondaryVertexHighPurBJetTags_handle.get();}
const std::vector<float>& CMS2::pfjets_softElectronByIP3dBJetTag() {return pfjets_softElectronByIP3dBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_softElectronByPtBJetTag() {return pfjets_softElectronByPtBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_softElectronTag() {return pfjets_softElectronTag_handle.get();}
const std::vector<float>& CMS2::pfjets_softMuonBJetTag() {return pfjets_softMuonBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_softMuonByIP3dBJetTag() {return pfjets_softMuonByIP3dBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_softMuonByPtBJetTag() {return pfjets_softMuonByPtBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_trackCountingHighEffBJetTag() {return pfjets_trackCountingHighEffBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_trackCountingHighPurBJetTag() {return pfjets_trackCountingHighPurBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_combinedSecondaryVertexBJetTag() {return trkjets_combinedSecondaryVertexBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_combinedSecondaryVertexMVABJetTag() {return trkjets_combinedSecondaryVertexMVABJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_jetBProbabilityBJetTag() {return trkjets_jetBProbabilityBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_jetProbabilityBJetTag() {return trkjets_jetProbabilityBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_simpleSecondaryVertexBJetTag() {return trkjets_simpleSecondaryVertexBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_simpleSecondaryVertexHighEffBJetTag() {return trkjets_simpleSecondaryVertexHighEffBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_simpleSecondaryVertexHighPurBJetTags() {return trkjets_simpleSecondaryVertexHighPurBJetTags_handle.get();}
const std::vector<float>& CMS2::trkjets_softElectronByIP3dBJetTag() {return trkjets_softElectronByIP3dBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_softElectronByPtBJetTag() {return trkjets_softElectronByPtBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_softElectronTag() {return trkjets_softElectronTag_handle.get();}
const std::vector<float>& CMS2::trkjets_softMuonBJetTag() {return trkjets_softMuonBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_softMuonByIP3dBJetTag() {return trkjets_softMuonByIP3dBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_softMuonByPtBJetTag() {return trkjets_softMuonByPtBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_trackCountingHighEffBJetTag() {return trkjets_trackCountingHighEffBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_trackCountingHighPurBJetTag() {return trkjets_trackCountingHighPurBJetTag_handle.get();}
const std::vector<float>& CMS2::evt_bs_covMatrix() {return evt_bs_covMatrix_handle.get();}
const std::vector<float>& CMS2::els_mc3dr() {return els_mc3dr_handle.get();}
const std::vector<float>& CMS2::els_mcdr() {return els_mcdr_handle.get();}
const std::vector<float>& CMS2::jets_mc3dr() {return jets_mc3dr_handle.get();}
const std::vector<float>& CMS2::jets_mcdr() {return jets_mcdr_handle.get();}
const std::vector<float>& CMS2::jets_mc_emEnergy() {return jets_mc_emEnergy_handle.get();}
const std::vector<float>& CMS2::jets_mc_gpdr() {return jets_mc_gpdr_handle.get();}
const std::vector<float>& CMS2::jets_mc_hadEnergy() {return jets_mc_hadEnergy_handle.get();}
const std::vector<float>& CMS2::jets_mc_invEnergy() {return jets_mc_invEnergy_handle.get();}
const std::vector<float>& CMS2::jets_mc_otherEnergy() {return jets_mc_otherEnergy_handle.get();}
const std::vector<float>& CMS2::mus_mc3dr() {return mus_mc3dr_handle.get();}
const std::vector<float>& CMS2::mus_mcdr() {return mus_mcdr_handle.get();}
const std::vector<float>& CMS2::pfjets_mc3dr() {return pfjets_mc3dr_handle.get();}
const std::vector<float>& CMS2::pfjets_mcdr() {return pfjets_mcdr_handle.get();}
const std::vector<float>& CMS2::pfjets_mc_emEnergy() {return pfjets_mc_emEnergy_handle.get();}
const std::vector<float>& CMS2::pfjets_mc_gpdr() {return pfjets_mc_gpdr_handle.get();}
const std::vector<float>& CMS2::pfjets_mc_hadEnergy() {return pfjets_mc_hadEnergy_handle.get();}
const std::vector<float>& CMS2::pfjets_mc_invEnergy() {return pfjets_mc_invEnergy_handle.get();}
const std::vector<float>& CMS2::pfjets_mc_otherEnergy() {return pfjets_mc_otherEnergy_handle.get();}
const std::vector<float>& CMS2::photons_mc3dr() {return photons_mc3dr_handle.get();}
const std::vector<float>& CMS2::photons_mcdr() {return photons_mcdr_handle.get();}
const std::vector<float>& CMS2::trk_mc3dr() {return trk_mc3dr_handle.get();}
const std::vector<float>& CMS2::trk_mcdr() {return trk_mcdr_handle.get();}
const std::vector<float>& CMS2::els_ecalJuraIso() {return els_ecalJuraIso_handle.get();}
const std::vector<float>& CMS2::els_ecalJuraTowerIso() {return els_ecalJuraTowerIso_handle.get();}
const std::vector<float>& CMS2::els_hcalConeIso() {return els_hcalConeIso_handle.get();}
const std::vector<float>& CMS2::els_tkJuraIso() {return els_tkJuraIso_handle.get();}
const std::vector<float>& CMS2::els_jetdr() {return els_jetdr_handle.get();}
const std::vector<float>& CMS2::els_musdr() {return els_musdr_handle.get();}
const std::vector<float>& CMS2::els_isoR03_chpf_radial() {return els_isoR03_chpf_radial_handle.get();}
const std::vector<float>& CMS2::els_isoR03_chpf_radialTight() {return els_isoR03_chpf_radialTight_handle.get();}
const std::vector<float>& CMS2::els_isoR03_chpf_radialTight_bv() {return els_isoR03_chpf_radialTight_bv_handle.get();}
const std::vector<float>& CMS2::els_isoR03_chpf_radial_bv() {return els_isoR03_chpf_radial_bv_handle.get();}
const std::vector<float>& CMS2::els_isoR03_empf_radial() {return els_isoR03_empf_radial_handle.get();}
const std::vector<float>& CMS2::els_isoR03_empf_radialTight() {return els_isoR03_empf_radialTight_handle.get();}
const std::vector<float>& CMS2::els_isoR03_empf_radialTight_bv() {return els_isoR03_empf_radialTight_bv_handle.get();}
const std::vector<float>& CMS2::els_isoR03_empf_radial_bv() {return els_isoR03_empf_radial_bv_handle.get();}
const std::vector<float>& CMS2::els_isoR03_nhpf_radial() {return els_isoR03_nhpf_radial_handle.get();}
const std::vector<float>& CMS2::els_isoR03_nhpf_radialTight() {return els_isoR03_nhpf_radialTight_handle.get();}
const std::vector<float>& CMS2::els_isoR03_nhpf_radialTight_bv() {return els_isoR03_nhpf_radialTight_bv_handle.get();}
const std::vector<float>& CMS2::els_isoR03_nhpf_radial_bv() {return els_isoR03_nhpf_radial_bv_handle.get();}
const std::vector<float>& CMS2::els_isoR03_pf2012n0p5_ch() {return els_isoR03_pf2012n0p5_ch_handle.get();}
const std::vector<float>& CMS2::els_isoR03_pf2012n0p5_em() {return els_isoR03_pf2012n0p5_em_handle.get();}
const std::vector<float>& CMS2::els_isoR03_pf2012n0p5_nh() {return els_isoR03_pf2012n0p5_nh_handle.get();}
const std::vector<float>& CMS2::els_isoR03_pf_radial() {return els_isoR03_pf_radial_handle.get();}
const std::vector<float>& CMS2::els_isoR03_pf_radialTight() {return els_isoR03_pf_radialTight_handle.get();}
const std::vector<float>& CMS2::els_isoR03_pf_radialTight_bv() {return els_isoR03_pf_radialTight_bv_handle.get();}
const std::vector<float>& CMS2::els_isoR03_pf_radial_bv() {return els_isoR03_pf_radial_bv_handle.get();}
const std::vector<float>& CMS2::els_chi2() {return els_chi2_handle.get();}
const std::vector<float>& CMS2::els_ckf_chi2() {return els_ckf_chi2_handle.get();}
const std::vector<float>& CMS2::els_ckf_ndof() {return els_ckf_ndof_handle.get();}
const std::vector<float>& CMS2::els_conv_dcot() {return els_conv_dcot_handle.get();}
const std::vector<float>& CMS2::els_conv_dist() {return els_conv_dist_handle.get();}
const std::vector<float>& CMS2::els_conv_old_dcot() {return els_conv_old_dcot_handle.get();}
const std::vector<float>& CMS2::els_conv_old_dist() {return els_conv_old_dist_handle.get();}
const std::vector<float>& CMS2::els_conv_old_radius() {return els_conv_old_radius_handle.get();}
const std::vector<float>& CMS2::els_conv_radius() {return els_conv_radius_handle.get();}
const std::vector<float>& CMS2::els_d0() {return els_d0_handle.get();}
const std::vector<float>& CMS2::els_d0Err() {return els_d0Err_handle.get();}
const std::vector<float>& CMS2::els_d0corr() {return els_d0corr_handle.get();}
const std::vector<float>& CMS2::els_dEtaIn() {return els_dEtaIn_handle.get();}
const std::vector<float>& CMS2::els_dEtaOut() {return els_dEtaOut_handle.get();}
const std::vector<float>& CMS2::els_dPhiIn() {return els_dPhiIn_handle.get();}
const std::vector<float>& CMS2::els_dPhiInPhiOut() {return els_dPhiInPhiOut_handle.get();}
const std::vector<float>& CMS2::els_dPhiOut() {return els_dPhiOut_handle.get();}
const std::vector<float>& CMS2::els_deltaEtaEleClusterTrackAtCalo() {return els_deltaEtaEleClusterTrackAtCalo_handle.get();}
const std::vector<float>& CMS2::els_deltaPhiEleClusterTrackAtCalo() {return els_deltaPhiEleClusterTrackAtCalo_handle.get();}
const std::vector<float>& CMS2::els_e1x5() {return els_e1x5_handle.get();}
const std::vector<float>& CMS2::els_e2x5Max() {return els_e2x5Max_handle.get();}
const std::vector<float>& CMS2::els_e3x3() {return els_e3x3_handle.get();}
const std::vector<float>& CMS2::els_e5x5() {return els_e5x5_handle.get();}
const std::vector<float>& CMS2::els_eMax() {return els_eMax_handle.get();}
const std::vector<float>& CMS2::els_eOverPIn() {return els_eOverPIn_handle.get();}
const std::vector<float>& CMS2::els_eOverPOut() {return els_eOverPOut_handle.get();}
const std::vector<float>& CMS2::els_eSC() {return els_eSC_handle.get();}
const std::vector<float>& CMS2::els_eSCPresh() {return els_eSCPresh_handle.get();}
const std::vector<float>& CMS2::els_eSCRaw() {return els_eSCRaw_handle.get();}
const std::vector<float>& CMS2::els_eSeed() {return els_eSeed_handle.get();}
const std::vector<float>& CMS2::els_eSeedOverPIn() {return els_eSeedOverPIn_handle.get();}
const std::vector<float>& CMS2::els_eSeedOverPOut() {return els_eSeedOverPOut_handle.get();}
const std::vector<float>& CMS2::els_ecalEnergy() {return els_ecalEnergy_handle.get();}
const std::vector<float>& CMS2::els_ecalEnergyError() {return els_ecalEnergyError_handle.get();}
const std::vector<float>& CMS2::els_ecalIso() {return els_ecalIso_handle.get();}
const std::vector<float>& CMS2::els_ecalIso04() {return els_ecalIso04_handle.get();}
const std::vector<float>& CMS2::els_etaErr() {return els_etaErr_handle.get();}
const std::vector<float>& CMS2::els_etaSC() {return els_etaSC_handle.get();}
const std::vector<float>& CMS2::els_etaSCwidth() {return els_etaSCwidth_handle.get();}
const std::vector<float>& CMS2::els_fbrem() {return els_fbrem_handle.get();}
const std::vector<float>& CMS2::els_hOverE() {return els_hOverE_handle.get();}
const std::vector<float>& CMS2::els_hcalDepth1OverEcal() {return els_hcalDepth1OverEcal_handle.get();}
const std::vector<float>& CMS2::els_hcalDepth1TowerSumEt() {return els_hcalDepth1TowerSumEt_handle.get();}
const std::vector<float>& CMS2::els_hcalDepth1TowerSumEt04() {return els_hcalDepth1TowerSumEt04_handle.get();}
const std::vector<float>& CMS2::els_hcalDepth2OverEcal() {return els_hcalDepth2OverEcal_handle.get();}
const std::vector<float>& CMS2::els_hcalDepth2TowerSumEt() {return els_hcalDepth2TowerSumEt_handle.get();}
const std::vector<float>& CMS2::els_hcalDepth2TowerSumEt04() {return els_hcalDepth2TowerSumEt04_handle.get();}
const std::vector<float>& CMS2::els_hcalIso() {return els_hcalIso_handle.get();}
const std::vector<float>& CMS2::els_hcalIso04() {return els_hcalIso04_handle.get();}
const std::vector<float>& CMS2::els_ip3d() {return els_ip3d_handle.get();}
const std::vector<float>& CMS2::els_ip3derr() {return els_ip3derr_handle.get();}
const std::vector<float>& CMS2::els_iso03_pf() {return els_iso03_pf_handle.get();}
const std::vector<float>& CMS2::els_iso03_pf2012_ch() {return els_iso03_pf2012_ch_handle.get();}
const std::vector<float>& CMS2::els_iso03_pf2012_em() {return els_iso03_pf2012_em_handle.get();}
const std::vector<float>& CMS2::els_iso03_pf2012ext_ch() {return els_iso03_pf2012ext_ch_handle.get();}
const std::vector<float>& CMS2::els_iso03_pf2012ext_em() {return els_iso03_pf2012ext_em_handle.get();}
const std::vector<float>& CMS2::els_iso03_pf2012ext_nh() {return els_iso03_pf2012ext_nh_handle.get();}
const std::vector<float>& CMS2::els_iso03_pf2012_nh() {return els_iso03_pf2012_nh_handle.get();}
const std::vector<float>& CMS2::els_iso03_pf_ch() {return els_iso03_pf_ch_handle.get();}
const std::vector<float>& CMS2::els_iso03_pf_gamma05() {return els_iso03_pf_gamma05_handle.get();}
const std::vector<float>& CMS2::els_iso03_pf_nhad05() {return els_iso03_pf_nhad05_handle.get();}
const std::vector<float>& CMS2::els_iso04_pf() {return els_iso04_pf_handle.get();}
const std::vector<float>& CMS2::els_iso04_pf2012_ch() {return els_iso04_pf2012_ch_handle.get();}
const std::vector<float>& CMS2::els_iso04_pf2012_em() {return els_iso04_pf2012_em_handle.get();}
const std::vector<float>& CMS2::els_iso04_pf2012ext_ch() {return els_iso04_pf2012ext_ch_handle.get();}
const std::vector<float>& CMS2::els_iso04_pf2012ext_em() {return els_iso04_pf2012ext_em_handle.get();}
const std::vector<float>& CMS2::els_iso04_pf2012ext_nh() {return els_iso04_pf2012ext_nh_handle.get();}
const std::vector<float>& CMS2::els_iso04_pf2012_nh() {return els_iso04_pf2012_nh_handle.get();}
const std::vector<float>& CMS2::els_iso04_pf_ch() {return els_iso04_pf_ch_handle.get();}
const std::vector<float>& CMS2::els_iso04_pf_gamma05() {return els_iso04_pf_gamma05_handle.get();}
const std::vector<float>& CMS2::els_iso04_pf_nhad05() {return els_iso04_pf_nhad05_handle.get();}
const std::vector<float>& CMS2::els_layer1_charge() {return els_layer1_charge_handle.get();}
const std::vector<float>& CMS2::els_lh() {return els_lh_handle.get();}
const std::vector<float>& CMS2::els_mva() {return els_mva_handle.get();}
const std::vector<float>& CMS2::els_ndof() {return els_ndof_handle.get();}
const std::vector<float>& CMS2::els_pfChargedHadronIso() {return els_pfChargedHadronIso_handle.get();}
const std::vector<float>& CMS2::els_pfNeutralHadronIso() {return els_pfNeutralHadronIso_handle.get();}
const std::vector<float>& CMS2::els_pfPhotonIso() {return els_pfPhotonIso_handle.get();}
const std::vector<float>& CMS2::els_phiErr() {return els_phiErr_handle.get();}
const std::vector<float>& CMS2::els_phiSC() {return els_phiSC_handle.get();}
const std::vector<float>& CMS2::els_phiSCwidth() {return els_phiSCwidth_handle.get();}
const std::vector<float>& CMS2::els_ptErr() {return els_ptErr_handle.get();}
const std::vector<float>& CMS2::els_r9() {return els_r9_handle.get();}
const std::vector<float>& CMS2::els_sigmaEtaEta() {return els_sigmaEtaEta_handle.get();}
const std::vector<float>& CMS2::els_sigmaIEtaIEta() {return els_sigmaIEtaIEta_handle.get();}
const std::vector<float>& CMS2::els_sigmaIEtaIEtaSC() {return els_sigmaIEtaIEtaSC_handle.get();}
const std::vector<float>& CMS2::els_sigmaIEtaIPhi() {return els_sigmaIEtaIPhi_handle.get();}
const std::vector<float>& CMS2::els_sigmaIPhiIPhi() {return els_sigmaIPhiIPhi_handle.get();}
const std::vector<float>& CMS2::els_sigmaIPhiIPhiSC() {return els_sigmaIPhiIPhiSC_handle.get();}
const std::vector<float>& CMS2::els_sigmaIphiIphi() {return els_sigmaIphiIphi_handle.get();}
const std::vector<float>& CMS2::els_sigmaPhiPhi() {return els_sigmaPhiPhi_handle.get();}
const std::vector<float>& CMS2::els_tkIso() {return els_tkIso_handle.get();}
const std::vector<float>& CMS2::els_tkIso04() {return els_tkIso04_handle.get();}
const std::vector<float>& CMS2::els_trackMomentumError() {return els_trackMomentumError_handle.get();}
const std::vector<float>& CMS2::els_trkdr() {return els_trkdr_handle.get();}
const std::vector<float>& CMS2::els_trkshFrac() {return els_trkshFrac_handle.get();}
const std::vector<float>& CMS2::els_z0() {return els_z0_handle.get();}
const std::vector<float>& CMS2::els_z0Err() {return els_z0Err_handle.get();}
const std::vector<float>& CMS2::els_z0corr() {return els_z0corr_handle.get();}
const std::vector<float>& CMS2::gsftrks_chi2() {return gsftrks_chi2_handle.get();}
const std::vector<float>& CMS2::gsftrks_d0() {return gsftrks_d0_handle.get();}
const std::vector<float>& CMS2::gsftrks_d0Err() {return gsftrks_d0Err_handle.get();}
const std::vector<float>& CMS2::gsftrks_d0corr() {return gsftrks_d0corr_handle.get();}
const std::vector<float>& CMS2::gsftrks_d0corrPhi() {return gsftrks_d0corrPhi_handle.get();}
const std::vector<float>& CMS2::gsftrks_d0phiCov() {return gsftrks_d0phiCov_handle.get();}
const std::vector<float>& CMS2::gsftrks_etaErr() {return gsftrks_etaErr_handle.get();}
const std::vector<float>& CMS2::gsftrks_layer1_charge() {return gsftrks_layer1_charge_handle.get();}
const std::vector<float>& CMS2::gsftrks_ndof() {return gsftrks_ndof_handle.get();}
const std::vector<float>& CMS2::gsftrks_phiErr() {return gsftrks_phiErr_handle.get();}
const std::vector<float>& CMS2::gsftrks_ptErr() {return gsftrks_ptErr_handle.get();}
const std::vector<float>& CMS2::gsftrks_z0() {return gsftrks_z0_handle.get();}
const std::vector<float>& CMS2::gsftrks_z0Err() {return gsftrks_z0Err_handle.get();}
const std::vector<float>& CMS2::gsftrks_z0corr() {return gsftrks_z0corr_handle.get();}
const std::vector<float>& CMS2::hyp_Ht() {return hyp_Ht_handle.get();}
const std::vector<float>& CMS2::hyp_dPhi_nJet_metMuonJESCorr() {return hyp_dPhi_nJet_metMuonJESCorr_handle.get();}
const std::vector<float>& CMS2::hyp_dPhi_nJet_muCorrMet() {return hyp_dPhi_nJet_muCorrMet_handle.get();}
const std::vector<float>& CMS2::hyp_dPhi_nJet_tcMet() {return hyp_dPhi_nJet_tcMet_handle.get();}
const std::vector<float>& CMS2::hyp_dPhi_nJet_unCorrMet() {return hyp_dPhi_nJet_unCorrMet_handle.get();}
const std::vector<float>& CMS2::hyp_ll_chi2() {return hyp_ll_chi2_handle.get();}
const std::vector<float>& CMS2::hyp_ll_d0() {return hyp_ll_d0_handle.get();}
const std::vector<float>& CMS2::hyp_ll_d0Err() {return hyp_ll_d0Err_handle.get();}
const std::vector<float>& CMS2::hyp_ll_d0corr() {return hyp_ll_d0corr_handle.get();}
const std::vector<float>& CMS2::hyp_ll_dPhi_metMuonJESCorr() {return hyp_ll_dPhi_metMuonJESCorr_handle.get();}
const std::vector<float>& CMS2::hyp_ll_dPhi_muCorrMet() {return hyp_ll_dPhi_muCorrMet_handle.get();}
const std::vector<float>& CMS2::hyp_ll_dPhi_tcMet() {return hyp_ll_dPhi_tcMet_handle.get();}
const std::vector<float>& CMS2::hyp_ll_dPhi_unCorrMet() {return hyp_ll_dPhi_unCorrMet_handle.get();}
const std::vector<float>& CMS2::hyp_ll_etaErr() {return hyp_ll_etaErr_handle.get();}
const std::vector<float>& CMS2::hyp_ll_ndof() {return hyp_ll_ndof_handle.get();}
const std::vector<float>& CMS2::hyp_ll_phiErr() {return hyp_ll_phiErr_handle.get();}
const std::vector<float>& CMS2::hyp_ll_ptErr() {return hyp_ll_ptErr_handle.get();}
const std::vector<float>& CMS2::hyp_ll_z0() {return hyp_ll_z0_handle.get();}
const std::vector<float>& CMS2::hyp_ll_z0Err() {return hyp_ll_z0Err_handle.get();}
const std::vector<float>& CMS2::hyp_ll_z0corr() {return hyp_ll_z0corr_handle.get();}
const std::vector<float>& CMS2::hyp_lt_chi2() {return hyp_lt_chi2_handle.get();}
const std::vector<float>& CMS2::hyp_lt_d0() {return hyp_lt_d0_handle.get();}
const std::vector<float>& CMS2::hyp_lt_d0Err() {return hyp_lt_d0Err_handle.get();}
const std::vector<float>& CMS2::hyp_lt_d0corr() {return hyp_lt_d0corr_handle.get();}
const std::vector<float>& CMS2::hyp_lt_dPhi_metMuonJESCorr() {return hyp_lt_dPhi_metMuonJESCorr_handle.get();}
const std::vector<float>& CMS2::hyp_lt_dPhi_muCorrMet() {return hyp_lt_dPhi_muCorrMet_handle.get();}
const std::vector<float>& CMS2::hyp_lt_dPhi_tcMet() {return hyp_lt_dPhi_tcMet_handle.get();}
const std::vector<float>& CMS2::hyp_lt_dPhi_unCorrMet() {return hyp_lt_dPhi_unCorrMet_handle.get();}
const std::vector<float>& CMS2::hyp_lt_etaErr() {return hyp_lt_etaErr_handle.get();}
const std::vector<float>& CMS2::hyp_lt_ndof() {return hyp_lt_ndof_handle.get();}
const std::vector<float>& CMS2::hyp_lt_phiErr() {return hyp_lt_phiErr_handle.get();}
const std::vector<float>& CMS2::hyp_lt_ptErr() {return hyp_lt_ptErr_handle.get();}
const std::vector<float>& CMS2::hyp_lt_z0() {return hyp_lt_z0_handle.get();}
const std::vector<float>& CMS2::hyp_lt_z0Err() {return hyp_lt_z0Err_handle.get();}
const std::vector<float>& CMS2::hyp_lt_z0corr() {return hyp_lt_z0corr_handle.get();}
const std::vector<float>& CMS2::hyp_mt2_metMuonJESCorr() {return hyp_mt2_metMuonJESCorr_handle.get();}
const std::vector<float>& CMS2::hyp_mt2_muCorrMet() {return hyp_mt2_muCorrMet_handle.get();}
const std::vector<float>& CMS2::hyp_mt2_tcMet() {return hyp_mt2_tcMet_handle.get();}
const std::vector<float>& CMS2::hyp_sumJetPt() {return hyp_sumJetPt_handle.get();}
const std::vector<float>& CMS2::hyp_FVFit_chi2ndf() {return hyp_FVFit_chi2ndf_handle.get();}
const std::vector<float>& CMS2::hyp_FVFit_prob() {return hyp_FVFit_prob_handle.get();}
const std::vector<float>& CMS2::hyp_FVFit_v4cxx() {return hyp_FVFit_v4cxx_handle.get();}
const std::vector<float>& CMS2::hyp_FVFit_v4cxy() {return hyp_FVFit_v4cxy_handle.get();}
const std::vector<float>& CMS2::hyp_FVFit_v4cyy() {return hyp_FVFit_v4cyy_handle.get();}
const std::vector<float>& CMS2::hyp_FVFit_v4czx() {return hyp_FVFit_v4czx_handle.get();}
const std::vector<float>& CMS2::hyp_FVFit_v4czy() {return hyp_FVFit_v4czy_handle.get();}
const std::vector<float>& CMS2::hyp_FVFit_v4czz() {return hyp_FVFit_v4czz_handle.get();}
const std::vector<float>& CMS2::jets_approximatefHPD() {return jets_approximatefHPD_handle.get();}
const std::vector<float>& CMS2::jets_approximatefRBX() {return jets_approximatefRBX_handle.get();}
const std::vector<float>& CMS2::jets_cor() {return jets_cor_handle.get();}
const std::vector<float>& CMS2::jets_corL1FastL2L3() {return jets_corL1FastL2L3_handle.get();}
const std::vector<float>& CMS2::jets_corL1L2L3() {return jets_corL1L2L3_handle.get();}
const std::vector<float>& CMS2::jets_emFrac() {return jets_emFrac_handle.get();}
const std::vector<float>& CMS2::jets_fHPD() {return jets_fHPD_handle.get();}
const std::vector<float>& CMS2::jets_fRBX() {return jets_fRBX_handle.get();}
const std::vector<float>& CMS2::jets_fSubDetector1() {return jets_fSubDetector1_handle.get();}
const std::vector<float>& CMS2::jets_fSubDetector2() {return jets_fSubDetector2_handle.get();}
const std::vector<float>& CMS2::jets_fSubDetector3() {return jets_fSubDetector3_handle.get();}
const std::vector<float>& CMS2::jets_fSubDetector4() {return jets_fSubDetector4_handle.get();}
const std::vector<float>& CMS2::jets_hitsInN90() {return jets_hitsInN90_handle.get();}
const std::vector<float>& CMS2::jets_n90Hits() {return jets_n90Hits_handle.get();}
const std::vector<float>& CMS2::jets_nECALTowers() {return jets_nECALTowers_handle.get();}
const std::vector<float>& CMS2::jets_nHCALTowers() {return jets_nHCALTowers_handle.get();}
const std::vector<float>& CMS2::jets_restrictedEMF() {return jets_restrictedEMF_handle.get();}
const std::vector<float>& CMS2::mus_met_deltax() {return mus_met_deltax_handle.get();}
const std::vector<float>& CMS2::mus_met_deltay() {return mus_met_deltay_handle.get();}
const std::vector<float>& CMS2::mus_eledr() {return mus_eledr_handle.get();}
const std::vector<float>& CMS2::mus_jetdr() {return mus_jetdr_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_chpf_radial() {return mus_isoR03_chpf_radial_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_chpf_radialTight() {return mus_isoR03_chpf_radialTight_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_empf_radial() {return mus_isoR03_empf_radial_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_empf_radialTight() {return mus_isoR03_empf_radialTight_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_nhpf_radial() {return mus_isoR03_nhpf_radial_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_nhpf_radialTight() {return mus_isoR03_nhpf_radialTight_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_pf_radial() {return mus_isoR03_pf_radial_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_pf_radialTight() {return mus_isoR03_pf_radialTight_handle.get();}
const std::vector<float>& CMS2::mus_backToBackCompat() {return mus_backToBackCompat_handle.get();}
const std::vector<float>& CMS2::mus_caloCompatibility() {return mus_caloCompatibility_handle.get();}
const std::vector<float>& CMS2::mus_chi2() {return mus_chi2_handle.get();}
const std::vector<float>& CMS2::mus_chi2LocalMomentum() {return mus_chi2LocalMomentum_handle.get();}
const std::vector<float>& CMS2::mus_chi2LocalPosition() {return mus_chi2LocalPosition_handle.get();}
const std::vector<float>& CMS2::mus_cosmicCompat() {return mus_cosmicCompat_handle.get();}
const std::vector<float>& CMS2::mus_d0() {return mus_d0_handle.get();}
const std::vector<float>& CMS2::mus_d0Err() {return mus_d0Err_handle.get();}
const std::vector<float>& CMS2::mus_d0corr() {return mus_d0corr_handle.get();}
const std::vector<float>& CMS2::mus_e_em() {return mus_e_em_handle.get();}
const std::vector<float>& CMS2::mus_e_emS9() {return mus_e_emS9_handle.get();}
const std::vector<float>& CMS2::mus_e_had() {return mus_e_had_handle.get();}
const std::vector<float>& CMS2::mus_e_hadS9() {return mus_e_hadS9_handle.get();}
const std::vector<float>& CMS2::mus_e_ho() {return mus_e_ho_handle.get();}
const std::vector<float>& CMS2::mus_e_hoS9() {return mus_e_hoS9_handle.get();}
const std::vector<float>& CMS2::mus_etaErr() {return mus_etaErr_handle.get();}
const std::vector<float>& CMS2::mus_gfit_chi2() {return mus_gfit_chi2_handle.get();}
const std::vector<float>& CMS2::mus_gfit_d0() {return mus_gfit_d0_handle.get();}
const std::vector<float>& CMS2::mus_gfit_d0Err() {return mus_gfit_d0Err_handle.get();}
const std::vector<float>& CMS2::mus_gfit_d0corr() {return mus_gfit_d0corr_handle.get();}
const std::vector<float>& CMS2::mus_gfit_ndof() {return mus_gfit_ndof_handle.get();}
const std::vector<float>& CMS2::mus_gfit_qoverp() {return mus_gfit_qoverp_handle.get();}
const std::vector<float>& CMS2::mus_gfit_qoverpError() {return mus_gfit_qoverpError_handle.get();}
const std::vector<float>& CMS2::mus_gfit_z0() {return mus_gfit_z0_handle.get();}
const std::vector<float>& CMS2::mus_gfit_z0Err() {return mus_gfit_z0Err_handle.get();}
const std::vector<float>& CMS2::mus_gfit_z0corr() {return mus_gfit_z0corr_handle.get();}
const std::vector<float>& CMS2::mus_glbKink() {return mus_glbKink_handle.get();}
const std::vector<float>& CMS2::mus_glbTrackProbability() {return mus_glbTrackProbability_handle.get();}
const std::vector<float>& CMS2::mus_globalDeltaEtaPhi() {return mus_globalDeltaEtaPhi_handle.get();}
const std::vector<float>& CMS2::mus_ip3d() {return mus_ip3d_handle.get();}
const std::vector<float>& CMS2::mus_ip3derr() {return mus_ip3derr_handle.get();}
const std::vector<float>& CMS2::mus_iso03_emEt() {return mus_iso03_emEt_handle.get();}
const std::vector<float>& CMS2::mus_iso03_hadEt() {return mus_iso03_hadEt_handle.get();}
const std::vector<float>& CMS2::mus_iso03_hoEt() {return mus_iso03_hoEt_handle.get();}
const std::vector<float>& CMS2::mus_iso03_pf() {return mus_iso03_pf_handle.get();}
const std::vector<float>& CMS2::mus_iso03_sumPt() {return mus_iso03_sumPt_handle.get();}
const std::vector<float>& CMS2::mus_iso04_pf() {return mus_iso04_pf_handle.get();}
const std::vector<float>& CMS2::mus_iso05_emEt() {return mus_iso05_emEt_handle.get();}
const std::vector<float>& CMS2::mus_iso05_hadEt() {return mus_iso05_hadEt_handle.get();}
const std::vector<float>& CMS2::mus_iso05_hoEt() {return mus_iso05_hoEt_handle.get();}
const std::vector<float>& CMS2::mus_iso05_sumPt() {return mus_iso05_sumPt_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_pf_ChargedHadronPt() {return mus_isoR03_pf_ChargedHadronPt_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_pf_ChargedParticlePt() {return mus_isoR03_pf_ChargedParticlePt_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_pf_NeutralHadronEt() {return mus_isoR03_pf_NeutralHadronEt_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_pf_NeutralHadronEtHighThreshold() {return mus_isoR03_pf_NeutralHadronEtHighThreshold_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_pf_PUPt() {return mus_isoR03_pf_PUPt_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_pf_PhotonEt() {return mus_isoR03_pf_PhotonEt_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_pf_PhotonEtHighThreshold() {return mus_isoR03_pf_PhotonEtHighThreshold_handle.get();}
const std::vector<float>& CMS2::mus_isoR04_pf_ChargedHadronPt() {return mus_isoR04_pf_ChargedHadronPt_handle.get();}
const std::vector<float>& CMS2::mus_isoR04_pf_ChargedParticlePt() {return mus_isoR04_pf_ChargedParticlePt_handle.get();}
const std::vector<float>& CMS2::mus_isoR04_pf_NeutralHadronEt() {return mus_isoR04_pf_NeutralHadronEt_handle.get();}
const std::vector<float>& CMS2::mus_isoR04_pf_NeutralHadronEtHighThreshold() {return mus_isoR04_pf_NeutralHadronEtHighThreshold_handle.get();}
const std::vector<float>& CMS2::mus_isoR04_pf_PUPt() {return mus_isoR04_pf_PUPt_handle.get();}
const std::vector<float>& CMS2::mus_isoR04_pf_PhotonEt() {return mus_isoR04_pf_PhotonEt_handle.get();}
const std::vector<float>& CMS2::mus_isoR04_pf_PhotonEtHighThreshold() {return mus_isoR04_pf_PhotonEtHighThreshold_handle.get();}
const std::vector<float>& CMS2::mus_iso_ecalvetoDep() {return mus_iso_ecalvetoDep_handle.get();}
const std::vector<float>& CMS2::mus_iso_hcalvetoDep() {return mus_iso_hcalvetoDep_handle.get();}
const std::vector<float>& CMS2::mus_iso_hovetoDep() {return mus_iso_hovetoDep_handle.get();}
const std::vector<float>& CMS2::mus_iso_trckvetoDep() {return mus_iso_trckvetoDep_handle.get();}
const std::vector<float>& CMS2::mus_localDistance() {return mus_localDistance_handle.get();}
const std::vector<float>& CMS2::mus_ndof() {return mus_ndof_handle.get();}
const std::vector<float>& CMS2::mus_overlapCompat() {return mus_overlapCompat_handle.get();}
const std::vector<float>& CMS2::mus_pfdeltaP() {return mus_pfdeltaP_handle.get();}
const std::vector<float>& CMS2::mus_pfecalE() {return mus_pfecalE_handle.get();}
const std::vector<float>& CMS2::mus_pfhcalE() {return mus_pfhcalE_handle.get();}
const std::vector<float>& CMS2::mus_pfmva_emu() {return mus_pfmva_emu_handle.get();}
const std::vector<float>& CMS2::mus_pfmva_epi() {return mus_pfmva_epi_handle.get();}
const std::vector<float>& CMS2::mus_pfmva_nothing_gamma() {return mus_pfmva_nothing_gamma_handle.get();}
const std::vector<float>& CMS2::mus_pfmva_nothing_nh() {return mus_pfmva_nothing_nh_handle.get();}
const std::vector<float>& CMS2::mus_pfmva_pimu() {return mus_pfmva_pimu_handle.get();}
const std::vector<float>& CMS2::mus_pfpS1E() {return mus_pfpS1E_handle.get();}
const std::vector<float>& CMS2::mus_pfpS2E() {return mus_pfpS2E_handle.get();}
const std::vector<float>& CMS2::mus_pfrawEcalE() {return mus_pfrawEcalE_handle.get();}
const std::vector<float>& CMS2::mus_pfrawHcalE() {return mus_pfrawHcalE_handle.get();}
const std::vector<float>& CMS2::mus_phiErr() {return mus_phiErr_handle.get();}
const std::vector<float>& CMS2::mus_ptErr() {return mus_ptErr_handle.get();}
const std::vector<float>& CMS2::mus_qoverp() {return mus_qoverp_handle.get();}
const std::vector<float>& CMS2::mus_qoverpError() {return mus_qoverpError_handle.get();}
const std::vector<float>& CMS2::mus_segmCompatibility() {return mus_segmCompatibility_handle.get();}
const std::vector<float>& CMS2::mus_staRelChi2() {return mus_staRelChi2_handle.get();}
const std::vector<float>& CMS2::mus_sta_chi2() {return mus_sta_chi2_handle.get();}
const std::vector<float>& CMS2::mus_sta_d0() {return mus_sta_d0_handle.get();}
const std::vector<float>& CMS2::mus_sta_d0Err() {return mus_sta_d0Err_handle.get();}
const std::vector<float>& CMS2::mus_sta_d0corr() {return mus_sta_d0corr_handle.get();}
const std::vector<float>& CMS2::mus_sta_ndof() {return mus_sta_ndof_handle.get();}
const std::vector<float>& CMS2::mus_sta_qoverp() {return mus_sta_qoverp_handle.get();}
const std::vector<float>& CMS2::mus_sta_qoverpError() {return mus_sta_qoverpError_handle.get();}
const std::vector<float>& CMS2::mus_sta_z0() {return mus_sta_z0_handle.get();}
const std::vector<float>& CMS2::mus_sta_z0Err() {return mus_sta_z0Err_handle.get();}
const std::vector<float>& CMS2::mus_sta_z0corr() {return mus_sta_z0corr_handle.get();}
const std::vector<float>& CMS2::mus_timeAtIpInOut() {return mus_timeAtIpInOut_handle.get();}
const std::vector<float>& CMS2::mus_timeAtIpInOutErr() {return mus_timeAtIpInOutErr_handle.get();}
const std::vector<float>& CMS2::mus_timeAtIpOutIn() {return mus_timeAtIpOutIn_handle.get();}
const std::vector<float>& CMS2::mus_timeAtIpOutInErr() {return mus_timeAtIpOutInErr_handle.get();}
const std::vector<float>& CMS2::mus_timeCompat() {return mus_timeCompat_handle.get();}
const std::vector<float>& CMS2::mus_trkKink() {return mus_trkKink_handle.get();}
const std::vector<float>& CMS2::mus_trkRelChi2() {return mus_trkRelChi2_handle.get();}
const std::vector<float>& CMS2::mus_vertexCompat() {return mus_vertexCompat_handle.get();}
const std::vector<float>& CMS2::mus_vertexphi() {return mus_vertexphi_handle.get();}
const std::vector<float>& CMS2::mus_z0() {return mus_z0_handle.get();}
const std::vector<float>& CMS2::mus_z0Err() {return mus_z0Err_handle.get();}
const std::vector<float>& CMS2::mus_z0corr() {return mus_z0corr_handle.get();}
const std::vector<float>& CMS2::pfjets_mvavalue() {return pfjets_mvavalue_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_beta() {return pfjets_full53xmva_beta_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_betaStar() {return pfjets_full53xmva_betaStar_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_d0() {return pfjets_full53xmva_d0_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_dRMean() {return pfjets_full53xmva_dRMean_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_dZ() {return pfjets_full53xmva_dZ_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_frac01() {return pfjets_full53xmva_frac01_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_frac02() {return pfjets_full53xmva_frac02_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_frac03() {return pfjets_full53xmva_frac03_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_frac04() {return pfjets_full53xmva_frac04_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_frac05() {return pfjets_full53xmva_frac05_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_nCharged() {return pfjets_full53xmva_nCharged_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_nNeutrals() {return pfjets_full53xmva_nNeutrals_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_nvtx() {return pfjets_full53xmva_nvtx_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmvavalue() {return pfjets_full53xmvavalue_handle.get();}
const std::vector<float>& CMS2::pfjets_full5xmvavalue() {return pfjets_full5xmvavalue_handle.get();}
const std::vector<float>& CMS2::trkjet_met() {return trkjet_met_handle.get();}
const std::vector<float>& CMS2::trkjet_metPhi() {return trkjet_metPhi_handle.get();}
const std::vector<float>& CMS2::trkjet_sumet() {return trkjet_sumet_handle.get();}
const std::vector<float>& CMS2::trk_met() {return trk_met_handle.get();}
const std::vector<float>& CMS2::trk_metPhi() {return trk_metPhi_handle.get();}
const std::vector<float>& CMS2::trk_sumet() {return trk_sumet_handle.get();}
const std::vector<float>& CMS2::pfcands_deltaP() {return pfcands_deltaP_handle.get();}
const std::vector<float>& CMS2::pfcands_ecalE() {return pfcands_ecalE_handle.get();}
const std::vector<float>& CMS2::pfcands_hcalE() {return pfcands_hcalE_handle.get();}
const std::vector<float>& CMS2::pfcands_mva_emu() {return pfcands_mva_emu_handle.get();}
const std::vector<float>& CMS2::pfcands_mva_epi() {return pfcands_mva_epi_handle.get();}
const std::vector<float>& CMS2::pfcands_mva_nothing_gamma() {return pfcands_mva_nothing_gamma_handle.get();}
const std::vector<float>& CMS2::pfcands_mva_nothing_nh() {return pfcands_mva_nothing_nh_handle.get();}
const std::vector<float>& CMS2::pfcands_mva_pimu() {return pfcands_mva_pimu_handle.get();}
const std::vector<float>& CMS2::pfcands_pS1E() {return pfcands_pS1E_handle.get();}
const std::vector<float>& CMS2::pfcands_pS2E() {return pfcands_pS2E_handle.get();}
const std::vector<float>& CMS2::pfcands_rawEcalE() {return pfcands_rawEcalE_handle.get();}
const std::vector<float>& CMS2::pfcands_rawHcalE() {return pfcands_rawHcalE_handle.get();}
const std::vector<float>& CMS2::pfels_deltaP() {return pfels_deltaP_handle.get();}
const std::vector<float>& CMS2::pfels_ecalE() {return pfels_ecalE_handle.get();}
const std::vector<float>& CMS2::pfels_hcalE() {return pfels_hcalE_handle.get();}
const std::vector<float>& CMS2::pfels_iso04ChargedHadrons() {return pfels_iso04ChargedHadrons_handle.get();}
const std::vector<float>& CMS2::pfels_iso04NeutralHadrons() {return pfels_iso04NeutralHadrons_handle.get();}
const std::vector<float>& CMS2::pfels_iso04Photons() {return pfels_iso04Photons_handle.get();}
const std::vector<float>& CMS2::pfels_isoChargedHadrons() {return pfels_isoChargedHadrons_handle.get();}
const std::vector<float>& CMS2::pfels_isoNeutralHadrons() {return pfels_isoNeutralHadrons_handle.get();}
const std::vector<float>& CMS2::pfels_isoPhotons() {return pfels_isoPhotons_handle.get();}
const std::vector<float>& CMS2::pfels_mva_emu() {return pfels_mva_emu_handle.get();}
const std::vector<float>& CMS2::pfels_mva_epi() {return pfels_mva_epi_handle.get();}
const std::vector<float>& CMS2::pfels_mva_nothing_gamma() {return pfels_mva_nothing_gamma_handle.get();}
const std::vector<float>& CMS2::pfels_mva_nothing_nh() {return pfels_mva_nothing_nh_handle.get();}
const std::vector<float>& CMS2::pfels_mva_pimu() {return pfels_mva_pimu_handle.get();}
const std::vector<float>& CMS2::pfels_pS1E() {return pfels_pS1E_handle.get();}
const std::vector<float>& CMS2::pfels_pS2E() {return pfels_pS2E_handle.get();}
const std::vector<float>& CMS2::pfels_rawEcalE() {return pfels_rawEcalE_handle.get();}
const std::vector<float>& CMS2::pfels_rawHcalE() {return pfels_rawHcalE_handle.get();}
const std::vector<float>& CMS2::pfjets_area() {return pfjets_area_handle.get();}
const std::vector<float>& CMS2::pfjets_chargedEmE() {return pfjets_chargedEmE_handle.get();}
const std::vector<float>& CMS2::pfjets_chargedHadronE() {return pfjets_chargedHadronE_handle.get();}
const std::vector<float>& CMS2::pfjets_cor() {return pfjets_cor_handle.get();}
const std::vector<float>& CMS2::pfjets_corL1Fast() {return pfjets_corL1Fast_handle.get();}
const std::vector<float>& CMS2::pfjets_corL1FastL2L3() {return pfjets_corL1FastL2L3_handle.get();}
const std::vector<float>& CMS2::pfjets_corL1FastL2L3residual() {return pfjets_corL1FastL2L3residual_handle.get();}
const std::vector<float>& CMS2::pfjets_corL1L2L3() {return pfjets_corL1L2L3_handle.get();}
const std::vector<float>& CMS2::pfjets_electronE() {return pfjets_electronE_handle.get();}
const std::vector<float>& CMS2::pfjets_hfEmE() {return pfjets_hfEmE_handle.get();}
const std::vector<float>& CMS2::pfjets_hfHadronE() {return pfjets_hfHadronE_handle.get();}
const std::vector<float>& CMS2::pfjets_muonE() {return pfjets_muonE_handle.get();}
const std::vector<float>& CMS2::pfjets_neutralEmE() {return pfjets_neutralEmE_handle.get();}
const std::vector<float>& CMS2::pfjets_neutralHadronE() {return pfjets_neutralHadronE_handle.get();}
const std::vector<float>& CMS2::pfjets_photonE() {return pfjets_photonE_handle.get();}
const std::vector<float>& CMS2::pfmus_deltaP() {return pfmus_deltaP_handle.get();}
const std::vector<float>& CMS2::pfmus_ecalE() {return pfmus_ecalE_handle.get();}
const std::vector<float>& CMS2::pfmus_hcalE() {return pfmus_hcalE_handle.get();}
const std::vector<float>& CMS2::pfmus_iso04ChargedHadrons() {return pfmus_iso04ChargedHadrons_handle.get();}
const std::vector<float>& CMS2::pfmus_iso04NeutralHadrons() {return pfmus_iso04NeutralHadrons_handle.get();}
const std::vector<float>& CMS2::pfmus_iso04Photons() {return pfmus_iso04Photons_handle.get();}
const std::vector<float>& CMS2::pfmus_isoChargedHadrons() {return pfmus_isoChargedHadrons_handle.get();}
const std::vector<float>& CMS2::pfmus_isoNeutralHadrons() {return pfmus_isoNeutralHadrons_handle.get();}
const std::vector<float>& CMS2::pfmus_isoPhotons() {return pfmus_isoPhotons_handle.get();}
const std::vector<float>& CMS2::pfmus_mva_emu() {return pfmus_mva_emu_handle.get();}
const std::vector<float>& CMS2::pfmus_mva_epi() {return pfmus_mva_epi_handle.get();}
const std::vector<float>& CMS2::pfmus_mva_nothing_gamma() {return pfmus_mva_nothing_gamma_handle.get();}
const std::vector<float>& CMS2::pfmus_mva_nothing_nh() {return pfmus_mva_nothing_nh_handle.get();}
const std::vector<float>& CMS2::pfmus_mva_pimu() {return pfmus_mva_pimu_handle.get();}
const std::vector<float>& CMS2::pfmus_pS1E() {return pfmus_pS1E_handle.get();}
const std::vector<float>& CMS2::pfmus_pS2E() {return pfmus_pS2E_handle.get();}
const std::vector<float>& CMS2::pfmus_rawEcalE() {return pfmus_rawEcalE_handle.get();}
const std::vector<float>& CMS2::pfmus_rawHcalE() {return pfmus_rawHcalE_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronDeadECAL() {return taus_pf_againstElectronDeadECAL_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronLoose() {return taus_pf_againstElectronLoose_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronLooseMVA2() {return taus_pf_againstElectronLooseMVA2_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronLooseMVA3() {return taus_pf_againstElectronLooseMVA3_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronMVA() {return taus_pf_againstElectronMVA_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronMVA2category() {return taus_pf_againstElectronMVA2category_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronMVA2raw() {return taus_pf_againstElectronMVA2raw_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronMVA3category() {return taus_pf_againstElectronMVA3category_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronMVA3raw() {return taus_pf_againstElectronMVA3raw_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronMedium() {return taus_pf_againstElectronMedium_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronMediumMVA2() {return taus_pf_againstElectronMediumMVA2_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronMediumMVA3() {return taus_pf_againstElectronMediumMVA3_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronTight() {return taus_pf_againstElectronTight_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronTightMVA2() {return taus_pf_againstElectronTightMVA2_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronTightMVA3() {return taus_pf_againstElectronTightMVA3_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronVLooseMVA2() {return taus_pf_againstElectronVLooseMVA2_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronVTightMVA3() {return taus_pf_againstElectronVTightMVA3_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstMuonLoose() {return taus_pf_againstMuonLoose_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstMuonLoose2() {return taus_pf_againstMuonLoose2_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstMuonMedium() {return taus_pf_againstMuonMedium_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstMuonMedium2() {return taus_pf_againstMuonMedium2_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstMuonTight() {return taus_pf_againstMuonTight_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstMuonTight2() {return taus_pf_againstMuonTight2_handle.get();}
const std::vector<float>& CMS2::taus_pf_byCombinedIsolationDeltaBetaCorrRaw() {return taus_pf_byCombinedIsolationDeltaBetaCorrRaw_handle.get();}
const std::vector<float>& CMS2::taus_pf_byCombinedIsolationDeltaBetaCorrRaw3Hits() {return taus_pf_byCombinedIsolationDeltaBetaCorrRaw3Hits_handle.get();}
const std::vector<float>& CMS2::taus_pf_byDecayModeFinding() {return taus_pf_byDecayModeFinding_handle.get();}
const std::vector<float>& CMS2::taus_pf_byIsolationMVA2raw() {return taus_pf_byIsolationMVA2raw_handle.get();}
const std::vector<float>& CMS2::taus_pf_byIsolationMVAraw() {return taus_pf_byIsolationMVAraw_handle.get();}
const std::vector<float>& CMS2::taus_pf_byLooseCombinedIsolationDeltaBetaCorr() {return taus_pf_byLooseCombinedIsolationDeltaBetaCorr_handle.get();}
const std::vector<float>& CMS2::taus_pf_byLooseCombinedIsolationDeltaBetaCorr3Hits() {return taus_pf_byLooseCombinedIsolationDeltaBetaCorr3Hits_handle.get();}
const std::vector<float>& CMS2::taus_pf_byLooseIsolationMVA() {return taus_pf_byLooseIsolationMVA_handle.get();}
const std::vector<float>& CMS2::taus_pf_byLooseIsolationMVA2() {return taus_pf_byLooseIsolationMVA2_handle.get();}
const std::vector<float>& CMS2::taus_pf_byMediumCombinedIsolationDeltaBetaCorr() {return taus_pf_byMediumCombinedIsolationDeltaBetaCorr_handle.get();}
const std::vector<float>& CMS2::taus_pf_byMediumCombinedIsolationDeltaBetaCorr3Hits() {return taus_pf_byMediumCombinedIsolationDeltaBetaCorr3Hits_handle.get();}
const std::vector<float>& CMS2::taus_pf_byMediumIsolationMVA() {return taus_pf_byMediumIsolationMVA_handle.get();}
const std::vector<float>& CMS2::taus_pf_byMediumIsolationMVA2() {return taus_pf_byMediumIsolationMVA2_handle.get();}
const std::vector<float>& CMS2::taus_pf_byTightCombinedIsolationDeltaBetaCorr() {return taus_pf_byTightCombinedIsolationDeltaBetaCorr_handle.get();}
const std::vector<float>& CMS2::taus_pf_byTightCombinedIsolationDeltaBetaCorr3Hits() {return taus_pf_byTightCombinedIsolationDeltaBetaCorr3Hits_handle.get();}
const std::vector<float>& CMS2::taus_pf_byTightIsolationMVA() {return taus_pf_byTightIsolationMVA_handle.get();}
const std::vector<float>& CMS2::taus_pf_byTightIsolationMVA2() {return taus_pf_byTightIsolationMVA2_handle.get();}
const std::vector<float>& CMS2::taus_pf_byVLooseCombinedIsolationDeltaBetaCorr() {return taus_pf_byVLooseCombinedIsolationDeltaBetaCorr_handle.get();}
const std::vector<float>& CMS2::photons_e1x5() {return photons_e1x5_handle.get();}
const std::vector<float>& CMS2::photons_e2x5Max() {return photons_e2x5Max_handle.get();}
const std::vector<float>& CMS2::photons_e3x3() {return photons_e3x3_handle.get();}
const std::vector<float>& CMS2::photons_e5x5() {return photons_e5x5_handle.get();}
const std::vector<float>& CMS2::photons_ecalIso03() {return photons_ecalIso03_handle.get();}
const std::vector<float>& CMS2::photons_ecalIso04() {return photons_ecalIso04_handle.get();}
const std::vector<float>& CMS2::photons_hOverE() {return photons_hOverE_handle.get();}
const std::vector<float>& CMS2::photons_hcalDepth1TowerSumEtBcConeDR03() {return photons_hcalDepth1TowerSumEtBcConeDR03_handle.get();}
const std::vector<float>& CMS2::photons_hcalDepth1TowerSumEtBcConeDR04() {return photons_hcalDepth1TowerSumEtBcConeDR04_handle.get();}
const std::vector<float>& CMS2::photons_hcalDepth2TowerSumEtBcConeDR03() {return photons_hcalDepth2TowerSumEtBcConeDR03_handle.get();}
const std::vector<float>& CMS2::photons_hcalDepth2TowerSumEtBcConeDR04() {return photons_hcalDepth2TowerSumEtBcConeDR04_handle.get();}
const std::vector<float>& CMS2::photons_hcalIso03() {return photons_hcalIso03_handle.get();}
const std::vector<float>& CMS2::photons_hcalIso04() {return photons_hcalIso04_handle.get();}
const std::vector<float>& CMS2::photons_hcalTowerSumEtBcConeDR03() {return photons_hcalTowerSumEtBcConeDR03_handle.get();}
const std::vector<float>& CMS2::photons_hcalTowerSumEtBcConeDR04() {return photons_hcalTowerSumEtBcConeDR04_handle.get();}
const std::vector<float>& CMS2::photons_ntkIsoHollow03() {return photons_ntkIsoHollow03_handle.get();}
const std::vector<float>& CMS2::photons_ntkIsoHollow04() {return photons_ntkIsoHollow04_handle.get();}
const std::vector<float>& CMS2::photons_ntkIsoSolid03() {return photons_ntkIsoSolid03_handle.get();}
const std::vector<float>& CMS2::photons_ntkIsoSolid04() {return photons_ntkIsoSolid04_handle.get();}
const std::vector<float>& CMS2::photons_sigmaEtaEta() {return photons_sigmaEtaEta_handle.get();}
const std::vector<float>& CMS2::photons_sigmaIEtaIEta() {return photons_sigmaIEtaIEta_handle.get();}
const std::vector<float>& CMS2::photons_swissSeed() {return photons_swissSeed_handle.get();}
const std::vector<float>& CMS2::photons_tkIsoHollow03() {return photons_tkIsoHollow03_handle.get();}
const std::vector<float>& CMS2::photons_tkIsoHollow04() {return photons_tkIsoHollow04_handle.get();}
const std::vector<float>& CMS2::photons_tkIsoSolid03() {return photons_tkIsoSolid03_handle.get();}
const std::vector<float>& CMS2::photons_tkIsoSolid04() {return photons_tkIsoSolid04_handle.get();}
const std::vector<float>& CMS2::puInfo_trueNumInteractions() {return puInfo_trueNumInteractions_handle.get();}
const std::vector<float>& CMS2::convs_chi2() {return convs_chi2_handle.get();}
const std::vector<float>& CMS2::convs_dl() {return convs_dl_handle.get();}
const std::vector<float>& CMS2::convs_ndof() {return convs_ndof_handle.get();}
const std::vector<float>& CMS2::sparm_values() {return sparm_values_handle.get();}
const std::vector<float>& CMS2::scs_clustersSize() {return scs_clustersSize_handle.get();}
const std::vector<float>& CMS2::scs_crystalsSize() {return scs_crystalsSize_handle.get();}
const std::vector<float>& CMS2::scs_e1x3() {return scs_e1x3_handle.get();}
const std::vector<float>& CMS2::scs_e1x5() {return scs_e1x5_handle.get();}
const std::vector<float>& CMS2::scs_e2nd() {return scs_e2nd_handle.get();}
const std::vector<float>& CMS2::scs_e2x2() {return scs_e2x2_handle.get();}
const std::vector<float>& CMS2::scs_e2x5Max() {return scs_e2x5Max_handle.get();}
const std::vector<float>& CMS2::scs_e3x1() {return scs_e3x1_handle.get();}
const std::vector<float>& CMS2::scs_e3x2() {return scs_e3x2_handle.get();}
const std::vector<float>& CMS2::scs_e3x3() {return scs_e3x3_handle.get();}
const std::vector<float>& CMS2::scs_e4x4() {return scs_e4x4_handle.get();}
const std::vector<float>& CMS2::scs_e5x5() {return scs_e5x5_handle.get();}
const std::vector<float>& CMS2::scs_eMax() {return scs_eMax_handle.get();}
const std::vector<float>& CMS2::scs_eSeed() {return scs_eSeed_handle.get();}
const std::vector<float>& CMS2::scs_energy() {return scs_energy_handle.get();}
const std::vector<float>& CMS2::scs_eta() {return scs_eta_handle.get();}
const std::vector<float>& CMS2::scs_hoe() {return scs_hoe_handle.get();}
const std::vector<float>& CMS2::scs_laserCorMax() {return scs_laserCorMax_handle.get();}
const std::vector<float>& CMS2::scs_laserCorMean() {return scs_laserCorMean_handle.get();}
const std::vector<float>& CMS2::scs_laserCorSeed() {return scs_laserCorSeed_handle.get();}
const std::vector<float>& CMS2::scs_phi() {return scs_phi_handle.get();}
const std::vector<float>& CMS2::scs_preshowerEnergy() {return scs_preshowerEnergy_handle.get();}
const std::vector<float>& CMS2::scs_rawEnergy() {return scs_rawEnergy_handle.get();}
const std::vector<float>& CMS2::scs_sigmaEtaEta() {return scs_sigmaEtaEta_handle.get();}
const std::vector<float>& CMS2::scs_sigmaEtaPhi() {return scs_sigmaEtaPhi_handle.get();}
const std::vector<float>& CMS2::scs_sigmaIEtaIEta() {return scs_sigmaIEtaIEta_handle.get();}
const std::vector<float>& CMS2::scs_sigmaIEtaIEtaSC() {return scs_sigmaIEtaIEtaSC_handle.get();}
const std::vector<float>& CMS2::scs_sigmaIEtaIPhi() {return scs_sigmaIEtaIPhi_handle.get();}
const std::vector<float>& CMS2::scs_sigmaIEtaIPhiSC() {return scs_sigmaIEtaIPhiSC_handle.get();}
const std::vector<float>& CMS2::scs_sigmaIPhiIPhi() {return scs_sigmaIPhiIPhi_handle.get();}
const std::vector<float>& CMS2::scs_sigmaIPhiIPhiSC() {return scs_sigmaIPhiIPhiSC_handle.get();}
const std::vector<float>& CMS2::scs_sigmaPhiPhi() {return scs_sigmaPhiPhi_handle.get();}
const std::vector<float>& CMS2::scs_timeSeed() {return scs_timeSeed_handle.get();}
const std::vector<float>& CMS2::svs_anglePV() {return svs_anglePV_handle.get();}
const std::vector<float>& CMS2::svs_chi2() {return svs_chi2_handle.get();}
const std::vector<float>& CMS2::svs_dist3Dsig() {return svs_dist3Dsig_handle.get();}
const std::vector<float>& CMS2::svs_dist3Dval() {return svs_dist3Dval_handle.get();}
const std::vector<float>& CMS2::svs_distXYsig() {return svs_distXYsig_handle.get();}
const std::vector<float>& CMS2::svs_distXYval() {return svs_distXYval_handle.get();}
const std::vector<float>& CMS2::svs_ndof() {return svs_ndof_handle.get();}
const std::vector<float>& CMS2::svs_prob() {return svs_prob_handle.get();}
const std::vector<float>& CMS2::svs_xError() {return svs_xError_handle.get();}
const std::vector<float>& CMS2::svs_yError() {return svs_yError_handle.get();}
const std::vector<float>& CMS2::svs_zError() {return svs_zError_handle.get();}
const std::vector<float>& CMS2::mus_tcmet_deltax() {return mus_tcmet_deltax_handle.get();}
const std::vector<float>& CMS2::mus_tcmet_deltay() {return mus_tcmet_deltay_handle.get();}
const std::vector<float>& CMS2::pfcands_dzpv() {return pfcands_dzpv_handle.get();}
const std::vector<float>& CMS2::pfcands_trkiso() {return pfcands_trkiso_handle.get();}
const std::vector<float>& CMS2::trks_chi2() {return trks_chi2_handle.get();}
const std::vector<float>& CMS2::trks_d0() {return trks_d0_handle.get();}
const std::vector<float>& CMS2::trks_d0Err() {return trks_d0Err_handle.get();}
const std::vector<float>& CMS2::trks_d0corr() {return trks_d0corr_handle.get();}
const std::vector<float>& CMS2::trks_d0corrPhi() {return trks_d0corrPhi_handle.get();}
const std::vector<float>& CMS2::trks_d0phiCov() {return trks_d0phiCov_handle.get();}
const std::vector<float>& CMS2::trks_etaErr() {return trks_etaErr_handle.get();}
const std::vector<float>& CMS2::trks_layer1_charge() {return trks_layer1_charge_handle.get();}
const std::vector<float>& CMS2::trks_ndof() {return trks_ndof_handle.get();}
const std::vector<float>& CMS2::trks_phiErr() {return trks_phiErr_handle.get();}
const std::vector<float>& CMS2::trks_ptErr() {return trks_ptErr_handle.get();}
const std::vector<float>& CMS2::trks_validFraction() {return trks_validFraction_handle.get();}
const std::vector<float>& CMS2::trks_z0() {return trks_z0_handle.get();}
const std::vector<float>& CMS2::trks_z0Err() {return trks_z0Err_handle.get();}
const std::vector<float>& CMS2::trks_z0corr() {return trks_z0corr_handle.get();}
const std::vector<float>& CMS2::trkjets_cor() {return trkjets_cor_handle.get();}
const std::vector<float>& CMS2::trks_d0Errvtx() {return trks_d0Errvtx_handle.get();}
const std::vector<float>& CMS2::trks_d0vtx() {return trks_d0vtx_handle.get();}
const std::vector<float>& CMS2::vtxs_chi2() {return vtxs_chi2_handle.get();}
const std::vector<float>& CMS2::vtxs_ndof() {return vtxs_ndof_handle.get();}
const std::vector<float>& CMS2::vtxs_sumpt() {return vtxs_sumpt_handle.get();}
const std::vector<float>& CMS2::vtxs_xError() {return vtxs_xError_handle.get();}
const std::vector<float>& CMS2::vtxs_yError() {return vtxs_yError_handle.get();}
const std::vector<float>& CMS2::vtxs_zError() {return vtxs_zError_handle.get();}
const std::vector<float>& CMS2::bsvtxs_chi2() {return bsvtxs_chi2_handle.get();}
const std::vector<float>& CMS2::bsvtxs_ndof() {return bsvtxs_ndof_handle.get();}
const std::vector<float>& CMS2::bsvtxs_sumpt() {return bsvtxs_sumpt_handle.get();}
const std::vector<float>& CMS2::bsvtxs_xError() {return bsvtxs_xError_handle.get();}
const std::vector<float>& CMS2::bsvtxs_yError() {return bsvtxs_yError_handle.get();}
const std::vector<float>& CMS2::bsvtxs_zError() {return bsvtxs_zError_handle.get();}
const std::vector<std::vector<float> >& CMS2::els_convs_dcot() {return els_convs_dcot_handle.get();}
const std::vector<std::vector<float> >& CMS2::els_convs_dist() {return els_convs_dist_handle.get();}
const std::vector<std::vector<float> >& CMS2::els_convs_radius() {return els_convs_radius_handle.get();}
const std::vector<std::vector<float> >& CMS2::mus_stationShowerDeltaR() {return mus_stationShowerDeltaR_handle.get();}
const std::vector<std::vector<float> >& CMS2::mus_stationShowerSizeT() {return mus_stationShowerSizeT_handle.get();}
const std::vector<std::vector<float> >& CMS2::puInfo_instLumi() {return puInfo_instLumi_handle.get();}
const std::vector<std::vector<float> >& CMS2::puInfo_sump_highpt() {return puInfo_sump_highpt_handle.get();}
const std::vector<std::vector<float> >& CMS2::puInfo_sumpt_lowpt() {return puInfo_sumpt_lowpt_handle.get();}
const std::vector<std::vector<float> >& CMS2::puInfo_zpositions() {return puInfo_zpositions_handle.get();}
const std::vector<std::vector<float> >& CMS2::vtxs_covMatrix() {return vtxs_covMatrix_handle.get();}
const std::vector<std::vector<float> >& CMS2::bsvtxs_covMatrix() {return bsvtxs_covMatrix_handle.get();}
const int& CMS2::evt_cscLooseHaloId() {return evt_cscLooseHaloId_handle.get();}
const int& CMS2::evt_cscTightHaloId() {return evt_cscTightHaloId_handle.get();}
const int& CMS2::evt_ecalLooseHaloId() {return evt_ecalLooseHaloId_handle.get();}
const int& CMS2::evt_ecalTightHaloId() {return evt_ecalTightHaloId_handle.get();}
const int& CMS2::evt_extremeTightHaloId() {return evt_extremeTightHaloId_handle.get();}
const int& CMS2::evt_globalLooseHaloId() {return evt_globalLooseHaloId_handle.get();}
const int& CMS2::evt_globalTightHaloId() {return evt_globalTightHaloId_handle.get();}
const int& CMS2::evt_hcalLooseHaloId() {return evt_hcalLooseHaloId_handle.get();}
const int& CMS2::evt_hcalTightHaloId() {return evt_hcalTightHaloId_handle.get();}
const int& CMS2::evt_looseHaloId() {return evt_looseHaloId_handle.get();}
const int& CMS2::evt_nHaloLikeTracks() {return evt_nHaloLikeTracks_handle.get();}
const int& CMS2::evt_nHaloTriggerCandidates() {return evt_nHaloTriggerCandidates_handle.get();}
const int& CMS2::evt_tightHaloId() {return evt_tightHaloId_handle.get();}
const int& CMS2::evt_bsType() {return evt_bsType_handle.get();}
const int& CMS2::evt_bunchCrossing() {return evt_bunchCrossing_handle.get();}
const int& CMS2::evt_experimentType() {return evt_experimentType_handle.get();}
const int& CMS2::evt_isRealData() {return evt_isRealData_handle.get();}
const int& CMS2::evt_orbitNumber() {return evt_orbitNumber_handle.get();}
const int& CMS2::evt_storeNumber() {return evt_storeNumber_handle.get();}
const int& CMS2::hcalnoise_GetRecHitCount() {return hcalnoise_GetRecHitCount_handle.get();}
const int& CMS2::hcalnoise_GetRecHitCount15() {return hcalnoise_GetRecHitCount15_handle.get();}
const int& CMS2::hcalnoise_maxHPDHits() {return hcalnoise_maxHPDHits_handle.get();}
const int& CMS2::hcalnoise_maxHPDNoOtherHits() {return hcalnoise_maxHPDNoOtherHits_handle.get();}
const int& CMS2::hcalnoise_maxRBXHits() {return hcalnoise_maxRBXHits_handle.get();}
const int& CMS2::hcalnoise_maxZeros() {return hcalnoise_maxZeros_handle.get();}
const int& CMS2::hcalnoise_noiseFilterStatus() {return hcalnoise_noiseFilterStatus_handle.get();}
const int& CMS2::hcalnoise_noiseType() {return hcalnoise_noiseType_handle.get();}
const int& CMS2::hcalnoise_num10GeVHits() {return hcalnoise_num10GeVHits_handle.get();}
const int& CMS2::hcalnoise_num25GeVHits() {return hcalnoise_num25GeVHits_handle.get();}
const int& CMS2::hcalnoise_numFlatNoiseChannels() {return hcalnoise_numFlatNoiseChannels_handle.get();}
const int& CMS2::hcalnoise_numIsolatedNoiseChannels() {return hcalnoise_numIsolatedNoiseChannels_handle.get();}
const int& CMS2::hcalnoise_numProblematicRBXs() {return hcalnoise_numProblematicRBXs_handle.get();}
const int& CMS2::hcalnoise_numSpikeNoiseChannels() {return hcalnoise_numSpikeNoiseChannels_handle.get();}
const int& CMS2::hcalnoise_numTS4TS5NoiseChannels() {return hcalnoise_numTS4TS5NoiseChannels_handle.get();}
const int& CMS2::hcalnoise_numTriangleNoiseChannels() {return hcalnoise_numTriangleNoiseChannels_handle.get();}
const int& CMS2::hcalnoise_passHighLevelNoiseFilter() {return hcalnoise_passHighLevelNoiseFilter_handle.get();}
const int& CMS2::hcalnoise_passLooseNoiseFilter() {return hcalnoise_passLooseNoiseFilter_handle.get();}
const int& CMS2::hcalnoise_passTightNoiseFilter() {return hcalnoise_passTightNoiseFilter_handle.get();}
const int& CMS2::l1_nemiso() {return l1_nemiso_handle.get();}
const int& CMS2::l1_nemnoiso() {return l1_nemnoiso_handle.get();}
const int& CMS2::l1_njetsc() {return l1_njetsc_handle.get();}
const int& CMS2::l1_njetsf() {return l1_njetsf_handle.get();}
const int& CMS2::l1_njetst() {return l1_njetst_handle.get();}
const int& CMS2::l1_nmus() {return l1_nmus_handle.get();}
const int& CMS2::ls_lumiSecQual() {return ls_lumiSecQual_handle.get();}
const int& CMS2::pdfinfo_id1() {return pdfinfo_id1_handle.get();}
const int& CMS2::pdfinfo_id2() {return pdfinfo_id2_handle.get();}
const int& CMS2::sparm_subProcessId() {return sparm_subProcessId_handle.get();}
const std::vector<int>& CMS2::evt_ecaliPhiSuspects() {return evt_ecaliPhiSuspects_handle.get();}
const std::vector<int>& CMS2::evt_globaliPhiSuspects() {return evt_globaliPhiSuspects_handle.get();}
const std::vector<int>& CMS2::evt_hcaliPhiSuspects() {return evt_hcaliPhiSuspects_handle.get();}
const std::vector<int>& CMS2::els_mc3_id() {return els_mc3_id_handle.get();}
const std::vector<int>& CMS2::els_mc3idx() {return els_mc3idx_handle.get();}
const std::vector<int>& CMS2::els_mc3_motherid() {return els_mc3_motherid_handle.get();}
const std::vector<int>& CMS2::els_mc3_motheridx() {return els_mc3_motheridx_handle.get();}
const std::vector<int>& CMS2::els_mc_id() {return els_mc_id_handle.get();}
const std::vector<int>& CMS2::els_mcidx() {return els_mcidx_handle.get();}
const std::vector<int>& CMS2::els_mc_motherid() {return els_mc_motherid_handle.get();}
const std::vector<int>& CMS2::jets_mc3_id() {return jets_mc3_id_handle.get();}
const std::vector<int>& CMS2::jets_mc3idx() {return jets_mc3idx_handle.get();}
const std::vector<int>& CMS2::jets_mc_gpidx() {return jets_mc_gpidx_handle.get();}
const std::vector<int>& CMS2::jets_mc_id() {return jets_mc_id_handle.get();}
const std::vector<int>& CMS2::jets_mcidx() {return jets_mcidx_handle.get();}
const std::vector<int>& CMS2::jets_mc_motherid() {return jets_mc_motherid_handle.get();}
const std::vector<int>& CMS2::mus_mc3_id() {return mus_mc3_id_handle.get();}
const std::vector<int>& CMS2::mus_mc3idx() {return mus_mc3idx_handle.get();}
const std::vector<int>& CMS2::mus_mc3_motherid() {return mus_mc3_motherid_handle.get();}
const std::vector<int>& CMS2::mus_mc3_motheridx() {return mus_mc3_motheridx_handle.get();}
const std::vector<int>& CMS2::mus_mc_id() {return mus_mc_id_handle.get();}
const std::vector<int>& CMS2::mus_mcidx() {return mus_mcidx_handle.get();}
const std::vector<int>& CMS2::mus_mc_motherid() {return mus_mc_motherid_handle.get();}
const std::vector<int>& CMS2::pfjets_mc3_id() {return pfjets_mc3_id_handle.get();}
const std::vector<int>& CMS2::pfjets_mc3idx() {return pfjets_mc3idx_handle.get();}
const std::vector<int>& CMS2::pfjets_mc_gpidx() {return pfjets_mc_gpidx_handle.get();}
const std::vector<int>& CMS2::pfjets_mc_id() {return pfjets_mc_id_handle.get();}
const std::vector<int>& CMS2::pfjets_mcidx() {return pfjets_mcidx_handle.get();}
const std::vector<int>& CMS2::pfjets_mc_motherid() {return pfjets_mc_motherid_handle.get();}
const std::vector<int>& CMS2::photons_mc3_id() {return photons_mc3_id_handle.get();}
const std::vector<int>& CMS2::photons_mc3idx() {return photons_mc3idx_handle.get();}
const std::vector<int>& CMS2::photons_mc3_motherid() {return photons_mc3_motherid_handle.get();}
const std::vector<int>& CMS2::photons_mc3_motheridx() {return photons_mc3_motheridx_handle.get();}
const std::vector<int>& CMS2::photons_mc_id() {return photons_mc_id_handle.get();}
const std::vector<int>& CMS2::photons_mcidx() {return photons_mcidx_handle.get();}
const std::vector<int>& CMS2::photons_mc_motherid() {return photons_mc_motherid_handle.get();}
const std::vector<int>& CMS2::trk_mc3_id() {return trk_mc3_id_handle.get();}
const std::vector<int>& CMS2::trk_mc3idx() {return trk_mc3idx_handle.get();}
const std::vector<int>& CMS2::trk_mc3_motherid() {return trk_mc3_motherid_handle.get();}
const std::vector<int>& CMS2::trk_mc3_motheridx() {return trk_mc3_motheridx_handle.get();}
const std::vector<int>& CMS2::trk_mc_id() {return trk_mc_id_handle.get();}
const std::vector<int>& CMS2::trk_mcidx() {return trk_mcidx_handle.get();}
const std::vector<int>& CMS2::trk_mc_motherid() {return trk_mc_motherid_handle.get();}
const std::vector<int>& CMS2::els_closestJet() {return els_closestJet_handle.get();}
const std::vector<int>& CMS2::els_closestMuon() {return els_closestMuon_handle.get();}
const std::vector<int>& CMS2::els_pfelsidx() {return els_pfelsidx_handle.get();}
const std::vector<int>& CMS2::els_category() {return els_category_handle.get();}
const std::vector<int>& CMS2::els_charge() {return els_charge_handle.get();}
const std::vector<int>& CMS2::els_ckf_laywithmeas() {return els_ckf_laywithmeas_handle.get();}
const std::vector<int>& CMS2::els_class() {return els_class_handle.get();}
const std::vector<int>& CMS2::els_conv_delMissHits() {return els_conv_delMissHits_handle.get();}
const std::vector<int>& CMS2::els_conv_flag() {return els_conv_flag_handle.get();}
const std::vector<int>& CMS2::els_conv_gsftkidx() {return els_conv_gsftkidx_handle.get();}
const std::vector<int>& CMS2::els_conv_old_delMissHits() {return els_conv_old_delMissHits_handle.get();}
const std::vector<int>& CMS2::els_conv_old_flag() {return els_conv_old_flag_handle.get();}
const std::vector<int>& CMS2::els_conv_old_gsftkidx() {return els_conv_old_gsftkidx_handle.get();}
const std::vector<int>& CMS2::els_conv_old_tkidx() {return els_conv_old_tkidx_handle.get();}
const std::vector<int>& CMS2::els_conv_tkidx() {return els_conv_tkidx_handle.get();}
const std::vector<int>& CMS2::els_exp_innerlayers() {return els_exp_innerlayers_handle.get();}
const std::vector<int>& CMS2::els_exp_outerlayers() {return els_exp_outerlayers_handle.get();}
const std::vector<int>& CMS2::els_fiduciality() {return els_fiduciality_handle.get();}
const std::vector<int>& CMS2::els_gsftrkidx() {return els_gsftrkidx_handle.get();}
const std::vector<int>& CMS2::els_layer1_det() {return els_layer1_det_handle.get();}
const std::vector<int>& CMS2::els_layer1_layer() {return els_layer1_layer_handle.get();}
const std::vector<int>& CMS2::els_layer1_sizerphi() {return els_layer1_sizerphi_handle.get();}
const std::vector<int>& CMS2::els_layer1_sizerz() {return els_layer1_sizerz_handle.get();}
const std::vector<int>& CMS2::els_lostHits() {return els_lostHits_handle.get();}
const std::vector<int>& CMS2::els_lost_pixelhits() {return els_lost_pixelhits_handle.get();}
const std::vector<int>& CMS2::els_nSeed() {return els_nSeed_handle.get();}
const std::vector<int>& CMS2::els_sccharge() {return els_sccharge_handle.get();}
const std::vector<int>& CMS2::els_scindex() {return els_scindex_handle.get();}
const std::vector<int>& CMS2::els_trk_charge() {return els_trk_charge_handle.get();}
const std::vector<int>& CMS2::els_trkidx() {return els_trkidx_handle.get();}
const std::vector<int>& CMS2::els_type() {return els_type_handle.get();}
const std::vector<int>& CMS2::els_validHits() {return els_validHits_handle.get();}
const std::vector<int>& CMS2::els_valid_pixelhits() {return els_valid_pixelhits_handle.get();}
const std::vector<int>& CMS2::genps_id() {return genps_id_handle.get();}
const std::vector<int>& CMS2::genps_id_mother() {return genps_id_mother_handle.get();}
const std::vector<int>& CMS2::genps_status() {return genps_status_handle.get();}
const std::vector<int>& CMS2::gsftrks_charge() {return gsftrks_charge_handle.get();}
const std::vector<int>& CMS2::gsftrks_exp_innerlayers() {return gsftrks_exp_innerlayers_handle.get();}
const std::vector<int>& CMS2::gsftrks_exp_outerlayers() {return gsftrks_exp_outerlayers_handle.get();}
const std::vector<int>& CMS2::gsftrks_layer1_det() {return gsftrks_layer1_det_handle.get();}
const std::vector<int>& CMS2::gsftrks_layer1_layer() {return gsftrks_layer1_layer_handle.get();}
const std::vector<int>& CMS2::gsftrks_layer1_sizerphi() {return gsftrks_layer1_sizerphi_handle.get();}
const std::vector<int>& CMS2::gsftrks_layer1_sizerz() {return gsftrks_layer1_sizerz_handle.get();}
const std::vector<int>& CMS2::gsftrks_lostHits() {return gsftrks_lostHits_handle.get();}
const std::vector<int>& CMS2::gsftrks_lost_pixelhits() {return gsftrks_lost_pixelhits_handle.get();}
const std::vector<int>& CMS2::gsftrks_nlayers() {return gsftrks_nlayers_handle.get();}
const std::vector<int>& CMS2::gsftrks_nlayers3D() {return gsftrks_nlayers3D_handle.get();}
const std::vector<int>& CMS2::gsftrks_nlayersLost() {return gsftrks_nlayersLost_handle.get();}
const std::vector<int>& CMS2::gsftrks_validHits() {return gsftrks_validHits_handle.get();}
const std::vector<int>& CMS2::gsftrks_valid_pixelhits() {return gsftrks_valid_pixelhits_handle.get();}
const std::vector<int>& CMS2::hyp_ll_charge() {return hyp_ll_charge_handle.get();}
const std::vector<int>& CMS2::hyp_ll_id() {return hyp_ll_id_handle.get();}
const std::vector<int>& CMS2::hyp_ll_index() {return hyp_ll_index_handle.get();}
const std::vector<int>& CMS2::hyp_ll_lostHits() {return hyp_ll_lostHits_handle.get();}
const std::vector<int>& CMS2::hyp_ll_validHits() {return hyp_ll_validHits_handle.get();}
const std::vector<int>& CMS2::hyp_lt_charge() {return hyp_lt_charge_handle.get();}
const std::vector<int>& CMS2::hyp_lt_id() {return hyp_lt_id_handle.get();}
const std::vector<int>& CMS2::hyp_lt_index() {return hyp_lt_index_handle.get();}
const std::vector<int>& CMS2::hyp_lt_lostHits() {return hyp_lt_lostHits_handle.get();}
const std::vector<int>& CMS2::hyp_lt_validHits() {return hyp_lt_validHits_handle.get();}
const std::vector<int>& CMS2::hyp_njets() {return hyp_njets_handle.get();}
const std::vector<int>& CMS2::hyp_nojets() {return hyp_nojets_handle.get();}
const std::vector<int>& CMS2::hyp_type() {return hyp_type_handle.get();}
const std::vector<int>& CMS2::hyp_FVFit_ndf() {return hyp_FVFit_ndf_handle.get();}
const std::vector<int>& CMS2::hyp_FVFit_status() {return hyp_FVFit_status_handle.get();}
const std::vector<int>& CMS2::hyp_ll_mc_id() {return hyp_ll_mc_id_handle.get();}
const std::vector<int>& CMS2::hyp_ll_mc_motherid() {return hyp_ll_mc_motherid_handle.get();}
const std::vector<int>& CMS2::hyp_lt_mc_id() {return hyp_lt_mc_id_handle.get();}
const std::vector<int>& CMS2::hyp_lt_mc_motherid() {return hyp_lt_mc_motherid_handle.get();}
const std::vector<int>& CMS2::pfjets_mcflavorAlgo() {return pfjets_mcflavorAlgo_handle.get();}
const std::vector<int>& CMS2::pfjets_mcflavorPhys() {return pfjets_mcflavorPhys_handle.get();}
const std::vector<int>& CMS2::jets_closestElectron() {return jets_closestElectron_handle.get();}
const std::vector<int>& CMS2::jets_closestMuon() {return jets_closestMuon_handle.get();}
const std::vector<int>& CMS2::l1_emiso_ieta() {return l1_emiso_ieta_handle.get();}
const std::vector<int>& CMS2::l1_emiso_iphi() {return l1_emiso_iphi_handle.get();}
const std::vector<int>& CMS2::l1_emiso_rawId() {return l1_emiso_rawId_handle.get();}
const std::vector<int>& CMS2::l1_emiso_type() {return l1_emiso_type_handle.get();}
const std::vector<int>& CMS2::l1_emnoiso_ieta() {return l1_emnoiso_ieta_handle.get();}
const std::vector<int>& CMS2::l1_emnoiso_iphi() {return l1_emnoiso_iphi_handle.get();}
const std::vector<int>& CMS2::l1_emnoiso_rawId() {return l1_emnoiso_rawId_handle.get();}
const std::vector<int>& CMS2::l1_emnoiso_type() {return l1_emnoiso_type_handle.get();}
const std::vector<int>& CMS2::l1_jetsc_ieta() {return l1_jetsc_ieta_handle.get();}
const std::vector<int>& CMS2::l1_jetsc_iphi() {return l1_jetsc_iphi_handle.get();}
const std::vector<int>& CMS2::l1_jetsc_rawId() {return l1_jetsc_rawId_handle.get();}
const std::vector<int>& CMS2::l1_jetsc_type() {return l1_jetsc_type_handle.get();}
const std::vector<int>& CMS2::l1_jetsf_ieta() {return l1_jetsf_ieta_handle.get();}
const std::vector<int>& CMS2::l1_jetsf_iphi() {return l1_jetsf_iphi_handle.get();}
const std::vector<int>& CMS2::l1_jetsf_rawId() {return l1_jetsf_rawId_handle.get();}
const std::vector<int>& CMS2::l1_jetsf_type() {return l1_jetsf_type_handle.get();}
const std::vector<int>& CMS2::l1_jetst_ieta() {return l1_jetst_ieta_handle.get();}
const std::vector<int>& CMS2::l1_jetst_iphi() {return l1_jetst_iphi_handle.get();}
const std::vector<int>& CMS2::l1_jetst_rawId() {return l1_jetst_rawId_handle.get();}
const std::vector<int>& CMS2::l1_jetst_type() {return l1_jetst_type_handle.get();}
const std::vector<int>& CMS2::l1_mus_flags() {return l1_mus_flags_handle.get();}
const std::vector<int>& CMS2::l1_mus_q() {return l1_mus_q_handle.get();}
const std::vector<int>& CMS2::l1_mus_qual() {return l1_mus_qual_handle.get();}
const std::vector<int>& CMS2::l1_mus_qualFlags() {return l1_mus_qualFlags_handle.get();}
const std::vector<int>& CMS2::mus_met_flag() {return mus_met_flag_handle.get();}
const std::vector<int>& CMS2::mus_closestEle() {return mus_closestEle_handle.get();}
const std::vector<int>& CMS2::mus_closestJet() {return mus_closestJet_handle.get();}
const std::vector<int>& CMS2::mus_pfmusidx() {return mus_pfmusidx_handle.get();}
const std::vector<int>& CMS2::mus_charge() {return mus_charge_handle.get();}
const std::vector<int>& CMS2::mus_gfit_validHits() {return mus_gfit_validHits_handle.get();}
const std::vector<int>& CMS2::mus_gfit_validSTAHits() {return mus_gfit_validSTAHits_handle.get();}
const std::vector<int>& CMS2::mus_gfit_validSiHits() {return mus_gfit_validSiHits_handle.get();}
const std::vector<int>& CMS2::mus_goodmask() {return mus_goodmask_handle.get();}
const std::vector<int>& CMS2::mus_iso03_ntrk() {return mus_iso03_ntrk_handle.get();}
const std::vector<int>& CMS2::mus_iso05_ntrk() {return mus_iso05_ntrk_handle.get();}
const std::vector<int>& CMS2::mus_lostHits() {return mus_lostHits_handle.get();}
const std::vector<int>& CMS2::mus_muonBestTrackType() {return mus_muonBestTrackType_handle.get();}
const std::vector<int>& CMS2::mus_nOverlaps() {return mus_nOverlaps_handle.get();}
const std::vector<int>& CMS2::mus_nmatches() {return mus_nmatches_handle.get();}
const std::vector<int>& CMS2::mus_numberOfMatchedStations() {return mus_numberOfMatchedStations_handle.get();}
const std::vector<int>& CMS2::mus_overlap0() {return mus_overlap0_handle.get();}
const std::vector<int>& CMS2::mus_overlap1() {return mus_overlap1_handle.get();}
const std::vector<int>& CMS2::mus_pfcharge() {return mus_pfcharge_handle.get();}
const std::vector<int>& CMS2::mus_pfflag() {return mus_pfflag_handle.get();}
const std::vector<int>& CMS2::mus_pfparticleId() {return mus_pfparticleId_handle.get();}
const std::vector<int>& CMS2::mus_pid_PFMuon() {return mus_pid_PFMuon_handle.get();}
const std::vector<int>& CMS2::mus_pid_TM2DCompatibilityLoose() {return mus_pid_TM2DCompatibilityLoose_handle.get();}
const std::vector<int>& CMS2::mus_pid_TM2DCompatibilityTight() {return mus_pid_TM2DCompatibilityTight_handle.get();}
const std::vector<int>& CMS2::mus_pid_TMLastStationLoose() {return mus_pid_TMLastStationLoose_handle.get();}
const std::vector<int>& CMS2::mus_pid_TMLastStationTight() {return mus_pid_TMLastStationTight_handle.get();}
const std::vector<int>& CMS2::mus_sta_validHits() {return mus_sta_validHits_handle.get();}
const std::vector<int>& CMS2::mus_timeDirection() {return mus_timeDirection_handle.get();}
const std::vector<int>& CMS2::mus_timeNumStationsUsed() {return mus_timeNumStationsUsed_handle.get();}
const std::vector<int>& CMS2::mus_trk_charge() {return mus_trk_charge_handle.get();}
const std::vector<int>& CMS2::mus_trkidx() {return mus_trkidx_handle.get();}
const std::vector<int>& CMS2::mus_type() {return mus_type_handle.get();}
const std::vector<int>& CMS2::mus_validHits() {return mus_validHits_handle.get();}
const std::vector<int>& CMS2::pfcands_charge() {return pfcands_charge_handle.get();}
const std::vector<int>& CMS2::pfcands_flag() {return pfcands_flag_handle.get();}
const std::vector<int>& CMS2::pfcands_particleId() {return pfcands_particleId_handle.get();}
const std::vector<int>& CMS2::pfcands_pfelsidx() {return pfcands_pfelsidx_handle.get();}
const std::vector<int>& CMS2::pfcands_pfmusidx() {return pfcands_pfmusidx_handle.get();}
const std::vector<int>& CMS2::pfcands_trkidx() {return pfcands_trkidx_handle.get();}
const std::vector<int>& CMS2::pfcands_vtxidx() {return pfcands_vtxidx_handle.get();}
const std::vector<int>& CMS2::pfels_elsidx() {return pfels_elsidx_handle.get();}
const std::vector<int>& CMS2::pfels_charge() {return pfels_charge_handle.get();}
const std::vector<int>& CMS2::pfels_flag() {return pfels_flag_handle.get();}
const std::vector<int>& CMS2::pfels_particleId() {return pfels_particleId_handle.get();}
const std::vector<int>& CMS2::pfjets_chargedHadronMultiplicity() {return pfjets_chargedHadronMultiplicity_handle.get();}
const std::vector<int>& CMS2::pfjets_chargedMultiplicity() {return pfjets_chargedMultiplicity_handle.get();}
const std::vector<int>& CMS2::pfjets_electronMultiplicity() {return pfjets_electronMultiplicity_handle.get();}
const std::vector<int>& CMS2::pfjets_hfEmMultiplicity() {return pfjets_hfEmMultiplicity_handle.get();}
const std::vector<int>& CMS2::pfjets_hfHadronMultiplicity() {return pfjets_hfHadronMultiplicity_handle.get();}
const std::vector<int>& CMS2::pfjets_muonMultiplicity() {return pfjets_muonMultiplicity_handle.get();}
const std::vector<int>& CMS2::pfjets_neutralHadronMultiplicity() {return pfjets_neutralHadronMultiplicity_handle.get();}
const std::vector<int>& CMS2::pfjets_neutralMultiplicity() {return pfjets_neutralMultiplicity_handle.get();}
const std::vector<int>& CMS2::pfjets_photonMultiplicity() {return pfjets_photonMultiplicity_handle.get();}
const std::vector<int>& CMS2::pfmus_musidx() {return pfmus_musidx_handle.get();}
const std::vector<int>& CMS2::pfmus_charge() {return pfmus_charge_handle.get();}
const std::vector<int>& CMS2::pfmus_flag() {return pfmus_flag_handle.get();}
const std::vector<int>& CMS2::pfmus_particleId() {return pfmus_particleId_handle.get();}
const std::vector<int>& CMS2::taus_pf_charge() {return taus_pf_charge_handle.get();}
const std::vector<int>& CMS2::taus_pf_pfjetIndex() {return taus_pf_pfjetIndex_handle.get();}
const std::vector<int>& CMS2::photons_fiduciality() {return photons_fiduciality_handle.get();}
const std::vector<int>& CMS2::photons_scindex() {return photons_scindex_handle.get();}
const std::vector<int>& CMS2::puInfo_bunchCrossing() {return puInfo_bunchCrossing_handle.get();}
const std::vector<int>& CMS2::puInfo_nPUvertices() {return puInfo_nPUvertices_handle.get();}
const std::vector<int>& CMS2::convs_algo() {return convs_algo_handle.get();}
const std::vector<int>& CMS2::convs_isConverted() {return convs_isConverted_handle.get();}
const std::vector<int>& CMS2::convs_quality() {return convs_quality_handle.get();}
const std::vector<int>& CMS2::scs_detIdSeed() {return scs_detIdSeed_handle.get();}
const std::vector<int>& CMS2::scs_elsidx() {return scs_elsidx_handle.get();}
const std::vector<int>& CMS2::scs_severitySeed() {return scs_severitySeed_handle.get();}
const std::vector<int>& CMS2::svs_isKs() {return svs_isKs_handle.get();}
const std::vector<int>& CMS2::svs_isLambda() {return svs_isLambda_handle.get();}
const std::vector<int>& CMS2::svs_mc3_id() {return svs_mc3_id_handle.get();}
const std::vector<int>& CMS2::svs_nTrks() {return svs_nTrks_handle.get();}
const std::vector<int>& CMS2::mus_tcmet_flag() {return mus_tcmet_flag_handle.get();}
const std::vector<int>& CMS2::trks_algo() {return trks_algo_handle.get();}
const std::vector<int>& CMS2::trks_charge() {return trks_charge_handle.get();}
const std::vector<int>& CMS2::trks_exp_innerlayers() {return trks_exp_innerlayers_handle.get();}
const std::vector<int>& CMS2::trks_exp_outerlayers() {return trks_exp_outerlayers_handle.get();}
const std::vector<int>& CMS2::trks_layer1_det() {return trks_layer1_det_handle.get();}
const std::vector<int>& CMS2::trks_layer1_layer() {return trks_layer1_layer_handle.get();}
const std::vector<int>& CMS2::trks_layer1_sizerphi() {return trks_layer1_sizerphi_handle.get();}
const std::vector<int>& CMS2::trks_layer1_sizerz() {return trks_layer1_sizerz_handle.get();}
const std::vector<int>& CMS2::trks_lostHits() {return trks_lostHits_handle.get();}
const std::vector<int>& CMS2::trks_lost_pixelhits() {return trks_lost_pixelhits_handle.get();}
const std::vector<int>& CMS2::trks_nLoops() {return trks_nLoops_handle.get();}
const std::vector<int>& CMS2::trks_nlayers() {return trks_nlayers_handle.get();}
const std::vector<int>& CMS2::trks_nlayers3D() {return trks_nlayers3D_handle.get();}
const std::vector<int>& CMS2::trks_nlayersLost() {return trks_nlayersLost_handle.get();}
const std::vector<int>& CMS2::trks_pvidx0() {return trks_pvidx0_handle.get();}
const std::vector<int>& CMS2::trks_pvidx1() {return trks_pvidx1_handle.get();}
const std::vector<int>& CMS2::trks_qualityMask() {return trks_qualityMask_handle.get();}
const std::vector<int>& CMS2::trks_validHits() {return trks_validHits_handle.get();}
const std::vector<int>& CMS2::trks_valid_pixelhits() {return trks_valid_pixelhits_handle.get();}
const std::vector<int>& CMS2::trks_elsidx() {return trks_elsidx_handle.get();}
const std::vector<int>& CMS2::trk_musidx() {return trk_musidx_handle.get();}
const std::vector<int>& CMS2::trkjets_ntrks() {return trkjets_ntrks_handle.get();}
const std::vector<int>& CMS2::trkjets_vtxs_idx() {return trkjets_vtxs_idx_handle.get();}
const std::vector<int>& CMS2::vtxs_isFake() {return vtxs_isFake_handle.get();}
const std::vector<int>& CMS2::vtxs_isValid() {return vtxs_isValid_handle.get();}
const std::vector<int>& CMS2::vtxs_tracksSize() {return vtxs_tracksSize_handle.get();}
const std::vector<int>& CMS2::bsvtxs_isFake() {return bsvtxs_isFake_handle.get();}
const std::vector<int>& CMS2::bsvtxs_isValid() {return bsvtxs_isValid_handle.get();}
const std::vector<int>& CMS2::bsvtxs_tracksSize() {return bsvtxs_tracksSize_handle.get();}
const std::vector<std::vector<int> >& CMS2::els_convs_delMissHits() {return els_convs_delMissHits_handle.get();}
const std::vector<std::vector<int> >& CMS2::els_convs_flag() {return els_convs_flag_handle.get();}
const std::vector<std::vector<int> >& CMS2::els_convs_gsftkidx() {return els_convs_gsftkidx_handle.get();}
const std::vector<std::vector<int> >& CMS2::els_convs_tkidx() {return els_convs_tkidx_handle.get();}
const std::vector<std::vector<int> >& CMS2::genps_lepdaughter_id() {return genps_lepdaughter_id_handle.get();}
const std::vector<std::vector<int> >& CMS2::genps_lepdaughter_idx() {return genps_lepdaughter_idx_handle.get();}
const std::vector<std::vector<int> >& CMS2::hlt_trigObjs_id() {return hlt_trigObjs_id_handle.get();}
const std::vector<std::vector<int> >& CMS2::hyp_jets_idx() {return hyp_jets_idx_handle.get();}
const std::vector<std::vector<int> >& CMS2::hyp_other_jets_idx() {return hyp_other_jets_idx_handle.get();}
const std::vector<std::vector<int> >& CMS2::mus_nStationCorrelatedHits() {return mus_nStationCorrelatedHits_handle.get();}
const std::vector<std::vector<int> >& CMS2::mus_nStationHits() {return mus_nStationHits_handle.get();}
const std::vector<std::vector<int> >& CMS2::pfjets_pfcandIndicies() {return pfjets_pfcandIndicies_handle.get();}
const std::vector<std::vector<int> >& CMS2::taus_pf_pfcandIndicies() {return taus_pf_pfcandIndicies_handle.get();}
const std::vector<std::vector<int> >& CMS2::puInfo_ntrks_highpt() {return puInfo_ntrks_highpt_handle.get();}
const std::vector<std::vector<int> >& CMS2::puInfo_ntrks_lowpt() {return puInfo_ntrks_lowpt_handle.get();}
const std::vector<std::vector<int> >& CMS2::convs_nHitsBeforeVtx() {return convs_nHitsBeforeVtx_handle.get();}
const std::vector<std::vector<int> >& CMS2::convs_tkalgo() {return convs_tkalgo_handle.get();}
const std::vector<std::vector<int> >& CMS2::convs_tkidx() {return convs_tkidx_handle.get();}
const unsigned int& CMS2::els_HLT_Ele17_Ele8_L1sL1DoubleEG137_version() {return els_HLT_Ele17_Ele8_L1sL1DoubleEG137_version_handle.get();}
const unsigned int& CMS2::els_HLT_Ele17_Ele8_LeadingLeg_version() {return els_HLT_Ele17_Ele8_LeadingLeg_version_handle.get();}
const unsigned int& CMS2::els_HLT_Ele17_Ele8_Mass50_LeadingLeg_version() {return els_HLT_Ele17_Ele8_Mass50_LeadingLeg_version_handle.get();}
const unsigned int& CMS2::els_HLT_Ele17_Ele8_Mass50_TrailingLeg_version() {return els_HLT_Ele17_Ele8_Mass50_TrailingLeg_version_handle.get();}
const unsigned int& CMS2::els_HLT_Ele17_Ele8_TrailingLeg_version() {return els_HLT_Ele17_Ele8_TrailingLeg_version_handle.get();}
const unsigned int& CMS2::els_HLT_Ele17_Ele8_version() {return els_HLT_Ele17_Ele8_version_handle.get();}
const unsigned int& CMS2::els_HLT_Ele20_SC4_Mass50_LeadingLeg_version() {return els_HLT_Ele20_SC4_Mass50_LeadingLeg_version_handle.get();}
const unsigned int& CMS2::els_HLT_Ele20_SC4_Mass50_TrailingLeg_version() {return els_HLT_Ele20_SC4_Mass50_TrailingLeg_version_handle.get();}
const unsigned int& CMS2::els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_version() {return els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_version_handle.get();}
const unsigned int& CMS2::els_HLT_Ele27_WP80_version() {return els_HLT_Ele27_WP80_version_handle.get();}
const unsigned int& CMS2::els_HLT_Ele32_SC17_Mass50_LeadingLeg_version() {return els_HLT_Ele32_SC17_Mass50_LeadingLeg_version_handle.get();}
const unsigned int& CMS2::els_HLT_Ele32_SC17_Mass50_TrailingLeg_version() {return els_HLT_Ele32_SC17_Mass50_TrailingLeg_version_handle.get();}
const unsigned int& CMS2::els_HLT_Mu17_Ele8_TrailingLeg_version() {return els_HLT_Mu17_Ele8_TrailingLeg_version_handle.get();}
const unsigned int& CMS2::els_HLT_Mu17_Ele8_version() {return els_HLT_Mu17_Ele8_version_handle.get();}
const unsigned int& CMS2::els_HLT_Mu8_Ele17_version() {return els_HLT_Mu8_Ele17_version_handle.get();}
const unsigned int& CMS2::evt_nels() {return evt_nels_handle.get();}
const unsigned int& CMS2::evt_detectorStatus() {return evt_detectorStatus_handle.get();}
const unsigned int& CMS2::evt_event() {return evt_event_handle.get();}
const unsigned int& CMS2::evt_lumiBlock() {return evt_lumiBlock_handle.get();}
const unsigned int& CMS2::evt_run() {return evt_run_handle.get();}
const unsigned int& CMS2::genps_flavorHistoryFilterResult() {return genps_flavorHistoryFilterResult_handle.get();}
const unsigned int& CMS2::evt_ngenjets() {return evt_ngenjets_handle.get();}
const unsigned int& CMS2::genps_signalProcessID() {return genps_signalProcessID_handle.get();}
const unsigned int& CMS2::evt_njets() {return evt_njets_handle.get();}
const unsigned int& CMS2::l1_bits1() {return l1_bits1_handle.get();}
const unsigned int& CMS2::l1_bits2() {return l1_bits2_handle.get();}
const unsigned int& CMS2::l1_bits3() {return l1_bits3_handle.get();}
const unsigned int& CMS2::l1_bits4() {return l1_bits4_handle.get();}
const unsigned int& CMS2::l1_techbits1() {return l1_techbits1_handle.get();}
const unsigned int& CMS2::l1_techbits2() {return l1_techbits2_handle.get();}
const unsigned int& CMS2::ls_lsNumber() {return ls_lsNumber_handle.get();}
const unsigned int& CMS2::ls_numOrbit() {return ls_numOrbit_handle.get();}
const unsigned int& CMS2::ls_startOrbit() {return ls_startOrbit_handle.get();}
const unsigned int& CMS2::mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_version() {return mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_version_handle.get();}
const unsigned int& CMS2::mus_HLT_IsoMu24_eta2p1_version() {return mus_HLT_IsoMu24_eta2p1_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu17_Ele8_LeadingLeg_version() {return mus_HLT_Mu17_Ele8_LeadingLeg_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu17_Ele8_version() {return mus_HLT_Mu17_Ele8_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_version() {return mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu17_Mu8_LeadingLeg_version() {return mus_HLT_Mu17_Mu8_LeadingLeg_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu17_Mu8_TrailingLeg_version() {return mus_HLT_Mu17_Mu8_TrailingLeg_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu17_Mu8_version() {return mus_HLT_Mu17_Mu8_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu17_TkMu8_LeadingLeg_version() {return mus_HLT_Mu17_TkMu8_LeadingLeg_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_version() {return mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu17_TkMu8_TrailingLeg_version() {return mus_HLT_Mu17_TkMu8_TrailingLeg_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu17_TkMu8_version() {return mus_HLT_Mu17_TkMu8_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu8_Ele17_TrailingLeg_version() {return mus_HLT_Mu8_Ele17_TrailingLeg_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu8_Ele17_version() {return mus_HLT_Mu8_Ele17_version_handle.get();}
const unsigned int& CMS2::evt_nphotons() {return evt_nphotons_handle.get();}
const unsigned int& CMS2::evt_ecalRecoStatus() {return evt_ecalRecoStatus_handle.get();}
const unsigned int& CMS2::evt_nscs() {return evt_nscs_handle.get();}
const unsigned int& CMS2::evt_ntrkjets() {return evt_ntrkjets_handle.get();}
const unsigned int& CMS2::evt_nvtxs() {return evt_nvtxs_handle.get();}
const unsigned int& CMS2::evt_nbsvtxs() {return evt_nbsvtxs_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele17_Ele8() {return els_HLT_Ele17_Ele8_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele17_Ele8_L1sL1DoubleEG137() {return els_HLT_Ele17_Ele8_L1sL1DoubleEG137_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele17_Ele8_LeadingLeg() {return els_HLT_Ele17_Ele8_LeadingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele17_Ele8_Mass50_LeadingLeg() {return els_HLT_Ele17_Ele8_Mass50_LeadingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele17_Ele8_Mass50_TrailingLeg() {return els_HLT_Ele17_Ele8_Mass50_TrailingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele17_Ele8_TrailingLeg() {return els_HLT_Ele17_Ele8_TrailingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele20_SC4_Mass50_LeadingLeg() {return els_HLT_Ele20_SC4_Mass50_LeadingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele20_SC4_Mass50_TrailingLeg() {return els_HLT_Ele20_SC4_Mass50_TrailingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele27_WP80() {return els_HLT_Ele27_WP80_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22() {return els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele32_SC17_Mass50_LeadingLeg() {return els_HLT_Ele32_SC17_Mass50_LeadingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele32_SC17_Mass50_TrailingLeg() {return els_HLT_Ele32_SC17_Mass50_TrailingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Mu17_Ele8() {return els_HLT_Mu17_Ele8_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Mu17_Ele8_TrailingLeg() {return els_HLT_Mu17_Ele8_TrailingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Mu8_Ele17() {return els_HLT_Mu8_Ele17_handle.get();}
const std::vector<unsigned int>& CMS2::els_id2012ext_loose() {return els_id2012ext_loose_handle.get();}
const std::vector<unsigned int>& CMS2::els_id2012ext_medium() {return els_id2012ext_medium_handle.get();}
const std::vector<unsigned int>& CMS2::els_id2012ext_tight() {return els_id2012ext_tight_handle.get();}
const std::vector<unsigned int>& CMS2::els_id2012ext_veto() {return els_id2012ext_veto_handle.get();}
const std::vector<unsigned int>& CMS2::els_id2012_loose() {return els_id2012_loose_handle.get();}
const std::vector<unsigned int>& CMS2::els_id2012_medium() {return els_id2012_medium_handle.get();}
const std::vector<unsigned int>& CMS2::els_id2012_tight() {return els_id2012_tight_handle.get();}
const std::vector<unsigned int>& CMS2::els_id2012_veto() {return els_id2012_veto_handle.get();}
const std::vector<unsigned int>& CMS2::hlt_prescales() {return hlt_prescales_handle.get();}
const std::vector<unsigned int>& CMS2::l1_prescales() {return l1_prescales_handle.get();}
const std::vector<unsigned int>& CMS2::l1_techtrigprescales() {return l1_techtrigprescales_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_IsoMu24_eta2p1() {return mus_HLT_IsoMu24_eta2p1_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1() {return mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu17_Ele8() {return mus_HLT_Mu17_Ele8_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu17_Ele8_LeadingLeg() {return mus_HLT_Mu17_Ele8_LeadingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu17_Mu8() {return mus_HLT_Mu17_Mu8_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen() {return mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu17_Mu8_LeadingLeg() {return mus_HLT_Mu17_Mu8_LeadingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu17_Mu8_TrailingLeg() {return mus_HLT_Mu17_Mu8_TrailingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu17_TkMu8() {return mus_HLT_Mu17_TkMu8_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu17_TkMu8_LeadingLeg() {return mus_HLT_Mu17_TkMu8_LeadingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu17_TkMu8_TrailingLeg() {return mus_HLT_Mu17_TkMu8_TrailingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered() {return mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu8_Ele17() {return mus_HLT_Mu8_Ele17_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu8_Ele17_TrailingLeg() {return mus_HLT_Mu8_Ele17_TrailingLeg_handle.get();}
const unsigned long long& CMS2::evt_timestamp() {return evt_timestamp_handle.get();}
const int& CMS2::evt_nEvts() {return evt_nEvts_handle.get();}
const float& CMS2::evt_filt_eff() {return evt_filt_eff_handle.get();}


// trigger methods:
bool CMS2::passHLTTrigger(const TString& trigName)
{
    int trigIndx;
    std::vector<TString>::const_iterator begin_it = hlt_trigNames().begin();
    std::vector<TString>::const_iterator end_it = hlt_trigNames().end();
    std::vector<TString>::const_iterator found_it = find(begin_it, end_it, trigName);
    if(found_it != end_it)
    {
        trigIndx = found_it - begin_it;
    }
    else
    {
        std::cout << "Cannot find Trigger " << trigName << std::endl; 
        return false;
    }
    return hlt_bits().TestBitNumber(trigIndx);
}

bool CMS2::passL1Trigger(const TString& trigName)
{
    int trigIndx;
    std::vector<TString>::const_iterator begin_it = l1_trigNames().begin();
    std::vector<TString>::const_iterator end_it = l1_trigNames().end();
    std::vector<TString>::const_iterator found_it = find(begin_it, end_it, trigName);
    if(found_it != end_it)
    {
        trigIndx = found_it - begin_it;
    }
    else 
    {
        std::cout << "Cannot find Trigger " << trigName << std::endl; 
        return false;
    }

    if (trigIndx <= 31)
    {
        unsigned int bitmask = 1;
        bitmask <<= trigIndx;
        return l1_bits1() & bitmask;
    }
    if (trigIndx >= 32 && trigIndx <= 63)
    {
        unsigned int bitmask = 1;
        bitmask <<= (trigIndx - 32); 
        return l1_bits2() & bitmask;
    }
    if (trigIndx >= 64 && trigIndx <= 95)
    {
        unsigned int bitmask = 1;
        bitmask <<= (trigIndx - 64); 
        return l1_bits3() & bitmask;
    }
    if (trigIndx >= 96 && trigIndx <= 127) 
    {
        unsigned int bitmask = 1;
        bitmask <<= (trigIndx - 96); 
        return l1_bits4() & bitmask;
    }
    return false;
}


/*static*/ void CMS2::progress(const int nEventsTotal, const int nEventsChain)
{
    int period = 1000;
    if (nEventsTotal%1000 == 0)
    {
        // xterm magic from L. Vacavant and A. Cerri
        if (isatty(1))
        {
            if ((nEventsChain - nEventsTotal) > period)
            {
                float frac = (float)nEventsTotal/(nEventsChain*0.01);
                printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%\033[0m\033[32m <---\033[0m\015", frac);
                fflush(stdout);
            }
            else
            {
                printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%\033[0m\033[32m <---\033[0m\015", 100.0);
                std::cout << std::endl;
            }
        }
    }
}

namespace tas
{
    bool passHLTTrigger(const TString& trigName) {return cms2.passHLTTrigger(trigName);}
	bool passL1Trigger(const TString& trigName) {return cms2.passL1Trigger(trigName);}

    const TBits& hlt_bits() {return cms2.hlt_bits();}
    const std::vector<TString>& evt_CMS2tag() {return cms2.evt_CMS2tag();}
    const std::vector<TString>& evt_dataset() {return cms2.evt_dataset();}
    const std::vector<TString>& hlt_trigNames() {return cms2.hlt_trigNames();}
    const std::vector<TString>& l1_techtrigNames() {return cms2.l1_techtrigNames();}
    const std::vector<TString>& l1_trigNames() {return cms2.l1_trigNames();}
    const std::vector<TString>& evt_errCategory() {return cms2.evt_errCategory();}
    const std::vector<TString>& evt_errModule() {return cms2.evt_errModule();}
    const std::vector<TString>& evt_errSeverity() {return cms2.evt_errSeverity();}
    const std::vector<TString>& sparm_comment() {return cms2.sparm_comment();}
    const std::vector<TString>& sparm_names() {return cms2.sparm_names();}
    const bool& evt_eventHasHalo() {return cms2.evt_eventHasHalo();}
    const bool& hcalnoise_HasBadRBXTS4TS5() {return cms2.hcalnoise_HasBadRBXTS4TS5();}
    const bool& ls_isValid() {return cms2.ls_isValid();}
    const bool& filt_ecalBE() {return cms2.filt_ecalBE();}
    const bool& filt_ecalDR() {return cms2.filt_ecalDR();}
    const bool& filt_ecalLaser() {return cms2.filt_ecalLaser();}
    const bool& filt_ecalTP() {return cms2.filt_ecalTP();}
    const bool& filt_eeBadSc() {return cms2.filt_eeBadSc();}
    const bool& filt_greedyMuon() {return cms2.filt_greedyMuon();}
    const bool& filt_hcalLaser() {return cms2.filt_hcalLaser();}
    const bool& filt_inconsistentMuon() {return cms2.filt_inconsistentMuon();}
    const bool& filt_jetIDFailure() {return cms2.filt_jetIDFailure();}
    const bool& filt_multiEvent() {return cms2.filt_multiEvent();}
    const bool& filt_trackingFailure() {return cms2.filt_trackingFailure();}
    const bool& evt_hbheFilter() {return cms2.evt_hbheFilter();}
    const std::vector<bool>& els_conv_vtx_flag() {return cms2.els_conv_vtx_flag();}
    const std::vector<bool>& els_passingMvaPreselection() {return cms2.els_passingMvaPreselection();}
    const std::vector<bool>& els_passingPflowPreselection() {return cms2.els_passingPflowPreselection();}
    const std::vector<bool>& mus_isRPCMuon() {return cms2.mus_isRPCMuon();}
    const std::vector<bool>& mus_tightMatch() {return cms2.mus_tightMatch();}
    const std::vector<bool>& mus_updatedSta() {return cms2.mus_updatedSta();}
    const std::vector<bool>& pfcands_isMuIso() {return cms2.pfcands_isMuIso();}
    const std::vector<bool>& photons_haspixelSeed() {return cms2.photons_haspixelSeed();}
    const std::vector<double>& jets_closestElectron_DR() {return cms2.jets_closestElectron_DR();}
    const std::vector<double>& jets_closestMuon_DR() {return cms2.jets_closestMuon_DR();}
    const float& evt_bs_Xwidth() {return cms2.evt_bs_Xwidth();}
    const float& evt_bs_XwidthErr() {return cms2.evt_bs_XwidthErr();}
    const float& evt_bs_Ywidth() {return cms2.evt_bs_Ywidth();}
    const float& evt_bs_YwidthErr() {return cms2.evt_bs_YwidthErr();}
    const float& evt_bs_dxdz() {return cms2.evt_bs_dxdz();}
    const float& evt_bs_dxdzErr() {return cms2.evt_bs_dxdzErr();}
    const float& evt_bs_dydz() {return cms2.evt_bs_dydz();}
    const float& evt_bs_dydzErr() {return cms2.evt_bs_dydzErr();}
    const float& evt_bs_sigmaZ() {return cms2.evt_bs_sigmaZ();}
    const float& evt_bs_sigmaZErr() {return cms2.evt_bs_sigmaZErr();}
    const float& evt_bs_xErr() {return cms2.evt_bs_xErr();}
    const float& evt_bs_yErr() {return cms2.evt_bs_yErr();}
    const float& evt_bs_zErr() {return cms2.evt_bs_zErr();}
    const float& evt_bField() {return cms2.evt_bField();}
    const float& evt_rho() {return cms2.evt_rho();}
    const float& evt_rhoJEC() {return cms2.evt_rhoJEC();}
    const float& evt_fixgrid_all_rho() {return cms2.evt_fixgrid_all_rho();}
    const float& evt_fixgridfastjet_all_rho() {return cms2.evt_fixgridfastjet_all_rho();}
    const float& evt_kfactor() {return cms2.evt_kfactor();}
    const float& evt_scale1fb() {return cms2.evt_scale1fb();}
    const float& evt_xsec_excl() {return cms2.evt_xsec_excl();}
    const float& evt_xsec_incl() {return cms2.evt_xsec_incl();}
    const float& gen_met() {return cms2.gen_met();}
    const float& gen_metPhi() {return cms2.gen_metPhi();}
    const float& genps_alphaQCD() {return cms2.genps_alphaQCD();}
    const float& genps_pthat() {return cms2.genps_pthat();}
    const float& genps_qScale() {return cms2.genps_qScale();}
    const float& genps_weight() {return cms2.genps_weight();}
    const float& gen_sumEt() {return cms2.gen_sumEt();}
    const float& hcalnoise_GetRecHitEnergy() {return cms2.hcalnoise_GetRecHitEnergy();}
    const float& hcalnoise_GetRecHitEnergy15() {return cms2.hcalnoise_GetRecHitEnergy15();}
    const float& hcalnoise_GetTotalCalibCharge() {return cms2.hcalnoise_GetTotalCalibCharge();}
    const float& hcalnoise_TS4TS5NoiseSumE() {return cms2.hcalnoise_TS4TS5NoiseSumE();}
    const float& hcalnoise_TS4TS5NoiseSumEt() {return cms2.hcalnoise_TS4TS5NoiseSumEt();}
    const float& hcalnoise_eventChargeFraction() {return cms2.hcalnoise_eventChargeFraction();}
    const float& hcalnoise_eventEMEnergy() {return cms2.hcalnoise_eventEMEnergy();}
    const float& hcalnoise_eventEMFraction() {return cms2.hcalnoise_eventEMFraction();}
    const float& hcalnoise_eventHadEnergy() {return cms2.hcalnoise_eventHadEnergy();}
    const float& hcalnoise_eventTrackEnergy() {return cms2.hcalnoise_eventTrackEnergy();}
    const float& hcalnoise_flatNoiseSumE() {return cms2.hcalnoise_flatNoiseSumE();}
    const float& hcalnoise_flatNoiseSumEt() {return cms2.hcalnoise_flatNoiseSumEt();}
    const float& hcalnoise_isolatedNoiseSumE() {return cms2.hcalnoise_isolatedNoiseSumE();}
    const float& hcalnoise_isolatedNoiseSumEt() {return cms2.hcalnoise_isolatedNoiseSumEt();}
    const float& hcalnoise_max10GeVHitTime() {return cms2.hcalnoise_max10GeVHitTime();}
    const float& hcalnoise_max25GeVHitTime() {return cms2.hcalnoise_max25GeVHitTime();}
    const float& hcalnoise_maxE10TS() {return cms2.hcalnoise_maxE10TS();}
    const float& hcalnoise_maxE2Over10TS() {return cms2.hcalnoise_maxE2Over10TS();}
    const float& hcalnoise_maxE2TS() {return cms2.hcalnoise_maxE2TS();}
    const float& hcalnoise_min10GeVHitTime() {return cms2.hcalnoise_min10GeVHitTime();}
    const float& hcalnoise_min25GeVHitTime() {return cms2.hcalnoise_min25GeVHitTime();}
    const float& hcalnoise_minE10TS() {return cms2.hcalnoise_minE10TS();}
    const float& hcalnoise_minE2Over10TS() {return cms2.hcalnoise_minE2Over10TS();}
    const float& hcalnoise_minE2TS() {return cms2.hcalnoise_minE2TS();}
    const float& hcalnoise_minHPDEMF() {return cms2.hcalnoise_minHPDEMF();}
    const float& hcalnoise_minRBXEMF() {return cms2.hcalnoise_minRBXEMF();}
    const float& hcalnoise_rms10GeVHitTime() {return cms2.hcalnoise_rms10GeVHitTime();}
    const float& hcalnoise_rms25GeVHitTime() {return cms2.hcalnoise_rms25GeVHitTime();}
    const float& hcalnoise_spikeNoiseSumE() {return cms2.hcalnoise_spikeNoiseSumE();}
    const float& hcalnoise_spikeNoiseSumEt() {return cms2.hcalnoise_spikeNoiseSumEt();}
    const float& hcalnoise_triangleNoiseSumE() {return cms2.hcalnoise_triangleNoiseSumE();}
    const float& hcalnoise_triangleNoiseSumEt() {return cms2.hcalnoise_triangleNoiseSumEt();}
    const float& evt_kt6calo_central_rho() {return cms2.evt_kt6calo_central_rho();}
    const float& evt_kt6calo_muhlt_rho() {return cms2.evt_kt6calo_muhlt_rho();}
    const float& evt_kt6calo_rho() {return cms2.evt_kt6calo_rho();}
    const float& evt_kt6pf_ctrChargedPU_rho() {return cms2.evt_kt6pf_ctrChargedPU_rho();}
    const float& evt_kt6pf_ctrNeutral_rho() {return cms2.evt_kt6pf_ctrNeutral_rho();}
    const float& evt_kt6pf_ctrNeutralTight_rho() {return cms2.evt_kt6pf_ctrNeutralTight_rho();}
    const float& evt_kt6pf_foregiso_rho() {return cms2.evt_kt6pf_foregiso_rho();}
    const float& l1_met_etTot() {return cms2.l1_met_etTot();}
    const float& l1_met_met() {return cms2.l1_met_met();}
    const float& l1_mht_htTot() {return cms2.l1_mht_htTot();}
    const float& l1_mht_mht() {return cms2.l1_mht_mht();}
    const float& ls_avgInsDelLumi() {return cms2.ls_avgInsDelLumi();}
    const float& ls_avgInsDelLumiErr() {return cms2.ls_avgInsDelLumiErr();}
    const float& ls_avgInsRecLumi() {return cms2.ls_avgInsRecLumi();}
    const float& ls_avgInsRecLumiErr() {return cms2.ls_avgInsRecLumiErr();}
    const float& ls_deadFrac() {return cms2.ls_deadFrac();}
    const float& ls_intgDelLumi() {return cms2.ls_intgDelLumi();}
    const float& ls_intgRecLumi() {return cms2.ls_intgRecLumi();}
    const float& ls_lumiSectionLength() {return cms2.ls_lumiSectionLength();}
    const float& evt_ecalendcapm_met() {return cms2.evt_ecalendcapm_met();}
    const float& evt_ecalendcapm_metPhi() {return cms2.evt_ecalendcapm_metPhi();}
    const float& evt_ecalendcapp_met() {return cms2.evt_ecalendcapp_met();}
    const float& evt_ecalendcapp_metPhi() {return cms2.evt_ecalendcapp_metPhi();}
    const float& evt_ecalmet() {return cms2.evt_ecalmet();}
    const float& evt_ecalmetPhi() {return cms2.evt_ecalmetPhi();}
    const float& evt_endcapm_met() {return cms2.evt_endcapm_met();}
    const float& evt_endcapm_metPhi() {return cms2.evt_endcapm_metPhi();}
    const float& evt_endcapp_met() {return cms2.evt_endcapp_met();}
    const float& evt_endcapp_metPhi() {return cms2.evt_endcapp_metPhi();}
    const float& evt_hcalendcapm_met() {return cms2.evt_hcalendcapm_met();}
    const float& evt_hcalendcapm_metPhi() {return cms2.evt_hcalendcapm_metPhi();}
    const float& evt_hcalendcapp_met() {return cms2.evt_hcalendcapp_met();}
    const float& evt_hcalendcapp_metPhi() {return cms2.evt_hcalendcapp_metPhi();}
    const float& evt_hcalmet() {return cms2.evt_hcalmet();}
    const float& evt_hcalmetPhi() {return cms2.evt_hcalmetPhi();}
    const float& evt_met() {return cms2.evt_met();}
    const float& evt_met_EtGt3() {return cms2.evt_met_EtGt3();}
    const float& evt_metHO() {return cms2.evt_metHO();}
    const float& evt_metHOPhi() {return cms2.evt_metHOPhi();}
    const float& evt_metHOSig() {return cms2.evt_metHOSig();}
    const float& evt_metMuonCorr() {return cms2.evt_metMuonCorr();}
    const float& evt_metMuonCorrPhi() {return cms2.evt_metMuonCorrPhi();}
    const float& evt_metMuonCorrSig() {return cms2.evt_metMuonCorrSig();}
    const float& evt_metMuonJESCorr() {return cms2.evt_metMuonJESCorr();}
    const float& evt_metMuonJESCorrPhi() {return cms2.evt_metMuonJESCorrPhi();}
    const float& evt_metMuonJESCorrSig() {return cms2.evt_metMuonJESCorrSig();}
    const float& evt_metNoHF() {return cms2.evt_metNoHF();}
    const float& evt_metNoHFHO() {return cms2.evt_metNoHFHO();}
    const float& evt_metNoHFHOPhi() {return cms2.evt_metNoHFHOPhi();}
    const float& evt_metNoHFHOSig() {return cms2.evt_metNoHFHOSig();}
    const float& evt_metNoHFPhi() {return cms2.evt_metNoHFPhi();}
    const float& evt_metNoHFSig() {return cms2.evt_metNoHFSig();}
    const float& evt_metOpt() {return cms2.evt_metOpt();}
    const float& evt_metOptHO() {return cms2.evt_metOptHO();}
    const float& evt_metOptHOPhi() {return cms2.evt_metOptHOPhi();}
    const float& evt_metOptHOSig() {return cms2.evt_metOptHOSig();}
    const float& evt_metOptNoHF() {return cms2.evt_metOptNoHF();}
    const float& evt_metOptNoHFHO() {return cms2.evt_metOptNoHFHO();}
    const float& evt_metOptNoHFHOPhi() {return cms2.evt_metOptNoHFHOPhi();}
    const float& evt_metOptNoHFHOSig() {return cms2.evt_metOptNoHFHOSig();}
    const float& evt_metOptNoHFPhi() {return cms2.evt_metOptNoHFPhi();}
    const float& evt_metOptNoHFSig() {return cms2.evt_metOptNoHFSig();}
    const float& evt_metOptPhi() {return cms2.evt_metOptPhi();}
    const float& evt_metOptSig() {return cms2.evt_metOptSig();}
    const float& evt_metPhi() {return cms2.evt_metPhi();}
    const float& evt_metPhi_EtGt3() {return cms2.evt_metPhi_EtGt3();}
    const float& evt_metSig() {return cms2.evt_metSig();}
    const float& evt_sumet() {return cms2.evt_sumet();}
    const float& evt_sumet_EtGt3() {return cms2.evt_sumet_EtGt3();}
    const float& evt_sumetHO() {return cms2.evt_sumetHO();}
    const float& evt_sumetMuonCorr() {return cms2.evt_sumetMuonCorr();}
    const float& evt_sumetMuonJESCorr() {return cms2.evt_sumetMuonJESCorr();}
    const float& evt_sumetNoHF() {return cms2.evt_sumetNoHF();}
    const float& evt_sumetNoHFHO() {return cms2.evt_sumetNoHFHO();}
    const float& evt_sumetOpt() {return cms2.evt_sumetOpt();}
    const float& evt_sumetOptHO() {return cms2.evt_sumetOptHO();}
    const float& evt_sumetOptNoHF() {return cms2.evt_sumetOptNoHF();}
    const float& evt_sumetOptNoHFHO() {return cms2.evt_sumetOptNoHFHO();}
    const float& pdfinfo_pdf1() {return cms2.pdfinfo_pdf1();}
    const float& pdfinfo_pdf2() {return cms2.pdfinfo_pdf2();}
    const float& pdfinfo_scale() {return cms2.pdfinfo_scale();}
    const float& pdfinfo_x1() {return cms2.pdfinfo_x1();}
    const float& pdfinfo_x2() {return cms2.pdfinfo_x2();}
    const float& evt_fixgrid_rho_all() {return cms2.evt_fixgrid_rho_all();}
    const float& evt_fixgrid_rho_ctr() {return cms2.evt_fixgrid_rho_ctr();}
    const float& evt_fixgrid_rho_fwd() {return cms2.evt_fixgrid_rho_fwd();}
    const float& evt_pfmet() {return cms2.evt_pfmet();}
    const float& evt_pfmetPhi() {return cms2.evt_pfmetPhi();}
    const float& evt_pfmetPhi_type1cor() {return cms2.evt_pfmetPhi_type1cor();}
    const float& evt_pfmetSig() {return cms2.evt_pfmetSig();}
    const float& evt_pfmetSignificance() {return cms2.evt_pfmetSignificance();}
    const float& evt_pfmet_type1cor() {return cms2.evt_pfmet_type1cor();}
    const float& evt_pfsumet() {return cms2.evt_pfsumet();}
    const float& sparm_filterEfficiency() {return cms2.sparm_filterEfficiency();}
    const float& sparm_pdfScale() {return cms2.sparm_pdfScale();}
    const float& sparm_pdfWeight1() {return cms2.sparm_pdfWeight1();}
    const float& sparm_pdfWeight2() {return cms2.sparm_pdfWeight2();}
    const float& sparm_weight() {return cms2.sparm_weight();}
    const float& sparm_xsec() {return cms2.sparm_xsec();}
    const float& evt_pf_tcmet() {return cms2.evt_pf_tcmet();}
    const float& evt_pf_tcmetPhi() {return cms2.evt_pf_tcmetPhi();}
    const float& evt_pf_tcmetSig() {return cms2.evt_pf_tcmetSig();}
    const float& evt_pf_tcsumet() {return cms2.evt_pf_tcsumet();}
    const float& evt_tcmet() {return cms2.evt_tcmet();}
    const float& evt_tcmetPhi() {return cms2.evt_tcmetPhi();}
    const float& evt_tcmetSig() {return cms2.evt_tcmetSig();}
    const float& evt_tcsumet() {return cms2.evt_tcsumet();}
    const float& evt_ww_rho_act() {return cms2.evt_ww_rho_act();}
    const float& evt_ww_rho() {return cms2.evt_ww_rho();}
    const float& evt_ww_rho_rnd() {return cms2.evt_ww_rho_rnd();}
    const float& evt_ww_rho_vor() {return cms2.evt_ww_rho_vor();}
    const LorentzVector & evt_bsp4() {return cms2.evt_bsp4();}
    const LorentzVector & l1_met_p4() {return cms2.l1_met_p4();}
    const LorentzVector & l1_mht_p4() {return cms2.l1_mht_p4();}
    const std::vector<LorentzVector >& els_mc_motherp4() {return cms2.els_mc_motherp4();}
    const std::vector<LorentzVector >& els_mc_p4() {return cms2.els_mc_p4();}
    const std::vector<LorentzVector >& jets_mc_gp_p4() {return cms2.jets_mc_gp_p4();}
    const std::vector<LorentzVector >& jets_mc_motherp4() {return cms2.jets_mc_motherp4();}
    const std::vector<LorentzVector >& jets_mc_p4() {return cms2.jets_mc_p4();}
    const std::vector<LorentzVector >& mus_mc_motherp4() {return cms2.mus_mc_motherp4();}
    const std::vector<LorentzVector >& mus_mc_p4() {return cms2.mus_mc_p4();}
    const std::vector<LorentzVector >& pfjets_mc_gp_p4() {return cms2.pfjets_mc_gp_p4();}
    const std::vector<LorentzVector >& pfjets_mc_motherp4() {return cms2.pfjets_mc_motherp4();}
    const std::vector<LorentzVector >& pfjets_mc_p4() {return cms2.pfjets_mc_p4();}
    const std::vector<LorentzVector >& photons_mc_motherp4() {return cms2.photons_mc_motherp4();}
    const std::vector<LorentzVector >& photons_mc_p4() {return cms2.photons_mc_p4();}
    const std::vector<LorentzVector >& trk_mcp4() {return cms2.trk_mcp4();}
    const std::vector<LorentzVector >& els_conv_pos_p4() {return cms2.els_conv_pos_p4();}
    const std::vector<LorentzVector >& els_inner_position() {return cms2.els_inner_position();}
    const std::vector<LorentzVector >& els_outer_position() {return cms2.els_outer_position();}
    const std::vector<LorentzVector >& els_p4() {return cms2.els_p4();}
    const std::vector<LorentzVector >& els_p4In() {return cms2.els_p4In();}
    const std::vector<LorentzVector >& els_p4Out() {return cms2.els_p4Out();}
    const std::vector<LorentzVector >& els_trk_p4() {return cms2.els_trk_p4();}
    const std::vector<LorentzVector >& els_vertex_p4() {return cms2.els_vertex_p4();}
    const std::vector<LorentzVector >& genjets_p4() {return cms2.genjets_p4();}
    const std::vector<LorentzVector >& genps_p4() {return cms2.genps_p4();}
    const std::vector<LorentzVector >& genps_prod_vtx() {return cms2.genps_prod_vtx();}
    const std::vector<LorentzVector >& gsftrks_inner_position() {return cms2.gsftrks_inner_position();}
    const std::vector<LorentzVector >& gsftrks_outer_p4() {return cms2.gsftrks_outer_p4();}
    const std::vector<LorentzVector >& gsftrks_outer_position() {return cms2.gsftrks_outer_position();}
    const std::vector<LorentzVector >& gsftrks_p4() {return cms2.gsftrks_p4();}
    const std::vector<LorentzVector >& gsftrks_vertex_p4() {return cms2.gsftrks_vertex_p4();}
    const std::vector<LorentzVector >& hyp_ll_p4() {return cms2.hyp_ll_p4();}
    const std::vector<LorentzVector >& hyp_ll_trk_p4() {return cms2.hyp_ll_trk_p4();}
    const std::vector<LorentzVector >& hyp_lt_p4() {return cms2.hyp_lt_p4();}
    const std::vector<LorentzVector >& hyp_lt_trk_p4() {return cms2.hyp_lt_trk_p4();}
    const std::vector<LorentzVector >& hyp_p4() {return cms2.hyp_p4();}
    const std::vector<LorentzVector >& hyp_FVFit_p4() {return cms2.hyp_FVFit_p4();}
    const std::vector<LorentzVector >& hyp_FVFit_v4() {return cms2.hyp_FVFit_v4();}
    const std::vector<LorentzVector >& hyp_ll_mc_p4() {return cms2.hyp_ll_mc_p4();}
    const std::vector<LorentzVector >& hyp_lt_mc_p4() {return cms2.hyp_lt_mc_p4();}
    const std::vector<LorentzVector >& jets_p4() {return cms2.jets_p4();}
    const std::vector<LorentzVector >& jets_vertex_p4() {return cms2.jets_vertex_p4();}
    const std::vector<LorentzVector >& l1_emiso_p4() {return cms2.l1_emiso_p4();}
    const std::vector<LorentzVector >& l1_emnoiso_p4() {return cms2.l1_emnoiso_p4();}
    const std::vector<LorentzVector >& l1_jetsc_p4() {return cms2.l1_jetsc_p4();}
    const std::vector<LorentzVector >& l1_jetsf_p4() {return cms2.l1_jetsf_p4();}
    const std::vector<LorentzVector >& l1_jetst_p4() {return cms2.l1_jetst_p4();}
    const std::vector<LorentzVector >& l1_mus_p4() {return cms2.l1_mus_p4();}
    const std::vector<LorentzVector >& mus_ecalpos_p4() {return cms2.mus_ecalpos_p4();}
    const std::vector<LorentzVector >& mus_fitpicky_p4() {return cms2.mus_fitpicky_p4();}
    const std::vector<LorentzVector >& mus_fittev_p4() {return cms2.mus_fittev_p4();}
    const std::vector<LorentzVector >& mus_fittpfms_p4() {return cms2.mus_fittpfms_p4();}
    const std::vector<LorentzVector >& mus_gfit_outerPos_p4() {return cms2.mus_gfit_outerPos_p4();}
    const std::vector<LorentzVector >& mus_gfit_p4() {return cms2.mus_gfit_p4();}
    const std::vector<LorentzVector >& mus_gfit_vertex_p4() {return cms2.mus_gfit_vertex_p4();}
    const std::vector<LorentzVector >& mus_p4() {return cms2.mus_p4();}
    const std::vector<LorentzVector >& mus_pfp4() {return cms2.mus_pfp4();}
    const std::vector<LorentzVector >& mus_pfposAtEcal_p4() {return cms2.mus_pfposAtEcal_p4();}
    const std::vector<LorentzVector >& mus_sta_p4() {return cms2.mus_sta_p4();}
    const std::vector<LorentzVector >& mus_sta_vertex_p4() {return cms2.mus_sta_vertex_p4();}
    const std::vector<LorentzVector >& mus_trk_p4() {return cms2.mus_trk_p4();}
    const std::vector<LorentzVector >& mus_vertex_p4() {return cms2.mus_vertex_p4();}
    const std::vector<LorentzVector >& pfcands_p4() {return cms2.pfcands_p4();}
    const std::vector<LorentzVector >& pfcands_posAtEcal_p4() {return cms2.pfcands_posAtEcal_p4();}
    const std::vector<LorentzVector >& pfels_p4() {return cms2.pfels_p4();}
    const std::vector<LorentzVector >& pfels_posAtEcal_p4() {return cms2.pfels_posAtEcal_p4();}
    const std::vector<LorentzVector >& pfjets_p4() {return cms2.pfjets_p4();}
    const std::vector<LorentzVector >& pfmus_p4() {return cms2.pfmus_p4();}
    const std::vector<LorentzVector >& pfmus_posAtEcal_p4() {return cms2.pfmus_posAtEcal_p4();}
    const std::vector<LorentzVector >& taus_pf_p4() {return cms2.taus_pf_p4();}
    const std::vector<LorentzVector >& photons_p4() {return cms2.photons_p4();}
    const std::vector<LorentzVector >& convs_refitPairMom_p4() {return cms2.convs_refitPairMom_p4();}
    const std::vector<LorentzVector >& convs_vtxpos() {return cms2.convs_vtxpos();}
    const std::vector<LorentzVector >& scs_p4() {return cms2.scs_p4();}
    const std::vector<LorentzVector >& scs_pos_p4() {return cms2.scs_pos_p4();}
    const std::vector<LorentzVector >& scs_vtx_p4() {return cms2.scs_vtx_p4();}
    const std::vector<LorentzVector >& svs_flight() {return cms2.svs_flight();}
    const std::vector<LorentzVector >& svs_mc3_p4() {return cms2.svs_mc3_p4();}
    const std::vector<LorentzVector >& svs_p4() {return cms2.svs_p4();}
    const std::vector<LorentzVector >& svs_position() {return cms2.svs_position();}
    const std::vector<LorentzVector >& svs_refitp4() {return cms2.svs_refitp4();}
    const std::vector<LorentzVector >& trks_inner_position() {return cms2.trks_inner_position();}
    const std::vector<LorentzVector >& trks_outer_p4() {return cms2.trks_outer_p4();}
    const std::vector<LorentzVector >& trks_outer_position() {return cms2.trks_outer_position();}
    const std::vector<LorentzVector >& trks_trk_p4() {return cms2.trks_trk_p4();}
    const std::vector<LorentzVector >& trks_vertex_p4() {return cms2.trks_vertex_p4();}
    const std::vector<LorentzVector >& trkjets_p4() {return cms2.trkjets_p4();}
    const std::vector<LorentzVector >& vtxs_position() {return cms2.vtxs_position();}
    const std::vector<LorentzVector >& bsvtxs_position() {return cms2.bsvtxs_position();}
    const std::vector<std::vector<LorentzVector > >& els_convs_pos_p4() {return cms2.els_convs_pos_p4();}
    const std::vector<std::vector<LorentzVector > >& genps_lepdaughter_p4() {return cms2.genps_lepdaughter_p4();}
    const std::vector<std::vector<LorentzVector > >& hlt_trigObjs_p4() {return cms2.hlt_trigObjs_p4();}
    const std::vector<std::vector<LorentzVector > >& hyp_jets_p4() {return cms2.hyp_jets_p4();}
    const std::vector<std::vector<LorentzVector > >& hyp_other_jets_p4() {return cms2.hyp_other_jets_p4();}
    const std::vector<float>& jpts_combinedSecondaryVertexBJetTag() {return cms2.jpts_combinedSecondaryVertexBJetTag();}
    const std::vector<float>& jpts_combinedSecondaryVertexMVABJetTag() {return cms2.jpts_combinedSecondaryVertexMVABJetTag();}
    const std::vector<float>& jpts_jetBProbabilityBJetTag() {return cms2.jpts_jetBProbabilityBJetTag();}
    const std::vector<float>& jpts_jetProbabilityBJetTag() {return cms2.jpts_jetProbabilityBJetTag();}
    const std::vector<float>& jpts_simpleSecondaryVertexBJetTag() {return cms2.jpts_simpleSecondaryVertexBJetTag();}
    const std::vector<float>& jpts_simpleSecondaryVertexHighEffBJetTag() {return cms2.jpts_simpleSecondaryVertexHighEffBJetTag();}
    const std::vector<float>& jpts_simpleSecondaryVertexHighPurBJetTags() {return cms2.jpts_simpleSecondaryVertexHighPurBJetTags();}
    const std::vector<float>& jpts_softElectronByIP3dBJetTag() {return cms2.jpts_softElectronByIP3dBJetTag();}
    const std::vector<float>& jpts_softElectronByPtBJetTag() {return cms2.jpts_softElectronByPtBJetTag();}
    const std::vector<float>& jpts_softElectronTag() {return cms2.jpts_softElectronTag();}
    const std::vector<float>& jpts_softMuonBJetTag() {return cms2.jpts_softMuonBJetTag();}
    const std::vector<float>& jpts_softMuonByIP3dBJetTag() {return cms2.jpts_softMuonByIP3dBJetTag();}
    const std::vector<float>& jpts_softMuonByPtBJetTag() {return cms2.jpts_softMuonByPtBJetTag();}
    const std::vector<float>& jpts_trackCountingHighEffBJetTag() {return cms2.jpts_trackCountingHighEffBJetTag();}
    const std::vector<float>& jpts_trackCountingHighPurBJetTag() {return cms2.jpts_trackCountingHighPurBJetTag();}
    const std::vector<float>& jets_combinedSecondaryVertexBJetTag() {return cms2.jets_combinedSecondaryVertexBJetTag();}
    const std::vector<float>& jets_combinedSecondaryVertexMVABJetTag() {return cms2.jets_combinedSecondaryVertexMVABJetTag();}
    const std::vector<float>& jets_jetBProbabilityBJetTag() {return cms2.jets_jetBProbabilityBJetTag();}
    const std::vector<float>& jets_jetProbabilityBJetTag() {return cms2.jets_jetProbabilityBJetTag();}
    const std::vector<float>& jets_simpleSecondaryVertexBJetTag() {return cms2.jets_simpleSecondaryVertexBJetTag();}
    const std::vector<float>& jets_simpleSecondaryVertexHighEffBJetTag() {return cms2.jets_simpleSecondaryVertexHighEffBJetTag();}
    const std::vector<float>& jets_simpleSecondaryVertexHighPurBJetTags() {return cms2.jets_simpleSecondaryVertexHighPurBJetTags();}
    const std::vector<float>& jets_softElectronByIP3dBJetTag() {return cms2.jets_softElectronByIP3dBJetTag();}
    const std::vector<float>& jets_softElectronByPtBJetTag() {return cms2.jets_softElectronByPtBJetTag();}
    const std::vector<float>& jets_softElectronTag() {return cms2.jets_softElectronTag();}
    const std::vector<float>& jets_softMuonBJetTag() {return cms2.jets_softMuonBJetTag();}
    const std::vector<float>& jets_softMuonByIP3dBJetTag() {return cms2.jets_softMuonByIP3dBJetTag();}
    const std::vector<float>& jets_softMuonByPtBJetTag() {return cms2.jets_softMuonByPtBJetTag();}
    const std::vector<float>& jets_trackCountingHighEffBJetTag() {return cms2.jets_trackCountingHighEffBJetTag();}
    const std::vector<float>& jets_trackCountingHighPurBJetTag() {return cms2.jets_trackCountingHighPurBJetTag();}
    const std::vector<float>& pfjets_combinedSecondaryVertexBJetTag() {return cms2.pfjets_combinedSecondaryVertexBJetTag();}
    const std::vector<float>& pfjets_combinedSecondaryVertexMVABJetTag() {return cms2.pfjets_combinedSecondaryVertexMVABJetTag();}
    const std::vector<float>& pfjets_jetBProbabilityBJetTag() {return cms2.pfjets_jetBProbabilityBJetTag();}
    const std::vector<float>& pfjets_jetProbabilityBJetTag() {return cms2.pfjets_jetProbabilityBJetTag();}
    const std::vector<float>& pfjets_simpleSecondaryVertexBJetTag() {return cms2.pfjets_simpleSecondaryVertexBJetTag();}
    const std::vector<float>& pfjets_simpleSecondaryVertexHighEffBJetTag() {return cms2.pfjets_simpleSecondaryVertexHighEffBJetTag();}
    const std::vector<float>& pfjets_simpleSecondaryVertexHighPurBJetTags() {return cms2.pfjets_simpleSecondaryVertexHighPurBJetTags();}
    const std::vector<float>& pfjets_softElectronByIP3dBJetTag() {return cms2.pfjets_softElectronByIP3dBJetTag();}
    const std::vector<float>& pfjets_softElectronByPtBJetTag() {return cms2.pfjets_softElectronByPtBJetTag();}
    const std::vector<float>& pfjets_softElectronTag() {return cms2.pfjets_softElectronTag();}
    const std::vector<float>& pfjets_softMuonBJetTag() {return cms2.pfjets_softMuonBJetTag();}
    const std::vector<float>& pfjets_softMuonByIP3dBJetTag() {return cms2.pfjets_softMuonByIP3dBJetTag();}
    const std::vector<float>& pfjets_softMuonByPtBJetTag() {return cms2.pfjets_softMuonByPtBJetTag();}
    const std::vector<float>& pfjets_trackCountingHighEffBJetTag() {return cms2.pfjets_trackCountingHighEffBJetTag();}
    const std::vector<float>& pfjets_trackCountingHighPurBJetTag() {return cms2.pfjets_trackCountingHighPurBJetTag();}
    const std::vector<float>& trkjets_combinedSecondaryVertexBJetTag() {return cms2.trkjets_combinedSecondaryVertexBJetTag();}
    const std::vector<float>& trkjets_combinedSecondaryVertexMVABJetTag() {return cms2.trkjets_combinedSecondaryVertexMVABJetTag();}
    const std::vector<float>& trkjets_jetBProbabilityBJetTag() {return cms2.trkjets_jetBProbabilityBJetTag();}
    const std::vector<float>& trkjets_jetProbabilityBJetTag() {return cms2.trkjets_jetProbabilityBJetTag();}
    const std::vector<float>& trkjets_simpleSecondaryVertexBJetTag() {return cms2.trkjets_simpleSecondaryVertexBJetTag();}
    const std::vector<float>& trkjets_simpleSecondaryVertexHighEffBJetTag() {return cms2.trkjets_simpleSecondaryVertexHighEffBJetTag();}
    const std::vector<float>& trkjets_simpleSecondaryVertexHighPurBJetTags() {return cms2.trkjets_simpleSecondaryVertexHighPurBJetTags();}
    const std::vector<float>& trkjets_softElectronByIP3dBJetTag() {return cms2.trkjets_softElectronByIP3dBJetTag();}
    const std::vector<float>& trkjets_softElectronByPtBJetTag() {return cms2.trkjets_softElectronByPtBJetTag();}
    const std::vector<float>& trkjets_softElectronTag() {return cms2.trkjets_softElectronTag();}
    const std::vector<float>& trkjets_softMuonBJetTag() {return cms2.trkjets_softMuonBJetTag();}
    const std::vector<float>& trkjets_softMuonByIP3dBJetTag() {return cms2.trkjets_softMuonByIP3dBJetTag();}
    const std::vector<float>& trkjets_softMuonByPtBJetTag() {return cms2.trkjets_softMuonByPtBJetTag();}
    const std::vector<float>& trkjets_trackCountingHighEffBJetTag() {return cms2.trkjets_trackCountingHighEffBJetTag();}
    const std::vector<float>& trkjets_trackCountingHighPurBJetTag() {return cms2.trkjets_trackCountingHighPurBJetTag();}
    const std::vector<float>& evt_bs_covMatrix() {return cms2.evt_bs_covMatrix();}
    const std::vector<float>& els_mc3dr() {return cms2.els_mc3dr();}
    const std::vector<float>& els_mcdr() {return cms2.els_mcdr();}
    const std::vector<float>& jets_mc3dr() {return cms2.jets_mc3dr();}
    const std::vector<float>& jets_mcdr() {return cms2.jets_mcdr();}
    const std::vector<float>& jets_mc_emEnergy() {return cms2.jets_mc_emEnergy();}
    const std::vector<float>& jets_mc_gpdr() {return cms2.jets_mc_gpdr();}
    const std::vector<float>& jets_mc_hadEnergy() {return cms2.jets_mc_hadEnergy();}
    const std::vector<float>& jets_mc_invEnergy() {return cms2.jets_mc_invEnergy();}
    const std::vector<float>& jets_mc_otherEnergy() {return cms2.jets_mc_otherEnergy();}
    const std::vector<float>& mus_mc3dr() {return cms2.mus_mc3dr();}
    const std::vector<float>& mus_mcdr() {return cms2.mus_mcdr();}
    const std::vector<float>& pfjets_mc3dr() {return cms2.pfjets_mc3dr();}
    const std::vector<float>& pfjets_mcdr() {return cms2.pfjets_mcdr();}
    const std::vector<float>& pfjets_mc_emEnergy() {return cms2.pfjets_mc_emEnergy();}
    const std::vector<float>& pfjets_mc_gpdr() {return cms2.pfjets_mc_gpdr();}
    const std::vector<float>& pfjets_mc_hadEnergy() {return cms2.pfjets_mc_hadEnergy();}
    const std::vector<float>& pfjets_mc_invEnergy() {return cms2.pfjets_mc_invEnergy();}
    const std::vector<float>& pfjets_mc_otherEnergy() {return cms2.pfjets_mc_otherEnergy();}
    const std::vector<float>& photons_mc3dr() {return cms2.photons_mc3dr();}
    const std::vector<float>& photons_mcdr() {return cms2.photons_mcdr();}
    const std::vector<float>& trk_mc3dr() {return cms2.trk_mc3dr();}
    const std::vector<float>& trk_mcdr() {return cms2.trk_mcdr();}
    const std::vector<float>& els_ecalJuraIso() {return cms2.els_ecalJuraIso();}
    const std::vector<float>& els_ecalJuraTowerIso() {return cms2.els_ecalJuraTowerIso();}
    const std::vector<float>& els_hcalConeIso() {return cms2.els_hcalConeIso();}
    const std::vector<float>& els_tkJuraIso() {return cms2.els_tkJuraIso();}
    const std::vector<float>& els_jetdr() {return cms2.els_jetdr();}
    const std::vector<float>& els_musdr() {return cms2.els_musdr();}
    const std::vector<float>& els_isoR03_chpf_radial() {return cms2.els_isoR03_chpf_radial();}
    const std::vector<float>& els_isoR03_chpf_radialTight() {return cms2.els_isoR03_chpf_radialTight();}
    const std::vector<float>& els_isoR03_chpf_radialTight_bv() {return cms2.els_isoR03_chpf_radialTight_bv();}
    const std::vector<float>& els_isoR03_chpf_radial_bv() {return cms2.els_isoR03_chpf_radial_bv();}
    const std::vector<float>& els_isoR03_empf_radial() {return cms2.els_isoR03_empf_radial();}
    const std::vector<float>& els_isoR03_empf_radialTight() {return cms2.els_isoR03_empf_radialTight();}
    const std::vector<float>& els_isoR03_empf_radialTight_bv() {return cms2.els_isoR03_empf_radialTight_bv();}
    const std::vector<float>& els_isoR03_empf_radial_bv() {return cms2.els_isoR03_empf_radial_bv();}
    const std::vector<float>& els_isoR03_nhpf_radial() {return cms2.els_isoR03_nhpf_radial();}
    const std::vector<float>& els_isoR03_nhpf_radialTight() {return cms2.els_isoR03_nhpf_radialTight();}
    const std::vector<float>& els_isoR03_nhpf_radialTight_bv() {return cms2.els_isoR03_nhpf_radialTight_bv();}
    const std::vector<float>& els_isoR03_nhpf_radial_bv() {return cms2.els_isoR03_nhpf_radial_bv();}
    const std::vector<float>& els_isoR03_pf2012n0p5_ch() {return cms2.els_isoR03_pf2012n0p5_ch();}
    const std::vector<float>& els_isoR03_pf2012n0p5_em() {return cms2.els_isoR03_pf2012n0p5_em();}
    const std::vector<float>& els_isoR03_pf2012n0p5_nh() {return cms2.els_isoR03_pf2012n0p5_nh();}
    const std::vector<float>& els_isoR03_pf_radial() {return cms2.els_isoR03_pf_radial();}
    const std::vector<float>& els_isoR03_pf_radialTight() {return cms2.els_isoR03_pf_radialTight();}
    const std::vector<float>& els_isoR03_pf_radialTight_bv() {return cms2.els_isoR03_pf_radialTight_bv();}
    const std::vector<float>& els_isoR03_pf_radial_bv() {return cms2.els_isoR03_pf_radial_bv();}
    const std::vector<float>& els_chi2() {return cms2.els_chi2();}
    const std::vector<float>& els_ckf_chi2() {return cms2.els_ckf_chi2();}
    const std::vector<float>& els_ckf_ndof() {return cms2.els_ckf_ndof();}
    const std::vector<float>& els_conv_dcot() {return cms2.els_conv_dcot();}
    const std::vector<float>& els_conv_dist() {return cms2.els_conv_dist();}
    const std::vector<float>& els_conv_old_dcot() {return cms2.els_conv_old_dcot();}
    const std::vector<float>& els_conv_old_dist() {return cms2.els_conv_old_dist();}
    const std::vector<float>& els_conv_old_radius() {return cms2.els_conv_old_radius();}
    const std::vector<float>& els_conv_radius() {return cms2.els_conv_radius();}
    const std::vector<float>& els_d0() {return cms2.els_d0();}
    const std::vector<float>& els_d0Err() {return cms2.els_d0Err();}
    const std::vector<float>& els_d0corr() {return cms2.els_d0corr();}
    const std::vector<float>& els_dEtaIn() {return cms2.els_dEtaIn();}
    const std::vector<float>& els_dEtaOut() {return cms2.els_dEtaOut();}
    const std::vector<float>& els_dPhiIn() {return cms2.els_dPhiIn();}
    const std::vector<float>& els_dPhiInPhiOut() {return cms2.els_dPhiInPhiOut();}
    const std::vector<float>& els_dPhiOut() {return cms2.els_dPhiOut();}
    const std::vector<float>& els_deltaEtaEleClusterTrackAtCalo() {return cms2.els_deltaEtaEleClusterTrackAtCalo();}
    const std::vector<float>& els_deltaPhiEleClusterTrackAtCalo() {return cms2.els_deltaPhiEleClusterTrackAtCalo();}
    const std::vector<float>& els_e1x5() {return cms2.els_e1x5();}
    const std::vector<float>& els_e2x5Max() {return cms2.els_e2x5Max();}
    const std::vector<float>& els_e3x3() {return cms2.els_e3x3();}
    const std::vector<float>& els_e5x5() {return cms2.els_e5x5();}
    const std::vector<float>& els_eMax() {return cms2.els_eMax();}
    const std::vector<float>& els_eOverPIn() {return cms2.els_eOverPIn();}
    const std::vector<float>& els_eOverPOut() {return cms2.els_eOverPOut();}
    const std::vector<float>& els_eSC() {return cms2.els_eSC();}
    const std::vector<float>& els_eSCPresh() {return cms2.els_eSCPresh();}
    const std::vector<float>& els_eSCRaw() {return cms2.els_eSCRaw();}
    const std::vector<float>& els_eSeed() {return cms2.els_eSeed();}
    const std::vector<float>& els_eSeedOverPIn() {return cms2.els_eSeedOverPIn();}
    const std::vector<float>& els_eSeedOverPOut() {return cms2.els_eSeedOverPOut();}
    const std::vector<float>& els_ecalEnergy() {return cms2.els_ecalEnergy();}
    const std::vector<float>& els_ecalEnergyError() {return cms2.els_ecalEnergyError();}
    const std::vector<float>& els_ecalIso() {return cms2.els_ecalIso();}
    const std::vector<float>& els_ecalIso04() {return cms2.els_ecalIso04();}
    const std::vector<float>& els_etaErr() {return cms2.els_etaErr();}
    const std::vector<float>& els_etaSC() {return cms2.els_etaSC();}
    const std::vector<float>& els_etaSCwidth() {return cms2.els_etaSCwidth();}
    const std::vector<float>& els_fbrem() {return cms2.els_fbrem();}
    const std::vector<float>& els_hOverE() {return cms2.els_hOverE();}
    const std::vector<float>& els_hcalDepth1OverEcal() {return cms2.els_hcalDepth1OverEcal();}
    const std::vector<float>& els_hcalDepth1TowerSumEt() {return cms2.els_hcalDepth1TowerSumEt();}
    const std::vector<float>& els_hcalDepth1TowerSumEt04() {return cms2.els_hcalDepth1TowerSumEt04();}
    const std::vector<float>& els_hcalDepth2OverEcal() {return cms2.els_hcalDepth2OverEcal();}
    const std::vector<float>& els_hcalDepth2TowerSumEt() {return cms2.els_hcalDepth2TowerSumEt();}
    const std::vector<float>& els_hcalDepth2TowerSumEt04() {return cms2.els_hcalDepth2TowerSumEt04();}
    const std::vector<float>& els_hcalIso() {return cms2.els_hcalIso();}
    const std::vector<float>& els_hcalIso04() {return cms2.els_hcalIso04();}
    const std::vector<float>& els_ip3d() {return cms2.els_ip3d();}
    const std::vector<float>& els_ip3derr() {return cms2.els_ip3derr();}
    const std::vector<float>& els_iso03_pf() {return cms2.els_iso03_pf();}
    const std::vector<float>& els_iso03_pf2012_ch() {return cms2.els_iso03_pf2012_ch();}
    const std::vector<float>& els_iso03_pf2012_em() {return cms2.els_iso03_pf2012_em();}
    const std::vector<float>& els_iso03_pf2012ext_ch() {return cms2.els_iso03_pf2012ext_ch();}
    const std::vector<float>& els_iso03_pf2012ext_em() {return cms2.els_iso03_pf2012ext_em();}
    const std::vector<float>& els_iso03_pf2012ext_nh() {return cms2.els_iso03_pf2012ext_nh();}
    const std::vector<float>& els_iso03_pf2012_nh() {return cms2.els_iso03_pf2012_nh();}
    const std::vector<float>& els_iso03_pf_ch() {return cms2.els_iso03_pf_ch();}
    const std::vector<float>& els_iso03_pf_gamma05() {return cms2.els_iso03_pf_gamma05();}
    const std::vector<float>& els_iso03_pf_nhad05() {return cms2.els_iso03_pf_nhad05();}
    const std::vector<float>& els_iso04_pf() {return cms2.els_iso04_pf();}
    const std::vector<float>& els_iso04_pf2012_ch() {return cms2.els_iso04_pf2012_ch();}
    const std::vector<float>& els_iso04_pf2012_em() {return cms2.els_iso04_pf2012_em();}
    const std::vector<float>& els_iso04_pf2012ext_ch() {return cms2.els_iso04_pf2012ext_ch();}
    const std::vector<float>& els_iso04_pf2012ext_em() {return cms2.els_iso04_pf2012ext_em();}
    const std::vector<float>& els_iso04_pf2012ext_nh() {return cms2.els_iso04_pf2012ext_nh();}
    const std::vector<float>& els_iso04_pf2012_nh() {return cms2.els_iso04_pf2012_nh();}
    const std::vector<float>& els_iso04_pf_ch() {return cms2.els_iso04_pf_ch();}
    const std::vector<float>& els_iso04_pf_gamma05() {return cms2.els_iso04_pf_gamma05();}
    const std::vector<float>& els_iso04_pf_nhad05() {return cms2.els_iso04_pf_nhad05();}
    const std::vector<float>& els_layer1_charge() {return cms2.els_layer1_charge();}
    const std::vector<float>& els_lh() {return cms2.els_lh();}
    const std::vector<float>& els_mva() {return cms2.els_mva();}
    const std::vector<float>& els_ndof() {return cms2.els_ndof();}
    const std::vector<float>& els_pfChargedHadronIso() {return cms2.els_pfChargedHadronIso();}
    const std::vector<float>& els_pfNeutralHadronIso() {return cms2.els_pfNeutralHadronIso();}
    const std::vector<float>& els_pfPhotonIso() {return cms2.els_pfPhotonIso();}
    const std::vector<float>& els_phiErr() {return cms2.els_phiErr();}
    const std::vector<float>& els_phiSC() {return cms2.els_phiSC();}
    const std::vector<float>& els_phiSCwidth() {return cms2.els_phiSCwidth();}
    const std::vector<float>& els_ptErr() {return cms2.els_ptErr();}
    const std::vector<float>& els_r9() {return cms2.els_r9();}
    const std::vector<float>& els_sigmaEtaEta() {return cms2.els_sigmaEtaEta();}
    const std::vector<float>& els_sigmaIEtaIEta() {return cms2.els_sigmaIEtaIEta();}
    const std::vector<float>& els_sigmaIEtaIEtaSC() {return cms2.els_sigmaIEtaIEtaSC();}
    const std::vector<float>& els_sigmaIEtaIPhi() {return cms2.els_sigmaIEtaIPhi();}
    const std::vector<float>& els_sigmaIPhiIPhi() {return cms2.els_sigmaIPhiIPhi();}
    const std::vector<float>& els_sigmaIPhiIPhiSC() {return cms2.els_sigmaIPhiIPhiSC();}
    const std::vector<float>& els_sigmaIphiIphi() {return cms2.els_sigmaIphiIphi();}
    const std::vector<float>& els_sigmaPhiPhi() {return cms2.els_sigmaPhiPhi();}
    const std::vector<float>& els_tkIso() {return cms2.els_tkIso();}
    const std::vector<float>& els_tkIso04() {return cms2.els_tkIso04();}
    const std::vector<float>& els_trackMomentumError() {return cms2.els_trackMomentumError();}
    const std::vector<float>& els_trkdr() {return cms2.els_trkdr();}
    const std::vector<float>& els_trkshFrac() {return cms2.els_trkshFrac();}
    const std::vector<float>& els_z0() {return cms2.els_z0();}
    const std::vector<float>& els_z0Err() {return cms2.els_z0Err();}
    const std::vector<float>& els_z0corr() {return cms2.els_z0corr();}
    const std::vector<float>& gsftrks_chi2() {return cms2.gsftrks_chi2();}
    const std::vector<float>& gsftrks_d0() {return cms2.gsftrks_d0();}
    const std::vector<float>& gsftrks_d0Err() {return cms2.gsftrks_d0Err();}
    const std::vector<float>& gsftrks_d0corr() {return cms2.gsftrks_d0corr();}
    const std::vector<float>& gsftrks_d0corrPhi() {return cms2.gsftrks_d0corrPhi();}
    const std::vector<float>& gsftrks_d0phiCov() {return cms2.gsftrks_d0phiCov();}
    const std::vector<float>& gsftrks_etaErr() {return cms2.gsftrks_etaErr();}
    const std::vector<float>& gsftrks_layer1_charge() {return cms2.gsftrks_layer1_charge();}
    const std::vector<float>& gsftrks_ndof() {return cms2.gsftrks_ndof();}
    const std::vector<float>& gsftrks_phiErr() {return cms2.gsftrks_phiErr();}
    const std::vector<float>& gsftrks_ptErr() {return cms2.gsftrks_ptErr();}
    const std::vector<float>& gsftrks_z0() {return cms2.gsftrks_z0();}
    const std::vector<float>& gsftrks_z0Err() {return cms2.gsftrks_z0Err();}
    const std::vector<float>& gsftrks_z0corr() {return cms2.gsftrks_z0corr();}
    const std::vector<float>& hyp_Ht() {return cms2.hyp_Ht();}
    const std::vector<float>& hyp_dPhi_nJet_metMuonJESCorr() {return cms2.hyp_dPhi_nJet_metMuonJESCorr();}
    const std::vector<float>& hyp_dPhi_nJet_muCorrMet() {return cms2.hyp_dPhi_nJet_muCorrMet();}
    const std::vector<float>& hyp_dPhi_nJet_tcMet() {return cms2.hyp_dPhi_nJet_tcMet();}
    const std::vector<float>& hyp_dPhi_nJet_unCorrMet() {return cms2.hyp_dPhi_nJet_unCorrMet();}
    const std::vector<float>& hyp_ll_chi2() {return cms2.hyp_ll_chi2();}
    const std::vector<float>& hyp_ll_d0() {return cms2.hyp_ll_d0();}
    const std::vector<float>& hyp_ll_d0Err() {return cms2.hyp_ll_d0Err();}
    const std::vector<float>& hyp_ll_d0corr() {return cms2.hyp_ll_d0corr();}
    const std::vector<float>& hyp_ll_dPhi_metMuonJESCorr() {return cms2.hyp_ll_dPhi_metMuonJESCorr();}
    const std::vector<float>& hyp_ll_dPhi_muCorrMet() {return cms2.hyp_ll_dPhi_muCorrMet();}
    const std::vector<float>& hyp_ll_dPhi_tcMet() {return cms2.hyp_ll_dPhi_tcMet();}
    const std::vector<float>& hyp_ll_dPhi_unCorrMet() {return cms2.hyp_ll_dPhi_unCorrMet();}
    const std::vector<float>& hyp_ll_etaErr() {return cms2.hyp_ll_etaErr();}
    const std::vector<float>& hyp_ll_ndof() {return cms2.hyp_ll_ndof();}
    const std::vector<float>& hyp_ll_phiErr() {return cms2.hyp_ll_phiErr();}
    const std::vector<float>& hyp_ll_ptErr() {return cms2.hyp_ll_ptErr();}
    const std::vector<float>& hyp_ll_z0() {return cms2.hyp_ll_z0();}
    const std::vector<float>& hyp_ll_z0Err() {return cms2.hyp_ll_z0Err();}
    const std::vector<float>& hyp_ll_z0corr() {return cms2.hyp_ll_z0corr();}
    const std::vector<float>& hyp_lt_chi2() {return cms2.hyp_lt_chi2();}
    const std::vector<float>& hyp_lt_d0() {return cms2.hyp_lt_d0();}
    const std::vector<float>& hyp_lt_d0Err() {return cms2.hyp_lt_d0Err();}
    const std::vector<float>& hyp_lt_d0corr() {return cms2.hyp_lt_d0corr();}
    const std::vector<float>& hyp_lt_dPhi_metMuonJESCorr() {return cms2.hyp_lt_dPhi_metMuonJESCorr();}
    const std::vector<float>& hyp_lt_dPhi_muCorrMet() {return cms2.hyp_lt_dPhi_muCorrMet();}
    const std::vector<float>& hyp_lt_dPhi_tcMet() {return cms2.hyp_lt_dPhi_tcMet();}
    const std::vector<float>& hyp_lt_dPhi_unCorrMet() {return cms2.hyp_lt_dPhi_unCorrMet();}
    const std::vector<float>& hyp_lt_etaErr() {return cms2.hyp_lt_etaErr();}
    const std::vector<float>& hyp_lt_ndof() {return cms2.hyp_lt_ndof();}
    const std::vector<float>& hyp_lt_phiErr() {return cms2.hyp_lt_phiErr();}
    const std::vector<float>& hyp_lt_ptErr() {return cms2.hyp_lt_ptErr();}
    const std::vector<float>& hyp_lt_z0() {return cms2.hyp_lt_z0();}
    const std::vector<float>& hyp_lt_z0Err() {return cms2.hyp_lt_z0Err();}
    const std::vector<float>& hyp_lt_z0corr() {return cms2.hyp_lt_z0corr();}
    const std::vector<float>& hyp_mt2_metMuonJESCorr() {return cms2.hyp_mt2_metMuonJESCorr();}
    const std::vector<float>& hyp_mt2_muCorrMet() {return cms2.hyp_mt2_muCorrMet();}
    const std::vector<float>& hyp_mt2_tcMet() {return cms2.hyp_mt2_tcMet();}
    const std::vector<float>& hyp_sumJetPt() {return cms2.hyp_sumJetPt();}
    const std::vector<float>& hyp_FVFit_chi2ndf() {return cms2.hyp_FVFit_chi2ndf();}
    const std::vector<float>& hyp_FVFit_prob() {return cms2.hyp_FVFit_prob();}
    const std::vector<float>& hyp_FVFit_v4cxx() {return cms2.hyp_FVFit_v4cxx();}
    const std::vector<float>& hyp_FVFit_v4cxy() {return cms2.hyp_FVFit_v4cxy();}
    const std::vector<float>& hyp_FVFit_v4cyy() {return cms2.hyp_FVFit_v4cyy();}
    const std::vector<float>& hyp_FVFit_v4czx() {return cms2.hyp_FVFit_v4czx();}
    const std::vector<float>& hyp_FVFit_v4czy() {return cms2.hyp_FVFit_v4czy();}
    const std::vector<float>& hyp_FVFit_v4czz() {return cms2.hyp_FVFit_v4czz();}
    const std::vector<float>& jets_approximatefHPD() {return cms2.jets_approximatefHPD();}
    const std::vector<float>& jets_approximatefRBX() {return cms2.jets_approximatefRBX();}
    const std::vector<float>& jets_cor() {return cms2.jets_cor();}
    const std::vector<float>& jets_corL1FastL2L3() {return cms2.jets_corL1FastL2L3();}
    const std::vector<float>& jets_corL1L2L3() {return cms2.jets_corL1L2L3();}
    const std::vector<float>& jets_emFrac() {return cms2.jets_emFrac();}
    const std::vector<float>& jets_fHPD() {return cms2.jets_fHPD();}
    const std::vector<float>& jets_fRBX() {return cms2.jets_fRBX();}
    const std::vector<float>& jets_fSubDetector1() {return cms2.jets_fSubDetector1();}
    const std::vector<float>& jets_fSubDetector2() {return cms2.jets_fSubDetector2();}
    const std::vector<float>& jets_fSubDetector3() {return cms2.jets_fSubDetector3();}
    const std::vector<float>& jets_fSubDetector4() {return cms2.jets_fSubDetector4();}
    const std::vector<float>& jets_hitsInN90() {return cms2.jets_hitsInN90();}
    const std::vector<float>& jets_n90Hits() {return cms2.jets_n90Hits();}
    const std::vector<float>& jets_nECALTowers() {return cms2.jets_nECALTowers();}
    const std::vector<float>& jets_nHCALTowers() {return cms2.jets_nHCALTowers();}
    const std::vector<float>& jets_restrictedEMF() {return cms2.jets_restrictedEMF();}
    const std::vector<float>& mus_met_deltax() {return cms2.mus_met_deltax();}
    const std::vector<float>& mus_met_deltay() {return cms2.mus_met_deltay();}
    const std::vector<float>& mus_eledr() {return cms2.mus_eledr();}
    const std::vector<float>& mus_jetdr() {return cms2.mus_jetdr();}
    const std::vector<float>& mus_isoR03_chpf_radial() {return cms2.mus_isoR03_chpf_radial();}
    const std::vector<float>& mus_isoR03_chpf_radialTight() {return cms2.mus_isoR03_chpf_radialTight();}
    const std::vector<float>& mus_isoR03_empf_radial() {return cms2.mus_isoR03_empf_radial();}
    const std::vector<float>& mus_isoR03_empf_radialTight() {return cms2.mus_isoR03_empf_radialTight();}
    const std::vector<float>& mus_isoR03_nhpf_radial() {return cms2.mus_isoR03_nhpf_radial();}
    const std::vector<float>& mus_isoR03_nhpf_radialTight() {return cms2.mus_isoR03_nhpf_radialTight();}
    const std::vector<float>& mus_isoR03_pf_radial() {return cms2.mus_isoR03_pf_radial();}
    const std::vector<float>& mus_isoR03_pf_radialTight() {return cms2.mus_isoR03_pf_radialTight();}
    const std::vector<float>& mus_backToBackCompat() {return cms2.mus_backToBackCompat();}
    const std::vector<float>& mus_caloCompatibility() {return cms2.mus_caloCompatibility();}
    const std::vector<float>& mus_chi2() {return cms2.mus_chi2();}
    const std::vector<float>& mus_chi2LocalMomentum() {return cms2.mus_chi2LocalMomentum();}
    const std::vector<float>& mus_chi2LocalPosition() {return cms2.mus_chi2LocalPosition();}
    const std::vector<float>& mus_cosmicCompat() {return cms2.mus_cosmicCompat();}
    const std::vector<float>& mus_d0() {return cms2.mus_d0();}
    const std::vector<float>& mus_d0Err() {return cms2.mus_d0Err();}
    const std::vector<float>& mus_d0corr() {return cms2.mus_d0corr();}
    const std::vector<float>& mus_e_em() {return cms2.mus_e_em();}
    const std::vector<float>& mus_e_emS9() {return cms2.mus_e_emS9();}
    const std::vector<float>& mus_e_had() {return cms2.mus_e_had();}
    const std::vector<float>& mus_e_hadS9() {return cms2.mus_e_hadS9();}
    const std::vector<float>& mus_e_ho() {return cms2.mus_e_ho();}
    const std::vector<float>& mus_e_hoS9() {return cms2.mus_e_hoS9();}
    const std::vector<float>& mus_etaErr() {return cms2.mus_etaErr();}
    const std::vector<float>& mus_gfit_chi2() {return cms2.mus_gfit_chi2();}
    const std::vector<float>& mus_gfit_d0() {return cms2.mus_gfit_d0();}
    const std::vector<float>& mus_gfit_d0Err() {return cms2.mus_gfit_d0Err();}
    const std::vector<float>& mus_gfit_d0corr() {return cms2.mus_gfit_d0corr();}
    const std::vector<float>& mus_gfit_ndof() {return cms2.mus_gfit_ndof();}
    const std::vector<float>& mus_gfit_qoverp() {return cms2.mus_gfit_qoverp();}
    const std::vector<float>& mus_gfit_qoverpError() {return cms2.mus_gfit_qoverpError();}
    const std::vector<float>& mus_gfit_z0() {return cms2.mus_gfit_z0();}
    const std::vector<float>& mus_gfit_z0Err() {return cms2.mus_gfit_z0Err();}
    const std::vector<float>& mus_gfit_z0corr() {return cms2.mus_gfit_z0corr();}
    const std::vector<float>& mus_glbKink() {return cms2.mus_glbKink();}
    const std::vector<float>& mus_glbTrackProbability() {return cms2.mus_glbTrackProbability();}
    const std::vector<float>& mus_globalDeltaEtaPhi() {return cms2.mus_globalDeltaEtaPhi();}
    const std::vector<float>& mus_ip3d() {return cms2.mus_ip3d();}
    const std::vector<float>& mus_ip3derr() {return cms2.mus_ip3derr();}
    const std::vector<float>& mus_iso03_emEt() {return cms2.mus_iso03_emEt();}
    const std::vector<float>& mus_iso03_hadEt() {return cms2.mus_iso03_hadEt();}
    const std::vector<float>& mus_iso03_hoEt() {return cms2.mus_iso03_hoEt();}
    const std::vector<float>& mus_iso03_pf() {return cms2.mus_iso03_pf();}
    const std::vector<float>& mus_iso03_sumPt() {return cms2.mus_iso03_sumPt();}
    const std::vector<float>& mus_iso04_pf() {return cms2.mus_iso04_pf();}
    const std::vector<float>& mus_iso05_emEt() {return cms2.mus_iso05_emEt();}
    const std::vector<float>& mus_iso05_hadEt() {return cms2.mus_iso05_hadEt();}
    const std::vector<float>& mus_iso05_hoEt() {return cms2.mus_iso05_hoEt();}
    const std::vector<float>& mus_iso05_sumPt() {return cms2.mus_iso05_sumPt();}
    const std::vector<float>& mus_isoR03_pf_ChargedHadronPt() {return cms2.mus_isoR03_pf_ChargedHadronPt();}
    const std::vector<float>& mus_isoR03_pf_ChargedParticlePt() {return cms2.mus_isoR03_pf_ChargedParticlePt();}
    const std::vector<float>& mus_isoR03_pf_NeutralHadronEt() {return cms2.mus_isoR03_pf_NeutralHadronEt();}
    const std::vector<float>& mus_isoR03_pf_NeutralHadronEtHighThreshold() {return cms2.mus_isoR03_pf_NeutralHadronEtHighThreshold();}
    const std::vector<float>& mus_isoR03_pf_PUPt() {return cms2.mus_isoR03_pf_PUPt();}
    const std::vector<float>& mus_isoR03_pf_PhotonEt() {return cms2.mus_isoR03_pf_PhotonEt();}
    const std::vector<float>& mus_isoR03_pf_PhotonEtHighThreshold() {return cms2.mus_isoR03_pf_PhotonEtHighThreshold();}
    const std::vector<float>& mus_isoR04_pf_ChargedHadronPt() {return cms2.mus_isoR04_pf_ChargedHadronPt();}
    const std::vector<float>& mus_isoR04_pf_ChargedParticlePt() {return cms2.mus_isoR04_pf_ChargedParticlePt();}
    const std::vector<float>& mus_isoR04_pf_NeutralHadronEt() {return cms2.mus_isoR04_pf_NeutralHadronEt();}
    const std::vector<float>& mus_isoR04_pf_NeutralHadronEtHighThreshold() {return cms2.mus_isoR04_pf_NeutralHadronEtHighThreshold();}
    const std::vector<float>& mus_isoR04_pf_PUPt() {return cms2.mus_isoR04_pf_PUPt();}
    const std::vector<float>& mus_isoR04_pf_PhotonEt() {return cms2.mus_isoR04_pf_PhotonEt();}
    const std::vector<float>& mus_isoR04_pf_PhotonEtHighThreshold() {return cms2.mus_isoR04_pf_PhotonEtHighThreshold();}
    const std::vector<float>& mus_iso_ecalvetoDep() {return cms2.mus_iso_ecalvetoDep();}
    const std::vector<float>& mus_iso_hcalvetoDep() {return cms2.mus_iso_hcalvetoDep();}
    const std::vector<float>& mus_iso_hovetoDep() {return cms2.mus_iso_hovetoDep();}
    const std::vector<float>& mus_iso_trckvetoDep() {return cms2.mus_iso_trckvetoDep();}
    const std::vector<float>& mus_localDistance() {return cms2.mus_localDistance();}
    const std::vector<float>& mus_ndof() {return cms2.mus_ndof();}
    const std::vector<float>& mus_overlapCompat() {return cms2.mus_overlapCompat();}
    const std::vector<float>& mus_pfdeltaP() {return cms2.mus_pfdeltaP();}
    const std::vector<float>& mus_pfecalE() {return cms2.mus_pfecalE();}
    const std::vector<float>& mus_pfhcalE() {return cms2.mus_pfhcalE();}
    const std::vector<float>& mus_pfmva_emu() {return cms2.mus_pfmva_emu();}
    const std::vector<float>& mus_pfmva_epi() {return cms2.mus_pfmva_epi();}
    const std::vector<float>& mus_pfmva_nothing_gamma() {return cms2.mus_pfmva_nothing_gamma();}
    const std::vector<float>& mus_pfmva_nothing_nh() {return cms2.mus_pfmva_nothing_nh();}
    const std::vector<float>& mus_pfmva_pimu() {return cms2.mus_pfmva_pimu();}
    const std::vector<float>& mus_pfpS1E() {return cms2.mus_pfpS1E();}
    const std::vector<float>& mus_pfpS2E() {return cms2.mus_pfpS2E();}
    const std::vector<float>& mus_pfrawEcalE() {return cms2.mus_pfrawEcalE();}
    const std::vector<float>& mus_pfrawHcalE() {return cms2.mus_pfrawHcalE();}
    const std::vector<float>& mus_phiErr() {return cms2.mus_phiErr();}
    const std::vector<float>& mus_ptErr() {return cms2.mus_ptErr();}
    const std::vector<float>& mus_qoverp() {return cms2.mus_qoverp();}
    const std::vector<float>& mus_qoverpError() {return cms2.mus_qoverpError();}
    const std::vector<float>& mus_segmCompatibility() {return cms2.mus_segmCompatibility();}
    const std::vector<float>& mus_staRelChi2() {return cms2.mus_staRelChi2();}
    const std::vector<float>& mus_sta_chi2() {return cms2.mus_sta_chi2();}
    const std::vector<float>& mus_sta_d0() {return cms2.mus_sta_d0();}
    const std::vector<float>& mus_sta_d0Err() {return cms2.mus_sta_d0Err();}
    const std::vector<float>& mus_sta_d0corr() {return cms2.mus_sta_d0corr();}
    const std::vector<float>& mus_sta_ndof() {return cms2.mus_sta_ndof();}
    const std::vector<float>& mus_sta_qoverp() {return cms2.mus_sta_qoverp();}
    const std::vector<float>& mus_sta_qoverpError() {return cms2.mus_sta_qoverpError();}
    const std::vector<float>& mus_sta_z0() {return cms2.mus_sta_z0();}
    const std::vector<float>& mus_sta_z0Err() {return cms2.mus_sta_z0Err();}
    const std::vector<float>& mus_sta_z0corr() {return cms2.mus_sta_z0corr();}
    const std::vector<float>& mus_timeAtIpInOut() {return cms2.mus_timeAtIpInOut();}
    const std::vector<float>& mus_timeAtIpInOutErr() {return cms2.mus_timeAtIpInOutErr();}
    const std::vector<float>& mus_timeAtIpOutIn() {return cms2.mus_timeAtIpOutIn();}
    const std::vector<float>& mus_timeAtIpOutInErr() {return cms2.mus_timeAtIpOutInErr();}
    const std::vector<float>& mus_timeCompat() {return cms2.mus_timeCompat();}
    const std::vector<float>& mus_trkKink() {return cms2.mus_trkKink();}
    const std::vector<float>& mus_trkRelChi2() {return cms2.mus_trkRelChi2();}
    const std::vector<float>& mus_vertexCompat() {return cms2.mus_vertexCompat();}
    const std::vector<float>& mus_vertexphi() {return cms2.mus_vertexphi();}
    const std::vector<float>& mus_z0() {return cms2.mus_z0();}
    const std::vector<float>& mus_z0Err() {return cms2.mus_z0Err();}
    const std::vector<float>& mus_z0corr() {return cms2.mus_z0corr();}
    const std::vector<float>& pfjets_mvavalue() {return cms2.pfjets_mvavalue();}
    const std::vector<float>& pfjets_full53xmva_beta() {return cms2.pfjets_full53xmva_beta();}
    const std::vector<float>& pfjets_full53xmva_betaStar() {return cms2.pfjets_full53xmva_betaStar();}
    const std::vector<float>& pfjets_full53xmva_d0() {return cms2.pfjets_full53xmva_d0();}
    const std::vector<float>& pfjets_full53xmva_dRMean() {return cms2.pfjets_full53xmva_dRMean();}
    const std::vector<float>& pfjets_full53xmva_dZ() {return cms2.pfjets_full53xmva_dZ();}
    const std::vector<float>& pfjets_full53xmva_frac01() {return cms2.pfjets_full53xmva_frac01();}
    const std::vector<float>& pfjets_full53xmva_frac02() {return cms2.pfjets_full53xmva_frac02();}
    const std::vector<float>& pfjets_full53xmva_frac03() {return cms2.pfjets_full53xmva_frac03();}
    const std::vector<float>& pfjets_full53xmva_frac04() {return cms2.pfjets_full53xmva_frac04();}
    const std::vector<float>& pfjets_full53xmva_frac05() {return cms2.pfjets_full53xmva_frac05();}
    const std::vector<float>& pfjets_full53xmva_nCharged() {return cms2.pfjets_full53xmva_nCharged();}
    const std::vector<float>& pfjets_full53xmva_nNeutrals() {return cms2.pfjets_full53xmva_nNeutrals();}
    const std::vector<float>& pfjets_full53xmva_nvtx() {return cms2.pfjets_full53xmva_nvtx();}
    const std::vector<float>& pfjets_full53xmvavalue() {return cms2.pfjets_full53xmvavalue();}
    const std::vector<float>& pfjets_full5xmvavalue() {return cms2.pfjets_full5xmvavalue();}
    const std::vector<float>& trkjet_met() {return cms2.trkjet_met();}
    const std::vector<float>& trkjet_metPhi() {return cms2.trkjet_metPhi();}
    const std::vector<float>& trkjet_sumet() {return cms2.trkjet_sumet();}
    const std::vector<float>& trk_met() {return cms2.trk_met();}
    const std::vector<float>& trk_metPhi() {return cms2.trk_metPhi();}
    const std::vector<float>& trk_sumet() {return cms2.trk_sumet();}
    const std::vector<float>& pfcands_deltaP() {return cms2.pfcands_deltaP();}
    const std::vector<float>& pfcands_ecalE() {return cms2.pfcands_ecalE();}
    const std::vector<float>& pfcands_hcalE() {return cms2.pfcands_hcalE();}
    const std::vector<float>& pfcands_mva_emu() {return cms2.pfcands_mva_emu();}
    const std::vector<float>& pfcands_mva_epi() {return cms2.pfcands_mva_epi();}
    const std::vector<float>& pfcands_mva_nothing_gamma() {return cms2.pfcands_mva_nothing_gamma();}
    const std::vector<float>& pfcands_mva_nothing_nh() {return cms2.pfcands_mva_nothing_nh();}
    const std::vector<float>& pfcands_mva_pimu() {return cms2.pfcands_mva_pimu();}
    const std::vector<float>& pfcands_pS1E() {return cms2.pfcands_pS1E();}
    const std::vector<float>& pfcands_pS2E() {return cms2.pfcands_pS2E();}
    const std::vector<float>& pfcands_rawEcalE() {return cms2.pfcands_rawEcalE();}
    const std::vector<float>& pfcands_rawHcalE() {return cms2.pfcands_rawHcalE();}
    const std::vector<float>& pfels_deltaP() {return cms2.pfels_deltaP();}
    const std::vector<float>& pfels_ecalE() {return cms2.pfels_ecalE();}
    const std::vector<float>& pfels_hcalE() {return cms2.pfels_hcalE();}
    const std::vector<float>& pfels_iso04ChargedHadrons() {return cms2.pfels_iso04ChargedHadrons();}
    const std::vector<float>& pfels_iso04NeutralHadrons() {return cms2.pfels_iso04NeutralHadrons();}
    const std::vector<float>& pfels_iso04Photons() {return cms2.pfels_iso04Photons();}
    const std::vector<float>& pfels_isoChargedHadrons() {return cms2.pfels_isoChargedHadrons();}
    const std::vector<float>& pfels_isoNeutralHadrons() {return cms2.pfels_isoNeutralHadrons();}
    const std::vector<float>& pfels_isoPhotons() {return cms2.pfels_isoPhotons();}
    const std::vector<float>& pfels_mva_emu() {return cms2.pfels_mva_emu();}
    const std::vector<float>& pfels_mva_epi() {return cms2.pfels_mva_epi();}
    const std::vector<float>& pfels_mva_nothing_gamma() {return cms2.pfels_mva_nothing_gamma();}
    const std::vector<float>& pfels_mva_nothing_nh() {return cms2.pfels_mva_nothing_nh();}
    const std::vector<float>& pfels_mva_pimu() {return cms2.pfels_mva_pimu();}
    const std::vector<float>& pfels_pS1E() {return cms2.pfels_pS1E();}
    const std::vector<float>& pfels_pS2E() {return cms2.pfels_pS2E();}
    const std::vector<float>& pfels_rawEcalE() {return cms2.pfels_rawEcalE();}
    const std::vector<float>& pfels_rawHcalE() {return cms2.pfels_rawHcalE();}
    const std::vector<float>& pfjets_area() {return cms2.pfjets_area();}
    const std::vector<float>& pfjets_chargedEmE() {return cms2.pfjets_chargedEmE();}
    const std::vector<float>& pfjets_chargedHadronE() {return cms2.pfjets_chargedHadronE();}
    const std::vector<float>& pfjets_cor() {return cms2.pfjets_cor();}
    const std::vector<float>& pfjets_corL1Fast() {return cms2.pfjets_corL1Fast();}
    const std::vector<float>& pfjets_corL1FastL2L3() {return cms2.pfjets_corL1FastL2L3();}
    const std::vector<float>& pfjets_corL1FastL2L3residual() {return cms2.pfjets_corL1FastL2L3residual();}
    const std::vector<float>& pfjets_corL1L2L3() {return cms2.pfjets_corL1L2L3();}
    const std::vector<float>& pfjets_electronE() {return cms2.pfjets_electronE();}
    const std::vector<float>& pfjets_hfEmE() {return cms2.pfjets_hfEmE();}
    const std::vector<float>& pfjets_hfHadronE() {return cms2.pfjets_hfHadronE();}
    const std::vector<float>& pfjets_muonE() {return cms2.pfjets_muonE();}
    const std::vector<float>& pfjets_neutralEmE() {return cms2.pfjets_neutralEmE();}
    const std::vector<float>& pfjets_neutralHadronE() {return cms2.pfjets_neutralHadronE();}
    const std::vector<float>& pfjets_photonE() {return cms2.pfjets_photonE();}
    const std::vector<float>& pfmus_deltaP() {return cms2.pfmus_deltaP();}
    const std::vector<float>& pfmus_ecalE() {return cms2.pfmus_ecalE();}
    const std::vector<float>& pfmus_hcalE() {return cms2.pfmus_hcalE();}
    const std::vector<float>& pfmus_iso04ChargedHadrons() {return cms2.pfmus_iso04ChargedHadrons();}
    const std::vector<float>& pfmus_iso04NeutralHadrons() {return cms2.pfmus_iso04NeutralHadrons();}
    const std::vector<float>& pfmus_iso04Photons() {return cms2.pfmus_iso04Photons();}
    const std::vector<float>& pfmus_isoChargedHadrons() {return cms2.pfmus_isoChargedHadrons();}
    const std::vector<float>& pfmus_isoNeutralHadrons() {return cms2.pfmus_isoNeutralHadrons();}
    const std::vector<float>& pfmus_isoPhotons() {return cms2.pfmus_isoPhotons();}
    const std::vector<float>& pfmus_mva_emu() {return cms2.pfmus_mva_emu();}
    const std::vector<float>& pfmus_mva_epi() {return cms2.pfmus_mva_epi();}
    const std::vector<float>& pfmus_mva_nothing_gamma() {return cms2.pfmus_mva_nothing_gamma();}
    const std::vector<float>& pfmus_mva_nothing_nh() {return cms2.pfmus_mva_nothing_nh();}
    const std::vector<float>& pfmus_mva_pimu() {return cms2.pfmus_mva_pimu();}
    const std::vector<float>& pfmus_pS1E() {return cms2.pfmus_pS1E();}
    const std::vector<float>& pfmus_pS2E() {return cms2.pfmus_pS2E();}
    const std::vector<float>& pfmus_rawEcalE() {return cms2.pfmus_rawEcalE();}
    const std::vector<float>& pfmus_rawHcalE() {return cms2.pfmus_rawHcalE();}
    const std::vector<float>& taus_pf_againstElectronDeadECAL() {return cms2.taus_pf_againstElectronDeadECAL();}
    const std::vector<float>& taus_pf_againstElectronLoose() {return cms2.taus_pf_againstElectronLoose();}
    const std::vector<float>& taus_pf_againstElectronLooseMVA2() {return cms2.taus_pf_againstElectronLooseMVA2();}
    const std::vector<float>& taus_pf_againstElectronLooseMVA3() {return cms2.taus_pf_againstElectronLooseMVA3();}
    const std::vector<float>& taus_pf_againstElectronMVA() {return cms2.taus_pf_againstElectronMVA();}
    const std::vector<float>& taus_pf_againstElectronMVA2category() {return cms2.taus_pf_againstElectronMVA2category();}
    const std::vector<float>& taus_pf_againstElectronMVA2raw() {return cms2.taus_pf_againstElectronMVA2raw();}
    const std::vector<float>& taus_pf_againstElectronMVA3category() {return cms2.taus_pf_againstElectronMVA3category();}
    const std::vector<float>& taus_pf_againstElectronMVA3raw() {return cms2.taus_pf_againstElectronMVA3raw();}
    const std::vector<float>& taus_pf_againstElectronMedium() {return cms2.taus_pf_againstElectronMedium();}
    const std::vector<float>& taus_pf_againstElectronMediumMVA2() {return cms2.taus_pf_againstElectronMediumMVA2();}
    const std::vector<float>& taus_pf_againstElectronMediumMVA3() {return cms2.taus_pf_againstElectronMediumMVA3();}
    const std::vector<float>& taus_pf_againstElectronTight() {return cms2.taus_pf_againstElectronTight();}
    const std::vector<float>& taus_pf_againstElectronTightMVA2() {return cms2.taus_pf_againstElectronTightMVA2();}
    const std::vector<float>& taus_pf_againstElectronTightMVA3() {return cms2.taus_pf_againstElectronTightMVA3();}
    const std::vector<float>& taus_pf_againstElectronVLooseMVA2() {return cms2.taus_pf_againstElectronVLooseMVA2();}
    const std::vector<float>& taus_pf_againstElectronVTightMVA3() {return cms2.taus_pf_againstElectronVTightMVA3();}
    const std::vector<float>& taus_pf_againstMuonLoose() {return cms2.taus_pf_againstMuonLoose();}
    const std::vector<float>& taus_pf_againstMuonLoose2() {return cms2.taus_pf_againstMuonLoose2();}
    const std::vector<float>& taus_pf_againstMuonMedium() {return cms2.taus_pf_againstMuonMedium();}
    const std::vector<float>& taus_pf_againstMuonMedium2() {return cms2.taus_pf_againstMuonMedium2();}
    const std::vector<float>& taus_pf_againstMuonTight() {return cms2.taus_pf_againstMuonTight();}
    const std::vector<float>& taus_pf_againstMuonTight2() {return cms2.taus_pf_againstMuonTight2();}
    const std::vector<float>& taus_pf_byCombinedIsolationDeltaBetaCorrRaw() {return cms2.taus_pf_byCombinedIsolationDeltaBetaCorrRaw();}
    const std::vector<float>& taus_pf_byCombinedIsolationDeltaBetaCorrRaw3Hits() {return cms2.taus_pf_byCombinedIsolationDeltaBetaCorrRaw3Hits();}
    const std::vector<float>& taus_pf_byDecayModeFinding() {return cms2.taus_pf_byDecayModeFinding();}
    const std::vector<float>& taus_pf_byIsolationMVA2raw() {return cms2.taus_pf_byIsolationMVA2raw();}
    const std::vector<float>& taus_pf_byIsolationMVAraw() {return cms2.taus_pf_byIsolationMVAraw();}
    const std::vector<float>& taus_pf_byLooseCombinedIsolationDeltaBetaCorr() {return cms2.taus_pf_byLooseCombinedIsolationDeltaBetaCorr();}
    const std::vector<float>& taus_pf_byLooseCombinedIsolationDeltaBetaCorr3Hits() {return cms2.taus_pf_byLooseCombinedIsolationDeltaBetaCorr3Hits();}
    const std::vector<float>& taus_pf_byLooseIsolationMVA() {return cms2.taus_pf_byLooseIsolationMVA();}
    const std::vector<float>& taus_pf_byLooseIsolationMVA2() {return cms2.taus_pf_byLooseIsolationMVA2();}
    const std::vector<float>& taus_pf_byMediumCombinedIsolationDeltaBetaCorr() {return cms2.taus_pf_byMediumCombinedIsolationDeltaBetaCorr();}
    const std::vector<float>& taus_pf_byMediumCombinedIsolationDeltaBetaCorr3Hits() {return cms2.taus_pf_byMediumCombinedIsolationDeltaBetaCorr3Hits();}
    const std::vector<float>& taus_pf_byMediumIsolationMVA() {return cms2.taus_pf_byMediumIsolationMVA();}
    const std::vector<float>& taus_pf_byMediumIsolationMVA2() {return cms2.taus_pf_byMediumIsolationMVA2();}
    const std::vector<float>& taus_pf_byTightCombinedIsolationDeltaBetaCorr() {return cms2.taus_pf_byTightCombinedIsolationDeltaBetaCorr();}
    const std::vector<float>& taus_pf_byTightCombinedIsolationDeltaBetaCorr3Hits() {return cms2.taus_pf_byTightCombinedIsolationDeltaBetaCorr3Hits();}
    const std::vector<float>& taus_pf_byTightIsolationMVA() {return cms2.taus_pf_byTightIsolationMVA();}
    const std::vector<float>& taus_pf_byTightIsolationMVA2() {return cms2.taus_pf_byTightIsolationMVA2();}
    const std::vector<float>& taus_pf_byVLooseCombinedIsolationDeltaBetaCorr() {return cms2.taus_pf_byVLooseCombinedIsolationDeltaBetaCorr();}
    const std::vector<float>& photons_e1x5() {return cms2.photons_e1x5();}
    const std::vector<float>& photons_e2x5Max() {return cms2.photons_e2x5Max();}
    const std::vector<float>& photons_e3x3() {return cms2.photons_e3x3();}
    const std::vector<float>& photons_e5x5() {return cms2.photons_e5x5();}
    const std::vector<float>& photons_ecalIso03() {return cms2.photons_ecalIso03();}
    const std::vector<float>& photons_ecalIso04() {return cms2.photons_ecalIso04();}
    const std::vector<float>& photons_hOverE() {return cms2.photons_hOverE();}
    const std::vector<float>& photons_hcalDepth1TowerSumEtBcConeDR03() {return cms2.photons_hcalDepth1TowerSumEtBcConeDR03();}
    const std::vector<float>& photons_hcalDepth1TowerSumEtBcConeDR04() {return cms2.photons_hcalDepth1TowerSumEtBcConeDR04();}
    const std::vector<float>& photons_hcalDepth2TowerSumEtBcConeDR03() {return cms2.photons_hcalDepth2TowerSumEtBcConeDR03();}
    const std::vector<float>& photons_hcalDepth2TowerSumEtBcConeDR04() {return cms2.photons_hcalDepth2TowerSumEtBcConeDR04();}
    const std::vector<float>& photons_hcalIso03() {return cms2.photons_hcalIso03();}
    const std::vector<float>& photons_hcalIso04() {return cms2.photons_hcalIso04();}
    const std::vector<float>& photons_hcalTowerSumEtBcConeDR03() {return cms2.photons_hcalTowerSumEtBcConeDR03();}
    const std::vector<float>& photons_hcalTowerSumEtBcConeDR04() {return cms2.photons_hcalTowerSumEtBcConeDR04();}
    const std::vector<float>& photons_ntkIsoHollow03() {return cms2.photons_ntkIsoHollow03();}
    const std::vector<float>& photons_ntkIsoHollow04() {return cms2.photons_ntkIsoHollow04();}
    const std::vector<float>& photons_ntkIsoSolid03() {return cms2.photons_ntkIsoSolid03();}
    const std::vector<float>& photons_ntkIsoSolid04() {return cms2.photons_ntkIsoSolid04();}
    const std::vector<float>& photons_sigmaEtaEta() {return cms2.photons_sigmaEtaEta();}
    const std::vector<float>& photons_sigmaIEtaIEta() {return cms2.photons_sigmaIEtaIEta();}
    const std::vector<float>& photons_swissSeed() {return cms2.photons_swissSeed();}
    const std::vector<float>& photons_tkIsoHollow03() {return cms2.photons_tkIsoHollow03();}
    const std::vector<float>& photons_tkIsoHollow04() {return cms2.photons_tkIsoHollow04();}
    const std::vector<float>& photons_tkIsoSolid03() {return cms2.photons_tkIsoSolid03();}
    const std::vector<float>& photons_tkIsoSolid04() {return cms2.photons_tkIsoSolid04();}
    const std::vector<float>& puInfo_trueNumInteractions() {return cms2.puInfo_trueNumInteractions();}
    const std::vector<float>& convs_chi2() {return cms2.convs_chi2();}
    const std::vector<float>& convs_dl() {return cms2.convs_dl();}
    const std::vector<float>& convs_ndof() {return cms2.convs_ndof();}
    const std::vector<float>& sparm_values() {return cms2.sparm_values();}
    const std::vector<float>& scs_clustersSize() {return cms2.scs_clustersSize();}
    const std::vector<float>& scs_crystalsSize() {return cms2.scs_crystalsSize();}
    const std::vector<float>& scs_e1x3() {return cms2.scs_e1x3();}
    const std::vector<float>& scs_e1x5() {return cms2.scs_e1x5();}
    const std::vector<float>& scs_e2nd() {return cms2.scs_e2nd();}
    const std::vector<float>& scs_e2x2() {return cms2.scs_e2x2();}
    const std::vector<float>& scs_e2x5Max() {return cms2.scs_e2x5Max();}
    const std::vector<float>& scs_e3x1() {return cms2.scs_e3x1();}
    const std::vector<float>& scs_e3x2() {return cms2.scs_e3x2();}
    const std::vector<float>& scs_e3x3() {return cms2.scs_e3x3();}
    const std::vector<float>& scs_e4x4() {return cms2.scs_e4x4();}
    const std::vector<float>& scs_e5x5() {return cms2.scs_e5x5();}
    const std::vector<float>& scs_eMax() {return cms2.scs_eMax();}
    const std::vector<float>& scs_eSeed() {return cms2.scs_eSeed();}
    const std::vector<float>& scs_energy() {return cms2.scs_energy();}
    const std::vector<float>& scs_eta() {return cms2.scs_eta();}
    const std::vector<float>& scs_hoe() {return cms2.scs_hoe();}
    const std::vector<float>& scs_laserCorMax() {return cms2.scs_laserCorMax();}
    const std::vector<float>& scs_laserCorMean() {return cms2.scs_laserCorMean();}
    const std::vector<float>& scs_laserCorSeed() {return cms2.scs_laserCorSeed();}
    const std::vector<float>& scs_phi() {return cms2.scs_phi();}
    const std::vector<float>& scs_preshowerEnergy() {return cms2.scs_preshowerEnergy();}
    const std::vector<float>& scs_rawEnergy() {return cms2.scs_rawEnergy();}
    const std::vector<float>& scs_sigmaEtaEta() {return cms2.scs_sigmaEtaEta();}
    const std::vector<float>& scs_sigmaEtaPhi() {return cms2.scs_sigmaEtaPhi();}
    const std::vector<float>& scs_sigmaIEtaIEta() {return cms2.scs_sigmaIEtaIEta();}
    const std::vector<float>& scs_sigmaIEtaIEtaSC() {return cms2.scs_sigmaIEtaIEtaSC();}
    const std::vector<float>& scs_sigmaIEtaIPhi() {return cms2.scs_sigmaIEtaIPhi();}
    const std::vector<float>& scs_sigmaIEtaIPhiSC() {return cms2.scs_sigmaIEtaIPhiSC();}
    const std::vector<float>& scs_sigmaIPhiIPhi() {return cms2.scs_sigmaIPhiIPhi();}
    const std::vector<float>& scs_sigmaIPhiIPhiSC() {return cms2.scs_sigmaIPhiIPhiSC();}
    const std::vector<float>& scs_sigmaPhiPhi() {return cms2.scs_sigmaPhiPhi();}
    const std::vector<float>& scs_timeSeed() {return cms2.scs_timeSeed();}
    const std::vector<float>& svs_anglePV() {return cms2.svs_anglePV();}
    const std::vector<float>& svs_chi2() {return cms2.svs_chi2();}
    const std::vector<float>& svs_dist3Dsig() {return cms2.svs_dist3Dsig();}
    const std::vector<float>& svs_dist3Dval() {return cms2.svs_dist3Dval();}
    const std::vector<float>& svs_distXYsig() {return cms2.svs_distXYsig();}
    const std::vector<float>& svs_distXYval() {return cms2.svs_distXYval();}
    const std::vector<float>& svs_ndof() {return cms2.svs_ndof();}
    const std::vector<float>& svs_prob() {return cms2.svs_prob();}
    const std::vector<float>& svs_xError() {return cms2.svs_xError();}
    const std::vector<float>& svs_yError() {return cms2.svs_yError();}
    const std::vector<float>& svs_zError() {return cms2.svs_zError();}
    const std::vector<float>& mus_tcmet_deltax() {return cms2.mus_tcmet_deltax();}
    const std::vector<float>& mus_tcmet_deltay() {return cms2.mus_tcmet_deltay();}
    const std::vector<float>& pfcands_dzpv() {return cms2.pfcands_dzpv();}
    const std::vector<float>& pfcands_trkiso() {return cms2.pfcands_trkiso();}
    const std::vector<float>& trks_chi2() {return cms2.trks_chi2();}
    const std::vector<float>& trks_d0() {return cms2.trks_d0();}
    const std::vector<float>& trks_d0Err() {return cms2.trks_d0Err();}
    const std::vector<float>& trks_d0corr() {return cms2.trks_d0corr();}
    const std::vector<float>& trks_d0corrPhi() {return cms2.trks_d0corrPhi();}
    const std::vector<float>& trks_d0phiCov() {return cms2.trks_d0phiCov();}
    const std::vector<float>& trks_etaErr() {return cms2.trks_etaErr();}
    const std::vector<float>& trks_layer1_charge() {return cms2.trks_layer1_charge();}
    const std::vector<float>& trks_ndof() {return cms2.trks_ndof();}
    const std::vector<float>& trks_phiErr() {return cms2.trks_phiErr();}
    const std::vector<float>& trks_ptErr() {return cms2.trks_ptErr();}
    const std::vector<float>& trks_validFraction() {return cms2.trks_validFraction();}
    const std::vector<float>& trks_z0() {return cms2.trks_z0();}
    const std::vector<float>& trks_z0Err() {return cms2.trks_z0Err();}
    const std::vector<float>& trks_z0corr() {return cms2.trks_z0corr();}
    const std::vector<float>& trkjets_cor() {return cms2.trkjets_cor();}
    const std::vector<float>& trks_d0Errvtx() {return cms2.trks_d0Errvtx();}
    const std::vector<float>& trks_d0vtx() {return cms2.trks_d0vtx();}
    const std::vector<float>& vtxs_chi2() {return cms2.vtxs_chi2();}
    const std::vector<float>& vtxs_ndof() {return cms2.vtxs_ndof();}
    const std::vector<float>& vtxs_sumpt() {return cms2.vtxs_sumpt();}
    const std::vector<float>& vtxs_xError() {return cms2.vtxs_xError();}
    const std::vector<float>& vtxs_yError() {return cms2.vtxs_yError();}
    const std::vector<float>& vtxs_zError() {return cms2.vtxs_zError();}
    const std::vector<float>& bsvtxs_chi2() {return cms2.bsvtxs_chi2();}
    const std::vector<float>& bsvtxs_ndof() {return cms2.bsvtxs_ndof();}
    const std::vector<float>& bsvtxs_sumpt() {return cms2.bsvtxs_sumpt();}
    const std::vector<float>& bsvtxs_xError() {return cms2.bsvtxs_xError();}
    const std::vector<float>& bsvtxs_yError() {return cms2.bsvtxs_yError();}
    const std::vector<float>& bsvtxs_zError() {return cms2.bsvtxs_zError();}
    const std::vector<std::vector<float> >& els_convs_dcot() {return cms2.els_convs_dcot();}
    const std::vector<std::vector<float> >& els_convs_dist() {return cms2.els_convs_dist();}
    const std::vector<std::vector<float> >& els_convs_radius() {return cms2.els_convs_radius();}
    const std::vector<std::vector<float> >& mus_stationShowerDeltaR() {return cms2.mus_stationShowerDeltaR();}
    const std::vector<std::vector<float> >& mus_stationShowerSizeT() {return cms2.mus_stationShowerSizeT();}
    const std::vector<std::vector<float> >& puInfo_instLumi() {return cms2.puInfo_instLumi();}
    const std::vector<std::vector<float> >& puInfo_sump_highpt() {return cms2.puInfo_sump_highpt();}
    const std::vector<std::vector<float> >& puInfo_sumpt_lowpt() {return cms2.puInfo_sumpt_lowpt();}
    const std::vector<std::vector<float> >& puInfo_zpositions() {return cms2.puInfo_zpositions();}
    const std::vector<std::vector<float> >& vtxs_covMatrix() {return cms2.vtxs_covMatrix();}
    const std::vector<std::vector<float> >& bsvtxs_covMatrix() {return cms2.bsvtxs_covMatrix();}
    const int& evt_cscLooseHaloId() {return cms2.evt_cscLooseHaloId();}
    const int& evt_cscTightHaloId() {return cms2.evt_cscTightHaloId();}
    const int& evt_ecalLooseHaloId() {return cms2.evt_ecalLooseHaloId();}
    const int& evt_ecalTightHaloId() {return cms2.evt_ecalTightHaloId();}
    const int& evt_extremeTightHaloId() {return cms2.evt_extremeTightHaloId();}
    const int& evt_globalLooseHaloId() {return cms2.evt_globalLooseHaloId();}
    const int& evt_globalTightHaloId() {return cms2.evt_globalTightHaloId();}
    const int& evt_hcalLooseHaloId() {return cms2.evt_hcalLooseHaloId();}
    const int& evt_hcalTightHaloId() {return cms2.evt_hcalTightHaloId();}
    const int& evt_looseHaloId() {return cms2.evt_looseHaloId();}
    const int& evt_nHaloLikeTracks() {return cms2.evt_nHaloLikeTracks();}
    const int& evt_nHaloTriggerCandidates() {return cms2.evt_nHaloTriggerCandidates();}
    const int& evt_tightHaloId() {return cms2.evt_tightHaloId();}
    const int& evt_bsType() {return cms2.evt_bsType();}
    const int& evt_bunchCrossing() {return cms2.evt_bunchCrossing();}
    const int& evt_experimentType() {return cms2.evt_experimentType();}
    const int& evt_isRealData() {return cms2.evt_isRealData();}
    const int& evt_orbitNumber() {return cms2.evt_orbitNumber();}
    const int& evt_storeNumber() {return cms2.evt_storeNumber();}
    const int& hcalnoise_GetRecHitCount() {return cms2.hcalnoise_GetRecHitCount();}
    const int& hcalnoise_GetRecHitCount15() {return cms2.hcalnoise_GetRecHitCount15();}
    const int& hcalnoise_maxHPDHits() {return cms2.hcalnoise_maxHPDHits();}
    const int& hcalnoise_maxHPDNoOtherHits() {return cms2.hcalnoise_maxHPDNoOtherHits();}
    const int& hcalnoise_maxRBXHits() {return cms2.hcalnoise_maxRBXHits();}
    const int& hcalnoise_maxZeros() {return cms2.hcalnoise_maxZeros();}
    const int& hcalnoise_noiseFilterStatus() {return cms2.hcalnoise_noiseFilterStatus();}
    const int& hcalnoise_noiseType() {return cms2.hcalnoise_noiseType();}
    const int& hcalnoise_num10GeVHits() {return cms2.hcalnoise_num10GeVHits();}
    const int& hcalnoise_num25GeVHits() {return cms2.hcalnoise_num25GeVHits();}
    const int& hcalnoise_numFlatNoiseChannels() {return cms2.hcalnoise_numFlatNoiseChannels();}
    const int& hcalnoise_numIsolatedNoiseChannels() {return cms2.hcalnoise_numIsolatedNoiseChannels();}
    const int& hcalnoise_numProblematicRBXs() {return cms2.hcalnoise_numProblematicRBXs();}
    const int& hcalnoise_numSpikeNoiseChannels() {return cms2.hcalnoise_numSpikeNoiseChannels();}
    const int& hcalnoise_numTS4TS5NoiseChannels() {return cms2.hcalnoise_numTS4TS5NoiseChannels();}
    const int& hcalnoise_numTriangleNoiseChannels() {return cms2.hcalnoise_numTriangleNoiseChannels();}
    const int& hcalnoise_passHighLevelNoiseFilter() {return cms2.hcalnoise_passHighLevelNoiseFilter();}
    const int& hcalnoise_passLooseNoiseFilter() {return cms2.hcalnoise_passLooseNoiseFilter();}
    const int& hcalnoise_passTightNoiseFilter() {return cms2.hcalnoise_passTightNoiseFilter();}
    const int& l1_nemiso() {return cms2.l1_nemiso();}
    const int& l1_nemnoiso() {return cms2.l1_nemnoiso();}
    const int& l1_njetsc() {return cms2.l1_njetsc();}
    const int& l1_njetsf() {return cms2.l1_njetsf();}
    const int& l1_njetst() {return cms2.l1_njetst();}
    const int& l1_nmus() {return cms2.l1_nmus();}
    const int& ls_lumiSecQual() {return cms2.ls_lumiSecQual();}
    const int& pdfinfo_id1() {return cms2.pdfinfo_id1();}
    const int& pdfinfo_id2() {return cms2.pdfinfo_id2();}
    const int& sparm_subProcessId() {return cms2.sparm_subProcessId();}
    const std::vector<int>& evt_ecaliPhiSuspects() {return cms2.evt_ecaliPhiSuspects();}
    const std::vector<int>& evt_globaliPhiSuspects() {return cms2.evt_globaliPhiSuspects();}
    const std::vector<int>& evt_hcaliPhiSuspects() {return cms2.evt_hcaliPhiSuspects();}
    const std::vector<int>& els_mc3_id() {return cms2.els_mc3_id();}
    const std::vector<int>& els_mc3idx() {return cms2.els_mc3idx();}
    const std::vector<int>& els_mc3_motherid() {return cms2.els_mc3_motherid();}
    const std::vector<int>& els_mc3_motheridx() {return cms2.els_mc3_motheridx();}
    const std::vector<int>& els_mc_id() {return cms2.els_mc_id();}
    const std::vector<int>& els_mcidx() {return cms2.els_mcidx();}
    const std::vector<int>& els_mc_motherid() {return cms2.els_mc_motherid();}
    const std::vector<int>& jets_mc3_id() {return cms2.jets_mc3_id();}
    const std::vector<int>& jets_mc3idx() {return cms2.jets_mc3idx();}
    const std::vector<int>& jets_mc_gpidx() {return cms2.jets_mc_gpidx();}
    const std::vector<int>& jets_mc_id() {return cms2.jets_mc_id();}
    const std::vector<int>& jets_mcidx() {return cms2.jets_mcidx();}
    const std::vector<int>& jets_mc_motherid() {return cms2.jets_mc_motherid();}
    const std::vector<int>& mus_mc3_id() {return cms2.mus_mc3_id();}
    const std::vector<int>& mus_mc3idx() {return cms2.mus_mc3idx();}
    const std::vector<int>& mus_mc3_motherid() {return cms2.mus_mc3_motherid();}
    const std::vector<int>& mus_mc3_motheridx() {return cms2.mus_mc3_motheridx();}
    const std::vector<int>& mus_mc_id() {return cms2.mus_mc_id();}
    const std::vector<int>& mus_mcidx() {return cms2.mus_mcidx();}
    const std::vector<int>& mus_mc_motherid() {return cms2.mus_mc_motherid();}
    const std::vector<int>& pfjets_mc3_id() {return cms2.pfjets_mc3_id();}
    const std::vector<int>& pfjets_mc3idx() {return cms2.pfjets_mc3idx();}
    const std::vector<int>& pfjets_mc_gpidx() {return cms2.pfjets_mc_gpidx();}
    const std::vector<int>& pfjets_mc_id() {return cms2.pfjets_mc_id();}
    const std::vector<int>& pfjets_mcidx() {return cms2.pfjets_mcidx();}
    const std::vector<int>& pfjets_mc_motherid() {return cms2.pfjets_mc_motherid();}
    const std::vector<int>& photons_mc3_id() {return cms2.photons_mc3_id();}
    const std::vector<int>& photons_mc3idx() {return cms2.photons_mc3idx();}
    const std::vector<int>& photons_mc3_motherid() {return cms2.photons_mc3_motherid();}
    const std::vector<int>& photons_mc3_motheridx() {return cms2.photons_mc3_motheridx();}
    const std::vector<int>& photons_mc_id() {return cms2.photons_mc_id();}
    const std::vector<int>& photons_mcidx() {return cms2.photons_mcidx();}
    const std::vector<int>& photons_mc_motherid() {return cms2.photons_mc_motherid();}
    const std::vector<int>& trk_mc3_id() {return cms2.trk_mc3_id();}
    const std::vector<int>& trk_mc3idx() {return cms2.trk_mc3idx();}
    const std::vector<int>& trk_mc3_motherid() {return cms2.trk_mc3_motherid();}
    const std::vector<int>& trk_mc3_motheridx() {return cms2.trk_mc3_motheridx();}
    const std::vector<int>& trk_mc_id() {return cms2.trk_mc_id();}
    const std::vector<int>& trk_mcidx() {return cms2.trk_mcidx();}
    const std::vector<int>& trk_mc_motherid() {return cms2.trk_mc_motherid();}
    const std::vector<int>& els_closestJet() {return cms2.els_closestJet();}
    const std::vector<int>& els_closestMuon() {return cms2.els_closestMuon();}
    const std::vector<int>& els_pfelsidx() {return cms2.els_pfelsidx();}
    const std::vector<int>& els_category() {return cms2.els_category();}
    const std::vector<int>& els_charge() {return cms2.els_charge();}
    const std::vector<int>& els_ckf_laywithmeas() {return cms2.els_ckf_laywithmeas();}
    const std::vector<int>& els_class() {return cms2.els_class();}
    const std::vector<int>& els_conv_delMissHits() {return cms2.els_conv_delMissHits();}
    const std::vector<int>& els_conv_flag() {return cms2.els_conv_flag();}
    const std::vector<int>& els_conv_gsftkidx() {return cms2.els_conv_gsftkidx();}
    const std::vector<int>& els_conv_old_delMissHits() {return cms2.els_conv_old_delMissHits();}
    const std::vector<int>& els_conv_old_flag() {return cms2.els_conv_old_flag();}
    const std::vector<int>& els_conv_old_gsftkidx() {return cms2.els_conv_old_gsftkidx();}
    const std::vector<int>& els_conv_old_tkidx() {return cms2.els_conv_old_tkidx();}
    const std::vector<int>& els_conv_tkidx() {return cms2.els_conv_tkidx();}
    const std::vector<int>& els_exp_innerlayers() {return cms2.els_exp_innerlayers();}
    const std::vector<int>& els_exp_outerlayers() {return cms2.els_exp_outerlayers();}
    const std::vector<int>& els_fiduciality() {return cms2.els_fiduciality();}
    const std::vector<int>& els_gsftrkidx() {return cms2.els_gsftrkidx();}
    const std::vector<int>& els_layer1_det() {return cms2.els_layer1_det();}
    const std::vector<int>& els_layer1_layer() {return cms2.els_layer1_layer();}
    const std::vector<int>& els_layer1_sizerphi() {return cms2.els_layer1_sizerphi();}
    const std::vector<int>& els_layer1_sizerz() {return cms2.els_layer1_sizerz();}
    const std::vector<int>& els_lostHits() {return cms2.els_lostHits();}
    const std::vector<int>& els_lost_pixelhits() {return cms2.els_lost_pixelhits();}
    const std::vector<int>& els_nSeed() {return cms2.els_nSeed();}
    const std::vector<int>& els_sccharge() {return cms2.els_sccharge();}
    const std::vector<int>& els_scindex() {return cms2.els_scindex();}
    const std::vector<int>& els_trk_charge() {return cms2.els_trk_charge();}
    const std::vector<int>& els_trkidx() {return cms2.els_trkidx();}
    const std::vector<int>& els_type() {return cms2.els_type();}
    const std::vector<int>& els_validHits() {return cms2.els_validHits();}
    const std::vector<int>& els_valid_pixelhits() {return cms2.els_valid_pixelhits();}
    const std::vector<int>& genps_id() {return cms2.genps_id();}
    const std::vector<int>& genps_id_mother() {return cms2.genps_id_mother();}
    const std::vector<int>& genps_status() {return cms2.genps_status();}
    const std::vector<int>& gsftrks_charge() {return cms2.gsftrks_charge();}
    const std::vector<int>& gsftrks_exp_innerlayers() {return cms2.gsftrks_exp_innerlayers();}
    const std::vector<int>& gsftrks_exp_outerlayers() {return cms2.gsftrks_exp_outerlayers();}
    const std::vector<int>& gsftrks_layer1_det() {return cms2.gsftrks_layer1_det();}
    const std::vector<int>& gsftrks_layer1_layer() {return cms2.gsftrks_layer1_layer();}
    const std::vector<int>& gsftrks_layer1_sizerphi() {return cms2.gsftrks_layer1_sizerphi();}
    const std::vector<int>& gsftrks_layer1_sizerz() {return cms2.gsftrks_layer1_sizerz();}
    const std::vector<int>& gsftrks_lostHits() {return cms2.gsftrks_lostHits();}
    const std::vector<int>& gsftrks_lost_pixelhits() {return cms2.gsftrks_lost_pixelhits();}
    const std::vector<int>& gsftrks_nlayers() {return cms2.gsftrks_nlayers();}
    const std::vector<int>& gsftrks_nlayers3D() {return cms2.gsftrks_nlayers3D();}
    const std::vector<int>& gsftrks_nlayersLost() {return cms2.gsftrks_nlayersLost();}
    const std::vector<int>& gsftrks_validHits() {return cms2.gsftrks_validHits();}
    const std::vector<int>& gsftrks_valid_pixelhits() {return cms2.gsftrks_valid_pixelhits();}
    const std::vector<int>& hyp_ll_charge() {return cms2.hyp_ll_charge();}
    const std::vector<int>& hyp_ll_id() {return cms2.hyp_ll_id();}
    const std::vector<int>& hyp_ll_index() {return cms2.hyp_ll_index();}
    const std::vector<int>& hyp_ll_lostHits() {return cms2.hyp_ll_lostHits();}
    const std::vector<int>& hyp_ll_validHits() {return cms2.hyp_ll_validHits();}
    const std::vector<int>& hyp_lt_charge() {return cms2.hyp_lt_charge();}
    const std::vector<int>& hyp_lt_id() {return cms2.hyp_lt_id();}
    const std::vector<int>& hyp_lt_index() {return cms2.hyp_lt_index();}
    const std::vector<int>& hyp_lt_lostHits() {return cms2.hyp_lt_lostHits();}
    const std::vector<int>& hyp_lt_validHits() {return cms2.hyp_lt_validHits();}
    const std::vector<int>& hyp_njets() {return cms2.hyp_njets();}
    const std::vector<int>& hyp_nojets() {return cms2.hyp_nojets();}
    const std::vector<int>& hyp_type() {return cms2.hyp_type();}
    const std::vector<int>& hyp_FVFit_ndf() {return cms2.hyp_FVFit_ndf();}
    const std::vector<int>& hyp_FVFit_status() {return cms2.hyp_FVFit_status();}
    const std::vector<int>& hyp_ll_mc_id() {return cms2.hyp_ll_mc_id();}
    const std::vector<int>& hyp_ll_mc_motherid() {return cms2.hyp_ll_mc_motherid();}
    const std::vector<int>& hyp_lt_mc_id() {return cms2.hyp_lt_mc_id();}
    const std::vector<int>& hyp_lt_mc_motherid() {return cms2.hyp_lt_mc_motherid();}
    const std::vector<int>& pfjets_mcflavorAlgo() {return cms2.pfjets_mcflavorAlgo();}
    const std::vector<int>& pfjets_mcflavorPhys() {return cms2.pfjets_mcflavorPhys();}
    const std::vector<int>& jets_closestElectron() {return cms2.jets_closestElectron();}
    const std::vector<int>& jets_closestMuon() {return cms2.jets_closestMuon();}
    const std::vector<int>& l1_emiso_ieta() {return cms2.l1_emiso_ieta();}
    const std::vector<int>& l1_emiso_iphi() {return cms2.l1_emiso_iphi();}
    const std::vector<int>& l1_emiso_rawId() {return cms2.l1_emiso_rawId();}
    const std::vector<int>& l1_emiso_type() {return cms2.l1_emiso_type();}
    const std::vector<int>& l1_emnoiso_ieta() {return cms2.l1_emnoiso_ieta();}
    const std::vector<int>& l1_emnoiso_iphi() {return cms2.l1_emnoiso_iphi();}
    const std::vector<int>& l1_emnoiso_rawId() {return cms2.l1_emnoiso_rawId();}
    const std::vector<int>& l1_emnoiso_type() {return cms2.l1_emnoiso_type();}
    const std::vector<int>& l1_jetsc_ieta() {return cms2.l1_jetsc_ieta();}
    const std::vector<int>& l1_jetsc_iphi() {return cms2.l1_jetsc_iphi();}
    const std::vector<int>& l1_jetsc_rawId() {return cms2.l1_jetsc_rawId();}
    const std::vector<int>& l1_jetsc_type() {return cms2.l1_jetsc_type();}
    const std::vector<int>& l1_jetsf_ieta() {return cms2.l1_jetsf_ieta();}
    const std::vector<int>& l1_jetsf_iphi() {return cms2.l1_jetsf_iphi();}
    const std::vector<int>& l1_jetsf_rawId() {return cms2.l1_jetsf_rawId();}
    const std::vector<int>& l1_jetsf_type() {return cms2.l1_jetsf_type();}
    const std::vector<int>& l1_jetst_ieta() {return cms2.l1_jetst_ieta();}
    const std::vector<int>& l1_jetst_iphi() {return cms2.l1_jetst_iphi();}
    const std::vector<int>& l1_jetst_rawId() {return cms2.l1_jetst_rawId();}
    const std::vector<int>& l1_jetst_type() {return cms2.l1_jetst_type();}
    const std::vector<int>& l1_mus_flags() {return cms2.l1_mus_flags();}
    const std::vector<int>& l1_mus_q() {return cms2.l1_mus_q();}
    const std::vector<int>& l1_mus_qual() {return cms2.l1_mus_qual();}
    const std::vector<int>& l1_mus_qualFlags() {return cms2.l1_mus_qualFlags();}
    const std::vector<int>& mus_met_flag() {return cms2.mus_met_flag();}
    const std::vector<int>& mus_closestEle() {return cms2.mus_closestEle();}
    const std::vector<int>& mus_closestJet() {return cms2.mus_closestJet();}
    const std::vector<int>& mus_pfmusidx() {return cms2.mus_pfmusidx();}
    const std::vector<int>& mus_charge() {return cms2.mus_charge();}
    const std::vector<int>& mus_gfit_validHits() {return cms2.mus_gfit_validHits();}
    const std::vector<int>& mus_gfit_validSTAHits() {return cms2.mus_gfit_validSTAHits();}
    const std::vector<int>& mus_gfit_validSiHits() {return cms2.mus_gfit_validSiHits();}
    const std::vector<int>& mus_goodmask() {return cms2.mus_goodmask();}
    const std::vector<int>& mus_iso03_ntrk() {return cms2.mus_iso03_ntrk();}
    const std::vector<int>& mus_iso05_ntrk() {return cms2.mus_iso05_ntrk();}
    const std::vector<int>& mus_lostHits() {return cms2.mus_lostHits();}
    const std::vector<int>& mus_muonBestTrackType() {return cms2.mus_muonBestTrackType();}
    const std::vector<int>& mus_nOverlaps() {return cms2.mus_nOverlaps();}
    const std::vector<int>& mus_nmatches() {return cms2.mus_nmatches();}
    const std::vector<int>& mus_numberOfMatchedStations() {return cms2.mus_numberOfMatchedStations();}
    const std::vector<int>& mus_overlap0() {return cms2.mus_overlap0();}
    const std::vector<int>& mus_overlap1() {return cms2.mus_overlap1();}
    const std::vector<int>& mus_pfcharge() {return cms2.mus_pfcharge();}
    const std::vector<int>& mus_pfflag() {return cms2.mus_pfflag();}
    const std::vector<int>& mus_pfparticleId() {return cms2.mus_pfparticleId();}
    const std::vector<int>& mus_pid_PFMuon() {return cms2.mus_pid_PFMuon();}
    const std::vector<int>& mus_pid_TM2DCompatibilityLoose() {return cms2.mus_pid_TM2DCompatibilityLoose();}
    const std::vector<int>& mus_pid_TM2DCompatibilityTight() {return cms2.mus_pid_TM2DCompatibilityTight();}
    const std::vector<int>& mus_pid_TMLastStationLoose() {return cms2.mus_pid_TMLastStationLoose();}
    const std::vector<int>& mus_pid_TMLastStationTight() {return cms2.mus_pid_TMLastStationTight();}
    const std::vector<int>& mus_sta_validHits() {return cms2.mus_sta_validHits();}
    const std::vector<int>& mus_timeDirection() {return cms2.mus_timeDirection();}
    const std::vector<int>& mus_timeNumStationsUsed() {return cms2.mus_timeNumStationsUsed();}
    const std::vector<int>& mus_trk_charge() {return cms2.mus_trk_charge();}
    const std::vector<int>& mus_trkidx() {return cms2.mus_trkidx();}
    const std::vector<int>& mus_type() {return cms2.mus_type();}
    const std::vector<int>& mus_validHits() {return cms2.mus_validHits();}
    const std::vector<int>& pfcands_charge() {return cms2.pfcands_charge();}
    const std::vector<int>& pfcands_flag() {return cms2.pfcands_flag();}
    const std::vector<int>& pfcands_particleId() {return cms2.pfcands_particleId();}
    const std::vector<int>& pfcands_pfelsidx() {return cms2.pfcands_pfelsidx();}
    const std::vector<int>& pfcands_pfmusidx() {return cms2.pfcands_pfmusidx();}
    const std::vector<int>& pfcands_trkidx() {return cms2.pfcands_trkidx();}
    const std::vector<int>& pfcands_vtxidx() {return cms2.pfcands_vtxidx();}
    const std::vector<int>& pfels_elsidx() {return cms2.pfels_elsidx();}
    const std::vector<int>& pfels_charge() {return cms2.pfels_charge();}
    const std::vector<int>& pfels_flag() {return cms2.pfels_flag();}
    const std::vector<int>& pfels_particleId() {return cms2.pfels_particleId();}
    const std::vector<int>& pfjets_chargedHadronMultiplicity() {return cms2.pfjets_chargedHadronMultiplicity();}
    const std::vector<int>& pfjets_chargedMultiplicity() {return cms2.pfjets_chargedMultiplicity();}
    const std::vector<int>& pfjets_electronMultiplicity() {return cms2.pfjets_electronMultiplicity();}
    const std::vector<int>& pfjets_hfEmMultiplicity() {return cms2.pfjets_hfEmMultiplicity();}
    const std::vector<int>& pfjets_hfHadronMultiplicity() {return cms2.pfjets_hfHadronMultiplicity();}
    const std::vector<int>& pfjets_muonMultiplicity() {return cms2.pfjets_muonMultiplicity();}
    const std::vector<int>& pfjets_neutralHadronMultiplicity() {return cms2.pfjets_neutralHadronMultiplicity();}
    const std::vector<int>& pfjets_neutralMultiplicity() {return cms2.pfjets_neutralMultiplicity();}
    const std::vector<int>& pfjets_photonMultiplicity() {return cms2.pfjets_photonMultiplicity();}
    const std::vector<int>& pfmus_musidx() {return cms2.pfmus_musidx();}
    const std::vector<int>& pfmus_charge() {return cms2.pfmus_charge();}
    const std::vector<int>& pfmus_flag() {return cms2.pfmus_flag();}
    const std::vector<int>& pfmus_particleId() {return cms2.pfmus_particleId();}
    const std::vector<int>& taus_pf_charge() {return cms2.taus_pf_charge();}
    const std::vector<int>& taus_pf_pfjetIndex() {return cms2.taus_pf_pfjetIndex();}
    const std::vector<int>& photons_fiduciality() {return cms2.photons_fiduciality();}
    const std::vector<int>& photons_scindex() {return cms2.photons_scindex();}
    const std::vector<int>& puInfo_bunchCrossing() {return cms2.puInfo_bunchCrossing();}
    const std::vector<int>& puInfo_nPUvertices() {return cms2.puInfo_nPUvertices();}
    const std::vector<int>& convs_algo() {return cms2.convs_algo();}
    const std::vector<int>& convs_isConverted() {return cms2.convs_isConverted();}
    const std::vector<int>& convs_quality() {return cms2.convs_quality();}
    const std::vector<int>& scs_detIdSeed() {return cms2.scs_detIdSeed();}
    const std::vector<int>& scs_elsidx() {return cms2.scs_elsidx();}
    const std::vector<int>& scs_severitySeed() {return cms2.scs_severitySeed();}
    const std::vector<int>& svs_isKs() {return cms2.svs_isKs();}
    const std::vector<int>& svs_isLambda() {return cms2.svs_isLambda();}
    const std::vector<int>& svs_mc3_id() {return cms2.svs_mc3_id();}
    const std::vector<int>& svs_nTrks() {return cms2.svs_nTrks();}
    const std::vector<int>& mus_tcmet_flag() {return cms2.mus_tcmet_flag();}
    const std::vector<int>& trks_algo() {return cms2.trks_algo();}
    const std::vector<int>& trks_charge() {return cms2.trks_charge();}
    const std::vector<int>& trks_exp_innerlayers() {return cms2.trks_exp_innerlayers();}
    const std::vector<int>& trks_exp_outerlayers() {return cms2.trks_exp_outerlayers();}
    const std::vector<int>& trks_layer1_det() {return cms2.trks_layer1_det();}
    const std::vector<int>& trks_layer1_layer() {return cms2.trks_layer1_layer();}
    const std::vector<int>& trks_layer1_sizerphi() {return cms2.trks_layer1_sizerphi();}
    const std::vector<int>& trks_layer1_sizerz() {return cms2.trks_layer1_sizerz();}
    const std::vector<int>& trks_lostHits() {return cms2.trks_lostHits();}
    const std::vector<int>& trks_lost_pixelhits() {return cms2.trks_lost_pixelhits();}
    const std::vector<int>& trks_nLoops() {return cms2.trks_nLoops();}
    const std::vector<int>& trks_nlayers() {return cms2.trks_nlayers();}
    const std::vector<int>& trks_nlayers3D() {return cms2.trks_nlayers3D();}
    const std::vector<int>& trks_nlayersLost() {return cms2.trks_nlayersLost();}
    const std::vector<int>& trks_pvidx0() {return cms2.trks_pvidx0();}
    const std::vector<int>& trks_pvidx1() {return cms2.trks_pvidx1();}
    const std::vector<int>& trks_qualityMask() {return cms2.trks_qualityMask();}
    const std::vector<int>& trks_validHits() {return cms2.trks_validHits();}
    const std::vector<int>& trks_valid_pixelhits() {return cms2.trks_valid_pixelhits();}
    const std::vector<int>& trks_elsidx() {return cms2.trks_elsidx();}
    const std::vector<int>& trk_musidx() {return cms2.trk_musidx();}
    const std::vector<int>& trkjets_ntrks() {return cms2.trkjets_ntrks();}
    const std::vector<int>& trkjets_vtxs_idx() {return cms2.trkjets_vtxs_idx();}
    const std::vector<int>& vtxs_isFake() {return cms2.vtxs_isFake();}
    const std::vector<int>& vtxs_isValid() {return cms2.vtxs_isValid();}
    const std::vector<int>& vtxs_tracksSize() {return cms2.vtxs_tracksSize();}
    const std::vector<int>& bsvtxs_isFake() {return cms2.bsvtxs_isFake();}
    const std::vector<int>& bsvtxs_isValid() {return cms2.bsvtxs_isValid();}
    const std::vector<int>& bsvtxs_tracksSize() {return cms2.bsvtxs_tracksSize();}
    const std::vector<std::vector<int> >& els_convs_delMissHits() {return cms2.els_convs_delMissHits();}
    const std::vector<std::vector<int> >& els_convs_flag() {return cms2.els_convs_flag();}
    const std::vector<std::vector<int> >& els_convs_gsftkidx() {return cms2.els_convs_gsftkidx();}
    const std::vector<std::vector<int> >& els_convs_tkidx() {return cms2.els_convs_tkidx();}
    const std::vector<std::vector<int> >& genps_lepdaughter_id() {return cms2.genps_lepdaughter_id();}
    const std::vector<std::vector<int> >& genps_lepdaughter_idx() {return cms2.genps_lepdaughter_idx();}
    const std::vector<std::vector<int> >& hlt_trigObjs_id() {return cms2.hlt_trigObjs_id();}
    const std::vector<std::vector<int> >& hyp_jets_idx() {return cms2.hyp_jets_idx();}
    const std::vector<std::vector<int> >& hyp_other_jets_idx() {return cms2.hyp_other_jets_idx();}
    const std::vector<std::vector<int> >& mus_nStationCorrelatedHits() {return cms2.mus_nStationCorrelatedHits();}
    const std::vector<std::vector<int> >& mus_nStationHits() {return cms2.mus_nStationHits();}
    const std::vector<std::vector<int> >& pfjets_pfcandIndicies() {return cms2.pfjets_pfcandIndicies();}
    const std::vector<std::vector<int> >& taus_pf_pfcandIndicies() {return cms2.taus_pf_pfcandIndicies();}
    const std::vector<std::vector<int> >& puInfo_ntrks_highpt() {return cms2.puInfo_ntrks_highpt();}
    const std::vector<std::vector<int> >& puInfo_ntrks_lowpt() {return cms2.puInfo_ntrks_lowpt();}
    const std::vector<std::vector<int> >& convs_nHitsBeforeVtx() {return cms2.convs_nHitsBeforeVtx();}
    const std::vector<std::vector<int> >& convs_tkalgo() {return cms2.convs_tkalgo();}
    const std::vector<std::vector<int> >& convs_tkidx() {return cms2.convs_tkidx();}
    const unsigned int& els_HLT_Ele17_Ele8_L1sL1DoubleEG137_version() {return cms2.els_HLT_Ele17_Ele8_L1sL1DoubleEG137_version();}
    const unsigned int& els_HLT_Ele17_Ele8_LeadingLeg_version() {return cms2.els_HLT_Ele17_Ele8_LeadingLeg_version();}
    const unsigned int& els_HLT_Ele17_Ele8_Mass50_LeadingLeg_version() {return cms2.els_HLT_Ele17_Ele8_Mass50_LeadingLeg_version();}
    const unsigned int& els_HLT_Ele17_Ele8_Mass50_TrailingLeg_version() {return cms2.els_HLT_Ele17_Ele8_Mass50_TrailingLeg_version();}
    const unsigned int& els_HLT_Ele17_Ele8_TrailingLeg_version() {return cms2.els_HLT_Ele17_Ele8_TrailingLeg_version();}
    const unsigned int& els_HLT_Ele17_Ele8_version() {return cms2.els_HLT_Ele17_Ele8_version();}
    const unsigned int& els_HLT_Ele20_SC4_Mass50_LeadingLeg_version() {return cms2.els_HLT_Ele20_SC4_Mass50_LeadingLeg_version();}
    const unsigned int& els_HLT_Ele20_SC4_Mass50_TrailingLeg_version() {return cms2.els_HLT_Ele20_SC4_Mass50_TrailingLeg_version();}
    const unsigned int& els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_version() {return cms2.els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_version();}
    const unsigned int& els_HLT_Ele27_WP80_version() {return cms2.els_HLT_Ele27_WP80_version();}
    const unsigned int& els_HLT_Ele32_SC17_Mass50_LeadingLeg_version() {return cms2.els_HLT_Ele32_SC17_Mass50_LeadingLeg_version();}
    const unsigned int& els_HLT_Ele32_SC17_Mass50_TrailingLeg_version() {return cms2.els_HLT_Ele32_SC17_Mass50_TrailingLeg_version();}
    const unsigned int& els_HLT_Mu17_Ele8_TrailingLeg_version() {return cms2.els_HLT_Mu17_Ele8_TrailingLeg_version();}
    const unsigned int& els_HLT_Mu17_Ele8_version() {return cms2.els_HLT_Mu17_Ele8_version();}
    const unsigned int& els_HLT_Mu8_Ele17_version() {return cms2.els_HLT_Mu8_Ele17_version();}
    const unsigned int& evt_nels() {return cms2.evt_nels();}
    const unsigned int& evt_detectorStatus() {return cms2.evt_detectorStatus();}
    const unsigned int& evt_event() {return cms2.evt_event();}
    const unsigned int& evt_lumiBlock() {return cms2.evt_lumiBlock();}
    const unsigned int& evt_run() {return cms2.evt_run();}
    const unsigned int& genps_flavorHistoryFilterResult() {return cms2.genps_flavorHistoryFilterResult();}
    const unsigned int& evt_ngenjets() {return cms2.evt_ngenjets();}
    const unsigned int& genps_signalProcessID() {return cms2.genps_signalProcessID();}
    const unsigned int& evt_njets() {return cms2.evt_njets();}
    const unsigned int& l1_bits1() {return cms2.l1_bits1();}
    const unsigned int& l1_bits2() {return cms2.l1_bits2();}
    const unsigned int& l1_bits3() {return cms2.l1_bits3();}
    const unsigned int& l1_bits4() {return cms2.l1_bits4();}
    const unsigned int& l1_techbits1() {return cms2.l1_techbits1();}
    const unsigned int& l1_techbits2() {return cms2.l1_techbits2();}
    const unsigned int& ls_lsNumber() {return cms2.ls_lsNumber();}
    const unsigned int& ls_numOrbit() {return cms2.ls_numOrbit();}
    const unsigned int& ls_startOrbit() {return cms2.ls_startOrbit();}
    const unsigned int& mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_version() {return cms2.mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_version();}
    const unsigned int& mus_HLT_IsoMu24_eta2p1_version() {return cms2.mus_HLT_IsoMu24_eta2p1_version();}
    const unsigned int& mus_HLT_Mu17_Ele8_LeadingLeg_version() {return cms2.mus_HLT_Mu17_Ele8_LeadingLeg_version();}
    const unsigned int& mus_HLT_Mu17_Ele8_version() {return cms2.mus_HLT_Mu17_Ele8_version();}
    const unsigned int& mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_version() {return cms2.mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_version();}
    const unsigned int& mus_HLT_Mu17_Mu8_LeadingLeg_version() {return cms2.mus_HLT_Mu17_Mu8_LeadingLeg_version();}
    const unsigned int& mus_HLT_Mu17_Mu8_TrailingLeg_version() {return cms2.mus_HLT_Mu17_Mu8_TrailingLeg_version();}
    const unsigned int& mus_HLT_Mu17_Mu8_version() {return cms2.mus_HLT_Mu17_Mu8_version();}
    const unsigned int& mus_HLT_Mu17_TkMu8_LeadingLeg_version() {return cms2.mus_HLT_Mu17_TkMu8_LeadingLeg_version();}
    const unsigned int& mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_version() {return cms2.mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_version();}
    const unsigned int& mus_HLT_Mu17_TkMu8_TrailingLeg_version() {return cms2.mus_HLT_Mu17_TkMu8_TrailingLeg_version();}
    const unsigned int& mus_HLT_Mu17_TkMu8_version() {return cms2.mus_HLT_Mu17_TkMu8_version();}
    const unsigned int& mus_HLT_Mu8_Ele17_TrailingLeg_version() {return cms2.mus_HLT_Mu8_Ele17_TrailingLeg_version();}
    const unsigned int& mus_HLT_Mu8_Ele17_version() {return cms2.mus_HLT_Mu8_Ele17_version();}
    const unsigned int& evt_nphotons() {return cms2.evt_nphotons();}
    const unsigned int& evt_ecalRecoStatus() {return cms2.evt_ecalRecoStatus();}
    const unsigned int& evt_nscs() {return cms2.evt_nscs();}
    const unsigned int& evt_ntrkjets() {return cms2.evt_ntrkjets();}
    const unsigned int& evt_nvtxs() {return cms2.evt_nvtxs();}
    const unsigned int& evt_nbsvtxs() {return cms2.evt_nbsvtxs();}
    const std::vector<unsigned int>& els_HLT_Ele17_Ele8() {return cms2.els_HLT_Ele17_Ele8();}
    const std::vector<unsigned int>& els_HLT_Ele17_Ele8_L1sL1DoubleEG137() {return cms2.els_HLT_Ele17_Ele8_L1sL1DoubleEG137();}
    const std::vector<unsigned int>& els_HLT_Ele17_Ele8_LeadingLeg() {return cms2.els_HLT_Ele17_Ele8_LeadingLeg();}
    const std::vector<unsigned int>& els_HLT_Ele17_Ele8_Mass50_LeadingLeg() {return cms2.els_HLT_Ele17_Ele8_Mass50_LeadingLeg();}
    const std::vector<unsigned int>& els_HLT_Ele17_Ele8_Mass50_TrailingLeg() {return cms2.els_HLT_Ele17_Ele8_Mass50_TrailingLeg();}
    const std::vector<unsigned int>& els_HLT_Ele17_Ele8_TrailingLeg() {return cms2.els_HLT_Ele17_Ele8_TrailingLeg();}
    const std::vector<unsigned int>& els_HLT_Ele20_SC4_Mass50_LeadingLeg() {return cms2.els_HLT_Ele20_SC4_Mass50_LeadingLeg();}
    const std::vector<unsigned int>& els_HLT_Ele20_SC4_Mass50_TrailingLeg() {return cms2.els_HLT_Ele20_SC4_Mass50_TrailingLeg();}
    const std::vector<unsigned int>& els_HLT_Ele27_WP80() {return cms2.els_HLT_Ele27_WP80();}
    const std::vector<unsigned int>& els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22() {return cms2.els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22();}
    const std::vector<unsigned int>& els_HLT_Ele32_SC17_Mass50_LeadingLeg() {return cms2.els_HLT_Ele32_SC17_Mass50_LeadingLeg();}
    const std::vector<unsigned int>& els_HLT_Ele32_SC17_Mass50_TrailingLeg() {return cms2.els_HLT_Ele32_SC17_Mass50_TrailingLeg();}
    const std::vector<unsigned int>& els_HLT_Mu17_Ele8() {return cms2.els_HLT_Mu17_Ele8();}
    const std::vector<unsigned int>& els_HLT_Mu17_Ele8_TrailingLeg() {return cms2.els_HLT_Mu17_Ele8_TrailingLeg();}
    const std::vector<unsigned int>& els_HLT_Mu8_Ele17() {return cms2.els_HLT_Mu8_Ele17();}
    const std::vector<unsigned int>& els_id2012ext_loose() {return cms2.els_id2012ext_loose();}
    const std::vector<unsigned int>& els_id2012ext_medium() {return cms2.els_id2012ext_medium();}
    const std::vector<unsigned int>& els_id2012ext_tight() {return cms2.els_id2012ext_tight();}
    const std::vector<unsigned int>& els_id2012ext_veto() {return cms2.els_id2012ext_veto();}
    const std::vector<unsigned int>& els_id2012_loose() {return cms2.els_id2012_loose();}
    const std::vector<unsigned int>& els_id2012_medium() {return cms2.els_id2012_medium();}
    const std::vector<unsigned int>& els_id2012_tight() {return cms2.els_id2012_tight();}
    const std::vector<unsigned int>& els_id2012_veto() {return cms2.els_id2012_veto();}
    const std::vector<unsigned int>& hlt_prescales() {return cms2.hlt_prescales();}
    const std::vector<unsigned int>& l1_prescales() {return cms2.l1_prescales();}
    const std::vector<unsigned int>& l1_techtrigprescales() {return cms2.l1_techtrigprescales();}
    const std::vector<unsigned int>& mus_HLT_IsoMu24_eta2p1() {return cms2.mus_HLT_IsoMu24_eta2p1();}
    const std::vector<unsigned int>& mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1() {return cms2.mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1();}
    const std::vector<unsigned int>& mus_HLT_Mu17_Ele8() {return cms2.mus_HLT_Mu17_Ele8();}
    const std::vector<unsigned int>& mus_HLT_Mu17_Ele8_LeadingLeg() {return cms2.mus_HLT_Mu17_Ele8_LeadingLeg();}
    const std::vector<unsigned int>& mus_HLT_Mu17_Mu8() {return cms2.mus_HLT_Mu17_Mu8();}
    const std::vector<unsigned int>& mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen() {return cms2.mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen();}
    const std::vector<unsigned int>& mus_HLT_Mu17_Mu8_LeadingLeg() {return cms2.mus_HLT_Mu17_Mu8_LeadingLeg();}
    const std::vector<unsigned int>& mus_HLT_Mu17_Mu8_TrailingLeg() {return cms2.mus_HLT_Mu17_Mu8_TrailingLeg();}
    const std::vector<unsigned int>& mus_HLT_Mu17_TkMu8() {return cms2.mus_HLT_Mu17_TkMu8();}
    const std::vector<unsigned int>& mus_HLT_Mu17_TkMu8_LeadingLeg() {return cms2.mus_HLT_Mu17_TkMu8_LeadingLeg();}
    const std::vector<unsigned int>& mus_HLT_Mu17_TkMu8_TrailingLeg() {return cms2.mus_HLT_Mu17_TkMu8_TrailingLeg();}
    const std::vector<unsigned int>& mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered() {return cms2.mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered();}
    const std::vector<unsigned int>& mus_HLT_Mu8_Ele17() {return cms2.mus_HLT_Mu8_Ele17();}
    const std::vector<unsigned int>& mus_HLT_Mu8_Ele17_TrailingLeg() {return cms2.mus_HLT_Mu8_Ele17_TrailingLeg();}
    const unsigned long long& evt_timestamp() {return cms2.evt_timestamp();}
    const int& evt_nEvts() {return cms2.evt_nEvts();}
    const float& evt_filt_eff() {return cms2.evt_filt_eff();}

} // namespace tas



// ################################################################################################# //
// CMSSW complient
// ################################################################################################# //
#else

CMS2::CMS2()
    : hlt_bits_handle("hltMaker", "hltbits")
    , evt_CMS2tag_handle("eventMaker", "evtCMS2tag")
    , evt_dataset_handle("eventMaker", "evtdataset")
    , hlt_trigNames_handle("hltMaker", "hlttrigNames")
    , l1_techtrigNames_handle("l1Maker", "l1techtrigNames")
    , l1_trigNames_handle("l1Maker", "l1trigNames")
    , evt_errCategory_handle("recoErrorLogMaker", "evterrCategory")
    , evt_errModule_handle("recoErrorLogMaker", "evterrModule")
    , evt_errSeverity_handle("recoErrorLogMaker", "evterrSeverity")
    , sparm_comment_handle("sParmMaker", "sparmcomment")
    , sparm_names_handle("sParmMaker", "sparmnames")
    , evt_eventHasHalo_handle("beamHaloMaker", "evteventHasHalo")
    , hcalnoise_HasBadRBXTS4TS5_handle("hcalNoiseSummaryMaker", "hcalnoiseHasBadRBXTS4TS5")
    , ls_isValid_handle("luminosityMaker", "lsisValid")
    , filt_ecalBE_handle("metFilterMaker", "filtecalBE")
    , filt_ecalDR_handle("metFilterMaker", "filtecalDR")
    , filt_ecalLaser_handle("metFilterMaker", "filtecalLaser")
    , filt_ecalTP_handle("metFilterMaker", "filtecalTP")
    , filt_eeBadSc_handle("metFilterMaker", "filteeBadSc")
    , filt_greedyMuon_handle("metFilterMaker", "filtgreedyMuon")
    , filt_hcalLaser_handle("metFilterMaker", "filthcalLaser")
    , filt_inconsistentMuon_handle("metFilterMaker", "filtinconsistentMuon")
    , filt_jetIDFailure_handle("metFilterMaker", "filtjetIDFailure")
    , filt_multiEvent_handle("metFilterMaker", "filtmultiEvent")
    , filt_trackingFailure_handle("metFilterMaker", "filttrackingFailure")
    , evt_hbheFilter_handle("metMaker", "evthbheFilter")
    , els_conv_vtx_flag_handle("electronMaker", "elsconvvtxflag")
    , els_passingMvaPreselection_handle("electronMaker", "elspassingMvaPreselection")
    , els_passingPflowPreselection_handle("electronMaker", "elspassingPflowPreselection")
    , mus_isRPCMuon_handle("muonMaker", "musisRPCMuon")
    , mus_tightMatch_handle("muonMaker", "mustightMatch")
    , mus_updatedSta_handle("muonMaker", "musupdatedSta")
    , pfcands_isMuIso_handle("pfCandidateMaker", "pfcandsisMuIso")
    , photons_haspixelSeed_handle("photonMaker", "photonshaspixelSeed")
    , jets_closestElectron_DR_handle("jetToElAssMaker", "jetsclosestElectronDR")
    , jets_closestMuon_DR_handle("jetToMuAssMaker", "jetsclosestMuonDR")
    , evt_bs_Xwidth_handle("beamSpotMaker", "evtbsXwidth")
    , evt_bs_XwidthErr_handle("beamSpotMaker", "evtbsXwidthErr")
    , evt_bs_Ywidth_handle("beamSpotMaker", "evtbsYwidth")
    , evt_bs_YwidthErr_handle("beamSpotMaker", "evtbsYwidthErr")
    , evt_bs_dxdz_handle("beamSpotMaker", "evtbsdxdz")
    , evt_bs_dxdzErr_handle("beamSpotMaker", "evtbsdxdzErr")
    , evt_bs_dydz_handle("beamSpotMaker", "evtbsdydz")
    , evt_bs_dydzErr_handle("beamSpotMaker", "evtbsdydzErr")
    , evt_bs_sigmaZ_handle("beamSpotMaker", "evtbssigmaZ")
    , evt_bs_sigmaZErr_handle("beamSpotMaker", "evtbssigmaZErr")
    , evt_bs_xErr_handle("beamSpotMaker", "evtbsxErr")
    , evt_bs_yErr_handle("beamSpotMaker", "evtbsyErr")
    , evt_bs_zErr_handle("beamSpotMaker", "evtbszErr")
    , evt_bField_handle("eventMaker", "evtbField")
    , evt_rho_handle("fastJetMaker", "evtrho")
    , evt_rhoJEC_handle("fastJetMaker", "evtrhoJEC")
    , evt_fixgrid_all_rho_handle("fixedGridRhoAllMaker", "evtfixgridallrho")
    , evt_fixgridfastjet_all_rho_handle("fixedGridRhoFastJetAllMaker", "evtfixgridfastjetallrho")
    , gen_met_handle("genMaker", "genmet")
    , gen_metPhi_handle("genMaker", "genmetPhi")
    , genps_alphaQCD_handle("genMaker", "genpsalphaQCD")
    , genps_pthat_handle("genMaker", "genpspthat")
    , genps_qScale_handle("genMaker", "genpsqScale")
    , genps_weight_handle("genMaker", "genpsweight")
    , gen_sumEt_handle("genMaker", "gensumEt")
    , hcalnoise_GetRecHitEnergy_handle("hcalNoiseSummaryMaker", "hcalnoiseGetRecHitEnergy")
    , hcalnoise_GetRecHitEnergy15_handle("hcalNoiseSummaryMaker", "hcalnoiseGetRecHitEnergy15")
    , hcalnoise_GetTotalCalibCharge_handle("hcalNoiseSummaryMaker", "hcalnoiseGetTotalCalibCharge")
    , hcalnoise_TS4TS5NoiseSumE_handle("hcalNoiseSummaryMaker", "hcalnoiseTS4TS5NoiseSumE")
    , hcalnoise_TS4TS5NoiseSumEt_handle("hcalNoiseSummaryMaker", "hcalnoiseTS4TS5NoiseSumEt")
    , hcalnoise_eventChargeFraction_handle("hcalNoiseSummaryMaker", "hcalnoiseeventChargeFraction")
    , hcalnoise_eventEMEnergy_handle("hcalNoiseSummaryMaker", "hcalnoiseeventEMEnergy")
    , hcalnoise_eventEMFraction_handle("hcalNoiseSummaryMaker", "hcalnoiseeventEMFraction")
    , hcalnoise_eventHadEnergy_handle("hcalNoiseSummaryMaker", "hcalnoiseeventHadEnergy")
    , hcalnoise_eventTrackEnergy_handle("hcalNoiseSummaryMaker", "hcalnoiseeventTrackEnergy")
    , hcalnoise_flatNoiseSumE_handle("hcalNoiseSummaryMaker", "hcalnoiseflatNoiseSumE")
    , hcalnoise_flatNoiseSumEt_handle("hcalNoiseSummaryMaker", "hcalnoiseflatNoiseSumEt")
    , hcalnoise_isolatedNoiseSumE_handle("hcalNoiseSummaryMaker", "hcalnoiseisolatedNoiseSumE")
    , hcalnoise_isolatedNoiseSumEt_handle("hcalNoiseSummaryMaker", "hcalnoiseisolatedNoiseSumEt")
    , hcalnoise_max10GeVHitTime_handle("hcalNoiseSummaryMaker", "hcalnoisemax10GeVHitTime")
    , hcalnoise_max25GeVHitTime_handle("hcalNoiseSummaryMaker", "hcalnoisemax25GeVHitTime")
    , hcalnoise_maxE10TS_handle("hcalNoiseSummaryMaker", "hcalnoisemaxE10TS")
    , hcalnoise_maxE2Over10TS_handle("hcalNoiseSummaryMaker", "hcalnoisemaxE2Over10TS")
    , hcalnoise_maxE2TS_handle("hcalNoiseSummaryMaker", "hcalnoisemaxE2TS")
    , hcalnoise_min10GeVHitTime_handle("hcalNoiseSummaryMaker", "hcalnoisemin10GeVHitTime")
    , hcalnoise_min25GeVHitTime_handle("hcalNoiseSummaryMaker", "hcalnoisemin25GeVHitTime")
    , hcalnoise_minE10TS_handle("hcalNoiseSummaryMaker", "hcalnoiseminE10TS")
    , hcalnoise_minE2Over10TS_handle("hcalNoiseSummaryMaker", "hcalnoiseminE2Over10TS")
    , hcalnoise_minE2TS_handle("hcalNoiseSummaryMaker", "hcalnoiseminE2TS")
    , hcalnoise_minHPDEMF_handle("hcalNoiseSummaryMaker", "hcalnoiseminHPDEMF")
    , hcalnoise_minRBXEMF_handle("hcalNoiseSummaryMaker", "hcalnoiseminRBXEMF")
    , hcalnoise_rms10GeVHitTime_handle("hcalNoiseSummaryMaker", "hcalnoiserms10GeVHitTime")
    , hcalnoise_rms25GeVHitTime_handle("hcalNoiseSummaryMaker", "hcalnoiserms25GeVHitTime")
    , hcalnoise_spikeNoiseSumE_handle("hcalNoiseSummaryMaker", "hcalnoisespikeNoiseSumE")
    , hcalnoise_spikeNoiseSumEt_handle("hcalNoiseSummaryMaker", "hcalnoisespikeNoiseSumEt")
    , hcalnoise_triangleNoiseSumE_handle("hcalNoiseSummaryMaker", "hcalnoisetriangleNoiseSumE")
    , hcalnoise_triangleNoiseSumEt_handle("hcalNoiseSummaryMaker", "hcalnoisetriangleNoiseSumEt")
    , evt_kt6calo_central_rho_handle("kt6CaloJetsCentralRhoMaker", "evtkt6calocentralrho")
    , evt_kt6calo_muhlt_rho_handle("kt6CaloJetsForMuHLTRhoMaker", "evtkt6calomuhltrho")
    , evt_kt6calo_rho_handle("kt6CaloJetsRhoMaker", "evtkt6calorho")
    , evt_kt6pf_ctrChargedPU_rho_handle("kt6PFJetsCentralChargedPileUpRhoMaker", "evtkt6pfctrChargedPUrho")
    , evt_kt6pf_ctrNeutral_rho_handle("kt6PFJetsCentralNeutralRhoMaker", "evtkt6pfctrNeutralrho")
    , evt_kt6pf_ctrNeutralTight_rho_handle("kt6PFJetsCentralNeutralTightRhoMaker", "evtkt6pfctrNeutralTightrho")
    , evt_kt6pf_foregiso_rho_handle("kt6PFJetsForEGIsolationRhoMaker", "evtkt6pfforegisorho")
    , l1_met_etTot_handle("l1Maker", "l1metetTot")
    , l1_met_met_handle("l1Maker", "l1metmet")
    , l1_mht_htTot_handle("l1Maker", "l1mhthtTot")
    , l1_mht_mht_handle("l1Maker", "l1mhtmht")
    , ls_avgInsDelLumi_handle("luminosityMaker", "lsavgInsDelLumi")
    , ls_avgInsDelLumiErr_handle("luminosityMaker", "lsavgInsDelLumiErr")
    , ls_avgInsRecLumi_handle("luminosityMaker", "lsavgInsRecLumi")
    , ls_avgInsRecLumiErr_handle("luminosityMaker", "lsavgInsRecLumiErr")
    , ls_deadFrac_handle("luminosityMaker", "lsdeadFrac")
    , ls_intgDelLumi_handle("luminosityMaker", "lsintgDelLumi")
    , ls_intgRecLumi_handle("luminosityMaker", "lsintgRecLumi")
    , ls_lumiSectionLength_handle("luminosityMaker", "lslumiSectionLength")
    , evt_ecalendcapm_met_handle("metMaker", "evtecalendcapmmet")
    , evt_ecalendcapm_metPhi_handle("metMaker", "evtecalendcapmmetPhi")
    , evt_ecalendcapp_met_handle("metMaker", "evtecalendcappmet")
    , evt_ecalendcapp_metPhi_handle("metMaker", "evtecalendcappmetPhi")
    , evt_ecalmet_handle("metMaker", "evtecalmet")
    , evt_ecalmetPhi_handle("metMaker", "evtecalmetPhi")
    , evt_endcapm_met_handle("metMaker", "evtendcapmmet")
    , evt_endcapm_metPhi_handle("metMaker", "evtendcapmmetPhi")
    , evt_endcapp_met_handle("metMaker", "evtendcappmet")
    , evt_endcapp_metPhi_handle("metMaker", "evtendcappmetPhi")
    , evt_hcalendcapm_met_handle("metMaker", "evthcalendcapmmet")
    , evt_hcalendcapm_metPhi_handle("metMaker", "evthcalendcapmmetPhi")
    , evt_hcalendcapp_met_handle("metMaker", "evthcalendcappmet")
    , evt_hcalendcapp_metPhi_handle("metMaker", "evthcalendcappmetPhi")
    , evt_hcalmet_handle("metMaker", "evthcalmet")
    , evt_hcalmetPhi_handle("metMaker", "evthcalmetPhi")
    , evt_met_handle("metMaker", "evtmet")
    , evt_met_EtGt3_handle("metMaker", "evtmetEtGt3")
    , evt_metHO_handle("metMaker", "evtmetHO")
    , evt_metHOPhi_handle("metMaker", "evtmetHOPhi")
    , evt_metHOSig_handle("metMaker", "evtmetHOSig")
    , evt_metMuonCorr_handle("metMaker", "evtmetMuonCorr")
    , evt_metMuonCorrPhi_handle("metMaker", "evtmetMuonCorrPhi")
    , evt_metMuonCorrSig_handle("metMaker", "evtmetMuonCorrSig")
    , evt_metMuonJESCorr_handle("metMaker", "evtmetMuonJESCorr")
    , evt_metMuonJESCorrPhi_handle("metMaker", "evtmetMuonJESCorrPhi")
    , evt_metMuonJESCorrSig_handle("metMaker", "evtmetMuonJESCorrSig")
    , evt_metNoHF_handle("metMaker", "evtmetNoHF")
    , evt_metNoHFHO_handle("metMaker", "evtmetNoHFHO")
    , evt_metNoHFHOPhi_handle("metMaker", "evtmetNoHFHOPhi")
    , evt_metNoHFHOSig_handle("metMaker", "evtmetNoHFHOSig")
    , evt_metNoHFPhi_handle("metMaker", "evtmetNoHFPhi")
    , evt_metNoHFSig_handle("metMaker", "evtmetNoHFSig")
    , evt_metOpt_handle("metMaker", "evtmetOpt")
    , evt_metOptHO_handle("metMaker", "evtmetOptHO")
    , evt_metOptHOPhi_handle("metMaker", "evtmetOptHOPhi")
    , evt_metOptHOSig_handle("metMaker", "evtmetOptHOSig")
    , evt_metOptNoHF_handle("metMaker", "evtmetOptNoHF")
    , evt_metOptNoHFHO_handle("metMaker", "evtmetOptNoHFHO")
    , evt_metOptNoHFHOPhi_handle("metMaker", "evtmetOptNoHFHOPhi")
    , evt_metOptNoHFHOSig_handle("metMaker", "evtmetOptNoHFHOSig")
    , evt_metOptNoHFPhi_handle("metMaker", "evtmetOptNoHFPhi")
    , evt_metOptNoHFSig_handle("metMaker", "evtmetOptNoHFSig")
    , evt_metOptPhi_handle("metMaker", "evtmetOptPhi")
    , evt_metOptSig_handle("metMaker", "evtmetOptSig")
    , evt_metPhi_handle("metMaker", "evtmetPhi")
    , evt_metPhi_EtGt3_handle("metMaker", "evtmetPhiEtGt3")
    , evt_metSig_handle("metMaker", "evtmetSig")
    , evt_sumet_handle("metMaker", "evtsumet")
    , evt_sumet_EtGt3_handle("metMaker", "evtsumetEtGt3")
    , evt_sumetHO_handle("metMaker", "evtsumetHO")
    , evt_sumetMuonCorr_handle("metMaker", "evtsumetMuonCorr")
    , evt_sumetMuonJESCorr_handle("metMaker", "evtsumetMuonJESCorr")
    , evt_sumetNoHF_handle("metMaker", "evtsumetNoHF")
    , evt_sumetNoHFHO_handle("metMaker", "evtsumetNoHFHO")
    , evt_sumetOpt_handle("metMaker", "evtsumetOpt")
    , evt_sumetOptHO_handle("metMaker", "evtsumetOptHO")
    , evt_sumetOptNoHF_handle("metMaker", "evtsumetOptNoHF")
    , evt_sumetOptNoHFHO_handle("metMaker", "evtsumetOptNoHFHO")
    , pdfinfo_pdf1_handle("pdfinfoMaker", "pdfinfopdf1")
    , pdfinfo_pdf2_handle("pdfinfoMaker", "pdfinfopdf2")
    , pdfinfo_scale_handle("pdfinfoMaker", "pdfinfoscale")
    , pdfinfo_x1_handle("pdfinfoMaker", "pdfinfox1")
    , pdfinfo_x2_handle("pdfinfoMaker", "pdfinfox2")
    , evt_fixgrid_rho_all_handle("pfCandidateMaker", "evtfixgridrhoall")
    , evt_fixgrid_rho_ctr_handle("pfCandidateMaker", "evtfixgridrhoctr")
    , evt_fixgrid_rho_fwd_handle("pfCandidateMaker", "evtfixgridrhofwd")
    , evt_pfmet_handle("pfmetMaker", "evtpfmet")
    , evt_pfmetPhi_handle("pfmetMaker", "evtpfmetPhi")
    , evt_pfmetPhi_type1cor_handle("pfmetMaker", "evtpfmetPhitype1cor")
    , evt_pfmetSig_handle("pfmetMaker", "evtpfmetSig")
    , evt_pfmetSignificance_handle("pfmetMaker", "evtpfmetSignificance")
    , evt_pfmet_type1cor_handle("pfmetMaker", "evtpfmettype1cor")
    , evt_pfsumet_handle("pfmetMaker", "evtpfsumet")
    , sparm_filterEfficiency_handle("sParmMaker", "sparmfilterEfficiency")
    , sparm_pdfScale_handle("sParmMaker", "sparmpdfScale")
    , sparm_pdfWeight1_handle("sParmMaker", "sparmpdfWeight1")
    , sparm_pdfWeight2_handle("sParmMaker", "sparmpdfWeight2")
    , sparm_weight_handle("sParmMaker", "sparmweight")
    , sparm_xsec_handle("sParmMaker", "sparmxsec")
    , evt_pf_tcmet_handle("tcmetMaker", "evtpftcmet")
    , evt_pf_tcmetPhi_handle("tcmetMaker", "evtpftcmetPhi")
    , evt_pf_tcmetSig_handle("tcmetMaker", "evtpftcmetSig")
    , evt_pf_tcsumet_handle("tcmetMaker", "evtpftcsumet")
    , evt_tcmet_handle("tcmetMaker", "evttcmet")
    , evt_tcmetPhi_handle("tcmetMaker", "evttcmetPhi")
    , evt_tcmetSig_handle("tcmetMaker", "evttcmetSig")
    , evt_tcsumet_handle("tcmetMaker", "evttcsumet")
    , evt_ww_rho_act_handle("wwRhoActiveAreaMaker", "evtwwrhoact")
    , evt_ww_rho_handle("wwRhoDefaultMaker", "evtwwrho")
    , evt_ww_rho_rnd_handle("wwRhoRandomMaker", "evtwwrhornd")
    , evt_ww_rho_vor_handle("wwRhoVoronoiMaker", "evtwwrhovor")
    , evt_bsp4_handle("beamSpotMaker", "evtbsp4")
    , l1_met_p4_handle("l1Maker", "l1metp4")
    , l1_mht_p4_handle("l1Maker", "l1mhtp4")
    , els_mc_motherp4_handle("candToGenAssMaker", "elsmcmotherp4")
    , els_mc_p4_handle("candToGenAssMaker", "elsmcp4")
    , jets_mc_gp_p4_handle("candToGenAssMaker", "jetsmcgpp4")
    , jets_mc_motherp4_handle("candToGenAssMaker", "jetsmcmotherp4")
    , jets_mc_p4_handle("candToGenAssMaker", "jetsmcp4")
    , mus_mc_motherp4_handle("candToGenAssMaker", "musmcmotherp4")
    , mus_mc_p4_handle("candToGenAssMaker", "musmcp4")
    , pfjets_mc_gp_p4_handle("candToGenAssMaker", "pfjetsmcgpp4")
    , pfjets_mc_motherp4_handle("candToGenAssMaker", "pfjetsmcmotherp4")
    , pfjets_mc_p4_handle("candToGenAssMaker", "pfjetsmcp4")
    , photons_mc_motherp4_handle("candToGenAssMaker", "photonsmcmotherp4")
    , photons_mc_p4_handle("candToGenAssMaker", "photonsmcp4")
    , trk_mcp4_handle("candToGenAssMaker", "trkmcp4")
    , els_conv_pos_p4_handle("electronMaker", "elsconvposp4")
    , els_inner_position_handle("electronMaker", "elsinnerposition")
    , els_outer_position_handle("electronMaker", "elsouterposition")
    , els_p4_handle("electronMaker", "elsp4")
    , els_p4In_handle("electronMaker", "elsp4In")
    , els_p4Out_handle("electronMaker", "elsp4Out")
    , els_trk_p4_handle("electronMaker", "elstrkp4")
    , els_vertex_p4_handle("electronMaker", "elsvertexp4")
    , genjets_p4_handle("genJetMaker", "genjetsp4")
    , genps_p4_handle("genMaker", "genpsp4")
    , genps_prod_vtx_handle("genMaker", "genpsprodvtx")
    , gsftrks_inner_position_handle("gsfTrackMaker", "gsftrksinnerposition")
    , gsftrks_outer_p4_handle("gsfTrackMaker", "gsftrksouterp4")
    , gsftrks_outer_position_handle("gsfTrackMaker", "gsftrksouterposition")
    , gsftrks_p4_handle("gsfTrackMaker", "gsftrksp4")
    , gsftrks_vertex_p4_handle("gsfTrackMaker", "gsftrksvertexp4")
    , hyp_ll_p4_handle("hypDilepMaker", "hypllp4")
    , hyp_ll_trk_p4_handle("hypDilepMaker", "hyplltrkp4")
    , hyp_lt_p4_handle("hypDilepMaker", "hypltp4")
    , hyp_lt_trk_p4_handle("hypDilepMaker", "hyplttrkp4")
    , hyp_p4_handle("hypDilepMaker", "hypp4")
    , hyp_FVFit_p4_handle("hypDilepVertexMaker", "hypFVFitp4")
    , hyp_FVFit_v4_handle("hypDilepVertexMaker", "hypFVFitv4")
    , hyp_ll_mc_p4_handle("hypGenMaker", "hypllmcp4")
    , hyp_lt_mc_p4_handle("hypGenMaker", "hypltmcp4")
    , jets_p4_handle("jetMaker", "jetsp4")
    , jets_vertex_p4_handle("jetMaker", "jetsvertexp4")
    , l1_emiso_p4_handle("l1Maker", "l1emisop4")
    , l1_emnoiso_p4_handle("l1Maker", "l1emnoisop4")
    , l1_jetsc_p4_handle("l1Maker", "l1jetscp4")
    , l1_jetsf_p4_handle("l1Maker", "l1jetsfp4")
    , l1_jetst_p4_handle("l1Maker", "l1jetstp4")
    , l1_mus_p4_handle("l1Maker", "l1musp4")
    , mus_ecalpos_p4_handle("muonMaker", "musecalposp4")
    , mus_fitpicky_p4_handle("muonMaker", "musfitpickyp4")
    , mus_fittev_p4_handle("muonMaker", "musfittevp4")
    , mus_fittpfms_p4_handle("muonMaker", "musfittpfmsp4")
    , mus_gfit_outerPos_p4_handle("muonMaker", "musgfitouterPosp4")
    , mus_gfit_p4_handle("muonMaker", "musgfitp4")
    , mus_gfit_vertex_p4_handle("muonMaker", "musgfitvertexp4")
    , mus_p4_handle("muonMaker", "musp4")
    , mus_pfp4_handle("muonMaker", "muspfp4")
    , mus_pfposAtEcal_p4_handle("muonMaker", "muspfposAtEcalp4")
    , mus_sta_p4_handle("muonMaker", "musstap4")
    , mus_sta_vertex_p4_handle("muonMaker", "musstavertexp4")
    , mus_trk_p4_handle("muonMaker", "mustrkp4")
    , mus_vertex_p4_handle("muonMaker", "musvertexp4")
    , pfcands_p4_handle("pfCandidateMaker", "pfcandsp4")
    , pfcands_posAtEcal_p4_handle("pfCandidateMaker", "pfcandsposAtEcalp4")
    , pfels_p4_handle("pfElectronMaker", "pfelsp4")
    , pfels_posAtEcal_p4_handle("pfElectronMaker", "pfelsposAtEcalp4")
    , pfjets_p4_handle("pfJetMaker", "pfjetsp4")
    , pfmus_p4_handle("pfMuonMaker", "pfmusp4")
    , pfmus_posAtEcal_p4_handle("pfMuonMaker", "pfmusposAtEcalp4")
    , taus_pf_p4_handle("pftauMaker", "tauspfp4")
    , photons_p4_handle("photonMaker", "photonsp4")
    , convs_refitPairMom_p4_handle("recoConversionMaker", "convsrefitPairMomp4")
    , convs_vtxpos_handle("recoConversionMaker", "convsvtxpos")
    , scs_p4_handle("scMaker", "scsp4")
    , scs_pos_p4_handle("scMaker", "scsposp4")
    , scs_vtx_p4_handle("scMaker", "scsvtxp4")
    , svs_flight_handle("secondaryVertexMaker", "svsflight")
    , svs_mc3_p4_handle("secondaryVertexMaker", "svsmc3p4")
    , svs_p4_handle("secondaryVertexMaker", "svsp4")
    , svs_position_handle("secondaryVertexMaker", "svsposition")
    , svs_refitp4_handle("secondaryVertexMaker", "svsrefitp4")
    , trks_inner_position_handle("trackMaker", "trksinnerposition")
    , trks_outer_p4_handle("trackMaker", "trksouterp4")
    , trks_outer_position_handle("trackMaker", "trksouterposition")
    , trks_trk_p4_handle("trackMaker", "trkstrkp4")
    , trks_vertex_p4_handle("trackMaker", "trksvertexp4")
    , trkjets_p4_handle("trkJetMaker", "trkjetsp4")
    , vtxs_position_handle("vertexMaker", "vtxsposition")
    , bsvtxs_position_handle("vertexMakerWithBS", "bsvtxsposition")
    , els_convs_pos_p4_handle("electronMaker", "elsconvsposp4")
    , genps_lepdaughter_p4_handle("genMaker", "genpslepdaughterp4")
    , hlt_trigObjs_p4_handle("hltMaker", "hlttrigObjsp4")
    , hyp_jets_p4_handle("hypDilepMaker", "hypjetsp4")
    , hyp_other_jets_p4_handle("hypDilepMaker", "hypotherjetsp4")
    , jpts_combinedSecondaryVertexBJetTag_handle("bTagJPTJetMaker", "jptscombinedSecondaryVertexBJetTag")
    , jpts_combinedSecondaryVertexMVABJetTag_handle("bTagJPTJetMaker", "jptscombinedSecondaryVertexMVABJetTag")
    , jpts_jetBProbabilityBJetTag_handle("bTagJPTJetMaker", "jptsjetBProbabilityBJetTag")
    , jpts_jetProbabilityBJetTag_handle("bTagJPTJetMaker", "jptsjetProbabilityBJetTag")
    , jpts_simpleSecondaryVertexBJetTag_handle("bTagJPTJetMaker", "jptssimpleSecondaryVertexBJetTag")
    , jpts_simpleSecondaryVertexHighEffBJetTag_handle("bTagJPTJetMaker", "jptssimpleSecondaryVertexHighEffBJetTag")
    , jpts_simpleSecondaryVertexHighPurBJetTags_handle("bTagJPTJetMaker", "jptssimpleSecondaryVertexHighPurBJetTag")
    , jpts_softElectronByIP3dBJetTag_handle("bTagJPTJetMaker", "jptssoftElectronByIP3dBJetTag")
    , jpts_softElectronByPtBJetTag_handle("bTagJPTJetMaker", "jptssoftElectronByPtBJetTag")
    , jpts_softElectronTag_handle("bTagJPTJetMaker", "jptssoftElectronTag")
    , jpts_softMuonBJetTag_handle("bTagJPTJetMaker", "jptssoftMuonBJetTag")
    , jpts_softMuonByIP3dBJetTag_handle("bTagJPTJetMaker", "jptssoftMuonByIP3dBJetTag")
    , jpts_softMuonByPtBJetTag_handle("bTagJPTJetMaker", "jptssoftMuonByPtBJetTag")
    , jpts_trackCountingHighEffBJetTag_handle("bTagJPTJetMaker", "jptstrackCountingHighEffBJetTag")
    , jpts_trackCountingHighPurBJetTag_handle("bTagJPTJetMaker", "jptstrackCountingHighPurBJetTag")
    , jets_combinedSecondaryVertexBJetTag_handle("bTagMaker", "jetscombinedSecondaryVertexBJetTag")
    , jets_combinedSecondaryVertexMVABJetTag_handle("bTagMaker", "jetscombinedSecondaryVertexMVABJetTag")
    , jets_jetBProbabilityBJetTag_handle("bTagMaker", "jetsjetBProbabilityBJetTag")
    , jets_jetProbabilityBJetTag_handle("bTagMaker", "jetsjetProbabilityBJetTag")
    , jets_simpleSecondaryVertexBJetTag_handle("bTagMaker", "jetssimpleSecondaryVertexBJetTag")
    , jets_simpleSecondaryVertexHighEffBJetTag_handle("bTagMaker", "jetssimpleSecondaryVertexHighEffBJetTag")
    , jets_simpleSecondaryVertexHighPurBJetTags_handle("bTagMaker", "jetssimpleSecondaryVertexHighPurBJetTag")
    , jets_softElectronByIP3dBJetTag_handle("bTagMaker", "jetssoftElectronByIP3dBJetTag")
    , jets_softElectronByPtBJetTag_handle("bTagMaker", "jetssoftElectronByPtBJetTag")
    , jets_softElectronTag_handle("bTagMaker", "jetssoftElectronTag")
    , jets_softMuonBJetTag_handle("bTagMaker", "jetssoftMuonBJetTag")
    , jets_softMuonByIP3dBJetTag_handle("bTagMaker", "jetssoftMuonByIP3dBJetTag")
    , jets_softMuonByPtBJetTag_handle("bTagMaker", "jetssoftMuonByPtBJetTag")
    , jets_trackCountingHighEffBJetTag_handle("bTagMaker", "jetstrackCountingHighEffBJetTag")
    , jets_trackCountingHighPurBJetTag_handle("bTagMaker", "jetstrackCountingHighPurBJetTag")
    , pfjets_combinedSecondaryVertexBJetTag_handle("bTagPFJetMaker", "pfjetscombinedSecondaryVertexBJetTag")
    , pfjets_combinedSecondaryVertexMVABJetTag_handle("bTagPFJetMaker", "pfjetscombinedSecondaryVertexMVABJetTag")
    , pfjets_jetBProbabilityBJetTag_handle("bTagPFJetMaker", "pfjetsjetBProbabilityBJetTag")
    , pfjets_jetProbabilityBJetTag_handle("bTagPFJetMaker", "pfjetsjetProbabilityBJetTag")
    , pfjets_simpleSecondaryVertexBJetTag_handle("bTagPFJetMaker", "pfjetssimpleSecondaryVertexBJetTag")
    , pfjets_simpleSecondaryVertexHighEffBJetTag_handle("bTagPFJetMaker", "pfjetssimpleSecondaryVertexHighEffBJetTag")
    , pfjets_simpleSecondaryVertexHighPurBJetTags_handle("bTagPFJetMaker", "pfjetssimpleSecondaryVertexHighPurBJetTag")
    , pfjets_softElectronByIP3dBJetTag_handle("bTagPFJetMaker", "pfjetssoftElectronByIP3dBJetTag")
    , pfjets_softElectronByPtBJetTag_handle("bTagPFJetMaker", "pfjetssoftElectronByPtBJetTag")
    , pfjets_softElectronTag_handle("bTagPFJetMaker", "pfjetssoftElectronTag")
    , pfjets_softMuonBJetTag_handle("bTagPFJetMaker", "pfjetssoftMuonBJetTag")
    , pfjets_softMuonByIP3dBJetTag_handle("bTagPFJetMaker", "pfjetssoftMuonByIP3dBJetTag")
    , pfjets_softMuonByPtBJetTag_handle("bTagPFJetMaker", "pfjetssoftMuonByPtBJetTag")
    , pfjets_trackCountingHighEffBJetTag_handle("bTagPFJetMaker", "pfjetstrackCountingHighEffBJetTag")
    , pfjets_trackCountingHighPurBJetTag_handle("bTagPFJetMaker", "pfjetstrackCountingHighPurBJetTag")
    , trkjets_combinedSecondaryVertexBJetTag_handle("bTagTrkMaker", "trkjetscombinedSecondaryVertexBJetTag")
    , trkjets_combinedSecondaryVertexMVABJetTag_handle("bTagTrkMaker", "trkjetscombinedSecondaryVertexMVABJetTag")
    , trkjets_jetBProbabilityBJetTag_handle("bTagTrkMaker", "trkjetsjetBProbabilityBJetTag")
    , trkjets_jetProbabilityBJetTag_handle("bTagTrkMaker", "trkjetsjetProbabilityBJetTag")
    , trkjets_simpleSecondaryVertexBJetTag_handle("bTagTrkMaker", "trkjetssimpleSecondaryVertexBJetTag")
    , trkjets_simpleSecondaryVertexHighEffBJetTag_handle("bTagTrkMaker", "trkjetssimpleSecondaryVertexHighEffBJetTag")
    , trkjets_simpleSecondaryVertexHighPurBJetTags_handle("bTagTrkMaker", "trkjetssimpleSecondaryVertexHighPurBJetTag")
    , trkjets_softElectronByIP3dBJetTag_handle("bTagTrkMaker", "trkjetssoftElectronByIP3dBJetTag")
    , trkjets_softElectronByPtBJetTag_handle("bTagTrkMaker", "trkjetssoftElectronByPtBJetTag")
    , trkjets_softElectronTag_handle("bTagTrkMaker", "trkjetssoftElectronTag")
    , trkjets_softMuonBJetTag_handle("bTagTrkMaker", "trkjetssoftMuonBJetTag")
    , trkjets_softMuonByIP3dBJetTag_handle("bTagTrkMaker", "trkjetssoftMuonByIP3dBJetTag")
    , trkjets_softMuonByPtBJetTag_handle("bTagTrkMaker", "trkjetssoftMuonByPtBJetTag")
    , trkjets_trackCountingHighEffBJetTag_handle("bTagTrkMaker", "trkjetstrackCountingHighEffBJetTag")
    , trkjets_trackCountingHighPurBJetTag_handle("bTagTrkMaker", "trkjetstrackCountingHighPurBJetTag")
    , evt_bs_covMatrix_handle("beamSpotMaker", "evtbscovMatrix")
    , els_mc3dr_handle("candToGenAssMaker", "elsmc3dr")
    , els_mcdr_handle("candToGenAssMaker", "elsmcdr")
    , jets_mc3dr_handle("candToGenAssMaker", "jetsmc3dr")
    , jets_mcdr_handle("candToGenAssMaker", "jetsmcdr")
    , jets_mc_emEnergy_handle("candToGenAssMaker", "jetsmcemEnergy")
    , jets_mc_gpdr_handle("candToGenAssMaker", "jetsmcgpdr")
    , jets_mc_hadEnergy_handle("candToGenAssMaker", "jetsmchadEnergy")
    , jets_mc_invEnergy_handle("candToGenAssMaker", "jetsmcinvEnergy")
    , jets_mc_otherEnergy_handle("candToGenAssMaker", "jetsmcotherEnergy")
    , mus_mc3dr_handle("candToGenAssMaker", "musmc3dr")
    , mus_mcdr_handle("candToGenAssMaker", "musmcdr")
    , pfjets_mc3dr_handle("candToGenAssMaker", "pfjetsmc3dr")
    , pfjets_mcdr_handle("candToGenAssMaker", "pfjetsmcdr")
    , pfjets_mc_emEnergy_handle("candToGenAssMaker", "pfjetsmcemEnergy")
    , pfjets_mc_gpdr_handle("candToGenAssMaker", "pfjetsmcgpdr")
    , pfjets_mc_hadEnergy_handle("candToGenAssMaker", "pfjetsmchadEnergy")
    , pfjets_mc_invEnergy_handle("candToGenAssMaker", "pfjetsmcinvEnergy")
    , pfjets_mc_otherEnergy_handle("candToGenAssMaker", "pfjetsmcotherEnergy")
    , photons_mc3dr_handle("candToGenAssMaker", "photonsmc3dr")
    , photons_mcdr_handle("candToGenAssMaker", "photonsmcdr")
    , trk_mc3dr_handle("candToGenAssMaker", "trkmc3dr")
    , trk_mcdr_handle("candToGenAssMaker", "trkmcdr")
    , els_ecalJuraIso_handle("elCaloIsoMaker", "elsecalJuraIso")
    , els_ecalJuraTowerIso_handle("elCaloIsoMaker", "elsecalJuraTowerIso")
    , els_hcalConeIso_handle("elCaloIsoMaker", "elshcalConeIso")
    , els_tkJuraIso_handle("elTkJuraIsoMaker", "elstkJuraIso")
    , els_jetdr_handle("elToJetAssMaker", "elsjetdr")
    , els_musdr_handle("elToMuAssMaker", "elsmusdr")
    , els_isoR03_chpf_radial_handle("electronIsolationMaker", "elsisoR03chpfradial")
    , els_isoR03_chpf_radialTight_handle("electronIsolationMaker", "elsisoR03chpfradialTight")
    , els_isoR03_chpf_radialTight_bv_handle("electronIsolationMaker", "elsisoR03chpfradialTightbv")
    , els_isoR03_chpf_radial_bv_handle("electronIsolationMaker", "elsisoR03chpfradialbv")
    , els_isoR03_empf_radial_handle("electronIsolationMaker", "elsisoR03empfradial")
    , els_isoR03_empf_radialTight_handle("electronIsolationMaker", "elsisoR03empfradialTight")
    , els_isoR03_empf_radialTight_bv_handle("electronIsolationMaker", "elsisoR03empfradialTightbv")
    , els_isoR03_empf_radial_bv_handle("electronIsolationMaker", "elsisoR03empfradialbv")
    , els_isoR03_nhpf_radial_handle("electronIsolationMaker", "elsisoR03nhpfradial")
    , els_isoR03_nhpf_radialTight_handle("electronIsolationMaker", "elsisoR03nhpfradialTight")
    , els_isoR03_nhpf_radialTight_bv_handle("electronIsolationMaker", "elsisoR03nhpfradialTightbv")
    , els_isoR03_nhpf_radial_bv_handle("electronIsolationMaker", "elsisoR03nhpfradialbv")
    , els_isoR03_pf2012n0p5_ch_handle("electronIsolationMaker", "elsisoR03pf2012n0p5ch")
    , els_isoR03_pf2012n0p5_em_handle("electronIsolationMaker", "elsisoR03pf2012n0p5em")
    , els_isoR03_pf2012n0p5_nh_handle("electronIsolationMaker", "elsisoR03pf2012n0p5nh")
    , els_isoR03_pf_radial_handle("electronIsolationMaker", "elsisoR03pfradial")
    , els_isoR03_pf_radialTight_handle("electronIsolationMaker", "elsisoR03pfradialTight")
    , els_isoR03_pf_radialTight_bv_handle("electronIsolationMaker", "elsisoR03pfradialTightbv")
    , els_isoR03_pf_radial_bv_handle("electronIsolationMaker", "elsisoR03pfradialbv")
    , els_chi2_handle("electronMaker", "elschi2")
    , els_ckf_chi2_handle("electronMaker", "elsckfchi2")
    , els_ckf_ndof_handle("electronMaker", "elsckfndof")
    , els_conv_dcot_handle("electronMaker", "elsconvdcot")
    , els_conv_dist_handle("electronMaker", "elsconvdist")
    , els_conv_old_dcot_handle("electronMaker", "elsconvolddcot")
    , els_conv_old_dist_handle("electronMaker", "elsconvolddist")
    , els_conv_old_radius_handle("electronMaker", "elsconvoldradius")
    , els_conv_radius_handle("electronMaker", "elsconvradius")
    , els_d0_handle("electronMaker", "elsd0")
    , els_d0Err_handle("electronMaker", "elsd0Err")
    , els_d0corr_handle("electronMaker", "elsd0corr")
    , els_dEtaIn_handle("electronMaker", "elsdEtaIn")
    , els_dEtaOut_handle("electronMaker", "elsdEtaOut")
    , els_dPhiIn_handle("electronMaker", "elsdPhiIn")
    , els_dPhiInPhiOut_handle("electronMaker", "elsdPhiInPhiOut")
    , els_dPhiOut_handle("electronMaker", "elsdPhiOut")
    , els_deltaEtaEleClusterTrackAtCalo_handle("electronMaker", "elsdeltaEtaEleClusterTrackAtCalo")
    , els_deltaPhiEleClusterTrackAtCalo_handle("electronMaker", "elsdeltaPhiEleClusterTrackAtCalo")
    , els_e1x5_handle("electronMaker", "else1x5")
    , els_e2x5Max_handle("electronMaker", "else2x5Max")
    , els_e3x3_handle("electronMaker", "else3x3")
    , els_e5x5_handle("electronMaker", "else5x5")
    , els_eMax_handle("electronMaker", "elseMax")
    , els_eOverPIn_handle("electronMaker", "elseOverPIn")
    , els_eOverPOut_handle("electronMaker", "elseOverPOut")
    , els_eSC_handle("electronMaker", "elseSC")
    , els_eSCPresh_handle("electronMaker", "elseSCPresh")
    , els_eSCRaw_handle("electronMaker", "elseSCRaw")
    , els_eSeed_handle("electronMaker", "elseSeed")
    , els_eSeedOverPIn_handle("electronMaker", "elseSeedOverPIn")
    , els_eSeedOverPOut_handle("electronMaker", "elseSeedOverPOut")
    , els_ecalEnergy_handle("electronMaker", "elsecalEnergy")
    , els_ecalEnergyError_handle("electronMaker", "elsecalEnergyError")
    , els_ecalIso_handle("electronMaker", "elsecalIso")
    , els_ecalIso04_handle("electronMaker", "elsecalIso04")
    , els_etaErr_handle("electronMaker", "elsetaErr")
    , els_etaSC_handle("electronMaker", "elsetaSC")
    , els_etaSCwidth_handle("electronMaker", "elsetaSCwidth")
    , els_fbrem_handle("electronMaker", "elsfbrem")
    , els_hOverE_handle("electronMaker", "elshOverE")
    , els_hcalDepth1OverEcal_handle("electronMaker", "elshcalDepth1OverEcal")
    , els_hcalDepth1TowerSumEt_handle("electronMaker", "elshcalDepth1TowerSumEt")
    , els_hcalDepth1TowerSumEt04_handle("electronMaker", "elshcalDepth1TowerSumEt04")
    , els_hcalDepth2OverEcal_handle("electronMaker", "elshcalDepth2OverEcal")
    , els_hcalDepth2TowerSumEt_handle("electronMaker", "elshcalDepth2TowerSumEt")
    , els_hcalDepth2TowerSumEt04_handle("electronMaker", "elshcalDepth2TowerSumEt04")
    , els_hcalIso_handle("electronMaker", "elshcalIso")
    , els_hcalIso04_handle("electronMaker", "elshcalIso04")
    , els_ip3d_handle("electronMaker", "elsip3d")
    , els_ip3derr_handle("electronMaker", "elsip3derr")
    , els_iso03_pf_handle("electronMaker", "elsiso03pf")
    , els_iso03_pf2012_ch_handle("electronMaker", "elsiso03pf2012ch")
    , els_iso03_pf2012_em_handle("electronMaker", "elsiso03pf2012em")
    , els_iso03_pf2012ext_ch_handle("electronMaker", "elsiso03pf2012extch")
    , els_iso03_pf2012ext_em_handle("electronMaker", "elsiso03pf2012extem")
    , els_iso03_pf2012ext_nh_handle("electronMaker", "elsiso03pf2012extnh")
    , els_iso03_pf2012_nh_handle("electronMaker", "elsiso03pf2012nh")
    , els_iso03_pf_ch_handle("electronMaker", "elsiso03pfch")
    , els_iso03_pf_gamma05_handle("electronMaker", "elsiso03pfgamma05")
    , els_iso03_pf_nhad05_handle("electronMaker", "elsiso03pfnhad05")
    , els_iso04_pf_handle("electronMaker", "elsiso04pf")
    , els_iso04_pf2012_ch_handle("electronMaker", "elsiso04pf2012ch")
    , els_iso04_pf2012_em_handle("electronMaker", "elsiso04pf2012em")
    , els_iso04_pf2012ext_ch_handle("electronMaker", "elsiso04pf2012extch")
    , els_iso04_pf2012ext_em_handle("electronMaker", "elsiso04pf2012extem")
    , els_iso04_pf2012ext_nh_handle("electronMaker", "elsiso04pf2012extnh")
    , els_iso04_pf2012_nh_handle("electronMaker", "elsiso04pf2012nh")
    , els_iso04_pf_ch_handle("electronMaker", "elsiso04pfch")
    , els_iso04_pf_gamma05_handle("electronMaker", "elsiso04pfgamma05")
    , els_iso04_pf_nhad05_handle("electronMaker", "elsiso04pfnhad05")
    , els_layer1_charge_handle("electronMaker", "elslayer1charge")
    , els_lh_handle("electronMaker", "elslh")
    , els_mva_handle("electronMaker", "elsmva")
    , els_ndof_handle("electronMaker", "elsndof")
    , els_pfChargedHadronIso_handle("electronMaker", "elspfChargedHadronIso")
    , els_pfNeutralHadronIso_handle("electronMaker", "elspfNeutralHadronIso")
    , els_pfPhotonIso_handle("electronMaker", "elspfPhotonIso")
    , els_phiErr_handle("electronMaker", "elsphiErr")
    , els_phiSC_handle("electronMaker", "elsphiSC")
    , els_phiSCwidth_handle("electronMaker", "elsphiSCwidth")
    , els_ptErr_handle("electronMaker", "elsptErr")
    , els_r9_handle("electronMaker", "elsr9")
    , els_sigmaEtaEta_handle("electronMaker", "elssigmaEtaEta")
    , els_sigmaIEtaIEta_handle("electronMaker", "elssigmaIEtaIEta")
    , els_sigmaIEtaIEtaSC_handle("electronMaker", "elssigmaIEtaIEtaSC")
    , els_sigmaIEtaIPhi_handle("electronMaker", "elssigmaIEtaIPhi")
    , els_sigmaIPhiIPhi_handle("electronMaker", "elssigmaIPhiIPhi")
    , els_sigmaIPhiIPhiSC_handle("electronMaker", "elssigmaIPhiIPhiSC")
    , els_sigmaIphiIphi_handle("electronMaker", "elssigmaIphiIphi")
    , els_sigmaPhiPhi_handle("electronMaker", "elssigmaPhiPhi")
    , els_tkIso_handle("electronMaker", "elstkIso")
    , els_tkIso04_handle("electronMaker", "elstkIso04")
    , els_trackMomentumError_handle("electronMaker", "elstrackMomentumError")
    , els_trkdr_handle("electronMaker", "elstrkdr")
    , els_trkshFrac_handle("electronMaker", "elstrkshFrac")
    , els_z0_handle("electronMaker", "elsz0")
    , els_z0Err_handle("electronMaker", "elsz0Err")
    , els_z0corr_handle("electronMaker", "elsz0corr")
    , gsftrks_chi2_handle("gsfTrackMaker", "gsftrkschi2")
    , gsftrks_d0_handle("gsfTrackMaker", "gsftrksd0")
    , gsftrks_d0Err_handle("gsfTrackMaker", "gsftrksd0Err")
    , gsftrks_d0corr_handle("gsfTrackMaker", "gsftrksd0corr")
    , gsftrks_d0corrPhi_handle("gsfTrackMaker", "gsftrksd0corrPhi")
    , gsftrks_d0phiCov_handle("gsfTrackMaker", "gsftrksd0phiCov")
    , gsftrks_etaErr_handle("gsfTrackMaker", "gsftrksetaErr")
    , gsftrks_layer1_charge_handle("gsfTrackMaker", "gsftrkslayer1charge")
    , gsftrks_ndof_handle("gsfTrackMaker", "gsftrksndof")
    , gsftrks_phiErr_handle("gsfTrackMaker", "gsftrksphiErr")
    , gsftrks_ptErr_handle("gsfTrackMaker", "gsftrksptErr")
    , gsftrks_z0_handle("gsfTrackMaker", "gsftrksz0")
    , gsftrks_z0Err_handle("gsfTrackMaker", "gsftrksz0Err")
    , gsftrks_z0corr_handle("gsfTrackMaker", "gsftrksz0corr")
    , hyp_Ht_handle("hypDilepMaker", "hypHt")
    , hyp_dPhi_nJet_metMuonJESCorr_handle("hypDilepMaker", "hypdPhinJetmetMuonJESCorr")
    , hyp_dPhi_nJet_muCorrMet_handle("hypDilepMaker", "hypdPhinJetmuCorrMet")
    , hyp_dPhi_nJet_tcMet_handle("hypDilepMaker", "hypdPhinJettcMet")
    , hyp_dPhi_nJet_unCorrMet_handle("hypDilepMaker", "hypdPhinJetunCorrMet")
    , hyp_ll_chi2_handle("hypDilepMaker", "hypllchi2")
    , hyp_ll_d0_handle("hypDilepMaker", "hyplld0")
    , hyp_ll_d0Err_handle("hypDilepMaker", "hyplld0Err")
    , hyp_ll_d0corr_handle("hypDilepMaker", "hyplld0corr")
    , hyp_ll_dPhi_metMuonJESCorr_handle("hypDilepMaker", "hyplldPhimetMuonJESCorr")
    , hyp_ll_dPhi_muCorrMet_handle("hypDilepMaker", "hyplldPhimuCorrMet")
    , hyp_ll_dPhi_tcMet_handle("hypDilepMaker", "hyplldPhitcMet")
    , hyp_ll_dPhi_unCorrMet_handle("hypDilepMaker", "hyplldPhiunCorrMet")
    , hyp_ll_etaErr_handle("hypDilepMaker", "hyplletaErr")
    , hyp_ll_ndof_handle("hypDilepMaker", "hypllndof")
    , hyp_ll_phiErr_handle("hypDilepMaker", "hypllphiErr")
    , hyp_ll_ptErr_handle("hypDilepMaker", "hypllptErr")
    , hyp_ll_z0_handle("hypDilepMaker", "hypllz0")
    , hyp_ll_z0Err_handle("hypDilepMaker", "hypllz0Err")
    , hyp_ll_z0corr_handle("hypDilepMaker", "hypllz0corr")
    , hyp_lt_chi2_handle("hypDilepMaker", "hypltchi2")
    , hyp_lt_d0_handle("hypDilepMaker", "hypltd0")
    , hyp_lt_d0Err_handle("hypDilepMaker", "hypltd0Err")
    , hyp_lt_d0corr_handle("hypDilepMaker", "hypltd0corr")
    , hyp_lt_dPhi_metMuonJESCorr_handle("hypDilepMaker", "hypltdPhimetMuonJESCorr")
    , hyp_lt_dPhi_muCorrMet_handle("hypDilepMaker", "hypltdPhimuCorrMet")
    , hyp_lt_dPhi_tcMet_handle("hypDilepMaker", "hypltdPhitcMet")
    , hyp_lt_dPhi_unCorrMet_handle("hypDilepMaker", "hypltdPhiunCorrMet")
    , hyp_lt_etaErr_handle("hypDilepMaker", "hypltetaErr")
    , hyp_lt_ndof_handle("hypDilepMaker", "hypltndof")
    , hyp_lt_phiErr_handle("hypDilepMaker", "hypltphiErr")
    , hyp_lt_ptErr_handle("hypDilepMaker", "hypltptErr")
    , hyp_lt_z0_handle("hypDilepMaker", "hypltz0")
    , hyp_lt_z0Err_handle("hypDilepMaker", "hypltz0Err")
    , hyp_lt_z0corr_handle("hypDilepMaker", "hypltz0corr")
    , hyp_mt2_metMuonJESCorr_handle("hypDilepMaker", "hypmt2metMuonJESCorr")
    , hyp_mt2_muCorrMet_handle("hypDilepMaker", "hypmt2muCorrMet")
    , hyp_mt2_tcMet_handle("hypDilepMaker", "hypmt2tcMet")
    , hyp_sumJetPt_handle("hypDilepMaker", "hypsumJetPt")
    , hyp_FVFit_chi2ndf_handle("hypDilepVertexMaker", "hypFVFitchi2ndf")
    , hyp_FVFit_prob_handle("hypDilepVertexMaker", "hypFVFitprob")
    , hyp_FVFit_v4cxx_handle("hypDilepVertexMaker", "hypFVFitv4cxx")
    , hyp_FVFit_v4cxy_handle("hypDilepVertexMaker", "hypFVFitv4cxy")
    , hyp_FVFit_v4cyy_handle("hypDilepVertexMaker", "hypFVFitv4cyy")
    , hyp_FVFit_v4czx_handle("hypDilepVertexMaker", "hypFVFitv4czx")
    , hyp_FVFit_v4czy_handle("hypDilepVertexMaker", "hypFVFitv4czy")
    , hyp_FVFit_v4czz_handle("hypDilepVertexMaker", "hypFVFitv4czz")
    , jets_approximatefHPD_handle("jetMaker", "jetsapproximatefHPD")
    , jets_approximatefRBX_handle("jetMaker", "jetsapproximatefRBX")
    , jets_cor_handle("jetMaker", "jetscor")
    , jets_corL1FastL2L3_handle("jetMaker", "jetscorL1FastL2L3")
    , jets_corL1L2L3_handle("jetMaker", "jetscorL1L2L3")
    , jets_emFrac_handle("jetMaker", "jetsemFrac")
    , jets_fHPD_handle("jetMaker", "jetsfHPD")
    , jets_fRBX_handle("jetMaker", "jetsfRBX")
    , jets_fSubDetector1_handle("jetMaker", "jetsfSubDetector1")
    , jets_fSubDetector2_handle("jetMaker", "jetsfSubDetector2")
    , jets_fSubDetector3_handle("jetMaker", "jetsfSubDetector3")
    , jets_fSubDetector4_handle("jetMaker", "jetsfSubDetector4")
    , jets_hitsInN90_handle("jetMaker", "jetshitsInN90")
    , jets_n90Hits_handle("jetMaker", "jetsn90Hits")
    , jets_nECALTowers_handle("jetMaker", "jetsnECALTowers")
    , jets_nHCALTowers_handle("jetMaker", "jetsnHCALTowers")
    , jets_restrictedEMF_handle("jetMaker", "jetsrestrictedEMF")
    , mus_met_deltax_handle("metMaker", "musmetdeltax")
    , mus_met_deltay_handle("metMaker", "musmetdeltay")
    , mus_eledr_handle("muToElsAssMaker", "museledr")
    , mus_jetdr_handle("muToJetAssMaker", "musjetdr")
    , mus_isoR03_chpf_radial_handle("muonIsolationMaker", "musisoR03chpfradial")
    , mus_isoR03_chpf_radialTight_handle("muonIsolationMaker", "musisoR03chpfradialTight")
    , mus_isoR03_empf_radial_handle("muonIsolationMaker", "musisoR03empfradial")
    , mus_isoR03_empf_radialTight_handle("muonIsolationMaker", "musisoR03empfradialTight")
    , mus_isoR03_nhpf_radial_handle("muonIsolationMaker", "musisoR03nhpfradial")
    , mus_isoR03_nhpf_radialTight_handle("muonIsolationMaker", "musisoR03nhpfradialTight")
    , mus_isoR03_pf_radial_handle("muonIsolationMaker", "musisoR03pfradial")
    , mus_isoR03_pf_radialTight_handle("muonIsolationMaker", "musisoR03pfradialTight")
    , mus_backToBackCompat_handle("muonMaker", "musbackToBackCompat")
    , mus_caloCompatibility_handle("muonMaker", "muscaloCompatibility")
    , mus_chi2_handle("muonMaker", "muschi2")
    , mus_chi2LocalMomentum_handle("muonMaker", "muschi2LocalMomentum")
    , mus_chi2LocalPosition_handle("muonMaker", "muschi2LocalPosition")
    , mus_cosmicCompat_handle("muonMaker", "muscosmicCompat")
    , mus_d0_handle("muonMaker", "musd0")
    , mus_d0Err_handle("muonMaker", "musd0Err")
    , mus_d0corr_handle("muonMaker", "musd0corr")
    , mus_e_em_handle("muonMaker", "museem")
    , mus_e_emS9_handle("muonMaker", "museemS9")
    , mus_e_had_handle("muonMaker", "musehad")
    , mus_e_hadS9_handle("muonMaker", "musehadS9")
    , mus_e_ho_handle("muonMaker", "museho")
    , mus_e_hoS9_handle("muonMaker", "musehoS9")
    , mus_etaErr_handle("muonMaker", "musetaErr")
    , mus_gfit_chi2_handle("muonMaker", "musgfitchi2")
    , mus_gfit_d0_handle("muonMaker", "musgfitd0")
    , mus_gfit_d0Err_handle("muonMaker", "musgfitd0Err")
    , mus_gfit_d0corr_handle("muonMaker", "musgfitd0corr")
    , mus_gfit_ndof_handle("muonMaker", "musgfitndof")
    , mus_gfit_qoverp_handle("muonMaker", "musgfitqoverp")
    , mus_gfit_qoverpError_handle("muonMaker", "musgfitqoverpError")
    , mus_gfit_z0_handle("muonMaker", "musgfitz0")
    , mus_gfit_z0Err_handle("muonMaker", "musgfitz0Err")
    , mus_gfit_z0corr_handle("muonMaker", "musgfitz0corr")
    , mus_glbKink_handle("muonMaker", "musglbKink")
    , mus_glbTrackProbability_handle("muonMaker", "musglbTrackProbability")
    , mus_globalDeltaEtaPhi_handle("muonMaker", "musglobalDeltaEtaPhi")
    , mus_ip3d_handle("muonMaker", "musip3d")
    , mus_ip3derr_handle("muonMaker", "musip3derr")
    , mus_iso03_emEt_handle("muonMaker", "musiso03emEt")
    , mus_iso03_hadEt_handle("muonMaker", "musiso03hadEt")
    , mus_iso03_hoEt_handle("muonMaker", "musiso03hoEt")
    , mus_iso03_pf_handle("muonMaker", "musiso03pf")
    , mus_iso03_sumPt_handle("muonMaker", "musiso03sumPt")
    , mus_iso04_pf_handle("muonMaker", "musiso04pf")
    , mus_iso05_emEt_handle("muonMaker", "musiso05emEt")
    , mus_iso05_hadEt_handle("muonMaker", "musiso05hadEt")
    , mus_iso05_hoEt_handle("muonMaker", "musiso05hoEt")
    , mus_iso05_sumPt_handle("muonMaker", "musiso05sumPt")
    , mus_isoR03_pf_ChargedHadronPt_handle("muonMaker", "musisoR03pfChargedHadronPt")
    , mus_isoR03_pf_ChargedParticlePt_handle("muonMaker", "musisoR03pfChargedParticlePt")
    , mus_isoR03_pf_NeutralHadronEt_handle("muonMaker", "musisoR03pfNeutralHadronEt")
    , mus_isoR03_pf_NeutralHadronEtHighThreshold_handle("muonMaker", "musisoR03pfNeutralHadronEtHighThreshold")
    , mus_isoR03_pf_PUPt_handle("muonMaker", "musisoR03pfPUPt")
    , mus_isoR03_pf_PhotonEt_handle("muonMaker", "musisoR03pfPhotonEt")
    , mus_isoR03_pf_PhotonEtHighThreshold_handle("muonMaker", "musisoR03pfPhotonEtHighThreshold")
    , mus_isoR04_pf_ChargedHadronPt_handle("muonMaker", "musisoR04pfChargedHadronPt")
    , mus_isoR04_pf_ChargedParticlePt_handle("muonMaker", "musisoR04pfChargedParticlePt")
    , mus_isoR04_pf_NeutralHadronEt_handle("muonMaker", "musisoR04pfNeutralHadronEt")
    , mus_isoR04_pf_NeutralHadronEtHighThreshold_handle("muonMaker", "musisoR04pfNeutralHadronEtHighThreshold")
    , mus_isoR04_pf_PUPt_handle("muonMaker", "musisoR04pfPUPt")
    , mus_isoR04_pf_PhotonEt_handle("muonMaker", "musisoR04pfPhotonEt")
    , mus_isoR04_pf_PhotonEtHighThreshold_handle("muonMaker", "musisoR04pfPhotonEtHighThreshold")
    , mus_iso_ecalvetoDep_handle("muonMaker", "musisoecalvetoDep")
    , mus_iso_hcalvetoDep_handle("muonMaker", "musisohcalvetoDep")
    , mus_iso_hovetoDep_handle("muonMaker", "musisohovetoDep")
    , mus_iso_trckvetoDep_handle("muonMaker", "musisotrckvetoDep")
    , mus_localDistance_handle("muonMaker", "muslocalDistance")
    , mus_ndof_handle("muonMaker", "musndof")
    , mus_overlapCompat_handle("muonMaker", "musoverlapCompat")
    , mus_pfdeltaP_handle("muonMaker", "muspfdeltaP")
    , mus_pfecalE_handle("muonMaker", "muspfecalE")
    , mus_pfhcalE_handle("muonMaker", "muspfhcalE")
    , mus_pfmva_emu_handle("muonMaker", "muspfmvaemu")
    , mus_pfmva_epi_handle("muonMaker", "muspfmvaepi")
    , mus_pfmva_nothing_gamma_handle("muonMaker", "muspfmvanothinggamma")
    , mus_pfmva_nothing_nh_handle("muonMaker", "muspfmvanothingnh")
    , mus_pfmva_pimu_handle("muonMaker", "muspfmvapimu")
    , mus_pfpS1E_handle("muonMaker", "muspfpS1E")
    , mus_pfpS2E_handle("muonMaker", "muspfpS2E")
    , mus_pfrawEcalE_handle("muonMaker", "muspfrawEcalE")
    , mus_pfrawHcalE_handle("muonMaker", "muspfrawHcalE")
    , mus_phiErr_handle("muonMaker", "musphiErr")
    , mus_ptErr_handle("muonMaker", "musptErr")
    , mus_qoverp_handle("muonMaker", "musqoverp")
    , mus_qoverpError_handle("muonMaker", "musqoverpError")
    , mus_segmCompatibility_handle("muonMaker", "mussegmCompatibility")
    , mus_staRelChi2_handle("muonMaker", "musstaRelChi2")
    , mus_sta_chi2_handle("muonMaker", "musstachi2")
    , mus_sta_d0_handle("muonMaker", "musstad0")
    , mus_sta_d0Err_handle("muonMaker", "musstad0Err")
    , mus_sta_d0corr_handle("muonMaker", "musstad0corr")
    , mus_sta_ndof_handle("muonMaker", "musstandof")
    , mus_sta_qoverp_handle("muonMaker", "musstaqoverp")
    , mus_sta_qoverpError_handle("muonMaker", "musstaqoverpError")
    , mus_sta_z0_handle("muonMaker", "musstaz0")
    , mus_sta_z0Err_handle("muonMaker", "musstaz0Err")
    , mus_sta_z0corr_handle("muonMaker", "musstaz0corr")
    , mus_timeAtIpInOut_handle("muonMaker", "mustimeAtIpInOut")
    , mus_timeAtIpInOutErr_handle("muonMaker", "mustimeAtIpInOutErr")
    , mus_timeAtIpOutIn_handle("muonMaker", "mustimeAtIpOutIn")
    , mus_timeAtIpOutInErr_handle("muonMaker", "mustimeAtIpOutInErr")
    , mus_timeCompat_handle("muonMaker", "mustimeCompat")
    , mus_trkKink_handle("muonMaker", "mustrkKink")
    , mus_trkRelChi2_handle("muonMaker", "mustrkRelChi2")
    , mus_vertexCompat_handle("muonMaker", "musvertexCompat")
    , mus_vertexphi_handle("muonMaker", "musvertexphi")
    , mus_z0_handle("muonMaker", "musz0")
    , mus_z0Err_handle("muonMaker", "musz0Err")
    , mus_z0corr_handle("muonMaker", "musz0corr")
    , pfjets_mvavalue_handle("mvaJetIdMaker", "pfjetsmvavalue")
    , pfjets_full53xmva_beta_handle("mvaJetIdMakerFull53x", "pfjetsfull53xmvabeta")
    , pfjets_full53xmva_betaStar_handle("mvaJetIdMakerFull53x", "pfjetsfull53xmvabetaStar")
    , pfjets_full53xmva_d0_handle("mvaJetIdMakerFull53x", "pfjetsfull53xmvad0")
    , pfjets_full53xmva_dRMean_handle("mvaJetIdMakerFull53x", "pfjetsfull53xmvadRMean")
    , pfjets_full53xmva_dZ_handle("mvaJetIdMakerFull53x", "pfjetsfull53xmvadZ")
    , pfjets_full53xmva_frac01_handle("mvaJetIdMakerFull53x", "pfjetsfull53xmvafrac01")
    , pfjets_full53xmva_frac02_handle("mvaJetIdMakerFull53x", "pfjetsfull53xmvafrac02")
    , pfjets_full53xmva_frac03_handle("mvaJetIdMakerFull53x", "pfjetsfull53xmvafrac03")
    , pfjets_full53xmva_frac04_handle("mvaJetIdMakerFull53x", "pfjetsfull53xmvafrac04")
    , pfjets_full53xmva_frac05_handle("mvaJetIdMakerFull53x", "pfjetsfull53xmvafrac05")
    , pfjets_full53xmva_nCharged_handle("mvaJetIdMakerFull53x", "pfjetsfull53xmvanCharged")
    , pfjets_full53xmva_nNeutrals_handle("mvaJetIdMakerFull53x", "pfjetsfull53xmvanNeutrals")
    , pfjets_full53xmva_nvtx_handle("mvaJetIdMakerFull53x", "pfjetsfull53xmvanvtx")
    , pfjets_full53xmvavalue_handle("mvaJetIdMakerFull53x", "pfjetsfull53xmvavalue")
    , pfjets_full5xmvavalue_handle("mvaJetIdMakerFull5x", "pfjetsfull5xmvavalue")
    , trkjet_met_handle("myTrkJetMetMaker", "trkjetmet")
    , trkjet_metPhi_handle("myTrkJetMetMaker", "trkjetmetPhi")
    , trkjet_sumet_handle("myTrkJetMetMaker", "trkjetsumet")
    , trk_met_handle("myTrkMetMaker", "trkmet")
    , trk_metPhi_handle("myTrkMetMaker", "trkmetPhi")
    , trk_sumet_handle("myTrkMetMaker", "trksumet")
    , pfcands_deltaP_handle("pfCandidateMaker", "pfcandsdeltaP")
    , pfcands_ecalE_handle("pfCandidateMaker", "pfcandsecalE")
    , pfcands_hcalE_handle("pfCandidateMaker", "pfcandshcalE")
    , pfcands_mva_emu_handle("pfCandidateMaker", "pfcandsmvaemu")
    , pfcands_mva_epi_handle("pfCandidateMaker", "pfcandsmvaepi")
    , pfcands_mva_nothing_gamma_handle("pfCandidateMaker", "pfcandsmvanothinggamma")
    , pfcands_mva_nothing_nh_handle("pfCandidateMaker", "pfcandsmvanothingnh")
    , pfcands_mva_pimu_handle("pfCandidateMaker", "pfcandsmvapimu")
    , pfcands_pS1E_handle("pfCandidateMaker", "pfcandspS1E")
    , pfcands_pS2E_handle("pfCandidateMaker", "pfcandspS2E")
    , pfcands_rawEcalE_handle("pfCandidateMaker", "pfcandsrawEcalE")
    , pfcands_rawHcalE_handle("pfCandidateMaker", "pfcandsrawHcalE")
    , pfels_deltaP_handle("pfElectronMaker", "pfelsdeltaP")
    , pfels_ecalE_handle("pfElectronMaker", "pfelsecalE")
    , pfels_hcalE_handle("pfElectronMaker", "pfelshcalE")
    , pfels_iso04ChargedHadrons_handle("pfElectronMaker", "pfelsiso04ChargedHadrons")
    , pfels_iso04NeutralHadrons_handle("pfElectronMaker", "pfelsiso04NeutralHadrons")
    , pfels_iso04Photons_handle("pfElectronMaker", "pfelsiso04Photons")
    , pfels_isoChargedHadrons_handle("pfElectronMaker", "pfelsisoChargedHadrons")
    , pfels_isoNeutralHadrons_handle("pfElectronMaker", "pfelsisoNeutralHadrons")
    , pfels_isoPhotons_handle("pfElectronMaker", "pfelsisoPhotons")
    , pfels_mva_emu_handle("pfElectronMaker", "pfelsmvaemu")
    , pfels_mva_epi_handle("pfElectronMaker", "pfelsmvaepi")
    , pfels_mva_nothing_gamma_handle("pfElectronMaker", "pfelsmvanothinggamma")
    , pfels_mva_nothing_nh_handle("pfElectronMaker", "pfelsmvanothingnh")
    , pfels_mva_pimu_handle("pfElectronMaker", "pfelsmvapimu")
    , pfels_pS1E_handle("pfElectronMaker", "pfelspS1E")
    , pfels_pS2E_handle("pfElectronMaker", "pfelspS2E")
    , pfels_rawEcalE_handle("pfElectronMaker", "pfelsrawEcalE")
    , pfels_rawHcalE_handle("pfElectronMaker", "pfelsrawHcalE")
    , pfjets_area_handle("pfJetMaker", "pfjetsarea")
    , pfjets_chargedEmE_handle("pfJetMaker", "pfjetschargedEmE")
    , pfjets_chargedHadronE_handle("pfJetMaker", "pfjetschargedHadronE")
    , pfjets_cor_handle("pfJetMaker", "pfjetscor")
    , pfjets_corL1Fast_handle("pfJetMaker", "pfjetscorL1Fast")
    , pfjets_corL1FastL2L3_handle("pfJetMaker", "pfjetscorL1FastL2L3")
    , pfjets_corL1FastL2L3residual_handle("pfJetMaker", "pfjetscorL1FastL2L3residual")
    , pfjets_corL1L2L3_handle("pfJetMaker", "pfjetscorL1L2L3")
    , pfjets_electronE_handle("pfJetMaker", "pfjetselectronE")
    , pfjets_hfEmE_handle("pfJetMaker", "pfjetshfEmE")
    , pfjets_hfHadronE_handle("pfJetMaker", "pfjetshfHadronE")
    , pfjets_muonE_handle("pfJetMaker", "pfjetsmuonE")
    , pfjets_neutralEmE_handle("pfJetMaker", "pfjetsneutralEmE")
    , pfjets_neutralHadronE_handle("pfJetMaker", "pfjetsneutralHadronE")
    , pfjets_photonE_handle("pfJetMaker", "pfjetsphotonE")
    , pfmus_deltaP_handle("pfMuonMaker", "pfmusdeltaP")
    , pfmus_ecalE_handle("pfMuonMaker", "pfmusecalE")
    , pfmus_hcalE_handle("pfMuonMaker", "pfmushcalE")
    , pfmus_iso04ChargedHadrons_handle("pfMuonMaker", "pfmusiso04ChargedHadrons")
    , pfmus_iso04NeutralHadrons_handle("pfMuonMaker", "pfmusiso04NeutralHadrons")
    , pfmus_iso04Photons_handle("pfMuonMaker", "pfmusiso04Photons")
    , pfmus_isoChargedHadrons_handle("pfMuonMaker", "pfmusisoChargedHadrons")
    , pfmus_isoNeutralHadrons_handle("pfMuonMaker", "pfmusisoNeutralHadrons")
    , pfmus_isoPhotons_handle("pfMuonMaker", "pfmusisoPhotons")
    , pfmus_mva_emu_handle("pfMuonMaker", "pfmusmvaemu")
    , pfmus_mva_epi_handle("pfMuonMaker", "pfmusmvaepi")
    , pfmus_mva_nothing_gamma_handle("pfMuonMaker", "pfmusmvanothinggamma")
    , pfmus_mva_nothing_nh_handle("pfMuonMaker", "pfmusmvanothingnh")
    , pfmus_mva_pimu_handle("pfMuonMaker", "pfmusmvapimu")
    , pfmus_pS1E_handle("pfMuonMaker", "pfmuspS1E")
    , pfmus_pS2E_handle("pfMuonMaker", "pfmuspS2E")
    , pfmus_rawEcalE_handle("pfMuonMaker", "pfmusrawEcalE")
    , pfmus_rawHcalE_handle("pfMuonMaker", "pfmusrawHcalE")
    , taus_pf_againstElectronDeadECAL_handle("pftauMaker", "tauspfagainstElectronDeadECAL")
    , taus_pf_againstElectronLoose_handle("pftauMaker", "tauspfagainstElectronLoose")
    , taus_pf_againstElectronLooseMVA2_handle("pftauMaker", "tauspfagainstElectronLooseMVA2")
    , taus_pf_againstElectronLooseMVA3_handle("pftauMaker", "tauspfagainstElectronLooseMVA3")
    , taus_pf_againstElectronMVA_handle("pftauMaker", "tauspfagainstElectronMVA")
    , taus_pf_againstElectronMVA2category_handle("pftauMaker", "tauspfagainstElectronMVA2category")
    , taus_pf_againstElectronMVA2raw_handle("pftauMaker", "tauspfagainstElectronMVA2raw")
    , taus_pf_againstElectronMVA3category_handle("pftauMaker", "tauspfagainstElectronMVA3category")
    , taus_pf_againstElectronMVA3raw_handle("pftauMaker", "tauspfagainstElectronMVA3raw")
    , taus_pf_againstElectronMedium_handle("pftauMaker", "tauspfagainstElectronMedium")
    , taus_pf_againstElectronMediumMVA2_handle("pftauMaker", "tauspfagainstElectronMediumMVA2")
    , taus_pf_againstElectronMediumMVA3_handle("pftauMaker", "tauspfagainstElectronMediumMVA3")
    , taus_pf_againstElectronTight_handle("pftauMaker", "tauspfagainstElectronTight")
    , taus_pf_againstElectronTightMVA2_handle("pftauMaker", "tauspfagainstElectronTightMVA2")
    , taus_pf_againstElectronTightMVA3_handle("pftauMaker", "tauspfagainstElectronTightMVA3")
    , taus_pf_againstElectronVLooseMVA2_handle("pftauMaker", "tauspfagainstElectronVLooseMVA2")
    , taus_pf_againstElectronVTightMVA3_handle("pftauMaker", "tauspfagainstElectronVTightMVA3")
    , taus_pf_againstMuonLoose_handle("pftauMaker", "tauspfagainstMuonLoose")
    , taus_pf_againstMuonLoose2_handle("pftauMaker", "tauspfagainstMuonLoose2")
    , taus_pf_againstMuonMedium_handle("pftauMaker", "tauspfagainstMuonMedium")
    , taus_pf_againstMuonMedium2_handle("pftauMaker", "tauspfagainstMuonMedium2")
    , taus_pf_againstMuonTight_handle("pftauMaker", "tauspfagainstMuonTight")
    , taus_pf_againstMuonTight2_handle("pftauMaker", "tauspfagainstMuonTight2")
    , taus_pf_byCombinedIsolationDeltaBetaCorrRaw_handle("pftauMaker", "tauspfbyCombinedIsolationDeltaBetaCorrRaw")
    , taus_pf_byCombinedIsolationDeltaBetaCorrRaw3Hits_handle("pftauMaker", "tauspfbyCombinedIsolationDeltaBetaCorrRaw3Hits")
    , taus_pf_byDecayModeFinding_handle("pftauMaker", "tauspfbyDecayModeFinding")
    , taus_pf_byIsolationMVA2raw_handle("pftauMaker", "tauspfbyIsolationMVA2raw")
    , taus_pf_byIsolationMVAraw_handle("pftauMaker", "tauspfbyIsolationMVAraw")
    , taus_pf_byLooseCombinedIsolationDeltaBetaCorr_handle("pftauMaker", "tauspfbyLooseCombinedIsolationDeltaBetaCorr")
    , taus_pf_byLooseCombinedIsolationDeltaBetaCorr3Hits_handle("pftauMaker", "tauspfbyLooseCombinedIsolationDeltaBetaCorr3Hits")
    , taus_pf_byLooseIsolationMVA_handle("pftauMaker", "tauspfbyLooseIsolationMVA")
    , taus_pf_byLooseIsolationMVA2_handle("pftauMaker", "tauspfbyLooseIsolationMVA2")
    , taus_pf_byMediumCombinedIsolationDeltaBetaCorr_handle("pftauMaker", "tauspfbyMediumCombinedIsolationDeltaBetaCorr")
    , taus_pf_byMediumCombinedIsolationDeltaBetaCorr3Hits_handle("pftauMaker", "tauspfbyMediumCombinedIsolationDeltaBetaCorr3Hits")
    , taus_pf_byMediumIsolationMVA_handle("pftauMaker", "tauspfbyMediumIsolationMVA")
    , taus_pf_byMediumIsolationMVA2_handle("pftauMaker", "tauspfbyMediumIsolationMVA2")
    , taus_pf_byTightCombinedIsolationDeltaBetaCorr_handle("pftauMaker", "tauspfbyTightCombinedIsolationDeltaBetaCorr")
    , taus_pf_byTightCombinedIsolationDeltaBetaCorr3Hits_handle("pftauMaker", "tauspfbyTightCombinedIsolationDeltaBetaCorr3Hits")
    , taus_pf_byTightIsolationMVA_handle("pftauMaker", "tauspfbyTightIsolationMVA")
    , taus_pf_byTightIsolationMVA2_handle("pftauMaker", "tauspfbyTightIsolationMVA2")
    , taus_pf_byVLooseCombinedIsolationDeltaBetaCorr_handle("pftauMaker", "tauspfbyVLooseCombinedIsolationDeltaBetaCorr")
    , photons_e1x5_handle("photonMaker", "photonse1x5")
    , photons_e2x5Max_handle("photonMaker", "photonse2x5Max")
    , photons_e3x3_handle("photonMaker", "photonse3x3")
    , photons_e5x5_handle("photonMaker", "photonse5x5")
    , photons_ecalIso03_handle("photonMaker", "photonsecalIso03")
    , photons_ecalIso04_handle("photonMaker", "photonsecalIso04")
    , photons_hOverE_handle("photonMaker", "photonshOverE")
    , photons_hcalDepth1TowerSumEtBcConeDR03_handle("photonMaker", "photonshcalDepth1TowerSumEtBcConeDR03")
    , photons_hcalDepth1TowerSumEtBcConeDR04_handle("photonMaker", "photonshcalDepth1TowerSumEtBcConeDR04")
    , photons_hcalDepth2TowerSumEtBcConeDR03_handle("photonMaker", "photonshcalDepth2TowerSumEtBcConeDR03")
    , photons_hcalDepth2TowerSumEtBcConeDR04_handle("photonMaker", "photonshcalDepth2TowerSumEtBcConeDR04")
    , photons_hcalIso03_handle("photonMaker", "photonshcalIso03")
    , photons_hcalIso04_handle("photonMaker", "photonshcalIso04")
    , photons_hcalTowerSumEtBcConeDR03_handle("photonMaker", "photonshcalTowerSumEtBcConeDR03")
    , photons_hcalTowerSumEtBcConeDR04_handle("photonMaker", "photonshcalTowerSumEtBcConeDR04")
    , photons_ntkIsoHollow03_handle("photonMaker", "photonsntkIsoHollow03")
    , photons_ntkIsoHollow04_handle("photonMaker", "photonsntkIsoHollow04")
    , photons_ntkIsoSolid03_handle("photonMaker", "photonsntkIsoSolid03")
    , photons_ntkIsoSolid04_handle("photonMaker", "photonsntkIsoSolid04")
    , photons_sigmaEtaEta_handle("photonMaker", "photonssigmaEtaEta")
    , photons_sigmaIEtaIEta_handle("photonMaker", "photonssigmaIEtaIEta")
    , photons_swissSeed_handle("photonMaker", "photonsswissSeed")
    , photons_tkIsoHollow03_handle("photonMaker", "photonstkIsoHollow03")
    , photons_tkIsoHollow04_handle("photonMaker", "photonstkIsoHollow04")
    , photons_tkIsoSolid03_handle("photonMaker", "photonstkIsoSolid03")
    , photons_tkIsoSolid04_handle("photonMaker", "photonstkIsoSolid04")
    , puInfo_trueNumInteractions_handle("puSummaryInfoMaker", "puInfotrueNumInteractions")
    , convs_chi2_handle("recoConversionMaker", "convschi2")
    , convs_dl_handle("recoConversionMaker", "convsdl")
    , convs_ndof_handle("recoConversionMaker", "convsndof")
    , sparm_values_handle("sParmMaker", "sparmvalues")
    , scs_clustersSize_handle("scMaker", "scsclustersSize")
    , scs_crystalsSize_handle("scMaker", "scscrystalsSize")
    , scs_e1x3_handle("scMaker", "scse1x3")
    , scs_e1x5_handle("scMaker", "scse1x5")
    , scs_e2nd_handle("scMaker", "scse2nd")
    , scs_e2x2_handle("scMaker", "scse2x2")
    , scs_e2x5Max_handle("scMaker", "scse2x5Max")
    , scs_e3x1_handle("scMaker", "scse3x1")
    , scs_e3x2_handle("scMaker", "scse3x2")
    , scs_e3x3_handle("scMaker", "scse3x3")
    , scs_e4x4_handle("scMaker", "scse4x4")
    , scs_e5x5_handle("scMaker", "scse5x5")
    , scs_eMax_handle("scMaker", "scseMax")
    , scs_eSeed_handle("scMaker", "scseSeed")
    , scs_energy_handle("scMaker", "scsenergy")
    , scs_eta_handle("scMaker", "scseta")
    , scs_hoe_handle("scMaker", "scshoe")
    , scs_laserCorMax_handle("scMaker", "scslaserCorMax")
    , scs_laserCorMean_handle("scMaker", "scslaserCorMean")
    , scs_laserCorSeed_handle("scMaker", "scslaserCorSeed")
    , scs_phi_handle("scMaker", "scsphi")
    , scs_preshowerEnergy_handle("scMaker", "scspreshowerEnergy")
    , scs_rawEnergy_handle("scMaker", "scsrawEnergy")
    , scs_sigmaEtaEta_handle("scMaker", "scssigmaEtaEta")
    , scs_sigmaEtaPhi_handle("scMaker", "scssigmaEtaPhi")
    , scs_sigmaIEtaIEta_handle("scMaker", "scssigmaIEtaIEta")
    , scs_sigmaIEtaIEtaSC_handle("scMaker", "scssigmaIEtaIEtaSC")
    , scs_sigmaIEtaIPhi_handle("scMaker", "scssigmaIEtaIPhi")
    , scs_sigmaIEtaIPhiSC_handle("scMaker", "scssigmaIEtaIPhiSC")
    , scs_sigmaIPhiIPhi_handle("scMaker", "scssigmaIPhiIPhi")
    , scs_sigmaIPhiIPhiSC_handle("scMaker", "scssigmaIPhiIPhiSC")
    , scs_sigmaPhiPhi_handle("scMaker", "scssigmaPhiPhi")
    , scs_timeSeed_handle("scMaker", "scstimeSeed")
    , svs_anglePV_handle("secondaryVertexMaker", "svsanglePV")
    , svs_chi2_handle("secondaryVertexMaker", "svschi2")
    , svs_dist3Dsig_handle("secondaryVertexMaker", "svsdist3Dsig")
    , svs_dist3Dval_handle("secondaryVertexMaker", "svsdist3Dval")
    , svs_distXYsig_handle("secondaryVertexMaker", "svsdistXYsig")
    , svs_distXYval_handle("secondaryVertexMaker", "svsdistXYval")
    , svs_ndof_handle("secondaryVertexMaker", "svsndof")
    , svs_prob_handle("secondaryVertexMaker", "svsprob")
    , svs_xError_handle("secondaryVertexMaker", "svsxError")
    , svs_yError_handle("secondaryVertexMaker", "svsyError")
    , svs_zError_handle("secondaryVertexMaker", "svszError")
    , mus_tcmet_deltax_handle("tcmetMaker", "mustcmetdeltax")
    , mus_tcmet_deltay_handle("tcmetMaker", "mustcmetdeltay")
    , pfcands_dzpv_handle("trackIsolationMaker", "pfcandsdzpv")
    , pfcands_trkiso_handle("trackIsolationMaker", "pfcandstrkiso")
    , trks_chi2_handle("trackMaker", "trkschi2")
    , trks_d0_handle("trackMaker", "trksd0")
    , trks_d0Err_handle("trackMaker", "trksd0Err")
    , trks_d0corr_handle("trackMaker", "trksd0corr")
    , trks_d0corrPhi_handle("trackMaker", "trksd0corrPhi")
    , trks_d0phiCov_handle("trackMaker", "trksd0phiCov")
    , trks_etaErr_handle("trackMaker", "trksetaErr")
    , trks_layer1_charge_handle("trackMaker", "trkslayer1charge")
    , trks_ndof_handle("trackMaker", "trksndof")
    , trks_phiErr_handle("trackMaker", "trksphiErr")
    , trks_ptErr_handle("trackMaker", "trksptErr")
    , trks_validFraction_handle("trackMaker", "trksvalidFraction")
    , trks_z0_handle("trackMaker", "trksz0")
    , trks_z0Err_handle("trackMaker", "trksz0Err")
    , trks_z0corr_handle("trackMaker", "trksz0corr")
    , trkjets_cor_handle("trkJetMaker", "trkjetscor")
    , trks_d0Errvtx_handle("trkToVtxAssMaker", "trksd0Errvtx")
    , trks_d0vtx_handle("trkToVtxAssMaker", "trksd0vtx")
    , vtxs_chi2_handle("vertexMaker", "vtxschi2")
    , vtxs_ndof_handle("vertexMaker", "vtxsndof")
    , vtxs_sumpt_handle("vertexMaker", "vtxssumpt")
    , vtxs_xError_handle("vertexMaker", "vtxsxError")
    , vtxs_yError_handle("vertexMaker", "vtxsyError")
    , vtxs_zError_handle("vertexMaker", "vtxszError")
    , bsvtxs_chi2_handle("vertexMakerWithBS", "bsvtxschi2")
    , bsvtxs_ndof_handle("vertexMakerWithBS", "bsvtxsndof")
    , bsvtxs_sumpt_handle("vertexMakerWithBS", "bsvtxssumpt")
    , bsvtxs_xError_handle("vertexMakerWithBS", "bsvtxsxError")
    , bsvtxs_yError_handle("vertexMakerWithBS", "bsvtxsyError")
    , bsvtxs_zError_handle("vertexMakerWithBS", "bsvtxszError")
    , els_convs_dcot_handle("electronMaker", "elsconvsdcot")
    , els_convs_dist_handle("electronMaker", "elsconvsdist")
    , els_convs_radius_handle("electronMaker", "elsconvsradius")
    , mus_stationShowerDeltaR_handle("muonMaker", "musstationShowerDeltaR")
    , mus_stationShowerSizeT_handle("muonMaker", "musstationShowerSizeT")
    , puInfo_instLumi_handle("puSummaryInfoMaker", "puInfoinstLumi")
    , puInfo_sump_highpt_handle("puSummaryInfoMaker", "puInfosumpthighpt")
    , puInfo_sumpt_lowpt_handle("puSummaryInfoMaker", "puInfosumptlowpt")
    , puInfo_zpositions_handle("puSummaryInfoMaker", "puInfozpositions")
    , vtxs_covMatrix_handle("vertexMaker", "vtxscovMatrix")
    , bsvtxs_covMatrix_handle("vertexMakerWithBS", "bsvtxscovMatrix")
    , evt_cscLooseHaloId_handle("beamHaloMaker", "evtcscLooseHaloId")
    , evt_cscTightHaloId_handle("beamHaloMaker", "evtcscTightHaloId")
    , evt_ecalLooseHaloId_handle("beamHaloMaker", "evtecalLooseHaloId")
    , evt_ecalTightHaloId_handle("beamHaloMaker", "evtecalTightHaloId")
    , evt_extremeTightHaloId_handle("beamHaloMaker", "evtextremeTightHaloId")
    , evt_globalLooseHaloId_handle("beamHaloMaker", "evtglobalLooseHaloId")
    , evt_globalTightHaloId_handle("beamHaloMaker", "evtglobalTightHaloId")
    , evt_hcalLooseHaloId_handle("beamHaloMaker", "evthcalLooseHaloId")
    , evt_hcalTightHaloId_handle("beamHaloMaker", "evthcalTightHaloId")
    , evt_looseHaloId_handle("beamHaloMaker", "evtlooseHaloId")
    , evt_nHaloLikeTracks_handle("beamHaloMaker", "evtnHaloLikeTracks")
    , evt_nHaloTriggerCandidates_handle("beamHaloMaker", "evtnHaloTriggerCandidates")
    , evt_tightHaloId_handle("beamHaloMaker", "evttightHaloId")
    , evt_bsType_handle("beamSpotMaker", "evtbsType")
    , evt_bunchCrossing_handle("eventMaker", "evtbunchCrossing")
    , evt_experimentType_handle("eventMaker", "evtexperimentType")
    , evt_isRealData_handle("eventMaker", "evtisRealData")
    , evt_orbitNumber_handle("eventMaker", "evtorbitNumber")
    , evt_storeNumber_handle("eventMaker", "evtstoreNumber")
    , hcalnoise_GetRecHitCount_handle("hcalNoiseSummaryMaker", "hcalnoiseGetRecHitCount")
    , hcalnoise_GetRecHitCount15_handle("hcalNoiseSummaryMaker", "hcalnoiseGetRecHitCount15")
    , hcalnoise_maxHPDHits_handle("hcalNoiseSummaryMaker", "hcalnoisemaxHPDHits")
    , hcalnoise_maxHPDNoOtherHits_handle("hcalNoiseSummaryMaker", "hcalnoisemaxHPDNoOtherHits")
    , hcalnoise_maxRBXHits_handle("hcalNoiseSummaryMaker", "hcalnoisemaxRBXHits")
    , hcalnoise_maxZeros_handle("hcalNoiseSummaryMaker", "hcalnoisemaxZeros")
    , hcalnoise_noiseFilterStatus_handle("hcalNoiseSummaryMaker", "hcalnoisenoiseFilterStatus")
    , hcalnoise_noiseType_handle("hcalNoiseSummaryMaker", "hcalnoisenoiseType")
    , hcalnoise_num10GeVHits_handle("hcalNoiseSummaryMaker", "hcalnoisenum10GeVHits")
    , hcalnoise_num25GeVHits_handle("hcalNoiseSummaryMaker", "hcalnoisenum25GeVHits")
    , hcalnoise_numFlatNoiseChannels_handle("hcalNoiseSummaryMaker", "hcalnoisenumFlatNoiseChannels")
    , hcalnoise_numIsolatedNoiseChannels_handle("hcalNoiseSummaryMaker", "hcalnoisenumIsolatedNoiseChannels")
    , hcalnoise_numProblematicRBXs_handle("hcalNoiseSummaryMaker", "hcalnoisenumProblematicRBXs")
    , hcalnoise_numSpikeNoiseChannels_handle("hcalNoiseSummaryMaker", "hcalnoisenumSpikeNoiseChannels")
    , hcalnoise_numTS4TS5NoiseChannels_handle("hcalNoiseSummaryMaker", "hcalnoisenumTS4TS5NoiseChannels")
    , hcalnoise_numTriangleNoiseChannels_handle("hcalNoiseSummaryMaker", "hcalnoisenumTriangleNoiseChannels")
    , hcalnoise_passHighLevelNoiseFilter_handle("hcalNoiseSummaryMaker", "hcalnoisepassHighLevelNoiseFilter")
    , hcalnoise_passLooseNoiseFilter_handle("hcalNoiseSummaryMaker", "hcalnoisepassLooseNoiseFilter")
    , hcalnoise_passTightNoiseFilter_handle("hcalNoiseSummaryMaker", "hcalnoisepassTightNoiseFilter")
    , l1_nemiso_handle("l1Maker", "l1nemiso")
    , l1_nemnoiso_handle("l1Maker", "l1nemnoiso")
    , l1_njetsc_handle("l1Maker", "l1njetsc")
    , l1_njetsf_handle("l1Maker", "l1njetsf")
    , l1_njetst_handle("l1Maker", "l1njetst")
    , l1_nmus_handle("l1Maker", "l1nmus")
    , ls_lumiSecQual_handle("luminosityMaker", "lslumiSecQual")
    , pdfinfo_id1_handle("pdfinfoMaker", "pdfinfoid1")
    , pdfinfo_id2_handle("pdfinfoMaker", "pdfinfoid2")
    , sparm_subProcessId_handle("sParmMaker", "sparmsubProcessId")
    , evt_ecaliPhiSuspects_handle("beamHaloMaker", "evtecaliPhiSuspects")
    , evt_globaliPhiSuspects_handle("beamHaloMaker", "evtglobaliPhiSuspects")
    , evt_hcaliPhiSuspects_handle("beamHaloMaker", "evthcaliPhiSuspects")
    , els_mc3_id_handle("candToGenAssMaker", "elsmc3id")
    , els_mc3idx_handle("candToGenAssMaker", "elsmc3idx")
    , els_mc3_motherid_handle("candToGenAssMaker", "elsmc3motherid")
    , els_mc3_motheridx_handle("candToGenAssMaker", "elsmc3motheridx")
    , els_mc_id_handle("candToGenAssMaker", "elsmcid")
    , els_mcidx_handle("candToGenAssMaker", "elsmcidx")
    , els_mc_motherid_handle("candToGenAssMaker", "elsmcmotherid")
    , jets_mc3_id_handle("candToGenAssMaker", "jetsmc3id")
    , jets_mc3idx_handle("candToGenAssMaker", "jetsmc3idx")
    , jets_mc_gpidx_handle("candToGenAssMaker", "jetsmcgpidx")
    , jets_mc_id_handle("candToGenAssMaker", "jetsmcid")
    , jets_mcidx_handle("candToGenAssMaker", "jetsmcidx")
    , jets_mc_motherid_handle("candToGenAssMaker", "jetsmcmotherid")
    , mus_mc3_id_handle("candToGenAssMaker", "musmc3id")
    , mus_mc3idx_handle("candToGenAssMaker", "musmc3idx")
    , mus_mc3_motherid_handle("candToGenAssMaker", "musmc3motherid")
    , mus_mc3_motheridx_handle("candToGenAssMaker", "musmc3motheridx")
    , mus_mc_id_handle("candToGenAssMaker", "musmcid")
    , mus_mcidx_handle("candToGenAssMaker", "musmcidx")
    , mus_mc_motherid_handle("candToGenAssMaker", "musmcmotherid")
    , pfjets_mc3_id_handle("candToGenAssMaker", "pfjetsmc3id")
    , pfjets_mc3idx_handle("candToGenAssMaker", "pfjetsmc3idx")
    , pfjets_mc_gpidx_handle("candToGenAssMaker", "pfjetsmcgpidx")
    , pfjets_mc_id_handle("candToGenAssMaker", "pfjetsmcid")
    , pfjets_mcidx_handle("candToGenAssMaker", "pfjetsmcidx")
    , pfjets_mc_motherid_handle("candToGenAssMaker", "pfjetsmcmotherid")
    , photons_mc3_id_handle("candToGenAssMaker", "photonsmc3id")
    , photons_mc3idx_handle("candToGenAssMaker", "photonsmc3idx")
    , photons_mc3_motherid_handle("candToGenAssMaker", "photonsmc3motherid")
    , photons_mc3_motheridx_handle("candToGenAssMaker", "photonsmc3motheridx")
    , photons_mc_id_handle("candToGenAssMaker", "photonsmcid")
    , photons_mcidx_handle("candToGenAssMaker", "photonsmcidx")
    , photons_mc_motherid_handle("candToGenAssMaker", "photonsmcmotherid")
    , trk_mc3_id_handle("candToGenAssMaker", "trkmc3id")
    , trk_mc3idx_handle("candToGenAssMaker", "trkmc3idx")
    , trk_mc3_motherid_handle("candToGenAssMaker", "trkmc3motherid")
    , trk_mc3_motheridx_handle("candToGenAssMaker", "trkmc3motheridx")
    , trk_mc_id_handle("candToGenAssMaker", "trkmcid")
    , trk_mcidx_handle("candToGenAssMaker", "trkmcidx")
    , trk_mc_motherid_handle("candToGenAssMaker", "trkmcmotherid")
    , els_closestJet_handle("elToJetAssMaker", "elsclosestJet")
    , els_closestMuon_handle("elToMuAssMaker", "elsclosestMuon")
    , els_pfelsidx_handle("elToPFElAssMaker", "elspfelsidx")
    , els_category_handle("electronMaker", "elscategory")
    , els_charge_handle("electronMaker", "elscharge")
    , els_ckf_laywithmeas_handle("electronMaker", "elsckflaywithmeas")
    , els_class_handle("electronMaker", "elsclass")
    , els_conv_delMissHits_handle("electronMaker", "elsconvdelMissHits")
    , els_conv_flag_handle("electronMaker", "elsconvflag")
    , els_conv_gsftkidx_handle("electronMaker", "elsconvgsftkidx")
    , els_conv_old_delMissHits_handle("electronMaker", "elsconvolddelMissHits")
    , els_conv_old_flag_handle("electronMaker", "elsconvoldflag")
    , els_conv_old_gsftkidx_handle("electronMaker", "elsconvoldgsftkidx")
    , els_conv_old_tkidx_handle("electronMaker", "elsconvoldtkidx")
    , els_conv_tkidx_handle("electronMaker", "elsconvtkidx")
    , els_exp_innerlayers_handle("electronMaker", "elsexpinnerlayers")
    , els_exp_outerlayers_handle("electronMaker", "elsexpouterlayers")
    , els_fiduciality_handle("electronMaker", "elsfiduciality")
    , els_gsftrkidx_handle("electronMaker", "elsgsftrkidx")
    , els_layer1_det_handle("electronMaker", "elslayer1det")
    , els_layer1_layer_handle("electronMaker", "elslayer1layer")
    , els_layer1_sizerphi_handle("electronMaker", "elslayer1sizerphi")
    , els_layer1_sizerz_handle("electronMaker", "elslayer1sizerz")
    , els_lostHits_handle("electronMaker", "elslostHits")
    , els_lost_pixelhits_handle("electronMaker", "elslostpixelhits")
    , els_nSeed_handle("electronMaker", "elsnSeed")
    , els_sccharge_handle("electronMaker", "elssccharge")
    , els_scindex_handle("electronMaker", "elsscindex")
    , els_trk_charge_handle("electronMaker", "elstrkcharge")
    , els_trkidx_handle("electronMaker", "elstrkidx")
    , els_type_handle("electronMaker", "elstype")
    , els_validHits_handle("electronMaker", "elsvalidHits")
    , els_valid_pixelhits_handle("electronMaker", "elsvalidpixelhits")
    , genps_id_handle("genMaker", "genpsid")
    , genps_id_mother_handle("genMaker", "genpsidmother")
    , genps_status_handle("genMaker", "genpsstatus")
    , gsftrks_charge_handle("gsfTrackMaker", "gsftrkscharge")
    , gsftrks_exp_innerlayers_handle("gsfTrackMaker", "gsftrksexpinnerlayers")
    , gsftrks_exp_outerlayers_handle("gsfTrackMaker", "gsftrksexpouterlayers")
    , gsftrks_layer1_det_handle("gsfTrackMaker", "gsftrkslayer1det")
    , gsftrks_layer1_layer_handle("gsfTrackMaker", "gsftrkslayer1layer")
    , gsftrks_layer1_sizerphi_handle("gsfTrackMaker", "gsftrkslayer1sizerphi")
    , gsftrks_layer1_sizerz_handle("gsfTrackMaker", "gsftrkslayer1sizerz")
    , gsftrks_lostHits_handle("gsfTrackMaker", "gsftrkslostHits")
    , gsftrks_lost_pixelhits_handle("gsfTrackMaker", "gsftrkslostpixelhits")
    , gsftrks_nlayers_handle("gsfTrackMaker", "gsftrksnlayers")
    , gsftrks_nlayers3D_handle("gsfTrackMaker", "gsftrksnlayers3D")
    , gsftrks_nlayersLost_handle("gsfTrackMaker", "gsftrksnlayersLost")
    , gsftrks_validHits_handle("gsfTrackMaker", "gsftrksvalidHits")
    , gsftrks_valid_pixelhits_handle("gsfTrackMaker", "gsftrksvalidpixelhits")
    , hyp_ll_charge_handle("hypDilepMaker", "hypllcharge")
    , hyp_ll_id_handle("hypDilepMaker", "hypllid")
    , hyp_ll_index_handle("hypDilepMaker", "hypllindex")
    , hyp_ll_lostHits_handle("hypDilepMaker", "hyplllostHits")
    , hyp_ll_validHits_handle("hypDilepMaker", "hypllvalidHits")
    , hyp_lt_charge_handle("hypDilepMaker", "hypltcharge")
    , hyp_lt_id_handle("hypDilepMaker", "hypltid")
    , hyp_lt_index_handle("hypDilepMaker", "hypltindex")
    , hyp_lt_lostHits_handle("hypDilepMaker", "hypltlostHits")
    , hyp_lt_validHits_handle("hypDilepMaker", "hypltvalidHits")
    , hyp_njets_handle("hypDilepMaker", "hypnjets")
    , hyp_nojets_handle("hypDilepMaker", "hypnojets")
    , hyp_type_handle("hypDilepMaker", "hyptype")
    , hyp_FVFit_ndf_handle("hypDilepVertexMaker", "hypFVFitndf")
    , hyp_FVFit_status_handle("hypDilepVertexMaker", "hypFVFitstatus")
    , hyp_ll_mc_id_handle("hypGenMaker", "hypllmcid")
    , hyp_ll_mc_motherid_handle("hypGenMaker", "hypllmcmotherid")
    , hyp_lt_mc_id_handle("hypGenMaker", "hypltmcid")
    , hyp_lt_mc_motherid_handle("hypGenMaker", "hypltmcmotherid")
    , pfjets_mcflavorAlgo_handle("jetFlavorMaker", "pfjetsmcflavorAlgo")
    , pfjets_mcflavorPhys_handle("jetFlavorMaker", "pfjetsmcflavorPhys")
    , jets_closestElectron_handle("jetToElAssMaker", "jetsclosestElectron")
    , jets_closestMuon_handle("jetToMuAssMaker", "jetsclosestMuon")
    , l1_emiso_ieta_handle("l1Maker", "l1emisoieta")
    , l1_emiso_iphi_handle("l1Maker", "l1emisoiphi")
    , l1_emiso_rawId_handle("l1Maker", "l1emisorawId")
    , l1_emiso_type_handle("l1Maker", "l1emisotype")
    , l1_emnoiso_ieta_handle("l1Maker", "l1emnoisoieta")
    , l1_emnoiso_iphi_handle("l1Maker", "l1emnoisoiphi")
    , l1_emnoiso_rawId_handle("l1Maker", "l1emnoisorawId")
    , l1_emnoiso_type_handle("l1Maker", "l1emnoisotype")
    , l1_jetsc_ieta_handle("l1Maker", "l1jetscieta")
    , l1_jetsc_iphi_handle("l1Maker", "l1jetsciphi")
    , l1_jetsc_rawId_handle("l1Maker", "l1jetscrawId")
    , l1_jetsc_type_handle("l1Maker", "l1jetsctype")
    , l1_jetsf_ieta_handle("l1Maker", "l1jetsfieta")
    , l1_jetsf_iphi_handle("l1Maker", "l1jetsfiphi")
    , l1_jetsf_rawId_handle("l1Maker", "l1jetsfrawId")
    , l1_jetsf_type_handle("l1Maker", "l1jetsftype")
    , l1_jetst_ieta_handle("l1Maker", "l1jetstieta")
    , l1_jetst_iphi_handle("l1Maker", "l1jetstiphi")
    , l1_jetst_rawId_handle("l1Maker", "l1jetstrawId")
    , l1_jetst_type_handle("l1Maker", "l1jetsttype")
    , l1_mus_flags_handle("l1Maker", "l1musflags")
    , l1_mus_q_handle("l1Maker", "l1musq")
    , l1_mus_qual_handle("l1Maker", "l1musqual")
    , l1_mus_qualFlags_handle("l1Maker", "l1musqualFlags")
    , mus_met_flag_handle("metMaker", "musmetflag")
    , mus_closestEle_handle("muToElsAssMaker", "musclosestEle")
    , mus_closestJet_handle("muToJetAssMaker", "musclosestJet")
    , mus_pfmusidx_handle("muToPFMuAssMaker", "muspfmusidx")
    , mus_charge_handle("muonMaker", "muscharge")
    , mus_gfit_validHits_handle("muonMaker", "musgfitvalidHits")
    , mus_gfit_validSTAHits_handle("muonMaker", "musgfitvalidSTAHits")
    , mus_gfit_validSiHits_handle("muonMaker", "musgfitvalidSiHits")
    , mus_goodmask_handle("muonMaker", "musgoodmask")
    , mus_iso03_ntrk_handle("muonMaker", "musiso03ntrk")
    , mus_iso05_ntrk_handle("muonMaker", "musiso05ntrk")
    , mus_lostHits_handle("muonMaker", "muslostHits")
    , mus_muonBestTrackType_handle("muonMaker", "musmuonBestTrackType")
    , mus_nOverlaps_handle("muonMaker", "musnOverlaps")
    , mus_nmatches_handle("muonMaker", "musnmatches")
    , mus_numberOfMatchedStations_handle("muonMaker", "musnumberOfMatchedStations")
    , mus_overlap0_handle("muonMaker", "musoverlap0")
    , mus_overlap1_handle("muonMaker", "musoverlap1")
    , mus_pfcharge_handle("muonMaker", "muspfcharge")
    , mus_pfflag_handle("muonMaker", "muspfflag")
    , mus_pfparticleId_handle("muonMaker", "muspfparticleId")
    , mus_pid_PFMuon_handle("muonMaker", "muspidPFMuon")
    , mus_pid_TM2DCompatibilityLoose_handle("muonMaker", "muspidTM2DCompatibilityLoose")
    , mus_pid_TM2DCompatibilityTight_handle("muonMaker", "muspidTM2DCompatibilityTight")
    , mus_pid_TMLastStationLoose_handle("muonMaker", "muspidTMLastStationLoose")
    , mus_pid_TMLastStationTight_handle("muonMaker", "muspidTMLastStationTight")
    , mus_sta_validHits_handle("muonMaker", "musstavalidHits")
    , mus_timeDirection_handle("muonMaker", "mustimeDirection")
    , mus_timeNumStationsUsed_handle("muonMaker", "mustimeNumStationsUsed")
    , mus_trk_charge_handle("muonMaker", "mustrkcharge")
    , mus_trkidx_handle("muonMaker", "mustrkidx")
    , mus_type_handle("muonMaker", "mustype")
    , mus_validHits_handle("muonMaker", "musvalidHits")
    , pfcands_charge_handle("pfCandidateMaker", "pfcandscharge")
    , pfcands_flag_handle("pfCandidateMaker", "pfcandsflag")
    , pfcands_particleId_handle("pfCandidateMaker", "pfcandsparticleId")
    , pfcands_pfelsidx_handle("pfCandidateMaker", "pfcandspfelsidx")
    , pfcands_pfmusidx_handle("pfCandidateMaker", "pfcandspfmusidx")
    , pfcands_trkidx_handle("pfCandidateMaker", "pfcandstrkidx")
    , pfcands_vtxidx_handle("pfCandidateMaker", "pfcandsvtxidx")
    , pfels_elsidx_handle("pfElToElAssMaker", "pfelselsidx")
    , pfels_charge_handle("pfElectronMaker", "pfelscharge")
    , pfels_flag_handle("pfElectronMaker", "pfelsflag")
    , pfels_particleId_handle("pfElectronMaker", "pfelsparticleId")
    , pfjets_chargedHadronMultiplicity_handle("pfJetMaker", "pfjetschargedHadronMultiplicity")
    , pfjets_chargedMultiplicity_handle("pfJetMaker", "pfjetschargedMultiplicity")
    , pfjets_electronMultiplicity_handle("pfJetMaker", "pfjetselectronMultiplicity")
    , pfjets_hfEmMultiplicity_handle("pfJetMaker", "pfjetshfEmMultiplicity")
    , pfjets_hfHadronMultiplicity_handle("pfJetMaker", "pfjetshfHadronMultiplicity")
    , pfjets_muonMultiplicity_handle("pfJetMaker", "pfjetsmuonMultiplicity")
    , pfjets_neutralHadronMultiplicity_handle("pfJetMaker", "pfjetsneutralHadronMultiplicity")
    , pfjets_neutralMultiplicity_handle("pfJetMaker", "pfjetsneutralMultiplicity")
    , pfjets_photonMultiplicity_handle("pfJetMaker", "pfjetsphotonMultiplicity")
    , pfmus_musidx_handle("pfMuToMuAssMaker", "pfmusmusidx")
    , pfmus_charge_handle("pfMuonMaker", "pfmuscharge")
    , pfmus_flag_handle("pfMuonMaker", "pfmusflag")
    , pfmus_particleId_handle("pfMuonMaker", "pfmusparticleId")
    , taus_pf_charge_handle("pftauMaker", "tauspfcharge")
    , taus_pf_pfjetIndex_handle("pftauMaker", "tauspfpfjetIndex")
    , photons_fiduciality_handle("photonMaker", "photonsfiduciality")
    , photons_scindex_handle("photonMaker", "photonsscindex")
    , puInfo_bunchCrossing_handle("puSummaryInfoMaker", "puInfobunchCrossing")
    , puInfo_nPUvertices_handle("puSummaryInfoMaker", "puInfonPUvertices")
    , convs_algo_handle("recoConversionMaker", "convsalgo")
    , convs_isConverted_handle("recoConversionMaker", "convsisConverted")
    , convs_quality_handle("recoConversionMaker", "convsquality")
    , scs_detIdSeed_handle("scMaker", "scsdetIdSeed")
    , scs_elsidx_handle("scMaker", "scselsidx")
    , scs_severitySeed_handle("scMaker", "scsseveritySeed")
    , svs_isKs_handle("secondaryVertexMaker", "svsisKs")
    , svs_isLambda_handle("secondaryVertexMaker", "svsisLambda")
    , svs_mc3_id_handle("secondaryVertexMaker", "svsmc3id")
    , svs_nTrks_handle("secondaryVertexMaker", "svsnTrks")
    , mus_tcmet_flag_handle("tcmetMaker", "mustcmetflag")
    , trks_algo_handle("trackMaker", "trksalgo")
    , trks_charge_handle("trackMaker", "trkscharge")
    , trks_exp_innerlayers_handle("trackMaker", "trksexpinnerlayers")
    , trks_exp_outerlayers_handle("trackMaker", "trksexpouterlayers")
    , trks_layer1_det_handle("trackMaker", "trkslayer1det")
    , trks_layer1_layer_handle("trackMaker", "trkslayer1layer")
    , trks_layer1_sizerphi_handle("trackMaker", "trkslayer1sizerphi")
    , trks_layer1_sizerz_handle("trackMaker", "trkslayer1sizerz")
    , trks_lostHits_handle("trackMaker", "trkslostHits")
    , trks_lost_pixelhits_handle("trackMaker", "trkslostpixelhits")
    , trks_nLoops_handle("trackMaker", "trksnLoops")
    , trks_nlayers_handle("trackMaker", "trksnlayers")
    , trks_nlayers3D_handle("trackMaker", "trksnlayers3D")
    , trks_nlayersLost_handle("trackMaker", "trksnlayersLost")
    , trks_pvidx0_handle("trackMaker", "trkspvidx0")
    , trks_pvidx1_handle("trackMaker", "trkspvidx1")
    , trks_qualityMask_handle("trackMaker", "trksqualityMask")
    , trks_validHits_handle("trackMaker", "trksvalidHits")
    , trks_valid_pixelhits_handle("trackMaker", "trksvalidpixelhits")
    , trks_elsidx_handle("trackToElsAssMaker", "trkselsidx")
    , trk_musidx_handle("trackToMuonAssMaker", "trkmusidx")
    , trkjets_ntrks_handle("trkJetMaker", "trkjetsntrks")
    , trkjets_vtxs_idx_handle("trkJetMaker", "trkjetsvtxsidx")
    , vtxs_isFake_handle("vertexMaker", "vtxsisFake")
    , vtxs_isValid_handle("vertexMaker", "vtxsisValid")
    , vtxs_tracksSize_handle("vertexMaker", "vtxstracksSize")
    , bsvtxs_isFake_handle("vertexMakerWithBS", "bsvtxsisFake")
    , bsvtxs_isValid_handle("vertexMakerWithBS", "bsvtxsisValid")
    , bsvtxs_tracksSize_handle("vertexMakerWithBS", "bsvtxstracksSize")
    , els_convs_delMissHits_handle("electronMaker", "elsconvsdelMissHits")
    , els_convs_flag_handle("electronMaker", "elsconvsflag")
    , els_convs_gsftkidx_handle("electronMaker", "elsconvsgsftkidx")
    , els_convs_tkidx_handle("electronMaker", "elsconvstkidx")
    , genps_lepdaughter_id_handle("genMaker", "genpslepdaughterid")
    , genps_lepdaughter_idx_handle("genMaker", "genpslepdaughteridx")
    , hlt_trigObjs_id_handle("hltMaker", "hlttrigObjsid")
    , hyp_jets_idx_handle("hypDilepMaker", "hypjetsidx")
    , hyp_other_jets_idx_handle("hypDilepMaker", "hypotherjetsidx")
    , mus_nStationCorrelatedHits_handle("muonMaker", "musnStationCorrelatedHits")
    , mus_nStationHits_handle("muonMaker", "musnStationHits")
    , pfjets_pfcandIndicies_handle("pfJetMaker", "pfjetspfcandIndicies")
    , taus_pf_pfcandIndicies_handle("pftauMaker", "tauspfpfcandIndicies")
    , puInfo_ntrks_highpt_handle("puSummaryInfoMaker", "puInfontrkshighpt")
    , puInfo_ntrks_lowpt_handle("puSummaryInfoMaker", "puInfontrkslowpt")
    , convs_nHitsBeforeVtx_handle("recoConversionMaker", "convsnHitsBeforeVtx")
    , convs_tkalgo_handle("recoConversionMaker", "convstkalgo")
    , convs_tkidx_handle("recoConversionMaker", "convstkidx")
    , els_HLT_Ele17_Ele8_L1sL1DoubleEG137_version_handle("elToTrigAssMaker", "elsHLTEle17Ele8L1sL1DoubleEG137version")
    , els_HLT_Ele17_Ele8_LeadingLeg_version_handle("elToTrigAssMaker", "elsHLTEle17Ele8LeadingLegversion")
    , els_HLT_Ele17_Ele8_Mass50_LeadingLeg_version_handle("elToTrigAssMaker", "elsHLTEle17Ele8Mass50LeadingLegversion")
    , els_HLT_Ele17_Ele8_Mass50_TrailingLeg_version_handle("elToTrigAssMaker", "elsHLTEle17Ele8Mass50TrailingLegversion")
    , els_HLT_Ele17_Ele8_TrailingLeg_version_handle("elToTrigAssMaker", "elsHLTEle17Ele8TrailingLegversion")
    , els_HLT_Ele17_Ele8_version_handle("elToTrigAssMaker", "elsHLTEle17Ele8version")
    , els_HLT_Ele20_SC4_Mass50_LeadingLeg_version_handle("elToTrigAssMaker", "elsHLTEle20SC4Mass50LeadingLegversion")
    , els_HLT_Ele20_SC4_Mass50_TrailingLeg_version_handle("elToTrigAssMaker", "elsHLTEle20SC4Mass50TrailingLegversion")
    , els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_version_handle("elToTrigAssMaker", "elsHLTEle27WP80L1sL1SingleEG20ORL1SingleEG22version")
    , els_HLT_Ele27_WP80_version_handle("elToTrigAssMaker", "elsHLTEle27WP80version")
    , els_HLT_Ele32_SC17_Mass50_LeadingLeg_version_handle("elToTrigAssMaker", "elsHLTEle32SC17Mass50LeadingLegversion")
    , els_HLT_Ele32_SC17_Mass50_TrailingLeg_version_handle("elToTrigAssMaker", "elsHLTEle32SC17Mass50TrailingLegversion")
    , els_HLT_Mu17_Ele8_TrailingLeg_version_handle("elToTrigAssMaker", "elsHLTMu17Ele8TrailingLegversion")
    , els_HLT_Mu17_Ele8_version_handle("elToTrigAssMaker", "elsHLTMu17Ele8version")
    , els_HLT_Mu8_Ele17_version_handle("elToTrigAssMaker", "elsHLTMu8Ele17version")
    , evt_nels_handle("electronMaker", "evtnels")
    , evt_detectorStatus_handle("eventMaker", "evtdetectorStatus")
    , evt_event_handle("eventMaker", "evtevent")
    , evt_lumiBlock_handle("eventMaker", "evtlumiBlock")
    , evt_run_handle("eventMaker", "evtrun")
    , genps_flavorHistoryFilterResult_handle("flavorHistoryMaker", "genpsflavorHistoryFilterResult")
    , evt_ngenjets_handle("genJetMaker", "evtngenjets")
    , genps_signalProcessID_handle("genMaker", "genpssignalProcessID")
    , evt_njets_handle("jetMaker", "evtnjets")
    , l1_bits1_handle("l1Maker", "l1bits1")
    , l1_bits2_handle("l1Maker", "l1bits2")
    , l1_bits3_handle("l1Maker", "l1bits3")
    , l1_bits4_handle("l1Maker", "l1bits4")
    , l1_techbits1_handle("l1Maker", "l1techbits1")
    , l1_techbits2_handle("l1Maker", "l1techbits2")
    , ls_lsNumber_handle("luminosityMaker", "lslsNumber")
    , ls_numOrbit_handle("luminosityMaker", "lsnumOrbit")
    , ls_startOrbit_handle("luminosityMaker", "lsstartOrbit")
    , mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_version_handle("muToTrigAssMaker", "musHLTIsoMu24eta2p1L1sMu16Eta2p1version")
    , mus_HLT_IsoMu24_eta2p1_version_handle("muToTrigAssMaker", "musHLTIsoMu24eta2p1version")
    , mus_HLT_Mu17_Ele8_LeadingLeg_version_handle("muToTrigAssMaker", "musHLTMu17Ele8LeadingLegversion")
    , mus_HLT_Mu17_Ele8_version_handle("muToTrigAssMaker", "musHLTMu17Ele8version")
    , mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_version_handle("muToTrigAssMaker", "musHLTMu17Mu8L1sL1DoubleMu10MuOpenversion")
    , mus_HLT_Mu17_Mu8_LeadingLeg_version_handle("muToTrigAssMaker", "musHLTMu17Mu8LeadingLegversion")
    , mus_HLT_Mu17_Mu8_TrailingLeg_version_handle("muToTrigAssMaker", "musHLTMu17Mu8TrailingLegversion")
    , mus_HLT_Mu17_Mu8_version_handle("muToTrigAssMaker", "musHLTMu17Mu8version")
    , mus_HLT_Mu17_TkMu8_LeadingLeg_version_handle("muToTrigAssMaker", "musHLTMu17TkMu8LeadingLegversion")
    , mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_version_handle("muToTrigAssMaker", "musHLTMu17TkMu8TrailingLegTrkFilteredversion")
    , mus_HLT_Mu17_TkMu8_TrailingLeg_version_handle("muToTrigAssMaker", "musHLTMu17TkMu8TrailingLegversion")
    , mus_HLT_Mu17_TkMu8_version_handle("muToTrigAssMaker", "musHLTMu17TkMu8version")
    , mus_HLT_Mu8_Ele17_TrailingLeg_version_handle("muToTrigAssMaker", "musHLTMu8Ele17TrailingLegversion")
    , mus_HLT_Mu8_Ele17_version_handle("muToTrigAssMaker", "musHLTMu8Ele17version")
    , evt_nphotons_handle("photonMaker", "evtnphotons")
    , evt_ecalRecoStatus_handle("scMaker", "evtecalrecostatus")
    , evt_nscs_handle("scMaker", "evtnscs")
    , evt_ntrkjets_handle("trkJetMaker", "evtntrkjets")
    , evt_nvtxs_handle("vertexMaker", "evtnvtxs")
    , evt_nbsvtxs_handle("vertexMakerWithBS", "evtnbsvtxs")
    , els_HLT_Ele17_Ele8_handle("elToTrigAssMaker", "elsHLTEle17Ele8")
    , els_HLT_Ele17_Ele8_L1sL1DoubleEG137_handle("elToTrigAssMaker", "elsHLTEle17Ele8L1sL1DoubleEG137")
    , els_HLT_Ele17_Ele8_LeadingLeg_handle("elToTrigAssMaker", "elsHLTEle17Ele8LeadingLeg")
    , els_HLT_Ele17_Ele8_Mass50_LeadingLeg_handle("elToTrigAssMaker", "elsHLTEle17Ele8Mass50LeadingLeg")
    , els_HLT_Ele17_Ele8_Mass50_TrailingLeg_handle("elToTrigAssMaker", "elsHLTEle17Ele8Mass50TrailingLeg")
    , els_HLT_Ele17_Ele8_TrailingLeg_handle("elToTrigAssMaker", "elsHLTEle17Ele8TrailingLeg")
    , els_HLT_Ele20_SC4_Mass50_LeadingLeg_handle("elToTrigAssMaker", "elsHLTEle20SC4Mass50LeadingLeg")
    , els_HLT_Ele20_SC4_Mass50_TrailingLeg_handle("elToTrigAssMaker", "elsHLTEle20SC4Mass50TrailingLeg")
    , els_HLT_Ele27_WP80_handle("elToTrigAssMaker", "elsHLTEle27WP80")
    , els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_handle("elToTrigAssMaker", "elsHLTEle27WP80L1sL1SingleEG20ORL1SingleEG22")
    , els_HLT_Ele32_SC17_Mass50_LeadingLeg_handle("elToTrigAssMaker", "elsHLTEle32SC17Mass50LeadingLeg")
    , els_HLT_Ele32_SC17_Mass50_TrailingLeg_handle("elToTrigAssMaker", "elsHLTEle32SC17Mass50TrailingLeg")
    , els_HLT_Mu17_Ele8_handle("elToTrigAssMaker", "elsHLTMu17Ele8")
    , els_HLT_Mu17_Ele8_TrailingLeg_handle("elToTrigAssMaker", "elsHLTMu17Ele8TrailingLeg")
    , els_HLT_Mu8_Ele17_handle("elToTrigAssMaker", "elsHLTMu8Ele17")
    , els_id2012ext_loose_handle("electronMaker", "elsid2012extloose")
    , els_id2012ext_medium_handle("electronMaker", "elsid2012extmedium")
    , els_id2012ext_tight_handle("electronMaker", "elsid2012exttight")
    , els_id2012ext_veto_handle("electronMaker", "elsid2012extveto")
    , els_id2012_loose_handle("electronMaker", "elsid2012loose")
    , els_id2012_medium_handle("electronMaker", "elsid2012medium")
    , els_id2012_tight_handle("electronMaker", "elsid2012tight")
    , els_id2012_veto_handle("electronMaker", "elsid2012veto")
    , hlt_prescales_handle("hltMaker", "hltprescales")
    , l1_prescales_handle("l1Maker", "l1prescales")
    , l1_techtrigprescales_handle("l1Maker", "l1techtrigprescales")
    , mus_HLT_IsoMu24_eta2p1_handle("muToTrigAssMaker", "musHLTIsoMu24eta2p1")
    , mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_handle("muToTrigAssMaker", "musHLTIsoMu24eta2p1L1sMu16Eta2p1")
    , mus_HLT_Mu17_Ele8_handle("muToTrigAssMaker", "musHLTMu17Ele8")
    , mus_HLT_Mu17_Ele8_LeadingLeg_handle("muToTrigAssMaker", "musHLTMu17Ele8LeadingLeg")
    , mus_HLT_Mu17_Mu8_handle("muToTrigAssMaker", "musHLTMu17Mu8")
    , mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_handle("muToTrigAssMaker", "musHLTMu17Mu8L1sL1DoubleMu10MuOpen")
    , mus_HLT_Mu17_Mu8_LeadingLeg_handle("muToTrigAssMaker", "musHLTMu17Mu8LeadingLeg")
    , mus_HLT_Mu17_Mu8_TrailingLeg_handle("muToTrigAssMaker", "musHLTMu17Mu8TrailingLeg")
    , mus_HLT_Mu17_TkMu8_handle("muToTrigAssMaker", "musHLTMu17TkMu8")
    , mus_HLT_Mu17_TkMu8_LeadingLeg_handle("muToTrigAssMaker", "musHLTMu17TkMu8LeadingLeg")
    , mus_HLT_Mu17_TkMu8_TrailingLeg_handle("muToTrigAssMaker", "musHLTMu17TkMu8TrailingLeg")
    , mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_handle("muToTrigAssMaker", "musHLTMu17TkMu8TrailingLegTrkFiltered")
    , mus_HLT_Mu8_Ele17_handle("muToTrigAssMaker", "musHLTMu8Ele17")
    , mus_HLT_Mu8_Ele17_TrailingLeg_handle("muToTrigAssMaker", "musHLTMu8Ele17TrailingLeg")
    , evt_timestamp_handle("eventMaker", "evttimestamp")
{
}

void CMS2::Init()
{
    hlt_bits_handle.Clear();
    evt_CMS2tag_handle.Clear();
    evt_dataset_handle.Clear();
    hlt_trigNames_handle.Clear();
    l1_techtrigNames_handle.Clear();
    l1_trigNames_handle.Clear();
    evt_errCategory_handle.Clear();
    evt_errModule_handle.Clear();
    evt_errSeverity_handle.Clear();
    sparm_comment_handle.Clear();
    sparm_names_handle.Clear();
    evt_eventHasHalo_handle.Clear();
    hcalnoise_HasBadRBXTS4TS5_handle.Clear();
    ls_isValid_handle.Clear();
    filt_ecalBE_handle.Clear();
    filt_ecalDR_handle.Clear();
    filt_ecalLaser_handle.Clear();
    filt_ecalTP_handle.Clear();
    filt_eeBadSc_handle.Clear();
    filt_greedyMuon_handle.Clear();
    filt_hcalLaser_handle.Clear();
    filt_inconsistentMuon_handle.Clear();
    filt_jetIDFailure_handle.Clear();
    filt_multiEvent_handle.Clear();
    filt_trackingFailure_handle.Clear();
    evt_hbheFilter_handle.Clear();
    els_conv_vtx_flag_handle.Clear();
    els_passingMvaPreselection_handle.Clear();
    els_passingPflowPreselection_handle.Clear();
    mus_isRPCMuon_handle.Clear();
    mus_tightMatch_handle.Clear();
    mus_updatedSta_handle.Clear();
    pfcands_isMuIso_handle.Clear();
    photons_haspixelSeed_handle.Clear();
    jets_closestElectron_DR_handle.Clear();
    jets_closestMuon_DR_handle.Clear();
    evt_bs_Xwidth_handle.Clear();
    evt_bs_XwidthErr_handle.Clear();
    evt_bs_Ywidth_handle.Clear();
    evt_bs_YwidthErr_handle.Clear();
    evt_bs_dxdz_handle.Clear();
    evt_bs_dxdzErr_handle.Clear();
    evt_bs_dydz_handle.Clear();
    evt_bs_dydzErr_handle.Clear();
    evt_bs_sigmaZ_handle.Clear();
    evt_bs_sigmaZErr_handle.Clear();
    evt_bs_xErr_handle.Clear();
    evt_bs_yErr_handle.Clear();
    evt_bs_zErr_handle.Clear();
    evt_bField_handle.Clear();
    evt_rho_handle.Clear();
    evt_rhoJEC_handle.Clear();
    evt_fixgrid_all_rho_handle.Clear();
    evt_fixgridfastjet_all_rho_handle.Clear();
    gen_met_handle.Clear();
    gen_metPhi_handle.Clear();
    genps_alphaQCD_handle.Clear();
    genps_pthat_handle.Clear();
    genps_qScale_handle.Clear();
    genps_weight_handle.Clear();
    gen_sumEt_handle.Clear();
    hcalnoise_GetRecHitEnergy_handle.Clear();
    hcalnoise_GetRecHitEnergy15_handle.Clear();
    hcalnoise_GetTotalCalibCharge_handle.Clear();
    hcalnoise_TS4TS5NoiseSumE_handle.Clear();
    hcalnoise_TS4TS5NoiseSumEt_handle.Clear();
    hcalnoise_eventChargeFraction_handle.Clear();
    hcalnoise_eventEMEnergy_handle.Clear();
    hcalnoise_eventEMFraction_handle.Clear();
    hcalnoise_eventHadEnergy_handle.Clear();
    hcalnoise_eventTrackEnergy_handle.Clear();
    hcalnoise_flatNoiseSumE_handle.Clear();
    hcalnoise_flatNoiseSumEt_handle.Clear();
    hcalnoise_isolatedNoiseSumE_handle.Clear();
    hcalnoise_isolatedNoiseSumEt_handle.Clear();
    hcalnoise_max10GeVHitTime_handle.Clear();
    hcalnoise_max25GeVHitTime_handle.Clear();
    hcalnoise_maxE10TS_handle.Clear();
    hcalnoise_maxE2Over10TS_handle.Clear();
    hcalnoise_maxE2TS_handle.Clear();
    hcalnoise_min10GeVHitTime_handle.Clear();
    hcalnoise_min25GeVHitTime_handle.Clear();
    hcalnoise_minE10TS_handle.Clear();
    hcalnoise_minE2Over10TS_handle.Clear();
    hcalnoise_minE2TS_handle.Clear();
    hcalnoise_minHPDEMF_handle.Clear();
    hcalnoise_minRBXEMF_handle.Clear();
    hcalnoise_rms10GeVHitTime_handle.Clear();
    hcalnoise_rms25GeVHitTime_handle.Clear();
    hcalnoise_spikeNoiseSumE_handle.Clear();
    hcalnoise_spikeNoiseSumEt_handle.Clear();
    hcalnoise_triangleNoiseSumE_handle.Clear();
    hcalnoise_triangleNoiseSumEt_handle.Clear();
    evt_kt6calo_central_rho_handle.Clear();
    evt_kt6calo_muhlt_rho_handle.Clear();
    evt_kt6calo_rho_handle.Clear();
    evt_kt6pf_ctrChargedPU_rho_handle.Clear();
    evt_kt6pf_ctrNeutral_rho_handle.Clear();
    evt_kt6pf_ctrNeutralTight_rho_handle.Clear();
    evt_kt6pf_foregiso_rho_handle.Clear();
    l1_met_etTot_handle.Clear();
    l1_met_met_handle.Clear();
    l1_mht_htTot_handle.Clear();
    l1_mht_mht_handle.Clear();
    ls_avgInsDelLumi_handle.Clear();
    ls_avgInsDelLumiErr_handle.Clear();
    ls_avgInsRecLumi_handle.Clear();
    ls_avgInsRecLumiErr_handle.Clear();
    ls_deadFrac_handle.Clear();
    ls_intgDelLumi_handle.Clear();
    ls_intgRecLumi_handle.Clear();
    ls_lumiSectionLength_handle.Clear();
    evt_ecalendcapm_met_handle.Clear();
    evt_ecalendcapm_metPhi_handle.Clear();
    evt_ecalendcapp_met_handle.Clear();
    evt_ecalendcapp_metPhi_handle.Clear();
    evt_ecalmet_handle.Clear();
    evt_ecalmetPhi_handle.Clear();
    evt_endcapm_met_handle.Clear();
    evt_endcapm_metPhi_handle.Clear();
    evt_endcapp_met_handle.Clear();
    evt_endcapp_metPhi_handle.Clear();
    evt_hcalendcapm_met_handle.Clear();
    evt_hcalendcapm_metPhi_handle.Clear();
    evt_hcalendcapp_met_handle.Clear();
    evt_hcalendcapp_metPhi_handle.Clear();
    evt_hcalmet_handle.Clear();
    evt_hcalmetPhi_handle.Clear();
    evt_met_handle.Clear();
    evt_met_EtGt3_handle.Clear();
    evt_metHO_handle.Clear();
    evt_metHOPhi_handle.Clear();
    evt_metHOSig_handle.Clear();
    evt_metMuonCorr_handle.Clear();
    evt_metMuonCorrPhi_handle.Clear();
    evt_metMuonCorrSig_handle.Clear();
    evt_metMuonJESCorr_handle.Clear();
    evt_metMuonJESCorrPhi_handle.Clear();
    evt_metMuonJESCorrSig_handle.Clear();
    evt_metNoHF_handle.Clear();
    evt_metNoHFHO_handle.Clear();
    evt_metNoHFHOPhi_handle.Clear();
    evt_metNoHFHOSig_handle.Clear();
    evt_metNoHFPhi_handle.Clear();
    evt_metNoHFSig_handle.Clear();
    evt_metOpt_handle.Clear();
    evt_metOptHO_handle.Clear();
    evt_metOptHOPhi_handle.Clear();
    evt_metOptHOSig_handle.Clear();
    evt_metOptNoHF_handle.Clear();
    evt_metOptNoHFHO_handle.Clear();
    evt_metOptNoHFHOPhi_handle.Clear();
    evt_metOptNoHFHOSig_handle.Clear();
    evt_metOptNoHFPhi_handle.Clear();
    evt_metOptNoHFSig_handle.Clear();
    evt_metOptPhi_handle.Clear();
    evt_metOptSig_handle.Clear();
    evt_metPhi_handle.Clear();
    evt_metPhi_EtGt3_handle.Clear();
    evt_metSig_handle.Clear();
    evt_sumet_handle.Clear();
    evt_sumet_EtGt3_handle.Clear();
    evt_sumetHO_handle.Clear();
    evt_sumetMuonCorr_handle.Clear();
    evt_sumetMuonJESCorr_handle.Clear();
    evt_sumetNoHF_handle.Clear();
    evt_sumetNoHFHO_handle.Clear();
    evt_sumetOpt_handle.Clear();
    evt_sumetOptHO_handle.Clear();
    evt_sumetOptNoHF_handle.Clear();
    evt_sumetOptNoHFHO_handle.Clear();
    pdfinfo_pdf1_handle.Clear();
    pdfinfo_pdf2_handle.Clear();
    pdfinfo_scale_handle.Clear();
    pdfinfo_x1_handle.Clear();
    pdfinfo_x2_handle.Clear();
    evt_fixgrid_rho_all_handle.Clear();
    evt_fixgrid_rho_ctr_handle.Clear();
    evt_fixgrid_rho_fwd_handle.Clear();
    evt_pfmet_handle.Clear();
    evt_pfmetPhi_handle.Clear();
    evt_pfmetPhi_type1cor_handle.Clear();
    evt_pfmetSig_handle.Clear();
    evt_pfmetSignificance_handle.Clear();
    evt_pfmet_type1cor_handle.Clear();
    evt_pfsumet_handle.Clear();
    sparm_filterEfficiency_handle.Clear();
    sparm_pdfScale_handle.Clear();
    sparm_pdfWeight1_handle.Clear();
    sparm_pdfWeight2_handle.Clear();
    sparm_weight_handle.Clear();
    sparm_xsec_handle.Clear();
    evt_pf_tcmet_handle.Clear();
    evt_pf_tcmetPhi_handle.Clear();
    evt_pf_tcmetSig_handle.Clear();
    evt_pf_tcsumet_handle.Clear();
    evt_tcmet_handle.Clear();
    evt_tcmetPhi_handle.Clear();
    evt_tcmetSig_handle.Clear();
    evt_tcsumet_handle.Clear();
    evt_ww_rho_act_handle.Clear();
    evt_ww_rho_handle.Clear();
    evt_ww_rho_rnd_handle.Clear();
    evt_ww_rho_vor_handle.Clear();
    evt_bsp4_handle.Clear();
    l1_met_p4_handle.Clear();
    l1_mht_p4_handle.Clear();
    els_mc_motherp4_handle.Clear();
    els_mc_p4_handle.Clear();
    jets_mc_gp_p4_handle.Clear();
    jets_mc_motherp4_handle.Clear();
    jets_mc_p4_handle.Clear();
    mus_mc_motherp4_handle.Clear();
    mus_mc_p4_handle.Clear();
    pfjets_mc_gp_p4_handle.Clear();
    pfjets_mc_motherp4_handle.Clear();
    pfjets_mc_p4_handle.Clear();
    photons_mc_motherp4_handle.Clear();
    photons_mc_p4_handle.Clear();
    trk_mcp4_handle.Clear();
    els_conv_pos_p4_handle.Clear();
    els_inner_position_handle.Clear();
    els_outer_position_handle.Clear();
    els_p4_handle.Clear();
    els_p4In_handle.Clear();
    els_p4Out_handle.Clear();
    els_trk_p4_handle.Clear();
    els_vertex_p4_handle.Clear();
    genjets_p4_handle.Clear();
    genps_p4_handle.Clear();
    genps_prod_vtx_handle.Clear();
    gsftrks_inner_position_handle.Clear();
    gsftrks_outer_p4_handle.Clear();
    gsftrks_outer_position_handle.Clear();
    gsftrks_p4_handle.Clear();
    gsftrks_vertex_p4_handle.Clear();
    hyp_ll_p4_handle.Clear();
    hyp_ll_trk_p4_handle.Clear();
    hyp_lt_p4_handle.Clear();
    hyp_lt_trk_p4_handle.Clear();
    hyp_p4_handle.Clear();
    hyp_FVFit_p4_handle.Clear();
    hyp_FVFit_v4_handle.Clear();
    hyp_ll_mc_p4_handle.Clear();
    hyp_lt_mc_p4_handle.Clear();
    jets_p4_handle.Clear();
    jets_vertex_p4_handle.Clear();
    l1_emiso_p4_handle.Clear();
    l1_emnoiso_p4_handle.Clear();
    l1_jetsc_p4_handle.Clear();
    l1_jetsf_p4_handle.Clear();
    l1_jetst_p4_handle.Clear();
    l1_mus_p4_handle.Clear();
    mus_ecalpos_p4_handle.Clear();
    mus_fitpicky_p4_handle.Clear();
    mus_fittev_p4_handle.Clear();
    mus_fittpfms_p4_handle.Clear();
    mus_gfit_outerPos_p4_handle.Clear();
    mus_gfit_p4_handle.Clear();
    mus_gfit_vertex_p4_handle.Clear();
    mus_p4_handle.Clear();
    mus_pfp4_handle.Clear();
    mus_pfposAtEcal_p4_handle.Clear();
    mus_sta_p4_handle.Clear();
    mus_sta_vertex_p4_handle.Clear();
    mus_trk_p4_handle.Clear();
    mus_vertex_p4_handle.Clear();
    pfcands_p4_handle.Clear();
    pfcands_posAtEcal_p4_handle.Clear();
    pfels_p4_handle.Clear();
    pfels_posAtEcal_p4_handle.Clear();
    pfjets_p4_handle.Clear();
    pfmus_p4_handle.Clear();
    pfmus_posAtEcal_p4_handle.Clear();
    taus_pf_p4_handle.Clear();
    photons_p4_handle.Clear();
    convs_refitPairMom_p4_handle.Clear();
    convs_vtxpos_handle.Clear();
    scs_p4_handle.Clear();
    scs_pos_p4_handle.Clear();
    scs_vtx_p4_handle.Clear();
    svs_flight_handle.Clear();
    svs_mc3_p4_handle.Clear();
    svs_p4_handle.Clear();
    svs_position_handle.Clear();
    svs_refitp4_handle.Clear();
    trks_inner_position_handle.Clear();
    trks_outer_p4_handle.Clear();
    trks_outer_position_handle.Clear();
    trks_trk_p4_handle.Clear();
    trks_vertex_p4_handle.Clear();
    trkjets_p4_handle.Clear();
    vtxs_position_handle.Clear();
    bsvtxs_position_handle.Clear();
    els_convs_pos_p4_handle.Clear();
    genps_lepdaughter_p4_handle.Clear();
    hlt_trigObjs_p4_handle.Clear();
    hyp_jets_p4_handle.Clear();
    hyp_other_jets_p4_handle.Clear();
    jpts_combinedSecondaryVertexBJetTag_handle.Clear();
    jpts_combinedSecondaryVertexMVABJetTag_handle.Clear();
    jpts_jetBProbabilityBJetTag_handle.Clear();
    jpts_jetProbabilityBJetTag_handle.Clear();
    jpts_simpleSecondaryVertexBJetTag_handle.Clear();
    jpts_simpleSecondaryVertexHighEffBJetTag_handle.Clear();
    jpts_simpleSecondaryVertexHighPurBJetTags_handle.Clear();
    jpts_softElectronByIP3dBJetTag_handle.Clear();
    jpts_softElectronByPtBJetTag_handle.Clear();
    jpts_softElectronTag_handle.Clear();
    jpts_softMuonBJetTag_handle.Clear();
    jpts_softMuonByIP3dBJetTag_handle.Clear();
    jpts_softMuonByPtBJetTag_handle.Clear();
    jpts_trackCountingHighEffBJetTag_handle.Clear();
    jpts_trackCountingHighPurBJetTag_handle.Clear();
    jets_combinedSecondaryVertexBJetTag_handle.Clear();
    jets_combinedSecondaryVertexMVABJetTag_handle.Clear();
    jets_jetBProbabilityBJetTag_handle.Clear();
    jets_jetProbabilityBJetTag_handle.Clear();
    jets_simpleSecondaryVertexBJetTag_handle.Clear();
    jets_simpleSecondaryVertexHighEffBJetTag_handle.Clear();
    jets_simpleSecondaryVertexHighPurBJetTags_handle.Clear();
    jets_softElectronByIP3dBJetTag_handle.Clear();
    jets_softElectronByPtBJetTag_handle.Clear();
    jets_softElectronTag_handle.Clear();
    jets_softMuonBJetTag_handle.Clear();
    jets_softMuonByIP3dBJetTag_handle.Clear();
    jets_softMuonByPtBJetTag_handle.Clear();
    jets_trackCountingHighEffBJetTag_handle.Clear();
    jets_trackCountingHighPurBJetTag_handle.Clear();
    pfjets_combinedSecondaryVertexBJetTag_handle.Clear();
    pfjets_combinedSecondaryVertexMVABJetTag_handle.Clear();
    pfjets_jetBProbabilityBJetTag_handle.Clear();
    pfjets_jetProbabilityBJetTag_handle.Clear();
    pfjets_simpleSecondaryVertexBJetTag_handle.Clear();
    pfjets_simpleSecondaryVertexHighEffBJetTag_handle.Clear();
    pfjets_simpleSecondaryVertexHighPurBJetTags_handle.Clear();
    pfjets_softElectronByIP3dBJetTag_handle.Clear();
    pfjets_softElectronByPtBJetTag_handle.Clear();
    pfjets_softElectronTag_handle.Clear();
    pfjets_softMuonBJetTag_handle.Clear();
    pfjets_softMuonByIP3dBJetTag_handle.Clear();
    pfjets_softMuonByPtBJetTag_handle.Clear();
    pfjets_trackCountingHighEffBJetTag_handle.Clear();
    pfjets_trackCountingHighPurBJetTag_handle.Clear();
    trkjets_combinedSecondaryVertexBJetTag_handle.Clear();
    trkjets_combinedSecondaryVertexMVABJetTag_handle.Clear();
    trkjets_jetBProbabilityBJetTag_handle.Clear();
    trkjets_jetProbabilityBJetTag_handle.Clear();
    trkjets_simpleSecondaryVertexBJetTag_handle.Clear();
    trkjets_simpleSecondaryVertexHighEffBJetTag_handle.Clear();
    trkjets_simpleSecondaryVertexHighPurBJetTags_handle.Clear();
    trkjets_softElectronByIP3dBJetTag_handle.Clear();
    trkjets_softElectronByPtBJetTag_handle.Clear();
    trkjets_softElectronTag_handle.Clear();
    trkjets_softMuonBJetTag_handle.Clear();
    trkjets_softMuonByIP3dBJetTag_handle.Clear();
    trkjets_softMuonByPtBJetTag_handle.Clear();
    trkjets_trackCountingHighEffBJetTag_handle.Clear();
    trkjets_trackCountingHighPurBJetTag_handle.Clear();
    evt_bs_covMatrix_handle.Clear();
    els_mc3dr_handle.Clear();
    els_mcdr_handle.Clear();
    jets_mc3dr_handle.Clear();
    jets_mcdr_handle.Clear();
    jets_mc_emEnergy_handle.Clear();
    jets_mc_gpdr_handle.Clear();
    jets_mc_hadEnergy_handle.Clear();
    jets_mc_invEnergy_handle.Clear();
    jets_mc_otherEnergy_handle.Clear();
    mus_mc3dr_handle.Clear();
    mus_mcdr_handle.Clear();
    pfjets_mc3dr_handle.Clear();
    pfjets_mcdr_handle.Clear();
    pfjets_mc_emEnergy_handle.Clear();
    pfjets_mc_gpdr_handle.Clear();
    pfjets_mc_hadEnergy_handle.Clear();
    pfjets_mc_invEnergy_handle.Clear();
    pfjets_mc_otherEnergy_handle.Clear();
    photons_mc3dr_handle.Clear();
    photons_mcdr_handle.Clear();
    trk_mc3dr_handle.Clear();
    trk_mcdr_handle.Clear();
    els_ecalJuraIso_handle.Clear();
    els_ecalJuraTowerIso_handle.Clear();
    els_hcalConeIso_handle.Clear();
    els_tkJuraIso_handle.Clear();
    els_jetdr_handle.Clear();
    els_musdr_handle.Clear();
    els_isoR03_chpf_radial_handle.Clear();
    els_isoR03_chpf_radialTight_handle.Clear();
    els_isoR03_chpf_radialTight_bv_handle.Clear();
    els_isoR03_chpf_radial_bv_handle.Clear();
    els_isoR03_empf_radial_handle.Clear();
    els_isoR03_empf_radialTight_handle.Clear();
    els_isoR03_empf_radialTight_bv_handle.Clear();
    els_isoR03_empf_radial_bv_handle.Clear();
    els_isoR03_nhpf_radial_handle.Clear();
    els_isoR03_nhpf_radialTight_handle.Clear();
    els_isoR03_nhpf_radialTight_bv_handle.Clear();
    els_isoR03_nhpf_radial_bv_handle.Clear();
    els_isoR03_pf2012n0p5_ch_handle.Clear();
    els_isoR03_pf2012n0p5_em_handle.Clear();
    els_isoR03_pf2012n0p5_nh_handle.Clear();
    els_isoR03_pf_radial_handle.Clear();
    els_isoR03_pf_radialTight_handle.Clear();
    els_isoR03_pf_radialTight_bv_handle.Clear();
    els_isoR03_pf_radial_bv_handle.Clear();
    els_chi2_handle.Clear();
    els_ckf_chi2_handle.Clear();
    els_ckf_ndof_handle.Clear();
    els_conv_dcot_handle.Clear();
    els_conv_dist_handle.Clear();
    els_conv_old_dcot_handle.Clear();
    els_conv_old_dist_handle.Clear();
    els_conv_old_radius_handle.Clear();
    els_conv_radius_handle.Clear();
    els_d0_handle.Clear();
    els_d0Err_handle.Clear();
    els_d0corr_handle.Clear();
    els_dEtaIn_handle.Clear();
    els_dEtaOut_handle.Clear();
    els_dPhiIn_handle.Clear();
    els_dPhiInPhiOut_handle.Clear();
    els_dPhiOut_handle.Clear();
    els_deltaEtaEleClusterTrackAtCalo_handle.Clear();
    els_deltaPhiEleClusterTrackAtCalo_handle.Clear();
    els_e1x5_handle.Clear();
    els_e2x5Max_handle.Clear();
    els_e3x3_handle.Clear();
    els_e5x5_handle.Clear();
    els_eMax_handle.Clear();
    els_eOverPIn_handle.Clear();
    els_eOverPOut_handle.Clear();
    els_eSC_handle.Clear();
    els_eSCPresh_handle.Clear();
    els_eSCRaw_handle.Clear();
    els_eSeed_handle.Clear();
    els_eSeedOverPIn_handle.Clear();
    els_eSeedOverPOut_handle.Clear();
    els_ecalEnergy_handle.Clear();
    els_ecalEnergyError_handle.Clear();
    els_ecalIso_handle.Clear();
    els_ecalIso04_handle.Clear();
    els_etaErr_handle.Clear();
    els_etaSC_handle.Clear();
    els_etaSCwidth_handle.Clear();
    els_fbrem_handle.Clear();
    els_hOverE_handle.Clear();
    els_hcalDepth1OverEcal_handle.Clear();
    els_hcalDepth1TowerSumEt_handle.Clear();
    els_hcalDepth1TowerSumEt04_handle.Clear();
    els_hcalDepth2OverEcal_handle.Clear();
    els_hcalDepth2TowerSumEt_handle.Clear();
    els_hcalDepth2TowerSumEt04_handle.Clear();
    els_hcalIso_handle.Clear();
    els_hcalIso04_handle.Clear();
    els_ip3d_handle.Clear();
    els_ip3derr_handle.Clear();
    els_iso03_pf_handle.Clear();
    els_iso03_pf2012_ch_handle.Clear();
    els_iso03_pf2012_em_handle.Clear();
    els_iso03_pf2012ext_ch_handle.Clear();
    els_iso03_pf2012ext_em_handle.Clear();
    els_iso03_pf2012ext_nh_handle.Clear();
    els_iso03_pf2012_nh_handle.Clear();
    els_iso03_pf_ch_handle.Clear();
    els_iso03_pf_gamma05_handle.Clear();
    els_iso03_pf_nhad05_handle.Clear();
    els_iso04_pf_handle.Clear();
    els_iso04_pf2012_ch_handle.Clear();
    els_iso04_pf2012_em_handle.Clear();
    els_iso04_pf2012ext_ch_handle.Clear();
    els_iso04_pf2012ext_em_handle.Clear();
    els_iso04_pf2012ext_nh_handle.Clear();
    els_iso04_pf2012_nh_handle.Clear();
    els_iso04_pf_ch_handle.Clear();
    els_iso04_pf_gamma05_handle.Clear();
    els_iso04_pf_nhad05_handle.Clear();
    els_layer1_charge_handle.Clear();
    els_lh_handle.Clear();
    els_mva_handle.Clear();
    els_ndof_handle.Clear();
    els_pfChargedHadronIso_handle.Clear();
    els_pfNeutralHadronIso_handle.Clear();
    els_pfPhotonIso_handle.Clear();
    els_phiErr_handle.Clear();
    els_phiSC_handle.Clear();
    els_phiSCwidth_handle.Clear();
    els_ptErr_handle.Clear();
    els_r9_handle.Clear();
    els_sigmaEtaEta_handle.Clear();
    els_sigmaIEtaIEta_handle.Clear();
    els_sigmaIEtaIEtaSC_handle.Clear();
    els_sigmaIEtaIPhi_handle.Clear();
    els_sigmaIPhiIPhi_handle.Clear();
    els_sigmaIPhiIPhiSC_handle.Clear();
    els_sigmaIphiIphi_handle.Clear();
    els_sigmaPhiPhi_handle.Clear();
    els_tkIso_handle.Clear();
    els_tkIso04_handle.Clear();
    els_trackMomentumError_handle.Clear();
    els_trkdr_handle.Clear();
    els_trkshFrac_handle.Clear();
    els_z0_handle.Clear();
    els_z0Err_handle.Clear();
    els_z0corr_handle.Clear();
    gsftrks_chi2_handle.Clear();
    gsftrks_d0_handle.Clear();
    gsftrks_d0Err_handle.Clear();
    gsftrks_d0corr_handle.Clear();
    gsftrks_d0corrPhi_handle.Clear();
    gsftrks_d0phiCov_handle.Clear();
    gsftrks_etaErr_handle.Clear();
    gsftrks_layer1_charge_handle.Clear();
    gsftrks_ndof_handle.Clear();
    gsftrks_phiErr_handle.Clear();
    gsftrks_ptErr_handle.Clear();
    gsftrks_z0_handle.Clear();
    gsftrks_z0Err_handle.Clear();
    gsftrks_z0corr_handle.Clear();
    hyp_Ht_handle.Clear();
    hyp_dPhi_nJet_metMuonJESCorr_handle.Clear();
    hyp_dPhi_nJet_muCorrMet_handle.Clear();
    hyp_dPhi_nJet_tcMet_handle.Clear();
    hyp_dPhi_nJet_unCorrMet_handle.Clear();
    hyp_ll_chi2_handle.Clear();
    hyp_ll_d0_handle.Clear();
    hyp_ll_d0Err_handle.Clear();
    hyp_ll_d0corr_handle.Clear();
    hyp_ll_dPhi_metMuonJESCorr_handle.Clear();
    hyp_ll_dPhi_muCorrMet_handle.Clear();
    hyp_ll_dPhi_tcMet_handle.Clear();
    hyp_ll_dPhi_unCorrMet_handle.Clear();
    hyp_ll_etaErr_handle.Clear();
    hyp_ll_ndof_handle.Clear();
    hyp_ll_phiErr_handle.Clear();
    hyp_ll_ptErr_handle.Clear();
    hyp_ll_z0_handle.Clear();
    hyp_ll_z0Err_handle.Clear();
    hyp_ll_z0corr_handle.Clear();
    hyp_lt_chi2_handle.Clear();
    hyp_lt_d0_handle.Clear();
    hyp_lt_d0Err_handle.Clear();
    hyp_lt_d0corr_handle.Clear();
    hyp_lt_dPhi_metMuonJESCorr_handle.Clear();
    hyp_lt_dPhi_muCorrMet_handle.Clear();
    hyp_lt_dPhi_tcMet_handle.Clear();
    hyp_lt_dPhi_unCorrMet_handle.Clear();
    hyp_lt_etaErr_handle.Clear();
    hyp_lt_ndof_handle.Clear();
    hyp_lt_phiErr_handle.Clear();
    hyp_lt_ptErr_handle.Clear();
    hyp_lt_z0_handle.Clear();
    hyp_lt_z0Err_handle.Clear();
    hyp_lt_z0corr_handle.Clear();
    hyp_mt2_metMuonJESCorr_handle.Clear();
    hyp_mt2_muCorrMet_handle.Clear();
    hyp_mt2_tcMet_handle.Clear();
    hyp_sumJetPt_handle.Clear();
    hyp_FVFit_chi2ndf_handle.Clear();
    hyp_FVFit_prob_handle.Clear();
    hyp_FVFit_v4cxx_handle.Clear();
    hyp_FVFit_v4cxy_handle.Clear();
    hyp_FVFit_v4cyy_handle.Clear();
    hyp_FVFit_v4czx_handle.Clear();
    hyp_FVFit_v4czy_handle.Clear();
    hyp_FVFit_v4czz_handle.Clear();
    jets_approximatefHPD_handle.Clear();
    jets_approximatefRBX_handle.Clear();
    jets_cor_handle.Clear();
    jets_corL1FastL2L3_handle.Clear();
    jets_corL1L2L3_handle.Clear();
    jets_emFrac_handle.Clear();
    jets_fHPD_handle.Clear();
    jets_fRBX_handle.Clear();
    jets_fSubDetector1_handle.Clear();
    jets_fSubDetector2_handle.Clear();
    jets_fSubDetector3_handle.Clear();
    jets_fSubDetector4_handle.Clear();
    jets_hitsInN90_handle.Clear();
    jets_n90Hits_handle.Clear();
    jets_nECALTowers_handle.Clear();
    jets_nHCALTowers_handle.Clear();
    jets_restrictedEMF_handle.Clear();
    mus_met_deltax_handle.Clear();
    mus_met_deltay_handle.Clear();
    mus_eledr_handle.Clear();
    mus_jetdr_handle.Clear();
    mus_isoR03_chpf_radial_handle.Clear();
    mus_isoR03_chpf_radialTight_handle.Clear();
    mus_isoR03_empf_radial_handle.Clear();
    mus_isoR03_empf_radialTight_handle.Clear();
    mus_isoR03_nhpf_radial_handle.Clear();
    mus_isoR03_nhpf_radialTight_handle.Clear();
    mus_isoR03_pf_radial_handle.Clear();
    mus_isoR03_pf_radialTight_handle.Clear();
    mus_backToBackCompat_handle.Clear();
    mus_caloCompatibility_handle.Clear();
    mus_chi2_handle.Clear();
    mus_chi2LocalMomentum_handle.Clear();
    mus_chi2LocalPosition_handle.Clear();
    mus_cosmicCompat_handle.Clear();
    mus_d0_handle.Clear();
    mus_d0Err_handle.Clear();
    mus_d0corr_handle.Clear();
    mus_e_em_handle.Clear();
    mus_e_emS9_handle.Clear();
    mus_e_had_handle.Clear();
    mus_e_hadS9_handle.Clear();
    mus_e_ho_handle.Clear();
    mus_e_hoS9_handle.Clear();
    mus_etaErr_handle.Clear();
    mus_gfit_chi2_handle.Clear();
    mus_gfit_d0_handle.Clear();
    mus_gfit_d0Err_handle.Clear();
    mus_gfit_d0corr_handle.Clear();
    mus_gfit_ndof_handle.Clear();
    mus_gfit_qoverp_handle.Clear();
    mus_gfit_qoverpError_handle.Clear();
    mus_gfit_z0_handle.Clear();
    mus_gfit_z0Err_handle.Clear();
    mus_gfit_z0corr_handle.Clear();
    mus_glbKink_handle.Clear();
    mus_glbTrackProbability_handle.Clear();
    mus_globalDeltaEtaPhi_handle.Clear();
    mus_ip3d_handle.Clear();
    mus_ip3derr_handle.Clear();
    mus_iso03_emEt_handle.Clear();
    mus_iso03_hadEt_handle.Clear();
    mus_iso03_hoEt_handle.Clear();
    mus_iso03_pf_handle.Clear();
    mus_iso03_sumPt_handle.Clear();
    mus_iso04_pf_handle.Clear();
    mus_iso05_emEt_handle.Clear();
    mus_iso05_hadEt_handle.Clear();
    mus_iso05_hoEt_handle.Clear();
    mus_iso05_sumPt_handle.Clear();
    mus_isoR03_pf_ChargedHadronPt_handle.Clear();
    mus_isoR03_pf_ChargedParticlePt_handle.Clear();
    mus_isoR03_pf_NeutralHadronEt_handle.Clear();
    mus_isoR03_pf_NeutralHadronEtHighThreshold_handle.Clear();
    mus_isoR03_pf_PUPt_handle.Clear();
    mus_isoR03_pf_PhotonEt_handle.Clear();
    mus_isoR03_pf_PhotonEtHighThreshold_handle.Clear();
    mus_isoR04_pf_ChargedHadronPt_handle.Clear();
    mus_isoR04_pf_ChargedParticlePt_handle.Clear();
    mus_isoR04_pf_NeutralHadronEt_handle.Clear();
    mus_isoR04_pf_NeutralHadronEtHighThreshold_handle.Clear();
    mus_isoR04_pf_PUPt_handle.Clear();
    mus_isoR04_pf_PhotonEt_handle.Clear();
    mus_isoR04_pf_PhotonEtHighThreshold_handle.Clear();
    mus_iso_ecalvetoDep_handle.Clear();
    mus_iso_hcalvetoDep_handle.Clear();
    mus_iso_hovetoDep_handle.Clear();
    mus_iso_trckvetoDep_handle.Clear();
    mus_localDistance_handle.Clear();
    mus_ndof_handle.Clear();
    mus_overlapCompat_handle.Clear();
    mus_pfdeltaP_handle.Clear();
    mus_pfecalE_handle.Clear();
    mus_pfhcalE_handle.Clear();
    mus_pfmva_emu_handle.Clear();
    mus_pfmva_epi_handle.Clear();
    mus_pfmva_nothing_gamma_handle.Clear();
    mus_pfmva_nothing_nh_handle.Clear();
    mus_pfmva_pimu_handle.Clear();
    mus_pfpS1E_handle.Clear();
    mus_pfpS2E_handle.Clear();
    mus_pfrawEcalE_handle.Clear();
    mus_pfrawHcalE_handle.Clear();
    mus_phiErr_handle.Clear();
    mus_ptErr_handle.Clear();
    mus_qoverp_handle.Clear();
    mus_qoverpError_handle.Clear();
    mus_segmCompatibility_handle.Clear();
    mus_staRelChi2_handle.Clear();
    mus_sta_chi2_handle.Clear();
    mus_sta_d0_handle.Clear();
    mus_sta_d0Err_handle.Clear();
    mus_sta_d0corr_handle.Clear();
    mus_sta_ndof_handle.Clear();
    mus_sta_qoverp_handle.Clear();
    mus_sta_qoverpError_handle.Clear();
    mus_sta_z0_handle.Clear();
    mus_sta_z0Err_handle.Clear();
    mus_sta_z0corr_handle.Clear();
    mus_timeAtIpInOut_handle.Clear();
    mus_timeAtIpInOutErr_handle.Clear();
    mus_timeAtIpOutIn_handle.Clear();
    mus_timeAtIpOutInErr_handle.Clear();
    mus_timeCompat_handle.Clear();
    mus_trkKink_handle.Clear();
    mus_trkRelChi2_handle.Clear();
    mus_vertexCompat_handle.Clear();
    mus_vertexphi_handle.Clear();
    mus_z0_handle.Clear();
    mus_z0Err_handle.Clear();
    mus_z0corr_handle.Clear();
    pfjets_mvavalue_handle.Clear();
    pfjets_full53xmva_beta_handle.Clear();
    pfjets_full53xmva_betaStar_handle.Clear();
    pfjets_full53xmva_d0_handle.Clear();
    pfjets_full53xmva_dRMean_handle.Clear();
    pfjets_full53xmva_dZ_handle.Clear();
    pfjets_full53xmva_frac01_handle.Clear();
    pfjets_full53xmva_frac02_handle.Clear();
    pfjets_full53xmva_frac03_handle.Clear();
    pfjets_full53xmva_frac04_handle.Clear();
    pfjets_full53xmva_frac05_handle.Clear();
    pfjets_full53xmva_nCharged_handle.Clear();
    pfjets_full53xmva_nNeutrals_handle.Clear();
    pfjets_full53xmva_nvtx_handle.Clear();
    pfjets_full53xmvavalue_handle.Clear();
    pfjets_full5xmvavalue_handle.Clear();
    trkjet_met_handle.Clear();
    trkjet_metPhi_handle.Clear();
    trkjet_sumet_handle.Clear();
    trk_met_handle.Clear();
    trk_metPhi_handle.Clear();
    trk_sumet_handle.Clear();
    pfcands_deltaP_handle.Clear();
    pfcands_ecalE_handle.Clear();
    pfcands_hcalE_handle.Clear();
    pfcands_mva_emu_handle.Clear();
    pfcands_mva_epi_handle.Clear();
    pfcands_mva_nothing_gamma_handle.Clear();
    pfcands_mva_nothing_nh_handle.Clear();
    pfcands_mva_pimu_handle.Clear();
    pfcands_pS1E_handle.Clear();
    pfcands_pS2E_handle.Clear();
    pfcands_rawEcalE_handle.Clear();
    pfcands_rawHcalE_handle.Clear();
    pfels_deltaP_handle.Clear();
    pfels_ecalE_handle.Clear();
    pfels_hcalE_handle.Clear();
    pfels_iso04ChargedHadrons_handle.Clear();
    pfels_iso04NeutralHadrons_handle.Clear();
    pfels_iso04Photons_handle.Clear();
    pfels_isoChargedHadrons_handle.Clear();
    pfels_isoNeutralHadrons_handle.Clear();
    pfels_isoPhotons_handle.Clear();
    pfels_mva_emu_handle.Clear();
    pfels_mva_epi_handle.Clear();
    pfels_mva_nothing_gamma_handle.Clear();
    pfels_mva_nothing_nh_handle.Clear();
    pfels_mva_pimu_handle.Clear();
    pfels_pS1E_handle.Clear();
    pfels_pS2E_handle.Clear();
    pfels_rawEcalE_handle.Clear();
    pfels_rawHcalE_handle.Clear();
    pfjets_area_handle.Clear();
    pfjets_chargedEmE_handle.Clear();
    pfjets_chargedHadronE_handle.Clear();
    pfjets_cor_handle.Clear();
    pfjets_corL1Fast_handle.Clear();
    pfjets_corL1FastL2L3_handle.Clear();
    pfjets_corL1FastL2L3residual_handle.Clear();
    pfjets_corL1L2L3_handle.Clear();
    pfjets_electronE_handle.Clear();
    pfjets_hfEmE_handle.Clear();
    pfjets_hfHadronE_handle.Clear();
    pfjets_muonE_handle.Clear();
    pfjets_neutralEmE_handle.Clear();
    pfjets_neutralHadronE_handle.Clear();
    pfjets_photonE_handle.Clear();
    pfmus_deltaP_handle.Clear();
    pfmus_ecalE_handle.Clear();
    pfmus_hcalE_handle.Clear();
    pfmus_iso04ChargedHadrons_handle.Clear();
    pfmus_iso04NeutralHadrons_handle.Clear();
    pfmus_iso04Photons_handle.Clear();
    pfmus_isoChargedHadrons_handle.Clear();
    pfmus_isoNeutralHadrons_handle.Clear();
    pfmus_isoPhotons_handle.Clear();
    pfmus_mva_emu_handle.Clear();
    pfmus_mva_epi_handle.Clear();
    pfmus_mva_nothing_gamma_handle.Clear();
    pfmus_mva_nothing_nh_handle.Clear();
    pfmus_mva_pimu_handle.Clear();
    pfmus_pS1E_handle.Clear();
    pfmus_pS2E_handle.Clear();
    pfmus_rawEcalE_handle.Clear();
    pfmus_rawHcalE_handle.Clear();
    taus_pf_againstElectronDeadECAL_handle.Clear();
    taus_pf_againstElectronLoose_handle.Clear();
    taus_pf_againstElectronLooseMVA2_handle.Clear();
    taus_pf_againstElectronLooseMVA3_handle.Clear();
    taus_pf_againstElectronMVA_handle.Clear();
    taus_pf_againstElectronMVA2category_handle.Clear();
    taus_pf_againstElectronMVA2raw_handle.Clear();
    taus_pf_againstElectronMVA3category_handle.Clear();
    taus_pf_againstElectronMVA3raw_handle.Clear();
    taus_pf_againstElectronMedium_handle.Clear();
    taus_pf_againstElectronMediumMVA2_handle.Clear();
    taus_pf_againstElectronMediumMVA3_handle.Clear();
    taus_pf_againstElectronTight_handle.Clear();
    taus_pf_againstElectronTightMVA2_handle.Clear();
    taus_pf_againstElectronTightMVA3_handle.Clear();
    taus_pf_againstElectronVLooseMVA2_handle.Clear();
    taus_pf_againstElectronVTightMVA3_handle.Clear();
    taus_pf_againstMuonLoose_handle.Clear();
    taus_pf_againstMuonLoose2_handle.Clear();
    taus_pf_againstMuonMedium_handle.Clear();
    taus_pf_againstMuonMedium2_handle.Clear();
    taus_pf_againstMuonTight_handle.Clear();
    taus_pf_againstMuonTight2_handle.Clear();
    taus_pf_byCombinedIsolationDeltaBetaCorrRaw_handle.Clear();
    taus_pf_byCombinedIsolationDeltaBetaCorrRaw3Hits_handle.Clear();
    taus_pf_byDecayModeFinding_handle.Clear();
    taus_pf_byIsolationMVA2raw_handle.Clear();
    taus_pf_byIsolationMVAraw_handle.Clear();
    taus_pf_byLooseCombinedIsolationDeltaBetaCorr_handle.Clear();
    taus_pf_byLooseCombinedIsolationDeltaBetaCorr3Hits_handle.Clear();
    taus_pf_byLooseIsolationMVA_handle.Clear();
    taus_pf_byLooseIsolationMVA2_handle.Clear();
    taus_pf_byMediumCombinedIsolationDeltaBetaCorr_handle.Clear();
    taus_pf_byMediumCombinedIsolationDeltaBetaCorr3Hits_handle.Clear();
    taus_pf_byMediumIsolationMVA_handle.Clear();
    taus_pf_byMediumIsolationMVA2_handle.Clear();
    taus_pf_byTightCombinedIsolationDeltaBetaCorr_handle.Clear();
    taus_pf_byTightCombinedIsolationDeltaBetaCorr3Hits_handle.Clear();
    taus_pf_byTightIsolationMVA_handle.Clear();
    taus_pf_byTightIsolationMVA2_handle.Clear();
    taus_pf_byVLooseCombinedIsolationDeltaBetaCorr_handle.Clear();
    photons_e1x5_handle.Clear();
    photons_e2x5Max_handle.Clear();
    photons_e3x3_handle.Clear();
    photons_e5x5_handle.Clear();
    photons_ecalIso03_handle.Clear();
    photons_ecalIso04_handle.Clear();
    photons_hOverE_handle.Clear();
    photons_hcalDepth1TowerSumEtBcConeDR03_handle.Clear();
    photons_hcalDepth1TowerSumEtBcConeDR04_handle.Clear();
    photons_hcalDepth2TowerSumEtBcConeDR03_handle.Clear();
    photons_hcalDepth2TowerSumEtBcConeDR04_handle.Clear();
    photons_hcalIso03_handle.Clear();
    photons_hcalIso04_handle.Clear();
    photons_hcalTowerSumEtBcConeDR03_handle.Clear();
    photons_hcalTowerSumEtBcConeDR04_handle.Clear();
    photons_ntkIsoHollow03_handle.Clear();
    photons_ntkIsoHollow04_handle.Clear();
    photons_ntkIsoSolid03_handle.Clear();
    photons_ntkIsoSolid04_handle.Clear();
    photons_sigmaEtaEta_handle.Clear();
    photons_sigmaIEtaIEta_handle.Clear();
    photons_swissSeed_handle.Clear();
    photons_tkIsoHollow03_handle.Clear();
    photons_tkIsoHollow04_handle.Clear();
    photons_tkIsoSolid03_handle.Clear();
    photons_tkIsoSolid04_handle.Clear();
    puInfo_trueNumInteractions_handle.Clear();
    convs_chi2_handle.Clear();
    convs_dl_handle.Clear();
    convs_ndof_handle.Clear();
    sparm_values_handle.Clear();
    scs_clustersSize_handle.Clear();
    scs_crystalsSize_handle.Clear();
    scs_e1x3_handle.Clear();
    scs_e1x5_handle.Clear();
    scs_e2nd_handle.Clear();
    scs_e2x2_handle.Clear();
    scs_e2x5Max_handle.Clear();
    scs_e3x1_handle.Clear();
    scs_e3x2_handle.Clear();
    scs_e3x3_handle.Clear();
    scs_e4x4_handle.Clear();
    scs_e5x5_handle.Clear();
    scs_eMax_handle.Clear();
    scs_eSeed_handle.Clear();
    scs_energy_handle.Clear();
    scs_eta_handle.Clear();
    scs_hoe_handle.Clear();
    scs_laserCorMax_handle.Clear();
    scs_laserCorMean_handle.Clear();
    scs_laserCorSeed_handle.Clear();
    scs_phi_handle.Clear();
    scs_preshowerEnergy_handle.Clear();
    scs_rawEnergy_handle.Clear();
    scs_sigmaEtaEta_handle.Clear();
    scs_sigmaEtaPhi_handle.Clear();
    scs_sigmaIEtaIEta_handle.Clear();
    scs_sigmaIEtaIEtaSC_handle.Clear();
    scs_sigmaIEtaIPhi_handle.Clear();
    scs_sigmaIEtaIPhiSC_handle.Clear();
    scs_sigmaIPhiIPhi_handle.Clear();
    scs_sigmaIPhiIPhiSC_handle.Clear();
    scs_sigmaPhiPhi_handle.Clear();
    scs_timeSeed_handle.Clear();
    svs_anglePV_handle.Clear();
    svs_chi2_handle.Clear();
    svs_dist3Dsig_handle.Clear();
    svs_dist3Dval_handle.Clear();
    svs_distXYsig_handle.Clear();
    svs_distXYval_handle.Clear();
    svs_ndof_handle.Clear();
    svs_prob_handle.Clear();
    svs_xError_handle.Clear();
    svs_yError_handle.Clear();
    svs_zError_handle.Clear();
    mus_tcmet_deltax_handle.Clear();
    mus_tcmet_deltay_handle.Clear();
    pfcands_dzpv_handle.Clear();
    pfcands_trkiso_handle.Clear();
    trks_chi2_handle.Clear();
    trks_d0_handle.Clear();
    trks_d0Err_handle.Clear();
    trks_d0corr_handle.Clear();
    trks_d0corrPhi_handle.Clear();
    trks_d0phiCov_handle.Clear();
    trks_etaErr_handle.Clear();
    trks_layer1_charge_handle.Clear();
    trks_ndof_handle.Clear();
    trks_phiErr_handle.Clear();
    trks_ptErr_handle.Clear();
    trks_validFraction_handle.Clear();
    trks_z0_handle.Clear();
    trks_z0Err_handle.Clear();
    trks_z0corr_handle.Clear();
    trkjets_cor_handle.Clear();
    trks_d0Errvtx_handle.Clear();
    trks_d0vtx_handle.Clear();
    vtxs_chi2_handle.Clear();
    vtxs_ndof_handle.Clear();
    vtxs_sumpt_handle.Clear();
    vtxs_xError_handle.Clear();
    vtxs_yError_handle.Clear();
    vtxs_zError_handle.Clear();
    bsvtxs_chi2_handle.Clear();
    bsvtxs_ndof_handle.Clear();
    bsvtxs_sumpt_handle.Clear();
    bsvtxs_xError_handle.Clear();
    bsvtxs_yError_handle.Clear();
    bsvtxs_zError_handle.Clear();
    els_convs_dcot_handle.Clear();
    els_convs_dist_handle.Clear();
    els_convs_radius_handle.Clear();
    mus_stationShowerDeltaR_handle.Clear();
    mus_stationShowerSizeT_handle.Clear();
    puInfo_instLumi_handle.Clear();
    puInfo_sump_highpt_handle.Clear();
    puInfo_sumpt_lowpt_handle.Clear();
    puInfo_zpositions_handle.Clear();
    vtxs_covMatrix_handle.Clear();
    bsvtxs_covMatrix_handle.Clear();
    evt_cscLooseHaloId_handle.Clear();
    evt_cscTightHaloId_handle.Clear();
    evt_ecalLooseHaloId_handle.Clear();
    evt_ecalTightHaloId_handle.Clear();
    evt_extremeTightHaloId_handle.Clear();
    evt_globalLooseHaloId_handle.Clear();
    evt_globalTightHaloId_handle.Clear();
    evt_hcalLooseHaloId_handle.Clear();
    evt_hcalTightHaloId_handle.Clear();
    evt_looseHaloId_handle.Clear();
    evt_nHaloLikeTracks_handle.Clear();
    evt_nHaloTriggerCandidates_handle.Clear();
    evt_tightHaloId_handle.Clear();
    evt_bsType_handle.Clear();
    evt_bunchCrossing_handle.Clear();
    evt_experimentType_handle.Clear();
    evt_isRealData_handle.Clear();
    evt_orbitNumber_handle.Clear();
    evt_storeNumber_handle.Clear();
    hcalnoise_GetRecHitCount_handle.Clear();
    hcalnoise_GetRecHitCount15_handle.Clear();
    hcalnoise_maxHPDHits_handle.Clear();
    hcalnoise_maxHPDNoOtherHits_handle.Clear();
    hcalnoise_maxRBXHits_handle.Clear();
    hcalnoise_maxZeros_handle.Clear();
    hcalnoise_noiseFilterStatus_handle.Clear();
    hcalnoise_noiseType_handle.Clear();
    hcalnoise_num10GeVHits_handle.Clear();
    hcalnoise_num25GeVHits_handle.Clear();
    hcalnoise_numFlatNoiseChannels_handle.Clear();
    hcalnoise_numIsolatedNoiseChannels_handle.Clear();
    hcalnoise_numProblematicRBXs_handle.Clear();
    hcalnoise_numSpikeNoiseChannels_handle.Clear();
    hcalnoise_numTS4TS5NoiseChannels_handle.Clear();
    hcalnoise_numTriangleNoiseChannels_handle.Clear();
    hcalnoise_passHighLevelNoiseFilter_handle.Clear();
    hcalnoise_passLooseNoiseFilter_handle.Clear();
    hcalnoise_passTightNoiseFilter_handle.Clear();
    l1_nemiso_handle.Clear();
    l1_nemnoiso_handle.Clear();
    l1_njetsc_handle.Clear();
    l1_njetsf_handle.Clear();
    l1_njetst_handle.Clear();
    l1_nmus_handle.Clear();
    ls_lumiSecQual_handle.Clear();
    pdfinfo_id1_handle.Clear();
    pdfinfo_id2_handle.Clear();
    sparm_subProcessId_handle.Clear();
    evt_ecaliPhiSuspects_handle.Clear();
    evt_globaliPhiSuspects_handle.Clear();
    evt_hcaliPhiSuspects_handle.Clear();
    els_mc3_id_handle.Clear();
    els_mc3idx_handle.Clear();
    els_mc3_motherid_handle.Clear();
    els_mc3_motheridx_handle.Clear();
    els_mc_id_handle.Clear();
    els_mcidx_handle.Clear();
    els_mc_motherid_handle.Clear();
    jets_mc3_id_handle.Clear();
    jets_mc3idx_handle.Clear();
    jets_mc_gpidx_handle.Clear();
    jets_mc_id_handle.Clear();
    jets_mcidx_handle.Clear();
    jets_mc_motherid_handle.Clear();
    mus_mc3_id_handle.Clear();
    mus_mc3idx_handle.Clear();
    mus_mc3_motherid_handle.Clear();
    mus_mc3_motheridx_handle.Clear();
    mus_mc_id_handle.Clear();
    mus_mcidx_handle.Clear();
    mus_mc_motherid_handle.Clear();
    pfjets_mc3_id_handle.Clear();
    pfjets_mc3idx_handle.Clear();
    pfjets_mc_gpidx_handle.Clear();
    pfjets_mc_id_handle.Clear();
    pfjets_mcidx_handle.Clear();
    pfjets_mc_motherid_handle.Clear();
    photons_mc3_id_handle.Clear();
    photons_mc3idx_handle.Clear();
    photons_mc3_motherid_handle.Clear();
    photons_mc3_motheridx_handle.Clear();
    photons_mc_id_handle.Clear();
    photons_mcidx_handle.Clear();
    photons_mc_motherid_handle.Clear();
    trk_mc3_id_handle.Clear();
    trk_mc3idx_handle.Clear();
    trk_mc3_motherid_handle.Clear();
    trk_mc3_motheridx_handle.Clear();
    trk_mc_id_handle.Clear();
    trk_mcidx_handle.Clear();
    trk_mc_motherid_handle.Clear();
    els_closestJet_handle.Clear();
    els_closestMuon_handle.Clear();
    els_pfelsidx_handle.Clear();
    els_category_handle.Clear();
    els_charge_handle.Clear();
    els_ckf_laywithmeas_handle.Clear();
    els_class_handle.Clear();
    els_conv_delMissHits_handle.Clear();
    els_conv_flag_handle.Clear();
    els_conv_gsftkidx_handle.Clear();
    els_conv_old_delMissHits_handle.Clear();
    els_conv_old_flag_handle.Clear();
    els_conv_old_gsftkidx_handle.Clear();
    els_conv_old_tkidx_handle.Clear();
    els_conv_tkidx_handle.Clear();
    els_exp_innerlayers_handle.Clear();
    els_exp_outerlayers_handle.Clear();
    els_fiduciality_handle.Clear();
    els_gsftrkidx_handle.Clear();
    els_layer1_det_handle.Clear();
    els_layer1_layer_handle.Clear();
    els_layer1_sizerphi_handle.Clear();
    els_layer1_sizerz_handle.Clear();
    els_lostHits_handle.Clear();
    els_lost_pixelhits_handle.Clear();
    els_nSeed_handle.Clear();
    els_sccharge_handle.Clear();
    els_scindex_handle.Clear();
    els_trk_charge_handle.Clear();
    els_trkidx_handle.Clear();
    els_type_handle.Clear();
    els_validHits_handle.Clear();
    els_valid_pixelhits_handle.Clear();
    genps_id_handle.Clear();
    genps_id_mother_handle.Clear();
    genps_status_handle.Clear();
    gsftrks_charge_handle.Clear();
    gsftrks_exp_innerlayers_handle.Clear();
    gsftrks_exp_outerlayers_handle.Clear();
    gsftrks_layer1_det_handle.Clear();
    gsftrks_layer1_layer_handle.Clear();
    gsftrks_layer1_sizerphi_handle.Clear();
    gsftrks_layer1_sizerz_handle.Clear();
    gsftrks_lostHits_handle.Clear();
    gsftrks_lost_pixelhits_handle.Clear();
    gsftrks_nlayers_handle.Clear();
    gsftrks_nlayers3D_handle.Clear();
    gsftrks_nlayersLost_handle.Clear();
    gsftrks_validHits_handle.Clear();
    gsftrks_valid_pixelhits_handle.Clear();
    hyp_ll_charge_handle.Clear();
    hyp_ll_id_handle.Clear();
    hyp_ll_index_handle.Clear();
    hyp_ll_lostHits_handle.Clear();
    hyp_ll_validHits_handle.Clear();
    hyp_lt_charge_handle.Clear();
    hyp_lt_id_handle.Clear();
    hyp_lt_index_handle.Clear();
    hyp_lt_lostHits_handle.Clear();
    hyp_lt_validHits_handle.Clear();
    hyp_njets_handle.Clear();
    hyp_nojets_handle.Clear();
    hyp_type_handle.Clear();
    hyp_FVFit_ndf_handle.Clear();
    hyp_FVFit_status_handle.Clear();
    hyp_ll_mc_id_handle.Clear();
    hyp_ll_mc_motherid_handle.Clear();
    hyp_lt_mc_id_handle.Clear();
    hyp_lt_mc_motherid_handle.Clear();
    pfjets_mcflavorAlgo_handle.Clear();
    pfjets_mcflavorPhys_handle.Clear();
    jets_closestElectron_handle.Clear();
    jets_closestMuon_handle.Clear();
    l1_emiso_ieta_handle.Clear();
    l1_emiso_iphi_handle.Clear();
    l1_emiso_rawId_handle.Clear();
    l1_emiso_type_handle.Clear();
    l1_emnoiso_ieta_handle.Clear();
    l1_emnoiso_iphi_handle.Clear();
    l1_emnoiso_rawId_handle.Clear();
    l1_emnoiso_type_handle.Clear();
    l1_jetsc_ieta_handle.Clear();
    l1_jetsc_iphi_handle.Clear();
    l1_jetsc_rawId_handle.Clear();
    l1_jetsc_type_handle.Clear();
    l1_jetsf_ieta_handle.Clear();
    l1_jetsf_iphi_handle.Clear();
    l1_jetsf_rawId_handle.Clear();
    l1_jetsf_type_handle.Clear();
    l1_jetst_ieta_handle.Clear();
    l1_jetst_iphi_handle.Clear();
    l1_jetst_rawId_handle.Clear();
    l1_jetst_type_handle.Clear();
    l1_mus_flags_handle.Clear();
    l1_mus_q_handle.Clear();
    l1_mus_qual_handle.Clear();
    l1_mus_qualFlags_handle.Clear();
    mus_met_flag_handle.Clear();
    mus_closestEle_handle.Clear();
    mus_closestJet_handle.Clear();
    mus_pfmusidx_handle.Clear();
    mus_charge_handle.Clear();
    mus_gfit_validHits_handle.Clear();
    mus_gfit_validSTAHits_handle.Clear();
    mus_gfit_validSiHits_handle.Clear();
    mus_goodmask_handle.Clear();
    mus_iso03_ntrk_handle.Clear();
    mus_iso05_ntrk_handle.Clear();
    mus_lostHits_handle.Clear();
    mus_muonBestTrackType_handle.Clear();
    mus_nOverlaps_handle.Clear();
    mus_nmatches_handle.Clear();
    mus_numberOfMatchedStations_handle.Clear();
    mus_overlap0_handle.Clear();
    mus_overlap1_handle.Clear();
    mus_pfcharge_handle.Clear();
    mus_pfflag_handle.Clear();
    mus_pfparticleId_handle.Clear();
    mus_pid_PFMuon_handle.Clear();
    mus_pid_TM2DCompatibilityLoose_handle.Clear();
    mus_pid_TM2DCompatibilityTight_handle.Clear();
    mus_pid_TMLastStationLoose_handle.Clear();
    mus_pid_TMLastStationTight_handle.Clear();
    mus_sta_validHits_handle.Clear();
    mus_timeDirection_handle.Clear();
    mus_timeNumStationsUsed_handle.Clear();
    mus_trk_charge_handle.Clear();
    mus_trkidx_handle.Clear();
    mus_type_handle.Clear();
    mus_validHits_handle.Clear();
    pfcands_charge_handle.Clear();
    pfcands_flag_handle.Clear();
    pfcands_particleId_handle.Clear();
    pfcands_pfelsidx_handle.Clear();
    pfcands_pfmusidx_handle.Clear();
    pfcands_trkidx_handle.Clear();
    pfcands_vtxidx_handle.Clear();
    pfels_elsidx_handle.Clear();
    pfels_charge_handle.Clear();
    pfels_flag_handle.Clear();
    pfels_particleId_handle.Clear();
    pfjets_chargedHadronMultiplicity_handle.Clear();
    pfjets_chargedMultiplicity_handle.Clear();
    pfjets_electronMultiplicity_handle.Clear();
    pfjets_hfEmMultiplicity_handle.Clear();
    pfjets_hfHadronMultiplicity_handle.Clear();
    pfjets_muonMultiplicity_handle.Clear();
    pfjets_neutralHadronMultiplicity_handle.Clear();
    pfjets_neutralMultiplicity_handle.Clear();
    pfjets_photonMultiplicity_handle.Clear();
    pfmus_musidx_handle.Clear();
    pfmus_charge_handle.Clear();
    pfmus_flag_handle.Clear();
    pfmus_particleId_handle.Clear();
    taus_pf_charge_handle.Clear();
    taus_pf_pfjetIndex_handle.Clear();
    photons_fiduciality_handle.Clear();
    photons_scindex_handle.Clear();
    puInfo_bunchCrossing_handle.Clear();
    puInfo_nPUvertices_handle.Clear();
    convs_algo_handle.Clear();
    convs_isConverted_handle.Clear();
    convs_quality_handle.Clear();
    scs_detIdSeed_handle.Clear();
    scs_elsidx_handle.Clear();
    scs_severitySeed_handle.Clear();
    svs_isKs_handle.Clear();
    svs_isLambda_handle.Clear();
    svs_mc3_id_handle.Clear();
    svs_nTrks_handle.Clear();
    mus_tcmet_flag_handle.Clear();
    trks_algo_handle.Clear();
    trks_charge_handle.Clear();
    trks_exp_innerlayers_handle.Clear();
    trks_exp_outerlayers_handle.Clear();
    trks_layer1_det_handle.Clear();
    trks_layer1_layer_handle.Clear();
    trks_layer1_sizerphi_handle.Clear();
    trks_layer1_sizerz_handle.Clear();
    trks_lostHits_handle.Clear();
    trks_lost_pixelhits_handle.Clear();
    trks_nLoops_handle.Clear();
    trks_nlayers_handle.Clear();
    trks_nlayers3D_handle.Clear();
    trks_nlayersLost_handle.Clear();
    trks_pvidx0_handle.Clear();
    trks_pvidx1_handle.Clear();
    trks_qualityMask_handle.Clear();
    trks_validHits_handle.Clear();
    trks_valid_pixelhits_handle.Clear();
    trks_elsidx_handle.Clear();
    trk_musidx_handle.Clear();
    trkjets_ntrks_handle.Clear();
    trkjets_vtxs_idx_handle.Clear();
    vtxs_isFake_handle.Clear();
    vtxs_isValid_handle.Clear();
    vtxs_tracksSize_handle.Clear();
    bsvtxs_isFake_handle.Clear();
    bsvtxs_isValid_handle.Clear();
    bsvtxs_tracksSize_handle.Clear();
    els_convs_delMissHits_handle.Clear();
    els_convs_flag_handle.Clear();
    els_convs_gsftkidx_handle.Clear();
    els_convs_tkidx_handle.Clear();
    genps_lepdaughter_id_handle.Clear();
    genps_lepdaughter_idx_handle.Clear();
    hlt_trigObjs_id_handle.Clear();
    hyp_jets_idx_handle.Clear();
    hyp_other_jets_idx_handle.Clear();
    mus_nStationCorrelatedHits_handle.Clear();
    mus_nStationHits_handle.Clear();
    pfjets_pfcandIndicies_handle.Clear();
    taus_pf_pfcandIndicies_handle.Clear();
    puInfo_ntrks_highpt_handle.Clear();
    puInfo_ntrks_lowpt_handle.Clear();
    convs_nHitsBeforeVtx_handle.Clear();
    convs_tkalgo_handle.Clear();
    convs_tkidx_handle.Clear();
    els_HLT_Ele17_Ele8_L1sL1DoubleEG137_version_handle.Clear();
    els_HLT_Ele17_Ele8_LeadingLeg_version_handle.Clear();
    els_HLT_Ele17_Ele8_Mass50_LeadingLeg_version_handle.Clear();
    els_HLT_Ele17_Ele8_Mass50_TrailingLeg_version_handle.Clear();
    els_HLT_Ele17_Ele8_TrailingLeg_version_handle.Clear();
    els_HLT_Ele17_Ele8_version_handle.Clear();
    els_HLT_Ele20_SC4_Mass50_LeadingLeg_version_handle.Clear();
    els_HLT_Ele20_SC4_Mass50_TrailingLeg_version_handle.Clear();
    els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_version_handle.Clear();
    els_HLT_Ele27_WP80_version_handle.Clear();
    els_HLT_Ele32_SC17_Mass50_LeadingLeg_version_handle.Clear();
    els_HLT_Ele32_SC17_Mass50_TrailingLeg_version_handle.Clear();
    els_HLT_Mu17_Ele8_TrailingLeg_version_handle.Clear();
    els_HLT_Mu17_Ele8_version_handle.Clear();
    els_HLT_Mu8_Ele17_version_handle.Clear();
    evt_nels_handle.Clear();
    evt_detectorStatus_handle.Clear();
    evt_event_handle.Clear();
    evt_lumiBlock_handle.Clear();
    evt_run_handle.Clear();
    genps_flavorHistoryFilterResult_handle.Clear();
    evt_ngenjets_handle.Clear();
    genps_signalProcessID_handle.Clear();
    evt_njets_handle.Clear();
    l1_bits1_handle.Clear();
    l1_bits2_handle.Clear();
    l1_bits3_handle.Clear();
    l1_bits4_handle.Clear();
    l1_techbits1_handle.Clear();
    l1_techbits2_handle.Clear();
    ls_lsNumber_handle.Clear();
    ls_numOrbit_handle.Clear();
    ls_startOrbit_handle.Clear();
    mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_version_handle.Clear();
    mus_HLT_IsoMu24_eta2p1_version_handle.Clear();
    mus_HLT_Mu17_Ele8_LeadingLeg_version_handle.Clear();
    mus_HLT_Mu17_Ele8_version_handle.Clear();
    mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_version_handle.Clear();
    mus_HLT_Mu17_Mu8_LeadingLeg_version_handle.Clear();
    mus_HLT_Mu17_Mu8_TrailingLeg_version_handle.Clear();
    mus_HLT_Mu17_Mu8_version_handle.Clear();
    mus_HLT_Mu17_TkMu8_LeadingLeg_version_handle.Clear();
    mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_version_handle.Clear();
    mus_HLT_Mu17_TkMu8_TrailingLeg_version_handle.Clear();
    mus_HLT_Mu17_TkMu8_version_handle.Clear();
    mus_HLT_Mu8_Ele17_TrailingLeg_version_handle.Clear();
    mus_HLT_Mu8_Ele17_version_handle.Clear();
    evt_nphotons_handle.Clear();
    evt_ecalRecoStatus_handle.Clear();
    evt_nscs_handle.Clear();
    evt_ntrkjets_handle.Clear();
    evt_nvtxs_handle.Clear();
    evt_nbsvtxs_handle.Clear();
    els_HLT_Ele17_Ele8_handle.Clear();
    els_HLT_Ele17_Ele8_L1sL1DoubleEG137_handle.Clear();
    els_HLT_Ele17_Ele8_LeadingLeg_handle.Clear();
    els_HLT_Ele17_Ele8_Mass50_LeadingLeg_handle.Clear();
    els_HLT_Ele17_Ele8_Mass50_TrailingLeg_handle.Clear();
    els_HLT_Ele17_Ele8_TrailingLeg_handle.Clear();
    els_HLT_Ele20_SC4_Mass50_LeadingLeg_handle.Clear();
    els_HLT_Ele20_SC4_Mass50_TrailingLeg_handle.Clear();
    els_HLT_Ele27_WP80_handle.Clear();
    els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_handle.Clear();
    els_HLT_Ele32_SC17_Mass50_LeadingLeg_handle.Clear();
    els_HLT_Ele32_SC17_Mass50_TrailingLeg_handle.Clear();
    els_HLT_Mu17_Ele8_handle.Clear();
    els_HLT_Mu17_Ele8_TrailingLeg_handle.Clear();
    els_HLT_Mu8_Ele17_handle.Clear();
    els_id2012ext_loose_handle.Clear();
    els_id2012ext_medium_handle.Clear();
    els_id2012ext_tight_handle.Clear();
    els_id2012ext_veto_handle.Clear();
    els_id2012_loose_handle.Clear();
    els_id2012_medium_handle.Clear();
    els_id2012_tight_handle.Clear();
    els_id2012_veto_handle.Clear();
    hlt_prescales_handle.Clear();
    l1_prescales_handle.Clear();
    l1_techtrigprescales_handle.Clear();
    mus_HLT_IsoMu24_eta2p1_handle.Clear();
    mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_handle.Clear();
    mus_HLT_Mu17_Ele8_handle.Clear();
    mus_HLT_Mu17_Ele8_LeadingLeg_handle.Clear();
    mus_HLT_Mu17_Mu8_handle.Clear();
    mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_handle.Clear();
    mus_HLT_Mu17_Mu8_LeadingLeg_handle.Clear();
    mus_HLT_Mu17_Mu8_TrailingLeg_handle.Clear();
    mus_HLT_Mu17_TkMu8_handle.Clear();
    mus_HLT_Mu17_TkMu8_LeadingLeg_handle.Clear();
    mus_HLT_Mu17_TkMu8_TrailingLeg_handle.Clear();
    mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_handle.Clear();
    mus_HLT_Mu8_Ele17_handle.Clear();
    mus_HLT_Mu8_Ele17_TrailingLeg_handle.Clear();
    evt_timestamp_handle.Clear();

}

void CMS2::SetEvent(const edm::Event& event)
{
    hlt_bits_handle.SetEvent(event);
    evt_CMS2tag_handle.SetEvent(event);
    evt_dataset_handle.SetEvent(event);
    hlt_trigNames_handle.SetEvent(event);
    l1_techtrigNames_handle.SetEvent(event);
    l1_trigNames_handle.SetEvent(event);
    evt_errCategory_handle.SetEvent(event);
    evt_errModule_handle.SetEvent(event);
    evt_errSeverity_handle.SetEvent(event);
    sparm_comment_handle.SetEvent(event);
    sparm_names_handle.SetEvent(event);
    evt_eventHasHalo_handle.SetEvent(event);
    hcalnoise_HasBadRBXTS4TS5_handle.SetEvent(event);
    ls_isValid_handle.SetEvent(event);
    filt_ecalBE_handle.SetEvent(event);
    filt_ecalDR_handle.SetEvent(event);
    filt_ecalLaser_handle.SetEvent(event);
    filt_ecalTP_handle.SetEvent(event);
    filt_eeBadSc_handle.SetEvent(event);
    filt_greedyMuon_handle.SetEvent(event);
    filt_hcalLaser_handle.SetEvent(event);
    filt_inconsistentMuon_handle.SetEvent(event);
    filt_jetIDFailure_handle.SetEvent(event);
    filt_multiEvent_handle.SetEvent(event);
    filt_trackingFailure_handle.SetEvent(event);
    evt_hbheFilter_handle.SetEvent(event);
    els_conv_vtx_flag_handle.SetEvent(event);
    els_passingMvaPreselection_handle.SetEvent(event);
    els_passingPflowPreselection_handle.SetEvent(event);
    mus_isRPCMuon_handle.SetEvent(event);
    mus_tightMatch_handle.SetEvent(event);
    mus_updatedSta_handle.SetEvent(event);
    pfcands_isMuIso_handle.SetEvent(event);
    photons_haspixelSeed_handle.SetEvent(event);
    jets_closestElectron_DR_handle.SetEvent(event);
    jets_closestMuon_DR_handle.SetEvent(event);
    evt_bs_Xwidth_handle.SetEvent(event);
    evt_bs_XwidthErr_handle.SetEvent(event);
    evt_bs_Ywidth_handle.SetEvent(event);
    evt_bs_YwidthErr_handle.SetEvent(event);
    evt_bs_dxdz_handle.SetEvent(event);
    evt_bs_dxdzErr_handle.SetEvent(event);
    evt_bs_dydz_handle.SetEvent(event);
    evt_bs_dydzErr_handle.SetEvent(event);
    evt_bs_sigmaZ_handle.SetEvent(event);
    evt_bs_sigmaZErr_handle.SetEvent(event);
    evt_bs_xErr_handle.SetEvent(event);
    evt_bs_yErr_handle.SetEvent(event);
    evt_bs_zErr_handle.SetEvent(event);
    evt_bField_handle.SetEvent(event);
    evt_rho_handle.SetEvent(event);
    evt_rhoJEC_handle.SetEvent(event);
    evt_fixgrid_all_rho_handle.SetEvent(event);
    evt_fixgridfastjet_all_rho_handle.SetEvent(event);
    gen_met_handle.SetEvent(event);
    gen_metPhi_handle.SetEvent(event);
    genps_alphaQCD_handle.SetEvent(event);
    genps_pthat_handle.SetEvent(event);
    genps_qScale_handle.SetEvent(event);
    genps_weight_handle.SetEvent(event);
    gen_sumEt_handle.SetEvent(event);
    hcalnoise_GetRecHitEnergy_handle.SetEvent(event);
    hcalnoise_GetRecHitEnergy15_handle.SetEvent(event);
    hcalnoise_GetTotalCalibCharge_handle.SetEvent(event);
    hcalnoise_TS4TS5NoiseSumE_handle.SetEvent(event);
    hcalnoise_TS4TS5NoiseSumEt_handle.SetEvent(event);
    hcalnoise_eventChargeFraction_handle.SetEvent(event);
    hcalnoise_eventEMEnergy_handle.SetEvent(event);
    hcalnoise_eventEMFraction_handle.SetEvent(event);
    hcalnoise_eventHadEnergy_handle.SetEvent(event);
    hcalnoise_eventTrackEnergy_handle.SetEvent(event);
    hcalnoise_flatNoiseSumE_handle.SetEvent(event);
    hcalnoise_flatNoiseSumEt_handle.SetEvent(event);
    hcalnoise_isolatedNoiseSumE_handle.SetEvent(event);
    hcalnoise_isolatedNoiseSumEt_handle.SetEvent(event);
    hcalnoise_max10GeVHitTime_handle.SetEvent(event);
    hcalnoise_max25GeVHitTime_handle.SetEvent(event);
    hcalnoise_maxE10TS_handle.SetEvent(event);
    hcalnoise_maxE2Over10TS_handle.SetEvent(event);
    hcalnoise_maxE2TS_handle.SetEvent(event);
    hcalnoise_min10GeVHitTime_handle.SetEvent(event);
    hcalnoise_min25GeVHitTime_handle.SetEvent(event);
    hcalnoise_minE10TS_handle.SetEvent(event);
    hcalnoise_minE2Over10TS_handle.SetEvent(event);
    hcalnoise_minE2TS_handle.SetEvent(event);
    hcalnoise_minHPDEMF_handle.SetEvent(event);
    hcalnoise_minRBXEMF_handle.SetEvent(event);
    hcalnoise_rms10GeVHitTime_handle.SetEvent(event);
    hcalnoise_rms25GeVHitTime_handle.SetEvent(event);
    hcalnoise_spikeNoiseSumE_handle.SetEvent(event);
    hcalnoise_spikeNoiseSumEt_handle.SetEvent(event);
    hcalnoise_triangleNoiseSumE_handle.SetEvent(event);
    hcalnoise_triangleNoiseSumEt_handle.SetEvent(event);
    evt_kt6calo_central_rho_handle.SetEvent(event);
    evt_kt6calo_muhlt_rho_handle.SetEvent(event);
    evt_kt6calo_rho_handle.SetEvent(event);
    evt_kt6pf_ctrChargedPU_rho_handle.SetEvent(event);
    evt_kt6pf_ctrNeutral_rho_handle.SetEvent(event);
    evt_kt6pf_ctrNeutralTight_rho_handle.SetEvent(event);
    evt_kt6pf_foregiso_rho_handle.SetEvent(event);
    l1_met_etTot_handle.SetEvent(event);
    l1_met_met_handle.SetEvent(event);
    l1_mht_htTot_handle.SetEvent(event);
    l1_mht_mht_handle.SetEvent(event);
    ls_avgInsDelLumi_handle.SetEvent(event);
    ls_avgInsDelLumiErr_handle.SetEvent(event);
    ls_avgInsRecLumi_handle.SetEvent(event);
    ls_avgInsRecLumiErr_handle.SetEvent(event);
    ls_deadFrac_handle.SetEvent(event);
    ls_intgDelLumi_handle.SetEvent(event);
    ls_intgRecLumi_handle.SetEvent(event);
    ls_lumiSectionLength_handle.SetEvent(event);
    evt_ecalendcapm_met_handle.SetEvent(event);
    evt_ecalendcapm_metPhi_handle.SetEvent(event);
    evt_ecalendcapp_met_handle.SetEvent(event);
    evt_ecalendcapp_metPhi_handle.SetEvent(event);
    evt_ecalmet_handle.SetEvent(event);
    evt_ecalmetPhi_handle.SetEvent(event);
    evt_endcapm_met_handle.SetEvent(event);
    evt_endcapm_metPhi_handle.SetEvent(event);
    evt_endcapp_met_handle.SetEvent(event);
    evt_endcapp_metPhi_handle.SetEvent(event);
    evt_hcalendcapm_met_handle.SetEvent(event);
    evt_hcalendcapm_metPhi_handle.SetEvent(event);
    evt_hcalendcapp_met_handle.SetEvent(event);
    evt_hcalendcapp_metPhi_handle.SetEvent(event);
    evt_hcalmet_handle.SetEvent(event);
    evt_hcalmetPhi_handle.SetEvent(event);
    evt_met_handle.SetEvent(event);
    evt_met_EtGt3_handle.SetEvent(event);
    evt_metHO_handle.SetEvent(event);
    evt_metHOPhi_handle.SetEvent(event);
    evt_metHOSig_handle.SetEvent(event);
    evt_metMuonCorr_handle.SetEvent(event);
    evt_metMuonCorrPhi_handle.SetEvent(event);
    evt_metMuonCorrSig_handle.SetEvent(event);
    evt_metMuonJESCorr_handle.SetEvent(event);
    evt_metMuonJESCorrPhi_handle.SetEvent(event);
    evt_metMuonJESCorrSig_handle.SetEvent(event);
    evt_metNoHF_handle.SetEvent(event);
    evt_metNoHFHO_handle.SetEvent(event);
    evt_metNoHFHOPhi_handle.SetEvent(event);
    evt_metNoHFHOSig_handle.SetEvent(event);
    evt_metNoHFPhi_handle.SetEvent(event);
    evt_metNoHFSig_handle.SetEvent(event);
    evt_metOpt_handle.SetEvent(event);
    evt_metOptHO_handle.SetEvent(event);
    evt_metOptHOPhi_handle.SetEvent(event);
    evt_metOptHOSig_handle.SetEvent(event);
    evt_metOptNoHF_handle.SetEvent(event);
    evt_metOptNoHFHO_handle.SetEvent(event);
    evt_metOptNoHFHOPhi_handle.SetEvent(event);
    evt_metOptNoHFHOSig_handle.SetEvent(event);
    evt_metOptNoHFPhi_handle.SetEvent(event);
    evt_metOptNoHFSig_handle.SetEvent(event);
    evt_metOptPhi_handle.SetEvent(event);
    evt_metOptSig_handle.SetEvent(event);
    evt_metPhi_handle.SetEvent(event);
    evt_metPhi_EtGt3_handle.SetEvent(event);
    evt_metSig_handle.SetEvent(event);
    evt_sumet_handle.SetEvent(event);
    evt_sumet_EtGt3_handle.SetEvent(event);
    evt_sumetHO_handle.SetEvent(event);
    evt_sumetMuonCorr_handle.SetEvent(event);
    evt_sumetMuonJESCorr_handle.SetEvent(event);
    evt_sumetNoHF_handle.SetEvent(event);
    evt_sumetNoHFHO_handle.SetEvent(event);
    evt_sumetOpt_handle.SetEvent(event);
    evt_sumetOptHO_handle.SetEvent(event);
    evt_sumetOptNoHF_handle.SetEvent(event);
    evt_sumetOptNoHFHO_handle.SetEvent(event);
    pdfinfo_pdf1_handle.SetEvent(event);
    pdfinfo_pdf2_handle.SetEvent(event);
    pdfinfo_scale_handle.SetEvent(event);
    pdfinfo_x1_handle.SetEvent(event);
    pdfinfo_x2_handle.SetEvent(event);
    evt_fixgrid_rho_all_handle.SetEvent(event);
    evt_fixgrid_rho_ctr_handle.SetEvent(event);
    evt_fixgrid_rho_fwd_handle.SetEvent(event);
    evt_pfmet_handle.SetEvent(event);
    evt_pfmetPhi_handle.SetEvent(event);
    evt_pfmetPhi_type1cor_handle.SetEvent(event);
    evt_pfmetSig_handle.SetEvent(event);
    evt_pfmetSignificance_handle.SetEvent(event);
    evt_pfmet_type1cor_handle.SetEvent(event);
    evt_pfsumet_handle.SetEvent(event);
    sparm_filterEfficiency_handle.SetEvent(event);
    sparm_pdfScale_handle.SetEvent(event);
    sparm_pdfWeight1_handle.SetEvent(event);
    sparm_pdfWeight2_handle.SetEvent(event);
    sparm_weight_handle.SetEvent(event);
    sparm_xsec_handle.SetEvent(event);
    evt_pf_tcmet_handle.SetEvent(event);
    evt_pf_tcmetPhi_handle.SetEvent(event);
    evt_pf_tcmetSig_handle.SetEvent(event);
    evt_pf_tcsumet_handle.SetEvent(event);
    evt_tcmet_handle.SetEvent(event);
    evt_tcmetPhi_handle.SetEvent(event);
    evt_tcmetSig_handle.SetEvent(event);
    evt_tcsumet_handle.SetEvent(event);
    evt_ww_rho_act_handle.SetEvent(event);
    evt_ww_rho_handle.SetEvent(event);
    evt_ww_rho_rnd_handle.SetEvent(event);
    evt_ww_rho_vor_handle.SetEvent(event);
    evt_bsp4_handle.SetEvent(event);
    l1_met_p4_handle.SetEvent(event);
    l1_mht_p4_handle.SetEvent(event);
    els_mc_motherp4_handle.SetEvent(event);
    els_mc_p4_handle.SetEvent(event);
    jets_mc_gp_p4_handle.SetEvent(event);
    jets_mc_motherp4_handle.SetEvent(event);
    jets_mc_p4_handle.SetEvent(event);
    mus_mc_motherp4_handle.SetEvent(event);
    mus_mc_p4_handle.SetEvent(event);
    pfjets_mc_gp_p4_handle.SetEvent(event);
    pfjets_mc_motherp4_handle.SetEvent(event);
    pfjets_mc_p4_handle.SetEvent(event);
    photons_mc_motherp4_handle.SetEvent(event);
    photons_mc_p4_handle.SetEvent(event);
    trk_mcp4_handle.SetEvent(event);
    els_conv_pos_p4_handle.SetEvent(event);
    els_inner_position_handle.SetEvent(event);
    els_outer_position_handle.SetEvent(event);
    els_p4_handle.SetEvent(event);
    els_p4In_handle.SetEvent(event);
    els_p4Out_handle.SetEvent(event);
    els_trk_p4_handle.SetEvent(event);
    els_vertex_p4_handle.SetEvent(event);
    genjets_p4_handle.SetEvent(event);
    genps_p4_handle.SetEvent(event);
    genps_prod_vtx_handle.SetEvent(event);
    gsftrks_inner_position_handle.SetEvent(event);
    gsftrks_outer_p4_handle.SetEvent(event);
    gsftrks_outer_position_handle.SetEvent(event);
    gsftrks_p4_handle.SetEvent(event);
    gsftrks_vertex_p4_handle.SetEvent(event);
    hyp_ll_p4_handle.SetEvent(event);
    hyp_ll_trk_p4_handle.SetEvent(event);
    hyp_lt_p4_handle.SetEvent(event);
    hyp_lt_trk_p4_handle.SetEvent(event);
    hyp_p4_handle.SetEvent(event);
    hyp_FVFit_p4_handle.SetEvent(event);
    hyp_FVFit_v4_handle.SetEvent(event);
    hyp_ll_mc_p4_handle.SetEvent(event);
    hyp_lt_mc_p4_handle.SetEvent(event);
    jets_p4_handle.SetEvent(event);
    jets_vertex_p4_handle.SetEvent(event);
    l1_emiso_p4_handle.SetEvent(event);
    l1_emnoiso_p4_handle.SetEvent(event);
    l1_jetsc_p4_handle.SetEvent(event);
    l1_jetsf_p4_handle.SetEvent(event);
    l1_jetst_p4_handle.SetEvent(event);
    l1_mus_p4_handle.SetEvent(event);
    mus_ecalpos_p4_handle.SetEvent(event);
    mus_fitpicky_p4_handle.SetEvent(event);
    mus_fittev_p4_handle.SetEvent(event);
    mus_fittpfms_p4_handle.SetEvent(event);
    mus_gfit_outerPos_p4_handle.SetEvent(event);
    mus_gfit_p4_handle.SetEvent(event);
    mus_gfit_vertex_p4_handle.SetEvent(event);
    mus_p4_handle.SetEvent(event);
    mus_pfp4_handle.SetEvent(event);
    mus_pfposAtEcal_p4_handle.SetEvent(event);
    mus_sta_p4_handle.SetEvent(event);
    mus_sta_vertex_p4_handle.SetEvent(event);
    mus_trk_p4_handle.SetEvent(event);
    mus_vertex_p4_handle.SetEvent(event);
    pfcands_p4_handle.SetEvent(event);
    pfcands_posAtEcal_p4_handle.SetEvent(event);
    pfels_p4_handle.SetEvent(event);
    pfels_posAtEcal_p4_handle.SetEvent(event);
    pfjets_p4_handle.SetEvent(event);
    pfmus_p4_handle.SetEvent(event);
    pfmus_posAtEcal_p4_handle.SetEvent(event);
    taus_pf_p4_handle.SetEvent(event);
    photons_p4_handle.SetEvent(event);
    convs_refitPairMom_p4_handle.SetEvent(event);
    convs_vtxpos_handle.SetEvent(event);
    scs_p4_handle.SetEvent(event);
    scs_pos_p4_handle.SetEvent(event);
    scs_vtx_p4_handle.SetEvent(event);
    svs_flight_handle.SetEvent(event);
    svs_mc3_p4_handle.SetEvent(event);
    svs_p4_handle.SetEvent(event);
    svs_position_handle.SetEvent(event);
    svs_refitp4_handle.SetEvent(event);
    trks_inner_position_handle.SetEvent(event);
    trks_outer_p4_handle.SetEvent(event);
    trks_outer_position_handle.SetEvent(event);
    trks_trk_p4_handle.SetEvent(event);
    trks_vertex_p4_handle.SetEvent(event);
    trkjets_p4_handle.SetEvent(event);
    vtxs_position_handle.SetEvent(event);
    bsvtxs_position_handle.SetEvent(event);
    els_convs_pos_p4_handle.SetEvent(event);
    genps_lepdaughter_p4_handle.SetEvent(event);
    hlt_trigObjs_p4_handle.SetEvent(event);
    hyp_jets_p4_handle.SetEvent(event);
    hyp_other_jets_p4_handle.SetEvent(event);
    jpts_combinedSecondaryVertexBJetTag_handle.SetEvent(event);
    jpts_combinedSecondaryVertexMVABJetTag_handle.SetEvent(event);
    jpts_jetBProbabilityBJetTag_handle.SetEvent(event);
    jpts_jetProbabilityBJetTag_handle.SetEvent(event);
    jpts_simpleSecondaryVertexBJetTag_handle.SetEvent(event);
    jpts_simpleSecondaryVertexHighEffBJetTag_handle.SetEvent(event);
    jpts_simpleSecondaryVertexHighPurBJetTags_handle.SetEvent(event);
    jpts_softElectronByIP3dBJetTag_handle.SetEvent(event);
    jpts_softElectronByPtBJetTag_handle.SetEvent(event);
    jpts_softElectronTag_handle.SetEvent(event);
    jpts_softMuonBJetTag_handle.SetEvent(event);
    jpts_softMuonByIP3dBJetTag_handle.SetEvent(event);
    jpts_softMuonByPtBJetTag_handle.SetEvent(event);
    jpts_trackCountingHighEffBJetTag_handle.SetEvent(event);
    jpts_trackCountingHighPurBJetTag_handle.SetEvent(event);
    jets_combinedSecondaryVertexBJetTag_handle.SetEvent(event);
    jets_combinedSecondaryVertexMVABJetTag_handle.SetEvent(event);
    jets_jetBProbabilityBJetTag_handle.SetEvent(event);
    jets_jetProbabilityBJetTag_handle.SetEvent(event);
    jets_simpleSecondaryVertexBJetTag_handle.SetEvent(event);
    jets_simpleSecondaryVertexHighEffBJetTag_handle.SetEvent(event);
    jets_simpleSecondaryVertexHighPurBJetTags_handle.SetEvent(event);
    jets_softElectronByIP3dBJetTag_handle.SetEvent(event);
    jets_softElectronByPtBJetTag_handle.SetEvent(event);
    jets_softElectronTag_handle.SetEvent(event);
    jets_softMuonBJetTag_handle.SetEvent(event);
    jets_softMuonByIP3dBJetTag_handle.SetEvent(event);
    jets_softMuonByPtBJetTag_handle.SetEvent(event);
    jets_trackCountingHighEffBJetTag_handle.SetEvent(event);
    jets_trackCountingHighPurBJetTag_handle.SetEvent(event);
    pfjets_combinedSecondaryVertexBJetTag_handle.SetEvent(event);
    pfjets_combinedSecondaryVertexMVABJetTag_handle.SetEvent(event);
    pfjets_jetBProbabilityBJetTag_handle.SetEvent(event);
    pfjets_jetProbabilityBJetTag_handle.SetEvent(event);
    pfjets_simpleSecondaryVertexBJetTag_handle.SetEvent(event);
    pfjets_simpleSecondaryVertexHighEffBJetTag_handle.SetEvent(event);
    pfjets_simpleSecondaryVertexHighPurBJetTags_handle.SetEvent(event);
    pfjets_softElectronByIP3dBJetTag_handle.SetEvent(event);
    pfjets_softElectronByPtBJetTag_handle.SetEvent(event);
    pfjets_softElectronTag_handle.SetEvent(event);
    pfjets_softMuonBJetTag_handle.SetEvent(event);
    pfjets_softMuonByIP3dBJetTag_handle.SetEvent(event);
    pfjets_softMuonByPtBJetTag_handle.SetEvent(event);
    pfjets_trackCountingHighEffBJetTag_handle.SetEvent(event);
    pfjets_trackCountingHighPurBJetTag_handle.SetEvent(event);
    trkjets_combinedSecondaryVertexBJetTag_handle.SetEvent(event);
    trkjets_combinedSecondaryVertexMVABJetTag_handle.SetEvent(event);
    trkjets_jetBProbabilityBJetTag_handle.SetEvent(event);
    trkjets_jetProbabilityBJetTag_handle.SetEvent(event);
    trkjets_simpleSecondaryVertexBJetTag_handle.SetEvent(event);
    trkjets_simpleSecondaryVertexHighEffBJetTag_handle.SetEvent(event);
    trkjets_simpleSecondaryVertexHighPurBJetTags_handle.SetEvent(event);
    trkjets_softElectronByIP3dBJetTag_handle.SetEvent(event);
    trkjets_softElectronByPtBJetTag_handle.SetEvent(event);
    trkjets_softElectronTag_handle.SetEvent(event);
    trkjets_softMuonBJetTag_handle.SetEvent(event);
    trkjets_softMuonByIP3dBJetTag_handle.SetEvent(event);
    trkjets_softMuonByPtBJetTag_handle.SetEvent(event);
    trkjets_trackCountingHighEffBJetTag_handle.SetEvent(event);
    trkjets_trackCountingHighPurBJetTag_handle.SetEvent(event);
    evt_bs_covMatrix_handle.SetEvent(event);
    els_mc3dr_handle.SetEvent(event);
    els_mcdr_handle.SetEvent(event);
    jets_mc3dr_handle.SetEvent(event);
    jets_mcdr_handle.SetEvent(event);
    jets_mc_emEnergy_handle.SetEvent(event);
    jets_mc_gpdr_handle.SetEvent(event);
    jets_mc_hadEnergy_handle.SetEvent(event);
    jets_mc_invEnergy_handle.SetEvent(event);
    jets_mc_otherEnergy_handle.SetEvent(event);
    mus_mc3dr_handle.SetEvent(event);
    mus_mcdr_handle.SetEvent(event);
    pfjets_mc3dr_handle.SetEvent(event);
    pfjets_mcdr_handle.SetEvent(event);
    pfjets_mc_emEnergy_handle.SetEvent(event);
    pfjets_mc_gpdr_handle.SetEvent(event);
    pfjets_mc_hadEnergy_handle.SetEvent(event);
    pfjets_mc_invEnergy_handle.SetEvent(event);
    pfjets_mc_otherEnergy_handle.SetEvent(event);
    photons_mc3dr_handle.SetEvent(event);
    photons_mcdr_handle.SetEvent(event);
    trk_mc3dr_handle.SetEvent(event);
    trk_mcdr_handle.SetEvent(event);
    els_ecalJuraIso_handle.SetEvent(event);
    els_ecalJuraTowerIso_handle.SetEvent(event);
    els_hcalConeIso_handle.SetEvent(event);
    els_tkJuraIso_handle.SetEvent(event);
    els_jetdr_handle.SetEvent(event);
    els_musdr_handle.SetEvent(event);
    els_isoR03_chpf_radial_handle.SetEvent(event);
    els_isoR03_chpf_radialTight_handle.SetEvent(event);
    els_isoR03_chpf_radialTight_bv_handle.SetEvent(event);
    els_isoR03_chpf_radial_bv_handle.SetEvent(event);
    els_isoR03_empf_radial_handle.SetEvent(event);
    els_isoR03_empf_radialTight_handle.SetEvent(event);
    els_isoR03_empf_radialTight_bv_handle.SetEvent(event);
    els_isoR03_empf_radial_bv_handle.SetEvent(event);
    els_isoR03_nhpf_radial_handle.SetEvent(event);
    els_isoR03_nhpf_radialTight_handle.SetEvent(event);
    els_isoR03_nhpf_radialTight_bv_handle.SetEvent(event);
    els_isoR03_nhpf_radial_bv_handle.SetEvent(event);
    els_isoR03_pf2012n0p5_ch_handle.SetEvent(event);
    els_isoR03_pf2012n0p5_em_handle.SetEvent(event);
    els_isoR03_pf2012n0p5_nh_handle.SetEvent(event);
    els_isoR03_pf_radial_handle.SetEvent(event);
    els_isoR03_pf_radialTight_handle.SetEvent(event);
    els_isoR03_pf_radialTight_bv_handle.SetEvent(event);
    els_isoR03_pf_radial_bv_handle.SetEvent(event);
    els_chi2_handle.SetEvent(event);
    els_ckf_chi2_handle.SetEvent(event);
    els_ckf_ndof_handle.SetEvent(event);
    els_conv_dcot_handle.SetEvent(event);
    els_conv_dist_handle.SetEvent(event);
    els_conv_old_dcot_handle.SetEvent(event);
    els_conv_old_dist_handle.SetEvent(event);
    els_conv_old_radius_handle.SetEvent(event);
    els_conv_radius_handle.SetEvent(event);
    els_d0_handle.SetEvent(event);
    els_d0Err_handle.SetEvent(event);
    els_d0corr_handle.SetEvent(event);
    els_dEtaIn_handle.SetEvent(event);
    els_dEtaOut_handle.SetEvent(event);
    els_dPhiIn_handle.SetEvent(event);
    els_dPhiInPhiOut_handle.SetEvent(event);
    els_dPhiOut_handle.SetEvent(event);
    els_deltaEtaEleClusterTrackAtCalo_handle.SetEvent(event);
    els_deltaPhiEleClusterTrackAtCalo_handle.SetEvent(event);
    els_e1x5_handle.SetEvent(event);
    els_e2x5Max_handle.SetEvent(event);
    els_e3x3_handle.SetEvent(event);
    els_e5x5_handle.SetEvent(event);
    els_eMax_handle.SetEvent(event);
    els_eOverPIn_handle.SetEvent(event);
    els_eOverPOut_handle.SetEvent(event);
    els_eSC_handle.SetEvent(event);
    els_eSCPresh_handle.SetEvent(event);
    els_eSCRaw_handle.SetEvent(event);
    els_eSeed_handle.SetEvent(event);
    els_eSeedOverPIn_handle.SetEvent(event);
    els_eSeedOverPOut_handle.SetEvent(event);
    els_ecalEnergy_handle.SetEvent(event);
    els_ecalEnergyError_handle.SetEvent(event);
    els_ecalIso_handle.SetEvent(event);
    els_ecalIso04_handle.SetEvent(event);
    els_etaErr_handle.SetEvent(event);
    els_etaSC_handle.SetEvent(event);
    els_etaSCwidth_handle.SetEvent(event);
    els_fbrem_handle.SetEvent(event);
    els_hOverE_handle.SetEvent(event);
    els_hcalDepth1OverEcal_handle.SetEvent(event);
    els_hcalDepth1TowerSumEt_handle.SetEvent(event);
    els_hcalDepth1TowerSumEt04_handle.SetEvent(event);
    els_hcalDepth2OverEcal_handle.SetEvent(event);
    els_hcalDepth2TowerSumEt_handle.SetEvent(event);
    els_hcalDepth2TowerSumEt04_handle.SetEvent(event);
    els_hcalIso_handle.SetEvent(event);
    els_hcalIso04_handle.SetEvent(event);
    els_ip3d_handle.SetEvent(event);
    els_ip3derr_handle.SetEvent(event);
    els_iso03_pf_handle.SetEvent(event);
    els_iso03_pf2012_ch_handle.SetEvent(event);
    els_iso03_pf2012_em_handle.SetEvent(event);
    els_iso03_pf2012ext_ch_handle.SetEvent(event);
    els_iso03_pf2012ext_em_handle.SetEvent(event);
    els_iso03_pf2012ext_nh_handle.SetEvent(event);
    els_iso03_pf2012_nh_handle.SetEvent(event);
    els_iso03_pf_ch_handle.SetEvent(event);
    els_iso03_pf_gamma05_handle.SetEvent(event);
    els_iso03_pf_nhad05_handle.SetEvent(event);
    els_iso04_pf_handle.SetEvent(event);
    els_iso04_pf2012_ch_handle.SetEvent(event);
    els_iso04_pf2012_em_handle.SetEvent(event);
    els_iso04_pf2012ext_ch_handle.SetEvent(event);
    els_iso04_pf2012ext_em_handle.SetEvent(event);
    els_iso04_pf2012ext_nh_handle.SetEvent(event);
    els_iso04_pf2012_nh_handle.SetEvent(event);
    els_iso04_pf_ch_handle.SetEvent(event);
    els_iso04_pf_gamma05_handle.SetEvent(event);
    els_iso04_pf_nhad05_handle.SetEvent(event);
    els_layer1_charge_handle.SetEvent(event);
    els_lh_handle.SetEvent(event);
    els_mva_handle.SetEvent(event);
    els_ndof_handle.SetEvent(event);
    els_pfChargedHadronIso_handle.SetEvent(event);
    els_pfNeutralHadronIso_handle.SetEvent(event);
    els_pfPhotonIso_handle.SetEvent(event);
    els_phiErr_handle.SetEvent(event);
    els_phiSC_handle.SetEvent(event);
    els_phiSCwidth_handle.SetEvent(event);
    els_ptErr_handle.SetEvent(event);
    els_r9_handle.SetEvent(event);
    els_sigmaEtaEta_handle.SetEvent(event);
    els_sigmaIEtaIEta_handle.SetEvent(event);
    els_sigmaIEtaIEtaSC_handle.SetEvent(event);
    els_sigmaIEtaIPhi_handle.SetEvent(event);
    els_sigmaIPhiIPhi_handle.SetEvent(event);
    els_sigmaIPhiIPhiSC_handle.SetEvent(event);
    els_sigmaIphiIphi_handle.SetEvent(event);
    els_sigmaPhiPhi_handle.SetEvent(event);
    els_tkIso_handle.SetEvent(event);
    els_tkIso04_handle.SetEvent(event);
    els_trackMomentumError_handle.SetEvent(event);
    els_trkdr_handle.SetEvent(event);
    els_trkshFrac_handle.SetEvent(event);
    els_z0_handle.SetEvent(event);
    els_z0Err_handle.SetEvent(event);
    els_z0corr_handle.SetEvent(event);
    gsftrks_chi2_handle.SetEvent(event);
    gsftrks_d0_handle.SetEvent(event);
    gsftrks_d0Err_handle.SetEvent(event);
    gsftrks_d0corr_handle.SetEvent(event);
    gsftrks_d0corrPhi_handle.SetEvent(event);
    gsftrks_d0phiCov_handle.SetEvent(event);
    gsftrks_etaErr_handle.SetEvent(event);
    gsftrks_layer1_charge_handle.SetEvent(event);
    gsftrks_ndof_handle.SetEvent(event);
    gsftrks_phiErr_handle.SetEvent(event);
    gsftrks_ptErr_handle.SetEvent(event);
    gsftrks_z0_handle.SetEvent(event);
    gsftrks_z0Err_handle.SetEvent(event);
    gsftrks_z0corr_handle.SetEvent(event);
    hyp_Ht_handle.SetEvent(event);
    hyp_dPhi_nJet_metMuonJESCorr_handle.SetEvent(event);
    hyp_dPhi_nJet_muCorrMet_handle.SetEvent(event);
    hyp_dPhi_nJet_tcMet_handle.SetEvent(event);
    hyp_dPhi_nJet_unCorrMet_handle.SetEvent(event);
    hyp_ll_chi2_handle.SetEvent(event);
    hyp_ll_d0_handle.SetEvent(event);
    hyp_ll_d0Err_handle.SetEvent(event);
    hyp_ll_d0corr_handle.SetEvent(event);
    hyp_ll_dPhi_metMuonJESCorr_handle.SetEvent(event);
    hyp_ll_dPhi_muCorrMet_handle.SetEvent(event);
    hyp_ll_dPhi_tcMet_handle.SetEvent(event);
    hyp_ll_dPhi_unCorrMet_handle.SetEvent(event);
    hyp_ll_etaErr_handle.SetEvent(event);
    hyp_ll_ndof_handle.SetEvent(event);
    hyp_ll_phiErr_handle.SetEvent(event);
    hyp_ll_ptErr_handle.SetEvent(event);
    hyp_ll_z0_handle.SetEvent(event);
    hyp_ll_z0Err_handle.SetEvent(event);
    hyp_ll_z0corr_handle.SetEvent(event);
    hyp_lt_chi2_handle.SetEvent(event);
    hyp_lt_d0_handle.SetEvent(event);
    hyp_lt_d0Err_handle.SetEvent(event);
    hyp_lt_d0corr_handle.SetEvent(event);
    hyp_lt_dPhi_metMuonJESCorr_handle.SetEvent(event);
    hyp_lt_dPhi_muCorrMet_handle.SetEvent(event);
    hyp_lt_dPhi_tcMet_handle.SetEvent(event);
    hyp_lt_dPhi_unCorrMet_handle.SetEvent(event);
    hyp_lt_etaErr_handle.SetEvent(event);
    hyp_lt_ndof_handle.SetEvent(event);
    hyp_lt_phiErr_handle.SetEvent(event);
    hyp_lt_ptErr_handle.SetEvent(event);
    hyp_lt_z0_handle.SetEvent(event);
    hyp_lt_z0Err_handle.SetEvent(event);
    hyp_lt_z0corr_handle.SetEvent(event);
    hyp_mt2_metMuonJESCorr_handle.SetEvent(event);
    hyp_mt2_muCorrMet_handle.SetEvent(event);
    hyp_mt2_tcMet_handle.SetEvent(event);
    hyp_sumJetPt_handle.SetEvent(event);
    hyp_FVFit_chi2ndf_handle.SetEvent(event);
    hyp_FVFit_prob_handle.SetEvent(event);
    hyp_FVFit_v4cxx_handle.SetEvent(event);
    hyp_FVFit_v4cxy_handle.SetEvent(event);
    hyp_FVFit_v4cyy_handle.SetEvent(event);
    hyp_FVFit_v4czx_handle.SetEvent(event);
    hyp_FVFit_v4czy_handle.SetEvent(event);
    hyp_FVFit_v4czz_handle.SetEvent(event);
    jets_approximatefHPD_handle.SetEvent(event);
    jets_approximatefRBX_handle.SetEvent(event);
    jets_cor_handle.SetEvent(event);
    jets_corL1FastL2L3_handle.SetEvent(event);
    jets_corL1L2L3_handle.SetEvent(event);
    jets_emFrac_handle.SetEvent(event);
    jets_fHPD_handle.SetEvent(event);
    jets_fRBX_handle.SetEvent(event);
    jets_fSubDetector1_handle.SetEvent(event);
    jets_fSubDetector2_handle.SetEvent(event);
    jets_fSubDetector3_handle.SetEvent(event);
    jets_fSubDetector4_handle.SetEvent(event);
    jets_hitsInN90_handle.SetEvent(event);
    jets_n90Hits_handle.SetEvent(event);
    jets_nECALTowers_handle.SetEvent(event);
    jets_nHCALTowers_handle.SetEvent(event);
    jets_restrictedEMF_handle.SetEvent(event);
    mus_met_deltax_handle.SetEvent(event);
    mus_met_deltay_handle.SetEvent(event);
    mus_eledr_handle.SetEvent(event);
    mus_jetdr_handle.SetEvent(event);
    mus_isoR03_chpf_radial_handle.SetEvent(event);
    mus_isoR03_chpf_radialTight_handle.SetEvent(event);
    mus_isoR03_empf_radial_handle.SetEvent(event);
    mus_isoR03_empf_radialTight_handle.SetEvent(event);
    mus_isoR03_nhpf_radial_handle.SetEvent(event);
    mus_isoR03_nhpf_radialTight_handle.SetEvent(event);
    mus_isoR03_pf_radial_handle.SetEvent(event);
    mus_isoR03_pf_radialTight_handle.SetEvent(event);
    mus_backToBackCompat_handle.SetEvent(event);
    mus_caloCompatibility_handle.SetEvent(event);
    mus_chi2_handle.SetEvent(event);
    mus_chi2LocalMomentum_handle.SetEvent(event);
    mus_chi2LocalPosition_handle.SetEvent(event);
    mus_cosmicCompat_handle.SetEvent(event);
    mus_d0_handle.SetEvent(event);
    mus_d0Err_handle.SetEvent(event);
    mus_d0corr_handle.SetEvent(event);
    mus_e_em_handle.SetEvent(event);
    mus_e_emS9_handle.SetEvent(event);
    mus_e_had_handle.SetEvent(event);
    mus_e_hadS9_handle.SetEvent(event);
    mus_e_ho_handle.SetEvent(event);
    mus_e_hoS9_handle.SetEvent(event);
    mus_etaErr_handle.SetEvent(event);
    mus_gfit_chi2_handle.SetEvent(event);
    mus_gfit_d0_handle.SetEvent(event);
    mus_gfit_d0Err_handle.SetEvent(event);
    mus_gfit_d0corr_handle.SetEvent(event);
    mus_gfit_ndof_handle.SetEvent(event);
    mus_gfit_qoverp_handle.SetEvent(event);
    mus_gfit_qoverpError_handle.SetEvent(event);
    mus_gfit_z0_handle.SetEvent(event);
    mus_gfit_z0Err_handle.SetEvent(event);
    mus_gfit_z0corr_handle.SetEvent(event);
    mus_glbKink_handle.SetEvent(event);
    mus_glbTrackProbability_handle.SetEvent(event);
    mus_globalDeltaEtaPhi_handle.SetEvent(event);
    mus_ip3d_handle.SetEvent(event);
    mus_ip3derr_handle.SetEvent(event);
    mus_iso03_emEt_handle.SetEvent(event);
    mus_iso03_hadEt_handle.SetEvent(event);
    mus_iso03_hoEt_handle.SetEvent(event);
    mus_iso03_pf_handle.SetEvent(event);
    mus_iso03_sumPt_handle.SetEvent(event);
    mus_iso04_pf_handle.SetEvent(event);
    mus_iso05_emEt_handle.SetEvent(event);
    mus_iso05_hadEt_handle.SetEvent(event);
    mus_iso05_hoEt_handle.SetEvent(event);
    mus_iso05_sumPt_handle.SetEvent(event);
    mus_isoR03_pf_ChargedHadronPt_handle.SetEvent(event);
    mus_isoR03_pf_ChargedParticlePt_handle.SetEvent(event);
    mus_isoR03_pf_NeutralHadronEt_handle.SetEvent(event);
    mus_isoR03_pf_NeutralHadronEtHighThreshold_handle.SetEvent(event);
    mus_isoR03_pf_PUPt_handle.SetEvent(event);
    mus_isoR03_pf_PhotonEt_handle.SetEvent(event);
    mus_isoR03_pf_PhotonEtHighThreshold_handle.SetEvent(event);
    mus_isoR04_pf_ChargedHadronPt_handle.SetEvent(event);
    mus_isoR04_pf_ChargedParticlePt_handle.SetEvent(event);
    mus_isoR04_pf_NeutralHadronEt_handle.SetEvent(event);
    mus_isoR04_pf_NeutralHadronEtHighThreshold_handle.SetEvent(event);
    mus_isoR04_pf_PUPt_handle.SetEvent(event);
    mus_isoR04_pf_PhotonEt_handle.SetEvent(event);
    mus_isoR04_pf_PhotonEtHighThreshold_handle.SetEvent(event);
    mus_iso_ecalvetoDep_handle.SetEvent(event);
    mus_iso_hcalvetoDep_handle.SetEvent(event);
    mus_iso_hovetoDep_handle.SetEvent(event);
    mus_iso_trckvetoDep_handle.SetEvent(event);
    mus_localDistance_handle.SetEvent(event);
    mus_ndof_handle.SetEvent(event);
    mus_overlapCompat_handle.SetEvent(event);
    mus_pfdeltaP_handle.SetEvent(event);
    mus_pfecalE_handle.SetEvent(event);
    mus_pfhcalE_handle.SetEvent(event);
    mus_pfmva_emu_handle.SetEvent(event);
    mus_pfmva_epi_handle.SetEvent(event);
    mus_pfmva_nothing_gamma_handle.SetEvent(event);
    mus_pfmva_nothing_nh_handle.SetEvent(event);
    mus_pfmva_pimu_handle.SetEvent(event);
    mus_pfpS1E_handle.SetEvent(event);
    mus_pfpS2E_handle.SetEvent(event);
    mus_pfrawEcalE_handle.SetEvent(event);
    mus_pfrawHcalE_handle.SetEvent(event);
    mus_phiErr_handle.SetEvent(event);
    mus_ptErr_handle.SetEvent(event);
    mus_qoverp_handle.SetEvent(event);
    mus_qoverpError_handle.SetEvent(event);
    mus_segmCompatibility_handle.SetEvent(event);
    mus_staRelChi2_handle.SetEvent(event);
    mus_sta_chi2_handle.SetEvent(event);
    mus_sta_d0_handle.SetEvent(event);
    mus_sta_d0Err_handle.SetEvent(event);
    mus_sta_d0corr_handle.SetEvent(event);
    mus_sta_ndof_handle.SetEvent(event);
    mus_sta_qoverp_handle.SetEvent(event);
    mus_sta_qoverpError_handle.SetEvent(event);
    mus_sta_z0_handle.SetEvent(event);
    mus_sta_z0Err_handle.SetEvent(event);
    mus_sta_z0corr_handle.SetEvent(event);
    mus_timeAtIpInOut_handle.SetEvent(event);
    mus_timeAtIpInOutErr_handle.SetEvent(event);
    mus_timeAtIpOutIn_handle.SetEvent(event);
    mus_timeAtIpOutInErr_handle.SetEvent(event);
    mus_timeCompat_handle.SetEvent(event);
    mus_trkKink_handle.SetEvent(event);
    mus_trkRelChi2_handle.SetEvent(event);
    mus_vertexCompat_handle.SetEvent(event);
    mus_vertexphi_handle.SetEvent(event);
    mus_z0_handle.SetEvent(event);
    mus_z0Err_handle.SetEvent(event);
    mus_z0corr_handle.SetEvent(event);
    pfjets_mvavalue_handle.SetEvent(event);
    pfjets_full53xmva_beta_handle.SetEvent(event);
    pfjets_full53xmva_betaStar_handle.SetEvent(event);
    pfjets_full53xmva_d0_handle.SetEvent(event);
    pfjets_full53xmva_dRMean_handle.SetEvent(event);
    pfjets_full53xmva_dZ_handle.SetEvent(event);
    pfjets_full53xmva_frac01_handle.SetEvent(event);
    pfjets_full53xmva_frac02_handle.SetEvent(event);
    pfjets_full53xmva_frac03_handle.SetEvent(event);
    pfjets_full53xmva_frac04_handle.SetEvent(event);
    pfjets_full53xmva_frac05_handle.SetEvent(event);
    pfjets_full53xmva_nCharged_handle.SetEvent(event);
    pfjets_full53xmva_nNeutrals_handle.SetEvent(event);
    pfjets_full53xmva_nvtx_handle.SetEvent(event);
    pfjets_full53xmvavalue_handle.SetEvent(event);
    pfjets_full5xmvavalue_handle.SetEvent(event);
    trkjet_met_handle.SetEvent(event);
    trkjet_metPhi_handle.SetEvent(event);
    trkjet_sumet_handle.SetEvent(event);
    trk_met_handle.SetEvent(event);
    trk_metPhi_handle.SetEvent(event);
    trk_sumet_handle.SetEvent(event);
    pfcands_deltaP_handle.SetEvent(event);
    pfcands_ecalE_handle.SetEvent(event);
    pfcands_hcalE_handle.SetEvent(event);
    pfcands_mva_emu_handle.SetEvent(event);
    pfcands_mva_epi_handle.SetEvent(event);
    pfcands_mva_nothing_gamma_handle.SetEvent(event);
    pfcands_mva_nothing_nh_handle.SetEvent(event);
    pfcands_mva_pimu_handle.SetEvent(event);
    pfcands_pS1E_handle.SetEvent(event);
    pfcands_pS2E_handle.SetEvent(event);
    pfcands_rawEcalE_handle.SetEvent(event);
    pfcands_rawHcalE_handle.SetEvent(event);
    pfels_deltaP_handle.SetEvent(event);
    pfels_ecalE_handle.SetEvent(event);
    pfels_hcalE_handle.SetEvent(event);
    pfels_iso04ChargedHadrons_handle.SetEvent(event);
    pfels_iso04NeutralHadrons_handle.SetEvent(event);
    pfels_iso04Photons_handle.SetEvent(event);
    pfels_isoChargedHadrons_handle.SetEvent(event);
    pfels_isoNeutralHadrons_handle.SetEvent(event);
    pfels_isoPhotons_handle.SetEvent(event);
    pfels_mva_emu_handle.SetEvent(event);
    pfels_mva_epi_handle.SetEvent(event);
    pfels_mva_nothing_gamma_handle.SetEvent(event);
    pfels_mva_nothing_nh_handle.SetEvent(event);
    pfels_mva_pimu_handle.SetEvent(event);
    pfels_pS1E_handle.SetEvent(event);
    pfels_pS2E_handle.SetEvent(event);
    pfels_rawEcalE_handle.SetEvent(event);
    pfels_rawHcalE_handle.SetEvent(event);
    pfjets_area_handle.SetEvent(event);
    pfjets_chargedEmE_handle.SetEvent(event);
    pfjets_chargedHadronE_handle.SetEvent(event);
    pfjets_cor_handle.SetEvent(event);
    pfjets_corL1Fast_handle.SetEvent(event);
    pfjets_corL1FastL2L3_handle.SetEvent(event);
    pfjets_corL1FastL2L3residual_handle.SetEvent(event);
    pfjets_corL1L2L3_handle.SetEvent(event);
    pfjets_electronE_handle.SetEvent(event);
    pfjets_hfEmE_handle.SetEvent(event);
    pfjets_hfHadronE_handle.SetEvent(event);
    pfjets_muonE_handle.SetEvent(event);
    pfjets_neutralEmE_handle.SetEvent(event);
    pfjets_neutralHadronE_handle.SetEvent(event);
    pfjets_photonE_handle.SetEvent(event);
    pfmus_deltaP_handle.SetEvent(event);
    pfmus_ecalE_handle.SetEvent(event);
    pfmus_hcalE_handle.SetEvent(event);
    pfmus_iso04ChargedHadrons_handle.SetEvent(event);
    pfmus_iso04NeutralHadrons_handle.SetEvent(event);
    pfmus_iso04Photons_handle.SetEvent(event);
    pfmus_isoChargedHadrons_handle.SetEvent(event);
    pfmus_isoNeutralHadrons_handle.SetEvent(event);
    pfmus_isoPhotons_handle.SetEvent(event);
    pfmus_mva_emu_handle.SetEvent(event);
    pfmus_mva_epi_handle.SetEvent(event);
    pfmus_mva_nothing_gamma_handle.SetEvent(event);
    pfmus_mva_nothing_nh_handle.SetEvent(event);
    pfmus_mva_pimu_handle.SetEvent(event);
    pfmus_pS1E_handle.SetEvent(event);
    pfmus_pS2E_handle.SetEvent(event);
    pfmus_rawEcalE_handle.SetEvent(event);
    pfmus_rawHcalE_handle.SetEvent(event);
    taus_pf_againstElectronDeadECAL_handle.SetEvent(event);
    taus_pf_againstElectronLoose_handle.SetEvent(event);
    taus_pf_againstElectronLooseMVA2_handle.SetEvent(event);
    taus_pf_againstElectronLooseMVA3_handle.SetEvent(event);
    taus_pf_againstElectronMVA_handle.SetEvent(event);
    taus_pf_againstElectronMVA2category_handle.SetEvent(event);
    taus_pf_againstElectronMVA2raw_handle.SetEvent(event);
    taus_pf_againstElectronMVA3category_handle.SetEvent(event);
    taus_pf_againstElectronMVA3raw_handle.SetEvent(event);
    taus_pf_againstElectronMedium_handle.SetEvent(event);
    taus_pf_againstElectronMediumMVA2_handle.SetEvent(event);
    taus_pf_againstElectronMediumMVA3_handle.SetEvent(event);
    taus_pf_againstElectronTight_handle.SetEvent(event);
    taus_pf_againstElectronTightMVA2_handle.SetEvent(event);
    taus_pf_againstElectronTightMVA3_handle.SetEvent(event);
    taus_pf_againstElectronVLooseMVA2_handle.SetEvent(event);
    taus_pf_againstElectronVTightMVA3_handle.SetEvent(event);
    taus_pf_againstMuonLoose_handle.SetEvent(event);
    taus_pf_againstMuonLoose2_handle.SetEvent(event);
    taus_pf_againstMuonMedium_handle.SetEvent(event);
    taus_pf_againstMuonMedium2_handle.SetEvent(event);
    taus_pf_againstMuonTight_handle.SetEvent(event);
    taus_pf_againstMuonTight2_handle.SetEvent(event);
    taus_pf_byCombinedIsolationDeltaBetaCorrRaw_handle.SetEvent(event);
    taus_pf_byCombinedIsolationDeltaBetaCorrRaw3Hits_handle.SetEvent(event);
    taus_pf_byDecayModeFinding_handle.SetEvent(event);
    taus_pf_byIsolationMVA2raw_handle.SetEvent(event);
    taus_pf_byIsolationMVAraw_handle.SetEvent(event);
    taus_pf_byLooseCombinedIsolationDeltaBetaCorr_handle.SetEvent(event);
    taus_pf_byLooseCombinedIsolationDeltaBetaCorr3Hits_handle.SetEvent(event);
    taus_pf_byLooseIsolationMVA_handle.SetEvent(event);
    taus_pf_byLooseIsolationMVA2_handle.SetEvent(event);
    taus_pf_byMediumCombinedIsolationDeltaBetaCorr_handle.SetEvent(event);
    taus_pf_byMediumCombinedIsolationDeltaBetaCorr3Hits_handle.SetEvent(event);
    taus_pf_byMediumIsolationMVA_handle.SetEvent(event);
    taus_pf_byMediumIsolationMVA2_handle.SetEvent(event);
    taus_pf_byTightCombinedIsolationDeltaBetaCorr_handle.SetEvent(event);
    taus_pf_byTightCombinedIsolationDeltaBetaCorr3Hits_handle.SetEvent(event);
    taus_pf_byTightIsolationMVA_handle.SetEvent(event);
    taus_pf_byTightIsolationMVA2_handle.SetEvent(event);
    taus_pf_byVLooseCombinedIsolationDeltaBetaCorr_handle.SetEvent(event);
    photons_e1x5_handle.SetEvent(event);
    photons_e2x5Max_handle.SetEvent(event);
    photons_e3x3_handle.SetEvent(event);
    photons_e5x5_handle.SetEvent(event);
    photons_ecalIso03_handle.SetEvent(event);
    photons_ecalIso04_handle.SetEvent(event);
    photons_hOverE_handle.SetEvent(event);
    photons_hcalDepth1TowerSumEtBcConeDR03_handle.SetEvent(event);
    photons_hcalDepth1TowerSumEtBcConeDR04_handle.SetEvent(event);
    photons_hcalDepth2TowerSumEtBcConeDR03_handle.SetEvent(event);
    photons_hcalDepth2TowerSumEtBcConeDR04_handle.SetEvent(event);
    photons_hcalIso03_handle.SetEvent(event);
    photons_hcalIso04_handle.SetEvent(event);
    photons_hcalTowerSumEtBcConeDR03_handle.SetEvent(event);
    photons_hcalTowerSumEtBcConeDR04_handle.SetEvent(event);
    photons_ntkIsoHollow03_handle.SetEvent(event);
    photons_ntkIsoHollow04_handle.SetEvent(event);
    photons_ntkIsoSolid03_handle.SetEvent(event);
    photons_ntkIsoSolid04_handle.SetEvent(event);
    photons_sigmaEtaEta_handle.SetEvent(event);
    photons_sigmaIEtaIEta_handle.SetEvent(event);
    photons_swissSeed_handle.SetEvent(event);
    photons_tkIsoHollow03_handle.SetEvent(event);
    photons_tkIsoHollow04_handle.SetEvent(event);
    photons_tkIsoSolid03_handle.SetEvent(event);
    photons_tkIsoSolid04_handle.SetEvent(event);
    puInfo_trueNumInteractions_handle.SetEvent(event);
    convs_chi2_handle.SetEvent(event);
    convs_dl_handle.SetEvent(event);
    convs_ndof_handle.SetEvent(event);
    sparm_values_handle.SetEvent(event);
    scs_clustersSize_handle.SetEvent(event);
    scs_crystalsSize_handle.SetEvent(event);
    scs_e1x3_handle.SetEvent(event);
    scs_e1x5_handle.SetEvent(event);
    scs_e2nd_handle.SetEvent(event);
    scs_e2x2_handle.SetEvent(event);
    scs_e2x5Max_handle.SetEvent(event);
    scs_e3x1_handle.SetEvent(event);
    scs_e3x2_handle.SetEvent(event);
    scs_e3x3_handle.SetEvent(event);
    scs_e4x4_handle.SetEvent(event);
    scs_e5x5_handle.SetEvent(event);
    scs_eMax_handle.SetEvent(event);
    scs_eSeed_handle.SetEvent(event);
    scs_energy_handle.SetEvent(event);
    scs_eta_handle.SetEvent(event);
    scs_hoe_handle.SetEvent(event);
    scs_laserCorMax_handle.SetEvent(event);
    scs_laserCorMean_handle.SetEvent(event);
    scs_laserCorSeed_handle.SetEvent(event);
    scs_phi_handle.SetEvent(event);
    scs_preshowerEnergy_handle.SetEvent(event);
    scs_rawEnergy_handle.SetEvent(event);
    scs_sigmaEtaEta_handle.SetEvent(event);
    scs_sigmaEtaPhi_handle.SetEvent(event);
    scs_sigmaIEtaIEta_handle.SetEvent(event);
    scs_sigmaIEtaIEtaSC_handle.SetEvent(event);
    scs_sigmaIEtaIPhi_handle.SetEvent(event);
    scs_sigmaIEtaIPhiSC_handle.SetEvent(event);
    scs_sigmaIPhiIPhi_handle.SetEvent(event);
    scs_sigmaIPhiIPhiSC_handle.SetEvent(event);
    scs_sigmaPhiPhi_handle.SetEvent(event);
    scs_timeSeed_handle.SetEvent(event);
    svs_anglePV_handle.SetEvent(event);
    svs_chi2_handle.SetEvent(event);
    svs_dist3Dsig_handle.SetEvent(event);
    svs_dist3Dval_handle.SetEvent(event);
    svs_distXYsig_handle.SetEvent(event);
    svs_distXYval_handle.SetEvent(event);
    svs_ndof_handle.SetEvent(event);
    svs_prob_handle.SetEvent(event);
    svs_xError_handle.SetEvent(event);
    svs_yError_handle.SetEvent(event);
    svs_zError_handle.SetEvent(event);
    mus_tcmet_deltax_handle.SetEvent(event);
    mus_tcmet_deltay_handle.SetEvent(event);
    pfcands_dzpv_handle.SetEvent(event);
    pfcands_trkiso_handle.SetEvent(event);
    trks_chi2_handle.SetEvent(event);
    trks_d0_handle.SetEvent(event);
    trks_d0Err_handle.SetEvent(event);
    trks_d0corr_handle.SetEvent(event);
    trks_d0corrPhi_handle.SetEvent(event);
    trks_d0phiCov_handle.SetEvent(event);
    trks_etaErr_handle.SetEvent(event);
    trks_layer1_charge_handle.SetEvent(event);
    trks_ndof_handle.SetEvent(event);
    trks_phiErr_handle.SetEvent(event);
    trks_ptErr_handle.SetEvent(event);
    trks_validFraction_handle.SetEvent(event);
    trks_z0_handle.SetEvent(event);
    trks_z0Err_handle.SetEvent(event);
    trks_z0corr_handle.SetEvent(event);
    trkjets_cor_handle.SetEvent(event);
    trks_d0Errvtx_handle.SetEvent(event);
    trks_d0vtx_handle.SetEvent(event);
    vtxs_chi2_handle.SetEvent(event);
    vtxs_ndof_handle.SetEvent(event);
    vtxs_sumpt_handle.SetEvent(event);
    vtxs_xError_handle.SetEvent(event);
    vtxs_yError_handle.SetEvent(event);
    vtxs_zError_handle.SetEvent(event);
    bsvtxs_chi2_handle.SetEvent(event);
    bsvtxs_ndof_handle.SetEvent(event);
    bsvtxs_sumpt_handle.SetEvent(event);
    bsvtxs_xError_handle.SetEvent(event);
    bsvtxs_yError_handle.SetEvent(event);
    bsvtxs_zError_handle.SetEvent(event);
    els_convs_dcot_handle.SetEvent(event);
    els_convs_dist_handle.SetEvent(event);
    els_convs_radius_handle.SetEvent(event);
    mus_stationShowerDeltaR_handle.SetEvent(event);
    mus_stationShowerSizeT_handle.SetEvent(event);
    puInfo_instLumi_handle.SetEvent(event);
    puInfo_sump_highpt_handle.SetEvent(event);
    puInfo_sumpt_lowpt_handle.SetEvent(event);
    puInfo_zpositions_handle.SetEvent(event);
    vtxs_covMatrix_handle.SetEvent(event);
    bsvtxs_covMatrix_handle.SetEvent(event);
    evt_cscLooseHaloId_handle.SetEvent(event);
    evt_cscTightHaloId_handle.SetEvent(event);
    evt_ecalLooseHaloId_handle.SetEvent(event);
    evt_ecalTightHaloId_handle.SetEvent(event);
    evt_extremeTightHaloId_handle.SetEvent(event);
    evt_globalLooseHaloId_handle.SetEvent(event);
    evt_globalTightHaloId_handle.SetEvent(event);
    evt_hcalLooseHaloId_handle.SetEvent(event);
    evt_hcalTightHaloId_handle.SetEvent(event);
    evt_looseHaloId_handle.SetEvent(event);
    evt_nHaloLikeTracks_handle.SetEvent(event);
    evt_nHaloTriggerCandidates_handle.SetEvent(event);
    evt_tightHaloId_handle.SetEvent(event);
    evt_bsType_handle.SetEvent(event);
    evt_bunchCrossing_handle.SetEvent(event);
    evt_experimentType_handle.SetEvent(event);
    evt_isRealData_handle.SetEvent(event);
    evt_orbitNumber_handle.SetEvent(event);
    evt_storeNumber_handle.SetEvent(event);
    hcalnoise_GetRecHitCount_handle.SetEvent(event);
    hcalnoise_GetRecHitCount15_handle.SetEvent(event);
    hcalnoise_maxHPDHits_handle.SetEvent(event);
    hcalnoise_maxHPDNoOtherHits_handle.SetEvent(event);
    hcalnoise_maxRBXHits_handle.SetEvent(event);
    hcalnoise_maxZeros_handle.SetEvent(event);
    hcalnoise_noiseFilterStatus_handle.SetEvent(event);
    hcalnoise_noiseType_handle.SetEvent(event);
    hcalnoise_num10GeVHits_handle.SetEvent(event);
    hcalnoise_num25GeVHits_handle.SetEvent(event);
    hcalnoise_numFlatNoiseChannels_handle.SetEvent(event);
    hcalnoise_numIsolatedNoiseChannels_handle.SetEvent(event);
    hcalnoise_numProblematicRBXs_handle.SetEvent(event);
    hcalnoise_numSpikeNoiseChannels_handle.SetEvent(event);
    hcalnoise_numTS4TS5NoiseChannels_handle.SetEvent(event);
    hcalnoise_numTriangleNoiseChannels_handle.SetEvent(event);
    hcalnoise_passHighLevelNoiseFilter_handle.SetEvent(event);
    hcalnoise_passLooseNoiseFilter_handle.SetEvent(event);
    hcalnoise_passTightNoiseFilter_handle.SetEvent(event);
    l1_nemiso_handle.SetEvent(event);
    l1_nemnoiso_handle.SetEvent(event);
    l1_njetsc_handle.SetEvent(event);
    l1_njetsf_handle.SetEvent(event);
    l1_njetst_handle.SetEvent(event);
    l1_nmus_handle.SetEvent(event);
    ls_lumiSecQual_handle.SetEvent(event);
    pdfinfo_id1_handle.SetEvent(event);
    pdfinfo_id2_handle.SetEvent(event);
    sparm_subProcessId_handle.SetEvent(event);
    evt_ecaliPhiSuspects_handle.SetEvent(event);
    evt_globaliPhiSuspects_handle.SetEvent(event);
    evt_hcaliPhiSuspects_handle.SetEvent(event);
    els_mc3_id_handle.SetEvent(event);
    els_mc3idx_handle.SetEvent(event);
    els_mc3_motherid_handle.SetEvent(event);
    els_mc3_motheridx_handle.SetEvent(event);
    els_mc_id_handle.SetEvent(event);
    els_mcidx_handle.SetEvent(event);
    els_mc_motherid_handle.SetEvent(event);
    jets_mc3_id_handle.SetEvent(event);
    jets_mc3idx_handle.SetEvent(event);
    jets_mc_gpidx_handle.SetEvent(event);
    jets_mc_id_handle.SetEvent(event);
    jets_mcidx_handle.SetEvent(event);
    jets_mc_motherid_handle.SetEvent(event);
    mus_mc3_id_handle.SetEvent(event);
    mus_mc3idx_handle.SetEvent(event);
    mus_mc3_motherid_handle.SetEvent(event);
    mus_mc3_motheridx_handle.SetEvent(event);
    mus_mc_id_handle.SetEvent(event);
    mus_mcidx_handle.SetEvent(event);
    mus_mc_motherid_handle.SetEvent(event);
    pfjets_mc3_id_handle.SetEvent(event);
    pfjets_mc3idx_handle.SetEvent(event);
    pfjets_mc_gpidx_handle.SetEvent(event);
    pfjets_mc_id_handle.SetEvent(event);
    pfjets_mcidx_handle.SetEvent(event);
    pfjets_mc_motherid_handle.SetEvent(event);
    photons_mc3_id_handle.SetEvent(event);
    photons_mc3idx_handle.SetEvent(event);
    photons_mc3_motherid_handle.SetEvent(event);
    photons_mc3_motheridx_handle.SetEvent(event);
    photons_mc_id_handle.SetEvent(event);
    photons_mcidx_handle.SetEvent(event);
    photons_mc_motherid_handle.SetEvent(event);
    trk_mc3_id_handle.SetEvent(event);
    trk_mc3idx_handle.SetEvent(event);
    trk_mc3_motherid_handle.SetEvent(event);
    trk_mc3_motheridx_handle.SetEvent(event);
    trk_mc_id_handle.SetEvent(event);
    trk_mcidx_handle.SetEvent(event);
    trk_mc_motherid_handle.SetEvent(event);
    els_closestJet_handle.SetEvent(event);
    els_closestMuon_handle.SetEvent(event);
    els_pfelsidx_handle.SetEvent(event);
    els_category_handle.SetEvent(event);
    els_charge_handle.SetEvent(event);
    els_ckf_laywithmeas_handle.SetEvent(event);
    els_class_handle.SetEvent(event);
    els_conv_delMissHits_handle.SetEvent(event);
    els_conv_flag_handle.SetEvent(event);
    els_conv_gsftkidx_handle.SetEvent(event);
    els_conv_old_delMissHits_handle.SetEvent(event);
    els_conv_old_flag_handle.SetEvent(event);
    els_conv_old_gsftkidx_handle.SetEvent(event);
    els_conv_old_tkidx_handle.SetEvent(event);
    els_conv_tkidx_handle.SetEvent(event);
    els_exp_innerlayers_handle.SetEvent(event);
    els_exp_outerlayers_handle.SetEvent(event);
    els_fiduciality_handle.SetEvent(event);
    els_gsftrkidx_handle.SetEvent(event);
    els_layer1_det_handle.SetEvent(event);
    els_layer1_layer_handle.SetEvent(event);
    els_layer1_sizerphi_handle.SetEvent(event);
    els_layer1_sizerz_handle.SetEvent(event);
    els_lostHits_handle.SetEvent(event);
    els_lost_pixelhits_handle.SetEvent(event);
    els_nSeed_handle.SetEvent(event);
    els_sccharge_handle.SetEvent(event);
    els_scindex_handle.SetEvent(event);
    els_trk_charge_handle.SetEvent(event);
    els_trkidx_handle.SetEvent(event);
    els_type_handle.SetEvent(event);
    els_validHits_handle.SetEvent(event);
    els_valid_pixelhits_handle.SetEvent(event);
    genps_id_handle.SetEvent(event);
    genps_id_mother_handle.SetEvent(event);
    genps_status_handle.SetEvent(event);
    gsftrks_charge_handle.SetEvent(event);
    gsftrks_exp_innerlayers_handle.SetEvent(event);
    gsftrks_exp_outerlayers_handle.SetEvent(event);
    gsftrks_layer1_det_handle.SetEvent(event);
    gsftrks_layer1_layer_handle.SetEvent(event);
    gsftrks_layer1_sizerphi_handle.SetEvent(event);
    gsftrks_layer1_sizerz_handle.SetEvent(event);
    gsftrks_lostHits_handle.SetEvent(event);
    gsftrks_lost_pixelhits_handle.SetEvent(event);
    gsftrks_nlayers_handle.SetEvent(event);
    gsftrks_nlayers3D_handle.SetEvent(event);
    gsftrks_nlayersLost_handle.SetEvent(event);
    gsftrks_validHits_handle.SetEvent(event);
    gsftrks_valid_pixelhits_handle.SetEvent(event);
    hyp_ll_charge_handle.SetEvent(event);
    hyp_ll_id_handle.SetEvent(event);
    hyp_ll_index_handle.SetEvent(event);
    hyp_ll_lostHits_handle.SetEvent(event);
    hyp_ll_validHits_handle.SetEvent(event);
    hyp_lt_charge_handle.SetEvent(event);
    hyp_lt_id_handle.SetEvent(event);
    hyp_lt_index_handle.SetEvent(event);
    hyp_lt_lostHits_handle.SetEvent(event);
    hyp_lt_validHits_handle.SetEvent(event);
    hyp_njets_handle.SetEvent(event);
    hyp_nojets_handle.SetEvent(event);
    hyp_type_handle.SetEvent(event);
    hyp_FVFit_ndf_handle.SetEvent(event);
    hyp_FVFit_status_handle.SetEvent(event);
    hyp_ll_mc_id_handle.SetEvent(event);
    hyp_ll_mc_motherid_handle.SetEvent(event);
    hyp_lt_mc_id_handle.SetEvent(event);
    hyp_lt_mc_motherid_handle.SetEvent(event);
    pfjets_mcflavorAlgo_handle.SetEvent(event);
    pfjets_mcflavorPhys_handle.SetEvent(event);
    jets_closestElectron_handle.SetEvent(event);
    jets_closestMuon_handle.SetEvent(event);
    l1_emiso_ieta_handle.SetEvent(event);
    l1_emiso_iphi_handle.SetEvent(event);
    l1_emiso_rawId_handle.SetEvent(event);
    l1_emiso_type_handle.SetEvent(event);
    l1_emnoiso_ieta_handle.SetEvent(event);
    l1_emnoiso_iphi_handle.SetEvent(event);
    l1_emnoiso_rawId_handle.SetEvent(event);
    l1_emnoiso_type_handle.SetEvent(event);
    l1_jetsc_ieta_handle.SetEvent(event);
    l1_jetsc_iphi_handle.SetEvent(event);
    l1_jetsc_rawId_handle.SetEvent(event);
    l1_jetsc_type_handle.SetEvent(event);
    l1_jetsf_ieta_handle.SetEvent(event);
    l1_jetsf_iphi_handle.SetEvent(event);
    l1_jetsf_rawId_handle.SetEvent(event);
    l1_jetsf_type_handle.SetEvent(event);
    l1_jetst_ieta_handle.SetEvent(event);
    l1_jetst_iphi_handle.SetEvent(event);
    l1_jetst_rawId_handle.SetEvent(event);
    l1_jetst_type_handle.SetEvent(event);
    l1_mus_flags_handle.SetEvent(event);
    l1_mus_q_handle.SetEvent(event);
    l1_mus_qual_handle.SetEvent(event);
    l1_mus_qualFlags_handle.SetEvent(event);
    mus_met_flag_handle.SetEvent(event);
    mus_closestEle_handle.SetEvent(event);
    mus_closestJet_handle.SetEvent(event);
    mus_pfmusidx_handle.SetEvent(event);
    mus_charge_handle.SetEvent(event);
    mus_gfit_validHits_handle.SetEvent(event);
    mus_gfit_validSTAHits_handle.SetEvent(event);
    mus_gfit_validSiHits_handle.SetEvent(event);
    mus_goodmask_handle.SetEvent(event);
    mus_iso03_ntrk_handle.SetEvent(event);
    mus_iso05_ntrk_handle.SetEvent(event);
    mus_lostHits_handle.SetEvent(event);
    mus_muonBestTrackType_handle.SetEvent(event);
    mus_nOverlaps_handle.SetEvent(event);
    mus_nmatches_handle.SetEvent(event);
    mus_numberOfMatchedStations_handle.SetEvent(event);
    mus_overlap0_handle.SetEvent(event);
    mus_overlap1_handle.SetEvent(event);
    mus_pfcharge_handle.SetEvent(event);
    mus_pfflag_handle.SetEvent(event);
    mus_pfparticleId_handle.SetEvent(event);
    mus_pid_PFMuon_handle.SetEvent(event);
    mus_pid_TM2DCompatibilityLoose_handle.SetEvent(event);
    mus_pid_TM2DCompatibilityTight_handle.SetEvent(event);
    mus_pid_TMLastStationLoose_handle.SetEvent(event);
    mus_pid_TMLastStationTight_handle.SetEvent(event);
    mus_sta_validHits_handle.SetEvent(event);
    mus_timeDirection_handle.SetEvent(event);
    mus_timeNumStationsUsed_handle.SetEvent(event);
    mus_trk_charge_handle.SetEvent(event);
    mus_trkidx_handle.SetEvent(event);
    mus_type_handle.SetEvent(event);
    mus_validHits_handle.SetEvent(event);
    pfcands_charge_handle.SetEvent(event);
    pfcands_flag_handle.SetEvent(event);
    pfcands_particleId_handle.SetEvent(event);
    pfcands_pfelsidx_handle.SetEvent(event);
    pfcands_pfmusidx_handle.SetEvent(event);
    pfcands_trkidx_handle.SetEvent(event);
    pfcands_vtxidx_handle.SetEvent(event);
    pfels_elsidx_handle.SetEvent(event);
    pfels_charge_handle.SetEvent(event);
    pfels_flag_handle.SetEvent(event);
    pfels_particleId_handle.SetEvent(event);
    pfjets_chargedHadronMultiplicity_handle.SetEvent(event);
    pfjets_chargedMultiplicity_handle.SetEvent(event);
    pfjets_electronMultiplicity_handle.SetEvent(event);
    pfjets_hfEmMultiplicity_handle.SetEvent(event);
    pfjets_hfHadronMultiplicity_handle.SetEvent(event);
    pfjets_muonMultiplicity_handle.SetEvent(event);
    pfjets_neutralHadronMultiplicity_handle.SetEvent(event);
    pfjets_neutralMultiplicity_handle.SetEvent(event);
    pfjets_photonMultiplicity_handle.SetEvent(event);
    pfmus_musidx_handle.SetEvent(event);
    pfmus_charge_handle.SetEvent(event);
    pfmus_flag_handle.SetEvent(event);
    pfmus_particleId_handle.SetEvent(event);
    taus_pf_charge_handle.SetEvent(event);
    taus_pf_pfjetIndex_handle.SetEvent(event);
    photons_fiduciality_handle.SetEvent(event);
    photons_scindex_handle.SetEvent(event);
    puInfo_bunchCrossing_handle.SetEvent(event);
    puInfo_nPUvertices_handle.SetEvent(event);
    convs_algo_handle.SetEvent(event);
    convs_isConverted_handle.SetEvent(event);
    convs_quality_handle.SetEvent(event);
    scs_detIdSeed_handle.SetEvent(event);
    scs_elsidx_handle.SetEvent(event);
    scs_severitySeed_handle.SetEvent(event);
    svs_isKs_handle.SetEvent(event);
    svs_isLambda_handle.SetEvent(event);
    svs_mc3_id_handle.SetEvent(event);
    svs_nTrks_handle.SetEvent(event);
    mus_tcmet_flag_handle.SetEvent(event);
    trks_algo_handle.SetEvent(event);
    trks_charge_handle.SetEvent(event);
    trks_exp_innerlayers_handle.SetEvent(event);
    trks_exp_outerlayers_handle.SetEvent(event);
    trks_layer1_det_handle.SetEvent(event);
    trks_layer1_layer_handle.SetEvent(event);
    trks_layer1_sizerphi_handle.SetEvent(event);
    trks_layer1_sizerz_handle.SetEvent(event);
    trks_lostHits_handle.SetEvent(event);
    trks_lost_pixelhits_handle.SetEvent(event);
    trks_nLoops_handle.SetEvent(event);
    trks_nlayers_handle.SetEvent(event);
    trks_nlayers3D_handle.SetEvent(event);
    trks_nlayersLost_handle.SetEvent(event);
    trks_pvidx0_handle.SetEvent(event);
    trks_pvidx1_handle.SetEvent(event);
    trks_qualityMask_handle.SetEvent(event);
    trks_validHits_handle.SetEvent(event);
    trks_valid_pixelhits_handle.SetEvent(event);
    trks_elsidx_handle.SetEvent(event);
    trk_musidx_handle.SetEvent(event);
    trkjets_ntrks_handle.SetEvent(event);
    trkjets_vtxs_idx_handle.SetEvent(event);
    vtxs_isFake_handle.SetEvent(event);
    vtxs_isValid_handle.SetEvent(event);
    vtxs_tracksSize_handle.SetEvent(event);
    bsvtxs_isFake_handle.SetEvent(event);
    bsvtxs_isValid_handle.SetEvent(event);
    bsvtxs_tracksSize_handle.SetEvent(event);
    els_convs_delMissHits_handle.SetEvent(event);
    els_convs_flag_handle.SetEvent(event);
    els_convs_gsftkidx_handle.SetEvent(event);
    els_convs_tkidx_handle.SetEvent(event);
    genps_lepdaughter_id_handle.SetEvent(event);
    genps_lepdaughter_idx_handle.SetEvent(event);
    hlt_trigObjs_id_handle.SetEvent(event);
    hyp_jets_idx_handle.SetEvent(event);
    hyp_other_jets_idx_handle.SetEvent(event);
    mus_nStationCorrelatedHits_handle.SetEvent(event);
    mus_nStationHits_handle.SetEvent(event);
    pfjets_pfcandIndicies_handle.SetEvent(event);
    taus_pf_pfcandIndicies_handle.SetEvent(event);
    puInfo_ntrks_highpt_handle.SetEvent(event);
    puInfo_ntrks_lowpt_handle.SetEvent(event);
    convs_nHitsBeforeVtx_handle.SetEvent(event);
    convs_tkalgo_handle.SetEvent(event);
    convs_tkidx_handle.SetEvent(event);
    els_HLT_Ele17_Ele8_L1sL1DoubleEG137_version_handle.SetEvent(event);
    els_HLT_Ele17_Ele8_LeadingLeg_version_handle.SetEvent(event);
    els_HLT_Ele17_Ele8_Mass50_LeadingLeg_version_handle.SetEvent(event);
    els_HLT_Ele17_Ele8_Mass50_TrailingLeg_version_handle.SetEvent(event);
    els_HLT_Ele17_Ele8_TrailingLeg_version_handle.SetEvent(event);
    els_HLT_Ele17_Ele8_version_handle.SetEvent(event);
    els_HLT_Ele20_SC4_Mass50_LeadingLeg_version_handle.SetEvent(event);
    els_HLT_Ele20_SC4_Mass50_TrailingLeg_version_handle.SetEvent(event);
    els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_version_handle.SetEvent(event);
    els_HLT_Ele27_WP80_version_handle.SetEvent(event);
    els_HLT_Ele32_SC17_Mass50_LeadingLeg_version_handle.SetEvent(event);
    els_HLT_Ele32_SC17_Mass50_TrailingLeg_version_handle.SetEvent(event);
    els_HLT_Mu17_Ele8_TrailingLeg_version_handle.SetEvent(event);
    els_HLT_Mu17_Ele8_version_handle.SetEvent(event);
    els_HLT_Mu8_Ele17_version_handle.SetEvent(event);
    evt_nels_handle.SetEvent(event);
    evt_detectorStatus_handle.SetEvent(event);
    evt_event_handle.SetEvent(event);
    evt_lumiBlock_handle.SetEvent(event);
    evt_run_handle.SetEvent(event);
    genps_flavorHistoryFilterResult_handle.SetEvent(event);
    evt_ngenjets_handle.SetEvent(event);
    genps_signalProcessID_handle.SetEvent(event);
    evt_njets_handle.SetEvent(event);
    l1_bits1_handle.SetEvent(event);
    l1_bits2_handle.SetEvent(event);
    l1_bits3_handle.SetEvent(event);
    l1_bits4_handle.SetEvent(event);
    l1_techbits1_handle.SetEvent(event);
    l1_techbits2_handle.SetEvent(event);
    ls_lsNumber_handle.SetEvent(event);
    ls_numOrbit_handle.SetEvent(event);
    ls_startOrbit_handle.SetEvent(event);
    mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_version_handle.SetEvent(event);
    mus_HLT_IsoMu24_eta2p1_version_handle.SetEvent(event);
    mus_HLT_Mu17_Ele8_LeadingLeg_version_handle.SetEvent(event);
    mus_HLT_Mu17_Ele8_version_handle.SetEvent(event);
    mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_version_handle.SetEvent(event);
    mus_HLT_Mu17_Mu8_LeadingLeg_version_handle.SetEvent(event);
    mus_HLT_Mu17_Mu8_TrailingLeg_version_handle.SetEvent(event);
    mus_HLT_Mu17_Mu8_version_handle.SetEvent(event);
    mus_HLT_Mu17_TkMu8_LeadingLeg_version_handle.SetEvent(event);
    mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_version_handle.SetEvent(event);
    mus_HLT_Mu17_TkMu8_TrailingLeg_version_handle.SetEvent(event);
    mus_HLT_Mu17_TkMu8_version_handle.SetEvent(event);
    mus_HLT_Mu8_Ele17_TrailingLeg_version_handle.SetEvent(event);
    mus_HLT_Mu8_Ele17_version_handle.SetEvent(event);
    evt_nphotons_handle.SetEvent(event);
    evt_ecalRecoStatus_handle.SetEvent(event);
    evt_nscs_handle.SetEvent(event);
    evt_ntrkjets_handle.SetEvent(event);
    evt_nvtxs_handle.SetEvent(event);
    evt_nbsvtxs_handle.SetEvent(event);
    els_HLT_Ele17_Ele8_handle.SetEvent(event);
    els_HLT_Ele17_Ele8_L1sL1DoubleEG137_handle.SetEvent(event);
    els_HLT_Ele17_Ele8_LeadingLeg_handle.SetEvent(event);
    els_HLT_Ele17_Ele8_Mass50_LeadingLeg_handle.SetEvent(event);
    els_HLT_Ele17_Ele8_Mass50_TrailingLeg_handle.SetEvent(event);
    els_HLT_Ele17_Ele8_TrailingLeg_handle.SetEvent(event);
    els_HLT_Ele20_SC4_Mass50_LeadingLeg_handle.SetEvent(event);
    els_HLT_Ele20_SC4_Mass50_TrailingLeg_handle.SetEvent(event);
    els_HLT_Ele27_WP80_handle.SetEvent(event);
    els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_handle.SetEvent(event);
    els_HLT_Ele32_SC17_Mass50_LeadingLeg_handle.SetEvent(event);
    els_HLT_Ele32_SC17_Mass50_TrailingLeg_handle.SetEvent(event);
    els_HLT_Mu17_Ele8_handle.SetEvent(event);
    els_HLT_Mu17_Ele8_TrailingLeg_handle.SetEvent(event);
    els_HLT_Mu8_Ele17_handle.SetEvent(event);
    els_id2012ext_loose_handle.SetEvent(event);
    els_id2012ext_medium_handle.SetEvent(event);
    els_id2012ext_tight_handle.SetEvent(event);
    els_id2012ext_veto_handle.SetEvent(event);
    els_id2012_loose_handle.SetEvent(event);
    els_id2012_medium_handle.SetEvent(event);
    els_id2012_tight_handle.SetEvent(event);
    els_id2012_veto_handle.SetEvent(event);
    hlt_prescales_handle.SetEvent(event);
    l1_prescales_handle.SetEvent(event);
    l1_techtrigprescales_handle.SetEvent(event);
    mus_HLT_IsoMu24_eta2p1_handle.SetEvent(event);
    mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_handle.SetEvent(event);
    mus_HLT_Mu17_Ele8_handle.SetEvent(event);
    mus_HLT_Mu17_Ele8_LeadingLeg_handle.SetEvent(event);
    mus_HLT_Mu17_Mu8_handle.SetEvent(event);
    mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_handle.SetEvent(event);
    mus_HLT_Mu17_Mu8_LeadingLeg_handle.SetEvent(event);
    mus_HLT_Mu17_Mu8_TrailingLeg_handle.SetEvent(event);
    mus_HLT_Mu17_TkMu8_handle.SetEvent(event);
    mus_HLT_Mu17_TkMu8_LeadingLeg_handle.SetEvent(event);
    mus_HLT_Mu17_TkMu8_TrailingLeg_handle.SetEvent(event);
    mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_handle.SetEvent(event);
    mus_HLT_Mu8_Ele17_handle.SetEvent(event);
    mus_HLT_Mu8_Ele17_TrailingLeg_handle.SetEvent(event);
    evt_timestamp_handle.SetEvent(event);

}

// trigger methods:
bool CMS2::passHLTTrigger(const TString& trigName)
{
    int trigIndx;
    std::vector<TString>::const_iterator begin_it = hlt_trigNames().begin();
    std::vector<TString>::const_iterator end_it = hlt_trigNames().end();
    std::vector<TString>::const_iterator found_it = find(begin_it, end_it, trigName);
    if(found_it != end_it)
    {
        trigIndx = found_it - begin_it;
    }
    else
    {
        std::cout << "Cannot find Trigger " << trigName << std::endl; 
        return false;
    }
    return hlt_bits().TestBitNumber(trigIndx);
}

bool CMS2::passL1Trigger(const TString& trigName)
{
    int trigIndx;
    std::vector<TString>::const_iterator begin_it = l1_trigNames().begin();
    std::vector<TString>::const_iterator end_it = l1_trigNames().end();
    std::vector<TString>::const_iterator found_it = find(begin_it, end_it, trigName);
    if(found_it != end_it)
    {
        trigIndx = found_it - begin_it;
    }
    else 
    {
        std::cout << "Cannot find Trigger " << trigName << std::endl; 
        return false;
    }

    if (trigIndx <= 31)
    {
        unsigned int bitmask = 1;
        bitmask <<= trigIndx;
        return l1_bits1() & bitmask;
    }
    if (trigIndx >= 32 && trigIndx <= 63)
    {
        unsigned int bitmask = 1;
        bitmask <<= (trigIndx - 32); 
        return l1_bits2() & bitmask;
    }
    if (trigIndx >= 64 && trigIndx <= 95)
    {
        unsigned int bitmask = 1;
        bitmask <<= (trigIndx - 64); 
        return l1_bits3() & bitmask;
    }
    if (trigIndx >= 96 && trigIndx <= 127) 
    {
        unsigned int bitmask = 1;
        bitmask <<= (trigIndx - 96); 
        return l1_bits4() & bitmask;
    }
    return false;
}


/*static*/ void CMS2::progress(const int nEventsTotal, const int nEventsChain)
{
    int period = 1000;
    if (nEventsTotal%1000 == 0)
    {
        // xterm magic from L. Vacavant and A. Cerri
        if (isatty(1))
        {
            if ((nEventsChain - nEventsTotal) > period)
            {
                float frac = (float)nEventsTotal/(nEventsChain*0.01);
                printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%\033[0m\033[32m <---\033[0m\015", frac);
                fflush(stdout);
            }
            else
            {
                printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%\033[0m\033[32m <---\033[0m\015", 100.0);
                std::cout << std::endl;
            }
        }
    }
}


// public interface implementation
// ---------------------------------------------------------------------------------------------- //
 
// branch accessor methods:
const TBits& CMS2::hlt_bits() {return hlt_bits_handle.get();}
const std::vector<TString>& CMS2::evt_CMS2tag() {return evt_CMS2tag_handle.get();}
const std::vector<TString>& CMS2::evt_dataset() {return evt_dataset_handle.get();}
const std::vector<TString>& CMS2::hlt_trigNames() {return hlt_trigNames_handle.get();}
const std::vector<TString>& CMS2::l1_techtrigNames() {return l1_techtrigNames_handle.get();}
const std::vector<TString>& CMS2::l1_trigNames() {return l1_trigNames_handle.get();}
const std::vector<TString>& CMS2::evt_errCategory() {return evt_errCategory_handle.get();}
const std::vector<TString>& CMS2::evt_errModule() {return evt_errModule_handle.get();}
const std::vector<TString>& CMS2::evt_errSeverity() {return evt_errSeverity_handle.get();}
const std::vector<TString>& CMS2::sparm_comment() {return sparm_comment_handle.get();}
const std::vector<TString>& CMS2::sparm_names() {return sparm_names_handle.get();}
const bool& CMS2::evt_eventHasHalo() {return evt_eventHasHalo_handle.get();}
const bool& CMS2::hcalnoise_HasBadRBXTS4TS5() {return hcalnoise_HasBadRBXTS4TS5_handle.get();}
const bool& CMS2::ls_isValid() {return ls_isValid_handle.get();}
const bool& CMS2::filt_ecalBE() {return filt_ecalBE_handle.get();}
const bool& CMS2::filt_ecalDR() {return filt_ecalDR_handle.get();}
const bool& CMS2::filt_ecalLaser() {return filt_ecalLaser_handle.get();}
const bool& CMS2::filt_ecalTP() {return filt_ecalTP_handle.get();}
const bool& CMS2::filt_eeBadSc() {return filt_eeBadSc_handle.get();}
const bool& CMS2::filt_greedyMuon() {return filt_greedyMuon_handle.get();}
const bool& CMS2::filt_hcalLaser() {return filt_hcalLaser_handle.get();}
const bool& CMS2::filt_inconsistentMuon() {return filt_inconsistentMuon_handle.get();}
const bool& CMS2::filt_jetIDFailure() {return filt_jetIDFailure_handle.get();}
const bool& CMS2::filt_multiEvent() {return filt_multiEvent_handle.get();}
const bool& CMS2::filt_trackingFailure() {return filt_trackingFailure_handle.get();}
const bool& CMS2::evt_hbheFilter() {return evt_hbheFilter_handle.get();}
const std::vector<bool>& CMS2::els_conv_vtx_flag() {return els_conv_vtx_flag_handle.get();}
const std::vector<bool>& CMS2::els_passingMvaPreselection() {return els_passingMvaPreselection_handle.get();}
const std::vector<bool>& CMS2::els_passingPflowPreselection() {return els_passingPflowPreselection_handle.get();}
const std::vector<bool>& CMS2::mus_isRPCMuon() {return mus_isRPCMuon_handle.get();}
const std::vector<bool>& CMS2::mus_tightMatch() {return mus_tightMatch_handle.get();}
const std::vector<bool>& CMS2::mus_updatedSta() {return mus_updatedSta_handle.get();}
const std::vector<bool>& CMS2::pfcands_isMuIso() {return pfcands_isMuIso_handle.get();}
const std::vector<bool>& CMS2::photons_haspixelSeed() {return photons_haspixelSeed_handle.get();}
const std::vector<double>& CMS2::jets_closestElectron_DR() {return jets_closestElectron_DR_handle.get();}
const std::vector<double>& CMS2::jets_closestMuon_DR() {return jets_closestMuon_DR_handle.get();}
const float& CMS2::evt_bs_Xwidth() {return evt_bs_Xwidth_handle.get();}
const float& CMS2::evt_bs_XwidthErr() {return evt_bs_XwidthErr_handle.get();}
const float& CMS2::evt_bs_Ywidth() {return evt_bs_Ywidth_handle.get();}
const float& CMS2::evt_bs_YwidthErr() {return evt_bs_YwidthErr_handle.get();}
const float& CMS2::evt_bs_dxdz() {return evt_bs_dxdz_handle.get();}
const float& CMS2::evt_bs_dxdzErr() {return evt_bs_dxdzErr_handle.get();}
const float& CMS2::evt_bs_dydz() {return evt_bs_dydz_handle.get();}
const float& CMS2::evt_bs_dydzErr() {return evt_bs_dydzErr_handle.get();}
const float& CMS2::evt_bs_sigmaZ() {return evt_bs_sigmaZ_handle.get();}
const float& CMS2::evt_bs_sigmaZErr() {return evt_bs_sigmaZErr_handle.get();}
const float& CMS2::evt_bs_xErr() {return evt_bs_xErr_handle.get();}
const float& CMS2::evt_bs_yErr() {return evt_bs_yErr_handle.get();}
const float& CMS2::evt_bs_zErr() {return evt_bs_zErr_handle.get();}
const float& CMS2::evt_bField() {return evt_bField_handle.get();}
const float& CMS2::evt_rho() {return evt_rho_handle.get();}
const float& CMS2::evt_rhoJEC() {return evt_rhoJEC_handle.get();}
const float& CMS2::evt_fixgrid_all_rho() {return evt_fixgrid_all_rho_handle.get();}
const float& CMS2::evt_fixgridfastjet_all_rho() {return evt_fixgridfastjet_all_rho_handle.get();}
const float& CMS2::gen_met() {return gen_met_handle.get();}
const float& CMS2::gen_metPhi() {return gen_metPhi_handle.get();}
const float& CMS2::genps_alphaQCD() {return genps_alphaQCD_handle.get();}
const float& CMS2::genps_pthat() {return genps_pthat_handle.get();}
const float& CMS2::genps_qScale() {return genps_qScale_handle.get();}
const float& CMS2::genps_weight() {return genps_weight_handle.get();}
const float& CMS2::gen_sumEt() {return gen_sumEt_handle.get();}
const float& CMS2::hcalnoise_GetRecHitEnergy() {return hcalnoise_GetRecHitEnergy_handle.get();}
const float& CMS2::hcalnoise_GetRecHitEnergy15() {return hcalnoise_GetRecHitEnergy15_handle.get();}
const float& CMS2::hcalnoise_GetTotalCalibCharge() {return hcalnoise_GetTotalCalibCharge_handle.get();}
const float& CMS2::hcalnoise_TS4TS5NoiseSumE() {return hcalnoise_TS4TS5NoiseSumE_handle.get();}
const float& CMS2::hcalnoise_TS4TS5NoiseSumEt() {return hcalnoise_TS4TS5NoiseSumEt_handle.get();}
const float& CMS2::hcalnoise_eventChargeFraction() {return hcalnoise_eventChargeFraction_handle.get();}
const float& CMS2::hcalnoise_eventEMEnergy() {return hcalnoise_eventEMEnergy_handle.get();}
const float& CMS2::hcalnoise_eventEMFraction() {return hcalnoise_eventEMFraction_handle.get();}
const float& CMS2::hcalnoise_eventHadEnergy() {return hcalnoise_eventHadEnergy_handle.get();}
const float& CMS2::hcalnoise_eventTrackEnergy() {return hcalnoise_eventTrackEnergy_handle.get();}
const float& CMS2::hcalnoise_flatNoiseSumE() {return hcalnoise_flatNoiseSumE_handle.get();}
const float& CMS2::hcalnoise_flatNoiseSumEt() {return hcalnoise_flatNoiseSumEt_handle.get();}
const float& CMS2::hcalnoise_isolatedNoiseSumE() {return hcalnoise_isolatedNoiseSumE_handle.get();}
const float& CMS2::hcalnoise_isolatedNoiseSumEt() {return hcalnoise_isolatedNoiseSumEt_handle.get();}
const float& CMS2::hcalnoise_max10GeVHitTime() {return hcalnoise_max10GeVHitTime_handle.get();}
const float& CMS2::hcalnoise_max25GeVHitTime() {return hcalnoise_max25GeVHitTime_handle.get();}
const float& CMS2::hcalnoise_maxE10TS() {return hcalnoise_maxE10TS_handle.get();}
const float& CMS2::hcalnoise_maxE2Over10TS() {return hcalnoise_maxE2Over10TS_handle.get();}
const float& CMS2::hcalnoise_maxE2TS() {return hcalnoise_maxE2TS_handle.get();}
const float& CMS2::hcalnoise_min10GeVHitTime() {return hcalnoise_min10GeVHitTime_handle.get();}
const float& CMS2::hcalnoise_min25GeVHitTime() {return hcalnoise_min25GeVHitTime_handle.get();}
const float& CMS2::hcalnoise_minE10TS() {return hcalnoise_minE10TS_handle.get();}
const float& CMS2::hcalnoise_minE2Over10TS() {return hcalnoise_minE2Over10TS_handle.get();}
const float& CMS2::hcalnoise_minE2TS() {return hcalnoise_minE2TS_handle.get();}
const float& CMS2::hcalnoise_minHPDEMF() {return hcalnoise_minHPDEMF_handle.get();}
const float& CMS2::hcalnoise_minRBXEMF() {return hcalnoise_minRBXEMF_handle.get();}
const float& CMS2::hcalnoise_rms10GeVHitTime() {return hcalnoise_rms10GeVHitTime_handle.get();}
const float& CMS2::hcalnoise_rms25GeVHitTime() {return hcalnoise_rms25GeVHitTime_handle.get();}
const float& CMS2::hcalnoise_spikeNoiseSumE() {return hcalnoise_spikeNoiseSumE_handle.get();}
const float& CMS2::hcalnoise_spikeNoiseSumEt() {return hcalnoise_spikeNoiseSumEt_handle.get();}
const float& CMS2::hcalnoise_triangleNoiseSumE() {return hcalnoise_triangleNoiseSumE_handle.get();}
const float& CMS2::hcalnoise_triangleNoiseSumEt() {return hcalnoise_triangleNoiseSumEt_handle.get();}
const float& CMS2::evt_kt6calo_central_rho() {return evt_kt6calo_central_rho_handle.get();}
const float& CMS2::evt_kt6calo_muhlt_rho() {return evt_kt6calo_muhlt_rho_handle.get();}
const float& CMS2::evt_kt6calo_rho() {return evt_kt6calo_rho_handle.get();}
const float& CMS2::evt_kt6pf_ctrChargedPU_rho() {return evt_kt6pf_ctrChargedPU_rho_handle.get();}
const float& CMS2::evt_kt6pf_ctrNeutral_rho() {return evt_kt6pf_ctrNeutral_rho_handle.get();}
const float& CMS2::evt_kt6pf_ctrNeutralTight_rho() {return evt_kt6pf_ctrNeutralTight_rho_handle.get();}
const float& CMS2::evt_kt6pf_foregiso_rho() {return evt_kt6pf_foregiso_rho_handle.get();}
const float& CMS2::l1_met_etTot() {return l1_met_etTot_handle.get();}
const float& CMS2::l1_met_met() {return l1_met_met_handle.get();}
const float& CMS2::l1_mht_htTot() {return l1_mht_htTot_handle.get();}
const float& CMS2::l1_mht_mht() {return l1_mht_mht_handle.get();}
const float& CMS2::ls_avgInsDelLumi() {return ls_avgInsDelLumi_handle.get();}
const float& CMS2::ls_avgInsDelLumiErr() {return ls_avgInsDelLumiErr_handle.get();}
const float& CMS2::ls_avgInsRecLumi() {return ls_avgInsRecLumi_handle.get();}
const float& CMS2::ls_avgInsRecLumiErr() {return ls_avgInsRecLumiErr_handle.get();}
const float& CMS2::ls_deadFrac() {return ls_deadFrac_handle.get();}
const float& CMS2::ls_intgDelLumi() {return ls_intgDelLumi_handle.get();}
const float& CMS2::ls_intgRecLumi() {return ls_intgRecLumi_handle.get();}
const float& CMS2::ls_lumiSectionLength() {return ls_lumiSectionLength_handle.get();}
const float& CMS2::evt_ecalendcapm_met() {return evt_ecalendcapm_met_handle.get();}
const float& CMS2::evt_ecalendcapm_metPhi() {return evt_ecalendcapm_metPhi_handle.get();}
const float& CMS2::evt_ecalendcapp_met() {return evt_ecalendcapp_met_handle.get();}
const float& CMS2::evt_ecalendcapp_metPhi() {return evt_ecalendcapp_metPhi_handle.get();}
const float& CMS2::evt_ecalmet() {return evt_ecalmet_handle.get();}
const float& CMS2::evt_ecalmetPhi() {return evt_ecalmetPhi_handle.get();}
const float& CMS2::evt_endcapm_met() {return evt_endcapm_met_handle.get();}
const float& CMS2::evt_endcapm_metPhi() {return evt_endcapm_metPhi_handle.get();}
const float& CMS2::evt_endcapp_met() {return evt_endcapp_met_handle.get();}
const float& CMS2::evt_endcapp_metPhi() {return evt_endcapp_metPhi_handle.get();}
const float& CMS2::evt_hcalendcapm_met() {return evt_hcalendcapm_met_handle.get();}
const float& CMS2::evt_hcalendcapm_metPhi() {return evt_hcalendcapm_metPhi_handle.get();}
const float& CMS2::evt_hcalendcapp_met() {return evt_hcalendcapp_met_handle.get();}
const float& CMS2::evt_hcalendcapp_metPhi() {return evt_hcalendcapp_metPhi_handle.get();}
const float& CMS2::evt_hcalmet() {return evt_hcalmet_handle.get();}
const float& CMS2::evt_hcalmetPhi() {return evt_hcalmetPhi_handle.get();}
const float& CMS2::evt_met() {return evt_met_handle.get();}
const float& CMS2::evt_met_EtGt3() {return evt_met_EtGt3_handle.get();}
const float& CMS2::evt_metHO() {return evt_metHO_handle.get();}
const float& CMS2::evt_metHOPhi() {return evt_metHOPhi_handle.get();}
const float& CMS2::evt_metHOSig() {return evt_metHOSig_handle.get();}
const float& CMS2::evt_metMuonCorr() {return evt_metMuonCorr_handle.get();}
const float& CMS2::evt_metMuonCorrPhi() {return evt_metMuonCorrPhi_handle.get();}
const float& CMS2::evt_metMuonCorrSig() {return evt_metMuonCorrSig_handle.get();}
const float& CMS2::evt_metMuonJESCorr() {return evt_metMuonJESCorr_handle.get();}
const float& CMS2::evt_metMuonJESCorrPhi() {return evt_metMuonJESCorrPhi_handle.get();}
const float& CMS2::evt_metMuonJESCorrSig() {return evt_metMuonJESCorrSig_handle.get();}
const float& CMS2::evt_metNoHF() {return evt_metNoHF_handle.get();}
const float& CMS2::evt_metNoHFHO() {return evt_metNoHFHO_handle.get();}
const float& CMS2::evt_metNoHFHOPhi() {return evt_metNoHFHOPhi_handle.get();}
const float& CMS2::evt_metNoHFHOSig() {return evt_metNoHFHOSig_handle.get();}
const float& CMS2::evt_metNoHFPhi() {return evt_metNoHFPhi_handle.get();}
const float& CMS2::evt_metNoHFSig() {return evt_metNoHFSig_handle.get();}
const float& CMS2::evt_metOpt() {return evt_metOpt_handle.get();}
const float& CMS2::evt_metOptHO() {return evt_metOptHO_handle.get();}
const float& CMS2::evt_metOptHOPhi() {return evt_metOptHOPhi_handle.get();}
const float& CMS2::evt_metOptHOSig() {return evt_metOptHOSig_handle.get();}
const float& CMS2::evt_metOptNoHF() {return evt_metOptNoHF_handle.get();}
const float& CMS2::evt_metOptNoHFHO() {return evt_metOptNoHFHO_handle.get();}
const float& CMS2::evt_metOptNoHFHOPhi() {return evt_metOptNoHFHOPhi_handle.get();}
const float& CMS2::evt_metOptNoHFHOSig() {return evt_metOptNoHFHOSig_handle.get();}
const float& CMS2::evt_metOptNoHFPhi() {return evt_metOptNoHFPhi_handle.get();}
const float& CMS2::evt_metOptNoHFSig() {return evt_metOptNoHFSig_handle.get();}
const float& CMS2::evt_metOptPhi() {return evt_metOptPhi_handle.get();}
const float& CMS2::evt_metOptSig() {return evt_metOptSig_handle.get();}
const float& CMS2::evt_metPhi() {return evt_metPhi_handle.get();}
const float& CMS2::evt_metPhi_EtGt3() {return evt_metPhi_EtGt3_handle.get();}
const float& CMS2::evt_metSig() {return evt_metSig_handle.get();}
const float& CMS2::evt_sumet() {return evt_sumet_handle.get();}
const float& CMS2::evt_sumet_EtGt3() {return evt_sumet_EtGt3_handle.get();}
const float& CMS2::evt_sumetHO() {return evt_sumetHO_handle.get();}
const float& CMS2::evt_sumetMuonCorr() {return evt_sumetMuonCorr_handle.get();}
const float& CMS2::evt_sumetMuonJESCorr() {return evt_sumetMuonJESCorr_handle.get();}
const float& CMS2::evt_sumetNoHF() {return evt_sumetNoHF_handle.get();}
const float& CMS2::evt_sumetNoHFHO() {return evt_sumetNoHFHO_handle.get();}
const float& CMS2::evt_sumetOpt() {return evt_sumetOpt_handle.get();}
const float& CMS2::evt_sumetOptHO() {return evt_sumetOptHO_handle.get();}
const float& CMS2::evt_sumetOptNoHF() {return evt_sumetOptNoHF_handle.get();}
const float& CMS2::evt_sumetOptNoHFHO() {return evt_sumetOptNoHFHO_handle.get();}
const float& CMS2::pdfinfo_pdf1() {return pdfinfo_pdf1_handle.get();}
const float& CMS2::pdfinfo_pdf2() {return pdfinfo_pdf2_handle.get();}
const float& CMS2::pdfinfo_scale() {return pdfinfo_scale_handle.get();}
const float& CMS2::pdfinfo_x1() {return pdfinfo_x1_handle.get();}
const float& CMS2::pdfinfo_x2() {return pdfinfo_x2_handle.get();}
const float& CMS2::evt_fixgrid_rho_all() {return evt_fixgrid_rho_all_handle.get();}
const float& CMS2::evt_fixgrid_rho_ctr() {return evt_fixgrid_rho_ctr_handle.get();}
const float& CMS2::evt_fixgrid_rho_fwd() {return evt_fixgrid_rho_fwd_handle.get();}
const float& CMS2::evt_pfmet() {return evt_pfmet_handle.get();}
const float& CMS2::evt_pfmetPhi() {return evt_pfmetPhi_handle.get();}
const float& CMS2::evt_pfmetPhi_type1cor() {return evt_pfmetPhi_type1cor_handle.get();}
const float& CMS2::evt_pfmetSig() {return evt_pfmetSig_handle.get();}
const float& CMS2::evt_pfmetSignificance() {return evt_pfmetSignificance_handle.get();}
const float& CMS2::evt_pfmet_type1cor() {return evt_pfmet_type1cor_handle.get();}
const float& CMS2::evt_pfsumet() {return evt_pfsumet_handle.get();}
const float& CMS2::sparm_filterEfficiency() {return sparm_filterEfficiency_handle.get();}
const float& CMS2::sparm_pdfScale() {return sparm_pdfScale_handle.get();}
const float& CMS2::sparm_pdfWeight1() {return sparm_pdfWeight1_handle.get();}
const float& CMS2::sparm_pdfWeight2() {return sparm_pdfWeight2_handle.get();}
const float& CMS2::sparm_weight() {return sparm_weight_handle.get();}
const float& CMS2::sparm_xsec() {return sparm_xsec_handle.get();}
const float& CMS2::evt_pf_tcmet() {return evt_pf_tcmet_handle.get();}
const float& CMS2::evt_pf_tcmetPhi() {return evt_pf_tcmetPhi_handle.get();}
const float& CMS2::evt_pf_tcmetSig() {return evt_pf_tcmetSig_handle.get();}
const float& CMS2::evt_pf_tcsumet() {return evt_pf_tcsumet_handle.get();}
const float& CMS2::evt_tcmet() {return evt_tcmet_handle.get();}
const float& CMS2::evt_tcmetPhi() {return evt_tcmetPhi_handle.get();}
const float& CMS2::evt_tcmetSig() {return evt_tcmetSig_handle.get();}
const float& CMS2::evt_tcsumet() {return evt_tcsumet_handle.get();}
const float& CMS2::evt_ww_rho_act() {return evt_ww_rho_act_handle.get();}
const float& CMS2::evt_ww_rho() {return evt_ww_rho_handle.get();}
const float& CMS2::evt_ww_rho_rnd() {return evt_ww_rho_rnd_handle.get();}
const float& CMS2::evt_ww_rho_vor() {return evt_ww_rho_vor_handle.get();}
const LorentzVector & CMS2::evt_bsp4() {return evt_bsp4_handle.get();}
const LorentzVector & CMS2::l1_met_p4() {return l1_met_p4_handle.get();}
const LorentzVector & CMS2::l1_mht_p4() {return l1_mht_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::els_mc_motherp4() {return els_mc_motherp4_handle.get();}
const std::vector<LorentzVector >& CMS2::els_mc_p4() {return els_mc_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::jets_mc_gp_p4() {return jets_mc_gp_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::jets_mc_motherp4() {return jets_mc_motherp4_handle.get();}
const std::vector<LorentzVector >& CMS2::jets_mc_p4() {return jets_mc_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_mc_motherp4() {return mus_mc_motherp4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_mc_p4() {return mus_mc_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::pfjets_mc_gp_p4() {return pfjets_mc_gp_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::pfjets_mc_motherp4() {return pfjets_mc_motherp4_handle.get();}
const std::vector<LorentzVector >& CMS2::pfjets_mc_p4() {return pfjets_mc_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::photons_mc_motherp4() {return photons_mc_motherp4_handle.get();}
const std::vector<LorentzVector >& CMS2::photons_mc_p4() {return photons_mc_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::trk_mcp4() {return trk_mcp4_handle.get();}
const std::vector<LorentzVector >& CMS2::els_conv_pos_p4() {return els_conv_pos_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::els_inner_position() {return els_inner_position_handle.get();}
const std::vector<LorentzVector >& CMS2::els_outer_position() {return els_outer_position_handle.get();}
const std::vector<LorentzVector >& CMS2::els_p4() {return els_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::els_p4In() {return els_p4In_handle.get();}
const std::vector<LorentzVector >& CMS2::els_p4Out() {return els_p4Out_handle.get();}
const std::vector<LorentzVector >& CMS2::els_trk_p4() {return els_trk_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::els_vertex_p4() {return els_vertex_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::genjets_p4() {return genjets_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::genps_p4() {return genps_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::genps_prod_vtx() {return genps_prod_vtx_handle.get();}
const std::vector<LorentzVector >& CMS2::gsftrks_inner_position() {return gsftrks_inner_position_handle.get();}
const std::vector<LorentzVector >& CMS2::gsftrks_outer_p4() {return gsftrks_outer_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::gsftrks_outer_position() {return gsftrks_outer_position_handle.get();}
const std::vector<LorentzVector >& CMS2::gsftrks_p4() {return gsftrks_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::gsftrks_vertex_p4() {return gsftrks_vertex_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::hyp_ll_p4() {return hyp_ll_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::hyp_ll_trk_p4() {return hyp_ll_trk_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::hyp_lt_p4() {return hyp_lt_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::hyp_lt_trk_p4() {return hyp_lt_trk_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::hyp_p4() {return hyp_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::hyp_FVFit_p4() {return hyp_FVFit_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::hyp_FVFit_v4() {return hyp_FVFit_v4_handle.get();}
const std::vector<LorentzVector >& CMS2::hyp_ll_mc_p4() {return hyp_ll_mc_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::hyp_lt_mc_p4() {return hyp_lt_mc_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::jets_p4() {return jets_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::jets_vertex_p4() {return jets_vertex_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::l1_emiso_p4() {return l1_emiso_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::l1_emnoiso_p4() {return l1_emnoiso_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::l1_jetsc_p4() {return l1_jetsc_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::l1_jetsf_p4() {return l1_jetsf_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::l1_jetst_p4() {return l1_jetst_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::l1_mus_p4() {return l1_mus_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_ecalpos_p4() {return mus_ecalpos_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_fitpicky_p4() {return mus_fitpicky_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_fittev_p4() {return mus_fittev_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_fittpfms_p4() {return mus_fittpfms_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_gfit_outerPos_p4() {return mus_gfit_outerPos_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_gfit_p4() {return mus_gfit_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_gfit_vertex_p4() {return mus_gfit_vertex_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_p4() {return mus_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_pfp4() {return mus_pfp4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_pfposAtEcal_p4() {return mus_pfposAtEcal_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_sta_p4() {return mus_sta_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_sta_vertex_p4() {return mus_sta_vertex_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_trk_p4() {return mus_trk_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::mus_vertex_p4() {return mus_vertex_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::pfcands_p4() {return pfcands_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::pfcands_posAtEcal_p4() {return pfcands_posAtEcal_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::pfels_p4() {return pfels_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::pfels_posAtEcal_p4() {return pfels_posAtEcal_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::pfjets_p4() {return pfjets_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::pfmus_p4() {return pfmus_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::pfmus_posAtEcal_p4() {return pfmus_posAtEcal_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::taus_pf_p4() {return taus_pf_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::photons_p4() {return photons_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::convs_refitPairMom_p4() {return convs_refitPairMom_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::convs_vtxpos() {return convs_vtxpos_handle.get();}
const std::vector<LorentzVector >& CMS2::scs_p4() {return scs_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::scs_pos_p4() {return scs_pos_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::scs_vtx_p4() {return scs_vtx_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::svs_flight() {return svs_flight_handle.get();}
const std::vector<LorentzVector >& CMS2::svs_mc3_p4() {return svs_mc3_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::svs_p4() {return svs_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::svs_position() {return svs_position_handle.get();}
const std::vector<LorentzVector >& CMS2::svs_refitp4() {return svs_refitp4_handle.get();}
const std::vector<LorentzVector >& CMS2::trks_inner_position() {return trks_inner_position_handle.get();}
const std::vector<LorentzVector >& CMS2::trks_outer_p4() {return trks_outer_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::trks_outer_position() {return trks_outer_position_handle.get();}
const std::vector<LorentzVector >& CMS2::trks_trk_p4() {return trks_trk_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::trks_vertex_p4() {return trks_vertex_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::trkjets_p4() {return trkjets_p4_handle.get();}
const std::vector<LorentzVector >& CMS2::vtxs_position() {return vtxs_position_handle.get();}
const std::vector<LorentzVector >& CMS2::bsvtxs_position() {return bsvtxs_position_handle.get();}
const std::vector<std::vector<LorentzVector > >& CMS2::els_convs_pos_p4() {return els_convs_pos_p4_handle.get();}
const std::vector<std::vector<LorentzVector > >& CMS2::genps_lepdaughter_p4() {return genps_lepdaughter_p4_handle.get();}
const std::vector<std::vector<LorentzVector > >& CMS2::hlt_trigObjs_p4() {return hlt_trigObjs_p4_handle.get();}
const std::vector<std::vector<LorentzVector > >& CMS2::hyp_jets_p4() {return hyp_jets_p4_handle.get();}
const std::vector<std::vector<LorentzVector > >& CMS2::hyp_other_jets_p4() {return hyp_other_jets_p4_handle.get();}
const std::vector<float>& CMS2::jpts_combinedSecondaryVertexBJetTag() {return jpts_combinedSecondaryVertexBJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_combinedSecondaryVertexMVABJetTag() {return jpts_combinedSecondaryVertexMVABJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_jetBProbabilityBJetTag() {return jpts_jetBProbabilityBJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_jetProbabilityBJetTag() {return jpts_jetProbabilityBJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_simpleSecondaryVertexBJetTag() {return jpts_simpleSecondaryVertexBJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_simpleSecondaryVertexHighEffBJetTag() {return jpts_simpleSecondaryVertexHighEffBJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_simpleSecondaryVertexHighPurBJetTags() {return jpts_simpleSecondaryVertexHighPurBJetTags_handle.get();}
const std::vector<float>& CMS2::jpts_softElectronByIP3dBJetTag() {return jpts_softElectronByIP3dBJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_softElectronByPtBJetTag() {return jpts_softElectronByPtBJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_softElectronTag() {return jpts_softElectronTag_handle.get();}
const std::vector<float>& CMS2::jpts_softMuonBJetTag() {return jpts_softMuonBJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_softMuonByIP3dBJetTag() {return jpts_softMuonByIP3dBJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_softMuonByPtBJetTag() {return jpts_softMuonByPtBJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_trackCountingHighEffBJetTag() {return jpts_trackCountingHighEffBJetTag_handle.get();}
const std::vector<float>& CMS2::jpts_trackCountingHighPurBJetTag() {return jpts_trackCountingHighPurBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_combinedSecondaryVertexBJetTag() {return jets_combinedSecondaryVertexBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_combinedSecondaryVertexMVABJetTag() {return jets_combinedSecondaryVertexMVABJetTag_handle.get();}
const std::vector<float>& CMS2::jets_jetBProbabilityBJetTag() {return jets_jetBProbabilityBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_jetProbabilityBJetTag() {return jets_jetProbabilityBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_simpleSecondaryVertexBJetTag() {return jets_simpleSecondaryVertexBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_simpleSecondaryVertexHighEffBJetTag() {return jets_simpleSecondaryVertexHighEffBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_simpleSecondaryVertexHighPurBJetTags() {return jets_simpleSecondaryVertexHighPurBJetTags_handle.get();}
const std::vector<float>& CMS2::jets_softElectronByIP3dBJetTag() {return jets_softElectronByIP3dBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_softElectronByPtBJetTag() {return jets_softElectronByPtBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_softElectronTag() {return jets_softElectronTag_handle.get();}
const std::vector<float>& CMS2::jets_softMuonBJetTag() {return jets_softMuonBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_softMuonByIP3dBJetTag() {return jets_softMuonByIP3dBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_softMuonByPtBJetTag() {return jets_softMuonByPtBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_trackCountingHighEffBJetTag() {return jets_trackCountingHighEffBJetTag_handle.get();}
const std::vector<float>& CMS2::jets_trackCountingHighPurBJetTag() {return jets_trackCountingHighPurBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_combinedSecondaryVertexBJetTag() {return pfjets_combinedSecondaryVertexBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_combinedSecondaryVertexMVABJetTag() {return pfjets_combinedSecondaryVertexMVABJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_jetBProbabilityBJetTag() {return pfjets_jetBProbabilityBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_jetProbabilityBJetTag() {return pfjets_jetProbabilityBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_simpleSecondaryVertexBJetTag() {return pfjets_simpleSecondaryVertexBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_simpleSecondaryVertexHighEffBJetTag() {return pfjets_simpleSecondaryVertexHighEffBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_simpleSecondaryVertexHighPurBJetTags() {return pfjets_simpleSecondaryVertexHighPurBJetTags_handle.get();}
const std::vector<float>& CMS2::pfjets_softElectronByIP3dBJetTag() {return pfjets_softElectronByIP3dBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_softElectronByPtBJetTag() {return pfjets_softElectronByPtBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_softElectronTag() {return pfjets_softElectronTag_handle.get();}
const std::vector<float>& CMS2::pfjets_softMuonBJetTag() {return pfjets_softMuonBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_softMuonByIP3dBJetTag() {return pfjets_softMuonByIP3dBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_softMuonByPtBJetTag() {return pfjets_softMuonByPtBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_trackCountingHighEffBJetTag() {return pfjets_trackCountingHighEffBJetTag_handle.get();}
const std::vector<float>& CMS2::pfjets_trackCountingHighPurBJetTag() {return pfjets_trackCountingHighPurBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_combinedSecondaryVertexBJetTag() {return trkjets_combinedSecondaryVertexBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_combinedSecondaryVertexMVABJetTag() {return trkjets_combinedSecondaryVertexMVABJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_jetBProbabilityBJetTag() {return trkjets_jetBProbabilityBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_jetProbabilityBJetTag() {return trkjets_jetProbabilityBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_simpleSecondaryVertexBJetTag() {return trkjets_simpleSecondaryVertexBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_simpleSecondaryVertexHighEffBJetTag() {return trkjets_simpleSecondaryVertexHighEffBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_simpleSecondaryVertexHighPurBJetTags() {return trkjets_simpleSecondaryVertexHighPurBJetTags_handle.get();}
const std::vector<float>& CMS2::trkjets_softElectronByIP3dBJetTag() {return trkjets_softElectronByIP3dBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_softElectronByPtBJetTag() {return trkjets_softElectronByPtBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_softElectronTag() {return trkjets_softElectronTag_handle.get();}
const std::vector<float>& CMS2::trkjets_softMuonBJetTag() {return trkjets_softMuonBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_softMuonByIP3dBJetTag() {return trkjets_softMuonByIP3dBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_softMuonByPtBJetTag() {return trkjets_softMuonByPtBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_trackCountingHighEffBJetTag() {return trkjets_trackCountingHighEffBJetTag_handle.get();}
const std::vector<float>& CMS2::trkjets_trackCountingHighPurBJetTag() {return trkjets_trackCountingHighPurBJetTag_handle.get();}
const std::vector<float>& CMS2::evt_bs_covMatrix() {return evt_bs_covMatrix_handle.get();}
const std::vector<float>& CMS2::els_mc3dr() {return els_mc3dr_handle.get();}
const std::vector<float>& CMS2::els_mcdr() {return els_mcdr_handle.get();}
const std::vector<float>& CMS2::jets_mc3dr() {return jets_mc3dr_handle.get();}
const std::vector<float>& CMS2::jets_mcdr() {return jets_mcdr_handle.get();}
const std::vector<float>& CMS2::jets_mc_emEnergy() {return jets_mc_emEnergy_handle.get();}
const std::vector<float>& CMS2::jets_mc_gpdr() {return jets_mc_gpdr_handle.get();}
const std::vector<float>& CMS2::jets_mc_hadEnergy() {return jets_mc_hadEnergy_handle.get();}
const std::vector<float>& CMS2::jets_mc_invEnergy() {return jets_mc_invEnergy_handle.get();}
const std::vector<float>& CMS2::jets_mc_otherEnergy() {return jets_mc_otherEnergy_handle.get();}
const std::vector<float>& CMS2::mus_mc3dr() {return mus_mc3dr_handle.get();}
const std::vector<float>& CMS2::mus_mcdr() {return mus_mcdr_handle.get();}
const std::vector<float>& CMS2::pfjets_mc3dr() {return pfjets_mc3dr_handle.get();}
const std::vector<float>& CMS2::pfjets_mcdr() {return pfjets_mcdr_handle.get();}
const std::vector<float>& CMS2::pfjets_mc_emEnergy() {return pfjets_mc_emEnergy_handle.get();}
const std::vector<float>& CMS2::pfjets_mc_gpdr() {return pfjets_mc_gpdr_handle.get();}
const std::vector<float>& CMS2::pfjets_mc_hadEnergy() {return pfjets_mc_hadEnergy_handle.get();}
const std::vector<float>& CMS2::pfjets_mc_invEnergy() {return pfjets_mc_invEnergy_handle.get();}
const std::vector<float>& CMS2::pfjets_mc_otherEnergy() {return pfjets_mc_otherEnergy_handle.get();}
const std::vector<float>& CMS2::photons_mc3dr() {return photons_mc3dr_handle.get();}
const std::vector<float>& CMS2::photons_mcdr() {return photons_mcdr_handle.get();}
const std::vector<float>& CMS2::trk_mc3dr() {return trk_mc3dr_handle.get();}
const std::vector<float>& CMS2::trk_mcdr() {return trk_mcdr_handle.get();}
const std::vector<float>& CMS2::els_ecalJuraIso() {return els_ecalJuraIso_handle.get();}
const std::vector<float>& CMS2::els_ecalJuraTowerIso() {return els_ecalJuraTowerIso_handle.get();}
const std::vector<float>& CMS2::els_hcalConeIso() {return els_hcalConeIso_handle.get();}
const std::vector<float>& CMS2::els_tkJuraIso() {return els_tkJuraIso_handle.get();}
const std::vector<float>& CMS2::els_jetdr() {return els_jetdr_handle.get();}
const std::vector<float>& CMS2::els_musdr() {return els_musdr_handle.get();}
const std::vector<float>& CMS2::els_isoR03_chpf_radial() {return els_isoR03_chpf_radial_handle.get();}
const std::vector<float>& CMS2::els_isoR03_chpf_radialTight() {return els_isoR03_chpf_radialTight_handle.get();}
const std::vector<float>& CMS2::els_isoR03_chpf_radialTight_bv() {return els_isoR03_chpf_radialTight_bv_handle.get();}
const std::vector<float>& CMS2::els_isoR03_chpf_radial_bv() {return els_isoR03_chpf_radial_bv_handle.get();}
const std::vector<float>& CMS2::els_isoR03_empf_radial() {return els_isoR03_empf_radial_handle.get();}
const std::vector<float>& CMS2::els_isoR03_empf_radialTight() {return els_isoR03_empf_radialTight_handle.get();}
const std::vector<float>& CMS2::els_isoR03_empf_radialTight_bv() {return els_isoR03_empf_radialTight_bv_handle.get();}
const std::vector<float>& CMS2::els_isoR03_empf_radial_bv() {return els_isoR03_empf_radial_bv_handle.get();}
const std::vector<float>& CMS2::els_isoR03_nhpf_radial() {return els_isoR03_nhpf_radial_handle.get();}
const std::vector<float>& CMS2::els_isoR03_nhpf_radialTight() {return els_isoR03_nhpf_radialTight_handle.get();}
const std::vector<float>& CMS2::els_isoR03_nhpf_radialTight_bv() {return els_isoR03_nhpf_radialTight_bv_handle.get();}
const std::vector<float>& CMS2::els_isoR03_nhpf_radial_bv() {return els_isoR03_nhpf_radial_bv_handle.get();}
const std::vector<float>& CMS2::els_isoR03_pf2012n0p5_ch() {return els_isoR03_pf2012n0p5_ch_handle.get();}
const std::vector<float>& CMS2::els_isoR03_pf2012n0p5_em() {return els_isoR03_pf2012n0p5_em_handle.get();}
const std::vector<float>& CMS2::els_isoR03_pf2012n0p5_nh() {return els_isoR03_pf2012n0p5_nh_handle.get();}
const std::vector<float>& CMS2::els_isoR03_pf_radial() {return els_isoR03_pf_radial_handle.get();}
const std::vector<float>& CMS2::els_isoR03_pf_radialTight() {return els_isoR03_pf_radialTight_handle.get();}
const std::vector<float>& CMS2::els_isoR03_pf_radialTight_bv() {return els_isoR03_pf_radialTight_bv_handle.get();}
const std::vector<float>& CMS2::els_isoR03_pf_radial_bv() {return els_isoR03_pf_radial_bv_handle.get();}
const std::vector<float>& CMS2::els_chi2() {return els_chi2_handle.get();}
const std::vector<float>& CMS2::els_ckf_chi2() {return els_ckf_chi2_handle.get();}
const std::vector<float>& CMS2::els_ckf_ndof() {return els_ckf_ndof_handle.get();}
const std::vector<float>& CMS2::els_conv_dcot() {return els_conv_dcot_handle.get();}
const std::vector<float>& CMS2::els_conv_dist() {return els_conv_dist_handle.get();}
const std::vector<float>& CMS2::els_conv_old_dcot() {return els_conv_old_dcot_handle.get();}
const std::vector<float>& CMS2::els_conv_old_dist() {return els_conv_old_dist_handle.get();}
const std::vector<float>& CMS2::els_conv_old_radius() {return els_conv_old_radius_handle.get();}
const std::vector<float>& CMS2::els_conv_radius() {return els_conv_radius_handle.get();}
const std::vector<float>& CMS2::els_d0() {return els_d0_handle.get();}
const std::vector<float>& CMS2::els_d0Err() {return els_d0Err_handle.get();}
const std::vector<float>& CMS2::els_d0corr() {return els_d0corr_handle.get();}
const std::vector<float>& CMS2::els_dEtaIn() {return els_dEtaIn_handle.get();}
const std::vector<float>& CMS2::els_dEtaOut() {return els_dEtaOut_handle.get();}
const std::vector<float>& CMS2::els_dPhiIn() {return els_dPhiIn_handle.get();}
const std::vector<float>& CMS2::els_dPhiInPhiOut() {return els_dPhiInPhiOut_handle.get();}
const std::vector<float>& CMS2::els_dPhiOut() {return els_dPhiOut_handle.get();}
const std::vector<float>& CMS2::els_deltaEtaEleClusterTrackAtCalo() {return els_deltaEtaEleClusterTrackAtCalo_handle.get();}
const std::vector<float>& CMS2::els_deltaPhiEleClusterTrackAtCalo() {return els_deltaPhiEleClusterTrackAtCalo_handle.get();}
const std::vector<float>& CMS2::els_e1x5() {return els_e1x5_handle.get();}
const std::vector<float>& CMS2::els_e2x5Max() {return els_e2x5Max_handle.get();}
const std::vector<float>& CMS2::els_e3x3() {return els_e3x3_handle.get();}
const std::vector<float>& CMS2::els_e5x5() {return els_e5x5_handle.get();}
const std::vector<float>& CMS2::els_eMax() {return els_eMax_handle.get();}
const std::vector<float>& CMS2::els_eOverPIn() {return els_eOverPIn_handle.get();}
const std::vector<float>& CMS2::els_eOverPOut() {return els_eOverPOut_handle.get();}
const std::vector<float>& CMS2::els_eSC() {return els_eSC_handle.get();}
const std::vector<float>& CMS2::els_eSCPresh() {return els_eSCPresh_handle.get();}
const std::vector<float>& CMS2::els_eSCRaw() {return els_eSCRaw_handle.get();}
const std::vector<float>& CMS2::els_eSeed() {return els_eSeed_handle.get();}
const std::vector<float>& CMS2::els_eSeedOverPIn() {return els_eSeedOverPIn_handle.get();}
const std::vector<float>& CMS2::els_eSeedOverPOut() {return els_eSeedOverPOut_handle.get();}
const std::vector<float>& CMS2::els_ecalEnergy() {return els_ecalEnergy_handle.get();}
const std::vector<float>& CMS2::els_ecalEnergyError() {return els_ecalEnergyError_handle.get();}
const std::vector<float>& CMS2::els_ecalIso() {return els_ecalIso_handle.get();}
const std::vector<float>& CMS2::els_ecalIso04() {return els_ecalIso04_handle.get();}
const std::vector<float>& CMS2::els_etaErr() {return els_etaErr_handle.get();}
const std::vector<float>& CMS2::els_etaSC() {return els_etaSC_handle.get();}
const std::vector<float>& CMS2::els_etaSCwidth() {return els_etaSCwidth_handle.get();}
const std::vector<float>& CMS2::els_fbrem() {return els_fbrem_handle.get();}
const std::vector<float>& CMS2::els_hOverE() {return els_hOverE_handle.get();}
const std::vector<float>& CMS2::els_hcalDepth1OverEcal() {return els_hcalDepth1OverEcal_handle.get();}
const std::vector<float>& CMS2::els_hcalDepth1TowerSumEt() {return els_hcalDepth1TowerSumEt_handle.get();}
const std::vector<float>& CMS2::els_hcalDepth1TowerSumEt04() {return els_hcalDepth1TowerSumEt04_handle.get();}
const std::vector<float>& CMS2::els_hcalDepth2OverEcal() {return els_hcalDepth2OverEcal_handle.get();}
const std::vector<float>& CMS2::els_hcalDepth2TowerSumEt() {return els_hcalDepth2TowerSumEt_handle.get();}
const std::vector<float>& CMS2::els_hcalDepth2TowerSumEt04() {return els_hcalDepth2TowerSumEt04_handle.get();}
const std::vector<float>& CMS2::els_hcalIso() {return els_hcalIso_handle.get();}
const std::vector<float>& CMS2::els_hcalIso04() {return els_hcalIso04_handle.get();}
const std::vector<float>& CMS2::els_ip3d() {return els_ip3d_handle.get();}
const std::vector<float>& CMS2::els_ip3derr() {return els_ip3derr_handle.get();}
const std::vector<float>& CMS2::els_iso03_pf() {return els_iso03_pf_handle.get();}
const std::vector<float>& CMS2::els_iso03_pf2012_ch() {return els_iso03_pf2012_ch_handle.get();}
const std::vector<float>& CMS2::els_iso03_pf2012_em() {return els_iso03_pf2012_em_handle.get();}
const std::vector<float>& CMS2::els_iso03_pf2012ext_ch() {return els_iso03_pf2012ext_ch_handle.get();}
const std::vector<float>& CMS2::els_iso03_pf2012ext_em() {return els_iso03_pf2012ext_em_handle.get();}
const std::vector<float>& CMS2::els_iso03_pf2012ext_nh() {return els_iso03_pf2012ext_nh_handle.get();}
const std::vector<float>& CMS2::els_iso03_pf2012_nh() {return els_iso03_pf2012_nh_handle.get();}
const std::vector<float>& CMS2::els_iso03_pf_ch() {return els_iso03_pf_ch_handle.get();}
const std::vector<float>& CMS2::els_iso03_pf_gamma05() {return els_iso03_pf_gamma05_handle.get();}
const std::vector<float>& CMS2::els_iso03_pf_nhad05() {return els_iso03_pf_nhad05_handle.get();}
const std::vector<float>& CMS2::els_iso04_pf() {return els_iso04_pf_handle.get();}
const std::vector<float>& CMS2::els_iso04_pf2012_ch() {return els_iso04_pf2012_ch_handle.get();}
const std::vector<float>& CMS2::els_iso04_pf2012_em() {return els_iso04_pf2012_em_handle.get();}
const std::vector<float>& CMS2::els_iso04_pf2012ext_ch() {return els_iso04_pf2012ext_ch_handle.get();}
const std::vector<float>& CMS2::els_iso04_pf2012ext_em() {return els_iso04_pf2012ext_em_handle.get();}
const std::vector<float>& CMS2::els_iso04_pf2012ext_nh() {return els_iso04_pf2012ext_nh_handle.get();}
const std::vector<float>& CMS2::els_iso04_pf2012_nh() {return els_iso04_pf2012_nh_handle.get();}
const std::vector<float>& CMS2::els_iso04_pf_ch() {return els_iso04_pf_ch_handle.get();}
const std::vector<float>& CMS2::els_iso04_pf_gamma05() {return els_iso04_pf_gamma05_handle.get();}
const std::vector<float>& CMS2::els_iso04_pf_nhad05() {return els_iso04_pf_nhad05_handle.get();}
const std::vector<float>& CMS2::els_layer1_charge() {return els_layer1_charge_handle.get();}
const std::vector<float>& CMS2::els_lh() {return els_lh_handle.get();}
const std::vector<float>& CMS2::els_mva() {return els_mva_handle.get();}
const std::vector<float>& CMS2::els_ndof() {return els_ndof_handle.get();}
const std::vector<float>& CMS2::els_pfChargedHadronIso() {return els_pfChargedHadronIso_handle.get();}
const std::vector<float>& CMS2::els_pfNeutralHadronIso() {return els_pfNeutralHadronIso_handle.get();}
const std::vector<float>& CMS2::els_pfPhotonIso() {return els_pfPhotonIso_handle.get();}
const std::vector<float>& CMS2::els_phiErr() {return els_phiErr_handle.get();}
const std::vector<float>& CMS2::els_phiSC() {return els_phiSC_handle.get();}
const std::vector<float>& CMS2::els_phiSCwidth() {return els_phiSCwidth_handle.get();}
const std::vector<float>& CMS2::els_ptErr() {return els_ptErr_handle.get();}
const std::vector<float>& CMS2::els_r9() {return els_r9_handle.get();}
const std::vector<float>& CMS2::els_sigmaEtaEta() {return els_sigmaEtaEta_handle.get();}
const std::vector<float>& CMS2::els_sigmaIEtaIEta() {return els_sigmaIEtaIEta_handle.get();}
const std::vector<float>& CMS2::els_sigmaIEtaIEtaSC() {return els_sigmaIEtaIEtaSC_handle.get();}
const std::vector<float>& CMS2::els_sigmaIEtaIPhi() {return els_sigmaIEtaIPhi_handle.get();}
const std::vector<float>& CMS2::els_sigmaIPhiIPhi() {return els_sigmaIPhiIPhi_handle.get();}
const std::vector<float>& CMS2::els_sigmaIPhiIPhiSC() {return els_sigmaIPhiIPhiSC_handle.get();}
const std::vector<float>& CMS2::els_sigmaIphiIphi() {return els_sigmaIphiIphi_handle.get();}
const std::vector<float>& CMS2::els_sigmaPhiPhi() {return els_sigmaPhiPhi_handle.get();}
const std::vector<float>& CMS2::els_tkIso() {return els_tkIso_handle.get();}
const std::vector<float>& CMS2::els_tkIso04() {return els_tkIso04_handle.get();}
const std::vector<float>& CMS2::els_trackMomentumError() {return els_trackMomentumError_handle.get();}
const std::vector<float>& CMS2::els_trkdr() {return els_trkdr_handle.get();}
const std::vector<float>& CMS2::els_trkshFrac() {return els_trkshFrac_handle.get();}
const std::vector<float>& CMS2::els_z0() {return els_z0_handle.get();}
const std::vector<float>& CMS2::els_z0Err() {return els_z0Err_handle.get();}
const std::vector<float>& CMS2::els_z0corr() {return els_z0corr_handle.get();}
const std::vector<float>& CMS2::gsftrks_chi2() {return gsftrks_chi2_handle.get();}
const std::vector<float>& CMS2::gsftrks_d0() {return gsftrks_d0_handle.get();}
const std::vector<float>& CMS2::gsftrks_d0Err() {return gsftrks_d0Err_handle.get();}
const std::vector<float>& CMS2::gsftrks_d0corr() {return gsftrks_d0corr_handle.get();}
const std::vector<float>& CMS2::gsftrks_d0corrPhi() {return gsftrks_d0corrPhi_handle.get();}
const std::vector<float>& CMS2::gsftrks_d0phiCov() {return gsftrks_d0phiCov_handle.get();}
const std::vector<float>& CMS2::gsftrks_etaErr() {return gsftrks_etaErr_handle.get();}
const std::vector<float>& CMS2::gsftrks_layer1_charge() {return gsftrks_layer1_charge_handle.get();}
const std::vector<float>& CMS2::gsftrks_ndof() {return gsftrks_ndof_handle.get();}
const std::vector<float>& CMS2::gsftrks_phiErr() {return gsftrks_phiErr_handle.get();}
const std::vector<float>& CMS2::gsftrks_ptErr() {return gsftrks_ptErr_handle.get();}
const std::vector<float>& CMS2::gsftrks_z0() {return gsftrks_z0_handle.get();}
const std::vector<float>& CMS2::gsftrks_z0Err() {return gsftrks_z0Err_handle.get();}
const std::vector<float>& CMS2::gsftrks_z0corr() {return gsftrks_z0corr_handle.get();}
const std::vector<float>& CMS2::hyp_Ht() {return hyp_Ht_handle.get();}
const std::vector<float>& CMS2::hyp_dPhi_nJet_metMuonJESCorr() {return hyp_dPhi_nJet_metMuonJESCorr_handle.get();}
const std::vector<float>& CMS2::hyp_dPhi_nJet_muCorrMet() {return hyp_dPhi_nJet_muCorrMet_handle.get();}
const std::vector<float>& CMS2::hyp_dPhi_nJet_tcMet() {return hyp_dPhi_nJet_tcMet_handle.get();}
const std::vector<float>& CMS2::hyp_dPhi_nJet_unCorrMet() {return hyp_dPhi_nJet_unCorrMet_handle.get();}
const std::vector<float>& CMS2::hyp_ll_chi2() {return hyp_ll_chi2_handle.get();}
const std::vector<float>& CMS2::hyp_ll_d0() {return hyp_ll_d0_handle.get();}
const std::vector<float>& CMS2::hyp_ll_d0Err() {return hyp_ll_d0Err_handle.get();}
const std::vector<float>& CMS2::hyp_ll_d0corr() {return hyp_ll_d0corr_handle.get();}
const std::vector<float>& CMS2::hyp_ll_dPhi_metMuonJESCorr() {return hyp_ll_dPhi_metMuonJESCorr_handle.get();}
const std::vector<float>& CMS2::hyp_ll_dPhi_muCorrMet() {return hyp_ll_dPhi_muCorrMet_handle.get();}
const std::vector<float>& CMS2::hyp_ll_dPhi_tcMet() {return hyp_ll_dPhi_tcMet_handle.get();}
const std::vector<float>& CMS2::hyp_ll_dPhi_unCorrMet() {return hyp_ll_dPhi_unCorrMet_handle.get();}
const std::vector<float>& CMS2::hyp_ll_etaErr() {return hyp_ll_etaErr_handle.get();}
const std::vector<float>& CMS2::hyp_ll_ndof() {return hyp_ll_ndof_handle.get();}
const std::vector<float>& CMS2::hyp_ll_phiErr() {return hyp_ll_phiErr_handle.get();}
const std::vector<float>& CMS2::hyp_ll_ptErr() {return hyp_ll_ptErr_handle.get();}
const std::vector<float>& CMS2::hyp_ll_z0() {return hyp_ll_z0_handle.get();}
const std::vector<float>& CMS2::hyp_ll_z0Err() {return hyp_ll_z0Err_handle.get();}
const std::vector<float>& CMS2::hyp_ll_z0corr() {return hyp_ll_z0corr_handle.get();}
const std::vector<float>& CMS2::hyp_lt_chi2() {return hyp_lt_chi2_handle.get();}
const std::vector<float>& CMS2::hyp_lt_d0() {return hyp_lt_d0_handle.get();}
const std::vector<float>& CMS2::hyp_lt_d0Err() {return hyp_lt_d0Err_handle.get();}
const std::vector<float>& CMS2::hyp_lt_d0corr() {return hyp_lt_d0corr_handle.get();}
const std::vector<float>& CMS2::hyp_lt_dPhi_metMuonJESCorr() {return hyp_lt_dPhi_metMuonJESCorr_handle.get();}
const std::vector<float>& CMS2::hyp_lt_dPhi_muCorrMet() {return hyp_lt_dPhi_muCorrMet_handle.get();}
const std::vector<float>& CMS2::hyp_lt_dPhi_tcMet() {return hyp_lt_dPhi_tcMet_handle.get();}
const std::vector<float>& CMS2::hyp_lt_dPhi_unCorrMet() {return hyp_lt_dPhi_unCorrMet_handle.get();}
const std::vector<float>& CMS2::hyp_lt_etaErr() {return hyp_lt_etaErr_handle.get();}
const std::vector<float>& CMS2::hyp_lt_ndof() {return hyp_lt_ndof_handle.get();}
const std::vector<float>& CMS2::hyp_lt_phiErr() {return hyp_lt_phiErr_handle.get();}
const std::vector<float>& CMS2::hyp_lt_ptErr() {return hyp_lt_ptErr_handle.get();}
const std::vector<float>& CMS2::hyp_lt_z0() {return hyp_lt_z0_handle.get();}
const std::vector<float>& CMS2::hyp_lt_z0Err() {return hyp_lt_z0Err_handle.get();}
const std::vector<float>& CMS2::hyp_lt_z0corr() {return hyp_lt_z0corr_handle.get();}
const std::vector<float>& CMS2::hyp_mt2_metMuonJESCorr() {return hyp_mt2_metMuonJESCorr_handle.get();}
const std::vector<float>& CMS2::hyp_mt2_muCorrMet() {return hyp_mt2_muCorrMet_handle.get();}
const std::vector<float>& CMS2::hyp_mt2_tcMet() {return hyp_mt2_tcMet_handle.get();}
const std::vector<float>& CMS2::hyp_sumJetPt() {return hyp_sumJetPt_handle.get();}
const std::vector<float>& CMS2::hyp_FVFit_chi2ndf() {return hyp_FVFit_chi2ndf_handle.get();}
const std::vector<float>& CMS2::hyp_FVFit_prob() {return hyp_FVFit_prob_handle.get();}
const std::vector<float>& CMS2::hyp_FVFit_v4cxx() {return hyp_FVFit_v4cxx_handle.get();}
const std::vector<float>& CMS2::hyp_FVFit_v4cxy() {return hyp_FVFit_v4cxy_handle.get();}
const std::vector<float>& CMS2::hyp_FVFit_v4cyy() {return hyp_FVFit_v4cyy_handle.get();}
const std::vector<float>& CMS2::hyp_FVFit_v4czx() {return hyp_FVFit_v4czx_handle.get();}
const std::vector<float>& CMS2::hyp_FVFit_v4czy() {return hyp_FVFit_v4czy_handle.get();}
const std::vector<float>& CMS2::hyp_FVFit_v4czz() {return hyp_FVFit_v4czz_handle.get();}
const std::vector<float>& CMS2::jets_approximatefHPD() {return jets_approximatefHPD_handle.get();}
const std::vector<float>& CMS2::jets_approximatefRBX() {return jets_approximatefRBX_handle.get();}
const std::vector<float>& CMS2::jets_cor() {return jets_cor_handle.get();}
const std::vector<float>& CMS2::jets_corL1FastL2L3() {return jets_corL1FastL2L3_handle.get();}
const std::vector<float>& CMS2::jets_corL1L2L3() {return jets_corL1L2L3_handle.get();}
const std::vector<float>& CMS2::jets_emFrac() {return jets_emFrac_handle.get();}
const std::vector<float>& CMS2::jets_fHPD() {return jets_fHPD_handle.get();}
const std::vector<float>& CMS2::jets_fRBX() {return jets_fRBX_handle.get();}
const std::vector<float>& CMS2::jets_fSubDetector1() {return jets_fSubDetector1_handle.get();}
const std::vector<float>& CMS2::jets_fSubDetector2() {return jets_fSubDetector2_handle.get();}
const std::vector<float>& CMS2::jets_fSubDetector3() {return jets_fSubDetector3_handle.get();}
const std::vector<float>& CMS2::jets_fSubDetector4() {return jets_fSubDetector4_handle.get();}
const std::vector<float>& CMS2::jets_hitsInN90() {return jets_hitsInN90_handle.get();}
const std::vector<float>& CMS2::jets_n90Hits() {return jets_n90Hits_handle.get();}
const std::vector<float>& CMS2::jets_nECALTowers() {return jets_nECALTowers_handle.get();}
const std::vector<float>& CMS2::jets_nHCALTowers() {return jets_nHCALTowers_handle.get();}
const std::vector<float>& CMS2::jets_restrictedEMF() {return jets_restrictedEMF_handle.get();}
const std::vector<float>& CMS2::mus_met_deltax() {return mus_met_deltax_handle.get();}
const std::vector<float>& CMS2::mus_met_deltay() {return mus_met_deltay_handle.get();}
const std::vector<float>& CMS2::mus_eledr() {return mus_eledr_handle.get();}
const std::vector<float>& CMS2::mus_jetdr() {return mus_jetdr_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_chpf_radial() {return mus_isoR03_chpf_radial_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_chpf_radialTight() {return mus_isoR03_chpf_radialTight_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_empf_radial() {return mus_isoR03_empf_radial_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_empf_radialTight() {return mus_isoR03_empf_radialTight_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_nhpf_radial() {return mus_isoR03_nhpf_radial_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_nhpf_radialTight() {return mus_isoR03_nhpf_radialTight_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_pf_radial() {return mus_isoR03_pf_radial_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_pf_radialTight() {return mus_isoR03_pf_radialTight_handle.get();}
const std::vector<float>& CMS2::mus_backToBackCompat() {return mus_backToBackCompat_handle.get();}
const std::vector<float>& CMS2::mus_caloCompatibility() {return mus_caloCompatibility_handle.get();}
const std::vector<float>& CMS2::mus_chi2() {return mus_chi2_handle.get();}
const std::vector<float>& CMS2::mus_chi2LocalMomentum() {return mus_chi2LocalMomentum_handle.get();}
const std::vector<float>& CMS2::mus_chi2LocalPosition() {return mus_chi2LocalPosition_handle.get();}
const std::vector<float>& CMS2::mus_cosmicCompat() {return mus_cosmicCompat_handle.get();}
const std::vector<float>& CMS2::mus_d0() {return mus_d0_handle.get();}
const std::vector<float>& CMS2::mus_d0Err() {return mus_d0Err_handle.get();}
const std::vector<float>& CMS2::mus_d0corr() {return mus_d0corr_handle.get();}
const std::vector<float>& CMS2::mus_e_em() {return mus_e_em_handle.get();}
const std::vector<float>& CMS2::mus_e_emS9() {return mus_e_emS9_handle.get();}
const std::vector<float>& CMS2::mus_e_had() {return mus_e_had_handle.get();}
const std::vector<float>& CMS2::mus_e_hadS9() {return mus_e_hadS9_handle.get();}
const std::vector<float>& CMS2::mus_e_ho() {return mus_e_ho_handle.get();}
const std::vector<float>& CMS2::mus_e_hoS9() {return mus_e_hoS9_handle.get();}
const std::vector<float>& CMS2::mus_etaErr() {return mus_etaErr_handle.get();}
const std::vector<float>& CMS2::mus_gfit_chi2() {return mus_gfit_chi2_handle.get();}
const std::vector<float>& CMS2::mus_gfit_d0() {return mus_gfit_d0_handle.get();}
const std::vector<float>& CMS2::mus_gfit_d0Err() {return mus_gfit_d0Err_handle.get();}
const std::vector<float>& CMS2::mus_gfit_d0corr() {return mus_gfit_d0corr_handle.get();}
const std::vector<float>& CMS2::mus_gfit_ndof() {return mus_gfit_ndof_handle.get();}
const std::vector<float>& CMS2::mus_gfit_qoverp() {return mus_gfit_qoverp_handle.get();}
const std::vector<float>& CMS2::mus_gfit_qoverpError() {return mus_gfit_qoverpError_handle.get();}
const std::vector<float>& CMS2::mus_gfit_z0() {return mus_gfit_z0_handle.get();}
const std::vector<float>& CMS2::mus_gfit_z0Err() {return mus_gfit_z0Err_handle.get();}
const std::vector<float>& CMS2::mus_gfit_z0corr() {return mus_gfit_z0corr_handle.get();}
const std::vector<float>& CMS2::mus_glbKink() {return mus_glbKink_handle.get();}
const std::vector<float>& CMS2::mus_glbTrackProbability() {return mus_glbTrackProbability_handle.get();}
const std::vector<float>& CMS2::mus_globalDeltaEtaPhi() {return mus_globalDeltaEtaPhi_handle.get();}
const std::vector<float>& CMS2::mus_ip3d() {return mus_ip3d_handle.get();}
const std::vector<float>& CMS2::mus_ip3derr() {return mus_ip3derr_handle.get();}
const std::vector<float>& CMS2::mus_iso03_emEt() {return mus_iso03_emEt_handle.get();}
const std::vector<float>& CMS2::mus_iso03_hadEt() {return mus_iso03_hadEt_handle.get();}
const std::vector<float>& CMS2::mus_iso03_hoEt() {return mus_iso03_hoEt_handle.get();}
const std::vector<float>& CMS2::mus_iso03_pf() {return mus_iso03_pf_handle.get();}
const std::vector<float>& CMS2::mus_iso03_sumPt() {return mus_iso03_sumPt_handle.get();}
const std::vector<float>& CMS2::mus_iso04_pf() {return mus_iso04_pf_handle.get();}
const std::vector<float>& CMS2::mus_iso05_emEt() {return mus_iso05_emEt_handle.get();}
const std::vector<float>& CMS2::mus_iso05_hadEt() {return mus_iso05_hadEt_handle.get();}
const std::vector<float>& CMS2::mus_iso05_hoEt() {return mus_iso05_hoEt_handle.get();}
const std::vector<float>& CMS2::mus_iso05_sumPt() {return mus_iso05_sumPt_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_pf_ChargedHadronPt() {return mus_isoR03_pf_ChargedHadronPt_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_pf_ChargedParticlePt() {return mus_isoR03_pf_ChargedParticlePt_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_pf_NeutralHadronEt() {return mus_isoR03_pf_NeutralHadronEt_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_pf_NeutralHadronEtHighThreshold() {return mus_isoR03_pf_NeutralHadronEtHighThreshold_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_pf_PUPt() {return mus_isoR03_pf_PUPt_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_pf_PhotonEt() {return mus_isoR03_pf_PhotonEt_handle.get();}
const std::vector<float>& CMS2::mus_isoR03_pf_PhotonEtHighThreshold() {return mus_isoR03_pf_PhotonEtHighThreshold_handle.get();}
const std::vector<float>& CMS2::mus_isoR04_pf_ChargedHadronPt() {return mus_isoR04_pf_ChargedHadronPt_handle.get();}
const std::vector<float>& CMS2::mus_isoR04_pf_ChargedParticlePt() {return mus_isoR04_pf_ChargedParticlePt_handle.get();}
const std::vector<float>& CMS2::mus_isoR04_pf_NeutralHadronEt() {return mus_isoR04_pf_NeutralHadronEt_handle.get();}
const std::vector<float>& CMS2::mus_isoR04_pf_NeutralHadronEtHighThreshold() {return mus_isoR04_pf_NeutralHadronEtHighThreshold_handle.get();}
const std::vector<float>& CMS2::mus_isoR04_pf_PUPt() {return mus_isoR04_pf_PUPt_handle.get();}
const std::vector<float>& CMS2::mus_isoR04_pf_PhotonEt() {return mus_isoR04_pf_PhotonEt_handle.get();}
const std::vector<float>& CMS2::mus_isoR04_pf_PhotonEtHighThreshold() {return mus_isoR04_pf_PhotonEtHighThreshold_handle.get();}
const std::vector<float>& CMS2::mus_iso_ecalvetoDep() {return mus_iso_ecalvetoDep_handle.get();}
const std::vector<float>& CMS2::mus_iso_hcalvetoDep() {return mus_iso_hcalvetoDep_handle.get();}
const std::vector<float>& CMS2::mus_iso_hovetoDep() {return mus_iso_hovetoDep_handle.get();}
const std::vector<float>& CMS2::mus_iso_trckvetoDep() {return mus_iso_trckvetoDep_handle.get();}
const std::vector<float>& CMS2::mus_localDistance() {return mus_localDistance_handle.get();}
const std::vector<float>& CMS2::mus_ndof() {return mus_ndof_handle.get();}
const std::vector<float>& CMS2::mus_overlapCompat() {return mus_overlapCompat_handle.get();}
const std::vector<float>& CMS2::mus_pfdeltaP() {return mus_pfdeltaP_handle.get();}
const std::vector<float>& CMS2::mus_pfecalE() {return mus_pfecalE_handle.get();}
const std::vector<float>& CMS2::mus_pfhcalE() {return mus_pfhcalE_handle.get();}
const std::vector<float>& CMS2::mus_pfmva_emu() {return mus_pfmva_emu_handle.get();}
const std::vector<float>& CMS2::mus_pfmva_epi() {return mus_pfmva_epi_handle.get();}
const std::vector<float>& CMS2::mus_pfmva_nothing_gamma() {return mus_pfmva_nothing_gamma_handle.get();}
const std::vector<float>& CMS2::mus_pfmva_nothing_nh() {return mus_pfmva_nothing_nh_handle.get();}
const std::vector<float>& CMS2::mus_pfmva_pimu() {return mus_pfmva_pimu_handle.get();}
const std::vector<float>& CMS2::mus_pfpS1E() {return mus_pfpS1E_handle.get();}
const std::vector<float>& CMS2::mus_pfpS2E() {return mus_pfpS2E_handle.get();}
const std::vector<float>& CMS2::mus_pfrawEcalE() {return mus_pfrawEcalE_handle.get();}
const std::vector<float>& CMS2::mus_pfrawHcalE() {return mus_pfrawHcalE_handle.get();}
const std::vector<float>& CMS2::mus_phiErr() {return mus_phiErr_handle.get();}
const std::vector<float>& CMS2::mus_ptErr() {return mus_ptErr_handle.get();}
const std::vector<float>& CMS2::mus_qoverp() {return mus_qoverp_handle.get();}
const std::vector<float>& CMS2::mus_qoverpError() {return mus_qoverpError_handle.get();}
const std::vector<float>& CMS2::mus_segmCompatibility() {return mus_segmCompatibility_handle.get();}
const std::vector<float>& CMS2::mus_staRelChi2() {return mus_staRelChi2_handle.get();}
const std::vector<float>& CMS2::mus_sta_chi2() {return mus_sta_chi2_handle.get();}
const std::vector<float>& CMS2::mus_sta_d0() {return mus_sta_d0_handle.get();}
const std::vector<float>& CMS2::mus_sta_d0Err() {return mus_sta_d0Err_handle.get();}
const std::vector<float>& CMS2::mus_sta_d0corr() {return mus_sta_d0corr_handle.get();}
const std::vector<float>& CMS2::mus_sta_ndof() {return mus_sta_ndof_handle.get();}
const std::vector<float>& CMS2::mus_sta_qoverp() {return mus_sta_qoverp_handle.get();}
const std::vector<float>& CMS2::mus_sta_qoverpError() {return mus_sta_qoverpError_handle.get();}
const std::vector<float>& CMS2::mus_sta_z0() {return mus_sta_z0_handle.get();}
const std::vector<float>& CMS2::mus_sta_z0Err() {return mus_sta_z0Err_handle.get();}
const std::vector<float>& CMS2::mus_sta_z0corr() {return mus_sta_z0corr_handle.get();}
const std::vector<float>& CMS2::mus_timeAtIpInOut() {return mus_timeAtIpInOut_handle.get();}
const std::vector<float>& CMS2::mus_timeAtIpInOutErr() {return mus_timeAtIpInOutErr_handle.get();}
const std::vector<float>& CMS2::mus_timeAtIpOutIn() {return mus_timeAtIpOutIn_handle.get();}
const std::vector<float>& CMS2::mus_timeAtIpOutInErr() {return mus_timeAtIpOutInErr_handle.get();}
const std::vector<float>& CMS2::mus_timeCompat() {return mus_timeCompat_handle.get();}
const std::vector<float>& CMS2::mus_trkKink() {return mus_trkKink_handle.get();}
const std::vector<float>& CMS2::mus_trkRelChi2() {return mus_trkRelChi2_handle.get();}
const std::vector<float>& CMS2::mus_vertexCompat() {return mus_vertexCompat_handle.get();}
const std::vector<float>& CMS2::mus_vertexphi() {return mus_vertexphi_handle.get();}
const std::vector<float>& CMS2::mus_z0() {return mus_z0_handle.get();}
const std::vector<float>& CMS2::mus_z0Err() {return mus_z0Err_handle.get();}
const std::vector<float>& CMS2::mus_z0corr() {return mus_z0corr_handle.get();}
const std::vector<float>& CMS2::pfjets_mvavalue() {return pfjets_mvavalue_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_beta() {return pfjets_full53xmva_beta_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_betaStar() {return pfjets_full53xmva_betaStar_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_d0() {return pfjets_full53xmva_d0_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_dRMean() {return pfjets_full53xmva_dRMean_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_dZ() {return pfjets_full53xmva_dZ_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_frac01() {return pfjets_full53xmva_frac01_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_frac02() {return pfjets_full53xmva_frac02_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_frac03() {return pfjets_full53xmva_frac03_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_frac04() {return pfjets_full53xmva_frac04_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_frac05() {return pfjets_full53xmva_frac05_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_nCharged() {return pfjets_full53xmva_nCharged_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_nNeutrals() {return pfjets_full53xmva_nNeutrals_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmva_nvtx() {return pfjets_full53xmva_nvtx_handle.get();}
const std::vector<float>& CMS2::pfjets_full53xmvavalue() {return pfjets_full53xmvavalue_handle.get();}
const std::vector<float>& CMS2::pfjets_full5xmvavalue() {return pfjets_full5xmvavalue_handle.get();}
const std::vector<float>& CMS2::trkjet_met() {return trkjet_met_handle.get();}
const std::vector<float>& CMS2::trkjet_metPhi() {return trkjet_metPhi_handle.get();}
const std::vector<float>& CMS2::trkjet_sumet() {return trkjet_sumet_handle.get();}
const std::vector<float>& CMS2::trk_met() {return trk_met_handle.get();}
const std::vector<float>& CMS2::trk_metPhi() {return trk_metPhi_handle.get();}
const std::vector<float>& CMS2::trk_sumet() {return trk_sumet_handle.get();}
const std::vector<float>& CMS2::pfcands_deltaP() {return pfcands_deltaP_handle.get();}
const std::vector<float>& CMS2::pfcands_ecalE() {return pfcands_ecalE_handle.get();}
const std::vector<float>& CMS2::pfcands_hcalE() {return pfcands_hcalE_handle.get();}
const std::vector<float>& CMS2::pfcands_mva_emu() {return pfcands_mva_emu_handle.get();}
const std::vector<float>& CMS2::pfcands_mva_epi() {return pfcands_mva_epi_handle.get();}
const std::vector<float>& CMS2::pfcands_mva_nothing_gamma() {return pfcands_mva_nothing_gamma_handle.get();}
const std::vector<float>& CMS2::pfcands_mva_nothing_nh() {return pfcands_mva_nothing_nh_handle.get();}
const std::vector<float>& CMS2::pfcands_mva_pimu() {return pfcands_mva_pimu_handle.get();}
const std::vector<float>& CMS2::pfcands_pS1E() {return pfcands_pS1E_handle.get();}
const std::vector<float>& CMS2::pfcands_pS2E() {return pfcands_pS2E_handle.get();}
const std::vector<float>& CMS2::pfcands_rawEcalE() {return pfcands_rawEcalE_handle.get();}
const std::vector<float>& CMS2::pfcands_rawHcalE() {return pfcands_rawHcalE_handle.get();}
const std::vector<float>& CMS2::pfels_deltaP() {return pfels_deltaP_handle.get();}
const std::vector<float>& CMS2::pfels_ecalE() {return pfels_ecalE_handle.get();}
const std::vector<float>& CMS2::pfels_hcalE() {return pfels_hcalE_handle.get();}
const std::vector<float>& CMS2::pfels_iso04ChargedHadrons() {return pfels_iso04ChargedHadrons_handle.get();}
const std::vector<float>& CMS2::pfels_iso04NeutralHadrons() {return pfels_iso04NeutralHadrons_handle.get();}
const std::vector<float>& CMS2::pfels_iso04Photons() {return pfels_iso04Photons_handle.get();}
const std::vector<float>& CMS2::pfels_isoChargedHadrons() {return pfels_isoChargedHadrons_handle.get();}
const std::vector<float>& CMS2::pfels_isoNeutralHadrons() {return pfels_isoNeutralHadrons_handle.get();}
const std::vector<float>& CMS2::pfels_isoPhotons() {return pfels_isoPhotons_handle.get();}
const std::vector<float>& CMS2::pfels_mva_emu() {return pfels_mva_emu_handle.get();}
const std::vector<float>& CMS2::pfels_mva_epi() {return pfels_mva_epi_handle.get();}
const std::vector<float>& CMS2::pfels_mva_nothing_gamma() {return pfels_mva_nothing_gamma_handle.get();}
const std::vector<float>& CMS2::pfels_mva_nothing_nh() {return pfels_mva_nothing_nh_handle.get();}
const std::vector<float>& CMS2::pfels_mva_pimu() {return pfels_mva_pimu_handle.get();}
const std::vector<float>& CMS2::pfels_pS1E() {return pfels_pS1E_handle.get();}
const std::vector<float>& CMS2::pfels_pS2E() {return pfels_pS2E_handle.get();}
const std::vector<float>& CMS2::pfels_rawEcalE() {return pfels_rawEcalE_handle.get();}
const std::vector<float>& CMS2::pfels_rawHcalE() {return pfels_rawHcalE_handle.get();}
const std::vector<float>& CMS2::pfjets_area() {return pfjets_area_handle.get();}
const std::vector<float>& CMS2::pfjets_chargedEmE() {return pfjets_chargedEmE_handle.get();}
const std::vector<float>& CMS2::pfjets_chargedHadronE() {return pfjets_chargedHadronE_handle.get();}
const std::vector<float>& CMS2::pfjets_cor() {return pfjets_cor_handle.get();}
const std::vector<float>& CMS2::pfjets_corL1Fast() {return pfjets_corL1Fast_handle.get();}
const std::vector<float>& CMS2::pfjets_corL1FastL2L3() {return pfjets_corL1FastL2L3_handle.get();}
const std::vector<float>& CMS2::pfjets_corL1FastL2L3residual() {return pfjets_corL1FastL2L3residual_handle.get();}
const std::vector<float>& CMS2::pfjets_corL1L2L3() {return pfjets_corL1L2L3_handle.get();}
const std::vector<float>& CMS2::pfjets_electronE() {return pfjets_electronE_handle.get();}
const std::vector<float>& CMS2::pfjets_hfEmE() {return pfjets_hfEmE_handle.get();}
const std::vector<float>& CMS2::pfjets_hfHadronE() {return pfjets_hfHadronE_handle.get();}
const std::vector<float>& CMS2::pfjets_muonE() {return pfjets_muonE_handle.get();}
const std::vector<float>& CMS2::pfjets_neutralEmE() {return pfjets_neutralEmE_handle.get();}
const std::vector<float>& CMS2::pfjets_neutralHadronE() {return pfjets_neutralHadronE_handle.get();}
const std::vector<float>& CMS2::pfjets_photonE() {return pfjets_photonE_handle.get();}
const std::vector<float>& CMS2::pfmus_deltaP() {return pfmus_deltaP_handle.get();}
const std::vector<float>& CMS2::pfmus_ecalE() {return pfmus_ecalE_handle.get();}
const std::vector<float>& CMS2::pfmus_hcalE() {return pfmus_hcalE_handle.get();}
const std::vector<float>& CMS2::pfmus_iso04ChargedHadrons() {return pfmus_iso04ChargedHadrons_handle.get();}
const std::vector<float>& CMS2::pfmus_iso04NeutralHadrons() {return pfmus_iso04NeutralHadrons_handle.get();}
const std::vector<float>& CMS2::pfmus_iso04Photons() {return pfmus_iso04Photons_handle.get();}
const std::vector<float>& CMS2::pfmus_isoChargedHadrons() {return pfmus_isoChargedHadrons_handle.get();}
const std::vector<float>& CMS2::pfmus_isoNeutralHadrons() {return pfmus_isoNeutralHadrons_handle.get();}
const std::vector<float>& CMS2::pfmus_isoPhotons() {return pfmus_isoPhotons_handle.get();}
const std::vector<float>& CMS2::pfmus_mva_emu() {return pfmus_mva_emu_handle.get();}
const std::vector<float>& CMS2::pfmus_mva_epi() {return pfmus_mva_epi_handle.get();}
const std::vector<float>& CMS2::pfmus_mva_nothing_gamma() {return pfmus_mva_nothing_gamma_handle.get();}
const std::vector<float>& CMS2::pfmus_mva_nothing_nh() {return pfmus_mva_nothing_nh_handle.get();}
const std::vector<float>& CMS2::pfmus_mva_pimu() {return pfmus_mva_pimu_handle.get();}
const std::vector<float>& CMS2::pfmus_pS1E() {return pfmus_pS1E_handle.get();}
const std::vector<float>& CMS2::pfmus_pS2E() {return pfmus_pS2E_handle.get();}
const std::vector<float>& CMS2::pfmus_rawEcalE() {return pfmus_rawEcalE_handle.get();}
const std::vector<float>& CMS2::pfmus_rawHcalE() {return pfmus_rawHcalE_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronDeadECAL() {return taus_pf_againstElectronDeadECAL_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronLoose() {return taus_pf_againstElectronLoose_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronLooseMVA2() {return taus_pf_againstElectronLooseMVA2_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronLooseMVA3() {return taus_pf_againstElectronLooseMVA3_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronMVA() {return taus_pf_againstElectronMVA_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronMVA2category() {return taus_pf_againstElectronMVA2category_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronMVA2raw() {return taus_pf_againstElectronMVA2raw_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronMVA3category() {return taus_pf_againstElectronMVA3category_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronMVA3raw() {return taus_pf_againstElectronMVA3raw_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronMedium() {return taus_pf_againstElectronMedium_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronMediumMVA2() {return taus_pf_againstElectronMediumMVA2_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronMediumMVA3() {return taus_pf_againstElectronMediumMVA3_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronTight() {return taus_pf_againstElectronTight_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronTightMVA2() {return taus_pf_againstElectronTightMVA2_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronTightMVA3() {return taus_pf_againstElectronTightMVA3_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronVLooseMVA2() {return taus_pf_againstElectronVLooseMVA2_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstElectronVTightMVA3() {return taus_pf_againstElectronVTightMVA3_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstMuonLoose() {return taus_pf_againstMuonLoose_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstMuonLoose2() {return taus_pf_againstMuonLoose2_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstMuonMedium() {return taus_pf_againstMuonMedium_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstMuonMedium2() {return taus_pf_againstMuonMedium2_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstMuonTight() {return taus_pf_againstMuonTight_handle.get();}
const std::vector<float>& CMS2::taus_pf_againstMuonTight2() {return taus_pf_againstMuonTight2_handle.get();}
const std::vector<float>& CMS2::taus_pf_byCombinedIsolationDeltaBetaCorrRaw() {return taus_pf_byCombinedIsolationDeltaBetaCorrRaw_handle.get();}
const std::vector<float>& CMS2::taus_pf_byCombinedIsolationDeltaBetaCorrRaw3Hits() {return taus_pf_byCombinedIsolationDeltaBetaCorrRaw3Hits_handle.get();}
const std::vector<float>& CMS2::taus_pf_byDecayModeFinding() {return taus_pf_byDecayModeFinding_handle.get();}
const std::vector<float>& CMS2::taus_pf_byIsolationMVA2raw() {return taus_pf_byIsolationMVA2raw_handle.get();}
const std::vector<float>& CMS2::taus_pf_byIsolationMVAraw() {return taus_pf_byIsolationMVAraw_handle.get();}
const std::vector<float>& CMS2::taus_pf_byLooseCombinedIsolationDeltaBetaCorr() {return taus_pf_byLooseCombinedIsolationDeltaBetaCorr_handle.get();}
const std::vector<float>& CMS2::taus_pf_byLooseCombinedIsolationDeltaBetaCorr3Hits() {return taus_pf_byLooseCombinedIsolationDeltaBetaCorr3Hits_handle.get();}
const std::vector<float>& CMS2::taus_pf_byLooseIsolationMVA() {return taus_pf_byLooseIsolationMVA_handle.get();}
const std::vector<float>& CMS2::taus_pf_byLooseIsolationMVA2() {return taus_pf_byLooseIsolationMVA2_handle.get();}
const std::vector<float>& CMS2::taus_pf_byMediumCombinedIsolationDeltaBetaCorr() {return taus_pf_byMediumCombinedIsolationDeltaBetaCorr_handle.get();}
const std::vector<float>& CMS2::taus_pf_byMediumCombinedIsolationDeltaBetaCorr3Hits() {return taus_pf_byMediumCombinedIsolationDeltaBetaCorr3Hits_handle.get();}
const std::vector<float>& CMS2::taus_pf_byMediumIsolationMVA() {return taus_pf_byMediumIsolationMVA_handle.get();}
const std::vector<float>& CMS2::taus_pf_byMediumIsolationMVA2() {return taus_pf_byMediumIsolationMVA2_handle.get();}
const std::vector<float>& CMS2::taus_pf_byTightCombinedIsolationDeltaBetaCorr() {return taus_pf_byTightCombinedIsolationDeltaBetaCorr_handle.get();}
const std::vector<float>& CMS2::taus_pf_byTightCombinedIsolationDeltaBetaCorr3Hits() {return taus_pf_byTightCombinedIsolationDeltaBetaCorr3Hits_handle.get();}
const std::vector<float>& CMS2::taus_pf_byTightIsolationMVA() {return taus_pf_byTightIsolationMVA_handle.get();}
const std::vector<float>& CMS2::taus_pf_byTightIsolationMVA2() {return taus_pf_byTightIsolationMVA2_handle.get();}
const std::vector<float>& CMS2::taus_pf_byVLooseCombinedIsolationDeltaBetaCorr() {return taus_pf_byVLooseCombinedIsolationDeltaBetaCorr_handle.get();}
const std::vector<float>& CMS2::photons_e1x5() {return photons_e1x5_handle.get();}
const std::vector<float>& CMS2::photons_e2x5Max() {return photons_e2x5Max_handle.get();}
const std::vector<float>& CMS2::photons_e3x3() {return photons_e3x3_handle.get();}
const std::vector<float>& CMS2::photons_e5x5() {return photons_e5x5_handle.get();}
const std::vector<float>& CMS2::photons_ecalIso03() {return photons_ecalIso03_handle.get();}
const std::vector<float>& CMS2::photons_ecalIso04() {return photons_ecalIso04_handle.get();}
const std::vector<float>& CMS2::photons_hOverE() {return photons_hOverE_handle.get();}
const std::vector<float>& CMS2::photons_hcalDepth1TowerSumEtBcConeDR03() {return photons_hcalDepth1TowerSumEtBcConeDR03_handle.get();}
const std::vector<float>& CMS2::photons_hcalDepth1TowerSumEtBcConeDR04() {return photons_hcalDepth1TowerSumEtBcConeDR04_handle.get();}
const std::vector<float>& CMS2::photons_hcalDepth2TowerSumEtBcConeDR03() {return photons_hcalDepth2TowerSumEtBcConeDR03_handle.get();}
const std::vector<float>& CMS2::photons_hcalDepth2TowerSumEtBcConeDR04() {return photons_hcalDepth2TowerSumEtBcConeDR04_handle.get();}
const std::vector<float>& CMS2::photons_hcalIso03() {return photons_hcalIso03_handle.get();}
const std::vector<float>& CMS2::photons_hcalIso04() {return photons_hcalIso04_handle.get();}
const std::vector<float>& CMS2::photons_hcalTowerSumEtBcConeDR03() {return photons_hcalTowerSumEtBcConeDR03_handle.get();}
const std::vector<float>& CMS2::photons_hcalTowerSumEtBcConeDR04() {return photons_hcalTowerSumEtBcConeDR04_handle.get();}
const std::vector<float>& CMS2::photons_ntkIsoHollow03() {return photons_ntkIsoHollow03_handle.get();}
const std::vector<float>& CMS2::photons_ntkIsoHollow04() {return photons_ntkIsoHollow04_handle.get();}
const std::vector<float>& CMS2::photons_ntkIsoSolid03() {return photons_ntkIsoSolid03_handle.get();}
const std::vector<float>& CMS2::photons_ntkIsoSolid04() {return photons_ntkIsoSolid04_handle.get();}
const std::vector<float>& CMS2::photons_sigmaEtaEta() {return photons_sigmaEtaEta_handle.get();}
const std::vector<float>& CMS2::photons_sigmaIEtaIEta() {return photons_sigmaIEtaIEta_handle.get();}
const std::vector<float>& CMS2::photons_swissSeed() {return photons_swissSeed_handle.get();}
const std::vector<float>& CMS2::photons_tkIsoHollow03() {return photons_tkIsoHollow03_handle.get();}
const std::vector<float>& CMS2::photons_tkIsoHollow04() {return photons_tkIsoHollow04_handle.get();}
const std::vector<float>& CMS2::photons_tkIsoSolid03() {return photons_tkIsoSolid03_handle.get();}
const std::vector<float>& CMS2::photons_tkIsoSolid04() {return photons_tkIsoSolid04_handle.get();}
const std::vector<float>& CMS2::puInfo_trueNumInteractions() {return puInfo_trueNumInteractions_handle.get();}
const std::vector<float>& CMS2::convs_chi2() {return convs_chi2_handle.get();}
const std::vector<float>& CMS2::convs_dl() {return convs_dl_handle.get();}
const std::vector<float>& CMS2::convs_ndof() {return convs_ndof_handle.get();}
const std::vector<float>& CMS2::sparm_values() {return sparm_values_handle.get();}
const std::vector<float>& CMS2::scs_clustersSize() {return scs_clustersSize_handle.get();}
const std::vector<float>& CMS2::scs_crystalsSize() {return scs_crystalsSize_handle.get();}
const std::vector<float>& CMS2::scs_e1x3() {return scs_e1x3_handle.get();}
const std::vector<float>& CMS2::scs_e1x5() {return scs_e1x5_handle.get();}
const std::vector<float>& CMS2::scs_e2nd() {return scs_e2nd_handle.get();}
const std::vector<float>& CMS2::scs_e2x2() {return scs_e2x2_handle.get();}
const std::vector<float>& CMS2::scs_e2x5Max() {return scs_e2x5Max_handle.get();}
const std::vector<float>& CMS2::scs_e3x1() {return scs_e3x1_handle.get();}
const std::vector<float>& CMS2::scs_e3x2() {return scs_e3x2_handle.get();}
const std::vector<float>& CMS2::scs_e3x3() {return scs_e3x3_handle.get();}
const std::vector<float>& CMS2::scs_e4x4() {return scs_e4x4_handle.get();}
const std::vector<float>& CMS2::scs_e5x5() {return scs_e5x5_handle.get();}
const std::vector<float>& CMS2::scs_eMax() {return scs_eMax_handle.get();}
const std::vector<float>& CMS2::scs_eSeed() {return scs_eSeed_handle.get();}
const std::vector<float>& CMS2::scs_energy() {return scs_energy_handle.get();}
const std::vector<float>& CMS2::scs_eta() {return scs_eta_handle.get();}
const std::vector<float>& CMS2::scs_hoe() {return scs_hoe_handle.get();}
const std::vector<float>& CMS2::scs_laserCorMax() {return scs_laserCorMax_handle.get();}
const std::vector<float>& CMS2::scs_laserCorMean() {return scs_laserCorMean_handle.get();}
const std::vector<float>& CMS2::scs_laserCorSeed() {return scs_laserCorSeed_handle.get();}
const std::vector<float>& CMS2::scs_phi() {return scs_phi_handle.get();}
const std::vector<float>& CMS2::scs_preshowerEnergy() {return scs_preshowerEnergy_handle.get();}
const std::vector<float>& CMS2::scs_rawEnergy() {return scs_rawEnergy_handle.get();}
const std::vector<float>& CMS2::scs_sigmaEtaEta() {return scs_sigmaEtaEta_handle.get();}
const std::vector<float>& CMS2::scs_sigmaEtaPhi() {return scs_sigmaEtaPhi_handle.get();}
const std::vector<float>& CMS2::scs_sigmaIEtaIEta() {return scs_sigmaIEtaIEta_handle.get();}
const std::vector<float>& CMS2::scs_sigmaIEtaIEtaSC() {return scs_sigmaIEtaIEtaSC_handle.get();}
const std::vector<float>& CMS2::scs_sigmaIEtaIPhi() {return scs_sigmaIEtaIPhi_handle.get();}
const std::vector<float>& CMS2::scs_sigmaIEtaIPhiSC() {return scs_sigmaIEtaIPhiSC_handle.get();}
const std::vector<float>& CMS2::scs_sigmaIPhiIPhi() {return scs_sigmaIPhiIPhi_handle.get();}
const std::vector<float>& CMS2::scs_sigmaIPhiIPhiSC() {return scs_sigmaIPhiIPhiSC_handle.get();}
const std::vector<float>& CMS2::scs_sigmaPhiPhi() {return scs_sigmaPhiPhi_handle.get();}
const std::vector<float>& CMS2::scs_timeSeed() {return scs_timeSeed_handle.get();}
const std::vector<float>& CMS2::svs_anglePV() {return svs_anglePV_handle.get();}
const std::vector<float>& CMS2::svs_chi2() {return svs_chi2_handle.get();}
const std::vector<float>& CMS2::svs_dist3Dsig() {return svs_dist3Dsig_handle.get();}
const std::vector<float>& CMS2::svs_dist3Dval() {return svs_dist3Dval_handle.get();}
const std::vector<float>& CMS2::svs_distXYsig() {return svs_distXYsig_handle.get();}
const std::vector<float>& CMS2::svs_distXYval() {return svs_distXYval_handle.get();}
const std::vector<float>& CMS2::svs_ndof() {return svs_ndof_handle.get();}
const std::vector<float>& CMS2::svs_prob() {return svs_prob_handle.get();}
const std::vector<float>& CMS2::svs_xError() {return svs_xError_handle.get();}
const std::vector<float>& CMS2::svs_yError() {return svs_yError_handle.get();}
const std::vector<float>& CMS2::svs_zError() {return svs_zError_handle.get();}
const std::vector<float>& CMS2::mus_tcmet_deltax() {return mus_tcmet_deltax_handle.get();}
const std::vector<float>& CMS2::mus_tcmet_deltay() {return mus_tcmet_deltay_handle.get();}
const std::vector<float>& CMS2::pfcands_dzpv() {return pfcands_dzpv_handle.get();}
const std::vector<float>& CMS2::pfcands_trkiso() {return pfcands_trkiso_handle.get();}
const std::vector<float>& CMS2::trks_chi2() {return trks_chi2_handle.get();}
const std::vector<float>& CMS2::trks_d0() {return trks_d0_handle.get();}
const std::vector<float>& CMS2::trks_d0Err() {return trks_d0Err_handle.get();}
const std::vector<float>& CMS2::trks_d0corr() {return trks_d0corr_handle.get();}
const std::vector<float>& CMS2::trks_d0corrPhi() {return trks_d0corrPhi_handle.get();}
const std::vector<float>& CMS2::trks_d0phiCov() {return trks_d0phiCov_handle.get();}
const std::vector<float>& CMS2::trks_etaErr() {return trks_etaErr_handle.get();}
const std::vector<float>& CMS2::trks_layer1_charge() {return trks_layer1_charge_handle.get();}
const std::vector<float>& CMS2::trks_ndof() {return trks_ndof_handle.get();}
const std::vector<float>& CMS2::trks_phiErr() {return trks_phiErr_handle.get();}
const std::vector<float>& CMS2::trks_ptErr() {return trks_ptErr_handle.get();}
const std::vector<float>& CMS2::trks_validFraction() {return trks_validFraction_handle.get();}
const std::vector<float>& CMS2::trks_z0() {return trks_z0_handle.get();}
const std::vector<float>& CMS2::trks_z0Err() {return trks_z0Err_handle.get();}
const std::vector<float>& CMS2::trks_z0corr() {return trks_z0corr_handle.get();}
const std::vector<float>& CMS2::trkjets_cor() {return trkjets_cor_handle.get();}
const std::vector<float>& CMS2::trks_d0Errvtx() {return trks_d0Errvtx_handle.get();}
const std::vector<float>& CMS2::trks_d0vtx() {return trks_d0vtx_handle.get();}
const std::vector<float>& CMS2::vtxs_chi2() {return vtxs_chi2_handle.get();}
const std::vector<float>& CMS2::vtxs_ndof() {return vtxs_ndof_handle.get();}
const std::vector<float>& CMS2::vtxs_sumpt() {return vtxs_sumpt_handle.get();}
const std::vector<float>& CMS2::vtxs_xError() {return vtxs_xError_handle.get();}
const std::vector<float>& CMS2::vtxs_yError() {return vtxs_yError_handle.get();}
const std::vector<float>& CMS2::vtxs_zError() {return vtxs_zError_handle.get();}
const std::vector<float>& CMS2::bsvtxs_chi2() {return bsvtxs_chi2_handle.get();}
const std::vector<float>& CMS2::bsvtxs_ndof() {return bsvtxs_ndof_handle.get();}
const std::vector<float>& CMS2::bsvtxs_sumpt() {return bsvtxs_sumpt_handle.get();}
const std::vector<float>& CMS2::bsvtxs_xError() {return bsvtxs_xError_handle.get();}
const std::vector<float>& CMS2::bsvtxs_yError() {return bsvtxs_yError_handle.get();}
const std::vector<float>& CMS2::bsvtxs_zError() {return bsvtxs_zError_handle.get();}
const std::vector<std::vector<float> >& CMS2::els_convs_dcot() {return els_convs_dcot_handle.get();}
const std::vector<std::vector<float> >& CMS2::els_convs_dist() {return els_convs_dist_handle.get();}
const std::vector<std::vector<float> >& CMS2::els_convs_radius() {return els_convs_radius_handle.get();}
const std::vector<std::vector<float> >& CMS2::mus_stationShowerDeltaR() {return mus_stationShowerDeltaR_handle.get();}
const std::vector<std::vector<float> >& CMS2::mus_stationShowerSizeT() {return mus_stationShowerSizeT_handle.get();}
const std::vector<std::vector<float> >& CMS2::puInfo_instLumi() {return puInfo_instLumi_handle.get();}
const std::vector<std::vector<float> >& CMS2::puInfo_sump_highpt() {return puInfo_sump_highpt_handle.get();}
const std::vector<std::vector<float> >& CMS2::puInfo_sumpt_lowpt() {return puInfo_sumpt_lowpt_handle.get();}
const std::vector<std::vector<float> >& CMS2::puInfo_zpositions() {return puInfo_zpositions_handle.get();}
const std::vector<std::vector<float> >& CMS2::vtxs_covMatrix() {return vtxs_covMatrix_handle.get();}
const std::vector<std::vector<float> >& CMS2::bsvtxs_covMatrix() {return bsvtxs_covMatrix_handle.get();}
const int& CMS2::evt_cscLooseHaloId() {return evt_cscLooseHaloId_handle.get();}
const int& CMS2::evt_cscTightHaloId() {return evt_cscTightHaloId_handle.get();}
const int& CMS2::evt_ecalLooseHaloId() {return evt_ecalLooseHaloId_handle.get();}
const int& CMS2::evt_ecalTightHaloId() {return evt_ecalTightHaloId_handle.get();}
const int& CMS2::evt_extremeTightHaloId() {return evt_extremeTightHaloId_handle.get();}
const int& CMS2::evt_globalLooseHaloId() {return evt_globalLooseHaloId_handle.get();}
const int& CMS2::evt_globalTightHaloId() {return evt_globalTightHaloId_handle.get();}
const int& CMS2::evt_hcalLooseHaloId() {return evt_hcalLooseHaloId_handle.get();}
const int& CMS2::evt_hcalTightHaloId() {return evt_hcalTightHaloId_handle.get();}
const int& CMS2::evt_looseHaloId() {return evt_looseHaloId_handle.get();}
const int& CMS2::evt_nHaloLikeTracks() {return evt_nHaloLikeTracks_handle.get();}
const int& CMS2::evt_nHaloTriggerCandidates() {return evt_nHaloTriggerCandidates_handle.get();}
const int& CMS2::evt_tightHaloId() {return evt_tightHaloId_handle.get();}
const int& CMS2::evt_bsType() {return evt_bsType_handle.get();}
const int& CMS2::evt_bunchCrossing() {return evt_bunchCrossing_handle.get();}
const int& CMS2::evt_experimentType() {return evt_experimentType_handle.get();}
const int& CMS2::evt_isRealData() {return evt_isRealData_handle.get();}
const int& CMS2::evt_orbitNumber() {return evt_orbitNumber_handle.get();}
const int& CMS2::evt_storeNumber() {return evt_storeNumber_handle.get();}
const int& CMS2::hcalnoise_GetRecHitCount() {return hcalnoise_GetRecHitCount_handle.get();}
const int& CMS2::hcalnoise_GetRecHitCount15() {return hcalnoise_GetRecHitCount15_handle.get();}
const int& CMS2::hcalnoise_maxHPDHits() {return hcalnoise_maxHPDHits_handle.get();}
const int& CMS2::hcalnoise_maxHPDNoOtherHits() {return hcalnoise_maxHPDNoOtherHits_handle.get();}
const int& CMS2::hcalnoise_maxRBXHits() {return hcalnoise_maxRBXHits_handle.get();}
const int& CMS2::hcalnoise_maxZeros() {return hcalnoise_maxZeros_handle.get();}
const int& CMS2::hcalnoise_noiseFilterStatus() {return hcalnoise_noiseFilterStatus_handle.get();}
const int& CMS2::hcalnoise_noiseType() {return hcalnoise_noiseType_handle.get();}
const int& CMS2::hcalnoise_num10GeVHits() {return hcalnoise_num10GeVHits_handle.get();}
const int& CMS2::hcalnoise_num25GeVHits() {return hcalnoise_num25GeVHits_handle.get();}
const int& CMS2::hcalnoise_numFlatNoiseChannels() {return hcalnoise_numFlatNoiseChannels_handle.get();}
const int& CMS2::hcalnoise_numIsolatedNoiseChannels() {return hcalnoise_numIsolatedNoiseChannels_handle.get();}
const int& CMS2::hcalnoise_numProblematicRBXs() {return hcalnoise_numProblematicRBXs_handle.get();}
const int& CMS2::hcalnoise_numSpikeNoiseChannels() {return hcalnoise_numSpikeNoiseChannels_handle.get();}
const int& CMS2::hcalnoise_numTS4TS5NoiseChannels() {return hcalnoise_numTS4TS5NoiseChannels_handle.get();}
const int& CMS2::hcalnoise_numTriangleNoiseChannels() {return hcalnoise_numTriangleNoiseChannels_handle.get();}
const int& CMS2::hcalnoise_passHighLevelNoiseFilter() {return hcalnoise_passHighLevelNoiseFilter_handle.get();}
const int& CMS2::hcalnoise_passLooseNoiseFilter() {return hcalnoise_passLooseNoiseFilter_handle.get();}
const int& CMS2::hcalnoise_passTightNoiseFilter() {return hcalnoise_passTightNoiseFilter_handle.get();}
const int& CMS2::l1_nemiso() {return l1_nemiso_handle.get();}
const int& CMS2::l1_nemnoiso() {return l1_nemnoiso_handle.get();}
const int& CMS2::l1_njetsc() {return l1_njetsc_handle.get();}
const int& CMS2::l1_njetsf() {return l1_njetsf_handle.get();}
const int& CMS2::l1_njetst() {return l1_njetst_handle.get();}
const int& CMS2::l1_nmus() {return l1_nmus_handle.get();}
const int& CMS2::ls_lumiSecQual() {return ls_lumiSecQual_handle.get();}
const int& CMS2::pdfinfo_id1() {return pdfinfo_id1_handle.get();}
const int& CMS2::pdfinfo_id2() {return pdfinfo_id2_handle.get();}
const int& CMS2::sparm_subProcessId() {return sparm_subProcessId_handle.get();}
const std::vector<int>& CMS2::evt_ecaliPhiSuspects() {return evt_ecaliPhiSuspects_handle.get();}
const std::vector<int>& CMS2::evt_globaliPhiSuspects() {return evt_globaliPhiSuspects_handle.get();}
const std::vector<int>& CMS2::evt_hcaliPhiSuspects() {return evt_hcaliPhiSuspects_handle.get();}
const std::vector<int>& CMS2::els_mc3_id() {return els_mc3_id_handle.get();}
const std::vector<int>& CMS2::els_mc3idx() {return els_mc3idx_handle.get();}
const std::vector<int>& CMS2::els_mc3_motherid() {return els_mc3_motherid_handle.get();}
const std::vector<int>& CMS2::els_mc3_motheridx() {return els_mc3_motheridx_handle.get();}
const std::vector<int>& CMS2::els_mc_id() {return els_mc_id_handle.get();}
const std::vector<int>& CMS2::els_mcidx() {return els_mcidx_handle.get();}
const std::vector<int>& CMS2::els_mc_motherid() {return els_mc_motherid_handle.get();}
const std::vector<int>& CMS2::jets_mc3_id() {return jets_mc3_id_handle.get();}
const std::vector<int>& CMS2::jets_mc3idx() {return jets_mc3idx_handle.get();}
const std::vector<int>& CMS2::jets_mc_gpidx() {return jets_mc_gpidx_handle.get();}
const std::vector<int>& CMS2::jets_mc_id() {return jets_mc_id_handle.get();}
const std::vector<int>& CMS2::jets_mcidx() {return jets_mcidx_handle.get();}
const std::vector<int>& CMS2::jets_mc_motherid() {return jets_mc_motherid_handle.get();}
const std::vector<int>& CMS2::mus_mc3_id() {return mus_mc3_id_handle.get();}
const std::vector<int>& CMS2::mus_mc3idx() {return mus_mc3idx_handle.get();}
const std::vector<int>& CMS2::mus_mc3_motherid() {return mus_mc3_motherid_handle.get();}
const std::vector<int>& CMS2::mus_mc3_motheridx() {return mus_mc3_motheridx_handle.get();}
const std::vector<int>& CMS2::mus_mc_id() {return mus_mc_id_handle.get();}
const std::vector<int>& CMS2::mus_mcidx() {return mus_mcidx_handle.get();}
const std::vector<int>& CMS2::mus_mc_motherid() {return mus_mc_motherid_handle.get();}
const std::vector<int>& CMS2::pfjets_mc3_id() {return pfjets_mc3_id_handle.get();}
const std::vector<int>& CMS2::pfjets_mc3idx() {return pfjets_mc3idx_handle.get();}
const std::vector<int>& CMS2::pfjets_mc_gpidx() {return pfjets_mc_gpidx_handle.get();}
const std::vector<int>& CMS2::pfjets_mc_id() {return pfjets_mc_id_handle.get();}
const std::vector<int>& CMS2::pfjets_mcidx() {return pfjets_mcidx_handle.get();}
const std::vector<int>& CMS2::pfjets_mc_motherid() {return pfjets_mc_motherid_handle.get();}
const std::vector<int>& CMS2::photons_mc3_id() {return photons_mc3_id_handle.get();}
const std::vector<int>& CMS2::photons_mc3idx() {return photons_mc3idx_handle.get();}
const std::vector<int>& CMS2::photons_mc3_motherid() {return photons_mc3_motherid_handle.get();}
const std::vector<int>& CMS2::photons_mc3_motheridx() {return photons_mc3_motheridx_handle.get();}
const std::vector<int>& CMS2::photons_mc_id() {return photons_mc_id_handle.get();}
const std::vector<int>& CMS2::photons_mcidx() {return photons_mcidx_handle.get();}
const std::vector<int>& CMS2::photons_mc_motherid() {return photons_mc_motherid_handle.get();}
const std::vector<int>& CMS2::trk_mc3_id() {return trk_mc3_id_handle.get();}
const std::vector<int>& CMS2::trk_mc3idx() {return trk_mc3idx_handle.get();}
const std::vector<int>& CMS2::trk_mc3_motherid() {return trk_mc3_motherid_handle.get();}
const std::vector<int>& CMS2::trk_mc3_motheridx() {return trk_mc3_motheridx_handle.get();}
const std::vector<int>& CMS2::trk_mc_id() {return trk_mc_id_handle.get();}
const std::vector<int>& CMS2::trk_mcidx() {return trk_mcidx_handle.get();}
const std::vector<int>& CMS2::trk_mc_motherid() {return trk_mc_motherid_handle.get();}
const std::vector<int>& CMS2::els_closestJet() {return els_closestJet_handle.get();}
const std::vector<int>& CMS2::els_closestMuon() {return els_closestMuon_handle.get();}
const std::vector<int>& CMS2::els_pfelsidx() {return els_pfelsidx_handle.get();}
const std::vector<int>& CMS2::els_category() {return els_category_handle.get();}
const std::vector<int>& CMS2::els_charge() {return els_charge_handle.get();}
const std::vector<int>& CMS2::els_ckf_laywithmeas() {return els_ckf_laywithmeas_handle.get();}
const std::vector<int>& CMS2::els_class() {return els_class_handle.get();}
const std::vector<int>& CMS2::els_conv_delMissHits() {return els_conv_delMissHits_handle.get();}
const std::vector<int>& CMS2::els_conv_flag() {return els_conv_flag_handle.get();}
const std::vector<int>& CMS2::els_conv_gsftkidx() {return els_conv_gsftkidx_handle.get();}
const std::vector<int>& CMS2::els_conv_old_delMissHits() {return els_conv_old_delMissHits_handle.get();}
const std::vector<int>& CMS2::els_conv_old_flag() {return els_conv_old_flag_handle.get();}
const std::vector<int>& CMS2::els_conv_old_gsftkidx() {return els_conv_old_gsftkidx_handle.get();}
const std::vector<int>& CMS2::els_conv_old_tkidx() {return els_conv_old_tkidx_handle.get();}
const std::vector<int>& CMS2::els_conv_tkidx() {return els_conv_tkidx_handle.get();}
const std::vector<int>& CMS2::els_exp_innerlayers() {return els_exp_innerlayers_handle.get();}
const std::vector<int>& CMS2::els_exp_outerlayers() {return els_exp_outerlayers_handle.get();}
const std::vector<int>& CMS2::els_fiduciality() {return els_fiduciality_handle.get();}
const std::vector<int>& CMS2::els_gsftrkidx() {return els_gsftrkidx_handle.get();}
const std::vector<int>& CMS2::els_layer1_det() {return els_layer1_det_handle.get();}
const std::vector<int>& CMS2::els_layer1_layer() {return els_layer1_layer_handle.get();}
const std::vector<int>& CMS2::els_layer1_sizerphi() {return els_layer1_sizerphi_handle.get();}
const std::vector<int>& CMS2::els_layer1_sizerz() {return els_layer1_sizerz_handle.get();}
const std::vector<int>& CMS2::els_lostHits() {return els_lostHits_handle.get();}
const std::vector<int>& CMS2::els_lost_pixelhits() {return els_lost_pixelhits_handle.get();}
const std::vector<int>& CMS2::els_nSeed() {return els_nSeed_handle.get();}
const std::vector<int>& CMS2::els_sccharge() {return els_sccharge_handle.get();}
const std::vector<int>& CMS2::els_scindex() {return els_scindex_handle.get();}
const std::vector<int>& CMS2::els_trk_charge() {return els_trk_charge_handle.get();}
const std::vector<int>& CMS2::els_trkidx() {return els_trkidx_handle.get();}
const std::vector<int>& CMS2::els_type() {return els_type_handle.get();}
const std::vector<int>& CMS2::els_validHits() {return els_validHits_handle.get();}
const std::vector<int>& CMS2::els_valid_pixelhits() {return els_valid_pixelhits_handle.get();}
const std::vector<int>& CMS2::genps_id() {return genps_id_handle.get();}
const std::vector<int>& CMS2::genps_id_mother() {return genps_id_mother_handle.get();}
const std::vector<int>& CMS2::genps_status() {return genps_status_handle.get();}
const std::vector<int>& CMS2::gsftrks_charge() {return gsftrks_charge_handle.get();}
const std::vector<int>& CMS2::gsftrks_exp_innerlayers() {return gsftrks_exp_innerlayers_handle.get();}
const std::vector<int>& CMS2::gsftrks_exp_outerlayers() {return gsftrks_exp_outerlayers_handle.get();}
const std::vector<int>& CMS2::gsftrks_layer1_det() {return gsftrks_layer1_det_handle.get();}
const std::vector<int>& CMS2::gsftrks_layer1_layer() {return gsftrks_layer1_layer_handle.get();}
const std::vector<int>& CMS2::gsftrks_layer1_sizerphi() {return gsftrks_layer1_sizerphi_handle.get();}
const std::vector<int>& CMS2::gsftrks_layer1_sizerz() {return gsftrks_layer1_sizerz_handle.get();}
const std::vector<int>& CMS2::gsftrks_lostHits() {return gsftrks_lostHits_handle.get();}
const std::vector<int>& CMS2::gsftrks_lost_pixelhits() {return gsftrks_lost_pixelhits_handle.get();}
const std::vector<int>& CMS2::gsftrks_nlayers() {return gsftrks_nlayers_handle.get();}
const std::vector<int>& CMS2::gsftrks_nlayers3D() {return gsftrks_nlayers3D_handle.get();}
const std::vector<int>& CMS2::gsftrks_nlayersLost() {return gsftrks_nlayersLost_handle.get();}
const std::vector<int>& CMS2::gsftrks_validHits() {return gsftrks_validHits_handle.get();}
const std::vector<int>& CMS2::gsftrks_valid_pixelhits() {return gsftrks_valid_pixelhits_handle.get();}
const std::vector<int>& CMS2::hyp_ll_charge() {return hyp_ll_charge_handle.get();}
const std::vector<int>& CMS2::hyp_ll_id() {return hyp_ll_id_handle.get();}
const std::vector<int>& CMS2::hyp_ll_index() {return hyp_ll_index_handle.get();}
const std::vector<int>& CMS2::hyp_ll_lostHits() {return hyp_ll_lostHits_handle.get();}
const std::vector<int>& CMS2::hyp_ll_validHits() {return hyp_ll_validHits_handle.get();}
const std::vector<int>& CMS2::hyp_lt_charge() {return hyp_lt_charge_handle.get();}
const std::vector<int>& CMS2::hyp_lt_id() {return hyp_lt_id_handle.get();}
const std::vector<int>& CMS2::hyp_lt_index() {return hyp_lt_index_handle.get();}
const std::vector<int>& CMS2::hyp_lt_lostHits() {return hyp_lt_lostHits_handle.get();}
const std::vector<int>& CMS2::hyp_lt_validHits() {return hyp_lt_validHits_handle.get();}
const std::vector<int>& CMS2::hyp_njets() {return hyp_njets_handle.get();}
const std::vector<int>& CMS2::hyp_nojets() {return hyp_nojets_handle.get();}
const std::vector<int>& CMS2::hyp_type() {return hyp_type_handle.get();}
const std::vector<int>& CMS2::hyp_FVFit_ndf() {return hyp_FVFit_ndf_handle.get();}
const std::vector<int>& CMS2::hyp_FVFit_status() {return hyp_FVFit_status_handle.get();}
const std::vector<int>& CMS2::hyp_ll_mc_id() {return hyp_ll_mc_id_handle.get();}
const std::vector<int>& CMS2::hyp_ll_mc_motherid() {return hyp_ll_mc_motherid_handle.get();}
const std::vector<int>& CMS2::hyp_lt_mc_id() {return hyp_lt_mc_id_handle.get();}
const std::vector<int>& CMS2::hyp_lt_mc_motherid() {return hyp_lt_mc_motherid_handle.get();}
const std::vector<int>& CMS2::pfjets_mcflavorAlgo() {return pfjets_mcflavorAlgo_handle.get();}
const std::vector<int>& CMS2::pfjets_mcflavorPhys() {return pfjets_mcflavorPhys_handle.get();}
const std::vector<int>& CMS2::jets_closestElectron() {return jets_closestElectron_handle.get();}
const std::vector<int>& CMS2::jets_closestMuon() {return jets_closestMuon_handle.get();}
const std::vector<int>& CMS2::l1_emiso_ieta() {return l1_emiso_ieta_handle.get();}
const std::vector<int>& CMS2::l1_emiso_iphi() {return l1_emiso_iphi_handle.get();}
const std::vector<int>& CMS2::l1_emiso_rawId() {return l1_emiso_rawId_handle.get();}
const std::vector<int>& CMS2::l1_emiso_type() {return l1_emiso_type_handle.get();}
const std::vector<int>& CMS2::l1_emnoiso_ieta() {return l1_emnoiso_ieta_handle.get();}
const std::vector<int>& CMS2::l1_emnoiso_iphi() {return l1_emnoiso_iphi_handle.get();}
const std::vector<int>& CMS2::l1_emnoiso_rawId() {return l1_emnoiso_rawId_handle.get();}
const std::vector<int>& CMS2::l1_emnoiso_type() {return l1_emnoiso_type_handle.get();}
const std::vector<int>& CMS2::l1_jetsc_ieta() {return l1_jetsc_ieta_handle.get();}
const std::vector<int>& CMS2::l1_jetsc_iphi() {return l1_jetsc_iphi_handle.get();}
const std::vector<int>& CMS2::l1_jetsc_rawId() {return l1_jetsc_rawId_handle.get();}
const std::vector<int>& CMS2::l1_jetsc_type() {return l1_jetsc_type_handle.get();}
const std::vector<int>& CMS2::l1_jetsf_ieta() {return l1_jetsf_ieta_handle.get();}
const std::vector<int>& CMS2::l1_jetsf_iphi() {return l1_jetsf_iphi_handle.get();}
const std::vector<int>& CMS2::l1_jetsf_rawId() {return l1_jetsf_rawId_handle.get();}
const std::vector<int>& CMS2::l1_jetsf_type() {return l1_jetsf_type_handle.get();}
const std::vector<int>& CMS2::l1_jetst_ieta() {return l1_jetst_ieta_handle.get();}
const std::vector<int>& CMS2::l1_jetst_iphi() {return l1_jetst_iphi_handle.get();}
const std::vector<int>& CMS2::l1_jetst_rawId() {return l1_jetst_rawId_handle.get();}
const std::vector<int>& CMS2::l1_jetst_type() {return l1_jetst_type_handle.get();}
const std::vector<int>& CMS2::l1_mus_flags() {return l1_mus_flags_handle.get();}
const std::vector<int>& CMS2::l1_mus_q() {return l1_mus_q_handle.get();}
const std::vector<int>& CMS2::l1_mus_qual() {return l1_mus_qual_handle.get();}
const std::vector<int>& CMS2::l1_mus_qualFlags() {return l1_mus_qualFlags_handle.get();}
const std::vector<int>& CMS2::mus_met_flag() {return mus_met_flag_handle.get();}
const std::vector<int>& CMS2::mus_closestEle() {return mus_closestEle_handle.get();}
const std::vector<int>& CMS2::mus_closestJet() {return mus_closestJet_handle.get();}
const std::vector<int>& CMS2::mus_pfmusidx() {return mus_pfmusidx_handle.get();}
const std::vector<int>& CMS2::mus_charge() {return mus_charge_handle.get();}
const std::vector<int>& CMS2::mus_gfit_validHits() {return mus_gfit_validHits_handle.get();}
const std::vector<int>& CMS2::mus_gfit_validSTAHits() {return mus_gfit_validSTAHits_handle.get();}
const std::vector<int>& CMS2::mus_gfit_validSiHits() {return mus_gfit_validSiHits_handle.get();}
const std::vector<int>& CMS2::mus_goodmask() {return mus_goodmask_handle.get();}
const std::vector<int>& CMS2::mus_iso03_ntrk() {return mus_iso03_ntrk_handle.get();}
const std::vector<int>& CMS2::mus_iso05_ntrk() {return mus_iso05_ntrk_handle.get();}
const std::vector<int>& CMS2::mus_lostHits() {return mus_lostHits_handle.get();}
const std::vector<int>& CMS2::mus_muonBestTrackType() {return mus_muonBestTrackType_handle.get();}
const std::vector<int>& CMS2::mus_nOverlaps() {return mus_nOverlaps_handle.get();}
const std::vector<int>& CMS2::mus_nmatches() {return mus_nmatches_handle.get();}
const std::vector<int>& CMS2::mus_numberOfMatchedStations() {return mus_numberOfMatchedStations_handle.get();}
const std::vector<int>& CMS2::mus_overlap0() {return mus_overlap0_handle.get();}
const std::vector<int>& CMS2::mus_overlap1() {return mus_overlap1_handle.get();}
const std::vector<int>& CMS2::mus_pfcharge() {return mus_pfcharge_handle.get();}
const std::vector<int>& CMS2::mus_pfflag() {return mus_pfflag_handle.get();}
const std::vector<int>& CMS2::mus_pfparticleId() {return mus_pfparticleId_handle.get();}
const std::vector<int>& CMS2::mus_pid_PFMuon() {return mus_pid_PFMuon_handle.get();}
const std::vector<int>& CMS2::mus_pid_TM2DCompatibilityLoose() {return mus_pid_TM2DCompatibilityLoose_handle.get();}
const std::vector<int>& CMS2::mus_pid_TM2DCompatibilityTight() {return mus_pid_TM2DCompatibilityTight_handle.get();}
const std::vector<int>& CMS2::mus_pid_TMLastStationLoose() {return mus_pid_TMLastStationLoose_handle.get();}
const std::vector<int>& CMS2::mus_pid_TMLastStationTight() {return mus_pid_TMLastStationTight_handle.get();}
const std::vector<int>& CMS2::mus_sta_validHits() {return mus_sta_validHits_handle.get();}
const std::vector<int>& CMS2::mus_timeDirection() {return mus_timeDirection_handle.get();}
const std::vector<int>& CMS2::mus_timeNumStationsUsed() {return mus_timeNumStationsUsed_handle.get();}
const std::vector<int>& CMS2::mus_trk_charge() {return mus_trk_charge_handle.get();}
const std::vector<int>& CMS2::mus_trkidx() {return mus_trkidx_handle.get();}
const std::vector<int>& CMS2::mus_type() {return mus_type_handle.get();}
const std::vector<int>& CMS2::mus_validHits() {return mus_validHits_handle.get();}
const std::vector<int>& CMS2::pfcands_charge() {return pfcands_charge_handle.get();}
const std::vector<int>& CMS2::pfcands_flag() {return pfcands_flag_handle.get();}
const std::vector<int>& CMS2::pfcands_particleId() {return pfcands_particleId_handle.get();}
const std::vector<int>& CMS2::pfcands_pfelsidx() {return pfcands_pfelsidx_handle.get();}
const std::vector<int>& CMS2::pfcands_pfmusidx() {return pfcands_pfmusidx_handle.get();}
const std::vector<int>& CMS2::pfcands_trkidx() {return pfcands_trkidx_handle.get();}
const std::vector<int>& CMS2::pfcands_vtxidx() {return pfcands_vtxidx_handle.get();}
const std::vector<int>& CMS2::pfels_elsidx() {return pfels_elsidx_handle.get();}
const std::vector<int>& CMS2::pfels_charge() {return pfels_charge_handle.get();}
const std::vector<int>& CMS2::pfels_flag() {return pfels_flag_handle.get();}
const std::vector<int>& CMS2::pfels_particleId() {return pfels_particleId_handle.get();}
const std::vector<int>& CMS2::pfjets_chargedHadronMultiplicity() {return pfjets_chargedHadronMultiplicity_handle.get();}
const std::vector<int>& CMS2::pfjets_chargedMultiplicity() {return pfjets_chargedMultiplicity_handle.get();}
const std::vector<int>& CMS2::pfjets_electronMultiplicity() {return pfjets_electronMultiplicity_handle.get();}
const std::vector<int>& CMS2::pfjets_hfEmMultiplicity() {return pfjets_hfEmMultiplicity_handle.get();}
const std::vector<int>& CMS2::pfjets_hfHadronMultiplicity() {return pfjets_hfHadronMultiplicity_handle.get();}
const std::vector<int>& CMS2::pfjets_muonMultiplicity() {return pfjets_muonMultiplicity_handle.get();}
const std::vector<int>& CMS2::pfjets_neutralHadronMultiplicity() {return pfjets_neutralHadronMultiplicity_handle.get();}
const std::vector<int>& CMS2::pfjets_neutralMultiplicity() {return pfjets_neutralMultiplicity_handle.get();}
const std::vector<int>& CMS2::pfjets_photonMultiplicity() {return pfjets_photonMultiplicity_handle.get();}
const std::vector<int>& CMS2::pfmus_musidx() {return pfmus_musidx_handle.get();}
const std::vector<int>& CMS2::pfmus_charge() {return pfmus_charge_handle.get();}
const std::vector<int>& CMS2::pfmus_flag() {return pfmus_flag_handle.get();}
const std::vector<int>& CMS2::pfmus_particleId() {return pfmus_particleId_handle.get();}
const std::vector<int>& CMS2::taus_pf_charge() {return taus_pf_charge_handle.get();}
const std::vector<int>& CMS2::taus_pf_pfjetIndex() {return taus_pf_pfjetIndex_handle.get();}
const std::vector<int>& CMS2::photons_fiduciality() {return photons_fiduciality_handle.get();}
const std::vector<int>& CMS2::photons_scindex() {return photons_scindex_handle.get();}
const std::vector<int>& CMS2::puInfo_bunchCrossing() {return puInfo_bunchCrossing_handle.get();}
const std::vector<int>& CMS2::puInfo_nPUvertices() {return puInfo_nPUvertices_handle.get();}
const std::vector<int>& CMS2::convs_algo() {return convs_algo_handle.get();}
const std::vector<int>& CMS2::convs_isConverted() {return convs_isConverted_handle.get();}
const std::vector<int>& CMS2::convs_quality() {return convs_quality_handle.get();}
const std::vector<int>& CMS2::scs_detIdSeed() {return scs_detIdSeed_handle.get();}
const std::vector<int>& CMS2::scs_elsidx() {return scs_elsidx_handle.get();}
const std::vector<int>& CMS2::scs_severitySeed() {return scs_severitySeed_handle.get();}
const std::vector<int>& CMS2::svs_isKs() {return svs_isKs_handle.get();}
const std::vector<int>& CMS2::svs_isLambda() {return svs_isLambda_handle.get();}
const std::vector<int>& CMS2::svs_mc3_id() {return svs_mc3_id_handle.get();}
const std::vector<int>& CMS2::svs_nTrks() {return svs_nTrks_handle.get();}
const std::vector<int>& CMS2::mus_tcmet_flag() {return mus_tcmet_flag_handle.get();}
const std::vector<int>& CMS2::trks_algo() {return trks_algo_handle.get();}
const std::vector<int>& CMS2::trks_charge() {return trks_charge_handle.get();}
const std::vector<int>& CMS2::trks_exp_innerlayers() {return trks_exp_innerlayers_handle.get();}
const std::vector<int>& CMS2::trks_exp_outerlayers() {return trks_exp_outerlayers_handle.get();}
const std::vector<int>& CMS2::trks_layer1_det() {return trks_layer1_det_handle.get();}
const std::vector<int>& CMS2::trks_layer1_layer() {return trks_layer1_layer_handle.get();}
const std::vector<int>& CMS2::trks_layer1_sizerphi() {return trks_layer1_sizerphi_handle.get();}
const std::vector<int>& CMS2::trks_layer1_sizerz() {return trks_layer1_sizerz_handle.get();}
const std::vector<int>& CMS2::trks_lostHits() {return trks_lostHits_handle.get();}
const std::vector<int>& CMS2::trks_lost_pixelhits() {return trks_lost_pixelhits_handle.get();}
const std::vector<int>& CMS2::trks_nLoops() {return trks_nLoops_handle.get();}
const std::vector<int>& CMS2::trks_nlayers() {return trks_nlayers_handle.get();}
const std::vector<int>& CMS2::trks_nlayers3D() {return trks_nlayers3D_handle.get();}
const std::vector<int>& CMS2::trks_nlayersLost() {return trks_nlayersLost_handle.get();}
const std::vector<int>& CMS2::trks_pvidx0() {return trks_pvidx0_handle.get();}
const std::vector<int>& CMS2::trks_pvidx1() {return trks_pvidx1_handle.get();}
const std::vector<int>& CMS2::trks_qualityMask() {return trks_qualityMask_handle.get();}
const std::vector<int>& CMS2::trks_validHits() {return trks_validHits_handle.get();}
const std::vector<int>& CMS2::trks_valid_pixelhits() {return trks_valid_pixelhits_handle.get();}
const std::vector<int>& CMS2::trks_elsidx() {return trks_elsidx_handle.get();}
const std::vector<int>& CMS2::trk_musidx() {return trk_musidx_handle.get();}
const std::vector<int>& CMS2::trkjets_ntrks() {return trkjets_ntrks_handle.get();}
const std::vector<int>& CMS2::trkjets_vtxs_idx() {return trkjets_vtxs_idx_handle.get();}
const std::vector<int>& CMS2::vtxs_isFake() {return vtxs_isFake_handle.get();}
const std::vector<int>& CMS2::vtxs_isValid() {return vtxs_isValid_handle.get();}
const std::vector<int>& CMS2::vtxs_tracksSize() {return vtxs_tracksSize_handle.get();}
const std::vector<int>& CMS2::bsvtxs_isFake() {return bsvtxs_isFake_handle.get();}
const std::vector<int>& CMS2::bsvtxs_isValid() {return bsvtxs_isValid_handle.get();}
const std::vector<int>& CMS2::bsvtxs_tracksSize() {return bsvtxs_tracksSize_handle.get();}
const std::vector<std::vector<int> >& CMS2::els_convs_delMissHits() {return els_convs_delMissHits_handle.get();}
const std::vector<std::vector<int> >& CMS2::els_convs_flag() {return els_convs_flag_handle.get();}
const std::vector<std::vector<int> >& CMS2::els_convs_gsftkidx() {return els_convs_gsftkidx_handle.get();}
const std::vector<std::vector<int> >& CMS2::els_convs_tkidx() {return els_convs_tkidx_handle.get();}
const std::vector<std::vector<int> >& CMS2::genps_lepdaughter_id() {return genps_lepdaughter_id_handle.get();}
const std::vector<std::vector<int> >& CMS2::genps_lepdaughter_idx() {return genps_lepdaughter_idx_handle.get();}
const std::vector<std::vector<int> >& CMS2::hlt_trigObjs_id() {return hlt_trigObjs_id_handle.get();}
const std::vector<std::vector<int> >& CMS2::hyp_jets_idx() {return hyp_jets_idx_handle.get();}
const std::vector<std::vector<int> >& CMS2::hyp_other_jets_idx() {return hyp_other_jets_idx_handle.get();}
const std::vector<std::vector<int> >& CMS2::mus_nStationCorrelatedHits() {return mus_nStationCorrelatedHits_handle.get();}
const std::vector<std::vector<int> >& CMS2::mus_nStationHits() {return mus_nStationHits_handle.get();}
const std::vector<std::vector<int> >& CMS2::pfjets_pfcandIndicies() {return pfjets_pfcandIndicies_handle.get();}
const std::vector<std::vector<int> >& CMS2::taus_pf_pfcandIndicies() {return taus_pf_pfcandIndicies_handle.get();}
const std::vector<std::vector<int> >& CMS2::puInfo_ntrks_highpt() {return puInfo_ntrks_highpt_handle.get();}
const std::vector<std::vector<int> >& CMS2::puInfo_ntrks_lowpt() {return puInfo_ntrks_lowpt_handle.get();}
const std::vector<std::vector<int> >& CMS2::convs_nHitsBeforeVtx() {return convs_nHitsBeforeVtx_handle.get();}
const std::vector<std::vector<int> >& CMS2::convs_tkalgo() {return convs_tkalgo_handle.get();}
const std::vector<std::vector<int> >& CMS2::convs_tkidx() {return convs_tkidx_handle.get();}
const unsigned int& CMS2::els_HLT_Ele17_Ele8_L1sL1DoubleEG137_version() {return els_HLT_Ele17_Ele8_L1sL1DoubleEG137_version_handle.get();}
const unsigned int& CMS2::els_HLT_Ele17_Ele8_LeadingLeg_version() {return els_HLT_Ele17_Ele8_LeadingLeg_version_handle.get();}
const unsigned int& CMS2::els_HLT_Ele17_Ele8_Mass50_LeadingLeg_version() {return els_HLT_Ele17_Ele8_Mass50_LeadingLeg_version_handle.get();}
const unsigned int& CMS2::els_HLT_Ele17_Ele8_Mass50_TrailingLeg_version() {return els_HLT_Ele17_Ele8_Mass50_TrailingLeg_version_handle.get();}
const unsigned int& CMS2::els_HLT_Ele17_Ele8_TrailingLeg_version() {return els_HLT_Ele17_Ele8_TrailingLeg_version_handle.get();}
const unsigned int& CMS2::els_HLT_Ele17_Ele8_version() {return els_HLT_Ele17_Ele8_version_handle.get();}
const unsigned int& CMS2::els_HLT_Ele20_SC4_Mass50_LeadingLeg_version() {return els_HLT_Ele20_SC4_Mass50_LeadingLeg_version_handle.get();}
const unsigned int& CMS2::els_HLT_Ele20_SC4_Mass50_TrailingLeg_version() {return els_HLT_Ele20_SC4_Mass50_TrailingLeg_version_handle.get();}
const unsigned int& CMS2::els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_version() {return els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_version_handle.get();}
const unsigned int& CMS2::els_HLT_Ele27_WP80_version() {return els_HLT_Ele27_WP80_version_handle.get();}
const unsigned int& CMS2::els_HLT_Ele32_SC17_Mass50_LeadingLeg_version() {return els_HLT_Ele32_SC17_Mass50_LeadingLeg_version_handle.get();}
const unsigned int& CMS2::els_HLT_Ele32_SC17_Mass50_TrailingLeg_version() {return els_HLT_Ele32_SC17_Mass50_TrailingLeg_version_handle.get();}
const unsigned int& CMS2::els_HLT_Mu17_Ele8_TrailingLeg_version() {return els_HLT_Mu17_Ele8_TrailingLeg_version_handle.get();}
const unsigned int& CMS2::els_HLT_Mu17_Ele8_version() {return els_HLT_Mu17_Ele8_version_handle.get();}
const unsigned int& CMS2::els_HLT_Mu8_Ele17_version() {return els_HLT_Mu8_Ele17_version_handle.get();}
const unsigned int& CMS2::evt_nels() {return evt_nels_handle.get();}
const unsigned int& CMS2::evt_detectorStatus() {return evt_detectorStatus_handle.get();}
const unsigned int& CMS2::evt_event() {return evt_event_handle.get();}
const unsigned int& CMS2::evt_lumiBlock() {return evt_lumiBlock_handle.get();}
const unsigned int& CMS2::evt_run() {return evt_run_handle.get();}
const unsigned int& CMS2::genps_flavorHistoryFilterResult() {return genps_flavorHistoryFilterResult_handle.get();}
const unsigned int& CMS2::evt_ngenjets() {return evt_ngenjets_handle.get();}
const unsigned int& CMS2::genps_signalProcessID() {return genps_signalProcessID_handle.get();}
const unsigned int& CMS2::evt_njets() {return evt_njets_handle.get();}
const unsigned int& CMS2::l1_bits1() {return l1_bits1_handle.get();}
const unsigned int& CMS2::l1_bits2() {return l1_bits2_handle.get();}
const unsigned int& CMS2::l1_bits3() {return l1_bits3_handle.get();}
const unsigned int& CMS2::l1_bits4() {return l1_bits4_handle.get();}
const unsigned int& CMS2::l1_techbits1() {return l1_techbits1_handle.get();}
const unsigned int& CMS2::l1_techbits2() {return l1_techbits2_handle.get();}
const unsigned int& CMS2::ls_lsNumber() {return ls_lsNumber_handle.get();}
const unsigned int& CMS2::ls_numOrbit() {return ls_numOrbit_handle.get();}
const unsigned int& CMS2::ls_startOrbit() {return ls_startOrbit_handle.get();}
const unsigned int& CMS2::mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_version() {return mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_version_handle.get();}
const unsigned int& CMS2::mus_HLT_IsoMu24_eta2p1_version() {return mus_HLT_IsoMu24_eta2p1_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu17_Ele8_LeadingLeg_version() {return mus_HLT_Mu17_Ele8_LeadingLeg_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu17_Ele8_version() {return mus_HLT_Mu17_Ele8_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_version() {return mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu17_Mu8_LeadingLeg_version() {return mus_HLT_Mu17_Mu8_LeadingLeg_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu17_Mu8_TrailingLeg_version() {return mus_HLT_Mu17_Mu8_TrailingLeg_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu17_Mu8_version() {return mus_HLT_Mu17_Mu8_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu17_TkMu8_LeadingLeg_version() {return mus_HLT_Mu17_TkMu8_LeadingLeg_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_version() {return mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu17_TkMu8_TrailingLeg_version() {return mus_HLT_Mu17_TkMu8_TrailingLeg_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu17_TkMu8_version() {return mus_HLT_Mu17_TkMu8_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu8_Ele17_TrailingLeg_version() {return mus_HLT_Mu8_Ele17_TrailingLeg_version_handle.get();}
const unsigned int& CMS2::mus_HLT_Mu8_Ele17_version() {return mus_HLT_Mu8_Ele17_version_handle.get();}
const unsigned int& CMS2::evt_nphotons() {return evt_nphotons_handle.get();}
const unsigned int& CMS2::evt_ecalRecoStatus() {return evt_ecalRecoStatus_handle.get();}
const unsigned int& CMS2::evt_nscs() {return evt_nscs_handle.get();}
const unsigned int& CMS2::evt_ntrkjets() {return evt_ntrkjets_handle.get();}
const unsigned int& CMS2::evt_nvtxs() {return evt_nvtxs_handle.get();}
const unsigned int& CMS2::evt_nbsvtxs() {return evt_nbsvtxs_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele17_Ele8() {return els_HLT_Ele17_Ele8_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele17_Ele8_L1sL1DoubleEG137() {return els_HLT_Ele17_Ele8_L1sL1DoubleEG137_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele17_Ele8_LeadingLeg() {return els_HLT_Ele17_Ele8_LeadingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele17_Ele8_Mass50_LeadingLeg() {return els_HLT_Ele17_Ele8_Mass50_LeadingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele17_Ele8_Mass50_TrailingLeg() {return els_HLT_Ele17_Ele8_Mass50_TrailingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele17_Ele8_TrailingLeg() {return els_HLT_Ele17_Ele8_TrailingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele20_SC4_Mass50_LeadingLeg() {return els_HLT_Ele20_SC4_Mass50_LeadingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele20_SC4_Mass50_TrailingLeg() {return els_HLT_Ele20_SC4_Mass50_TrailingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele27_WP80() {return els_HLT_Ele27_WP80_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22() {return els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele32_SC17_Mass50_LeadingLeg() {return els_HLT_Ele32_SC17_Mass50_LeadingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Ele32_SC17_Mass50_TrailingLeg() {return els_HLT_Ele32_SC17_Mass50_TrailingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Mu17_Ele8() {return els_HLT_Mu17_Ele8_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Mu17_Ele8_TrailingLeg() {return els_HLT_Mu17_Ele8_TrailingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::els_HLT_Mu8_Ele17() {return els_HLT_Mu8_Ele17_handle.get();}
const std::vector<unsigned int>& CMS2::els_id2012ext_loose() {return els_id2012ext_loose_handle.get();}
const std::vector<unsigned int>& CMS2::els_id2012ext_medium() {return els_id2012ext_medium_handle.get();}
const std::vector<unsigned int>& CMS2::els_id2012ext_tight() {return els_id2012ext_tight_handle.get();}
const std::vector<unsigned int>& CMS2::els_id2012ext_veto() {return els_id2012ext_veto_handle.get();}
const std::vector<unsigned int>& CMS2::els_id2012_loose() {return els_id2012_loose_handle.get();}
const std::vector<unsigned int>& CMS2::els_id2012_medium() {return els_id2012_medium_handle.get();}
const std::vector<unsigned int>& CMS2::els_id2012_tight() {return els_id2012_tight_handle.get();}
const std::vector<unsigned int>& CMS2::els_id2012_veto() {return els_id2012_veto_handle.get();}
const std::vector<unsigned int>& CMS2::hlt_prescales() {return hlt_prescales_handle.get();}
const std::vector<unsigned int>& CMS2::l1_prescales() {return l1_prescales_handle.get();}
const std::vector<unsigned int>& CMS2::l1_techtrigprescales() {return l1_techtrigprescales_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_IsoMu24_eta2p1() {return mus_HLT_IsoMu24_eta2p1_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1() {return mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu17_Ele8() {return mus_HLT_Mu17_Ele8_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu17_Ele8_LeadingLeg() {return mus_HLT_Mu17_Ele8_LeadingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu17_Mu8() {return mus_HLT_Mu17_Mu8_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen() {return mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu17_Mu8_LeadingLeg() {return mus_HLT_Mu17_Mu8_LeadingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu17_Mu8_TrailingLeg() {return mus_HLT_Mu17_Mu8_TrailingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu17_TkMu8() {return mus_HLT_Mu17_TkMu8_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu17_TkMu8_LeadingLeg() {return mus_HLT_Mu17_TkMu8_LeadingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu17_TkMu8_TrailingLeg() {return mus_HLT_Mu17_TkMu8_TrailingLeg_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered() {return mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu8_Ele17() {return mus_HLT_Mu8_Ele17_handle.get();}
const std::vector<unsigned int>& CMS2::mus_HLT_Mu8_Ele17_TrailingLeg() {return mus_HLT_Mu8_Ele17_TrailingLeg_handle.get();}
const unsigned long long& CMS2::evt_timestamp() {return evt_timestamp_handle.get();}


namespace tas
{
    bool passHLTTrigger(const TString& trigName) {return cms2.passHLTTrigger(trigName);}
	bool passL1Trigger(const TString& trigName) {return cms2.passL1Trigger(trigName);}

    const TBits& hlt_bits() {return cms2.hlt_bits();}
    const std::vector<TString>& evt_CMS2tag() {return cms2.evt_CMS2tag();}
    const std::vector<TString>& evt_dataset() {return cms2.evt_dataset();}
    const std::vector<TString>& hlt_trigNames() {return cms2.hlt_trigNames();}
    const std::vector<TString>& l1_techtrigNames() {return cms2.l1_techtrigNames();}
    const std::vector<TString>& l1_trigNames() {return cms2.l1_trigNames();}
    const std::vector<TString>& evt_errCategory() {return cms2.evt_errCategory();}
    const std::vector<TString>& evt_errModule() {return cms2.evt_errModule();}
    const std::vector<TString>& evt_errSeverity() {return cms2.evt_errSeverity();}
    const std::vector<TString>& sparm_comment() {return cms2.sparm_comment();}
    const std::vector<TString>& sparm_names() {return cms2.sparm_names();}
    const bool& evt_eventHasHalo() {return cms2.evt_eventHasHalo();}
    const bool& hcalnoise_HasBadRBXTS4TS5() {return cms2.hcalnoise_HasBadRBXTS4TS5();}
    const bool& ls_isValid() {return cms2.ls_isValid();}
    const bool& filt_ecalBE() {return cms2.filt_ecalBE();}
    const bool& filt_ecalDR() {return cms2.filt_ecalDR();}
    const bool& filt_ecalLaser() {return cms2.filt_ecalLaser();}
    const bool& filt_ecalTP() {return cms2.filt_ecalTP();}
    const bool& filt_eeBadSc() {return cms2.filt_eeBadSc();}
    const bool& filt_greedyMuon() {return cms2.filt_greedyMuon();}
    const bool& filt_hcalLaser() {return cms2.filt_hcalLaser();}
    const bool& filt_inconsistentMuon() {return cms2.filt_inconsistentMuon();}
    const bool& filt_jetIDFailure() {return cms2.filt_jetIDFailure();}
    const bool& filt_multiEvent() {return cms2.filt_multiEvent();}
    const bool& filt_trackingFailure() {return cms2.filt_trackingFailure();}
    const bool& evt_hbheFilter() {return cms2.evt_hbheFilter();}
    const std::vector<bool>& els_conv_vtx_flag() {return cms2.els_conv_vtx_flag();}
    const std::vector<bool>& els_passingMvaPreselection() {return cms2.els_passingMvaPreselection();}
    const std::vector<bool>& els_passingPflowPreselection() {return cms2.els_passingPflowPreselection();}
    const std::vector<bool>& mus_isRPCMuon() {return cms2.mus_isRPCMuon();}
    const std::vector<bool>& mus_tightMatch() {return cms2.mus_tightMatch();}
    const std::vector<bool>& mus_updatedSta() {return cms2.mus_updatedSta();}
    const std::vector<bool>& pfcands_isMuIso() {return cms2.pfcands_isMuIso();}
    const std::vector<bool>& photons_haspixelSeed() {return cms2.photons_haspixelSeed();}
    const std::vector<double>& jets_closestElectron_DR() {return cms2.jets_closestElectron_DR();}
    const std::vector<double>& jets_closestMuon_DR() {return cms2.jets_closestMuon_DR();}
    const float& evt_bs_Xwidth() {return cms2.evt_bs_Xwidth();}
    const float& evt_bs_XwidthErr() {return cms2.evt_bs_XwidthErr();}
    const float& evt_bs_Ywidth() {return cms2.evt_bs_Ywidth();}
    const float& evt_bs_YwidthErr() {return cms2.evt_bs_YwidthErr();}
    const float& evt_bs_dxdz() {return cms2.evt_bs_dxdz();}
    const float& evt_bs_dxdzErr() {return cms2.evt_bs_dxdzErr();}
    const float& evt_bs_dydz() {return cms2.evt_bs_dydz();}
    const float& evt_bs_dydzErr() {return cms2.evt_bs_dydzErr();}
    const float& evt_bs_sigmaZ() {return cms2.evt_bs_sigmaZ();}
    const float& evt_bs_sigmaZErr() {return cms2.evt_bs_sigmaZErr();}
    const float& evt_bs_xErr() {return cms2.evt_bs_xErr();}
    const float& evt_bs_yErr() {return cms2.evt_bs_yErr();}
    const float& evt_bs_zErr() {return cms2.evt_bs_zErr();}
    const float& evt_bField() {return cms2.evt_bField();}
    const float& evt_rho() {return cms2.evt_rho();}
    const float& evt_rhoJEC() {return cms2.evt_rhoJEC();}
    const float& evt_fixgrid_all_rho() {return cms2.evt_fixgrid_all_rho();}
    const float& evt_fixgridfastjet_all_rho() {return cms2.evt_fixgridfastjet_all_rho();}
    const float& gen_met() {return cms2.gen_met();}
    const float& gen_metPhi() {return cms2.gen_metPhi();}
    const float& genps_alphaQCD() {return cms2.genps_alphaQCD();}
    const float& genps_pthat() {return cms2.genps_pthat();}
    const float& genps_qScale() {return cms2.genps_qScale();}
    const float& genps_weight() {return cms2.genps_weight();}
    const float& gen_sumEt() {return cms2.gen_sumEt();}
    const float& hcalnoise_GetRecHitEnergy() {return cms2.hcalnoise_GetRecHitEnergy();}
    const float& hcalnoise_GetRecHitEnergy15() {return cms2.hcalnoise_GetRecHitEnergy15();}
    const float& hcalnoise_GetTotalCalibCharge() {return cms2.hcalnoise_GetTotalCalibCharge();}
    const float& hcalnoise_TS4TS5NoiseSumE() {return cms2.hcalnoise_TS4TS5NoiseSumE();}
    const float& hcalnoise_TS4TS5NoiseSumEt() {return cms2.hcalnoise_TS4TS5NoiseSumEt();}
    const float& hcalnoise_eventChargeFraction() {return cms2.hcalnoise_eventChargeFraction();}
    const float& hcalnoise_eventEMEnergy() {return cms2.hcalnoise_eventEMEnergy();}
    const float& hcalnoise_eventEMFraction() {return cms2.hcalnoise_eventEMFraction();}
    const float& hcalnoise_eventHadEnergy() {return cms2.hcalnoise_eventHadEnergy();}
    const float& hcalnoise_eventTrackEnergy() {return cms2.hcalnoise_eventTrackEnergy();}
    const float& hcalnoise_flatNoiseSumE() {return cms2.hcalnoise_flatNoiseSumE();}
    const float& hcalnoise_flatNoiseSumEt() {return cms2.hcalnoise_flatNoiseSumEt();}
    const float& hcalnoise_isolatedNoiseSumE() {return cms2.hcalnoise_isolatedNoiseSumE();}
    const float& hcalnoise_isolatedNoiseSumEt() {return cms2.hcalnoise_isolatedNoiseSumEt();}
    const float& hcalnoise_max10GeVHitTime() {return cms2.hcalnoise_max10GeVHitTime();}
    const float& hcalnoise_max25GeVHitTime() {return cms2.hcalnoise_max25GeVHitTime();}
    const float& hcalnoise_maxE10TS() {return cms2.hcalnoise_maxE10TS();}
    const float& hcalnoise_maxE2Over10TS() {return cms2.hcalnoise_maxE2Over10TS();}
    const float& hcalnoise_maxE2TS() {return cms2.hcalnoise_maxE2TS();}
    const float& hcalnoise_min10GeVHitTime() {return cms2.hcalnoise_min10GeVHitTime();}
    const float& hcalnoise_min25GeVHitTime() {return cms2.hcalnoise_min25GeVHitTime();}
    const float& hcalnoise_minE10TS() {return cms2.hcalnoise_minE10TS();}
    const float& hcalnoise_minE2Over10TS() {return cms2.hcalnoise_minE2Over10TS();}
    const float& hcalnoise_minE2TS() {return cms2.hcalnoise_minE2TS();}
    const float& hcalnoise_minHPDEMF() {return cms2.hcalnoise_minHPDEMF();}
    const float& hcalnoise_minRBXEMF() {return cms2.hcalnoise_minRBXEMF();}
    const float& hcalnoise_rms10GeVHitTime() {return cms2.hcalnoise_rms10GeVHitTime();}
    const float& hcalnoise_rms25GeVHitTime() {return cms2.hcalnoise_rms25GeVHitTime();}
    const float& hcalnoise_spikeNoiseSumE() {return cms2.hcalnoise_spikeNoiseSumE();}
    const float& hcalnoise_spikeNoiseSumEt() {return cms2.hcalnoise_spikeNoiseSumEt();}
    const float& hcalnoise_triangleNoiseSumE() {return cms2.hcalnoise_triangleNoiseSumE();}
    const float& hcalnoise_triangleNoiseSumEt() {return cms2.hcalnoise_triangleNoiseSumEt();}
    const float& evt_kt6calo_central_rho() {return cms2.evt_kt6calo_central_rho();}
    const float& evt_kt6calo_muhlt_rho() {return cms2.evt_kt6calo_muhlt_rho();}
    const float& evt_kt6calo_rho() {return cms2.evt_kt6calo_rho();}
    const float& evt_kt6pf_ctrChargedPU_rho() {return cms2.evt_kt6pf_ctrChargedPU_rho();}
    const float& evt_kt6pf_ctrNeutral_rho() {return cms2.evt_kt6pf_ctrNeutral_rho();}
    const float& evt_kt6pf_ctrNeutralTight_rho() {return cms2.evt_kt6pf_ctrNeutralTight_rho();}
    const float& evt_kt6pf_foregiso_rho() {return cms2.evt_kt6pf_foregiso_rho();}
    const float& l1_met_etTot() {return cms2.l1_met_etTot();}
    const float& l1_met_met() {return cms2.l1_met_met();}
    const float& l1_mht_htTot() {return cms2.l1_mht_htTot();}
    const float& l1_mht_mht() {return cms2.l1_mht_mht();}
    const float& ls_avgInsDelLumi() {return cms2.ls_avgInsDelLumi();}
    const float& ls_avgInsDelLumiErr() {return cms2.ls_avgInsDelLumiErr();}
    const float& ls_avgInsRecLumi() {return cms2.ls_avgInsRecLumi();}
    const float& ls_avgInsRecLumiErr() {return cms2.ls_avgInsRecLumiErr();}
    const float& ls_deadFrac() {return cms2.ls_deadFrac();}
    const float& ls_intgDelLumi() {return cms2.ls_intgDelLumi();}
    const float& ls_intgRecLumi() {return cms2.ls_intgRecLumi();}
    const float& ls_lumiSectionLength() {return cms2.ls_lumiSectionLength();}
    const float& evt_ecalendcapm_met() {return cms2.evt_ecalendcapm_met();}
    const float& evt_ecalendcapm_metPhi() {return cms2.evt_ecalendcapm_metPhi();}
    const float& evt_ecalendcapp_met() {return cms2.evt_ecalendcapp_met();}
    const float& evt_ecalendcapp_metPhi() {return cms2.evt_ecalendcapp_metPhi();}
    const float& evt_ecalmet() {return cms2.evt_ecalmet();}
    const float& evt_ecalmetPhi() {return cms2.evt_ecalmetPhi();}
    const float& evt_endcapm_met() {return cms2.evt_endcapm_met();}
    const float& evt_endcapm_metPhi() {return cms2.evt_endcapm_metPhi();}
    const float& evt_endcapp_met() {return cms2.evt_endcapp_met();}
    const float& evt_endcapp_metPhi() {return cms2.evt_endcapp_metPhi();}
    const float& evt_hcalendcapm_met() {return cms2.evt_hcalendcapm_met();}
    const float& evt_hcalendcapm_metPhi() {return cms2.evt_hcalendcapm_metPhi();}
    const float& evt_hcalendcapp_met() {return cms2.evt_hcalendcapp_met();}
    const float& evt_hcalendcapp_metPhi() {return cms2.evt_hcalendcapp_metPhi();}
    const float& evt_hcalmet() {return cms2.evt_hcalmet();}
    const float& evt_hcalmetPhi() {return cms2.evt_hcalmetPhi();}
    const float& evt_met() {return cms2.evt_met();}
    const float& evt_met_EtGt3() {return cms2.evt_met_EtGt3();}
    const float& evt_metHO() {return cms2.evt_metHO();}
    const float& evt_metHOPhi() {return cms2.evt_metHOPhi();}
    const float& evt_metHOSig() {return cms2.evt_metHOSig();}
    const float& evt_metMuonCorr() {return cms2.evt_metMuonCorr();}
    const float& evt_metMuonCorrPhi() {return cms2.evt_metMuonCorrPhi();}
    const float& evt_metMuonCorrSig() {return cms2.evt_metMuonCorrSig();}
    const float& evt_metMuonJESCorr() {return cms2.evt_metMuonJESCorr();}
    const float& evt_metMuonJESCorrPhi() {return cms2.evt_metMuonJESCorrPhi();}
    const float& evt_metMuonJESCorrSig() {return cms2.evt_metMuonJESCorrSig();}
    const float& evt_metNoHF() {return cms2.evt_metNoHF();}
    const float& evt_metNoHFHO() {return cms2.evt_metNoHFHO();}
    const float& evt_metNoHFHOPhi() {return cms2.evt_metNoHFHOPhi();}
    const float& evt_metNoHFHOSig() {return cms2.evt_metNoHFHOSig();}
    const float& evt_metNoHFPhi() {return cms2.evt_metNoHFPhi();}
    const float& evt_metNoHFSig() {return cms2.evt_metNoHFSig();}
    const float& evt_metOpt() {return cms2.evt_metOpt();}
    const float& evt_metOptHO() {return cms2.evt_metOptHO();}
    const float& evt_metOptHOPhi() {return cms2.evt_metOptHOPhi();}
    const float& evt_metOptHOSig() {return cms2.evt_metOptHOSig();}
    const float& evt_metOptNoHF() {return cms2.evt_metOptNoHF();}
    const float& evt_metOptNoHFHO() {return cms2.evt_metOptNoHFHO();}
    const float& evt_metOptNoHFHOPhi() {return cms2.evt_metOptNoHFHOPhi();}
    const float& evt_metOptNoHFHOSig() {return cms2.evt_metOptNoHFHOSig();}
    const float& evt_metOptNoHFPhi() {return cms2.evt_metOptNoHFPhi();}
    const float& evt_metOptNoHFSig() {return cms2.evt_metOptNoHFSig();}
    const float& evt_metOptPhi() {return cms2.evt_metOptPhi();}
    const float& evt_metOptSig() {return cms2.evt_metOptSig();}
    const float& evt_metPhi() {return cms2.evt_metPhi();}
    const float& evt_metPhi_EtGt3() {return cms2.evt_metPhi_EtGt3();}
    const float& evt_metSig() {return cms2.evt_metSig();}
    const float& evt_sumet() {return cms2.evt_sumet();}
    const float& evt_sumet_EtGt3() {return cms2.evt_sumet_EtGt3();}
    const float& evt_sumetHO() {return cms2.evt_sumetHO();}
    const float& evt_sumetMuonCorr() {return cms2.evt_sumetMuonCorr();}
    const float& evt_sumetMuonJESCorr() {return cms2.evt_sumetMuonJESCorr();}
    const float& evt_sumetNoHF() {return cms2.evt_sumetNoHF();}
    const float& evt_sumetNoHFHO() {return cms2.evt_sumetNoHFHO();}
    const float& evt_sumetOpt() {return cms2.evt_sumetOpt();}
    const float& evt_sumetOptHO() {return cms2.evt_sumetOptHO();}
    const float& evt_sumetOptNoHF() {return cms2.evt_sumetOptNoHF();}
    const float& evt_sumetOptNoHFHO() {return cms2.evt_sumetOptNoHFHO();}
    const float& pdfinfo_pdf1() {return cms2.pdfinfo_pdf1();}
    const float& pdfinfo_pdf2() {return cms2.pdfinfo_pdf2();}
    const float& pdfinfo_scale() {return cms2.pdfinfo_scale();}
    const float& pdfinfo_x1() {return cms2.pdfinfo_x1();}
    const float& pdfinfo_x2() {return cms2.pdfinfo_x2();}
    const float& evt_fixgrid_rho_all() {return cms2.evt_fixgrid_rho_all();}
    const float& evt_fixgrid_rho_ctr() {return cms2.evt_fixgrid_rho_ctr();}
    const float& evt_fixgrid_rho_fwd() {return cms2.evt_fixgrid_rho_fwd();}
    const float& evt_pfmet() {return cms2.evt_pfmet();}
    const float& evt_pfmetPhi() {return cms2.evt_pfmetPhi();}
    const float& evt_pfmetPhi_type1cor() {return cms2.evt_pfmetPhi_type1cor();}
    const float& evt_pfmetSig() {return cms2.evt_pfmetSig();}
    const float& evt_pfmetSignificance() {return cms2.evt_pfmetSignificance();}
    const float& evt_pfmet_type1cor() {return cms2.evt_pfmet_type1cor();}
    const float& evt_pfsumet() {return cms2.evt_pfsumet();}
    const float& sparm_filterEfficiency() {return cms2.sparm_filterEfficiency();}
    const float& sparm_pdfScale() {return cms2.sparm_pdfScale();}
    const float& sparm_pdfWeight1() {return cms2.sparm_pdfWeight1();}
    const float& sparm_pdfWeight2() {return cms2.sparm_pdfWeight2();}
    const float& sparm_weight() {return cms2.sparm_weight();}
    const float& sparm_xsec() {return cms2.sparm_xsec();}
    const float& evt_pf_tcmet() {return cms2.evt_pf_tcmet();}
    const float& evt_pf_tcmetPhi() {return cms2.evt_pf_tcmetPhi();}
    const float& evt_pf_tcmetSig() {return cms2.evt_pf_tcmetSig();}
    const float& evt_pf_tcsumet() {return cms2.evt_pf_tcsumet();}
    const float& evt_tcmet() {return cms2.evt_tcmet();}
    const float& evt_tcmetPhi() {return cms2.evt_tcmetPhi();}
    const float& evt_tcmetSig() {return cms2.evt_tcmetSig();}
    const float& evt_tcsumet() {return cms2.evt_tcsumet();}
    const float& evt_ww_rho_act() {return cms2.evt_ww_rho_act();}
    const float& evt_ww_rho() {return cms2.evt_ww_rho();}
    const float& evt_ww_rho_rnd() {return cms2.evt_ww_rho_rnd();}
    const float& evt_ww_rho_vor() {return cms2.evt_ww_rho_vor();}
    const LorentzVector & evt_bsp4() {return cms2.evt_bsp4();}
    const LorentzVector & l1_met_p4() {return cms2.l1_met_p4();}
    const LorentzVector & l1_mht_p4() {return cms2.l1_mht_p4();}
    const std::vector<LorentzVector >& els_mc_motherp4() {return cms2.els_mc_motherp4();}
    const std::vector<LorentzVector >& els_mc_p4() {return cms2.els_mc_p4();}
    const std::vector<LorentzVector >& jets_mc_gp_p4() {return cms2.jets_mc_gp_p4();}
    const std::vector<LorentzVector >& jets_mc_motherp4() {return cms2.jets_mc_motherp4();}
    const std::vector<LorentzVector >& jets_mc_p4() {return cms2.jets_mc_p4();}
    const std::vector<LorentzVector >& mus_mc_motherp4() {return cms2.mus_mc_motherp4();}
    const std::vector<LorentzVector >& mus_mc_p4() {return cms2.mus_mc_p4();}
    const std::vector<LorentzVector >& pfjets_mc_gp_p4() {return cms2.pfjets_mc_gp_p4();}
    const std::vector<LorentzVector >& pfjets_mc_motherp4() {return cms2.pfjets_mc_motherp4();}
    const std::vector<LorentzVector >& pfjets_mc_p4() {return cms2.pfjets_mc_p4();}
    const std::vector<LorentzVector >& photons_mc_motherp4() {return cms2.photons_mc_motherp4();}
    const std::vector<LorentzVector >& photons_mc_p4() {return cms2.photons_mc_p4();}
    const std::vector<LorentzVector >& trk_mcp4() {return cms2.trk_mcp4();}
    const std::vector<LorentzVector >& els_conv_pos_p4() {return cms2.els_conv_pos_p4();}
    const std::vector<LorentzVector >& els_inner_position() {return cms2.els_inner_position();}
    const std::vector<LorentzVector >& els_outer_position() {return cms2.els_outer_position();}
    const std::vector<LorentzVector >& els_p4() {return cms2.els_p4();}
    const std::vector<LorentzVector >& els_p4In() {return cms2.els_p4In();}
    const std::vector<LorentzVector >& els_p4Out() {return cms2.els_p4Out();}
    const std::vector<LorentzVector >& els_trk_p4() {return cms2.els_trk_p4();}
    const std::vector<LorentzVector >& els_vertex_p4() {return cms2.els_vertex_p4();}
    const std::vector<LorentzVector >& genjets_p4() {return cms2.genjets_p4();}
    const std::vector<LorentzVector >& genps_p4() {return cms2.genps_p4();}
    const std::vector<LorentzVector >& genps_prod_vtx() {return cms2.genps_prod_vtx();}
    const std::vector<LorentzVector >& gsftrks_inner_position() {return cms2.gsftrks_inner_position();}
    const std::vector<LorentzVector >& gsftrks_outer_p4() {return cms2.gsftrks_outer_p4();}
    const std::vector<LorentzVector >& gsftrks_outer_position() {return cms2.gsftrks_outer_position();}
    const std::vector<LorentzVector >& gsftrks_p4() {return cms2.gsftrks_p4();}
    const std::vector<LorentzVector >& gsftrks_vertex_p4() {return cms2.gsftrks_vertex_p4();}
    const std::vector<LorentzVector >& hyp_ll_p4() {return cms2.hyp_ll_p4();}
    const std::vector<LorentzVector >& hyp_ll_trk_p4() {return cms2.hyp_ll_trk_p4();}
    const std::vector<LorentzVector >& hyp_lt_p4() {return cms2.hyp_lt_p4();}
    const std::vector<LorentzVector >& hyp_lt_trk_p4() {return cms2.hyp_lt_trk_p4();}
    const std::vector<LorentzVector >& hyp_p4() {return cms2.hyp_p4();}
    const std::vector<LorentzVector >& hyp_FVFit_p4() {return cms2.hyp_FVFit_p4();}
    const std::vector<LorentzVector >& hyp_FVFit_v4() {return cms2.hyp_FVFit_v4();}
    const std::vector<LorentzVector >& hyp_ll_mc_p4() {return cms2.hyp_ll_mc_p4();}
    const std::vector<LorentzVector >& hyp_lt_mc_p4() {return cms2.hyp_lt_mc_p4();}
    const std::vector<LorentzVector >& jets_p4() {return cms2.jets_p4();}
    const std::vector<LorentzVector >& jets_vertex_p4() {return cms2.jets_vertex_p4();}
    const std::vector<LorentzVector >& l1_emiso_p4() {return cms2.l1_emiso_p4();}
    const std::vector<LorentzVector >& l1_emnoiso_p4() {return cms2.l1_emnoiso_p4();}
    const std::vector<LorentzVector >& l1_jetsc_p4() {return cms2.l1_jetsc_p4();}
    const std::vector<LorentzVector >& l1_jetsf_p4() {return cms2.l1_jetsf_p4();}
    const std::vector<LorentzVector >& l1_jetst_p4() {return cms2.l1_jetst_p4();}
    const std::vector<LorentzVector >& l1_mus_p4() {return cms2.l1_mus_p4();}
    const std::vector<LorentzVector >& mus_ecalpos_p4() {return cms2.mus_ecalpos_p4();}
    const std::vector<LorentzVector >& mus_fitpicky_p4() {return cms2.mus_fitpicky_p4();}
    const std::vector<LorentzVector >& mus_fittev_p4() {return cms2.mus_fittev_p4();}
    const std::vector<LorentzVector >& mus_fittpfms_p4() {return cms2.mus_fittpfms_p4();}
    const std::vector<LorentzVector >& mus_gfit_outerPos_p4() {return cms2.mus_gfit_outerPos_p4();}
    const std::vector<LorentzVector >& mus_gfit_p4() {return cms2.mus_gfit_p4();}
    const std::vector<LorentzVector >& mus_gfit_vertex_p4() {return cms2.mus_gfit_vertex_p4();}
    const std::vector<LorentzVector >& mus_p4() {return cms2.mus_p4();}
    const std::vector<LorentzVector >& mus_pfp4() {return cms2.mus_pfp4();}
    const std::vector<LorentzVector >& mus_pfposAtEcal_p4() {return cms2.mus_pfposAtEcal_p4();}
    const std::vector<LorentzVector >& mus_sta_p4() {return cms2.mus_sta_p4();}
    const std::vector<LorentzVector >& mus_sta_vertex_p4() {return cms2.mus_sta_vertex_p4();}
    const std::vector<LorentzVector >& mus_trk_p4() {return cms2.mus_trk_p4();}
    const std::vector<LorentzVector >& mus_vertex_p4() {return cms2.mus_vertex_p4();}
    const std::vector<LorentzVector >& pfcands_p4() {return cms2.pfcands_p4();}
    const std::vector<LorentzVector >& pfcands_posAtEcal_p4() {return cms2.pfcands_posAtEcal_p4();}
    const std::vector<LorentzVector >& pfels_p4() {return cms2.pfels_p4();}
    const std::vector<LorentzVector >& pfels_posAtEcal_p4() {return cms2.pfels_posAtEcal_p4();}
    const std::vector<LorentzVector >& pfjets_p4() {return cms2.pfjets_p4();}
    const std::vector<LorentzVector >& pfmus_p4() {return cms2.pfmus_p4();}
    const std::vector<LorentzVector >& pfmus_posAtEcal_p4() {return cms2.pfmus_posAtEcal_p4();}
    const std::vector<LorentzVector >& taus_pf_p4() {return cms2.taus_pf_p4();}
    const std::vector<LorentzVector >& photons_p4() {return cms2.photons_p4();}
    const std::vector<LorentzVector >& convs_refitPairMom_p4() {return cms2.convs_refitPairMom_p4();}
    const std::vector<LorentzVector >& convs_vtxpos() {return cms2.convs_vtxpos();}
    const std::vector<LorentzVector >& scs_p4() {return cms2.scs_p4();}
    const std::vector<LorentzVector >& scs_pos_p4() {return cms2.scs_pos_p4();}
    const std::vector<LorentzVector >& scs_vtx_p4() {return cms2.scs_vtx_p4();}
    const std::vector<LorentzVector >& svs_flight() {return cms2.svs_flight();}
    const std::vector<LorentzVector >& svs_mc3_p4() {return cms2.svs_mc3_p4();}
    const std::vector<LorentzVector >& svs_p4() {return cms2.svs_p4();}
    const std::vector<LorentzVector >& svs_position() {return cms2.svs_position();}
    const std::vector<LorentzVector >& svs_refitp4() {return cms2.svs_refitp4();}
    const std::vector<LorentzVector >& trks_inner_position() {return cms2.trks_inner_position();}
    const std::vector<LorentzVector >& trks_outer_p4() {return cms2.trks_outer_p4();}
    const std::vector<LorentzVector >& trks_outer_position() {return cms2.trks_outer_position();}
    const std::vector<LorentzVector >& trks_trk_p4() {return cms2.trks_trk_p4();}
    const std::vector<LorentzVector >& trks_vertex_p4() {return cms2.trks_vertex_p4();}
    const std::vector<LorentzVector >& trkjets_p4() {return cms2.trkjets_p4();}
    const std::vector<LorentzVector >& vtxs_position() {return cms2.vtxs_position();}
    const std::vector<LorentzVector >& bsvtxs_position() {return cms2.bsvtxs_position();}
    const std::vector<std::vector<LorentzVector > >& els_convs_pos_p4() {return cms2.els_convs_pos_p4();}
    const std::vector<std::vector<LorentzVector > >& genps_lepdaughter_p4() {return cms2.genps_lepdaughter_p4();}
    const std::vector<std::vector<LorentzVector > >& hlt_trigObjs_p4() {return cms2.hlt_trigObjs_p4();}
    const std::vector<std::vector<LorentzVector > >& hyp_jets_p4() {return cms2.hyp_jets_p4();}
    const std::vector<std::vector<LorentzVector > >& hyp_other_jets_p4() {return cms2.hyp_other_jets_p4();}
    const std::vector<float>& jpts_combinedSecondaryVertexBJetTag() {return cms2.jpts_combinedSecondaryVertexBJetTag();}
    const std::vector<float>& jpts_combinedSecondaryVertexMVABJetTag() {return cms2.jpts_combinedSecondaryVertexMVABJetTag();}
    const std::vector<float>& jpts_jetBProbabilityBJetTag() {return cms2.jpts_jetBProbabilityBJetTag();}
    const std::vector<float>& jpts_jetProbabilityBJetTag() {return cms2.jpts_jetProbabilityBJetTag();}
    const std::vector<float>& jpts_simpleSecondaryVertexBJetTag() {return cms2.jpts_simpleSecondaryVertexBJetTag();}
    const std::vector<float>& jpts_simpleSecondaryVertexHighEffBJetTag() {return cms2.jpts_simpleSecondaryVertexHighEffBJetTag();}
    const std::vector<float>& jpts_simpleSecondaryVertexHighPurBJetTags() {return cms2.jpts_simpleSecondaryVertexHighPurBJetTags();}
    const std::vector<float>& jpts_softElectronByIP3dBJetTag() {return cms2.jpts_softElectronByIP3dBJetTag();}
    const std::vector<float>& jpts_softElectronByPtBJetTag() {return cms2.jpts_softElectronByPtBJetTag();}
    const std::vector<float>& jpts_softElectronTag() {return cms2.jpts_softElectronTag();}
    const std::vector<float>& jpts_softMuonBJetTag() {return cms2.jpts_softMuonBJetTag();}
    const std::vector<float>& jpts_softMuonByIP3dBJetTag() {return cms2.jpts_softMuonByIP3dBJetTag();}
    const std::vector<float>& jpts_softMuonByPtBJetTag() {return cms2.jpts_softMuonByPtBJetTag();}
    const std::vector<float>& jpts_trackCountingHighEffBJetTag() {return cms2.jpts_trackCountingHighEffBJetTag();}
    const std::vector<float>& jpts_trackCountingHighPurBJetTag() {return cms2.jpts_trackCountingHighPurBJetTag();}
    const std::vector<float>& jets_combinedSecondaryVertexBJetTag() {return cms2.jets_combinedSecondaryVertexBJetTag();}
    const std::vector<float>& jets_combinedSecondaryVertexMVABJetTag() {return cms2.jets_combinedSecondaryVertexMVABJetTag();}
    const std::vector<float>& jets_jetBProbabilityBJetTag() {return cms2.jets_jetBProbabilityBJetTag();}
    const std::vector<float>& jets_jetProbabilityBJetTag() {return cms2.jets_jetProbabilityBJetTag();}
    const std::vector<float>& jets_simpleSecondaryVertexBJetTag() {return cms2.jets_simpleSecondaryVertexBJetTag();}
    const std::vector<float>& jets_simpleSecondaryVertexHighEffBJetTag() {return cms2.jets_simpleSecondaryVertexHighEffBJetTag();}
    const std::vector<float>& jets_simpleSecondaryVertexHighPurBJetTags() {return cms2.jets_simpleSecondaryVertexHighPurBJetTags();}
    const std::vector<float>& jets_softElectronByIP3dBJetTag() {return cms2.jets_softElectronByIP3dBJetTag();}
    const std::vector<float>& jets_softElectronByPtBJetTag() {return cms2.jets_softElectronByPtBJetTag();}
    const std::vector<float>& jets_softElectronTag() {return cms2.jets_softElectronTag();}
    const std::vector<float>& jets_softMuonBJetTag() {return cms2.jets_softMuonBJetTag();}
    const std::vector<float>& jets_softMuonByIP3dBJetTag() {return cms2.jets_softMuonByIP3dBJetTag();}
    const std::vector<float>& jets_softMuonByPtBJetTag() {return cms2.jets_softMuonByPtBJetTag();}
    const std::vector<float>& jets_trackCountingHighEffBJetTag() {return cms2.jets_trackCountingHighEffBJetTag();}
    const std::vector<float>& jets_trackCountingHighPurBJetTag() {return cms2.jets_trackCountingHighPurBJetTag();}
    const std::vector<float>& pfjets_combinedSecondaryVertexBJetTag() {return cms2.pfjets_combinedSecondaryVertexBJetTag();}
    const std::vector<float>& pfjets_combinedSecondaryVertexMVABJetTag() {return cms2.pfjets_combinedSecondaryVertexMVABJetTag();}
    const std::vector<float>& pfjets_jetBProbabilityBJetTag() {return cms2.pfjets_jetBProbabilityBJetTag();}
    const std::vector<float>& pfjets_jetProbabilityBJetTag() {return cms2.pfjets_jetProbabilityBJetTag();}
    const std::vector<float>& pfjets_simpleSecondaryVertexBJetTag() {return cms2.pfjets_simpleSecondaryVertexBJetTag();}
    const std::vector<float>& pfjets_simpleSecondaryVertexHighEffBJetTag() {return cms2.pfjets_simpleSecondaryVertexHighEffBJetTag();}
    const std::vector<float>& pfjets_simpleSecondaryVertexHighPurBJetTags() {return cms2.pfjets_simpleSecondaryVertexHighPurBJetTags();}
    const std::vector<float>& pfjets_softElectronByIP3dBJetTag() {return cms2.pfjets_softElectronByIP3dBJetTag();}
    const std::vector<float>& pfjets_softElectronByPtBJetTag() {return cms2.pfjets_softElectronByPtBJetTag();}
    const std::vector<float>& pfjets_softElectronTag() {return cms2.pfjets_softElectronTag();}
    const std::vector<float>& pfjets_softMuonBJetTag() {return cms2.pfjets_softMuonBJetTag();}
    const std::vector<float>& pfjets_softMuonByIP3dBJetTag() {return cms2.pfjets_softMuonByIP3dBJetTag();}
    const std::vector<float>& pfjets_softMuonByPtBJetTag() {return cms2.pfjets_softMuonByPtBJetTag();}
    const std::vector<float>& pfjets_trackCountingHighEffBJetTag() {return cms2.pfjets_trackCountingHighEffBJetTag();}
    const std::vector<float>& pfjets_trackCountingHighPurBJetTag() {return cms2.pfjets_trackCountingHighPurBJetTag();}
    const std::vector<float>& trkjets_combinedSecondaryVertexBJetTag() {return cms2.trkjets_combinedSecondaryVertexBJetTag();}
    const std::vector<float>& trkjets_combinedSecondaryVertexMVABJetTag() {return cms2.trkjets_combinedSecondaryVertexMVABJetTag();}
    const std::vector<float>& trkjets_jetBProbabilityBJetTag() {return cms2.trkjets_jetBProbabilityBJetTag();}
    const std::vector<float>& trkjets_jetProbabilityBJetTag() {return cms2.trkjets_jetProbabilityBJetTag();}
    const std::vector<float>& trkjets_simpleSecondaryVertexBJetTag() {return cms2.trkjets_simpleSecondaryVertexBJetTag();}
    const std::vector<float>& trkjets_simpleSecondaryVertexHighEffBJetTag() {return cms2.trkjets_simpleSecondaryVertexHighEffBJetTag();}
    const std::vector<float>& trkjets_simpleSecondaryVertexHighPurBJetTags() {return cms2.trkjets_simpleSecondaryVertexHighPurBJetTags();}
    const std::vector<float>& trkjets_softElectronByIP3dBJetTag() {return cms2.trkjets_softElectronByIP3dBJetTag();}
    const std::vector<float>& trkjets_softElectronByPtBJetTag() {return cms2.trkjets_softElectronByPtBJetTag();}
    const std::vector<float>& trkjets_softElectronTag() {return cms2.trkjets_softElectronTag();}
    const std::vector<float>& trkjets_softMuonBJetTag() {return cms2.trkjets_softMuonBJetTag();}
    const std::vector<float>& trkjets_softMuonByIP3dBJetTag() {return cms2.trkjets_softMuonByIP3dBJetTag();}
    const std::vector<float>& trkjets_softMuonByPtBJetTag() {return cms2.trkjets_softMuonByPtBJetTag();}
    const std::vector<float>& trkjets_trackCountingHighEffBJetTag() {return cms2.trkjets_trackCountingHighEffBJetTag();}
    const std::vector<float>& trkjets_trackCountingHighPurBJetTag() {return cms2.trkjets_trackCountingHighPurBJetTag();}
    const std::vector<float>& evt_bs_covMatrix() {return cms2.evt_bs_covMatrix();}
    const std::vector<float>& els_mc3dr() {return cms2.els_mc3dr();}
    const std::vector<float>& els_mcdr() {return cms2.els_mcdr();}
    const std::vector<float>& jets_mc3dr() {return cms2.jets_mc3dr();}
    const std::vector<float>& jets_mcdr() {return cms2.jets_mcdr();}
    const std::vector<float>& jets_mc_emEnergy() {return cms2.jets_mc_emEnergy();}
    const std::vector<float>& jets_mc_gpdr() {return cms2.jets_mc_gpdr();}
    const std::vector<float>& jets_mc_hadEnergy() {return cms2.jets_mc_hadEnergy();}
    const std::vector<float>& jets_mc_invEnergy() {return cms2.jets_mc_invEnergy();}
    const std::vector<float>& jets_mc_otherEnergy() {return cms2.jets_mc_otherEnergy();}
    const std::vector<float>& mus_mc3dr() {return cms2.mus_mc3dr();}
    const std::vector<float>& mus_mcdr() {return cms2.mus_mcdr();}
    const std::vector<float>& pfjets_mc3dr() {return cms2.pfjets_mc3dr();}
    const std::vector<float>& pfjets_mcdr() {return cms2.pfjets_mcdr();}
    const std::vector<float>& pfjets_mc_emEnergy() {return cms2.pfjets_mc_emEnergy();}
    const std::vector<float>& pfjets_mc_gpdr() {return cms2.pfjets_mc_gpdr();}
    const std::vector<float>& pfjets_mc_hadEnergy() {return cms2.pfjets_mc_hadEnergy();}
    const std::vector<float>& pfjets_mc_invEnergy() {return cms2.pfjets_mc_invEnergy();}
    const std::vector<float>& pfjets_mc_otherEnergy() {return cms2.pfjets_mc_otherEnergy();}
    const std::vector<float>& photons_mc3dr() {return cms2.photons_mc3dr();}
    const std::vector<float>& photons_mcdr() {return cms2.photons_mcdr();}
    const std::vector<float>& trk_mc3dr() {return cms2.trk_mc3dr();}
    const std::vector<float>& trk_mcdr() {return cms2.trk_mcdr();}
    const std::vector<float>& els_ecalJuraIso() {return cms2.els_ecalJuraIso();}
    const std::vector<float>& els_ecalJuraTowerIso() {return cms2.els_ecalJuraTowerIso();}
    const std::vector<float>& els_hcalConeIso() {return cms2.els_hcalConeIso();}
    const std::vector<float>& els_tkJuraIso() {return cms2.els_tkJuraIso();}
    const std::vector<float>& els_jetdr() {return cms2.els_jetdr();}
    const std::vector<float>& els_musdr() {return cms2.els_musdr();}
    const std::vector<float>& els_isoR03_chpf_radial() {return cms2.els_isoR03_chpf_radial();}
    const std::vector<float>& els_isoR03_chpf_radialTight() {return cms2.els_isoR03_chpf_radialTight();}
    const std::vector<float>& els_isoR03_chpf_radialTight_bv() {return cms2.els_isoR03_chpf_radialTight_bv();}
    const std::vector<float>& els_isoR03_chpf_radial_bv() {return cms2.els_isoR03_chpf_radial_bv();}
    const std::vector<float>& els_isoR03_empf_radial() {return cms2.els_isoR03_empf_radial();}
    const std::vector<float>& els_isoR03_empf_radialTight() {return cms2.els_isoR03_empf_radialTight();}
    const std::vector<float>& els_isoR03_empf_radialTight_bv() {return cms2.els_isoR03_empf_radialTight_bv();}
    const std::vector<float>& els_isoR03_empf_radial_bv() {return cms2.els_isoR03_empf_radial_bv();}
    const std::vector<float>& els_isoR03_nhpf_radial() {return cms2.els_isoR03_nhpf_radial();}
    const std::vector<float>& els_isoR03_nhpf_radialTight() {return cms2.els_isoR03_nhpf_radialTight();}
    const std::vector<float>& els_isoR03_nhpf_radialTight_bv() {return cms2.els_isoR03_nhpf_radialTight_bv();}
    const std::vector<float>& els_isoR03_nhpf_radial_bv() {return cms2.els_isoR03_nhpf_radial_bv();}
    const std::vector<float>& els_isoR03_pf2012n0p5_ch() {return cms2.els_isoR03_pf2012n0p5_ch();}
    const std::vector<float>& els_isoR03_pf2012n0p5_em() {return cms2.els_isoR03_pf2012n0p5_em();}
    const std::vector<float>& els_isoR03_pf2012n0p5_nh() {return cms2.els_isoR03_pf2012n0p5_nh();}
    const std::vector<float>& els_isoR03_pf_radial() {return cms2.els_isoR03_pf_radial();}
    const std::vector<float>& els_isoR03_pf_radialTight() {return cms2.els_isoR03_pf_radialTight();}
    const std::vector<float>& els_isoR03_pf_radialTight_bv() {return cms2.els_isoR03_pf_radialTight_bv();}
    const std::vector<float>& els_isoR03_pf_radial_bv() {return cms2.els_isoR03_pf_radial_bv();}
    const std::vector<float>& els_chi2() {return cms2.els_chi2();}
    const std::vector<float>& els_ckf_chi2() {return cms2.els_ckf_chi2();}
    const std::vector<float>& els_ckf_ndof() {return cms2.els_ckf_ndof();}
    const std::vector<float>& els_conv_dcot() {return cms2.els_conv_dcot();}
    const std::vector<float>& els_conv_dist() {return cms2.els_conv_dist();}
    const std::vector<float>& els_conv_old_dcot() {return cms2.els_conv_old_dcot();}
    const std::vector<float>& els_conv_old_dist() {return cms2.els_conv_old_dist();}
    const std::vector<float>& els_conv_old_radius() {return cms2.els_conv_old_radius();}
    const std::vector<float>& els_conv_radius() {return cms2.els_conv_radius();}
    const std::vector<float>& els_d0() {return cms2.els_d0();}
    const std::vector<float>& els_d0Err() {return cms2.els_d0Err();}
    const std::vector<float>& els_d0corr() {return cms2.els_d0corr();}
    const std::vector<float>& els_dEtaIn() {return cms2.els_dEtaIn();}
    const std::vector<float>& els_dEtaOut() {return cms2.els_dEtaOut();}
    const std::vector<float>& els_dPhiIn() {return cms2.els_dPhiIn();}
    const std::vector<float>& els_dPhiInPhiOut() {return cms2.els_dPhiInPhiOut();}
    const std::vector<float>& els_dPhiOut() {return cms2.els_dPhiOut();}
    const std::vector<float>& els_deltaEtaEleClusterTrackAtCalo() {return cms2.els_deltaEtaEleClusterTrackAtCalo();}
    const std::vector<float>& els_deltaPhiEleClusterTrackAtCalo() {return cms2.els_deltaPhiEleClusterTrackAtCalo();}
    const std::vector<float>& els_e1x5() {return cms2.els_e1x5();}
    const std::vector<float>& els_e2x5Max() {return cms2.els_e2x5Max();}
    const std::vector<float>& els_e3x3() {return cms2.els_e3x3();}
    const std::vector<float>& els_e5x5() {return cms2.els_e5x5();}
    const std::vector<float>& els_eMax() {return cms2.els_eMax();}
    const std::vector<float>& els_eOverPIn() {return cms2.els_eOverPIn();}
    const std::vector<float>& els_eOverPOut() {return cms2.els_eOverPOut();}
    const std::vector<float>& els_eSC() {return cms2.els_eSC();}
    const std::vector<float>& els_eSCPresh() {return cms2.els_eSCPresh();}
    const std::vector<float>& els_eSCRaw() {return cms2.els_eSCRaw();}
    const std::vector<float>& els_eSeed() {return cms2.els_eSeed();}
    const std::vector<float>& els_eSeedOverPIn() {return cms2.els_eSeedOverPIn();}
    const std::vector<float>& els_eSeedOverPOut() {return cms2.els_eSeedOverPOut();}
    const std::vector<float>& els_ecalEnergy() {return cms2.els_ecalEnergy();}
    const std::vector<float>& els_ecalEnergyError() {return cms2.els_ecalEnergyError();}
    const std::vector<float>& els_ecalIso() {return cms2.els_ecalIso();}
    const std::vector<float>& els_ecalIso04() {return cms2.els_ecalIso04();}
    const std::vector<float>& els_etaErr() {return cms2.els_etaErr();}
    const std::vector<float>& els_etaSC() {return cms2.els_etaSC();}
    const std::vector<float>& els_etaSCwidth() {return cms2.els_etaSCwidth();}
    const std::vector<float>& els_fbrem() {return cms2.els_fbrem();}
    const std::vector<float>& els_hOverE() {return cms2.els_hOverE();}
    const std::vector<float>& els_hcalDepth1OverEcal() {return cms2.els_hcalDepth1OverEcal();}
    const std::vector<float>& els_hcalDepth1TowerSumEt() {return cms2.els_hcalDepth1TowerSumEt();}
    const std::vector<float>& els_hcalDepth1TowerSumEt04() {return cms2.els_hcalDepth1TowerSumEt04();}
    const std::vector<float>& els_hcalDepth2OverEcal() {return cms2.els_hcalDepth2OverEcal();}
    const std::vector<float>& els_hcalDepth2TowerSumEt() {return cms2.els_hcalDepth2TowerSumEt();}
    const std::vector<float>& els_hcalDepth2TowerSumEt04() {return cms2.els_hcalDepth2TowerSumEt04();}
    const std::vector<float>& els_hcalIso() {return cms2.els_hcalIso();}
    const std::vector<float>& els_hcalIso04() {return cms2.els_hcalIso04();}
    const std::vector<float>& els_ip3d() {return cms2.els_ip3d();}
    const std::vector<float>& els_ip3derr() {return cms2.els_ip3derr();}
    const std::vector<float>& els_iso03_pf() {return cms2.els_iso03_pf();}
    const std::vector<float>& els_iso03_pf2012_ch() {return cms2.els_iso03_pf2012_ch();}
    const std::vector<float>& els_iso03_pf2012_em() {return cms2.els_iso03_pf2012_em();}
    const std::vector<float>& els_iso03_pf2012ext_ch() {return cms2.els_iso03_pf2012ext_ch();}
    const std::vector<float>& els_iso03_pf2012ext_em() {return cms2.els_iso03_pf2012ext_em();}
    const std::vector<float>& els_iso03_pf2012ext_nh() {return cms2.els_iso03_pf2012ext_nh();}
    const std::vector<float>& els_iso03_pf2012_nh() {return cms2.els_iso03_pf2012_nh();}
    const std::vector<float>& els_iso03_pf_ch() {return cms2.els_iso03_pf_ch();}
    const std::vector<float>& els_iso03_pf_gamma05() {return cms2.els_iso03_pf_gamma05();}
    const std::vector<float>& els_iso03_pf_nhad05() {return cms2.els_iso03_pf_nhad05();}
    const std::vector<float>& els_iso04_pf() {return cms2.els_iso04_pf();}
    const std::vector<float>& els_iso04_pf2012_ch() {return cms2.els_iso04_pf2012_ch();}
    const std::vector<float>& els_iso04_pf2012_em() {return cms2.els_iso04_pf2012_em();}
    const std::vector<float>& els_iso04_pf2012ext_ch() {return cms2.els_iso04_pf2012ext_ch();}
    const std::vector<float>& els_iso04_pf2012ext_em() {return cms2.els_iso04_pf2012ext_em();}
    const std::vector<float>& els_iso04_pf2012ext_nh() {return cms2.els_iso04_pf2012ext_nh();}
    const std::vector<float>& els_iso04_pf2012_nh() {return cms2.els_iso04_pf2012_nh();}
    const std::vector<float>& els_iso04_pf_ch() {return cms2.els_iso04_pf_ch();}
    const std::vector<float>& els_iso04_pf_gamma05() {return cms2.els_iso04_pf_gamma05();}
    const std::vector<float>& els_iso04_pf_nhad05() {return cms2.els_iso04_pf_nhad05();}
    const std::vector<float>& els_layer1_charge() {return cms2.els_layer1_charge();}
    const std::vector<float>& els_lh() {return cms2.els_lh();}
    const std::vector<float>& els_mva() {return cms2.els_mva();}
    const std::vector<float>& els_ndof() {return cms2.els_ndof();}
    const std::vector<float>& els_pfChargedHadronIso() {return cms2.els_pfChargedHadronIso();}
    const std::vector<float>& els_pfNeutralHadronIso() {return cms2.els_pfNeutralHadronIso();}
    const std::vector<float>& els_pfPhotonIso() {return cms2.els_pfPhotonIso();}
    const std::vector<float>& els_phiErr() {return cms2.els_phiErr();}
    const std::vector<float>& els_phiSC() {return cms2.els_phiSC();}
    const std::vector<float>& els_phiSCwidth() {return cms2.els_phiSCwidth();}
    const std::vector<float>& els_ptErr() {return cms2.els_ptErr();}
    const std::vector<float>& els_r9() {return cms2.els_r9();}
    const std::vector<float>& els_sigmaEtaEta() {return cms2.els_sigmaEtaEta();}
    const std::vector<float>& els_sigmaIEtaIEta() {return cms2.els_sigmaIEtaIEta();}
    const std::vector<float>& els_sigmaIEtaIEtaSC() {return cms2.els_sigmaIEtaIEtaSC();}
    const std::vector<float>& els_sigmaIEtaIPhi() {return cms2.els_sigmaIEtaIPhi();}
    const std::vector<float>& els_sigmaIPhiIPhi() {return cms2.els_sigmaIPhiIPhi();}
    const std::vector<float>& els_sigmaIPhiIPhiSC() {return cms2.els_sigmaIPhiIPhiSC();}
    const std::vector<float>& els_sigmaIphiIphi() {return cms2.els_sigmaIphiIphi();}
    const std::vector<float>& els_sigmaPhiPhi() {return cms2.els_sigmaPhiPhi();}
    const std::vector<float>& els_tkIso() {return cms2.els_tkIso();}
    const std::vector<float>& els_tkIso04() {return cms2.els_tkIso04();}
    const std::vector<float>& els_trackMomentumError() {return cms2.els_trackMomentumError();}
    const std::vector<float>& els_trkdr() {return cms2.els_trkdr();}
    const std::vector<float>& els_trkshFrac() {return cms2.els_trkshFrac();}
    const std::vector<float>& els_z0() {return cms2.els_z0();}
    const std::vector<float>& els_z0Err() {return cms2.els_z0Err();}
    const std::vector<float>& els_z0corr() {return cms2.els_z0corr();}
    const std::vector<float>& gsftrks_chi2() {return cms2.gsftrks_chi2();}
    const std::vector<float>& gsftrks_d0() {return cms2.gsftrks_d0();}
    const std::vector<float>& gsftrks_d0Err() {return cms2.gsftrks_d0Err();}
    const std::vector<float>& gsftrks_d0corr() {return cms2.gsftrks_d0corr();}
    const std::vector<float>& gsftrks_d0corrPhi() {return cms2.gsftrks_d0corrPhi();}
    const std::vector<float>& gsftrks_d0phiCov() {return cms2.gsftrks_d0phiCov();}
    const std::vector<float>& gsftrks_etaErr() {return cms2.gsftrks_etaErr();}
    const std::vector<float>& gsftrks_layer1_charge() {return cms2.gsftrks_layer1_charge();}
    const std::vector<float>& gsftrks_ndof() {return cms2.gsftrks_ndof();}
    const std::vector<float>& gsftrks_phiErr() {return cms2.gsftrks_phiErr();}
    const std::vector<float>& gsftrks_ptErr() {return cms2.gsftrks_ptErr();}
    const std::vector<float>& gsftrks_z0() {return cms2.gsftrks_z0();}
    const std::vector<float>& gsftrks_z0Err() {return cms2.gsftrks_z0Err();}
    const std::vector<float>& gsftrks_z0corr() {return cms2.gsftrks_z0corr();}
    const std::vector<float>& hyp_Ht() {return cms2.hyp_Ht();}
    const std::vector<float>& hyp_dPhi_nJet_metMuonJESCorr() {return cms2.hyp_dPhi_nJet_metMuonJESCorr();}
    const std::vector<float>& hyp_dPhi_nJet_muCorrMet() {return cms2.hyp_dPhi_nJet_muCorrMet();}
    const std::vector<float>& hyp_dPhi_nJet_tcMet() {return cms2.hyp_dPhi_nJet_tcMet();}
    const std::vector<float>& hyp_dPhi_nJet_unCorrMet() {return cms2.hyp_dPhi_nJet_unCorrMet();}
    const std::vector<float>& hyp_ll_chi2() {return cms2.hyp_ll_chi2();}
    const std::vector<float>& hyp_ll_d0() {return cms2.hyp_ll_d0();}
    const std::vector<float>& hyp_ll_d0Err() {return cms2.hyp_ll_d0Err();}
    const std::vector<float>& hyp_ll_d0corr() {return cms2.hyp_ll_d0corr();}
    const std::vector<float>& hyp_ll_dPhi_metMuonJESCorr() {return cms2.hyp_ll_dPhi_metMuonJESCorr();}
    const std::vector<float>& hyp_ll_dPhi_muCorrMet() {return cms2.hyp_ll_dPhi_muCorrMet();}
    const std::vector<float>& hyp_ll_dPhi_tcMet() {return cms2.hyp_ll_dPhi_tcMet();}
    const std::vector<float>& hyp_ll_dPhi_unCorrMet() {return cms2.hyp_ll_dPhi_unCorrMet();}
    const std::vector<float>& hyp_ll_etaErr() {return cms2.hyp_ll_etaErr();}
    const std::vector<float>& hyp_ll_ndof() {return cms2.hyp_ll_ndof();}
    const std::vector<float>& hyp_ll_phiErr() {return cms2.hyp_ll_phiErr();}
    const std::vector<float>& hyp_ll_ptErr() {return cms2.hyp_ll_ptErr();}
    const std::vector<float>& hyp_ll_z0() {return cms2.hyp_ll_z0();}
    const std::vector<float>& hyp_ll_z0Err() {return cms2.hyp_ll_z0Err();}
    const std::vector<float>& hyp_ll_z0corr() {return cms2.hyp_ll_z0corr();}
    const std::vector<float>& hyp_lt_chi2() {return cms2.hyp_lt_chi2();}
    const std::vector<float>& hyp_lt_d0() {return cms2.hyp_lt_d0();}
    const std::vector<float>& hyp_lt_d0Err() {return cms2.hyp_lt_d0Err();}
    const std::vector<float>& hyp_lt_d0corr() {return cms2.hyp_lt_d0corr();}
    const std::vector<float>& hyp_lt_dPhi_metMuonJESCorr() {return cms2.hyp_lt_dPhi_metMuonJESCorr();}
    const std::vector<float>& hyp_lt_dPhi_muCorrMet() {return cms2.hyp_lt_dPhi_muCorrMet();}
    const std::vector<float>& hyp_lt_dPhi_tcMet() {return cms2.hyp_lt_dPhi_tcMet();}
    const std::vector<float>& hyp_lt_dPhi_unCorrMet() {return cms2.hyp_lt_dPhi_unCorrMet();}
    const std::vector<float>& hyp_lt_etaErr() {return cms2.hyp_lt_etaErr();}
    const std::vector<float>& hyp_lt_ndof() {return cms2.hyp_lt_ndof();}
    const std::vector<float>& hyp_lt_phiErr() {return cms2.hyp_lt_phiErr();}
    const std::vector<float>& hyp_lt_ptErr() {return cms2.hyp_lt_ptErr();}
    const std::vector<float>& hyp_lt_z0() {return cms2.hyp_lt_z0();}
    const std::vector<float>& hyp_lt_z0Err() {return cms2.hyp_lt_z0Err();}
    const std::vector<float>& hyp_lt_z0corr() {return cms2.hyp_lt_z0corr();}
    const std::vector<float>& hyp_mt2_metMuonJESCorr() {return cms2.hyp_mt2_metMuonJESCorr();}
    const std::vector<float>& hyp_mt2_muCorrMet() {return cms2.hyp_mt2_muCorrMet();}
    const std::vector<float>& hyp_mt2_tcMet() {return cms2.hyp_mt2_tcMet();}
    const std::vector<float>& hyp_sumJetPt() {return cms2.hyp_sumJetPt();}
    const std::vector<float>& hyp_FVFit_chi2ndf() {return cms2.hyp_FVFit_chi2ndf();}
    const std::vector<float>& hyp_FVFit_prob() {return cms2.hyp_FVFit_prob();}
    const std::vector<float>& hyp_FVFit_v4cxx() {return cms2.hyp_FVFit_v4cxx();}
    const std::vector<float>& hyp_FVFit_v4cxy() {return cms2.hyp_FVFit_v4cxy();}
    const std::vector<float>& hyp_FVFit_v4cyy() {return cms2.hyp_FVFit_v4cyy();}
    const std::vector<float>& hyp_FVFit_v4czx() {return cms2.hyp_FVFit_v4czx();}
    const std::vector<float>& hyp_FVFit_v4czy() {return cms2.hyp_FVFit_v4czy();}
    const std::vector<float>& hyp_FVFit_v4czz() {return cms2.hyp_FVFit_v4czz();}
    const std::vector<float>& jets_approximatefHPD() {return cms2.jets_approximatefHPD();}
    const std::vector<float>& jets_approximatefRBX() {return cms2.jets_approximatefRBX();}
    const std::vector<float>& jets_cor() {return cms2.jets_cor();}
    const std::vector<float>& jets_corL1FastL2L3() {return cms2.jets_corL1FastL2L3();}
    const std::vector<float>& jets_corL1L2L3() {return cms2.jets_corL1L2L3();}
    const std::vector<float>& jets_emFrac() {return cms2.jets_emFrac();}
    const std::vector<float>& jets_fHPD() {return cms2.jets_fHPD();}
    const std::vector<float>& jets_fRBX() {return cms2.jets_fRBX();}
    const std::vector<float>& jets_fSubDetector1() {return cms2.jets_fSubDetector1();}
    const std::vector<float>& jets_fSubDetector2() {return cms2.jets_fSubDetector2();}
    const std::vector<float>& jets_fSubDetector3() {return cms2.jets_fSubDetector3();}
    const std::vector<float>& jets_fSubDetector4() {return cms2.jets_fSubDetector4();}
    const std::vector<float>& jets_hitsInN90() {return cms2.jets_hitsInN90();}
    const std::vector<float>& jets_n90Hits() {return cms2.jets_n90Hits();}
    const std::vector<float>& jets_nECALTowers() {return cms2.jets_nECALTowers();}
    const std::vector<float>& jets_nHCALTowers() {return cms2.jets_nHCALTowers();}
    const std::vector<float>& jets_restrictedEMF() {return cms2.jets_restrictedEMF();}
    const std::vector<float>& mus_met_deltax() {return cms2.mus_met_deltax();}
    const std::vector<float>& mus_met_deltay() {return cms2.mus_met_deltay();}
    const std::vector<float>& mus_eledr() {return cms2.mus_eledr();}
    const std::vector<float>& mus_jetdr() {return cms2.mus_jetdr();}
    const std::vector<float>& mus_isoR03_chpf_radial() {return cms2.mus_isoR03_chpf_radial();}
    const std::vector<float>& mus_isoR03_chpf_radialTight() {return cms2.mus_isoR03_chpf_radialTight();}
    const std::vector<float>& mus_isoR03_empf_radial() {return cms2.mus_isoR03_empf_radial();}
    const std::vector<float>& mus_isoR03_empf_radialTight() {return cms2.mus_isoR03_empf_radialTight();}
    const std::vector<float>& mus_isoR03_nhpf_radial() {return cms2.mus_isoR03_nhpf_radial();}
    const std::vector<float>& mus_isoR03_nhpf_radialTight() {return cms2.mus_isoR03_nhpf_radialTight();}
    const std::vector<float>& mus_isoR03_pf_radial() {return cms2.mus_isoR03_pf_radial();}
    const std::vector<float>& mus_isoR03_pf_radialTight() {return cms2.mus_isoR03_pf_radialTight();}
    const std::vector<float>& mus_backToBackCompat() {return cms2.mus_backToBackCompat();}
    const std::vector<float>& mus_caloCompatibility() {return cms2.mus_caloCompatibility();}
    const std::vector<float>& mus_chi2() {return cms2.mus_chi2();}
    const std::vector<float>& mus_chi2LocalMomentum() {return cms2.mus_chi2LocalMomentum();}
    const std::vector<float>& mus_chi2LocalPosition() {return cms2.mus_chi2LocalPosition();}
    const std::vector<float>& mus_cosmicCompat() {return cms2.mus_cosmicCompat();}
    const std::vector<float>& mus_d0() {return cms2.mus_d0();}
    const std::vector<float>& mus_d0Err() {return cms2.mus_d0Err();}
    const std::vector<float>& mus_d0corr() {return cms2.mus_d0corr();}
    const std::vector<float>& mus_e_em() {return cms2.mus_e_em();}
    const std::vector<float>& mus_e_emS9() {return cms2.mus_e_emS9();}
    const std::vector<float>& mus_e_had() {return cms2.mus_e_had();}
    const std::vector<float>& mus_e_hadS9() {return cms2.mus_e_hadS9();}
    const std::vector<float>& mus_e_ho() {return cms2.mus_e_ho();}
    const std::vector<float>& mus_e_hoS9() {return cms2.mus_e_hoS9();}
    const std::vector<float>& mus_etaErr() {return cms2.mus_etaErr();}
    const std::vector<float>& mus_gfit_chi2() {return cms2.mus_gfit_chi2();}
    const std::vector<float>& mus_gfit_d0() {return cms2.mus_gfit_d0();}
    const std::vector<float>& mus_gfit_d0Err() {return cms2.mus_gfit_d0Err();}
    const std::vector<float>& mus_gfit_d0corr() {return cms2.mus_gfit_d0corr();}
    const std::vector<float>& mus_gfit_ndof() {return cms2.mus_gfit_ndof();}
    const std::vector<float>& mus_gfit_qoverp() {return cms2.mus_gfit_qoverp();}
    const std::vector<float>& mus_gfit_qoverpError() {return cms2.mus_gfit_qoverpError();}
    const std::vector<float>& mus_gfit_z0() {return cms2.mus_gfit_z0();}
    const std::vector<float>& mus_gfit_z0Err() {return cms2.mus_gfit_z0Err();}
    const std::vector<float>& mus_gfit_z0corr() {return cms2.mus_gfit_z0corr();}
    const std::vector<float>& mus_glbKink() {return cms2.mus_glbKink();}
    const std::vector<float>& mus_glbTrackProbability() {return cms2.mus_glbTrackProbability();}
    const std::vector<float>& mus_globalDeltaEtaPhi() {return cms2.mus_globalDeltaEtaPhi();}
    const std::vector<float>& mus_ip3d() {return cms2.mus_ip3d();}
    const std::vector<float>& mus_ip3derr() {return cms2.mus_ip3derr();}
    const std::vector<float>& mus_iso03_emEt() {return cms2.mus_iso03_emEt();}
    const std::vector<float>& mus_iso03_hadEt() {return cms2.mus_iso03_hadEt();}
    const std::vector<float>& mus_iso03_hoEt() {return cms2.mus_iso03_hoEt();}
    const std::vector<float>& mus_iso03_pf() {return cms2.mus_iso03_pf();}
    const std::vector<float>& mus_iso03_sumPt() {return cms2.mus_iso03_sumPt();}
    const std::vector<float>& mus_iso04_pf() {return cms2.mus_iso04_pf();}
    const std::vector<float>& mus_iso05_emEt() {return cms2.mus_iso05_emEt();}
    const std::vector<float>& mus_iso05_hadEt() {return cms2.mus_iso05_hadEt();}
    const std::vector<float>& mus_iso05_hoEt() {return cms2.mus_iso05_hoEt();}
    const std::vector<float>& mus_iso05_sumPt() {return cms2.mus_iso05_sumPt();}
    const std::vector<float>& mus_isoR03_pf_ChargedHadronPt() {return cms2.mus_isoR03_pf_ChargedHadronPt();}
    const std::vector<float>& mus_isoR03_pf_ChargedParticlePt() {return cms2.mus_isoR03_pf_ChargedParticlePt();}
    const std::vector<float>& mus_isoR03_pf_NeutralHadronEt() {return cms2.mus_isoR03_pf_NeutralHadronEt();}
    const std::vector<float>& mus_isoR03_pf_NeutralHadronEtHighThreshold() {return cms2.mus_isoR03_pf_NeutralHadronEtHighThreshold();}
    const std::vector<float>& mus_isoR03_pf_PUPt() {return cms2.mus_isoR03_pf_PUPt();}
    const std::vector<float>& mus_isoR03_pf_PhotonEt() {return cms2.mus_isoR03_pf_PhotonEt();}
    const std::vector<float>& mus_isoR03_pf_PhotonEtHighThreshold() {return cms2.mus_isoR03_pf_PhotonEtHighThreshold();}
    const std::vector<float>& mus_isoR04_pf_ChargedHadronPt() {return cms2.mus_isoR04_pf_ChargedHadronPt();}
    const std::vector<float>& mus_isoR04_pf_ChargedParticlePt() {return cms2.mus_isoR04_pf_ChargedParticlePt();}
    const std::vector<float>& mus_isoR04_pf_NeutralHadronEt() {return cms2.mus_isoR04_pf_NeutralHadronEt();}
    const std::vector<float>& mus_isoR04_pf_NeutralHadronEtHighThreshold() {return cms2.mus_isoR04_pf_NeutralHadronEtHighThreshold();}
    const std::vector<float>& mus_isoR04_pf_PUPt() {return cms2.mus_isoR04_pf_PUPt();}
    const std::vector<float>& mus_isoR04_pf_PhotonEt() {return cms2.mus_isoR04_pf_PhotonEt();}
    const std::vector<float>& mus_isoR04_pf_PhotonEtHighThreshold() {return cms2.mus_isoR04_pf_PhotonEtHighThreshold();}
    const std::vector<float>& mus_iso_ecalvetoDep() {return cms2.mus_iso_ecalvetoDep();}
    const std::vector<float>& mus_iso_hcalvetoDep() {return cms2.mus_iso_hcalvetoDep();}
    const std::vector<float>& mus_iso_hovetoDep() {return cms2.mus_iso_hovetoDep();}
    const std::vector<float>& mus_iso_trckvetoDep() {return cms2.mus_iso_trckvetoDep();}
    const std::vector<float>& mus_localDistance() {return cms2.mus_localDistance();}
    const std::vector<float>& mus_ndof() {return cms2.mus_ndof();}
    const std::vector<float>& mus_overlapCompat() {return cms2.mus_overlapCompat();}
    const std::vector<float>& mus_pfdeltaP() {return cms2.mus_pfdeltaP();}
    const std::vector<float>& mus_pfecalE() {return cms2.mus_pfecalE();}
    const std::vector<float>& mus_pfhcalE() {return cms2.mus_pfhcalE();}
    const std::vector<float>& mus_pfmva_emu() {return cms2.mus_pfmva_emu();}
    const std::vector<float>& mus_pfmva_epi() {return cms2.mus_pfmva_epi();}
    const std::vector<float>& mus_pfmva_nothing_gamma() {return cms2.mus_pfmva_nothing_gamma();}
    const std::vector<float>& mus_pfmva_nothing_nh() {return cms2.mus_pfmva_nothing_nh();}
    const std::vector<float>& mus_pfmva_pimu() {return cms2.mus_pfmva_pimu();}
    const std::vector<float>& mus_pfpS1E() {return cms2.mus_pfpS1E();}
    const std::vector<float>& mus_pfpS2E() {return cms2.mus_pfpS2E();}
    const std::vector<float>& mus_pfrawEcalE() {return cms2.mus_pfrawEcalE();}
    const std::vector<float>& mus_pfrawHcalE() {return cms2.mus_pfrawHcalE();}
    const std::vector<float>& mus_phiErr() {return cms2.mus_phiErr();}
    const std::vector<float>& mus_ptErr() {return cms2.mus_ptErr();}
    const std::vector<float>& mus_qoverp() {return cms2.mus_qoverp();}
    const std::vector<float>& mus_qoverpError() {return cms2.mus_qoverpError();}
    const std::vector<float>& mus_segmCompatibility() {return cms2.mus_segmCompatibility();}
    const std::vector<float>& mus_staRelChi2() {return cms2.mus_staRelChi2();}
    const std::vector<float>& mus_sta_chi2() {return cms2.mus_sta_chi2();}
    const std::vector<float>& mus_sta_d0() {return cms2.mus_sta_d0();}
    const std::vector<float>& mus_sta_d0Err() {return cms2.mus_sta_d0Err();}
    const std::vector<float>& mus_sta_d0corr() {return cms2.mus_sta_d0corr();}
    const std::vector<float>& mus_sta_ndof() {return cms2.mus_sta_ndof();}
    const std::vector<float>& mus_sta_qoverp() {return cms2.mus_sta_qoverp();}
    const std::vector<float>& mus_sta_qoverpError() {return cms2.mus_sta_qoverpError();}
    const std::vector<float>& mus_sta_z0() {return cms2.mus_sta_z0();}
    const std::vector<float>& mus_sta_z0Err() {return cms2.mus_sta_z0Err();}
    const std::vector<float>& mus_sta_z0corr() {return cms2.mus_sta_z0corr();}
    const std::vector<float>& mus_timeAtIpInOut() {return cms2.mus_timeAtIpInOut();}
    const std::vector<float>& mus_timeAtIpInOutErr() {return cms2.mus_timeAtIpInOutErr();}
    const std::vector<float>& mus_timeAtIpOutIn() {return cms2.mus_timeAtIpOutIn();}
    const std::vector<float>& mus_timeAtIpOutInErr() {return cms2.mus_timeAtIpOutInErr();}
    const std::vector<float>& mus_timeCompat() {return cms2.mus_timeCompat();}
    const std::vector<float>& mus_trkKink() {return cms2.mus_trkKink();}
    const std::vector<float>& mus_trkRelChi2() {return cms2.mus_trkRelChi2();}
    const std::vector<float>& mus_vertexCompat() {return cms2.mus_vertexCompat();}
    const std::vector<float>& mus_vertexphi() {return cms2.mus_vertexphi();}
    const std::vector<float>& mus_z0() {return cms2.mus_z0();}
    const std::vector<float>& mus_z0Err() {return cms2.mus_z0Err();}
    const std::vector<float>& mus_z0corr() {return cms2.mus_z0corr();}
    const std::vector<float>& pfjets_mvavalue() {return cms2.pfjets_mvavalue();}
    const std::vector<float>& pfjets_full53xmva_beta() {return cms2.pfjets_full53xmva_beta();}
    const std::vector<float>& pfjets_full53xmva_betaStar() {return cms2.pfjets_full53xmva_betaStar();}
    const std::vector<float>& pfjets_full53xmva_d0() {return cms2.pfjets_full53xmva_d0();}
    const std::vector<float>& pfjets_full53xmva_dRMean() {return cms2.pfjets_full53xmva_dRMean();}
    const std::vector<float>& pfjets_full53xmva_dZ() {return cms2.pfjets_full53xmva_dZ();}
    const std::vector<float>& pfjets_full53xmva_frac01() {return cms2.pfjets_full53xmva_frac01();}
    const std::vector<float>& pfjets_full53xmva_frac02() {return cms2.pfjets_full53xmva_frac02();}
    const std::vector<float>& pfjets_full53xmva_frac03() {return cms2.pfjets_full53xmva_frac03();}
    const std::vector<float>& pfjets_full53xmva_frac04() {return cms2.pfjets_full53xmva_frac04();}
    const std::vector<float>& pfjets_full53xmva_frac05() {return cms2.pfjets_full53xmva_frac05();}
    const std::vector<float>& pfjets_full53xmva_nCharged() {return cms2.pfjets_full53xmva_nCharged();}
    const std::vector<float>& pfjets_full53xmva_nNeutrals() {return cms2.pfjets_full53xmva_nNeutrals();}
    const std::vector<float>& pfjets_full53xmva_nvtx() {return cms2.pfjets_full53xmva_nvtx();}
    const std::vector<float>& pfjets_full53xmvavalue() {return cms2.pfjets_full53xmvavalue();}
    const std::vector<float>& pfjets_full5xmvavalue() {return cms2.pfjets_full5xmvavalue();}
    const std::vector<float>& trkjet_met() {return cms2.trkjet_met();}
    const std::vector<float>& trkjet_metPhi() {return cms2.trkjet_metPhi();}
    const std::vector<float>& trkjet_sumet() {return cms2.trkjet_sumet();}
    const std::vector<float>& trk_met() {return cms2.trk_met();}
    const std::vector<float>& trk_metPhi() {return cms2.trk_metPhi();}
    const std::vector<float>& trk_sumet() {return cms2.trk_sumet();}
    const std::vector<float>& pfcands_deltaP() {return cms2.pfcands_deltaP();}
    const std::vector<float>& pfcands_ecalE() {return cms2.pfcands_ecalE();}
    const std::vector<float>& pfcands_hcalE() {return cms2.pfcands_hcalE();}
    const std::vector<float>& pfcands_mva_emu() {return cms2.pfcands_mva_emu();}
    const std::vector<float>& pfcands_mva_epi() {return cms2.pfcands_mva_epi();}
    const std::vector<float>& pfcands_mva_nothing_gamma() {return cms2.pfcands_mva_nothing_gamma();}
    const std::vector<float>& pfcands_mva_nothing_nh() {return cms2.pfcands_mva_nothing_nh();}
    const std::vector<float>& pfcands_mva_pimu() {return cms2.pfcands_mva_pimu();}
    const std::vector<float>& pfcands_pS1E() {return cms2.pfcands_pS1E();}
    const std::vector<float>& pfcands_pS2E() {return cms2.pfcands_pS2E();}
    const std::vector<float>& pfcands_rawEcalE() {return cms2.pfcands_rawEcalE();}
    const std::vector<float>& pfcands_rawHcalE() {return cms2.pfcands_rawHcalE();}
    const std::vector<float>& pfels_deltaP() {return cms2.pfels_deltaP();}
    const std::vector<float>& pfels_ecalE() {return cms2.pfels_ecalE();}
    const std::vector<float>& pfels_hcalE() {return cms2.pfels_hcalE();}
    const std::vector<float>& pfels_iso04ChargedHadrons() {return cms2.pfels_iso04ChargedHadrons();}
    const std::vector<float>& pfels_iso04NeutralHadrons() {return cms2.pfels_iso04NeutralHadrons();}
    const std::vector<float>& pfels_iso04Photons() {return cms2.pfels_iso04Photons();}
    const std::vector<float>& pfels_isoChargedHadrons() {return cms2.pfels_isoChargedHadrons();}
    const std::vector<float>& pfels_isoNeutralHadrons() {return cms2.pfels_isoNeutralHadrons();}
    const std::vector<float>& pfels_isoPhotons() {return cms2.pfels_isoPhotons();}
    const std::vector<float>& pfels_mva_emu() {return cms2.pfels_mva_emu();}
    const std::vector<float>& pfels_mva_epi() {return cms2.pfels_mva_epi();}
    const std::vector<float>& pfels_mva_nothing_gamma() {return cms2.pfels_mva_nothing_gamma();}
    const std::vector<float>& pfels_mva_nothing_nh() {return cms2.pfels_mva_nothing_nh();}
    const std::vector<float>& pfels_mva_pimu() {return cms2.pfels_mva_pimu();}
    const std::vector<float>& pfels_pS1E() {return cms2.pfels_pS1E();}
    const std::vector<float>& pfels_pS2E() {return cms2.pfels_pS2E();}
    const std::vector<float>& pfels_rawEcalE() {return cms2.pfels_rawEcalE();}
    const std::vector<float>& pfels_rawHcalE() {return cms2.pfels_rawHcalE();}
    const std::vector<float>& pfjets_area() {return cms2.pfjets_area();}
    const std::vector<float>& pfjets_chargedEmE() {return cms2.pfjets_chargedEmE();}
    const std::vector<float>& pfjets_chargedHadronE() {return cms2.pfjets_chargedHadronE();}
    const std::vector<float>& pfjets_cor() {return cms2.pfjets_cor();}
    const std::vector<float>& pfjets_corL1Fast() {return cms2.pfjets_corL1Fast();}
    const std::vector<float>& pfjets_corL1FastL2L3() {return cms2.pfjets_corL1FastL2L3();}
    const std::vector<float>& pfjets_corL1FastL2L3residual() {return cms2.pfjets_corL1FastL2L3residual();}
    const std::vector<float>& pfjets_corL1L2L3() {return cms2.pfjets_corL1L2L3();}
    const std::vector<float>& pfjets_electronE() {return cms2.pfjets_electronE();}
    const std::vector<float>& pfjets_hfEmE() {return cms2.pfjets_hfEmE();}
    const std::vector<float>& pfjets_hfHadronE() {return cms2.pfjets_hfHadronE();}
    const std::vector<float>& pfjets_muonE() {return cms2.pfjets_muonE();}
    const std::vector<float>& pfjets_neutralEmE() {return cms2.pfjets_neutralEmE();}
    const std::vector<float>& pfjets_neutralHadronE() {return cms2.pfjets_neutralHadronE();}
    const std::vector<float>& pfjets_photonE() {return cms2.pfjets_photonE();}
    const std::vector<float>& pfmus_deltaP() {return cms2.pfmus_deltaP();}
    const std::vector<float>& pfmus_ecalE() {return cms2.pfmus_ecalE();}
    const std::vector<float>& pfmus_hcalE() {return cms2.pfmus_hcalE();}
    const std::vector<float>& pfmus_iso04ChargedHadrons() {return cms2.pfmus_iso04ChargedHadrons();}
    const std::vector<float>& pfmus_iso04NeutralHadrons() {return cms2.pfmus_iso04NeutralHadrons();}
    const std::vector<float>& pfmus_iso04Photons() {return cms2.pfmus_iso04Photons();}
    const std::vector<float>& pfmus_isoChargedHadrons() {return cms2.pfmus_isoChargedHadrons();}
    const std::vector<float>& pfmus_isoNeutralHadrons() {return cms2.pfmus_isoNeutralHadrons();}
    const std::vector<float>& pfmus_isoPhotons() {return cms2.pfmus_isoPhotons();}
    const std::vector<float>& pfmus_mva_emu() {return cms2.pfmus_mva_emu();}
    const std::vector<float>& pfmus_mva_epi() {return cms2.pfmus_mva_epi();}
    const std::vector<float>& pfmus_mva_nothing_gamma() {return cms2.pfmus_mva_nothing_gamma();}
    const std::vector<float>& pfmus_mva_nothing_nh() {return cms2.pfmus_mva_nothing_nh();}
    const std::vector<float>& pfmus_mva_pimu() {return cms2.pfmus_mva_pimu();}
    const std::vector<float>& pfmus_pS1E() {return cms2.pfmus_pS1E();}
    const std::vector<float>& pfmus_pS2E() {return cms2.pfmus_pS2E();}
    const std::vector<float>& pfmus_rawEcalE() {return cms2.pfmus_rawEcalE();}
    const std::vector<float>& pfmus_rawHcalE() {return cms2.pfmus_rawHcalE();}
    const std::vector<float>& taus_pf_againstElectronDeadECAL() {return cms2.taus_pf_againstElectronDeadECAL();}
    const std::vector<float>& taus_pf_againstElectronLoose() {return cms2.taus_pf_againstElectronLoose();}
    const std::vector<float>& taus_pf_againstElectronLooseMVA2() {return cms2.taus_pf_againstElectronLooseMVA2();}
    const std::vector<float>& taus_pf_againstElectronLooseMVA3() {return cms2.taus_pf_againstElectronLooseMVA3();}
    const std::vector<float>& taus_pf_againstElectronMVA() {return cms2.taus_pf_againstElectronMVA();}
    const std::vector<float>& taus_pf_againstElectronMVA2category() {return cms2.taus_pf_againstElectronMVA2category();}
    const std::vector<float>& taus_pf_againstElectronMVA2raw() {return cms2.taus_pf_againstElectronMVA2raw();}
    const std::vector<float>& taus_pf_againstElectronMVA3category() {return cms2.taus_pf_againstElectronMVA3category();}
    const std::vector<float>& taus_pf_againstElectronMVA3raw() {return cms2.taus_pf_againstElectronMVA3raw();}
    const std::vector<float>& taus_pf_againstElectronMedium() {return cms2.taus_pf_againstElectronMedium();}
    const std::vector<float>& taus_pf_againstElectronMediumMVA2() {return cms2.taus_pf_againstElectronMediumMVA2();}
    const std::vector<float>& taus_pf_againstElectronMediumMVA3() {return cms2.taus_pf_againstElectronMediumMVA3();}
    const std::vector<float>& taus_pf_againstElectronTight() {return cms2.taus_pf_againstElectronTight();}
    const std::vector<float>& taus_pf_againstElectronTightMVA2() {return cms2.taus_pf_againstElectronTightMVA2();}
    const std::vector<float>& taus_pf_againstElectronTightMVA3() {return cms2.taus_pf_againstElectronTightMVA3();}
    const std::vector<float>& taus_pf_againstElectronVLooseMVA2() {return cms2.taus_pf_againstElectronVLooseMVA2();}
    const std::vector<float>& taus_pf_againstElectronVTightMVA3() {return cms2.taus_pf_againstElectronVTightMVA3();}
    const std::vector<float>& taus_pf_againstMuonLoose() {return cms2.taus_pf_againstMuonLoose();}
    const std::vector<float>& taus_pf_againstMuonLoose2() {return cms2.taus_pf_againstMuonLoose2();}
    const std::vector<float>& taus_pf_againstMuonMedium() {return cms2.taus_pf_againstMuonMedium();}
    const std::vector<float>& taus_pf_againstMuonMedium2() {return cms2.taus_pf_againstMuonMedium2();}
    const std::vector<float>& taus_pf_againstMuonTight() {return cms2.taus_pf_againstMuonTight();}
    const std::vector<float>& taus_pf_againstMuonTight2() {return cms2.taus_pf_againstMuonTight2();}
    const std::vector<float>& taus_pf_byCombinedIsolationDeltaBetaCorrRaw() {return cms2.taus_pf_byCombinedIsolationDeltaBetaCorrRaw();}
    const std::vector<float>& taus_pf_byCombinedIsolationDeltaBetaCorrRaw3Hits() {return cms2.taus_pf_byCombinedIsolationDeltaBetaCorrRaw3Hits();}
    const std::vector<float>& taus_pf_byDecayModeFinding() {return cms2.taus_pf_byDecayModeFinding();}
    const std::vector<float>& taus_pf_byIsolationMVA2raw() {return cms2.taus_pf_byIsolationMVA2raw();}
    const std::vector<float>& taus_pf_byIsolationMVAraw() {return cms2.taus_pf_byIsolationMVAraw();}
    const std::vector<float>& taus_pf_byLooseCombinedIsolationDeltaBetaCorr() {return cms2.taus_pf_byLooseCombinedIsolationDeltaBetaCorr();}
    const std::vector<float>& taus_pf_byLooseCombinedIsolationDeltaBetaCorr3Hits() {return cms2.taus_pf_byLooseCombinedIsolationDeltaBetaCorr3Hits();}
    const std::vector<float>& taus_pf_byLooseIsolationMVA() {return cms2.taus_pf_byLooseIsolationMVA();}
    const std::vector<float>& taus_pf_byLooseIsolationMVA2() {return cms2.taus_pf_byLooseIsolationMVA2();}
    const std::vector<float>& taus_pf_byMediumCombinedIsolationDeltaBetaCorr() {return cms2.taus_pf_byMediumCombinedIsolationDeltaBetaCorr();}
    const std::vector<float>& taus_pf_byMediumCombinedIsolationDeltaBetaCorr3Hits() {return cms2.taus_pf_byMediumCombinedIsolationDeltaBetaCorr3Hits();}
    const std::vector<float>& taus_pf_byMediumIsolationMVA() {return cms2.taus_pf_byMediumIsolationMVA();}
    const std::vector<float>& taus_pf_byMediumIsolationMVA2() {return cms2.taus_pf_byMediumIsolationMVA2();}
    const std::vector<float>& taus_pf_byTightCombinedIsolationDeltaBetaCorr() {return cms2.taus_pf_byTightCombinedIsolationDeltaBetaCorr();}
    const std::vector<float>& taus_pf_byTightCombinedIsolationDeltaBetaCorr3Hits() {return cms2.taus_pf_byTightCombinedIsolationDeltaBetaCorr3Hits();}
    const std::vector<float>& taus_pf_byTightIsolationMVA() {return cms2.taus_pf_byTightIsolationMVA();}
    const std::vector<float>& taus_pf_byTightIsolationMVA2() {return cms2.taus_pf_byTightIsolationMVA2();}
    const std::vector<float>& taus_pf_byVLooseCombinedIsolationDeltaBetaCorr() {return cms2.taus_pf_byVLooseCombinedIsolationDeltaBetaCorr();}
    const std::vector<float>& photons_e1x5() {return cms2.photons_e1x5();}
    const std::vector<float>& photons_e2x5Max() {return cms2.photons_e2x5Max();}
    const std::vector<float>& photons_e3x3() {return cms2.photons_e3x3();}
    const std::vector<float>& photons_e5x5() {return cms2.photons_e5x5();}
    const std::vector<float>& photons_ecalIso03() {return cms2.photons_ecalIso03();}
    const std::vector<float>& photons_ecalIso04() {return cms2.photons_ecalIso04();}
    const std::vector<float>& photons_hOverE() {return cms2.photons_hOverE();}
    const std::vector<float>& photons_hcalDepth1TowerSumEtBcConeDR03() {return cms2.photons_hcalDepth1TowerSumEtBcConeDR03();}
    const std::vector<float>& photons_hcalDepth1TowerSumEtBcConeDR04() {return cms2.photons_hcalDepth1TowerSumEtBcConeDR04();}
    const std::vector<float>& photons_hcalDepth2TowerSumEtBcConeDR03() {return cms2.photons_hcalDepth2TowerSumEtBcConeDR03();}
    const std::vector<float>& photons_hcalDepth2TowerSumEtBcConeDR04() {return cms2.photons_hcalDepth2TowerSumEtBcConeDR04();}
    const std::vector<float>& photons_hcalIso03() {return cms2.photons_hcalIso03();}
    const std::vector<float>& photons_hcalIso04() {return cms2.photons_hcalIso04();}
    const std::vector<float>& photons_hcalTowerSumEtBcConeDR03() {return cms2.photons_hcalTowerSumEtBcConeDR03();}
    const std::vector<float>& photons_hcalTowerSumEtBcConeDR04() {return cms2.photons_hcalTowerSumEtBcConeDR04();}
    const std::vector<float>& photons_ntkIsoHollow03() {return cms2.photons_ntkIsoHollow03();}
    const std::vector<float>& photons_ntkIsoHollow04() {return cms2.photons_ntkIsoHollow04();}
    const std::vector<float>& photons_ntkIsoSolid03() {return cms2.photons_ntkIsoSolid03();}
    const std::vector<float>& photons_ntkIsoSolid04() {return cms2.photons_ntkIsoSolid04();}
    const std::vector<float>& photons_sigmaEtaEta() {return cms2.photons_sigmaEtaEta();}
    const std::vector<float>& photons_sigmaIEtaIEta() {return cms2.photons_sigmaIEtaIEta();}
    const std::vector<float>& photons_swissSeed() {return cms2.photons_swissSeed();}
    const std::vector<float>& photons_tkIsoHollow03() {return cms2.photons_tkIsoHollow03();}
    const std::vector<float>& photons_tkIsoHollow04() {return cms2.photons_tkIsoHollow04();}
    const std::vector<float>& photons_tkIsoSolid03() {return cms2.photons_tkIsoSolid03();}
    const std::vector<float>& photons_tkIsoSolid04() {return cms2.photons_tkIsoSolid04();}
    const std::vector<float>& puInfo_trueNumInteractions() {return cms2.puInfo_trueNumInteractions();}
    const std::vector<float>& convs_chi2() {return cms2.convs_chi2();}
    const std::vector<float>& convs_dl() {return cms2.convs_dl();}
    const std::vector<float>& convs_ndof() {return cms2.convs_ndof();}
    const std::vector<float>& sparm_values() {return cms2.sparm_values();}
    const std::vector<float>& scs_clustersSize() {return cms2.scs_clustersSize();}
    const std::vector<float>& scs_crystalsSize() {return cms2.scs_crystalsSize();}
    const std::vector<float>& scs_e1x3() {return cms2.scs_e1x3();}
    const std::vector<float>& scs_e1x5() {return cms2.scs_e1x5();}
    const std::vector<float>& scs_e2nd() {return cms2.scs_e2nd();}
    const std::vector<float>& scs_e2x2() {return cms2.scs_e2x2();}
    const std::vector<float>& scs_e2x5Max() {return cms2.scs_e2x5Max();}
    const std::vector<float>& scs_e3x1() {return cms2.scs_e3x1();}
    const std::vector<float>& scs_e3x2() {return cms2.scs_e3x2();}
    const std::vector<float>& scs_e3x3() {return cms2.scs_e3x3();}
    const std::vector<float>& scs_e4x4() {return cms2.scs_e4x4();}
    const std::vector<float>& scs_e5x5() {return cms2.scs_e5x5();}
    const std::vector<float>& scs_eMax() {return cms2.scs_eMax();}
    const std::vector<float>& scs_eSeed() {return cms2.scs_eSeed();}
    const std::vector<float>& scs_energy() {return cms2.scs_energy();}
    const std::vector<float>& scs_eta() {return cms2.scs_eta();}
    const std::vector<float>& scs_hoe() {return cms2.scs_hoe();}
    const std::vector<float>& scs_laserCorMax() {return cms2.scs_laserCorMax();}
    const std::vector<float>& scs_laserCorMean() {return cms2.scs_laserCorMean();}
    const std::vector<float>& scs_laserCorSeed() {return cms2.scs_laserCorSeed();}
    const std::vector<float>& scs_phi() {return cms2.scs_phi();}
    const std::vector<float>& scs_preshowerEnergy() {return cms2.scs_preshowerEnergy();}
    const std::vector<float>& scs_rawEnergy() {return cms2.scs_rawEnergy();}
    const std::vector<float>& scs_sigmaEtaEta() {return cms2.scs_sigmaEtaEta();}
    const std::vector<float>& scs_sigmaEtaPhi() {return cms2.scs_sigmaEtaPhi();}
    const std::vector<float>& scs_sigmaIEtaIEta() {return cms2.scs_sigmaIEtaIEta();}
    const std::vector<float>& scs_sigmaIEtaIEtaSC() {return cms2.scs_sigmaIEtaIEtaSC();}
    const std::vector<float>& scs_sigmaIEtaIPhi() {return cms2.scs_sigmaIEtaIPhi();}
    const std::vector<float>& scs_sigmaIEtaIPhiSC() {return cms2.scs_sigmaIEtaIPhiSC();}
    const std::vector<float>& scs_sigmaIPhiIPhi() {return cms2.scs_sigmaIPhiIPhi();}
    const std::vector<float>& scs_sigmaIPhiIPhiSC() {return cms2.scs_sigmaIPhiIPhiSC();}
    const std::vector<float>& scs_sigmaPhiPhi() {return cms2.scs_sigmaPhiPhi();}
    const std::vector<float>& scs_timeSeed() {return cms2.scs_timeSeed();}
    const std::vector<float>& svs_anglePV() {return cms2.svs_anglePV();}
    const std::vector<float>& svs_chi2() {return cms2.svs_chi2();}
    const std::vector<float>& svs_dist3Dsig() {return cms2.svs_dist3Dsig();}
    const std::vector<float>& svs_dist3Dval() {return cms2.svs_dist3Dval();}
    const std::vector<float>& svs_distXYsig() {return cms2.svs_distXYsig();}
    const std::vector<float>& svs_distXYval() {return cms2.svs_distXYval();}
    const std::vector<float>& svs_ndof() {return cms2.svs_ndof();}
    const std::vector<float>& svs_prob() {return cms2.svs_prob();}
    const std::vector<float>& svs_xError() {return cms2.svs_xError();}
    const std::vector<float>& svs_yError() {return cms2.svs_yError();}
    const std::vector<float>& svs_zError() {return cms2.svs_zError();}
    const std::vector<float>& mus_tcmet_deltax() {return cms2.mus_tcmet_deltax();}
    const std::vector<float>& mus_tcmet_deltay() {return cms2.mus_tcmet_deltay();}
    const std::vector<float>& pfcands_dzpv() {return cms2.pfcands_dzpv();}
    const std::vector<float>& pfcands_trkiso() {return cms2.pfcands_trkiso();}
    const std::vector<float>& trks_chi2() {return cms2.trks_chi2();}
    const std::vector<float>& trks_d0() {return cms2.trks_d0();}
    const std::vector<float>& trks_d0Err() {return cms2.trks_d0Err();}
    const std::vector<float>& trks_d0corr() {return cms2.trks_d0corr();}
    const std::vector<float>& trks_d0corrPhi() {return cms2.trks_d0corrPhi();}
    const std::vector<float>& trks_d0phiCov() {return cms2.trks_d0phiCov();}
    const std::vector<float>& trks_etaErr() {return cms2.trks_etaErr();}
    const std::vector<float>& trks_layer1_charge() {return cms2.trks_layer1_charge();}
    const std::vector<float>& trks_ndof() {return cms2.trks_ndof();}
    const std::vector<float>& trks_phiErr() {return cms2.trks_phiErr();}
    const std::vector<float>& trks_ptErr() {return cms2.trks_ptErr();}
    const std::vector<float>& trks_validFraction() {return cms2.trks_validFraction();}
    const std::vector<float>& trks_z0() {return cms2.trks_z0();}
    const std::vector<float>& trks_z0Err() {return cms2.trks_z0Err();}
    const std::vector<float>& trks_z0corr() {return cms2.trks_z0corr();}
    const std::vector<float>& trkjets_cor() {return cms2.trkjets_cor();}
    const std::vector<float>& trks_d0Errvtx() {return cms2.trks_d0Errvtx();}
    const std::vector<float>& trks_d0vtx() {return cms2.trks_d0vtx();}
    const std::vector<float>& vtxs_chi2() {return cms2.vtxs_chi2();}
    const std::vector<float>& vtxs_ndof() {return cms2.vtxs_ndof();}
    const std::vector<float>& vtxs_sumpt() {return cms2.vtxs_sumpt();}
    const std::vector<float>& vtxs_xError() {return cms2.vtxs_xError();}
    const std::vector<float>& vtxs_yError() {return cms2.vtxs_yError();}
    const std::vector<float>& vtxs_zError() {return cms2.vtxs_zError();}
    const std::vector<float>& bsvtxs_chi2() {return cms2.bsvtxs_chi2();}
    const std::vector<float>& bsvtxs_ndof() {return cms2.bsvtxs_ndof();}
    const std::vector<float>& bsvtxs_sumpt() {return cms2.bsvtxs_sumpt();}
    const std::vector<float>& bsvtxs_xError() {return cms2.bsvtxs_xError();}
    const std::vector<float>& bsvtxs_yError() {return cms2.bsvtxs_yError();}
    const std::vector<float>& bsvtxs_zError() {return cms2.bsvtxs_zError();}
    const std::vector<std::vector<float> >& els_convs_dcot() {return cms2.els_convs_dcot();}
    const std::vector<std::vector<float> >& els_convs_dist() {return cms2.els_convs_dist();}
    const std::vector<std::vector<float> >& els_convs_radius() {return cms2.els_convs_radius();}
    const std::vector<std::vector<float> >& mus_stationShowerDeltaR() {return cms2.mus_stationShowerDeltaR();}
    const std::vector<std::vector<float> >& mus_stationShowerSizeT() {return cms2.mus_stationShowerSizeT();}
    const std::vector<std::vector<float> >& puInfo_instLumi() {return cms2.puInfo_instLumi();}
    const std::vector<std::vector<float> >& puInfo_sump_highpt() {return cms2.puInfo_sump_highpt();}
    const std::vector<std::vector<float> >& puInfo_sumpt_lowpt() {return cms2.puInfo_sumpt_lowpt();}
    const std::vector<std::vector<float> >& puInfo_zpositions() {return cms2.puInfo_zpositions();}
    const std::vector<std::vector<float> >& vtxs_covMatrix() {return cms2.vtxs_covMatrix();}
    const std::vector<std::vector<float> >& bsvtxs_covMatrix() {return cms2.bsvtxs_covMatrix();}
    const int& evt_cscLooseHaloId() {return cms2.evt_cscLooseHaloId();}
    const int& evt_cscTightHaloId() {return cms2.evt_cscTightHaloId();}
    const int& evt_ecalLooseHaloId() {return cms2.evt_ecalLooseHaloId();}
    const int& evt_ecalTightHaloId() {return cms2.evt_ecalTightHaloId();}
    const int& evt_extremeTightHaloId() {return cms2.evt_extremeTightHaloId();}
    const int& evt_globalLooseHaloId() {return cms2.evt_globalLooseHaloId();}
    const int& evt_globalTightHaloId() {return cms2.evt_globalTightHaloId();}
    const int& evt_hcalLooseHaloId() {return cms2.evt_hcalLooseHaloId();}
    const int& evt_hcalTightHaloId() {return cms2.evt_hcalTightHaloId();}
    const int& evt_looseHaloId() {return cms2.evt_looseHaloId();}
    const int& evt_nHaloLikeTracks() {return cms2.evt_nHaloLikeTracks();}
    const int& evt_nHaloTriggerCandidates() {return cms2.evt_nHaloTriggerCandidates();}
    const int& evt_tightHaloId() {return cms2.evt_tightHaloId();}
    const int& evt_bsType() {return cms2.evt_bsType();}
    const int& evt_bunchCrossing() {return cms2.evt_bunchCrossing();}
    const int& evt_experimentType() {return cms2.evt_experimentType();}
    const int& evt_isRealData() {return cms2.evt_isRealData();}
    const int& evt_orbitNumber() {return cms2.evt_orbitNumber();}
    const int& evt_storeNumber() {return cms2.evt_storeNumber();}
    const int& hcalnoise_GetRecHitCount() {return cms2.hcalnoise_GetRecHitCount();}
    const int& hcalnoise_GetRecHitCount15() {return cms2.hcalnoise_GetRecHitCount15();}
    const int& hcalnoise_maxHPDHits() {return cms2.hcalnoise_maxHPDHits();}
    const int& hcalnoise_maxHPDNoOtherHits() {return cms2.hcalnoise_maxHPDNoOtherHits();}
    const int& hcalnoise_maxRBXHits() {return cms2.hcalnoise_maxRBXHits();}
    const int& hcalnoise_maxZeros() {return cms2.hcalnoise_maxZeros();}
    const int& hcalnoise_noiseFilterStatus() {return cms2.hcalnoise_noiseFilterStatus();}
    const int& hcalnoise_noiseType() {return cms2.hcalnoise_noiseType();}
    const int& hcalnoise_num10GeVHits() {return cms2.hcalnoise_num10GeVHits();}
    const int& hcalnoise_num25GeVHits() {return cms2.hcalnoise_num25GeVHits();}
    const int& hcalnoise_numFlatNoiseChannels() {return cms2.hcalnoise_numFlatNoiseChannels();}
    const int& hcalnoise_numIsolatedNoiseChannels() {return cms2.hcalnoise_numIsolatedNoiseChannels();}
    const int& hcalnoise_numProblematicRBXs() {return cms2.hcalnoise_numProblematicRBXs();}
    const int& hcalnoise_numSpikeNoiseChannels() {return cms2.hcalnoise_numSpikeNoiseChannels();}
    const int& hcalnoise_numTS4TS5NoiseChannels() {return cms2.hcalnoise_numTS4TS5NoiseChannels();}
    const int& hcalnoise_numTriangleNoiseChannels() {return cms2.hcalnoise_numTriangleNoiseChannels();}
    const int& hcalnoise_passHighLevelNoiseFilter() {return cms2.hcalnoise_passHighLevelNoiseFilter();}
    const int& hcalnoise_passLooseNoiseFilter() {return cms2.hcalnoise_passLooseNoiseFilter();}
    const int& hcalnoise_passTightNoiseFilter() {return cms2.hcalnoise_passTightNoiseFilter();}
    const int& l1_nemiso() {return cms2.l1_nemiso();}
    const int& l1_nemnoiso() {return cms2.l1_nemnoiso();}
    const int& l1_njetsc() {return cms2.l1_njetsc();}
    const int& l1_njetsf() {return cms2.l1_njetsf();}
    const int& l1_njetst() {return cms2.l1_njetst();}
    const int& l1_nmus() {return cms2.l1_nmus();}
    const int& ls_lumiSecQual() {return cms2.ls_lumiSecQual();}
    const int& pdfinfo_id1() {return cms2.pdfinfo_id1();}
    const int& pdfinfo_id2() {return cms2.pdfinfo_id2();}
    const int& sparm_subProcessId() {return cms2.sparm_subProcessId();}
    const std::vector<int>& evt_ecaliPhiSuspects() {return cms2.evt_ecaliPhiSuspects();}
    const std::vector<int>& evt_globaliPhiSuspects() {return cms2.evt_globaliPhiSuspects();}
    const std::vector<int>& evt_hcaliPhiSuspects() {return cms2.evt_hcaliPhiSuspects();}
    const std::vector<int>& els_mc3_id() {return cms2.els_mc3_id();}
    const std::vector<int>& els_mc3idx() {return cms2.els_mc3idx();}
    const std::vector<int>& els_mc3_motherid() {return cms2.els_mc3_motherid();}
    const std::vector<int>& els_mc3_motheridx() {return cms2.els_mc3_motheridx();}
    const std::vector<int>& els_mc_id() {return cms2.els_mc_id();}
    const std::vector<int>& els_mcidx() {return cms2.els_mcidx();}
    const std::vector<int>& els_mc_motherid() {return cms2.els_mc_motherid();}
    const std::vector<int>& jets_mc3_id() {return cms2.jets_mc3_id();}
    const std::vector<int>& jets_mc3idx() {return cms2.jets_mc3idx();}
    const std::vector<int>& jets_mc_gpidx() {return cms2.jets_mc_gpidx();}
    const std::vector<int>& jets_mc_id() {return cms2.jets_mc_id();}
    const std::vector<int>& jets_mcidx() {return cms2.jets_mcidx();}
    const std::vector<int>& jets_mc_motherid() {return cms2.jets_mc_motherid();}
    const std::vector<int>& mus_mc3_id() {return cms2.mus_mc3_id();}
    const std::vector<int>& mus_mc3idx() {return cms2.mus_mc3idx();}
    const std::vector<int>& mus_mc3_motherid() {return cms2.mus_mc3_motherid();}
    const std::vector<int>& mus_mc3_motheridx() {return cms2.mus_mc3_motheridx();}
    const std::vector<int>& mus_mc_id() {return cms2.mus_mc_id();}
    const std::vector<int>& mus_mcidx() {return cms2.mus_mcidx();}
    const std::vector<int>& mus_mc_motherid() {return cms2.mus_mc_motherid();}
    const std::vector<int>& pfjets_mc3_id() {return cms2.pfjets_mc3_id();}
    const std::vector<int>& pfjets_mc3idx() {return cms2.pfjets_mc3idx();}
    const std::vector<int>& pfjets_mc_gpidx() {return cms2.pfjets_mc_gpidx();}
    const std::vector<int>& pfjets_mc_id() {return cms2.pfjets_mc_id();}
    const std::vector<int>& pfjets_mcidx() {return cms2.pfjets_mcidx();}
    const std::vector<int>& pfjets_mc_motherid() {return cms2.pfjets_mc_motherid();}
    const std::vector<int>& photons_mc3_id() {return cms2.photons_mc3_id();}
    const std::vector<int>& photons_mc3idx() {return cms2.photons_mc3idx();}
    const std::vector<int>& photons_mc3_motherid() {return cms2.photons_mc3_motherid();}
    const std::vector<int>& photons_mc3_motheridx() {return cms2.photons_mc3_motheridx();}
    const std::vector<int>& photons_mc_id() {return cms2.photons_mc_id();}
    const std::vector<int>& photons_mcidx() {return cms2.photons_mcidx();}
    const std::vector<int>& photons_mc_motherid() {return cms2.photons_mc_motherid();}
    const std::vector<int>& trk_mc3_id() {return cms2.trk_mc3_id();}
    const std::vector<int>& trk_mc3idx() {return cms2.trk_mc3idx();}
    const std::vector<int>& trk_mc3_motherid() {return cms2.trk_mc3_motherid();}
    const std::vector<int>& trk_mc3_motheridx() {return cms2.trk_mc3_motheridx();}
    const std::vector<int>& trk_mc_id() {return cms2.trk_mc_id();}
    const std::vector<int>& trk_mcidx() {return cms2.trk_mcidx();}
    const std::vector<int>& trk_mc_motherid() {return cms2.trk_mc_motherid();}
    const std::vector<int>& els_closestJet() {return cms2.els_closestJet();}
    const std::vector<int>& els_closestMuon() {return cms2.els_closestMuon();}
    const std::vector<int>& els_pfelsidx() {return cms2.els_pfelsidx();}
    const std::vector<int>& els_category() {return cms2.els_category();}
    const std::vector<int>& els_charge() {return cms2.els_charge();}
    const std::vector<int>& els_ckf_laywithmeas() {return cms2.els_ckf_laywithmeas();}
    const std::vector<int>& els_class() {return cms2.els_class();}
    const std::vector<int>& els_conv_delMissHits() {return cms2.els_conv_delMissHits();}
    const std::vector<int>& els_conv_flag() {return cms2.els_conv_flag();}
    const std::vector<int>& els_conv_gsftkidx() {return cms2.els_conv_gsftkidx();}
    const std::vector<int>& els_conv_old_delMissHits() {return cms2.els_conv_old_delMissHits();}
    const std::vector<int>& els_conv_old_flag() {return cms2.els_conv_old_flag();}
    const std::vector<int>& els_conv_old_gsftkidx() {return cms2.els_conv_old_gsftkidx();}
    const std::vector<int>& els_conv_old_tkidx() {return cms2.els_conv_old_tkidx();}
    const std::vector<int>& els_conv_tkidx() {return cms2.els_conv_tkidx();}
    const std::vector<int>& els_exp_innerlayers() {return cms2.els_exp_innerlayers();}
    const std::vector<int>& els_exp_outerlayers() {return cms2.els_exp_outerlayers();}
    const std::vector<int>& els_fiduciality() {return cms2.els_fiduciality();}
    const std::vector<int>& els_gsftrkidx() {return cms2.els_gsftrkidx();}
    const std::vector<int>& els_layer1_det() {return cms2.els_layer1_det();}
    const std::vector<int>& els_layer1_layer() {return cms2.els_layer1_layer();}
    const std::vector<int>& els_layer1_sizerphi() {return cms2.els_layer1_sizerphi();}
    const std::vector<int>& els_layer1_sizerz() {return cms2.els_layer1_sizerz();}
    const std::vector<int>& els_lostHits() {return cms2.els_lostHits();}
    const std::vector<int>& els_lost_pixelhits() {return cms2.els_lost_pixelhits();}
    const std::vector<int>& els_nSeed() {return cms2.els_nSeed();}
    const std::vector<int>& els_sccharge() {return cms2.els_sccharge();}
    const std::vector<int>& els_scindex() {return cms2.els_scindex();}
    const std::vector<int>& els_trk_charge() {return cms2.els_trk_charge();}
    const std::vector<int>& els_trkidx() {return cms2.els_trkidx();}
    const std::vector<int>& els_type() {return cms2.els_type();}
    const std::vector<int>& els_validHits() {return cms2.els_validHits();}
    const std::vector<int>& els_valid_pixelhits() {return cms2.els_valid_pixelhits();}
    const std::vector<int>& genps_id() {return cms2.genps_id();}
    const std::vector<int>& genps_id_mother() {return cms2.genps_id_mother();}
    const std::vector<int>& genps_status() {return cms2.genps_status();}
    const std::vector<int>& gsftrks_charge() {return cms2.gsftrks_charge();}
    const std::vector<int>& gsftrks_exp_innerlayers() {return cms2.gsftrks_exp_innerlayers();}
    const std::vector<int>& gsftrks_exp_outerlayers() {return cms2.gsftrks_exp_outerlayers();}
    const std::vector<int>& gsftrks_layer1_det() {return cms2.gsftrks_layer1_det();}
    const std::vector<int>& gsftrks_layer1_layer() {return cms2.gsftrks_layer1_layer();}
    const std::vector<int>& gsftrks_layer1_sizerphi() {return cms2.gsftrks_layer1_sizerphi();}
    const std::vector<int>& gsftrks_layer1_sizerz() {return cms2.gsftrks_layer1_sizerz();}
    const std::vector<int>& gsftrks_lostHits() {return cms2.gsftrks_lostHits();}
    const std::vector<int>& gsftrks_lost_pixelhits() {return cms2.gsftrks_lost_pixelhits();}
    const std::vector<int>& gsftrks_nlayers() {return cms2.gsftrks_nlayers();}
    const std::vector<int>& gsftrks_nlayers3D() {return cms2.gsftrks_nlayers3D();}
    const std::vector<int>& gsftrks_nlayersLost() {return cms2.gsftrks_nlayersLost();}
    const std::vector<int>& gsftrks_validHits() {return cms2.gsftrks_validHits();}
    const std::vector<int>& gsftrks_valid_pixelhits() {return cms2.gsftrks_valid_pixelhits();}
    const std::vector<int>& hyp_ll_charge() {return cms2.hyp_ll_charge();}
    const std::vector<int>& hyp_ll_id() {return cms2.hyp_ll_id();}
    const std::vector<int>& hyp_ll_index() {return cms2.hyp_ll_index();}
    const std::vector<int>& hyp_ll_lostHits() {return cms2.hyp_ll_lostHits();}
    const std::vector<int>& hyp_ll_validHits() {return cms2.hyp_ll_validHits();}
    const std::vector<int>& hyp_lt_charge() {return cms2.hyp_lt_charge();}
    const std::vector<int>& hyp_lt_id() {return cms2.hyp_lt_id();}
    const std::vector<int>& hyp_lt_index() {return cms2.hyp_lt_index();}
    const std::vector<int>& hyp_lt_lostHits() {return cms2.hyp_lt_lostHits();}
    const std::vector<int>& hyp_lt_validHits() {return cms2.hyp_lt_validHits();}
    const std::vector<int>& hyp_njets() {return cms2.hyp_njets();}
    const std::vector<int>& hyp_nojets() {return cms2.hyp_nojets();}
    const std::vector<int>& hyp_type() {return cms2.hyp_type();}
    const std::vector<int>& hyp_FVFit_ndf() {return cms2.hyp_FVFit_ndf();}
    const std::vector<int>& hyp_FVFit_status() {return cms2.hyp_FVFit_status();}
    const std::vector<int>& hyp_ll_mc_id() {return cms2.hyp_ll_mc_id();}
    const std::vector<int>& hyp_ll_mc_motherid() {return cms2.hyp_ll_mc_motherid();}
    const std::vector<int>& hyp_lt_mc_id() {return cms2.hyp_lt_mc_id();}
    const std::vector<int>& hyp_lt_mc_motherid() {return cms2.hyp_lt_mc_motherid();}
    const std::vector<int>& pfjets_mcflavorAlgo() {return cms2.pfjets_mcflavorAlgo();}
    const std::vector<int>& pfjets_mcflavorPhys() {return cms2.pfjets_mcflavorPhys();}
    const std::vector<int>& jets_closestElectron() {return cms2.jets_closestElectron();}
    const std::vector<int>& jets_closestMuon() {return cms2.jets_closestMuon();}
    const std::vector<int>& l1_emiso_ieta() {return cms2.l1_emiso_ieta();}
    const std::vector<int>& l1_emiso_iphi() {return cms2.l1_emiso_iphi();}
    const std::vector<int>& l1_emiso_rawId() {return cms2.l1_emiso_rawId();}
    const std::vector<int>& l1_emiso_type() {return cms2.l1_emiso_type();}
    const std::vector<int>& l1_emnoiso_ieta() {return cms2.l1_emnoiso_ieta();}
    const std::vector<int>& l1_emnoiso_iphi() {return cms2.l1_emnoiso_iphi();}
    const std::vector<int>& l1_emnoiso_rawId() {return cms2.l1_emnoiso_rawId();}
    const std::vector<int>& l1_emnoiso_type() {return cms2.l1_emnoiso_type();}
    const std::vector<int>& l1_jetsc_ieta() {return cms2.l1_jetsc_ieta();}
    const std::vector<int>& l1_jetsc_iphi() {return cms2.l1_jetsc_iphi();}
    const std::vector<int>& l1_jetsc_rawId() {return cms2.l1_jetsc_rawId();}
    const std::vector<int>& l1_jetsc_type() {return cms2.l1_jetsc_type();}
    const std::vector<int>& l1_jetsf_ieta() {return cms2.l1_jetsf_ieta();}
    const std::vector<int>& l1_jetsf_iphi() {return cms2.l1_jetsf_iphi();}
    const std::vector<int>& l1_jetsf_rawId() {return cms2.l1_jetsf_rawId();}
    const std::vector<int>& l1_jetsf_type() {return cms2.l1_jetsf_type();}
    const std::vector<int>& l1_jetst_ieta() {return cms2.l1_jetst_ieta();}
    const std::vector<int>& l1_jetst_iphi() {return cms2.l1_jetst_iphi();}
    const std::vector<int>& l1_jetst_rawId() {return cms2.l1_jetst_rawId();}
    const std::vector<int>& l1_jetst_type() {return cms2.l1_jetst_type();}
    const std::vector<int>& l1_mus_flags() {return cms2.l1_mus_flags();}
    const std::vector<int>& l1_mus_q() {return cms2.l1_mus_q();}
    const std::vector<int>& l1_mus_qual() {return cms2.l1_mus_qual();}
    const std::vector<int>& l1_mus_qualFlags() {return cms2.l1_mus_qualFlags();}
    const std::vector<int>& mus_met_flag() {return cms2.mus_met_flag();}
    const std::vector<int>& mus_closestEle() {return cms2.mus_closestEle();}
    const std::vector<int>& mus_closestJet() {return cms2.mus_closestJet();}
    const std::vector<int>& mus_pfmusidx() {return cms2.mus_pfmusidx();}
    const std::vector<int>& mus_charge() {return cms2.mus_charge();}
    const std::vector<int>& mus_gfit_validHits() {return cms2.mus_gfit_validHits();}
    const std::vector<int>& mus_gfit_validSTAHits() {return cms2.mus_gfit_validSTAHits();}
    const std::vector<int>& mus_gfit_validSiHits() {return cms2.mus_gfit_validSiHits();}
    const std::vector<int>& mus_goodmask() {return cms2.mus_goodmask();}
    const std::vector<int>& mus_iso03_ntrk() {return cms2.mus_iso03_ntrk();}
    const std::vector<int>& mus_iso05_ntrk() {return cms2.mus_iso05_ntrk();}
    const std::vector<int>& mus_lostHits() {return cms2.mus_lostHits();}
    const std::vector<int>& mus_muonBestTrackType() {return cms2.mus_muonBestTrackType();}
    const std::vector<int>& mus_nOverlaps() {return cms2.mus_nOverlaps();}
    const std::vector<int>& mus_nmatches() {return cms2.mus_nmatches();}
    const std::vector<int>& mus_numberOfMatchedStations() {return cms2.mus_numberOfMatchedStations();}
    const std::vector<int>& mus_overlap0() {return cms2.mus_overlap0();}
    const std::vector<int>& mus_overlap1() {return cms2.mus_overlap1();}
    const std::vector<int>& mus_pfcharge() {return cms2.mus_pfcharge();}
    const std::vector<int>& mus_pfflag() {return cms2.mus_pfflag();}
    const std::vector<int>& mus_pfparticleId() {return cms2.mus_pfparticleId();}
    const std::vector<int>& mus_pid_PFMuon() {return cms2.mus_pid_PFMuon();}
    const std::vector<int>& mus_pid_TM2DCompatibilityLoose() {return cms2.mus_pid_TM2DCompatibilityLoose();}
    const std::vector<int>& mus_pid_TM2DCompatibilityTight() {return cms2.mus_pid_TM2DCompatibilityTight();}
    const std::vector<int>& mus_pid_TMLastStationLoose() {return cms2.mus_pid_TMLastStationLoose();}
    const std::vector<int>& mus_pid_TMLastStationTight() {return cms2.mus_pid_TMLastStationTight();}
    const std::vector<int>& mus_sta_validHits() {return cms2.mus_sta_validHits();}
    const std::vector<int>& mus_timeDirection() {return cms2.mus_timeDirection();}
    const std::vector<int>& mus_timeNumStationsUsed() {return cms2.mus_timeNumStationsUsed();}
    const std::vector<int>& mus_trk_charge() {return cms2.mus_trk_charge();}
    const std::vector<int>& mus_trkidx() {return cms2.mus_trkidx();}
    const std::vector<int>& mus_type() {return cms2.mus_type();}
    const std::vector<int>& mus_validHits() {return cms2.mus_validHits();}
    const std::vector<int>& pfcands_charge() {return cms2.pfcands_charge();}
    const std::vector<int>& pfcands_flag() {return cms2.pfcands_flag();}
    const std::vector<int>& pfcands_particleId() {return cms2.pfcands_particleId();}
    const std::vector<int>& pfcands_pfelsidx() {return cms2.pfcands_pfelsidx();}
    const std::vector<int>& pfcands_pfmusidx() {return cms2.pfcands_pfmusidx();}
    const std::vector<int>& pfcands_trkidx() {return cms2.pfcands_trkidx();}
    const std::vector<int>& pfcands_vtxidx() {return cms2.pfcands_vtxidx();}
    const std::vector<int>& pfels_elsidx() {return cms2.pfels_elsidx();}
    const std::vector<int>& pfels_charge() {return cms2.pfels_charge();}
    const std::vector<int>& pfels_flag() {return cms2.pfels_flag();}
    const std::vector<int>& pfels_particleId() {return cms2.pfels_particleId();}
    const std::vector<int>& pfjets_chargedHadronMultiplicity() {return cms2.pfjets_chargedHadronMultiplicity();}
    const std::vector<int>& pfjets_chargedMultiplicity() {return cms2.pfjets_chargedMultiplicity();}
    const std::vector<int>& pfjets_electronMultiplicity() {return cms2.pfjets_electronMultiplicity();}
    const std::vector<int>& pfjets_hfEmMultiplicity() {return cms2.pfjets_hfEmMultiplicity();}
    const std::vector<int>& pfjets_hfHadronMultiplicity() {return cms2.pfjets_hfHadronMultiplicity();}
    const std::vector<int>& pfjets_muonMultiplicity() {return cms2.pfjets_muonMultiplicity();}
    const std::vector<int>& pfjets_neutralHadronMultiplicity() {return cms2.pfjets_neutralHadronMultiplicity();}
    const std::vector<int>& pfjets_neutralMultiplicity() {return cms2.pfjets_neutralMultiplicity();}
    const std::vector<int>& pfjets_photonMultiplicity() {return cms2.pfjets_photonMultiplicity();}
    const std::vector<int>& pfmus_musidx() {return cms2.pfmus_musidx();}
    const std::vector<int>& pfmus_charge() {return cms2.pfmus_charge();}
    const std::vector<int>& pfmus_flag() {return cms2.pfmus_flag();}
    const std::vector<int>& pfmus_particleId() {return cms2.pfmus_particleId();}
    const std::vector<int>& taus_pf_charge() {return cms2.taus_pf_charge();}
    const std::vector<int>& taus_pf_pfjetIndex() {return cms2.taus_pf_pfjetIndex();}
    const std::vector<int>& photons_fiduciality() {return cms2.photons_fiduciality();}
    const std::vector<int>& photons_scindex() {return cms2.photons_scindex();}
    const std::vector<int>& puInfo_bunchCrossing() {return cms2.puInfo_bunchCrossing();}
    const std::vector<int>& puInfo_nPUvertices() {return cms2.puInfo_nPUvertices();}
    const std::vector<int>& convs_algo() {return cms2.convs_algo();}
    const std::vector<int>& convs_isConverted() {return cms2.convs_isConverted();}
    const std::vector<int>& convs_quality() {return cms2.convs_quality();}
    const std::vector<int>& scs_detIdSeed() {return cms2.scs_detIdSeed();}
    const std::vector<int>& scs_elsidx() {return cms2.scs_elsidx();}
    const std::vector<int>& scs_severitySeed() {return cms2.scs_severitySeed();}
    const std::vector<int>& svs_isKs() {return cms2.svs_isKs();}
    const std::vector<int>& svs_isLambda() {return cms2.svs_isLambda();}
    const std::vector<int>& svs_mc3_id() {return cms2.svs_mc3_id();}
    const std::vector<int>& svs_nTrks() {return cms2.svs_nTrks();}
    const std::vector<int>& mus_tcmet_flag() {return cms2.mus_tcmet_flag();}
    const std::vector<int>& trks_algo() {return cms2.trks_algo();}
    const std::vector<int>& trks_charge() {return cms2.trks_charge();}
    const std::vector<int>& trks_exp_innerlayers() {return cms2.trks_exp_innerlayers();}
    const std::vector<int>& trks_exp_outerlayers() {return cms2.trks_exp_outerlayers();}
    const std::vector<int>& trks_layer1_det() {return cms2.trks_layer1_det();}
    const std::vector<int>& trks_layer1_layer() {return cms2.trks_layer1_layer();}
    const std::vector<int>& trks_layer1_sizerphi() {return cms2.trks_layer1_sizerphi();}
    const std::vector<int>& trks_layer1_sizerz() {return cms2.trks_layer1_sizerz();}
    const std::vector<int>& trks_lostHits() {return cms2.trks_lostHits();}
    const std::vector<int>& trks_lost_pixelhits() {return cms2.trks_lost_pixelhits();}
    const std::vector<int>& trks_nLoops() {return cms2.trks_nLoops();}
    const std::vector<int>& trks_nlayers() {return cms2.trks_nlayers();}
    const std::vector<int>& trks_nlayers3D() {return cms2.trks_nlayers3D();}
    const std::vector<int>& trks_nlayersLost() {return cms2.trks_nlayersLost();}
    const std::vector<int>& trks_pvidx0() {return cms2.trks_pvidx0();}
    const std::vector<int>& trks_pvidx1() {return cms2.trks_pvidx1();}
    const std::vector<int>& trks_qualityMask() {return cms2.trks_qualityMask();}
    const std::vector<int>& trks_validHits() {return cms2.trks_validHits();}
    const std::vector<int>& trks_valid_pixelhits() {return cms2.trks_valid_pixelhits();}
    const std::vector<int>& trks_elsidx() {return cms2.trks_elsidx();}
    const std::vector<int>& trk_musidx() {return cms2.trk_musidx();}
    const std::vector<int>& trkjets_ntrks() {return cms2.trkjets_ntrks();}
    const std::vector<int>& trkjets_vtxs_idx() {return cms2.trkjets_vtxs_idx();}
    const std::vector<int>& vtxs_isFake() {return cms2.vtxs_isFake();}
    const std::vector<int>& vtxs_isValid() {return cms2.vtxs_isValid();}
    const std::vector<int>& vtxs_tracksSize() {return cms2.vtxs_tracksSize();}
    const std::vector<int>& bsvtxs_isFake() {return cms2.bsvtxs_isFake();}
    const std::vector<int>& bsvtxs_isValid() {return cms2.bsvtxs_isValid();}
    const std::vector<int>& bsvtxs_tracksSize() {return cms2.bsvtxs_tracksSize();}
    const std::vector<std::vector<int> >& els_convs_delMissHits() {return cms2.els_convs_delMissHits();}
    const std::vector<std::vector<int> >& els_convs_flag() {return cms2.els_convs_flag();}
    const std::vector<std::vector<int> >& els_convs_gsftkidx() {return cms2.els_convs_gsftkidx();}
    const std::vector<std::vector<int> >& els_convs_tkidx() {return cms2.els_convs_tkidx();}
    const std::vector<std::vector<int> >& genps_lepdaughter_id() {return cms2.genps_lepdaughter_id();}
    const std::vector<std::vector<int> >& genps_lepdaughter_idx() {return cms2.genps_lepdaughter_idx();}
    const std::vector<std::vector<int> >& hlt_trigObjs_id() {return cms2.hlt_trigObjs_id();}
    const std::vector<std::vector<int> >& hyp_jets_idx() {return cms2.hyp_jets_idx();}
    const std::vector<std::vector<int> >& hyp_other_jets_idx() {return cms2.hyp_other_jets_idx();}
    const std::vector<std::vector<int> >& mus_nStationCorrelatedHits() {return cms2.mus_nStationCorrelatedHits();}
    const std::vector<std::vector<int> >& mus_nStationHits() {return cms2.mus_nStationHits();}
    const std::vector<std::vector<int> >& pfjets_pfcandIndicies() {return cms2.pfjets_pfcandIndicies();}
    const std::vector<std::vector<int> >& taus_pf_pfcandIndicies() {return cms2.taus_pf_pfcandIndicies();}
    const std::vector<std::vector<int> >& puInfo_ntrks_highpt() {return cms2.puInfo_ntrks_highpt();}
    const std::vector<std::vector<int> >& puInfo_ntrks_lowpt() {return cms2.puInfo_ntrks_lowpt();}
    const std::vector<std::vector<int> >& convs_nHitsBeforeVtx() {return cms2.convs_nHitsBeforeVtx();}
    const std::vector<std::vector<int> >& convs_tkalgo() {return cms2.convs_tkalgo();}
    const std::vector<std::vector<int> >& convs_tkidx() {return cms2.convs_tkidx();}
    const unsigned int& els_HLT_Ele17_Ele8_L1sL1DoubleEG137_version() {return cms2.els_HLT_Ele17_Ele8_L1sL1DoubleEG137_version();}
    const unsigned int& els_HLT_Ele17_Ele8_LeadingLeg_version() {return cms2.els_HLT_Ele17_Ele8_LeadingLeg_version();}
    const unsigned int& els_HLT_Ele17_Ele8_Mass50_LeadingLeg_version() {return cms2.els_HLT_Ele17_Ele8_Mass50_LeadingLeg_version();}
    const unsigned int& els_HLT_Ele17_Ele8_Mass50_TrailingLeg_version() {return cms2.els_HLT_Ele17_Ele8_Mass50_TrailingLeg_version();}
    const unsigned int& els_HLT_Ele17_Ele8_TrailingLeg_version() {return cms2.els_HLT_Ele17_Ele8_TrailingLeg_version();}
    const unsigned int& els_HLT_Ele17_Ele8_version() {return cms2.els_HLT_Ele17_Ele8_version();}
    const unsigned int& els_HLT_Ele20_SC4_Mass50_LeadingLeg_version() {return cms2.els_HLT_Ele20_SC4_Mass50_LeadingLeg_version();}
    const unsigned int& els_HLT_Ele20_SC4_Mass50_TrailingLeg_version() {return cms2.els_HLT_Ele20_SC4_Mass50_TrailingLeg_version();}
    const unsigned int& els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_version() {return cms2.els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_version();}
    const unsigned int& els_HLT_Ele27_WP80_version() {return cms2.els_HLT_Ele27_WP80_version();}
    const unsigned int& els_HLT_Ele32_SC17_Mass50_LeadingLeg_version() {return cms2.els_HLT_Ele32_SC17_Mass50_LeadingLeg_version();}
    const unsigned int& els_HLT_Ele32_SC17_Mass50_TrailingLeg_version() {return cms2.els_HLT_Ele32_SC17_Mass50_TrailingLeg_version();}
    const unsigned int& els_HLT_Mu17_Ele8_TrailingLeg_version() {return cms2.els_HLT_Mu17_Ele8_TrailingLeg_version();}
    const unsigned int& els_HLT_Mu17_Ele8_version() {return cms2.els_HLT_Mu17_Ele8_version();}
    const unsigned int& els_HLT_Mu8_Ele17_version() {return cms2.els_HLT_Mu8_Ele17_version();}
    const unsigned int& evt_nels() {return cms2.evt_nels();}
    const unsigned int& evt_detectorStatus() {return cms2.evt_detectorStatus();}
    const unsigned int& evt_event() {return cms2.evt_event();}
    const unsigned int& evt_lumiBlock() {return cms2.evt_lumiBlock();}
    const unsigned int& evt_run() {return cms2.evt_run();}
    const unsigned int& genps_flavorHistoryFilterResult() {return cms2.genps_flavorHistoryFilterResult();}
    const unsigned int& evt_ngenjets() {return cms2.evt_ngenjets();}
    const unsigned int& genps_signalProcessID() {return cms2.genps_signalProcessID();}
    const unsigned int& evt_njets() {return cms2.evt_njets();}
    const unsigned int& l1_bits1() {return cms2.l1_bits1();}
    const unsigned int& l1_bits2() {return cms2.l1_bits2();}
    const unsigned int& l1_bits3() {return cms2.l1_bits3();}
    const unsigned int& l1_bits4() {return cms2.l1_bits4();}
    const unsigned int& l1_techbits1() {return cms2.l1_techbits1();}
    const unsigned int& l1_techbits2() {return cms2.l1_techbits2();}
    const unsigned int& ls_lsNumber() {return cms2.ls_lsNumber();}
    const unsigned int& ls_numOrbit() {return cms2.ls_numOrbit();}
    const unsigned int& ls_startOrbit() {return cms2.ls_startOrbit();}
    const unsigned int& mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_version() {return cms2.mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_version();}
    const unsigned int& mus_HLT_IsoMu24_eta2p1_version() {return cms2.mus_HLT_IsoMu24_eta2p1_version();}
    const unsigned int& mus_HLT_Mu17_Ele8_LeadingLeg_version() {return cms2.mus_HLT_Mu17_Ele8_LeadingLeg_version();}
    const unsigned int& mus_HLT_Mu17_Ele8_version() {return cms2.mus_HLT_Mu17_Ele8_version();}
    const unsigned int& mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_version() {return cms2.mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_version();}
    const unsigned int& mus_HLT_Mu17_Mu8_LeadingLeg_version() {return cms2.mus_HLT_Mu17_Mu8_LeadingLeg_version();}
    const unsigned int& mus_HLT_Mu17_Mu8_TrailingLeg_version() {return cms2.mus_HLT_Mu17_Mu8_TrailingLeg_version();}
    const unsigned int& mus_HLT_Mu17_Mu8_version() {return cms2.mus_HLT_Mu17_Mu8_version();}
    const unsigned int& mus_HLT_Mu17_TkMu8_LeadingLeg_version() {return cms2.mus_HLT_Mu17_TkMu8_LeadingLeg_version();}
    const unsigned int& mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_version() {return cms2.mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered_version();}
    const unsigned int& mus_HLT_Mu17_TkMu8_TrailingLeg_version() {return cms2.mus_HLT_Mu17_TkMu8_TrailingLeg_version();}
    const unsigned int& mus_HLT_Mu17_TkMu8_version() {return cms2.mus_HLT_Mu17_TkMu8_version();}
    const unsigned int& mus_HLT_Mu8_Ele17_TrailingLeg_version() {return cms2.mus_HLT_Mu8_Ele17_TrailingLeg_version();}
    const unsigned int& mus_HLT_Mu8_Ele17_version() {return cms2.mus_HLT_Mu8_Ele17_version();}
    const unsigned int& evt_nphotons() {return cms2.evt_nphotons();}
    const unsigned int& evt_ecalRecoStatus() {return cms2.evt_ecalRecoStatus();}
    const unsigned int& evt_nscs() {return cms2.evt_nscs();}
    const unsigned int& evt_ntrkjets() {return cms2.evt_ntrkjets();}
    const unsigned int& evt_nvtxs() {return cms2.evt_nvtxs();}
    const unsigned int& evt_nbsvtxs() {return cms2.evt_nbsvtxs();}
    const std::vector<unsigned int>& els_HLT_Ele17_Ele8() {return cms2.els_HLT_Ele17_Ele8();}
    const std::vector<unsigned int>& els_HLT_Ele17_Ele8_L1sL1DoubleEG137() {return cms2.els_HLT_Ele17_Ele8_L1sL1DoubleEG137();}
    const std::vector<unsigned int>& els_HLT_Ele17_Ele8_LeadingLeg() {return cms2.els_HLT_Ele17_Ele8_LeadingLeg();}
    const std::vector<unsigned int>& els_HLT_Ele17_Ele8_Mass50_LeadingLeg() {return cms2.els_HLT_Ele17_Ele8_Mass50_LeadingLeg();}
    const std::vector<unsigned int>& els_HLT_Ele17_Ele8_Mass50_TrailingLeg() {return cms2.els_HLT_Ele17_Ele8_Mass50_TrailingLeg();}
    const std::vector<unsigned int>& els_HLT_Ele17_Ele8_TrailingLeg() {return cms2.els_HLT_Ele17_Ele8_TrailingLeg();}
    const std::vector<unsigned int>& els_HLT_Ele20_SC4_Mass50_LeadingLeg() {return cms2.els_HLT_Ele20_SC4_Mass50_LeadingLeg();}
    const std::vector<unsigned int>& els_HLT_Ele20_SC4_Mass50_TrailingLeg() {return cms2.els_HLT_Ele20_SC4_Mass50_TrailingLeg();}
    const std::vector<unsigned int>& els_HLT_Ele27_WP80() {return cms2.els_HLT_Ele27_WP80();}
    const std::vector<unsigned int>& els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22() {return cms2.els_HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22();}
    const std::vector<unsigned int>& els_HLT_Ele32_SC17_Mass50_LeadingLeg() {return cms2.els_HLT_Ele32_SC17_Mass50_LeadingLeg();}
    const std::vector<unsigned int>& els_HLT_Ele32_SC17_Mass50_TrailingLeg() {return cms2.els_HLT_Ele32_SC17_Mass50_TrailingLeg();}
    const std::vector<unsigned int>& els_HLT_Mu17_Ele8() {return cms2.els_HLT_Mu17_Ele8();}
    const std::vector<unsigned int>& els_HLT_Mu17_Ele8_TrailingLeg() {return cms2.els_HLT_Mu17_Ele8_TrailingLeg();}
    const std::vector<unsigned int>& els_HLT_Mu8_Ele17() {return cms2.els_HLT_Mu8_Ele17();}
    const std::vector<unsigned int>& els_id2012ext_loose() {return cms2.els_id2012ext_loose();}
    const std::vector<unsigned int>& els_id2012ext_medium() {return cms2.els_id2012ext_medium();}
    const std::vector<unsigned int>& els_id2012ext_tight() {return cms2.els_id2012ext_tight();}
    const std::vector<unsigned int>& els_id2012ext_veto() {return cms2.els_id2012ext_veto();}
    const std::vector<unsigned int>& els_id2012_loose() {return cms2.els_id2012_loose();}
    const std::vector<unsigned int>& els_id2012_medium() {return cms2.els_id2012_medium();}
    const std::vector<unsigned int>& els_id2012_tight() {return cms2.els_id2012_tight();}
    const std::vector<unsigned int>& els_id2012_veto() {return cms2.els_id2012_veto();}
    const std::vector<unsigned int>& hlt_prescales() {return cms2.hlt_prescales();}
    const std::vector<unsigned int>& l1_prescales() {return cms2.l1_prescales();}
    const std::vector<unsigned int>& l1_techtrigprescales() {return cms2.l1_techtrigprescales();}
    const std::vector<unsigned int>& mus_HLT_IsoMu24_eta2p1() {return cms2.mus_HLT_IsoMu24_eta2p1();}
    const std::vector<unsigned int>& mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1() {return cms2.mus_HLT_IsoMu24_eta2p1_L1sMu16Eta2p1();}
    const std::vector<unsigned int>& mus_HLT_Mu17_Ele8() {return cms2.mus_HLT_Mu17_Ele8();}
    const std::vector<unsigned int>& mus_HLT_Mu17_Ele8_LeadingLeg() {return cms2.mus_HLT_Mu17_Ele8_LeadingLeg();}
    const std::vector<unsigned int>& mus_HLT_Mu17_Mu8() {return cms2.mus_HLT_Mu17_Mu8();}
    const std::vector<unsigned int>& mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen() {return cms2.mus_HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen();}
    const std::vector<unsigned int>& mus_HLT_Mu17_Mu8_LeadingLeg() {return cms2.mus_HLT_Mu17_Mu8_LeadingLeg();}
    const std::vector<unsigned int>& mus_HLT_Mu17_Mu8_TrailingLeg() {return cms2.mus_HLT_Mu17_Mu8_TrailingLeg();}
    const std::vector<unsigned int>& mus_HLT_Mu17_TkMu8() {return cms2.mus_HLT_Mu17_TkMu8();}
    const std::vector<unsigned int>& mus_HLT_Mu17_TkMu8_LeadingLeg() {return cms2.mus_HLT_Mu17_TkMu8_LeadingLeg();}
    const std::vector<unsigned int>& mus_HLT_Mu17_TkMu8_TrailingLeg() {return cms2.mus_HLT_Mu17_TkMu8_TrailingLeg();}
    const std::vector<unsigned int>& mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered() {return cms2.mus_HLT_Mu17_TkMu8_TrailingLegTrkFiltered();}
    const std::vector<unsigned int>& mus_HLT_Mu8_Ele17() {return cms2.mus_HLT_Mu8_Ele17();}
    const std::vector<unsigned int>& mus_HLT_Mu8_Ele17_TrailingLeg() {return cms2.mus_HLT_Mu8_Ele17_TrailingLeg();}
    const unsigned long long& evt_timestamp() {return cms2.evt_timestamp();}

} // namespace tas


#endif //CMS2_USE_CMSSW

