#ifndef AT_YIELDTYPE_H
#define AT_YIELDTYPE_H

#include <string>

namespace at
{
    struct YieldType
    {
        enum value_type
        {
            up,
            base,
            down,
            static_size
        };
    };

    // get the yield type
    //  0 : base
    // > 1: up
    // < 1: down
    YieldType::value_type GetYieldType(int type);

    // return the name of the yield type
    std::string GetYieldTypeName(const YieldType::value_type type);

} // namespace at

#endif // AT_YIELDTYPE_H
