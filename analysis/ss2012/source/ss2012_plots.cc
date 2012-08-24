#include <iostream>
#include <string>
#include "TChain.h"
#include "ScanChainSSB2012.h"
#include "PlotLooper.new.h"
#include "rt/RootTools.h"
#include "SignalRegion.h"
#include <boost/program_options.hpp>

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
    std::string output_file         = "";
    std::string fake_rate_file_name = "plots/data/data40c_pt35.root";
    std::string fake_rate_hist_name = "h_mufr40c";
    std::string suffix              = "";
    std::string vtxreweight_file    = "";
    std::string sample_name         = "";
    float m_glu                     = 1000;
    float m_lsp                     = 100;
    unsigned int num_btags          = 0;
    unsigned int signal_region_num  = 0;
    float lumi                      = 1.0;
    bool verbose                    = false;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"     , "print this menu")
        ("nev"      , po::value<long>(&number_of_events)          , "number of events to run on (-1 == all)"              )
        ("output"   , po::value<std::string>(&output_file)        , "name of output root file"                            )
        ("input"    , po::value<std::string>(&input_file)         , "name of input root file"                             )
        ("sample"   , po::value<std::string>(&sample_name)        , "name of input sample (from at/Sample.h)"             )
        ("fr_file"  , po::value<std::string>(&fake_rate_file_name), "fake rate file name"                                 )
        ("fr_hist"  , po::value<std::string>(&fake_rate_hist_name), "fake rate hist name"                                 )
        ("vtx_file" , po::value<std::string>(&vtxreweight_file)   , "ROOT file for the vertex reweight (ignored for data)")
        ("suffix"   , po::value<std::string>(&suffix)             , "suffix to pring (png, eps, pdf).  empty for none"    )
        ("nbtags"   , po::value<unsigned int>(&num_btags)         , "number of btags to cut on"                           )
        ("sr"       , po::value<unsigned int>(&signal_region_num) , "signal region number"                                )
        ("mglu"     , po::value<float>(&m_glu)                    , "gluino mass"                                         )
        ("mlsp"     , po::value<float>(&m_lsp)                    , "LSP mass"                                            )
        ("lumi"     , po::value<float>(&lumi)                     , "luminosity"                                          )
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
            cout << "ERROR: ss2012_plots: input file " << input_file << " not found" << endl;
            cout << desc << "\n";
            return 1;
        }
    }

    //// check that fake rate file exists and is specified
    //if (!fake_rate_file_name.empty())
    //{ 
    //    if (!rt::exists(fake_rate_file_name))
    //    {
    //        cout << "ERROR: create_fake_pred: fake rate file " << fake_rate_file_name << " not found" << endl;
    //        cout << desc << "\n";
    //        return 1;
    //    }
    //}
	//else
	//{
    //    cout << "ERROR: create_fake_pred: fake rate file not specified" << endl;
	//	cout << desc << "\n";
	//	return 1;
	//}

    //// check that vertex reweight file exists
    //if (!vtxreweight_file.empty())
    //{ 
    //    if (!rt::exists(vtxreweight_file))
    //    {
    //        cout << "ERROR: FakeRateStudy: vertex reweight file " << vtxreweight_file << " not found" << endl;
    //        cout << desc << "\n";
    //        return 1;
    //    }
    //}


    // do the main analysis
    // -------------------------------------------------------------------------------------------------//
    
	// input
    TChain* chain  = NULL;
    bool is_data   = false;
    bool is_signal = false;
    at::Sample::value_type sample = at::Sample::static_size;
    string signal_region_name = Form("sr%d", signal_region_num);
    SignalRegion::value_type signal_region = GetSignalRegionFromName(signal_region_name);
    if (sample_name.empty())  // use input file
    {
	    if (input_file.empty())
	    {
            cout << "ERROR: ss2012_plots: input file or sample not found -- specify one or the other" << endl; 
            cout << desc << "\n";
            return 1;
        }
        else
        {
		    chain = new TChain("tree");
		    chain->Add(input_file.c_str());
            if (output_file.empty())
            {
                output_file = "plots/test/test.root";
            }
        }
    }
    else // use the sample
    {
        cout << "processing "  << sample_name << endl;
        sample = at::GetSampleFromName(sample_name);
        is_data   = (at::GetSampleInfo(sample).type == at::SampleType::data);
        is_signal = (at::GetSampleInfo(sample).type == at::SampleType::signal);
        if (input_file.empty())
        {
            input_file = Form("babies/52X/%s.root", sample_name.c_str());
        }
        if (output_file.empty())
        {
            const char* sr = GetSignalRegionInfo(signal_region).name.c_str();
            output_file = Form("plots/%s/%s.root", sr, sample_name.c_str());
        }
		chain = new TChain("tree");
		chain->Add(input_file.c_str());
        cout << input_file << endl;
	}

    // scan the chain
    ScanChainSSB2012
    (
        chain,
        PlotLooper
        (
            output_file,       
            sample,
            signal_region,
            vtxreweight_file,
            fake_rate_file_name,
            fake_rate_hist_name,
            num_btags,
            m_glu,
            m_lsp,
            lumi,
            verbose,
            !suffix.empty(),  
            suffix
        ),
        number_of_events,
        is_data,
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
