#ifndef RT_FILLHIST_H
#define RT_FILLHIST_H

// ROOT includes
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"

namespace rt
{
    // fill the histogram with overflow bins
    void Fill(TH1& hist, double x, double w = 1.0);
    void Fill(TH1* hist, double x, double w = 1.0);

    // fill the 2D histogram with overflow bins
    void Fill2D(TH2& hist, double x, double y, double w = 1.0);
    void Fill2D(TH2* hist, double x, double y, double w = 1.0);
    void Fill2D(TH1* hist, double x, double y, double w = 1.0);

    // fill the 3D histogram with overflow bins
    void Fill3D(TH3& hist, double x, double y, double z, double w = 1.0);
    void Fill3D(TH3* hist, double x, double y, double z, double w = 1.0);
    void Fill3D(TH1* hist, double x, double y, double z, double w = 1.0);

} // namespace rt

#endif // RT_FILLHIST_H
