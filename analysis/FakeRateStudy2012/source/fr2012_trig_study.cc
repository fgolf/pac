#include "FakeRateTrigStudy.h"
#include <iostream>
#include <string>
#include "TChain.h"
#include "fr/Sample.h"
#include "FakeRateBabyWrapper.h"
#include "at/ScanChain.h"
#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>
#include "rt/RootTools.h"

// validate channels
bool ValidLeptonName(const std::string& channel)
{
    if (channel == "mu")
        return true;
    if (channel == "el")
        return true;
    return false;
}


int main(int argc, char* argv[])
try
{
    // set the style
    rt::SetStyle("emruoi");

    using namespace std;

    // inputs
    // -------------------------------------------------------------------------------------------------//

    long number_of_events      = -1;
    std::string sample_name    = "data";
    std::string root_file_name = "plots/test/test.root";
    std::string good_run_list  = "";
    std::string channel        = "both";
    std::string suffix         = "";
	float lumi				   = 1.0;
    bool verbose               = false;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"          , "print this menu")
        ("nev"           , po::value<long>(&number_of_events)         , "number of events to run on (-1 == all)"          )
        ("lumi"          , po::value<float>(&lumi)                    , "luminosity (default is 1.0 fb)"                  )
        ("sample"        , po::value<std::string>(&sample_name)       , "name of dataset"                                 )
        ("channel"       , po::value<std::string>(&channel)           , "name of channel (valid options: \"mu\", \"el\")" )
        ("root_file_name", po::value<std::string>(&root_file_name)    , "name of output root file"                        )
        ("suffix"        , po::value<std::string>(&suffix)            , "suffix to pring (png, eps, pdf).  empty for nonf")
        ("verbose"       , po::value<bool>(&verbose)                  , "verbosity"                                       )
        ("run_list"      , po::value<std::string>(&good_run_list)     , "good run list"                                   )
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

    // check that the channel option is one of the supported
    if (!ValidLeptonName(channel))
    {
        cout << "ERROR: invalid channel option" << endl;
        cout << desc << "\n";
        return 1;
    }

    // do the main analysis
    // -------------------------------------------------------------------------------------------------//

    // sample 
    fr::Sample::value_type sample = fr::GetSampleFromName(sample_name);

    // output 
    std::string full_output_path = root_file_name.empty() ? fr::GetSampleInfo(sample).output_file : root_file_name;  
	rt::string_replace_all(full_output_path, ".root", "_trig.root");
    cout << "output file: " << full_output_path << endl;

    // input chain
    boost::shared_ptr<TChain> chain(fr::GetSampleTChain(sample));

    // scan the chain
    at::ScanChain<FakeRateBaby>
	(
		/*input chain ptr =*/chain.get(), 
		FakeRateTrigStudy
		(
			full_output_path, 
            sample,
			channel, 
			lumi, 
			verbose, 
			!suffix.empty(), suffix
		), 
        fake_rate_baby,
        number_of_events,
        good_run_list, 
        /*fast=*/true,
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
