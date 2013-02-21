#include "SignalBinInfo.h"
#include <iostream>

using namespace std;
using namespace at;

namespace ss
{
    // construct:
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
        , nbinsy(x_num_bins)
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
                //m0:  350-1200
                //m12: 0-800
                return MakeSignalBinInfo(25.0f, 325.0f, 1225.0f, 25.0f, 0.0f, 850.f);
                break;
            default:
                // return bogus value with warning
                cout << "[ss::GetSignalBinInfo] Warning: not a signal sample -- return default bins" << endl;
                SignalBinInfo bin_info(100u, 0.0f, 100.0f, 100u, 0.0f, 100.0f);
                return bin_info;
        }
    }


} // namespace ss
