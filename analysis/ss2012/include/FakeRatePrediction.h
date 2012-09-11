#ifndef FAKERATEPREDICTION_H
#define FAKERATEPREDICTION_H

#include "TH2.h"
#include "at/DileptonHypType.h"
#include "PredSummary.h"
#include <string>
#include <tr1/memory>

// Stuct to determine which type of fake rate
struct FakeRateType 
{ 
    enum value_type
    {
        E, 
        MU, 
        EE, 
        EMU, 
        MUMU, 
        static_size,
    };
};

// Fake Rate Predction class to compute the prediction
class FakeRatePrediction
{
public:
    // construct:
    FakeRatePrediction(TH2* mufr, TH2* elfr, float scale = 1.0);

    // methods:
    void ComputeAllFakePredictions
    (
        TH2F* h_sf_ee, 
        TH2F* h_sf_mm, 
        TH2F* h_sf_em, 
        TH2F* h_sf_me, 
        TH2F* h_df_ee, 
        TH2F* h_df_mm, 
        TH2F* h_df_em
    );

    PredSummary GetSingleFakePredictionRaw() const;
    PredSummary GetSingleFakePrediction() const;
    PredSummary GetDoubleFakePrediction() const;
    PredSummary GetFakePrediction() const;

private:
    // members: 
    std::tr1::shared_ptr<TH2> h_mufr;
    std::tr1::shared_ptr<TH2> h_elfr;
    float m_scale;
    float m_ele_max;
    float m_mu_max;
    PredSummary sf_raw;
    PredSummary sf;
    PredSummary df;
    PredSummary all;

    // methods: 
    Pred SingleFakePrediction(const TH2F*, FakeRateType::value_type, at::DileptonHypType::value_type); 
    Pred DoubleFakePrediction(const TH2F*, FakeRateType::value_type);
};

#endif
