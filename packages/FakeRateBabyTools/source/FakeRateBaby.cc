#include "FakeRateBaby.h"
FakeRateBaby fake_rate_baby;
namespace frb {
	const int &run() { return fake_rate_baby.run(); }
	const int &ls() { return fake_rate_baby.ls(); }
	const unsigned int &evt() { return fake_rate_baby.evt(); }
	const float &weight() { return fake_rate_baby.weight(); }
	const bool &is_real_data() { return fake_rate_baby.is_real_data(); }
	const TString &dataset() { return fake_rate_baby.dataset(); }
	const TString &filename() { return fake_rate_baby.filename(); }
	const int &pu_nPUvertices() { return fake_rate_baby.pu_nPUvertices(); }
	const float &pu_nPUtrueint() { return fake_rate_baby.pu_nPUtrueint(); }
	const int &evt_nvtxs() { return fake_rate_baby.evt_nvtxs(); }
	const int &nFOels() { return fake_rate_baby.nFOels(); }
	const int &nFOmus() { return fake_rate_baby.nFOmus(); }
	const int &ngsfs() { return fake_rate_baby.ngsfs(); }
	const int &nmus() { return fake_rate_baby.nmus(); }
	const int &nvetoels() { return fake_rate_baby.nvetoels(); }
	const int &nvetomus() { return fake_rate_baby.nvetomus(); }
	const int &nloosemus() { return fake_rate_baby.nloosemus(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lp4() { return fake_rate_baby.lp4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &mc3p4() { return fake_rate_baby.mc3p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &foel_p4() { return fake_rate_baby.foel_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &fomu_p4() { return fake_rate_baby.fomu_p4(); }
	const int &foel_id() { return fake_rate_baby.foel_id(); }
	const int &fomu_id() { return fake_rate_baby.fomu_id(); }
	const float &foel_mass() { return fake_rate_baby.foel_mass(); }
	const float &fomu_mass() { return fake_rate_baby.fomu_mass(); }
	const float &pt() { return fake_rate_baby.pt(); }
	const float &eta() { return fake_rate_baby.eta(); }
	const float &sceta() { return fake_rate_baby.sceta(); }
	const float &phi() { return fake_rate_baby.phi(); }
	const float &scet() { return fake_rate_baby.scet(); }
	const float &d0() { return fake_rate_baby.d0(); }
	const float &dz() { return fake_rate_baby.dz(); }
	const float &ip3d() { return fake_rate_baby.ip3d(); }
	const float &d0err() { return fake_rate_baby.d0err(); }
	const float &dzerr() { return fake_rate_baby.dzerr(); }
	const float &ip3derr() { return fake_rate_baby.ip3derr(); }
	const float &hoe() { return fake_rate_baby.hoe(); }
	const float &pfmet() { return fake_rate_baby.pfmet(); }
	const float &pfmetphi() { return fake_rate_baby.pfmetphi(); }
	const float &iso() { return fake_rate_baby.iso(); }
	const float &iso_nps() { return fake_rate_baby.iso_nps(); }
	const float &trck_iso() { return fake_rate_baby.trck_iso(); }
	const float &ecal_iso() { return fake_rate_baby.ecal_iso(); }
	const float &ecal_iso_nps() { return fake_rate_baby.ecal_iso_nps(); }
	const float &hcal_iso() { return fake_rate_baby.hcal_iso(); }
	const float &pfiso03() { return fake_rate_baby.pfiso03(); }
	const float &ch_pfiso03() { return fake_rate_baby.ch_pfiso03(); }
	const float &nh_pfiso03() { return fake_rate_baby.nh_pfiso03(); }
	const float &em_pfiso03() { return fake_rate_baby.em_pfiso03(); }
	const float &pfiso04() { return fake_rate_baby.pfiso04(); }
	const float &ch_pfiso04() { return fake_rate_baby.ch_pfiso04(); }
	const float &nh_pfiso04() { return fake_rate_baby.nh_pfiso04(); }
	const float &em_pfiso04() { return fake_rate_baby.em_pfiso04(); }
	const float &pfpupt03() { return fake_rate_baby.pfpupt03(); }
	const float &pfpupt04() { return fake_rate_baby.pfpupt04(); }
	const float &cpfiso03_rho() { return fake_rate_baby.cpfiso03_rho(); }
	const float &cpfiso04_rho() { return fake_rate_baby.cpfiso04_rho(); }
	const float &cpfiso03_db() { return fake_rate_baby.cpfiso03_db(); }
	const int &id() { return fake_rate_baby.id(); }
	const bool &closestMuon() { return fake_rate_baby.closestMuon(); }
	const float &el_id_sieie() { return fake_rate_baby.el_id_sieie(); }
	const float &el_id_detain() { return fake_rate_baby.el_id_detain(); }
	const float &el_id_dphiin() { return fake_rate_baby.el_id_dphiin(); }
	const bool &el_id_smurfV5() { return fake_rate_baby.el_id_smurfV5(); }
	const bool &el_id_vbtf80() { return fake_rate_baby.el_id_vbtf80(); }
	const bool &el_id_vbtf90() { return fake_rate_baby.el_id_vbtf90(); }
	const float &el_effarea03() { return fake_rate_baby.el_effarea03(); }
	const float &el_effarea04() { return fake_rate_baby.el_effarea04(); }
	const float &mu_effarea03() { return fake_rate_baby.mu_effarea03(); }
	const float &mu_nh_effarea03() { return fake_rate_baby.mu_nh_effarea03(); }
	const float &mu_em_effarea03() { return fake_rate_baby.mu_em_effarea03(); }
	const float &mu_effarea03_tight() { return fake_rate_baby.mu_effarea03_tight(); }
	const float &mu_nh_effarea03_tight() { return fake_rate_baby.mu_nh_effarea03_tight(); }
	const float &mu_em_effarea03_tight() { return fake_rate_baby.mu_em_effarea03_tight(); }
	const float &mu_effarea04() { return fake_rate_baby.mu_effarea04(); }
	const float &mu_nh_effarea04() { return fake_rate_baby.mu_nh_effarea04(); }
	const float &mu_em_effarea04() { return fake_rate_baby.mu_em_effarea04(); }
	const float &mu_effarea04_tight() { return fake_rate_baby.mu_effarea04_tight(); }
	const float &mu_nh_effarea04_tight() { return fake_rate_baby.mu_nh_effarea04_tight(); }
	const float &mu_em_effarea04_tight() { return fake_rate_baby.mu_em_effarea04_tight(); }
	const bool &conv0MissHits() { return fake_rate_baby.conv0MissHits(); }
	const bool &convHitPattern() { return fake_rate_baby.convHitPattern(); }
	const bool &convPartnerTrack() { return fake_rate_baby.convPartnerTrack(); }
	const bool &convMIT() { return fake_rate_baby.convMIT(); }
	const float &mt() { return fake_rate_baby.mt(); }
	const float &pfmt() { return fake_rate_baby.pfmt(); }
	const bool &q3() { return fake_rate_baby.q3(); }
	const int &els_exp_innerlayers() { return fake_rate_baby.els_exp_innerlayers(); }
	const float &d0PV_wwV1() { return fake_rate_baby.d0PV_wwV1(); }
	const float &dzPV_wwV1() { return fake_rate_baby.dzPV_wwV1(); }
	const float &ht_pf() { return fake_rate_baby.ht_pf(); }
	const float &ht_pf_L2L3() { return fake_rate_baby.ht_pf_L2L3(); }
	const float &ht_pf_L1FastL2L3() { return fake_rate_baby.ht_pf_L1FastL2L3(); }
	const int &mcid() { return fake_rate_baby.mcid(); }
	const int &mcmotherid() { return fake_rate_baby.mcmotherid(); }
	const int &mc3id() { return fake_rate_baby.mc3id(); }
	const float &mc3pt() { return fake_rate_baby.mc3pt(); }
	const float &mc3dr() { return fake_rate_baby.mc3dr(); }
	const int &leptonIsFromW() { return fake_rate_baby.leptonIsFromW(); }
	const bool &mu_isCosmic() { return fake_rate_baby.mu_isCosmic(); }
	const float &mu_ecal_veto_dep() { return fake_rate_baby.mu_ecal_veto_dep(); }
	const float &mu_hcal_veto_dep() { return fake_rate_baby.mu_hcal_veto_dep(); }
	const float &mu_nchi2() { return fake_rate_baby.mu_nchi2(); }
	const float &mz_fo_gsf() { return fake_rate_baby.mz_fo_gsf(); }
	const float &mz_gsf_iso() { return fake_rate_baby.mz_gsf_iso(); }
	const float &mz_fo_ctf() { return fake_rate_baby.mz_fo_ctf(); }
	const float &mz_ctf_iso() { return fake_rate_baby.mz_ctf_iso(); }
	const float &mupsilon_fo_mu() { return fake_rate_baby.mupsilon_fo_mu(); }
	const float &mupsilon_mu_iso() { return fake_rate_baby.mupsilon_mu_iso(); }
	const float &mu_nchi2global() { return fake_rate_baby.mu_nchi2global(); }
	const bool &mu_isGlobal() { return fake_rate_baby.mu_isGlobal(); }
	const bool &mu_isPF() { return fake_rate_baby.mu_isPF(); }
	const int &mu_numberOfValidMuonHits() { return fake_rate_baby.mu_numberOfValidMuonHits(); }
	const int &mu_numberOfMatchedStations() { return fake_rate_baby.mu_numberOfMatchedStations(); }
	const int &mu_trackerLayersWithMeasurement() { return fake_rate_baby.mu_trackerLayersWithMeasurement(); }
	const int &mu_numberOfValidPixelHits() { return fake_rate_baby.mu_numberOfValidPixelHits(); }
	const bool &num_el_ssV7() { return fake_rate_baby.num_el_ssV7(); }
	const bool &num_el_ssV7_noIso() { return fake_rate_baby.num_el_ssV7_noIso(); }
	const bool &v1_el_ssV7() { return fake_rate_baby.v1_el_ssV7(); }
	const bool &v2_el_ssV7() { return fake_rate_baby.v2_el_ssV7(); }
	const bool &v3_el_ssV7() { return fake_rate_baby.v3_el_ssV7(); }
	const bool &num_mu_ssV5() { return fake_rate_baby.num_mu_ssV5(); }
	const bool &num_mu_ssV5_noIso() { return fake_rate_baby.num_mu_ssV5_noIso(); }
	const bool &fo_mu_ssV5() { return fake_rate_baby.fo_mu_ssV5(); }
	const bool &fo_mu_ssV5_noIso() { return fake_rate_baby.fo_mu_ssV5_noIso(); }
	const bool &num_el_TTZcuttightv1() { return fake_rate_baby.num_el_TTZcuttightv1(); }
	const bool &num_el_TTZcuttightv1_noIso() { return fake_rate_baby.num_el_TTZcuttightv1_noIso(); }
	const bool &fo_el_TTZcuttightv1() { return fake_rate_baby.fo_el_TTZcuttightv1(); }
	const bool &fo_el_TTZcuttightv1_noIso() { return fake_rate_baby.fo_el_TTZcuttightv1_noIso(); }
	const bool &num_el_TTZcutloosev1() { return fake_rate_baby.num_el_TTZcutloosev1(); }
	const bool &num_el_TTZcutloosev1_noIso() { return fake_rate_baby.num_el_TTZcutloosev1_noIso(); }
	const bool &fo_el_TTZcutloosev1() { return fake_rate_baby.fo_el_TTZcutloosev1(); }
	const bool &fo_el_TTZcutloosev1_noIso() { return fake_rate_baby.fo_el_TTZcutloosev1_noIso(); }
	const bool &num_el_TTZMVAtightv1() { return fake_rate_baby.num_el_TTZMVAtightv1(); }
	const bool &num_el_TTZMVAtightv1_noIso() { return fake_rate_baby.num_el_TTZMVAtightv1_noIso(); }
	const bool &fo_el_TTZMVAtightv1() { return fake_rate_baby.fo_el_TTZMVAtightv1(); }
	const bool &fo_el_TTZMVAtightv1_noIso() { return fake_rate_baby.fo_el_TTZMVAtightv1_noIso(); }
	const bool &num_el_TTZMVAloosev1() { return fake_rate_baby.num_el_TTZMVAloosev1(); }
	const bool &num_el_TTZMVAloosev1_noIso() { return fake_rate_baby.num_el_TTZMVAloosev1_noIso(); }
	const bool &fo_el_TTZMVAloosev1() { return fake_rate_baby.fo_el_TTZMVAloosev1(); }
	const bool &fo_el_TTZMVAloosev1_noIso() { return fake_rate_baby.fo_el_TTZMVAloosev1_noIso(); }
	const bool &num_mu_TTZtightv1() { return fake_rate_baby.num_mu_TTZtightv1(); }
	const bool &num_mu_TTZtightv1_noIso() { return fake_rate_baby.num_mu_TTZtightv1_noIso(); }
	const bool &fo_mu_TTZtightv1() { return fake_rate_baby.fo_mu_TTZtightv1(); }
	const bool &fo_mu_TTZtightv1_noIso() { return fake_rate_baby.fo_mu_TTZtightv1_noIso(); }
	const bool &num_mu_TTZloosev1() { return fake_rate_baby.num_mu_TTZloosev1(); }
	const bool &num_mu_TTZloosev1_noIso() { return fake_rate_baby.num_mu_TTZloosev1_noIso(); }
	const bool &fo_mu_TTZloosev1() { return fake_rate_baby.fo_mu_TTZloosev1(); }
	const bool &fo_mu_TTZloosev1_noIso() { return fake_rate_baby.fo_mu_TTZloosev1_noIso(); }
	const bool &num_el_ssV6() { return fake_rate_baby.num_el_ssV6(); }
	const bool &num_el_ssV6_noIso() { return fake_rate_baby.num_el_ssV6_noIso(); }
	const bool &v1_el_ssV6() { return fake_rate_baby.v1_el_ssV6(); }
	const bool &v2_el_ssV6() { return fake_rate_baby.v2_el_ssV6(); }
	const bool &v3_el_ssV6() { return fake_rate_baby.v3_el_ssV6(); }
	const bool &numNomSSv4() { return fake_rate_baby.numNomSSv4(); }
	const bool &numNomSSv4noIso() { return fake_rate_baby.numNomSSv4noIso(); }
	const bool &fo_mussV4_04() { return fake_rate_baby.fo_mussV4_04(); }
	const bool &fo_mussV4_noIso() { return fake_rate_baby.fo_mussV4_noIso(); }
	const bool &num_el_smurfV6() { return fake_rate_baby.num_el_smurfV6(); }
	const bool &num_el_smurfV6lh() { return fake_rate_baby.num_el_smurfV6lh(); }
	const bool &v1_el_smurfV1() { return fake_rate_baby.v1_el_smurfV1(); }
	const bool &v2_el_smurfV1() { return fake_rate_baby.v2_el_smurfV1(); }
	const bool &v3_el_smurfV1() { return fake_rate_baby.v3_el_smurfV1(); }
	const bool &v4_el_smurfV1() { return fake_rate_baby.v4_el_smurfV1(); }
	const bool &num_mu_smurfV6() { return fake_rate_baby.num_mu_smurfV6(); }
	const bool &fo_mu_smurf_04() { return fake_rate_baby.fo_mu_smurf_04(); }
	const bool &fo_mu_smurf_10() { return fake_rate_baby.fo_mu_smurf_10(); }
	const bool &num_el_OSV2() { return fake_rate_baby.num_el_OSV2(); }
	const bool &num_mu_OSGV2() { return fake_rate_baby.num_mu_OSGV2(); }
	const bool &num_mu_OSZV2() { return fake_rate_baby.num_mu_OSZV2(); }
	const bool &fo_el_OSV2() { return fake_rate_baby.fo_el_OSV2(); }
	const bool &fo_mu_OSGV2() { return fake_rate_baby.fo_mu_OSGV2(); }
	const bool &num_el_OSV3() { return fake_rate_baby.num_el_OSV3(); }
	const bool &num_mu_OSGV3() { return fake_rate_baby.num_mu_OSGV3(); }
	const bool &fo_el_OSV3() { return fake_rate_baby.fo_el_OSV3(); }
	const bool &fo_mu_OSGV3() { return fake_rate_baby.fo_mu_OSGV3(); }
	const int &ele8_vstar() { return fake_rate_baby.ele8_vstar(); }
	const int &ele8_CaloIdL_TrkIdVL_vstar() { return fake_rate_baby.ele8_CaloIdL_TrkIdVL_vstar(); }
	const int &ele8_CaloIdL_CaloIsoVL_Jet40_vstar() { return fake_rate_baby.ele8_CaloIdL_CaloIsoVL_Jet40_vstar(); }
	const int &ele8_CaloIdL_CaloIsoVL_vstar() { return fake_rate_baby.ele8_CaloIdL_CaloIsoVL_vstar(); }
	const int &ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar() { return fake_rate_baby.ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar(); }
	const int &ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar() { return fake_rate_baby.ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar(); }
	const int &ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar() { return fake_rate_baby.ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar(); }
	const int &ele8_CaloIdT_TrkIdVL_vstar() { return fake_rate_baby.ele8_CaloIdT_TrkIdVL_vstar(); }
	const int &ele8_CaloIdT_TrkIdVL_Jet30_vstar() { return fake_rate_baby.ele8_CaloIdT_TrkIdVL_Jet30_vstar(); }
	const int &ele17_CaloIdL_CaloIsoVL_vstar() { return fake_rate_baby.ele17_CaloIdL_CaloIsoVL_vstar(); }
	const int &ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar() { return fake_rate_baby.ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar(); }
	const int &ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar() { return fake_rate_baby.ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar(); }
	const int &photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar() { return fake_rate_baby.photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar(); }
	const int &ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar() { return fake_rate_baby.ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar(); }
	const int &ele27_WP80_vstar() { return fake_rate_baby.ele27_WP80_vstar(); }
	const int &ele8_version() { return fake_rate_baby.ele8_version(); }
	const int &ele8_CaloIdL_TrkIdVL_version() { return fake_rate_baby.ele8_CaloIdL_TrkIdVL_version(); }
	const int &ele8_CaloIdL_CaloIsoVL_Jet40_version() { return fake_rate_baby.ele8_CaloIdL_CaloIsoVL_Jet40_version(); }
	const int &ele8_CaloIdL_CaloIsoVL_version() { return fake_rate_baby.ele8_CaloIdL_CaloIsoVL_version(); }
	const int &ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version() { return fake_rate_baby.ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version(); }
	const int &ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version() { return fake_rate_baby.ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version(); }
	const int &ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version() { return fake_rate_baby.ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version(); }
	const int &ele8_CaloIdT_TrkIdVL_version() { return fake_rate_baby.ele8_CaloIdT_TrkIdVL_version(); }
	const int &ele8_CaloIdT_TrkIdVL_Jet30_version() { return fake_rate_baby.ele8_CaloIdT_TrkIdVL_Jet30_version(); }
	const int &ele17_CaloIdL_CaloIsoVL_version() { return fake_rate_baby.ele17_CaloIdL_CaloIsoVL_version(); }
	const int &ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version() { return fake_rate_baby.ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version(); }
	const int &ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version() { return fake_rate_baby.ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version(); }
	const int &photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version() { return fake_rate_baby.photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version(); }
	const int &ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_version() { return fake_rate_baby.ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_version(); }
	const int &ele27_WP80_version() { return fake_rate_baby.ele27_WP80_version(); }
	const float &dr_ele8_vstar() { return fake_rate_baby.dr_ele8_vstar(); }
	const float &dr_ele8_CaloIdL_TrkIdVL_vstar() { return fake_rate_baby.dr_ele8_CaloIdL_TrkIdVL_vstar(); }
	const float &dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar() { return fake_rate_baby.dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar(); }
	const float &dr_ele8_CaloIdL_CaloIsoVL_vstar() { return fake_rate_baby.dr_ele8_CaloIdL_CaloIsoVL_vstar(); }
	const float &dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar() { return fake_rate_baby.dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar(); }
	const float &dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar() { return fake_rate_baby.dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar(); }
	const float &dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar() { return fake_rate_baby.dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar(); }
	const float &dr_ele8_CaloIdT_TrkIdVL_vstar() { return fake_rate_baby.dr_ele8_CaloIdT_TrkIdVL_vstar(); }
	const float &dr_ele8_CaloIdT_TrkIdVL_Jet30_vstar() { return fake_rate_baby.dr_ele8_CaloIdT_TrkIdVL_Jet30_vstar(); }
	const float &dr_ele17_CaloIdL_CaloIsoVL_vstar() { return fake_rate_baby.dr_ele17_CaloIdL_CaloIsoVL_vstar(); }
	const float &dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar() { return fake_rate_baby.dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar(); }
	const float &dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar() { return fake_rate_baby.dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar(); }
	const float &dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar() { return fake_rate_baby.dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar(); }
	const float &dr_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar() { return fake_rate_baby.dr_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar(); }
	const float &dr_ele27_WP80_vstar() { return fake_rate_baby.dr_ele27_WP80_vstar(); }
	const int &hltps_ele8_vstar() { return fake_rate_baby.hltps_ele8_vstar(); }
	const int &hltps_ele8_CaloIdL_TrkIdVL_vstar() { return fake_rate_baby.hltps_ele8_CaloIdL_TrkIdVL_vstar(); }
	const int &hltps_ele8_CaloIdL_CaloIsoVL_Jet40_vstar() { return fake_rate_baby.hltps_ele8_CaloIdL_CaloIsoVL_Jet40_vstar(); }
	const int &hltps_ele8_CaloIdL_CaloIsoVL_vstar() { return fake_rate_baby.hltps_ele8_CaloIdL_CaloIsoVL_vstar(); }
	const int &hltps_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar() { return fake_rate_baby.hltps_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar(); }
	const int &hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar() { return fake_rate_baby.hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar(); }
	const int &hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar() { return fake_rate_baby.hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar(); }
	const int &hltps_ele8_CaloIdT_TrkIdVL_vstar() { return fake_rate_baby.hltps_ele8_CaloIdT_TrkIdVL_vstar(); }
	const int &hltps_ele8_CaloIdT_TrkIdVL_Jet30_vstar() { return fake_rate_baby.hltps_ele8_CaloIdT_TrkIdVL_Jet30_vstar(); }
	const int &hltps_ele17_CaloIdL_CaloIsoVL_vstar() { return fake_rate_baby.hltps_ele17_CaloIdL_CaloIsoVL_vstar(); }
	const int &hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar() { return fake_rate_baby.hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar(); }
	const int &hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar() { return fake_rate_baby.hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar(); }
	const int &hltps_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar() { return fake_rate_baby.hltps_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar(); }
	const int &hltps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar() { return fake_rate_baby.hltps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar(); }
	const int &hltps_ele27_WP80_vstar() { return fake_rate_baby.hltps_ele27_WP80_vstar(); }
	const int &mu3_vstar() { return fake_rate_baby.mu3_vstar(); }
	const int &mu5_vstar() { return fake_rate_baby.mu5_vstar(); }
	const int &mu8_vstar() { return fake_rate_baby.mu8_vstar(); }
	const int &mu12_vstar() { return fake_rate_baby.mu12_vstar(); }
	const int &mu15_vstar() { return fake_rate_baby.mu15_vstar(); }
	const int &mu17_vstar() { return fake_rate_baby.mu17_vstar(); }
	const int &mu20_vstar() { return fake_rate_baby.mu20_vstar(); }
	const int &mu24_vstar() { return fake_rate_baby.mu24_vstar(); }
	const int &mu30_vstar() { return fake_rate_baby.mu30_vstar(); }
	const int &mu15_eta2p1_vstar() { return fake_rate_baby.mu15_eta2p1_vstar(); }
	const int &mu24_eta2p1_vstar() { return fake_rate_baby.mu24_eta2p1_vstar(); }
	const int &mu30_eta2p1_vstar() { return fake_rate_baby.mu30_eta2p1_vstar(); }
	const int &mu8_Jet40_vstar() { return fake_rate_baby.mu8_Jet40_vstar(); }
	const int &isoMu20_eta2p1_vstar() { return fake_rate_baby.isoMu20_eta2p1_vstar(); }
	const int &isoMu24_eta2p1_vstar() { return fake_rate_baby.isoMu24_eta2p1_vstar(); }
	const int &isoMu30_eta2p1_vstar() { return fake_rate_baby.isoMu30_eta2p1_vstar(); }
	const int &relIso1p0Mu17_vstar() { return fake_rate_baby.relIso1p0Mu17_vstar(); }
	const int &relIso1p0Mu20_vstar() { return fake_rate_baby.relIso1p0Mu20_vstar(); }
	const int &relIso1p0Mu5_vstar() { return fake_rate_baby.relIso1p0Mu5_vstar(); }
	const int &mu3_version() { return fake_rate_baby.mu3_version(); }
	const int &mu5_version() { return fake_rate_baby.mu5_version(); }
	const int &mu8_version() { return fake_rate_baby.mu8_version(); }
	const int &mu12_version() { return fake_rate_baby.mu12_version(); }
	const int &mu15_version() { return fake_rate_baby.mu15_version(); }
	const int &mu17_version() { return fake_rate_baby.mu17_version(); }
	const int &mu20_version() { return fake_rate_baby.mu20_version(); }
	const int &mu24_version() { return fake_rate_baby.mu24_version(); }
	const int &mu30_version() { return fake_rate_baby.mu30_version(); }
	const int &mu15_eta2p1_version() { return fake_rate_baby.mu15_eta2p1_version(); }
	const int &mu24_eta2p1_version() { return fake_rate_baby.mu24_eta2p1_version(); }
	const int &mu30_eta2p1_version() { return fake_rate_baby.mu30_eta2p1_version(); }
	const int &mu8_Jet40_version() { return fake_rate_baby.mu8_Jet40_version(); }
	const int &isoMu20_eta2p1_version() { return fake_rate_baby.isoMu20_eta2p1_version(); }
	const int &isoMu24_eta2p1_version() { return fake_rate_baby.isoMu24_eta2p1_version(); }
	const int &isoMu30_eta2p1_version() { return fake_rate_baby.isoMu30_eta2p1_version(); }
	const int &relIso1p0Mu17_version() { return fake_rate_baby.relIso1p0Mu17_version(); }
	const int &relIso1p0Mu20_version() { return fake_rate_baby.relIso1p0Mu20_version(); }
	const int &relIso1p0Mu5_version() { return fake_rate_baby.relIso1p0Mu5_version(); }
	const float &dr_mu3_vstar() { return fake_rate_baby.dr_mu3_vstar(); }
	const float &dr_mu5_vstar() { return fake_rate_baby.dr_mu5_vstar(); }
	const float &dr_mu8_vstar() { return fake_rate_baby.dr_mu8_vstar(); }
	const float &dr_mu12_vstar() { return fake_rate_baby.dr_mu12_vstar(); }
	const float &dr_mu15_vstar() { return fake_rate_baby.dr_mu15_vstar(); }
	const float &dr_mu17_vstar() { return fake_rate_baby.dr_mu17_vstar(); }
	const float &dr_mu20_vstar() { return fake_rate_baby.dr_mu20_vstar(); }
	const float &dr_mu24_vstar() { return fake_rate_baby.dr_mu24_vstar(); }
	const float &dr_mu30_vstar() { return fake_rate_baby.dr_mu30_vstar(); }
	const float &dr_mu15_eta2p1_vstar() { return fake_rate_baby.dr_mu15_eta2p1_vstar(); }
	const float &dr_mu24_eta2p1_vstar() { return fake_rate_baby.dr_mu24_eta2p1_vstar(); }
	const float &dr_mu30_eta2p1_vstar() { return fake_rate_baby.dr_mu30_eta2p1_vstar(); }
	const float &dr_mu8_Jet40_vstar() { return fake_rate_baby.dr_mu8_Jet40_vstar(); }
	const float &dr_isoMu20_eta2p1_vstar() { return fake_rate_baby.dr_isoMu20_eta2p1_vstar(); }
	const float &dr_isoMu24_eta2p1_vstar() { return fake_rate_baby.dr_isoMu24_eta2p1_vstar(); }
	const float &dr_isoMu30_eta2p1_vstar() { return fake_rate_baby.dr_isoMu30_eta2p1_vstar(); }
	const float &dr_relIso1p0Mu17_vstar() { return fake_rate_baby.dr_relIso1p0Mu17_vstar(); }
	const float &dr_relIso1p0Mu20_vstar() { return fake_rate_baby.dr_relIso1p0Mu20_vstar(); }
	const float &dr_relIso1p0Mu5_vstar() { return fake_rate_baby.dr_relIso1p0Mu5_vstar(); }
	const int &hltps_mu3_vstar() { return fake_rate_baby.hltps_mu3_vstar(); }
	const int &hltps_mu5_vstar() { return fake_rate_baby.hltps_mu5_vstar(); }
	const int &hltps_mu8_vstar() { return fake_rate_baby.hltps_mu8_vstar(); }
	const int &hltps_mu12_vstar() { return fake_rate_baby.hltps_mu12_vstar(); }
	const int &hltps_mu15_vstar() { return fake_rate_baby.hltps_mu15_vstar(); }
	const int &hltps_mu17_vstar() { return fake_rate_baby.hltps_mu17_vstar(); }
	const int &hltps_mu20_vstar() { return fake_rate_baby.hltps_mu20_vstar(); }
	const int &hltps_mu24_vstar() { return fake_rate_baby.hltps_mu24_vstar(); }
	const int &hltps_mu30_vstar() { return fake_rate_baby.hltps_mu30_vstar(); }
	const int &hltps_mu15_eta2p1_vstar() { return fake_rate_baby.hltps_mu15_eta2p1_vstar(); }
	const int &hltps_mu24_eta2p1_vstar() { return fake_rate_baby.hltps_mu24_eta2p1_vstar(); }
	const int &hltps_mu30_eta2p1_vstar() { return fake_rate_baby.hltps_mu30_eta2p1_vstar(); }
	const int &hltps_mu8_Jet40_vstar() { return fake_rate_baby.hltps_mu8_Jet40_vstar(); }
	const int &hltps_isoMu20_eta2p1_vstar() { return fake_rate_baby.hltps_isoMu20_eta2p1_vstar(); }
	const int &hltps_isoMu24_eta2p1_vstar() { return fake_rate_baby.hltps_isoMu24_eta2p1_vstar(); }
	const int &hltps_isoMu30_eta2p1_vstar() { return fake_rate_baby.hltps_isoMu30_eta2p1_vstar(); }
	const int &hltps_relIso1p0Mu17_vstar() { return fake_rate_baby.hltps_relIso1p0Mu17_vstar(); }
	const int &hltps_relIso1p0Mu20_vstar() { return fake_rate_baby.hltps_relIso1p0Mu20_vstar(); }
	const int &hltps_relIso1p0Mu5_vstar() { return fake_rate_baby.hltps_relIso1p0Mu5_vstar(); }
	const float &ptpfj1() { return fake_rate_baby.ptpfj1(); }
	const int &npfj1() { return fake_rate_baby.npfj1(); }
	const float &csvpfj1() { return fake_rate_baby.csvpfj1(); }
	const float &ptpfj1_b2b() { return fake_rate_baby.ptpfj1_b2b(); }
	const float &dphipfj1_b2b() { return fake_rate_baby.dphipfj1_b2b(); }
	const float &ptpfcj1() { return fake_rate_baby.ptpfcj1(); }
	const int &npfcj1() { return fake_rate_baby.npfcj1(); }
	const float &ptpfcj1_b2b() { return fake_rate_baby.ptpfcj1_b2b(); }
	const float &dphipfcj1_b2b() { return fake_rate_baby.dphipfcj1_b2b(); }
	const bool &btagpfc() { return fake_rate_baby.btagpfc(); }
	const float &emfpfcL1Fj1() { return fake_rate_baby.emfpfcL1Fj1(); }
	const float &ptpfcL1Fj1() { return fake_rate_baby.ptpfcL1Fj1(); }
	const float &dphipfcL1Fj1() { return fake_rate_baby.dphipfcL1Fj1(); }
	const int &npfcL1Fj1() { return fake_rate_baby.npfcL1Fj1(); }
	const int &npfc30L1Fj1() { return fake_rate_baby.npfc30L1Fj1(); }
	const int &npfc40L1Fj1() { return fake_rate_baby.npfc40L1Fj1(); }
	const int &nbpfc40L1Fj1() { return fake_rate_baby.nbpfc40L1Fj1(); }
	const float &ptpfcL1Fj1_b2b() { return fake_rate_baby.ptpfcL1Fj1_b2b(); }
	const float &dphipfcL1Fj1_b2b() { return fake_rate_baby.dphipfcL1Fj1_b2b(); }
	const bool &btagpfcL1F() { return fake_rate_baby.btagpfcL1F(); }
	const int &npfc50L1Fj1_eth() { return fake_rate_baby.npfc50L1Fj1_eth(); }
	const int &npfc65L1Fj1_eth() { return fake_rate_baby.npfc65L1Fj1_eth(); }
	const float &emfpfcL1Fj1res() { return fake_rate_baby.emfpfcL1Fj1res(); }
	const float &ptpfcL1Fj1res() { return fake_rate_baby.ptpfcL1Fj1res(); }
	const float &dphipfcL1Fj1res() { return fake_rate_baby.dphipfcL1Fj1res(); }
	const int &npfcL1Fj1res() { return fake_rate_baby.npfcL1Fj1res(); }
	const int &npfc30L1Fj1res() { return fake_rate_baby.npfc30L1Fj1res(); }
	const int &npfc40L1Fj1res() { return fake_rate_baby.npfc40L1Fj1res(); }
	const int &nbpfc40L1Fj1res() { return fake_rate_baby.nbpfc40L1Fj1res(); }
	const float &ptpfcL1Fj1res_b2b() { return fake_rate_baby.ptpfcL1Fj1res_b2b(); }
	const float &dphipfcL1Fj1res_b2b() { return fake_rate_baby.dphipfcL1Fj1res_b2b(); }
	const bool &btagpfcL1Fres() { return fake_rate_baby.btagpfcL1Fres(); }
	const int &npfc50L1Fj1res_eth() { return fake_rate_baby.npfc50L1Fj1res_eth(); }
	const int &npfc65L1Fj1res_eth() { return fake_rate_baby.npfc65L1Fj1res_eth(); }
	const float &ptbtagpfcL1Fj1() { return fake_rate_baby.ptbtagpfcL1Fj1(); }
	const float &dphibtagpfcL1Fj1() { return fake_rate_baby.dphibtagpfcL1Fj1(); }
	const float &ptbtagpfcL1Fj1res() { return fake_rate_baby.ptbtagpfcL1Fj1res(); }
	const float &dphibtagpfcL1Fj1res() { return fake_rate_baby.dphibtagpfcL1Fj1res(); }
	const int &nbpfcjet() { return fake_rate_baby.nbpfcjet(); }
	const float &dRpfcNear() { return fake_rate_baby.dRpfcNear(); }
	const float &dRpfcFar() { return fake_rate_baby.dRpfcFar(); }
	const float &rho() { return fake_rate_baby.rho(); }
}
