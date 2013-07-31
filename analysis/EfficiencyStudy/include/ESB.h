// -*- C++ -*-
#ifndef ESB_H
#define ESB_H
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
class ESB {
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
	TString *dataset_;
	TBranch *dataset_branch;
	bool dataset_isLoaded;
	TString *filename_;
	TBranch *filename_branch;
	bool filename_isLoaded;
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
	lep1_dz_branch = 0;
	if (tree->GetBranch("lep1_dz") != 0) {
		lep1_dz_branch = tree->GetBranch("lep1_dz");
		if (lep1_dz_branch) {lep1_dz_branch->SetAddress(&lep1_dz_);}
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
	lep2_dz_branch = 0;
	if (tree->GetBranch("lep2_dz") != 0) {
		lep2_dz_branch = tree->GetBranch("lep2_dz");
		if (lep2_dz_branch) {lep2_dz_branch->SetAddress(&lep2_dz_);}
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
	is_os_branch = 0;
	if (tree->GetBranch("is_os") != 0) {
		is_os_branch = tree->GetBranch("is_os");
		if (is_os_branch) {is_os_branch->SetAddress(&is_os_);}
	}
	is_ss_branch = 0;
	if (tree->GetBranch("is_ss") != 0) {
		is_ss_branch = tree->GetBranch("is_ss");
		if (is_ss_branch) {is_ss_branch->SetAddress(&is_ss_);}
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
		scale1fb_isLoaded = false;
		xsec_isLoaded = false;
		kfactor_isLoaded = false;
		gen_met_isLoaded = false;
		gen_met_phi_isLoaded = false;
		dataset_isLoaded = false;
		filename_isLoaded = false;
		lep1_p4_isLoaded = false;
		lep1_passes_id_isLoaded = false;
		lep1_passes_iso_isLoaded = false;
		lep1_is_num_isLoaded = false;
		lep1_is_fo_isLoaded = false;
		lep1_is_fromw_isLoaded = false;
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
		lep2_is_fromw_isLoaded = false;
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
	if (scale1fb_branch != 0) scale1fb();
	if (xsec_branch != 0) xsec();
	if (kfactor_branch != 0) kfactor();
	if (gen_met_branch != 0) gen_met();
	if (gen_met_phi_branch != 0) gen_met_phi();
	if (dataset_branch != 0) dataset();
	if (filename_branch != 0) filename();
	if (lep1_p4_branch != 0) lep1_p4();
	if (lep1_passes_id_branch != 0) lep1_passes_id();
	if (lep1_passes_iso_branch != 0) lep1_passes_iso();
	if (lep1_is_num_branch != 0) lep1_is_num();
	if (lep1_is_fo_branch != 0) lep1_is_fo();
	if (lep1_is_fromw_branch != 0) lep1_is_fromw();
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
	if (lep2_is_fromw_branch != 0) lep2_is_fromw();
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
extern ESB eff_study_baby;
#endif

namespace esb {
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
	const float &scale1fb();
	const float &xsec();
	const float &kfactor();
	const float &gen_met();
	const float &gen_met_phi();
	const TString &dataset();
	const TString &filename();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_p4();
	const bool &lep1_passes_id();
	const bool &lep1_passes_iso();
	const bool &lep1_is_num();
	const bool &lep1_is_fo();
	const int &lep1_is_fromw();
	const int &lep1_charge();
	const int &lep1_pdgid();
	const int &lep1_type();
	const float &lep1_d0();
	const float &lep1_dz();
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
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mcp4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mc3p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_mc_momp4();
	const int &lep1_mcid();
	const int &lep1_mc3id();
	const int &lep1_momid();
	const int &lep1_mc3_momid();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_gsf_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_ctf_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_sc_p4();
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
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_gfit_p4();
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
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_p4();
	const bool &lep2_passes_id();
	const bool &lep2_passes_iso();
	const bool &lep2_is_num();
	const bool &lep2_is_fo();
	const int &lep2_is_fromw();
	const int &lep2_charge();
	const int &lep2_pdgid();
	const int &lep2_type();
	const float &lep2_d0();
	const float &lep2_dz();
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
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mcp4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mc3p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_mc_momp4();
	const int &lep2_mcid();
	const int &lep2_mc3id();
	const int &lep2_momid();
	const int &lep2_mc3_momid();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_gsf_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_ctf_p4();
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_sc_p4();
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
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_gfit_p4();
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
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &dilep_p4();
	const bool &is_os();
	const bool &is_ss();
	const int &dilep_type();
	const int &dilep_gen_type();
	const float &dilep_mass();
	const float &dilep_dphi();
	const float &dilep_deta();
	const float &dilep_dr();
	const int &fiduciality();
}
#endif
