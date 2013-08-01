#include "SignalBinInfo.h"
#include <iostream>

using namespace std;
using namespace at;

namespace ewkino
{
    // construct:
    SignalBinInfo::SignalBinInfo()
        : nbinsx(100)
        , xmin(0)
        , xmax(1000)
        , xwidth((xmax-xmin)/static_cast<float>(nbinsx))
        , nbinsy(100)
        , ymin(0)
        , ymax(1000)
        , ywidth((ymax-ymin)/static_cast<float>(nbinsy))
        , offset(0.0)
    {}

    SignalBinInfo::SignalBinInfo
    (
        const unsigned int x_num_bins,
        const float x_min,
        const float x_max,
        const unsigned int y_num_bins,
        const float y_min,
        const float y_max,
        const float off_set
        )
        : nbinsx(x_num_bins)
        , xmin(x_min)
        , xmax(x_max)
        , xwidth((x_max-x_min)/static_cast<float>(x_num_bins))
        , nbinsy(y_num_bins)
        , ymin(y_min)
        , ymax(y_max)
        , ywidth((y_max-y_min)/static_cast<float>(y_num_bins))
        , offset(off_set)
    {}

    SignalBinInfo::SignalBinInfo
    (
        const unsigned int x_num_bins,
        const float* x_bins,
        const unsigned int y_num_bins,
        const float* y_bins,
        const float off_set
    )
        : nbinsx(x_num_bins)
        , xmin(*x_bins)
        , xmax(*(x_bins+x_num_bins))
        , xwidth(-1)
        , nbinsy(y_num_bins)
        , ymin(*x_bins)
        , ymax(*(x_bins+y_num_bins))
        , ywidth(-1)
        , offset(off_set)
    {
        xbins.assign(x_bins,x_bins+x_num_bins+1);
        ybins.assign(y_bins,y_bins+y_num_bins+1);        
    }

    // non-member methods:

    // make signal bin info
    SignalBinInfo MakeSignalBinInfo
    (
        const float x_bin_width,
        const float x_min,
        const float x_max,
        const float y_bin_width,
        const float y_min,
        const float y_max,
        const float offset,
        const bool center_bins
    )
    {
        if (center_bins)
        {
            const unsigned int x_num_bins = static_cast<unsigned int>((x_max - x_min)/x_bin_width + 1); // +1 to center the bin
            const unsigned int y_num_bins = static_cast<unsigned int>((y_max - y_min)/y_bin_width + 1); // +1 to center the bin
            return SignalBinInfo(x_num_bins, x_min-0.5*x_bin_width, x_max+0.5*x_bin_width, y_num_bins, y_min-0.5*y_bin_width, y_max+0.5*y_bin_width, offset); 
        }
        else
        {
            const unsigned int x_num_bins = static_cast<unsigned int>((x_max - x_min)/x_bin_width);
            const unsigned int y_num_bins = static_cast<unsigned int>((y_max - y_min)/y_bin_width);
            return SignalBinInfo(x_num_bins, x_min, x_max, y_num_bins, y_min, y_max, offset); 
        }
    }

    SignalBinInfo MakeSignalBinInfo
    (
        const unsigned int x_num_bins,
        const float* x_bins,
        const unsigned int y_num_bins,
        const float* y_bins,
        const float offset,
        const bool center_bins
    )
    {
        if (center_bins)
        {
            std::vector<float> new_x_bins;
            for (unsigned int idx = 0; idx < x_num_bins; idx++)
            {
                float bin_width = (*(x_bins+idx+1)) - (*(x_bins+idx));
                if (idx == 0)
                    new_x_bins.push_back((*(x_bins+idx)) - 0.5 * bin_width);
                
                new_x_bins.push_back((*(x_bins+idx)) + 0.5 * bin_width);

                if (idx == x_num_bins-1)
                    new_x_bins.push_back((*(x_bins+idx+1)) + 0.5 * bin_width);
            }

            std::vector<float> new_y_bins;
            for (unsigned int idx = 0; idx < y_num_bins; idx++)
            {
                float bin_width = (*(y_bins+idx+1)) - (*(y_bins+idx));
                if (idx == 0)
                    new_y_bins.push_back((*(y_bins+idx)) - 0.5 * bin_width);
                
                new_y_bins.push_back((*(y_bins+idx)) + 0.5 * bin_width);

                if (idx == y_num_bins-1)
                    new_y_bins.push_back((*(y_bins+idx+1)) + 0.5 * bin_width);
            }
           
            return SignalBinInfo(x_num_bins+1, &new_x_bins[0], y_num_bins+1, &new_y_bins[0], offset); 
        }
        else
        {
            return SignalBinInfo(x_num_bins, x_bins, y_num_bins, y_bins, offset); 
        }
    }

