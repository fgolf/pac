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

float DileptonTriggerScaleFactorSystUnc();

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

float DileptonTagAndProbeScaleFactorSystUnc
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
float TagAndProbeScaleFactorSystUnc(int id, float pt, float eta);

// Due to low stats in the TTGamma sample, we use the yield on the baseline region and 
// extrapolate to each Signal region using a scale factor derived from signal lepton
// ttbar yields:
//     N_ttgamma_SRn = N_ttgamma_sr0 * (N_ttbar_SRn / N_ttbar_SR0)
// where
//     N_ttbar_SRn   = # events with 1 lepton + 2 jets + SRn requirement
//     N_ttgamma_SR0 = baseline prediction for ttgamma from the analysis
// inputs:
//      sr_num        = SignalRegion Number: 0 - 35 (9, 19, 29 excluded) 
//      analysis_type = 0 --> high_pt anlysis, 1 --> low_pt analysis 
// returns pair<float, float> where 
//      first  = scale factor 
//      second = uncertainty 
// MC used: /TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM
std::pair<float, float> TTGammaScaleFactor(const unsigned int sr_num, const unsigned int analysis_type);

// apply the scale factor to the TTGamma prediciton for SR0
// inputs:
//      sr_num        = SignalRegion Number: 0 - 35 (9, 19, 29 excluded) 
//      analysis_type = 0 --> high_pt anlysis, 1 --> low_pt analysis 
//      N_ttg_SR0     = predictions for TTGamma sample in baseline 
// returns pair<float, float> where 
//      first  = predictions for TTGamma in SR sr_num 
//      second = uncertainty 
std::pair<float, float> ApplyTTGammaScaleFactor
(
    const unsigned int sr_num,
    const unsigned int analysis_type,
    const float N_ttg_SR0_value,
    const float N_ttg_SR0_error
);

#endif
