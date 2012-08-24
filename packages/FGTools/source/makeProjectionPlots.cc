#include <iostream>

#include "makeProjectionPlots.h"
#include "eff.h"

#include "TH1.h"
#include "TAxis.h"
#include "TArrayD.h"
#include "TCanvas.h"
#include "TString.h"

#include <math.h>
#include <cstdlib>

using namespace std;

TH1F* makeProjectionPlots (TH2F* hist, std::string axis) {
 	 
    if (axis != "X" && axis != "Y") {
        std::cout << "You've requested a projection onto a non-existent axis.  Exiting." << std::endl;
        exit(1);
    }

    // need to add 2 to number of bins to account for underflow/overflow
    int nxbins = hist->GetNbinsX();
    int nybins = hist->GetNbinsY();
    if (axis == "Y") {
        nxbins = hist->GetNbinsY();
        nybins = hist->GetNbinsX();
    }

    TAxis* xaxis   = hist->GetXaxis();
    if (axis == "Y")
        xaxis = hist->GetYaxis();

    const TArrayD* xbins = xaxis->GetXbins();
    const int xsize = xbins->GetSize();
    Double_t binsx[xsize];
    for (int ibin = 0; ibin < xsize; ibin++)
        binsx[ibin] = xbins->At(ibin);

    TH1F* xproj = new TH1F("proj", "proj", xsize-1, binsx);
    xproj->GetXaxis()->ImportAttributes(xaxis);

    // for each bin in x, sum column in y
    for (int ix = 1; ix < nxbins+1; ix++) {

        Double_t sum = 0.;
        Double_t error = 0.;
        for (int iy = 1; iy < nybins+1; iy++) {
			   			   
            int bin = hist->GetBin(ix, iy); // get absolute bin number from x,y bin count
            if (axis == "Y")
                bin = hist->GetBin(iy, ix);
            sum += hist->GetBinContent(bin);
            error += hist->GetBinError(bin) * hist->GetBinError(bin);
        }
        xproj->SetBinContent(ix, sum/nybins);
        xproj->SetBinError(ix, sqrt(error));
    }

    return xproj;
}

TH1F* makeProjectionPlots (TH2F* numhist, TH2F* denhist, std::string axis) {
	 
    if (axis != "X" && axis != "Y") {
        std::cout << "You've requested a projection onto a non-existent axis.  Exiting." << std::endl;
        exit (1);
    }

    // need to add 2 to number of bins to account for underflow/overflow
    int nxbins = numhist->GetNbinsX();
    int nybins = numhist->GetNbinsY();
    if (axis == "Y") {
        nxbins = numhist->GetNbinsY();
        nybins = numhist->GetNbinsX();
    }

    TAxis* xaxis   = numhist->GetXaxis();
    if (axis == "Y")
        xaxis = numhist->GetYaxis();

    const TArrayD* xbins = xaxis->GetXbins();
    double* binsx = NULL;
    int xsize = xbins->GetSize();     
    binsx = new double[xsize];
    for (int ibin = 0; ibin < xsize; ibin++)
        binsx[ibin] = xbins->At(ibin);

    TH1F* numproj = new TH1F("numproj", "numproj", xsize-1, binsx);
    numproj->GetXaxis()->ImportAttributes(xaxis);

    TH1F* denproj = new TH1F("denproj", "denproj", xsize-1, binsx);
    denproj->GetXaxis()->ImportAttributes(xaxis);

    // for each bin in x, sum column in y
    for (int ix = 1; ix < nxbins+1; ix++) {

        Double_t numsum = 0.;
        Double_t numerror = 0.;
        Double_t densum = 0.;
        Double_t denerror = 0.;
        for (int iy = 1; iy < nybins+1; iy++) {
			   			   
            int bin = numhist->GetBin(ix, iy); // get absolute bin number from x,y bin count
            if (axis == "Y")
                bin = numhist->GetBin(iy, ix);
            numsum += numhist->GetBinContent(bin);
            numerror += numhist->GetBinError(bin) * numhist->GetBinError(bin);	
            densum += denhist->GetBinContent(bin);
            denerror += denhist->GetBinError(bin) * denhist->GetBinError(bin);
        }
        numproj->SetBinContent(ix, numsum);
        numproj->SetBinError(ix, sqrt(numerror));
        denproj->SetBinContent(ix, densum);
        denproj->SetBinError(ix, sqrt(denerror));
    }

    TString histname = numhist->GetName();
    TString axisname = axis;
    axisname.ToLower();
    histname += Form("_%s%s", axisname.Data(), "proj"); 
    TH1F* proj = eff(denproj, numproj, histname.Data());
    proj->GetXaxis()->ImportAttributes(xaxis);

    delete numproj;
    delete denproj;

    return proj;
}

void compareRFhists (TH2F* old_hist, TH2F* new_hist) {

    TH2F* diff_hist = (TH2F*)new_hist->Clone();
    diff_hist->Add(old_hist, -1.);

    TCanvas* cx = new TCanvas();
    cx->cd();
    diff_hist->Draw("colz");
}

void clearHists (TH2F* hist) {

    delete hist;
}
