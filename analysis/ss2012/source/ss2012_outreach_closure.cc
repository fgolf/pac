// c++
#include <iostream>
#include <string>

// ROOT
#include "TChain.h"
#include "TSystem.h"
#include "Math/LorentzVector.h"

// tools
#include "rt/RootTools.h"

// analysis
#include "CMS2Wrapper.h"
#include "at/ScanChain.h"
#include "at/Sample.h"
#include "OutreachClosure.h"
#include "OutreachBabyWrapper.h"

// BOOST
#include <boost/program_options.hpp>

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
    std::string output_file         = "";
    std::string input_file          = "";
    std::string sample_name         = "data";
    std::string fit_file_name       = "";

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"          , "print this menu")
        ("nev"           , po::value<long>(&number_of_events)           , "number of events to run on (-1 == all)"                                            )
        ("verbose"       , po::value<bool>(&verbose)                    , "output debug info"                                                                 )
        ("sample"        , po::value<std::string>(&sample_name)         , "name of input sample (from at/Sample.h)"                                           )
        ("output"        , po::value<std::string>(&output_file)         , "output ROOT file for baby tree (<sample name>.root)"                               )
        ("input"         , po::value<std::string>(&input_file)          , "input ntuple (default for the sample in DataSetFactory.cpp)"                       )
        ("fit_file"      , po::value<std::string>(&fit_file_name)       , "file for outreach fitted eff histograms ROOT file"                                 )
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
		cout << "number_of_events   :\t" << number_of_events    << endl;
		cout << "verbose            :\t" << verbose             << endl;
		cout << "sample_name        :\t" << sample_name         << endl;
		cout << "output_file        :\t" << output_file         << endl;
		cout << "input_file         :\t" << input_file          << endl;
		cout << "fit_file           :\t" << fit_file_name       << endl;
	}

    // do the main analysis
    // -------------------------------------------------------------------------------------------------//

	// input
    TChain chain("tree");
    at::Sample::value_type sample = !sample_name.empty() ? at::GetSampleFromName(sample_name) : at::Sample::static_size; 
   
	if (input_file.empty())
	{
        chain.Add(Form("babies_outreach/%s.root", sample_name.c_str()));
	}
	else
	{
        chain.Add(input_file.c_str());
	}

	// output
    if (output_file.empty())
    {
        output_file = Form("plots/outreach/closure/%s.root", rt::filename(sample_name).c_str());
    }

    cout << "sample has " << chain.GetEntries() << " entries" << endl;
    if (verbose) {rt::PrintFilesFromTChain(chain);}

    // scan the chain
    at::ScanChain
    (
        &chain, 
        OutreachClosure 
        (
            output_file,
            sample,
            fit_file_name,
            verbose
        ),
        outreach_baby,
        number_of_events,
        /*good run list=*/"",  // doing the good run list at analysis level in order to set a flag
        /*fast=*/true,
        verbose
    ); 

    // done
    return 0;
}
catch (std::exception& e)
{
    cerr << "ss2012_analysis failed..." << endl;
    cerr << e.what() << endl;
    return 1;
}
