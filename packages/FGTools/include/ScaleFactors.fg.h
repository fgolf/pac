#ifndef SCALEFACTORS_H
#define SCALEFACTORS_H

#include "Math/LorentzVector.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

float dileptonTagAndProbeScaleFactor(int hyp_idx);
float tagAndProbeScaleFactor(int id, float pt, float eta);

enum TrigEffType
{
	DzDbl,
	LeadDbl,
	Sgl,
	TrailDbl,
	N_TrigEffType
};

float dilepTriggerScaleFactor(int hyp_idx);
float dilepTriggerScaleFactor(int id1, LorentzVector &vec1, int id2, LorentzVector &vec2);
float triggerScaleFactor(enum TrigEffType trig_eff_type, int id, const LorentzVector &p4);

#endif
