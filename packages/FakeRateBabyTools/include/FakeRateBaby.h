// -*- C++ -*-
#ifndef FakeRateBaby_H
#define FakeRateBaby_H
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

#define PARANOIA

using namespace std; 
class FakeRateBaby {
private: 
protected: 
	unsigned int index;
	int	run_;
	TBranch *run_branch;
	bool run_isLoaded;
	int	ls_;
	TBranch *ls_branch;
	bool ls_isLoaded;
	unsigned int	evt_;
	TBranch *evt_branch;
	bool evt_isLoaded;
	float	weight_;
	TBranch *weight_branch;
	bool weight_isLoaded;
	int	pu_nPUvertices_;
	TBranch *pu_nPUvertices_branch;
	bool pu_nPUvertices_isLoaded;
	int	evt_nvtxs_;
	TBranch *evt_nvtxs_branch;
	bool evt_nvtxs_isLoaded;
	int	nFOels_;
	TBranch *nFOels_branch;
	bool nFOels_isLoaded;
	int	nFOmus_;
	TBranch *nFOmus_branch;
	bool nFOmus_isLoaded;
	int	ngsfs_;
	TBranch *ngsfs_branch;
	bool ngsfs_isLoaded;
	int	nmus_;
	TBranch *nmus_branch;
	bool nmus_isLoaded;
	int	foel_id_;
	TBranch *foel_id_branch;
	bool foel_id_isLoaded;
	int	fomu_id_;
	TBranch *fomu_id_branch;
	bool fomu_id_isLoaded;
	float	foel_mass_;
	TBranch *foel_mass_branch;
	bool foel_mass_isLoaded;
	float	fomu_mass_;
	TBranch *fomu_mass_branch;
	bool fomu_mass_isLoaded;
	float	pt_;
	TBranch *pt_branch;
	bool pt_isLoaded;
	float	eta_;
	TBranch *eta_branch;
	bool eta_isLoaded;
	float	sceta_;
	TBranch *sceta_branch;
	bool sceta_isLoaded;
	float	phi_;
	TBranch *phi_branch;
	bool phi_isLoaded;
	float	scet_;
	TBranch *scet_branch;
	bool scet_isLoaded;
	float	hoe_;
	TBranch *hoe_branch;
	bool hoe_isLoaded;
	float	pfmet_;
	TBranch *pfmet_branch;
	bool pfmet_isLoaded;
	float	pfmetphi_;
	TBranch *pfmetphi_branch;
	bool pfmetphi_isLoaded;
	float	iso_;
	TBranch *iso_branch;
	bool iso_isLoaded;
	float	iso_nps_;
	TBranch *iso_nps_branch;
	bool iso_nps_isLoaded;
	float	trck_iso_;
	TBranch *trck_iso_branch;
	bool trck_iso_isLoaded;
	float	ecal_iso_;
	TBranch *ecal_iso_branch;
	bool ecal_iso_isLoaded;
	float	ecal_iso_nps_;
	TBranch *ecal_iso_nps_branch;
	bool ecal_iso_nps_isLoaded;
	float	hcal_iso_;
	TBranch *hcal_iso_branch;
	bool hcal_iso_isLoaded;
	float	pfiso03_;
	TBranch *pfiso03_branch;
	bool pfiso03_isLoaded;
	float	ch_pfiso03_;
	TBranch *ch_pfiso03_branch;
	bool ch_pfiso03_isLoaded;
	float	nh_pfiso03_;
	TBranch *nh_pfiso03_branch;
	bool nh_pfiso03_isLoaded;
	float	em_pfiso03_;
	TBranch *em_pfiso03_branch;
	bool em_pfiso03_isLoaded;
	float	pfiso04_;
	TBranch *pfiso04_branch;
	bool pfiso04_isLoaded;
	float	ch_pfiso04_;
	TBranch *ch_pfiso04_branch;
	bool ch_pfiso04_isLoaded;
	float	nh_pfiso04_;
	TBranch *nh_pfiso04_branch;
	bool nh_pfiso04_isLoaded;
	float	em_pfiso04_;
	TBranch *em_pfiso04_branch;
	bool em_pfiso04_isLoaded;
	float	pfpupt03_;
	TBranch *pfpupt03_branch;
	bool pfpupt03_isLoaded;
	float	pfpupt04_;
	TBranch *pfpupt04_branch;
	bool pfpupt04_isLoaded;
	float	cpfiso03_rho_;
	TBranch *cpfiso03_rho_branch;
	bool cpfiso03_rho_isLoaded;
	float	cpfiso03_db_;
	TBranch *cpfiso03_db_branch;
	bool cpfiso03_db_isLoaded;
	int	id_;
	TBranch *id_branch;
	bool id_isLoaded;
	bool	closestMuon_;
	TBranch *closestMuon_branch;
	bool closestMuon_isLoaded;
	float	el_id_sieie_;
	TBranch *el_id_sieie_branch;
	bool el_id_sieie_isLoaded;
	float	el_id_detain_;
	TBranch *el_id_detain_branch;
	bool el_id_detain_isLoaded;
	float	el_id_dphiin_;
	TBranch *el_id_dphiin_branch;
	bool el_id_dphiin_isLoaded;
	bool	el_id_smurfV5_;
	TBranch *el_id_smurfV5_branch;
	bool el_id_smurfV5_isLoaded;
	bool	el_id_vbtf80_;
	TBranch *el_id_vbtf80_branch;
	bool el_id_vbtf80_isLoaded;
	bool	el_id_vbtf90_;
	TBranch *el_id_vbtf90_branch;
	bool el_id_vbtf90_isLoaded;
	float	el_effarea_;
	TBranch *el_effarea_branch;
	bool el_effarea_isLoaded;
	float	mu_effarea03_;
	TBranch *mu_effarea03_branch;
	bool mu_effarea03_isLoaded;
	float	mu_nh_effarea03_;
	TBranch *mu_nh_effarea03_branch;
	bool mu_nh_effarea03_isLoaded;
	float	mu_em_effarea03_;
	TBranch *mu_em_effarea03_branch;
	bool mu_em_effarea03_isLoaded;
	float	mu_effarea03_tight_;
	TBranch *mu_effarea03_tight_branch;
	bool mu_effarea03_tight_isLoaded;
	float	mu_nh_effarea03_tight_;
	TBranch *mu_nh_effarea03_tight_branch;
	bool mu_nh_effarea03_tight_isLoaded;
	float	mu_em_effarea03_tight_;
	TBranch *mu_em_effarea03_tight_branch;
	bool mu_em_effarea03_tight_isLoaded;
	float	mu_effarea04_;
	TBranch *mu_effarea04_branch;
	bool mu_effarea04_isLoaded;
	float	mu_nh_effarea04_;
	TBranch *mu_nh_effarea04_branch;
	bool mu_nh_effarea04_isLoaded;
	float	mu_em_effarea04_;
	TBranch *mu_em_effarea04_branch;
	bool mu_em_effarea04_isLoaded;
	float	mu_effarea04_tight_;
	TBranch *mu_effarea04_tight_branch;
	bool mu_effarea04_tight_isLoaded;
	float	mu_nh_effarea04_tight_;
	TBranch *mu_nh_effarea04_tight_branch;
	bool mu_nh_effarea04_tight_isLoaded;
	float	mu_em_effarea04_tight_;
	TBranch *mu_em_effarea04_tight_branch;
	bool mu_em_effarea04_tight_isLoaded;
	bool	conv0MissHits_;
	TBranch *conv0MissHits_branch;
	bool conv0MissHits_isLoaded;
	bool	convHitPattern_;
	TBranch *convHitPattern_branch;
	bool convHitPattern_isLoaded;
	bool	convPartnerTrack_;
	TBranch *convPartnerTrack_branch;
	bool convPartnerTrack_isLoaded;
	bool	convMIT_;
	TBranch *convMIT_branch;
	bool convMIT_isLoaded;
	float	mt_;
	TBranch *mt_branch;
	bool mt_isLoaded;
	float	pfmt_;
	TBranch *pfmt_branch;
	bool pfmt_isLoaded;
	bool	q3_;
	TBranch *q3_branch;
	bool q3_isLoaded;
	int	els_exp_innerlayers_;
	TBranch *els_exp_innerlayers_branch;
	bool els_exp_innerlayers_isLoaded;
	float	d0PV_wwV1_;
	TBranch *d0PV_wwV1_branch;
	bool d0PV_wwV1_isLoaded;
	float	dzPV_wwV1_;
	TBranch *dzPV_wwV1_branch;
	bool dzPV_wwV1_isLoaded;
	float	ht_calo_;
	TBranch *ht_calo_branch;
	bool ht_calo_isLoaded;
	float	ht_calo_L2L3_;
	TBranch *ht_calo_L2L3_branch;
	bool ht_calo_L2L3_isLoaded;
	float	ht_pf_;
	TBranch *ht_pf_branch;
	bool ht_pf_isLoaded;
	float	ht_pf_L2L3_;
	TBranch *ht_pf_L2L3_branch;
	bool ht_pf_L2L3_isLoaded;
	float	ht_pf_L1FastL2L3_;
	TBranch *ht_pf_L1FastL2L3_branch;
	bool ht_pf_L1FastL2L3_isLoaded;
	int	mcid_;
	TBranch *mcid_branch;
	bool mcid_isLoaded;
	int	mcmotherid_;
	TBranch *mcmotherid_branch;
	bool mcmotherid_isLoaded;
	int	mc3id_;
	TBranch *mc3id_branch;
	bool mc3id_isLoaded;
	float	mc3pt_;
	TBranch *mc3pt_branch;
	bool mc3pt_isLoaded;
	float	mc3dr_;
	TBranch *mc3dr_branch;
	bool mc3dr_isLoaded;
	int	leptonIsFromW_;
	TBranch *leptonIsFromW_branch;
	bool leptonIsFromW_isLoaded;
	bool	mu_isCosmic_;
	TBranch *mu_isCosmic_branch;
	bool mu_isCosmic_isLoaded;
	float	mz_fo_gsf_;
	TBranch *mz_fo_gsf_branch;
	bool mz_fo_gsf_isLoaded;
	float	mz_gsf_iso_;
	TBranch *mz_gsf_iso_branch;
	bool mz_gsf_iso_isLoaded;
	float	mz_fo_ctf_;
	TBranch *mz_fo_ctf_branch;
	bool mz_fo_ctf_isLoaded;
	float	mz_ctf_iso_;
	TBranch *mz_ctf_iso_branch;
	bool mz_ctf_iso_isLoaded;
	float	mupsilon_fo_mu_;
	TBranch *mupsilon_fo_mu_branch;
	bool mupsilon_fo_mu_isLoaded;
	float	mupsilon_mu_iso_;
	TBranch *mupsilon_mu_iso_branch;
	bool mupsilon_mu_iso_isLoaded;
	bool	num_el_ssV7_;
	TBranch *num_el_ssV7_branch;
	bool num_el_ssV7_isLoaded;
	bool	num_el_ssV7_noIso_;
	TBranch *num_el_ssV7_noIso_branch;
	bool num_el_ssV7_noIso_isLoaded;
	bool	v1_el_ssV7_;
	TBranch *v1_el_ssV7_branch;
	bool v1_el_ssV7_isLoaded;
	bool	v2_el_ssV7_;
	TBranch *v2_el_ssV7_branch;
	bool v2_el_ssV7_isLoaded;
	bool	v3_el_ssV7_;
	TBranch *v3_el_ssV7_branch;
	bool v3_el_ssV7_isLoaded;
	bool	num_mu_ssV5_;
	TBranch *num_mu_ssV5_branch;
	bool num_mu_ssV5_isLoaded;
	bool	num_mu_ssV5_noIso_;
	TBranch *num_mu_ssV5_noIso_branch;
	bool num_mu_ssV5_noIso_isLoaded;
	bool	fo_mu_ssV5_;
	TBranch *fo_mu_ssV5_branch;
	bool fo_mu_ssV5_isLoaded;
	bool	fo_mu_ssV5_noIso_;
	TBranch *fo_mu_ssV5_noIso_branch;
	bool fo_mu_ssV5_noIso_isLoaded;
	bool	num_el_ssV6_;
	TBranch *num_el_ssV6_branch;
	bool num_el_ssV6_isLoaded;
	bool	num_el_ssV6_noIso_;
	TBranch *num_el_ssV6_noIso_branch;
	bool num_el_ssV6_noIso_isLoaded;
	bool	v1_el_ssV6_;
	TBranch *v1_el_ssV6_branch;
	bool v1_el_ssV6_isLoaded;
	bool	v2_el_ssV6_;
	TBranch *v2_el_ssV6_branch;
	bool v2_el_ssV6_isLoaded;
	bool	v3_el_ssV6_;
	TBranch *v3_el_ssV6_branch;
	bool v3_el_ssV6_isLoaded;
	bool	numNomSSv4_;
	TBranch *numNomSSv4_branch;
	bool numNomSSv4_isLoaded;
	bool	numNomSSv4noIso_;
	TBranch *numNomSSv4noIso_branch;
	bool numNomSSv4noIso_isLoaded;
	bool	fo_mussV4_04_;
	TBranch *fo_mussV4_04_branch;
	bool fo_mussV4_04_isLoaded;
	bool	fo_mussV4_noIso_;
	TBranch *fo_mussV4_noIso_branch;
	bool fo_mussV4_noIso_isLoaded;
	bool	num_el_smurfV6_;
	TBranch *num_el_smurfV6_branch;
	bool num_el_smurfV6_isLoaded;
	bool	num_el_smurfV6lh_;
	TBranch *num_el_smurfV6lh_branch;
	bool num_el_smurfV6lh_isLoaded;
	bool	v1_el_smurfV1_;
	TBranch *v1_el_smurfV1_branch;
	bool v1_el_smurfV1_isLoaded;
	bool	v2_el_smurfV1_;
	TBranch *v2_el_smurfV1_branch;
	bool v2_el_smurfV1_isLoaded;
	bool	v3_el_smurfV1_;
	TBranch *v3_el_smurfV1_branch;
	bool v3_el_smurfV1_isLoaded;
	bool	v4_el_smurfV1_;
	TBranch *v4_el_smurfV1_branch;
	bool v4_el_smurfV1_isLoaded;
	bool	num_mu_smurfV6_;
	TBranch *num_mu_smurfV6_branch;
	bool num_mu_smurfV6_isLoaded;
	bool	fo_mu_smurf_04_;
	TBranch *fo_mu_smurf_04_branch;
	bool fo_mu_smurf_04_isLoaded;
	bool	fo_mu_smurf_10_;
	TBranch *fo_mu_smurf_10_branch;
	bool fo_mu_smurf_10_isLoaded;
	bool	num_el_OSV2_;
	TBranch *num_el_OSV2_branch;
	bool num_el_OSV2_isLoaded;
	bool	num_mu_OSGV2_;
	TBranch *num_mu_OSGV2_branch;
	bool num_mu_OSGV2_isLoaded;
	bool	num_mu_OSZV2_;
	TBranch *num_mu_OSZV2_branch;
	bool num_mu_OSZV2_isLoaded;
	bool	fo_el_OSV2_;
	TBranch *fo_el_OSV2_branch;
	bool fo_el_OSV2_isLoaded;
	bool	fo_mu_OSGV2_;
	TBranch *fo_mu_OSGV2_branch;
	bool fo_mu_OSGV2_isLoaded;
	bool	num_el_OSV3_;
	TBranch *num_el_OSV3_branch;
	bool num_el_OSV3_isLoaded;
	bool	num_mu_OSGV3_;
	TBranch *num_mu_OSGV3_branch;
	bool num_mu_OSGV3_isLoaded;
	bool	fo_el_OSV3_;
	TBranch *fo_el_OSV3_branch;
	bool fo_el_OSV3_isLoaded;
	bool	fo_mu_OSGV3_;
	TBranch *fo_mu_OSGV3_branch;
	bool fo_mu_OSGV3_isLoaded;
	int	ele8_vstar_;
	TBranch *ele8_vstar_branch;
	bool ele8_vstar_isLoaded;
	int	ele8_CaloIdL_TrkIdVL_vstar_;
	TBranch *ele8_CaloIdL_TrkIdVL_vstar_branch;
	bool ele8_CaloIdL_TrkIdVL_vstar_isLoaded;
	int	ele8_CaloIdL_CaloIsoVL_Jet40_vstar_;
	TBranch *ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch;
	bool ele8_CaloIdL_CaloIsoVL_Jet40_vstar_isLoaded;
	int	ele8_CaloIdL_CaloIsoVL_vstar_;
	TBranch *ele8_CaloIdL_CaloIsoVL_vstar_branch;
	bool ele8_CaloIdL_CaloIsoVL_vstar_isLoaded;
	int	ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_;
	TBranch *ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch;
	bool ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_isLoaded;
	int	ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_;
	TBranch *ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch;
	bool ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded;
	int	ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_;
	TBranch *ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch;
	bool ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded;
	int	ele8_CaloIdT_TrkIdVL_vstar_;
	TBranch *ele8_CaloIdT_TrkIdVL_vstar_branch;
	bool ele8_CaloIdT_TrkIdVL_vstar_isLoaded;
	int	ele8_CaloIdT_TrkIdVL_Jet30_vstar_;
	TBranch *ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch;
	bool ele8_CaloIdT_TrkIdVL_Jet30_vstar_isLoaded;
	int	ele17_CaloIdL_CaloIsoVL_vstar_;
	TBranch *ele17_CaloIdL_CaloIsoVL_vstar_branch;
	bool ele17_CaloIdL_CaloIsoVL_vstar_isLoaded;
	int	ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_;
	TBranch *ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch;
	bool ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded;
	int	ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_;
	TBranch *ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch;
	bool ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded;
	int	photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_;
	TBranch *photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch;
	bool photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_isLoaded;
	int	ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_;
	TBranch *ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch;
	bool ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_isLoaded;
	int	ele27_WP80_vstar_;
	TBranch *ele27_WP80_vstar_branch;
	bool ele27_WP80_vstar_isLoaded;
	int	ele8_version_;
	TBranch *ele8_version_branch;
	bool ele8_version_isLoaded;
	int	ele8_CaloIdL_TrkIdVL_version_;
	TBranch *ele8_CaloIdL_TrkIdVL_version_branch;
	bool ele8_CaloIdL_TrkIdVL_version_isLoaded;
	int	ele8_CaloIdL_CaloIsoVL_Jet40_version_;
	TBranch *ele8_CaloIdL_CaloIsoVL_Jet40_version_branch;
	bool ele8_CaloIdL_CaloIsoVL_Jet40_version_isLoaded;
	int	ele8_CaloIdL_CaloIsoVL_version_;
	TBranch *ele8_CaloIdL_CaloIsoVL_version_branch;
	bool ele8_CaloIdL_CaloIsoVL_version_isLoaded;
	int	ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_;
	TBranch *ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_branch;
	bool ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_isLoaded;
	int	ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_;
	TBranch *ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_branch;
	bool ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_isLoaded;
	int	ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_;
	TBranch *ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_branch;
	bool ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_isLoaded;
	int	ele8_CaloIdT_TrkIdVL_version_;
	TBranch *ele8_CaloIdT_TrkIdVL_version_branch;
	bool ele8_CaloIdT_TrkIdVL_version_isLoaded;
	int	ele8_CaloIdT_TrkIdVL_Jet30_version_;
	TBranch *ele8_CaloIdT_TrkIdVL_Jet30_version_branch;
	bool ele8_CaloIdT_TrkIdVL_Jet30_version_isLoaded;
	int	ele17_CaloIdL_CaloIsoVL_version_;
	TBranch *ele17_CaloIdL_CaloIsoVL_version_branch;
	bool ele17_CaloIdL_CaloIsoVL_version_isLoaded;
	int	ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_;
	TBranch *ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_branch;
	bool ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_isLoaded;
	int	ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_;
	TBranch *ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_branch;
	bool ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_isLoaded;
	int	photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_;
	TBranch *photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_branch;
	bool photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_isLoaded;
	int	ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_version_;
	TBranch *ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_version_branch;
	bool ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_version_isLoaded;
	int	ele27_WP80_version_;
	TBranch *ele27_WP80_version_branch;
	bool ele27_WP80_version_isLoaded;
	float	dr_ele8_vstar_;
	TBranch *dr_ele8_vstar_branch;
	bool dr_ele8_vstar_isLoaded;
	float	dr_ele8_CaloIdL_TrkIdVL_vstar_;
	TBranch *dr_ele8_CaloIdL_TrkIdVL_vstar_branch;
	bool dr_ele8_CaloIdL_TrkIdVL_vstar_isLoaded;
	float	dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_;
	TBranch *dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch;
	bool dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_isLoaded;
	float	dr_ele8_CaloIdL_CaloIsoVL_vstar_;
	TBranch *dr_ele8_CaloIdL_CaloIsoVL_vstar_branch;
	bool dr_ele8_CaloIdL_CaloIsoVL_vstar_isLoaded;
	float	dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_;
	TBranch *dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch;
	bool dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_isLoaded;
	float	dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_;
	TBranch *dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch;
	bool dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded;
	float	dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_;
	TBranch *dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch;
	bool dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded;
	float	dr_ele8_CaloIdT_TrkIdVL_vstar_;
	TBranch *dr_ele8_CaloIdT_TrkIdVL_vstar_branch;
	bool dr_ele8_CaloIdT_TrkIdVL_vstar_isLoaded;
	float	dr_ele8_CaloIdT_TrkIdVL_Jet30_vstar_;
	TBranch *dr_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch;
	bool dr_ele8_CaloIdT_TrkIdVL_Jet30_vstar_isLoaded;
	float	dr_ele17_CaloIdL_CaloIsoVL_vstar_;
	TBranch *dr_ele17_CaloIdL_CaloIsoVL_vstar_branch;
	bool dr_ele17_CaloIdL_CaloIsoVL_vstar_isLoaded;
	float	dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_;
	TBranch *dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch;
	bool dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded;
	float	dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_;
	TBranch *dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch;
	bool dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded;
	float	dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_;
	TBranch *dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch;
	bool dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_isLoaded;
	float	dr_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_;
	TBranch *dr_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch;
	bool dr_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_isLoaded;
	float	dr_ele27_WP80_vstar_;
	TBranch *dr_ele27_WP80_vstar_branch;
	bool dr_ele27_WP80_vstar_isLoaded;
	int	hltps_ele8_vstar_;
	TBranch *hltps_ele8_vstar_branch;
	bool hltps_ele8_vstar_isLoaded;
	int	hltps_ele8_CaloIdL_TrkIdVL_vstar_;
	TBranch *hltps_ele8_CaloIdL_TrkIdVL_vstar_branch;
	bool hltps_ele8_CaloIdL_TrkIdVL_vstar_isLoaded;
	int	hltps_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_;
	TBranch *hltps_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch;
	bool hltps_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_isLoaded;
	int	hltps_ele8_CaloIdL_CaloIsoVL_vstar_;
	TBranch *hltps_ele8_CaloIdL_CaloIsoVL_vstar_branch;
	bool hltps_ele8_CaloIdL_CaloIsoVL_vstar_isLoaded;
	int	hltps_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_;
	TBranch *hltps_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch;
	bool hltps_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_isLoaded;
	int	hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_;
	TBranch *hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch;
	bool hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded;
	int	hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_;
	TBranch *hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch;
	bool hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded;
	int	hltps_ele8_CaloIdT_TrkIdVL_vstar_;
	TBranch *hltps_ele8_CaloIdT_TrkIdVL_vstar_branch;
	bool hltps_ele8_CaloIdT_TrkIdVL_vstar_isLoaded;
	int	hltps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_;
	TBranch *hltps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch;
	bool hltps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_isLoaded;
	int	hltps_ele17_CaloIdL_CaloIsoVL_vstar_;
	TBranch *hltps_ele17_CaloIdL_CaloIsoVL_vstar_branch;
	bool hltps_ele17_CaloIdL_CaloIsoVL_vstar_isLoaded;
	int	hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_;
	TBranch *hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch;
	bool hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded;
	int	hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_;
	TBranch *hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch;
	bool hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded;
	int	hltps_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_;
	TBranch *hltps_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch;
	bool hltps_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_isLoaded;
	int	hltps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_;
	TBranch *hltps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch;
	bool hltps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_isLoaded;
	int	hltps_ele27_WP80_vstar_;
	TBranch *hltps_ele27_WP80_vstar_branch;
	bool hltps_ele27_WP80_vstar_isLoaded;
	int	l1ps_ele8_CaloIdL_CaloIsoVL_vstar_;
	TBranch *l1ps_ele8_CaloIdL_CaloIsoVL_vstar_branch;
	bool l1ps_ele8_CaloIdL_CaloIsoVL_vstar_isLoaded;
	int	l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_;
	TBranch *l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch;
	bool l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded;
	int	l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_;
	TBranch *l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch;
	bool l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded;
	int	l1ps_ele8_CaloIdT_TrkIdVL_vstar_;
	TBranch *l1ps_ele8_CaloIdT_TrkIdVL_vstar_branch;
	bool l1ps_ele8_CaloIdT_TrkIdVL_vstar_isLoaded;
	int	l1ps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_;
	TBranch *l1ps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch;
	bool l1ps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_isLoaded;
	int	l1ps_ele17_CaloIdL_CaloIsoVL_vstar_;
	TBranch *l1ps_ele17_CaloIdL_CaloIsoVL_vstar_branch;
	bool l1ps_ele17_CaloIdL_CaloIsoVL_vstar_isLoaded;
	int	l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_;
	TBranch *l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch;
	bool l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded;
	int	l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_;
	TBranch *l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch;
	bool l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded;
	int	l1ps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_;
	TBranch *l1ps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch;
	bool l1ps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_isLoaded;
	int	l1ps_ele27_WP80_vstar_;
	TBranch *l1ps_ele27_WP80_vstar_branch;
	bool l1ps_ele27_WP80_vstar_isLoaded;
	int	mu3_vstar_;
	TBranch *mu3_vstar_branch;
	bool mu3_vstar_isLoaded;
	int	mu5_vstar_;
	TBranch *mu5_vstar_branch;
	bool mu5_vstar_isLoaded;
	int	mu8_vstar_;
	TBranch *mu8_vstar_branch;
	bool mu8_vstar_isLoaded;
	int	mu12_vstar_;
	TBranch *mu12_vstar_branch;
	bool mu12_vstar_isLoaded;
	int	mu15_vstar_;
	TBranch *mu15_vstar_branch;
	bool mu15_vstar_isLoaded;
	int	mu17_vstar_;
	TBranch *mu17_vstar_branch;
	bool mu17_vstar_isLoaded;
	int	mu20_vstar_;
	TBranch *mu20_vstar_branch;
	bool mu20_vstar_isLoaded;
	int	mu24_vstar_;
	TBranch *mu24_vstar_branch;
	bool mu24_vstar_isLoaded;
	int	mu30_vstar_;
	TBranch *mu30_vstar_branch;
	bool mu30_vstar_isLoaded;
	int	mu15_eta2p1_vstar_;
	TBranch *mu15_eta2p1_vstar_branch;
	bool mu15_eta2p1_vstar_isLoaded;
	int	mu24_eta2p1_vstar_;
	TBranch *mu24_eta2p1_vstar_branch;
	bool mu24_eta2p1_vstar_isLoaded;
	int	mu30_eta2p1_vstar_;
	TBranch *mu30_eta2p1_vstar_branch;
	bool mu30_eta2p1_vstar_isLoaded;
	int	mu8_Jet40_vstar_;
	TBranch *mu8_Jet40_vstar_branch;
	bool mu8_Jet40_vstar_isLoaded;
	int	isoMu20_eta2p1_vstar_;
	TBranch *isoMu20_eta2p1_vstar_branch;
	bool isoMu20_eta2p1_vstar_isLoaded;
	int	isoMu24_eta2p1_vstar_;
	TBranch *isoMu24_eta2p1_vstar_branch;
	bool isoMu24_eta2p1_vstar_isLoaded;
	int	isoMu30_eta2p1_vstar_;
	TBranch *isoMu30_eta2p1_vstar_branch;
	bool isoMu30_eta2p1_vstar_isLoaded;
	int	relIso1p0Mu17_vstar_;
	TBranch *relIso1p0Mu17_vstar_branch;
	bool relIso1p0Mu17_vstar_isLoaded;
	int	relIso1p0Mu5_vstar_;
	TBranch *relIso1p0Mu5_vstar_branch;
	bool relIso1p0Mu5_vstar_isLoaded;
	int	mu3_version_;
	TBranch *mu3_version_branch;
	bool mu3_version_isLoaded;
	int	mu5_version_;
	TBranch *mu5_version_branch;
	bool mu5_version_isLoaded;
	int	mu8_version_;
	TBranch *mu8_version_branch;
	bool mu8_version_isLoaded;
	int	mu12_version_;
	TBranch *mu12_version_branch;
	bool mu12_version_isLoaded;
	int	mu15_version_;
	TBranch *mu15_version_branch;
	bool mu15_version_isLoaded;
	int	mu17_version_;
	TBranch *mu17_version_branch;
	bool mu17_version_isLoaded;
	int	mu20_version_;
	TBranch *mu20_version_branch;
	bool mu20_version_isLoaded;
	int	mu24_version_;
	TBranch *mu24_version_branch;
	bool mu24_version_isLoaded;
	int	mu30_version_;
	TBranch *mu30_version_branch;
	bool mu30_version_isLoaded;
	int	mu15_eta2p1_version_;
	TBranch *mu15_eta2p1_version_branch;
	bool mu15_eta2p1_version_isLoaded;
	int	mu24_eta2p1_version_;
	TBranch *mu24_eta2p1_version_branch;
	bool mu24_eta2p1_version_isLoaded;
	int	mu30_eta2p1_version_;
	TBranch *mu30_eta2p1_version_branch;
	bool mu30_eta2p1_version_isLoaded;
	int	mu8_Jet40_version_;
	TBranch *mu8_Jet40_version_branch;
	bool mu8_Jet40_version_isLoaded;
	int	isoMu20_eta2p1_version_;
	TBranch *isoMu20_eta2p1_version_branch;
	bool isoMu20_eta2p1_version_isLoaded;
	int	isoMu24_eta2p1_version_;
	TBranch *isoMu24_eta2p1_version_branch;
	bool isoMu24_eta2p1_version_isLoaded;
	int	isoMu30_eta2p1_version_;
	TBranch *isoMu30_eta2p1_version_branch;
	bool isoMu30_eta2p1_version_isLoaded;
	int	relIso1p0Mu17_version_;
	TBranch *relIso1p0Mu17_version_branch;
	bool relIso1p0Mu17_version_isLoaded;
	int	relIso1p0Mu5_version_;
	TBranch *relIso1p0Mu5_version_branch;
	bool relIso1p0Mu5_version_isLoaded;
	float	dr_mu3_vstar_;
	TBranch *dr_mu3_vstar_branch;
	bool dr_mu3_vstar_isLoaded;
	float	dr_mu5_vstar_;
	TBranch *dr_mu5_vstar_branch;
	bool dr_mu5_vstar_isLoaded;
	float	dr_mu8_vstar_;
	TBranch *dr_mu8_vstar_branch;
	bool dr_mu8_vstar_isLoaded;
	float	dr_mu12_vstar_;
	TBranch *dr_mu12_vstar_branch;
	bool dr_mu12_vstar_isLoaded;
	float	dr_mu15_vstar_;
	TBranch *dr_mu15_vstar_branch;
	bool dr_mu15_vstar_isLoaded;
	float	dr_mu17_vstar_;
	TBranch *dr_mu17_vstar_branch;
	bool dr_mu17_vstar_isLoaded;
	float	dr_mu20_vstar_;
	TBranch *dr_mu20_vstar_branch;
	bool dr_mu20_vstar_isLoaded;
	float	dr_mu24_vstar_;
	TBranch *dr_mu24_vstar_branch;
	bool dr_mu24_vstar_isLoaded;
	float	dr_mu30_vstar_;
	TBranch *dr_mu30_vstar_branch;
	bool dr_mu30_vstar_isLoaded;
	float	dr_mu15_eta2p1_vstar_;
	TBranch *dr_mu15_eta2p1_vstar_branch;
	bool dr_mu15_eta2p1_vstar_isLoaded;
	float	dr_mu24_eta2p1_vstar_;
	TBranch *dr_mu24_eta2p1_vstar_branch;
	bool dr_mu24_eta2p1_vstar_isLoaded;
	float	dr_mu30_eta2p1_vstar_;
	TBranch *dr_mu30_eta2p1_vstar_branch;
	bool dr_mu30_eta2p1_vstar_isLoaded;
	float	dr_mu8_Jet40_vstar_;
	TBranch *dr_mu8_Jet40_vstar_branch;
	bool dr_mu8_Jet40_vstar_isLoaded;
	float	dr_isoMu20_eta2p1_vstar_;
	TBranch *dr_isoMu20_eta2p1_vstar_branch;
	bool dr_isoMu20_eta2p1_vstar_isLoaded;
	float	dr_isoMu24_eta2p1_vstar_;
	TBranch *dr_isoMu24_eta2p1_vstar_branch;
	bool dr_isoMu24_eta2p1_vstar_isLoaded;
	float	dr_isoMu30_eta2p1_vstar_;
	TBranch *dr_isoMu30_eta2p1_vstar_branch;
	bool dr_isoMu30_eta2p1_vstar_isLoaded;
	float	dr_relIso1p0Mu17_vstar_;
	TBranch *dr_relIso1p0Mu17_vstar_branch;
	bool dr_relIso1p0Mu17_vstar_isLoaded;
	float	dr_relIso1p0Mu5_vstar_;
	TBranch *dr_relIso1p0Mu5_vstar_branch;
	bool dr_relIso1p0Mu5_vstar_isLoaded;
	int	hltps_mu3_vstar_;
	TBranch *hltps_mu3_vstar_branch;
	bool hltps_mu3_vstar_isLoaded;
	int	hltps_mu5_vstar_;
	TBranch *hltps_mu5_vstar_branch;
	bool hltps_mu5_vstar_isLoaded;
	int	hltps_mu8_vstar_;
	TBranch *hltps_mu8_vstar_branch;
	bool hltps_mu8_vstar_isLoaded;
	int	hltps_mu12_vstar_;
	TBranch *hltps_mu12_vstar_branch;
	bool hltps_mu12_vstar_isLoaded;
	int	hltps_mu15_vstar_;
	TBranch *hltps_mu15_vstar_branch;
	bool hltps_mu15_vstar_isLoaded;
	int	hltps_mu17_vstar_;
	TBranch *hltps_mu17_vstar_branch;
	bool hltps_mu17_vstar_isLoaded;
	int	hltps_mu20_vstar_;
	TBranch *hltps_mu20_vstar_branch;
	bool hltps_mu20_vstar_isLoaded;
	int	hltps_mu24_vstar_;
	TBranch *hltps_mu24_vstar_branch;
	bool hltps_mu24_vstar_isLoaded;
	int	hltps_mu30_vstar_;
	TBranch *hltps_mu30_vstar_branch;
	bool hltps_mu30_vstar_isLoaded;
	int	hltps_mu15_eta2p1_vstar_;
	TBranch *hltps_mu15_eta2p1_vstar_branch;
	bool hltps_mu15_eta2p1_vstar_isLoaded;
	int	hltps_mu24_eta2p1_vstar_;
	TBranch *hltps_mu24_eta2p1_vstar_branch;
	bool hltps_mu24_eta2p1_vstar_isLoaded;
	int	hltps_mu30_eta2p1_vstar_;
	TBranch *hltps_mu30_eta2p1_vstar_branch;
	bool hltps_mu30_eta2p1_vstar_isLoaded;
	int	hltps_mu8_Jet40_vstar_;
	TBranch *hltps_mu8_Jet40_vstar_branch;
	bool hltps_mu8_Jet40_vstar_isLoaded;
	int	hltps_isoMu20_eta2p1_vstar_;
	TBranch *hltps_isoMu20_eta2p1_vstar_branch;
	bool hltps_isoMu20_eta2p1_vstar_isLoaded;
	int	hltps_isoMu24_eta2p1_vstar_;
	TBranch *hltps_isoMu24_eta2p1_vstar_branch;
	bool hltps_isoMu24_eta2p1_vstar_isLoaded;
	int	hltps_isoMu30_eta2p1_vstar_;
	TBranch *hltps_isoMu30_eta2p1_vstar_branch;
	bool hltps_isoMu30_eta2p1_vstar_isLoaded;
	int	hltps_relIso1p0Mu17_vstar_;
	TBranch *hltps_relIso1p0Mu17_vstar_branch;
	bool hltps_relIso1p0Mu17_vstar_isLoaded;
	int	hltps_relIso1p0Mu5_vstar_;
	TBranch *hltps_relIso1p0Mu5_vstar_branch;
	bool hltps_relIso1p0Mu5_vstar_isLoaded;
	int	l1ps_mu5_vstar_;
	TBranch *l1ps_mu5_vstar_branch;
	bool l1ps_mu5_vstar_isLoaded;
	int	l1ps_mu8_vstar_;
	TBranch *l1ps_mu8_vstar_branch;
	bool l1ps_mu8_vstar_isLoaded;
	int	l1ps_mu12_vstar_;
	TBranch *l1ps_mu12_vstar_branch;
	bool l1ps_mu12_vstar_isLoaded;
	int	l1ps_mu17_vstar_;
	TBranch *l1ps_mu17_vstar_branch;
	bool l1ps_mu17_vstar_isLoaded;
	int	l1ps_mu15_eta2p1_vstar_;
	TBranch *l1ps_mu15_eta2p1_vstar_branch;
	bool l1ps_mu15_eta2p1_vstar_isLoaded;
	int	l1ps_mu24_eta2p1_vstar_;
	TBranch *l1ps_mu24_eta2p1_vstar_branch;
	bool l1ps_mu24_eta2p1_vstar_isLoaded;
	int	l1ps_mu30_eta2p1_vstar_;
	TBranch *l1ps_mu30_eta2p1_vstar_branch;
	bool l1ps_mu30_eta2p1_vstar_isLoaded;
	int	l1ps_isoMu20_eta2p1_vstar_;
	TBranch *l1ps_isoMu20_eta2p1_vstar_branch;
	bool l1ps_isoMu20_eta2p1_vstar_isLoaded;
	int	l1ps_isoMu24_eta2p1_vstar_;
	TBranch *l1ps_isoMu24_eta2p1_vstar_branch;
	bool l1ps_isoMu24_eta2p1_vstar_isLoaded;
	int	l1ps_isoMu30_eta2p1_vstar_;
	TBranch *l1ps_isoMu30_eta2p1_vstar_branch;
	bool l1ps_isoMu30_eta2p1_vstar_isLoaded;
	int	l1ps_relIso1p0Mu17_vstar_;
	TBranch *l1ps_relIso1p0Mu17_vstar_branch;
	bool l1ps_relIso1p0Mu17_vstar_isLoaded;
	int	l1ps_relIso1p0Mu5_vstar_;
	TBranch *l1ps_relIso1p0Mu5_vstar_branch;
	bool l1ps_relIso1p0Mu5_vstar_isLoaded;
	float	ptj1_;
	TBranch *ptj1_branch;
	bool ptj1_isLoaded;
	int	nj1_;
	TBranch *nj1_branch;
	bool nj1_isLoaded;
	float	ptj1_b2b_;
	TBranch *ptj1_b2b_branch;
	bool ptj1_b2b_isLoaded;
	float	dphij1_b2b_;
	TBranch *dphij1_b2b_branch;
	bool dphij1_b2b_isLoaded;
	float	ptpfj1_;
	TBranch *ptpfj1_branch;
	bool ptpfj1_isLoaded;
	int	npfj1_;
	TBranch *npfj1_branch;
	bool npfj1_isLoaded;
	float	ptpfj1_b2b_;
	TBranch *ptpfj1_b2b_branch;
	bool ptpfj1_b2b_isLoaded;
	float	dphipfj1_b2b_;
	TBranch *dphipfj1_b2b_branch;
	bool dphipfj1_b2b_isLoaded;
	float	ptpfcj1_;
	TBranch *ptpfcj1_branch;
	bool ptpfcj1_isLoaded;
	int	npfcj1_;
	TBranch *npfcj1_branch;
	bool npfcj1_isLoaded;
	float	ptpfcj1_b2b_;
	TBranch *ptpfcj1_b2b_branch;
	bool ptpfcj1_b2b_isLoaded;
	float	dphipfcj1_b2b_;
	TBranch *dphipfcj1_b2b_branch;
	bool dphipfcj1_b2b_isLoaded;
	bool	btagpfc_;
	TBranch *btagpfc_branch;
	bool btagpfc_isLoaded;
	float	emfpfcL1Fj1_;
	TBranch *emfpfcL1Fj1_branch;
	bool emfpfcL1Fj1_isLoaded;
	float	ptpfcL1Fj1_;
	TBranch *ptpfcL1Fj1_branch;
	bool ptpfcL1Fj1_isLoaded;
	float	dphipfcL1Fj1_;
	TBranch *dphipfcL1Fj1_branch;
	bool dphipfcL1Fj1_isLoaded;
	int	npfcL1Fj1_;
	TBranch *npfcL1Fj1_branch;
	bool npfcL1Fj1_isLoaded;
	int	npfc30L1Fj1_;
	TBranch *npfc30L1Fj1_branch;
	bool npfc30L1Fj1_isLoaded;
	int	npfc40L1Fj1_;
	TBranch *npfc40L1Fj1_branch;
	bool npfc40L1Fj1_isLoaded;
	float	ptpfcL1Fj1_b2b_;
	TBranch *ptpfcL1Fj1_b2b_branch;
	bool ptpfcL1Fj1_b2b_isLoaded;
	float	dphipfcL1Fj1_b2b_;
	TBranch *dphipfcL1Fj1_b2b_branch;
	bool dphipfcL1Fj1_b2b_isLoaded;
	bool	btagpfcL1F_;
	TBranch *btagpfcL1F_branch;
	bool btagpfcL1F_isLoaded;
	float	emfpfcL1Fj1res_;
	TBranch *emfpfcL1Fj1res_branch;
	bool emfpfcL1Fj1res_isLoaded;
	float	ptpfcL1Fj1res_;
	TBranch *ptpfcL1Fj1res_branch;
	bool ptpfcL1Fj1res_isLoaded;
	float	dphipfcL1Fj1res_;
	TBranch *dphipfcL1Fj1res_branch;
	bool dphipfcL1Fj1res_isLoaded;
	int	npfcL1Fj1res_;
	TBranch *npfcL1Fj1res_branch;
	bool npfcL1Fj1res_isLoaded;
	int	npfc30L1Fj1res_;
	TBranch *npfc30L1Fj1res_branch;
	bool npfc30L1Fj1res_isLoaded;
	int	npfc40L1Fj1res_;
	TBranch *npfc40L1Fj1res_branch;
	bool npfc40L1Fj1res_isLoaded;
	float	ptpfcL1Fj1res_b2b_;
	TBranch *ptpfcL1Fj1res_b2b_branch;
	bool ptpfcL1Fj1res_b2b_isLoaded;
	float	dphipfcL1Fj1res_b2b_;
	TBranch *dphipfcL1Fj1res_b2b_branch;
	bool dphipfcL1Fj1res_b2b_isLoaded;
	bool	btagpfcL1Fres_;
	TBranch *btagpfcL1Fres_branch;
	bool btagpfcL1Fres_isLoaded;
	float	ptbtagpfcL1Fj1_;
	TBranch *ptbtagpfcL1Fj1_branch;
	bool ptbtagpfcL1Fj1_isLoaded;
	float	dphibtagpfcL1Fj1_;
	TBranch *dphibtagpfcL1Fj1_branch;
	bool dphibtagpfcL1Fj1_isLoaded;
	float	ptbtagpfcL1Fj1res_;
	TBranch *ptbtagpfcL1Fj1res_branch;
	bool ptbtagpfcL1Fj1res_isLoaded;
	float	dphibtagpfcL1Fj1res_;
	TBranch *dphibtagpfcL1Fj1res_branch;
	bool dphibtagpfcL1Fj1res_isLoaded;
	int	nbjet_;
	TBranch *nbjet_branch;
	bool nbjet_isLoaded;
	float	dRNear_;
	TBranch *dRNear_branch;
	bool dRNear_isLoaded;
	float	dRFar_;
	TBranch *dRFar_branch;
	bool dRFar_isLoaded;
	int	nbpfcjet_;
	TBranch *nbpfcjet_branch;
	bool nbpfcjet_isLoaded;
	float	dRpfcNear_;
	TBranch *dRpfcNear_branch;
	bool dRpfcNear_isLoaded;
	float	dRpfcFar_;
	TBranch *dRpfcFar_branch;
	bool dRpfcFar_isLoaded;
	float	rho_;
	TBranch *rho_branch;
	bool rho_isLoaded;
public: 
void Init(TTree *tree) {
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
	weight_branch = 0;
	if (tree->GetBranch("weight") != 0) {
		weight_branch = tree->GetBranch("weight");
		weight_branch->SetAddress(&weight_);
	}
	pu_nPUvertices_branch = 0;
	if (tree->GetBranch("pu_nPUvertices") != 0) {
		pu_nPUvertices_branch = tree->GetBranch("pu_nPUvertices");
		pu_nPUvertices_branch->SetAddress(&pu_nPUvertices_);
	}
	evt_nvtxs_branch = 0;
	if (tree->GetBranch("evt_nvtxs") != 0) {
		evt_nvtxs_branch = tree->GetBranch("evt_nvtxs");
		evt_nvtxs_branch->SetAddress(&evt_nvtxs_);
	}
	nFOels_branch = 0;
	if (tree->GetBranch("nFOels") != 0) {
		nFOels_branch = tree->GetBranch("nFOels");
		nFOels_branch->SetAddress(&nFOels_);
	}
	nFOmus_branch = 0;
	if (tree->GetBranch("nFOmus") != 0) {
		nFOmus_branch = tree->GetBranch("nFOmus");
		nFOmus_branch->SetAddress(&nFOmus_);
	}
	ngsfs_branch = 0;
	if (tree->GetBranch("ngsfs") != 0) {
		ngsfs_branch = tree->GetBranch("ngsfs");
		ngsfs_branch->SetAddress(&ngsfs_);
	}
	nmus_branch = 0;
	if (tree->GetBranch("nmus") != 0) {
		nmus_branch = tree->GetBranch("nmus");
		nmus_branch->SetAddress(&nmus_);
	}
	foel_id_branch = 0;
	if (tree->GetBranch("foel_id") != 0) {
		foel_id_branch = tree->GetBranch("foel_id");
		foel_id_branch->SetAddress(&foel_id_);
	}
	fomu_id_branch = 0;
	if (tree->GetBranch("fomu_id") != 0) {
		fomu_id_branch = tree->GetBranch("fomu_id");
		fomu_id_branch->SetAddress(&fomu_id_);
	}
	foel_mass_branch = 0;
	if (tree->GetBranch("foel_mass") != 0) {
		foel_mass_branch = tree->GetBranch("foel_mass");
		foel_mass_branch->SetAddress(&foel_mass_);
	}
	fomu_mass_branch = 0;
	if (tree->GetBranch("fomu_mass") != 0) {
		fomu_mass_branch = tree->GetBranch("fomu_mass");
		fomu_mass_branch->SetAddress(&fomu_mass_);
	}
	pt_branch = 0;
	if (tree->GetBranch("pt") != 0) {
		pt_branch = tree->GetBranch("pt");
		pt_branch->SetAddress(&pt_);
	}
	eta_branch = 0;
	if (tree->GetBranch("eta") != 0) {
		eta_branch = tree->GetBranch("eta");
		eta_branch->SetAddress(&eta_);
	}
	sceta_branch = 0;
	if (tree->GetBranch("sceta") != 0) {
		sceta_branch = tree->GetBranch("sceta");
		sceta_branch->SetAddress(&sceta_);
	}
	phi_branch = 0;
	if (tree->GetBranch("phi") != 0) {
		phi_branch = tree->GetBranch("phi");
		phi_branch->SetAddress(&phi_);
	}
	scet_branch = 0;
	if (tree->GetBranch("scet") != 0) {
		scet_branch = tree->GetBranch("scet");
		scet_branch->SetAddress(&scet_);
	}
	hoe_branch = 0;
	if (tree->GetBranch("hoe") != 0) {
		hoe_branch = tree->GetBranch("hoe");
		hoe_branch->SetAddress(&hoe_);
	}
	pfmet_branch = 0;
	if (tree->GetBranch("pfmet") != 0) {
		pfmet_branch = tree->GetBranch("pfmet");
		pfmet_branch->SetAddress(&pfmet_);
	}
	pfmetphi_branch = 0;
	if (tree->GetBranch("pfmetphi") != 0) {
		pfmetphi_branch = tree->GetBranch("pfmetphi");
		pfmetphi_branch->SetAddress(&pfmetphi_);
	}
	iso_branch = 0;
	if (tree->GetBranch("iso") != 0) {
		iso_branch = tree->GetBranch("iso");
		iso_branch->SetAddress(&iso_);
	}
	iso_nps_branch = 0;
	if (tree->GetBranch("iso_nps") != 0) {
		iso_nps_branch = tree->GetBranch("iso_nps");
		iso_nps_branch->SetAddress(&iso_nps_);
	}
	trck_iso_branch = 0;
	if (tree->GetBranch("trck_iso") != 0) {
		trck_iso_branch = tree->GetBranch("trck_iso");
		trck_iso_branch->SetAddress(&trck_iso_);
	}
	ecal_iso_branch = 0;
	if (tree->GetBranch("ecal_iso") != 0) {
		ecal_iso_branch = tree->GetBranch("ecal_iso");
		ecal_iso_branch->SetAddress(&ecal_iso_);
	}
	ecal_iso_nps_branch = 0;
	if (tree->GetBranch("ecal_iso_nps") != 0) {
		ecal_iso_nps_branch = tree->GetBranch("ecal_iso_nps");
		ecal_iso_nps_branch->SetAddress(&ecal_iso_nps_);
	}
	hcal_iso_branch = 0;
	if (tree->GetBranch("hcal_iso") != 0) {
		hcal_iso_branch = tree->GetBranch("hcal_iso");
		hcal_iso_branch->SetAddress(&hcal_iso_);
	}
	pfiso03_branch = 0;
	if (tree->GetBranch("pfiso03") != 0) {
		pfiso03_branch = tree->GetBranch("pfiso03");
		pfiso03_branch->SetAddress(&pfiso03_);
	}
	ch_pfiso03_branch = 0;
	if (tree->GetBranch("ch_pfiso03") != 0) {
		ch_pfiso03_branch = tree->GetBranch("ch_pfiso03");
		ch_pfiso03_branch->SetAddress(&ch_pfiso03_);
	}
	nh_pfiso03_branch = 0;
	if (tree->GetBranch("nh_pfiso03") != 0) {
		nh_pfiso03_branch = tree->GetBranch("nh_pfiso03");
		nh_pfiso03_branch->SetAddress(&nh_pfiso03_);
	}
	em_pfiso03_branch = 0;
	if (tree->GetBranch("em_pfiso03") != 0) {
		em_pfiso03_branch = tree->GetBranch("em_pfiso03");
		em_pfiso03_branch->SetAddress(&em_pfiso03_);
	}
	pfiso04_branch = 0;
	if (tree->GetBranch("pfiso04") != 0) {
		pfiso04_branch = tree->GetBranch("pfiso04");
		pfiso04_branch->SetAddress(&pfiso04_);
	}
	ch_pfiso04_branch = 0;
	if (tree->GetBranch("ch_pfiso04") != 0) {
		ch_pfiso04_branch = tree->GetBranch("ch_pfiso04");
		ch_pfiso04_branch->SetAddress(&ch_pfiso04_);
	}
	nh_pfiso04_branch = 0;
	if (tree->GetBranch("nh_pfiso04") != 0) {
		nh_pfiso04_branch = tree->GetBranch("nh_pfiso04");
		nh_pfiso04_branch->SetAddress(&nh_pfiso04_);
	}
	em_pfiso04_branch = 0;
	if (tree->GetBranch("em_pfiso04") != 0) {
		em_pfiso04_branch = tree->GetBranch("em_pfiso04");
		em_pfiso04_branch->SetAddress(&em_pfiso04_);
	}
	pfpupt03_branch = 0;
	if (tree->GetBranch("pfpupt03") != 0) {
		pfpupt03_branch = tree->GetBranch("pfpupt03");
		pfpupt03_branch->SetAddress(&pfpupt03_);
	}
	pfpupt04_branch = 0;
	if (tree->GetBranch("pfpupt04") != 0) {
		pfpupt04_branch = tree->GetBranch("pfpupt04");
		pfpupt04_branch->SetAddress(&pfpupt04_);
	}
	cpfiso03_rho_branch = 0;
	if (tree->GetBranch("cpfiso03_rho") != 0) {
		cpfiso03_rho_branch = tree->GetBranch("cpfiso03_rho");
		cpfiso03_rho_branch->SetAddress(&cpfiso03_rho_);
	}
	cpfiso03_db_branch = 0;
	if (tree->GetBranch("cpfiso03_db") != 0) {
		cpfiso03_db_branch = tree->GetBranch("cpfiso03_db");
		cpfiso03_db_branch->SetAddress(&cpfiso03_db_);
	}
	id_branch = 0;
	if (tree->GetBranch("id") != 0) {
		id_branch = tree->GetBranch("id");
		id_branch->SetAddress(&id_);
	}
	closestMuon_branch = 0;
	if (tree->GetBranch("closestMuon") != 0) {
		closestMuon_branch = tree->GetBranch("closestMuon");
		closestMuon_branch->SetAddress(&closestMuon_);
	}
	el_id_sieie_branch = 0;
	if (tree->GetBranch("el_id_sieie") != 0) {
		el_id_sieie_branch = tree->GetBranch("el_id_sieie");
		el_id_sieie_branch->SetAddress(&el_id_sieie_);
	}
	el_id_detain_branch = 0;
	if (tree->GetBranch("el_id_detain") != 0) {
		el_id_detain_branch = tree->GetBranch("el_id_detain");
		el_id_detain_branch->SetAddress(&el_id_detain_);
	}
	el_id_dphiin_branch = 0;
	if (tree->GetBranch("el_id_dphiin") != 0) {
		el_id_dphiin_branch = tree->GetBranch("el_id_dphiin");
		el_id_dphiin_branch->SetAddress(&el_id_dphiin_);
	}
	el_id_smurfV5_branch = 0;
	if (tree->GetBranch("el_id_smurfV5") != 0) {
		el_id_smurfV5_branch = tree->GetBranch("el_id_smurfV5");
		el_id_smurfV5_branch->SetAddress(&el_id_smurfV5_);
	}
	el_id_vbtf80_branch = 0;
	if (tree->GetBranch("el_id_vbtf80") != 0) {
		el_id_vbtf80_branch = tree->GetBranch("el_id_vbtf80");
		el_id_vbtf80_branch->SetAddress(&el_id_vbtf80_);
	}
	el_id_vbtf90_branch = 0;
	if (tree->GetBranch("el_id_vbtf90") != 0) {
		el_id_vbtf90_branch = tree->GetBranch("el_id_vbtf90");
		el_id_vbtf90_branch->SetAddress(&el_id_vbtf90_);
	}
	el_effarea_branch = 0;
	if (tree->GetBranch("el_effarea") != 0) {
		el_effarea_branch = tree->GetBranch("el_effarea");
		el_effarea_branch->SetAddress(&el_effarea_);
	}
	mu_effarea03_branch = 0;
	if (tree->GetBranch("mu_effarea03") != 0) {
		mu_effarea03_branch = tree->GetBranch("mu_effarea03");
		mu_effarea03_branch->SetAddress(&mu_effarea03_);
	}
	mu_nh_effarea03_branch = 0;
	if (tree->GetBranch("mu_nh_effarea03") != 0) {
		mu_nh_effarea03_branch = tree->GetBranch("mu_nh_effarea03");
		mu_nh_effarea03_branch->SetAddress(&mu_nh_effarea03_);
	}
	mu_em_effarea03_branch = 0;
	if (tree->GetBranch("mu_em_effarea03") != 0) {
		mu_em_effarea03_branch = tree->GetBranch("mu_em_effarea03");
		mu_em_effarea03_branch->SetAddress(&mu_em_effarea03_);
	}
	mu_effarea03_tight_branch = 0;
	if (tree->GetBranch("mu_effarea03_tight") != 0) {
		mu_effarea03_tight_branch = tree->GetBranch("mu_effarea03_tight");
		mu_effarea03_tight_branch->SetAddress(&mu_effarea03_tight_);
	}
	mu_nh_effarea03_tight_branch = 0;
	if (tree->GetBranch("mu_nh_effarea03_tight") != 0) {
		mu_nh_effarea03_tight_branch = tree->GetBranch("mu_nh_effarea03_tight");
		mu_nh_effarea03_tight_branch->SetAddress(&mu_nh_effarea03_tight_);
	}
	mu_em_effarea03_tight_branch = 0;
	if (tree->GetBranch("mu_em_effarea03_tight") != 0) {
		mu_em_effarea03_tight_branch = tree->GetBranch("mu_em_effarea03_tight");
		mu_em_effarea03_tight_branch->SetAddress(&mu_em_effarea03_tight_);
	}
	mu_effarea04_branch = 0;
	if (tree->GetBranch("mu_effarea04") != 0) {
		mu_effarea04_branch = tree->GetBranch("mu_effarea04");
		mu_effarea04_branch->SetAddress(&mu_effarea04_);
	}
	mu_nh_effarea04_branch = 0;
	if (tree->GetBranch("mu_nh_effarea04") != 0) {
		mu_nh_effarea04_branch = tree->GetBranch("mu_nh_effarea04");
		mu_nh_effarea04_branch->SetAddress(&mu_nh_effarea04_);
	}
	mu_em_effarea04_branch = 0;
	if (tree->GetBranch("mu_em_effarea04") != 0) {
		mu_em_effarea04_branch = tree->GetBranch("mu_em_effarea04");
		mu_em_effarea04_branch->SetAddress(&mu_em_effarea04_);
	}
	mu_effarea04_tight_branch = 0;
	if (tree->GetBranch("mu_effarea04_tight") != 0) {
		mu_effarea04_tight_branch = tree->GetBranch("mu_effarea04_tight");
		mu_effarea04_tight_branch->SetAddress(&mu_effarea04_tight_);
	}
	mu_nh_effarea04_tight_branch = 0;
	if (tree->GetBranch("mu_nh_effarea04_tight") != 0) {
		mu_nh_effarea04_tight_branch = tree->GetBranch("mu_nh_effarea04_tight");
		mu_nh_effarea04_tight_branch->SetAddress(&mu_nh_effarea04_tight_);
	}
	mu_em_effarea04_tight_branch = 0;
	if (tree->GetBranch("mu_em_effarea04_tight") != 0) {
		mu_em_effarea04_tight_branch = tree->GetBranch("mu_em_effarea04_tight");
		mu_em_effarea04_tight_branch->SetAddress(&mu_em_effarea04_tight_);
	}
	conv0MissHits_branch = 0;
	if (tree->GetBranch("conv0MissHits") != 0) {
		conv0MissHits_branch = tree->GetBranch("conv0MissHits");
		conv0MissHits_branch->SetAddress(&conv0MissHits_);
	}
	convHitPattern_branch = 0;
	if (tree->GetBranch("convHitPattern") != 0) {
		convHitPattern_branch = tree->GetBranch("convHitPattern");
		convHitPattern_branch->SetAddress(&convHitPattern_);
	}
	convPartnerTrack_branch = 0;
	if (tree->GetBranch("convPartnerTrack") != 0) {
		convPartnerTrack_branch = tree->GetBranch("convPartnerTrack");
		convPartnerTrack_branch->SetAddress(&convPartnerTrack_);
	}
	convMIT_branch = 0;
	if (tree->GetBranch("convMIT") != 0) {
		convMIT_branch = tree->GetBranch("convMIT");
		convMIT_branch->SetAddress(&convMIT_);
	}
	mt_branch = 0;
	if (tree->GetBranch("mt") != 0) {
		mt_branch = tree->GetBranch("mt");
		mt_branch->SetAddress(&mt_);
	}
	pfmt_branch = 0;
	if (tree->GetBranch("pfmt") != 0) {
		pfmt_branch = tree->GetBranch("pfmt");
		pfmt_branch->SetAddress(&pfmt_);
	}
	q3_branch = 0;
	if (tree->GetBranch("q3") != 0) {
		q3_branch = tree->GetBranch("q3");
		q3_branch->SetAddress(&q3_);
	}
	els_exp_innerlayers_branch = 0;
	if (tree->GetBranch("els_exp_innerlayers") != 0) {
		els_exp_innerlayers_branch = tree->GetBranch("els_exp_innerlayers");
		els_exp_innerlayers_branch->SetAddress(&els_exp_innerlayers_);
	}
	d0PV_wwV1_branch = 0;
	if (tree->GetBranch("d0PV_wwV1") != 0) {
		d0PV_wwV1_branch = tree->GetBranch("d0PV_wwV1");
		d0PV_wwV1_branch->SetAddress(&d0PV_wwV1_);
	}
	dzPV_wwV1_branch = 0;
	if (tree->GetBranch("dzPV_wwV1") != 0) {
		dzPV_wwV1_branch = tree->GetBranch("dzPV_wwV1");
		dzPV_wwV1_branch->SetAddress(&dzPV_wwV1_);
	}
	ht_calo_branch = 0;
	if (tree->GetBranch("ht_calo") != 0) {
		ht_calo_branch = tree->GetBranch("ht_calo");
		ht_calo_branch->SetAddress(&ht_calo_);
	}
	ht_calo_L2L3_branch = 0;
	if (tree->GetBranch("ht_calo_L2L3") != 0) {
		ht_calo_L2L3_branch = tree->GetBranch("ht_calo_L2L3");
		ht_calo_L2L3_branch->SetAddress(&ht_calo_L2L3_);
	}
	ht_pf_branch = 0;
	if (tree->GetBranch("ht_pf") != 0) {
		ht_pf_branch = tree->GetBranch("ht_pf");
		ht_pf_branch->SetAddress(&ht_pf_);
	}
	ht_pf_L2L3_branch = 0;
	if (tree->GetBranch("ht_pf_L2L3") != 0) {
		ht_pf_L2L3_branch = tree->GetBranch("ht_pf_L2L3");
		ht_pf_L2L3_branch->SetAddress(&ht_pf_L2L3_);
	}
	ht_pf_L1FastL2L3_branch = 0;
	if (tree->GetBranch("ht_pf_L1FastL2L3") != 0) {
		ht_pf_L1FastL2L3_branch = tree->GetBranch("ht_pf_L1FastL2L3");
		ht_pf_L1FastL2L3_branch->SetAddress(&ht_pf_L1FastL2L3_);
	}
	mcid_branch = 0;
	if (tree->GetBranch("mcid") != 0) {
		mcid_branch = tree->GetBranch("mcid");
		mcid_branch->SetAddress(&mcid_);
	}
	mcmotherid_branch = 0;
	if (tree->GetBranch("mcmotherid") != 0) {
		mcmotherid_branch = tree->GetBranch("mcmotherid");
		mcmotherid_branch->SetAddress(&mcmotherid_);
	}
	mc3id_branch = 0;
	if (tree->GetBranch("mc3id") != 0) {
		mc3id_branch = tree->GetBranch("mc3id");
		mc3id_branch->SetAddress(&mc3id_);
	}
	mc3pt_branch = 0;
	if (tree->GetBranch("mc3pt") != 0) {
		mc3pt_branch = tree->GetBranch("mc3pt");
		mc3pt_branch->SetAddress(&mc3pt_);
	}
	mc3dr_branch = 0;
	if (tree->GetBranch("mc3dr") != 0) {
		mc3dr_branch = tree->GetBranch("mc3dr");
		mc3dr_branch->SetAddress(&mc3dr_);
	}
	leptonIsFromW_branch = 0;
	if (tree->GetBranch("leptonIsFromW") != 0) {
		leptonIsFromW_branch = tree->GetBranch("leptonIsFromW");
		leptonIsFromW_branch->SetAddress(&leptonIsFromW_);
	}
	mu_isCosmic_branch = 0;
	if (tree->GetBranch("mu_isCosmic") != 0) {
		mu_isCosmic_branch = tree->GetBranch("mu_isCosmic");
		mu_isCosmic_branch->SetAddress(&mu_isCosmic_);
	}
	mz_fo_gsf_branch = 0;
	if (tree->GetBranch("mz_fo_gsf") != 0) {
		mz_fo_gsf_branch = tree->GetBranch("mz_fo_gsf");
		mz_fo_gsf_branch->SetAddress(&mz_fo_gsf_);
	}
	mz_gsf_iso_branch = 0;
	if (tree->GetBranch("mz_gsf_iso") != 0) {
		mz_gsf_iso_branch = tree->GetBranch("mz_gsf_iso");
		mz_gsf_iso_branch->SetAddress(&mz_gsf_iso_);
	}
	mz_fo_ctf_branch = 0;
	if (tree->GetBranch("mz_fo_ctf") != 0) {
		mz_fo_ctf_branch = tree->GetBranch("mz_fo_ctf");
		mz_fo_ctf_branch->SetAddress(&mz_fo_ctf_);
	}
	mz_ctf_iso_branch = 0;
	if (tree->GetBranch("mz_ctf_iso") != 0) {
		mz_ctf_iso_branch = tree->GetBranch("mz_ctf_iso");
		mz_ctf_iso_branch->SetAddress(&mz_ctf_iso_);
	}
	mupsilon_fo_mu_branch = 0;
	if (tree->GetBranch("mupsilon_fo_mu") != 0) {
		mupsilon_fo_mu_branch = tree->GetBranch("mupsilon_fo_mu");
		mupsilon_fo_mu_branch->SetAddress(&mupsilon_fo_mu_);
	}
	mupsilon_mu_iso_branch = 0;
	if (tree->GetBranch("mupsilon_mu_iso") != 0) {
		mupsilon_mu_iso_branch = tree->GetBranch("mupsilon_mu_iso");
		mupsilon_mu_iso_branch->SetAddress(&mupsilon_mu_iso_);
	}
	num_el_ssV7_branch = 0;
	if (tree->GetBranch("num_el_ssV7") != 0) {
		num_el_ssV7_branch = tree->GetBranch("num_el_ssV7");
		num_el_ssV7_branch->SetAddress(&num_el_ssV7_);
	}
	num_el_ssV7_noIso_branch = 0;
	if (tree->GetBranch("num_el_ssV7_noIso") != 0) {
		num_el_ssV7_noIso_branch = tree->GetBranch("num_el_ssV7_noIso");
		num_el_ssV7_noIso_branch->SetAddress(&num_el_ssV7_noIso_);
	}
	v1_el_ssV7_branch = 0;
	if (tree->GetBranch("v1_el_ssV7") != 0) {
		v1_el_ssV7_branch = tree->GetBranch("v1_el_ssV7");
		v1_el_ssV7_branch->SetAddress(&v1_el_ssV7_);
	}
	v2_el_ssV7_branch = 0;
	if (tree->GetBranch("v2_el_ssV7") != 0) {
		v2_el_ssV7_branch = tree->GetBranch("v2_el_ssV7");
		v2_el_ssV7_branch->SetAddress(&v2_el_ssV7_);
	}
	v3_el_ssV7_branch = 0;
	if (tree->GetBranch("v3_el_ssV7") != 0) {
		v3_el_ssV7_branch = tree->GetBranch("v3_el_ssV7");
		v3_el_ssV7_branch->SetAddress(&v3_el_ssV7_);
	}
	num_mu_ssV5_branch = 0;
	if (tree->GetBranch("num_mu_ssV5") != 0) {
		num_mu_ssV5_branch = tree->GetBranch("num_mu_ssV5");
		num_mu_ssV5_branch->SetAddress(&num_mu_ssV5_);
	}
	num_mu_ssV5_noIso_branch = 0;
	if (tree->GetBranch("num_mu_ssV5_noIso") != 0) {
		num_mu_ssV5_noIso_branch = tree->GetBranch("num_mu_ssV5_noIso");
		num_mu_ssV5_noIso_branch->SetAddress(&num_mu_ssV5_noIso_);
	}
	fo_mu_ssV5_branch = 0;
	if (tree->GetBranch("fo_mu_ssV5") != 0) {
		fo_mu_ssV5_branch = tree->GetBranch("fo_mu_ssV5");
		fo_mu_ssV5_branch->SetAddress(&fo_mu_ssV5_);
	}
	fo_mu_ssV5_noIso_branch = 0;
	if (tree->GetBranch("fo_mu_ssV5_noIso") != 0) {
		fo_mu_ssV5_noIso_branch = tree->GetBranch("fo_mu_ssV5_noIso");
		fo_mu_ssV5_noIso_branch->SetAddress(&fo_mu_ssV5_noIso_);
	}
	num_el_ssV6_branch = 0;
	if (tree->GetBranch("num_el_ssV6") != 0) {
		num_el_ssV6_branch = tree->GetBranch("num_el_ssV6");
		num_el_ssV6_branch->SetAddress(&num_el_ssV6_);
	}
	num_el_ssV6_noIso_branch = 0;
	if (tree->GetBranch("num_el_ssV6_noIso") != 0) {
		num_el_ssV6_noIso_branch = tree->GetBranch("num_el_ssV6_noIso");
		num_el_ssV6_noIso_branch->SetAddress(&num_el_ssV6_noIso_);
	}
	v1_el_ssV6_branch = 0;
	if (tree->GetBranch("v1_el_ssV6") != 0) {
		v1_el_ssV6_branch = tree->GetBranch("v1_el_ssV6");
		v1_el_ssV6_branch->SetAddress(&v1_el_ssV6_);
	}
	v2_el_ssV6_branch = 0;
	if (tree->GetBranch("v2_el_ssV6") != 0) {
		v2_el_ssV6_branch = tree->GetBranch("v2_el_ssV6");
		v2_el_ssV6_branch->SetAddress(&v2_el_ssV6_);
	}
	v3_el_ssV6_branch = 0;
	if (tree->GetBranch("v3_el_ssV6") != 0) {
		v3_el_ssV6_branch = tree->GetBranch("v3_el_ssV6");
		v3_el_ssV6_branch->SetAddress(&v3_el_ssV6_);
	}
	numNomSSv4_branch = 0;
	if (tree->GetBranch("numNomSSv4") != 0) {
		numNomSSv4_branch = tree->GetBranch("numNomSSv4");
		numNomSSv4_branch->SetAddress(&numNomSSv4_);
	}
	numNomSSv4noIso_branch = 0;
	if (tree->GetBranch("numNomSSv4noIso") != 0) {
		numNomSSv4noIso_branch = tree->GetBranch("numNomSSv4noIso");
		numNomSSv4noIso_branch->SetAddress(&numNomSSv4noIso_);
	}
	fo_mussV4_04_branch = 0;
	if (tree->GetBranch("fo_mussV4_04") != 0) {
		fo_mussV4_04_branch = tree->GetBranch("fo_mussV4_04");
		fo_mussV4_04_branch->SetAddress(&fo_mussV4_04_);
	}
	fo_mussV4_noIso_branch = 0;
	if (tree->GetBranch("fo_mussV4_noIso") != 0) {
		fo_mussV4_noIso_branch = tree->GetBranch("fo_mussV4_noIso");
		fo_mussV4_noIso_branch->SetAddress(&fo_mussV4_noIso_);
	}
	num_el_smurfV6_branch = 0;
	if (tree->GetBranch("num_el_smurfV6") != 0) {
		num_el_smurfV6_branch = tree->GetBranch("num_el_smurfV6");
		num_el_smurfV6_branch->SetAddress(&num_el_smurfV6_);
	}
	num_el_smurfV6lh_branch = 0;
	if (tree->GetBranch("num_el_smurfV6lh") != 0) {
		num_el_smurfV6lh_branch = tree->GetBranch("num_el_smurfV6lh");
		num_el_smurfV6lh_branch->SetAddress(&num_el_smurfV6lh_);
	}
	v1_el_smurfV1_branch = 0;
	if (tree->GetBranch("v1_el_smurfV1") != 0) {
		v1_el_smurfV1_branch = tree->GetBranch("v1_el_smurfV1");
		v1_el_smurfV1_branch->SetAddress(&v1_el_smurfV1_);
	}
	v2_el_smurfV1_branch = 0;
	if (tree->GetBranch("v2_el_smurfV1") != 0) {
		v2_el_smurfV1_branch = tree->GetBranch("v2_el_smurfV1");
		v2_el_smurfV1_branch->SetAddress(&v2_el_smurfV1_);
	}
	v3_el_smurfV1_branch = 0;
	if (tree->GetBranch("v3_el_smurfV1") != 0) {
		v3_el_smurfV1_branch = tree->GetBranch("v3_el_smurfV1");
		v3_el_smurfV1_branch->SetAddress(&v3_el_smurfV1_);
	}
	v4_el_smurfV1_branch = 0;
	if (tree->GetBranch("v4_el_smurfV1") != 0) {
		v4_el_smurfV1_branch = tree->GetBranch("v4_el_smurfV1");
		v4_el_smurfV1_branch->SetAddress(&v4_el_smurfV1_);
	}
	num_mu_smurfV6_branch = 0;
	if (tree->GetBranch("num_mu_smurfV6") != 0) {
		num_mu_smurfV6_branch = tree->GetBranch("num_mu_smurfV6");
		num_mu_smurfV6_branch->SetAddress(&num_mu_smurfV6_);
	}
	fo_mu_smurf_04_branch = 0;
	if (tree->GetBranch("fo_mu_smurf_04") != 0) {
		fo_mu_smurf_04_branch = tree->GetBranch("fo_mu_smurf_04");
		fo_mu_smurf_04_branch->SetAddress(&fo_mu_smurf_04_);
	}
	fo_mu_smurf_10_branch = 0;
	if (tree->GetBranch("fo_mu_smurf_10") != 0) {
		fo_mu_smurf_10_branch = tree->GetBranch("fo_mu_smurf_10");
		fo_mu_smurf_10_branch->SetAddress(&fo_mu_smurf_10_);
	}
	num_el_OSV2_branch = 0;
	if (tree->GetBranch("num_el_OSV2") != 0) {
		num_el_OSV2_branch = tree->GetBranch("num_el_OSV2");
		num_el_OSV2_branch->SetAddress(&num_el_OSV2_);
	}
	num_mu_OSGV2_branch = 0;
	if (tree->GetBranch("num_mu_OSGV2") != 0) {
		num_mu_OSGV2_branch = tree->GetBranch("num_mu_OSGV2");
		num_mu_OSGV2_branch->SetAddress(&num_mu_OSGV2_);
	}
	num_mu_OSZV2_branch = 0;
	if (tree->GetBranch("num_mu_OSZV2") != 0) {
		num_mu_OSZV2_branch = tree->GetBranch("num_mu_OSZV2");
		num_mu_OSZV2_branch->SetAddress(&num_mu_OSZV2_);
	}
	fo_el_OSV2_branch = 0;
	if (tree->GetBranch("fo_el_OSV2") != 0) {
		fo_el_OSV2_branch = tree->GetBranch("fo_el_OSV2");
		fo_el_OSV2_branch->SetAddress(&fo_el_OSV2_);
	}
	fo_mu_OSGV2_branch = 0;
	if (tree->GetBranch("fo_mu_OSGV2") != 0) {
		fo_mu_OSGV2_branch = tree->GetBranch("fo_mu_OSGV2");
		fo_mu_OSGV2_branch->SetAddress(&fo_mu_OSGV2_);
	}
	num_el_OSV3_branch = 0;
	if (tree->GetBranch("num_el_OSV3") != 0) {
		num_el_OSV3_branch = tree->GetBranch("num_el_OSV3");
		num_el_OSV3_branch->SetAddress(&num_el_OSV3_);
	}
	num_mu_OSGV3_branch = 0;
	if (tree->GetBranch("num_mu_OSGV3") != 0) {
		num_mu_OSGV3_branch = tree->GetBranch("num_mu_OSGV3");
		num_mu_OSGV3_branch->SetAddress(&num_mu_OSGV3_);
	}
	fo_el_OSV3_branch = 0;
	if (tree->GetBranch("fo_el_OSV3") != 0) {
		fo_el_OSV3_branch = tree->GetBranch("fo_el_OSV3");
		fo_el_OSV3_branch->SetAddress(&fo_el_OSV3_);
	}
	fo_mu_OSGV3_branch = 0;
	if (tree->GetBranch("fo_mu_OSGV3") != 0) {
		fo_mu_OSGV3_branch = tree->GetBranch("fo_mu_OSGV3");
		fo_mu_OSGV3_branch->SetAddress(&fo_mu_OSGV3_);
	}
	ele8_vstar_branch = 0;
	if (tree->GetBranch("ele8_vstar") != 0) {
		ele8_vstar_branch = tree->GetBranch("ele8_vstar");
		ele8_vstar_branch->SetAddress(&ele8_vstar_);
	}
	ele8_CaloIdL_TrkIdVL_vstar_branch = 0;
	if (tree->GetBranch("ele8_CaloIdL_TrkIdVL_vstar") != 0) {
		ele8_CaloIdL_TrkIdVL_vstar_branch = tree->GetBranch("ele8_CaloIdL_TrkIdVL_vstar");
		ele8_CaloIdL_TrkIdVL_vstar_branch->SetAddress(&ele8_CaloIdL_TrkIdVL_vstar_);
	}
	ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch = 0;
	if (tree->GetBranch("ele8_CaloIdL_CaloIsoVL_Jet40_vstar") != 0) {
		ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch = tree->GetBranch("ele8_CaloIdL_CaloIsoVL_Jet40_vstar");
		ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch->SetAddress(&ele8_CaloIdL_CaloIsoVL_Jet40_vstar_);
	}
	ele8_CaloIdL_CaloIsoVL_vstar_branch = 0;
	if (tree->GetBranch("ele8_CaloIdL_CaloIsoVL_vstar") != 0) {
		ele8_CaloIdL_CaloIsoVL_vstar_branch = tree->GetBranch("ele8_CaloIdL_CaloIsoVL_vstar");
		ele8_CaloIdL_CaloIsoVL_vstar_branch->SetAddress(&ele8_CaloIdL_CaloIsoVL_vstar_);
	}
	ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch = 0;
	if (tree->GetBranch("ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar") != 0) {
		ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch = tree->GetBranch("ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar");
		ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch->SetAddress(&ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_);
	}
	ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch = 0;
	if (tree->GetBranch("ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar") != 0) {
		ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch = tree->GetBranch("ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar");
		ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch->SetAddress(&ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_);
	}
	ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch = 0;
	if (tree->GetBranch("ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar") != 0) {
		ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch = tree->GetBranch("ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar");
		ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch->SetAddress(&ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_);
	}
	ele8_CaloIdT_TrkIdVL_vstar_branch = 0;
	if (tree->GetBranch("ele8_CaloIdT_TrkIdVL_vstar") != 0) {
		ele8_CaloIdT_TrkIdVL_vstar_branch = tree->GetBranch("ele8_CaloIdT_TrkIdVL_vstar");
		ele8_CaloIdT_TrkIdVL_vstar_branch->SetAddress(&ele8_CaloIdT_TrkIdVL_vstar_);
	}
	ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch = 0;
	if (tree->GetBranch("ele8_CaloIdT_TrkIdVL_Jet30_vstar") != 0) {
		ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch = tree->GetBranch("ele8_CaloIdT_TrkIdVL_Jet30_vstar");
		ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch->SetAddress(&ele8_CaloIdT_TrkIdVL_Jet30_vstar_);
	}
	ele17_CaloIdL_CaloIsoVL_vstar_branch = 0;
	if (tree->GetBranch("ele17_CaloIdL_CaloIsoVL_vstar") != 0) {
		ele17_CaloIdL_CaloIsoVL_vstar_branch = tree->GetBranch("ele17_CaloIdL_CaloIsoVL_vstar");
		ele17_CaloIdL_CaloIsoVL_vstar_branch->SetAddress(&ele17_CaloIdL_CaloIsoVL_vstar_);
	}
	ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch = 0;
	if (tree->GetBranch("ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar") != 0) {
		ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch = tree->GetBranch("ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar");
		ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch->SetAddress(&ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_);
	}
	ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch = 0;
	if (tree->GetBranch("ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar") != 0) {
		ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch = tree->GetBranch("ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar");
		ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch->SetAddress(&ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_);
	}
	photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch = 0;
	if (tree->GetBranch("photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar") != 0) {
		photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch = tree->GetBranch("photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar");
		photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch->SetAddress(&photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_);
	}
	ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch = 0;
	if (tree->GetBranch("ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar") != 0) {
		ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch = tree->GetBranch("ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar");
		ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch->SetAddress(&ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_);
	}
	ele27_WP80_vstar_branch = 0;
	if (tree->GetBranch("ele27_WP80_vstar") != 0) {
		ele27_WP80_vstar_branch = tree->GetBranch("ele27_WP80_vstar");
		ele27_WP80_vstar_branch->SetAddress(&ele27_WP80_vstar_);
	}
	ele8_version_branch = 0;
	if (tree->GetBranch("ele8_version") != 0) {
		ele8_version_branch = tree->GetBranch("ele8_version");
		ele8_version_branch->SetAddress(&ele8_version_);
	}
	ele8_CaloIdL_TrkIdVL_version_branch = 0;
	if (tree->GetBranch("ele8_CaloIdL_TrkIdVL_version") != 0) {
		ele8_CaloIdL_TrkIdVL_version_branch = tree->GetBranch("ele8_CaloIdL_TrkIdVL_version");
		ele8_CaloIdL_TrkIdVL_version_branch->SetAddress(&ele8_CaloIdL_TrkIdVL_version_);
	}
	ele8_CaloIdL_CaloIsoVL_Jet40_version_branch = 0;
	if (tree->GetBranch("ele8_CaloIdL_CaloIsoVL_Jet40_version") != 0) {
		ele8_CaloIdL_CaloIsoVL_Jet40_version_branch = tree->GetBranch("ele8_CaloIdL_CaloIsoVL_Jet40_version");
		ele8_CaloIdL_CaloIsoVL_Jet40_version_branch->SetAddress(&ele8_CaloIdL_CaloIsoVL_Jet40_version_);
	}
	ele8_CaloIdL_CaloIsoVL_version_branch = 0;
	if (tree->GetBranch("ele8_CaloIdL_CaloIsoVL_version") != 0) {
		ele8_CaloIdL_CaloIsoVL_version_branch = tree->GetBranch("ele8_CaloIdL_CaloIsoVL_version");
		ele8_CaloIdL_CaloIsoVL_version_branch->SetAddress(&ele8_CaloIdL_CaloIsoVL_version_);
	}
	ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_branch = 0;
	if (tree->GetBranch("ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version") != 0) {
		ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_branch = tree->GetBranch("ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version");
		ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_branch->SetAddress(&ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_);
	}
	ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_branch = 0;
	if (tree->GetBranch("ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version") != 0) {
		ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_branch = tree->GetBranch("ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version");
		ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_branch->SetAddress(&ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_);
	}
	ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_branch = 0;
	if (tree->GetBranch("ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version") != 0) {
		ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_branch = tree->GetBranch("ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version");
		ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_branch->SetAddress(&ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_);
	}
	ele8_CaloIdT_TrkIdVL_version_branch = 0;
	if (tree->GetBranch("ele8_CaloIdT_TrkIdVL_version") != 0) {
		ele8_CaloIdT_TrkIdVL_version_branch = tree->GetBranch("ele8_CaloIdT_TrkIdVL_version");
		ele8_CaloIdT_TrkIdVL_version_branch->SetAddress(&ele8_CaloIdT_TrkIdVL_version_);
	}
	ele8_CaloIdT_TrkIdVL_Jet30_version_branch = 0;
	if (tree->GetBranch("ele8_CaloIdT_TrkIdVL_Jet30_version") != 0) {
		ele8_CaloIdT_TrkIdVL_Jet30_version_branch = tree->GetBranch("ele8_CaloIdT_TrkIdVL_Jet30_version");
		ele8_CaloIdT_TrkIdVL_Jet30_version_branch->SetAddress(&ele8_CaloIdT_TrkIdVL_Jet30_version_);
	}
	ele17_CaloIdL_CaloIsoVL_version_branch = 0;
	if (tree->GetBranch("ele17_CaloIdL_CaloIsoVL_version") != 0) {
		ele17_CaloIdL_CaloIsoVL_version_branch = tree->GetBranch("ele17_CaloIdL_CaloIsoVL_version");
		ele17_CaloIdL_CaloIsoVL_version_branch->SetAddress(&ele17_CaloIdL_CaloIsoVL_version_);
	}
	ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_branch = 0;
	if (tree->GetBranch("ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version") != 0) {
		ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_branch = tree->GetBranch("ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version");
		ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_branch->SetAddress(&ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_);
	}
	ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_branch = 0;
	if (tree->GetBranch("ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version") != 0) {
		ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_branch = tree->GetBranch("ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version");
		ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_branch->SetAddress(&ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_);
	}
	photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_branch = 0;
	if (tree->GetBranch("photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version") != 0) {
		photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_branch = tree->GetBranch("photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version");
		photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_branch->SetAddress(&photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_);
	}
	ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_version_branch = 0;
	if (tree->GetBranch("ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_version") != 0) {
		ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_version_branch = tree->GetBranch("ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_version");
		ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_version_branch->SetAddress(&ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_version_);
	}
	ele27_WP80_version_branch = 0;
	if (tree->GetBranch("ele27_WP80_version") != 0) {
		ele27_WP80_version_branch = tree->GetBranch("ele27_WP80_version");
		ele27_WP80_version_branch->SetAddress(&ele27_WP80_version_);
	}
	dr_ele8_vstar_branch = 0;
	if (tree->GetBranch("dr_ele8_vstar") != 0) {
		dr_ele8_vstar_branch = tree->GetBranch("dr_ele8_vstar");
		dr_ele8_vstar_branch->SetAddress(&dr_ele8_vstar_);
	}
	dr_ele8_CaloIdL_TrkIdVL_vstar_branch = 0;
	if (tree->GetBranch("dr_ele8_CaloIdL_TrkIdVL_vstar") != 0) {
		dr_ele8_CaloIdL_TrkIdVL_vstar_branch = tree->GetBranch("dr_ele8_CaloIdL_TrkIdVL_vstar");
		dr_ele8_CaloIdL_TrkIdVL_vstar_branch->SetAddress(&dr_ele8_CaloIdL_TrkIdVL_vstar_);
	}
	dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch = 0;
	if (tree->GetBranch("dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar") != 0) {
		dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch = tree->GetBranch("dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar");
		dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch->SetAddress(&dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_);
	}
	dr_ele8_CaloIdL_CaloIsoVL_vstar_branch = 0;
	if (tree->GetBranch("dr_ele8_CaloIdL_CaloIsoVL_vstar") != 0) {
		dr_ele8_CaloIdL_CaloIsoVL_vstar_branch = tree->GetBranch("dr_ele8_CaloIdL_CaloIsoVL_vstar");
		dr_ele8_CaloIdL_CaloIsoVL_vstar_branch->SetAddress(&dr_ele8_CaloIdL_CaloIsoVL_vstar_);
	}
	dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch = 0;
	if (tree->GetBranch("dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar") != 0) {
		dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch = tree->GetBranch("dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar");
		dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch->SetAddress(&dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_);
	}
	dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch = 0;
	if (tree->GetBranch("dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar") != 0) {
		dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch = tree->GetBranch("dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar");
		dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch->SetAddress(&dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_);
	}
	dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch = 0;
	if (tree->GetBranch("dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar") != 0) {
		dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch = tree->GetBranch("dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar");
		dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch->SetAddress(&dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_);
	}
	dr_ele8_CaloIdT_TrkIdVL_vstar_branch = 0;
	if (tree->GetBranch("dr_ele8_CaloIdT_TrkIdVL_vstar") != 0) {
		dr_ele8_CaloIdT_TrkIdVL_vstar_branch = tree->GetBranch("dr_ele8_CaloIdT_TrkIdVL_vstar");
		dr_ele8_CaloIdT_TrkIdVL_vstar_branch->SetAddress(&dr_ele8_CaloIdT_TrkIdVL_vstar_);
	}
	dr_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch = 0;
	if (tree->GetBranch("dr_ele8_CaloIdT_TrkIdVL_Jet30_vstar") != 0) {
		dr_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch = tree->GetBranch("dr_ele8_CaloIdT_TrkIdVL_Jet30_vstar");
		dr_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch->SetAddress(&dr_ele8_CaloIdT_TrkIdVL_Jet30_vstar_);
	}
	dr_ele17_CaloIdL_CaloIsoVL_vstar_branch = 0;
	if (tree->GetBranch("dr_ele17_CaloIdL_CaloIsoVL_vstar") != 0) {
		dr_ele17_CaloIdL_CaloIsoVL_vstar_branch = tree->GetBranch("dr_ele17_CaloIdL_CaloIsoVL_vstar");
		dr_ele17_CaloIdL_CaloIsoVL_vstar_branch->SetAddress(&dr_ele17_CaloIdL_CaloIsoVL_vstar_);
	}
	dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch = 0;
	if (tree->GetBranch("dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar") != 0) {
		dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch = tree->GetBranch("dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar");
		dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch->SetAddress(&dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_);
	}
	dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch = 0;
	if (tree->GetBranch("dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar") != 0) {
		dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch = tree->GetBranch("dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar");
		dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch->SetAddress(&dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_);
	}
	dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch = 0;
	if (tree->GetBranch("dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar") != 0) {
		dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch = tree->GetBranch("dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar");
		dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch->SetAddress(&dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_);
	}
	dr_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch = 0;
	if (tree->GetBranch("dr_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar") != 0) {
		dr_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch = tree->GetBranch("dr_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar");
		dr_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch->SetAddress(&dr_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_);
	}
	dr_ele27_WP80_vstar_branch = 0;
	if (tree->GetBranch("dr_ele27_WP80_vstar") != 0) {
		dr_ele27_WP80_vstar_branch = tree->GetBranch("dr_ele27_WP80_vstar");
		dr_ele27_WP80_vstar_branch->SetAddress(&dr_ele27_WP80_vstar_);
	}
	hltps_ele8_vstar_branch = 0;
	if (tree->GetBranch("hltps_ele8_vstar") != 0) {
		hltps_ele8_vstar_branch = tree->GetBranch("hltps_ele8_vstar");
		hltps_ele8_vstar_branch->SetAddress(&hltps_ele8_vstar_);
	}
	hltps_ele8_CaloIdL_TrkIdVL_vstar_branch = 0;
	if (tree->GetBranch("hltps_ele8_CaloIdL_TrkIdVL_vstar") != 0) {
		hltps_ele8_CaloIdL_TrkIdVL_vstar_branch = tree->GetBranch("hltps_ele8_CaloIdL_TrkIdVL_vstar");
		hltps_ele8_CaloIdL_TrkIdVL_vstar_branch->SetAddress(&hltps_ele8_CaloIdL_TrkIdVL_vstar_);
	}
	hltps_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch = 0;
	if (tree->GetBranch("hltps_ele8_CaloIdL_CaloIsoVL_Jet40_vstar") != 0) {
		hltps_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch = tree->GetBranch("hltps_ele8_CaloIdL_CaloIsoVL_Jet40_vstar");
		hltps_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch->SetAddress(&hltps_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_);
	}
	hltps_ele8_CaloIdL_CaloIsoVL_vstar_branch = 0;
	if (tree->GetBranch("hltps_ele8_CaloIdL_CaloIsoVL_vstar") != 0) {
		hltps_ele8_CaloIdL_CaloIsoVL_vstar_branch = tree->GetBranch("hltps_ele8_CaloIdL_CaloIsoVL_vstar");
		hltps_ele8_CaloIdL_CaloIsoVL_vstar_branch->SetAddress(&hltps_ele8_CaloIdL_CaloIsoVL_vstar_);
	}
	hltps_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch = 0;
	if (tree->GetBranch("hltps_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar") != 0) {
		hltps_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch = tree->GetBranch("hltps_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar");
		hltps_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch->SetAddress(&hltps_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_);
	}
	hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch = 0;
	if (tree->GetBranch("hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar") != 0) {
		hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch = tree->GetBranch("hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar");
		hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch->SetAddress(&hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_);
	}
	hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch = 0;
	if (tree->GetBranch("hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar") != 0) {
		hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch = tree->GetBranch("hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar");
		hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch->SetAddress(&hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_);
	}
	hltps_ele8_CaloIdT_TrkIdVL_vstar_branch = 0;
	if (tree->GetBranch("hltps_ele8_CaloIdT_TrkIdVL_vstar") != 0) {
		hltps_ele8_CaloIdT_TrkIdVL_vstar_branch = tree->GetBranch("hltps_ele8_CaloIdT_TrkIdVL_vstar");
		hltps_ele8_CaloIdT_TrkIdVL_vstar_branch->SetAddress(&hltps_ele8_CaloIdT_TrkIdVL_vstar_);
	}
	hltps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch = 0;
	if (tree->GetBranch("hltps_ele8_CaloIdT_TrkIdVL_Jet30_vstar") != 0) {
		hltps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch = tree->GetBranch("hltps_ele8_CaloIdT_TrkIdVL_Jet30_vstar");
		hltps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch->SetAddress(&hltps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_);
	}
	hltps_ele17_CaloIdL_CaloIsoVL_vstar_branch = 0;
	if (tree->GetBranch("hltps_ele17_CaloIdL_CaloIsoVL_vstar") != 0) {
		hltps_ele17_CaloIdL_CaloIsoVL_vstar_branch = tree->GetBranch("hltps_ele17_CaloIdL_CaloIsoVL_vstar");
		hltps_ele17_CaloIdL_CaloIsoVL_vstar_branch->SetAddress(&hltps_ele17_CaloIdL_CaloIsoVL_vstar_);
	}
	hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch = 0;
	if (tree->GetBranch("hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar") != 0) {
		hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch = tree->GetBranch("hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar");
		hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch->SetAddress(&hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_);
	}
	hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch = 0;
	if (tree->GetBranch("hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar") != 0) {
		hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch = tree->GetBranch("hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar");
		hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch->SetAddress(&hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_);
	}
	hltps_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch = 0;
	if (tree->GetBranch("hltps_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar") != 0) {
		hltps_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch = tree->GetBranch("hltps_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar");
		hltps_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch->SetAddress(&hltps_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_);
	}
	hltps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch = 0;
	if (tree->GetBranch("hltps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar") != 0) {
		hltps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch = tree->GetBranch("hltps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar");
		hltps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch->SetAddress(&hltps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_);
	}
	hltps_ele27_WP80_vstar_branch = 0;
	if (tree->GetBranch("hltps_ele27_WP80_vstar") != 0) {
		hltps_ele27_WP80_vstar_branch = tree->GetBranch("hltps_ele27_WP80_vstar");
		hltps_ele27_WP80_vstar_branch->SetAddress(&hltps_ele27_WP80_vstar_);
	}
	l1ps_ele8_CaloIdL_CaloIsoVL_vstar_branch = 0;
	if (tree->GetBranch("l1ps_ele8_CaloIdL_CaloIsoVL_vstar") != 0) {
		l1ps_ele8_CaloIdL_CaloIsoVL_vstar_branch = tree->GetBranch("l1ps_ele8_CaloIdL_CaloIsoVL_vstar");
		l1ps_ele8_CaloIdL_CaloIsoVL_vstar_branch->SetAddress(&l1ps_ele8_CaloIdL_CaloIsoVL_vstar_);
	}
	l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch = 0;
	if (tree->GetBranch("l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar") != 0) {
		l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch = tree->GetBranch("l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar");
		l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch->SetAddress(&l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_);
	}
	l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch = 0;
	if (tree->GetBranch("l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar") != 0) {
		l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch = tree->GetBranch("l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar");
		l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch->SetAddress(&l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_);
	}
	l1ps_ele8_CaloIdT_TrkIdVL_vstar_branch = 0;
	if (tree->GetBranch("l1ps_ele8_CaloIdT_TrkIdVL_vstar") != 0) {
		l1ps_ele8_CaloIdT_TrkIdVL_vstar_branch = tree->GetBranch("l1ps_ele8_CaloIdT_TrkIdVL_vstar");
		l1ps_ele8_CaloIdT_TrkIdVL_vstar_branch->SetAddress(&l1ps_ele8_CaloIdT_TrkIdVL_vstar_);
	}
	l1ps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch = 0;
	if (tree->GetBranch("l1ps_ele8_CaloIdT_TrkIdVL_Jet30_vstar") != 0) {
		l1ps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch = tree->GetBranch("l1ps_ele8_CaloIdT_TrkIdVL_Jet30_vstar");
		l1ps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch->SetAddress(&l1ps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_);
	}
	l1ps_ele17_CaloIdL_CaloIsoVL_vstar_branch = 0;
	if (tree->GetBranch("l1ps_ele17_CaloIdL_CaloIsoVL_vstar") != 0) {
		l1ps_ele17_CaloIdL_CaloIsoVL_vstar_branch = tree->GetBranch("l1ps_ele17_CaloIdL_CaloIsoVL_vstar");
		l1ps_ele17_CaloIdL_CaloIsoVL_vstar_branch->SetAddress(&l1ps_ele17_CaloIdL_CaloIsoVL_vstar_);
	}
	l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch = 0;
	if (tree->GetBranch("l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar") != 0) {
		l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch = tree->GetBranch("l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar");
		l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch->SetAddress(&l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_);
	}
	l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch = 0;
	if (tree->GetBranch("l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar") != 0) {
		l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch = tree->GetBranch("l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar");
		l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch->SetAddress(&l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_);
	}
	l1ps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch = 0;
	if (tree->GetBranch("l1ps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar") != 0) {
		l1ps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch = tree->GetBranch("l1ps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar");
		l1ps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch->SetAddress(&l1ps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_);
	}
	l1ps_ele27_WP80_vstar_branch = 0;
	if (tree->GetBranch("l1ps_ele27_WP80_vstar") != 0) {
		l1ps_ele27_WP80_vstar_branch = tree->GetBranch("l1ps_ele27_WP80_vstar");
		l1ps_ele27_WP80_vstar_branch->SetAddress(&l1ps_ele27_WP80_vstar_);
	}
	mu3_vstar_branch = 0;
	if (tree->GetBranch("mu3_vstar") != 0) {
		mu3_vstar_branch = tree->GetBranch("mu3_vstar");
		mu3_vstar_branch->SetAddress(&mu3_vstar_);
	}
	mu5_vstar_branch = 0;
	if (tree->GetBranch("mu5_vstar") != 0) {
		mu5_vstar_branch = tree->GetBranch("mu5_vstar");
		mu5_vstar_branch->SetAddress(&mu5_vstar_);
	}
	mu8_vstar_branch = 0;
	if (tree->GetBranch("mu8_vstar") != 0) {
		mu8_vstar_branch = tree->GetBranch("mu8_vstar");
		mu8_vstar_branch->SetAddress(&mu8_vstar_);
	}
	mu12_vstar_branch = 0;
	if (tree->GetBranch("mu12_vstar") != 0) {
		mu12_vstar_branch = tree->GetBranch("mu12_vstar");
		mu12_vstar_branch->SetAddress(&mu12_vstar_);
	}
	mu15_vstar_branch = 0;
	if (tree->GetBranch("mu15_vstar") != 0) {
		mu15_vstar_branch = tree->GetBranch("mu15_vstar");
		mu15_vstar_branch->SetAddress(&mu15_vstar_);
	}
	mu17_vstar_branch = 0;
	if (tree->GetBranch("mu17_vstar") != 0) {
		mu17_vstar_branch = tree->GetBranch("mu17_vstar");
		mu17_vstar_branch->SetAddress(&mu17_vstar_);
	}
	mu20_vstar_branch = 0;
	if (tree->GetBranch("mu20_vstar") != 0) {
		mu20_vstar_branch = tree->GetBranch("mu20_vstar");
		mu20_vstar_branch->SetAddress(&mu20_vstar_);
	}
	mu24_vstar_branch = 0;
	if (tree->GetBranch("mu24_vstar") != 0) {
		mu24_vstar_branch = tree->GetBranch("mu24_vstar");
		mu24_vstar_branch->SetAddress(&mu24_vstar_);
	}
	mu30_vstar_branch = 0;
	if (tree->GetBranch("mu30_vstar") != 0) {
		mu30_vstar_branch = tree->GetBranch("mu30_vstar");
		mu30_vstar_branch->SetAddress(&mu30_vstar_);
	}
	mu15_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("mu15_eta2p1_vstar") != 0) {
		mu15_eta2p1_vstar_branch = tree->GetBranch("mu15_eta2p1_vstar");
		mu15_eta2p1_vstar_branch->SetAddress(&mu15_eta2p1_vstar_);
	}
	mu24_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("mu24_eta2p1_vstar") != 0) {
		mu24_eta2p1_vstar_branch = tree->GetBranch("mu24_eta2p1_vstar");
		mu24_eta2p1_vstar_branch->SetAddress(&mu24_eta2p1_vstar_);
	}
	mu30_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("mu30_eta2p1_vstar") != 0) {
		mu30_eta2p1_vstar_branch = tree->GetBranch("mu30_eta2p1_vstar");
		mu30_eta2p1_vstar_branch->SetAddress(&mu30_eta2p1_vstar_);
	}
	mu8_Jet40_vstar_branch = 0;
	if (tree->GetBranch("mu8_Jet40_vstar") != 0) {
		mu8_Jet40_vstar_branch = tree->GetBranch("mu8_Jet40_vstar");
		mu8_Jet40_vstar_branch->SetAddress(&mu8_Jet40_vstar_);
	}
	isoMu20_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("isoMu20_eta2p1_vstar") != 0) {
		isoMu20_eta2p1_vstar_branch = tree->GetBranch("isoMu20_eta2p1_vstar");
		isoMu20_eta2p1_vstar_branch->SetAddress(&isoMu20_eta2p1_vstar_);
	}
	isoMu24_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("isoMu24_eta2p1_vstar") != 0) {
		isoMu24_eta2p1_vstar_branch = tree->GetBranch("isoMu24_eta2p1_vstar");
		isoMu24_eta2p1_vstar_branch->SetAddress(&isoMu24_eta2p1_vstar_);
	}
	isoMu30_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("isoMu30_eta2p1_vstar") != 0) {
		isoMu30_eta2p1_vstar_branch = tree->GetBranch("isoMu30_eta2p1_vstar");
		isoMu30_eta2p1_vstar_branch->SetAddress(&isoMu30_eta2p1_vstar_);
	}
	relIso1p0Mu17_vstar_branch = 0;
	if (tree->GetBranch("relIso1p0Mu17_vstar") != 0) {
		relIso1p0Mu17_vstar_branch = tree->GetBranch("relIso1p0Mu17_vstar");
		relIso1p0Mu17_vstar_branch->SetAddress(&relIso1p0Mu17_vstar_);
	}
	relIso1p0Mu5_vstar_branch = 0;
	if (tree->GetBranch("relIso1p0Mu5_vstar") != 0) {
		relIso1p0Mu5_vstar_branch = tree->GetBranch("relIso1p0Mu5_vstar");
		relIso1p0Mu5_vstar_branch->SetAddress(&relIso1p0Mu5_vstar_);
	}
	mu3_version_branch = 0;
	if (tree->GetBranch("mu3_version") != 0) {
		mu3_version_branch = tree->GetBranch("mu3_version");
		mu3_version_branch->SetAddress(&mu3_version_);
	}
	mu5_version_branch = 0;
	if (tree->GetBranch("mu5_version") != 0) {
		mu5_version_branch = tree->GetBranch("mu5_version");
		mu5_version_branch->SetAddress(&mu5_version_);
	}
	mu8_version_branch = 0;
	if (tree->GetBranch("mu8_version") != 0) {
		mu8_version_branch = tree->GetBranch("mu8_version");
		mu8_version_branch->SetAddress(&mu8_version_);
	}
	mu12_version_branch = 0;
	if (tree->GetBranch("mu12_version") != 0) {
		mu12_version_branch = tree->GetBranch("mu12_version");
		mu12_version_branch->SetAddress(&mu12_version_);
	}
	mu15_version_branch = 0;
	if (tree->GetBranch("mu15_version") != 0) {
		mu15_version_branch = tree->GetBranch("mu15_version");
		mu15_version_branch->SetAddress(&mu15_version_);
	}
	mu17_version_branch = 0;
	if (tree->GetBranch("mu17_version") != 0) {
		mu17_version_branch = tree->GetBranch("mu17_version");
		mu17_version_branch->SetAddress(&mu17_version_);
	}
	mu20_version_branch = 0;
	if (tree->GetBranch("mu20_version") != 0) {
		mu20_version_branch = tree->GetBranch("mu20_version");
		mu20_version_branch->SetAddress(&mu20_version_);
	}
	mu24_version_branch = 0;
	if (tree->GetBranch("mu24_version") != 0) {
		mu24_version_branch = tree->GetBranch("mu24_version");
		mu24_version_branch->SetAddress(&mu24_version_);
	}
	mu30_version_branch = 0;
	if (tree->GetBranch("mu30_version") != 0) {
		mu30_version_branch = tree->GetBranch("mu30_version");
		mu30_version_branch->SetAddress(&mu30_version_);
	}
	mu15_eta2p1_version_branch = 0;
	if (tree->GetBranch("mu15_eta2p1_version") != 0) {
		mu15_eta2p1_version_branch = tree->GetBranch("mu15_eta2p1_version");
		mu15_eta2p1_version_branch->SetAddress(&mu15_eta2p1_version_);
	}
	mu24_eta2p1_version_branch = 0;
	if (tree->GetBranch("mu24_eta2p1_version") != 0) {
		mu24_eta2p1_version_branch = tree->GetBranch("mu24_eta2p1_version");
		mu24_eta2p1_version_branch->SetAddress(&mu24_eta2p1_version_);
	}
	mu30_eta2p1_version_branch = 0;
	if (tree->GetBranch("mu30_eta2p1_version") != 0) {
		mu30_eta2p1_version_branch = tree->GetBranch("mu30_eta2p1_version");
		mu30_eta2p1_version_branch->SetAddress(&mu30_eta2p1_version_);
	}
	mu8_Jet40_version_branch = 0;
	if (tree->GetBranch("mu8_Jet40_version") != 0) {
		mu8_Jet40_version_branch = tree->GetBranch("mu8_Jet40_version");
		mu8_Jet40_version_branch->SetAddress(&mu8_Jet40_version_);
	}
	isoMu20_eta2p1_version_branch = 0;
	if (tree->GetBranch("isoMu20_eta2p1_version") != 0) {
		isoMu20_eta2p1_version_branch = tree->GetBranch("isoMu20_eta2p1_version");
		isoMu20_eta2p1_version_branch->SetAddress(&isoMu20_eta2p1_version_);
	}
	isoMu24_eta2p1_version_branch = 0;
	if (tree->GetBranch("isoMu24_eta2p1_version") != 0) {
		isoMu24_eta2p1_version_branch = tree->GetBranch("isoMu24_eta2p1_version");
		isoMu24_eta2p1_version_branch->SetAddress(&isoMu24_eta2p1_version_);
	}
	isoMu30_eta2p1_version_branch = 0;
	if (tree->GetBranch("isoMu30_eta2p1_version") != 0) {
		isoMu30_eta2p1_version_branch = tree->GetBranch("isoMu30_eta2p1_version");
		isoMu30_eta2p1_version_branch->SetAddress(&isoMu30_eta2p1_version_);
	}
	relIso1p0Mu17_version_branch = 0;
	if (tree->GetBranch("relIso1p0Mu17_version") != 0) {
		relIso1p0Mu17_version_branch = tree->GetBranch("relIso1p0Mu17_version");
		relIso1p0Mu17_version_branch->SetAddress(&relIso1p0Mu17_version_);
	}
	relIso1p0Mu5_version_branch = 0;
	if (tree->GetBranch("relIso1p0Mu5_version") != 0) {
		relIso1p0Mu5_version_branch = tree->GetBranch("relIso1p0Mu5_version");
		relIso1p0Mu5_version_branch->SetAddress(&relIso1p0Mu5_version_);
	}
	dr_mu3_vstar_branch = 0;
	if (tree->GetBranch("dr_mu3_vstar") != 0) {
		dr_mu3_vstar_branch = tree->GetBranch("dr_mu3_vstar");
		dr_mu3_vstar_branch->SetAddress(&dr_mu3_vstar_);
	}
	dr_mu5_vstar_branch = 0;
	if (tree->GetBranch("dr_mu5_vstar") != 0) {
		dr_mu5_vstar_branch = tree->GetBranch("dr_mu5_vstar");
		dr_mu5_vstar_branch->SetAddress(&dr_mu5_vstar_);
	}
	dr_mu8_vstar_branch = 0;
	if (tree->GetBranch("dr_mu8_vstar") != 0) {
		dr_mu8_vstar_branch = tree->GetBranch("dr_mu8_vstar");
		dr_mu8_vstar_branch->SetAddress(&dr_mu8_vstar_);
	}
	dr_mu12_vstar_branch = 0;
	if (tree->GetBranch("dr_mu12_vstar") != 0) {
		dr_mu12_vstar_branch = tree->GetBranch("dr_mu12_vstar");
		dr_mu12_vstar_branch->SetAddress(&dr_mu12_vstar_);
	}
	dr_mu15_vstar_branch = 0;
	if (tree->GetBranch("dr_mu15_vstar") != 0) {
		dr_mu15_vstar_branch = tree->GetBranch("dr_mu15_vstar");
		dr_mu15_vstar_branch->SetAddress(&dr_mu15_vstar_);
	}
	dr_mu17_vstar_branch = 0;
	if (tree->GetBranch("dr_mu17_vstar") != 0) {
		dr_mu17_vstar_branch = tree->GetBranch("dr_mu17_vstar");
		dr_mu17_vstar_branch->SetAddress(&dr_mu17_vstar_);
	}
	dr_mu20_vstar_branch = 0;
	if (tree->GetBranch("dr_mu20_vstar") != 0) {
		dr_mu20_vstar_branch = tree->GetBranch("dr_mu20_vstar");
		dr_mu20_vstar_branch->SetAddress(&dr_mu20_vstar_);
	}
	dr_mu24_vstar_branch = 0;
	if (tree->GetBranch("dr_mu24_vstar") != 0) {
		dr_mu24_vstar_branch = tree->GetBranch("dr_mu24_vstar");
		dr_mu24_vstar_branch->SetAddress(&dr_mu24_vstar_);
	}
	dr_mu30_vstar_branch = 0;
	if (tree->GetBranch("dr_mu30_vstar") != 0) {
		dr_mu30_vstar_branch = tree->GetBranch("dr_mu30_vstar");
		dr_mu30_vstar_branch->SetAddress(&dr_mu30_vstar_);
	}
	dr_mu15_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("dr_mu15_eta2p1_vstar") != 0) {
		dr_mu15_eta2p1_vstar_branch = tree->GetBranch("dr_mu15_eta2p1_vstar");
		dr_mu15_eta2p1_vstar_branch->SetAddress(&dr_mu15_eta2p1_vstar_);
	}
	dr_mu24_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("dr_mu24_eta2p1_vstar") != 0) {
		dr_mu24_eta2p1_vstar_branch = tree->GetBranch("dr_mu24_eta2p1_vstar");
		dr_mu24_eta2p1_vstar_branch->SetAddress(&dr_mu24_eta2p1_vstar_);
	}
	dr_mu30_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("dr_mu30_eta2p1_vstar") != 0) {
		dr_mu30_eta2p1_vstar_branch = tree->GetBranch("dr_mu30_eta2p1_vstar");
		dr_mu30_eta2p1_vstar_branch->SetAddress(&dr_mu30_eta2p1_vstar_);
	}
	dr_mu8_Jet40_vstar_branch = 0;
	if (tree->GetBranch("dr_mu8_Jet40_vstar") != 0) {
		dr_mu8_Jet40_vstar_branch = tree->GetBranch("dr_mu8_Jet40_vstar");
		dr_mu8_Jet40_vstar_branch->SetAddress(&dr_mu8_Jet40_vstar_);
	}
	dr_isoMu20_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("dr_isoMu20_eta2p1_vstar") != 0) {
		dr_isoMu20_eta2p1_vstar_branch = tree->GetBranch("dr_isoMu20_eta2p1_vstar");
		dr_isoMu20_eta2p1_vstar_branch->SetAddress(&dr_isoMu20_eta2p1_vstar_);
	}
	dr_isoMu24_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("dr_isoMu24_eta2p1_vstar") != 0) {
		dr_isoMu24_eta2p1_vstar_branch = tree->GetBranch("dr_isoMu24_eta2p1_vstar");
		dr_isoMu24_eta2p1_vstar_branch->SetAddress(&dr_isoMu24_eta2p1_vstar_);
	}
	dr_isoMu30_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("dr_isoMu30_eta2p1_vstar") != 0) {
		dr_isoMu30_eta2p1_vstar_branch = tree->GetBranch("dr_isoMu30_eta2p1_vstar");
		dr_isoMu30_eta2p1_vstar_branch->SetAddress(&dr_isoMu30_eta2p1_vstar_);
	}
	dr_relIso1p0Mu17_vstar_branch = 0;
	if (tree->GetBranch("dr_relIso1p0Mu17_vstar") != 0) {
		dr_relIso1p0Mu17_vstar_branch = tree->GetBranch("dr_relIso1p0Mu17_vstar");
		dr_relIso1p0Mu17_vstar_branch->SetAddress(&dr_relIso1p0Mu17_vstar_);
	}
	dr_relIso1p0Mu5_vstar_branch = 0;
	if (tree->GetBranch("dr_relIso1p0Mu5_vstar") != 0) {
		dr_relIso1p0Mu5_vstar_branch = tree->GetBranch("dr_relIso1p0Mu5_vstar");
		dr_relIso1p0Mu5_vstar_branch->SetAddress(&dr_relIso1p0Mu5_vstar_);
	}
	hltps_mu3_vstar_branch = 0;
	if (tree->GetBranch("hltps_mu3_vstar") != 0) {
		hltps_mu3_vstar_branch = tree->GetBranch("hltps_mu3_vstar");
		hltps_mu3_vstar_branch->SetAddress(&hltps_mu3_vstar_);
	}
	hltps_mu5_vstar_branch = 0;
	if (tree->GetBranch("hltps_mu5_vstar") != 0) {
		hltps_mu5_vstar_branch = tree->GetBranch("hltps_mu5_vstar");
		hltps_mu5_vstar_branch->SetAddress(&hltps_mu5_vstar_);
	}
	hltps_mu8_vstar_branch = 0;
	if (tree->GetBranch("hltps_mu8_vstar") != 0) {
		hltps_mu8_vstar_branch = tree->GetBranch("hltps_mu8_vstar");
		hltps_mu8_vstar_branch->SetAddress(&hltps_mu8_vstar_);
	}
	hltps_mu12_vstar_branch = 0;
	if (tree->GetBranch("hltps_mu12_vstar") != 0) {
		hltps_mu12_vstar_branch = tree->GetBranch("hltps_mu12_vstar");
		hltps_mu12_vstar_branch->SetAddress(&hltps_mu12_vstar_);
	}
	hltps_mu15_vstar_branch = 0;
	if (tree->GetBranch("hltps_mu15_vstar") != 0) {
		hltps_mu15_vstar_branch = tree->GetBranch("hltps_mu15_vstar");
		hltps_mu15_vstar_branch->SetAddress(&hltps_mu15_vstar_);
	}
	hltps_mu17_vstar_branch = 0;
	if (tree->GetBranch("hltps_mu17_vstar") != 0) {
		hltps_mu17_vstar_branch = tree->GetBranch("hltps_mu17_vstar");
		hltps_mu17_vstar_branch->SetAddress(&hltps_mu17_vstar_);
	}
	hltps_mu20_vstar_branch = 0;
	if (tree->GetBranch("hltps_mu20_vstar") != 0) {
		hltps_mu20_vstar_branch = tree->GetBranch("hltps_mu20_vstar");
		hltps_mu20_vstar_branch->SetAddress(&hltps_mu20_vstar_);
	}
	hltps_mu24_vstar_branch = 0;
	if (tree->GetBranch("hltps_mu24_vstar") != 0) {
		hltps_mu24_vstar_branch = tree->GetBranch("hltps_mu24_vstar");
		hltps_mu24_vstar_branch->SetAddress(&hltps_mu24_vstar_);
	}
	hltps_mu30_vstar_branch = 0;
	if (tree->GetBranch("hltps_mu30_vstar") != 0) {
		hltps_mu30_vstar_branch = tree->GetBranch("hltps_mu30_vstar");
		hltps_mu30_vstar_branch->SetAddress(&hltps_mu30_vstar_);
	}
	hltps_mu15_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("hltps_mu15_eta2p1_vstar") != 0) {
		hltps_mu15_eta2p1_vstar_branch = tree->GetBranch("hltps_mu15_eta2p1_vstar");
		hltps_mu15_eta2p1_vstar_branch->SetAddress(&hltps_mu15_eta2p1_vstar_);
	}
	hltps_mu24_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("hltps_mu24_eta2p1_vstar") != 0) {
		hltps_mu24_eta2p1_vstar_branch = tree->GetBranch("hltps_mu24_eta2p1_vstar");
		hltps_mu24_eta2p1_vstar_branch->SetAddress(&hltps_mu24_eta2p1_vstar_);
	}
	hltps_mu30_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("hltps_mu30_eta2p1_vstar") != 0) {
		hltps_mu30_eta2p1_vstar_branch = tree->GetBranch("hltps_mu30_eta2p1_vstar");
		hltps_mu30_eta2p1_vstar_branch->SetAddress(&hltps_mu30_eta2p1_vstar_);
	}
	hltps_mu8_Jet40_vstar_branch = 0;
	if (tree->GetBranch("hltps_mu8_Jet40_vstar") != 0) {
		hltps_mu8_Jet40_vstar_branch = tree->GetBranch("hltps_mu8_Jet40_vstar");
		hltps_mu8_Jet40_vstar_branch->SetAddress(&hltps_mu8_Jet40_vstar_);
	}
	hltps_isoMu20_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("hltps_isoMu20_eta2p1_vstar") != 0) {
		hltps_isoMu20_eta2p1_vstar_branch = tree->GetBranch("hltps_isoMu20_eta2p1_vstar");
		hltps_isoMu20_eta2p1_vstar_branch->SetAddress(&hltps_isoMu20_eta2p1_vstar_);
	}
	hltps_isoMu24_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("hltps_isoMu24_eta2p1_vstar") != 0) {
		hltps_isoMu24_eta2p1_vstar_branch = tree->GetBranch("hltps_isoMu24_eta2p1_vstar");
		hltps_isoMu24_eta2p1_vstar_branch->SetAddress(&hltps_isoMu24_eta2p1_vstar_);
	}
	hltps_isoMu30_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("hltps_isoMu30_eta2p1_vstar") != 0) {
		hltps_isoMu30_eta2p1_vstar_branch = tree->GetBranch("hltps_isoMu30_eta2p1_vstar");
		hltps_isoMu30_eta2p1_vstar_branch->SetAddress(&hltps_isoMu30_eta2p1_vstar_);
	}
	hltps_relIso1p0Mu17_vstar_branch = 0;
	if (tree->GetBranch("hltps_relIso1p0Mu17_vstar") != 0) {
		hltps_relIso1p0Mu17_vstar_branch = tree->GetBranch("hltps_relIso1p0Mu17_vstar");
		hltps_relIso1p0Mu17_vstar_branch->SetAddress(&hltps_relIso1p0Mu17_vstar_);
	}
	hltps_relIso1p0Mu5_vstar_branch = 0;
	if (tree->GetBranch("hltps_relIso1p0Mu5_vstar") != 0) {
		hltps_relIso1p0Mu5_vstar_branch = tree->GetBranch("hltps_relIso1p0Mu5_vstar");
		hltps_relIso1p0Mu5_vstar_branch->SetAddress(&hltps_relIso1p0Mu5_vstar_);
	}
	l1ps_mu5_vstar_branch = 0;
	if (tree->GetBranch("l1ps_mu5_vstar") != 0) {
		l1ps_mu5_vstar_branch = tree->GetBranch("l1ps_mu5_vstar");
		l1ps_mu5_vstar_branch->SetAddress(&l1ps_mu5_vstar_);
	}
	l1ps_mu8_vstar_branch = 0;
	if (tree->GetBranch("l1ps_mu8_vstar") != 0) {
		l1ps_mu8_vstar_branch = tree->GetBranch("l1ps_mu8_vstar");
		l1ps_mu8_vstar_branch->SetAddress(&l1ps_mu8_vstar_);
	}
	l1ps_mu12_vstar_branch = 0;
	if (tree->GetBranch("l1ps_mu12_vstar") != 0) {
		l1ps_mu12_vstar_branch = tree->GetBranch("l1ps_mu12_vstar");
		l1ps_mu12_vstar_branch->SetAddress(&l1ps_mu12_vstar_);
	}
	l1ps_mu17_vstar_branch = 0;
	if (tree->GetBranch("l1ps_mu17_vstar") != 0) {
		l1ps_mu17_vstar_branch = tree->GetBranch("l1ps_mu17_vstar");
		l1ps_mu17_vstar_branch->SetAddress(&l1ps_mu17_vstar_);
	}
	l1ps_mu15_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("l1ps_mu15_eta2p1_vstar") != 0) {
		l1ps_mu15_eta2p1_vstar_branch = tree->GetBranch("l1ps_mu15_eta2p1_vstar");
		l1ps_mu15_eta2p1_vstar_branch->SetAddress(&l1ps_mu15_eta2p1_vstar_);
	}
	l1ps_mu24_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("l1ps_mu24_eta2p1_vstar") != 0) {
		l1ps_mu24_eta2p1_vstar_branch = tree->GetBranch("l1ps_mu24_eta2p1_vstar");
		l1ps_mu24_eta2p1_vstar_branch->SetAddress(&l1ps_mu24_eta2p1_vstar_);
	}
	l1ps_mu30_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("l1ps_mu30_eta2p1_vstar") != 0) {
		l1ps_mu30_eta2p1_vstar_branch = tree->GetBranch("l1ps_mu30_eta2p1_vstar");
		l1ps_mu30_eta2p1_vstar_branch->SetAddress(&l1ps_mu30_eta2p1_vstar_);
	}
	l1ps_isoMu20_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("l1ps_isoMu20_eta2p1_vstar") != 0) {
		l1ps_isoMu20_eta2p1_vstar_branch = tree->GetBranch("l1ps_isoMu20_eta2p1_vstar");
		l1ps_isoMu20_eta2p1_vstar_branch->SetAddress(&l1ps_isoMu20_eta2p1_vstar_);
	}
	l1ps_isoMu24_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("l1ps_isoMu24_eta2p1_vstar") != 0) {
		l1ps_isoMu24_eta2p1_vstar_branch = tree->GetBranch("l1ps_isoMu24_eta2p1_vstar");
		l1ps_isoMu24_eta2p1_vstar_branch->SetAddress(&l1ps_isoMu24_eta2p1_vstar_);
	}
	l1ps_isoMu30_eta2p1_vstar_branch = 0;
	if (tree->GetBranch("l1ps_isoMu30_eta2p1_vstar") != 0) {
		l1ps_isoMu30_eta2p1_vstar_branch = tree->GetBranch("l1ps_isoMu30_eta2p1_vstar");
		l1ps_isoMu30_eta2p1_vstar_branch->SetAddress(&l1ps_isoMu30_eta2p1_vstar_);
	}
	l1ps_relIso1p0Mu17_vstar_branch = 0;
	if (tree->GetBranch("l1ps_relIso1p0Mu17_vstar") != 0) {
		l1ps_relIso1p0Mu17_vstar_branch = tree->GetBranch("l1ps_relIso1p0Mu17_vstar");
		l1ps_relIso1p0Mu17_vstar_branch->SetAddress(&l1ps_relIso1p0Mu17_vstar_);
	}
	l1ps_relIso1p0Mu5_vstar_branch = 0;
	if (tree->GetBranch("l1ps_relIso1p0Mu5_vstar") != 0) {
		l1ps_relIso1p0Mu5_vstar_branch = tree->GetBranch("l1ps_relIso1p0Mu5_vstar");
		l1ps_relIso1p0Mu5_vstar_branch->SetAddress(&l1ps_relIso1p0Mu5_vstar_);
	}
	ptj1_branch = 0;
	if (tree->GetBranch("ptj1") != 0) {
		ptj1_branch = tree->GetBranch("ptj1");
		ptj1_branch->SetAddress(&ptj1_);
	}
	nj1_branch = 0;
	if (tree->GetBranch("nj1") != 0) {
		nj1_branch = tree->GetBranch("nj1");
		nj1_branch->SetAddress(&nj1_);
	}
	ptj1_b2b_branch = 0;
	if (tree->GetBranch("ptj1_b2b") != 0) {
		ptj1_b2b_branch = tree->GetBranch("ptj1_b2b");
		ptj1_b2b_branch->SetAddress(&ptj1_b2b_);
	}
	dphij1_b2b_branch = 0;
	if (tree->GetBranch("dphij1_b2b") != 0) {
		dphij1_b2b_branch = tree->GetBranch("dphij1_b2b");
		dphij1_b2b_branch->SetAddress(&dphij1_b2b_);
	}
	ptpfj1_branch = 0;
	if (tree->GetBranch("ptpfj1") != 0) {
		ptpfj1_branch = tree->GetBranch("ptpfj1");
		ptpfj1_branch->SetAddress(&ptpfj1_);
	}
	npfj1_branch = 0;
	if (tree->GetBranch("npfj1") != 0) {
		npfj1_branch = tree->GetBranch("npfj1");
		npfj1_branch->SetAddress(&npfj1_);
	}
	ptpfj1_b2b_branch = 0;
	if (tree->GetBranch("ptpfj1_b2b") != 0) {
		ptpfj1_b2b_branch = tree->GetBranch("ptpfj1_b2b");
		ptpfj1_b2b_branch->SetAddress(&ptpfj1_b2b_);
	}
	dphipfj1_b2b_branch = 0;
	if (tree->GetBranch("dphipfj1_b2b") != 0) {
		dphipfj1_b2b_branch = tree->GetBranch("dphipfj1_b2b");
		dphipfj1_b2b_branch->SetAddress(&dphipfj1_b2b_);
	}
	ptpfcj1_branch = 0;
	if (tree->GetBranch("ptpfcj1") != 0) {
		ptpfcj1_branch = tree->GetBranch("ptpfcj1");
		ptpfcj1_branch->SetAddress(&ptpfcj1_);
	}
	npfcj1_branch = 0;
	if (tree->GetBranch("npfcj1") != 0) {
		npfcj1_branch = tree->GetBranch("npfcj1");
		npfcj1_branch->SetAddress(&npfcj1_);
	}
	ptpfcj1_b2b_branch = 0;
	if (tree->GetBranch("ptpfcj1_b2b") != 0) {
		ptpfcj1_b2b_branch = tree->GetBranch("ptpfcj1_b2b");
		ptpfcj1_b2b_branch->SetAddress(&ptpfcj1_b2b_);
	}
	dphipfcj1_b2b_branch = 0;
	if (tree->GetBranch("dphipfcj1_b2b") != 0) {
		dphipfcj1_b2b_branch = tree->GetBranch("dphipfcj1_b2b");
		dphipfcj1_b2b_branch->SetAddress(&dphipfcj1_b2b_);
	}
	btagpfc_branch = 0;
	if (tree->GetBranch("btagpfc") != 0) {
		btagpfc_branch = tree->GetBranch("btagpfc");
		btagpfc_branch->SetAddress(&btagpfc_);
	}
	emfpfcL1Fj1_branch = 0;
	if (tree->GetBranch("emfpfcL1Fj1") != 0) {
		emfpfcL1Fj1_branch = tree->GetBranch("emfpfcL1Fj1");
		emfpfcL1Fj1_branch->SetAddress(&emfpfcL1Fj1_);
	}
	ptpfcL1Fj1_branch = 0;
	if (tree->GetBranch("ptpfcL1Fj1") != 0) {
		ptpfcL1Fj1_branch = tree->GetBranch("ptpfcL1Fj1");
		ptpfcL1Fj1_branch->SetAddress(&ptpfcL1Fj1_);
	}
	dphipfcL1Fj1_branch = 0;
	if (tree->GetBranch("dphipfcL1Fj1") != 0) {
		dphipfcL1Fj1_branch = tree->GetBranch("dphipfcL1Fj1");
		dphipfcL1Fj1_branch->SetAddress(&dphipfcL1Fj1_);
	}
	npfcL1Fj1_branch = 0;
	if (tree->GetBranch("npfcL1Fj1") != 0) {
		npfcL1Fj1_branch = tree->GetBranch("npfcL1Fj1");
		npfcL1Fj1_branch->SetAddress(&npfcL1Fj1_);
	}
	npfc30L1Fj1_branch = 0;
	if (tree->GetBranch("npfc30L1Fj1") != 0) {
		npfc30L1Fj1_branch = tree->GetBranch("npfc30L1Fj1");
		npfc30L1Fj1_branch->SetAddress(&npfc30L1Fj1_);
	}
	npfc40L1Fj1_branch = 0;
	if (tree->GetBranch("npfc40L1Fj1") != 0) {
		npfc40L1Fj1_branch = tree->GetBranch("npfc40L1Fj1");
		npfc40L1Fj1_branch->SetAddress(&npfc40L1Fj1_);
	}
	ptpfcL1Fj1_b2b_branch = 0;
	if (tree->GetBranch("ptpfcL1Fj1_b2b") != 0) {
		ptpfcL1Fj1_b2b_branch = tree->GetBranch("ptpfcL1Fj1_b2b");
		ptpfcL1Fj1_b2b_branch->SetAddress(&ptpfcL1Fj1_b2b_);
	}
	dphipfcL1Fj1_b2b_branch = 0;
	if (tree->GetBranch("dphipfcL1Fj1_b2b") != 0) {
		dphipfcL1Fj1_b2b_branch = tree->GetBranch("dphipfcL1Fj1_b2b");
		dphipfcL1Fj1_b2b_branch->SetAddress(&dphipfcL1Fj1_b2b_);
	}
	btagpfcL1F_branch = 0;
	if (tree->GetBranch("btagpfcL1F") != 0) {
		btagpfcL1F_branch = tree->GetBranch("btagpfcL1F");
		btagpfcL1F_branch->SetAddress(&btagpfcL1F_);
	}
	emfpfcL1Fj1res_branch = 0;
	if (tree->GetBranch("emfpfcL1Fj1res") != 0) {
		emfpfcL1Fj1res_branch = tree->GetBranch("emfpfcL1Fj1res");
		emfpfcL1Fj1res_branch->SetAddress(&emfpfcL1Fj1res_);
	}
	ptpfcL1Fj1res_branch = 0;
	if (tree->GetBranch("ptpfcL1Fj1res") != 0) {
		ptpfcL1Fj1res_branch = tree->GetBranch("ptpfcL1Fj1res");
		ptpfcL1Fj1res_branch->SetAddress(&ptpfcL1Fj1res_);
	}
	dphipfcL1Fj1res_branch = 0;
	if (tree->GetBranch("dphipfcL1Fj1res") != 0) {
		dphipfcL1Fj1res_branch = tree->GetBranch("dphipfcL1Fj1res");
		dphipfcL1Fj1res_branch->SetAddress(&dphipfcL1Fj1res_);
	}
	npfcL1Fj1res_branch = 0;
	if (tree->GetBranch("npfcL1Fj1res") != 0) {
		npfcL1Fj1res_branch = tree->GetBranch("npfcL1Fj1res");
		npfcL1Fj1res_branch->SetAddress(&npfcL1Fj1res_);
	}
	npfc30L1Fj1res_branch = 0;
	if (tree->GetBranch("npfc30L1Fj1res") != 0) {
		npfc30L1Fj1res_branch = tree->GetBranch("npfc30L1Fj1res");
		npfc30L1Fj1res_branch->SetAddress(&npfc30L1Fj1res_);
	}
	npfc40L1Fj1res_branch = 0;
	if (tree->GetBranch("npfc40L1Fj1res") != 0) {
		npfc40L1Fj1res_branch = tree->GetBranch("npfc40L1Fj1res");
		npfc40L1Fj1res_branch->SetAddress(&npfc40L1Fj1res_);
	}
	ptpfcL1Fj1res_b2b_branch = 0;
	if (tree->GetBranch("ptpfcL1Fj1res_b2b") != 0) {
		ptpfcL1Fj1res_b2b_branch = tree->GetBranch("ptpfcL1Fj1res_b2b");
		ptpfcL1Fj1res_b2b_branch->SetAddress(&ptpfcL1Fj1res_b2b_);
	}
	dphipfcL1Fj1res_b2b_branch = 0;
	if (tree->GetBranch("dphipfcL1Fj1res_b2b") != 0) {
		dphipfcL1Fj1res_b2b_branch = tree->GetBranch("dphipfcL1Fj1res_b2b");
		dphipfcL1Fj1res_b2b_branch->SetAddress(&dphipfcL1Fj1res_b2b_);
	}
	btagpfcL1Fres_branch = 0;
	if (tree->GetBranch("btagpfcL1Fres") != 0) {
		btagpfcL1Fres_branch = tree->GetBranch("btagpfcL1Fres");
		btagpfcL1Fres_branch->SetAddress(&btagpfcL1Fres_);
	}
	ptbtagpfcL1Fj1_branch = 0;
	if (tree->GetBranch("ptbtagpfcL1Fj1") != 0) {
		ptbtagpfcL1Fj1_branch = tree->GetBranch("ptbtagpfcL1Fj1");
		ptbtagpfcL1Fj1_branch->SetAddress(&ptbtagpfcL1Fj1_);
	}
	dphibtagpfcL1Fj1_branch = 0;
	if (tree->GetBranch("dphibtagpfcL1Fj1") != 0) {
		dphibtagpfcL1Fj1_branch = tree->GetBranch("dphibtagpfcL1Fj1");
		dphibtagpfcL1Fj1_branch->SetAddress(&dphibtagpfcL1Fj1_);
	}
	ptbtagpfcL1Fj1res_branch = 0;
	if (tree->GetBranch("ptbtagpfcL1Fj1res") != 0) {
		ptbtagpfcL1Fj1res_branch = tree->GetBranch("ptbtagpfcL1Fj1res");
		ptbtagpfcL1Fj1res_branch->SetAddress(&ptbtagpfcL1Fj1res_);
	}
	dphibtagpfcL1Fj1res_branch = 0;
	if (tree->GetBranch("dphibtagpfcL1Fj1res") != 0) {
		dphibtagpfcL1Fj1res_branch = tree->GetBranch("dphibtagpfcL1Fj1res");
		dphibtagpfcL1Fj1res_branch->SetAddress(&dphibtagpfcL1Fj1res_);
	}
	nbjet_branch = 0;
	if (tree->GetBranch("nbjet") != 0) {
		nbjet_branch = tree->GetBranch("nbjet");
		nbjet_branch->SetAddress(&nbjet_);
	}
	dRNear_branch = 0;
	if (tree->GetBranch("dRNear") != 0) {
		dRNear_branch = tree->GetBranch("dRNear");
		dRNear_branch->SetAddress(&dRNear_);
	}
	dRFar_branch = 0;
	if (tree->GetBranch("dRFar") != 0) {
		dRFar_branch = tree->GetBranch("dRFar");
		dRFar_branch->SetAddress(&dRFar_);
	}
	nbpfcjet_branch = 0;
	if (tree->GetBranch("nbpfcjet") != 0) {
		nbpfcjet_branch = tree->GetBranch("nbpfcjet");
		nbpfcjet_branch->SetAddress(&nbpfcjet_);
	}
	dRpfcNear_branch = 0;
	if (tree->GetBranch("dRpfcNear") != 0) {
		dRpfcNear_branch = tree->GetBranch("dRpfcNear");
		dRpfcNear_branch->SetAddress(&dRpfcNear_);
	}
	dRpfcFar_branch = 0;
	if (tree->GetBranch("dRpfcFar") != 0) {
		dRpfcFar_branch = tree->GetBranch("dRpfcFar");
		dRpfcFar_branch->SetAddress(&dRpfcFar_);
	}
	rho_branch = 0;
	if (tree->GetBranch("rho") != 0) {
		rho_branch = tree->GetBranch("rho");
		rho_branch->SetAddress(&rho_);
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
		weight_isLoaded = false;
		pu_nPUvertices_isLoaded = false;
		evt_nvtxs_isLoaded = false;
		nFOels_isLoaded = false;
		nFOmus_isLoaded = false;
		ngsfs_isLoaded = false;
		nmus_isLoaded = false;
		foel_id_isLoaded = false;
		fomu_id_isLoaded = false;
		foel_mass_isLoaded = false;
		fomu_mass_isLoaded = false;
		pt_isLoaded = false;
		eta_isLoaded = false;
		sceta_isLoaded = false;
		phi_isLoaded = false;
		scet_isLoaded = false;
		hoe_isLoaded = false;
		pfmet_isLoaded = false;
		pfmetphi_isLoaded = false;
		iso_isLoaded = false;
		iso_nps_isLoaded = false;
		trck_iso_isLoaded = false;
		ecal_iso_isLoaded = false;
		ecal_iso_nps_isLoaded = false;
		hcal_iso_isLoaded = false;
		pfiso03_isLoaded = false;
		ch_pfiso03_isLoaded = false;
		nh_pfiso03_isLoaded = false;
		em_pfiso03_isLoaded = false;
		pfiso04_isLoaded = false;
		ch_pfiso04_isLoaded = false;
		nh_pfiso04_isLoaded = false;
		em_pfiso04_isLoaded = false;
		pfpupt03_isLoaded = false;
		pfpupt04_isLoaded = false;
		cpfiso03_rho_isLoaded = false;
		cpfiso03_db_isLoaded = false;
		id_isLoaded = false;
		closestMuon_isLoaded = false;
		el_id_sieie_isLoaded = false;
		el_id_detain_isLoaded = false;
		el_id_dphiin_isLoaded = false;
		el_id_smurfV5_isLoaded = false;
		el_id_vbtf80_isLoaded = false;
		el_id_vbtf90_isLoaded = false;
		el_effarea_isLoaded = false;
		mu_effarea03_isLoaded = false;
		mu_nh_effarea03_isLoaded = false;
		mu_em_effarea03_isLoaded = false;
		mu_effarea03_tight_isLoaded = false;
		mu_nh_effarea03_tight_isLoaded = false;
		mu_em_effarea03_tight_isLoaded = false;
		mu_effarea04_isLoaded = false;
		mu_nh_effarea04_isLoaded = false;
		mu_em_effarea04_isLoaded = false;
		mu_effarea04_tight_isLoaded = false;
		mu_nh_effarea04_tight_isLoaded = false;
		mu_em_effarea04_tight_isLoaded = false;
		conv0MissHits_isLoaded = false;
		convHitPattern_isLoaded = false;
		convPartnerTrack_isLoaded = false;
		convMIT_isLoaded = false;
		mt_isLoaded = false;
		pfmt_isLoaded = false;
		q3_isLoaded = false;
		els_exp_innerlayers_isLoaded = false;
		d0PV_wwV1_isLoaded = false;
		dzPV_wwV1_isLoaded = false;
		ht_calo_isLoaded = false;
		ht_calo_L2L3_isLoaded = false;
		ht_pf_isLoaded = false;
		ht_pf_L2L3_isLoaded = false;
		ht_pf_L1FastL2L3_isLoaded = false;
		mcid_isLoaded = false;
		mcmotherid_isLoaded = false;
		mc3id_isLoaded = false;
		mc3pt_isLoaded = false;
		mc3dr_isLoaded = false;
		leptonIsFromW_isLoaded = false;
		mu_isCosmic_isLoaded = false;
		mz_fo_gsf_isLoaded = false;
		mz_gsf_iso_isLoaded = false;
		mz_fo_ctf_isLoaded = false;
		mz_ctf_iso_isLoaded = false;
		mupsilon_fo_mu_isLoaded = false;
		mupsilon_mu_iso_isLoaded = false;
		num_el_ssV7_isLoaded = false;
		num_el_ssV7_noIso_isLoaded = false;
		v1_el_ssV7_isLoaded = false;
		v2_el_ssV7_isLoaded = false;
		v3_el_ssV7_isLoaded = false;
		num_mu_ssV5_isLoaded = false;
		num_mu_ssV5_noIso_isLoaded = false;
		fo_mu_ssV5_isLoaded = false;
		fo_mu_ssV5_noIso_isLoaded = false;
		num_el_ssV6_isLoaded = false;
		num_el_ssV6_noIso_isLoaded = false;
		v1_el_ssV6_isLoaded = false;
		v2_el_ssV6_isLoaded = false;
		v3_el_ssV6_isLoaded = false;
		numNomSSv4_isLoaded = false;
		numNomSSv4noIso_isLoaded = false;
		fo_mussV4_04_isLoaded = false;
		fo_mussV4_noIso_isLoaded = false;
		num_el_smurfV6_isLoaded = false;
		num_el_smurfV6lh_isLoaded = false;
		v1_el_smurfV1_isLoaded = false;
		v2_el_smurfV1_isLoaded = false;
		v3_el_smurfV1_isLoaded = false;
		v4_el_smurfV1_isLoaded = false;
		num_mu_smurfV6_isLoaded = false;
		fo_mu_smurf_04_isLoaded = false;
		fo_mu_smurf_10_isLoaded = false;
		num_el_OSV2_isLoaded = false;
		num_mu_OSGV2_isLoaded = false;
		num_mu_OSZV2_isLoaded = false;
		fo_el_OSV2_isLoaded = false;
		fo_mu_OSGV2_isLoaded = false;
		num_el_OSV3_isLoaded = false;
		num_mu_OSGV3_isLoaded = false;
		fo_el_OSV3_isLoaded = false;
		fo_mu_OSGV3_isLoaded = false;
		ele8_vstar_isLoaded = false;
		ele8_CaloIdL_TrkIdVL_vstar_isLoaded = false;
		ele8_CaloIdL_CaloIsoVL_Jet40_vstar_isLoaded = false;
		ele8_CaloIdL_CaloIsoVL_vstar_isLoaded = false;
		ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_isLoaded = false;
		ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded = false;
		ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded = false;
		ele8_CaloIdT_TrkIdVL_vstar_isLoaded = false;
		ele8_CaloIdT_TrkIdVL_Jet30_vstar_isLoaded = false;
		ele17_CaloIdL_CaloIsoVL_vstar_isLoaded = false;
		ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded = false;
		ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded = false;
		photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_isLoaded = false;
		ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_isLoaded = false;
		ele27_WP80_vstar_isLoaded = false;
		ele8_version_isLoaded = false;
		ele8_CaloIdL_TrkIdVL_version_isLoaded = false;
		ele8_CaloIdL_CaloIsoVL_Jet40_version_isLoaded = false;
		ele8_CaloIdL_CaloIsoVL_version_isLoaded = false;
		ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_isLoaded = false;
		ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_isLoaded = false;
		ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_isLoaded = false;
		ele8_CaloIdT_TrkIdVL_version_isLoaded = false;
		ele8_CaloIdT_TrkIdVL_Jet30_version_isLoaded = false;
		ele17_CaloIdL_CaloIsoVL_version_isLoaded = false;
		ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_isLoaded = false;
		ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_isLoaded = false;
		photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_isLoaded = false;
		ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_version_isLoaded = false;
		ele27_WP80_version_isLoaded = false;
		dr_ele8_vstar_isLoaded = false;
		dr_ele8_CaloIdL_TrkIdVL_vstar_isLoaded = false;
		dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_isLoaded = false;
		dr_ele8_CaloIdL_CaloIsoVL_vstar_isLoaded = false;
		dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_isLoaded = false;
		dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded = false;
		dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded = false;
		dr_ele8_CaloIdT_TrkIdVL_vstar_isLoaded = false;
		dr_ele8_CaloIdT_TrkIdVL_Jet30_vstar_isLoaded = false;
		dr_ele17_CaloIdL_CaloIsoVL_vstar_isLoaded = false;
		dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded = false;
		dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded = false;
		dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_isLoaded = false;
		dr_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_isLoaded = false;
		dr_ele27_WP80_vstar_isLoaded = false;
		hltps_ele8_vstar_isLoaded = false;
		hltps_ele8_CaloIdL_TrkIdVL_vstar_isLoaded = false;
		hltps_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_isLoaded = false;
		hltps_ele8_CaloIdL_CaloIsoVL_vstar_isLoaded = false;
		hltps_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_isLoaded = false;
		hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded = false;
		hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded = false;
		hltps_ele8_CaloIdT_TrkIdVL_vstar_isLoaded = false;
		hltps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_isLoaded = false;
		hltps_ele17_CaloIdL_CaloIsoVL_vstar_isLoaded = false;
		hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded = false;
		hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded = false;
		hltps_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_isLoaded = false;
		hltps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_isLoaded = false;
		hltps_ele27_WP80_vstar_isLoaded = false;
		l1ps_ele8_CaloIdL_CaloIsoVL_vstar_isLoaded = false;
		l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded = false;
		l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded = false;
		l1ps_ele8_CaloIdT_TrkIdVL_vstar_isLoaded = false;
		l1ps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_isLoaded = false;
		l1ps_ele17_CaloIdL_CaloIsoVL_vstar_isLoaded = false;
		l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded = false;
		l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded = false;
		l1ps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_isLoaded = false;
		l1ps_ele27_WP80_vstar_isLoaded = false;
		mu3_vstar_isLoaded = false;
		mu5_vstar_isLoaded = false;
		mu8_vstar_isLoaded = false;
		mu12_vstar_isLoaded = false;
		mu15_vstar_isLoaded = false;
		mu17_vstar_isLoaded = false;
		mu20_vstar_isLoaded = false;
		mu24_vstar_isLoaded = false;
		mu30_vstar_isLoaded = false;
		mu15_eta2p1_vstar_isLoaded = false;
		mu24_eta2p1_vstar_isLoaded = false;
		mu30_eta2p1_vstar_isLoaded = false;
		mu8_Jet40_vstar_isLoaded = false;
		isoMu20_eta2p1_vstar_isLoaded = false;
		isoMu24_eta2p1_vstar_isLoaded = false;
		isoMu30_eta2p1_vstar_isLoaded = false;
		relIso1p0Mu17_vstar_isLoaded = false;
		relIso1p0Mu5_vstar_isLoaded = false;
		mu3_version_isLoaded = false;
		mu5_version_isLoaded = false;
		mu8_version_isLoaded = false;
		mu12_version_isLoaded = false;
		mu15_version_isLoaded = false;
		mu17_version_isLoaded = false;
		mu20_version_isLoaded = false;
		mu24_version_isLoaded = false;
		mu30_version_isLoaded = false;
		mu15_eta2p1_version_isLoaded = false;
		mu24_eta2p1_version_isLoaded = false;
		mu30_eta2p1_version_isLoaded = false;
		mu8_Jet40_version_isLoaded = false;
		isoMu20_eta2p1_version_isLoaded = false;
		isoMu24_eta2p1_version_isLoaded = false;
		isoMu30_eta2p1_version_isLoaded = false;
		relIso1p0Mu17_version_isLoaded = false;
		relIso1p0Mu5_version_isLoaded = false;
		dr_mu3_vstar_isLoaded = false;
		dr_mu5_vstar_isLoaded = false;
		dr_mu8_vstar_isLoaded = false;
		dr_mu12_vstar_isLoaded = false;
		dr_mu15_vstar_isLoaded = false;
		dr_mu17_vstar_isLoaded = false;
		dr_mu20_vstar_isLoaded = false;
		dr_mu24_vstar_isLoaded = false;
		dr_mu30_vstar_isLoaded = false;
		dr_mu15_eta2p1_vstar_isLoaded = false;
		dr_mu24_eta2p1_vstar_isLoaded = false;
		dr_mu30_eta2p1_vstar_isLoaded = false;
		dr_mu8_Jet40_vstar_isLoaded = false;
		dr_isoMu20_eta2p1_vstar_isLoaded = false;
		dr_isoMu24_eta2p1_vstar_isLoaded = false;
		dr_isoMu30_eta2p1_vstar_isLoaded = false;
		dr_relIso1p0Mu17_vstar_isLoaded = false;
		dr_relIso1p0Mu5_vstar_isLoaded = false;
		hltps_mu3_vstar_isLoaded = false;
		hltps_mu5_vstar_isLoaded = false;
		hltps_mu8_vstar_isLoaded = false;
		hltps_mu12_vstar_isLoaded = false;
		hltps_mu15_vstar_isLoaded = false;
		hltps_mu17_vstar_isLoaded = false;
		hltps_mu20_vstar_isLoaded = false;
		hltps_mu24_vstar_isLoaded = false;
		hltps_mu30_vstar_isLoaded = false;
		hltps_mu15_eta2p1_vstar_isLoaded = false;
		hltps_mu24_eta2p1_vstar_isLoaded = false;
		hltps_mu30_eta2p1_vstar_isLoaded = false;
		hltps_mu8_Jet40_vstar_isLoaded = false;
		hltps_isoMu20_eta2p1_vstar_isLoaded = false;
		hltps_isoMu24_eta2p1_vstar_isLoaded = false;
		hltps_isoMu30_eta2p1_vstar_isLoaded = false;
		hltps_relIso1p0Mu17_vstar_isLoaded = false;
		hltps_relIso1p0Mu5_vstar_isLoaded = false;
		l1ps_mu5_vstar_isLoaded = false;
		l1ps_mu8_vstar_isLoaded = false;
		l1ps_mu12_vstar_isLoaded = false;
		l1ps_mu17_vstar_isLoaded = false;
		l1ps_mu15_eta2p1_vstar_isLoaded = false;
		l1ps_mu24_eta2p1_vstar_isLoaded = false;
		l1ps_mu30_eta2p1_vstar_isLoaded = false;
		l1ps_isoMu20_eta2p1_vstar_isLoaded = false;
		l1ps_isoMu24_eta2p1_vstar_isLoaded = false;
		l1ps_isoMu30_eta2p1_vstar_isLoaded = false;
		l1ps_relIso1p0Mu17_vstar_isLoaded = false;
		l1ps_relIso1p0Mu5_vstar_isLoaded = false;
		ptj1_isLoaded = false;
		nj1_isLoaded = false;
		ptj1_b2b_isLoaded = false;
		dphij1_b2b_isLoaded = false;
		ptpfj1_isLoaded = false;
		npfj1_isLoaded = false;
		ptpfj1_b2b_isLoaded = false;
		dphipfj1_b2b_isLoaded = false;
		ptpfcj1_isLoaded = false;
		npfcj1_isLoaded = false;
		ptpfcj1_b2b_isLoaded = false;
		dphipfcj1_b2b_isLoaded = false;
		btagpfc_isLoaded = false;
		emfpfcL1Fj1_isLoaded = false;
		ptpfcL1Fj1_isLoaded = false;
		dphipfcL1Fj1_isLoaded = false;
		npfcL1Fj1_isLoaded = false;
		npfc30L1Fj1_isLoaded = false;
		npfc40L1Fj1_isLoaded = false;
		ptpfcL1Fj1_b2b_isLoaded = false;
		dphipfcL1Fj1_b2b_isLoaded = false;
		btagpfcL1F_isLoaded = false;
		emfpfcL1Fj1res_isLoaded = false;
		ptpfcL1Fj1res_isLoaded = false;
		dphipfcL1Fj1res_isLoaded = false;
		npfcL1Fj1res_isLoaded = false;
		npfc30L1Fj1res_isLoaded = false;
		npfc40L1Fj1res_isLoaded = false;
		ptpfcL1Fj1res_b2b_isLoaded = false;
		dphipfcL1Fj1res_b2b_isLoaded = false;
		btagpfcL1Fres_isLoaded = false;
		ptbtagpfcL1Fj1_isLoaded = false;
		dphibtagpfcL1Fj1_isLoaded = false;
		ptbtagpfcL1Fj1res_isLoaded = false;
		dphibtagpfcL1Fj1res_isLoaded = false;
		nbjet_isLoaded = false;
		dRNear_isLoaded = false;
		dRFar_isLoaded = false;
		nbpfcjet_isLoaded = false;
		dRpfcNear_isLoaded = false;
		dRpfcFar_isLoaded = false;
		rho_isLoaded = false;
	}

