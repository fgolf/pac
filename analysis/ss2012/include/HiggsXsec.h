#ifndef SS_HIGGS_XSEC_H
#define SS_HIGGS_XSEC_H

#include "at/Sample.h"

namespace ss
{
    struct HiggsProduction
    {
        enum value_type
        {
            ZH,
            WH,
            TTH,
            static_size
        };
    };

    struct HiggsDecay
    {
        enum value_type
        {
            HToWW,
            HToZZ,
            HToTauTau,
            static_size
        };
    };

    // Check the MC status 3 and determine which process.  This is needed for the following samples 
    // /WH_ZH_TTH_HToTauTau_M-125_lepdecay_8TeV-pythia6-tauola/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM
    // /WH_ZH_TTH_HToZZ_M-125_8TeV-pythia6/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM
    // /WH_ZH_TTH_HToWW_M-125_8TeV-pythia6/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM
    // M_Higgs = 125 GeV
    HiggsProduction::value_type GetHiggsProduction();
    HiggsDecay::value_type GetHiggsDecay();

    // Given the higgs process, determine the xsec
    // The numbers were taken from the higgs twiki:
    // https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageAt8TeV
    // M_Higgs = 125 GeV
    // cross sections in (pb)
    double GetHiggsProductionXsec(const HiggsProduction::value_type higgs_production);
    double GetHiggsBranchingRatio(const HiggsDecay::value_type higgs_decay);
    double GetHiggsXsec(const HiggsProduction::value_type higgs_production, const HiggsDecay::value_type higgs_decay);

    // the number generated 
    // sample dependent --> fractions hard coded
    // http://www.t2.ucsd.edu/tastwiki/bin/view/CMS/Summer12MonteCarlo53X_Slim_Winter13#Higgs  
    double GetHiggsNumGenerated
    (
        const at::Sample::value_type sample, 
        const HiggsProduction::value_type higgs_production, 
        const unsigned int num_generated
    );

    // scale 1fb using the xsec from GetHiggsXsec()
    // sample dependent --> fractions hard coded
    // http://www.t2.ucsd.edu/tastwiki/bin/view/CMS/Summer12MonteCarlo53X_Slim_Winter13#Higgs  
    double GetHiggsScale1fb
    (
        const at::Sample::value_type sample, 
        const HiggsProduction::value_type higgs_production,
        const HiggsDecay::value_type higgs_decay,
        const unsigned int num_generated
    );

    // print a summary table of the xsecs
    void PrintHiggsXsecTable(const bool print_tex = false);
}

#endif // SS_HIGGS_XSEC_H
