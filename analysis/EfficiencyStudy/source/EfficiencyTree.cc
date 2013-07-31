#include "EfficiencyTree.h"

EfficiencyTree::EfficiencyTree ()
{
}

EfficiencyTree::EfficiencyTree (const std::string &prefix)
    : DileptonTree(prefix)
{
}

void EfficiencyTree::Reset()
{
    event_info.Reset();
    DileptonTree::Reset();

    trig_hpt = false;
    trig_lpt = false;
    trig_vpt = false;
}

void EfficiencyTree::SetBranches(TTree &tree)
{
    event_info.SetBranches(tree);
    DileptonTree::SetBranches(tree);

    tree.Branch("trig_hpt", &trig_hpt, "trig_hpt/O");
    tree.Branch("trig_lpt", &trig_lpt, "trig_lpt/O");
    tree.Branch("trig_vpt", &trig_vpt, "trig_vpt/O");
}
