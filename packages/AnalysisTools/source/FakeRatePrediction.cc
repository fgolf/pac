#include "at/FakeRatePrediction.h"
#include "rt/RootTools.h"
#include <tr1/array>

using namespace rt;
using namespace std;

namespace at
{
    // at::FakeRatePrediction implementation
    // ----------------------------------------------------//

    // construct:
    FakeRatePrediction::FakeRatePrediction(TH2* mufr, TH2* elfr)
        : h_mufr(dynamic_cast<TH2*>(mufr->Clone()))
        , h_elfr(dynamic_cast<TH2*>(elfr->Clone()))
        , m_ele_max(0)
        , m_mu_max(0)
    {
        if (not h_mufr)
        {
            throw std::runtime_error("ERROR -- at::FakeRatePrediction - h_mufr is NULL!");
        }
        if (not h_elfr)
        {
            throw std::runtime_error("ERROR -- at::FakeRatePrediction - h_elfr is NULL!");
        }
        // take ownwership of the hists
        h_mufr->SetDirectory(0);
        h_elfr->SetDirectory(0);
        m_ele_max = h_elfr->GetMaximum();
        m_mu_max  = h_mufr->GetMaximum();
    }

    // methods
    Pred FakeRatePrediction::SingleFakePrediction(const TH2F* foHist, FakeRateType::value_type type, DileptonHypType::value_type hypType)
    {
        Float_t pred_total       = 0.0;
        Float_t pred_error_total = 0.0;

        if (type == FakeRateType::E) 
        {
            for (Int_t xbin = 1; xbin < h_elfr->GetXaxis()->GetNbins()+1; xbin++) 
            {
                for (Int_t ybin = 1; ybin < h_elfr->GetYaxis()->GetNbins()+1; ybin++) 
                {
                    Int_t bin         = h_elfr->GetBin(xbin, ybin);
                    Float_t nFOs      = foHist->GetBinContent(bin);    // number of denominator not numerator objects for this eta, pt bin
                    Float_t nFOsError = foHist->GetBinError(bin);      // number error on number of of denominator not numerator objects for this eta, pt bin
                    Float_t FRvalue   = h_elfr->GetBinContent(bin); // get value of fake rate for this eta, pt bin
                    Float_t FRerror   = h_elfr->GetBinError(bin);   // get error on fake rate for this eta, pt bin

                    // ok, have all of the inputs, calculate prediction and error for this bin
                    // start with calculating fr/(1-fr) for this bin
                    Float_t fr = FRvalue / (1 - FRvalue);
                    Float_t pred = fr * nFOs;

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
                    Float_t frError = FRerror * pow((1 - FRvalue), -2);

                    // now that we have the error on fr/(1-fr), the error on the prediction is 
                    // just the sum of this error and the error on FO count added in quadrature
                    // (sigma_pred/pred)^2 = (sigma_fr/fr)^2 + (sigma_fo/fo)^2
                    Float_t pred_error = (nFOs > 0) ? pred * sqrt(pow(frError/fr, 2) + pow(nFOsError/nFOs, 2)) : 0.;

                    // now increment the total values
                    pred_total += pred;
                    pred_error_total += pow(pred_error, 2);
                }
            }

            // check for zero value and assign error appropriately
            if (!is_zero(pred_total))            
            {
                pred_error_total = sqrt(pred_error_total);
            }
            else
            {
                // not sure if this was intentional here?
                pred_error_total = (hypType == DileptonHypType::EMU) ? (m_ele_max/(1 - m_ele_max)) : (m_ele_max/(1 - m_ele_max));
            }

            return Pred(pred_total, pred_error_total);
        }
        if (type == FakeRateType::MU) 
        {
            for (Int_t xbin = 1; xbin < h_mufr->GetXaxis()->GetNbins()+1; xbin++) 
            {
                for (Int_t ybin = 1; ybin < h_mufr->GetYaxis()->GetNbins()+1; ybin++) 
                {

                    Int_t bin         = h_mufr->GetBin(xbin, ybin);
                    Float_t nFOs      = foHist->GetBinContent(bin);    // number of denominator not numerator objects for this eta, pt bin
                    Float_t nFOsError = foHist->GetBinError(bin); // number error on number of of denominator not numerator objects for this eta, pt bin
                    Float_t FRvalue   = h_mufr->GetBinContent(bin); // get value of fake rate for this eta, pt bin
                    Float_t FRerror   = h_mufr->GetBinError(bin);   // get error on fake rate for this eta, pt bin

                    // ok, have all of the inputs, calculate prediction and error for this bin
                    // start with calculating fr/(1-fr) for this bin
                    Float_t fr = FRvalue / (1 - FRvalue);
                    Float_t pred = fr * nFOs;

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
                    Float_t frError = FRerror * pow((1 - FRvalue), -2);

                    // now that we have the error on fr/(1-fr), the error on the prediction is just the 
                    // sum of this error and the error on FO count added in quadrature
                    // (sigma_pred/pred)^2 = (sigma_fr/fr)^2 + (sigma_fo/fo)^2
                    Float_t pred_error = (nFOs > 0) ? pred * sqrt(pow(frError/fr, 2) + pow(nFOsError/nFOs, 2)) : 0;

                    // now increment the total values
                    pred_total += pred;
                    pred_error_total += pow(pred_error, 2);
                }
            }

            // check for zero value and assign error appropriately
            if (!is_zero(pred_total))            
            {
                pred_error_total = sqrt(pred_error_total);
            }
            else
            {
                // not sure if this was intentional here?
                pred_error_total = m_mu_max/(1 - m_mu_max);
            }

            return Pred(pred_total, pred_error_total);
        }

        return Pred(-1, -1);
    }

