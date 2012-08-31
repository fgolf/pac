// c++
#include <iostream>
#include <stdexcept>

// ROOT
#include "TChain.h"
#include "TTreeCache.h"
#include "TBenchmark.h"

// CMS2
#include "CMS2.h"

// tools
#include "at/DorkyEventIdentifier.h"
#include "at/GoodRun.h"
#include "rt/RootTools.h"

namespace at
{
    // Peform an analysis on a chain.
    template <typename Function>
    int ScanChainCMS2
    (
        TChain* chain, 
        Function analyze, 
        long num_events,
        const std::string& goodrun_file_name,
        bool fast,
        bool verbose
    )
    {
        using namespace std;

        // test chain
        if (!chain)
        {
            throw std::invalid_argument("at::ScanChain: chain is NULL!");
        }
        //rt::PrintFilesFromTChain(chain);
        string tree_name = chain->GetName();
    
        //if (chain->GetListOfBranches()->FindObject("EventAuxiliary"))
        //{
        //    chain->SetBranchStatus("EventAuxiliary",0);
        //}


        // set the "good run" list 
        if (!goodrun_file_name.empty())
        {
            set_goodrun_file(goodrun_file_name.c_str());
            //set_goodrun_file_json(goodrun_file_name.c_str());
        }

        // set the style
        rt::SetStyle("emruoi");
    
        // benchmark
        TBenchmark bmark;
        bmark.Start("benchmark");
    
        // events counts and max events
    	int i_permilleOld = 0;
        long num_events_total = 0;
        long num_events_chain = (num_events >= 0 && num_events < chain->GetEntries()) ? num_events : chain->GetEntries();
        TObjArray* list_of_files = chain->GetListOfFiles();
        TIter file_iter(list_of_files);
        TFile* current_file = NULL;

        // count the duplicates and bad events
        unsigned long duplicates = 0;
        unsigned long bad_events = 0;

        while ((current_file = (TFile*)file_iter.Next()))
        {
            TFile *file = TFile::Open(current_file->GetTitle());
            if (!file || file->IsZombie())
            {
                std::cout << "Skipping bad input file: " << current_file->GetTitle() << std::endl;
                continue;
            }

            TTree *tree = dynamic_cast<TTree*>(file->Get(tree_name.c_str()));
            if (!tree || tree->IsZombie())
            {
                std::cout << "Skipping bad input file (missing tree): " << current_file->GetTitle() << std::endl;
                continue;
            }

            if (fast)
            {
                TTreeCache::SetLearnEntries(10);
                tree->SetCacheSize(128*1024*1024);
            }
            cms2.Init(tree);

            // Loop over Events in current file
            if (num_events_total >= num_events_chain) continue;
            long num_events_tree = tree->GetEntriesFast();

            // loop over events to Analyze
            for (long event = 0; event != num_events_tree; ++event)
            {
                // quit if the total is > the number in the chain
                if (num_events_total >= num_events_chain) continue;

                // load the entry
                if (fast) tree->LoadTree(event);
                cms2.GetEntry(event);
                ++num_events_total;

                // pogress
            	int i_permille = (int)floor(1000 * num_events_total / float(num_events_chain));
            	if (i_permille != i_permilleOld) {
            	    printf("  \015\033[32m ---> \033[1m\033[31m%4.1f%%" "\033[0m\033[32m <---\033[0m\015", i_permille/10.);
            	    fflush(stdout);
            	    i_permilleOld = i_permille;
            	}

				// stop on a specific event
                //if (tas::evt_isRealData() && !(evt_run() == 190538 && evt_lumiBlock() == 636 && evt_event() == 928975370))
                //if (tas::evt_isRealData() && !(tas::evt_run() == 190538))
        		//{
        		//    continue;
        		//}

                // filter out events
                if (tas::evt_isRealData())
				{
					//if (verbose) {cout << "good run file = " << goodrun_file_name << endl;}
					if (!goodrun_file_name.empty())
					{
						// check for good run and events
						if(!goodrun(tas::evt_run(), tas::evt_lumiBlock())) 
							//if(!goodrun_json(tas::evt_run(), tas::evt_lumiBlock())) 
						{
							if (verbose) {cout << "Bad run and lumi:\t" << tas::evt_run() << ", " << tas::evt_lumiBlock() << endl;}
							bad_events++;
							continue;
						}
						//else
						//{
						//    if (verbose) {cout << "Good run and lumi:\t" << tas::evt_run() << ", " << tas::evt_lumiBlock() << endl;}
						//}
					}

					// check for dupiclate run and events
					DorkyEventIdentifier id = {tas::evt_run(), tas::evt_event(), tas::evt_lumiBlock()};
					if (is_duplicate(id))
					{
						if (verbose) {cout << "Duplicate event:\t" << id.run << ", " << id.event << ", " << id.lumi << endl;}
						duplicates++;
						continue;
					}
				}

				// print run/ls/event
        		if (verbose)
        		{
        		    cout << Form("run %d, ls %d, evt %d", tas::evt_run(), tas::evt_lumiBlock(), tas::evt_event()) << endl;
        		}

                // analysis
                analyze(event);

            } // end event loop

            // close current file
            file->Close();
            delete file;

        } // end file loop
    
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
        cout << "# of bad events filtered = " << bad_events << endl; 
        cout << "# of duplicates filtered = " << duplicates << endl; 
        cout << "------------------------------" << endl;
        cout << "CPU  Time:	" << Form("%.01f", bmark.GetCpuTime("benchmark" )) << endl;
        cout << "Real Time:	" << Form("%.01f", bmark.GetRealTime("benchmark")) << endl;
        cout << endl;
    
        // done
        return 0;
    }
    
} // namespace at

