#ifndef SAMESIGNTREE_H
#define SAMESIGNTREE_H

#include "at/Sample.h"
#include <vector> 
#include "Math/LorentzVector.h"
#include "at/DileptonHypType.h"
#include "DileptonTree.h"
#include "EventInfoTree.h"
#include "LooperTypes.h"

// forward declaration
class TTree;

// typedefs
typedef std::vector<LorentzVector> vecLorentzVector;
typedef std::vector<float> vecd;
typedef std::vector<int> veci;

struct EfficiencyTree : public DileptonTree
{
    // constructors and destructor
    EfficiencyTree ();
    EfficiencyTree (const std::string &prefix);
    virtual ~EfficiencyTree () {}

    void Reset();
    void SetBranches(TTree& tree);
    void SetAliases(TTree& tree) const;

public:

    // event level info
    EventInfoTree event_info;

    // trigger
    bool trig_hpt;  // SS high pt
    bool trig_lpt;  // SS low pt
    bool trig_vpt;  // SS very low pt
};

#endif
