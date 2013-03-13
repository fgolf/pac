#include "LeptonTree.h"
LeptonTree lepton_tree;
namespace lt {
	const unsigned int &event() { return lepton_tree.event(); }
	const unsigned int &run() { return lepton_tree.run(); }
	const unsigned int &lumi() { return lepton_tree.lumi(); }
	const float &rnd() { return lepton_tree.rnd(); }
	const unsigned int &nvtx() { return lepton_tree.nvtx(); }
	const unsigned int &npu() { return lepton_tree.npu(); }
	const unsigned int &npuPlusOne() { return lepton_tree.npuPlusOne(); }
	const unsigned int &npuMinusOne() { return lepton_tree.npuMinusOne(); }
	const unsigned int &leptonSelection() { return lepton_tree.leptonSelection(); }
	const unsigned int &eventSelection() { return lepton_tree.eventSelection(); }
	const float &rhoIsoAll() { return lepton_tree.rhoIsoAll(); }
	const float &rhoIsoAllCentral() { return lepton_tree.rhoIsoAllCentral(); }
	const float &rhoIsoNeutral() { return lepton_tree.rhoIsoNeutral(); }
	const float &tagAndProbeMass() { return lepton_tree.tagAndProbeMass(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > &tag() { return lepton_tree.tag(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > &probe() { return lepton_tree.probe(); }
	const int &qTag() { return lepton_tree.qTag(); }
	const int &qProbe() { return lepton_tree.qProbe(); }
	const float &scale1fb() { return lepton_tree.scale1fb(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > &jet1() { return lepton_tree.jet1(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > &jet2() { return lepton_tree.jet2(); }
	const ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > &jet3() { return lepton_tree.jet3(); }
	const float &met() { return lepton_tree.met(); }
	const float &metPhi() { return lepton_tree.metPhi(); }
	const float &trackMet() { return lepton_tree.trackMet(); }
	const float &trackMetPhi() { return lepton_tree.trackMetPhi(); }
	const unsigned int &njets() { return lepton_tree.njets(); }
	const float &hltPrescale() { return lepton_tree.hltPrescale(); }
	const float &sumet() { return lepton_tree.sumet(); }
	const float &metSig() { return lepton_tree.metSig(); }
	const float &mt() { return lepton_tree.mt(); }
	const float &dPhiProbeJet1() { return lepton_tree.dPhiProbeJet1(); }
	const float &electronHWW2011MVA() { return lepton_tree.electronHWW2011MVA(); }
	const float &egammaPOG2012MVA() { return lepton_tree.egammaPOG2012MVA(); }
	const float &muonHZZ2012IsoRingsMVA() { return lepton_tree.muonHZZ2012IsoRingsMVA(); }
	const unsigned int &vetoId() { return lepton_tree.vetoId(); }
	const unsigned int &looseId() { return lepton_tree.looseId(); }
	const unsigned int &mediumId() { return lepton_tree.mediumId(); }
	const unsigned int &tightId() { return lepton_tree.tightId(); }
	const float &pfmva() { return lepton_tree.pfmva(); }
	const float &sceta() { return lepton_tree.sceta(); }
	const float &scenergy() { return lepton_tree.scenergy(); }
	const bool &chargesAgree() { return lepton_tree.chargesAgree(); }
	const float &eopin() { return lepton_tree.eopin(); }
	const float &ooemoop() { return lepton_tree.ooemoop(); }
	const float &fbrem() { return lepton_tree.fbrem(); }
	const float &detain() { return lepton_tree.detain(); }
	const float &dphiin() { return lepton_tree.dphiin(); }
	const float &hoe() { return lepton_tree.hoe(); }
	const float &hoetow() { return lepton_tree.hoetow(); }
	const float &sieie() { return lepton_tree.sieie(); }
	const float &d0vtx() { return lepton_tree.d0vtx(); }
	const float &dzvtx() { return lepton_tree.dzvtx(); }
	const bool &vfitprob() { return lepton_tree.vfitprob(); }
	const float &mhit() { return lepton_tree.mhit(); }
	const float &ecaliso() { return lepton_tree.ecaliso(); }
	const float &hcaliso() { return lepton_tree.hcaliso(); }
	const float &trkiso() { return lepton_tree.trkiso(); }
	const float &pfemiso03() { return lepton_tree.pfemiso03(); }
	const float &pfchiso03() { return lepton_tree.pfchiso03(); }
	const float &pfnhiso03() { return lepton_tree.pfnhiso03(); }
	const float &pfemiso04() { return lepton_tree.pfemiso04(); }
	const float &pfchiso04() { return lepton_tree.pfchiso04(); }
	const float &pfnhiso04() { return lepton_tree.pfnhiso04(); }
	const float &radiso03() { return lepton_tree.radiso03(); }
	const float &radiso04() { return lepton_tree.radiso04(); }
	const float &iso2011() { return lepton_tree.iso2011(); }
	const float &ea04() { return lepton_tree.ea04(); }
	const float &ea03() { return lepton_tree.ea03(); }
	const float &dbeta03() { return lepton_tree.dbeta03(); }
	const float &dbeta04() { return lepton_tree.dbeta04(); }
	const float &el_test_pfchiso04_trkveto() { return lepton_tree.el_test_pfchiso04_trkveto(); }
	const float &el_test_pfchiso04_dzcut() { return lepton_tree.el_test_pfchiso04_dzcut(); }
	const float &el_test_pfchiso04_ebveto() { return lepton_tree.el_test_pfchiso04_ebveto(); }
	const float &el_test_pfemiso04_ebveto() { return lepton_tree.el_test_pfemiso04_ebveto(); }
	const float &eaem04() { return lepton_tree.eaem04(); }
	const float &eanh04() { return lepton_tree.eanh04(); }
	const float &gen_drs1() { return lepton_tree.gen_drs1(); }
	const float &gen_drs3() { return lepton_tree.gen_drs3(); }
	const unsigned int &HLT_Photon22_R9Id90_HE10_Iso40_EBOnly() { return lepton_tree.HLT_Photon22_R9Id90_HE10_Iso40_EBOnly(); }
	const unsigned int &HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_version() { return lepton_tree.HLT_Photon22_R9Id90_HE10_Iso40_EBOnly_version(); }
	const unsigned int &HLT_Photon36_R9Id90_HE10_Iso40_EBOnly() { return lepton_tree.HLT_Photon36_R9Id90_HE10_Iso40_EBOnly(); }
	const unsigned int &HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_version() { return lepton_tree.HLT_Photon36_R9Id90_HE10_Iso40_EBOnly_version(); }
	const unsigned int &HLT_Photon50_R9Id90_HE10_Iso40_EBOnly() { return lepton_tree.HLT_Photon50_R9Id90_HE10_Iso40_EBOnly(); }
	const unsigned int &HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_version() { return lepton_tree.HLT_Photon50_R9Id90_HE10_Iso40_EBOnly_version(); }
	const unsigned int &HLT_Photon75_R9Id90_HE10_Iso40_EBOnly() { return lepton_tree.HLT_Photon75_R9Id90_HE10_Iso40_EBOnly(); }
	const unsigned int &HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_version() { return lepton_tree.HLT_Photon75_R9Id90_HE10_Iso40_EBOnly_version(); }
	const unsigned int &HLT_Photon90_R9Id90_HE10_Iso40_EBOnly() { return lepton_tree.HLT_Photon90_R9Id90_HE10_Iso40_EBOnly(); }
	const unsigned int &HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_version() { return lepton_tree.HLT_Photon90_R9Id90_HE10_Iso40_EBOnly_version(); }
	const unsigned int &HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_tag() { return lepton_tree.HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_tag(); }
	const unsigned int &HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_probe() { return lepton_tree.HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_probe(); }
	const unsigned int &HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_version() { return lepton_tree.HLT_Mu17_Mu8_L1sL1DoubleMu10MuOpen_version(); }
	const unsigned int &HLT_Mu17_Mu8_TrailingLeg_tag() { return lepton_tree.HLT_Mu17_Mu8_TrailingLeg_tag(); }
	const unsigned int &HLT_Mu17_Mu8_TrailingLeg_probe() { return lepton_tree.HLT_Mu17_Mu8_TrailingLeg_probe(); }
	const unsigned int &HLT_Mu17_Mu8_TrailingLeg_version() { return lepton_tree.HLT_Mu17_Mu8_TrailingLeg_version(); }
	const unsigned int &HLT_Mu17_Mu8_LeadingLeg_tag() { return lepton_tree.HLT_Mu17_Mu8_LeadingLeg_tag(); }
	const unsigned int &HLT_Mu17_Mu8_LeadingLeg_probe() { return lepton_tree.HLT_Mu17_Mu8_LeadingLeg_probe(); }
	const unsigned int &HLT_Mu17_Mu8_LeadingLeg_version() { return lepton_tree.HLT_Mu17_Mu8_LeadingLeg_version(); }
	const unsigned int &HLT_Mu17_Mu8_tag() { return lepton_tree.HLT_Mu17_Mu8_tag(); }
	const unsigned int &HLT_Mu17_Mu8_probe() { return lepton_tree.HLT_Mu17_Mu8_probe(); }
	const unsigned int &HLT_Mu17_Mu8_version() { return lepton_tree.HLT_Mu17_Mu8_version(); }
	const unsigned int &HLT_Mu17_TkMu8_TrailingLeg_tag() { return lepton_tree.HLT_Mu17_TkMu8_TrailingLeg_tag(); }
	const unsigned int &HLT_Mu17_TkMu8_TrailingLeg_probe() { return lepton_tree.HLT_Mu17_TkMu8_TrailingLeg_probe(); }
	const unsigned int &HLT_Mu17_TkMu8_TrailingLeg_version() { return lepton_tree.HLT_Mu17_TkMu8_TrailingLeg_version(); }
	const unsigned int &HLT_Mu17_TkMu8_LeadingLeg_tag() { return lepton_tree.HLT_Mu17_TkMu8_LeadingLeg_tag(); }
	const unsigned int &HLT_Mu17_TkMu8_LeadingLeg_probe() { return lepton_tree.HLT_Mu17_TkMu8_LeadingLeg_probe(); }
	const unsigned int &HLT_Mu17_TkMu8_LeadingLeg_version() { return lepton_tree.HLT_Mu17_TkMu8_LeadingLeg_version(); }
	const unsigned int &HLT_Mu17_TkMu8_TrailingLegTrkFiltered_tag() { return lepton_tree.HLT_Mu17_TkMu8_TrailingLegTrkFiltered_tag(); }
	const unsigned int &HLT_Mu17_TkMu8_TrailingLegTrkFiltered_probe() { return lepton_tree.HLT_Mu17_TkMu8_TrailingLegTrkFiltered_probe(); }
	const unsigned int &HLT_Mu17_TkMu8_TrailingLegTrkFiltered_version() { return lepton_tree.HLT_Mu17_TkMu8_TrailingLegTrkFiltered_version(); }
	const unsigned int &HLT_Mu17_TkMu8_tag() { return lepton_tree.HLT_Mu17_TkMu8_tag(); }
	const unsigned int &HLT_Mu17_TkMu8_probe() { return lepton_tree.HLT_Mu17_TkMu8_probe(); }
	const unsigned int &HLT_Mu17_TkMu8_version() { return lepton_tree.HLT_Mu17_TkMu8_version(); }
	const unsigned int &HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_tag() { return lepton_tree.HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_tag(); }
	const unsigned int &HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_probe() { return lepton_tree.HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_probe(); }
	const unsigned int &HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_version() { return lepton_tree.HLT_IsoMu24_eta2p1_L1sMu16Eta2p1_version(); }
	const unsigned int &HLT_IsoMu24_eta2p1_tag() { return lepton_tree.HLT_IsoMu24_eta2p1_tag(); }
	const unsigned int &HLT_IsoMu24_eta2p1_probe() { return lepton_tree.HLT_IsoMu24_eta2p1_probe(); }
	const unsigned int &HLT_IsoMu24_eta2p1_version() { return lepton_tree.HLT_IsoMu24_eta2p1_version(); }
	const unsigned int &HLT_Mu8_tag() { return lepton_tree.HLT_Mu8_tag(); }
	const unsigned int &HLT_Mu8_probe() { return lepton_tree.HLT_Mu8_probe(); }
	const unsigned int &HLT_Mu8_version() { return lepton_tree.HLT_Mu8_version(); }
	const unsigned int &HLT_Mu17_tag() { return lepton_tree.HLT_Mu17_tag(); }
	const unsigned int &HLT_Mu17_probe() { return lepton_tree.HLT_Mu17_probe(); }
	const unsigned int &HLT_Mu17_version() { return lepton_tree.HLT_Mu17_version(); }
	const unsigned int &HLT_Ele17_Ele8_L1sL1DoubleEG137_tag() { return lepton_tree.HLT_Ele17_Ele8_L1sL1DoubleEG137_tag(); }
	const unsigned int &HLT_Ele17_Ele8_L1sL1DoubleEG137_probe() { return lepton_tree.HLT_Ele17_Ele8_L1sL1DoubleEG137_probe(); }
	const unsigned int &HLT_Ele17_Ele8_L1sL1DoubleEG137_version() { return lepton_tree.HLT_Ele17_Ele8_L1sL1DoubleEG137_version(); }
	const unsigned int &HLT_Ele17_Ele8_LeadingLeg_tag() { return lepton_tree.HLT_Ele17_Ele8_LeadingLeg_tag(); }
	const unsigned int &HLT_Ele17_Ele8_LeadingLeg_probe() { return lepton_tree.HLT_Ele17_Ele8_LeadingLeg_probe(); }
	const unsigned int &HLT_Ele17_Ele8_LeadingLeg_version() { return lepton_tree.HLT_Ele17_Ele8_LeadingLeg_version(); }
	const unsigned int &HLT_Ele17_Ele8_TrailingLeg_tag() { return lepton_tree.HLT_Ele17_Ele8_TrailingLeg_tag(); }
	const unsigned int &HLT_Ele17_Ele8_TrailingLeg_probe() { return lepton_tree.HLT_Ele17_Ele8_TrailingLeg_probe(); }
	const unsigned int &HLT_Ele17_Ele8_TrailingLeg_version() { return lepton_tree.HLT_Ele17_Ele8_TrailingLeg_version(); }
	const unsigned int &HLT_Ele17_Ele8_tag() { return lepton_tree.HLT_Ele17_Ele8_tag(); }
	const unsigned int &HLT_Ele17_Ele8_probe() { return lepton_tree.HLT_Ele17_Ele8_probe(); }
	const unsigned int &HLT_Ele17_Ele8_version() { return lepton_tree.HLT_Ele17_Ele8_version(); }
	const unsigned int &HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_tag() { return lepton_tree.HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_tag(); }
	const unsigned int &HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_probe() { return lepton_tree.HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_probe(); }
	const unsigned int &HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_version() { return lepton_tree.HLT_Ele27_WP80_L1sL1SingleEG20ORL1SingleEG22_version(); }
	const unsigned int &HLT_Ele27_WP80_tag() { return lepton_tree.HLT_Ele27_WP80_tag(); }
	const unsigned int &HLT_Ele27_WP80_probe() { return lepton_tree.HLT_Ele27_WP80_probe(); }
	const unsigned int &HLT_Ele27_WP80_version() { return lepton_tree.HLT_Ele27_WP80_version(); }
	const unsigned int &HLT_Ele17_Ele8_Mass50_LeadingLeg_tag() { return lepton_tree.HLT_Ele17_Ele8_Mass50_LeadingLeg_tag(); }
	const unsigned int &HLT_Ele17_Ele8_Mass50_LeadingLeg_probe() { return lepton_tree.HLT_Ele17_Ele8_Mass50_LeadingLeg_probe(); }
	const unsigned int &HLT_Ele17_Ele8_Mass50_LeadingLeg_version() { return lepton_tree.HLT_Ele17_Ele8_Mass50_LeadingLeg_version(); }
	const unsigned int &HLT_Ele17_Ele8_Mass50_TrailingLeg_tag() { return lepton_tree.HLT_Ele17_Ele8_Mass50_TrailingLeg_tag(); }
	const unsigned int &HLT_Ele17_Ele8_Mass50_TrailingLeg_probe() { return lepton_tree.HLT_Ele17_Ele8_Mass50_TrailingLeg_probe(); }
	const unsigned int &HLT_Ele17_Ele8_Mass50_TrailingLeg_version() { return lepton_tree.HLT_Ele17_Ele8_Mass50_TrailingLeg_version(); }
	const unsigned int &HLT_Ele20_SC4_Mass50_LeadingLeg_tag() { return lepton_tree.HLT_Ele20_SC4_Mass50_LeadingLeg_tag(); }
	const unsigned int &HLT_Ele20_SC4_Mass50_LeadingLeg_probe() { return lepton_tree.HLT_Ele20_SC4_Mass50_LeadingLeg_probe(); }
	const unsigned int &HLT_Ele20_SC4_Mass50_LeadingLeg_version() { return lepton_tree.HLT_Ele20_SC4_Mass50_LeadingLeg_version(); }
	const unsigned int &HLT_Ele20_SC4_Mass50_TrailingLeg_tag() { return lepton_tree.HLT_Ele20_SC4_Mass50_TrailingLeg_tag(); }
	const unsigned int &HLT_Ele20_SC4_Mass50_TrailingLeg_probe() { return lepton_tree.HLT_Ele20_SC4_Mass50_TrailingLeg_probe(); }
	const unsigned int &HLT_Ele20_SC4_Mass50_TrailingLeg_version() { return lepton_tree.HLT_Ele20_SC4_Mass50_TrailingLeg_version(); }
	const unsigned int &HLT_Ele32_SC17_Mass50_LeadingLeg_tag() { return lepton_tree.HLT_Ele32_SC17_Mass50_LeadingLeg_tag(); }
	const unsigned int &HLT_Ele32_SC17_Mass50_LeadingLeg_probe() { return lepton_tree.HLT_Ele32_SC17_Mass50_LeadingLeg_probe(); }
	const unsigned int &HLT_Ele32_SC17_Mass50_LeadingLeg_version() { return lepton_tree.HLT_Ele32_SC17_Mass50_LeadingLeg_version(); }
	const unsigned int &HLT_Ele32_SC17_Mass50_TrailingLeg_tag() { return lepton_tree.HLT_Ele32_SC17_Mass50_TrailingLeg_tag(); }
	const unsigned int &HLT_Ele32_SC17_Mass50_TrailingLeg_probe() { return lepton_tree.HLT_Ele32_SC17_Mass50_TrailingLeg_probe(); }
	const unsigned int &HLT_Ele32_SC17_Mass50_TrailingLeg_version() { return lepton_tree.HLT_Ele32_SC17_Mass50_TrailingLeg_version(); }
	const unsigned int &HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_tag() { return lepton_tree.HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_tag(); }
	const unsigned int &HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_probe() { return lepton_tree.HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_probe(); }
	const unsigned int &HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version() { return lepton_tree.HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version(); }
	const unsigned int &HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_tag() { return lepton_tree.HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_tag(); }
	const unsigned int &HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_probe() { return lepton_tree.HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_probe(); }
	const unsigned int &HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version() { return lepton_tree.HLT_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version(); }
	const unsigned int &HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_tag() { return lepton_tree.HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_tag(); }
	const unsigned int &HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_probe() { return lepton_tree.HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_probe(); }
	const unsigned int &HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version() { return lepton_tree.HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_version(); }
	const unsigned int &HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_tag() { return lepton_tree.HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_tag(); }
	const unsigned int &HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_probe() { return lepton_tree.HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_probe(); }
	const unsigned int &HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version() { return lepton_tree.HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_version(); }
	const unsigned int &HLT_Ele8_CaloIdT_TrkIdVL_tag() { return lepton_tree.HLT_Ele8_CaloIdT_TrkIdVL_tag(); }
	const unsigned int &HLT_Ele8_CaloIdT_TrkIdVL_probe() { return lepton_tree.HLT_Ele8_CaloIdT_TrkIdVL_probe(); }
	const unsigned int &HLT_Ele8_CaloIdT_TrkIdVL_version() { return lepton_tree.HLT_Ele8_CaloIdT_TrkIdVL_version(); }
}
