#ifndef SSB2012WRAPPER_H
#define SSB2012WRAPPER_H

// simple wrapper to samesignbtag to use with at::ScanChain()

#include "SSB2012.h"

void Init(SSB2012& samesignbtag, TTree* tree);
void GetEntry(SSB2012& samesignbtag, long event);
bool IsRealData(SSB2012& samesignbtag);
void LoadAllBranches(SSB2012& samesignbtag);
unsigned int Run(SSB2012& samesignbtag);
unsigned int LumiBlock(SSB2012& samesignbtag);
unsigned int Event(SSB2012& samesignbtag);

#endif //#efine SSB2012WRAPPER_H
