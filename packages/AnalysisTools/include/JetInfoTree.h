#ifndef JETINFOTREE_H
#define JETINFOTREE_H

#include <string>
#include <vector>
#include "Math/LorentzVector.h"

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
        void FillCommon(const std::vector<int>& mu_indices, const std::vector<int>& el_indices);
        void FillCommon(int hyp_index);

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
};

#endif // JETINFOTREE_H
