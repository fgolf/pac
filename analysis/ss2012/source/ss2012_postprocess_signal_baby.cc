// C++
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// BOOST
#include <boost/program_options.hpp>

// ROOT
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TFileMerger.h"

// Tools
#include "at/Sample.h"
#include "rt/MiscTools.h"
#include "SignalBinInfo.h"

/* --------------------------------------------------------------------------------------------- *
 This program is very specific to merge ss2012 babies from edm --> baby

 it take SUSY scan babies ROOT files that contain a TTree and a histogram: e.g.
 TFile*		output/t1tttt.root	
  KEY: TH1F	h_count;1	# of events
  KEY: TH2F	h_gen_count;1	# of Generated Events - T1tttt
  KEY: TTree	tree;2	baby tree for SS2012 analysis/

  This will get the xsections from the relavent histogram in data/xsec/susy_xsec.root.
  If the relevant xsec is not found, this will quit.

  It will
  1.  create a histogram that will be the # generated events
  2.  merge the baby chain into one TTree
  3.  add branches for the xsec, # generated events and scale1fb per susy mass point
  4.  add any k factors or efficiencies (defaults are 1.0)
  5.  write a new file with the new TTree and # generated events histogram and xsec histogram
* --------------------------------------------------------------------------------------------- */

using namespace std;
using namespace at;
using namespace ss;

