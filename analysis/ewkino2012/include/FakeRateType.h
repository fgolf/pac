#ifndef EWKINO_FAKERATETYPE_H
#define EWKINO_FAKERATETYPE_H

#include <string>
#include <vector>
#include "at/FakeRateBinInfo.h"

class TTree;

namespace ewkino
{
    struct FakeRateType
    {
        enum value_type
        {
            ss,
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

    // Get the FakeRateType from a string
    FakeRateType::value_type GetFakeRateTypeFromName(const std::string& analysis_type_name);

    // Get the info for the Signal region
    FakeRateTypeInfo GetFakeRateTypeInfo(const FakeRateType::value_type& analysis_type);
    FakeRateTypeInfo GetFakeRateTypeInfo(const std::string& analysis_type_name);

    // get the fake rate binning
    at::FakeRateBinInfo GetFakeRateBinInfo(bool use_eth_binning);

} // namespace ewkino

#endif // EWKINO_FAKERATETYPE_H