    Pred FakeRatePrediction::DoubleFakePrediction(const TH2F* foHist, FakeRateType::value_type type)
    {
        unsigned int MIN_XBIN = 1;
        unsigned int MIN_YBIN = 1;
        const unsigned int NETA_BINS = 4;

        Float_t pred_total       = 0.0;
        Float_t pred_error_total = 0.0;
        const unsigned int MAX_XBIN = foHist->GetXaxis()->GetNbins()+1;
        const unsigned int MAX_YBIN = foHist->GetYaxis()->GetNbins()+1;
        for (unsigned int xbin = MIN_XBIN; xbin < MAX_XBIN; xbin++) 
        {
            for (unsigned int ybin = MIN_YBIN; ybin < MAX_YBIN; ybin++) 
            {

                int xbin1 = ((xbin - MIN_XBIN) % NETA_BINS) + 1;
                int ybin1 = ((xbin - xbin1 + 1 - MIN_XBIN) / NETA_BINS) + 1;
                int xbin2 = ((ybin - MIN_YBIN) % NETA_BINS) + 1;
                int ybin2 = ((ybin - xbin2 + 1 - MIN_YBIN) / NETA_BINS) + 1;

                Int_t bin1 = -1;
                Int_t bin2 = -1;
                if (type == FakeRateType::EE) 
                {
                    bin1 = h_elfr->GetBin(xbin1, ybin1);
                    bin2 = h_elfr->GetBin(xbin2, ybin2);
                }
                else if (type == FakeRateType::MUMU) 
                {
                    bin1 = h_mufr->GetBin(xbin1, ybin1);
                    bin2 = h_mufr->GetBin(xbin2, ybin2);
                }
                else if (type == FakeRateType::EMU) 
                {
                    bin1 = h_elfr->GetBin(xbin1, ybin1);
                    bin2 = h_mufr->GetBin(xbin2, ybin2);
                }

                Float_t nFOs = foHist->GetBinContent(xbin, ybin);    // number of denominator not numerator objects for this eta, pt bin
                Float_t nFOsError = foHist->GetBinError(xbin, ybin); // number error on number of of denominator not numerator objects for this eta, pt bin
                Float_t FRvalue1 = 0.0;                              // get value of fake rate 1 for this eta, pt bin
                Float_t FRerror1 = 0.0;                              // get error on fake rate 1 for this eta, pt bin
                Float_t FRvalue2 = 0.0;                              // get value of fake rate 2 for this eta, pt bin
                Float_t FRerror2 = 0.0;                              // get error on fake rate 2 for this eta, pt bin

                if (type == FakeRateType::EE) 
                {
                    FRvalue1 = h_elfr->GetBinContent(bin1); 
                    FRerror1 = h_elfr->GetBinError(bin1);   
                    FRvalue2 = h_elfr->GetBinContent(bin2); 
                    FRerror2 = h_elfr->GetBinError(bin2);   
                }
                else if (type == FakeRateType::MUMU) 
                {
                    FRvalue1 = h_mufr->GetBinContent(bin1);     
                    FRerror1 = h_mufr->GetBinError(bin1);       
                    FRvalue2 = h_mufr->GetBinContent(bin2);     
                    FRerror2 = h_mufr->GetBinError(bin2);       
                }
                else if (type == FakeRateType::EMU) 
                {
                    FRvalue1 = h_elfr->GetBinContent(bin1);
                    FRerror1 = h_elfr->GetBinError(bin1);       
                    FRvalue2 = h_mufr->GetBinContent(bin2);
                    FRerror2 = h_mufr->GetBinError(bin2);       
                }

                // ok, have all of the inputs, calculate prediction and error for this bin
                // start with calculating fr/(1-fr) for this bin for each fake rate
                Float_t fr1 = FRvalue1 / (1 - FRvalue1);
                Float_t fr2 = FRvalue2 / (1 - FRvalue2);
                Float_t pred = fr1 * fr2 * nFOs;

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
                Float_t frError1 = FRerror1 * pow((1 - FRvalue1), -2);
                Float_t frError2 = FRerror2 * pow((1 - FRvalue2), -2);

                // if we have a same flavor final state (either EE or MM)
                // and both leptons are in the same eta, pt bin
                // then the FR for each leg will come from the same bin
                // and thus the two FR factors will be completely correlated.
                // We need to account for this in the uncertainty calculation.
                Float_t pred_error;
                if (nFOs == 0)
                {
                    pred_error = 0.;
                }
                else if (type == FakeRateType::EMU || bin1 != bin2) 
                {             
                    // now that we have the error on fr/(1-fr), the error on the prediction is just 
                    // the sum of this error and the error on FO count added in quadrature
                    // (sigma_pred/pred)^2 = (sigma_fr/fr)^2 + (sigma_fo/fo)^2
                    pred_error = pred * sqrt(pow(frError1/fr1, 2) + pow(frError2/fr2, 2) + pow(nFOsError/nFOs, 2));
                }
                else 
                {
                    Float_t totalFRfactor = fr1 * fr2;

                    // now that we have the error on each factor of fr/(1-fr), the error on the product when they are completely correlated is
                    // define FRprod = (FR_1 / (1 - FR_1)) * (FR_2 / (1 - FR_2)) = fr1 * fr2
                    // (sigma_FRprod/FRprod)^2 = (sigma_fr1/fr)^2 + (sigma_fr2/fr2)^2 + 2 * (sigma_fr1/fr1) * (sigma_fr2/fr2) * rho_fr1_fr2
                    // since the terms are completely correlated, rho_fr1_fr2 = 1, and thus
                    //
                    // (sigma_FRprod/FRprod)^2 = (sigma_fr1/fr1 + sigma_fr2/fr2)^2
                    // sigma_FRprod = FRprod * (sigma_fr1/fr1 + sigma_fr2/fr2) = fr2 * sigma_fr1 + fr1 *sigma_fr2
                    Float_t totalFRerror  = (fr2 * frError1 + fr1 * frError2);
                    pred_error = pred * sqrt(pow(totalFRerror/totalFRfactor, 2) + pow(nFOsError/nFOs, 2));
                }

                // now increment the total values
                pred_total += pred;
                pred_error_total += pow(pred_error, 2);
            }
        }

        if (not is_zero(pred_total))
        {
            pred_error_total = sqrt(pred_error_total);
        }
        else 
        {
            if (type == FakeRateType::MUMU)     pred_error_total = pow((m_mu_max/(1 - m_mu_max)), 2);
            else if (type == FakeRateType::EMU) pred_error_total = (m_mu_max/(1 - m_mu_max) * m_ele_max/(1 - m_ele_max));
            else                                pred_error_total = pow((m_ele_max/(1 - m_ele_max)), 2);        
        }


        return Pred(pred_total, pred_error_total);
    }

