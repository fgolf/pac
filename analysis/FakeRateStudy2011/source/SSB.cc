#include "SSB.h"
SSB samesignbtag;
namespace ssb {
	unsigned int &run() { return samesignbtag.run(); }
	unsigned int &ls() { return samesignbtag.ls(); }
	unsigned int &evt() { return samesignbtag.evt(); }
	float &scale() { return samesignbtag.scale(); }
	float &scale1fb() { return samesignbtag.scale1fb(); }
	unsigned int &type() { return samesignbtag.type(); }
	unsigned int &nvtxs() { return samesignbtag.nvtxs(); }
	float &vtxw() { return samesignbtag.vtxw(); }
	unsigned int &njets() { return samesignbtag.njets(); }
	unsigned int &njets20() { return samesignbtag.njets20(); }
	unsigned int &njets30() { return samesignbtag.njets30(); }
	unsigned int &nbtags() { return samesignbtag.nbtags(); }
	unsigned int &nbtags20() { return samesignbtag.nbtags20(); }
	unsigned int &nbtags30() { return samesignbtag.nbtags30(); }
	float &pfmet() { return samesignbtag.pfmet(); }
	float &ht() { return samesignbtag.ht(); }
	float &ht20() { return samesignbtag.ht20(); }
	float &ht30() { return samesignbtag.ht30(); }
	float &mass() { return samesignbtag.mass(); }
	float &mt() { return samesignbtag.mt(); }
	bool &trig_mm() { return samesignbtag.trig_mm(); }
	bool &trig_em() { return samesignbtag.trig_em(); }
	bool &trig_ee() { return samesignbtag.trig_ee(); }
	int &gen_sign() { return samesignbtag.gen_sign(); }
	int &gen_type() { return samesignbtag.gen_type(); }
	float &gen_ht() { return samesignbtag.gen_ht(); }
	float &gen_met() { return samesignbtag.gen_met(); }
	float &rho() { return samesignbtag.rho(); }
	float &pt1() { return samesignbtag.pt1(); }
	float &eta1() { return samesignbtag.eta1(); }
	int &id1() { return samesignbtag.id1(); }
	float &iso1() { return samesignbtag.iso1(); }
	float &iso_ch_1() { return samesignbtag.iso_ch_1(); }
	float &iso_em_1() { return samesignbtag.iso_em_1(); }
	float &iso_nh_1() { return samesignbtag.iso_nh_1(); }
	float &aeff1() { return samesignbtag.aeff1(); }
	float &dbeta1() { return samesignbtag.dbeta1(); }
	bool &num1() { return samesignbtag.num1(); }
	bool &fo1() { return samesignbtag.fo1(); }
	float &wfr1() { return samesignbtag.wfr1(); }
	float &wflip1() { return samesignbtag.wflip1(); }
	int &leptru1() { return samesignbtag.leptru1(); }
	float &pt2() { return samesignbtag.pt2(); }
	float &eta2() { return samesignbtag.eta2(); }
	float &iso2() { return samesignbtag.iso2(); }
	float &iso_ch_2() { return samesignbtag.iso_ch_2(); }
	float &iso_em_2() { return samesignbtag.iso_em_2(); }
	float &iso_nh_2() { return samesignbtag.iso_nh_2(); }
	int &aeff2() { return samesignbtag.aeff2(); }
	float &dbeta2() { return samesignbtag.dbeta2(); }
	bool &num2() { return samesignbtag.num2(); }
	bool &fo2() { return samesignbtag.fo2(); }
	int &id2() { return samesignbtag.id2(); }
	float &wfr2() { return samesignbtag.wfr2(); }
	float &wflip2() { return samesignbtag.wflip2(); }
	int &leptru2() { return samesignbtag.leptru2(); }
	bool &isSS() { return samesignbtag.isSS(); }
	bool &isSF() { return samesignbtag.isSF(); }
	bool &isDF() { return samesignbtag.isDF(); }
	bool &isOS() { return samesignbtag.isOS(); }
	float &trig_eff() { return samesignbtag.trig_eff(); }
	float &scale_nbtag() { return samesignbtag.scale_nbtag(); }
	float &scale_nbtag3() { return samesignbtag.scale_nbtag3(); }
	float &scale_unc_nbtag() { return samesignbtag.scale_unc_nbtag(); }
	float &scale_unc_nbtag3() { return samesignbtag.scale_unc_nbtag3(); }
	float &scale_tap() { return samesignbtag.scale_tap(); }
	float &sparm0() { return samesignbtag.sparm0(); }
	float &sparm1() { return samesignbtag.sparm1(); }
	float &sparm2() { return samesignbtag.sparm2(); }
	float &sparm3() { return samesignbtag.sparm3(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep1_p4() { return samesignbtag.gen_lep1_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_lep2_p4() { return samesignbtag.gen_lep2_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_b1_p4() { return samesignbtag.gen_b1_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_b2_p4() { return samesignbtag.gen_b2_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_b3_p4() { return samesignbtag.gen_b3_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &gen_b4_p4() { return samesignbtag.gen_b4_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_p4() { return samesignbtag.lep1_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_p4() { return samesignbtag.lep2_p4(); }
}
