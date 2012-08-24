#include <string>

namespace rt
{
    // merged a TChain
    void MergedTChain(const std::string& input_path, const std::string& merged_file = "merged.root", const std::string& tree_name = "tree", const std::string& option = "fast");

} // namespace rt
