#include "ScaleFactors.h"
#include "CMS2.h"
#include "AnalysisType.h"
#include "at/DileptonHypType.h"
#include <utility>
#include <cmath>

using namespace std;

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

// from ra5 twiki:
// https://twiki.cern.ch/twiki/bin/viewauth/CMS/SameSignDilepton2013#Trigger_Efficiencies_and_SF
float DileptonTriggerScaleFactorSystUnc() 
{
    return 0.06;
}

// general 
float DileptonTagAndProbeScaleFactor(const int l1_id, const float l1_pt, const float l1_eta, const int l2_id, const float l2_pt, const float l2_eta)
{
    const float sf1 = TagAndProbeScaleFactor(l1_id, l1_pt, l1_eta);
    const float sf2 = TagAndProbeScaleFactor(l2_id, l2_pt, l2_eta);
    return (sf1 * sf2);
}

float DileptonTagAndProbeScaleFactorSystUnc(const int l1_id, const float l1_pt, const float l1_eta, const int l2_id, const float l2_pt, const float l2_eta)
{
    const float e1  = TagAndProbeScaleFactorSystUnc(l1_id, l1_pt, l1_eta);
    const float e2  = TagAndProbeScaleFactorSystUnc(l2_id, l2_pt, l2_eta);
    return (e1 + e2); // fully correlated
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
        
        if (10 < pt && pt <= 15)
        {
            if (0.00   < aeta && aeta <= 0.80  ) {return 0.834;}
            if (0.80   < aeta && aeta <= 1.4442) {return 0.973;}
            if (1.566  < aeta && aeta <= 2.00  ) {return 0.954;}
            if (2.00   < aeta)                   {return 1.119;}
        }
        else if (15 < pt && pt <= 20)
        {
            if (0.00   < aeta && aeta <= 0.80  ) {return 0.918;}
            if (0.80   < aeta && aeta <= 1.4442) {return 0.906;}
            if (1.566  < aeta && aeta <= 2.00  ) {return 0.909;}
            if (2.00   < aeta)                   {return 0.944;}
        }
        else if (20 < pt && pt <= 30)
        {
            if (0.00   < aeta && aeta <= 0.80  ) {return 0.954;}
            if (0.80   < aeta && aeta <= 1.4442) {return 0.923;}
            if (1.566  < aeta && aeta <= 2.00  ) {return 0.921;}
            if (2.00   < aeta)                   {return 0.993;}
        }
        else if (30 < pt && pt <= 40)
        {
            if (0.00   < aeta && aeta <= 0.80  ) {return 0.960;}
            if (0.80   < aeta && aeta <= 1.4442) {return 0.935;}
            if (1.566  < aeta && aeta <= 2.00  ) {return 0.924;}
            if (2.00   < aeta)                   {return 0.959;}
        }
        else if (40 < pt && pt <= 50)
        {
            if (0.00   < aeta && aeta <= 0.80  ) {return 0.972;}
            if (0.80   < aeta && aeta <= 1.4442) {return 0.955;}
            if (1.566  < aeta && aeta <= 2.00  ) {return 0.950;}
            if (2.00   < aeta)                   {return 0.968;}
        }
        else if (pt > 50)
        {
            if (0.00   < aeta && aeta <= 0.80  ) {return 0.969;}
            if (0.80   < aeta && aeta <= 1.4442) {return 0.956;}
            if (1.566  < aeta && aeta <= 2.00  ) {return 0.995;}
            if (2.00   < aeta)                   {return 0.969;}
        }

        // if we get here, return bogus value
        cout << "[ss::TagAndProbeScaleFactor] WARNING -> missed coverage -- returning bogus value -999999" << endl;
        cout << Form("[ss::TagAndProbeScaleFactor] id: %d pt: %f eta: %f", id, pt, aeta) << endl; 
        return -999999.0;
    }

    if (abs(id)==13) 
    {
        if (10 < pt && pt <= 15)
        {
            if (0.00  < aeta && aeta <= 1.20) {return 0.973;}
            if (1.20  < aeta)                 {return 0.954;}
        }
        else if (15 < pt && pt <= 20)
        {
            if (0.00  < aeta && aeta <= 1.20) {return 0.957;}
            if (1.20  < aeta)                 {return 0.971;}
        }
        else if (20 < pt && pt <= 30)
        {
            if (0.00  < aeta && aeta <= 1.20) {return 0.964;}
            if (1.20  < aeta)                 {return 0.981;}
        }
        else if (30 < pt && pt <= 40)
        {
            if (0.00  < aeta && aeta <= 1.20) {return 0.971;}
            if (1.20  < aeta)                 {return 0.978;}
        }
        else if (40 < pt && pt <= 50)
        {
            if (0.00  < aeta && aeta <= 1.20) {return 0.978;}
            if (1.20  < aeta)                 {return 0.984;}
        }
        else if (pt > 50)
        {
            if (0.00  < aeta && aeta <= 1.20) {return 0.974;}
            if (1.20  < aeta)                 {return 0.977;}
        }

        // if we get here, return bogus value
        cout << "[ss::TagAndProbeScaleFactor] WARNING -> missed coverage -- returning bogus value -999999" << endl;
        cout << Form("[ss::TagAndProbeScaleFactor] id: %d pt: %f eta: %f", id, pt, aeta) << endl; 
        return -999999.0;
    }

    // if we get here, return bogus value
    return -999999.0;
}

