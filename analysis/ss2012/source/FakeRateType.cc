#include "FakeRateType.h"
#include "SSB2012.h"
#include "TTree.h"
#include <stdexcept>
#include <tr1/array>

ss::FakeRateTypeInfo s_FakeRateTypeInfos[] = 
{
    // inclusive
    {
        // name
        "hpt", 
        // ROOT title
        "high p_{T}",
        // latex title
        "high $p_{T}$"
    },
    {
        // name
        "eth", 
        // ROOT title
        "ETH",
        // latex title
        "ETH"
    },
    {
        // name
        "truncated", 
        // ROOT title
        "truncated",
        // latex title
        "truncated"
    },
};

// check that the FakeRateTypeInfoArray is the same size as the enum
// fails at compile time if it does
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
#define STATIC_ASSERT(expr) typedef char my_static_assert[(expr) ? 1 : -1]
STATIC_ASSERT(ARRAY_SIZE(s_FakeRateTypeInfos) == ss::FakeRateType::static_size);

namespace ss
{
    // wrapper function to get the FakeRateTypeInfo
    FakeRateType::value_type GetFakeRateTypeFromName(const std::string& analysis_type_name)
    {
        using namespace std;
        FakeRateType::value_type analysis_type = FakeRateType::static_size;
        for (size_t i = 0; i != FakeRateType::static_size; i++)
        {
            if (string(s_FakeRateTypeInfos[i].name) == analysis_type_name)
            {
                analysis_type = static_cast<FakeRateType::value_type>(i);
                break;
            }
        }

        // throw if not found
        if (analysis_type == FakeRateType::static_size)
        {
            throw std::domain_error("ERROR: at::GetFakeRateTypeInfo(std::string): analysis_type not found!");
        }

        return analysis_type; 
    }

    // wrapper function to get the FakeRateTypeInfo
    FakeRateTypeInfo GetFakeRateTypeInfo(const FakeRateType::value_type& analysis_type)
    {
        return s_FakeRateTypeInfos[analysis_type]; 
    }

    FakeRateTypeInfo GetFakeRateTypeInfo(const std::string& analysis_type_name)
    {
        FakeRateType::value_type analysis_type = GetFakeRateTypeFromName(analysis_type_name); 
        return GetFakeRateTypeInfo(analysis_type); 
    }

    FakeRateTypeInfo GetFakeRateTypeInfo(unsigned int analysis_type_number)
    {
        FakeRateType::value_type analysis_type = static_cast<FakeRateType::value_type>(analysis_type_number); 
        return GetFakeRateTypeInfo(analysis_type); 
    }

