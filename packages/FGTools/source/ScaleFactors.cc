#include "ScaleFactors.h"
#include "CMS2.h"
#include "DileptonHypType.h"

float dileptonTagAndProbeScaleFactor(int hyp_idx)
{
    float sf1 = tagAndProbeScaleFactor(cms2.hyp_lt_id().at(hyp_idx), cms2.hyp_lt_p4().at(hyp_idx).pt(), cms2.hyp_lt_p4().at(hyp_idx).eta());
    float sf2 = tagAndProbeScaleFactor(cms2.hyp_ll_id().at(hyp_idx), cms2.hyp_ll_p4().at(hyp_idx).pt(), cms2.hyp_ll_p4().at(hyp_idx).eta());

    return (sf1 * sf2);
}

float tagAndProbeScaleFactor(int id, float pt, float eta)
{
    unsigned int aid  = abs(id);
    float feta = fabs(eta); 

    if (aid == 11) {
        if (feta < 0.1479) {
            if (pt < 40.0 && pt > 20.0)
                return 0.9947;
            else if (pt > 40.0)
                return 0.9967;
            else
                return 0.0;
        }
        else if (feta < 2.4) {
            if (pt < 40.0 && pt > 20.0)
                return 0.9638;
            else if (pt > 40.0)
                return 0.9768;
            else
                return 0.0;
        }
        else return 0.0;
    }
    else if (aid == 13) { 
        if (feta < 0.1479) {
            if (pt < 40.0 && pt > 20.0)
                return 0.9863;
            else if (pt > 40.)
                return 0.9859;
            else
                return 0.;
        }
        else if (feta < 2.4) {
            if (pt < 40. && pt > 20.)
                return 0.9941;
            else if (pt > 40.0)
                return 0.9921;
            else
                return 0.0;
        }
        else return 0.0;
   }

    return 0.0;
}

float dilepTriggerScaleFactor(int hyp_idx)
{
    return dilepTriggerScaleFactor(cms2.hyp_lt_id().at(hyp_idx), cms2.hyp_lt_p4().at(hyp_idx),
                                   cms2.hyp_ll_id().at(hyp_idx), cms2.hyp_ll_p4().at(hyp_idx));
}

float dilepTriggerScaleFactor(int id1, LorentzVector &vec1, int id2, LorentzVector &vec2)
{
    double eff_1l = 0.0;
    double eff_1t = 0.0;
    double eff_2l = 0.0;
    double eff_2t = 0.0;
    double eff_z  = 0.0;

    DileptonHypType hyp_type = DILEPTON_EMU;
    if (abs(id1) == 13 && abs(id2) == 13)
        hyp_type = DILEPTON_MUMU;
    else if (abs(id1) == 11 && abs(id2) == 11)
        hyp_type = DILEPTON_EE;

    if (hyp_type == DILEPTON_EE || hyp_type == DILEPTON_MUMU) {
        eff_1l  = triggerScaleFactor(LeadDbl, id1, vec1);
        eff_1t  = triggerScaleFactor(TrailDbl, id1, vec1);
        eff_2l  = triggerScaleFactor(LeadDbl, id2, vec2);
        eff_2t  = triggerScaleFactor(TrailDbl, id2, vec2);
        if (vec1.pt() > vec2.pt())
            eff_z = triggerScaleFactor(DzDbl, id2, vec2);
        else
            eff_z = triggerScaleFactor(DzDbl, id1, vec1);

        return (eff_1l * eff_2t + eff_1t * eff_2l - eff_1l * eff_2l) * eff_z;
    }
    else if (hyp_type == DILEPTON_EMU) {
        eff_1l  = triggerScaleFactor(LeadDbl, id1, vec1);
        eff_1t  = triggerScaleFactor(TrailDbl, id1, vec1);
        eff_2l  = triggerScaleFactor(LeadDbl, id2, vec2);
        eff_2t  = triggerScaleFactor(TrailDbl, id2, vec2);
        if (abs(id2))
            eff_z = triggerScaleFactor(DzDbl, id2, vec2);
        else
            eff_z = triggerScaleFactor(DzDbl, id1, vec1);

        return (eff_1l * eff_2t + eff_1t * eff_2l - eff_1l * eff_2l) * sqrt(eff_z);
    }

    return 0.0;
}

