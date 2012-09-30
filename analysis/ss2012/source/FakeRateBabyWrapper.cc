#include "FakeRateBaby.h"

void Init(FakeRateBaby& fake_rate_baby, TTree* tree)
{
    fake_rate_baby.Init(tree);
}

void GetEntry(FakeRateBaby& fake_rate_baby, long event)
{
    fake_rate_baby.GetEntry(event);
}

void LoadAllBranches(FakeRateBaby& fake_rate_baby)
{
    fake_rate_baby.LoadAllBranches();
}

bool IsRealData(FakeRateBaby& fake_rate_baby)
{
    //return fake_rate_baby.is_real_data();
    return true;  // need to add this branch 
}

unsigned int Run(FakeRateBaby& fake_rate_baby)
{
    return fake_rate_baby.run();
}

unsigned int LumiBlock(FakeRateBaby& fake_rate_baby)
{
    return fake_rate_baby.ls();
}

unsigned int Event(FakeRateBaby& fake_rate_baby)
{
    return fake_rate_baby.evt();
}

