#ifndef TRILEPZ2012WRAPPER_H
#define TRILEPZ2012WRAPPER_H

// simple wrapper to samesignbtag to use with at::ScanChain()

#include "TRILEPZ2012.h"

void Init(TRILEPZ2012& trilepz, TTree* tree);
void GetEntry(TRILEPZ2012& trilepz, long event);
bool IsRealData(TRILEPZ2012& trilepz);
void LoadAllBranches(TRILEPZ2012& trilepz);
unsigned int Run(TRILEPZ2012& trilepz);
unsigned int LumiBlock(TRILEPZ2012& trilepz);
unsigned int Event(TRILEPZ2012& trilepz);

#endif //#define TRILEPZ2012WRAPPER_H
