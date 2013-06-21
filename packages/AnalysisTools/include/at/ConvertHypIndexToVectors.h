#ifndef CONVERTHYPINDEXTOVECTORS_H
#define CONVERTHYPINDEXTOVECTORS_H

#include <vector>

namespace at
{
    // function to convert a hyp index into a vector of mu/el indices
    // NOTE: clears any contents on the reference vector arguments
    void ConvertHypIndexToVectors(const int hyp_index, std::vector<int>& mu_indices, std::vector<int>& el_indices);

} // namespace at

#endif // CONVERTHYPINDEXTOVECTORS_H
