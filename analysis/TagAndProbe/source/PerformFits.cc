#include "PerformFits.h"

// c++
#include <string>
#include <stdexcept>
#include <algorithm>

// ROOT
#include "TCanvas.h"
#include "TH1.h"
#include "TLatex.h"
#include "TPaveText.h"

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
#include "RooProdPdf.h"
#include "RooExponential.h"
#include "RooVoigtian.h"
#include "RooExtendPdf.h"
#include "RooSimultaneous.h"
#include "RooCategory.h"
#include "RooGenericPdf.h"
#include "RooPolynomial.h"
#include "RooChebychev.h"

// Tools
#include "rt/RootTools.h"
#include "RooCMSShape.h"
#include "Constants.h"

using namespace std;

typedef RooAbsPdf* RooAbsPdfPtr;

namespace tp
{
    // PDF defintions
    // ----------------------------------------------------------------- //
    // ----------------------------------------------------------------- //

    // simple base class to hold the PDF types
    struct PdfBase
    {
        PdfBase() {}
        RooAbsPdfPtr model;
    };

    // BreitWigner * Cyrtal Ball  
    // ----------------------------------------------------------------- //

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
        mz->setVal(Mz);
        //mz->setConstant(kTRUE);

        // z width
        title = Form("gammaz%s", label.c_str());
        gammaz = new RooRealVar(title.c_str(), title.c_str(), 2.5, 0.1, 10, "GeV");
        gammaz->setVal(GammaZ);
        //gammaz->setConstant(kTRUE);

        // the BW
        title = Form("bw%s", label.c_str());
        bw = new RooBreitWigner(title.c_str(), title.c_str(), x, *mz, *gammaz);

