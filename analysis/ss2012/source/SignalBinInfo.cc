#include "SignalBinInfo.h"
#include <iostream>

using namespace std;
using namespace at;

namespace ss
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
    {}

    SignalBinInfo::SignalBinInfo
    (
        const unsigned int x_num_bins,
        const float x_min,
        const float x_max,
        const unsigned int y_num_bins,
        const float y_min,
        const float y_max
    )
        : nbinsx(x_num_bins)
        , xmin(x_min)
        , xmax(x_max)
        , xwidth((x_max-x_min)/static_cast<float>(x_num_bins))
        , nbinsy(y_num_bins)
        , ymin(y_min)
        , ymax(y_max)
        , ywidth((y_max-y_min)/static_cast<float>(y_num_bins))
    {}

    // non-member methods:

    // make signal bin info
    SignalBinInfo MakeSignalBinInfo
    (
        const float x_bin_width,
        const float x_min,
        const float x_max,
        const float y_bin_width,
        const float y_min,
        const float y_max
    )
    {
        const unsigned int x_num_bins = static_cast<unsigned int>((x_max - x_min)/x_bin_width);
        const unsigned int y_num_bins = static_cast<unsigned int>((y_max - y_min)/y_bin_width);
        return SignalBinInfo(x_num_bins, x_min, x_max, y_num_bins, y_min, y_max); 
    }

    // return the binning info for a specific signal sample 
    SignalBinInfo GetSignalBinInfo(const at::Sample::value_type sample)
    {
        switch(sample)
        {
            case Sample::ttjets:
                // used for SSTop.  Only need points for the various channels 
                // bin 1, 1: ee
                // bin 2, 1: em
                // bin 3, 1: mm
                // bin 4, 1: ll
                return MakeSignalBinInfo(1, 0, 1, 1, 0, 1);  
                break;
            case Sample::t1tttt:
                // /SMS-T1tttt_Mgluino-350to1200_mLSP-0to850_8TeV-Pythia6Z/StoreResults-PU_START52_V9_FastSim-v1/USER 
                // m_gluino:  350-1200
                // m_lsp: 0-850
                // return MakeSignalBinInfo(25.0f, 325.0f, 1225.0f, 25.0f, 0.0f, 875.f);
                return MakeSignalBinInfo(25.0f, 400.0f, 1425.0f, 25.0f, 0.0f, 1225.0f);  // use the same binning for both t1tttt scans
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
                return MakeSignalBinInfo(25.0f, 400.0f, 1425.0f, 25.0f, 0.0f, 1225.0f);
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
                return MakeSignalBinInfo(25.0f, 325.0f, 725.0f, 25.0f, 150.0f, 550.0f);
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
                return MakeSignalBinInfo(25.0f, 200.0f, 725.0f, 25.0f, 25.0f, 300.0f);
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
                return MakeSignalBinInfo(25.0f, 200.0f, 725.0f, 25.0f, 25.0f, 300.0f);
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
                return MakeSignalBinInfo(25.0f, 800.0f, 1225.0f, 25.0f, 225.0f, 1050.0f);
                break;
            case Sample::tchiwh:
                // /TChiwh-test/fgolf-TChiwh-test-6138c231f814ac3df24f1150dfcad736/USER 
                // m_chargino: 150-300 
                // m_lsp: 1-150 
                // charginio mass is [150, 300] GeV with 50 GeV steps
                // neutralino mass is [1 - 150] GeV with 50 GeV steps
                return MakeSignalBinInfo(50.0f, 100.0f, 350.0f, 50.0f, 0.0f, 200.0f);
                break;
            default:
                // return bogus value with warning
                cout << "[ss::GetSignalBinInfo] Warning: not a signal sample -- return default bins" << endl;
                SignalBinInfo bin_info(100u, 0.0f, 1000.0f, 100u, 0.0f, 1000.0f);
                return bin_info;
        }
    }

    std::string GetSignalBinHistLabel(const at::Sample::value_type sample)
    {
        const std::string title = at::GetSampleInfo(sample).title;
        switch(sample)
        {
            case Sample::t1tttt:                       return title + ";m_{#tilde{g}} (GeV); m_{#tilde{#chi}^{0}} (GeV)"         ; break;
            case Sample::t1tttt_scans:                 return title + ";m_{#tilde{g}} (GeV); m_{#tilde{#chi}^{0}} (GeV)"         ; break;
            case Sample::sbottomtop:                   return title + ";m_{#tilde{b}} (GeV); m_{#tilde{#chi}^{#pm}} (GeV)"       ; break;
            case Sample::tchiwh:                       return title + ";m_{#tilde{#chi}^{#pm}} (GeV); m_{#tilde{#chi}^{0}} (GeV)"; break;
            default:                                   return title + ";m_{0} (GeV); m_{12} (GeV)"                               ; break;
        }
        return title;
    }

} // namespace ss