    PredSummary FakeRatePrediction::GetSingleFakePredictionRaw() const
    {
        return sf_raw;
    }

    PredSummary FakeRatePrediction::GetSingleFakePrediction() const
    {
        return sf;
    }

    PredSummary FakeRatePrediction::GetDoubleFakePrediction() const
    {
        return df;
    }

    PredSummary FakeRatePrediction::GetFakePrediction() const
    {
        return all;
    }

    void FakeRatePrediction::ComputeAllFakePredictions
    (
         TH2F* h_sf_ee, 
         TH2F* h_sf_mm, 
         TH2F* h_sf_em, 
         TH2F* h_sf_me, 
         TH2F* h_df_ee, 
         TH2F* h_df_mm, 
         TH2F* h_df_em
    )
    {
        // check hists
        if (!h_sf_ee || !h_sf_mm || !h_sf_em || !h_sf_me || !h_df_ee || !h_df_mm || !h_df_em)
        {
            throw std::runtime_error("ERROR - at::FakeRatePrediction::ComputeAllFakePredictions: one or more histograms are NULL");
        }
        // SF raw
        Pred ee = SingleFakePrediction(h_sf_ee, FakeRateType::E , DileptonHypType::EE  );
        Pred mm = SingleFakePrediction(h_sf_mm, FakeRateType::MU, DileptonHypType::MUMU);
        Pred em = SingleFakePrediction(h_sf_em, FakeRateType::E , DileptonHypType::EMU );
        Pred me = SingleFakePrediction(h_sf_me, FakeRateType::MU, DileptonHypType::EMU );
        //em += me;
        sf_raw = PredSummary(ee, mm, em, me);

        // DF
        ee = DoubleFakePrediction(h_df_ee, FakeRateType::EE  );
        mm = DoubleFakePrediction(h_df_mm, FakeRateType::MUMU);
        em = DoubleFakePrediction(h_df_em, FakeRateType::EMU );
        df = PredSummary(ee, mm, em);

        // SF
        sf.ee = sf_raw.ee - (2.0*df.ee);
        sf.mm = sf_raw.mm - (2.0*df.mm);
        sf.em = sf_raw.em - (2.0*df.em);
        sf.ll = sf_raw.ll - (2.0*df.ll);
        sf.ee.error = sqrt(sf_raw.ee.error*sf_raw.ee.error + 4*df.ee.error*df.ee.error);
        sf.mm.error = sqrt(sf_raw.mm.error*sf_raw.mm.error + 4*df.mm.error*df.mm.error);
        sf.em.error = sqrt(sf_raw.em.error*sf_raw.em.error + 4*df.em.error*df.em.error);
        sf.ll.error = sqrt(sf_raw.ll.error*sf_raw.ll.error + 4*df.ll.error*df.ll.error);

        // fake
        all.ee = sf_raw.ee - df.ee;
        all.mm = sf_raw.mm - df.mm;
        all.em = sf_raw.em - df.em;
        all.ll = sf_raw.ll - df.ll;
    }

