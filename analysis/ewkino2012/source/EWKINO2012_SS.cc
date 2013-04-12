#include "EWKINO2012_SS.h"
EWKINO2012_SS ewk12ss;
namespace ewkino_ss {
	const unsigned int &run() { return ewk12ss.run(); }
	const unsigned int &ls() { return ewk12ss.ls(); }
	const unsigned int &evt() { return ewk12ss.evt(); }
	const bool &is_real_data() { return ewk12ss.is_real_data(); }
	const int &sample() { return ewk12ss.sample(); }
	const int &nvtxs() { return ewk12ss.nvtxs(); }
	const int &vtx_idx() { return ewk12ss.vtx_idx(); }
	const float &pfmet() { return ewk12ss.pfmet(); }
	const float &pfmet_phi() { return ewk12ss.pfmet_phi(); }
	const float &uncorpfmet() { return ewk12ss.uncorpfmet(); }
	const float &uncorpfmet_phi() { return ewk12ss.uncorpfmet_phi(); }
	const float &pu_nvtxs() { return ewk12ss.pu_nvtxs(); }
	const float &pu_ntrueint() { return ewk12ss.pu_ntrueint(); }
	const float &scale1fb() { return ewk12ss.scale1fb(); }
	const float &xsec() { return ewk12ss.xsec(); }
	const unsigned int &nevts() { return ewk12ss.nevts(); }
	const float &kfactor() { return ewk12ss.kfactor(); }
	const float &gen_met() { return ewk12ss.gen_met(); }
	const float &gen_met_phi() { return ewk12ss.gen_met_phi(); }
	const TString &dataset() { return ewk12ss.dataset(); }
	const TString &filename() { return ewk12ss.filename(); }
	const bool &filt_csc() { return ewk12ss.filt_csc(); }
	const bool &filt_hbhe() { return ewk12ss.filt_hbhe(); }
	const bool &filt_hcallaser() { return ewk12ss.filt_hcallaser(); }
	const bool &filt_ecallaser() { return ewk12ss.filt_ecallaser(); }
	const bool &filt_ecaltp() { return ewk12ss.filt_ecaltp(); }
	const bool &filt_trkfail() { return ewk12ss.filt_trkfail(); }
	const bool &filt_eebadsc() { return ewk12ss.filt_eebadsc(); }
	const bool &passes_metfilters() { return ewk12ss.passes_metfilters(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_p4() { return ewk12ss.lep1_p4(); }
	const bool &lep1_passes_id() { return ewk12ss.lep1_passes_id(); }
	const bool &lep1_passes_iso() { return ewk12ss.lep1_passes_iso(); }
	const bool &lep1_is_num() { return ewk12ss.lep1_is_num(); }
	const bool &lep1_is_den() { return ewk12ss.lep1_is_den(); }
	const bool &lep1_is_fo() { return ewk12ss.lep1_is_fo(); }
	const int &lep1_is_fromw() { return ewk12ss.lep1_is_fromw(); }
	const int &lep1_charge() { return ewk12ss.lep1_charge(); }
	const int &lep1_pdgid() { return ewk12ss.lep1_pdgid(); }
	const int &lep1_type() { return ewk12ss.lep1_type(); }
	const float &lep1_d0() { return ewk12ss.lep1_d0(); }
	const float &lep1_d0err() { return ewk12ss.lep1_d0err(); }
	const float &lep1_dz() { return ewk12ss.lep1_dz(); }
	const float &lep1_ip3d() { return ewk12ss.lep1_ip3d(); }
	const float &lep1_ip3derr() { return ewk12ss.lep1_ip3derr(); }
	const float &lep1_dzerr() { return ewk12ss.lep1_dzerr(); }
	const float &lep1_mt() { return ewk12ss.lep1_mt(); }
	const float &lep1_corpfiso() { return ewk12ss.lep1_corpfiso(); }
	const float &lep1_pfiso() { return ewk12ss.lep1_pfiso(); }
	const float &lep1_chiso() { return ewk12ss.lep1_chiso(); }
	const float &lep1_emiso() { return ewk12ss.lep1_emiso(); }
	const float &lep1_nhiso() { return ewk12ss.lep1_nhiso(); }
	const float &lep1_corpfiso04() { return ewk12ss.lep1_corpfiso04(); }
	const float &lep1_pfiso04() { return ewk12ss.lep1_pfiso04(); }
	const float &lep1_chiso04() { return ewk12ss.lep1_chiso04(); }
	const float &lep1_emiso04() { return ewk12ss.lep1_emiso04(); }
	const float &lep1_nhiso04() { return ewk12ss.lep1_nhiso04(); }
	const float &lep1_cordetiso() { return ewk12ss.lep1_cordetiso(); }
	const float &lep1_detiso() { return ewk12ss.lep1_detiso(); }
	const float &lep1_trkiso() { return ewk12ss.lep1_trkiso(); }
	const float &lep1_ecaliso() { return ewk12ss.lep1_ecaliso(); }
	const float &lep1_hcaliso() { return ewk12ss.lep1_hcaliso(); }
	const float &lep1_cordetiso04() { return ewk12ss.lep1_cordetiso04(); }
	const float &lep1_detiso04() { return ewk12ss.lep1_detiso04(); }
	const float &lep1_trkiso04() { return ewk12ss.lep1_trkiso04(); }
	const float &lep1_ecaliso04() { return ewk12ss.lep1_ecaliso04(); }
	const float &lep1_hcaliso04() { return ewk12ss.lep1_hcaliso04(); }
	const float &lep1_effarea() { return ewk12ss.lep1_effarea(); }
	const float &lep1_effarea04() { return ewk12ss.lep1_effarea04(); }
	const float &lep1_dbeta() { return ewk12ss.lep1_dbeta(); }
	const float &lep1_dbeta04() { return ewk12ss.lep1_dbeta04(); }
	const float &lep1_sf_lepeff() { return ewk12ss.lep1_sf_lepeff(); }
	const float &lep1_sf_trig() { return ewk12ss.lep1_sf_trig(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mcp4() { return ewk12ss.lep1_mcp4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mc3p4() { return ewk12ss.lep1_mc3p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mc_momp4() { return ewk12ss.lep1_mc_momp4(); }
	const int &lep1_mcid() { return ewk12ss.lep1_mcid(); }
	const int &lep1_mc3id() { return ewk12ss.lep1_mc3id(); }
	const int &lep1_momid() { return ewk12ss.lep1_momid(); }
	const int &lep1_mc3_momid() { return ewk12ss.lep1_mc3_momid(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_gsf_p4() { return ewk12ss.lep1_gsf_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_ctf_p4() { return ewk12ss.lep1_ctf_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_sc_p4() { return ewk12ss.lep1_sc_p4(); }
	const bool &lep1_q3agree() { return ewk12ss.lep1_q3agree(); }
	const bool &lep1_is_conv() { return ewk12ss.lep1_is_conv(); }
	const int &lep1_qsc() { return ewk12ss.lep1_qsc(); }
	const int &lep1_qctf() { return ewk12ss.lep1_qctf(); }
	const int &lep1_qgsf() { return ewk12ss.lep1_qgsf(); }
	const int &lep1_nmhits() { return ewk12ss.lep1_nmhits(); }
	const int &lep1_eleid_veto() { return ewk12ss.lep1_eleid_veto(); }
	const int &lep1_eleid_loose() { return ewk12ss.lep1_eleid_loose(); }
	const int &lep1_eleid_medium() { return ewk12ss.lep1_eleid_medium(); }
	const int &lep1_eleid_tight() { return ewk12ss.lep1_eleid_tight(); }
	const float &lep1_dphiin() { return ewk12ss.lep1_dphiin(); }
	const float &lep1_detain() { return ewk12ss.lep1_detain(); }
	const float &lep1_sieie() { return ewk12ss.lep1_sieie(); }
	const float &lep1_hoe() { return ewk12ss.lep1_hoe(); }
	const float &lep1_ooemoop() { return ewk12ss.lep1_ooemoop(); }
	const float &lep1_conv_dist() { return ewk12ss.lep1_conv_dist(); }
	const float &lep1_conv_dcot() { return ewk12ss.lep1_conv_dcot(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_gfit_p4() { return ewk12ss.lep1_gfit_p4(); }
	const bool &lep1_is_global() { return ewk12ss.lep1_is_global(); }
	const bool &lep1_is_tracker() { return ewk12ss.lep1_is_tracker(); }
	const bool &lep1_is_stamu() { return ewk12ss.lep1_is_stamu(); }
	const bool &lep1_is_pfmu() { return ewk12ss.lep1_is_pfmu(); }
	const bool &lep1_is_loosemu() { return ewk12ss.lep1_is_loosemu(); }
	const bool &lep1_is_tightmu() { return ewk12ss.lep1_is_tightmu(); }
	const int &lep1_npixelhits() { return ewk12ss.lep1_npixelhits(); }
	const int &lep1_nsihits() { return ewk12ss.lep1_nsihits(); }
	const int &lep1_nsilayers() { return ewk12ss.lep1_nsilayers(); }
	const int &lep1_nstahits() { return ewk12ss.lep1_nstahits(); }
	const int &lep1_nstations() { return ewk12ss.lep1_nstations(); }
	const float &lep1_chi2() { return ewk12ss.lep1_chi2(); }
	const float &lep1_ndof() { return ewk12ss.lep1_ndof(); }
	const float &lep1_pterr() { return ewk12ss.lep1_pterr(); }
	const float &lep1_ecal_vetodep() { return ewk12ss.lep1_ecal_vetodep(); }
	const float &lep1_hcal_vetodep() { return ewk12ss.lep1_hcal_vetodep(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_p4() { return ewk12ss.lep2_p4(); }
	const bool &lep2_passes_id() { return ewk12ss.lep2_passes_id(); }
	const bool &lep2_passes_iso() { return ewk12ss.lep2_passes_iso(); }
	const bool &lep2_is_num() { return ewk12ss.lep2_is_num(); }
	const bool &lep2_is_den() { return ewk12ss.lep2_is_den(); }
	const bool &lep2_is_fo() { return ewk12ss.lep2_is_fo(); }
	const int &lep2_is_fromw() { return ewk12ss.lep2_is_fromw(); }
	const int &lep2_charge() { return ewk12ss.lep2_charge(); }
	const int &lep2_pdgid() { return ewk12ss.lep2_pdgid(); }
	const int &lep2_type() { return ewk12ss.lep2_type(); }
	const float &lep2_d0() { return ewk12ss.lep2_d0(); }
	const float &lep2_d0err() { return ewk12ss.lep2_d0err(); }
	const float &lep2_dz() { return ewk12ss.lep2_dz(); }
	const float &lep2_ip3d() { return ewk12ss.lep2_ip3d(); }
	const float &lep2_ip3derr() { return ewk12ss.lep2_ip3derr(); }
	const float &lep2_dzerr() { return ewk12ss.lep2_dzerr(); }
	const float &lep2_mt() { return ewk12ss.lep2_mt(); }
	const float &lep2_corpfiso() { return ewk12ss.lep2_corpfiso(); }
	const float &lep2_pfiso() { return ewk12ss.lep2_pfiso(); }
	const float &lep2_chiso() { return ewk12ss.lep2_chiso(); }
	const float &lep2_emiso() { return ewk12ss.lep2_emiso(); }
	const float &lep2_nhiso() { return ewk12ss.lep2_nhiso(); }
	const float &lep2_corpfiso04() { return ewk12ss.lep2_corpfiso04(); }
	const float &lep2_pfiso04() { return ewk12ss.lep2_pfiso04(); }
	const float &lep2_chiso04() { return ewk12ss.lep2_chiso04(); }
	const float &lep2_emiso04() { return ewk12ss.lep2_emiso04(); }
	const float &lep2_nhiso04() { return ewk12ss.lep2_nhiso04(); }
	const float &lep2_cordetiso() { return ewk12ss.lep2_cordetiso(); }
	const float &lep2_detiso() { return ewk12ss.lep2_detiso(); }
	const float &lep2_trkiso() { return ewk12ss.lep2_trkiso(); }
	const float &lep2_ecaliso() { return ewk12ss.lep2_ecaliso(); }
	const float &lep2_hcaliso() { return ewk12ss.lep2_hcaliso(); }
	const float &lep2_cordetiso04() { return ewk12ss.lep2_cordetiso04(); }
	const float &lep2_detiso04() { return ewk12ss.lep2_detiso04(); }
	const float &lep2_trkiso04() { return ewk12ss.lep2_trkiso04(); }
	const float &lep2_ecaliso04() { return ewk12ss.lep2_ecaliso04(); }
	const float &lep2_hcaliso04() { return ewk12ss.lep2_hcaliso04(); }
	const float &lep2_effarea() { return ewk12ss.lep2_effarea(); }
	const float &lep2_effarea04() { return ewk12ss.lep2_effarea04(); }
	const float &lep2_dbeta() { return ewk12ss.lep2_dbeta(); }
	const float &lep2_dbeta04() { return ewk12ss.lep2_dbeta04(); }
	const float &lep2_sf_lepeff() { return ewk12ss.lep2_sf_lepeff(); }
	const float &lep2_sf_trig() { return ewk12ss.lep2_sf_trig(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mcp4() { return ewk12ss.lep2_mcp4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mc3p4() { return ewk12ss.lep2_mc3p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mc_momp4() { return ewk12ss.lep2_mc_momp4(); }
	const int &lep2_mcid() { return ewk12ss.lep2_mcid(); }
	const int &lep2_mc3id() { return ewk12ss.lep2_mc3id(); }
	const int &lep2_momid() { return ewk12ss.lep2_momid(); }
	const int &lep2_mc3_momid() { return ewk12ss.lep2_mc3_momid(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_gsf_p4() { return ewk12ss.lep2_gsf_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_ctf_p4() { return ewk12ss.lep2_ctf_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_sc_p4() { return ewk12ss.lep2_sc_p4(); }
	const bool &lep2_q3agree() { return ewk12ss.lep2_q3agree(); }
	const bool &lep2_is_conv() { return ewk12ss.lep2_is_conv(); }
	const int &lep2_qsc() { return ewk12ss.lep2_qsc(); }
	const int &lep2_qctf() { return ewk12ss.lep2_qctf(); }
	const int &lep2_qgsf() { return ewk12ss.lep2_qgsf(); }
	const int &lep2_nmhits() { return ewk12ss.lep2_nmhits(); }
	const int &lep2_eleid_veto() { return ewk12ss.lep2_eleid_veto(); }
	const int &lep2_eleid_loose() { return ewk12ss.lep2_eleid_loose(); }
	const int &lep2_eleid_medium() { return ewk12ss.lep2_eleid_medium(); }
	const int &lep2_eleid_tight() { return ewk12ss.lep2_eleid_tight(); }
	const float &lep2_dphiin() { return ewk12ss.lep2_dphiin(); }
	const float &lep2_detain() { return ewk12ss.lep2_detain(); }
	const float &lep2_sieie() { return ewk12ss.lep2_sieie(); }
	const float &lep2_hoe() { return ewk12ss.lep2_hoe(); }
	const float &lep2_ooemoop() { return ewk12ss.lep2_ooemoop(); }
	const float &lep2_conv_dist() { return ewk12ss.lep2_conv_dist(); }
	const float &lep2_conv_dcot() { return ewk12ss.lep2_conv_dcot(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_gfit_p4() { return ewk12ss.lep2_gfit_p4(); }
	const bool &lep2_is_global() { return ewk12ss.lep2_is_global(); }
	const bool &lep2_is_tracker() { return ewk12ss.lep2_is_tracker(); }
	const bool &lep2_is_stamu() { return ewk12ss.lep2_is_stamu(); }
	const bool &lep2_is_pfmu() { return ewk12ss.lep2_is_pfmu(); }
	const bool &lep2_is_loosemu() { return ewk12ss.lep2_is_loosemu(); }
	const bool &lep2_is_tightmu() { return ewk12ss.lep2_is_tightmu(); }
	const int &lep2_npixelhits() { return ewk12ss.lep2_npixelhits(); }
	const int &lep2_nsihits() { return ewk12ss.lep2_nsihits(); }
	const int &lep2_nsilayers() { return ewk12ss.lep2_nsilayers(); }
	const int &lep2_nstahits() { return ewk12ss.lep2_nstahits(); }
	const int &lep2_nstations() { return ewk12ss.lep2_nstations(); }
	const float &lep2_chi2() { return ewk12ss.lep2_chi2(); }
	const float &lep2_ndof() { return ewk12ss.lep2_ndof(); }
	const float &lep2_pterr() { return ewk12ss.lep2_pterr(); }
	const float &lep2_ecal_vetodep() { return ewk12ss.lep2_ecal_vetodep(); }
	const float &lep2_hcal_vetodep() { return ewk12ss.lep2_hcal_vetodep(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &dilep_p4() { return ewk12ss.dilep_p4(); }
	const bool &is_os() { return ewk12ss.is_os(); }
	const bool &is_ss() { return ewk12ss.is_ss(); }
	const bool &mm() { return ewk12ss.mm(); }
	const bool &ee() { return ewk12ss.ee(); }
	const bool &em() { return ewk12ss.em(); }
	const int &dilep_type() { return ewk12ss.dilep_type(); }
	const int &dilep_gen_type() { return ewk12ss.dilep_gen_type(); }
	const float &dilep_mass() { return ewk12ss.dilep_mass(); }
	const float &dilep_dphi() { return ewk12ss.dilep_dphi(); }
	const float &dilep_deta() { return ewk12ss.dilep_deta(); }
	const float &dilep_dr() { return ewk12ss.dilep_dr(); }
	const int &fiduciality() { return ewk12ss.fiduciality(); }
	const unsigned int &selection() { return ewk12ss.selection(); }
	const bool &is_good_lumi() { return ewk12ss.is_good_lumi(); }
	const int &njets() { return ewk12ss.njets(); }
	const int &nbtags() { return ewk12ss.nbtags(); }
	const int &ttbar_bkdn() { return ewk12ss.ttbar_bkdn(); }
	const float &vtxw() { return ewk12ss.vtxw(); }
	const float &mt() { return ewk12ss.mt(); }
	const float &ht() { return ewk12ss.ht(); }
	const float &rho() { return ewk12ss.rho(); }
	const float &rho_iso() { return ewk12ss.rho_iso(); }
	const bool &trig_mm() { return ewk12ss.trig_mm(); }
	const bool &trig_em() { return ewk12ss.trig_em(); }
	const bool &trig_ee() { return ewk12ss.trig_ee(); }
	const bool &trig_mm_mu17_mu8() { return ewk12ss.trig_mm_mu17_mu8(); }
	const bool &trig_ee_el17_el8_id_iso() { return ewk12ss.trig_ee_el17_el8_id_iso(); }
	const bool &trig_em_mu17_el8_id_iso() { return ewk12ss.trig_em_mu17_el8_id_iso(); }
	const bool &trig_em_mu8_el17_id_iso() { return ewk12ss.trig_em_mu8_el17_id_iso(); }
	const int &njets_dn() { return ewk12ss.njets_dn(); }
	const int &njets_up() { return ewk12ss.njets_up(); }
	const int &nbtags_dn() { return ewk12ss.nbtags_dn(); }
	const int &nbtags_up() { return ewk12ss.nbtags_up(); }
	const float &ht_dn() { return ewk12ss.ht_dn(); }
	const float &ht_up() { return ewk12ss.ht_up(); }
	const int &nbtags_reweighted() { return ewk12ss.nbtags_reweighted(); }
	const int &nbtags_reweighted_dn() { return ewk12ss.nbtags_reweighted_dn(); }
	const int &nbtags_reweighted_up() { return ewk12ss.nbtags_reweighted_up(); }
	const int &nbtags_reweighted_jec_dn() { return ewk12ss.nbtags_reweighted_jec_dn(); }
	const int &nbtags_reweighted_jec_up() { return ewk12ss.nbtags_reweighted_jec_up(); }
	const float &pfmet_dn() { return ewk12ss.pfmet_dn(); }
	const float &pfmet_up() { return ewk12ss.pfmet_up(); }
	const float &pfmet_phi_dn() { return ewk12ss.pfmet_phi_dn(); }
	const float &pfmet_phi_up() { return ewk12ss.pfmet_phi_up(); }
	const float &sf_dileptrig() { return ewk12ss.sf_dileptrig(); }
	const float &sf_lepeff() { return ewk12ss.sf_lepeff(); }
	const float &sparm0() { return ewk12ss.sparm0(); }
	const float &sparm1() { return ewk12ss.sparm1(); }
	const float &sparm2() { return ewk12ss.sparm2(); }
	const float &sparm3() { return ewk12ss.sparm3(); }
	const TString &sparm0_name() { return ewk12ss.sparm0_name(); }
	const TString &sparm1_name() { return ewk12ss.sparm1_name(); }
	const TString &sparm2_name() { return ewk12ss.sparm2_name(); }
	const TString &sparm3_name() { return ewk12ss.sparm3_name(); }
	const bool &is_pp() { return ewk12ss.is_pp(); }
	const bool &is_mm() { return ewk12ss.is_mm(); }
	const bool &is_sf() { return ewk12ss.is_sf(); }
	const bool &is_df() { return ewk12ss.is_df(); }
	const bool &no_extraz() { return ewk12ss.no_extraz(); }
	const bool &no_extrag() { return ewk12ss.no_extrag(); }
	const bool &clean() { return ewk12ss.clean(); }
	const bool &presel() { return ewk12ss.presel(); }
	const bool &em_mufo() { return ewk12ss.em_mufo(); }
	const bool &em_elfo() { return ewk12ss.em_elfo(); }
	const bool &hyp_good_vtx() { return ewk12ss.hyp_good_vtx(); }
	const bool &is_gen_pp() { return ewk12ss.is_gen_pp(); }
	const bool &is_gen_mm() { return ewk12ss.is_gen_mm(); }
	const int &gen_njets() { return ewk12ss.gen_njets(); }
	const int &gen_nleps() { return ewk12ss.gen_nleps(); }
	const int &gen_nmus() { return ewk12ss.gen_nmus(); }
	const int &gen_nels() { return ewk12ss.gen_nels(); }
	const int &gen_ntaus() { return ewk12ss.gen_ntaus(); }
	const float &gen_ht() { return ewk12ss.gen_ht(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearjet_p4() { return ewk12ss.lep1_nearjet_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearlep_p4() { return ewk12ss.lep1_nearlep_p4(); }
	const float &lep1_wfr() { return ewk12ss.lep1_wfr(); }
	const float &lep1_wflip() { return ewk12ss.lep1_wflip(); }
	const float &lep1_nearjet_dr() { return ewk12ss.lep1_nearjet_dr(); }
	const float &lep1_nearlep_dr() { return ewk12ss.lep1_nearlep_dr(); }
	const int &lep1_nearlep_id() { return ewk12ss.lep1_nearlep_id(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearjet_p4() { return ewk12ss.lep2_nearjet_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearlep_p4() { return ewk12ss.lep2_nearlep_p4(); }
	const float &lep2_wfr() { return ewk12ss.lep2_wfr(); }
	const float &lep2_wflip() { return ewk12ss.lep2_wflip(); }
	const float &lep2_nearjet_dr() { return ewk12ss.lep2_nearjet_dr(); }
	const float &lep2_nearlep_dr() { return ewk12ss.lep2_nearlep_dr(); }
	const int &lep2_nearlep_id() { return ewk12ss.lep2_nearlep_id(); }
	const float &jets_dr12() { return ewk12ss.jets_dr12(); }
	const float &dijet_mass() { return ewk12ss.dijet_mass(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_p4() { return ewk12ss.vjets_p4(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_p4_up() { return ewk12ss.vjets_p4_up(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_p4_dn() { return ewk12ss.vjets_p4_dn(); }
	const vector<int> &vjets_mcflavor_phys() { return ewk12ss.vjets_mcflavor_phys(); }
	const vector<int> &vjets_mcflavor_algo() { return ewk12ss.vjets_mcflavor_algo(); }
	const vector<int> &vjets_mcflavor_phys_up() { return ewk12ss.vjets_mcflavor_phys_up(); }
	const vector<int> &vjets_mcflavor_algo_up() { return ewk12ss.vjets_mcflavor_algo_up(); }
	const vector<int> &vjets_mcflavor_phys_dn() { return ewk12ss.vjets_mcflavor_phys_dn(); }
	const vector<int> &vjets_mcflavor_algo_dn() { return ewk12ss.vjets_mcflavor_algo_dn(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_mc3p4() { return ewk12ss.vjets_mc3p4(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vgenjets_p4() { return ewk12ss.vgenjets_p4(); }
	const vector<int> &vjets_mc3id() { return ewk12ss.vjets_mc3id(); }
	const vector<int> &vjets_momid() { return ewk12ss.vjets_momid(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_nearjet_p4() { return ewk12ss.vjets_nearjet_p4(); }
	const vector<float> &vjets_bdisc() { return ewk12ss.vjets_bdisc(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep1_p4() { return ewk12ss.gen_lep1_p4(); }
	const int &gen_lep1_pdgid() { return ewk12ss.gen_lep1_pdgid(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep2_p4() { return ewk12ss.gen_lep2_p4(); }
	const int &gen_lep2_pdgid() { return ewk12ss.gen_lep2_pdgid(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_dilep_p4() { return ewk12ss.gen_dilep_p4(); }
	const int &gen_dilep_type() { return ewk12ss.gen_dilep_type(); }
	const float &gen_dilep_mass() { return ewk12ss.gen_dilep_mass(); }
	const float &gen_dilep_dphi() { return ewk12ss.gen_dilep_dphi(); }
	const float &gen_dilep_deta() { return ewk12ss.gen_dilep_deta(); }
	const float &gen_dilep_dr() { return ewk12ss.gen_dilep_dr(); }
}
