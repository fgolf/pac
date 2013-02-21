#include "at/MCBtagCount.h"
#include "rt/is_equal.h"

// ROOT
#include "Math/LorentzVector.h"
#include "TRandom.h"

// typdefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

namespace at
{

    // bool to determine weither to apply the btag 
    bool CountBtag(const bool is_btagged, const float btag_scale_factor, const float btag_eff, const float random)
    {
        bool result = is_btagged;

        if (rt::is_equal(btag_scale_factor, 1.0f)) // no correction needed
        {
            return result; 
        }
        else if (btag_scale_factor > 1.0f)
        {                                                            
            if(not is_btagged) 
            {
                //fraction of jets that need to be upgraded
                float mistag_percent = (1.0 - btag_scale_factor)/(1.0 - (btag_scale_factor/btag_eff));        

                if (random < mistag_percent) 
                {
                    // upgrade to tagged
                    result = true;
                }
            }
        }
        else
        {                                                                    
            if (is_btagged && random > btag_scale_factor) 
            {
                // downgrage tagged to untagged
                result = false;
            }

        }

        // done
        return result;
    }

    // btag efficiency number
    double BtagEfficiency(const int flavor, const double jet_pt, const int uncertainty, const int uncertainty_light)
    {
        if (abs(flavor)==5)      {return 0.7195+uncertainty*(0.7665-0.7195);}
        else if (abs(flavor)==4) {return 0.19249+uncertainty*(0.7665 - 0.7195)/5;}
        else                     {return (0.0113428+(5.18983e-05*jet_pt))+(-2.59881e-08*(jet_pt*jet_pt))*(1+uncertainty_light*0.5);}
    }

    // btag scale factor number
    double BtagScaleFactor(const int flavor, const double jet_pt, const int uncertainty, const int uncertainty_light)
    {
        const float ptmin[] = {30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500, 600};
        const float nptbins = sizeof(ptmin)/sizeof(float);
        int binnumber=0;
        for (size_t i=0; i != nptbins-1; i++)
        {
            if (ptmin[i] < jet_pt && jet_pt < ptmin[i+1]) 
            {
                binnumber=i;
                break;
            }
        }

        if (abs(flavor)==5) 
        {
            const double SFb = 0.6981*((1.+(0.414063*jet_pt))/(1.+(0.300155*jet_pt)));
            const double SFb_error[] = 
            {
                0.0295675,
                0.0295095,
                0.0210867,
                0.0219349,
                0.0227033,
                0.0204062,
                0.0185857,
                0.0256242,
                0.0383341,
                0.0409675,
                0.0420284,
                0.0541299,
                0.0578761,
                0.0655432 
            };
            return SFb+uncertainty*1.5*SFb_error[binnumber];
        }
        if (abs(flavor)==4)
        {
            const double SFb = 0.6981*((1.+(0.414063*jet_pt))/(1.+(0.300155*jet_pt)));
            const double SFb_error[] = 
            {
                0.0295675,
                0.0295095,
                0.0210867,
                0.0219349,
                0.0227033,
                0.0204062,
                0.0185857,
                0.0256242,
                0.0383341,
                0.0409675,
                0.0420284,
                0.0541299,
                0.0578761,
                0.0655432 
            };
            return SFb+uncertainty*1.5*2*SFb_error[binnumber];   ///---? Where this come from 
        }

        else 
        {
            const double SF2012=1.10422 + -0.000523856*jet_pt + 1.14251e-06*jet_pt*jet_pt;
            if(uncertainty_light==-1)
            {
                const double SFmin = ((0.962627+(0.000448344*jet_pt))+(-1.25579e-06*(jet_pt*jet_pt)))+(4.82283e-10*(jet_pt*(jet_pt*jet_pt)));
                return SFmin*SF2012;
            }
            if(uncertainty_light==1)
            {
                const double SFmax = ((1.12368+(0.00124806*jet_pt))+(-3.9032e-06*(jet_pt*jet_pt)))+(2.80083e-09*(jet_pt*(jet_pt*jet_pt)));
                return SFmax*SF2012;
            }
            else
            {
                const double SFmean = ((1.04318+(0.000848162*jet_pt))+(-2.5795e-06*(jet_pt*jet_pt)))+(1.64156e-09*(jet_pt*(jet_pt*jet_pt)));
                return SFmean*SF2012;
            }
        }
    }

    unsigned int MCBtagCount
    (
        const std::vector<LorentzVector>& vjets_p4,
        const std::vector<bool>& vjets_btagged,
        const std::vector<int>& vjets_mcflavor,
        const at::YieldType::value_type yield_type
    )
    {
        // uncertainty type
        int unc_type = 0;
        switch (yield_type)
        {
            case at::YieldType::up:   unc_type = 1 ; break;
            case at::YieldType::down: unc_type = -1; break;
            default:                  unc_type = 0 ; break;
        }

        // uncertainty type light
        const int unc_type_light = 0;

        // random number generator
        static TRandom random(123456);

        // loop over jets
        unsigned int num_btags = 0; 
        for (size_t jidx = 0; jidx != vjets_p4.size(); jidx++)
        {
            const bool btagged   = vjets_btagged.at(jidx);
            const int jet_flavor = vjets_mcflavor.at(jidx);    
            const float pt       = vjets_p4.at(jidx).pt();

            // count the rescaled btags 
            const float eff           = BtagEfficiency (jet_flavor, pt, unc_type, unc_type_light);
            const float sf            = BtagScaleFactor(jet_flavor, pt, unc_type, unc_type_light);
            const float random_number = random.Uniform(0,1);
            if (CountBtag(btagged, sf, eff, random_number))
            {
                num_btags++; 
            }
        }
        return num_btags;
    }

} // namespace at
