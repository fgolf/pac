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
#include "CMS2Wrapper.h"
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
    //FactorizedJetCorrector* jet_pf_corrector = NULL;

    // loop over hypothesis
    for (unsigned int ihyp = 0; ihyp < cms2.hyp_p4().size(); ihyp++)
    {
        // eta < 2.5
        if (fabs(cms2.hyp_lt_p4().at(ihyp).eta()) > 2.4)
        {
            continue;
        }
        if (fabs(cms2.hyp_ll_p4().at(ihyp).eta()) > 2.4)
        {
            continue;
        }

        const int lt_id   = cms2.hyp_lt_id().at(ihyp);
        const int lt_idx  = cms2.hyp_lt_index().at(ihyp);
        const float lt_pt = cms2.hyp_lt_p4().at(ihyp).pt();
        const int ll_id   = cms2.hyp_ll_id().at(ihyp);
        const int ll_idx  = cms2.hyp_ll_index().at(ihyp);
        const float ll_pt = cms2.hyp_ll_p4().at(ihyp).pt();

        // require 5/10 GeV muons/electrons 
        const float mu_minpt = 5.0;
        const float el_minpt = 10.0;
        const float l1_pt = max(lt_pt, ll_pt);
        const float l2_pt = min(lt_pt, ll_pt);
        const unsigned int l1_id = lt_pt > ll_pt ? abs(lt_id) : abs(ll_id);
        const unsigned int l2_id = lt_pt > ll_pt ? abs(ll_id) : abs(lt_id);
        const float minpt1 = l1_id == 13 ? mu_minpt : el_minpt; 
        const float minpt2 = l2_id == 13 ? mu_minpt : el_minpt; 

        if (l1_pt < minpt1 || l2_pt < minpt2)
        {
            continue;
        }

        // jet type
        const JetType jet_type = evt_isRealData() ? JETS_TYPE_PF_FAST_CORR_RESIDUAL : JETS_TYPE_PF_FAST_CORR;

        // require 2 jets
        //int njets = jet_pf_corrector  ? samesign::nJets(ihyp, jet_pf_corrector, jet_type, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/10.0, /*pt2>*/10.0) : 
        //                                samesign::nJets(ihyp, jet_type,                   /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/10.0, /*pt2>*/10.0);
        int njets = samesign::nJets(ihyp, jet_type, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, mu_minpt, el_minpt);
        if (njets < 2)
        {
            continue;
        }

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
            if (evt_isRealData() && (!samesign::isDenominatorLepton(lt_id, lt_idx) || !samesign::isDenominatorLepton(ll_id, ll_idx)))
            {
                continue;
            }
            else if (not evt_isRealData() && not samesign::isNumeratorHypothesis(ihyp))
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
                //bool ee_or_em = ((hyp_typeToHypType(hyp_type().at(ihyp)) == DileptonHypType::EE) || (hyp_typeToHypType(hyp_type().at(ihyp)) == DileptonHypType::EMU));
                //if (not (ee_or_em && samesign::isNumeratorHypothesis(ihyp)))
                if (not samesign::isNumeratorHypothesis(ihyp))
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

    std::string input_file    = "";
    std::string output_file   = "ntuple_skim.root";
    std::string run_list      = "";
    long number_of_events     = -1;
    bool do_duplicate_removal = false;
    bool verbose              = false;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"     , "print this menu")
        ("nev"      , po::value<long>(&number_of_events)    , "number of events to run on (-1 == all)"           )
        ("output"   , po::value<std::string>(&output_file)  , "name of output root file (default is merged.root)")
        ("input"    , po::value<std::string>(&input_file)   , "name of input root(s) file (can be cvs)"          )
        ("run_list" , po::value<std::string>(&run_list)     , "good run list (default is empty)"                 )
        ("duplicate", po::value<bool>(&do_duplicate_removal), "remove duplicate events (default is false)"       )
        ("verbose"  , po::value<bool>(&verbose)             , "verbosity"                                        )
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
    
    at::SkimChain
    (
        chain,
        output_file,
        SelectSameSign,
        cms2,
        number_of_events,
        run_list,
        do_duplicate_removal,
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
