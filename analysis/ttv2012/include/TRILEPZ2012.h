// -*- C++ -*-
#ifndef TRILEPZ2012_H
#define TRILEPZ2012_H
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
class TRILEPZ2012 {
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
	TString dataset_;
	TBranch *dataset_branch;
	bool dataset_isLoaded;
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
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *zdilep_p4_;
	TBranch *zdilep_p4_branch;
	bool zdilep_p4_isLoaded;
	bool	zis_os_;
	TBranch *zis_os_branch;
	bool zis_os_isLoaded;
	bool	zis_ss_;
	TBranch *zis_ss_branch;
	bool zis_ss_isLoaded;
	int	zdilep_type_;
	TBranch *zdilep_type_branch;
	bool zdilep_type_isLoaded;
	int	zdilep_gen_type_;
	TBranch *zdilep_gen_type_branch;
	bool zdilep_gen_type_isLoaded;
	float	zdilep_mass_;
	TBranch *zdilep_mass_branch;
	bool zdilep_mass_isLoaded;
	float	zdilep_dphi_;
	TBranch *zdilep_dphi_branch;
	bool zdilep_dphi_isLoaded;
	float	zdilep_deta_;
	TBranch *zdilep_deta_branch;
	bool zdilep_deta_isLoaded;
	float	zdilep_dr_;
	TBranch *zdilep_dr_branch;
	bool zdilep_dr_isLoaded;
	int	zfiduciality_;
	TBranch *zfiduciality_branch;
	bool zfiduciality_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *wp4_;
	TBranch *wp4_branch;
	bool wp4_isLoaded;
	bool	wpasses_id_;
	TBranch *wpasses_id_branch;
	bool wpasses_id_isLoaded;
	bool	wpasses_iso_;
	TBranch *wpasses_iso_branch;
	bool wpasses_iso_isLoaded;
	bool	wis_num_;
	TBranch *wis_num_branch;
	bool wis_num_isLoaded;
	bool	wis_fo_;
	TBranch *wis_fo_branch;
	bool wis_fo_isLoaded;
	int	wis_fromw_;
	TBranch *wis_fromw_branch;
	bool wis_fromw_isLoaded;
	int	wcharge_;
	TBranch *wcharge_branch;
	bool wcharge_isLoaded;
	int	wpdgid_;
	TBranch *wpdgid_branch;
	bool wpdgid_isLoaded;
	int	wtype_;
	TBranch *wtype_branch;
	bool wtype_isLoaded;
	float	wd0_;
	TBranch *wd0_branch;
	bool wd0_isLoaded;
	float	wdz_;
	TBranch *wdz_branch;
	bool wdz_isLoaded;
	float	wmt_;
	TBranch *wmt_branch;
	bool wmt_isLoaded;
	float	wcorpfiso_;
	TBranch *wcorpfiso_branch;
	bool wcorpfiso_isLoaded;
	float	wpfiso_;
	TBranch *wpfiso_branch;
	bool wpfiso_isLoaded;
	float	wchiso_;
	TBranch *wchiso_branch;
	bool wchiso_isLoaded;
	float	wemiso_;
	TBranch *wemiso_branch;
	bool wemiso_isLoaded;
	float	wnhiso_;
	TBranch *wnhiso_branch;
	bool wnhiso_isLoaded;
	float	wcorpfiso04_;
	TBranch *wcorpfiso04_branch;
	bool wcorpfiso04_isLoaded;
	float	wpfiso04_;
	TBranch *wpfiso04_branch;
	bool wpfiso04_isLoaded;
	float	wchiso04_;
	TBranch *wchiso04_branch;
	bool wchiso04_isLoaded;
	float	wemiso04_;
	TBranch *wemiso04_branch;
	bool wemiso04_isLoaded;
	float	wnhiso04_;
	TBranch *wnhiso04_branch;
	bool wnhiso04_isLoaded;
	float	wcordetiso_;
	TBranch *wcordetiso_branch;
	bool wcordetiso_isLoaded;
	float	wdetiso_;
	TBranch *wdetiso_branch;
	bool wdetiso_isLoaded;
	float	wtrkiso_;
	TBranch *wtrkiso_branch;
	bool wtrkiso_isLoaded;
	float	wecaliso_;
	TBranch *wecaliso_branch;
	bool wecaliso_isLoaded;
	float	whcaliso_;
	TBranch *whcaliso_branch;
	bool whcaliso_isLoaded;
	float	wcordetiso04_;
	TBranch *wcordetiso04_branch;
	bool wcordetiso04_isLoaded;
	float	wdetiso04_;
	TBranch *wdetiso04_branch;
	bool wdetiso04_isLoaded;
	float	wtrkiso04_;
	TBranch *wtrkiso04_branch;
	bool wtrkiso04_isLoaded;
	float	wecaliso04_;
	TBranch *wecaliso04_branch;
	bool wecaliso04_isLoaded;
	float	whcaliso04_;
	TBranch *whcaliso04_branch;
	bool whcaliso04_isLoaded;
	float	weffarea_;
	TBranch *weffarea_branch;
	bool weffarea_isLoaded;
	float	weffarea04_;
	TBranch *weffarea04_branch;
	bool weffarea04_isLoaded;
	float	wdbeta_;
	TBranch *wdbeta_branch;
	bool wdbeta_isLoaded;
	float	wdbeta04_;
	TBranch *wdbeta04_branch;
	bool wdbeta04_isLoaded;
	float	wsf_lepeff_;
	TBranch *wsf_lepeff_branch;
	bool wsf_lepeff_isLoaded;
	float	wsf_trig_;
	TBranch *wsf_trig_branch;
	bool wsf_trig_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *wmcp4_;
	TBranch *wmcp4_branch;
	bool wmcp4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *wmc3p4_;
	TBranch *wmc3p4_branch;
	bool wmc3p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *wmc_momp4_;
	TBranch *wmc_momp4_branch;
	bool wmc_momp4_isLoaded;
	int	wmcid_;
	TBranch *wmcid_branch;
	bool wmcid_isLoaded;
	int	wmc3id_;
	TBranch *wmc3id_branch;
	bool wmc3id_isLoaded;
	int	wmomid_;
	TBranch *wmomid_branch;
	bool wmomid_isLoaded;
	int	wmc3_momid_;
	TBranch *wmc3_momid_branch;
	bool wmc3_momid_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *wgsf_p4_;
	TBranch *wgsf_p4_branch;
	bool wgsf_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *wctf_p4_;
	TBranch *wctf_p4_branch;
	bool wctf_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *wsc_p4_;
	TBranch *wsc_p4_branch;
	bool wsc_p4_isLoaded;
	bool	wq3agree_;
	TBranch *wq3agree_branch;
	bool wq3agree_isLoaded;
	bool	wis_conv_;
	TBranch *wis_conv_branch;
	bool wis_conv_isLoaded;
	int	wqsc_;
	TBranch *wqsc_branch;
	bool wqsc_isLoaded;
	int	wqctf_;
	TBranch *wqctf_branch;
	bool wqctf_isLoaded;
	int	wqgsf_;
	TBranch *wqgsf_branch;
	bool wqgsf_isLoaded;
	int	wnmhits_;
	TBranch *wnmhits_branch;
	bool wnmhits_isLoaded;
	int	weleid_veto_;
	TBranch *weleid_veto_branch;
	bool weleid_veto_isLoaded;
	int	weleid_loose_;
	TBranch *weleid_loose_branch;
	bool weleid_loose_isLoaded;
	int	weleid_medium_;
	TBranch *weleid_medium_branch;
	bool weleid_medium_isLoaded;
	int	weleid_tight_;
	TBranch *weleid_tight_branch;
	bool weleid_tight_isLoaded;
	float	wdphiin_;
	TBranch *wdphiin_branch;
	bool wdphiin_isLoaded;
	float	wdetain_;
	TBranch *wdetain_branch;
	bool wdetain_isLoaded;
	float	wsieie_;
	TBranch *wsieie_branch;
	bool wsieie_isLoaded;
	float	whoe_;
	TBranch *whoe_branch;
	bool whoe_isLoaded;
	float	wooemoop_;
	TBranch *wooemoop_branch;
	bool wooemoop_isLoaded;
	float	wconv_dist_;
	TBranch *wconv_dist_branch;
	bool wconv_dist_isLoaded;
	float	wconv_dcot_;
	TBranch *wconv_dcot_branch;
	bool wconv_dcot_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *wgfit_p4_;
	TBranch *wgfit_p4_branch;
	bool wgfit_p4_isLoaded;
	bool	wis_global_;
	TBranch *wis_global_branch;
	bool wis_global_isLoaded;
	bool	wis_tracker_;
	TBranch *wis_tracker_branch;
	bool wis_tracker_isLoaded;
	bool	wis_stamu_;
	TBranch *wis_stamu_branch;
	bool wis_stamu_isLoaded;
	bool	wis_pfmu_;
	TBranch *wis_pfmu_branch;
	bool wis_pfmu_isLoaded;
	bool	wis_loosemu_;
	TBranch *wis_loosemu_branch;
	bool wis_loosemu_isLoaded;
	bool	wis_tightmu_;
	TBranch *wis_tightmu_branch;
	bool wis_tightmu_isLoaded;
	int	wnpixelhits_;
	TBranch *wnpixelhits_branch;
	bool wnpixelhits_isLoaded;
	int	wnsihits_;
	TBranch *wnsihits_branch;
	bool wnsihits_isLoaded;
	int	wnsilayers_;
	TBranch *wnsilayers_branch;
	bool wnsilayers_isLoaded;
	int	wnstahits_;
	TBranch *wnstahits_branch;
	bool wnstahits_isLoaded;
	int	wnstations_;
	TBranch *wnstations_branch;
	bool wnstations_isLoaded;
	float	wchi2_;
	TBranch *wchi2_branch;
	bool wchi2_isLoaded;
	float	wndof_;
	TBranch *wndof_branch;
	bool wndof_isLoaded;
	float	wpterr_;
	TBranch *wpterr_branch;
	bool wpterr_isLoaded;
	float	wecal_vetodep_;
	TBranch *wecal_vetodep_branch;
	bool wecal_vetodep_isLoaded;
	float	whcal_vetodep_;
	TBranch *whcal_vetodep_branch;
	bool whcal_vetodep_isLoaded;
	unsigned int	selection_;
	TBranch *selection_branch;
	bool selection_isLoaded;
	bool	clean_;
	TBranch *clean_branch;
	bool clean_isLoaded;
	bool	is_good_lumi_;
	TBranch *is_good_lumi_branch;
	bool is_good_lumi_isLoaded;
	int	njets15_;
	TBranch *njets15_branch;
	bool njets15_isLoaded;
	int	njets30_;
	TBranch *njets30_branch;
	bool njets30_isLoaded;
	int	nbtags_loose_;
	TBranch *nbtags_loose_branch;
	bool nbtags_loose_isLoaded;
	int	nbtags_tight_;
	TBranch *nbtags_tight_branch;
	bool nbtags_tight_isLoaded;
	float	vtxw_;
	TBranch *vtxw_branch;
	bool vtxw_isLoaded;
	float	ht_;
	TBranch *ht_branch;
	bool ht_isLoaded;
	float	rho_;
	TBranch *rho_branch;
	bool rho_isLoaded;
	float	rho_iso_;
	TBranch *rho_iso_branch;
	bool rho_iso_isLoaded;
	float	sf_dileptrig_;
	TBranch *sf_dileptrig_branch;
	bool sf_dileptrig_isLoaded;
	float	sf_lepeff_;
	TBranch *sf_lepeff_branch;
	bool sf_lepeff_isLoaded;
	bool	trig_mm_;
	TBranch *trig_mm_branch;
	bool trig_mm_isLoaded;
	bool	trig_em_;
	TBranch *trig_em_branch;
	bool trig_em_isLoaded;
	bool	trig_ee_;
	TBranch *trig_ee_branch;
	bool trig_ee_isLoaded;
	int	event_type_;
	TBranch *event_type_branch;
	bool event_type_isLoaded;
	int	njets30_dn_;
	TBranch *njets30_dn_branch;
	bool njets30_dn_isLoaded;
	int	njets30_up_;
	TBranch *njets30_up_branch;
	bool njets30_up_isLoaded;
	int	njets15_dn_;
	TBranch *njets15_dn_branch;
	bool njets15_dn_isLoaded;
	int	njets15_up_;
	TBranch *njets15_up_branch;
	bool njets15_up_isLoaded;
	int	nbtags_loose_dn_;
	TBranch *nbtags_loose_dn_branch;
	bool nbtags_loose_dn_isLoaded;
	int	nbtags_loose_up_;
	TBranch *nbtags_loose_up_branch;
	bool nbtags_loose_up_isLoaded;
	float	ht_dn_;
	TBranch *ht_dn_branch;
	bool ht_dn_isLoaded;
	float	ht_up_;
	TBranch *ht_up_branch;
	bool ht_up_isLoaded;
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
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_nearbjet_p4_;
	TBranch *lep1_nearbjet_p4_branch;
	bool lep1_nearbjet_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_nearjet_p4_;
	TBranch *lep1_nearjet_p4_branch;
	bool lep1_nearjet_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_nearlep_p4_;
	TBranch *lep1_nearlep_p4_branch;
	bool lep1_nearlep_p4_isLoaded;
	float	lep1_wfr_;
	TBranch *lep1_wfr_branch;
	bool lep1_wfr_isLoaded;
	float	lep1_nearbjet_dr_;
	TBranch *lep1_nearbjet_dr_branch;
	bool lep1_nearbjet_dr_isLoaded;
	float	lep1_nearjet_dr_;
	TBranch *lep1_nearjet_dr_branch;
	bool lep1_nearjet_dr_isLoaded;
	float	lep1_nearlep_dr_;
	TBranch *lep1_nearlep_dr_branch;
	bool lep1_nearlep_dr_isLoaded;
	int	lep1_nearlep_id_;
	TBranch *lep1_nearlep_id_branch;
	bool lep1_nearlep_id_isLoaded;
	int	lep1_passes_id_bitmask_;
	TBranch *lep1_passes_id_bitmask_branch;
	bool lep1_passes_id_bitmask_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_nearbjet_p4_;
	TBranch *lep2_nearbjet_p4_branch;
	bool lep2_nearbjet_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_nearjet_p4_;
	TBranch *lep2_nearjet_p4_branch;
	bool lep2_nearjet_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_nearlep_p4_;
	TBranch *lep2_nearlep_p4_branch;
	bool lep2_nearlep_p4_isLoaded;
	float	lep2_wfr_;
	TBranch *lep2_wfr_branch;
	bool lep2_wfr_isLoaded;
	float	lep2_nearbjet_dr_;
	TBranch *lep2_nearbjet_dr_branch;
	bool lep2_nearbjet_dr_isLoaded;
	float	lep2_nearjet_dr_;
	TBranch *lep2_nearjet_dr_branch;
	bool lep2_nearjet_dr_isLoaded;
	float	lep2_nearlep_dr_;
	TBranch *lep2_nearlep_dr_branch;
	bool lep2_nearlep_dr_isLoaded;
	int	lep2_nearlep_id_;
	TBranch *lep2_nearlep_id_branch;
	bool lep2_nearlep_id_isLoaded;
	int	lep2_passes_id_bitmask_;
	TBranch *lep2_passes_id_bitmask_branch;
	bool lep2_passes_id_bitmask_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep3_nearbjet_p4_;
	TBranch *lep3_nearbjet_p4_branch;
	bool lep3_nearbjet_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep3_nearjet_p4_;
	TBranch *lep3_nearjet_p4_branch;
	bool lep3_nearjet_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep3_nearlep_p4_;
	TBranch *lep3_nearlep_p4_branch;
	bool lep3_nearlep_p4_isLoaded;
	float	lep3_wfr_;
	TBranch *lep3_wfr_branch;
	bool lep3_wfr_isLoaded;
	float	lep3_nearbjet_dr_;
	TBranch *lep3_nearbjet_dr_branch;
	bool lep3_nearbjet_dr_isLoaded;
	float	lep3_nearjet_dr_;
	TBranch *lep3_nearjet_dr_branch;
	bool lep3_nearjet_dr_isLoaded;
	float	lep3_nearlep_dr_;
	TBranch *lep3_nearlep_dr_branch;
	bool lep3_nearlep_dr_isLoaded;
	int	lep3_nearlep_id_;
	TBranch *lep3_nearlep_id_branch;
	bool lep3_nearlep_id_isLoaded;
	int	lep3_passes_id_bitmask_;
	TBranch *lep3_passes_id_bitmask_branch;
	bool lep3_passes_id_bitmask_isLoaded;
	bool	is_gen_z_;
	TBranch *is_gen_z_branch;
	bool is_gen_z_isLoaded;
	bool	is_gen_w_;
	TBranch *is_gen_w_branch;
	bool is_gen_w_isLoaded;
	int	gen_nbtags_;
	TBranch *gen_nbtags_branch;
	bool gen_nbtags_isLoaded;
	int	gen_njets_;
	TBranch *gen_njets_branch;
	bool gen_njets_isLoaded;
	float	gen_ht_;
	TBranch *gen_ht_branch;
	bool gen_ht_isLoaded;
	float	gen_nleps_;
	TBranch *gen_nleps_branch;
	bool gen_nleps_isLoaded;
	float	sf_nbtag_;
	TBranch *sf_nbtag_branch;
	bool sf_nbtag_isLoaded;
	float	sf_nbtag2_;
	TBranch *sf_nbtag2_branch;
	bool sf_nbtag2_isLoaded;
	float	sf_unc_nbtag_;
	TBranch *sf_unc_nbtag_branch;
	bool sf_unc_nbtag_isLoaded;
	float	sf_unc_nbtag2_;
	TBranch *sf_unc_nbtag2_branch;
	bool sf_unc_nbtag2_isLoaded;
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
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *vbjets_p4_;
	TBranch *vbjets_p4_branch;
	bool vbjets_p4_isLoaded;
	vector<bool> *vbtags_loose_;
	TBranch *vbtags_loose_branch;
	bool vbtags_loose_isLoaded;
	vector<bool> *vbtags_tight_;
	TBranch *vbtags_tight_branch;
	bool vbtags_tight_isLoaded;
	vector<float> *vbjets_disc_;
	TBranch *vbjets_disc_branch;
	bool vbjets_disc_isLoaded;
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
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *gen_lep3_p4_;
	TBranch *gen_lep3_p4_branch;
	bool gen_lep3_p4_isLoaded;
	float	gen_mt_;
	TBranch *gen_mt_branch;
	bool gen_mt_isLoaded;
	int	gen_lep3_pdgid_;
	TBranch *gen_lep3_pdgid_branch;
	bool gen_lep3_pdgid_isLoaded;
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
	float	lep1_ele_mva_trig_;
	TBranch *lep1_ele_mva_trig_branch;
	bool lep1_ele_mva_trig_isLoaded;
	float	lep2_ele_mva_trig_;
	TBranch *lep2_ele_mva_trig_branch;
	bool lep2_ele_mva_trig_isLoaded;
	float	lep3_ele_mva_trig_;
	TBranch *lep3_ele_mva_trig_branch;
	bool lep3_ele_mva_trig_isLoaded;
	float	lep1_ele_mva_nontrig_;
	TBranch *lep1_ele_mva_nontrig_branch;
	bool lep1_ele_mva_nontrig_isLoaded;
	float	lep2_ele_mva_nontrig_;
	TBranch *lep2_ele_mva_nontrig_branch;
	bool lep2_ele_mva_nontrig_isLoaded;
	float	lep3_ele_mva_nontrig_;
	TBranch *lep3_ele_mva_nontrig_branch;
	bool lep3_ele_mva_nontrig_isLoaded;
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
	zdilep_p4_branch = 0;
	if (tree->GetBranch("zdilep_p4") != 0) {
		zdilep_p4_branch = tree->GetBranch("zdilep_p4");
		zdilep_p4_branch->SetAddress(&zdilep_p4_);
	}
	wp4_branch = 0;
	if (tree->GetBranch("wp4") != 0) {
		wp4_branch = tree->GetBranch("wp4");
		wp4_branch->SetAddress(&wp4_);
	}
	wmcp4_branch = 0;
	if (tree->GetBranch("wmcp4") != 0) {
		wmcp4_branch = tree->GetBranch("wmcp4");
		wmcp4_branch->SetAddress(&wmcp4_);
	}
	wmc3p4_branch = 0;
	if (tree->GetBranch("wmc3p4") != 0) {
		wmc3p4_branch = tree->GetBranch("wmc3p4");
		wmc3p4_branch->SetAddress(&wmc3p4_);
	}
	wmc_momp4_branch = 0;
	if (tree->GetBranch("wmc_momp4") != 0) {
		wmc_momp4_branch = tree->GetBranch("wmc_momp4");
		wmc_momp4_branch->SetAddress(&wmc_momp4_);
	}
	wgsf_p4_branch = 0;
	if (tree->GetBranch("wgsf_p4") != 0) {
		wgsf_p4_branch = tree->GetBranch("wgsf_p4");
		wgsf_p4_branch->SetAddress(&wgsf_p4_);
	}
	wctf_p4_branch = 0;
	if (tree->GetBranch("wctf_p4") != 0) {
		wctf_p4_branch = tree->GetBranch("wctf_p4");
		wctf_p4_branch->SetAddress(&wctf_p4_);
	}
	wsc_p4_branch = 0;
	if (tree->GetBranch("wsc_p4") != 0) {
		wsc_p4_branch = tree->GetBranch("wsc_p4");
		wsc_p4_branch->SetAddress(&wsc_p4_);
	}
	wgfit_p4_branch = 0;
	if (tree->GetBranch("wgfit_p4") != 0) {
		wgfit_p4_branch = tree->GetBranch("wgfit_p4");
		wgfit_p4_branch->SetAddress(&wgfit_p4_);
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
	lep1_nearlep_p4_branch = 0;
	if (tree->GetBranch("lep1_nearlep_p4") != 0) {
		lep1_nearlep_p4_branch = tree->GetBranch("lep1_nearlep_p4");
		lep1_nearlep_p4_branch->SetAddress(&lep1_nearlep_p4_);
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
	lep2_nearlep_p4_branch = 0;
	if (tree->GetBranch("lep2_nearlep_p4") != 0) {
		lep2_nearlep_p4_branch = tree->GetBranch("lep2_nearlep_p4");
		lep2_nearlep_p4_branch->SetAddress(&lep2_nearlep_p4_);
	}
	lep3_nearbjet_p4_branch = 0;
	if (tree->GetBranch("lep3_nearbjet_p4") != 0) {
		lep3_nearbjet_p4_branch = tree->GetBranch("lep3_nearbjet_p4");
		lep3_nearbjet_p4_branch->SetAddress(&lep3_nearbjet_p4_);
	}
	lep3_nearjet_p4_branch = 0;
	if (tree->GetBranch("lep3_nearjet_p4") != 0) {
		lep3_nearjet_p4_branch = tree->GetBranch("lep3_nearjet_p4");
		lep3_nearjet_p4_branch->SetAddress(&lep3_nearjet_p4_);
	}
	lep3_nearlep_p4_branch = 0;
	if (tree->GetBranch("lep3_nearlep_p4") != 0) {
		lep3_nearlep_p4_branch = tree->GetBranch("lep3_nearlep_p4");
		lep3_nearlep_p4_branch->SetAddress(&lep3_nearlep_p4_);
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
	vbjets_p4_branch = 0;
	if (tree->GetBranch("vbjets_p4") != 0) {
		vbjets_p4_branch = tree->GetBranch("vbjets_p4");
		vbjets_p4_branch->SetAddress(&vbjets_p4_);
	}
	gen_lep1_p4_branch = 0;
	if (tree->GetBranch("gen_lep1_p4") != 0) {
		gen_lep1_p4_branch = tree->GetBranch("gen_lep1_p4");
		gen_lep1_p4_branch->SetAddress(&gen_lep1_p4_);
	}
	gen_lep2_p4_branch = 0;
	if (tree->GetBranch("gen_lep2_p4") != 0) {
		gen_lep2_p4_branch = tree->GetBranch("gen_lep2_p4");
		gen_lep2_p4_branch->SetAddress(&gen_lep2_p4_);
	}
	gen_lep3_p4_branch = 0;
	if (tree->GetBranch("gen_lep3_p4") != 0) {
		gen_lep3_p4_branch = tree->GetBranch("gen_lep3_p4");
		gen_lep3_p4_branch->SetAddress(&gen_lep3_p4_);
	}
	gen_dilep_p4_branch = 0;
	if (tree->GetBranch("gen_dilep_p4") != 0) {
		gen_dilep_p4_branch = tree->GetBranch("gen_dilep_p4");
		gen_dilep_p4_branch->SetAddress(&gen_dilep_p4_);
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
	uncorpfmet_branch = 0;
	if (tree->GetBranch("uncorpfmet") != 0) {
		uncorpfmet_branch = tree->GetBranch("uncorpfmet");
		uncorpfmet_branch->SetAddress(&uncorpfmet_);
	}
	uncorpfmet_phi_branch = 0;
	if (tree->GetBranch("uncorpfmet_phi") != 0) {
		uncorpfmet_phi_branch = tree->GetBranch("uncorpfmet_phi");
		uncorpfmet_phi_branch->SetAddress(&uncorpfmet_phi_);
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
	dataset_branch = 0;
	if (tree->GetBranch("dataset") != 0) {
		dataset_branch = tree->GetBranch("dataset");
		dataset_branch->SetAddress(&dataset_);
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
	lep1_is_fromw_branch = 0;
	if (tree->GetBranch("lep1_is_fromw") != 0) {
		lep1_is_fromw_branch = tree->GetBranch("lep1_is_fromw");
		lep1_is_fromw_branch->SetAddress(&lep1_is_fromw_);
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
	lep2_is_fromw_branch = 0;
	if (tree->GetBranch("lep2_is_fromw") != 0) {
		lep2_is_fromw_branch = tree->GetBranch("lep2_is_fromw");
		lep2_is_fromw_branch->SetAddress(&lep2_is_fromw_);
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
	zis_os_branch = 0;
	if (tree->GetBranch("zis_os") != 0) {
		zis_os_branch = tree->GetBranch("zis_os");
		zis_os_branch->SetAddress(&zis_os_);
	}
	zis_ss_branch = 0;
	if (tree->GetBranch("zis_ss") != 0) {
		zis_ss_branch = tree->GetBranch("zis_ss");
		zis_ss_branch->SetAddress(&zis_ss_);
	}
	zdilep_type_branch = 0;
	if (tree->GetBranch("zdilep_type") != 0) {
		zdilep_type_branch = tree->GetBranch("zdilep_type");
		zdilep_type_branch->SetAddress(&zdilep_type_);
	}
	zdilep_gen_type_branch = 0;
	if (tree->GetBranch("zdilep_gen_type") != 0) {
		zdilep_gen_type_branch = tree->GetBranch("zdilep_gen_type");
		zdilep_gen_type_branch->SetAddress(&zdilep_gen_type_);
	}
	zdilep_mass_branch = 0;
	if (tree->GetBranch("zdilep_mass") != 0) {
		zdilep_mass_branch = tree->GetBranch("zdilep_mass");
		zdilep_mass_branch->SetAddress(&zdilep_mass_);
	}
	zdilep_dphi_branch = 0;
	if (tree->GetBranch("zdilep_dphi") != 0) {
		zdilep_dphi_branch = tree->GetBranch("zdilep_dphi");
		zdilep_dphi_branch->SetAddress(&zdilep_dphi_);
	}
	zdilep_deta_branch = 0;
	if (tree->GetBranch("zdilep_deta") != 0) {
		zdilep_deta_branch = tree->GetBranch("zdilep_deta");
		zdilep_deta_branch->SetAddress(&zdilep_deta_);
	}
	zdilep_dr_branch = 0;
	if (tree->GetBranch("zdilep_dr") != 0) {
		zdilep_dr_branch = tree->GetBranch("zdilep_dr");
		zdilep_dr_branch->SetAddress(&zdilep_dr_);
	}
	zfiduciality_branch = 0;
	if (tree->GetBranch("zfiduciality") != 0) {
		zfiduciality_branch = tree->GetBranch("zfiduciality");
		zfiduciality_branch->SetAddress(&zfiduciality_);
	}
	wpasses_id_branch = 0;
	if (tree->GetBranch("wpasses_id") != 0) {
		wpasses_id_branch = tree->GetBranch("wpasses_id");
		wpasses_id_branch->SetAddress(&wpasses_id_);
	}
	wpasses_iso_branch = 0;
	if (tree->GetBranch("wpasses_iso") != 0) {
		wpasses_iso_branch = tree->GetBranch("wpasses_iso");
		wpasses_iso_branch->SetAddress(&wpasses_iso_);
	}
	wis_num_branch = 0;
	if (tree->GetBranch("wis_num") != 0) {
		wis_num_branch = tree->GetBranch("wis_num");
		wis_num_branch->SetAddress(&wis_num_);
	}
	wis_fo_branch = 0;
	if (tree->GetBranch("wis_fo") != 0) {
		wis_fo_branch = tree->GetBranch("wis_fo");
		wis_fo_branch->SetAddress(&wis_fo_);
	}
	wis_fromw_branch = 0;
	if (tree->GetBranch("wis_fromw") != 0) {
		wis_fromw_branch = tree->GetBranch("wis_fromw");
		wis_fromw_branch->SetAddress(&wis_fromw_);
	}
	wcharge_branch = 0;
	if (tree->GetBranch("wcharge") != 0) {
		wcharge_branch = tree->GetBranch("wcharge");
		wcharge_branch->SetAddress(&wcharge_);
	}
	wpdgid_branch = 0;
	if (tree->GetBranch("wpdgid") != 0) {
		wpdgid_branch = tree->GetBranch("wpdgid");
		wpdgid_branch->SetAddress(&wpdgid_);
	}
	wtype_branch = 0;
	if (tree->GetBranch("wtype") != 0) {
		wtype_branch = tree->GetBranch("wtype");
		wtype_branch->SetAddress(&wtype_);
	}
	wd0_branch = 0;
	if (tree->GetBranch("wd0") != 0) {
		wd0_branch = tree->GetBranch("wd0");
		wd0_branch->SetAddress(&wd0_);
	}
	wdz_branch = 0;
	if (tree->GetBranch("wdz") != 0) {
		wdz_branch = tree->GetBranch("wdz");
		wdz_branch->SetAddress(&wdz_);
	}
	wmt_branch = 0;
	if (tree->GetBranch("wmt") != 0) {
		wmt_branch = tree->GetBranch("wmt");
		wmt_branch->SetAddress(&wmt_);
	}
	wcorpfiso_branch = 0;
	if (tree->GetBranch("wcorpfiso") != 0) {
		wcorpfiso_branch = tree->GetBranch("wcorpfiso");
		wcorpfiso_branch->SetAddress(&wcorpfiso_);
	}
	wpfiso_branch = 0;
	if (tree->GetBranch("wpfiso") != 0) {
		wpfiso_branch = tree->GetBranch("wpfiso");
		wpfiso_branch->SetAddress(&wpfiso_);
	}
	wchiso_branch = 0;
	if (tree->GetBranch("wchiso") != 0) {
		wchiso_branch = tree->GetBranch("wchiso");
		wchiso_branch->SetAddress(&wchiso_);
	}
	wemiso_branch = 0;
	if (tree->GetBranch("wemiso") != 0) {
		wemiso_branch = tree->GetBranch("wemiso");
		wemiso_branch->SetAddress(&wemiso_);
	}
	wnhiso_branch = 0;
	if (tree->GetBranch("wnhiso") != 0) {
		wnhiso_branch = tree->GetBranch("wnhiso");
		wnhiso_branch->SetAddress(&wnhiso_);
	}
	wcorpfiso04_branch = 0;
	if (tree->GetBranch("wcorpfiso04") != 0) {
		wcorpfiso04_branch = tree->GetBranch("wcorpfiso04");
		wcorpfiso04_branch->SetAddress(&wcorpfiso04_);
	}
	wpfiso04_branch = 0;
	if (tree->GetBranch("wpfiso04") != 0) {
		wpfiso04_branch = tree->GetBranch("wpfiso04");
		wpfiso04_branch->SetAddress(&wpfiso04_);
	}
	wchiso04_branch = 0;
	if (tree->GetBranch("wchiso04") != 0) {
		wchiso04_branch = tree->GetBranch("wchiso04");
		wchiso04_branch->SetAddress(&wchiso04_);
	}
	wemiso04_branch = 0;
	if (tree->GetBranch("wemiso04") != 0) {
		wemiso04_branch = tree->GetBranch("wemiso04");
		wemiso04_branch->SetAddress(&wemiso04_);
	}
	wnhiso04_branch = 0;
	if (tree->GetBranch("wnhiso04") != 0) {
		wnhiso04_branch = tree->GetBranch("wnhiso04");
		wnhiso04_branch->SetAddress(&wnhiso04_);
	}
	wcordetiso_branch = 0;
	if (tree->GetBranch("wcordetiso") != 0) {
		wcordetiso_branch = tree->GetBranch("wcordetiso");
		wcordetiso_branch->SetAddress(&wcordetiso_);
	}
	wdetiso_branch = 0;
	if (tree->GetBranch("wdetiso") != 0) {
		wdetiso_branch = tree->GetBranch("wdetiso");
		wdetiso_branch->SetAddress(&wdetiso_);
	}
	wtrkiso_branch = 0;
	if (tree->GetBranch("wtrkiso") != 0) {
		wtrkiso_branch = tree->GetBranch("wtrkiso");
		wtrkiso_branch->SetAddress(&wtrkiso_);
	}
	wecaliso_branch = 0;
	if (tree->GetBranch("wecaliso") != 0) {
		wecaliso_branch = tree->GetBranch("wecaliso");
		wecaliso_branch->SetAddress(&wecaliso_);
	}
	whcaliso_branch = 0;
	if (tree->GetBranch("whcaliso") != 0) {
		whcaliso_branch = tree->GetBranch("whcaliso");
		whcaliso_branch->SetAddress(&whcaliso_);
	}
	wcordetiso04_branch = 0;
	if (tree->GetBranch("wcordetiso04") != 0) {
		wcordetiso04_branch = tree->GetBranch("wcordetiso04");
		wcordetiso04_branch->SetAddress(&wcordetiso04_);
	}
	wdetiso04_branch = 0;
	if (tree->GetBranch("wdetiso04") != 0) {
		wdetiso04_branch = tree->GetBranch("wdetiso04");
		wdetiso04_branch->SetAddress(&wdetiso04_);
	}
	wtrkiso04_branch = 0;
	if (tree->GetBranch("wtrkiso04") != 0) {
		wtrkiso04_branch = tree->GetBranch("wtrkiso04");
		wtrkiso04_branch->SetAddress(&wtrkiso04_);
	}
	wecaliso04_branch = 0;
	if (tree->GetBranch("wecaliso04") != 0) {
		wecaliso04_branch = tree->GetBranch("wecaliso04");
		wecaliso04_branch->SetAddress(&wecaliso04_);
	}
	whcaliso04_branch = 0;
	if (tree->GetBranch("whcaliso04") != 0) {
		whcaliso04_branch = tree->GetBranch("whcaliso04");
		whcaliso04_branch->SetAddress(&whcaliso04_);
	}
	weffarea_branch = 0;
	if (tree->GetBranch("weffarea") != 0) {
		weffarea_branch = tree->GetBranch("weffarea");
		weffarea_branch->SetAddress(&weffarea_);
	}
	weffarea04_branch = 0;
	if (tree->GetBranch("weffarea04") != 0) {
		weffarea04_branch = tree->GetBranch("weffarea04");
		weffarea04_branch->SetAddress(&weffarea04_);
	}
	wdbeta_branch = 0;
	if (tree->GetBranch("wdbeta") != 0) {
		wdbeta_branch = tree->GetBranch("wdbeta");
		wdbeta_branch->SetAddress(&wdbeta_);
	}
	wdbeta04_branch = 0;
	if (tree->GetBranch("wdbeta04") != 0) {
		wdbeta04_branch = tree->GetBranch("wdbeta04");
		wdbeta04_branch->SetAddress(&wdbeta04_);
	}
	wsf_lepeff_branch = 0;
	if (tree->GetBranch("wsf_lepeff") != 0) {
		wsf_lepeff_branch = tree->GetBranch("wsf_lepeff");
		wsf_lepeff_branch->SetAddress(&wsf_lepeff_);
	}
	wsf_trig_branch = 0;
	if (tree->GetBranch("wsf_trig") != 0) {
		wsf_trig_branch = tree->GetBranch("wsf_trig");
		wsf_trig_branch->SetAddress(&wsf_trig_);
	}
	wmcid_branch = 0;
	if (tree->GetBranch("wmcid") != 0) {
		wmcid_branch = tree->GetBranch("wmcid");
		wmcid_branch->SetAddress(&wmcid_);
	}
	wmc3id_branch = 0;
	if (tree->GetBranch("wmc3id") != 0) {
		wmc3id_branch = tree->GetBranch("wmc3id");
		wmc3id_branch->SetAddress(&wmc3id_);
	}
	wmomid_branch = 0;
	if (tree->GetBranch("wmomid") != 0) {
		wmomid_branch = tree->GetBranch("wmomid");
		wmomid_branch->SetAddress(&wmomid_);
	}
	wmc3_momid_branch = 0;
	if (tree->GetBranch("wmc3_momid") != 0) {
		wmc3_momid_branch = tree->GetBranch("wmc3_momid");
		wmc3_momid_branch->SetAddress(&wmc3_momid_);
	}
	wq3agree_branch = 0;
	if (tree->GetBranch("wq3agree") != 0) {
		wq3agree_branch = tree->GetBranch("wq3agree");
		wq3agree_branch->SetAddress(&wq3agree_);
	}
	wis_conv_branch = 0;
	if (tree->GetBranch("wis_conv") != 0) {
		wis_conv_branch = tree->GetBranch("wis_conv");
		wis_conv_branch->SetAddress(&wis_conv_);
	}
	wqsc_branch = 0;
	if (tree->GetBranch("wqsc") != 0) {
		wqsc_branch = tree->GetBranch("wqsc");
		wqsc_branch->SetAddress(&wqsc_);
	}
	wqctf_branch = 0;
	if (tree->GetBranch("wqctf") != 0) {
		wqctf_branch = tree->GetBranch("wqctf");
		wqctf_branch->SetAddress(&wqctf_);
	}
	wqgsf_branch = 0;
	if (tree->GetBranch("wqgsf") != 0) {
		wqgsf_branch = tree->GetBranch("wqgsf");
		wqgsf_branch->SetAddress(&wqgsf_);
	}
	wnmhits_branch = 0;
	if (tree->GetBranch("wnmhits") != 0) {
		wnmhits_branch = tree->GetBranch("wnmhits");
		wnmhits_branch->SetAddress(&wnmhits_);
	}
	weleid_veto_branch = 0;
	if (tree->GetBranch("weleid_veto") != 0) {
		weleid_veto_branch = tree->GetBranch("weleid_veto");
		weleid_veto_branch->SetAddress(&weleid_veto_);
	}
	weleid_loose_branch = 0;
	if (tree->GetBranch("weleid_loose") != 0) {
		weleid_loose_branch = tree->GetBranch("weleid_loose");
		weleid_loose_branch->SetAddress(&weleid_loose_);
	}
	weleid_medium_branch = 0;
	if (tree->GetBranch("weleid_medium") != 0) {
		weleid_medium_branch = tree->GetBranch("weleid_medium");
		weleid_medium_branch->SetAddress(&weleid_medium_);
	}
	weleid_tight_branch = 0;
	if (tree->GetBranch("weleid_tight") != 0) {
		weleid_tight_branch = tree->GetBranch("weleid_tight");
		weleid_tight_branch->SetAddress(&weleid_tight_);
	}
	wdphiin_branch = 0;
	if (tree->GetBranch("wdphiin") != 0) {
		wdphiin_branch = tree->GetBranch("wdphiin");
		wdphiin_branch->SetAddress(&wdphiin_);
	}
	wdetain_branch = 0;
	if (tree->GetBranch("wdetain") != 0) {
		wdetain_branch = tree->GetBranch("wdetain");
		wdetain_branch->SetAddress(&wdetain_);
	}
	wsieie_branch = 0;
	if (tree->GetBranch("wsieie") != 0) {
		wsieie_branch = tree->GetBranch("wsieie");
		wsieie_branch->SetAddress(&wsieie_);
	}
	whoe_branch = 0;
	if (tree->GetBranch("whoe") != 0) {
		whoe_branch = tree->GetBranch("whoe");
		whoe_branch->SetAddress(&whoe_);
	}
	wooemoop_branch = 0;
	if (tree->GetBranch("wooemoop") != 0) {
		wooemoop_branch = tree->GetBranch("wooemoop");
		wooemoop_branch->SetAddress(&wooemoop_);
	}
	wconv_dist_branch = 0;
	if (tree->GetBranch("wconv_dist") != 0) {
		wconv_dist_branch = tree->GetBranch("wconv_dist");
		wconv_dist_branch->SetAddress(&wconv_dist_);
	}
	wconv_dcot_branch = 0;
	if (tree->GetBranch("wconv_dcot") != 0) {
		wconv_dcot_branch = tree->GetBranch("wconv_dcot");
		wconv_dcot_branch->SetAddress(&wconv_dcot_);
	}
	wis_global_branch = 0;
	if (tree->GetBranch("wis_global") != 0) {
		wis_global_branch = tree->GetBranch("wis_global");
		wis_global_branch->SetAddress(&wis_global_);
	}
	wis_tracker_branch = 0;
	if (tree->GetBranch("wis_tracker") != 0) {
		wis_tracker_branch = tree->GetBranch("wis_tracker");
		wis_tracker_branch->SetAddress(&wis_tracker_);
	}
	wis_stamu_branch = 0;
	if (tree->GetBranch("wis_stamu") != 0) {
		wis_stamu_branch = tree->GetBranch("wis_stamu");
		wis_stamu_branch->SetAddress(&wis_stamu_);
	}
	wis_pfmu_branch = 0;
	if (tree->GetBranch("wis_pfmu") != 0) {
		wis_pfmu_branch = tree->GetBranch("wis_pfmu");
		wis_pfmu_branch->SetAddress(&wis_pfmu_);
	}
	wis_loosemu_branch = 0;
	if (tree->GetBranch("wis_loosemu") != 0) {
		wis_loosemu_branch = tree->GetBranch("wis_loosemu");
		wis_loosemu_branch->SetAddress(&wis_loosemu_);
	}
	wis_tightmu_branch = 0;
	if (tree->GetBranch("wis_tightmu") != 0) {
		wis_tightmu_branch = tree->GetBranch("wis_tightmu");
		wis_tightmu_branch->SetAddress(&wis_tightmu_);
	}
	wnpixelhits_branch = 0;
	if (tree->GetBranch("wnpixelhits") != 0) {
		wnpixelhits_branch = tree->GetBranch("wnpixelhits");
		wnpixelhits_branch->SetAddress(&wnpixelhits_);
	}
	wnsihits_branch = 0;
	if (tree->GetBranch("wnsihits") != 0) {
		wnsihits_branch = tree->GetBranch("wnsihits");
		wnsihits_branch->SetAddress(&wnsihits_);
	}
	wnsilayers_branch = 0;
	if (tree->GetBranch("wnsilayers") != 0) {
		wnsilayers_branch = tree->GetBranch("wnsilayers");
		wnsilayers_branch->SetAddress(&wnsilayers_);
	}
	wnstahits_branch = 0;
	if (tree->GetBranch("wnstahits") != 0) {
		wnstahits_branch = tree->GetBranch("wnstahits");
		wnstahits_branch->SetAddress(&wnstahits_);
	}
	wnstations_branch = 0;
	if (tree->GetBranch("wnstations") != 0) {
		wnstations_branch = tree->GetBranch("wnstations");
		wnstations_branch->SetAddress(&wnstations_);
	}
	wchi2_branch = 0;
	if (tree->GetBranch("wchi2") != 0) {
		wchi2_branch = tree->GetBranch("wchi2");
		wchi2_branch->SetAddress(&wchi2_);
	}
	wndof_branch = 0;
	if (tree->GetBranch("wndof") != 0) {
		wndof_branch = tree->GetBranch("wndof");
		wndof_branch->SetAddress(&wndof_);
	}
	wpterr_branch = 0;
	if (tree->GetBranch("wpterr") != 0) {
		wpterr_branch = tree->GetBranch("wpterr");
		wpterr_branch->SetAddress(&wpterr_);
	}
	wecal_vetodep_branch = 0;
	if (tree->GetBranch("wecal_vetodep") != 0) {
		wecal_vetodep_branch = tree->GetBranch("wecal_vetodep");
		wecal_vetodep_branch->SetAddress(&wecal_vetodep_);
	}
	whcal_vetodep_branch = 0;
	if (tree->GetBranch("whcal_vetodep") != 0) {
		whcal_vetodep_branch = tree->GetBranch("whcal_vetodep");
		whcal_vetodep_branch->SetAddress(&whcal_vetodep_);
	}
	selection_branch = 0;
	if (tree->GetBranch("selection") != 0) {
		selection_branch = tree->GetBranch("selection");
		selection_branch->SetAddress(&selection_);
	}
	clean_branch = 0;
	if (tree->GetBranch("clean") != 0) {
		clean_branch = tree->GetBranch("clean");
		clean_branch->SetAddress(&clean_);
	}
	is_good_lumi_branch = 0;
	if (tree->GetBranch("is_good_lumi") != 0) {
		is_good_lumi_branch = tree->GetBranch("is_good_lumi");
		is_good_lumi_branch->SetAddress(&is_good_lumi_);
	}
	njets15_branch = 0;
	if (tree->GetBranch("njets15") != 0) {
		njets15_branch = tree->GetBranch("njets15");
		njets15_branch->SetAddress(&njets15_);
	}
	njets30_branch = 0;
	if (tree->GetBranch("njets30") != 0) {
		njets30_branch = tree->GetBranch("njets30");
		njets30_branch->SetAddress(&njets30_);
	}
	nbtags_loose_branch = 0;
	if (tree->GetBranch("nbtags_loose") != 0) {
		nbtags_loose_branch = tree->GetBranch("nbtags_loose");
		nbtags_loose_branch->SetAddress(&nbtags_loose_);
	}
	nbtags_tight_branch = 0;
	if (tree->GetBranch("nbtags_tight") != 0) {
		nbtags_tight_branch = tree->GetBranch("nbtags_tight");
		nbtags_tight_branch->SetAddress(&nbtags_tight_);
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
	event_type_branch = 0;
	if (tree->GetBranch("event_type") != 0) {
		event_type_branch = tree->GetBranch("event_type");
		event_type_branch->SetAddress(&event_type_);
	}
	njets30_dn_branch = 0;
	if (tree->GetBranch("njets30_dn") != 0) {
		njets30_dn_branch = tree->GetBranch("njets30_dn");
		njets30_dn_branch->SetAddress(&njets30_dn_);
	}
	njets30_up_branch = 0;
	if (tree->GetBranch("njets30_up") != 0) {
		njets30_up_branch = tree->GetBranch("njets30_up");
		njets30_up_branch->SetAddress(&njets30_up_);
	}
	njets15_dn_branch = 0;
	if (tree->GetBranch("njets15_dn") != 0) {
		njets15_dn_branch = tree->GetBranch("njets15_dn");
		njets15_dn_branch->SetAddress(&njets15_dn_);
	}
	njets15_up_branch = 0;
	if (tree->GetBranch("njets15_up") != 0) {
		njets15_up_branch = tree->GetBranch("njets15_up");
		njets15_up_branch->SetAddress(&njets15_up_);
	}
	nbtags_loose_dn_branch = 0;
	if (tree->GetBranch("nbtags_loose_dn") != 0) {
		nbtags_loose_dn_branch = tree->GetBranch("nbtags_loose_dn");
		nbtags_loose_dn_branch->SetAddress(&nbtags_loose_dn_);
	}
	nbtags_loose_up_branch = 0;
	if (tree->GetBranch("nbtags_loose_up") != 0) {
		nbtags_loose_up_branch = tree->GetBranch("nbtags_loose_up");
		nbtags_loose_up_branch->SetAddress(&nbtags_loose_up_);
	}
	ht_dn_branch = 0;
	if (tree->GetBranch("ht_dn") != 0) {
		ht_dn_branch = tree->GetBranch("ht_dn");
		ht_dn_branch->SetAddress(&ht_dn_);
	}
	ht_up_branch = 0;
	if (tree->GetBranch("ht_up") != 0) {
		ht_up_branch = tree->GetBranch("ht_up");
		ht_up_branch->SetAddress(&ht_up_);
	}
	pfmet_dn_branch = 0;
	if (tree->GetBranch("pfmet_dn") != 0) {
		pfmet_dn_branch = tree->GetBranch("pfmet_dn");
		pfmet_dn_branch->SetAddress(&pfmet_dn_);
	}
	pfmet_up_branch = 0;
	if (tree->GetBranch("pfmet_up") != 0) {
		pfmet_up_branch = tree->GetBranch("pfmet_up");
		pfmet_up_branch->SetAddress(&pfmet_up_);
	}
	pfmet_phi_dn_branch = 0;
	if (tree->GetBranch("pfmet_phi_dn") != 0) {
		pfmet_phi_dn_branch = tree->GetBranch("pfmet_phi_dn");
		pfmet_phi_dn_branch->SetAddress(&pfmet_phi_dn_);
	}
	pfmet_phi_up_branch = 0;
	if (tree->GetBranch("pfmet_phi_up") != 0) {
		pfmet_phi_up_branch = tree->GetBranch("pfmet_phi_up");
		pfmet_phi_up_branch->SetAddress(&pfmet_phi_up_);
	}
	lep1_wfr_branch = 0;
	if (tree->GetBranch("lep1_wfr") != 0) {
		lep1_wfr_branch = tree->GetBranch("lep1_wfr");
		lep1_wfr_branch->SetAddress(&lep1_wfr_);
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
	lep1_nearlep_dr_branch = 0;
	if (tree->GetBranch("lep1_nearlep_dr") != 0) {
		lep1_nearlep_dr_branch = tree->GetBranch("lep1_nearlep_dr");
		lep1_nearlep_dr_branch->SetAddress(&lep1_nearlep_dr_);
	}
	lep1_nearlep_id_branch = 0;
	if (tree->GetBranch("lep1_nearlep_id") != 0) {
		lep1_nearlep_id_branch = tree->GetBranch("lep1_nearlep_id");
		lep1_nearlep_id_branch->SetAddress(&lep1_nearlep_id_);
	}
	lep1_passes_id_bitmask_branch = 0;
	if (tree->GetBranch("lep1_passes_id_bitmask") != 0) {
		lep1_passes_id_bitmask_branch = tree->GetBranch("lep1_passes_id_bitmask");
		lep1_passes_id_bitmask_branch->SetAddress(&lep1_passes_id_bitmask_);
	}
	lep2_wfr_branch = 0;
	if (tree->GetBranch("lep2_wfr") != 0) {
		lep2_wfr_branch = tree->GetBranch("lep2_wfr");
		lep2_wfr_branch->SetAddress(&lep2_wfr_);
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
	lep2_nearlep_dr_branch = 0;
	if (tree->GetBranch("lep2_nearlep_dr") != 0) {
		lep2_nearlep_dr_branch = tree->GetBranch("lep2_nearlep_dr");
		lep2_nearlep_dr_branch->SetAddress(&lep2_nearlep_dr_);
	}
	lep2_nearlep_id_branch = 0;
	if (tree->GetBranch("lep2_nearlep_id") != 0) {
		lep2_nearlep_id_branch = tree->GetBranch("lep2_nearlep_id");
		lep2_nearlep_id_branch->SetAddress(&lep2_nearlep_id_);
	}
	lep2_passes_id_bitmask_branch = 0;
	if (tree->GetBranch("lep2_passes_id_bitmask") != 0) {
		lep2_passes_id_bitmask_branch = tree->GetBranch("lep2_passes_id_bitmask");
		lep2_passes_id_bitmask_branch->SetAddress(&lep2_passes_id_bitmask_);
	}
	lep3_wfr_branch = 0;
	if (tree->GetBranch("lep3_wfr") != 0) {
		lep3_wfr_branch = tree->GetBranch("lep3_wfr");
		lep3_wfr_branch->SetAddress(&lep3_wfr_);
	}
	lep3_nearbjet_dr_branch = 0;
	if (tree->GetBranch("lep3_nearbjet_dr") != 0) {
		lep3_nearbjet_dr_branch = tree->GetBranch("lep3_nearbjet_dr");
		lep3_nearbjet_dr_branch->SetAddress(&lep3_nearbjet_dr_);
	}
	lep3_nearjet_dr_branch = 0;
	if (tree->GetBranch("lep3_nearjet_dr") != 0) {
		lep3_nearjet_dr_branch = tree->GetBranch("lep3_nearjet_dr");
		lep3_nearjet_dr_branch->SetAddress(&lep3_nearjet_dr_);
	}
	lep3_nearlep_dr_branch = 0;
	if (tree->GetBranch("lep3_nearlep_dr") != 0) {
		lep3_nearlep_dr_branch = tree->GetBranch("lep3_nearlep_dr");
		lep3_nearlep_dr_branch->SetAddress(&lep3_nearlep_dr_);
	}
	lep3_nearlep_id_branch = 0;
	if (tree->GetBranch("lep3_nearlep_id") != 0) {
		lep3_nearlep_id_branch = tree->GetBranch("lep3_nearlep_id");
		lep3_nearlep_id_branch->SetAddress(&lep3_nearlep_id_);
	}
	lep3_passes_id_bitmask_branch = 0;
	if (tree->GetBranch("lep3_passes_id_bitmask") != 0) {
		lep3_passes_id_bitmask_branch = tree->GetBranch("lep3_passes_id_bitmask");
		lep3_passes_id_bitmask_branch->SetAddress(&lep3_passes_id_bitmask_);
	}
	is_gen_z_branch = 0;
	if (tree->GetBranch("is_gen_z") != 0) {
		is_gen_z_branch = tree->GetBranch("is_gen_z");
		is_gen_z_branch->SetAddress(&is_gen_z_);
	}
	is_gen_w_branch = 0;
	if (tree->GetBranch("is_gen_w") != 0) {
		is_gen_w_branch = tree->GetBranch("is_gen_w");
		is_gen_w_branch->SetAddress(&is_gen_w_);
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
	gen_nleps_branch = 0;
	if (tree->GetBranch("gen_nleps") != 0) {
		gen_nleps_branch = tree->GetBranch("gen_nleps");
		gen_nleps_branch->SetAddress(&gen_nleps_);
	}
	sf_nbtag_branch = 0;
	if (tree->GetBranch("sf_nbtag") != 0) {
		sf_nbtag_branch = tree->GetBranch("sf_nbtag");
		sf_nbtag_branch->SetAddress(&sf_nbtag_);
	}
	sf_nbtag2_branch = 0;
	if (tree->GetBranch("sf_nbtag2") != 0) {
		sf_nbtag2_branch = tree->GetBranch("sf_nbtag2");
		sf_nbtag2_branch->SetAddress(&sf_nbtag2_);
	}
	sf_unc_nbtag_branch = 0;
	if (tree->GetBranch("sf_unc_nbtag") != 0) {
		sf_unc_nbtag_branch = tree->GetBranch("sf_unc_nbtag");
		sf_unc_nbtag_branch->SetAddress(&sf_unc_nbtag_);
	}
	sf_unc_nbtag2_branch = 0;
	if (tree->GetBranch("sf_unc_nbtag2") != 0) {
		sf_unc_nbtag2_branch = tree->GetBranch("sf_unc_nbtag2");
		sf_unc_nbtag2_branch->SetAddress(&sf_unc_nbtag2_);
	}
	bjets_dr12_branch = 0;
	if (tree->GetBranch("bjets_dr12") != 0) {
		bjets_dr12_branch = tree->GetBranch("bjets_dr12");
		bjets_dr12_branch->SetAddress(&bjets_dr12_);
	}
	vbtags_loose_branch = 0;
	if (tree->GetBranch("vbtags_loose") != 0) {
		vbtags_loose_branch = tree->GetBranch("vbtags_loose");
		vbtags_loose_branch->SetAddress(&vbtags_loose_);
	}
	vbtags_tight_branch = 0;
	if (tree->GetBranch("vbtags_tight") != 0) {
		vbtags_tight_branch = tree->GetBranch("vbtags_tight");
		vbtags_tight_branch->SetAddress(&vbtags_tight_);
	}
	vbjets_disc_branch = 0;
	if (tree->GetBranch("vbjets_disc") != 0) {
		vbjets_disc_branch = tree->GetBranch("vbjets_disc");
		vbjets_disc_branch->SetAddress(&vbjets_disc_);
	}
	gen_lep1_pdgid_branch = 0;
	if (tree->GetBranch("gen_lep1_pdgid") != 0) {
		gen_lep1_pdgid_branch = tree->GetBranch("gen_lep1_pdgid");
		gen_lep1_pdgid_branch->SetAddress(&gen_lep1_pdgid_);
	}
	gen_lep2_pdgid_branch = 0;
	if (tree->GetBranch("gen_lep2_pdgid") != 0) {
		gen_lep2_pdgid_branch = tree->GetBranch("gen_lep2_pdgid");
		gen_lep2_pdgid_branch->SetAddress(&gen_lep2_pdgid_);
	}
	gen_mt_branch = 0;
	if (tree->GetBranch("gen_mt") != 0) {
		gen_mt_branch = tree->GetBranch("gen_mt");
		gen_mt_branch->SetAddress(&gen_mt_);
	}
	gen_lep3_pdgid_branch = 0;
	if (tree->GetBranch("gen_lep3_pdgid") != 0) {
		gen_lep3_pdgid_branch = tree->GetBranch("gen_lep3_pdgid");
		gen_lep3_pdgid_branch->SetAddress(&gen_lep3_pdgid_);
	}
	gen_dilep_type_branch = 0;
	if (tree->GetBranch("gen_dilep_type") != 0) {
		gen_dilep_type_branch = tree->GetBranch("gen_dilep_type");
		gen_dilep_type_branch->SetAddress(&gen_dilep_type_);
	}
	gen_dilep_mass_branch = 0;
	if (tree->GetBranch("gen_dilep_mass") != 0) {
		gen_dilep_mass_branch = tree->GetBranch("gen_dilep_mass");
		gen_dilep_mass_branch->SetAddress(&gen_dilep_mass_);
	}
	gen_dilep_dphi_branch = 0;
	if (tree->GetBranch("gen_dilep_dphi") != 0) {
		gen_dilep_dphi_branch = tree->GetBranch("gen_dilep_dphi");
		gen_dilep_dphi_branch->SetAddress(&gen_dilep_dphi_);
	}
	gen_dilep_deta_branch = 0;
	if (tree->GetBranch("gen_dilep_deta") != 0) {
		gen_dilep_deta_branch = tree->GetBranch("gen_dilep_deta");
		gen_dilep_deta_branch->SetAddress(&gen_dilep_deta_);
	}
	gen_dilep_dr_branch = 0;
	if (tree->GetBranch("gen_dilep_dr") != 0) {
		gen_dilep_dr_branch = tree->GetBranch("gen_dilep_dr");
		gen_dilep_dr_branch->SetAddress(&gen_dilep_dr_);
	}
	lep1_ele_mva_trig_branch = 0;
	if (tree->GetBranch("lep1_ele_mva_trig") != 0) {
		lep1_ele_mva_trig_branch = tree->GetBranch("lep1_ele_mva_trig");
		lep1_ele_mva_trig_branch->SetAddress(&lep1_ele_mva_trig_);
	}
	lep2_ele_mva_trig_branch = 0;
	if (tree->GetBranch("lep2_ele_mva_trig") != 0) {
		lep2_ele_mva_trig_branch = tree->GetBranch("lep2_ele_mva_trig");
		lep2_ele_mva_trig_branch->SetAddress(&lep2_ele_mva_trig_);
	}
	lep3_ele_mva_trig_branch = 0;
	if (tree->GetBranch("lep3_ele_mva_trig") != 0) {
		lep3_ele_mva_trig_branch = tree->GetBranch("lep3_ele_mva_trig");
		lep3_ele_mva_trig_branch->SetAddress(&lep3_ele_mva_trig_);
	}
	lep1_ele_mva_nontrig_branch = 0;
	if (tree->GetBranch("lep1_ele_mva_nontrig") != 0) {
		lep1_ele_mva_nontrig_branch = tree->GetBranch("lep1_ele_mva_nontrig");
		lep1_ele_mva_nontrig_branch->SetAddress(&lep1_ele_mva_nontrig_);
	}
	lep2_ele_mva_nontrig_branch = 0;
	if (tree->GetBranch("lep2_ele_mva_nontrig") != 0) {
		lep2_ele_mva_nontrig_branch = tree->GetBranch("lep2_ele_mva_nontrig");
		lep2_ele_mva_nontrig_branch->SetAddress(&lep2_ele_mva_nontrig_);
	}
	lep3_ele_mva_nontrig_branch = 0;
	if (tree->GetBranch("lep3_ele_mva_nontrig") != 0) {
		lep3_ele_mva_nontrig_branch = tree->GetBranch("lep3_ele_mva_nontrig");
		lep3_ele_mva_nontrig_branch->SetAddress(&lep3_ele_mva_nontrig_);
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
		zdilep_p4_isLoaded = false;
		zis_os_isLoaded = false;
		zis_ss_isLoaded = false;
		zdilep_type_isLoaded = false;
		zdilep_gen_type_isLoaded = false;
		zdilep_mass_isLoaded = false;
		zdilep_dphi_isLoaded = false;
		zdilep_deta_isLoaded = false;
		zdilep_dr_isLoaded = false;
		zfiduciality_isLoaded = false;
		wp4_isLoaded = false;
		wpasses_id_isLoaded = false;
		wpasses_iso_isLoaded = false;
		wis_num_isLoaded = false;
		wis_fo_isLoaded = false;
		wis_fromw_isLoaded = false;
		wcharge_isLoaded = false;
		wpdgid_isLoaded = false;
		wtype_isLoaded = false;
		wd0_isLoaded = false;
		wdz_isLoaded = false;
		wmt_isLoaded = false;
		wcorpfiso_isLoaded = false;
		wpfiso_isLoaded = false;
		wchiso_isLoaded = false;
		wemiso_isLoaded = false;
		wnhiso_isLoaded = false;
		wcorpfiso04_isLoaded = false;
		wpfiso04_isLoaded = false;
		wchiso04_isLoaded = false;
		wemiso04_isLoaded = false;
		wnhiso04_isLoaded = false;
		wcordetiso_isLoaded = false;
		wdetiso_isLoaded = false;
		wtrkiso_isLoaded = false;
		wecaliso_isLoaded = false;
		whcaliso_isLoaded = false;
		wcordetiso04_isLoaded = false;
		wdetiso04_isLoaded = false;
		wtrkiso04_isLoaded = false;
		wecaliso04_isLoaded = false;
		whcaliso04_isLoaded = false;
		weffarea_isLoaded = false;
		weffarea04_isLoaded = false;
		wdbeta_isLoaded = false;
		wdbeta04_isLoaded = false;
		wsf_lepeff_isLoaded = false;
		wsf_trig_isLoaded = false;
		wmcp4_isLoaded = false;
		wmc3p4_isLoaded = false;
		wmc_momp4_isLoaded = false;
		wmcid_isLoaded = false;
		wmc3id_isLoaded = false;
		wmomid_isLoaded = false;
		wmc3_momid_isLoaded = false;
		wgsf_p4_isLoaded = false;
		wctf_p4_isLoaded = false;
		wsc_p4_isLoaded = false;
		wq3agree_isLoaded = false;
		wis_conv_isLoaded = false;
		wqsc_isLoaded = false;
		wqctf_isLoaded = false;
		wqgsf_isLoaded = false;
		wnmhits_isLoaded = false;
		weleid_veto_isLoaded = false;
		weleid_loose_isLoaded = false;
		weleid_medium_isLoaded = false;
		weleid_tight_isLoaded = false;
		wdphiin_isLoaded = false;
		wdetain_isLoaded = false;
		wsieie_isLoaded = false;
		whoe_isLoaded = false;
		wooemoop_isLoaded = false;
		wconv_dist_isLoaded = false;
		wconv_dcot_isLoaded = false;
		wgfit_p4_isLoaded = false;
		wis_global_isLoaded = false;
		wis_tracker_isLoaded = false;
		wis_stamu_isLoaded = false;
		wis_pfmu_isLoaded = false;
		wis_loosemu_isLoaded = false;
		wis_tightmu_isLoaded = false;
		wnpixelhits_isLoaded = false;
		wnsihits_isLoaded = false;
		wnsilayers_isLoaded = false;
		wnstahits_isLoaded = false;
		wnstations_isLoaded = false;
		wchi2_isLoaded = false;
		wndof_isLoaded = false;
		wpterr_isLoaded = false;
		wecal_vetodep_isLoaded = false;
		whcal_vetodep_isLoaded = false;
		selection_isLoaded = false;
		clean_isLoaded = false;
		is_good_lumi_isLoaded = false;
		njets15_isLoaded = false;
		njets30_isLoaded = false;
		nbtags_loose_isLoaded = false;
		nbtags_tight_isLoaded = false;
		vtxw_isLoaded = false;
		ht_isLoaded = false;
		rho_isLoaded = false;
		rho_iso_isLoaded = false;
		sf_dileptrig_isLoaded = false;
		sf_lepeff_isLoaded = false;
		trig_mm_isLoaded = false;
		trig_em_isLoaded = false;
		trig_ee_isLoaded = false;
		event_type_isLoaded = false;
		njets30_dn_isLoaded = false;
		njets30_up_isLoaded = false;
		njets15_dn_isLoaded = false;
		njets15_up_isLoaded = false;
		nbtags_loose_dn_isLoaded = false;
		nbtags_loose_up_isLoaded = false;
		ht_dn_isLoaded = false;
		ht_up_isLoaded = false;
		pfmet_dn_isLoaded = false;
		pfmet_up_isLoaded = false;
		pfmet_phi_dn_isLoaded = false;
		pfmet_phi_up_isLoaded = false;
		lep1_nearbjet_p4_isLoaded = false;
		lep1_nearjet_p4_isLoaded = false;
		lep1_nearlep_p4_isLoaded = false;
		lep1_wfr_isLoaded = false;
		lep1_nearbjet_dr_isLoaded = false;
		lep1_nearjet_dr_isLoaded = false;
		lep1_nearlep_dr_isLoaded = false;
		lep1_nearlep_id_isLoaded = false;
		lep1_passes_id_bitmask_isLoaded = false;
		lep2_nearbjet_p4_isLoaded = false;
		lep2_nearjet_p4_isLoaded = false;
		lep2_nearlep_p4_isLoaded = false;
		lep2_wfr_isLoaded = false;
		lep2_nearbjet_dr_isLoaded = false;
		lep2_nearjet_dr_isLoaded = false;
		lep2_nearlep_dr_isLoaded = false;
		lep2_nearlep_id_isLoaded = false;
		lep2_passes_id_bitmask_isLoaded = false;
		lep3_nearbjet_p4_isLoaded = false;
		lep3_nearjet_p4_isLoaded = false;
		lep3_nearlep_p4_isLoaded = false;
		lep3_wfr_isLoaded = false;
		lep3_nearbjet_dr_isLoaded = false;
		lep3_nearjet_dr_isLoaded = false;
		lep3_nearlep_dr_isLoaded = false;
		lep3_nearlep_id_isLoaded = false;
		lep3_passes_id_bitmask_isLoaded = false;
		is_gen_z_isLoaded = false;
		is_gen_w_isLoaded = false;
		gen_nbtags_isLoaded = false;
		gen_njets_isLoaded = false;
		gen_ht_isLoaded = false;
		gen_nleps_isLoaded = false;
		sf_nbtag_isLoaded = false;
		sf_nbtag2_isLoaded = false;
		sf_unc_nbtag_isLoaded = false;
		sf_unc_nbtag2_isLoaded = false;
		bjets_dr12_isLoaded = false;
		vgenb_p4_isLoaded = false;
		vjets_p4_isLoaded = false;
		vgenjets_p4_isLoaded = false;
		vbjets_p4_isLoaded = false;
		vbtags_loose_isLoaded = false;
		vbtags_tight_isLoaded = false;
		vbjets_disc_isLoaded = false;
		gen_lep1_p4_isLoaded = false;
		gen_lep1_pdgid_isLoaded = false;
		gen_lep2_p4_isLoaded = false;
		gen_lep2_pdgid_isLoaded = false;
		gen_lep3_p4_isLoaded = false;
		gen_mt_isLoaded = false;
		gen_lep3_pdgid_isLoaded = false;
		gen_dilep_p4_isLoaded = false;
		gen_dilep_type_isLoaded = false;
		gen_dilep_mass_isLoaded = false;
		gen_dilep_dphi_isLoaded = false;
		gen_dilep_deta_isLoaded = false;
		gen_dilep_dr_isLoaded = false;
		lep1_ele_mva_trig_isLoaded = false;
		lep2_ele_mva_trig_isLoaded = false;
		lep3_ele_mva_trig_isLoaded = false;
		lep1_ele_mva_nontrig_isLoaded = false;
		lep2_ele_mva_nontrig_isLoaded = false;
		lep3_ele_mva_nontrig_isLoaded = false;
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
	if (zdilep_p4_branch != 0) zdilep_p4();
	if (zis_os_branch != 0) zis_os();
	if (zis_ss_branch != 0) zis_ss();
	if (zdilep_type_branch != 0) zdilep_type();
	if (zdilep_gen_type_branch != 0) zdilep_gen_type();
	if (zdilep_mass_branch != 0) zdilep_mass();
	if (zdilep_dphi_branch != 0) zdilep_dphi();
	if (zdilep_deta_branch != 0) zdilep_deta();
	if (zdilep_dr_branch != 0) zdilep_dr();
	if (zfiduciality_branch != 0) zfiduciality();
	if (wp4_branch != 0) wp4();
	if (wpasses_id_branch != 0) wpasses_id();
	if (wpasses_iso_branch != 0) wpasses_iso();
	if (wis_num_branch != 0) wis_num();
	if (wis_fo_branch != 0) wis_fo();
	if (wis_fromw_branch != 0) wis_fromw();
	if (wcharge_branch != 0) wcharge();
	if (wpdgid_branch != 0) wpdgid();
	if (wtype_branch != 0) wtype();
	if (wd0_branch != 0) wd0();
	if (wdz_branch != 0) wdz();
	if (wmt_branch != 0) wmt();
	if (wcorpfiso_branch != 0) wcorpfiso();
	if (wpfiso_branch != 0) wpfiso();
	if (wchiso_branch != 0) wchiso();
	if (wemiso_branch != 0) wemiso();
	if (wnhiso_branch != 0) wnhiso();
	if (wcorpfiso04_branch != 0) wcorpfiso04();
	if (wpfiso04_branch != 0) wpfiso04();
	if (wchiso04_branch != 0) wchiso04();
	if (wemiso04_branch != 0) wemiso04();
	if (wnhiso04_branch != 0) wnhiso04();
	if (wcordetiso_branch != 0) wcordetiso();
	if (wdetiso_branch != 0) wdetiso();
	if (wtrkiso_branch != 0) wtrkiso();
	if (wecaliso_branch != 0) wecaliso();
	if (whcaliso_branch != 0) whcaliso();
	if (wcordetiso04_branch != 0) wcordetiso04();
	if (wdetiso04_branch != 0) wdetiso04();
	if (wtrkiso04_branch != 0) wtrkiso04();
	if (wecaliso04_branch != 0) wecaliso04();
	if (whcaliso04_branch != 0) whcaliso04();
	if (weffarea_branch != 0) weffarea();
	if (weffarea04_branch != 0) weffarea04();
	if (wdbeta_branch != 0) wdbeta();
	if (wdbeta04_branch != 0) wdbeta04();
	if (wsf_lepeff_branch != 0) wsf_lepeff();
	if (wsf_trig_branch != 0) wsf_trig();
	if (wmcp4_branch != 0) wmcp4();
	if (wmc3p4_branch != 0) wmc3p4();
	if (wmc_momp4_branch != 0) wmc_momp4();
	if (wmcid_branch != 0) wmcid();
	if (wmc3id_branch != 0) wmc3id();
	if (wmomid_branch != 0) wmomid();
	if (wmc3_momid_branch != 0) wmc3_momid();
	if (wgsf_p4_branch != 0) wgsf_p4();
	if (wctf_p4_branch != 0) wctf_p4();
	if (wsc_p4_branch != 0) wsc_p4();
	if (wq3agree_branch != 0) wq3agree();
	if (wis_conv_branch != 0) wis_conv();
	if (wqsc_branch != 0) wqsc();
	if (wqctf_branch != 0) wqctf();
	if (wqgsf_branch != 0) wqgsf();
	if (wnmhits_branch != 0) wnmhits();
	if (weleid_veto_branch != 0) weleid_veto();
	if (weleid_loose_branch != 0) weleid_loose();
	if (weleid_medium_branch != 0) weleid_medium();
	if (weleid_tight_branch != 0) weleid_tight();
	if (wdphiin_branch != 0) wdphiin();
	if (wdetain_branch != 0) wdetain();
	if (wsieie_branch != 0) wsieie();
	if (whoe_branch != 0) whoe();
	if (wooemoop_branch != 0) wooemoop();
	if (wconv_dist_branch != 0) wconv_dist();
	if (wconv_dcot_branch != 0) wconv_dcot();
	if (wgfit_p4_branch != 0) wgfit_p4();
	if (wis_global_branch != 0) wis_global();
	if (wis_tracker_branch != 0) wis_tracker();
	if (wis_stamu_branch != 0) wis_stamu();
	if (wis_pfmu_branch != 0) wis_pfmu();
	if (wis_loosemu_branch != 0) wis_loosemu();
	if (wis_tightmu_branch != 0) wis_tightmu();
	if (wnpixelhits_branch != 0) wnpixelhits();
	if (wnsihits_branch != 0) wnsihits();
	if (wnsilayers_branch != 0) wnsilayers();
	if (wnstahits_branch != 0) wnstahits();
	if (wnstations_branch != 0) wnstations();
	if (wchi2_branch != 0) wchi2();
	if (wndof_branch != 0) wndof();
	if (wpterr_branch != 0) wpterr();
	if (wecal_vetodep_branch != 0) wecal_vetodep();
	if (whcal_vetodep_branch != 0) whcal_vetodep();
	if (selection_branch != 0) selection();
	if (clean_branch != 0) clean();
	if (is_good_lumi_branch != 0) is_good_lumi();
	if (njets15_branch != 0) njets15();
	if (njets30_branch != 0) njets30();
	if (nbtags_loose_branch != 0) nbtags_loose();
	if (nbtags_tight_branch != 0) nbtags_tight();
	if (vtxw_branch != 0) vtxw();
	if (ht_branch != 0) ht();
	if (rho_branch != 0) rho();
	if (rho_iso_branch != 0) rho_iso();
	if (sf_dileptrig_branch != 0) sf_dileptrig();
	if (sf_lepeff_branch != 0) sf_lepeff();
	if (trig_mm_branch != 0) trig_mm();
	if (trig_em_branch != 0) trig_em();
	if (trig_ee_branch != 0) trig_ee();
	if (event_type_branch != 0) event_type();
	if (njets30_dn_branch != 0) njets30_dn();
	if (njets30_up_branch != 0) njets30_up();
	if (njets15_dn_branch != 0) njets15_dn();
	if (njets15_up_branch != 0) njets15_up();
	if (nbtags_loose_dn_branch != 0) nbtags_loose_dn();
	if (nbtags_loose_up_branch != 0) nbtags_loose_up();
	if (ht_dn_branch != 0) ht_dn();
	if (ht_up_branch != 0) ht_up();
	if (pfmet_dn_branch != 0) pfmet_dn();
	if (pfmet_up_branch != 0) pfmet_up();
	if (pfmet_phi_dn_branch != 0) pfmet_phi_dn();
	if (pfmet_phi_up_branch != 0) pfmet_phi_up();
	if (lep1_nearbjet_p4_branch != 0) lep1_nearbjet_p4();
	if (lep1_nearjet_p4_branch != 0) lep1_nearjet_p4();
	if (lep1_nearlep_p4_branch != 0) lep1_nearlep_p4();
	if (lep1_wfr_branch != 0) lep1_wfr();
	if (lep1_nearbjet_dr_branch != 0) lep1_nearbjet_dr();
	if (lep1_nearjet_dr_branch != 0) lep1_nearjet_dr();
	if (lep1_nearlep_dr_branch != 0) lep1_nearlep_dr();
	if (lep1_nearlep_id_branch != 0) lep1_nearlep_id();
	if (lep1_passes_id_bitmask_branch != 0) lep1_passes_id_bitmask();
	if (lep2_nearbjet_p4_branch != 0) lep2_nearbjet_p4();
	if (lep2_nearjet_p4_branch != 0) lep2_nearjet_p4();
	if (lep2_nearlep_p4_branch != 0) lep2_nearlep_p4();
	if (lep2_wfr_branch != 0) lep2_wfr();
	if (lep2_nearbjet_dr_branch != 0) lep2_nearbjet_dr();
	if (lep2_nearjet_dr_branch != 0) lep2_nearjet_dr();
	if (lep2_nearlep_dr_branch != 0) lep2_nearlep_dr();
	if (lep2_nearlep_id_branch != 0) lep2_nearlep_id();
	if (lep2_passes_id_bitmask_branch != 0) lep2_passes_id_bitmask();
	if (lep3_nearbjet_p4_branch != 0) lep3_nearbjet_p4();
	if (lep3_nearjet_p4_branch != 0) lep3_nearjet_p4();
	if (lep3_nearlep_p4_branch != 0) lep3_nearlep_p4();
	if (lep3_wfr_branch != 0) lep3_wfr();
	if (lep3_nearbjet_dr_branch != 0) lep3_nearbjet_dr();
	if (lep3_nearjet_dr_branch != 0) lep3_nearjet_dr();
	if (lep3_nearlep_dr_branch != 0) lep3_nearlep_dr();
	if (lep3_nearlep_id_branch != 0) lep3_nearlep_id();
	if (lep3_passes_id_bitmask_branch != 0) lep3_passes_id_bitmask();
	if (is_gen_z_branch != 0) is_gen_z();
	if (is_gen_w_branch != 0) is_gen_w();
	if (gen_nbtags_branch != 0) gen_nbtags();
	if (gen_njets_branch != 0) gen_njets();
	if (gen_ht_branch != 0) gen_ht();
	if (gen_nleps_branch != 0) gen_nleps();
	if (sf_nbtag_branch != 0) sf_nbtag();
	if (sf_nbtag2_branch != 0) sf_nbtag2();
	if (sf_unc_nbtag_branch != 0) sf_unc_nbtag();
	if (sf_unc_nbtag2_branch != 0) sf_unc_nbtag2();
	if (bjets_dr12_branch != 0) bjets_dr12();
	if (vgenb_p4_branch != 0) vgenb_p4();
	if (vjets_p4_branch != 0) vjets_p4();
	if (vgenjets_p4_branch != 0) vgenjets_p4();
	if (vbjets_p4_branch != 0) vbjets_p4();
	if (vbtags_loose_branch != 0) vbtags_loose();
	if (vbtags_tight_branch != 0) vbtags_tight();
	if (vbjets_disc_branch != 0) vbjets_disc();
	if (gen_lep1_p4_branch != 0) gen_lep1_p4();
	if (gen_lep1_pdgid_branch != 0) gen_lep1_pdgid();
	if (gen_lep2_p4_branch != 0) gen_lep2_p4();
	if (gen_lep2_pdgid_branch != 0) gen_lep2_pdgid();
	if (gen_lep3_p4_branch != 0) gen_lep3_p4();
	if (gen_mt_branch != 0) gen_mt();
	if (gen_lep3_pdgid_branch != 0) gen_lep3_pdgid();
	if (gen_dilep_p4_branch != 0) gen_dilep_p4();
	if (gen_dilep_type_branch != 0) gen_dilep_type();
	if (gen_dilep_mass_branch != 0) gen_dilep_mass();
	if (gen_dilep_dphi_branch != 0) gen_dilep_dphi();
	if (gen_dilep_deta_branch != 0) gen_dilep_deta();
	if (gen_dilep_dr_branch != 0) gen_dilep_dr();
	if (lep1_ele_mva_trig_branch != 0) lep1_ele_mva_trig();
	if (lep2_ele_mva_trig_branch != 0) lep2_ele_mva_trig();
	if (lep3_ele_mva_trig_branch != 0) lep3_ele_mva_trig();
	if (lep1_ele_mva_nontrig_branch != 0) lep1_ele_mva_nontrig();
	if (lep2_ele_mva_nontrig_branch != 0) lep2_ele_mva_nontrig();
	if (lep3_ele_mva_nontrig_branch != 0) lep3_ele_mva_nontrig();
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
		return dataset_;
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
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &zdilep_p4()
	{
		if (not zdilep_p4_isLoaded) {
			if (zdilep_p4_branch != 0) {
				zdilep_p4_branch->GetEntry(index);
			} else { 
				printf("branch zdilep_p4_branch does not exist!\n");
				exit(1);
			}
			zdilep_p4_isLoaded = true;
		}
		return *zdilep_p4_;
	}
	bool &	zis_os()
	{
		if (not zis_os_isLoaded) {
			if (zis_os_branch != 0) {
				zis_os_branch->GetEntry(index);
			} else { 
				printf("branch zis_os_branch does not exist!\n");
				exit(1);
			}
			zis_os_isLoaded = true;
		}
		return zis_os_;
	}
	bool &	zis_ss()
	{
		if (not zis_ss_isLoaded) {
			if (zis_ss_branch != 0) {
				zis_ss_branch->GetEntry(index);
			} else { 
				printf("branch zis_ss_branch does not exist!\n");
				exit(1);
			}
			zis_ss_isLoaded = true;
		}
		return zis_ss_;
	}
	int &zdilep_type()
	{
		if (not zdilep_type_isLoaded) {
			if (zdilep_type_branch != 0) {
				zdilep_type_branch->GetEntry(index);
			} else { 
				printf("branch zdilep_type_branch does not exist!\n");
				exit(1);
			}
			zdilep_type_isLoaded = true;
		}
		return zdilep_type_;
	}
	int &zdilep_gen_type()
	{
		if (not zdilep_gen_type_isLoaded) {
			if (zdilep_gen_type_branch != 0) {
				zdilep_gen_type_branch->GetEntry(index);
			} else { 
				printf("branch zdilep_gen_type_branch does not exist!\n");
				exit(1);
			}
			zdilep_gen_type_isLoaded = true;
		}
		return zdilep_gen_type_;
	}
	float &zdilep_mass()
	{
		if (not zdilep_mass_isLoaded) {
			if (zdilep_mass_branch != 0) {
				zdilep_mass_branch->GetEntry(index);
			} else { 
				printf("branch zdilep_mass_branch does not exist!\n");
				exit(1);
			}
			zdilep_mass_isLoaded = true;
		}
		return zdilep_mass_;
	}
	float &zdilep_dphi()
	{
		if (not zdilep_dphi_isLoaded) {
			if (zdilep_dphi_branch != 0) {
				zdilep_dphi_branch->GetEntry(index);
			} else { 
				printf("branch zdilep_dphi_branch does not exist!\n");
				exit(1);
			}
			zdilep_dphi_isLoaded = true;
		}
		return zdilep_dphi_;
	}
	float &zdilep_deta()
	{
		if (not zdilep_deta_isLoaded) {
			if (zdilep_deta_branch != 0) {
				zdilep_deta_branch->GetEntry(index);
			} else { 
				printf("branch zdilep_deta_branch does not exist!\n");
				exit(1);
			}
			zdilep_deta_isLoaded = true;
		}
		return zdilep_deta_;
	}
	float &zdilep_dr()
	{
		if (not zdilep_dr_isLoaded) {
			if (zdilep_dr_branch != 0) {
				zdilep_dr_branch->GetEntry(index);
			} else { 
				printf("branch zdilep_dr_branch does not exist!\n");
				exit(1);
			}
			zdilep_dr_isLoaded = true;
		}
		return zdilep_dr_;
	}
	int &zfiduciality()
	{
		if (not zfiduciality_isLoaded) {
			if (zfiduciality_branch != 0) {
				zfiduciality_branch->GetEntry(index);
			} else { 
				printf("branch zfiduciality_branch does not exist!\n");
				exit(1);
			}
			zfiduciality_isLoaded = true;
		}
		return zfiduciality_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wp4()
	{
		if (not wp4_isLoaded) {
			if (wp4_branch != 0) {
				wp4_branch->GetEntry(index);
			} else { 
				printf("branch wp4_branch does not exist!\n");
				exit(1);
			}
			wp4_isLoaded = true;
		}
		return *wp4_;
	}
	bool &	wpasses_id()
	{
		if (not wpasses_id_isLoaded) {
			if (wpasses_id_branch != 0) {
				wpasses_id_branch->GetEntry(index);
			} else { 
				printf("branch wpasses_id_branch does not exist!\n");
				exit(1);
			}
			wpasses_id_isLoaded = true;
		}
		return wpasses_id_;
	}
	bool &	wpasses_iso()
	{
		if (not wpasses_iso_isLoaded) {
			if (wpasses_iso_branch != 0) {
				wpasses_iso_branch->GetEntry(index);
			} else { 
				printf("branch wpasses_iso_branch does not exist!\n");
				exit(1);
			}
			wpasses_iso_isLoaded = true;
		}
		return wpasses_iso_;
	}
	bool &	wis_num()
	{
		if (not wis_num_isLoaded) {
			if (wis_num_branch != 0) {
				wis_num_branch->GetEntry(index);
			} else { 
				printf("branch wis_num_branch does not exist!\n");
				exit(1);
			}
			wis_num_isLoaded = true;
		}
		return wis_num_;
	}
	bool &	wis_fo()
	{
		if (not wis_fo_isLoaded) {
			if (wis_fo_branch != 0) {
				wis_fo_branch->GetEntry(index);
			} else { 
				printf("branch wis_fo_branch does not exist!\n");
				exit(1);
			}
			wis_fo_isLoaded = true;
		}
		return wis_fo_;
	}
	int &wis_fromw()
	{
		if (not wis_fromw_isLoaded) {
			if (wis_fromw_branch != 0) {
				wis_fromw_branch->GetEntry(index);
			} else { 
				printf("branch wis_fromw_branch does not exist!\n");
				exit(1);
			}
			wis_fromw_isLoaded = true;
		}
		return wis_fromw_;
	}
	int &wcharge()
	{
		if (not wcharge_isLoaded) {
			if (wcharge_branch != 0) {
				wcharge_branch->GetEntry(index);
			} else { 
				printf("branch wcharge_branch does not exist!\n");
				exit(1);
			}
			wcharge_isLoaded = true;
		}
		return wcharge_;
	}
	int &wpdgid()
	{
		if (not wpdgid_isLoaded) {
			if (wpdgid_branch != 0) {
				wpdgid_branch->GetEntry(index);
			} else { 
				printf("branch wpdgid_branch does not exist!\n");
				exit(1);
			}
			wpdgid_isLoaded = true;
		}
		return wpdgid_;
	}
	int &wtype()
	{
		if (not wtype_isLoaded) {
			if (wtype_branch != 0) {
				wtype_branch->GetEntry(index);
			} else { 
				printf("branch wtype_branch does not exist!\n");
				exit(1);
			}
			wtype_isLoaded = true;
		}
		return wtype_;
	}
	float &wd0()
	{
		if (not wd0_isLoaded) {
			if (wd0_branch != 0) {
				wd0_branch->GetEntry(index);
			} else { 
				printf("branch wd0_branch does not exist!\n");
				exit(1);
			}
			wd0_isLoaded = true;
		}
		return wd0_;
	}
	float &wdz()
	{
		if (not wdz_isLoaded) {
			if (wdz_branch != 0) {
				wdz_branch->GetEntry(index);
			} else { 
				printf("branch wdz_branch does not exist!\n");
				exit(1);
			}
			wdz_isLoaded = true;
		}
		return wdz_;
	}
	float &wmt()
	{
		if (not wmt_isLoaded) {
			if (wmt_branch != 0) {
				wmt_branch->GetEntry(index);
			} else { 
				printf("branch wmt_branch does not exist!\n");
				exit(1);
			}
			wmt_isLoaded = true;
		}
		return wmt_;
	}
	float &wcorpfiso()
	{
		if (not wcorpfiso_isLoaded) {
			if (wcorpfiso_branch != 0) {
				wcorpfiso_branch->GetEntry(index);
			} else { 
				printf("branch wcorpfiso_branch does not exist!\n");
				exit(1);
			}
			wcorpfiso_isLoaded = true;
		}
		return wcorpfiso_;
	}
	float &wpfiso()
	{
		if (not wpfiso_isLoaded) {
			if (wpfiso_branch != 0) {
				wpfiso_branch->GetEntry(index);
			} else { 
				printf("branch wpfiso_branch does not exist!\n");
				exit(1);
			}
			wpfiso_isLoaded = true;
		}
		return wpfiso_;
	}
	float &wchiso()
	{
		if (not wchiso_isLoaded) {
			if (wchiso_branch != 0) {
				wchiso_branch->GetEntry(index);
			} else { 
				printf("branch wchiso_branch does not exist!\n");
				exit(1);
			}
			wchiso_isLoaded = true;
		}
		return wchiso_;
	}
	float &wemiso()
	{
		if (not wemiso_isLoaded) {
			if (wemiso_branch != 0) {
				wemiso_branch->GetEntry(index);
			} else { 
				printf("branch wemiso_branch does not exist!\n");
				exit(1);
			}
			wemiso_isLoaded = true;
		}
		return wemiso_;
	}
	float &wnhiso()
	{
		if (not wnhiso_isLoaded) {
			if (wnhiso_branch != 0) {
				wnhiso_branch->GetEntry(index);
			} else { 
				printf("branch wnhiso_branch does not exist!\n");
				exit(1);
			}
			wnhiso_isLoaded = true;
		}
		return wnhiso_;
	}
	float &wcorpfiso04()
	{
		if (not wcorpfiso04_isLoaded) {
			if (wcorpfiso04_branch != 0) {
				wcorpfiso04_branch->GetEntry(index);
			} else { 
				printf("branch wcorpfiso04_branch does not exist!\n");
				exit(1);
			}
			wcorpfiso04_isLoaded = true;
		}
		return wcorpfiso04_;
	}
	float &wpfiso04()
	{
		if (not wpfiso04_isLoaded) {
			if (wpfiso04_branch != 0) {
				wpfiso04_branch->GetEntry(index);
			} else { 
				printf("branch wpfiso04_branch does not exist!\n");
				exit(1);
			}
			wpfiso04_isLoaded = true;
		}
		return wpfiso04_;
	}
	float &wchiso04()
	{
		if (not wchiso04_isLoaded) {
			if (wchiso04_branch != 0) {
				wchiso04_branch->GetEntry(index);
			} else { 
				printf("branch wchiso04_branch does not exist!\n");
				exit(1);
			}
			wchiso04_isLoaded = true;
		}
		return wchiso04_;
	}
	float &wemiso04()
	{
		if (not wemiso04_isLoaded) {
			if (wemiso04_branch != 0) {
				wemiso04_branch->GetEntry(index);
			} else { 
				printf("branch wemiso04_branch does not exist!\n");
				exit(1);
			}
			wemiso04_isLoaded = true;
		}
		return wemiso04_;
	}
	float &wnhiso04()
	{
		if (not wnhiso04_isLoaded) {
			if (wnhiso04_branch != 0) {
				wnhiso04_branch->GetEntry(index);
			} else { 
				printf("branch wnhiso04_branch does not exist!\n");
				exit(1);
			}
			wnhiso04_isLoaded = true;
		}
		return wnhiso04_;
	}
	float &wcordetiso()
	{
		if (not wcordetiso_isLoaded) {
			if (wcordetiso_branch != 0) {
				wcordetiso_branch->GetEntry(index);
			} else { 
				printf("branch wcordetiso_branch does not exist!\n");
				exit(1);
			}
			wcordetiso_isLoaded = true;
		}
		return wcordetiso_;
	}
	float &wdetiso()
	{
		if (not wdetiso_isLoaded) {
			if (wdetiso_branch != 0) {
				wdetiso_branch->GetEntry(index);
			} else { 
				printf("branch wdetiso_branch does not exist!\n");
				exit(1);
			}
			wdetiso_isLoaded = true;
		}
		return wdetiso_;
	}
	float &wtrkiso()
	{
		if (not wtrkiso_isLoaded) {
			if (wtrkiso_branch != 0) {
				wtrkiso_branch->GetEntry(index);
			} else { 
				printf("branch wtrkiso_branch does not exist!\n");
				exit(1);
			}
			wtrkiso_isLoaded = true;
		}
		return wtrkiso_;
	}
	float &wecaliso()
	{
		if (not wecaliso_isLoaded) {
			if (wecaliso_branch != 0) {
				wecaliso_branch->GetEntry(index);
			} else { 
				printf("branch wecaliso_branch does not exist!\n");
				exit(1);
			}
			wecaliso_isLoaded = true;
		}
		return wecaliso_;
	}
	float &whcaliso()
	{
		if (not whcaliso_isLoaded) {
			if (whcaliso_branch != 0) {
				whcaliso_branch->GetEntry(index);
			} else { 
				printf("branch whcaliso_branch does not exist!\n");
				exit(1);
			}
			whcaliso_isLoaded = true;
		}
		return whcaliso_;
	}
	float &wcordetiso04()
	{
		if (not wcordetiso04_isLoaded) {
			if (wcordetiso04_branch != 0) {
				wcordetiso04_branch->GetEntry(index);
			} else { 
				printf("branch wcordetiso04_branch does not exist!\n");
				exit(1);
			}
			wcordetiso04_isLoaded = true;
		}
		return wcordetiso04_;
	}
	float &wdetiso04()
	{
		if (not wdetiso04_isLoaded) {
			if (wdetiso04_branch != 0) {
				wdetiso04_branch->GetEntry(index);
			} else { 
				printf("branch wdetiso04_branch does not exist!\n");
				exit(1);
			}
			wdetiso04_isLoaded = true;
		}
		return wdetiso04_;
	}
	float &wtrkiso04()
	{
		if (not wtrkiso04_isLoaded) {
			if (wtrkiso04_branch != 0) {
				wtrkiso04_branch->GetEntry(index);
			} else { 
				printf("branch wtrkiso04_branch does not exist!\n");
				exit(1);
			}
			wtrkiso04_isLoaded = true;
		}
		return wtrkiso04_;
	}
	float &wecaliso04()
	{
		if (not wecaliso04_isLoaded) {
			if (wecaliso04_branch != 0) {
				wecaliso04_branch->GetEntry(index);
			} else { 
				printf("branch wecaliso04_branch does not exist!\n");
				exit(1);
			}
			wecaliso04_isLoaded = true;
		}
		return wecaliso04_;
	}
	float &whcaliso04()
	{
		if (not whcaliso04_isLoaded) {
			if (whcaliso04_branch != 0) {
				whcaliso04_branch->GetEntry(index);
			} else { 
				printf("branch whcaliso04_branch does not exist!\n");
				exit(1);
			}
			whcaliso04_isLoaded = true;
		}
		return whcaliso04_;
	}
	float &weffarea()
	{
		if (not weffarea_isLoaded) {
			if (weffarea_branch != 0) {
				weffarea_branch->GetEntry(index);
			} else { 
				printf("branch weffarea_branch does not exist!\n");
				exit(1);
			}
			weffarea_isLoaded = true;
		}
		return weffarea_;
	}
	float &weffarea04()
	{
		if (not weffarea04_isLoaded) {
			if (weffarea04_branch != 0) {
				weffarea04_branch->GetEntry(index);
			} else { 
				printf("branch weffarea04_branch does not exist!\n");
				exit(1);
			}
			weffarea04_isLoaded = true;
		}
		return weffarea04_;
	}
	float &wdbeta()
	{
		if (not wdbeta_isLoaded) {
			if (wdbeta_branch != 0) {
				wdbeta_branch->GetEntry(index);
			} else { 
				printf("branch wdbeta_branch does not exist!\n");
				exit(1);
			}
			wdbeta_isLoaded = true;
		}
		return wdbeta_;
	}
	float &wdbeta04()
	{
		if (not wdbeta04_isLoaded) {
			if (wdbeta04_branch != 0) {
				wdbeta04_branch->GetEntry(index);
			} else { 
				printf("branch wdbeta04_branch does not exist!\n");
				exit(1);
			}
			wdbeta04_isLoaded = true;
		}
		return wdbeta04_;
	}
	float &wsf_lepeff()
	{
		if (not wsf_lepeff_isLoaded) {
			if (wsf_lepeff_branch != 0) {
				wsf_lepeff_branch->GetEntry(index);
			} else { 
				printf("branch wsf_lepeff_branch does not exist!\n");
				exit(1);
			}
			wsf_lepeff_isLoaded = true;
		}
		return wsf_lepeff_;
	}
	float &wsf_trig()
	{
		if (not wsf_trig_isLoaded) {
			if (wsf_trig_branch != 0) {
				wsf_trig_branch->GetEntry(index);
			} else { 
				printf("branch wsf_trig_branch does not exist!\n");
				exit(1);
			}
			wsf_trig_isLoaded = true;
		}
		return wsf_trig_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wmcp4()
	{
		if (not wmcp4_isLoaded) {
			if (wmcp4_branch != 0) {
				wmcp4_branch->GetEntry(index);
			} else { 
				printf("branch wmcp4_branch does not exist!\n");
				exit(1);
			}
			wmcp4_isLoaded = true;
		}
		return *wmcp4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wmc3p4()
	{
		if (not wmc3p4_isLoaded) {
			if (wmc3p4_branch != 0) {
				wmc3p4_branch->GetEntry(index);
			} else { 
				printf("branch wmc3p4_branch does not exist!\n");
				exit(1);
			}
			wmc3p4_isLoaded = true;
		}
		return *wmc3p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wmc_momp4()
	{
		if (not wmc_momp4_isLoaded) {
			if (wmc_momp4_branch != 0) {
				wmc_momp4_branch->GetEntry(index);
			} else { 
				printf("branch wmc_momp4_branch does not exist!\n");
				exit(1);
			}
			wmc_momp4_isLoaded = true;
		}
		return *wmc_momp4_;
	}
	int &wmcid()
	{
		if (not wmcid_isLoaded) {
			if (wmcid_branch != 0) {
				wmcid_branch->GetEntry(index);
			} else { 
				printf("branch wmcid_branch does not exist!\n");
				exit(1);
			}
			wmcid_isLoaded = true;
		}
		return wmcid_;
	}
	int &wmc3id()
	{
		if (not wmc3id_isLoaded) {
			if (wmc3id_branch != 0) {
				wmc3id_branch->GetEntry(index);
			} else { 
				printf("branch wmc3id_branch does not exist!\n");
				exit(1);
			}
			wmc3id_isLoaded = true;
		}
		return wmc3id_;
	}
	int &wmomid()
	{
		if (not wmomid_isLoaded) {
			if (wmomid_branch != 0) {
				wmomid_branch->GetEntry(index);
			} else { 
				printf("branch wmomid_branch does not exist!\n");
				exit(1);
			}
			wmomid_isLoaded = true;
		}
		return wmomid_;
	}
	int &wmc3_momid()
	{
		if (not wmc3_momid_isLoaded) {
			if (wmc3_momid_branch != 0) {
				wmc3_momid_branch->GetEntry(index);
			} else { 
				printf("branch wmc3_momid_branch does not exist!\n");
				exit(1);
			}
			wmc3_momid_isLoaded = true;
		}
		return wmc3_momid_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wgsf_p4()
	{
		if (not wgsf_p4_isLoaded) {
			if (wgsf_p4_branch != 0) {
				wgsf_p4_branch->GetEntry(index);
			} else { 
				printf("branch wgsf_p4_branch does not exist!\n");
				exit(1);
			}
			wgsf_p4_isLoaded = true;
		}
		return *wgsf_p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wctf_p4()
	{
		if (not wctf_p4_isLoaded) {
			if (wctf_p4_branch != 0) {
				wctf_p4_branch->GetEntry(index);
			} else { 
				printf("branch wctf_p4_branch does not exist!\n");
				exit(1);
			}
			wctf_p4_isLoaded = true;
		}
		return *wctf_p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wsc_p4()
	{
		if (not wsc_p4_isLoaded) {
			if (wsc_p4_branch != 0) {
				wsc_p4_branch->GetEntry(index);
			} else { 
				printf("branch wsc_p4_branch does not exist!\n");
				exit(1);
			}
			wsc_p4_isLoaded = true;
		}
		return *wsc_p4_;
	}
	bool &	wq3agree()
	{
		if (not wq3agree_isLoaded) {
			if (wq3agree_branch != 0) {
				wq3agree_branch->GetEntry(index);
			} else { 
				printf("branch wq3agree_branch does not exist!\n");
				exit(1);
			}
			wq3agree_isLoaded = true;
		}
		return wq3agree_;
	}
	bool &	wis_conv()
	{
		if (not wis_conv_isLoaded) {
			if (wis_conv_branch != 0) {
				wis_conv_branch->GetEntry(index);
			} else { 
				printf("branch wis_conv_branch does not exist!\n");
				exit(1);
			}
			wis_conv_isLoaded = true;
		}
		return wis_conv_;
	}
	int &wqsc()
	{
		if (not wqsc_isLoaded) {
			if (wqsc_branch != 0) {
				wqsc_branch->GetEntry(index);
			} else { 
				printf("branch wqsc_branch does not exist!\n");
				exit(1);
			}
			wqsc_isLoaded = true;
		}
		return wqsc_;
	}
	int &wqctf()
	{
		if (not wqctf_isLoaded) {
			if (wqctf_branch != 0) {
				wqctf_branch->GetEntry(index);
			} else { 
				printf("branch wqctf_branch does not exist!\n");
				exit(1);
			}
			wqctf_isLoaded = true;
		}
		return wqctf_;
	}
	int &wqgsf()
	{
		if (not wqgsf_isLoaded) {
			if (wqgsf_branch != 0) {
				wqgsf_branch->GetEntry(index);
			} else { 
				printf("branch wqgsf_branch does not exist!\n");
				exit(1);
			}
			wqgsf_isLoaded = true;
		}
		return wqgsf_;
	}
	int &wnmhits()
	{
		if (not wnmhits_isLoaded) {
			if (wnmhits_branch != 0) {
				wnmhits_branch->GetEntry(index);
			} else { 
				printf("branch wnmhits_branch does not exist!\n");
				exit(1);
			}
			wnmhits_isLoaded = true;
		}
		return wnmhits_;
	}
	int &weleid_veto()
	{
		if (not weleid_veto_isLoaded) {
			if (weleid_veto_branch != 0) {
				weleid_veto_branch->GetEntry(index);
			} else { 
				printf("branch weleid_veto_branch does not exist!\n");
				exit(1);
			}
			weleid_veto_isLoaded = true;
		}
		return weleid_veto_;
	}
	int &weleid_loose()
	{
		if (not weleid_loose_isLoaded) {
			if (weleid_loose_branch != 0) {
				weleid_loose_branch->GetEntry(index);
			} else { 
				printf("branch weleid_loose_branch does not exist!\n");
				exit(1);
			}
			weleid_loose_isLoaded = true;
		}
		return weleid_loose_;
	}
	int &weleid_medium()
	{
		if (not weleid_medium_isLoaded) {
			if (weleid_medium_branch != 0) {
				weleid_medium_branch->GetEntry(index);
			} else { 
				printf("branch weleid_medium_branch does not exist!\n");
				exit(1);
			}
			weleid_medium_isLoaded = true;
		}
		return weleid_medium_;
	}
	int &weleid_tight()
	{
		if (not weleid_tight_isLoaded) {
			if (weleid_tight_branch != 0) {
				weleid_tight_branch->GetEntry(index);
			} else { 
				printf("branch weleid_tight_branch does not exist!\n");
				exit(1);
			}
			weleid_tight_isLoaded = true;
		}
		return weleid_tight_;
	}
	float &wdphiin()
	{
		if (not wdphiin_isLoaded) {
			if (wdphiin_branch != 0) {
				wdphiin_branch->GetEntry(index);
			} else { 
				printf("branch wdphiin_branch does not exist!\n");
				exit(1);
			}
			wdphiin_isLoaded = true;
		}
		return wdphiin_;
	}
	float &wdetain()
	{
		if (not wdetain_isLoaded) {
			if (wdetain_branch != 0) {
				wdetain_branch->GetEntry(index);
			} else { 
				printf("branch wdetain_branch does not exist!\n");
				exit(1);
			}
			wdetain_isLoaded = true;
		}
		return wdetain_;
	}
	float &wsieie()
	{
		if (not wsieie_isLoaded) {
			if (wsieie_branch != 0) {
				wsieie_branch->GetEntry(index);
			} else { 
				printf("branch wsieie_branch does not exist!\n");
				exit(1);
			}
			wsieie_isLoaded = true;
		}
		return wsieie_;
	}
	float &whoe()
	{
		if (not whoe_isLoaded) {
			if (whoe_branch != 0) {
				whoe_branch->GetEntry(index);
			} else { 
				printf("branch whoe_branch does not exist!\n");
				exit(1);
			}
			whoe_isLoaded = true;
		}
		return whoe_;
	}
	float &wooemoop()
	{
		if (not wooemoop_isLoaded) {
			if (wooemoop_branch != 0) {
				wooemoop_branch->GetEntry(index);
			} else { 
				printf("branch wooemoop_branch does not exist!\n");
				exit(1);
			}
			wooemoop_isLoaded = true;
		}
		return wooemoop_;
	}
	float &wconv_dist()
	{
		if (not wconv_dist_isLoaded) {
			if (wconv_dist_branch != 0) {
				wconv_dist_branch->GetEntry(index);
			} else { 
				printf("branch wconv_dist_branch does not exist!\n");
				exit(1);
			}
			wconv_dist_isLoaded = true;
		}
		return wconv_dist_;
	}
	float &wconv_dcot()
	{
		if (not wconv_dcot_isLoaded) {
			if (wconv_dcot_branch != 0) {
				wconv_dcot_branch->GetEntry(index);
			} else { 
				printf("branch wconv_dcot_branch does not exist!\n");
				exit(1);
			}
			wconv_dcot_isLoaded = true;
		}
		return wconv_dcot_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wgfit_p4()
	{
		if (not wgfit_p4_isLoaded) {
			if (wgfit_p4_branch != 0) {
				wgfit_p4_branch->GetEntry(index);
			} else { 
				printf("branch wgfit_p4_branch does not exist!\n");
				exit(1);
			}
			wgfit_p4_isLoaded = true;
		}
		return *wgfit_p4_;
	}
	bool &	wis_global()
	{
		if (not wis_global_isLoaded) {
			if (wis_global_branch != 0) {
				wis_global_branch->GetEntry(index);
			} else { 
				printf("branch wis_global_branch does not exist!\n");
				exit(1);
			}
			wis_global_isLoaded = true;
		}
		return wis_global_;
	}
	bool &	wis_tracker()
	{
		if (not wis_tracker_isLoaded) {
			if (wis_tracker_branch != 0) {
				wis_tracker_branch->GetEntry(index);
			} else { 
				printf("branch wis_tracker_branch does not exist!\n");
				exit(1);
			}
			wis_tracker_isLoaded = true;
		}
		return wis_tracker_;
	}
	bool &	wis_stamu()
	{
		if (not wis_stamu_isLoaded) {
			if (wis_stamu_branch != 0) {
				wis_stamu_branch->GetEntry(index);
			} else { 
				printf("branch wis_stamu_branch does not exist!\n");
				exit(1);
			}
			wis_stamu_isLoaded = true;
		}
		return wis_stamu_;
	}
	bool &	wis_pfmu()
	{
		if (not wis_pfmu_isLoaded) {
			if (wis_pfmu_branch != 0) {
				wis_pfmu_branch->GetEntry(index);
			} else { 
				printf("branch wis_pfmu_branch does not exist!\n");
				exit(1);
			}
			wis_pfmu_isLoaded = true;
		}
		return wis_pfmu_;
	}
	bool &	wis_loosemu()
	{
		if (not wis_loosemu_isLoaded) {
			if (wis_loosemu_branch != 0) {
				wis_loosemu_branch->GetEntry(index);
			} else { 
				printf("branch wis_loosemu_branch does not exist!\n");
				exit(1);
			}
			wis_loosemu_isLoaded = true;
		}
		return wis_loosemu_;
	}
	bool &	wis_tightmu()
	{
		if (not wis_tightmu_isLoaded) {
			if (wis_tightmu_branch != 0) {
				wis_tightmu_branch->GetEntry(index);
			} else { 
				printf("branch wis_tightmu_branch does not exist!\n");
				exit(1);
			}
			wis_tightmu_isLoaded = true;
		}
		return wis_tightmu_;
	}
	int &wnpixelhits()
	{
		if (not wnpixelhits_isLoaded) {
			if (wnpixelhits_branch != 0) {
				wnpixelhits_branch->GetEntry(index);
			} else { 
				printf("branch wnpixelhits_branch does not exist!\n");
				exit(1);
			}
			wnpixelhits_isLoaded = true;
		}
		return wnpixelhits_;
	}
	int &wnsihits()
	{
		if (not wnsihits_isLoaded) {
			if (wnsihits_branch != 0) {
				wnsihits_branch->GetEntry(index);
			} else { 
				printf("branch wnsihits_branch does not exist!\n");
				exit(1);
			}
			wnsihits_isLoaded = true;
		}
		return wnsihits_;
	}
	int &wnsilayers()
	{
		if (not wnsilayers_isLoaded) {
			if (wnsilayers_branch != 0) {
				wnsilayers_branch->GetEntry(index);
			} else { 
				printf("branch wnsilayers_branch does not exist!\n");
				exit(1);
			}
			wnsilayers_isLoaded = true;
		}
		return wnsilayers_;
	}
	int &wnstahits()
	{
		if (not wnstahits_isLoaded) {
			if (wnstahits_branch != 0) {
				wnstahits_branch->GetEntry(index);
			} else { 
				printf("branch wnstahits_branch does not exist!\n");
				exit(1);
			}
			wnstahits_isLoaded = true;
		}
		return wnstahits_;
	}
	int &wnstations()
	{
		if (not wnstations_isLoaded) {
			if (wnstations_branch != 0) {
				wnstations_branch->GetEntry(index);
			} else { 
				printf("branch wnstations_branch does not exist!\n");
				exit(1);
			}
			wnstations_isLoaded = true;
		}
		return wnstations_;
	}
	float &wchi2()
	{
		if (not wchi2_isLoaded) {
			if (wchi2_branch != 0) {
				wchi2_branch->GetEntry(index);
			} else { 
				printf("branch wchi2_branch does not exist!\n");
				exit(1);
			}
			wchi2_isLoaded = true;
		}
		return wchi2_;
	}
	float &wndof()
	{
		if (not wndof_isLoaded) {
			if (wndof_branch != 0) {
				wndof_branch->GetEntry(index);
			} else { 
				printf("branch wndof_branch does not exist!\n");
				exit(1);
			}
			wndof_isLoaded = true;
		}
		return wndof_;
	}
	float &wpterr()
	{
		if (not wpterr_isLoaded) {
			if (wpterr_branch != 0) {
				wpterr_branch->GetEntry(index);
			} else { 
				printf("branch wpterr_branch does not exist!\n");
				exit(1);
			}
			wpterr_isLoaded = true;
		}
		return wpterr_;
	}
	float &wecal_vetodep()
	{
		if (not wecal_vetodep_isLoaded) {
			if (wecal_vetodep_branch != 0) {
				wecal_vetodep_branch->GetEntry(index);
			} else { 
				printf("branch wecal_vetodep_branch does not exist!\n");
				exit(1);
			}
			wecal_vetodep_isLoaded = true;
		}
		return wecal_vetodep_;
	}
	float &whcal_vetodep()
	{
		if (not whcal_vetodep_isLoaded) {
			if (whcal_vetodep_branch != 0) {
				whcal_vetodep_branch->GetEntry(index);
			} else { 
				printf("branch whcal_vetodep_branch does not exist!\n");
				exit(1);
			}
			whcal_vetodep_isLoaded = true;
		}
		return whcal_vetodep_;
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
	int &njets15()
	{
		if (not njets15_isLoaded) {
			if (njets15_branch != 0) {
				njets15_branch->GetEntry(index);
			} else { 
				printf("branch njets15_branch does not exist!\n");
				exit(1);
			}
			njets15_isLoaded = true;
		}
		return njets15_;
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
	int &nbtags_tight()
	{
		if (not nbtags_tight_isLoaded) {
			if (nbtags_tight_branch != 0) {
				nbtags_tight_branch->GetEntry(index);
			} else { 
				printf("branch nbtags_tight_branch does not exist!\n");
				exit(1);
			}
			nbtags_tight_isLoaded = true;
		}
		return nbtags_tight_;
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
	int &event_type()
	{
		if (not event_type_isLoaded) {
			if (event_type_branch != 0) {
				event_type_branch->GetEntry(index);
			} else { 
				printf("branch event_type_branch does not exist!\n");
				exit(1);
			}
			event_type_isLoaded = true;
		}
		return event_type_;
	}
	int &njets30_dn()
	{
		if (not njets30_dn_isLoaded) {
			if (njets30_dn_branch != 0) {
				njets30_dn_branch->GetEntry(index);
			} else { 
				printf("branch njets30_dn_branch does not exist!\n");
				exit(1);
			}
			njets30_dn_isLoaded = true;
		}
		return njets30_dn_;
	}
	int &njets30_up()
	{
		if (not njets30_up_isLoaded) {
			if (njets30_up_branch != 0) {
				njets30_up_branch->GetEntry(index);
			} else { 
				printf("branch njets30_up_branch does not exist!\n");
				exit(1);
			}
			njets30_up_isLoaded = true;
		}
		return njets30_up_;
	}
	int &njets15_dn()
	{
		if (not njets15_dn_isLoaded) {
			if (njets15_dn_branch != 0) {
				njets15_dn_branch->GetEntry(index);
			} else { 
				printf("branch njets15_dn_branch does not exist!\n");
				exit(1);
			}
			njets15_dn_isLoaded = true;
		}
		return njets15_dn_;
	}
	int &njets15_up()
	{
		if (not njets15_up_isLoaded) {
			if (njets15_up_branch != 0) {
				njets15_up_branch->GetEntry(index);
			} else { 
				printf("branch njets15_up_branch does not exist!\n");
				exit(1);
			}
			njets15_up_isLoaded = true;
		}
		return njets15_up_;
	}
	int &nbtags_loose_dn()
	{
		if (not nbtags_loose_dn_isLoaded) {
			if (nbtags_loose_dn_branch != 0) {
				nbtags_loose_dn_branch->GetEntry(index);
			} else { 
				printf("branch nbtags_loose_dn_branch does not exist!\n");
				exit(1);
			}
			nbtags_loose_dn_isLoaded = true;
		}
		return nbtags_loose_dn_;
	}
	int &nbtags_loose_up()
	{
		if (not nbtags_loose_up_isLoaded) {
			if (nbtags_loose_up_branch != 0) {
				nbtags_loose_up_branch->GetEntry(index);
			} else { 
				printf("branch nbtags_loose_up_branch does not exist!\n");
				exit(1);
			}
			nbtags_loose_up_isLoaded = true;
		}
		return nbtags_loose_up_;
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
	int &lep1_passes_id_bitmask()
	{
		if (not lep1_passes_id_bitmask_isLoaded) {
			if (lep1_passes_id_bitmask_branch != 0) {
				lep1_passes_id_bitmask_branch->GetEntry(index);
			} else { 
				printf("branch lep1_passes_id_bitmask_branch does not exist!\n");
				exit(1);
			}
			lep1_passes_id_bitmask_isLoaded = true;
		}
		return lep1_passes_id_bitmask_;
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
	int &lep2_passes_id_bitmask()
	{
		if (not lep2_passes_id_bitmask_isLoaded) {
			if (lep2_passes_id_bitmask_branch != 0) {
				lep2_passes_id_bitmask_branch->GetEntry(index);
			} else { 
				printf("branch lep2_passes_id_bitmask_branch does not exist!\n");
				exit(1);
			}
			lep2_passes_id_bitmask_isLoaded = true;
		}
		return lep2_passes_id_bitmask_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_nearbjet_p4()
	{
		if (not lep3_nearbjet_p4_isLoaded) {
			if (lep3_nearbjet_p4_branch != 0) {
				lep3_nearbjet_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep3_nearbjet_p4_branch does not exist!\n");
				exit(1);
			}
			lep3_nearbjet_p4_isLoaded = true;
		}
		return *lep3_nearbjet_p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_nearjet_p4()
	{
		if (not lep3_nearjet_p4_isLoaded) {
			if (lep3_nearjet_p4_branch != 0) {
				lep3_nearjet_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep3_nearjet_p4_branch does not exist!\n");
				exit(1);
			}
			lep3_nearjet_p4_isLoaded = true;
		}
		return *lep3_nearjet_p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_nearlep_p4()
	{
		if (not lep3_nearlep_p4_isLoaded) {
			if (lep3_nearlep_p4_branch != 0) {
				lep3_nearlep_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep3_nearlep_p4_branch does not exist!\n");
				exit(1);
			}
			lep3_nearlep_p4_isLoaded = true;
		}
		return *lep3_nearlep_p4_;
	}
	float &lep3_wfr()
	{
		if (not lep3_wfr_isLoaded) {
			if (lep3_wfr_branch != 0) {
				lep3_wfr_branch->GetEntry(index);
			} else { 
				printf("branch lep3_wfr_branch does not exist!\n");
				exit(1);
			}
			lep3_wfr_isLoaded = true;
		}
		return lep3_wfr_;
	}
	float &lep3_nearbjet_dr()
	{
		if (not lep3_nearbjet_dr_isLoaded) {
			if (lep3_nearbjet_dr_branch != 0) {
				lep3_nearbjet_dr_branch->GetEntry(index);
			} else { 
				printf("branch lep3_nearbjet_dr_branch does not exist!\n");
				exit(1);
			}
			lep3_nearbjet_dr_isLoaded = true;
		}
		return lep3_nearbjet_dr_;
	}
	float &lep3_nearjet_dr()
	{
		if (not lep3_nearjet_dr_isLoaded) {
			if (lep3_nearjet_dr_branch != 0) {
				lep3_nearjet_dr_branch->GetEntry(index);
			} else { 
				printf("branch lep3_nearjet_dr_branch does not exist!\n");
				exit(1);
			}
			lep3_nearjet_dr_isLoaded = true;
		}
		return lep3_nearjet_dr_;
	}
	float &lep3_nearlep_dr()
	{
		if (not lep3_nearlep_dr_isLoaded) {
			if (lep3_nearlep_dr_branch != 0) {
				lep3_nearlep_dr_branch->GetEntry(index);
			} else { 
				printf("branch lep3_nearlep_dr_branch does not exist!\n");
				exit(1);
			}
			lep3_nearlep_dr_isLoaded = true;
		}
		return lep3_nearlep_dr_;
	}
	int &lep3_nearlep_id()
	{
		if (not lep3_nearlep_id_isLoaded) {
			if (lep3_nearlep_id_branch != 0) {
				lep3_nearlep_id_branch->GetEntry(index);
			} else { 
				printf("branch lep3_nearlep_id_branch does not exist!\n");
				exit(1);
			}
			lep3_nearlep_id_isLoaded = true;
		}
		return lep3_nearlep_id_;
	}
	int &lep3_passes_id_bitmask()
	{
		if (not lep3_passes_id_bitmask_isLoaded) {
			if (lep3_passes_id_bitmask_branch != 0) {
				lep3_passes_id_bitmask_branch->GetEntry(index);
			} else { 
				printf("branch lep3_passes_id_bitmask_branch does not exist!\n");
				exit(1);
			}
			lep3_passes_id_bitmask_isLoaded = true;
		}
		return lep3_passes_id_bitmask_;
	}
	bool &	is_gen_z()
	{
		if (not is_gen_z_isLoaded) {
			if (is_gen_z_branch != 0) {
				is_gen_z_branch->GetEntry(index);
			} else { 
				printf("branch is_gen_z_branch does not exist!\n");
				exit(1);
			}
			is_gen_z_isLoaded = true;
		}
		return is_gen_z_;
	}
	bool &	is_gen_w()
	{
		if (not is_gen_w_isLoaded) {
			if (is_gen_w_branch != 0) {
				is_gen_w_branch->GetEntry(index);
			} else { 
				printf("branch is_gen_w_branch does not exist!\n");
				exit(1);
			}
			is_gen_w_isLoaded = true;
		}
		return is_gen_w_;
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
	float &gen_nleps()
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
	float &sf_nbtag2()
	{
		if (not sf_nbtag2_isLoaded) {
			if (sf_nbtag2_branch != 0) {
				sf_nbtag2_branch->GetEntry(index);
			} else { 
				printf("branch sf_nbtag2_branch does not exist!\n");
				exit(1);
			}
			sf_nbtag2_isLoaded = true;
		}
		return sf_nbtag2_;
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
	float &sf_unc_nbtag2()
	{
		if (not sf_unc_nbtag2_isLoaded) {
			if (sf_unc_nbtag2_branch != 0) {
				sf_unc_nbtag2_branch->GetEntry(index);
			} else { 
				printf("branch sf_unc_nbtag2_branch does not exist!\n");
				exit(1);
			}
			sf_unc_nbtag2_isLoaded = true;
		}
		return sf_unc_nbtag2_;
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
	vector<bool> &vbtags_loose()
	{
		if (not vbtags_loose_isLoaded) {
			if (vbtags_loose_branch != 0) {
				vbtags_loose_branch->GetEntry(index);
			} else { 
				printf("branch vbtags_loose_branch does not exist!\n");
				exit(1);
			}
			vbtags_loose_isLoaded = true;
		}
		return *vbtags_loose_;
	}
	vector<bool> &vbtags_tight()
	{
		if (not vbtags_tight_isLoaded) {
			if (vbtags_tight_branch != 0) {
				vbtags_tight_branch->GetEntry(index);
			} else { 
				printf("branch vbtags_tight_branch does not exist!\n");
				exit(1);
			}
			vbtags_tight_isLoaded = true;
		}
		return *vbtags_tight_;
	}
	vector<float> &vbjets_disc()
	{
		if (not vbjets_disc_isLoaded) {
			if (vbjets_disc_branch != 0) {
				vbjets_disc_branch->GetEntry(index);
			} else { 
				printf("branch vbjets_disc_branch does not exist!\n");
				exit(1);
			}
			vbjets_disc_isLoaded = true;
		}
		return *vbjets_disc_;
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
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep3_p4()
	{
		if (not gen_lep3_p4_isLoaded) {
			if (gen_lep3_p4_branch != 0) {
				gen_lep3_p4_branch->GetEntry(index);
			} else { 
				printf("branch gen_lep3_p4_branch does not exist!\n");
				exit(1);
			}
			gen_lep3_p4_isLoaded = true;
		}
		return *gen_lep3_p4_;
	}
	float &gen_mt()
	{
		if (not gen_mt_isLoaded) {
			if (gen_mt_branch != 0) {
				gen_mt_branch->GetEntry(index);
			} else { 
				printf("branch gen_mt_branch does not exist!\n");
				exit(1);
			}
			gen_mt_isLoaded = true;
		}
		return gen_mt_;
	}
	int &gen_lep3_pdgid()
	{
		if (not gen_lep3_pdgid_isLoaded) {
			if (gen_lep3_pdgid_branch != 0) {
				gen_lep3_pdgid_branch->GetEntry(index);
			} else { 
				printf("branch gen_lep3_pdgid_branch does not exist!\n");
				exit(1);
			}
			gen_lep3_pdgid_isLoaded = true;
		}
		return gen_lep3_pdgid_;
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
	float &lep1_ele_mva_trig()
	{
		if (not lep1_ele_mva_trig_isLoaded) {
			if (lep1_ele_mva_trig_branch != 0) {
				lep1_ele_mva_trig_branch->GetEntry(index);
			} else { 
				printf("branch lep1_ele_mva_trig_branch does not exist!\n");
				exit(1);
			}
			lep1_ele_mva_trig_isLoaded = true;
		}
		return lep1_ele_mva_trig_;
	}
	float &lep2_ele_mva_trig()
	{
		if (not lep2_ele_mva_trig_isLoaded) {
			if (lep2_ele_mva_trig_branch != 0) {
				lep2_ele_mva_trig_branch->GetEntry(index);
			} else { 
				printf("branch lep2_ele_mva_trig_branch does not exist!\n");
				exit(1);
			}
			lep2_ele_mva_trig_isLoaded = true;
		}
		return lep2_ele_mva_trig_;
	}
	float &lep3_ele_mva_trig()
	{
		if (not lep3_ele_mva_trig_isLoaded) {
			if (lep3_ele_mva_trig_branch != 0) {
				lep3_ele_mva_trig_branch->GetEntry(index);
			} else { 
				printf("branch lep3_ele_mva_trig_branch does not exist!\n");
				exit(1);
			}
			lep3_ele_mva_trig_isLoaded = true;
		}
		return lep3_ele_mva_trig_;
	}
	float &lep1_ele_mva_nontrig()
	{
		if (not lep1_ele_mva_nontrig_isLoaded) {
			if (lep1_ele_mva_nontrig_branch != 0) {
				lep1_ele_mva_nontrig_branch->GetEntry(index);
			} else { 
				printf("branch lep1_ele_mva_nontrig_branch does not exist!\n");
				exit(1);
			}
			lep1_ele_mva_nontrig_isLoaded = true;
		}
		return lep1_ele_mva_nontrig_;
	}
	float &lep2_ele_mva_nontrig()
	{
		if (not lep2_ele_mva_nontrig_isLoaded) {
			if (lep2_ele_mva_nontrig_branch != 0) {
				lep2_ele_mva_nontrig_branch->GetEntry(index);
			} else { 
				printf("branch lep2_ele_mva_nontrig_branch does not exist!\n");
				exit(1);
			}
			lep2_ele_mva_nontrig_isLoaded = true;
		}
		return lep2_ele_mva_nontrig_;
	}
	float &lep3_ele_mva_nontrig()
	{
		if (not lep3_ele_mva_nontrig_isLoaded) {
			if (lep3_ele_mva_nontrig_branch != 0) {
				lep3_ele_mva_nontrig_branch->GetEntry(index);
			} else { 
				printf("branch lep3_ele_mva_nontrig_branch does not exist!\n");
				exit(1);
			}
			lep3_ele_mva_nontrig_isLoaded = true;
		}
		return lep3_ele_mva_nontrig_;
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
extern TRILEPZ2012 ttz3l;
#endif

namespace trilepz {
	unsigned int &run();
	unsigned int &ls();
	unsigned int &evt();
	bool &is_real_data();
	int &sample();
	int &nvtxs();
	int &vtx_idx();
	float &pfmet();
	float &pfmet_phi();
	float &uncorpfmet();
	float &uncorpfmet_phi();
	float &scale1fb();
	float &xsec();
	float &kfactor();
	float &gen_met();
	float &gen_met_phi();
	TString &dataset();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_p4();
	bool &lep1_passes_id();
	bool &lep1_passes_iso();
	bool &lep1_is_num();
	bool &lep1_is_fo();
	int &lep1_is_fromw();
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
	int &lep2_is_fromw();
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
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &zdilep_p4();
	bool &zis_os();
	bool &zis_ss();
	int &zdilep_type();
	int &zdilep_gen_type();
	float &zdilep_mass();
	float &zdilep_dphi();
	float &zdilep_deta();
	float &zdilep_dr();
	int &zfiduciality();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wp4();
	bool &wpasses_id();
	bool &wpasses_iso();
	bool &wis_num();
	bool &wis_fo();
	int &wis_fromw();
	int &wcharge();
	int &wpdgid();
	int &wtype();
	float &wd0();
	float &wdz();
	float &wmt();
	float &wcorpfiso();
	float &wpfiso();
	float &wchiso();
	float &wemiso();
	float &wnhiso();
	float &wcorpfiso04();
	float &wpfiso04();
	float &wchiso04();
	float &wemiso04();
	float &wnhiso04();
	float &wcordetiso();
	float &wdetiso();
	float &wtrkiso();
	float &wecaliso();
	float &whcaliso();
	float &wcordetiso04();
	float &wdetiso04();
	float &wtrkiso04();
	float &wecaliso04();
	float &whcaliso04();
	float &weffarea();
	float &weffarea04();
	float &wdbeta();
	float &wdbeta04();
	float &wsf_lepeff();
	float &wsf_trig();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wmcp4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wmc3p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wmc_momp4();
	int &wmcid();
	int &wmc3id();
	int &wmomid();
	int &wmc3_momid();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wgsf_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wctf_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wsc_p4();
	bool &wq3agree();
	bool &wis_conv();
	int &wqsc();
	int &wqctf();
	int &wqgsf();
	int &wnmhits();
	int &weleid_veto();
	int &weleid_loose();
	int &weleid_medium();
	int &weleid_tight();
	float &wdphiin();
	float &wdetain();
	float &wsieie();
	float &whoe();
	float &wooemoop();
	float &wconv_dist();
	float &wconv_dcot();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &wgfit_p4();
	bool &wis_global();
	bool &wis_tracker();
	bool &wis_stamu();
	bool &wis_pfmu();
	bool &wis_loosemu();
	bool &wis_tightmu();
	int &wnpixelhits();
	int &wnsihits();
	int &wnsilayers();
	int &wnstahits();
	int &wnstations();
	float &wchi2();
	float &wndof();
	float &wpterr();
	float &wecal_vetodep();
	float &whcal_vetodep();
	unsigned int &selection();
	bool &clean();
	bool &is_good_lumi();
	int &njets15();
	int &njets30();
	int &nbtags_loose();
	int &nbtags_tight();
	float &vtxw();
	float &ht();
	float &rho();
	float &rho_iso();
	float &sf_dileptrig();
	float &sf_lepeff();
	bool &trig_mm();
	bool &trig_em();
	bool &trig_ee();
	int &event_type();
	int &njets30_dn();
	int &njets30_up();
	int &njets15_dn();
	int &njets15_up();
	int &nbtags_loose_dn();
	int &nbtags_loose_up();
	float &ht_dn();
	float &ht_up();
	float &pfmet_dn();
	float &pfmet_up();
	float &pfmet_phi_dn();
	float &pfmet_phi_up();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearbjet_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearjet_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_nearlep_p4();
	float &lep1_wfr();
	float &lep1_nearbjet_dr();
	float &lep1_nearjet_dr();
	float &lep1_nearlep_dr();
	int &lep1_nearlep_id();
	int &lep1_passes_id_bitmask();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearbjet_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearjet_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_nearlep_p4();
	float &lep2_wfr();
	float &lep2_nearbjet_dr();
	float &lep2_nearjet_dr();
	float &lep2_nearlep_dr();
	int &lep2_nearlep_id();
	int &lep2_passes_id_bitmask();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_nearbjet_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_nearjet_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep3_nearlep_p4();
	float &lep3_wfr();
	float &lep3_nearbjet_dr();
	float &lep3_nearjet_dr();
	float &lep3_nearlep_dr();
	int &lep3_nearlep_id();
	int &lep3_passes_id_bitmask();
	bool &is_gen_z();
	bool &is_gen_w();
	int &gen_nbtags();
	int &gen_njets();
	float &gen_ht();
	float &gen_nleps();
	float &sf_nbtag();
	float &sf_nbtag2();
	float &sf_unc_nbtag();
	float &sf_unc_nbtag2();
	float &bjets_dr12();
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vgenb_p4();
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vjets_p4();
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vgenjets_p4();
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &vbjets_p4();
	vector<bool> &vbtags_loose();
	vector<bool> &vbtags_tight();
	vector<float> &vbjets_disc();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep1_p4();
	int &gen_lep1_pdgid();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep2_p4();
	int &gen_lep2_pdgid();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep3_p4();
	float &gen_mt();
	int &gen_lep3_pdgid();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_dilep_p4();
	int &gen_dilep_type();
	float &gen_dilep_mass();
	float &gen_dilep_dphi();
	float &gen_dilep_deta();
	float &gen_dilep_dr();
	float &lep1_ele_mva_trig();
	float &lep2_ele_mva_trig();
	float &lep3_ele_mva_trig();
	float &lep1_ele_mva_nontrig();
	float &lep2_ele_mva_nontrig();
	float &lep3_ele_mva_nontrig();
}
#endif
