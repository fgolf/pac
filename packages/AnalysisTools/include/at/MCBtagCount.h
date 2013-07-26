#ifndef AT_MCBTAGCOUNT_H
#define AT_MCBTAGCOUNT_H

#include <vector>
#include "at/Sample.h"
#include "at/YieldType.h"
#include "at/JetInfo.h"

// ROOT
#include "Math/LorentzVector.h"

// CORE
#include "jetSelections.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

// --------------------------------------------------------------------------
// Compute the MC scale factors and scaling up/down uncertainties
// NOT my code -- I got this from ETH and adapted it for pac
// https://twiki.cern.ch/twiki/pub/CMS/SameSignDilepton2013/BTagSF.hh
// https://twiki.cern.ch/twiki/pub/CMS/SameSignDilepton2013/BTagSF.cc
// --------------------------------------------------------------------------

namespace at
{
    // bool to determine weither to apply the btag 
    bool CountBtag
    (
        const bool is_btagged,
        const float btag_scale_factor,
        const float btag_eff,
        const float random
    );

    // btag efficiency number
    double BtagEfficiency
    (
        const BtagType btag_type,
        const int flavor,
        const double jet_pt,
        const int unc_option = 0,
        const int unc_light_light = 0
    );

    //// btag scale factor number
    double BtagScaleFactor
    (
        const BtagType btag_type,
        const int flavor,
        const float jet_pt, 
        const float jet_eta, 
        const at::Sample::value_type sample,
        const bool is_fastsim = false,
        const int unc_option = 0,
        const int unc_light_option = 0
    );

    // simple type to hold value/error for the scalefactor
    struct scale_factor_t
    {
        float value;
        float error;
    };

    // the fastsim scale factors and errors
    // I only implemented the samples we need for SameSign and commented the rest out
    scale_factor_t GetSMSScaleFactorAndError
    (
        const BtagType btag_type,
        const float jet_pt, 
        const float jet_eta, 
        const int flavor, 
        const at::Sample::value_type sample
    );

    // get the count of the MC btags using the random number procedure
    unsigned int MCBtagCount
    (
        const BtagType btag_type,
        const std::vector<LorentzVector>& vjets_p4,
        const std::vector<bool>& vjets_btags,
        const std::vector<int>& vjets_mcflavor,
        const at::Sample::value_type sample,
        const bool is_fastsim = false,
        const YieldType::value_type yield_type = YieldType::base,
        const unsigned int seed = 123456
    );

    unsigned int MCBtagCount
    (
        const at::JetBtagType::value_type btag_type,
        const std::vector<LorentzVector>& vjets_p4,
        const std::vector<bool>& vjets_btags,
        const std::vector<int>& vjets_mcflavor,
        const at::Sample::value_type sample,
        const bool is_fastsim = false,
        const YieldType::value_type yield_type = YieldType::base,
        const unsigned int seed = 123456
    );

    // get a vector of the new of the MC btags using the random number procedure
    std::vector<LorentzVector> RecountedBjets
    (
        const BtagType btag_type,
        const std::vector<LorentzVector>& vjets_p4,
        const std::vector<bool>& vjets_btags,
        const std::vector<int>& vjets_mcflavor,
        const at::Sample::value_type sample,
        const bool is_fastsim = false,
        const YieldType::value_type yield_type = YieldType::base,
        const unsigned int seed = 123456
    );

} // namespace at

#endif // AT_MCBTAGCOUNT_H
