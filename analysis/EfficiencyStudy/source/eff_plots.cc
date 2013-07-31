#include <iostream>
#include <string>
#include "TChain.h"
#include "PlotLooper.h"
#include "ESBWrapper.h"
#include "at/Sample.h"
#include "at/ScanChain.h"
#include "rt/RootTools.h"
#include <boost/program_options.hpp>

int main(int argc, char* argv[])
try
{
    // set the style
    rt::SetStyle("emruoi");

    using namespace std;

    // inputs
    // -------------------------------------------------------------------------------------------------//

    long number_of_events           = -1;
    std::string input_file          = "";
    std::string output_file         = "";
    std::string pdf_hist_file_name  = "plots/dy/pdf.root";
    std::string suffix              = "";
    std::string vtxreweight_file    = "";
    std::string sample_name         = "";
	float iso_cut                   = 0.1;
	bool derive_pdf					= false;
    bool verbose                    = false;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"     , "print this menu")
        ("nev"      , po::value<long>(&number_of_events)          , "number of events to run on (-1 == all)"               )
        ("output"   , po::value<std::string>(&output_file)        , "name of output root file (optional)"                  )
        ("input"    , po::value<std::string>(&input_file)         , "name of input root file (optional)"                   )
        ("sample"   , po::value<std::string>(&sample_name)        , "name of input sample (from at/Sample.h)"              )
        ("pdf_file" , po::value<std::string>(&pdf_hist_file_name) , "file name containing the pdf histogram"               )
        ("suffix"   , po::value<std::string>(&suffix)             , "suffix to print (png, eps, pdf, all).  empty for none")
        ("iso_cut"  , po::value<float>(&iso_cut)                  , "iso cut to use (default = 0.1)"                       )
        ("do_pdf"   , po::value<bool>(&derive_pdf)                , "derive the pdf histogram only and quit"               )
        ("verbose"  , po::value<bool>(&verbose)                   , "verbosity"                                            )
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

    // do the main analysis
    // -------------------------------------------------------------------------------------------------//
    
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
            input_file = Form("babies/%s.root", sample_name.c_str());
        }
        if (output_file.empty())
        {
            output_file = "plots/test.root";
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
            pdf_hist_file_name,
			iso_cut,
			derive_pdf,
            verbose
        ),
        eff_study_baby,
        number_of_events,
        /*good_run_list=*/"",
        (sample == at::Sample::data),
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
