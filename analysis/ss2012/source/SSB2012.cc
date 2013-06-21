#include "SSB2012.h"
SSB2012 samesignbtag;
namespace ssb {
	const unsigned int &run() { return samesignbtag.run(); }
	const unsigned int &ls() { return samesignbtag.ls(); }
	const unsigned int &evt() { return samesignbtag.evt(); }
	const bool &is_real_data() { return samesignbtag.is_real_data(); }
	const int &sample() { return samesignbtag.sample(); }
	const int &nvtxs() { return samesignbtag.nvtxs(); }
	const int &vtx_idx() { return samesignbtag.vtx_idx(); }
	const float &pfmet() { return samesignbtag.pfmet(); }
	const float &pfmet_phi() { return samesignbtag.pfmet_phi(); }
	const float &uncorpfmet() { return samesignbtag.uncorpfmet(); }
	const float &uncorpfmet_phi() { return samesignbtag.uncorpfmet_phi(); }
	const float &pu_nvtxs() { return samesignbtag.pu_nvtxs(); }
	const float &pu_ntrueint() { return samesignbtag.pu_ntrueint(); }
	const float &scale1fb() { return samesignbtag.scale1fb(); }
	const float &xsec() { return samesignbtag.xsec(); }
	const unsigned int &nevts() { return samesignbtag.nevts(); }
	const float &kfactor() { return samesignbtag.kfactor(); }
	const float &gen_met() { return samesignbtag.gen_met(); }
	const float &gen_met_phi() { return samesignbtag.gen_met_phi(); }
	const TString &dataset() { return samesignbtag.dataset(); }
	const TString &filename() { return samesignbtag.filename(); }
	const int &gen_nleps() { return samesignbtag.gen_nleps(); }
	const int &gen_nels() { return samesignbtag.gen_nels(); }
	const int &gen_nmus() { return samesignbtag.gen_nmus(); }
	const int &gen_ntaus() { return samesignbtag.gen_ntaus(); }
	const int &gen_nleps_with_fromtau() { return samesignbtag.gen_nleps_with_fromtau(); }
	const int &gen_nels_with_fromtau() { return samesignbtag.gen_nels_with_fromtau(); }
	const int &gen_nmus_with_fromtau() { return samesignbtag.gen_nmus_with_fromtau(); }
	const int &gen_ntaus_with_fromtau() { return samesignbtag.gen_ntaus_with_fromtau(); }
	const bool &filt_csc() { return samesignbtag.filt_csc(); }
	const bool &filt_hbhe() { return samesignbtag.filt_hbhe(); }
	const bool &filt_hcallaser() { return samesignbtag.filt_hcallaser(); }
	const bool &filt_ecallaser() { return samesignbtag.filt_ecallaser(); }
	const bool &filt_ecaltp() { return samesignbtag.filt_ecaltp(); }
	const bool &filt_trkfail() { return samesignbtag.filt_trkfail(); }
	const bool &filt_eebadsc() { return samesignbtag.filt_eebadsc(); }
	const bool &passes_metfilters() { return samesignbtag.passes_metfilters(); }
	const bool &lep1_passes_id() { return samesignbtag.lep1_passes_id(); }
	const bool &lep1_passes_iso() { return samesignbtag.lep1_passes_iso(); }
	const bool &lep1_is_num() { return samesignbtag.lep1_is_num(); }
	const bool &lep1_is_den() { return samesignbtag.lep1_is_den(); }
	const bool &lep1_is_fo() { return samesignbtag.lep1_is_fo(); }
	const int &lep1_is_fromw() { return samesignbtag.lep1_is_fromw(); }
	const int &lep1_charge() { return samesignbtag.lep1_charge(); }
	const int &lep1_pdgid() { return samesignbtag.lep1_pdgid(); }
	const int &lep1_type() { return samesignbtag.lep1_type(); }
	const float &lep1_d0() { return samesignbtag.lep1_d0(); }
	const float &lep1_d0err() { return samesignbtag.lep1_d0err(); }
	const float &lep1_dz() { return samesignbtag.lep1_dz(); }
	const float &lep1_ip3d() { return samesignbtag.lep1_ip3d(); }
	const float &lep1_ip3derr() { return samesignbtag.lep1_ip3derr(); }
	const float &lep1_dzerr() { return samesignbtag.lep1_dzerr(); }
	const float &lep1_mt() { return samesignbtag.lep1_mt(); }
	const float &lep1_corpfiso() { return samesignbtag.lep1_corpfiso(); }
	const float &lep1_pfiso() { return samesignbtag.lep1_pfiso(); }
	const float &lep1_chiso() { return samesignbtag.lep1_chiso(); }
	const float &lep1_emiso() { return samesignbtag.lep1_emiso(); }
	const float &lep1_nhiso() { return samesignbtag.lep1_nhiso(); }
	const float &lep1_corpfiso04() { return samesignbtag.lep1_corpfiso04(); }
	const float &lep1_pfiso04() { return samesignbtag.lep1_pfiso04(); }
	const float &lep1_chiso04() { return samesignbtag.lep1_chiso04(); }
	const float &lep1_emiso04() { return samesignbtag.lep1_emiso04(); }
	const float &lep1_nhiso04() { return samesignbtag.lep1_nhiso04(); }
	const float &lep1_cordetiso() { return samesignbtag.lep1_cordetiso(); }
	const float &lep1_detiso() { return samesignbtag.lep1_detiso(); }
	const float &lep1_trkiso() { return samesignbtag.lep1_trkiso(); }
	const float &lep1_ecaliso() { return samesignbtag.lep1_ecaliso(); }
	const float &lep1_hcaliso() { return samesignbtag.lep1_hcaliso(); }
	const float &lep1_cordetiso04() { return samesignbtag.lep1_cordetiso04(); }
	const float &lep1_detiso04() { return samesignbtag.lep1_detiso04(); }
	const float &lep1_trkiso04() { return samesignbtag.lep1_trkiso04(); }
	const float &lep1_ecaliso04() { return samesignbtag.lep1_ecaliso04(); }
	const float &lep1_hcaliso04() { return samesignbtag.lep1_hcaliso04(); }
	const float &lep1_effarea() { return samesignbtag.lep1_effarea(); }
	const float &lep1_effarea04() { return samesignbtag.lep1_effarea04(); }
	const float &lep1_dbeta() { return samesignbtag.lep1_dbeta(); }
	const float &lep1_dbeta04() { return samesignbtag.lep1_dbeta04(); }
	const float &lep1_sf_lepeff() { return samesignbtag.lep1_sf_lepeff(); }
	const float &lep1_sf_trig() { return samesignbtag.lep1_sf_trig(); }
	const int &lep1_mcid() { return samesignbtag.lep1_mcid(); }
	const int &lep1_mc3id() { return samesignbtag.lep1_mc3id(); }
	const int &lep1_momid() { return samesignbtag.lep1_momid(); }
	const int &lep1_mc3_momid() { return samesignbtag.lep1_mc3_momid(); }
	const bool &lep1_q3agree() { return samesignbtag.lep1_q3agree(); }
	const bool &lep1_is_conv() { return samesignbtag.lep1_is_conv(); }
	const int &lep1_qsc() { return samesignbtag.lep1_qsc(); }
	const int &lep1_qctf() { return samesignbtag.lep1_qctf(); }
	const int &lep1_qgsf() { return samesignbtag.lep1_qgsf(); }
	const int &lep1_nmhits() { return samesignbtag.lep1_nmhits(); }
	const int &lep1_eleid_veto() { return samesignbtag.lep1_eleid_veto(); }
	const int &lep1_eleid_loose() { return samesignbtag.lep1_eleid_loose(); }
	const int &lep1_eleid_medium() { return samesignbtag.lep1_eleid_medium(); }
	const int &lep1_eleid_tight() { return samesignbtag.lep1_eleid_tight(); }
	const float &lep1_dphiin() { return samesignbtag.lep1_dphiin(); }
	const float &lep1_detain() { return samesignbtag.lep1_detain(); }
	const float &lep1_sieie() { return samesignbtag.lep1_sieie(); }
	const float &lep1_hoe() { return samesignbtag.lep1_hoe(); }
	const float &lep1_ooemoop() { return samesignbtag.lep1_ooemoop(); }
	const float &lep1_conv_dist() { return samesignbtag.lep1_conv_dist(); }
	const float &lep1_conv_dcot() { return samesignbtag.lep1_conv_dcot(); }
	const bool &lep1_is_global() { return samesignbtag.lep1_is_global(); }
	const bool &lep1_is_tracker() { return samesignbtag.lep1_is_tracker(); }
	const bool &lep1_is_stamu() { return samesignbtag.lep1_is_stamu(); }
	const bool &lep1_is_pfmu() { return samesignbtag.lep1_is_pfmu(); }
	const bool &lep1_is_loosemu() { return samesignbtag.lep1_is_loosemu(); }
	const bool &lep1_is_tightmu() { return samesignbtag.lep1_is_tightmu(); }
	const int &lep1_npixelhits() { return samesignbtag.lep1_npixelhits(); }
	const int &lep1_nsihits() { return samesignbtag.lep1_nsihits(); }
	const int &lep1_nsilayers() { return samesignbtag.lep1_nsilayers(); }
	const int &lep1_nstahits() { return samesignbtag.lep1_nstahits(); }
	const int &lep1_nstations() { return samesignbtag.lep1_nstations(); }
	const float &lep1_chi2() { return samesignbtag.lep1_chi2(); }
	const float &lep1_ndof() { return samesignbtag.lep1_ndof(); }
	const float &lep1_pterr() { return samesignbtag.lep1_pterr(); }
	const float &lep1_ecal_vetodep() { return samesignbtag.lep1_ecal_vetodep(); }
	const float &lep1_hcal_vetodep() { return samesignbtag.lep1_hcal_vetodep(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_p4() { return samesignbtag.lep1_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mcp4() { return samesignbtag.lep1_mcp4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mc3p4() { return samesignbtag.lep1_mc3p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mc_momp4() { return samesignbtag.lep1_mc_momp4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_gsf_p4() { return samesignbtag.lep1_gsf_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_ctf_p4() { return samesignbtag.lep1_ctf_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_sc_p4() { return samesignbtag.lep1_sc_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_gfit_p4() { return samesignbtag.lep1_gfit_p4(); }
	const bool &lep2_passes_id() { return samesignbtag.lep2_passes_id(); }
	const bool &lep2_passes_iso() { return samesignbtag.lep2_passes_iso(); }
	const bool &lep2_is_num() { return samesignbtag.lep2_is_num(); }
	const bool &lep2_is_den() { return samesignbtag.lep2_is_den(); }
	const bool &lep2_is_fo() { return samesignbtag.lep2_is_fo(); }
	const int &lep2_is_fromw() { return samesignbtag.lep2_is_fromw(); }
	const int &lep2_charge() { return samesignbtag.lep2_charge(); }
	const int &lep2_pdgid() { return samesignbtag.lep2_pdgid(); }
	const int &lep2_type() { return samesignbtag.lep2_type(); }
	const float &lep2_d0() { return samesignbtag.lep2_d0(); }
	const float &lep2_d0err() { return samesignbtag.lep2_d0err(); }
	const float &lep2_dz() { return samesignbtag.lep2_dz(); }
	const float &lep2_ip3d() { return samesignbtag.lep2_ip3d(); }
	const float &lep2_ip3derr() { return samesignbtag.lep2_ip3derr(); }
	const float &lep2_dzerr() { return samesignbtag.lep2_dzerr(); }
	const float &lep2_mt() { return samesignbtag.lep2_mt(); }
	const float &lep2_corpfiso() { return samesignbtag.lep2_corpfiso(); }
	const float &lep2_pfiso() { return samesignbtag.lep2_pfiso(); }
	const float &lep2_chiso() { return samesignbtag.lep2_chiso(); }
	const float &lep2_emiso() { return samesignbtag.lep2_emiso(); }
	const float &lep2_nhiso() { return samesignbtag.lep2_nhiso(); }
	const float &lep2_corpfiso04() { return samesignbtag.lep2_corpfiso04(); }
	const float &lep2_pfiso04() { return samesignbtag.lep2_pfiso04(); }
	const float &lep2_chiso04() { return samesignbtag.lep2_chiso04(); }
	const float &lep2_emiso04() { return samesignbtag.lep2_emiso04(); }
	const float &lep2_nhiso04() { return samesignbtag.lep2_nhiso04(); }
	const float &lep2_cordetiso() { return samesignbtag.lep2_cordetiso(); }
	const float &lep2_detiso() { return samesignbtag.lep2_detiso(); }
	const float &lep2_trkiso() { return samesignbtag.lep2_trkiso(); }
	const float &lep2_ecaliso() { return samesignbtag.lep2_ecaliso(); }
	const float &lep2_hcaliso() { return samesignbtag.lep2_hcaliso(); }
	const float &lep2_cordetiso04() { return samesignbtag.lep2_cordetiso04(); }
	const float &lep2_detiso04() { return samesignbtag.lep2_detiso04(); }
	const float &lep2_trkiso04() { return samesignbtag.lep2_trkiso04(); }
	const float &lep2_ecaliso04() { return samesignbtag.lep2_ecaliso04(); }
	const float &lep2_hcaliso04() { return samesignbtag.lep2_hcaliso04(); }
	const float &lep2_effarea() { return samesignbtag.lep2_effarea(); }
	const float &lep2_effarea04() { return samesignbtag.lep2_effarea04(); }
	const float &lep2_dbeta() { return samesignbtag.lep2_dbeta(); }
	const float &lep2_dbeta04() { return samesignbtag.lep2_dbeta04(); }
	const float &lep2_sf_lepeff() { return samesignbtag.lep2_sf_lepeff(); }
	const float &lep2_sf_trig() { return samesignbtag.lep2_sf_trig(); }
	const int &lep2_mcid() { return samesignbtag.lep2_mcid(); }
	const int &lep2_mc3id() { return samesignbtag.lep2_mc3id(); }
	const int &lep2_momid() { return samesignbtag.lep2_momid(); }
	const int &lep2_mc3_momid() { return samesignbtag.lep2_mc3_momid(); }
	const bool &lep2_q3agree() { return samesignbtag.lep2_q3agree(); }
	const bool &lep2_is_conv() { return samesignbtag.lep2_is_conv(); }
	const int &lep2_qsc() { return samesignbtag.lep2_qsc(); }
	const int &lep2_qctf() { return samesignbtag.lep2_qctf(); }
	const int &lep2_qgsf() { return samesignbtag.lep2_qgsf(); }
	const int &lep2_nmhits() { return samesignbtag.lep2_nmhits(); }
	const int &lep2_eleid_veto() { return samesignbtag.lep2_eleid_veto(); }
	const int &lep2_eleid_loose() { return samesignbtag.lep2_eleid_loose(); }
	const int &lep2_eleid_medium() { return samesignbtag.lep2_eleid_medium(); }
	const int &lep2_eleid_tight() { return samesignbtag.lep2_eleid_tight(); }
	const float &lep2_dphiin() { return samesignbtag.lep2_dphiin(); }
	const float &lep2_detain() { return samesignbtag.lep2_detain(); }
	const float &lep2_sieie() { return samesignbtag.lep2_sieie(); }
	const float &lep2_hoe() { return samesignbtag.lep2_hoe(); }
	const float &lep2_ooemoop() { return samesignbtag.lep2_ooemoop(); }
	const float &lep2_conv_dist() { return samesignbtag.lep2_conv_dist(); }
	const float &lep2_conv_dcot() { return samesignbtag.lep2_conv_dcot(); }
	const bool &lep2_is_global() { return samesignbtag.lep2_is_global(); }
	const bool &lep2_is_tracker() { return samesignbtag.lep2_is_tracker(); }
	const bool &lep2_is_stamu() { return samesignbtag.lep2_is_stamu(); }
	const bool &lep2_is_pfmu() { return samesignbtag.lep2_is_pfmu(); }
	const bool &lep2_is_loosemu() { return samesignbtag.lep2_is_loosemu(); }
	const bool &lep2_is_tightmu() { return samesignbtag.lep2_is_tightmu(); }
	const int &lep2_npixelhits() { return samesignbtag.lep2_npixelhits(); }
	const int &lep2_nsihits() { return samesignbtag.lep2_nsihits(); }
	const int &lep2_nsilayers() { return samesignbtag.lep2_nsilayers(); }
	const int &lep2_nstahits() { return samesignbtag.lep2_nstahits(); }
	const int &lep2_nstations() { return samesignbtag.lep2_nstations(); }
	const float &lep2_chi2() { return samesignbtag.lep2_chi2(); }
	const float &lep2_ndof() { return samesignbtag.lep2_ndof(); }
	const float &lep2_pterr() { return samesignbtag.lep2_pterr(); }
	const float &lep2_ecal_vetodep() { return samesignbtag.lep2_ecal_vetodep(); }
	const float &lep2_hcal_vetodep() { return samesignbtag.lep2_hcal_vetodep(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_p4() { return samesignbtag.lep2_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mcp4() { return samesignbtag.lep2_mcp4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mc3p4() { return samesignbtag.lep2_mc3p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mc_momp4() { return samesignbtag.lep2_mc_momp4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_gsf_p4() { return samesignbtag.lep2_gsf_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_ctf_p4() { return samesignbtag.lep2_ctf_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_sc_p4() { return samesignbtag.lep2_sc_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_gfit_p4() { return samesignbtag.lep2_gfit_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &dilep_p4() { return samesignbtag.dilep_p4(); }
	const bool &os() { return samesignbtag.os(); }
	const bool &ss() { return samesignbtag.ss(); }
	const bool &mm() { return samesignbtag.mm(); }
	const bool &ee() { return samesignbtag.ee(); }
	const bool &em() { return samesignbtag.em(); }
	const int &dilep_type() { return samesignbtag.dilep_type(); }
	const int &dilep_gen_type() { return samesignbtag.dilep_gen_type(); }
	const float &dilep_mass() { return samesignbtag.dilep_mass(); }
	const float &dilep_dphi() { return samesignbtag.dilep_dphi(); }
	const float &dilep_deta() { return samesignbtag.dilep_deta(); }
	const float &dilep_dr() { return samesignbtag.dilep_dr(); }
	const int &fiduciality() { return samesignbtag.fiduciality(); }
	const bool &lep3_passes_id() { return samesignbtag.lep3_passes_id(); }
	const bool &lep3_passes_iso() { return samesignbtag.lep3_passes_iso(); }
	const bool &lep3_is_num() { return samesignbtag.lep3_is_num(); }
	const bool &lep3_is_den() { return samesignbtag.lep3_is_den(); }
	const bool &lep3_is_fo() { return samesignbtag.lep3_is_fo(); }
	const int &lep3_is_fromw() { return samesignbtag.lep3_is_fromw(); }
	const int &lep3_charge() { return samesignbtag.lep3_charge(); }
	const int &lep3_pdgid() { return samesignbtag.lep3_pdgid(); }
	const int &lep3_type() { return samesignbtag.lep3_type(); }
	const float &lep3_d0() { return samesignbtag.lep3_d0(); }
	const float &lep3_d0err() { return samesignbtag.lep3_d0err(); }
	const float &lep3_dz() { return samesignbtag.lep3_dz(); }
	const float &lep3_ip3d() { return samesignbtag.lep3_ip3d(); }
	const float &lep3_ip3derr() { return samesignbtag.lep3_ip3derr(); }
	const float &lep3_dzerr() { return samesignbtag.lep3_dzerr(); }
	const float &lep3_mt() { return samesignbtag.lep3_mt(); }
	const float &lep3_corpfiso() { return samesignbtag.lep3_corpfiso(); }
	const float &lep3_pfiso() { return samesignbtag.lep3_pfiso(); }
	const float &lep3_chiso() { return samesignbtag.lep3_chiso(); }
	const float &lep3_emiso() { return samesignbtag.lep3_emiso(); }
	const float &lep3_nhiso() { return samesignbtag.lep3_nhiso(); }
	const float &lep3_corpfiso04() { return samesignbtag.lep3_corpfiso04(); }
	const float &lep3_pfiso04() { return samesignbtag.lep3_pfiso04(); }
	const float &lep3_chiso04() { return samesignbtag.lep3_chiso04(); }
	const float &lep3_emiso04() { return samesignbtag.lep3_emiso04(); }
	const float &lep3_nhiso04() { return samesignbtag.lep3_nhiso04(); }
	const float &lep3_cordetiso() { return samesignbtag.lep3_cordetiso(); }
	const float &lep3_detiso() { return samesignbtag.lep3_detiso(); }
	const float &lep3_trkiso() { return samesignbtag.lep3_trkiso(); }
	const float &lep3_ecaliso() { return samesignbtag.lep3_ecaliso(); }
	const float &lep3_hcaliso() { return samesignbtag.lep3_hcaliso(); }
	const float &lep3_cordetiso04() { return samesignbtag.lep3_cordetiso04(); }
	const float &lep3_detiso04() { return samesignbtag.lep3_detiso04(); }
	const float &lep3_trkiso04() { return samesignbtag.lep3_trkiso04(); }
	const float &lep3_ecaliso04() { return samesignbtag.lep3_ecaliso04(); }
	const float &lep3_hcaliso04() { return samesignbtag.lep3_hcaliso04(); }
	const float &lep3_effarea() { return samesignbtag.lep3_effarea(); }
	const float &lep3_effarea04() { return samesignbtag.lep3_effarea04(); }
	const float &lep3_dbeta() { return samesignbtag.lep3_dbeta(); }
	const float &lep3_dbeta04() { return samesignbtag.lep3_dbeta04(); }
	const float &lep3_sf_lepeff() { return samesignbtag.lep3_sf_lepeff(); }
	const float &lep3_sf_trig() { return samesignbtag.lep3_sf_trig(); }
	const int &lep3_mcid() { return samesignbtag.lep3_mcid(); }
	const int &lep3_mc3id() { return samesignbtag.lep3_mc3id(); }
	const int &lep3_momid() { return samesignbtag.lep3_momid(); }
	const int &lep3_mc3_momid() { return samesignbtag.lep3_mc3_momid(); }
	const bool &lep3_q3agree() { return samesignbtag.lep3_q3agree(); }
	const bool &lep3_is_conv() { return samesignbtag.lep3_is_conv(); }
	const int &lep3_qsc() { return samesignbtag.lep3_qsc(); }
	const int &lep3_qctf() { return samesignbtag.lep3_qctf(); }
	const int &lep3_qgsf() { return samesignbtag.lep3_qgsf(); }
	const int &lep3_nmhits() { return samesignbtag.lep3_nmhits(); }
	const int &lep3_eleid_veto() { return samesignbtag.lep3_eleid_veto(); }
	const int &lep3_eleid_loose() { return samesignbtag.lep3_eleid_loose(); }
	const int &lep3_eleid_medium() { return samesignbtag.lep3_eleid_medium(); }
	const int &lep3_eleid_tight() { return samesignbtag.lep3_eleid_tight(); }
	const float &lep3_dphiin() { return samesignbtag.lep3_dphiin(); }
	const float &lep3_detain() { return samesignbtag.lep3_detain(); }
	const float &lep3_sieie() { return samesignbtag.lep3_sieie(); }
	const float &lep3_hoe() { return samesignbtag.lep3_hoe(); }
	const float &lep3_ooemoop() { return samesignbtag.lep3_ooemoop(); }
	const float &lep3_conv_dist() { return samesignbtag.lep3_conv_dist(); }
	const float &lep3_conv_dcot() { return samesignbtag.lep3_conv_dcot(); }
	const bool &lep3_is_global() { return samesignbtag.lep3_is_global(); }
	const bool &lep3_is_tracker() { return samesignbtag.lep3_is_tracker(); }
	const bool &lep3_is_stamu() { return samesignbtag.lep3_is_stamu(); }
	const bool &lep3_is_pfmu() { return samesignbtag.lep3_is_pfmu(); }
	const bool &lep3_is_loosemu() { return samesignbtag.lep3_is_loosemu(); }
	const bool &lep3_is_tightmu() { return samesignbtag.lep3_is_tightmu(); }
	const int &lep3_npixelhits() { return samesignbtag.lep3_npixelhits(); }
	const int &lep3_nsihits() { return samesignbtag.lep3_nsihits(); }
	const int &lep3_nsilayers() { return samesignbtag.lep3_nsilayers(); }
	const int &lep3_nstahits() { return samesignbtag.lep3_nstahits(); }
	const int &lep3_nstations() { return samesignbtag.lep3_nstations(); }
	const float &lep3_chi2() { return samesignbtag.lep3_chi2(); }
	const float &lep3_ndof() { return samesignbtag.lep3_ndof(); }
	const float &lep3_pterr() { return samesignbtag.lep3_pterr(); }
	const float &lep3_ecal_vetodep() { return samesignbtag.lep3_ecal_vetodep(); }
	const float &lep3_hcal_vetodep() { return samesignbtag.lep3_hcal_vetodep(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_p4() { return samesignbtag.lep3_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_mcp4() { return samesignbtag.lep3_mcp4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_mc3p4() { return samesignbtag.lep3_mc3p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_mc_momp4() { return samesignbtag.lep3_mc_momp4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_gsf_p4() { return samesignbtag.lep3_gsf_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_ctf_p4() { return samesignbtag.lep3_ctf_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_sc_p4() { return samesignbtag.lep3_sc_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_gfit_p4() { return samesignbtag.lep3_gfit_p4(); }
	const unsigned int &selection() { return samesignbtag.selection(); }
	const bool &is_good_lumi() { return samesignbtag.is_good_lumi(); }
	const int &charge_type() { return samesignbtag.charge_type(); }
	const int &njets() { return samesignbtag.njets(); }
	const int &njets20() { return samesignbtag.njets20(); }
	const int &njets30() { return samesignbtag.njets30(); }
	const int &nbtags() { return samesignbtag.nbtags(); }
	const int &nbtags20() { return samesignbtag.nbtags20(); }
	const int &nbtags30() { return samesignbtag.nbtags30(); }
	const int &nbtags_csvl() { return samesignbtag.nbtags_csvl(); }
	const int &ttbar_bkdn() { return samesignbtag.ttbar_bkdn(); }
	const int &higgs_bkdn() { return samesignbtag.higgs_bkdn(); }
	const int &higgs_decay() { return samesignbtag.higgs_decay(); }
	const float &vtxw() { return samesignbtag.vtxw(); }
	const float &mt() { return samesignbtag.mt(); }
	const float &ht() { return samesignbtag.ht(); }
	const float &ht20() { return samesignbtag.ht20(); }
	const float &ht30() { return samesignbtag.ht30(); }
	const float &rho() { return samesignbtag.rho(); }
	const float &rho_iso() { return samesignbtag.rho_iso(); }
	const bool &trig_mm() { return samesignbtag.trig_mm(); }
	const bool &trig_em() { return samesignbtag.trig_em(); }
	const bool &trig_ee() { return samesignbtag.trig_ee(); }
	const bool &trig_hpt() { return samesignbtag.trig_hpt(); }
	const bool &trig_lpt() { return samesignbtag.trig_lpt(); }
	const bool &trig_lpt_isomu() { return samesignbtag.trig_lpt_isomu(); }
	const bool &trig_mm_mu17_mu8() { return samesignbtag.trig_mm_mu17_mu8(); }
	const bool &trig_mm_dmu8_m8_pfht175() { return samesignbtag.trig_mm_dmu8_m8_pfht175(); }
	const bool &trig_mm_dmu8_m8_pfnopuht175() { return samesignbtag.trig_mm_dmu8_m8_pfnopuht175(); }
	const bool &trig_mm_dreliso1p0mu5_m8_pfht175() { return samesignbtag.trig_mm_dreliso1p0mu5_m8_pfht175(); }
	const bool &trig_mm_dreliso1p0mu5_m8_pfnopuht175() { return samesignbtag.trig_mm_dreliso1p0mu5_m8_pfnopuht175(); }
	const bool &trig_ee_el17_el8_id_iso() { return samesignbtag.trig_ee_el17_el8_id_iso(); }
	const bool &trig_ee_del8_id_m8_pfht175() { return samesignbtag.trig_ee_del8_id_m8_pfht175(); }
	const bool &trig_ee_del8_id_m8_pfnopuht175() { return samesignbtag.trig_ee_del8_id_m8_pfnopuht175(); }
	const bool &trig_em_mu17_el8_id_iso() { return samesignbtag.trig_em_mu17_el8_id_iso(); }
	const bool &trig_em_mu8_el17_id_iso() { return samesignbtag.trig_em_mu8_el17_id_iso(); }
	const bool &trig_em_mu8_el8_id_m8_pfht175() { return samesignbtag.trig_em_mu8_el8_id_m8_pfht175(); }
	const bool &trig_em_mu8_el8_id_m8_pfnopuht175() { return samesignbtag.trig_em_mu8_el8_id_m8_pfnopuht175(); }
	const bool &trig_em_riso1p0mu5_el8_id_m8_pfht175() { return samesignbtag.trig_em_riso1p0mu5_el8_id_m8_pfht175(); }
	const bool &trig_em_riso1p0mu5_el8_id_m8_pfnopuht175() { return samesignbtag.trig_em_riso1p0mu5_el8_id_m8_pfnopuht175(); }
	const int &njets_dn() { return samesignbtag.njets_dn(); }
	const int &njets_up() { return samesignbtag.njets_up(); }
	const int &njets_jer() { return samesignbtag.njets_jer(); }
	const int &nbtags_dn() { return samesignbtag.nbtags_dn(); }
	const int &nbtags_up() { return samesignbtag.nbtags_up(); }
	const int &nbtags_jer() { return samesignbtag.nbtags_jer(); }
	const float &ht_dn() { return samesignbtag.ht_dn(); }
	const float &ht_up() { return samesignbtag.ht_up(); }
	const float &ht_jer() { return samesignbtag.ht_jer(); }
	const int &njets20_dn() { return samesignbtag.njets20_dn(); }
	const int &njets20_up() { return samesignbtag.njets20_up(); }
	const int &nbtags20_dn() { return samesignbtag.nbtags20_dn(); }
	const int &nbtags20_up() { return samesignbtag.nbtags20_up(); }
	const float &ht20_dn() { return samesignbtag.ht20_dn(); }
	const float &ht20_up() { return samesignbtag.ht20_up(); }
	const int &njets30_dn() { return samesignbtag.njets30_dn(); }
	const int &njets30_up() { return samesignbtag.njets30_up(); }
	const int &nbtags30_dn() { return samesignbtag.nbtags30_dn(); }
	const int &nbtags30_up() { return samesignbtag.nbtags30_up(); }
	const int &nbtags_reweighted() { return samesignbtag.nbtags_reweighted(); }
	const int &nbtags_reweighted_dn() { return samesignbtag.nbtags_reweighted_dn(); }
	const int &nbtags_reweighted_up() { return samesignbtag.nbtags_reweighted_up(); }
	const int &nbtags_reweighted_jec_dn() { return samesignbtag.nbtags_reweighted_jec_dn(); }
	const int &nbtags_reweighted_jec_up() { return samesignbtag.nbtags_reweighted_jec_up(); }
	const int &nbtags_reweighted_jer() { return samesignbtag.nbtags_reweighted_jer(); }
	const float &ht30_dn() { return samesignbtag.ht30_dn(); }
	const float &ht30_up() { return samesignbtag.ht30_up(); }
	const float &pfmet_dn() { return samesignbtag.pfmet_dn(); }
	const float &pfmet_up() { return samesignbtag.pfmet_up(); }
	const float &pfmet_phi_dn() { return samesignbtag.pfmet_phi_dn(); }
	const float &pfmet_phi_up() { return samesignbtag.pfmet_phi_up(); }
	const float &pfmet_jer() { return samesignbtag.pfmet_jer(); }
	const float &pfmet_jer_phi() { return samesignbtag.pfmet_jer_phi(); }
	const float &pfmet_uncl_dn() { return samesignbtag.pfmet_uncl_dn(); }
	const float &pfmet_uncl_up() { return samesignbtag.pfmet_uncl_up(); }
	const float &sf_dileptrig() { return samesignbtag.sf_dileptrig(); }
	const float &sf_dileptrig_hpt() { return samesignbtag.sf_dileptrig_hpt(); }
	const float &sf_dileptrig_lpt() { return samesignbtag.sf_dileptrig_lpt(); }
	const float &sf_dileptrig_vpt() { return samesignbtag.sf_dileptrig_vpt(); }
	const float &sf_dilepeff() { return samesignbtag.sf_dilepeff(); }
	const float &sparm0() { return samesignbtag.sparm0(); }
	const float &sparm1() { return samesignbtag.sparm1(); }
	const float &sparm2() { return samesignbtag.sparm2(); }
	const float &sparm3() { return samesignbtag.sparm3(); }
	const TString &sparm0_name() { return samesignbtag.sparm0_name(); }
	const TString &sparm1_name() { return samesignbtag.sparm1_name(); }
	const TString &sparm2_name() { return samesignbtag.sparm2_name(); }
	const TString &sparm3_name() { return samesignbtag.sparm3_name(); }
	const bool &is_pp() { return samesignbtag.is_pp(); }
	const bool &is_mm() { return samesignbtag.is_mm(); }
	const bool &is_ss() { return samesignbtag.is_ss(); }
	const bool &is_sf() { return samesignbtag.is_sf(); }
	const bool &is_df() { return samesignbtag.is_df(); }
	const bool &is_os() { return samesignbtag.is_os(); }
	const bool &no_extraz() { return samesignbtag.no_extraz(); }
	const bool &no_extrag() { return samesignbtag.no_extrag(); }
	const bool &clean() { return samesignbtag.clean(); }
	const bool &presel() { return samesignbtag.presel(); }
	const bool &em_mufo() { return samesignbtag.em_mufo(); }
	const bool &em_elfo() { return samesignbtag.em_elfo(); }
	const bool &hyp_good_vtx() { return samesignbtag.hyp_good_vtx(); }
	const bool &is_gen_pp() { return samesignbtag.is_gen_pp(); }
	const bool &is_gen_mm() { return samesignbtag.is_gen_mm(); }
	const int &gen_nbtags() { return samesignbtag.gen_nbtags(); }
	const int &gen_njets() { return samesignbtag.gen_njets(); }
	const float &gen_ht() { return samesignbtag.gen_ht(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearbjet_p4() { return samesignbtag.lep1_nearbjet_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearjet_p4() { return samesignbtag.lep1_nearjet_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearlep_p4() { return samesignbtag.lep1_nearlep_p4(); }
	const float &lep1_wfr() { return samesignbtag.lep1_wfr(); }
	const float &lep1_wflip() { return samesignbtag.lep1_wflip(); }
	const float &lep1_nearbjet_dr() { return samesignbtag.lep1_nearbjet_dr(); }
	const float &lep1_nearjet_dr() { return samesignbtag.lep1_nearjet_dr(); }
	const float &lep1_nearlep_dr() { return samesignbtag.lep1_nearlep_dr(); }
	const int &lep1_nearlep_id() { return samesignbtag.lep1_nearlep_id(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearbjet_p4() { return samesignbtag.lep2_nearbjet_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearjet_p4() { return samesignbtag.lep2_nearjet_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearlep_p4() { return samesignbtag.lep2_nearlep_p4(); }
	const float &lep2_wfr() { return samesignbtag.lep2_wfr(); }
	const float &lep2_wflip() { return samesignbtag.lep2_wflip(); }
	const float &lep2_nearbjet_dr() { return samesignbtag.lep2_nearbjet_dr(); }
	const float &lep2_nearjet_dr() { return samesignbtag.lep2_nearjet_dr(); }
	const float &lep2_nearlep_dr() { return samesignbtag.lep2_nearlep_dr(); }
	const int &lep2_nearlep_id() { return samesignbtag.lep2_nearlep_id(); }
	const float &sf_nbtag() { return samesignbtag.sf_nbtag(); }
	const float &sf_nbtag3() { return samesignbtag.sf_nbtag3(); }
	const float &sf_unc_nbtag() { return samesignbtag.sf_unc_nbtag(); }
	const float &sf_unc_nbtag3() { return samesignbtag.sf_unc_nbtag3(); }
	const float &jets_dr12() { return samesignbtag.jets_dr12(); }
	const float &bjets_dr12() { return samesignbtag.bjets_dr12(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vgenb_p4() { return samesignbtag.vgenb_p4(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_p4() { return samesignbtag.vjets_p4(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_p4_up() { return samesignbtag.vjets_p4_up(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_p4_dn() { return samesignbtag.vjets_p4_dn(); }
	const vector<bool> &vjets_btagged() { return samesignbtag.vjets_btagged(); }
	const vector<bool> &vjets_btagged_up() { return samesignbtag.vjets_btagged_up(); }
	const vector<bool> &vjets_btagged_dn() { return samesignbtag.vjets_btagged_dn(); }
	const vector<int> &vjets_mcflavor_phys() { return samesignbtag.vjets_mcflavor_phys(); }
	const vector<int> &vjets_mcflavor_algo() { return samesignbtag.vjets_mcflavor_algo(); }
	const vector<int> &vjets_mcflavor_phys_up() { return samesignbtag.vjets_mcflavor_phys_up(); }
	const vector<int> &vjets_mcflavor_algo_up() { return samesignbtag.vjets_mcflavor_algo_up(); }
	const vector<int> &vjets_mcflavor_phys_dn() { return samesignbtag.vjets_mcflavor_phys_dn(); }
	const vector<int> &vjets_mcflavor_algo_dn() { return samesignbtag.vjets_mcflavor_algo_dn(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_mc3p4() { return samesignbtag.vjets_mc3p4(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vgenjets_p4() { return samesignbtag.vgenjets_p4(); }
	const vector<int> &vjets_mc3id() { return samesignbtag.vjets_mc3id(); }
	const vector<int> &vjets_momid() { return samesignbtag.vjets_momid(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_nearjet_p4() { return samesignbtag.vjets_nearjet_p4(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vbjets_p4() { return samesignbtag.vbjets_p4(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vbjets_p4_up() { return samesignbtag.vbjets_p4_up(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vbjets_p4_dn() { return samesignbtag.vbjets_p4_dn(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vbjets_mc3p4() { return samesignbtag.vbjets_mc3p4(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vbjets_nearjet_p4() { return samesignbtag.vbjets_nearjet_p4(); }
	const vector<float> &vbjets_nearjet_dr() { return samesignbtag.vbjets_nearjet_dr(); }
	const vector<int> &vbjets_mc3id() { return samesignbtag.vbjets_mc3id(); }
	const vector<int> &vbjets_momid() { return samesignbtag.vbjets_momid(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep1_p4() { return samesignbtag.gen_lep1_p4(); }
	const int &gen_lep1_pdgid() { return samesignbtag.gen_lep1_pdgid(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep2_p4() { return samesignbtag.gen_lep2_p4(); }
	const int &gen_lep2_pdgid() { return samesignbtag.gen_lep2_pdgid(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_dilep_p4() { return samesignbtag.gen_dilep_p4(); }
	const int &gen_dilep_type() { return samesignbtag.gen_dilep_type(); }
	const float &gen_dilep_mass() { return samesignbtag.gen_dilep_mass(); }
	const float &gen_dilep_dphi() { return samesignbtag.gen_dilep_dphi(); }
	const float &gen_dilep_deta() { return samesignbtag.gen_dilep_deta(); }
	const float &gen_dilep_dr() { return samesignbtag.gen_dilep_dr(); }
	const float &lep3_wfr() { return samesignbtag.lep3_wfr(); }
	const float &lep3_wflip() { return samesignbtag.lep3_wflip(); }
	const int &pfTau15_leadPtcandID() { return samesignbtag.pfTau15_leadPtcandID(); }
	const int &pfTau_leadPtcandID() { return samesignbtag.pfTau_leadPtcandID(); }
	const int &pfTauLoose_leadPtcandID() { return samesignbtag.pfTauLoose_leadPtcandID(); }
	const bool &passes_tau_veto() { return samesignbtag.passes_tau_veto(); }
	const bool &passes_isotrk_veto() { return samesignbtag.passes_isotrk_veto(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTau15() { return samesignbtag.pfTau15(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTau15_leadPtcand() { return samesignbtag.pfTau15_leadPtcand(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTau() { return samesignbtag.pfTau(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTau_leadPtcand() { return samesignbtag.pfTau_leadPtcand(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTauLoose() { return samesignbtag.pfTauLoose(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTauLoose_leadPtcand() { return samesignbtag.pfTauLoose_leadPtcand(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &mu_muid_loose_p4() { return samesignbtag.mu_muid_loose_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &mu_muid_tight_p4() { return samesignbtag.mu_muid_tight_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &mu_muid_ssv5_p4() { return samesignbtag.mu_muid_ssv5_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &el_elid_loose_p4() { return samesignbtag.el_elid_loose_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &el_elid_medium_p4() { return samesignbtag.el_elid_medium_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &el_elid_ssv7_p4() { return samesignbtag.el_elid_ssv7_p4(); }
}
