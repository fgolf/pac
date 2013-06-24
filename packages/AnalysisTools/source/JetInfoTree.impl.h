#include "at/ConvertHypIndexToVectors.h"
//#include "CMS2.h"

// templated function implementation for JetInfoTree 

template <typename Function>
void JetInfoTree::FillCommon
(
    const at::JetBaseSelectionArgs& jet_args,
    Function jet_selection
)
{
//     using namespace tas;

    // fill vectors
    vjets_p4  = at::GetJets       (jet_args, jet_selection);
    njets     = at::NumJets       (jet_args, jet_selection);
    vbjets_p4 = at::GetBtaggedJets(jet_args, jet_selection);
    nbtags    = at::NumBtaggedJets(jet_args, jet_selection);
}
