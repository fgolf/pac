#ifndef EFFICIENCYMODELTOOLS_H
#define EFFICIENCYMODELTOOLS_H

#include "GenParticleStruct.h"
#include "at/DileptonHypType.h"
#include "at/DileptonChargeType.h"
#include <utility>
#include <vector>
#include "Math/LorentzVector.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

namespace efftools {

    // get reco lepton matched to a given gen lepton
    std::pair<LorentzVector, int> getRecoLepton (struct GenParticleStruct& struct1);

    // get reco jets for same sign analysis, perform overlap removal for gen hyp and all good reco leptons
    std::vector<unsigned int> getRecoJets (struct GenParticleStruct& struct1, struct GenParticleStruct& struct2);

    // get reco jets for same sign analysis, perform overlap removal for a given hyp and all good reco leptons
    std::vector<unsigned int> getRecoJets (unsigned int hidx);

    // get reco jets for same sign analysis, perform overlap removal for all good reco leptons
    std::vector<unsigned int> getRecoJets ();

    // calculate HT for a collection of jets
    float getHT (std::vector<unsigned int>& jets);

    // make hyps from gen leptons
    std::vector<std::pair<GenParticleStruct, GenParticleStruct> > makeGenHyps (float eta_cut = 2.4, bool removeLeptonsOverlappingWithPartons = false);

    // choose the best hyp for same sign analysis given lepton pt cuts and type (SS, OS, ALL)
    std::pair<GenParticleStruct, GenParticleStruct> getGenHyp (float pt1_cut, float pt2_cut, at::DileptonChargeType::value_type hypType);

    // calculate gen ht
    float getGenHT(float pt_cut, float eta_cut);

    // get gen jets
    std::vector<LorentzVector> getGenJets (float pt_cut, float eta_cut);

    // get gen b jets
    std::vector<LorentzVector> getGenBjets (float pt_cut, float eta_cut);

    // get reco jet matched to a given gen jet
    int getRecoJet (LorentzVector p4);

    // get gen particle matched to a given reco jet
    int getGenParton (LorentzVector p4);

    // check if gen lepton overlaps with a status 3 parton (quark or gluon)
    bool leptonOverlapsWithParton(LorentzVector p4, float parton_pt = 20., float dr = 0.3);

    // get gen hyp type (ee, em, mm)
    at::DileptonHypType::value_type getHypType (int id1, int id2);
    
}

#endif
