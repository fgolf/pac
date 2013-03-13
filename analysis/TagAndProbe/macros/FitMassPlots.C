#include <iostream>
#include "rt/RootTools.h" 
#include "TCanvas.h" 
#include "TFile.h" 
//#include "TF1.h" 
//#include "TMath.h" 
//#include "TROOT.h" 
#include "TROOT.h"
#include "TH1D.h"
#include "TTree.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooAbsPdf.h"
#include "RooBreitWigner.h"
#include "RooCBShape.h"
#include "RooGaussian.h"
#include "RooFFTConvPdf.h"
#include "RooDataHist.h"
#include "RooHistPdf.h"
#include "RooKeysPdf.h"
#include "RooCategory.h"
#include "RooFormulaVar.h"
#include "RooSimultaneous.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"
#include "RooExtendPdf.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooRealVar.h"
#include "RooExponential.h"
#include "RooGenericPdf.h"
#include "RooPlot.h"

#include "PerformFits.h"
#include "CTable.h"

using namespace std;

// needs to be automated somehowe
const size_t npt_bins  = 6; const float pt_bins [] = {10, 15, 20, 30, 40, 50, 200};
const size_t neta_bins = 5; const float eta_bins[] = {0, 0.8, 1.4442, 1.566, 2.0, 2.5};

