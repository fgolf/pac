#include "SSB2011.h"
SSB2011 samesignbtag;
namespace ssb {
	float &scale1fb() { return samesignbtag.scale1fb(); }
	unsigned int &run() { return samesignbtag.run(); }
	unsigned int &ls() { return samesignbtag.ls(); }
	unsigned int &evt() { return samesignbtag.evt(); }
	unsigned int &type() { return samesignbtag.type(); }
	unsigned int &nbtags() { return samesignbtag.nbtags(); }
	unsigned int &njets() { return samesignbtag.njets(); }
	float &pfmet() { return samesignbtag.pfmet(); }
	float &tcmet() { return samesignbtag.tcmet(); }
	float &ht() { return samesignbtag.ht(); }
	float &mass() { return samesignbtag.mass(); }
	float &mt() { return samesignbtag.mt(); }
	float &vtxw() { return samesignbtag.vtxw(); }
	unsigned int &nvtxs() { return samesignbtag.nvtxs(); }
	bool &isSS() { return samesignbtag.isSS(); }
	bool &isSF() { return samesignbtag.isSF(); }
	bool &isDF() { return samesignbtag.isDF(); }
	bool &isOS() { return samesignbtag.isOS(); }
	bool &isOS_SF() { return samesignbtag.isOS_SF(); }
	bool &isOS_DF() { return samesignbtag.isOS_DF(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &p41() { return samesignbtag.p41(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &mc3p41() { return samesignbtag.mc3p41(); }
	int &mc3id1() { return samesignbtag.mc3id1(); }
	int &mcmomid1() { return samesignbtag.mcmomid1(); }
	float &pt1() { return samesignbtag.pt1(); }
	float &eta1() { return samesignbtag.eta1(); }
	int &id1() { return samesignbtag.id1(); }
	bool &num1() { return samesignbtag.num1(); }
	bool &fo1() { return samesignbtag.fo1(); }
	int &isWlep1() { return samesignbtag.isWlep1(); }
	float &wfr1() { return samesignbtag.wfr1(); }
	float &wflip1() { return samesignbtag.wflip1(); }
	unsigned int &frtype1() { return samesignbtag.frtype1(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &p42() { return samesignbtag.p42(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &mc3p42() { return samesignbtag.mc3p42(); }
	int &mc3id2() { return samesignbtag.mc3id2(); }
	int &mcmomid2() { return samesignbtag.mcmomid2(); }
	float &pt2() { return samesignbtag.pt2(); }
	float &eta2() { return samesignbtag.eta2(); }
	int &id2() { return samesignbtag.id2(); }
	bool &num2() { return samesignbtag.num2(); }
	bool &fo2() { return samesignbtag.fo2(); }
	int &isWlep2() { return samesignbtag.isWlep2(); }
	float &wfr2() { return samesignbtag.wfr2(); }
	float &wflip2() { return samesignbtag.wflip2(); }
	unsigned int &frtype2() { return samesignbtag.frtype2(); }
}