void LoadAllBranches() 
	// load all branches
{
	if (run_branch != 0) run();
	if (ls_branch != 0) ls();
	if (evt_branch != 0) evt();
	if (weight_branch != 0) weight();
	if (pu_nPUvertices_branch != 0) pu_nPUvertices();
	if (evt_nvtxs_branch != 0) evt_nvtxs();
	if (nFOels_branch != 0) nFOels();
	if (nFOmus_branch != 0) nFOmus();
	if (ngsfs_branch != 0) ngsfs();
	if (nmus_branch != 0) nmus();
	if (foel_id_branch != 0) foel_id();
	if (fomu_id_branch != 0) fomu_id();
	if (foel_mass_branch != 0) foel_mass();
	if (fomu_mass_branch != 0) fomu_mass();
	if (pt_branch != 0) pt();
	if (eta_branch != 0) eta();
	if (sceta_branch != 0) sceta();
	if (phi_branch != 0) phi();
	if (scet_branch != 0) scet();
	if (hoe_branch != 0) hoe();
	if (pfmet_branch != 0) pfmet();
	if (pfmetphi_branch != 0) pfmetphi();
	if (iso_branch != 0) iso();
	if (iso_nps_branch != 0) iso_nps();
	if (trck_iso_branch != 0) trck_iso();
	if (ecal_iso_branch != 0) ecal_iso();
	if (ecal_iso_nps_branch != 0) ecal_iso_nps();
	if (hcal_iso_branch != 0) hcal_iso();
	if (pfiso03_branch != 0) pfiso03();
	if (ch_pfiso03_branch != 0) ch_pfiso03();
	if (nh_pfiso03_branch != 0) nh_pfiso03();
	if (em_pfiso03_branch != 0) em_pfiso03();
	if (pfiso04_branch != 0) pfiso04();
	if (ch_pfiso04_branch != 0) ch_pfiso04();
	if (nh_pfiso04_branch != 0) nh_pfiso04();
	if (em_pfiso04_branch != 0) em_pfiso04();
	if (pfpupt03_branch != 0) pfpupt03();
	if (pfpupt04_branch != 0) pfpupt04();
	if (cpfiso03_rho_branch != 0) cpfiso03_rho();
	if (cpfiso03_db_branch != 0) cpfiso03_db();
	if (id_branch != 0) id();
	if (closestMuon_branch != 0) closestMuon();
	if (el_id_sieie_branch != 0) el_id_sieie();
	if (el_id_detain_branch != 0) el_id_detain();
	if (el_id_dphiin_branch != 0) el_id_dphiin();
	if (el_id_smurfV5_branch != 0) el_id_smurfV5();
	if (el_id_vbtf80_branch != 0) el_id_vbtf80();
	if (el_id_vbtf90_branch != 0) el_id_vbtf90();
	if (el_effarea_branch != 0) el_effarea();
	if (mu_effarea03_branch != 0) mu_effarea03();
	if (mu_nh_effarea03_branch != 0) mu_nh_effarea03();
	if (mu_em_effarea03_branch != 0) mu_em_effarea03();
	if (mu_effarea03_tight_branch != 0) mu_effarea03_tight();
	if (mu_nh_effarea03_tight_branch != 0) mu_nh_effarea03_tight();
	if (mu_em_effarea03_tight_branch != 0) mu_em_effarea03_tight();
	if (mu_effarea04_branch != 0) mu_effarea04();
	if (mu_nh_effarea04_branch != 0) mu_nh_effarea04();
	if (mu_em_effarea04_branch != 0) mu_em_effarea04();
	if (mu_effarea04_tight_branch != 0) mu_effarea04_tight();
	if (mu_nh_effarea04_tight_branch != 0) mu_nh_effarea04_tight();
	if (mu_em_effarea04_tight_branch != 0) mu_em_effarea04_tight();
	if (conv0MissHits_branch != 0) conv0MissHits();
	if (convHitPattern_branch != 0) convHitPattern();
	if (convPartnerTrack_branch != 0) convPartnerTrack();
	if (convMIT_branch != 0) convMIT();
	if (mt_branch != 0) mt();
	if (pfmt_branch != 0) pfmt();
	if (q3_branch != 0) q3();
	if (els_exp_innerlayers_branch != 0) els_exp_innerlayers();
	if (d0PV_wwV1_branch != 0) d0PV_wwV1();
	if (dzPV_wwV1_branch != 0) dzPV_wwV1();
	if (ht_calo_branch != 0) ht_calo();
	if (ht_calo_L2L3_branch != 0) ht_calo_L2L3();
	if (ht_pf_branch != 0) ht_pf();
	if (ht_pf_L2L3_branch != 0) ht_pf_L2L3();
	if (ht_pf_L1FastL2L3_branch != 0) ht_pf_L1FastL2L3();
	if (mcid_branch != 0) mcid();
	if (mcmotherid_branch != 0) mcmotherid();
	if (mc3id_branch != 0) mc3id();
	if (mc3pt_branch != 0) mc3pt();
	if (mc3dr_branch != 0) mc3dr();
	if (leptonIsFromW_branch != 0) leptonIsFromW();
	if (mu_isCosmic_branch != 0) mu_isCosmic();
	if (mz_fo_gsf_branch != 0) mz_fo_gsf();
	if (mz_gsf_iso_branch != 0) mz_gsf_iso();
	if (mz_fo_ctf_branch != 0) mz_fo_ctf();
	if (mz_ctf_iso_branch != 0) mz_ctf_iso();
	if (mupsilon_fo_mu_branch != 0) mupsilon_fo_mu();
	if (mupsilon_mu_iso_branch != 0) mupsilon_mu_iso();
	if (num_el_ssV7_branch != 0) num_el_ssV7();
	if (num_el_ssV7_noIso_branch != 0) num_el_ssV7_noIso();
	if (v1_el_ssV7_branch != 0) v1_el_ssV7();
	if (v2_el_ssV7_branch != 0) v2_el_ssV7();
	if (v3_el_ssV7_branch != 0) v3_el_ssV7();
	if (num_mu_ssV5_branch != 0) num_mu_ssV5();
	if (num_mu_ssV5_noIso_branch != 0) num_mu_ssV5_noIso();
	if (fo_mu_ssV5_branch != 0) fo_mu_ssV5();
	if (fo_mu_ssV5_noIso_branch != 0) fo_mu_ssV5_noIso();
	if (num_el_ssV6_branch != 0) num_el_ssV6();
	if (num_el_ssV6_noIso_branch != 0) num_el_ssV6_noIso();
	if (v1_el_ssV6_branch != 0) v1_el_ssV6();
	if (v2_el_ssV6_branch != 0) v2_el_ssV6();
	if (v3_el_ssV6_branch != 0) v3_el_ssV6();
	if (numNomSSv4_branch != 0) numNomSSv4();
	if (numNomSSv4noIso_branch != 0) numNomSSv4noIso();
	if (fo_mussV4_04_branch != 0) fo_mussV4_04();
	if (fo_mussV4_noIso_branch != 0) fo_mussV4_noIso();
	if (num_el_smurfV6_branch != 0) num_el_smurfV6();
	if (num_el_smurfV6lh_branch != 0) num_el_smurfV6lh();
	if (v1_el_smurfV1_branch != 0) v1_el_smurfV1();
	if (v2_el_smurfV1_branch != 0) v2_el_smurfV1();
	if (v3_el_smurfV1_branch != 0) v3_el_smurfV1();
	if (v4_el_smurfV1_branch != 0) v4_el_smurfV1();
	if (num_mu_smurfV6_branch != 0) num_mu_smurfV6();
	if (fo_mu_smurf_04_branch != 0) fo_mu_smurf_04();
	if (fo_mu_smurf_10_branch != 0) fo_mu_smurf_10();
	if (num_el_OSV2_branch != 0) num_el_OSV2();
	if (num_mu_OSGV2_branch != 0) num_mu_OSGV2();
	if (num_mu_OSZV2_branch != 0) num_mu_OSZV2();
	if (fo_el_OSV2_branch != 0) fo_el_OSV2();
	if (fo_mu_OSGV2_branch != 0) fo_mu_OSGV2();
	if (num_el_OSV3_branch != 0) num_el_OSV3();
	if (num_mu_OSGV3_branch != 0) num_mu_OSGV3();
	if (fo_el_OSV3_branch != 0) fo_el_OSV3();
	if (fo_mu_OSGV3_branch != 0) fo_mu_OSGV3();
	if (ele8_vstar_branch != 0) ele8_vstar();
	if (ele8_CaloIdL_TrkIdVL_vstar_branch != 0) ele8_CaloIdL_TrkIdVL_vstar();
	if (ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch != 0) ele8_CaloIdL_CaloIsoVL_Jet40_vstar();
	if (ele8_CaloIdL_CaloIsoVL_vstar_branch != 0) ele8_CaloIdL_CaloIsoVL_vstar();
	if (ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch != 0) ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar();
	if (ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch != 0) ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar();
	if (ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch != 0) ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar();
	if (ele8_CaloIdT_TrkIdVL_vstar_branch != 0) ele8_CaloIdT_TrkIdVL_vstar();
	if (ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch != 0) ele8_CaloIdT_TrkIdVL_Jet30_vstar();
	if (ele17_CaloIdL_CaloIsoVL_vstar_branch != 0) ele17_CaloIdL_CaloIsoVL_vstar();
	if (ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch != 0) ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar();
	if (ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch != 0) ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar();
	if (photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch != 0) photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar();
	if (ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch != 0) ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar();
	if (ele27_WP80_vstar_branch != 0) ele27_WP80_vstar();
	if (ele8_version_branch != 0) ele8_version();
	if (ele8_CaloIdL_TrkIdVL_version_branch != 0) ele8_CaloIdL_TrkIdVL_version();
	if (ele8_CaloIdL_CaloIsoVL_Jet40_version_branch != 0) ele8_CaloIdL_CaloIsoVL_Jet40_version();
	if (ele8_CaloIdL_CaloIsoVL_version_branch != 0) ele8_CaloIdL_CaloIsoVL_version();
	if (ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_branch != 0) ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version();
	if (ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_branch != 0) ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version();
	if (ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_branch != 0) ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version();
	if (ele8_CaloIdT_TrkIdVL_version_branch != 0) ele8_CaloIdT_TrkIdVL_version();
	if (ele8_CaloIdT_TrkIdVL_Jet30_version_branch != 0) ele8_CaloIdT_TrkIdVL_Jet30_version();
	if (ele17_CaloIdL_CaloIsoVL_version_branch != 0) ele17_CaloIdL_CaloIsoVL_version();
	if (ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_branch != 0) ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version();
	if (ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_branch != 0) ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version();
	if (photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_branch != 0) photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version();
	if (ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_version_branch != 0) ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_version();
	if (ele27_WP80_version_branch != 0) ele27_WP80_version();
	if (dr_ele8_vstar_branch != 0) dr_ele8_vstar();
	if (dr_ele8_CaloIdL_TrkIdVL_vstar_branch != 0) dr_ele8_CaloIdL_TrkIdVL_vstar();
	if (dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch != 0) dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar();
	if (dr_ele8_CaloIdL_CaloIsoVL_vstar_branch != 0) dr_ele8_CaloIdL_CaloIsoVL_vstar();
	if (dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch != 0) dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar();
	if (dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch != 0) dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar();
	if (dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch != 0) dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar();
	if (dr_ele8_CaloIdT_TrkIdVL_vstar_branch != 0) dr_ele8_CaloIdT_TrkIdVL_vstar();
	if (dr_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch != 0) dr_ele8_CaloIdT_TrkIdVL_Jet30_vstar();
	if (dr_ele17_CaloIdL_CaloIsoVL_vstar_branch != 0) dr_ele17_CaloIdL_CaloIsoVL_vstar();
	if (dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch != 0) dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar();
	if (dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch != 0) dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar();
	if (dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch != 0) dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar();
	if (dr_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch != 0) dr_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar();
	if (dr_ele27_WP80_vstar_branch != 0) dr_ele27_WP80_vstar();
	if (hltps_ele8_vstar_branch != 0) hltps_ele8_vstar();
	if (hltps_ele8_CaloIdL_TrkIdVL_vstar_branch != 0) hltps_ele8_CaloIdL_TrkIdVL_vstar();
	if (hltps_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch != 0) hltps_ele8_CaloIdL_CaloIsoVL_Jet40_vstar();
	if (hltps_ele8_CaloIdL_CaloIsoVL_vstar_branch != 0) hltps_ele8_CaloIdL_CaloIsoVL_vstar();
	if (hltps_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch != 0) hltps_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar();
	if (hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch != 0) hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar();
	if (hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch != 0) hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar();
	if (hltps_ele8_CaloIdT_TrkIdVL_vstar_branch != 0) hltps_ele8_CaloIdT_TrkIdVL_vstar();
	if (hltps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch != 0) hltps_ele8_CaloIdT_TrkIdVL_Jet30_vstar();
	if (hltps_ele17_CaloIdL_CaloIsoVL_vstar_branch != 0) hltps_ele17_CaloIdL_CaloIsoVL_vstar();
	if (hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch != 0) hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar();
	if (hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch != 0) hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar();
	if (hltps_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch != 0) hltps_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar();
	if (hltps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch != 0) hltps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar();
	if (hltps_ele27_WP80_vstar_branch != 0) hltps_ele27_WP80_vstar();
	if (l1ps_ele8_CaloIdL_CaloIsoVL_vstar_branch != 0) l1ps_ele8_CaloIdL_CaloIsoVL_vstar();
	if (l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch != 0) l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar();
	if (l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch != 0) l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar();
	if (l1ps_ele8_CaloIdT_TrkIdVL_vstar_branch != 0) l1ps_ele8_CaloIdT_TrkIdVL_vstar();
	if (l1ps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch != 0) l1ps_ele8_CaloIdT_TrkIdVL_Jet30_vstar();
	if (l1ps_ele17_CaloIdL_CaloIsoVL_vstar_branch != 0) l1ps_ele17_CaloIdL_CaloIsoVL_vstar();
	if (l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch != 0) l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar();
	if (l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch != 0) l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar();
	if (l1ps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch != 0) l1ps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar();
	if (l1ps_ele27_WP80_vstar_branch != 0) l1ps_ele27_WP80_vstar();
	if (mu3_vstar_branch != 0) mu3_vstar();
	if (mu5_vstar_branch != 0) mu5_vstar();
	if (mu8_vstar_branch != 0) mu8_vstar();
	if (mu12_vstar_branch != 0) mu12_vstar();
	if (mu15_vstar_branch != 0) mu15_vstar();
	if (mu17_vstar_branch != 0) mu17_vstar();
	if (mu20_vstar_branch != 0) mu20_vstar();
	if (mu24_vstar_branch != 0) mu24_vstar();
	if (mu30_vstar_branch != 0) mu30_vstar();
	if (mu15_eta2p1_vstar_branch != 0) mu15_eta2p1_vstar();
	if (mu24_eta2p1_vstar_branch != 0) mu24_eta2p1_vstar();
	if (mu30_eta2p1_vstar_branch != 0) mu30_eta2p1_vstar();
	if (mu8_Jet40_vstar_branch != 0) mu8_Jet40_vstar();
	if (isoMu20_eta2p1_vstar_branch != 0) isoMu20_eta2p1_vstar();
	if (isoMu24_eta2p1_vstar_branch != 0) isoMu24_eta2p1_vstar();
	if (isoMu30_eta2p1_vstar_branch != 0) isoMu30_eta2p1_vstar();
	if (relIso1p0Mu17_vstar_branch != 0) relIso1p0Mu17_vstar();
	if (relIso1p0Mu5_vstar_branch != 0) relIso1p0Mu5_vstar();
	if (mu3_version_branch != 0) mu3_version();
	if (mu5_version_branch != 0) mu5_version();
	if (mu8_version_branch != 0) mu8_version();
	if (mu12_version_branch != 0) mu12_version();
	if (mu15_version_branch != 0) mu15_version();
	if (mu17_version_branch != 0) mu17_version();
	if (mu20_version_branch != 0) mu20_version();
	if (mu24_version_branch != 0) mu24_version();
	if (mu30_version_branch != 0) mu30_version();
	if (mu15_eta2p1_version_branch != 0) mu15_eta2p1_version();
	if (mu24_eta2p1_version_branch != 0) mu24_eta2p1_version();
	if (mu30_eta2p1_version_branch != 0) mu30_eta2p1_version();
	if (mu8_Jet40_version_branch != 0) mu8_Jet40_version();
	if (isoMu20_eta2p1_version_branch != 0) isoMu20_eta2p1_version();
	if (isoMu24_eta2p1_version_branch != 0) isoMu24_eta2p1_version();
	if (isoMu30_eta2p1_version_branch != 0) isoMu30_eta2p1_version();
	if (relIso1p0Mu17_version_branch != 0) relIso1p0Mu17_version();
	if (relIso1p0Mu5_version_branch != 0) relIso1p0Mu5_version();
	if (dr_mu3_vstar_branch != 0) dr_mu3_vstar();
	if (dr_mu5_vstar_branch != 0) dr_mu5_vstar();
	if (dr_mu8_vstar_branch != 0) dr_mu8_vstar();
	if (dr_mu12_vstar_branch != 0) dr_mu12_vstar();
	if (dr_mu15_vstar_branch != 0) dr_mu15_vstar();
	if (dr_mu17_vstar_branch != 0) dr_mu17_vstar();
	if (dr_mu20_vstar_branch != 0) dr_mu20_vstar();
	if (dr_mu24_vstar_branch != 0) dr_mu24_vstar();
	if (dr_mu30_vstar_branch != 0) dr_mu30_vstar();
	if (dr_mu15_eta2p1_vstar_branch != 0) dr_mu15_eta2p1_vstar();
	if (dr_mu24_eta2p1_vstar_branch != 0) dr_mu24_eta2p1_vstar();
	if (dr_mu30_eta2p1_vstar_branch != 0) dr_mu30_eta2p1_vstar();
	if (dr_mu8_Jet40_vstar_branch != 0) dr_mu8_Jet40_vstar();
	if (dr_isoMu20_eta2p1_vstar_branch != 0) dr_isoMu20_eta2p1_vstar();
	if (dr_isoMu24_eta2p1_vstar_branch != 0) dr_isoMu24_eta2p1_vstar();
	if (dr_isoMu30_eta2p1_vstar_branch != 0) dr_isoMu30_eta2p1_vstar();
	if (dr_relIso1p0Mu17_vstar_branch != 0) dr_relIso1p0Mu17_vstar();
	if (dr_relIso1p0Mu5_vstar_branch != 0) dr_relIso1p0Mu5_vstar();
	if (hltps_mu3_vstar_branch != 0) hltps_mu3_vstar();
	if (hltps_mu5_vstar_branch != 0) hltps_mu5_vstar();
	if (hltps_mu8_vstar_branch != 0) hltps_mu8_vstar();
	if (hltps_mu12_vstar_branch != 0) hltps_mu12_vstar();
	if (hltps_mu15_vstar_branch != 0) hltps_mu15_vstar();
	if (hltps_mu17_vstar_branch != 0) hltps_mu17_vstar();
	if (hltps_mu20_vstar_branch != 0) hltps_mu20_vstar();
	if (hltps_mu24_vstar_branch != 0) hltps_mu24_vstar();
	if (hltps_mu30_vstar_branch != 0) hltps_mu30_vstar();
	if (hltps_mu15_eta2p1_vstar_branch != 0) hltps_mu15_eta2p1_vstar();
	if (hltps_mu24_eta2p1_vstar_branch != 0) hltps_mu24_eta2p1_vstar();
	if (hltps_mu30_eta2p1_vstar_branch != 0) hltps_mu30_eta2p1_vstar();
	if (hltps_mu8_Jet40_vstar_branch != 0) hltps_mu8_Jet40_vstar();
	if (hltps_isoMu20_eta2p1_vstar_branch != 0) hltps_isoMu20_eta2p1_vstar();
	if (hltps_isoMu24_eta2p1_vstar_branch != 0) hltps_isoMu24_eta2p1_vstar();
	if (hltps_isoMu30_eta2p1_vstar_branch != 0) hltps_isoMu30_eta2p1_vstar();
	if (hltps_relIso1p0Mu17_vstar_branch != 0) hltps_relIso1p0Mu17_vstar();
	if (hltps_relIso1p0Mu5_vstar_branch != 0) hltps_relIso1p0Mu5_vstar();
	if (l1ps_mu5_vstar_branch != 0) l1ps_mu5_vstar();
	if (l1ps_mu8_vstar_branch != 0) l1ps_mu8_vstar();
	if (l1ps_mu12_vstar_branch != 0) l1ps_mu12_vstar();
	if (l1ps_mu17_vstar_branch != 0) l1ps_mu17_vstar();
	if (l1ps_mu15_eta2p1_vstar_branch != 0) l1ps_mu15_eta2p1_vstar();
	if (l1ps_mu24_eta2p1_vstar_branch != 0) l1ps_mu24_eta2p1_vstar();
	if (l1ps_mu30_eta2p1_vstar_branch != 0) l1ps_mu30_eta2p1_vstar();
	if (l1ps_isoMu20_eta2p1_vstar_branch != 0) l1ps_isoMu20_eta2p1_vstar();
	if (l1ps_isoMu24_eta2p1_vstar_branch != 0) l1ps_isoMu24_eta2p1_vstar();
	if (l1ps_isoMu30_eta2p1_vstar_branch != 0) l1ps_isoMu30_eta2p1_vstar();
	if (l1ps_relIso1p0Mu17_vstar_branch != 0) l1ps_relIso1p0Mu17_vstar();
	if (l1ps_relIso1p0Mu5_vstar_branch != 0) l1ps_relIso1p0Mu5_vstar();
	if (ptj1_branch != 0) ptj1();
	if (nj1_branch != 0) nj1();
	if (ptj1_b2b_branch != 0) ptj1_b2b();
	if (dphij1_b2b_branch != 0) dphij1_b2b();
	if (ptpfj1_branch != 0) ptpfj1();
	if (npfj1_branch != 0) npfj1();
	if (ptpfj1_b2b_branch != 0) ptpfj1_b2b();
	if (dphipfj1_b2b_branch != 0) dphipfj1_b2b();
	if (ptpfcj1_branch != 0) ptpfcj1();
	if (npfcj1_branch != 0) npfcj1();
	if (ptpfcj1_b2b_branch != 0) ptpfcj1_b2b();
	if (dphipfcj1_b2b_branch != 0) dphipfcj1_b2b();
	if (btagpfc_branch != 0) btagpfc();
	if (emfpfcL1Fj1_branch != 0) emfpfcL1Fj1();
	if (ptpfcL1Fj1_branch != 0) ptpfcL1Fj1();
	if (dphipfcL1Fj1_branch != 0) dphipfcL1Fj1();
	if (npfcL1Fj1_branch != 0) npfcL1Fj1();
	if (npfc30L1Fj1_branch != 0) npfc30L1Fj1();
	if (npfc40L1Fj1_branch != 0) npfc40L1Fj1();
	if (ptpfcL1Fj1_b2b_branch != 0) ptpfcL1Fj1_b2b();
	if (dphipfcL1Fj1_b2b_branch != 0) dphipfcL1Fj1_b2b();
	if (btagpfcL1F_branch != 0) btagpfcL1F();
	if (emfpfcL1Fj1res_branch != 0) emfpfcL1Fj1res();
	if (ptpfcL1Fj1res_branch != 0) ptpfcL1Fj1res();
	if (dphipfcL1Fj1res_branch != 0) dphipfcL1Fj1res();
	if (npfcL1Fj1res_branch != 0) npfcL1Fj1res();
	if (npfc30L1Fj1res_branch != 0) npfc30L1Fj1res();
	if (npfc40L1Fj1res_branch != 0) npfc40L1Fj1res();
	if (ptpfcL1Fj1res_b2b_branch != 0) ptpfcL1Fj1res_b2b();
	if (dphipfcL1Fj1res_b2b_branch != 0) dphipfcL1Fj1res_b2b();
	if (btagpfcL1Fres_branch != 0) btagpfcL1Fres();
	if (ptbtagpfcL1Fj1_branch != 0) ptbtagpfcL1Fj1();
	if (dphibtagpfcL1Fj1_branch != 0) dphibtagpfcL1Fj1();
	if (ptbtagpfcL1Fj1res_branch != 0) ptbtagpfcL1Fj1res();
	if (dphibtagpfcL1Fj1res_branch != 0) dphibtagpfcL1Fj1res();
	if (nbjet_branch != 0) nbjet();
	if (dRNear_branch != 0) dRNear();
	if (dRFar_branch != 0) dRFar();
	if (nbpfcjet_branch != 0) nbpfcjet();
	if (dRpfcNear_branch != 0) dRpfcNear();
	if (dRpfcFar_branch != 0) dRpfcFar();
	if (rho_branch != 0) rho();
}

	int &run()
	{
		if (not run_isLoaded) {
			if (run_branch != 0) {
				run_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch run_branch does not exist!\n");
				exit(1);
			}
			run_isLoaded = true;
		}
		return run_;
	}
	int &ls()
	{
		if (not ls_isLoaded) {
			if (ls_branch != 0) {
				ls_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
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
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch evt_branch does not exist!\n");
				exit(1);
			}
			evt_isLoaded = true;
		}
		return evt_;
	}
	float &weight()
	{
		if (not weight_isLoaded) {
			if (weight_branch != 0) {
				weight_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch weight_branch does not exist!\n");
				exit(1);
			}
			weight_isLoaded = true;
		}
		return weight_;
	}
	int &pu_nPUvertices()
	{
		if (not pu_nPUvertices_isLoaded) {
			if (pu_nPUvertices_branch != 0) {
				pu_nPUvertices_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch pu_nPUvertices_branch does not exist!\n");
				exit(1);
			}
			pu_nPUvertices_isLoaded = true;
		}
		return pu_nPUvertices_;
	}
	int &evt_nvtxs()
	{
		if (not evt_nvtxs_isLoaded) {
			if (evt_nvtxs_branch != 0) {
				evt_nvtxs_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch evt_nvtxs_branch does not exist!\n");
				exit(1);
			}
			evt_nvtxs_isLoaded = true;
		}
		return evt_nvtxs_;
	}
	int &nFOels()
	{
		if (not nFOels_isLoaded) {
			if (nFOels_branch != 0) {
				nFOels_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch nFOels_branch does not exist!\n");
				exit(1);
			}
			nFOels_isLoaded = true;
		}
		return nFOels_;
	}
	int &nFOmus()
	{
		if (not nFOmus_isLoaded) {
			if (nFOmus_branch != 0) {
				nFOmus_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch nFOmus_branch does not exist!\n");
				exit(1);
			}
			nFOmus_isLoaded = true;
		}
		return nFOmus_;
	}
	int &ngsfs()
	{
		if (not ngsfs_isLoaded) {
			if (ngsfs_branch != 0) {
				ngsfs_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ngsfs_branch does not exist!\n");
				exit(1);
			}
			ngsfs_isLoaded = true;
		}
		return ngsfs_;
	}
	int &nmus()
	{
		if (not nmus_isLoaded) {
			if (nmus_branch != 0) {
				nmus_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch nmus_branch does not exist!\n");
				exit(1);
			}
			nmus_isLoaded = true;
		}
		return nmus_;
	}
	int &foel_id()
	{
		if (not foel_id_isLoaded) {
			if (foel_id_branch != 0) {
				foel_id_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch foel_id_branch does not exist!\n");
				exit(1);
			}
			foel_id_isLoaded = true;
		}
		return foel_id_;
	}
	int &fomu_id()
	{
		if (not fomu_id_isLoaded) {
			if (fomu_id_branch != 0) {
				fomu_id_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch fomu_id_branch does not exist!\n");
				exit(1);
			}
			fomu_id_isLoaded = true;
		}
		return fomu_id_;
	}
	float &foel_mass()
	{
		if (not foel_mass_isLoaded) {
			if (foel_mass_branch != 0) {
				foel_mass_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch foel_mass_branch does not exist!\n");
				exit(1);
			}
			foel_mass_isLoaded = true;
		}
		return foel_mass_;
	}
	float &fomu_mass()
	{
		if (not fomu_mass_isLoaded) {
			if (fomu_mass_branch != 0) {
				fomu_mass_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch fomu_mass_branch does not exist!\n");
				exit(1);
			}
			fomu_mass_isLoaded = true;
		}
		return fomu_mass_;
	}
	float &pt()
	{
		if (not pt_isLoaded) {
			if (pt_branch != 0) {
				pt_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch pt_branch does not exist!\n");
				exit(1);
			}
			pt_isLoaded = true;
		}
		return pt_;
	}
	float &eta()
	{
		if (not eta_isLoaded) {
			if (eta_branch != 0) {
				eta_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch eta_branch does not exist!\n");
				exit(1);
			}
			eta_isLoaded = true;
		}
		return eta_;
	}
	float &sceta()
	{
		if (not sceta_isLoaded) {
			if (sceta_branch != 0) {
				sceta_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch sceta_branch does not exist!\n");
				exit(1);
			}
			sceta_isLoaded = true;
		}
		return sceta_;
	}
	float &phi()
	{
		if (not phi_isLoaded) {
			if (phi_branch != 0) {
				phi_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch phi_branch does not exist!\n");
				exit(1);
			}
			phi_isLoaded = true;
		}
		return phi_;
	}
	float &scet()
	{
		if (not scet_isLoaded) {
			if (scet_branch != 0) {
				scet_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch scet_branch does not exist!\n");
				exit(1);
			}
			scet_isLoaded = true;
		}
		return scet_;
	}
	float &hoe()
	{
		if (not hoe_isLoaded) {
			if (hoe_branch != 0) {
				hoe_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hoe_branch does not exist!\n");
				exit(1);
			}
			hoe_isLoaded = true;
		}
		return hoe_;
	}
	float &pfmet()
	{
		if (not pfmet_isLoaded) {
			if (pfmet_branch != 0) {
				pfmet_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch pfmet_branch does not exist!\n");
				exit(1);
			}
			pfmet_isLoaded = true;
		}
		return pfmet_;
	}
	float &pfmetphi()
	{
		if (not pfmetphi_isLoaded) {
			if (pfmetphi_branch != 0) {
				pfmetphi_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch pfmetphi_branch does not exist!\n");
				exit(1);
			}
			pfmetphi_isLoaded = true;
		}
		return pfmetphi_;
	}
	float &iso()
	{
		if (not iso_isLoaded) {
			if (iso_branch != 0) {
				iso_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch iso_branch does not exist!\n");
				exit(1);
			}
			iso_isLoaded = true;
		}
		return iso_;
	}
	float &iso_nps()
	{
		if (not iso_nps_isLoaded) {
			if (iso_nps_branch != 0) {
				iso_nps_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch iso_nps_branch does not exist!\n");
				exit(1);
			}
			iso_nps_isLoaded = true;
		}
		return iso_nps_;
	}
	float &trck_iso()
	{
		if (not trck_iso_isLoaded) {
			if (trck_iso_branch != 0) {
				trck_iso_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch trck_iso_branch does not exist!\n");
				exit(1);
			}
			trck_iso_isLoaded = true;
		}
		return trck_iso_;
	}
	float &ecal_iso()
	{
		if (not ecal_iso_isLoaded) {
			if (ecal_iso_branch != 0) {
				ecal_iso_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ecal_iso_branch does not exist!\n");
				exit(1);
			}
			ecal_iso_isLoaded = true;
		}
		return ecal_iso_;
	}
	float &ecal_iso_nps()
	{
		if (not ecal_iso_nps_isLoaded) {
			if (ecal_iso_nps_branch != 0) {
				ecal_iso_nps_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ecal_iso_nps_branch does not exist!\n");
				exit(1);
			}
			ecal_iso_nps_isLoaded = true;
		}
		return ecal_iso_nps_;
	}
	float &hcal_iso()
	{
		if (not hcal_iso_isLoaded) {
			if (hcal_iso_branch != 0) {
				hcal_iso_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hcal_iso_branch does not exist!\n");
				exit(1);
			}
			hcal_iso_isLoaded = true;
		}
		return hcal_iso_;
	}
	float &pfiso03()
	{
		if (not pfiso03_isLoaded) {
			if (pfiso03_branch != 0) {
				pfiso03_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch pfiso03_branch does not exist!\n");
				exit(1);
			}
			pfiso03_isLoaded = true;
		}
		return pfiso03_;
	}
	float &ch_pfiso03()
	{
		if (not ch_pfiso03_isLoaded) {
			if (ch_pfiso03_branch != 0) {
				ch_pfiso03_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ch_pfiso03_branch does not exist!\n");
				exit(1);
			}
			ch_pfiso03_isLoaded = true;
		}
		return ch_pfiso03_;
	}
	float &nh_pfiso03()
	{
		if (not nh_pfiso03_isLoaded) {
			if (nh_pfiso03_branch != 0) {
				nh_pfiso03_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch nh_pfiso03_branch does not exist!\n");
				exit(1);
			}
			nh_pfiso03_isLoaded = true;
		}
		return nh_pfiso03_;
	}
	float &em_pfiso03()
	{
		if (not em_pfiso03_isLoaded) {
			if (em_pfiso03_branch != 0) {
				em_pfiso03_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch em_pfiso03_branch does not exist!\n");
				exit(1);
			}
			em_pfiso03_isLoaded = true;
		}
		return em_pfiso03_;
	}
	float &pfiso04()
	{
		if (not pfiso04_isLoaded) {
			if (pfiso04_branch != 0) {
				pfiso04_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch pfiso04_branch does not exist!\n");
				exit(1);
			}
			pfiso04_isLoaded = true;
		}
		return pfiso04_;
	}
	float &ch_pfiso04()
	{
		if (not ch_pfiso04_isLoaded) {
			if (ch_pfiso04_branch != 0) {
				ch_pfiso04_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ch_pfiso04_branch does not exist!\n");
				exit(1);
			}
			ch_pfiso04_isLoaded = true;
		}
		return ch_pfiso04_;
	}
	float &nh_pfiso04()
	{
		if (not nh_pfiso04_isLoaded) {
			if (nh_pfiso04_branch != 0) {
				nh_pfiso04_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch nh_pfiso04_branch does not exist!\n");
				exit(1);
			}
			nh_pfiso04_isLoaded = true;
		}
		return nh_pfiso04_;
	}
	float &em_pfiso04()
	{
		if (not em_pfiso04_isLoaded) {
			if (em_pfiso04_branch != 0) {
				em_pfiso04_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch em_pfiso04_branch does not exist!\n");
				exit(1);
			}
			em_pfiso04_isLoaded = true;
		}
		return em_pfiso04_;
	}
	float &pfpupt03()
	{
		if (not pfpupt03_isLoaded) {
			if (pfpupt03_branch != 0) {
				pfpupt03_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch pfpupt03_branch does not exist!\n");
				exit(1);
			}
			pfpupt03_isLoaded = true;
		}
		return pfpupt03_;
	}
	float &pfpupt04()
	{
		if (not pfpupt04_isLoaded) {
			if (pfpupt04_branch != 0) {
				pfpupt04_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch pfpupt04_branch does not exist!\n");
				exit(1);
			}
			pfpupt04_isLoaded = true;
		}
		return pfpupt04_;
	}
	float &cpfiso03_rho()
	{
		if (not cpfiso03_rho_isLoaded) {
			if (cpfiso03_rho_branch != 0) {
				cpfiso03_rho_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch cpfiso03_rho_branch does not exist!\n");
				exit(1);
			}
			cpfiso03_rho_isLoaded = true;
		}
		return cpfiso03_rho_;
	}
	float &cpfiso03_db()
	{
		if (not cpfiso03_db_isLoaded) {
			if (cpfiso03_db_branch != 0) {
				cpfiso03_db_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch cpfiso03_db_branch does not exist!\n");
				exit(1);
			}
			cpfiso03_db_isLoaded = true;
		}
		return cpfiso03_db_;
	}
	int &id()
	{
		if (not id_isLoaded) {
			if (id_branch != 0) {
				id_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch id_branch does not exist!\n");
				exit(1);
			}
			id_isLoaded = true;
		}
		return id_;
	}
	bool &	closestMuon()
	{
		if (not closestMuon_isLoaded) {
			if (closestMuon_branch != 0) {
				closestMuon_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch closestMuon_branch does not exist!\n");
				exit(1);
			}
			closestMuon_isLoaded = true;
		}
		return closestMuon_;
	}
	float &el_id_sieie()
	{
		if (not el_id_sieie_isLoaded) {
			if (el_id_sieie_branch != 0) {
				el_id_sieie_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch el_id_sieie_branch does not exist!\n");
				exit(1);
			}
			el_id_sieie_isLoaded = true;
		}
		return el_id_sieie_;
	}
	float &el_id_detain()
	{
		if (not el_id_detain_isLoaded) {
			if (el_id_detain_branch != 0) {
				el_id_detain_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch el_id_detain_branch does not exist!\n");
				exit(1);
			}
			el_id_detain_isLoaded = true;
		}
		return el_id_detain_;
	}
	float &el_id_dphiin()
	{
		if (not el_id_dphiin_isLoaded) {
			if (el_id_dphiin_branch != 0) {
				el_id_dphiin_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch el_id_dphiin_branch does not exist!\n");
				exit(1);
			}
			el_id_dphiin_isLoaded = true;
		}
		return el_id_dphiin_;
	}
	bool &	el_id_smurfV5()
	{
		if (not el_id_smurfV5_isLoaded) {
			if (el_id_smurfV5_branch != 0) {
				el_id_smurfV5_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch el_id_smurfV5_branch does not exist!\n");
				exit(1);
			}
			el_id_smurfV5_isLoaded = true;
		}
		return el_id_smurfV5_;
	}
	bool &	el_id_vbtf80()
	{
		if (not el_id_vbtf80_isLoaded) {
			if (el_id_vbtf80_branch != 0) {
				el_id_vbtf80_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch el_id_vbtf80_branch does not exist!\n");
				exit(1);
			}
			el_id_vbtf80_isLoaded = true;
		}
		return el_id_vbtf80_;
	}
	bool &	el_id_vbtf90()
	{
		if (not el_id_vbtf90_isLoaded) {
			if (el_id_vbtf90_branch != 0) {
				el_id_vbtf90_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch el_id_vbtf90_branch does not exist!\n");
				exit(1);
			}
			el_id_vbtf90_isLoaded = true;
		}
		return el_id_vbtf90_;
	}
	float &el_effarea()
	{
		if (not el_effarea_isLoaded) {
			if (el_effarea_branch != 0) {
				el_effarea_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch el_effarea_branch does not exist!\n");
				exit(1);
			}
			el_effarea_isLoaded = true;
		}
		return el_effarea_;
	}
	float &mu_effarea03()
	{
		if (not mu_effarea03_isLoaded) {
			if (mu_effarea03_branch != 0) {
				mu_effarea03_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu_effarea03_branch does not exist!\n");
				exit(1);
			}
			mu_effarea03_isLoaded = true;
		}
		return mu_effarea03_;
	}
	float &mu_nh_effarea03()
	{
		if (not mu_nh_effarea03_isLoaded) {
			if (mu_nh_effarea03_branch != 0) {
				mu_nh_effarea03_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu_nh_effarea03_branch does not exist!\n");
				exit(1);
			}
			mu_nh_effarea03_isLoaded = true;
		}
		return mu_nh_effarea03_;
	}
	float &mu_em_effarea03()
	{
		if (not mu_em_effarea03_isLoaded) {
			if (mu_em_effarea03_branch != 0) {
				mu_em_effarea03_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu_em_effarea03_branch does not exist!\n");
				exit(1);
			}
			mu_em_effarea03_isLoaded = true;
		}
		return mu_em_effarea03_;
	}
	float &mu_effarea03_tight()
	{
		if (not mu_effarea03_tight_isLoaded) {
			if (mu_effarea03_tight_branch != 0) {
				mu_effarea03_tight_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu_effarea03_tight_branch does not exist!\n");
				exit(1);
			}
			mu_effarea03_tight_isLoaded = true;
		}
		return mu_effarea03_tight_;
	}
	float &mu_nh_effarea03_tight()
	{
		if (not mu_nh_effarea03_tight_isLoaded) {
			if (mu_nh_effarea03_tight_branch != 0) {
				mu_nh_effarea03_tight_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu_nh_effarea03_tight_branch does not exist!\n");
				exit(1);
			}
			mu_nh_effarea03_tight_isLoaded = true;
		}
		return mu_nh_effarea03_tight_;
	}
	float &mu_em_effarea03_tight()
	{
		if (not mu_em_effarea03_tight_isLoaded) {
			if (mu_em_effarea03_tight_branch != 0) {
				mu_em_effarea03_tight_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu_em_effarea03_tight_branch does not exist!\n");
				exit(1);
			}
			mu_em_effarea03_tight_isLoaded = true;
		}
		return mu_em_effarea03_tight_;
	}
	float &mu_effarea04()
	{
		if (not mu_effarea04_isLoaded) {
			if (mu_effarea04_branch != 0) {
				mu_effarea04_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu_effarea04_branch does not exist!\n");
				exit(1);
			}
			mu_effarea04_isLoaded = true;
		}
		return mu_effarea04_;
	}
	float &mu_nh_effarea04()
	{
		if (not mu_nh_effarea04_isLoaded) {
			if (mu_nh_effarea04_branch != 0) {
				mu_nh_effarea04_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu_nh_effarea04_branch does not exist!\n");
				exit(1);
			}
			mu_nh_effarea04_isLoaded = true;
		}
		return mu_nh_effarea04_;
	}
	float &mu_em_effarea04()
	{
		if (not mu_em_effarea04_isLoaded) {
			if (mu_em_effarea04_branch != 0) {
				mu_em_effarea04_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu_em_effarea04_branch does not exist!\n");
				exit(1);
			}
			mu_em_effarea04_isLoaded = true;
		}
		return mu_em_effarea04_;
	}
	float &mu_effarea04_tight()
	{
		if (not mu_effarea04_tight_isLoaded) {
			if (mu_effarea04_tight_branch != 0) {
				mu_effarea04_tight_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu_effarea04_tight_branch does not exist!\n");
				exit(1);
			}
			mu_effarea04_tight_isLoaded = true;
		}
		return mu_effarea04_tight_;
	}
	float &mu_nh_effarea04_tight()
	{
		if (not mu_nh_effarea04_tight_isLoaded) {
			if (mu_nh_effarea04_tight_branch != 0) {
				mu_nh_effarea04_tight_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu_nh_effarea04_tight_branch does not exist!\n");
				exit(1);
			}
			mu_nh_effarea04_tight_isLoaded = true;
		}
		return mu_nh_effarea04_tight_;
	}
	float &mu_em_effarea04_tight()
	{
		if (not mu_em_effarea04_tight_isLoaded) {
			if (mu_em_effarea04_tight_branch != 0) {
				mu_em_effarea04_tight_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu_em_effarea04_tight_branch does not exist!\n");
				exit(1);
			}
			mu_em_effarea04_tight_isLoaded = true;
		}
		return mu_em_effarea04_tight_;
	}
	bool &	conv0MissHits()
	{
		if (not conv0MissHits_isLoaded) {
			if (conv0MissHits_branch != 0) {
				conv0MissHits_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch conv0MissHits_branch does not exist!\n");
				exit(1);
			}
			conv0MissHits_isLoaded = true;
		}
		return conv0MissHits_;
	}
	bool &	convHitPattern()
	{
		if (not convHitPattern_isLoaded) {
			if (convHitPattern_branch != 0) {
				convHitPattern_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch convHitPattern_branch does not exist!\n");
				exit(1);
			}
			convHitPattern_isLoaded = true;
		}
		return convHitPattern_;
	}
	bool &	convPartnerTrack()
	{
		if (not convPartnerTrack_isLoaded) {
			if (convPartnerTrack_branch != 0) {
				convPartnerTrack_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch convPartnerTrack_branch does not exist!\n");
				exit(1);
			}
			convPartnerTrack_isLoaded = true;
		}
		return convPartnerTrack_;
	}
	bool &	convMIT()
	{
		if (not convMIT_isLoaded) {
			if (convMIT_branch != 0) {
				convMIT_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch convMIT_branch does not exist!\n");
				exit(1);
			}
			convMIT_isLoaded = true;
		}
		return convMIT_;
	}
	float &mt()
	{
		if (not mt_isLoaded) {
			if (mt_branch != 0) {
				mt_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mt_branch does not exist!\n");
				exit(1);
			}
			mt_isLoaded = true;
		}
		return mt_;
	}
	float &pfmt()
	{
		if (not pfmt_isLoaded) {
			if (pfmt_branch != 0) {
				pfmt_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch pfmt_branch does not exist!\n");
				exit(1);
			}
			pfmt_isLoaded = true;
		}
		return pfmt_;
	}
	bool &	q3()
	{
		if (not q3_isLoaded) {
			if (q3_branch != 0) {
				q3_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch q3_branch does not exist!\n");
				exit(1);
			}
			q3_isLoaded = true;
		}
		return q3_;
	}
	int &els_exp_innerlayers()
	{
		if (not els_exp_innerlayers_isLoaded) {
			if (els_exp_innerlayers_branch != 0) {
				els_exp_innerlayers_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch els_exp_innerlayers_branch does not exist!\n");
				exit(1);
			}
			els_exp_innerlayers_isLoaded = true;
		}
		return els_exp_innerlayers_;
	}
	float &d0PV_wwV1()
	{
		if (not d0PV_wwV1_isLoaded) {
			if (d0PV_wwV1_branch != 0) {
				d0PV_wwV1_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch d0PV_wwV1_branch does not exist!\n");
				exit(1);
			}
			d0PV_wwV1_isLoaded = true;
		}
		return d0PV_wwV1_;
	}
	float &dzPV_wwV1()
	{
		if (not dzPV_wwV1_isLoaded) {
			if (dzPV_wwV1_branch != 0) {
				dzPV_wwV1_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dzPV_wwV1_branch does not exist!\n");
				exit(1);
			}
			dzPV_wwV1_isLoaded = true;
		}
		return dzPV_wwV1_;
	}
	float &ht_calo()
	{
		if (not ht_calo_isLoaded) {
			if (ht_calo_branch != 0) {
				ht_calo_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ht_calo_branch does not exist!\n");
				exit(1);
			}
			ht_calo_isLoaded = true;
		}
		return ht_calo_;
	}
	float &ht_calo_L2L3()
	{
		if (not ht_calo_L2L3_isLoaded) {
			if (ht_calo_L2L3_branch != 0) {
				ht_calo_L2L3_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ht_calo_L2L3_branch does not exist!\n");
				exit(1);
			}
			ht_calo_L2L3_isLoaded = true;
		}
		return ht_calo_L2L3_;
	}
	float &ht_pf()
	{
		if (not ht_pf_isLoaded) {
			if (ht_pf_branch != 0) {
				ht_pf_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ht_pf_branch does not exist!\n");
				exit(1);
			}
			ht_pf_isLoaded = true;
		}
		return ht_pf_;
	}
	float &ht_pf_L2L3()
	{
		if (not ht_pf_L2L3_isLoaded) {
			if (ht_pf_L2L3_branch != 0) {
				ht_pf_L2L3_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ht_pf_L2L3_branch does not exist!\n");
				exit(1);
			}
			ht_pf_L2L3_isLoaded = true;
		}
		return ht_pf_L2L3_;
	}
	float &ht_pf_L1FastL2L3()
	{
		if (not ht_pf_L1FastL2L3_isLoaded) {
			if (ht_pf_L1FastL2L3_branch != 0) {
				ht_pf_L1FastL2L3_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ht_pf_L1FastL2L3_branch does not exist!\n");
				exit(1);
			}
			ht_pf_L1FastL2L3_isLoaded = true;
		}
		return ht_pf_L1FastL2L3_;
	}
	int &mcid()
	{
		if (not mcid_isLoaded) {
			if (mcid_branch != 0) {
				mcid_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mcid_branch does not exist!\n");
				exit(1);
			}
			mcid_isLoaded = true;
		}
		return mcid_;
	}
	int &mcmotherid()
	{
		if (not mcmotherid_isLoaded) {
			if (mcmotherid_branch != 0) {
				mcmotherid_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mcmotherid_branch does not exist!\n");
				exit(1);
			}
			mcmotherid_isLoaded = true;
		}
		return mcmotherid_;
	}
	int &mc3id()
	{
		if (not mc3id_isLoaded) {
			if (mc3id_branch != 0) {
				mc3id_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mc3id_branch does not exist!\n");
				exit(1);
			}
			mc3id_isLoaded = true;
		}
		return mc3id_;
	}
	float &mc3pt()
	{
		if (not mc3pt_isLoaded) {
			if (mc3pt_branch != 0) {
				mc3pt_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mc3pt_branch does not exist!\n");
				exit(1);
			}
			mc3pt_isLoaded = true;
		}
		return mc3pt_;
	}
	float &mc3dr()
	{
		if (not mc3dr_isLoaded) {
			if (mc3dr_branch != 0) {
				mc3dr_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mc3dr_branch does not exist!\n");
				exit(1);
			}
			mc3dr_isLoaded = true;
		}
		return mc3dr_;
	}
	int &leptonIsFromW()
	{
		if (not leptonIsFromW_isLoaded) {
			if (leptonIsFromW_branch != 0) {
				leptonIsFromW_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch leptonIsFromW_branch does not exist!\n");
				exit(1);
			}
			leptonIsFromW_isLoaded = true;
		}
		return leptonIsFromW_;
	}
	bool &	mu_isCosmic()
	{
		if (not mu_isCosmic_isLoaded) {
			if (mu_isCosmic_branch != 0) {
				mu_isCosmic_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu_isCosmic_branch does not exist!\n");
				exit(1);
			}
			mu_isCosmic_isLoaded = true;
		}
		return mu_isCosmic_;
	}
	float &mz_fo_gsf()
	{
		if (not mz_fo_gsf_isLoaded) {
			if (mz_fo_gsf_branch != 0) {
				mz_fo_gsf_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mz_fo_gsf_branch does not exist!\n");
				exit(1);
			}
			mz_fo_gsf_isLoaded = true;
		}
		return mz_fo_gsf_;
	}
	float &mz_gsf_iso()
	{
		if (not mz_gsf_iso_isLoaded) {
			if (mz_gsf_iso_branch != 0) {
				mz_gsf_iso_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mz_gsf_iso_branch does not exist!\n");
				exit(1);
			}
			mz_gsf_iso_isLoaded = true;
		}
		return mz_gsf_iso_;
	}
	float &mz_fo_ctf()
	{
		if (not mz_fo_ctf_isLoaded) {
			if (mz_fo_ctf_branch != 0) {
				mz_fo_ctf_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mz_fo_ctf_branch does not exist!\n");
				exit(1);
			}
			mz_fo_ctf_isLoaded = true;
		}
		return mz_fo_ctf_;
	}
	float &mz_ctf_iso()
	{
		if (not mz_ctf_iso_isLoaded) {
			if (mz_ctf_iso_branch != 0) {
				mz_ctf_iso_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mz_ctf_iso_branch does not exist!\n");
				exit(1);
			}
			mz_ctf_iso_isLoaded = true;
		}
		return mz_ctf_iso_;
	}
	float &mupsilon_fo_mu()
	{
		if (not mupsilon_fo_mu_isLoaded) {
			if (mupsilon_fo_mu_branch != 0) {
				mupsilon_fo_mu_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mupsilon_fo_mu_branch does not exist!\n");
				exit(1);
			}
			mupsilon_fo_mu_isLoaded = true;
		}
		return mupsilon_fo_mu_;
	}
	float &mupsilon_mu_iso()
	{
		if (not mupsilon_mu_iso_isLoaded) {
			if (mupsilon_mu_iso_branch != 0) {
				mupsilon_mu_iso_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mupsilon_mu_iso_branch does not exist!\n");
				exit(1);
			}
			mupsilon_mu_iso_isLoaded = true;
		}
		return mupsilon_mu_iso_;
	}
	bool &	num_el_ssV7()
	{
		if (not num_el_ssV7_isLoaded) {
			if (num_el_ssV7_branch != 0) {
				num_el_ssV7_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch num_el_ssV7_branch does not exist!\n");
				exit(1);
			}
			num_el_ssV7_isLoaded = true;
		}
		return num_el_ssV7_;
	}
	bool &	num_el_ssV7_noIso()
	{
		if (not num_el_ssV7_noIso_isLoaded) {
			if (num_el_ssV7_noIso_branch != 0) {
				num_el_ssV7_noIso_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch num_el_ssV7_noIso_branch does not exist!\n");
				exit(1);
			}
			num_el_ssV7_noIso_isLoaded = true;
		}
		return num_el_ssV7_noIso_;
	}
	bool &	v1_el_ssV7()
	{
		if (not v1_el_ssV7_isLoaded) {
			if (v1_el_ssV7_branch != 0) {
				v1_el_ssV7_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch v1_el_ssV7_branch does not exist!\n");
				exit(1);
			}
			v1_el_ssV7_isLoaded = true;
		}
		return v1_el_ssV7_;
	}
	bool &	v2_el_ssV7()
	{
		if (not v2_el_ssV7_isLoaded) {
			if (v2_el_ssV7_branch != 0) {
				v2_el_ssV7_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch v2_el_ssV7_branch does not exist!\n");
				exit(1);
			}
			v2_el_ssV7_isLoaded = true;
		}
		return v2_el_ssV7_;
	}
	bool &	v3_el_ssV7()
	{
		if (not v3_el_ssV7_isLoaded) {
			if (v3_el_ssV7_branch != 0) {
				v3_el_ssV7_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch v3_el_ssV7_branch does not exist!\n");
				exit(1);
			}
			v3_el_ssV7_isLoaded = true;
		}
		return v3_el_ssV7_;
	}
	bool &	num_mu_ssV5()
	{
		if (not num_mu_ssV5_isLoaded) {
			if (num_mu_ssV5_branch != 0) {
				num_mu_ssV5_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch num_mu_ssV5_branch does not exist!\n");
				exit(1);
			}
			num_mu_ssV5_isLoaded = true;
		}
		return num_mu_ssV5_;
	}
	bool &	num_mu_ssV5_noIso()
	{
		if (not num_mu_ssV5_noIso_isLoaded) {
			if (num_mu_ssV5_noIso_branch != 0) {
				num_mu_ssV5_noIso_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch num_mu_ssV5_noIso_branch does not exist!\n");
				exit(1);
			}
			num_mu_ssV5_noIso_isLoaded = true;
		}
		return num_mu_ssV5_noIso_;
	}
	bool &	fo_mu_ssV5()
	{
		if (not fo_mu_ssV5_isLoaded) {
			if (fo_mu_ssV5_branch != 0) {
				fo_mu_ssV5_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch fo_mu_ssV5_branch does not exist!\n");
				exit(1);
			}
			fo_mu_ssV5_isLoaded = true;
		}
		return fo_mu_ssV5_;
	}
	bool &	fo_mu_ssV5_noIso()
	{
		if (not fo_mu_ssV5_noIso_isLoaded) {
			if (fo_mu_ssV5_noIso_branch != 0) {
				fo_mu_ssV5_noIso_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch fo_mu_ssV5_noIso_branch does not exist!\n");
				exit(1);
			}
			fo_mu_ssV5_noIso_isLoaded = true;
		}
		return fo_mu_ssV5_noIso_;
	}
	bool &	num_el_ssV6()
	{
		if (not num_el_ssV6_isLoaded) {
			if (num_el_ssV6_branch != 0) {
				num_el_ssV6_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch num_el_ssV6_branch does not exist!\n");
				exit(1);
			}
			num_el_ssV6_isLoaded = true;
		}
		return num_el_ssV6_;
	}
	bool &	num_el_ssV6_noIso()
	{
		if (not num_el_ssV6_noIso_isLoaded) {
			if (num_el_ssV6_noIso_branch != 0) {
				num_el_ssV6_noIso_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch num_el_ssV6_noIso_branch does not exist!\n");
				exit(1);
			}
			num_el_ssV6_noIso_isLoaded = true;
		}
		return num_el_ssV6_noIso_;
	}
	bool &	v1_el_ssV6()
	{
		if (not v1_el_ssV6_isLoaded) {
			if (v1_el_ssV6_branch != 0) {
				v1_el_ssV6_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch v1_el_ssV6_branch does not exist!\n");
				exit(1);
			}
			v1_el_ssV6_isLoaded = true;
		}
		return v1_el_ssV6_;
	}
	bool &	v2_el_ssV6()
	{
		if (not v2_el_ssV6_isLoaded) {
			if (v2_el_ssV6_branch != 0) {
				v2_el_ssV6_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch v2_el_ssV6_branch does not exist!\n");
				exit(1);
			}
			v2_el_ssV6_isLoaded = true;
		}
		return v2_el_ssV6_;
	}
	bool &	v3_el_ssV6()
	{
		if (not v3_el_ssV6_isLoaded) {
			if (v3_el_ssV6_branch != 0) {
				v3_el_ssV6_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch v3_el_ssV6_branch does not exist!\n");
				exit(1);
			}
			v3_el_ssV6_isLoaded = true;
		}
		return v3_el_ssV6_;
	}
	bool &	numNomSSv4()
	{
		if (not numNomSSv4_isLoaded) {
			if (numNomSSv4_branch != 0) {
				numNomSSv4_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch numNomSSv4_branch does not exist!\n");
				exit(1);
			}
			numNomSSv4_isLoaded = true;
		}
		return numNomSSv4_;
	}
	bool &	numNomSSv4noIso()
	{
		if (not numNomSSv4noIso_isLoaded) {
			if (numNomSSv4noIso_branch != 0) {
				numNomSSv4noIso_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch numNomSSv4noIso_branch does not exist!\n");
				exit(1);
			}
			numNomSSv4noIso_isLoaded = true;
		}
		return numNomSSv4noIso_;
	}
	bool &	fo_mussV4_04()
	{
		if (not fo_mussV4_04_isLoaded) {
			if (fo_mussV4_04_branch != 0) {
				fo_mussV4_04_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch fo_mussV4_04_branch does not exist!\n");
				exit(1);
			}
			fo_mussV4_04_isLoaded = true;
		}
		return fo_mussV4_04_;
	}
	bool &	fo_mussV4_noIso()
	{
		if (not fo_mussV4_noIso_isLoaded) {
			if (fo_mussV4_noIso_branch != 0) {
				fo_mussV4_noIso_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch fo_mussV4_noIso_branch does not exist!\n");
				exit(1);
			}
			fo_mussV4_noIso_isLoaded = true;
		}
		return fo_mussV4_noIso_;
	}
	bool &	num_el_smurfV6()
	{
		if (not num_el_smurfV6_isLoaded) {
			if (num_el_smurfV6_branch != 0) {
				num_el_smurfV6_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch num_el_smurfV6_branch does not exist!\n");
				exit(1);
			}
			num_el_smurfV6_isLoaded = true;
		}
		return num_el_smurfV6_;
	}
	bool &	num_el_smurfV6lh()
	{
		if (not num_el_smurfV6lh_isLoaded) {
			if (num_el_smurfV6lh_branch != 0) {
				num_el_smurfV6lh_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch num_el_smurfV6lh_branch does not exist!\n");
				exit(1);
			}
			num_el_smurfV6lh_isLoaded = true;
		}
		return num_el_smurfV6lh_;
	}
	bool &	v1_el_smurfV1()
	{
		if (not v1_el_smurfV1_isLoaded) {
			if (v1_el_smurfV1_branch != 0) {
				v1_el_smurfV1_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch v1_el_smurfV1_branch does not exist!\n");
				exit(1);
			}
			v1_el_smurfV1_isLoaded = true;
		}
		return v1_el_smurfV1_;
	}
	bool &	v2_el_smurfV1()
	{
		if (not v2_el_smurfV1_isLoaded) {
			if (v2_el_smurfV1_branch != 0) {
				v2_el_smurfV1_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch v2_el_smurfV1_branch does not exist!\n");
				exit(1);
			}
			v2_el_smurfV1_isLoaded = true;
		}
		return v2_el_smurfV1_;
	}
	bool &	v3_el_smurfV1()
	{
		if (not v3_el_smurfV1_isLoaded) {
			if (v3_el_smurfV1_branch != 0) {
				v3_el_smurfV1_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch v3_el_smurfV1_branch does not exist!\n");
				exit(1);
			}
			v3_el_smurfV1_isLoaded = true;
		}
		return v3_el_smurfV1_;
	}
	bool &	v4_el_smurfV1()
	{
		if (not v4_el_smurfV1_isLoaded) {
			if (v4_el_smurfV1_branch != 0) {
				v4_el_smurfV1_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch v4_el_smurfV1_branch does not exist!\n");
				exit(1);
			}
			v4_el_smurfV1_isLoaded = true;
		}
		return v4_el_smurfV1_;
	}
	bool &	num_mu_smurfV6()
	{
		if (not num_mu_smurfV6_isLoaded) {
			if (num_mu_smurfV6_branch != 0) {
				num_mu_smurfV6_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch num_mu_smurfV6_branch does not exist!\n");
				exit(1);
			}
			num_mu_smurfV6_isLoaded = true;
		}
		return num_mu_smurfV6_;
	}
	bool &	fo_mu_smurf_04()
	{
		if (not fo_mu_smurf_04_isLoaded) {
			if (fo_mu_smurf_04_branch != 0) {
				fo_mu_smurf_04_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch fo_mu_smurf_04_branch does not exist!\n");
				exit(1);
			}
			fo_mu_smurf_04_isLoaded = true;
		}
		return fo_mu_smurf_04_;
	}
	bool &	fo_mu_smurf_10()
	{
		if (not fo_mu_smurf_10_isLoaded) {
			if (fo_mu_smurf_10_branch != 0) {
				fo_mu_smurf_10_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch fo_mu_smurf_10_branch does not exist!\n");
				exit(1);
			}
			fo_mu_smurf_10_isLoaded = true;
		}
		return fo_mu_smurf_10_;
	}
	bool &	num_el_OSV2()
	{
		if (not num_el_OSV2_isLoaded) {
			if (num_el_OSV2_branch != 0) {
				num_el_OSV2_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch num_el_OSV2_branch does not exist!\n");
				exit(1);
			}
			num_el_OSV2_isLoaded = true;
		}
		return num_el_OSV2_;
	}
	bool &	num_mu_OSGV2()
	{
		if (not num_mu_OSGV2_isLoaded) {
			if (num_mu_OSGV2_branch != 0) {
				num_mu_OSGV2_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch num_mu_OSGV2_branch does not exist!\n");
				exit(1);
			}
			num_mu_OSGV2_isLoaded = true;
		}
		return num_mu_OSGV2_;
	}
	bool &	num_mu_OSZV2()
	{
		if (not num_mu_OSZV2_isLoaded) {
			if (num_mu_OSZV2_branch != 0) {
				num_mu_OSZV2_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch num_mu_OSZV2_branch does not exist!\n");
				exit(1);
			}
			num_mu_OSZV2_isLoaded = true;
		}
		return num_mu_OSZV2_;
	}
	bool &	fo_el_OSV2()
	{
		if (not fo_el_OSV2_isLoaded) {
			if (fo_el_OSV2_branch != 0) {
				fo_el_OSV2_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch fo_el_OSV2_branch does not exist!\n");
				exit(1);
			}
			fo_el_OSV2_isLoaded = true;
		}
		return fo_el_OSV2_;
	}
	bool &	fo_mu_OSGV2()
	{
		if (not fo_mu_OSGV2_isLoaded) {
			if (fo_mu_OSGV2_branch != 0) {
				fo_mu_OSGV2_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch fo_mu_OSGV2_branch does not exist!\n");
				exit(1);
			}
			fo_mu_OSGV2_isLoaded = true;
		}
		return fo_mu_OSGV2_;
	}
	bool &	num_el_OSV3()
	{
		if (not num_el_OSV3_isLoaded) {
			if (num_el_OSV3_branch != 0) {
				num_el_OSV3_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch num_el_OSV3_branch does not exist!\n");
				exit(1);
			}
			num_el_OSV3_isLoaded = true;
		}
		return num_el_OSV3_;
	}
	bool &	num_mu_OSGV3()
	{
		if (not num_mu_OSGV3_isLoaded) {
			if (num_mu_OSGV3_branch != 0) {
				num_mu_OSGV3_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch num_mu_OSGV3_branch does not exist!\n");
				exit(1);
			}
			num_mu_OSGV3_isLoaded = true;
		}
		return num_mu_OSGV3_;
	}
	bool &	fo_el_OSV3()
	{
		if (not fo_el_OSV3_isLoaded) {
			if (fo_el_OSV3_branch != 0) {
				fo_el_OSV3_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch fo_el_OSV3_branch does not exist!\n");
				exit(1);
			}
			fo_el_OSV3_isLoaded = true;
		}
		return fo_el_OSV3_;
	}
	bool &	fo_mu_OSGV3()
	{
		if (not fo_mu_OSGV3_isLoaded) {
			if (fo_mu_OSGV3_branch != 0) {
				fo_mu_OSGV3_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch fo_mu_OSGV3_branch does not exist!\n");
				exit(1);
			}
			fo_mu_OSGV3_isLoaded = true;
		}
		return fo_mu_OSGV3_;
	}
	int &ele8_vstar()
	{
		if (not ele8_vstar_isLoaded) {
			if (ele8_vstar_branch != 0) {
				ele8_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele8_vstar_branch does not exist!\n");
				exit(1);
			}
			ele8_vstar_isLoaded = true;
		}
		return ele8_vstar_;
	}
	int &ele8_CaloIdL_TrkIdVL_vstar()
	{
		if (not ele8_CaloIdL_TrkIdVL_vstar_isLoaded) {
			if (ele8_CaloIdL_TrkIdVL_vstar_branch != 0) {
				ele8_CaloIdL_TrkIdVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele8_CaloIdL_TrkIdVL_vstar_branch does not exist!\n");
				exit(1);
			}
			ele8_CaloIdL_TrkIdVL_vstar_isLoaded = true;
		}
		return ele8_CaloIdL_TrkIdVL_vstar_;
	}
	int &ele8_CaloIdL_CaloIsoVL_Jet40_vstar()
	{
		if (not ele8_CaloIdL_CaloIsoVL_Jet40_vstar_isLoaded) {
			if (ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch != 0) {
				ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch does not exist!\n");
				exit(1);
			}
			ele8_CaloIdL_CaloIsoVL_Jet40_vstar_isLoaded = true;
		}
		return ele8_CaloIdL_CaloIsoVL_Jet40_vstar_;
	}
	int &ele8_CaloIdL_CaloIsoVL_vstar()
	{
		if (not ele8_CaloIdL_CaloIsoVL_vstar_isLoaded) {
			if (ele8_CaloIdL_CaloIsoVL_vstar_branch != 0) {
				ele8_CaloIdL_CaloIsoVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele8_CaloIdL_CaloIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			ele8_CaloIdL_CaloIsoVL_vstar_isLoaded = true;
		}
		return ele8_CaloIdL_CaloIsoVL_vstar_;
	}
	int &ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar()
	{
		if (not ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_isLoaded) {
			if (ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch != 0) {
				ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_isLoaded = true;
		}
		return ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_;
	}
	int &ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()
	{
		if (not ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded) {
			if (ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch != 0) {
				ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded = true;
		}
		return ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_;
	}
	int &ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()
	{
		if (not ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded) {
			if (ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch != 0) {
				ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch does not exist!\n");
				exit(1);
			}
			ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded = true;
		}
		return ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_;
	}
	int &ele8_CaloIdT_TrkIdVL_vstar()
	{
		if (not ele8_CaloIdT_TrkIdVL_vstar_isLoaded) {
			if (ele8_CaloIdT_TrkIdVL_vstar_branch != 0) {
				ele8_CaloIdT_TrkIdVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele8_CaloIdT_TrkIdVL_vstar_branch does not exist!\n");
				exit(1);
			}
			ele8_CaloIdT_TrkIdVL_vstar_isLoaded = true;
		}
		return ele8_CaloIdT_TrkIdVL_vstar_;
	}
	int &ele8_CaloIdT_TrkIdVL_Jet30_vstar()
	{
		if (not ele8_CaloIdT_TrkIdVL_Jet30_vstar_isLoaded) {
			if (ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch != 0) {
				ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch does not exist!\n");
				exit(1);
			}
			ele8_CaloIdT_TrkIdVL_Jet30_vstar_isLoaded = true;
		}
		return ele8_CaloIdT_TrkIdVL_Jet30_vstar_;
	}
	int &ele17_CaloIdL_CaloIsoVL_vstar()
	{
		if (not ele17_CaloIdL_CaloIsoVL_vstar_isLoaded) {
			if (ele17_CaloIdL_CaloIsoVL_vstar_branch != 0) {
				ele17_CaloIdL_CaloIsoVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele17_CaloIdL_CaloIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			ele17_CaloIdL_CaloIsoVL_vstar_isLoaded = true;
		}
		return ele17_CaloIdL_CaloIsoVL_vstar_;
	}
	int &ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()
	{
		if (not ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded) {
			if (ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch != 0) {
				ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded = true;
		}
		return ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_;
	}
	int &ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()
	{
		if (not ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded) {
			if (ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch != 0) {
				ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch does not exist!\n");
				exit(1);
			}
			ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded = true;
		}
		return ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_;
	}
	int &photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar()
	{
		if (not photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_isLoaded) {
			if (photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch != 0) {
				photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_isLoaded = true;
		}
		return photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_;
	}
	int &ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar()
	{
		if (not ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_isLoaded) {
			if (ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch != 0) {
				ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch does not exist!\n");
				exit(1);
			}
			ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_isLoaded = true;
		}
		return ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_;
	}
	int &ele27_WP80_vstar()
	{
		if (not ele27_WP80_vstar_isLoaded) {
			if (ele27_WP80_vstar_branch != 0) {
				ele27_WP80_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele27_WP80_vstar_branch does not exist!\n");
				exit(1);
			}
			ele27_WP80_vstar_isLoaded = true;
		}
		return ele27_WP80_vstar_;
	}
	int &ele8_version()
	{
		if (not ele8_version_isLoaded) {
			if (ele8_version_branch != 0) {
				ele8_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele8_version_branch does not exist!\n");
				exit(1);
			}
			ele8_version_isLoaded = true;
		}
		return ele8_version_;
	}
	int &ele8_CaloIdL_TrkIdVL_version()
	{
		if (not ele8_CaloIdL_TrkIdVL_version_isLoaded) {
			if (ele8_CaloIdL_TrkIdVL_version_branch != 0) {
				ele8_CaloIdL_TrkIdVL_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele8_CaloIdL_TrkIdVL_version_branch does not exist!\n");
				exit(1);
			}
			ele8_CaloIdL_TrkIdVL_version_isLoaded = true;
		}
		return ele8_CaloIdL_TrkIdVL_version_;
	}
	int &ele8_CaloIdL_CaloIsoVL_Jet40_version()
	{
		if (not ele8_CaloIdL_CaloIsoVL_Jet40_version_isLoaded) {
			if (ele8_CaloIdL_CaloIsoVL_Jet40_version_branch != 0) {
				ele8_CaloIdL_CaloIsoVL_Jet40_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele8_CaloIdL_CaloIsoVL_Jet40_version_branch does not exist!\n");
				exit(1);
			}
			ele8_CaloIdL_CaloIsoVL_Jet40_version_isLoaded = true;
		}
		return ele8_CaloIdL_CaloIsoVL_Jet40_version_;
	}
	int &ele8_CaloIdL_CaloIsoVL_version()
	{
		if (not ele8_CaloIdL_CaloIsoVL_version_isLoaded) {
			if (ele8_CaloIdL_CaloIsoVL_version_branch != 0) {
				ele8_CaloIdL_CaloIsoVL_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele8_CaloIdL_CaloIsoVL_version_branch does not exist!\n");
				exit(1);
			}
			ele8_CaloIdL_CaloIsoVL_version_isLoaded = true;
		}
		return ele8_CaloIdL_CaloIsoVL_version_;
	}
	int &ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version()
	{
		if (not ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_isLoaded) {
			if (ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_branch != 0) {
				ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_branch does not exist!\n");
				exit(1);
			}
			ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_isLoaded = true;
		}
		return ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_;
	}
	int &ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version()
	{
		if (not ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_isLoaded) {
			if (ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_branch != 0) {
				ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_branch does not exist!\n");
				exit(1);
			}
			ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_isLoaded = true;
		}
		return ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_;
	}
	int &ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version()
	{
		if (not ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_isLoaded) {
			if (ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_branch != 0) {
				ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_branch does not exist!\n");
				exit(1);
			}
			ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_isLoaded = true;
		}
		return ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_;
	}
	int &ele8_CaloIdT_TrkIdVL_version()
	{
		if (not ele8_CaloIdT_TrkIdVL_version_isLoaded) {
			if (ele8_CaloIdT_TrkIdVL_version_branch != 0) {
				ele8_CaloIdT_TrkIdVL_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele8_CaloIdT_TrkIdVL_version_branch does not exist!\n");
				exit(1);
			}
			ele8_CaloIdT_TrkIdVL_version_isLoaded = true;
		}
		return ele8_CaloIdT_TrkIdVL_version_;
	}
	int &ele8_CaloIdT_TrkIdVL_Jet30_version()
	{
		if (not ele8_CaloIdT_TrkIdVL_Jet30_version_isLoaded) {
			if (ele8_CaloIdT_TrkIdVL_Jet30_version_branch != 0) {
				ele8_CaloIdT_TrkIdVL_Jet30_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele8_CaloIdT_TrkIdVL_Jet30_version_branch does not exist!\n");
				exit(1);
			}
			ele8_CaloIdT_TrkIdVL_Jet30_version_isLoaded = true;
		}
		return ele8_CaloIdT_TrkIdVL_Jet30_version_;
	}
	int &ele17_CaloIdL_CaloIsoVL_version()
	{
		if (not ele17_CaloIdL_CaloIsoVL_version_isLoaded) {
			if (ele17_CaloIdL_CaloIsoVL_version_branch != 0) {
				ele17_CaloIdL_CaloIsoVL_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele17_CaloIdL_CaloIsoVL_version_branch does not exist!\n");
				exit(1);
			}
			ele17_CaloIdL_CaloIsoVL_version_isLoaded = true;
		}
		return ele17_CaloIdL_CaloIsoVL_version_;
	}
	int &ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version()
	{
		if (not ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_isLoaded) {
			if (ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_branch != 0) {
				ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_branch does not exist!\n");
				exit(1);
			}
			ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_isLoaded = true;
		}
		return ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_;
	}
	int &ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version()
	{
		if (not ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_isLoaded) {
			if (ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_branch != 0) {
				ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_branch does not exist!\n");
				exit(1);
			}
			ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_isLoaded = true;
		}
		return ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version_;
	}
	int &photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version()
	{
		if (not photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_isLoaded) {
			if (photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_branch != 0) {
				photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_branch does not exist!\n");
				exit(1);
			}
			photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_isLoaded = true;
		}
		return photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_;
	}
	int &ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_version()
	{
		if (not ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_version_isLoaded) {
			if (ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_version_branch != 0) {
				ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_version_branch does not exist!\n");
				exit(1);
			}
			ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_version_isLoaded = true;
		}
		return ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_version_;
	}
	int &ele27_WP80_version()
	{
		if (not ele27_WP80_version_isLoaded) {
			if (ele27_WP80_version_branch != 0) {
				ele27_WP80_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ele27_WP80_version_branch does not exist!\n");
				exit(1);
			}
			ele27_WP80_version_isLoaded = true;
		}
		return ele27_WP80_version_;
	}
	float &dr_ele8_vstar()
	{
		if (not dr_ele8_vstar_isLoaded) {
			if (dr_ele8_vstar_branch != 0) {
				dr_ele8_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_ele8_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_ele8_vstar_isLoaded = true;
		}
		return dr_ele8_vstar_;
	}
	float &dr_ele8_CaloIdL_TrkIdVL_vstar()
	{
		if (not dr_ele8_CaloIdL_TrkIdVL_vstar_isLoaded) {
			if (dr_ele8_CaloIdL_TrkIdVL_vstar_branch != 0) {
				dr_ele8_CaloIdL_TrkIdVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_ele8_CaloIdL_TrkIdVL_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_ele8_CaloIdL_TrkIdVL_vstar_isLoaded = true;
		}
		return dr_ele8_CaloIdL_TrkIdVL_vstar_;
	}
	float &dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar()
	{
		if (not dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_isLoaded) {
			if (dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch != 0) {
				dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_isLoaded = true;
		}
		return dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_;
	}
	float &dr_ele8_CaloIdL_CaloIsoVL_vstar()
	{
		if (not dr_ele8_CaloIdL_CaloIsoVL_vstar_isLoaded) {
			if (dr_ele8_CaloIdL_CaloIsoVL_vstar_branch != 0) {
				dr_ele8_CaloIdL_CaloIsoVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_ele8_CaloIdL_CaloIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_ele8_CaloIdL_CaloIsoVL_vstar_isLoaded = true;
		}
		return dr_ele8_CaloIdL_CaloIsoVL_vstar_;
	}
	float &dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar()
	{
		if (not dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_isLoaded) {
			if (dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch != 0) {
				dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_isLoaded = true;
		}
		return dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_;
	}
	float &dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()
	{
		if (not dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded) {
			if (dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch != 0) {
				dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded = true;
		}
		return dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_;
	}
	float &dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()
	{
		if (not dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded) {
			if (dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch != 0) {
				dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded = true;
		}
		return dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_;
	}
	float &dr_ele8_CaloIdT_TrkIdVL_vstar()
	{
		if (not dr_ele8_CaloIdT_TrkIdVL_vstar_isLoaded) {
			if (dr_ele8_CaloIdT_TrkIdVL_vstar_branch != 0) {
				dr_ele8_CaloIdT_TrkIdVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_ele8_CaloIdT_TrkIdVL_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_ele8_CaloIdT_TrkIdVL_vstar_isLoaded = true;
		}
		return dr_ele8_CaloIdT_TrkIdVL_vstar_;
	}
	float &dr_ele8_CaloIdT_TrkIdVL_Jet30_vstar()
	{
		if (not dr_ele8_CaloIdT_TrkIdVL_Jet30_vstar_isLoaded) {
			if (dr_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch != 0) {
				dr_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_ele8_CaloIdT_TrkIdVL_Jet30_vstar_isLoaded = true;
		}
		return dr_ele8_CaloIdT_TrkIdVL_Jet30_vstar_;
	}
	float &dr_ele17_CaloIdL_CaloIsoVL_vstar()
	{
		if (not dr_ele17_CaloIdL_CaloIsoVL_vstar_isLoaded) {
			if (dr_ele17_CaloIdL_CaloIsoVL_vstar_branch != 0) {
				dr_ele17_CaloIdL_CaloIsoVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_ele17_CaloIdL_CaloIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_ele17_CaloIdL_CaloIsoVL_vstar_isLoaded = true;
		}
		return dr_ele17_CaloIdL_CaloIsoVL_vstar_;
	}
	float &dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()
	{
		if (not dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded) {
			if (dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch != 0) {
				dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded = true;
		}
		return dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_;
	}
	float &dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()
	{
		if (not dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded) {
			if (dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch != 0) {
				dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded = true;
		}
		return dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_;
	}
	float &dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar()
	{
		if (not dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_isLoaded) {
			if (dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch != 0) {
				dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_isLoaded = true;
		}
		return dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_;
	}
	float &dr_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar()
	{
		if (not dr_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_isLoaded) {
			if (dr_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch != 0) {
				dr_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_isLoaded = true;
		}
		return dr_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_;
	}
	float &dr_ele27_WP80_vstar()
	{
		if (not dr_ele27_WP80_vstar_isLoaded) {
			if (dr_ele27_WP80_vstar_branch != 0) {
				dr_ele27_WP80_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_ele27_WP80_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_ele27_WP80_vstar_isLoaded = true;
		}
		return dr_ele27_WP80_vstar_;
	}
	int &hltps_ele8_vstar()
	{
		if (not hltps_ele8_vstar_isLoaded) {
			if (hltps_ele8_vstar_branch != 0) {
				hltps_ele8_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_ele8_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_ele8_vstar_isLoaded = true;
		}
		return hltps_ele8_vstar_;
	}
	int &hltps_ele8_CaloIdL_TrkIdVL_vstar()
	{
		if (not hltps_ele8_CaloIdL_TrkIdVL_vstar_isLoaded) {
			if (hltps_ele8_CaloIdL_TrkIdVL_vstar_branch != 0) {
				hltps_ele8_CaloIdL_TrkIdVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_ele8_CaloIdL_TrkIdVL_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_ele8_CaloIdL_TrkIdVL_vstar_isLoaded = true;
		}
		return hltps_ele8_CaloIdL_TrkIdVL_vstar_;
	}
	int &hltps_ele8_CaloIdL_CaloIsoVL_Jet40_vstar()
	{
		if (not hltps_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_isLoaded) {
			if (hltps_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch != 0) {
				hltps_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_isLoaded = true;
		}
		return hltps_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_;
	}
	int &hltps_ele8_CaloIdL_CaloIsoVL_vstar()
	{
		if (not hltps_ele8_CaloIdL_CaloIsoVL_vstar_isLoaded) {
			if (hltps_ele8_CaloIdL_CaloIsoVL_vstar_branch != 0) {
				hltps_ele8_CaloIdL_CaloIsoVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_ele8_CaloIdL_CaloIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_ele8_CaloIdL_CaloIsoVL_vstar_isLoaded = true;
		}
		return hltps_ele8_CaloIdL_CaloIsoVL_vstar_;
	}
	int &hltps_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar()
	{
		if (not hltps_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_isLoaded) {
			if (hltps_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch != 0) {
				hltps_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_isLoaded = true;
		}
		return hltps_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_;
	}
	int &hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()
	{
		if (not hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded) {
			if (hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch != 0) {
				hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded = true;
		}
		return hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_;
	}
	int &hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()
	{
		if (not hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded) {
			if (hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch != 0) {
				hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded = true;
		}
		return hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_;
	}
	int &hltps_ele8_CaloIdT_TrkIdVL_vstar()
	{
		if (not hltps_ele8_CaloIdT_TrkIdVL_vstar_isLoaded) {
			if (hltps_ele8_CaloIdT_TrkIdVL_vstar_branch != 0) {
				hltps_ele8_CaloIdT_TrkIdVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_ele8_CaloIdT_TrkIdVL_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_ele8_CaloIdT_TrkIdVL_vstar_isLoaded = true;
		}
		return hltps_ele8_CaloIdT_TrkIdVL_vstar_;
	}
	int &hltps_ele8_CaloIdT_TrkIdVL_Jet30_vstar()
	{
		if (not hltps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_isLoaded) {
			if (hltps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch != 0) {
				hltps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_isLoaded = true;
		}
		return hltps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_;
	}
	int &hltps_ele17_CaloIdL_CaloIsoVL_vstar()
	{
		if (not hltps_ele17_CaloIdL_CaloIsoVL_vstar_isLoaded) {
			if (hltps_ele17_CaloIdL_CaloIsoVL_vstar_branch != 0) {
				hltps_ele17_CaloIdL_CaloIsoVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_ele17_CaloIdL_CaloIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_ele17_CaloIdL_CaloIsoVL_vstar_isLoaded = true;
		}
		return hltps_ele17_CaloIdL_CaloIsoVL_vstar_;
	}
	int &hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()
	{
		if (not hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded) {
			if (hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch != 0) {
				hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded = true;
		}
		return hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_;
	}
	int &hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()
	{
		if (not hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded) {
			if (hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch != 0) {
				hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded = true;
		}
		return hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_;
	}
	int &hltps_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar()
	{
		if (not hltps_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_isLoaded) {
			if (hltps_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch != 0) {
				hltps_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_isLoaded = true;
		}
		return hltps_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_;
	}
	int &hltps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar()
	{
		if (not hltps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_isLoaded) {
			if (hltps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch != 0) {
				hltps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_isLoaded = true;
		}
		return hltps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_;
	}
	int &hltps_ele27_WP80_vstar()
	{
		if (not hltps_ele27_WP80_vstar_isLoaded) {
			if (hltps_ele27_WP80_vstar_branch != 0) {
				hltps_ele27_WP80_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_ele27_WP80_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_ele27_WP80_vstar_isLoaded = true;
		}
		return hltps_ele27_WP80_vstar_;
	}
	int &l1ps_ele8_CaloIdL_CaloIsoVL_vstar()
	{
		if (not l1ps_ele8_CaloIdL_CaloIsoVL_vstar_isLoaded) {
			if (l1ps_ele8_CaloIdL_CaloIsoVL_vstar_branch != 0) {
				l1ps_ele8_CaloIdL_CaloIsoVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch l1ps_ele8_CaloIdL_CaloIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			l1ps_ele8_CaloIdL_CaloIsoVL_vstar_isLoaded = true;
		}
		return l1ps_ele8_CaloIdL_CaloIsoVL_vstar_;
	}
	int &l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()
	{
		if (not l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded) {
			if (l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch != 0) {
				l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded = true;
		}
		return l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_;
	}
	int &l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()
	{
		if (not l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded) {
			if (l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch != 0) {
				l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch does not exist!\n");
				exit(1);
			}
			l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded = true;
		}
		return l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_;
	}
	int &l1ps_ele8_CaloIdT_TrkIdVL_vstar()
	{
		if (not l1ps_ele8_CaloIdT_TrkIdVL_vstar_isLoaded) {
			if (l1ps_ele8_CaloIdT_TrkIdVL_vstar_branch != 0) {
				l1ps_ele8_CaloIdT_TrkIdVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch l1ps_ele8_CaloIdT_TrkIdVL_vstar_branch does not exist!\n");
				exit(1);
			}
			l1ps_ele8_CaloIdT_TrkIdVL_vstar_isLoaded = true;
		}
		return l1ps_ele8_CaloIdT_TrkIdVL_vstar_;
	}
	int &l1ps_ele8_CaloIdT_TrkIdVL_Jet30_vstar()
	{
		if (not l1ps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_isLoaded) {
			if (l1ps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch != 0) {
				l1ps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch l1ps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_branch does not exist!\n");
				exit(1);
			}
			l1ps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_isLoaded = true;
		}
		return l1ps_ele8_CaloIdT_TrkIdVL_Jet30_vstar_;
	}
	int &l1ps_ele17_CaloIdL_CaloIsoVL_vstar()
	{
		if (not l1ps_ele17_CaloIdL_CaloIsoVL_vstar_isLoaded) {
			if (l1ps_ele17_CaloIdL_CaloIsoVL_vstar_branch != 0) {
				l1ps_ele17_CaloIdL_CaloIsoVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch l1ps_ele17_CaloIdL_CaloIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			l1ps_ele17_CaloIdL_CaloIsoVL_vstar_isLoaded = true;
		}
		return l1ps_ele17_CaloIdL_CaloIsoVL_vstar_;
	}
	int &l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar()
	{
		if (not l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded) {
			if (l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch != 0) {
				l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded = true;
		}
		return l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_;
	}
	int &l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()
	{
		if (not l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded) {
			if (l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch != 0) {
				l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_branch does not exist!\n");
				exit(1);
			}
			l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_isLoaded = true;
		}
		return l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar_;
	}
	int &l1ps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar()
	{
		if (not l1ps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_isLoaded) {
			if (l1ps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch != 0) {
				l1ps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch l1ps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_branch does not exist!\n");
				exit(1);
			}
			l1ps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_isLoaded = true;
		}
		return l1ps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar_;
	}
	int &l1ps_ele27_WP80_vstar()
	{
		if (not l1ps_ele27_WP80_vstar_isLoaded) {
			if (l1ps_ele27_WP80_vstar_branch != 0) {
				l1ps_ele27_WP80_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch l1ps_ele27_WP80_vstar_branch does not exist!\n");
				exit(1);
			}
			l1ps_ele27_WP80_vstar_isLoaded = true;
		}
		return l1ps_ele27_WP80_vstar_;
	}
	int &mu3_vstar()
	{
		if (not mu3_vstar_isLoaded) {
			if (mu3_vstar_branch != 0) {
				mu3_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu3_vstar_branch does not exist!\n");
				exit(1);
			}
			mu3_vstar_isLoaded = true;
		}
		return mu3_vstar_;
	}
	int &mu5_vstar()
	{
		if (not mu5_vstar_isLoaded) {
			if (mu5_vstar_branch != 0) {
				mu5_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu5_vstar_branch does not exist!\n");
				exit(1);
			}
			mu5_vstar_isLoaded = true;
		}
		return mu5_vstar_;
	}
	int &mu8_vstar()
	{
		if (not mu8_vstar_isLoaded) {
			if (mu8_vstar_branch != 0) {
				mu8_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu8_vstar_branch does not exist!\n");
				exit(1);
			}
			mu8_vstar_isLoaded = true;
		}
		return mu8_vstar_;
	}
	int &mu12_vstar()
	{
		if (not mu12_vstar_isLoaded) {
			if (mu12_vstar_branch != 0) {
				mu12_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu12_vstar_branch does not exist!\n");
				exit(1);
			}
			mu12_vstar_isLoaded = true;
		}
		return mu12_vstar_;
	}
	int &mu15_vstar()
	{
		if (not mu15_vstar_isLoaded) {
			if (mu15_vstar_branch != 0) {
				mu15_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu15_vstar_branch does not exist!\n");
				exit(1);
			}
			mu15_vstar_isLoaded = true;
		}
		return mu15_vstar_;
	}
	int &mu17_vstar()
	{
		if (not mu17_vstar_isLoaded) {
			if (mu17_vstar_branch != 0) {
				mu17_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu17_vstar_branch does not exist!\n");
				exit(1);
			}
			mu17_vstar_isLoaded = true;
		}
		return mu17_vstar_;
	}
	int &mu20_vstar()
	{
		if (not mu20_vstar_isLoaded) {
			if (mu20_vstar_branch != 0) {
				mu20_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu20_vstar_branch does not exist!\n");
				exit(1);
			}
			mu20_vstar_isLoaded = true;
		}
		return mu20_vstar_;
	}
	int &mu24_vstar()
	{
		if (not mu24_vstar_isLoaded) {
			if (mu24_vstar_branch != 0) {
				mu24_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu24_vstar_branch does not exist!\n");
				exit(1);
			}
			mu24_vstar_isLoaded = true;
		}
		return mu24_vstar_;
	}
	int &mu30_vstar()
	{
		if (not mu30_vstar_isLoaded) {
			if (mu30_vstar_branch != 0) {
				mu30_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu30_vstar_branch does not exist!\n");
				exit(1);
			}
			mu30_vstar_isLoaded = true;
		}
		return mu30_vstar_;
	}
	int &mu15_eta2p1_vstar()
	{
		if (not mu15_eta2p1_vstar_isLoaded) {
			if (mu15_eta2p1_vstar_branch != 0) {
				mu15_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu15_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			mu15_eta2p1_vstar_isLoaded = true;
		}
		return mu15_eta2p1_vstar_;
	}
	int &mu24_eta2p1_vstar()
	{
		if (not mu24_eta2p1_vstar_isLoaded) {
			if (mu24_eta2p1_vstar_branch != 0) {
				mu24_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu24_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			mu24_eta2p1_vstar_isLoaded = true;
		}
		return mu24_eta2p1_vstar_;
	}
	int &mu30_eta2p1_vstar()
	{
		if (not mu30_eta2p1_vstar_isLoaded) {
			if (mu30_eta2p1_vstar_branch != 0) {
				mu30_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu30_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			mu30_eta2p1_vstar_isLoaded = true;
		}
		return mu30_eta2p1_vstar_;
	}
	int &mu8_Jet40_vstar()
	{
		if (not mu8_Jet40_vstar_isLoaded) {
			if (mu8_Jet40_vstar_branch != 0) {
				mu8_Jet40_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu8_Jet40_vstar_branch does not exist!\n");
				exit(1);
			}
			mu8_Jet40_vstar_isLoaded = true;
		}
		return mu8_Jet40_vstar_;
	}
	int &isoMu20_eta2p1_vstar()
	{
		if (not isoMu20_eta2p1_vstar_isLoaded) {
			if (isoMu20_eta2p1_vstar_branch != 0) {
				isoMu20_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch isoMu20_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			isoMu20_eta2p1_vstar_isLoaded = true;
		}
		return isoMu20_eta2p1_vstar_;
	}
	int &isoMu24_eta2p1_vstar()
	{
		if (not isoMu24_eta2p1_vstar_isLoaded) {
			if (isoMu24_eta2p1_vstar_branch != 0) {
				isoMu24_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch isoMu24_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			isoMu24_eta2p1_vstar_isLoaded = true;
		}
		return isoMu24_eta2p1_vstar_;
	}
	int &isoMu30_eta2p1_vstar()
	{
		if (not isoMu30_eta2p1_vstar_isLoaded) {
			if (isoMu30_eta2p1_vstar_branch != 0) {
				isoMu30_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch isoMu30_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			isoMu30_eta2p1_vstar_isLoaded = true;
		}
		return isoMu30_eta2p1_vstar_;
	}
	int &relIso1p0Mu17_vstar()
	{
		if (not relIso1p0Mu17_vstar_isLoaded) {
			if (relIso1p0Mu17_vstar_branch != 0) {
				relIso1p0Mu17_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch relIso1p0Mu17_vstar_branch does not exist!\n");
				exit(1);
			}
			relIso1p0Mu17_vstar_isLoaded = true;
		}
		return relIso1p0Mu17_vstar_;
	}
	int &relIso1p0Mu5_vstar()
	{
		if (not relIso1p0Mu5_vstar_isLoaded) {
			if (relIso1p0Mu5_vstar_branch != 0) {
				relIso1p0Mu5_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch relIso1p0Mu5_vstar_branch does not exist!\n");
				exit(1);
			}
			relIso1p0Mu5_vstar_isLoaded = true;
		}
		return relIso1p0Mu5_vstar_;
	}
	int &mu3_version()
	{
		if (not mu3_version_isLoaded) {
			if (mu3_version_branch != 0) {
				mu3_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu3_version_branch does not exist!\n");
				exit(1);
			}
			mu3_version_isLoaded = true;
		}
		return mu3_version_;
	}
	int &mu5_version()
	{
		if (not mu5_version_isLoaded) {
			if (mu5_version_branch != 0) {
				mu5_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu5_version_branch does not exist!\n");
				exit(1);
			}
			mu5_version_isLoaded = true;
		}
		return mu5_version_;
	}
	int &mu8_version()
	{
		if (not mu8_version_isLoaded) {
			if (mu8_version_branch != 0) {
				mu8_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu8_version_branch does not exist!\n");
				exit(1);
			}
			mu8_version_isLoaded = true;
		}
		return mu8_version_;
	}
	int &mu12_version()
	{
		if (not mu12_version_isLoaded) {
			if (mu12_version_branch != 0) {
				mu12_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu12_version_branch does not exist!\n");
				exit(1);
			}
			mu12_version_isLoaded = true;
		}
		return mu12_version_;
	}
	int &mu15_version()
	{
		if (not mu15_version_isLoaded) {
			if (mu15_version_branch != 0) {
				mu15_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu15_version_branch does not exist!\n");
				exit(1);
			}
			mu15_version_isLoaded = true;
		}
		return mu15_version_;
	}
	int &mu17_version()
	{
		if (not mu17_version_isLoaded) {
			if (mu17_version_branch != 0) {
				mu17_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu17_version_branch does not exist!\n");
				exit(1);
			}
			mu17_version_isLoaded = true;
		}
		return mu17_version_;
	}
	int &mu20_version()
	{
		if (not mu20_version_isLoaded) {
			if (mu20_version_branch != 0) {
				mu20_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu20_version_branch does not exist!\n");
				exit(1);
			}
			mu20_version_isLoaded = true;
		}
		return mu20_version_;
	}
	int &mu24_version()
	{
		if (not mu24_version_isLoaded) {
			if (mu24_version_branch != 0) {
				mu24_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu24_version_branch does not exist!\n");
				exit(1);
			}
			mu24_version_isLoaded = true;
		}
		return mu24_version_;
	}
	int &mu30_version()
	{
		if (not mu30_version_isLoaded) {
			if (mu30_version_branch != 0) {
				mu30_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu30_version_branch does not exist!\n");
				exit(1);
			}
			mu30_version_isLoaded = true;
		}
		return mu30_version_;
	}
	int &mu15_eta2p1_version()
	{
		if (not mu15_eta2p1_version_isLoaded) {
			if (mu15_eta2p1_version_branch != 0) {
				mu15_eta2p1_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu15_eta2p1_version_branch does not exist!\n");
				exit(1);
			}
			mu15_eta2p1_version_isLoaded = true;
		}
		return mu15_eta2p1_version_;
	}
	int &mu24_eta2p1_version()
	{
		if (not mu24_eta2p1_version_isLoaded) {
			if (mu24_eta2p1_version_branch != 0) {
				mu24_eta2p1_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu24_eta2p1_version_branch does not exist!\n");
				exit(1);
			}
			mu24_eta2p1_version_isLoaded = true;
		}
		return mu24_eta2p1_version_;
	}
	int &mu30_eta2p1_version()
	{
		if (not mu30_eta2p1_version_isLoaded) {
			if (mu30_eta2p1_version_branch != 0) {
				mu30_eta2p1_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu30_eta2p1_version_branch does not exist!\n");
				exit(1);
			}
			mu30_eta2p1_version_isLoaded = true;
		}
		return mu30_eta2p1_version_;
	}
	int &mu8_Jet40_version()
	{
		if (not mu8_Jet40_version_isLoaded) {
			if (mu8_Jet40_version_branch != 0) {
				mu8_Jet40_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch mu8_Jet40_version_branch does not exist!\n");
				exit(1);
			}
			mu8_Jet40_version_isLoaded = true;
		}
		return mu8_Jet40_version_;
	}
	int &isoMu20_eta2p1_version()
	{
		if (not isoMu20_eta2p1_version_isLoaded) {
			if (isoMu20_eta2p1_version_branch != 0) {
				isoMu20_eta2p1_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch isoMu20_eta2p1_version_branch does not exist!\n");
				exit(1);
			}
			isoMu20_eta2p1_version_isLoaded = true;
		}
		return isoMu20_eta2p1_version_;
	}
	int &isoMu24_eta2p1_version()
	{
		if (not isoMu24_eta2p1_version_isLoaded) {
			if (isoMu24_eta2p1_version_branch != 0) {
				isoMu24_eta2p1_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch isoMu24_eta2p1_version_branch does not exist!\n");
				exit(1);
			}
			isoMu24_eta2p1_version_isLoaded = true;
		}
		return isoMu24_eta2p1_version_;
	}
	int &isoMu30_eta2p1_version()
	{
		if (not isoMu30_eta2p1_version_isLoaded) {
			if (isoMu30_eta2p1_version_branch != 0) {
				isoMu30_eta2p1_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch isoMu30_eta2p1_version_branch does not exist!\n");
				exit(1);
			}
			isoMu30_eta2p1_version_isLoaded = true;
		}
		return isoMu30_eta2p1_version_;
	}
	int &relIso1p0Mu17_version()
	{
		if (not relIso1p0Mu17_version_isLoaded) {
			if (relIso1p0Mu17_version_branch != 0) {
				relIso1p0Mu17_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch relIso1p0Mu17_version_branch does not exist!\n");
				exit(1);
			}
			relIso1p0Mu17_version_isLoaded = true;
		}
		return relIso1p0Mu17_version_;
	}
	int &relIso1p0Mu5_version()
	{
		if (not relIso1p0Mu5_version_isLoaded) {
			if (relIso1p0Mu5_version_branch != 0) {
				relIso1p0Mu5_version_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch relIso1p0Mu5_version_branch does not exist!\n");
				exit(1);
			}
			relIso1p0Mu5_version_isLoaded = true;
		}
		return relIso1p0Mu5_version_;
	}
	float &dr_mu3_vstar()
	{
		if (not dr_mu3_vstar_isLoaded) {
			if (dr_mu3_vstar_branch != 0) {
				dr_mu3_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_mu3_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_mu3_vstar_isLoaded = true;
		}
		return dr_mu3_vstar_;
	}
	float &dr_mu5_vstar()
	{
		if (not dr_mu5_vstar_isLoaded) {
			if (dr_mu5_vstar_branch != 0) {
				dr_mu5_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_mu5_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_mu5_vstar_isLoaded = true;
		}
		return dr_mu5_vstar_;
	}
	float &dr_mu8_vstar()
	{
		if (not dr_mu8_vstar_isLoaded) {
			if (dr_mu8_vstar_branch != 0) {
				dr_mu8_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_mu8_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_mu8_vstar_isLoaded = true;
		}
		return dr_mu8_vstar_;
	}
	float &dr_mu12_vstar()
	{
		if (not dr_mu12_vstar_isLoaded) {
			if (dr_mu12_vstar_branch != 0) {
				dr_mu12_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_mu12_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_mu12_vstar_isLoaded = true;
		}
		return dr_mu12_vstar_;
	}
	float &dr_mu15_vstar()
	{
		if (not dr_mu15_vstar_isLoaded) {
			if (dr_mu15_vstar_branch != 0) {
				dr_mu15_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_mu15_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_mu15_vstar_isLoaded = true;
		}
		return dr_mu15_vstar_;
	}
	float &dr_mu17_vstar()
	{
		if (not dr_mu17_vstar_isLoaded) {
			if (dr_mu17_vstar_branch != 0) {
				dr_mu17_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_mu17_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_mu17_vstar_isLoaded = true;
		}
		return dr_mu17_vstar_;
	}
	float &dr_mu20_vstar()
	{
		if (not dr_mu20_vstar_isLoaded) {
			if (dr_mu20_vstar_branch != 0) {
				dr_mu20_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_mu20_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_mu20_vstar_isLoaded = true;
		}
		return dr_mu20_vstar_;
	}
	float &dr_mu24_vstar()
	{
		if (not dr_mu24_vstar_isLoaded) {
			if (dr_mu24_vstar_branch != 0) {
				dr_mu24_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_mu24_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_mu24_vstar_isLoaded = true;
		}
		return dr_mu24_vstar_;
	}
	float &dr_mu30_vstar()
	{
		if (not dr_mu30_vstar_isLoaded) {
			if (dr_mu30_vstar_branch != 0) {
				dr_mu30_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_mu30_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_mu30_vstar_isLoaded = true;
		}
		return dr_mu30_vstar_;
	}
	float &dr_mu15_eta2p1_vstar()
	{
		if (not dr_mu15_eta2p1_vstar_isLoaded) {
			if (dr_mu15_eta2p1_vstar_branch != 0) {
				dr_mu15_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_mu15_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_mu15_eta2p1_vstar_isLoaded = true;
		}
		return dr_mu15_eta2p1_vstar_;
	}
	float &dr_mu24_eta2p1_vstar()
	{
		if (not dr_mu24_eta2p1_vstar_isLoaded) {
			if (dr_mu24_eta2p1_vstar_branch != 0) {
				dr_mu24_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_mu24_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_mu24_eta2p1_vstar_isLoaded = true;
		}
		return dr_mu24_eta2p1_vstar_;
	}
	float &dr_mu30_eta2p1_vstar()
	{
		if (not dr_mu30_eta2p1_vstar_isLoaded) {
			if (dr_mu30_eta2p1_vstar_branch != 0) {
				dr_mu30_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_mu30_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_mu30_eta2p1_vstar_isLoaded = true;
		}
		return dr_mu30_eta2p1_vstar_;
	}
	float &dr_mu8_Jet40_vstar()
	{
		if (not dr_mu8_Jet40_vstar_isLoaded) {
			if (dr_mu8_Jet40_vstar_branch != 0) {
				dr_mu8_Jet40_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_mu8_Jet40_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_mu8_Jet40_vstar_isLoaded = true;
		}
		return dr_mu8_Jet40_vstar_;
	}
	float &dr_isoMu20_eta2p1_vstar()
	{
		if (not dr_isoMu20_eta2p1_vstar_isLoaded) {
			if (dr_isoMu20_eta2p1_vstar_branch != 0) {
				dr_isoMu20_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_isoMu20_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_isoMu20_eta2p1_vstar_isLoaded = true;
		}
		return dr_isoMu20_eta2p1_vstar_;
	}
	float &dr_isoMu24_eta2p1_vstar()
	{
		if (not dr_isoMu24_eta2p1_vstar_isLoaded) {
			if (dr_isoMu24_eta2p1_vstar_branch != 0) {
				dr_isoMu24_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_isoMu24_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_isoMu24_eta2p1_vstar_isLoaded = true;
		}
		return dr_isoMu24_eta2p1_vstar_;
	}
	float &dr_isoMu30_eta2p1_vstar()
	{
		if (not dr_isoMu30_eta2p1_vstar_isLoaded) {
			if (dr_isoMu30_eta2p1_vstar_branch != 0) {
				dr_isoMu30_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_isoMu30_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_isoMu30_eta2p1_vstar_isLoaded = true;
		}
		return dr_isoMu30_eta2p1_vstar_;
	}
	float &dr_relIso1p0Mu17_vstar()
	{
		if (not dr_relIso1p0Mu17_vstar_isLoaded) {
			if (dr_relIso1p0Mu17_vstar_branch != 0) {
				dr_relIso1p0Mu17_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_relIso1p0Mu17_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_relIso1p0Mu17_vstar_isLoaded = true;
		}
		return dr_relIso1p0Mu17_vstar_;
	}
	float &dr_relIso1p0Mu5_vstar()
	{
		if (not dr_relIso1p0Mu5_vstar_isLoaded) {
			if (dr_relIso1p0Mu5_vstar_branch != 0) {
				dr_relIso1p0Mu5_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dr_relIso1p0Mu5_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_relIso1p0Mu5_vstar_isLoaded = true;
		}
		return dr_relIso1p0Mu5_vstar_;
	}
	int &hltps_mu3_vstar()
	{
		if (not hltps_mu3_vstar_isLoaded) {
			if (hltps_mu3_vstar_branch != 0) {
				hltps_mu3_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_mu3_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_mu3_vstar_isLoaded = true;
		}
		return hltps_mu3_vstar_;
	}
	int &hltps_mu5_vstar()
	{
		if (not hltps_mu5_vstar_isLoaded) {
			if (hltps_mu5_vstar_branch != 0) {
				hltps_mu5_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_mu5_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_mu5_vstar_isLoaded = true;
		}
		return hltps_mu5_vstar_;
	}
	int &hltps_mu8_vstar()
	{
		if (not hltps_mu8_vstar_isLoaded) {
			if (hltps_mu8_vstar_branch != 0) {
				hltps_mu8_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_mu8_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_mu8_vstar_isLoaded = true;
		}
		return hltps_mu8_vstar_;
	}
	int &hltps_mu12_vstar()
	{
		if (not hltps_mu12_vstar_isLoaded) {
			if (hltps_mu12_vstar_branch != 0) {
				hltps_mu12_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_mu12_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_mu12_vstar_isLoaded = true;
		}
		return hltps_mu12_vstar_;
	}
	int &hltps_mu15_vstar()
	{
		if (not hltps_mu15_vstar_isLoaded) {
			if (hltps_mu15_vstar_branch != 0) {
				hltps_mu15_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_mu15_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_mu15_vstar_isLoaded = true;
		}
		return hltps_mu15_vstar_;
	}
	int &hltps_mu17_vstar()
	{
		if (not hltps_mu17_vstar_isLoaded) {
			if (hltps_mu17_vstar_branch != 0) {
				hltps_mu17_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_mu17_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_mu17_vstar_isLoaded = true;
		}
		return hltps_mu17_vstar_;
	}
	int &hltps_mu20_vstar()
	{
		if (not hltps_mu20_vstar_isLoaded) {
			if (hltps_mu20_vstar_branch != 0) {
				hltps_mu20_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_mu20_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_mu20_vstar_isLoaded = true;
		}
		return hltps_mu20_vstar_;
	}
	int &hltps_mu24_vstar()
	{
		if (not hltps_mu24_vstar_isLoaded) {
			if (hltps_mu24_vstar_branch != 0) {
				hltps_mu24_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_mu24_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_mu24_vstar_isLoaded = true;
		}
		return hltps_mu24_vstar_;
	}
	int &hltps_mu30_vstar()
	{
		if (not hltps_mu30_vstar_isLoaded) {
			if (hltps_mu30_vstar_branch != 0) {
				hltps_mu30_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_mu30_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_mu30_vstar_isLoaded = true;
		}
		return hltps_mu30_vstar_;
	}
	int &hltps_mu15_eta2p1_vstar()
	{
		if (not hltps_mu15_eta2p1_vstar_isLoaded) {
			if (hltps_mu15_eta2p1_vstar_branch != 0) {
				hltps_mu15_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_mu15_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_mu15_eta2p1_vstar_isLoaded = true;
		}
		return hltps_mu15_eta2p1_vstar_;
	}
	int &hltps_mu24_eta2p1_vstar()
	{
		if (not hltps_mu24_eta2p1_vstar_isLoaded) {
			if (hltps_mu24_eta2p1_vstar_branch != 0) {
				hltps_mu24_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_mu24_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_mu24_eta2p1_vstar_isLoaded = true;
		}
		return hltps_mu24_eta2p1_vstar_;
	}
	int &hltps_mu30_eta2p1_vstar()
	{
		if (not hltps_mu30_eta2p1_vstar_isLoaded) {
			if (hltps_mu30_eta2p1_vstar_branch != 0) {
				hltps_mu30_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_mu30_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_mu30_eta2p1_vstar_isLoaded = true;
		}
		return hltps_mu30_eta2p1_vstar_;
	}
	int &hltps_mu8_Jet40_vstar()
	{
		if (not hltps_mu8_Jet40_vstar_isLoaded) {
			if (hltps_mu8_Jet40_vstar_branch != 0) {
				hltps_mu8_Jet40_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_mu8_Jet40_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_mu8_Jet40_vstar_isLoaded = true;
		}
		return hltps_mu8_Jet40_vstar_;
	}
	int &hltps_isoMu20_eta2p1_vstar()
	{
		if (not hltps_isoMu20_eta2p1_vstar_isLoaded) {
			if (hltps_isoMu20_eta2p1_vstar_branch != 0) {
				hltps_isoMu20_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_isoMu20_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_isoMu20_eta2p1_vstar_isLoaded = true;
		}
		return hltps_isoMu20_eta2p1_vstar_;
	}
	int &hltps_isoMu24_eta2p1_vstar()
	{
		if (not hltps_isoMu24_eta2p1_vstar_isLoaded) {
			if (hltps_isoMu24_eta2p1_vstar_branch != 0) {
				hltps_isoMu24_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_isoMu24_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_isoMu24_eta2p1_vstar_isLoaded = true;
		}
		return hltps_isoMu24_eta2p1_vstar_;
	}
	int &hltps_isoMu30_eta2p1_vstar()
	{
		if (not hltps_isoMu30_eta2p1_vstar_isLoaded) {
			if (hltps_isoMu30_eta2p1_vstar_branch != 0) {
				hltps_isoMu30_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_isoMu30_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_isoMu30_eta2p1_vstar_isLoaded = true;
		}
		return hltps_isoMu30_eta2p1_vstar_;
	}
	int &hltps_relIso1p0Mu17_vstar()
	{
		if (not hltps_relIso1p0Mu17_vstar_isLoaded) {
			if (hltps_relIso1p0Mu17_vstar_branch != 0) {
				hltps_relIso1p0Mu17_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_relIso1p0Mu17_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_relIso1p0Mu17_vstar_isLoaded = true;
		}
		return hltps_relIso1p0Mu17_vstar_;
	}
	int &hltps_relIso1p0Mu5_vstar()
	{
		if (not hltps_relIso1p0Mu5_vstar_isLoaded) {
			if (hltps_relIso1p0Mu5_vstar_branch != 0) {
				hltps_relIso1p0Mu5_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch hltps_relIso1p0Mu5_vstar_branch does not exist!\n");
				exit(1);
			}
			hltps_relIso1p0Mu5_vstar_isLoaded = true;
		}
		return hltps_relIso1p0Mu5_vstar_;
	}
	int &l1ps_mu5_vstar()
	{
		if (not l1ps_mu5_vstar_isLoaded) {
			if (l1ps_mu5_vstar_branch != 0) {
				l1ps_mu5_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch l1ps_mu5_vstar_branch does not exist!\n");
				exit(1);
			}
			l1ps_mu5_vstar_isLoaded = true;
		}
		return l1ps_mu5_vstar_;
	}
	int &l1ps_mu8_vstar()
	{
		if (not l1ps_mu8_vstar_isLoaded) {
			if (l1ps_mu8_vstar_branch != 0) {
				l1ps_mu8_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch l1ps_mu8_vstar_branch does not exist!\n");
				exit(1);
			}
			l1ps_mu8_vstar_isLoaded = true;
		}
		return l1ps_mu8_vstar_;
	}
	int &l1ps_mu12_vstar()
	{
		if (not l1ps_mu12_vstar_isLoaded) {
			if (l1ps_mu12_vstar_branch != 0) {
				l1ps_mu12_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch l1ps_mu12_vstar_branch does not exist!\n");
				exit(1);
			}
			l1ps_mu12_vstar_isLoaded = true;
		}
		return l1ps_mu12_vstar_;
	}
	int &l1ps_mu17_vstar()
	{
		if (not l1ps_mu17_vstar_isLoaded) {
			if (l1ps_mu17_vstar_branch != 0) {
				l1ps_mu17_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch l1ps_mu17_vstar_branch does not exist!\n");
				exit(1);
			}
			l1ps_mu17_vstar_isLoaded = true;
		}
		return l1ps_mu17_vstar_;
	}
	int &l1ps_mu15_eta2p1_vstar()
	{
		if (not l1ps_mu15_eta2p1_vstar_isLoaded) {
			if (l1ps_mu15_eta2p1_vstar_branch != 0) {
				l1ps_mu15_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch l1ps_mu15_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			l1ps_mu15_eta2p1_vstar_isLoaded = true;
		}
		return l1ps_mu15_eta2p1_vstar_;
	}
	int &l1ps_mu24_eta2p1_vstar()
	{
		if (not l1ps_mu24_eta2p1_vstar_isLoaded) {
			if (l1ps_mu24_eta2p1_vstar_branch != 0) {
				l1ps_mu24_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch l1ps_mu24_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			l1ps_mu24_eta2p1_vstar_isLoaded = true;
		}
		return l1ps_mu24_eta2p1_vstar_;
	}
	int &l1ps_mu30_eta2p1_vstar()
	{
		if (not l1ps_mu30_eta2p1_vstar_isLoaded) {
			if (l1ps_mu30_eta2p1_vstar_branch != 0) {
				l1ps_mu30_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch l1ps_mu30_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			l1ps_mu30_eta2p1_vstar_isLoaded = true;
		}
		return l1ps_mu30_eta2p1_vstar_;
	}
	int &l1ps_isoMu20_eta2p1_vstar()
	{
		if (not l1ps_isoMu20_eta2p1_vstar_isLoaded) {
			if (l1ps_isoMu20_eta2p1_vstar_branch != 0) {
				l1ps_isoMu20_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch l1ps_isoMu20_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			l1ps_isoMu20_eta2p1_vstar_isLoaded = true;
		}
		return l1ps_isoMu20_eta2p1_vstar_;
	}
	int &l1ps_isoMu24_eta2p1_vstar()
	{
		if (not l1ps_isoMu24_eta2p1_vstar_isLoaded) {
			if (l1ps_isoMu24_eta2p1_vstar_branch != 0) {
				l1ps_isoMu24_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch l1ps_isoMu24_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			l1ps_isoMu24_eta2p1_vstar_isLoaded = true;
		}
		return l1ps_isoMu24_eta2p1_vstar_;
	}
	int &l1ps_isoMu30_eta2p1_vstar()
	{
		if (not l1ps_isoMu30_eta2p1_vstar_isLoaded) {
			if (l1ps_isoMu30_eta2p1_vstar_branch != 0) {
				l1ps_isoMu30_eta2p1_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch l1ps_isoMu30_eta2p1_vstar_branch does not exist!\n");
				exit(1);
			}
			l1ps_isoMu30_eta2p1_vstar_isLoaded = true;
		}
		return l1ps_isoMu30_eta2p1_vstar_;
	}
	int &l1ps_relIso1p0Mu17_vstar()
	{
		if (not l1ps_relIso1p0Mu17_vstar_isLoaded) {
			if (l1ps_relIso1p0Mu17_vstar_branch != 0) {
				l1ps_relIso1p0Mu17_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch l1ps_relIso1p0Mu17_vstar_branch does not exist!\n");
				exit(1);
			}
			l1ps_relIso1p0Mu17_vstar_isLoaded = true;
		}
		return l1ps_relIso1p0Mu17_vstar_;
	}
	int &l1ps_relIso1p0Mu5_vstar()
	{
		if (not l1ps_relIso1p0Mu5_vstar_isLoaded) {
			if (l1ps_relIso1p0Mu5_vstar_branch != 0) {
				l1ps_relIso1p0Mu5_vstar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch l1ps_relIso1p0Mu5_vstar_branch does not exist!\n");
				exit(1);
			}
			l1ps_relIso1p0Mu5_vstar_isLoaded = true;
		}
		return l1ps_relIso1p0Mu5_vstar_;
	}
	float &ptj1()
	{
		if (not ptj1_isLoaded) {
			if (ptj1_branch != 0) {
				ptj1_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ptj1_branch does not exist!\n");
				exit(1);
			}
			ptj1_isLoaded = true;
		}
		return ptj1_;
	}
	int &nj1()
	{
		if (not nj1_isLoaded) {
			if (nj1_branch != 0) {
				nj1_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch nj1_branch does not exist!\n");
				exit(1);
			}
			nj1_isLoaded = true;
		}
		return nj1_;
	}
	float &ptj1_b2b()
	{
		if (not ptj1_b2b_isLoaded) {
			if (ptj1_b2b_branch != 0) {
				ptj1_b2b_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ptj1_b2b_branch does not exist!\n");
				exit(1);
			}
			ptj1_b2b_isLoaded = true;
		}
		return ptj1_b2b_;
	}
	float &dphij1_b2b()
	{
		if (not dphij1_b2b_isLoaded) {
			if (dphij1_b2b_branch != 0) {
				dphij1_b2b_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dphij1_b2b_branch does not exist!\n");
				exit(1);
			}
			dphij1_b2b_isLoaded = true;
		}
		return dphij1_b2b_;
	}
	float &ptpfj1()
	{
		if (not ptpfj1_isLoaded) {
			if (ptpfj1_branch != 0) {
				ptpfj1_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ptpfj1_branch does not exist!\n");
				exit(1);
			}
			ptpfj1_isLoaded = true;
		}
		return ptpfj1_;
	}
	int &npfj1()
	{
		if (not npfj1_isLoaded) {
			if (npfj1_branch != 0) {
				npfj1_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch npfj1_branch does not exist!\n");
				exit(1);
			}
			npfj1_isLoaded = true;
		}
		return npfj1_;
	}
	float &ptpfj1_b2b()
	{
		if (not ptpfj1_b2b_isLoaded) {
			if (ptpfj1_b2b_branch != 0) {
				ptpfj1_b2b_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ptpfj1_b2b_branch does not exist!\n");
				exit(1);
			}
			ptpfj1_b2b_isLoaded = true;
		}
		return ptpfj1_b2b_;
	}
	float &dphipfj1_b2b()
	{
		if (not dphipfj1_b2b_isLoaded) {
			if (dphipfj1_b2b_branch != 0) {
				dphipfj1_b2b_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dphipfj1_b2b_branch does not exist!\n");
				exit(1);
			}
			dphipfj1_b2b_isLoaded = true;
		}
		return dphipfj1_b2b_;
	}
	float &ptpfcj1()
	{
		if (not ptpfcj1_isLoaded) {
			if (ptpfcj1_branch != 0) {
				ptpfcj1_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ptpfcj1_branch does not exist!\n");
				exit(1);
			}
			ptpfcj1_isLoaded = true;
		}
		return ptpfcj1_;
	}
	int &npfcj1()
	{
		if (not npfcj1_isLoaded) {
			if (npfcj1_branch != 0) {
				npfcj1_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch npfcj1_branch does not exist!\n");
				exit(1);
			}
			npfcj1_isLoaded = true;
		}
		return npfcj1_;
	}
	float &ptpfcj1_b2b()
	{
		if (not ptpfcj1_b2b_isLoaded) {
			if (ptpfcj1_b2b_branch != 0) {
				ptpfcj1_b2b_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ptpfcj1_b2b_branch does not exist!\n");
				exit(1);
			}
			ptpfcj1_b2b_isLoaded = true;
		}
		return ptpfcj1_b2b_;
	}
	float &dphipfcj1_b2b()
	{
		if (not dphipfcj1_b2b_isLoaded) {
			if (dphipfcj1_b2b_branch != 0) {
				dphipfcj1_b2b_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dphipfcj1_b2b_branch does not exist!\n");
				exit(1);
			}
			dphipfcj1_b2b_isLoaded = true;
		}
		return dphipfcj1_b2b_;
	}
	bool &	btagpfc()
	{
		if (not btagpfc_isLoaded) {
			if (btagpfc_branch != 0) {
				btagpfc_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch btagpfc_branch does not exist!\n");
				exit(1);
			}
			btagpfc_isLoaded = true;
		}
		return btagpfc_;
	}
	float &emfpfcL1Fj1()
	{
		if (not emfpfcL1Fj1_isLoaded) {
			if (emfpfcL1Fj1_branch != 0) {
				emfpfcL1Fj1_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch emfpfcL1Fj1_branch does not exist!\n");
				exit(1);
			}
			emfpfcL1Fj1_isLoaded = true;
		}
		return emfpfcL1Fj1_;
	}
	float &ptpfcL1Fj1()
	{
		if (not ptpfcL1Fj1_isLoaded) {
			if (ptpfcL1Fj1_branch != 0) {
				ptpfcL1Fj1_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ptpfcL1Fj1_branch does not exist!\n");
				exit(1);
			}
			ptpfcL1Fj1_isLoaded = true;
		}
		return ptpfcL1Fj1_;
	}
	float &dphipfcL1Fj1()
	{
		if (not dphipfcL1Fj1_isLoaded) {
			if (dphipfcL1Fj1_branch != 0) {
				dphipfcL1Fj1_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dphipfcL1Fj1_branch does not exist!\n");
				exit(1);
			}
			dphipfcL1Fj1_isLoaded = true;
		}
		return dphipfcL1Fj1_;
	}
	int &npfcL1Fj1()
	{
		if (not npfcL1Fj1_isLoaded) {
			if (npfcL1Fj1_branch != 0) {
				npfcL1Fj1_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch npfcL1Fj1_branch does not exist!\n");
				exit(1);
			}
			npfcL1Fj1_isLoaded = true;
		}
		return npfcL1Fj1_;
	}
	int &npfc30L1Fj1()
	{
		if (not npfc30L1Fj1_isLoaded) {
			if (npfc30L1Fj1_branch != 0) {
				npfc30L1Fj1_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch npfc30L1Fj1_branch does not exist!\n");
				exit(1);
			}
			npfc30L1Fj1_isLoaded = true;
		}
		return npfc30L1Fj1_;
	}
	int &npfc40L1Fj1()
	{
		if (not npfc40L1Fj1_isLoaded) {
			if (npfc40L1Fj1_branch != 0) {
				npfc40L1Fj1_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch npfc40L1Fj1_branch does not exist!\n");
				exit(1);
			}
			npfc40L1Fj1_isLoaded = true;
		}
		return npfc40L1Fj1_;
	}
	float &ptpfcL1Fj1_b2b()
	{
		if (not ptpfcL1Fj1_b2b_isLoaded) {
			if (ptpfcL1Fj1_b2b_branch != 0) {
				ptpfcL1Fj1_b2b_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ptpfcL1Fj1_b2b_branch does not exist!\n");
				exit(1);
			}
			ptpfcL1Fj1_b2b_isLoaded = true;
		}
		return ptpfcL1Fj1_b2b_;
	}
	float &dphipfcL1Fj1_b2b()
	{
		if (not dphipfcL1Fj1_b2b_isLoaded) {
			if (dphipfcL1Fj1_b2b_branch != 0) {
				dphipfcL1Fj1_b2b_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dphipfcL1Fj1_b2b_branch does not exist!\n");
				exit(1);
			}
			dphipfcL1Fj1_b2b_isLoaded = true;
		}
		return dphipfcL1Fj1_b2b_;
	}
	bool &	btagpfcL1F()
	{
		if (not btagpfcL1F_isLoaded) {
			if (btagpfcL1F_branch != 0) {
				btagpfcL1F_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch btagpfcL1F_branch does not exist!\n");
				exit(1);
			}
			btagpfcL1F_isLoaded = true;
		}
		return btagpfcL1F_;
	}
	float &emfpfcL1Fj1res()
	{
		if (not emfpfcL1Fj1res_isLoaded) {
			if (emfpfcL1Fj1res_branch != 0) {
				emfpfcL1Fj1res_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch emfpfcL1Fj1res_branch does not exist!\n");
				exit(1);
			}
			emfpfcL1Fj1res_isLoaded = true;
		}
		return emfpfcL1Fj1res_;
	}
	float &ptpfcL1Fj1res()
	{
		if (not ptpfcL1Fj1res_isLoaded) {
			if (ptpfcL1Fj1res_branch != 0) {
				ptpfcL1Fj1res_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ptpfcL1Fj1res_branch does not exist!\n");
				exit(1);
			}
			ptpfcL1Fj1res_isLoaded = true;
		}
		return ptpfcL1Fj1res_;
	}
	float &dphipfcL1Fj1res()
	{
		if (not dphipfcL1Fj1res_isLoaded) {
			if (dphipfcL1Fj1res_branch != 0) {
				dphipfcL1Fj1res_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dphipfcL1Fj1res_branch does not exist!\n");
				exit(1);
			}
			dphipfcL1Fj1res_isLoaded = true;
		}
		return dphipfcL1Fj1res_;
	}
	int &npfcL1Fj1res()
	{
		if (not npfcL1Fj1res_isLoaded) {
			if (npfcL1Fj1res_branch != 0) {
				npfcL1Fj1res_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch npfcL1Fj1res_branch does not exist!\n");
				exit(1);
			}
			npfcL1Fj1res_isLoaded = true;
		}
		return npfcL1Fj1res_;
	}
	int &npfc30L1Fj1res()
	{
		if (not npfc30L1Fj1res_isLoaded) {
			if (npfc30L1Fj1res_branch != 0) {
				npfc30L1Fj1res_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch npfc30L1Fj1res_branch does not exist!\n");
				exit(1);
			}
			npfc30L1Fj1res_isLoaded = true;
		}
		return npfc30L1Fj1res_;
	}
	int &npfc40L1Fj1res()
	{
		if (not npfc40L1Fj1res_isLoaded) {
			if (npfc40L1Fj1res_branch != 0) {
				npfc40L1Fj1res_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch npfc40L1Fj1res_branch does not exist!\n");
				exit(1);
			}
			npfc40L1Fj1res_isLoaded = true;
		}
		return npfc40L1Fj1res_;
	}
	float &ptpfcL1Fj1res_b2b()
	{
		if (not ptpfcL1Fj1res_b2b_isLoaded) {
			if (ptpfcL1Fj1res_b2b_branch != 0) {
				ptpfcL1Fj1res_b2b_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ptpfcL1Fj1res_b2b_branch does not exist!\n");
				exit(1);
			}
			ptpfcL1Fj1res_b2b_isLoaded = true;
		}
		return ptpfcL1Fj1res_b2b_;
	}
	float &dphipfcL1Fj1res_b2b()
	{
		if (not dphipfcL1Fj1res_b2b_isLoaded) {
			if (dphipfcL1Fj1res_b2b_branch != 0) {
				dphipfcL1Fj1res_b2b_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dphipfcL1Fj1res_b2b_branch does not exist!\n");
				exit(1);
			}
			dphipfcL1Fj1res_b2b_isLoaded = true;
		}
		return dphipfcL1Fj1res_b2b_;
	}
	bool &	btagpfcL1Fres()
	{
		if (not btagpfcL1Fres_isLoaded) {
			if (btagpfcL1Fres_branch != 0) {
				btagpfcL1Fres_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch btagpfcL1Fres_branch does not exist!\n");
				exit(1);
			}
			btagpfcL1Fres_isLoaded = true;
		}
		return btagpfcL1Fres_;
	}
	float &ptbtagpfcL1Fj1()
	{
		if (not ptbtagpfcL1Fj1_isLoaded) {
			if (ptbtagpfcL1Fj1_branch != 0) {
				ptbtagpfcL1Fj1_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ptbtagpfcL1Fj1_branch does not exist!\n");
				exit(1);
			}
			ptbtagpfcL1Fj1_isLoaded = true;
		}
		return ptbtagpfcL1Fj1_;
	}
	float &dphibtagpfcL1Fj1()
	{
		if (not dphibtagpfcL1Fj1_isLoaded) {
			if (dphibtagpfcL1Fj1_branch != 0) {
				dphibtagpfcL1Fj1_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dphibtagpfcL1Fj1_branch does not exist!\n");
				exit(1);
			}
			dphibtagpfcL1Fj1_isLoaded = true;
		}
		return dphibtagpfcL1Fj1_;
	}
	float &ptbtagpfcL1Fj1res()
	{
		if (not ptbtagpfcL1Fj1res_isLoaded) {
			if (ptbtagpfcL1Fj1res_branch != 0) {
				ptbtagpfcL1Fj1res_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch ptbtagpfcL1Fj1res_branch does not exist!\n");
				exit(1);
			}
			ptbtagpfcL1Fj1res_isLoaded = true;
		}
		return ptbtagpfcL1Fj1res_;
	}
	float &dphibtagpfcL1Fj1res()
	{
		if (not dphibtagpfcL1Fj1res_isLoaded) {
			if (dphibtagpfcL1Fj1res_branch != 0) {
				dphibtagpfcL1Fj1res_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dphibtagpfcL1Fj1res_branch does not exist!\n");
				exit(1);
			}
			dphibtagpfcL1Fj1res_isLoaded = true;
		}
		return dphibtagpfcL1Fj1res_;
	}
	int &nbjet()
	{
		if (not nbjet_isLoaded) {
			if (nbjet_branch != 0) {
				nbjet_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch nbjet_branch does not exist!\n");
				exit(1);
			}
			nbjet_isLoaded = true;
		}
		return nbjet_;
	}
	float &dRNear()
	{
		if (not dRNear_isLoaded) {
			if (dRNear_branch != 0) {
				dRNear_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dRNear_branch does not exist!\n");
				exit(1);
			}
			dRNear_isLoaded = true;
		}
		return dRNear_;
	}
	float &dRFar()
	{
		if (not dRFar_isLoaded) {
			if (dRFar_branch != 0) {
				dRFar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dRFar_branch does not exist!\n");
				exit(1);
			}
			dRFar_isLoaded = true;
		}
		return dRFar_;
	}
	int &nbpfcjet()
	{
		if (not nbpfcjet_isLoaded) {
			if (nbpfcjet_branch != 0) {
				nbpfcjet_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch nbpfcjet_branch does not exist!\n");
				exit(1);
			}
			nbpfcjet_isLoaded = true;
		}
		return nbpfcjet_;
	}
	float &dRpfcNear()
	{
		if (not dRpfcNear_isLoaded) {
			if (dRpfcNear_branch != 0) {
				dRpfcNear_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dRpfcNear_branch does not exist!\n");
				exit(1);
			}
			dRpfcNear_isLoaded = true;
		}
		return dRpfcNear_;
	}
	float &dRpfcFar()
	{
		if (not dRpfcFar_isLoaded) {
			if (dRpfcFar_branch != 0) {
				dRpfcFar_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch dRpfcFar_branch does not exist!\n");
				exit(1);
			}
			dRpfcFar_isLoaded = true;
		}
		return dRpfcFar_;
	}
	float &rho()
	{
		if (not rho_isLoaded) {
			if (rho_branch != 0) {
				rho_branch->GetEntry(index);
				#ifdef PARANOIA
				#endif // #ifdef PARANOIA
			} else { 
				printf("branch rho_branch does not exist!\n");
				exit(1);
			}
			rho_isLoaded = true;
		}
		return rho_;
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
extern FakeRateBaby fake_rate_baby;
#endif

namespace frb {
	int &run();
	int &ls();
	unsigned int &evt();
	float &weight();
	int &pu_nPUvertices();
	int &evt_nvtxs();
	int &nFOels();
	int &nFOmus();
	int &ngsfs();
	int &nmus();
	int &foel_id();
	int &fomu_id();
	float &foel_mass();
	float &fomu_mass();
	float &pt();
	float &eta();
	float &sceta();
	float &phi();
	float &scet();
	float &hoe();
	float &pfmet();
	float &pfmetphi();
	float &iso();
	float &iso_nps();
	float &trck_iso();
	float &ecal_iso();
	float &ecal_iso_nps();
	float &hcal_iso();
	float &pfiso03();
	float &ch_pfiso03();
	float &nh_pfiso03();
	float &em_pfiso03();
	float &pfiso04();
	float &ch_pfiso04();
	float &nh_pfiso04();
	float &em_pfiso04();
	float &pfpupt03();
	float &pfpupt04();
	float &cpfiso03_rho();
	float &cpfiso03_db();
	int &id();
	bool &closestMuon();
	float &el_id_sieie();
	float &el_id_detain();
	float &el_id_dphiin();
	bool &el_id_smurfV5();
	bool &el_id_vbtf80();
	bool &el_id_vbtf90();
	float &el_effarea();
	float &mu_effarea03();
	float &mu_nh_effarea03();
	float &mu_em_effarea03();
	float &mu_effarea03_tight();
	float &mu_nh_effarea03_tight();
	float &mu_em_effarea03_tight();
	float &mu_effarea04();
	float &mu_nh_effarea04();
	float &mu_em_effarea04();
	float &mu_effarea04_tight();
	float &mu_nh_effarea04_tight();
	float &mu_em_effarea04_tight();
	bool &conv0MissHits();
	bool &convHitPattern();
	bool &convPartnerTrack();
	bool &convMIT();
	float &mt();
	float &pfmt();
	bool &q3();
	int &els_exp_innerlayers();
	float &d0PV_wwV1();
	float &dzPV_wwV1();
	float &ht_calo();
	float &ht_calo_L2L3();
	float &ht_pf();
	float &ht_pf_L2L3();
	float &ht_pf_L1FastL2L3();
	int &mcid();
	int &mcmotherid();
	int &mc3id();
	float &mc3pt();
	float &mc3dr();
	int &leptonIsFromW();
	bool &mu_isCosmic();
	float &mz_fo_gsf();
	float &mz_gsf_iso();
	float &mz_fo_ctf();
	float &mz_ctf_iso();
	float &mupsilon_fo_mu();
	float &mupsilon_mu_iso();
	bool &num_el_ssV7();
	bool &num_el_ssV7_noIso();
	bool &v1_el_ssV7();
	bool &v2_el_ssV7();
	bool &v3_el_ssV7();
	bool &num_mu_ssV5();
	bool &num_mu_ssV5_noIso();
	bool &fo_mu_ssV5();
	bool &fo_mu_ssV5_noIso();
	bool &num_el_ssV6();
	bool &num_el_ssV6_noIso();
	bool &v1_el_ssV6();
	bool &v2_el_ssV6();
	bool &v3_el_ssV6();
	bool &numNomSSv4();
	bool &numNomSSv4noIso();
	bool &fo_mussV4_04();
	bool &fo_mussV4_noIso();
	bool &num_el_smurfV6();
	bool &num_el_smurfV6lh();
	bool &v1_el_smurfV1();
	bool &v2_el_smurfV1();
	bool &v3_el_smurfV1();
	bool &v4_el_smurfV1();
	bool &num_mu_smurfV6();
	bool &fo_mu_smurf_04();
	bool &fo_mu_smurf_10();
	bool &num_el_OSV2();
	bool &num_mu_OSGV2();
	bool &num_mu_OSZV2();
	bool &fo_el_OSV2();
	bool &fo_mu_OSGV2();
	bool &num_el_OSV3();
	bool &num_mu_OSGV3();
	bool &fo_el_OSV3();
	bool &fo_mu_OSGV3();
	int &ele8_vstar();
	int &ele8_CaloIdL_TrkIdVL_vstar();
	int &ele8_CaloIdL_CaloIsoVL_Jet40_vstar();
	int &ele8_CaloIdL_CaloIsoVL_vstar();
	int &ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar();
	int &ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar();
	int &ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar();
	int &ele8_CaloIdT_TrkIdVL_vstar();
	int &ele8_CaloIdT_TrkIdVL_Jet30_vstar();
	int &ele17_CaloIdL_CaloIsoVL_vstar();
	int &ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar();
	int &ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar();
	int &photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar();
	int &ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar();
	int &ele27_WP80_vstar();
	int &ele8_version();
	int &ele8_CaloIdL_TrkIdVL_version();
	int &ele8_CaloIdL_CaloIsoVL_Jet40_version();
	int &ele8_CaloIdL_CaloIsoVL_version();
	int &ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version();
	int &ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version();
	int &ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version();
	int &ele8_CaloIdT_TrkIdVL_version();
	int &ele8_CaloIdT_TrkIdVL_Jet30_version();
	int &ele17_CaloIdL_CaloIsoVL_version();
	int &ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version();
	int &ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version();
	int &photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version();
	int &ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_version();
	int &ele27_WP80_version();
	float &dr_ele8_vstar();
	float &dr_ele8_CaloIdL_TrkIdVL_vstar();
	float &dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar();
	float &dr_ele8_CaloIdL_CaloIsoVL_vstar();
	float &dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar();
	float &dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar();
	float &dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar();
	float &dr_ele8_CaloIdT_TrkIdVL_vstar();
	float &dr_ele8_CaloIdT_TrkIdVL_Jet30_vstar();
	float &dr_ele17_CaloIdL_CaloIsoVL_vstar();
	float &dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar();
	float &dr_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar();
	float &dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar();
	float &dr_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar();
	float &dr_ele27_WP80_vstar();
	int &hltps_ele8_vstar();
	int &hltps_ele8_CaloIdL_TrkIdVL_vstar();
	int &hltps_ele8_CaloIdL_CaloIsoVL_Jet40_vstar();
	int &hltps_ele8_CaloIdL_CaloIsoVL_vstar();
	int &hltps_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar();
	int &hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar();
	int &hltps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar();
	int &hltps_ele8_CaloIdT_TrkIdVL_vstar();
	int &hltps_ele8_CaloIdT_TrkIdVL_Jet30_vstar();
	int &hltps_ele17_CaloIdL_CaloIsoVL_vstar();
	int &hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar();
	int &hltps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar();
	int &hltps_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar();
	int &hltps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar();
	int &hltps_ele27_WP80_vstar();
	int &l1ps_ele8_CaloIdL_CaloIsoVL_vstar();
	int &l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar();
	int &l1ps_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar();
	int &l1ps_ele8_CaloIdT_TrkIdVL_vstar();
	int &l1ps_ele8_CaloIdT_TrkIdVL_Jet30_vstar();
	int &l1ps_ele17_CaloIdL_CaloIsoVL_vstar();
	int &l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar();
	int &l1ps_ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar();
	int &l1ps_ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_CentralPFJet30_vstar();
	int &l1ps_ele27_WP80_vstar();
	int &mu3_vstar();
	int &mu5_vstar();
	int &mu8_vstar();
	int &mu12_vstar();
	int &mu15_vstar();
	int &mu17_vstar();
	int &mu20_vstar();
	int &mu24_vstar();
	int &mu30_vstar();
	int &mu15_eta2p1_vstar();
	int &mu24_eta2p1_vstar();
	int &mu30_eta2p1_vstar();
	int &mu8_Jet40_vstar();
	int &isoMu20_eta2p1_vstar();
	int &isoMu24_eta2p1_vstar();
	int &isoMu30_eta2p1_vstar();
	int &relIso1p0Mu17_vstar();
	int &relIso1p0Mu5_vstar();
	int &mu3_version();
	int &mu5_version();
	int &mu8_version();
	int &mu12_version();
	int &mu15_version();
	int &mu17_version();
	int &mu20_version();
	int &mu24_version();
	int &mu30_version();
	int &mu15_eta2p1_version();
	int &mu24_eta2p1_version();
	int &mu30_eta2p1_version();
	int &mu8_Jet40_version();
	int &isoMu20_eta2p1_version();
	int &isoMu24_eta2p1_version();
	int &isoMu30_eta2p1_version();
	int &relIso1p0Mu17_version();
	int &relIso1p0Mu5_version();
	float &dr_mu3_vstar();
	float &dr_mu5_vstar();
	float &dr_mu8_vstar();
	float &dr_mu12_vstar();
	float &dr_mu15_vstar();
	float &dr_mu17_vstar();
	float &dr_mu20_vstar();
	float &dr_mu24_vstar();
	float &dr_mu30_vstar();
	float &dr_mu15_eta2p1_vstar();
	float &dr_mu24_eta2p1_vstar();
	float &dr_mu30_eta2p1_vstar();
	float &dr_mu8_Jet40_vstar();
	float &dr_isoMu20_eta2p1_vstar();
	float &dr_isoMu24_eta2p1_vstar();
	float &dr_isoMu30_eta2p1_vstar();
	float &dr_relIso1p0Mu17_vstar();
	float &dr_relIso1p0Mu5_vstar();
	int &hltps_mu3_vstar();
	int &hltps_mu5_vstar();
	int &hltps_mu8_vstar();
	int &hltps_mu12_vstar();
	int &hltps_mu15_vstar();
	int &hltps_mu17_vstar();
	int &hltps_mu20_vstar();
	int &hltps_mu24_vstar();
	int &hltps_mu30_vstar();
	int &hltps_mu15_eta2p1_vstar();
	int &hltps_mu24_eta2p1_vstar();
	int &hltps_mu30_eta2p1_vstar();
	int &hltps_mu8_Jet40_vstar();
	int &hltps_isoMu20_eta2p1_vstar();
	int &hltps_isoMu24_eta2p1_vstar();
	int &hltps_isoMu30_eta2p1_vstar();
	int &hltps_relIso1p0Mu17_vstar();
	int &hltps_relIso1p0Mu5_vstar();
	int &l1ps_mu5_vstar();
	int &l1ps_mu8_vstar();
	int &l1ps_mu12_vstar();
	int &l1ps_mu17_vstar();
	int &l1ps_mu15_eta2p1_vstar();
	int &l1ps_mu24_eta2p1_vstar();
	int &l1ps_mu30_eta2p1_vstar();
	int &l1ps_isoMu20_eta2p1_vstar();
	int &l1ps_isoMu24_eta2p1_vstar();
	int &l1ps_isoMu30_eta2p1_vstar();
	int &l1ps_relIso1p0Mu17_vstar();
	int &l1ps_relIso1p0Mu5_vstar();
	float &ptj1();
	int &nj1();
	float &ptj1_b2b();
	float &dphij1_b2b();
	float &ptpfj1();
	int &npfj1();
	float &ptpfj1_b2b();
	float &dphipfj1_b2b();
	float &ptpfcj1();
	int &npfcj1();
	float &ptpfcj1_b2b();
	float &dphipfcj1_b2b();
	bool &btagpfc();
	float &emfpfcL1Fj1();
	float &ptpfcL1Fj1();
	float &dphipfcL1Fj1();
	int &npfcL1Fj1();
	int &npfc30L1Fj1();
	int &npfc40L1Fj1();
	float &ptpfcL1Fj1_b2b();
	float &dphipfcL1Fj1_b2b();
	bool &btagpfcL1F();
	float &emfpfcL1Fj1res();
	float &ptpfcL1Fj1res();
	float &dphipfcL1Fj1res();
	int &npfcL1Fj1res();
	int &npfc30L1Fj1res();
	int &npfc40L1Fj1res();
	float &ptpfcL1Fj1res_b2b();
	float &dphipfcL1Fj1res_b2b();
	bool &btagpfcL1Fres();
	float &ptbtagpfcL1Fj1();
	float &dphibtagpfcL1Fj1();
	float &ptbtagpfcL1Fj1res();
	float &dphibtagpfcL1Fj1res();
	int &nbjet();
	float &dRNear();
	float &dRFar();
	int &nbpfcjet();
	float &dRpfcNear();
	float &dRpfcFar();
	float &rho();
}
#endif
