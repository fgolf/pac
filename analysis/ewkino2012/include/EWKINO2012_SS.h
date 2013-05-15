// -*- C++ -*-
#ifndef EWKINO2012_SS_H
#define EWKINO2012_SS_H
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
class EWKINO2012_SS {
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
	float	uncorpfmet_;
	TBranch *uncorpfmet_branch;
	bool uncorpfmet_isLoaded;
	float	uncorpfmet_phi_;
	TBranch *uncorpfmet_phi_branch;
	bool uncorpfmet_phi_isLoaded;
	float	pu_nvtxs_;
	TBranch *pu_nvtxs_branch;
	bool pu_nvtxs_isLoaded;
	float	pu_ntrueint_;
	TBranch *pu_ntrueint_branch;
	bool pu_ntrueint_isLoaded;
	float	scale1fb_;
	TBranch *scale1fb_branch;
	bool scale1fb_isLoaded;
	float	xsec_;
	TBranch *xsec_branch;
	bool xsec_isLoaded;
	unsigned int	nevts_;
	TBranch *nevts_branch;
	bool nevts_isLoaded;
	float	kfactor_;
	TBranch *kfactor_branch;
	bool kfactor_isLoaded;
	float	gen_met_;
	TBranch *gen_met_branch;
	bool gen_met_isLoaded;
	float	gen_met_phi_;
	TBranch *gen_met_phi_branch;
	bool gen_met_phi_isLoaded;
	TString *dataset_;
	TBranch *dataset_branch;
	bool dataset_isLoaded;
	TString *filename_;
	TBranch *filename_branch;
	bool filename_isLoaded;
	bool	filt_csc_;
	TBranch *filt_csc_branch;
	bool filt_csc_isLoaded;
	bool	filt_hbhe_;
	TBranch *filt_hbhe_branch;
	bool filt_hbhe_isLoaded;
	bool	filt_hcallaser_;
	TBranch *filt_hcallaser_branch;
	bool filt_hcallaser_isLoaded;
	bool	filt_ecallaser_;
	TBranch *filt_ecallaser_branch;
	bool filt_ecallaser_isLoaded;
	bool	filt_ecaltp_;
	TBranch *filt_ecaltp_branch;
	bool filt_ecaltp_isLoaded;
	bool	filt_trkfail_;
	TBranch *filt_trkfail_branch;
	bool filt_trkfail_isLoaded;
	bool	filt_eebadsc_;
	TBranch *filt_eebadsc_branch;
	bool filt_eebadsc_isLoaded;
	bool	passes_metfilters_;
	TBranch *passes_metfilters_branch;
	bool passes_metfilters_isLoaded;
	bool	lep1_passes_id_;
	TBranch *lep1_passes_id_branch;
	bool lep1_passes_id_isLoaded;
	bool	lep1_passes_iso_;
	TBranch *lep1_passes_iso_branch;
	bool lep1_passes_iso_isLoaded;
	bool	lep1_is_num_;
	TBranch *lep1_is_num_branch;
	bool lep1_is_num_isLoaded;
	bool	lep1_is_den_;
	TBranch *lep1_is_den_branch;
	bool lep1_is_den_isLoaded;
	bool	lep1_is_fo_;
	TBranch *lep1_is_fo_branch;
	bool lep1_is_fo_isLoaded;
	int	lep1_is_fromw_;
	TBranch *lep1_is_fromw_branch;
	bool lep1_is_fromw_isLoaded;
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
	float	lep1_d0err_;
	TBranch *lep1_d0err_branch;
	bool lep1_d0err_isLoaded;
	float	lep1_dz_;
	TBranch *lep1_dz_branch;
	bool lep1_dz_isLoaded;
	float	lep1_ip3d_;
	TBranch *lep1_ip3d_branch;
	bool lep1_ip3d_isLoaded;
	float	lep1_ip3derr_;
	TBranch *lep1_ip3derr_branch;
	bool lep1_ip3derr_isLoaded;
	float	lep1_dzerr_;
	TBranch *lep1_dzerr_branch;
	bool lep1_dzerr_isLoaded;
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
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_p4_;
	TBranch *lep1_p4_branch;
	bool lep1_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_mcp4_;
	TBranch *lep1_mcp4_branch;
	bool lep1_mcp4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_mc3p4_;
	TBranch *lep1_mc3p4_branch;
	bool lep1_mc3p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_mc_momp4_;
	TBranch *lep1_mc_momp4_branch;
	bool lep1_mc_momp4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_gsf_p4_;
	TBranch *lep1_gsf_p4_branch;
	bool lep1_gsf_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_ctf_p4_;
	TBranch *lep1_ctf_p4_branch;
	bool lep1_ctf_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_sc_p4_;
	TBranch *lep1_sc_p4_branch;
	bool lep1_sc_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_gfit_p4_;
	TBranch *lep1_gfit_p4_branch;
	bool lep1_gfit_p4_isLoaded;
	bool	lep2_passes_id_;
	TBranch *lep2_passes_id_branch;
	bool lep2_passes_id_isLoaded;
	bool	lep2_passes_iso_;
	TBranch *lep2_passes_iso_branch;
	bool lep2_passes_iso_isLoaded;
	bool	lep2_is_num_;
	TBranch *lep2_is_num_branch;
	bool lep2_is_num_isLoaded;
	bool	lep2_is_den_;
	TBranch *lep2_is_den_branch;
	bool lep2_is_den_isLoaded;
	bool	lep2_is_fo_;
	TBranch *lep2_is_fo_branch;
	bool lep2_is_fo_isLoaded;
	int	lep2_is_fromw_;
	TBranch *lep2_is_fromw_branch;
	bool lep2_is_fromw_isLoaded;
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
	float	lep2_d0err_;
	TBranch *lep2_d0err_branch;
	bool lep2_d0err_isLoaded;
	float	lep2_dz_;
	TBranch *lep2_dz_branch;
	bool lep2_dz_isLoaded;
	float	lep2_ip3d_;
	TBranch *lep2_ip3d_branch;
	bool lep2_ip3d_isLoaded;
	float	lep2_ip3derr_;
	TBranch *lep2_ip3derr_branch;
	bool lep2_ip3derr_isLoaded;
	float	lep2_dzerr_;
	TBranch *lep2_dzerr_branch;
	bool lep2_dzerr_isLoaded;
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
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_p4_;
	TBranch *lep2_p4_branch;
	bool lep2_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_mcp4_;
	TBranch *lep2_mcp4_branch;
	bool lep2_mcp4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_mc3p4_;
	TBranch *lep2_mc3p4_branch;
	bool lep2_mc3p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_mc_momp4_;
	TBranch *lep2_mc_momp4_branch;
	bool lep2_mc_momp4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_gsf_p4_;
	TBranch *lep2_gsf_p4_branch;
	bool lep2_gsf_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_ctf_p4_;
	TBranch *lep2_ctf_p4_branch;
	bool lep2_ctf_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_sc_p4_;
	TBranch *lep2_sc_p4_branch;
	bool lep2_sc_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_gfit_p4_;
	TBranch *lep2_gfit_p4_branch;
	bool lep2_gfit_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *dilep_p4_;
	TBranch *dilep_p4_branch;
	bool dilep_p4_isLoaded;
	bool	os_;
	TBranch *os_branch;
	bool os_isLoaded;
	bool	ss_;
	TBranch *ss_branch;
	bool ss_isLoaded;
	bool	mm_;
	TBranch *mm_branch;
	bool mm_isLoaded;
	bool	ee_;
	TBranch *ee_branch;
	bool ee_isLoaded;
	bool	em_;
	TBranch *em_branch;
	bool em_isLoaded;
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
	bool	lep3_passes_id_;
	TBranch *lep3_passes_id_branch;
	bool lep3_passes_id_isLoaded;
	bool	lep3_passes_iso_;
	TBranch *lep3_passes_iso_branch;
	bool lep3_passes_iso_isLoaded;
	bool	lep3_is_num_;
	TBranch *lep3_is_num_branch;
	bool lep3_is_num_isLoaded;
	bool	lep3_is_den_;
	TBranch *lep3_is_den_branch;
	bool lep3_is_den_isLoaded;
	bool	lep3_is_fo_;
	TBranch *lep3_is_fo_branch;
	bool lep3_is_fo_isLoaded;
	int	lep3_is_fromw_;
	TBranch *lep3_is_fromw_branch;
	bool lep3_is_fromw_isLoaded;
	int	lep3_charge_;
	TBranch *lep3_charge_branch;
	bool lep3_charge_isLoaded;
	int	lep3_pdgid_;
	TBranch *lep3_pdgid_branch;
	bool lep3_pdgid_isLoaded;
	int	lep3_type_;
	TBranch *lep3_type_branch;
	bool lep3_type_isLoaded;
	float	lep3_d0_;
	TBranch *lep3_d0_branch;
	bool lep3_d0_isLoaded;
	float	lep3_d0err_;
	TBranch *lep3_d0err_branch;
	bool lep3_d0err_isLoaded;
	float	lep3_dz_;
	TBranch *lep3_dz_branch;
	bool lep3_dz_isLoaded;
	float	lep3_ip3d_;
	TBranch *lep3_ip3d_branch;
	bool lep3_ip3d_isLoaded;
	float	lep3_ip3derr_;
	TBranch *lep3_ip3derr_branch;
	bool lep3_ip3derr_isLoaded;
	float	lep3_dzerr_;
	TBranch *lep3_dzerr_branch;
	bool lep3_dzerr_isLoaded;
	float	lep3_mt_;
	TBranch *lep3_mt_branch;
	bool lep3_mt_isLoaded;
	float	lep3_corpfiso_;
	TBranch *lep3_corpfiso_branch;
	bool lep3_corpfiso_isLoaded;
	float	lep3_pfiso_;
	TBranch *lep3_pfiso_branch;
	bool lep3_pfiso_isLoaded;
	float	lep3_chiso_;
	TBranch *lep3_chiso_branch;
	bool lep3_chiso_isLoaded;
	float	lep3_emiso_;
	TBranch *lep3_emiso_branch;
	bool lep3_emiso_isLoaded;
	float	lep3_nhiso_;
	TBranch *lep3_nhiso_branch;
	bool lep3_nhiso_isLoaded;
	float	lep3_corpfiso04_;
	TBranch *lep3_corpfiso04_branch;
	bool lep3_corpfiso04_isLoaded;
	float	lep3_pfiso04_;
	TBranch *lep3_pfiso04_branch;
	bool lep3_pfiso04_isLoaded;
	float	lep3_chiso04_;
	TBranch *lep3_chiso04_branch;
	bool lep3_chiso04_isLoaded;
	float	lep3_emiso04_;
	TBranch *lep3_emiso04_branch;
	bool lep3_emiso04_isLoaded;
	float	lep3_nhiso04_;
	TBranch *lep3_nhiso04_branch;
	bool lep3_nhiso04_isLoaded;
	float	lep3_cordetiso_;
	TBranch *lep3_cordetiso_branch;
	bool lep3_cordetiso_isLoaded;
	float	lep3_detiso_;
	TBranch *lep3_detiso_branch;
	bool lep3_detiso_isLoaded;
	float	lep3_trkiso_;
	TBranch *lep3_trkiso_branch;
	bool lep3_trkiso_isLoaded;
	float	lep3_ecaliso_;
	TBranch *lep3_ecaliso_branch;
	bool lep3_ecaliso_isLoaded;
	float	lep3_hcaliso_;
	TBranch *lep3_hcaliso_branch;
	bool lep3_hcaliso_isLoaded;
	float	lep3_cordetiso04_;
	TBranch *lep3_cordetiso04_branch;
	bool lep3_cordetiso04_isLoaded;
	float	lep3_detiso04_;
	TBranch *lep3_detiso04_branch;
	bool lep3_detiso04_isLoaded;
	float	lep3_trkiso04_;
	TBranch *lep3_trkiso04_branch;
	bool lep3_trkiso04_isLoaded;
	float	lep3_ecaliso04_;
	TBranch *lep3_ecaliso04_branch;
	bool lep3_ecaliso04_isLoaded;
	float	lep3_hcaliso04_;
	TBranch *lep3_hcaliso04_branch;
	bool lep3_hcaliso04_isLoaded;
	float	lep3_effarea_;
	TBranch *lep3_effarea_branch;
	bool lep3_effarea_isLoaded;
	float	lep3_effarea04_;
	TBranch *lep3_effarea04_branch;
	bool lep3_effarea04_isLoaded;
	float	lep3_dbeta_;
	TBranch *lep3_dbeta_branch;
	bool lep3_dbeta_isLoaded;
	float	lep3_dbeta04_;
	TBranch *lep3_dbeta04_branch;
	bool lep3_dbeta04_isLoaded;
	float	lep3_sf_lepeff_;
	TBranch *lep3_sf_lepeff_branch;
	bool lep3_sf_lepeff_isLoaded;
	float	lep3_sf_trig_;
	TBranch *lep3_sf_trig_branch;
	bool lep3_sf_trig_isLoaded;
	int	lep3_mcid_;
	TBranch *lep3_mcid_branch;
	bool lep3_mcid_isLoaded;
	int	lep3_mc3id_;
	TBranch *lep3_mc3id_branch;
	bool lep3_mc3id_isLoaded;
	int	lep3_momid_;
	TBranch *lep3_momid_branch;
	bool lep3_momid_isLoaded;
	int	lep3_mc3_momid_;
	TBranch *lep3_mc3_momid_branch;
	bool lep3_mc3_momid_isLoaded;
	bool	lep3_q3agree_;
	TBranch *lep3_q3agree_branch;
	bool lep3_q3agree_isLoaded;
	bool	lep3_is_conv_;
	TBranch *lep3_is_conv_branch;
	bool lep3_is_conv_isLoaded;
	int	lep3_qsc_;
	TBranch *lep3_qsc_branch;
	bool lep3_qsc_isLoaded;
	int	lep3_qctf_;
	TBranch *lep3_qctf_branch;
	bool lep3_qctf_isLoaded;
	int	lep3_qgsf_;
	TBranch *lep3_qgsf_branch;
	bool lep3_qgsf_isLoaded;
	int	lep3_nmhits_;
	TBranch *lep3_nmhits_branch;
	bool lep3_nmhits_isLoaded;
	int	lep3_eleid_veto_;
	TBranch *lep3_eleid_veto_branch;
	bool lep3_eleid_veto_isLoaded;
	int	lep3_eleid_loose_;
	TBranch *lep3_eleid_loose_branch;
	bool lep3_eleid_loose_isLoaded;
	int	lep3_eleid_medium_;
	TBranch *lep3_eleid_medium_branch;
	bool lep3_eleid_medium_isLoaded;
	int	lep3_eleid_tight_;
	TBranch *lep3_eleid_tight_branch;
	bool lep3_eleid_tight_isLoaded;
	float	lep3_dphiin_;
	TBranch *lep3_dphiin_branch;
	bool lep3_dphiin_isLoaded;
	float	lep3_detain_;
	TBranch *lep3_detain_branch;
	bool lep3_detain_isLoaded;
	float	lep3_sieie_;
	TBranch *lep3_sieie_branch;
	bool lep3_sieie_isLoaded;
	float	lep3_hoe_;
	TBranch *lep3_hoe_branch;
	bool lep3_hoe_isLoaded;
	float	lep3_ooemoop_;
	TBranch *lep3_ooemoop_branch;
	bool lep3_ooemoop_isLoaded;
	float	lep3_conv_dist_;
	TBranch *lep3_conv_dist_branch;
	bool lep3_conv_dist_isLoaded;
	float	lep3_conv_dcot_;
	TBranch *lep3_conv_dcot_branch;
	bool lep3_conv_dcot_isLoaded;
	bool	lep3_is_global_;
	TBranch *lep3_is_global_branch;
	bool lep3_is_global_isLoaded;
	bool	lep3_is_tracker_;
	TBranch *lep3_is_tracker_branch;
	bool lep3_is_tracker_isLoaded;
	bool	lep3_is_stamu_;
	TBranch *lep3_is_stamu_branch;
	bool lep3_is_stamu_isLoaded;
	bool	lep3_is_pfmu_;
	TBranch *lep3_is_pfmu_branch;
	bool lep3_is_pfmu_isLoaded;
	bool	lep3_is_loosemu_;
	TBranch *lep3_is_loosemu_branch;
	bool lep3_is_loosemu_isLoaded;
	bool	lep3_is_tightmu_;
	TBranch *lep3_is_tightmu_branch;
	bool lep3_is_tightmu_isLoaded;
	int	lep3_npixelhits_;
	TBranch *lep3_npixelhits_branch;
	bool lep3_npixelhits_isLoaded;
	int	lep3_nsihits_;
	TBranch *lep3_nsihits_branch;
	bool lep3_nsihits_isLoaded;
	int	lep3_nsilayers_;
	TBranch *lep3_nsilayers_branch;
	bool lep3_nsilayers_isLoaded;
	int	lep3_nstahits_;
	TBranch *lep3_nstahits_branch;
	bool lep3_nstahits_isLoaded;
	int	lep3_nstations_;
	TBranch *lep3_nstations_branch;
	bool lep3_nstations_isLoaded;
	float	lep3_chi2_;
	TBranch *lep3_chi2_branch;
	bool lep3_chi2_isLoaded;
	float	lep3_ndof_;
	TBranch *lep3_ndof_branch;
	bool lep3_ndof_isLoaded;
	float	lep3_pterr_;
	TBranch *lep3_pterr_branch;
	bool lep3_pterr_isLoaded;
	float	lep3_ecal_vetodep_;
	TBranch *lep3_ecal_vetodep_branch;
	bool lep3_ecal_vetodep_isLoaded;
	float	lep3_hcal_vetodep_;
	TBranch *lep3_hcal_vetodep_branch;
	bool lep3_hcal_vetodep_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep3_p4_;
	TBranch *lep3_p4_branch;
	bool lep3_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep3_mcp4_;
	TBranch *lep3_mcp4_branch;
	bool lep3_mcp4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep3_mc3p4_;
	TBranch *lep3_mc3p4_branch;
	bool lep3_mc3p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep3_mc_momp4_;
	TBranch *lep3_mc_momp4_branch;
	bool lep3_mc_momp4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep3_gsf_p4_;
	TBranch *lep3_gsf_p4_branch;
	bool lep3_gsf_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep3_ctf_p4_;
	TBranch *lep3_ctf_p4_branch;
	bool lep3_ctf_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep3_sc_p4_;
	TBranch *lep3_sc_p4_branch;
	bool lep3_sc_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep3_gfit_p4_;
	TBranch *lep3_gfit_p4_branch;
	bool lep3_gfit_p4_isLoaded;
	unsigned int	selection_;
	TBranch *selection_branch;
	bool selection_isLoaded;
	bool	is_good_lumi_;
	TBranch *is_good_lumi_branch;
	bool is_good_lumi_isLoaded;
	bool	charge_type_;
	TBranch *charge_type_branch;
	bool charge_type_isLoaded;
	int	njets_;
	TBranch *njets_branch;
	bool njets_isLoaded;
	int	nbtags_;
	TBranch *nbtags_branch;
	bool nbtags_isLoaded;
	int	nbtags_loose_;
	TBranch *nbtags_loose_branch;
	bool nbtags_loose_isLoaded;
	int	ttbar_bkdn_;
	TBranch *ttbar_bkdn_branch;
	bool ttbar_bkdn_isLoaded;
	float	vtxw_;
	TBranch *vtxw_branch;
	bool vtxw_isLoaded;
	float	mt_;
	TBranch *mt_branch;
	bool mt_isLoaded;
	float	mt2_;
	TBranch *mt2_branch;
	bool mt2_isLoaded;
	float	ht_;
	TBranch *ht_branch;
	bool ht_isLoaded;
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
	bool	trig_mm_mu17_mu8_;
	TBranch *trig_mm_mu17_mu8_branch;
	bool trig_mm_mu17_mu8_isLoaded;
	bool	trig_ee_el17_el8_id_iso_;
	TBranch *trig_ee_el17_el8_id_iso_branch;
	bool trig_ee_el17_el8_id_iso_isLoaded;
	bool	trig_em_mu17_el8_id_iso_;
	TBranch *trig_em_mu17_el8_id_iso_branch;
	bool trig_em_mu17_el8_id_iso_isLoaded;
	bool	trig_em_mu8_el17_id_iso_;
	TBranch *trig_em_mu8_el17_id_iso_branch;
	bool trig_em_mu8_el17_id_iso_isLoaded;
	int	njets_dn_;
	TBranch *njets_dn_branch;
	bool njets_dn_isLoaded;
	int	njets_up_;
	TBranch *njets_up_branch;
	bool njets_up_isLoaded;
	int	nbtags_dn_;
	TBranch *nbtags_dn_branch;
	bool nbtags_dn_isLoaded;
	int	nbtags_up_;
	TBranch *nbtags_up_branch;
	bool nbtags_up_isLoaded;
	float	ht_dn_;
	TBranch *ht_dn_branch;
	bool ht_dn_isLoaded;
	float	ht_up_;
	TBranch *ht_up_branch;
	bool ht_up_isLoaded;
	int	nbtags_reweighted_;
	TBranch *nbtags_reweighted_branch;
	bool nbtags_reweighted_isLoaded;
	int	nbtags_reweighted_dn_;
	TBranch *nbtags_reweighted_dn_branch;
	bool nbtags_reweighted_dn_isLoaded;
	int	nbtags_reweighted_up_;
	TBranch *nbtags_reweighted_up_branch;
	bool nbtags_reweighted_up_isLoaded;
	int	nbtags_reweighted_jec_dn_;
	TBranch *nbtags_reweighted_jec_dn_branch;
	bool nbtags_reweighted_jec_dn_isLoaded;
	int	nbtags_reweighted_jec_up_;
	TBranch *nbtags_reweighted_jec_up_branch;
	bool nbtags_reweighted_jec_up_isLoaded;
	float	pfmet_dn_;
	TBranch *pfmet_dn_branch;
	bool pfmet_dn_isLoaded;
	float	pfmet_up_;
	TBranch *pfmet_up_branch;
	bool pfmet_up_isLoaded;
	float	pfmet_phi_dn_;
	TBranch *pfmet_phi_dn_branch;
	bool pfmet_phi_dn_isLoaded;
	float	pfmet_phi_up_;
	TBranch *pfmet_phi_up_branch;
	bool pfmet_phi_up_isLoaded;
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
	TString *sparm0_name_;
	TBranch *sparm0_name_branch;
	bool sparm0_name_isLoaded;
	TString *sparm1_name_;
	TBranch *sparm1_name_branch;
	bool sparm1_name_isLoaded;
	TString *sparm2_name_;
	TBranch *sparm2_name_branch;
	bool sparm2_name_isLoaded;
	TString *sparm3_name_;
	TBranch *sparm3_name_branch;
	bool sparm3_name_isLoaded;
	bool	is_pp_;
	TBranch *is_pp_branch;
	bool is_pp_isLoaded;
	bool	is_mm_;
	TBranch *is_mm_branch;
	bool is_mm_isLoaded;
	bool	is_ss_;
	TBranch *is_ss_branch;
	bool is_ss_isLoaded;
	bool	is_sf_;
	TBranch *is_sf_branch;
	bool is_sf_isLoaded;
	bool	is_df_;
	TBranch *is_df_branch;
	bool is_df_isLoaded;
	bool	is_os_;
	TBranch *is_os_branch;
	bool is_os_isLoaded;
	bool	no_extraz_;
	TBranch *no_extraz_branch;
	bool no_extraz_isLoaded;
	bool	no_extrag_;
	TBranch *no_extrag_branch;
	bool no_extrag_isLoaded;
	bool	clean_;
	TBranch *clean_branch;
	bool clean_isLoaded;
	bool	presel_;
	TBranch *presel_branch;
	bool presel_isLoaded;
	bool	em_mufo_;
	TBranch *em_mufo_branch;
	bool em_mufo_isLoaded;
	bool	em_elfo_;
	TBranch *em_elfo_branch;
	bool em_elfo_isLoaded;
	bool	hyp_good_vtx_;
	TBranch *hyp_good_vtx_branch;
	bool hyp_good_vtx_isLoaded;
	bool	is_gen_pp_;
	TBranch *is_gen_pp_branch;
	bool is_gen_pp_isLoaded;
	bool	is_gen_mm_;
	TBranch *is_gen_mm_branch;
	bool is_gen_mm_isLoaded;
	int	gen_njets_;
	TBranch *gen_njets_branch;
	bool gen_njets_isLoaded;
	int	gen_nleps_;
	TBranch *gen_nleps_branch;
	bool gen_nleps_isLoaded;
	int	gen_nmus_;
	TBranch *gen_nmus_branch;
	bool gen_nmus_isLoaded;
	int	gen_nels_;
	TBranch *gen_nels_branch;
	bool gen_nels_isLoaded;
	int	gen_ntaus_;
	TBranch *gen_ntaus_branch;
	bool gen_ntaus_isLoaded;
	float	gen_ht_;
	TBranch *gen_ht_branch;
	bool gen_ht_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_nearjet_p4_;
	TBranch *lep1_nearjet_p4_branch;
	bool lep1_nearjet_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_nearlep_p4_;
	TBranch *lep1_nearlep_p4_branch;
	bool lep1_nearlep_p4_isLoaded;
	float	lep1_wfr_;
	TBranch *lep1_wfr_branch;
	bool lep1_wfr_isLoaded;
	float	lep1_wflip_;
	TBranch *lep1_wflip_branch;
	bool lep1_wflip_isLoaded;
	float	lep1_nearjet_dr_;
	TBranch *lep1_nearjet_dr_branch;
	bool lep1_nearjet_dr_isLoaded;
	float	lep1_nearlep_dr_;
	TBranch *lep1_nearlep_dr_branch;
	bool lep1_nearlep_dr_isLoaded;
	int	lep1_nearlep_id_;
	TBranch *lep1_nearlep_id_branch;
	bool lep1_nearlep_id_isLoaded;
	bool	lep1_isFromH_;
	TBranch *lep1_isFromH_branch;
	bool lep1_isFromH_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_nearjet_p4_;
	TBranch *lep2_nearjet_p4_branch;
	bool lep2_nearjet_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_nearlep_p4_;
	TBranch *lep2_nearlep_p4_branch;
	bool lep2_nearlep_p4_isLoaded;
	float	lep2_wfr_;
	TBranch *lep2_wfr_branch;
	bool lep2_wfr_isLoaded;
	float	lep2_wflip_;
	TBranch *lep2_wflip_branch;
	bool lep2_wflip_isLoaded;
	float	lep2_nearjet_dr_;
	TBranch *lep2_nearjet_dr_branch;
	bool lep2_nearjet_dr_isLoaded;
	float	lep2_nearlep_dr_;
	TBranch *lep2_nearlep_dr_branch;
	bool lep2_nearlep_dr_isLoaded;
	int	lep2_nearlep_id_;
	TBranch *lep2_nearlep_id_branch;
	bool lep2_nearlep_id_isLoaded;
	bool	lep2_isFromH_;
	TBranch *lep2_isFromH_branch;
	bool lep2_isFromH_isLoaded;
	float	jets_dr12_;
	TBranch *jets_dr12_branch;
	bool jets_dr12_isLoaded;
	float	dijet_mass_;
	TBranch *dijet_mass_branch;
	bool dijet_mass_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *vjets_p4_;
	TBranch *vjets_p4_branch;
	bool vjets_p4_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *vjets_p4_up_;
	TBranch *vjets_p4_up_branch;
	bool vjets_p4_up_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *vjets_p4_dn_;
	TBranch *vjets_p4_dn_branch;
	bool vjets_p4_dn_isLoaded;
	vector<int> *vjets_mcflavor_phys_;
	TBranch *vjets_mcflavor_phys_branch;
	bool vjets_mcflavor_phys_isLoaded;
	vector<int> *vjets_mcflavor_algo_;
	TBranch *vjets_mcflavor_algo_branch;
	bool vjets_mcflavor_algo_isLoaded;
	vector<int> *vjets_mcflavor_phys_up_;
	TBranch *vjets_mcflavor_phys_up_branch;
	bool vjets_mcflavor_phys_up_isLoaded;
	vector<int> *vjets_mcflavor_algo_up_;
	TBranch *vjets_mcflavor_algo_up_branch;
	bool vjets_mcflavor_algo_up_isLoaded;
	vector<int> *vjets_mcflavor_phys_dn_;
	TBranch *vjets_mcflavor_phys_dn_branch;
	bool vjets_mcflavor_phys_dn_isLoaded;
	vector<int> *vjets_mcflavor_algo_dn_;
	TBranch *vjets_mcflavor_algo_dn_branch;
	bool vjets_mcflavor_algo_dn_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *vjets_mc3p4_;
	TBranch *vjets_mc3p4_branch;
	bool vjets_mc3p4_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *vgenjets_p4_;
	TBranch *vgenjets_p4_branch;
	bool vgenjets_p4_isLoaded;
	vector<int> *vjets_mc3id_;
	TBranch *vjets_mc3id_branch;
	bool vjets_mc3id_isLoaded;
	vector<int> *vjets_momid_;
	TBranch *vjets_momid_branch;
	bool vjets_momid_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *vjets_nearjet_p4_;
	TBranch *vjets_nearjet_p4_branch;
	bool vjets_nearjet_p4_isLoaded;
	vector<float> *vjets_nearjet_dr_;
	TBranch *vjets_nearjet_dr_branch;
	bool vjets_nearjet_dr_isLoaded;
	vector<float> *vjets_bdisc_;
	TBranch *vjets_bdisc_branch;
	bool vjets_bdisc_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *gen_lep1_p4_;
	TBranch *gen_lep1_p4_branch;
	bool gen_lep1_p4_isLoaded;
	int	gen_lep1_pdgid_;
	TBranch *gen_lep1_pdgid_branch;
	bool gen_lep1_pdgid_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *gen_lep2_p4_;
	TBranch *gen_lep2_p4_branch;
	bool gen_lep2_p4_isLoaded;
	int	gen_lep2_pdgid_;
	TBranch *gen_lep2_pdgid_branch;
	bool gen_lep2_pdgid_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *gen_dilep_p4_;
	TBranch *gen_dilep_p4_branch;
	bool gen_dilep_p4_isLoaded;
	int	gen_dilep_type_;
	TBranch *gen_dilep_type_branch;
	bool gen_dilep_type_isLoaded;
	float	gen_dilep_mass_;
	TBranch *gen_dilep_mass_branch;
	bool gen_dilep_mass_isLoaded;
	float	gen_dilep_dphi_;
	TBranch *gen_dilep_dphi_branch;
	bool gen_dilep_dphi_isLoaded;
	float	gen_dilep_deta_;
	TBranch *gen_dilep_deta_branch;
	bool gen_dilep_deta_isLoaded;
	float	gen_dilep_dr_;
	TBranch *gen_dilep_dr_branch;
	bool gen_dilep_dr_isLoaded;
	int	pfcandid5_;
	TBranch *pfcandid5_branch;
	bool pfcandid5_isLoaded;
	int	pfcandid10_;
	TBranch *pfcandid10_branch;
	bool pfcandid10_isLoaded;
	int	pfcanddirid10_;
	TBranch *pfcanddirid10_branch;
	bool pfcanddirid10_isLoaded;
	int	pfcandvetoid10_;
	TBranch *pfcandvetoid10_branch;
	bool pfcandvetoid10_isLoaded;
	int	pfcandvetoLid10_;
	TBranch *pfcandvetoLid10_branch;
	bool pfcandvetoLid10_isLoaded;
	int	pfcandidOS10_;
	TBranch *pfcandidOS10_branch;
	bool pfcandidOS10_isLoaded;
	int	pfcandidOS10looseZ_;
	TBranch *pfcandidOS10looseZ_branch;
	bool pfcandidOS10looseZ_isLoaded;
	int	pfcandid5looseZ_;
	TBranch *pfcandid5looseZ_branch;
	bool pfcandid5looseZ_isLoaded;
	float	trkpt5_;
	TBranch *trkpt5_branch;
	bool trkpt5_isLoaded;
	float	mleptrk5_;
	TBranch *mleptrk5_branch;
	bool mleptrk5_isLoaded;
	float	trkreliso5_;
	TBranch *trkreliso5_branch;
	bool trkreliso5_isLoaded;
	float	trkpt10_;
	TBranch *trkpt10_branch;
	bool trkpt10_isLoaded;
	float	mleptrk10_;
	TBranch *mleptrk10_branch;
	bool mleptrk10_isLoaded;
	float	trkreliso10_;
	TBranch *trkreliso10_branch;
	bool trkreliso10_isLoaded;
	float	trkpt5loose_;
	TBranch *trkpt5loose_branch;
	bool trkpt5loose_isLoaded;
	float	trkreliso5loose_;
	TBranch *trkreliso5loose_branch;
	bool trkreliso5loose_isLoaded;
	float	trkpt10loose_;
	TBranch *trkpt10loose_branch;
	bool trkpt10loose_isLoaded;
	float	trkreliso10loose_;
	TBranch *trkreliso10loose_branch;
	bool trkreliso10loose_isLoaded;
	float	trkpt10pt0p1_;
	TBranch *trkpt10pt0p1_branch;
	bool trkpt10pt0p1_isLoaded;
	float	trkreliso10pt0p1_;
	TBranch *trkreliso10pt0p1_branch;
	bool trkreliso10pt0p1_isLoaded;
	float	trkpt10pt0p2_;
	TBranch *trkpt10pt0p2_branch;
	bool trkpt10pt0p2_isLoaded;
	float	trkreliso10pt0p2_;
	TBranch *trkreliso10pt0p2_branch;
	bool trkreliso10pt0p2_isLoaded;
	float	trkpt10pt0p3_;
	TBranch *trkpt10pt0p3_branch;
	bool trkpt10pt0p3_isLoaded;
	float	trkreliso10pt0p3_;
	TBranch *trkreliso10pt0p3_branch;
	bool trkreliso10pt0p3_isLoaded;
	float	trkpt10pt0p4_;
	TBranch *trkpt10pt0p4_branch;
	bool trkpt10pt0p4_isLoaded;
	float	trkreliso10pt0p4_;
	TBranch *trkreliso10pt0p4_branch;
	bool trkreliso10pt0p4_isLoaded;
	float	trkpt10pt0p5_;
	TBranch *trkpt10pt0p5_branch;
	bool trkpt10pt0p5_isLoaded;
	float	trkreliso10pt0p5_;
	TBranch *trkreliso10pt0p5_branch;
	bool trkreliso10pt0p5_isLoaded;
	float	trkpt10pt0p6_;
	TBranch *trkpt10pt0p6_branch;
	bool trkpt10pt0p6_isLoaded;
	float	trkreliso10pt0p6_;
	TBranch *trkreliso10pt0p6_branch;
	bool trkreliso10pt0p6_isLoaded;
	float	trkpt10pt0p7_;
	TBranch *trkpt10pt0p7_branch;
	bool trkpt10pt0p7_isLoaded;
	float	trkreliso10pt0p7_;
	TBranch *trkreliso10pt0p7_branch;
	bool trkreliso10pt0p7_isLoaded;
	float	trkpt10pt0p8_;
	TBranch *trkpt10pt0p8_branch;
	bool trkpt10pt0p8_isLoaded;
	float	trkreliso10pt0p8_;
	TBranch *trkreliso10pt0p8_branch;
	bool trkreliso10pt0p8_isLoaded;
	float	trkpt10pt0p9_;
	TBranch *trkpt10pt0p9_branch;
	bool trkpt10pt0p9_isLoaded;
	float	trkreliso10pt0p9_;
	TBranch *trkreliso10pt0p9_branch;
	bool trkreliso10pt0p9_isLoaded;
	float	trkpt10pt1p0_;
	TBranch *trkpt10pt1p0_branch;
	bool trkpt10pt1p0_isLoaded;
	float	trkreliso10pt1p0_;
	TBranch *trkreliso10pt1p0_branch;
	bool trkreliso10pt1p0_isLoaded;
	float	pfcandiso5_;
	TBranch *pfcandiso5_branch;
	bool pfcandiso5_isLoaded;
	float	pfcandiso10_;
	TBranch *pfcandiso10_branch;
	bool pfcandiso10_isLoaded;
	float	pfcanddiriso10_;
	TBranch *pfcanddiriso10_branch;
	bool pfcanddiriso10_isLoaded;
	float	pfcandvetoiso10_;
	TBranch *pfcandvetoiso10_branch;
	bool pfcandvetoiso10_isLoaded;
	float	pfcandvetoLiso10_;
	TBranch *pfcandvetoLiso10_branch;
	bool pfcandvetoLiso10_isLoaded;
	float	pfcandisoOS10_;
	TBranch *pfcandisoOS10_branch;
	bool pfcandisoOS10_isLoaded;
	float	pfcandisoOS10looseZ_;
	TBranch *pfcandisoOS10looseZ_branch;
	bool pfcandisoOS10looseZ_isLoaded;
	float	pfcandiso5looseZ_;
	TBranch *pfcandiso5looseZ_branch;
	bool pfcandiso5looseZ_isLoaded;
	float	pfcandpt5_;
	TBranch *pfcandpt5_branch;
	bool pfcandpt5_isLoaded;
	float	pfcandpt10_;
	TBranch *pfcandpt10_branch;
	bool pfcandpt10_isLoaded;
	float	pfcanddirpt10_;
	TBranch *pfcanddirpt10_branch;
	bool pfcanddirpt10_isLoaded;
	float	pfcandvetopt10_;
	TBranch *pfcandvetopt10_branch;
	bool pfcandvetopt10_isLoaded;
	float	pfcandvetoLpt10_;
	TBranch *pfcandvetoLpt10_branch;
	bool pfcandvetoLpt10_isLoaded;
	float	pfcandptOS10_;
	TBranch *pfcandptOS10_branch;
	bool pfcandptOS10_isLoaded;
	float	pfcandptOS10looseZ_;
	TBranch *pfcandptOS10looseZ_branch;
	bool pfcandptOS10looseZ_isLoaded;
	float	pfcandpt5looseZ_;
	TBranch *pfcandpt5looseZ_branch;
	bool pfcandpt5looseZ_isLoaded;
	float	pfcanddz5_;
	TBranch *pfcanddz5_branch;
	bool pfcanddz5_isLoaded;
	float	pfcanddz10_;
	TBranch *pfcanddz10_branch;
	bool pfcanddz10_isLoaded;
	float	pfcanddirdz10_;
	TBranch *pfcanddirdz10_branch;
	bool pfcanddirdz10_isLoaded;
	float	pfcandvetodz10_;
	TBranch *pfcandvetodz10_branch;
	bool pfcandvetodz10_isLoaded;
	float	pfcandvetoLdz10_;
	TBranch *pfcandvetoLdz10_branch;
	bool pfcandvetoLdz10_isLoaded;
	float	pfcanddzOS10_;
	TBranch *pfcanddzOS10_branch;
	bool pfcanddzOS10_isLoaded;
	float	pfcanddzOS10looseZ_;
	TBranch *pfcanddzOS10looseZ_branch;
	bool pfcanddzOS10looseZ_isLoaded;
	float	pfcanddz5looseZ_;
	TBranch *pfcanddz5looseZ_branch;
	bool pfcanddz5looseZ_isLoaded;
	float	pfcandmindrj5_;
	TBranch *pfcandmindrj5_branch;
	bool pfcandmindrj5_isLoaded;
	float	pfcandmindrj10_;
	TBranch *pfcandmindrj10_branch;
	bool pfcandmindrj10_isLoaded;
	float	pfcanddirmindrj10_;
	TBranch *pfcanddirmindrj10_branch;
	bool pfcanddirmindrj10_isLoaded;
	float	pfcandvetomindrj10_;
	TBranch *pfcandvetomindrj10_branch;
	bool pfcandvetomindrj10_isLoaded;
	float	pfcandvetoLmindrj10_;
	TBranch *pfcandvetoLmindrj10_branch;
	bool pfcandvetoLmindrj10_isLoaded;
	float	pfcandpt10pt0p1_;
	TBranch *pfcandpt10pt0p1_branch;
	bool pfcandpt10pt0p1_isLoaded;
	float	pfcandiso10pt0p1_;
	TBranch *pfcandiso10pt0p1_branch;
	bool pfcandiso10pt0p1_isLoaded;
	float	pfcandpt10pt0p2_;
	TBranch *pfcandpt10pt0p2_branch;
	bool pfcandpt10pt0p2_isLoaded;
	float	pfcandiso10pt0p2_;
	TBranch *pfcandiso10pt0p2_branch;
	bool pfcandiso10pt0p2_isLoaded;
	float	pfcandpt10pt0p3_;
	TBranch *pfcandpt10pt0p3_branch;
	bool pfcandpt10pt0p3_isLoaded;
	float	pfcandiso10pt0p3_;
	TBranch *pfcandiso10pt0p3_branch;
	bool pfcandiso10pt0p3_isLoaded;
	float	pfcandpt10pt0p4_;
	TBranch *pfcandpt10pt0p4_branch;
	bool pfcandpt10pt0p4_isLoaded;
	float	pfcandiso10pt0p4_;
	TBranch *pfcandiso10pt0p4_branch;
	bool pfcandiso10pt0p4_isLoaded;
	float	pfcandpt10pt0p5_;
	TBranch *pfcandpt10pt0p5_branch;
	bool pfcandpt10pt0p5_isLoaded;
	float	pfcandiso10pt0p5_;
	TBranch *pfcandiso10pt0p5_branch;
	bool pfcandiso10pt0p5_isLoaded;
	float	pfcandpt10pt0p6_;
	TBranch *pfcandpt10pt0p6_branch;
	bool pfcandpt10pt0p6_isLoaded;
	float	pfcandiso10pt0p6_;
	TBranch *pfcandiso10pt0p6_branch;
	bool pfcandiso10pt0p6_isLoaded;
	float	pfcandpt10pt0p7_;
	TBranch *pfcandpt10pt0p7_branch;
	bool pfcandpt10pt0p7_isLoaded;
	float	pfcandiso10pt0p7_;
	TBranch *pfcandiso10pt0p7_branch;
	bool pfcandiso10pt0p7_isLoaded;
	float	pfcandpt10pt0p8_;
	TBranch *pfcandpt10pt0p8_branch;
	bool pfcandpt10pt0p8_isLoaded;
	float	pfcandiso10pt0p8_;
	TBranch *pfcandiso10pt0p8_branch;
	bool pfcandiso10pt0p8_isLoaded;
	float	pfcandpt10pt0p9_;
	TBranch *pfcandpt10pt0p9_branch;
	bool pfcandpt10pt0p9_isLoaded;
	float	pfcandiso10pt0p9_;
	TBranch *pfcandiso10pt0p9_branch;
	bool pfcandiso10pt0p9_isLoaded;
	float	pfcandpt10pt1p0_;
	TBranch *pfcandpt10pt1p0_branch;
	bool pfcandpt10pt1p0_isLoaded;
	float	pfcandiso10pt1p0_;
	TBranch *pfcandiso10pt1p0_branch;
	bool pfcandiso10pt1p0_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *pfcand5_;
	TBranch *pfcand5_branch;
	bool pfcand5_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *pfcand10_;
	TBranch *pfcand10_branch;
	bool pfcand10_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *pfcanddir10_;
	TBranch *pfcanddir10_branch;
	bool pfcanddir10_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *pfcandveto10_;
	TBranch *pfcandveto10_branch;
	bool pfcandveto10_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *pfcandvetoL10_;
	TBranch *pfcandvetoL10_branch;
	bool pfcandvetoL10_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *pfcandOS10_;
	TBranch *pfcandOS10_branch;
	bool pfcandOS10_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *pfcandOS10looseZ_;
	TBranch *pfcandOS10looseZ_branch;
	bool pfcandOS10looseZ_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *pfcand5looseZ_;
	TBranch *pfcand5looseZ_branch;
	bool pfcand5looseZ_isLoaded;
	int	pfTau15_leadPtcandID_;
	TBranch *pfTau15_leadPtcandID_branch;
	bool pfTau15_leadPtcandID_isLoaded;
	int	pfTau_leadPtcandID_;
	TBranch *pfTau_leadPtcandID_branch;
	bool pfTau_leadPtcandID_isLoaded;
	int	pfTauLoose_leadPtcandID_;
	TBranch *pfTauLoose_leadPtcandID_branch;
	bool pfTauLoose_leadPtcandID_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *pfTau15_;
	TBranch *pfTau15_branch;
	bool pfTau15_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *pfTau15_leadPtcand_;
	TBranch *pfTau15_leadPtcand_branch;
	bool pfTau15_leadPtcand_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *pfTau_;
	TBranch *pfTau_branch;
	bool pfTau_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *pfTau_leadPtcand_;
	TBranch *pfTau_leadPtcand_branch;
	bool pfTau_leadPtcand_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *pfTauLoose_;
	TBranch *pfTauLoose_branch;
	bool pfTauLoose_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *pfTauLoose_leadPtcand_;
	TBranch *pfTauLoose_leadPtcand_branch;
	bool pfTauLoose_leadPtcand_isLoaded;
	vector<float> *pfjets_beta_;
	TBranch *pfjets_beta_branch;
	bool pfjets_beta_isLoaded;
	vector<float> *pfjets_beta2_;
	TBranch *pfjets_beta2_branch;
	bool pfjets_beta2_isLoaded;
	vector<float> *pfjets_beta_0p1_;
	TBranch *pfjets_beta_0p1_branch;
	bool pfjets_beta_0p1_isLoaded;
	vector<float> *pfjets_beta_0p2_;
	TBranch *pfjets_beta_0p2_branch;
	bool pfjets_beta_0p2_isLoaded;
	vector<float> *pfjets_beta2_0p1_;
	TBranch *pfjets_beta2_0p1_branch;
	bool pfjets_beta2_0p1_isLoaded;
	vector<float> *pfjets_beta2_0p5_;
	TBranch *pfjets_beta2_0p5_branch;
	bool pfjets_beta2_0p5_isLoaded;
	vector<float> *pfjets_mvaPUid_;
	TBranch *pfjets_mvaPUid_branch;
	bool pfjets_mvaPUid_isLoaded;
	vector<float> *pfjets_mva5xPUid_;
	TBranch *pfjets_mva5xPUid_branch;
	bool pfjets_mva5xPUid_isLoaded;
	vector<float> *pfjets_mvaBeta_;
	TBranch *pfjets_mvaBeta_branch;
	bool pfjets_mvaBeta_isLoaded;
	bool	passes_isotrk_veto_;
	TBranch *passes_isotrk_veto_branch;
	bool passes_isotrk_veto_isLoaded;
	bool	passes_tau_veto_;
	TBranch *passes_tau_veto_branch;
	bool passes_tau_veto_isLoaded;
	int	njets_pv_tight0_;
	TBranch *njets_pv_tight0_branch;
	bool njets_pv_tight0_isLoaded;
	int	njets_pv_tight1_;
	TBranch *njets_pv_tight1_branch;
	bool njets_pv_tight1_isLoaded;
	int	njets_pv_tight2_;
	TBranch *njets_pv_tight2_branch;
	bool njets_pv_tight2_isLoaded;
public: 
void Init(TTree *tree) {
	lep1_p4_branch = 0;
	if (tree->GetBranch("lep1_p4") != 0) {
		lep1_p4_branch = tree->GetBranch("lep1_p4");
		if (lep1_p4_branch) {lep1_p4_branch->SetAddress(&lep1_p4_);}
	}
	lep1_mcp4_branch = 0;
	if (tree->GetBranch("lep1_mcp4") != 0) {
		lep1_mcp4_branch = tree->GetBranch("lep1_mcp4");
		if (lep1_mcp4_branch) {lep1_mcp4_branch->SetAddress(&lep1_mcp4_);}
	}
	lep1_mc3p4_branch = 0;
	if (tree->GetBranch("lep1_mc3p4") != 0) {
		lep1_mc3p4_branch = tree->GetBranch("lep1_mc3p4");
		if (lep1_mc3p4_branch) {lep1_mc3p4_branch->SetAddress(&lep1_mc3p4_);}
	}
	lep1_mc_momp4_branch = 0;
	if (tree->GetBranch("lep1_mc_momp4") != 0) {
		lep1_mc_momp4_branch = tree->GetBranch("lep1_mc_momp4");
		if (lep1_mc_momp4_branch) {lep1_mc_momp4_branch->SetAddress(&lep1_mc_momp4_);}
	}
	lep1_gsf_p4_branch = 0;
	if (tree->GetBranch("lep1_gsf_p4") != 0) {
		lep1_gsf_p4_branch = tree->GetBranch("lep1_gsf_p4");
		if (lep1_gsf_p4_branch) {lep1_gsf_p4_branch->SetAddress(&lep1_gsf_p4_);}
	}
	lep1_ctf_p4_branch = 0;
	if (tree->GetBranch("lep1_ctf_p4") != 0) {
		lep1_ctf_p4_branch = tree->GetBranch("lep1_ctf_p4");
		if (lep1_ctf_p4_branch) {lep1_ctf_p4_branch->SetAddress(&lep1_ctf_p4_);}
	}
	lep1_sc_p4_branch = 0;
	if (tree->GetBranch("lep1_sc_p4") != 0) {
		lep1_sc_p4_branch = tree->GetBranch("lep1_sc_p4");
		if (lep1_sc_p4_branch) {lep1_sc_p4_branch->SetAddress(&lep1_sc_p4_);}
	}
	lep1_gfit_p4_branch = 0;
	if (tree->GetBranch("lep1_gfit_p4") != 0) {
		lep1_gfit_p4_branch = tree->GetBranch("lep1_gfit_p4");
		if (lep1_gfit_p4_branch) {lep1_gfit_p4_branch->SetAddress(&lep1_gfit_p4_);}
	}
	lep2_p4_branch = 0;
	if (tree->GetBranch("lep2_p4") != 0) {
		lep2_p4_branch = tree->GetBranch("lep2_p4");
		if (lep2_p4_branch) {lep2_p4_branch->SetAddress(&lep2_p4_);}
	}
	lep2_mcp4_branch = 0;
	if (tree->GetBranch("lep2_mcp4") != 0) {
		lep2_mcp4_branch = tree->GetBranch("lep2_mcp4");
		if (lep2_mcp4_branch) {lep2_mcp4_branch->SetAddress(&lep2_mcp4_);}
	}
	lep2_mc3p4_branch = 0;
	if (tree->GetBranch("lep2_mc3p4") != 0) {
		lep2_mc3p4_branch = tree->GetBranch("lep2_mc3p4");
		if (lep2_mc3p4_branch) {lep2_mc3p4_branch->SetAddress(&lep2_mc3p4_);}
	}
	lep2_mc_momp4_branch = 0;
	if (tree->GetBranch("lep2_mc_momp4") != 0) {
		lep2_mc_momp4_branch = tree->GetBranch("lep2_mc_momp4");
		if (lep2_mc_momp4_branch) {lep2_mc_momp4_branch->SetAddress(&lep2_mc_momp4_);}
	}
	lep2_gsf_p4_branch = 0;
	if (tree->GetBranch("lep2_gsf_p4") != 0) {
		lep2_gsf_p4_branch = tree->GetBranch("lep2_gsf_p4");
		if (lep2_gsf_p4_branch) {lep2_gsf_p4_branch->SetAddress(&lep2_gsf_p4_);}
	}
	lep2_ctf_p4_branch = 0;
	if (tree->GetBranch("lep2_ctf_p4") != 0) {
		lep2_ctf_p4_branch = tree->GetBranch("lep2_ctf_p4");
		if (lep2_ctf_p4_branch) {lep2_ctf_p4_branch->SetAddress(&lep2_ctf_p4_);}
	}
	lep2_sc_p4_branch = 0;
	if (tree->GetBranch("lep2_sc_p4") != 0) {
		lep2_sc_p4_branch = tree->GetBranch("lep2_sc_p4");
		if (lep2_sc_p4_branch) {lep2_sc_p4_branch->SetAddress(&lep2_sc_p4_);}
	}
	lep2_gfit_p4_branch = 0;
	if (tree->GetBranch("lep2_gfit_p4") != 0) {
		lep2_gfit_p4_branch = tree->GetBranch("lep2_gfit_p4");
		if (lep2_gfit_p4_branch) {lep2_gfit_p4_branch->SetAddress(&lep2_gfit_p4_);}
	}
	dilep_p4_branch = 0;
	if (tree->GetBranch("dilep_p4") != 0) {
		dilep_p4_branch = tree->GetBranch("dilep_p4");
		if (dilep_p4_branch) {dilep_p4_branch->SetAddress(&dilep_p4_);}
	}
	lep3_p4_branch = 0;
	if (tree->GetBranch("lep3_p4") != 0) {
		lep3_p4_branch = tree->GetBranch("lep3_p4");
		if (lep3_p4_branch) {lep3_p4_branch->SetAddress(&lep3_p4_);}
	}
	lep3_mcp4_branch = 0;
	if (tree->GetBranch("lep3_mcp4") != 0) {
		lep3_mcp4_branch = tree->GetBranch("lep3_mcp4");
		if (lep3_mcp4_branch) {lep3_mcp4_branch->SetAddress(&lep3_mcp4_);}
	}
	lep3_mc3p4_branch = 0;
	if (tree->GetBranch("lep3_mc3p4") != 0) {
		lep3_mc3p4_branch = tree->GetBranch("lep3_mc3p4");
		if (lep3_mc3p4_branch) {lep3_mc3p4_branch->SetAddress(&lep3_mc3p4_);}
	}
	lep3_mc_momp4_branch = 0;
	if (tree->GetBranch("lep3_mc_momp4") != 0) {
		lep3_mc_momp4_branch = tree->GetBranch("lep3_mc_momp4");
		if (lep3_mc_momp4_branch) {lep3_mc_momp4_branch->SetAddress(&lep3_mc_momp4_);}
	}
	lep3_gsf_p4_branch = 0;
	if (tree->GetBranch("lep3_gsf_p4") != 0) {
		lep3_gsf_p4_branch = tree->GetBranch("lep3_gsf_p4");
		if (lep3_gsf_p4_branch) {lep3_gsf_p4_branch->SetAddress(&lep3_gsf_p4_);}
	}
	lep3_ctf_p4_branch = 0;
	if (tree->GetBranch("lep3_ctf_p4") != 0) {
		lep3_ctf_p4_branch = tree->GetBranch("lep3_ctf_p4");
		if (lep3_ctf_p4_branch) {lep3_ctf_p4_branch->SetAddress(&lep3_ctf_p4_);}
	}
	lep3_sc_p4_branch = 0;
	if (tree->GetBranch("lep3_sc_p4") != 0) {
		lep3_sc_p4_branch = tree->GetBranch("lep3_sc_p4");
		if (lep3_sc_p4_branch) {lep3_sc_p4_branch->SetAddress(&lep3_sc_p4_);}
	}
	lep3_gfit_p4_branch = 0;
	if (tree->GetBranch("lep3_gfit_p4") != 0) {
		lep3_gfit_p4_branch = tree->GetBranch("lep3_gfit_p4");
		if (lep3_gfit_p4_branch) {lep3_gfit_p4_branch->SetAddress(&lep3_gfit_p4_);}
	}
	lep1_nearjet_p4_branch = 0;
	if (tree->GetBranch("lep1_nearjet_p4") != 0) {
		lep1_nearjet_p4_branch = tree->GetBranch("lep1_nearjet_p4");
		if (lep1_nearjet_p4_branch) {lep1_nearjet_p4_branch->SetAddress(&lep1_nearjet_p4_);}
	}
	lep1_nearlep_p4_branch = 0;
	if (tree->GetBranch("lep1_nearlep_p4") != 0) {
		lep1_nearlep_p4_branch = tree->GetBranch("lep1_nearlep_p4");
		if (lep1_nearlep_p4_branch) {lep1_nearlep_p4_branch->SetAddress(&lep1_nearlep_p4_);}
	}
	lep2_nearjet_p4_branch = 0;
	if (tree->GetBranch("lep2_nearjet_p4") != 0) {
		lep2_nearjet_p4_branch = tree->GetBranch("lep2_nearjet_p4");
		if (lep2_nearjet_p4_branch) {lep2_nearjet_p4_branch->SetAddress(&lep2_nearjet_p4_);}
	}
	lep2_nearlep_p4_branch = 0;
	if (tree->GetBranch("lep2_nearlep_p4") != 0) {
		lep2_nearlep_p4_branch = tree->GetBranch("lep2_nearlep_p4");
		if (lep2_nearlep_p4_branch) {lep2_nearlep_p4_branch->SetAddress(&lep2_nearlep_p4_);}
	}
	vjets_p4_branch = 0;
	if (tree->GetBranch("vjets_p4") != 0) {
		vjets_p4_branch = tree->GetBranch("vjets_p4");
		if (vjets_p4_branch) {vjets_p4_branch->SetAddress(&vjets_p4_);}
	}
	vjets_p4_up_branch = 0;
	if (tree->GetBranch("vjets_p4_up") != 0) {
		vjets_p4_up_branch = tree->GetBranch("vjets_p4_up");
		if (vjets_p4_up_branch) {vjets_p4_up_branch->SetAddress(&vjets_p4_up_);}
	}
	vjets_p4_dn_branch = 0;
	if (tree->GetBranch("vjets_p4_dn") != 0) {
		vjets_p4_dn_branch = tree->GetBranch("vjets_p4_dn");
		if (vjets_p4_dn_branch) {vjets_p4_dn_branch->SetAddress(&vjets_p4_dn_);}
	}
	vjets_mc3p4_branch = 0;
	if (tree->GetBranch("vjets_mc3p4") != 0) {
		vjets_mc3p4_branch = tree->GetBranch("vjets_mc3p4");
		if (vjets_mc3p4_branch) {vjets_mc3p4_branch->SetAddress(&vjets_mc3p4_);}
	}
	vgenjets_p4_branch = 0;
	if (tree->GetBranch("vgenjets_p4") != 0) {
		vgenjets_p4_branch = tree->GetBranch("vgenjets_p4");
		if (vgenjets_p4_branch) {vgenjets_p4_branch->SetAddress(&vgenjets_p4_);}
	}
	vjets_nearjet_p4_branch = 0;
	if (tree->GetBranch("vjets_nearjet_p4") != 0) {
		vjets_nearjet_p4_branch = tree->GetBranch("vjets_nearjet_p4");
		if (vjets_nearjet_p4_branch) {vjets_nearjet_p4_branch->SetAddress(&vjets_nearjet_p4_);}
	}
	gen_lep1_p4_branch = 0;
	if (tree->GetBranch("gen_lep1_p4") != 0) {
		gen_lep1_p4_branch = tree->GetBranch("gen_lep1_p4");
		if (gen_lep1_p4_branch) {gen_lep1_p4_branch->SetAddress(&gen_lep1_p4_);}
	}
	gen_lep2_p4_branch = 0;
	if (tree->GetBranch("gen_lep2_p4") != 0) {
		gen_lep2_p4_branch = tree->GetBranch("gen_lep2_p4");
		if (gen_lep2_p4_branch) {gen_lep2_p4_branch->SetAddress(&gen_lep2_p4_);}
	}
	gen_dilep_p4_branch = 0;
	if (tree->GetBranch("gen_dilep_p4") != 0) {
		gen_dilep_p4_branch = tree->GetBranch("gen_dilep_p4");
		if (gen_dilep_p4_branch) {gen_dilep_p4_branch->SetAddress(&gen_dilep_p4_);}
	}
	pfcand5_branch = 0;
	if (tree->GetBranch("pfcand5") != 0) {
		pfcand5_branch = tree->GetBranch("pfcand5");
		if (pfcand5_branch) {pfcand5_branch->SetAddress(&pfcand5_);}
	}
	pfcand10_branch = 0;
	if (tree->GetBranch("pfcand10") != 0) {
		pfcand10_branch = tree->GetBranch("pfcand10");
		if (pfcand10_branch) {pfcand10_branch->SetAddress(&pfcand10_);}
	}
	pfcanddir10_branch = 0;
	if (tree->GetBranch("pfcanddir10") != 0) {
		pfcanddir10_branch = tree->GetBranch("pfcanddir10");
		if (pfcanddir10_branch) {pfcanddir10_branch->SetAddress(&pfcanddir10_);}
	}
	pfcandveto10_branch = 0;
	if (tree->GetBranch("pfcandveto10") != 0) {
		pfcandveto10_branch = tree->GetBranch("pfcandveto10");
		if (pfcandveto10_branch) {pfcandveto10_branch->SetAddress(&pfcandveto10_);}
	}
	pfcandvetoL10_branch = 0;
	if (tree->GetBranch("pfcandvetoL10") != 0) {
		pfcandvetoL10_branch = tree->GetBranch("pfcandvetoL10");
		if (pfcandvetoL10_branch) {pfcandvetoL10_branch->SetAddress(&pfcandvetoL10_);}
	}
	pfcandOS10_branch = 0;
	if (tree->GetBranch("pfcandOS10") != 0) {
		pfcandOS10_branch = tree->GetBranch("pfcandOS10");
		if (pfcandOS10_branch) {pfcandOS10_branch->SetAddress(&pfcandOS10_);}
	}
	pfcandOS10looseZ_branch = 0;
	if (tree->GetBranch("pfcandOS10looseZ") != 0) {
		pfcandOS10looseZ_branch = tree->GetBranch("pfcandOS10looseZ");
		if (pfcandOS10looseZ_branch) {pfcandOS10looseZ_branch->SetAddress(&pfcandOS10looseZ_);}
	}
	pfcand5looseZ_branch = 0;
	if (tree->GetBranch("pfcand5looseZ") != 0) {
		pfcand5looseZ_branch = tree->GetBranch("pfcand5looseZ");
		if (pfcand5looseZ_branch) {pfcand5looseZ_branch->SetAddress(&pfcand5looseZ_);}
	}
	pfTau15_branch = 0;
	if (tree->GetBranch("pfTau15") != 0) {
		pfTau15_branch = tree->GetBranch("pfTau15");
		if (pfTau15_branch) {pfTau15_branch->SetAddress(&pfTau15_);}
	}
	pfTau15_leadPtcand_branch = 0;
	if (tree->GetBranch("pfTau15_leadPtcand") != 0) {
		pfTau15_leadPtcand_branch = tree->GetBranch("pfTau15_leadPtcand");
		if (pfTau15_leadPtcand_branch) {pfTau15_leadPtcand_branch->SetAddress(&pfTau15_leadPtcand_);}
	}
	pfTau_branch = 0;
	if (tree->GetBranch("pfTau") != 0) {
		pfTau_branch = tree->GetBranch("pfTau");
		if (pfTau_branch) {pfTau_branch->SetAddress(&pfTau_);}
	}
	pfTau_leadPtcand_branch = 0;
	if (tree->GetBranch("pfTau_leadPtcand") != 0) {
		pfTau_leadPtcand_branch = tree->GetBranch("pfTau_leadPtcand");
		if (pfTau_leadPtcand_branch) {pfTau_leadPtcand_branch->SetAddress(&pfTau_leadPtcand_);}
	}
	pfTauLoose_branch = 0;
	if (tree->GetBranch("pfTauLoose") != 0) {
		pfTauLoose_branch = tree->GetBranch("pfTauLoose");
		if (pfTauLoose_branch) {pfTauLoose_branch->SetAddress(&pfTauLoose_);}
	}
	pfTauLoose_leadPtcand_branch = 0;
	if (tree->GetBranch("pfTauLoose_leadPtcand") != 0) {
		pfTauLoose_leadPtcand_branch = tree->GetBranch("pfTauLoose_leadPtcand");
		if (pfTauLoose_leadPtcand_branch) {pfTauLoose_leadPtcand_branch->SetAddress(&pfTauLoose_leadPtcand_);}
	}
  tree->SetMakeClass(1);
	run_branch = 0;
	if (tree->GetBranch("run") != 0) {
		run_branch = tree->GetBranch("run");
		if (run_branch) {run_branch->SetAddress(&run_);}
	}
	ls_branch = 0;
	if (tree->GetBranch("ls") != 0) {
		ls_branch = tree->GetBranch("ls");
		if (ls_branch) {ls_branch->SetAddress(&ls_);}
	}
	evt_branch = 0;
	if (tree->GetBranch("evt") != 0) {
		evt_branch = tree->GetBranch("evt");
		if (evt_branch) {evt_branch->SetAddress(&evt_);}
	}
	is_real_data_branch = 0;
	if (tree->GetBranch("is_real_data") != 0) {
		is_real_data_branch = tree->GetBranch("is_real_data");
		if (is_real_data_branch) {is_real_data_branch->SetAddress(&is_real_data_);}
	}
	sample_branch = 0;
	if (tree->GetBranch("sample") != 0) {
		sample_branch = tree->GetBranch("sample");
		if (sample_branch) {sample_branch->SetAddress(&sample_);}
	}
	nvtxs_branch = 0;
	if (tree->GetBranch("nvtxs") != 0) {
		nvtxs_branch = tree->GetBranch("nvtxs");
		if (nvtxs_branch) {nvtxs_branch->SetAddress(&nvtxs_);}
	}
	vtx_idx_branch = 0;
	if (tree->GetBranch("vtx_idx") != 0) {
		vtx_idx_branch = tree->GetBranch("vtx_idx");
		if (vtx_idx_branch) {vtx_idx_branch->SetAddress(&vtx_idx_);}
	}
	pfmet_branch = 0;
	if (tree->GetBranch("pfmet") != 0) {
		pfmet_branch = tree->GetBranch("pfmet");
		if (pfmet_branch) {pfmet_branch->SetAddress(&pfmet_);}
	}
	pfmet_phi_branch = 0;
	if (tree->GetBranch("pfmet_phi") != 0) {
		pfmet_phi_branch = tree->GetBranch("pfmet_phi");
		if (pfmet_phi_branch) {pfmet_phi_branch->SetAddress(&pfmet_phi_);}
	}
	uncorpfmet_branch = 0;
	if (tree->GetBranch("uncorpfmet") != 0) {
		uncorpfmet_branch = tree->GetBranch("uncorpfmet");
		if (uncorpfmet_branch) {uncorpfmet_branch->SetAddress(&uncorpfmet_);}
	}
	uncorpfmet_phi_branch = 0;
	if (tree->GetBranch("uncorpfmet_phi") != 0) {
		uncorpfmet_phi_branch = tree->GetBranch("uncorpfmet_phi");
		if (uncorpfmet_phi_branch) {uncorpfmet_phi_branch->SetAddress(&uncorpfmet_phi_);}
	}
	pu_nvtxs_branch = 0;
	if (tree->GetBranch("pu_nvtxs") != 0) {
		pu_nvtxs_branch = tree->GetBranch("pu_nvtxs");
		if (pu_nvtxs_branch) {pu_nvtxs_branch->SetAddress(&pu_nvtxs_);}
	}
	pu_ntrueint_branch = 0;
	if (tree->GetBranch("pu_ntrueint") != 0) {
		pu_ntrueint_branch = tree->GetBranch("pu_ntrueint");
		if (pu_ntrueint_branch) {pu_ntrueint_branch->SetAddress(&pu_ntrueint_);}
	}
	scale1fb_branch = 0;
	if (tree->GetBranch("scale1fb") != 0) {
		scale1fb_branch = tree->GetBranch("scale1fb");
		if (scale1fb_branch) {scale1fb_branch->SetAddress(&scale1fb_);}
	}
	xsec_branch = 0;
	if (tree->GetBranch("xsec") != 0) {
		xsec_branch = tree->GetBranch("xsec");
		if (xsec_branch) {xsec_branch->SetAddress(&xsec_);}
	}
	nevts_branch = 0;
	if (tree->GetBranch("nevts") != 0) {
		nevts_branch = tree->GetBranch("nevts");
		if (nevts_branch) {nevts_branch->SetAddress(&nevts_);}
	}
	kfactor_branch = 0;
	if (tree->GetBranch("kfactor") != 0) {
		kfactor_branch = tree->GetBranch("kfactor");
		if (kfactor_branch) {kfactor_branch->SetAddress(&kfactor_);}
	}
	gen_met_branch = 0;
	if (tree->GetBranch("gen_met") != 0) {
		gen_met_branch = tree->GetBranch("gen_met");
		if (gen_met_branch) {gen_met_branch->SetAddress(&gen_met_);}
	}
	gen_met_phi_branch = 0;
	if (tree->GetBranch("gen_met_phi") != 0) {
		gen_met_phi_branch = tree->GetBranch("gen_met_phi");
		if (gen_met_phi_branch) {gen_met_phi_branch->SetAddress(&gen_met_phi_);}
	}
	dataset_branch = 0;
	if (tree->GetBranch("dataset") != 0) {
		dataset_branch = tree->GetBranch("dataset");
		if (dataset_branch) {dataset_branch->SetAddress(&dataset_);}
	}
	filename_branch = 0;
	if (tree->GetBranch("filename") != 0) {
		filename_branch = tree->GetBranch("filename");
		if (filename_branch) {filename_branch->SetAddress(&filename_);}
	}
	filt_csc_branch = 0;
	if (tree->GetBranch("filt_csc") != 0) {
		filt_csc_branch = tree->GetBranch("filt_csc");
		if (filt_csc_branch) {filt_csc_branch->SetAddress(&filt_csc_);}
	}
	filt_hbhe_branch = 0;
	if (tree->GetBranch("filt_hbhe") != 0) {
		filt_hbhe_branch = tree->GetBranch("filt_hbhe");
		if (filt_hbhe_branch) {filt_hbhe_branch->SetAddress(&filt_hbhe_);}
	}
	filt_hcallaser_branch = 0;
	if (tree->GetBranch("filt_hcallaser") != 0) {
		filt_hcallaser_branch = tree->GetBranch("filt_hcallaser");
		if (filt_hcallaser_branch) {filt_hcallaser_branch->SetAddress(&filt_hcallaser_);}
	}
	filt_ecallaser_branch = 0;
	if (tree->GetBranch("filt_ecallaser") != 0) {
		filt_ecallaser_branch = tree->GetBranch("filt_ecallaser");
		if (filt_ecallaser_branch) {filt_ecallaser_branch->SetAddress(&filt_ecallaser_);}
	}
	filt_ecaltp_branch = 0;
	if (tree->GetBranch("filt_ecaltp") != 0) {
		filt_ecaltp_branch = tree->GetBranch("filt_ecaltp");
		if (filt_ecaltp_branch) {filt_ecaltp_branch->SetAddress(&filt_ecaltp_);}
	}
	filt_trkfail_branch = 0;
	if (tree->GetBranch("filt_trkfail") != 0) {
		filt_trkfail_branch = tree->GetBranch("filt_trkfail");
		if (filt_trkfail_branch) {filt_trkfail_branch->SetAddress(&filt_trkfail_);}
	}
	filt_eebadsc_branch = 0;
	if (tree->GetBranch("filt_eebadsc") != 0) {
		filt_eebadsc_branch = tree->GetBranch("filt_eebadsc");
		if (filt_eebadsc_branch) {filt_eebadsc_branch->SetAddress(&filt_eebadsc_);}
	}
	passes_metfilters_branch = 0;
	if (tree->GetBranch("passes_metfilters") != 0) {
		passes_metfilters_branch = tree->GetBranch("passes_metfilters");
		if (passes_metfilters_branch) {passes_metfilters_branch->SetAddress(&passes_metfilters_);}
	}
	lep1_passes_id_branch = 0;
	if (tree->GetBranch("lep1_passes_id") != 0) {
		lep1_passes_id_branch = tree->GetBranch("lep1_passes_id");
		if (lep1_passes_id_branch) {lep1_passes_id_branch->SetAddress(&lep1_passes_id_);}
	}
	lep1_passes_iso_branch = 0;
	if (tree->GetBranch("lep1_passes_iso") != 0) {
		lep1_passes_iso_branch = tree->GetBranch("lep1_passes_iso");
		if (lep1_passes_iso_branch) {lep1_passes_iso_branch->SetAddress(&lep1_passes_iso_);}
	}
	lep1_is_num_branch = 0;
	if (tree->GetBranch("lep1_is_num") != 0) {
		lep1_is_num_branch = tree->GetBranch("lep1_is_num");
		if (lep1_is_num_branch) {lep1_is_num_branch->SetAddress(&lep1_is_num_);}
	}
	lep1_is_den_branch = 0;
	if (tree->GetBranch("lep1_is_den") != 0) {
		lep1_is_den_branch = tree->GetBranch("lep1_is_den");
		if (lep1_is_den_branch) {lep1_is_den_branch->SetAddress(&lep1_is_den_);}
	}
	lep1_is_fo_branch = 0;
	if (tree->GetBranch("lep1_is_fo") != 0) {
		lep1_is_fo_branch = tree->GetBranch("lep1_is_fo");
		if (lep1_is_fo_branch) {lep1_is_fo_branch->SetAddress(&lep1_is_fo_);}
	}
	lep1_is_fromw_branch = 0;
	if (tree->GetBranch("lep1_is_fromw") != 0) {
		lep1_is_fromw_branch = tree->GetBranch("lep1_is_fromw");
		if (lep1_is_fromw_branch) {lep1_is_fromw_branch->SetAddress(&lep1_is_fromw_);}
	}
	lep1_charge_branch = 0;
	if (tree->GetBranch("lep1_charge") != 0) {
		lep1_charge_branch = tree->GetBranch("lep1_charge");
		if (lep1_charge_branch) {lep1_charge_branch->SetAddress(&lep1_charge_);}
	}
	lep1_pdgid_branch = 0;
	if (tree->GetBranch("lep1_pdgid") != 0) {
		lep1_pdgid_branch = tree->GetBranch("lep1_pdgid");
		if (lep1_pdgid_branch) {lep1_pdgid_branch->SetAddress(&lep1_pdgid_);}
	}
	lep1_type_branch = 0;
	if (tree->GetBranch("lep1_type") != 0) {
		lep1_type_branch = tree->GetBranch("lep1_type");
		if (lep1_type_branch) {lep1_type_branch->SetAddress(&lep1_type_);}
	}
	lep1_d0_branch = 0;
	if (tree->GetBranch("lep1_d0") != 0) {
		lep1_d0_branch = tree->GetBranch("lep1_d0");
		if (lep1_d0_branch) {lep1_d0_branch->SetAddress(&lep1_d0_);}
	}
	lep1_d0err_branch = 0;
	if (tree->GetBranch("lep1_d0err") != 0) {
		lep1_d0err_branch = tree->GetBranch("lep1_d0err");
		if (lep1_d0err_branch) {lep1_d0err_branch->SetAddress(&lep1_d0err_);}
	}
	lep1_dz_branch = 0;
	if (tree->GetBranch("lep1_dz") != 0) {
		lep1_dz_branch = tree->GetBranch("lep1_dz");
		if (lep1_dz_branch) {lep1_dz_branch->SetAddress(&lep1_dz_);}
	}
	lep1_ip3d_branch = 0;
	if (tree->GetBranch("lep1_ip3d") != 0) {
		lep1_ip3d_branch = tree->GetBranch("lep1_ip3d");
		if (lep1_ip3d_branch) {lep1_ip3d_branch->SetAddress(&lep1_ip3d_);}
	}
	lep1_ip3derr_branch = 0;
	if (tree->GetBranch("lep1_ip3derr") != 0) {
		lep1_ip3derr_branch = tree->GetBranch("lep1_ip3derr");
		if (lep1_ip3derr_branch) {lep1_ip3derr_branch->SetAddress(&lep1_ip3derr_);}
	}
	lep1_dzerr_branch = 0;
	if (tree->GetBranch("lep1_dzerr") != 0) {
		lep1_dzerr_branch = tree->GetBranch("lep1_dzerr");
		if (lep1_dzerr_branch) {lep1_dzerr_branch->SetAddress(&lep1_dzerr_);}
	}
	lep1_mt_branch = 0;
	if (tree->GetBranch("lep1_mt") != 0) {
		lep1_mt_branch = tree->GetBranch("lep1_mt");
		if (lep1_mt_branch) {lep1_mt_branch->SetAddress(&lep1_mt_);}
	}
	lep1_corpfiso_branch = 0;
	if (tree->GetBranch("lep1_corpfiso") != 0) {
		lep1_corpfiso_branch = tree->GetBranch("lep1_corpfiso");
		if (lep1_corpfiso_branch) {lep1_corpfiso_branch->SetAddress(&lep1_corpfiso_);}
	}
	lep1_pfiso_branch = 0;
	if (tree->GetBranch("lep1_pfiso") != 0) {
		lep1_pfiso_branch = tree->GetBranch("lep1_pfiso");
		if (lep1_pfiso_branch) {lep1_pfiso_branch->SetAddress(&lep1_pfiso_);}
	}
	lep1_chiso_branch = 0;
	if (tree->GetBranch("lep1_chiso") != 0) {
		lep1_chiso_branch = tree->GetBranch("lep1_chiso");
		if (lep1_chiso_branch) {lep1_chiso_branch->SetAddress(&lep1_chiso_);}
	}
	lep1_emiso_branch = 0;
	if (tree->GetBranch("lep1_emiso") != 0) {
		lep1_emiso_branch = tree->GetBranch("lep1_emiso");
		if (lep1_emiso_branch) {lep1_emiso_branch->SetAddress(&lep1_emiso_);}
	}
	lep1_nhiso_branch = 0;
	if (tree->GetBranch("lep1_nhiso") != 0) {
		lep1_nhiso_branch = tree->GetBranch("lep1_nhiso");
		if (lep1_nhiso_branch) {lep1_nhiso_branch->SetAddress(&lep1_nhiso_);}
	}
	lep1_corpfiso04_branch = 0;
	if (tree->GetBranch("lep1_corpfiso04") != 0) {
		lep1_corpfiso04_branch = tree->GetBranch("lep1_corpfiso04");
		if (lep1_corpfiso04_branch) {lep1_corpfiso04_branch->SetAddress(&lep1_corpfiso04_);}
	}
	lep1_pfiso04_branch = 0;
	if (tree->GetBranch("lep1_pfiso04") != 0) {
		lep1_pfiso04_branch = tree->GetBranch("lep1_pfiso04");
		if (lep1_pfiso04_branch) {lep1_pfiso04_branch->SetAddress(&lep1_pfiso04_);}
	}
	lep1_chiso04_branch = 0;
	if (tree->GetBranch("lep1_chiso04") != 0) {
		lep1_chiso04_branch = tree->GetBranch("lep1_chiso04");
		if (lep1_chiso04_branch) {lep1_chiso04_branch->SetAddress(&lep1_chiso04_);}
	}
	lep1_emiso04_branch = 0;
	if (tree->GetBranch("lep1_emiso04") != 0) {
		lep1_emiso04_branch = tree->GetBranch("lep1_emiso04");
		if (lep1_emiso04_branch) {lep1_emiso04_branch->SetAddress(&lep1_emiso04_);}
	}
	lep1_nhiso04_branch = 0;
	if (tree->GetBranch("lep1_nhiso04") != 0) {
		lep1_nhiso04_branch = tree->GetBranch("lep1_nhiso04");
		if (lep1_nhiso04_branch) {lep1_nhiso04_branch->SetAddress(&lep1_nhiso04_);}
	}
	lep1_cordetiso_branch = 0;
	if (tree->GetBranch("lep1_cordetiso") != 0) {
		lep1_cordetiso_branch = tree->GetBranch("lep1_cordetiso");
		if (lep1_cordetiso_branch) {lep1_cordetiso_branch->SetAddress(&lep1_cordetiso_);}
	}
	lep1_detiso_branch = 0;
	if (tree->GetBranch("lep1_detiso") != 0) {
		lep1_detiso_branch = tree->GetBranch("lep1_detiso");
		if (lep1_detiso_branch) {lep1_detiso_branch->SetAddress(&lep1_detiso_);}
	}
	lep1_trkiso_branch = 0;
	if (tree->GetBranch("lep1_trkiso") != 0) {
		lep1_trkiso_branch = tree->GetBranch("lep1_trkiso");
		if (lep1_trkiso_branch) {lep1_trkiso_branch->SetAddress(&lep1_trkiso_);}
	}
	lep1_ecaliso_branch = 0;
	if (tree->GetBranch("lep1_ecaliso") != 0) {
		lep1_ecaliso_branch = tree->GetBranch("lep1_ecaliso");
		if (lep1_ecaliso_branch) {lep1_ecaliso_branch->SetAddress(&lep1_ecaliso_);}
	}
	lep1_hcaliso_branch = 0;
	if (tree->GetBranch("lep1_hcaliso") != 0) {
		lep1_hcaliso_branch = tree->GetBranch("lep1_hcaliso");
		if (lep1_hcaliso_branch) {lep1_hcaliso_branch->SetAddress(&lep1_hcaliso_);}
	}
	lep1_cordetiso04_branch = 0;
	if (tree->GetBranch("lep1_cordetiso04") != 0) {
		lep1_cordetiso04_branch = tree->GetBranch("lep1_cordetiso04");
		if (lep1_cordetiso04_branch) {lep1_cordetiso04_branch->SetAddress(&lep1_cordetiso04_);}
	}
	lep1_detiso04_branch = 0;
	if (tree->GetBranch("lep1_detiso04") != 0) {
		lep1_detiso04_branch = tree->GetBranch("lep1_detiso04");
		if (lep1_detiso04_branch) {lep1_detiso04_branch->SetAddress(&lep1_detiso04_);}
	}
	lep1_trkiso04_branch = 0;
	if (tree->GetBranch("lep1_trkiso04") != 0) {
		lep1_trkiso04_branch = tree->GetBranch("lep1_trkiso04");
		if (lep1_trkiso04_branch) {lep1_trkiso04_branch->SetAddress(&lep1_trkiso04_);}
	}
	lep1_ecaliso04_branch = 0;
	if (tree->GetBranch("lep1_ecaliso04") != 0) {
		lep1_ecaliso04_branch = tree->GetBranch("lep1_ecaliso04");
		if (lep1_ecaliso04_branch) {lep1_ecaliso04_branch->SetAddress(&lep1_ecaliso04_);}
	}
	lep1_hcaliso04_branch = 0;
	if (tree->GetBranch("lep1_hcaliso04") != 0) {
		lep1_hcaliso04_branch = tree->GetBranch("lep1_hcaliso04");
		if (lep1_hcaliso04_branch) {lep1_hcaliso04_branch->SetAddress(&lep1_hcaliso04_);}
	}
	lep1_effarea_branch = 0;
	if (tree->GetBranch("lep1_effarea") != 0) {
		lep1_effarea_branch = tree->GetBranch("lep1_effarea");
		if (lep1_effarea_branch) {lep1_effarea_branch->SetAddress(&lep1_effarea_);}
	}
	lep1_effarea04_branch = 0;
	if (tree->GetBranch("lep1_effarea04") != 0) {
		lep1_effarea04_branch = tree->GetBranch("lep1_effarea04");
		if (lep1_effarea04_branch) {lep1_effarea04_branch->SetAddress(&lep1_effarea04_);}
	}
	lep1_dbeta_branch = 0;
	if (tree->GetBranch("lep1_dbeta") != 0) {
		lep1_dbeta_branch = tree->GetBranch("lep1_dbeta");
		if (lep1_dbeta_branch) {lep1_dbeta_branch->SetAddress(&lep1_dbeta_);}
	}
	lep1_dbeta04_branch = 0;
	if (tree->GetBranch("lep1_dbeta04") != 0) {
		lep1_dbeta04_branch = tree->GetBranch("lep1_dbeta04");
		if (lep1_dbeta04_branch) {lep1_dbeta04_branch->SetAddress(&lep1_dbeta04_);}
	}
	lep1_sf_lepeff_branch = 0;
	if (tree->GetBranch("lep1_sf_lepeff") != 0) {
		lep1_sf_lepeff_branch = tree->GetBranch("lep1_sf_lepeff");
		if (lep1_sf_lepeff_branch) {lep1_sf_lepeff_branch->SetAddress(&lep1_sf_lepeff_);}
	}
	lep1_sf_trig_branch = 0;
	if (tree->GetBranch("lep1_sf_trig") != 0) {
		lep1_sf_trig_branch = tree->GetBranch("lep1_sf_trig");
		if (lep1_sf_trig_branch) {lep1_sf_trig_branch->SetAddress(&lep1_sf_trig_);}
	}
	lep1_mcid_branch = 0;
	if (tree->GetBranch("lep1_mcid") != 0) {
		lep1_mcid_branch = tree->GetBranch("lep1_mcid");
		if (lep1_mcid_branch) {lep1_mcid_branch->SetAddress(&lep1_mcid_);}
	}
	lep1_mc3id_branch = 0;
	if (tree->GetBranch("lep1_mc3id") != 0) {
		lep1_mc3id_branch = tree->GetBranch("lep1_mc3id");
		if (lep1_mc3id_branch) {lep1_mc3id_branch->SetAddress(&lep1_mc3id_);}
	}
	lep1_momid_branch = 0;
	if (tree->GetBranch("lep1_momid") != 0) {
		lep1_momid_branch = tree->GetBranch("lep1_momid");
		if (lep1_momid_branch) {lep1_momid_branch->SetAddress(&lep1_momid_);}
	}
	lep1_mc3_momid_branch = 0;
	if (tree->GetBranch("lep1_mc3_momid") != 0) {
		lep1_mc3_momid_branch = tree->GetBranch("lep1_mc3_momid");
		if (lep1_mc3_momid_branch) {lep1_mc3_momid_branch->SetAddress(&lep1_mc3_momid_);}
	}
	lep1_q3agree_branch = 0;
	if (tree->GetBranch("lep1_q3agree") != 0) {
		lep1_q3agree_branch = tree->GetBranch("lep1_q3agree");
		if (lep1_q3agree_branch) {lep1_q3agree_branch->SetAddress(&lep1_q3agree_);}
	}
	lep1_is_conv_branch = 0;
	if (tree->GetBranch("lep1_is_conv") != 0) {
		lep1_is_conv_branch = tree->GetBranch("lep1_is_conv");
		if (lep1_is_conv_branch) {lep1_is_conv_branch->SetAddress(&lep1_is_conv_);}
	}
	lep1_qsc_branch = 0;
	if (tree->GetBranch("lep1_qsc") != 0) {
		lep1_qsc_branch = tree->GetBranch("lep1_qsc");
		if (lep1_qsc_branch) {lep1_qsc_branch->SetAddress(&lep1_qsc_);}
	}
	lep1_qctf_branch = 0;
	if (tree->GetBranch("lep1_qctf") != 0) {
		lep1_qctf_branch = tree->GetBranch("lep1_qctf");
		if (lep1_qctf_branch) {lep1_qctf_branch->SetAddress(&lep1_qctf_);}
	}
	lep1_qgsf_branch = 0;
	if (tree->GetBranch("lep1_qgsf") != 0) {
		lep1_qgsf_branch = tree->GetBranch("lep1_qgsf");
		if (lep1_qgsf_branch) {lep1_qgsf_branch->SetAddress(&lep1_qgsf_);}
	}
	lep1_nmhits_branch = 0;
	if (tree->GetBranch("lep1_nmhits") != 0) {
		lep1_nmhits_branch = tree->GetBranch("lep1_nmhits");
		if (lep1_nmhits_branch) {lep1_nmhits_branch->SetAddress(&lep1_nmhits_);}
	}
	lep1_eleid_veto_branch = 0;
	if (tree->GetBranch("lep1_eleid_veto") != 0) {
		lep1_eleid_veto_branch = tree->GetBranch("lep1_eleid_veto");
		if (lep1_eleid_veto_branch) {lep1_eleid_veto_branch->SetAddress(&lep1_eleid_veto_);}
	}
	lep1_eleid_loose_branch = 0;
	if (tree->GetBranch("lep1_eleid_loose") != 0) {
		lep1_eleid_loose_branch = tree->GetBranch("lep1_eleid_loose");
		if (lep1_eleid_loose_branch) {lep1_eleid_loose_branch->SetAddress(&lep1_eleid_loose_);}
	}
	lep1_eleid_medium_branch = 0;
	if (tree->GetBranch("lep1_eleid_medium") != 0) {
		lep1_eleid_medium_branch = tree->GetBranch("lep1_eleid_medium");
		if (lep1_eleid_medium_branch) {lep1_eleid_medium_branch->SetAddress(&lep1_eleid_medium_);}
	}
	lep1_eleid_tight_branch = 0;
	if (tree->GetBranch("lep1_eleid_tight") != 0) {
		lep1_eleid_tight_branch = tree->GetBranch("lep1_eleid_tight");
		if (lep1_eleid_tight_branch) {lep1_eleid_tight_branch->SetAddress(&lep1_eleid_tight_);}
	}
	lep1_dphiin_branch = 0;
	if (tree->GetBranch("lep1_dphiin") != 0) {
		lep1_dphiin_branch = tree->GetBranch("lep1_dphiin");
		if (lep1_dphiin_branch) {lep1_dphiin_branch->SetAddress(&lep1_dphiin_);}
	}
	lep1_detain_branch = 0;
	if (tree->GetBranch("lep1_detain") != 0) {
		lep1_detain_branch = tree->GetBranch("lep1_detain");
		if (lep1_detain_branch) {lep1_detain_branch->SetAddress(&lep1_detain_);}
	}
	lep1_sieie_branch = 0;
	if (tree->GetBranch("lep1_sieie") != 0) {
		lep1_sieie_branch = tree->GetBranch("lep1_sieie");
		if (lep1_sieie_branch) {lep1_sieie_branch->SetAddress(&lep1_sieie_);}
	}
	lep1_hoe_branch = 0;
	if (tree->GetBranch("lep1_hoe") != 0) {
		lep1_hoe_branch = tree->GetBranch("lep1_hoe");
		if (lep1_hoe_branch) {lep1_hoe_branch->SetAddress(&lep1_hoe_);}
	}
	lep1_ooemoop_branch = 0;
	if (tree->GetBranch("lep1_ooemoop") != 0) {
		lep1_ooemoop_branch = tree->GetBranch("lep1_ooemoop");
		if (lep1_ooemoop_branch) {lep1_ooemoop_branch->SetAddress(&lep1_ooemoop_);}
	}
	lep1_conv_dist_branch = 0;
	if (tree->GetBranch("lep1_conv_dist") != 0) {
		lep1_conv_dist_branch = tree->GetBranch("lep1_conv_dist");
		if (lep1_conv_dist_branch) {lep1_conv_dist_branch->SetAddress(&lep1_conv_dist_);}
	}
	lep1_conv_dcot_branch = 0;
	if (tree->GetBranch("lep1_conv_dcot") != 0) {
		lep1_conv_dcot_branch = tree->GetBranch("lep1_conv_dcot");
		if (lep1_conv_dcot_branch) {lep1_conv_dcot_branch->SetAddress(&lep1_conv_dcot_);}
	}
	lep1_is_global_branch = 0;
	if (tree->GetBranch("lep1_is_global") != 0) {
		lep1_is_global_branch = tree->GetBranch("lep1_is_global");
		if (lep1_is_global_branch) {lep1_is_global_branch->SetAddress(&lep1_is_global_);}
	}
	lep1_is_tracker_branch = 0;
	if (tree->GetBranch("lep1_is_tracker") != 0) {
		lep1_is_tracker_branch = tree->GetBranch("lep1_is_tracker");
		if (lep1_is_tracker_branch) {lep1_is_tracker_branch->SetAddress(&lep1_is_tracker_);}
	}
	lep1_is_stamu_branch = 0;
	if (tree->GetBranch("lep1_is_stamu") != 0) {
		lep1_is_stamu_branch = tree->GetBranch("lep1_is_stamu");
		if (lep1_is_stamu_branch) {lep1_is_stamu_branch->SetAddress(&lep1_is_stamu_);}
	}
	lep1_is_pfmu_branch = 0;
	if (tree->GetBranch("lep1_is_pfmu") != 0) {
		lep1_is_pfmu_branch = tree->GetBranch("lep1_is_pfmu");
		if (lep1_is_pfmu_branch) {lep1_is_pfmu_branch->SetAddress(&lep1_is_pfmu_);}
	}
	lep1_is_loosemu_branch = 0;
	if (tree->GetBranch("lep1_is_loosemu") != 0) {
		lep1_is_loosemu_branch = tree->GetBranch("lep1_is_loosemu");
		if (lep1_is_loosemu_branch) {lep1_is_loosemu_branch->SetAddress(&lep1_is_loosemu_);}
	}
	lep1_is_tightmu_branch = 0;
	if (tree->GetBranch("lep1_is_tightmu") != 0) {
		lep1_is_tightmu_branch = tree->GetBranch("lep1_is_tightmu");
		if (lep1_is_tightmu_branch) {lep1_is_tightmu_branch->SetAddress(&lep1_is_tightmu_);}
	}
	lep1_npixelhits_branch = 0;
	if (tree->GetBranch("lep1_npixelhits") != 0) {
		lep1_npixelhits_branch = tree->GetBranch("lep1_npixelhits");
		if (lep1_npixelhits_branch) {lep1_npixelhits_branch->SetAddress(&lep1_npixelhits_);}
	}
	lep1_nsihits_branch = 0;
	if (tree->GetBranch("lep1_nsihits") != 0) {
		lep1_nsihits_branch = tree->GetBranch("lep1_nsihits");
		if (lep1_nsihits_branch) {lep1_nsihits_branch->SetAddress(&lep1_nsihits_);}
	}
	lep1_nsilayers_branch = 0;
	if (tree->GetBranch("lep1_nsilayers") != 0) {
		lep1_nsilayers_branch = tree->GetBranch("lep1_nsilayers");
		if (lep1_nsilayers_branch) {lep1_nsilayers_branch->SetAddress(&lep1_nsilayers_);}
	}
	lep1_nstahits_branch = 0;
	if (tree->GetBranch("lep1_nstahits") != 0) {
		lep1_nstahits_branch = tree->GetBranch("lep1_nstahits");
		if (lep1_nstahits_branch) {lep1_nstahits_branch->SetAddress(&lep1_nstahits_);}
	}
	lep1_nstations_branch = 0;
	if (tree->GetBranch("lep1_nstations") != 0) {
		lep1_nstations_branch = tree->GetBranch("lep1_nstations");
		if (lep1_nstations_branch) {lep1_nstations_branch->SetAddress(&lep1_nstations_);}
	}
	lep1_chi2_branch = 0;
	if (tree->GetBranch("lep1_chi2") != 0) {
		lep1_chi2_branch = tree->GetBranch("lep1_chi2");
		if (lep1_chi2_branch) {lep1_chi2_branch->SetAddress(&lep1_chi2_);}
	}
	lep1_ndof_branch = 0;
	if (tree->GetBranch("lep1_ndof") != 0) {
		lep1_ndof_branch = tree->GetBranch("lep1_ndof");
		if (lep1_ndof_branch) {lep1_ndof_branch->SetAddress(&lep1_ndof_);}
	}
	lep1_pterr_branch = 0;
	if (tree->GetBranch("lep1_pterr") != 0) {
		lep1_pterr_branch = tree->GetBranch("lep1_pterr");
		if (lep1_pterr_branch) {lep1_pterr_branch->SetAddress(&lep1_pterr_);}
	}
	lep1_ecal_vetodep_branch = 0;
	if (tree->GetBranch("lep1_ecal_vetodep") != 0) {
		lep1_ecal_vetodep_branch = tree->GetBranch("lep1_ecal_vetodep");
		if (lep1_ecal_vetodep_branch) {lep1_ecal_vetodep_branch->SetAddress(&lep1_ecal_vetodep_);}
	}
	lep1_hcal_vetodep_branch = 0;
	if (tree->GetBranch("lep1_hcal_vetodep") != 0) {
		lep1_hcal_vetodep_branch = tree->GetBranch("lep1_hcal_vetodep");
		if (lep1_hcal_vetodep_branch) {lep1_hcal_vetodep_branch->SetAddress(&lep1_hcal_vetodep_);}
	}
	lep2_passes_id_branch = 0;
	if (tree->GetBranch("lep2_passes_id") != 0) {
		lep2_passes_id_branch = tree->GetBranch("lep2_passes_id");
		if (lep2_passes_id_branch) {lep2_passes_id_branch->SetAddress(&lep2_passes_id_);}
	}
	lep2_passes_iso_branch = 0;
	if (tree->GetBranch("lep2_passes_iso") != 0) {
		lep2_passes_iso_branch = tree->GetBranch("lep2_passes_iso");
		if (lep2_passes_iso_branch) {lep2_passes_iso_branch->SetAddress(&lep2_passes_iso_);}
	}
	lep2_is_num_branch = 0;
	if (tree->GetBranch("lep2_is_num") != 0) {
		lep2_is_num_branch = tree->GetBranch("lep2_is_num");
		if (lep2_is_num_branch) {lep2_is_num_branch->SetAddress(&lep2_is_num_);}
	}
	lep2_is_den_branch = 0;
	if (tree->GetBranch("lep2_is_den") != 0) {
		lep2_is_den_branch = tree->GetBranch("lep2_is_den");
		if (lep2_is_den_branch) {lep2_is_den_branch->SetAddress(&lep2_is_den_);}
	}
	lep2_is_fo_branch = 0;
	if (tree->GetBranch("lep2_is_fo") != 0) {
		lep2_is_fo_branch = tree->GetBranch("lep2_is_fo");
		if (lep2_is_fo_branch) {lep2_is_fo_branch->SetAddress(&lep2_is_fo_);}
	}
	lep2_is_fromw_branch = 0;
	if (tree->GetBranch("lep2_is_fromw") != 0) {
		lep2_is_fromw_branch = tree->GetBranch("lep2_is_fromw");
		if (lep2_is_fromw_branch) {lep2_is_fromw_branch->SetAddress(&lep2_is_fromw_);}
	}
	lep2_charge_branch = 0;
	if (tree->GetBranch("lep2_charge") != 0) {
		lep2_charge_branch = tree->GetBranch("lep2_charge");
		if (lep2_charge_branch) {lep2_charge_branch->SetAddress(&lep2_charge_);}
	}
	lep2_pdgid_branch = 0;
	if (tree->GetBranch("lep2_pdgid") != 0) {
		lep2_pdgid_branch = tree->GetBranch("lep2_pdgid");
		if (lep2_pdgid_branch) {lep2_pdgid_branch->SetAddress(&lep2_pdgid_);}
	}
	lep2_type_branch = 0;
	if (tree->GetBranch("lep2_type") != 0) {
		lep2_type_branch = tree->GetBranch("lep2_type");
		if (lep2_type_branch) {lep2_type_branch->SetAddress(&lep2_type_);}
	}
	lep2_d0_branch = 0;
	if (tree->GetBranch("lep2_d0") != 0) {
		lep2_d0_branch = tree->GetBranch("lep2_d0");
		if (lep2_d0_branch) {lep2_d0_branch->SetAddress(&lep2_d0_);}
	}
	lep2_d0err_branch = 0;
	if (tree->GetBranch("lep2_d0err") != 0) {
		lep2_d0err_branch = tree->GetBranch("lep2_d0err");
		if (lep2_d0err_branch) {lep2_d0err_branch->SetAddress(&lep2_d0err_);}
	}
	lep2_dz_branch = 0;
	if (tree->GetBranch("lep2_dz") != 0) {
		lep2_dz_branch = tree->GetBranch("lep2_dz");
		if (lep2_dz_branch) {lep2_dz_branch->SetAddress(&lep2_dz_);}
	}
	lep2_ip3d_branch = 0;
	if (tree->GetBranch("lep2_ip3d") != 0) {
		lep2_ip3d_branch = tree->GetBranch("lep2_ip3d");
		if (lep2_ip3d_branch) {lep2_ip3d_branch->SetAddress(&lep2_ip3d_);}
	}
	lep2_ip3derr_branch = 0;
	if (tree->GetBranch("lep2_ip3derr") != 0) {
		lep2_ip3derr_branch = tree->GetBranch("lep2_ip3derr");
		if (lep2_ip3derr_branch) {lep2_ip3derr_branch->SetAddress(&lep2_ip3derr_);}
	}
	lep2_dzerr_branch = 0;
	if (tree->GetBranch("lep2_dzerr") != 0) {
		lep2_dzerr_branch = tree->GetBranch("lep2_dzerr");
		if (lep2_dzerr_branch) {lep2_dzerr_branch->SetAddress(&lep2_dzerr_);}
	}
	lep2_mt_branch = 0;
	if (tree->GetBranch("lep2_mt") != 0) {
		lep2_mt_branch = tree->GetBranch("lep2_mt");
		if (lep2_mt_branch) {lep2_mt_branch->SetAddress(&lep2_mt_);}
	}
	lep2_corpfiso_branch = 0;
	if (tree->GetBranch("lep2_corpfiso") != 0) {
		lep2_corpfiso_branch = tree->GetBranch("lep2_corpfiso");
		if (lep2_corpfiso_branch) {lep2_corpfiso_branch->SetAddress(&lep2_corpfiso_);}
	}
	lep2_pfiso_branch = 0;
	if (tree->GetBranch("lep2_pfiso") != 0) {
		lep2_pfiso_branch = tree->GetBranch("lep2_pfiso");
		if (lep2_pfiso_branch) {lep2_pfiso_branch->SetAddress(&lep2_pfiso_);}
	}
	lep2_chiso_branch = 0;
	if (tree->GetBranch("lep2_chiso") != 0) {
		lep2_chiso_branch = tree->GetBranch("lep2_chiso");
		if (lep2_chiso_branch) {lep2_chiso_branch->SetAddress(&lep2_chiso_);}
	}
	lep2_emiso_branch = 0;
	if (tree->GetBranch("lep2_emiso") != 0) {
		lep2_emiso_branch = tree->GetBranch("lep2_emiso");
		if (lep2_emiso_branch) {lep2_emiso_branch->SetAddress(&lep2_emiso_);}
	}
	lep2_nhiso_branch = 0;
	if (tree->GetBranch("lep2_nhiso") != 0) {
		lep2_nhiso_branch = tree->GetBranch("lep2_nhiso");
		if (lep2_nhiso_branch) {lep2_nhiso_branch->SetAddress(&lep2_nhiso_);}
	}
	lep2_corpfiso04_branch = 0;
	if (tree->GetBranch("lep2_corpfiso04") != 0) {
		lep2_corpfiso04_branch = tree->GetBranch("lep2_corpfiso04");
		if (lep2_corpfiso04_branch) {lep2_corpfiso04_branch->SetAddress(&lep2_corpfiso04_);}
	}
	lep2_pfiso04_branch = 0;
	if (tree->GetBranch("lep2_pfiso04") != 0) {
		lep2_pfiso04_branch = tree->GetBranch("lep2_pfiso04");
		if (lep2_pfiso04_branch) {lep2_pfiso04_branch->SetAddress(&lep2_pfiso04_);}
	}
	lep2_chiso04_branch = 0;
	if (tree->GetBranch("lep2_chiso04") != 0) {
		lep2_chiso04_branch = tree->GetBranch("lep2_chiso04");
		if (lep2_chiso04_branch) {lep2_chiso04_branch->SetAddress(&lep2_chiso04_);}
	}
	lep2_emiso04_branch = 0;
	if (tree->GetBranch("lep2_emiso04") != 0) {
		lep2_emiso04_branch = tree->GetBranch("lep2_emiso04");
		if (lep2_emiso04_branch) {lep2_emiso04_branch->SetAddress(&lep2_emiso04_);}
	}
	lep2_nhiso04_branch = 0;
	if (tree->GetBranch("lep2_nhiso04") != 0) {
		lep2_nhiso04_branch = tree->GetBranch("lep2_nhiso04");
		if (lep2_nhiso04_branch) {lep2_nhiso04_branch->SetAddress(&lep2_nhiso04_);}
	}
	lep2_cordetiso_branch = 0;
	if (tree->GetBranch("lep2_cordetiso") != 0) {
		lep2_cordetiso_branch = tree->GetBranch("lep2_cordetiso");
		if (lep2_cordetiso_branch) {lep2_cordetiso_branch->SetAddress(&lep2_cordetiso_);}
	}
	lep2_detiso_branch = 0;
	if (tree->GetBranch("lep2_detiso") != 0) {
		lep2_detiso_branch = tree->GetBranch("lep2_detiso");
		if (lep2_detiso_branch) {lep2_detiso_branch->SetAddress(&lep2_detiso_);}
	}
	lep2_trkiso_branch = 0;
	if (tree->GetBranch("lep2_trkiso") != 0) {
		lep2_trkiso_branch = tree->GetBranch("lep2_trkiso");
		if (lep2_trkiso_branch) {lep2_trkiso_branch->SetAddress(&lep2_trkiso_);}
	}
	lep2_ecaliso_branch = 0;
	if (tree->GetBranch("lep2_ecaliso") != 0) {
		lep2_ecaliso_branch = tree->GetBranch("lep2_ecaliso");
		if (lep2_ecaliso_branch) {lep2_ecaliso_branch->SetAddress(&lep2_ecaliso_);}
	}
	lep2_hcaliso_branch = 0;
	if (tree->GetBranch("lep2_hcaliso") != 0) {
		lep2_hcaliso_branch = tree->GetBranch("lep2_hcaliso");
		if (lep2_hcaliso_branch) {lep2_hcaliso_branch->SetAddress(&lep2_hcaliso_);}
	}
	lep2_cordetiso04_branch = 0;
	if (tree->GetBranch("lep2_cordetiso04") != 0) {
		lep2_cordetiso04_branch = tree->GetBranch("lep2_cordetiso04");
		if (lep2_cordetiso04_branch) {lep2_cordetiso04_branch->SetAddress(&lep2_cordetiso04_);}
	}
	lep2_detiso04_branch = 0;
	if (tree->GetBranch("lep2_detiso04") != 0) {
		lep2_detiso04_branch = tree->GetBranch("lep2_detiso04");
		if (lep2_detiso04_branch) {lep2_detiso04_branch->SetAddress(&lep2_detiso04_);}
	}
	lep2_trkiso04_branch = 0;
	if (tree->GetBranch("lep2_trkiso04") != 0) {
		lep2_trkiso04_branch = tree->GetBranch("lep2_trkiso04");
		if (lep2_trkiso04_branch) {lep2_trkiso04_branch->SetAddress(&lep2_trkiso04_);}
	}
	lep2_ecaliso04_branch = 0;
	if (tree->GetBranch("lep2_ecaliso04") != 0) {
		lep2_ecaliso04_branch = tree->GetBranch("lep2_ecaliso04");
		if (lep2_ecaliso04_branch) {lep2_ecaliso04_branch->SetAddress(&lep2_ecaliso04_);}
	}
	lep2_hcaliso04_branch = 0;
	if (tree->GetBranch("lep2_hcaliso04") != 0) {
		lep2_hcaliso04_branch = tree->GetBranch("lep2_hcaliso04");
		if (lep2_hcaliso04_branch) {lep2_hcaliso04_branch->SetAddress(&lep2_hcaliso04_);}
	}
	lep2_effarea_branch = 0;
	if (tree->GetBranch("lep2_effarea") != 0) {
		lep2_effarea_branch = tree->GetBranch("lep2_effarea");
		if (lep2_effarea_branch) {lep2_effarea_branch->SetAddress(&lep2_effarea_);}
	}
	lep2_effarea04_branch = 0;
	if (tree->GetBranch("lep2_effarea04") != 0) {
		lep2_effarea04_branch = tree->GetBranch("lep2_effarea04");
		if (lep2_effarea04_branch) {lep2_effarea04_branch->SetAddress(&lep2_effarea04_);}
	}
	lep2_dbeta_branch = 0;
	if (tree->GetBranch("lep2_dbeta") != 0) {
		lep2_dbeta_branch = tree->GetBranch("lep2_dbeta");
		if (lep2_dbeta_branch) {lep2_dbeta_branch->SetAddress(&lep2_dbeta_);}
	}
	lep2_dbeta04_branch = 0;
	if (tree->GetBranch("lep2_dbeta04") != 0) {
		lep2_dbeta04_branch = tree->GetBranch("lep2_dbeta04");
		if (lep2_dbeta04_branch) {lep2_dbeta04_branch->SetAddress(&lep2_dbeta04_);}
	}
	lep2_sf_lepeff_branch = 0;
	if (tree->GetBranch("lep2_sf_lepeff") != 0) {
		lep2_sf_lepeff_branch = tree->GetBranch("lep2_sf_lepeff");
		if (lep2_sf_lepeff_branch) {lep2_sf_lepeff_branch->SetAddress(&lep2_sf_lepeff_);}
	}
	lep2_sf_trig_branch = 0;
	if (tree->GetBranch("lep2_sf_trig") != 0) {
		lep2_sf_trig_branch = tree->GetBranch("lep2_sf_trig");
		if (lep2_sf_trig_branch) {lep2_sf_trig_branch->SetAddress(&lep2_sf_trig_);}
	}
	lep2_mcid_branch = 0;
	if (tree->GetBranch("lep2_mcid") != 0) {
		lep2_mcid_branch = tree->GetBranch("lep2_mcid");
		if (lep2_mcid_branch) {lep2_mcid_branch->SetAddress(&lep2_mcid_);}
	}
	lep2_mc3id_branch = 0;
	if (tree->GetBranch("lep2_mc3id") != 0) {
		lep2_mc3id_branch = tree->GetBranch("lep2_mc3id");
		if (lep2_mc3id_branch) {lep2_mc3id_branch->SetAddress(&lep2_mc3id_);}
	}
	lep2_momid_branch = 0;
	if (tree->GetBranch("lep2_momid") != 0) {
		lep2_momid_branch = tree->GetBranch("lep2_momid");
		if (lep2_momid_branch) {lep2_momid_branch->SetAddress(&lep2_momid_);}
	}
	lep2_mc3_momid_branch = 0;
	if (tree->GetBranch("lep2_mc3_momid") != 0) {
		lep2_mc3_momid_branch = tree->GetBranch("lep2_mc3_momid");
		if (lep2_mc3_momid_branch) {lep2_mc3_momid_branch->SetAddress(&lep2_mc3_momid_);}
	}
	lep2_q3agree_branch = 0;
	if (tree->GetBranch("lep2_q3agree") != 0) {
		lep2_q3agree_branch = tree->GetBranch("lep2_q3agree");
		if (lep2_q3agree_branch) {lep2_q3agree_branch->SetAddress(&lep2_q3agree_);}
	}
	lep2_is_conv_branch = 0;
	if (tree->GetBranch("lep2_is_conv") != 0) {
		lep2_is_conv_branch = tree->GetBranch("lep2_is_conv");
		if (lep2_is_conv_branch) {lep2_is_conv_branch->SetAddress(&lep2_is_conv_);}
	}
	lep2_qsc_branch = 0;
	if (tree->GetBranch("lep2_qsc") != 0) {
		lep2_qsc_branch = tree->GetBranch("lep2_qsc");
		if (lep2_qsc_branch) {lep2_qsc_branch->SetAddress(&lep2_qsc_);}
	}
	lep2_qctf_branch = 0;
	if (tree->GetBranch("lep2_qctf") != 0) {
		lep2_qctf_branch = tree->GetBranch("lep2_qctf");
		if (lep2_qctf_branch) {lep2_qctf_branch->SetAddress(&lep2_qctf_);}
	}
	lep2_qgsf_branch = 0;
	if (tree->GetBranch("lep2_qgsf") != 0) {
		lep2_qgsf_branch = tree->GetBranch("lep2_qgsf");
		if (lep2_qgsf_branch) {lep2_qgsf_branch->SetAddress(&lep2_qgsf_);}
	}
	lep2_nmhits_branch = 0;
	if (tree->GetBranch("lep2_nmhits") != 0) {
		lep2_nmhits_branch = tree->GetBranch("lep2_nmhits");
		if (lep2_nmhits_branch) {lep2_nmhits_branch->SetAddress(&lep2_nmhits_);}
	}
	lep2_eleid_veto_branch = 0;
	if (tree->GetBranch("lep2_eleid_veto") != 0) {
		lep2_eleid_veto_branch = tree->GetBranch("lep2_eleid_veto");
		if (lep2_eleid_veto_branch) {lep2_eleid_veto_branch->SetAddress(&lep2_eleid_veto_);}
	}
	lep2_eleid_loose_branch = 0;
	if (tree->GetBranch("lep2_eleid_loose") != 0) {
		lep2_eleid_loose_branch = tree->GetBranch("lep2_eleid_loose");
		if (lep2_eleid_loose_branch) {lep2_eleid_loose_branch->SetAddress(&lep2_eleid_loose_);}
	}
	lep2_eleid_medium_branch = 0;
	if (tree->GetBranch("lep2_eleid_medium") != 0) {
		lep2_eleid_medium_branch = tree->GetBranch("lep2_eleid_medium");
		if (lep2_eleid_medium_branch) {lep2_eleid_medium_branch->SetAddress(&lep2_eleid_medium_);}
	}
	lep2_eleid_tight_branch = 0;
	if (tree->GetBranch("lep2_eleid_tight") != 0) {
		lep2_eleid_tight_branch = tree->GetBranch("lep2_eleid_tight");
		if (lep2_eleid_tight_branch) {lep2_eleid_tight_branch->SetAddress(&lep2_eleid_tight_);}
	}
	lep2_dphiin_branch = 0;
	if (tree->GetBranch("lep2_dphiin") != 0) {
		lep2_dphiin_branch = tree->GetBranch("lep2_dphiin");
		if (lep2_dphiin_branch) {lep2_dphiin_branch->SetAddress(&lep2_dphiin_);}
	}
	lep2_detain_branch = 0;
	if (tree->GetBranch("lep2_detain") != 0) {
		lep2_detain_branch = tree->GetBranch("lep2_detain");
		if (lep2_detain_branch) {lep2_detain_branch->SetAddress(&lep2_detain_);}
	}
	lep2_sieie_branch = 0;
	if (tree->GetBranch("lep2_sieie") != 0) {
		lep2_sieie_branch = tree->GetBranch("lep2_sieie");
		if (lep2_sieie_branch) {lep2_sieie_branch->SetAddress(&lep2_sieie_);}
	}
	lep2_hoe_branch = 0;
	if (tree->GetBranch("lep2_hoe") != 0) {
		lep2_hoe_branch = tree->GetBranch("lep2_hoe");
		if (lep2_hoe_branch) {lep2_hoe_branch->SetAddress(&lep2_hoe_);}
	}
	lep2_ooemoop_branch = 0;
	if (tree->GetBranch("lep2_ooemoop") != 0) {
		lep2_ooemoop_branch = tree->GetBranch("lep2_ooemoop");
		if (lep2_ooemoop_branch) {lep2_ooemoop_branch->SetAddress(&lep2_ooemoop_);}
	}
	lep2_conv_dist_branch = 0;
	if (tree->GetBranch("lep2_conv_dist") != 0) {
		lep2_conv_dist_branch = tree->GetBranch("lep2_conv_dist");
		if (lep2_conv_dist_branch) {lep2_conv_dist_branch->SetAddress(&lep2_conv_dist_);}
	}
	lep2_conv_dcot_branch = 0;
	if (tree->GetBranch("lep2_conv_dcot") != 0) {
		lep2_conv_dcot_branch = tree->GetBranch("lep2_conv_dcot");
		if (lep2_conv_dcot_branch) {lep2_conv_dcot_branch->SetAddress(&lep2_conv_dcot_);}
	}
	lep2_is_global_branch = 0;
	if (tree->GetBranch("lep2_is_global") != 0) {
		lep2_is_global_branch = tree->GetBranch("lep2_is_global");
		if (lep2_is_global_branch) {lep2_is_global_branch->SetAddress(&lep2_is_global_);}
	}
	lep2_is_tracker_branch = 0;
	if (tree->GetBranch("lep2_is_tracker") != 0) {
		lep2_is_tracker_branch = tree->GetBranch("lep2_is_tracker");
		if (lep2_is_tracker_branch) {lep2_is_tracker_branch->SetAddress(&lep2_is_tracker_);}
	}
	lep2_is_stamu_branch = 0;
	if (tree->GetBranch("lep2_is_stamu") != 0) {
		lep2_is_stamu_branch = tree->GetBranch("lep2_is_stamu");
		if (lep2_is_stamu_branch) {lep2_is_stamu_branch->SetAddress(&lep2_is_stamu_);}
	}
	lep2_is_pfmu_branch = 0;
	if (tree->GetBranch("lep2_is_pfmu") != 0) {
		lep2_is_pfmu_branch = tree->GetBranch("lep2_is_pfmu");
		if (lep2_is_pfmu_branch) {lep2_is_pfmu_branch->SetAddress(&lep2_is_pfmu_);}
	}
	lep2_is_loosemu_branch = 0;
	if (tree->GetBranch("lep2_is_loosemu") != 0) {
		lep2_is_loosemu_branch = tree->GetBranch("lep2_is_loosemu");
		if (lep2_is_loosemu_branch) {lep2_is_loosemu_branch->SetAddress(&lep2_is_loosemu_);}
	}
	lep2_is_tightmu_branch = 0;
	if (tree->GetBranch("lep2_is_tightmu") != 0) {
		lep2_is_tightmu_branch = tree->GetBranch("lep2_is_tightmu");
		if (lep2_is_tightmu_branch) {lep2_is_tightmu_branch->SetAddress(&lep2_is_tightmu_);}
	}
	lep2_npixelhits_branch = 0;
	if (tree->GetBranch("lep2_npixelhits") != 0) {
		lep2_npixelhits_branch = tree->GetBranch("lep2_npixelhits");
		if (lep2_npixelhits_branch) {lep2_npixelhits_branch->SetAddress(&lep2_npixelhits_);}
	}
	lep2_nsihits_branch = 0;
	if (tree->GetBranch("lep2_nsihits") != 0) {
		lep2_nsihits_branch = tree->GetBranch("lep2_nsihits");
		if (lep2_nsihits_branch) {lep2_nsihits_branch->SetAddress(&lep2_nsihits_);}
	}
	lep2_nsilayers_branch = 0;
	if (tree->GetBranch("lep2_nsilayers") != 0) {
		lep2_nsilayers_branch = tree->GetBranch("lep2_nsilayers");
		if (lep2_nsilayers_branch) {lep2_nsilayers_branch->SetAddress(&lep2_nsilayers_);}
	}
	lep2_nstahits_branch = 0;
	if (tree->GetBranch("lep2_nstahits") != 0) {
		lep2_nstahits_branch = tree->GetBranch("lep2_nstahits");
		if (lep2_nstahits_branch) {lep2_nstahits_branch->SetAddress(&lep2_nstahits_);}
	}
	lep2_nstations_branch = 0;
	if (tree->GetBranch("lep2_nstations") != 0) {
		lep2_nstations_branch = tree->GetBranch("lep2_nstations");
		if (lep2_nstations_branch) {lep2_nstations_branch->SetAddress(&lep2_nstations_);}
	}
	lep2_chi2_branch = 0;
	if (tree->GetBranch("lep2_chi2") != 0) {
		lep2_chi2_branch = tree->GetBranch("lep2_chi2");
		if (lep2_chi2_branch) {lep2_chi2_branch->SetAddress(&lep2_chi2_);}
	}
	lep2_ndof_branch = 0;
	if (tree->GetBranch("lep2_ndof") != 0) {
		lep2_ndof_branch = tree->GetBranch("lep2_ndof");
		if (lep2_ndof_branch) {lep2_ndof_branch->SetAddress(&lep2_ndof_);}
	}
	lep2_pterr_branch = 0;
	if (tree->GetBranch("lep2_pterr") != 0) {
		lep2_pterr_branch = tree->GetBranch("lep2_pterr");
		if (lep2_pterr_branch) {lep2_pterr_branch->SetAddress(&lep2_pterr_);}
	}
	lep2_ecal_vetodep_branch = 0;
	if (tree->GetBranch("lep2_ecal_vetodep") != 0) {
		lep2_ecal_vetodep_branch = tree->GetBranch("lep2_ecal_vetodep");
		if (lep2_ecal_vetodep_branch) {lep2_ecal_vetodep_branch->SetAddress(&lep2_ecal_vetodep_);}
	}
	lep2_hcal_vetodep_branch = 0;
	if (tree->GetBranch("lep2_hcal_vetodep") != 0) {
		lep2_hcal_vetodep_branch = tree->GetBranch("lep2_hcal_vetodep");
		if (lep2_hcal_vetodep_branch) {lep2_hcal_vetodep_branch->SetAddress(&lep2_hcal_vetodep_);}
	}
	os_branch = 0;
	if (tree->GetBranch("os") != 0) {
		os_branch = tree->GetBranch("os");
		if (os_branch) {os_branch->SetAddress(&os_);}
	}
	ss_branch = 0;
	if (tree->GetBranch("ss") != 0) {
		ss_branch = tree->GetBranch("ss");
		if (ss_branch) {ss_branch->SetAddress(&ss_);}
	}
	mm_branch = 0;
	if (tree->GetBranch("mm") != 0) {
		mm_branch = tree->GetBranch("mm");
		if (mm_branch) {mm_branch->SetAddress(&mm_);}
	}
	ee_branch = 0;
	if (tree->GetBranch("ee") != 0) {
		ee_branch = tree->GetBranch("ee");
		if (ee_branch) {ee_branch->SetAddress(&ee_);}
	}
	em_branch = 0;
	if (tree->GetBranch("em") != 0) {
		em_branch = tree->GetBranch("em");
		if (em_branch) {em_branch->SetAddress(&em_);}
	}
	dilep_type_branch = 0;
	if (tree->GetBranch("dilep_type") != 0) {
		dilep_type_branch = tree->GetBranch("dilep_type");
		if (dilep_type_branch) {dilep_type_branch->SetAddress(&dilep_type_);}
	}
	dilep_gen_type_branch = 0;
	if (tree->GetBranch("dilep_gen_type") != 0) {
		dilep_gen_type_branch = tree->GetBranch("dilep_gen_type");
		if (dilep_gen_type_branch) {dilep_gen_type_branch->SetAddress(&dilep_gen_type_);}
	}
	dilep_mass_branch = 0;
	if (tree->GetBranch("dilep_mass") != 0) {
		dilep_mass_branch = tree->GetBranch("dilep_mass");
		if (dilep_mass_branch) {dilep_mass_branch->SetAddress(&dilep_mass_);}
	}
	dilep_dphi_branch = 0;
	if (tree->GetBranch("dilep_dphi") != 0) {
		dilep_dphi_branch = tree->GetBranch("dilep_dphi");
		if (dilep_dphi_branch) {dilep_dphi_branch->SetAddress(&dilep_dphi_);}
	}
	dilep_deta_branch = 0;
	if (tree->GetBranch("dilep_deta") != 0) {
		dilep_deta_branch = tree->GetBranch("dilep_deta");
		if (dilep_deta_branch) {dilep_deta_branch->SetAddress(&dilep_deta_);}
	}
	dilep_dr_branch = 0;
	if (tree->GetBranch("dilep_dr") != 0) {
		dilep_dr_branch = tree->GetBranch("dilep_dr");
		if (dilep_dr_branch) {dilep_dr_branch->SetAddress(&dilep_dr_);}
	}
	fiduciality_branch = 0;
	if (tree->GetBranch("fiduciality") != 0) {
		fiduciality_branch = tree->GetBranch("fiduciality");
		if (fiduciality_branch) {fiduciality_branch->SetAddress(&fiduciality_);}
	}
	lep3_passes_id_branch = 0;
	if (tree->GetBranch("lep3_passes_id") != 0) {
		lep3_passes_id_branch = tree->GetBranch("lep3_passes_id");
		if (lep3_passes_id_branch) {lep3_passes_id_branch->SetAddress(&lep3_passes_id_);}
	}
	lep3_passes_iso_branch = 0;
	if (tree->GetBranch("lep3_passes_iso") != 0) {
		lep3_passes_iso_branch = tree->GetBranch("lep3_passes_iso");
		if (lep3_passes_iso_branch) {lep3_passes_iso_branch->SetAddress(&lep3_passes_iso_);}
	}
	lep3_is_num_branch = 0;
	if (tree->GetBranch("lep3_is_num") != 0) {
		lep3_is_num_branch = tree->GetBranch("lep3_is_num");
		if (lep3_is_num_branch) {lep3_is_num_branch->SetAddress(&lep3_is_num_);}
	}
	lep3_is_den_branch = 0;
	if (tree->GetBranch("lep3_is_den") != 0) {
		lep3_is_den_branch = tree->GetBranch("lep3_is_den");
		if (lep3_is_den_branch) {lep3_is_den_branch->SetAddress(&lep3_is_den_);}
	}
	lep3_is_fo_branch = 0;
	if (tree->GetBranch("lep3_is_fo") != 0) {
		lep3_is_fo_branch = tree->GetBranch("lep3_is_fo");
		if (lep3_is_fo_branch) {lep3_is_fo_branch->SetAddress(&lep3_is_fo_);}
	}
	lep3_is_fromw_branch = 0;
	if (tree->GetBranch("lep3_is_fromw") != 0) {
		lep3_is_fromw_branch = tree->GetBranch("lep3_is_fromw");
		if (lep3_is_fromw_branch) {lep3_is_fromw_branch->SetAddress(&lep3_is_fromw_);}
	}
	lep3_charge_branch = 0;
	if (tree->GetBranch("lep3_charge") != 0) {
		lep3_charge_branch = tree->GetBranch("lep3_charge");
		if (lep3_charge_branch) {lep3_charge_branch->SetAddress(&lep3_charge_);}
	}
	lep3_pdgid_branch = 0;
	if (tree->GetBranch("lep3_pdgid") != 0) {
		lep3_pdgid_branch = tree->GetBranch("lep3_pdgid");
		if (lep3_pdgid_branch) {lep3_pdgid_branch->SetAddress(&lep3_pdgid_);}
	}
	lep3_type_branch = 0;
	if (tree->GetBranch("lep3_type") != 0) {
		lep3_type_branch = tree->GetBranch("lep3_type");
		if (lep3_type_branch) {lep3_type_branch->SetAddress(&lep3_type_);}
	}
	lep3_d0_branch = 0;
	if (tree->GetBranch("lep3_d0") != 0) {
		lep3_d0_branch = tree->GetBranch("lep3_d0");
		if (lep3_d0_branch) {lep3_d0_branch->SetAddress(&lep3_d0_);}
	}
	lep3_d0err_branch = 0;
	if (tree->GetBranch("lep3_d0err") != 0) {
		lep3_d0err_branch = tree->GetBranch("lep3_d0err");
		if (lep3_d0err_branch) {lep3_d0err_branch->SetAddress(&lep3_d0err_);}
	}
	lep3_dz_branch = 0;
	if (tree->GetBranch("lep3_dz") != 0) {
		lep3_dz_branch = tree->GetBranch("lep3_dz");
		if (lep3_dz_branch) {lep3_dz_branch->SetAddress(&lep3_dz_);}
	}
	lep3_ip3d_branch = 0;
	if (tree->GetBranch("lep3_ip3d") != 0) {
		lep3_ip3d_branch = tree->GetBranch("lep3_ip3d");
		if (lep3_ip3d_branch) {lep3_ip3d_branch->SetAddress(&lep3_ip3d_);}
	}
	lep3_ip3derr_branch = 0;
	if (tree->GetBranch("lep3_ip3derr") != 0) {
		lep3_ip3derr_branch = tree->GetBranch("lep3_ip3derr");
		if (lep3_ip3derr_branch) {lep3_ip3derr_branch->SetAddress(&lep3_ip3derr_);}
	}
	lep3_dzerr_branch = 0;
	if (tree->GetBranch("lep3_dzerr") != 0) {
		lep3_dzerr_branch = tree->GetBranch("lep3_dzerr");
		if (lep3_dzerr_branch) {lep3_dzerr_branch->SetAddress(&lep3_dzerr_);}
	}
	lep3_mt_branch = 0;
	if (tree->GetBranch("lep3_mt") != 0) {
		lep3_mt_branch = tree->GetBranch("lep3_mt");
		if (lep3_mt_branch) {lep3_mt_branch->SetAddress(&lep3_mt_);}
	}
	lep3_corpfiso_branch = 0;
	if (tree->GetBranch("lep3_corpfiso") != 0) {
		lep3_corpfiso_branch = tree->GetBranch("lep3_corpfiso");
		if (lep3_corpfiso_branch) {lep3_corpfiso_branch->SetAddress(&lep3_corpfiso_);}
	}
	lep3_pfiso_branch = 0;
	if (tree->GetBranch("lep3_pfiso") != 0) {
		lep3_pfiso_branch = tree->GetBranch("lep3_pfiso");
		if (lep3_pfiso_branch) {lep3_pfiso_branch->SetAddress(&lep3_pfiso_);}
	}
	lep3_chiso_branch = 0;
	if (tree->GetBranch("lep3_chiso") != 0) {
		lep3_chiso_branch = tree->GetBranch("lep3_chiso");
		if (lep3_chiso_branch) {lep3_chiso_branch->SetAddress(&lep3_chiso_);}
	}
	lep3_emiso_branch = 0;
	if (tree->GetBranch("lep3_emiso") != 0) {
		lep3_emiso_branch = tree->GetBranch("lep3_emiso");
		if (lep3_emiso_branch) {lep3_emiso_branch->SetAddress(&lep3_emiso_);}
	}
	lep3_nhiso_branch = 0;
	if (tree->GetBranch("lep3_nhiso") != 0) {
		lep3_nhiso_branch = tree->GetBranch("lep3_nhiso");
		if (lep3_nhiso_branch) {lep3_nhiso_branch->SetAddress(&lep3_nhiso_);}
	}
	lep3_corpfiso04_branch = 0;
	if (tree->GetBranch("lep3_corpfiso04") != 0) {
		lep3_corpfiso04_branch = tree->GetBranch("lep3_corpfiso04");
		if (lep3_corpfiso04_branch) {lep3_corpfiso04_branch->SetAddress(&lep3_corpfiso04_);}
	}
	lep3_pfiso04_branch = 0;
	if (tree->GetBranch("lep3_pfiso04") != 0) {
		lep3_pfiso04_branch = tree->GetBranch("lep3_pfiso04");
		if (lep3_pfiso04_branch) {lep3_pfiso04_branch->SetAddress(&lep3_pfiso04_);}
	}
	lep3_chiso04_branch = 0;
	if (tree->GetBranch("lep3_chiso04") != 0) {
		lep3_chiso04_branch = tree->GetBranch("lep3_chiso04");
		if (lep3_chiso04_branch) {lep3_chiso04_branch->SetAddress(&lep3_chiso04_);}
	}
	lep3_emiso04_branch = 0;
	if (tree->GetBranch("lep3_emiso04") != 0) {
		lep3_emiso04_branch = tree->GetBranch("lep3_emiso04");
		if (lep3_emiso04_branch) {lep3_emiso04_branch->SetAddress(&lep3_emiso04_);}
	}
	lep3_nhiso04_branch = 0;
	if (tree->GetBranch("lep3_nhiso04") != 0) {
		lep3_nhiso04_branch = tree->GetBranch("lep3_nhiso04");
		if (lep3_nhiso04_branch) {lep3_nhiso04_branch->SetAddress(&lep3_nhiso04_);}
	}
	lep3_cordetiso_branch = 0;
	if (tree->GetBranch("lep3_cordetiso") != 0) {
		lep3_cordetiso_branch = tree->GetBranch("lep3_cordetiso");
		if (lep3_cordetiso_branch) {lep3_cordetiso_branch->SetAddress(&lep3_cordetiso_);}
	}
	lep3_detiso_branch = 0;
	if (tree->GetBranch("lep3_detiso") != 0) {
		lep3_detiso_branch = tree->GetBranch("lep3_detiso");
		if (lep3_detiso_branch) {lep3_detiso_branch->SetAddress(&lep3_detiso_);}
	}
	lep3_trkiso_branch = 0;
	if (tree->GetBranch("lep3_trkiso") != 0) {
		lep3_trkiso_branch = tree->GetBranch("lep3_trkiso");
		if (lep3_trkiso_branch) {lep3_trkiso_branch->SetAddress(&lep3_trkiso_);}
	}
	lep3_ecaliso_branch = 0;
	if (tree->GetBranch("lep3_ecaliso") != 0) {
		lep3_ecaliso_branch = tree->GetBranch("lep3_ecaliso");
		if (lep3_ecaliso_branch) {lep3_ecaliso_branch->SetAddress(&lep3_ecaliso_);}
	}
	lep3_hcaliso_branch = 0;
	if (tree->GetBranch("lep3_hcaliso") != 0) {
		lep3_hcaliso_branch = tree->GetBranch("lep3_hcaliso");
		if (lep3_hcaliso_branch) {lep3_hcaliso_branch->SetAddress(&lep3_hcaliso_);}
	}
	lep3_cordetiso04_branch = 0;
	if (tree->GetBranch("lep3_cordetiso04") != 0) {
		lep3_cordetiso04_branch = tree->GetBranch("lep3_cordetiso04");
		if (lep3_cordetiso04_branch) {lep3_cordetiso04_branch->SetAddress(&lep3_cordetiso04_);}
	}
	lep3_detiso04_branch = 0;
	if (tree->GetBranch("lep3_detiso04") != 0) {
		lep3_detiso04_branch = tree->GetBranch("lep3_detiso04");
		if (lep3_detiso04_branch) {lep3_detiso04_branch->SetAddress(&lep3_detiso04_);}
	}
	lep3_trkiso04_branch = 0;
	if (tree->GetBranch("lep3_trkiso04") != 0) {
		lep3_trkiso04_branch = tree->GetBranch("lep3_trkiso04");
		if (lep3_trkiso04_branch) {lep3_trkiso04_branch->SetAddress(&lep3_trkiso04_);}
	}
	lep3_ecaliso04_branch = 0;
	if (tree->GetBranch("lep3_ecaliso04") != 0) {
		lep3_ecaliso04_branch = tree->GetBranch("lep3_ecaliso04");
		if (lep3_ecaliso04_branch) {lep3_ecaliso04_branch->SetAddress(&lep3_ecaliso04_);}
	}
	lep3_hcaliso04_branch = 0;
	if (tree->GetBranch("lep3_hcaliso04") != 0) {
		lep3_hcaliso04_branch = tree->GetBranch("lep3_hcaliso04");
		if (lep3_hcaliso04_branch) {lep3_hcaliso04_branch->SetAddress(&lep3_hcaliso04_);}
	}
	lep3_effarea_branch = 0;
	if (tree->GetBranch("lep3_effarea") != 0) {
		lep3_effarea_branch = tree->GetBranch("lep3_effarea");
		if (lep3_effarea_branch) {lep3_effarea_branch->SetAddress(&lep3_effarea_);}
	}
	lep3_effarea04_branch = 0;
	if (tree->GetBranch("lep3_effarea04") != 0) {
		lep3_effarea04_branch = tree->GetBranch("lep3_effarea04");
		if (lep3_effarea04_branch) {lep3_effarea04_branch->SetAddress(&lep3_effarea04_);}
	}
	lep3_dbeta_branch = 0;
	if (tree->GetBranch("lep3_dbeta") != 0) {
		lep3_dbeta_branch = tree->GetBranch("lep3_dbeta");
		if (lep3_dbeta_branch) {lep3_dbeta_branch->SetAddress(&lep3_dbeta_);}
	}
	lep3_dbeta04_branch = 0;
	if (tree->GetBranch("lep3_dbeta04") != 0) {
		lep3_dbeta04_branch = tree->GetBranch("lep3_dbeta04");
		if (lep3_dbeta04_branch) {lep3_dbeta04_branch->SetAddress(&lep3_dbeta04_);}
	}
	lep3_sf_lepeff_branch = 0;
	if (tree->GetBranch("lep3_sf_lepeff") != 0) {
		lep3_sf_lepeff_branch = tree->GetBranch("lep3_sf_lepeff");
		if (lep3_sf_lepeff_branch) {lep3_sf_lepeff_branch->SetAddress(&lep3_sf_lepeff_);}
	}
	lep3_sf_trig_branch = 0;
	if (tree->GetBranch("lep3_sf_trig") != 0) {
		lep3_sf_trig_branch = tree->GetBranch("lep3_sf_trig");
		if (lep3_sf_trig_branch) {lep3_sf_trig_branch->SetAddress(&lep3_sf_trig_);}
	}
	lep3_mcid_branch = 0;
	if (tree->GetBranch("lep3_mcid") != 0) {
		lep3_mcid_branch = tree->GetBranch("lep3_mcid");
		if (lep3_mcid_branch) {lep3_mcid_branch->SetAddress(&lep3_mcid_);}
	}
	lep3_mc3id_branch = 0;
	if (tree->GetBranch("lep3_mc3id") != 0) {
		lep3_mc3id_branch = tree->GetBranch("lep3_mc3id");
		if (lep3_mc3id_branch) {lep3_mc3id_branch->SetAddress(&lep3_mc3id_);}
	}
	lep3_momid_branch = 0;
	if (tree->GetBranch("lep3_momid") != 0) {
		lep3_momid_branch = tree->GetBranch("lep3_momid");
		if (lep3_momid_branch) {lep3_momid_branch->SetAddress(&lep3_momid_);}
	}
	lep3_mc3_momid_branch = 0;
	if (tree->GetBranch("lep3_mc3_momid") != 0) {
		lep3_mc3_momid_branch = tree->GetBranch("lep3_mc3_momid");
		if (lep3_mc3_momid_branch) {lep3_mc3_momid_branch->SetAddress(&lep3_mc3_momid_);}
	}
	lep3_q3agree_branch = 0;
	if (tree->GetBranch("lep3_q3agree") != 0) {
		lep3_q3agree_branch = tree->GetBranch("lep3_q3agree");
		if (lep3_q3agree_branch) {lep3_q3agree_branch->SetAddress(&lep3_q3agree_);}
	}
	lep3_is_conv_branch = 0;
	if (tree->GetBranch("lep3_is_conv") != 0) {
		lep3_is_conv_branch = tree->GetBranch("lep3_is_conv");
		if (lep3_is_conv_branch) {lep3_is_conv_branch->SetAddress(&lep3_is_conv_);}
	}
	lep3_qsc_branch = 0;
	if (tree->GetBranch("lep3_qsc") != 0) {
		lep3_qsc_branch = tree->GetBranch("lep3_qsc");
		if (lep3_qsc_branch) {lep3_qsc_branch->SetAddress(&lep3_qsc_);}
	}
	lep3_qctf_branch = 0;
	if (tree->GetBranch("lep3_qctf") != 0) {
		lep3_qctf_branch = tree->GetBranch("lep3_qctf");
		if (lep3_qctf_branch) {lep3_qctf_branch->SetAddress(&lep3_qctf_);}
	}
	lep3_qgsf_branch = 0;
	if (tree->GetBranch("lep3_qgsf") != 0) {
		lep3_qgsf_branch = tree->GetBranch("lep3_qgsf");
		if (lep3_qgsf_branch) {lep3_qgsf_branch->SetAddress(&lep3_qgsf_);}
	}
	lep3_nmhits_branch = 0;
	if (tree->GetBranch("lep3_nmhits") != 0) {
		lep3_nmhits_branch = tree->GetBranch("lep3_nmhits");
		if (lep3_nmhits_branch) {lep3_nmhits_branch->SetAddress(&lep3_nmhits_);}
	}
	lep3_eleid_veto_branch = 0;
	if (tree->GetBranch("lep3_eleid_veto") != 0) {
		lep3_eleid_veto_branch = tree->GetBranch("lep3_eleid_veto");
		if (lep3_eleid_veto_branch) {lep3_eleid_veto_branch->SetAddress(&lep3_eleid_veto_);}
	}
	lep3_eleid_loose_branch = 0;
	if (tree->GetBranch("lep3_eleid_loose") != 0) {
		lep3_eleid_loose_branch = tree->GetBranch("lep3_eleid_loose");
		if (lep3_eleid_loose_branch) {lep3_eleid_loose_branch->SetAddress(&lep3_eleid_loose_);}
	}
	lep3_eleid_medium_branch = 0;
	if (tree->GetBranch("lep3_eleid_medium") != 0) {
		lep3_eleid_medium_branch = tree->GetBranch("lep3_eleid_medium");
		if (lep3_eleid_medium_branch) {lep3_eleid_medium_branch->SetAddress(&lep3_eleid_medium_);}
	}
	lep3_eleid_tight_branch = 0;
	if (tree->GetBranch("lep3_eleid_tight") != 0) {
		lep3_eleid_tight_branch = tree->GetBranch("lep3_eleid_tight");
		if (lep3_eleid_tight_branch) {lep3_eleid_tight_branch->SetAddress(&lep3_eleid_tight_);}
	}
	lep3_dphiin_branch = 0;
	if (tree->GetBranch("lep3_dphiin") != 0) {
		lep3_dphiin_branch = tree->GetBranch("lep3_dphiin");
		if (lep3_dphiin_branch) {lep3_dphiin_branch->SetAddress(&lep3_dphiin_);}
	}
	lep3_detain_branch = 0;
	if (tree->GetBranch("lep3_detain") != 0) {
		lep3_detain_branch = tree->GetBranch("lep3_detain");
		if (lep3_detain_branch) {lep3_detain_branch->SetAddress(&lep3_detain_);}
	}
	lep3_sieie_branch = 0;
	if (tree->GetBranch("lep3_sieie") != 0) {
		lep3_sieie_branch = tree->GetBranch("lep3_sieie");
		if (lep3_sieie_branch) {lep3_sieie_branch->SetAddress(&lep3_sieie_);}
	}
	lep3_hoe_branch = 0;
	if (tree->GetBranch("lep3_hoe") != 0) {
		lep3_hoe_branch = tree->GetBranch("lep3_hoe");
		if (lep3_hoe_branch) {lep3_hoe_branch->SetAddress(&lep3_hoe_);}
	}
	lep3_ooemoop_branch = 0;
	if (tree->GetBranch("lep3_ooemoop") != 0) {
		lep3_ooemoop_branch = tree->GetBranch("lep3_ooemoop");
		if (lep3_ooemoop_branch) {lep3_ooemoop_branch->SetAddress(&lep3_ooemoop_);}
	}
	lep3_conv_dist_branch = 0;
	if (tree->GetBranch("lep3_conv_dist") != 0) {
		lep3_conv_dist_branch = tree->GetBranch("lep3_conv_dist");
		if (lep3_conv_dist_branch) {lep3_conv_dist_branch->SetAddress(&lep3_conv_dist_);}
	}
	lep3_conv_dcot_branch = 0;
	if (tree->GetBranch("lep3_conv_dcot") != 0) {
		lep3_conv_dcot_branch = tree->GetBranch("lep3_conv_dcot");
		if (lep3_conv_dcot_branch) {lep3_conv_dcot_branch->SetAddress(&lep3_conv_dcot_);}
	}
	lep3_is_global_branch = 0;
	if (tree->GetBranch("lep3_is_global") != 0) {
		lep3_is_global_branch = tree->GetBranch("lep3_is_global");
		if (lep3_is_global_branch) {lep3_is_global_branch->SetAddress(&lep3_is_global_);}
	}
	lep3_is_tracker_branch = 0;
	if (tree->GetBranch("lep3_is_tracker") != 0) {
		lep3_is_tracker_branch = tree->GetBranch("lep3_is_tracker");
		if (lep3_is_tracker_branch) {lep3_is_tracker_branch->SetAddress(&lep3_is_tracker_);}
	}
	lep3_is_stamu_branch = 0;
	if (tree->GetBranch("lep3_is_stamu") != 0) {
		lep3_is_stamu_branch = tree->GetBranch("lep3_is_stamu");
		if (lep3_is_stamu_branch) {lep3_is_stamu_branch->SetAddress(&lep3_is_stamu_);}
	}
	lep3_is_pfmu_branch = 0;
	if (tree->GetBranch("lep3_is_pfmu") != 0) {
		lep3_is_pfmu_branch = tree->GetBranch("lep3_is_pfmu");
		if (lep3_is_pfmu_branch) {lep3_is_pfmu_branch->SetAddress(&lep3_is_pfmu_);}
	}
	lep3_is_loosemu_branch = 0;
	if (tree->GetBranch("lep3_is_loosemu") != 0) {
		lep3_is_loosemu_branch = tree->GetBranch("lep3_is_loosemu");
		if (lep3_is_loosemu_branch) {lep3_is_loosemu_branch->SetAddress(&lep3_is_loosemu_);}
	}
	lep3_is_tightmu_branch = 0;
	if (tree->GetBranch("lep3_is_tightmu") != 0) {
		lep3_is_tightmu_branch = tree->GetBranch("lep3_is_tightmu");
		if (lep3_is_tightmu_branch) {lep3_is_tightmu_branch->SetAddress(&lep3_is_tightmu_);}
	}
	lep3_npixelhits_branch = 0;
	if (tree->GetBranch("lep3_npixelhits") != 0) {
		lep3_npixelhits_branch = tree->GetBranch("lep3_npixelhits");
		if (lep3_npixelhits_branch) {lep3_npixelhits_branch->SetAddress(&lep3_npixelhits_);}
	}
	lep3_nsihits_branch = 0;
	if (tree->GetBranch("lep3_nsihits") != 0) {
		lep3_nsihits_branch = tree->GetBranch("lep3_nsihits");
		if (lep3_nsihits_branch) {lep3_nsihits_branch->SetAddress(&lep3_nsihits_);}
	}
	lep3_nsilayers_branch = 0;
	if (tree->GetBranch("lep3_nsilayers") != 0) {
		lep3_nsilayers_branch = tree->GetBranch("lep3_nsilayers");
		if (lep3_nsilayers_branch) {lep3_nsilayers_branch->SetAddress(&lep3_nsilayers_);}
	}
	lep3_nstahits_branch = 0;
	if (tree->GetBranch("lep3_nstahits") != 0) {
		lep3_nstahits_branch = tree->GetBranch("lep3_nstahits");
		if (lep3_nstahits_branch) {lep3_nstahits_branch->SetAddress(&lep3_nstahits_);}
	}
	lep3_nstations_branch = 0;
	if (tree->GetBranch("lep3_nstations") != 0) {
		lep3_nstations_branch = tree->GetBranch("lep3_nstations");
		if (lep3_nstations_branch) {lep3_nstations_branch->SetAddress(&lep3_nstations_);}
	}
	lep3_chi2_branch = 0;
	if (tree->GetBranch("lep3_chi2") != 0) {
		lep3_chi2_branch = tree->GetBranch("lep3_chi2");
		if (lep3_chi2_branch) {lep3_chi2_branch->SetAddress(&lep3_chi2_);}
	}
	lep3_ndof_branch = 0;
	if (tree->GetBranch("lep3_ndof") != 0) {
		lep3_ndof_branch = tree->GetBranch("lep3_ndof");
		if (lep3_ndof_branch) {lep3_ndof_branch->SetAddress(&lep3_ndof_);}
	}
	lep3_pterr_branch = 0;
	if (tree->GetBranch("lep3_pterr") != 0) {
		lep3_pterr_branch = tree->GetBranch("lep3_pterr");
		if (lep3_pterr_branch) {lep3_pterr_branch->SetAddress(&lep3_pterr_);}
	}
	lep3_ecal_vetodep_branch = 0;
	if (tree->GetBranch("lep3_ecal_vetodep") != 0) {
		lep3_ecal_vetodep_branch = tree->GetBranch("lep3_ecal_vetodep");
		if (lep3_ecal_vetodep_branch) {lep3_ecal_vetodep_branch->SetAddress(&lep3_ecal_vetodep_);}
	}
	lep3_hcal_vetodep_branch = 0;
	if (tree->GetBranch("lep3_hcal_vetodep") != 0) {
		lep3_hcal_vetodep_branch = tree->GetBranch("lep3_hcal_vetodep");
		if (lep3_hcal_vetodep_branch) {lep3_hcal_vetodep_branch->SetAddress(&lep3_hcal_vetodep_);}
	}
	selection_branch = 0;
	if (tree->GetBranch("selection") != 0) {
		selection_branch = tree->GetBranch("selection");
		if (selection_branch) {selection_branch->SetAddress(&selection_);}
	}
	is_good_lumi_branch = 0;
	if (tree->GetBranch("is_good_lumi") != 0) {
		is_good_lumi_branch = tree->GetBranch("is_good_lumi");
		if (is_good_lumi_branch) {is_good_lumi_branch->SetAddress(&is_good_lumi_);}
	}
	charge_type_branch = 0;
	if (tree->GetBranch("charge_type") != 0) {
		charge_type_branch = tree->GetBranch("charge_type");
		if (charge_type_branch) {charge_type_branch->SetAddress(&charge_type_);}
	}
	njets_branch = 0;
	if (tree->GetBranch("njets") != 0) {
		njets_branch = tree->GetBranch("njets");
		if (njets_branch) {njets_branch->SetAddress(&njets_);}
	}
	nbtags_branch = 0;
	if (tree->GetBranch("nbtags") != 0) {
		nbtags_branch = tree->GetBranch("nbtags");
		if (nbtags_branch) {nbtags_branch->SetAddress(&nbtags_);}
	}
	nbtags_loose_branch = 0;
	if (tree->GetBranch("nbtags_loose") != 0) {
		nbtags_loose_branch = tree->GetBranch("nbtags_loose");
		if (nbtags_loose_branch) {nbtags_loose_branch->SetAddress(&nbtags_loose_);}
	}
	ttbar_bkdn_branch = 0;
	if (tree->GetBranch("ttbar_bkdn") != 0) {
		ttbar_bkdn_branch = tree->GetBranch("ttbar_bkdn");
		if (ttbar_bkdn_branch) {ttbar_bkdn_branch->SetAddress(&ttbar_bkdn_);}
	}
	vtxw_branch = 0;
	if (tree->GetBranch("vtxw") != 0) {
		vtxw_branch = tree->GetBranch("vtxw");
		if (vtxw_branch) {vtxw_branch->SetAddress(&vtxw_);}
	}
	mt_branch = 0;
	if (tree->GetBranch("mt") != 0) {
		mt_branch = tree->GetBranch("mt");
		if (mt_branch) {mt_branch->SetAddress(&mt_);}
	}
	mt2_branch = 0;
	if (tree->GetBranch("mt2") != 0) {
		mt2_branch = tree->GetBranch("mt2");
		if (mt2_branch) {mt2_branch->SetAddress(&mt2_);}
	}
	ht_branch = 0;
	if (tree->GetBranch("ht") != 0) {
		ht_branch = tree->GetBranch("ht");
		if (ht_branch) {ht_branch->SetAddress(&ht_);}
	}
	rho_branch = 0;
	if (tree->GetBranch("rho") != 0) {
		rho_branch = tree->GetBranch("rho");
		if (rho_branch) {rho_branch->SetAddress(&rho_);}
	}
	rho_iso_branch = 0;
	if (tree->GetBranch("rho_iso") != 0) {
		rho_iso_branch = tree->GetBranch("rho_iso");
		if (rho_iso_branch) {rho_iso_branch->SetAddress(&rho_iso_);}
	}
	trig_mm_branch = 0;
	if (tree->GetBranch("trig_mm") != 0) {
		trig_mm_branch = tree->GetBranch("trig_mm");
		if (trig_mm_branch) {trig_mm_branch->SetAddress(&trig_mm_);}
	}
	trig_em_branch = 0;
	if (tree->GetBranch("trig_em") != 0) {
		trig_em_branch = tree->GetBranch("trig_em");
		if (trig_em_branch) {trig_em_branch->SetAddress(&trig_em_);}
	}
	trig_ee_branch = 0;
	if (tree->GetBranch("trig_ee") != 0) {
		trig_ee_branch = tree->GetBranch("trig_ee");
		if (trig_ee_branch) {trig_ee_branch->SetAddress(&trig_ee_);}
	}
	trig_mm_mu17_mu8_branch = 0;
	if (tree->GetBranch("trig_mm_mu17_mu8") != 0) {
		trig_mm_mu17_mu8_branch = tree->GetBranch("trig_mm_mu17_mu8");
		if (trig_mm_mu17_mu8_branch) {trig_mm_mu17_mu8_branch->SetAddress(&trig_mm_mu17_mu8_);}
	}
	trig_ee_el17_el8_id_iso_branch = 0;
	if (tree->GetBranch("trig_ee_el17_el8_id_iso") != 0) {
		trig_ee_el17_el8_id_iso_branch = tree->GetBranch("trig_ee_el17_el8_id_iso");
		if (trig_ee_el17_el8_id_iso_branch) {trig_ee_el17_el8_id_iso_branch->SetAddress(&trig_ee_el17_el8_id_iso_);}
	}
	trig_em_mu17_el8_id_iso_branch = 0;
	if (tree->GetBranch("trig_em_mu17_el8_id_iso") != 0) {
		trig_em_mu17_el8_id_iso_branch = tree->GetBranch("trig_em_mu17_el8_id_iso");
		if (trig_em_mu17_el8_id_iso_branch) {trig_em_mu17_el8_id_iso_branch->SetAddress(&trig_em_mu17_el8_id_iso_);}
	}
	trig_em_mu8_el17_id_iso_branch = 0;
	if (tree->GetBranch("trig_em_mu8_el17_id_iso") != 0) {
		trig_em_mu8_el17_id_iso_branch = tree->GetBranch("trig_em_mu8_el17_id_iso");
		if (trig_em_mu8_el17_id_iso_branch) {trig_em_mu8_el17_id_iso_branch->SetAddress(&trig_em_mu8_el17_id_iso_);}
	}
	njets_dn_branch = 0;
	if (tree->GetBranch("njets_dn") != 0) {
		njets_dn_branch = tree->GetBranch("njets_dn");
		if (njets_dn_branch) {njets_dn_branch->SetAddress(&njets_dn_);}
	}
	njets_up_branch = 0;
	if (tree->GetBranch("njets_up") != 0) {
		njets_up_branch = tree->GetBranch("njets_up");
		if (njets_up_branch) {njets_up_branch->SetAddress(&njets_up_);}
	}
	nbtags_dn_branch = 0;
	if (tree->GetBranch("nbtags_dn") != 0) {
		nbtags_dn_branch = tree->GetBranch("nbtags_dn");
		if (nbtags_dn_branch) {nbtags_dn_branch->SetAddress(&nbtags_dn_);}
	}
	nbtags_up_branch = 0;
	if (tree->GetBranch("nbtags_up") != 0) {
		nbtags_up_branch = tree->GetBranch("nbtags_up");
		if (nbtags_up_branch) {nbtags_up_branch->SetAddress(&nbtags_up_);}
	}
	ht_dn_branch = 0;
	if (tree->GetBranch("ht_dn") != 0) {
		ht_dn_branch = tree->GetBranch("ht_dn");
		if (ht_dn_branch) {ht_dn_branch->SetAddress(&ht_dn_);}
	}
	ht_up_branch = 0;
	if (tree->GetBranch("ht_up") != 0) {
		ht_up_branch = tree->GetBranch("ht_up");
		if (ht_up_branch) {ht_up_branch->SetAddress(&ht_up_);}
	}
	nbtags_reweighted_branch = 0;
	if (tree->GetBranch("nbtags_reweighted") != 0) {
		nbtags_reweighted_branch = tree->GetBranch("nbtags_reweighted");
		if (nbtags_reweighted_branch) {nbtags_reweighted_branch->SetAddress(&nbtags_reweighted_);}
	}
	nbtags_reweighted_dn_branch = 0;
	if (tree->GetBranch("nbtags_reweighted_dn") != 0) {
		nbtags_reweighted_dn_branch = tree->GetBranch("nbtags_reweighted_dn");
		if (nbtags_reweighted_dn_branch) {nbtags_reweighted_dn_branch->SetAddress(&nbtags_reweighted_dn_);}
	}
	nbtags_reweighted_up_branch = 0;
	if (tree->GetBranch("nbtags_reweighted_up") != 0) {
		nbtags_reweighted_up_branch = tree->GetBranch("nbtags_reweighted_up");
		if (nbtags_reweighted_up_branch) {nbtags_reweighted_up_branch->SetAddress(&nbtags_reweighted_up_);}
	}
	nbtags_reweighted_jec_dn_branch = 0;
	if (tree->GetBranch("nbtags_reweighted_jec_dn") != 0) {
		nbtags_reweighted_jec_dn_branch = tree->GetBranch("nbtags_reweighted_jec_dn");
		if (nbtags_reweighted_jec_dn_branch) {nbtags_reweighted_jec_dn_branch->SetAddress(&nbtags_reweighted_jec_dn_);}
	}
	nbtags_reweighted_jec_up_branch = 0;
	if (tree->GetBranch("nbtags_reweighted_jec_up") != 0) {
		nbtags_reweighted_jec_up_branch = tree->GetBranch("nbtags_reweighted_jec_up");
		if (nbtags_reweighted_jec_up_branch) {nbtags_reweighted_jec_up_branch->SetAddress(&nbtags_reweighted_jec_up_);}
	}
	pfmet_dn_branch = 0;
	if (tree->GetBranch("pfmet_dn") != 0) {
		pfmet_dn_branch = tree->GetBranch("pfmet_dn");
		if (pfmet_dn_branch) {pfmet_dn_branch->SetAddress(&pfmet_dn_);}
	}
	pfmet_up_branch = 0;
	if (tree->GetBranch("pfmet_up") != 0) {
		pfmet_up_branch = tree->GetBranch("pfmet_up");
		if (pfmet_up_branch) {pfmet_up_branch->SetAddress(&pfmet_up_);}
	}
	pfmet_phi_dn_branch = 0;
	if (tree->GetBranch("pfmet_phi_dn") != 0) {
		pfmet_phi_dn_branch = tree->GetBranch("pfmet_phi_dn");
		if (pfmet_phi_dn_branch) {pfmet_phi_dn_branch->SetAddress(&pfmet_phi_dn_);}
	}
	pfmet_phi_up_branch = 0;
	if (tree->GetBranch("pfmet_phi_up") != 0) {
		pfmet_phi_up_branch = tree->GetBranch("pfmet_phi_up");
		if (pfmet_phi_up_branch) {pfmet_phi_up_branch->SetAddress(&pfmet_phi_up_);}
	}
	sf_dileptrig_branch = 0;
	if (tree->GetBranch("sf_dileptrig") != 0) {
		sf_dileptrig_branch = tree->GetBranch("sf_dileptrig");
		if (sf_dileptrig_branch) {sf_dileptrig_branch->SetAddress(&sf_dileptrig_);}
	}
	sf_lepeff_branch = 0;
	if (tree->GetBranch("sf_lepeff") != 0) {
		sf_lepeff_branch = tree->GetBranch("sf_lepeff");
		if (sf_lepeff_branch) {sf_lepeff_branch->SetAddress(&sf_lepeff_);}
	}
	sparm0_branch = 0;
	if (tree->GetBranch("sparm0") != 0) {
		sparm0_branch = tree->GetBranch("sparm0");
		if (sparm0_branch) {sparm0_branch->SetAddress(&sparm0_);}
	}
	sparm1_branch = 0;
	if (tree->GetBranch("sparm1") != 0) {
		sparm1_branch = tree->GetBranch("sparm1");
		if (sparm1_branch) {sparm1_branch->SetAddress(&sparm1_);}
	}
	sparm2_branch = 0;
	if (tree->GetBranch("sparm2") != 0) {
		sparm2_branch = tree->GetBranch("sparm2");
		if (sparm2_branch) {sparm2_branch->SetAddress(&sparm2_);}
	}
	sparm3_branch = 0;
	if (tree->GetBranch("sparm3") != 0) {
		sparm3_branch = tree->GetBranch("sparm3");
		if (sparm3_branch) {sparm3_branch->SetAddress(&sparm3_);}
	}
	sparm0_name_branch = 0;
	if (tree->GetBranch("sparm0_name") != 0) {
		sparm0_name_branch = tree->GetBranch("sparm0_name");
		if (sparm0_name_branch) {sparm0_name_branch->SetAddress(&sparm0_name_);}
	}
	sparm1_name_branch = 0;
	if (tree->GetBranch("sparm1_name") != 0) {
		sparm1_name_branch = tree->GetBranch("sparm1_name");
		if (sparm1_name_branch) {sparm1_name_branch->SetAddress(&sparm1_name_);}
	}
	sparm2_name_branch = 0;
	if (tree->GetBranch("sparm2_name") != 0) {
		sparm2_name_branch = tree->GetBranch("sparm2_name");
		if (sparm2_name_branch) {sparm2_name_branch->SetAddress(&sparm2_name_);}
	}
	sparm3_name_branch = 0;
	if (tree->GetBranch("sparm3_name") != 0) {
		sparm3_name_branch = tree->GetBranch("sparm3_name");
		if (sparm3_name_branch) {sparm3_name_branch->SetAddress(&sparm3_name_);}
	}
	is_pp_branch = 0;
	if (tree->GetBranch("is_pp") != 0) {
		is_pp_branch = tree->GetBranch("is_pp");
		if (is_pp_branch) {is_pp_branch->SetAddress(&is_pp_);}
	}
	is_mm_branch = 0;
	if (tree->GetBranch("is_mm") != 0) {
		is_mm_branch = tree->GetBranch("is_mm");
		if (is_mm_branch) {is_mm_branch->SetAddress(&is_mm_);}
	}
	is_ss_branch = 0;
	if (tree->GetBranch("is_ss") != 0) {
		is_ss_branch = tree->GetBranch("is_ss");
		if (is_ss_branch) {is_ss_branch->SetAddress(&is_ss_);}
	}
	is_sf_branch = 0;
	if (tree->GetBranch("is_sf") != 0) {
		is_sf_branch = tree->GetBranch("is_sf");
		if (is_sf_branch) {is_sf_branch->SetAddress(&is_sf_);}
	}
	is_df_branch = 0;
	if (tree->GetBranch("is_df") != 0) {
		is_df_branch = tree->GetBranch("is_df");
		if (is_df_branch) {is_df_branch->SetAddress(&is_df_);}
	}
	is_os_branch = 0;
	if (tree->GetBranch("is_os") != 0) {
		is_os_branch = tree->GetBranch("is_os");
		if (is_os_branch) {is_os_branch->SetAddress(&is_os_);}
	}
	no_extraz_branch = 0;
	if (tree->GetBranch("no_extraz") != 0) {
		no_extraz_branch = tree->GetBranch("no_extraz");
		if (no_extraz_branch) {no_extraz_branch->SetAddress(&no_extraz_);}
	}
	no_extrag_branch = 0;
	if (tree->GetBranch("no_extrag") != 0) {
		no_extrag_branch = tree->GetBranch("no_extrag");
		if (no_extrag_branch) {no_extrag_branch->SetAddress(&no_extrag_);}
	}
	clean_branch = 0;
	if (tree->GetBranch("clean") != 0) {
		clean_branch = tree->GetBranch("clean");
		if (clean_branch) {clean_branch->SetAddress(&clean_);}
	}
	presel_branch = 0;
	if (tree->GetBranch("presel") != 0) {
		presel_branch = tree->GetBranch("presel");
		if (presel_branch) {presel_branch->SetAddress(&presel_);}
	}
	em_mufo_branch = 0;
	if (tree->GetBranch("em_mufo") != 0) {
		em_mufo_branch = tree->GetBranch("em_mufo");
		if (em_mufo_branch) {em_mufo_branch->SetAddress(&em_mufo_);}
	}
	em_elfo_branch = 0;
	if (tree->GetBranch("em_elfo") != 0) {
		em_elfo_branch = tree->GetBranch("em_elfo");
		if (em_elfo_branch) {em_elfo_branch->SetAddress(&em_elfo_);}
	}
	hyp_good_vtx_branch = 0;
	if (tree->GetBranch("hyp_good_vtx") != 0) {
		hyp_good_vtx_branch = tree->GetBranch("hyp_good_vtx");
		if (hyp_good_vtx_branch) {hyp_good_vtx_branch->SetAddress(&hyp_good_vtx_);}
	}
	is_gen_pp_branch = 0;
	if (tree->GetBranch("is_gen_pp") != 0) {
		is_gen_pp_branch = tree->GetBranch("is_gen_pp");
		if (is_gen_pp_branch) {is_gen_pp_branch->SetAddress(&is_gen_pp_);}
	}
	is_gen_mm_branch = 0;
	if (tree->GetBranch("is_gen_mm") != 0) {
		is_gen_mm_branch = tree->GetBranch("is_gen_mm");
		if (is_gen_mm_branch) {is_gen_mm_branch->SetAddress(&is_gen_mm_);}
	}
	gen_njets_branch = 0;
	if (tree->GetBranch("gen_njets") != 0) {
		gen_njets_branch = tree->GetBranch("gen_njets");
		if (gen_njets_branch) {gen_njets_branch->SetAddress(&gen_njets_);}
	}
	gen_nleps_branch = 0;
	if (tree->GetBranch("gen_nleps") != 0) {
		gen_nleps_branch = tree->GetBranch("gen_nleps");
		if (gen_nleps_branch) {gen_nleps_branch->SetAddress(&gen_nleps_);}
	}
	gen_nmus_branch = 0;
	if (tree->GetBranch("gen_nmus") != 0) {
		gen_nmus_branch = tree->GetBranch("gen_nmus");
		if (gen_nmus_branch) {gen_nmus_branch->SetAddress(&gen_nmus_);}
	}
	gen_nels_branch = 0;
	if (tree->GetBranch("gen_nels") != 0) {
		gen_nels_branch = tree->GetBranch("gen_nels");
		if (gen_nels_branch) {gen_nels_branch->SetAddress(&gen_nels_);}
	}
	gen_ntaus_branch = 0;
	if (tree->GetBranch("gen_ntaus") != 0) {
		gen_ntaus_branch = tree->GetBranch("gen_ntaus");
		if (gen_ntaus_branch) {gen_ntaus_branch->SetAddress(&gen_ntaus_);}
	}
	gen_ht_branch = 0;
	if (tree->GetBranch("gen_ht") != 0) {
		gen_ht_branch = tree->GetBranch("gen_ht");
		if (gen_ht_branch) {gen_ht_branch->SetAddress(&gen_ht_);}
	}
	lep1_wfr_branch = 0;
	if (tree->GetBranch("lep1_wfr") != 0) {
		lep1_wfr_branch = tree->GetBranch("lep1_wfr");
		if (lep1_wfr_branch) {lep1_wfr_branch->SetAddress(&lep1_wfr_);}
	}
	lep1_wflip_branch = 0;
	if (tree->GetBranch("lep1_wflip") != 0) {
		lep1_wflip_branch = tree->GetBranch("lep1_wflip");
		if (lep1_wflip_branch) {lep1_wflip_branch->SetAddress(&lep1_wflip_);}
	}
	lep1_nearjet_dr_branch = 0;
	if (tree->GetBranch("lep1_nearjet_dr") != 0) {
		lep1_nearjet_dr_branch = tree->GetBranch("lep1_nearjet_dr");
		if (lep1_nearjet_dr_branch) {lep1_nearjet_dr_branch->SetAddress(&lep1_nearjet_dr_);}
	}
	lep1_nearlep_dr_branch = 0;
	if (tree->GetBranch("lep1_nearlep_dr") != 0) {
		lep1_nearlep_dr_branch = tree->GetBranch("lep1_nearlep_dr");
		if (lep1_nearlep_dr_branch) {lep1_nearlep_dr_branch->SetAddress(&lep1_nearlep_dr_);}
	}
	lep1_nearlep_id_branch = 0;
	if (tree->GetBranch("lep1_nearlep_id") != 0) {
		lep1_nearlep_id_branch = tree->GetBranch("lep1_nearlep_id");
		if (lep1_nearlep_id_branch) {lep1_nearlep_id_branch->SetAddress(&lep1_nearlep_id_);}
	}
	lep1_isFromH_branch = 0;
	if (tree->GetBranch("lep1_isFromH") != 0) {
		lep1_isFromH_branch = tree->GetBranch("lep1_isFromH");
		if (lep1_isFromH_branch) {lep1_isFromH_branch->SetAddress(&lep1_isFromH_);}
	}
	lep2_wfr_branch = 0;
	if (tree->GetBranch("lep2_wfr") != 0) {
		lep2_wfr_branch = tree->GetBranch("lep2_wfr");
		if (lep2_wfr_branch) {lep2_wfr_branch->SetAddress(&lep2_wfr_);}
	}
	lep2_wflip_branch = 0;
	if (tree->GetBranch("lep2_wflip") != 0) {
		lep2_wflip_branch = tree->GetBranch("lep2_wflip");
		if (lep2_wflip_branch) {lep2_wflip_branch->SetAddress(&lep2_wflip_);}
	}
	lep2_nearjet_dr_branch = 0;
	if (tree->GetBranch("lep2_nearjet_dr") != 0) {
		lep2_nearjet_dr_branch = tree->GetBranch("lep2_nearjet_dr");
		if (lep2_nearjet_dr_branch) {lep2_nearjet_dr_branch->SetAddress(&lep2_nearjet_dr_);}
	}
	lep2_nearlep_dr_branch = 0;
	if (tree->GetBranch("lep2_nearlep_dr") != 0) {
		lep2_nearlep_dr_branch = tree->GetBranch("lep2_nearlep_dr");
		if (lep2_nearlep_dr_branch) {lep2_nearlep_dr_branch->SetAddress(&lep2_nearlep_dr_);}
	}
	lep2_nearlep_id_branch = 0;
	if (tree->GetBranch("lep2_nearlep_id") != 0) {
		lep2_nearlep_id_branch = tree->GetBranch("lep2_nearlep_id");
		if (lep2_nearlep_id_branch) {lep2_nearlep_id_branch->SetAddress(&lep2_nearlep_id_);}
	}
	lep2_isFromH_branch = 0;
	if (tree->GetBranch("lep2_isFromH") != 0) {
		lep2_isFromH_branch = tree->GetBranch("lep2_isFromH");
		if (lep2_isFromH_branch) {lep2_isFromH_branch->SetAddress(&lep2_isFromH_);}
	}
	jets_dr12_branch = 0;
	if (tree->GetBranch("jets_dr12") != 0) {
		jets_dr12_branch = tree->GetBranch("jets_dr12");
		if (jets_dr12_branch) {jets_dr12_branch->SetAddress(&jets_dr12_);}
	}
	dijet_mass_branch = 0;
	if (tree->GetBranch("dijet_mass") != 0) {
		dijet_mass_branch = tree->GetBranch("dijet_mass");
		if (dijet_mass_branch) {dijet_mass_branch->SetAddress(&dijet_mass_);}
	}
	vjets_mcflavor_phys_branch = 0;
	if (tree->GetBranch("vjets_mcflavor_phys") != 0) {
		vjets_mcflavor_phys_branch = tree->GetBranch("vjets_mcflavor_phys");
		if (vjets_mcflavor_phys_branch) {vjets_mcflavor_phys_branch->SetAddress(&vjets_mcflavor_phys_);}
	}
	vjets_mcflavor_algo_branch = 0;
	if (tree->GetBranch("vjets_mcflavor_algo") != 0) {
		vjets_mcflavor_algo_branch = tree->GetBranch("vjets_mcflavor_algo");
		if (vjets_mcflavor_algo_branch) {vjets_mcflavor_algo_branch->SetAddress(&vjets_mcflavor_algo_);}
	}
	vjets_mcflavor_phys_up_branch = 0;
	if (tree->GetBranch("vjets_mcflavor_phys_up") != 0) {
		vjets_mcflavor_phys_up_branch = tree->GetBranch("vjets_mcflavor_phys_up");
		if (vjets_mcflavor_phys_up_branch) {vjets_mcflavor_phys_up_branch->SetAddress(&vjets_mcflavor_phys_up_);}
	}
	vjets_mcflavor_algo_up_branch = 0;
	if (tree->GetBranch("vjets_mcflavor_algo_up") != 0) {
		vjets_mcflavor_algo_up_branch = tree->GetBranch("vjets_mcflavor_algo_up");
		if (vjets_mcflavor_algo_up_branch) {vjets_mcflavor_algo_up_branch->SetAddress(&vjets_mcflavor_algo_up_);}
	}
	vjets_mcflavor_phys_dn_branch = 0;
	if (tree->GetBranch("vjets_mcflavor_phys_dn") != 0) {
		vjets_mcflavor_phys_dn_branch = tree->GetBranch("vjets_mcflavor_phys_dn");
		if (vjets_mcflavor_phys_dn_branch) {vjets_mcflavor_phys_dn_branch->SetAddress(&vjets_mcflavor_phys_dn_);}
	}
	vjets_mcflavor_algo_dn_branch = 0;
	if (tree->GetBranch("vjets_mcflavor_algo_dn") != 0) {
		vjets_mcflavor_algo_dn_branch = tree->GetBranch("vjets_mcflavor_algo_dn");
		if (vjets_mcflavor_algo_dn_branch) {vjets_mcflavor_algo_dn_branch->SetAddress(&vjets_mcflavor_algo_dn_);}
	}
	vjets_mc3id_branch = 0;
	if (tree->GetBranch("vjets_mc3id") != 0) {
		vjets_mc3id_branch = tree->GetBranch("vjets_mc3id");
		if (vjets_mc3id_branch) {vjets_mc3id_branch->SetAddress(&vjets_mc3id_);}
	}
	vjets_momid_branch = 0;
	if (tree->GetBranch("vjets_momid") != 0) {
		vjets_momid_branch = tree->GetBranch("vjets_momid");
		if (vjets_momid_branch) {vjets_momid_branch->SetAddress(&vjets_momid_);}
	}
	vjets_nearjet_dr_branch = 0;
	if (tree->GetBranch("vjets_nearjet_dr") != 0) {
		vjets_nearjet_dr_branch = tree->GetBranch("vjets_nearjet_dr");
		if (vjets_nearjet_dr_branch) {vjets_nearjet_dr_branch->SetAddress(&vjets_nearjet_dr_);}
	}
	vjets_bdisc_branch = 0;
	if (tree->GetBranch("vjets_bdisc") != 0) {
		vjets_bdisc_branch = tree->GetBranch("vjets_bdisc");
		if (vjets_bdisc_branch) {vjets_bdisc_branch->SetAddress(&vjets_bdisc_);}
	}
	gen_lep1_pdgid_branch = 0;
	if (tree->GetBranch("gen_lep1_pdgid") != 0) {
		gen_lep1_pdgid_branch = tree->GetBranch("gen_lep1_pdgid");
		if (gen_lep1_pdgid_branch) {gen_lep1_pdgid_branch->SetAddress(&gen_lep1_pdgid_);}
	}
	gen_lep2_pdgid_branch = 0;
	if (tree->GetBranch("gen_lep2_pdgid") != 0) {
		gen_lep2_pdgid_branch = tree->GetBranch("gen_lep2_pdgid");
		if (gen_lep2_pdgid_branch) {gen_lep2_pdgid_branch->SetAddress(&gen_lep2_pdgid_);}
	}
	gen_dilep_type_branch = 0;
	if (tree->GetBranch("gen_dilep_type") != 0) {
		gen_dilep_type_branch = tree->GetBranch("gen_dilep_type");
		if (gen_dilep_type_branch) {gen_dilep_type_branch->SetAddress(&gen_dilep_type_);}
	}
	gen_dilep_mass_branch = 0;
	if (tree->GetBranch("gen_dilep_mass") != 0) {
		gen_dilep_mass_branch = tree->GetBranch("gen_dilep_mass");
		if (gen_dilep_mass_branch) {gen_dilep_mass_branch->SetAddress(&gen_dilep_mass_);}
	}
	gen_dilep_dphi_branch = 0;
	if (tree->GetBranch("gen_dilep_dphi") != 0) {
		gen_dilep_dphi_branch = tree->GetBranch("gen_dilep_dphi");
		if (gen_dilep_dphi_branch) {gen_dilep_dphi_branch->SetAddress(&gen_dilep_dphi_);}
	}
	gen_dilep_deta_branch = 0;
	if (tree->GetBranch("gen_dilep_deta") != 0) {
		gen_dilep_deta_branch = tree->GetBranch("gen_dilep_deta");
		if (gen_dilep_deta_branch) {gen_dilep_deta_branch->SetAddress(&gen_dilep_deta_);}
	}
	gen_dilep_dr_branch = 0;
	if (tree->GetBranch("gen_dilep_dr") != 0) {
		gen_dilep_dr_branch = tree->GetBranch("gen_dilep_dr");
		if (gen_dilep_dr_branch) {gen_dilep_dr_branch->SetAddress(&gen_dilep_dr_);}
	}
	pfcandid5_branch = 0;
	if (tree->GetBranch("pfcandid5") != 0) {
		pfcandid5_branch = tree->GetBranch("pfcandid5");
		if (pfcandid5_branch) {pfcandid5_branch->SetAddress(&pfcandid5_);}
	}
	pfcandid10_branch = 0;
	if (tree->GetBranch("pfcandid10") != 0) {
		pfcandid10_branch = tree->GetBranch("pfcandid10");
		if (pfcandid10_branch) {pfcandid10_branch->SetAddress(&pfcandid10_);}
	}
	pfcanddirid10_branch = 0;
	if (tree->GetBranch("pfcanddirid10") != 0) {
		pfcanddirid10_branch = tree->GetBranch("pfcanddirid10");
		if (pfcanddirid10_branch) {pfcanddirid10_branch->SetAddress(&pfcanddirid10_);}
	}
	pfcandvetoid10_branch = 0;
	if (tree->GetBranch("pfcandvetoid10") != 0) {
		pfcandvetoid10_branch = tree->GetBranch("pfcandvetoid10");
		if (pfcandvetoid10_branch) {pfcandvetoid10_branch->SetAddress(&pfcandvetoid10_);}
	}
	pfcandvetoLid10_branch = 0;
	if (tree->GetBranch("pfcandvetoLid10") != 0) {
		pfcandvetoLid10_branch = tree->GetBranch("pfcandvetoLid10");
		if (pfcandvetoLid10_branch) {pfcandvetoLid10_branch->SetAddress(&pfcandvetoLid10_);}
	}
	pfcandidOS10_branch = 0;
	if (tree->GetBranch("pfcandidOS10") != 0) {
		pfcandidOS10_branch = tree->GetBranch("pfcandidOS10");
		if (pfcandidOS10_branch) {pfcandidOS10_branch->SetAddress(&pfcandidOS10_);}
	}
	pfcandidOS10looseZ_branch = 0;
	if (tree->GetBranch("pfcandidOS10looseZ") != 0) {
		pfcandidOS10looseZ_branch = tree->GetBranch("pfcandidOS10looseZ");
		if (pfcandidOS10looseZ_branch) {pfcandidOS10looseZ_branch->SetAddress(&pfcandidOS10looseZ_);}
	}
	pfcandid5looseZ_branch = 0;
	if (tree->GetBranch("pfcandid5looseZ") != 0) {
		pfcandid5looseZ_branch = tree->GetBranch("pfcandid5looseZ");
		if (pfcandid5looseZ_branch) {pfcandid5looseZ_branch->SetAddress(&pfcandid5looseZ_);}
	}
	trkpt5_branch = 0;
	if (tree->GetBranch("trkpt5") != 0) {
		trkpt5_branch = tree->GetBranch("trkpt5");
		if (trkpt5_branch) {trkpt5_branch->SetAddress(&trkpt5_);}
	}
	mleptrk5_branch = 0;
	if (tree->GetBranch("mleptrk5") != 0) {
		mleptrk5_branch = tree->GetBranch("mleptrk5");
		if (mleptrk5_branch) {mleptrk5_branch->SetAddress(&mleptrk5_);}
	}
	trkreliso5_branch = 0;
	if (tree->GetBranch("trkreliso5") != 0) {
		trkreliso5_branch = tree->GetBranch("trkreliso5");
		if (trkreliso5_branch) {trkreliso5_branch->SetAddress(&trkreliso5_);}
	}
	trkpt10_branch = 0;
	if (tree->GetBranch("trkpt10") != 0) {
		trkpt10_branch = tree->GetBranch("trkpt10");
		if (trkpt10_branch) {trkpt10_branch->SetAddress(&trkpt10_);}
	}
	mleptrk10_branch = 0;
	if (tree->GetBranch("mleptrk10") != 0) {
		mleptrk10_branch = tree->GetBranch("mleptrk10");
		if (mleptrk10_branch) {mleptrk10_branch->SetAddress(&mleptrk10_);}
	}
	trkreliso10_branch = 0;
	if (tree->GetBranch("trkreliso10") != 0) {
		trkreliso10_branch = tree->GetBranch("trkreliso10");
		if (trkreliso10_branch) {trkreliso10_branch->SetAddress(&trkreliso10_);}
	}
	trkpt5loose_branch = 0;
	if (tree->GetBranch("trkpt5loose") != 0) {
		trkpt5loose_branch = tree->GetBranch("trkpt5loose");
		if (trkpt5loose_branch) {trkpt5loose_branch->SetAddress(&trkpt5loose_);}
	}
	trkreliso5loose_branch = 0;
	if (tree->GetBranch("trkreliso5loose") != 0) {
		trkreliso5loose_branch = tree->GetBranch("trkreliso5loose");
		if (trkreliso5loose_branch) {trkreliso5loose_branch->SetAddress(&trkreliso5loose_);}
	}
	trkpt10loose_branch = 0;
	if (tree->GetBranch("trkpt10loose") != 0) {
		trkpt10loose_branch = tree->GetBranch("trkpt10loose");
		if (trkpt10loose_branch) {trkpt10loose_branch->SetAddress(&trkpt10loose_);}
	}
	trkreliso10loose_branch = 0;
	if (tree->GetBranch("trkreliso10loose") != 0) {
		trkreliso10loose_branch = tree->GetBranch("trkreliso10loose");
		if (trkreliso10loose_branch) {trkreliso10loose_branch->SetAddress(&trkreliso10loose_);}
	}
	trkpt10pt0p1_branch = 0;
	if (tree->GetBranch("trkpt10pt0p1") != 0) {
		trkpt10pt0p1_branch = tree->GetBranch("trkpt10pt0p1");
		if (trkpt10pt0p1_branch) {trkpt10pt0p1_branch->SetAddress(&trkpt10pt0p1_);}
	}
	trkreliso10pt0p1_branch = 0;
	if (tree->GetBranch("trkreliso10pt0p1") != 0) {
		trkreliso10pt0p1_branch = tree->GetBranch("trkreliso10pt0p1");
		if (trkreliso10pt0p1_branch) {trkreliso10pt0p1_branch->SetAddress(&trkreliso10pt0p1_);}
	}
	trkpt10pt0p2_branch = 0;
	if (tree->GetBranch("trkpt10pt0p2") != 0) {
		trkpt10pt0p2_branch = tree->GetBranch("trkpt10pt0p2");
		if (trkpt10pt0p2_branch) {trkpt10pt0p2_branch->SetAddress(&trkpt10pt0p2_);}
	}
	trkreliso10pt0p2_branch = 0;
	if (tree->GetBranch("trkreliso10pt0p2") != 0) {
		trkreliso10pt0p2_branch = tree->GetBranch("trkreliso10pt0p2");
		if (trkreliso10pt0p2_branch) {trkreliso10pt0p2_branch->SetAddress(&trkreliso10pt0p2_);}
	}
	trkpt10pt0p3_branch = 0;
	if (tree->GetBranch("trkpt10pt0p3") != 0) {
		trkpt10pt0p3_branch = tree->GetBranch("trkpt10pt0p3");
		if (trkpt10pt0p3_branch) {trkpt10pt0p3_branch->SetAddress(&trkpt10pt0p3_);}
	}
	trkreliso10pt0p3_branch = 0;
	if (tree->GetBranch("trkreliso10pt0p3") != 0) {
		trkreliso10pt0p3_branch = tree->GetBranch("trkreliso10pt0p3");
		if (trkreliso10pt0p3_branch) {trkreliso10pt0p3_branch->SetAddress(&trkreliso10pt0p3_);}
	}
	trkpt10pt0p4_branch = 0;
	if (tree->GetBranch("trkpt10pt0p4") != 0) {
		trkpt10pt0p4_branch = tree->GetBranch("trkpt10pt0p4");
		if (trkpt10pt0p4_branch) {trkpt10pt0p4_branch->SetAddress(&trkpt10pt0p4_);}
	}
	trkreliso10pt0p4_branch = 0;
	if (tree->GetBranch("trkreliso10pt0p4") != 0) {
		trkreliso10pt0p4_branch = tree->GetBranch("trkreliso10pt0p4");
		if (trkreliso10pt0p4_branch) {trkreliso10pt0p4_branch->SetAddress(&trkreliso10pt0p4_);}
	}
	trkpt10pt0p5_branch = 0;
	if (tree->GetBranch("trkpt10pt0p5") != 0) {
		trkpt10pt0p5_branch = tree->GetBranch("trkpt10pt0p5");
		if (trkpt10pt0p5_branch) {trkpt10pt0p5_branch->SetAddress(&trkpt10pt0p5_);}
	}
	trkreliso10pt0p5_branch = 0;
	if (tree->GetBranch("trkreliso10pt0p5") != 0) {
		trkreliso10pt0p5_branch = tree->GetBranch("trkreliso10pt0p5");
		if (trkreliso10pt0p5_branch) {trkreliso10pt0p5_branch->SetAddress(&trkreliso10pt0p5_);}
	}
	trkpt10pt0p6_branch = 0;
	if (tree->GetBranch("trkpt10pt0p6") != 0) {
		trkpt10pt0p6_branch = tree->GetBranch("trkpt10pt0p6");
		if (trkpt10pt0p6_branch) {trkpt10pt0p6_branch->SetAddress(&trkpt10pt0p6_);}
	}
	trkreliso10pt0p6_branch = 0;
	if (tree->GetBranch("trkreliso10pt0p6") != 0) {
		trkreliso10pt0p6_branch = tree->GetBranch("trkreliso10pt0p6");
		if (trkreliso10pt0p6_branch) {trkreliso10pt0p6_branch->SetAddress(&trkreliso10pt0p6_);}
	}
	trkpt10pt0p7_branch = 0;
	if (tree->GetBranch("trkpt10pt0p7") != 0) {
		trkpt10pt0p7_branch = tree->GetBranch("trkpt10pt0p7");
		if (trkpt10pt0p7_branch) {trkpt10pt0p7_branch->SetAddress(&trkpt10pt0p7_);}
	}
	trkreliso10pt0p7_branch = 0;
	if (tree->GetBranch("trkreliso10pt0p7") != 0) {
		trkreliso10pt0p7_branch = tree->GetBranch("trkreliso10pt0p7");
		if (trkreliso10pt0p7_branch) {trkreliso10pt0p7_branch->SetAddress(&trkreliso10pt0p7_);}
	}
	trkpt10pt0p8_branch = 0;
	if (tree->GetBranch("trkpt10pt0p8") != 0) {
		trkpt10pt0p8_branch = tree->GetBranch("trkpt10pt0p8");
		if (trkpt10pt0p8_branch) {trkpt10pt0p8_branch->SetAddress(&trkpt10pt0p8_);}
	}
	trkreliso10pt0p8_branch = 0;
	if (tree->GetBranch("trkreliso10pt0p8") != 0) {
		trkreliso10pt0p8_branch = tree->GetBranch("trkreliso10pt0p8");
		if (trkreliso10pt0p8_branch) {trkreliso10pt0p8_branch->SetAddress(&trkreliso10pt0p8_);}
	}
	trkpt10pt0p9_branch = 0;
	if (tree->GetBranch("trkpt10pt0p9") != 0) {
		trkpt10pt0p9_branch = tree->GetBranch("trkpt10pt0p9");
		if (trkpt10pt0p9_branch) {trkpt10pt0p9_branch->SetAddress(&trkpt10pt0p9_);}
	}
	trkreliso10pt0p9_branch = 0;
	if (tree->GetBranch("trkreliso10pt0p9") != 0) {
		trkreliso10pt0p9_branch = tree->GetBranch("trkreliso10pt0p9");
		if (trkreliso10pt0p9_branch) {trkreliso10pt0p9_branch->SetAddress(&trkreliso10pt0p9_);}
	}
	trkpt10pt1p0_branch = 0;
	if (tree->GetBranch("trkpt10pt1p0") != 0) {
		trkpt10pt1p0_branch = tree->GetBranch("trkpt10pt1p0");
		if (trkpt10pt1p0_branch) {trkpt10pt1p0_branch->SetAddress(&trkpt10pt1p0_);}
	}
	trkreliso10pt1p0_branch = 0;
	if (tree->GetBranch("trkreliso10pt1p0") != 0) {
		trkreliso10pt1p0_branch = tree->GetBranch("trkreliso10pt1p0");
		if (trkreliso10pt1p0_branch) {trkreliso10pt1p0_branch->SetAddress(&trkreliso10pt1p0_);}
	}
	pfcandiso5_branch = 0;
	if (tree->GetBranch("pfcandiso5") != 0) {
		pfcandiso5_branch = tree->GetBranch("pfcandiso5");
		if (pfcandiso5_branch) {pfcandiso5_branch->SetAddress(&pfcandiso5_);}
	}
	pfcandiso10_branch = 0;
	if (tree->GetBranch("pfcandiso10") != 0) {
		pfcandiso10_branch = tree->GetBranch("pfcandiso10");
		if (pfcandiso10_branch) {pfcandiso10_branch->SetAddress(&pfcandiso10_);}
	}
	pfcanddiriso10_branch = 0;
	if (tree->GetBranch("pfcanddiriso10") != 0) {
		pfcanddiriso10_branch = tree->GetBranch("pfcanddiriso10");
		if (pfcanddiriso10_branch) {pfcanddiriso10_branch->SetAddress(&pfcanddiriso10_);}
	}
	pfcandvetoiso10_branch = 0;
	if (tree->GetBranch("pfcandvetoiso10") != 0) {
		pfcandvetoiso10_branch = tree->GetBranch("pfcandvetoiso10");
		if (pfcandvetoiso10_branch) {pfcandvetoiso10_branch->SetAddress(&pfcandvetoiso10_);}
	}
	pfcandvetoLiso10_branch = 0;
	if (tree->GetBranch("pfcandvetoLiso10") != 0) {
		pfcandvetoLiso10_branch = tree->GetBranch("pfcandvetoLiso10");
		if (pfcandvetoLiso10_branch) {pfcandvetoLiso10_branch->SetAddress(&pfcandvetoLiso10_);}
	}
	pfcandisoOS10_branch = 0;
	if (tree->GetBranch("pfcandisoOS10") != 0) {
		pfcandisoOS10_branch = tree->GetBranch("pfcandisoOS10");
		if (pfcandisoOS10_branch) {pfcandisoOS10_branch->SetAddress(&pfcandisoOS10_);}
	}
	pfcandisoOS10looseZ_branch = 0;
	if (tree->GetBranch("pfcandisoOS10looseZ") != 0) {
		pfcandisoOS10looseZ_branch = tree->GetBranch("pfcandisoOS10looseZ");
		if (pfcandisoOS10looseZ_branch) {pfcandisoOS10looseZ_branch->SetAddress(&pfcandisoOS10looseZ_);}
	}
	pfcandiso5looseZ_branch = 0;
	if (tree->GetBranch("pfcandiso5looseZ") != 0) {
		pfcandiso5looseZ_branch = tree->GetBranch("pfcandiso5looseZ");
		if (pfcandiso5looseZ_branch) {pfcandiso5looseZ_branch->SetAddress(&pfcandiso5looseZ_);}
	}
	pfcandpt5_branch = 0;
	if (tree->GetBranch("pfcandpt5") != 0) {
		pfcandpt5_branch = tree->GetBranch("pfcandpt5");
		if (pfcandpt5_branch) {pfcandpt5_branch->SetAddress(&pfcandpt5_);}
	}
	pfcandpt10_branch = 0;
	if (tree->GetBranch("pfcandpt10") != 0) {
		pfcandpt10_branch = tree->GetBranch("pfcandpt10");
		if (pfcandpt10_branch) {pfcandpt10_branch->SetAddress(&pfcandpt10_);}
	}
	pfcanddirpt10_branch = 0;
	if (tree->GetBranch("pfcanddirpt10") != 0) {
		pfcanddirpt10_branch = tree->GetBranch("pfcanddirpt10");
		if (pfcanddirpt10_branch) {pfcanddirpt10_branch->SetAddress(&pfcanddirpt10_);}
	}
	pfcandvetopt10_branch = 0;
	if (tree->GetBranch("pfcandvetopt10") != 0) {
		pfcandvetopt10_branch = tree->GetBranch("pfcandvetopt10");
		if (pfcandvetopt10_branch) {pfcandvetopt10_branch->SetAddress(&pfcandvetopt10_);}
	}
	pfcandvetoLpt10_branch = 0;
	if (tree->GetBranch("pfcandvetoLpt10") != 0) {
		pfcandvetoLpt10_branch = tree->GetBranch("pfcandvetoLpt10");
		if (pfcandvetoLpt10_branch) {pfcandvetoLpt10_branch->SetAddress(&pfcandvetoLpt10_);}
	}
	pfcandptOS10_branch = 0;
	if (tree->GetBranch("pfcandptOS10") != 0) {
		pfcandptOS10_branch = tree->GetBranch("pfcandptOS10");
		if (pfcandptOS10_branch) {pfcandptOS10_branch->SetAddress(&pfcandptOS10_);}
	}
	pfcandptOS10looseZ_branch = 0;
	if (tree->GetBranch("pfcandptOS10looseZ") != 0) {
		pfcandptOS10looseZ_branch = tree->GetBranch("pfcandptOS10looseZ");
		if (pfcandptOS10looseZ_branch) {pfcandptOS10looseZ_branch->SetAddress(&pfcandptOS10looseZ_);}
	}
	pfcandpt5looseZ_branch = 0;
	if (tree->GetBranch("pfcandpt5looseZ") != 0) {
		pfcandpt5looseZ_branch = tree->GetBranch("pfcandpt5looseZ");
		if (pfcandpt5looseZ_branch) {pfcandpt5looseZ_branch->SetAddress(&pfcandpt5looseZ_);}
	}
	pfcanddz5_branch = 0;
	if (tree->GetBranch("pfcanddz5") != 0) {
		pfcanddz5_branch = tree->GetBranch("pfcanddz5");
		if (pfcanddz5_branch) {pfcanddz5_branch->SetAddress(&pfcanddz5_);}
	}
	pfcanddz10_branch = 0;
	if (tree->GetBranch("pfcanddz10") != 0) {
		pfcanddz10_branch = tree->GetBranch("pfcanddz10");
		if (pfcanddz10_branch) {pfcanddz10_branch->SetAddress(&pfcanddz10_);}
	}
	pfcanddirdz10_branch = 0;
	if (tree->GetBranch("pfcanddirdz10") != 0) {
		pfcanddirdz10_branch = tree->GetBranch("pfcanddirdz10");
		if (pfcanddirdz10_branch) {pfcanddirdz10_branch->SetAddress(&pfcanddirdz10_);}
	}
	pfcandvetodz10_branch = 0;
	if (tree->GetBranch("pfcandvetodz10") != 0) {
		pfcandvetodz10_branch = tree->GetBranch("pfcandvetodz10");
		if (pfcandvetodz10_branch) {pfcandvetodz10_branch->SetAddress(&pfcandvetodz10_);}
	}
	pfcandvetoLdz10_branch = 0;
	if (tree->GetBranch("pfcandvetoLdz10") != 0) {
		pfcandvetoLdz10_branch = tree->GetBranch("pfcandvetoLdz10");
		if (pfcandvetoLdz10_branch) {pfcandvetoLdz10_branch->SetAddress(&pfcandvetoLdz10_);}
	}
	pfcanddzOS10_branch = 0;
	if (tree->GetBranch("pfcanddzOS10") != 0) {
		pfcanddzOS10_branch = tree->GetBranch("pfcanddzOS10");
		if (pfcanddzOS10_branch) {pfcanddzOS10_branch->SetAddress(&pfcanddzOS10_);}
	}
	pfcanddzOS10looseZ_branch = 0;
	if (tree->GetBranch("pfcanddzOS10looseZ") != 0) {
		pfcanddzOS10looseZ_branch = tree->GetBranch("pfcanddzOS10looseZ");
		if (pfcanddzOS10looseZ_branch) {pfcanddzOS10looseZ_branch->SetAddress(&pfcanddzOS10looseZ_);}
	}
	pfcanddz5looseZ_branch = 0;
	if (tree->GetBranch("pfcanddz5looseZ") != 0) {
		pfcanddz5looseZ_branch = tree->GetBranch("pfcanddz5looseZ");
		if (pfcanddz5looseZ_branch) {pfcanddz5looseZ_branch->SetAddress(&pfcanddz5looseZ_);}
	}
	pfcandmindrj5_branch = 0;
	if (tree->GetBranch("pfcandmindrj5") != 0) {
		pfcandmindrj5_branch = tree->GetBranch("pfcandmindrj5");
		if (pfcandmindrj5_branch) {pfcandmindrj5_branch->SetAddress(&pfcandmindrj5_);}
	}
	pfcandmindrj10_branch = 0;
	if (tree->GetBranch("pfcandmindrj10") != 0) {
		pfcandmindrj10_branch = tree->GetBranch("pfcandmindrj10");
		if (pfcandmindrj10_branch) {pfcandmindrj10_branch->SetAddress(&pfcandmindrj10_);}
	}
	pfcanddirmindrj10_branch = 0;
	if (tree->GetBranch("pfcanddirmindrj10") != 0) {
		pfcanddirmindrj10_branch = tree->GetBranch("pfcanddirmindrj10");
		if (pfcanddirmindrj10_branch) {pfcanddirmindrj10_branch->SetAddress(&pfcanddirmindrj10_);}
	}
	pfcandvetomindrj10_branch = 0;
	if (tree->GetBranch("pfcandvetomindrj10") != 0) {
		pfcandvetomindrj10_branch = tree->GetBranch("pfcandvetomindrj10");
		if (pfcandvetomindrj10_branch) {pfcandvetomindrj10_branch->SetAddress(&pfcandvetomindrj10_);}
	}
	pfcandvetoLmindrj10_branch = 0;
	if (tree->GetBranch("pfcandvetoLmindrj10") != 0) {
		pfcandvetoLmindrj10_branch = tree->GetBranch("pfcandvetoLmindrj10");
		if (pfcandvetoLmindrj10_branch) {pfcandvetoLmindrj10_branch->SetAddress(&pfcandvetoLmindrj10_);}
	}
	pfcandpt10pt0p1_branch = 0;
	if (tree->GetBranch("pfcandpt10pt0p1") != 0) {
		pfcandpt10pt0p1_branch = tree->GetBranch("pfcandpt10pt0p1");
		if (pfcandpt10pt0p1_branch) {pfcandpt10pt0p1_branch->SetAddress(&pfcandpt10pt0p1_);}
	}
	pfcandiso10pt0p1_branch = 0;
	if (tree->GetBranch("pfcandiso10pt0p1") != 0) {
		pfcandiso10pt0p1_branch = tree->GetBranch("pfcandiso10pt0p1");
		if (pfcandiso10pt0p1_branch) {pfcandiso10pt0p1_branch->SetAddress(&pfcandiso10pt0p1_);}
	}
	pfcandpt10pt0p2_branch = 0;
	if (tree->GetBranch("pfcandpt10pt0p2") != 0) {
		pfcandpt10pt0p2_branch = tree->GetBranch("pfcandpt10pt0p2");
		if (pfcandpt10pt0p2_branch) {pfcandpt10pt0p2_branch->SetAddress(&pfcandpt10pt0p2_);}
	}
	pfcandiso10pt0p2_branch = 0;
	if (tree->GetBranch("pfcandiso10pt0p2") != 0) {
		pfcandiso10pt0p2_branch = tree->GetBranch("pfcandiso10pt0p2");
		if (pfcandiso10pt0p2_branch) {pfcandiso10pt0p2_branch->SetAddress(&pfcandiso10pt0p2_);}
	}
	pfcandpt10pt0p3_branch = 0;
	if (tree->GetBranch("pfcandpt10pt0p3") != 0) {
		pfcandpt10pt0p3_branch = tree->GetBranch("pfcandpt10pt0p3");
		if (pfcandpt10pt0p3_branch) {pfcandpt10pt0p3_branch->SetAddress(&pfcandpt10pt0p3_);}
	}
	pfcandiso10pt0p3_branch = 0;
	if (tree->GetBranch("pfcandiso10pt0p3") != 0) {
		pfcandiso10pt0p3_branch = tree->GetBranch("pfcandiso10pt0p3");
		if (pfcandiso10pt0p3_branch) {pfcandiso10pt0p3_branch->SetAddress(&pfcandiso10pt0p3_);}
	}
	pfcandpt10pt0p4_branch = 0;
	if (tree->GetBranch("pfcandpt10pt0p4") != 0) {
		pfcandpt10pt0p4_branch = tree->GetBranch("pfcandpt10pt0p4");
		if (pfcandpt10pt0p4_branch) {pfcandpt10pt0p4_branch->SetAddress(&pfcandpt10pt0p4_);}
	}
	pfcandiso10pt0p4_branch = 0;
	if (tree->GetBranch("pfcandiso10pt0p4") != 0) {
		pfcandiso10pt0p4_branch = tree->GetBranch("pfcandiso10pt0p4");
		if (pfcandiso10pt0p4_branch) {pfcandiso10pt0p4_branch->SetAddress(&pfcandiso10pt0p4_);}
	}
	pfcandpt10pt0p5_branch = 0;
	if (tree->GetBranch("pfcandpt10pt0p5") != 0) {
		pfcandpt10pt0p5_branch = tree->GetBranch("pfcandpt10pt0p5");
		if (pfcandpt10pt0p5_branch) {pfcandpt10pt0p5_branch->SetAddress(&pfcandpt10pt0p5_);}
	}
	pfcandiso10pt0p5_branch = 0;
	if (tree->GetBranch("pfcandiso10pt0p5") != 0) {
		pfcandiso10pt0p5_branch = tree->GetBranch("pfcandiso10pt0p5");
		if (pfcandiso10pt0p5_branch) {pfcandiso10pt0p5_branch->SetAddress(&pfcandiso10pt0p5_);}
	}
	pfcandpt10pt0p6_branch = 0;
	if (tree->GetBranch("pfcandpt10pt0p6") != 0) {
		pfcandpt10pt0p6_branch = tree->GetBranch("pfcandpt10pt0p6");
		if (pfcandpt10pt0p6_branch) {pfcandpt10pt0p6_branch->SetAddress(&pfcandpt10pt0p6_);}
	}
	pfcandiso10pt0p6_branch = 0;
	if (tree->GetBranch("pfcandiso10pt0p6") != 0) {
		pfcandiso10pt0p6_branch = tree->GetBranch("pfcandiso10pt0p6");
		if (pfcandiso10pt0p6_branch) {pfcandiso10pt0p6_branch->SetAddress(&pfcandiso10pt0p6_);}
	}
	pfcandpt10pt0p7_branch = 0;
	if (tree->GetBranch("pfcandpt10pt0p7") != 0) {
		pfcandpt10pt0p7_branch = tree->GetBranch("pfcandpt10pt0p7");
		if (pfcandpt10pt0p7_branch) {pfcandpt10pt0p7_branch->SetAddress(&pfcandpt10pt0p7_);}
	}
	pfcandiso10pt0p7_branch = 0;
	if (tree->GetBranch("pfcandiso10pt0p7") != 0) {
		pfcandiso10pt0p7_branch = tree->GetBranch("pfcandiso10pt0p7");
		if (pfcandiso10pt0p7_branch) {pfcandiso10pt0p7_branch->SetAddress(&pfcandiso10pt0p7_);}
	}
	pfcandpt10pt0p8_branch = 0;
	if (tree->GetBranch("pfcandpt10pt0p8") != 0) {
		pfcandpt10pt0p8_branch = tree->GetBranch("pfcandpt10pt0p8");
		if (pfcandpt10pt0p8_branch) {pfcandpt10pt0p8_branch->SetAddress(&pfcandpt10pt0p8_);}
	}
	pfcandiso10pt0p8_branch = 0;
	if (tree->GetBranch("pfcandiso10pt0p8") != 0) {
		pfcandiso10pt0p8_branch = tree->GetBranch("pfcandiso10pt0p8");
		if (pfcandiso10pt0p8_branch) {pfcandiso10pt0p8_branch->SetAddress(&pfcandiso10pt0p8_);}
	}
	pfcandpt10pt0p9_branch = 0;
	if (tree->GetBranch("pfcandpt10pt0p9") != 0) {
		pfcandpt10pt0p9_branch = tree->GetBranch("pfcandpt10pt0p9");
		if (pfcandpt10pt0p9_branch) {pfcandpt10pt0p9_branch->SetAddress(&pfcandpt10pt0p9_);}
	}
	pfcandiso10pt0p9_branch = 0;
	if (tree->GetBranch("pfcandiso10pt0p9") != 0) {
		pfcandiso10pt0p9_branch = tree->GetBranch("pfcandiso10pt0p9");
		if (pfcandiso10pt0p9_branch) {pfcandiso10pt0p9_branch->SetAddress(&pfcandiso10pt0p9_);}
	}
	pfcandpt10pt1p0_branch = 0;
	if (tree->GetBranch("pfcandpt10pt1p0") != 0) {
		pfcandpt10pt1p0_branch = tree->GetBranch("pfcandpt10pt1p0");
		if (pfcandpt10pt1p0_branch) {pfcandpt10pt1p0_branch->SetAddress(&pfcandpt10pt1p0_);}
	}
	pfcandiso10pt1p0_branch = 0;
	if (tree->GetBranch("pfcandiso10pt1p0") != 0) {
		pfcandiso10pt1p0_branch = tree->GetBranch("pfcandiso10pt1p0");
		if (pfcandiso10pt1p0_branch) {pfcandiso10pt1p0_branch->SetAddress(&pfcandiso10pt1p0_);}
	}
	pfTau15_leadPtcandID_branch = 0;
	if (tree->GetBranch("pfTau15_leadPtcandID") != 0) {
		pfTau15_leadPtcandID_branch = tree->GetBranch("pfTau15_leadPtcandID");
		if (pfTau15_leadPtcandID_branch) {pfTau15_leadPtcandID_branch->SetAddress(&pfTau15_leadPtcandID_);}
	}
	pfTau_leadPtcandID_branch = 0;
	if (tree->GetBranch("pfTau_leadPtcandID") != 0) {
		pfTau_leadPtcandID_branch = tree->GetBranch("pfTau_leadPtcandID");
		if (pfTau_leadPtcandID_branch) {pfTau_leadPtcandID_branch->SetAddress(&pfTau_leadPtcandID_);}
	}
	pfTauLoose_leadPtcandID_branch = 0;
	if (tree->GetBranch("pfTauLoose_leadPtcandID") != 0) {
		pfTauLoose_leadPtcandID_branch = tree->GetBranch("pfTauLoose_leadPtcandID");
		if (pfTauLoose_leadPtcandID_branch) {pfTauLoose_leadPtcandID_branch->SetAddress(&pfTauLoose_leadPtcandID_);}
	}
	pfjets_beta_branch = 0;
	if (tree->GetBranch("pfjets_beta") != 0) {
		pfjets_beta_branch = tree->GetBranch("pfjets_beta");
		if (pfjets_beta_branch) {pfjets_beta_branch->SetAddress(&pfjets_beta_);}
	}
	pfjets_beta2_branch = 0;
	if (tree->GetBranch("pfjets_beta2") != 0) {
		pfjets_beta2_branch = tree->GetBranch("pfjets_beta2");
		if (pfjets_beta2_branch) {pfjets_beta2_branch->SetAddress(&pfjets_beta2_);}
	}
	pfjets_beta_0p1_branch = 0;
	if (tree->GetBranch("pfjets_beta_0p1") != 0) {
		pfjets_beta_0p1_branch = tree->GetBranch("pfjets_beta_0p1");
		if (pfjets_beta_0p1_branch) {pfjets_beta_0p1_branch->SetAddress(&pfjets_beta_0p1_);}
	}
	pfjets_beta_0p2_branch = 0;
	if (tree->GetBranch("pfjets_beta_0p2") != 0) {
		pfjets_beta_0p2_branch = tree->GetBranch("pfjets_beta_0p2");
		if (pfjets_beta_0p2_branch) {pfjets_beta_0p2_branch->SetAddress(&pfjets_beta_0p2_);}
	}
	pfjets_beta2_0p1_branch = 0;
	if (tree->GetBranch("pfjets_beta2_0p1") != 0) {
		pfjets_beta2_0p1_branch = tree->GetBranch("pfjets_beta2_0p1");
		if (pfjets_beta2_0p1_branch) {pfjets_beta2_0p1_branch->SetAddress(&pfjets_beta2_0p1_);}
	}
	pfjets_beta2_0p5_branch = 0;
	if (tree->GetBranch("pfjets_beta2_0p5") != 0) {
		pfjets_beta2_0p5_branch = tree->GetBranch("pfjets_beta2_0p5");
		if (pfjets_beta2_0p5_branch) {pfjets_beta2_0p5_branch->SetAddress(&pfjets_beta2_0p5_);}
	}
	pfjets_mvaPUid_branch = 0;
	if (tree->GetBranch("pfjets_mvaPUid") != 0) {
		pfjets_mvaPUid_branch = tree->GetBranch("pfjets_mvaPUid");
		if (pfjets_mvaPUid_branch) {pfjets_mvaPUid_branch->SetAddress(&pfjets_mvaPUid_);}
	}
	pfjets_mva5xPUid_branch = 0;
	if (tree->GetBranch("pfjets_mva5xPUid") != 0) {
		pfjets_mva5xPUid_branch = tree->GetBranch("pfjets_mva5xPUid");
		if (pfjets_mva5xPUid_branch) {pfjets_mva5xPUid_branch->SetAddress(&pfjets_mva5xPUid_);}
	}
	pfjets_mvaBeta_branch = 0;
	if (tree->GetBranch("pfjets_mvaBeta") != 0) {
		pfjets_mvaBeta_branch = tree->GetBranch("pfjets_mvaBeta");
		if (pfjets_mvaBeta_branch) {pfjets_mvaBeta_branch->SetAddress(&pfjets_mvaBeta_);}
	}
	passes_isotrk_veto_branch = 0;
	if (tree->GetBranch("passes_isotrk_veto") != 0) {
		passes_isotrk_veto_branch = tree->GetBranch("passes_isotrk_veto");
		if (passes_isotrk_veto_branch) {passes_isotrk_veto_branch->SetAddress(&passes_isotrk_veto_);}
	}
	passes_tau_veto_branch = 0;
	if (tree->GetBranch("passes_tau_veto") != 0) {
		passes_tau_veto_branch = tree->GetBranch("passes_tau_veto");
		if (passes_tau_veto_branch) {passes_tau_veto_branch->SetAddress(&passes_tau_veto_);}
	}
	njets_pv_tight0_branch = 0;
	if (tree->GetBranch("njets_pv_tight0") != 0) {
		njets_pv_tight0_branch = tree->GetBranch("njets_pv_tight0");
		if (njets_pv_tight0_branch) {njets_pv_tight0_branch->SetAddress(&njets_pv_tight0_);}
	}
	njets_pv_tight1_branch = 0;
	if (tree->GetBranch("njets_pv_tight1") != 0) {
		njets_pv_tight1_branch = tree->GetBranch("njets_pv_tight1");
		if (njets_pv_tight1_branch) {njets_pv_tight1_branch->SetAddress(&njets_pv_tight1_);}
	}
	njets_pv_tight2_branch = 0;
	if (tree->GetBranch("njets_pv_tight2") != 0) {
		njets_pv_tight2_branch = tree->GetBranch("njets_pv_tight2");
		if (njets_pv_tight2_branch) {njets_pv_tight2_branch->SetAddress(&njets_pv_tight2_);}
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
		uncorpfmet_isLoaded = false;
		uncorpfmet_phi_isLoaded = false;
		pu_nvtxs_isLoaded = false;
		pu_ntrueint_isLoaded = false;
		scale1fb_isLoaded = false;
		xsec_isLoaded = false;
		nevts_isLoaded = false;
		kfactor_isLoaded = false;
		gen_met_isLoaded = false;
		gen_met_phi_isLoaded = false;
		dataset_isLoaded = false;
		filename_isLoaded = false;
		filt_csc_isLoaded = false;
		filt_hbhe_isLoaded = false;
		filt_hcallaser_isLoaded = false;
		filt_ecallaser_isLoaded = false;
		filt_ecaltp_isLoaded = false;
		filt_trkfail_isLoaded = false;
		filt_eebadsc_isLoaded = false;
		passes_metfilters_isLoaded = false;
		lep1_passes_id_isLoaded = false;
		lep1_passes_iso_isLoaded = false;
		lep1_is_num_isLoaded = false;
		lep1_is_den_isLoaded = false;
		lep1_is_fo_isLoaded = false;
		lep1_is_fromw_isLoaded = false;
		lep1_charge_isLoaded = false;
		lep1_pdgid_isLoaded = false;
		lep1_type_isLoaded = false;
		lep1_d0_isLoaded = false;
		lep1_d0err_isLoaded = false;
		lep1_dz_isLoaded = false;
		lep1_ip3d_isLoaded = false;
		lep1_ip3derr_isLoaded = false;
		lep1_dzerr_isLoaded = false;
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
		lep1_mcid_isLoaded = false;
		lep1_mc3id_isLoaded = false;
		lep1_momid_isLoaded = false;
		lep1_mc3_momid_isLoaded = false;
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
		lep1_p4_isLoaded = false;
		lep1_mcp4_isLoaded = false;
		lep1_mc3p4_isLoaded = false;
		lep1_mc_momp4_isLoaded = false;
		lep1_gsf_p4_isLoaded = false;
		lep1_ctf_p4_isLoaded = false;
		lep1_sc_p4_isLoaded = false;
		lep1_gfit_p4_isLoaded = false;
		lep2_passes_id_isLoaded = false;
		lep2_passes_iso_isLoaded = false;
		lep2_is_num_isLoaded = false;
		lep2_is_den_isLoaded = false;
		lep2_is_fo_isLoaded = false;
		lep2_is_fromw_isLoaded = false;
		lep2_charge_isLoaded = false;
		lep2_pdgid_isLoaded = false;
		lep2_type_isLoaded = false;
		lep2_d0_isLoaded = false;
		lep2_d0err_isLoaded = false;
		lep2_dz_isLoaded = false;
		lep2_ip3d_isLoaded = false;
		lep2_ip3derr_isLoaded = false;
		lep2_dzerr_isLoaded = false;
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
		lep2_mcid_isLoaded = false;
		lep2_mc3id_isLoaded = false;
		lep2_momid_isLoaded = false;
		lep2_mc3_momid_isLoaded = false;
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
		lep2_p4_isLoaded = false;
		lep2_mcp4_isLoaded = false;
		lep2_mc3p4_isLoaded = false;
		lep2_mc_momp4_isLoaded = false;
		lep2_gsf_p4_isLoaded = false;
		lep2_ctf_p4_isLoaded = false;
		lep2_sc_p4_isLoaded = false;
		lep2_gfit_p4_isLoaded = false;
		dilep_p4_isLoaded = false;
		os_isLoaded = false;
		ss_isLoaded = false;
		mm_isLoaded = false;
		ee_isLoaded = false;
		em_isLoaded = false;
		dilep_type_isLoaded = false;
		dilep_gen_type_isLoaded = false;
		dilep_mass_isLoaded = false;
		dilep_dphi_isLoaded = false;
		dilep_deta_isLoaded = false;
		dilep_dr_isLoaded = false;
		fiduciality_isLoaded = false;
		lep3_passes_id_isLoaded = false;
		lep3_passes_iso_isLoaded = false;
		lep3_is_num_isLoaded = false;
		lep3_is_den_isLoaded = false;
		lep3_is_fo_isLoaded = false;
		lep3_is_fromw_isLoaded = false;
		lep3_charge_isLoaded = false;
		lep3_pdgid_isLoaded = false;
		lep3_type_isLoaded = false;
		lep3_d0_isLoaded = false;
		lep3_d0err_isLoaded = false;
		lep3_dz_isLoaded = false;
		lep3_ip3d_isLoaded = false;
		lep3_ip3derr_isLoaded = false;
		lep3_dzerr_isLoaded = false;
		lep3_mt_isLoaded = false;
		lep3_corpfiso_isLoaded = false;
		lep3_pfiso_isLoaded = false;
		lep3_chiso_isLoaded = false;
		lep3_emiso_isLoaded = false;
		lep3_nhiso_isLoaded = false;
		lep3_corpfiso04_isLoaded = false;
		lep3_pfiso04_isLoaded = false;
		lep3_chiso04_isLoaded = false;
		lep3_emiso04_isLoaded = false;
		lep3_nhiso04_isLoaded = false;
		lep3_cordetiso_isLoaded = false;
		lep3_detiso_isLoaded = false;
		lep3_trkiso_isLoaded = false;
		lep3_ecaliso_isLoaded = false;
		lep3_hcaliso_isLoaded = false;
		lep3_cordetiso04_isLoaded = false;
		lep3_detiso04_isLoaded = false;
		lep3_trkiso04_isLoaded = false;
		lep3_ecaliso04_isLoaded = false;
		lep3_hcaliso04_isLoaded = false;
		lep3_effarea_isLoaded = false;
		lep3_effarea04_isLoaded = false;
		lep3_dbeta_isLoaded = false;
		lep3_dbeta04_isLoaded = false;
		lep3_sf_lepeff_isLoaded = false;
		lep3_sf_trig_isLoaded = false;
		lep3_mcid_isLoaded = false;
		lep3_mc3id_isLoaded = false;
		lep3_momid_isLoaded = false;
		lep3_mc3_momid_isLoaded = false;
		lep3_q3agree_isLoaded = false;
		lep3_is_conv_isLoaded = false;
		lep3_qsc_isLoaded = false;
		lep3_qctf_isLoaded = false;
		lep3_qgsf_isLoaded = false;
		lep3_nmhits_isLoaded = false;
		lep3_eleid_veto_isLoaded = false;
		lep3_eleid_loose_isLoaded = false;
		lep3_eleid_medium_isLoaded = false;
		lep3_eleid_tight_isLoaded = false;
		lep3_dphiin_isLoaded = false;
		lep3_detain_isLoaded = false;
		lep3_sieie_isLoaded = false;
		lep3_hoe_isLoaded = false;
		lep3_ooemoop_isLoaded = false;
		lep3_conv_dist_isLoaded = false;
		lep3_conv_dcot_isLoaded = false;
		lep3_is_global_isLoaded = false;
		lep3_is_tracker_isLoaded = false;
		lep3_is_stamu_isLoaded = false;
		lep3_is_pfmu_isLoaded = false;
		lep3_is_loosemu_isLoaded = false;
		lep3_is_tightmu_isLoaded = false;
		lep3_npixelhits_isLoaded = false;
		lep3_nsihits_isLoaded = false;
		lep3_nsilayers_isLoaded = false;
		lep3_nstahits_isLoaded = false;
		lep3_nstations_isLoaded = false;
		lep3_chi2_isLoaded = false;
		lep3_ndof_isLoaded = false;
		lep3_pterr_isLoaded = false;
		lep3_ecal_vetodep_isLoaded = false;
		lep3_hcal_vetodep_isLoaded = false;
		lep3_p4_isLoaded = false;
		lep3_mcp4_isLoaded = false;
		lep3_mc3p4_isLoaded = false;
		lep3_mc_momp4_isLoaded = false;
		lep3_gsf_p4_isLoaded = false;
		lep3_ctf_p4_isLoaded = false;
		lep3_sc_p4_isLoaded = false;
		lep3_gfit_p4_isLoaded = false;
		selection_isLoaded = false;
		is_good_lumi_isLoaded = false;
		charge_type_isLoaded = false;
		njets_isLoaded = false;
		nbtags_isLoaded = false;
		nbtags_loose_isLoaded = false;
		ttbar_bkdn_isLoaded = false;
		vtxw_isLoaded = false;
		mt_isLoaded = false;
		mt2_isLoaded = false;
		ht_isLoaded = false;
		rho_isLoaded = false;
		rho_iso_isLoaded = false;
		trig_mm_isLoaded = false;
		trig_em_isLoaded = false;
		trig_ee_isLoaded = false;
		trig_mm_mu17_mu8_isLoaded = false;
		trig_ee_el17_el8_id_iso_isLoaded = false;
		trig_em_mu17_el8_id_iso_isLoaded = false;
		trig_em_mu8_el17_id_iso_isLoaded = false;
		njets_dn_isLoaded = false;
		njets_up_isLoaded = false;
		nbtags_dn_isLoaded = false;
		nbtags_up_isLoaded = false;
		ht_dn_isLoaded = false;
		ht_up_isLoaded = false;
		nbtags_reweighted_isLoaded = false;
		nbtags_reweighted_dn_isLoaded = false;
		nbtags_reweighted_up_isLoaded = false;
		nbtags_reweighted_jec_dn_isLoaded = false;
		nbtags_reweighted_jec_up_isLoaded = false;
		pfmet_dn_isLoaded = false;
		pfmet_up_isLoaded = false;
		pfmet_phi_dn_isLoaded = false;
		pfmet_phi_up_isLoaded = false;
		sf_dileptrig_isLoaded = false;
		sf_lepeff_isLoaded = false;
		sparm0_isLoaded = false;
		sparm1_isLoaded = false;
		sparm2_isLoaded = false;
		sparm3_isLoaded = false;
		sparm0_name_isLoaded = false;
		sparm1_name_isLoaded = false;
		sparm2_name_isLoaded = false;
		sparm3_name_isLoaded = false;
		is_pp_isLoaded = false;
		is_mm_isLoaded = false;
		is_ss_isLoaded = false;
		is_sf_isLoaded = false;
		is_df_isLoaded = false;
		is_os_isLoaded = false;
		no_extraz_isLoaded = false;
		no_extrag_isLoaded = false;
		clean_isLoaded = false;
		presel_isLoaded = false;
		em_mufo_isLoaded = false;
		em_elfo_isLoaded = false;
		hyp_good_vtx_isLoaded = false;
		is_gen_pp_isLoaded = false;
		is_gen_mm_isLoaded = false;
		gen_njets_isLoaded = false;
		gen_nleps_isLoaded = false;
		gen_nmus_isLoaded = false;
		gen_nels_isLoaded = false;
		gen_ntaus_isLoaded = false;
		gen_ht_isLoaded = false;
		lep1_nearjet_p4_isLoaded = false;
		lep1_nearlep_p4_isLoaded = false;
		lep1_wfr_isLoaded = false;
		lep1_wflip_isLoaded = false;
		lep1_nearjet_dr_isLoaded = false;
		lep1_nearlep_dr_isLoaded = false;
		lep1_nearlep_id_isLoaded = false;
		lep1_isFromH_isLoaded = false;
		lep2_nearjet_p4_isLoaded = false;
		lep2_nearlep_p4_isLoaded = false;
		lep2_wfr_isLoaded = false;
		lep2_wflip_isLoaded = false;
		lep2_nearjet_dr_isLoaded = false;
		lep2_nearlep_dr_isLoaded = false;
		lep2_nearlep_id_isLoaded = false;
		lep2_isFromH_isLoaded = false;
		jets_dr12_isLoaded = false;
		dijet_mass_isLoaded = false;
		vjets_p4_isLoaded = false;
		vjets_p4_up_isLoaded = false;
		vjets_p4_dn_isLoaded = false;
		vjets_mcflavor_phys_isLoaded = false;
		vjets_mcflavor_algo_isLoaded = false;
		vjets_mcflavor_phys_up_isLoaded = false;
		vjets_mcflavor_algo_up_isLoaded = false;
		vjets_mcflavor_phys_dn_isLoaded = false;
		vjets_mcflavor_algo_dn_isLoaded = false;
		vjets_mc3p4_isLoaded = false;
		vgenjets_p4_isLoaded = false;
		vjets_mc3id_isLoaded = false;
		vjets_momid_isLoaded = false;
		vjets_nearjet_p4_isLoaded = false;
		vjets_nearjet_dr_isLoaded = false;
		vjets_bdisc_isLoaded = false;
		gen_lep1_p4_isLoaded = false;
		gen_lep1_pdgid_isLoaded = false;
		gen_lep2_p4_isLoaded = false;
		gen_lep2_pdgid_isLoaded = false;
		gen_dilep_p4_isLoaded = false;
		gen_dilep_type_isLoaded = false;
		gen_dilep_mass_isLoaded = false;
		gen_dilep_dphi_isLoaded = false;
		gen_dilep_deta_isLoaded = false;
		gen_dilep_dr_isLoaded = false;
		pfcandid5_isLoaded = false;
		pfcandid10_isLoaded = false;
		pfcanddirid10_isLoaded = false;
		pfcandvetoid10_isLoaded = false;
		pfcandvetoLid10_isLoaded = false;
		pfcandidOS10_isLoaded = false;
		pfcandidOS10looseZ_isLoaded = false;
		pfcandid5looseZ_isLoaded = false;
		trkpt5_isLoaded = false;
		mleptrk5_isLoaded = false;
		trkreliso5_isLoaded = false;
		trkpt10_isLoaded = false;
		mleptrk10_isLoaded = false;
		trkreliso10_isLoaded = false;
		trkpt5loose_isLoaded = false;
		trkreliso5loose_isLoaded = false;
		trkpt10loose_isLoaded = false;
		trkreliso10loose_isLoaded = false;
		trkpt10pt0p1_isLoaded = false;
		trkreliso10pt0p1_isLoaded = false;
		trkpt10pt0p2_isLoaded = false;
		trkreliso10pt0p2_isLoaded = false;
		trkpt10pt0p3_isLoaded = false;
		trkreliso10pt0p3_isLoaded = false;
		trkpt10pt0p4_isLoaded = false;
		trkreliso10pt0p4_isLoaded = false;
		trkpt10pt0p5_isLoaded = false;
		trkreliso10pt0p5_isLoaded = false;
		trkpt10pt0p6_isLoaded = false;
		trkreliso10pt0p6_isLoaded = false;
		trkpt10pt0p7_isLoaded = false;
		trkreliso10pt0p7_isLoaded = false;
		trkpt10pt0p8_isLoaded = false;
		trkreliso10pt0p8_isLoaded = false;
		trkpt10pt0p9_isLoaded = false;
		trkreliso10pt0p9_isLoaded = false;
		trkpt10pt1p0_isLoaded = false;
		trkreliso10pt1p0_isLoaded = false;
		pfcandiso5_isLoaded = false;
		pfcandiso10_isLoaded = false;
		pfcanddiriso10_isLoaded = false;
		pfcandvetoiso10_isLoaded = false;
		pfcandvetoLiso10_isLoaded = false;
		pfcandisoOS10_isLoaded = false;
		pfcandisoOS10looseZ_isLoaded = false;
		pfcandiso5looseZ_isLoaded = false;
		pfcandpt5_isLoaded = false;
		pfcandpt10_isLoaded = false;
		pfcanddirpt10_isLoaded = false;
		pfcandvetopt10_isLoaded = false;
		pfcandvetoLpt10_isLoaded = false;
		pfcandptOS10_isLoaded = false;
		pfcandptOS10looseZ_isLoaded = false;
		pfcandpt5looseZ_isLoaded = false;
		pfcanddz5_isLoaded = false;
		pfcanddz10_isLoaded = false;
		pfcanddirdz10_isLoaded = false;
		pfcandvetodz10_isLoaded = false;
		pfcandvetoLdz10_isLoaded = false;
		pfcanddzOS10_isLoaded = false;
		pfcanddzOS10looseZ_isLoaded = false;
		pfcanddz5looseZ_isLoaded = false;
		pfcandmindrj5_isLoaded = false;
		pfcandmindrj10_isLoaded = false;
		pfcanddirmindrj10_isLoaded = false;
		pfcandvetomindrj10_isLoaded = false;
		pfcandvetoLmindrj10_isLoaded = false;
		pfcandpt10pt0p1_isLoaded = false;
		pfcandiso10pt0p1_isLoaded = false;
		pfcandpt10pt0p2_isLoaded = false;
		pfcandiso10pt0p2_isLoaded = false;
		pfcandpt10pt0p3_isLoaded = false;
		pfcandiso10pt0p3_isLoaded = false;
		pfcandpt10pt0p4_isLoaded = false;
		pfcandiso10pt0p4_isLoaded = false;
		pfcandpt10pt0p5_isLoaded = false;
		pfcandiso10pt0p5_isLoaded = false;
		pfcandpt10pt0p6_isLoaded = false;
		pfcandiso10pt0p6_isLoaded = false;
		pfcandpt10pt0p7_isLoaded = false;
		pfcandiso10pt0p7_isLoaded = false;
		pfcandpt10pt0p8_isLoaded = false;
		pfcandiso10pt0p8_isLoaded = false;
		pfcandpt10pt0p9_isLoaded = false;
		pfcandiso10pt0p9_isLoaded = false;
		pfcandpt10pt1p0_isLoaded = false;
		pfcandiso10pt1p0_isLoaded = false;
		pfcand5_isLoaded = false;
		pfcand10_isLoaded = false;
		pfcanddir10_isLoaded = false;
		pfcandveto10_isLoaded = false;
		pfcandvetoL10_isLoaded = false;
		pfcandOS10_isLoaded = false;
		pfcandOS10looseZ_isLoaded = false;
		pfcand5looseZ_isLoaded = false;
		pfTau15_leadPtcandID_isLoaded = false;
		pfTau_leadPtcandID_isLoaded = false;
		pfTauLoose_leadPtcandID_isLoaded = false;
		pfTau15_isLoaded = false;
		pfTau15_leadPtcand_isLoaded = false;
		pfTau_isLoaded = false;
		pfTau_leadPtcand_isLoaded = false;
		pfTauLoose_isLoaded = false;
		pfTauLoose_leadPtcand_isLoaded = false;
		pfjets_beta_isLoaded = false;
		pfjets_beta2_isLoaded = false;
		pfjets_beta_0p1_isLoaded = false;
		pfjets_beta_0p2_isLoaded = false;
		pfjets_beta2_0p1_isLoaded = false;
		pfjets_beta2_0p5_isLoaded = false;
		pfjets_mvaPUid_isLoaded = false;
		pfjets_mva5xPUid_isLoaded = false;
		pfjets_mvaBeta_isLoaded = false;
		passes_isotrk_veto_isLoaded = false;
		passes_tau_veto_isLoaded = false;
		njets_pv_tight0_isLoaded = false;
		njets_pv_tight1_isLoaded = false;
		njets_pv_tight2_isLoaded = false;
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
	if (uncorpfmet_branch != 0) uncorpfmet();
	if (uncorpfmet_phi_branch != 0) uncorpfmet_phi();
	if (pu_nvtxs_branch != 0) pu_nvtxs();
	if (pu_ntrueint_branch != 0) pu_ntrueint();
	if (scale1fb_branch != 0) scale1fb();
	if (xsec_branch != 0) xsec();
	if (nevts_branch != 0) nevts();
	if (kfactor_branch != 0) kfactor();
	if (gen_met_branch != 0) gen_met();
	if (gen_met_phi_branch != 0) gen_met_phi();
	if (dataset_branch != 0) dataset();
	if (filename_branch != 0) filename();
	if (filt_csc_branch != 0) filt_csc();
	if (filt_hbhe_branch != 0) filt_hbhe();
	if (filt_hcallaser_branch != 0) filt_hcallaser();
	if (filt_ecallaser_branch != 0) filt_ecallaser();
	if (filt_ecaltp_branch != 0) filt_ecaltp();
	if (filt_trkfail_branch != 0) filt_trkfail();
	if (filt_eebadsc_branch != 0) filt_eebadsc();
	if (passes_metfilters_branch != 0) passes_metfilters();
	if (lep1_passes_id_branch != 0) lep1_passes_id();
	if (lep1_passes_iso_branch != 0) lep1_passes_iso();
	if (lep1_is_num_branch != 0) lep1_is_num();
	if (lep1_is_den_branch != 0) lep1_is_den();
	if (lep1_is_fo_branch != 0) lep1_is_fo();
	if (lep1_is_fromw_branch != 0) lep1_is_fromw();
	if (lep1_charge_branch != 0) lep1_charge();
	if (lep1_pdgid_branch != 0) lep1_pdgid();
	if (lep1_type_branch != 0) lep1_type();
	if (lep1_d0_branch != 0) lep1_d0();
	if (lep1_d0err_branch != 0) lep1_d0err();
	if (lep1_dz_branch != 0) lep1_dz();
	if (lep1_ip3d_branch != 0) lep1_ip3d();
	if (lep1_ip3derr_branch != 0) lep1_ip3derr();
	if (lep1_dzerr_branch != 0) lep1_dzerr();
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
	if (lep1_mcid_branch != 0) lep1_mcid();
	if (lep1_mc3id_branch != 0) lep1_mc3id();
	if (lep1_momid_branch != 0) lep1_momid();
	if (lep1_mc3_momid_branch != 0) lep1_mc3_momid();
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
	if (lep1_p4_branch != 0) lep1_p4();
	if (lep1_mcp4_branch != 0) lep1_mcp4();
	if (lep1_mc3p4_branch != 0) lep1_mc3p4();
	if (lep1_mc_momp4_branch != 0) lep1_mc_momp4();
	if (lep1_gsf_p4_branch != 0) lep1_gsf_p4();
	if (lep1_ctf_p4_branch != 0) lep1_ctf_p4();
	if (lep1_sc_p4_branch != 0) lep1_sc_p4();
	if (lep1_gfit_p4_branch != 0) lep1_gfit_p4();
	if (lep2_passes_id_branch != 0) lep2_passes_id();
	if (lep2_passes_iso_branch != 0) lep2_passes_iso();
	if (lep2_is_num_branch != 0) lep2_is_num();
	if (lep2_is_den_branch != 0) lep2_is_den();
	if (lep2_is_fo_branch != 0) lep2_is_fo();
	if (lep2_is_fromw_branch != 0) lep2_is_fromw();
	if (lep2_charge_branch != 0) lep2_charge();
	if (lep2_pdgid_branch != 0) lep2_pdgid();
	if (lep2_type_branch != 0) lep2_type();
	if (lep2_d0_branch != 0) lep2_d0();
	if (lep2_d0err_branch != 0) lep2_d0err();
	if (lep2_dz_branch != 0) lep2_dz();
	if (lep2_ip3d_branch != 0) lep2_ip3d();
	if (lep2_ip3derr_branch != 0) lep2_ip3derr();
	if (lep2_dzerr_branch != 0) lep2_dzerr();
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
	if (lep2_mcid_branch != 0) lep2_mcid();
	if (lep2_mc3id_branch != 0) lep2_mc3id();
	if (lep2_momid_branch != 0) lep2_momid();
	if (lep2_mc3_momid_branch != 0) lep2_mc3_momid();
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
	if (lep2_p4_branch != 0) lep2_p4();
	if (lep2_mcp4_branch != 0) lep2_mcp4();
	if (lep2_mc3p4_branch != 0) lep2_mc3p4();
	if (lep2_mc_momp4_branch != 0) lep2_mc_momp4();
	if (lep2_gsf_p4_branch != 0) lep2_gsf_p4();
	if (lep2_ctf_p4_branch != 0) lep2_ctf_p4();
	if (lep2_sc_p4_branch != 0) lep2_sc_p4();
	if (lep2_gfit_p4_branch != 0) lep2_gfit_p4();
	if (dilep_p4_branch != 0) dilep_p4();
	if (os_branch != 0) os();
	if (ss_branch != 0) ss();
	if (mm_branch != 0) mm();
	if (ee_branch != 0) ee();
	if (em_branch != 0) em();
	if (dilep_type_branch != 0) dilep_type();
	if (dilep_gen_type_branch != 0) dilep_gen_type();
	if (dilep_mass_branch != 0) dilep_mass();
	if (dilep_dphi_branch != 0) dilep_dphi();
	if (dilep_deta_branch != 0) dilep_deta();
	if (dilep_dr_branch != 0) dilep_dr();
	if (fiduciality_branch != 0) fiduciality();
	if (lep3_passes_id_branch != 0) lep3_passes_id();
	if (lep3_passes_iso_branch != 0) lep3_passes_iso();
	if (lep3_is_num_branch != 0) lep3_is_num();
	if (lep3_is_den_branch != 0) lep3_is_den();
	if (lep3_is_fo_branch != 0) lep3_is_fo();
	if (lep3_is_fromw_branch != 0) lep3_is_fromw();
	if (lep3_charge_branch != 0) lep3_charge();
	if (lep3_pdgid_branch != 0) lep3_pdgid();
	if (lep3_type_branch != 0) lep3_type();
	if (lep3_d0_branch != 0) lep3_d0();
	if (lep3_d0err_branch != 0) lep3_d0err();
	if (lep3_dz_branch != 0) lep3_dz();
	if (lep3_ip3d_branch != 0) lep3_ip3d();
	if (lep3_ip3derr_branch != 0) lep3_ip3derr();
	if (lep3_dzerr_branch != 0) lep3_dzerr();
	if (lep3_mt_branch != 0) lep3_mt();
	if (lep3_corpfiso_branch != 0) lep3_corpfiso();
	if (lep3_pfiso_branch != 0) lep3_pfiso();
	if (lep3_chiso_branch != 0) lep3_chiso();
	if (lep3_emiso_branch != 0) lep3_emiso();
	if (lep3_nhiso_branch != 0) lep3_nhiso();
	if (lep3_corpfiso04_branch != 0) lep3_corpfiso04();
	if (lep3_pfiso04_branch != 0) lep3_pfiso04();
	if (lep3_chiso04_branch != 0) lep3_chiso04();
	if (lep3_emiso04_branch != 0) lep3_emiso04();
	if (lep3_nhiso04_branch != 0) lep3_nhiso04();
	if (lep3_cordetiso_branch != 0) lep3_cordetiso();
	if (lep3_detiso_branch != 0) lep3_detiso();
	if (lep3_trkiso_branch != 0) lep3_trkiso();
	if (lep3_ecaliso_branch != 0) lep3_ecaliso();
	if (lep3_hcaliso_branch != 0) lep3_hcaliso();
	if (lep3_cordetiso04_branch != 0) lep3_cordetiso04();
	if (lep3_detiso04_branch != 0) lep3_detiso04();
	if (lep3_trkiso04_branch != 0) lep3_trkiso04();
	if (lep3_ecaliso04_branch != 0) lep3_ecaliso04();
	if (lep3_hcaliso04_branch != 0) lep3_hcaliso04();
	if (lep3_effarea_branch != 0) lep3_effarea();
	if (lep3_effarea04_branch != 0) lep3_effarea04();
	if (lep3_dbeta_branch != 0) lep3_dbeta();
	if (lep3_dbeta04_branch != 0) lep3_dbeta04();
	if (lep3_sf_lepeff_branch != 0) lep3_sf_lepeff();
	if (lep3_sf_trig_branch != 0) lep3_sf_trig();
	if (lep3_mcid_branch != 0) lep3_mcid();
	if (lep3_mc3id_branch != 0) lep3_mc3id();
	if (lep3_momid_branch != 0) lep3_momid();
	if (lep3_mc3_momid_branch != 0) lep3_mc3_momid();
	if (lep3_q3agree_branch != 0) lep3_q3agree();
	if (lep3_is_conv_branch != 0) lep3_is_conv();
	if (lep3_qsc_branch != 0) lep3_qsc();
	if (lep3_qctf_branch != 0) lep3_qctf();
	if (lep3_qgsf_branch != 0) lep3_qgsf();
	if (lep3_nmhits_branch != 0) lep3_nmhits();
	if (lep3_eleid_veto_branch != 0) lep3_eleid_veto();
	if (lep3_eleid_loose_branch != 0) lep3_eleid_loose();
	if (lep3_eleid_medium_branch != 0) lep3_eleid_medium();
	if (lep3_eleid_tight_branch != 0) lep3_eleid_tight();
	if (lep3_dphiin_branch != 0) lep3_dphiin();
	if (lep3_detain_branch != 0) lep3_detain();
	if (lep3_sieie_branch != 0) lep3_sieie();
	if (lep3_hoe_branch != 0) lep3_hoe();
	if (lep3_ooemoop_branch != 0) lep3_ooemoop();
	if (lep3_conv_dist_branch != 0) lep3_conv_dist();
	if (lep3_conv_dcot_branch != 0) lep3_conv_dcot();
	if (lep3_is_global_branch != 0) lep3_is_global();
	if (lep3_is_tracker_branch != 0) lep3_is_tracker();
	if (lep3_is_stamu_branch != 0) lep3_is_stamu();
	if (lep3_is_pfmu_branch != 0) lep3_is_pfmu();
	if (lep3_is_loosemu_branch != 0) lep3_is_loosemu();
	if (lep3_is_tightmu_branch != 0) lep3_is_tightmu();
	if (lep3_npixelhits_branch != 0) lep3_npixelhits();
	if (lep3_nsihits_branch != 0) lep3_nsihits();
	if (lep3_nsilayers_branch != 0) lep3_nsilayers();
	if (lep3_nstahits_branch != 0) lep3_nstahits();
	if (lep3_nstations_branch != 0) lep3_nstations();
	if (lep3_chi2_branch != 0) lep3_chi2();
	if (lep3_ndof_branch != 0) lep3_ndof();
	if (lep3_pterr_branch != 0) lep3_pterr();
	if (lep3_ecal_vetodep_branch != 0) lep3_ecal_vetodep();
	if (lep3_hcal_vetodep_branch != 0) lep3_hcal_vetodep();
	if (lep3_p4_branch != 0) lep3_p4();
	if (lep3_mcp4_branch != 0) lep3_mcp4();
	if (lep3_mc3p4_branch != 0) lep3_mc3p4();
	if (lep3_mc_momp4_branch != 0) lep3_mc_momp4();
	if (lep3_gsf_p4_branch != 0) lep3_gsf_p4();
	if (lep3_ctf_p4_branch != 0) lep3_ctf_p4();
	if (lep3_sc_p4_branch != 0) lep3_sc_p4();
	if (lep3_gfit_p4_branch != 0) lep3_gfit_p4();
	if (selection_branch != 0) selection();
	if (is_good_lumi_branch != 0) is_good_lumi();
	if (charge_type_branch != 0) charge_type();
	if (njets_branch != 0) njets();
	if (nbtags_branch != 0) nbtags();
	if (nbtags_loose_branch != 0) nbtags_loose();
	if (ttbar_bkdn_branch != 0) ttbar_bkdn();
	if (vtxw_branch != 0) vtxw();
	if (mt_branch != 0) mt();
	if (mt2_branch != 0) mt2();
	if (ht_branch != 0) ht();
	if (rho_branch != 0) rho();
	if (rho_iso_branch != 0) rho_iso();
	if (trig_mm_branch != 0) trig_mm();
	if (trig_em_branch != 0) trig_em();
	if (trig_ee_branch != 0) trig_ee();
	if (trig_mm_mu17_mu8_branch != 0) trig_mm_mu17_mu8();
	if (trig_ee_el17_el8_id_iso_branch != 0) trig_ee_el17_el8_id_iso();
	if (trig_em_mu17_el8_id_iso_branch != 0) trig_em_mu17_el8_id_iso();
	if (trig_em_mu8_el17_id_iso_branch != 0) trig_em_mu8_el17_id_iso();
	if (njets_dn_branch != 0) njets_dn();
	if (njets_up_branch != 0) njets_up();
	if (nbtags_dn_branch != 0) nbtags_dn();
	if (nbtags_up_branch != 0) nbtags_up();
	if (ht_dn_branch != 0) ht_dn();
	if (ht_up_branch != 0) ht_up();
	if (nbtags_reweighted_branch != 0) nbtags_reweighted();
	if (nbtags_reweighted_dn_branch != 0) nbtags_reweighted_dn();
	if (nbtags_reweighted_up_branch != 0) nbtags_reweighted_up();
	if (nbtags_reweighted_jec_dn_branch != 0) nbtags_reweighted_jec_dn();
	if (nbtags_reweighted_jec_up_branch != 0) nbtags_reweighted_jec_up();
	if (pfmet_dn_branch != 0) pfmet_dn();
	if (pfmet_up_branch != 0) pfmet_up();
	if (pfmet_phi_dn_branch != 0) pfmet_phi_dn();
	if (pfmet_phi_up_branch != 0) pfmet_phi_up();
	if (sf_dileptrig_branch != 0) sf_dileptrig();
	if (sf_lepeff_branch != 0) sf_lepeff();
	if (sparm0_branch != 0) sparm0();
	if (sparm1_branch != 0) sparm1();
	if (sparm2_branch != 0) sparm2();
	if (sparm3_branch != 0) sparm3();
	if (sparm0_name_branch != 0) sparm0_name();
	if (sparm1_name_branch != 0) sparm1_name();
	if (sparm2_name_branch != 0) sparm2_name();
	if (sparm3_name_branch != 0) sparm3_name();
	if (is_pp_branch != 0) is_pp();
	if (is_mm_branch != 0) is_mm();
	if (is_ss_branch != 0) is_ss();
	if (is_sf_branch != 0) is_sf();
	if (is_df_branch != 0) is_df();
	if (is_os_branch != 0) is_os();
	if (no_extraz_branch != 0) no_extraz();
	if (no_extrag_branch != 0) no_extrag();
	if (clean_branch != 0) clean();
	if (presel_branch != 0) presel();
	if (em_mufo_branch != 0) em_mufo();
	if (em_elfo_branch != 0) em_elfo();
	if (hyp_good_vtx_branch != 0) hyp_good_vtx();
	if (is_gen_pp_branch != 0) is_gen_pp();
	if (is_gen_mm_branch != 0) is_gen_mm();
	if (gen_njets_branch != 0) gen_njets();
	if (gen_nleps_branch != 0) gen_nleps();
	if (gen_nmus_branch != 0) gen_nmus();
	if (gen_nels_branch != 0) gen_nels();
	if (gen_ntaus_branch != 0) gen_ntaus();
	if (gen_ht_branch != 0) gen_ht();
	if (lep1_nearjet_p4_branch != 0) lep1_nearjet_p4();
	if (lep1_nearlep_p4_branch != 0) lep1_nearlep_p4();
	if (lep1_wfr_branch != 0) lep1_wfr();
	if (lep1_wflip_branch != 0) lep1_wflip();
	if (lep1_nearjet_dr_branch != 0) lep1_nearjet_dr();
	if (lep1_nearlep_dr_branch != 0) lep1_nearlep_dr();
	if (lep1_nearlep_id_branch != 0) lep1_nearlep_id();
	if (lep1_isFromH_branch != 0) lep1_isFromH();
	if (lep2_nearjet_p4_branch != 0) lep2_nearjet_p4();
	if (lep2_nearlep_p4_branch != 0) lep2_nearlep_p4();
	if (lep2_wfr_branch != 0) lep2_wfr();
	if (lep2_wflip_branch != 0) lep2_wflip();
	if (lep2_nearjet_dr_branch != 0) lep2_nearjet_dr();
	if (lep2_nearlep_dr_branch != 0) lep2_nearlep_dr();
	if (lep2_nearlep_id_branch != 0) lep2_nearlep_id();
	if (lep2_isFromH_branch != 0) lep2_isFromH();
	if (jets_dr12_branch != 0) jets_dr12();
	if (dijet_mass_branch != 0) dijet_mass();
	if (vjets_p4_branch != 0) vjets_p4();
	if (vjets_p4_up_branch != 0) vjets_p4_up();
	if (vjets_p4_dn_branch != 0) vjets_p4_dn();
	if (vjets_mcflavor_phys_branch != 0) vjets_mcflavor_phys();
	if (vjets_mcflavor_algo_branch != 0) vjets_mcflavor_algo();
	if (vjets_mcflavor_phys_up_branch != 0) vjets_mcflavor_phys_up();
	if (vjets_mcflavor_algo_up_branch != 0) vjets_mcflavor_algo_up();
	if (vjets_mcflavor_phys_dn_branch != 0) vjets_mcflavor_phys_dn();
	if (vjets_mcflavor_algo_dn_branch != 0) vjets_mcflavor_algo_dn();
	if (vjets_mc3p4_branch != 0) vjets_mc3p4();
	if (vgenjets_p4_branch != 0) vgenjets_p4();
	if (vjets_mc3id_branch != 0) vjets_mc3id();
	if (vjets_momid_branch != 0) vjets_momid();
	if (vjets_nearjet_p4_branch != 0) vjets_nearjet_p4();
	if (vjets_nearjet_dr_branch != 0) vjets_nearjet_dr();
	if (vjets_bdisc_branch != 0) vjets_bdisc();
	if (gen_lep1_p4_branch != 0) gen_lep1_p4();
	if (gen_lep1_pdgid_branch != 0) gen_lep1_pdgid();
	if (gen_lep2_p4_branch != 0) gen_lep2_p4();
	if (gen_lep2_pdgid_branch != 0) gen_lep2_pdgid();
	if (gen_dilep_p4_branch != 0) gen_dilep_p4();
	if (gen_dilep_type_branch != 0) gen_dilep_type();
	if (gen_dilep_mass_branch != 0) gen_dilep_mass();
	if (gen_dilep_dphi_branch != 0) gen_dilep_dphi();
	if (gen_dilep_deta_branch != 0) gen_dilep_deta();
	if (gen_dilep_dr_branch != 0) gen_dilep_dr();
	if (pfcandid5_branch != 0) pfcandid5();
	if (pfcandid10_branch != 0) pfcandid10();
	if (pfcanddirid10_branch != 0) pfcanddirid10();
	if (pfcandvetoid10_branch != 0) pfcandvetoid10();
	if (pfcandvetoLid10_branch != 0) pfcandvetoLid10();
	if (pfcandidOS10_branch != 0) pfcandidOS10();
	if (pfcandidOS10looseZ_branch != 0) pfcandidOS10looseZ();
	if (pfcandid5looseZ_branch != 0) pfcandid5looseZ();
	if (trkpt5_branch != 0) trkpt5();
	if (mleptrk5_branch != 0) mleptrk5();
	if (trkreliso5_branch != 0) trkreliso5();
	if (trkpt10_branch != 0) trkpt10();
	if (mleptrk10_branch != 0) mleptrk10();
	if (trkreliso10_branch != 0) trkreliso10();
	if (trkpt5loose_branch != 0) trkpt5loose();
	if (trkreliso5loose_branch != 0) trkreliso5loose();
	if (trkpt10loose_branch != 0) trkpt10loose();
	if (trkreliso10loose_branch != 0) trkreliso10loose();
	if (trkpt10pt0p1_branch != 0) trkpt10pt0p1();
	if (trkreliso10pt0p1_branch != 0) trkreliso10pt0p1();
	if (trkpt10pt0p2_branch != 0) trkpt10pt0p2();
	if (trkreliso10pt0p2_branch != 0) trkreliso10pt0p2();
	if (trkpt10pt0p3_branch != 0) trkpt10pt0p3();
	if (trkreliso10pt0p3_branch != 0) trkreliso10pt0p3();
	if (trkpt10pt0p4_branch != 0) trkpt10pt0p4();
	if (trkreliso10pt0p4_branch != 0) trkreliso10pt0p4();
	if (trkpt10pt0p5_branch != 0) trkpt10pt0p5();
	if (trkreliso10pt0p5_branch != 0) trkreliso10pt0p5();
	if (trkpt10pt0p6_branch != 0) trkpt10pt0p6();
	if (trkreliso10pt0p6_branch != 0) trkreliso10pt0p6();
	if (trkpt10pt0p7_branch != 0) trkpt10pt0p7();
	if (trkreliso10pt0p7_branch != 0) trkreliso10pt0p7();
	if (trkpt10pt0p8_branch != 0) trkpt10pt0p8();
	if (trkreliso10pt0p8_branch != 0) trkreliso10pt0p8();
	if (trkpt10pt0p9_branch != 0) trkpt10pt0p9();
	if (trkreliso10pt0p9_branch != 0) trkreliso10pt0p9();
	if (trkpt10pt1p0_branch != 0) trkpt10pt1p0();
	if (trkreliso10pt1p0_branch != 0) trkreliso10pt1p0();
	if (pfcandiso5_branch != 0) pfcandiso5();
	if (pfcandiso10_branch != 0) pfcandiso10();
	if (pfcanddiriso10_branch != 0) pfcanddiriso10();
	if (pfcandvetoiso10_branch != 0) pfcandvetoiso10();
	if (pfcandvetoLiso10_branch != 0) pfcandvetoLiso10();
	if (pfcandisoOS10_branch != 0) pfcandisoOS10();
	if (pfcandisoOS10looseZ_branch != 0) pfcandisoOS10looseZ();
	if (pfcandiso5looseZ_branch != 0) pfcandiso5looseZ();
	if (pfcandpt5_branch != 0) pfcandpt5();
	if (pfcandpt10_branch != 0) pfcandpt10();
	if (pfcanddirpt10_branch != 0) pfcanddirpt10();
	if (pfcandvetopt10_branch != 0) pfcandvetopt10();
	if (pfcandvetoLpt10_branch != 0) pfcandvetoLpt10();
	if (pfcandptOS10_branch != 0) pfcandptOS10();
	if (pfcandptOS10looseZ_branch != 0) pfcandptOS10looseZ();
	if (pfcandpt5looseZ_branch != 0) pfcandpt5looseZ();
	if (pfcanddz5_branch != 0) pfcanddz5();
	if (pfcanddz10_branch != 0) pfcanddz10();
	if (pfcanddirdz10_branch != 0) pfcanddirdz10();
	if (pfcandvetodz10_branch != 0) pfcandvetodz10();
	if (pfcandvetoLdz10_branch != 0) pfcandvetoLdz10();
	if (pfcanddzOS10_branch != 0) pfcanddzOS10();
	if (pfcanddzOS10looseZ_branch != 0) pfcanddzOS10looseZ();
	if (pfcanddz5looseZ_branch != 0) pfcanddz5looseZ();
	if (pfcandmindrj5_branch != 0) pfcandmindrj5();
	if (pfcandmindrj10_branch != 0) pfcandmindrj10();
	if (pfcanddirmindrj10_branch != 0) pfcanddirmindrj10();
	if (pfcandvetomindrj10_branch != 0) pfcandvetomindrj10();
	if (pfcandvetoLmindrj10_branch != 0) pfcandvetoLmindrj10();
	if (pfcandpt10pt0p1_branch != 0) pfcandpt10pt0p1();
	if (pfcandiso10pt0p1_branch != 0) pfcandiso10pt0p1();
	if (pfcandpt10pt0p2_branch != 0) pfcandpt10pt0p2();
	if (pfcandiso10pt0p2_branch != 0) pfcandiso10pt0p2();
	if (pfcandpt10pt0p3_branch != 0) pfcandpt10pt0p3();
	if (pfcandiso10pt0p3_branch != 0) pfcandiso10pt0p3();
	if (pfcandpt10pt0p4_branch != 0) pfcandpt10pt0p4();
	if (pfcandiso10pt0p4_branch != 0) pfcandiso10pt0p4();
	if (pfcandpt10pt0p5_branch != 0) pfcandpt10pt0p5();
	if (pfcandiso10pt0p5_branch != 0) pfcandiso10pt0p5();
	if (pfcandpt10pt0p6_branch != 0) pfcandpt10pt0p6();
	if (pfcandiso10pt0p6_branch != 0) pfcandiso10pt0p6();
	if (pfcandpt10pt0p7_branch != 0) pfcandpt10pt0p7();
	if (pfcandiso10pt0p7_branch != 0) pfcandiso10pt0p7();
	if (pfcandpt10pt0p8_branch != 0) pfcandpt10pt0p8();
	if (pfcandiso10pt0p8_branch != 0) pfcandiso10pt0p8();
	if (pfcandpt10pt0p9_branch != 0) pfcandpt10pt0p9();
	if (pfcandiso10pt0p9_branch != 0) pfcandiso10pt0p9();
	if (pfcandpt10pt1p0_branch != 0) pfcandpt10pt1p0();
	if (pfcandiso10pt1p0_branch != 0) pfcandiso10pt1p0();
	if (pfcand5_branch != 0) pfcand5();
	if (pfcand10_branch != 0) pfcand10();
	if (pfcanddir10_branch != 0) pfcanddir10();
	if (pfcandveto10_branch != 0) pfcandveto10();
	if (pfcandvetoL10_branch != 0) pfcandvetoL10();
	if (pfcandOS10_branch != 0) pfcandOS10();
	if (pfcandOS10looseZ_branch != 0) pfcandOS10looseZ();
	if (pfcand5looseZ_branch != 0) pfcand5looseZ();
	if (pfTau15_leadPtcandID_branch != 0) pfTau15_leadPtcandID();
	if (pfTau_leadPtcandID_branch != 0) pfTau_leadPtcandID();
	if (pfTauLoose_leadPtcandID_branch != 0) pfTauLoose_leadPtcandID();
	if (pfTau15_branch != 0) pfTau15();
	if (pfTau15_leadPtcand_branch != 0) pfTau15_leadPtcand();
	if (pfTau_branch != 0) pfTau();
	if (pfTau_leadPtcand_branch != 0) pfTau_leadPtcand();
	if (pfTauLoose_branch != 0) pfTauLoose();
	if (pfTauLoose_leadPtcand_branch != 0) pfTauLoose_leadPtcand();
	if (pfjets_beta_branch != 0) pfjets_beta();
	if (pfjets_beta2_branch != 0) pfjets_beta2();
	if (pfjets_beta_0p1_branch != 0) pfjets_beta_0p1();
	if (pfjets_beta_0p2_branch != 0) pfjets_beta_0p2();
	if (pfjets_beta2_0p1_branch != 0) pfjets_beta2_0p1();
	if (pfjets_beta2_0p5_branch != 0) pfjets_beta2_0p5();
	if (pfjets_mvaPUid_branch != 0) pfjets_mvaPUid();
	if (pfjets_mva5xPUid_branch != 0) pfjets_mva5xPUid();
	if (pfjets_mvaBeta_branch != 0) pfjets_mvaBeta();
	if (passes_isotrk_veto_branch != 0) passes_isotrk_veto();
	if (passes_tau_veto_branch != 0) passes_tau_veto();
	if (njets_pv_tight0_branch != 0) njets_pv_tight0();
	if (njets_pv_tight1_branch != 0) njets_pv_tight1();
	if (njets_pv_tight2_branch != 0) njets_pv_tight2();
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
	float &uncorpfmet()
	{
		if (not uncorpfmet_isLoaded) {
			if (uncorpfmet_branch != 0) {
				uncorpfmet_branch->GetEntry(index);
			} else { 
				printf("branch uncorpfmet_branch does not exist!\n");
				exit(1);
			}
			uncorpfmet_isLoaded = true;
		}
		return uncorpfmet_;
	}
	float &uncorpfmet_phi()
	{
		if (not uncorpfmet_phi_isLoaded) {
			if (uncorpfmet_phi_branch != 0) {
				uncorpfmet_phi_branch->GetEntry(index);
			} else { 
				printf("branch uncorpfmet_phi_branch does not exist!\n");
				exit(1);
			}
			uncorpfmet_phi_isLoaded = true;
		}
		return uncorpfmet_phi_;
	}
	float &pu_nvtxs()
	{
		if (not pu_nvtxs_isLoaded) {
			if (pu_nvtxs_branch != 0) {
				pu_nvtxs_branch->GetEntry(index);
			} else { 
				printf("branch pu_nvtxs_branch does not exist!\n");
				exit(1);
			}
			pu_nvtxs_isLoaded = true;
		}
		return pu_nvtxs_;
	}
	float &pu_ntrueint()
	{
		if (not pu_ntrueint_isLoaded) {
			if (pu_ntrueint_branch != 0) {
				pu_ntrueint_branch->GetEntry(index);
			} else { 
				printf("branch pu_ntrueint_branch does not exist!\n");
				exit(1);
			}
			pu_ntrueint_isLoaded = true;
		}
		return pu_ntrueint_;
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
	unsigned int &nevts()
	{
		if (not nevts_isLoaded) {
			if (nevts_branch != 0) {
				nevts_branch->GetEntry(index);
			} else { 
				printf("branch nevts_branch does not exist!\n");
				exit(1);
			}
			nevts_isLoaded = true;
		}
		return nevts_;
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
	TString &dataset()
	{
		if (not dataset_isLoaded) {
			if (dataset_branch != 0) {
				dataset_branch->GetEntry(index);
			} else { 
				printf("branch dataset_branch does not exist!\n");
				exit(1);
			}
			dataset_isLoaded = true;
		}
		return *dataset_;
	}
	TString &filename()
	{
		if (not filename_isLoaded) {
			if (filename_branch != 0) {
				filename_branch->GetEntry(index);
			} else { 
				printf("branch filename_branch does not exist!\n");
				exit(1);
			}
			filename_isLoaded = true;
		}
		return *filename_;
	}
	bool &	filt_csc()
	{
		if (not filt_csc_isLoaded) {
			if (filt_csc_branch != 0) {
				filt_csc_branch->GetEntry(index);
			} else { 
				printf("branch filt_csc_branch does not exist!\n");
				exit(1);
			}
			filt_csc_isLoaded = true;
		}
		return filt_csc_;
	}
	bool &	filt_hbhe()
	{
		if (not filt_hbhe_isLoaded) {
			if (filt_hbhe_branch != 0) {
				filt_hbhe_branch->GetEntry(index);
			} else { 
				printf("branch filt_hbhe_branch does not exist!\n");
				exit(1);
			}
			filt_hbhe_isLoaded = true;
		}
		return filt_hbhe_;
	}
	bool &	filt_hcallaser()
	{
		if (not filt_hcallaser_isLoaded) {
			if (filt_hcallaser_branch != 0) {
				filt_hcallaser_branch->GetEntry(index);
			} else { 
				printf("branch filt_hcallaser_branch does not exist!\n");
				exit(1);
			}
			filt_hcallaser_isLoaded = true;
		}
		return filt_hcallaser_;
	}
	bool &	filt_ecallaser()
	{
		if (not filt_ecallaser_isLoaded) {
			if (filt_ecallaser_branch != 0) {
				filt_ecallaser_branch->GetEntry(index);
			} else { 
				printf("branch filt_ecallaser_branch does not exist!\n");
				exit(1);
			}
			filt_ecallaser_isLoaded = true;
		}
		return filt_ecallaser_;
	}
	bool &	filt_ecaltp()
	{
		if (not filt_ecaltp_isLoaded) {
			if (filt_ecaltp_branch != 0) {
				filt_ecaltp_branch->GetEntry(index);
			} else { 
				printf("branch filt_ecaltp_branch does not exist!\n");
				exit(1);
			}
			filt_ecaltp_isLoaded = true;
		}
		return filt_ecaltp_;
	}
	bool &	filt_trkfail()
	{
		if (not filt_trkfail_isLoaded) {
			if (filt_trkfail_branch != 0) {
				filt_trkfail_branch->GetEntry(index);
			} else { 
				printf("branch filt_trkfail_branch does not exist!\n");
				exit(1);
			}
			filt_trkfail_isLoaded = true;
		}
		return filt_trkfail_;
	}
	bool &	filt_eebadsc()
	{
		if (not filt_eebadsc_isLoaded) {
			if (filt_eebadsc_branch != 0) {
				filt_eebadsc_branch->GetEntry(index);
			} else { 
				printf("branch filt_eebadsc_branch does not exist!\n");
				exit(1);
			}
			filt_eebadsc_isLoaded = true;
		}
		return filt_eebadsc_;
	}
	bool &	passes_metfilters()
	{
		if (not passes_metfilters_isLoaded) {
			if (passes_metfilters_branch != 0) {
				passes_metfilters_branch->GetEntry(index);
			} else { 
				printf("branch passes_metfilters_branch does not exist!\n");
				exit(1);
			}
			passes_metfilters_isLoaded = true;
		}
		return passes_metfilters_;
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
	bool &	lep1_is_den()
	{
		if (not lep1_is_den_isLoaded) {
			if (lep1_is_den_branch != 0) {
				lep1_is_den_branch->GetEntry(index);
			} else { 
				printf("branch lep1_is_den_branch does not exist!\n");
				exit(1);
			}
			lep1_is_den_isLoaded = true;
		}
		return lep1_is_den_;
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
	int &lep1_is_fromw()
	{
		if (not lep1_is_fromw_isLoaded) {
			if (lep1_is_fromw_branch != 0) {
				lep1_is_fromw_branch->GetEntry(index);
			} else { 
				printf("branch lep1_is_fromw_branch does not exist!\n");
				exit(1);
			}
			lep1_is_fromw_isLoaded = true;
		}
		return lep1_is_fromw_;
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
	float &lep1_d0err()
	{
		if (not lep1_d0err_isLoaded) {
			if (lep1_d0err_branch != 0) {
				lep1_d0err_branch->GetEntry(index);
			} else { 
				printf("branch lep1_d0err_branch does not exist!\n");
				exit(1);
			}
			lep1_d0err_isLoaded = true;
		}
		return lep1_d0err_;
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
	float &lep1_ip3d()
	{
		if (not lep1_ip3d_isLoaded) {
			if (lep1_ip3d_branch != 0) {
				lep1_ip3d_branch->GetEntry(index);
			} else { 
				printf("branch lep1_ip3d_branch does not exist!\n");
				exit(1);
			}
			lep1_ip3d_isLoaded = true;
		}
		return lep1_ip3d_;
	}
	float &lep1_ip3derr()
	{
		if (not lep1_ip3derr_isLoaded) {
			if (lep1_ip3derr_branch != 0) {
				lep1_ip3derr_branch->GetEntry(index);
			} else { 
				printf("branch lep1_ip3derr_branch does not exist!\n");
				exit(1);
			}
			lep1_ip3derr_isLoaded = true;
		}
		return lep1_ip3derr_;
	}
	float &lep1_dzerr()
	{
		if (not lep1_dzerr_isLoaded) {
			if (lep1_dzerr_branch != 0) {
				lep1_dzerr_branch->GetEntry(index);
			} else { 
				printf("branch lep1_dzerr_branch does not exist!\n");
				exit(1);
			}
			lep1_dzerr_isLoaded = true;
		}
		return lep1_dzerr_;
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
	bool &	lep2_is_den()
	{
		if (not lep2_is_den_isLoaded) {
			if (lep2_is_den_branch != 0) {
				lep2_is_den_branch->GetEntry(index);
			} else { 
				printf("branch lep2_is_den_branch does not exist!\n");
				exit(1);
			}
			lep2_is_den_isLoaded = true;
		}
		return lep2_is_den_;
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
	int &lep2_is_fromw()
	{
		if (not lep2_is_fromw_isLoaded) {
			if (lep2_is_fromw_branch != 0) {
				lep2_is_fromw_branch->GetEntry(index);
			} else { 
				printf("branch lep2_is_fromw_branch does not exist!\n");
				exit(1);
			}
			lep2_is_fromw_isLoaded = true;
		}
		return lep2_is_fromw_;
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
	float &lep2_d0err()
	{
		if (not lep2_d0err_isLoaded) {
			if (lep2_d0err_branch != 0) {
				lep2_d0err_branch->GetEntry(index);
			} else { 
				printf("branch lep2_d0err_branch does not exist!\n");
				exit(1);
			}
			lep2_d0err_isLoaded = true;
		}
		return lep2_d0err_;
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
	float &lep2_ip3d()
	{
		if (not lep2_ip3d_isLoaded) {
			if (lep2_ip3d_branch != 0) {
				lep2_ip3d_branch->GetEntry(index);
			} else { 
				printf("branch lep2_ip3d_branch does not exist!\n");
				exit(1);
			}
			lep2_ip3d_isLoaded = true;
		}
		return lep2_ip3d_;
	}
	float &lep2_ip3derr()
	{
		if (not lep2_ip3derr_isLoaded) {
			if (lep2_ip3derr_branch != 0) {
				lep2_ip3derr_branch->GetEntry(index);
			} else { 
				printf("branch lep2_ip3derr_branch does not exist!\n");
				exit(1);
			}
			lep2_ip3derr_isLoaded = true;
		}
		return lep2_ip3derr_;
	}
	float &lep2_dzerr()
	{
		if (not lep2_dzerr_isLoaded) {
			if (lep2_dzerr_branch != 0) {
				lep2_dzerr_branch->GetEntry(index);
			} else { 
				printf("branch lep2_dzerr_branch does not exist!\n");
				exit(1);
			}
			lep2_dzerr_isLoaded = true;
		}
		return lep2_dzerr_;
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
	bool &	os()
	{
		if (not os_isLoaded) {
			if (os_branch != 0) {
				os_branch->GetEntry(index);
			} else { 
				printf("branch os_branch does not exist!\n");
				exit(1);
			}
			os_isLoaded = true;
		}
		return os_;
	}
	bool &	ss()
	{
		if (not ss_isLoaded) {
			if (ss_branch != 0) {
				ss_branch->GetEntry(index);
			} else { 
				printf("branch ss_branch does not exist!\n");
				exit(1);
			}
			ss_isLoaded = true;
		}
		return ss_;
	}
	bool &	mm()
	{
		if (not mm_isLoaded) {
			if (mm_branch != 0) {
				mm_branch->GetEntry(index);
			} else { 
				printf("branch mm_branch does not exist!\n");
				exit(1);
			}
			mm_isLoaded = true;
		}
		return mm_;
	}
	bool &	ee()
	{
		if (not ee_isLoaded) {
			if (ee_branch != 0) {
				ee_branch->GetEntry(index);
			} else { 
				printf("branch ee_branch does not exist!\n");
				exit(1);
			}
			ee_isLoaded = true;
		}
		return ee_;
	}
	bool &	em()
	{
		if (not em_isLoaded) {
			if (em_branch != 0) {
				em_branch->GetEntry(index);
			} else { 
				printf("branch em_branch does not exist!\n");
				exit(1);
			}
			em_isLoaded = true;
		}
		return em_;
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
	bool &	lep3_passes_id()
	{
		if (not lep3_passes_id_isLoaded) {
			if (lep3_passes_id_branch != 0) {
				lep3_passes_id_branch->GetEntry(index);
			} else { 
				printf("branch lep3_passes_id_branch does not exist!\n");
				exit(1);
			}
			lep3_passes_id_isLoaded = true;
		}
		return lep3_passes_id_;
	}
	bool &	lep3_passes_iso()
	{
		if (not lep3_passes_iso_isLoaded) {
			if (lep3_passes_iso_branch != 0) {
				lep3_passes_iso_branch->GetEntry(index);
			} else { 
				printf("branch lep3_passes_iso_branch does not exist!\n");
				exit(1);
			}
			lep3_passes_iso_isLoaded = true;
		}
		return lep3_passes_iso_;
	}
	bool &	lep3_is_num()
	{
		if (not lep3_is_num_isLoaded) {
			if (lep3_is_num_branch != 0) {
				lep3_is_num_branch->GetEntry(index);
			} else { 
				printf("branch lep3_is_num_branch does not exist!\n");
				exit(1);
			}
			lep3_is_num_isLoaded = true;
		}
		return lep3_is_num_;
	}
	bool &	lep3_is_den()
	{
		if (not lep3_is_den_isLoaded) {
			if (lep3_is_den_branch != 0) {
				lep3_is_den_branch->GetEntry(index);
			} else { 
				printf("branch lep3_is_den_branch does not exist!\n");
				exit(1);
			}
			lep3_is_den_isLoaded = true;
		}
		return lep3_is_den_;
	}
	bool &	lep3_is_fo()
	{
		if (not lep3_is_fo_isLoaded) {
			if (lep3_is_fo_branch != 0) {
				lep3_is_fo_branch->GetEntry(index);
			} else { 
				printf("branch lep3_is_fo_branch does not exist!\n");
				exit(1);
			}
			lep3_is_fo_isLoaded = true;
		}
		return lep3_is_fo_;
	}
	int &lep3_is_fromw()
	{
		if (not lep3_is_fromw_isLoaded) {
			if (lep3_is_fromw_branch != 0) {
				lep3_is_fromw_branch->GetEntry(index);
			} else { 
				printf("branch lep3_is_fromw_branch does not exist!\n");
				exit(1);
			}
			lep3_is_fromw_isLoaded = true;
		}
		return lep3_is_fromw_;
	}
	int &lep3_charge()
	{
		if (not lep3_charge_isLoaded) {
			if (lep3_charge_branch != 0) {
				lep3_charge_branch->GetEntry(index);
			} else { 
				printf("branch lep3_charge_branch does not exist!\n");
				exit(1);
			}
			lep3_charge_isLoaded = true;
		}
		return lep3_charge_;
	}
	int &lep3_pdgid()
	{
		if (not lep3_pdgid_isLoaded) {
			if (lep3_pdgid_branch != 0) {
				lep3_pdgid_branch->GetEntry(index);
			} else { 
				printf("branch lep3_pdgid_branch does not exist!\n");
				exit(1);
			}
			lep3_pdgid_isLoaded = true;
		}
		return lep3_pdgid_;
	}
	int &lep3_type()
	{
		if (not lep3_type_isLoaded) {
			if (lep3_type_branch != 0) {
				lep3_type_branch->GetEntry(index);
			} else { 
				printf("branch lep3_type_branch does not exist!\n");
				exit(1);
			}
			lep3_type_isLoaded = true;
		}
		return lep3_type_;
	}
	float &lep3_d0()
	{
		if (not lep3_d0_isLoaded) {
			if (lep3_d0_branch != 0) {
				lep3_d0_branch->GetEntry(index);
			} else { 
				printf("branch lep3_d0_branch does not exist!\n");
				exit(1);
			}
			lep3_d0_isLoaded = true;
		}
		return lep3_d0_;
	}
	float &lep3_d0err()
	{
		if (not lep3_d0err_isLoaded) {
			if (lep3_d0err_branch != 0) {
				lep3_d0err_branch->GetEntry(index);
			} else { 
				printf("branch lep3_d0err_branch does not exist!\n");
				exit(1);
			}
			lep3_d0err_isLoaded = true;
		}
		return lep3_d0err_;
	}
	float &lep3_dz()
	{
		if (not lep3_dz_isLoaded) {
			if (lep3_dz_branch != 0) {
				lep3_dz_branch->GetEntry(index);
			} else { 
				printf("branch lep3_dz_branch does not exist!\n");
				exit(1);
			}
			lep3_dz_isLoaded = true;
		}
		return lep3_dz_;
	}
	float &lep3_ip3d()
	{
		if (not lep3_ip3d_isLoaded) {
			if (lep3_ip3d_branch != 0) {
				lep3_ip3d_branch->GetEntry(index);
			} else { 
				printf("branch lep3_ip3d_branch does not exist!\n");
				exit(1);
			}
			lep3_ip3d_isLoaded = true;
		}
		return lep3_ip3d_;
	}
	float &lep3_ip3derr()
	{
		if (not lep3_ip3derr_isLoaded) {
			if (lep3_ip3derr_branch != 0) {
				lep3_ip3derr_branch->GetEntry(index);
			} else { 
				printf("branch lep3_ip3derr_branch does not exist!\n");
				exit(1);
			}
			lep3_ip3derr_isLoaded = true;
		}
		return lep3_ip3derr_;
	}
	float &lep3_dzerr()
	{
		if (not lep3_dzerr_isLoaded) {
			if (lep3_dzerr_branch != 0) {
				lep3_dzerr_branch->GetEntry(index);
			} else { 
				printf("branch lep3_dzerr_branch does not exist!\n");
				exit(1);
			}
			lep3_dzerr_isLoaded = true;
		}
		return lep3_dzerr_;
	}
	float &lep3_mt()
	{
		if (not lep3_mt_isLoaded) {
			if (lep3_mt_branch != 0) {
				lep3_mt_branch->GetEntry(index);
			} else { 
				printf("branch lep3_mt_branch does not exist!\n");
				exit(1);
			}
			lep3_mt_isLoaded = true;
		}
		return lep3_mt_;
	}
	float &lep3_corpfiso()
	{
		if (not lep3_corpfiso_isLoaded) {
			if (lep3_corpfiso_branch != 0) {
				lep3_corpfiso_branch->GetEntry(index);
			} else { 
				printf("branch lep3_corpfiso_branch does not exist!\n");
				exit(1);
			}
			lep3_corpfiso_isLoaded = true;
		}
		return lep3_corpfiso_;
	}
	float &lep3_pfiso()
	{
		if (not lep3_pfiso_isLoaded) {
			if (lep3_pfiso_branch != 0) {
				lep3_pfiso_branch->GetEntry(index);
			} else { 
				printf("branch lep3_pfiso_branch does not exist!\n");
				exit(1);
			}
			lep3_pfiso_isLoaded = true;
		}
		return lep3_pfiso_;
	}
	float &lep3_chiso()
	{
		if (not lep3_chiso_isLoaded) {
			if (lep3_chiso_branch != 0) {
				lep3_chiso_branch->GetEntry(index);
			} else { 
				printf("branch lep3_chiso_branch does not exist!\n");
				exit(1);
			}
			lep3_chiso_isLoaded = true;
		}
		return lep3_chiso_;
	}
	float &lep3_emiso()
	{
		if (not lep3_emiso_isLoaded) {
			if (lep3_emiso_branch != 0) {
				lep3_emiso_branch->GetEntry(index);
			} else { 
				printf("branch lep3_emiso_branch does not exist!\n");
				exit(1);
			}
			lep3_emiso_isLoaded = true;
		}
		return lep3_emiso_;
	}
	float &lep3_nhiso()
	{
		if (not lep3_nhiso_isLoaded) {
			if (lep3_nhiso_branch != 0) {
				lep3_nhiso_branch->GetEntry(index);
			} else { 
				printf("branch lep3_nhiso_branch does not exist!\n");
				exit(1);
			}
			lep3_nhiso_isLoaded = true;
		}
		return lep3_nhiso_;
	}
	float &lep3_corpfiso04()
	{
		if (not lep3_corpfiso04_isLoaded) {
			if (lep3_corpfiso04_branch != 0) {
				lep3_corpfiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep3_corpfiso04_branch does not exist!\n");
				exit(1);
			}
			lep3_corpfiso04_isLoaded = true;
		}
		return lep3_corpfiso04_;
	}
	float &lep3_pfiso04()
	{
		if (not lep3_pfiso04_isLoaded) {
			if (lep3_pfiso04_branch != 0) {
				lep3_pfiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep3_pfiso04_branch does not exist!\n");
				exit(1);
			}
			lep3_pfiso04_isLoaded = true;
		}
		return lep3_pfiso04_;
	}
	float &lep3_chiso04()
	{
		if (not lep3_chiso04_isLoaded) {
			if (lep3_chiso04_branch != 0) {
				lep3_chiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep3_chiso04_branch does not exist!\n");
				exit(1);
			}
			lep3_chiso04_isLoaded = true;
		}
		return lep3_chiso04_;
	}
	float &lep3_emiso04()
	{
		if (not lep3_emiso04_isLoaded) {
			if (lep3_emiso04_branch != 0) {
				lep3_emiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep3_emiso04_branch does not exist!\n");
				exit(1);
			}
			lep3_emiso04_isLoaded = true;
		}
		return lep3_emiso04_;
	}
	float &lep3_nhiso04()
	{
		if (not lep3_nhiso04_isLoaded) {
			if (lep3_nhiso04_branch != 0) {
				lep3_nhiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep3_nhiso04_branch does not exist!\n");
				exit(1);
			}
			lep3_nhiso04_isLoaded = true;
		}
		return lep3_nhiso04_;
	}
	float &lep3_cordetiso()
	{
		if (not lep3_cordetiso_isLoaded) {
			if (lep3_cordetiso_branch != 0) {
				lep3_cordetiso_branch->GetEntry(index);
			} else { 
				printf("branch lep3_cordetiso_branch does not exist!\n");
				exit(1);
			}
			lep3_cordetiso_isLoaded = true;
		}
		return lep3_cordetiso_;
	}
	float &lep3_detiso()
	{
		if (not lep3_detiso_isLoaded) {
			if (lep3_detiso_branch != 0) {
				lep3_detiso_branch->GetEntry(index);
			} else { 
				printf("branch lep3_detiso_branch does not exist!\n");
				exit(1);
			}
			lep3_detiso_isLoaded = true;
		}
		return lep3_detiso_;
	}
	float &lep3_trkiso()
	{
		if (not lep3_trkiso_isLoaded) {
			if (lep3_trkiso_branch != 0) {
				lep3_trkiso_branch->GetEntry(index);
			} else { 
				printf("branch lep3_trkiso_branch does not exist!\n");
				exit(1);
			}
			lep3_trkiso_isLoaded = true;
		}
		return lep3_trkiso_;
	}
	float &lep3_ecaliso()
	{
		if (not lep3_ecaliso_isLoaded) {
			if (lep3_ecaliso_branch != 0) {
				lep3_ecaliso_branch->GetEntry(index);
			} else { 
				printf("branch lep3_ecaliso_branch does not exist!\n");
				exit(1);
			}
			lep3_ecaliso_isLoaded = true;
		}
		return lep3_ecaliso_;
	}
	float &lep3_hcaliso()
	{
		if (not lep3_hcaliso_isLoaded) {
			if (lep3_hcaliso_branch != 0) {
				lep3_hcaliso_branch->GetEntry(index);
			} else { 
				printf("branch lep3_hcaliso_branch does not exist!\n");
				exit(1);
			}
			lep3_hcaliso_isLoaded = true;
		}
		return lep3_hcaliso_;
	}
	float &lep3_cordetiso04()
	{
		if (not lep3_cordetiso04_isLoaded) {
			if (lep3_cordetiso04_branch != 0) {
				lep3_cordetiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep3_cordetiso04_branch does not exist!\n");
				exit(1);
			}
			lep3_cordetiso04_isLoaded = true;
		}
		return lep3_cordetiso04_;
	}
	float &lep3_detiso04()
	{
		if (not lep3_detiso04_isLoaded) {
			if (lep3_detiso04_branch != 0) {
				lep3_detiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep3_detiso04_branch does not exist!\n");
				exit(1);
			}
			lep3_detiso04_isLoaded = true;
		}
		return lep3_detiso04_;
	}
	float &lep3_trkiso04()
	{
		if (not lep3_trkiso04_isLoaded) {
			if (lep3_trkiso04_branch != 0) {
				lep3_trkiso04_branch->GetEntry(index);
			} else { 
				printf("branch lep3_trkiso04_branch does not exist!\n");
				exit(1);
			}
			lep3_trkiso04_isLoaded = true;
		}
		return lep3_trkiso04_;
	}
	float &lep3_ecaliso04()
	{
		if (not lep3_ecaliso04_isLoaded) {
			if (lep3_ecaliso04_branch != 0) {
				lep3_ecaliso04_branch->GetEntry(index);
			} else { 
				printf("branch lep3_ecaliso04_branch does not exist!\n");
				exit(1);
			}
			lep3_ecaliso04_isLoaded = true;
		}
		return lep3_ecaliso04_;
	}
	float &lep3_hcaliso04()
	{
		if (not lep3_hcaliso04_isLoaded) {
			if (lep3_hcaliso04_branch != 0) {
				lep3_hcaliso04_branch->GetEntry(index);
			} else { 
				printf("branch lep3_hcaliso04_branch does not exist!\n");
				exit(1);
			}
			lep3_hcaliso04_isLoaded = true;
		}
		return lep3_hcaliso04_;
	}
	float &lep3_effarea()
	{
		if (not lep3_effarea_isLoaded) {
			if (lep3_effarea_branch != 0) {
				lep3_effarea_branch->GetEntry(index);
			} else { 
				printf("branch lep3_effarea_branch does not exist!\n");
				exit(1);
			}
			lep3_effarea_isLoaded = true;
		}
		return lep3_effarea_;
	}
	float &lep3_effarea04()
	{
		if (not lep3_effarea04_isLoaded) {
			if (lep3_effarea04_branch != 0) {
				lep3_effarea04_branch->GetEntry(index);
			} else { 
				printf("branch lep3_effarea04_branch does not exist!\n");
				exit(1);
			}
			lep3_effarea04_isLoaded = true;
		}
		return lep3_effarea04_;
	}
	float &lep3_dbeta()
	{
		if (not lep3_dbeta_isLoaded) {
			if (lep3_dbeta_branch != 0) {
				lep3_dbeta_branch->GetEntry(index);
			} else { 
				printf("branch lep3_dbeta_branch does not exist!\n");
				exit(1);
			}
			lep3_dbeta_isLoaded = true;
		}
		return lep3_dbeta_;
	}
	float &lep3_dbeta04()
	{
		if (not lep3_dbeta04_isLoaded) {
			if (lep3_dbeta04_branch != 0) {
				lep3_dbeta04_branch->GetEntry(index);
			} else { 
				printf("branch lep3_dbeta04_branch does not exist!\n");
				exit(1);
			}
			lep3_dbeta04_isLoaded = true;
		}
		return lep3_dbeta04_;
	}
	float &lep3_sf_lepeff()
	{
		if (not lep3_sf_lepeff_isLoaded) {
			if (lep3_sf_lepeff_branch != 0) {
				lep3_sf_lepeff_branch->GetEntry(index);
			} else { 
				printf("branch lep3_sf_lepeff_branch does not exist!\n");
				exit(1);
			}
			lep3_sf_lepeff_isLoaded = true;
		}
		return lep3_sf_lepeff_;
	}
	float &lep3_sf_trig()
	{
		if (not lep3_sf_trig_isLoaded) {
			if (lep3_sf_trig_branch != 0) {
				lep3_sf_trig_branch->GetEntry(index);
			} else { 
				printf("branch lep3_sf_trig_branch does not exist!\n");
				exit(1);
			}
			lep3_sf_trig_isLoaded = true;
		}
		return lep3_sf_trig_;
	}
	int &lep3_mcid()
	{
		if (not lep3_mcid_isLoaded) {
			if (lep3_mcid_branch != 0) {
				lep3_mcid_branch->GetEntry(index);
			} else { 
				printf("branch lep3_mcid_branch does not exist!\n");
				exit(1);
			}
			lep3_mcid_isLoaded = true;
		}
		return lep3_mcid_;
	}
	int &lep3_mc3id()
	{
		if (not lep3_mc3id_isLoaded) {
			if (lep3_mc3id_branch != 0) {
				lep3_mc3id_branch->GetEntry(index);
			} else { 
				printf("branch lep3_mc3id_branch does not exist!\n");
				exit(1);
			}
			lep3_mc3id_isLoaded = true;
		}
		return lep3_mc3id_;
	}
	int &lep3_momid()
	{
		if (not lep3_momid_isLoaded) {
			if (lep3_momid_branch != 0) {
				lep3_momid_branch->GetEntry(index);
			} else { 
				printf("branch lep3_momid_branch does not exist!\n");
				exit(1);
			}
			lep3_momid_isLoaded = true;
		}
		return lep3_momid_;
	}
	int &lep3_mc3_momid()
	{
		if (not lep3_mc3_momid_isLoaded) {
			if (lep3_mc3_momid_branch != 0) {
				lep3_mc3_momid_branch->GetEntry(index);
			} else { 
				printf("branch lep3_mc3_momid_branch does not exist!\n");
				exit(1);
			}
			lep3_mc3_momid_isLoaded = true;
		}
		return lep3_mc3_momid_;
	}
	bool &	lep3_q3agree()
	{
		if (not lep3_q3agree_isLoaded) {
			if (lep3_q3agree_branch != 0) {
				lep3_q3agree_branch->GetEntry(index);
			} else { 
				printf("branch lep3_q3agree_branch does not exist!\n");
				exit(1);
			}
			lep3_q3agree_isLoaded = true;
		}
		return lep3_q3agree_;
	}
	bool &	lep3_is_conv()
	{
		if (not lep3_is_conv_isLoaded) {
			if (lep3_is_conv_branch != 0) {
				lep3_is_conv_branch->GetEntry(index);
			} else { 
				printf("branch lep3_is_conv_branch does not exist!\n");
				exit(1);
			}
			lep3_is_conv_isLoaded = true;
		}
		return lep3_is_conv_;
	}
	int &lep3_qsc()
	{
		if (not lep3_qsc_isLoaded) {
			if (lep3_qsc_branch != 0) {
				lep3_qsc_branch->GetEntry(index);
			} else { 
				printf("branch lep3_qsc_branch does not exist!\n");
				exit(1);
			}
			lep3_qsc_isLoaded = true;
		}
		return lep3_qsc_;
	}
	int &lep3_qctf()
	{
		if (not lep3_qctf_isLoaded) {
			if (lep3_qctf_branch != 0) {
				lep3_qctf_branch->GetEntry(index);
			} else { 
				printf("branch lep3_qctf_branch does not exist!\n");
				exit(1);
			}
			lep3_qctf_isLoaded = true;
		}
		return lep3_qctf_;
	}
	int &lep3_qgsf()
	{
		if (not lep3_qgsf_isLoaded) {
			if (lep3_qgsf_branch != 0) {
				lep3_qgsf_branch->GetEntry(index);
			} else { 
				printf("branch lep3_qgsf_branch does not exist!\n");
				exit(1);
			}
			lep3_qgsf_isLoaded = true;
		}
		return lep3_qgsf_;
	}
	int &lep3_nmhits()
	{
		if (not lep3_nmhits_isLoaded) {
			if (lep3_nmhits_branch != 0) {
				lep3_nmhits_branch->GetEntry(index);
			} else { 
				printf("branch lep3_nmhits_branch does not exist!\n");
				exit(1);
			}
			lep3_nmhits_isLoaded = true;
		}
		return lep3_nmhits_;
	}
	int &lep3_eleid_veto()
	{
		if (not lep3_eleid_veto_isLoaded) {
			if (lep3_eleid_veto_branch != 0) {
				lep3_eleid_veto_branch->GetEntry(index);
			} else { 
				printf("branch lep3_eleid_veto_branch does not exist!\n");
				exit(1);
			}
			lep3_eleid_veto_isLoaded = true;
		}
		return lep3_eleid_veto_;
	}
	int &lep3_eleid_loose()
	{
		if (not lep3_eleid_loose_isLoaded) {
			if (lep3_eleid_loose_branch != 0) {
				lep3_eleid_loose_branch->GetEntry(index);
			} else { 
				printf("branch lep3_eleid_loose_branch does not exist!\n");
				exit(1);
			}
			lep3_eleid_loose_isLoaded = true;
		}
		return lep3_eleid_loose_;
	}
	int &lep3_eleid_medium()
	{
		if (not lep3_eleid_medium_isLoaded) {
			if (lep3_eleid_medium_branch != 0) {
				lep3_eleid_medium_branch->GetEntry(index);
			} else { 
				printf("branch lep3_eleid_medium_branch does not exist!\n");
				exit(1);
			}
			lep3_eleid_medium_isLoaded = true;
		}
		return lep3_eleid_medium_;
	}
	int &lep3_eleid_tight()
	{
		if (not lep3_eleid_tight_isLoaded) {
			if (lep3_eleid_tight_branch != 0) {
				lep3_eleid_tight_branch->GetEntry(index);
			} else { 
				printf("branch lep3_eleid_tight_branch does not exist!\n");
				exit(1);
			}
			lep3_eleid_tight_isLoaded = true;
		}
		return lep3_eleid_tight_;
	}
	float &lep3_dphiin()
	{
		if (not lep3_dphiin_isLoaded) {
			if (lep3_dphiin_branch != 0) {
				lep3_dphiin_branch->GetEntry(index);
			} else { 
				printf("branch lep3_dphiin_branch does not exist!\n");
				exit(1);
			}
			lep3_dphiin_isLoaded = true;
		}
		return lep3_dphiin_;
	}
	float &lep3_detain()
	{
		if (not lep3_detain_isLoaded) {
			if (lep3_detain_branch != 0) {
				lep3_detain_branch->GetEntry(index);
			} else { 
				printf("branch lep3_detain_branch does not exist!\n");
				exit(1);
			}
			lep3_detain_isLoaded = true;
		}
		return lep3_detain_;
	}
	float &lep3_sieie()
	{
		if (not lep3_sieie_isLoaded) {
			if (lep3_sieie_branch != 0) {
				lep3_sieie_branch->GetEntry(index);
			} else { 
				printf("branch lep3_sieie_branch does not exist!\n");
				exit(1);
			}
			lep3_sieie_isLoaded = true;
		}
		return lep3_sieie_;
	}
	float &lep3_hoe()
	{
		if (not lep3_hoe_isLoaded) {
			if (lep3_hoe_branch != 0) {
				lep3_hoe_branch->GetEntry(index);
			} else { 
				printf("branch lep3_hoe_branch does not exist!\n");
				exit(1);
			}
			lep3_hoe_isLoaded = true;
		}
		return lep3_hoe_;
	}
	float &lep3_ooemoop()
	{
		if (not lep3_ooemoop_isLoaded) {
			if (lep3_ooemoop_branch != 0) {
				lep3_ooemoop_branch->GetEntry(index);
			} else { 
				printf("branch lep3_ooemoop_branch does not exist!\n");
				exit(1);
			}
			lep3_ooemoop_isLoaded = true;
		}
		return lep3_ooemoop_;
	}
	float &lep3_conv_dist()
	{
		if (not lep3_conv_dist_isLoaded) {
			if (lep3_conv_dist_branch != 0) {
				lep3_conv_dist_branch->GetEntry(index);
			} else { 
				printf("branch lep3_conv_dist_branch does not exist!\n");
				exit(1);
			}
			lep3_conv_dist_isLoaded = true;
		}
		return lep3_conv_dist_;
	}
	float &lep3_conv_dcot()
	{
		if (not lep3_conv_dcot_isLoaded) {
			if (lep3_conv_dcot_branch != 0) {
				lep3_conv_dcot_branch->GetEntry(index);
			} else { 
				printf("branch lep3_conv_dcot_branch does not exist!\n");
				exit(1);
			}
			lep3_conv_dcot_isLoaded = true;
		}
		return lep3_conv_dcot_;
	}
	bool &	lep3_is_global()
	{
		if (not lep3_is_global_isLoaded) {
			if (lep3_is_global_branch != 0) {
				lep3_is_global_branch->GetEntry(index);
			} else { 
				printf("branch lep3_is_global_branch does not exist!\n");
				exit(1);
			}
			lep3_is_global_isLoaded = true;
		}
		return lep3_is_global_;
	}
	bool &	lep3_is_tracker()
	{
		if (not lep3_is_tracker_isLoaded) {
			if (lep3_is_tracker_branch != 0) {
				lep3_is_tracker_branch->GetEntry(index);
			} else { 
				printf("branch lep3_is_tracker_branch does not exist!\n");
				exit(1);
			}
			lep3_is_tracker_isLoaded = true;
		}
		return lep3_is_tracker_;
	}
	bool &	lep3_is_stamu()
	{
		if (not lep3_is_stamu_isLoaded) {
			if (lep3_is_stamu_branch != 0) {
				lep3_is_stamu_branch->GetEntry(index);
			} else { 
				printf("branch lep3_is_stamu_branch does not exist!\n");
				exit(1);
			}
			lep3_is_stamu_isLoaded = true;
		}
		return lep3_is_stamu_;
	}
	bool &	lep3_is_pfmu()
	{
		if (not lep3_is_pfmu_isLoaded) {
			if (lep3_is_pfmu_branch != 0) {
				lep3_is_pfmu_branch->GetEntry(index);
			} else { 
				printf("branch lep3_is_pfmu_branch does not exist!\n");
				exit(1);
			}
			lep3_is_pfmu_isLoaded = true;
		}
		return lep3_is_pfmu_;
	}
	bool &	lep3_is_loosemu()
	{
		if (not lep3_is_loosemu_isLoaded) {
			if (lep3_is_loosemu_branch != 0) {
				lep3_is_loosemu_branch->GetEntry(index);
			} else { 
				printf("branch lep3_is_loosemu_branch does not exist!\n");
				exit(1);
			}
			lep3_is_loosemu_isLoaded = true;
		}
		return lep3_is_loosemu_;
	}
	bool &	lep3_is_tightmu()
	{
		if (not lep3_is_tightmu_isLoaded) {
			if (lep3_is_tightmu_branch != 0) {
				lep3_is_tightmu_branch->GetEntry(index);
			} else { 
				printf("branch lep3_is_tightmu_branch does not exist!\n");
				exit(1);
			}
			lep3_is_tightmu_isLoaded = true;
		}
		return lep3_is_tightmu_;
	}
	int &lep3_npixelhits()
	{
		if (not lep3_npixelhits_isLoaded) {
			if (lep3_npixelhits_branch != 0) {
				lep3_npixelhits_branch->GetEntry(index);
			} else { 
				printf("branch lep3_npixelhits_branch does not exist!\n");
				exit(1);
			}
			lep3_npixelhits_isLoaded = true;
		}
		return lep3_npixelhits_;
	}
	int &lep3_nsihits()
	{
		if (not lep3_nsihits_isLoaded) {
			if (lep3_nsihits_branch != 0) {
				lep3_nsihits_branch->GetEntry(index);
			} else { 
				printf("branch lep3_nsihits_branch does not exist!\n");
				exit(1);
			}
			lep3_nsihits_isLoaded = true;
		}
		return lep3_nsihits_;
	}
	int &lep3_nsilayers()
	{
		if (not lep3_nsilayers_isLoaded) {
			if (lep3_nsilayers_branch != 0) {
				lep3_nsilayers_branch->GetEntry(index);
			} else { 
				printf("branch lep3_nsilayers_branch does not exist!\n");
				exit(1);
			}
			lep3_nsilayers_isLoaded = true;
		}
		return lep3_nsilayers_;
	}
	int &lep3_nstahits()
	{
		if (not lep3_nstahits_isLoaded) {
			if (lep3_nstahits_branch != 0) {
				lep3_nstahits_branch->GetEntry(index);
			} else { 
				printf("branch lep3_nstahits_branch does not exist!\n");
				exit(1);
			}
			lep3_nstahits_isLoaded = true;
		}
		return lep3_nstahits_;
	}
	int &lep3_nstations()
	{
		if (not lep3_nstations_isLoaded) {
			if (lep3_nstations_branch != 0) {
				lep3_nstations_branch->GetEntry(index);
			} else { 
				printf("branch lep3_nstations_branch does not exist!\n");
				exit(1);
			}
			lep3_nstations_isLoaded = true;
		}
		return lep3_nstations_;
	}
	float &lep3_chi2()
	{
		if (not lep3_chi2_isLoaded) {
			if (lep3_chi2_branch != 0) {
				lep3_chi2_branch->GetEntry(index);
			} else { 
				printf("branch lep3_chi2_branch does not exist!\n");
				exit(1);
			}
			lep3_chi2_isLoaded = true;
		}
		return lep3_chi2_;
	}
	float &lep3_ndof()
	{
		if (not lep3_ndof_isLoaded) {
			if (lep3_ndof_branch != 0) {
				lep3_ndof_branch->GetEntry(index);
			} else { 
				printf("branch lep3_ndof_branch does not exist!\n");
				exit(1);
			}
			lep3_ndof_isLoaded = true;
		}
		return lep3_ndof_;
	}
	float &lep3_pterr()
	{
		if (not lep3_pterr_isLoaded) {
			if (lep3_pterr_branch != 0) {
				lep3_pterr_branch->GetEntry(index);
			} else { 
				printf("branch lep3_pterr_branch does not exist!\n");
				exit(1);
			}
			lep3_pterr_isLoaded = true;
		}
		return lep3_pterr_;
	}
	float &lep3_ecal_vetodep()
	{
		if (not lep3_ecal_vetodep_isLoaded) {
			if (lep3_ecal_vetodep_branch != 0) {
				lep3_ecal_vetodep_branch->GetEntry(index);
			} else { 
				printf("branch lep3_ecal_vetodep_branch does not exist!\n");
				exit(1);
			}
			lep3_ecal_vetodep_isLoaded = true;
		}
		return lep3_ecal_vetodep_;
	}
	float &lep3_hcal_vetodep()
	{
		if (not lep3_hcal_vetodep_isLoaded) {
			if (lep3_hcal_vetodep_branch != 0) {
				lep3_hcal_vetodep_branch->GetEntry(index);
			} else { 
				printf("branch lep3_hcal_vetodep_branch does not exist!\n");
				exit(1);
			}
			lep3_hcal_vetodep_isLoaded = true;
		}
		return lep3_hcal_vetodep_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_p4()
	{
		if (not lep3_p4_isLoaded) {
			if (lep3_p4_branch != 0) {
				lep3_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep3_p4_branch does not exist!\n");
				exit(1);
			}
			lep3_p4_isLoaded = true;
		}
		return *lep3_p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_mcp4()
	{
		if (not lep3_mcp4_isLoaded) {
			if (lep3_mcp4_branch != 0) {
				lep3_mcp4_branch->GetEntry(index);
			} else { 
				printf("branch lep3_mcp4_branch does not exist!\n");
				exit(1);
			}
			lep3_mcp4_isLoaded = true;
		}
		return *lep3_mcp4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_mc3p4()
	{
		if (not lep3_mc3p4_isLoaded) {
			if (lep3_mc3p4_branch != 0) {
				lep3_mc3p4_branch->GetEntry(index);
			} else { 
				printf("branch lep3_mc3p4_branch does not exist!\n");
				exit(1);
			}
			lep3_mc3p4_isLoaded = true;
		}
		return *lep3_mc3p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_mc_momp4()
	{
		if (not lep3_mc_momp4_isLoaded) {
			if (lep3_mc_momp4_branch != 0) {
				lep3_mc_momp4_branch->GetEntry(index);
			} else { 
				printf("branch lep3_mc_momp4_branch does not exist!\n");
				exit(1);
			}
			lep3_mc_momp4_isLoaded = true;
		}
		return *lep3_mc_momp4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_gsf_p4()
	{
		if (not lep3_gsf_p4_isLoaded) {
			if (lep3_gsf_p4_branch != 0) {
				lep3_gsf_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep3_gsf_p4_branch does not exist!\n");
				exit(1);
			}
			lep3_gsf_p4_isLoaded = true;
		}
		return *lep3_gsf_p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_ctf_p4()
	{
		if (not lep3_ctf_p4_isLoaded) {
			if (lep3_ctf_p4_branch != 0) {
				lep3_ctf_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep3_ctf_p4_branch does not exist!\n");
				exit(1);
			}
			lep3_ctf_p4_isLoaded = true;
		}
		return *lep3_ctf_p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_sc_p4()
	{
		if (not lep3_sc_p4_isLoaded) {
			if (lep3_sc_p4_branch != 0) {
				lep3_sc_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep3_sc_p4_branch does not exist!\n");
				exit(1);
			}
			lep3_sc_p4_isLoaded = true;
		}
		return *lep3_sc_p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_gfit_p4()
	{
		if (not lep3_gfit_p4_isLoaded) {
			if (lep3_gfit_p4_branch != 0) {
				lep3_gfit_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep3_gfit_p4_branch does not exist!\n");
				exit(1);
			}
			lep3_gfit_p4_isLoaded = true;
		}
		return *lep3_gfit_p4_;
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
	bool &	charge_type()
	{
		if (not charge_type_isLoaded) {
			if (charge_type_branch != 0) {
				charge_type_branch->GetEntry(index);
			} else { 
				printf("branch charge_type_branch does not exist!\n");
				exit(1);
			}
			charge_type_isLoaded = true;
		}
		return charge_type_;
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
	int &nbtags_loose()
	{
		if (not nbtags_loose_isLoaded) {
			if (nbtags_loose_branch != 0) {
				nbtags_loose_branch->GetEntry(index);
			} else { 
				printf("branch nbtags_loose_branch does not exist!\n");
				exit(1);
			}
			nbtags_loose_isLoaded = true;
		}
		return nbtags_loose_;
	}
	int &ttbar_bkdn()
	{
		if (not ttbar_bkdn_isLoaded) {
			if (ttbar_bkdn_branch != 0) {
				ttbar_bkdn_branch->GetEntry(index);
			} else { 
				printf("branch ttbar_bkdn_branch does not exist!\n");
				exit(1);
			}
			ttbar_bkdn_isLoaded = true;
		}
		return ttbar_bkdn_;
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
	float &mt()
	{
		if (not mt_isLoaded) {
			if (mt_branch != 0) {
				mt_branch->GetEntry(index);
			} else { 
				printf("branch mt_branch does not exist!\n");
				exit(1);
			}
			mt_isLoaded = true;
		}
		return mt_;
	}
	float &mt2()
	{
		if (not mt2_isLoaded) {
			if (mt2_branch != 0) {
				mt2_branch->GetEntry(index);
			} else { 
				printf("branch mt2_branch does not exist!\n");
				exit(1);
			}
			mt2_isLoaded = true;
		}
		return mt2_;
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
	bool &	trig_mm_mu17_mu8()
	{
		if (not trig_mm_mu17_mu8_isLoaded) {
			if (trig_mm_mu17_mu8_branch != 0) {
				trig_mm_mu17_mu8_branch->GetEntry(index);
			} else { 
				printf("branch trig_mm_mu17_mu8_branch does not exist!\n");
				exit(1);
			}
			trig_mm_mu17_mu8_isLoaded = true;
		}
		return trig_mm_mu17_mu8_;
	}
	bool &	trig_ee_el17_el8_id_iso()
	{
		if (not trig_ee_el17_el8_id_iso_isLoaded) {
			if (trig_ee_el17_el8_id_iso_branch != 0) {
				trig_ee_el17_el8_id_iso_branch->GetEntry(index);
			} else { 
				printf("branch trig_ee_el17_el8_id_iso_branch does not exist!\n");
				exit(1);
			}
			trig_ee_el17_el8_id_iso_isLoaded = true;
		}
		return trig_ee_el17_el8_id_iso_;
	}
	bool &	trig_em_mu17_el8_id_iso()
	{
		if (not trig_em_mu17_el8_id_iso_isLoaded) {
			if (trig_em_mu17_el8_id_iso_branch != 0) {
				trig_em_mu17_el8_id_iso_branch->GetEntry(index);
			} else { 
				printf("branch trig_em_mu17_el8_id_iso_branch does not exist!\n");
				exit(1);
			}
			trig_em_mu17_el8_id_iso_isLoaded = true;
		}
		return trig_em_mu17_el8_id_iso_;
	}
	bool &	trig_em_mu8_el17_id_iso()
	{
		if (not trig_em_mu8_el17_id_iso_isLoaded) {
			if (trig_em_mu8_el17_id_iso_branch != 0) {
				trig_em_mu8_el17_id_iso_branch->GetEntry(index);
			} else { 
				printf("branch trig_em_mu8_el17_id_iso_branch does not exist!\n");
				exit(1);
			}
			trig_em_mu8_el17_id_iso_isLoaded = true;
		}
		return trig_em_mu8_el17_id_iso_;
	}
	int &njets_dn()
	{
		if (not njets_dn_isLoaded) {
			if (njets_dn_branch != 0) {
				njets_dn_branch->GetEntry(index);
			} else { 
				printf("branch njets_dn_branch does not exist!\n");
				exit(1);
			}
			njets_dn_isLoaded = true;
		}
		return njets_dn_;
	}
	int &njets_up()
	{
		if (not njets_up_isLoaded) {
			if (njets_up_branch != 0) {
				njets_up_branch->GetEntry(index);
			} else { 
				printf("branch njets_up_branch does not exist!\n");
				exit(1);
			}
			njets_up_isLoaded = true;
		}
		return njets_up_;
	}
	int &nbtags_dn()
	{
		if (not nbtags_dn_isLoaded) {
			if (nbtags_dn_branch != 0) {
				nbtags_dn_branch->GetEntry(index);
			} else { 
				printf("branch nbtags_dn_branch does not exist!\n");
				exit(1);
			}
			nbtags_dn_isLoaded = true;
		}
		return nbtags_dn_;
	}
	int &nbtags_up()
	{
		if (not nbtags_up_isLoaded) {
			if (nbtags_up_branch != 0) {
				nbtags_up_branch->GetEntry(index);
			} else { 
				printf("branch nbtags_up_branch does not exist!\n");
				exit(1);
			}
			nbtags_up_isLoaded = true;
		}
		return nbtags_up_;
	}
	float &ht_dn()
	{
		if (not ht_dn_isLoaded) {
			if (ht_dn_branch != 0) {
				ht_dn_branch->GetEntry(index);
			} else { 
				printf("branch ht_dn_branch does not exist!\n");
				exit(1);
			}
			ht_dn_isLoaded = true;
		}
		return ht_dn_;
	}
	float &ht_up()
	{
		if (not ht_up_isLoaded) {
			if (ht_up_branch != 0) {
				ht_up_branch->GetEntry(index);
			} else { 
				printf("branch ht_up_branch does not exist!\n");
				exit(1);
			}
			ht_up_isLoaded = true;
		}
		return ht_up_;
	}
	int &nbtags_reweighted()
	{
		if (not nbtags_reweighted_isLoaded) {
			if (nbtags_reweighted_branch != 0) {
				nbtags_reweighted_branch->GetEntry(index);
			} else { 
				printf("branch nbtags_reweighted_branch does not exist!\n");
				exit(1);
			}
			nbtags_reweighted_isLoaded = true;
		}
		return nbtags_reweighted_;
	}
	int &nbtags_reweighted_dn()
	{
		if (not nbtags_reweighted_dn_isLoaded) {
			if (nbtags_reweighted_dn_branch != 0) {
				nbtags_reweighted_dn_branch->GetEntry(index);
			} else { 
				printf("branch nbtags_reweighted_dn_branch does not exist!\n");
				exit(1);
			}
			nbtags_reweighted_dn_isLoaded = true;
		}
		return nbtags_reweighted_dn_;
	}
	int &nbtags_reweighted_up()
	{
		if (not nbtags_reweighted_up_isLoaded) {
			if (nbtags_reweighted_up_branch != 0) {
				nbtags_reweighted_up_branch->GetEntry(index);
			} else { 
				printf("branch nbtags_reweighted_up_branch does not exist!\n");
				exit(1);
			}
			nbtags_reweighted_up_isLoaded = true;
		}
		return nbtags_reweighted_up_;
	}
	int &nbtags_reweighted_jec_dn()
	{
		if (not nbtags_reweighted_jec_dn_isLoaded) {
			if (nbtags_reweighted_jec_dn_branch != 0) {
				nbtags_reweighted_jec_dn_branch->GetEntry(index);
			} else { 
				printf("branch nbtags_reweighted_jec_dn_branch does not exist!\n");
				exit(1);
			}
			nbtags_reweighted_jec_dn_isLoaded = true;
		}
		return nbtags_reweighted_jec_dn_;
	}
	int &nbtags_reweighted_jec_up()
	{
		if (not nbtags_reweighted_jec_up_isLoaded) {
			if (nbtags_reweighted_jec_up_branch != 0) {
				nbtags_reweighted_jec_up_branch->GetEntry(index);
			} else { 
				printf("branch nbtags_reweighted_jec_up_branch does not exist!\n");
				exit(1);
			}
			nbtags_reweighted_jec_up_isLoaded = true;
		}
		return nbtags_reweighted_jec_up_;
	}
	float &pfmet_dn()
	{
		if (not pfmet_dn_isLoaded) {
			if (pfmet_dn_branch != 0) {
				pfmet_dn_branch->GetEntry(index);
			} else { 
				printf("branch pfmet_dn_branch does not exist!\n");
				exit(1);
			}
			pfmet_dn_isLoaded = true;
		}
		return pfmet_dn_;
	}
	float &pfmet_up()
	{
		if (not pfmet_up_isLoaded) {
			if (pfmet_up_branch != 0) {
				pfmet_up_branch->GetEntry(index);
			} else { 
				printf("branch pfmet_up_branch does not exist!\n");
				exit(1);
			}
			pfmet_up_isLoaded = true;
		}
		return pfmet_up_;
	}
	float &pfmet_phi_dn()
	{
		if (not pfmet_phi_dn_isLoaded) {
			if (pfmet_phi_dn_branch != 0) {
				pfmet_phi_dn_branch->GetEntry(index);
			} else { 
				printf("branch pfmet_phi_dn_branch does not exist!\n");
				exit(1);
			}
			pfmet_phi_dn_isLoaded = true;
		}
		return pfmet_phi_dn_;
	}
	float &pfmet_phi_up()
	{
		if (not pfmet_phi_up_isLoaded) {
			if (pfmet_phi_up_branch != 0) {
				pfmet_phi_up_branch->GetEntry(index);
			} else { 
				printf("branch pfmet_phi_up_branch does not exist!\n");
				exit(1);
			}
			pfmet_phi_up_isLoaded = true;
		}
		return pfmet_phi_up_;
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
	TString &sparm0_name()
	{
		if (not sparm0_name_isLoaded) {
			if (sparm0_name_branch != 0) {
				sparm0_name_branch->GetEntry(index);
			} else { 
				printf("branch sparm0_name_branch does not exist!\n");
				exit(1);
			}
			sparm0_name_isLoaded = true;
		}
		return *sparm0_name_;
	}
	TString &sparm1_name()
	{
		if (not sparm1_name_isLoaded) {
			if (sparm1_name_branch != 0) {
				sparm1_name_branch->GetEntry(index);
			} else { 
				printf("branch sparm1_name_branch does not exist!\n");
				exit(1);
			}
			sparm1_name_isLoaded = true;
		}
		return *sparm1_name_;
	}
	TString &sparm2_name()
	{
		if (not sparm2_name_isLoaded) {
			if (sparm2_name_branch != 0) {
				sparm2_name_branch->GetEntry(index);
			} else { 
				printf("branch sparm2_name_branch does not exist!\n");
				exit(1);
			}
			sparm2_name_isLoaded = true;
		}
		return *sparm2_name_;
	}
	TString &sparm3_name()
	{
		if (not sparm3_name_isLoaded) {
			if (sparm3_name_branch != 0) {
				sparm3_name_branch->GetEntry(index);
			} else { 
				printf("branch sparm3_name_branch does not exist!\n");
				exit(1);
			}
			sparm3_name_isLoaded = true;
		}
		return *sparm3_name_;
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
	bool &	no_extrag()
	{
		if (not no_extrag_isLoaded) {
			if (no_extrag_branch != 0) {
				no_extrag_branch->GetEntry(index);
			} else { 
				printf("branch no_extrag_branch does not exist!\n");
				exit(1);
			}
			no_extrag_isLoaded = true;
		}
		return no_extrag_;
	}
	bool &	clean()
	{
		if (not clean_isLoaded) {
			if (clean_branch != 0) {
				clean_branch->GetEntry(index);
			} else { 
				printf("branch clean_branch does not exist!\n");
				exit(1);
			}
			clean_isLoaded = true;
		}
		return clean_;
	}
	bool &	presel()
	{
		if (not presel_isLoaded) {
			if (presel_branch != 0) {
				presel_branch->GetEntry(index);
			} else { 
				printf("branch presel_branch does not exist!\n");
				exit(1);
			}
			presel_isLoaded = true;
		}
		return presel_;
	}
	bool &	em_mufo()
	{
		if (not em_mufo_isLoaded) {
			if (em_mufo_branch != 0) {
				em_mufo_branch->GetEntry(index);
			} else { 
				printf("branch em_mufo_branch does not exist!\n");
				exit(1);
			}
			em_mufo_isLoaded = true;
		}
		return em_mufo_;
	}
	bool &	em_elfo()
	{
		if (not em_elfo_isLoaded) {
			if (em_elfo_branch != 0) {
				em_elfo_branch->GetEntry(index);
			} else { 
				printf("branch em_elfo_branch does not exist!\n");
				exit(1);
			}
			em_elfo_isLoaded = true;
		}
		return em_elfo_;
	}
	bool &	hyp_good_vtx()
	{
		if (not hyp_good_vtx_isLoaded) {
			if (hyp_good_vtx_branch != 0) {
				hyp_good_vtx_branch->GetEntry(index);
			} else { 
				printf("branch hyp_good_vtx_branch does not exist!\n");
				exit(1);
			}
			hyp_good_vtx_isLoaded = true;
		}
		return hyp_good_vtx_;
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
	int &gen_nleps()
	{
		if (not gen_nleps_isLoaded) {
			if (gen_nleps_branch != 0) {
				gen_nleps_branch->GetEntry(index);
			} else { 
				printf("branch gen_nleps_branch does not exist!\n");
				exit(1);
			}
			gen_nleps_isLoaded = true;
		}
		return gen_nleps_;
	}
	int &gen_nmus()
	{
		if (not gen_nmus_isLoaded) {
			if (gen_nmus_branch != 0) {
				gen_nmus_branch->GetEntry(index);
			} else { 
				printf("branch gen_nmus_branch does not exist!\n");
				exit(1);
			}
			gen_nmus_isLoaded = true;
		}
		return gen_nmus_;
	}
	int &gen_nels()
	{
		if (not gen_nels_isLoaded) {
			if (gen_nels_branch != 0) {
				gen_nels_branch->GetEntry(index);
			} else { 
				printf("branch gen_nels_branch does not exist!\n");
				exit(1);
			}
			gen_nels_isLoaded = true;
		}
		return gen_nels_;
	}
	int &gen_ntaus()
	{
		if (not gen_ntaus_isLoaded) {
			if (gen_ntaus_branch != 0) {
				gen_ntaus_branch->GetEntry(index);
			} else { 
				printf("branch gen_ntaus_branch does not exist!\n");
				exit(1);
			}
			gen_ntaus_isLoaded = true;
		}
		return gen_ntaus_;
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
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearlep_p4()
	{
		if (not lep1_nearlep_p4_isLoaded) {
			if (lep1_nearlep_p4_branch != 0) {
				lep1_nearlep_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep1_nearlep_p4_branch does not exist!\n");
				exit(1);
			}
			lep1_nearlep_p4_isLoaded = true;
		}
		return *lep1_nearlep_p4_;
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
	float &lep1_nearlep_dr()
	{
		if (not lep1_nearlep_dr_isLoaded) {
			if (lep1_nearlep_dr_branch != 0) {
				lep1_nearlep_dr_branch->GetEntry(index);
			} else { 
				printf("branch lep1_nearlep_dr_branch does not exist!\n");
				exit(1);
			}
			lep1_nearlep_dr_isLoaded = true;
		}
		return lep1_nearlep_dr_;
	}
	int &lep1_nearlep_id()
	{
		if (not lep1_nearlep_id_isLoaded) {
			if (lep1_nearlep_id_branch != 0) {
				lep1_nearlep_id_branch->GetEntry(index);
			} else { 
				printf("branch lep1_nearlep_id_branch does not exist!\n");
				exit(1);
			}
			lep1_nearlep_id_isLoaded = true;
		}
		return lep1_nearlep_id_;
	}
	bool &	lep1_isFromH()
	{
		if (not lep1_isFromH_isLoaded) {
			if (lep1_isFromH_branch != 0) {
				lep1_isFromH_branch->GetEntry(index);
			} else { 
				printf("branch lep1_isFromH_branch does not exist!\n");
				exit(1);
			}
			lep1_isFromH_isLoaded = true;
		}
		return lep1_isFromH_;
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
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearlep_p4()
	{
		if (not lep2_nearlep_p4_isLoaded) {
			if (lep2_nearlep_p4_branch != 0) {
				lep2_nearlep_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep2_nearlep_p4_branch does not exist!\n");
				exit(1);
			}
			lep2_nearlep_p4_isLoaded = true;
		}
		return *lep2_nearlep_p4_;
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
	float &lep2_nearlep_dr()
	{
		if (not lep2_nearlep_dr_isLoaded) {
			if (lep2_nearlep_dr_branch != 0) {
				lep2_nearlep_dr_branch->GetEntry(index);
			} else { 
				printf("branch lep2_nearlep_dr_branch does not exist!\n");
				exit(1);
			}
			lep2_nearlep_dr_isLoaded = true;
		}
		return lep2_nearlep_dr_;
	}
	int &lep2_nearlep_id()
	{
		if (not lep2_nearlep_id_isLoaded) {
			if (lep2_nearlep_id_branch != 0) {
				lep2_nearlep_id_branch->GetEntry(index);
			} else { 
				printf("branch lep2_nearlep_id_branch does not exist!\n");
				exit(1);
			}
			lep2_nearlep_id_isLoaded = true;
		}
		return lep2_nearlep_id_;
	}
	bool &	lep2_isFromH()
	{
		if (not lep2_isFromH_isLoaded) {
			if (lep2_isFromH_branch != 0) {
				lep2_isFromH_branch->GetEntry(index);
			} else { 
				printf("branch lep2_isFromH_branch does not exist!\n");
				exit(1);
			}
			lep2_isFromH_isLoaded = true;
		}
		return lep2_isFromH_;
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
	float &dijet_mass()
	{
		if (not dijet_mass_isLoaded) {
			if (dijet_mass_branch != 0) {
				dijet_mass_branch->GetEntry(index);
			} else { 
				printf("branch dijet_mass_branch does not exist!\n");
				exit(1);
			}
			dijet_mass_isLoaded = true;
		}
		return dijet_mass_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_p4()
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
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_p4_up()
	{
		if (not vjets_p4_up_isLoaded) {
			if (vjets_p4_up_branch != 0) {
				vjets_p4_up_branch->GetEntry(index);
			} else { 
				printf("branch vjets_p4_up_branch does not exist!\n");
				exit(1);
			}
			vjets_p4_up_isLoaded = true;
		}
		return *vjets_p4_up_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_p4_dn()
	{
		if (not vjets_p4_dn_isLoaded) {
			if (vjets_p4_dn_branch != 0) {
				vjets_p4_dn_branch->GetEntry(index);
			} else { 
				printf("branch vjets_p4_dn_branch does not exist!\n");
				exit(1);
			}
			vjets_p4_dn_isLoaded = true;
		}
		return *vjets_p4_dn_;
	}
	const vector<int> &vjets_mcflavor_phys()
	{
		if (not vjets_mcflavor_phys_isLoaded) {
			if (vjets_mcflavor_phys_branch != 0) {
				vjets_mcflavor_phys_branch->GetEntry(index);
			} else { 
				printf("branch vjets_mcflavor_phys_branch does not exist!\n");
				exit(1);
			}
			vjets_mcflavor_phys_isLoaded = true;
		}
		return *vjets_mcflavor_phys_;
	}
	const vector<int> &vjets_mcflavor_algo()
	{
		if (not vjets_mcflavor_algo_isLoaded) {
			if (vjets_mcflavor_algo_branch != 0) {
				vjets_mcflavor_algo_branch->GetEntry(index);
			} else { 
				printf("branch vjets_mcflavor_algo_branch does not exist!\n");
				exit(1);
			}
			vjets_mcflavor_algo_isLoaded = true;
		}
		return *vjets_mcflavor_algo_;
	}
	const vector<int> &vjets_mcflavor_phys_up()
	{
		if (not vjets_mcflavor_phys_up_isLoaded) {
			if (vjets_mcflavor_phys_up_branch != 0) {
				vjets_mcflavor_phys_up_branch->GetEntry(index);
			} else { 
				printf("branch vjets_mcflavor_phys_up_branch does not exist!\n");
				exit(1);
			}
			vjets_mcflavor_phys_up_isLoaded = true;
		}
		return *vjets_mcflavor_phys_up_;
	}
	const vector<int> &vjets_mcflavor_algo_up()
	{
		if (not vjets_mcflavor_algo_up_isLoaded) {
			if (vjets_mcflavor_algo_up_branch != 0) {
				vjets_mcflavor_algo_up_branch->GetEntry(index);
			} else { 
				printf("branch vjets_mcflavor_algo_up_branch does not exist!\n");
				exit(1);
			}
			vjets_mcflavor_algo_up_isLoaded = true;
		}
		return *vjets_mcflavor_algo_up_;
	}
	const vector<int> &vjets_mcflavor_phys_dn()
	{
		if (not vjets_mcflavor_phys_dn_isLoaded) {
			if (vjets_mcflavor_phys_dn_branch != 0) {
				vjets_mcflavor_phys_dn_branch->GetEntry(index);
			} else { 
				printf("branch vjets_mcflavor_phys_dn_branch does not exist!\n");
				exit(1);
			}
			vjets_mcflavor_phys_dn_isLoaded = true;
		}
		return *vjets_mcflavor_phys_dn_;
	}
	const vector<int> &vjets_mcflavor_algo_dn()
	{
		if (not vjets_mcflavor_algo_dn_isLoaded) {
			if (vjets_mcflavor_algo_dn_branch != 0) {
				vjets_mcflavor_algo_dn_branch->GetEntry(index);
			} else { 
				printf("branch vjets_mcflavor_algo_dn_branch does not exist!\n");
				exit(1);
			}
			vjets_mcflavor_algo_dn_isLoaded = true;
		}
		return *vjets_mcflavor_algo_dn_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_mc3p4()
	{
		if (not vjets_mc3p4_isLoaded) {
			if (vjets_mc3p4_branch != 0) {
				vjets_mc3p4_branch->GetEntry(index);
			} else { 
				printf("branch vjets_mc3p4_branch does not exist!\n");
				exit(1);
			}
			vjets_mc3p4_isLoaded = true;
		}
		return *vjets_mc3p4_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vgenjets_p4()
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
	const vector<int> &vjets_mc3id()
	{
		if (not vjets_mc3id_isLoaded) {
			if (vjets_mc3id_branch != 0) {
				vjets_mc3id_branch->GetEntry(index);
			} else { 
				printf("branch vjets_mc3id_branch does not exist!\n");
				exit(1);
			}
			vjets_mc3id_isLoaded = true;
		}
		return *vjets_mc3id_;
	}
	const vector<int> &vjets_momid()
	{
		if (not vjets_momid_isLoaded) {
			if (vjets_momid_branch != 0) {
				vjets_momid_branch->GetEntry(index);
			} else { 
				printf("branch vjets_momid_branch does not exist!\n");
				exit(1);
			}
			vjets_momid_isLoaded = true;
		}
		return *vjets_momid_;
	}
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_nearjet_p4()
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
	const vector<float> &vjets_nearjet_dr()
	{
		if (not vjets_nearjet_dr_isLoaded) {
			if (vjets_nearjet_dr_branch != 0) {
				vjets_nearjet_dr_branch->GetEntry(index);
			} else { 
				printf("branch vjets_nearjet_dr_branch does not exist!\n");
				exit(1);
			}
			vjets_nearjet_dr_isLoaded = true;
		}
		return *vjets_nearjet_dr_;
	}
	const vector<float> &vjets_bdisc()
	{
		if (not vjets_bdisc_isLoaded) {
			if (vjets_bdisc_branch != 0) {
				vjets_bdisc_branch->GetEntry(index);
			} else { 
				printf("branch vjets_bdisc_branch does not exist!\n");
				exit(1);
			}
			vjets_bdisc_isLoaded = true;
		}
		return *vjets_bdisc_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep1_p4()
	{
		if (not gen_lep1_p4_isLoaded) {
			if (gen_lep1_p4_branch != 0) {
				gen_lep1_p4_branch->GetEntry(index);
			} else { 
				printf("branch gen_lep1_p4_branch does not exist!\n");
				exit(1);
			}
			gen_lep1_p4_isLoaded = true;
		}
		return *gen_lep1_p4_;
	}
	int &gen_lep1_pdgid()
	{
		if (not gen_lep1_pdgid_isLoaded) {
			if (gen_lep1_pdgid_branch != 0) {
				gen_lep1_pdgid_branch->GetEntry(index);
			} else { 
				printf("branch gen_lep1_pdgid_branch does not exist!\n");
				exit(1);
			}
			gen_lep1_pdgid_isLoaded = true;
		}
		return gen_lep1_pdgid_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep2_p4()
	{
		if (not gen_lep2_p4_isLoaded) {
			if (gen_lep2_p4_branch != 0) {
				gen_lep2_p4_branch->GetEntry(index);
			} else { 
				printf("branch gen_lep2_p4_branch does not exist!\n");
				exit(1);
			}
			gen_lep2_p4_isLoaded = true;
		}
		return *gen_lep2_p4_;
	}
	int &gen_lep2_pdgid()
	{
		if (not gen_lep2_pdgid_isLoaded) {
			if (gen_lep2_pdgid_branch != 0) {
				gen_lep2_pdgid_branch->GetEntry(index);
			} else { 
				printf("branch gen_lep2_pdgid_branch does not exist!\n");
				exit(1);
			}
			gen_lep2_pdgid_isLoaded = true;
		}
		return gen_lep2_pdgid_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_dilep_p4()
	{
		if (not gen_dilep_p4_isLoaded) {
			if (gen_dilep_p4_branch != 0) {
				gen_dilep_p4_branch->GetEntry(index);
			} else { 
				printf("branch gen_dilep_p4_branch does not exist!\n");
				exit(1);
			}
			gen_dilep_p4_isLoaded = true;
		}
		return *gen_dilep_p4_;
	}
	int &gen_dilep_type()
	{
		if (not gen_dilep_type_isLoaded) {
			if (gen_dilep_type_branch != 0) {
				gen_dilep_type_branch->GetEntry(index);
			} else { 
				printf("branch gen_dilep_type_branch does not exist!\n");
				exit(1);
			}
			gen_dilep_type_isLoaded = true;
		}
		return gen_dilep_type_;
	}
	float &gen_dilep_mass()
	{
		if (not gen_dilep_mass_isLoaded) {
			if (gen_dilep_mass_branch != 0) {
				gen_dilep_mass_branch->GetEntry(index);
			} else { 
				printf("branch gen_dilep_mass_branch does not exist!\n");
				exit(1);
			}
			gen_dilep_mass_isLoaded = true;
		}
		return gen_dilep_mass_;
	}
	float &gen_dilep_dphi()
	{
		if (not gen_dilep_dphi_isLoaded) {
			if (gen_dilep_dphi_branch != 0) {
				gen_dilep_dphi_branch->GetEntry(index);
			} else { 
				printf("branch gen_dilep_dphi_branch does not exist!\n");
				exit(1);
			}
			gen_dilep_dphi_isLoaded = true;
		}
		return gen_dilep_dphi_;
	}
	float &gen_dilep_deta()
	{
		if (not gen_dilep_deta_isLoaded) {
			if (gen_dilep_deta_branch != 0) {
				gen_dilep_deta_branch->GetEntry(index);
			} else { 
				printf("branch gen_dilep_deta_branch does not exist!\n");
				exit(1);
			}
			gen_dilep_deta_isLoaded = true;
		}
		return gen_dilep_deta_;
	}
	float &gen_dilep_dr()
	{
		if (not gen_dilep_dr_isLoaded) {
			if (gen_dilep_dr_branch != 0) {
				gen_dilep_dr_branch->GetEntry(index);
			} else { 
				printf("branch gen_dilep_dr_branch does not exist!\n");
				exit(1);
			}
			gen_dilep_dr_isLoaded = true;
		}
		return gen_dilep_dr_;
	}
	int &pfcandid5()
	{
		if (not pfcandid5_isLoaded) {
			if (pfcandid5_branch != 0) {
				pfcandid5_branch->GetEntry(index);
			} else { 
				printf("branch pfcandid5_branch does not exist!\n");
				exit(1);
			}
			pfcandid5_isLoaded = true;
		}
		return pfcandid5_;
	}
	int &pfcandid10()
	{
		if (not pfcandid10_isLoaded) {
			if (pfcandid10_branch != 0) {
				pfcandid10_branch->GetEntry(index);
			} else { 
				printf("branch pfcandid10_branch does not exist!\n");
				exit(1);
			}
			pfcandid10_isLoaded = true;
		}
		return pfcandid10_;
	}
	int &pfcanddirid10()
	{
		if (not pfcanddirid10_isLoaded) {
			if (pfcanddirid10_branch != 0) {
				pfcanddirid10_branch->GetEntry(index);
			} else { 
				printf("branch pfcanddirid10_branch does not exist!\n");
				exit(1);
			}
			pfcanddirid10_isLoaded = true;
		}
		return pfcanddirid10_;
	}
	int &pfcandvetoid10()
	{
		if (not pfcandvetoid10_isLoaded) {
			if (pfcandvetoid10_branch != 0) {
				pfcandvetoid10_branch->GetEntry(index);
			} else { 
				printf("branch pfcandvetoid10_branch does not exist!\n");
				exit(1);
			}
			pfcandvetoid10_isLoaded = true;
		}
		return pfcandvetoid10_;
	}
	int &pfcandvetoLid10()
	{
		if (not pfcandvetoLid10_isLoaded) {
			if (pfcandvetoLid10_branch != 0) {
				pfcandvetoLid10_branch->GetEntry(index);
			} else { 
				printf("branch pfcandvetoLid10_branch does not exist!\n");
				exit(1);
			}
			pfcandvetoLid10_isLoaded = true;
		}
		return pfcandvetoLid10_;
	}
	int &pfcandidOS10()
	{
		if (not pfcandidOS10_isLoaded) {
			if (pfcandidOS10_branch != 0) {
				pfcandidOS10_branch->GetEntry(index);
			} else { 
				printf("branch pfcandidOS10_branch does not exist!\n");
				exit(1);
			}
			pfcandidOS10_isLoaded = true;
		}
		return pfcandidOS10_;
	}
	int &pfcandidOS10looseZ()
	{
		if (not pfcandidOS10looseZ_isLoaded) {
			if (pfcandidOS10looseZ_branch != 0) {
				pfcandidOS10looseZ_branch->GetEntry(index);
			} else { 
				printf("branch pfcandidOS10looseZ_branch does not exist!\n");
				exit(1);
			}
			pfcandidOS10looseZ_isLoaded = true;
		}
		return pfcandidOS10looseZ_;
	}
	int &pfcandid5looseZ()
	{
		if (not pfcandid5looseZ_isLoaded) {
			if (pfcandid5looseZ_branch != 0) {
				pfcandid5looseZ_branch->GetEntry(index);
			} else { 
				printf("branch pfcandid5looseZ_branch does not exist!\n");
				exit(1);
			}
			pfcandid5looseZ_isLoaded = true;
		}
		return pfcandid5looseZ_;
	}
	float &trkpt5()
	{
		if (not trkpt5_isLoaded) {
			if (trkpt5_branch != 0) {
				trkpt5_branch->GetEntry(index);
			} else { 
				printf("branch trkpt5_branch does not exist!\n");
				exit(1);
			}
			trkpt5_isLoaded = true;
		}
		return trkpt5_;
	}
	float &mleptrk5()
	{
		if (not mleptrk5_isLoaded) {
			if (mleptrk5_branch != 0) {
				mleptrk5_branch->GetEntry(index);
			} else { 
				printf("branch mleptrk5_branch does not exist!\n");
				exit(1);
			}
			mleptrk5_isLoaded = true;
		}
		return mleptrk5_;
	}
	float &trkreliso5()
	{
		if (not trkreliso5_isLoaded) {
			if (trkreliso5_branch != 0) {
				trkreliso5_branch->GetEntry(index);
			} else { 
				printf("branch trkreliso5_branch does not exist!\n");
				exit(1);
			}
			trkreliso5_isLoaded = true;
		}
		return trkreliso5_;
	}
	float &trkpt10()
	{
		if (not trkpt10_isLoaded) {
			if (trkpt10_branch != 0) {
				trkpt10_branch->GetEntry(index);
			} else { 
				printf("branch trkpt10_branch does not exist!\n");
				exit(1);
			}
			trkpt10_isLoaded = true;
		}
		return trkpt10_;
	}
	float &mleptrk10()
	{
		if (not mleptrk10_isLoaded) {
			if (mleptrk10_branch != 0) {
				mleptrk10_branch->GetEntry(index);
			} else { 
				printf("branch mleptrk10_branch does not exist!\n");
				exit(1);
			}
			mleptrk10_isLoaded = true;
		}
		return mleptrk10_;
	}
	float &trkreliso10()
	{
		if (not trkreliso10_isLoaded) {
			if (trkreliso10_branch != 0) {
				trkreliso10_branch->GetEntry(index);
			} else { 
				printf("branch trkreliso10_branch does not exist!\n");
				exit(1);
			}
			trkreliso10_isLoaded = true;
		}
		return trkreliso10_;
	}
	float &trkpt5loose()
	{
		if (not trkpt5loose_isLoaded) {
			if (trkpt5loose_branch != 0) {
				trkpt5loose_branch->GetEntry(index);
			} else { 
				printf("branch trkpt5loose_branch does not exist!\n");
				exit(1);
			}
			trkpt5loose_isLoaded = true;
		}
		return trkpt5loose_;
	}
	float &trkreliso5loose()
	{
		if (not trkreliso5loose_isLoaded) {
			if (trkreliso5loose_branch != 0) {
				trkreliso5loose_branch->GetEntry(index);
			} else { 
				printf("branch trkreliso5loose_branch does not exist!\n");
				exit(1);
			}
			trkreliso5loose_isLoaded = true;
		}
		return trkreliso5loose_;
	}
	float &trkpt10loose()
	{
		if (not trkpt10loose_isLoaded) {
			if (trkpt10loose_branch != 0) {
				trkpt10loose_branch->GetEntry(index);
			} else { 
				printf("branch trkpt10loose_branch does not exist!\n");
				exit(1);
			}
			trkpt10loose_isLoaded = true;
		}
		return trkpt10loose_;
	}
	float &trkreliso10loose()
	{
		if (not trkreliso10loose_isLoaded) {
			if (trkreliso10loose_branch != 0) {
				trkreliso10loose_branch->GetEntry(index);
			} else { 
				printf("branch trkreliso10loose_branch does not exist!\n");
				exit(1);
			}
			trkreliso10loose_isLoaded = true;
		}
		return trkreliso10loose_;
	}
	float &trkpt10pt0p1()
	{
		if (not trkpt10pt0p1_isLoaded) {
			if (trkpt10pt0p1_branch != 0) {
				trkpt10pt0p1_branch->GetEntry(index);
			} else { 
				printf("branch trkpt10pt0p1_branch does not exist!\n");
				exit(1);
			}
			trkpt10pt0p1_isLoaded = true;
		}
		return trkpt10pt0p1_;
	}
	float &trkreliso10pt0p1()
	{
		if (not trkreliso10pt0p1_isLoaded) {
			if (trkreliso10pt0p1_branch != 0) {
				trkreliso10pt0p1_branch->GetEntry(index);
			} else { 
				printf("branch trkreliso10pt0p1_branch does not exist!\n");
				exit(1);
			}
			trkreliso10pt0p1_isLoaded = true;
		}
		return trkreliso10pt0p1_;
	}
	float &trkpt10pt0p2()
	{
		if (not trkpt10pt0p2_isLoaded) {
			if (trkpt10pt0p2_branch != 0) {
				trkpt10pt0p2_branch->GetEntry(index);
			} else { 
				printf("branch trkpt10pt0p2_branch does not exist!\n");
				exit(1);
			}
			trkpt10pt0p2_isLoaded = true;
		}
		return trkpt10pt0p2_;
	}
	float &trkreliso10pt0p2()
	{
		if (not trkreliso10pt0p2_isLoaded) {
			if (trkreliso10pt0p2_branch != 0) {
				trkreliso10pt0p2_branch->GetEntry(index);
			} else { 
				printf("branch trkreliso10pt0p2_branch does not exist!\n");
				exit(1);
			}
			trkreliso10pt0p2_isLoaded = true;
		}
		return trkreliso10pt0p2_;
	}
	float &trkpt10pt0p3()
	{
		if (not trkpt10pt0p3_isLoaded) {
			if (trkpt10pt0p3_branch != 0) {
				trkpt10pt0p3_branch->GetEntry(index);
			} else { 
				printf("branch trkpt10pt0p3_branch does not exist!\n");
				exit(1);
			}
			trkpt10pt0p3_isLoaded = true;
		}
		return trkpt10pt0p3_;
	}
	float &trkreliso10pt0p3()
	{
		if (not trkreliso10pt0p3_isLoaded) {
			if (trkreliso10pt0p3_branch != 0) {
				trkreliso10pt0p3_branch->GetEntry(index);
			} else { 
				printf("branch trkreliso10pt0p3_branch does not exist!\n");
				exit(1);
			}
			trkreliso10pt0p3_isLoaded = true;
		}
		return trkreliso10pt0p3_;
	}
	float &trkpt10pt0p4()
	{
		if (not trkpt10pt0p4_isLoaded) {
			if (trkpt10pt0p4_branch != 0) {
				trkpt10pt0p4_branch->GetEntry(index);
			} else { 
				printf("branch trkpt10pt0p4_branch does not exist!\n");
				exit(1);
			}
			trkpt10pt0p4_isLoaded = true;
		}
		return trkpt10pt0p4_;
	}
	float &trkreliso10pt0p4()
	{
		if (not trkreliso10pt0p4_isLoaded) {
			if (trkreliso10pt0p4_branch != 0) {
				trkreliso10pt0p4_branch->GetEntry(index);
			} else { 
				printf("branch trkreliso10pt0p4_branch does not exist!\n");
				exit(1);
			}
			trkreliso10pt0p4_isLoaded = true;
		}
		return trkreliso10pt0p4_;
	}
	float &trkpt10pt0p5()
	{
		if (not trkpt10pt0p5_isLoaded) {
			if (trkpt10pt0p5_branch != 0) {
				trkpt10pt0p5_branch->GetEntry(index);
			} else { 
				printf("branch trkpt10pt0p5_branch does not exist!\n");
				exit(1);
			}
			trkpt10pt0p5_isLoaded = true;
		}
		return trkpt10pt0p5_;
	}
	float &trkreliso10pt0p5()
	{
		if (not trkreliso10pt0p5_isLoaded) {
			if (trkreliso10pt0p5_branch != 0) {
				trkreliso10pt0p5_branch->GetEntry(index);
			} else { 
				printf("branch trkreliso10pt0p5_branch does not exist!\n");
				exit(1);
			}
			trkreliso10pt0p5_isLoaded = true;
		}
		return trkreliso10pt0p5_;
	}
	float &trkpt10pt0p6()
	{
		if (not trkpt10pt0p6_isLoaded) {
			if (trkpt10pt0p6_branch != 0) {
				trkpt10pt0p6_branch->GetEntry(index);
			} else { 
				printf("branch trkpt10pt0p6_branch does not exist!\n");
				exit(1);
			}
			trkpt10pt0p6_isLoaded = true;
		}
		return trkpt10pt0p6_;
	}
	float &trkreliso10pt0p6()
	{
		if (not trkreliso10pt0p6_isLoaded) {
			if (trkreliso10pt0p6_branch != 0) {
				trkreliso10pt0p6_branch->GetEntry(index);
			} else { 
				printf("branch trkreliso10pt0p6_branch does not exist!\n");
				exit(1);
			}
			trkreliso10pt0p6_isLoaded = true;
		}
		return trkreliso10pt0p6_;
	}
	float &trkpt10pt0p7()
	{
		if (not trkpt10pt0p7_isLoaded) {
			if (trkpt10pt0p7_branch != 0) {
				trkpt10pt0p7_branch->GetEntry(index);
			} else { 
				printf("branch trkpt10pt0p7_branch does not exist!\n");
				exit(1);
			}
			trkpt10pt0p7_isLoaded = true;
		}
		return trkpt10pt0p7_;
	}
	float &trkreliso10pt0p7()
	{
		if (not trkreliso10pt0p7_isLoaded) {
			if (trkreliso10pt0p7_branch != 0) {
				trkreliso10pt0p7_branch->GetEntry(index);
			} else { 
				printf("branch trkreliso10pt0p7_branch does not exist!\n");
				exit(1);
			}
			trkreliso10pt0p7_isLoaded = true;
		}
		return trkreliso10pt0p7_;
	}
	float &trkpt10pt0p8()
	{
		if (not trkpt10pt0p8_isLoaded) {
			if (trkpt10pt0p8_branch != 0) {
				trkpt10pt0p8_branch->GetEntry(index);
			} else { 
				printf("branch trkpt10pt0p8_branch does not exist!\n");
				exit(1);
			}
			trkpt10pt0p8_isLoaded = true;
		}
		return trkpt10pt0p8_;
	}
	float &trkreliso10pt0p8()
	{
		if (not trkreliso10pt0p8_isLoaded) {
			if (trkreliso10pt0p8_branch != 0) {
				trkreliso10pt0p8_branch->GetEntry(index);
			} else { 
				printf("branch trkreliso10pt0p8_branch does not exist!\n");
				exit(1);
			}
			trkreliso10pt0p8_isLoaded = true;
		}
		return trkreliso10pt0p8_;
	}
	float &trkpt10pt0p9()
	{
		if (not trkpt10pt0p9_isLoaded) {
			if (trkpt10pt0p9_branch != 0) {
				trkpt10pt0p9_branch->GetEntry(index);
			} else { 
				printf("branch trkpt10pt0p9_branch does not exist!\n");
				exit(1);
			}
			trkpt10pt0p9_isLoaded = true;
		}
		return trkpt10pt0p9_;
	}
	float &trkreliso10pt0p9()
	{
		if (not trkreliso10pt0p9_isLoaded) {
			if (trkreliso10pt0p9_branch != 0) {
				trkreliso10pt0p9_branch->GetEntry(index);
			} else { 
				printf("branch trkreliso10pt0p9_branch does not exist!\n");
				exit(1);
			}
			trkreliso10pt0p9_isLoaded = true;
		}
		return trkreliso10pt0p9_;
	}
	float &trkpt10pt1p0()
	{
		if (not trkpt10pt1p0_isLoaded) {
			if (trkpt10pt1p0_branch != 0) {
				trkpt10pt1p0_branch->GetEntry(index);
			} else { 
				printf("branch trkpt10pt1p0_branch does not exist!\n");
				exit(1);
			}
			trkpt10pt1p0_isLoaded = true;
		}
		return trkpt10pt1p0_;
	}
	float &trkreliso10pt1p0()
	{
		if (not trkreliso10pt1p0_isLoaded) {
			if (trkreliso10pt1p0_branch != 0) {
				trkreliso10pt1p0_branch->GetEntry(index);
			} else { 
				printf("branch trkreliso10pt1p0_branch does not exist!\n");
				exit(1);
			}
			trkreliso10pt1p0_isLoaded = true;
		}
		return trkreliso10pt1p0_;
	}
	float &pfcandiso5()
	{
		if (not pfcandiso5_isLoaded) {
			if (pfcandiso5_branch != 0) {
				pfcandiso5_branch->GetEntry(index);
			} else { 
				printf("branch pfcandiso5_branch does not exist!\n");
				exit(1);
			}
			pfcandiso5_isLoaded = true;
		}
		return pfcandiso5_;
	}
	float &pfcandiso10()
	{
		if (not pfcandiso10_isLoaded) {
			if (pfcandiso10_branch != 0) {
				pfcandiso10_branch->GetEntry(index);
			} else { 
				printf("branch pfcandiso10_branch does not exist!\n");
				exit(1);
			}
			pfcandiso10_isLoaded = true;
		}
		return pfcandiso10_;
	}
	float &pfcanddiriso10()
	{
		if (not pfcanddiriso10_isLoaded) {
			if (pfcanddiriso10_branch != 0) {
				pfcanddiriso10_branch->GetEntry(index);
			} else { 
				printf("branch pfcanddiriso10_branch does not exist!\n");
				exit(1);
			}
			pfcanddiriso10_isLoaded = true;
		}
		return pfcanddiriso10_;
	}
	float &pfcandvetoiso10()
	{
		if (not pfcandvetoiso10_isLoaded) {
			if (pfcandvetoiso10_branch != 0) {
				pfcandvetoiso10_branch->GetEntry(index);
			} else { 
				printf("branch pfcandvetoiso10_branch does not exist!\n");
				exit(1);
			}
			pfcandvetoiso10_isLoaded = true;
		}
		return pfcandvetoiso10_;
	}
	float &pfcandvetoLiso10()
	{
		if (not pfcandvetoLiso10_isLoaded) {
			if (pfcandvetoLiso10_branch != 0) {
				pfcandvetoLiso10_branch->GetEntry(index);
			} else { 
				printf("branch pfcandvetoLiso10_branch does not exist!\n");
				exit(1);
			}
			pfcandvetoLiso10_isLoaded = true;
		}
		return pfcandvetoLiso10_;
	}
	float &pfcandisoOS10()
	{
		if (not pfcandisoOS10_isLoaded) {
			if (pfcandisoOS10_branch != 0) {
				pfcandisoOS10_branch->GetEntry(index);
			} else { 
				printf("branch pfcandisoOS10_branch does not exist!\n");
				exit(1);
			}
			pfcandisoOS10_isLoaded = true;
		}
		return pfcandisoOS10_;
	}
	float &pfcandisoOS10looseZ()
	{
		if (not pfcandisoOS10looseZ_isLoaded) {
			if (pfcandisoOS10looseZ_branch != 0) {
				pfcandisoOS10looseZ_branch->GetEntry(index);
			} else { 
				printf("branch pfcandisoOS10looseZ_branch does not exist!\n");
				exit(1);
			}
			pfcandisoOS10looseZ_isLoaded = true;
		}
		return pfcandisoOS10looseZ_;
	}
	float &pfcandiso5looseZ()
	{
		if (not pfcandiso5looseZ_isLoaded) {
			if (pfcandiso5looseZ_branch != 0) {
				pfcandiso5looseZ_branch->GetEntry(index);
			} else { 
				printf("branch pfcandiso5looseZ_branch does not exist!\n");
				exit(1);
			}
			pfcandiso5looseZ_isLoaded = true;
		}
		return pfcandiso5looseZ_;
	}
	float &pfcandpt5()
	{
		if (not pfcandpt5_isLoaded) {
			if (pfcandpt5_branch != 0) {
				pfcandpt5_branch->GetEntry(index);
			} else { 
				printf("branch pfcandpt5_branch does not exist!\n");
				exit(1);
			}
			pfcandpt5_isLoaded = true;
		}
		return pfcandpt5_;
	}
	float &pfcandpt10()
	{
		if (not pfcandpt10_isLoaded) {
			if (pfcandpt10_branch != 0) {
				pfcandpt10_branch->GetEntry(index);
			} else { 
				printf("branch pfcandpt10_branch does not exist!\n");
				exit(1);
			}
			pfcandpt10_isLoaded = true;
		}
		return pfcandpt10_;
	}
	float &pfcanddirpt10()
	{
		if (not pfcanddirpt10_isLoaded) {
			if (pfcanddirpt10_branch != 0) {
				pfcanddirpt10_branch->GetEntry(index);
			} else { 
				printf("branch pfcanddirpt10_branch does not exist!\n");
				exit(1);
			}
			pfcanddirpt10_isLoaded = true;
		}
		return pfcanddirpt10_;
	}
	float &pfcandvetopt10()
	{
		if (not pfcandvetopt10_isLoaded) {
			if (pfcandvetopt10_branch != 0) {
				pfcandvetopt10_branch->GetEntry(index);
			} else { 
				printf("branch pfcandvetopt10_branch does not exist!\n");
				exit(1);
			}
			pfcandvetopt10_isLoaded = true;
		}
		return pfcandvetopt10_;
	}
	float &pfcandvetoLpt10()
	{
		if (not pfcandvetoLpt10_isLoaded) {
			if (pfcandvetoLpt10_branch != 0) {
				pfcandvetoLpt10_branch->GetEntry(index);
			} else { 
				printf("branch pfcandvetoLpt10_branch does not exist!\n");
				exit(1);
			}
			pfcandvetoLpt10_isLoaded = true;
		}
		return pfcandvetoLpt10_;
	}
	float &pfcandptOS10()
	{
		if (not pfcandptOS10_isLoaded) {
			if (pfcandptOS10_branch != 0) {
				pfcandptOS10_branch->GetEntry(index);
			} else { 
				printf("branch pfcandptOS10_branch does not exist!\n");
				exit(1);
			}
			pfcandptOS10_isLoaded = true;
		}
		return pfcandptOS10_;
	}
	float &pfcandptOS10looseZ()
	{
		if (not pfcandptOS10looseZ_isLoaded) {
			if (pfcandptOS10looseZ_branch != 0) {
				pfcandptOS10looseZ_branch->GetEntry(index);
			} else { 
				printf("branch pfcandptOS10looseZ_branch does not exist!\n");
				exit(1);
			}
			pfcandptOS10looseZ_isLoaded = true;
		}
		return pfcandptOS10looseZ_;
	}
	float &pfcandpt5looseZ()
	{
		if (not pfcandpt5looseZ_isLoaded) {
			if (pfcandpt5looseZ_branch != 0) {
				pfcandpt5looseZ_branch->GetEntry(index);
			} else { 
				printf("branch pfcandpt5looseZ_branch does not exist!\n");
				exit(1);
			}
			pfcandpt5looseZ_isLoaded = true;
		}
		return pfcandpt5looseZ_;
	}
	float &pfcanddz5()
	{
		if (not pfcanddz5_isLoaded) {
			if (pfcanddz5_branch != 0) {
				pfcanddz5_branch->GetEntry(index);
			} else { 
				printf("branch pfcanddz5_branch does not exist!\n");
				exit(1);
			}
			pfcanddz5_isLoaded = true;
		}
		return pfcanddz5_;
	}
	float &pfcanddz10()
	{
		if (not pfcanddz10_isLoaded) {
			if (pfcanddz10_branch != 0) {
				pfcanddz10_branch->GetEntry(index);
			} else { 
				printf("branch pfcanddz10_branch does not exist!\n");
				exit(1);
			}
			pfcanddz10_isLoaded = true;
		}
		return pfcanddz10_;
	}
	float &pfcanddirdz10()
	{
		if (not pfcanddirdz10_isLoaded) {
			if (pfcanddirdz10_branch != 0) {
				pfcanddirdz10_branch->GetEntry(index);
			} else { 
				printf("branch pfcanddirdz10_branch does not exist!\n");
				exit(1);
			}
			pfcanddirdz10_isLoaded = true;
		}
		return pfcanddirdz10_;
	}
	float &pfcandvetodz10()
	{
		if (not pfcandvetodz10_isLoaded) {
			if (pfcandvetodz10_branch != 0) {
				pfcandvetodz10_branch->GetEntry(index);
			} else { 
				printf("branch pfcandvetodz10_branch does not exist!\n");
				exit(1);
			}
			pfcandvetodz10_isLoaded = true;
		}
		return pfcandvetodz10_;
	}
	float &pfcandvetoLdz10()
	{
		if (not pfcandvetoLdz10_isLoaded) {
			if (pfcandvetoLdz10_branch != 0) {
				pfcandvetoLdz10_branch->GetEntry(index);
			} else { 
				printf("branch pfcandvetoLdz10_branch does not exist!\n");
				exit(1);
			}
			pfcandvetoLdz10_isLoaded = true;
		}
		return pfcandvetoLdz10_;
	}
	float &pfcanddzOS10()
	{
		if (not pfcanddzOS10_isLoaded) {
			if (pfcanddzOS10_branch != 0) {
				pfcanddzOS10_branch->GetEntry(index);
			} else { 
				printf("branch pfcanddzOS10_branch does not exist!\n");
				exit(1);
			}
			pfcanddzOS10_isLoaded = true;
		}
		return pfcanddzOS10_;
	}
	float &pfcanddzOS10looseZ()
	{
		if (not pfcanddzOS10looseZ_isLoaded) {
			if (pfcanddzOS10looseZ_branch != 0) {
				pfcanddzOS10looseZ_branch->GetEntry(index);
			} else { 
				printf("branch pfcanddzOS10looseZ_branch does not exist!\n");
				exit(1);
			}
			pfcanddzOS10looseZ_isLoaded = true;
		}
		return pfcanddzOS10looseZ_;
	}
	float &pfcanddz5looseZ()
	{
		if (not pfcanddz5looseZ_isLoaded) {
			if (pfcanddz5looseZ_branch != 0) {
				pfcanddz5looseZ_branch->GetEntry(index);
			} else { 
				printf("branch pfcanddz5looseZ_branch does not exist!\n");
				exit(1);
			}
			pfcanddz5looseZ_isLoaded = true;
		}
		return pfcanddz5looseZ_;
	}
	float &pfcandmindrj5()
	{
		if (not pfcandmindrj5_isLoaded) {
			if (pfcandmindrj5_branch != 0) {
				pfcandmindrj5_branch->GetEntry(index);
			} else { 
				printf("branch pfcandmindrj5_branch does not exist!\n");
				exit(1);
			}
			pfcandmindrj5_isLoaded = true;
		}
		return pfcandmindrj5_;
	}
	float &pfcandmindrj10()
	{
		if (not pfcandmindrj10_isLoaded) {
			if (pfcandmindrj10_branch != 0) {
				pfcandmindrj10_branch->GetEntry(index);
			} else { 
				printf("branch pfcandmindrj10_branch does not exist!\n");
				exit(1);
			}
			pfcandmindrj10_isLoaded = true;
		}
		return pfcandmindrj10_;
	}
	float &pfcanddirmindrj10()
	{
		if (not pfcanddirmindrj10_isLoaded) {
			if (pfcanddirmindrj10_branch != 0) {
				pfcanddirmindrj10_branch->GetEntry(index);
			} else { 
				printf("branch pfcanddirmindrj10_branch does not exist!\n");
				exit(1);
			}
			pfcanddirmindrj10_isLoaded = true;
		}
		return pfcanddirmindrj10_;
	}
	float &pfcandvetomindrj10()
	{
		if (not pfcandvetomindrj10_isLoaded) {
			if (pfcandvetomindrj10_branch != 0) {
				pfcandvetomindrj10_branch->GetEntry(index);
			} else { 
				printf("branch pfcandvetomindrj10_branch does not exist!\n");
				exit(1);
			}
			pfcandvetomindrj10_isLoaded = true;
		}
		return pfcandvetomindrj10_;
	}
	float &pfcandvetoLmindrj10()
	{
		if (not pfcandvetoLmindrj10_isLoaded) {
			if (pfcandvetoLmindrj10_branch != 0) {
				pfcandvetoLmindrj10_branch->GetEntry(index);
			} else { 
				printf("branch pfcandvetoLmindrj10_branch does not exist!\n");
				exit(1);
			}
			pfcandvetoLmindrj10_isLoaded = true;
		}
		return pfcandvetoLmindrj10_;
	}
	float &pfcandpt10pt0p1()
	{
		if (not pfcandpt10pt0p1_isLoaded) {
			if (pfcandpt10pt0p1_branch != 0) {
				pfcandpt10pt0p1_branch->GetEntry(index);
			} else { 
				printf("branch pfcandpt10pt0p1_branch does not exist!\n");
				exit(1);
			}
			pfcandpt10pt0p1_isLoaded = true;
		}
		return pfcandpt10pt0p1_;
	}
	float &pfcandiso10pt0p1()
	{
		if (not pfcandiso10pt0p1_isLoaded) {
			if (pfcandiso10pt0p1_branch != 0) {
				pfcandiso10pt0p1_branch->GetEntry(index);
			} else { 
				printf("branch pfcandiso10pt0p1_branch does not exist!\n");
				exit(1);
			}
			pfcandiso10pt0p1_isLoaded = true;
		}
		return pfcandiso10pt0p1_;
	}
	float &pfcandpt10pt0p2()
	{
		if (not pfcandpt10pt0p2_isLoaded) {
			if (pfcandpt10pt0p2_branch != 0) {
				pfcandpt10pt0p2_branch->GetEntry(index);
			} else { 
				printf("branch pfcandpt10pt0p2_branch does not exist!\n");
				exit(1);
			}
			pfcandpt10pt0p2_isLoaded = true;
		}
		return pfcandpt10pt0p2_;
	}
	float &pfcandiso10pt0p2()
	{
		if (not pfcandiso10pt0p2_isLoaded) {
			if (pfcandiso10pt0p2_branch != 0) {
				pfcandiso10pt0p2_branch->GetEntry(index);
			} else { 
				printf("branch pfcandiso10pt0p2_branch does not exist!\n");
				exit(1);
			}
			pfcandiso10pt0p2_isLoaded = true;
		}
		return pfcandiso10pt0p2_;
	}
	float &pfcandpt10pt0p3()
	{
		if (not pfcandpt10pt0p3_isLoaded) {
			if (pfcandpt10pt0p3_branch != 0) {
				pfcandpt10pt0p3_branch->GetEntry(index);
			} else { 
				printf("branch pfcandpt10pt0p3_branch does not exist!\n");
				exit(1);
			}
			pfcandpt10pt0p3_isLoaded = true;
		}
		return pfcandpt10pt0p3_;
	}
	float &pfcandiso10pt0p3()
	{
		if (not pfcandiso10pt0p3_isLoaded) {
			if (pfcandiso10pt0p3_branch != 0) {
				pfcandiso10pt0p3_branch->GetEntry(index);
			} else { 
				printf("branch pfcandiso10pt0p3_branch does not exist!\n");
				exit(1);
			}
			pfcandiso10pt0p3_isLoaded = true;
		}
		return pfcandiso10pt0p3_;
	}
	float &pfcandpt10pt0p4()
	{
		if (not pfcandpt10pt0p4_isLoaded) {
			if (pfcandpt10pt0p4_branch != 0) {
				pfcandpt10pt0p4_branch->GetEntry(index);
			} else { 
				printf("branch pfcandpt10pt0p4_branch does not exist!\n");
				exit(1);
			}
			pfcandpt10pt0p4_isLoaded = true;
		}
		return pfcandpt10pt0p4_;
	}
	float &pfcandiso10pt0p4()
	{
		if (not pfcandiso10pt0p4_isLoaded) {
			if (pfcandiso10pt0p4_branch != 0) {
				pfcandiso10pt0p4_branch->GetEntry(index);
			} else { 
				printf("branch pfcandiso10pt0p4_branch does not exist!\n");
				exit(1);
			}
			pfcandiso10pt0p4_isLoaded = true;
		}
		return pfcandiso10pt0p4_;
	}
	float &pfcandpt10pt0p5()
	{
		if (not pfcandpt10pt0p5_isLoaded) {
			if (pfcandpt10pt0p5_branch != 0) {
				pfcandpt10pt0p5_branch->GetEntry(index);
			} else { 
				printf("branch pfcandpt10pt0p5_branch does not exist!\n");
				exit(1);
			}
			pfcandpt10pt0p5_isLoaded = true;
		}
		return pfcandpt10pt0p5_;
	}
	float &pfcandiso10pt0p5()
	{
		if (not pfcandiso10pt0p5_isLoaded) {
			if (pfcandiso10pt0p5_branch != 0) {
				pfcandiso10pt0p5_branch->GetEntry(index);
			} else { 
				printf("branch pfcandiso10pt0p5_branch does not exist!\n");
				exit(1);
			}
			pfcandiso10pt0p5_isLoaded = true;
		}
		return pfcandiso10pt0p5_;
	}
	float &pfcandpt10pt0p6()
	{
		if (not pfcandpt10pt0p6_isLoaded) {
			if (pfcandpt10pt0p6_branch != 0) {
				pfcandpt10pt0p6_branch->GetEntry(index);
			} else { 
				printf("branch pfcandpt10pt0p6_branch does not exist!\n");
				exit(1);
			}
			pfcandpt10pt0p6_isLoaded = true;
		}
		return pfcandpt10pt0p6_;
	}
	float &pfcandiso10pt0p6()
	{
		if (not pfcandiso10pt0p6_isLoaded) {
			if (pfcandiso10pt0p6_branch != 0) {
				pfcandiso10pt0p6_branch->GetEntry(index);
			} else { 
				printf("branch pfcandiso10pt0p6_branch does not exist!\n");
				exit(1);
			}
			pfcandiso10pt0p6_isLoaded = true;
		}
		return pfcandiso10pt0p6_;
	}
	float &pfcandpt10pt0p7()
	{
		if (not pfcandpt10pt0p7_isLoaded) {
			if (pfcandpt10pt0p7_branch != 0) {
				pfcandpt10pt0p7_branch->GetEntry(index);
			} else { 
				printf("branch pfcandpt10pt0p7_branch does not exist!\n");
				exit(1);
			}
			pfcandpt10pt0p7_isLoaded = true;
		}
		return pfcandpt10pt0p7_;
	}
	float &pfcandiso10pt0p7()
	{
		if (not pfcandiso10pt0p7_isLoaded) {
			if (pfcandiso10pt0p7_branch != 0) {
				pfcandiso10pt0p7_branch->GetEntry(index);
			} else { 
				printf("branch pfcandiso10pt0p7_branch does not exist!\n");
				exit(1);
			}
			pfcandiso10pt0p7_isLoaded = true;
		}
		return pfcandiso10pt0p7_;
	}
	float &pfcandpt10pt0p8()
	{
		if (not pfcandpt10pt0p8_isLoaded) {
			if (pfcandpt10pt0p8_branch != 0) {
				pfcandpt10pt0p8_branch->GetEntry(index);
			} else { 
				printf("branch pfcandpt10pt0p8_branch does not exist!\n");
				exit(1);
			}
			pfcandpt10pt0p8_isLoaded = true;
		}
		return pfcandpt10pt0p8_;
	}
	float &pfcandiso10pt0p8()
	{
		if (not pfcandiso10pt0p8_isLoaded) {
			if (pfcandiso10pt0p8_branch != 0) {
				pfcandiso10pt0p8_branch->GetEntry(index);
			} else { 
				printf("branch pfcandiso10pt0p8_branch does not exist!\n");
				exit(1);
			}
			pfcandiso10pt0p8_isLoaded = true;
		}
		return pfcandiso10pt0p8_;
	}
	float &pfcandpt10pt0p9()
	{
		if (not pfcandpt10pt0p9_isLoaded) {
			if (pfcandpt10pt0p9_branch != 0) {
				pfcandpt10pt0p9_branch->GetEntry(index);
			} else { 
				printf("branch pfcandpt10pt0p9_branch does not exist!\n");
				exit(1);
			}
			pfcandpt10pt0p9_isLoaded = true;
		}
		return pfcandpt10pt0p9_;
	}
	float &pfcandiso10pt0p9()
	{
		if (not pfcandiso10pt0p9_isLoaded) {
			if (pfcandiso10pt0p9_branch != 0) {
				pfcandiso10pt0p9_branch->GetEntry(index);
			} else { 
				printf("branch pfcandiso10pt0p9_branch does not exist!\n");
				exit(1);
			}
			pfcandiso10pt0p9_isLoaded = true;
		}
		return pfcandiso10pt0p9_;
	}
	float &pfcandpt10pt1p0()
	{
		if (not pfcandpt10pt1p0_isLoaded) {
			if (pfcandpt10pt1p0_branch != 0) {
				pfcandpt10pt1p0_branch->GetEntry(index);
			} else { 
				printf("branch pfcandpt10pt1p0_branch does not exist!\n");
				exit(1);
			}
			pfcandpt10pt1p0_isLoaded = true;
		}
		return pfcandpt10pt1p0_;
	}
	float &pfcandiso10pt1p0()
	{
		if (not pfcandiso10pt1p0_isLoaded) {
			if (pfcandiso10pt1p0_branch != 0) {
				pfcandiso10pt1p0_branch->GetEntry(index);
			} else { 
				printf("branch pfcandiso10pt1p0_branch does not exist!\n");
				exit(1);
			}
			pfcandiso10pt1p0_isLoaded = true;
		}
		return pfcandiso10pt1p0_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcand5()
	{
		if (not pfcand5_isLoaded) {
			if (pfcand5_branch != 0) {
				pfcand5_branch->GetEntry(index);
			} else { 
				printf("branch pfcand5_branch does not exist!\n");
				exit(1);
			}
			pfcand5_isLoaded = true;
		}
		return *pfcand5_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcand10()
	{
		if (not pfcand10_isLoaded) {
			if (pfcand10_branch != 0) {
				pfcand10_branch->GetEntry(index);
			} else { 
				printf("branch pfcand10_branch does not exist!\n");
				exit(1);
			}
			pfcand10_isLoaded = true;
		}
		return *pfcand10_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcanddir10()
	{
		if (not pfcanddir10_isLoaded) {
			if (pfcanddir10_branch != 0) {
				pfcanddir10_branch->GetEntry(index);
			} else { 
				printf("branch pfcanddir10_branch does not exist!\n");
				exit(1);
			}
			pfcanddir10_isLoaded = true;
		}
		return *pfcanddir10_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcandveto10()
	{
		if (not pfcandveto10_isLoaded) {
			if (pfcandveto10_branch != 0) {
				pfcandveto10_branch->GetEntry(index);
			} else { 
				printf("branch pfcandveto10_branch does not exist!\n");
				exit(1);
			}
			pfcandveto10_isLoaded = true;
		}
		return *pfcandveto10_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcandvetoL10()
	{
		if (not pfcandvetoL10_isLoaded) {
			if (pfcandvetoL10_branch != 0) {
				pfcandvetoL10_branch->GetEntry(index);
			} else { 
				printf("branch pfcandvetoL10_branch does not exist!\n");
				exit(1);
			}
			pfcandvetoL10_isLoaded = true;
		}
		return *pfcandvetoL10_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcandOS10()
	{
		if (not pfcandOS10_isLoaded) {
			if (pfcandOS10_branch != 0) {
				pfcandOS10_branch->GetEntry(index);
			} else { 
				printf("branch pfcandOS10_branch does not exist!\n");
				exit(1);
			}
			pfcandOS10_isLoaded = true;
		}
		return *pfcandOS10_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcandOS10looseZ()
	{
		if (not pfcandOS10looseZ_isLoaded) {
			if (pfcandOS10looseZ_branch != 0) {
				pfcandOS10looseZ_branch->GetEntry(index);
			} else { 
				printf("branch pfcandOS10looseZ_branch does not exist!\n");
				exit(1);
			}
			pfcandOS10looseZ_isLoaded = true;
		}
		return *pfcandOS10looseZ_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcand5looseZ()
	{
		if (not pfcand5looseZ_isLoaded) {
			if (pfcand5looseZ_branch != 0) {
				pfcand5looseZ_branch->GetEntry(index);
			} else { 
				printf("branch pfcand5looseZ_branch does not exist!\n");
				exit(1);
			}
			pfcand5looseZ_isLoaded = true;
		}
		return *pfcand5looseZ_;
	}
	int &pfTau15_leadPtcandID()
	{
		if (not pfTau15_leadPtcandID_isLoaded) {
			if (pfTau15_leadPtcandID_branch != 0) {
				pfTau15_leadPtcandID_branch->GetEntry(index);
			} else { 
				printf("branch pfTau15_leadPtcandID_branch does not exist!\n");
				exit(1);
			}
			pfTau15_leadPtcandID_isLoaded = true;
		}
		return pfTau15_leadPtcandID_;
	}
	int &pfTau_leadPtcandID()
	{
		if (not pfTau_leadPtcandID_isLoaded) {
			if (pfTau_leadPtcandID_branch != 0) {
				pfTau_leadPtcandID_branch->GetEntry(index);
			} else { 
				printf("branch pfTau_leadPtcandID_branch does not exist!\n");
				exit(1);
			}
			pfTau_leadPtcandID_isLoaded = true;
		}
		return pfTau_leadPtcandID_;
	}
	int &pfTauLoose_leadPtcandID()
	{
		if (not pfTauLoose_leadPtcandID_isLoaded) {
			if (pfTauLoose_leadPtcandID_branch != 0) {
				pfTauLoose_leadPtcandID_branch->GetEntry(index);
			} else { 
				printf("branch pfTauLoose_leadPtcandID_branch does not exist!\n");
				exit(1);
			}
			pfTauLoose_leadPtcandID_isLoaded = true;
		}
		return pfTauLoose_leadPtcandID_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTau15()
	{
		if (not pfTau15_isLoaded) {
			if (pfTau15_branch != 0) {
				pfTau15_branch->GetEntry(index);
			} else { 
				printf("branch pfTau15_branch does not exist!\n");
				exit(1);
			}
			pfTau15_isLoaded = true;
		}
		return *pfTau15_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTau15_leadPtcand()
	{
		if (not pfTau15_leadPtcand_isLoaded) {
			if (pfTau15_leadPtcand_branch != 0) {
				pfTau15_leadPtcand_branch->GetEntry(index);
			} else { 
				printf("branch pfTau15_leadPtcand_branch does not exist!\n");
				exit(1);
			}
			pfTau15_leadPtcand_isLoaded = true;
		}
		return *pfTau15_leadPtcand_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTau()
	{
		if (not pfTau_isLoaded) {
			if (pfTau_branch != 0) {
				pfTau_branch->GetEntry(index);
			} else { 
				printf("branch pfTau_branch does not exist!\n");
				exit(1);
			}
			pfTau_isLoaded = true;
		}
		return *pfTau_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTau_leadPtcand()
	{
		if (not pfTau_leadPtcand_isLoaded) {
			if (pfTau_leadPtcand_branch != 0) {
				pfTau_leadPtcand_branch->GetEntry(index);
			} else { 
				printf("branch pfTau_leadPtcand_branch does not exist!\n");
				exit(1);
			}
			pfTau_leadPtcand_isLoaded = true;
		}
		return *pfTau_leadPtcand_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTauLoose()
	{
		if (not pfTauLoose_isLoaded) {
			if (pfTauLoose_branch != 0) {
				pfTauLoose_branch->GetEntry(index);
			} else { 
				printf("branch pfTauLoose_branch does not exist!\n");
				exit(1);
			}
			pfTauLoose_isLoaded = true;
		}
		return *pfTauLoose_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTauLoose_leadPtcand()
	{
		if (not pfTauLoose_leadPtcand_isLoaded) {
			if (pfTauLoose_leadPtcand_branch != 0) {
				pfTauLoose_leadPtcand_branch->GetEntry(index);
			} else { 
				printf("branch pfTauLoose_leadPtcand_branch does not exist!\n");
				exit(1);
			}
			pfTauLoose_leadPtcand_isLoaded = true;
		}
		return *pfTauLoose_leadPtcand_;
	}
	const vector<float> &pfjets_beta()
	{
		if (not pfjets_beta_isLoaded) {
			if (pfjets_beta_branch != 0) {
				pfjets_beta_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_beta_branch does not exist!\n");
				exit(1);
			}
			pfjets_beta_isLoaded = true;
		}
		return *pfjets_beta_;
	}
	const vector<float> &pfjets_beta2()
	{
		if (not pfjets_beta2_isLoaded) {
			if (pfjets_beta2_branch != 0) {
				pfjets_beta2_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_beta2_branch does not exist!\n");
				exit(1);
			}
			pfjets_beta2_isLoaded = true;
		}
		return *pfjets_beta2_;
	}
	const vector<float> &pfjets_beta_0p1()
	{
		if (not pfjets_beta_0p1_isLoaded) {
			if (pfjets_beta_0p1_branch != 0) {
				pfjets_beta_0p1_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_beta_0p1_branch does not exist!\n");
				exit(1);
			}
			pfjets_beta_0p1_isLoaded = true;
		}
		return *pfjets_beta_0p1_;
	}
	const vector<float> &pfjets_beta_0p2()
	{
		if (not pfjets_beta_0p2_isLoaded) {
			if (pfjets_beta_0p2_branch != 0) {
				pfjets_beta_0p2_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_beta_0p2_branch does not exist!\n");
				exit(1);
			}
			pfjets_beta_0p2_isLoaded = true;
		}
		return *pfjets_beta_0p2_;
	}
	const vector<float> &pfjets_beta2_0p1()
	{
		if (not pfjets_beta2_0p1_isLoaded) {
			if (pfjets_beta2_0p1_branch != 0) {
				pfjets_beta2_0p1_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_beta2_0p1_branch does not exist!\n");
				exit(1);
			}
			pfjets_beta2_0p1_isLoaded = true;
		}
		return *pfjets_beta2_0p1_;
	}
	const vector<float> &pfjets_beta2_0p5()
	{
		if (not pfjets_beta2_0p5_isLoaded) {
			if (pfjets_beta2_0p5_branch != 0) {
				pfjets_beta2_0p5_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_beta2_0p5_branch does not exist!\n");
				exit(1);
			}
			pfjets_beta2_0p5_isLoaded = true;
		}
		return *pfjets_beta2_0p5_;
	}
	const vector<float> &pfjets_mvaPUid()
	{
		if (not pfjets_mvaPUid_isLoaded) {
			if (pfjets_mvaPUid_branch != 0) {
				pfjets_mvaPUid_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_mvaPUid_branch does not exist!\n");
				exit(1);
			}
			pfjets_mvaPUid_isLoaded = true;
		}
		return *pfjets_mvaPUid_;
	}
	const vector<float> &pfjets_mva5xPUid()
	{
		if (not pfjets_mva5xPUid_isLoaded) {
			if (pfjets_mva5xPUid_branch != 0) {
				pfjets_mva5xPUid_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_mva5xPUid_branch does not exist!\n");
				exit(1);
			}
			pfjets_mva5xPUid_isLoaded = true;
		}
		return *pfjets_mva5xPUid_;
	}
	const vector<float> &pfjets_mvaBeta()
	{
		if (not pfjets_mvaBeta_isLoaded) {
			if (pfjets_mvaBeta_branch != 0) {
				pfjets_mvaBeta_branch->GetEntry(index);
			} else { 
				printf("branch pfjets_mvaBeta_branch does not exist!\n");
				exit(1);
			}
			pfjets_mvaBeta_isLoaded = true;
		}
		return *pfjets_mvaBeta_;
	}
	bool &	passes_isotrk_veto()
	{
		if (not passes_isotrk_veto_isLoaded) {
			if (passes_isotrk_veto_branch != 0) {
				passes_isotrk_veto_branch->GetEntry(index);
			} else { 
				printf("branch passes_isotrk_veto_branch does not exist!\n");
				exit(1);
			}
			passes_isotrk_veto_isLoaded = true;
		}
		return passes_isotrk_veto_;
	}
	bool &	passes_tau_veto()
	{
		if (not passes_tau_veto_isLoaded) {
			if (passes_tau_veto_branch != 0) {
				passes_tau_veto_branch->GetEntry(index);
			} else { 
				printf("branch passes_tau_veto_branch does not exist!\n");
				exit(1);
			}
			passes_tau_veto_isLoaded = true;
		}
		return passes_tau_veto_;
	}
	int &njets_pv_tight0()
	{
		if (not njets_pv_tight0_isLoaded) {
			if (njets_pv_tight0_branch != 0) {
				njets_pv_tight0_branch->GetEntry(index);
			} else { 
				printf("branch njets_pv_tight0_branch does not exist!\n");
				exit(1);
			}
			njets_pv_tight0_isLoaded = true;
		}
		return njets_pv_tight0_;
	}
	int &njets_pv_tight1()
	{
		if (not njets_pv_tight1_isLoaded) {
			if (njets_pv_tight1_branch != 0) {
				njets_pv_tight1_branch->GetEntry(index);
			} else { 
				printf("branch njets_pv_tight1_branch does not exist!\n");
				exit(1);
			}
			njets_pv_tight1_isLoaded = true;
		}
		return njets_pv_tight1_;
	}
	int &njets_pv_tight2()
	{
		if (not njets_pv_tight2_isLoaded) {
			if (njets_pv_tight2_branch != 0) {
				njets_pv_tight2_branch->GetEntry(index);
			} else { 
				printf("branch njets_pv_tight2_branch does not exist!\n");
				exit(1);
			}
			njets_pv_tight2_isLoaded = true;
		}
		return njets_pv_tight2_;
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
extern EWKINO2012_SS ewk12ss;
#endif

namespace ewkino_ss {
	const unsigned int &run();
	const unsigned int &ls();
	const unsigned int &evt();
	const bool &is_real_data();
	const int &sample();
	const int &nvtxs();
	const int &vtx_idx();
	const float &pfmet();
	const float &pfmet_phi();
	const float &uncorpfmet();
	const float &uncorpfmet_phi();
	const float &pu_nvtxs();
	const float &pu_ntrueint();
	const float &scale1fb();
	const float &xsec();
	const unsigned int &nevts();
	const float &kfactor();
	const float &gen_met();
	const float &gen_met_phi();
	const TString &dataset();
	const TString &filename();
	const bool &filt_csc();
	const bool &filt_hbhe();
	const bool &filt_hcallaser();
	const bool &filt_ecallaser();
	const bool &filt_ecaltp();
	const bool &filt_trkfail();
	const bool &filt_eebadsc();
	const bool &passes_metfilters();
	const bool &lep1_passes_id();
	const bool &lep1_passes_iso();
	const bool &lep1_is_num();
	const bool &lep1_is_den();
	const bool &lep1_is_fo();
	const int &lep1_is_fromw();
	const int &lep1_charge();
	const int &lep1_pdgid();
	const int &lep1_type();
	const float &lep1_d0();
	const float &lep1_d0err();
	const float &lep1_dz();
	const float &lep1_ip3d();
	const float &lep1_ip3derr();
	const float &lep1_dzerr();
	const float &lep1_mt();
	const float &lep1_corpfiso();
	const float &lep1_pfiso();
	const float &lep1_chiso();
	const float &lep1_emiso();
	const float &lep1_nhiso();
	const float &lep1_corpfiso04();
	const float &lep1_pfiso04();
	const float &lep1_chiso04();
	const float &lep1_emiso04();
	const float &lep1_nhiso04();
	const float &lep1_cordetiso();
	const float &lep1_detiso();
	const float &lep1_trkiso();
	const float &lep1_ecaliso();
	const float &lep1_hcaliso();
	const float &lep1_cordetiso04();
	const float &lep1_detiso04();
	const float &lep1_trkiso04();
	const float &lep1_ecaliso04();
	const float &lep1_hcaliso04();
	const float &lep1_effarea();
	const float &lep1_effarea04();
	const float &lep1_dbeta();
	const float &lep1_dbeta04();
	const float &lep1_sf_lepeff();
	const float &lep1_sf_trig();
	const int &lep1_mcid();
	const int &lep1_mc3id();
	const int &lep1_momid();
	const int &lep1_mc3_momid();
	const bool &lep1_q3agree();
	const bool &lep1_is_conv();
	const int &lep1_qsc();
	const int &lep1_qctf();
	const int &lep1_qgsf();
	const int &lep1_nmhits();
	const int &lep1_eleid_veto();
	const int &lep1_eleid_loose();
	const int &lep1_eleid_medium();
	const int &lep1_eleid_tight();
	const float &lep1_dphiin();
	const float &lep1_detain();
	const float &lep1_sieie();
	const float &lep1_hoe();
	const float &lep1_ooemoop();
	const float &lep1_conv_dist();
	const float &lep1_conv_dcot();
	const bool &lep1_is_global();
	const bool &lep1_is_tracker();
	const bool &lep1_is_stamu();
	const bool &lep1_is_pfmu();
	const bool &lep1_is_loosemu();
	const bool &lep1_is_tightmu();
	const int &lep1_npixelhits();
	const int &lep1_nsihits();
	const int &lep1_nsilayers();
	const int &lep1_nstahits();
	const int &lep1_nstations();
	const float &lep1_chi2();
	const float &lep1_ndof();
	const float &lep1_pterr();
	const float &lep1_ecal_vetodep();
	const float &lep1_hcal_vetodep();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mcp4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mc3p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mc_momp4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_gsf_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_ctf_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_sc_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_gfit_p4();
	const bool &lep2_passes_id();
	const bool &lep2_passes_iso();
	const bool &lep2_is_num();
	const bool &lep2_is_den();
	const bool &lep2_is_fo();
	const int &lep2_is_fromw();
	const int &lep2_charge();
	const int &lep2_pdgid();
	const int &lep2_type();
	const float &lep2_d0();
	const float &lep2_d0err();
	const float &lep2_dz();
	const float &lep2_ip3d();
	const float &lep2_ip3derr();
	const float &lep2_dzerr();
	const float &lep2_mt();
	const float &lep2_corpfiso();
	const float &lep2_pfiso();
	const float &lep2_chiso();
	const float &lep2_emiso();
	const float &lep2_nhiso();
	const float &lep2_corpfiso04();
	const float &lep2_pfiso04();
	const float &lep2_chiso04();
	const float &lep2_emiso04();
	const float &lep2_nhiso04();
	const float &lep2_cordetiso();
	const float &lep2_detiso();
	const float &lep2_trkiso();
	const float &lep2_ecaliso();
	const float &lep2_hcaliso();
	const float &lep2_cordetiso04();
	const float &lep2_detiso04();
	const float &lep2_trkiso04();
	const float &lep2_ecaliso04();
	const float &lep2_hcaliso04();
	const float &lep2_effarea();
	const float &lep2_effarea04();
	const float &lep2_dbeta();
	const float &lep2_dbeta04();
	const float &lep2_sf_lepeff();
	const float &lep2_sf_trig();
	const int &lep2_mcid();
	const int &lep2_mc3id();
	const int &lep2_momid();
	const int &lep2_mc3_momid();
	const bool &lep2_q3agree();
	const bool &lep2_is_conv();
	const int &lep2_qsc();
	const int &lep2_qctf();
	const int &lep2_qgsf();
	const int &lep2_nmhits();
	const int &lep2_eleid_veto();
	const int &lep2_eleid_loose();
	const int &lep2_eleid_medium();
	const int &lep2_eleid_tight();
	const float &lep2_dphiin();
	const float &lep2_detain();
	const float &lep2_sieie();
	const float &lep2_hoe();
	const float &lep2_ooemoop();
	const float &lep2_conv_dist();
	const float &lep2_conv_dcot();
	const bool &lep2_is_global();
	const bool &lep2_is_tracker();
	const bool &lep2_is_stamu();
	const bool &lep2_is_pfmu();
	const bool &lep2_is_loosemu();
	const bool &lep2_is_tightmu();
	const int &lep2_npixelhits();
	const int &lep2_nsihits();
	const int &lep2_nsilayers();
	const int &lep2_nstahits();
	const int &lep2_nstations();
	const float &lep2_chi2();
	const float &lep2_ndof();
	const float &lep2_pterr();
	const float &lep2_ecal_vetodep();
	const float &lep2_hcal_vetodep();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mcp4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mc3p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mc_momp4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_gsf_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_ctf_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_sc_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_gfit_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &dilep_p4();
	const bool &os();
	const bool &ss();
	const bool &mm();
	const bool &ee();
	const bool &em();
	const int &dilep_type();
	const int &dilep_gen_type();
	const float &dilep_mass();
	const float &dilep_dphi();
	const float &dilep_deta();
	const float &dilep_dr();
	const int &fiduciality();
	const bool &lep3_passes_id();
	const bool &lep3_passes_iso();
	const bool &lep3_is_num();
	const bool &lep3_is_den();
	const bool &lep3_is_fo();
	const int &lep3_is_fromw();
	const int &lep3_charge();
	const int &lep3_pdgid();
	const int &lep3_type();
	const float &lep3_d0();
	const float &lep3_d0err();
	const float &lep3_dz();
	const float &lep3_ip3d();
	const float &lep3_ip3derr();
	const float &lep3_dzerr();
	const float &lep3_mt();
	const float &lep3_corpfiso();
	const float &lep3_pfiso();
	const float &lep3_chiso();
	const float &lep3_emiso();
	const float &lep3_nhiso();
	const float &lep3_corpfiso04();
	const float &lep3_pfiso04();
	const float &lep3_chiso04();
	const float &lep3_emiso04();
	const float &lep3_nhiso04();
	const float &lep3_cordetiso();
	const float &lep3_detiso();
	const float &lep3_trkiso();
	const float &lep3_ecaliso();
	const float &lep3_hcaliso();
	const float &lep3_cordetiso04();
	const float &lep3_detiso04();
	const float &lep3_trkiso04();
	const float &lep3_ecaliso04();
	const float &lep3_hcaliso04();
	const float &lep3_effarea();
	const float &lep3_effarea04();
	const float &lep3_dbeta();
	const float &lep3_dbeta04();
	const float &lep3_sf_lepeff();
	const float &lep3_sf_trig();
	const int &lep3_mcid();
	const int &lep3_mc3id();
	const int &lep3_momid();
	const int &lep3_mc3_momid();
	const bool &lep3_q3agree();
	const bool &lep3_is_conv();
	const int &lep3_qsc();
	const int &lep3_qctf();
	const int &lep3_qgsf();
	const int &lep3_nmhits();
	const int &lep3_eleid_veto();
	const int &lep3_eleid_loose();
	const int &lep3_eleid_medium();
	const int &lep3_eleid_tight();
	const float &lep3_dphiin();
	const float &lep3_detain();
	const float &lep3_sieie();
	const float &lep3_hoe();
	const float &lep3_ooemoop();
	const float &lep3_conv_dist();
	const float &lep3_conv_dcot();
	const bool &lep3_is_global();
	const bool &lep3_is_tracker();
	const bool &lep3_is_stamu();
	const bool &lep3_is_pfmu();
	const bool &lep3_is_loosemu();
	const bool &lep3_is_tightmu();
	const int &lep3_npixelhits();
	const int &lep3_nsihits();
	const int &lep3_nsilayers();
	const int &lep3_nstahits();
	const int &lep3_nstations();
	const float &lep3_chi2();
	const float &lep3_ndof();
	const float &lep3_pterr();
	const float &lep3_ecal_vetodep();
	const float &lep3_hcal_vetodep();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_mcp4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_mc3p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_mc_momp4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_gsf_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_ctf_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_sc_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_gfit_p4();
	const unsigned int &selection();
	const bool &is_good_lumi();
	const bool &charge_type();
	const int &njets();
	const int &nbtags();
	const int &nbtags_loose();
	const int &ttbar_bkdn();
	const float &vtxw();
	const float &mt();
	const float &mt2();
	const float &ht();
	const float &rho();
	const float &rho_iso();
	const bool &trig_mm();
	const bool &trig_em();
	const bool &trig_ee();
	const bool &trig_mm_mu17_mu8();
	const bool &trig_ee_el17_el8_id_iso();
	const bool &trig_em_mu17_el8_id_iso();
	const bool &trig_em_mu8_el17_id_iso();
	const int &njets_dn();
	const int &njets_up();
	const int &nbtags_dn();
	const int &nbtags_up();
	const float &ht_dn();
	const float &ht_up();
	const int &nbtags_reweighted();
	const int &nbtags_reweighted_dn();
	const int &nbtags_reweighted_up();
	const int &nbtags_reweighted_jec_dn();
	const int &nbtags_reweighted_jec_up();
	const float &pfmet_dn();
	const float &pfmet_up();
	const float &pfmet_phi_dn();
	const float &pfmet_phi_up();
	const float &sf_dileptrig();
	const float &sf_lepeff();
	const float &sparm0();
	const float &sparm1();
	const float &sparm2();
	const float &sparm3();
	const TString &sparm0_name();
	const TString &sparm1_name();
	const TString &sparm2_name();
	const TString &sparm3_name();
	const bool &is_pp();
	const bool &is_mm();
	const bool &is_ss();
	const bool &is_sf();
	const bool &is_df();
	const bool &is_os();
	const bool &no_extraz();
	const bool &no_extrag();
	const bool &clean();
	const bool &presel();
	const bool &em_mufo();
	const bool &em_elfo();
	const bool &hyp_good_vtx();
	const bool &is_gen_pp();
	const bool &is_gen_mm();
	const int &gen_njets();
	const int &gen_nleps();
	const int &gen_nmus();
	const int &gen_nels();
	const int &gen_ntaus();
	const float &gen_ht();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearjet_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearlep_p4();
	const float &lep1_wfr();
	const float &lep1_wflip();
	const float &lep1_nearjet_dr();
	const float &lep1_nearlep_dr();
	const int &lep1_nearlep_id();
	const bool &lep1_isFromH();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearjet_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearlep_p4();
	const float &lep2_wfr();
	const float &lep2_wflip();
	const float &lep2_nearjet_dr();
	const float &lep2_nearlep_dr();
	const int &lep2_nearlep_id();
	const bool &lep2_isFromH();
	const float &jets_dr12();
	const float &dijet_mass();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_p4();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_p4_up();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_p4_dn();
	const vector<int> &vjets_mcflavor_phys();
	const vector<int> &vjets_mcflavor_algo();
	const vector<int> &vjets_mcflavor_phys_up();
	const vector<int> &vjets_mcflavor_algo_up();
	const vector<int> &vjets_mcflavor_phys_dn();
	const vector<int> &vjets_mcflavor_algo_dn();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_mc3p4();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vgenjets_p4();
	const vector<int> &vjets_mc3id();
	const vector<int> &vjets_momid();
	const vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_nearjet_p4();
	const vector<float> &vjets_nearjet_dr();
	const vector<float> &vjets_bdisc();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep1_p4();
	const int &gen_lep1_pdgid();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep2_p4();
	const int &gen_lep2_pdgid();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_dilep_p4();
	const int &gen_dilep_type();
	const float &gen_dilep_mass();
	const float &gen_dilep_dphi();
	const float &gen_dilep_deta();
	const float &gen_dilep_dr();
	const int &pfcandid5();
	const int &pfcandid10();
	const int &pfcanddirid10();
	const int &pfcandvetoid10();
	const int &pfcandvetoLid10();
	const int &pfcandidOS10();
	const int &pfcandidOS10looseZ();
	const int &pfcandid5looseZ();
	const float &trkpt5();
	const float &mleptrk5();
	const float &trkreliso5();
	const float &trkpt10();
	const float &mleptrk10();
	const float &trkreliso10();
	const float &trkpt5loose();
	const float &trkreliso5loose();
	const float &trkpt10loose();
	const float &trkreliso10loose();
	const float &trkpt10pt0p1();
	const float &trkreliso10pt0p1();
	const float &trkpt10pt0p2();
	const float &trkreliso10pt0p2();
	const float &trkpt10pt0p3();
	const float &trkreliso10pt0p3();
	const float &trkpt10pt0p4();
	const float &trkreliso10pt0p4();
	const float &trkpt10pt0p5();
	const float &trkreliso10pt0p5();
	const float &trkpt10pt0p6();
	const float &trkreliso10pt0p6();
	const float &trkpt10pt0p7();
	const float &trkreliso10pt0p7();
	const float &trkpt10pt0p8();
	const float &trkreliso10pt0p8();
	const float &trkpt10pt0p9();
	const float &trkreliso10pt0p9();
	const float &trkpt10pt1p0();
	const float &trkreliso10pt1p0();
	const float &pfcandiso5();
	const float &pfcandiso10();
	const float &pfcanddiriso10();
	const float &pfcandvetoiso10();
	const float &pfcandvetoLiso10();
	const float &pfcandisoOS10();
	const float &pfcandisoOS10looseZ();
	const float &pfcandiso5looseZ();
	const float &pfcandpt5();
	const float &pfcandpt10();
	const float &pfcanddirpt10();
	const float &pfcandvetopt10();
	const float &pfcandvetoLpt10();
	const float &pfcandptOS10();
	const float &pfcandptOS10looseZ();
	const float &pfcandpt5looseZ();
	const float &pfcanddz5();
	const float &pfcanddz10();
	const float &pfcanddirdz10();
	const float &pfcandvetodz10();
	const float &pfcandvetoLdz10();
	const float &pfcanddzOS10();
	const float &pfcanddzOS10looseZ();
	const float &pfcanddz5looseZ();
	const float &pfcandmindrj5();
	const float &pfcandmindrj10();
	const float &pfcanddirmindrj10();
	const float &pfcandvetomindrj10();
	const float &pfcandvetoLmindrj10();
	const float &pfcandpt10pt0p1();
	const float &pfcandiso10pt0p1();
	const float &pfcandpt10pt0p2();
	const float &pfcandiso10pt0p2();
	const float &pfcandpt10pt0p3();
	const float &pfcandiso10pt0p3();
	const float &pfcandpt10pt0p4();
	const float &pfcandiso10pt0p4();
	const float &pfcandpt10pt0p5();
	const float &pfcandiso10pt0p5();
	const float &pfcandpt10pt0p6();
	const float &pfcandiso10pt0p6();
	const float &pfcandpt10pt0p7();
	const float &pfcandiso10pt0p7();
	const float &pfcandpt10pt0p8();
	const float &pfcandiso10pt0p8();
	const float &pfcandpt10pt0p9();
	const float &pfcandiso10pt0p9();
	const float &pfcandpt10pt1p0();
	const float &pfcandiso10pt1p0();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcand5();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcand10();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcanddir10();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcandveto10();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcandvetoL10();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcandOS10();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcandOS10looseZ();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfcand5looseZ();
	const int &pfTau15_leadPtcandID();
	const int &pfTau_leadPtcandID();
	const int &pfTauLoose_leadPtcandID();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTau15();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTau15_leadPtcand();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTau();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTau_leadPtcand();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTauLoose();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &pfTauLoose_leadPtcand();
	const vector<float> &pfjets_beta();
	const vector<float> &pfjets_beta2();
	const vector<float> &pfjets_beta_0p1();
	const vector<float> &pfjets_beta_0p2();
	const vector<float> &pfjets_beta2_0p1();
	const vector<float> &pfjets_beta2_0p5();
	const vector<float> &pfjets_mvaPUid();
	const vector<float> &pfjets_mva5xPUid();
	const vector<float> &pfjets_mvaBeta();
	const bool &passes_isotrk_veto();
	const bool &passes_tau_veto();
	const int &njets_pv_tight0();
	const int &njets_pv_tight1();
	const int &njets_pv_tight2();
}
#endif
