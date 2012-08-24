// -*- C++ -*-
#ifndef SSB_H
#define SSB_H
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
	float	scale_;
	TBranch *scale_branch;
	bool scale_isLoaded;
	float	scale1fb_;
	TBranch *scale1fb_branch;
	bool scale1fb_isLoaded;
	unsigned int	type_;
	TBranch *type_branch;
	bool type_isLoaded;
	unsigned int	nvtxs_;
	TBranch *nvtxs_branch;
	bool nvtxs_isLoaded;
	float	vtxw_;
	TBranch *vtxw_branch;
	bool vtxw_isLoaded;
	unsigned int	njets_;
	TBranch *njets_branch;
	bool njets_isLoaded;
	unsigned int	njets20_;
	TBranch *njets20_branch;
	bool njets20_isLoaded;
	unsigned int	njets30_;
	TBranch *njets30_branch;
	bool njets30_isLoaded;
	unsigned int	nbtags_;
	TBranch *nbtags_branch;
	bool nbtags_isLoaded;
	unsigned int	nbtags20_;
	TBranch *nbtags20_branch;
	bool nbtags20_isLoaded;
	unsigned int	nbtags30_;
	TBranch *nbtags30_branch;
	bool nbtags30_isLoaded;
	float	pfmet_;
	TBranch *pfmet_branch;
	bool pfmet_isLoaded;
	float	ht_;
	TBranch *ht_branch;
	bool ht_isLoaded;
	float	ht20_;
	TBranch *ht20_branch;
	bool ht20_isLoaded;
	float	ht30_;
	TBranch *ht30_branch;
	bool ht30_isLoaded;
	float	mass_;
	TBranch *mass_branch;
	bool mass_isLoaded;
	float	mt_;
	TBranch *mt_branch;
	bool mt_isLoaded;
	bool	trig_mm_;
	TBranch *trig_mm_branch;
	bool trig_mm_isLoaded;
	bool	trig_em_;
	TBranch *trig_em_branch;
	bool trig_em_isLoaded;
	bool	trig_ee_;
	TBranch *trig_ee_branch;
	bool trig_ee_isLoaded;
	int	gen_sign_;
	TBranch *gen_sign_branch;
	bool gen_sign_isLoaded;
	int	gen_type_;
	TBranch *gen_type_branch;
	bool gen_type_isLoaded;
	float	gen_ht_;
	TBranch *gen_ht_branch;
	bool gen_ht_isLoaded;
	float	gen_met_;
	TBranch *gen_met_branch;
	bool gen_met_isLoaded;
	float	rho_;
	TBranch *rho_branch;
	bool rho_isLoaded;
	float	pt1_;
	TBranch *pt1_branch;
	bool pt1_isLoaded;
	float	eta1_;
	TBranch *eta1_branch;
	bool eta1_isLoaded;
	int	id1_;
	TBranch *id1_branch;
	bool id1_isLoaded;
	float	iso1_;
	TBranch *iso1_branch;
	bool iso1_isLoaded;
	float	iso_ch_1_;
	TBranch *iso_ch_1_branch;
	bool iso_ch_1_isLoaded;
	float	iso_em_1_;
	TBranch *iso_em_1_branch;
	bool iso_em_1_isLoaded;
	float	iso_nh_1_;
	TBranch *iso_nh_1_branch;
	bool iso_nh_1_isLoaded;
	float	aeff1_;
	TBranch *aeff1_branch;
	bool aeff1_isLoaded;
	float	dbeta1_;
	TBranch *dbeta1_branch;
	bool dbeta1_isLoaded;
	bool	num1_;
	TBranch *num1_branch;
	bool num1_isLoaded;
	bool	fo1_;
	TBranch *fo1_branch;
	bool fo1_isLoaded;
	float	wfr1_;
	TBranch *wfr1_branch;
	bool wfr1_isLoaded;
	float	wflip1_;
	TBranch *wflip1_branch;
	bool wflip1_isLoaded;
	int	leptru1_;
	TBranch *leptru1_branch;
	bool leptru1_isLoaded;
	float	pt2_;
	TBranch *pt2_branch;
	bool pt2_isLoaded;
	float	eta2_;
	TBranch *eta2_branch;
	bool eta2_isLoaded;
	float	iso2_;
	TBranch *iso2_branch;
	bool iso2_isLoaded;
	float	iso_ch_2_;
	TBranch *iso_ch_2_branch;
	bool iso_ch_2_isLoaded;
	float	iso_em_2_;
	TBranch *iso_em_2_branch;
	bool iso_em_2_isLoaded;
	float	iso_nh_2_;
	TBranch *iso_nh_2_branch;
	bool iso_nh_2_isLoaded;
	int	aeff2_;
	TBranch *aeff2_branch;
	bool aeff2_isLoaded;
	float	dbeta2_;
	TBranch *dbeta2_branch;
	bool dbeta2_isLoaded;
	bool	num2_;
	TBranch *num2_branch;
	bool num2_isLoaded;
	bool	fo2_;
	TBranch *fo2_branch;
	bool fo2_isLoaded;
	int	id2_;
	TBranch *id2_branch;
	bool id2_isLoaded;
	float	wfr2_;
	TBranch *wfr2_branch;
	bool wfr2_isLoaded;
	float	wflip2_;
	TBranch *wflip2_branch;
	bool wflip2_isLoaded;
	int	leptru2_;
	TBranch *leptru2_branch;
	bool leptru2_isLoaded;
	bool	isSS_;
	TBranch *isSS_branch;
	bool isSS_isLoaded;
	bool	isSF_;
	TBranch *isSF_branch;
	bool isSF_isLoaded;
	bool	isDF_;
	TBranch *isDF_branch;
	bool isDF_isLoaded;
	bool	isOS_;
	TBranch *isOS_branch;
	bool isOS_isLoaded;
	float	trig_eff_;
	TBranch *trig_eff_branch;
	bool trig_eff_isLoaded;
	float	scale_nbtag_;
	TBranch *scale_nbtag_branch;
	bool scale_nbtag_isLoaded;
	float	scale_nbtag3_;
	TBranch *scale_nbtag3_branch;
	bool scale_nbtag3_isLoaded;
	float	scale_unc_nbtag_;
	TBranch *scale_unc_nbtag_branch;
	bool scale_unc_nbtag_isLoaded;
	float	scale_unc_nbtag3_;
	TBranch *scale_unc_nbtag3_branch;
	bool scale_unc_nbtag3_isLoaded;
	float	scale_tap_;
	TBranch *scale_tap_branch;
	bool scale_tap_isLoaded;
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
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *gen_lep1_p4_;
	TBranch *gen_lep1_p4_branch;
	bool gen_lep1_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *gen_lep2_p4_;
	TBranch *gen_lep2_p4_branch;
	bool gen_lep2_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *gen_b1_p4_;
	TBranch *gen_b1_p4_branch;
	bool gen_b1_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *gen_b2_p4_;
	TBranch *gen_b2_p4_branch;
	bool gen_b2_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *gen_b3_p4_;
	TBranch *gen_b3_p4_branch;
	bool gen_b3_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *gen_b4_p4_;
	TBranch *gen_b4_p4_branch;
	bool gen_b4_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep1_p4_;
	TBranch *lep1_p4_branch;
	bool lep1_p4_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *lep2_p4_;
	TBranch *lep2_p4_branch;
	bool lep2_p4_isLoaded;
