#include "SSB2011.h"
#include "FakePredLooper.h"
#include "mcSelections.h"
#include "rt/RootTools.h"
#include <iostream>
#include <algorithm>
#include <tr1/array>
#include <cmath>
#include "at/VtxReweight.h"
#include "CTable.h"

typedef std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > vecLorentzVector;

FakeRate::FakeRate(const std::string& file_name, const std::string& hist_name)
    : h_fake_rate(rt::GetHistFromRootFile<TH1>(file_name, hist_name))
{
}

FakeRate::~FakeRate()
{
    delete h_fake_rate;
}

float FakeRate::GetValue(float pt) const
{
    // check the boundary conditions
    pt = std::min(pt, static_cast<float>(h_fake_rate->GetXaxis()->GetXmax()-0.00001));
    pt = std::max(pt, static_cast<float>(h_fake_rate->GetXaxis()->GetXmin()+0.00001));

    // result
    int bin  = h_fake_rate->FindBin(pt);
    return h_fake_rate->GetBinContent(bin);
};

float FakeRate::GetError(float pt) const
{
    // check the boundary conditions
    pt = std::min(pt, static_cast<float>(h_fake_rate->GetXaxis()->GetXmax()-0.00001));
    pt = std::max(pt, static_cast<float>(h_fake_rate->GetXaxis()->GetXmin()+0.00001));

    // result
    int bin  = h_fake_rate->FindBin(pt);
    return h_fake_rate->GetBinError(bin);
};

float FakeRate::GetValue(float pt, float eta) const
{
    // want the |eta|
    eta = fabs(eta);

    // check the boundary conditions
    pt  = std::min(pt, static_cast<float>(h_fake_rate->GetYaxis()->GetXmax()-0.00001));
    pt  = std::max(pt, static_cast<float>(h_fake_rate->GetYaxis()->GetXmin()+0.00001));
    eta = std::min(eta, static_cast<float>(h_fake_rate->GetXaxis()->GetXmax()-0.00001));
    eta = std::max(eta, static_cast<float>(h_fake_rate->GetXaxis()->GetXmin()+0.00001));

    // result
    int bin  = h_fake_rate->FindBin(eta, pt);
    return h_fake_rate->GetBinContent(bin);
};

float FakeRate::GetError(float pt, float eta) const
{
    // want the |eta|
    eta = fabs(eta);

    // check the boundary conditions
    pt  = std::min(pt, static_cast<float>(h_fake_rate->GetYaxis()->GetXmax()-0.00001));
    pt  = std::max(pt, static_cast<float>(h_fake_rate->GetYaxis()->GetXmin()+0.00001));
    eta = std::min(eta, static_cast<float>(h_fake_rate->GetXaxis()->GetXmax()-0.00001));
    eta = std::max(eta, static_cast<float>(h_fake_rate->GetXaxis()->GetXmin()+0.00001));

    // result
    int bin  = h_fake_rate->FindBin(eta, pt);
    return h_fake_rate->GetBinError(bin);
};

float FakeRate::GetValue(float pt, float eta, float mc3pt) const
{
    // want the |eta|
    eta = fabs(eta);

    // check the boundary conditions
    eta    = std::min(eta, static_cast<float>(h_fake_rate->GetXaxis()->GetXmax()-0.00001));
    eta    = std::max(eta, static_cast<float>(h_fake_rate->GetXaxis()->GetXmin()+0.00001));
    pt     = std::min(pt, static_cast<float>(h_fake_rate->GetYaxis()->GetXmax()-0.00001));
    pt     = std::max(pt, static_cast<float>(h_fake_rate->GetYaxis()->GetXmin()+0.00001));
    mc3pt  = std::min(mc3pt, static_cast<float>(h_fake_rate->GetZaxis()->GetXmax()-0.00001));
    mc3pt  = std::max(mc3pt, static_cast<float>(h_fake_rate->GetZaxis()->GetXmin()+0.00001));

    // result
    int bin  = h_fake_rate->FindBin(eta, pt, mc3pt);
    return h_fake_rate->GetBinContent(bin);
};

float FakeRate::GetError(float pt, float eta, float mc3pt) const
{
    // want the |eta|
    eta = fabs(eta);

    // check the boundary conditions
    eta    = std::min(eta, static_cast<float>(h_fake_rate->GetXaxis()->GetXmax()-0.00001));
    eta    = std::max(eta, static_cast<float>(h_fake_rate->GetXaxis()->GetXmin()+0.00001));
    pt     = std::min(pt, static_cast<float>(h_fake_rate->GetYaxis()->GetXmax()-0.00001));
    pt     = std::max(pt, static_cast<float>(h_fake_rate->GetYaxis()->GetXmin()+0.00001));
    mc3pt  = std::min(mc3pt, static_cast<float>(h_fake_rate->GetZaxis()->GetXmax()-0.00001));
    mc3pt  = std::max(mc3pt, static_cast<float>(h_fake_rate->GetZaxis()->GetXmin()+0.00001));

    // result
    int bin  = h_fake_rate->FindBin(eta, pt, mc3pt);
    return h_fake_rate->GetBinError(bin);
};

