#include <iostream>
#include "TChain.h"
#include "TSystem.h"
#ifndef __RTINT__
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"
#endif

// CMSSW includes
//#include "DataFormats/TrackReco/interface/Track.h"

using namespace std;

void set_aliases(TTree* tree)
{
    tree->SetAlias("tk", "recoTracks_generalTracks__RECO.obj");
    tree->SetAlias("gp", "recoGenParticles_genParticles__HLT.obj");
    return;
}

void test_fwlite()
{
    // Set FWLite
    // -------------------------------------------------------------------------------------------------//
    cout << "working" << endl;

#ifndef __RTINT__
    // load framework libraries
    cout << "loading FWLite" << endl;
    gSystem->Load("libFWCoreFWLite");
    AutoLibraryLoader::enable();
#endif

    //cout << "working" << endl;
   TChain* e = new TChain("Events");
   e->Add("$HOME/data/dymumu.root");
   set_aliases(e);
   cout << e->GetEntries("recoTracks_generalTracks__RECO.@obj.size()>100") << endl;
   cout << e->GetEntries() << endl;
}
    

#ifndef __CINT__
int main()
{
    test_fwlite();
    return 0;
}
#endif
