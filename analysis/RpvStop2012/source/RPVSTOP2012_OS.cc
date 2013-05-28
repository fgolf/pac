#include "RPVSTOP2012_OS.h"
RPVSTOP2012_OS rpvstop12os;
namespace rpvstop_os {
	const unsigned int &run() { return rpvstop12os.run(); }
	const unsigned int &ls() { return rpvstop12os.ls(); }
	const unsigned int &evt() { return rpvstop12os.evt(); }
	const bool &is_real_data() { return rpvstop12os.is_real_data(); }
	const int &sample() { return rpvstop12os.sample(); }
	const int &nvtxs() { return rpvstop12os.nvtxs(); }
	const int &vtx_idx() { return rpvstop12os.vtx_idx(); }
	const float &pfmet() { return rpvstop12os.pfmet(); }
	const float &pfmet_phi() { return rpvstop12os.pfmet_phi(); }
	const float &uncorpfmet() { return rpvstop12os.uncorpfmet(); }
	const float &uncorpfmet_phi() { return rpvstop12os.uncorpfmet_phi(); }
	const float &pu_nvtxs() { return rpvstop12os.pu_nvtxs(); }
	const float &pu_ntrueint() { return rpvstop12os.pu_ntrueint(); }
	const float &kfactor() { return rpvstop12os.kfactor(); }
	const float &gen_met() { return rpvstop12os.gen_met(); }
	const float &gen_met_phi() { return rpvstop12os.gen_met_phi(); }
	const TString &dataset() { return rpvstop12os.dataset(); }
	const TString &filename() { return rpvstop12os.filename(); }
	const int &gen_nleps() { return rpvstop12os.gen_nleps(); }
	const int &gen_nels() { return rpvstop12os.gen_nels(); }
	const int &gen_nmus() { return rpvstop12os.gen_nmus(); }
	const int &gen_ntaus() { return rpvstop12os.gen_ntaus(); }
	const int &gen_nleps_with_fromtau() { return rpvstop12os.gen_nleps_with_fromtau(); }
	const int &gen_nels_with_fromtau() { return rpvstop12os.gen_nels_with_fromtau(); }
	const int &gen_nmus_with_fromtau() { return rpvstop12os.gen_nmus_with_fromtau(); }
	const int &gen_ntaus_with_fromtau() { return rpvstop12os.gen_ntaus_with_fromtau(); }
	const bool &filt_csc() { return rpvstop12os.filt_csc(); }
	const bool &filt_hbhe() { return rpvstop12os.filt_hbhe(); }
	const bool &filt_hcallaser() { return rpvstop12os.filt_hcallaser(); }
	const bool &filt_ecallaser() { return rpvstop12os.filt_ecallaser(); }
	const bool &filt_ecaltp() { return rpvstop12os.filt_ecaltp(); }
	const bool &filt_trkfail() { return rpvstop12os.filt_trkfail(); }
	const bool &filt_eebadsc() { return rpvstop12os.filt_eebadsc(); }
	const bool &passes_metfilters() { return rpvstop12os.passes_metfilters(); }
	const bool &lep1_passes_id() { return rpvstop12os.lep1_passes_id(); }
	const bool &lep1_passes_iso() { return rpvstop12os.lep1_passes_iso(); }
	const bool &lep1_is_num() { return rpvstop12os.lep1_is_num(); }
	const bool &lep1_is_den() { return rpvstop12os.lep1_is_den(); }
	const bool &lep1_is_fo() { return rpvstop12os.lep1_is_fo(); }
	const int &lep1_is_fromw() { return rpvstop12os.lep1_is_fromw(); }
	const int &lep1_charge() { return rpvstop12os.lep1_charge(); }
	const int &lep1_pdgid() { return rpvstop12os.lep1_pdgid(); }
	const int &lep1_type() { return rpvstop12os.lep1_type(); }
	const float &lep1_d0() { return rpvstop12os.lep1_d0(); }
	const float &lep1_d0err() { return rpvstop12os.lep1_d0err(); }
	const float &lep1_dz() { return rpvstop12os.lep1_dz(); }
	const float &lep1_ip3d() { return rpvstop12os.lep1_ip3d(); }
	const float &lep1_ip3derr() { return rpvstop12os.lep1_ip3derr(); }
	const float &lep1_dzerr() { return rpvstop12os.lep1_dzerr(); }
	const float &lep1_mt() { return rpvstop12os.lep1_mt(); }
	const float &lep1_corpfiso() { return rpvstop12os.lep1_corpfiso(); }
	const float &lep1_pfiso() { return rpvstop12os.lep1_pfiso(); }
	const float &lep1_chiso() { return rpvstop12os.lep1_chiso(); }
	const float &lep1_emiso() { return rpvstop12os.lep1_emiso(); }
	const float &lep1_nhiso() { return rpvstop12os.lep1_nhiso(); }
	const float &lep1_corpfiso04() { return rpvstop12os.lep1_corpfiso04(); }
	const float &lep1_pfiso04() { return rpvstop12os.lep1_pfiso04(); }
	const float &lep1_chiso04() { return rpvstop12os.lep1_chiso04(); }
	const float &lep1_emiso04() { return rpvstop12os.lep1_emiso04(); }
	const float &lep1_nhiso04() { return rpvstop12os.lep1_nhiso04(); }
	const float &lep1_cordetiso() { return rpvstop12os.lep1_cordetiso(); }
	const float &lep1_detiso() { return rpvstop12os.lep1_detiso(); }
	const float &lep1_trkiso() { return rpvstop12os.lep1_trkiso(); }
	const float &lep1_ecaliso() { return rpvstop12os.lep1_ecaliso(); }
	const float &lep1_hcaliso() { return rpvstop12os.lep1_hcaliso(); }
	const float &lep1_cordetiso04() { return rpvstop12os.lep1_cordetiso04(); }
	const float &lep1_detiso04() { return rpvstop12os.lep1_detiso04(); }
	const float &lep1_trkiso04() { return rpvstop12os.lep1_trkiso04(); }
	const float &lep1_ecaliso04() { return rpvstop12os.lep1_ecaliso04(); }
	const float &lep1_hcaliso04() { return rpvstop12os.lep1_hcaliso04(); }
	const float &lep1_effarea() { return rpvstop12os.lep1_effarea(); }
	const float &lep1_effarea04() { return rpvstop12os.lep1_effarea04(); }
	const float &lep1_dbeta() { return rpvstop12os.lep1_dbeta(); }
	const float &lep1_dbeta04() { return rpvstop12os.lep1_dbeta04(); }
	const float &lep1_sf_lepeff() { return rpvstop12os.lep1_sf_lepeff(); }
	const float &lep1_sf_trig() { return rpvstop12os.lep1_sf_trig(); }
	const int &lep1_mcid() { return rpvstop12os.lep1_mcid(); }
	const int &lep1_mc3id() { return rpvstop12os.lep1_mc3id(); }
	const int &lep1_momid() { return rpvstop12os.lep1_momid(); }
	const int &lep1_mc3_momid() { return rpvstop12os.lep1_mc3_momid(); }
	const bool &lep1_q3agree() { return rpvstop12os.lep1_q3agree(); }
	const bool &lep1_is_conv() { return rpvstop12os.lep1_is_conv(); }
	const int &lep1_qsc() { return rpvstop12os.lep1_qsc(); }
	const int &lep1_qctf() { return rpvstop12os.lep1_qctf(); }
	const int &lep1_qgsf() { return rpvstop12os.lep1_qgsf(); }
	const int &lep1_nmhits() { return rpvstop12os.lep1_nmhits(); }
	const int &lep1_eleid_veto() { return rpvstop12os.lep1_eleid_veto(); }
	const int &lep1_eleid_loose() { return rpvstop12os.lep1_eleid_loose(); }
	const int &lep1_eleid_medium() { return rpvstop12os.lep1_eleid_medium(); }
	const int &lep1_eleid_tight() { return rpvstop12os.lep1_eleid_tight(); }
	const float &lep1_dphiin() { return rpvstop12os.lep1_dphiin(); }
	const float &lep1_detain() { return rpvstop12os.lep1_detain(); }
	const float &lep1_sieie() { return rpvstop12os.lep1_sieie(); }
	const float &lep1_hoe() { return rpvstop12os.lep1_hoe(); }
	const float &lep1_ooemoop() { return rpvstop12os.lep1_ooemoop(); }
	const float &lep1_conv_dist() { return rpvstop12os.lep1_conv_dist(); }
	const float &lep1_conv_dcot() { return rpvstop12os.lep1_conv_dcot(); }
	const bool &lep1_is_global() { return rpvstop12os.lep1_is_global(); }
	const bool &lep1_is_tracker() { return rpvstop12os.lep1_is_tracker(); }
	const bool &lep1_is_stamu() { return rpvstop12os.lep1_is_stamu(); }
	const bool &lep1_is_pfmu() { return rpvstop12os.lep1_is_pfmu(); }
	const bool &lep1_is_loosemu() { return rpvstop12os.lep1_is_loosemu(); }
	const bool &lep1_is_tightmu() { return rpvstop12os.lep1_is_tightmu(); }
	const int &lep1_npixelhits() { return rpvstop12os.lep1_npixelhits(); }
	const int &lep1_nsihits() { return rpvstop12os.lep1_nsihits(); }
	const int &lep1_nsilayers() { return rpvstop12os.lep1_nsilayers(); }
	const int &lep1_nstahits() { return rpvstop12os.lep1_nstahits(); }
	const int &lep1_nstations() { return rpvstop12os.lep1_nstations(); }
	const float &lep1_chi2() { return rpvstop12os.lep1_chi2(); }
	const float &lep1_ndof() { return rpvstop12os.lep1_ndof(); }
	const float &lep1_pterr() { return rpvstop12os.lep1_pterr(); }
	const float &lep1_ecal_vetodep() { return rpvstop12os.lep1_ecal_vetodep(); }
	const float &lep1_hcal_vetodep() { return rpvstop12os.lep1_hcal_vetodep(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_p4() { return rpvstop12os.lep1_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mcp4() { return rpvstop12os.lep1_mcp4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mc3p4() { return rpvstop12os.lep1_mc3p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mc_momp4() { return rpvstop12os.lep1_mc_momp4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_gsf_p4() { return rpvstop12os.lep1_gsf_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_ctf_p4() { return rpvstop12os.lep1_ctf_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_sc_p4() { return rpvstop12os.lep1_sc_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_gfit_p4() { return rpvstop12os.lep1_gfit_p4(); }
	const bool &lep2_passes_id() { return rpvstop12os.lep2_passes_id(); }
	const bool &lep2_passes_iso() { return rpvstop12os.lep2_passes_iso(); }
	const bool &lep2_is_num() { return rpvstop12os.lep2_is_num(); }
	const bool &lep2_is_den() { return rpvstop12os.lep2_is_den(); }
	const bool &lep2_is_fo() { return rpvstop12os.lep2_is_fo(); }
	const int &lep2_is_fromw() { return rpvstop12os.lep2_is_fromw(); }
	const int &lep2_charge() { return rpvstop12os.lep2_charge(); }
	const int &lep2_pdgid() { return rpvstop12os.lep2_pdgid(); }
	const int &lep2_type() { return rpvstop12os.lep2_type(); }
	const float &lep2_d0() { return rpvstop12os.lep2_d0(); }
	const float &lep2_d0err() { return rpvstop12os.lep2_d0err(); }
	const float &lep2_dz() { return rpvstop12os.lep2_dz(); }
	const float &lep2_ip3d() { return rpvstop12os.lep2_ip3d(); }
	const float &lep2_ip3derr() { return rpvstop12os.lep2_ip3derr(); }
	const float &lep2_dzerr() { return rpvstop12os.lep2_dzerr(); }
	const float &lep2_mt() { return rpvstop12os.lep2_mt(); }
	const float &lep2_corpfiso() { return rpvstop12os.lep2_corpfiso(); }
	const float &lep2_pfiso() { return rpvstop12os.lep2_pfiso(); }
	const float &lep2_chiso() { return rpvstop12os.lep2_chiso(); }
	const float &lep2_emiso() { return rpvstop12os.lep2_emiso(); }
	const float &lep2_nhiso() { return rpvstop12os.lep2_nhiso(); }
	const float &lep2_corpfiso04() { return rpvstop12os.lep2_corpfiso04(); }
	const float &lep2_pfiso04() { return rpvstop12os.lep2_pfiso04(); }
	const float &lep2_chiso04() { return rpvstop12os.lep2_chiso04(); }
	const float &lep2_emiso04() { return rpvstop12os.lep2_emiso04(); }
	const float &lep2_nhiso04() { return rpvstop12os.lep2_nhiso04(); }
	const float &lep2_cordetiso() { return rpvstop12os.lep2_cordetiso(); }
	const float &lep2_detiso() { return rpvstop12os.lep2_detiso(); }
	const float &lep2_trkiso() { return rpvstop12os.lep2_trkiso(); }
	const float &lep2_ecaliso() { return rpvstop12os.lep2_ecaliso(); }
	const float &lep2_hcaliso() { return rpvstop12os.lep2_hcaliso(); }
	const float &lep2_cordetiso04() { return rpvstop12os.lep2_cordetiso04(); }
	const float &lep2_detiso04() { return rpvstop12os.lep2_detiso04(); }
	const float &lep2_trkiso04() { return rpvstop12os.lep2_trkiso04(); }
	const float &lep2_ecaliso04() { return rpvstop12os.lep2_ecaliso04(); }
	const float &lep2_hcaliso04() { return rpvstop12os.lep2_hcaliso04(); }
	const float &lep2_effarea() { return rpvstop12os.lep2_effarea(); }
	const float &lep2_effarea04() { return rpvstop12os.lep2_effarea04(); }
	const float &lep2_dbeta() { return rpvstop12os.lep2_dbeta(); }
	const float &lep2_dbeta04() { return rpvstop12os.lep2_dbeta04(); }
	const float &lep2_sf_lepeff() { return rpvstop12os.lep2_sf_lepeff(); }
	const float &lep2_sf_trig() { return rpvstop12os.lep2_sf_trig(); }
	const int &lep2_mcid() { return rpvstop12os.lep2_mcid(); }
	const int &lep2_mc3id() { return rpvstop12os.lep2_mc3id(); }
	const int &lep2_momid() { return rpvstop12os.lep2_momid(); }
	const int &lep2_mc3_momid() { return rpvstop12os.lep2_mc3_momid(); }
	const bool &lep2_q3agree() { return rpvstop12os.lep2_q3agree(); }
	const bool &lep2_is_conv() { return rpvstop12os.lep2_is_conv(); }
	const int &lep2_qsc() { return rpvstop12os.lep2_qsc(); }
	const int &lep2_qctf() { return rpvstop12os.lep2_qctf(); }
	const int &lep2_qgsf() { return rpvstop12os.lep2_qgsf(); }
	const int &lep2_nmhits() { return rpvstop12os.lep2_nmhits(); }
	const int &lep2_eleid_veto() { return rpvstop12os.lep2_eleid_veto(); }
	const int &lep2_eleid_loose() { return rpvstop12os.lep2_eleid_loose(); }
	const int &lep2_eleid_medium() { return rpvstop12os.lep2_eleid_medium(); }
	const int &lep2_eleid_tight() { return rpvstop12os.lep2_eleid_tight(); }
	const float &lep2_dphiin() { return rpvstop12os.lep2_dphiin(); }
	const float &lep2_detain() { return rpvstop12os.lep2_detain(); }
	const float &lep2_sieie() { return rpvstop12os.lep2_sieie(); }
	const float &lep2_hoe() { return rpvstop12os.lep2_hoe(); }
	const float &lep2_ooemoop() { return rpvstop12os.lep2_ooemoop(); }
	const float &lep2_conv_dist() { return rpvstop12os.lep2_conv_dist(); }
	const float &lep2_conv_dcot() { return rpvstop12os.lep2_conv_dcot(); }
	const bool &lep2_is_global() { return rpvstop12os.lep2_is_global(); }
	const bool &lep2_is_tracker() { return rpvstop12os.lep2_is_tracker(); }
	const bool &lep2_is_stamu() { return rpvstop12os.lep2_is_stamu(); }
	const bool &lep2_is_pfmu() { return rpvstop12os.lep2_is_pfmu(); }
	const bool &lep2_is_loosemu() { return rpvstop12os.lep2_is_loosemu(); }
	const bool &lep2_is_tightmu() { return rpvstop12os.lep2_is_tightmu(); }
	const int &lep2_npixelhits() { return rpvstop12os.lep2_npixelhits(); }
	const int &lep2_nsihits() { return rpvstop12os.lep2_nsihits(); }
	const int &lep2_nsilayers() { return rpvstop12os.lep2_nsilayers(); }
	const int &lep2_nstahits() { return rpvstop12os.lep2_nstahits(); }
	const int &lep2_nstations() { return rpvstop12os.lep2_nstations(); }
	const float &lep2_chi2() { return rpvstop12os.lep2_chi2(); }
	const float &lep2_ndof() { return rpvstop12os.lep2_ndof(); }
	const float &lep2_pterr() { return rpvstop12os.lep2_pterr(); }
	const float &lep2_ecal_vetodep() { return rpvstop12os.lep2_ecal_vetodep(); }
	const float &lep2_hcal_vetodep() { return rpvstop12os.lep2_hcal_vetodep(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_p4() { return rpvstop12os.lep2_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mcp4() { return rpvstop12os.lep2_mcp4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mc3p4() { return rpvstop12os.lep2_mc3p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mc_momp4() { return rpvstop12os.lep2_mc_momp4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_gsf_p4() { return rpvstop12os.lep2_gsf_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_ctf_p4() { return rpvstop12os.lep2_ctf_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_sc_p4() { return rpvstop12os.lep2_sc_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_gfit_p4() { return rpvstop12os.lep2_gfit_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &dilep_p4() { return rpvstop12os.dilep_p4(); }
	const bool &os() { return rpvstop12os.os(); }
	const bool &ss() { return rpvstop12os.ss(); }
	const bool &mm() { return rpvstop12os.mm(); }
	const bool &ee() { return rpvstop12os.ee(); }
	const bool &em() { return rpvstop12os.em(); }
	const int &dilep_type() { return rpvstop12os.dilep_type(); }
	const int &dilep_gen_type() { return rpvstop12os.dilep_gen_type(); }
	const float &dilep_mass() { return rpvstop12os.dilep_mass(); }
	const float &dilep_dphi() { return rpvstop12os.dilep_dphi(); }
	const float &dilep_deta() { return rpvstop12os.dilep_deta(); }
	const float &dilep_dr() { return rpvstop12os.dilep_dr(); }
	const int &fiduciality() { return rpvstop12os.fiduciality(); }
	const bool &lep3_passes_id() { return rpvstop12os.lep3_passes_id(); }
	const bool &lep3_passes_iso() { return rpvstop12os.lep3_passes_iso(); }
	const bool &lep3_is_num() { return rpvstop12os.lep3_is_num(); }
	const bool &lep3_is_den() { return rpvstop12os.lep3_is_den(); }
	const bool &lep3_is_fo() { return rpvstop12os.lep3_is_fo(); }
	const int &lep3_is_fromw() { return rpvstop12os.lep3_is_fromw(); }
	const int &lep3_charge() { return rpvstop12os.lep3_charge(); }
	const int &lep3_pdgid() { return rpvstop12os.lep3_pdgid(); }
	const int &lep3_type() { return rpvstop12os.lep3_type(); }
	const float &lep3_d0() { return rpvstop12os.lep3_d0(); }
	const float &lep3_d0err() { return rpvstop12os.lep3_d0err(); }
	const float &lep3_dz() { return rpvstop12os.lep3_dz(); }
	const float &lep3_ip3d() { return rpvstop12os.lep3_ip3d(); }
	const float &lep3_ip3derr() { return rpvstop12os.lep3_ip3derr(); }
	const float &lep3_dzerr() { return rpvstop12os.lep3_dzerr(); }
	const float &lep3_mt() { return rpvstop12os.lep3_mt(); }
	const float &lep3_corpfiso() { return rpvstop12os.lep3_corpfiso(); }
	const float &lep3_pfiso() { return rpvstop12os.lep3_pfiso(); }
	const float &lep3_chiso() { return rpvstop12os.lep3_chiso(); }
	const float &lep3_emiso() { return rpvstop12os.lep3_emiso(); }
	const float &lep3_nhiso() { return rpvstop12os.lep3_nhiso(); }
	const float &lep3_corpfiso04() { return rpvstop12os.lep3_corpfiso04(); }
	const float &lep3_pfiso04() { return rpvstop12os.lep3_pfiso04(); }
	const float &lep3_chiso04() { return rpvstop12os.lep3_chiso04(); }
	const float &lep3_emiso04() { return rpvstop12os.lep3_emiso04(); }
	const float &lep3_nhiso04() { return rpvstop12os.lep3_nhiso04(); }
	const float &lep3_cordetiso() { return rpvstop12os.lep3_cordetiso(); }
	const float &lep3_detiso() { return rpvstop12os.lep3_detiso(); }
	const float &lep3_trkiso() { return rpvstop12os.lep3_trkiso(); }
	const float &lep3_ecaliso() { return rpvstop12os.lep3_ecaliso(); }
	const float &lep3_hcaliso() { return rpvstop12os.lep3_hcaliso(); }
	const float &lep3_cordetiso04() { return rpvstop12os.lep3_cordetiso04(); }
	const float &lep3_detiso04() { return rpvstop12os.lep3_detiso04(); }
	const float &lep3_trkiso04() { return rpvstop12os.lep3_trkiso04(); }
	const float &lep3_ecaliso04() { return rpvstop12os.lep3_ecaliso04(); }
	const float &lep3_hcaliso04() { return rpvstop12os.lep3_hcaliso04(); }
	const float &lep3_effarea() { return rpvstop12os.lep3_effarea(); }
	const float &lep3_effarea04() { return rpvstop12os.lep3_effarea04(); }
	const float &lep3_dbeta() { return rpvstop12os.lep3_dbeta(); }
	const float &lep3_dbeta04() { return rpvstop12os.lep3_dbeta04(); }
	const float &lep3_sf_lepeff() { return rpvstop12os.lep3_sf_lepeff(); }
	const float &lep3_sf_trig() { return rpvstop12os.lep3_sf_trig(); }
	const int &lep3_mcid() { return rpvstop12os.lep3_mcid(); }
	const int &lep3_mc3id() { return rpvstop12os.lep3_mc3id(); }
	const int &lep3_momid() { return rpvstop12os.lep3_momid(); }
	const int &lep3_mc3_momid() { return rpvstop12os.lep3_mc3_momid(); }
	const bool &lep3_q3agree() { return rpvstop12os.lep3_q3agree(); }
	const bool &lep3_is_conv() { return rpvstop12os.lep3_is_conv(); }
	const int &lep3_qsc() { return rpvstop12os.lep3_qsc(); }
	const int &lep3_qctf() { return rpvstop12os.lep3_qctf(); }
	const int &lep3_qgsf() { return rpvstop12os.lep3_qgsf(); }
	const int &lep3_nmhits() { return rpvstop12os.lep3_nmhits(); }
	const int &lep3_eleid_veto() { return rpvstop12os.lep3_eleid_veto(); }
	const int &lep3_eleid_loose() { return rpvstop12os.lep3_eleid_loose(); }
	const int &lep3_eleid_medium() { return rpvstop12os.lep3_eleid_medium(); }
	const int &lep3_eleid_tight() { return rpvstop12os.lep3_eleid_tight(); }
	const float &lep3_dphiin() { return rpvstop12os.lep3_dphiin(); }
	const float &lep3_detain() { return rpvstop12os.lep3_detain(); }
	const float &lep3_sieie() { return rpvstop12os.lep3_sieie(); }
	const float &lep3_hoe() { return rpvstop12os.lep3_hoe(); }
	const float &lep3_ooemoop() { return rpvstop12os.lep3_ooemoop(); }
	const float &lep3_conv_dist() { return rpvstop12os.lep3_conv_dist(); }
	const float &lep3_conv_dcot() { return rpvstop12os.lep3_conv_dcot(); }
	const bool &lep3_is_global() { return rpvstop12os.lep3_is_global(); }
	const bool &lep3_is_tracker() { return rpvstop12os.lep3_is_tracker(); }
	const bool &lep3_is_stamu() { return rpvstop12os.lep3_is_stamu(); }
	const bool &lep3_is_pfmu() { return rpvstop12os.lep3_is_pfmu(); }
	const bool &lep3_is_loosemu() { return rpvstop12os.lep3_is_loosemu(); }
	const bool &lep3_is_tightmu() { return rpvstop12os.lep3_is_tightmu(); }
	const int &lep3_npixelhits() { return rpvstop12os.lep3_npixelhits(); }
	const int &lep3_nsihits() { return rpvstop12os.lep3_nsihits(); }
	const int &lep3_nsilayers() { return rpvstop12os.lep3_nsilayers(); }
	const int &lep3_nstahits() { return rpvstop12os.lep3_nstahits(); }
	const int &lep3_nstations() { return rpvstop12os.lep3_nstations(); }
	const float &lep3_chi2() { return rpvstop12os.lep3_chi2(); }
	const float &lep3_ndof() { return rpvstop12os.lep3_ndof(); }
	const float &lep3_pterr() { return rpvstop12os.lep3_pterr(); }
	const float &lep3_ecal_vetodep() { return rpvstop12os.lep3_ecal_vetodep(); }
	const float &lep3_hcal_vetodep() { return rpvstop12os.lep3_hcal_vetodep(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_p4() { return rpvstop12os.lep3_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_mcp4() { return rpvstop12os.lep3_mcp4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_mc3p4() { return rpvstop12os.lep3_mc3p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_mc_momp4() { return rpvstop12os.lep3_mc_momp4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_gsf_p4() { return rpvstop12os.lep3_gsf_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_ctf_p4() { return rpvstop12os.lep3_ctf_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_sc_p4() { return rpvstop12os.lep3_sc_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_gfit_p4() { return rpvstop12os.lep3_gfit_p4(); }
	const unsigned int &selection() { return rpvstop12os.selection(); }
	const bool &is_good_lumi() { return rpvstop12os.is_good_lumi(); }
	const bool &charge_type() { return rpvstop12os.charge_type(); }
	const int &njets() { return rpvstop12os.njets(); }
	const int &nbtags() { return rpvstop12os.nbtags(); }
	const int &nbtags_loose() { return rpvstop12os.nbtags_loose(); }
	const int &ttbar_bkdn() { return rpvstop12os.ttbar_bkdn(); }
	const float &vtxw() { return rpvstop12os.vtxw(); }
	const float &mt() { return rpvstop12os.mt(); }
	const float &mt2() { return rpvstop12os.mt2(); }
	const float &ht() { return rpvstop12os.ht(); }
	const float &rho() { return rpvstop12os.rho(); }
	const float &rho_iso() { return rpvstop12os.rho_iso(); }
	const bool &trig_mm() { return rpvstop12os.trig_mm(); }
	const bool &trig_em() { return rpvstop12os.trig_em(); }
	const bool &trig_ee() { return rpvstop12os.trig_ee(); }
	const bool &trig_mm_mu17_mu8() { return rpvstop12os.trig_mm_mu17_mu8(); }
	const bool &trig_ee_el17_el8_id_iso() { return rpvstop12os.trig_ee_el17_el8_id_iso(); }
	const bool &trig_em_mu17_el8_id_iso() { return rpvstop12os.trig_em_mu17_el8_id_iso(); }
	const bool &trig_em_mu8_el17_id_iso() { return rpvstop12os.trig_em_mu8_el17_id_iso(); }
	const int &njets_dn() { return rpvstop12os.njets_dn(); }
	const int &njets_up() { return rpvstop12os.njets_up(); }
	const int &nbtags_dn() { return rpvstop12os.nbtags_dn(); }
	const int &nbtags_up() { return rpvstop12os.nbtags_up(); }
	const float &ht_dn() { return rpvstop12os.ht_dn(); }
	const float &ht_up() { return rpvstop12os.ht_up(); }
	const int &nbtags_reweighted() { return rpvstop12os.nbtags_reweighted(); }
	const int &nbtags_reweighted_dn() { return rpvstop12os.nbtags_reweighted_dn(); }
	const int &nbtags_reweighted_up() { return rpvstop12os.nbtags_reweighted_up(); }
	const int &nbtags_reweighted_jec_dn() { return rpvstop12os.nbtags_reweighted_jec_dn(); }
	const int &nbtags_reweighted_jec_up() { return rpvstop12os.nbtags_reweighted_jec_up(); }
	const float &pfmet_dn() { return rpvstop12os.pfmet_dn(); }
	const float &pfmet_up() { return rpvstop12os.pfmet_up(); }
	const float &pfmet_phi_dn() { return rpvstop12os.pfmet_phi_dn(); }
	const float &pfmet_phi_up() { return rpvstop12os.pfmet_phi_up(); }
	const float &sf_dileptrig() { return rpvstop12os.sf_dileptrig(); }
	const float &sf_lepeff() { return rpvstop12os.sf_lepeff(); }
	const float &sparm0() { return rpvstop12os.sparm0(); }
	const float &sparm1() { return rpvstop12os.sparm1(); }
	const float &sparm2() { return rpvstop12os.sparm2(); }
	const float &sparm3() { return rpvstop12os.sparm3(); }
	const TString &sparm0_name() { return rpvstop12os.sparm0_name(); }
	const TString &sparm1_name() { return rpvstop12os.sparm1_name(); }
	const TString &sparm2_name() { return rpvstop12os.sparm2_name(); }
	const TString &sparm3_name() { return rpvstop12os.sparm3_name(); }
	const bool &is_pp() { return rpvstop12os.is_pp(); }
	const bool &is_mm() { return rpvstop12os.is_mm(); }
	const bool &is_ss() { return rpvstop12os.is_ss(); }
	const bool &is_sf() { return rpvstop12os.is_sf(); }
	const bool &is_df() { return rpvstop12os.is_df(); }
	const bool &is_os() { return rpvstop12os.is_os(); }
	const bool &no_extraz() { return rpvstop12os.no_extraz(); }
	const bool &no_extrag() { return rpvstop12os.no_extrag(); }
	const bool &clean() { return rpvstop12os.clean(); }
	const bool &presel() { return rpvstop12os.presel(); }
	const bool &em_mufo() { return rpvstop12os.em_mufo(); }
	const bool &em_elfo() { return rpvstop12os.em_elfo(); }
	const bool &hyp_good_vtx() { return rpvstop12os.hyp_good_vtx(); }
	const bool &is_gen_pp() { return rpvstop12os.is_gen_pp(); }
	const bool &is_gen_mm() { return rpvstop12os.is_gen_mm(); }
	const int &gen_njets() { return rpvstop12os.gen_njets(); }
	const float &gen_ht() { return rpvstop12os.gen_ht(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearjet_p4() { return rpvstop12os.lep1_nearjet_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearlep_p4() { return rpvstop12os.lep1_nearlep_p4(); }
	const float &lep1_wfr() { return rpvstop12os.lep1_wfr(); }
	const float &lep1_wflip() { return rpvstop12os.lep1_wflip(); }
	const float &lep1_nearjet_dr() { return rpvstop12os.lep1_nearjet_dr(); }
	const float &lep1_nearlep_dr() { return rpvstop12os.lep1_nearlep_dr(); }
	const int &lep1_nearlep_id() { return rpvstop12os.lep1_nearlep_id(); }
	const bool &lep1_isFromH() { return rpvstop12os.lep1_isFromH(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearjet_p4() { return rpvstop12os.lep2_nearjet_p4(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearlep_p4() { return rpvstop12os.lep2_nearlep_p4(); }
	const float &lep2_wfr() { return rpvstop12os.lep2_wfr(); }
	const float &lep2_wflip() { return rpvstop12os.lep2_wflip(); }
	const float &lep2_nearjet_dr() { return rpvstop12os.lep2_nearjet_dr(); }
	const float &lep2_nearlep_dr() { return rpvstop12os.lep2_nearlep_dr(); }
	const int &lep2_nearlep_id() { return rpvstop12os.lep2_nearlep_id(); }
	const bool &lep2_isFromH() { return rpvstop12os.lep2_isFromH(); }
	const float &jets_dr12() { return rpvstop12os.jets_dr12(); }
	const float &dijet_mass() { return rpvstop12os.dijet_mass(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_p4() { return rpvstop12os.vjets_p4(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_p4_up() { return rpvstop12os.vjets_p4_up(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_p4_dn() { return rpvstop12os.vjets_p4_dn(); }
	const vector<int> &vjets_mcflavor_phys() { return rpvstop12os.vjets_mcflavor_phys(); }
	const vector<int> &vjets_mcflavor_algo() { return rpvstop12os.vjets_mcflavor_algo(); }
	const vector<int> &vjets_mcflavor_phys_up() { return rpvstop12os.vjets_mcflavor_phys_up(); }
	const vector<int> &vjets_mcflavor_algo_up() { return rpvstop12os.vjets_mcflavor_algo_up(); }
	const vector<int> &vjets_mcflavor_phys_dn() { return rpvstop12os.vjets_mcflavor_phys_dn(); }
	const vector<int> &vjets_mcflavor_algo_dn() { return rpvstop12os.vjets_mcflavor_algo_dn(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_mc3p4() { return rpvstop12os.vjets_mc3p4(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vgenjets_p4() { return rpvstop12os.vgenjets_p4(); }
	const vector<int> &vjets_mc3id() { return rpvstop12os.vjets_mc3id(); }
	const vector<int> &vjets_momid() { return rpvstop12os.vjets_momid(); }
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_nearjet_p4() { return rpvstop12os.vjets_nearjet_p4(); }
	const vector<float> &vjets_nearjet_dr() { return rpvstop12os.vjets_nearjet_dr(); }
	const vector<float> &vjets_bdisc() { return rpvstop12os.vjets_bdisc(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep1_p4() { return rpvstop12os.gen_lep1_p4(); }
	const int &gen_lep1_pdgid() { return rpvstop12os.gen_lep1_pdgid(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep2_p4() { return rpvstop12os.gen_lep2_p4(); }
	const int &gen_lep2_pdgid() { return rpvstop12os.gen_lep2_pdgid(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep3_p4() { return rpvstop12os.gen_lep3_p4(); }
	const int &gen_lep3_pdgid() { return rpvstop12os.gen_lep3_pdgid(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_dilep_p4() { return rpvstop12os.gen_dilep_p4(); }
	const int &gen_dilep_type() { return rpvstop12os.gen_dilep_type(); }
	const float &gen_dilep_mass() { return rpvstop12os.gen_dilep_mass(); }
	const float &gen_dilep_dphi() { return rpvstop12os.gen_dilep_dphi(); }
	const float &gen_dilep_deta() { return rpvstop12os.gen_dilep_deta(); }
	const float &gen_dilep_dr() { return rpvstop12os.gen_dilep_dr(); }
	const int &pfcandid5() { return rpvstop12os.pfcandid5(); }
	const int &pfcandid10() { return rpvstop12os.pfcandid10(); }
	const int &pfcanddirid10() { return rpvstop12os.pfcanddirid10(); }
	const int &pfcandvetoid10() { return rpvstop12os.pfcandvetoid10(); }
	const int &pfcandvetoLid10() { return rpvstop12os.pfcandvetoLid10(); }
	const int &pfcandidOS10() { return rpvstop12os.pfcandidOS10(); }
	const int &pfcandidOS10looseZ() { return rpvstop12os.pfcandidOS10looseZ(); }
	const int &pfcandid5looseZ() { return rpvstop12os.pfcandid5looseZ(); }
	const float &trkpt5() { return rpvstop12os.trkpt5(); }
	const float &mleptrk5() { return rpvstop12os.mleptrk5(); }
	const float &trkreliso5() { return rpvstop12os.trkreliso5(); }
	const float &trkpt10() { return rpvstop12os.trkpt10(); }
	const float &mleptrk10() { return rpvstop12os.mleptrk10(); }
	const float &trkreliso10() { return rpvstop12os.trkreliso10(); }
	const float &trkpt5loose() { return rpvstop12os.trkpt5loose(); }
	const float &trkreliso5loose() { return rpvstop12os.trkreliso5loose(); }
	const float &trkpt10loose() { return rpvstop12os.trkpt10loose(); }
	const float &trkreliso10loose() { return rpvstop12os.trkreliso10loose(); }
	const float &trkpt10pt0p1() { return rpvstop12os.trkpt10pt0p1(); }
	const float &trkreliso10pt0p1() { return rpvstop12os.trkreliso10pt0p1(); }
	const float &trkpt10pt0p2() { return rpvstop12os.trkpt10pt0p2(); }
	const float &trkreliso10pt0p2() { return rpvstop12os.trkreliso10pt0p2(); }
	const float &trkpt10pt0p3() { return rpvstop12os.trkpt10pt0p3(); }
	const float &trkreliso10pt0p3() { return rpvstop12os.trkreliso10pt0p3(); }
	const float &trkpt10pt0p4() { return rpvstop12os.trkpt10pt0p4(); }
	const float &trkreliso10pt0p4() { return rpvstop12os.trkreliso10pt0p4(); }
	const float &trkpt10pt0p5() { return rpvstop12os.trkpt10pt0p5(); }
	const float &trkreliso10pt0p5() { return rpvstop12os.trkreliso10pt0p5(); }
	const float &trkpt10pt0p6() { return rpvstop12os.trkpt10pt0p6(); }
	const float &trkreliso10pt0p6() { return rpvstop12os.trkreliso10pt0p6(); }
	const float &trkpt10pt0p7() { return rpvstop12os.trkpt10pt0p7(); }
	const float &trkreliso10pt0p7() { return rpvstop12os.trkreliso10pt0p7(); }
	const float &trkpt10pt0p8() { return rpvstop12os.trkpt10pt0p8(); }
	const float &trkreliso10pt0p8() { return rpvstop12os.trkreliso10pt0p8(); }
	const float &trkpt10pt0p9() { return rpvstop12os.trkpt10pt0p9(); }
	const float &trkreliso10pt0p9() { return rpvstop12os.trkreliso10pt0p9(); }
	const float &trkpt10pt1p0() { return rpvstop12os.trkpt10pt1p0(); }
	const float &trkreliso10pt1p0() { return rpvstop12os.trkreliso10pt1p0(); }
	const float &pfcandiso5() { return rpvstop12os.pfcandiso5(); }
	const float &pfcandiso10() { return rpvstop12os.pfcandiso10(); }
	const float &pfcanddiriso10() { return rpvstop12os.pfcanddiriso10(); }
	const float &pfcandvetoiso10() { return rpvstop12os.pfcandvetoiso10(); }
	const float &pfcandvetoLiso10() { return rpvstop12os.pfcandvetoLiso10(); }
	const float &pfcandisoOS10() { return rpvstop12os.pfcandisoOS10(); }
	const float &pfcandisoOS10looseZ() { return rpvstop12os.pfcandisoOS10looseZ(); }
	const float &pfcandiso5looseZ() { return rpvstop12os.pfcandiso5looseZ(); }
	const float &pfcandpt5() { return rpvstop12os.pfcandpt5(); }
	const float &pfcandpt10() { return rpvstop12os.pfcandpt10(); }
	const float &pfcanddirpt10() { return rpvstop12os.pfcanddirpt10(); }
	const float &pfcandvetopt10() { return rpvstop12os.pfcandvetopt10(); }
	const float &pfcandvetoLpt10() { return rpvstop12os.pfcandvetoLpt10(); }
	const float &pfcandptOS10() { return rpvstop12os.pfcandptOS10(); }
	const float &pfcandptOS10looseZ() { return rpvstop12os.pfcandptOS10looseZ(); }
	const float &pfcandpt5looseZ() { return rpvstop12os.pfcandpt5looseZ(); }
	const float &pfcanddz5() { return rpvstop12os.pfcanddz5(); }
	const float &pfcanddz10() { return rpvstop12os.pfcanddz10(); }
	const float &pfcanddirdz10() { return rpvstop12os.pfcanddirdz10(); }
	const float &pfcandvetodz10() { return rpvstop12os.pfcandvetodz10(); }
	const float &pfcandvetoLdz10() { return rpvstop12os.pfcandvetoLdz10(); }
	const float &pfcanddzOS10() { return rpvstop12os.pfcanddzOS10(); }
	const float &pfcanddzOS10looseZ() { return rpvstop12os.pfcanddzOS10looseZ(); }
	const float &pfcanddz5looseZ() { return rpvstop12os.pfcanddz5looseZ(); }
	const float &pfcandmindrj5() { return rpvstop12os.pfcandmindrj5(); }
	const float &pfcandmindrj10() { return rpvstop12os.pfcandmindrj10(); }
	const float &pfcanddirmindrj10() { return rpvstop12os.pfcanddirmindrj10(); }
	const float &pfcandvetomindrj10() { return rpvstop12os.pfcandvetomindrj10(); }
	const float &pfcandvetoLmindrj10() { return rpvstop12os.pfcandvetoLmindrj10(); }
	const float &pfcandpt10pt0p1() { return rpvstop12os.pfcandpt10pt0p1(); }
	const float &pfcandiso10pt0p1() { return rpvstop12os.pfcandiso10pt0p1(); }
	const float &pfcandpt10pt0p2() { return rpvstop12os.pfcandpt10pt0p2(); }
	const float &pfcandiso10pt0p2() { return rpvstop12os.pfcandiso10pt0p2(); }
	const float &pfcandpt10pt0p3() { return rpvstop12os.pfcandpt10pt0p3(); }
	const float &pfcandiso10pt0p3() { return rpvstop12os.pfcandiso10pt0p3(); }
	const float &pfcandpt10pt0p4() { return rpvstop12os.pfcandpt10pt0p4(); }
	const float &pfcandiso10pt0p4() { return rpvstop12os.pfcandiso10pt0p4(); }
	const float &pfcandpt10pt0p5() { return rpvstop12os.pfcandpt10pt0p5(); }
	const float &pfcandiso10pt0p5() { return rpvstop12os.pfcandiso10pt0p5(); }
	const float &pfcandpt10pt0p6() { return rpvstop12os.pfcandpt10pt0p6(); }
	const float &pfcandiso10pt0p6() { return rpvstop12os.pfcandiso10pt0p6(); }
	const float &pfcandpt10pt0p7() { return rpvstop12os.pfcandpt10pt0p7(); }
	const float &pfcandiso10pt0p7() { return rpvstop12os.pfcandiso10pt0p7(); }
	const float &pfcandpt10pt0p8() { return rpvstop12os.pfcandpt10pt0p8(); }
	const float &pfcandiso10pt0p8() { return rpvstop12os.pfcandiso10pt0p8(); }
	const float &pfcandpt10pt0p9() { return rpvstop12os.pfcandpt10pt0p9(); }
	const float &pfcandiso10pt0p9() { return rpvstop12os.pfcandiso10pt0p9(); }
	const float &pfcandpt10pt1p0() { return rpvstop12os.pfcandpt10pt1p0(); }
	const float &pfcandiso10pt1p0() { return rpvstop12os.pfcandiso10pt1p0(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcand5() { return rpvstop12os.pfcand5(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcand10() { return rpvstop12os.pfcand10(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcanddir10() { return rpvstop12os.pfcanddir10(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcandveto10() { return rpvstop12os.pfcandveto10(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcandvetoL10() { return rpvstop12os.pfcandvetoL10(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcandOS10() { return rpvstop12os.pfcandOS10(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcandOS10looseZ() { return rpvstop12os.pfcandOS10looseZ(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcand5looseZ() { return rpvstop12os.pfcand5looseZ(); }
	const int &pfTau15_leadPtcandID() { return rpvstop12os.pfTau15_leadPtcandID(); }
	const int &pfTau_leadPtcandID() { return rpvstop12os.pfTau_leadPtcandID(); }
	const int &pfTauLoose_leadPtcandID() { return rpvstop12os.pfTauLoose_leadPtcandID(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTau15() { return rpvstop12os.pfTau15(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTau15_leadPtcand() { return rpvstop12os.pfTau15_leadPtcand(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTau() { return rpvstop12os.pfTau(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTau_leadPtcand() { return rpvstop12os.pfTau_leadPtcand(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTauLoose() { return rpvstop12os.pfTauLoose(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTauLoose_leadPtcand() { return rpvstop12os.pfTauLoose_leadPtcand(); }
	const vector<float> &pfjets_beta() { return rpvstop12os.pfjets_beta(); }
	const vector<float> &pfjets_beta2() { return rpvstop12os.pfjets_beta2(); }
	const vector<float> &pfjets_beta_0p1() { return rpvstop12os.pfjets_beta_0p1(); }
	const vector<float> &pfjets_beta_0p2() { return rpvstop12os.pfjets_beta_0p2(); }
	const vector<float> &pfjets_beta2_0p1() { return rpvstop12os.pfjets_beta2_0p1(); }
	const vector<float> &pfjets_beta2_0p5() { return rpvstop12os.pfjets_beta2_0p5(); }
	const vector<float> &pfjets_mvaPUid() { return rpvstop12os.pfjets_mvaPUid(); }
	const vector<float> &pfjets_mva5xPUid() { return rpvstop12os.pfjets_mva5xPUid(); }
	const vector<float> &pfjets_mvaBeta() { return rpvstop12os.pfjets_mvaBeta(); }
	const bool &passes_isotrk_veto() { return rpvstop12os.passes_isotrk_veto(); }
	const bool &passes_tau_veto() { return rpvstop12os.passes_tau_veto(); }
	const int &njets_pv_tight0() { return rpvstop12os.njets_pv_tight0(); }
	const int &njets_pv_tight1() { return rpvstop12os.njets_pv_tight1(); }
	const int &njets_pv_tight2() { return rpvstop12os.njets_pv_tight2(); }
	const float &scale1fb() { return rpvstop12os.scale1fb(); }
	const float &xsec() { return rpvstop12os.xsec(); }
	const unsigned int &nevts() { return rpvstop12os.nevts(); }
	const float &br() { return rpvstop12os.br(); }
}