// construct:
FakePredLooper::FakePredLooper
(
     const std::string& root_file_name,
     const std::string& vtxreweight_file_name,
     const std::string& fr_file_name,
     const std::string& fr_hist_name,
     unsigned int num_btags,
     bool directb,
     float lumi,
     bool verbose,
     bool print,
     const std::string& suffix
)
    : at::AnalysisWithHist(root_file_name, print, suffix)
    , m_lumi(lumi)
    , m_verbose(verbose)
    , m_nbtags(num_btags)
    , m_directb(directb)
    , m_fr_file_name(fr_file_name)
    , m_fr(fr_file_name, fr_hist_name)
{
    // set vertex weight file
    if (!vtxreweight_file_name.empty())
    {
        cout << "using vertex reweight file : " << vtxreweight_file_name << endl;
        set_vtxreweight_rootfile(vtxreweight_file_name.c_str(), verbose);
    }

    // begin job
    BeginJob();
}

// destroy:
FakePredLooper::~FakePredLooper()
{
    // end  job
    EndJob();
}

// methods:
void FakePredLooper::BeginJob()
{
    BookHists();
}

// end job
void FakePredLooper::EndJob()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    int   nobs         = hc["h_mm_nobs"]->GetEntries();
    float nobs_err     = sqrt(static_cast<float>(nobs)); 
    int   nobs_db      = hc["h_mm_nobs_directb"]->GetEntries();
    float nobs_db_err  = sqrt(static_cast<float>(nobs_db)); 
    //int nfo_df   = hc["h_mm_nfo_df"]->GetEntries();
    //float sf_raw   = rt::Integral(hc["h_mm_nfo_sf"]);
    //float df_raw   = rt::Integral(hc["h_mm_nfo_df"]);

    // SF prediction (pt, eta) 
    TH2F& h_sf = *static_cast<TH2F*>(hc["h_mm_nfo_sf_eta_pt"]);
    FakeRate fr(m_fr_file_name, "h_mufr40c");
    float nfo_sf = h_sf.GetEntries();
    float sf_raw = 0.0;
    float sf_err = 0.0;
    for (int ptbin = 1; ptbin != h_sf.GetNbinsY()+1; ptbin++)
    {  
        for (int etabin = 1; etabin != h_sf.GetNbinsX()+1; etabin++)
        {  
            float bin_count = h_sf.GetBinContent(etabin, ptbin);
            float bin_err   = h_sf.GetBinError(etabin, ptbin);
            float pt  = h_sf.GetYaxis()->GetBinCenter(ptbin);
            float eta = h_sf.GetXaxis()->GetBinCenter(etabin);
            float f = fr.GetValue(pt, eta);
            float e = fr.GetError(pt, eta);
            e = e / pow(1.0 - f, 2);
            f = f / (1.0 - f);
            float bin_pred = (bin_count * f); 
            float bin_pred_err = pow(bin_count*f,2) * (pow(e/f, 2) + pow(bin_err/bin_count, 2)); 
            sf_raw += bin_pred; 
            sf_err += !rt::is_zero(bin_pred) ? bin_pred_err : 0.0;
        }
    }
    sf_err = sqrt(sf_err);
    //cout << Form("nobs %d, sf_raw %f, sf_err %f, raw bin count %f", nobs, sf_raw, sf_err, nfo_sf_count) << endl;

    // SF prediction (pt, eta) direct b
    TH2F& h_sf_db = *static_cast<TH2F*>(hc["h_mm_nfo_sf_eta_pt_directb"]);
    FakeRate fr_db(m_fr_file_name, "h_mufr40c_directb");
    float nfo_sf_db = h_sf_db.GetEntries();
    float sf_raw_db = 0.0;
    float sf_err_db = 0.0;
    for (int ptbin = 1; ptbin != h_sf.GetNbinsY()+1; ptbin++)
    {  
        for (int etabin = 1; etabin != h_sf.GetNbinsX()+1; etabin++)
        {  
            float bin_count = h_sf_db.GetBinContent(etabin, ptbin);
            float bin_err   = h_sf_db.GetBinError(etabin, ptbin);
            float pt  = h_sf.GetYaxis()->GetBinCenter(ptbin);
            float eta = h_sf.GetXaxis()->GetBinCenter(etabin);
            float f = fr_db.GetValue(pt, eta);
            float e = fr_db.GetError(pt, eta);
            e = e / pow(1.0 - f, 2);
            f = f / (1.0 - f);
            float bin_pred = (bin_count * f); 
            float bin_pred_err = pow(bin_count*f,2) * (pow(e/f, 2) + pow(bin_err/bin_count, 2)); 
            sf_raw_db += bin_pred; 
            sf_err_db += !rt::is_zero(bin_pred) ? bin_pred_err : 0.0;
        }
    }
    sf_err_db = sqrt(sf_err_db);

    // SF prediction (mc3 pt) direct b
    TH2F& h_sf_mc3 = *static_cast<TH2F*>(hc["h_mm_nfo_sf_mc3"]);
    FakeRate fr_mc3(m_fr_file_name, "h_mufr40c_vs_mc3");
    float nfo_sf_mc3 = h_sf_mc3.GetEntries();
    float sf_raw_mc3 = 0.0;
    float sf_err_mc3 = 0.0;
    for (int mc3ptbin = 1; mc3ptbin != h_sf_mc3.GetNbinsX()+1; mc3ptbin++)
    {  
            float bin_count = h_sf_mc3.GetBinContent(mc3ptbin);
            float bin_err   = h_sf_mc3.GetBinError(mc3ptbin);
            float pt  = h_sf_mc3.GetXaxis()->GetBinCenter(mc3ptbin);
            float f = fr_mc3.GetValue(pt);
            float e = fr_mc3.GetError(pt);
            e = e / pow(1.0 - f, 2);
            f = f / (1.0 - f);
            float bin_pred = (bin_count * f); 
            float bin_pred_err = pow(bin_count*f,2) * (pow(e/f, 2) + pow(bin_err/bin_count, 2)); 
            //cout << Form("pt %f, bin_count %f, bin_err %f, bin_pred %f, bin_pred_err %f, f %f, e %f", pt, bin_count, bin_err, bin_pred, bin_pred_err, f, e) << endl;
            sf_raw_mc3 += bin_pred; 
            sf_err_mc3 += !rt::is_zero(bin_pred) ? bin_pred_err : 0.0;
    }
    sf_err_mc3 = sqrt(sf_err_mc3);

    // SF prediction (eta, mc3pt) direct b
    TH2F& h_sf_eta_mc3 = *static_cast<TH2F*>(hc["h_mm_nfo_sf_eta_mc3"]);
    FakeRate fr_eta_mc3(m_fr_file_name, "h_mufr40c_eta_mc3");
    float nfo_sf_eta_mc3 = h_sf_eta_mc3.GetEntries();
    float sf_raw_eta_mc3 = 0.0;
    float sf_err_eta_mc3 = 0.0;
    for (int mc3ptbin = 1; mc3ptbin != h_sf_eta_mc3.GetNbinsY()+1; mc3ptbin++)
    {  
        for (int etabin = 1; etabin != h_sf_eta_mc3.GetNbinsX()+1; etabin++)
        {  
            float bin_count = h_sf_eta_mc3.GetBinContent(etabin, mc3ptbin);
            float bin_err   = h_sf_eta_mc3.GetBinError(etabin, mc3ptbin);
            float pt  = h_sf_eta_mc3.GetYaxis()->GetBinCenter(mc3ptbin);
            float eta = h_sf_eta_mc3.GetXaxis()->GetBinCenter(etabin);
            float f = fr_eta_mc3.GetValue(pt, eta);
            float e = fr_eta_mc3.GetError(pt, eta);
            e = e / pow(1.0 - f, 2);
            f = f / (1.0 - f);
            // fill the holes with the FR(mc3 pt) value
            if (rt::is_zero(f) && !rt::is_zero(bin_count))
            {
                f = fr_mc3.GetValue(pt);
                e = fr_mc3.GetError(pt);
                cout << Form("FR(eta, mc3) hole: eta %f, mc3 pt %f -- using FR(mc3 pt) value of %f+/-%f", eta, pt, f, e) << endl;
            }
            float bin_pred = (bin_count * f); 
            float bin_pred_err = pow(bin_count*f,2) * (pow(e/f, 2) + pow(bin_err/bin_count, 2)); 
            //cout << Form("mc3pt %f, eta %f, bin_count %f, bin_err %f, bin_pred %f, bin_pred_err %f, f %f, e %f", pt, eta, bin_count, bin_err, bin_pred, bin_pred_err, f, e) << endl;
            if (rt::is_zero(f) && !rt::is_zero(bin_count))
            {
            }
            sf_raw_eta_mc3 += bin_pred; 
            sf_err_eta_mc3 += !rt::is_zero(bin_pred) ? bin_pred_err : 0.0;
        }
    }
    sf_err_eta_mc3 = sqrt(sf_err_eta_mc3);

    // SF prediction (pt, mc3pt) direct b
    TH2F& h_sf_pt_mc3 = *static_cast<TH2F*>(hc["h_mm_nfo_sf_pt_mc3"]);
    FakeRate fr_pt_mc3(m_fr_file_name, "h_mufr40c_pt_mc3");
    float nfo_sf_pt_mc3 = h_sf_pt_mc3.GetEntries();
    float sf_raw_pt_mc3 = 0.0;
    float sf_err_pt_mc3 = 0.0;
    for (int mc3ptbin = 1; mc3ptbin != h_sf_pt_mc3.GetNbinsY()+1; mc3ptbin++)
    {  
        for (int ptbin = 1; ptbin != h_sf_pt_mc3.GetNbinsX()+1; ptbin++)
        {  
            float bin_count = h_sf_pt_mc3.GetBinContent(ptbin, mc3ptbin);
            float bin_err   = h_sf_pt_mc3.GetBinError(ptbin, mc3ptbin);
            float mc3pt = h_sf_pt_mc3.GetYaxis()->GetBinCenter(mc3ptbin);
            float pt    = h_sf_pt_mc3.GetXaxis()->GetBinCenter(ptbin);
            float f = fr_pt_mc3.GetValue(mc3pt, pt);
            float e = fr_pt_mc3.GetError(mc3pt, pt);
            // fill the holes with the FR(mc3 pt) value
            if (rt::is_zero(f) && !rt::is_zero(bin_count))
            {
                f = fr_mc3.GetValue(pt);
                e = fr_mc3.GetError(pt);
                cout << Form("FR(pt, mc3) hole: pt %f, mc3 pt %f -- using FR(mc3 pt) value of %f+/-%f", pt, mc3pt, f, e) << endl;
            }
            e = e / pow(1.0 - f, 2);
            f = f / (1.0 - f);
            float bin_pred = (bin_count * f); 
            float bin_pred_err = pow(bin_count*f,2) * (pow(e/f, 2) + pow(bin_err/bin_count, 2)); 
            //cout << Form("mc3pt %f, pt %f, bin_count %f, bin_err %f, bin_pred %f, bin_pred_err %f, f %f, e %f", mc3pt, pt, bin_count, bin_err, bin_pred, bin_pred_err, f, e) << endl;
            sf_raw_pt_mc3 += bin_pred; 
            sf_err_pt_mc3 += !rt::is_zero(bin_pred) ? bin_pred_err : 0.0;
        }
    }
    sf_err_pt_mc3 = sqrt(sf_err_pt_mc3);

    // SF prediction (eta, pt, mc3pt) direct b
    TH2F& h_sf_eta_pt_mc3 = *static_cast<TH2F*>(hc["h_mm_nfo_sf_eta_pt_mc3"]);
    FakeRate fr_eta_pt_mc3(m_fr_file_name, "h_mufr40c_eta_pt_mc3");
    float nfo_sf_eta_pt_mc3 = h_sf_eta_pt_mc3.GetEntries();
    float sf_raw_eta_pt_mc3 = 0.0;
    float sf_err_eta_pt_mc3 = 0.0;
    for (int mc3ptbin = 1; mc3ptbin != h_sf_eta_pt_mc3.GetNbinsZ()+1; mc3ptbin++)
    {  
        for (int ptbin = 1; ptbin != h_sf_eta_pt_mc3.GetNbinsY()+1; ptbin++)
        {  
            for (int etabin = 1; etabin != h_sf_eta_pt_mc3.GetNbinsX()+1; etabin++)
            {  
                float bin_count = h_sf_eta_pt_mc3.GetBinContent(etabin, ptbin, mc3ptbin);
                float bin_err   = h_sf_eta_pt_mc3.GetBinError(etabin, ptbin, mc3ptbin);
                float eta   = h_sf_eta_pt_mc3.GetXaxis()->GetBinCenter(etabin);
                float pt    = h_sf_eta_pt_mc3.GetYaxis()->GetBinCenter(ptbin);
                float mc3pt = h_sf_eta_pt_mc3.GetZaxis()->GetBinCenter(mc3ptbin);
                float f = fr_eta_pt_mc3.GetValue(pt, eta, mc3pt);
                float e = fr_eta_pt_mc3.GetError(pt, eta, mc3pt);
                // fill the holes with the FR(mc3 pt) value
                if (rt::is_zero(f) && !rt::is_zero(bin_count))
                {
                    f = fr_mc3.GetValue(pt);
                    e = fr_mc3.GetError(pt);
                    cout << Form("FR(eta, pt, mc3) hole: eta %f, pt %f, mc3 pt %f -- using FR(mc3 pt) value of %f+/-%f", eta, pt, mc3pt, f, e) << endl;
                }
                e = e / pow(1.0 - f, 2);
                f = f / (1.0 - f);
                float bin_pred = (bin_count * f); 
                float bin_pred_err = pow(bin_count*f,2) * (pow(e/f, 2) + pow(bin_err/bin_count, 2)); 
                //cout << Form("mc3pt %f, pt %f, eta %f, bin_count %f, bin_err %f, bin_pred %f, bin_pred_err %f, f %f, e %f", mc3pt, pt, eta, bin_count, bin_err, bin_pred, bin_pred_err, f, e) << endl;
                sf_raw_eta_pt_mc3 += bin_pred; 
                sf_err_eta_pt_mc3 += !rt::is_zero(bin_pred) ? bin_pred_err : 0.0;
            }
        }
    }
    sf_err_eta_pt_mc3 = sqrt(sf_err_eta_pt_mc3);

    // ratios
    float ratio_orig        = nobs/sf_raw;
    float ratio_db          = nobs_db/sf_raw_db;
    float ratio_mc3         = nobs_db/sf_raw_mc3;
    float ratio_eta_mc3     = nobs_db/sf_raw_eta_mc3;
    float ratio_pt_mc3      = nobs_db/sf_raw_pt_mc3;
    float ratio_eta_pt_mc3  = nobs_db/sf_raw_eta_pt_mc3;

    float ratio_orig_err        = ratio_orig      * sqrt(pow(nobs_err   /nobs   ,2) + pow(sf_err           /sf_raw,2)           );
    float ratio_db_err          = ratio_db        * sqrt(pow(nobs_db_err/nobs_db,2) + pow(sf_err_db        /sf_raw_db,2)        );
    float ratio_mc3_err         = ratio_mc3       * sqrt(pow(nobs_db_err/nobs_db,2) + pow(sf_err_mc3       /sf_raw_mc3,2)       );
    float ratio_eta_mc3_err     = ratio_eta_mc3   * sqrt(pow(nobs_db_err/nobs_db,2) + pow(sf_err_eta_mc3   /sf_raw_eta_mc3,2)   );
    float ratio_pt_mc3_err      = ratio_pt_mc3    * sqrt(pow(nobs_db_err/nobs_db,2) + pow(sf_err_pt_mc3/sf_raw_pt_mc3,2)        );
    float ratio_eta_pt_mc3_err  = ratio_eta_pt_mc3* sqrt(pow(nobs_db_err/nobs_db,2) + pow(sf_err_eta_pt_mc3/sf_raw_eta_pt_mc3,2));

    // print pred output
    CTable pred_calc;
    pred_calc.setTitle("calc of prediction");
    pred_calc.useTitle();
    pred_calc.setTable() (              "# FOs" , "pred"                                                                  , "ratio"                                       )
                         ( "SS obs"             ,   "N/A"           , rt::pm(nobs, nobs_err, "2.2")                       , "NA"                                          )
                         ( "SS obs db"          ,   "N/A"           , rt::pm(nobs_db, nobs_db_err, "2.2")                 , "NA"                                          )
                         ( "SF raw"             ,  nfo_sf           , rt::pm(sf_raw, sf_err, "2.2")                       , rt::pm(ratio_orig      , ratio_orig_err      )) 
                         ( "SF raw db"          ,  nfo_sf_db        , rt::pm(sf_raw_db, sf_err_db, "2.2")                 , rt::pm(ratio_db        , ratio_db_err        )) 
                         ( "SF raw mc3"         ,  nfo_sf_mc3       , rt::pm(sf_raw_mc3, sf_err_mc3, "2.2")               , rt::pm(ratio_mc3       , ratio_mc3_err       )) 
                         ( "SF raw eta, mc3"    ,  nfo_sf_eta_mc3   , rt::pm(sf_raw_eta_mc3, sf_err_eta_mc3, "2.2")       , rt::pm(ratio_eta_mc3   , ratio_eta_mc3_err   )) 
                         ( "SF raw pt, mc3"     ,  nfo_sf_pt_mc3    , rt::pm(sf_raw_pt_mc3, sf_err_pt_mc3, "2.2")         , rt::pm(ratio_pt_mc3    , ratio_pt_mc3_err    )) 
                         ( "SF raw eta, pt, mc3",  nfo_sf_eta_pt_mc3, rt::pm(sf_raw_eta_pt_mc3, sf_err_eta_pt_mc3, "2.2") , rt::pm(ratio_eta_pt_mc3, ratio_eta_pt_mc3_err));
    pred_calc.print();

    // do the single fake raw count
    //TH2F& h_sf   = *static_cast<TH2F*>(hc["h_mm_nfo_sf"]);
    //int nfo_sf   = h_sf.GetEntries();
    //float sf_raw = 0.0;
    //float sf_err = 0.0;
    //for (int etabin = 1; etabin != h_sf.GetNbinsX()+1; etabin++)
    //{  
    //    for (int ptbin = 1; ptbin != h_sf.GetNbinsY()+1; ptbin++)
    //    {  
    //        float bin_count = h_sf.GetBinContent(etabin, ptbin);
    //        //float bin_err   = h_sf.GetBinError(etabin, ptbin);
    //        float bin_err   = sqrt(bin_count); 
    //        sf_raw += bin_count; 
    //        float ptmin = h_sf.GetYaxis()->GetBinLowEdge(ptbin);
    //        float ptmax = h_sf.GetYaxis()->GetBinUpEdge(ptbin);
    //        float etamin = h_sf.GetXaxis()->GetBinLowEdge(etabin);
    //        float etamax = h_sf.GetXaxis()->GetBinUpEdge(etabin);
    //        float err_temp = 0.0;
    //        for (size_t i = 0; i != m_sf.size(); i++)
    //        {
    //            const SF& sf = m_sf.at(i);
    //            //if (ptmin > sf.fo.pt  || ptmax < sf.fo.pt) continue;
    //            if ( ptbin != h_sf.GetNbinsY())
    //            {
    //                if (ptmin > sf.fo.pt  || ptmax < sf.fo.pt) continue;
    //            }
    //            else
    //            {
    //                if (ptmin > sf.fo.pt) continue;
    //            }
    //            if (etamin > sf.fo.aeta || etamax < sf.fo.aeta) continue;

    //            float f = sf.fo.fr / (1.0 - sf.fo.fr);              // f = fr/(1-fr)
    //            float e = sf.fo.frerr * pow((1.0 - sf.fo.fr), -2);  // sigma_f = sigma_fr /(1-fr)^2
    //            err_temp += pow(e/f, 2);
    //        }
    //        sf_err += pow(bin_count*f,2) *(err_temp + pow(bin_err/bin_count, 2)); 
    //    }
    //}
    //sf_err = sqrt(sf_err);
    //cout << Form("nobs %d, sf_raw %f, sf_err %f", nobs, sf_raw, sf_err) << endl;
    
    /*
    // add DF hists
    hc["h_mm_nfo_df"]->Add(hc["h_mm_nfo_df1"], hc["h_mm_nfo_df2"], 0.5, 0.5);

    float nfo_sf     = m_sf.size(); 
    float nfo_sf_err = sqrt(nfo_sf); 
    float sf_raw = 0.0;
    float sf_err = 0.0;
    for (size_t i = 0; i != m_sf.size(); i++)
    {
        const SF& sf = m_sf.at(i);
        float f = sf.fo.fr / (1.0 - sf.fo.fr);              // f = fr/(1-fr)
        cout << Form("pt %f, eta %f, sf.fo.fr = %f, sf.fo.frerr = %f", sf.fo.pt, sf.fo.aeta, sf.fo.fr, sf.fo.frerr) << endl;
        float e = sf.fo.frerr * pow((1.0 - sf.fo.fr), -2);  // sigma_f = sigma_fr /(1-fr)^2
        cout << Form("i = %d, f = %f, e = %f", i, f, e) << endl;
        sf_raw += f; 
        //sf_err += pow(e, 2); 
        sf_err += pow(e, 2); 
    }
    sf_err = sqrt(sf_err);

    float nfo_df     = m_df.size(); 
    float nfo_df_err = sqrt(nfo_df); 
    float df_raw = 0.0;
    float df_err = 0.0;
    for (size_t i = 0; i != m_df.size(); i++)
    {
        const DF& df = m_df.at(i);
        float f1  = df.fo1.fr / (1.0 - df.fo1.fr);              // f = fr/(1-fr)
        float f2  = df.fo2.fr / (1.0 - df.fo2.fr);              // f = fr/(1-fr)
        float e1 = df.fo1.frerr * pow((1.0 - df.fo1.fr), -2);  // sigma_f = sigma_fr /(1-fr)^2
        float e2 = df.fo2.frerr * pow((1.0 - df.fo2.fr), -2);  // sigma_f = sigma_fr /(1-fr)^2
        df_raw += f1 * f2; 
        df_err += pow(f1*f2, 2) * (pow(e1/f1, 2) + pow(e2/f2, 2)); 
    }
    df_err = sqrt(df_err);

    float df_pred       = df_raw;
    float df_pred_err   = !m_df.empty() ? df_raw * sqrt((pow(df_err/df_raw,2) + pow(nfo_df_err/nfo_df,2))) : 0.0;
    float sf_raw_err    = !m_sf.empty() ? sf_raw * sqrt((pow(sf_err/sf_raw,2) + pow(nfo_sf_err/nfo_sf,2))) : 0.0;
    float sf_pred       = sf_raw - 2*df_raw;
    float sf_pred_err   = sqrt(pow(sf_raw_err, 2) + pow(2*df_pred_err, 2)); 
    float fake_pred     = sf_pred + df_pred;
    float fake_pred_err = sqrt(pow(sf_pred_err,2) + pow(df_pred_err,2));
    float mc_pred     = 0;
    float mc_pred_err = 0;
    switch (m_nbtags)
    {
        case 0: mc_pred = 11.34; mc_pred_err = 0.342; break;
        case 2: mc_pred = 1.27;  mc_pred_err = 0.10;  break;
        default: break;
    }
    //float pred = mc_pred + fake_pred;
    float pred = fake_pred;
    float pred_err = sqrt(pow(mc_pred_err,2) + pow(fake_pred_err,2));

    cout << Form("nfo_sf %f, nfo_sf_err %f", nfo_sf, nfo_sf_err) << endl;
    cout << Form("nfo_sf %f, nfo_sf_err %f", nfo_sf, nfo_sf_err) << endl;

    // print pred output
    CTable pred_calc;
    pred_calc.setTitle("calc of prediction");
    pred_calc.useTitle();
    pred_calc.setTable() (              "# FOs", "pred"                                  )
                         ( "SS obs"    ,   "N/A", nobs                                   )
                         ( "SF raw"    ,  nfo_sf, rt::pm(sf_raw, sf_raw_err, "2.2")      )
                         ( "SF pred"   ,   "N/A", rt::pm(sf_pred, sf_pred_err, "2.2")    )
                         ( "DF pred"   ,  nfo_df, rt::pm(df_pred, df_pred_err, "2.2")    )
                         ( "fake pred" ,   "N/A", rt::pm(fake_pred, fake_pred_err, "2.2"))
                         //( "MC pred"   ,   "N/A", rt::pm(mc_pred, mc_pred_err)           )
                         ( "pred"      ,   "N/A", rt::pm(pred, pred_err)                 );
    pred_calc.print();
    cout << endl << endl;
    */

    if (m_verbose)
    {
        hc.List();
    }
}

