#include "TTbarBreakDown.h"
#include "CMS2.h"

using namespace tas;
using namespace at;

TTbarBreakDown::value_type GetTTbarBreakDown(at::Sample::value_type sample, int lep1_is_fromw, int lep2_is_fromw)
{
    // not ttjets
    if (sample != Sample::ttjets && sample != Sample::ttdil && sample != Sample::ttslb && sample != Sample::ttslo && sample != Sample::ttotr)
    {
        return TTbarBreakDown::static_size;
    }

    // TTbar --> ll X
    if (lep1_is_fromw > 0 && lep2_is_fromw > 0)
    {
        return TTbarBreakDown::TTDIL;
    }

    // TTbar --> other
    if (lep1_is_fromw < 1 && lep2_is_fromw < 1)
    {
        return TTbarBreakDown::TTOTR;
    }

    // TTbar --> l + (b --> l) X
    if (lep1_is_fromw > 0 && (lep2_is_fromw == -1 || lep2_is_fromw == -2))
    {
        return TTbarBreakDown::TTSLB;
    }
    if (lep2_is_fromw > 0 && (lep1_is_fromw == -1 || lep1_is_fromw == -2))
    {
        return TTbarBreakDown::TTSLB;
    }

    // TTbar --> l + (not b --> l) X
    if (lep1_is_fromw > 0 && (lep2_is_fromw == 0 || lep2_is_fromw == -3))
    {
        return TTbarBreakDown::TTSLO;
    }
    if (lep2_is_fromw > 0 && (lep1_is_fromw == 0 || lep1_is_fromw == -3))
    {
        return TTbarBreakDown::TTSLO;
    }

    return TTbarBreakDown::static_size;
}
