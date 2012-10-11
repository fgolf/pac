#ifndef OUTREACHBABYWRAPPER_H
#define OUTREACHBABYWRAPPER_H

// simple wrapper to samesignbtag to use with at::ScanChain()

#include "OutreachBaby.h"

void Init(OutreachBaby&, TTree* tree);
void GetEntry(OutreachBaby&, long event);
bool IsRealData(OutreachBaby&);
void LoadAllBranches(OutreachBaby&);
unsigned int Run(OutreachBaby&);
unsigned int LumiBlock(OutreachBaby&);
unsigned int Event(OutreachBaby&);

#endif //#efine OUTREACHBABYWRAPPER_H
