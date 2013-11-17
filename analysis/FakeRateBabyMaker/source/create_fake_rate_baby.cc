#include "myBabyMaker.h"
#include "rt/RootTools.h"
#include "TChain.h"
#include <string>
#include <iostream>
#include <boost/program_options.hpp>

int main(int argc, char* argv[])
 try
{
    // set the style
    rt::SetStyle("emruoi");

    using namespace std;

    // inputs
    // -------------------------------------------------------------------------------------------------//

    std::string input_file          = "";
    std::string output_file         = "fake_rate_baby_tree.root";
    std::string jetcorr_path        = rt::getenv("PAC") + "/externals/source/cms2_core/CORE/jetcorr/data";
    std::string good_run_list       = "";
    long number_of_events           = -1;
    short e_or_mu                   = -1;
    bool apply_filter               = false;
    bool verbose                    = false;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"     , "print this menu")
        ("input"    , po::value<std::string>(&input_file)->required() , "name of input ROOT file"                                  )
        ("output"   , po::value<std::string>(&output_file)            , "name of output ROOT file"                                 )
        ("run_list" , po::value<std::string>(&good_run_list)          , "good Run list (no default)"                               )
        ("jetcorr"  , po::value<std::string>(&good_run_list)          , "path to jet correction files (default is \"data\")"       )
        ("nev"      , po::value<long>(&number_of_events)              , "number of events to run on (-1 == all)"                   )
        ("eormu"    , po::value<short>(&e_or_mu)                      , "electron or muon (11 == electron, 13 == muon, -1 == both)")
        ("filter"   , po::value<bool>(&apply_filter)                  , "apply filter (default == false)"                          )
        ("verbose"  , po::value<bool>(&verbose)                       , "verbosity (default == false)"                             )
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

    // check that input file exists and is specified
    if (!input_file.empty())
    { 
        if (rt::ls(input_file).empty())
        {
            cout << "[create_fake_rate_baby] Error : input file " << input_file << " not found" << endl;
            cout << desc << "\n";
            return 1;
        }
    }

    // check e_or_mu is valid 
    if (not (e_or_mu == 11 or e_or_mu == 13 or e_or_mu == -1))
    {
        cout << "[create_fake_rate_baby] Error : eormu value is invalid." << endl;
        cout << desc << "\n";
        return 1;
    }

    // check that the jetcorr path is a valid directory
    if (not rt::exists(jetcorr_path))
    {
        cout << "[create_fake_rate_baby] Error : input file " << jetcorr_path << " not found" << endl;
        return 1;
    }


    // inputs
    cout << "inputs:" << endl;
    cout << "input_file       :\t" << input_file       << endl;
    cout << "output_file      :\t" << output_file      << endl;
    cout << "jetcorr_path     :\t" << jetcorr_path     << endl;
    cout << "good_run_list    :\t" << good_run_list    << endl;
    cout << "number_of_events :\t" << number_of_events << endl;
    cout << "e_or_mu          :\t" << e_or_mu          << endl;
    cout << "apply_filter     :\t" << apply_filter     << endl;
    cout << "verbose          :\t" << verbose          << endl;

    // do the main analysis
    // -------------------------------------------------------------------------------------------------//

    // create the chain
    TChain chain("Events");
    rt::MakeTChain(input_file, chain.GetName(), &chain, verbose);
    rt::PrintFilesFromTChain(chain);

    // run babymaker
    myBabyMaker babymaker;
    babymaker.SetNumEvents(number_of_events);
    babymaker.SetVerbose(verbose);
    if (!good_run_list.empty())
    {
        babymaker.SetGoodRunList(good_run_list.c_str());
    }
    cout << "running fake rate baby maker..." << endl;
    babymaker.ScanChain(&chain, output_file.c_str(), e_or_mu, apply_filter, jetcorr_path.c_str());
    cout << "finished fake rate baby maker..." << endl;

    // done 
    return 0;
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
