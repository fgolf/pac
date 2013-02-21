#include <iostream>
#include <string>
#include "TChain.h"
#include "InterpLooper.h"
#include "SSB2012Wrapper.h"
#include "at/ScanChain.h"
#include "at/Sample.h"
#include "at/YieldType.h"
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
    std::string fake_rate_file_name = "data/fake_rates/ssFR_data_ewkcor_13Feb2013.root";
    std::string flip_rate_file_name = "data/flip_rates/ssFL_data_standard_02182013.root";
    std::string sample_name         = "";
    std::string analysis_type_name  = "high_pt";
    std::string good_run_list       = "";
    bool exclusive                  = true;
    bool do_scale_factors           = true;
    float sparm0                    = -999999.0;
    float sparm1                    = -999999.0;
    float sparm2                    = -999999.0;
    float sparm3                    = -999999.0;
    float sf_flip                   = 0.84;
    float fake_sys_unc              = 0.5;
    float flip_sys_unc              = 0.2;
    float mc_sys_unc                = 0.5;
    unsigned int signal_region_num  = 0;
    int yield_type_raw              = 0;
    float lumi                      = 1.0;
    bool verbose                    = false;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"      , "print this menu")
        ("nev"       , po::value<long>(&number_of_events)          , "number of events to run on (-1 == all)"                     )
        ("output"    , po::value<std::string>(&output_file)        , "name of output root file"                                   )
        ("input"     , po::value<std::string>(&input_file)         , "name of input root file"                                    )
        ("sample"    , po::value<std::string>(&sample_name)        , "name of input sample (from at/Sample.h)"                    )
        ("anal_type" , po::value<std::string>(&analysis_type_name) , "name of analysis type (from AnalysisType.h)"                )
        ("fr_file"   , po::value<std::string>(&fake_rate_file_name), "fake rate file name"                                        )
        ("fl_file"   , po::value<std::string>(&flip_rate_file_name), "flip rate file name"                                        )
        ("run_list"  , po::value<std::string>(&good_run_list)      , "Good Run list (no default)"                                 )
        ("sr"        , po::value<unsigned int>(&signal_region_num) , "signal region number (default is 0)"                        )
        ("do_sf"     , po::value<bool>(&do_scale_factors)          , "use the MC scale factors (default is true)"                 )
        ("sparm0"    , po::value<float>(&sparm0)                   , "sparm0 value is required"                                   )
        ("sparm1"    , po::value<float>(&sparm1)                   , "sparm1 value is required"                                   )
        ("sparm2"    , po::value<float>(&sparm2)                   , "sparm2 value is required"                                   )
        ("sparm3"    , po::value<float>(&sparm3)                   , "sparm3 value is required"                                   )
        ("sf_flip"   , po::value<float>(&sf_flip)                  , "scale factor for flips (default is 0.84)"                   )
        ("fr_unc"    , po::value<float>(&fake_sys_unc)             , "systematic uncertainty for fake prediction (default is 0.5)")
        ("fl_unc"    , po::value<float>(&flip_sys_unc)             , "systematic uncertainty for flip prediction (default is 0.2)")
        ("mc_unc"    , po::value<float>(&mc_sys_unc)               , "systematic uncertainty for MC prediction (default is 0.5)"  )
        ("lumi"      , po::value<float>(&lumi)                     , "luminosity"                                                 )
        ("excl"      , po::value<bool>(&exclusive)                 , "use exclusive signal region"                                )
        ("yield_type", po::value<int>(&yield_type_raw)             , "yield type (0 == base, > 0 == up, < 0 == down)"             )
        ("verbose"   , po::value<bool>(&verbose)                   , "verbosity"                                                  )
        ;

    po::variables_map vm;
    try
    {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
        if (vm.count("help")) {
            cout << desc << "\n";
            return 1;
        }
    }
    catch(const std::exception& e)
    {
        cerr << e.what() << "\nexiting" << endl;
        return 1;
    }


    // check that input file exists and is specified
    if (!input_file.empty())
    { 
        if (!rt::exists(input_file))
        {
            cout << "[ss2012_interp_hists] ERROR: input file " << input_file << " not found" << endl;
            cout << desc << "\n";
            return 1;
        }
    }

    // do the main analysis
    // -------------------------------------------------------------------------------------------------//

    // analysis type
    const ss::AnalysisType::value_type analysis_type = ss::GetAnalysisTypeFromName(analysis_type_name); 
    const ss::AnalysisTypeInfo ati                   = ss::GetAnalysisTypeInfo(analysis_type); 

    // yield type
    const at::YieldType::value_type yield_type = at::GetYieldType(yield_type_raw);

    // signal region and type
    const SignalRegionType::value_type signal_region_type = (exclusive ? SignalRegionType::exclusive : SignalRegionType::inclusive);
    const std::string signal_region_type_name             = GetSignalRegionTypeName(signal_region_type);
    const string signal_region_name                       = Form("sr%d", signal_region_num);
    const SignalRegion::value_type signal_region          = GetSignalRegionFromName(signal_region_name, ati.name, signal_region_type_name);

    // input
    TChain* chain  = NULL;
    at::Sample::value_type sample = at::Sample::static_size;
    bool is_data = false; 
    if (sample_name.empty())  // use input file
    {
        if (input_file.empty())
        {
            cout << "[ss2012_interp_hists] ERROR: input file or sample not found -- specify one or the other" << endl; 
            cout << desc << "\n";
            return 1;
        }
        else
        {
            chain = new TChain("tree");
            chain->Add(input_file.c_str());
            if (output_file.empty())
            {
                output_file = "plots/interp/test.root";
            }
        }
    }
    else // use the sample
    {
        cout << "processing "  << sample_name << endl;
        sample  = at::GetSampleFromName(sample_name);
        is_data = at::SampleIsData(sample);
        if (input_file.empty())
        {
            const string short_name = ati.short_name.c_str();
            input_file = Form("babies/%s/%s.root", short_name.c_str(), sample_name.c_str());
        }
        if (output_file.empty())
        {
            //const char* sr = GetSignalRegionInfo(signal_region, analysis_type, signal_region_type).name.c_str();
            output_file = Form("plots/interp/%s.root", sample_name.c_str());
        }
        chain = new TChain("tree");
        chain->Add(input_file.c_str());
        cout << "running on input: " << input_file << endl;
    }

    // scan the chain
    ScanChain
    (
        chain,
        InterpLooper
        (
            output_file,       
            sample,
            signal_region,
            analysis_type,
            signal_region_type,
            yield_type,
            fake_rate_file_name,
            flip_rate_file_name,
            do_scale_factors,
            sparm0,
            sparm1,
            sparm2,
            sparm3,
            sf_flip,
            fake_sys_unc,
            flip_sys_unc,
            mc_sys_unc,
            lumi,
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
