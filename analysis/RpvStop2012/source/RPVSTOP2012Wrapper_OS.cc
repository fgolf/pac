#include "RPVSTOP2012_OS.h"

void Init(RPVSTOP2012_OS& rpvstop12os, TTree* tree)
{
    rpvstop12os.Init(tree);
}

void GetEntry(RPVSTOP2012_OS& rpvstop12os, long event)
{
    rpvstop12os.GetEntry(event);
}

void LoadAllBranches(RPVSTOP2012_OS& rpvstop12os)
{
    rpvstop12os.LoadAllBranches();
}

bool IsRealData(RPVSTOP2012_OS& rpvstop12os)
{
    return rpvstop12os.is_real_data();
}

unsigned int Run(RPVSTOP2012_OS& rpvstop12os)
{
    return rpvstop12os.run();
}

unsigned int LumiBlock(RPVSTOP2012_OS& rpvstop12os)
{
    return rpvstop12os.ls();
}

unsigned int Event(RPVSTOP2012_OS& rpvstop12os)
{
    return rpvstop12os.evt();
}
