#include "ScaleFactors.h"
#include "CMS2.h"
#include "AnalysisType.h"
#include "at/DileptonHypType.h"
#include <utility>
#include <cmath>

// only works on CMS2
float DileptonTagAndProbeScaleFactor(const int hyp_idx)
{
    const int l1_id    = cms2.hyp_lt_id().at(hyp_idx);
    const float l1_pt  = cms2.hyp_lt_p4().at(hyp_idx).pt();
    const float l1_eta = (abs(l1_id)==13 ? cms2.hyp_lt_p4().at(hyp_idx).pt() : cms2.els_etaSC().at(cms2.hyp_lt_index().at(hyp_idx)));
    const int l2_id    = cms2.hyp_ll_id().at(hyp_idx);
    const float l2_pt  = cms2.hyp_ll_p4().at(hyp_idx).pt();
    const float l2_eta = (abs(l1_id)==13 ? cms2.hyp_ll_p4().at(hyp_idx).pt() : cms2.els_etaSC().at(cms2.hyp_ll_index().at(hyp_idx)));

    const float sf1 = TagAndProbeScaleFactor(l1_id, l1_pt, l1_eta);
    const float sf2 = TagAndProbeScaleFactor(l2_id, l2_pt, l2_eta);
    return (sf1 * sf2);
}

// general 
float DileptonTagAndProbeScaleFactor(const int l1_id, const float l1_pt, const float l1_eta, const int l2_id, const float l2_pt, const float l2_eta)
{
    const float sf1 = TagAndProbeScaleFactor(l1_id, l1_pt, l1_eta);
    const float sf2 = TagAndProbeScaleFactor(l2_id, l2_pt, l2_eta);
    return (sf1 * sf2);
}

// NOTE: eta for electrons should be SC eta
float TagAndProbeScaleFactor(int id, float pt, float eta)
{
    // haven't measured very-low pt
    if (pt < 10)
    {
        return 1.0;
    }
    const double aeta = fabs(eta);

    if (abs(id)==11) 
    {
        if (1.4442 < aeta && aeta < 1.566)
        {
            cout << "[ss::TagAndProbeScaleFactor] WARNING -> eta is in the transition region. returning bogus value -999999" << endl;
            cout << Form("[ss::TagAndProbeScaleFactor] id: %d pt: %f eta: %f", id, pt, aeta) << endl; 
            return -999999.0;
        }
        
        if (10 < pt && pt < 15)
        {
            if (0.00   < aeta && aeta < 0.80  ) {return 0.834;}
            if (0.80   < aeta && aeta < 1.4442) {return 0.973;}
            if (1.566  < aeta && aeta < 2.00  ) {return 0.954;}
            if (2.00   < aeta                 ) {return 1.119;}
        }
        else if (15 < pt && pt < 20)
        {
            if (0.00   < aeta && aeta < 0.80  ) {return 0.918;}
            if (0.80   < aeta && aeta < 1.4442) {return 0.906;}
            if (1.566  < aeta && aeta < 2.00  ) {return 0.909;}
            if (2.00   < aeta                 ) {return 0.944;}
        }
        else if (20 < pt && pt < 30)
        {
            if (0.00   < aeta && aeta < 0.80  ) {return 0.954;}
            if (0.80   < aeta && aeta < 1.4442) {return 0.923;}
            if (1.566  < aeta && aeta < 2.00  ) {return 0.921;}
            if (2.00   < aeta                 ) {return 0.993;}
        }
        else if (30 < pt && pt < 40)
        {
            if (0.00   < aeta && aeta < 0.80  ) {return 0.960;}
            if (0.80   < aeta && aeta < 1.4442) {return 0.935;}
            if (1.566  < aeta && aeta < 2.00  ) {return 0.924;}
            if (2.00   < aeta                 ) {return 0.959;}
        }
        else if (40 < pt && pt < 50)
        {
            if (0.00   < aeta && aeta < 0.80  ) {return 0.972;}
            if (0.80   < aeta && aeta < 1.4442) {return 0.955;}
            if (1.566  < aeta && aeta < 2.00  ) {return 0.950;}
            if (2.00   < aeta                 ) {return 0.968;}
        }
        else if (pt > 50)
        {
            if (0.00   < aeta && aeta < 0.80  ) {return 0.969;}
            if (0.80   < aeta && aeta < 1.4442) {return 0.956;}
            if (1.566  < aeta && aeta < 2.00  ) {return 0.995;}
            if (2.00   < aeta                 ) {return 0.969;}
        }

        // if we get here, return bogus value
        cout << "[ss::TagAndProbeScaleFactor] WARNING -> missed coverage -- returning bogus value -999999" << endl;
        cout << Form("[ss::TagAndProbeScaleFactor] id: %d pt: %f eta: %f", id, pt, aeta) << endl; 
        return -999999.0;
    }

    if (abs(id)==13) 
    {
        if (10 < pt && pt < 15)
        {
            if (0.00  < aeta && aeta < 1.20) {return 0.973;}
            if (1.20  < aeta               ) {return 0.954;}
        }
        else if (15 < pt && pt < 20)
        {
            if (0.00  < aeta && aeta < 1.20) {return 0.957;}
            if (1.20  < aeta               ) {return 0.971;}
        }
        else if (20 < pt && pt < 30)
        {
            if (0.00  < aeta && aeta < 1.20) {return 0.964;}
            if (1.20  < aeta               ) {return 0.981;}
        }
        else if (30 < pt && pt < 40)
        {
            if (0.00  < aeta && aeta < 1.20) {return 0.971;}
            if (1.20  < aeta               ) {return 0.978;}
        }
        else if (40 < pt && pt < 50)
        {
            if (0.00  < aeta && aeta < 1.20) {return 0.978;}
            if (1.20  < aeta               ) {return 0.984;}
        }
        else if (pt > 50)
        {
            if (0.00  < aeta && aeta < 1.20) {return 0.974;}
            if (1.20  < aeta               ) {return 0.977;}
        }

        // if we get here, return bogus value
        cout << "[ss::TagAndProbeScaleFactor] WARNING -> missed coverage -- returning bogus value -999999" << endl;
        cout << Form("[ss::TagAndProbeScaleFactor] id: %d pt: %f eta: %f", id, pt, aeta) << endl; 
        return -999999.0;
    }

    // if we get here, return bogus value
    return -999999.0;
}

