#ifndef RPVSTOP2012WRAPPER_OS_H
#define RPVSTOP2012WRAPPER_OS_H

// simple wrapper to ewk12ss to use with at::ScanChain()

#include "RPVSTOP2012_OS.h"

void Init(RPVSTOP2012_SS& rpvstop12ss, TTree* tree);
void GetEntry(RPVSTOP2012_SS& rpvstop12ss, long event);
bool IsRealData(RPVSTOP2012_SS& rpvstop12ss);
void LoadAllBranches(RPVSTOP2012_SS& rpvstop12ss);
unsigned int Run(RPVSTOP2012_SS& rpvstop12ss);
unsigned int LumiBlock(RPVSTOP2012_SS& rpvstop12ss);
unsigned int Event(RPVSTOP2012_SS& rpvstop12ss);

#endif //#efine RPVSTOP2012_SSWRAPPER_H
