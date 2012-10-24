#include "TRILEPZ2012.h"

void Init(TRILEPZ2012& trilepz, TTree* tree)
{
    trilepz.Init(tree);
}

void GetEntry(TRILEPZ2012& trilepz, long event)
{
    trilepz.GetEntry(event);
}

void LoadAllBranches(TRILEPZ2012& trilepz)
{
    trilepz.LoadAllBranches();
}

bool IsRealData(TRILEPZ2012& trilepz)
{
    return trilepz.is_real_data();
}

unsigned int Run(TRILEPZ2012& trilepz)
{
    return trilepz.run();
}

unsigned int LumiBlock(TRILEPZ2012& trilepz)
{
    return trilepz.ls();
}

unsigned int Event(TRILEPZ2012& trilepz)
{
    return trilepz.evt();
}

