// -*- C++ -*-
#ifndef SSB2012_H
#define SSB2012_H
#include "Math/LorentzVector.h"
#include "Math/Point3D.h"
#include "TMath.h"
#include "TBranch.h"
#include "TTree.h"
#include "TH1F.h"
#include "TFile.h"
#include "TBits.h"
#include <vector> 
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

using namespace std; 
class SSB {
private: 
protected: 
	unsigned int index;
	unsigned int	run_;
	TBranch *run_branch;
	bool run_isLoaded;
	unsigned int	ls_;
	TBranch *ls_branch;
	bool ls_isLoaded;
	unsigned int	evt_;
	TBranch *evt_branch;
	bool evt_isLoaded;
	bool	is_real_data_;
	TBranch *is_real_data_branch;
	bool is_real_data_isLoaded;
	int	sample_;
	TBranch *sample_branch;
	bool sample_isLoaded;
	int	nvtxs_;
	TBranch *nvtxs_branch;
	bool nvtxs_isLoaded;
	int	vtx_idx_;
	TBranch *vtx_idx_branch;
	bool vtx_idx_isLoaded;
	float	pfmet_;
	TBranch *pfmet_branch;
	bool pfmet_isLoaded;
	float	pfmet_phi_;
	TBranch *pfmet_phi_branch;
	bool pfmet_phi_isLoaded;
	float	corpfmet_;
	TBranch *corpfmet_branch;
	bool corpfmet_isLoaded;
	float	corpfmet_phi_;
	TBranch *corpfmet_phi_branch;
	bool corpfmet_phi_isLoaded;
	float	scale1fb_;
	TBranch *scale1fb_branch;
	bool scale1fb_isLoaded;
	float	xsec_;
	TBranch *xsec_branch;
	bool xsec_isLoaded;
	float	kfactor_;
	TBranch *kfactor_branch;
	bool kfactor_isLoaded;
	float	gen_met_;
	TBranch *gen_met_branch;
	bool gen_met_isLoaded;
	float	gen_met_phi_;
	TBranch *gen_met_phi_branch;
	bool gen_met_phi_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_p4_;
	TBranch *lep1_p4_branch;
	bool lep1_p4_isLoaded;
	bool	lep1_passes_id_;
	TBranch *lep1_passes_id_branch;
	bool lep1_passes_id_isLoaded;
	bool	lep1_passes_iso_;
	TBranch *lep1_passes_iso_branch;
	bool lep1_passes_iso_isLoaded;
	bool	lep1_is_num_;
	TBranch *lep1_is_num_branch;
	bool lep1_is_num_isLoaded;
	bool	lep1_is_fo_;
	TBranch *lep1_is_fo_branch;
	bool lep1_is_fo_isLoaded;
	int	lep1_charge_;
	TBranch *lep1_charge_branch;
	bool lep1_charge_isLoaded;
	int	lep1_pdgid_;
	TBranch *lep1_pdgid_branch;
	bool lep1_pdgid_isLoaded;
	int	lep1_type_;
	TBranch *lep1_type_branch;
	bool lep1_type_isLoaded;
	float	lep1_d0_;
	TBranch *lep1_d0_branch;
	bool lep1_d0_isLoaded;
	float	lep1_dz_;
	TBranch *lep1_dz_branch;
	bool lep1_dz_isLoaded;
	float	lep1_mt_;
	TBranch *lep1_mt_branch;
	bool lep1_mt_isLoaded;
	float	lep1_corpfiso_;
	TBranch *lep1_corpfiso_branch;
	bool lep1_corpfiso_isLoaded;
	float	lep1_pfiso_;
	TBranch *lep1_pfiso_branch;
	bool lep1_pfiso_isLoaded;
	float	lep1_chiso_;
	TBranch *lep1_chiso_branch;
	bool lep1_chiso_isLoaded;
	float	lep1_emiso_;
	TBranch *lep1_emiso_branch;
	bool lep1_emiso_isLoaded;
	float	lep1_nhiso_;
	TBranch *lep1_nhiso_branch;
	bool lep1_nhiso_isLoaded;
	float	lep1_corpfiso04_;
	TBranch *lep1_corpfiso04_branch;
	bool lep1_corpfiso04_isLoaded;
	float	lep1_pfiso04_;
	TBranch *lep1_pfiso04_branch;
	bool lep1_pfiso04_isLoaded;
	float	lep1_chiso04_;
	TBranch *lep1_chiso04_branch;
	bool lep1_chiso04_isLoaded;
	float	lep1_emiso04_;
	TBranch *lep1_emiso04_branch;
	bool lep1_emiso04_isLoaded;
	float	lep1_nhiso04_;
	TBranch *lep1_nhiso04_branch;
	bool lep1_nhiso04_isLoaded;
	float	lep1_cordetiso_;
	TBranch *lep1_cordetiso_branch;
	bool lep1_cordetiso_isLoaded;
	float	lep1_detiso_;
	TBranch *lep1_detiso_branch;
	bool lep1_detiso_isLoaded;
	float	lep1_trkiso_;
	TBranch *lep1_trkiso_branch;
	bool lep1_trkiso_isLoaded;
	float	lep1_ecaliso_;
	TBranch *lep1_ecaliso_branch;
	bool lep1_ecaliso_isLoaded;
	float	lep1_hcaliso_;
	TBranch *lep1_hcaliso_branch;
	bool lep1_hcaliso_isLoaded;
	float	lep1_cordetiso04_;
	TBranch *lep1_cordetiso04_branch;
	bool lep1_cordetiso04_isLoaded;
	float	lep1_detiso04_;
	TBranch *lep1_detiso04_branch;
	bool lep1_detiso04_isLoaded;
	float	lep1_trkiso04_;
	TBranch *lep1_trkiso04_branch;
	bool lep1_trkiso04_isLoaded;
	float	lep1_ecaliso04_;
	TBranch *lep1_ecaliso04_branch;
	bool lep1_ecaliso04_isLoaded;
	float	lep1_hcaliso04_;
	TBranch *lep1_hcaliso04_branch;
	bool lep1_hcaliso04_isLoaded;
	float	lep1_effarea_;
	TBranch *lep1_effarea_branch;
	bool lep1_effarea_isLoaded;
	float	lep1_effarea04_;
	TBranch *lep1_effarea04_branch;
	bool lep1_effarea04_isLoaded;
	float	lep1_dbeta_;
	TBranch *lep1_dbeta_branch;
	bool lep1_dbeta_isLoaded;
	float	lep1_dbeta04_;
	TBranch *lep1_dbeta04_branch;
	bool lep1_dbeta04_isLoaded;
	float	lep1_sf_lepeff_;
	TBranch *lep1_sf_lepeff_branch;
	bool lep1_sf_lepeff_isLoaded;
	float	lep1_sf_trig_;
	TBranch *lep1_sf_trig_branch;
	bool lep1_sf_trig_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_mcp4_;
	TBranch *lep1_mcp4_branch;
	bool lep1_mcp4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_mc3p4_;
	TBranch *lep1_mc3p4_branch;
	bool lep1_mc3p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_mc_momp4_;
	TBranch *lep1_mc_momp4_branch;
	bool lep1_mc_momp4_isLoaded;
	int	lep1_mcid_;
	TBranch *lep1_mcid_branch;
	bool lep1_mcid_isLoaded;
	int	lep1_mc3id_;
	TBranch *lep1_mc3id_branch;
	bool lep1_mc3id_isLoaded;
	int	lep1_momid_;
	TBranch *lep1_momid_branch;
	bool lep1_momid_isLoaded;
	int	lep1_mc3_momid_;
	TBranch *lep1_mc3_momid_branch;
	bool lep1_mc3_momid_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_gsf_p4_;
	TBranch *lep1_gsf_p4_branch;
	bool lep1_gsf_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_ctf_p4_;
	TBranch *lep1_ctf_p4_branch;
	bool lep1_ctf_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_sc_p4_;
	TBranch *lep1_sc_p4_branch;
	bool lep1_sc_p4_isLoaded;
	bool	lep1_q3agree_;
	TBranch *lep1_q3agree_branch;
	bool lep1_q3agree_isLoaded;
	bool	lep1_is_conv_;
	TBranch *lep1_is_conv_branch;
	bool lep1_is_conv_isLoaded;
	int	lep1_qsc_;
	TBranch *lep1_qsc_branch;
	bool lep1_qsc_isLoaded;
	int	lep1_qctf_;
	TBranch *lep1_qctf_branch;
	bool lep1_qctf_isLoaded;
	int	lep1_qgsf_;
	TBranch *lep1_qgsf_branch;
	bool lep1_qgsf_isLoaded;
	int	lep1_nmhits_;
	TBranch *lep1_nmhits_branch;
	bool lep1_nmhits_isLoaded;
	int	lep1_eleid_veto_;
	TBranch *lep1_eleid_veto_branch;
	bool lep1_eleid_veto_isLoaded;
	int	lep1_eleid_loose_;
	TBranch *lep1_eleid_loose_branch;
	bool lep1_eleid_loose_isLoaded;
	int	lep1_eleid_medium_;
	TBranch *lep1_eleid_medium_branch;
	bool lep1_eleid_medium_isLoaded;
	int	lep1_eleid_tight_;
	TBranch *lep1_eleid_tight_branch;
	bool lep1_eleid_tight_isLoaded;
	float	lep1_dphiin_;
	TBranch *lep1_dphiin_branch;
	bool lep1_dphiin_isLoaded;
	float	lep1_detain_;
	TBranch *lep1_detain_branch;
	bool lep1_detain_isLoaded;
	float	lep1_sieie_;
	TBranch *lep1_sieie_branch;
	bool lep1_sieie_isLoaded;
	float	lep1_hoe_;
	TBranch *lep1_hoe_branch;
	bool lep1_hoe_isLoaded;
	float	lep1_ooemoop_;
	TBranch *lep1_ooemoop_branch;
	bool lep1_ooemoop_isLoaded;
	float	lep1_conv_dist_;
	TBranch *lep1_conv_dist_branch;
	bool lep1_conv_dist_isLoaded;
	float	lep1_conv_dcot_;
	TBranch *lep1_conv_dcot_branch;
	bool lep1_conv_dcot_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_gfit_p4_;
	TBranch *lep1_gfit_p4_branch;
	bool lep1_gfit_p4_isLoaded;
	bool	lep1_is_global_;
	TBranch *lep1_is_global_branch;
	bool lep1_is_global_isLoaded;
	bool	lep1_is_tracker_;
	TBranch *lep1_is_tracker_branch;
	bool lep1_is_tracker_isLoaded;
	bool	lep1_is_stamu_;
	TBranch *lep1_is_stamu_branch;
	bool lep1_is_stamu_isLoaded;
	bool	lep1_is_pfmu_;
	TBranch *lep1_is_pfmu_branch;
	bool lep1_is_pfmu_isLoaded;
	bool	lep1_is_loosemu_;
	TBranch *lep1_is_loosemu_branch;
	bool lep1_is_loosemu_isLoaded;
	bool	lep1_is_tightmu_;
	TBranch *lep1_is_tightmu_branch;
	bool lep1_is_tightmu_isLoaded;
	int	lep1_npixelhits_;
	TBranch *lep1_npixelhits_branch;
	bool lep1_npixelhits_isLoaded;
	int	lep1_nsihits_;
	TBranch *lep1_nsihits_branch;
	bool lep1_nsihits_isLoaded;
	int	lep1_nsilayers_;
	TBranch *lep1_nsilayers_branch;
	bool lep1_nsilayers_isLoaded;
	int	lep1_nstahits_;
	TBranch *lep1_nstahits_branch;
	bool lep1_nstahits_isLoaded;
	int	lep1_nstations_;
	TBranch *lep1_nstations_branch;
	bool lep1_nstations_isLoaded;
	float	lep1_chi2_;
	TBranch *lep1_chi2_branch;
	bool lep1_chi2_isLoaded;
	float	lep1_ndof_;
	TBranch *lep1_ndof_branch;
	bool lep1_ndof_isLoaded;
	float	lep1_pterr_;
	TBranch *lep1_pterr_branch;
	bool lep1_pterr_isLoaded;
	float	lep1_ecal_vetodep_;
	TBranch *lep1_ecal_vetodep_branch;
	bool lep1_ecal_vetodep_isLoaded;
	float	lep1_hcal_vetodep_;
	TBranch *lep1_hcal_vetodep_branch;
	bool lep1_hcal_vetodep_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_p4_;
	TBranch *lep2_p4_branch;
	bool lep2_p4_isLoaded;
	bool	lep2_passes_id_;
	TBranch *lep2_passes_id_branch;
	bool lep2_passes_id_isLoaded;
	bool	lep2_passes_iso_;
	TBranch *lep2_passes_iso_branch;
	bool lep2_passes_iso_isLoaded;
	bool	lep2_is_num_;
	TBranch *lep2_is_num_branch;
	bool lep2_is_num_isLoaded;
	bool	lep2_is_fo_;
	TBranch *lep2_is_fo_branch;
	bool lep2_is_fo_isLoaded;
	int	lep2_charge_;
	TBranch *lep2_charge_branch;
	bool lep2_charge_isLoaded;
	int	lep2_pdgid_;
	TBranch *lep2_pdgid_branch;
	bool lep2_pdgid_isLoaded;
	int	lep2_type_;
	TBranch *lep2_type_branch;
	bool lep2_type_isLoaded;
	float	lep2_d0_;
	TBranch *lep2_d0_branch;
	bool lep2_d0_isLoaded;
	float	lep2_dz_;
	TBranch *lep2_dz_branch;
	bool lep2_dz_isLoaded;
	float	lep2_mt_;
	TBranch *lep2_mt_branch;
	bool lep2_mt_isLoaded;
	float	lep2_corpfiso_;
	TBranch *lep2_corpfiso_branch;
	bool lep2_corpfiso_isLoaded;
	float	lep2_pfiso_;
	TBranch *lep2_pfiso_branch;
	bool lep2_pfiso_isLoaded;
	float	lep2_chiso_;
	TBranch *lep2_chiso_branch;
	bool lep2_chiso_isLoaded;
	float	lep2_emiso_;
	TBranch *lep2_emiso_branch;
	bool lep2_emiso_isLoaded;
	float	lep2_nhiso_;
	TBranch *lep2_nhiso_branch;
	bool lep2_nhiso_isLoaded;
	float	lep2_corpfiso04_;
	TBranch *lep2_corpfiso04_branch;
	bool lep2_corpfiso04_isLoaded;
	float	lep2_pfiso04_;
	TBranch *lep2_pfiso04_branch;
	bool lep2_pfiso04_isLoaded;
	float	lep2_chiso04_;
	TBranch *lep2_chiso04_branch;
	bool lep2_chiso04_isLoaded;
	float	lep2_emiso04_;
	TBranch *lep2_emiso04_branch;
	bool lep2_emiso04_isLoaded;
	float	lep2_nhiso04_;
	TBranch *lep2_nhiso04_branch;
	bool lep2_nhiso04_isLoaded;
	float	lep2_cordetiso_;
	TBranch *lep2_cordetiso_branch;
	bool lep2_cordetiso_isLoaded;
	float	lep2_detiso_;
	TBranch *lep2_detiso_branch;
	bool lep2_detiso_isLoaded;
	float	lep2_trkiso_;
	TBranch *lep2_trkiso_branch;
	bool lep2_trkiso_isLoaded;
	float	lep2_ecaliso_;
	TBranch *lep2_ecaliso_branch;
	bool lep2_ecaliso_isLoaded;
	float	lep2_hcaliso_;
	TBranch *lep2_hcaliso_branch;
	bool lep2_hcaliso_isLoaded;
	float	lep2_cordetiso04_;
	TBranch *lep2_cordetiso04_branch;
	bool lep2_cordetiso04_isLoaded;
	float	lep2_detiso04_;
	TBranch *lep2_detiso04_branch;
	bool lep2_detiso04_isLoaded;
	float	lep2_trkiso04_;
	TBranch *lep2_trkiso04_branch;
	bool lep2_trkiso04_isLoaded;
	float	lep2_ecaliso04_;
	TBranch *lep2_ecaliso04_branch;
	bool lep2_ecaliso04_isLoaded;
	float	lep2_hcaliso04_;
	TBranch *lep2_hcaliso04_branch;
	bool lep2_hcaliso04_isLoaded;
	float	lep2_effarea_;
	TBranch *lep2_effarea_branch;
	bool lep2_effarea_isLoaded;
	float	lep2_effarea04_;
	TBranch *lep2_effarea04_branch;
	bool lep2_effarea04_isLoaded;
	float	lep2_dbeta_;
	TBranch *lep2_dbeta_branch;
	bool lep2_dbeta_isLoaded;
	float	lep2_dbeta04_;
	TBranch *lep2_dbeta04_branch;
	bool lep2_dbeta04_isLoaded;
	float	lep2_sf_lepeff_;
	TBranch *lep2_sf_lepeff_branch;
	bool lep2_sf_lepeff_isLoaded;
	float	lep2_sf_trig_;
	TBranch *lep2_sf_trig_branch;
	bool lep2_sf_trig_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_mcp4_;
	TBranch *lep2_mcp4_branch;
	bool lep2_mcp4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_mc3p4_;
	TBranch *lep2_mc3p4_branch;
	bool lep2_mc3p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_mc_momp4_;
	TBranch *lep2_mc_momp4_branch;
	bool lep2_mc_momp4_isLoaded;
	int	lep2_mcid_;
	TBranch *lep2_mcid_branch;
	bool lep2_mcid_isLoaded;
	int	lep2_mc3id_;
	TBranch *lep2_mc3id_branch;
	bool lep2_mc3id_isLoaded;
	int	lep2_momid_;
	TBranch *lep2_momid_branch;
	bool lep2_momid_isLoaded;
	int	lep2_mc3_momid_;
	TBranch *lep2_mc3_momid_branch;
	bool lep2_mc3_momid_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_gsf_p4_;
	TBranch *lep2_gsf_p4_branch;
	bool lep2_gsf_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_ctf_p4_;
	TBranch *lep2_ctf_p4_branch;
	bool lep2_ctf_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_sc_p4_;
	TBranch *lep2_sc_p4_branch;
	bool lep2_sc_p4_isLoaded;
	bool	lep2_q3agree_;
	TBranch *lep2_q3agree_branch;
	bool lep2_q3agree_isLoaded;
	bool	lep2_is_conv_;
	TBranch *lep2_is_conv_branch;
	bool lep2_is_conv_isLoaded;
	int	lep2_qsc_;
	TBranch *lep2_qsc_branch;
	bool lep2_qsc_isLoaded;
	int	lep2_qctf_;
	TBranch *lep2_qctf_branch;
	bool lep2_qctf_isLoaded;
	int	lep2_qgsf_;
	TBranch *lep2_qgsf_branch;
	bool lep2_qgsf_isLoaded;
	int	lep2_nmhits_;
	TBranch *lep2_nmhits_branch;
	bool lep2_nmhits_isLoaded;
	int	lep2_eleid_veto_;
	TBranch *lep2_eleid_veto_branch;
	bool lep2_eleid_veto_isLoaded;
	int	lep2_eleid_loose_;
	TBranch *lep2_eleid_loose_branch;
	bool lep2_eleid_loose_isLoaded;
	int	lep2_eleid_medium_;
	TBranch *lep2_eleid_medium_branch;
	bool lep2_eleid_medium_isLoaded;
	int	lep2_eleid_tight_;
	TBranch *lep2_eleid_tight_branch;
	bool lep2_eleid_tight_isLoaded;
	float	lep2_dphiin_;
	TBranch *lep2_dphiin_branch;
	bool lep2_dphiin_isLoaded;
	float	lep2_detain_;
	TBranch *lep2_detain_branch;
	bool lep2_detain_isLoaded;
	float	lep2_sieie_;
	TBranch *lep2_sieie_branch;
	bool lep2_sieie_isLoaded;
	float	lep2_hoe_;
	TBranch *lep2_hoe_branch;
	bool lep2_hoe_isLoaded;
	float	lep2_ooemoop_;
	TBranch *lep2_ooemoop_branch;
	bool lep2_ooemoop_isLoaded;
	float	lep2_conv_dist_;
	TBranch *lep2_conv_dist_branch;
	bool lep2_conv_dist_isLoaded;
	float	lep2_conv_dcot_;
	TBranch *lep2_conv_dcot_branch;
	bool lep2_conv_dcot_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_gfit_p4_;
	TBranch *lep2_gfit_p4_branch;
	bool lep2_gfit_p4_isLoaded;
	bool	lep2_is_global_;
	TBranch *lep2_is_global_branch;
	bool lep2_is_global_isLoaded;
	bool	lep2_is_tracker_;
	TBranch *lep2_is_tracker_branch;
	bool lep2_is_tracker_isLoaded;
	bool	lep2_is_stamu_;
	TBranch *lep2_is_stamu_branch;
	bool lep2_is_stamu_isLoaded;
	bool	lep2_is_pfmu_;
	TBranch *lep2_is_pfmu_branch;
	bool lep2_is_pfmu_isLoaded;
	bool	lep2_is_loosemu_;
	TBranch *lep2_is_loosemu_branch;
	bool lep2_is_loosemu_isLoaded;
	bool	lep2_is_tightmu_;
	TBranch *lep2_is_tightmu_branch;
	bool lep2_is_tightmu_isLoaded;
	int	lep2_npixelhits_;
	TBranch *lep2_npixelhits_branch;
	bool lep2_npixelhits_isLoaded;
	int	lep2_nsihits_;
	TBranch *lep2_nsihits_branch;
	bool lep2_nsihits_isLoaded;
	int	lep2_nsilayers_;
	TBranch *lep2_nsilayers_branch;
	bool lep2_nsilayers_isLoaded;
	int	lep2_nstahits_;
	TBranch *lep2_nstahits_branch;
	bool lep2_nstahits_isLoaded;
	int	lep2_nstations_;
	TBranch *lep2_nstations_branch;
	bool lep2_nstations_isLoaded;
	float	lep2_chi2_;
	TBranch *lep2_chi2_branch;
	bool lep2_chi2_isLoaded;
	float	lep2_ndof_;
	TBranch *lep2_ndof_branch;
	bool lep2_ndof_isLoaded;
	float	lep2_pterr_;
	TBranch *lep2_pterr_branch;
	bool lep2_pterr_isLoaded;
	float	lep2_ecal_vetodep_;
	TBranch *lep2_ecal_vetodep_branch;
	bool lep2_ecal_vetodep_isLoaded;
	float	lep2_hcal_vetodep_;
	TBranch *lep2_hcal_vetodep_branch;
	bool lep2_hcal_vetodep_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *dilep_p4_;
	TBranch *dilep_p4_branch;
	bool dilep_p4_isLoaded;
	bool	is_os_;
	TBranch *is_os_branch;
	bool is_os_isLoaded;
	bool	is_ss_;
	TBranch *is_ss_branch;
	bool is_ss_isLoaded;
	int	dilep_type_;
	TBranch *dilep_type_branch;
	bool dilep_type_isLoaded;
	int	dilep_gen_type_;
	TBranch *dilep_gen_type_branch;
	bool dilep_gen_type_isLoaded;
	float	dilep_mass_;
	TBranch *dilep_mass_branch;
	bool dilep_mass_isLoaded;
	float	dilep_dphi_;
	TBranch *dilep_dphi_branch;
	bool dilep_dphi_isLoaded;
	float	dilep_deta_;
	TBranch *dilep_deta_branch;
	bool dilep_deta_isLoaded;
	float	dilep_dr_;
	TBranch *dilep_dr_branch;
	bool dilep_dr_isLoaded;
	int	fiduciality_;
	TBranch *fiduciality_branch;
	bool fiduciality_isLoaded;
	unsigned int	selection_;
	TBranch *selection_branch;
	bool selection_isLoaded;
	bool	is_good_lumi_;
	TBranch *is_good_lumi_branch;
	bool is_good_lumi_isLoaded;
	int	njets_;
	TBranch *njets_branch;
	bool njets_isLoaded;
	int	njets20_;
	TBranch *njets20_branch;
	bool njets20_isLoaded;
	int	njets30_;
	TBranch *njets30_branch;
	bool njets30_isLoaded;
	int	nbtags_;
	TBranch *nbtags_branch;
	bool nbtags_isLoaded;
	int	nbtags20_;
	TBranch *nbtags20_branch;
	bool nbtags20_isLoaded;
	int	nbtags30_;
	TBranch *nbtags30_branch;
	bool nbtags30_isLoaded;
	float	vtxw_;
	TBranch *vtxw_branch;
	bool vtxw_isLoaded;
	float	ht_;
	TBranch *ht_branch;
	bool ht_isLoaded;
	float	ht20_;
	TBranch *ht20_branch;
	bool ht20_isLoaded;
	float	ht30_;
	TBranch *ht30_branch;
	bool ht30_isLoaded;
	float	rho_;
	TBranch *rho_branch;
	bool rho_isLoaded;
	float	rho_iso_;
	TBranch *rho_iso_branch;
	bool rho_iso_isLoaded;
	bool	trig_mm_;
	TBranch *trig_mm_branch;
	bool trig_mm_isLoaded;
	bool	trig_em_;
	TBranch *trig_em_branch;
	bool trig_em_isLoaded;
	bool	trig_ee_;
	TBranch *trig_ee_branch;
	bool trig_ee_isLoaded;
	float	sf_dileptrig_;
	TBranch *sf_dileptrig_branch;
	bool sf_dileptrig_isLoaded;
	float	sf_lepeff_;
	TBranch *sf_lepeff_branch;
	bool sf_lepeff_isLoaded;
	float	sparm0_;
	TBranch *sparm0_branch;
	bool sparm0_isLoaded;
	float	sparm1_;
	TBranch *sparm1_branch;
	bool sparm1_isLoaded;
	float	sparm2_;
	TBranch *sparm2_branch;
	bool sparm2_isLoaded;
	float	sparm3_;
	TBranch *sparm3_branch;
	bool sparm3_isLoaded;
	bool	is_pp_;
	TBranch *is_pp_branch;
	bool is_pp_isLoaded;
	bool	is_mm_;
	TBranch *is_mm_branch;
	bool is_mm_isLoaded;
	bool	is_sf_;
	TBranch *is_sf_branch;
	bool is_sf_isLoaded;
	bool	is_df_;
	TBranch *is_df_branch;
	bool is_df_isLoaded;
	bool	no_extraz_;
	TBranch *no_extraz_branch;
	bool no_extraz_isLoaded;
	bool	is_gen_pp_;
	TBranch *is_gen_pp_branch;
	bool is_gen_pp_isLoaded;
	bool	is_gen_mm_;
	TBranch *is_gen_mm_branch;
	bool is_gen_mm_isLoaded;
	int	gen_nbtags_;
	TBranch *gen_nbtags_branch;
	bool gen_nbtags_isLoaded;
	int	gen_njets_;
	TBranch *gen_njets_branch;
	bool gen_njets_isLoaded;
	float	gen_ht_;
	TBranch *gen_ht_branch;
	bool gen_ht_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_nearbjet_p4_;
	TBranch *lep1_nearbjet_p4_branch;
	bool lep1_nearbjet_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_nearjet_p4_;
	TBranch *lep1_nearjet_p4_branch;
	bool lep1_nearjet_p4_isLoaded;
	float	lep1_wfr_;
	TBranch *lep1_wfr_branch;
	bool lep1_wfr_isLoaded;
	float	lep1_wflip_;
	TBranch *lep1_wflip_branch;
	bool lep1_wflip_isLoaded;
	float	lep1_nearbjet_dr_;
	TBranch *lep1_nearbjet_dr_branch;
	bool lep1_nearbjet_dr_isLoaded;
	float	lep1_nearjet_dr_;
	TBranch *lep1_nearjet_dr_branch;
	bool lep1_nearjet_dr_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_nearbjet_p4_;
	TBranch *lep2_nearbjet_p4_branch;
	bool lep2_nearbjet_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_nearjet_p4_;
	TBranch *lep2_nearjet_p4_branch;
	bool lep2_nearjet_p4_isLoaded;
	float	lep2_wfr_;
	TBranch *lep2_wfr_branch;
	bool lep2_wfr_isLoaded;
	float	lep2_wflip_;
	TBranch *lep2_wflip_branch;
	bool lep2_wflip_isLoaded;
	float	lep2_nearbjet_dr_;
	TBranch *lep2_nearbjet_dr_branch;
	bool lep2_nearbjet_dr_isLoaded;
	float	lep2_nearjet_dr_;
	TBranch *lep2_nearjet_dr_branch;
	bool lep2_nearjet_dr_isLoaded;
	float	sf_nbtag_;
	TBranch *sf_nbtag_branch;
	bool sf_nbtag_isLoaded;
	float	sf_nbtag3_;
	TBranch *sf_nbtag3_branch;
	bool sf_nbtag3_isLoaded;
	float	sf_unc_nbtag_;
	TBranch *sf_unc_nbtag_branch;
	bool sf_unc_nbtag_isLoaded;
	float	sf_unc_nbtag3_;
	TBranch *sf_unc_nbtag3_branch;
	bool sf_unc_nbtag3_isLoaded;
	float	jets_dr12_;
	TBranch *jets_dr12_branch;
	bool jets_dr12_isLoaded;
	float	bjets_dr12_;
	TBranch *bjets_dr12_branch;
	bool bjets_dr12_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *vgenb_p4_;
	TBranch *vgenb_p4_branch;
	bool vgenb_p4_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *vjets_p4_;
	TBranch *vjets_p4_branch;
	bool vjets_p4_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *vgenjets_p4_;
	TBranch *vgenjets_p4_branch;
	bool vgenjets_p4_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *vjets_nearjet_p4_;
	TBranch *vjets_nearjet_p4_branch;
	bool vjets_nearjet_p4_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *vbjets_p4_;
	TBranch *vbjets_p4_branch;
	bool vbjets_p4_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *vbjets_nearjet_p4_;
	TBranch *vbjets_nearjet_p4_branch;
	bool vbjets_nearjet_p4_isLoaded;
public: 
void Init(TTree *tree) {
	lep1_p4_branch = 0;
	if (tree->GetBranch("lep1_p4") != 0) {
		lep1_p4_branch = tree->GetBranch("lep1_p4");
		lep1_p4_branch->SetAddress(&lep1_p4_);
	}
	lep1_mcp4_branch = 0;
	if (tree->GetBranch("lep1_mcp4") != 0) {
		lep1_mcp4_branch = tree->GetBranch("lep1_mcp4");
		lep1_mcp4_branch->SetAddress(&lep1_mcp4_);
	}
	lep1_mc3p4_branch = 0;
	if (tree->GetBranch("lep1_mc3p4") != 0) {
		lep1_mc3p4_branch = tree->GetBranch("lep1_mc3p4");
		lep1_mc3p4_branch->SetAddress(&lep1_mc3p4_);
	}
	lep1_mc_momp4_branch = 0;
	if (tree->GetBranch("lep1_mc_momp4") != 0) {
		lep1_mc_momp4_branch = tree->GetBranch("lep1_mc_momp4");
		lep1_mc_momp4_branch->SetAddress(&lep1_mc_momp4_);
	}
	lep1_gsf_p4_branch = 0;
	if (tree->GetBranch("lep1_gsf_p4") != 0) {
		lep1_gsf_p4_branch = tree->GetBranch("lep1_gsf_p4");
		lep1_gsf_p4_branch->SetAddress(&lep1_gsf_p4_);
	}
	lep1_ctf_p4_branch = 0;
	if (tree->GetBranch("lep1_ctf_p4") != 0) {
		lep1_ctf_p4_branch = tree->GetBranch("lep1_ctf_p4");
		lep1_ctf_p4_branch->SetAddress(&lep1_ctf_p4_);
	}
	lep1_sc_p4_branch = 0;
	if (tree->GetBranch("lep1_sc_p4") != 0) {
		lep1_sc_p4_branch = tree->GetBranch("lep1_sc_p4");
		lep1_sc_p4_branch->SetAddress(&lep1_sc_p4_);
	}
	lep1_gfit_p4_branch = 0;
	if (tree->GetBranch("lep1_gfit_p4") != 0) {
		lep1_gfit_p4_branch = tree->GetBranch("lep1_gfit_p4");
		lep1_gfit_p4_branch->SetAddress(&lep1_gfit_p4_);
	}
	lep2_p4_branch = 0;
	if (tree->GetBranch("lep2_p4") != 0) {
		lep2_p4_branch = tree->GetBranch("lep2_p4");
		lep2_p4_branch->SetAddress(&lep2_p4_);
	}
	lep2_mcp4_branch = 0;
	if (tree->GetBranch("lep2_mcp4") != 0) {
		lep2_mcp4_branch = tree->GetBranch("lep2_mcp4");
		lep2_mcp4_branch->SetAddress(&lep2_mcp4_);
	}
	lep2_mc3p4_branch = 0;
	if (tree->GetBranch("lep2_mc3p4") != 0) {
		lep2_mc3p4_branch = tree->GetBranch("lep2_mc3p4");
		lep2_mc3p4_branch->SetAddress(&lep2_mc3p4_);
	}
	lep2_mc_momp4_branch = 0;
	if (tree->GetBranch("lep2_mc_momp4") != 0) {
		lep2_mc_momp4_branch = tree->GetBranch("lep2_mc_momp4");
		lep2_mc_momp4_branch->SetAddress(&lep2_mc_momp4_);
	}
	lep2_gsf_p4_branch = 0;
	if (tree->GetBranch("lep2_gsf_p4") != 0) {
		lep2_gsf_p4_branch = tree->GetBranch("lep2_gsf_p4");
		lep2_gsf_p4_branch->SetAddress(&lep2_gsf_p4_);
	}
	lep2_ctf_p4_branch = 0;
	if (tree->GetBranch("lep2_ctf_p4") != 0) {
		lep2_ctf_p4_branch = tree->GetBranch("lep2_ctf_p4");
		lep2_ctf_p4_branch->SetAddress(&lep2_ctf_p4_);
	}
	lep2_sc_p4_branch = 0;
	if (tree->GetBranch("lep2_sc_p4") != 0) {
		lep2_sc_p4_branch = tree->GetBranch("lep2_sc_p4");
		lep2_sc_p4_branch->SetAddress(&lep2_sc_p4_);
	}
	lep2_gfit_p4_branch = 0;
	if (tree->GetBranch("lep2_gfit_p4") != 0) {
		lep2_gfit_p4_branch = tree->GetBranch("lep2_gfit_p4");
		lep2_gfit_p4_branch->SetAddress(&lep2_gfit_p4_);
	}
	dilep_p4_branch = 0;
	if (tree->GetBranch("dilep_p4") != 0) {
		dilep_p4_branch = tree->GetBranch("dilep_p4");
		dilep_p4_branch->SetAddress(&dilep_p4_);
	}
	lep1_nearbjet_p4_branch = 0;
	if (tree->GetBranch("lep1_nearbjet_p4") != 0) {
		lep1_nearbjet_p4_branch = tree->GetBranch("lep1_nearbjet_p4");
		lep1_nearbjet_p4_branch->SetAddress(&lep1_nearbjet_p4_);
	}
	lep1_nearjet_p4_branch = 0;
	if (tree->GetBranch("lep1_nearjet_p4") != 0) {
		lep1_nearjet_p4_branch = tree->GetBranch("lep1_nearjet_p4");
		lep1_nearjet_p4_branch->SetAddress(&lep1_nearjet_p4_);
	}
	lep2_nearbjet_p4_branch = 0;
	if (tree->GetBranch("lep2_nearbjet_p4") != 0) {
		lep2_nearbjet_p4_branch = tree->GetBranch("lep2_nearbjet_p4");
		lep2_nearbjet_p4_branch->SetAddress(&lep2_nearbjet_p4_);
	}
	lep2_nearjet_p4_branch = 0;
	if (tree->GetBranch("lep2_nearjet_p4") != 0) {
		lep2_nearjet_p4_branch = tree->GetBranch("lep2_nearjet_p4");
		lep2_nearjet_p4_branch->SetAddress(&lep2_nearjet_p4_);
	}
	vgenb_p4_branch = 0;
	if (tree->GetBranch("vgenb_p4") != 0) {
		vgenb_p4_branch = tree->GetBranch("vgenb_p4");
		vgenb_p4_branch->SetAddress(&vgenb_p4_);
	}
	vjets_p4_branch = 0;
	if (tree->GetBranch("vjets_p4") != 0) {
		vjets_p4_branch = tree->GetBranch("vjets_p4");
		vjets_p4_branch->SetAddress(&vjets_p4_);
	}
	vgenjets_p4_branch = 0;
	if (tree->GetBranch("vgenjets_p4") != 0) {
		vgenjets_p4_branch = tree->GetBranch("vgenjets_p4");
		vgenjets_p4_branch->SetAddress(&vgenjets_p4_);
	}
	vjets_nearjet_p4_branch = 0;
	if (tree->GetBranch("vjets_nearjet_p4") != 0) {
		vjets_nearjet_p4_branch = tree->GetBranch("vjets_nearjet_p4");
		vjets_nearjet_p4_branch->SetAddress(&vjets_nearjet_p4_);
	}
	vbjets_p4_branch = 0;
	if (tree->GetBranch("vbjets_p4") != 0) {
		vbjets_p4_branch = tree->GetBranch("vbjets_p4");
		vbjets_p4_branch->SetAddress(&vbjets_p4_);
	}
	vbjets_nearjet_p4_branch = 0;
	if (tree->GetBranch("vbjets_nearjet_p4") != 0) {
		vbjets_nearjet_p4_branch = tree->GetBranch("vbjets_nearjet_p4");
		vbjets_nearjet_p4_branch->SetAddress(&vbjets_nearjet_p4_);
	}
  tree->SetMakeClass(1);
	run_branch = 0;
	if (tree->GetBranch("run") != 0) {
		run_branch = tree->GetBranch("run");
		run_branch->SetAddress(&run_);
	}
	ls_branch = 0;
	if (tree->GetBranch("ls") != 0) {
		ls_branch = tree->GetBranch("ls");
		ls_branch->SetAddress(&ls_);
	}
	evt_branch = 0;
	if (tree->GetBranch("evt") != 0) {
		evt_branch = tree->GetBranch("evt");
		evt_branch->SetAddress(&evt_);
	}
	is_real_data_branch = 0;
	if (tree->GetBranch("is_real_data") != 0) {
		is_real_data_branch = tree->GetBranch("is_real_data");
		is_real_data_branch->SetAddress(&is_real_data_);
	}
	sample_branch = 0;
	if (tree->GetBranch("sample") != 0) {
		sample_branch = tree->GetBranch("sample");
		sample_branch->SetAddress(&sample_);
	}
	nvtxs_branch = 0;
	if (tree->GetBranch("nvtxs") != 0) {
		nvtxs_branch = tree->GetBranch("nvtxs");
		nvtxs_branch->SetAddress(&nvtxs_);
	}
	vtx_idx_branch = 0;
	if (tree->GetBranch("vtx_idx") != 0) {
		vtx_idx_branch = tree->GetBranch("vtx_idx");
		vtx_idx_branch->SetAddress(&vtx_idx_);
	}
	pfmet_branch = 0;
	if (tree->GetBranch("pfmet") != 0) {
		pfmet_branch = tree->GetBranch("pfmet");
		pfmet_branch->SetAddress(&pfmet_);
	}
	pfmet_phi_branch = 0;
	if (tree->GetBranch("pfmet_phi") != 0) {
		pfmet_phi_branch = tree->GetBranch("pfmet_phi");
		pfmet_phi_branch->SetAddress(&pfmet_phi_);
	}
	corpfmet_branch = 0;
	if (tree->GetBranch("corpfmet") != 0) {
		corpfmet_branch = tree->GetBranch("corpfmet");
		corpfmet_branch->SetAddress(&corpfmet_);
	}
	corpfmet_phi_branch = 0;
	if (tree->GetBranch("corpfmet_phi") != 0) {
		corpfmet_phi_branch = tree->GetBranch("corpfmet_phi");
		corpfmet_phi_branch->SetAddress(&corpfmet_phi_);
	}
	scale1fb_branch = 0;
	if (tree->GetBranch("scale1fb") != 0) {
		scale1fb_branch = tree->GetBranch("scale1fb");
		scale1fb_branch->SetAddress(&scale1fb_);
	}
	xsec_branch = 0;
	if (tree->GetBranch("xsec") != 0) {
		xsec_branch = tree->GetBranch("xsec");
		xsec_branch->SetAddress(&xsec_);
	}
	kfactor_branch = 0;
	if (tree->GetBranch("kfactor") != 0) {
		kfactor_branch = tree->GetBranch("kfactor");
		kfactor_branch->SetAddress(&kfactor_);
	}
	gen_met_branch = 0;
	if (tree->GetBranch("gen_met") != 0) {
		gen_met_branch = tree->GetBranch("gen_met");
		gen_met_branch->SetAddress(&gen_met_);
	}
	gen_met_phi_branch = 0;
	if (tree->GetBranch("gen_met_phi") != 0) {
		gen_met_phi_branch = tree->GetBranch("gen_met_phi");
		gen_met_phi_branch->SetAddress(&gen_met_phi_);
	}
	lep1_passes_id_branch = 0;
	if (tree->GetBranch("lep1_passes_id") != 0) {
		lep1_passes_id_branch = tree->GetBranch("lep1_passes_id");
		lep1_passes_id_branch->SetAddress(&lep1_passes_id_);
	}
	lep1_passes_iso_branch = 0;
	if (tree->GetBranch("lep1_passes_iso") != 0) {
		lep1_passes_iso_branch = tree->GetBranch("lep1_passes_iso");
		lep1_passes_iso_branch->SetAddress(&lep1_passes_iso_);
	}
	lep1_is_num_branch = 0;
	if (tree->GetBranch("lep1_is_num") != 0) {
		lep1_is_num_branch = tree->GetBranch("lep1_is_num");
		lep1_is_num_branch->SetAddress(&lep1_is_num_);
	}
	lep1_is_fo_branch = 0;
	if (tree->GetBranch("lep1_is_fo") != 0) {
		lep1_is_fo_branch = tree->GetBranch("lep1_is_fo");
		lep1_is_fo_branch->SetAddress(&lep1_is_fo_);
	}
	lep1_charge_branch = 0;
	if (tree->GetBranch("lep1_charge") != 0) {
		lep1_charge_branch = tree->GetBranch("lep1_charge");
		lep1_charge_branch->SetAddress(&lep1_charge_);
	}
	lep1_pdgid_branch = 0;
	if (tree->GetBranch("lep1_pdgid") != 0) {
		lep1_pdgid_branch = tree->GetBranch("lep1_pdgid");
		lep1_pdgid_branch->SetAddress(&lep1_pdgid_);
	}
	lep1_type_branch = 0;
	if (tree->GetBranch("lep1_type") != 0) {
		lep1_type_branch = tree->GetBranch("lep1_type");
		lep1_type_branch->SetAddress(&lep1_type_);
	}
	lep1_d0_branch = 0;
	if (tree->GetBranch("lep1_d0") != 0) {
		lep1_d0_branch = tree->GetBranch("lep1_d0");
		lep1_d0_branch->SetAddress(&lep1_d0_);
	}
	lep1_dz_branch = 0;
	if (tree->GetBranch("lep1_dz") != 0) {
		lep1_dz_branch = tree->GetBranch("lep1_dz");
		lep1_dz_branch->SetAddress(&lep1_dz_);
	}
	lep1_mt_branch = 0;
	if (tree->GetBranch("lep1_mt") != 0) {
		lep1_mt_branch = tree->GetBranch("lep1_mt");
		lep1_mt_branch->SetAddress(&lep1_mt_);
	}
	lep1_corpfiso_branch = 0;
	if (tree->GetBranch("lep1_corpfiso") != 0) {
		lep1_corpfiso_branch = tree->GetBranch("lep1_corpfiso");
		lep1_corpfiso_branch->SetAddress(&lep1_corpfiso_);
	}
	lep1_pfiso_branch = 0;
	if (tree->GetBranch("lep1_pfiso") != 0) {
		lep1_pfiso_branch = tree->GetBranch("lep1_pfiso");
		lep1_pfiso_branch->SetAddress(&lep1_pfiso_);
	}
	lep1_chiso_branch = 0;
	if (tree->GetBranch("lep1_chiso") != 0) {
		lep1_chiso_branch = tree->GetBranch("lep1_chiso");
		lep1_chiso_branch->SetAddress(&lep1_chiso_);
	}
	lep1_emiso_branch = 0;
	if (tree->GetBranch("lep1_emiso") != 0) {
		lep1_emiso_branch = tree->GetBranch("lep1_emiso");
		lep1_emiso_branch->SetAddress(&lep1_emiso_);
	}
	lep1_nhiso_branch = 0;
	if (tree->GetBranch("lep1_nhiso") != 0) {
		lep1_nhiso_branch = tree->GetBranch("lep1_nhiso");
		lep1_nhiso_branch->SetAddress(&lep1_nhiso_);
	}
	lep1_corpfiso04_branch = 0;
	if (tree->GetBranch("lep1_corpfiso04") != 0) {
		lep1_corpfiso04_branch = tree->GetBranch("lep1_corpfiso04");
		lep1_corpfiso04_branch->SetAddress(&lep1_corpfiso04_);
	}
	lep1_pfiso04_branch = 0;
	if (tree->GetBranch("lep1_pfiso04") != 0) {
		lep1_pfiso04_branch = tree->GetBranch("lep1_pfiso04");
		lep1_pfiso04_branch->SetAddress(&lep1_pfiso04_);
	}
	lep1_chiso04_branch = 0;
	if (tree->GetBranch("lep1_chiso04") != 0) {
		lep1_chiso04_branch = tree->GetBranch("lep1_chiso04");
		lep1_chiso04_branch->SetAddress(&lep1_chiso04_);
	}
	lep1_emiso04_branch = 0;
	if (tree->GetBranch("lep1_emiso04") != 0) {
		lep1_emiso04_branch = tree->GetBranch("lep1_emiso04");
		lep1_emiso04_branch->SetAddress(&lep1_emiso04_);
	}
	lep1_nhiso04_branch = 0;
	if (tree->GetBranch("lep1_nhiso04") != 0) {
		lep1_nhiso04_branch = tree->GetBranch("lep1_nhiso04");
		lep1_nhiso04_branch->SetAddress(&lep1_nhiso04_);
	}
	lep1_cordetiso_branch = 0;
	if (tree->GetBranch("lep1_cordetiso") != 0) {
		lep1_cordetiso_branch = tree->GetBranch("lep1_cordetiso");
		lep1_cordetiso_branch->SetAddress(&lep1_cordetiso_);
	}
	lep1_detiso_branch = 0;
	if (tree->GetBranch("lep1_detiso") != 0) {
		lep1_detiso_branch = tree->GetBranch("lep1_detiso");
		lep1_detiso_branch->SetAddress(&lep1_detiso_);
	}
	lep1_trkiso_branch = 0;
	if (tree->GetBranch("lep1_trkiso") != 0) {
		lep1_trkiso_branch = tree->GetBranch("lep1_trkiso");
		lep1_trkiso_branch->SetAddress(&lep1_trkiso_);
	}
	lep1_ecaliso_branch = 0;
	if (tree->GetBranch("lep1_ecaliso") != 0) {
		lep1_ecaliso_branch = tree->GetBranch("lep1_ecaliso");
		lep1_ecaliso_branch->SetAddress(&lep1_ecaliso_);
	}
	lep1_hcaliso_branch = 0;
	if (tree->GetBranch("lep1_hcaliso") != 0) {
		lep1_hcaliso_branch = tree->GetBranch("lep1_hcaliso");
		lep1_hcaliso_branch->SetAddress(&lep1_hcaliso_);
	}
	lep1_cordetiso04_branch = 0;
	if (tree->GetBranch("lep1_cordetiso04") != 0) {
		lep1_cordetiso04_branch = tree->GetBranch("lep1_cordetiso04");
		lep1_cordetiso04_branch->SetAddress(&lep1_cordetiso04_);
	}
	lep1_detiso04_branch = 0;
	if (tree->GetBranch("lep1_detiso04") != 0) {
		lep1_detiso04_branch = tree->GetBranch("lep1_detiso04");
		lep1_detiso04_branch->SetAddress(&lep1_detiso04_);
	}
	lep1_trkiso04_branch = 0;
	if (tree->GetBranch("lep1_trkiso04") != 0) {
		lep1_trkiso04_branch = tree->GetBranch("lep1_trkiso04");
		lep1_trkiso04_branch->SetAddress(&lep1_trkiso04_);
	}
	lep1_ecaliso04_branch = 0;
	if (tree->GetBranch("lep1_ecaliso04") != 0) {
		lep1_ecaliso04_branch = tree->GetBranch("lep1_ecaliso04");
		lep1_ecaliso04_branch->SetAddress(&lep1_ecaliso04_);
	}
	lep1_hcaliso04_branch = 0;
	if (tree->GetBranch("lep1_hcaliso04") != 0) {
		lep1_hcaliso04_branch = tree->GetBranch("lep1_hcaliso04");
		lep1_hcaliso04_branch->SetAddress(&lep1_hcaliso04_);
	}
	lep1_effarea_branch = 0;
	if (tree->GetBranch("lep1_effarea") != 0) {
		lep1_effarea_branch = tree->GetBranch("lep1_effarea");
		lep1_effarea_branch->SetAddress(&lep1_effarea_);
	}
	lep1_effarea04_branch = 0;
	if (tree->GetBranch("lep1_effarea04") != 0) {
		lep1_effarea04_branch = tree->GetBranch("lep1_effarea04");
		lep1_effarea04_branch->SetAddress(&lep1_effarea04_);
	}
	lep1_dbeta_branch = 0;
	if (tree->GetBranch("lep1_dbeta") != 0) {
		lep1_dbeta_branch = tree->GetBranch("lep1_dbeta");
		lep1_dbeta_branch->SetAddress(&lep1_dbeta_);
	}
	lep1_dbeta04_branch = 0;
	if (tree->GetBranch("lep1_dbeta04") != 0) {
		lep1_dbeta04_branch = tree->GetBranch("lep1_dbeta04");
		lep1_dbeta04_branch->SetAddress(&lep1_dbeta04_);
	}
	lep1_sf_lepeff_branch = 0;
	if (tree->GetBranch("lep1_sf_lepeff") != 0) {
		lep1_sf_lepeff_branch = tree->GetBranch("lep1_sf_lepeff");
		lep1_sf_lepeff_branch->SetAddress(&lep1_sf_lepeff_);
	}
	lep1_sf_trig_branch = 0;
	if (tree->GetBranch("lep1_sf_trig") != 0) {
		lep1_sf_trig_branch = tree->GetBranch("lep1_sf_trig");
		lep1_sf_trig_branch->SetAddress(&lep1_sf_trig_);
	}
	lep1_mcid_branch = 0;
	if (tree->GetBranch("lep1_mcid") != 0) {
		lep1_mcid_branch = tree->GetBranch("lep1_mcid");
		lep1_mcid_branch->SetAddress(&lep1_mcid_);
	}
	lep1_mc3id_branch = 0;
	if (tree->GetBranch("lep1_mc3id") != 0) {
		lep1_mc3id_branch = tree->GetBranch("lep1_mc3id");
		lep1_mc3id_branch->SetAddress(&lep1_mc3id_);
	}
	lep1_momid_branch = 0;
	if (tree->GetBranch("lep1_momid") != 0) {
		lep1_momid_branch = tree->GetBranch("lep1_momid");
		lep1_momid_branch->SetAddress(&lep1_momid_);
	}
	lep1_mc3_momid_branch = 0;
	if (tree->GetBranch("lep1_mc3_momid") != 0) {
		lep1_mc3_momid_branch = tree->GetBranch("lep1_mc3_momid");
		lep1_mc3_momid_branch->SetAddress(&lep1_mc3_momid_);
	}
	lep1_q3agree_branch = 0;
	if (tree->GetBranch("lep1_q3agree") != 0) {
		lep1_q3agree_branch = tree->GetBranch("lep1_q3agree");
		lep1_q3agree_branch->SetAddress(&lep1_q3agree_);
	}
	lep1_is_conv_branch = 0;
	if (tree->GetBranch("lep1_is_conv") != 0) {
		lep1_is_conv_branch = tree->GetBranch("lep1_is_conv");
		lep1_is_conv_branch->SetAddress(&lep1_is_conv_);
	}
	lep1_qsc_branch = 0;
	if (tree->GetBranch("lep1_qsc") != 0) {
		lep1_qsc_branch = tree->GetBranch("lep1_qsc");
		lep1_qsc_branch->SetAddress(&lep1_qsc_);
	}
	lep1_qctf_branch = 0;
	if (tree->GetBranch("lep1_qctf") != 0) {
		lep1_qctf_branch = tree->GetBranch("lep1_qctf");
		lep1_qctf_branch->SetAddress(&lep1_qctf_);
	}
	lep1_qgsf_branch = 0;
	if (tree->GetBranch("lep1_qgsf") != 0) {
		lep1_qgsf_branch = tree->GetBranch("lep1_qgsf");
		lep1_qgsf_branch->SetAddress(&lep1_qgsf_);
	}
	lep1_nmhits_branch = 0;
	if (tree->GetBranch("lep1_nmhits") != 0) {
		lep1_nmhits_branch = tree->GetBranch("lep1_nmhits");
		lep1_nmhits_branch->SetAddress(&lep1_nmhits_);
	}
	lep1_eleid_veto_branch = 0;
	if (tree->GetBranch("lep1_eleid_veto") != 0) {
		lep1_eleid_veto_branch = tree->GetBranch("lep1_eleid_veto");
		lep1_eleid_veto_branch->SetAddress(&lep1_eleid_veto_);
	}
	lep1_eleid_loose_branch = 0;
	if (tree->GetBranch("lep1_eleid_loose") != 0) {
		lep1_eleid_loose_branch = tree->GetBranch("lep1_eleid_loose");
		lep1_eleid_loose_branch->SetAddress(&lep1_eleid_loose_);
	}
	lep1_eleid_medium_branch = 0;
	if (tree->GetBranch("lep1_eleid_medium") != 0) {
		lep1_eleid_medium_branch = tree->GetBranch("lep1_eleid_medium");
		lep1_eleid_medium_branch->SetAddress(&lep1_eleid_medium_);
	}
	lep1_eleid_tight_branch = 0;
	if (tree->GetBranch("lep1_eleid_tight") != 0) {
		lep1_eleid_tight_branch = tree->GetBranch("lep1_eleid_tight");
		lep1_eleid_tight_branch->SetAddress(&lep1_eleid_tight_);
	}
	lep1_dphiin_branch = 0;
	if (tree->GetBranch("lep1_dphiin") != 0) {
		lep1_dphiin_branch = tree->GetBranch("lep1_dphiin");
		lep1_dphiin_branch->SetAddress(&lep1_dphiin_);
	}
	lep1_detain_branch = 0;
	if (tree->GetBranch("lep1_detain") != 0) {
		lep1_detain_branch = tree->GetBranch("lep1_detain");
		lep1_detain_branch->SetAddress(&lep1_detain_);
	}
	lep1_sieie_branch = 0;
	if (tree->GetBranch("lep1_sieie") != 0) {
		lep1_sieie_branch = tree->GetBranch("lep1_sieie");
		lep1_sieie_branch->SetAddress(&lep1_sieie_);
	}
	lep1_hoe_branch = 0;
	if (tree->GetBranch("lep1_hoe") != 0) {
		lep1_hoe_branch = tree->GetBranch("lep1_hoe");
		lep1_hoe_branch->SetAddress(&lep1_hoe_);
	}
	lep1_ooemoop_branch = 0;
	if (tree->GetBranch("lep1_ooemoop") != 0) {
		lep1_ooemoop_branch = tree->GetBranch("lep1_ooemoop");
		lep1_ooemoop_branch->SetAddress(&lep1_ooemoop_);
	}
	lep1_conv_dist_branch = 0;
	if (tree->GetBranch("lep1_conv_dist") != 0) {
		lep1_conv_dist_branch = tree->GetBranch("lep1_conv_dist");
		lep1_conv_dist_branch->SetAddress(&lep1_conv_dist_);
	}
	lep1_conv_dcot_branch = 0;
	if (tree->GetBranch("lep1_conv_dcot") != 0) {
		lep1_conv_dcot_branch = tree->GetBranch("lep1_conv_dcot");
		lep1_conv_dcot_branch->SetAddress(&lep1_conv_dcot_);
	}
	lep1_is_global_branch = 0;
	if (tree->GetBranch("lep1_is_global") != 0) {
		lep1_is_global_branch = tree->GetBranch("lep1_is_global");
		lep1_is_global_branch->SetAddress(&lep1_is_global_);
	}
	lep1_is_tracker_branch = 0;
	if (tree->GetBranch("lep1_is_tracker") != 0) {
		lep1_is_tracker_branch = tree->GetBranch("lep1_is_tracker");
		lep1_is_tracker_branch->SetAddress(&lep1_is_tracker_);
	}
	lep1_is_stamu_branch = 0;
	if (tree->GetBranch("lep1_is_stamu") != 0) {
		lep1_is_stamu_branch = tree->GetBranch("lep1_is_stamu");
		lep1_is_stamu_branch->SetAddress(&lep1_is_stamu_);
	}
	lep1_is_pfmu_branch = 0;
	if (tree->GetBranch("lep1_is_pfmu") != 0) {
		lep1_is_pfmu_branch = tree->GetBranch("lep1_is_pfmu");
		lep1_is_pfmu_branch->SetAddress(&lep1_is_pfmu_);
	}
	lep1_is_loosemu_branch = 0;
	if (tree->GetBranch("lep1_is_loosemu") != 0) {
		lep1_is_loosemu_branch = tree->GetBranch("lep1_is_loosemu");
		lep1_is_loosemu_branch->SetAddress(&lep1_is_loosemu_);
	}
	lep1_is_tightmu_branch = 0;
	if (tree->GetBranch("lep1_is_tightmu") != 0) {
		lep1_is_tightmu_branch = tree->GetBranch("lep1_is_tightmu");
		lep1_is_tightmu_branch->SetAddress(&lep1_is_tightmu_);
	}
	lep1_npixelhits_branch = 0;
	if (tree->GetBranch("lep1_npixelhits") != 0) {
		lep1_npixelhits_branch = tree->GetBranch("lep1_npixelhits");
		lep1_npixelhits_branch->SetAddress(&lep1_npixelhits_);
	}
	lep1_nsihits_branch = 0;
	if (tree->GetBranch("lep1_nsihits") != 0) {
		lep1_nsihits_branch = tree->GetBranch("lep1_nsihits");
		lep1_nsihits_branch->SetAddress(&lep1_nsihits_);
	}
	lep1_nsilayers_branch = 0;
	if (tree->GetBranch("lep1_nsilayers") != 0) {
		lep1_nsilayers_branch = tree->GetBranch("lep1_nsilayers");
		lep1_nsilayers_branch->SetAddress(&lep1_nsilayers_);
	}
	lep1_nstahits_branch = 0;
	if (tree->GetBranch("lep1_nstahits") != 0) {
		lep1_nstahits_branch = tree->GetBranch("lep1_nstahits");
		lep1_nstahits_branch->SetAddress(&lep1_nstahits_);
	}
	lep1_nstations_branch = 0;
	if (tree->GetBranch("lep1_nstations") != 0) {
		lep1_nstations_branch = tree->GetBranch("lep1_nstations");
		lep1_nstations_branch->SetAddress(&lep1_nstations_);
	}
	lep1_chi2_branch = 0;
	if (tree->GetBranch("lep1_chi2") != 0) {
		lep1_chi2_branch = tree->GetBranch("lep1_chi2");
		lep1_chi2_branch->SetAddress(&lep1_chi2_);
	}
	lep1_ndof_branch = 0;
	if (tree->GetBranch("lep1_ndof") != 0) {
		lep1_ndof_branch = tree->GetBranch("lep1_ndof");
		lep1_ndof_branch->SetAddress(&lep1_ndof_);
	}
	lep1_pterr_branch = 0;
	if (tree->GetBranch("lep1_pterr") != 0) {
		lep1_pterr_branch = tree->GetBranch("lep1_pterr");
		lep1_pterr_branch->SetAddress(&lep1_pterr_);
	}
	lep1_ecal_vetodep_branch = 0;
	if (tree->GetBranch("lep1_ecal_vetodep") != 0) {
		lep1_ecal_vetodep_branch = tree->GetBranch("lep1_ecal_vetodep");
		lep1_ecal_vetodep_branch->SetAddress(&lep1_ecal_vetodep_);
	}
	lep1_hcal_vetodep_branch = 0;
	if (tree->GetBranch("lep1_hcal_vetodep") != 0) {
		lep1_hcal_vetodep_branch = tree->GetBranch("lep1_hcal_vetodep");
		lep1_hcal_vetodep_branch->SetAddress(&lep1_hcal_vetodep_);
	}
	lep2_passes_id_branch = 0;
	if (tree->GetBranch("lep2_passes_id") != 0) {
		lep2_passes_id_branch = tree->GetBranch("lep2_passes_id");
		lep2_passes_id_branch->SetAddress(&lep2_passes_id_);
	}
	lep2_passes_iso_branch = 0;
	if (tree->GetBranch("lep2_passes_iso") != 0) {
		lep2_passes_iso_branch = tree->GetBranch("lep2_passes_iso");
		lep2_passes_iso_branch->SetAddress(&lep2_passes_iso_);
	}
	lep2_is_num_branch = 0;
	if (tree->GetBranch("lep2_is_num") != 0) {
		lep2_is_num_branch = tree->GetBranch("lep2_is_num");
		lep2_is_num_branch->SetAddress(&lep2_is_num_);
	}
	lep2_is_fo_branch = 0;
	if (tree->GetBranch("lep2_is_fo") != 0) {
		lep2_is_fo_branch = tree->GetBranch("lep2_is_fo");
		lep2_is_fo_branch->SetAddress(&lep2_is_fo_);
	}
	lep2_charge_branch = 0;
	if (tree->GetBranch("lep2_charge") != 0) {
		lep2_charge_branch = tree->GetBranch("lep2_charge");
		lep2_charge_branch->SetAddress(&lep2_charge_);
	}
	lep2_pdgid_branch = 0;
	if (tree->GetBranch("lep2_pdgid") != 0) {
		lep2_pdgid_branch = tree->GetBranch("lep2_pdgid");
		lep2_pdgid_branch->SetAddress(&lep2_pdgid_);
	}
	lep2_type_branch = 0;
	if (tree->GetBranch("lep2_type") != 0) {
		lep2_type_branch = tree->GetBranch("lep2_type");
		lep2_type_branch->SetAddress(&lep2_type_);
	}
	lep2_d0_branch = 0;
	if (tree->GetBranch("lep2_d0") != 0) {
		lep2_d0_branch = tree->GetBranch("lep2_d0");
		lep2_d0_branch->SetAddress(&lep2_d0_);
	}
	lep2_dz_branch = 0;
	if (tree->GetBranch("lep2_dz") != 0) {
		lep2_dz_branch = tree->GetBranch("lep2_dz");
		lep2_dz_branch->SetAddress(&lep2_dz_);
	}
	lep2_mt_branch = 0;
	if (tree->GetBranch("lep2_mt") != 0) {
		lep2_mt_branch = tree->GetBranch("lep2_mt");
		lep2_mt_branch->SetAddress(&lep2_mt_);
	}
	lep2_corpfiso_branch = 0;
	if (tree->GetBranch("lep2_corpfiso") != 0) {
		lep2_corpfiso_branch = tree->GetBranch("lep2_corpfiso");
		lep2_corpfiso_branch->SetAddress(&lep2_corpfiso_);
	}
	lep2_pfiso_branch = 0;
	if (tree->GetBranch("lep2_pfiso") != 0) {
		lep2_pfiso_branch = tree->GetBranch("lep2_pfiso");
		lep2_pfiso_branch->SetAddress(&lep2_pfiso_);
	}
	lep2_chiso_branch = 0;
	if (tree->GetBranch("lep2_chiso") != 0) {
		lep2_chiso_branch = tree->GetBranch("lep2_chiso");
		lep2_chiso_branch->SetAddress(&lep2_chiso_);
	}
	lep2_emiso_branch = 0;
	if (tree->GetBranch("lep2_emiso") != 0) {
		lep2_emiso_branch = tree->GetBranch("lep2_emiso");
		lep2_emiso_branch->SetAddress(&lep2_emiso_);
	}
	lep2_nhiso_branch = 0;
	if (tree->GetBranch("lep2_nhiso") != 0) {
		lep2_nhiso_branch = tree->GetBranch("lep2_nhiso");
		lep2_nhiso_branch->SetAddress(&lep2_nhiso_);
	}
	lep2_corpfiso04_branch = 0;
	if (tree->GetBranch("lep2_corpfiso04") != 0) {
		lep2_corpfiso04_branch = tree->GetBranch("lep2_corpfiso04");
		lep2_corpfiso04_branch->SetAddress(&lep2_corpfiso04_);
	}
	lep2_pfiso04_branch = 0;
	if (tree->GetBranch("lep2_pfiso04") != 0) {
		lep2_pfiso04_branch = tree->GetBranch("lep2_pfiso04");
		lep2_pfiso04_branch->SetAddress(&lep2_pfiso04_);
	}
	lep2_chiso04_branch = 0;
	if (tree->GetBranch("lep2_chiso04") != 0) {
		lep2_chiso04_branch = tree->GetBranch("lep2_chiso04");
		lep2_chiso04_branch->SetAddress(&lep2_chiso04_);
	}
	lep2_emiso04_branch = 0;
	if (tree->GetBranch("lep2_emiso04") != 0) {
		lep2_emiso04_branch = tree->GetBranch("lep2_emiso04");
		lep2_emiso04_branch->SetAddress(&lep2_emiso04_);
	}
	lep2_nhiso04_branch = 0;
	if (tree->GetBranch("lep2_nhiso04") != 0) {
		lep2_nhiso04_branch = tree->GetBranch("lep2_nhiso04");
		lep2_nhiso04_branch->SetAddress(&lep2_nhiso04_);
	}
	lep2_cordetiso_branch = 0;
	if (tree->GetBranch("lep2_cordetiso") != 0) {
		lep2_cordetiso_branch = tree->GetBranch("lep2_cordetiso");
		lep2_cordetiso_branch->SetAddress(&lep2_cordetiso_);
	}
	lep2_detiso_branch = 0;
	if (tree->GetBranch("lep2_detiso") != 0) {
		lep2_detiso_branch = tree->GetBranch("lep2_detiso");
		lep2_detiso_branch->SetAddress(&lep2_detiso_);
	}
	lep2_trkiso_branch = 0;
	if (tree->GetBranch("lep2_trkiso") != 0) {
		lep2_trkiso_branch = tree->GetBranch("lep2_trkiso");
		lep2_trkiso_branch->SetAddress(&lep2_trkiso_);
	}
	lep2_ecaliso_branch = 0;
	if (tree->GetBranch("lep2_ecaliso") != 0) {
		lep2_ecaliso_branch = tree->GetBranch("lep2_ecaliso");
		lep2_ecaliso_branch->SetAddress(&lep2_ecaliso_);
	}
	lep2_hcaliso_branch = 0;
	if (tree->GetBranch("lep2_hcaliso") != 0) {
		lep2_hcaliso_branch = tree->GetBranch("lep2_hcaliso");
		lep2_hcaliso_branch->SetAddress(&lep2_hcaliso_);
	}
	lep2_cordetiso04_branch = 0;
	if (tree->GetBranch("lep2_cordetiso04") != 0) {
		lep2_cordetiso04_branch = tree->GetBranch("lep2_cordetiso04");
		lep2_cordetiso04_branch->SetAddress(&lep2_cordetiso04_);
	}
	lep2_detiso04_branch = 0;
	if (tree->GetBranch("lep2_detiso04") != 0) {
		lep2_detiso04_branch = tree->GetBranch("lep2_detiso04");
		lep2_detiso04_branch->SetAddress(&lep2_detiso04_);
	}
	lep2_trkiso04_branch = 0;
	if (tree->GetBranch("lep2_trkiso04") != 0) {
		lep2_trkiso04_branch = tree->GetBranch("lep2_trkiso04");
		lep2_trkiso04_branch->SetAddress(&lep2_trkiso04_);
	}
	lep2_ecaliso04_branch = 0;
	if (tree->GetBranch("lep2_ecaliso04") != 0) {
		lep2_ecaliso04_branch = tree->GetBranch("lep2_ecaliso04");
		lep2_ecaliso04_branch->SetAddress(&lep2_ecaliso04_);
	}
	lep2_hcaliso04_branch = 0;
	if (tree->GetBranch("lep2_hcaliso04") != 0) {
		lep2_hcaliso04_branch = tree->GetBranch("lep2_hcaliso04");
		lep2_hcaliso04_branch->SetAddress(&lep2_hcaliso04_);
	}
	lep2_effarea_branch = 0;
	if (tree->GetBranch("lep2_effarea") != 0) {
		lep2_effarea_branch = tree->GetBranch("lep2_effarea");
		lep2_effarea_branch->SetAddress(&lep2_effarea_);
	}
	lep2_effarea04_branch = 0;
	if (tree->GetBranch("lep2_effarea04") != 0) {
		lep2_effarea04_branch = tree->GetBranch("lep2_effarea04");
		lep2_effarea04_branch->SetAddress(&lep2_effarea04_);
	}
	lep2_dbeta_branch = 0;
	if (tree->GetBranch("lep2_dbeta") != 0) {
		lep2_dbeta_branch = tree->GetBranch("lep2_dbeta");
		lep2_dbeta_branch->SetAddress(&lep2_dbeta_);
	}
	lep2_dbeta04_branch = 0;
	if (tree->GetBranch("lep2_dbeta04") != 0) {
		lep2_dbeta04_branch = tree->GetBranch("lep2_dbeta04");
		lep2_dbeta04_branch->SetAddress(&lep2_dbeta04_);
	}
	lep2_sf_lepeff_branch = 0;
	if (tree->GetBranch("lep2_sf_lepeff") != 0) {
		lep2_sf_lepeff_branch = tree->GetBranch("lep2_sf_lepeff");
		lep2_sf_lepeff_branch->SetAddress(&lep2_sf_lepeff_);
	}
	lep2_sf_trig_branch = 0;
	if (tree->GetBranch("lep2_sf_trig") != 0) {
		lep2_sf_trig_branch = tree->GetBranch("lep2_sf_trig");
		lep2_sf_trig_branch->SetAddress(&lep2_sf_trig_);
	}
	lep2_mcid_branch = 0;
	if (tree->GetBranch("lep2_mcid") != 0) {
		lep2_mcid_branch = tree->GetBranch("lep2_mcid");
		lep2_mcid_branch->SetAddress(&lep2_mcid_);
	}
	lep2_mc3id_branch = 0;
	if (tree->GetBranch("lep2_mc3id") != 0) {
		lep2_mc3id_branch = tree->GetBranch("lep2_mc3id");
		lep2_mc3id_branch->SetAddress(&lep2_mc3id_);
	}
	lep2_momid_branch = 0;
	if (tree->GetBranch("lep2_momid") != 0) {
		lep2_momid_branch = tree->GetBranch("lep2_momid");
		lep2_momid_branch->SetAddress(&lep2_momid_);
	}
	lep2_mc3_momid_branch = 0;
	if (tree->GetBranch("lep2_mc3_momid") != 0) {
		lep2_mc3_momid_branch = tree->GetBranch("lep2_mc3_momid");
		lep2_mc3_momid_branch->SetAddress(&lep2_mc3_momid_);
	}
	lep2_q3agree_branch = 0;
	if (tree->GetBranch("lep2_q3agree") != 0) {
		lep2_q3agree_branch = tree->GetBranch("lep2_q3agree");
		lep2_q3agree_branch->SetAddress(&lep2_q3agree_);
	}
	lep2_is_conv_branch = 0;
	if (tree->GetBranch("lep2_is_conv") != 0) {
		lep2_is_conv_branch = tree->GetBranch("lep2_is_conv");
		lep2_is_conv_branch->SetAddress(&lep2_is_conv_);
	}
	lep2_qsc_branch = 0;
	if (tree->GetBranch("lep2_qsc") != 0) {
		lep2_qsc_branch = tree->GetBranch("lep2_qsc");
		lep2_qsc_branch->SetAddress(&lep2_qsc_);
	}
	lep2_qctf_branch = 0;
	if (tree->GetBranch("lep2_qctf") != 0) {
		lep2_qctf_branch = tree->GetBranch("lep2_qctf");
		lep2_qctf_branch->SetAddress(&lep2_qctf_);
	}
	lep2_qgsf_branch = 0;
	if (tree->GetBranch("lep2_qgsf") != 0) {
		lep2_qgsf_branch = tree->GetBranch("lep2_qgsf");
		lep2_qgsf_branch->SetAddress(&lep2_qgsf_);
	}
	lep2_nmhits_branch = 0;
	if (tree->GetBranch("lep2_nmhits") != 0) {
		lep2_nmhits_branch = tree->GetBranch("lep2_nmhits");
		lep2_nmhits_branch->SetAddress(&lep2_nmhits_);
	}
	lep2_eleid_veto_branch = 0;
	if (tree->GetBranch("lep2_eleid_veto") != 0) {
		lep2_eleid_veto_branch = tree->GetBranch("lep2_eleid_veto");
		lep2_eleid_veto_branch->SetAddress(&lep2_eleid_veto_);
	}
	lep2_eleid_loose_branch = 0;
	if (tree->GetBranch("lep2_eleid_loose") != 0) {
		lep2_eleid_loose_branch = tree->GetBranch("lep2_eleid_loose");
		lep2_eleid_loose_branch->SetAddress(&lep2_eleid_loose_);
	}
	lep2_eleid_medium_branch = 0;
	if (tree->GetBranch("lep2_eleid_medium") != 0) {
		lep2_eleid_medium_branch = tree->GetBranch("lep2_eleid_medium");
		lep2_eleid_medium_branch->SetAddress(&lep2_eleid_medium_);
	}
	lep2_eleid_tight_branch = 0;
	if (tree->GetBranch("lep2_eleid_tight") != 0) {
		lep2_eleid_tight_branch = tree->GetBranch("lep2_eleid_tight");
		lep2_eleid_tight_branch->SetAddress(&lep2_eleid_tight_);
	}
	lep2_dphiin_branch = 0;
	if (tree->GetBranch("lep2_dphiin") != 0) {
		lep2_dphiin_branch = tree->GetBranch("lep2_dphiin");
		lep2_dphiin_branch->SetAddress(&lep2_dphiin_);
	}
	lep2_detain_branch = 0;
	if (tree->GetBranch("lep2_detain") != 0) {
		lep2_detain_branch = tree->GetBranch("lep2_detain");
		lep2_detain_branch->SetAddress(&lep2_detain_);
	}
	lep2_sieie_branch = 0;
	if (tree->GetBranch("lep2_sieie") != 0) {
		lep2_sieie_branch = tree->GetBranch("lep2_sieie");
		lep2_sieie_branch->SetAddress(&lep2_sieie_);
	}
	lep2_hoe_branch = 0;
	if (tree->GetBranch("lep2_hoe") != 0) {
		lep2_hoe_branch = tree->GetBranch("lep2_hoe");
		lep2_hoe_branch->SetAddress(&lep2_hoe_);
	}
	lep2_ooemoop_branch = 0;
	if (tree->GetBranch("lep2_ooemoop") != 0) {
		lep2_ooemoop_branch = tree->GetBranch("lep2_ooemoop");
		lep2_ooemoop_branch->SetAddress(&lep2_ooemoop_);
	}
	lep2_conv_dist_branch = 0;
	if (tree->GetBranch("lep2_conv_dist") != 0) {
		lep2_conv_dist_branch = tree->GetBranch("lep2_conv_dist");
		lep2_conv_dist_branch->SetAddress(&lep2_conv_dist_);
	}
	lep2_conv_dcot_branch = 0;
	if (tree->GetBranch("lep2_conv_dcot") != 0) {
		lep2_conv_dcot_branch = tree->GetBranch("lep2_conv_dcot");
		lep2_conv_dcot_branch->SetAddress(&lep2_conv_dcot_);
	}
	lep2_is_global_branch = 0;
	if (tree->GetBranch("lep2_is_global") != 0) {
		lep2_is_global_branch = tree->GetBranch("lep2_is_global");
		lep2_is_global_branch->SetAddress(&lep2_is_global_);
	}
	lep2_is_tracker_branch = 0;
	if (tree->GetBranch("lep2_is_tracker") != 0) {
		lep2_is_tracker_branch = tree->GetBranch("lep2_is_tracker");
		lep2_is_tracker_branch->SetAddress(&lep2_is_tracker_);
	}
	lep2_is_stamu_branch = 0;
	if (tree->GetBranch("lep2_is_stamu") != 0) {
		lep2_is_stamu_branch = tree->GetBranch("lep2_is_stamu");
		lep2_is_stamu_branch->SetAddress(&lep2_is_stamu_);
	}
	lep2_is_pfmu_branch = 0;
	if (tree->GetBranch("lep2_is_pfmu") != 0) {
		lep2_is_pfmu_branch = tree->GetBranch("lep2_is_pfmu");
		lep2_is_pfmu_branch->SetAddress(&lep2_is_pfmu_);
	}
	lep2_is_loosemu_branch = 0;
	if (tree->GetBranch("lep2_is_loosemu") != 0) {
		lep2_is_loosemu_branch = tree->GetBranch("lep2_is_loosemu");
		lep2_is_loosemu_branch->SetAddress(&lep2_is_loosemu_);
	}
	lep2_is_tightmu_branch = 0;
	if (tree->GetBranch("lep2_is_tightmu") != 0) {
		lep2_is_tightmu_branch = tree->GetBranch("lep2_is_tightmu");
		lep2_is_tightmu_branch->SetAddress(&lep2_is_tightmu_);
	}
	lep2_npixelhits_branch = 0;
	if (tree->GetBranch("lep2_npixelhits") != 0) {
		lep2_npixelhits_branch = tree->GetBranch("lep2_npixelhits");
		lep2_npixelhits_branch->SetAddress(&lep2_npixelhits_);
	}
	lep2_nsihits_branch = 0;
	if (tree->GetBranch("lep2_nsihits") != 0) {
		lep2_nsihits_branch = tree->GetBranch("lep2_nsihits");
		lep2_nsihits_branch->SetAddress(&lep2_nsihits_);
	}
	lep2_nsilayers_branch = 0;
	if (tree->GetBranch("lep2_nsilayers") != 0) {
		lep2_nsilayers_branch = tree->GetBranch("lep2_nsilayers");
		lep2_nsilayers_branch->SetAddress(&lep2_nsilayers_);
	}
	lep2_nstahits_branch = 0;
	if (tree->GetBranch("lep2_nstahits") != 0) {
		lep2_nstahits_branch = tree->GetBranch("lep2_nstahits");
		lep2_nstahits_branch->SetAddress(&lep2_nstahits_);
	}
	lep2_nstations_branch = 0;
	if (tree->GetBranch("lep2_nstations") != 0) {
		lep2_nstations_branch = tree->GetBranch("lep2_nstations");
		lep2_nstations_branch->SetAddress(&lep2_nstations_);
	}
	lep2_chi2_branch = 0;
	if (tree->GetBranch("lep2_chi2") != 0) {
		lep2_chi2_branch = tree->GetBranch("lep2_chi2");
		lep2_chi2_branch->SetAddress(&lep2_chi2_);
	}
	lep2_ndof_branch = 0;
	if (tree->GetBranch("lep2_ndof") != 0) {
		lep2_ndof_branch = tree->GetBranch("lep2_ndof");
		lep2_ndof_branch->SetAddress(&lep2_ndof_);
	}
	lep2_pterr_branch = 0;
	if (tree->GetBranch("lep2_pterr") != 0) {
		lep2_pterr_branch = tree->GetBranch("lep2_pterr");
		lep2_pterr_branch->SetAddress(&lep2_pterr_);
	}
	lep2_ecal_vetodep_branch = 0;
	if (tree->GetBranch("lep2_ecal_vetodep") != 0) {
		lep2_ecal_vetodep_branch = tree->GetBranch("lep2_ecal_vetodep");
		lep2_ecal_vetodep_branch->SetAddress(&lep2_ecal_vetodep_);
	}
	lep2_hcal_vetodep_branch = 0;
	if (tree->GetBranch("lep2_hcal_vetodep") != 0) {
		lep2_hcal_vetodep_branch = tree->GetBranch("lep2_hcal_vetodep");
		lep2_hcal_vetodep_branch->SetAddress(&lep2_hcal_vetodep_);
	}
	is_os_branch = 0;
	if (tree->GetBranch("is_os") != 0) {
		is_os_branch = tree->GetBranch("is_os");
		is_os_branch->SetAddress(&is_os_);
	}
	is_ss_branch = 0;
	if (tree->GetBranch("is_ss") != 0) {
		is_ss_branch = tree->GetBranch("is_ss");
		is_ss_branch->SetAddress(&is_ss_);
	}
	dilep_type_branch = 0;
	if (tree->GetBranch("dilep_type") != 0) {
		dilep_type_branch = tree->GetBranch("dilep_type");
		dilep_type_branch->SetAddress(&dilep_type_);
	}
	dilep_gen_type_branch = 0;
	if (tree->GetBranch("dilep_gen_type") != 0) {
		dilep_gen_type_branch = tree->GetBranch("dilep_gen_type");
		dilep_gen_type_branch->SetAddress(&dilep_gen_type_);
	}
	dilep_mass_branch = 0;
	if (tree->GetBranch("dilep_mass") != 0) {
		dilep_mass_branch = tree->GetBranch("dilep_mass");
		dilep_mass_branch->SetAddress(&dilep_mass_);
	}
	dilep_dphi_branch = 0;
	if (tree->GetBranch("dilep_dphi") != 0) {
		dilep_dphi_branch = tree->GetBranch("dilep_dphi");
		dilep_dphi_branch->SetAddress(&dilep_dphi_);
	}
	dilep_deta_branch = 0;
	if (tree->GetBranch("dilep_deta") != 0) {
		dilep_deta_branch = tree->GetBranch("dilep_deta");
		dilep_deta_branch->SetAddress(&dilep_deta_);
	}
	dilep_dr_branch = 0;
	if (tree->GetBranch("dilep_dr") != 0) {
		dilep_dr_branch = tree->GetBranch("dilep_dr");
		dilep_dr_branch->SetAddress(&dilep_dr_);
	}
	fiduciality_branch = 0;
	if (tree->GetBranch("fiduciality") != 0) {
		fiduciality_branch = tree->GetBranch("fiduciality");
		fiduciality_branch->SetAddress(&fiduciality_);
	}
	selection_branch = 0;
	if (tree->GetBranch("selection") != 0) {
		selection_branch = tree->GetBranch("selection");
		selection_branch->SetAddress(&selection_);
	}
	is_good_lumi_branch = 0;
	if (tree->GetBranch("is_good_lumi") != 0) {
		is_good_lumi_branch = tree->GetBranch("is_good_lumi");
		is_good_lumi_branch->SetAddress(&is_good_lumi_);
	}
	njets_branch = 0;
	if (tree->GetBranch("njets") != 0) {
		njets_branch = tree->GetBranch("njets");
		njets_branch->SetAddress(&njets_);
	}
	njets20_branch = 0;
	if (tree->GetBranch("njets20") != 0) {
		njets20_branch = tree->GetBranch("njets20");
		njets20_branch->SetAddress(&njets20_);
	}
	njets30_branch = 0;
	if (tree->GetBranch("njets30") != 0) {
		njets30_branch = tree->GetBranch("njets30");
		njets30_branch->SetAddress(&njets30_);
	}
	nbtags_branch = 0;
	if (tree->GetBranch("nbtags") != 0) {
		nbtags_branch = tree->GetBranch("nbtags");
		nbtags_branch->SetAddress(&nbtags_);
	}
	nbtags20_branch = 0;
	if (tree->GetBranch("nbtags20") != 0) {
		nbtags20_branch = tree->GetBranch("nbtags20");
		nbtags20_branch->SetAddress(&nbtags20_);
	}
	nbtags30_branch = 0;
	if (tree->GetBranch("nbtags30") != 0) {
		nbtags30_branch = tree->GetBranch("nbtags30");
		nbtags30_branch->SetAddress(&nbtags30_);
	}
	vtxw_branch = 0;
	if (tree->GetBranch("vtxw") != 0) {
		vtxw_branch = tree->GetBranch("vtxw");
		vtxw_branch->SetAddress(&vtxw_);
	}
	ht_branch = 0;
	if (tree->GetBranch("ht") != 0) {
		ht_branch = tree->GetBranch("ht");
		ht_branch->SetAddress(&ht_);
	}
	ht20_branch = 0;
	if (tree->GetBranch("ht20") != 0) {
		ht20_branch = tree->GetBranch("ht20");
		ht20_branch->SetAddress(&ht20_);
	}
	ht30_branch = 0;
	if (tree->GetBranch("ht30") != 0) {
		ht30_branch = tree->GetBranch("ht30");
		ht30_branch->SetAddress(&ht30_);
	}
	rho_branch = 0;
	if (tree->GetBranch("rho") != 0) {
		rho_branch = tree->GetBranch("rho");
		rho_branch->SetAddress(&rho_);
	}
	rho_iso_branch = 0;
	if (tree->GetBranch("rho_iso") != 0) {
		rho_iso_branch = tree->GetBranch("rho_iso");
		rho_iso_branch->SetAddress(&rho_iso_);
	}
	trig_mm_branch = 0;
	if (tree->GetBranch("trig_mm") != 0) {
		trig_mm_branch = tree->GetBranch("trig_mm");
		trig_mm_branch->SetAddress(&trig_mm_);
	}
	trig_em_branch = 0;
	if (tree->GetBranch("trig_em") != 0) {
		trig_em_branch = tree->GetBranch("trig_em");
		trig_em_branch->SetAddress(&trig_em_);
	}
	trig_ee_branch = 0;
	if (tree->GetBranch("trig_ee") != 0) {
		trig_ee_branch = tree->GetBranch("trig_ee");
		trig_ee_branch->SetAddress(&trig_ee_);
	}
	sf_dileptrig_branch = 0;
	if (tree->GetBranch("sf_dileptrig") != 0) {
		sf_dileptrig_branch = tree->GetBranch("sf_dileptrig");
		sf_dileptrig_branch->SetAddress(&sf_dileptrig_);
	}
	sf_lepeff_branch = 0;
	if (tree->GetBranch("sf_lepeff") != 0) {
		sf_lepeff_branch = tree->GetBranch("sf_lepeff");
		sf_lepeff_branch->SetAddress(&sf_lepeff_);
	}
	sparm0_branch = 0;
	if (tree->GetBranch("sparm0") != 0) {
		sparm0_branch = tree->GetBranch("sparm0");
		sparm0_branch->SetAddress(&sparm0_);
	}
	sparm1_branch = 0;
	if (tree->GetBranch("sparm1") != 0) {
		sparm1_branch = tree->GetBranch("sparm1");
		sparm1_branch->SetAddress(&sparm1_);
	}
	sparm2_branch = 0;
	if (tree->GetBranch("sparm2") != 0) {
		sparm2_branch = tree->GetBranch("sparm2");
		sparm2_branch->SetAddress(&sparm2_);
	}
	sparm3_branch = 0;
	if (tree->GetBranch("sparm3") != 0) {
		sparm3_branch = tree->GetBranch("sparm3");
		sparm3_branch->SetAddress(&sparm3_);
	}
	is_pp_branch = 0;
	if (tree->GetBranch("is_pp") != 0) {
		is_pp_branch = tree->GetBranch("is_pp");
		is_pp_branch->SetAddress(&is_pp_);
	}
	is_mm_branch = 0;
	if (tree->GetBranch("is_mm") != 0) {
		is_mm_branch = tree->GetBranch("is_mm");
		is_mm_branch->SetAddress(&is_mm_);
	}
	is_sf_branch = 0;
	if (tree->GetBranch("is_sf") != 0) {
		is_sf_branch = tree->GetBranch("is_sf");
		is_sf_branch->SetAddress(&is_sf_);
	}
	is_df_branch = 0;
	if (tree->GetBranch("is_df") != 0) {
		is_df_branch = tree->GetBranch("is_df");
		is_df_branch->SetAddress(&is_df_);
	}
	no_extraz_branch = 0;
	if (tree->GetBranch("no_extraz") != 0) {
		no_extraz_branch = tree->GetBranch("no_extraz");
		no_extraz_branch->SetAddress(&no_extraz_);
	}
	is_gen_pp_branch = 0;
	if (tree->GetBranch("is_gen_pp") != 0) {
		is_gen_pp_branch = tree->GetBranch("is_gen_pp");
		is_gen_pp_branch->SetAddress(&is_gen_pp_);
	}
	is_gen_mm_branch = 0;
	if (tree->GetBranch("is_gen_mm") != 0) {
		is_gen_mm_branch = tree->GetBranch("is_gen_mm");
		is_gen_mm_branch->SetAddress(&is_gen_mm_);
	}
	gen_nbtags_branch = 0;
	if (tree->GetBranch("gen_nbtags") != 0) {
		gen_nbtags_branch = tree->GetBranch("gen_nbtags");
		gen_nbtags_branch->SetAddress(&gen_nbtags_);
	}
	gen_njets_branch = 0;
	if (tree->GetBranch("gen_njets") != 0) {
		gen_njets_branch = tree->GetBranch("gen_njets");
		gen_njets_branch->SetAddress(&gen_njets_);
	}
	gen_ht_branch = 0;
	if (tree->GetBranch("gen_ht") != 0) {
		gen_ht_branch = tree->GetBranch("gen_ht");
		gen_ht_branch->SetAddress(&gen_ht_);
	}
	lep1_wfr_branch = 0;
	if (tree->GetBranch("lep1_wfr") != 0) {
		lep1_wfr_branch = tree->GetBranch("lep1_wfr");
		lep1_wfr_branch->SetAddress(&lep1_wfr_);
	}
	lep1_wflip_branch = 0;
	if (tree->GetBranch("lep1_wflip") != 0) {
		lep1_wflip_branch = tree->GetBranch("lep1_wflip");
		lep1_wflip_branch->SetAddress(&lep1_wflip_);
	}
	lep1_nearbjet_dr_branch = 0;
	if (tree->GetBranch("lep1_nearbjet_dr") != 0) {
		lep1_nearbjet_dr_branch = tree->GetBranch("lep1_nearbjet_dr");
		lep1_nearbjet_dr_branch->SetAddress(&lep1_nearbjet_dr_);
	}
	lep1_nearjet_dr_branch = 0;
	if (tree->GetBranch("lep1_nearjet_dr") != 0) {
		lep1_nearjet_dr_branch = tree->GetBranch("lep1_nearjet_dr");
		lep1_nearjet_dr_branch->SetAddress(&lep1_nearjet_dr_);
	}
	lep2_wfr_branch = 0;
	if (tree->GetBranch("lep2_wfr") != 0) {
		lep2_wfr_branch = tree->GetBranch("lep2_wfr");
		lep2_wfr_branch->SetAddress(&lep2_wfr_);
	}
	lep2_wflip_branch = 0;
	if (tree->GetBranch("lep2_wflip") != 0) {
		lep2_wflip_branch = tree->GetBranch("lep2_wflip");
		lep2_wflip_branch->SetAddress(&lep2_wflip_);
	}
	lep2_nearbjet_dr_branch = 0;
	if (tree->GetBranch("lep2_nearbjet_dr") != 0) {
		lep2_nearbjet_dr_branch = tree->GetBranch("lep2_nearbjet_dr");
		lep2_nearbjet_dr_branch->SetAddress(&lep2_nearbjet_dr_);
	}
	lep2_nearjet_dr_branch = 0;
	if (tree->GetBranch("lep2_nearjet_dr") != 0) {
		lep2_nearjet_dr_branch = tree->GetBranch("lep2_nearjet_dr");
		lep2_nearjet_dr_branch->SetAddress(&lep2_nearjet_dr_);
	}
	sf_nbtag_branch = 0;
	if (tree->GetBranch("sf_nbtag") != 0) {
		sf_nbtag_branch = tree->GetBranch("sf_nbtag");
		sf_nbtag_branch->SetAddress(&sf_nbtag_);
	}
	sf_nbtag3_branch = 0;
	if (tree->GetBranch("sf_nbtag3") != 0) {
		sf_nbtag3_branch = tree->GetBranch("sf_nbtag3");
		sf_nbtag3_branch->SetAddress(&sf_nbtag3_);
	}
	sf_unc_nbtag_branch = 0;
	if (tree->GetBranch("sf_unc_nbtag") != 0) {
		sf_unc_nbtag_branch = tree->GetBranch("sf_unc_nbtag");
		sf_unc_nbtag_branch->SetAddress(&sf_unc_nbtag_);
	}
	sf_unc_nbtag3_branch = 0;
	if (tree->GetBranch("sf_unc_nbtag3") != 0) {
		sf_unc_nbtag3_branch = tree->GetBranch("sf_unc_nbtag3");
		sf_unc_nbtag3_branch->SetAddress(&sf_unc_nbtag3_);
	}
	jets_dr12_branch = 0;
	if (tree->GetBranch("jets_dr12") != 0) {
		jets_dr12_branch = tree->GetBranch("jets_dr12");
		jets_dr12_branch->SetAddress(&jets_dr12_);
	}
	bjets_dr12_branch = 0;
	if (tree->GetBranch("bjets_dr12") != 0) {
		bjets_dr12_branch = tree->GetBranch("bjets_dr12");
		bjets_dr12_branch->SetAddress(&bjets_dr12_);
	}
  tree->SetMakeClass(0);
}
void GetEntry(unsigned int idx) 
	// this only marks branches as not loaded, saving a lot of time
	{
		index = idx;
		run_isLoaded = false;
		ls_isLoaded = false;
		evt_isLoaded = false;
		is_real_data_isLoaded = false;
		sample_isLoaded = false;
		nvtxs_isLoaded = false;
		vtx_idx_isLoaded = false;
		pfmet_isLoaded = false;
		pfmet_phi_isLoaded = false;
		corpfmet_isLoaded = false;
		corpfmet_phi_isLoaded = false;
		scale1fb_isLoaded = false;
		xsec_isLoaded = false;
		kfactor_isLoaded = false;
		gen_met_isLoaded = false;
		gen_met_phi_isLoaded = false;
		lep1_p4_isLoaded = false;
		lep1_passes_id_isLoaded = false;
		lep1_passes_iso_isLoaded = false;
		lep1_is_num_isLoaded = false;
		lep1_is_fo_isLoaded = false;
		lep1_charge_isLoaded = false;
		lep1_pdgid_isLoaded = false;
		lep1_type_isLoaded = false;
		lep1_d0_isLoaded = false;
		lep1_dz_isLoaded = false;
		lep1_mt_isLoaded = false;
		lep1_corpfiso_isLoaded = false;
		lep1_pfiso_isLoaded = false;
		lep1_chiso_isLoaded = false;
		lep1_emiso_isLoaded = false;
		lep1_nhiso_isLoaded = false;
		lep1_corpfiso04_isLoaded = false;
		lep1_pfiso04_isLoaded = false;
		lep1_chiso04_isLoaded = false;
		lep1_emiso04_isLoaded = false;
		lep1_nhiso04_isLoaded = false;
		lep1_cordetiso_isLoaded = false;
		lep1_detiso_isLoaded = false;
		lep1_trkiso_isLoaded = false;
		lep1_ecaliso_isLoaded = false;
		lep1_hcaliso_isLoaded = false;
		lep1_cordetiso04_isLoaded = false;
		lep1_detiso04_isLoaded = false;
		lep1_trkiso04_isLoaded = false;
		lep1_ecaliso04_isLoaded = false;
		lep1_hcaliso04_isLoaded = false;
		lep1_effarea_isLoaded = false;
		lep1_effarea04_isLoaded = false;
		lep1_dbeta_isLoaded = false;
		lep1_dbeta04_isLoaded = false;
		lep1_sf_lepeff_isLoaded = false;
		lep1_sf_trig_isLoaded = false;
		lep1_mcp4_isLoaded = false;
		lep1_mc3p4_isLoaded = false;
		lep1_mc_momp4_isLoaded = false;
		lep1_mcid_isLoaded = false;
		lep1_mc3id_isLoaded = false;
		lep1_momid_isLoaded = false;
		lep1_mc3_momid_isLoaded = false;
		lep1_gsf_p4_isLoaded = false;
		lep1_ctf_p4_isLoaded = false;
		lep1_sc_p4_isLoaded = false;
		lep1_q3agree_isLoaded = false;
		lep1_is_conv_isLoaded = false;
		lep1_qsc_isLoaded = false;
		lep1_qctf_isLoaded = false;
		lep1_qgsf_isLoaded = false;
		lep1_nmhits_isLoaded = false;
		lep1_eleid_veto_isLoaded = false;
		lep1_eleid_loose_isLoaded = false;
		lep1_eleid_medium_isLoaded = false;
		lep1_eleid_tight_isLoaded = false;
		lep1_dphiin_isLoaded = false;
		lep1_detain_isLoaded = false;
		lep1_sieie_isLoaded = false;
		lep1_hoe_isLoaded = false;
		lep1_ooemoop_isLoaded = false;
		lep1_conv_dist_isLoaded = false;
		lep1_conv_dcot_isLoaded = false;
		lep1_gfit_p4_isLoaded = false;
		lep1_is_global_isLoaded = false;
		lep1_is_tracker_isLoaded = false;
		lep1_is_stamu_isLoaded = false;
		lep1_is_pfmu_isLoaded = false;
		lep1_is_loosemu_isLoaded = false;
		lep1_is_tightmu_isLoaded = false;
		lep1_npixelhits_isLoaded = false;
		lep1_nsihits_isLoaded = false;
		lep1_nsilayers_isLoaded = false;
		lep1_nstahits_isLoaded = false;
		lep1_nstations_isLoaded = false;
		lep1_chi2_isLoaded = false;
		lep1_ndof_isLoaded = false;
		lep1_pterr_isLoaded = false;
		lep1_ecal_vetodep_isLoaded = false;
		lep1_hcal_vetodep_isLoaded = false;
		lep2_p4_isLoaded = false;
		lep2_passes_id_isLoaded = false;
		lep2_passes_iso_isLoaded = false;
		lep2_is_num_isLoaded = false;
		lep2_is_fo_isLoaded = false;
		lep2_charge_isLoaded = false;
		lep2_pdgid_isLoaded = false;
		lep2_type_isLoaded = false;
		lep2_d0_isLoaded = false;
		lep2_dz_isLoaded = false;
		lep2_mt_isLoaded = false;
		lep2_corpfiso_isLoaded = false;
		lep2_pfiso_isLoaded = false;
		lep2_chiso_isLoaded = false;
		lep2_emiso_isLoaded = false;
		lep2_nhiso_isLoaded = false;
		lep2_corpfiso04_isLoaded = false;
		lep2_pfiso04_isLoaded = false;
		lep2_chiso04_isLoaded = false;
		lep2_emiso04_isLoaded = false;
		lep2_nhiso04_isLoaded = false;
		lep2_cordetiso_isLoaded = false;
		lep2_detiso_isLoaded = false;
		lep2_trkiso_isLoaded = false;
		lep2_ecaliso_isLoaded = false;
		lep2_hcaliso_isLoaded = false;
		lep2_cordetiso04_isLoaded = false;
		lep2_detiso04_isLoaded = false;
		lep2_trkiso04_isLoaded = false;
		lep2_ecaliso04_isLoaded = false;
		lep2_hcaliso04_isLoaded = false;
		lep2_effarea_isLoaded = false;
		lep2_effarea04_isLoaded = false;
		lep2_dbeta_isLoaded = false;
		lep2_dbeta04_isLoaded = false;
		lep2_sf_lepeff_isLoaded = false;
		lep2_sf_trig_isLoaded = false;
		lep2_mcp4_isLoaded = false;
		lep2_mc3p4_isLoaded = false;
		lep2_mc_momp4_isLoaded = false;
		lep2_mcid_isLoaded = false;
		lep2_mc3id_isLoaded = false;
		lep2_momid_isLoaded = false;
		lep2_mc3_momid_isLoaded = false;
		lep2_gsf_p4_isLoaded = false;
		lep2_ctf_p4_isLoaded = false;
		lep2_sc_p4_isLoaded = false;
		lep2_q3agree_isLoaded = false;
		lep2_is_conv_isLoaded = false;
		lep2_qsc_isLoaded = false;
		lep2_qctf_isLoaded = false;
		lep2_qgsf_isLoaded = false;
		lep2_nmhits_isLoaded = false;
		lep2_eleid_veto_isLoaded = false;
		lep2_eleid_loose_isLoaded = false;
		lep2_eleid_medium_isLoaded = false;
		lep2_eleid_tight_isLoaded = false;
		lep2_dphiin_isLoaded = false;
		lep2_detain_isLoaded = false;
		lep2_sieie_isLoaded = false;
		lep2_hoe_isLoaded = false;
		lep2_ooemoop_isLoaded = false;
		lep2_conv_dist_isLoaded = false;
		lep2_conv_dcot_isLoaded = false;
		lep2_gfit_p4_isLoaded = false;
		lep2_is_global_isLoaded = false;
		lep2_is_tracker_isLoaded = false;
		lep2_is_stamu_isLoaded = false;
		lep2_is_pfmu_isLoaded = false;
		lep2_is_loosemu_isLoaded = false;
		lep2_is_tightmu_isLoaded = false;
		lep2_npixelhits_isLoaded = false;
		lep2_nsihits_isLoaded = false;
		lep2_nsilayers_isLoaded = false;
		lep2_nstahits_isLoaded = false;
		lep2_nstations_isLoaded = false;
		lep2_chi2_isLoaded = false;
		lep2_ndof_isLoaded = false;
		lep2_pterr_isLoaded = false;
		lep2_ecal_vetodep_isLoaded = false;
		lep2_hcal_vetodep_isLoaded = false;
		dilep_p4_isLoaded = false;
		is_os_isLoaded = false;
		is_ss_isLoaded = false;
		dilep_type_isLoaded = false;
		dilep_gen_type_isLoaded = false;
		dilep_mass_isLoaded = false;
		dilep_dphi_isLoaded = false;
		dilep_deta_isLoaded = false;
		dilep_dr_isLoaded = false;
		fiduciality_isLoaded = false;
		selection_isLoaded = false;
		is_good_lumi_isLoaded = false;
		njets_isLoaded = false;
		njets20_isLoaded = false;
		njets30_isLoaded = false;
		nbtags_isLoaded = false;
		nbtags20_isLoaded = false;
		nbtags30_isLoaded = false;
		vtxw_isLoaded = false;
		ht_isLoaded = false;
		ht20_isLoaded = false;
		ht30_isLoaded = false;
		rho_isLoaded = false;
		rho_iso_isLoaded = false;
		trig_mm_isLoaded = false;
		trig_em_isLoaded = false;
		trig_ee_isLoaded = false;
		sf_dileptrig_isLoaded = false;
		sf_lepeff_isLoaded = false;
		sparm0_isLoaded = false;
		sparm1_isLoaded = false;
		sparm2_isLoaded = false;
		sparm3_isLoaded = false;
		is_pp_isLoaded = false;
		is_mm_isLoaded = false;
		is_sf_isLoaded = false;
		is_df_isLoaded = false;
		no_extraz_isLoaded = false;
		is_gen_pp_isLoaded = false;
		is_gen_mm_isLoaded = false;
		gen_nbtags_isLoaded = false;
		gen_njets_isLoaded = false;
		gen_ht_isLoaded = false;
		lep1_nearbjet_p4_isLoaded = false;
		lep1_nearjet_p4_isLoaded = false;
		lep1_wfr_isLoaded = false;
		lep1_wflip_isLoaded = false;
		lep1_nearbjet_dr_isLoaded = false;
		lep1_nearjet_dr_isLoaded = false;
		lep2_nearbjet_p4_isLoaded = false;
		lep2_nearjet_p4_isLoaded = false;
		lep2_wfr_isLoaded = false;
		lep2_wflip_isLoaded = false;
		lep2_nearbjet_dr_isLoaded = false;
		lep2_nearjet_dr_isLoaded = false;
		sf_nbtag_isLoaded = false;
		sf_nbtag3_isLoaded = false;
		sf_unc_nbtag_isLoaded = false;
		sf_unc_nbtag3_isLoaded = false;
		jets_dr12_isLoaded = false;
		bjets_dr12_isLoaded = false;
		vgenb_p4_isLoaded = false;
		vjets_p4_isLoaded = false;
		vgenjets_p4_isLoaded = false;
		vjets_nearjet_p4_isLoaded = false;
		vbjets_p4_isLoaded = false;
		vbjets_nearjet_p4_isLoaded = false;
	}

void LoadAllBranches() 
	// load all branches
{
	if (run_branch != 0) run();
	if (ls_branch != 0) ls();
	if (evt_branch != 0) evt();
	if (is_real_data_branch != 0) is_real_data();
	if (sample_branch != 0) sample();
	if (nvtxs_branch != 0) nvtxs();
	if (vtx_idx_branch != 0) vtx_idx();
	if (pfmet_branch != 0) pfmet();
	if (pfmet_phi_branch != 0) pfmet_phi();
	if (corpfmet_branch != 0) corpfmet();
	if (corpfmet_phi_branch != 0) corpfmet_phi();
	if (scale1fb_branch != 0) scale1fb();
	if (xsec_branch != 0) xsec();
	if (kfactor_branch != 0) kfactor();
	if (gen_met_branch != 0) gen_met();
	if (gen_met_phi_branch != 0) gen_met_phi();
	if (lep1_p4_branch != 0) lep1_p4();
	if (lep1_passes_id_branch != 0) lep1_passes_id();
	if (lep1_passes_iso_branch != 0) lep1_passes_iso();
	if (lep1_is_num_branch != 0) lep1_is_num();
	if (lep1_is_fo_branch != 0) lep1_is_fo();
	if (lep1_charge_branch != 0) lep1_charge();
	if (lep1_pdgid_branch != 0) lep1_pdgid();
	if (lep1_type_branch != 0) lep1_type();
	if (lep1_d0_branch != 0) lep1_d0();
	if (lep1_dz_branch != 0) lep1_dz();
	if (lep1_mt_branch != 0) lep1_mt();
	if (lep1_corpfiso_branch != 0) lep1_corpfiso();
	if (lep1_pfiso_branch != 0) lep1_pfiso();
	if (lep1_chiso_branch != 0) lep1_chiso();
	if (lep1_emiso_branch != 0) lep1_emiso();
	if (lep1_nhiso_branch != 0) lep1_nhiso();
	if (lep1_corpfiso04_branch != 0) lep1_corpfiso04();
	if (lep1_pfiso04_branch != 0) lep1_pfiso04();
	if (lep1_chiso04_branch != 0) lep1_chiso04();
	if (lep1_emiso04_branch != 0) lep1_emiso04();
	if (lep1_nhiso04_branch != 0) lep1_nhiso04();
	if (lep1_cordetiso_branch != 0) lep1_cordetiso();
	if (lep1_detiso_branch != 0) lep1_detiso();
	if (lep1_trkiso_branch != 0) lep1_trkiso();
	if (lep1_ecaliso_branch != 0) lep1_ecaliso();
	if (lep1_hcaliso_branch != 0) lep1_hcaliso();
	if (lep1_cordetiso04_branch != 0) lep1_cordetiso04();
	if (lep1_detiso04_branch != 0) lep1_detiso04();
	if (lep1_trkiso04_branch != 0) lep1_trkiso04();
	if (lep1_ecaliso04_branch != 0) lep1_ecaliso04();
	if (lep1_hcaliso04_branch != 0) lep1_hcaliso04();
	if (lep1_effarea_branch != 0) lep1_effarea();
	if (lep1_effarea04_branch != 0) lep1_effarea04();
	if (lep1_dbeta_branch != 0) lep1_dbeta();
	if (lep1_dbeta04_branch != 0) lep1_dbeta04();
	if (lep1_sf_lepeff_branch != 0) lep1_sf_lepeff();
	if (lep1_sf_trig_branch != 0) lep1_sf_trig();
	if (lep1_mcp4_branch != 0) lep1_mcp4();
	if (lep1_mc3p4_branch != 0) lep1_mc3p4();
	if (lep1_mc_momp4_branch != 0) lep1_mc_momp4();
	if (lep1_mcid_branch != 0) lep1_mcid();
	if (lep1_mc3id_branch != 0) lep1_mc3id();
	if (lep1_momid_branch != 0) lep1_momid();
	if (lep1_mc3_momid_branch != 0) lep1_mc3_momid();
	if (lep1_gsf_p4_branch != 0) lep1_gsf_p4();
	if (lep1_ctf_p4_branch != 0) lep1_ctf_p4();
	if (lep1_sc_p4_branch != 0) lep1_sc_p4();
	if (lep1_q3agree_branch != 0) lep1_q3agree();
	if (lep1_is_conv_branch != 0) lep1_is_conv();
	if (lep1_qsc_branch != 0) lep1_qsc();
	if (lep1_qctf_branch != 0) lep1_qctf();
	if (lep1_qgsf_branch != 0) lep1_qgsf();
	if (lep1_nmhits_branch != 0) lep1_nmhits();
	if (lep1_eleid_veto_branch != 0) lep1_eleid_veto();
	if (lep1_eleid_loose_branch != 0) lep1_eleid_loose();
	if (lep1_eleid_medium_branch != 0) lep1_eleid_medium();
	if (lep1_eleid_tight_branch != 0) lep1_eleid_tight();
	if (lep1_dphiin_branch != 0) lep1_dphiin();
	if (lep1_detain_branch != 0) lep1_detain();
	if (lep1_sieie_branch != 0) lep1_sieie();
	if (lep1_hoe_branch != 0) lep1_hoe();
	if (lep1_ooemoop_branch != 0) lep1_ooemoop();
	if (lep1_conv_dist_branch != 0) lep1_conv_dist();
	if (lep1_conv_dcot_branch != 0) lep1_conv_dcot();
	if (lep1_gfit_p4_branch != 0) lep1_gfit_p4();
	if (lep1_is_global_branch != 0) lep1_is_global();
	if (lep1_is_tracker_branch != 0) lep1_is_tracker();
	if (lep1_is_stamu_branch != 0) lep1_is_stamu();
	if (lep1_is_pfmu_branch != 0) lep1_is_pfmu();
	if (lep1_is_loosemu_branch != 0) lep1_is_loosemu();
	if (lep1_is_tightmu_branch != 0) lep1_is_tightmu();
	if (lep1_npixelhits_branch != 0) lep1_npixelhits();
	if (lep1_nsihits_branch != 0) lep1_nsihits();
	if (lep1_nsilayers_branch != 0) lep1_nsilayers();
	if (lep1_nstahits_branch != 0) lep1_nstahits();
	if (lep1_nstations_branch != 0) lep1_nstations();
	if (lep1_chi2_branch != 0) lep1_chi2();
	if (lep1_ndof_branch != 0) lep1_ndof();
	if (lep1_pterr_branch != 0) lep1_pterr();
	if (lep1_ecal_vetodep_branch != 0) lep1_ecal_vetodep();
	if (lep1_hcal_vetodep_branch != 0) lep1_hcal_vetodep();
	if (lep2_p4_branch != 0) lep2_p4();
	if (lep2_passes_id_branch != 0) lep2_passes_id();
	if (lep2_passes_iso_branch != 0) lep2_passes_iso();
	if (lep2_is_num_branch != 0) lep2_is_num();
	if (lep2_is_fo_branch != 0) lep2_is_fo();
	if (lep2_charge_branch != 0) lep2_charge();
	if (lep2_pdgid_branch != 0) lep2_pdgid();
	if (lep2_type_branch != 0) lep2_type();
	if (lep2_d0_branch != 0) lep2_d0();
	if (lep2_dz_branch != 0) lep2_dz();
	if (lep2_mt_branch != 0) lep2_mt();
	if (lep2_corpfiso_branch != 0) lep2_corpfiso();
	if (lep2_pfiso_branch != 0) lep2_pfiso();
	if (lep2_chiso_branch != 0) lep2_chiso();
	if (lep2_emiso_branch != 0) lep2_emiso();
	if (lep2_nhiso_branch != 0) lep2_nhiso();
	if (lep2_corpfiso04_branch != 0) lep2_corpfiso04();
	if (lep2_pfiso04_branch != 0) lep2_pfiso04();
	if (lep2_chiso04_branch != 0) lep2_chiso04();
	if (lep2_emiso04_branch != 0) lep2_emiso04();
	if (lep2_nhiso04_branch != 0) lep2_nhiso04();
	if (lep2_cordetiso_branch != 0) lep2_cordetiso();
	if (lep2_detiso_branch != 0) lep2_detiso();
	if (lep2_trkiso_branch != 0) lep2_trkiso();
	if (lep2_ecaliso_branch != 0) lep2_ecaliso();
	if (lep2_hcaliso_branch != 0) lep2_hcaliso();
	if (lep2_cordetiso04_branch != 0) lep2_cordetiso04();
	if (lep2_detiso04_branch != 0) lep2_detiso04();
	if (lep2_trkiso04_branch != 0) lep2_trkiso04();
	if (lep2_ecaliso04_branch != 0) lep2_ecaliso04();
	if (lep2_hcaliso04_branch != 0) lep2_hcaliso04();
	if (lep2_effarea_branch != 0) lep2_effarea();
	if (lep2_effarea04_branch != 0) lep2_effarea04();
	if (lep2_dbeta_branch != 0) lep2_dbeta();
	if (lep2_dbeta04_branch != 0) lep2_dbeta04();
	if (lep2_sf_lepeff_branch != 0) lep2_sf_lepeff();
	if (lep2_sf_trig_branch != 0) lep2_sf_trig();
	if (lep2_mcp4_branch != 0) lep2_mcp4();
	if (lep2_mc3p4_branch != 0) lep2_mc3p4();
	if (lep2_mc_momp4_branch != 0) lep2_mc_momp4();
	if (lep2_mcid_branch != 0) lep2_mcid();
	if (lep2_mc3id_branch != 0) lep2_mc3id();
	if (lep2_momid_branch != 0) lep2_momid();
	if (lep2_mc3_momid_branch != 0) lep2_mc3_momid();
	if (lep2_gsf_p4_branch != 0) lep2_gsf_p4();
	if (lep2_ctf_p4_branch != 0) lep2_ctf_p4();
	if (lep2_sc_p4_branch != 0) lep2_sc_p4();
	if (lep2_q3agree_branch != 0) lep2_q3agree();
	if (lep2_is_conv_branch != 0) lep2_is_conv();
	if (lep2_qsc_branch != 0) lep2_qsc();
	if (lep2_qctf_branch != 0) lep2_qctf();
	if (lep2_qgsf_branch != 0) lep2_qgsf();
	if (lep2_nmhits_branch != 0) lep2_nmhits();
	if (lep2_eleid_veto_branch != 0) lep2_eleid_veto();
	if (lep2_eleid_loose_branch != 0) lep2_eleid_loose();
	if (lep2_eleid_medium_branch != 0) lep2_eleid_medium();
	if (lep2_eleid_tight_branch != 0) lep2_eleid_tight();
	if (lep2_dphiin_branch != 0) lep2_dphiin();
	if (lep2_detain_branch != 0) lep2_detain();
	if (lep2_sieie_branch != 0) lep2_sieie();
	if (lep2_hoe_branch != 0) lep2_hoe();
	if (lep2_ooemoop_branch != 0) lep2_ooemoop();
	if (lep2_conv_dist_branch != 0) lep2_conv_dist();
	if (lep2_conv_dcot_branch != 0) lep2_conv_dcot();
	if (lep2_gfit_p4_branch != 0) lep2_gfit_p4();
	if (lep2_is_global_branch != 0) lep2_is_global();
	if (lep2_is_tracker_branch != 0) lep2_is_tracker();
	if (lep2_is_stamu_branch != 0) lep2_is_stamu();
	if (lep2_is_pfmu_branch != 0) lep2_is_pfmu();
	if (lep2_is_loosemu_branch != 0) lep2_is_loosemu();
	if (lep2_is_tightmu_branch != 0) lep2_is_tightmu();
	if (lep2_npixelhits_branch != 0) lep2_npixelhits();
	if (lep2_nsihits_branch != 0) lep2_nsihits();
	if (lep2_nsilayers_branch != 0) lep2_nsilayers();
	if (lep2_nstahits_branch != 0) lep2_nstahits();
	if (lep2_nstations_branch != 0) lep2_nstations();
	if (lep2_chi2_branch != 0) lep2_chi2();
	if (lep2_ndof_branch != 0) lep2_ndof();
	if (lep2_pterr_branch != 0) lep2_pterr();
	if (lep2_ecal_vetodep_branch != 0) lep2_ecal_vetodep();
	if (lep2_hcal_vetodep_branch != 0) lep2_hcal_vetodep();
	if (dilep_p4_branch != 0) dilep_p4();
	if (is_os_branch != 0) is_os();
	if (is_ss_branch != 0) is_ss();
	if (dilep_type_branch != 0) dilep_type();
	if (dilep_gen_type_branch != 0) dilep_gen_type();
	if (dilep_mass_branch != 0) dilep_mass();
	if (dilep_dphi_branch != 0) dilep_dphi();
	if (dilep_deta_branch != 0) dilep_deta();
	if (dilep_dr_branch != 0) dilep_dr();
	if (fiduciality_branch != 0) fiduciality();
	if (selection_branch != 0) selection();
	if (is_good_lumi_branch != 0) is_good_lumi();
	if (njets_branch != 0) njets();
	if (njets20_branch != 0) njets20();
	if (njets30_branch != 0) njets30();
	if (nbtags_branch != 0) nbtags();
	if (nbtags20_branch != 0) nbtags20();
	if (nbtags30_branch != 0) nbtags30();
	if (vtxw_branch != 0) vtxw();
	if (ht_branch != 0) ht();
	if (ht20_branch != 0) ht20();
	if (ht30_branch != 0) ht30();
	if (rho_branch != 0) rho();
	if (rho_iso_branch != 0) rho_iso();
	if (trig_mm_branch != 0) trig_mm();
	if (trig_em_branch != 0) trig_em();
	if (trig_ee_branch != 0) trig_ee();
	if (sf_dileptrig_branch != 0) sf_dileptrig();
	if (sf_lepeff_branch != 0) sf_lepeff();
	if (sparm0_branch != 0) sparm0();
	if (sparm1_branch != 0) sparm1();
	if (sparm2_branch != 0) sparm2();
	if (sparm3_branch != 0) sparm3();
	if (is_pp_branch != 0) is_pp();
	if (is_mm_branch != 0) is_mm();
	if (is_sf_branch != 0) is_sf();
	if (is_df_branch != 0) is_df();
	if (no_extraz_branch != 0) no_extraz();
	if (is_gen_pp_branch != 0) is_gen_pp();
	if (is_gen_mm_branch != 0) is_gen_mm();
	if (gen_nbtags_branch != 0) gen_nbtags();
	if (gen_njets_branch != 0) gen_njets();
	if (gen_ht_branch != 0) gen_ht();
	if (lep1_nearbjet_p4_branch != 0) lep1_nearbjet_p4();
	if (lep1_nearjet_p4_branch != 0) lep1_nearjet_p4();
	if (lep1_wfr_branch != 0) lep1_wfr();
	if (lep1_wflip_branch != 0) lep1_wflip();
	if (lep1_nearbjet_dr_branch != 0) lep1_nearbjet_dr();
	if (lep1_nearjet_dr_branch != 0) lep1_nearjet_dr();
	if (lep2_nearbjet_p4_branch != 0) lep2_nearbjet_p4();
	if (lep2_nearjet_p4_branch != 0) lep2_nearjet_p4();
	if (lep2_wfr_branch != 0) lep2_wfr();
	if (lep2_wflip_branch != 0) lep2_wflip();
	if (lep2_nearbjet_dr_branch != 0) lep2_nearbjet_dr();
	if (lep2_nearjet_dr_branch != 0) lep2_nearjet_dr();
	if (sf_nbtag_branch != 0) sf_nbtag();
	if (sf_nbtag3_branch != 0) sf_nbtag3();
	if (sf_unc_nbtag_branch != 0) sf_unc_nbtag();
	if (sf_unc_nbtag3_branch != 0) sf_unc_nbtag3();
	if (jets_dr12_branch != 0) jets_dr12();
	if (bjets_dr12_branch != 0) bjets_dr12();
	if (vgenb_p4_branch != 0) vgenb_p4();
	if (vjets_p4_branch != 0) vjets_p4();
	if (vgenjets_p4_branch != 0) vgenjets_p4();
	if (vjets_nearjet_p4_branch != 0) vjets_nearjet_p4();
	if (vbjets_p4_branch != 0) vbjets_p4();
	if (vbjets_nearjet_p4_branch != 0) vbjets_nearjet_p4();
}

