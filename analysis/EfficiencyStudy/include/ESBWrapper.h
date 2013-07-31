#ifndef ESBWRAPPER_H
#define ESBWRAPPER_H

// simple wrapper to samesignbtag to use with at::ScanChain()

#include "ESB.h"

void Init(ESB& samesignbtag, TTree* tree);
void GetEntry(ESB& samesignbtag, long event);
bool IsRealData(ESB& samesignbtag);
void LoadAllBranches(ESB& samesignbtag);
unsigned int Run(ESB& samesignbtag);
unsigned int LumiBlock(ESB& samesignbtag);
unsigned int Event(ESB& samesignbtag);

#endif //#efine ESBWRAPPER_H
