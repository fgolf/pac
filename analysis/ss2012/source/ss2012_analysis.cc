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
#include "AnalysisLooper.h"

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
    bool gen_only                   = false;
    double luminosity               = 1.0;
    std::string output_file         = "";
    std::string input_file          = "";
    std::string ntuple_type_name    = "cms2";
    std::string fake_rate_file_name = "data/fake_rates/ssFR_data_standard_23May2012.root";
    std::string flip_rate_file_name = "data/flip_rates/fliprate42X.root";
    std::string fake_rate_hist_name = "h_mufr40c";
    std::string sample_name         = "data";
    std::string vtxreweight_file    = "";
    std::string good_run_list       = "";
    bool sync_print                 = false;
    bool sparms                     = false;
    bool switchSigns                = false;
    int jetMetScale                 = 0;
    bool isFastSim                  = false;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"          , "print this menu")
        ("nev"           , po::value<long>(&number_of_events)           , "number of events to run on (-1 == all)"                                            )
        ("lumi"          , po::value<double>(&luminosity)               , "luminosity of analysis (1 fb^-1 default -- ignored for data)"                      )
        ("verbose"       , po::value<bool>(&verbose)                    , "output debug info"                                                                 )
        ("gen_only"      , po::value<bool>(&gen_only)                   , "only fill gen variables"                                                           )
        ("sample"        , po::value<std::string>(&sample_name)         , "name of input sample (from at/Sample.h)"                                           )
        ("ntuple_type"   , po::value<std::string>(&ntuple_type_name)    , "ntuple type name (cms2, ss_skim, tensor, ...)"                                     )
        ("output"        , po::value<std::string>(&output_file)         , "output ROOT file for baby tree (<sample name>.root)"                               )
        ("input"         , po::value<std::string>(&input_file)          , "input ntuple (default for the sample in DataSetFactory.cpp)"                       )
        ("fr"            , po::value<std::string>(&fake_rate_file_name) , "fake rate file name (default: data/fake_rates/ssFR_data_standard_23May2012.root)"  )
        ("fl"            , po::value<std::string>(&flip_rate_file_name) , "flip rate file name (default: data/flip_rates/fliprate42X.root)"                   )
        ("fr_hist"       , po::value<std::string>(&fake_rate_hist_name) , "fake rate histogram name (default: h_mufr40c)"                                     )  // to do for muons
        ("vtx_file"      , po::value<std::string>(&vtxreweight_file)    , "ROOT file for the vertex reweight (ignored for data)"                              )
        ("run_list"      , po::value<std::string>(&good_run_list)       , "Good Run list (no default)"                                                        )
        ("sparms"        , po::value<bool>(&sparms)                     , "unpack the sparms"                                                                 )
        ("switchSigns"   , po::value<bool>(&switchSigns)                , "switch the meaning of SS and OS"                                                   )
        ("sync_print"    , po::value<bool>(&sync_print)                 , "print for sync"                                                                    )
        ("jetMetScale"   , po::value<int>(&jetMetScale)                 , "+1 to scale jets up, -1 to scale jets down"                                        )
        ("isFastSim"     , po::value<bool>(&isFastSim)                  , "use FastSim btag scale factors"                                                    )
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
		cout << "good_run_list      :\t" << good_run_list       << endl;
		cout << "fake_rate_file_name:\t" << fake_rate_file_name << endl;
		cout << "flip_rate_file_name:\t" << flip_rate_file_name << endl;
		cout << "sparms             :\t" << sparms              << endl;
		cout << "switchSigns        :\t" << switchSigns         << endl;
		cout << "jetMetScale        :\t" << jetMetScale         << endl;
		cout << "isFastSim          :\t" << isFastSim           << endl;
	}

    // test inputs boundary conditions
    // -------------------------------------------------------------------------------------------------//

    // path to the analysis
    //std::string analysis_path = rt::getenv("SS");

    // Make sure jetMetScale is kosher
    if (jetMetScale < -1 || jetMetScale > 1) 
	{
		cout << "Illegal jetMetScale " << endl;
		return 1;
	}

    // check that vertex reweight file exists
    if (!vtxreweight_file.empty())
    { 
        //vtxreweight_file = analysis_path + "/" + vtxreweight_file; 
        if (!rt::exists(vtxreweight_file))
        {
            cout << "SSAnalysis error: vertex reweight file " << vtxreweight_file << " not found" << endl;
            cout << desc << "\n";
            return 1;
        }
    }

    // check that good run file file exists
    if (!good_run_list.empty())
    {
        //good_run_list = analysis_path + "/" + good_run_list; 
        if (!rt::exists(good_run_list))
        {
            cout << "SSAnalysis error: good run list file " << good_run_list << " not found" << endl;
            cout << desc << "\n";
            return 1;
        }
    }

    // check that fake rate root file exists 
    if (!fake_rate_file_name.empty())
    {
        //fake_rate_file_name = analysis_path + "/" + fake_rate_file_name; 
        if (!rt::exists(fake_rate_file_name))
        {
            cout << "SSAnalysis error: fake rate root file " << fake_rate_file_name << " not found" << endl;
            cout << desc << "\n";
            return 1;
        }
    }
    else
    {
        cout << "SSAnalysis error: fake rate root file not specified! Exiting..." << endl;
        cout << desc << "\n";
    }

    // check that flip rate root file exists 
    if (!flip_rate_file_name.empty())
    {
        //flip_rate_file_name = analysis_path + "/" + flip_rate_file_name; 
        if (!rt::exists(flip_rate_file_name))
        {
            cout << "SSAnalysis error: fake rate root file " << flip_rate_file_name << " not found" << endl;
            cout << desc << "\n";
            return 1;
        }
    }
    else
    {
        cout << "SSAnalysis error: fake rate root file not specified! Exiting..." << endl;
        cout << desc << "\n";
    }

    // do the main analysis
    // -------------------------------------------------------------------------------------------------//

	// input
    TChain* chain  = NULL;
    bool is_data   = false;
    bool is_signal = false;
    at::Sample::value_type sample = at::Sample::static_size; 
	if (input_file.empty())
	{
        cout << "processing "  << sample_name << endl;
        sample = at::GetSampleFromName(sample_name);
        is_data   = (at::GetSampleInfo(sample).type == at::SampleType::data);
        is_signal = (at::GetSampleInfo(sample).type == at::SampleType::signal);
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
		//chain = new TChain("Events");
		//chain->Add(input_file.c_str());
        chain = rt::CreateTChainFromCommaSeperatedList(input_file, "Events");
	}

    cout << "sample has " << chain->GetEntries() << " entries" << endl;
    if (verbose) {rt::PrintFilesFromTChain(chain);}

    // scan the chain
    at::ScanChainCMS2
    (
        chain, 
        SSAnalysisLooper 
        (
            output_file,
            sample,
            fake_rate_file_name,
            flip_rate_file_name,
            fake_rate_hist_name,
            good_run_list,
            vtxreweight_file, 
            luminosity,
            sparms,
	    	jetMetScale,
	    	isFastSim,
            sync_print,
            verbose
        ),
        number_of_events,
        /*good run list=*/"",  // doing the good run list at analysis level in order to set a flag
        /*fast=*/true,
        verbose
    ); 

	// test the good run list
	//at::ScanChainCMS2(chain, at::ScanChainTestAnalysis, number_of_events, good_run_list, true, verbose);
    
	// cleanup
	delete chain;

    //TFile* f = TFile::Open(output_file.c_str(), "RECREATE");
    //TTree* t = new TTree("tree", "tree");
    //t->Write();
    //f->Close();
    //delete f;
	
    // done
    return 0;
}
catch (std::exception& e)
{
    cerr << "ss2012_analysis failed..." << endl;
    cerr << e.what() << endl;
    return 1;
}

