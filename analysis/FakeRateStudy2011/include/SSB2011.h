// -*- C++ -*-
#ifndef SSB2011_H
#define SSB2011_H
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
class SSB2011 {
private: 
protected: 
	unsigned int index;
	float	scale1fb_;
	TBranch *scale1fb_branch;
	bool scale1fb_isLoaded;
	unsigned int	run_;
	TBranch *run_branch;
	bool run_isLoaded;
	unsigned int	ls_;
	TBranch *ls_branch;
	bool ls_isLoaded;
	unsigned int	evt_;
	TBranch *evt_branch;
	bool evt_isLoaded;
	unsigned int	type_;
	TBranch *type_branch;
	bool type_isLoaded;
	unsigned int	nbtags_;
	TBranch *nbtags_branch;
	bool nbtags_isLoaded;
	unsigned int	njets_;
	TBranch *njets_branch;
	bool njets_isLoaded;
	float	pfmet_;
	TBranch *pfmet_branch;
	bool pfmet_isLoaded;
	float	tcmet_;
	TBranch *tcmet_branch;
	bool tcmet_isLoaded;
	float	ht_;
	TBranch *ht_branch;
	bool ht_isLoaded;
	float	mass_;
	TBranch *mass_branch;
	bool mass_isLoaded;
	float	mt_;
	TBranch *mt_branch;
	bool mt_isLoaded;
	float	vtxw_;
	TBranch *vtxw_branch;
	bool vtxw_isLoaded;
	unsigned int	nvtxs_;
	TBranch *nvtxs_branch;
	bool nvtxs_isLoaded;
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
	bool	isOS_SF_;
	TBranch *isOS_SF_branch;
	bool isOS_SF_isLoaded;
	bool	isOS_DF_;
	TBranch *isOS_DF_branch;
	bool isOS_DF_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *p41_;
	TBranch *p41_branch;
	bool p41_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *mc3p41_;
	TBranch *mc3p41_branch;
	bool mc3p41_isLoaded;
	int	mc3id1_;
	TBranch *mc3id1_branch;
	bool mc3id1_isLoaded;
	int	mcmomid1_;
	TBranch *mcmomid1_branch;
	bool mcmomid1_isLoaded;
	int	mcmomid2_;
	TBranch *mcmomid2_branch;
	bool mcmomid2_isLoaded;
	float pt1_;
	TBranch *pt1_branch;
	bool pt1_isLoaded;
	float	eta1_;
	TBranch *eta1_branch;
	bool eta1_isLoaded;
	int	id1_;
	TBranch *id1_branch;
	bool id1_isLoaded;
	bool	num1_;
	TBranch *num1_branch;
	bool num1_isLoaded;
	bool	fo1_;
	TBranch *fo1_branch;
	bool fo1_isLoaded;
	int	isWlep1_;
	TBranch *isWlep1_branch;
	bool isWlep1_isLoaded;
	float	wfr1_;
	TBranch *wfr1_branch;
	bool wfr1_isLoaded;
	float	wflip1_;
	TBranch *wflip1_branch;
	bool wflip1_isLoaded;
	unsigned int	frtype1_;
	TBranch *frtype1_branch;
	bool frtype1_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *p42_;
	TBranch *p42_branch;
	bool p42_isLoaded;
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > *mc3p42_;
	TBranch *mc3p42_branch;
	bool mc3p42_isLoaded;
	float	pt2_;
	TBranch *pt2_branch;
	bool pt2_isLoaded;
	float	eta2_;
	TBranch *eta2_branch;
	bool eta2_isLoaded;
	int	id2_;
	TBranch *id2_branch;
	bool id2_isLoaded;
	int	mc3id2_;
	TBranch *mc3id2_branch;
	bool mc3id2_isLoaded;
	bool	num2_;
	TBranch *num2_branch;
	bool num2_isLoaded;
	bool	fo2_;
	TBranch *fo2_branch;
	bool fo2_isLoaded;
	int	isWlep2_;
	TBranch *isWlep2_branch;
	bool isWlep2_isLoaded;
	float	wfr2_;
	TBranch *wfr2_branch;
	bool wfr2_isLoaded;
	float	wflip2_;
	TBranch *wflip2_branch;
	bool wflip2_isLoaded;
	unsigned int	frtype2_;
	TBranch *frtype2_branch;
	bool frtype2_isLoaded;
public: 
void Init(TTree *tree) {
	p41_branch = 0;
	if (tree->GetBranch("p41") != 0) {
		p41_branch = tree->GetBranch("p41");
		p41_branch->SetAddress(&p41_);
	}
	mc3p41_branch = 0;
	if (tree->GetBranch("mc3p41") != 0) {
		mc3p41_branch = tree->GetBranch("mc3p41");
		mc3p41_branch->SetAddress(&mc3p41_);
	}
	p42_branch = 0;
	if (tree->GetBranch("p42") != 0) {
		p42_branch = tree->GetBranch("p42");
		p42_branch->SetAddress(&p42_);
	}
	mc3p42_branch = 0;
	if (tree->GetBranch("mc3p42") != 0) {
		mc3p42_branch = tree->GetBranch("mc3p42");
		mc3p42_branch->SetAddress(&mc3p42_);
	}
  tree->SetMakeClass(1);
	scale1fb_branch = 0;
	if (tree->GetBranch("scale1fb") != 0) {
		scale1fb_branch = tree->GetBranch("scale1fb");
		scale1fb_branch->SetAddress(&scale1fb_);
	}
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
	type_branch = 0;
	if (tree->GetBranch("type") != 0) {
		type_branch = tree->GetBranch("type");
		type_branch->SetAddress(&type_);
	}
	nbtags_branch = 0;
	if (tree->GetBranch("nbtags") != 0) {
		nbtags_branch = tree->GetBranch("nbtags");
		nbtags_branch->SetAddress(&nbtags_);
	}
	njets_branch = 0;
	if (tree->GetBranch("njets") != 0) {
		njets_branch = tree->GetBranch("njets");
		njets_branch->SetAddress(&njets_);
	}
	pfmet_branch = 0;
	if (tree->GetBranch("pfmet") != 0) {
		pfmet_branch = tree->GetBranch("pfmet");
		pfmet_branch->SetAddress(&pfmet_);
	}
	tcmet_branch = 0;
	if (tree->GetBranch("tcmet") != 0) {
		tcmet_branch = tree->GetBranch("tcmet");
		tcmet_branch->SetAddress(&tcmet_);
	}
	ht_branch = 0;
	if (tree->GetBranch("ht") != 0) {
		ht_branch = tree->GetBranch("ht");
		ht_branch->SetAddress(&ht_);
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
	vtxw_branch = 0;
	if (tree->GetBranch("vtxw") != 0) {
		vtxw_branch = tree->GetBranch("vtxw");
		vtxw_branch->SetAddress(&vtxw_);
	}
	nvtxs_branch = 0;
	if (tree->GetBranch("nvtxs") != 0) {
		nvtxs_branch = tree->GetBranch("nvtxs");
		nvtxs_branch->SetAddress(&nvtxs_);
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
	isOS_SF_branch = 0;
	if (tree->GetBranch("isOS_SF") != 0) {
		isOS_SF_branch = tree->GetBranch("isOS_SF");
		isOS_SF_branch->SetAddress(&isOS_SF_);
	}
	isOS_DF_branch = 0;
	if (tree->GetBranch("isOS_DF") != 0) {
		isOS_DF_branch = tree->GetBranch("isOS_DF");
		isOS_DF_branch->SetAddress(&isOS_DF_);
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
	mc3id1_branch = 0;
	if (tree->GetBranch("mc3id1") != 0) {
		mc3id1_branch = tree->GetBranch("mc3id1");
		mc3id1_branch->SetAddress(&mc3id1_);
	}
	mcmomid1_branch = 0;
	if (tree->GetBranch("mcmomid1") != 0) {
		mcmomid1_branch = tree->GetBranch("mcmomid1");
		mcmomid1_branch->SetAddress(&mcmomid1_);
	}
	mcmomid2_branch = 0;
	if (tree->GetBranch("mcmomid2") != 0) {
		mcmomid2_branch = tree->GetBranch("mcmomid2");
		mcmomid2_branch->SetAddress(&mcmomid2_);
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
	isWlep1_branch = 0;
	if (tree->GetBranch("isWlep1") != 0) {
		isWlep1_branch = tree->GetBranch("isWlep1");
		isWlep1_branch->SetAddress(&isWlep1_);
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
	frtype1_branch = 0;
	if (tree->GetBranch("frtype1") != 0) {
		frtype1_branch = tree->GetBranch("frtype1");
		frtype1_branch->SetAddress(&frtype1_);
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
	id2_branch = 0;
	if (tree->GetBranch("id2") != 0) {
		id2_branch = tree->GetBranch("id2");
		id2_branch->SetAddress(&id2_);
	}
	mc3id2_branch = 0;
	if (tree->GetBranch("mc3id2") != 0) {
		mc3id2_branch = tree->GetBranch("mc3id2");
		mc3id2_branch->SetAddress(&mc3id2_);
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
	isWlep2_branch = 0;
	if (tree->GetBranch("isWlep2") != 0) {
		isWlep2_branch = tree->GetBranch("isWlep2");
		isWlep2_branch->SetAddress(&isWlep2_);
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
	frtype2_branch = 0;
	if (tree->GetBranch("frtype2") != 0) {
		frtype2_branch = tree->GetBranch("frtype2");
		frtype2_branch->SetAddress(&frtype2_);
	}
  tree->SetMakeClass(0);
}
void GetEntry(unsigned int idx) 
	// this only marks branches as not loaded, saving a lot of time
	{
		index = idx;
		scale1fb_isLoaded = false;
		run_isLoaded = false;
		ls_isLoaded = false;
		evt_isLoaded = false;
		type_isLoaded = false;
		nbtags_isLoaded = false;
		njets_isLoaded = false;
		pfmet_isLoaded = false;
		tcmet_isLoaded = false;
		ht_isLoaded = false;
		mass_isLoaded = false;
		mt_isLoaded = false;
		vtxw_isLoaded = false;
		nvtxs_isLoaded = false;
		isSS_isLoaded = false;
		isSF_isLoaded = false;
		isDF_isLoaded = false;
		isOS_isLoaded = false;
		isOS_SF_isLoaded = false;
		isOS_DF_isLoaded = false;
		p41_isLoaded = false;
		mc3p41_isLoaded = false;
		pt1_isLoaded = false;
		eta1_isLoaded = false;
		id1_isLoaded = false;
		mc3id1_isLoaded = false;
		mcmomid1_isLoaded = false;
		mcmomid2_isLoaded = false;
		num1_isLoaded = false;
		fo1_isLoaded = false;
		isWlep1_isLoaded = false;
		wfr1_isLoaded = false;
		wflip1_isLoaded = false;
		frtype1_isLoaded = false;
		p42_isLoaded = false;
		mc3p42_isLoaded = false;
		pt2_isLoaded = false;
		eta2_isLoaded = false;
		id2_isLoaded = false;
		mc3id2_isLoaded = false;
		num2_isLoaded = false;
		fo2_isLoaded = false;
		isWlep2_isLoaded = false;
		wfr2_isLoaded = false;
		wflip2_isLoaded = false;
		frtype2_isLoaded = false;
	}

void LoadAllBranches() 
	// load all branches
{
	if (scale1fb_branch != 0) scale1fb();
	if (run_branch != 0) run();
	if (ls_branch != 0) ls();
	if (evt_branch != 0) evt();
	if (type_branch != 0) type();
	if (nbtags_branch != 0) nbtags();
	if (njets_branch != 0) njets();
	if (pfmet_branch != 0) pfmet();
	if (tcmet_branch != 0) tcmet();
	if (ht_branch != 0) ht();
	if (mass_branch != 0) mass();
	if (mt_branch != 0) mt();
	if (vtxw_branch != 0) vtxw();
	if (nvtxs_branch != 0) nvtxs();
	if (isSS_branch != 0) isSS();
	if (isSF_branch != 0) isSF();
	if (isDF_branch != 0) isDF();
	if (isOS_branch != 0) isOS();
	if (isOS_SF_branch != 0) isOS_SF();
	if (isOS_DF_branch != 0) isOS_DF();
	if (p41_branch != 0) p41();
	if (mc3p41_branch != 0) mc3p41();
	if (pt1_branch != 0) pt1();
	if (eta1_branch != 0) eta1();
	if (id1_branch != 0) id1();
	if (mc3id1_branch != 0) mc3id1();
	if (mcmomid1_branch != 0) mcmomid1();
	if (mcmomid2_branch != 0) mcmomid2();
	if (num1_branch != 0) num1();
	if (fo1_branch != 0) fo1();
	if (isWlep1_branch != 0) isWlep1();
	if (wfr1_branch != 0) wfr1();
	if (wflip1_branch != 0) wflip1();
	if (frtype1_branch != 0) frtype1();
	if (p42_branch != 0) p42();
	if (mc3p42_branch != 0) mc3p42();
	if (pt2_branch != 0) pt2();
	if (eta2_branch != 0) eta2();
	if (id2_branch != 0) id2();
	if (mc3id2_branch != 0) mc3id2();
	if (num2_branch != 0) num2();
	if (fo2_branch != 0) fo2();
	if (isWlep2_branch != 0) isWlep2();
	if (wfr2_branch != 0) wfr2();
	if (wflip2_branch != 0) wflip2();
	if (frtype2_branch != 0) frtype2();
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
	bool &	isOS_SF()
	{
		if (not isOS_SF_isLoaded) {
			if (isOS_SF_branch != 0) {
				isOS_SF_branch->GetEntry(index);
			} else { 
				printf("branch isOS_SF_branch does not exist!\n");
				exit(1);
			}
			isOS_SF_isLoaded = true;
		}
		return isOS_SF_;
	}
	bool &	isOS_DF()
	{
		if (not isOS_DF_isLoaded) {
			if (isOS_DF_branch != 0) {
				isOS_DF_branch->GetEntry(index);
			} else { 
				printf("branch isOS_DF_branch does not exist!\n");
				exit(1);
			}
			isOS_DF_isLoaded = true;
		}
		return isOS_DF_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &p41()
	{
		if (not p41_isLoaded) {
			if (p41_branch != 0) {
				p41_branch->GetEntry(index);
			} else { 
				printf("branch p41_branch does not exist!\n");
				exit(1);
			}
			p41_isLoaded = true;
		}
		return *p41_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &mc3p41()
	{
		if (not mc3p41_isLoaded) {
			if (mc3p41_branch != 0) {
				mc3p41_branch->GetEntry(index);
			} else { 
				printf("branch mc3p41_branch does not exist!\n");
				exit(1);
			}
			mc3p41_isLoaded = true;
		}
		return *mc3p41_;
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
	int &mc3id1()
	{
		if (not mc3id1_isLoaded) {
			if (mc3id1_branch != 0) {
				mc3id1_branch->GetEntry(index);
			} else { 
				printf("branch mc3id1_branch does not exist!\n");
				exit(1);
			}
			mc3id1_isLoaded = true;
		}
		return mc3id1_;
	}
	int &mcmomid1()
	{
		if (not mcmomid1_isLoaded) {
			if (mcmomid1_branch != 0) {
				mcmomid1_branch->GetEntry(index);
			} else { 
				printf("branch mcmomid1_branch does not exist!\n");
				exit(1);
			}
			mcmomid1_isLoaded = true;
		}
		return mcmomid1_;
	}
	int &mcmomid2()
	{
		if (not mcmomid2_isLoaded) {
			if (mcmomid2_branch != 0) {
				mcmomid2_branch->GetEntry(index);
			} else { 
				printf("branch mcmomid2_branch does not exist!\n");
				exit(1);
			}
			mcmomid2_isLoaded = true;
		}
		return mcmomid2_;
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
	int &isWlep1()
	{
		if (not isWlep1_isLoaded) {
			if (isWlep1_branch != 0) {
				isWlep1_branch->GetEntry(index);
			} else { 
				printf("branch isWlep1_branch does not exist!\n");
				exit(1);
			}
			isWlep1_isLoaded = true;
		}
		return isWlep1_;
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
	unsigned int &frtype1()
	{
		if (not frtype1_isLoaded) {
			if (frtype1_branch != 0) {
				frtype1_branch->GetEntry(index);
			} else { 
				printf("branch frtype1_branch does not exist!\n");
				exit(1);
			}
			frtype1_isLoaded = true;
		}
		return frtype1_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &p42()
	{
		if (not p42_isLoaded) {
			if (p42_branch != 0) {
				p42_branch->GetEntry(index);
			} else { 
				printf("branch p42_branch does not exist!\n");
				exit(1);
			}
			p42_isLoaded = true;
		}
		return *p42_;
	}
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &mc3p42()
	{
		if (not mc3p42_isLoaded) {
			if (mc3p42_branch != 0) {
				mc3p42_branch->GetEntry(index);
			} else { 
				printf("branch mc3p42_branch does not exist!\n");
				exit(1);
			}
			mc3p42_isLoaded = true;
		}
		return *mc3p42_;
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
	int &mc3id2()
	{
		if (not mc3id2_isLoaded) {
			if (mc3id2_branch != 0) {
				mc3id2_branch->GetEntry(index);
			} else { 
				printf("branch mc3id2_branch does not exist!\n");
				exit(1);
			}
			mc3id2_isLoaded = true;
		}
		return mc3id2_;
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
	int &isWlep2()
	{
		if (not isWlep2_isLoaded) {
			if (isWlep2_branch != 0) {
				isWlep2_branch->GetEntry(index);
			} else { 
				printf("branch isWlep2_branch does not exist!\n");
				exit(1);
			}
			isWlep2_isLoaded = true;
		}
		return isWlep2_;
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
	unsigned int &frtype2()
	{
		if (not frtype2_isLoaded) {
			if (frtype2_branch != 0) {
				frtype2_branch->GetEntry(index);
			} else { 
				printf("branch frtype2_branch does not exist!\n");
				exit(1);
			}
			frtype2_isLoaded = true;
		}
		return frtype2_;
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
extern SSB2011 samesignbtag;
#endif

namespace ssb {
	float &scale1fb();
	unsigned int &run();
	unsigned int &ls();
	unsigned int &evt();
	unsigned int &type();
	unsigned int &nbtags();
	unsigned int &njets();
	float &pfmet();
	float &tcmet();
	float &ht();
	float &mass();
	float &mt();
	float &vtxw();
	unsigned int &nvtxs();
	bool &isSS();
	bool &isSF();
	bool &isDF();
	bool &isOS();
	bool &isOS_SF();
	bool &isOS_DF();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &p41();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &mc3p41();
	int &mc3id1();
	int &mcmomid1();
	float &pt1();
	float &eta1();
	int &id1();
	bool &num1();
	bool &fo1();
	int &isWlep1();
	float &wfr1();
	float &wflip1();
	unsigned int &frtype1();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &p42();
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &mc3p42();
	int &mcmomid2();
	int &mc3id2();
	float &pt2();
	float &eta2();
	int &id2();
	bool &num2();
	bool &fo2();
	int &isWlep2();
	float &wfr2();
	float &wflip2();
	unsigned int &frtype2();
}
#endif
