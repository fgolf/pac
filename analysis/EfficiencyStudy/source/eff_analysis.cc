// c++
#include <iostream>
#include <string>

// ROOT
#include "TChain.h"
#include "TSystem.h"

// tools
#include "rt/RootTools.h"

// analysis
#include "at/ScanChain.h"
#include "at/Sample.h"
#include "EffAnalysisLooper.h"
#include "CMS2Wrapper.h"

// BOOST
#include <boost/program_options.hpp>
#include "Math/LorentzVector.h"

// typdefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

using namespace std;

int main(int argc, char* argv[])
try
{
    // inputs
    // -------------------------------------------------------------------------------------------------//

    long number_of_events           = -1;
    bool verbose                    = false;
    double luminosity               = 1.0;
    std::string output_file         = "";
    std::string input_file          = "";
    std::string ntuple_type_name    = "cms2";
    std::string sample_name         = "";

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"          , "print this menu")
        ("nev"           , po::value<long>(&number_of_events)           , "number of events to run on (-1 == all)"                                            )
        ("lumi"          , po::value<double>(&luminosity)               , "luminosity of analysis (1 fb^-1 default -- ignored for data)"                      )
        ("verbose"       , po::value<bool>(&verbose)                    , "output debug info"                                                                 )
        ("sample"        , po::value<std::string>(&sample_name)         , "name of input sample (from at/Sample.h)"                                           )
        ("ntuple_type"   , po::value<std::string>(&ntuple_type_name)    , "ntuple type name (cms2, ss_skim, ...) (from at/Sample.h)"                          )
        ("output"        , po::value<std::string>(&output_file)         , "output ROOT file for baby tree (default: <sample name>.root)"                      )
        ("input"         , po::value<std::string>(&input_file)          , "input ntuple (default is determined by the sample used)"                           )
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

    if (verbose)
    {
        cout << "inputs:" << endl;
        cout << "number_of_events   :\t" << number_of_events     << endl;
        cout << "luminosity         :\t" << luminosity           << endl;
        cout << "verbose            :\t" << verbose              << endl;
        cout << "sample_name        :\t" << sample_name          << endl;
        cout << "ntuple_type_name   :\t" << ntuple_type_name     << endl;
        cout << "output_file        :\t" << output_file          << endl;
        cout << "input_file         :\t" << input_file           << endl;
    }

    // test inputs boundary conditions
    // -------------------------------------------------------------------------------------------------//

    // do the main analysis
    // -------------------------------------------------------------------------------------------------//

    // input
    TChain* chain  = NULL;
    at::Sample::value_type sample = at::Sample::static_size; 
	if (not sample_name.empty())
	{
        cout << "processing "  << sample_name << endl;
        sample = at::GetSampleFromName(sample_name);
	}
	else
	{
        cout << "no sample name given." << endl;
	}
    if (input_file.empty())
    {
        chain = at::GetSampleTChain(sample, at::GetNtupleTypeFromName(ntuple_type_name));
        if (output_file.empty())
        {
            output_file = Form("babies/%s.root", sample_name.c_str());
        }
    }
    else
    {
        if (output_file.empty())
        {
            output_file = Form("babies/%s.root", rt::filename(sample_name).c_str());
        }
        chain = rt::CreateTChainFromCommaSeperatedList(input_file, "Events");
    }

    cout << "sample has " << chain->GetEntries() << " entries" << endl;
    cout << "sample has " << chain->GetListOfFiles()->GetEntries() << " files" << endl;
    if (verbose) {rt::PrintFilesFromTChain(chain);}

    // scan the chain
    at::ScanChainWithFilename<CMS2>
    (
        chain, 
        EffAnalysisLooper 
        (
            output_file,
            sample,
            luminosity,
            verbose
        ),
        cms2,
        number_of_events,
        "",//good_run_list,
        /*fast=*/true,
        verbose
    ); 

    // cleanup
    delete chain;

    // done
    return 0;
}
catch (std::exception& e)
{
    cerr << "eff_analysis failed..." << endl;
    cerr << e.what() << endl;
    return 1;
}