float triggerScaleFactor(enum TrigEffType trig_eff_type, int id, const LorentzVector &p4)
{
    unsigned int aid  = abs(id);
    float eta = fabs(p4.eta()); 
    float pt = p4.pt();

    if (aid == 11)
    {
        switch (trig_eff_type)
        {
            case DzDbl:
                if (fabs(eta) < 0.000) return 0.;
                if (fabs(eta) > 2.500) return 0.;

                if (pt < 20.000) return 0.;
                if (pt > 7000.000) return 0.;

                if (fabs(eta) < 0.800000) {
                    if (pt < 22.500000) return 1.000;
                    else if (pt < 25.000000) return 1.000;
                    else if (pt < 27.500000) return 0.999;
                    else if (pt < 30.000000) return 1.000;
                    else if (pt < 35.000000) return 1.000;
                    else if (pt < 40.000000) return 1.000;
                    else if (pt < 50.000000) return 1.000;
                    else if (pt < 7000.000000) return 1.000;
                }
                else if (fabs(eta) < 1.479000) {
                    if (pt < 22.500000) return 1.000;
                    else if (pt < 25.000000) return 1.000;
                    else if (pt < 27.500000) return 1.000;
                    else if (pt < 30.000000) return 0.999;
                    else if (pt < 35.000000) return 0.999;
                    else if (pt < 40.000000) return 0.999;
                    else if (pt < 50.000000) return 0.999;
                    else if (pt < 7000.000000) return 1.000;
                }
                else if (fabs(eta) < 2.000000) {
                    if (pt < 22.500000) return 1.000;
                    else if (pt < 25.000000) return 1.000;
                    else if (pt < 27.500000) return 0.994;
                    else if (pt < 30.000000) return 0.998;
                    else if (pt < 35.000000) return 0.999;
                    else if (pt < 40.000000) return 0.999;
                    else if (pt < 50.000000) return 0.998;
                    else if (pt < 7000.000000) return 0.997;
                }
                else if (fabs(eta) < 2.500000) {
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
            case LeadDbl:
                if (fabs(eta) < 0.000) return 0.;
                if (fabs(eta) > 2.500) return 0.;

                if (pt < 20.000) return 0.;
                if (pt > 7000.000) return 0.;

                if (fabs(eta) < 0.800000) {
                    if (pt < 22.500000) return 0.929;
                    else if (pt < 25.000000) return 0.964;
                    else if (pt < 27.500000) return 0.961;
                    else if (pt < 30.000000) return 0.968;
                    else if (pt < 35.000000) return 0.972;
                    else if (pt < 40.000000) return 0.974;
                    else if (pt < 50.000000) return 0.975;
                    else if (pt < 7000.000000) return 0.977;
                }
                else if (fabs(eta) < 1.479000) {
                    if (pt < 22.500000) return 0.955;
                    else if (pt < 25.000000) return 0.972;
                    else if (pt < 27.500000) return 0.985;
                    else if (pt < 30.000000) return 0.985;
                    else if (pt < 35.000000) return 0.986;
                    else if (pt < 40.000000) return 0.992;
                    else if (pt < 50.000000) return 0.995;
                    else if (pt < 7000.000000) return 0.996;
                }
                else if (fabs(eta) < 2.000000) {
                    if (pt < 22.500000) return 0.980;
                    else if (pt < 25.000000) return 0.991;
                    else if (pt < 27.500000) return 0.986;
                    else if (pt < 30.000000) return 0.983;
                    else if (pt < 35.000000) return 0.990;
                    else if (pt < 40.000000) return 0.993;
                    else if (pt < 50.000000) return 0.995;
                    else if (pt < 7000.000000) return 0.994;
                }
                else if (fabs(eta) < 2.500000) {
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
            case Sgl:
                if (fabs(eta) < 0.000) return 0.;
                if (fabs(eta) > 2.500) return 0.;

                if (pt < 20.000) return 0.;
                if (pt > 7000.000) return 0.;

                if (fabs(eta) < 0.800000) {
                    if (pt < 22.500000) return 0.000;
                    else if (pt < 25.000000) return 0.000;
                    else if (pt < 27.500000) return 0.059;
                    else if (pt < 30.000000) return 0.739;
                    else if (pt < 35.000000) return 0.906;
                    else if (pt < 40.000000) return 0.927;
                    else if (pt < 50.000000) return 0.944;
                    else if (pt < 7000.000000) return 0.952;
                }
                else if (fabs(eta) < 1.479000) {
                    if (pt < 22.500000) return 0.001;
                    else if (pt < 25.000000) return 0.028;
                    else if (pt < 27.500000) return 0.110;
                    else if (pt < 30.000000) return 0.660;
                    else if (pt < 35.000000) return 0.913;
                    else if (pt < 40.000000) return 0.940;
                    else if (pt < 50.000000) return 0.956;
                    else if (pt < 7000.000000) return 0.969;
                }
                else if (fabs(eta) < 2.000000) {
                    if (pt < 22.500000) return 0.000;
                    else if (pt < 25.000000) return 0.007;
                    else if (pt < 27.500000) return 0.113;
                    else if (pt < 30.000000) return 0.456;
                    else if (pt < 35.000000) return 0.691;
                    else if (pt < 40.000000) return 0.746;
                    else if (pt < 50.000000) return 0.767;
                    else if (pt < 7000.000000) return 0.769;
                }
                else if (fabs(eta) < 2.500000) {
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
            case TrailDbl:
                if (fabs(eta) < 0.000) return 0.;
                if (fabs(eta) > 2.500) return 0.;

                if (pt < 20.000) return 0.;
                if (pt > 7000.000) return 0.;

                if (fabs(eta) < 0.800000) {
                    if (pt < 22.500000) return 0.948;
                    else if (pt < 25.000000) return 0.966;
                    else if (pt < 27.500000) return 0.963;
                    else if (pt < 30.000000) return 0.968;
                    else if (pt < 35.000000) return 0.969;
                    else if (pt < 40.000000) return 0.972;
                    else if (pt < 50.000000) return 0.972;
                    else if (pt < 7000.000000) return 0.976;
                }
                else if (fabs(eta) < 1.479000) {
                    if (pt < 22.500000) return 0.969;
                    else if (pt < 25.000000) return 0.972;
                    else if (pt < 27.500000) return 0.976;
                    else if (pt < 30.000000) return 0.982;
                    else if (pt < 35.000000) return 0.985;
                    else if (pt < 40.000000) return 0.986;
                    else if (pt < 50.000000) return 0.989;
                    else if (pt < 7000.000000) return 0.990;
                }
                else if (fabs(eta) < 2.000000) {
                    if (pt < 22.500000) return 0.973;
                    else if (pt < 25.000000) return 1.000;
                    else if (pt < 27.500000) return 0.983;
                    else if (pt < 30.000000) return 0.979;
                    else if (pt < 35.000000) return 0.988;
                    else if (pt < 40.000000) return 0.987;
                    else if (pt < 50.000000) return 0.990;
                    else if (pt < 7000.000000) return 0.991;
                }
                else if (fabs(eta) < 2.500000) {
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
            case N_TrigEffType:
            default:
                return 0;
        };
    }
    else if (aid == 13)
    {
        switch (trig_eff_type)
        {
            case DzDbl:
                if (fabs(eta) < 0.000) return 0.;
                if (fabs(eta) > 2.400) return 0.;

                if (pt < 20.000) return 0.;
                if (pt > 7000.000) return 0.;

                if (fabs(eta) < 0.800000) {
                    if (pt < 22.500000) return 0.925;
                    else if (pt < 25.000000) return 0.931;
                    else if (pt < 27.500000) return 0.923;
                    else if (pt < 30.000000) return 0.919;
                    else if (pt < 35.000000) return 0.926;
                    else if (pt < 40.000000) return 0.932;
                    else if (pt < 50.000000) return 0.936;
                    else if (pt < 7000.000000) return 0.941;
                }
                else if (fabs(eta) < 1.200000) {
                    if (pt < 22.500000) return 0.921;
                    else if (pt < 25.000000) return 0.926;
                    else if (pt < 27.500000) return 0.922;
                    else if (pt < 30.000000) return 0.931;
                    else if (pt < 35.000000) return 0.926;
                    else if (pt < 40.000000) return 0.911;
                    else if (pt < 50.000000) return 0.910;
                    else if (pt < 7000.000000) return 0.897;
                }
                else if (fabs(eta) < 2.400000) {
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
            case LeadDbl:
                if (fabs(eta) < 0.000) return 0.;
                if (fabs(eta) > 2.400) return 0.;

                if (pt < 20.000) return 0.;
                if (pt > 7000.000) return 0.;

                if (fabs(eta) < 0.800000) {
                    if (pt < 22.500000) return 0.971;
                    else if (pt < 25.000000) return 0.972;
                    else if (pt < 27.500000) return 0.980;
                    else if (pt < 30.000000) return 0.970;
                    else if (pt < 35.000000) return 0.975;
                    else if (pt < 40.000000) return 0.977;
                    else if (pt < 50.000000) return 0.976;
                    else if (pt < 7000.000000) return 0.975;
                }
                else if (fabs(eta) < 1.200000) {
                    if (pt < 22.500000) return 0.905;
                    else if (pt < 25.000000) return 0.929;
                    else if (pt < 27.500000) return 0.950;
                    else if (pt < 30.000000) return 0.934;
                    else if (pt < 35.000000) return 0.935;
                    else if (pt < 40.000000) return 0.940;
                    else if (pt < 50.000000) return 0.942;
                    else if (pt < 7000.000000) return 0.935;
                }
                else if (fabs(eta) < 2.400000) {
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
            case Sgl:
                if (fabs(eta) < 0.000) return 0.;
                if (fabs(eta) > 2.400) return 0.;

                if (pt < 20.000) return 0.;
                if (pt > 7000.000) return 0.;

                if (fabs(eta) < 0.800000) {
                    if (pt < 22.500000) return 0.001;
                    else if (pt < 25.000000) return 0.396;
                    else if (pt < 27.500000) return 0.886;
                    else if (pt < 30.000000) return 0.893;
                    else if (pt < 35.000000) return 0.914;
                    else if (pt < 40.000000) return 0.923;
                    else if (pt < 50.000000) return 0.935;
                    else if (pt < 7000.000000) return 0.945;
                }
                else if (fabs(eta) < 1.200000) {
                    if (pt < 22.500000) return 0.001;
                    else if (pt < 25.000000) return 0.369;
                    else if (pt < 27.500000) return 0.817;
                    else if (pt < 30.000000) return 0.823;
                    else if (pt < 35.000000) return 0.833;
                    else if (pt < 40.000000) return 0.854;
                    else if (pt < 50.000000) return 0.862;
                    else if (pt < 7000.000000) return 0.857;
                }
                else if (fabs(eta) < 2.400000) {
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
            case TrailDbl:
                if (fabs(eta) < 0.000) return 0.;
                if (fabs(eta) > 2.400) return 0.;

                if (pt < 20.000) return 0.;
                if (pt > 7000.000) return 0.;

                if (fabs(eta) < 0.800000) {
                    if (pt < 22.500000) return 0.975;
                    else if (pt < 25.000000) return 0.973;
                    else if (pt < 27.500000) return 0.983;
                    else if (pt < 30.000000) return 0.971;
                    else if (pt < 35.000000) return 0.977;
                    else if (pt < 40.000000) return 0.978;
                    else if (pt < 50.000000) return 0.978;
                    else if (pt < 7000.000000) return 0.977;
                }
                else if (fabs(eta) < 1.200000) {
                    if (pt < 22.500000) return 0.925;
                    else if (pt < 25.000000) return 0.938;
                    else if (pt < 27.500000) return 0.962;
                    else if (pt < 30.000000) return 0.942;
                    else if (pt < 35.000000) return 0.945;
                    else if (pt < 40.000000) return 0.950;
                    else if (pt < 50.000000) return 0.950;
                    else if (pt < 7000.000000) return 0.943;
                }
                else if (fabs(eta) < 2.400000) {
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
            case N_TrigEffType:
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