	unsigned int &run()
	{
		if (not run_isLoaded) {
			if (run_branch != 0) {
				run_branch->GetEntry(index);
			} else { 
				printf("branch run_branch does not exist!\n");
				exit(1);
			}
			run_isLoaded = true;
		}
		return run_;
	}
	unsigned int &ls()
	{
		if (not ls_isLoaded) {
			if (ls_branch != 0) {
				ls_branch->GetEntry(index);
			} else { 
				printf("branch ls_branch does not exist!\n");
				exit(1);
			}
			ls_isLoaded = true;
		}
		return ls_;
	}
	unsigned int &evt()
	{
		if (not evt_isLoaded) {
			if (evt_branch != 0) {
				evt_branch->GetEntry(index);
			} else { 
				printf("branch evt_branch does not exist!\n");
				exit(1);
			}
			evt_isLoaded = true;
		}
		return evt_;
	}
	bool &	is_real_data()
	{
		if (not is_real_data_isLoaded) {
			if (is_real_data_branch != 0) {
				is_real_data_branch->GetEntry(index);
			} else { 
				printf("branch is_real_data_branch does not exist!\n");
				exit(1);
			}
			is_real_data_isLoaded = true;
		}
		return is_real_data_;
	}
	int &sample()
	{
		if (not sample_isLoaded) {
			if (sample_branch != 0) {
				sample_branch->GetEntry(index);
			} else { 
				printf("branch sample_branch does not exist!\n");
				exit(1);
			}
			sample_isLoaded = true;
		}
		return sample_;
	}
	int &nvtxs()
	{
		if (not nvtxs_isLoaded) {
			if (nvtxs_branch != 0) {
				nvtxs_branch->GetEntry(index);
			} else { 
				printf("branch nvtxs_branch does not exist!\n");
				exit(1);
			}
			nvtxs_isLoaded = true;
		}
		return nvtxs_;
	}
	int &vtx_idx()
	{
		if (not vtx_idx_isLoaded) {
			if (vtx_idx_branch != 0) {
				vtx_idx_branch->GetEntry(index);
			} else { 
				printf("branch vtx_idx_branch does not exist!\n");
				exit(1);
			}
			vtx_idx_isLoaded = true;
		}
		return vtx_idx_;
	}
	float &pfmet()
	{
		if (not pfmet_isLoaded) {
			if (pfmet_branch != 0) {
				pfmet_branch->GetEntry(index);
			} else { 
				printf("branch pfmet_branch does not exist!\n");
				exit(1);
			}
			pfmet_isLoaded = true;
		}
		return pfmet_;
	}
	float &pfmet_phi()
	{
		if (not pfmet_phi_isLoaded) {
			if (pfmet_phi_branch != 0) {
				pfmet_phi_branch->GetEntry(index);
			} else { 
				printf("branch pfmet_phi_branch does not exist!\n");
				exit(1);
			}
			pfmet_phi_isLoaded = true;
		}
		return pfmet_phi_;
	}
	float &corpfmet()
	{
		if (not corpfmet_isLoaded) {
			if (corpfmet_branch != 0) {
				corpfmet_branch->GetEntry(index);
			} else { 
				printf("branch corpfmet_branch does not exist!\n");
				exit(1);
			}
			corpfmet_isLoaded = true;
		}
		return corpfmet_;
	}
	float &corpfmet_phi()
	{
		if (not corpfmet_phi_isLoaded) {
			if (corpfmet_phi_branch != 0) {
				corpfmet_phi_branch->GetEntry(index);
			} else { 
				printf("branch corpfmet_phi_branch does not exist!\n");
				exit(1);
			}
			corpfmet_phi_isLoaded = true;
		}
		return corpfmet_phi_;
	}
	float &scale1fb()
	{
		if (not scale1fb_isLoaded) {
			if (scale1fb_branch != 0) {
				scale1fb_branch->GetEntry(index);
			} else { 
				printf("branch scale1fb_branch does not exist!\n");
				exit(1);
			}
			scale1fb_isLoaded = true;
		}
		return scale1fb_;
	}
	float &xsec()
	{
		if (not xsec_isLoaded) {
			if (xsec_branch != 0) {
				xsec_branch->GetEntry(index);
			} else { 
				printf("branch xsec_branch does not exist!\n");
				exit(1);
			}
			xsec_isLoaded = true;
		}
		return xsec_;
	}
	float &kfactor()
	{
		if (not kfactor_isLoaded) {
			if (kfactor_branch != 0) {
				kfactor_branch->GetEntry(index);
			} else { 
				printf("branch kfactor_branch does not exist!\n");
				exit(1);
			}
			kfactor_isLoaded = true;
		}
		return kfactor_;
	}
	float &gen_met()
	{
		if (not gen_met_isLoaded) {
			if (gen_met_branch != 0) {
				gen_met_branch->GetEntry(index);
			} else { 
				printf("branch gen_met_branch does not exist!\n");
				exit(1);
			}
			gen_met_isLoaded = true;
		}
		return gen_met_;
	}
	float &gen_met_phi()
	{
		if (not gen_met_phi_isLoaded) {
			if (gen_met_phi_branch != 0) {
				gen_met_phi_branch->GetEntry(index);
			} else { 
				printf("branch gen_met_phi_branch does not exist!\n");
				exit(1);
			}
			gen_met_phi_isLoaded = true;
		}
		return gen_met_phi_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_p4()
	{
		if (not lep1_p4_isLoaded) {
			if (lep1_p4_branch != 0) {
				lep1_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep1_p4_branch does not exist!\n");
				exit(1);
			}
			lep1_p4_isLoaded = true;
		}
		return *lep1_p4_;
	}
	bool &	lep1_passes_id()
	{
		if (not lep1_passes_id_isLoaded) {
			if (lep1_passes_id_branch != 0) {
				lep1_passes_id_branch->GetEntry(index);
			} else { 
				printf("branch lep1_passes_id_branch does not exist!\n");
				exit(1);
			}
			lep1_passes_id_isLoaded = true;
		}
		return lep1_passes_id_;
	}
	bool &	lep1_passes_iso()
	{
		if (not lep1_passes_iso_isLoaded) {
			if (lep1_passes_iso_branch != 0) {
				lep1_passes_iso_branch->GetEntry(index);
			} else { 
				printf("branch lep1_passes_iso_branch does not exist!\n");
				exit(1);
			}
			lep1_passes_iso_isLoaded = true;
		}
		return lep1_passes_iso_;
	}
	bool &	lep1_is_num()
	{
		if (not lep1_is_num_isLoaded) {
			if (lep1_is_num_branch != 0) {
				lep1_is_num_branch->GetEntry(index);
			} else { 
				printf("branch lep1_is_num_branch does not exist!\n");
				exit(1);
			}
			lep1_is_num_isLoaded = true;
		}
		return lep1_is_num_;
	}
	bool &	lep1_is_fo()
	{
		if (not lep1_is_fo_isLoaded) {
			if (lep1_is_fo_branch != 0) {
				lep1_is_fo_branch->GetEntry(index);
			} else { 
				printf("branch lep1_is_fo_branch does not exist!\n");
				exit(1);
			}
			lep1_is_fo_isLoaded = true;
		}
		return lep1_is_fo_;
	}
	int &lep1_charge()
	{
		if (not lep1_charge_isLoaded) {
			if (lep1_charge_branch != 0) {
				lep1_charge_branch->GetEntry(index);
			} else { 
				printf("branch lep1_charge_branch does not exist!\n");
				exit(1);
			}
			lep1_charge_isLoaded = true;
		}
		return lep1_charge_;
	}
	int &lep1_pdgid()
	{
		if (not lep1_pdgid_isLoaded) {
			if (lep1_pdgid_branch != 0) {
				lep1_pdgid_branch->GetEntry(index);
			} else { 
				printf("branch lep1_pdgid_branch does not exist!\n");
				exit(1);
			}
			lep1_pdgid_isLoaded = true;
		}
		return lep1_pdgid_;
	}
	int &lep1_type()
	{
		if (not lep1_type_isLoaded) {
			if (lep1_type_branch != 0) {
				lep1_type_branch->GetEntry(index);
			} else { 
				printf("branch lep1_type_branch does not exist!\n");
				exit(1);
			}
			lep1_type_isLoaded = true;
		}
		return lep1_type_;
	}
	float &lep1_d0()
	{
		if (not lep1_d0_isLoaded) {
			if (lep1_d0_branch != 0) {
				lep1_d0_branch->GetEntry(index);
			} else { 
				printf("branch lep1_d0_branch does not exist!\n");
				exit(1);
			}
			lep1_d0_isLoaded = true;
		}
		return lep1_d0_;
	}
	float &lep1_dz()
	{
		if (not lep1_dz_isLoaded) {
			if (lep1_dz_branch != 0) {
				lep1_dz_branch->GetEntry(index);
			} else { 
				printf("branch lep1_dz_branch does not exist!\n");
				exit(1);
			}
			lep1_dz_isLoaded = true;
		}
		return lep1_dz_;
	}
	float &lep1_mt()
	{
		if (not lep1_mt_isLoaded) {
			if (lep1_mt_branch != 0) {
				lep1_mt_branch->GetEntry(index);
			} else { 
				printf("branch lep1_mt_branch does not exist!\n");
				exit(1);
			}
			lep1_mt_isLoaded = true;
		}
		return lep1_mt_;
	}
	float &lep1_corpfiso()
	{
		if (not lep1_corpfiso_isLoaded) {
			if (lep1_corpfiso_branch != 0) {
				lep1_corpfiso_branch->GetEntry(index);
			} else { 
				printf("branch lep1_corpfiso_branch does not exist!\n");
				exit(1);
			}
			lep1_corpfiso_isLoaded = true;
		}
		return lep1_corpfiso_;
	}
	float &lep1_pfiso()
	{
		if (not lep1_pfiso_isLoaded) {
			if (lep1_pfiso_branch != 0) {
				lep1_pfiso_branch->GetEntry(index);
			} else { 
				printf("branch lep1_pfiso_branch does not exist!\n");
				exit(1);
			}
			lep1_pfiso_isLoaded = true;
		}
		return lep1_pfiso_;
	}
	float &lep1_chiso()
	{
		if (not lep1_chiso_isLoaded) {
			if (lep1_chiso_branch != 0) {
				lep1_chiso_branch->GetEntry(index);
			} else { 
				printf("branch lep1_chiso_branch does not exist!\n");
				exit(1);
			}
			lep1_chiso_isLoaded = true;
		}
		return lep1_chiso_;
	}
	float &lep1_emiso()
	{
		if (not lep1_emiso_isLoaded) {
			if (lep1_emiso_branch != 0) {
				lep1_emiso_branch->GetEntry(index);
			} else { 
				printf("branch lep1_emiso_branch does not exist!\n");
				exit(1);
			}
			lep1_emiso_isLoaded = true;
		}
		return lep1_emiso_;
	}
	float &lep1_nhiso()
	{
		if (not lep1_nhiso_isLoaded) {
			if (lep1_nhiso_branch != 0) {
				lep1_nhiso_branch->GetEntry(index);
			} else { 
				printf("branch lep1_nhiso_branch does not exist!\n");
				exit(1);
			}
			lep1_nhiso_isLoaded = true;
		}
		return lep1_nhiso_;
	}
	float &lep1_corpfiso04()
	{
		if (not lep1_corpfiso04_isLoaded) {
			if (lep1_corpfiso04_branch != 0) {
				lep1_corpfiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep1_corpfiso04_branch does not exist!\n");
				exit(1);
			}
			lep1_corpfiso04_isLoaded = true;
		}
		return lep1_corpfiso04_;
	}
	float &lep1_pfiso04()
	{
		if (not lep1_pfiso04_isLoaded) {
			if (lep1_pfiso04_branch != 0) {
				lep1_pfiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep1_pfiso04_branch does not exist!\n");
				exit(1);
			}
			lep1_pfiso04_isLoaded = true;
		}
		return lep1_pfiso04_;
	}
	float &lep1_chiso04()
	{
		if (not lep1_chiso04_isLoaded) {
			if (lep1_chiso04_branch != 0) {
				lep1_chiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep1_chiso04_branch does not exist!\n");
				exit(1);
			}
			lep1_chiso04_isLoaded = true;
		}
		return lep1_chiso04_;
	}
	float &lep1_emiso04()
	{
		if (not lep1_emiso04_isLoaded) {
			if (lep1_emiso04_branch != 0) {
				lep1_emiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep1_emiso04_branch does not exist!\n");
				exit(1);
			}
			lep1_emiso04_isLoaded = true;
		}
		return lep1_emiso04_;
	}
	float &lep1_nhiso04()
	{
		if (not lep1_nhiso04_isLoaded) {
			if (lep1_nhiso04_branch != 0) {
				lep1_nhiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep1_nhiso04_branch does not exist!\n");
				exit(1);
			}
			lep1_nhiso04_isLoaded = true;
		}
		return lep1_nhiso04_;
	}
	float &lep1_cordetiso()
	{
		if (not lep1_cordetiso_isLoaded) {
			if (lep1_cordetiso_branch != 0) {
				lep1_cordetiso_branch->GetEntry(index);
			} else { 
				printf("branch lep1_cordetiso_branch does not exist!\n");
				exit(1);
			}
			lep1_cordetiso_isLoaded = true;
		}
		return lep1_cordetiso_;
	}
	float &lep1_detiso()
	{
		if (not lep1_detiso_isLoaded) {
			if (lep1_detiso_branch != 0) {
				lep1_detiso_branch->GetEntry(index);
			} else { 
				printf("branch lep1_detiso_branch does not exist!\n");
				exit(1);
			}
			lep1_detiso_isLoaded = true;
		}
		return lep1_detiso_;
	}
	float &lep1_trkiso()
	{
		if (not lep1_trkiso_isLoaded) {
			if (lep1_trkiso_branch != 0) {
				lep1_trkiso_branch->GetEntry(index);
			} else { 
				printf("branch lep1_trkiso_branch does not exist!\n");
				exit(1);
			}
			lep1_trkiso_isLoaded = true;
		}
		return lep1_trkiso_;
	}
	float &lep1_ecaliso()
	{
		if (not lep1_ecaliso_isLoaded) {
			if (lep1_ecaliso_branch != 0) {
				lep1_ecaliso_branch->GetEntry(index);
			} else { 
				printf("branch lep1_ecaliso_branch does not exist!\n");
				exit(1);
			}
			lep1_ecaliso_isLoaded = true;
		}
		return lep1_ecaliso_;
	}
	float &lep1_hcaliso()
	{
		if (not lep1_hcaliso_isLoaded) {
			if (lep1_hcaliso_branch != 0) {
				lep1_hcaliso_branch->GetEntry(index);
			} else { 
				printf("branch lep1_hcaliso_branch does not exist!\n");
				exit(1);
			}
			lep1_hcaliso_isLoaded = true;
		}
		return lep1_hcaliso_;
	}
	float &lep1_cordetiso04()
	{
		if (not lep1_cordetiso04_isLoaded) {
			if (lep1_cordetiso04_branch != 0) {
				lep1_cordetiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep1_cordetiso04_branch does not exist!\n");
				exit(1);
			}
			lep1_cordetiso04_isLoaded = true;
		}
		return lep1_cordetiso04_;
	}
	float &lep1_detiso04()
	{
		if (not lep1_detiso04_isLoaded) {
			if (lep1_detiso04_branch != 0) {
				lep1_detiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep1_detiso04_branch does not exist!\n");
				exit(1);
			}
			lep1_detiso04_isLoaded = true;
		}
		return lep1_detiso04_;
	}
	float &lep1_trkiso04()
	{
		if (not lep1_trkiso04_isLoaded) {
			if (lep1_trkiso04_branch != 0) {
				lep1_trkiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep1_trkiso04_branch does not exist!\n");
				exit(1);
			}
			lep1_trkiso04_isLoaded = true;
		}
		return lep1_trkiso04_;
	}
	float &lep1_ecaliso04()
	{
		if (not lep1_ecaliso04_isLoaded) {
			if (lep1_ecaliso04_branch != 0) {
				lep1_ecaliso04_branch->GetEntry(index);
			} else { 
				printf("branch lep1_ecaliso04_branch does not exist!\n");
				exit(1);
			}
			lep1_ecaliso04_isLoaded = true;
		}
		return lep1_ecaliso04_;
	}
	float &lep1_hcaliso04()
	{
		if (not lep1_hcaliso04_isLoaded) {
			if (lep1_hcaliso04_branch != 0) {
				lep1_hcaliso04_branch->GetEntry(index);
			} else { 
				printf("branch lep1_hcaliso04_branch does not exist!\n");
				exit(1);
			}
			lep1_hcaliso04_isLoaded = true;
		}
		return lep1_hcaliso04_;
	}
	float &lep1_effarea()
	{
		if (not lep1_effarea_isLoaded) {
			if (lep1_effarea_branch != 0) {
				lep1_effarea_branch->GetEntry(index);
			} else { 
				printf("branch lep1_effarea_branch does not exist!\n");
				exit(1);
			}
			lep1_effarea_isLoaded = true;
		}
		return lep1_effarea_;
	}
	float &lep1_effarea04()
	{
		if (not lep1_effarea04_isLoaded) {
			if (lep1_effarea04_branch != 0) {
				lep1_effarea04_branch->GetEntry(index);
			} else { 
				printf("branch lep1_effarea04_branch does not exist!\n");
				exit(1);
			}
			lep1_effarea04_isLoaded = true;
		}
		return lep1_effarea04_;
	}
	float &lep1_dbeta()
	{
		if (not lep1_dbeta_isLoaded) {
			if (lep1_dbeta_branch != 0) {
				lep1_dbeta_branch->GetEntry(index);
			} else { 
				printf("branch lep1_dbeta_branch does not exist!\n");
				exit(1);
			}
			lep1_dbeta_isLoaded = true;
		}
		return lep1_dbeta_;
	}
	float &lep1_dbeta04()
	{
		if (not lep1_dbeta04_isLoaded) {
			if (lep1_dbeta04_branch != 0) {
				lep1_dbeta04_branch->GetEntry(index);
			} else { 
				printf("branch lep1_dbeta04_branch does not exist!\n");
				exit(1);
			}
			lep1_dbeta04_isLoaded = true;
		}
		return lep1_dbeta04_;
	}
	float &lep1_sf_lepeff()
	{
		if (not lep1_sf_lepeff_isLoaded) {
			if (lep1_sf_lepeff_branch != 0) {
				lep1_sf_lepeff_branch->GetEntry(index);
			} else { 
				printf("branch lep1_sf_lepeff_branch does not exist!\n");
				exit(1);
			}
			lep1_sf_lepeff_isLoaded = true;
		}
		return lep1_sf_lepeff_;
	}
	float &lep1_sf_trig()
	{
		if (not lep1_sf_trig_isLoaded) {
			if (lep1_sf_trig_branch != 0) {
				lep1_sf_trig_branch->GetEntry(index);
			} else { 
				printf("branch lep1_sf_trig_branch does not exist!\n");
				exit(1);
			}
			lep1_sf_trig_isLoaded = true;
		}
		return lep1_sf_trig_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mcp4()
	{
		if (not lep1_mcp4_isLoaded) {
			if (lep1_mcp4_branch != 0) {
				lep1_mcp4_branch->GetEntry(index);
			} else { 
				printf("branch lep1_mcp4_branch does not exist!\n");
				exit(1);
			}
			lep1_mcp4_isLoaded = true;
		}
		return *lep1_mcp4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mc3p4()
	{
		if (not lep1_mc3p4_isLoaded) {
			if (lep1_mc3p4_branch != 0) {
				lep1_mc3p4_branch->GetEntry(index);
			} else { 
				printf("branch lep1_mc3p4_branch does not exist!\n");
				exit(1);
			}
			lep1_mc3p4_isLoaded = true;
		}
		return *lep1_mc3p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mc_momp4()
	{
		if (not lep1_mc_momp4_isLoaded) {
			if (lep1_mc_momp4_branch != 0) {
				lep1_mc_momp4_branch->GetEntry(index);
			} else { 
				printf("branch lep1_mc_momp4_branch does not exist!\n");
				exit(1);
			}
			lep1_mc_momp4_isLoaded = true;
		}
		return *lep1_mc_momp4_;
	}
	int &lep1_mcid()
	{
		if (not lep1_mcid_isLoaded) {
			if (lep1_mcid_branch != 0) {
				lep1_mcid_branch->GetEntry(index);
			} else { 
				printf("branch lep1_mcid_branch does not exist!\n");
				exit(1);
			}
			lep1_mcid_isLoaded = true;
		}
		return lep1_mcid_;
	}
	int &lep1_mc3id()
	{
		if (not lep1_mc3id_isLoaded) {
			if (lep1_mc3id_branch != 0) {
				lep1_mc3id_branch->GetEntry(index);
			} else { 
				printf("branch lep1_mc3id_branch does not exist!\n");
				exit(1);
			}
			lep1_mc3id_isLoaded = true;
		}
		return lep1_mc3id_;
	}
	int &lep1_momid()
	{
		if (not lep1_momid_isLoaded) {
			if (lep1_momid_branch != 0) {
				lep1_momid_branch->GetEntry(index);
			} else { 
				printf("branch lep1_momid_branch does not exist!\n");
				exit(1);
			}
			lep1_momid_isLoaded = true;
		}
		return lep1_momid_;
	}
	int &lep1_mc3_momid()
	{
		if (not lep1_mc3_momid_isLoaded) {
			if (lep1_mc3_momid_branch != 0) {
				lep1_mc3_momid_branch->GetEntry(index);
			} else { 
				printf("branch lep1_mc3_momid_branch does not exist!\n");
				exit(1);
			}
			lep1_mc3_momid_isLoaded = true;
		}
		return lep1_mc3_momid_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_gsf_p4()
	{
		if (not lep1_gsf_p4_isLoaded) {
			if (lep1_gsf_p4_branch != 0) {
				lep1_gsf_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep1_gsf_p4_branch does not exist!\n");
				exit(1);
			}
			lep1_gsf_p4_isLoaded = true;
		}
		return *lep1_gsf_p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_ctf_p4()
	{
		if (not lep1_ctf_p4_isLoaded) {
			if (lep1_ctf_p4_branch != 0) {
				lep1_ctf_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep1_ctf_p4_branch does not exist!\n");
				exit(1);
			}
			lep1_ctf_p4_isLoaded = true;
		}
		return *lep1_ctf_p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_sc_p4()
	{
		if (not lep1_sc_p4_isLoaded) {
			if (lep1_sc_p4_branch != 0) {
				lep1_sc_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep1_sc_p4_branch does not exist!\n");
				exit(1);
			}
			lep1_sc_p4_isLoaded = true;
		}
		return *lep1_sc_p4_;
	}
	bool &	lep1_q3agree()
	{
		if (not lep1_q3agree_isLoaded) {
			if (lep1_q3agree_branch != 0) {
				lep1_q3agree_branch->GetEntry(index);
			} else { 
				printf("branch lep1_q3agree_branch does not exist!\n");
				exit(1);
			}
			lep1_q3agree_isLoaded = true;
		}
		return lep1_q3agree_;
	}
	bool &	lep1_is_conv()
	{
		if (not lep1_is_conv_isLoaded) {
			if (lep1_is_conv_branch != 0) {
				lep1_is_conv_branch->GetEntry(index);
			} else { 
				printf("branch lep1_is_conv_branch does not exist!\n");
				exit(1);
			}
			lep1_is_conv_isLoaded = true;
		}
		return lep1_is_conv_;
	}
	int &lep1_qsc()
	{
		if (not lep1_qsc_isLoaded) {
			if (lep1_qsc_branch != 0) {
				lep1_qsc_branch->GetEntry(index);
			} else { 
				printf("branch lep1_qsc_branch does not exist!\n");
				exit(1);
			}
			lep1_qsc_isLoaded = true;
		}
		return lep1_qsc_;
	}
	int &lep1_qctf()
	{
		if (not lep1_qctf_isLoaded) {
			if (lep1_qctf_branch != 0) {
				lep1_qctf_branch->GetEntry(index);
			} else { 
				printf("branch lep1_qctf_branch does not exist!\n");
				exit(1);
			}
			lep1_qctf_isLoaded = true;
		}
		return lep1_qctf_;
	}
	int &lep1_qgsf()
	{
		if (not lep1_qgsf_isLoaded) {
			if (lep1_qgsf_branch != 0) {
				lep1_qgsf_branch->GetEntry(index);
			} else { 
				printf("branch lep1_qgsf_branch does not exist!\n");
				exit(1);
			}
			lep1_qgsf_isLoaded = true;
		}
		return lep1_qgsf_;
	}
	int &lep1_nmhits()
	{
		if (not lep1_nmhits_isLoaded) {
			if (lep1_nmhits_branch != 0) {
				lep1_nmhits_branch->GetEntry(index);
			} else { 
				printf("branch lep1_nmhits_branch does not exist!\n");
				exit(1);
			}
			lep1_nmhits_isLoaded = true;
		}
		return lep1_nmhits_;
	}
	int &lep1_eleid_veto()
	{
		if (not lep1_eleid_veto_isLoaded) {
			if (lep1_eleid_veto_branch != 0) {
				lep1_eleid_veto_branch->GetEntry(index);
			} else { 
				printf("branch lep1_eleid_veto_branch does not exist!\n");
				exit(1);
			}
			lep1_eleid_veto_isLoaded = true;
		}
		return lep1_eleid_veto_;
	}
	int &lep1_eleid_loose()
	{
		if (not lep1_eleid_loose_isLoaded) {
			if (lep1_eleid_loose_branch != 0) {
				lep1_eleid_loose_branch->GetEntry(index);
			} else { 
				printf("branch lep1_eleid_loose_branch does not exist!\n");
				exit(1);
			}
			lep1_eleid_loose_isLoaded = true;
		}
		return lep1_eleid_loose_;
	}
	int &lep1_eleid_medium()
	{
		if (not lep1_eleid_medium_isLoaded) {
			if (lep1_eleid_medium_branch != 0) {
				lep1_eleid_medium_branch->GetEntry(index);
			} else { 
				printf("branch lep1_eleid_medium_branch does not exist!\n");
				exit(1);
			}
			lep1_eleid_medium_isLoaded = true;
		}
		return lep1_eleid_medium_;
	}
	int &lep1_eleid_tight()
	{
		if (not lep1_eleid_tight_isLoaded) {
			if (lep1_eleid_tight_branch != 0) {
				lep1_eleid_tight_branch->GetEntry(index);
			} else { 
				printf("branch lep1_eleid_tight_branch does not exist!\n");
				exit(1);
			}
			lep1_eleid_tight_isLoaded = true;
		}
		return lep1_eleid_tight_;
	}
	float &lep1_dphiin()
	{
		if (not lep1_dphiin_isLoaded) {
			if (lep1_dphiin_branch != 0) {
				lep1_dphiin_branch->GetEntry(index);
			} else { 
				printf("branch lep1_dphiin_branch does not exist!\n");
				exit(1);
			}
			lep1_dphiin_isLoaded = true;
		}
		return lep1_dphiin_;
	}
	float &lep1_detain()
	{
		if (not lep1_detain_isLoaded) {
			if (lep1_detain_branch != 0) {
				lep1_detain_branch->GetEntry(index);
			} else { 
				printf("branch lep1_detain_branch does not exist!\n");
				exit(1);
			}
			lep1_detain_isLoaded = true;
		}
		return lep1_detain_;
	}
	float &lep1_sieie()
	{
		if (not lep1_sieie_isLoaded) {
			if (lep1_sieie_branch != 0) {
				lep1_sieie_branch->GetEntry(index);
			} else { 
				printf("branch lep1_sieie_branch does not exist!\n");
				exit(1);
			}
			lep1_sieie_isLoaded = true;
		}
		return lep1_sieie_;
	}
	float &lep1_hoe()
	{
		if (not lep1_hoe_isLoaded) {
			if (lep1_hoe_branch != 0) {
				lep1_hoe_branch->GetEntry(index);
			} else { 
				printf("branch lep1_hoe_branch does not exist!\n");
				exit(1);
			}
			lep1_hoe_isLoaded = true;
		}
		return lep1_hoe_;
	}
	float &lep1_ooemoop()
	{
		if (not lep1_ooemoop_isLoaded) {
			if (lep1_ooemoop_branch != 0) {
				lep1_ooemoop_branch->GetEntry(index);
			} else { 
				printf("branch lep1_ooemoop_branch does not exist!\n");
				exit(1);
			}
			lep1_ooemoop_isLoaded = true;
		}
		return lep1_ooemoop_;
	}
	float &lep1_conv_dist()
	{
		if (not lep1_conv_dist_isLoaded) {
			if (lep1_conv_dist_branch != 0) {
				lep1_conv_dist_branch->GetEntry(index);
			} else { 
				printf("branch lep1_conv_dist_branch does not exist!\n");
				exit(1);
			}
			lep1_conv_dist_isLoaded = true;
		}
		return lep1_conv_dist_;
	}
	float &lep1_conv_dcot()
	{
		if (not lep1_conv_dcot_isLoaded) {
			if (lep1_conv_dcot_branch != 0) {
				lep1_conv_dcot_branch->GetEntry(index);
			} else { 
				printf("branch lep1_conv_dcot_branch does not exist!\n");
				exit(1);
			}
			lep1_conv_dcot_isLoaded = true;
		}
		return lep1_conv_dcot_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_gfit_p4()
	{
		if (not lep1_gfit_p4_isLoaded) {
			if (lep1_gfit_p4_branch != 0) {
				lep1_gfit_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep1_gfit_p4_branch does not exist!\n");
				exit(1);
			}
			lep1_gfit_p4_isLoaded = true;
		}
		return *lep1_gfit_p4_;
	}
	bool &	lep1_is_global()
	{
		if (not lep1_is_global_isLoaded) {
			if (lep1_is_global_branch != 0) {
				lep1_is_global_branch->GetEntry(index);
			} else { 
				printf("branch lep1_is_global_branch does not exist!\n");
				exit(1);
			}
			lep1_is_global_isLoaded = true;
		}
		return lep1_is_global_;
	}
	bool &	lep1_is_tracker()
	{
		if (not lep1_is_tracker_isLoaded) {
			if (lep1_is_tracker_branch != 0) {
				lep1_is_tracker_branch->GetEntry(index);
			} else { 
				printf("branch lep1_is_tracker_branch does not exist!\n");
				exit(1);
			}
			lep1_is_tracker_isLoaded = true;
		}
		return lep1_is_tracker_;
	}
	bool &	lep1_is_stamu()
	{
		if (not lep1_is_stamu_isLoaded) {
			if (lep1_is_stamu_branch != 0) {
				lep1_is_stamu_branch->GetEntry(index);
			} else { 
				printf("branch lep1_is_stamu_branch does not exist!\n");
				exit(1);
			}
			lep1_is_stamu_isLoaded = true;
		}
		return lep1_is_stamu_;
	}
	bool &	lep1_is_pfmu()
	{
		if (not lep1_is_pfmu_isLoaded) {
			if (lep1_is_pfmu_branch != 0) {
				lep1_is_pfmu_branch->GetEntry(index);
			} else { 
				printf("branch lep1_is_pfmu_branch does not exist!\n");
				exit(1);
			}
			lep1_is_pfmu_isLoaded = true;
		}
		return lep1_is_pfmu_;
	}
	bool &	lep1_is_loosemu()
	{
		if (not lep1_is_loosemu_isLoaded) {
			if (lep1_is_loosemu_branch != 0) {
				lep1_is_loosemu_branch->GetEntry(index);
			} else { 
				printf("branch lep1_is_loosemu_branch does not exist!\n");
				exit(1);
			}
			lep1_is_loosemu_isLoaded = true;
		}
		return lep1_is_loosemu_;
	}
	bool &	lep1_is_tightmu()
	{
		if (not lep1_is_tightmu_isLoaded) {
			if (lep1_is_tightmu_branch != 0) {
				lep1_is_tightmu_branch->GetEntry(index);
			} else { 
				printf("branch lep1_is_tightmu_branch does not exist!\n");
				exit(1);
			}
			lep1_is_tightmu_isLoaded = true;
		}
		return lep1_is_tightmu_;
	}
	int &lep1_npixelhits()
	{
		if (not lep1_npixelhits_isLoaded) {
			if (lep1_npixelhits_branch != 0) {
				lep1_npixelhits_branch->GetEntry(index);
			} else { 
				printf("branch lep1_npixelhits_branch does not exist!\n");
				exit(1);
			}
			lep1_npixelhits_isLoaded = true;
		}
		return lep1_npixelhits_;
	}
	int &lep1_nsihits()
	{
		if (not lep1_nsihits_isLoaded) {
			if (lep1_nsihits_branch != 0) {
				lep1_nsihits_branch->GetEntry(index);
			} else { 
				printf("branch lep1_nsihits_branch does not exist!\n");
				exit(1);
			}
			lep1_nsihits_isLoaded = true;
		}
		return lep1_nsihits_;
	}
	int &lep1_nsilayers()
	{
		if (not lep1_nsilayers_isLoaded) {
			if (lep1_nsilayers_branch != 0) {
				lep1_nsilayers_branch->GetEntry(index);
			} else { 
				printf("branch lep1_nsilayers_branch does not exist!\n");
				exit(1);
			}
			lep1_nsilayers_isLoaded = true;
		}
		return lep1_nsilayers_;
	}
	int &lep1_nstahits()
	{
		if (not lep1_nstahits_isLoaded) {
			if (lep1_nstahits_branch != 0) {
				lep1_nstahits_branch->GetEntry(index);
			} else { 
				printf("branch lep1_nstahits_branch does not exist!\n");
				exit(1);
			}
			lep1_nstahits_isLoaded = true;
		}
		return lep1_nstahits_;
	}
	int &lep1_nstations()
	{
		if (not lep1_nstations_isLoaded) {
			if (lep1_nstations_branch != 0) {
				lep1_nstations_branch->GetEntry(index);
			} else { 
				printf("branch lep1_nstations_branch does not exist!\n");
				exit(1);
			}
			lep1_nstations_isLoaded = true;
		}
		return lep1_nstations_;
	}
	float &lep1_chi2()
	{
		if (not lep1_chi2_isLoaded) {
			if (lep1_chi2_branch != 0) {
				lep1_chi2_branch->GetEntry(index);
			} else { 
				printf("branch lep1_chi2_branch does not exist!\n");
				exit(1);
			}
			lep1_chi2_isLoaded = true;
		}
		return lep1_chi2_;
	}
	float &lep1_ndof()
	{
		if (not lep1_ndof_isLoaded) {
			if (lep1_ndof_branch != 0) {
				lep1_ndof_branch->GetEntry(index);
			} else { 
				printf("branch lep1_ndof_branch does not exist!\n");
				exit(1);
			}
			lep1_ndof_isLoaded = true;
		}
		return lep1_ndof_;
	}
	float &lep1_pterr()
	{
		if (not lep1_pterr_isLoaded) {
			if (lep1_pterr_branch != 0) {
				lep1_pterr_branch->GetEntry(index);
			} else { 
				printf("branch lep1_pterr_branch does not exist!\n");
				exit(1);
			}
			lep1_pterr_isLoaded = true;
		}
		return lep1_pterr_;
	}
	float &lep1_ecal_vetodep()
	{
		if (not lep1_ecal_vetodep_isLoaded) {
			if (lep1_ecal_vetodep_branch != 0) {
				lep1_ecal_vetodep_branch->GetEntry(index);
			} else { 
				printf("branch lep1_ecal_vetodep_branch does not exist!\n");
				exit(1);
			}
			lep1_ecal_vetodep_isLoaded = true;
		}
		return lep1_ecal_vetodep_;
	}
	float &lep1_hcal_vetodep()
	{
		if (not lep1_hcal_vetodep_isLoaded) {
			if (lep1_hcal_vetodep_branch != 0) {
				lep1_hcal_vetodep_branch->GetEntry(index);
			} else { 
				printf("branch lep1_hcal_vetodep_branch does not exist!\n");
				exit(1);
			}
			lep1_hcal_vetodep_isLoaded = true;
		}
		return lep1_hcal_vetodep_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_p4()
	{
		if (not lep2_p4_isLoaded) {
			if (lep2_p4_branch != 0) {
				lep2_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep2_p4_branch does not exist!\n");
				exit(1);
			}
			lep2_p4_isLoaded = true;
		}
		return *lep2_p4_;
	}
	bool &	lep2_passes_id()
	{
		if (not lep2_passes_id_isLoaded) {
			if (lep2_passes_id_branch != 0) {
				lep2_passes_id_branch->GetEntry(index);
			} else { 
				printf("branch lep2_passes_id_branch does not exist!\n");
				exit(1);
			}
			lep2_passes_id_isLoaded = true;
		}
		return lep2_passes_id_;
	}
	bool &	lep2_passes_iso()
	{
		if (not lep2_passes_iso_isLoaded) {
			if (lep2_passes_iso_branch != 0) {
				lep2_passes_iso_branch->GetEntry(index);
			} else { 
				printf("branch lep2_passes_iso_branch does not exist!\n");
				exit(1);
			}
			lep2_passes_iso_isLoaded = true;
		}
		return lep2_passes_iso_;
	}
	bool &	lep2_is_num()
	{
		if (not lep2_is_num_isLoaded) {
			if (lep2_is_num_branch != 0) {
				lep2_is_num_branch->GetEntry(index);
			} else { 
				printf("branch lep2_is_num_branch does not exist!\n");
				exit(1);
			}
			lep2_is_num_isLoaded = true;
		}
		return lep2_is_num_;
	}
	bool &	lep2_is_fo()
	{
		if (not lep2_is_fo_isLoaded) {
			if (lep2_is_fo_branch != 0) {
				lep2_is_fo_branch->GetEntry(index);
			} else { 
				printf("branch lep2_is_fo_branch does not exist!\n");
				exit(1);
			}
			lep2_is_fo_isLoaded = true;
		}
		return lep2_is_fo_;
	}
	int &lep2_charge()
	{
		if (not lep2_charge_isLoaded) {
			if (lep2_charge_branch != 0) {
				lep2_charge_branch->GetEntry(index);
			} else { 
				printf("branch lep2_charge_branch does not exist!\n");
				exit(1);
			}
			lep2_charge_isLoaded = true;
		}
		return lep2_charge_;
	}
	int &lep2_pdgid()
	{
		if (not lep2_pdgid_isLoaded) {
			if (lep2_pdgid_branch != 0) {
				lep2_pdgid_branch->GetEntry(index);
			} else { 
				printf("branch lep2_pdgid_branch does not exist!\n");
				exit(1);
			}
			lep2_pdgid_isLoaded = true;
		}
		return lep2_pdgid_;
	}
	int &lep2_type()
	{
		if (not lep2_type_isLoaded) {
			if (lep2_type_branch != 0) {
				lep2_type_branch->GetEntry(index);
			} else { 
				printf("branch lep2_type_branch does not exist!\n");
				exit(1);
			}
			lep2_type_isLoaded = true;
		}
		return lep2_type_;
	}
	float &lep2_d0()
	{
		if (not lep2_d0_isLoaded) {
			if (lep2_d0_branch != 0) {
				lep2_d0_branch->GetEntry(index);
			} else { 
				printf("branch lep2_d0_branch does not exist!\n");
				exit(1);
			}
			lep2_d0_isLoaded = true;
		}
		return lep2_d0_;
	}
	float &lep2_dz()
	{
		if (not lep2_dz_isLoaded) {
			if (lep2_dz_branch != 0) {
				lep2_dz_branch->GetEntry(index);
			} else { 
				printf("branch lep2_dz_branch does not exist!\n");
				exit(1);
			}
			lep2_dz_isLoaded = true;
		}
		return lep2_dz_;
	}
	float &lep2_mt()
	{
		if (not lep2_mt_isLoaded) {
			if (lep2_mt_branch != 0) {
				lep2_mt_branch->GetEntry(index);
			} else { 
				printf("branch lep2_mt_branch does not exist!\n");
				exit(1);
			}
			lep2_mt_isLoaded = true;
		}
		return lep2_mt_;
	}
	float &lep2_corpfiso()
	{
		if (not lep2_corpfiso_isLoaded) {
			if (lep2_corpfiso_branch != 0) {
				lep2_corpfiso_branch->GetEntry(index);
			} else { 
				printf("branch lep2_corpfiso_branch does not exist!\n");
				exit(1);
			}
			lep2_corpfiso_isLoaded = true;
		}
		return lep2_corpfiso_;
	}
	float &lep2_pfiso()
	{
		if (not lep2_pfiso_isLoaded) {
			if (lep2_pfiso_branch != 0) {
				lep2_pfiso_branch->GetEntry(index);
			} else { 
				printf("branch lep2_pfiso_branch does not exist!\n");
				exit(1);
			}
			lep2_pfiso_isLoaded = true;
		}
		return lep2_pfiso_;
	}
	float &lep2_chiso()
	{
		if (not lep2_chiso_isLoaded) {
			if (lep2_chiso_branch != 0) {
				lep2_chiso_branch->GetEntry(index);
			} else { 
				printf("branch lep2_chiso_branch does not exist!\n");
				exit(1);
			}
			lep2_chiso_isLoaded = true;
		}
		return lep2_chiso_;
	}
	float &lep2_emiso()
	{
		if (not lep2_emiso_isLoaded) {
			if (lep2_emiso_branch != 0) {
				lep2_emiso_branch->GetEntry(index);
			} else { 
				printf("branch lep2_emiso_branch does not exist!\n");
				exit(1);
			}
			lep2_emiso_isLoaded = true;
		}
		return lep2_emiso_;
	}
	float &lep2_nhiso()
	{
		if (not lep2_nhiso_isLoaded) {
			if (lep2_nhiso_branch != 0) {
				lep2_nhiso_branch->GetEntry(index);
			} else { 
				printf("branch lep2_nhiso_branch does not exist!\n");
				exit(1);
			}
			lep2_nhiso_isLoaded = true;
		}
		return lep2_nhiso_;
	}
	float &lep2_corpfiso04()
	{
		if (not lep2_corpfiso04_isLoaded) {
			if (lep2_corpfiso04_branch != 0) {
				lep2_corpfiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep2_corpfiso04_branch does not exist!\n");
				exit(1);
			}
			lep2_corpfiso04_isLoaded = true;
		}
		return lep2_corpfiso04_;
	}
	float &lep2_pfiso04()
	{
		if (not lep2_pfiso04_isLoaded) {
			if (lep2_pfiso04_branch != 0) {
				lep2_pfiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep2_pfiso04_branch does not exist!\n");
				exit(1);
			}
			lep2_pfiso04_isLoaded = true;
		}
		return lep2_pfiso04_;
	}
	float &lep2_chiso04()
	{
		if (not lep2_chiso04_isLoaded) {
			if (lep2_chiso04_branch != 0) {
				lep2_chiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep2_chiso04_branch does not exist!\n");
				exit(1);
			}
			lep2_chiso04_isLoaded = true;
		}
		return lep2_chiso04_;
	}
	float &lep2_emiso04()
	{
		if (not lep2_emiso04_isLoaded) {
			if (lep2_emiso04_branch != 0) {
				lep2_emiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep2_emiso04_branch does not exist!\n");
				exit(1);
			}
			lep2_emiso04_isLoaded = true;
		}
		return lep2_emiso04_;
	}
	float &lep2_nhiso04()
	{
		if (not lep2_nhiso04_isLoaded) {
			if (lep2_nhiso04_branch != 0) {
				lep2_nhiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep2_nhiso04_branch does not exist!\n");
				exit(1);
			}
			lep2_nhiso04_isLoaded = true;
		}
		return lep2_nhiso04_;
	}
	float &lep2_cordetiso()
	{
		if (not lep2_cordetiso_isLoaded) {
			if (lep2_cordetiso_branch != 0) {
				lep2_cordetiso_branch->GetEntry(index);
			} else { 
				printf("branch lep2_cordetiso_branch does not exist!\n");
				exit(1);
			}
			lep2_cordetiso_isLoaded = true;
		}
		return lep2_cordetiso_;
	}
	float &lep2_detiso()
	{
		if (not lep2_detiso_isLoaded) {
			if (lep2_detiso_branch != 0) {
				lep2_detiso_branch->GetEntry(index);
			} else { 
				printf("branch lep2_detiso_branch does not exist!\n");
				exit(1);
			}
			lep2_detiso_isLoaded = true;
		}
		return lep2_detiso_;
	}
	float &lep2_trkiso()
	{
		if (not lep2_trkiso_isLoaded) {
			if (lep2_trkiso_branch != 0) {
				lep2_trkiso_branch->GetEntry(index);
			} else { 
				printf("branch lep2_trkiso_branch does not exist!\n");
				exit(1);
			}
			lep2_trkiso_isLoaded = true;
		}
		return lep2_trkiso_;
	}
	float &lep2_ecaliso()
	{
		if (not lep2_ecaliso_isLoaded) {
			if (lep2_ecaliso_branch != 0) {
				lep2_ecaliso_branch->GetEntry(index);
			} else { 
				printf("branch lep2_ecaliso_branch does not exist!\n");
				exit(1);
			}
			lep2_ecaliso_isLoaded = true;
		}
		return lep2_ecaliso_;
	}
	float &lep2_hcaliso()
	{
		if (not lep2_hcaliso_isLoaded) {
			if (lep2_hcaliso_branch != 0) {
				lep2_hcaliso_branch->GetEntry(index);
			} else { 
				printf("branch lep2_hcaliso_branch does not exist!\n");
				exit(1);
			}
			lep2_hcaliso_isLoaded = true;
		}
		return lep2_hcaliso_;
	}
	float &lep2_cordetiso04()
	{
		if (not lep2_cordetiso04_isLoaded) {
			if (lep2_cordetiso04_branch != 0) {
				lep2_cordetiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep2_cordetiso04_branch does not exist!\n");
				exit(1);
			}
			lep2_cordetiso04_isLoaded = true;
		}
		return lep2_cordetiso04_;
	}
	float &lep2_detiso04()
	{
		if (not lep2_detiso04_isLoaded) {
			if (lep2_detiso04_branch != 0) {
				lep2_detiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep2_detiso04_branch does not exist!\n");
				exit(1);
			}
			lep2_detiso04_isLoaded = true;
		}
		return lep2_detiso04_;
	}
	float &lep2_trkiso04()
	{
		if (not lep2_trkiso04_isLoaded) {
			if (lep2_trkiso04_branch != 0) {
				lep2_trkiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep2_trkiso04_branch does not exist!\n");
				exit(1);
			}
			lep2_trkiso04_isLoaded = true;
		}
		return lep2_trkiso04_;
	}
	float &lep2_ecaliso04()
	{
		if (not lep2_ecaliso04_isLoaded) {
			if (lep2_ecaliso04_branch != 0) {
				lep2_ecaliso04_branch->GetEntry(index);
			} else { 
				printf("branch lep2_ecaliso04_branch does not exist!\n");
				exit(1);
			}
			lep2_ecaliso04_isLoaded = true;
		}
		return lep2_ecaliso04_;
	}
	float &lep2_hcaliso04()
	{
		if (not lep2_hcaliso04_isLoaded) {
			if (lep2_hcaliso04_branch != 0) {
				lep2_hcaliso04_branch->GetEntry(index);
			} else { 
				printf("branch lep2_hcaliso04_branch does not exist!\n");
				exit(1);
			}
			lep2_hcaliso04_isLoaded = true;
		}
		return lep2_hcaliso04_;
	}
	float &lep2_effarea()
	{
		if (not lep2_effarea_isLoaded) {
			if (lep2_effarea_branch != 0) {
				lep2_effarea_branch->GetEntry(index);
			} else { 
				printf("branch lep2_effarea_branch does not exist!\n");
				exit(1);
			}
			lep2_effarea_isLoaded = true;
		}
		return lep2_effarea_;
	}
	float &lep2_effarea04()
	{
		if (not lep2_effarea04_isLoaded) {
			if (lep2_effarea04_branch != 0) {
				lep2_effarea04_branch->GetEntry(index);
			} else { 
				printf("branch lep2_effarea04_branch does not exist!\n");
				exit(1);
			}
			lep2_effarea04_isLoaded = true;
		}
		return lep2_effarea04_;
	}
	float &lep2_dbeta()
	{
		if (not lep2_dbeta_isLoaded) {
			if (lep2_dbeta_branch != 0) {
				lep2_dbeta_branch->GetEntry(index);
			} else { 
				printf("branch lep2_dbeta_branch does not exist!\n");
				exit(1);
			}
			lep2_dbeta_isLoaded = true;
		}
		return lep2_dbeta_;
	}
	float &lep2_dbeta04()
	{
		if (not lep2_dbeta04_isLoaded) {
			if (lep2_dbeta04_branch != 0) {
				lep2_dbeta04_branch->GetEntry(index);
			} else { 
				printf("branch lep2_dbeta04_branch does not exist!\n");
				exit(1);
			}
			lep2_dbeta04_isLoaded = true;
		}
		return lep2_dbeta04_;
	}
	float &lep2_sf_lepeff()
	{
		if (not lep2_sf_lepeff_isLoaded) {
			if (lep2_sf_lepeff_branch != 0) {
				lep2_sf_lepeff_branch->GetEntry(index);
			} else { 
				printf("branch lep2_sf_lepeff_branch does not exist!\n");
				exit(1);
			}
			lep2_sf_lepeff_isLoaded = true;
		}
		return lep2_sf_lepeff_;
	}
	float &lep2_sf_trig()
	{
		if (not lep2_sf_trig_isLoaded) {
			if (lep2_sf_trig_branch != 0) {
				lep2_sf_trig_branch->GetEntry(index);
			} else { 
				printf("branch lep2_sf_trig_branch does not exist!\n");
				exit(1);
			}
			lep2_sf_trig_isLoaded = true;
		}
		return lep2_sf_trig_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mcp4()
	{
		if (not lep2_mcp4_isLoaded) {
			if (lep2_mcp4_branch != 0) {
				lep2_mcp4_branch->GetEntry(index);
			} else { 
				printf("branch lep2_mcp4_branch does not exist!\n");
				exit(1);
			}
			lep2_mcp4_isLoaded = true;
		}
		return *lep2_mcp4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mc3p4()
	{
		if (not lep2_mc3p4_isLoaded) {
			if (lep2_mc3p4_branch != 0) {
				lep2_mc3p4_branch->GetEntry(index);
			} else { 
				printf("branch lep2_mc3p4_branch does not exist!\n");
				exit(1);
			}
			lep2_mc3p4_isLoaded = true;
		}
		return *lep2_mc3p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mc_momp4()
	{
		if (not lep2_mc_momp4_isLoaded) {
			if (lep2_mc_momp4_branch != 0) {
				lep2_mc_momp4_branch->GetEntry(index);
			} else { 
				printf("branch lep2_mc_momp4_branch does not exist!\n");
				exit(1);
			}
			lep2_mc_momp4_isLoaded = true;
		}
		return *lep2_mc_momp4_;
	}
	int &lep2_mcid()
	{
		if (not lep2_mcid_isLoaded) {
			if (lep2_mcid_branch != 0) {
				lep2_mcid_branch->GetEntry(index);
			} else { 
				printf("branch lep2_mcid_branch does not exist!\n");
				exit(1);
			}
			lep2_mcid_isLoaded = true;
		}
		return lep2_mcid_;
	}
	int &lep2_mc3id()
	{
		if (not lep2_mc3id_isLoaded) {
			if (lep2_mc3id_branch != 0) {
				lep2_mc3id_branch->GetEntry(index);
			} else { 
				printf("branch lep2_mc3id_branch does not exist!\n");
				exit(1);
			}
			lep2_mc3id_isLoaded = true;
		}
		return lep2_mc3id_;
	}
	int &lep2_momid()
	{
		if (not lep2_momid_isLoaded) {
			if (lep2_momid_branch != 0) {
				lep2_momid_branch->GetEntry(index);
			} else { 
				printf("branch lep2_momid_branch does not exist!\n");
				exit(1);
			}
			lep2_momid_isLoaded = true;
		}
		return lep2_momid_;
	}
	int &lep2_mc3_momid()
	{
		if (not lep2_mc3_momid_isLoaded) {
			if (lep2_mc3_momid_branch != 0) {
				lep2_mc3_momid_branch->GetEntry(index);
			} else { 
				printf("branch lep2_mc3_momid_branch does not exist!\n");
				exit(1);
			}
			lep2_mc3_momid_isLoaded = true;
		}
		return lep2_mc3_momid_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_gsf_p4()
	{
		if (not lep2_gsf_p4_isLoaded) {
			if (lep2_gsf_p4_branch != 0) {
				lep2_gsf_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep2_gsf_p4_branch does not exist!\n");
				exit(1);
			}
			lep2_gsf_p4_isLoaded = true;
		}
		return *lep2_gsf_p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_ctf_p4()
	{
		if (not lep2_ctf_p4_isLoaded) {
			if (lep2_ctf_p4_branch != 0) {
				lep2_ctf_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep2_ctf_p4_branch does not exist!\n");
				exit(1);
			}
			lep2_ctf_p4_isLoaded = true;
		}
		return *lep2_ctf_p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_sc_p4()
	{
		if (not lep2_sc_p4_isLoaded) {
			if (lep2_sc_p4_branch != 0) {
				lep2_sc_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep2_sc_p4_branch does not exist!\n");
				exit(1);
			}
			lep2_sc_p4_isLoaded = true;
		}
		return *lep2_sc_p4_;
	}
	bool &	lep2_q3agree()
	{
		if (not lep2_q3agree_isLoaded) {
			if (lep2_q3agree_branch != 0) {
				lep2_q3agree_branch->GetEntry(index);
			} else { 
				printf("branch lep2_q3agree_branch does not exist!\n");
				exit(1);
			}
			lep2_q3agree_isLoaded = true;
		}
		return lep2_q3agree_;
	}
	bool &	lep2_is_conv()
	{
		if (not lep2_is_conv_isLoaded) {
			if (lep2_is_conv_branch != 0) {
				lep2_is_conv_branch->GetEntry(index);
			} else { 
				printf("branch lep2_is_conv_branch does not exist!\n");
				exit(1);
			}
			lep2_is_conv_isLoaded = true;
		}
		return lep2_is_conv_;
	}
	int &lep2_qsc()
	{
		if (not lep2_qsc_isLoaded) {
			if (lep2_qsc_branch != 0) {
				lep2_qsc_branch->GetEntry(index);
			} else { 
				printf("branch lep2_qsc_branch does not exist!\n");
				exit(1);
			}
			lep2_qsc_isLoaded = true;
		}
		return lep2_qsc_;
	}
	int &lep2_qctf()
	{
		if (not lep2_qctf_isLoaded) {
			if (lep2_qctf_branch != 0) {
				lep2_qctf_branch->GetEntry(index);
			} else { 
				printf("branch lep2_qctf_branch does not exist!\n");
				exit(1);
			}
			lep2_qctf_isLoaded = true;
		}
		return lep2_qctf_;
	}
	int &lep2_qgsf()
	{
		if (not lep2_qgsf_isLoaded) {
			if (lep2_qgsf_branch != 0) {
				lep2_qgsf_branch->GetEntry(index);
			} else { 
				printf("branch lep2_qgsf_branch does not exist!\n");
				exit(1);
			}
			lep2_qgsf_isLoaded = true;
		}
		return lep2_qgsf_;
	}
	int &lep2_nmhits()
	{
		if (not lep2_nmhits_isLoaded) {
			if (lep2_nmhits_branch != 0) {
				lep2_nmhits_branch->GetEntry(index);
			} else { 
				printf("branch lep2_nmhits_branch does not exist!\n");
				exit(1);
			}
			lep2_nmhits_isLoaded = true;
		}
		return lep2_nmhits_;
	}
	int &lep2_eleid_veto()
	{
		if (not lep2_eleid_veto_isLoaded) {
			if (lep2_eleid_veto_branch != 0) {
				lep2_eleid_veto_branch->GetEntry(index);
			} else { 
				printf("branch lep2_eleid_veto_branch does not exist!\n");
				exit(1);
			}
			lep2_eleid_veto_isLoaded = true;
		}
		return lep2_eleid_veto_;
	}
	int &lep2_eleid_loose()
	{
		if (not lep2_eleid_loose_isLoaded) {
			if (lep2_eleid_loose_branch != 0) {
				lep2_eleid_loose_branch->GetEntry(index);
			} else { 
				printf("branch lep2_eleid_loose_branch does not exist!\n");
				exit(1);
			}
			lep2_eleid_loose_isLoaded = true;
		}
		return lep2_eleid_loose_;
	}
	int &lep2_eleid_medium()
	{
		if (not lep2_eleid_medium_isLoaded) {
			if (lep2_eleid_medium_branch != 0) {
				lep2_eleid_medium_branch->GetEntry(index);
			} else { 
				printf("branch lep2_eleid_medium_branch does not exist!\n");
				exit(1);
			}
			lep2_eleid_medium_isLoaded = true;
		}
		return lep2_eleid_medium_;
	}
	int &lep2_eleid_tight()
	{
		if (not lep2_eleid_tight_isLoaded) {
			if (lep2_eleid_tight_branch != 0) {
				lep2_eleid_tight_branch->GetEntry(index);
			} else { 
				printf("branch lep2_eleid_tight_branch does not exist!\n");
				exit(1);
			}
			lep2_eleid_tight_isLoaded = true;
		}
		return lep2_eleid_tight_;
	}
	float &lep2_dphiin()
	{
		if (not lep2_dphiin_isLoaded) {
			if (lep2_dphiin_branch != 0) {
				lep2_dphiin_branch->GetEntry(index);
			} else { 
				printf("branch lep2_dphiin_branch does not exist!\n");
				exit(1);
			}
			lep2_dphiin_isLoaded = true;
		}
		return lep2_dphiin_;
	}
	float &lep2_detain()
	{
		if (not lep2_detain_isLoaded) {
			if (lep2_detain_branch != 0) {
				lep2_detain_branch->GetEntry(index);
			} else { 
				printf("branch lep2_detain_branch does not exist!\n");
				exit(1);
			}
			lep2_detain_isLoaded = true;
		}
		return lep2_detain_;
	}
	float &lep2_sieie()
	{
		if (not lep2_sieie_isLoaded) {
			if (lep2_sieie_branch != 0) {
				lep2_sieie_branch->GetEntry(index);
			} else { 
				printf("branch lep2_sieie_branch does not exist!\n");
				exit(1);
			}
			lep2_sieie_isLoaded = true;
		}
		return lep2_sieie_;
	}
	float &lep2_hoe()
	{
		if (not lep2_hoe_isLoaded) {
			if (lep2_hoe_branch != 0) {
				lep2_hoe_branch->GetEntry(index);
			} else { 
				printf("branch lep2_hoe_branch does not exist!\n");
				exit(1);
			}
			lep2_hoe_isLoaded = true;
		}
		return lep2_hoe_;
	}
	float &lep2_ooemoop()
	{
		if (not lep2_ooemoop_isLoaded) {
			if (lep2_ooemoop_branch != 0) {
				lep2_ooemoop_branch->GetEntry(index);
			} else { 
				printf("branch lep2_ooemoop_branch does not exist!\n");
				exit(1);
			}
			lep2_ooemoop_isLoaded = true;
		}
		return lep2_ooemoop_;
	}
	float &lep2_conv_dist()
	{
		if (not lep2_conv_dist_isLoaded) {
			if (lep2_conv_dist_branch != 0) {
				lep2_conv_dist_branch->GetEntry(index);
			} else { 
				printf("branch lep2_conv_dist_branch does not exist!\n");
				exit(1);
			}
			lep2_conv_dist_isLoaded = true;
		}
		return lep2_conv_dist_;
	}
	float &lep2_conv_dcot()
	{
		if (not lep2_conv_dcot_isLoaded) {
			if (lep2_conv_dcot_branch != 0) {
				lep2_conv_dcot_branch->GetEntry(index);
			} else { 
				printf("branch lep2_conv_dcot_branch does not exist!\n");
				exit(1);
			}
			lep2_conv_dcot_isLoaded = true;
		}
		return lep2_conv_dcot_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_gfit_p4()
	{
		if (not lep2_gfit_p4_isLoaded) {
			if (lep2_gfit_p4_branch != 0) {
				lep2_gfit_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep2_gfit_p4_branch does not exist!\n");
				exit(1);
			}
			lep2_gfit_p4_isLoaded = true;
		}
		return *lep2_gfit_p4_;
	}
	bool &	lep2_is_global()
	{
		if (not lep2_is_global_isLoaded) {
			if (lep2_is_global_branch != 0) {
				lep2_is_global_branch->GetEntry(index);
			} else { 
				printf("branch lep2_is_global_branch does not exist!\n");
				exit(1);
			}
			lep2_is_global_isLoaded = true;
		}
		return lep2_is_global_;
	}
	bool &	lep2_is_tracker()
	{
		if (not lep2_is_tracker_isLoaded) {
			if (lep2_is_tracker_branch != 0) {
				lep2_is_tracker_branch->GetEntry(index);
			} else { 
				printf("branch lep2_is_tracker_branch does not exist!\n");
				exit(1);
			}
			lep2_is_tracker_isLoaded = true;
		}
		return lep2_is_tracker_;
	}
	bool &	lep2_is_stamu()
	{
		if (not lep2_is_stamu_isLoaded) {
			if (lep2_is_stamu_branch != 0) {
				lep2_is_stamu_branch->GetEntry(index);
			} else { 
				printf("branch lep2_is_stamu_branch does not exist!\n");
				exit(1);
			}
			lep2_is_stamu_isLoaded = true;
		}
		return lep2_is_stamu_;
	}
	bool &	lep2_is_pfmu()
	{
		if (not lep2_is_pfmu_isLoaded) {
			if (lep2_is_pfmu_branch != 0) {
				lep2_is_pfmu_branch->GetEntry(index);
			} else { 
				printf("branch lep2_is_pfmu_branch does not exist!\n");
				exit(1);
			}
			lep2_is_pfmu_isLoaded = true;
		}
		return lep2_is_pfmu_;
	}
	bool &	lep2_is_loosemu()
	{
		if (not lep2_is_loosemu_isLoaded) {
			if (lep2_is_loosemu_branch != 0) {
				lep2_is_loosemu_branch->GetEntry(index);
			} else { 
				printf("branch lep2_is_loosemu_branch does not exist!\n");
				exit(1);
			}
			lep2_is_loosemu_isLoaded = true;
		}
		return lep2_is_loosemu_;
	}
	bool &	lep2_is_tightmu()
	{
		if (not lep2_is_tightmu_isLoaded) {
			if (lep2_is_tightmu_branch != 0) {
				lep2_is_tightmu_branch->GetEntry(index);
			} else { 
				printf("branch lep2_is_tightmu_branch does not exist!\n");
				exit(1);
			}
			lep2_is_tightmu_isLoaded = true;
		}
		return lep2_is_tightmu_;
	}
	int &lep2_npixelhits()
	{
		if (not lep2_npixelhits_isLoaded) {
			if (lep2_npixelhits_branch != 0) {
				lep2_npixelhits_branch->GetEntry(index);
			} else { 
				printf("branch lep2_npixelhits_branch does not exist!\n");
				exit(1);
			}
			lep2_npixelhits_isLoaded = true;
		}
		return lep2_npixelhits_;
	}
	int &lep2_nsihits()
	{
		if (not lep2_nsihits_isLoaded) {
			if (lep2_nsihits_branch != 0) {
				lep2_nsihits_branch->GetEntry(index);
			} else { 
				printf("branch lep2_nsihits_branch does not exist!\n");
				exit(1);
			}
			lep2_nsihits_isLoaded = true;
		}
		return lep2_nsihits_;
	}
	int &lep2_nsilayers()
	{
		if (not lep2_nsilayers_isLoaded) {
			if (lep2_nsilayers_branch != 0) {
				lep2_nsilayers_branch->GetEntry(index);
			} else { 
				printf("branch lep2_nsilayers_branch does not exist!\n");
				exit(1);
			}
			lep2_nsilayers_isLoaded = true;
		}
		return lep2_nsilayers_;
	}
	int &lep2_nstahits()
	{
		if (not lep2_nstahits_isLoaded) {
			if (lep2_nstahits_branch != 0) {
				lep2_nstahits_branch->GetEntry(index);
			} else { 
				printf("branch lep2_nstahits_branch does not exist!\n");
				exit(1);
			}
			lep2_nstahits_isLoaded = true;
		}
		return lep2_nstahits_;
	}
	int &lep2_nstations()
	{
		if (not lep2_nstations_isLoaded) {
			if (lep2_nstations_branch != 0) {
				lep2_nstations_branch->GetEntry(index);
			} else { 
				printf("branch lep2_nstations_branch does not exist!\n");
				exit(1);
			}
			lep2_nstations_isLoaded = true;
		}
		return lep2_nstations_;
	}
	float &lep2_chi2()
	{
		if (not lep2_chi2_isLoaded) {
			if (lep2_chi2_branch != 0) {
				lep2_chi2_branch->GetEntry(index);
			} else { 
				printf("branch lep2_chi2_branch does not exist!\n");
				exit(1);
			}
			lep2_chi2_isLoaded = true;
		}
		return lep2_chi2_;
	}
	float &lep2_ndof()
	{
		if (not lep2_ndof_isLoaded) {
			if (lep2_ndof_branch != 0) {
				lep2_ndof_branch->GetEntry(index);
			} else { 
				printf("branch lep2_ndof_branch does not exist!\n");
				exit(1);
			}
			lep2_ndof_isLoaded = true;
		}
		return lep2_ndof_;
	}
	float &lep2_pterr()
	{
		if (not lep2_pterr_isLoaded) {
			if (lep2_pterr_branch != 0) {
				lep2_pterr_branch->GetEntry(index);
			} else { 
				printf("branch lep2_pterr_branch does not exist!\n");
				exit(1);
			}
			lep2_pterr_isLoaded = true;
		}
		return lep2_pterr_;
	}
	float &lep2_ecal_vetodep()
	{
		if (not lep2_ecal_vetodep_isLoaded) {
			if (lep2_ecal_vetodep_branch != 0) {
				lep2_ecal_vetodep_branch->GetEntry(index);
			} else { 
				printf("branch lep2_ecal_vetodep_branch does not exist!\n");
				exit(1);
			}
			lep2_ecal_vetodep_isLoaded = true;
		}
		return lep2_ecal_vetodep_;
	}
	float &lep2_hcal_vetodep()
	{
		if (not lep2_hcal_vetodep_isLoaded) {
			if (lep2_hcal_vetodep_branch != 0) {
				lep2_hcal_vetodep_branch->GetEntry(index);
			} else { 
				printf("branch lep2_hcal_vetodep_branch does not exist!\n");
				exit(1);
			}
			lep2_hcal_vetodep_isLoaded = true;
		}
		return lep2_hcal_vetodep_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &dilep_p4()
	{
		if (not dilep_p4_isLoaded) {
			if (dilep_p4_branch != 0) {
				dilep_p4_branch->GetEntry(index);
			} else { 
				printf("branch dilep_p4_branch does not exist!\n");
				exit(1);
			}
			dilep_p4_isLoaded = true;
		}
		return *dilep_p4_;
	}
	bool &	is_os()
	{
		if (not is_os_isLoaded) {
			if (is_os_branch != 0) {
				is_os_branch->GetEntry(index);
			} else { 
				printf("branch is_os_branch does not exist!\n");
				exit(1);
			}
			is_os_isLoaded = true;
		}
		return is_os_;
	}
	bool &	is_ss()
	{
		if (not is_ss_isLoaded) {
			if (is_ss_branch != 0) {
				is_ss_branch->GetEntry(index);
			} else { 
				printf("branch is_ss_branch does not exist!\n");
				exit(1);
			}
			is_ss_isLoaded = true;
		}
		return is_ss_;
	}
	int &dilep_type()
	{
		if (not dilep_type_isLoaded) {
			if (dilep_type_branch != 0) {
				dilep_type_branch->GetEntry(index);
			} else { 
				printf("branch dilep_type_branch does not exist!\n");
				exit(1);
			}
			dilep_type_isLoaded = true;
		}
		return dilep_type_;
	}
	int &dilep_gen_type()
	{
		if (not dilep_gen_type_isLoaded) {
			if (dilep_gen_type_branch != 0) {
				dilep_gen_type_branch->GetEntry(index);
			} else { 
				printf("branch dilep_gen_type_branch does not exist!\n");
				exit(1);
			}
			dilep_gen_type_isLoaded = true;
		}
		return dilep_gen_type_;
	}
	float &dilep_mass()
	{
		if (not dilep_mass_isLoaded) {
			if (dilep_mass_branch != 0) {
				dilep_mass_branch->GetEntry(index);
			} else { 
				printf("branch dilep_mass_branch does not exist!\n");
				exit(1);
			}
			dilep_mass_isLoaded = true;
		}
		return dilep_mass_;
	}
	float &dilep_dphi()
	{
		if (not dilep_dphi_isLoaded) {
			if (dilep_dphi_branch != 0) {
				dilep_dphi_branch->GetEntry(index);
			} else { 
				printf("branch dilep_dphi_branch does not exist!\n");
				exit(1);
			}
			dilep_dphi_isLoaded = true;
		}
		return dilep_dphi_;
	}
	float &dilep_deta()
	{
		if (not dilep_deta_isLoaded) {
			if (dilep_deta_branch != 0) {
				dilep_deta_branch->GetEntry(index);
			} else { 
				printf("branch dilep_deta_branch does not exist!\n");
				exit(1);
			}
			dilep_deta_isLoaded = true;
		}
		return dilep_deta_;
	}
	float &dilep_dr()
	{
		if (not dilep_dr_isLoaded) {
			if (dilep_dr_branch != 0) {
				dilep_dr_branch->GetEntry(index);
			} else { 
				printf("branch dilep_dr_branch does not exist!\n");
				exit(1);
			}
			dilep_dr_isLoaded = true;
		}
		return dilep_dr_;
	}
	int &fiduciality()
	{
		if (not fiduciality_isLoaded) {
			if (fiduciality_branch != 0) {
				fiduciality_branch->GetEntry(index);
			} else { 
				printf("branch fiduciality_branch does not exist!\n");
				exit(1);
			}
			fiduciality_isLoaded = true;
		}
		return fiduciality_;
	}
	unsigned int &selection()
	{
		if (not selection_isLoaded) {
			if (selection_branch != 0) {
				selection_branch->GetEntry(index);
			} else { 
				printf("branch selection_branch does not exist!\n");
				exit(1);
			}
			selection_isLoaded = true;
		}
		return selection_;
	}
	bool &	is_good_lumi()
	{
		if (not is_good_lumi_isLoaded) {
			if (is_good_lumi_branch != 0) {
				is_good_lumi_branch->GetEntry(index);
			} else { 
				printf("branch is_good_lumi_branch does not exist!\n");
				exit(1);
			}
			is_good_lumi_isLoaded = true;
		}
		return is_good_lumi_;
	}
	int &njets()
	{
		if (not njets_isLoaded) {
			if (njets_branch != 0) {
				njets_branch->GetEntry(index);
			} else { 
				printf("branch njets_branch does not exist!\n");
				exit(1);
			}
			njets_isLoaded = true;
		}
		return njets_;
	}
	int &njets20()
	{
		if (not njets20_isLoaded) {
			if (njets20_branch != 0) {
				njets20_branch->GetEntry(index);
			} else { 
				printf("branch njets20_branch does not exist!\n");
				exit(1);
			}
			njets20_isLoaded = true;
		}
		return njets20_;
	}
	int &njets30()
	{
		if (not njets30_isLoaded) {
			if (njets30_branch != 0) {
				njets30_branch->GetEntry(index);
			} else { 
				printf("branch njets30_branch does not exist!\n");
				exit(1);
			}
			njets30_isLoaded = true;
		}
		return njets30_;
	}
	int &nbtags()
	{
		if (not nbtags_isLoaded) {
			if (nbtags_branch != 0) {
				nbtags_branch->GetEntry(index);
			} else { 
				printf("branch nbtags_branch does not exist!\n");
				exit(1);
			}
			nbtags_isLoaded = true;
		}
		return nbtags_;
	}
	int &nbtags20()
	{
		if (not nbtags20_isLoaded) {
			if (nbtags20_branch != 0) {
				nbtags20_branch->GetEntry(index);
			} else { 
				printf("branch nbtags20_branch does not exist!\n");
				exit(1);
			}
			nbtags20_isLoaded = true;
		}
		return nbtags20_;
	}
	int &nbtags30()
	{
		if (not nbtags30_isLoaded) {
			if (nbtags30_branch != 0) {
				nbtags30_branch->GetEntry(index);
			} else { 
				printf("branch nbtags30_branch does not exist!\n");
				exit(1);
			}
			nbtags30_isLoaded = true;
		}
		return nbtags30_;
	}
	float &vtxw()
	{
		if (not vtxw_isLoaded) {
			if (vtxw_branch != 0) {
				vtxw_branch->GetEntry(index);
			} else { 
				printf("branch vtxw_branch does not exist!\n");
				exit(1);
			}
			vtxw_isLoaded = true;
		}
		return vtxw_;
	}
	float &ht()
	{
		if (not ht_isLoaded) {
			if (ht_branch != 0) {
				ht_branch->GetEntry(index);
			} else { 
				printf("branch ht_branch does not exist!\n");
				exit(1);
			}
			ht_isLoaded = true;
		}
		return ht_;
	}
	float &ht20()
	{
		if (not ht20_isLoaded) {
			if (ht20_branch != 0) {
				ht20_branch->GetEntry(index);
			} else { 
				printf("branch ht20_branch does not exist!\n");
				exit(1);
			}
			ht20_isLoaded = true;
		}
		return ht20_;
	}
	float &ht30()
	{
		if (not ht30_isLoaded) {
			if (ht30_branch != 0) {
				ht30_branch->GetEntry(index);
			} else { 
				printf("branch ht30_branch does not exist!\n");
				exit(1);
			}
			ht30_isLoaded = true;
		}
		return ht30_;
	}
	float &rho()
	{
		if (not rho_isLoaded) {
			if (rho_branch != 0) {
				rho_branch->GetEntry(index);
			} else { 
				printf("branch rho_branch does not exist!\n");
				exit(1);
			}
			rho_isLoaded = true;
		}
		return rho_;
	}
	float &rho_iso()
	{
		if (not rho_iso_isLoaded) {
			if (rho_iso_branch != 0) {
				rho_iso_branch->GetEntry(index);
			} else { 
				printf("branch rho_iso_branch does not exist!\n");
				exit(1);
			}
			rho_iso_isLoaded = true;
		}
		return rho_iso_;
	}
	bool &	trig_mm()
	{
		if (not trig_mm_isLoaded) {
			if (trig_mm_branch != 0) {
				trig_mm_branch->GetEntry(index);
			} else { 
				printf("branch trig_mm_branch does not exist!\n");
				exit(1);
			}
			trig_mm_isLoaded = true;
		}
		return trig_mm_;
	}
	bool &	trig_em()
	{
		if (not trig_em_isLoaded) {
			if (trig_em_branch != 0) {
				trig_em_branch->GetEntry(index);
			} else { 
				printf("branch trig_em_branch does not exist!\n");
				exit(1);
			}
			trig_em_isLoaded = true;
		}
		return trig_em_;
	}
	bool &	trig_ee()
	{
		if (not trig_ee_isLoaded) {
			if (trig_ee_branch != 0) {
				trig_ee_branch->GetEntry(index);
			} else { 
				printf("branch trig_ee_branch does not exist!\n");
				exit(1);
			}
			trig_ee_isLoaded = true;
		}
		return trig_ee_;
	}
	float &sf_dileptrig()
	{
		if (not sf_dileptrig_isLoaded) {
			if (sf_dileptrig_branch != 0) {
				sf_dileptrig_branch->GetEntry(index);
			} else { 
				printf("branch sf_dileptrig_branch does not exist!\n");
				exit(1);
			}
			sf_dileptrig_isLoaded = true;
		}
		return sf_dileptrig_;
	}
	float &sf_lepeff()
	{
		if (not sf_lepeff_isLoaded) {
			if (sf_lepeff_branch != 0) {
				sf_lepeff_branch->GetEntry(index);
			} else { 
				printf("branch sf_lepeff_branch does not exist!\n");
				exit(1);
			}
			sf_lepeff_isLoaded = true;
		}
		return sf_lepeff_;
	}
	float &sparm0()
	{
		if (not sparm0_isLoaded) {
			if (sparm0_branch != 0) {
				sparm0_branch->GetEntry(index);
			} else { 
				printf("branch sparm0_branch does not exist!\n");
				exit(1);
			}
			sparm0_isLoaded = true;
		}
		return sparm0_;
	}
	float &sparm1()
	{
		if (not sparm1_isLoaded) {
			if (sparm1_branch != 0) {
				sparm1_branch->GetEntry(index);
			} else { 
				printf("branch sparm1_branch does not exist!\n");
				exit(1);
			}
			sparm1_isLoaded = true;
		}
		return sparm1_;
	}
	float &sparm2()
	{
		if (not sparm2_isLoaded) {
			if (sparm2_branch != 0) {
				sparm2_branch->GetEntry(index);
			} else { 
				printf("branch sparm2_branch does not exist!\n");
				exit(1);
			}
			sparm2_isLoaded = true;
		}
		return sparm2_;
	}
	float &sparm3()
	{
		if (not sparm3_isLoaded) {
			if (sparm3_branch != 0) {
				sparm3_branch->GetEntry(index);
			} else { 
				printf("branch sparm3_branch does not exist!\n");
				exit(1);
			}
			sparm3_isLoaded = true;
		}
		return sparm3_;
	}
	bool &	is_pp()
	{
		if (not is_pp_isLoaded) {
			if (is_pp_branch != 0) {
				is_pp_branch->GetEntry(index);
			} else { 
				printf("branch is_pp_branch does not exist!\n");
				exit(1);
			}
			is_pp_isLoaded = true;
		}
		return is_pp_;
	}
	bool &	is_mm()
	{
		if (not is_mm_isLoaded) {
			if (is_mm_branch != 0) {
				is_mm_branch->GetEntry(index);
			} else { 
				printf("branch is_mm_branch does not exist!\n");
				exit(1);
			}
			is_mm_isLoaded = true;
		}
		return is_mm_;
	}
	bool &	is_sf()
	{
		if (not is_sf_isLoaded) {
			if (is_sf_branch != 0) {
				is_sf_branch->GetEntry(index);
			} else { 
				printf("branch is_sf_branch does not exist!\n");
				exit(1);
			}
			is_sf_isLoaded = true;
		}
		return is_sf_;
	}
	bool &	is_df()
	{
		if (not is_df_isLoaded) {
			if (is_df_branch != 0) {
				is_df_branch->GetEntry(index);
			} else { 
				printf("branch is_df_branch does not exist!\n");
				exit(1);
			}
			is_df_isLoaded = true;
		}
		return is_df_;
	}
	bool &	no_extraz()
	{
		if (not no_extraz_isLoaded) {
			if (no_extraz_branch != 0) {
				no_extraz_branch->GetEntry(index);
			} else { 
				printf("branch no_extraz_branch does not exist!\n");
				exit(1);
			}
			no_extraz_isLoaded = true;
		}
		return no_extraz_;
	}
	bool &	is_gen_pp()
	{
		if (not is_gen_pp_isLoaded) {
			if (is_gen_pp_branch != 0) {
				is_gen_pp_branch->GetEntry(index);
			} else { 
				printf("branch is_gen_pp_branch does not exist!\n");
				exit(1);
			}
			is_gen_pp_isLoaded = true;
		}
		return is_gen_pp_;
	}
	bool &	is_gen_mm()
	{
		if (not is_gen_mm_isLoaded) {
			if (is_gen_mm_branch != 0) {
				is_gen_mm_branch->GetEntry(index);
			} else { 
				printf("branch is_gen_mm_branch does not exist!\n");
				exit(1);
			}
			is_gen_mm_isLoaded = true;
		}
		return is_gen_mm_;
	}
	int &gen_nbtags()
	{
		if (not gen_nbtags_isLoaded) {
			if (gen_nbtags_branch != 0) {
				gen_nbtags_branch->GetEntry(index);
			} else { 
				printf("branch gen_nbtags_branch does not exist!\n");
				exit(1);
			}
			gen_nbtags_isLoaded = true;
		}
		return gen_nbtags_;
	}
	int &gen_njets()
	{
		if (not gen_njets_isLoaded) {
			if (gen_njets_branch != 0) {
				gen_njets_branch->GetEntry(index);
			} else { 
				printf("branch gen_njets_branch does not exist!\n");
				exit(1);
			}
			gen_njets_isLoaded = true;
		}
		return gen_njets_;
	}
	float &gen_ht()
	{
		if (not gen_ht_isLoaded) {
			if (gen_ht_branch != 0) {
				gen_ht_branch->GetEntry(index);
			} else { 
				printf("branch gen_ht_branch does not exist!\n");
				exit(1);
			}
			gen_ht_isLoaded = true;
		}
		return gen_ht_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearbjet_p4()
	{
		if (not lep1_nearbjet_p4_isLoaded) {
			if (lep1_nearbjet_p4_branch != 0) {
				lep1_nearbjet_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep1_nearbjet_p4_branch does not exist!\n");
				exit(1);
			}
			lep1_nearbjet_p4_isLoaded = true;
		}
		return *lep1_nearbjet_p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearjet_p4()
	{
		if (not lep1_nearjet_p4_isLoaded) {
			if (lep1_nearjet_p4_branch != 0) {
				lep1_nearjet_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep1_nearjet_p4_branch does not exist!\n");
				exit(1);
			}
			lep1_nearjet_p4_isLoaded = true;
		}
		return *lep1_nearjet_p4_;
	}
	float &lep1_wfr()
	{
		if (not lep1_wfr_isLoaded) {
			if (lep1_wfr_branch != 0) {
				lep1_wfr_branch->GetEntry(index);
			} else { 
				printf("branch lep1_wfr_branch does not exist!\n");
				exit(1);
			}
			lep1_wfr_isLoaded = true;
		}
		return lep1_wfr_;
	}
	float &lep1_wflip()
	{
		if (not lep1_wflip_isLoaded) {
			if (lep1_wflip_branch != 0) {
				lep1_wflip_branch->GetEntry(index);
			} else { 
				printf("branch lep1_wflip_branch does not exist!\n");
				exit(1);
			}
			lep1_wflip_isLoaded = true;
		}
		return lep1_wflip_;
	}
	float &lep1_nearbjet_dr()
	{
		if (not lep1_nearbjet_dr_isLoaded) {
			if (lep1_nearbjet_dr_branch != 0) {
				lep1_nearbjet_dr_branch->GetEntry(index);
			} else { 
				printf("branch lep1_nearbjet_dr_branch does not exist!\n");
				exit(1);
			}
			lep1_nearbjet_dr_isLoaded = true;
		}
		return lep1_nearbjet_dr_;
	}
	float &lep1_nearjet_dr()
	{
		if (not lep1_nearjet_dr_isLoaded) {
			if (lep1_nearjet_dr_branch != 0) {
				lep1_nearjet_dr_branch->GetEntry(index);
			} else { 
				printf("branch lep1_nearjet_dr_branch does not exist!\n");
				exit(1);
			}
			lep1_nearjet_dr_isLoaded = true;
		}
		return lep1_nearjet_dr_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearbjet_p4()
	{
		if (not lep2_nearbjet_p4_isLoaded) {
			if (lep2_nearbjet_p4_branch != 0) {
				lep2_nearbjet_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep2_nearbjet_p4_branch does not exist!\n");
				exit(1);
			}
			lep2_nearbjet_p4_isLoaded = true;
		}
		return *lep2_nearbjet_p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearjet_p4()
	{
		if (not lep2_nearjet_p4_isLoaded) {
			if (lep2_nearjet_p4_branch != 0) {
				lep2_nearjet_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep2_nearjet_p4_branch does not exist!\n");
				exit(1);
			}
			lep2_nearjet_p4_isLoaded = true;
		}
		return *lep2_nearjet_p4_;
	}
	float &lep2_wfr()
	{
		if (not lep2_wfr_isLoaded) {
			if (lep2_wfr_branch != 0) {
				lep2_wfr_branch->GetEntry(index);
			} else { 
				printf("branch lep2_wfr_branch does not exist!\n");
				exit(1);
			}
			lep2_wfr_isLoaded = true;
		}
		return lep2_wfr_;
	}
	float &lep2_wflip()
	{
		if (not lep2_wflip_isLoaded) {
			if (lep2_wflip_branch != 0) {
				lep2_wflip_branch->GetEntry(index);
			} else { 
				printf("branch lep2_wflip_branch does not exist!\n");
				exit(1);
			}
			lep2_wflip_isLoaded = true;
		}
		return lep2_wflip_;
	}
	float &lep2_nearbjet_dr()
	{
		if (not lep2_nearbjet_dr_isLoaded) {
			if (lep2_nearbjet_dr_branch != 0) {
				lep2_nearbjet_dr_branch->GetEntry(index);
			} else { 
				printf("branch lep2_nearbjet_dr_branch does not exist!\n");
				exit(1);
			}
			lep2_nearbjet_dr_isLoaded = true;
		}
		return lep2_nearbjet_dr_;
	}
	float &lep2_nearjet_dr()
	{
		if (not lep2_nearjet_dr_isLoaded) {
			if (lep2_nearjet_dr_branch != 0) {
				lep2_nearjet_dr_branch->GetEntry(index);
			} else { 
				printf("branch lep2_nearjet_dr_branch does not exist!\n");
				exit(1);
			}
			lep2_nearjet_dr_isLoaded = true;
		}
		return lep2_nearjet_dr_;
	}
	float &sf_nbtag()
	{
		if (not sf_nbtag_isLoaded) {
			if (sf_nbtag_branch != 0) {
				sf_nbtag_branch->GetEntry(index);
			} else { 
				printf("branch sf_nbtag_branch does not exist!\n");
				exit(1);
			}
			sf_nbtag_isLoaded = true;
		}
		return sf_nbtag_;
	}
	float &sf_nbtag3()
	{
		if (not sf_nbtag3_isLoaded) {
			if (sf_nbtag3_branch != 0) {
				sf_nbtag3_branch->GetEntry(index);
			} else { 
				printf("branch sf_nbtag3_branch does not exist!\n");
				exit(1);
			}
			sf_nbtag3_isLoaded = true;
		}
		return sf_nbtag3_;
	}
	float &sf_unc_nbtag()
	{
		if (not sf_unc_nbtag_isLoaded) {
			if (sf_unc_nbtag_branch != 0) {
				sf_unc_nbtag_branch->GetEntry(index);
			} else { 
				printf("branch sf_unc_nbtag_branch does not exist!\n");
				exit(1);
			}
			sf_unc_nbtag_isLoaded = true;
		}
		return sf_unc_nbtag_;
	}
	float &sf_unc_nbtag3()
	{
		if (not sf_unc_nbtag3_isLoaded) {
			if (sf_unc_nbtag3_branch != 0) {
				sf_unc_nbtag3_branch->GetEntry(index);
			} else { 
				printf("branch sf_unc_nbtag3_branch does not exist!\n");
				exit(1);
			}
			sf_unc_nbtag3_isLoaded = true;
		}
		return sf_unc_nbtag3_;
	}
	float &jets_dr12()
	{
		if (not jets_dr12_isLoaded) {
			if (jets_dr12_branch != 0) {
				jets_dr12_branch->GetEntry(index);
			} else { 
				printf("branch jets_dr12_branch does not exist!\n");
				exit(1);
			}
			jets_dr12_isLoaded = true;
		}
		return jets_dr12_;
	}
	float &bjets_dr12()
	{
		if (not bjets_dr12_isLoaded) {
			if (bjets_dr12_branch != 0) {
				bjets_dr12_branch->GetEntry(index);
			} else { 
				printf("branch bjets_dr12_branch does not exist!\n");
				exit(1);
			}
			bjets_dr12_isLoaded = true;
		}
		return bjets_dr12_;
	}
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vgenb_p4()
	{
		if (not vgenb_p4_isLoaded) {
			if (vgenb_p4_branch != 0) {
				vgenb_p4_branch->GetEntry(index);
			} else { 
				printf("branch vgenb_p4_branch does not exist!\n");
				exit(1);
			}
			vgenb_p4_isLoaded = true;
		}
		return *vgenb_p4_;
	}
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_p4()
	{
		if (not vjets_p4_isLoaded) {
			if (vjets_p4_branch != 0) {
				vjets_p4_branch->GetEntry(index);
			} else { 
				printf("branch vjets_p4_branch does not exist!\n");
				exit(1);
			}
			vjets_p4_isLoaded = true;
		}
		return *vjets_p4_;
	}
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vgenjets_p4()
	{
		if (not vgenjets_p4_isLoaded) {
			if (vgenjets_p4_branch != 0) {
				vgenjets_p4_branch->GetEntry(index);
			} else { 
				printf("branch vgenjets_p4_branch does not exist!\n");
				exit(1);
			}
			vgenjets_p4_isLoaded = true;
		}
		return *vgenjets_p4_;
	}
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_nearjet_p4()
	{
		if (not vjets_nearjet_p4_isLoaded) {
			if (vjets_nearjet_p4_branch != 0) {
				vjets_nearjet_p4_branch->GetEntry(index);
			} else { 
				printf("branch vjets_nearjet_p4_branch does not exist!\n");
				exit(1);
			}
			vjets_nearjet_p4_isLoaded = true;
		}
		return *vjets_nearjet_p4_;
	}
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vbjets_p4()
	{
		if (not vbjets_p4_isLoaded) {
			if (vbjets_p4_branch != 0) {
				vbjets_p4_branch->GetEntry(index);
			} else { 
				printf("branch vbjets_p4_branch does not exist!\n");
				exit(1);
			}
			vbjets_p4_isLoaded = true;
		}
		return *vbjets_p4_;
	}
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vbjets_nearjet_p4()
	{
		if (not vbjets_nearjet_p4_isLoaded) {
			if (vbjets_nearjet_p4_branch != 0) {
				vbjets_nearjet_p4_branch->GetEntry(index);
			} else { 
				printf("branch vbjets_nearjet_p4_branch does not exist!\n");
				exit(1);
			}
			vbjets_nearjet_p4_isLoaded = true;
		}
		return *vbjets_nearjet_p4_;
	}

  static void progress( int nEventsTotal, int nEventsChain ){
    int period = 1000;
    if(nEventsTotal%1000 == 0) {
      // xterm magic from L. Vacavant and A. Cerri
      if (isatty(1)) {
        if( ( nEventsChain - nEventsTotal ) > period ){
          float frac = (float)nEventsTotal/(nEventsChain*0.01);
          printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
               "\033[0m\033[32m <---\033[0m\015", frac);
          fflush(stdout);
        }
        else {
          printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
                 "\033[0m\033[32m <---\033[0m\015", 100.);
          cout << endl;
        }
      }
    }
  }
  
};

#ifndef __CINT__
extern SSB samesignbtag;
#endif

namespace ssb {
	unsigned int &run();
	unsigned int &ls();
	unsigned int &evt();
	bool &is_real_data();
	int &sample();
	int &nvtxs();
	int &vtx_idx();
	float &pfmet();
	float &pfmet_phi();
	float &corpfmet();
	float &corpfmet_phi();
	float &scale1fb();
	float &xsec();
	float &kfactor();
	float &gen_met();
	float &gen_met_phi();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_p4();
	bool &lep1_passes_id();
	bool &lep1_passes_iso();
	bool &lep1_is_num();
	bool &lep1_is_fo();
	int &lep1_charge();
	int &lep1_pdgid();
	int &lep1_type();
	float &lep1_d0();
	float &lep1_dz();
	float &lep1_mt();
	float &lep1_corpfiso();
	float &lep1_pfiso();
	float &lep1_chiso();
	float &lep1_emiso();
	float &lep1_nhiso();
	float &lep1_corpfiso04();
	float &lep1_pfiso04();
	float &lep1_chiso04();
	float &lep1_emiso04();
	float &lep1_nhiso04();
	float &lep1_cordetiso();
	float &lep1_detiso();
	float &lep1_trkiso();
	float &lep1_ecaliso();
	float &lep1_hcaliso();
	float &lep1_cordetiso04();
	float &lep1_detiso04();
	float &lep1_trkiso04();
	float &lep1_ecaliso04();
	float &lep1_hcaliso04();
	float &lep1_effarea();
	float &lep1_effarea04();
	float &lep1_dbeta();
	float &lep1_dbeta04();
	float &lep1_sf_lepeff();
	float &lep1_sf_trig();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mcp4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mc3p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mc_momp4();
	int &lep1_mcid();
	int &lep1_mc3id();
	int &lep1_momid();
	int &lep1_mc3_momid();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_gsf_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_ctf_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_sc_p4();
	bool &lep1_q3agree();
	bool &lep1_is_conv();
	int &lep1_qsc();
	int &lep1_qctf();
	int &lep1_qgsf();
	int &lep1_nmhits();
	int &lep1_eleid_veto();
	int &lep1_eleid_loose();
	int &lep1_eleid_medium();
	int &lep1_eleid_tight();
	float &lep1_dphiin();
	float &lep1_detain();
	float &lep1_sieie();
	float &lep1_hoe();
	float &lep1_ooemoop();
	float &lep1_conv_dist();
	float &lep1_conv_dcot();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_gfit_p4();
	bool &lep1_is_global();
	bool &lep1_is_tracker();
	bool &lep1_is_stamu();
	bool &lep1_is_pfmu();
	bool &lep1_is_loosemu();
	bool &lep1_is_tightmu();
	int &lep1_npixelhits();
	int &lep1_nsihits();
	int &lep1_nsilayers();
	int &lep1_nstahits();
	int &lep1_nstations();
	float &lep1_chi2();
	float &lep1_ndof();
	float &lep1_pterr();
	float &lep1_ecal_vetodep();
	float &lep1_hcal_vetodep();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_p4();
	bool &lep2_passes_id();
	bool &lep2_passes_iso();
	bool &lep2_is_num();
	bool &lep2_is_fo();
	int &lep2_charge();
	int &lep2_pdgid();
	int &lep2_type();
	float &lep2_d0();
	float &lep2_dz();
	float &lep2_mt();
	float &lep2_corpfiso();
	float &lep2_pfiso();
	float &lep2_chiso();
	float &lep2_emiso();
	float &lep2_nhiso();
	float &lep2_corpfiso04();
	float &lep2_pfiso04();
	float &lep2_chiso04();
	float &lep2_emiso04();
	float &lep2_nhiso04();
	float &lep2_cordetiso();
	float &lep2_detiso();
	float &lep2_trkiso();
	float &lep2_ecaliso();
	float &lep2_hcaliso();
	float &lep2_cordetiso04();
	float &lep2_detiso04();
	float &lep2_trkiso04();
	float &lep2_ecaliso04();
	float &lep2_hcaliso04();
	float &lep2_effarea();
	float &lep2_effarea04();
	float &lep2_dbeta();
	float &lep2_dbeta04();
	float &lep2_sf_lepeff();
	float &lep2_sf_trig();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mcp4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mc3p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mc_momp4();
	int &lep2_mcid();
	int &lep2_mc3id();
	int &lep2_momid();
	int &lep2_mc3_momid();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_gsf_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_ctf_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_sc_p4();
	bool &lep2_q3agree();
	bool &lep2_is_conv();
	int &lep2_qsc();
	int &lep2_qctf();
	int &lep2_qgsf();
	int &lep2_nmhits();
	int &lep2_eleid_veto();
	int &lep2_eleid_loose();
	int &lep2_eleid_medium();
	int &lep2_eleid_tight();
	float &lep2_dphiin();
	float &lep2_detain();
	float &lep2_sieie();
	float &lep2_hoe();
	float &lep2_ooemoop();
	float &lep2_conv_dist();
	float &lep2_conv_dcot();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_gfit_p4();
	bool &lep2_is_global();
	bool &lep2_is_tracker();
	bool &lep2_is_stamu();
	bool &lep2_is_pfmu();
	bool &lep2_is_loosemu();
	bool &lep2_is_tightmu();
	int &lep2_npixelhits();
	int &lep2_nsihits();
	int &lep2_nsilayers();
	int &lep2_nstahits();
	int &lep2_nstations();
	float &lep2_chi2();
	float &lep2_ndof();
	float &lep2_pterr();
	float &lep2_ecal_vetodep();
	float &lep2_hcal_vetodep();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &dilep_p4();
	bool &is_os();
	bool &is_ss();
	int &dilep_type();
	int &dilep_gen_type();
	float &dilep_mass();
	float &dilep_dphi();
	float &dilep_deta();
	float &dilep_dr();
	int &fiduciality();
	unsigned int &selection();
	bool &is_good_lumi();
	int &njets();
	int &njets20();
	int &njets30();
	int &nbtags();
	int &nbtags20();
	int &nbtags30();
	float &vtxw();
	float &ht();
	float &ht20();
	float &ht30();
	float &rho();
	float &rho_iso();
	bool &trig_mm();
	bool &trig_em();
	bool &trig_ee();
	float &sf_dileptrig();
	float &sf_lepeff();
	float &sparm0();
	float &sparm1();
	float &sparm2();
	float &sparm3();
	bool &is_pp();
	bool &is_mm();
	bool &is_sf();
	bool &is_df();
	bool &no_extraz();
	bool &is_gen_pp();
	bool &is_gen_mm();
	int &gen_nbtags();
	int &gen_njets();
	float &gen_ht();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearbjet_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearjet_p4();
	float &lep1_wfr();
	float &lep1_wflip();
	float &lep1_nearbjet_dr();
	float &lep1_nearjet_dr();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearbjet_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearjet_p4();
	float &lep2_wfr();
	float &lep2_wflip();
	float &lep2_nearbjet_dr();
	float &lep2_nearjet_dr();
	float &sf_nbtag();
	float &sf_nbtag3();
	float &sf_unc_nbtag();
	float &sf_unc_nbtag3();
	float &jets_dr12();
	float &bjets_dr12();
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vgenb_p4();
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_p4();
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vgenjets_p4();
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_nearjet_p4();
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vbjets_p4();
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vbjets_nearjet_p4();
}
#endif
