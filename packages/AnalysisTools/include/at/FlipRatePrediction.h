#ifndef AT_FLIPRATEPREDICTION_H
#define AT_FLIPRATEPREDICTION_H

#include "TH2.h"
#include "at/DileptonHypType.h"
#include "PredSummary.h"
#include <string>
#include <tr1/memory>

namespace at
{
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

            PredSummary GetFlipPrediction(float scale_factor = 1.0) const;

        private:
            // members: 
            std::tr1::shared_ptr<TH2> h_flip_rate;
            float m_scale;
            PredSummary flip;

            // methods: 
            Pred SingleFlipPrediction(const TH2F*);
            Pred DoubleFlipPrediction(const TH2F*);
    };

    // non members
    void FillDoubleFlipHist
    (
        TH2F& hist, 
        const TH2F& h_flip,
        float pt1, 
        float eta1, 
        float pt2, 
        float eta2, 
        float weight
    );

} // namespace at

#endif // AT_FLIPRATEPREDICTION_H