    // return the binning info for a specific signal sample 
    SignalBinInfo GetSignalBinInfo(const at::Sample::value_type sample)
    {
        switch(sample)
        {
            case Sample::ttjets:
            case Sample::ttw:
                // used for SSTop.  Only need points for the various channels 
                return MakeSignalBinInfo(1, 0, 1, 1, 0, 1, 0);  
                break;
            case Sample::t1tttt:
                // /SMS-T1tttt_Mgluino-350to2000_mLSP-0to1650_8TeV-Pythia6Z/StoreResults-PU_START52_V9_FastSim-v1/USER
                // m_gluino:  350-2000
                // m_lsp: 0-1650
                return MakeSignalBinInfo(50.0f, 350.0f, 2000.0f, 50.0f, 0.0f, 1660.0f, 100.0f, /*center_bins=*/true);
                break;
            case Sample::t1tttt_scans:
                // using same binning for all the mass poonts points
                // /SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-400to750_mLSP-1_50GeVX50GeV_Binning/Summer12-START52_V9_FSIM-v1/AODSIM
                // /SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-800to1400_mLSP-1_50GeVX50GeV_Binning/Summer12-START52_V9_FSIM-v2/AODSIM
                // /SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-400to750_mLSP-25to550_50GeVX50GeV_Binning/Summer12-START52_V9_FSIM-v1/AODSIM
                // /SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-775to1075_mLSP-25to500_50GeVX50GeV_Binning/Summer12-START52_V9_FSIM-v1/AODSIM
                // /SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-775to1075_mLSP-525to875_50GeVX50GeV_Binning/Summer12-START52_V9_FSIM-v2/AODSIM
                // /SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-1100to1400_mLSP-25to500_50GeVX50GeV_Binning/Summer12-START52_V9_FSIM-v2/AODSIM
                // /SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-1100to1400_mLSP-525to1000_25GeVX25GeV_Binning/Summer12-START52_V9_FSIM-v2/AODSIM
                // /SMS-MadGraph_Pythia6Zstar_8TeV_T1tttt_2J_mGo-1100to1400_mLSP-1025to1200_50GeVX50GeV_Binning/Summer12-START52_V9_FSIM-v1/AODSIM
                // m_gluino:  400-1400, 25 GeV steps
                // m_lsp: 1025-1200, 25 GeV steps
                // gluino mass is [400, 750] GeV with 25 GeV steps
                // LSP mass is [150, msbottom -175] GeV with 25 GeV steps
                // neutralino mass is fixed to 50 GeV
                // ~120k events per grid point
                return MakeSignalBinInfo(25.0f, 400.0f, 1400.0f, 25.0f, 0.0f, 1200.0f, 150.0f, /*center_bins=*/true);  // RA5's new binning
                break;
            case Sample::sbottomtop:
                // /SMS-T4tW_Msbottom-325to700_mChargino-150to625_8TeV-Madgraph/Summer12-START52_V9_FSIM/USER
                // m_sbottom:  325-700
                // m_chargino: 150-625 
                // m_lsp: 50
                // sbottom mass is [325, 700] GeV with 25 GeV steps
                // chargino mass is [150, msbottom -175] GeV with 25 GeV steps
                // neutralino mass is fixed to 50 GeV
                // ~120k events per grid point
                return MakeSignalBinInfo(25.0f, 325.0f, 700.0f, 25.0f, 150.0f, 675.0f, 0.0f, /*center_bins=*/true);
                break;
            case Sample::t6ttww_x05:
                // //SMS-T6ttWW_mSbottom-200to700_mChargino-50to600_mLSP_25to300_x05_8TeV-Madgraph/Summer12-START52_V9_FSIM_UFL/USER
                // m_sbottom:  200-700
                // m_chargino: 25-300 
                // m_lsp: 50
                // sbottom mass is [325, 700] GeV with 25 GeV steps
                // chargino mass is [150, msbottom -175] GeV with 25 GeV steps
                // neutralino mass is fixed to 50 GeV
                // ~120k events per grid point
                return MakeSignalBinInfo(50.0f, 325.0f, 700.0f, 50.0f, 0.0f, 675.0f, 100.0f, /*center_bins=*/true);
                break;
            case Sample::t6ttww_x08:
                // //SMS-T6ttWW_mSbottom-200to700_mChargino-50to600_mLSP_25to300_x08_8TeV-Madgraph/Summer12-START52_V9_FSIM_UFL/USER
                // m_sbottom:  325-700
                // m_chargino: 150-625 
                // m_lsp: 50
                // sbottom mass is [325, 700] GeV with 25 GeV steps
                // chargino mass is [150, msbottom -175] GeV with 25 GeV steps
                // neutralino mass is fixed to 50 GeV
                // ~120k events per grid point
                return MakeSignalBinInfo(50.0f, 325.0f, 700.0f, 50.0f, 0.0f, 675.0f, 150.0f, /*center_bins=*/true);
                break;
            case Sample::t5tttt:
                // /SMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph/Summer12-START52_V9_FSIM_UFL/USER
                // /SMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph_900_1000/Summer12-START52_V9_FSIM_UFL/USER
                // /SMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph_1000_1075/Summer12-START52_V9_FSIM_UFL/USER
                // /SMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph_1075_1175/Summer12-START52_V9_FSIM_UFL/USER
                // /SMS-T5tttt_mGo-800to1200_mStop-225to1025_mLSP_50_8TeV-Madgraph_1175_1200/Summer12-START52_V9_FSIM_UFL/USER
                // m_sbottom:  800-1200
                // m_chargino: 225-1025 
                // m_lsp: 50
                // gluino mass in [800, 1200] GeV with 25 GeV step
                // stop mass in [225, gluino -175] GeV with 25 GeV step
                // neutralino mass is fixed to 50 GeV
                // ~120k events per grid point
                return MakeSignalBinInfo(25.0f, 800.0f, 1200.0f, 25.0f, 225.0f, 1025.0f, 625.0f, /*center_bins=*/true);
                break;
            case Sample::t5lnu:
                // /SMS-T5lnuPlusPlus_mGo-400to1400_mLSP_300to1300_8TeV-Madgraph/Summer12-START52_V9_FSIM_UFL/USER 
                // The scan is performed in the space:
                // gluino mass in [400, 1400] GeV with 25 GeV step
                // LSP mass in [0, mGluino-100] GeV with 25 GeV step
                // m_chi_pm = x * m_chi0 + (1 - x)*m_glu, x = 0.8
                //~12k events per grid point
                return MakeSignalBinInfo(25.0f, 600.0f, 1100.0f, 25.0f, 0.0f, 1050.0f, 500.0f, /*center_bins=*/true);
                break;
        case Sample::tchiwh:
        {
            // /SMS-TChiWH_WlnuHWW_2J_mChargino-250to500_mLSP-1to50_TuneZ2star_8TeV-madgraph-tauola/Summer12-START53_V7C_FSIM-v1/AODSIM
            // /SMS-TChiWH_WlnuHWW_2J_mChargino-200to500_mLSP-170to370_TuneZ2star_8TeV-madgraph-tauola/Summer12-START53_V7C_FSIM-v1/AODSIM
            // /SMS-TChiWH_WlnuHWW_2J_mChargino-130to225_mLSP-1to50_TuneZ2star_8TeV-madgraph-tauola/Summer12-START53_V7C_FSIM-v1/AODSIM
            //
            // m_chargino: 130,150,175,200,225,250,275,300,350,400,450,500
            // m_lsp: 1,20,25,45,50,70,75,95,100,120,125,145,150,170,175,195,200,220,225,245,250,270,275,295,300,320,325,345,350,370
            //
            static const float tchiwh_x_bins[] = {130,150,175,200,225,250,275,300,325,350,375,400,425,450,475,500};
            static const unsigned int tchiwh_nbins_x = sizeof(tchiwh_x_bins)/sizeof(float)-1;
            static const float tchiwh_y_bins[] = {1,20,25,45,50,70,75,95,100,120,125,145,150,170,175,195,200,220,225,245,250,270,275,295,300,320,325,345,350,370};
            static const unsigned int tchiwh_nbins_y = sizeof(tchiwh_y_bins)/sizeof(float)-1;
            return MakeSignalBinInfo(tchiwh_nbins_x, tchiwh_x_bins, tchiwh_nbins_y, tchiwh_y_bins, 0.0f, /*center_bins=*/true);
        }
        break;
        default:
            // return bogus value with warning
            cout << "[ewkino::GetSignalBinInfo] Warning: not a signal sample -- return default bins" << endl;
            SignalBinInfo bin_info(100u, 0.0f, 1000.0f, 100u, 0.0f, 1000.0f, 0.0f);
            return bin_info;
        }
    }

    std::string GetSignalBinHistLabel(const at::Sample::value_type sample)
    {
        const std::string title = at::GetSampleInfo(sample).title;
        switch(sample)
        {
        case Sample::t1tttt:     return title + ";m_{#tilde{g}} (GeV); m_{#tilde{#chi}^{0}} (GeV)"         ; break;
        case Sample::sbottomtop: return title + ";m_{#tilde{b}} (GeV); m_{#tilde{#chi}^{#pm}} (GeV)"       ; break;
        case Sample::tchiwh:     return title + ";m_{#tilde{#chi}^{#pm}} (GeV); m_{#tilde{#chi}^{0}} (GeV)"; break;
        default:                 return title + ";m_{0} (GeV); m_{12} (GeV)"                               ; break;
        }
        return title;
    }

} // namespace ss
