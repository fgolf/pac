#ifndef SYSTEMATICTYPE_H
#define SYSTEMATICTYPE_H

#include <string>

namespace ss
{
    struct SystematicType
    {
        enum value_type
        {
            None,    // don't scale  
            JES_UP,  // Jet Energy Scale +/-
            JES_DN,  // Jet Energy Scale +/-
            JER,     // Jet Energy Resolution
            MET_UP,  // unclustered MET +/-
            MET_DN,  // unclustered MET +/-
            BEFF_UP, // B-tagged efficiency +/-
            BEFF_DN, // B-tagged efficiency +/-
            static_size
        };
    };

    // Get the SystematicType from a string
    SystematicType::value_type GetSystematicTypeFromName(const std::string& syst_type_name);

    // function to return the appropriate related met, ht, # jets, and # btags based on the 
    // systematic flag
    void GetReweightedKinematicVariables
    (
        float& met,
        float& ht,
        int& njets,
        int& nbtags,
        const bool do_beff_sf = true,
        const SystematicType::value_type syst_type = SystematicType::None
    );

} // namespace ss


#endif // SYSTEMATICTYPE_H
