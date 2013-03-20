#include "ScaleFactors.h"
#include "CMS2.h"
#include "AnalysisType.h"
#include "at/DileptonHypType.h"

// only works on CMS2
float DileptonTagAndProbeScaleFactor(const int hyp_idx)
{
    const float sf1 = TagAndProbeScaleFactor(cms2.hyp_lt_id().at(hyp_idx), cms2.hyp_lt_p4().at(hyp_idx).pt(), cms2.hyp_lt_p4().at(hyp_idx).eta());
    const float sf2 = TagAndProbeScaleFactor(cms2.hyp_ll_id().at(hyp_idx), cms2.hyp_ll_p4().at(hyp_idx).pt(), cms2.hyp_ll_p4().at(hyp_idx).eta());
    return (sf1 * sf2);
}

// general 
float DileptonTagAndProbeScaleFactor(const int l1_id, const LorentzVector& l1_p4, const int l2_id, const LorentzVector& l2_p4)
{
    const float sf1 = TagAndProbeScaleFactor(l1_id, l1_p4.pt(), l1_p4.eta());
    const float sf2 = TagAndProbeScaleFactor(l2_id, l2_p4.pt(), l2_p4.eta());
    return (sf1 * sf2);
}

float TagAndProbeScaleFactor(int id, float pt, float eta)
{
    if (abs(id)==11) 
    {
        const double aeta = fabs(eta);

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
        return -999999.0;
    }

    if (abs(id)==13) 
    {
        const double aeta = fabs(eta);

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

    return 0.0;
}
