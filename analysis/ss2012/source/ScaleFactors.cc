#include "ScaleFactors.h"
#include "CMS2.h"
#include "AnalysisType.h"
#include "at/DileptonHypType.h"

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
            return -999999.0;
        }
        
        if (10 < pt && pt < 15)
        {
            if (0.00   < aeta && aeta < 0.80  ) {return 0.834;}
            if (0.80   < aeta && aeta < 1.4442) {return 0.973;}
            if (1.566  < aeta && aeta < 2.00  ) {return 0.954;}
            if (2.00   < aeta && aeta < 2.50  ) {return 1.119;}
        }
        else if (15 < pt && pt < 20)
        {
            if (0.00   < aeta && aeta < 0.80  ) {return 0.918;}
            if (0.80   < aeta && aeta < 1.4442) {return 0.906;}
            if (1.566  < aeta && aeta < 2.00  ) {return 0.909;}
            if (2.00   < aeta && aeta < 2.50  ) {return 0.944;}
        }
        else if (20 < pt && pt < 30)
        {
            if (0.00   < aeta && aeta < 0.80  ) {return 0.954;}
            if (0.80   < aeta && aeta < 1.4442) {return 0.923;}
            if (1.566  < aeta && aeta < 2.00  ) {return 0.921;}
            if (2.00   < aeta && aeta < 2.50  ) {return 0.993;}
        }
        else if (30 < pt && pt < 40)
        {
            if (0.00   < aeta && aeta < 0.80  ) {return 0.960;}
            if (0.80   < aeta && aeta < 1.4442) {return 0.935;}
            if (1.566  < aeta && aeta < 2.00  ) {return 0.924;}
            if (2.00   < aeta && aeta < 2.50  ) {return 0.959;}
        }
        else if (40 < pt && pt < 50)
        {
            if (0.00   < aeta && aeta < 0.80  ) {return 0.972;}
            if (0.80   < aeta && aeta < 1.4442) {return 0.955;}
            if (1.566  < aeta && aeta < 2.00  ) {return 0.950;}
            if (2.00   < aeta && aeta < 2.50  ) {return 0.968;}
        }
        else if (pt > 50)
        {
            if (0.00   < aeta && aeta < 0.80  ) {return 0.969;}
            if (0.80   < aeta && aeta < 1.4442) {return 0.956;}
            if (1.566  < aeta && aeta < 2.00  ) {return 0.995;}
            if (2.00   < aeta && aeta < 2.50  ) {return 0.969;}
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
            if (1.20  < aeta && aeta < 2.50) {return 0.954;}
        }
        else if (15 < pt && pt < 20)
        {
            if (0.00  < aeta && aeta < 1.20) {return 0.957;}
            if (1.20  < aeta && aeta < 2.50) {return 0.971;}
        }
        else if (20 < pt && pt < 30)
        {
            if (0.00  < aeta && aeta < 1.20) {return 0.964;}
            if (1.20  < aeta && aeta < 2.50) {return 0.981;}
        }
        else if (30 < pt && pt < 40)
        {
            if (0.00  < aeta && aeta < 1.20) {return 0.971;}
            if (1.20  < aeta && aeta < 2.50) {return 0.978;}
        }
        else if (40 < pt && pt < 50)
        {
            if (0.00  < aeta && aeta < 1.20) {return 0.978;}
            if (1.20  < aeta && aeta < 2.50) {return 0.984;}
        }
        else if (pt > 50)
        {
            if (0.00  < aeta && aeta < 1.20) {return 0.974;}
            if (1.20  < aeta && aeta < 2.50) {return 0.977;}
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
        // not measured yet
        return 0.0;
    }

    return 0.0;
}
