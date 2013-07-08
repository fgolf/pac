// C++
#include <iostream>
#include <stdexcept>
#include <string>

// BOOST
#include <boost/program_options.hpp>

// ROOT
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TDirectory.h"
#include "rt/MiscTools.h"
#include "TString.h"

 using namespace std;

void SetBranchStatus(TTree* tree, const std::string& alias_name, const int value)
{
    std::string branch_name = (tree->GetAlias(alias_name.c_str()) ? tree->GetAlias(alias_name.c_str()) : "");
    if (not branch_name.empty())
    {
        branch_name = rt::string_replace_all(branch_name, ".obj", "*");
        tree->SetBranchStatus(branch_name.c_str(), value); 
    }
}

int AddCMS2BranchesWithTag
(
    const std::string& input_file_name, 
    const std::string& output_file_name, 
    const std::string& cms2_tag,
    const int events,
    const float xsec, 
    const float kfactor, 
    const float filt_eff, 
    const bool SortBasketsByEntry = false
)
{
    // check the input
    //-------------------------------------------------------------`
    std::cout << "Processing File " << input_file_name << std::endl;
    TFile input_file(input_file_name.c_str());
    if (input_file.IsZombie()) 
    {
        throw std::invalid_argument("[AddCMS2Branches] File does not exist! exiting..."); 
    }

    TTree* tree = dynamic_cast<TTree*>(input_file.Get("Events"));
    if (!tree || tree->IsZombie()) 
    {
        throw std::invalid_argument("[AddCMS2Branches] TTree \"Events\" does not exist! exiting..."); 
    }

    // Removes all non *_CMS2.* branches
    //-------------------------------------------------------------`
    tree->SetBranchStatus("*"        , 0);
    tree->SetBranchStatus("*_CMS2.*" , 1);

    // Removes the branches (if they exist) that we want to replace
    //-------------------------------------------------------------`

    SetBranchStatus(tree, "evt_xsec_excl", 0);
    SetBranchStatus(tree, "evt_scale1fb" , 0); 
    SetBranchStatus(tree, "evt_xsec_excl", 0); 
    SetBranchStatus(tree, "evt_xsec_incl", 0); 
    SetBranchStatus(tree, "evt_kfactor"  , 0); 
    SetBranchStatus(tree, "evt_filt_eff" , 0); 
    SetBranchStatus(tree, "evt_nEvts"    , 0); 
    SetBranchStatus(tree, "evt_CMS2tag"  , 0);

    // Calculate scaling factor and put variables into tree 
    //-------------------------------------------------------------

    const float scale1fb = (events > 0 ? xsec * kfactor * 1000.0f * filt_eff/static_cast<float>(events) : -999999.0f);
    std::cout << "scale1fb: " << scale1fb << std::endl; 

    // Clone the tree to modify 
    //-------------------------------------------------------------

    TFile output_file(output_file_name.c_str(), "RECREATE");
    TTree *clone = (SortBasketsByEntry ? tree->CloneTree(-1, "fastSortBasketsByEntry") : tree->CloneTree(-1, "fast"));
    clone->SetDirectory(&output_file);

    // Add the new branches 
    //-------------------------------------------------------------
    std::vector<TString> vcms2_tag;
    vcms2_tag.push_back(TString(cms2_tag.c_str()));

    TBranch* b1 = clone->Branch("evtscale1fb" , const_cast<float*>(&scale1fb) , "evt_scale1fb/F"  ); 
    TBranch* b2 = clone->Branch("evtxsecexcl" , const_cast<float*>(&xsec    ) , "evt_xsec_excl/F" ); 
    TBranch* b3 = clone->Branch("evtxsecincl" , const_cast<float*>(&xsec    ) , "evt_xsec_incl/F" ); 
    TBranch* b4 = clone->Branch("evtkfactor"  , const_cast<float*>(&kfactor ) , "evt_kfactor/F"   ); 
    TBranch* b5 = clone->Branch("evtnEvts"    , const_cast<int*>(&events    ) , "evt_nEvts/I"     ); 
    TBranch* b6 = clone->Branch("evtfilteff"  , const_cast<float*>(&filt_eff) , "evt_filt_eff/F"  ); 
    TBranch* b7 = clone->Branch("evtCMS2tag"  , "std::vector<TString>"        , &vcms2_tag        , 32000, 0);

    clone->SetAlias("evt_scale1fb"  , "evtscale1fb" ); 
    clone->SetAlias("evt_xsec_excl" , "evtxsecexcl" ); 
    clone->SetAlias("evt_xsec_incl" , "evtxsecincl" ); 
    clone->SetAlias("evt_kfactor"   , "evtkfactor"  ); 
    clone->SetAlias("evt_nEvts"     , "evtnEvts"    ); 
    clone->SetAlias("evt_filt_eff"  , "evtfilteff"  ); 
    clone->SetAlias("evt_CMS2tag"   , "evtCMS2tag"  );

    for (Int_t i = 0, nentries = tree->GetEntries(); i < nentries; i++) 
    {
        b1->Fill();
        b2->Fill();
        b3->Fill();
        b4->Fill();
        b5->Fill();
        b6->Fill();
        b7->Fill();
    }

    // wrap up
    //-------------------------------------------------------------

    clone->Write(); 
    output_file.Close();
    input_file.Close();
    std::cout << "Post Processed file is complete: " << output_file_name << std::endl; 
    return 0;
}

int main(int argc, char* argv[])
try
{

    // inputs
    // -------------------------------------------------------------------------------------------------//

    std::string output_file = "";
    std::string input_file  = "";
    std::string cms2_tag    = "";
    float kfactor           = 1.0;
    float filter_eff        = 1.0;
    float xsec              = -999999.0;
    int num_events          = -999999;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"        , "print this menu")
        ("input"      , po::value<std::string>(&input_file)  , "input ntuple file"         )
        ("output"     , po::value<std::string>(&output_file) , "output ntuple file"        )
        ("cms2_tag"   , po::value<std::string>(&cms2_tag)    , "CMS2 tag"                  )
        ("xsec"       , po::value<float>(&xsec)              , "cross section"             )
        ("kfactor"    , po::value<float>(&kfactor  )         , "k factor"                  )
        ("filter_eff" , po::value<float>(&filter_eff)        , "filter efficiency"         )
        ("num_events" , po::value<int>(&num_events)          , "number of generated events")
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
        cout << desc << "\n";
        return 1;
    }

    if (vm.count("help")) {
        cout << desc << "\n";
        return 1;
    }

    cout << "inputs:" << endl;
    cout << "input_file  :\t" << input_file  << endl;
    cout << "output_file :\t" << output_file << endl;
    cout << "CMS2 tag    :\t" << cms2_tag    << endl;
    cout << "xsec        :\t" << xsec        << endl;
    cout << "kfactor     :\t" << kfactor     << endl;
    cout << "filter_eff  :\t" << filter_eff  << endl;
    cout << "num_events  :\t" << num_events  << endl;

    // do it 
    // -------------------------------------------------------------------------------------------------//

    AddCMS2BranchesWithTag(input_file, output_file, cms2_tag, num_events, xsec, kfactor, filter_eff); 
    return 0;
}
catch (std::exception& e)
{
    cerr << "ewkino2012_ss_analysis failed..." << endl;
    cerr << e.what() << endl;
    return 1;
}

