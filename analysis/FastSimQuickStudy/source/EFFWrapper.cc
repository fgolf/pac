#include "EFF.h"

void Init(EFF& eff_obj, TTree* tree)
{
    eff_obj.Init(tree);
}

void GetEntry(EFF& eff_obj, long event)
{
    eff_obj.GetEntry(event);
}

void LoadAllBranches(EFF& eff_obj)
{
    eff_obj.LoadAllBranches();
}

bool IsRealData(EFF& eff_obj)
{
    return eff_obj.is_real_data();
}

unsigned int Run(EFF& eff_obj)
{
    return eff_obj.run();
}

unsigned int LumiBlock(EFF& eff_obj)
{
    return eff_obj.ls();
}

unsigned int Event(EFF& eff_obj)
{
    return eff_obj.evt();
}
