#include "ScaleFactors.h"
#include "CMS2.h"
#include "at/DileptonHypType.h"

float dileptonTagAndProbeScaleFactor(int hyp_idx)
{
    float sf1 = tagAndProbeScaleFactor(cms2.hyp_lt_id().at(hyp_idx), cms2.hyp_lt_p4().at(hyp_idx).pt(), cms2.hyp_lt_p4().at(hyp_idx).eta());
    float sf2 = tagAndProbeScaleFactor(cms2.hyp_ll_id().at(hyp_idx), cms2.hyp_ll_p4().at(hyp_idx).pt(), cms2.hyp_ll_p4().at(hyp_idx).eta());

    return (sf1 * sf2);
}

float tagAndProbeScaleFactor(int id, float pt, float eta)
{
    return 1.0; // decided to take one on Friday
}

float dilepTriggerScaleFactor(at::DileptonHypType::value_type& hyp_type)
{
    // values supplied by UF (ICHEP values)
    //if (hyp_type == DileptonHypType::EE)   {return 0.95;}
    //if (hyp_type == DileptonHypType::MUMU) {return 0.88;}
    //if (hyp_type == DileptonHypType::EMU)  {return 0.92;}

    // values supplied by UF (ICHEP values)
    if (hyp_type == at::DileptonHypType::EE)   {return 0.960;}
    if (hyp_type == at::DileptonHypType::MUMU) {return 0.875;}
    if (hyp_type == at::DileptonHypType::EMU)  {return 0.934;}
    return 0.0;
}

float dilepTriggerScaleFactor(int hyp_idx)
{
    at::DileptonHypType::value_type hyp_type = at::hyp_typeToHypType(cms2.hyp_type().at(hyp_idx));    
    return dilepTriggerScaleFactor(hyp_type);
}

