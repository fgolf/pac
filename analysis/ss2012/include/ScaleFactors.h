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
    const ss::AnalysisType::value_type& anal_type,
    const LorentzVector& trailing_p4
);

// Lepton ID and isolatoin efficiency (full event -- CMS2)
float DileptonTagAndProbeScaleFactor(const int hyp_idx);

// Lepton ID and isolatoin efficiency (full event -- general)
float DileptonTagAndProbeScaleFactor
(
    const int l1_id, 
    const LorentzVector& l1_p4, 
    const int l2_id, 
    const LorentzVector& l2_p4
);

// Lepton ID and isolatoin efficiency (lepton)
float TagAndProbeScaleFactor(int id, float pt, float eta);

#endif
