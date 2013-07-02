#ifndef AT_GENJETINFO_H
#define AT_GENJETINFO_H

#include <vector>
#include "Math/LorentzVector.h"


// typedefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

namespace at
{
    // get gen jets
    std::vector<LorentzVector> GetGenJets(const float pt_cut, const float eta_cut);

    // get gen b jets
    std::vector<LorentzVector> GetGenBJets(const float pt_cut, const float eta_cut);

    // calculate gen ht
    float GetGenHT(const float pt_cut, const float eta_cut);

} // namespace at

#endif // AT_GENJETINFO_H
