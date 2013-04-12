#include "EWKINO2012_SS.h"

void Init(EWKINO2012_SS& ewk12ss, TTree* tree)
{
    ewk12ss.Init(tree);
}

void GetEntry(EWKINO2012_SS& ewk12ss, long event)
{
    ewk12ss.GetEntry(event);
}

void LoadAllBranches(EWKINO2012_SS& ewk12ss)
{
    ewk12ss.LoadAllBranches();
}

bool IsRealData(EWKINO2012_SS& ewk12ss)
{
    return ewk12ss.is_real_data();
}

unsigned int Run(EWKINO2012_SS& ewk12ss)
{
    return ewk12ss.run();
}

unsigned int LumiBlock(EWKINO2012_SS& ewk12ss)
{
    return ewk12ss.ls();
}

unsigned int Event(EWKINO2012_SS& ewk12ss)
{
    return ewk12ss.evt();
}
