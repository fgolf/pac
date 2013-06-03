#ifndef AT_SIGNIFICANCE_H
#define AT_SIGNIFICANCE_H

#include "TMath.h"

namespace at
{
    // return the simple signifcance 
    // note: uncertainty is absolute
    float SimpleSignficance(const float N_sig, const float N_bkgd, const float unc_bkgd);

// from http://www.pd.infn.it/~dorigo/nSigma.cc
//--------------------------------------------------------------------------------------------
//
// nSigma.cc
// v1.1, updated by Greg Landsberg 5/21/09
//
// This Root code computes the probability for the expectd background Bkgr with the FRACTIONAL
// uncertainty sFfrac (i.e., B = Bkgr*(1 +/- sBfrac)) to fluctuate to or above the
// observed number of events nobs
//
// To find 3/5 sigma evidence/discovery points, one should use nobs = int(<S+B>),
// where <S+B> is the expected mean of the signal + background.
//
// Usage: NSigma(Double_t Bkgr, Int_t nobs, Double_t sBfrac) returns the one sided probability
// of an upward backround fluctuations, expressed in Gaussian sigmas. It is suggested to run
// this code in the compiled mode, i.e. .L nSigma.cc++
//
// 5 sigma corresponds to the p-value of 2.85E-7; 3 sigma corresponds to p-value of 1.35E-3
//
//---------------------------------------------------------------------------------------------
    Double_t NSigma(Double_t Bkgr, Int_t nobs, Double_t sBfrac);

} // end namespace at

#endif // AT_SIGNIFICANCE_H
