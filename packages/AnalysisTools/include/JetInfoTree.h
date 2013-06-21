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

        int njets;
        vecLorentzVector vjets_p4;
        int nbtags;
        vecLorentzVector vbjets_p4;

    private: 

};

// template function definitiions
#include "JetInfoTree.impl.h"

#endif // JETINFOTREE_H
