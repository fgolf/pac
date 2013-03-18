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
#include "Measurement.h"
#include "rt/RootTools.h"
#include "at/Sample.h"
#include "at/ScanChain.h"
#include "at/AnalysisWithHist.h"
#include "at/Predicates.h"
#include "at/DorkyEventIdentifier.h"
#include "LeptonTreeWrapper.h"
#include "LeptonSelections.h"
#include "Constants.h"

using namespace at;
using namespace std;
using namespace rt;
using namespace lt;

class LeptonTreeLooper : public AnalysisWithHist
{
	public:
		LeptonTreeLooper
        (
            const std::string& file_name, 
            const tp::Mode::value_type mode,
            const tp::Selection::value_type numerator,
            const tp::Selection::value_type denominator,
            const float fit_mass_low,
            const float fit_mass_high,
            const bool verbose
        ); 
		int operator() (long event);
		void BookHists();
		virtual void EndJob();
    private:
        tp::Mode::value_type m_mode;
        tp::Selection::value_type m_num;
        tp::Selection::value_type m_den;
        const float m_mlow;
        const float m_mhigh;
        TH1D* h_pu;
        const bool m_verbose;
        int m_duplicates;
};

LeptonTreeLooper::LeptonTreeLooper
(
    const std::string& file_name, 
    const tp::Mode::value_type mode,
    const tp::Selection::value_type numerator,
    const tp::Selection::value_type denominator,
    const float fit_mass_low,
    const float fit_mass_high,
    const bool verbose
)
	: AnalysisWithHist(file_name, true, "png")
    , m_mode(mode)
    , m_num(numerator)
    , m_den(denominator)
    , m_mlow(fit_mass_low)
    , m_mhigh(fit_mass_high)
    , h_pu(rt::GetHistFromRootFile<TH1D>("data/puWeights_Summer12_53x_Observed.root", "puWeights"))
    , m_verbose(verbose)
    , m_duplicates(0)
{
	BookHists();
}

void LeptonTreeLooper::EndJob()
{
    // print the duplicates
    if (m_duplicates > 0)
    {
        cout << "[tap_make_plots] found " << m_duplicates << " duplicate events" << endl;
    }
}

//const std::tr1::array<float, 6> pt_bins  = {{10, 20, 30, 50, 100, 7000}};
//const std::tr1::array<float, 2> eta_bins = {{0, 1.4442}};
//const size_t npt_bins  = 5; const float pt_bins [] = {10, 20, 30, 50, 100, 7000};
//const size_t neta_bins = 1; const float eta_bins[] = {0, 1.4442};

// egamma binning
const size_t npt_bins  = 6; const float pt_bins [] = {10, 15, 20, 30, 40, 50, 200};
const size_t neta_bins = 5; const float eta_bins[] = {0, 0.8, 1.4442, 1.566, 2.0, 2.5};

// mu binning
//const size_t npt_bins  = 6; const float pt_bins [] = {10, 15, 20, 30, 40, 50, 200};
//const size_t neta_bins = 2; const float eta_bins[] = {0, 1.2, 2.5};

void LeptonTreeLooper::BookHists()
{
	TH1Container& hc = m_hist_container;

    // mass bins
    const int nmass_bins = static_cast<int>(fabs(m_mhigh - m_mlow)/tp::MassBinWidth);

    // book pt hists 
    for (size_t ptbin = 0; ptbin != npt_bins; ptbin++)
    {
        for (size_t etabin = 0; etabin != neta_bins; etabin++)
        {
            const std::string bin_title = Form("%1.0f GeV < p_{T} < %1.0f GeV, %1.2f < |#eta| < %1.2f", pt_bins[ptbin], pt_bins[ptbin+1], eta_bins[etabin], eta_bins[etabin+1]);

            hc.Add(new TH1F(Form("h_pass_pt%lu_eta%lu", ptbin, etabin), Form("Passing probes (%s); tag & probe mass (GeV); Events / %1.1f (GeV)", bin_title.c_str(), tp::MassBinWidth), nmass_bins, m_mlow, m_mhigh));
            hc.Add(new TH1F(Form("h_fail_pt%lu_eta%lu", ptbin, etabin), Form("Failing probes (%s); tag & probe mass (GeV); Events / %1.1f (GeV)", bin_title.c_str(), tp::MassBinWidth), nmass_bins, m_mlow, m_mhigh));
        }
    }

    // sumw2
    hc.SetMarkerStyle(20);
    hc.SetMarkerSize(1.0);
    hc.Sumw2();
}

