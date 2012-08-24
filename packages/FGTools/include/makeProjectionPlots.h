#ifndef MAKEPROJECTIONPLOTS_H
#define MAKEPROJECTIONPLOTS_H

#include <string>
#include "TH1.h"
#include "TH2.h"

TH1F* makeProjectionPlots (TH2F*, std::string="X");
TH1F* makeProjectionPlots (TH2F*, TH2F*, std::string="X");
void compareRFhists (TH2F*, TH2F*);
void clearHists (TH2F*);

#endif
