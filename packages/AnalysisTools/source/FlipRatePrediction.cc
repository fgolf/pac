#include "at/FlipRatePrediction.h"
#include "rt/RootTools.h"

using namespace rt;
using namespace std;

namespace at
{
    // FlipRatePrediction implementation
    // ----------------------------------------------------//

    // construct:
    FlipRatePrediction::FlipRatePrediction(TH2* flip_rate, float scale)
        : h_flip_rate(dynamic_cast<TH2*>(flip_rate->Clone()))
        , m_scale(scale)
    {
        if (not h_flip_rate)
        {
            throw std::runtime_error("ERROR -- FlipRatePrediction - h_flip_rate is NULL!");
        }

        // take ownwership of the hists
        h_flip_rate->SetDirectory(0);
    }

    // methods:
    Pred FlipRatePrediction::SingleFlipPrediction(const TH2F* foHist)
    {
        double pred_total       = 0.0;
        double pred_error_total = 0.0;

        for (Int_t xbin = 1; xbin < h_flip_rate->GetXaxis()->GetNbins()+1; xbin++) 
        {
            for (Int_t ybin = 1; ybin < h_flip_rate->GetYaxis()->GetNbins()+1; ybin++) 
            {
                Int_t bin = h_flip_rate->GetBin(xbin, ybin);
                double nFOs = foHist->GetBinContent(bin);       // number of electrons from OS emu pairs in this eta, pt bin
                double nFOsError = foHist->GetBinError(bin);    // number error on the number of electrons from OS emu pairs for this eta, pt bin
                double FRvalue = h_flip_rate->GetBinContent(bin); // get value of flip rate for this eta, pt bin
                double FRerror = h_flip_rate->GetBinError(bin);   // get error on flip rate for this eta, pt bin

                // ok, have all of the inputs, calculate prediction and error for this bin
                // start with calculating fr/(1-fr) for this bin
                double fr = FRvalue / (1 - FRvalue);
                double pred = fr * nFOs;

                // now, need to get errors on these terms, be careful
                // start with hardest part, error on fr
                //
                // start with basic equation: (sigma_f/f)^2 = (sigma_num/num)^2 + (sigma_den/den)^2 - 2 * (sigma_num/num) * (sigma_den/den) * rho_num_den
                // f is the value fr from above
                // num is the value FRvalue from above
                // den is 1 - FRvalue
                //
                // sigma_num is the value FRerror from above
                // sigma_den is also the value FRerror from above (the error on 1 - A is just the error on A)
                // 
                // the numerator and denominator are completely anti-correlated, so rho_num_den is -1
                // 
                // combining all of this we can simplify the above to be
                //
                // (sigma_f/f)^2 = (sigma_num/num)^2 + (sigma_num/(1-num))^2 + 2 * sigma_num^2 * (1/num) * (1/(1-num))
                // (sigma_f/f)^2 = sigma_num^2 * [1/num + 1/(1-num)]^2
                // sigma_f = f * sigma_num * (1/(num * (1-num)))
                // sigma_f = sigma_num * (1 - num)^{-2}
                //
                double frError = FRerror * pow((1 - FRvalue), -2);

                // now that we have the error on fr/(1-fr), the error on the prediction is just the 
                // sum of this error and the error on FO count added in quadrature
                // (sigma_pred/pred)^2 = (sigma_fr/fr)^2 + (sigma_fo/fo)^2
                double pred_error = 0.0;
                if (nFOs > 0 && pred > 0.0)
                {
                    pred_error = pred * sqrt(pow(frError/fr, 2) + pow(nFOsError/nFOs, 2));
                }

                // now increment the total values
                pred_total += pred;
                pred_error_total += pow(pred_error, 2);
            }
        }

        pred_error_total = sqrt(pred_error_total);
        Pred result(pred_total, pred_error_total);

        return result;
    }

