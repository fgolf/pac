#ifndef SS_SIGNALBININFO_H
#define SS_SIGNALBININFO_H

#include "at/Sample.h"

namespace ss
{
    struct SignalBinInfo
    {
        // construct:
        SignalBinInfo
        (
            const unsigned int x_num_bins,
            const float x_min,
            const float x_max,
            const unsigned int y_num_bins,
            const float y_min,
            const float y_max
        );

        // members:
        unsigned int nbinsx; 
        float xmin; 
        float xmax;
        float xwidth;
        unsigned int nbinsy; 
        float ymin; 
        float ymax;
        float ywidth;
    };

    // non-member methods:

    // make SignalBinInfo using bin width
    SignalBinInfo MakeSignalBinInfo
    (
        const float x_bin_width,
        const float x_min,
        const float x_max,
        const float y_bin_width,
        const float y_min,
        const float y_max
    );

    // return the binning info for a specific signal sample 
    SignalBinInfo GetSignalBinInfo(const at::Sample::value_type sample);

} // namespace ss

#endif // SS_SIGNALBININFO_H
