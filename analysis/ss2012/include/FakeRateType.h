#ifndef SS_FAKERATETYPE_H
#define SS_FAKERATETYPE_H

#include <string>
#include <vector>

class TTree;

namespace ss
{
    struct FakeRateType
    {
        enum value_type
        {
            hpt,
            eth,
            truncated,
            static_size
        };
    };

    // Fake Rate Type Infomation
    struct FakeRateTypeInfo
    {
        std::string name;
        std::string title;
        std::string latex;
    };

    struct FakeRateBinInfo
    {
        std::vector<float> vel_vtx_bins;
        std::vector<float> vel_eta_bins;
        std::vector<float> vel_pt_bins;
        std::vector<float> vmu_vtx_bins;
        std::vector<float> vmu_eta_bins;
        std::vector<float> vmu_pt_bins;

        size_t num_el_vtx_bins() {return vel_vtx_bins.size()-1;}
        size_t num_el_eta_bins() {return vel_eta_bins.size()-1;}
        size_t num_el_pt_bins () {return vel_pt_bins.size() -1;}
        size_t num_mu_vtx_bins() {return vmu_vtx_bins.size()-1;}
        size_t num_mu_eta_bins() {return vmu_eta_bins.size()-1;}
        size_t num_mu_pt_bins () {return vmu_pt_bins.size() -1;}

        float* el_vtx_bins() {return &vel_vtx_bins[0];}
        float* el_eta_bins() {return &vel_eta_bins[0];}
        float* el_pt_bins()  {return &vel_pt_bins[0] ;}
        float* mu_vtx_bins() {return &vmu_vtx_bins[0];}
        float* mu_eta_bins() {return &vmu_eta_bins[0];}
        float* mu_pt_bins()  {return &vmu_pt_bins[0] ;}
    };

    // Get the FakeRateType from a string
    FakeRateType::value_type GetFakeRateTypeFromName(const std::string& analysis_type_name);

    // Get the info for the Signal region
    FakeRateTypeInfo GetFakeRateTypeInfo(const FakeRateType::value_type& analysis_type);
    FakeRateTypeInfo GetFakeRateTypeInfo(const std::string& analysis_type_name);

    // get the fake rate binning
    FakeRateBinInfo GetFakeRateBinInfo(bool use_eth_binning);

} // namespace ss

#endif // SS_FAKERATETYPE_H
