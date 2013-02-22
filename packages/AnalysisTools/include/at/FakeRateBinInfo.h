#ifndef AT_FAKERATEBININFO_H
#define AT_FAKERATEBININFO_H

#include <vector>

namespace at
{
    struct FakeRateBinInfo
    {
        // methods:
        std::size_t num_el_vtx_bins() {return vel_vtx_bins.size()-1;}
        std::size_t num_el_eta_bins() {return vel_eta_bins.size()-1;}
        std::size_t num_el_pt_bins () {return vel_pt_bins.size() -1;}
        std::size_t num_mu_vtx_bins() {return vmu_vtx_bins.size()-1;}
        std::size_t num_mu_eta_bins() {return vmu_eta_bins.size()-1;}
        std::size_t num_mu_pt_bins () {return vmu_pt_bins.size() -1;}

        const float* const el_vtx_bins() {return &vel_vtx_bins[0];}
        const float* const el_eta_bins() {return &vel_eta_bins[0];}
        const float* const el_pt_bins()  {return &vel_pt_bins [0];}
        const float* const mu_vtx_bins() {return &vmu_vtx_bins[0];}
        const float* const mu_eta_bins() {return &vmu_eta_bins[0];}
        const float* const mu_pt_bins()  {return &vmu_pt_bins [0];}

        // members:
        std::vector<float> vel_vtx_bins;
        std::vector<float> vel_eta_bins;
        std::vector<float> vel_pt_bins;
        std::vector<float> vmu_vtx_bins;
        std::vector<float> vmu_eta_bins;
        std::vector<float> vmu_pt_bins;

    };

} // namespace at

#endif // AT_FAKERATEBININFO_H