public: 
void Init(TTree *tree) {
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
	gen_b1_p4_branch = 0;
	if (tree->GetBranch("gen_b1_p4") != 0) {
		gen_b1_p4_branch = tree->GetBranch("gen_b1_p4");
		gen_b1_p4_branch->SetAddress(&gen_b1_p4_);
	}
	gen_b2_p4_branch = 0;
	if (tree->GetBranch("gen_b2_p4") != 0) {
		gen_b2_p4_branch = tree->GetBranch("gen_b2_p4");
		gen_b2_p4_branch->SetAddress(&gen_b2_p4_);
	}
	gen_b3_p4_branch = 0;
	if (tree->GetBranch("gen_b3_p4") != 0) {
		gen_b3_p4_branch = tree->GetBranch("gen_b3_p4");
		gen_b3_p4_branch->SetAddress(&gen_b3_p4_);
	}
	gen_b4_p4_branch = 0;
	if (tree->GetBranch("gen_b4_p4") != 0) {
		gen_b4_p4_branch = tree->GetBranch("gen_b4_p4");
		gen_b4_p4_branch->SetAddress(&gen_b4_p4_);
	}
	lep1_p4_branch = 0;
	if (tree->GetBranch("lep1_p4") != 0) {
		lep1_p4_branch = tree->GetBranch("lep1_p4");
		lep1_p4_branch->SetAddress(&lep1_p4_);
	}
	lep2_p4_branch = 0;
	if (tree->GetBranch("lep2_p4") != 0) {
		lep2_p4_branch = tree->GetBranch("lep2_p4");
		lep2_p4_branch->SetAddress(&lep2_p4_);
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
	scale_branch = 0;
	if (tree->GetBranch("scale") != 0) {
		scale_branch = tree->GetBranch("scale");
		scale_branch->SetAddress(&scale_);
	}
	scale1fb_branch = 0;
	if (tree->GetBranch("scale1fb") != 0) {
		scale1fb_branch = tree->GetBranch("scale1fb");
		scale1fb_branch->SetAddress(&scale1fb_);
	}
	type_branch = 0;
	if (tree->GetBranch("type") != 0) {
		type_branch = tree->GetBranch("type");
		type_branch->SetAddress(&type_);
	}
	nvtxs_branch = 0;
	if (tree->GetBranch("nvtxs") != 0) {
		nvtxs_branch = tree->GetBranch("nvtxs");
		nvtxs_branch->SetAddress(&nvtxs_);
	}
	vtxw_branch = 0;
	if (tree->GetBranch("vtxw") != 0) {
		vtxw_branch = tree->GetBranch("vtxw");
		vtxw_branch->SetAddress(&vtxw_);
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
	pfmet_branch = 0;
	if (tree->GetBranch("pfmet") != 0) {
		pfmet_branch = tree->GetBranch("pfmet");
		pfmet_branch->SetAddress(&pfmet_);
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
	mass_branch = 0;
	if (tree->GetBranch("mass") != 0) {
		mass_branch = tree->GetBranch("mass");
		mass_branch->SetAddress(&mass_);
	}
	mt_branch = 0;
	if (tree->GetBranch("mt") != 0) {
		mt_branch = tree->GetBranch("mt");
		mt_branch->SetAddress(&mt_);
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
	gen_sign_branch = 0;
	if (tree->GetBranch("gen_sign") != 0) {
		gen_sign_branch = tree->GetBranch("gen_sign");
		gen_sign_branch->SetAddress(&gen_sign_);
	}
	gen_type_branch = 0;
	if (tree->GetBranch("gen_type") != 0) {
		gen_type_branch = tree->GetBranch("gen_type");
		gen_type_branch->SetAddress(&gen_type_);
	}
	gen_ht_branch = 0;
	if (tree->GetBranch("gen_ht") != 0) {
		gen_ht_branch = tree->GetBranch("gen_ht");
		gen_ht_branch->SetAddress(&gen_ht_);
	}
	gen_met_branch = 0;
	if (tree->GetBranch("gen_met") != 0) {
		gen_met_branch = tree->GetBranch("gen_met");
		gen_met_branch->SetAddress(&gen_met_);
	}
	rho_branch = 0;
	if (tree->GetBranch("rho") != 0) {
		rho_branch = tree->GetBranch("rho");
		rho_branch->SetAddress(&rho_);
	}
	pt1_branch = 0;
	if (tree->GetBranch("pt1") != 0) {
		pt1_branch = tree->GetBranch("pt1");
		pt1_branch->SetAddress(&pt1_);
	}
	eta1_branch = 0;
	if (tree->GetBranch("eta1") != 0) {
		eta1_branch = tree->GetBranch("eta1");
		eta1_branch->SetAddress(&eta1_);
	}
	id1_branch = 0;
	if (tree->GetBranch("id1") != 0) {
		id1_branch = tree->GetBranch("id1");
		id1_branch->SetAddress(&id1_);
	}
	iso1_branch = 0;
	if (tree->GetBranch("iso1") != 0) {
		iso1_branch = tree->GetBranch("iso1");
		iso1_branch->SetAddress(&iso1_);
	}
	iso_ch_1_branch = 0;
	if (tree->GetBranch("iso_ch_1") != 0) {
		iso_ch_1_branch = tree->GetBranch("iso_ch_1");
		iso_ch_1_branch->SetAddress(&iso_ch_1_);
	}
	iso_em_1_branch = 0;
	if (tree->GetBranch("iso_em_1") != 0) {
		iso_em_1_branch = tree->GetBranch("iso_em_1");
		iso_em_1_branch->SetAddress(&iso_em_1_);
	}
	iso_nh_1_branch = 0;
	if (tree->GetBranch("iso_nh_1") != 0) {
		iso_nh_1_branch = tree->GetBranch("iso_nh_1");
		iso_nh_1_branch->SetAddress(&iso_nh_1_);
	}
	aeff1_branch = 0;
	if (tree->GetBranch("aeff1") != 0) {
		aeff1_branch = tree->GetBranch("aeff1");
		aeff1_branch->SetAddress(&aeff1_);
	}
	dbeta1_branch = 0;
	if (tree->GetBranch("dbeta1") != 0) {
		dbeta1_branch = tree->GetBranch("dbeta1");
		dbeta1_branch->SetAddress(&dbeta1_);
	}
	num1_branch = 0;
	if (tree->GetBranch("num1") != 0) {
		num1_branch = tree->GetBranch("num1");
		num1_branch->SetAddress(&num1_);
	}
	fo1_branch = 0;
	if (tree->GetBranch("fo1") != 0) {
		fo1_branch = tree->GetBranch("fo1");
		fo1_branch->SetAddress(&fo1_);
	}
	wfr1_branch = 0;
	if (tree->GetBranch("wfr1") != 0) {
		wfr1_branch = tree->GetBranch("wfr1");
		wfr1_branch->SetAddress(&wfr1_);
	}
	wflip1_branch = 0;
	if (tree->GetBranch("wflip1") != 0) {
		wflip1_branch = tree->GetBranch("wflip1");
		wflip1_branch->SetAddress(&wflip1_);
	}
	leptru1_branch = 0;
	if (tree->GetBranch("leptru1") != 0) {
		leptru1_branch = tree->GetBranch("leptru1");
		leptru1_branch->SetAddress(&leptru1_);
	}
	pt2_branch = 0;
	if (tree->GetBranch("pt2") != 0) {
		pt2_branch = tree->GetBranch("pt2");
		pt2_branch->SetAddress(&pt2_);
	}
	eta2_branch = 0;
	if (tree->GetBranch("eta2") != 0) {
		eta2_branch = tree->GetBranch("eta2");
		eta2_branch->SetAddress(&eta2_);
	}
	iso2_branch = 0;
	if (tree->GetBranch("iso2") != 0) {
		iso2_branch = tree->GetBranch("iso2");
		iso2_branch->SetAddress(&iso2_);
	}
	iso_ch_2_branch = 0;
	if (tree->GetBranch("iso_ch_2") != 0) {
		iso_ch_2_branch = tree->GetBranch("iso_ch_2");
		iso_ch_2_branch->SetAddress(&iso_ch_2_);
	}
	iso_em_2_branch = 0;
	if (tree->GetBranch("iso_em_2") != 0) {
		iso_em_2_branch = tree->GetBranch("iso_em_2");
		iso_em_2_branch->SetAddress(&iso_em_2_);
	}
	iso_nh_2_branch = 0;
	if (tree->GetBranch("iso_nh_2") != 0) {
		iso_nh_2_branch = tree->GetBranch("iso_nh_2");
		iso_nh_2_branch->SetAddress(&iso_nh_2_);
	}
	aeff2_branch = 0;
	if (tree->GetBranch("aeff2") != 0) {
		aeff2_branch = tree->GetBranch("aeff2");
		aeff2_branch->SetAddress(&aeff2_);
	}
	dbeta2_branch = 0;
	if (tree->GetBranch("dbeta2") != 0) {
		dbeta2_branch = tree->GetBranch("dbeta2");
		dbeta2_branch->SetAddress(&dbeta2_);
	}
	num2_branch = 0;
	if (tree->GetBranch("num2") != 0) {
		num2_branch = tree->GetBranch("num2");
		num2_branch->SetAddress(&num2_);
	}
	fo2_branch = 0;
	if (tree->GetBranch("fo2") != 0) {
		fo2_branch = tree->GetBranch("fo2");
		fo2_branch->SetAddress(&fo2_);
	}
	id2_branch = 0;
	if (tree->GetBranch("id2") != 0) {
		id2_branch = tree->GetBranch("id2");
		id2_branch->SetAddress(&id2_);
	}
	wfr2_branch = 0;
	if (tree->GetBranch("wfr2") != 0) {
		wfr2_branch = tree->GetBranch("wfr2");
		wfr2_branch->SetAddress(&wfr2_);
	}
	wflip2_branch = 0;
	if (tree->GetBranch("wflip2") != 0) {
		wflip2_branch = tree->GetBranch("wflip2");
		wflip2_branch->SetAddress(&wflip2_);
	}
	leptru2_branch = 0;
	if (tree->GetBranch("leptru2") != 0) {
		leptru2_branch = tree->GetBranch("leptru2");
		leptru2_branch->SetAddress(&leptru2_);
	}
	isSS_branch = 0;
	if (tree->GetBranch("isSS") != 0) {
		isSS_branch = tree->GetBranch("isSS");
		isSS_branch->SetAddress(&isSS_);
	}
	isSF_branch = 0;
	if (tree->GetBranch("isSF") != 0) {
		isSF_branch = tree->GetBranch("isSF");
		isSF_branch->SetAddress(&isSF_);
	}
	isDF_branch = 0;
	if (tree->GetBranch("isDF") != 0) {
		isDF_branch = tree->GetBranch("isDF");
		isDF_branch->SetAddress(&isDF_);
	}
	isOS_branch = 0;
	if (tree->GetBranch("isOS") != 0) {
		isOS_branch = tree->GetBranch("isOS");
		isOS_branch->SetAddress(&isOS_);
	}
	trig_eff_branch = 0;
	if (tree->GetBranch("trig_eff") != 0) {
		trig_eff_branch = tree->GetBranch("trig_eff");
		trig_eff_branch->SetAddress(&trig_eff_);
	}
	scale_nbtag_branch = 0;
	if (tree->GetBranch("scale_nbtag") != 0) {
		scale_nbtag_branch = tree->GetBranch("scale_nbtag");
		scale_nbtag_branch->SetAddress(&scale_nbtag_);
	}
	scale_nbtag3_branch = 0;
	if (tree->GetBranch("scale_nbtag3") != 0) {
		scale_nbtag3_branch = tree->GetBranch("scale_nbtag3");
		scale_nbtag3_branch->SetAddress(&scale_nbtag3_);
	}
	scale_unc_nbtag_branch = 0;
	if (tree->GetBranch("scale_unc_nbtag") != 0) {
		scale_unc_nbtag_branch = tree->GetBranch("scale_unc_nbtag");
		scale_unc_nbtag_branch->SetAddress(&scale_unc_nbtag_);
	}
	scale_unc_nbtag3_branch = 0;
	if (tree->GetBranch("scale_unc_nbtag3") != 0) {
		scale_unc_nbtag3_branch = tree->GetBranch("scale_unc_nbtag3");
		scale_unc_nbtag3_branch->SetAddress(&scale_unc_nbtag3_);
	}
	scale_tap_branch = 0;
	if (tree->GetBranch("scale_tap") != 0) {
		scale_tap_branch = tree->GetBranch("scale_tap");
		scale_tap_branch->SetAddress(&scale_tap_);
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
  tree->SetMakeClass(0);
}
void GetEntry(unsigned int idx) 
	// this only marks branches as not loaded, saving a lot of time
	{
		index = idx;
		run_isLoaded = false;
		ls_isLoaded = false;
		evt_isLoaded = false;
		scale_isLoaded = false;
		scale1fb_isLoaded = false;
		type_isLoaded = false;
		nvtxs_isLoaded = false;
		vtxw_isLoaded = false;
		njets_isLoaded = false;
		njets20_isLoaded = false;
		njets30_isLoaded = false;
		nbtags_isLoaded = false;
		nbtags20_isLoaded = false;
		nbtags30_isLoaded = false;
		pfmet_isLoaded = false;
		ht_isLoaded = false;
		ht20_isLoaded = false;
		ht30_isLoaded = false;
		mass_isLoaded = false;
		mt_isLoaded = false;
		trig_mm_isLoaded = false;
		trig_em_isLoaded = false;
		trig_ee_isLoaded = false;
		gen_sign_isLoaded = false;
		gen_type_isLoaded = false;
		gen_ht_isLoaded = false;
		gen_met_isLoaded = false;
		rho_isLoaded = false;
		pt1_isLoaded = false;
		eta1_isLoaded = false;
		id1_isLoaded = false;
		iso1_isLoaded = false;
		iso_ch_1_isLoaded = false;
		iso_em_1_isLoaded = false;
		iso_nh_1_isLoaded = false;
		aeff1_isLoaded = false;
		dbeta1_isLoaded = false;
		num1_isLoaded = false;
		fo1_isLoaded = false;
		wfr1_isLoaded = false;
		wflip1_isLoaded = false;
		leptru1_isLoaded = false;
		pt2_isLoaded = false;
		eta2_isLoaded = false;
		iso2_isLoaded = false;
		iso_ch_2_isLoaded = false;
		iso_em_2_isLoaded = false;
		iso_nh_2_isLoaded = false;
		aeff2_isLoaded = false;
		dbeta2_isLoaded = false;
		num2_isLoaded = false;
		fo2_isLoaded = false;
		id2_isLoaded = false;
		wfr2_isLoaded = false;
		wflip2_isLoaded = false;
		leptru2_isLoaded = false;
		isSS_isLoaded = false;
		isSF_isLoaded = false;
		isDF_isLoaded = false;
		isOS_isLoaded = false;
		trig_eff_isLoaded = false;
		scale_nbtag_isLoaded = false;
		scale_nbtag3_isLoaded = false;
		scale_unc_nbtag_isLoaded = false;
		scale_unc_nbtag3_isLoaded = false;
		scale_tap_isLoaded = false;
		sparm0_isLoaded = false;
		sparm1_isLoaded = false;
		sparm2_isLoaded = false;
		sparm3_isLoaded = false;
		gen_lep1_p4_isLoaded = false;
		gen_lep2_p4_isLoaded = false;
		gen_b1_p4_isLoaded = false;
		gen_b2_p4_isLoaded = false;
		gen_b3_p4_isLoaded = false;
		gen_b4_p4_isLoaded = false;
		lep1_p4_isLoaded = false;
		lep2_p4_isLoaded = false;
	}

void LoadAllBranches() 
	// load all branches
{
	if (run_branch != 0) run();
	if (ls_branch != 0) ls();
	if (evt_branch != 0) evt();
	if (scale_branch != 0) scale();
	if (scale1fb_branch != 0) scale1fb();
	if (type_branch != 0) type();
	if (nvtxs_branch != 0) nvtxs();
	if (vtxw_branch != 0) vtxw();
	if (njets_branch != 0) njets();
	if (njets20_branch != 0) njets20();
	if (njets30_branch != 0) njets30();
	if (nbtags_branch != 0) nbtags();
	if (nbtags20_branch != 0) nbtags20();
	if (nbtags30_branch != 0) nbtags30();
	if (pfmet_branch != 0) pfmet();
	if (ht_branch != 0) ht();
	if (ht20_branch != 0) ht20();
	if (ht30_branch != 0) ht30();
	if (mass_branch != 0) mass();
	if (mt_branch != 0) mt();
	if (trig_mm_branch != 0) trig_mm();
	if (trig_em_branch != 0) trig_em();
	if (trig_ee_branch != 0) trig_ee();
	if (gen_sign_branch != 0) gen_sign();
	if (gen_type_branch != 0) gen_type();
	if (gen_ht_branch != 0) gen_ht();
	if (gen_met_branch != 0) gen_met();
	if (rho_branch != 0) rho();
	if (pt1_branch != 0) pt1();
	if (eta1_branch != 0) eta1();
	if (id1_branch != 0) id1();
	if (iso1_branch != 0) iso1();
	if (iso_ch_1_branch != 0) iso_ch_1();
	if (iso_em_1_branch != 0) iso_em_1();
	if (iso_nh_1_branch != 0) iso_nh_1();
	if (aeff1_branch != 0) aeff1();
	if (dbeta1_branch != 0) dbeta1();
	if (num1_branch != 0) num1();
	if (fo1_branch != 0) fo1();
	if (wfr1_branch != 0) wfr1();
	if (wflip1_branch != 0) wflip1();
	if (leptru1_branch != 0) leptru1();
	if (pt2_branch != 0) pt2();
	if (eta2_branch != 0) eta2();
	if (iso2_branch != 0) iso2();
	if (iso_ch_2_branch != 0) iso_ch_2();
	if (iso_em_2_branch != 0) iso_em_2();
	if (iso_nh_2_branch != 0) iso_nh_2();
	if (aeff2_branch != 0) aeff2();
	if (dbeta2_branch != 0) dbeta2();
	if (num2_branch != 0) num2();
	if (fo2_branch != 0) fo2();
	if (id2_branch != 0) id2();
	if (wfr2_branch != 0) wfr2();
	if (wflip2_branch != 0) wflip2();
	if (leptru2_branch != 0) leptru2();
	if (isSS_branch != 0) isSS();
	if (isSF_branch != 0) isSF();
	if (isDF_branch != 0) isDF();
	if (isOS_branch != 0) isOS();
	if (trig_eff_branch != 0) trig_eff();
	if (scale_nbtag_branch != 0) scale_nbtag();
	if (scale_nbtag3_branch != 0) scale_nbtag3();
	if (scale_unc_nbtag_branch != 0) scale_unc_nbtag();
	if (scale_unc_nbtag3_branch != 0) scale_unc_nbtag3();
	if (scale_tap_branch != 0) scale_tap();
	if (sparm0_branch != 0) sparm0();
	if (sparm1_branch != 0) sparm1();
	if (sparm2_branch != 0) sparm2();
	if (sparm3_branch != 0) sparm3();
	if (gen_lep1_p4_branch != 0) gen_lep1_p4();
	if (gen_lep2_p4_branch != 0) gen_lep2_p4();
	if (gen_b1_p4_branch != 0) gen_b1_p4();
	if (gen_b2_p4_branch != 0) gen_b2_p4();
	if (gen_b3_p4_branch != 0) gen_b3_p4();
	if (gen_b4_p4_branch != 0) gen_b4_p4();
	if (lep1_p4_branch != 0) lep1_p4();
	if (lep2_p4_branch != 0) lep2_p4();
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
	float &scale()
	{
		if (not scale_isLoaded) {
			if (scale_branch != 0) {
				scale_branch->GetEntry(index);
			} else { 
				printf("branch scale_branch does not exist!\n");
				exit(1);
			}
			scale_isLoaded = true;
		}
		return scale_;
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
	unsigned int &type()
	{
		if (not type_isLoaded) {
			if (type_branch != 0) {
				type_branch->GetEntry(index);
			} else { 
				printf("branch type_branch does not exist!\n");
				exit(1);
			}
			type_isLoaded = true;
		}
		return type_;
	}
	unsigned int &nvtxs()
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
	unsigned int &njets()
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
	unsigned int &njets20()
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
	unsigned int &njets30()
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
	unsigned int &nbtags()
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
	unsigned int &nbtags20()
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
	unsigned int &nbtags30()
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
	float &mass()
	{
		if (not mass_isLoaded) {
			if (mass_branch != 0) {
				mass_branch->GetEntry(index);
			} else { 
				printf("branch mass_branch does not exist!\n");
				exit(1);
			}
			mass_isLoaded = true;
		}
		return mass_;
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
	int &gen_sign()
	{
		if (not gen_sign_isLoaded) {
			if (gen_sign_branch != 0) {
				gen_sign_branch->GetEntry(index);
			} else { 
				printf("branch gen_sign_branch does not exist!\n");
				exit(1);
			}
			gen_sign_isLoaded = true;
		}
		return gen_sign_;
	}
	int &gen_type()
	{
		if (not gen_type_isLoaded) {
			if (gen_type_branch != 0) {
				gen_type_branch->GetEntry(index);
			} else { 
				printf("branch gen_type_branch does not exist!\n");
				exit(1);
			}
			gen_type_isLoaded = true;
		}
		return gen_type_;
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
	float &pt1()
	{
		if (not pt1_isLoaded) {
			if (pt1_branch != 0) {
				pt1_branch->GetEntry(index);
			} else { 
				printf("branch pt1_branch does not exist!\n");
				exit(1);
			}
			pt1_isLoaded = true;
		}
		return pt1_;
	}
	float &eta1()
	{
		if (not eta1_isLoaded) {
			if (eta1_branch != 0) {
				eta1_branch->GetEntry(index);
			} else { 
				printf("branch eta1_branch does not exist!\n");
				exit(1);
			}
			eta1_isLoaded = true;
		}
		return eta1_;
	}
	int &id1()
	{
		if (not id1_isLoaded) {
			if (id1_branch != 0) {
				id1_branch->GetEntry(index);
			} else { 
				printf("branch id1_branch does not exist!\n");
				exit(1);
			}
			id1_isLoaded = true;
		}
		return id1_;
	}
	float &iso1()
	{
		if (not iso1_isLoaded) {
			if (iso1_branch != 0) {
				iso1_branch->GetEntry(index);
			} else { 
				printf("branch iso1_branch does not exist!\n");
				exit(1);
			}
			iso1_isLoaded = true;
		}
		return iso1_;
	}
	float &iso_ch_1()
	{
		if (not iso_ch_1_isLoaded) {
			if (iso_ch_1_branch != 0) {
				iso_ch_1_branch->GetEntry(index);
			} else { 
				printf("branch iso_ch_1_branch does not exist!\n");
				exit(1);
			}
			iso_ch_1_isLoaded = true;
		}
		return iso_ch_1_;
	}
	float &iso_em_1()
	{
		if (not iso_em_1_isLoaded) {
			if (iso_em_1_branch != 0) {
				iso_em_1_branch->GetEntry(index);
			} else { 
				printf("branch iso_em_1_branch does not exist!\n");
				exit(1);
			}
			iso_em_1_isLoaded = true;
		}
		return iso_em_1_;
	}
	float &iso_nh_1()
	{
		if (not iso_nh_1_isLoaded) {
			if (iso_nh_1_branch != 0) {
				iso_nh_1_branch->GetEntry(index);
			} else { 
				printf("branch iso_nh_1_branch does not exist!\n");
				exit(1);
			}
			iso_nh_1_isLoaded = true;
		}
		return iso_nh_1_;
	}
	float &aeff1()
	{
		if (not aeff1_isLoaded) {
			if (aeff1_branch != 0) {
				aeff1_branch->GetEntry(index);
			} else { 
				printf("branch aeff1_branch does not exist!\n");
				exit(1);
			}
			aeff1_isLoaded = true;
		}
		return aeff1_;
	}
	float &dbeta1()
	{
		if (not dbeta1_isLoaded) {
			if (dbeta1_branch != 0) {
				dbeta1_branch->GetEntry(index);
			} else { 
				printf("branch dbeta1_branch does not exist!\n");
				exit(1);
			}
			dbeta1_isLoaded = true;
		}
		return dbeta1_;
	}
	bool &	num1()
	{
		if (not num1_isLoaded) {
			if (num1_branch != 0) {
				num1_branch->GetEntry(index);
			} else { 
				printf("branch num1_branch does not exist!\n");
				exit(1);
			}
			num1_isLoaded = true;
		}
		return num1_;
	}
	bool &	fo1()
	{
		if (not fo1_isLoaded) {
			if (fo1_branch != 0) {
				fo1_branch->GetEntry(index);
			} else { 
				printf("branch fo1_branch does not exist!\n");
				exit(1);
			}
			fo1_isLoaded = true;
		}
		return fo1_;
	}
	float &wfr1()
	{
		if (not wfr1_isLoaded) {
			if (wfr1_branch != 0) {
				wfr1_branch->GetEntry(index);
			} else { 
				printf("branch wfr1_branch does not exist!\n");
				exit(1);
			}
			wfr1_isLoaded = true;
		}
		return wfr1_;
	}
	float &wflip1()
	{
		if (not wflip1_isLoaded) {
			if (wflip1_branch != 0) {
				wflip1_branch->GetEntry(index);
			} else { 
				printf("branch wflip1_branch does not exist!\n");
				exit(1);
			}
			wflip1_isLoaded = true;
		}
		return wflip1_;
	}
	int &leptru1()
	{
		if (not leptru1_isLoaded) {
			if (leptru1_branch != 0) {
				leptru1_branch->GetEntry(index);
			} else { 
				printf("branch leptru1_branch does not exist!\n");
				exit(1);
			}
			leptru1_isLoaded = true;
		}
		return leptru1_;
	}
	float &pt2()
	{
		if (not pt2_isLoaded) {
			if (pt2_branch != 0) {
				pt2_branch->GetEntry(index);
			} else { 
				printf("branch pt2_branch does not exist!\n");
				exit(1);
			}
			pt2_isLoaded = true;
		}
		return pt2_;
	}
	float &eta2()
	{
		if (not eta2_isLoaded) {
			if (eta2_branch != 0) {
				eta2_branch->GetEntry(index);
			} else { 
				printf("branch eta2_branch does not exist!\n");
				exit(1);
			}
			eta2_isLoaded = true;
		}
		return eta2_;
	}
	float &iso2()
	{
		if (not iso2_isLoaded) {
			if (iso2_branch != 0) {
				iso2_branch->GetEntry(index);
			} else { 
				printf("branch iso2_branch does not exist!\n");
				exit(1);
			}
			iso2_isLoaded = true;
		}
		return iso2_;
	}
	float &iso_ch_2()
	{
		if (not iso_ch_2_isLoaded) {
			if (iso_ch_2_branch != 0) {
				iso_ch_2_branch->GetEntry(index);
			} else { 
				printf("branch iso_ch_2_branch does not exist!\n");
				exit(1);
			}
			iso_ch_2_isLoaded = true;
		}
		return iso_ch_2_;
	}
	float &iso_em_2()
	{
		if (not iso_em_2_isLoaded) {
			if (iso_em_2_branch != 0) {
				iso_em_2_branch->GetEntry(index);
			} else { 
				printf("branch iso_em_2_branch does not exist!\n");
				exit(1);
			}
			iso_em_2_isLoaded = true;
		}
		return iso_em_2_;
	}
	float &iso_nh_2()
	{
		if (not iso_nh_2_isLoaded) {
			if (iso_nh_2_branch != 0) {
				iso_nh_2_branch->GetEntry(index);
			} else { 
				printf("branch iso_nh_2_branch does not exist!\n");
				exit(1);
			}
			iso_nh_2_isLoaded = true;
		}
		return iso_nh_2_;
	}
	int &aeff2()
	{
		if (not aeff2_isLoaded) {
			if (aeff2_branch != 0) {
				aeff2_branch->GetEntry(index);
			} else { 
				printf("branch aeff2_branch does not exist!\n");
				exit(1);
			}
			aeff2_isLoaded = true;
		}
		return aeff2_;
	}
	float &dbeta2()
	{
		if (not dbeta2_isLoaded) {
			if (dbeta2_branch != 0) {
				dbeta2_branch->GetEntry(index);
			} else { 
				printf("branch dbeta2_branch does not exist!\n");
				exit(1);
			}
			dbeta2_isLoaded = true;
		}
		return dbeta2_;
	}
	bool &	num2()
	{
		if (not num2_isLoaded) {
			if (num2_branch != 0) {
				num2_branch->GetEntry(index);
			} else { 
				printf("branch num2_branch does not exist!\n");
				exit(1);
			}
			num2_isLoaded = true;
		}
		return num2_;
	}
	bool &	fo2()
	{
		if (not fo2_isLoaded) {
			if (fo2_branch != 0) {
				fo2_branch->GetEntry(index);
			} else { 
				printf("branch fo2_branch does not exist!\n");
				exit(1);
			}
			fo2_isLoaded = true;
		}
		return fo2_;
	}
	int &id2()
	{
		if (not id2_isLoaded) {
			if (id2_branch != 0) {
				id2_branch->GetEntry(index);
			} else { 
				printf("branch id2_branch does not exist!\n");
				exit(1);
			}
			id2_isLoaded = true;
		}
		return id2_;
	}
	float &wfr2()
	{
		if (not wfr2_isLoaded) {
			if (wfr2_branch != 0) {
				wfr2_branch->GetEntry(index);
			} else { 
				printf("branch wfr2_branch does not exist!\n");
				exit(1);
			}
			wfr2_isLoaded = true;
		}
		return wfr2_;
	}
	float &wflip2()
	{
		if (not wflip2_isLoaded) {
			if (wflip2_branch != 0) {
				wflip2_branch->GetEntry(index);
			} else { 
				printf("branch wflip2_branch does not exist!\n");
				exit(1);
			}
			wflip2_isLoaded = true;
		}
		return wflip2_;
	}
	int &leptru2()
	{
		if (not leptru2_isLoaded) {
			if (leptru2_branch != 0) {
				leptru2_branch->GetEntry(index);
			} else { 
				printf("branch leptru2_branch does not exist!\n");
				exit(1);
			}
			leptru2_isLoaded = true;
		}
		return leptru2_;
	}
	bool &	isSS()
	{
		if (not isSS_isLoaded) {
			if (isSS_branch != 0) {
				isSS_branch->GetEntry(index);
			} else { 
				printf("branch isSS_branch does not exist!\n");
				exit(1);
			}
			isSS_isLoaded = true;
		}
		return isSS_;
	}
	bool &	isSF()
	{
		if (not isSF_isLoaded) {
			if (isSF_branch != 0) {
				isSF_branch->GetEntry(index);
			} else { 
				printf("branch isSF_branch does not exist!\n");
				exit(1);
			}
			isSF_isLoaded = true;
		}
		return isSF_;
	}
	bool &	isDF()
	{
		if (not isDF_isLoaded) {
			if (isDF_branch != 0) {
				isDF_branch->GetEntry(index);
			} else { 
				printf("branch isDF_branch does not exist!\n");
				exit(1);
			}
			isDF_isLoaded = true;
		}
		return isDF_;
	}
	bool &	isOS()
	{
		if (not isOS_isLoaded) {
			if (isOS_branch != 0) {
				isOS_branch->GetEntry(index);
			} else { 
				printf("branch isOS_branch does not exist!\n");
				exit(1);
			}
			isOS_isLoaded = true;
		}
		return isOS_;
	}
	float &trig_eff()
	{
		if (not trig_eff_isLoaded) {
			if (trig_eff_branch != 0) {
				trig_eff_branch->GetEntry(index);
			} else { 
				printf("branch trig_eff_branch does not exist!\n");
				exit(1);
			}
			trig_eff_isLoaded = true;
		}
		return trig_eff_;
	}
	float &scale_nbtag()
	{
		if (not scale_nbtag_isLoaded) {
			if (scale_nbtag_branch != 0) {
				scale_nbtag_branch->GetEntry(index);
			} else { 
				printf("branch scale_nbtag_branch does not exist!\n");
				exit(1);
			}
			scale_nbtag_isLoaded = true;
		}
		return scale_nbtag_;
	}
	float &scale_nbtag3()
	{
		if (not scale_nbtag3_isLoaded) {
			if (scale_nbtag3_branch != 0) {
				scale_nbtag3_branch->GetEntry(index);
			} else { 
				printf("branch scale_nbtag3_branch does not exist!\n");
				exit(1);
			}
			scale_nbtag3_isLoaded = true;
		}
		return scale_nbtag3_;
	}
	float &scale_unc_nbtag()
	{
		if (not scale_unc_nbtag_isLoaded) {
			if (scale_unc_nbtag_branch != 0) {
				scale_unc_nbtag_branch->GetEntry(index);
			} else { 
				printf("branch scale_unc_nbtag_branch does not exist!\n");
				exit(1);
			}
			scale_unc_nbtag_isLoaded = true;
		}
		return scale_unc_nbtag_;
	}
	float &scale_unc_nbtag3()
	{
		if (not scale_unc_nbtag3_isLoaded) {
			if (scale_unc_nbtag3_branch != 0) {
				scale_unc_nbtag3_branch->GetEntry(index);
			} else { 
				printf("branch scale_unc_nbtag3_branch does not exist!\n");
				exit(1);
			}
			scale_unc_nbtag3_isLoaded = true;
		}
		return scale_unc_nbtag3_;
	}
	float &scale_tap()
	{
		if (not scale_tap_isLoaded) {
			if (scale_tap_branch != 0) {
				scale_tap_branch->GetEntry(index);
			} else { 
				printf("branch scale_tap_branch does not exist!\n");
				exit(1);
			}
			scale_tap_isLoaded = true;
		}
		return scale_tap_;
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
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_b1_p4()
	{
		if (not gen_b1_p4_isLoaded) {
			if (gen_b1_p4_branch != 0) {
				gen_b1_p4_branch->GetEntry(index);
			} else { 
				printf("branch gen_b1_p4_branch does not exist!\n");
				exit(1);
			}
			gen_b1_p4_isLoaded = true;
		}
		return *gen_b1_p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_b2_p4()
	{
		if (not gen_b2_p4_isLoaded) {
			if (gen_b2_p4_branch != 0) {
				gen_b2_p4_branch->GetEntry(index);
			} else { 
				printf("branch gen_b2_p4_branch does not exist!\n");
				exit(1);
			}
			gen_b2_p4_isLoaded = true;
		}
		return *gen_b2_p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_b3_p4()
	{
		if (not gen_b3_p4_isLoaded) {
			if (gen_b3_p4_branch != 0) {
				gen_b3_p4_branch->GetEntry(index);
			} else { 
				printf("branch gen_b3_p4_branch does not exist!\n");
				exit(1);
			}
			gen_b3_p4_isLoaded = true;
		}
		return *gen_b3_p4_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_b4_p4()
	{
		if (not gen_b4_p4_isLoaded) {
			if (gen_b4_p4_branch != 0) {
				gen_b4_p4_branch->GetEntry(index);
			} else { 
				printf("branch gen_b4_p4_branch does not exist!\n");
				exit(1);
			}
			gen_b4_p4_isLoaded = true;
		}
		return *gen_b4_p4_;
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
	float &scale();
	float &scale1fb();
	unsigned int &type();
	unsigned int &nvtxs();
	float &vtxw();
	unsigned int &njets();
	unsigned int &njets20();
	unsigned int &njets30();
	unsigned int &nbtags();
	unsigned int &nbtags20();
	unsigned int &nbtags30();
	float &pfmet();
	float &ht();
	float &ht20();
	float &ht30();
	float &mass();
	float &mt();
	bool &trig_mm();
	bool &trig_em();
	bool &trig_ee();
	int &gen_sign();
	int &gen_type();
	float &gen_ht();
	float &gen_met();
	float &rho();
	float &pt1();
	float &eta1();
	int &id1();
	float &iso1();
	float &iso_ch_1();
	float &iso_em_1();
	float &iso_nh_1();
	float &aeff1();
	float &dbeta1();
	bool &num1();
	bool &fo1();
	float &wfr1();
	float &wflip1();
	int &leptru1();
	float &pt2();
	float &eta2();
	float &iso2();
	float &iso_ch_2();
	float &iso_em_2();
	float &iso_nh_2();
	int &aeff2();
	float &dbeta2();
	bool &num2();
	bool &fo2();
	int &id2();
	float &wfr2();
	float &wflip2();
	int &leptru2();
	bool &isSS();
	bool &isSF();
	bool &isDF();
	bool &isOS();
	float &trig_eff();
	float &scale_nbtag();
	float &scale_nbtag3();
	float &scale_unc_nbtag();
	float &scale_unc_nbtag3();
	float &scale_tap();
	float &sparm0();
	float &sparm1();
	float &sparm2();
	float &sparm3();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep1_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep2_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_b1_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_b2_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_b3_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_b4_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_p4();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_p4();
}
#endif
