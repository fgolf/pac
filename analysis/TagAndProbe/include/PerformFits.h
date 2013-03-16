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
            Linear,
            Poly3,
            Poly6,
            Poly8,
            Poly4Exp,
            Poly8Exp,
            Chebychev,
            ChebyExp,
            static_size
        };
    };

    // cheesy struct to hold value/error 
    struct value_t
    {
        float value;
        float error;
    };

    // a simple struct to hold the results
    struct Result
    {
        Result();
        Result(const float, const float, const float, const float, const float, const float);

        value_t eff;
        value_t num;
        value_t den;
        TCanvas* cpass;
        TCanvas* cfail;

        std::string eff_str() const;
        std::string num_str() const;
        std::string den_str() const;
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