// Data/MC scale factor for the ID/Iso efficiencies for electrons 
// NOTE: the eta here is the super cluser eta
float TagAndProbeScaleFactorSystUnc(int id, float pt, float eta)
{
    if (abs(id)==11)
    {
        if (10 < pt && pt <= 15) {return sqrt(0.10*0.10 + 0.03*0.03);}
        if (15 < pt && pt <= 30) {return sqrt(0.05*0.05 + 0.03*0.03);}
        else if (pt > 30)        {return sqrt(0.05*0.05 + 0.03*0.03);}
    }
    if (abs(id)==13)
    {
        if (10 < pt && pt <= 15) {return sqrt(0.05*0.05 + 0.05*0.05);}
        if (15 < pt && pt <= 30) {return sqrt(0.03*0.03 + 0.05*0.05);}
        else if (pt > 30)        {return sqrt(0.03*0.03 + 0.03*0.03);}
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
    const float lep_pt   = trailing_p4.pt();
    
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
// analysis type value: 0 high pt, 1 low pt, 2 vlow pt
// MC used: /TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM
std::pair<float, float> TTGammaScaleFactor(const unsigned int sr_num, const unsigned int analysis_type)
{
    // high pT results
    if (analysis_type == 0)
    {
        // number passing ttbar events for Signal Region 0
        const float N_ttbar_SR0 = 765814.06;

        // number passing ttbar events for Signal Region sr_num 
        float N_ttbar_SRn = -999999.0;
        switch (sr_num)
        {
            case 0  : N_ttbar_SRn = 765814.06 ; break;
            case 1  : N_ttbar_SRn = 138496.48 ; break;
            case 2  : N_ttbar_SRn = 11352.13  ; break;
            case 3  : N_ttbar_SRn = 74148.16  ; break;
            case 4  : N_ttbar_SRn = 39103.90  ; break;
            case 5  : N_ttbar_SRn = 37455.95  ; break;
            case 6  : N_ttbar_SRn = 8142.28   ; break;
            case 7  : N_ttbar_SRn = 13021.80  ; break;
            case 8  : N_ttbar_SRn = 16958.17  ; break;
            case 10 : N_ttbar_SRn = 379888.03 ; break;
            case 11 : N_ttbar_SRn = 69087.73  ; break;
            case 12 : N_ttbar_SRn = 5731.75   ; break;
            case 13 : N_ttbar_SRn = 33950.84  ; break;
            case 14 : N_ttbar_SRn = 17628.79  ; break;
            case 15 : N_ttbar_SRn = 19335.24  ; break;
            case 16 : N_ttbar_SRn = 4087.10   ; break;
            case 17 : N_ttbar_SRn = 6300.05   ; break;
            case 18 : N_ttbar_SRn = 7762.02   ; break;
            case 20 : N_ttbar_SRn = 211825.67 ; break;
            case 21 : N_ttbar_SRn = 40484.23  ; break;
            case 22 : N_ttbar_SRn = 3146.72   ; break;
            case 23 : N_ttbar_SRn = 28366.49  ; break;
            case 24 : N_ttbar_SRn = 15690.63  ; break;
            case 25 : N_ttbar_SRn = 7382.87   ; break;
            case 26 : N_ttbar_SRn = 1929.73   ; break;
            case 27 : N_ttbar_SRn = 4300.23   ; break;
            case 28 : N_ttbar_SRn = 6313.33   ; break;
            case 30 : N_ttbar_SRn = 209175.67 ; break;
            case 31 : N_ttbar_SRn = 209175.67 ; break;
            case 32 : N_ttbar_SRn = 52516.80  ; break;
            case 33 : N_ttbar_SRn = 19546.44  ; break;
            case 34 : N_ttbar_SRn = 586052.12 ; break;
            case 35 : N_ttbar_SRn = 586052.12 ; break;
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
        const float N_ttbar_SR0 = 350696.59;

        // number passing ttbar events for Signal Region sr_num 
        float N_ttbar_SRn = -999999.0;
        switch (sr_num)
        {
            case 0  : N_ttbar_SRn = 350696.59 ; break; 
            case 1  : N_ttbar_SRn = 71646.70  ; break; 
            case 2  : N_ttbar_SRn = 12293.04  ; break; 
            case 3  : N_ttbar_SRn = 66772.94  ; break; 
            case 4  : N_ttbar_SRn = 42921.61  ; break; 
            case 5  : N_ttbar_SRn = 25738.51  ; break; 
            case 6  : N_ttbar_SRn = 8977.41   ; break; 
            case 7  : N_ttbar_SRn = 14350.30  ; break; 
            case 8  : N_ttbar_SRn = 19529.59  ; break; 
            case 10 : N_ttbar_SRn = 165850.39 ; break; 
            case 11 : N_ttbar_SRn = 35337.00  ; break; 
            case 12 : N_ttbar_SRn = 6223.78   ; break; 
            case 13 : N_ttbar_SRn = 30400.45  ; break; 
            case 14 : N_ttbar_SRn = 19329.94  ; break; 
            case 15 : N_ttbar_SRn = 13152.16  ; break; 
            case 16 : N_ttbar_SRn = 4501.07   ; break; 
            case 17 : N_ttbar_SRn = 6895.11   ; break; 
            case 18 : N_ttbar_SRn = 8922.83   ; break; 
            case 20 : N_ttbar_SRn = 122273.79 ; break; 
            case 21 : N_ttbar_SRn = 22117.01  ; break; 
            case 22 : N_ttbar_SRn = 3417.46   ; break; 
            case 23 : N_ttbar_SRn = 26074.65  ; break; 
            case 24 : N_ttbar_SRn = 17306.83  ; break; 
            case 25 : N_ttbar_SRn = 5601.37   ; break; 
            case 26 : N_ttbar_SRn = 2157.63   ; break; 
            case 27 : N_ttbar_SRn = 4841.90   ; break; 
            case 28 : N_ttbar_SRn = 7341.33   ; break; 
            default : 
                      std::cout << Form("[ss::TTGammaScaleFactor] Signal Region %u not valid.  Return bogus value.", sr_num) << std::endl; 
                      return std::make_pair(-999999.0 , -999999.0); 
        }

        // return the scale factor 
        const float sf_value = N_ttbar_SRn / N_ttbar_SR0;
        const float sf_error = sqrt(sf_value * (1.0 - sf_value) / N_ttbar_SR0);
        return std::make_pair(sf_value, sf_error);
    }
    // very low pT results
    else if (analysis_type == 2)
    {
        // number passing ttbar events for Signal Region 0
        const float N_ttbar_SR0 = 355516.16;

        // number passing ttbar events for Signal Region sr_num 
        float N_ttbar_SRn = -999999.0;
        switch (sr_num)
        {
            case 0  : N_ttbar_SRn = 355516.16 ; break; 
            case 1  : N_ttbar_SRn = 72456.09  ; break; 
            case 2  : N_ttbar_SRn = 12417.48  ; break; 
            case 3  : N_ttbar_SRn = 67650.02  ; break; 
            case 4  : N_ttbar_SRn = 43429.74  ; break; 
            case 5  : N_ttbar_SRn = 26354.46  ; break; 
            case 6  : N_ttbar_SRn = 9161.57   ; break; 
            case 7  : N_ttbar_SRn = 14815.27  ; break; 
            case 8  : N_ttbar_SRn = 20039.05  ; break; 
            case 10 : N_ttbar_SRn = 168105.98 ; break; 
            case 11 : N_ttbar_SRn = 35735.58  ; break; 
            case 12 : N_ttbar_SRn = 6281.94   ; break; 
            case 13 : N_ttbar_SRn = 30794.53  ; break; 
            case 14 : N_ttbar_SRn = 19552.91  ; break; 
            case 15 : N_ttbar_SRn = 13455.14  ; break; 
            case 16 : N_ttbar_SRn = 4588.36   ; break; 
            case 17 : N_ttbar_SRn = 7114.00   ; break; 
            case 18 : N_ttbar_SRn = 9147.92   ; break; 
            case 20 : N_ttbar_SRn = 124032.30 ; break; 
            case 21 : N_ttbar_SRn = 22393.74  ; break; 
            case 22 : N_ttbar_SRn = 3462.88   ; break; 
            case 23 : N_ttbar_SRn = 26427.00  ; break; 
            case 24 : N_ttbar_SRn = 17534.63  ; break; 
            case 25 : N_ttbar_SRn = 5758.05   ; break; 
            case 26 : N_ttbar_SRn = 2215.24   ; break; 
            case 27 : N_ttbar_SRn = 5008.78   ; break; 
            case 28 : N_ttbar_SRn = 7548.44   ; break; 
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
//      analysis_type = 0 --> high_pt anlysis, 1 --> low_pt analysis,  2 --> vlow_pt analysis 
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
