#include "at/YieldType.h"

namespace at
{
    // get the yield type
    //  0 : base
    // > 1: up
    // < 1: down
    YieldType::value_type GetYieldType(int type)
    {
        if      (type > 0) {return YieldType::up;  }
        else if (type < 0) {return YieldType::down;}
        else               {return YieldType::base;}
    }

    std::string GetYieldTypeName(const YieldType::value_type type)
    {
        switch (type)
        {
            case YieldType::up:   {return "up"  ; break;}
            case YieldType::down: {return "down"; break;}
            case YieldType::base: {return "base"; break;}
            default:              {return "base"; break;}
        }
    }
}