    Pred FlipRatePrediction::DoubleFlipPrediction(const TH2F* foHist)
    {
        const unsigned int NETA_BINS = 8;
        double pred_total       = 0.;
        double pred_error_total = 0.;
        const unsigned int MAX_XBIN = foHist->GetXaxis()->GetNbins()+1;
        const unsigned int MAX_YBIN = foHist->GetYaxis()->GetNbins()+1;
        for (unsigned int  xbin = 1; xbin < MAX_XBIN; xbin++) 
        {
            for (unsigned int ybin = 1; ybin < MAX_YBIN; ybin++) 
            {

                int xbin1 = ((xbin - 1) % NETA_BINS) + 1;
                int ybin1 = ((xbin - xbin1) / NETA_BINS) + 1;
                int xbin2 = ((ybin - 1) % NETA_BINS) + 1;
                int ybin2 = ((ybin - xbin2) / NETA_BINS) + 1;

                Int_t bin1 = h_flip_rate->GetBin(xbin1, ybin1);
                Int_t bin2 = h_flip_rate->GetBin(xbin2, ybin2);

                double nFOs = foHist->GetBinContent(xbin, ybin);      // number of electrons from OS ee pairs for this eta, pt bin
                double nFOsError = foHist->GetBinError(xbin, ybin);   // number error on number of electrons from OS ee pairs for this eta, pt bin
                double FRvalue1 = h_flip_rate->GetBinContent(bin1);   // get value of fake rate 1 for this eta, pt bin
                double FRerror1 = h_flip_rate->GetBinError(bin1);     // get error on fake rate 1 for this eta, pt bin
                double FRvalue2 = h_flip_rate->GetBinContent(bin2);   // get value of fake rate 2 for this eta, pt bin
                double FRerror2 = h_flip_rate->GetBinError(bin2);     // get error on fake rate 2 for this eta, pt bin

                // ok, have all of the inputs, calculate prediction and error for this bin
                // start with calculating fr/(1-fr) for this bin for each fake rate
                double fr1 = FRvalue1 / (1 - FRvalue1);
                double fr2 = FRvalue2 / (1 - FRvalue2);
                double pred = (fr1 + fr2) * nFOs;

                // now, need to get errors on these terms, be careful
                // start with hardest part, error on fr
                //
                // start with basic equation: (sigma_f/f)^2 = (sigma_num/num)^2 + (sigma_den/den)^2 - 2 * (sigma_num/num) * (sigma_den/den) * rho_num_den
                // f is the value fr from above
                // num is the value FRvalue from above
                // den is 1 - FRvalue
                //
                // sigma_num is the value FRerror from above
                // sigma_den is also the value FRerror from above (the error on 1 - A is just the error on A)
                // 
                // the numerator and denominator are completely anti-correlated, so rho_num_den is -1
                // 
                // combining all of this we can simplify the above to be
                //
                // (sigma_f/f)^2 = (sigma_num/num)^2 + (sigma_num/(1-num))^2 + 2 * sigma_num^2 * (1/num) * (1/(1-num))
                // (sigma_f/f)^2 = sigma_num^2 * [1/num + 1/(1-num)]^2
                // sigma_f = f * sigma_num * (1/(num * (1-num)))
                // sigma_f = sigma_num * (1 - num)^{-2}
                //
                double frError1 = FRerror1 * pow((1 - FRvalue1), -2);
                double frError2 = FRerror2 * pow((1 - FRvalue2), -2);

                // if we have a same flavor final state (either EE or MM)
                // and both leptons are in the same eta, pt bin
                // then the FR for each leg will come from the same bin
                // and thus the two FR factors will be completely correlated.
                // We need to account for this in the uncertainty calculation.
                double pred_error;
                //if (nFOs == 0 || is_zero(FRvalue1 * FRvalue2))
                if (nFOs == 0 || (FRvalue1 * FRvalue2)<1e-12)
                {
                    pred_error = 0.0;
                }
                else if (bin1 != bin2) 
                { 
                    // now that we have the error on fr/(1-fr), the error on the 
                    // prediction is just the sum of this error and the error on FO count added in quadrature
                    // (sigma_pred/pred)^2 = (sigma_fr/fr)^2 + (sigma_fo/fo)^2
                    pred_error = pred * sqrt(pow(frError1/fr1, 2) + pow(frError2/fr2, 2) + pow(nFOsError/nFOs, 2));
                }
                else 
                {
                    double totalFRfactor = FRvalue1 * FRvalue2;

                    // now that we have the error on each factor of fr/(1-fr), the error on the product when they are completely correlated is
                    // define FRprod = (FR_1 / (1 - FR_1)) * (FR_2 / (1 - FR_2)) = fr1 * fr2
                    // (sigma_FRprod/FRprod)^2 = (sigma_fr1/fr)^2 + (sigma_fr2/fr2)^2 + 2 * (sigma_fr1/fr1) * (sigma_fr2/fr2) * rho_fr1_fr2
                    // since the terms are completely correlated, rho_fr1_fr2 = 1, and thus
                    //
                    // (sigma_FRprod/FRprod)^2 = (sigma_fr1/fr1 + sigma_fr2/fr2)^2
                    // sigma_FRprod = FRprod * (sigma_fr1/fr1 + sigma_fr2/fr2) = fr2 * sigma_fr1 + fr1 *sigma_fr2
                    double totalFRerror  = (fr2 * frError1 + fr1 * frError2);
                    pred_error = pred * sqrt(pow(totalFRerror/totalFRfactor, 2) + pow(nFOsError/nFOs, 2));
                }

                // now increment the total values
                pred_total += pred;
                pred_error_total += pow(pred_error, 2);
            }
        }

        pred_error_total = sqrt(pred_error_total);
        Pred result(pred_total, pred_error_total);

        return result;    
    }

