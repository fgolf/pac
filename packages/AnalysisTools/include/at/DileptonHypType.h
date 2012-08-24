// -*- C++ -*-
#ifndef DILEPTONHYPTYPE_H
#define DILEPTONHYPTYPE_H

namespace at {
    
    struct HypType {
        enum value_type {
            DILEPTON_SS,
            DILEPTON_OS,
            static_size
        };
    };

    struct DileptonHypType {
        enum value_type {
            DILEPTON_ALL,
            DILEPTON_MUMU,
            DILEPTON_EMU,
            DILEPTON_EE,
            static_size
        };
    };

    static const char dilepton_hypo_names[][128] = { "all", "mm", "em", "ee" };

    DileptonHypType::value_type hyp_typeToHypType (int hyp_type);

};

#endif
