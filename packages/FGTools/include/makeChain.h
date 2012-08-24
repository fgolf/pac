#ifndef MAKECHAIN_H
#define MAKECHAIN_H

#include "TChain.h"

TChain *makeChain (const char *glob, const char *treename = "Events", TChain* chain_in = 0, bool verbose = false);
TChain *makeChain_command (const char *cmd, const char *treename = "Events", bool verbose = false);

#endif
