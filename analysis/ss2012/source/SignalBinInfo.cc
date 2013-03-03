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
            case Sample::t1tttt:
                // /SMS-T1tttt_Mgluino-350to1200_mLSP-0to850_8TeV-Pythia6Z/StoreResults-PU_START52_V9_FastSim-v1/USER 
                // m_gluino:  350-1200
                // m_lsp: 0-850
                return MakeSignalBinInfo(25.0f, 325.0f, 1225.0f, 25.0f, 0.0f, 875.f);
                break;
            case Sample::sbottomtop:
                // /SMS-T4tW_Msbottom-325to700_mChargino-150to625_8TeV-Madgraph/Summer12-START52_V9_FSIM/USER
                // m_sbottom:  325-700
                // m_chargino: 150-625 
                // m_lsp: 50
                // sbottom mass in [325, 700] GeV with 25 GeV step
                // chargino mass in [150, msbottom -175] GeV with 25 GeV step
                // neutralino mass is fixed to 50 GeV
                // ~120k events per grid point
                return MakeSignalBinInfo(25.0f, 300.0f, 725.0f, 25.0f, 125.0f, 650.0f);
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
            case Sample::t1tttt:     return title + ";m_{#tilde{g}} (GeV); m_{#tilde{#chi}^{0}} (GeV)"  ; break;
            case Sample::sbottomtop: return title + ";m_{#tilde{b}} (GeV); m_{#tilde{#chi}^{#pm}} (GeV)"; break;
            default:                 return title + ";m_{0} (GeV); m_{12} (GeV)"                        ; break;
        }
    }


} // namespace ss
