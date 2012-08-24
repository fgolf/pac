#include <iostream>
#include <string>
#include "TChain.h"
#include "FakeRateScanChain.h"
#include "FakeRateStudy.h"
#include "Sample.h"
#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>
#include "rt/RootTools.h"

bool ValidCharge(int charge)
{
    switch(charge)
    {
        case 1: 
        case -1:
        case 0:
            return true;
            break;
        default:
            return false;
    }
    return false;
}

bool ValidLeptonName(const std::string& channel)
{
    if (channel == "mu")
        return true;
//    if (channel == "el")
//        return true;
    return false;
}

int main(int argc, char* argv[])
try
{
    // set the style
    rt::SetStyle("emruoi");

    using namespace std;

    // inputs
    // -------------------------------------------------------------------------------------------------//

    long number_of_events        = -1;
    std::string root_file_name   = "";
    std::string sample_name      = "data";
    std::string channel          = "mu";
    std::string suffix           = "";
    std::string vtxreweight_file = "";
    //float away_jet_cut           = 40.0;
    short charge                 = 0;
    float lumi                   = 1.0;
    bool verbose                 = false;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"          , "print this menu")
        ("nev"           , po::value<long>(&number_of_events)        , "number of events to run on (-1 == all)"              )
        ("lumi"          , po::value<float>(&lumi)                   , "luminosity (default is 1.0 fb)"                      )
        ("sample"        , po::value<std::string>(&sample_name)      , "name of dataset (valid options: \"data\", \"qcd\")"  )
        ("channel"       , po::value<std::string>(&channel)          , "name of channel (valid options: \"mu\", \"el\")"     )
        //("jet_cut"       , po::value<float>(&away_jet_cut)           , "away jet cut (default 40 GeV)"                       )
        ("charge"        , po::value<short>(&charge)                 , "-1: +ve, -1: -ve, 0: both"                           )
        ("root_file_name", po::value<std::string>(&root_file_name)   , "name of output root file"                            )
        ("vtx_file"      , po::value<std::string>(&vtxreweight_file) , "ROOT file for the vertex reweight (ignored for data)")
        ("suffix"        , po::value<std::string>(&suffix)           , "suffix to pring (png, eps, pdf).  empty for nonf"    )
        ("verbose"       , po::value<bool>(&verbose)                 , "verbosity"                                           )
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

    // check that the channel option is one of the supported
    if (!ValidLeptonName(channel))
    {
        cout << "ERROR: FakeRateStudy: invalid channel option" << endl;
        cout << desc << "\n";
        return 1;
    }

    // check that the charge option is one of the supported
    if (!ValidCharge(charge))
    {
        cout << "ERROR: FakeRateStudy: invalid charge option" << endl;
        cout << desc << "\n";
        return 1;
    }

    // check that vertex reweight file exists
    if (!vtxreweight_file.empty())
    { 
        if (!rt::exists(vtxreweight_file))
        {
            cout << "ERROR: FakeRateStudy: vertex reweight file " << vtxreweight_file << " not found" << endl;
            cout << desc << "\n";
            return 1;
        }
    }

    // do the main analysis
    // -------------------------------------------------------------------------------------------------//
    
    // sample info
    fr::Sample::value_type sample = fr::GetSampleFromName(sample_name);
    bool is_data = false; //(fr::GetSampleInfo(sample).type == fr::SampleType::data);

    // directories
    //std::string analysis_path = rt::getenv("PWD");
    //root_file_name = rt::string_contains(root_file_name, ".root") ? rt::string_remove_all(root_file_name, ".root") : root_file_name;
	//std::string root_base_name = rt::basename(root_file_name);
    //std::string full_output_path = Form("%s/plots/%s/%s/%s.root", analysis_path.c_str(), root_base_name.c_str(), dataset.c_str(), root_file_name.c_str()); 
    std::string full_output_path = root_file_name.empty() ? fr::GetSampleInfo(sample).output_file : root_file_name;  
    cout << "output file: " << full_output_path << endl;

    // data
    boost::shared_ptr<TChain> chain(fr::GetSampleTChain(sample));

    // scan the chain
    FakeRateScanChain
    (
        /*input chain ptr =*/chain.get(),
        FakeRateStudy
        (
            full_output_path,       
            sample,
            channel,
            vtxreweight_file,
            lumi,
            //away_jet_cut,
            charge,
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
