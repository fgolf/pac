#ifndef EWKINO2012WRAPPER_SS_H
#define EWKINO2012WRAPPER_SS_H

// simple wrapper to ewk12ss to use with at::ScanChain()

#include "EWKINO2012_SS.h"

void Init(EWKINO2012_SS& ewk12ss, TTree* tree);
void GetEntry(EWKINO2012_SS& ewk12ss, long event);
bool IsRealData(EWKINO2012_SS& ewk12ss);
void LoadAllBranches(EWKINO2012_SS& ewk12ss);
unsigned int Run(EWKINO2012_SS& ewk12ss);
unsigned int LumiBlock(EWKINO2012_SS& ewk12ss);
unsigned int Event(EWKINO2012_SS& ewk12ss);

#endif //#efine EWKINO2012_SSWRAPPER_H