// binning contants
//std::tr1::array<float, 9> mu_vtx_bins = {{ 0.0,  3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0, 30.0}};
//std::tr1::array<float, 9> el_vtx_bins = {{ 0.0,  3.0, 6.0, 9.0, 12.0, 15.0, 18.0, 21.0, 30.0}};
//std::tr1::array<float, 6> mu_pt_bins  = {{ 5.0, 10.0, 15.0, 20.0, 25.0, 35.0}};
//std::tr1::array<float, 6> mu_pt_bins  = {{ 20.0, 25.0, 30.0, 35.0, 45.0, 55.0}};
std::tr1::array<float, 4> mu_pt_bins  = {{ 20.0, 25.0, 30.0, 35.0}};
//std::tr1::array<float, 4> mu_pt_bins  = {{20.0, 25.0, 30.0, 35.0}};
//std::tr1::array<float, 6> el_pt_bins  = {{10.0, 15.0, 20.0, 25.0, 35.0, 55.0}};
//std::tr1::array<float, 5> mu_eta_bins = {{0.0, 1.0, 1.5, 2.0, 2.4}};
std::tr1::array<float, 5> mu_eta_bins = {{0.0, 1.0, 1.479, 2.0, 2.5}};
//std::tr1::array<float, 5> el_eta_bins = {{0.0, 1.0, 1.5, 2.0, 2.4}};
//std::tr1::array<float, 13> mc3_pt_bins = {{5.00, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40, 45, 50, 60, 70, 100}};
//std::tr1::array<float, 11> mc3_pt_bins = {{0.00, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0}};
//std::tr1::array<float, 16> mc3_pt_bins = {{0.00, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110, 120, 130, 140, 150}};
//std::tr1::array<float, 13> mc3_pt_bins = {{0.00, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110, 130}};
//std::tr1::array<float, 14> mc3_pt_bins = {{5.00, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40, 45, 50, 60, 70, 80, 100}};
std::tr1::array<float, 13> mc3_pt_bins = {{5.00, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40, 45, 50, 60, 70, 80}};
//std::tr1::array<float, 13> mc3_pt_bins = {{5.00, 10.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40, 45, 50, 60, 70, 80}};
//std::tr1::array<float, 37> mc3_pt_bins = 
//{{
//    20, 22, 24, 26, 28, 
//    30, 32, 34, 36, 38, 
//    40, 42, 44, 46, 48, 
//    50, 52, 54, 56, 58, 
//    60, 62, 64, 66, 68, 
//    70, 72, 74, 76, 78, 
//    80, 82, 84, 86, 88, 
//    90, 100 
//}};
//std::tr1::array<float, 43> mc3_pt_bins = 
//{{
//    20, 22, 24, 26, 28, 
//    30, 32, 34, 36, 38, 
//    40, 45, 
//    50, 55,
//    60, 65,
//    70, 75,
//    80, 85,
//    90, 95,
//    100,105,
//    110,115,
//    120,125,
//    130,135,
//    140,145,
//    150,155,
//    160,165,
//    170,175,
//    180,185,
//    190,195,
//    200
//}};

