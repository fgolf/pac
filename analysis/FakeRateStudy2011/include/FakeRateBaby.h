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
	int	evt_ndavtxs_;
	TBranch *evt_ndavtxs_branch;
	bool evt_ndavtxs_isLoaded;
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
	LorentzVector	lp4_;
	TBranch *lp4_branch;
	bool lp4_isLoaded;
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
	float	tcmet_;
	TBranch *tcmet_branch;
	bool tcmet_isLoaded;
	float	tcmetphi_;
	TBranch *tcmetphi_branch;
	bool tcmetphi_isLoaded;
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
	float	nt_iso_;
	TBranch *nt_iso_branch;
	bool nt_iso_isLoaded;
	float	nt_iso_nps_;
	TBranch *nt_iso_nps_branch;
	bool nt_iso_nps_isLoaded;
	float	trck_iso_;
	TBranch *trck_iso_branch;
	bool trck_iso_isLoaded;
	float	trck_nt_iso_;
	TBranch *trck_nt_iso_branch;
	bool trck_nt_iso_isLoaded;
	float	ecal_iso_;
	TBranch *ecal_iso_branch;
	bool ecal_iso_isLoaded;
	float	ecal_iso_nps_;
	TBranch *ecal_iso_nps_branch;
	bool ecal_iso_nps_isLoaded;
	float	ecal_nt_iso_;
	TBranch *ecal_nt_iso_branch;
	bool ecal_nt_iso_isLoaded;
	float	ecal_nt_iso_nps_;
	TBranch *ecal_nt_iso_nps_branch;
	bool ecal_nt_iso_nps_isLoaded;
	float	hcal_iso_;
	TBranch *hcal_iso_branch;
	bool hcal_iso_isLoaded;
	float	hcal_nt_iso_;
	TBranch *hcal_nt_iso_branch;
	bool hcal_nt_iso_isLoaded;
	float	nt_pfiso03_;
	TBranch *nt_pfiso03_branch;
	bool nt_pfiso03_isLoaded;
	float	nt_pfiso04_;
	TBranch *nt_pfiso04_branch;
	bool nt_pfiso04_isLoaded;
	int	id_;
	TBranch *id_branch;
	bool id_isLoaded;
	bool	closestMuon_;
	TBranch *closestMuon_branch;
	bool closestMuon_isLoaded;
	bool	el_id_smurfV5_;
	TBranch *el_id_smurfV5_branch;
	bool el_id_smurfV5_isLoaded;
	bool	el_id_vbtf80_;
	TBranch *el_id_vbtf80_branch;
	bool el_id_vbtf80_isLoaded;
	bool	el_id_vbtf90_;
	TBranch *el_id_vbtf90_branch;
	bool el_id_vbtf90_isLoaded;
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
	int	mcid_;
	TBranch *mcid_branch;
	bool mcid_isLoaded;
	int	mcmotherid_;
	TBranch *mcmotherid_branch;
	bool mcmotherid_isLoaded;
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
	float	ht_jpt_L2L3_;
	TBranch *ht_jpt_L2L3_branch;
	bool ht_jpt_L2L3_isLoaded;
	float	ht_pf_;
	TBranch *ht_pf_branch;
	bool ht_pf_isLoaded;
	float	ht_pf_L2L3_;
	TBranch *ht_pf_L2L3_branch;
	bool ht_pf_L2L3_isLoaded;
	float	ht_pf_L1FastL2L3_;
	TBranch *ht_pf_L1FastL2L3_branch;
	bool ht_pf_L1FastL2L3_isLoaded;
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
	float	el_lh_;
	TBranch *el_lh_branch;
	bool el_lh_isLoaded;
	float	el_mva_;
	TBranch *el_mva_branch;
	bool el_mva_isLoaded;
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
	bool	num_el_ssV3_;
	TBranch *num_el_ssV3_branch;
	bool num_el_ssV3_isLoaded;
	bool	v1_el_ssV3_;
	TBranch *v1_el_ssV3_branch;
	bool v1_el_ssV3_isLoaded;
	bool	v2_el_ssV3_;
	TBranch *v2_el_ssV3_branch;
	bool v2_el_ssV3_isLoaded;
	bool	v3_el_ssV3_;
	TBranch *v3_el_ssV3_branch;
	bool v3_el_ssV3_isLoaded;
	bool	num_el_ssV4_;
	TBranch *num_el_ssV4_branch;
	bool num_el_ssV4_isLoaded;
	bool	v1_el_ssV4_;
	TBranch *v1_el_ssV4_branch;
	bool v1_el_ssV4_isLoaded;
	bool	v2_el_ssV4_;
	TBranch *v2_el_ssV4_branch;
	bool v2_el_ssV4_isLoaded;
	bool	v3_el_ssV4_;
	TBranch *v3_el_ssV4_branch;
	bool v3_el_ssV4_isLoaded;
	bool	num_el_ssV5_;
	TBranch *num_el_ssV5_branch;
	bool num_el_ssV5_isLoaded;
	bool	v1_el_ssV5_;
	TBranch *v1_el_ssV5_branch;
	bool v1_el_ssV5_isLoaded;
	bool	v2_el_ssV5_;
	TBranch *v2_el_ssV5_branch;
	bool v2_el_ssV5_isLoaded;
	bool	v3_el_ssV5_;
	TBranch *v3_el_ssV5_branch;
	bool v3_el_ssV5_isLoaded;
	bool	num_el_ssV5_noIso_;
	TBranch *num_el_ssV5_noIso_branch;
	bool num_el_ssV5_noIso_isLoaded;
	bool	num_el_ssV6_;
	TBranch *num_el_ssV6_branch;
	bool num_el_ssV6_isLoaded;
	bool	v1_el_ssV6_;
	TBranch *v1_el_ssV6_branch;
	bool v1_el_ssV6_isLoaded;
	bool	v2_el_ssV6_;
	TBranch *v2_el_ssV6_branch;
	bool v2_el_ssV6_isLoaded;
	bool	v3_el_ssV6_;
	TBranch *v3_el_ssV6_branch;
	bool v3_el_ssV6_isLoaded;
	bool	num_el_ssV6_noIso_;
	TBranch *num_el_ssV6_noIso_branch;
	bool num_el_ssV6_noIso_isLoaded;
	bool	numNomSSv3_;
	TBranch *numNomSSv3_branch;
	bool numNomSSv3_isLoaded;
	bool	fo_mussV3_04_;
	TBranch *fo_mussV3_04_branch;
	bool fo_mussV3_04_isLoaded;
	bool	numNomSSv4_;
	TBranch *numNomSSv4_branch;
	bool numNomSSv4_isLoaded;
	bool	fo_mussV4_04_;
	TBranch *fo_mussV4_04_branch;
	bool fo_mussV4_04_isLoaded;
	bool	numNomSSv4noIso_;
	TBranch *numNomSSv4noIso_branch;
	bool numNomSSv4noIso_isLoaded;
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
	bool	numOct6_;
	TBranch *numOct6_branch;
	bool numOct6_isLoaded;
	bool	v1Oct6_;
	TBranch *v1Oct6_branch;
	bool v1Oct6_isLoaded;
	bool	v2Oct6_;
	TBranch *v2Oct6_branch;
	bool v2Oct6_isLoaded;
	bool	v3Oct6_;
	TBranch *v3Oct6_branch;
	bool v3Oct6_isLoaded;
	bool	num_;
	TBranch *num_branch;
	bool num_isLoaded;
	bool	fo_04_;
	TBranch *fo_04_branch;
	bool fo_04_isLoaded;
	bool	fo_10_;
	TBranch *fo_10_branch;
	bool fo_10_isLoaded;
	bool	v1SSV2_;
	TBranch *v1SSV2_branch;
	bool v1SSV2_isLoaded;
	bool	v2SSV2_;
	TBranch *v2SSV2_branch;
	bool v2SSV2_isLoaded;
	bool	v3SSV2_;
	TBranch *v3SSV2_branch;
	bool v3SSV2_isLoaded;
	bool	numSSV2_;
	TBranch *numSSV2_branch;
	bool numSSV2_isLoaded;
	bool	numNomSSv2_;
	TBranch *numNomSSv2_branch;
	bool numNomSSv2_isLoaded;
	bool	fo_mussV2_04_;
	TBranch *fo_mussV2_04_branch;
	bool fo_mussV2_04_isLoaded;
	bool	fo_mussV2_10_;
	TBranch *fo_mussV2_10_branch;
	bool fo_mussV2_10_isLoaded;
	bool	num_OSGv1_;
	TBranch *num_OSGv1_branch;
	bool num_OSGv1_isLoaded;
	bool	num_OSZv1_;
	TBranch *num_OSZv1_branch;
	bool num_OSZv1_isLoaded;
	bool	numOSOct18_;
	TBranch *numOSOct18_branch;
	bool numOSOct18_isLoaded;
	bool	v1OSOct18_;
	TBranch *v1OSOct18_branch;
	bool v1OSOct18_isLoaded;
	bool	v2OSOct18_;
	TBranch *v2OSOct18_branch;
	bool v2OSOct18_isLoaded;
	bool	v3OSOct18_;
	TBranch *v3OSOct18_branch;
	bool v3OSOct18_isLoaded;
	bool	num_wwV1_;
	TBranch *num_wwV1_branch;
	bool num_wwV1_isLoaded;
	bool	v1_wwV1_;
	TBranch *v1_wwV1_branch;
	bool v1_wwV1_isLoaded;
	bool	v2_wwV1_;
	TBranch *v2_wwV1_branch;
	bool v2_wwV1_isLoaded;
	bool	v3_wwV1_;
	TBranch *v3_wwV1_branch;
	bool v3_wwV1_isLoaded;
	bool	v4_wwV1_;
	TBranch *v4_wwV1_branch;
	bool v4_wwV1_isLoaded;
	bool	fo_wwV1_04_;
	TBranch *fo_wwV1_04_branch;
	bool fo_wwV1_04_isLoaded;
	bool	fo_wwV1_10_;
	TBranch *fo_wwV1_10_branch;
	bool fo_wwV1_10_isLoaded;
	bool	fo_wwV1_10_d0_;
	TBranch *fo_wwV1_10_d0_branch;
	bool fo_wwV1_10_d0_isLoaded;
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
	int	ele17_CaloIdL_CaloIsoVL_vstar_;
	TBranch *ele17_CaloIdL_CaloIsoVL_vstar_branch;
	bool ele17_CaloIdL_CaloIsoVL_vstar_isLoaded;
	int	ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_;
	TBranch *ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch;
	bool ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_isLoaded;
	int	ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_;
	TBranch *ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch;
	bool ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded;
	int	photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_;
	TBranch *photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch;
	bool photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_isLoaded;
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
	int	ele17_CaloIdL_CaloIsoVL_version_;
	TBranch *ele17_CaloIdL_CaloIsoVL_version_branch;
	bool ele17_CaloIdL_CaloIsoVL_version_isLoaded;
	int	ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_;
	TBranch *ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_branch;
	bool ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_isLoaded;
	int	ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_;
	TBranch *ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_branch;
	bool ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_isLoaded;
	int	photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_;
	TBranch *photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_branch;
	bool photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_isLoaded;
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
	float	dr_ele17_CaloIdL_CaloIsoVL_vstar_;
	TBranch *dr_ele17_CaloIdL_CaloIsoVL_vstar_branch;
	bool dr_ele17_CaloIdL_CaloIsoVL_vstar_isLoaded;
	float	dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_;
	TBranch *dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch;
	bool dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_isLoaded;
	float	dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_;
	TBranch *dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch;
	bool dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded;
	float	dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_;
	TBranch *dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch;
	bool dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_isLoaded;
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
	int	mu20_vstar_;
	TBranch *mu20_vstar_branch;
	bool mu20_vstar_isLoaded;
	int	mu24_vstar_;
	TBranch *mu24_vstar_branch;
	bool mu24_vstar_isLoaded;
	int	mu30_vstar_;
	TBranch *mu30_vstar_branch;
	bool mu30_vstar_isLoaded;
	int	mu8_Jet40_vstar_;
	TBranch *mu8_Jet40_vstar_branch;
	bool mu8_Jet40_vstar_isLoaded;
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
	int	mu20_version_;
	TBranch *mu20_version_branch;
	bool mu20_version_isLoaded;
	int	mu24_version_;
	TBranch *mu24_version_branch;
	bool mu24_version_isLoaded;
	int	mu30_version_;
	TBranch *mu30_version_branch;
	bool mu30_version_isLoaded;
	int	mu8_Jet40_version_;
	TBranch *mu8_Jet40_version_branch;
	bool mu8_Jet40_version_isLoaded;
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
	float	dr_mu20_vstar_;
	TBranch *dr_mu20_vstar_branch;
	bool dr_mu20_vstar_isLoaded;
	float	dr_mu24_vstar_;
	TBranch *dr_mu24_vstar_branch;
	bool dr_mu24_vstar_isLoaded;
	float	dr_mu30_vstar_;
	TBranch *dr_mu30_vstar_branch;
	bool dr_mu30_vstar_isLoaded;
	float	dr_mu8_Jet40_vstar_;
	TBranch *dr_mu8_Jet40_vstar_branch;
	bool dr_mu8_Jet40_vstar_isLoaded;
	int	hlt15u_;
	TBranch *hlt15u_branch;
	bool hlt15u_isLoaded;
	int	hlt30u_;
	TBranch *hlt30u_branch;
	bool hlt30u_isLoaded;
	int	hlt50u_;
	TBranch *hlt50u_branch;
	bool hlt50u_isLoaded;
	int	l16u_;
	TBranch *l16u_branch;
	bool l16u_isLoaded;
	int	l110_;
	TBranch *l110_branch;
	bool l110_isLoaded;
	int	ph10_;
	TBranch *ph10_branch;
	bool ph10_isLoaded;
	int	ph15_;
	TBranch *ph15_branch;
	bool ph15_isLoaded;
	int	ph20_;
	TBranch *ph20_branch;
	bool ph20_isLoaded;
	int	el10_lw_;
	TBranch *el10_lw_branch;
	bool el10_lw_isLoaded;
	int	el10_sw_;
	TBranch *el10_sw_branch;
	bool el10_sw_isLoaded;
	int	el10_sw_v2_;
	TBranch *el10_sw_v2_branch;
	bool el10_sw_v2_isLoaded;
	int	el10_lw_id_;
	TBranch *el10_lw_id_branch;
	bool el10_lw_id_isLoaded;
	int	el10_sw_id_;
	TBranch *el10_sw_id_branch;
	bool el10_sw_id_isLoaded;
	int	el15_lw_;
	TBranch *el15_lw_branch;
	bool el15_lw_isLoaded;
	int	el15_sw_;
	TBranch *el15_sw_branch;
	bool el15_sw_isLoaded;
	int	el15_lw_id_;
	TBranch *el15_lw_id_branch;
	bool el15_lw_id_isLoaded;
	int	el15_sw_id_;
	TBranch *el15_sw_id_branch;
	bool el15_sw_id_isLoaded;
	int	el15_sw_cid_;
	TBranch *el15_sw_cid_branch;
	bool el15_sw_cid_isLoaded;
	int	el20_sw_;
	TBranch *el20_sw_branch;
	bool el20_sw_isLoaded;
	int	el25_sw_;
	TBranch *el25_sw_branch;
	bool el25_sw_isLoaded;
	int	Del10_sw_;
	TBranch *Del10_sw_branch;
	bool Del10_sw_isLoaded;
	int	el17_sw_;
	TBranch *el17_sw_branch;
	bool el17_sw_isLoaded;
	int	el17_sw_v2_;
	TBranch *el17_sw_v2_branch;
	bool el17_sw_v2_isLoaded;
	int	el17_iso_;
	TBranch *el17_iso_branch;
	bool el17_iso_isLoaded;
	int	el17_loose_;
	TBranch *el17_loose_branch;
	bool el17_loose_isLoaded;
	int	el17_sw_cid_;
	TBranch *el17_sw_cid_branch;
	bool el17_sw_cid_isLoaded;
	int	el17_sw_id_;
	TBranch *el17_sw_id_branch;
	bool el17_sw_id_isLoaded;
	int	el17_tiso_;
	TBranch *el17_tiso_branch;
	bool el17_tiso_isLoaded;
	int	el17_tiso_v1_;
	TBranch *el17_tiso_v1_branch;
	bool el17_tiso_v1_isLoaded;
	float	drph10_;
	TBranch *drph10_branch;
	bool drph10_isLoaded;
	float	drph15_;
	TBranch *drph15_branch;
	bool drph15_isLoaded;
	float	drph20_;
	TBranch *drph20_branch;
	bool drph20_isLoaded;
	float	drel10_lw_;
	TBranch *drel10_lw_branch;
	bool drel10_lw_isLoaded;
	float	drel10_sw_;
	TBranch *drel10_sw_branch;
	bool drel10_sw_isLoaded;
	float	drel10_sw_v2_;
	TBranch *drel10_sw_v2_branch;
	bool drel10_sw_v2_isLoaded;
	float	drel10_lw_id_;
	TBranch *drel10_lw_id_branch;
	bool drel10_lw_id_isLoaded;
	float	drel10_sw_id_;
	TBranch *drel10_sw_id_branch;
	bool drel10_sw_id_isLoaded;
	float	drel15_lw_;
	TBranch *drel15_lw_branch;
	bool drel15_lw_isLoaded;
	float	drel15_sw_;
	TBranch *drel15_sw_branch;
	bool drel15_sw_isLoaded;
	float	drel15_lw_id_;
	TBranch *drel15_lw_id_branch;
	bool drel15_lw_id_isLoaded;
	float	drel15_sw_id_;
	TBranch *drel15_sw_id_branch;
	bool drel15_sw_id_isLoaded;
	float	drel15_sw_cid_;
	TBranch *drel15_sw_cid_branch;
	bool drel15_sw_cid_isLoaded;
	float	drel20_sw_;
	TBranch *drel20_sw_branch;
	bool drel20_sw_isLoaded;
	float	drel25_sw_;
	TBranch *drel25_sw_branch;
	bool drel25_sw_isLoaded;
	float	drDel10_sw_;
	TBranch *drDel10_sw_branch;
	bool drDel10_sw_isLoaded;
	float	drel17_sw_;
	TBranch *drel17_sw_branch;
	bool drel17_sw_isLoaded;
	float	drel17_sw_v2_;
	TBranch *drel17_sw_v2_branch;
	bool drel17_sw_v2_isLoaded;
	float	drel17_iso_;
	TBranch *drel17_iso_branch;
	bool drel17_iso_isLoaded;
	float	drel17_loose_;
	TBranch *drel17_loose_branch;
	bool drel17_loose_isLoaded;
	float	drel17_sw_cid_;
	TBranch *drel17_sw_cid_branch;
	bool drel17_sw_cid_isLoaded;
	float	drel17_sw_id_;
	TBranch *drel17_sw_id_branch;
	bool drel17_sw_id_isLoaded;
	float	drel17_tiso_;
	TBranch *drel17_tiso_branch;
	bool drel17_tiso_isLoaded;
	float	drel17_tiso_v1_;
	TBranch *drel17_tiso_v1_branch;
	bool drel17_tiso_v1_isLoaded;
	int	mu17_;
	TBranch *mu17_branch;
	bool mu17_isLoaded;
	int	mu15_;
	TBranch *mu15_branch;
	bool mu15_isLoaded;
	int	mu13_;
	TBranch *mu13_branch;
	bool mu13_isLoaded;
	int	mu11_;
	TBranch *mu11_branch;
	bool mu11_isLoaded;
	int	mu9_;
	TBranch *mu9_branch;
	bool mu9_isLoaded;
	int	mu7_;
	TBranch *mu7_branch;
	bool mu7_isLoaded;
	int	mu5_;
	TBranch *mu5_branch;
	bool mu5_isLoaded;
	float	drmu17_;
	TBranch *drmu17_branch;
	bool drmu17_isLoaded;
	float	drmu15_;
	TBranch *drmu15_branch;
	bool drmu15_isLoaded;
	float	drmu13_;
	TBranch *drmu13_branch;
	bool drmu13_isLoaded;
	float	drmu11_;
	TBranch *drmu11_branch;
	bool drmu11_isLoaded;
	float	drmu9_;
	TBranch *drmu9_branch;
	bool drmu9_isLoaded;
	float	drmu7_;
	TBranch *drmu7_branch;
	bool drmu7_isLoaded;
	float	drmu5_;
	TBranch *drmu5_branch;
	bool drmu5_isLoaded;
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
	float	ptbtagpfcL1Fj1_;
	TBranch *ptbtagpfcL1Fj1_branch;
	bool ptbtagpfcL1Fj1_isLoaded;
	float	dphibtagpfcL1Fj1_;
	TBranch *dphibtagpfcL1Fj1_branch;
	bool dphibtagpfcL1Fj1_isLoaded;
	float	ptjptcj1_;
	TBranch *ptjptcj1_branch;
	bool ptjptcj1_isLoaded;
	int	njptcj1_;
	TBranch *njptcj1_branch;
	bool njptcj1_isLoaded;
	float	ptjptcj1_b2b_;
	TBranch *ptjptcj1_b2b_branch;
	bool ptjptcj1_b2b_isLoaded;
	float	dphijptcj1_b2b_;
	TBranch *dphijptcj1_b2b_branch;
	bool dphijptcj1_b2b_isLoaded;
	bool	btagjptc_;
	TBranch *btagjptc_branch;
	bool btagjptc_isLoaded;
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
	evt_ndavtxs_branch = 0;
	if (tree->GetBranch("evt_ndavtxs") != 0) {
		evt_ndavtxs_branch = tree->GetBranch("evt_ndavtxs");
		evt_ndavtxs_branch->SetAddress(&evt_ndavtxs_);
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
	lp4_branch = 0;
	if (tree->GetBranch("lp4") != 0) {
		lp4_branch = tree->GetBranch("lp4");
		lp4_branch->SetAddress(&lp4_);
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
	tcmet_branch = 0;
	if (tree->GetBranch("tcmet") != 0) {
		tcmet_branch = tree->GetBranch("tcmet");
		tcmet_branch->SetAddress(&tcmet_);
	}
	tcmetphi_branch = 0;
	if (tree->GetBranch("tcmetphi") != 0) {
		tcmetphi_branch = tree->GetBranch("tcmetphi");
		tcmetphi_branch->SetAddress(&tcmetphi_);
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
	nt_iso_branch = 0;
	if (tree->GetBranch("nt_iso") != 0) {
		nt_iso_branch = tree->GetBranch("nt_iso");
		nt_iso_branch->SetAddress(&nt_iso_);
	}
	nt_iso_nps_branch = 0;
	if (tree->GetBranch("nt_iso_nps") != 0) {
		nt_iso_nps_branch = tree->GetBranch("nt_iso_nps");
		nt_iso_nps_branch->SetAddress(&nt_iso_nps_);
	}
	trck_iso_branch = 0;
	if (tree->GetBranch("trck_iso") != 0) {
		trck_iso_branch = tree->GetBranch("trck_iso");
		trck_iso_branch->SetAddress(&trck_iso_);
	}
	trck_nt_iso_branch = 0;
	if (tree->GetBranch("trck_nt_iso") != 0) {
		trck_nt_iso_branch = tree->GetBranch("trck_nt_iso");
		trck_nt_iso_branch->SetAddress(&trck_nt_iso_);
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
	ecal_nt_iso_branch = 0;
	if (tree->GetBranch("ecal_nt_iso") != 0) {
		ecal_nt_iso_branch = tree->GetBranch("ecal_nt_iso");
		ecal_nt_iso_branch->SetAddress(&ecal_nt_iso_);
	}
	ecal_nt_iso_nps_branch = 0;
	if (tree->GetBranch("ecal_nt_iso_nps") != 0) {
		ecal_nt_iso_nps_branch = tree->GetBranch("ecal_nt_iso_nps");
		ecal_nt_iso_nps_branch->SetAddress(&ecal_nt_iso_nps_);
	}
	hcal_iso_branch = 0;
	if (tree->GetBranch("hcal_iso") != 0) {
		hcal_iso_branch = tree->GetBranch("hcal_iso");
		hcal_iso_branch->SetAddress(&hcal_iso_);
	}
	hcal_nt_iso_branch = 0;
	if (tree->GetBranch("hcal_nt_iso") != 0) {
		hcal_nt_iso_branch = tree->GetBranch("hcal_nt_iso");
		hcal_nt_iso_branch->SetAddress(&hcal_nt_iso_);
	}
	nt_pfiso03_branch = 0;
	if (tree->GetBranch("nt_pfiso03") != 0) {
		nt_pfiso03_branch = tree->GetBranch("nt_pfiso03");
		nt_pfiso03_branch->SetAddress(&nt_pfiso03_);
	}
	nt_pfiso04_branch = 0;
	if (tree->GetBranch("nt_pfiso04") != 0) {
		nt_pfiso04_branch = tree->GetBranch("nt_pfiso04");
		nt_pfiso04_branch->SetAddress(&nt_pfiso04_);
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
	ht_jpt_L2L3_branch = 0;
	if (tree->GetBranch("ht_jpt_L2L3") != 0) {
		ht_jpt_L2L3_branch = tree->GetBranch("ht_jpt_L2L3");
		ht_jpt_L2L3_branch->SetAddress(&ht_jpt_L2L3_);
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
	el_lh_branch = 0;
	if (tree->GetBranch("el_lh") != 0) {
		el_lh_branch = tree->GetBranch("el_lh");
		el_lh_branch->SetAddress(&el_lh_);
	}
	el_mva_branch = 0;
	if (tree->GetBranch("el_mva") != 0) {
		el_mva_branch = tree->GetBranch("el_mva");
		el_mva_branch->SetAddress(&el_mva_);
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
	num_el_ssV3_branch = 0;
	if (tree->GetBranch("num_el_ssV3") != 0) {
		num_el_ssV3_branch = tree->GetBranch("num_el_ssV3");
		num_el_ssV3_branch->SetAddress(&num_el_ssV3_);
	}
	v1_el_ssV3_branch = 0;
	if (tree->GetBranch("v1_el_ssV3") != 0) {
		v1_el_ssV3_branch = tree->GetBranch("v1_el_ssV3");
		v1_el_ssV3_branch->SetAddress(&v1_el_ssV3_);
	}
	v2_el_ssV3_branch = 0;
	if (tree->GetBranch("v2_el_ssV3") != 0) {
		v2_el_ssV3_branch = tree->GetBranch("v2_el_ssV3");
		v2_el_ssV3_branch->SetAddress(&v2_el_ssV3_);
	}
	v3_el_ssV3_branch = 0;
	if (tree->GetBranch("v3_el_ssV3") != 0) {
		v3_el_ssV3_branch = tree->GetBranch("v3_el_ssV3");
		v3_el_ssV3_branch->SetAddress(&v3_el_ssV3_);
	}
	num_el_ssV4_branch = 0;
	if (tree->GetBranch("num_el_ssV4") != 0) {
		num_el_ssV4_branch = tree->GetBranch("num_el_ssV4");
		num_el_ssV4_branch->SetAddress(&num_el_ssV4_);
	}
	v1_el_ssV4_branch = 0;
	if (tree->GetBranch("v1_el_ssV4") != 0) {
		v1_el_ssV4_branch = tree->GetBranch("v1_el_ssV4");
		v1_el_ssV4_branch->SetAddress(&v1_el_ssV4_);
	}
	v2_el_ssV4_branch = 0;
	if (tree->GetBranch("v2_el_ssV4") != 0) {
		v2_el_ssV4_branch = tree->GetBranch("v2_el_ssV4");
		v2_el_ssV4_branch->SetAddress(&v2_el_ssV4_);
	}
	v3_el_ssV4_branch = 0;
	if (tree->GetBranch("v3_el_ssV4") != 0) {
		v3_el_ssV4_branch = tree->GetBranch("v3_el_ssV4");
		v3_el_ssV4_branch->SetAddress(&v3_el_ssV4_);
	}
	num_el_ssV5_branch = 0;
	if (tree->GetBranch("num_el_ssV5") != 0) {
		num_el_ssV5_branch = tree->GetBranch("num_el_ssV5");
		num_el_ssV5_branch->SetAddress(&num_el_ssV5_);
	}
	v1_el_ssV5_branch = 0;
	if (tree->GetBranch("v1_el_ssV5") != 0) {
		v1_el_ssV5_branch = tree->GetBranch("v1_el_ssV5");
		v1_el_ssV5_branch->SetAddress(&v1_el_ssV5_);
	}
	v2_el_ssV5_branch = 0;
	if (tree->GetBranch("v2_el_ssV5") != 0) {
		v2_el_ssV5_branch = tree->GetBranch("v2_el_ssV5");
		v2_el_ssV5_branch->SetAddress(&v2_el_ssV5_);
	}
	v3_el_ssV5_branch = 0;
	if (tree->GetBranch("v3_el_ssV5") != 0) {
		v3_el_ssV5_branch = tree->GetBranch("v3_el_ssV5");
		v3_el_ssV5_branch->SetAddress(&v3_el_ssV5_);
	}
	num_el_ssV5_noIso_branch = 0;
	if (tree->GetBranch("num_el_ssV5_noIso") != 0) {
		num_el_ssV5_noIso_branch = tree->GetBranch("num_el_ssV5_noIso");
		num_el_ssV5_noIso_branch->SetAddress(&num_el_ssV5_noIso_);
	}
	num_el_ssV6_branch = 0;
	if (tree->GetBranch("num_el_ssV6") != 0) {
		num_el_ssV6_branch = tree->GetBranch("num_el_ssV6");
		num_el_ssV6_branch->SetAddress(&num_el_ssV6_);
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
	num_el_ssV6_noIso_branch = 0;
	if (tree->GetBranch("num_el_ssV6_noIso") != 0) {
		num_el_ssV6_noIso_branch = tree->GetBranch("num_el_ssV6_noIso");
		num_el_ssV6_noIso_branch->SetAddress(&num_el_ssV6_noIso_);
	}
	numNomSSv3_branch = 0;
	if (tree->GetBranch("numNomSSv3") != 0) {
		numNomSSv3_branch = tree->GetBranch("numNomSSv3");
		numNomSSv3_branch->SetAddress(&numNomSSv3_);
	}
	fo_mussV3_04_branch = 0;
	if (tree->GetBranch("fo_mussV3_04") != 0) {
		fo_mussV3_04_branch = tree->GetBranch("fo_mussV3_04");
		fo_mussV3_04_branch->SetAddress(&fo_mussV3_04_);
	}
	numNomSSv4_branch = 0;
	if (tree->GetBranch("numNomSSv4") != 0) {
		numNomSSv4_branch = tree->GetBranch("numNomSSv4");
		numNomSSv4_branch->SetAddress(&numNomSSv4_);
	}
	fo_mussV4_04_branch = 0;
	if (tree->GetBranch("fo_mussV4_04") != 0) {
		fo_mussV4_04_branch = tree->GetBranch("fo_mussV4_04");
		fo_mussV4_04_branch->SetAddress(&fo_mussV4_04_);
	}
	numNomSSv4noIso_branch = 0;
	if (tree->GetBranch("numNomSSv4noIso") != 0) {
		numNomSSv4noIso_branch = tree->GetBranch("numNomSSv4noIso");
		numNomSSv4noIso_branch->SetAddress(&numNomSSv4noIso_);
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
	numOct6_branch = 0;
	if (tree->GetBranch("numOct6") != 0) {
		numOct6_branch = tree->GetBranch("numOct6");
		numOct6_branch->SetAddress(&numOct6_);
	}
	v1Oct6_branch = 0;
	if (tree->GetBranch("v1Oct6") != 0) {
		v1Oct6_branch = tree->GetBranch("v1Oct6");
		v1Oct6_branch->SetAddress(&v1Oct6_);
	}
	v2Oct6_branch = 0;
	if (tree->GetBranch("v2Oct6") != 0) {
		v2Oct6_branch = tree->GetBranch("v2Oct6");
		v2Oct6_branch->SetAddress(&v2Oct6_);
	}
	v3Oct6_branch = 0;
	if (tree->GetBranch("v3Oct6") != 0) {
		v3Oct6_branch = tree->GetBranch("v3Oct6");
		v3Oct6_branch->SetAddress(&v3Oct6_);
	}
	num_branch = 0;
	if (tree->GetBranch("num") != 0) {
		num_branch = tree->GetBranch("num");
		num_branch->SetAddress(&num_);
	}
	fo_04_branch = 0;
	if (tree->GetBranch("fo_04") != 0) {
		fo_04_branch = tree->GetBranch("fo_04");
		fo_04_branch->SetAddress(&fo_04_);
	}
	fo_10_branch = 0;
	if (tree->GetBranch("fo_10") != 0) {
		fo_10_branch = tree->GetBranch("fo_10");
		fo_10_branch->SetAddress(&fo_10_);
	}
	v1SSV2_branch = 0;
	if (tree->GetBranch("v1SSV2") != 0) {
		v1SSV2_branch = tree->GetBranch("v1SSV2");
		v1SSV2_branch->SetAddress(&v1SSV2_);
	}
	v2SSV2_branch = 0;
	if (tree->GetBranch("v2SSV2") != 0) {
		v2SSV2_branch = tree->GetBranch("v2SSV2");
		v2SSV2_branch->SetAddress(&v2SSV2_);
	}
	v3SSV2_branch = 0;
	if (tree->GetBranch("v3SSV2") != 0) {
		v3SSV2_branch = tree->GetBranch("v3SSV2");
		v3SSV2_branch->SetAddress(&v3SSV2_);
	}
	numSSV2_branch = 0;
	if (tree->GetBranch("numSSV2") != 0) {
		numSSV2_branch = tree->GetBranch("numSSV2");
		numSSV2_branch->SetAddress(&numSSV2_);
	}
	numNomSSv2_branch = 0;
	if (tree->GetBranch("numNomSSv2") != 0) {
		numNomSSv2_branch = tree->GetBranch("numNomSSv2");
		numNomSSv2_branch->SetAddress(&numNomSSv2_);
	}
	fo_mussV2_04_branch = 0;
	if (tree->GetBranch("fo_mussV2_04") != 0) {
		fo_mussV2_04_branch = tree->GetBranch("fo_mussV2_04");
		fo_mussV2_04_branch->SetAddress(&fo_mussV2_04_);
	}
	fo_mussV2_10_branch = 0;
	if (tree->GetBranch("fo_mussV2_10") != 0) {
		fo_mussV2_10_branch = tree->GetBranch("fo_mussV2_10");
		fo_mussV2_10_branch->SetAddress(&fo_mussV2_10_);
	}
	num_OSGv1_branch = 0;
	if (tree->GetBranch("num_OSGv1") != 0) {
		num_OSGv1_branch = tree->GetBranch("num_OSGv1");
		num_OSGv1_branch->SetAddress(&num_OSGv1_);
	}
	num_OSZv1_branch = 0;
	if (tree->GetBranch("num_OSZv1") != 0) {
		num_OSZv1_branch = tree->GetBranch("num_OSZv1");
		num_OSZv1_branch->SetAddress(&num_OSZv1_);
	}
	numOSOct18_branch = 0;
	if (tree->GetBranch("numOSOct18") != 0) {
		numOSOct18_branch = tree->GetBranch("numOSOct18");
		numOSOct18_branch->SetAddress(&numOSOct18_);
	}
	v1OSOct18_branch = 0;
	if (tree->GetBranch("v1OSOct18") != 0) {
		v1OSOct18_branch = tree->GetBranch("v1OSOct18");
		v1OSOct18_branch->SetAddress(&v1OSOct18_);
	}
	v2OSOct18_branch = 0;
	if (tree->GetBranch("v2OSOct18") != 0) {
		v2OSOct18_branch = tree->GetBranch("v2OSOct18");
		v2OSOct18_branch->SetAddress(&v2OSOct18_);
	}
	v3OSOct18_branch = 0;
	if (tree->GetBranch("v3OSOct18") != 0) {
		v3OSOct18_branch = tree->GetBranch("v3OSOct18");
		v3OSOct18_branch->SetAddress(&v3OSOct18_);
	}
	num_wwV1_branch = 0;
	if (tree->GetBranch("num_wwV1") != 0) {
		num_wwV1_branch = tree->GetBranch("num_wwV1");
		num_wwV1_branch->SetAddress(&num_wwV1_);
	}
	v1_wwV1_branch = 0;
	if (tree->GetBranch("v1_wwV1") != 0) {
		v1_wwV1_branch = tree->GetBranch("v1_wwV1");
		v1_wwV1_branch->SetAddress(&v1_wwV1_);
	}
	v2_wwV1_branch = 0;
	if (tree->GetBranch("v2_wwV1") != 0) {
		v2_wwV1_branch = tree->GetBranch("v2_wwV1");
		v2_wwV1_branch->SetAddress(&v2_wwV1_);
	}
	v3_wwV1_branch = 0;
	if (tree->GetBranch("v3_wwV1") != 0) {
		v3_wwV1_branch = tree->GetBranch("v3_wwV1");
		v3_wwV1_branch->SetAddress(&v3_wwV1_);
	}
	v4_wwV1_branch = 0;
	if (tree->GetBranch("v4_wwV1") != 0) {
		v4_wwV1_branch = tree->GetBranch("v4_wwV1");
		v4_wwV1_branch->SetAddress(&v4_wwV1_);
	}
	fo_wwV1_04_branch = 0;
	if (tree->GetBranch("fo_wwV1_04") != 0) {
		fo_wwV1_04_branch = tree->GetBranch("fo_wwV1_04");
		fo_wwV1_04_branch->SetAddress(&fo_wwV1_04_);
	}
	fo_wwV1_10_branch = 0;
	if (tree->GetBranch("fo_wwV1_10") != 0) {
		fo_wwV1_10_branch = tree->GetBranch("fo_wwV1_10");
		fo_wwV1_10_branch->SetAddress(&fo_wwV1_10_);
	}
	fo_wwV1_10_d0_branch = 0;
	if (tree->GetBranch("fo_wwV1_10_d0") != 0) {
		fo_wwV1_10_d0_branch = tree->GetBranch("fo_wwV1_10_d0");
		fo_wwV1_10_d0_branch->SetAddress(&fo_wwV1_10_d0_);
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
	ele17_CaloIdL_CaloIsoVL_vstar_branch = 0;
	if (tree->GetBranch("ele17_CaloIdL_CaloIsoVL_vstar") != 0) {
		ele17_CaloIdL_CaloIsoVL_vstar_branch = tree->GetBranch("ele17_CaloIdL_CaloIsoVL_vstar");
		ele17_CaloIdL_CaloIsoVL_vstar_branch->SetAddress(&ele17_CaloIdL_CaloIsoVL_vstar_);
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
	photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch = 0;
	if (tree->GetBranch("photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar") != 0) {
		photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch = tree->GetBranch("photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar");
		photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch->SetAddress(&photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_);
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
	ele17_CaloIdL_CaloIsoVL_version_branch = 0;
	if (tree->GetBranch("ele17_CaloIdL_CaloIsoVL_version") != 0) {
		ele17_CaloIdL_CaloIsoVL_version_branch = tree->GetBranch("ele17_CaloIdL_CaloIsoVL_version");
		ele17_CaloIdL_CaloIsoVL_version_branch->SetAddress(&ele17_CaloIdL_CaloIsoVL_version_);
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
	photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_branch = 0;
	if (tree->GetBranch("photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version") != 0) {
		photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_branch = tree->GetBranch("photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version");
		photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_branch->SetAddress(&photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_);
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
	dr_ele17_CaloIdL_CaloIsoVL_vstar_branch = 0;
	if (tree->GetBranch("dr_ele17_CaloIdL_CaloIsoVL_vstar") != 0) {
		dr_ele17_CaloIdL_CaloIsoVL_vstar_branch = tree->GetBranch("dr_ele17_CaloIdL_CaloIsoVL_vstar");
		dr_ele17_CaloIdL_CaloIsoVL_vstar_branch->SetAddress(&dr_ele17_CaloIdL_CaloIsoVL_vstar_);
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
	dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch = 0;
	if (tree->GetBranch("dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar") != 0) {
		dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch = tree->GetBranch("dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar");
		dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch->SetAddress(&dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_);
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
	mu8_Jet40_vstar_branch = 0;
	if (tree->GetBranch("mu8_Jet40_vstar") != 0) {
		mu8_Jet40_vstar_branch = tree->GetBranch("mu8_Jet40_vstar");
		mu8_Jet40_vstar_branch->SetAddress(&mu8_Jet40_vstar_);
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
	mu8_Jet40_version_branch = 0;
	if (tree->GetBranch("mu8_Jet40_version") != 0) {
		mu8_Jet40_version_branch = tree->GetBranch("mu8_Jet40_version");
		mu8_Jet40_version_branch->SetAddress(&mu8_Jet40_version_);
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
	dr_mu8_Jet40_vstar_branch = 0;
	if (tree->GetBranch("dr_mu8_Jet40_vstar") != 0) {
		dr_mu8_Jet40_vstar_branch = tree->GetBranch("dr_mu8_Jet40_vstar");
		dr_mu8_Jet40_vstar_branch->SetAddress(&dr_mu8_Jet40_vstar_);
	}
	hlt15u_branch = 0;
	if (tree->GetBranch("hlt15u") != 0) {
		hlt15u_branch = tree->GetBranch("hlt15u");
		hlt15u_branch->SetAddress(&hlt15u_);
	}
	hlt30u_branch = 0;
	if (tree->GetBranch("hlt30u") != 0) {
		hlt30u_branch = tree->GetBranch("hlt30u");
		hlt30u_branch->SetAddress(&hlt30u_);
	}
	hlt50u_branch = 0;
	if (tree->GetBranch("hlt50u") != 0) {
		hlt50u_branch = tree->GetBranch("hlt50u");
		hlt50u_branch->SetAddress(&hlt50u_);
	}
	l16u_branch = 0;
	if (tree->GetBranch("l16u") != 0) {
		l16u_branch = tree->GetBranch("l16u");
		l16u_branch->SetAddress(&l16u_);
	}
	l110_branch = 0;
	if (tree->GetBranch("l110") != 0) {
		l110_branch = tree->GetBranch("l110");
		l110_branch->SetAddress(&l110_);
	}
	ph10_branch = 0;
	if (tree->GetBranch("ph10") != 0) {
		ph10_branch = tree->GetBranch("ph10");
		ph10_branch->SetAddress(&ph10_);
	}
	ph15_branch = 0;
	if (tree->GetBranch("ph15") != 0) {
		ph15_branch = tree->GetBranch("ph15");
		ph15_branch->SetAddress(&ph15_);
	}
	ph20_branch = 0;
	if (tree->GetBranch("ph20") != 0) {
		ph20_branch = tree->GetBranch("ph20");
		ph20_branch->SetAddress(&ph20_);
	}
	el10_lw_branch = 0;
	if (tree->GetBranch("el10_lw") != 0) {
		el10_lw_branch = tree->GetBranch("el10_lw");
		el10_lw_branch->SetAddress(&el10_lw_);
	}
	el10_sw_branch = 0;
	if (tree->GetBranch("el10_sw") != 0) {
		el10_sw_branch = tree->GetBranch("el10_sw");
		el10_sw_branch->SetAddress(&el10_sw_);
	}
	el10_sw_v2_branch = 0;
	if (tree->GetBranch("el10_sw_v2") != 0) {
		el10_sw_v2_branch = tree->GetBranch("el10_sw_v2");
		el10_sw_v2_branch->SetAddress(&el10_sw_v2_);
	}
	el10_lw_id_branch = 0;
	if (tree->GetBranch("el10_lw_id") != 0) {
		el10_lw_id_branch = tree->GetBranch("el10_lw_id");
		el10_lw_id_branch->SetAddress(&el10_lw_id_);
	}
	el10_sw_id_branch = 0;
	if (tree->GetBranch("el10_sw_id") != 0) {
		el10_sw_id_branch = tree->GetBranch("el10_sw_id");
		el10_sw_id_branch->SetAddress(&el10_sw_id_);
	}
	el15_lw_branch = 0;
	if (tree->GetBranch("el15_lw") != 0) {
		el15_lw_branch = tree->GetBranch("el15_lw");
		el15_lw_branch->SetAddress(&el15_lw_);
	}
	el15_sw_branch = 0;
	if (tree->GetBranch("el15_sw") != 0) {
		el15_sw_branch = tree->GetBranch("el15_sw");
		el15_sw_branch->SetAddress(&el15_sw_);
	}
	el15_lw_id_branch = 0;
	if (tree->GetBranch("el15_lw_id") != 0) {
		el15_lw_id_branch = tree->GetBranch("el15_lw_id");
		el15_lw_id_branch->SetAddress(&el15_lw_id_);
	}
	el15_sw_id_branch = 0;
	if (tree->GetBranch("el15_sw_id") != 0) {
		el15_sw_id_branch = tree->GetBranch("el15_sw_id");
		el15_sw_id_branch->SetAddress(&el15_sw_id_);
	}
	el15_sw_cid_branch = 0;
	if (tree->GetBranch("el15_sw_cid") != 0) {
		el15_sw_cid_branch = tree->GetBranch("el15_sw_cid");
		el15_sw_cid_branch->SetAddress(&el15_sw_cid_);
	}
	el20_sw_branch = 0;
	if (tree->GetBranch("el20_sw") != 0) {
		el20_sw_branch = tree->GetBranch("el20_sw");
		el20_sw_branch->SetAddress(&el20_sw_);
	}
	el25_sw_branch = 0;
	if (tree->GetBranch("el25_sw") != 0) {
		el25_sw_branch = tree->GetBranch("el25_sw");
		el25_sw_branch->SetAddress(&el25_sw_);
	}
	Del10_sw_branch = 0;
	if (tree->GetBranch("Del10_sw") != 0) {
		Del10_sw_branch = tree->GetBranch("Del10_sw");
		Del10_sw_branch->SetAddress(&Del10_sw_);
	}
	el17_sw_branch = 0;
	if (tree->GetBranch("el17_sw") != 0) {
		el17_sw_branch = tree->GetBranch("el17_sw");
		el17_sw_branch->SetAddress(&el17_sw_);
	}
	el17_sw_v2_branch = 0;
	if (tree->GetBranch("el17_sw_v2") != 0) {
		el17_sw_v2_branch = tree->GetBranch("el17_sw_v2");
		el17_sw_v2_branch->SetAddress(&el17_sw_v2_);
	}
	el17_iso_branch = 0;
	if (tree->GetBranch("el17_iso") != 0) {
		el17_iso_branch = tree->GetBranch("el17_iso");
		el17_iso_branch->SetAddress(&el17_iso_);
	}
	el17_loose_branch = 0;
	if (tree->GetBranch("el17_loose") != 0) {
		el17_loose_branch = tree->GetBranch("el17_loose");
		el17_loose_branch->SetAddress(&el17_loose_);
	}
	el17_sw_cid_branch = 0;
	if (tree->GetBranch("el17_sw_cid") != 0) {
		el17_sw_cid_branch = tree->GetBranch("el17_sw_cid");
		el17_sw_cid_branch->SetAddress(&el17_sw_cid_);
	}
	el17_sw_id_branch = 0;
	if (tree->GetBranch("el17_sw_id") != 0) {
		el17_sw_id_branch = tree->GetBranch("el17_sw_id");
		el17_sw_id_branch->SetAddress(&el17_sw_id_);
	}
	el17_tiso_branch = 0;
	if (tree->GetBranch("el17_tiso") != 0) {
		el17_tiso_branch = tree->GetBranch("el17_tiso");
		el17_tiso_branch->SetAddress(&el17_tiso_);
	}
	el17_tiso_v1_branch = 0;
	if (tree->GetBranch("el17_tiso_v1") != 0) {
		el17_tiso_v1_branch = tree->GetBranch("el17_tiso_v1");
		el17_tiso_v1_branch->SetAddress(&el17_tiso_v1_);
	}
	drph10_branch = 0;
	if (tree->GetBranch("drph10") != 0) {
		drph10_branch = tree->GetBranch("drph10");
		drph10_branch->SetAddress(&drph10_);
	}
	drph15_branch = 0;
	if (tree->GetBranch("drph15") != 0) {
		drph15_branch = tree->GetBranch("drph15");
		drph15_branch->SetAddress(&drph15_);
	}
	drph20_branch = 0;
	if (tree->GetBranch("drph20") != 0) {
		drph20_branch = tree->GetBranch("drph20");
		drph20_branch->SetAddress(&drph20_);
	}
	drel10_lw_branch = 0;
	if (tree->GetBranch("drel10_lw") != 0) {
		drel10_lw_branch = tree->GetBranch("drel10_lw");
		drel10_lw_branch->SetAddress(&drel10_lw_);
	}
	drel10_sw_branch = 0;
	if (tree->GetBranch("drel10_sw") != 0) {
		drel10_sw_branch = tree->GetBranch("drel10_sw");
		drel10_sw_branch->SetAddress(&drel10_sw_);
	}
	drel10_sw_v2_branch = 0;
	if (tree->GetBranch("drel10_sw_v2") != 0) {
		drel10_sw_v2_branch = tree->GetBranch("drel10_sw_v2");
		drel10_sw_v2_branch->SetAddress(&drel10_sw_v2_);
	}
	drel10_lw_id_branch = 0;
	if (tree->GetBranch("drel10_lw_id") != 0) {
		drel10_lw_id_branch = tree->GetBranch("drel10_lw_id");
		drel10_lw_id_branch->SetAddress(&drel10_lw_id_);
	}
	drel10_sw_id_branch = 0;
	if (tree->GetBranch("drel10_sw_id") != 0) {
		drel10_sw_id_branch = tree->GetBranch("drel10_sw_id");
		drel10_sw_id_branch->SetAddress(&drel10_sw_id_);
	}
	drel15_lw_branch = 0;
	if (tree->GetBranch("drel15_lw") != 0) {
		drel15_lw_branch = tree->GetBranch("drel15_lw");
		drel15_lw_branch->SetAddress(&drel15_lw_);
	}
	drel15_sw_branch = 0;
	if (tree->GetBranch("drel15_sw") != 0) {
		drel15_sw_branch = tree->GetBranch("drel15_sw");
		drel15_sw_branch->SetAddress(&drel15_sw_);
	}
	drel15_lw_id_branch = 0;
	if (tree->GetBranch("drel15_lw_id") != 0) {
		drel15_lw_id_branch = tree->GetBranch("drel15_lw_id");
		drel15_lw_id_branch->SetAddress(&drel15_lw_id_);
	}
	drel15_sw_id_branch = 0;
	if (tree->GetBranch("drel15_sw_id") != 0) {
		drel15_sw_id_branch = tree->GetBranch("drel15_sw_id");
		drel15_sw_id_branch->SetAddress(&drel15_sw_id_);
	}
	drel15_sw_cid_branch = 0;
	if (tree->GetBranch("drel15_sw_cid") != 0) {
		drel15_sw_cid_branch = tree->GetBranch("drel15_sw_cid");
		drel15_sw_cid_branch->SetAddress(&drel15_sw_cid_);
	}
	drel20_sw_branch = 0;
	if (tree->GetBranch("drel20_sw") != 0) {
		drel20_sw_branch = tree->GetBranch("drel20_sw");
		drel20_sw_branch->SetAddress(&drel20_sw_);
	}
	drel25_sw_branch = 0;
	if (tree->GetBranch("drel25_sw") != 0) {
		drel25_sw_branch = tree->GetBranch("drel25_sw");
		drel25_sw_branch->SetAddress(&drel25_sw_);
	}
	drDel10_sw_branch = 0;
	if (tree->GetBranch("drDel10_sw") != 0) {
		drDel10_sw_branch = tree->GetBranch("drDel10_sw");
		drDel10_sw_branch->SetAddress(&drDel10_sw_);
	}
	drel17_sw_branch = 0;
	if (tree->GetBranch("drel17_sw") != 0) {
		drel17_sw_branch = tree->GetBranch("drel17_sw");
		drel17_sw_branch->SetAddress(&drel17_sw_);
	}
	drel17_sw_v2_branch = 0;
	if (tree->GetBranch("drel17_sw_v2") != 0) {
		drel17_sw_v2_branch = tree->GetBranch("drel17_sw_v2");
		drel17_sw_v2_branch->SetAddress(&drel17_sw_v2_);
	}
	drel17_iso_branch = 0;
	if (tree->GetBranch("drel17_iso") != 0) {
		drel17_iso_branch = tree->GetBranch("drel17_iso");
		drel17_iso_branch->SetAddress(&drel17_iso_);
	}
	drel17_loose_branch = 0;
	if (tree->GetBranch("drel17_loose") != 0) {
		drel17_loose_branch = tree->GetBranch("drel17_loose");
		drel17_loose_branch->SetAddress(&drel17_loose_);
	}
	drel17_sw_cid_branch = 0;
	if (tree->GetBranch("drel17_sw_cid") != 0) {
		drel17_sw_cid_branch = tree->GetBranch("drel17_sw_cid");
		drel17_sw_cid_branch->SetAddress(&drel17_sw_cid_);
	}
	drel17_sw_id_branch = 0;
	if (tree->GetBranch("drel17_sw_id") != 0) {
		drel17_sw_id_branch = tree->GetBranch("drel17_sw_id");
		drel17_sw_id_branch->SetAddress(&drel17_sw_id_);
	}
	drel17_tiso_branch = 0;
	if (tree->GetBranch("drel17_tiso") != 0) {
		drel17_tiso_branch = tree->GetBranch("drel17_tiso");
		drel17_tiso_branch->SetAddress(&drel17_tiso_);
	}
	drel17_tiso_v1_branch = 0;
	if (tree->GetBranch("drel17_tiso_v1") != 0) {
		drel17_tiso_v1_branch = tree->GetBranch("drel17_tiso_v1");
		drel17_tiso_v1_branch->SetAddress(&drel17_tiso_v1_);
	}
	mu17_branch = 0;
	if (tree->GetBranch("mu17") != 0) {
		mu17_branch = tree->GetBranch("mu17");
		mu17_branch->SetAddress(&mu17_);
	}
	mu15_branch = 0;
	if (tree->GetBranch("mu15") != 0) {
		mu15_branch = tree->GetBranch("mu15");
		mu15_branch->SetAddress(&mu15_);
	}
	mu13_branch = 0;
	if (tree->GetBranch("mu13") != 0) {
		mu13_branch = tree->GetBranch("mu13");
		mu13_branch->SetAddress(&mu13_);
	}
	mu11_branch = 0;
	if (tree->GetBranch("mu11") != 0) {
		mu11_branch = tree->GetBranch("mu11");
		mu11_branch->SetAddress(&mu11_);
	}
	mu9_branch = 0;
	if (tree->GetBranch("mu9") != 0) {
		mu9_branch = tree->GetBranch("mu9");
		mu9_branch->SetAddress(&mu9_);
	}
	mu7_branch = 0;
	if (tree->GetBranch("mu7") != 0) {
		mu7_branch = tree->GetBranch("mu7");
		mu7_branch->SetAddress(&mu7_);
	}
	mu5_branch = 0;
	if (tree->GetBranch("mu5") != 0) {
		mu5_branch = tree->GetBranch("mu5");
		mu5_branch->SetAddress(&mu5_);
	}
	drmu17_branch = 0;
	if (tree->GetBranch("drmu17") != 0) {
		drmu17_branch = tree->GetBranch("drmu17");
		drmu17_branch->SetAddress(&drmu17_);
	}
	drmu15_branch = 0;
	if (tree->GetBranch("drmu15") != 0) {
		drmu15_branch = tree->GetBranch("drmu15");
		drmu15_branch->SetAddress(&drmu15_);
	}
	drmu13_branch = 0;
	if (tree->GetBranch("drmu13") != 0) {
		drmu13_branch = tree->GetBranch("drmu13");
		drmu13_branch->SetAddress(&drmu13_);
	}
	drmu11_branch = 0;
	if (tree->GetBranch("drmu11") != 0) {
		drmu11_branch = tree->GetBranch("drmu11");
		drmu11_branch->SetAddress(&drmu11_);
	}
	drmu9_branch = 0;
	if (tree->GetBranch("drmu9") != 0) {
		drmu9_branch = tree->GetBranch("drmu9");
		drmu9_branch->SetAddress(&drmu9_);
	}
	drmu7_branch = 0;
	if (tree->GetBranch("drmu7") != 0) {
		drmu7_branch = tree->GetBranch("drmu7");
		drmu7_branch->SetAddress(&drmu7_);
	}
	drmu5_branch = 0;
	if (tree->GetBranch("drmu5") != 0) {
		drmu5_branch = tree->GetBranch("drmu5");
		drmu5_branch->SetAddress(&drmu5_);
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
	ptjptcj1_branch = 0;
	if (tree->GetBranch("ptjptcj1") != 0) {
		ptjptcj1_branch = tree->GetBranch("ptjptcj1");
		ptjptcj1_branch->SetAddress(&ptjptcj1_);
	}
	njptcj1_branch = 0;
	if (tree->GetBranch("njptcj1") != 0) {
		njptcj1_branch = tree->GetBranch("njptcj1");
		njptcj1_branch->SetAddress(&njptcj1_);
	}
	ptjptcj1_b2b_branch = 0;
	if (tree->GetBranch("ptjptcj1_b2b") != 0) {
		ptjptcj1_b2b_branch = tree->GetBranch("ptjptcj1_b2b");
		ptjptcj1_b2b_branch->SetAddress(&ptjptcj1_b2b_);
	}
	dphijptcj1_b2b_branch = 0;
	if (tree->GetBranch("dphijptcj1_b2b") != 0) {
		dphijptcj1_b2b_branch = tree->GetBranch("dphijptcj1_b2b");
		dphijptcj1_b2b_branch->SetAddress(&dphijptcj1_b2b_);
	}
	btagjptc_branch = 0;
	if (tree->GetBranch("btagjptc") != 0) {
		btagjptc_branch = tree->GetBranch("btagjptc");
		btagjptc_branch->SetAddress(&btagjptc_);
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
		evt_ndavtxs_isLoaded = false;
		nFOels_isLoaded = false;
		nFOmus_isLoaded = false;
		ngsfs_isLoaded = false;
		nmus_isLoaded = false;
		foel_id_isLoaded = false;
		fomu_id_isLoaded = false;
		foel_mass_isLoaded = false;
		fomu_mass_isLoaded = false;
		pt_isLoaded = false;
		lp4_isLoaded = false;
		eta_isLoaded = false;
		sceta_isLoaded = false;
		phi_isLoaded = false;
		scet_isLoaded = false;
		hoe_isLoaded = false;
		tcmet_isLoaded = false;
		tcmetphi_isLoaded = false;
		pfmet_isLoaded = false;
		pfmetphi_isLoaded = false;
		iso_isLoaded = false;
		iso_nps_isLoaded = false;
		nt_iso_isLoaded = false;
		nt_iso_nps_isLoaded = false;
		trck_iso_isLoaded = false;
		trck_nt_iso_isLoaded = false;
		ecal_iso_isLoaded = false;
		ecal_iso_nps_isLoaded = false;
		ecal_nt_iso_isLoaded = false;
		ecal_nt_iso_nps_isLoaded = false;
		hcal_iso_isLoaded = false;
		hcal_nt_iso_isLoaded = false;
		nt_pfiso03_isLoaded = false;
		nt_pfiso04_isLoaded = false;
		id_isLoaded = false;
		closestMuon_isLoaded = false;
		el_id_smurfV5_isLoaded = false;
		el_id_vbtf80_isLoaded = false;
		el_id_vbtf90_isLoaded = false;
		conv0MissHits_isLoaded = false;
		convHitPattern_isLoaded = false;
		convPartnerTrack_isLoaded = false;
		convMIT_isLoaded = false;
		mt_isLoaded = false;
		pfmt_isLoaded = false;
		q3_isLoaded = false;
		els_exp_innerlayers_isLoaded = false;
		mcid_isLoaded = false;
		mcmotherid_isLoaded = false;
		d0PV_wwV1_isLoaded = false;
		dzPV_wwV1_isLoaded = false;
		ht_calo_isLoaded = false;
		ht_calo_L2L3_isLoaded = false;
		ht_jpt_L2L3_isLoaded = false;
		ht_pf_isLoaded = false;
		ht_pf_L2L3_isLoaded = false;
		ht_pf_L1FastL2L3_isLoaded = false;
		mc3id_isLoaded = false;
		mc3pt_isLoaded = false;
		mc3dr_isLoaded = false;
		leptonIsFromW_isLoaded = false;
		el_lh_isLoaded = false;
		el_mva_isLoaded = false;
		mu_isCosmic_isLoaded = false;
		mz_fo_gsf_isLoaded = false;
		mz_gsf_iso_isLoaded = false;
		mz_fo_ctf_isLoaded = false;
		mz_ctf_iso_isLoaded = false;
		mupsilon_fo_mu_isLoaded = false;
		mupsilon_mu_iso_isLoaded = false;
		num_el_ssV3_isLoaded = false;
		v1_el_ssV3_isLoaded = false;
		v2_el_ssV3_isLoaded = false;
		v3_el_ssV3_isLoaded = false;
		num_el_ssV4_isLoaded = false;
		v1_el_ssV4_isLoaded = false;
		v2_el_ssV4_isLoaded = false;
		v3_el_ssV4_isLoaded = false;
		num_el_ssV5_isLoaded = false;
		v1_el_ssV5_isLoaded = false;
		v2_el_ssV5_isLoaded = false;
		v3_el_ssV5_isLoaded = false;
		num_el_ssV5_noIso_isLoaded = false;
		num_el_ssV6_isLoaded = false;
		v1_el_ssV6_isLoaded = false;
		v2_el_ssV6_isLoaded = false;
		v3_el_ssV6_isLoaded = false;
		num_el_ssV6_noIso_isLoaded = false;
		numNomSSv3_isLoaded = false;
		fo_mussV3_04_isLoaded = false;
		numNomSSv4_isLoaded = false;
		fo_mussV4_04_isLoaded = false;
		numNomSSv4noIso_isLoaded = false;
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
		numOct6_isLoaded = false;
		v1Oct6_isLoaded = false;
		v2Oct6_isLoaded = false;
		v3Oct6_isLoaded = false;
		num_isLoaded = false;
		fo_04_isLoaded = false;
		fo_10_isLoaded = false;
		v1SSV2_isLoaded = false;
		v2SSV2_isLoaded = false;
		v3SSV2_isLoaded = false;
		numSSV2_isLoaded = false;
		numNomSSv2_isLoaded = false;
		fo_mussV2_04_isLoaded = false;
		fo_mussV2_10_isLoaded = false;
		num_OSGv1_isLoaded = false;
		num_OSZv1_isLoaded = false;
		numOSOct18_isLoaded = false;
		v1OSOct18_isLoaded = false;
		v2OSOct18_isLoaded = false;
		v3OSOct18_isLoaded = false;
		num_wwV1_isLoaded = false;
		v1_wwV1_isLoaded = false;
		v2_wwV1_isLoaded = false;
		v3_wwV1_isLoaded = false;
		v4_wwV1_isLoaded = false;
		fo_wwV1_04_isLoaded = false;
		fo_wwV1_10_isLoaded = false;
		fo_wwV1_10_d0_isLoaded = false;
		ele8_vstar_isLoaded = false;
		ele8_CaloIdL_TrkIdVL_vstar_isLoaded = false;
		ele8_CaloIdL_CaloIsoVL_Jet40_vstar_isLoaded = false;
		ele8_CaloIdL_CaloIsoVL_vstar_isLoaded = false;
		ele17_CaloIdL_CaloIsoVL_vstar_isLoaded = false;
		ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_isLoaded = false;
		ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded = false;
		photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_isLoaded = false;
		ele8_version_isLoaded = false;
		ele8_CaloIdL_TrkIdVL_version_isLoaded = false;
		ele8_CaloIdL_CaloIsoVL_Jet40_version_isLoaded = false;
		ele8_CaloIdL_CaloIsoVL_version_isLoaded = false;
		ele17_CaloIdL_CaloIsoVL_version_isLoaded = false;
		ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_isLoaded = false;
		ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_isLoaded = false;
		photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_isLoaded = false;
		dr_ele8_vstar_isLoaded = false;
		dr_ele8_CaloIdL_TrkIdVL_vstar_isLoaded = false;
		dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_isLoaded = false;
		dr_ele8_CaloIdL_CaloIsoVL_vstar_isLoaded = false;
		dr_ele17_CaloIdL_CaloIsoVL_vstar_isLoaded = false;
		dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_isLoaded = false;
		dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded = false;
		dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_isLoaded = false;
		mu3_vstar_isLoaded = false;
		mu5_vstar_isLoaded = false;
		mu8_vstar_isLoaded = false;
		mu12_vstar_isLoaded = false;
		mu15_vstar_isLoaded = false;
		mu20_vstar_isLoaded = false;
		mu24_vstar_isLoaded = false;
		mu30_vstar_isLoaded = false;
		mu8_Jet40_vstar_isLoaded = false;
		mu3_version_isLoaded = false;
		mu5_version_isLoaded = false;
		mu8_version_isLoaded = false;
		mu12_version_isLoaded = false;
		mu15_version_isLoaded = false;
		mu20_version_isLoaded = false;
		mu24_version_isLoaded = false;
		mu30_version_isLoaded = false;
		mu8_Jet40_version_isLoaded = false;
		dr_mu3_vstar_isLoaded = false;
		dr_mu5_vstar_isLoaded = false;
		dr_mu8_vstar_isLoaded = false;
		dr_mu12_vstar_isLoaded = false;
		dr_mu15_vstar_isLoaded = false;
		dr_mu20_vstar_isLoaded = false;
		dr_mu24_vstar_isLoaded = false;
		dr_mu30_vstar_isLoaded = false;
		dr_mu8_Jet40_vstar_isLoaded = false;
		hlt15u_isLoaded = false;
		hlt30u_isLoaded = false;
		hlt50u_isLoaded = false;
		l16u_isLoaded = false;
		l110_isLoaded = false;
		ph10_isLoaded = false;
		ph15_isLoaded = false;
		ph20_isLoaded = false;
		el10_lw_isLoaded = false;
		el10_sw_isLoaded = false;
		el10_sw_v2_isLoaded = false;
		el10_lw_id_isLoaded = false;
		el10_sw_id_isLoaded = false;
		el15_lw_isLoaded = false;
		el15_sw_isLoaded = false;
		el15_lw_id_isLoaded = false;
		el15_sw_id_isLoaded = false;
		el15_sw_cid_isLoaded = false;
		el20_sw_isLoaded = false;
		el25_sw_isLoaded = false;
		Del10_sw_isLoaded = false;
		el17_sw_isLoaded = false;
		el17_sw_v2_isLoaded = false;
		el17_iso_isLoaded = false;
		el17_loose_isLoaded = false;
		el17_sw_cid_isLoaded = false;
		el17_sw_id_isLoaded = false;
		el17_tiso_isLoaded = false;
		el17_tiso_v1_isLoaded = false;
		drph10_isLoaded = false;
		drph15_isLoaded = false;
		drph20_isLoaded = false;
		drel10_lw_isLoaded = false;
		drel10_sw_isLoaded = false;
		drel10_sw_v2_isLoaded = false;
		drel10_lw_id_isLoaded = false;
		drel10_sw_id_isLoaded = false;
		drel15_lw_isLoaded = false;
		drel15_sw_isLoaded = false;
		drel15_lw_id_isLoaded = false;
		drel15_sw_id_isLoaded = false;
		drel15_sw_cid_isLoaded = false;
		drel20_sw_isLoaded = false;
		drel25_sw_isLoaded = false;
		drDel10_sw_isLoaded = false;
		drel17_sw_isLoaded = false;
		drel17_sw_v2_isLoaded = false;
		drel17_iso_isLoaded = false;
		drel17_loose_isLoaded = false;
		drel17_sw_cid_isLoaded = false;
		drel17_sw_id_isLoaded = false;
		drel17_tiso_isLoaded = false;
		drel17_tiso_v1_isLoaded = false;
		mu17_isLoaded = false;
		mu15_isLoaded = false;
		mu13_isLoaded = false;
		mu11_isLoaded = false;
		mu9_isLoaded = false;
		mu7_isLoaded = false;
		mu5_isLoaded = false;
		drmu17_isLoaded = false;
		drmu15_isLoaded = false;
		drmu13_isLoaded = false;
		drmu11_isLoaded = false;
		drmu9_isLoaded = false;
		drmu7_isLoaded = false;
		drmu5_isLoaded = false;
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
		ptbtagpfcL1Fj1_isLoaded = false;
		dphibtagpfcL1Fj1_isLoaded = false;
		ptjptcj1_isLoaded = false;
		njptcj1_isLoaded = false;
		ptjptcj1_b2b_isLoaded = false;
		dphijptcj1_b2b_isLoaded = false;
		btagjptc_isLoaded = false;
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
	if (evt_ndavtxs_branch != 0) evt_ndavtxs();
	if (nFOels_branch != 0) nFOels();
	if (nFOmus_branch != 0) nFOmus();
	if (ngsfs_branch != 0) ngsfs();
	if (nmus_branch != 0) nmus();
	if (foel_id_branch != 0) foel_id();
	if (fomu_id_branch != 0) fomu_id();
	if (foel_mass_branch != 0) foel_mass();
	if (fomu_mass_branch != 0) fomu_mass();
	if (pt_branch != 0) pt();
	if (lp4_branch != 0) lp4();
	if (eta_branch != 0) eta();
	if (sceta_branch != 0) sceta();
	if (phi_branch != 0) phi();
	if (scet_branch != 0) scet();
	if (hoe_branch != 0) hoe();
	if (tcmet_branch != 0) tcmet();
	if (tcmetphi_branch != 0) tcmetphi();
	if (pfmet_branch != 0) pfmet();
	if (pfmetphi_branch != 0) pfmetphi();
	if (iso_branch != 0) iso();
	if (iso_nps_branch != 0) iso_nps();
	if (nt_iso_branch != 0) nt_iso();
	if (nt_iso_nps_branch != 0) nt_iso_nps();
	if (trck_iso_branch != 0) trck_iso();
	if (trck_nt_iso_branch != 0) trck_nt_iso();
	if (ecal_iso_branch != 0) ecal_iso();
	if (ecal_iso_nps_branch != 0) ecal_iso_nps();
	if (ecal_nt_iso_branch != 0) ecal_nt_iso();
	if (ecal_nt_iso_nps_branch != 0) ecal_nt_iso_nps();
	if (hcal_iso_branch != 0) hcal_iso();
	if (hcal_nt_iso_branch != 0) hcal_nt_iso();
	if (nt_pfiso03_branch != 0) nt_pfiso03();
	if (nt_pfiso04_branch != 0) nt_pfiso04();
	if (id_branch != 0) id();
	if (closestMuon_branch != 0) closestMuon();
	if (el_id_smurfV5_branch != 0) el_id_smurfV5();
	if (el_id_vbtf80_branch != 0) el_id_vbtf80();
	if (el_id_vbtf90_branch != 0) el_id_vbtf90();
	if (conv0MissHits_branch != 0) conv0MissHits();
	if (convHitPattern_branch != 0) convHitPattern();
	if (convPartnerTrack_branch != 0) convPartnerTrack();
	if (convMIT_branch != 0) convMIT();
	if (mt_branch != 0) mt();
	if (pfmt_branch != 0) pfmt();
	if (q3_branch != 0) q3();
	if (els_exp_innerlayers_branch != 0) els_exp_innerlayers();
	if (mcid_branch != 0) mcid();
	if (mcmotherid_branch != 0) mcmotherid();
	if (d0PV_wwV1_branch != 0) d0PV_wwV1();
	if (dzPV_wwV1_branch != 0) dzPV_wwV1();
	if (ht_calo_branch != 0) ht_calo();
	if (ht_calo_L2L3_branch != 0) ht_calo_L2L3();
	if (ht_jpt_L2L3_branch != 0) ht_jpt_L2L3();
	if (ht_pf_branch != 0) ht_pf();
	if (ht_pf_L2L3_branch != 0) ht_pf_L2L3();
	if (ht_pf_L1FastL2L3_branch != 0) ht_pf_L1FastL2L3();
	if (mc3id_branch != 0) mc3id();
	if (mc3pt_branch != 0) mc3pt();
	if (mc3dr_branch != 0) mc3dr();
	if (leptonIsFromW_branch != 0) leptonIsFromW();
	if (el_lh_branch != 0) el_lh();
	if (el_mva_branch != 0) el_mva();
	if (mu_isCosmic_branch != 0) mu_isCosmic();
	if (mz_fo_gsf_branch != 0) mz_fo_gsf();
	if (mz_gsf_iso_branch != 0) mz_gsf_iso();
	if (mz_fo_ctf_branch != 0) mz_fo_ctf();
	if (mz_ctf_iso_branch != 0) mz_ctf_iso();
	if (mupsilon_fo_mu_branch != 0) mupsilon_fo_mu();
	if (mupsilon_mu_iso_branch != 0) mupsilon_mu_iso();
	if (num_el_ssV3_branch != 0) num_el_ssV3();
	if (v1_el_ssV3_branch != 0) v1_el_ssV3();
	if (v2_el_ssV3_branch != 0) v2_el_ssV3();
	if (v3_el_ssV3_branch != 0) v3_el_ssV3();
	if (num_el_ssV4_branch != 0) num_el_ssV4();
	if (v1_el_ssV4_branch != 0) v1_el_ssV4();
	if (v2_el_ssV4_branch != 0) v2_el_ssV4();
	if (v3_el_ssV4_branch != 0) v3_el_ssV4();
	if (num_el_ssV5_branch != 0) num_el_ssV5();
	if (v1_el_ssV5_branch != 0) v1_el_ssV5();
	if (v2_el_ssV5_branch != 0) v2_el_ssV5();
	if (v3_el_ssV5_branch != 0) v3_el_ssV5();
	if (num_el_ssV5_noIso_branch != 0) num_el_ssV5_noIso();
	if (num_el_ssV6_branch != 0) num_el_ssV6();
	if (v1_el_ssV6_branch != 0) v1_el_ssV6();
	if (v2_el_ssV6_branch != 0) v2_el_ssV6();
	if (v3_el_ssV6_branch != 0) v3_el_ssV6();
	if (num_el_ssV6_noIso_branch != 0) num_el_ssV6_noIso();
	if (numNomSSv3_branch != 0) numNomSSv3();
	if (fo_mussV3_04_branch != 0) fo_mussV3_04();
	if (numNomSSv4_branch != 0) numNomSSv4();
	if (fo_mussV4_04_branch != 0) fo_mussV4_04();
	if (numNomSSv4noIso_branch != 0) numNomSSv4noIso();
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
	if (numOct6_branch != 0) numOct6();
	if (v1Oct6_branch != 0) v1Oct6();
	if (v2Oct6_branch != 0) v2Oct6();
	if (v3Oct6_branch != 0) v3Oct6();
	if (num_branch != 0) num();
	if (fo_04_branch != 0) fo_04();
	if (fo_10_branch != 0) fo_10();
	if (v1SSV2_branch != 0) v1SSV2();
	if (v2SSV2_branch != 0) v2SSV2();
	if (v3SSV2_branch != 0) v3SSV2();
	if (numSSV2_branch != 0) numSSV2();
	if (numNomSSv2_branch != 0) numNomSSv2();
	if (fo_mussV2_04_branch != 0) fo_mussV2_04();
	if (fo_mussV2_10_branch != 0) fo_mussV2_10();
	if (num_OSGv1_branch != 0) num_OSGv1();
	if (num_OSZv1_branch != 0) num_OSZv1();
	if (numOSOct18_branch != 0) numOSOct18();
	if (v1OSOct18_branch != 0) v1OSOct18();
	if (v2OSOct18_branch != 0) v2OSOct18();
	if (v3OSOct18_branch != 0) v3OSOct18();
	if (num_wwV1_branch != 0) num_wwV1();
	if (v1_wwV1_branch != 0) v1_wwV1();
	if (v2_wwV1_branch != 0) v2_wwV1();
	if (v3_wwV1_branch != 0) v3_wwV1();
	if (v4_wwV1_branch != 0) v4_wwV1();
	if (fo_wwV1_04_branch != 0) fo_wwV1_04();
	if (fo_wwV1_10_branch != 0) fo_wwV1_10();
	if (fo_wwV1_10_d0_branch != 0) fo_wwV1_10_d0();
	if (ele8_vstar_branch != 0) ele8_vstar();
	if (ele8_CaloIdL_TrkIdVL_vstar_branch != 0) ele8_CaloIdL_TrkIdVL_vstar();
	if (ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch != 0) ele8_CaloIdL_CaloIsoVL_Jet40_vstar();
	if (ele8_CaloIdL_CaloIsoVL_vstar_branch != 0) ele8_CaloIdL_CaloIsoVL_vstar();
	if (ele17_CaloIdL_CaloIsoVL_vstar_branch != 0) ele17_CaloIdL_CaloIsoVL_vstar();
	if (ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch != 0) ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar();
	if (ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch != 0) ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar();
	if (photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch != 0) photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar();
	if (ele8_version_branch != 0) ele8_version();
	if (ele8_CaloIdL_TrkIdVL_version_branch != 0) ele8_CaloIdL_TrkIdVL_version();
	if (ele8_CaloIdL_CaloIsoVL_Jet40_version_branch != 0) ele8_CaloIdL_CaloIsoVL_Jet40_version();
	if (ele8_CaloIdL_CaloIsoVL_version_branch != 0) ele8_CaloIdL_CaloIsoVL_version();
	if (ele17_CaloIdL_CaloIsoVL_version_branch != 0) ele17_CaloIdL_CaloIsoVL_version();
	if (ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_branch != 0) ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version();
	if (ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_branch != 0) ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version();
	if (photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_branch != 0) photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version();
	if (dr_ele8_vstar_branch != 0) dr_ele8_vstar();
	if (dr_ele8_CaloIdL_TrkIdVL_vstar_branch != 0) dr_ele8_CaloIdL_TrkIdVL_vstar();
	if (dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar_branch != 0) dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar();
	if (dr_ele8_CaloIdL_CaloIsoVL_vstar_branch != 0) dr_ele8_CaloIdL_CaloIsoVL_vstar();
	if (dr_ele17_CaloIdL_CaloIsoVL_vstar_branch != 0) dr_ele17_CaloIdL_CaloIsoVL_vstar();
	if (dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch != 0) dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar();
	if (dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch != 0) dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar();
	if (dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch != 0) dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar();
	if (mu3_vstar_branch != 0) mu3_vstar();
	if (mu5_vstar_branch != 0) mu5_vstar();
	if (mu8_vstar_branch != 0) mu8_vstar();
	if (mu12_vstar_branch != 0) mu12_vstar();
	if (mu15_vstar_branch != 0) mu15_vstar();
	if (mu20_vstar_branch != 0) mu20_vstar();
	if (mu24_vstar_branch != 0) mu24_vstar();
	if (mu30_vstar_branch != 0) mu30_vstar();
	if (mu8_Jet40_vstar_branch != 0) mu8_Jet40_vstar();
	if (mu3_version_branch != 0) mu3_version();
	if (mu5_version_branch != 0) mu5_version();
	if (mu8_version_branch != 0) mu8_version();
	if (mu12_version_branch != 0) mu12_version();
	if (mu15_version_branch != 0) mu15_version();
	if (mu20_version_branch != 0) mu20_version();
	if (mu24_version_branch != 0) mu24_version();
	if (mu30_version_branch != 0) mu30_version();
	if (mu8_Jet40_version_branch != 0) mu8_Jet40_version();
	if (dr_mu3_vstar_branch != 0) dr_mu3_vstar();
	if (dr_mu5_vstar_branch != 0) dr_mu5_vstar();
	if (dr_mu8_vstar_branch != 0) dr_mu8_vstar();
	if (dr_mu12_vstar_branch != 0) dr_mu12_vstar();
	if (dr_mu15_vstar_branch != 0) dr_mu15_vstar();
	if (dr_mu20_vstar_branch != 0) dr_mu20_vstar();
	if (dr_mu24_vstar_branch != 0) dr_mu24_vstar();
	if (dr_mu30_vstar_branch != 0) dr_mu30_vstar();
	if (dr_mu8_Jet40_vstar_branch != 0) dr_mu8_Jet40_vstar();
	if (hlt15u_branch != 0) hlt15u();
	if (hlt30u_branch != 0) hlt30u();
	if (hlt50u_branch != 0) hlt50u();
	if (l16u_branch != 0) l16u();
	if (l110_branch != 0) l110();
	if (ph10_branch != 0) ph10();
	if (ph15_branch != 0) ph15();
	if (ph20_branch != 0) ph20();
	if (el10_lw_branch != 0) el10_lw();
	if (el10_sw_branch != 0) el10_sw();
	if (el10_sw_v2_branch != 0) el10_sw_v2();
	if (el10_lw_id_branch != 0) el10_lw_id();
	if (el10_sw_id_branch != 0) el10_sw_id();
	if (el15_lw_branch != 0) el15_lw();
	if (el15_sw_branch != 0) el15_sw();
	if (el15_lw_id_branch != 0) el15_lw_id();
	if (el15_sw_id_branch != 0) el15_sw_id();
	if (el15_sw_cid_branch != 0) el15_sw_cid();
	if (el20_sw_branch != 0) el20_sw();
	if (el25_sw_branch != 0) el25_sw();
	if (Del10_sw_branch != 0) Del10_sw();
	if (el17_sw_branch != 0) el17_sw();
	if (el17_sw_v2_branch != 0) el17_sw_v2();
	if (el17_iso_branch != 0) el17_iso();
	if (el17_loose_branch != 0) el17_loose();
	if (el17_sw_cid_branch != 0) el17_sw_cid();
	if (el17_sw_id_branch != 0) el17_sw_id();
	if (el17_tiso_branch != 0) el17_tiso();
	if (el17_tiso_v1_branch != 0) el17_tiso_v1();
	if (drph10_branch != 0) drph10();
	if (drph15_branch != 0) drph15();
	if (drph20_branch != 0) drph20();
	if (drel10_lw_branch != 0) drel10_lw();
	if (drel10_sw_branch != 0) drel10_sw();
	if (drel10_sw_v2_branch != 0) drel10_sw_v2();
	if (drel10_lw_id_branch != 0) drel10_lw_id();
	if (drel10_sw_id_branch != 0) drel10_sw_id();
	if (drel15_lw_branch != 0) drel15_lw();
	if (drel15_sw_branch != 0) drel15_sw();
	if (drel15_lw_id_branch != 0) drel15_lw_id();
	if (drel15_sw_id_branch != 0) drel15_sw_id();
	if (drel15_sw_cid_branch != 0) drel15_sw_cid();
	if (drel20_sw_branch != 0) drel20_sw();
	if (drel25_sw_branch != 0) drel25_sw();
	if (drDel10_sw_branch != 0) drDel10_sw();
	if (drel17_sw_branch != 0) drel17_sw();
	if (drel17_sw_v2_branch != 0) drel17_sw_v2();
	if (drel17_iso_branch != 0) drel17_iso();
	if (drel17_loose_branch != 0) drel17_loose();
	if (drel17_sw_cid_branch != 0) drel17_sw_cid();
	if (drel17_sw_id_branch != 0) drel17_sw_id();
	if (drel17_tiso_branch != 0) drel17_tiso();
	if (drel17_tiso_v1_branch != 0) drel17_tiso_v1();
	if (mu17_branch != 0) mu17();
	if (mu15_branch != 0) mu15();
	if (mu13_branch != 0) mu13();
	if (mu11_branch != 0) mu11();
	if (mu9_branch != 0) mu9();
	if (mu7_branch != 0) mu7();
	if (mu5_branch != 0) mu5();
	if (drmu17_branch != 0) drmu17();
	if (drmu15_branch != 0) drmu15();
	if (drmu13_branch != 0) drmu13();
	if (drmu11_branch != 0) drmu11();
	if (drmu9_branch != 0) drmu9();
	if (drmu7_branch != 0) drmu7();
	if (drmu5_branch != 0) drmu5();
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
	if (ptbtagpfcL1Fj1_branch != 0) ptbtagpfcL1Fj1();
	if (dphibtagpfcL1Fj1_branch != 0) dphibtagpfcL1Fj1();
	if (ptjptcj1_branch != 0) ptjptcj1();
	if (njptcj1_branch != 0) njptcj1();
	if (ptjptcj1_b2b_branch != 0) ptjptcj1_b2b();
	if (dphijptcj1_b2b_branch != 0) dphijptcj1_b2b();
	if (btagjptc_branch != 0) btagjptc();
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
	float &weight()
	{
		if (not weight_isLoaded) {
			if (weight_branch != 0) {
				weight_branch->GetEntry(index);
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
			} else { 
				printf("branch evt_nvtxs_branch does not exist!\n");
				exit(1);
			}
			evt_nvtxs_isLoaded = true;
		}
		return evt_nvtxs_;
	}
	int &evt_ndavtxs()
	{
		if (not evt_ndavtxs_isLoaded) {
			if (evt_ndavtxs_branch != 0) {
				evt_ndavtxs_branch->GetEntry(index);
			} else { 
				printf("branch evt_ndavtxs_branch does not exist!\n");
				exit(1);
			}
			evt_ndavtxs_isLoaded = true;
		}
		return evt_ndavtxs_;
	}
	int &nFOels()
	{
		if (not nFOels_isLoaded) {
			if (nFOels_branch != 0) {
				nFOels_branch->GetEntry(index);
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
			} else { 
				printf("branch pt_branch does not exist!\n");
				exit(1);
			}
			pt_isLoaded = true;
		}
		return pt_;
	}
	LorentzVector &lp4()
	{
		if (not lp4_isLoaded) {
			if (lp4_branch != 0) {
				lp4_branch->GetEntry(index);
			} else { 
				printf("branch lp4_branch does not exist!\n");
				exit(1);
			}
			lp4_isLoaded = true;
		}
		return lp4_;
	}
	float &eta()
	{
		if (not eta_isLoaded) {
			if (eta_branch != 0) {
				eta_branch->GetEntry(index);
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
			} else { 
				printf("branch hoe_branch does not exist!\n");
				exit(1);
			}
			hoe_isLoaded = true;
		}
		return hoe_;
	}
	float &tcmet()
	{
		if (not tcmet_isLoaded) {
			if (tcmet_branch != 0) {
				tcmet_branch->GetEntry(index);
			} else { 
				printf("branch tcmet_branch does not exist!\n");
				exit(1);
			}
			tcmet_isLoaded = true;
		}
		return tcmet_;
	}
	float &tcmetphi()
	{
		if (not tcmetphi_isLoaded) {
			if (tcmetphi_branch != 0) {
				tcmetphi_branch->GetEntry(index);
			} else { 
				printf("branch tcmetphi_branch does not exist!\n");
				exit(1);
			}
			tcmetphi_isLoaded = true;
		}
		return tcmetphi_;
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
	float &pfmetphi()
	{
		if (not pfmetphi_isLoaded) {
			if (pfmetphi_branch != 0) {
				pfmetphi_branch->GetEntry(index);
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
			} else { 
				printf("branch iso_nps_branch does not exist!\n");
				exit(1);
			}
			iso_nps_isLoaded = true;
		}
		return iso_nps_;
	}
	float &nt_iso()
	{
		if (not nt_iso_isLoaded) {
			if (nt_iso_branch != 0) {
				nt_iso_branch->GetEntry(index);
			} else { 
				printf("branch nt_iso_branch does not exist!\n");
				exit(1);
			}
			nt_iso_isLoaded = true;
		}
		return nt_iso_;
	}
	float &nt_iso_nps()
	{
		if (not nt_iso_nps_isLoaded) {
			if (nt_iso_nps_branch != 0) {
				nt_iso_nps_branch->GetEntry(index);
			} else { 
				printf("branch nt_iso_nps_branch does not exist!\n");
				exit(1);
			}
			nt_iso_nps_isLoaded = true;
		}
		return nt_iso_nps_;
	}
	float &trck_iso()
	{
		if (not trck_iso_isLoaded) {
			if (trck_iso_branch != 0) {
				trck_iso_branch->GetEntry(index);
			} else { 
				printf("branch trck_iso_branch does not exist!\n");
				exit(1);
			}
			trck_iso_isLoaded = true;
		}
		return trck_iso_;
	}
	float &trck_nt_iso()
	{
		if (not trck_nt_iso_isLoaded) {
			if (trck_nt_iso_branch != 0) {
				trck_nt_iso_branch->GetEntry(index);
			} else { 
				printf("branch trck_nt_iso_branch does not exist!\n");
				exit(1);
			}
			trck_nt_iso_isLoaded = true;
		}
		return trck_nt_iso_;
	}
	float &ecal_iso()
	{
		if (not ecal_iso_isLoaded) {
			if (ecal_iso_branch != 0) {
				ecal_iso_branch->GetEntry(index);
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
			} else { 
				printf("branch ecal_iso_nps_branch does not exist!\n");
				exit(1);
			}
			ecal_iso_nps_isLoaded = true;
		}
		return ecal_iso_nps_;
	}
	float &ecal_nt_iso()
	{
		if (not ecal_nt_iso_isLoaded) {
			if (ecal_nt_iso_branch != 0) {
				ecal_nt_iso_branch->GetEntry(index);
			} else { 
				printf("branch ecal_nt_iso_branch does not exist!\n");
				exit(1);
			}
			ecal_nt_iso_isLoaded = true;
		}
		return ecal_nt_iso_;
	}
	float &ecal_nt_iso_nps()
	{
		if (not ecal_nt_iso_nps_isLoaded) {
			if (ecal_nt_iso_nps_branch != 0) {
				ecal_nt_iso_nps_branch->GetEntry(index);
			} else { 
				printf("branch ecal_nt_iso_nps_branch does not exist!\n");
				exit(1);
			}
			ecal_nt_iso_nps_isLoaded = true;
		}
		return ecal_nt_iso_nps_;
	}
	float &hcal_iso()
	{
		if (not hcal_iso_isLoaded) {
			if (hcal_iso_branch != 0) {
				hcal_iso_branch->GetEntry(index);
			} else { 
				printf("branch hcal_iso_branch does not exist!\n");
				exit(1);
			}
			hcal_iso_isLoaded = true;
		}
		return hcal_iso_;
	}
	float &hcal_nt_iso()
	{
		if (not hcal_nt_iso_isLoaded) {
			if (hcal_nt_iso_branch != 0) {
				hcal_nt_iso_branch->GetEntry(index);
			} else { 
				printf("branch hcal_nt_iso_branch does not exist!\n");
				exit(1);
			}
			hcal_nt_iso_isLoaded = true;
		}
		return hcal_nt_iso_;
	}
	float &nt_pfiso03()
	{
		if (not nt_pfiso03_isLoaded) {
			if (nt_pfiso03_branch != 0) {
				nt_pfiso03_branch->GetEntry(index);
			} else { 
				printf("branch nt_pfiso03_branch does not exist!\n");
				exit(1);
			}
			nt_pfiso03_isLoaded = true;
		}
		return nt_pfiso03_;
	}
	float &nt_pfiso04()
	{
		if (not nt_pfiso04_isLoaded) {
			if (nt_pfiso04_branch != 0) {
				nt_pfiso04_branch->GetEntry(index);
			} else { 
				printf("branch nt_pfiso04_branch does not exist!\n");
				exit(1);
			}
			nt_pfiso04_isLoaded = true;
		}
		return nt_pfiso04_;
	}
	int &id()
	{
		if (not id_isLoaded) {
			if (id_branch != 0) {
				id_branch->GetEntry(index);
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
			} else { 
				printf("branch closestMuon_branch does not exist!\n");
				exit(1);
			}
			closestMuon_isLoaded = true;
		}
		return closestMuon_;
	}
	bool &	el_id_smurfV5()
	{
		if (not el_id_smurfV5_isLoaded) {
			if (el_id_smurfV5_branch != 0) {
				el_id_smurfV5_branch->GetEntry(index);
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
			} else { 
				printf("branch el_id_vbtf90_branch does not exist!\n");
				exit(1);
			}
			el_id_vbtf90_isLoaded = true;
		}
		return el_id_vbtf90_;
	}
	bool &	conv0MissHits()
	{
		if (not conv0MissHits_isLoaded) {
			if (conv0MissHits_branch != 0) {
				conv0MissHits_branch->GetEntry(index);
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
			} else { 
				printf("branch els_exp_innerlayers_branch does not exist!\n");
				exit(1);
			}
			els_exp_innerlayers_isLoaded = true;
		}
		return els_exp_innerlayers_;
	}
	int &mcid()
	{
		if (not mcid_isLoaded) {
			if (mcid_branch != 0) {
				mcid_branch->GetEntry(index);
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
			} else { 
				printf("branch mcmotherid_branch does not exist!\n");
				exit(1);
			}
			mcmotherid_isLoaded = true;
		}
		return mcmotherid_;
	}
	float &d0PV_wwV1()
	{
		if (not d0PV_wwV1_isLoaded) {
			if (d0PV_wwV1_branch != 0) {
				d0PV_wwV1_branch->GetEntry(index);
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
			} else { 
				printf("branch ht_calo_L2L3_branch does not exist!\n");
				exit(1);
			}
			ht_calo_L2L3_isLoaded = true;
		}
		return ht_calo_L2L3_;
	}
	float &ht_jpt_L2L3()
	{
		if (not ht_jpt_L2L3_isLoaded) {
			if (ht_jpt_L2L3_branch != 0) {
				ht_jpt_L2L3_branch->GetEntry(index);
			} else { 
				printf("branch ht_jpt_L2L3_branch does not exist!\n");
				exit(1);
			}
			ht_jpt_L2L3_isLoaded = true;
		}
		return ht_jpt_L2L3_;
	}
	float &ht_pf()
	{
		if (not ht_pf_isLoaded) {
			if (ht_pf_branch != 0) {
				ht_pf_branch->GetEntry(index);
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
			} else { 
				printf("branch ht_pf_L1FastL2L3_branch does not exist!\n");
				exit(1);
			}
			ht_pf_L1FastL2L3_isLoaded = true;
		}
		return ht_pf_L1FastL2L3_;
	}
	int &mc3id()
	{
		if (not mc3id_isLoaded) {
			if (mc3id_branch != 0) {
				mc3id_branch->GetEntry(index);
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
			} else { 
				printf("branch leptonIsFromW_branch does not exist!\n");
				exit(1);
			}
			leptonIsFromW_isLoaded = true;
		}
		return leptonIsFromW_;
	}
	float &el_lh()
	{
		if (not el_lh_isLoaded) {
			if (el_lh_branch != 0) {
				el_lh_branch->GetEntry(index);
			} else { 
				printf("branch el_lh_branch does not exist!\n");
				exit(1);
			}
			el_lh_isLoaded = true;
		}
		return el_lh_;
	}
	float &el_mva()
	{
		if (not el_mva_isLoaded) {
			if (el_mva_branch != 0) {
				el_mva_branch->GetEntry(index);
			} else { 
				printf("branch el_mva_branch does not exist!\n");
				exit(1);
			}
			el_mva_isLoaded = true;
		}
		return el_mva_;
	}
	bool &	mu_isCosmic()
	{
		if (not mu_isCosmic_isLoaded) {
			if (mu_isCosmic_branch != 0) {
				mu_isCosmic_branch->GetEntry(index);
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
			} else { 
				printf("branch mupsilon_mu_iso_branch does not exist!\n");
				exit(1);
			}
			mupsilon_mu_iso_isLoaded = true;
		}
		return mupsilon_mu_iso_;
	}
	bool &	num_el_ssV3()
	{
		if (not num_el_ssV3_isLoaded) {
			if (num_el_ssV3_branch != 0) {
				num_el_ssV3_branch->GetEntry(index);
			} else { 
				printf("branch num_el_ssV3_branch does not exist!\n");
				exit(1);
			}
			num_el_ssV3_isLoaded = true;
		}
		return num_el_ssV3_;
	}
	bool &	v1_el_ssV3()
	{
		if (not v1_el_ssV3_isLoaded) {
			if (v1_el_ssV3_branch != 0) {
				v1_el_ssV3_branch->GetEntry(index);
			} else { 
				printf("branch v1_el_ssV3_branch does not exist!\n");
				exit(1);
			}
			v1_el_ssV3_isLoaded = true;
		}
		return v1_el_ssV3_;
	}
	bool &	v2_el_ssV3()
	{
		if (not v2_el_ssV3_isLoaded) {
			if (v2_el_ssV3_branch != 0) {
				v2_el_ssV3_branch->GetEntry(index);
			} else { 
				printf("branch v2_el_ssV3_branch does not exist!\n");
				exit(1);
			}
			v2_el_ssV3_isLoaded = true;
		}
		return v2_el_ssV3_;
	}
	bool &	v3_el_ssV3()
	{
		if (not v3_el_ssV3_isLoaded) {
			if (v3_el_ssV3_branch != 0) {
				v3_el_ssV3_branch->GetEntry(index);
			} else { 
				printf("branch v3_el_ssV3_branch does not exist!\n");
				exit(1);
			}
			v3_el_ssV3_isLoaded = true;
		}
		return v3_el_ssV3_;
	}
	bool &	num_el_ssV4()
	{
		if (not num_el_ssV4_isLoaded) {
			if (num_el_ssV4_branch != 0) {
				num_el_ssV4_branch->GetEntry(index);
			} else { 
				printf("branch num_el_ssV4_branch does not exist!\n");
				exit(1);
			}
			num_el_ssV4_isLoaded = true;
		}
		return num_el_ssV4_;
	}
	bool &	v1_el_ssV4()
	{
		if (not v1_el_ssV4_isLoaded) {
			if (v1_el_ssV4_branch != 0) {
				v1_el_ssV4_branch->GetEntry(index);
			} else { 
				printf("branch v1_el_ssV4_branch does not exist!\n");
				exit(1);
			}
			v1_el_ssV4_isLoaded = true;
		}
		return v1_el_ssV4_;
	}
	bool &	v2_el_ssV4()
	{
		if (not v2_el_ssV4_isLoaded) {
			if (v2_el_ssV4_branch != 0) {
				v2_el_ssV4_branch->GetEntry(index);
			} else { 
				printf("branch v2_el_ssV4_branch does not exist!\n");
				exit(1);
			}
			v2_el_ssV4_isLoaded = true;
		}
		return v2_el_ssV4_;
	}
	bool &	v3_el_ssV4()
	{
		if (not v3_el_ssV4_isLoaded) {
			if (v3_el_ssV4_branch != 0) {
				v3_el_ssV4_branch->GetEntry(index);
			} else { 
				printf("branch v3_el_ssV4_branch does not exist!\n");
				exit(1);
			}
			v3_el_ssV4_isLoaded = true;
		}
		return v3_el_ssV4_;
	}
	bool &	num_el_ssV5()
	{
		if (not num_el_ssV5_isLoaded) {
			if (num_el_ssV5_branch != 0) {
				num_el_ssV5_branch->GetEntry(index);
			} else { 
				printf("branch num_el_ssV5_branch does not exist!\n");
				exit(1);
			}
			num_el_ssV5_isLoaded = true;
		}
		return num_el_ssV5_;
	}
	bool &	v1_el_ssV5()
	{
		if (not v1_el_ssV5_isLoaded) {
			if (v1_el_ssV5_branch != 0) {
				v1_el_ssV5_branch->GetEntry(index);
			} else { 
				printf("branch v1_el_ssV5_branch does not exist!\n");
				exit(1);
			}
			v1_el_ssV5_isLoaded = true;
		}
		return v1_el_ssV5_;
	}
	bool &	v2_el_ssV5()
	{
		if (not v2_el_ssV5_isLoaded) {
			if (v2_el_ssV5_branch != 0) {
				v2_el_ssV5_branch->GetEntry(index);
			} else { 
				printf("branch v2_el_ssV5_branch does not exist!\n");
				exit(1);
			}
			v2_el_ssV5_isLoaded = true;
		}
		return v2_el_ssV5_;
	}
	bool &	v3_el_ssV5()
	{
		if (not v3_el_ssV5_isLoaded) {
			if (v3_el_ssV5_branch != 0) {
				v3_el_ssV5_branch->GetEntry(index);
			} else { 
				printf("branch v3_el_ssV5_branch does not exist!\n");
				exit(1);
			}
			v3_el_ssV5_isLoaded = true;
		}
		return v3_el_ssV5_;
	}
	bool &	num_el_ssV5_noIso()
	{
		if (not num_el_ssV5_noIso_isLoaded) {
			if (num_el_ssV5_noIso_branch != 0) {
				num_el_ssV5_noIso_branch->GetEntry(index);
			} else { 
				printf("branch num_el_ssV5_noIso_branch does not exist!\n");
				exit(1);
			}
			num_el_ssV5_noIso_isLoaded = true;
		}
		return num_el_ssV5_noIso_;
	}
	bool &	num_el_ssV6()
	{
		if (not num_el_ssV6_isLoaded) {
			if (num_el_ssV6_branch != 0) {
				num_el_ssV6_branch->GetEntry(index);
			} else { 
				printf("branch num_el_ssV6_branch does not exist!\n");
				exit(1);
			}
			num_el_ssV6_isLoaded = true;
		}
		return num_el_ssV6_;
	}
	bool &	v1_el_ssV6()
	{
		if (not v1_el_ssV6_isLoaded) {
			if (v1_el_ssV6_branch != 0) {
				v1_el_ssV6_branch->GetEntry(index);
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
			} else { 
				printf("branch v3_el_ssV6_branch does not exist!\n");
				exit(1);
			}
			v3_el_ssV6_isLoaded = true;
		}
		return v3_el_ssV6_;
	}
	bool &	num_el_ssV6_noIso()
	{
		if (not num_el_ssV6_noIso_isLoaded) {
			if (num_el_ssV6_noIso_branch != 0) {
				num_el_ssV6_noIso_branch->GetEntry(index);
			} else { 
				printf("branch num_el_ssV6_noIso_branch does not exist!\n");
				exit(1);
			}
			num_el_ssV6_noIso_isLoaded = true;
		}
		return num_el_ssV6_noIso_;
	}
	bool &	numNomSSv3()
	{
		if (not numNomSSv3_isLoaded) {
			if (numNomSSv3_branch != 0) {
				numNomSSv3_branch->GetEntry(index);
			} else { 
				printf("branch numNomSSv3_branch does not exist!\n");
				exit(1);
			}
			numNomSSv3_isLoaded = true;
		}
		return numNomSSv3_;
	}
	bool &	fo_mussV3_04()
	{
		if (not fo_mussV3_04_isLoaded) {
			if (fo_mussV3_04_branch != 0) {
				fo_mussV3_04_branch->GetEntry(index);
			} else { 
				printf("branch fo_mussV3_04_branch does not exist!\n");
				exit(1);
			}
			fo_mussV3_04_isLoaded = true;
		}
		return fo_mussV3_04_;
	}
	bool &	numNomSSv4()
	{
		if (not numNomSSv4_isLoaded) {
			if (numNomSSv4_branch != 0) {
				numNomSSv4_branch->GetEntry(index);
			} else { 
				printf("branch numNomSSv4_branch does not exist!\n");
				exit(1);
			}
			numNomSSv4_isLoaded = true;
		}
		return numNomSSv4_;
	}
	bool &	fo_mussV4_04()
	{
		if (not fo_mussV4_04_isLoaded) {
			if (fo_mussV4_04_branch != 0) {
				fo_mussV4_04_branch->GetEntry(index);
			} else { 
				printf("branch fo_mussV4_04_branch does not exist!\n");
				exit(1);
			}
			fo_mussV4_04_isLoaded = true;
		}
		return fo_mussV4_04_;
	}
	bool &	numNomSSv4noIso()
	{
		if (not numNomSSv4noIso_isLoaded) {
			if (numNomSSv4noIso_branch != 0) {
				numNomSSv4noIso_branch->GetEntry(index);
			} else { 
				printf("branch numNomSSv4noIso_branch does not exist!\n");
				exit(1);
			}
			numNomSSv4noIso_isLoaded = true;
		}
		return numNomSSv4noIso_;
	}
	bool &	fo_mussV4_noIso()
	{
		if (not fo_mussV4_noIso_isLoaded) {
			if (fo_mussV4_noIso_branch != 0) {
				fo_mussV4_noIso_branch->GetEntry(index);
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
			} else { 
				printf("branch fo_mu_OSGV3_branch does not exist!\n");
				exit(1);
			}
			fo_mu_OSGV3_isLoaded = true;
		}
		return fo_mu_OSGV3_;
	}
	bool &	numOct6()
	{
		if (not numOct6_isLoaded) {
			if (numOct6_branch != 0) {
				numOct6_branch->GetEntry(index);
			} else { 
				printf("branch numOct6_branch does not exist!\n");
				exit(1);
			}
			numOct6_isLoaded = true;
		}
		return numOct6_;
	}
	bool &	v1Oct6()
	{
		if (not v1Oct6_isLoaded) {
			if (v1Oct6_branch != 0) {
				v1Oct6_branch->GetEntry(index);
			} else { 
				printf("branch v1Oct6_branch does not exist!\n");
				exit(1);
			}
			v1Oct6_isLoaded = true;
		}
		return v1Oct6_;
	}
	bool &	v2Oct6()
	{
		if (not v2Oct6_isLoaded) {
			if (v2Oct6_branch != 0) {
				v2Oct6_branch->GetEntry(index);
			} else { 
				printf("branch v2Oct6_branch does not exist!\n");
				exit(1);
			}
			v2Oct6_isLoaded = true;
		}
		return v2Oct6_;
	}
	bool &	v3Oct6()
	{
		if (not v3Oct6_isLoaded) {
			if (v3Oct6_branch != 0) {
				v3Oct6_branch->GetEntry(index);
			} else { 
				printf("branch v3Oct6_branch does not exist!\n");
				exit(1);
			}
			v3Oct6_isLoaded = true;
		}
		return v3Oct6_;
	}
	bool &	num()
	{
		if (not num_isLoaded) {
			if (num_branch != 0) {
				num_branch->GetEntry(index);
			} else { 
				printf("branch num_branch does not exist!\n");
				exit(1);
			}
			num_isLoaded = true;
		}
		return num_;
	}
	bool &	fo_04()
	{
		if (not fo_04_isLoaded) {
			if (fo_04_branch != 0) {
				fo_04_branch->GetEntry(index);
			} else { 
				printf("branch fo_04_branch does not exist!\n");
				exit(1);
			}
			fo_04_isLoaded = true;
		}
		return fo_04_;
	}
	bool &	fo_10()
	{
		if (not fo_10_isLoaded) {
			if (fo_10_branch != 0) {
				fo_10_branch->GetEntry(index);
			} else { 
				printf("branch fo_10_branch does not exist!\n");
				exit(1);
			}
			fo_10_isLoaded = true;
		}
		return fo_10_;
	}
	bool &	v1SSV2()
	{
		if (not v1SSV2_isLoaded) {
			if (v1SSV2_branch != 0) {
				v1SSV2_branch->GetEntry(index);
			} else { 
				printf("branch v1SSV2_branch does not exist!\n");
				exit(1);
			}
			v1SSV2_isLoaded = true;
		}
		return v1SSV2_;
	}
	bool &	v2SSV2()
	{
		if (not v2SSV2_isLoaded) {
			if (v2SSV2_branch != 0) {
				v2SSV2_branch->GetEntry(index);
			} else { 
				printf("branch v2SSV2_branch does not exist!\n");
				exit(1);
			}
			v2SSV2_isLoaded = true;
		}
		return v2SSV2_;
	}
	bool &	v3SSV2()
	{
		if (not v3SSV2_isLoaded) {
			if (v3SSV2_branch != 0) {
				v3SSV2_branch->GetEntry(index);
			} else { 
				printf("branch v3SSV2_branch does not exist!\n");
				exit(1);
			}
			v3SSV2_isLoaded = true;
		}
		return v3SSV2_;
	}
	bool &	numSSV2()
	{
		if (not numSSV2_isLoaded) {
			if (numSSV2_branch != 0) {
				numSSV2_branch->GetEntry(index);
			} else { 
				printf("branch numSSV2_branch does not exist!\n");
				exit(1);
			}
			numSSV2_isLoaded = true;
		}
		return numSSV2_;
	}
	bool &	numNomSSv2()
	{
		if (not numNomSSv2_isLoaded) {
			if (numNomSSv2_branch != 0) {
				numNomSSv2_branch->GetEntry(index);
			} else { 
				printf("branch numNomSSv2_branch does not exist!\n");
				exit(1);
			}
			numNomSSv2_isLoaded = true;
		}
		return numNomSSv2_;
	}
	bool &	fo_mussV2_04()
	{
		if (not fo_mussV2_04_isLoaded) {
			if (fo_mussV2_04_branch != 0) {
				fo_mussV2_04_branch->GetEntry(index);
			} else { 
				printf("branch fo_mussV2_04_branch does not exist!\n");
				exit(1);
			}
			fo_mussV2_04_isLoaded = true;
		}
		return fo_mussV2_04_;
	}
	bool &	fo_mussV2_10()
	{
		if (not fo_mussV2_10_isLoaded) {
			if (fo_mussV2_10_branch != 0) {
				fo_mussV2_10_branch->GetEntry(index);
			} else { 
				printf("branch fo_mussV2_10_branch does not exist!\n");
				exit(1);
			}
			fo_mussV2_10_isLoaded = true;
		}
		return fo_mussV2_10_;
	}
	bool &	num_OSGv1()
	{
		if (not num_OSGv1_isLoaded) {
			if (num_OSGv1_branch != 0) {
				num_OSGv1_branch->GetEntry(index);
			} else { 
				printf("branch num_OSGv1_branch does not exist!\n");
				exit(1);
			}
			num_OSGv1_isLoaded = true;
		}
		return num_OSGv1_;
	}
	bool &	num_OSZv1()
	{
		if (not num_OSZv1_isLoaded) {
			if (num_OSZv1_branch != 0) {
				num_OSZv1_branch->GetEntry(index);
			} else { 
				printf("branch num_OSZv1_branch does not exist!\n");
				exit(1);
			}
			num_OSZv1_isLoaded = true;
		}
		return num_OSZv1_;
	}
	bool &	numOSOct18()
	{
		if (not numOSOct18_isLoaded) {
			if (numOSOct18_branch != 0) {
				numOSOct18_branch->GetEntry(index);
			} else { 
				printf("branch numOSOct18_branch does not exist!\n");
				exit(1);
			}
			numOSOct18_isLoaded = true;
		}
		return numOSOct18_;
	}
	bool &	v1OSOct18()
	{
		if (not v1OSOct18_isLoaded) {
			if (v1OSOct18_branch != 0) {
				v1OSOct18_branch->GetEntry(index);
			} else { 
				printf("branch v1OSOct18_branch does not exist!\n");
				exit(1);
			}
			v1OSOct18_isLoaded = true;
		}
		return v1OSOct18_;
	}
	bool &	v2OSOct18()
	{
		if (not v2OSOct18_isLoaded) {
			if (v2OSOct18_branch != 0) {
				v2OSOct18_branch->GetEntry(index);
			} else { 
				printf("branch v2OSOct18_branch does not exist!\n");
				exit(1);
			}
			v2OSOct18_isLoaded = true;
		}
		return v2OSOct18_;
	}
	bool &	v3OSOct18()
	{
		if (not v3OSOct18_isLoaded) {
			if (v3OSOct18_branch != 0) {
				v3OSOct18_branch->GetEntry(index);
			} else { 
				printf("branch v3OSOct18_branch does not exist!\n");
				exit(1);
			}
			v3OSOct18_isLoaded = true;
		}
		return v3OSOct18_;
	}
	bool &	num_wwV1()
	{
		if (not num_wwV1_isLoaded) {
			if (num_wwV1_branch != 0) {
				num_wwV1_branch->GetEntry(index);
			} else { 
				printf("branch num_wwV1_branch does not exist!\n");
				exit(1);
			}
			num_wwV1_isLoaded = true;
		}
		return num_wwV1_;
	}
	bool &	v1_wwV1()
	{
		if (not v1_wwV1_isLoaded) {
			if (v1_wwV1_branch != 0) {
				v1_wwV1_branch->GetEntry(index);
			} else { 
				printf("branch v1_wwV1_branch does not exist!\n");
				exit(1);
			}
			v1_wwV1_isLoaded = true;
		}
		return v1_wwV1_;
	}
	bool &	v2_wwV1()
	{
		if (not v2_wwV1_isLoaded) {
			if (v2_wwV1_branch != 0) {
				v2_wwV1_branch->GetEntry(index);
			} else { 
				printf("branch v2_wwV1_branch does not exist!\n");
				exit(1);
			}
			v2_wwV1_isLoaded = true;
		}
		return v2_wwV1_;
	}
	bool &	v3_wwV1()
	{
		if (not v3_wwV1_isLoaded) {
			if (v3_wwV1_branch != 0) {
				v3_wwV1_branch->GetEntry(index);
			} else { 
				printf("branch v3_wwV1_branch does not exist!\n");
				exit(1);
			}
			v3_wwV1_isLoaded = true;
		}
		return v3_wwV1_;
	}
	bool &	v4_wwV1()
	{
		if (not v4_wwV1_isLoaded) {
			if (v4_wwV1_branch != 0) {
				v4_wwV1_branch->GetEntry(index);
			} else { 
				printf("branch v4_wwV1_branch does not exist!\n");
				exit(1);
			}
			v4_wwV1_isLoaded = true;
		}
		return v4_wwV1_;
	}
	bool &	fo_wwV1_04()
	{
		if (not fo_wwV1_04_isLoaded) {
			if (fo_wwV1_04_branch != 0) {
				fo_wwV1_04_branch->GetEntry(index);
			} else { 
				printf("branch fo_wwV1_04_branch does not exist!\n");
				exit(1);
			}
			fo_wwV1_04_isLoaded = true;
		}
		return fo_wwV1_04_;
	}
	bool &	fo_wwV1_10()
	{
		if (not fo_wwV1_10_isLoaded) {
			if (fo_wwV1_10_branch != 0) {
				fo_wwV1_10_branch->GetEntry(index);
			} else { 
				printf("branch fo_wwV1_10_branch does not exist!\n");
				exit(1);
			}
			fo_wwV1_10_isLoaded = true;
		}
		return fo_wwV1_10_;
	}
	bool &	fo_wwV1_10_d0()
	{
		if (not fo_wwV1_10_d0_isLoaded) {
			if (fo_wwV1_10_d0_branch != 0) {
				fo_wwV1_10_d0_branch->GetEntry(index);
			} else { 
				printf("branch fo_wwV1_10_d0_branch does not exist!\n");
				exit(1);
			}
			fo_wwV1_10_d0_isLoaded = true;
		}
		return fo_wwV1_10_d0_;
	}
	int &ele8_vstar()
	{
		if (not ele8_vstar_isLoaded) {
			if (ele8_vstar_branch != 0) {
				ele8_vstar_branch->GetEntry(index);
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
			} else { 
				printf("branch ele8_CaloIdL_CaloIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			ele8_CaloIdL_CaloIsoVL_vstar_isLoaded = true;
		}
		return ele8_CaloIdL_CaloIsoVL_vstar_;
	}
	int &ele17_CaloIdL_CaloIsoVL_vstar()
	{
		if (not ele17_CaloIdL_CaloIsoVL_vstar_isLoaded) {
			if (ele17_CaloIdL_CaloIsoVL_vstar_branch != 0) {
				ele17_CaloIdL_CaloIsoVL_vstar_branch->GetEntry(index);
			} else { 
				printf("branch ele17_CaloIdL_CaloIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			ele17_CaloIdL_CaloIsoVL_vstar_isLoaded = true;
		}
		return ele17_CaloIdL_CaloIsoVL_vstar_;
	}
	int &ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar()
	{
		if (not ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_isLoaded) {
			if (ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch != 0) {
				ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch->GetEntry(index);
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
			} else { 
				printf("branch ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded = true;
		}
		return ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_;
	}
	int &photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar()
	{
		if (not photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_isLoaded) {
			if (photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch != 0) {
				photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch->GetEntry(index);
			} else { 
				printf("branch photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_isLoaded = true;
		}
		return photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_;
	}
	int &ele8_version()
	{
		if (not ele8_version_isLoaded) {
			if (ele8_version_branch != 0) {
				ele8_version_branch->GetEntry(index);
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
			} else { 
				printf("branch ele8_CaloIdL_CaloIsoVL_version_branch does not exist!\n");
				exit(1);
			}
			ele8_CaloIdL_CaloIsoVL_version_isLoaded = true;
		}
		return ele8_CaloIdL_CaloIsoVL_version_;
	}
	int &ele17_CaloIdL_CaloIsoVL_version()
	{
		if (not ele17_CaloIdL_CaloIsoVL_version_isLoaded) {
			if (ele17_CaloIdL_CaloIsoVL_version_branch != 0) {
				ele17_CaloIdL_CaloIsoVL_version_branch->GetEntry(index);
			} else { 
				printf("branch ele17_CaloIdL_CaloIsoVL_version_branch does not exist!\n");
				exit(1);
			}
			ele17_CaloIdL_CaloIsoVL_version_isLoaded = true;
		}
		return ele17_CaloIdL_CaloIsoVL_version_;
	}
	int &ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version()
	{
		if (not ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_isLoaded) {
			if (ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_branch != 0) {
				ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version_branch->GetEntry(index);
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
			} else { 
				printf("branch ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_branch does not exist!\n");
				exit(1);
			}
			ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_isLoaded = true;
		}
		return ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version_;
	}
	int &photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version()
	{
		if (not photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_isLoaded) {
			if (photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_branch != 0) {
				photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_branch->GetEntry(index);
			} else { 
				printf("branch photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_branch does not exist!\n");
				exit(1);
			}
			photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_isLoaded = true;
		}
		return photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version_;
	}
	float &dr_ele8_vstar()
	{
		if (not dr_ele8_vstar_isLoaded) {
			if (dr_ele8_vstar_branch != 0) {
				dr_ele8_vstar_branch->GetEntry(index);
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
			} else { 
				printf("branch dr_ele8_CaloIdL_CaloIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_ele8_CaloIdL_CaloIsoVL_vstar_isLoaded = true;
		}
		return dr_ele8_CaloIdL_CaloIsoVL_vstar_;
	}
	float &dr_ele17_CaloIdL_CaloIsoVL_vstar()
	{
		if (not dr_ele17_CaloIdL_CaloIsoVL_vstar_isLoaded) {
			if (dr_ele17_CaloIdL_CaloIsoVL_vstar_branch != 0) {
				dr_ele17_CaloIdL_CaloIsoVL_vstar_branch->GetEntry(index);
			} else { 
				printf("branch dr_ele17_CaloIdL_CaloIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_ele17_CaloIdL_CaloIsoVL_vstar_isLoaded = true;
		}
		return dr_ele17_CaloIdL_CaloIsoVL_vstar_;
	}
	float &dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar()
	{
		if (not dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_isLoaded) {
			if (dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch != 0) {
				dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar_branch->GetEntry(index);
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
			} else { 
				printf("branch dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_isLoaded = true;
		}
		return dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar_;
	}
	float &dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar()
	{
		if (not dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_isLoaded) {
			if (dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch != 0) {
				dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch->GetEntry(index);
			} else { 
				printf("branch dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_isLoaded = true;
		}
		return dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar_;
	}
	int &mu3_vstar()
	{
		if (not mu3_vstar_isLoaded) {
			if (mu3_vstar_branch != 0) {
				mu3_vstar_branch->GetEntry(index);
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
			} else { 
				printf("branch mu15_vstar_branch does not exist!\n");
				exit(1);
			}
			mu15_vstar_isLoaded = true;
		}
		return mu15_vstar_;
	}
	int &mu20_vstar()
	{
		if (not mu20_vstar_isLoaded) {
			if (mu20_vstar_branch != 0) {
				mu20_vstar_branch->GetEntry(index);
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
			} else { 
				printf("branch mu30_vstar_branch does not exist!\n");
				exit(1);
			}
			mu30_vstar_isLoaded = true;
		}
		return mu30_vstar_;
	}
	int &mu8_Jet40_vstar()
	{
		if (not mu8_Jet40_vstar_isLoaded) {
			if (mu8_Jet40_vstar_branch != 0) {
				mu8_Jet40_vstar_branch->GetEntry(index);
			} else { 
				printf("branch mu8_Jet40_vstar_branch does not exist!\n");
				exit(1);
			}
			mu8_Jet40_vstar_isLoaded = true;
		}
		return mu8_Jet40_vstar_;
	}
	int &mu3_version()
	{
		if (not mu3_version_isLoaded) {
			if (mu3_version_branch != 0) {
				mu3_version_branch->GetEntry(index);
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
			} else { 
				printf("branch mu15_version_branch does not exist!\n");
				exit(1);
			}
			mu15_version_isLoaded = true;
		}
		return mu15_version_;
	}
	int &mu20_version()
	{
		if (not mu20_version_isLoaded) {
			if (mu20_version_branch != 0) {
				mu20_version_branch->GetEntry(index);
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
			} else { 
				printf("branch mu30_version_branch does not exist!\n");
				exit(1);
			}
			mu30_version_isLoaded = true;
		}
		return mu30_version_;
	}
	int &mu8_Jet40_version()
	{
		if (not mu8_Jet40_version_isLoaded) {
			if (mu8_Jet40_version_branch != 0) {
				mu8_Jet40_version_branch->GetEntry(index);
			} else { 
				printf("branch mu8_Jet40_version_branch does not exist!\n");
				exit(1);
			}
			mu8_Jet40_version_isLoaded = true;
		}
		return mu8_Jet40_version_;
	}
	float &dr_mu3_vstar()
	{
		if (not dr_mu3_vstar_isLoaded) {
			if (dr_mu3_vstar_branch != 0) {
				dr_mu3_vstar_branch->GetEntry(index);
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
			} else { 
				printf("branch dr_mu15_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_mu15_vstar_isLoaded = true;
		}
		return dr_mu15_vstar_;
	}
	float &dr_mu20_vstar()
	{
		if (not dr_mu20_vstar_isLoaded) {
			if (dr_mu20_vstar_branch != 0) {
				dr_mu20_vstar_branch->GetEntry(index);
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
			} else { 
				printf("branch dr_mu30_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_mu30_vstar_isLoaded = true;
		}
		return dr_mu30_vstar_;
	}
	float &dr_mu8_Jet40_vstar()
	{
		if (not dr_mu8_Jet40_vstar_isLoaded) {
			if (dr_mu8_Jet40_vstar_branch != 0) {
				dr_mu8_Jet40_vstar_branch->GetEntry(index);
			} else { 
				printf("branch dr_mu8_Jet40_vstar_branch does not exist!\n");
				exit(1);
			}
			dr_mu8_Jet40_vstar_isLoaded = true;
		}
		return dr_mu8_Jet40_vstar_;
	}
	int &hlt15u()
	{
		if (not hlt15u_isLoaded) {
			if (hlt15u_branch != 0) {
				hlt15u_branch->GetEntry(index);
			} else { 
				printf("branch hlt15u_branch does not exist!\n");
				exit(1);
			}
			hlt15u_isLoaded = true;
		}
		return hlt15u_;
	}
	int &hlt30u()
	{
		if (not hlt30u_isLoaded) {
			if (hlt30u_branch != 0) {
				hlt30u_branch->GetEntry(index);
			} else { 
				printf("branch hlt30u_branch does not exist!\n");
				exit(1);
			}
			hlt30u_isLoaded = true;
		}
		return hlt30u_;
	}
	int &hlt50u()
	{
		if (not hlt50u_isLoaded) {
			if (hlt50u_branch != 0) {
				hlt50u_branch->GetEntry(index);
			} else { 
				printf("branch hlt50u_branch does not exist!\n");
				exit(1);
			}
			hlt50u_isLoaded = true;
		}
		return hlt50u_;
	}
	int &l16u()
	{
		if (not l16u_isLoaded) {
			if (l16u_branch != 0) {
				l16u_branch->GetEntry(index);
			} else { 
				printf("branch l16u_branch does not exist!\n");
				exit(1);
			}
			l16u_isLoaded = true;
		}
		return l16u_;
	}
	int &l110()
	{
		if (not l110_isLoaded) {
			if (l110_branch != 0) {
				l110_branch->GetEntry(index);
			} else { 
				printf("branch l110_branch does not exist!\n");
				exit(1);
			}
			l110_isLoaded = true;
		}
		return l110_;
	}
	int &ph10()
	{
		if (not ph10_isLoaded) {
			if (ph10_branch != 0) {
				ph10_branch->GetEntry(index);
			} else { 
				printf("branch ph10_branch does not exist!\n");
				exit(1);
			}
			ph10_isLoaded = true;
		}
		return ph10_;
	}
	int &ph15()
	{
		if (not ph15_isLoaded) {
			if (ph15_branch != 0) {
				ph15_branch->GetEntry(index);
			} else { 
				printf("branch ph15_branch does not exist!\n");
				exit(1);
			}
			ph15_isLoaded = true;
		}
		return ph15_;
	}
	int &ph20()
	{
		if (not ph20_isLoaded) {
			if (ph20_branch != 0) {
				ph20_branch->GetEntry(index);
			} else { 
				printf("branch ph20_branch does not exist!\n");
				exit(1);
			}
			ph20_isLoaded = true;
		}
		return ph20_;
	}
	int &el10_lw()
	{
		if (not el10_lw_isLoaded) {
			if (el10_lw_branch != 0) {
				el10_lw_branch->GetEntry(index);
			} else { 
				printf("branch el10_lw_branch does not exist!\n");
				exit(1);
			}
			el10_lw_isLoaded = true;
		}
		return el10_lw_;
	}
	int &el10_sw()
	{
		if (not el10_sw_isLoaded) {
			if (el10_sw_branch != 0) {
				el10_sw_branch->GetEntry(index);
			} else { 
				printf("branch el10_sw_branch does not exist!\n");
				exit(1);
			}
			el10_sw_isLoaded = true;
		}
		return el10_sw_;
	}
	int &el10_sw_v2()
	{
		if (not el10_sw_v2_isLoaded) {
			if (el10_sw_v2_branch != 0) {
				el10_sw_v2_branch->GetEntry(index);
			} else { 
				printf("branch el10_sw_v2_branch does not exist!\n");
				exit(1);
			}
			el10_sw_v2_isLoaded = true;
		}
		return el10_sw_v2_;
	}
	int &el10_lw_id()
	{
		if (not el10_lw_id_isLoaded) {
			if (el10_lw_id_branch != 0) {
				el10_lw_id_branch->GetEntry(index);
			} else { 
				printf("branch el10_lw_id_branch does not exist!\n");
				exit(1);
			}
			el10_lw_id_isLoaded = true;
		}
		return el10_lw_id_;
	}
	int &el10_sw_id()
	{
		if (not el10_sw_id_isLoaded) {
			if (el10_sw_id_branch != 0) {
				el10_sw_id_branch->GetEntry(index);
			} else { 
				printf("branch el10_sw_id_branch does not exist!\n");
				exit(1);
			}
			el10_sw_id_isLoaded = true;
		}
		return el10_sw_id_;
	}
	int &el15_lw()
	{
		if (not el15_lw_isLoaded) {
			if (el15_lw_branch != 0) {
				el15_lw_branch->GetEntry(index);
			} else { 
				printf("branch el15_lw_branch does not exist!\n");
				exit(1);
			}
			el15_lw_isLoaded = true;
		}
		return el15_lw_;
	}
	int &el15_sw()
	{
		if (not el15_sw_isLoaded) {
			if (el15_sw_branch != 0) {
				el15_sw_branch->GetEntry(index);
			} else { 
				printf("branch el15_sw_branch does not exist!\n");
				exit(1);
			}
			el15_sw_isLoaded = true;
		}
		return el15_sw_;
	}
	int &el15_lw_id()
	{
		if (not el15_lw_id_isLoaded) {
			if (el15_lw_id_branch != 0) {
				el15_lw_id_branch->GetEntry(index);
			} else { 
				printf("branch el15_lw_id_branch does not exist!\n");
				exit(1);
			}
			el15_lw_id_isLoaded = true;
		}
		return el15_lw_id_;
	}
	int &el15_sw_id()
	{
		if (not el15_sw_id_isLoaded) {
			if (el15_sw_id_branch != 0) {
				el15_sw_id_branch->GetEntry(index);
			} else { 
				printf("branch el15_sw_id_branch does not exist!\n");
				exit(1);
			}
			el15_sw_id_isLoaded = true;
		}
		return el15_sw_id_;
	}
	int &el15_sw_cid()
	{
		if (not el15_sw_cid_isLoaded) {
			if (el15_sw_cid_branch != 0) {
				el15_sw_cid_branch->GetEntry(index);
			} else { 
				printf("branch el15_sw_cid_branch does not exist!\n");
				exit(1);
			}
			el15_sw_cid_isLoaded = true;
		}
		return el15_sw_cid_;
	}
	int &el20_sw()
	{
		if (not el20_sw_isLoaded) {
			if (el20_sw_branch != 0) {
				el20_sw_branch->GetEntry(index);
			} else { 
				printf("branch el20_sw_branch does not exist!\n");
				exit(1);
			}
			el20_sw_isLoaded = true;
		}
		return el20_sw_;
	}
	int &el25_sw()
	{
		if (not el25_sw_isLoaded) {
			if (el25_sw_branch != 0) {
				el25_sw_branch->GetEntry(index);
			} else { 
				printf("branch el25_sw_branch does not exist!\n");
				exit(1);
			}
			el25_sw_isLoaded = true;
		}
		return el25_sw_;
	}
	int &Del10_sw()
	{
		if (not Del10_sw_isLoaded) {
			if (Del10_sw_branch != 0) {
				Del10_sw_branch->GetEntry(index);
			} else { 
				printf("branch Del10_sw_branch does not exist!\n");
				exit(1);
			}
			Del10_sw_isLoaded = true;
		}
		return Del10_sw_;
	}
	int &el17_sw()
	{
		if (not el17_sw_isLoaded) {
			if (el17_sw_branch != 0) {
				el17_sw_branch->GetEntry(index);
			} else { 
				printf("branch el17_sw_branch does not exist!\n");
				exit(1);
			}
			el17_sw_isLoaded = true;
		}
		return el17_sw_;
	}
	int &el17_sw_v2()
	{
		if (not el17_sw_v2_isLoaded) {
			if (el17_sw_v2_branch != 0) {
				el17_sw_v2_branch->GetEntry(index);
			} else { 
				printf("branch el17_sw_v2_branch does not exist!\n");
				exit(1);
			}
			el17_sw_v2_isLoaded = true;
		}
		return el17_sw_v2_;
	}
	int &el17_iso()
	{
		if (not el17_iso_isLoaded) {
			if (el17_iso_branch != 0) {
				el17_iso_branch->GetEntry(index);
			} else { 
				printf("branch el17_iso_branch does not exist!\n");
				exit(1);
			}
			el17_iso_isLoaded = true;
		}
		return el17_iso_;
	}
	int &el17_loose()
	{
		if (not el17_loose_isLoaded) {
			if (el17_loose_branch != 0) {
				el17_loose_branch->GetEntry(index);
			} else { 
				printf("branch el17_loose_branch does not exist!\n");
				exit(1);
			}
			el17_loose_isLoaded = true;
		}
		return el17_loose_;
	}
	int &el17_sw_cid()
	{
		if (not el17_sw_cid_isLoaded) {
			if (el17_sw_cid_branch != 0) {
				el17_sw_cid_branch->GetEntry(index);
			} else { 
				printf("branch el17_sw_cid_branch does not exist!\n");
				exit(1);
			}
			el17_sw_cid_isLoaded = true;
		}
		return el17_sw_cid_;
	}
	int &el17_sw_id()
	{
		if (not el17_sw_id_isLoaded) {
			if (el17_sw_id_branch != 0) {
				el17_sw_id_branch->GetEntry(index);
			} else { 
				printf("branch el17_sw_id_branch does not exist!\n");
				exit(1);
			}
			el17_sw_id_isLoaded = true;
		}
		return el17_sw_id_;
	}
	int &el17_tiso()
	{
		if (not el17_tiso_isLoaded) {
			if (el17_tiso_branch != 0) {
				el17_tiso_branch->GetEntry(index);
			} else { 
				printf("branch el17_tiso_branch does not exist!\n");
				exit(1);
			}
			el17_tiso_isLoaded = true;
		}
		return el17_tiso_;
	}
	int &el17_tiso_v1()
	{
		if (not el17_tiso_v1_isLoaded) {
			if (el17_tiso_v1_branch != 0) {
				el17_tiso_v1_branch->GetEntry(index);
			} else { 
				printf("branch el17_tiso_v1_branch does not exist!\n");
				exit(1);
			}
			el17_tiso_v1_isLoaded = true;
		}
		return el17_tiso_v1_;
	}
	float &drph10()
	{
		if (not drph10_isLoaded) {
			if (drph10_branch != 0) {
				drph10_branch->GetEntry(index);
			} else { 
				printf("branch drph10_branch does not exist!\n");
				exit(1);
			}
			drph10_isLoaded = true;
		}
		return drph10_;
	}
	float &drph15()
	{
		if (not drph15_isLoaded) {
			if (drph15_branch != 0) {
				drph15_branch->GetEntry(index);
			} else { 
				printf("branch drph15_branch does not exist!\n");
				exit(1);
			}
			drph15_isLoaded = true;
		}
		return drph15_;
	}
	float &drph20()
	{
		if (not drph20_isLoaded) {
			if (drph20_branch != 0) {
				drph20_branch->GetEntry(index);
			} else { 
				printf("branch drph20_branch does not exist!\n");
				exit(1);
			}
			drph20_isLoaded = true;
		}
		return drph20_;
	}
	float &drel10_lw()
	{
		if (not drel10_lw_isLoaded) {
			if (drel10_lw_branch != 0) {
				drel10_lw_branch->GetEntry(index);
			} else { 
				printf("branch drel10_lw_branch does not exist!\n");
				exit(1);
			}
			drel10_lw_isLoaded = true;
		}
		return drel10_lw_;
	}
	float &drel10_sw()
	{
		if (not drel10_sw_isLoaded) {
			if (drel10_sw_branch != 0) {
				drel10_sw_branch->GetEntry(index);
			} else { 
				printf("branch drel10_sw_branch does not exist!\n");
				exit(1);
			}
			drel10_sw_isLoaded = true;
		}
		return drel10_sw_;
	}
	float &drel10_sw_v2()
	{
		if (not drel10_sw_v2_isLoaded) {
			if (drel10_sw_v2_branch != 0) {
				drel10_sw_v2_branch->GetEntry(index);
			} else { 
				printf("branch drel10_sw_v2_branch does not exist!\n");
				exit(1);
			}
			drel10_sw_v2_isLoaded = true;
		}
		return drel10_sw_v2_;
	}
	float &drel10_lw_id()
	{
		if (not drel10_lw_id_isLoaded) {
			if (drel10_lw_id_branch != 0) {
				drel10_lw_id_branch->GetEntry(index);
			} else { 
				printf("branch drel10_lw_id_branch does not exist!\n");
				exit(1);
			}
			drel10_lw_id_isLoaded = true;
		}
		return drel10_lw_id_;
	}
	float &drel10_sw_id()
	{
		if (not drel10_sw_id_isLoaded) {
			if (drel10_sw_id_branch != 0) {
				drel10_sw_id_branch->GetEntry(index);
			} else { 
				printf("branch drel10_sw_id_branch does not exist!\n");
				exit(1);
			}
			drel10_sw_id_isLoaded = true;
		}
		return drel10_sw_id_;
	}
	float &drel15_lw()
	{
		if (not drel15_lw_isLoaded) {
			if (drel15_lw_branch != 0) {
				drel15_lw_branch->GetEntry(index);
			} else { 
				printf("branch drel15_lw_branch does not exist!\n");
				exit(1);
			}
			drel15_lw_isLoaded = true;
		}
		return drel15_lw_;
	}
	float &drel15_sw()
	{
		if (not drel15_sw_isLoaded) {
			if (drel15_sw_branch != 0) {
				drel15_sw_branch->GetEntry(index);
			} else { 
				printf("branch drel15_sw_branch does not exist!\n");
				exit(1);
			}
			drel15_sw_isLoaded = true;
		}
		return drel15_sw_;
	}
	float &drel15_lw_id()
	{
		if (not drel15_lw_id_isLoaded) {
			if (drel15_lw_id_branch != 0) {
				drel15_lw_id_branch->GetEntry(index);
			} else { 
				printf("branch drel15_lw_id_branch does not exist!\n");
				exit(1);
			}
			drel15_lw_id_isLoaded = true;
		}
		return drel15_lw_id_;
	}
	float &drel15_sw_id()
	{
		if (not drel15_sw_id_isLoaded) {
			if (drel15_sw_id_branch != 0) {
				drel15_sw_id_branch->GetEntry(index);
			} else { 
				printf("branch drel15_sw_id_branch does not exist!\n");
				exit(1);
			}
			drel15_sw_id_isLoaded = true;
		}
		return drel15_sw_id_;
	}
	float &drel15_sw_cid()
	{
		if (not drel15_sw_cid_isLoaded) {
			if (drel15_sw_cid_branch != 0) {
				drel15_sw_cid_branch->GetEntry(index);
			} else { 
				printf("branch drel15_sw_cid_branch does not exist!\n");
				exit(1);
			}
			drel15_sw_cid_isLoaded = true;
		}
		return drel15_sw_cid_;
	}
	float &drel20_sw()
	{
		if (not drel20_sw_isLoaded) {
			if (drel20_sw_branch != 0) {
				drel20_sw_branch->GetEntry(index);
			} else { 
				printf("branch drel20_sw_branch does not exist!\n");
				exit(1);
			}
			drel20_sw_isLoaded = true;
		}
		return drel20_sw_;
	}
	float &drel25_sw()
	{
		if (not drel25_sw_isLoaded) {
			if (drel25_sw_branch != 0) {
				drel25_sw_branch->GetEntry(index);
			} else { 
				printf("branch drel25_sw_branch does not exist!\n");
				exit(1);
			}
			drel25_sw_isLoaded = true;
		}
		return drel25_sw_;
	}
	float &drDel10_sw()
	{
		if (not drDel10_sw_isLoaded) {
			if (drDel10_sw_branch != 0) {
				drDel10_sw_branch->GetEntry(index);
			} else { 
				printf("branch drDel10_sw_branch does not exist!\n");
				exit(1);
			}
			drDel10_sw_isLoaded = true;
		}
		return drDel10_sw_;
	}
	float &drel17_sw()
	{
		if (not drel17_sw_isLoaded) {
			if (drel17_sw_branch != 0) {
				drel17_sw_branch->GetEntry(index);
			} else { 
				printf("branch drel17_sw_branch does not exist!\n");
				exit(1);
			}
			drel17_sw_isLoaded = true;
		}
		return drel17_sw_;
	}
	float &drel17_sw_v2()
	{
		if (not drel17_sw_v2_isLoaded) {
			if (drel17_sw_v2_branch != 0) {
				drel17_sw_v2_branch->GetEntry(index);
			} else { 
				printf("branch drel17_sw_v2_branch does not exist!\n");
				exit(1);
			}
			drel17_sw_v2_isLoaded = true;
		}
		return drel17_sw_v2_;
	}
	float &drel17_iso()
	{
		if (not drel17_iso_isLoaded) {
			if (drel17_iso_branch != 0) {
				drel17_iso_branch->GetEntry(index);
			} else { 
				printf("branch drel17_iso_branch does not exist!\n");
				exit(1);
			}
			drel17_iso_isLoaded = true;
		}
		return drel17_iso_;
	}
	float &drel17_loose()
	{
		if (not drel17_loose_isLoaded) {
			if (drel17_loose_branch != 0) {
				drel17_loose_branch->GetEntry(index);
			} else { 
				printf("branch drel17_loose_branch does not exist!\n");
				exit(1);
			}
			drel17_loose_isLoaded = true;
		}
		return drel17_loose_;
	}
	float &drel17_sw_cid()
	{
		if (not drel17_sw_cid_isLoaded) {
			if (drel17_sw_cid_branch != 0) {
				drel17_sw_cid_branch->GetEntry(index);
			} else { 
				printf("branch drel17_sw_cid_branch does not exist!\n");
				exit(1);
			}
			drel17_sw_cid_isLoaded = true;
		}
		return drel17_sw_cid_;
	}
	float &drel17_sw_id()
	{
		if (not drel17_sw_id_isLoaded) {
			if (drel17_sw_id_branch != 0) {
				drel17_sw_id_branch->GetEntry(index);
			} else { 
				printf("branch drel17_sw_id_branch does not exist!\n");
				exit(1);
			}
			drel17_sw_id_isLoaded = true;
		}
		return drel17_sw_id_;
	}
	float &drel17_tiso()
	{
		if (not drel17_tiso_isLoaded) {
			if (drel17_tiso_branch != 0) {
				drel17_tiso_branch->GetEntry(index);
			} else { 
				printf("branch drel17_tiso_branch does not exist!\n");
				exit(1);
			}
			drel17_tiso_isLoaded = true;
		}
		return drel17_tiso_;
	}
	float &drel17_tiso_v1()
	{
		if (not drel17_tiso_v1_isLoaded) {
			if (drel17_tiso_v1_branch != 0) {
				drel17_tiso_v1_branch->GetEntry(index);
			} else { 
				printf("branch drel17_tiso_v1_branch does not exist!\n");
				exit(1);
			}
			drel17_tiso_v1_isLoaded = true;
		}
		return drel17_tiso_v1_;
	}
	int &mu17()
	{
		if (not mu17_isLoaded) {
			if (mu17_branch != 0) {
				mu17_branch->GetEntry(index);
			} else { 
				printf("branch mu17_branch does not exist!\n");
				exit(1);
			}
			mu17_isLoaded = true;
		}
		return mu17_;
	}
	int &mu15()
	{
		if (not mu15_isLoaded) {
			if (mu15_branch != 0) {
				mu15_branch->GetEntry(index);
			} else { 
				printf("branch mu15_branch does not exist!\n");
				exit(1);
			}
			mu15_isLoaded = true;
		}
		return mu15_;
	}
	int &mu13()
	{
		if (not mu13_isLoaded) {
			if (mu13_branch != 0) {
				mu13_branch->GetEntry(index);
			} else { 
				printf("branch mu13_branch does not exist!\n");
				exit(1);
			}
			mu13_isLoaded = true;
		}
		return mu13_;
	}
	int &mu11()
	{
		if (not mu11_isLoaded) {
			if (mu11_branch != 0) {
				mu11_branch->GetEntry(index);
			} else { 
				printf("branch mu11_branch does not exist!\n");
				exit(1);
			}
			mu11_isLoaded = true;
		}
		return mu11_;
	}
	int &mu9()
	{
		if (not mu9_isLoaded) {
			if (mu9_branch != 0) {
				mu9_branch->GetEntry(index);
			} else { 
				printf("branch mu9_branch does not exist!\n");
				exit(1);
			}
			mu9_isLoaded = true;
		}
		return mu9_;
	}
	int &mu7()
	{
		if (not mu7_isLoaded) {
			if (mu7_branch != 0) {
				mu7_branch->GetEntry(index);
			} else { 
				printf("branch mu7_branch does not exist!\n");
				exit(1);
			}
			mu7_isLoaded = true;
		}
		return mu7_;
	}
	int &mu5()
	{
		if (not mu5_isLoaded) {
			if (mu5_branch != 0) {
				mu5_branch->GetEntry(index);
			} else { 
				printf("branch mu5_branch does not exist!\n");
				exit(1);
			}
			mu5_isLoaded = true;
		}
		return mu5_;
	}
	float &drmu17()
	{
		if (not drmu17_isLoaded) {
			if (drmu17_branch != 0) {
				drmu17_branch->GetEntry(index);
			} else { 
				printf("branch drmu17_branch does not exist!\n");
				exit(1);
			}
			drmu17_isLoaded = true;
		}
		return drmu17_;
	}
	float &drmu15()
	{
		if (not drmu15_isLoaded) {
			if (drmu15_branch != 0) {
				drmu15_branch->GetEntry(index);
			} else { 
				printf("branch drmu15_branch does not exist!\n");
				exit(1);
			}
			drmu15_isLoaded = true;
		}
		return drmu15_;
	}
	float &drmu13()
	{
		if (not drmu13_isLoaded) {
			if (drmu13_branch != 0) {
				drmu13_branch->GetEntry(index);
			} else { 
				printf("branch drmu13_branch does not exist!\n");
				exit(1);
			}
			drmu13_isLoaded = true;
		}
		return drmu13_;
	}
	float &drmu11()
	{
		if (not drmu11_isLoaded) {
			if (drmu11_branch != 0) {
				drmu11_branch->GetEntry(index);
			} else { 
				printf("branch drmu11_branch does not exist!\n");
				exit(1);
			}
			drmu11_isLoaded = true;
		}
		return drmu11_;
	}
	float &drmu9()
	{
		if (not drmu9_isLoaded) {
			if (drmu9_branch != 0) {
				drmu9_branch->GetEntry(index);
			} else { 
				printf("branch drmu9_branch does not exist!\n");
				exit(1);
			}
			drmu9_isLoaded = true;
		}
		return drmu9_;
	}
	float &drmu7()
	{
		if (not drmu7_isLoaded) {
			if (drmu7_branch != 0) {
				drmu7_branch->GetEntry(index);
			} else { 
				printf("branch drmu7_branch does not exist!\n");
				exit(1);
			}
			drmu7_isLoaded = true;
		}
		return drmu7_;
	}
	float &drmu5()
	{
		if (not drmu5_isLoaded) {
			if (drmu5_branch != 0) {
				drmu5_branch->GetEntry(index);
			} else { 
				printf("branch drmu5_branch does not exist!\n");
				exit(1);
			}
			drmu5_isLoaded = true;
		}
		return drmu5_;
	}
	float &ptj1()
	{
		if (not ptj1_isLoaded) {
			if (ptj1_branch != 0) {
				ptj1_branch->GetEntry(index);
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
			} else { 
				printf("branch btagpfcL1F_branch does not exist!\n");
				exit(1);
			}
			btagpfcL1F_isLoaded = true;
		}
		return btagpfcL1F_;
	}
	float &ptbtagpfcL1Fj1()
	{
		if (not ptbtagpfcL1Fj1_isLoaded) {
			if (ptbtagpfcL1Fj1_branch != 0) {
				ptbtagpfcL1Fj1_branch->GetEntry(index);
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
			} else { 
				printf("branch dphibtagpfcL1Fj1_branch does not exist!\n");
				exit(1);
			}
			dphibtagpfcL1Fj1_isLoaded = true;
		}
		return dphibtagpfcL1Fj1_;
	}
	float &ptjptcj1()
	{
		if (not ptjptcj1_isLoaded) {
			if (ptjptcj1_branch != 0) {
				ptjptcj1_branch->GetEntry(index);
			} else { 
				printf("branch ptjptcj1_branch does not exist!\n");
				exit(1);
			}
			ptjptcj1_isLoaded = true;
		}
		return ptjptcj1_;
	}
	int &njptcj1()
	{
		if (not njptcj1_isLoaded) {
			if (njptcj1_branch != 0) {
				njptcj1_branch->GetEntry(index);
			} else { 
				printf("branch njptcj1_branch does not exist!\n");
				exit(1);
			}
			njptcj1_isLoaded = true;
		}
		return njptcj1_;
	}
	float &ptjptcj1_b2b()
	{
		if (not ptjptcj1_b2b_isLoaded) {
			if (ptjptcj1_b2b_branch != 0) {
				ptjptcj1_b2b_branch->GetEntry(index);
			} else { 
				printf("branch ptjptcj1_b2b_branch does not exist!\n");
				exit(1);
			}
			ptjptcj1_b2b_isLoaded = true;
		}
		return ptjptcj1_b2b_;
	}
	float &dphijptcj1_b2b()
	{
		if (not dphijptcj1_b2b_isLoaded) {
			if (dphijptcj1_b2b_branch != 0) {
				dphijptcj1_b2b_branch->GetEntry(index);
			} else { 
				printf("branch dphijptcj1_b2b_branch does not exist!\n");
				exit(1);
			}
			dphijptcj1_b2b_isLoaded = true;
		}
		return dphijptcj1_b2b_;
	}
	bool &	btagjptc()
	{
		if (not btagjptc_isLoaded) {
			if (btagjptc_branch != 0) {
				btagjptc_branch->GetEntry(index);
			} else { 
				printf("branch btagjptc_branch does not exist!\n");
				exit(1);
			}
			btagjptc_isLoaded = true;
		}
		return btagjptc_;
	}
	int &nbjet()
	{
		if (not nbjet_isLoaded) {
			if (nbjet_branch != 0) {
				nbjet_branch->GetEntry(index);
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
	int &evt_ndavtxs();
	int &nFOels();
	int &nFOmus();
	int &ngsfs();
	int &nmus();
	int &foel_id();
	int &fomu_id();
	float &foel_mass();
	float &fomu_mass();
	float &pt();
	LorentzVector &lp4();
	float &eta();
	float &sceta();
	float &phi();
	float &scet();
	float &hoe();
	float &tcmet();
	float &tcmetphi();
	float &pfmet();
	float &pfmetphi();
	float &iso();
	float &iso_nps();
	float &nt_iso();
	float &nt_iso_nps();
	float &trck_iso();
	float &trck_nt_iso();
	float &ecal_iso();
	float &ecal_iso_nps();
	float &ecal_nt_iso();
	float &ecal_nt_iso_nps();
	float &hcal_iso();
	float &hcal_nt_iso();
	float &nt_pfiso03();
	float &nt_pfiso04();
	int &id();
	bool &closestMuon();
	bool &el_id_smurfV5();
	bool &el_id_vbtf80();
	bool &el_id_vbtf90();
	bool &conv0MissHits();
	bool &convHitPattern();
	bool &convPartnerTrack();
	bool &convMIT();
	float &mt();
	float &pfmt();
	bool &q3();
	int &els_exp_innerlayers();
	int &mcid();
	int &mcmotherid();
	float &d0PV_wwV1();
	float &dzPV_wwV1();
	float &ht_calo();
	float &ht_calo_L2L3();
	float &ht_jpt_L2L3();
	float &ht_pf();
	float &ht_pf_L2L3();
	float &ht_pf_L1FastL2L3();
	int &mc3id();
	float &mc3pt();
	float &mc3dr();
	int &leptonIsFromW();
	float &el_lh();
	float &el_mva();
	bool &mu_isCosmic();
	float &mz_fo_gsf();
	float &mz_gsf_iso();
	float &mz_fo_ctf();
	float &mz_ctf_iso();
	float &mupsilon_fo_mu();
	float &mupsilon_mu_iso();
	bool &num_el_ssV3();
	bool &v1_el_ssV3();
	bool &v2_el_ssV3();
	bool &v3_el_ssV3();
	bool &num_el_ssV4();
	bool &v1_el_ssV4();
	bool &v2_el_ssV4();
	bool &v3_el_ssV4();
	bool &num_el_ssV5();
	bool &v1_el_ssV5();
	bool &v2_el_ssV5();
	bool &v3_el_ssV5();
	bool &num_el_ssV5_noIso();
	bool &num_el_ssV6();
	bool &v1_el_ssV6();
	bool &v2_el_ssV6();
	bool &v3_el_ssV6();
	bool &num_el_ssV6_noIso();
	bool &numNomSSv3();
	bool &fo_mussV3_04();
	bool &numNomSSv4();
	bool &fo_mussV4_04();
	bool &numNomSSv4noIso();
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
	bool &numOct6();
	bool &v1Oct6();
	bool &v2Oct6();
	bool &v3Oct6();
	bool &num();
	bool &fo_04();
	bool &fo_10();
	bool &v1SSV2();
	bool &v2SSV2();
	bool &v3SSV2();
	bool &numSSV2();
	bool &numNomSSv2();
	bool &fo_mussV2_04();
	bool &fo_mussV2_10();
	bool &num_OSGv1();
	bool &num_OSZv1();
	bool &numOSOct18();
	bool &v1OSOct18();
	bool &v2OSOct18();
	bool &v3OSOct18();
	bool &num_wwV1();
	bool &v1_wwV1();
	bool &v2_wwV1();
	bool &v3_wwV1();
	bool &v4_wwV1();
	bool &fo_wwV1_04();
	bool &fo_wwV1_10();
	bool &fo_wwV1_10_d0();
	int &ele8_vstar();
	int &ele8_CaloIdL_TrkIdVL_vstar();
	int &ele8_CaloIdL_CaloIsoVL_Jet40_vstar();
	int &ele8_CaloIdL_CaloIsoVL_vstar();
	int &ele17_CaloIdL_CaloIsoVL_vstar();
	int &ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar();
	int &ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar();
	int &photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar();
	int &ele8_version();
	int &ele8_CaloIdL_TrkIdVL_version();
	int &ele8_CaloIdL_CaloIsoVL_Jet40_version();
	int &ele8_CaloIdL_CaloIsoVL_version();
	int &ele17_CaloIdL_CaloIsoVL_version();
	int &ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_version();
	int &ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version();
	int &photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_version();
	float &dr_ele8_vstar();
	float &dr_ele8_CaloIdL_TrkIdVL_vstar();
	float &dr_ele8_CaloIdL_CaloIsoVL_Jet40_vstar();
	float &dr_ele8_CaloIdL_CaloIsoVL_vstar();
	float &dr_ele17_CaloIdL_CaloIsoVL_vstar();
	float &dr_ele8_CaloIdT_TrkIdVL_CaloIsoVL_TrkIsoVL_vstar();
	float &dr_ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar();
	float &dr_photon20_CaloIdVT_IsoT_Ele8_CaloIdL_CaloIsoVL_vstar();
	int &mu3_vstar();
	int &mu5_vstar();
	int &mu8_vstar();
	int &mu12_vstar();
	int &mu15_vstar();
	int &mu20_vstar();
	int &mu24_vstar();
	int &mu30_vstar();
	int &mu8_Jet40_vstar();
	int &mu3_version();
	int &mu5_version();
	int &mu8_version();
	int &mu12_version();
	int &mu15_version();
	int &mu20_version();
	int &mu24_version();
	int &mu30_version();
	int &mu8_Jet40_version();
	float &dr_mu3_vstar();
	float &dr_mu5_vstar();
	float &dr_mu8_vstar();
	float &dr_mu12_vstar();
	float &dr_mu15_vstar();
	float &dr_mu20_vstar();
	float &dr_mu24_vstar();
	float &dr_mu30_vstar();
	float &dr_mu8_Jet40_vstar();
	int &hlt15u();
	int &hlt30u();
	int &hlt50u();
	int &l16u();
	int &l110();
	int &ph10();
	int &ph15();
	int &ph20();
	int &el10_lw();
	int &el10_sw();
	int &el10_sw_v2();
	int &el10_lw_id();
	int &el10_sw_id();
	int &el15_lw();
	int &el15_sw();
	int &el15_lw_id();
	int &el15_sw_id();
	int &el15_sw_cid();
	int &el20_sw();
	int &el25_sw();
	int &Del10_sw();
	int &el17_sw();
	int &el17_sw_v2();
	int &el17_iso();
	int &el17_loose();
	int &el17_sw_cid();
	int &el17_sw_id();
	int &el17_tiso();
	int &el17_tiso_v1();
	float &drph10();
	float &drph15();
	float &drph20();
	float &drel10_lw();
	float &drel10_sw();
	float &drel10_sw_v2();
	float &drel10_lw_id();
	float &drel10_sw_id();
	float &drel15_lw();
	float &drel15_sw();
	float &drel15_lw_id();
	float &drel15_sw_id();
	float &drel15_sw_cid();
	float &drel20_sw();
	float &drel25_sw();
	float &drDel10_sw();
	float &drel17_sw();
	float &drel17_sw_v2();
	float &drel17_iso();
	float &drel17_loose();
	float &drel17_sw_cid();
	float &drel17_sw_id();
	float &drel17_tiso();
	float &drel17_tiso_v1();
	int &mu17();
	int &mu15();
	int &mu13();
	int &mu11();
	int &mu9();
	int &mu7();
	int &mu5();
	float &drmu17();
	float &drmu15();
	float &drmu13();
	float &drmu11();
	float &drmu9();
	float &drmu7();
	float &drmu5();
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
	float &ptbtagpfcL1Fj1();
	float &dphibtagpfcL1Fj1();
	float &ptjptcj1();
	int &njptcj1();
	float &ptjptcj1_b2b();
	float &dphijptcj1_b2b();
	bool &btagjptc();
	int &nbjet();
	float &dRNear();
	float &dRFar();
	int &nbpfcjet();
	float &dRpfcNear();
	float &dRpfcFar();
	float &rho();
}
#endif
