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
    std::string fake_rate_file_name = "data/fake_rates/ssFR_data_standard_16Dec2012.root";
    std::string flip_rate_file_name = "data/flip_rates/fliprate42X.root";
    std::string suffix              = "";
    std::string vtxreweight_file    = "";
    std::string sample_name         = "";
    std::string analysis_type_name  = "high_pt";
    std::string event_list_name     = "";
    std::string good_run_list       = "";
    bool exclusive                  = false;
    bool do_scale_factors           = true;
    bool check_good_lumi            = true;
    float sparm0                    = -999;
    float sparm1                    = -999;
    float sparm2                    = -999;
    float sparm3                    = -999;
    float sf_flip                   = 0.8;
    float fake_sys_unc              = 0.5;
    float flip_sys_unc              = 0.2;
    float mc_sys_unc                = 0.5;
    unsigned int num_btags          = 0;
    unsigned int num_jets           = 2;
    int charge_option               = 0;
    unsigned int signal_region_num  = 0;
    float lumi                      = 1.0;
    float l1_min_pt                 = 5.0;
    float l1_max_pt                 = 10000000.0;
    float l2_min_pt                 = 5.0;
    float l2_max_pt                 = 10000000.0;
    float min_ht                    = 80.0;
    bool verbose                    = false;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"     , "print this menu")
        ("nev"      , po::value<long>(&number_of_events)          , "number of events to run on (-1 == all)"                     )
        ("output"   , po::value<std::string>(&output_file)        , "name of output root file (optional)"                        )
        ("input"    , po::value<std::string>(&input_file)         , "name of input root file (optional)"                         )
        ("sample"   , po::value<std::string>(&sample_name)        , "name of input sample (from at/Sample.h)"                    )
        ("anal_type", po::value<std::string>(&analysis_type_name) , "name of analysis type (from AnalysisType.h)"                )
        ("fr_file"  , po::value<std::string>(&fake_rate_file_name), "fake rate file name"                                        )
        ("fl_file"  , po::value<std::string>(&flip_rate_file_name), "flip rate file name"                                        )
        ("vtx_file" , po::value<std::string>(&vtxreweight_file)   , "ROOT file for the vertex reweight (ignored for data)"       )
        ("evt_list" , po::value<std::string>(&event_list_name)    , "name of file for event list.  empty for none"               )
        ("run_list" , po::value<std::string>(&good_run_list)      , "Good Run list (no default)"                                 )
        ("suffix"   , po::value<std::string>(&suffix)             , "suffix to print (png, eps, pdf, all).  empty for none"      )
        ("nbtags"   , po::value<unsigned int>(&num_btags)         , "number of btags to cut on (default is 0)"                   )
        ("njets"    , po::value<unsigned int>(&num_jets)          , "number of jets to cut on (default is 2)"                    )
        ("sr"       , po::value<unsigned int>(&signal_region_num) , "signal region number (default is 0)"                        )
        ("do_sf"    , po::value<bool>(&do_scale_factors)          , "use the MC scale factors (default is true)"                 )
        ("gr"       , po::value<bool>(&check_good_lumi)           , "for data, check the is_good_lumi() method"                  )
        ("sparm0"   , po::value<float>(&sparm0)                   , "sparm0 value is required"                                   )
        ("sparm1"   , po::value<float>(&sparm1)                   , "sparm1 value is required"                                   )
        ("sparm2"   , po::value<float>(&sparm2)                   , "sparm2 value is required"                                   )
        ("sparm3"   , po::value<float>(&sparm3)                   , "sparm3 value is required"                                   )
        ("sf_flip"  , po::value<float>(&sf_flip)                  , "scale factor for flips (default is 0.8)"                    )
        ("fr_unc"   , po::value<float>(&fake_sys_unc)             , "systematic uncertainty for fake prediction (default is 0.5)")
        ("fl_unc"   , po::value<float>(&flip_sys_unc)             , "systematic uncertainty for flip prediction (default is 0.2)")
        ("mc_unc"   , po::value<float>(&mc_sys_unc)               , "systematic uncertainty for MC prediction (default is 0.5)"  )
        ("lumi"     , po::value<float>(&lumi)                     , "luminosity"                                                 )
        ("charge"   , po::value<int>(&charge_option)              , "charge option (1 is ++ events, -1 is -- events, 0 is both)" )
        ("excl"     , po::value<bool>(&exclusive)                 , "use exclusive signal region"                                )
        ("l1_min_pt", po::value<float>(&l1_min_pt)                , "trailing lepton min pT"                                     )
        ("l1_max_pt", po::value<float>(&l1_max_pt)                , "trailing lepton max pT"                                     )
        ("l2_min_pt", po::value<float>(&l2_min_pt)                , "leading lepton min pT"                                      )
        ("l2_max_pt", po::value<float>(&l2_max_pt)                , "leading lepton max pT"                                      )
        ("ht"       , po::value<float>(&min_ht)                   , "min HT"                                                     )
        ("verbose"  , po::value<bool>(&verbose)                   , "verbosity"                                                  )
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
    
	// analysis type
    const ss::AnalysisType::value_type analysis_type = ss::GetAnalysisTypeFromName(analysis_type_name); 
    const ss::AnalysisTypeInfo ati                   = ss::GetAnalysisTypeInfo(analysis_type); 

    // signal region and type
    const SignalRegionType::value_type signal_region_type = (exclusive ? SignalRegionType::exclusive : SignalRegionType::inclusive);
    const std::string signal_region_type_name             = GetSignalRegionTypeName(signal_region_type);
    const string signal_region_name                       = Form("sr%d", signal_region_num);
    const SignalRegion::value_type signal_region          = GetSignalRegionFromName(signal_region_name, ati.name, signal_region_type_name);

	// input
    TChain* chain  = NULL;
    bool is_data   = false;
    bool is_signal = false;
    at::Sample::value_type sample = at::Sample::static_size;
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
			const string short_name = ati.short_name.c_str();
            input_file = Form("babies/%s/%s.root", short_name.c_str(), sample_name.c_str());
            // special case for ttbar breakdown
            switch (sample)
            {
                case at::Sample::ttdil: input_file = Form("babies/%s/ttjets.root", short_name.c_str()) ; break; 
                case at::Sample::ttotr: input_file = Form("babies/%s/ttjets.root", short_name.c_str()); break;
                case at::Sample::ttslb: input_file = Form("babies/%s/ttjets.root", short_name.c_str()); break;
                case at::Sample::ttslo: input_file = Form("babies/%s/ttjets.root", short_name.c_str()); break;
                default: {/*do nothing*/}
            }

        }
        if (output_file.empty())
        {
            const char* sr = GetSignalRegionInfo(signal_region, analysis_type, signal_region_type).name.c_str();
            output_file = Form("plots/test/%s/%s/%s/%s.root", ati.name.c_str(), signal_region_type_name.c_str(), sr, sample_name.c_str());
        }
		chain = new TChain("tree");
		chain->Add(input_file.c_str());
        cout << input_file << endl;
	}

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
            signal_region_type,
            vtxreweight_file,
            fake_rate_file_name,
            flip_rate_file_name,
			event_list_name,
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
            fake_sys_unc,
            flip_sys_unc,
            mc_sys_unc,
            lumi,
            l1_min_pt,
            l1_max_pt,
            l2_min_pt,
            l2_max_pt,
            min_ht,
            verbose
        ),
        samesignbtag,
        number_of_events,
        good_run_list,
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
