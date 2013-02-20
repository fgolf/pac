#include "TH2.h"
#include "TFile.h"
#include "rt/RootTools.h"

float ChargeFlipRate(const float pt, const float eta)
{
    if (fabs(eta) < 1.0)
    {
        if      (fabs(pt) < 25)  {return 6.05313e-5; }
        else if (fabs(pt) < 50)  {return 8.98131e-5; }
        else if (fabs(pt) < 75)  {return 7.61506e-5; }
        else if (fabs(pt) < 100) {return 7.71302e-5; }
        else if (fabs(pt) < 125) {return 0.000104576;}
        else                     {return 0.000137569;}
    }
    if (fabs(eta) < 2.0)
    {
        if      (fabs(pt) < 25)  {return 0.000137621;}
        else if (fabs(pt) < 50)  {return 0.000285069;}
        else if (fabs(pt) < 75)  {return 0.000496877;}
        else if (fabs(pt) < 100) {return 0.000813807;}
        else if (fabs(pt) < 125) {return 0.00108998; }
        else                     {return 0.00120798; }
    }
    else
    {
        if      (fabs(pt) < 25)  {return 8.1182e-5;  }
        else if (fabs(pt) < 50)  {return 0.000466018;}
        else if (fabs(pt) < 75)  {return 0.000966014;}
        else if (fabs(pt) < 100) {return 0.00149879; }
        else if (fabs(pt) < 125) {return 0.00158556; }
        else                     {return 0.00363156; }
    }
}

float ChargeFlipRateError(const float pt, const float eta)
{
    if (fabs(eta) < 1.0)
    {
        if      (fabs(pt) < 25)  {return 1.16489e-5;}
        else if (fabs(pt) < 50)  {return 5.73769e-6;}
        else if (fabs(pt) < 75)  {return 8.46085e-5;}
        else if (fabs(pt) < 100) {return 1.32272e-5;}
        else if (fabs(pt) < 125) {return 2.28191e-5;}
        else                     {return 3.81522e-5;}
    }
    if (fabs(eta) < 2.0)
    {
        if      (fabs(pt) < 25)  {return 2.29353e-5; }
        else if (fabs(pt) < 50)  {return 1.43232e-5; }
        else if (fabs(pt) < 75)  {return 3.23359e-5; }
        else if (fabs(pt) < 100) {return 6.75555e-5; }
        else if (fabs(pt) < 125) {return 0.000119576;}
        else                     {return 0.000188541;}
    }
    else
    {
        if      (fabs(pt) < 25)  {return 3.63042e-5;}
        else if (fabs(pt) < 50)  {return 3.96608e-5;}
        else if (fabs(pt) < 75)  {return 0.000110034;}
        else if (fabs(pt) < 100) {return 0.000256847;}
        else if (fabs(pt) < 125) {return 0.000439406;}
        else                     {return 0.00109297;}
    }
}

void ConvertFlipRateToHisto(const std::string& outfile)
{
    TFile file(outfile.c_str(), "RECREATE");
    file.cd();

    //const float xbins[9] = { 0.0, 0.5, 1.0, 1.479, 1.8, 2.0, 2.1, 2.2, 2.4 };
    //const unsigned int nbinsx = 8;
    //const float ybins[18] = { 10., 20., 25., 30., 35., 40., 45., 50., 55., 60., 65., 70., 75., 80., 85., 90., 95., 100. };
    //const unsigned int nbinsy = 17;
    const float xbins[4] = {0.0, 1.0, 2.0, 2.4};
    const unsigned int nbinsx = 3;
    const float ybins[7] = {0.0, 25.0, 50.0, 75.0, 100.0, 125.0, 150.0};
    const unsigned int nbinsy = 6;

    TH2F flipRate("flipRate", "SameSign Electron Charge Flip Rate;|#eta|;p_{T} (GeV)", nbinsx, xbins, nbinsy, ybins);
    for (unsigned int ix = 1; ix < nbinsx+1; ix++) 
    {
        for (unsigned int iy = 1; iy < nbinsy+1; iy++) 
        {
            const float eta   = (xbins[ix] + xbins[ix-1])/2.0;
            const float pt    = (ybins[iy] + ybins[iy-1])/2.0;
            const float rate  = ChargeFlipRate(pt, eta);
            const float error = ChargeFlipRateError(pt, eta);

            flipRate.SetBinContent(ix, iy, rate);
            flipRate.SetBinError(ix, iy, error);
        }
    }

    flipRate.Write();
    file.Close();
}