// book hists 
 void FakePredLooper::BookHists()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;
    TH1::SetDefaultSumw2(true);

    // Fake Counts
    //hc.Add(new TH1F("h_mm_nfo_sf", "SF count", 3, -0.5, 0.5));
    //hc.Add(new TH1F("h_mm_nfo_df", "DF count", 3, -0.5, 0.5));
    //hc.Add(new TH1F("h_mm_nobs"   , "n obs SS events;count"        , 3, -0.5, 2.5)); 
    hc.Add(new TH2F("h_mm_nfo_sf" , "nFO SF;|#eta|;p_{T}"          , mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()));
    hc.Add(new TH2F("h_mm_sf_raw" , "SF raw;|#eta|;p_{T}"          , mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()));
    hc.Add(new TH2F("h_mm_nfo_df1", "nFO DF (lepton1);|#eta|;p_{T}", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()));
    hc.Add(new TH2F("h_mm_nfo_df2", "nFO DF (lepton2);|#eta|;p_{T}", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()));
    hc.Add(new TH2F("h_mm_nfo_df" , "nFO DF;|#eta|;p_{T}"          , mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()));

    hc.Add(new TH1F("h_mm_nobs"        , "n obs SS events;count"          , 3, -0.5, 2.5)); 
    hc.Add(new TH1F("h_mm_nobs_directb", "n obs SS events (directb);count", 3, -0.5, 2.5)); 

    hc.Add(new TH2F("h_mm_nfo_sf_eta_pt"        , "# SF events;|#eta^{fo}|;p_{T}^{fo}"                , mu_eta_bins.size()-1 , mu_eta_bins.data() , mu_pt_bins.size()-1 , mu_pt_bins.data()));
    hc.Add(new TH2F("h_mm_nfo_sf_eta_pt_directb", "# SF events (matched to b);|#eta^{fo}|;p_{T}^{fo}" , mu_eta_bins.size()-1 , mu_eta_bins.data() , mu_pt_bins.size()-1 , mu_pt_bins.data()));
    hc.Add(new TH1F("h_mm_nfo_sf_mc3"           , "# SF events;p_{T}^{b}"                             , mc3_pt_bins.size()-1 , mc3_pt_bins.data()));
    hc.Add(new TH2F("h_mm_nfo_sf_eta_mc3"       , "# SF events;|#eta^{fo}|;p_{T}^{b}"                 , mu_eta_bins.size()-1 , mu_eta_bins.data() , mc3_pt_bins.size()-1, mc3_pt_bins.data()));
    hc.Add(new TH2F("h_mm_nfo_sf_pt_mc3"        , "# SF events;|p_{T}^{fo}|;p_{T}^{b}"                , mu_pt_bins.size()-1  , mu_pt_bins.data()  , mc3_pt_bins.size()-1, mc3_pt_bins.data()));
    hc.Add(new TH3F("h_mm_nfo_sf_eta_pt_mc3"    , "# SF events;|#eta^{fo}|;p_{T}^{fo};p_{T}^{b}"      , mu_eta_bins.size()-1 , mu_eta_bins.data() , mu_pt_bins.size()-1 , mu_pt_bins.data(), mc3_pt_bins.size()-1, mc3_pt_bins.data()));

    // Fake Errors 
    hc.Add(new TH2F("h_mm_sf_err", "SF error", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()));
    hc.Add(new TH2F("h_mm_df_err", "DF error", mu_eta_bins.size()-1, mu_eta_bins.data(), mu_pt_bins.size()-1, mu_pt_bins.data()));
    //hc["h_mm_sf_err"]->GetXaxis()->ImportAttributes(m_fr.h_fake_rate.GetXaxis());
    //hc["h_mm_sf_err"]->GetYaxis()->ImportAttributes(m_fr.h_fake_rate.GetYaxis());
        
    return;
}

    // main analysis function operator 
