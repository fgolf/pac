#include "SSB2012.h"
SSB2012 samesignbtag;
namespace ssb {
	unsigned int &run() { return samesignbtag.run(); }
	unsigned int &ls() { return samesignbtag.ls(); }
	unsigned int &evt() { return samesignbtag.evt(); }
	bool &is_real_data() { return samesignbtag.is_real_data(); }
	int &sample() { return samesignbtag.sample(); }
	int &nvtxs() { return samesignbtag.nvtxs(); }
	int &vtx_idx() { return samesignbtag.vtx_idx(); }
	float &pfmet() { return samesignbtag.pfmet(); }
	float &pfmet_phi() { return samesignbtag.pfmet_phi(); }
	float &uncorpfmet() { return samesignbtag.uncorpfmet(); }
	float &uncorpfmet_phi() { return samesignbtag.uncorpfmet_phi(); }
	float &scale1fb() { return samesignbtag.scale1fb(); }
	float &xsec() { return samesignbtag.xsec(); }
	float &kfactor() { return samesignbtag.kfactor(); }
	float &gen_met() { return samesignbtag.gen_met(); }
	float &gen_met_phi() { return samesignbtag.gen_met_phi(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_p4() { return samesignbtag.lep1_p4(); }
	bool &lep1_passes_id() { return samesignbtag.lep1_passes_id(); }
	bool &lep1_passes_iso() { return samesignbtag.lep1_passes_iso(); }
	bool &lep1_is_num() { return samesignbtag.lep1_is_num(); }
	bool &lep1_is_fo() { return samesignbtag.lep1_is_fo(); }
	int &lep1_charge() { return samesignbtag.lep1_charge(); }
	int &lep1_pdgid() { return samesignbtag.lep1_pdgid(); }
	int &lep1_type() { return samesignbtag.lep1_type(); }
	float &lep1_d0() { return samesignbtag.lep1_d0(); }
	float &lep1_dz() { return samesignbtag.lep1_dz(); }
	float &lep1_mt() { return samesignbtag.lep1_mt(); }
	float &lep1_corpfiso() { return samesignbtag.lep1_corpfiso(); }
	float &lep1_pfiso() { return samesignbtag.lep1_pfiso(); }
	float &lep1_chiso() { return samesignbtag.lep1_chiso(); }
	float &lep1_emiso() { return samesignbtag.lep1_emiso(); }
	float &lep1_nhiso() { return samesignbtag.lep1_nhiso(); }
	float &lep1_corpfiso04() { return samesignbtag.lep1_corpfiso04(); }
	float &lep1_pfiso04() { return samesignbtag.lep1_pfiso04(); }
	float &lep1_chiso04() { return samesignbtag.lep1_chiso04(); }
	float &lep1_emiso04() { return samesignbtag.lep1_emiso04(); }
	float &lep1_nhiso04() { return samesignbtag.lep1_nhiso04(); }
	float &lep1_cordetiso() { return samesignbtag.lep1_cordetiso(); }
	float &lep1_detiso() { return samesignbtag.lep1_detiso(); }
	float &lep1_trkiso() { return samesignbtag.lep1_trkiso(); }
	float &lep1_ecaliso() { return samesignbtag.lep1_ecaliso(); }
	float &lep1_hcaliso() { return samesignbtag.lep1_hcaliso(); }
	float &lep1_cordetiso04() { return samesignbtag.lep1_cordetiso04(); }
	float &lep1_detiso04() { return samesignbtag.lep1_detiso04(); }
	float &lep1_trkiso04() { return samesignbtag.lep1_trkiso04(); }
	float &lep1_ecaliso04() { return samesignbtag.lep1_ecaliso04(); }
	float &lep1_hcaliso04() { return samesignbtag.lep1_hcaliso04(); }
	float &lep1_effarea() { return samesignbtag.lep1_effarea(); }
	float &lep1_effarea04() { return samesignbtag.lep1_effarea04(); }
	float &lep1_dbeta() { return samesignbtag.lep1_dbeta(); }
	float &lep1_dbeta04() { return samesignbtag.lep1_dbeta04(); }
	float &lep1_sf_lepeff() { return samesignbtag.lep1_sf_lepeff(); }
	float &lep1_sf_trig() { return samesignbtag.lep1_sf_trig(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mcp4() { return samesignbtag.lep1_mcp4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mc3p4() { return samesignbtag.lep1_mc3p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mc_momp4() { return samesignbtag.lep1_mc_momp4(); }
	int &lep1_mcid() { return samesignbtag.lep1_mcid(); }
	int &lep1_mc3id() { return samesignbtag.lep1_mc3id(); }
	int &lep1_momid() { return samesignbtag.lep1_momid(); }
	int &lep1_mc3_momid() { return samesignbtag.lep1_mc3_momid(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_gsf_p4() { return samesignbtag.lep1_gsf_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_ctf_p4() { return samesignbtag.lep1_ctf_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_sc_p4() { return samesignbtag.lep1_sc_p4(); }
	bool &lep1_q3agree() { return samesignbtag.lep1_q3agree(); }
	bool &lep1_is_conv() { return samesignbtag.lep1_is_conv(); }
	int &lep1_qsc() { return samesignbtag.lep1_qsc(); }
	int &lep1_qctf() { return samesignbtag.lep1_qctf(); }
	int &lep1_qgsf() { return samesignbtag.lep1_qgsf(); }
	int &lep1_nmhits() { return samesignbtag.lep1_nmhits(); }
	int &lep1_eleid_veto() { return samesignbtag.lep1_eleid_veto(); }
	int &lep1_eleid_loose() { return samesignbtag.lep1_eleid_loose(); }
	int &lep1_eleid_medium() { return samesignbtag.lep1_eleid_medium(); }
	int &lep1_eleid_tight() { return samesignbtag.lep1_eleid_tight(); }
	float &lep1_dphiin() { return samesignbtag.lep1_dphiin(); }
	float &lep1_detain() { return samesignbtag.lep1_detain(); }
	float &lep1_sieie() { return samesignbtag.lep1_sieie(); }
	float &lep1_hoe() { return samesignbtag.lep1_hoe(); }
	float &lep1_ooemoop() { return samesignbtag.lep1_ooemoop(); }
	float &lep1_conv_dist() { return samesignbtag.lep1_conv_dist(); }
	float &lep1_conv_dcot() { return samesignbtag.lep1_conv_dcot(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_gfit_p4() { return samesignbtag.lep1_gfit_p4(); }
	bool &lep1_is_global() { return samesignbtag.lep1_is_global(); }
	bool &lep1_is_tracker() { return samesignbtag.lep1_is_tracker(); }
	bool &lep1_is_stamu() { return samesignbtag.lep1_is_stamu(); }
	bool &lep1_is_pfmu() { return samesignbtag.lep1_is_pfmu(); }
	bool &lep1_is_loosemu() { return samesignbtag.lep1_is_loosemu(); }
	bool &lep1_is_tightmu() { return samesignbtag.lep1_is_tightmu(); }
	int &lep1_npixelhits() { return samesignbtag.lep1_npixelhits(); }
	int &lep1_nsihits() { return samesignbtag.lep1_nsihits(); }
	int &lep1_nsilayers() { return samesignbtag.lep1_nsilayers(); }
	int &lep1_nstahits() { return samesignbtag.lep1_nstahits(); }
	int &lep1_nstations() { return samesignbtag.lep1_nstations(); }
	float &lep1_chi2() { return samesignbtag.lep1_chi2(); }
	float &lep1_ndof() { return samesignbtag.lep1_ndof(); }
	float &lep1_pterr() { return samesignbtag.lep1_pterr(); }
	float &lep1_ecal_vetodep() { return samesignbtag.lep1_ecal_vetodep(); }
	float &lep1_hcal_vetodep() { return samesignbtag.lep1_hcal_vetodep(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_p4() { return samesignbtag.lep2_p4(); }
	bool &lep2_passes_id() { return samesignbtag.lep2_passes_id(); }
	bool &lep2_passes_iso() { return samesignbtag.lep2_passes_iso(); }
	bool &lep2_is_num() { return samesignbtag.lep2_is_num(); }
	bool &lep2_is_fo() { return samesignbtag.lep2_is_fo(); }
	int &lep2_charge() { return samesignbtag.lep2_charge(); }
	int &lep2_pdgid() { return samesignbtag.lep2_pdgid(); }
	int &lep2_type() { return samesignbtag.lep2_type(); }
	float &lep2_d0() { return samesignbtag.lep2_d0(); }
	float &lep2_dz() { return samesignbtag.lep2_dz(); }
	float &lep2_mt() { return samesignbtag.lep2_mt(); }
	float &lep2_corpfiso() { return samesignbtag.lep2_corpfiso(); }
	float &lep2_pfiso() { return samesignbtag.lep2_pfiso(); }
	float &lep2_chiso() { return samesignbtag.lep2_chiso(); }
	float &lep2_emiso() { return samesignbtag.lep2_emiso(); }
	float &lep2_nhiso() { return samesignbtag.lep2_nhiso(); }
	float &lep2_corpfiso04() { return samesignbtag.lep2_corpfiso04(); }
	float &lep2_pfiso04() { return samesignbtag.lep2_pfiso04(); }
	float &lep2_chiso04() { return samesignbtag.lep2_chiso04(); }
	float &lep2_emiso04() { return samesignbtag.lep2_emiso04(); }
	float &lep2_nhiso04() { return samesignbtag.lep2_nhiso04(); }
	float &lep2_cordetiso() { return samesignbtag.lep2_cordetiso(); }
	float &lep2_detiso() { return samesignbtag.lep2_detiso(); }
	float &lep2_trkiso() { return samesignbtag.lep2_trkiso(); }
	float &lep2_ecaliso() { return samesignbtag.lep2_ecaliso(); }
	float &lep2_hcaliso() { return samesignbtag.lep2_hcaliso(); }
	float &lep2_cordetiso04() { return samesignbtag.lep2_cordetiso04(); }
	float &lep2_detiso04() { return samesignbtag.lep2_detiso04(); }
	float &lep2_trkiso04() { return samesignbtag.lep2_trkiso04(); }
	float &lep2_ecaliso04() { return samesignbtag.lep2_ecaliso04(); }
	float &lep2_hcaliso04() { return samesignbtag.lep2_hcaliso04(); }
	float &lep2_effarea() { return samesignbtag.lep2_effarea(); }
	float &lep2_effarea04() { return samesignbtag.lep2_effarea04(); }
	float &lep2_dbeta() { return samesignbtag.lep2_dbeta(); }
	float &lep2_dbeta04() { return samesignbtag.lep2_dbeta04(); }
	float &lep2_sf_lepeff() { return samesignbtag.lep2_sf_lepeff(); }
	float &lep2_sf_trig() { return samesignbtag.lep2_sf_trig(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mcp4() { return samesignbtag.lep2_mcp4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mc3p4() { return samesignbtag.lep2_mc3p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mc_momp4() { return samesignbtag.lep2_mc_momp4(); }
	int &lep2_mcid() { return samesignbtag.lep2_mcid(); }
	int &lep2_mc3id() { return samesignbtag.lep2_mc3id(); }
	int &lep2_momid() { return samesignbtag.lep2_momid(); }
	int &lep2_mc3_momid() { return samesignbtag.lep2_mc3_momid(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_gsf_p4() { return samesignbtag.lep2_gsf_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_ctf_p4() { return samesignbtag.lep2_ctf_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_sc_p4() { return samesignbtag.lep2_sc_p4(); }
	bool &lep2_q3agree() { return samesignbtag.lep2_q3agree(); }
	bool &lep2_is_conv() { return samesignbtag.lep2_is_conv(); }
	int &lep2_qsc() { return samesignbtag.lep2_qsc(); }
	int &lep2_qctf() { return samesignbtag.lep2_qctf(); }
	int &lep2_qgsf() { return samesignbtag.lep2_qgsf(); }
	int &lep2_nmhits() { return samesignbtag.lep2_nmhits(); }
	int &lep2_eleid_veto() { return samesignbtag.lep2_eleid_veto(); }
	int &lep2_eleid_loose() { return samesignbtag.lep2_eleid_loose(); }
	int &lep2_eleid_medium() { return samesignbtag.lep2_eleid_medium(); }
	int &lep2_eleid_tight() { return samesignbtag.lep2_eleid_tight(); }
	float &lep2_dphiin() { return samesignbtag.lep2_dphiin(); }
	float &lep2_detain() { return samesignbtag.lep2_detain(); }
	float &lep2_sieie() { return samesignbtag.lep2_sieie(); }
	float &lep2_hoe() { return samesignbtag.lep2_hoe(); }
	float &lep2_ooemoop() { return samesignbtag.lep2_ooemoop(); }
	float &lep2_conv_dist() { return samesignbtag.lep2_conv_dist(); }
	float &lep2_conv_dcot() { return samesignbtag.lep2_conv_dcot(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_gfit_p4() { return samesignbtag.lep2_gfit_p4(); }
	bool &lep2_is_global() { return samesignbtag.lep2_is_global(); }
	bool &lep2_is_tracker() { return samesignbtag.lep2_is_tracker(); }
	bool &lep2_is_stamu() { return samesignbtag.lep2_is_stamu(); }
	bool &lep2_is_pfmu() { return samesignbtag.lep2_is_pfmu(); }
	bool &lep2_is_loosemu() { return samesignbtag.lep2_is_loosemu(); }
	bool &lep2_is_tightmu() { return samesignbtag.lep2_is_tightmu(); }
	int &lep2_npixelhits() { return samesignbtag.lep2_npixelhits(); }
	int &lep2_nsihits() { return samesignbtag.lep2_nsihits(); }
	int &lep2_nsilayers() { return samesignbtag.lep2_nsilayers(); }
	int &lep2_nstahits() { return samesignbtag.lep2_nstahits(); }
	int &lep2_nstations() { return samesignbtag.lep2_nstations(); }
	float &lep2_chi2() { return samesignbtag.lep2_chi2(); }
	float &lep2_ndof() { return samesignbtag.lep2_ndof(); }
	float &lep2_pterr() { return samesignbtag.lep2_pterr(); }
	float &lep2_ecal_vetodep() { return samesignbtag.lep2_ecal_vetodep(); }
	float &lep2_hcal_vetodep() { return samesignbtag.lep2_hcal_vetodep(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &dilep_p4() { return samesignbtag.dilep_p4(); }
	bool &is_os() { return samesignbtag.is_os(); }
	bool &is_ss() { return samesignbtag.is_ss(); }
	int &dilep_type() { return samesignbtag.dilep_type(); }
	int &dilep_gen_type() { return samesignbtag.dilep_gen_type(); }
	float &dilep_mass() { return samesignbtag.dilep_mass(); }
	float &dilep_dphi() { return samesignbtag.dilep_dphi(); }
	float &dilep_deta() { return samesignbtag.dilep_deta(); }
	float &dilep_dr() { return samesignbtag.dilep_dr(); }
	int &fiduciality() { return samesignbtag.fiduciality(); }
	unsigned int &selection() { return samesignbtag.selection(); }
	bool &is_good_lumi() { return samesignbtag.is_good_lumi(); }
	int &njets() { return samesignbtag.njets(); }
	int &njets20() { return samesignbtag.njets20(); }
	int &njets30() { return samesignbtag.njets30(); }
	int &nbtags() { return samesignbtag.nbtags(); }
	int &nbtags20() { return samesignbtag.nbtags20(); }
	int &nbtags30() { return samesignbtag.nbtags30(); }
	float &vtxw() { return samesignbtag.vtxw(); }
	float &mt() { return samesignbtag.mt(); }
	float &ht() { return samesignbtag.ht(); }
	float &ht20() { return samesignbtag.ht20(); }
	float &ht30() { return samesignbtag.ht30(); }
	float &rho() { return samesignbtag.rho(); }
	float &rho_iso() { return samesignbtag.rho_iso(); }
	bool &trig_mm() { return samesignbtag.trig_mm(); }
	bool &trig_em() { return samesignbtag.trig_em(); }
	bool &trig_ee() { return samesignbtag.trig_ee(); }
	int &njets_dn() { return samesignbtag.njets_dn(); }
	int &njets_up() { return samesignbtag.njets_up(); }
	int &nbtags_dn() { return samesignbtag.nbtags_dn(); }
	int &nbtags_up() { return samesignbtag.nbtags_up(); }
	float &ht_dn() { return samesignbtag.ht_dn(); }
	float &ht_up() { return samesignbtag.ht_up(); }
	int &njets20_dn() { return samesignbtag.njets20_dn(); }
	int &njets20_up() { return samesignbtag.njets20_up(); }
	int &nbtags20_dn() { return samesignbtag.nbtags20_dn(); }
	int &nbtags20_up() { return samesignbtag.nbtags20_up(); }
	float &ht20_dn() { return samesignbtag.ht20_dn(); }
	float &ht20_up() { return samesignbtag.ht20_up(); }
	int &njets30_dn() { return samesignbtag.njets30_dn(); }
	int &njets30_up() { return samesignbtag.njets30_up(); }
	int &nbtags30_dn() { return samesignbtag.nbtags30_dn(); }
	int &nbtags30_up() { return samesignbtag.nbtags30_up(); }
	float &ht30_dn() { return samesignbtag.ht30_dn(); }
	float &ht30_up() { return samesignbtag.ht30_up(); }
	float &pfmet_dn() { return samesignbtag.pfmet_dn(); }
	float &pfmet_up() { return samesignbtag.pfmet_up(); }
	float &pfmet_phi_dn() { return samesignbtag.pfmet_phi_dn(); }
	float &pfmet_phi_up() { return samesignbtag.pfmet_phi_up(); }
	float &sf_dileptrig() { return samesignbtag.sf_dileptrig(); }
	float &sf_lepeff() { return samesignbtag.sf_lepeff(); }
	float &sparm0() { return samesignbtag.sparm0(); }
	float &sparm1() { return samesignbtag.sparm1(); }
	float &sparm2() { return samesignbtag.sparm2(); }
	float &sparm3() { return samesignbtag.sparm3(); }
	bool &is_pp() { return samesignbtag.is_pp(); }
	bool &is_mm() { return samesignbtag.is_mm(); }
	bool &is_sf() { return samesignbtag.is_sf(); }
	bool &is_df() { return samesignbtag.is_df(); }
	bool &no_extraz() { return samesignbtag.no_extraz(); }
	bool &is_gen_pp() { return samesignbtag.is_gen_pp(); }
	bool &is_gen_mm() { return samesignbtag.is_gen_mm(); }
	int &gen_nbtags() { return samesignbtag.gen_nbtags(); }
	int &gen_njets() { return samesignbtag.gen_njets(); }
	float &gen_ht() { return samesignbtag.gen_ht(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearbjet_p4() { return samesignbtag.lep1_nearbjet_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearjet_p4() { return samesignbtag.lep1_nearjet_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearlep_p4() { return samesignbtag.lep1_nearlep_p4(); }
	float &lep1_wfr() { return samesignbtag.lep1_wfr(); }
	float &lep1_wflip() { return samesignbtag.lep1_wflip(); }
	float &lep1_nearbjet_dr() { return samesignbtag.lep1_nearbjet_dr(); }
	float &lep1_nearjet_dr() { return samesignbtag.lep1_nearjet_dr(); }
	float &lep1_nearlep_dr() { return samesignbtag.lep1_nearlep_dr(); }
	int &lep1_nearlep_id() { return samesignbtag.lep1_nearlep_id(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearbjet_p4() { return samesignbtag.lep2_nearbjet_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearjet_p4() { return samesignbtag.lep2_nearjet_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearlep_p4() { return samesignbtag.lep2_nearlep_p4(); }
	float &lep2_wfr() { return samesignbtag.lep2_wfr(); }
	float &lep2_wflip() { return samesignbtag.lep2_wflip(); }
	float &lep2_nearbjet_dr() { return samesignbtag.lep2_nearbjet_dr(); }
	float &lep2_nearjet_dr() { return samesignbtag.lep2_nearjet_dr(); }
	float &lep2_nearlep_dr() { return samesignbtag.lep2_nearlep_dr(); }
	int &lep2_nearlep_id() { return samesignbtag.lep2_nearlep_id(); }
	float &sf_nbtag() { return samesignbtag.sf_nbtag(); }
	float &sf_nbtag3() { return samesignbtag.sf_nbtag3(); }
	float &sf_unc_nbtag() { return samesignbtag.sf_unc_nbtag(); }
	float &sf_unc_nbtag3() { return samesignbtag.sf_unc_nbtag3(); }
	float &jets_dr12() { return samesignbtag.jets_dr12(); }
	float &bjets_dr12() { return samesignbtag.bjets_dr12(); }
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vgenb_p4() { return samesignbtag.vgenb_p4(); }
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_p4() { return samesignbtag.vjets_p4(); }
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vgenjets_p4() { return samesignbtag.vgenjets_p4(); }
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_nearjet_p4() { return samesignbtag.vjets_nearjet_p4(); }
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vbjets_p4() { return samesignbtag.vbjets_p4(); }
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vbjets_nearjet_p4() { return samesignbtag.vbjets_nearjet_p4(); }
	vector<bool> &vbtags() { return samesignbtag.vbtags(); }
	vector<float> &vbjets_nearjet_dr() { return samesignbtag.vbjets_nearjet_dr(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep1_p4() { return samesignbtag.gen_lep1_p4(); }
	int &gen_lep1_pdgid() { return samesignbtag.gen_lep1_pdgid(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep2_p4() { return samesignbtag.gen_lep2_p4(); }
	int &gen_lep2_pdgid() { return samesignbtag.gen_lep2_pdgid(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_dilep_p4() { return samesignbtag.gen_dilep_p4(); }
	int &gen_dilep_type() { return samesignbtag.gen_dilep_type(); }
	float &gen_dilep_mass() { return samesignbtag.gen_dilep_mass(); }
	float &gen_dilep_dphi() { return samesignbtag.gen_dilep_dphi(); }
	float &gen_dilep_deta() { return samesignbtag.gen_dilep_deta(); }
	float &gen_dilep_dr() { return samesignbtag.gen_dilep_dr(); }
}
