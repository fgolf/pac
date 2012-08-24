#include "at/DileptonHypType.h"
#include <stdexcept> 

namespace at {

    DileptonHypType::value_type hyp_typeToHypType (int hyp_type)
    {
        switch (hyp_type) {
        case 0:
            return DileptonHypType::DILEPTON_MUMU;
        case 1: case 2:
            return DileptonHypType::DILEPTON_EMU;
        case 3:
            return DileptonHypType::DILEPTON_EE;
        default:
            throw std::domain_error("ERROR: at::hyp_typeToHypTeyp: hyp_type out of bounds -- must be less than 4.");
        }

        return DileptonHypType::DILEPTON_ALL;
    }

}