float triggerScaleFactor(const TrigEffType::value_type& trig_eff_type, int id, const LorentzVector &p4)
{
    unsigned int aid  = abs(id);
    float aeta        = fabs(p4.eta()); 
    float pt          = p4.pt();

    if (aid == 11)
    {
        switch (trig_eff_type)
        {
            case TrigEffType::DzDbl:
                if (aeta < 0.000) return 0.;
                if (aeta > 2.500) return 0.;

                if (pt < 20.000) return 0.;
                if (pt > 7000.000) return 0.;

                if (aeta < 0.800000) {
                    if (pt < 22.500000) return 1.000;
                    else if (pt < 25.000000) return 1.000;
                    else if (pt < 27.500000) return 0.999;
                    else if (pt < 30.000000) return 1.000;
                    else if (pt < 35.000000) return 1.000;
                    else if (pt < 40.000000) return 1.000;
                    else if (pt < 50.000000) return 1.000;
                    else if (pt < 7000.000000) return 1.000;
                }
                else if (aeta < 1.479000) {
                    if (pt < 22.500000) return 1.000;
                    else if (pt < 25.000000) return 1.000;
                    else if (pt < 27.500000) return 1.000;
                    else if (pt < 30.000000) return 0.999;
                    else if (pt < 35.000000) return 0.999;
                    else if (pt < 40.000000) return 0.999;
                    else if (pt < 50.000000) return 0.999;
                    else if (pt < 7000.000000) return 1.000;
                }
                else if (aeta < 2.000000) {
                    if (pt < 22.500000) return 1.000;
                    else if (pt < 25.000000) return 1.000;
                    else if (pt < 27.500000) return 0.994;
                    else if (pt < 30.000000) return 0.998;
                    else if (pt < 35.000000) return 0.999;
                    else if (pt < 40.000000) return 0.999;
                    else if (pt < 50.000000) return 0.998;
                    else if (pt < 7000.000000) return 0.997;
                }
                else if (aeta < 2.500000) {
                    if (pt < 22.500000) return 1.000;
                    else if (pt < 25.000000) return 1.000;
                    else if (pt < 27.500000) return 0.991;
                    else if (pt < 30.000000) return 0.987;
                    else if (pt < 35.000000) return 0.993;
                    else if (pt < 40.000000) return 0.987;
                    else if (pt < 50.000000) return 0.987;
                    else if (pt < 7000.000000) return 0.985;
                }
                break;
            case TrigEffType::LeadDbl:
                if (aeta < 0.000) return 0.;
                if (aeta > 2.500) return 0.;

                if (pt < 20.000) return 0.;
                if (pt > 7000.000) return 0.;

                if (aeta < 0.800000) {
                    if (pt < 22.500000) return 0.929;
                    else if (pt < 25.000000) return 0.964;
                    else if (pt < 27.500000) return 0.961;
                    else if (pt < 30.000000) return 0.968;
                    else if (pt < 35.000000) return 0.972;
                    else if (pt < 40.000000) return 0.974;
                    else if (pt < 50.000000) return 0.975;
                    else if (pt < 7000.000000) return 0.977;
                }
                else if (aeta < 1.479000) {
                    if (pt < 22.500000) return 0.955;
                    else if (pt < 25.000000) return 0.972;
                    else if (pt < 27.500000) return 0.985;
                    else if (pt < 30.000000) return 0.985;
                    else if (pt < 35.000000) return 0.986;
                    else if (pt < 40.000000) return 0.992;
                    else if (pt < 50.000000) return 0.995;
                    else if (pt < 7000.000000) return 0.996;
                }
                else if (aeta < 2.000000) {
                    if (pt < 22.500000) return 0.980;
                    else if (pt < 25.000000) return 0.991;
                    else if (pt < 27.500000) return 0.986;
                    else if (pt < 30.000000) return 0.983;
                    else if (pt < 35.000000) return 0.990;
                    else if (pt < 40.000000) return 0.993;
                    else if (pt < 50.000000) return 0.995;
                    else if (pt < 7000.000000) return 0.994;
                }
                else if (aeta < 2.500000) {
                    if (pt < 22.500000) return 0.888;
                    else if (pt < 25.000000) return 0.988;
                    else if (pt < 27.500000) return 0.996;
                    else if (pt < 30.000000) return 0.992;
                    else if (pt < 35.000000) return 0.986;
                    else if (pt < 40.000000) return 0.989;
                    else if (pt < 50.000000) return 0.992;
                    else if (pt < 7000.000000) return 0.994;
                }
                break;
            case TrigEffType::Sgl:
                if (aeta < 0.000) return 0.;
                if (aeta > 2.500) return 0.;

                if (pt < 20.000) return 0.;
                if (pt > 7000.000) return 0.;

                if (aeta < 0.800000) {
                    if (pt < 22.500000) return 0.000;
                    else if (pt < 25.000000) return 0.000;
                    else if (pt < 27.500000) return 0.059;
                    else if (pt < 30.000000) return 0.739;
                    else if (pt < 35.000000) return 0.906;
                    else if (pt < 40.000000) return 0.927;
                    else if (pt < 50.000000) return 0.944;
                    else if (pt < 7000.000000) return 0.952;
                }
                else if (aeta < 1.479000) {
                    if (pt < 22.500000) return 0.001;
                    else if (pt < 25.000000) return 0.028;
                    else if (pt < 27.500000) return 0.110;
                    else if (pt < 30.000000) return 0.660;
                    else if (pt < 35.000000) return 0.913;
                    else if (pt < 40.000000) return 0.940;
                    else if (pt < 50.000000) return 0.956;
                    else if (pt < 7000.000000) return 0.969;
                }
                else if (aeta < 2.000000) {
                    if (pt < 22.500000) return 0.000;
                    else if (pt < 25.000000) return 0.007;
                    else if (pt < 27.500000) return 0.113;
                    else if (pt < 30.000000) return 0.456;
                    else if (pt < 35.000000) return 0.691;
                    else if (pt < 40.000000) return 0.746;
                    else if (pt < 50.000000) return 0.767;
                    else if (pt < 7000.000000) return 0.769;
                }
                else if (aeta < 2.500000) {
                    if (pt < 22.500000) return 0.000;
                    else if (pt < 25.000000) return 0.003;
                    else if (pt < 27.500000) return 0.087;
                    else if (pt < 30.000000) return 0.313;
                    else if (pt < 35.000000) return 0.533;
                    else if (pt < 40.000000) return 0.646;
                    else if (pt < 50.000000) return 0.695;
                    else if (pt < 7000.000000) return 0.691;
                }
                break;
            case TrigEffType::TrailDbl:
                if (aeta < 0.000) return 0.;
                if (aeta > 2.500) return 0.;

                if (pt < 20.000) return 0.;
                if (pt > 7000.000) return 0.;

                if (aeta < 0.800000) {
                    if (pt < 22.500000) return 0.948;
                    else if (pt < 25.000000) return 0.966;
                    else if (pt < 27.500000) return 0.963;
                    else if (pt < 30.000000) return 0.968;
                    else if (pt < 35.000000) return 0.969;
                    else if (pt < 40.000000) return 0.972;
                    else if (pt < 50.000000) return 0.972;
                    else if (pt < 7000.000000) return 0.976;
                }
                else if (aeta < 1.479000) {
                    if (pt < 22.500000) return 0.969;
                    else if (pt < 25.000000) return 0.972;
                    else if (pt < 27.500000) return 0.976;
                    else if (pt < 30.000000) return 0.982;
                    else if (pt < 35.000000) return 0.985;
                    else if (pt < 40.000000) return 0.986;
                    else if (pt < 50.000000) return 0.989;
                    else if (pt < 7000.000000) return 0.990;
                }
                else if (aeta < 2.000000) {
                    if (pt < 22.500000) return 0.973;
                    else if (pt < 25.000000) return 1.000;
                    else if (pt < 27.500000) return 0.983;
                    else if (pt < 30.000000) return 0.979;
                    else if (pt < 35.000000) return 0.988;
                    else if (pt < 40.000000) return 0.987;
                    else if (pt < 50.000000) return 0.990;
                    else if (pt < 7000.000000) return 0.991;
                }
                else if (aeta < 2.500000) {
                    if (pt < 22.500000) return 0.983;
                    else if (pt < 25.000000) return 0.981;
                    else if (pt < 27.500000) return 0.996;
                    else if (pt < 30.000000) return 0.989;
                    else if (pt < 35.000000) return 0.984;
                    else if (pt < 40.000000) return 0.986;
                    else if (pt < 50.000000) return 0.990;
                    else if (pt < 7000.000000) return 0.992;
                }
                break;
            case TrigEffType::static_size :
            default:
                return 0;
        };
    }
    else if (aid == 13)
    {
        switch (trig_eff_type)
        {
            case TrigEffType::DzDbl:
                if (aeta < 0.000) return 0.;
                if (aeta > 2.400) return 0.;

                if (pt < 20.000) return 0.;
                if (pt > 7000.000) return 0.;

                if (aeta < 0.800000) {
                    if (pt < 22.500000) return 0.925;
                    else if (pt < 25.000000) return 0.931;
                    else if (pt < 27.500000) return 0.923;
                    else if (pt < 30.000000) return 0.919;
                    else if (pt < 35.000000) return 0.926;
                    else if (pt < 40.000000) return 0.932;
                    else if (pt < 50.000000) return 0.936;
                    else if (pt < 7000.000000) return 0.941;
                }
                else if (aeta < 1.200000) {
                    if (pt < 22.500000) return 0.921;
                    else if (pt < 25.000000) return 0.926;
                    else if (pt < 27.500000) return 0.922;
                    else if (pt < 30.000000) return 0.931;
                    else if (pt < 35.000000) return 0.926;
                    else if (pt < 40.000000) return 0.911;
                    else if (pt < 50.000000) return 0.910;
                    else if (pt < 7000.000000) return 0.897;
                }
                else if (aeta < 2.400000) {
                    if (pt < 22.500000) return 0.879;
                    else if (pt < 25.000000) return 0.871;
                    else if (pt < 27.500000) return 0.874;
                    else if (pt < 30.000000) return 0.877;
                    else if (pt < 35.000000) return 0.880;
                    else if (pt < 40.000000) return 0.871;
                    else if (pt < 50.000000) return 0.854;
                    else if (pt < 7000.000000) return 0.846;
                }
                break;
            case TrigEffType::LeadDbl:
                if (aeta < 0.000) return 0.;
                if (aeta > 2.400) return 0.;

                if (pt < 20.000) return 0.;
                if (pt > 7000.000) return 0.;

                if (aeta < 0.800000) {
                    if (pt < 22.500000) return 0.971;
                    else if (pt < 25.000000) return 0.972;
                    else if (pt < 27.500000) return 0.980;
                    else if (pt < 30.000000) return 0.970;
                    else if (pt < 35.000000) return 0.975;
                    else if (pt < 40.000000) return 0.977;
                    else if (pt < 50.000000) return 0.976;
                    else if (pt < 7000.000000) return 0.975;
                }
                else if (aeta < 1.200000) {
                    if (pt < 22.500000) return 0.905;
                    else if (pt < 25.000000) return 0.929;
                    else if (pt < 27.500000) return 0.950;
                    else if (pt < 30.000000) return 0.934;
                    else if (pt < 35.000000) return 0.935;
                    else if (pt < 40.000000) return 0.940;
                    else if (pt < 50.000000) return 0.942;
                    else if (pt < 7000.000000) return 0.935;
                }
                else if (aeta < 2.400000) {
                    if (pt < 22.500000) return 0.886;
                    else if (pt < 25.000000) return 0.927;
                    else if (pt < 27.500000) return 0.921;
                    else if (pt < 30.000000) return 0.916;
                    else if (pt < 35.000000) return 0.918;
                    else if (pt < 40.000000) return 0.921;
                    else if (pt < 50.000000) return 0.924;
                    else if (pt < 7000.000000) return 0.923;
                }
                break;
            case TrigEffType::Sgl:
                if (aeta < 0.000) return 0.;
                if (aeta > 2.400) return 0.;

                if (pt < 20.000) return 0.;
                if (pt > 7000.000) return 0.;

                if (aeta < 0.800000) {
                    if (pt < 22.500000) return 0.001;
                    else if (pt < 25.000000) return 0.396;
                    else if (pt < 27.500000) return 0.886;
                    else if (pt < 30.000000) return 0.893;
                    else if (pt < 35.000000) return 0.914;
                    else if (pt < 40.000000) return 0.923;
                    else if (pt < 50.000000) return 0.935;
                    else if (pt < 7000.000000) return 0.945;
                }
                else if (aeta < 1.200000) {
                    if (pt < 22.500000) return 0.001;
                    else if (pt < 25.000000) return 0.369;
                    else if (pt < 27.500000) return 0.817;
                    else if (pt < 30.000000) return 0.823;
                    else if (pt < 35.000000) return 0.833;
                    else if (pt < 40.000000) return 0.854;
                    else if (pt < 50.000000) return 0.862;
                    else if (pt < 7000.000000) return 0.857;
                }
                else if (aeta < 2.400000) {
                    if (pt < 22.500000) return 0.006;
                    else if (pt < 25.000000) return 0.305;
                    else if (pt < 27.500000) return 0.597;
                    else if (pt < 30.000000) return 0.617;
                    else if (pt < 35.000000) return 0.624;
                    else if (pt < 40.000000) return 0.658;
                    else if (pt < 50.000000) return 0.703;
                    else if (pt < 7000.000000) return 0.711;
                }
                break;
            case TrigEffType::TrailDbl:
                if (aeta < 0.000) return 0.;
                if (aeta > 2.400) return 0.;

                if (pt < 20.000) return 0.;
                if (pt > 7000.000) return 0.;

                if (aeta < 0.800000) {
                    if (pt < 22.500000) return 0.975;
                    else if (pt < 25.000000) return 0.973;
                    else if (pt < 27.500000) return 0.983;
                    else if (pt < 30.000000) return 0.971;
                    else if (pt < 35.000000) return 0.977;
                    else if (pt < 40.000000) return 0.978;
                    else if (pt < 50.000000) return 0.978;
                    else if (pt < 7000.000000) return 0.977;
                }
                else if (aeta < 1.200000) {
                    if (pt < 22.500000) return 0.925;
                    else if (pt < 25.000000) return 0.938;
                    else if (pt < 27.500000) return 0.962;
                    else if (pt < 30.000000) return 0.942;
                    else if (pt < 35.000000) return 0.945;
                    else if (pt < 40.000000) return 0.950;
                    else if (pt < 50.000000) return 0.950;
                    else if (pt < 7000.000000) return 0.943;
                }
                else if (aeta < 2.400000) {
                    if (pt < 22.500000) return 0.927;
                    else if (pt < 25.000000) return 0.951;
                    else if (pt < 27.500000) return 0.947;
                    else if (pt < 30.000000) return 0.942;
                    else if (pt < 35.000000) return 0.941;
                    else if (pt < 40.000000) return 0.938;
                    else if (pt < 50.000000) return 0.939;
                    else if (pt < 7000.000000) return 0.936;
                }
                break;
            case TrigEffType::static_size:
            default:
                return 0;
        };
    }
    else
    {
        return 0.0;
    }
    return 0.0;
}
