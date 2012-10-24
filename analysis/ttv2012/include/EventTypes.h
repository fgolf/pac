#ifndef TTV2012_EVENTTYPES_H
#define TTV2012_EVENTTYPES_H

namespace ttv2012
{
    struct EventType
    {
        enum value_type
        {
            TRILEPTONZ,
            TRILEPTONZ_SF,
            TRILEPTONZ_DF,
            TRILEPTONZ_TF,
            static_size
        };
    };
}

#endif