int LeptonTreeLooper::operator() (long event)
{
	rt::TH1Container& hc = m_hist_container;

    using namespace tp;

	try
    {
        // tag and probe
        // ------------------------------------------------------------------------------------ //
        if (m_verbose) {cout << Form("\nrun %u, ls %u, evt %u", lt::run(), lt::lumi(), lt::event()) << endl;}

        // mode
        const bool is_mu   = (m_mode == tp::Mode::Muon     || m_mode == tp::Mode::MuonMC    );
        const bool is_el   = (m_mode == tp::Mode::Electron || m_mode == tp::Mode::ElectronMC);
        const bool is_mc   = (m_mode == tp::Mode::MuonMC   || m_mode == tp::Mode::ElectronMC);
        const bool is_data = (not is_mc);

        // check for dupiclate run and events
        // no native is_data branch in the tree so I can't handle it at the ScanChain level
        // hmmm, this doesn't work since there are multple lepton pairs per event...
        //if (is_data)
        //{
        //    DorkyEventIdentifier id = {lt::run(), lt::event(), lt::lumi()};
        //    if (is_duplicate(id))
        //    {
        //        if (m_verbose) {cout << "Duplicate event:\t" << lt::run() << ", " << lt::lumi() << ", " << lt::event() << endl;}
        //        m_duplicates++;
        //        return 0;
        //    }
        //}

        // passes the probe denominator 
        if (not tp::PassesSelection(m_mode, m_den))
        {
            if (m_verbose) {cout << "Did not pass the denominator selection" << endl;}
            return 0;
        }

        unsigned int evt_sel = eventSelection();
        // Z/onia --> ee
        if (is_el)
        {
            if (((evt_sel & EventSelection::ZeeTagAndProbe     ) != EventSelection::ZeeTagAndProbe   ) &&
                    ((evt_sel & EventSelection::OniaEETagAndProbe  ) != EventSelection::OniaEETagAndProbe))
            {
                if (m_verbose) {cout << "Did not pass Z/onia --> ee" << endl;}
                return 0;
            }
        }
        // Z/onia --> mm
        if (is_mu)
        {
            if (((evt_sel & EventSelection::ZmmTagAndProbe     ) != EventSelection::ZmmTagAndProbe     ) &&
                    ((evt_sel & EventSelection::OniaMuMuTagAndProbe) != EventSelection::OniaMuMuTagAndProbe))
            {
                if (m_verbose) {cout << "Did not pass Z/onia --> mm" << endl;}
                return 0;
            }
        }
    
        // require OS leptons
        if((qProbe() * qTag()) > 0)
        {
            if (m_verbose) {cout << "Did not pass OS requirement" << endl;}
            return 0;
        }

        // require mass window around the Z
        const float mass = tagAndProbeMass();
        if (not (m_mlow < mass && mass < m_mhigh))
        {
            if (m_verbose) {cout << "Did not pass Z mass requirement" << endl;}
            return 0;
        }

        // MC reqruied DeltaR(reco lepton, status 1 gen level lepton) < 0.2
        if (is_mc && gen_drs1() > 0.2)
        {
            if (m_verbose) {cout << "Did not DeltaR(lep, s1) < 0.2 requirement" << endl;}
            return 0;
        }

        // check pt boundaries
        const float probe_pt = probe().pt();
        const float pt_min   = pt_bins[0];
        const float pt_max   = pt_bins[npt_bins];
        if (not (pt_min < probe_pt &&  probe_pt < pt_max))
        {
            if (m_verbose) {cout << "outside pt bins" << endl;}
            return 0;
        }

        // check eta boundaries
        const float probe_eta = fabs(is_el ? sceta() : probe().eta());
        const float eta_min   = eta_bins[0];
        const float eta_max   = eta_bins[neta_bins];
        if (not (eta_min < probe_eta && probe_eta < eta_max))
        {
            if (m_verbose) {cout << "outside eta bins" << endl;}
            return 0;
        }

        // find pT/eta bin
        unsigned int pt_bin  = find_bin(probe_pt , pt_bins );
        unsigned int eta_bin = find_bin(probe_eta, eta_bins);
        const std::string h_pass_histname = Form("h_pass_pt%u_eta%u", pt_bin, eta_bin);
        const std::string h_fail_histname = Form("h_fail_pt%u_eta%u", pt_bin, eta_bin);

        if (m_verbose) {cout << Form("pt %f, ptbin %u"  , probe_pt , pt_bin ) << endl;}
        if (m_verbose) {cout << Form("eta %f, etabin %u", probe_eta, eta_bin) << endl;}

        const float nvtxs  = nvtx();
        const float weight = (is_mc ? (scale1fb() * h_pu->GetBinContent(nvtxs+1)) : 1.0);

        // passes the probe numerator 
        if (tp::PassesSelection(m_mode, m_num))
        {
            if (m_verbose) {cout << "passes the numerator selection" << endl;}

            // fill hists
            hc[h_pass_histname]->Fill(mass, weight);
        }
        // fails the probe numerator 
        else
        {
            if (m_verbose) {cout << "fails the numerator selection" << endl;}
            
            // fill hists
            hc[h_fail_histname]->Fill(mass, weight);
        }

        // done
        return 0;
    }
    catch (std::exception& e)
    {
        cout << Form("Fatal error on run %d, ls %d, event %d", lt::run(), lt::lumi(), lt::event()) << endl;
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
    std::string mode_name   = "";
    std::string num_name    = "";
    std::string den_name    = "";
    std::string run_list    = "";
    int number_of_events    = -1;
    float fit_mass_low      = 60.0;
    float fit_mass_high     = 120.0;
    int run                 = -1;
    int lumi                = -1;
    int event               = -1;
    bool verbose            = false;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"     , "print this menu")
        ("mode"     , po::value<std::string>(&mode_name)->required(), "REQUIRED: which channel are we analysising (Muon, MuonMC, Electron, ElectronMC)")
        ("num"      , po::value<std::string>(&num_name)->required() , "REQUIRED: numerator selection"                                                  )
        ("den"      , po::value<std::string>(&den_name)->required() , "REQUIRED: denominator selection"                                                )
        ("output"   , po::value<std::string>(&output_file)          , "output ROOT file for baby tree (default: <sample name>.root)"         )
        ("input"    , po::value<std::string>(&input_file)           , "input ntuple (default is determined by the sample used)"              )
        ("run_list" , po::value<std::string>(&run_list)             , "good run list"                                                                  )
        ("fit_mlow" , po::value<float>(&fit_mass_low)               , "mass of the z window for fitting (low side)"                                    )
        ("fit_mhigh", po::value<float>(&fit_mass_high)              , "mass of the z window for fitting (high side)"                                   )
        ("nev"      , po::value<int>(&number_of_events)             , "number of events to run on (-1 == all)"                                         )
        ("verbose"  , po::value<bool>(&verbose)                     , "verbose print out"                                                              )
        ("run"      , po::value<int>(&run)                          , "select a specific run (negative numbers == all)"                                )
        ("lumi"     , po::value<int>(&lumi)                         , "select a specific lumi (negative numbers == all)"                               )
        ("event"    , po::value<int>(&event)                        , "select a specific event (negative numbers == all)"                              )
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
    cout << "mode_name        :\t" << mode_name        << endl; 
    cout << "num_name         :\t" << num_name         << endl; 
    cout << "den_name         :\t" << den_name         << endl; 
    cout << "run_list         :\t" << run_list         << endl; 
    cout << "fit_mass_low     :\t" << fit_mass_low     << endl; 
    cout << "fit_mass_high    :\t" << fit_mass_high    << endl; 
    cout << "number_of_events :\t" << number_of_events << endl; 
    cout << "run              :\t" << run              << endl;
    cout << "lumi             :\t" << lumi             << endl;
    cout << "event            :\t" << event            << endl;
    cout << "verbose          :\t" << verbose          << endl; 

    // do it
    // ------------------------------------------------------------------ //

    // mode
    tp::Mode::value_type mode = tp::GetModeFromString(mode_name);

    // selection
    tp::Selection::value_type numerator   = tp::GetSelectionFromString(num_name);
    tp::Selection::value_type denominator = tp::GetSelectionFromString(den_name);

    // data?
    const bool is_data = (mode == tp::Mode::Electron || mode == tp::Mode::Muon);

    // output file
    if (output_file.empty())
    {
        output_file = Form("plots/%s/%s/raw_plots.root", rt::string_remove_all(den_name, "Den").c_str(), mode_name.c_str());
    }

    // input file
    if (input_file.empty())
    {
        switch(mode)
        {
            case tp::Mode::Muon      : input_file = "/nfs-7/userdata/rwkelley/babies/LeptonTree/V00-02-09/SingleMu/merged_Moriond.root";                                                                                break; 
            case tp::Mode::Electron  : input_file = "/nfs-7/userdata/rwkelley/babies/LeptonTree/V00-02-09/SingleElectron/merged_Moriond.root";                                                                          break; 
            case tp::Mode::MuonMC    : input_file = "/nfs-7/userdata/rwkelley/babies/LeptonTree/V00-02-07/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM/merged_mm.root"; break; 
            case tp::Mode::ElectronMC: input_file = "/nfs-7/userdata/rwkelley/babies/LeptonTree/V00-02-07/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM/merged_ee.root"; break; 
            default: throw std::invalid_argument("[tp_make_plots] no input file given. exiting");
        }
    }
	TChain chain("leptons");
    chain.Add(input_file.c_str());
	rt::PrintFilesFromTChain(chain);

    // analysis looper
	ScanChain
    (
        &chain, 
        LeptonTreeLooper
        (
            output_file, 
            mode, 
            numerator, 
            denominator, 
            fit_mass_low,
            fit_mass_high,
            verbose
        ),
        lepton_tree, 
        number_of_events,
        run_list,
        is_data,
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
    cerr << "[tp_make_plots] Error: failed..." << endl;
    cerr << e.what() << endl;
    return 1;
}

