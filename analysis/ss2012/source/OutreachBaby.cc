#include "OutreachBaby.h"
OutreachBaby outreach_baby;
namespace orb {
	unsigned int &run() { return outreach_baby.run(); }
	unsigned int &ls() { return outreach_baby.ls(); }
	unsigned int &evt() { return outreach_baby.evt(); }
	bool &is_real_data() { return outreach_baby.is_real_data(); }
	int &sample() { return outreach_baby.sample(); }
	int &nvtxs() { return outreach_baby.nvtxs(); }
	int &vtx_idx() { return outreach_baby.vtx_idx(); }
	float &pfmet() { return outreach_baby.pfmet(); }
	float &pfmet_phi() { return outreach_baby.pfmet_phi(); }
	float &uncorpfmet() { return outreach_baby.uncorpfmet(); }
	float &uncorpfmet_phi() { return outreach_baby.uncorpfmet_phi(); }
	float &scale1fb() { return outreach_baby.scale1fb(); }
	float &xsec() { return outreach_baby.xsec(); }
	float &kfactor() { return outreach_baby.kfactor(); }
	float &gen_met() { return outreach_baby.gen_met(); }
	float &gen_met_phi() { return outreach_baby.gen_met_phi(); }
	int &gen_dilep_type() { return outreach_baby.gen_dilep_type(); }
	float &gen_ht() { return outreach_baby.gen_ht(); }
	int &gen_nbtags() { return outreach_baby.gen_nbtags(); }
	int &gen_njets() { return outreach_baby.gen_njets(); }
	bool &gen_is_ss() { return outreach_baby.gen_is_ss(); }
	bool &gen_is_os() { return outreach_baby.gen_is_os(); }
	int &dilep_type() { return outreach_baby.dilep_type(); }
	float &reco_ht() { return outreach_baby.reco_ht(); }
	float &reco_met() { return outreach_baby.reco_met(); }
	int &reco_nbtags() { return outreach_baby.reco_nbtags(); }
	int &reco_njets() { return outreach_baby.reco_njets(); }
	float &reco_is_ss() { return outreach_baby.reco_is_ss(); }
	float &reco_is_os() { return outreach_baby.reco_is_os(); }
	float &sf_dileptrig() { return outreach_baby.sf_dileptrig(); }
	float &sf_lepeff() { return outreach_baby.sf_lepeff(); }
	float &sf_nbtag() { return outreach_baby.sf_nbtag(); }
	float &sf_nbtag3() { return outreach_baby.sf_nbtag3(); }
	float &sparm0() { return outreach_baby.sparm0(); }
	float &sparm1() { return outreach_baby.sparm1(); }
	float &sparm2() { return outreach_baby.sparm2(); }
	float &sparm3() { return outreach_baby.sparm3(); }
	int &lep1_gen_pdgid() { return outreach_baby.lep1_gen_pdgid(); }
	int &lep1_pdgid() { return outreach_baby.lep1_pdgid(); }
	bool &lep1_matched() { return outreach_baby.lep1_matched(); }
	bool &lep1_from_tau() { return outreach_baby.lep1_from_tau(); }
	bool &lep1_passes_id() { return outreach_baby.lep1_passes_id(); }
	bool &lep1_passes_iso() { return outreach_baby.lep1_passes_iso(); }
	bool &lep1_num() { return outreach_baby.lep1_num(); }
	float &lep1_iso() { return outreach_baby.lep1_iso(); }
	int &lep2_pdgid() { return outreach_baby.lep2_pdgid(); }
	int &lep2_gen_pdgid() { return outreach_baby.lep2_gen_pdgid(); }
	bool &lep2_matched() { return outreach_baby.lep2_matched(); }
	bool &lep2_from_tau() { return outreach_baby.lep2_from_tau(); }
	bool &lep2_passes_id() { return outreach_baby.lep2_passes_id(); }
	bool &lep2_passes_iso() { return outreach_baby.lep2_passes_iso(); }
	bool &lep2_num() { return outreach_baby.lep2_num(); }
	float &lep2_iso() { return outreach_baby.lep2_iso(); }
	float &metw30() { return outreach_baby.metw30(); }
	float &metw50() { return outreach_baby.metw50(); }
	float &metw120() { return outreach_baby.metw120(); }
	float &btagw() { return outreach_baby.btagw(); }
	float &pt1w() { return outreach_baby.pt1w(); }
	float &pt2w() { return outreach_baby.pt2w(); }
	float &htw200() { return outreach_baby.htw200(); }
	float &htw320() { return outreach_baby.htw320(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_gen_p4() { return outreach_baby.lep1_gen_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep1_p4() { return outreach_baby.lep1_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_gen_p4() { return outreach_baby.lep2_gen_p4(); }
	ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > &lep2_p4() { return outreach_baby.lep2_p4(); }
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gen_vbjets_p4() { return outreach_baby.gen_vbjets_p4(); }
	vector<bool> &gen_vbjets_matched() { return outreach_baby.gen_vbjets_matched(); }
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &gen_vjets_p4() { return outreach_baby.gen_vjets_p4(); }
	vector<bool> &gen_vjets_matched() { return outreach_baby.gen_vjets_matched(); }
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &reco_vbjets_p4() { return outreach_baby.reco_vbjets_p4(); }
	vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > &reco_vjets_p4() { return outreach_baby.reco_vjets_p4(); }
}
