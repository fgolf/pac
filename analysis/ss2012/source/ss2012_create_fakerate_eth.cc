#include <iostream>
#include <string>
#include "TChain.h"
#include "FakeRateBabyWrapper.h"
#include "FakeRateBabyLooperETH.h"
#include "at/ScanChain.h"
#include "rt/RootTools.h"
#include "fr/Sample.h"
#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>

bool ValidCharge(int charge)
{
    switch(charge)
    {
        case 1: 
        case -1:
        case 0:
            return true;
            break;
        default:
            return false;
    }
    return false;
}

bool ValidLeptonName(const std::string& channel)
{
    if (channel == "mu")
        return true;
    if (channel == "el")
        return true;
//    if (channel == "both")
//        return true;
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

    long number_of_events          = -1;
    std::string sample_name        = "data";
    std::string root_file_name     = "test.root";
    std::string channel            = "mu";
    std::string suffix             = "";
    std::string good_run_list      = "";
    bool verbose                   = false;
    float lumi			   = 1.0;
    int charge                     = 0;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"          , "print this menu")
        ("nev"           , po::value<long>(&number_of_events)      , "number of events to run on (-1 == all)"           )
        ("lumi"          , po::value<float>(&lumi)                 , "luminosity (default is 1.0 fb)"                   )
        ("sample"        , po::value<std::string>(&sample_name)    , "name of sample"                                   )
        ("channel"       , po::value<std::string>(&channel)        , "name of channel (valid options: \"mu\", \"el\")"  )
        ("root_file_name", po::value<std::string>(&root_file_name) , "name of output root file"                         )
        ("run_list"      , po::value<std::string>(&good_run_list)  , "good run list"                                    )
        ("suffix"        , po::value<std::string>(&suffix)         , "suffix to pring (png, eps, pdf).  empty for nonf" )
        ("charge"        , po::value<int>(&charge)                 , "-1: +ve, -1: -ve, 0: both"                        )
        ("verbose"       , po::value<bool>(&verbose)               , "verbosity"                                        )
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

    // check that the charge option is one of the supported
    if (!ValidCharge(charge))
    {
        cout << "ERROR: invalid charge option" << endl;
        cout << desc << "\n";
        return 1;
    }

    // do the main analysis
    // -------------------------------------------------------------------------------------------------//

    // directories
    // std::string analysis_path = rt::getenv("SS");
    std::string analysis_path = rt::getenv("PAC") + "/analysis/ss2012";
    root_file_name = rt::string_contains(root_file_name, ".root") ? rt::string_remove_all(root_file_name, ".root") : root_file_name;
    std::string root_base_name = rt::basename(root_file_name);
    std::string full_output_path = Form("%s/plots/fake_rates/%s/%s.root", analysis_path.c_str(), root_base_name.c_str(), root_file_name.c_str()); 
    cout << "output file: " << full_output_path << endl;

    // data
    fr::Sample::value_type sample = fr::GetSampleFromName(sample_name); 
    boost::shared_ptr<TChain> chain(fr::GetSampleTChain(sample));

    // scan the chain
    at::ScanChainWithFilename<FakeRateBaby>
    (
        /*input chain ptr =*/chain.get(), 
        FakeRateBabyLooperETH(full_output_path, sample, channel, lumi, charge, verbose, !suffix.empty(), suffix), 
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