CTable FitMassPlots(const std::string& data_filename = "", const std::string& mc_filename = "", const string& output_path = "test", const std::string& suffix = "eps")
{
    // histograms
    rt::TH1Container hc_data(data_filename); 
    rt::TH1Container hc_mc(mc_filename); 

    // make the output dir
    rt::mkdir("plots/" + output_path, /*force=*/true);
    
    CTable t;
    t.useTitle();
    t.setTitle("data/MC efficiency and scale factor");

    //for (size_t pt_bin = 0; pt_bin != npt_bins; pt_bin++)
    for (size_t pt_bin = 0; pt_bin != 1; pt_bin++)
    {
        const float pt_min = pt_bins[pt_bin];
        const float pt_max = pt_bins[pt_bin+1];
        const string pt_label = Form("%1.0f GeV < p_{T} < %1.0f GeV", pt_min, pt_max); 
        t.setColLabel(pt_label, pt_bin);

        //for (size_t eta_bin = 0; eta_bin != neta_bins; eta_bin++)
        for (size_t eta_bin = 0; eta_bin != 1; eta_bin++)
        {
            const float eta_min = eta_bins[eta_bin];
            const float eta_max = eta_bins[eta_bin+1];
            const string eta_label = Form("%1.2f < |\\eta| < %1.2f", eta_min, eta_max); 
            t.setRowLabel(eta_label, eta_bin);

            const string hist_pass_name = Form("h_pass_pt%lu_eta%lu", pt_bin, eta_bin);
            const string hist_fail_name = Form("h_fail_pt%lu_eta%lu", pt_bin, eta_bin);
            
            TH1F* h_data_pass = dynamic_cast<TH1F*>(hc_data[hist_pass_name]);
            TH1F* h_data_fail = dynamic_cast<TH1F*>(hc_data[hist_fail_name]);
            TH1F* h_mc_pass   = dynamic_cast<TH1F*>(hc_mc  [hist_pass_name]);
            TH1F* h_mc_fail   = dynamic_cast<TH1F*>(hc_mc  [hist_fail_name]);

            t.setCell(hist_pass_name, eta_bin, pt_bin);
            
            // do the fit
            tp::Result dr = tp::PerformSimultaneousFit(h_data_pass, h_data_fail, pt_label, eta_label);
            dr.cpass->cd();
            dr.cpass->Draw();
            dr.cpass->Print(Form("plots/%s/p_data_pass_pt%lu_eta%lu.%s", output_path.c_str(), pt_bin, eta_bin, suffix.c_str()));
            dr.cfail->cd();
            dr.cfail->Draw();
            dr.cfail->Print(Form("plots/%s/p_data_fail_pt%lu_eta%lu.%s", output_path.c_str(), pt_bin, eta_bin, suffix.c_str()));
            
            // count the MC
            tp::Result mr = tp::PerformSimpleCount(h_mc_pass, h_mc_fail, pt_label, eta_label);
            mr.cpass->cd();
            mr.cpass->Draw();
            mr.cpass->Print(Form("plots/%s/p_mc_pass_pt%lu_eta%lu.%s", output_path.c_str(), pt_bin, eta_bin, suffix.c_str()));
            mr.cfail->cd();
            mr.cfail->Draw();
            mr.cpass->Print(Form("plots/%s/p_mc_fail_pt%lu_eta%lu.%s", output_path.c_str(), pt_bin, eta_bin, suffix.c_str()));
            
            // scale factor
            float dr_err = std::max(dr.eff_err_high, dr.eff_err_low);
            float mr_err = std::max(mr.eff_err_high, mr.eff_err_low);
            float sf_val = dr.eff/mr.eff;
            float sf_err = sf_val * sqrt(pow(dr_err/dr.eff, 2) + pow(mr_err/mr.eff, 2));
            string sf    = rt::pm(sf_val, sf_err, "1.3");
            
            t.setCell(sf, eta_bin, pt_bin); 
        }
    }


    //    TH1F* h_data_pass = dynamic_cast<TH1F*>(hc_data["h_pass_pt0_eta0"]);
    //    TH1F* h_data_fail = dynamic_cast<TH1F*>(hc_data["h_fail_pt0_eta0"]);
    //
    //    TH1F* h_mc_pass = dynamic_cast<TH1F*>(hc_mc["h_pass_pt0_eta0"]);
    //    TH1F* h_mc_fail = dynamic_cast<TH1F*>(hc_mc["h_fail_pt0_eta0"]);
    //
    //    // make the output dir
    //    rt::mkdir("plots/" + output_path, /*force=*/true);
    //
    //    // do the fit
    //    tp::Result dr = tp::PerformSimultaneousFit(h_data_pass, h_data_fail);
    //    dr.cpass->cd();
    //    dr.cpass->Draw();
    //    dr.cpass->Print(Form("plots/%s/p_data_pass.%s", output_path.c_str(), suffix.c_str()));
    //    dr.cfail->cd();
    //    dr.cfail->Draw();
    //    dr.cfail->Print(Form("plots/%s/p_data_fail.%s", output_path.c_str(), suffix.c_str()));
    //
    //    // count the MC
    //    tp::Result mr = tp::PerformSimpleCount(h_mc_pass, h_mc_fail);
    //    mr.cpass->cd();
    //    mr.cpass->Draw();
    //    mr.cpass->Print(Form("plots/%s/p_mc_pass.%s", output_path.c_str(), suffix.c_str()));
    //    mr.cfail->cd();
    //    mr.cfail->Draw();
    //    mr.cfail->Print(Form("plots/%s/p_mc_fail.%s", output_path.c_str(), suffix.c_str()));
    //
    //    // scale factor
    //    float dr_err = std::max(dr.eff_err_high, dr.eff_err_low);
    //    float mr_err = std::max(mr.eff_err_high, mr.eff_err_low);
    //    float sf_val = dr.eff/mr.eff;
    //    float sf_err = sf_val * sqrt(pow(dr_err/dr.eff, 2) + pow(mr_err/mr.eff, 2));
    //    string sf    = rt::pm(sf_val, sf_err, "1.3");
    //
    //    // print the output
    //    CTable t;
    //    t.useTitle();
    //    t.setTitle("data/MC efficiency and scale factor");
    //    t.setTable() (            "data eff", "mc eff",  "data/mc SF")
    //                 ("pt0_eta0",   dr.str(), mr.str(), sf); 
    return t;
}

#ifndef __CINT__
int main()
{
    CTable t_id   = FitMassPlots("plots/EgammaID/electron/raw_plots.root"  , "plots/EgammaID/electronMC/raw_plots.root"  , "test/id"  );
    //CTable t_iso  = FitMassPlots("plots/EgammaIso/electron/raw_plots.root" , "plots/EgammaIso/electronMC/raw_plots.root" , "test/iso" );
    //CTable t_both = FitMassPlots("plots/EgammaBoth/electron/raw_plots.root", "plots/EgammaBoth/electronMC/raw_plots.root", "test/both");

    t_id.setTitle("data/MC eff and SF for electron ID");
    //t_iso.setTitle("data/MC eff and SF for electron Iso");
    //t_both.setTitle("data/MC eff and SF for electron Iso+ID");

    t_id.print();
    //t_iso.print();
    //t_both.print();

    return 0;
}
#endif

