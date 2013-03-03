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
	: AnalysisWithHist(file_name)
{
	BookHists();
}

void QuickAnalysis::EndJob()
{
	//TH1Container& hc = m_hist_container;
    //hc.Print("plots/
}

void QuickAnalysis::BookHists()
{
	TH1Container& hc = m_hist_container;
	hc.Add(new TH1F("h_m3lep"    , "m_{3l};m_{3l}"      , 200, 0, 200));
	hc.Add(new TH1F("h_m3lep_fix", "m_{3l} (fix);m_{3l}", 200, 0, 200));
}

//// relax the 0 hit cut on the electron ID 
//static const cuts_t electronSelection_ssV7_noIso_relaxmhit = //(electronSelection_ssV7_noIso & ~(1ll<<ELENOTCONV_HITPATTERN_0MHITS));
//                       electronSelectionFO_SS_baselineV2    |
//                       (1ll<<ELEID_WP2012_MEDIUM_NOISO)     |
//                       //(0ll<<ELENOTCONV_HITPATTERN_0MHITS)  |
//                       (1ll<<ELE_NOT_TRANSITION)            |
//                       (1ll<<ELECHARGE_NOTFLIP3AGREE);
//
//bool isGoodLeptonRelaxHitCut(int idx)
//{
//	// electrons
//	if (!pass_electronSelection(idx, electronSelection_ssV7_noIso_relaxmhit, false, false))
//		return false;
//	if ((cms2.els_fiduciality().at(idx) & (1<<ISEB)) == (1<<ISEB))
//		return (cms2.els_hOverE().at(idx) < 0.10);
//	else
//		return (cms2.els_hOverE().at(idx) < 0.075);
//}


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
        if (100.0 < pt_max && pt_max < 160.0) {return 0;}

        const float m_01 = (l_p4[0] + l_p4[1]).mass();
        if (62.0 < m_01 && m_01 < 72.0) {return 0;}

        const float m_02 = (l_p4[0] + l_p4[2]).mass();
        if (52.0 < m_02 && m_02 < 55.0) {return 0;}

        const float m_12 = (l_p4[1] + l_p4[2]).mass();
        if (7.2 < m_12 && m_12 < 8.2) {return 0;}

        rt::Fill(hc["h_m3lep_fix"], m_3l);

        //cout << "evt_ww_rho_vor(): " << evt_ww_rho_vor() << endl;

		//// electron loop
		//for (size_t idx = 0; idx != els_p4().size(); idx++)
		//{
		//	const LorentzVector& el_p4 = els_p4().at(idx);	

		//	// pt > 20 && |eta| < 2.4
		//	if (el_p4.pt() < 20.0 || fabs(el_p4.eta()) > 2.4)
		//	{
		//		continue;
		//	}

        //    float iso_orig = electronIsoValuePF2012_FastJetEffArea(idx);
        //    float iso_fix  = electronIsoValuePF2012_FastJetEffArea_v2(idx);

		//	// if passes ID with no missing hits relaxed
		//	//if (isGoodLepton1MHitCut(idx) && not samesign::isGoodLepton(11, idx))
		//	if (isGoodLeptonRelaxHitCut(idx) && els_exp_innerlayers().at(idx) >= 1)
        //    {
        //        rt::Fill(hc["h_iso_nomhitcut_orig"], iso_orig);
        //        rt::Fill(hc["h_iso_nomhitcut_fix" ], iso_fix );
        //        rt::Fill(hc["h_iso_nomhitcut_diff"], iso_orig - iso_fix);
        //    }

		//	// if passes full ID 
		//	if (samesign::isGoodLepton(11, idx))
        //    {
        //        rt::Fill(hc["h_iso_fullid_orig"], iso_orig);
        //        rt::Fill(hc["h_iso_fullid_fix" ], iso_fix );
        //        rt::Fill(hc["h_iso_fullid_diff"], iso_orig - iso_fix);
        //    }
		//}
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