int FakePredLooper::operator()(long event)
{
    using namespace std;
    using namespace ssb;

    try
    {
        // base analysis
        at::AnalysisWithHist::operator()(event);

        // convenience alias
        rt::TH1Container& hc = m_hist_container;

        // which dataset
        //bool is_data  = m_dataset=="data";
        //bool is_qcd   = m_dataset=="qcd";
        //bool is_ttbar = m_dataset=="ttbar";

        // selections 
        // ----------------------------------------------------------------------------------------------------------------------------//

        if (nvtxs() >= 3 && nvtxs() <= 8)
        //if (nvtxs() >= 14)
        {
            return 0;
        }
       
        // mm events for now
        if (type() != 1)
        {
            return 0;
        }

        // don't care about OS
        if (isOS())
        {
            return 0;
        }

        // two jet events
        if (njets() < 2)
        {
            return 0;
        }

        // two btagged jets
        if (nbtags() < m_nbtags)
        {
            return 0;
        }
  
        // keep on FO's from B's
        if (m_directb)
        {
          // do nothing yet
        }


        
        //// require FO to be not from W and num to be from W
        //bool wlep_req1 = fo1() ? isWlep1() < 1 : isWlep1()==1;
        //bool wlep_req2 = fo2() ? isWlep2() < 1 : isWlep2()==1;
        //if (not(wlep_req1 && wlep_req2))
        //{
        //    return 0;
        //}

        // Fill Hists 
        // ----------------------------------------------------------------------------------------------------------------------------//
       
        float fr1     = m_fr.GetValue(pt1(), eta1());
        float fr2     = m_fr.GetValue(pt2(), eta2());
        float fr_weight = 1.0;
        float fr_err1 = m_fr.GetError(pt1(), eta1());
        float fr_err2 = m_fr.GetError(pt2(), eta2());

        //float fr_error  = 0.0;
        if (isSF())
        {
            fr_weight = fo1()*fr1/(1.0-fr1) + fo2()*fr2/(1.0-fr2);
        }
        else if (isDF())
        {
            fr_weight = fr1/(1.0-fr1) * fr2/(1.0-fr2);
            //fr_error = 
            //pred_error = pred * sqrt(pow(frError1/fr1, 2) + pow(frError2/fr2, 2) + pow(nFOsError/nFOs, 2));
        }

        if (isSS())
        {
            bool mc3_matched  = (mc3id1()!=-999 && mc3id2()!=-999);
		    bool direct_b_l1  = (mc3_matched && abs(mc3id1())==5 && idIsBeauty(mcmomid1()) && isWlep1()<1);
		    bool direct_b_l2  = (mc3_matched && abs(mc3id2())==5 && idIsBeauty(mcmomid2()) && isWlep2()<1);
		    bool fromW_l1     = (isWlep1()==1);
		    bool fromW_l2     = (isWlep2()==1);
            bool direct_b     = mc3_matched && ((direct_b_l1 && fromW_l2) || (direct_b_l2 && fromW_l1));

            rt::Fill(hc["h_mm_nobs"], 1.0);
            if (direct_b)
            {
                rt::Fill(hc["h_mm_nobs_directb"], 1.0);
            }
        }
        if (isSF())
        {
            float sf_eta    = fo1() ? fabs(eta1())  : fabs(eta2());
            float sf_pt     = fo1() ? pt1()         : pt2();
            float sf_fr     = fo1() ? fr1           : fr2;
            float sf_fr_err = fo1() ? fr_err1       : fr_err2;
            float sf_mc3pt  = fo1() ? mc3p41().pt() : mc3p42().pt();
            int sf_mc3id    = fo1() ? mc3id1()      : mc3id2();
            int sf_mcmomid  = fo1() ? mcmomid1()    : mcmomid2();
            bool not_from_w = fo1() ? isWlep1()<1   : isWlep2()<1;
		
            // mc3 matching
		    bool mc3_matched = (sf_mc3id != -999);
		    //bool direct_b    = (mc3_matched && abs(sf_mc3id)==5 && idIsBeauty(sf_mcmomid) && not_from_w && (sf_mc3pt > sf_pt));
		    bool direct_b    = (mc3_matched && abs(sf_mc3id)==5 && idIsBeauty(sf_mcmomid) && not_from_w);

            // Fill
            rt::Fill2D(hc["h_mm_sf_raw"       ], sf_eta, sf_pt, fr_weight);
            rt::Fill2D(hc["h_mm_nfo_sf"       ], sf_eta, sf_pt, 1.0);
            rt::Fill2D(hc["h_mm_nfo_sf_eta_pt"], sf_eta, sf_pt, 1.0);
            if (direct_b)
            {
                rt::Fill2D(hc["h_mm_nfo_sf_eta_pt_directb"], sf_eta, sf_pt,           1.0);
                rt::Fill  (hc["h_mm_nfo_sf_mc3"           ], sf_mc3pt,                1.0);
                rt::Fill2D(hc["h_mm_nfo_sf_eta_mc3"       ], sf_eta, sf_mc3pt,        1.0);
                rt::Fill2D(hc["h_mm_nfo_sf_pt_mc3"        ], sf_pt , sf_mc3pt,        1.0);
                rt::Fill3D(hc["h_mm_nfo_sf_eta_pt_mc3"    ], sf_eta, sf_pt, sf_mc3pt, 1.0);
            }

            m_sf.push_back(SF(sf_pt, sf_eta, sf_fr, sf_fr_err));  
        }
        if (isDF())
        {
            rt::Fill2D(hc["h_mm_nfo_df1"], fabs(eta1()), pt1(), fr_weight);
            rt::Fill2D(hc["h_mm_nfo_df2"], fabs(eta2()), pt2(), fr_weight);
            m_df.push_back(DF(pt1(), eta1(), fr1, fr_err1, pt2(), eta2(), fr2, fr_err2));  
        }
       
    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
    }

    // analysis end
    return 0;
} 
