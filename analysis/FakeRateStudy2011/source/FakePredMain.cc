#include <iostream>
#include <string>
#include "TChain.h"
#include "FakePredScanChain.h"
#include "FakePredLooper.h"
#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>
#include "rt/RootTools.h"

int main(int argc, char* argv[])
try
{
    // set the style
    rt::SetStyle("emruoi");

    using namespace std;

    // inputs
    // -------------------------------------------------------------------------------------------------//

    long number_of_events           = -1;
    std::string input_file          = "";
    std::string output_file         = "plots/pred/pred.root";
    std::string fake_rate_file_name = "plots/data/data40c_pt35.root";
    std::string fake_rate_hist_name = "h_mufr40c";
    std::string suffix              = "";
    std::string vtxreweight_file    = "";
    bool directb                    = false;
    unsigned int num_btags          = 0;
    float lumi                      = 1.0;
    bool verbose                    = false;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"     , "print this menu")
        ("nev"      , po::value<long>(&number_of_events)          , "number of events to run on (-1 == all)"              )
        ("output"   , po::value<std::string>(&output_file)        , "name of output root file"                            )
        ("input"    , po::value<std::string>(&input_file)         , "name of input root file"                             )
        ("fr_file"  , po::value<std::string>(&fake_rate_file_name), "fake rate file name"                                 )
        ("fr_hist"  , po::value<std::string>(&fake_rate_hist_name), "fake rate hist name"                                 )
        ("vtx_file" , po::value<std::string>(&vtxreweight_file)   , "ROOT file for the vertex reweight (ignored for data)")
        ("suffix"   , po::value<std::string>(&suffix)             , "suffix to pring (png, eps, pdf).  empty for none"    )
        ("nbtags"   , po::value<unsigned int>(&num_btags)         , "number of btags to cut on"                           )
        ("directb"  , po::value<bool>(&directb)                   , "require direct b production"                         )
        ("verbose"  , po::value<bool>(&verbose)                   , "verbosity"                                           )
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
        if (!rt::exists(input_file))
        {
            cout << "ERROR: create_fake_pred: input file " << input_file << " not found" << endl;
            cout << desc << "\n";
            return 1;
        }
    }
	else
	{
        cout << "ERROR: create_fake_pred: input file not specified" << endl;
		cout << desc << "\n";
		return 1;
	}

    // check that fake rate file exists and is specified
    if (!fake_rate_file_name.empty())
    { 
        if (!rt::exists(fake_rate_file_name))
        {
            cout << "ERROR: create_fake_pred: fake rate file " << fake_rate_file_name << " not found" << endl;
            cout << desc << "\n";
            return 1;
        }
    }
	else
	{
        cout << "ERROR: create_fake_pred: fake rate file not specified" << endl;
		cout << desc << "\n";
		return 1;
	}

    // check that vertex reweight file exists
    if (!vtxreweight_file.empty())
    { 
        if (!rt::exists(vtxreweight_file))
        {
            cout << "ERROR: FakeRateStudy: vertex reweight file " << vtxreweight_file << " not found" << endl;
            cout << desc << "\n";
            return 1;
        }
    }

    // do the main analysis
    // -------------------------------------------------------------------------------------------------//
    
    // sample info
	TChain chain("tree");
	chain.Add(input_file.c_str());
	if (verbose) {rt::PrintFilesFromTChain(chain);}

    // scan the chain
    FakePredScanChain
    (
        /*input chain ptr =*/&chain,
        FakePredLooper
        (
            output_file,       
            vtxreweight_file,
            fake_rate_file_name,
            fake_rate_hist_name,
            num_btags,
            directb,
            lumi,
            verbose,
            !suffix.empty(),  
            suffix
        ),
        number_of_events,
        //is_data,
        false,
        verbose
    );
    
    // done 
    return 0;
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
