// c++
#include <iostream>
#include <string>
#include <stdexcept>

// ROOT
#include "TChain.h"
#include "TSystem.h"
#include "Math/LorentzVector.h"

// tools
#include "at/AnalysisWithTree.h"
#include "at/ScanChain.h"
#include "at/Sample.h"
#include "at/Predicates.h"
#include "at/DileptonHypType.h"
#include "SingleLeptonTree.h"
#include "EventInfoTree.h"
#include "rt/RootTools.h"

// analysis
#include "CMS2Wrapper.h"
#include "ssSelections.h"
#include "eventSelections.h"

// BOOST
#include <boost/program_options.hpp>

// typdefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

using namespace std;

// Tree Format 
// -------------------------------------------------------------------------------------------------//
// -------------------------------------------------------------------------------------------------//

// typedefs
typedef std::vector<LorentzVector> vecLorentzVector;
typedef std::vector<float> vecd;
typedef std::vector<int> veci;

struct EfficiencyTree : public SingleLeptonTree
{
    // constructors and destructor
    EfficiencyTree ();
    EfficiencyTree (const std::string &prefix);
    virtual ~EfficiencyTree () {}

    void Reset();
    void SetBranches(TTree& tree);
    void SetAliases(TTree& tree) const;

public:

    // event level info
    EventInfoTree event_info;
};

EfficiencyTree::EfficiencyTree ()
{
}

EfficiencyTree::EfficiencyTree (const std::string &prefix)
    : SingleLeptonTree(prefix)
{
}

void EfficiencyTree::Reset()
{
    event_info.Reset();
    SingleLeptonTree::Reset();
}

void EfficiencyTree::SetBranches(TTree &tree)
{
    event_info.SetBranches(tree);
    SingleLeptonTree::SetBranches(tree);
}


// Basic Looper 
// -------------------------------------------------------------------------------------------------//
// -------------------------------------------------------------------------------------------------//

class EfficiencyBaby : public at::AnalysisWithTree
{
    public:
        // construct:
        EfficiencyBaby
        (
             const std::string& root_file_name,
             const at::Sample::value_type& sample,
             double luminosity = 1.0,
             bool verbose = false
        );

        // destroy:
        ~EfficiencyBaby();

        // function operator:
        int operator() (long event, const std::string& filename);

        // members:
        virtual void BeginJob();
        virtual void EndJob();
        int Analyze(long event, const std::string& filename);

    private:
        // members:
        at::Sample::value_type m_sample;
        double m_lumi;
        bool m_verbose;

        // struct to hold tree values
        EfficiencyTree m_evt;

};

// construct:
EfficiencyBaby::EfficiencyBaby
(
    const std::string& root_file_name,
    const at::Sample::value_type& sample,
    double luminosity,
    bool verbose
)
    : AnalysisWithTree(root_file_name, "tree", "baby tree for efficiency study")
    , m_sample(sample)
    , m_lumi(luminosity)
    , m_verbose(verbose)
{
    // begin job
    BeginJob();
}

// destroy:
EfficiencyBaby::~EfficiencyBaby()
{
}

// function operator: operate on each event
int EfficiencyBaby::operator() (long event, const std::string& filename)
{
    // call base class operator
    return Analyze(event, filename);
}

// members:
void EfficiencyBaby::BeginJob()
{
    // initialize branches
    m_evt.Reset();
    m_evt.SetBranches(*m_tree);
}

void EfficiencyBaby::EndJob()
{
    // call base class end job
    AnalysisWithTree::EndJob();
}

