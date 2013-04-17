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
    std::string fake_rate_file_name = "data/fake_rates/ssFR_data_ewkcor_17Apr2013.root";
    std::string flip_rate_file_name = "data/flip_rates/ssFL_data_standard_02222013.root";
    std::string den_hist_file_name  = "";
    std::string sample_name         = "";
    std::string analysis_type_name  = "high_pt";
    std::string sr_string           = "-1";
    bool exclusive                  = true;
    bool do_scale_factors           = true;
    bool do_beff_sf                 = true;
    float sparm0                    = -999999.0;
    float sparm1                    = -999999.0;
    float sparm2                    = -999999.0;
    float sparm3                    = -999999.0;
    float sf_flip                   = 1.39;
    float fake_sys_unc              = 0.5;
    float flip_sys_unc              = 0.3;
    float mc_sys_unc                = 0.5;
    float lumi                      = 1.0;
    bool verbose                    = false;
    int run                         = -1;
    int ls                          = -1;
    int event                       = -1;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"      , "print this menu")
        ("input"     , po::value<std::string>(&input_file)->required() , "REQUIRED: name of input root file"                                             )
        ("sample"    , po::value<std::string>(&sample_name)->required(), "REQUIRED: name of input sample (from at/Sample.h)"                             )
        ("output"    , po::value<std::string>(&output_file)            , "name of output root file"                                                      )
        ("anal_type" , po::value<std::string>(&analysis_type_name)     , "name of analysis type (from AnalysisType.h)"                                   )
        ("fr_file"   , po::value<std::string>(&fake_rate_file_name)    , Form("fake rate file name (default: %s)", fake_rate_file_name.c_str())          )
        ("fl_file"   , po::value<std::string>(&flip_rate_file_name)    , Form("flip rate file name (default: %s)", flip_rate_file_name.c_str())          )
        ("den_file"  , po::value<std::string>(&den_hist_file_name)     , Form("den count file name (default: %s)", input_file.c_str())                   )
        ("sr"        , po::value<std::string>(&sr_string)              , "comma seperated list of SRs to run on (any < 0 means all -- default)"          )
        ("nev"       , po::value<long>(&number_of_events)              , "number of events to run on (-1 == all)"                                        )
        ("do_sf"     , po::value<bool>(&do_scale_factors)              , "use the MC scale factors (default is true)"                                    )
        ("do_beff_sf", po::value<bool>(&do_beff_sf)                    , "do the btag efficiency reweight (MC only -- default is true)"                  )
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
        ("run"       , po::value<int>(&run)                            , "select a specific run (negative numbers == all)"                               )
        ("ls"        , po::value<int>(&ls)                             , "select a specific ls (negative numbers == all)"                                )
        ("event"     , po::value<int>(&event)                          , "select a specific event (negative numbers == all)"                             )
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
    cout << "fake_rate_file_name :\t" << fake_rate_file_name << endl;
    cout << "flip_rate_file_name :\t" << flip_rate_file_name << endl;
    cout << "den_hist_file_name  :\t" << den_hist_file_name  << endl;
    cout << "number_of_events    :\t" << number_of_events    << endl;
    cout << "sr                  :\t" << sr_string           << endl;
    cout << "do_scale_factors    :\t" << do_scale_factors    << endl;
    cout << "do_beff_sf          :\t" << do_beff_sf          << endl;
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
    cout << "run                 :\t" << run                 << endl;
    cout << "ls                  :\t" << ls                  << endl;
    cout << "event               :\t" << event               << endl;

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

    // parse the signal region string
    std::vector<std::string> sr_strings = rt::string_split(sr_string);
    std::vector<unsigned int> sr_nums;
    for (size_t i = 0; i != sr_strings.size(); i++)
    {
        int sr_num_raw = boost::lexical_cast<int>(sr_strings.at(i));
        // any < 0 numbers means run on all
        if (sr_num_raw < 0)
        {
            sr_nums.clear();
            const unsigned int values[] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,
                                           10, 11, 12, 13, 14, 15, 16, 17, 18,
                                           20, 21, 22, 23, 24, 25, 26, 27, 28};
            sr_nums.assign(values, values+27);
            break;
        }
        sr_nums.push_back(sr_num_raw);
    }
    cout << "[ss2012_interp_hists] running in SR(s): ";
    for (size_t i = 0; i != sr_nums.size(); i++)
    {
        if (sr_nums.at(i) != sr_nums.back()) {cout << sr_nums.at(i) << ", ";}
        else                                 {cout << sr_nums.at(i) << endl;}
    }

    // do the main analysis
    // -------------------------------------------------------------------------------------------------//

    // analysis type
    const ss::AnalysisType::value_type analysis_type = ss::GetAnalysisTypeFromName(analysis_type_name); 
    const ss::AnalysisTypeInfo ati                   = ss::GetAnalysisTypeInfo(analysis_type); 

    // yield type
    //const at::YieldType::value_type yield_type = at::GetYieldType(yield_type_raw);

    // signal region and type
    const SignalRegionType::value_type signal_region_type = (exclusive ? SignalRegionType::exclusive : SignalRegionType::inclusive);

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
            sr_nums,
            analysis_type,
            signal_region_type,
            fake_rate_file_name,
            flip_rate_file_name,
            den_hist_file_name,
            do_scale_factors,
            do_beff_sf,
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
        verbose,
        run,
        ls,
        event
    );

    // done 
    return 0;
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
