#ifndef AT_FLIPRATEBININFO_H
#define AT_FLIPRATEBININFO_H

#include <vector>

namespace at
{
    struct FlipRateBinInfo
    {
        // methods:
        std::size_t num_eta_bins() {return v_eta_bins.size()-1;}
        std::size_t num_pt_bins () {return v_pt_bins.size() -1;}

        const float* const eta_bins() {return &v_eta_bins[0];}
        const float* const pt_bins()  {return &v_pt_bins[0] ;}

        // members:
        std::vector<float> v_eta_bins;
        std::vector<float> v_pt_bins;
    };

} // namespace at

#endif // AT_FLIPRATEBININFO_H

