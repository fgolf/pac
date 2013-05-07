// c++
#include <iostream>
#include <string>

// ROOT
#include "TChain.h"
#include "rt/MiscTools.h"

// BOOST
#include <boost/program_options.hpp>

using namespace std;

// merged a TChain
void MergedTChain(const std::string& input_path, const std::string& merged_file, const std::string& tree_name, const std::string& option)
{
    cout << Form("merging %s to %s", input_path.c_str(), merged_file.c_str()) << endl;
    rt::mkdir(rt::dirname(merged_file), /*force=*/true);
    TTree::SetMaxTreeSize(5368709120); // 5GB
    TChain* chain = rt::CreateTChainFromCommaSeperatedList(input_path, tree_name);
    chain->Merge(merged_file.c_str(), option.c_str());
    cout << "complete." << endl; 
    delete chain;
}

int main(int argc, char* argv[])
{
    // inputs
    // -------------------------------------------------------------------------------------------------//

    std::string input_file  = "";
    std::string output_file = "";
    std::string tree_name   = "";
    std::string option      = "fast";

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"   , "print this menu")
        ("input" , po::value<std::string>(&input_file) , "name of input file" )
        ("output", po::value<std::string>(&output_file), "name of output file")
        ("tree"  , po::value<std::string>(&tree_name)  , "tree name"          )
        ("option", po::value<std::string>(&option)     , "options"            )
        ;

    po::variables_map vm;
    try
    {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    }
    catch(const std::exception& e)
    {
        cerr << e.what() << "\nexiting" << endl;
        return 1;
    }

    if (vm.count("help")) {
        cout << desc << "\n";
        return 1;
    }

    // do the merging 
    MergedTChain(input_file, output_file, tree_name, option);
    return 0;
}
