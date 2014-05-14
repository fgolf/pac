// -*- C++ -*-
#ifndef OutreachBaby_H
#define OutreachBaby_H
#include "Math/LorentzVector.h"
#include "Math/Point3D.h"
#include "TMath.h"
#include "TBranch.h"
#include "TTree.h"
#include "TH1F.h"
#include "TFile.h"
#include "TBits.h"
#include <vector> 
#include <unistd.h>
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

using namespace std; 
class OutreachBaby {
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
	int	gen_dilep_type_;
	TBranch *gen_dilep_type_branch;
	bool gen_dilep_type_isLoaded;
	float	gen_ht_;
	TBranch *gen_ht_branch;
	bool gen_ht_isLoaded;
	int	gen_nbtags_;
	TBranch *gen_nbtags_branch;
	bool gen_nbtags_isLoaded;
	int	gen_njets_;
	TBranch *gen_njets_branch;
	bool gen_njets_isLoaded;
	bool	gen_is_ss_;
	TBranch *gen_is_ss_branch;
	bool gen_is_ss_isLoaded;
	bool	gen_is_os_;
	TBranch *gen_is_os_branch;
	bool gen_is_os_isLoaded;
	int	dilep_type_;
	TBranch *dilep_type_branch;
	bool dilep_type_isLoaded;
	float	reco_ht_;
	TBranch *reco_ht_branch;
	bool reco_ht_isLoaded;
	float	reco_met_;
	TBranch *reco_met_branch;
	bool reco_met_isLoaded;
	int	reco_nbtags_;
	TBranch *reco_nbtags_branch;
	bool reco_nbtags_isLoaded;
	int	reco_njets_;
	TBranch *reco_njets_branch;
	bool reco_njets_isLoaded;
	float	reco_is_ss_;
	TBranch *reco_is_ss_branch;
	bool reco_is_ss_isLoaded;
	float	reco_is_os_;
	TBranch *reco_is_os_branch;
	bool reco_is_os_isLoaded;
	float	sf_dileptrig_;
	TBranch *sf_dileptrig_branch;
	bool sf_dileptrig_isLoaded;
	float	sf_lepeff_;
	TBranch *sf_lepeff_branch;
	bool sf_lepeff_isLoaded;
	float	sf_nbtag_;
	TBranch *sf_nbtag_branch;
	bool sf_nbtag_isLoaded;
	float	sf_nbtag3_;
	TBranch *sf_nbtag3_branch;
	bool sf_nbtag3_isLoaded;
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
	int	lep1_gen_pdgid_;
	TBranch *lep1_gen_pdgid_branch;
	bool lep1_gen_pdgid_isLoaded;
	int	lep1_pdgid_;
	TBranch *lep1_pdgid_branch;
	bool lep1_pdgid_isLoaded;
	bool	lep1_matched_;
	TBranch *lep1_matched_branch;
	bool lep1_matched_isLoaded;
	bool	lep1_from_tau_;
	TBranch *lep1_from_tau_branch;
	bool lep1_from_tau_isLoaded;
	bool	lep1_passes_id_;
	TBranch *lep1_passes_id_branch;
	bool lep1_passes_id_isLoaded;
	bool	lep1_passes_iso_;
	TBranch *lep1_passes_iso_branch;
	bool lep1_passes_iso_isLoaded;
	bool	lep1_num_;
	TBranch *lep1_num_branch;
	bool lep1_num_isLoaded;
	float	lep1_iso_;
	TBranch *lep1_iso_branch;
	bool lep1_iso_isLoaded;
	int	lep2_pdgid_;
	TBranch *lep2_pdgid_branch;
	bool lep2_pdgid_isLoaded;
	int	lep2_gen_pdgid_;
	TBranch *lep2_gen_pdgid_branch;
	bool lep2_gen_pdgid_isLoaded;
	bool	lep2_matched_;
	TBranch *lep2_matched_branch;
	bool lep2_matched_isLoaded;
	bool	lep2_from_tau_;
	TBranch *lep2_from_tau_branch;
	bool lep2_from_tau_isLoaded;
	bool	lep2_passes_id_;
	TBranch *lep2_passes_id_branch;
	bool lep2_passes_id_isLoaded;
	bool	lep2_passes_iso_;
	TBranch *lep2_passes_iso_branch;
	bool lep2_passes_iso_isLoaded;
	bool	lep2_num_;
	TBranch *lep2_num_branch;
	bool lep2_num_isLoaded;
	float	lep2_iso_;
	TBranch *lep2_iso_branch;
	bool lep2_iso_isLoaded;
	float	metw30_;
	TBranch *metw30_branch;
	bool metw30_isLoaded;
	float	metw50_;
	TBranch *metw50_branch;
	bool metw50_isLoaded;
	float	metw120_;
	TBranch *metw120_branch;
	bool metw120_isLoaded;
	float	btagw_;
	TBranch *btagw_branch;
	bool btagw_isLoaded;
	float	pt1w_;
	TBranch *pt1w_branch;
	bool pt1w_isLoaded;
	float	pt2w_;
	TBranch *pt2w_branch;
	bool pt2w_isLoaded;
	float	htw200_;
	TBranch *htw200_branch;
	bool htw200_isLoaded;
	float	htw320_;
	TBranch *htw320_branch;
	bool htw320_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_gen_p4_;
	TBranch *lep1_gen_p4_branch;
	bool lep1_gen_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_p4_;
	TBranch *lep1_p4_branch;
	bool lep1_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_gen_p4_;
	TBranch *lep2_gen_p4_branch;
	bool lep2_gen_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_p4_;
	TBranch *lep2_p4_branch;
	bool lep2_p4_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *gen_vbjets_p4_;
	TBranch *gen_vbjets_p4_branch;
	bool gen_vbjets_p4_isLoaded;
	vector<bool> *gen_vbjets_matched_;
	TBranch *gen_vbjets_matched_branch;
	bool gen_vbjets_matched_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *gen_vjets_p4_;
	TBranch *gen_vjets_p4_branch;
	bool gen_vjets_p4_isLoaded;
	vector<bool> *gen_vjets_matched_;
	TBranch *gen_vjets_matched_branch;
	bool gen_vjets_matched_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *reco_vbjets_p4_;
	TBranch *reco_vbjets_p4_branch;
	bool reco_vbjets_p4_isLoaded;
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > *reco_vjets_p4_;
	TBranch *reco_vjets_p4_branch;
	bool reco_vjets_p4_isLoaded;
public: 
void Init(TTree *tree) {
	lep1_gen_p4_branch = 0;
	if (tree->GetBranch("lep1_gen_p4") != 0) {
		lep1_gen_p4_branch = tree->GetBranch("lep1_gen_p4");
		lep1_gen_p4_branch->SetAddress(&lep1_gen_p4_);
	}
	lep1_p4_branch = 0;
	if (tree->GetBranch("lep1_p4") != 0) {
		lep1_p4_branch = tree->GetBranch("lep1_p4");
		lep1_p4_branch->SetAddress(&lep1_p4_);
	}
	lep2_gen_p4_branch = 0;
	if (tree->GetBranch("lep2_gen_p4") != 0) {
		lep2_gen_p4_branch = tree->GetBranch("lep2_gen_p4");
		lep2_gen_p4_branch->SetAddress(&lep2_gen_p4_);
	}
	lep2_p4_branch = 0;
	if (tree->GetBranch("lep2_p4") != 0) {
		lep2_p4_branch = tree->GetBranch("lep2_p4");
		lep2_p4_branch->SetAddress(&lep2_p4_);
	}
	gen_vbjets_p4_branch = 0;
	if (tree->GetBranch("gen_vbjets_p4") != 0) {
		gen_vbjets_p4_branch = tree->GetBranch("gen_vbjets_p4");
		gen_vbjets_p4_branch->SetAddress(&gen_vbjets_p4_);
	}
	gen_vjets_p4_branch = 0;
	if (tree->GetBranch("gen_vjets_p4") != 0) {
		gen_vjets_p4_branch = tree->GetBranch("gen_vjets_p4");
		gen_vjets_p4_branch->SetAddress(&gen_vjets_p4_);
	}
	reco_vbjets_p4_branch = 0;
	if (tree->GetBranch("reco_vbjets_p4") != 0) {
		reco_vbjets_p4_branch = tree->GetBranch("reco_vbjets_p4");
		reco_vbjets_p4_branch->SetAddress(&reco_vbjets_p4_);
	}
	reco_vjets_p4_branch = 0;
	if (tree->GetBranch("reco_vjets_p4") != 0) {
		reco_vjets_p4_branch = tree->GetBranch("reco_vjets_p4");
		reco_vjets_p4_branch->SetAddress(&reco_vjets_p4_);
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
	gen_dilep_type_branch = 0;
	if (tree->GetBranch("gen_dilep_type") != 0) {
		gen_dilep_type_branch = tree->GetBranch("gen_dilep_type");
		gen_dilep_type_branch->SetAddress(&gen_dilep_type_);
	}
	gen_ht_branch = 0;
	if (tree->GetBranch("gen_ht") != 0) {
		gen_ht_branch = tree->GetBranch("gen_ht");
		gen_ht_branch->SetAddress(&gen_ht_);
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
	gen_is_ss_branch = 0;
	if (tree->GetBranch("gen_is_ss") != 0) {
		gen_is_ss_branch = tree->GetBranch("gen_is_ss");
		gen_is_ss_branch->SetAddress(&gen_is_ss_);
	}
	gen_is_os_branch = 0;
	if (tree->GetBranch("gen_is_os") != 0) {
		gen_is_os_branch = tree->GetBranch("gen_is_os");
		gen_is_os_branch->SetAddress(&gen_is_os_);
	}
	dilep_type_branch = 0;
	if (tree->GetBranch("dilep_type") != 0) {
		dilep_type_branch = tree->GetBranch("dilep_type");
		dilep_type_branch->SetAddress(&dilep_type_);
	}
	reco_ht_branch = 0;
	if (tree->GetBranch("reco_ht") != 0) {
		reco_ht_branch = tree->GetBranch("reco_ht");
		reco_ht_branch->SetAddress(&reco_ht_);
	}
	reco_met_branch = 0;
	if (tree->GetBranch("reco_met") != 0) {
		reco_met_branch = tree->GetBranch("reco_met");
		reco_met_branch->SetAddress(&reco_met_);
	}
	reco_nbtags_branch = 0;
	if (tree->GetBranch("reco_nbtags") != 0) {
		reco_nbtags_branch = tree->GetBranch("reco_nbtags");
		reco_nbtags_branch->SetAddress(&reco_nbtags_);
	}
	reco_njets_branch = 0;
	if (tree->GetBranch("reco_njets") != 0) {
		reco_njets_branch = tree->GetBranch("reco_njets");
		reco_njets_branch->SetAddress(&reco_njets_);
	}
	reco_is_ss_branch = 0;
	if (tree->GetBranch("reco_is_ss") != 0) {
		reco_is_ss_branch = tree->GetBranch("reco_is_ss");
		reco_is_ss_branch->SetAddress(&reco_is_ss_);
	}
	reco_is_os_branch = 0;
	if (tree->GetBranch("reco_is_os") != 0) {
		reco_is_os_branch = tree->GetBranch("reco_is_os");
		reco_is_os_branch->SetAddress(&reco_is_os_);
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
	lep1_gen_pdgid_branch = 0;
	if (tree->GetBranch("lep1_gen_pdgid") != 0) {
		lep1_gen_pdgid_branch = tree->GetBranch("lep1_gen_pdgid");
		lep1_gen_pdgid_branch->SetAddress(&lep1_gen_pdgid_);
	}
	lep1_pdgid_branch = 0;
	if (tree->GetBranch("lep1_pdgid") != 0) {
		lep1_pdgid_branch = tree->GetBranch("lep1_pdgid");
		lep1_pdgid_branch->SetAddress(&lep1_pdgid_);
	}
	lep1_matched_branch = 0;
	if (tree->GetBranch("lep1_matched") != 0) {
		lep1_matched_branch = tree->GetBranch("lep1_matched");
		lep1_matched_branch->SetAddress(&lep1_matched_);
	}
	lep1_from_tau_branch = 0;
	if (tree->GetBranch("lep1_from_tau") != 0) {
		lep1_from_tau_branch = tree->GetBranch("lep1_from_tau");
		lep1_from_tau_branch->SetAddress(&lep1_from_tau_);
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
	lep1_num_branch = 0;
	if (tree->GetBranch("lep1_num") != 0) {
		lep1_num_branch = tree->GetBranch("lep1_num");
		lep1_num_branch->SetAddress(&lep1_num_);
	}
	lep1_iso_branch = 0;
	if (tree->GetBranch("lep1_iso") != 0) {
		lep1_iso_branch = tree->GetBranch("lep1_iso");
		lep1_iso_branch->SetAddress(&lep1_iso_);
	}
	lep2_pdgid_branch = 0;
	if (tree->GetBranch("lep2_pdgid") != 0) {
		lep2_pdgid_branch = tree->GetBranch("lep2_pdgid");
		lep2_pdgid_branch->SetAddress(&lep2_pdgid_);
	}
	lep2_gen_pdgid_branch = 0;
	if (tree->GetBranch("lep2_gen_pdgid") != 0) {
		lep2_gen_pdgid_branch = tree->GetBranch("lep2_gen_pdgid");
		lep2_gen_pdgid_branch->SetAddress(&lep2_gen_pdgid_);
	}
	lep2_matched_branch = 0;
	if (tree->GetBranch("lep2_matched") != 0) {
		lep2_matched_branch = tree->GetBranch("lep2_matched");
		lep2_matched_branch->SetAddress(&lep2_matched_);
	}
	lep2_from_tau_branch = 0;
	if (tree->GetBranch("lep2_from_tau") != 0) {
		lep2_from_tau_branch = tree->GetBranch("lep2_from_tau");
		lep2_from_tau_branch->SetAddress(&lep2_from_tau_);
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
	lep2_num_branch = 0;
	if (tree->GetBranch("lep2_num") != 0) {
		lep2_num_branch = tree->GetBranch("lep2_num");
		lep2_num_branch->SetAddress(&lep2_num_);
	}
	lep2_iso_branch = 0;
	if (tree->GetBranch("lep2_iso") != 0) {
		lep2_iso_branch = tree->GetBranch("lep2_iso");
		lep2_iso_branch->SetAddress(&lep2_iso_);
	}
	metw30_branch = 0;
	if (tree->GetBranch("metw30") != 0) {
		metw30_branch = tree->GetBranch("metw30");
		metw30_branch->SetAddress(&metw30_);
	}
	metw50_branch = 0;
	if (tree->GetBranch("metw50") != 0) {
		metw50_branch = tree->GetBranch("metw50");
		metw50_branch->SetAddress(&metw50_);
	}
	metw120_branch = 0;
	if (tree->GetBranch("metw120") != 0) {
		metw120_branch = tree->GetBranch("metw120");
		metw120_branch->SetAddress(&metw120_);
	}
	btagw_branch = 0;
	if (tree->GetBranch("btagw") != 0) {
		btagw_branch = tree->GetBranch("btagw");
		btagw_branch->SetAddress(&btagw_);
	}
	pt1w_branch = 0;
	if (tree->GetBranch("pt1w") != 0) {
		pt1w_branch = tree->GetBranch("pt1w");
		pt1w_branch->SetAddress(&pt1w_);
	}
	pt2w_branch = 0;
	if (tree->GetBranch("pt2w") != 0) {
		pt2w_branch = tree->GetBranch("pt2w");
		pt2w_branch->SetAddress(&pt2w_);
	}
	htw200_branch = 0;
	if (tree->GetBranch("htw200") != 0) {
		htw200_branch = tree->GetBranch("htw200");
		htw200_branch->SetAddress(&htw200_);
	}
	htw320_branch = 0;
	if (tree->GetBranch("htw320") != 0) {
		htw320_branch = tree->GetBranch("htw320");
		htw320_branch->SetAddress(&htw320_);
	}
	gen_vbjets_matched_branch = 0;
	if (tree->GetBranch("gen_vbjets_matched") != 0) {
		gen_vbjets_matched_branch = tree->GetBranch("gen_vbjets_matched");
		gen_vbjets_matched_branch->SetAddress(&gen_vbjets_matched_);
	}
	gen_vjets_matched_branch = 0;
	if (tree->GetBranch("gen_vjets_matched") != 0) {
		gen_vjets_matched_branch = tree->GetBranch("gen_vjets_matched");
		gen_vjets_matched_branch->SetAddress(&gen_vjets_matched_);
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
		gen_dilep_type_isLoaded = false;
		gen_ht_isLoaded = false;
		gen_nbtags_isLoaded = false;
		gen_njets_isLoaded = false;
		gen_is_ss_isLoaded = false;
		gen_is_os_isLoaded = false;
		dilep_type_isLoaded = false;
		reco_ht_isLoaded = false;
		reco_met_isLoaded = false;
		reco_nbtags_isLoaded = false;
		reco_njets_isLoaded = false;
		reco_is_ss_isLoaded = false;
		reco_is_os_isLoaded = false;
		sf_dileptrig_isLoaded = false;
		sf_lepeff_isLoaded = false;
		sf_nbtag_isLoaded = false;
		sf_nbtag3_isLoaded = false;
		sparm0_isLoaded = false;
		sparm1_isLoaded = false;
		sparm2_isLoaded = false;
		sparm3_isLoaded = false;
		lep1_gen_pdgid_isLoaded = false;
		lep1_pdgid_isLoaded = false;
		lep1_matched_isLoaded = false;
		lep1_from_tau_isLoaded = false;
		lep1_passes_id_isLoaded = false;
		lep1_passes_iso_isLoaded = false;
		lep1_num_isLoaded = false;
		lep1_iso_isLoaded = false;
		lep2_pdgid_isLoaded = false;
		lep2_gen_pdgid_isLoaded = false;
		lep2_matched_isLoaded = false;
		lep2_from_tau_isLoaded = false;
		lep2_passes_id_isLoaded = false;
		lep2_passes_iso_isLoaded = false;
		lep2_num_isLoaded = false;
		lep2_iso_isLoaded = false;
		metw30_isLoaded = false;
		metw50_isLoaded = false;
		metw120_isLoaded = false;
		btagw_isLoaded = false;
		pt1w_isLoaded = false;
		pt2w_isLoaded = false;
		htw200_isLoaded = false;
		htw320_isLoaded = false;
		lep1_gen_p4_isLoaded = false;
		lep1_p4_isLoaded = false;
		lep2_gen_p4_isLoaded = false;
		lep2_p4_isLoaded = false;
		gen_vbjets_p4_isLoaded = false;
		gen_vbjets_matched_isLoaded = false;
		gen_vjets_p4_isLoaded = false;
		gen_vjets_matched_isLoaded = false;
		reco_vbjets_p4_isLoaded = false;
		reco_vjets_p4_isLoaded = false;
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
	if (gen_dilep_type_branch != 0) gen_dilep_type();
	if (gen_ht_branch != 0) gen_ht();
	if (gen_nbtags_branch != 0) gen_nbtags();
	if (gen_njets_branch != 0) gen_njets();
	if (gen_is_ss_branch != 0) gen_is_ss();
	if (gen_is_os_branch != 0) gen_is_os();
	if (dilep_type_branch != 0) dilep_type();
	if (reco_ht_branch != 0) reco_ht();
	if (reco_met_branch != 0) reco_met();
	if (reco_nbtags_branch != 0) reco_nbtags();
	if (reco_njets_branch != 0) reco_njets();
	if (reco_is_ss_branch != 0) reco_is_ss();
	if (reco_is_os_branch != 0) reco_is_os();
	if (sf_dileptrig_branch != 0) sf_dileptrig();
	if (sf_lepeff_branch != 0) sf_lepeff();
	if (sf_nbtag_branch != 0) sf_nbtag();
	if (sf_nbtag3_branch != 0) sf_nbtag3();
	if (sparm0_branch != 0) sparm0();
	if (sparm1_branch != 0) sparm1();
	if (sparm2_branch != 0) sparm2();
	if (sparm3_branch != 0) sparm3();
	if (lep1_gen_pdgid_branch != 0) lep1_gen_pdgid();
	if (lep1_pdgid_branch != 0) lep1_pdgid();
	if (lep1_matched_branch != 0) lep1_matched();
	if (lep1_from_tau_branch != 0) lep1_from_tau();
	if (lep1_passes_id_branch != 0) lep1_passes_id();
	if (lep1_passes_iso_branch != 0) lep1_passes_iso();
	if (lep1_num_branch != 0) lep1_num();
	if (lep1_iso_branch != 0) lep1_iso();
	if (lep2_pdgid_branch != 0) lep2_pdgid();
	if (lep2_gen_pdgid_branch != 0) lep2_gen_pdgid();
	if (lep2_matched_branch != 0) lep2_matched();
	if (lep2_from_tau_branch != 0) lep2_from_tau();
	if (lep2_passes_id_branch != 0) lep2_passes_id();
	if (lep2_passes_iso_branch != 0) lep2_passes_iso();
	if (lep2_num_branch != 0) lep2_num();
	if (lep2_iso_branch != 0) lep2_iso();
	if (metw30_branch != 0) metw30();
	if (metw50_branch != 0) metw50();
	if (metw120_branch != 0) metw120();
	if (btagw_branch != 0) btagw();
	if (pt1w_branch != 0) pt1w();
	if (pt2w_branch != 0) pt2w();
	if (htw200_branch != 0) htw200();
	if (htw320_branch != 0) htw320();
	if (lep1_gen_p4_branch != 0) lep1_gen_p4();
	if (lep1_p4_branch != 0) lep1_p4();
	if (lep2_gen_p4_branch != 0) lep2_gen_p4();
	if (lep2_p4_branch != 0) lep2_p4();
	if (gen_vbjets_p4_branch != 0) gen_vbjets_p4();
	if (gen_vbjets_matched_branch != 0) gen_vbjets_matched();
	if (gen_vjets_p4_branch != 0) gen_vjets_p4();
	if (gen_vjets_matched_branch != 0) gen_vjets_matched();
	if (reco_vbjets_p4_branch != 0) reco_vbjets_p4();
	if (reco_vjets_p4_branch != 0) reco_vjets_p4();
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
	bool &	gen_is_ss()
	{
		if (not gen_is_ss_isLoaded) {
			if (gen_is_ss_branch != 0) {
				gen_is_ss_branch->GetEntry(index);
			} else { 
				printf("branch gen_is_ss_branch does not exist!\n");
				exit(1);
			}
			gen_is_ss_isLoaded = true;
		}
		return gen_is_ss_;
	}
	bool &	gen_is_os()
	{
		if (not gen_is_os_isLoaded) {
			if (gen_is_os_branch != 0) {
				gen_is_os_branch->GetEntry(index);
			} else { 
				printf("branch gen_is_os_branch does not exist!\n");
				exit(1);
			}
			gen_is_os_isLoaded = true;
		}
		return gen_is_os_;
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
	float &reco_ht()
	{
		if (not reco_ht_isLoaded) {
			if (reco_ht_branch != 0) {
				reco_ht_branch->GetEntry(index);
			} else { 
				printf("branch reco_ht_branch does not exist!\n");
				exit(1);
			}
			reco_ht_isLoaded = true;
		}
		return reco_ht_;
	}
	float &reco_met()
	{
		if (not reco_met_isLoaded) {
			if (reco_met_branch != 0) {
				reco_met_branch->GetEntry(index);
			} else { 
				printf("branch reco_met_branch does not exist!\n");
				exit(1);
			}
			reco_met_isLoaded = true;
		}
		return reco_met_;
	}
	int &reco_nbtags()
	{
		if (not reco_nbtags_isLoaded) {
			if (reco_nbtags_branch != 0) {
				reco_nbtags_branch->GetEntry(index);
			} else { 
				printf("branch reco_nbtags_branch does not exist!\n");
				exit(1);
			}
			reco_nbtags_isLoaded = true;
		}
		return reco_nbtags_;
	}
	int &reco_njets()
	{
		if (not reco_njets_isLoaded) {
			if (reco_njets_branch != 0) {
				reco_njets_branch->GetEntry(index);
			} else { 
				printf("branch reco_njets_branch does not exist!\n");
				exit(1);
			}
			reco_njets_isLoaded = true;
		}
		return reco_njets_;
	}
	float &reco_is_ss()
	{
		if (not reco_is_ss_isLoaded) {
			if (reco_is_ss_branch != 0) {
				reco_is_ss_branch->GetEntry(index);
			} else { 
				printf("branch reco_is_ss_branch does not exist!\n");
				exit(1);
			}
			reco_is_ss_isLoaded = true;
		}
		return reco_is_ss_;
	}
	float &reco_is_os()
	{
		if (not reco_is_os_isLoaded) {
			if (reco_is_os_branch != 0) {
				reco_is_os_branch->GetEntry(index);
			} else { 
				printf("branch reco_is_os_branch does not exist!\n");
				exit(1);
			}
			reco_is_os_isLoaded = true;
		}
		return reco_is_os_;
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
	int &lep1_gen_pdgid()
	{
		if (not lep1_gen_pdgid_isLoaded) {
			if (lep1_gen_pdgid_branch != 0) {
				lep1_gen_pdgid_branch->GetEntry(index);
			} else { 
				printf("branch lep1_gen_pdgid_branch does not exist!\n");
				exit(1);
			}
			lep1_gen_pdgid_isLoaded = true;
		}
		return lep1_gen_pdgid_;
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
	bool &	lep1_matched()
	{
		if (not lep1_matched_isLoaded) {
			if (lep1_matched_branch != 0) {
				lep1_matched_branch->GetEntry(index);
			} else { 
				printf("branch lep1_matched_branch does not exist!\n");
				exit(1);
			}
			lep1_matched_isLoaded = true;
		}
		return lep1_matched_;
	}
	bool &	lep1_from_tau()
	{
		if (not lep1_from_tau_isLoaded) {
			if (lep1_from_tau_branch != 0) {
				lep1_from_tau_branch->GetEntry(index);
			} else { 
				printf("branch lep1_from_tau_branch does not exist!\n");
				exit(1);
			}
			lep1_from_tau_isLoaded = true;
		}
		return lep1_from_tau_;
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
	bool &	lep1_num()
	{
		if (not lep1_num_isLoaded) {
			if (lep1_num_branch != 0) {
				lep1_num_branch->GetEntry(index);
			} else { 
				printf("branch lep1_num_branch does not exist!\n");
				exit(1);
			}
			lep1_num_isLoaded = true;
		}
		return lep1_num_;
	}
	float &lep1_iso()
	{
		if (not lep1_iso_isLoaded) {
			if (lep1_iso_branch != 0) {
				lep1_iso_branch->GetEntry(index);
			} else { 
				printf("branch lep1_iso_branch does not exist!\n");
				exit(1);
			}
			lep1_iso_isLoaded = true;
		}
		return lep1_iso_;
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
	int &lep2_gen_pdgid()
	{
		if (not lep2_gen_pdgid_isLoaded) {
			if (lep2_gen_pdgid_branch != 0) {
				lep2_gen_pdgid_branch->GetEntry(index);
			} else { 
				printf("branch lep2_gen_pdgid_branch does not exist!\n");
				exit(1);
			}
			lep2_gen_pdgid_isLoaded = true;
		}
		return lep2_gen_pdgid_;
	}
	bool &	lep2_matched()
	{
		if (not lep2_matched_isLoaded) {
			if (lep2_matched_branch != 0) {
				lep2_matched_branch->GetEntry(index);
			} else { 
				printf("branch lep2_matched_branch does not exist!\n");
				exit(1);
			}
			lep2_matched_isLoaded = true;
		}
		return lep2_matched_;
	}
	bool &	lep2_from_tau()
	{
		if (not lep2_from_tau_isLoaded) {
			if (lep2_from_tau_branch != 0) {
				lep2_from_tau_branch->GetEntry(index);
			} else { 
				printf("branch lep2_from_tau_branch does not exist!\n");
				exit(1);
			}
			lep2_from_tau_isLoaded = true;
		}
		return lep2_from_tau_;
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
	bool &	lep2_num()
	{
		if (not lep2_num_isLoaded) {
			if (lep2_num_branch != 0) {
				lep2_num_branch->GetEntry(index);
			} else { 
				printf("branch lep2_num_branch does not exist!\n");
				exit(1);
			}
			lep2_num_isLoaded = true;
		}
		return lep2_num_;
	}
	float &lep2_iso()
	{
		if (not lep2_iso_isLoaded) {
			if (lep2_iso_branch != 0) {
				lep2_iso_branch->GetEntry(index);
			} else { 
				printf("branch lep2_iso_branch does not exist!\n");
				exit(1);
			}
			lep2_iso_isLoaded = true;
		}
		return lep2_iso_;
	}
	float &metw30()
	{
		if (not metw30_isLoaded) {
			if (metw30_branch != 0) {
				metw30_branch->GetEntry(index);
			} else { 
				printf("branch metw30_branch does not exist!\n");
				exit(1);
			}
			metw30_isLoaded = true;
		}
		return metw30_;
	}
	float &metw50()
	{
		if (not metw50_isLoaded) {
			if (metw50_branch != 0) {
				metw50_branch->GetEntry(index);
			} else { 
				printf("branch metw50_branch does not exist!\n");
				exit(1);
			}
			metw50_isLoaded = true;
		}
		return metw50_;
	}
	float &metw120()
	{
		if (not metw120_isLoaded) {
			if (metw120_branch != 0) {
				metw120_branch->GetEntry(index);
			} else { 
				printf("branch metw120_branch does not exist!\n");
				exit(1);
			}
			metw120_isLoaded = true;
		}
		return metw120_;
	}
	float &btagw()
	{
		if (not btagw_isLoaded) {
			if (btagw_branch != 0) {
				btagw_branch->GetEntry(index);
			} else { 
				printf("branch btagw_branch does not exist!\n");
				exit(1);
			}
			btagw_isLoaded = true;
		}
		return btagw_;
	}
	float &pt1w()
	{
		if (not pt1w_isLoaded) {
			if (pt1w_branch != 0) {
				pt1w_branch->GetEntry(index);
			} else { 
				printf("branch pt1w_branch does not exist!\n");
				exit(1);
			}
			pt1w_isLoaded = true;
		}
		return pt1w_;
	}
	float &pt2w()
	{
		if (not pt2w_isLoaded) {
			if (pt2w_branch != 0) {
				pt2w_branch->GetEntry(index);
			} else { 
				printf("branch pt2w_branch does not exist!\n");
				exit(1);
			}
			pt2w_isLoaded = true;
		}
		return pt2w_;
	}
	float &htw200()
	{
		if (not htw200_isLoaded) {
			if (htw200_branch != 0) {
				htw200_branch->GetEntry(index);
			} else { 
				printf("branch htw200_branch does not exist!\n");
				exit(1);
			}
			htw200_isLoaded = true;
		}
		return htw200_;
	}
	float &htw320()
	{
		if (not htw320_isLoaded) {
			if (htw320_branch != 0) {
				htw320_branch->GetEntry(index);
			} else { 
				printf("branch htw320_branch does not exist!\n");
				exit(1);
			}
			htw320_isLoaded = true;
		}
		return htw320_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_gen_p4()
	{
		if (not lep1_gen_p4_isLoaded) {
			if (lep1_gen_p4_branch != 0) {
				lep1_gen_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep1_gen_p4_branch does not exist!\n");
				exit(1);
			}
			lep1_gen_p4_isLoaded = true;
		}
		return *lep1_gen_p4_;
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
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_gen_p4()
	{
		if (not lep2_gen_p4_isLoaded) {
			if (lep2_gen_p4_branch != 0) {
				lep2_gen_p4_branch->GetEntry(index);
			} else { 
				printf("branch lep2_gen_p4_branch does not exist!\n");
				exit(1);
			}
			lep2_gen_p4_isLoaded = true;
		}
		return *lep2_gen_p4_;
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
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gen_vbjets_p4()
	{
		if (not gen_vbjets_p4_isLoaded) {
			if (gen_vbjets_p4_branch != 0) {
				gen_vbjets_p4_branch->GetEntry(index);
			} else { 
				printf("branch gen_vbjets_p4_branch does not exist!\n");
				exit(1);
			}
			gen_vbjets_p4_isLoaded = true;
		}
		return *gen_vbjets_p4_;
	}
	vector<bool> &gen_vbjets_matched()
	{
		if (not gen_vbjets_matched_isLoaded) {
			if (gen_vbjets_matched_branch != 0) {
				gen_vbjets_matched_branch->GetEntry(index);
			} else { 
				printf("branch gen_vbjets_matched_branch does not exist!\n");
				exit(1);
			}
			gen_vbjets_matched_isLoaded = true;
		}
		return *gen_vbjets_matched_;
	}
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gen_vjets_p4()
	{
		if (not gen_vjets_p4_isLoaded) {
			if (gen_vjets_p4_branch != 0) {
				gen_vjets_p4_branch->GetEntry(index);
			} else { 
				printf("branch gen_vjets_p4_branch does not exist!\n");
				exit(1);
			}
			gen_vjets_p4_isLoaded = true;
		}
		return *gen_vjets_p4_;
	}
	vector<bool> &gen_vjets_matched()
	{
		if (not gen_vjets_matched_isLoaded) {
			if (gen_vjets_matched_branch != 0) {
				gen_vjets_matched_branch->GetEntry(index);
			} else { 
				printf("branch gen_vjets_matched_branch does not exist!\n");
				exit(1);
			}
			gen_vjets_matched_isLoaded = true;
		}
		return *gen_vjets_matched_;
	}
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &reco_vbjets_p4()
	{
		if (not reco_vbjets_p4_isLoaded) {
			if (reco_vbjets_p4_branch != 0) {
				reco_vbjets_p4_branch->GetEntry(index);
			} else { 
				printf("branch reco_vbjets_p4_branch does not exist!\n");
				exit(1);
			}
			reco_vbjets_p4_isLoaded = true;
		}
		return *reco_vbjets_p4_;
	}
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &reco_vjets_p4()
	{
		if (not reco_vjets_p4_isLoaded) {
			if (reco_vjets_p4_branch != 0) {
				reco_vjets_p4_branch->GetEntry(index);
			} else { 
				printf("branch reco_vjets_p4_branch does not exist!\n");
				exit(1);
			}
			reco_vjets_p4_isLoaded = true;
		}
		return *reco_vjets_p4_;
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
extern OutreachBaby outreach_baby;
#endif

namespace orb {
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
	int &gen_dilep_type();
	float &gen_ht();
	int &gen_nbtags();
	int &gen_njets();
	bool &gen_is_ss();
	bool &gen_is_os();
	int &dilep_type();
	float &reco_ht();
	float &reco_met();
	int &reco_nbtags();
	int &reco_njets();
	float &reco_is_ss();
	float &reco_is_os();
	float &sf_dileptrig();
	float &sf_lepeff();
	float &sf_nbtag();
	float &sf_nbtag3();
	float &sparm0();
	float &sparm1();
	float &sparm2();
	float &sparm3();
	int &lep1_gen_pdgid();
	int &lep1_pdgid();
	bool &lep1_matched();
	bool &lep1_from_tau();
	bool &lep1_passes_id();
	bool &lep1_passes_iso();
	bool &lep1_num();
	float &lep1_iso();
	int &lep2_pdgid();
	int &lep2_gen_pdgid();
	bool &lep2_matched();
	bool &lep2_from_tau();
	bool &lep2_passes_id();
	bool &lep2_passes_iso();
	bool &lep2_num();
	float &lep2_iso();
	float &metw30();
	float &metw50();
	float &metw120();
	float &btagw();
	float &pt1w();
	float &pt2w();
	float &htw200();
	float &htw320();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_gen_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_gen_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_p4();
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gen_vbjets_p4();
	vector<bool> &gen_vbjets_matched();
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gen_vjets_p4();
	vector<bool> &gen_vjets_matched();
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &reco_vbjets_p4();
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &reco_vjets_p4();
}
#endif
