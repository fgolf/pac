#ifndef AT_MCBTAGCOUNT_H
#define AT_MCBTAGCOUNT_H

#include <vector>
#include "at/YieldType.h"

// ROOT
#include "Math/LorentzVector.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

namespace at
{
    // bool to determine weither to apply the btag 
    bool CountBtag(const bool is_btagged, const float btag_scale_factor, const float btag_eff, const float random);

    // btag efficiency number
    double BtagEfficiency(const int flavor, const double jet_pt, const int uncertainty, const int uncertainty_light);

    // btag scale factor number
    double BtagScaleFactor(const int flavor, const double jet_pt, const int uncertainty, const int uncertainty_light);

    // get the count of the MC btags using the random number procedure
    unsigned int MCBtagCount
    (
        const std::vector<LorentzVector>& vjets_p4,
        const std::vector<bool>& vjets_btags,
        const std::vector<int>& vjets_mcflavor,
        const YieldType::value_type yield_type = YieldType::base
    );

} // namespace at

#endif // AT_MCBTAGCOUNT_H
