#ifndef EFF2_H
#define EFF2_H

#include "TH2.h"

TH2F* eff2(TH2F* h1, TH2F* h2, const char* name="eff");
TH2F* eff2(const char* name1, const char* name2, const char* name="eff");

#endif
