#ifndef FLIPRATEPREDICTION_H
#define FLIPRATEPREDICTION_H

#include "TH2.h"
#include "at/DileptonHypType.h"
#include "PredSummary.h"
#include <string>
#include <tr1/memory>

// Stuct to determine which type of fake rate
struct FlipRateType 
{ 
    enum value_type
    {
        EE, 
        EMU, 
        static_size,
    };
};

// Flip Rate Predction class to compute the prediction
class FlipRatePrediction
{
public:
    // construct:
    FlipRatePrediction(TH2* flip_rate, float scale = 1.0);

    // methods:
    void ComputeAllFlipPredictions
    (
        TH2F* h_ee, 
        TH2F* h_em 
    );

    PredSummary GetFlipPrediction() const;

private:
    // members: 
    std::tr1::shared_ptr<TH2> h_flip_rate;
    float m_scale;
    PredSummary flip;

    // methods: 
    Pred SingleFlipPrediction(const TH2F*);
    Pred DoubleFlipPrediction(const TH2F*);
};

#endif
