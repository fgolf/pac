#include <iostream>
#include <string>
#include "TChain.h"
#include "at/ScanChain.h"
#include "FakeRateBabyWrapper.h"
#include "FakeRateBabyLooper.h"
#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>
#include "rt/RootTools.h"

bool ValidDatasetName(const std::string& dataset)
{
    if (dataset == "data")
        return true;
    if (dataset == "data2012Cv2")
        return true;
    if (dataset == "data2012ABr")
        return true;
    if (dataset == "data2012ABv1")
        return true;
    if (dataset == "ttbar12")
        return true;
    return false;
}

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
    if (channel == "el")
        return true;
//    if (channel == "both")
//        return true;
    return false;
}

// Factor function to gererate the datastets
boost::shared_ptr<TChain> TChainFactory(const std::string& dataset = "qcd", const std::string& channel = "mu")
{    
    // check that the dataset is one of the supported
    if (!ValidDatasetName(dataset))
    {
        throw std::runtime_error("ERROR: need valid option (\"data\", \"data2012Cv2\")");
    }

    // prefix name
    bool local = rt::string_contains(rt::getenv("HOSTNAME"), "tensor");
    
    boost::shared_ptr<TChain> chain(new TChain("tree"));

     
    // full 12.26 /fb of 2012AB reprocessed and 2012C
    if (dataset == "data")
    {
        //const std::string& ntuple_path = local ? rt::getenv("HOME") + "/Data/babies/fr/FakeRate20May2012v2/" : "/nfs-7/userdata/rwkelley/babies/fr/FakeRate20May2012v2/";     // 920 /pb
        //const std::string& ntuple_path = local ? rt::getenv("HOME") + "/Data/babies/fr/FakeRate20May2012_11p38fb/" : "/nfs-7/userdata/rwkelley/babies/fr/FakeRate20May2012_11p38fb/";     // 10.45 /fb
        const std::string& ntuple_path = local ? rt::getenv("HOME") + "/Data/babies/fr/FakeRate20May2012_12p26fb/" : "/nfs-7/userdata/rwkelley/babies/fr/FakeRate20May2012_12p26fb/";     // 12.26 /fb
        if (channel=="mu")
        {
            // don't have all of these yet
			chain->Add(Form("%s/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root" , ntuple_path.c_str()));
			chain->Add(Form("%s/DoubleMu_Run2012A-13Jul2012-v1_AOD/*.root"         , ntuple_path.c_str()));
			chain->Add(Form("%s/DoubleMu_Run2012B-13Jul2012-v4_AOD/*.root"         , ntuple_path.c_str()));
			chain->Add(Form("%s/SingleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root" , ntuple_path.c_str()));
			chain->Add(Form("%s/SingleMu_Run2012A-13Jul2012-v1_AOD/*.root"         , ntuple_path.c_str()));
			chain->Add(Form("%s/SingleMu_Run2012B-13Jul2012-v1_AOD/*.root"         , ntuple_path.c_str()));
			chain->Add(Form("%s/DoubleMu_Run2012C-24Aug2012-v1_AOD/*.root"         , ntuple_path.c_str()));
			chain->Add(Form("%s/DoubleMu_Run2012C-PromptReco-v2_AOD/*.root"        , ntuple_path.c_str()));
			chain->Add(Form("%s/SingleMu_Run2012C-24Aug2012-v1_AOD/*.root"         , ntuple_path.c_str()));
			chain->Add(Form("%s/SingleMu_Run2012C-PromptReco-v2_AOD/*.root"        , ntuple_path.c_str()));
        }
        else if (channel=="el")
        {
            chain->Add(Form("%s/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/*.root", ntuple_path.c_str())); 
            chain->Add(Form("%s/DoubleElectron_Run2012A-13Jul2012-v1_AOD/*.root"        , ntuple_path.c_str())); 
            chain->Add(Form("%s/DoubleElectron_Run2012B-13Jul2012-v1_AOD/*.root"        , ntuple_path.c_str())); 
            chain->Add(Form("%s/DoubleElectron_Run2012C-24Aug2012-v1_AOD/*.root"        , ntuple_path.c_str())); 
            chain->Add(Form("%s/DoubleElectron_Run2012C-PromptReco-v2_AOD/*.root"       , ntuple_path.c_str())); 
			
        }
    }    
    // 2012 AB prompt v1
    if (dataset == "data2012ABv1")
    {
        //const std::string& ntuple_path = local ? rt::getenv("HOME") + "/Data/babies/fr/FakeRate20May2012v2/" : "/nfs-7/userdata/rwkelley/babies/fr/FakeRate20May2012v2/";             // 920 /pb from AN
        //const std::string& ntuple_path = local ? rt::getenv("HOME") + "/Data/babies/fr/FakeRate20May2012_3p95fb/"  : "/nfs-7/userdata/rwkelley/babies/fr/FakeRate20May2012_3p95fb/";  // 3.95 /fb 
        const std::string& ntuple_path = local ? rt::getenv("HOME") + "/Data/babies/fr/FakeRate20May2012_5p098ifb/": "/nfs-7/userdata/rwkelley/babies/fr/FakeRate20May2012_5p098ifb/";  // 5.1 /fb (full 2012AB)
        if (channel=="mu")
        {
            chain->Add(Form("%s/SingleMu_Run2012A-PromptReco-v1_AOD/*.root", ntuple_path.c_str())); 
            chain->Add(Form("%s/SingleMu_Run2012B-PromptReco-v1_AOD/*.root", ntuple_path.c_str())); 
            chain->Add(Form("%s/DoubleMu_Run2012A-PromptReco-v1_AOD/*.root", ntuple_path.c_str())); 
            chain->Add(Form("%s/DoubleMu_Run2012B-PromptReco-v1_AOD/*.root", ntuple_path.c_str())); 
        }
        else if (channel=="el")
        {
            chain->Add(Form("%s/DoubleElectron_Run2012A-PromptReco-v1_AOD/*.root", ntuple_path.c_str())); 
            chain->Add(Form("%s/DoubleElectron_Run2012B-PromptReco-v1_AOD/*.root", ntuple_path.c_str())); 
        }
    }    
    // 2012C prompt v2
    else if (dataset == "data2012Cv2")
    {
        const std::string& ntuple_path = local ? rt::getenv("HOME") + "/Data/babies/fr/FakeRate20May2012_2012Cv2/" : "/nfs-7/userdata/rwkelley/babies/fr/FakeRate20May2012_2012Cv2";
        if (channel=="mu")
        {
            chain->Add(Form("%s/SingleMu_Run2012C-PromptReco-v2_AOD/*.root", ntuple_path.c_str())); 
            chain->Add(Form("%s/DoubleMu_Run2012C-PromptReco-v2_AOD/*.root", ntuple_path.c_str())); 
        }
        else if (channel=="el")
        {
            chain->Add(Form("%s/DoubleElectron_Run2012C-PromptReco-v2_AOD/*.root", ntuple_path.c_str())); 
        }
    }    
    // 2012A/B rereco 13Jul2012 and 06Aug2012 recovery
    else if (dataset == "data2012ABr")
    {
        const std::string& ntuple_path = local ? rt::getenv("HOME") + "/Data/babies/fr/FakeRate20May2012_submit2/" : "/nfs-7/userdata/rwkelley/babies/fr/FakeRate20May2012_submit2";
        if (channel=="mu")
        {
        	const std::string& ntuple_path = local ? rt::getenv("HOME") + "/Data/babies/fr/FakeRate20May2012_submit2/" : "/nfs-7/userdata/rwkelley/babies/fr/FakeRate20May2012_submit2/";  
            chain->Add(Form("%s/DoubleMu_Run2012A-13Jul2012-v1_AOD/*.root", ntuple_path.c_str())); 
            chain->Add(Form("%s/DoubleMu_Run2012B-13Jul2012-v1_AOD/*.root", ntuple_path.c_str())); 
            chain->Add(Form("%s/SingleMu_Run2012A-13Jul2012-v1_AOD/*.root", ntuple_path.c_str())); 
            chain->Add(Form("%s/SingleMu_Run2012B-13Jul2012-v1_AOD/*.root", ntuple_path.c_str())); 
			chain->Add(Form("%s/DoubleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root" , ntuple_path.c_str()));
			chain->Add(Form("%s/SingleMu_Run2012A-recover-06Aug2012-v1_AOD/*.root" , ntuple_path.c_str()));
        }
        else if (channel=="el")
        {
            chain->Add(Form("%s/DoubleElectron_Run2012A-recover-06Aug2012-v1_AOD/*.root", ntuple_path.c_str())); 
            chain->Add(Form("%s/DoubleElectron_Run2012A-13Jul2012-v1_AOD/*.root", ntuple_path.c_str())); 
            chain->Add(Form("%s/DoubleElectron_Run2012B-13Jul2012-v1_AOD/*.root", ntuple_path.c_str())); 
        }
    }    
    else if (dataset == "ttbar12")
    {
        const std::string& ntuple_path = local ? rt::getenv("HOME") + "/Data/babies/fr/FakeRate20May2012_mc/" : "/nfs-7/userdata/rwkelley/babies/fr/FakeRate20May2012_mc";
        chain->Add(Form("%s/TTJets_TuneZ2star_8TeV-madgraph-tauola_Summer12-PU_S7_START52_V9-v1/*.root", ntuple_path.c_str())); 
    }    

    return chain;
}

