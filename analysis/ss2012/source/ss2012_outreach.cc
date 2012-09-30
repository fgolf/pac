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
#include "OutreachLooper.h"

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
    double luminosity               = 1.0;
    std::string output_file         = "";
    std::string input_file          = "";
    std::string ntuple_type_name    = "cms2";
    std::string sample_name         = "data";
    std::string vtxreweight_file    = "";
    bool sparms                     = false;
    bool is_fastsim                 = false;
    //int num_jets                    = 0;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"          , "print this menu")
        ("nev"           , po::value<long>(&number_of_events)           , "number of events to run on (-1 == all)"                                            )
        ("lumi"          , po::value<double>(&luminosity)               , "luminosity of analysis (1 fb^-1 default -- ignored for data)"                      )
        ("verbose"       , po::value<bool>(&verbose)                    , "output debug info"                                                                 )
        ("sample"        , po::value<std::string>(&sample_name)         , "name of input sample (from at/Sample.h)"                                           )
        ("ntuple_type"   , po::value<std::string>(&ntuple_type_name)    , "ntuple type name (cms2, ss_skim, tensor, ...)"                                     )
        ("output"        , po::value<std::string>(&output_file)         , "output ROOT file for baby tree (<sample name>.root)"                               )
        ("input"         , po::value<std::string>(&input_file)          , "input ntuple (default for the sample in DataSetFactory.cpp)"                       )
        ("vtx_file"      , po::value<std::string>(&vtxreweight_file)    , "ROOT file for the vertex reweight (ignored for data)"                              )
        ("is_fastsim"    , po::value<bool>(&is_fastsim)                 , "use FastSim btag scale factors"                                                    )
        ("sparms"        , po::value<bool>(&sparms)                     , "unpack the sparms"                                                                 )
        //("njets"         , po::value<int>(&num_jets)                    , "minimum # of jets to select"                                                       )
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
		cout << "luminosity         :\t" << luminosity          << endl;
		cout << "verbose            :\t" << verbose             << endl;
		cout << "sample_name        :\t" << sample_name         << endl;
		cout << "ntuple_type_name   :\t" << ntuple_type_name    << endl;
		cout << "output_file        :\t" << output_file         << endl;
		cout << "input_file         :\t" << input_file          << endl;
		cout << "vtxreweight_file   :\t" << vtxreweight_file    << endl;
		cout << "is_fastsim         :\t" << is_fastsim          << endl;
		cout << "sparms             :\t" << sparms              << endl;
		//cout << "num_jets           :\t" << num_jets            << endl;
	}

    // do the main analysis
    // -------------------------------------------------------------------------------------------------//

	// input
    TChain* chain  = NULL;
    at::Sample::value_type sample = at::Sample::static_size; 
	if (input_file.empty())
	{
        cout << "processing "  << sample_name << endl;
        sample = at::GetSampleFromName(sample_name);
        chain = at::GetSampleTChain(sample, at::GetNtupleTypeFromName(ntuple_type_name));
	}
	else
	{
        chain = rt::CreateTChainFromCommaSeperatedList(input_file, "Events");
	}

	// output
    if (output_file.empty())
    {
        output_file = Form("babies_outreach/%s.root", rt::filename(sample_name).c_str());
    }

    cout << "sample has " << chain->GetEntries() << " entries" << endl;
    if (verbose) {rt::PrintFilesFromTChain(chain);}

    // scan the chain
    at::ScanChain
    (
        chain, 
        OutreachLooper 
        (
            output_file,
            sample,
            luminosity,
			vtxreweight_file,
            is_fastsim,
            sparms,
            verbose
        ),
        cms2,
        number_of_events,
        /*good run list=*/"",  // doing the good run list at analysis level in order to set a flag
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
    cerr << "ss2012_analysis failed..." << endl;
    cerr << e.what() << endl;
    return 1;
}
