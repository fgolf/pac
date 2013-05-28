// c++
#include <iostream>
#include <stdexcept>
#include <set>

// ROOT
#include "TChain.h"
#include "TTreeCache.h"
#include "TBenchmark.h"

// SSB baby
#include "RPVSTOP2012_OS.h"

// tools
#include "rt/RootTools.h"
#include "at/DorkyEventIdentifier.h"
#include "at/GoodRun.h"

// Peform an filter on a SSB ntuple.
template <typename Function>
int SkimChainOS
(
    TChain* chain, 
    const std::string& output_file_name,
    const std::string& goodrun_file_name,
    Function selected, 
    long num_events,
    bool do_duplicate_removal,
    bool verbose
    )
{
    using namespace std;

    // test chain
    if (!chain)
    {
        throw std::invalid_argument("at::SkimChain: chain is NULL!");
    }
    rt::PrintFilesFromTChain(chain);
    string tree_name = chain->GetName();

    // the output file
    TFile* output_root_file = TFile::Open(output_file_name.c_str(), "RECREATE");
    TTree* new_tree         = chain->CloneTree(0); 
    new_tree->SetDirectory(output_root_file);

    // set the "good run" list 
    if (!goodrun_file_name.empty())
    {
        set_goodrun_file(goodrun_file_name.c_str());
    }

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
    int duplicates = 0;
    int bad_events = 0;

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
        tree->SetDirectory(file);

        // init
        rpvstop12os.Init(new_tree);
        rpvstop12os.Init(tree);

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
            rpvstop12os.GetEntry(event);
            ++num_events_total;

            // data only
            if (rpvstop_os::is_real_data())
            {
                // filter bad runs
                if (!goodrun_file_name.empty())
                {
                    // check for good run and events
                    if(!goodrun(rpvstop_os::run(), rpvstop_os::ls())) 
                    {
                        if (verbose) {cout << "Bad run and lumi:\t" << rpvstop_os::run() << ", " << rpvstop_os::ls() << endl;}
                        bad_events++;
                        continue;
                    }
                    //else
                    //{
                    //    if (verbose) {cout << "Good run and lumi:\t" << tas::evt_run() << ", " << tas::evt_lumiBlock() << endl;}
                    //}
                }
                // check for dupiclate run and events (only for data)
                if (do_duplicate_removal)
                {
                    at::DorkyEventIdentifier id = {rpvstop_os::run(), rpvstop_os::evt(), rpvstop_os::ls()};
                    if (is_duplicate(id))
                    {
                        if (verbose)
                        {
                            cout << "Duplicate event:\t" << id.run << ", " << id.event << ", " << id.lumi << endl;
                        }
                        duplicates++;
                        continue;
                    }
                }
            }

            // pogress
            int i_permille = (int)floor(1000 * num_events_total / float(num_events_chain));
            if (i_permille != i_permilleOld)
            {
                printf("  \015\033[32m ---> \033[1m\033[31m%4.1f%%" "\033[0m\033[32m <---\033[0m\015", i_permille/10.);
                fflush(stdout);
                i_permilleOld = i_permille;
            }

            // filter
            if (not selected(event))
            {
                continue;
            }

            // fill the new tree
            file->cd();
            rpvstop12os.LoadAllBranches();
            output_root_file->cd();
            new_tree->Fill();

        } // end event loop

        // Clean Up
        //delete tree;
        file->Close();
        delete file;
    }

    // wrap up
    output_root_file->cd();
    new_tree->Write();
    output_root_file->Close();
    delete output_root_file;

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
    if (not goodrun_file_name.empty())
    {
        cout << "# of bad events filtered = " << bad_events << endl; 
    }
    if (do_duplicate_removal)
    {
        cout << duplicates << " Duplicate Events" << endl;
    }
    else
    {
        cout << " No Duplicate removal peformed" << endl;
    }
    cout << "skimmed output saved in " << output_file_name << endl;  
    cout << "------------------------------" << endl;
    cout << "CPU  Time:	" << Form("%.01f", bmark.GetCpuTime("benchmark" )) << endl;
    cout << "Real Time:	" << Form("%.01f", bmark.GetRealTime("benchmark")) << endl;
    cout << endl;

    // done
    return 0;
}

