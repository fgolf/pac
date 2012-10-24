#include "TRILEPZ2012.h"
TRILEPZ2012 ttz3l;
namespace trilepz {
	unsigned int &run() { return ttz3l.run(); }
	unsigned int &ls() { return ttz3l.ls(); }
	unsigned int &evt() { return ttz3l.evt(); }
	bool &is_real_data() { return ttz3l.is_real_data(); }
	int &sample() { return ttz3l.sample(); }
	int &nvtxs() { return ttz3l.nvtxs(); }
	int &vtx_idx() { return ttz3l.vtx_idx(); }
	float &pfmet() { return ttz3l.pfmet(); }
	float &pfmet_phi() { return ttz3l.pfmet_phi(); }
	float &uncorpfmet() { return ttz3l.uncorpfmet(); }
	float &uncorpfmet_phi() { return ttz3l.uncorpfmet_phi(); }
	float &scale1fb() { return ttz3l.scale1fb(); }
	float &xsec() { return ttz3l.xsec(); }
	float &kfactor() { return ttz3l.kfactor(); }
	float &gen_met() { return ttz3l.gen_met(); }
	float &gen_met_phi() { return ttz3l.gen_met_phi(); }
	TString &dataset() { return ttz3l.dataset(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_p4() { return ttz3l.lep1_p4(); }
	bool &lep1_passes_id() { return ttz3l.lep1_passes_id(); }
	bool &lep1_passes_iso() { return ttz3l.lep1_passes_iso(); }
	bool &lep1_is_num() { return ttz3l.lep1_is_num(); }
	bool &lep1_is_fo() { return ttz3l.lep1_is_fo(); }
	int &lep1_is_fromw() { return ttz3l.lep1_is_fromw(); }
	int &lep1_charge() { return ttz3l.lep1_charge(); }
	int &lep1_pdgid() { return ttz3l.lep1_pdgid(); }
	int &lep1_type() { return ttz3l.lep1_type(); }
	float &lep1_d0() { return ttz3l.lep1_d0(); }
	float &lep1_dz() { return ttz3l.lep1_dz(); }
	float &lep1_mt() { return ttz3l.lep1_mt(); }
	float &lep1_corpfiso() { return ttz3l.lep1_corpfiso(); }
	float &lep1_pfiso() { return ttz3l.lep1_pfiso(); }
	float &lep1_chiso() { return ttz3l.lep1_chiso(); }
	float &lep1_emiso() { return ttz3l.lep1_emiso(); }
	float &lep1_nhiso() { return ttz3l.lep1_nhiso(); }
	float &lep1_corpfiso04() { return ttz3l.lep1_corpfiso04(); }
	float &lep1_pfiso04() { return ttz3l.lep1_pfiso04(); }
	float &lep1_chiso04() { return ttz3l.lep1_chiso04(); }
	float &lep1_emiso04() { return ttz3l.lep1_emiso04(); }
	float &lep1_nhiso04() { return ttz3l.lep1_nhiso04(); }
	float &lep1_cordetiso() { return ttz3l.lep1_cordetiso(); }
	float &lep1_detiso() { return ttz3l.lep1_detiso(); }
	float &lep1_trkiso() { return ttz3l.lep1_trkiso(); }
	float &lep1_ecaliso() { return ttz3l.lep1_ecaliso(); }
	float &lep1_hcaliso() { return ttz3l.lep1_hcaliso(); }
	float &lep1_cordetiso04() { return ttz3l.lep1_cordetiso04(); }
	float &lep1_detiso04() { return ttz3l.lep1_detiso04(); }
	float &lep1_trkiso04() { return ttz3l.lep1_trkiso04(); }
	float &lep1_ecaliso04() { return ttz3l.lep1_ecaliso04(); }
	float &lep1_hcaliso04() { return ttz3l.lep1_hcaliso04(); }
	float &lep1_effarea() { return ttz3l.lep1_effarea(); }
	float &lep1_effarea04() { return ttz3l.lep1_effarea04(); }
	float &lep1_dbeta() { return ttz3l.lep1_dbeta(); }
	float &lep1_dbeta04() { return ttz3l.lep1_dbeta04(); }
	float &lep1_sf_lepeff() { return ttz3l.lep1_sf_lepeff(); }
	float &lep1_sf_trig() { return ttz3l.lep1_sf_trig(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mcp4() { return ttz3l.lep1_mcp4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mc3p4() { return ttz3l.lep1_mc3p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mc_momp4() { return ttz3l.lep1_mc_momp4(); }
	int &lep1_mcid() { return ttz3l.lep1_mcid(); }
	int &lep1_mc3id() { return ttz3l.lep1_mc3id(); }
	int &lep1_momid() { return ttz3l.lep1_momid(); }
	int &lep1_mc3_momid() { return ttz3l.lep1_mc3_momid(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_gsf_p4() { return ttz3l.lep1_gsf_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_ctf_p4() { return ttz3l.lep1_ctf_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_sc_p4() { return ttz3l.lep1_sc_p4(); }
	bool &lep1_q3agree() { return ttz3l.lep1_q3agree(); }
	bool &lep1_is_conv() { return ttz3l.lep1_is_conv(); }
	int &lep1_qsc() { return ttz3l.lep1_qsc(); }
	int &lep1_qctf() { return ttz3l.lep1_qctf(); }
	int &lep1_qgsf() { return ttz3l.lep1_qgsf(); }
	int &lep1_nmhits() { return ttz3l.lep1_nmhits(); }
	int &lep1_eleid_veto() { return ttz3l.lep1_eleid_veto(); }
	int &lep1_eleid_loose() { return ttz3l.lep1_eleid_loose(); }
	int &lep1_eleid_medium() { return ttz3l.lep1_eleid_medium(); }
	int &lep1_eleid_tight() { return ttz3l.lep1_eleid_tight(); }
	float &lep1_dphiin() { return ttz3l.lep1_dphiin(); }
	float &lep1_detain() { return ttz3l.lep1_detain(); }
	float &lep1_sieie() { return ttz3l.lep1_sieie(); }
	float &lep1_hoe() { return ttz3l.lep1_hoe(); }
	float &lep1_ooemoop() { return ttz3l.lep1_ooemoop(); }
	float &lep1_conv_dist() { return ttz3l.lep1_conv_dist(); }
	float &lep1_conv_dcot() { return ttz3l.lep1_conv_dcot(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_gfit_p4() { return ttz3l.lep1_gfit_p4(); }
	bool &lep1_is_global() { return ttz3l.lep1_is_global(); }
	bool &lep1_is_tracker() { return ttz3l.lep1_is_tracker(); }
	bool &lep1_is_stamu() { return ttz3l.lep1_is_stamu(); }
	bool &lep1_is_pfmu() { return ttz3l.lep1_is_pfmu(); }
	bool &lep1_is_loosemu() { return ttz3l.lep1_is_loosemu(); }
	bool &lep1_is_tightmu() { return ttz3l.lep1_is_tightmu(); }
	int &lep1_npixelhits() { return ttz3l.lep1_npixelhits(); }
	int &lep1_nsihits() { return ttz3l.lep1_nsihits(); }
	int &lep1_nsilayers() { return ttz3l.lep1_nsilayers(); }
	int &lep1_nstahits() { return ttz3l.lep1_nstahits(); }
	int &lep1_nstations() { return ttz3l.lep1_nstations(); }
	float &lep1_chi2() { return ttz3l.lep1_chi2(); }
	float &lep1_ndof() { return ttz3l.lep1_ndof(); }
	float &lep1_pterr() { return ttz3l.lep1_pterr(); }
	float &lep1_ecal_vetodep() { return ttz3l.lep1_ecal_vetodep(); }
	float &lep1_hcal_vetodep() { return ttz3l.lep1_hcal_vetodep(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_p4() { return ttz3l.lep2_p4(); }
	bool &lep2_passes_id() { return ttz3l.lep2_passes_id(); }
	bool &lep2_passes_iso() { return ttz3l.lep2_passes_iso(); }
	bool &lep2_is_num() { return ttz3l.lep2_is_num(); }
	bool &lep2_is_fo() { return ttz3l.lep2_is_fo(); }
	int &lep2_is_fromw() { return ttz3l.lep2_is_fromw(); }
	int &lep2_charge() { return ttz3l.lep2_charge(); }
	int &lep2_pdgid() { return ttz3l.lep2_pdgid(); }
	int &lep2_type() { return ttz3l.lep2_type(); }
	float &lep2_d0() { return ttz3l.lep2_d0(); }
	float &lep2_dz() { return ttz3l.lep2_dz(); }
	float &lep2_mt() { return ttz3l.lep2_mt(); }
	float &lep2_corpfiso() { return ttz3l.lep2_corpfiso(); }
	float &lep2_pfiso() { return ttz3l.lep2_pfiso(); }
	float &lep2_chiso() { return ttz3l.lep2_chiso(); }
	float &lep2_emiso() { return ttz3l.lep2_emiso(); }
	float &lep2_nhiso() { return ttz3l.lep2_nhiso(); }
	float &lep2_corpfiso04() { return ttz3l.lep2_corpfiso04(); }
	float &lep2_pfiso04() { return ttz3l.lep2_pfiso04(); }
	float &lep2_chiso04() { return ttz3l.lep2_chiso04(); }
	float &lep2_emiso04() { return ttz3l.lep2_emiso04(); }
	float &lep2_nhiso04() { return ttz3l.lep2_nhiso04(); }
	float &lep2_cordetiso() { return ttz3l.lep2_cordetiso(); }
	float &lep2_detiso() { return ttz3l.lep2_detiso(); }
	float &lep2_trkiso() { return ttz3l.lep2_trkiso(); }
	float &lep2_ecaliso() { return ttz3l.lep2_ecaliso(); }
	float &lep2_hcaliso() { return ttz3l.lep2_hcaliso(); }
	float &lep2_cordetiso04() { return ttz3l.lep2_cordetiso04(); }
	float &lep2_detiso04() { return ttz3l.lep2_detiso04(); }
	float &lep2_trkiso04() { return ttz3l.lep2_trkiso04(); }
	float &lep2_ecaliso04() { return ttz3l.lep2_ecaliso04(); }
	float &lep2_hcaliso04() { return ttz3l.lep2_hcaliso04(); }
	float &lep2_effarea() { return ttz3l.lep2_effarea(); }
	float &lep2_effarea04() { return ttz3l.lep2_effarea04(); }
	float &lep2_dbeta() { return ttz3l.lep2_dbeta(); }
	float &lep2_dbeta04() { return ttz3l.lep2_dbeta04(); }
	float &lep2_sf_lepeff() { return ttz3l.lep2_sf_lepeff(); }
	float &lep2_sf_trig() { return ttz3l.lep2_sf_trig(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mcp4() { return ttz3l.lep2_mcp4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mc3p4() { return ttz3l.lep2_mc3p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mc_momp4() { return ttz3l.lep2_mc_momp4(); }
	int &lep2_mcid() { return ttz3l.lep2_mcid(); }
	int &lep2_mc3id() { return ttz3l.lep2_mc3id(); }
	int &lep2_momid() { return ttz3l.lep2_momid(); }
	int &lep2_mc3_momid() { return ttz3l.lep2_mc3_momid(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_gsf_p4() { return ttz3l.lep2_gsf_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_ctf_p4() { return ttz3l.lep2_ctf_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_sc_p4() { return ttz3l.lep2_sc_p4(); }
	bool &lep2_q3agree() { return ttz3l.lep2_q3agree(); }
	bool &lep2_is_conv() { return ttz3l.lep2_is_conv(); }
	int &lep2_qsc() { return ttz3l.lep2_qsc(); }
	int &lep2_qctf() { return ttz3l.lep2_qctf(); }
	int &lep2_qgsf() { return ttz3l.lep2_qgsf(); }
	int &lep2_nmhits() { return ttz3l.lep2_nmhits(); }
	int &lep2_eleid_veto() { return ttz3l.lep2_eleid_veto(); }
	int &lep2_eleid_loose() { return ttz3l.lep2_eleid_loose(); }
	int &lep2_eleid_medium() { return ttz3l.lep2_eleid_medium(); }
	int &lep2_eleid_tight() { return ttz3l.lep2_eleid_tight(); }
	float &lep2_dphiin() { return ttz3l.lep2_dphiin(); }
	float &lep2_detain() { return ttz3l.lep2_detain(); }
	float &lep2_sieie() { return ttz3l.lep2_sieie(); }
	float &lep2_hoe() { return ttz3l.lep2_hoe(); }
	float &lep2_ooemoop() { return ttz3l.lep2_ooemoop(); }
	float &lep2_conv_dist() { return ttz3l.lep2_conv_dist(); }
	float &lep2_conv_dcot() { return ttz3l.lep2_conv_dcot(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_gfit_p4() { return ttz3l.lep2_gfit_p4(); }
	bool &lep2_is_global() { return ttz3l.lep2_is_global(); }
	bool &lep2_is_tracker() { return ttz3l.lep2_is_tracker(); }
	bool &lep2_is_stamu() { return ttz3l.lep2_is_stamu(); }
	bool &lep2_is_pfmu() { return ttz3l.lep2_is_pfmu(); }
	bool &lep2_is_loosemu() { return ttz3l.lep2_is_loosemu(); }
	bool &lep2_is_tightmu() { return ttz3l.lep2_is_tightmu(); }
	int &lep2_npixelhits() { return ttz3l.lep2_npixelhits(); }
	int &lep2_nsihits() { return ttz3l.lep2_nsihits(); }
	int &lep2_nsilayers() { return ttz3l.lep2_nsilayers(); }
	int &lep2_nstahits() { return ttz3l.lep2_nstahits(); }
	int &lep2_nstations() { return ttz3l.lep2_nstations(); }
	float &lep2_chi2() { return ttz3l.lep2_chi2(); }
	float &lep2_ndof() { return ttz3l.lep2_ndof(); }
	float &lep2_pterr() { return ttz3l.lep2_pterr(); }
	float &lep2_ecal_vetodep() { return ttz3l.lep2_ecal_vetodep(); }
	float &lep2_hcal_vetodep() { return ttz3l.lep2_hcal_vetodep(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &zdilep_p4() { return ttz3l.zdilep_p4(); }
	bool &zis_os() { return ttz3l.zis_os(); }
	bool &zis_ss() { return ttz3l.zis_ss(); }
	int &zdilep_type() { return ttz3l.zdilep_type(); }
	int &zdilep_gen_type() { return ttz3l.zdilep_gen_type(); }
	float &zdilep_mass() { return ttz3l.zdilep_mass(); }
	float &zdilep_dphi() { return ttz3l.zdilep_dphi(); }
	float &zdilep_deta() { return ttz3l.zdilep_deta(); }
	float &zdilep_dr() { return ttz3l.zdilep_dr(); }
	int &zfiduciality() { return ttz3l.zfiduciality(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wp4() { return ttz3l.wp4(); }
	bool &wpasses_id() { return ttz3l.wpasses_id(); }
	bool &wpasses_iso() { return ttz3l.wpasses_iso(); }
	bool &wis_num() { return ttz3l.wis_num(); }
	bool &wis_fo() { return ttz3l.wis_fo(); }
	int &wis_fromw() { return ttz3l.wis_fromw(); }
	int &wcharge() { return ttz3l.wcharge(); }
	int &wpdgid() { return ttz3l.wpdgid(); }
	int &wtype() { return ttz3l.wtype(); }
	float &wd0() { return ttz3l.wd0(); }
	float &wdz() { return ttz3l.wdz(); }
	float &wmt() { return ttz3l.wmt(); }
	float &wcorpfiso() { return ttz3l.wcorpfiso(); }
	float &wpfiso() { return ttz3l.wpfiso(); }
	float &wchiso() { return ttz3l.wchiso(); }
	float &wemiso() { return ttz3l.wemiso(); }
	float &wnhiso() { return ttz3l.wnhiso(); }
	float &wcorpfiso04() { return ttz3l.wcorpfiso04(); }
	float &wpfiso04() { return ttz3l.wpfiso04(); }
	float &wchiso04() { return ttz3l.wchiso04(); }
	float &wemiso04() { return ttz3l.wemiso04(); }
	float &wnhiso04() { return ttz3l.wnhiso04(); }
	float &wcordetiso() { return ttz3l.wcordetiso(); }
	float &wdetiso() { return ttz3l.wdetiso(); }
	float &wtrkiso() { return ttz3l.wtrkiso(); }
	float &wecaliso() { return ttz3l.wecaliso(); }
	float &whcaliso() { return ttz3l.whcaliso(); }
	float &wcordetiso04() { return ttz3l.wcordetiso04(); }
	float &wdetiso04() { return ttz3l.wdetiso04(); }
	float &wtrkiso04() { return ttz3l.wtrkiso04(); }
	float &wecaliso04() { return ttz3l.wecaliso04(); }
	float &whcaliso04() { return ttz3l.whcaliso04(); }
	float &weffarea() { return ttz3l.weffarea(); }
	float &weffarea04() { return ttz3l.weffarea04(); }
	float &wdbeta() { return ttz3l.wdbeta(); }
	float &wdbeta04() { return ttz3l.wdbeta04(); }
	float &wsf_lepeff() { return ttz3l.wsf_lepeff(); }
	float &wsf_trig() { return ttz3l.wsf_trig(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wmcp4() { return ttz3l.wmcp4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wmc3p4() { return ttz3l.wmc3p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wmc_momp4() { return ttz3l.wmc_momp4(); }
	int &wmcid() { return ttz3l.wmcid(); }
	int &wmc3id() { return ttz3l.wmc3id(); }
	int &wmomid() { return ttz3l.wmomid(); }
	int &wmc3_momid() { return ttz3l.wmc3_momid(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wgsf_p4() { return ttz3l.wgsf_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wctf_p4() { return ttz3l.wctf_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wsc_p4() { return ttz3l.wsc_p4(); }
	bool &wq3agree() { return ttz3l.wq3agree(); }
	bool &wis_conv() { return ttz3l.wis_conv(); }
	int &wqsc() { return ttz3l.wqsc(); }
	int &wqctf() { return ttz3l.wqctf(); }
	int &wqgsf() { return ttz3l.wqgsf(); }
	int &wnmhits() { return ttz3l.wnmhits(); }
	int &weleid_veto() { return ttz3l.weleid_veto(); }
	int &weleid_loose() { return ttz3l.weleid_loose(); }
	int &weleid_medium() { return ttz3l.weleid_medium(); }
	int &weleid_tight() { return ttz3l.weleid_tight(); }
	float &wdphiin() { return ttz3l.wdphiin(); }
	float &wdetain() { return ttz3l.wdetain(); }
	float &wsieie() { return ttz3l.wsieie(); }
	float &whoe() { return ttz3l.whoe(); }
	float &wooemoop() { return ttz3l.wooemoop(); }
	float &wconv_dist() { return ttz3l.wconv_dist(); }
	float &wconv_dcot() { return ttz3l.wconv_dcot(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wgfit_p4() { return ttz3l.wgfit_p4(); }
	bool &wis_global() { return ttz3l.wis_global(); }
	bool &wis_tracker() { return ttz3l.wis_tracker(); }
	bool &wis_stamu() { return ttz3l.wis_stamu(); }
	bool &wis_pfmu() { return ttz3l.wis_pfmu(); }
	bool &wis_loosemu() { return ttz3l.wis_loosemu(); }
	bool &wis_tightmu() { return ttz3l.wis_tightmu(); }
	int &wnpixelhits() { return ttz3l.wnpixelhits(); }
	int &wnsihits() { return ttz3l.wnsihits(); }
	int &wnsilayers() { return ttz3l.wnsilayers(); }
	int &wnstahits() { return ttz3l.wnstahits(); }
	int &wnstations() { return ttz3l.wnstations(); }
	float &wchi2() { return ttz3l.wchi2(); }
	float &wndof() { return ttz3l.wndof(); }
	float &wpterr() { return ttz3l.wpterr(); }
	float &wecal_vetodep() { return ttz3l.wecal_vetodep(); }
	float &whcal_vetodep() { return ttz3l.whcal_vetodep(); }
	unsigned int &selection() { return ttz3l.selection(); }
	bool &clean() { return ttz3l.clean(); }
	bool &is_good_lumi() { return ttz3l.is_good_lumi(); }
	int &njets15() { return ttz3l.njets15(); }
	int &njets30() { return ttz3l.njets30(); }
	int &nbtags_loose() { return ttz3l.nbtags_loose(); }
	int &nbtags_tight() { return ttz3l.nbtags_tight(); }
	float &vtxw() { return ttz3l.vtxw(); }
	float &ht() { return ttz3l.ht(); }
	float &rho() { return ttz3l.rho(); }
	float &rho_iso() { return ttz3l.rho_iso(); }
	float &sf_dileptrig() { return ttz3l.sf_dileptrig(); }
	float &sf_lepeff() { return ttz3l.sf_lepeff(); }
	bool &trig_mm() { return ttz3l.trig_mm(); }
	bool &trig_em() { return ttz3l.trig_em(); }
	bool &trig_ee() { return ttz3l.trig_ee(); }
	int &event_type() { return ttz3l.event_type(); }
	int &njets30_dn() { return ttz3l.njets30_dn(); }
	int &njets30_up() { return ttz3l.njets30_up(); }
	int &njets15_dn() { return ttz3l.njets15_dn(); }
	int &njets15_up() { return ttz3l.njets15_up(); }
	int &nbtags_loose_dn() { return ttz3l.nbtags_loose_dn(); }
	int &nbtags_loose_up() { return ttz3l.nbtags_loose_up(); }
	float &ht_dn() { return ttz3l.ht_dn(); }
	float &ht_up() { return ttz3l.ht_up(); }
	float &pfmet_dn() { return ttz3l.pfmet_dn(); }
	float &pfmet_up() { return ttz3l.pfmet_up(); }
	float &pfmet_phi_dn() { return ttz3l.pfmet_phi_dn(); }
	float &pfmet_phi_up() { return ttz3l.pfmet_phi_up(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearbjet_p4() { return ttz3l.lep1_nearbjet_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearjet_p4() { return ttz3l.lep1_nearjet_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearlep_p4() { return ttz3l.lep1_nearlep_p4(); }
	float &lep1_wfr() { return ttz3l.lep1_wfr(); }
	float &lep1_nearbjet_dr() { return ttz3l.lep1_nearbjet_dr(); }
	float &lep1_nearjet_dr() { return ttz3l.lep1_nearjet_dr(); }
	float &lep1_nearlep_dr() { return ttz3l.lep1_nearlep_dr(); }
	int &lep1_nearlep_id() { return ttz3l.lep1_nearlep_id(); }
	int &lep1_passes_id_bitmask() { return ttz3l.lep1_passes_id_bitmask(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearbjet_p4() { return ttz3l.lep2_nearbjet_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearjet_p4() { return ttz3l.lep2_nearjet_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearlep_p4() { return ttz3l.lep2_nearlep_p4(); }
	float &lep2_wfr() { return ttz3l.lep2_wfr(); }
	float &lep2_nearbjet_dr() { return ttz3l.lep2_nearbjet_dr(); }
	float &lep2_nearjet_dr() { return ttz3l.lep2_nearjet_dr(); }
	float &lep2_nearlep_dr() { return ttz3l.lep2_nearlep_dr(); }
	int &lep2_nearlep_id() { return ttz3l.lep2_nearlep_id(); }
	int &lep2_passes_id_bitmask() { return ttz3l.lep2_passes_id_bitmask(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_nearbjet_p4() { return ttz3l.lep3_nearbjet_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_nearjet_p4() { return ttz3l.lep3_nearjet_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_nearlep_p4() { return ttz3l.lep3_nearlep_p4(); }
	float &lep3_wfr() { return ttz3l.lep3_wfr(); }
	float &lep3_nearbjet_dr() { return ttz3l.lep3_nearbjet_dr(); }
	float &lep3_nearjet_dr() { return ttz3l.lep3_nearjet_dr(); }
	float &lep3_nearlep_dr() { return ttz3l.lep3_nearlep_dr(); }
	int &lep3_nearlep_id() { return ttz3l.lep3_nearlep_id(); }
	int &lep3_passes_id_bitmask() { return ttz3l.lep3_passes_id_bitmask(); }
	bool &is_gen_z() { return ttz3l.is_gen_z(); }
	bool &is_gen_w() { return ttz3l.is_gen_w(); }
	int &gen_nbtags() { return ttz3l.gen_nbtags(); }
	int &gen_njets() { return ttz3l.gen_njets(); }
	float &gen_ht() { return ttz3l.gen_ht(); }
	float &gen_nleps() { return ttz3l.gen_nleps(); }
	float &sf_nbtag() { return ttz3l.sf_nbtag(); }
	float &sf_nbtag2() { return ttz3l.sf_nbtag2(); }
	float &sf_unc_nbtag() { return ttz3l.sf_unc_nbtag(); }
	float &sf_unc_nbtag2() { return ttz3l.sf_unc_nbtag2(); }
	float &bjets_dr12() { return ttz3l.bjets_dr12(); }
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vgenb_p4() { return ttz3l.vgenb_p4(); }
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_p4() { return ttz3l.vjets_p4(); }
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vgenjets_p4() { return ttz3l.vgenjets_p4(); }
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vbjets_p4() { return ttz3l.vbjets_p4(); }
	vector<bool> &vbtags_loose() { return ttz3l.vbtags_loose(); }
	vector<bool> &vbtags_tight() { return ttz3l.vbtags_tight(); }
	vector<float> &vbjets_disc() { return ttz3l.vbjets_disc(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep1_p4() { return ttz3l.gen_lep1_p4(); }
	int &gen_lep1_pdgid() { return ttz3l.gen_lep1_pdgid(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep2_p4() { return ttz3l.gen_lep2_p4(); }
	int &gen_lep2_pdgid() { return ttz3l.gen_lep2_pdgid(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep3_p4() { return ttz3l.gen_lep3_p4(); }
	float &gen_mt() { return ttz3l.gen_mt(); }
	int &gen_lep3_pdgid() { return ttz3l.gen_lep3_pdgid(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_dilep_p4() { return ttz3l.gen_dilep_p4(); }
	int &gen_dilep_type() { return ttz3l.gen_dilep_type(); }
	float &gen_dilep_mass() { return ttz3l.gen_dilep_mass(); }
	float &gen_dilep_dphi() { return ttz3l.gen_dilep_dphi(); }
	float &gen_dilep_deta() { return ttz3l.gen_dilep_deta(); }
	float &gen_dilep_dr() { return ttz3l.gen_dilep_dr(); }
	float &lep1_ele_mva_trig() { return ttz3l.lep1_ele_mva_trig(); }
	float &lep2_ele_mva_trig() { return ttz3l.lep2_ele_mva_trig(); }
	float &lep3_ele_mva_trig() { return ttz3l.lep3_ele_mva_trig(); }
	float &lep1_ele_mva_nontrig() { return ttz3l.lep1_ele_mva_nontrig(); }
	float &lep2_ele_mva_nontrig() { return ttz3l.lep2_ele_mva_nontrig(); }
	float &lep3_ele_mva_nontrig() { return ttz3l.lep3_ele_mva_nontrig(); }
}
