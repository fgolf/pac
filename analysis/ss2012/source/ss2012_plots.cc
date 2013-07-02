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
    std::string fake_rate_file_name = "data/fake_rates/ssFR_data_ewkcor_17Apr2013.root";
    std::string flip_rate_file_name = "data/flip_rates/ssFL_data_standard_02222013.root";
    std::string suffix              = "";
    std::string vtxreweight_file    = "";
    std::string sample_name         = "";
    std::string analysis_type_name  = "high_pt";
    std::string event_list_name     = "";
    std::string good_run_list       = "";
    bool exclusive                  = false;
    bool do_scale_factors           = true;
    bool do_truth_matching          = true;
    bool check_good_lumi            = true;
    bool do_3lep_veto               = false;
    float sparm0                    = -999;
    float sparm1                    = -999;
    float sparm2                    = -999;
    float sparm3                    = -999;
    float sf_flip                   = 1.39;
    float fake_sys_unc              = 0.5;
    float flip_sys_unc              = 0.3;
    float mc_sys_unc                = 0.5;
    unsigned int num_btags          = 0;
    unsigned int num_jets           = 2;
    int charge_option               = 0;
    unsigned int signal_region_num  = 0;
    float lumi                      = 1.0;
    float min_ht                    = 80.0;
    bool verbose                    = false;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"     , "print this menu")
        ("sample"   , po::value<std::string>(&sample_name)->required()        , "REQUIRED: name of input sample (from at/Sample.h)"                             )
        ("anal_type", po::value<std::string>(&analysis_type_name)->required() , "REQUIRED: name of analysis type (from AnalysisType.h)"                         )
        ("sr"       , po::value<unsigned int>(&signal_region_num)->required() , "REQUIRED: signal region number (default is 0)"                                 )
        ("nev"      , po::value<long>(&number_of_events)                      , "number of events to run on (-1 == all)"                                        )
        ("output"   , po::value<std::string>(&output_file)                    , "name of output root file"                                                      )
        ("input"    , po::value<std::string>(&input_file)                     , "name of input root file"                                                       )
        ("fr_file"  , po::value<std::string>(&fake_rate_file_name)            , Form("fake rate file name (default: %s)", fake_rate_file_name.c_str())          )
        ("fl_file"  , po::value<std::string>(&flip_rate_file_name)            , Form("flip rate file name (default: %s)", flip_rate_file_name.c_str())          )
        ("vtx_file" , po::value<std::string>(&vtxreweight_file)               , "ROOT file for the vertex reweight (ignored for data)"                          )
        ("evt_list" , po::value<std::string>(&event_list_name)                , "name of file for event list.  empty for none"                                  )
        ("run_list" , po::value<std::string>(&good_run_list)                  , "Good Run list (no default)"                                                    )
        ("suffix"   , po::value<std::string>(&suffix)                         , "suffix to print (png, eps, pdf, all).  empty for none"                         )
        ("nbtags"   , po::value<unsigned int>(&num_btags)                     , "number of btags to cut on (default is 0)"                                      )
        ("njets"    , po::value<unsigned int>(&num_jets)                      , "number of jets to cut on (default is 2)"                                       )
        ("do_sf"    , po::value<bool>(&do_scale_factors)                      , "use the MC scale factors (default is true)"                                    )
        ("do_match" , po::value<bool>(&do_truth_matching)                     , "apply the truth matching to MC (default is true)"                              )
        ("gr"       , po::value<bool>(&check_good_lumi)                       , "for data, check the is_good_lumi() method"                                     )
        ("3lep_veto", po::value<bool>(&do_3lep_veto)                          , "apply veto to the third lepton in the event"                                   )
        ("sparm0"   , po::value<float>(&sparm0)                               , "sparm0 value is required"                                                      )
        ("sparm1"   , po::value<float>(&sparm1)                               , "sparm1 value is required"                                                      )
        ("sparm2"   , po::value<float>(&sparm2)                               , "sparm2 value is required"                                                      )
        ("sparm3"   , po::value<float>(&sparm3)                               , "sparm3 value is required"                                                      )
        ("sf_flip"  , po::value<float>(&sf_flip)                              , Form("scale factor for flips (default is %f)", sf_flip)                         )
        ("fr_unc"   , po::value<float>(&fake_sys_unc)                         , Form("systematic uncertainty for fake prediction (default is %f)", fake_sys_unc))
        ("fl_unc"   , po::value<float>(&flip_sys_unc)                         , Form("systematic uncertainty for flip prediction (default is %f)", fake_sys_unc))
        ("mc_unc"   , po::value<float>(&mc_sys_unc)                           , Form("systematic uncertainty for MC prediction (default is %f)", fake_sys_unc)  )
        ("lumi"     , po::value<float>(&lumi)                                 , "luminosity"                                                                    )
        ("charge"   , po::value<int>(&charge_option)                          , "charge option (1 is ++ events, -1 is -- events, 0 is both)"                    )
        ("excl"     , po::value<bool>(&exclusive)                             , "use exclusive signal region"                                                   )
        ("ht"       , po::value<float>(&min_ht)                               , "min HT"                                                                        )
        ("verbose"  , po::value<bool>(&verbose)                               , "verbosity"                                                                     )
        ;

    // parse it
    try
    {
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) 
        {
            cout << desc << "\n";
            return 1;
        }

        po::notify(vm);
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << "\nexiting" << endl;
        cout << desc << "\n";
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown error!" << "\n";
        return false;
    }

    // check that input file exists and is specified
    if (!input_file.empty())
    { 
        if (rt::ls(input_file).empty())
        {
            cout << "[ss2012_plots] Error : input file " << input_file << " not found" << endl;
            cout << desc << "\n";
            return 1;
        }
    }

    // inputs
    cout << "inputs:" << endl;
    cout << "sample_name         :\t" << sample_name         << endl;
    cout << "analysis_type_name  :\t" << analysis_type_name  << endl;
    cout << "signal_region_num   :\t" << signal_region_num   << endl;
    cout << "number_of_events    :\t" << number_of_events    << endl;
    cout << "output_file         :\t" << output_file         << endl;
    cout << "input_file          :\t" << input_file          << endl;
    cout << "fake_rate_file_name :\t" << fake_rate_file_name << endl;
    cout << "flip_rate_file_name :\t" << flip_rate_file_name << endl;
    cout << "vtxreweight_file    :\t" << vtxreweight_file    << endl;
    cout << "event_list_name     :\t" << event_list_name     << endl;
    cout << "good_run_list       :\t" << good_run_list       << endl;
    cout << "suffix              :\t" << suffix              << endl;
    cout << "num_btags           :\t" << num_btags           << endl;
    cout << "num_jets            :\t" << num_jets            << endl;
    cout << "do_scale_factors    :\t" << do_scale_factors    << endl;
    cout << "do_scale_factors    :\t" << do_scale_factors    << endl;
    cout << "check_good_lumi     :\t" << check_good_lumi     << endl;
    cout << "3lep_veto           :\t" << do_3lep_veto        << endl;
    cout << "sparm0              :\t" << sparm0              << endl;
    cout << "sparm1              :\t" << sparm1              << endl;
    cout << "sparm2              :\t" << sparm2              << endl;
    cout << "sparm3              :\t" << sparm3              << endl;
    cout << "sf_flip             :\t" << sf_flip             << endl;
    cout << "fake_sys_unc        :\t" << fake_sys_unc        << endl;
    cout << "flip_sys_unc        :\t" << flip_sys_unc        << endl;
    cout << "mc_sys_unc          :\t" << mc_sys_unc          << endl;
    cout << "lumi                :\t" << lumi                << endl;
    cout << "charge_option       :\t" << charge_option       << endl;
    cout << "exclusive           :\t" << exclusive           << endl;
    cout << "min_ht              :\t" << min_ht              << endl;
    cout << "verbose             :\t" << verbose             << endl;

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
            cout << "[ss2012_plots] Error: input file or sample not found -- specify one or the other" << endl; 
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
        is_signal = (at::GetSampleInfo(sample).type == at::SampleType::susy);
        if (input_file.empty())
        {
            const string short_name = ati.short_name.c_str();
            input_file = Form("babies/%s/%s.root", (is_signal ? "signal" : short_name.c_str()), sample_name.c_str());
            switch (sample)
            {
                case at::Sample::ttdil: input_file = Form("babies/%s/ttjets.root", short_name.c_str()); break; 
                case at::Sample::ttotr: input_file = Form("babies/%s/ttjets.root", short_name.c_str()); break;
                case at::Sample::ttslb: input_file = Form("babies/%s/ttjets.root", short_name.c_str()); break;
                case at::Sample::ttslo: input_file = Form("babies/%s/ttjets.root", short_name.c_str()); break;
                default: {/*do nothing*/}
            }
            if (verbose) {cout << "input file is " << input_file << endl;}
            {cout << "input file is " << input_file << endl;}
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
            do_3lep_veto,
            do_truth_matching,
            sparm0,
            sparm1,
            sparm2,
            sparm3,
            sf_flip,
            fake_sys_unc,
            flip_sys_unc,
            mc_sys_unc,
            lumi,
            min_ht,
            verbose
        ),
        samesignbtag,
        number_of_events,
        good_run_list,
        is_data,
        verbose
    );

    delete chain;

    // done 
    return 0;
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
