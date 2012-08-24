#include "TH2.h"
#include "fliprate_egun.cc" // get this from UserCode/JRibnik/NtupleMacros/Tools
#include "eff2.C"
#include "TFile.h"

void convertFlipRateToHisto (const char* outfile) {

    TFile* file = new TFile(outfile, "RECREATE");
    file->cd();

    float xbins[9] = { 0.0, 0.5, 1.0, 1.479, 1.8, 2.0, 2.1, 2.2, 2.4 };
    unsigned int nbinsx = 8;
    float ybins[18] = { 10., 20., 25., 30., 35., 40., 45., 50., 55., 60., 65., 70., 75., 80., 85., 90., 95., 100. };
    unsigned int nbinsy = 17;

    TH2F* flipRateNum = new TH2F("flipRateNum", "flipRateNum", nbinsx, xbins, nbinsy, ybins);
    flipRateNum->GetXaxis()->SetTitle("#eta");
    flipRateNum->GetYaxis()->SetTitle("p_{T} (GeV)");
    flipRateNum->SetTitle("");
    flipRateNum->Sumw2();

    TH2F* flipRateDen = new TH2F("flipRateDen", "flipRateDen", nbinsx, xbins, nbinsy, ybins);
    flipRateDen->GetXaxis()->SetTitle("#eta");
    flipRateDen->GetYaxis()->SetTitle("p_{T} (GeV)");
    flipRateDen->SetTitle("");
    flipRateDen->Sumw2();

    for (unsigned int ix = 1; ix < nbinsx+1; ix++) {
        for (unsigned int iy = 1; iy < nbinsy+1; iy++) {

            float eta = (xbins[ix] + xbins[ix-1])/2.;
            float pt  = (ybins[iy] + ybins[iy-1])/2.;

            float den = getSingleEleDenom(pt, eta);
            float num = getSingleEleNum(pt, eta);

            flipRateNum->SetBinContent(ix, iy, num);
            flipRateNum->SetBinError(ix, iy, sqrt(num));
            flipRateDen->SetBinContent(ix, iy, den);
            flipRateDen->SetBinError(ix, iy, sqrt(den));
        }
    }

    TH2F* flipRate = eff2(flipRateDen, flipRateNum, "flipRate");
    // check if any bins are zero and set the errors "appropriately"
    for (unsigned int ix = 1; ix < nbinsx+1; ix++) {
        for (unsigned int iy = 1; iy < nbinsy+1; iy++) {

            float fliprate = flipRate->GetBinContent(ix, iy);
            if (fliprate > 0)
                continue;

            float denom = flipRateDen->GetBinContent(ix, iy);
            flipRate->SetBinError(ix, iy, 1./denom);
        }
    }    

    flipRate->Write();
}