        // Crystal ball
        title = Form("mean%s"  , label.c_str()); mean  = new RooRealVar(title.c_str(), title.c_str(), 0 , -10 , 10);
        title = Form("gammaz%s", label.c_str()); sigma = new RooRealVar(title.c_str(), title.c_str(), 1 , 0.1 , 10);
        title = Form("alpha%s" , label.c_str()); alpha = new RooRealVar(title.c_str(), title.c_str(), 5 , 0   , 20);
        title = Form("n%s"     , label.c_str()); n     = new RooRealVar(title.c_str(), title.c_str(), 1 , 0   , 10);
        title = Form("cb%s"    , label.c_str()); cb    = new RooCBShape(title.c_str(), title.c_str(), x, *mean , *sigma , *alpha , *n);
        title = Form("BWconvCB%s", label.c_str());
        model = RooAbsPdfPtr(new RooFFTConvPdf(title.c_str(), title.c_str(), x, *bw, *cb));
    }

    // MC template 
    // ----------------------------------------------------------------- //

    struct MCTemplateConvGausPdf : public PdfBase
    {
        MCTemplateConvGausPdf(RooRealVar &m, TH1F* hist, const std::string& label, RooRealVar *sigma0=0, int intOrder=1);
        RooRealVar  *mean;
        RooRealVar  *sigma;
        RooGaussian *gaus;
//         RooRealVar* mean;
//         RooRealVar* sigma;
//         RooRealVar* alpha;
//         RooRealVar* n;
//         RooCBShape* cb;
        TH1F        *inHist;
        RooDataHist *dataHist;
        RooHistPdf  *histPdf;
    };

    MCTemplateConvGausPdf::MCTemplateConvGausPdf(RooRealVar &m, TH1F* hist, const std::string& label, RooRealVar *sigma0, int intOrder)
    {  
//         char name[10];
//         sprintf(name,"%s",label.c_str());
// 
//         char vname[50];  
// 
//         sprintf(vname,"mean%s",name);  mean  = new RooRealVar(vname,vname,0,-10,10);
//         if(sigma0) { sigma = sigma0; }
//         else       { sprintf(vname,"sigma%s",name); sigma = new RooRealVar(vname,vname,2,0,5); }
//         sprintf(vname,"gaus%s",name);  gaus  = new RooGaussian(vname,vname,m,*mean,*sigma);

        string title;
        title = Form("mean%s"  , label.c_str()); mean  = new RooRealVar(title.c_str(), title.c_str(), 0 , -10 , 10);
        title = Form("sigma%s" , label.c_str()); sigma = new RooRealVar(title.c_str(), title.c_str(), 2 ,   0 , 10);
        title = Form("gaus%s"  , label.c_str()); gaus  = new RooGaussian(title.c_str(), title.c_str(), m, *mean , *sigma);
//         title = Form("alpha%s" , label.c_str()); alpha = new RooRealVar(title.c_str(), title.c_str(), 5 , 0   , 20);
//         title = Form("n%s"     , label.c_str()); n     = new RooRealVar(title.c_str(), title.c_str(), 1 , 0   , 10);
//         title = Form("cb%s"    , label.c_str()); cb    = new RooCBShape(title.c_str(), title.c_str(), m, *mean , *sigma , *alpha , *n);

        title = Form("inHist_%s",hist->GetName());
        inHist = dynamic_cast<TH1F*>(hist->Clone(title.c_str()));
        title = Form("dataHist%s",label.c_str()); dataHist = new RooDataHist(title.c_str(), title.c_str(), RooArgSet(m), inHist);
        title = Form("histPdf%s" ,label.c_str()); histPdf  = new RooHistPdf(title.c_str(), title.c_str(), m,*dataHist, intOrder);
        //title = Form("signal%s"  ,label.c_str()); model    = new RooFFTConvPdf(title.c_str(), title.c_str(), m, *histPdf, *cb);
        title = Form("signal%s"  ,label.c_str()); model    = new RooFFTConvPdf(title.c_str(), title.c_str(), m, *histPdf, *gaus);
    }

    // Exponential 
    // ----------------------------------------------------------------- //

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

    // eff * Exponential 
    // ----------------------------------------------------------------- //

    struct ErfExpPdf : public PdfBase
    {
        ErfExpPdf(RooRealVar &m, const std::string& label);
        RooRealVar *alfa;
        RooRealVar *beta; 
        RooRealVar *gamma; 
        RooRealVar *peak;
    };

    ErfExpPdf::ErfExpPdf(RooRealVar& x, const std::string& label)
    {
        string title;
        title = Form("alfa%s" , label.c_str());  alfa = new RooRealVar(title.c_str(), title.c_str(), 50  ,  5, 200);
        title = Form("beta%s" , label.c_str());  beta = new RooRealVar(title.c_str(), title.c_str(), 0.01,  0, 10 );
        title = Form("gamma%s", label.c_str()); gamma = new RooRealVar(title.c_str(), title.c_str(), 0.1 ,  0, 1  );
        title = Form("peak%s" , label.c_str());  peak = new RooRealVar(title.c_str(), title.c_str(), Mz  , 85, 97 );
        peak->setConstant(kTRUE);  

        title = Form("background%s", label.c_str());
        model = RooAbsPdfPtr(new RooCMSShape(title.c_str(), title.c_str(), x, *alfa, *beta, *gamma, *peak));
    }

    // ChecychevPdf 
    // ----------------------------------------------------------------- //

    struct ChebychevPdf : public PdfBase
    {
        ChebychevPdf (RooRealVar &m, const std::string& label);
        RooRealVar *a0;
        RooRealVar *a1; 
    };

    ChebychevPdf::ChebychevPdf(RooRealVar& x, const std::string& label)
    {
        string title;
        title = Form("a0%s", label.c_str()); a0 = new RooRealVar(title.c_str(), title.c_str(), 0.0, -10, 10);
        title = Form("a1%s", label.c_str()); a1 = new RooRealVar(title.c_str(), title.c_str(), 0.0, -10, 10);

        title = Form("background%s", label.c_str());
        model = RooAbsPdfPtr(new RooChebychev(title.c_str(), title.c_str(), x, RooArgList(*a0, *a1)));
    }

    // Checychev * Exp
    // ----------------------------------------------------------------- //

    struct ChebyExpPdf : public PdfBase
    {
        ChebyExpPdf (RooRealVar &m, const std::string& label);
        RooRealVar *a0;
        RooRealVar *a1; 
        RooRealVar *t; 
        RooExponential *exp;
        RooChebychev *chevychev;
    };

    ChebyExpPdf::ChebyExpPdf(RooRealVar& x, const std::string& label)
    {
        string title;
        title = Form("a0%s", label.c_str()); a0 = new RooRealVar(title.c_str(), title.c_str(), 0.0, -10, 10);
        title = Form("a1%s", label.c_str()); a1 = new RooRealVar(title.c_str(), title.c_str(), 0.0, -10, 10);
        title = Form("t%s", label.c_str());   t = new RooRealVar(title.c_str(), title.c_str(), -0.1, -1.0, 0.0);

        title = Form("exp%s", label.c_str()); 
        exp = new RooExponential(title.c_str(), title.c_str(), x, *t);

        title = Form("background%s", label.c_str());
        chevychev = new RooChebychev(title.c_str(), title.c_str(), x, RooArgList(*a0, *a1));

        title = Form("chevyexp%s", label.c_str());
        model = RooAbsPdfPtr(new RooFFTConvPdf(title.c_str(), title.c_str(), x, *chevychev, *exp));
    }

    // Quadratic * exp (not working) 
    // ----------------------------------------------------------------- //

    // not working
    struct QuadraticExpPdf : public PdfBase
    {
        QuadraticExpPdf(RooRealVar &x, const std::string& label);
        RooRealVar *a0;
        RooRealVar *a1;
        RooRealVar *a2;
        RooRealVar *t;
        RooExponential *exp;
        RooPolynomial *poly;
    };

    // (1 + a1*m + a2*m^2) * exp{-t}
    QuadraticExpPdf::QuadraticExpPdf(RooRealVar &x, const std::string& l)
    {
        a0 = new RooRealVar(Form("a0%s", l.c_str()), Form("a0%s", l.c_str()),   0.0);//, -10.0, 10.0);
        a1 = new RooRealVar(Form("a1%s", l.c_str()), Form("a1%s", l.c_str()),   0.0);//, -10.0, 10.0);
        a2 = new RooRealVar(Form("a2%s", l.c_str()), Form("a2%s", l.c_str()),   0.0);//, -10.0, 10.0);
        t  = new RooRealVar(Form("t%s" , l.c_str()), Form("t%s" , l.c_str()), -1e-6, -10.0, 0.000);

        string title = Form("exp%s", l.c_str()); 
        exp = new RooExponential(title.c_str(), title.c_str(), x, *t);

        title = Form("poly%s", l.c_str());
        poly = new RooPolynomial(title.c_str(), title.c_str(), x, RooArgList(*a0, *a1, *a2));

        title = Form("background%s", l.c_str());
        model = RooAbsPdfPtr(new RooProdPdf(title.c_str(), title.c_str(), RooArgList(*poly, *exp)));
    }

    // 4th order polynomial * exp 
    // ----------------------------------------------------------------- //

    struct Poly4ExpPdf : public PdfBase
    {
        Poly4ExpPdf(RooRealVar &x, const std::string& label);
        RooRealVar *a0;
        RooRealVar *a1;
        RooRealVar *a2;
        RooRealVar *a3;
        RooRealVar *a4;
        RooRealVar *a5;
        RooRealVar *a6;
        RooRealVar *t;
        RooExponential *exp;
        RooPolynomial *poly;
    };

    Poly4ExpPdf::Poly4ExpPdf(RooRealVar &x, const std::string& l)
    {
        a0 = new RooRealVar(Form("a0%s", l.c_str()), Form("a0%s", l.c_str()), 0.0);
        a1 = new RooRealVar(Form("a1%s", l.c_str()), Form("a1%s", l.c_str()), 0.0);
        a2 = new RooRealVar(Form("a2%s", l.c_str()), Form("a2%s", l.c_str()), 0.0);
        a3 = new RooRealVar(Form("a3%s", l.c_str()), Form("a3%s", l.c_str()), 0.0);
        a4 = new RooRealVar(Form("a4%s", l.c_str()), Form("a4%s", l.c_str()), 0.0);
        t  = new RooRealVar(Form("t%s" , l.c_str()), Form("t%s" , l.c_str()), -1e-6, -10.0, 0.00);

        // (a0 + a1*x + a2*x^2 + a3*x^3 + a4*x^4) * exp{-t}
        string title = Form("exp%s", l.c_str()); 
        exp = new RooExponential(title.c_str(), title.c_str(), x, *t);

        title = Form("poly%s", l.c_str());
        poly = new RooPolynomial(title.c_str(), title.c_str(), x, RooArgList(*a0, *a1, *a2, *a3, *a4));

        title = Form("background%s", l.c_str());
        model = RooAbsPdfPtr(new RooProdPdf(title.c_str(), title.c_str(), RooArgList(*poly, *exp)));
    }

    // 8th order polynomial * exp 
    // ----------------------------------------------------------------- //

    struct Poly8ExpPdf : public PdfBase
    {
        Poly8ExpPdf(RooRealVar &x, const std::string& label);
        RooRealVar *a0;
        RooRealVar *a1;
        RooRealVar *a2;
        RooRealVar *a3;
        RooRealVar *a4;
        RooRealVar *a5;
        RooRealVar *a6;
        RooRealVar *a7;
        RooRealVar *a8;
        RooRealVar *t;
        RooExponential *exp;
        RooPolynomial *poly;
    };

    // Sum(an*x^n) * exp{-|t|*x}, n = 0, 8
    Poly8ExpPdf::Poly8ExpPdf(RooRealVar &x, const std::string& l)
    {
        a0 = new RooRealVar(Form("a0%s", l.c_str()), Form("a0%s", l.c_str()), 0.0);
        a1 = new RooRealVar(Form("a1%s", l.c_str()), Form("a1%s", l.c_str()), 0.0);
        a2 = new RooRealVar(Form("a2%s", l.c_str()), Form("a2%s", l.c_str()), 0.0);
        a3 = new RooRealVar(Form("a3%s", l.c_str()), Form("a3%s", l.c_str()), 0.0);
        a4 = new RooRealVar(Form("a4%s", l.c_str()), Form("a4%s", l.c_str()), 0.0);
        a5 = new RooRealVar(Form("a5%s", l.c_str()), Form("a5%s", l.c_str()), 0.0);
        a6 = new RooRealVar(Form("a6%s", l.c_str()), Form("a6%s", l.c_str()), 0.0);
        a7 = new RooRealVar(Form("a7%s", l.c_str()), Form("a7%s", l.c_str()), 0.0);
        a8 = new RooRealVar(Form("a8%s", l.c_str()), Form("a8%s", l.c_str()), 0.0);
        t  = new RooRealVar(Form("t%s" , l.c_str()), Form("t%s" , l.c_str()), -1e-6, -10.0, 0.00);

        // (a0 + a1*x + a2*x^2 + a3*x^3 + a4*x^4) * exp{-t}
        string title = Form("exp%s", l.c_str()); 
        exp = new RooExponential(title.c_str(), title.c_str(), x, *t);

        title = Form("poly%s", l.c_str());
        poly = new RooPolynomial(title.c_str(), title.c_str(), x, RooArgList(*a0, *a1, *a2, *a3, *a4, *a5, *a6, *a7, *a8));

        title = Form("background%s", l.c_str());
        model = RooAbsPdfPtr(new RooProdPdf(title.c_str(), title.c_str(), RooArgList(*poly, *exp)));
    }

    // linear 
    // ----------------------------------------------------------------- //

    struct LinearPdf : public PdfBase
    {
        LinearPdf(RooRealVar &x, const std::string& label);
        RooRealVar *a0;
        RooRealVar *a1;
    };

    LinearPdf::LinearPdf(RooRealVar &x, const std::string& l)
    {
        a0 = new RooRealVar(Form("a0%s", l.c_str()), Form("a0%s", l.c_str()),   0.0);
        a1 = new RooRealVar(Form("a1%s", l.c_str()), Form("a1%s", l.c_str()),   0.0);

        // (1 + a1*m + a2*m^2) * exp{-t}
        string title = Form("background%s", l.c_str());
        model = RooAbsPdfPtr(new RooPolynomial(title.c_str(), title.c_str(), x, RooArgList(*a0, *a1)));
    }

    // 3rd order polynomial 
    // ----------------------------------------------------------------- //

    struct Poly3Pdf : public PdfBase
    {
        Poly3Pdf(RooRealVar &x, const std::string& label);
        RooRealVar *a0;
        RooRealVar *a1;
        RooRealVar *a2;
        RooRealVar *a3;
    };

    Poly3Pdf::Poly3Pdf(RooRealVar &x, const std::string& l)
    {
        a0 = new RooRealVar(Form("a0%s", l.c_str()), Form("a0%s", l.c_str()),   0.0);
        a1 = new RooRealVar(Form("a1%s", l.c_str()), Form("a1%s", l.c_str()),   0.0);
        a2 = new RooRealVar(Form("a2%s", l.c_str()), Form("a2%s", l.c_str()),   0.0);
        a3 = new RooRealVar(Form("a3%s", l.c_str()), Form("a3%s", l.c_str()),   0.0);

        // (1 + a1*m + a2*m^2) * exp{-t}
        string title = Form("background%s", l.c_str());
        model = RooAbsPdfPtr(new RooPolynomial(title.c_str(), title.c_str(), x, RooArgList(*a0, *a1, *a2, *a3)));
    }

    // 6th order polynomial 
    // ----------------------------------------------------------------- //

    struct Poly6Pdf : public PdfBase
    {
        Poly6Pdf(RooRealVar &x, const std::string& label);
        RooRealVar *a0;
        RooRealVar *a1;
        RooRealVar *a2;
        RooRealVar *a3;
        RooRealVar *a4;
        RooRealVar *a5;
        RooRealVar *a6;
    };

    Poly6Pdf::Poly6Pdf(RooRealVar &x, const std::string& l)
    {
        a0 = new RooRealVar(Form("a0%s", l.c_str()), Form("a0%s", l.c_str()), 0.0);
        a1 = new RooRealVar(Form("a1%s", l.c_str()), Form("a1%s", l.c_str()), 0.0);
        a2 = new RooRealVar(Form("a2%s", l.c_str()), Form("a2%s", l.c_str()), 0.0);
        a3 = new RooRealVar(Form("a3%s", l.c_str()), Form("a3%s", l.c_str()), 0.0);
        a4 = new RooRealVar(Form("a4%s", l.c_str()), Form("a4%s", l.c_str()), 0.0);
        a5 = new RooRealVar(Form("a5%s", l.c_str()), Form("a5%s", l.c_str()), 0.0);
        a6 = new RooRealVar(Form("a6%s", l.c_str()), Form("a6%s", l.c_str()), 0.0);

        // Sum(an*m^n), n = 0, 6
        string title = Form("background%s", l.c_str());
        model = RooAbsPdfPtr(new RooPolynomial(title.c_str(), title.c_str(), x, RooArgList(*a0, *a1, *a2, *a3, *a4, *a5, *a6)));
    }

    // 8th order polynomial 
    // ----------------------------------------------------------------- //

    struct Poly8Pdf : public PdfBase
    {
        Poly8Pdf(RooRealVar &x, const std::string& label);
        RooRealVar *a0;
        RooRealVar *a1;
        RooRealVar *a2;
        RooRealVar *a3;
        RooRealVar *a4;
        RooRealVar *a5;
        RooRealVar *a6;
        RooRealVar *a7;
        RooRealVar *a8;
    };

    // Sum(an*m^n), n = 0, 10 
    Poly8Pdf::Poly8Pdf(RooRealVar &x, const std::string& l)
    {
        a0  = new RooRealVar(Form("a0%s" , l.c_str()), Form("a0%s" , l.c_str()), 0.0);
        a1  = new RooRealVar(Form("a1%s" , l.c_str()), Form("a1%s" , l.c_str()), 0.0);
        a2  = new RooRealVar(Form("a2%s" , l.c_str()), Form("a2%s" , l.c_str()), 0.0);
        a3  = new RooRealVar(Form("a3%s" , l.c_str()), Form("a3%s" , l.c_str()), 0.0);
        a4  = new RooRealVar(Form("a4%s" , l.c_str()), Form("a4%s" , l.c_str()), 0.0);
        a5  = new RooRealVar(Form("a5%s" , l.c_str()), Form("a5%s" , l.c_str()), 0.0);
        a6  = new RooRealVar(Form("a6%s" , l.c_str()), Form("a6%s" , l.c_str()), 0.0);
        a7  = new RooRealVar(Form("a7%s" , l.c_str()), Form("a7%s" , l.c_str()), 0.0);
        a8  = new RooRealVar(Form("a8%s" , l.c_str()), Form("a8%s" , l.c_str()), 0.0);

        string title = Form("background%s", l.c_str());
        model = RooAbsPdfPtr(new RooPolynomial(title.c_str(), title.c_str(), x, RooArgList(*a0, *a1, *a2, *a3, *a4, *a5, *a6, *a7, *a8)));
    }

    // wrapper to get the PDFs
    // ----------------------------------------------------------------- //

    PdfBase* CreateModelPdf(Model::value_type model, RooRealVar &x, const std::string& label = "", TH1F* const hist_template = NULL)
    {
        if (model == Model::MCTemplate && hist_template == NULL)
        {
            throw std::invalid_argument("[tp::CreateModelPdf] Error: template histogram is NULL!");
        }

        switch (model)
        {
            case Model::BreitWignerCB: return new BreitWignerCBPdf(x, label);                     break; 
            case Model::MCTemplate:    return new MCTemplateConvGausPdf(x, hist_template, label); break; 
            case Model::Exponential:   return new ExponentialPdf(x, label);                       break; 
            case Model::ErfExp:        return new ErfExpPdf(x, label);                            break; 
            case Model::QuadraticExp:  return new QuadraticExpPdf(x, label);                      break; 
            case Model::Chebychev:     return new ChebychevPdf(x, label);                         break; 
            case Model::ChebyExp:      return new ChebyExpPdf(x, label);                          break; 
            case Model::Linear:        return new LinearPdf(x, label);                            break; 
            case Model::Poly3:         return new Poly3Pdf(x, label);                             break; 
            case Model::Poly6:         return new Poly6Pdf(x, label);                             break; 
            case Model::Poly8:         return new Poly8Pdf(x, label);                             break; 
            case Model::Poly4Exp:      return new Poly4ExpPdf(x, label);                          break; 
            case Model::Poly8Exp:      return new Poly8ExpPdf(x, label);                          break; 
            default:
                throw std::invalid_argument("[tp::CreateModelPdf] Error: model not supported");
        }

        // return NULL pointer (should never get here)
        return new PdfBase;
    }

    // simple class to hold the results
    // ----------------------------------------------------------------- //

    // construct
    Result::Result(const float e, const float de, const float n, const float dn, const float d, const float dd)
        : cpass(new TCanvas("cpass", "cpass", 800, 600))
        , cfail(new TCanvas("cfail", "cfail", 800, 600))
    {
        eff.value = e;
        eff.error = de;
        num.value = n;
        num.error = dn;
        den.value = d;
        den.error = dd;
    }

    Result::Result()
        : cpass(new TCanvas("cpass", "cpass", 800, 600))
        , cfail(new TCanvas("cfail", "cfail", 800, 600))
    {
        eff.value = -999999.0;
        eff.error = -999999.0;
        num.value = -999999.0;
        num.error = -999999.0;
        den.value = -999999.0;
        den.error = -999999.0;
    }

    std::string Result::eff_str() const
    {
        return rt::pm(eff.value, eff.value, "1.3");
    }

    std::string Result::num_str() const
    {
        return rt::pm(num.value, num.value, "1.3");
    }

    std::string Result::den_str() const
    {
        return rt::pm(den.value, den.value, "1.3");
    }

    // helper function to create a tex box
    TPaveText* CreateTextBox(double x1, double y1, double x2, double y2, const std::string& text, const Color_t color = kBlack)
    {
        TPaveText *text_box = new TPaveText(x1,y1,x2,y2,"NDC");
        text_box->SetTextColor(color);
        text_box->SetFillStyle(0);
        text_box->SetBorderSize(0);
        text_box->SetTextAlign(12);
        text_box->AddText(text.c_str());
        return text_box;
    }

    // Peform the fit
    Result PerformSimultaneousFit
    (
        const Model::value_type sig_pass_model, 
        const Model::value_type sig_fail_model, 
        const Model::value_type bkg_pass_model, 
        const Model::value_type bkg_fail_model, 
        const TH1* const h_pass, 
        const TH1* const h_fail,
        const std::string pt_label, 
        const std::string eta_label, 
        const float mlow,
        const float mhigh,
        TH1F* const h_pass_template,
        TH1F* const h_fail_template
    )
    {
        // test template hist's existence
        if (sig_pass_model == Model::MCTemplate && h_pass_template == NULL)
        {
            throw std::invalid_argument("[tp::PerformSumultaneousFit] Error: pass template histogram is NULL!");
        }
        if (sig_fail_model == Model::MCTemplate && h_fail_template == NULL)
        {
            throw std::invalid_argument("[tp::PerformSumultaneousFit] Error: fail template histogram is NULL!");
        }

        // independent mass var
        RooRealVar mass("mass", "mass", mlow, mhigh, "GeV");

        // Define categories
        RooCategory sample("sample","");
        sample.defineType("pass",1);
        sample.defineType("pail",2);

        // signal model (need ptr for polymorphism to work -- references for convenience)
        PdfBase* spass_model_ptr = CreateModelPdf(sig_pass_model, mass, "_pass", h_pass_template);
        PdfBase* sfail_model_ptr = CreateModelPdf(sig_fail_model, mass, "_fail", h_fail_template);
        RooAbsPdf& spass_model   = *(spass_model_ptr->model);
        RooAbsPdf& sfail_model   = *(sfail_model_ptr->model);

        // background model (need ptr for polymorphism to work -- references for convenience)
        PdfBase* bpass_model_ptr = CreateModelPdf(bkg_pass_model, mass, "_pass");
        PdfBase* bfail_model_ptr = CreateModelPdf(bkg_fail_model, mass, "_fail");
        RooAbsPdf& bpass_model   = *(bpass_model_ptr->model);
        RooAbsPdf& bfail_model   = *(bfail_model_ptr->model);

        // count maximums
        double nsig_max      = h_pass->Integral() + h_fail->Integral();
        double nbkg_fail_max = h_fail->Integral();
        double nbkg_pass_max = h_pass->Integral();

        RooRealVar eff("eff", "Efficiency", 0.8 ,0 ,1.0);
        RooRealVar nsig("nsig", "Signal Yield", 0.80*nsig_max, 0, nsig_max);
        RooRealVar nbkg_pass("nbkg_pass","Background count in PASS sample", 50, 0, nbkg_pass_max);
        RooRealVar nbkg_fail("nbkg_fail","Background count in FAIL sample", 0.1*nbkg_fail_max, 0.01, nbkg_fail_max);
        RooFormulaVar nsig_pass("nsig_pass" ,"eff*nsig"      , RooArgList(eff, nsig));
        RooFormulaVar nsig_fail("nsig_fail" ,"(1.0-eff)*nsig", RooArgList(eff, nsig));
        RooFormulaVar ntot_pass("ntot_pass" ,"nsig_pass+nbkg_pass", RooArgList(nsig_pass, nbkg_pass));
        RooFormulaVar ntot_fail("ntot_fail" ,"nsig_fail+nbkg_fail", RooArgList(nsig_fail, nbkg_fail));

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

        // to the fit
        RooFitResult *roo_fit_result = total_pdf.fitTo(data_comb, RooFit::Extended(), RooFit::Strategy(1), RooFit::Save());
        //mass.setRange("signalRange", 81, 101);

        // results of eff
        Result simple_result
        (
            eff.getVal(), 
            max(eff.getErrorHi(), eff.getErrorLo()),
            nsig_pass.getVal(), 
            nsig_pass.getPropagatedError(*roo_fit_result),
            ntot_pass.getVal(), 
            ntot_pass.getPropagatedError(*roo_fit_result)
        );
  
        // passing plot
        simple_result.cpass->cd(); 
        RooPlot *mframe_pass = mass.frame(RooFit::Bins(static_cast<int>(fabs(mhigh-mlow)/tp::MassBinWidth)));
        data_pass.plotOn(mframe_pass, RooFit::MarkerStyle(kFullCircle), RooFit::MarkerSize(0.8), RooFit::DrawOption("ZP"));
        model_pass.plotOn(mframe_pass);
        model_pass.plotOn(mframe_pass,RooFit::Components("ebkg_pass"), RooFit::LineStyle(kDashed), RooFit::LineColor(kRed));
        mframe_pass->SetTitle("Passing Probes");
        mframe_pass->Draw();
        TPaveText *pt_box        = CreateTextBox(0.15, 0.80, 0.41, 0.85, pt_label ); pt_box->Draw();
        TPaveText *eta_box       = CreateTextBox(0.15, 0.75, 0.33, 0.80, eta_label); eta_box->Draw();
        TPaveText *npass_box     = CreateTextBox(0.15, 0.70, 0.33, 0.75, Form("%1.0f Events", nbkg_pass_max)); npass_box->Draw();
        TPaveText *eff_box       = CreateTextBox(0.65, 0.80, 0.85, 0.84, "#varepsilon = " + simple_result.eff_str()); eff_box->Draw();
        TPaveText *nsig_pass_box = CreateTextBox(0.65, 0.75, 0.85, 0.79, Form("N_{sig} = %1.0f #pm %1.0f", nsig_pass.getVal(), nsig_pass.getPropagatedError(*roo_fit_result))); nsig_pass_box->Draw();
        TPaveText *nbkg_pass_box = CreateTextBox(0.65, 0.70, 0.85, 0.74, Form("N_{bkg} = %1.0f #pm %1.0f", nbkg_pass.getVal(), nbkg_pass.getPropagatedError(*roo_fit_result))); nbkg_pass_box->Draw();
        TPaveText *ntot_pass_box = CreateTextBox(0.65, 0.65, 0.85, 0.69, Form("N_{tot} = %1.0f #pm %1.0f", ntot_pass.getVal(), ntot_pass.getPropagatedError(*roo_fit_result))); ntot_pass_box->Draw();

        // failing plot
        simple_result.cfail->cd(); 
        RooPlot *mframe_fail = mass.frame(RooFit::Bins(static_cast<int>(fabs(mhigh-mlow)/tp::MassBinWidth)));
        data_fail.plotOn(mframe_fail, RooFit::MarkerStyle(kFullCircle), RooFit::MarkerSize(0.8), RooFit::DrawOption("ZP"));
        model_fail.plotOn(mframe_fail);
        model_fail.plotOn(mframe_fail,RooFit::Components("ebkg_fail"), RooFit::LineStyle(kDashed), RooFit::LineColor(kRed));
        mframe_fail->SetTitle("Failing Probes");
        mframe_fail->Draw();
        pt_box->Draw();
        eta_box->Draw();
        TPaveText *nfail_box     = CreateTextBox(0.15, 0.70, 0.33, 0.75, Form("%1.0f Events", nbkg_fail_max)); nfail_box->Draw();
        eff_box->Draw();
        TPaveText *nsig_fail_box = CreateTextBox(0.65, 0.75, 0.85, 0.79, Form("N_{sig} = %1.0f #pm %1.0f", nsig_fail.getVal(), nsig_fail.getPropagatedError(*roo_fit_result))); nsig_fail_box->Draw();
        TPaveText *nbkg_fail_box = CreateTextBox(0.65, 0.70, 0.85, 0.74, Form("N_{bkg} = %1.0f #pm %1.0f", nbkg_fail.getVal(), nbkg_fail.getPropagatedError(*roo_fit_result))); nbkg_fail_box->Draw();
        TPaveText *ntot_fail_box = CreateTextBox(0.65, 0.65, 0.85, 0.69, Form("N_{tot} = %1.0f #pm %1.0f", ntot_fail.getVal(), ntot_fail.getPropagatedError(*roo_fit_result))); ntot_fail_box->Draw();

        // done 
        return simple_result;
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
        double num_pass      = rt::IntegralAndError(h_pass).first;
        double num_pass_err  = rt::IntegralAndError(h_pass).second;
        double num_fail      = rt::IntegralAndError(h_fail).first;
        double num_fail_err  = rt::IntegralAndError(h_fail).second;
        double num_total     = num_pass + num_fail;
        double num_total_err = sqrt(num_pass_err*num_pass_err + num_fail_err*num_fail_err);
        double eff           = num_pass/num_total;
        double eff_err       = sqrt(eff * (1.0 - eff)/num_total); // binomial
        Result simple_result(eff, eff_err, num_pass, num_pass_err, num_total, num_total_err); // taking symmetric for now

        // independent mass var
        RooRealVar mass("mass", "mass", mlow, mhigh, "GeV");
        RooDataHist hist_pass("data_pass", "data_pass", RooArgSet(mass), h_pass);
        RooDataHist hist_fail("data_fail", "data_fail", RooArgSet(mass), h_fail);

        // passing plot
        simple_result.cpass->cd(); 
        RooPlot *mframe_pass = mass.frame(RooFit::Bins(static_cast<int>(fabs(mhigh-mlow)/tp::MassBinWidth)));
        hist_pass.plotOn(mframe_pass);
        mframe_pass->SetTitle("MC Passing Probes");
        mframe_pass->Draw();
        TPaveText *pt_box    = CreateTextBox(0.15, 0.80, 0.41, 0.85, pt_label ); pt_box->Draw();
        TPaveText *eta_box   = CreateTextBox(0.15, 0.75, 0.33, 0.80, eta_label); eta_box->Draw();
        TPaveText *npass_box = CreateTextBox(0.15, 0.70, 0.33, 0.75, Form("%1.0f Events", h_pass->Integral())); npass_box->Draw();
        TPaveText *eff_box   = CreateTextBox(0.65, 0.80, 0.85, 0.84, "#varepsilon = " + simple_result.eff_str()); eff_box->Draw();
        TPaveText *num_box   = CreateTextBox(0.65, 0.75, 0.85, 0.79, Form("N_{pass } = %1.0f", simple_result.num.value)); num_box->Draw();
        TPaveText *den_box   = CreateTextBox(0.65, 0.70, 0.85, 0.74, Form("N_{total} = %1.0f", simple_result.den.value)); den_box->Draw();

        // failing plot
        simple_result.cfail->cd(); 
        RooPlot *mframe_fail = mass.frame(RooFit::Bins(static_cast<int>(fabs(mhigh-mlow)/tp::MassBinWidth)));
        hist_fail.plotOn(mframe_fail);
        mframe_fail->SetTitle("MC Failing Probes");
        mframe_fail->Draw();
        pt_box->Draw();
        eta_box->Draw();
        TPaveText *nfail_box = CreateTextBox(0.15, 0.70, 0.33, 0.75, Form("%1.0f Events", h_fail->Integral())); nfail_box->Draw();
        eff_box->Draw();
        num_box->Draw();
        den_box->Draw();

        return simple_result;
    }

} // namespace tp