    at::FakeRateBinInfo GetFakeRateBinInfo(bool use_eth_binning)
    {
        at::FakeRateBinInfo fr_bin_info;
        if (use_eth_binning)
        {
            const float tmp_mu_vtx_bins[] = {5.0, 7.0, 9.0, 11.0, 13.0, 15.0, 17.0, 19.0, 21.0, 23.0, 25.0};
            const float tmp_mu_eta_bins[] = {0.0, 0.5, 1.0, 1.5, 2.0, 2.5};
            const float tmp_mu_pt_bins[]  = {20.0, 25.0, 30.0, 35.0, 40.0, 50.0, 60.0};

            const float tmp_el_vtx_bins[] = {5.0, 7.0, 9.0, 11.0, 13.0, 15.0, 17.0, 19.0, 21.0, 23.0, 25.0};
            const float tmp_el_eta_bins[] = {0.0, 0.5, 1.0, 1.5, 2.0, 2.5};
            const float tmp_el_pt_bins[]  = {20.0, 25.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 100.0};

            size_t tmp_num_el_vtx_bins = (sizeof(tmp_el_vtx_bins) / sizeof(tmp_el_vtx_bins[0]));
            size_t tmp_num_el_eta_bins = (sizeof(tmp_el_eta_bins) / sizeof(tmp_el_eta_bins[0]));
            size_t tmp_num_el_pt_bins  = (sizeof(tmp_el_pt_bins)  / sizeof(tmp_el_pt_bins[0]) );

            size_t tmp_num_mu_vtx_bins = (sizeof(tmp_mu_vtx_bins) / sizeof(tmp_mu_vtx_bins[0]));
            size_t tmp_num_mu_eta_bins = (sizeof(tmp_mu_eta_bins) / sizeof(tmp_mu_eta_bins[0]));
            size_t tmp_num_mu_pt_bins  = (sizeof(tmp_mu_pt_bins)  / sizeof(tmp_mu_pt_bins[0]) );

            fr_bin_info.vel_vtx_bins.assign(tmp_el_vtx_bins, tmp_el_vtx_bins+tmp_num_el_vtx_bins);
            fr_bin_info.vel_eta_bins.assign(tmp_el_eta_bins, tmp_el_eta_bins+tmp_num_el_eta_bins);
            fr_bin_info.vel_pt_bins .assign(tmp_el_pt_bins , tmp_el_pt_bins +tmp_num_el_pt_bins );

            fr_bin_info.vmu_vtx_bins.assign(tmp_mu_vtx_bins, tmp_mu_vtx_bins+tmp_num_mu_vtx_bins);
            fr_bin_info.vmu_eta_bins.assign(tmp_mu_eta_bins, tmp_mu_eta_bins+tmp_num_mu_eta_bins);
            fr_bin_info.vmu_pt_bins .assign(tmp_mu_pt_bins , tmp_mu_pt_bins +tmp_num_mu_pt_bins );
        }
        else
        {
            const float tmp_el_vtx_bins[] = {0.0,  3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0, 30.0};
            const float tmp_el_eta_bins[] = {0.0, 1.0, 1.479, 2.0, 2.5};
	    const float tmp_el_pt_bins[]  = {10.0, 15.0, 20.0, 25.0, 35.0, 55.0};
	    //            const float tmp_el_pt_bins[]  = {10.0, 15.0, 20.0, 22.0, 25.0, 30.0, 35.0, 55.0};

            const float tmp_mu_vtx_bins[] = {0.0,  3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0, 30.0};
            const float tmp_mu_eta_bins[] = {0.0, 1.0, 1.479, 2.0, 2.5};
	    //	    const float tmp_mu_pt_bins[]  = {5.0, 10.0, 15.0, 20.0, 25.0, 35.0, 60.0};
	    const float tmp_mu_pt_bins[]  = {5.0, 10.0, 15.0, 20.0, 22.0, 25.0, 30.0, 35.0, 60.0};

            size_t tmp_num_el_vtx_bins = (sizeof(tmp_el_vtx_bins) / sizeof(tmp_el_vtx_bins[0]));
            size_t tmp_num_el_eta_bins = (sizeof(tmp_el_eta_bins) / sizeof(tmp_el_eta_bins[0]));
            size_t tmp_num_el_pt_bins  = (sizeof(tmp_el_pt_bins)  / sizeof(tmp_el_pt_bins[0]) );

            size_t tmp_num_mu_vtx_bins = (sizeof(tmp_mu_vtx_bins) / sizeof(tmp_mu_vtx_bins[0]));
            size_t tmp_num_mu_eta_bins = (sizeof(tmp_mu_eta_bins) / sizeof(tmp_mu_eta_bins[0]));
            size_t tmp_num_mu_pt_bins  = (sizeof(tmp_mu_pt_bins)  / sizeof(tmp_mu_pt_bins[0]) );

            fr_bin_info.vel_vtx_bins.assign(tmp_el_vtx_bins, tmp_el_vtx_bins+tmp_num_el_vtx_bins);
            fr_bin_info.vel_eta_bins.assign(tmp_el_eta_bins, tmp_el_eta_bins+tmp_num_el_eta_bins);
            fr_bin_info.vel_pt_bins .assign(tmp_el_pt_bins , tmp_el_pt_bins +tmp_num_el_pt_bins );

            fr_bin_info.vmu_vtx_bins.assign(tmp_mu_vtx_bins, tmp_mu_vtx_bins+tmp_num_mu_vtx_bins);
            fr_bin_info.vmu_eta_bins.assign(tmp_mu_eta_bins, tmp_mu_eta_bins+tmp_num_mu_eta_bins);
            fr_bin_info.vmu_pt_bins .assign(tmp_mu_pt_bins , tmp_mu_pt_bins +tmp_num_mu_pt_bins );
        }

        return fr_bin_info;
    }

} // namespace ss
