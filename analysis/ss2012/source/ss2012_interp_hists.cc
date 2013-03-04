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
    std::string fake_rate_file_name = "data/fake_rates/ssFR_data_ewkcor_26Feb2013.root";
    std::string flip_rate_file_name = "data/flip_rates/ssFL_data_standard_02222013.root";
    std::string den_hist_file_name  = "";
    std::string sample_name         = "";
    std::string analysis_type_name  = "high_pt";
    bool exclusive                  = true;
    bool do_scale_factors           = true;
    float sparm0                    = -999999.0;
    float sparm1                    = -999999.0;
    float sparm2                    = -999999.0;
    float sparm3                    = -999999.0;
    float sf_flip                   = 1.39;
    float fake_sys_unc              = 0.5;
    float flip_sys_unc              = 0.3;
    float mc_sys_unc                = 0.5;
    unsigned int signal_region_num  = 0;
    int yield_type_raw              = 0;
    float lumi                      = 1.0;
    bool verbose                    = false;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"      , "print this menu")
        ("input"     , po::value<std::string>(&input_file)->required() , "REQUIRED: name of input root file"                                             )
        ("sample"    , po::value<std::string>(&sample_name)->required(), "REQUIRED: name of input sample (from at/Sample.h)"                             )
        ("output"    , po::value<std::string>(&output_file)            , "name of output root file"                                                      )
        ("anal_type" , po::value<std::string>(&analysis_type_name)     , "name of analysis type (from AnalysisType.h)"                                   )
        ("yield_type", po::value<int>(&yield_type_raw)                 , "yield type (0 == base (default), > 0 == up, < 0 == down)"                      )
        ("fr_file"   , po::value<std::string>(&fake_rate_file_name)    , Form("fake rate file name (default: %s)", fake_rate_file_name.c_str())          )
        ("fl_file"   , po::value<std::string>(&flip_rate_file_name)    , Form("flip rate file name (default: %s)", flip_rate_file_name.c_str())          )
        ("den_file"  , po::value<std::string>(&den_hist_file_name)     , Form("den count file name (default: %s)", input_file.c_str())                   )
        ("nev"       , po::value<long>(&number_of_events)              , "number of events to run on (-1 == all)"                                        )
        ("sr"        , po::value<unsigned int>(&signal_region_num)     , "signal region number (default is 0)"                                           )
        ("do_sf"     , po::value<bool>(&do_scale_factors)              , "use the MC scale factors (default is true)"                                    )
        ("sparm0"    , po::value<float>(&sparm0)                       , "sparm0 is required to be this value"                                           )
        ("sparm1"    , po::value<float>(&sparm1)                       , "sparm1 is required to be this value"                                           )
        ("sparm2"    , po::value<float>(&sparm2)                       , "sparm2 is required to be this value"                                           )
        ("sparm3"    , po::value<float>(&sparm3)                       , "sparm3 is required to be this value"                                           )
        ("sf_flip"   , po::value<float>(&sf_flip)                      , Form("scale factor for flips (default is %f)", sf_flip)                         )
        ("fr_unc"    , po::value<float>(&fake_sys_unc)                 , Form("systematic uncertainty for fake prediction (default is %f)", fake_sys_unc))
        ("fl_unc"    , po::value<float>(&flip_sys_unc)                 , Form("systematic uncertainty for flip prediction (default is %f)", fake_sys_unc))
        ("mc_unc"    , po::value<float>(&mc_sys_unc)                   , Form("systematic uncertainty for MC prediction (default is %f)", fake_sys_unc)  )
        ("lumi"      , po::value<float>(&lumi)                         , "luminosity"                                                                    )
        ("excl"      , po::value<bool>(&exclusive)                     , "use exclusive signal region"                                                   )
        ("verbose"   , po::value<bool>(&verbose)                       , "verbosity"                                                                     )
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
    
    // default is to use den hist in the baby file (h_gen_count)
    if (den_hist_file_name.empty())
    {
        den_hist_file_name = input_file;
    }

    cout << "inputs:" << endl;
    cout << "input_file          :\t" << input_file          << endl;
    cout << "sample_name         :\t" << sample_name         << endl;
    cout << "output_file         :\t" << output_file         << endl;
    cout << "analysis_type_name  :\t" << analysis_type_name  << endl;
    cout << "yield_type_raw      :\t" << yield_type_raw      << endl;
    cout << "fake_rate_file_name :\t" << fake_rate_file_name << endl;
    cout << "flip_rate_file_name :\t" << flip_rate_file_name << endl;
    cout << "den_hist_file_name  :\t" << den_hist_file_name  << endl;
    cout << "number_of_events    :\t" << number_of_events    << endl;
    cout << "signal_region_num   :\t" << signal_region_num   << endl;
    cout << "do_scale_factors    :\t" << do_scale_factors    << endl;
    cout << "sparm0              :\t" << sparm0              << endl;
    cout << "sparm1              :\t" << sparm1              << endl;
    cout << "sparm2              :\t" << sparm2              << endl;
    cout << "sparm3              :\t" << sparm3              << endl;
    cout << "sf_flip             :\t" << sf_flip             << endl;
    cout << "fake_sys_unc        :\t" << fake_sys_unc        << endl;
    cout << "flip_sys_unc        :\t" << flip_sys_unc        << endl;
    cout << "mc_sys_unc          :\t" << mc_sys_unc          << endl;
    cout << "lumi                :\t" << lumi                << endl;
    cout << "exclusive           :\t" << exclusive           << endl;
    cout << "verbose             :\t" << verbose             << endl;

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

    // sample
    at::Sample::value_type sample = at::GetSampleFromName(sample_name);
    const bool is_data = (at::GetSampleInfo(sample).type == at::SampleType::data);

    // input chain
    TChain chain("tree");
    chain.Add(input_file.c_str());

    // output
    if (output_file.empty())
    {
        output_file = Form("plots/interp/%s.root", sample_name.c_str());
    }

    cout << "processing "  << sample_name << endl;
    cout << "running on input: " << input_file << endl;

    // scan the chain
    ScanChain
    (
        &chain,
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
            den_hist_file_name,
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
        /*good run list =*/"",
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
