// make the Tag & Probe plots 

// c++
#include <stdexcept>
#include <iostream>
#include <tr1/array>

// ROOT
#include "TChain.h"
#include "TH1F.h"
#include "Math/LorentzVector.h"

// BOOST
#include <boost/program_options.hpp>

// Tools
#include "rt/RootTools.h"
#include "at/Sample.h"
#include "at/ScanChain.h"
#include "at/AnalysisWithHist.h"
#include "at/Predicates.h"
#include "at/DorkyEventIdentifier.h"
#include "EFFWrapper.h"

using namespace at;
using namespace std;
using namespace rt;
using namespace eff;

class LeptonEffPlotsLooper : public AnalysisWithHist
{
	public:
		LeptonEffPlotsLooper
        (
            const std::string& file_name, 
            const bool verbose
        ); 
		int operator() (long event);
		void BookHists();
		virtual void EndJob();
    private:
        const bool m_verbose;
};

LeptonEffPlotsLooper::LeptonEffPlotsLooper
(
    const std::string& file_name, 
    const bool verbose
)
	: AnalysisWithHist(file_name, true, "png")
    , m_verbose(verbose)
{
	BookHists();
}

void LeptonEffPlotsLooper::EndJob()
{
	TH1Container& hc = m_hist_container;

    // electrons
    hc.Add(rt::MakeEfficiencyPlot(hc["h_el_id_vs_nvtxs"  ] , hc["h_el_den_vs_nvtxs"] , "h_el_eff_id_vs_nvtxs"   , "Electron Efficiency ID;# vertices;Efficiency"      ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_el_iso_vs_nvtxs" ] , hc["h_el_den_vs_nvtxs"] , "h_el_eff_iso_vs_nvtxs"  , "Electron Efficiency Iso;# vertices;Efficiency"     ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_el_both_vs_nvtxs"] , hc["h_el_den_vs_nvtxs"] , "h_el_eff_both_vs_nvtxs" , "Electron Efficiency ID + Iso;# vertices;Efficiency"));

    hc.Add(rt::MakeEfficiencyPlot(hc["h_el_id_vs_pt"  ] , hc["h_el_den_vs_pt"] , "h_el_eff_id_vs_pt"   , "Electron Efficiency ID;electron p_{T} (GeV);Efficiency"       ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_el_iso_vs_pt" ] , hc["h_el_den_vs_pt"] , "h_el_eff_iso_vs_pt"  , "Electron Efficiency Iso;electron p_{T} (GeV);Efficiency"     ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_el_both_vs_pt"] , hc["h_el_den_vs_pt"] , "h_el_eff_both_vs_pt" , "Electron Efficiency ID + Iso;electron p_{T} (GeV);Efficiency"));

    hc.Add(rt::MakeEfficiencyPlot(hc["h_el_id_vs_eta"  ] , hc["h_el_den_vs_eta"] , "h_el_eff_id_vs_eta"   , "Electron Efficiency ID;electron #eta;Efficiency"      ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_el_iso_vs_eta" ] , hc["h_el_den_vs_eta"] , "h_el_eff_iso_vs_eta"  , "Electron Efficiency Iso;electron #eta;Efficiency"     ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_el_both_vs_eta"] , hc["h_el_den_vs_eta"] , "h_el_eff_both_vs_eta" , "Electron Efficiency ID + Iso;electron #eta;Efficiency"));

    // muons 
    hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_id_vs_nvtxs"  ] , hc["h_mu_den_vs_nvtxs"] , "h_mu_eff_id_vs_nvtxs"   , "Muon Efficiency ID;# vertices;Efficiency"      ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_iso_vs_nvtxs" ] , hc["h_mu_den_vs_nvtxs"] , "h_mu_eff_iso_vs_nvtxs"  , "Muon Efficiency Iso;# vertices;Efficiency"     ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_both_vs_nvtxs"] , hc["h_mu_den_vs_nvtxs"] , "h_mu_eff_both_vs_nvtxs" , "Muon Efficiency ID + Iso;# vertices;Efficiency"));

    hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_id_vs_pt"  ] , hc["h_mu_den_vs_pt"] , "h_mu_eff_id_vs_pt"   , "Muon Efficiency ID;muon p_{T} (GeV);Efficiency"      ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_iso_vs_pt" ] , hc["h_mu_den_vs_pt"] , "h_mu_eff_iso_vs_pt"  , "Muon Efficiency Iso;muon p_{T} (GeV);Efficiency"     ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_both_vs_pt"] , hc["h_mu_den_vs_pt"] , "h_mu_eff_both_vs_pt" , "Muon Efficiency ID + Iso;muon p_{T} (GeV);Efficiency"));

    hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_id_vs_eta"  ] , hc["h_mu_den_vs_eta"] , "h_mu_eff_id_vs_eta"   , "Muon Efficiency ID;muon #eta;Efficiency"      ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_iso_vs_eta" ] , hc["h_mu_den_vs_eta"] , "h_mu_eff_iso_vs_eta"  , "Muon Efficiency Iso;muon #eta;Efficiency"     ));
    hc.Add(rt::MakeEfficiencyPlot(hc["h_mu_both_vs_eta"] , hc["h_mu_den_vs_eta"] , "h_mu_eff_both_vs_eta" , "Muon Efficiency ID + Iso;muon #eta;Efficiency"));
}

// electron binning
const std::tr1::array<float, 11> el_pt_bins  = {{10, 15, 20, 40, 60, 80, 100, 120, 160, 180, 200}};
const std::tr1::array<float, 11> el_eta_bins = {{-2.4, -2.0, -1.566, -1.4442, -0.8, 0, 0.8, 1.4442, 1.566, 2.0, 2.4}};

// mu binning
// const std::tr1::array<float, 8> mu_pt_bins  = {{10, 15, 20, 30, 40, 50, 100, 200}};
const std::tr1::array<float, 11> mu_pt_bins  = {{10, 15, 20, 40, 60, 80, 100, 120, 160, 180, 200}};
const std::tr1::array<float,  9> mu_eta_bins = {{-2.4, -2.0, -1.5, -0.8, 0, 0.8, 1.5, 2.0, 2.4}};

// # vertex binning
const size_t vtx_nbins = 40; const float vtx_bins_min = 0; const float vtx_bins_max = 40; 

void LeptonEffPlotsLooper::BookHists()
{
	TH1Container& hc = m_hist_container;

    // electrons
    hc.Add(new TH1F("h_el_den_vs_nvtxs"  , "Electron MC Matched to Reco Only;# of vertices;A.U." , vtx_nbins , vtx_bins_min , vtx_bins_max));
    hc.Add(new TH1F("h_el_id_vs_nvtxs"   , "Electron Passes ID;# of vertices;A.U."               , vtx_nbins , vtx_bins_min , vtx_bins_max));
    hc.Add(new TH1F("h_el_iso_vs_nvtxs"  , "Electron Passes Iso;# of vertices;A.U."              , vtx_nbins , vtx_bins_min , vtx_bins_max));
    hc.Add(new TH1F("h_el_both_vs_nvtxs" , "Electron Passes ID and Iso;# of vertices;A.U."       , vtx_nbins , vtx_bins_min , vtx_bins_max));

    hc.Add(new TH1F("h_el_den_vs_pt"  , "Electron MC Matched to Reco Only;electron p_{T} (GeV);A.U." , el_pt_bins.size()-1 , el_pt_bins.data()));
    hc.Add(new TH1F("h_el_id_vs_pt"   , "Electron Passes ID;electron p_{T} (GeV);A.U."               , el_pt_bins.size()-1 , el_pt_bins.data()));
    hc.Add(new TH1F("h_el_iso_vs_pt"  , "Electron Passes Iso;electron p_{T} (GeV);A.U."              , el_pt_bins.size()-1 , el_pt_bins.data()));
    hc.Add(new TH1F("h_el_both_vs_pt" , "Electron Passes ID and Iso;electron p_{T} (GeV);A.U."       , el_pt_bins.size()-1 , el_pt_bins.data()));

    hc.Add(new TH1F("h_el_den_vs_eta"  , "Electron MC Matched to Reco Only;electron #eta;A.U." , el_eta_bins.size()-1 , el_eta_bins.data()));
    hc.Add(new TH1F("h_el_id_vs_eta"   , "Electron Passes ID;electron #eta;A.U."               , el_eta_bins.size()-1 , el_eta_bins.data()));
    hc.Add(new TH1F("h_el_iso_vs_eta"  , "Electron Passes Iso;electron #eta;A.U."              , el_eta_bins.size()-1 , el_eta_bins.data()));
    hc.Add(new TH1F("h_el_both_vs_eta" , "Electron Passes ID and Iso;electron #eta;A.U."       , el_eta_bins.size()-1 , el_eta_bins.data()));
    
    // muons
    hc.Add(new TH1F("h_mu_den_vs_nvtxs"  , "Muon MC Matched to Reco Only;# of vertices;A.U." , vtx_nbins , vtx_bins_min , vtx_bins_max));
    hc.Add(new TH1F("h_mu_id_vs_nvtxs"   , "Muon Passes ID;# of vertices;A.U."               , vtx_nbins , vtx_bins_min , vtx_bins_max));
    hc.Add(new TH1F("h_mu_iso_vs_nvtxs"  , "Muon Passes Iso;# of vertices;A.U."              , vtx_nbins , vtx_bins_min , vtx_bins_max));
    hc.Add(new TH1F("h_mu_both_vs_nvtxs" , "Muon Passes ID and Iso;# of vertices;A.U."       , vtx_nbins , vtx_bins_min , vtx_bins_max));

    hc.Add(new TH1F("h_mu_den_vs_pt"  , "Muon MC Matched to Reco Only;muon p_{T} (GeV);A.U." , mu_pt_bins.size()-1 , mu_pt_bins.data()));
    hc.Add(new TH1F("h_mu_id_vs_pt"   , "Muon Passes ID;muon p_{T} (GeV);A.U."               , mu_pt_bins.size()-1 , mu_pt_bins.data()));
    hc.Add(new TH1F("h_mu_iso_vs_pt"  , "Muon Passes Iso;muon p_{T} (GeV);A.U."              , mu_pt_bins.size()-1 , mu_pt_bins.data()));
    hc.Add(new TH1F("h_mu_both_vs_pt" , "Muon Passes ID and Iso;muon p_{T} (GeV);A.U."       , mu_pt_bins.size()-1 , mu_pt_bins.data()));

    hc.Add(new TH1F("h_mu_den_vs_eta"  , "Muon MC Matched to Reco Only;muon #eta;A.U." , mu_eta_bins.size()-1 , mu_eta_bins.data()));
    hc.Add(new TH1F("h_mu_id_vs_eta"   , "Muon Passes ID;muon #eta;A.U."               , mu_eta_bins.size()-1 , mu_eta_bins.data()));
    hc.Add(new TH1F("h_mu_iso_vs_eta"  , "Muon Passes Iso;muon #eta;A.U."              , mu_eta_bins.size()-1 , mu_eta_bins.data()));
    hc.Add(new TH1F("h_mu_both_vs_eta" , "Muon Passes ID and Iso;muon #eta;A.U."       , mu_eta_bins.size()-1 , mu_eta_bins.data()));
    
    // style
    hc.SetMarkerStyle(20);
    hc.SetMarkerSize(1.0);
    hc.Sumw2();
}

int LeptonEffPlotsLooper::operator() (long event)
{
	rt::TH1Container& hc = m_hist_container;

    using namespace eff;

	try
    {
        // check kinematics 
        const float lep_pt   = p4().pt();
        const float lep_eta  = p4().eta();
        const float lep_aeta = fabs(p4().eta());
        const bool lep_den   = lep_pt>10.0 && lep_aeta<2.4;
        if (not (lep_den))
        {
            return 0;
        }

        // selections
        const bool lep_is_mu      = abs(pdgid())==13;
        const bool lep_is_el      = abs(pdgid())==11;
        const bool lep_passes_id  = passes_id();
        const bool lep_passes_iso = passes_iso();
        const bool lep_passes_ss  = lep_passes_id && lep_passes_iso;

        // electrons
        if (lep_is_el)
        {
            // no crack electrons
            if (1.4442 < lep_aeta && lep_aeta < 1.566) 
            {
                return 0;
            }

            // denominator
            rt::Fill(hc["h_el_den_vs_nvtxs"], nvtxs());
            rt::Fill(hc["h_el_den_vs_pt"   ], lep_pt);
            rt::Fill(hc["h_el_den_vs_eta"  ], lep_eta);

            // id 
            if (lep_passes_id)
            {
                rt::Fill(hc["h_el_id_vs_nvtxs"], nvtxs());
                rt::Fill(hc["h_el_id_vs_pt"   ], lep_pt );
                rt::Fill(hc["h_el_id_vs_eta"  ], lep_eta);
            }

            // iso 
            if (lep_passes_iso)
            {
                rt::Fill(hc["h_el_iso_vs_nvtxs"], nvtxs());
                rt::Fill(hc["h_el_iso_vs_pt"   ], lep_pt );
                rt::Fill(hc["h_el_iso_vs_eta"  ], lep_eta);
            }

            // id and iso
            if (lep_passes_ss)
            {
                rt::Fill(hc["h_el_both_vs_nvtxs"], nvtxs());
                rt::Fill(hc["h_el_both_vs_pt"   ], lep_pt );
                rt::Fill(hc["h_el_both_vs_eta"  ], lep_eta);
            }
        }

        // muons
        if (lep_is_mu)
        {
            // denominator
            rt::Fill(hc["h_mu_den_vs_nvtxs"], nvtxs());
            rt::Fill(hc["h_mu_den_vs_pt"   ], lep_pt  );
            rt::Fill(hc["h_mu_den_vs_eta"  ], lep_eta );

            // id 
            if (lep_passes_id)
            {
                rt::Fill(hc["h_mu_id_vs_nvtxs"], nvtxs());
                rt::Fill(hc["h_mu_id_vs_pt"   ], lep_pt );
                rt::Fill(hc["h_mu_id_vs_eta"  ], lep_eta);
            }

            // iso 
            if (lep_passes_iso)
            {
                rt::Fill(hc["h_mu_iso_vs_nvtxs"], nvtxs());
                rt::Fill(hc["h_mu_iso_vs_pt"   ], lep_pt );
                rt::Fill(hc["h_mu_iso_vs_eta"  ], lep_eta);
            }

            // id and iso
            if (lep_passes_ss)
            {
                rt::Fill(hc["h_mu_both_vs_nvtxs"], nvtxs());
                rt::Fill(hc["h_mu_both_vs_pt"   ], lep_pt );
                rt::Fill(hc["h_mu_both_vs_eta"  ], lep_eta);
            }
        }

        // done
        return 0;
    }
    catch (std::exception& e)
    {
        cout << Form("[lepton_eff_plots] Fatal error on run %d, ls %d, event %d", eff::run(), eff::ls(), eff::evt()) << endl;
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
    std::string output_file = "";
    std::string input_file  = "";
    int number_of_events    = -1;
    int run                 = -1;
    int lumi                = -1;
    int event               = -1;
    bool verbose            = false;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"     , "print this menu")
        ("input"    , po::value<std::string>(&input_file)->required(), "REQUIRED: input ntuple (default is determined by the sample used)")
        ("output"   , po::value<std::string>(&output_file)           , "output ROOT file for baby tree (default: plots/test/test.root)"   )
        ("nev"      , po::value<int>(&number_of_events)              , "number of events to run on (-1 == all)"                           )
        ("verbose"  , po::value<bool>(&verbose)                      , "verbose print out"                                                )
        ("run"      , po::value<int>(&run)                           , "select a specific run (negative numbers == all)"                  )
        ("lumi"     , po::value<int>(&lumi)                          , "select a specific lumi (negative numbers == all)"                 )
        ("event"    , po::value<int>(&event)                         , "select a specific event (negative numbers == all)"                )
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
    cout << "output_file      :\t" << output_file      << endl; 
    cout << "input_file       :\t" << input_file       << endl; 
    cout << "number_of_events :\t" << number_of_events << endl; 
    cout << "run              :\t" << run              << endl;
    cout << "lumi             :\t" << lumi             << endl;
    cout << "event            :\t" << event            << endl;
    cout << "verbose          :\t" << verbose          << endl; 

    // do it
    // ------------------------------------------------------------------ //

    // output file
    if (output_file.empty())
    {
        output_file = "plots/test_plots/test.root";
    }

	TChain chain("tree");
    chain.Add(input_file.c_str());
	rt::PrintFilesFromTChain(chain);

    // analysis looper
	ScanChain
    (
        &chain, 
        LeptonEffPlotsLooper
        (
            output_file, 
            verbose
        ),
        eff_obj, 
        number_of_events,
        /*run_list=*/"",
        /*is_data=*/false,
        verbose,
        run,
        lumi,
        event
    );

    // done
	return 0;
}
catch (std::exception& e)
{
    cerr << "[lepton_eff_plots] Error: failed..." << endl;
    cerr << e.what() << endl;
    return 1;
}

