#ifndef VTXREWEIGHT_H
#define VTXREWEIGHT_H

#include "TH1.h"

float vtxweight( bool isData = false , int nvtx = 1 );
void set_vtxreweight_rootfile ( const char* filename = "vtxreweight.root", bool verbose = false );
static TH1F* vtxreweight_hist;

#endif

