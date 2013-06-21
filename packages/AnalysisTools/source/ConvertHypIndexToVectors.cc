#include "at/ConvertHypIndexToVectors.h"
#include "CMS2.h"

namespace at
{
    // function to convert a hyp index into a vector of mu/el indices
    // NOTE: clears any contents on the reference vector arguments
    void ConvertHypIndexToVectors(const int hyp_index, std::vector<int>& mu_indices, std::vector<int>& el_indices)
    {
        mu_indices.clear();
        el_indices.clear();

        // empty vectors if the hyp index is invalid
        if (hyp_index < 0)
        {
            return;
        }

        // ll
        if (abs(tas::hyp_ll_id().at(hyp_index))==11)
        {
            el_indices.push_back(tas::hyp_ll_index().at(hyp_index));
        }
        else
        {
            mu_indices.push_back(tas::hyp_ll_index().at(hyp_index));
        }

        // lt
        if (abs(tas::hyp_lt_id().at(hyp_index))==11)
        {
            el_indices.push_back(tas::hyp_lt_index().at(hyp_index));
        }
        else
        {
            mu_indices.push_back(tas::hyp_lt_index().at(hyp_index));
        }

        // done
        return;
    }

} // namespace