float DileptonTriggerScaleFactor
(
    const at::DileptonHypType::value_type& hyp_type,
    const ss::AnalysisType::value_type& anal_type,
    const LorentzVector& trailing_p4
)
{
    // values supplied by UF (ICHEP values)
    //if (hyp_type == DileptonHypType::EE)   {return 0.95;}
    //if (hyp_type == DileptonHypType::MUMU) {return 0.88;}
    //if (hyp_type == DileptonHypType::EMU)  {return 0.92;}

    // values supplied by UF (HCP values)
    //if (hyp_type == at::DileptonHypType::EE)   {return 0.960;}
    //if (hyp_type == at::DileptonHypType::MUMU) {return 0.875;}
    //if (hyp_type == at::DileptonHypType::EMU)  {return 0.934;}

    const bool is_barrel = (fabs(trailing_p4.eta()) < 1.0);
    const bool lep_pt    = trailing_p4.pt();
    
    // values supplied by ETH (LHCP value)
    if (anal_type == ss::AnalysisType::high_pt)
    {
        if (hyp_type == at::DileptonHypType::EE)   {return (lep_pt < 30 ? 0.92 : 0.96);} 
        if (hyp_type == at::DileptonHypType::MUMU) {return (is_barrel   ? 0.90 : 0.81);} 
        if (hyp_type == at::DileptonHypType::EMU)  {return 0.93;                       } 
    }
    if (anal_type == ss::AnalysisType::low_pt)
    {
        if (hyp_type == at::DileptonHypType::EE)   {return 0.93;                     } 
        if (hyp_type == at::DileptonHypType::MUMU) {return (is_barrel ? 0.94 : 0.90);} 
        if (hyp_type == at::DileptonHypType::EMU)  {return 0.93;                     } 
    }
    if (anal_type == ss::AnalysisType::vlow_pt)
    {
        // not measured yet --> using vlow_pt
        if (hyp_type == at::DileptonHypType::EE)   {return 0.93;                     } 
        if (hyp_type == at::DileptonHypType::MUMU) {return (is_barrel ? 0.94 : 0.90);} 
        if (hyp_type == at::DileptonHypType::EMU)  {return 0.93;                     } 
        return 0.0;
    }

    return 0.0;
}  

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
std::pair<float, float> TTGammaScaleFactor(const unsigned int sr_num, const unsigned int analysis_type)
{
    // high pT results
    if (analysis_type == 0)
    {
        // number passing ttbar events for Signal Region 0
        const float N_ttbar_SR0 = 751250.62;

        // number passing ttbar events for Signal Region sr_num 
        float N_ttbar_SRn = -999999.0;
        switch (sr_num)
        {
            case 0  : N_ttbar_SRn = 751250.62 ; break;
            case 1  : N_ttbar_SRn = 135849.73 ; break;
            case 2  : N_ttbar_SRn = 11143.52  ; break;
            case 3  : N_ttbar_SRn = 72756.26  ; break;
            case 4  : N_ttbar_SRn = 38384.17  ; break;
            case 5  : N_ttbar_SRn = 36759.14  ; break;
            case 6  : N_ttbar_SRn = 7998.78   ; break;
            case 7  : N_ttbar_SRn = 12780.68  ; break;
            case 8  : N_ttbar_SRn = 16657.09  ; break;
            case 10 : N_ttbar_SRn = 372659.00 ; break;
            case 11 : N_ttbar_SRn = 67766.82  ; break;
            case 12 : N_ttbar_SRn = 5626.79   ; break;
            case 13 : N_ttbar_SRn = 33315.69  ; break;
            case 14 : N_ttbar_SRn = 17304.34  ; break;
            case 15 : N_ttbar_SRn = 18976.98  ; break;
            case 16 : N_ttbar_SRn = 4015.82   ; break;
            case 17 : N_ttbar_SRn = 6182.02   ; break;
            case 18 : N_ttbar_SRn = 7625.88   ; break;
            case 20 : N_ttbar_SRn = 207860.59 ; break;
            case 21 : N_ttbar_SRn = 39718.86  ; break;
            case 22 : N_ttbar_SRn = 3088.90   ; break;
            case 23 : N_ttbar_SRn = 27836.15  ; break;
            case 24 : N_ttbar_SRn = 15404.18  ; break;
            case 25 : N_ttbar_SRn = 7249.26   ; break;
            case 26 : N_ttbar_SRn = 1895.01   ; break;
            case 27 : N_ttbar_SRn = 4222.36   ; break;
            case 28 : N_ttbar_SRn = 6200.34   ; break;
            default : 
                std::cout << Form("[ss::TTGammaScaleFactor] Signal Region %u not valid.  Return bogus value.", sr_num) << std::endl; 
                return std::make_pair(-999999.0 , -999999.0); 
        }

        // return the scale factor 
        const float sf_value = N_ttbar_SRn / N_ttbar_SR0;
        const float sf_error = sqrt(sf_value * (1.0 - sf_value) / N_ttbar_SR0);
        return std::make_pair(sf_value, sf_error);
    }
    // low pT results
    else if (analysis_type == 1)
    {
        // number passing ttbar events for Signal Region 0
        const float N_ttbar_SR0 = 312383.12;

        // number passing ttbar events for Signal Region sr_num 
        float N_ttbar_SRn = -999999.0;
        switch (sr_num)
        {
            case 0  : N_ttbar_SRn = 312383.12 ; break; 
            case 1  : N_ttbar_SRn = 63861.72  ; break; 
            case 2  : N_ttbar_SRn = 11143.52  ; break; 
            case 3  : N_ttbar_SRn = 58841.65  ; break; 
            case 4  : N_ttbar_SRn = 38384.17  ; break; 
            case 5  : N_ttbar_SRn = 21909.01  ; break; 
            case 6  : N_ttbar_SRn = 7998.78   ; break; 
            case 7  : N_ttbar_SRn = 11577.39  ; break; 
            case 8  : N_ttbar_SRn = 16657.09  ; break; 
            case 10 : N_ttbar_SRn = 147874.94 ; break; 
            case 11 : N_ttbar_SRn = 31529.23  ; break; 
            case 12 : N_ttbar_SRn = 5626.79   ; break; 
            case 13 : N_ttbar_SRn = 26851.46  ; break; 
            case 14 : N_ttbar_SRn = 17304.34  ; break; 
            case 15 : N_ttbar_SRn = 11225.76  ; break; 
            case 16 : N_ttbar_SRn = 4015.82   ; break; 
            case 17 : N_ttbar_SRn = 5583.87   ; break; 
            case 18 : N_ttbar_SRn = 7625.88   ; break; 
            case 20 : N_ttbar_SRn = 108305.35 ; break; 
            case 21 : N_ttbar_SRn = 19509.91  ; break; 
            case 22 : N_ttbar_SRn = 3088.90   ; break; 
            case 23 : N_ttbar_SRn = 22842.32  ; break; 
            case 24 : N_ttbar_SRn = 15404.18  ; break; 
            case 25 : N_ttbar_SRn = 4641.87   ; break; 
            case 26 : N_ttbar_SRn = 1895.01   ; break; 
            case 27 : N_ttbar_SRn = 3844.01   ; break; 
            case 28 : N_ttbar_SRn = 6200.34   ; break; 
            default : 
                std::cout << Form("[ss::TTGammaScaleFactor] Signal Region %u not valid.  Return bogus value.", sr_num) << std::endl; 
                return std::make_pair(-999999.0 , -999999.0); 
        }

        // return the scale factor 
        const float sf_value = N_ttbar_SRn / N_ttbar_SR0;
        const float sf_error = sqrt(sf_value * (1.0 - sf_value) / N_ttbar_SR0);
        return std::make_pair(sf_value, sf_error);
    }
    else
    {
        std::cout << Form("[ss::TTGammaScaleFactor] AnalysisType %u not valid.  Return bogus value.", analysis_type) << std::endl; 
        return std::make_pair(-999999.0 , -999999.0); 
    }
} 

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
)
{
    const std::pair<float, float> sf = TTGammaScaleFactor(sr_num, analysis_type);
    const float N_ttg_SRn_value = N_ttg_SR0_value * sf.first;
    const float N_ttg_SRn_error = N_ttg_SRn_value * sqrt(pow(sf.second/sf.first, 2) + pow(N_ttg_SR0_error/N_ttg_SR0_value, 2));
    return std::make_pair(N_ttg_SRn_value, N_ttg_SRn_error);
}
