// C++ includes
#include <iostream>
#include <string>
#include <stdexcept>

// ROOT includes
#include "TString.h"

// CMSSW includes
// #include "FWCore/FWLite/interface/AutoLibraryLoader.h" // needed for FWLite if you want to run edm files
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/PythonParameterSet/interface/MakeParameterSets.h"

// ------------------------------------------------------------------------------------ //
// The main program 
// ------------------------------------------------------------------------------------ //

int main(int argc, char **argv)
try
{
    using namespace std;

    // needed for FWLite if you want to run edm files
//     gSystem->Load("libFWCoreFWLite");
//     AutoLibraryLoader::enable();

    // parse the inputs
    // -------------------------------------------------------------------------------------------------//

    // check that the python is passed
    if (argc < 2)
    {
        throw std::invalid_argument(Form("Usage : %s [parameters.py]", argv[0]));
    }

    // check that pset contains "process" 
    const std::string pset_filename = argv[1];
    if (!edm::readPSetsFrom(argv[1])->existsAs<edm::ParameterSet>("process"))
    {
        throw std::invalid_argument(Form("[python_cfg_example] Error: ParametersSet 'process' is missing in your configuration file"));
    }

    // get the python configuration
    const edm::ParameterSet& process = edm::readPSetsFrom(pset_filename)->getParameter<edm::ParameterSet>("process");
    const edm::ParameterSet& pset    = process.getParameter<edm::ParameterSet>("pset");

    // get the inputs 
    const long long max_events                     = pset.getParameter<long long>                  ("max_events"    ) ;
    const bool verbose                             = pset.getParameter<bool>                       ("verbose"       ) ;
    const std::string analysis_path                = pset.getParameter<std::string>                ("analysis_path" ) ;
    const std::string output_label                 = pset.getParameter<std::string>                ("output_label"  ) ;
    const std::string sample_name                  = pset.getParameter<std::string>                ("sample_name"   ) ;
    const double lumi                              = pset.getParameter<double>                     ("lumi"          ) ;
    const double mass_stop                         = pset.getParameter<double>                     ("mass_stop"     ) ;
    const double mass_lsp                          = pset.getParameter<double>                     ("mass_lsp"      ) ;
    const std::vector<unsigned int> search_regions = pset.getParameter<std::vector<unsigned int> > ("search_regions") ;

    // print out the parameters 
    // -------------------------------------------------------------------------------------------------//

    cout << "\n[python_cfg_example] running with the following inputs:" << endl;
    printf("%-25s = %lld\n"  , "max_events"   , max_events           ); 
    printf("%-25s = %1.1f\n" , "lumi"         , lumi                 ); 
    printf("%-25s = %s\n"    , "sample_name"  , sample_name.c_str()  ); 
    printf("%-25s = %s\n"    , "output_label" , output_label.c_str() ); 
    printf("%-25s = %d\n"    , "verbose"      , verbose              ); 
    printf("%-25s = %1.0f\n" , "mass_stop"    , mass_stop            ); 
    printf("%-25s = %1.0f\n" , "mass_lsp"     , mass_lsp             ); 

    // print the search regions
    printf("%-25s = ", "SR(s)");
    for (size_t i = 0; i != search_regions.size(); i++)
    {
        if (search_regions.at(i) != search_regions.back()) {cout << search_regions.at(i) << ", ";}
        else                                               {cout << search_regions.at(i) << endl;}
    }

    // do stuff 
    // -------------------------------------------------------------------------------------------------//

    //...

    // done
    // -------------------------------------------------------------------------------------------------//

    return 0;
}
catch (std::exception& e)
{
    std::cerr << "[stop_interp_plots] Error: failed..." << std::endl;
    std::cerr << e.what() << std::endl;
    return 1;
}