int main(int argc, char* argv[])
try
{
    // set the style
    rt::SetStyle("emruoi");

    using namespace std;

    // inputs
    // -------------------------------------------------------------------------------------------------//

    long number_of_events          = -1;
    std::string dataset            = "data";
    std::string root_file_name     = "test.root";
    std::string channel            = "mu";
    std::string suffix             = "";
    std::string good_run_list      = "";
    bool verbose                   = false;
	float lumi					   = 1.0;
    int charge                     = 0;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"          , "print this menu")
        ("nev"           , po::value<long>(&number_of_events)      , "number of events to run on (-1 == all)"           )
        ("lumi"          , po::value<float>(&lumi)                 , "luminosity (default is 1.0 fb)"                   )
        ("dataset"       , po::value<std::string>(&dataset)        , "name of dataset"                                  )
        ("channel"       , po::value<std::string>(&channel)        , "name of channel (valid options: \"mu\", \"el\")"  )
        ("root_file_name", po::value<std::string>(&root_file_name) , "name of output root file"                         )
        ("run_list"      , po::value<std::string>(&good_run_list)  , "good run list"                                    )
        ("suffix"        , po::value<std::string>(&suffix)         , "suffix to pring (png, eps, pdf).  empty for nonf" )
        ("charge"        , po::value<int>(&charge)                 , "-1: +ve, -1: -ve, 0: both"                        )
        ("verbose"       , po::value<bool>(&verbose)               , "verbosity"                                        )
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
        cout << "ERROR: invalid channel option" << endl;
        cout << desc << "\n";
        return 1;
    }

    // check that the dataset option is one of the supported
    if (!ValidDatasetName(dataset))
    {
        cout << "ERROR: invalid dataset option" << endl;
        cout << desc << "\n";
        return 1;
    }

    // check that the charge option is one of the supported
    if (!ValidCharge(charge))
    {
        cout << "ERROR: invalid charge option" << endl;
        cout << desc << "\n";
        return 1;
    }

    // do the main analysis
    // -------------------------------------------------------------------------------------------------//

    // directories
    std::string analysis_path = rt::getenv("SS");
    root_file_name = rt::string_contains(root_file_name, ".root") ? rt::string_remove_all(root_file_name, ".root") : root_file_name;
	std::string root_base_name = rt::basename(root_file_name);
    std::string full_output_path = Form("%s/plots/fake_rates/%s/%s.root", analysis_path.c_str(), root_base_name.c_str(), root_file_name.c_str()); 
    cout << "output file: " << full_output_path << endl;

    // data
    boost::shared_ptr<TChain> chain = TChainFactory(dataset, channel);

    // scan the chain
    at::ScanChain<FakeRateBaby>
    (
        /*input chain ptr =*/chain.get(), 
        FakeRateBabyLooper(full_output_path, dataset, channel, lumi, charge, verbose, !suffix.empty(), suffix), 
        fake_rate_baby,
        number_of_events,
        good_run_list,
        /*fast=*/true,
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
