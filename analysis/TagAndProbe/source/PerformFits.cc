#include "PerformFits.h"

// c++
#include <string>
#include <stdexcept>
#include <algorithm>

// ROOT
#include "TCanvas.h"
#include "TH1.h"
#include "TLatex.h"

// RooFit
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "RooPlot.h"
#include "RooBreitWigner.h"
#include "RooFFTConvPdf.h"
#include "RooCBShape.h"
#include "RooAddPdf.h"
#include "RooExponential.h"
#include "RooVoigtian.h"
#include "RooExtendPdf.h"
#include "RooSimultaneous.h"
#include "RooCategory.h"

#include "rt/RootTools.h"
#include "Constants.h"

using namespace std;

typedef RooAbsPdf* RooAbsPdfPtr;

namespace tp
{
    // PDF defintions
    // ----------------------------------------------------------------- //

    // simple base class to hold the PDF types
    struct PdfBase
    {
        PdfBase() {}
        RooAbsPdfPtr model;
    };

    struct BreitWignerCBPdf : public PdfBase
    {
        BreitWignerCBPdf(RooRealVar& x, const std::string& label);
        RooRealVar* mz;
        RooRealVar* gammaz;
        RooBreitWigner* bw;
        RooRealVar* mean;
        RooRealVar* sigma;
        RooRealVar* alpha;
        RooRealVar* n;
        RooCBShape* cb;
    };

    BreitWignerCBPdf::BreitWignerCBPdf(RooRealVar& x, const std::string& label)
    {
        // z mass 
        string title = Form("mz%s", label.c_str());
        mz = new RooRealVar(title.c_str(), title.c_str(), 91, 80, 100, "GeV");
        mz->setVal(91.1876);
        mz->setConstant(kTRUE);

        // z width
        title = Form("gammaz%s", label.c_str());
        gammaz = new RooRealVar(title.c_str(), title.c_str(), 2.5, 0.1, 5, "GeV");
        gammaz->setVal(2.4952);
        gammaz->setConstant(kTRUE);

        // the BW
        title = Form("bw%s", label.c_str());
        bw = new RooBreitWigner(title.c_str(), title.c_str(), x, *mz, *gammaz);

        // Crystal ball
        title = Form("mean%s"  , label.c_str()); mean  = new RooRealVar(title.c_str(), title.c_str(), 0 , -10 , 10);
        title = Form("gammaz%s", label.c_str()); sigma = new RooRealVar(title.c_str(), title.c_str(), 1 , 0.1 , 5);
        title = Form("alpha%s" , label.c_str()); alpha = new RooRealVar(title.c_str(), title.c_str(), 5 , 0   , 20);
        title = Form("n%s"     , label.c_str()); n     = new RooRealVar(title.c_str(), title.c_str(), 1 , 0   , 10);
        title = Form("cb%s"    , label.c_str()); cb    = new RooCBShape(title.c_str(), title.c_str(), x, *mean , *sigma , *alpha , *n);
        title = Form("BWconvCB%s", label.c_str());
        model = RooAbsPdfPtr(new RooFFTConvPdf(title.c_str(), title.c_str(), x, *bw, *cb));
    }

    struct ExponentialPdf : public PdfBase
    {
        ExponentialPdf(RooRealVar& x, const std::string& label);
        RooRealVar* t;
        RooExponential* cb;
    };

    ExponentialPdf::ExponentialPdf(RooRealVar& x, const std::string& label)
    {
            string title = Form("t%s", label.c_str()); 
            t = new RooRealVar(title.c_str(), title.c_str(), -0.1, -1.0, 0.0);

            title = Form("exp%s", label.c_str()); 
            model = RooAbsPdfPtr(new RooExponential(title.c_str(), title.c_str(), x, *t));
    }

    // wrapper to get the PDFs
    PdfBase* CreateModelPdf(Model::value_type model, RooRealVar &x, const std::string& label = "")
    {
        switch (model)
        {
            case Model::BreitWignerCB: return new BreitWignerCBPdf(x, label); break;
            case Model::Exponential:   return new ExponentialPdf(x, label);   break;
            default:
                throw std::invalid_argument("[tp::CreateModelPdf] Error: model not supported");
        }

        // return NULL pointer (should never get here)
        return new PdfBase;
    }

