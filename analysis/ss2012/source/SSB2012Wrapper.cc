#include "SSB2012.h"

void Init(SSB2012& samesignbtag, TTree* tree)
{
    samesignbtag.Init(tree);
}

void GetEntry(SSB2012& samesignbtag, long event)
{
    samesignbtag.GetEntry(event);
}

void LoadAllBranches(SSB2012& samesignbtag)
{
    samesignbtag.LoadAllBranches();
}

bool IsRealData(SSB2012& samesignbtag)
{
    return samesignbtag.is_real_data();
}

unsigned int Run(SSB2012& samesignbtag)
{
    return samesignbtag.run();
}

unsigned int LumiBlock(SSB2012& samesignbtag)
{
    return samesignbtag.ls();
}

unsigned int Event(SSB2012& samesignbtag)
{
    return samesignbtag.evt();
}

