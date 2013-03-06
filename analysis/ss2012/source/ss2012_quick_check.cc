// quick check of the isolation variables for SS
#include "TChain.h"
#include "TH1F.h"
#include "rt/RootTools.h"
#include "at/Sample.h"
#include "at/ScanChain.h"
#include "at/AnalysisWithHist.h"
#include "at/Predicates.h"
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
		int operator() (long event);
		void BookHists();
		virtual void EndJob();
};

QuickAnalysis::QuickAnalysis(const std::string& file_name)
	: AnalysisWithHist(file_name, true, "png")
{
	BookHists();
}

void QuickAnalysis::EndJob()
{
}

void QuickAnalysis::BookHists()
{
	TH1Container& hc = m_hist_container;
	hc.Add(new TH1F("h_m3lep"    , "m_{3l};m_{3l}"           , 200, 0, 200));
	hc.Add(new TH1F("h_m3lep_rej", "m_{3l} (rejected);m_{3l}", 200, 0, 200));
	hc.Add(new TH1F("h_m3lep_acc", "m_{3l} (accepted);m_{3l}", 200, 0, 200));

    hc.Add(new TH1F("h_pt_max_peak1_acc", "max pt in 81 < m_{3l} < 89; max p_{T} (GeV)", 60, 0, 300));
    hc.Add(new TH1F("h_m01_peak1_acc"   , "m01 81 < m_{3l} < 89; m_{01} (GeV)"         , 50, 0, 100));
    hc.Add(new TH1F("h_m02_peak1_acc"   , "m02 81 < m_{3l} < 89; m_{02} (GeV)"         , 50, 0, 100));
    hc.Add(new TH1F("h_m12_peak1_acc"   , "m13 81 < m_{3l} < 89; m_{12} (GeV)"         , 50, 0, 100));
    hc.Add(new TH1F("h_pt_max_peak1_rej", "max pt in 81 < m_{3l} < 89; max p_{T} (GeV)", 60, 0, 300));
    hc.Add(new TH1F("h_m01_peak1_rej"   , "m01 81 < m_{3l} < 89; m_{01} (GeV)"         , 50, 0, 100));
    hc.Add(new TH1F("h_m02_peak1_rej"   , "m02 81 < m_{3l} < 89; m_{02} (GeV)"         , 50, 0, 100));
    hc.Add(new TH1F("h_m12_peak1_rej"   , "m13 81 < m_{3l} < 89; m_{12} (GeV)"         , 50, 0, 100));

    hc.Add(new TH1F("h_pt_max_peak2_acc", "max pt in 68 < m_{3l} < 76; max p_{T} (GeV)", 60, 0, 300));
    hc.Add(new TH1F("h_m01_peak2_acc"   , "m01 68 < m_{3l} < 76; m_{01} (GeV)"         , 50, 0, 100));
    hc.Add(new TH1F("h_m02_peak2_acc"   , "m02 68 < m_{3l} < 76; m_{02} (GeV)"         , 50, 0, 100));
    hc.Add(new TH1F("h_m12_peak2_acc"   , "m13 68 < m_{3l} < 76; m_{12} (GeV)"         , 50, 0, 100));
    hc.Add(new TH1F("h_pt_max_peak2_rej", "max pt in 68 < m_{3l} < 76; max p_{T} (GeV)", 60, 0, 300));
    hc.Add(new TH1F("h_m01_peak2_rej"   , "m01 68 < m_{3l} < 76; m_{01} (GeV)"         , 50, 0, 100));
    hc.Add(new TH1F("h_m02_peak2_rej"   , "m02 68 < m_{3l} < 76; m_{02} (GeV)"         , 50, 0, 100));
    hc.Add(new TH1F("h_m12_peak2_rej"   , "m13 68 < m_{3l} < 76; m_{12} (GeV)"         , 50, 0, 100));
}

int QuickAnalysis::operator() (long event)
{
	rt::TH1Container& hc = m_hist_container;

    using namespace tas;

	try
	{
        vector<LorentzVector> l_p4;
        for (size_t i = 0; i != genps_p4().size(); i++)
        {
            const unsigned int id = abs(genps_id().at(i));
            if (genps_status().at(i) != 3) {continue;}

            if (id == 11)
            {
                l_p4.push_back(genps_p4().at(i));
            }
            if (id == 13)
            {
                l_p4.push_back(genps_p4().at(i));
            }
        }

        // sort by pt
        std::sort(l_p4.begin(), l_p4.end(), at::SortByPt<LorentzVector>());

        // must have 3 generater level leptons
        if (l_p4.size() < 3) 
        {
            return 0;
        }

        const float m_3l = (l_p4[0] + l_p4[1] + l_p4[2]).mass();
        rt::Fill(hc["h_m3lep"], m_3l);

        const float pt_max = l_p4.at(0).pt();
        const float m01    = (l_p4[0] + l_p4[1]).mass();
        const float m02    = (l_p4[0] + l_p4[2]).mass();
        const float m12    = (l_p4[1] + l_p4[2]).mass();

        const bool pt_max_cut = (100.0 < pt_max && pt_max < 160.0);
        const bool m01_cut    = (62.0 < m01 && m01 < 72.0);
        const bool m02_cut    = (52.0 < m02 && m02 < 55.0);
        const bool m12_cut    = (7.2 < m12 && m12 < 8.2);
        const bool rejected   = (pt_max_cut && m01_cut && m02_cut && m12_cut);

        const bool peak1 = (85 < m_3l && m_3l < 83);
        const bool peak2 = (72 < m_3l && m_3l < 78);
        if (rejected)
        {
            rt::Fill(hc["h_m3lep_rej"], m_3l);
            if (peak1)
            {
                rt::Fill(hc["h_pt_max_peak1_rej"], pt_max);
                rt::Fill(hc["h_m01_peak1_rej"   ], m01   );
                rt::Fill(hc["h_m02_peak1_rej"   ], m02   );
                rt::Fill(hc["h_m12_peak1_rej"   ], m12   );
            }
            if (peak2)
            {
                rt::Fill(hc["h_pt_max_peak2_rej"], pt_max);
                rt::Fill(hc["h_m01_peak2_rej"   ], m01   );
                rt::Fill(hc["h_m02_peak2_rej"   ], m02   );
                rt::Fill(hc["h_m12_peak2_rej"   ], m12   );
            }
        }
        else
        {
            rt::Fill(hc["h_m3lep_acc"], m_3l);
            if (peak1)
            {
                rt::Fill(hc["h_pt_max_peak1_acc"], pt_max);
                rt::Fill(hc["h_m01_peak1_acc"   ], m01   );
                rt::Fill(hc["h_m02_peak1_acc"   ], m02   );
                rt::Fill(hc["h_m12_peak1_acc"   ], m12   );
            }
            if (peak2)
            {
                rt::Fill(hc["h_pt_max_peak2_acc"], pt_max);
                rt::Fill(hc["h_m01_peak2_acc"   ], m01   );
                rt::Fill(hc["h_m02_peak2_acc"   ], m02   );
                rt::Fill(hc["h_m12_peak2_acc"   ], m12   );
            }
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

	ScanChain(&chain, QuickAnalysis(output_file), cms2, number_of_events, "", true, false);
	return 0;
}
catch (std::exception& e)
{
    cerr << "[ss2012_anlaysis] Error: failed..." << endl;
    cerr << e.what() << endl;
    return 1;
}

