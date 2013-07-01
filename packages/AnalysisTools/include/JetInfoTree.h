#ifndef JETINFOTREE_H
#define JETINFOTREE_H

#include <string>
#include <vector>
#include "Math/LorentzVector.h"
#include "at/JetInfo.h"

// forward declaration
class TTree;

// typedefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef std::vector<LorentzVector> vecLorentzVector;
typedef std::vector<float> vecd;
typedef std::vector<bool> vecb;
typedef std::vector<int> veci;

class JetInfoTree
{
    public:
        // construct/destroy:
        JetInfoTree();
        JetInfoTree(const std::string &prefix = "", const std::string &postfix = "");
        virtual ~JetInfoTree() {}

        // methods:
        void Reset();
        void SetBranches(TTree &tree);

        template <typename Function>
        void FillCommon
        (
            const at::JetBaseSelectionArgs& jet_args,
            Function jet_election
        );

    private:

        // members:
        std::string m_prefix;
        std::string m_postfix;

    public:

        // branch objects
        // ----------------------------------------- //

        // sum jet pt
        float ht;

        // jets
        int njets;
        float jets_dr12;
        vecLorentzVector vjets_p4;
        vecLorentzVector vjets_mc3p4;
        vecLorentzVector vjets_nearjet_p4;
        vecd vjets_nearjet_dr;
        vecd vjets_disc;
        vecb vjets_btagged;
        veci vjets_mcflavor_phys;
        veci vjets_mcflavor_algo;
        veci vjets_momid;
        veci vjets_mc3id;

        // btagged jets
        int nbtags;
        float bjets_dr12;
        vecLorentzVector vbjets_p4;
        vecLorentzVector vbjets_mc3p4;
        vecLorentzVector vbjets_nearjet_p4;
        vecd vbjets_nearjet_dr;
        vecd vbjets_disc;
        veci vbjets_mcflavor_phys;
        veci vbjets_mcflavor_algo;
        veci vbjets_mc3id;
        veci vbjets_momid;

        // generator level jets
        vecLorentzVector vgenjets_p4;

    private: 

};

// template function definitiions
#include "JetInfoTree.impl.h"

#endif // JETINFOTREE_H
