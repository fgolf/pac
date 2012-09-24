#include <iostream>
#include <string>
#include "TChain.h"
#include "muonSelections.h"
#include "electronSelections.h"
#include "ssSelections.h"
#include "jetSelections.h"
#include "trackSelections.h"
#include "eventSelections.h"
#include "jetcorr/FactorizedJetCorrector.h"
#include "at/DileptonHypType.h"
#include "at/SkimChain.h"
#include "rt/RootTools.h"
#include <boost/program_options.hpp>

// skim code
// very simple
bool SelectSameSign(long event)
{
    using namespace tas;
    using namespace at;

    // not used yet
    // FactorizedJetCorrector* jet_pf_corrector=NULL

    // loop over hypothesis
    for (unsigned int ihyp = 0; ihyp < cms2.hyp_p4().size(); ihyp++)
    {
        // eta < 2.5
        if (fabs(cms2.hyp_lt_p4().at(ihyp).eta()) > 2.5)
        {
            continue;
        }
        if (fabs(cms2.hyp_ll_p4().at(ihyp).eta()) > 2.5)
        {
            continue;
        }

        int lt_id   = cms2.hyp_lt_id().at(ihyp);
        int lt_idx  = cms2.hyp_lt_index().at(ihyp);
        float lt_pt = cms2.hyp_lt_p4().at(ihyp).pt();
        int ll_id   = cms2.hyp_ll_id().at(ihyp);
        int ll_idx  = cms2.hyp_ll_index().at(ihyp);
        float ll_pt = cms2.hyp_ll_p4().at(ihyp).pt();

        // require 20/10 GeV leptons
        if (min(lt_pt, ll_pt) < 10.0 || max(lt_pt, ll_pt) < 20.0)
        {
            continue;
        }

        // jet type
        //JetType jet_type = evt_isRealData() ? JETS_TYPE_PF_FAST_CORR_RESIDUAL : JETS_TYPE_PF_FAST_CORR;

        // require 2 jets
        //int njets = jet_pf_corrector  ? samesign::nJets(ihyp, jet_pf_corrector, jet_type, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt2>*/20.0) : 
        //                                samesign::nJets(ihyp, jet_type,                   /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt2>*/20.0);
        //int njets = samesign::nJets(ihyp, jet_type, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt2>*/20.0);
        //if (njets < 2)
        //{
        //    continue;
        //}

        // need at least one good vertex
        int nGoodVertices = numberOfGoodVertices();
        if (nGoodVertices < 1)
        {
            continue;
        }

        // same sign
        if ((lt_id * ll_id) > 0)
        {
            // keep if FO/FO
            if (!samesign::isDenominatorLepton(lt_id, lt_idx) || !samesign::isDenominatorLepton(ll_id, ll_idx))
            {
                continue;
            }
            return true;
        }
        // oppposite sign and data
        else if ((lt_id * ll_id) < 0)
        {
            if (evt_isRealData())
            {
                // select specific events
                bool ee_or_em = ((hyp_typeToHypType(hyp_type().at(ihyp)) == DileptonHypType::EE) || (hyp_typeToHypType(hyp_type().at(ihyp)) == DileptonHypType::EMU));
                if (not (ee_or_em && samesign::isNumeratorHypothesis(ihyp)))
                {
                    continue;
                }
                return true;
            }        
        }
    }

    return false;
}

// do the skim
int main(int argc, char* argv[])
try
{
    using namespace std;

    // inputs
    // -------------------------------------------------------------------------------------------------//

    std::string input_file  = "";
    std::string output_file = "ntuple_skim.root";
    std::string run_list    = "";
    long number_of_events   = -1;
    bool verbose            = false;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"     , "print this menu")
        ("nev"      , po::value<long>(&number_of_events)   , "number of events to run on (-1 == all)"           )
        ("output"   , po::value<std::string>(&output_file) , "name of output root file (default is merged.root)")
        ("input"    , po::value<std::string>(&input_file)  , "name of input root(s) file (can be cvs)"          )
        ("run_list" , po::value<std::string>(&run_list)    , "good run list (default is empty)"                 )
        ("verbose"  , po::value<bool>(&verbose)            , "verbosity"                                        )
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

    if (vm.count("help"))
    {
        cout << desc << "\n";
        return 1;
    }

    // check that input file exists and is specified
    if (!input_file.empty())
    { 
        //if (!rt::exists(input_file))
        //{
        //    cout << "ERROR: ss2012_plots: input file " << input_file << " not found" << endl;
        //    cout << desc << "\n";
        //    return 1;
        //}
    }
    else
    {
        cout << "ERROR: ss2012_skim: input file " << input_file << " not specified." << endl;
        cout << desc << "\n";
        return 1;
    }

    // if the run list is specified, check that it exists 
    if (!run_list.empty())
    { 
        if (!rt::exists(run_list))
        {
            cout << "ERROR: ss2012_skim: run_list " << run_list << " not found" << endl;
            cout << desc << "\n";
            return 1;
        }
    }

    // print the input
    if (verbose)
    {
        cout << "input files = "  << input_file  << endl;
        cout << "output files = " << output_file << endl;
        cout << "run_list = "     << run_list    << endl;
    }
    
    // do the main analysis
    // -------------------------------------------------------------------------------------------------//

    // make the directory for the output file

    // merge the tree
    TChain* chain = rt::CreateTChainFromCommaSeperatedList(input_file, "Events");
    //if (chain->GetListOfBranches()->Contains("EventAuxiliary"))
    //{
    //    chain->SetBranchStatus("EventAuxiliary", 0);
    //}

    //// run the skim and do not cut events except for duplicates and bad runs
    rt::mkdir(rt::dirname(output_file), /*force=*/true);
    
    SkimChainCMS2
    (
        chain,
        output_file,
        run_list,
        SelectSameSign,
        number_of_events,
        /*do_duplicate_removal=*/true,
        verbose
    );

    // cleanup
    delete chain;
    
    // done 
    return 0;
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
    return 1;
}
