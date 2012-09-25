#ifndef SCALEFACTORS_H
#define SCALEFACTORS_H

#include "Math/LorentzVector.h"
#include "at/DileptonHypType.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

float dileptonTagAndProbeScaleFactor(int hyp_idx);
float tagAndProbeScaleFactor(int id, float pt, float eta);

struct TrigEffType
{
	enum value_type
	{
		DzDbl,
		LeadDbl,
		Sgl,
		TrailDbl,
		static_size
	};
};

float dilepTriggerScaleFactor(at::DileptonHypType::value_type& hyp_type);
float dilepTriggerScaleFactor(int hyp_idx);
float triggerScaleFactor(const TrigEffType::value_type& trig_eff_type, int id, const LorentzVector &p4);

#endif
