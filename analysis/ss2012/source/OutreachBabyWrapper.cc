#include "OutreachBaby.h"

void Init(OutreachBaby& outreach_baby, TTree* tree)
{
    outreach_baby.Init(tree);
}

void GetEntry(OutreachBaby& outreach_baby, long event)
{
    outreach_baby.GetEntry(event);
}

void LoadAllBranches(OutreachBaby& outreach_baby)
{
    outreach_baby.LoadAllBranches();
}

bool IsRealData(OutreachBaby& outreach_baby)
{
    return outreach_baby.is_real_data();
}

unsigned int Run(OutreachBaby& outreach_baby)
{
    return outreach_baby.run();
}

unsigned int LumiBlock(OutreachBaby& outreach_baby)
{
    return outreach_baby.ls();
}

unsigned int Event(OutreachBaby& outreach_baby)
{
    return outreach_baby.evt();
}

