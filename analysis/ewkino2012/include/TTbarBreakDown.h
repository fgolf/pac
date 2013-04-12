#ifndef TTBARBREAKDOWN_H
#define TTBARBREAKDOWN_H

#include "at/Sample.h"

struct TTbarBreakDown
{
    enum value_type
    {
        TTDIL, // TTbar --> ll X 
        TTSLO, // TTbar --> l + (not b --> l) X
        TTSLB, // TTbar --> l + (b --> l) X
        TTOTR, // TTbar --> other 
        static_size
    };
};

TTbarBreakDown::value_type GetTTbarBreakDown(at::Sample::value_type sample, int lep1_is_fromw, int lep2_is_fromw);

#endif // TTBARBREAKDOWN_H
