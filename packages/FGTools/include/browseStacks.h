#ifndef BROWSESTACKS_H
#define BROWSESTACKS_H


#include "TH1.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TString.h"
#include <set>
#include "getMyHistosNames.h"
#include "histtools.h"

using namespace std;

double GetMinimum(const vector<TH1F*> &v_hists);
TLegend* makeLegend(const vector<TH1F*> &v_hists, vector<TString> v_legEntries, bool drawLogY, TString histName);
TPaveText *getPaveText(const vector<TH1F*> &v_hists, int i_channel); //call this after makeLegend please
void browseStacks(vector<TString> v_samples, vector<Color_t> v_colors, TString outfile, vector<TString> v_legEntries, bool drawLogY = false, vector<Style_t> v_style = vector<Style_t>(), bool plotData = false);

#endif
