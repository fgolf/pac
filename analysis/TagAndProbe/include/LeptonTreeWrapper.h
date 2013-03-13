#ifndef LEPTONTREEWRAPPER_H
#define LEPTONTREEWRAPPER_H

// simple wrapper to samesignbtag to use with at::ScanChain()

#include "LeptonTree.h"

void Init(LeptonTree& samesignbtag, TTree* tree);
void GetEntry(LeptonTree& samesignbtag, long event);
bool IsRealData(LeptonTree& samesignbtag);
void LoadAllBranches(LeptonTree& samesignbtag);
unsigned int Run(LeptonTree& samesignbtag);
unsigned int LumiBlock(LeptonTree& samesignbtag);
unsigned int Event(LeptonTree& samesignbtag);

#endif //#efine LEPTONTREEWRAPPER_H
