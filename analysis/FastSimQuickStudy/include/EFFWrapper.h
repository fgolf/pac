#ifndef EFFWRAPPER_H
#define EFFWRAPPER_H

// simple wrapper to eff_obj to use with at::ScanChain()

#include "EFF.h"

void Init(EFF& samesignbtag, TTree* tree);
void GetEntry(EFF& samesignbtag, long event);
bool IsRealData(EFF& samesignbtag);
void LoadAllBranches(EFF& samesignbtag);
unsigned int Run(EFF& samesignbtag);
unsigned int LumiBlock(EFF& samesignbtag);
unsigned int Event(EFF& samesignbtag);

#endif // EFFWRAPPER_H
