#ifndef TP_PERFORM_FITS_H
#define TP_PERFORM_FITS_H

#include "TCanvas.h"
#include "TH1.h"
#include <string>

namespace tp
{
    // models available
    struct Model
    {
        enum value_type
        {
            BreitWignerCB,
            MCTemplate,
            Exponential,
            ErfExp,
            ErfPolyExp,
            QuadraticExp,
            Poly3,
            Poly6,
            Poly4Exp,
            Chebychev,
            ChebyExp,
            static_size
        };
    };

    // a simple struct to hold the results
    struct Result
    {
        Result();
        Result(float, float, float);

        float eff;
        float eff_err_high;
        float eff_err_low;
        TCanvas* cpass;
        TCanvas* cfail;

        std::string str() const;
    };

    // Get the model
    
    // Peform simultaneous fit
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
        const float mlow = 60.0,
        const float mhigh = 120.0,
        TH1F* const h_pass_template = NULL,
        TH1F* const h_fail_template = NULL
    );

    // Peform  
    Result PerformSimpleCount
    (
        TH1* const h_pass, 
        TH1* const h_fail,
        const std::string pt_label, 
        const std::string eta_label, 
        const float mlow = 60.0,
        const float mhigh = 120.0
    );

} // namespace tp

#endif // TP_PERFORM_FITS_H
