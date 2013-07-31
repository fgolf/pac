#include "ESB.h"

void Init(ESB& samesignbtag, TTree* tree)
{
    samesignbtag.Init(tree);
}

void GetEntry(ESB& samesignbtag, long event)
{
    samesignbtag.GetEntry(event);
}

void LoadAllBranches(ESB& samesignbtag)
{
    samesignbtag.LoadAllBranches();
}

bool IsRealData(ESB& samesignbtag)
{
    return samesignbtag.is_real_data();
}

unsigned int Run(ESB& samesignbtag)
{
    return samesignbtag.run();
}

unsigned int LumiBlock(ESB& samesignbtag)
{
    return samesignbtag.ls();
}

unsigned int Event(ESB& samesignbtag)
{
    return samesignbtag.evt();
}

