#include <iostream>
#include <string>
#include "TChain.h"
#include "FRClosureLooper.h"
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
    std::string fake_rate_file_name = "data/fake_rates/ssFR_data_standard_29Jan2013_d0Cut.root";
    std::string mufr_hist_name      = "h_mufr40c";
    std::string elfr_hist_name      = "h_elfr40c";
    std::string vtxreweight_file    = "";
    std::string sample_name         = "";
    std::string analysis_type_name  = "high_pt";
    bool exclusive                  = false;
    bool do_scale_factors           = false;
    bool do_scale1fb                = false;
    unsigned int num_btags          = 0;
    unsigned int num_jets           = 2;
    float met_cut                   = 0;
    float ht_cut                    = 0;
    int charge_option               = 0;
    unsigned int signal_region_num  = 0;
    float lumi                      = 1.0;
    bool verbose                    = false;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"     , "print this menu")
        ("nev"      , po::value<long>(&number_of_events)          , "number of events to run on (-1 == all)"                    )
        ("output"   , po::value<std::string>(&output_file)        , "name of output root file"                                  )
        ("input"    , po::value<std::string>(&input_file)         , "name of input root file"                                   )
        ("sample"   , po::value<std::string>(&sample_name)        , "name of input sample (from at/Sample.h)"                   )
        ("fr_file"  , po::value<std::string>(&fake_rate_file_name), "fake rate file name"                                       )
        ("anal_type", po::value<std::string>(&analysis_type_name) , "name of analysis type (from AnalysisType.h)"               )
        ("mufr"     , po::value<std::string>(&mufr_hist_name)     , "muon fake rate hist name"                                  )
        ("elfr"     , po::value<std::string>(&elfr_hist_name)     , "electron fake rate hist name"                              )
        ("vtx_file" , po::value<std::string>(&vtxreweight_file)   , "ROOT file for the vertex reweight (ignored for data)"      )
        ("nbtags"   , po::value<unsigned int>(&num_btags)         , "number of btags to cut on"                                 )
        ("njets"    , po::value<unsigned int>(&num_jets)          , "number of jets to cut on"                                  )
        ("met"      , po::value<float>(&met_cut)                  , "met to cut on"                                             )
        ("ht"       , po::value<float>(&ht_cut)                   , "ht to cut on"                                              )
        ("sr"       , po::value<unsigned int>(&signal_region_num) , "signal region number"                                      )
        //("do_sf"    , po::value<bool>(&do_scale_factors)          , "use the scale factors (default is true)"                   )
        ("do_1fb"   , po::value<bool>(&do_scale1fb)               , "use the scale1fb (default is false)"                       )
        ("lumi"     , po::value<float>(&lumi)                     , "luminosity"                                                )
        ("charge"   , po::value<int>(&charge_option)              , "charge option (1 is ++ events, -1 is -- events, 0 is both)")
        ("excl"     , po::value<bool>(&exclusive)                 , "use exclusive signal region"                               )
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
    //if (!input_file.empty())
    //{ 
    //    if (!rt::exists(input_file))
    //    {
    //        cout << "ERROR: ss2012_plots: input file " << input_file << " not found" << endl;
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
    const SignalRegionInfo signal_region_info             = GetSignalRegionInfo(signal_region, analysis_type, signal_region_type);

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
            //chain = new TChain("tree");
            //chain->Add(input_file.c_str());
            chain = rt::CreateTChainFromCommaSeperatedList(input_file, "tree");
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
            input_file = Form("babies/%s/%s.root", ati.short_name.c_str(), sample_name.c_str());
            //                 // special case for ttbar breakdown
            //                 switch (sample)
            //                 {
            //                     case at::Sample::ttdil: input_file = Form("babies/%s/ttdil.root", ati.short_name.c_str()); break; 
            //                     case at::Sample::ttotr: input_file = Form("babies/%s/ttotr.root", ati.short_name.c_str()); break;
            //                     case at::Sample::ttslb: input_file = Form("babies/%s/ttslb.root", ati.short_name.c_str()); break;
            //                     case at::Sample::ttslo: input_file = Form("babies/%s/ttslo.root", ati.short_name.c_str()); break;
            //                     default: {/*do nothing*/}
            //                 }
            chain = new TChain("tree");
            chain->Add(input_file.c_str());
        }
        else
        {
            chain = rt::CreateTChainFromCommaSeperatedList(input_file, "tree");
        }
        if (output_file.empty())
        {
            output_file = Form("plots/closure_test/%s/%s.root", signal_region_info.name.c_str(), sample_name.c_str());
        }
        cout << "input file(s) = " << input_file << endl;
    }

    // scan the chain
    ScanChain
    (
       chain,
       FRClosureLooper
       (
            output_file,       
            sample,
            signal_region,
            analysis_type,
            signal_region_type,
            vtxreweight_file,
            fake_rate_file_name,
            mufr_hist_name,
            elfr_hist_name,
            do_scale_factors,
            do_scale1fb,
            num_btags,
            num_jets,
            met_cut,
            ht_cut,
            charge_option,
            lumi,
            verbose
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
