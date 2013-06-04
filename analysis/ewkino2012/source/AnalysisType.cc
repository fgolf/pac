#include "AnalysisType.h"
#include "EWKINO2012_SS.h"
#include "TTree.h"
#include <stdexcept>

ewkino::AnalysisTypeInfo s_AnalysisTypeInfos[] = 
{
    // inclusive
    {
        // name
        "ss", 
        // short name
        "ss", 
        // ROOT title
        "ss",
        // latex title
        "ss"
    },
};

// check that the AnalysisTypeInfoArray is the same size as the enum
// fails at compile time if it does
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
#define STATIC_ASSERT(expr) typedef char my_static_assert[(expr) ? 1 : -1]
STATIC_ASSERT(ARRAY_SIZE(s_AnalysisTypeInfos) == ewkino::AnalysisType::static_size);

namespace ewkino
{
    // wrapper function to get the AnalysisTypeInfo
    AnalysisType::value_type GetAnalysisTypeFromName(const std::string& analysis_type_name)
    {
        using namespace std;
        AnalysisType::value_type analysis_type = AnalysisType::static_size;
        for (size_t i = 0; i != AnalysisType::static_size; i++)
        {
            if (string(s_AnalysisTypeInfos[i].name) == analysis_type_name)
            {
                analysis_type = static_cast<AnalysisType::value_type>(i);
                break;
            }
        }

        // throw if not found
        if (analysis_type == AnalysisType::static_size)
        {
            throw std::domain_error("ERROR: at::GetAnalysisTypeInfo(std::string): analysis_type not found!");
        }

        return analysis_type; 
    }

    // wrapper function to get the AnalysisTypeInfo
    AnalysisTypeInfo GetAnalysisTypeInfo(const AnalysisType::value_type& analysis_type)
    {
        return s_AnalysisTypeInfos[analysis_type]; 
    }

    AnalysisTypeInfo GetAnalysisTypeInfo(const std::string& analysis_type_name)
    {
        AnalysisType::value_type analysis_type = GetAnalysisTypeFromName(analysis_type_name); 
        return GetAnalysisTypeInfo(analysis_type); 
    }

    AnalysisTypeInfo GetAnalysisTypeInfo(unsigned int analysis_type_number)
    {
        AnalysisType::value_type analysis_type = static_cast<AnalysisType::value_type>(analysis_type_number); 
        return GetAnalysisTypeInfo(analysis_type); 
    }

    // aliases for TTree
    void SetAnalysisTypeAliases(TTree& tree)
    {
        tree.SetAlias("trig_mm_hpt", "trig_mm");
        tree.SetAlias("trig_em_hpt", "trig_em");
        tree.SetAlias("trig_ee_hpt", "trig_ee");
    }

} // namespace ewkino
