#include <iostream>
#include <string>
#include "TChain.h"
#include "SSB2012Wrapper.h"
#include "at/SkimChain.h"
#include "rt/RootTools.h"
#include <boost/program_options.hpp>

// trivial no skim function
bool keep_all_events(long)
{
    return true;
}

// simple # jets selection
struct simple_selection
{
	simple_selection(unsigned int njets = 0) : m_njets(njets) {}
	bool operator() (long) const {return static_cast<unsigned int>(ssb::njets()) >= m_njets;}
	unsigned int m_njets;
};

int main(int argc, char* argv[])
try
{
    using namespace std;

    // inputs
    // -------------------------------------------------------------------------------------------------//

    std::string input_file    = "";
    std::string output_file   = "merged.root";
    std::string run_list      = "";
    int number_of_events      = -1;
    bool verbose              = false;
    bool do_duplicate_removal = true;
	unsigned int njets        = 0;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"     , "print this menu")
        ("output"   , po::value<std::string>(&output_file)  , "name of output root file (default is merged.root)"    )
        ("input"    , po::value<std::string>(&input_file)   , "name of input root(s) file (can be cvs)"              )
        ("run_list" , po::value<std::string>(&run_list)     , "good run list (default is empty)"                     )
        ("nev"      , po::value<int>(&number_of_events)     , "number of events"                                     )
        ("njets"    , po::value<unsigned int>(&njets)       , "number of jets to cun on while merging (default is 0)")
        ("duplicate", po::value<bool>(&do_duplicate_removal), "remove duplicate events"                              )
        ("verbose"  , po::value<bool>(&verbose)             , "verbosity"                                            )
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

    // check that input file exists and is specified
    if (!input_file.empty())
    { 
        //if (!rt::exists(input_file))
        //{
        //    cout << "ERROR: ss2012_skim: input file " << input_file << " not found" << endl;
        //    cout << desc << "\n";
        //    return 1;
        //}
    }
    else
    {
        cout << "ERROR: ss2012_skim: input file " << input_file << " not specified." << endl;
        cout << desc << "\n";
        return 1;
    }

    // if the run list is specified, check that it exists 
    if (!run_list.empty())
    { 
        if (!rt::exists(run_list))
        {
            cout << "ERROR: ss2012_skim: run_list " << run_list << " not found" << endl;
            cout << desc << "\n";
            return 1;
        }
    }

    // print the input
    if (verbose)
    {
        cout << "input files = "  << input_file  << endl;
        cout << "output files = " << output_file << endl;
        cout << "run_list = "     << run_list    << endl;
    }
    
    // do the main analysis
    // -------------------------------------------------------------------------------------------------//

    // make the directory for the output file

    // merge the tree
    TChain* chain = rt::CreateTChainFromCommaSeperatedList(input_file, "tree");
    //chain->SetDirectory(0);

    // run the skim and do not cut events except for duplicates and bad runs
    rt::mkdir(rt::dirname(output_file), /*force=*/true);
    
    at::SkimChain<SSB2012>
    (
        chain,
        output_file,
        simple_selection(njets),
        samesignbtag,
        number_of_events,
        run_list,
        do_duplicate_removal,
        verbose
    );

    // cleanup
    //delete chain;
    
    // done 
    return 0;
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