int main(int argc, char* argv[])
try
{
    // inputs
    // -------------------------------------------------------------------------------------------------//

    std::string output_file  = "";
    std::string input_file   = "";
    std::string xsec_file    = "data/xsec/susy_xsec.root";
    std::string sample_name  = "";
    long long max_tree_size  = 214748364800LL; // 200 GB 
    bool gen_count_from_tree = false;

    // define inputs
    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"               , "print this menu")
        ("input"              , po::value<std::string>(&input_file)->required()  , "REQUIRED: input ntuple file (or files in a comma sperareted list)")
        ("output"             , po::value<std::string>(&output_file)->required() , "REQUIRED: output ntuple file"                                     )
        ("sample"             , po::value<std::string>(&sample_name)->required() , "REQUIRED: sample to post process (at/Sample.h)"                   )
        ("xsec"               , po::value<std::string>(&xsec_file)               , "cross section file path (data/xsec/susy_xsec.root)"               )
        ("maxsize"            , po::value<long long>(&max_tree_size)             , "Maximum Tree File size before it makes a new file"                )
        ("gen_count_from_tree", po::value<bool>(&gen_count_from_tree)            , "Get the gen count from the Tree (assumes there was no filter)"    )
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

    cout << "[ss2012_postprocess_signal_baby] post processing with the following inputs:" << endl;
    cout << "input_file  :\t"  << input_file    << endl;
    cout << "output_file :\t"  << output_file   << endl;
    cout << "sample_name :\t"  << sample_name   << endl;
    cout << "xsec_file   :\t"  << xsec_file     << endl;
    cout << "maxtreesize:\t" << max_tree_size << endl;
    cout << "gen_count_from_tree:\t" << gen_count_from_tree << endl;

    // check the sample to post process
    // -------------------------------------------------------------------------------------------------//

    Sample::value_type sample = GetSampleFromName(sample_name);
    switch (sample)
    {
        case Sample::t1tttt:       break;
        case Sample::t1tttt_scans: break;
        case Sample::sbottomtop:   break;
        case Sample::t6ttww_x08:   break;
        case Sample::t6ttww_x05:   break;
        case Sample::tchiwh:       break;
        default: 
            cout << "[ss2012_postprocess_signal_baby] Error: Sample " << sample_name << " is not supported" << endl;
            return 1;
    }
    SampleInfo sample_info = GetSampleInfo(sample);

    // Merge the Chains
    // -------------------------------------------------------------------------------------------------//

    // maximum output tree limit
    TTree::SetMaxTreeSize(max_tree_size); 
    cout << "[ss2012_postprocess_signal_baby] TTree::GetMaxTreeSize() = " << TTree::GetMaxTreeSize() << endl;

    TChain* chain_ptr = rt::CreateTChainFromCommaSeperatedList(input_file, "tree");
    TChain& chain = *chain_ptr;
    chain.SetDirectory(NULL);
    cout << "Merging TTree(s) for " << sample_name << " -- please wait..." << endl;
    cout << "tree has " << chain.GetEntries() << " entries" << endl;

    // Removes the branches (if they exist) that we want to replace
    chain.SetBranchStatus("*"       , 1);
    chain.SetBranchStatus("xsec"    , 0);
    chain.SetBranchStatus("nevts"   , 0); 
    chain.SetBranchStatus("scale1fb", 0); 

    // clone it
    TFile* output = TFile::Open(output_file.c_str(), "RECREATE");
    TTree* clone = chain.CloneTree(-1, "fast");

    // create the # generated events histogram 
    // -------------------------------------------------------------------------------------------------//

    ss::SignalBinInfo bin_info = ss::GetSignalBinInfo(sample);
    TH2F* h_gen_count = new TH2F("h_gen_count", Form("# Generated Events - %s", GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax);
    h_gen_count->SetDirectory(NULL); // taking ownership

    if (gen_count_from_tree)
    {
        h_gen_count->SetDirectory(gDirectory); // needed by TTree::Draw
        chain.Draw("sparm1:sparm0>>h_gen_count", "", "goff");
        h_gen_count->SetDirectory(NULL);
    }
    else
    {
        const vector<string> vfile_names_glob = rt::string_split(input_file, ",");
        vector<string> vfile_names;
        for (size_t i = 0; i != vfile_names_glob.size(); i++)
        {
            vector<string> vfile_names_temp = rt::ls(vfile_names_glob.at(i));
            vfile_names.insert(vfile_names.end(), vfile_names_temp.begin(), vfile_names_temp.end());
        }
        for (size_t i = 0; i != vfile_names.size(); i++)
        {
            //cout << vfile_names.at(i) << endl;
            try
            {
                TH2F* h_temp = rt::GetHistFromRootFile<TH2F>(vfile_names.at(i), "h_gen_count");
                h_gen_count->Add(h_temp);
                delete h_temp;
            }
            catch (std::exception& e)
            {
                cout << "[ss2012_post_process_signal_baby] Error: " << vfile_names.at(i) << " does not have h_gen_count!" << endl;
                throw e; 
            }
        }
    }

    // create the # scale 1fb histogram 
    // -------------------------------------------------------------------------------------------------//

    TH1F* h_xsec = rt::GetHistFromRootFile<TH1F>(xsec_file, Form("h_xsec_%s", sample_name.c_str()));
    h_xsec->SetName("h_xsec");
    h_xsec->SetDirectory(NULL); // taking ownership

    TH2F* h_scale1fb = new TH2F("h_scale1fb", Form("# Scale to 1 fb^{-1} - %s", GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax);
    h_scale1fb->SetDirectory(NULL);
    for (int xbin = 1; xbin != h_scale1fb->GetNbinsX()+1; xbin++)
    {
        const float xsec     = h_xsec->GetBinContent(xbin);
        const float xsec_err = h_xsec->GetBinError(xbin);
        for (int ybin = 1; ybin != h_scale1fb->GetNbinsY()+1; ybin++)
        {
            const float num_gen      = static_cast<float>(h_gen_count->GetBinContent(xbin, ybin));
            const float scale1fb     = (num_gen > 0 ? (xsec * 1000.0f)/num_gen : 0.0f);
            const float scale1fb_err = (num_gen > 0 ? (xsec_err * 1000.0f)/num_gen : 0.0f);
            h_scale1fb->SetBinContent(xbin, ybin, scale1fb    );
            h_scale1fb->SetBinError  (xbin, ybin, scale1fb_err);
        }
    }

    // add the cross section
    // -------------------------------------------------------------------------------------------------//

    unsigned int nevts = 0;
    float xsec = -999999.0; 
    float scale1fb = -999999.0;
    float sparm0;
    float sparm1;
    float sparm2;
    float sparm3;

    // set the branches for the sparms
    clone->SetBranchStatus("sparm*", 1);
    clone->SetBranchAddress("sparm0", &sparm0);
    clone->SetBranchAddress("sparm1", &sparm1);
    clone->SetBranchAddress("sparm2", &sparm2);
    clone->SetBranchAddress("sparm3", &sparm3);
    
    TBranch* b1 = clone->Branch("scale1fb", const_cast<float*>       (&scale1fb), "scale1fb/F"); 
    TBranch* b2 = clone->Branch("xsec"    , const_cast<float*>       (&xsec    ), "xsec/F"    ); 
    TBranch* b3 = clone->Branch("nevts"   , const_cast<unsigned int*>(&nevts   ), "nevts/i"   ); 

    // counts
    const size_t num_events_chain = clone->GetEntries();
    size_t i_permilleOld          = 0;
    size_t num_events_total       = 0;

    //for (size_t i = 0; i != num_events_chain; i++) 
    for (size_t i = 0; i != 100; i++) 
    {
        // get the current TTree entry
        clone->GetEntry(i);
        num_events_total++;

        // set the values
        switch (sample)
        {
            case at::Sample::t1tttt:       // m_gluino vs m_lsp
            case at::Sample::t1tttt_scans: // m_gluino vs m_lsp
                xsec     = rt::GetBinContent1D(h_xsec, sparm0);
                scale1fb = rt::GetBinContent2D(h_scale1fb, sparm0, sparm1);
                nevts    = static_cast<unsigned int>(rt::GetBinContent2D(h_gen_count, sparm0, sparm1));
                break;
            case at::Sample::sbottomtop: // m_sbottom vs m_chargino
            case Sample::t6ttww_x08:     // m_sbottom vs m_chargino
            case Sample::t6ttww_x05:     // m_sbottom vs m_chargino
                xsec     = rt::GetBinContent1D(h_xsec, sparm0);
                scale1fb = rt::GetBinContent2D(h_scale1fb, sparm0, sparm1);
                nevts    = static_cast<unsigned int>(rt::GetBinContent2D(h_gen_count, sparm0, sparm1));
                break;
            default:
                {/* do nothing */}
        }

        // pogress
        size_t i_permille = static_cast<size_t>(floor(1000 * num_events_total / float(num_events_chain)));
        if (i_permille != i_permilleOld)
        {
            printf("  \015\033[32m ---> \033[1m\033[31m%4.1f%%" "\033[0m\033[32m <---\033[0m\015", i_permille/10.0);
            fflush(stdout);
            i_permilleOld = i_permille;
        }

        // fill the branches
        b1->Fill();
        b2->Fill();
        b3->Fill();
    }

    // save output
    // -------------------------------------------------------------------------------------------------//
    // this is tricky because you have to save the histogram and the baby could potentially be
    // large enough to spill to another file

    // write the tree;
    output = clone->GetCurrentFile();
    output->Write();
    output->Close();

    // save the hists in each root file
    const string output_file_star           = rt::string_replace_first(output_file, ".root", "*.root");
    const vector<string> voutput_file_names = rt::ls(output_file_star);
    for (size_t i = 0; i != voutput_file_names.size(); i++)
    {
        cout << "putting hists in file " << voutput_file_names.at(i).c_str() << endl;
        TFile file(voutput_file_names.at(i).c_str(), "UPDATE");
        h_gen_count->Write();
        h_scale1fb->Write();
        h_xsec->Write();
        file.Close();
    }
    cout << "[ss2012_postprocess_signal_baby] complete..." << endl;

    // cleanup
    delete h_xsec;
    delete chain_ptr;

    // done
    return 0;
}
catch (std::exception& e)
{
    cerr << "[ss2012_postprocess_signal_baby] failed..." << endl;
    cerr << e.what() << endl;
    return 1;
}
