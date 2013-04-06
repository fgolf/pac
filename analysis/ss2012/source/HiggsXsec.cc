#include "HiggsXsec.h"
#include "CTable.h"
#include "CMS2.h"
#include "mcSelections.h"
#include <stdexcept>
#include <string>
#include <iostream>

using namespace std;

namespace ss
{
    // Check the MC status 3 and determine which process.  This is needed for the following samples 
    // /WH_ZH_TTH_HToTauTau_M-125_lepdecay_8TeV-pythia6-tauola/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM
    // /WH_ZH_TTH_HToZZ_M-125_8TeV-pythia6/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM
    // /WH_ZH_TTH_HToWW_M-125_8TeV-pythia6/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM
    // M_Higgs = 125 GeV
    using namespace tas;

    HiggsProduction::value_type GetHiggsProduction()
    {
        // return the result
        switch (genps_signalProcessID())
        {
            case 24 : return HiggsProduction::ZH;  break;   //'MSUB(24)=1  !ZH production', 
            case 26 : return HiggsProduction::WH;  break;   //'MSUB(26)=1  !WH production', 
            case 121: return HiggsProduction::TTH; break;   //'MSUB(121)=1 !gg to ttH', 
            case 122: return HiggsProduction::TTH; break;   //'MSUB(122)=1 !qq to ttH', 
            default: {/*do nothing*/}
        }

        // if we get here, we failed to find something that makes sense 
        // in this context
        return HiggsProduction::static_size;
    }

    HiggsDecay::value_type GetHiggsDecay()
    {
        using namespace tas;

        // nice for troubleshooting
        //dumpDocLines();

        int h_daught_idx = -9999;
        for (size_t idx = 0; idx != genps_id().size(); idx++)
        {
            // only consider status 3
            if (genps_status().at(idx) != 3) {continue;}

            const unsigned int mother = abs(genps_id_mother().at(idx));

            // found or already found the higg's daughters index
            // --> assuming higgs decays symmetrically
            if (h_daught_idx < 0 and mother == 25)
            {
                h_daught_idx = idx; 
                break;
            } 
        }

        // determine higgs decay process
        const unsigned int h_daught_id = abs(genps_id().at(h_daught_idx));
        const bool h_to_ww = (h_daught_id==24);
        const bool h_to_zz = (h_daught_id==23);
        const bool h_to_tt = (h_daught_id==15);

        // return the result
        if (h_to_ww) {return HiggsDecay::HToWW;     }
        if (h_to_zz) {return HiggsDecay::HToZZ;     }
        if (h_to_tt) {return HiggsDecay::HToTauTau; }

        // if we get here, we failed to find something that makes sense 
        // in this context
        return HiggsDecay::static_size;
    }

    // Given the higgs process, determine the xsec
    // The numbers were taken from the higgs twiki:
    // https://twiki.cern.ch/twiki/bin/view/LHCPhysics/CERNYellowReportPageAt8TeV
    // M_Higgs = 125 GeV
    // cross sections (pb)
    double GetHiggsProductionXsec(const HiggsProduction::value_type higgs_production)
    {
        // cross sections (pb)
        static const float sigma_ZH = 0.3943;
        static const float sigma_WH = 0.6966;
        static const float sigma_ttH = 0.1302;

        switch (higgs_production)
        {
            case HiggsProduction::ZH : {return sigma_ZH ;}
            case HiggsProduction::WH : {return sigma_WH ;}
            case HiggsProduction::TTH: {return sigma_ttH;}
            default:                {return -999999.0;}
        };

        // if we're here, return bs value
        return -999999.0;
    }

    double GetHiggsBranchingRatio(const HiggsDecay::value_type higgs_decay)
    {
        // tau Branching ratio
        // http://pdg.lbl.gov/2012/listings/rpp2012-list-tau.pdf
        //static const float TauToLep = /*tau --> tau_nu e e_nu=*/0.1783 + /*tau --> tau_nu mu mu_nu=*/0.1741;

        // branching ratios
        static const float HToWW = 0.215;
        static const float HToZZ = 0.0264;
        static const float HToTauTau = 0.0632;

        switch (higgs_decay)
        {
            case HiggsDecay::HToWW    : {return HToWW;    }
            case HiggsDecay::HToZZ    : {return HToZZ;    }
            case HiggsDecay::HToTauTau: {return HToTauTau;}
            //case HiggsDecay::HToTauTau: {return HToTauTau * TauToLep;}
            default:                    {return -999999.0;}
        };

        return -999999.0;
    }

    double GetHiggsXsec(const HiggsProduction::value_type higgs_production, const HiggsDecay::value_type higgs_decay)
    {
        return GetHiggsProductionXsec(higgs_production) * GetHiggsBranchingRatio(higgs_decay);
    }

