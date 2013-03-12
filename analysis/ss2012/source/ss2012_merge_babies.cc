#include <iostream>
#include <string>
#include "TChain.h"
#include "SSB2012Wrapper.h"
#include "at/SkimChain.h"
#include "rt/RootTools.h"
#include "AnalysisType.h"
#include <boost/program_options.hpp>

// trivial no skim function
bool keep_all_events(long)
{
    return true;
}

// simple # jets selection
struct simple_skim
{
    simple_skim(int njets, ss::AnalysisType::value_type anal_type) : m_njets(njets), m_at(anal_type) {}
    bool operator() (long) const 
    {
        using namespace ssb;
        using namespace ss;

        // lepton pT cut values
        float mu_min_pt = 0.0;
        float el_min_pt = 0.0;
        switch(m_at)
        {
            case AnalysisType::high_pt:
                mu_min_pt = 20.0;
                el_min_pt = 20.0;
                break;
            case AnalysisType::high_pt_eth:
                mu_min_pt = 20.0;
                el_min_pt = 20.0;
                break;
            case AnalysisType::hcp:
                mu_min_pt = 20.0;
                el_min_pt = 20.0;
                break;
            case AnalysisType::low_pt:
                mu_min_pt = 10.0;
                el_min_pt = 10.0;
                break;
            case AnalysisType::vlow_pt:
                mu_min_pt = 5.0;
                el_min_pt = 10.0;
                break;
            case AnalysisType::higgsino:
                mu_min_pt = 10.0;
                el_min_pt = 10.0;
                break;
            default:
                mu_min_pt = 20.0;
                el_min_pt = 20.0;
                break;
        }
        if (lep1_p4().pt() < (abs(lep1_pdgid()==11) ? el_min_pt : mu_min_pt))
        {
            return false;
        }
        if (lep2_p4().pt() < (abs(lep2_pdgid()==11) ? el_min_pt : mu_min_pt))
        {
            return false;
        }

        if (is_real_data())
        {
            const bool result = (dilep_type() < 4 && (is_ss() || is_os() || is_sf() || is_df()) && njets() >= m_njets);
            return result;
        }
        else
        {
            //bool result = (dilep_type() < 4 && (is_ss() || is_os() || is_sf() || is_df()) && njets() >= m_njets);
            const bool result = (dilep_type() < 4 && (is_ss() || is_sf() || is_df()) && njets() >= m_njets);
            return result;
        }
    }
    int m_njets;
    ss::AnalysisType::value_type m_at;
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
    std::string anal_type     = "vlow_pt";
    int number_of_events      = -1;
    bool verbose              = false;
    bool do_duplicate_removal = true;
    int njets                 = 0;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"     , "print this menu")
        ("input"    , po::value<std::string>(&input_file)->required(), "REQUIRED: name of input root(s) file (can be cvs)"    )
        ("anal_type", po::value<std::string>(&anal_type)->required() , "REQUIRED: name of analysis type"                      )
        ("output"   , po::value<std::string>(&output_file)           , "name of output root file (default is merged.root)"    )
        ("run_list" , po::value<std::string>(&run_list)              , "good run list (default is empty)"                     )
        ("nev"      , po::value<int>(&number_of_events)              , "number of events"                                     )
        ("njets"    , po::value<int>(&njets)                         , "number of jets to cun on while merging (default is 0)")
        ("duplicate", po::value<bool>(&do_duplicate_removal)         , "remove duplicate events"                              )
        ("verbose"  , po::value<bool>(&verbose)                      , "verbosity"                                            )
        ;

    // parse it
    try
    {
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) 
        {
            cout << desc << "\n";
            return 1;
        }

        po::notify(vm);
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << "\nexiting" << endl;
        cout << desc << "\n";
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown error!" << "\n";
        return false;
    }

    // check that input file exists and is specified (hmm, doesn't work for a csv)
    //if (rt::ls(input_file).empty())
    //{
    //    cout << "[ss2012_merge_baby] Error: input file " << input_file << " not found" << endl;
    //    cout << desc << "\n";
    //    return 1;
    //}

    // if the run list is specified, check that it exists 
    if (!run_list.empty())
    { 
        if (!rt::exists(run_list))
        {
            cout << "[ss2012_merge_baby] Error: run_list " << run_list << " not found" << endl;
            cout << desc << "\n";
            return 1;
        }
    }

    // print the input
    cout << "input_file           : \t" << input_file          << endl;
    cout << "anal_type            : \t" << anal_type           << endl;
    cout << "output_file          : \t" << output_file         << endl;
    cout << "run_list             : \t" << run_list            << endl;
    cout << "number_of_events     : \t" << number_of_events    << endl;
    cout << "njets                : \t" << njets               << endl;
    cout << "do_duplicate_removal : \t" << do_duplicate_removal<< endl;
    cout << "verbose              : \t" << verbose             << endl;

    // do it 
    // -------------------------------------------------------------------------------------------------//

    // merge the tree
    TChain* chain = rt::CreateTChainFromCommaSeperatedList(input_file, "tree");
    //chain->SetDirectory(0);

    // analysis type
    ss::AnalysisType::value_type analysis_type = ss::GetAnalysisTypeFromName(anal_type);

    // make the directory for the output file
    rt::mkdir(rt::dirname(output_file), /*force=*/true);

    // run the skim and do not cut events except for duplicates and bad runs
    at::SkimChain<SSB2012>
    (
        chain,
        output_file,
        simple_skim(njets, analysis_type),
        //keep_all_events,
        samesignbtag,
        number_of_events,
        run_list,
        do_duplicate_removal,
        verbose
    );

    // cleanup
    delete chain;

    // done 
    return 0;
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