    // construct
    Result::Result(float e, float eh, float el)
        : eff(e)
        , eff_err_high(eh)
        , eff_err_low(el)
        , cpass(new TCanvas("cpass", "cpass", 800, 600))
        , cfail(new TCanvas("cfail", "cfail", 800, 600))
    {
    }

    Result::Result()
        : eff(0)
        , eff_err_high(0)
        , eff_err_low(0)
        , cpass(new TCanvas("cpass", "cpass", 800, 600))
        , cfail(new TCanvas("cfail", "cfail", 800, 600))
    {
    }

    std::string Result::str() const
    {
        return rt::pm(eff, std::max(eff_err_high, eff_err_low), "1.3");
    }


    // Peform the fit
    Result PerformSimultaneousFit
    (
        //const Model::value_type model, 
        const TH1* const h_pass, 
        const TH1* const h_fail,
        const std::string pt_label, 
        const std::string eta_label, 
        const float mlow,
        const float mhigh
    )
    {
        // independent mass var
        RooRealVar mass("mass", "mass", mlow, mhigh, "GeV");

        // Define categories
        RooCategory sample("sample","");
        sample.defineType("pass",1);
        sample.defineType("pail",2);

        // signal model (need ptr for polymorphism to work -- references for convenience)
        PdfBase* spass_model_ptr = CreateModelPdf(Model::BreitWignerCB, mass, "_pass");
        PdfBase* sfail_model_ptr = CreateModelPdf(Model::BreitWignerCB, mass, "_fail");
        RooAbsPdf& spass_model = *(spass_model_ptr->model);
        RooAbsPdf& sfail_model = *(sfail_model_ptr->model);

        // background model (need ptr for polymorphism to work -- references for convenience)
        PdfBase* bpass_model_ptr = CreateModelPdf(Model::Exponential,  mass, "_pass");
        PdfBase* bfail_model_ptr = CreateModelPdf(Model::Exponential,  mass, "_fail");
        RooAbsPdf& bpass_model = *(bpass_model_ptr->model);
        RooAbsPdf& bfail_model = *(bfail_model_ptr->model);

        // count maximums
        double nsig_max      = h_pass->Integral() + h_fail->Integral();
        double nbkg_fail_max = h_fail->Integral();
        double nbkg_pass_max = h_pass->Integral();

        RooRealVar eff("eff", "Efficiency", 0.8 ,0 ,1.0);
        RooRealVar nsig("nsig", "Signal Yield", 0.80*nsig_max, 0, nsig_max);
        RooRealVar nbkg_pass("nbkg_pass","Background count in PASS sample", 50, 0, nbkg_pass_max);
        RooRealVar nbkg_fail("nbkg_fail","Background count in FAIL sample", 0.1*nbkg_fail_max, 0.01, nbkg_fail_max);
        RooFormulaVar nsig_pass("nsig_pass" ,"eff*nsig"      , RooArgList(eff, nsig));
        RooFormulaVar nsig_fail("nsign_fail","(1.0-eff)*nsig", RooArgList(eff, nsig));

        // efficiency counts
        RooExtendPdf esig_pass("esig_pass","esig_pass", spass_model, nsig_pass, "signalRange");
        RooExtendPdf ebkg_pass("ebkg_pass","ebkg_pass", bpass_model, nbkg_pass, "signalRange");
        RooAddPdf model_pass("model_pass","Model for PASS sample", RooArgList(esig_pass, ebkg_pass));

        RooExtendPdf esig_fail("esig_fail","esig_fail", sfail_model, nsig_fail, "signalRange");
        RooExtendPdf ebkg_fail("ebkg_fail","ebkg_fail", bfail_model, nbkg_fail, "signalRange");
        RooAddPdf model_fail("model_fail","Model for Fail sample", RooArgList(esig_fail, ebkg_fail));

        // import data histograms
        RooDataHist data_pass("data_pass", "data_pass", RooArgSet(mass), h_pass);
        RooDataHist data_fail("data_fail", "data_fail", RooArgSet(mass), h_fail);
        RooDataHist data_comb("data_comb", "data_comb", RooArgList(mass), RooFit::Index(sample), RooFit::Import("pass", data_pass), RooFit::Import("fail", data_fail));  

        // for the total PDF
        RooSimultaneous total_pdf("total_pdf","total_pdf",sample);
        total_pdf.addPdf(model_pass, "pass");  
        total_pdf.addPdf(model_fail, "fail");
        total_pdf.fitTo(data_comb, RooFit::Extended(), RooFit::Strategy(1), RooFit::Save());

        // results of eff
        Result fit_result(eff.getVal(), eff.getErrorHi(), eff.getErrorLo()); 
  
        // passing plot
        fit_result.cpass->cd(); 
        RooPlot *mframe_pass = mass.frame(RooFit::Bins(static_cast<int>(fabs(mhigh-mlow)/tp::MassBinWidth)));
        data_pass.plotOn(mframe_pass, RooFit::MarkerStyle(kFullCircle), RooFit::MarkerSize(0.8), RooFit::DrawOption("ZP"));
        model_pass.plotOn(mframe_pass);
        model_pass.plotOn(mframe_pass,RooFit::Components("ebkg_pass"), RooFit::LineStyle(kDashed), RooFit::LineColor(kRed));
        mframe_pass->Draw();
        TLatex pt_box(0.21, 0.85, pt_label.c_str());
        pt_box.Draw();
//   plotPass.AddTextBox(binlabelx,0.21,0.85,0.51,0.90,0,kBlack,-1);
//   if((name.CompareTo("etapt")==0) || (name.CompareTo("etaphi")==0)) {
//     plotPass.AddTextBox(binlabely,0.21,0.80,0.51,0.85,0,kBlack,-1);        
//     plotPass.AddTextBox(yield,0.21,0.76,0.51,0.80,0,kBlack,-1);    
//   } else {
//     plotPass.AddTextBox(yield,0.21,0.81,0.51,0.85,0,kBlack,-1);
//   }
//   plotPass.AddTextBox(effstr,0.70,0.85,0.94,0.90,0,kBlack,-1);
//   if(bkgpass>0)
//     plotPass.AddTextBox(0.70,0.68,0.94,0.83,0,kBlack,-1,2,nsigstr,nbkgstr);//,chi2str);
//   else
//     plotPass.AddTextBox(0.70,0.73,0.94,0.83,0,kBlack,-1,1,nsigstr);//,chi2str);
//      plotPass.Draw(cpass,kTRUE,format);

        // failing plot
        fit_result.cfail->cd(); 
        RooPlot *mframe_fail = mass.frame(RooFit::Bins(static_cast<int>(fabs(mhigh-mlow)/tp::MassBinWidth)));
        data_fail.plotOn(mframe_fail, RooFit::MarkerStyle(kFullCircle), RooFit::MarkerSize(0.8), RooFit::DrawOption("ZP"));
        model_fail.plotOn(mframe_fail);
        model_fail.plotOn(mframe_fail,RooFit::Components("ebkg_fail"), RooFit::LineStyle(kDashed), RooFit::LineColor(kRed));
        mframe_fail->Draw();

        // done 
        return fit_result;
    }

    // Peform the fit
    Result PerformSimpleCount
    (
        //const Model::value_type model, 
        TH1* const h_pass, 
        TH1* const h_fail,
        const std::string pt_label, 
        const std::string eta_label, 
        const float mlow,
        const float mhigh
    )
    {
        // connts
        double num_pass  = h_pass->Integral();
        double num_fail  = h_fail->Integral();
        double num_total = num_pass + num_fail;
        double eff_total = num_pass/(num_pass + num_total);
        double err_total = sqrt(eff_total * (1.0 - eff_total)/num_total); // binomial

        Result fit_result;
        fit_result.eff = num_pass/num_total;
        fit_result.eff_err_low  = err_total;
        fit_result.eff_err_high = err_total;

        fit_result.cpass->cd();
        h_pass->Draw();

        fit_result.cfail->cd();
        h_fail->Draw();

        return fit_result;
    }

} // namespace tp