    // the number generated 
    // the number generated 
    // sample dependent --> values hard coded
    // http://www.t2.ucsd.edu/tastwiki/bin/view/CMS/Summer12MonteCarlo53X_Slim_Winter13#Higgs  
    double GetHiggsNumGenerated
    (
        const at::Sample::value_type sample, 
        const HiggsProduction::value_type higgs_production, 
        const int num_generated
    )
    {
        using namespace at;

        if (num_generated < 0)
        {
            throw std::domain_error("[ss::GetHiggsNumGenerated] ERROR -- num_generated must be > 0");
        }

        // fraction of sub-process
        float frac_zh  = -1.0;
        float frac_wh  = -1.0;
        float frac_tth = -1.0;
        switch (sample)
        {
            case Sample::wh_zh_tth_hzz: {frac_wh = 0.3; frac_zh = 0.3; frac_tth = 0.4; break;}
            case Sample::wh_zh_tth_hww: {frac_wh = 0.3; frac_zh = 0.3; frac_tth = 0.4; break;}
            case Sample::wh_zh_tth_htt: {frac_wh = 0.3; frac_zh = 0.3; frac_tth = 0.4; break;}
            default: {/*do nothing*/}
        }

        switch (higgs_production)
        {
            case HiggsProduction::ZH : {return num_generated * frac_zh ;}
            case HiggsProduction::WH : {return num_generated * frac_wh ;}
            case HiggsProduction::TTH: {return num_generated * frac_tth;}
            default: {/*do nothing*/}
        };

        // if we're here, return bs value
        return -999999.0;
    }

    // scale 1fb using the xsec from GetHiggsXsec()
    double GetHiggsScale1fb
    (
        const at::Sample::value_type sample, 
        const HiggsProduction::value_type higgs_production, 
        const HiggsDecay::value_type higgs_decay,
        const int num_generated
    )
    {
        const float xsec = GetHiggsXsec(higgs_production, higgs_decay);
        const float ngen = GetHiggsNumGenerated(sample, higgs_production, num_generated);
        if (ngen < 0)
        {
            throw std::domain_error("[ss::GetHiggsScale1fb] ERROR -- ngen must be > 0");
        }
        return ((xsec * 1000.0)/static_cast<float>(ngen));
    }

    // print a summary table of the xsecs
    void PrintHiggsXsecTable(const bool print_tex)
    {
        const string sigma_ZH_HToWW      = Form("%1.6f", GetHiggsXsec(HiggsProduction::ZH , HiggsDecay::HToWW));
        const string sigma_ZH_HToZZ      = Form("%1.6f", GetHiggsXsec(HiggsProduction::ZH , HiggsDecay::HToZZ));
        const string sigma_ZH_HToTauTau  = Form("%1.6f", GetHiggsXsec(HiggsProduction::ZH , HiggsDecay::HToTauTau));
        const string sigma_WH_HToWW      = Form("%1.6f", GetHiggsXsec(HiggsProduction::WH , HiggsDecay::HToWW));
        const string sigma_WH_HToZZ      = Form("%1.6f", GetHiggsXsec(HiggsProduction::WH , HiggsDecay::HToZZ));
        const string sigma_WH_HToTauTau  = Form("%1.6f", GetHiggsXsec(HiggsProduction::WH , HiggsDecay::HToTauTau));
        const string sigma_TTH_HToWW     = Form("%1.6f", GetHiggsXsec(HiggsProduction::TTH, HiggsDecay::HToWW));
        const string sigma_TTH_HToZZ     = Form("%1.6f", GetHiggsXsec(HiggsProduction::TTH, HiggsDecay::HToZZ));
        const string sigma_TTH_HToTauTau = Form("%1.6f", GetHiggsXsec(HiggsProduction::TTH, HiggsDecay::HToTauTau));

        CTable t;
        t.useTitle();
        t.setTitle("higgs cross sections * BR; $m_{H}$ = 150 GeV");
        t.setTable() (              "$H \\rightarrow WW$", " $H\\rightarrow ZZ$", "$H \\rightarrow \\tau\\tau$")
                     ( "ZH"        ,       sigma_ZH_HToWW,        sigma_ZH_HToZZ,            sigma_ZH_HToTauTau)
                     ( "WH"        ,       sigma_WH_HToWW,        sigma_WH_HToZZ,            sigma_WH_HToTauTau)
                     ( "t\\bar{t}H",      sigma_TTH_HToWW,       sigma_TTH_HToZZ,           sigma_TTH_HToTauTau);
        if (print_tex)
        {
            t.printTex();
        }
        else
        {
            t.print();
        }
    }
}
