#include "at/DileptonChargeType.h"
#include <stdexcept> 

namespace at 
{
    std::string GetDileptonChargeTypeName(const DileptonChargeType::value_type& charge_type)
    {
        switch (charge_type) 
        {
            case DileptonChargeType::SS: return "ss";
            case DileptonChargeType::SF: return "sf";
            case DileptonChargeType::DF: return "df";
            case DileptonChargeType::OS: return "os";
            default:
                throw std::domain_error("ERROR: at::GetDileptonChargeName: charge_type out of bounds");
        };
    }

    std::string GetDileptonChargeTypeTitle(const DileptonChargeType::value_type& charge_type)
    {
        switch (charge_type) 
        {
            case DileptonChargeType::SS: return "SS";
            case DileptonChargeType::SF: return "SF";
            case DileptonChargeType::DF: return "DF";
            case DileptonChargeType::OS: return "OS";
            default:
                throw std::domain_error("ERROR: at::GetDileptonChargeTitle: charge_type out of bounds");
        };
    }
    
    std::string GetDileptonChargeTypeLatex(const DileptonChargeType::value_type& charge_type)
    {
        switch (charge_type) 
        {
            case DileptonChargeType::SS: return "SS";
            case DileptonChargeType::SF: return "SF";
            case DileptonChargeType::DF: return "DF";
            case DileptonChargeType::OS: return "OS";
            default:
                throw std::domain_error("ERROR: at::GetDileptonChargeTitle: charge_type out of bounds");
        };
    }
}