int EfficiencyBaby::Analyze(long event, const std::string& filename)
{
    using namespace tas;

    try
    {
        // Reset Tree Variables
        // --------------------------------------------------------------------------------------------------------- //

        m_evt.Reset();

        // Analysis Selections
        // --------------------------------------------------------------------------------------------------------- //

        // electron loop
        for (size_t el_idx = 0; el_idx != els_p4().size(); el_idx++)
        {
            const LorentzVector& el_p4 = els_p4().at(el_idx);
            const int el_id            = (-11 * els_charge().at(el_idx));

            // kinematics
            if (el_p4.pt() < 10 or fabs(el_p4.eta()) > 2.4)
            {
                if (m_verbose) {std::cout << "electron fails kinematic selection" << std::endl;}
                continue;
            }

            // require matching
            const bool matched = (abs(els_mc3_id().at(el_idx)) == 11 and abs(genps_status().at(els_mc3idx().at(el_idx))) == 3);
            if (not matched)
            {
                if (m_verbose) {std::cout << "electron failing matching requirement" << std::endl;}
                continue;
            }

            // require matched to Z
            //const int el_mc3_momid = els_mc3_motherid().at(el_idx);
            //const bool z_matched = (el_mc3_momid == 23);
            //if (not z_matched)
            //{
            //    if (m_verbose) {std::cout << "electron failing matching mother requirement" << std::endl;}
            //    continue;
            //}

            // corrected PF isolation
            m_evt.corpfiso   = samesign::leptonIsolation(el_id, el_idx);
            m_evt.passes_iso = samesign::isIsolatedLepton(el_id, el_idx);

            // passes samesign ID
            m_evt.passes_id  = samesign::isGoodLepton(el_id, el_idx, /*use el eta*/true);

            // passes full ID+iso
            m_evt.is_den  = samesign::isDenominatorLepton(el_id, el_idx, /*use el eta*/true);
            m_evt.is_num  = samesign::isNumeratorLepton(el_id, el_idx, /*use el eta*/true);

            // fill the tree
            m_evt.event_info.FillCommon(m_sample, filename);
            m_evt.FillCommon(el_id, el_idx);
            m_tree->Fill();
        }

        // muon loop
        for (size_t mu_idx = 0; mu_idx != mus_p4().size(); mu_idx++)
        {
            const LorentzVector& mu_p4 = mus_p4().at(mu_idx);
            const int mu_id            = (-13 * mus_charge().at(mu_idx));

            // kinematics
            if (mu_p4.pt() < 10 or fabs(mu_p4.eta()) > 2.4)
            {
                if (m_verbose) {std::cout << "muon fails kinematic selection" << std::endl;}
                continue;
            }

            // require matching
            const bool matched = (abs(mus_mc3_id().at(mu_idx)) == 13 and abs(genps_status().at(mus_mc3idx().at(mu_idx))) == 3);
            if (not matched)
            {
                if (m_verbose) {std::cout << "muon failing matching requirement" << std::endl;}
                continue;
            }

            //// require matched to Z
            //const int mu_mc3_momid = mus_mc3_motherid().at(mu_idx);
            //const bool z_matched = (mu_mc3_momid == 23);
            //if (not z_matched)
            //{
            //    if (m_verbose) {std::cout << "muon failing matching mother requirement" << std::endl;}
            //    continue;
            //}

            // corrected PF isolation
            m_evt.corpfiso   = samesign::leptonIsolation(mu_id, mu_idx);
            m_evt.passes_iso = samesign::isIsolatedLepton(mu_id, mu_idx);

            // passes samesign ID
            m_evt.passes_id  = samesign::isGoodLepton(mu_id, mu_idx, /*use el eta*/true);

            // passes full ID+iso
            m_evt.is_den  = samesign::isDenominatorLepton(mu_id, mu_idx, /*use el eta*/true);
            m_evt.is_num  = samesign::isNumeratorLepton(mu_id, mu_idx, /*use el eta*/true);

            // fill the tree
            m_evt.event_info.FillCommon(m_sample, filename);
            m_evt.FillCommon(mu_id, mu_idx);
            m_tree->Fill();
        }

        // go to the next event
        return 0;
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


// main program
// -------------------------------------------------------------------------------------------------//
// -------------------------------------------------------------------------------------------------//

int main(int argc, char* argv[])
try
{
    // inputs
    // -------------------------------------------------------------------------------------------------//

    long number_of_events           = -1;
    bool verbose                    = false;
    double luminosity               = 1.0;
    std::string output_file         = "";
    std::string input_file          = "";
    std::string ntuple_type_name    = "cms2";
    std::string sample_name         = "";

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"          , "print this menu")
        ("nev"           , po::value<long>(&number_of_events)           , "number of events to run on (-1 == all)"                                            )
        ("lumi"          , po::value<double>(&luminosity)               , "luminosity of analysis (1 fb^-1 default -- ignored for data)"                      )
        ("verbose"       , po::value<bool>(&verbose)                    , "output debug info"                                                                 )
        ("sample"        , po::value<std::string>(&sample_name)         , "name of input sample (from at/Sample.h)"                                           )
        ("ntuple_type"   , po::value<std::string>(&ntuple_type_name)    , "ntuple type name (cms2, ss_skim, ...) (from at/Sample.h)"                          )
        ("output"        , po::value<std::string>(&output_file)         , "output ROOT file for baby tree (default: <sample name>.root)"                      )
        ("input"         , po::value<std::string>(&input_file)          , "input ntuple (default is determined by the sample used)"                           )
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

    if (verbose)
    {
        cout << "inputs:" << endl;
        cout << "number_of_events   :\t" << number_of_events     << endl;
        cout << "luminosity         :\t" << luminosity           << endl;
        cout << "verbose            :\t" << verbose              << endl;
        cout << "sample_name        :\t" << sample_name          << endl;
        cout << "ntuple_type_name   :\t" << ntuple_type_name     << endl;
        cout << "output_file        :\t" << output_file          << endl;
        cout << "input_file         :\t" << input_file           << endl;
    }

    // test inputs boundary conditions
    // -------------------------------------------------------------------------------------------------//

    // do the main analysis
    // -------------------------------------------------------------------------------------------------//

    // input
    TChain* chain  = NULL;
    at::Sample::value_type sample = at::Sample::static_size; 
	if (not sample_name.empty())
	{
        cout << "processing "  << sample_name << endl;
        sample = at::GetSampleFromName(sample_name);
	}
	else
	{
        cout << "no sample name given." << endl;
	}
    if (input_file.empty())
    {
        chain = at::GetSampleTChain(sample, at::GetNtupleTypeFromName(ntuple_type_name));
        if (output_file.empty())
        {
            output_file = Form("babies/%s.root", sample_name.c_str());
        }
    }
    else
    {
        if (output_file.empty())
        {
            output_file = Form("babies/%s.root", rt::filename(sample_name).c_str());
        }
        chain = rt::CreateTChainFromCommaSeperatedList(input_file, "Events");
    }

    cout << "sample has " << chain->GetEntries() << " entries" << endl;
    cout << "sample has " << chain->GetListOfFiles()->GetEntries() << " files" << endl;
    if (verbose) {rt::PrintFilesFromTChain(chain);}

    // scan the chain
    at::ScanChainWithFilename<CMS2>
    (
        chain, 
        EfficiencyBaby 
        (
            output_file,
            sample,
            luminosity,
            verbose
        ),
        cms2,
        number_of_events,
        "",//good_run_list,
        /*fast=*/true,
        verbose
    ); 

    // cleanup
    delete chain;

    // done
    return 0;
}
catch (std::exception& e)
{
    cerr << "eff_analysis failed..." << endl;
    cerr << e.what() << endl;
    return 1;
}

