#ifndef SCALEFACTORS_H
#define SCALEFACTORS_H

#include "Math/LorentzVector.h"
#include "at/DileptonHypType.h"
#include "AnalysisType.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

// Trigger
float DileptonTriggerScaleFactor
(
    const at::DileptonHypType::value_type& hyp_type,
    const ewkino::AnalysisType::value_type& anal_type,
    const LorentzVector& trailing_p4
);

// Lepton ID and isolatoin efficiency (full event -- CMS2)
float DileptonTagAndProbeScaleFactor(const int hyp_idx);

// Lepton ID and isolatoin efficiency (full event -- general)
float DileptonTagAndProbeScaleFactor
(
    const int l1_id, 
    const float l1_pt, 
    const float l1_eta, 
    const int l2_id, 
    const float l2_pt, 
    const float l2_eta 
);

// Lepton ID and isolatoin efficiency (lepton)
float TagAndProbeScaleFactor(int id, float pt, float eta);

#endif
