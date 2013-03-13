#include "LeptonTree.h"

void Init(LeptonTree& samesignbtag, TTree* tree)
{
    samesignbtag.Init(tree);
}

void GetEntry(LeptonTree& samesignbtag, long event)
{
    samesignbtag.GetEntry(event);
}

void LoadAllBranches(LeptonTree& samesignbtag)
{
    samesignbtag.LoadAllBranches();
}

bool IsRealData(LeptonTree& samesignbtag)
{
    return false; // no flag in the ntuple
}

unsigned int Run(LeptonTree& samesignbtag)
{
    return samesignbtag.run();
}

unsigned int LumiBlock(LeptonTree& samesignbtag)
{
    return samesignbtag.lumi();
}

unsigned int Event(LeptonTree& samesignbtag)
{
    return samesignbtag.event();
}
