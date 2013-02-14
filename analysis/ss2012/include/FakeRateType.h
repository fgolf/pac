#ifndef SS_FAKERATETYPE_H
#define SS_FAKERATETYPE_H

#include <string>

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
        float el_vtx_bins[];
        unsigned int num_el_vtx_bins;

        float el_eta_bins[];
        unsigned int num_el_eta_bins;

        float el_pt_bins[];
        unsigned int num_el_pt_bins;

        float mu_vtx_bins[];
        unsigned int num_mu_vtx_bins;

        float mu_eta_bins[];
        unsigned int num_mu_eta_bins;

        float mu_pt_bins[];
        unsigned int num_mu_pt_bins;
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
