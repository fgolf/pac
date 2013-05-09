// quick check of the isolation variables for SS
#include "TChain.h"
#include "TH1F.h"
#include "rt/RootTools.h"
#include "at/Sample.h"
#include "at/ScanChain.h"
#include "at/AnalysisWithHist.h"
#include "at/Predicates.h"
#include "at/Status3EventIdentifier.h"
#include <stdexcept>
#include "CMS2Wrapper.h"
#include "ssSelections.h"
#include "electronSelections.h"

// BOOST
#include <boost/program_options.hpp>

using namespace at;
using namespace std;
using namespace rt;
using namespace tas;

class QuickAnalysis : public AnalysisWithHist
{
	public:
		QuickAnalysis(const std::string& file_name); 
		int operator() (long event, const std::string& file_name);
		void BookHists();
		virtual void EndJob();
};

QuickAnalysis::QuickAnalysis(const std::string& file_name)
	: AnalysisWithHist(file_name, true, "eps")
{
	BookHists();
}

void QuickAnalysis::EndJob()
{
}

void QuickAnalysis::BookHists()
{
	TH1Container& hc = m_hist_container;
	hc.Add(new TH1F("h_mu_pt", "p_{T}", 100, 0, 200));
}

int QuickAnalysis::operator() (long event, const std::string& filename)
{
	rt::TH1Container& hc = m_hist_container;

	try
	{
        for (size_t i = 0; i != mus_p4().size(); i++)
        {
            hc["h_mu_pt"]->Fill(mus_p4().at(i).pt());
        }
	}
    catch (std::exception& e)
    {
        cout << Form("Fatal error on run %d, ls %d, event %d", evt_run(), evt_lumiBlock(), evt_event()) << endl;
        cout << e.what() << endl;
        cout << "Exiting..." << endl;
        exit(1);
    }

    // done
    return 0;
}

int main(int argc, char* argv[])
try
{
    std::string output_file         = "";
    std::string input_file          = "";
    int number_of_events            = -1;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"  , "print this menu")
        ("output", po::value<std::string>(&output_file)->required(), "REQUIRED: output ROOT file for baby tree (default: <sample name>.root)")
        ("input" , po::value<std::string>(&input_file)->required() , "REQUIRED: input ntuple (default is determined by the sample used)"     )
        ("nev"   , po::value<int>(&number_of_events)               , "number of events to run on (-1 == all)"                                )
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

    cout << "inputs:" << endl;
    cout << "number_of_events   :\t" << number_of_events    << endl;
    cout << "input_file         :\t" << input_file          << endl;
    cout << "output_file        :\t" << output_file         << endl;

    // do it

	TChain chain("Events");
    chain.Add(input_file.c_str());
	rt::PrintFilesFromTChain(chain);

	ScanChainWithFilename(&chain, QuickAnalysis(output_file), cms2, number_of_events, /*run_list=*/"", true, false);
	return 0;
}
catch (std::exception& e)
{
    cerr << "[ss2012_anlaysis] Error: failed..." << endl;
    cerr << e.what() << endl;
    return 1;
}

