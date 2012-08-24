#ifndef DILEPTONHYPTYPE_H
#define DILEPTONHYPTYPE_H

#include <string>

namespace at 
{
    // flavor
    struct DileptonHypType
    {
        enum value_type
        {
            ALL,
            MUMU,
            EMU,
            EE,
            static_size
        };
    };

    // return the name of the name the DileptonHypType
    std::string GetDileptonHypTypeName(const DileptonHypType::value_type& hyp_type);

    // return the title for ROOT of the name the DileptonHypType
    std::string GetDileptonHypTypeTitle(const DileptonHypType::value_type& hyp_type);

    // return the title for latex of the name the DileptonHypType
    std::string GetDileptonHypTypeLatex(const DileptonHypType::value_type& hyp_type);

    // convert the int to a DileptonHypType
    DileptonHypType::value_type hyp_typeToHypType(int hyp_type);
};

#endif // DILEPTONHYPTYPE_H
