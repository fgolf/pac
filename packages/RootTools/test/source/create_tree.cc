// This program is to create a simple root Tree to make some realistic plots
// for test RootTools.

// c++
#include <iostream>

// ROOT 
#include "TTree.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TSystem.h"

// pythia 8 header
#include "Pythia.h"

const size_t num_events = 10000;

int main()
try
{
    using namespace std;

    // set up the path for the output
    const string PAC(gSystem->Getenv("PAC"));
    const string path = PAC + "/packages/RootTools/test";
    //cout << "Current path is set to:\t" << path << endl;

    //Create pythia8 object
    Pythia8::Pythia pythia;
    pythia.settings.resetAll();

    //Set the initial state and other process independent parameters
    pythia.readFile(path + "/data/cards/general_param.card");

    // Proess specific card
    pythia.readFile(path + "/data/cards/drellyan.card");

    // Initialize
    pythia.init();

    // Creat the Tree
    TTree* tree = new TTree("tree", "Tree of resonant events");

    // Declare the branch variables
    TLorentzVector* res_p4  = new TLorentzVector;
    TLorentzVector* mu1_p4  = new TLorentzVector;
    TLorentzVector* mu2_p4  = new TLorentzVector;
    TLorentzVector* mu12_p4 = new TLorentzVector;

    // Set the branches
    tree->Branch("res" , "TLorentzVector", &res_p4 , 32000, 0);
    tree->Branch("mu1" , "TLorentzVector", &mu1_p4 , 32000, 0);
    tree->Branch("mu2" , "TLorentzVector", &mu2_p4 , 32000, 0);
    tree->Branch("mu12", "TLorentzVector", &mu12_p4, 32000, 0);

    // loop over num_events and create events
    for(size_t event = 0; event < num_events; event++)
    {
        // generate a new event
        if( !pythia.next() ) continue;

        //loop over particles
        for(int i = 0; i < pythia.event.size(); i++)
        {
            // the ith particles from the event
            Pythia8::Particle& particle = pythia.event[i];

            // only keep Z's and mu's from Z's
            bool is_resonance = particle.id() == 23 && abs(pythia.event[particle.daughter1()].id()) == 13;

            // select only the resonance 4 vector
            if (is_resonance)
            {
                // set resonance p4
                res_p4->SetXYZT(particle.px(), particle.py(), particle.pz(), particle.e());

                // set daughter p4
                Pythia8::Particle& daughter1 = pythia.event[particle.daughter1()];  
                Pythia8::Particle& daughter2 = pythia.event[particle.daughter2()];  

                // mu1 is higheer pt mu
                if (daughter1.pT() >= daughter2.pT())
                {
                    mu1_p4->SetXYZT(daughter1.px(), daughter1.py(), daughter1.pz(), daughter1.e());
                    mu2_p4->SetXYZT(daughter2.px(), daughter2.py(), daughter2.pz(), daughter2.e());
                }
                else
                {
                    mu1_p4->SetXYZT(daughter2.px(), daughter2.py(), daughter2.pz(), daughter2.e());
                    mu2_p4->SetXYZT(daughter1.px(), daughter1.py(), daughter1.pz(), daughter1.e());
                }

                // invariant mass of daughters
                *mu12_p4 = *mu1_p4 + *mu2_p4;
                

                // Fill the tree
                tree->Fill();
            }
            else
            {
                continue;
            }
        }
    }
   
    // save to a root file
    TFile* file = new TFile(( path + "/data/trees/drellyan.root").c_str(), "RECREATE");
    tree->Print();
    tree->Write();
    file->Close();

    // delete pointers
    delete res_p4;
    delete mu1_p4;
    delete mu2_p4;
    delete mu12_p4;
    delete tree;
    delete file;

    return 0;
}
catch(...)
{
}
