// c++
#include <iostream>
#include <stdexcept>
#include <set>

// ROOT
#include "TChain.h"
#include "TTreeCache.h"
#include "TBenchmark.h"

// SSB baby
#include "SSB.h"

// tools
#include "rt/RootTools.h"
//#include "at/DorkyEventIdentifier.hpp"

// Peform an analysis on a CMS2 ntuple.
template <typename Function>
int ScanChainSSB
(
    TChain* chain, 
    Function analyze, 
    long num_events,
    bool is_data,
    bool verbose
)
{
    using namespace std;

    // test chain
    if (!chain)
    {
        throw std::invalid_argument("at::ScanChain: chain is NULL!");
    }
    rt::PrintFilesFromTChain(chain);
    string tree_name = chain->GetName();

    // set the style
    rt::SetStyle("emruoi");

    // benchmark
    TBenchmark bmark;
    bmark.Start("benchmark");

    // events counts and max events
    int i_permilleOld = 0;
    long num_events_total = 0;
    long num_events_chain = (num_events >= 0 && num_events < chain->GetEntries()) ? num_events : chain->GetEntries();
    int duplicates = 0;
    TObjArray* list_of_files = chain->GetListOfFiles();
    TIter file_iter(list_of_files);
    TFile* current_file = NULL;

    while ((current_file = (TFile*)file_iter.Next()))
    {
        TFile *file = new TFile(current_file->GetTitle());
        TTree *tree = dynamic_cast<TTree*>(file->Get(tree_name.c_str()));
        if (not tree)
        {
            continue;
        }
        TTreeCache::SetLearnEntries(10);
        tree->SetCacheSize(128*1024*1024);
        samesignbtag.Init(tree);

        // Loop over Events in current file
        if (num_events_total >= num_events_chain) continue;
        long num_events_tree = tree->GetEntriesFast();

        // loop over events to Analyze
        for (long event = 0; event != num_events_tree; ++event)
        {
            // quit if the total is > the number in the chain
            if (num_events_total >= num_events_chain) continue;

            // load the entry
            tree->LoadTree(event);
            samesignbtag.GetEntry(event);
            ++num_events_total;

            // check for dupiclate run and events (only for data)
			//if (is_data)
			//{
			//	at::DorkyEventIdentifier id = {frb::run(), frb::evt(), frb::ls()};
			//	if (is_duplicate(id))
			//	{
			//		if (verbose)
			//		{
			//			cout << "Duplicate event:\t" << id.run << ", " << id.event << ", " << id.lumi << endl;
			//		}
			//		duplicates++;
			//		continue;
			//	}
			//}

            // pogress
            int i_permille = (int)floor(1000 * num_events_total / float(num_events_chain));
            if (i_permille != i_permilleOld) {
                printf("  \015\033[32m ---> \033[1m\033[31m%4.1f%%" "\033[0m\033[32m <---\033[0m\015", i_permille/10.);
                fflush(stdout);
                i_permilleOld = i_permille;
            }

            // analysis
            analyze(event);

        } // end event loop

        // Clean Up
        delete tree;
        file->Close();
        delete file;
    }

    // print warning if the totals don't line up
    if (num_events_chain != num_events_total) 
    {
        cout << "Error: number of events from the files " 
            << "(" << num_events_chain << ") " 
            << "is not equal to the total number of events "
            << "(" << num_events_total << ")." 
            << endl;
    }

    // the benchmark results 
    // -------------------------------------------------------------------------------------------------//
    bmark.Stop("benchmark");
    cout << endl;
    cout << num_events_total << " Events Processed" << endl;
	if (is_data)
	{
    	cout << duplicates << " Duplicate Events" << endl;
	}
	else
	{
    	cout << " No Duplicate removal peformed" << endl;
	}
    cout << "------------------------------" << endl;
    cout << "CPU  Time:	" << Form("%.01f", bmark.GetCpuTime("benchmark" )) << endl;
    cout << "Real Time:	" << Form("%.01f", bmark.GetRealTime("benchmark")) << endl;
    cout << endl;

    // done
    return 0;
}