    void FlipRatePrediction::ComputeAllFlipPredictions
    (
         TH2F* h_ee, 
         TH2F* h_em
    )
    {
        // check hists
        if (!h_ee || !h_em)
        {
            throw std::runtime_error("ERROR - FlipRatePrediction::ComputeAllFlipPredictions: one or more histograms are NULL");
        }

        // SF raw
        flip.ee = DoubleFlipPrediction(h_ee);
        flip.em = SingleFlipPrediction(h_em);
        flip.mm = Pred(0.0, 0.0);
        flip.ll = flip.ee + flip.mm + flip.em;
    }

    PredSummary FlipRatePrediction::GetFlipPrediction(float scale_factor) const
    {
        PredSummary temp(flip);
        temp.ee = (scale_factor *temp.ee);
        temp.em = (scale_factor *temp.em);
        temp.mm = (scale_factor *temp.mm);
        temp.ll = (scale_factor *temp.ll);
        return temp;
    }

    // non members
    int DoubleFlipBinLookup(const TH2F& h_flip, float pt, float eta)
    {
        float max_pt  = h_flip.GetYaxis()->GetXmax(); 
        float min_pt  = h_flip.GetYaxis()->GetXmin();
        float max_eta = h_flip.GetXaxis()->GetXmax();
        float min_eta = h_flip.GetXaxis()->GetXmin();
        
        eta = fabs(eta);
        eta = eta >= max_eta ? max_eta-0.001 : eta;
        pt  = pt  >= max_pt  ? max_pt-0.001  : pt;
        if (pt < min_pt || eta > max_eta || eta < min_eta+0.001)
        {
            return -1;
        }
       
        int etabin = h_flip.GetXaxis()->FindBin(eta);
        int ptbin  = h_flip.GetYaxis()->FindBin(pt);
    
        if(ptbin <= 0)  {throw std::domain_error("ERROR: PlotLooper::DoubleFlipBinLookup: ptbin <= 0" );}
        if(etabin <= 0) {throw std::domain_error("ERROR: PlotLooper::DoubleFlipBinLookup: etabin <= 0");}
    
        int bin = (ptbin-1) * h_flip.GetNbinsX() + etabin;
        return bin;
    }
    
    void FillDoubleFlipHist
    (
        TH2F& hist, 
        const TH2F& h_flip,
        float pt1, 
        float eta1, 
        float pt2, 
        float eta2, 
        float weight
        )
    {
        std::pair<int, int> bins(DoubleFlipBinLookup(h_flip, pt1, eta1), DoubleFlipBinLookup(h_flip, pt2, eta2));
        float value = hist.GetBinContent(bins.first, bins.second);
        value += weight;
        hist.SetBinContent(bins.first, bins.second, value);
        hist.SetBinError(bins.first, bins.second, weight * sqrt(value/weight));
    }

} // namespace at