    // non members
    int DoubleFakeBinLookup(const TH2F& h_mufr, const TH2F& h_elfr, int id, float pt, float eta)
    {
        id  = abs(id);
        eta = fabs(eta);
        const TH2F& hist = (id == 11 ? h_elfr : h_mufr);
        float max_pt  = hist.GetYaxis()->GetXmax(); 
        float min_pt  = hist.GetYaxis()->GetXmin();
        float max_eta = hist.GetXaxis()->GetXmax();
        float min_eta = hist.GetXaxis()->GetXmin();
    
        eta = eta >= max_eta ? max_eta-0.001 : eta;
        pt  = pt  >= max_pt  ? max_pt-0.001  : pt;
        if (pt < min_pt || eta > max_eta || eta < min_eta+0.001)
        {
            return -1;
        }
       
        int etabin = hist.GetXaxis()->FindBin(eta);
        int ptbin  = hist.GetYaxis()->FindBin(pt);
    
        if(ptbin <= 0)  {throw std::domain_error("ERROR: PlotLooper::DoubleFakeBinLookup: ptbin <= 0" );}
        if(etabin <= 0) {throw std::domain_error("ERROR: PlotLooper::DoubleFakeBinLookup: etabin <= 0");}
    
        int bin = (ptbin-1) * hist.GetNbinsX() + etabin;
        //cout << Form("id %u pt %f eta %f pt_bin %u eta_bin %u", id, pt, eta, ptbin, etabin) << endl;
        return bin;
    }

    void FillDoubleFakeHist
    (
        TH2F& hist, 
        const TH2F& h_mufr,
        const TH2F& h_elfr,
        const at::DileptonHypType::value_type& hyp, 
        int id1, 
        float pt1, 
        float eta1, 
        int id2, 
        float pt2, 
        float eta2, 
        float weight
    )
    {
        std::pair<int, int> bins(DoubleFakeBinLookup(h_mufr, h_elfr, id1, pt1, eta1), DoubleFakeBinLookup(h_mufr, h_elfr, id2, pt2, eta2));
        if (hyp == at::DileptonHypType::EMU && abs(id1) == 13)
        {
            bins = std::make_pair(DoubleFakeBinLookup(h_mufr, h_elfr, id2, pt2, eta2), DoubleFakeBinLookup(h_mufr, h_elfr, id1, pt1, eta1));
        }
        float value = hist.GetBinContent(bins.first, bins.second);
    
        value += weight;
        hist.SetBinContent(bins.first, bins.second, value);
        hist.SetBinError(bins.first, bins.second, weight * sqrt(value/weight));
    }

} // namespace at
