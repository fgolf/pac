#include <iostream>
#include <string>
#include "TChain.h"
#include "PlotLooper.h"
#include "SSB2012Wrapper.h"
#include "at/ScanChain.h"
#include "rt/RootTools.h"
#include "SignalRegion.h"
#include <boost/program_options.hpp>

int main(int argc, char* argv[])
try
{
    // set the style
    rt::SetStyle("emruoi");

    using namespace std;
    using namespace ss;

    // inputs
    // -------------------------------------------------------------------------------------------------//

    long number_of_events           = -1;
    std::string input_file          = "";
    std::string output_file         = "";
    std::string fake_rate_file_name = "data/fake_rates/ssFR_data_standard_24Sep2012.root";
    std::string flip_rate_file_name = "data/flip_rates/fliprate42X.root";
    std::string suffix              = "";
    std::string vtxreweight_file    = "";
    std::string sample_name         = "";
    std::string analysis_type_name  = "high_pt";
    bool do_scale_factors           = true;
    bool check_good_lumi            = true;
    float sparm0                    = -999;
    float sparm1                    = -999;
    float sparm2                    = -999;
    float sparm3                    = -999;
    float sf_flip                   = 0.8;
    unsigned int num_btags          = 0;
    unsigned int num_jets           = 2;
    int charge_option               = 0;
    unsigned int signal_region_num  = 0;
    bool exclusive                  = false;
    float lumi                      = 1.0;
    float min_pt                    = 20.0;
    float max_pt                    = 10000000.0;
    bool verbose                    = false;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"     , "print this menu")
        ("nev"      , po::value<long>(&number_of_events)          , "number of events to run on (-1 == all)"                    )
        ("output"   , po::value<std::string>(&output_file)        , "name of output root file"                                  )
        ("input"    , po::value<std::string>(&input_file)         , "name of input root file"                                   )
        ("sample"   , po::value<std::string>(&sample_name)        , "name of input sample (from at/Sample.h)"                   )
        ("anal_type", po::value<std::string>(&analysis_type_name) , "name of input sample (from at/AnalysisType.h)"             )
        ("fr_file"  , po::value<std::string>(&fake_rate_file_name), "fake rate file name"                                       )
        ("fl_file"  , po::value<std::string>(&flip_rate_file_name), "flip rate file name"                                       )
        ("vtx_file" , po::value<std::string>(&vtxreweight_file)   , "ROOT file for the vertex reweight (ignored for data)"      )
        ("suffix"   , po::value<std::string>(&suffix)             , "suffix to pring (png, eps, pdf).  empty for none"          )
        ("nbtags"   , po::value<unsigned int>(&num_btags)         , "number of btags to cut on"                                 )
        ("njets"    , po::value<unsigned int>(&num_jets)          , "number of jets to cut on"                                  )
        ("sr"       , po::value<unsigned int>(&signal_region_num) , "signal region number"                                      )
        ("do_sf"    , po::value<bool>(&do_scale_factors)          , "use the scale factors (default is true)"                   )
        ("gr"       , po::value<bool>(&check_good_lumi)           , "for data, check the is_good_lumi() method"                 )
        ("sparm1"   , po::value<float>(&sparm0)                   , "sparm0"                                                    )
        ("sparm2"   , po::value<float>(&sparm1)                   , "sparm1"                                                    )
        ("sparm3"   , po::value<float>(&sparm2)                   , "sparm2"                                                    )
        ("sparm4"   , po::value<float>(&sparm3)                   , "sparm3"                                                    )
        ("sf_flip"  , po::value<float>(&sf_flip)                  , "scale factor for flips"                                    )
        ("lumi"     , po::value<float>(&lumi)                     , "luminosity"                                                )
        ("charge"   , po::value<int>(&charge_option)              , "charge option (1 is ++ events, -1 is -- events, 0 is both)")
        ("excl"     , po::value<bool>(&exclusive)                 , "use exclusive signal region"                               )
        ("min_pt"   , po::value<float>(&min_pt)                   , "min pT"                                                    )
        ("max_pt"   , po::value<float>(&max_pt)                   , "max pT"                                                    )
        ("verbose"  , po::value<bool>(&verbose)                   , "verbosity"                                                 )
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
    string signal_region_name = Form(exclusive ? "ex_sr%d" : "sr%d", signal_region_num);
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
        sample    = at::GetSampleFromName(sample_name);
        is_data   = (at::GetSampleInfo(sample).type == at::SampleType::data);
        is_signal = false; // not used 
        if (input_file.empty())
        {
            input_file = Form("babies/%s.root", sample_name.c_str());
            // special case for ttbar breakdown
            switch (sample)
            {
                case at::Sample::ttdil: input_file = "babies/ttjets.root"; break; 
                case at::Sample::ttotr: input_file = "babies/ttjets.root"; break;
                case at::Sample::ttslb: input_file = "babies/ttjets.root"; break;
                case at::Sample::ttslo: input_file = "babies/ttjets.root"; break;
                default: {/*do nothing*/}
            }

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

	// analysis type
    ss::AnalysisType::value_type analysis_type = ss::GetAnalysisTypeFromName(analysis_type_name); 

    // scan the chain
    ScanChain
    (
        chain,
        PlotLooper
        (
            output_file,       
            sample,
            signal_region,
			analysis_type,
            vtxreweight_file,
            fake_rate_file_name,
            flip_rate_file_name,
            num_btags,
            num_jets,
            charge_option,
            do_scale_factors,
            check_good_lumi, 
            sparm0,
            sparm1,
            sparm2,
            sparm3,
            sf_flip,
            lumi,
            min_pt,
            max_pt,
            verbose,
            !suffix.empty(),  
            suffix
        ),
        samesignbtag,
        number_of_events,
        /*good_run_file=*/"",
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
