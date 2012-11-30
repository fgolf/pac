#include "rt/FillHist.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;

namespace rt
{
    // fill the hist with overflow bins
    void Fill(TH1& hist, double x, double w)
    {   
        x = min(hist.GetXaxis()->GetBinCenter(hist.GetXaxis()->GetLast()) , x);
        x = max(hist.GetXaxis()->GetBinCenter(hist.GetXaxis()->GetFirst()), x);
        hist.Fill(x, w);
    }   

    void Fill(TH1* hist_ptr, double x, double w)
    {   
        if (!hist_ptr)
        {
            cerr << "Warning: rt::Fill() -- hist pointer is NULL! Doing nothing." << endl;
            return;
        }
        Fill(*hist_ptr, x, w);
    }   


    // fill the 2D hist with overflow bins
    void Fill2D(TH2& hist, double x, double y, double w)
    {   
        x = min(hist.GetXaxis()->GetBinCenter(hist.GetXaxis()->GetLast()) , x);
        x = max(hist.GetXaxis()->GetBinCenter(hist.GetXaxis()->GetFirst()), x);
        y = min(hist.GetYaxis()->GetBinCenter(hist.GetYaxis()->GetLast()) , y);
        y = max(hist.GetYaxis()->GetBinCenter(hist.GetYaxis()->GetFirst()), y);
        hist.Fill(x, y, w);
    }

    void Fill2D(TH2* hist_ptr, double x, double y, double w)
    {   
        if (!hist_ptr)
        {
            cerr << "Warning: rt::Fill2D() -- hist pointer is NULL! Doing nothing." << endl;
            return;
        }
        Fill2D(*hist_ptr, x, y, w);
    }

    void Fill2D(TH1* hist_ptr, double x, double y, double w)
    {   
        if (!hist_ptr)
        {
            cerr << "Warning: rt::Fill2D() -- hist pointer is NULL! Doing nothing." << endl;
            return;
        }
        if (TH2* h2d = dynamic_cast<TH2*>(hist_ptr))
        {
            Fill2D(h2d, x, y, w);
        }
        else
        {
            throw runtime_error("ERROR: rt::Fill2D() -- hist pointer is not a TH2*!");
        }
        return;
    }

    // fill the 3D hist with overflow bins
    void Fill3D(TH3& hist, double x, double y, double z, double w)
    {   
        x = min(hist.GetXaxis()->GetBinCenter(hist.GetXaxis()->GetLast()) , x);
        x = max(hist.GetXaxis()->GetBinCenter(hist.GetXaxis()->GetFirst()), x);
        y = min(hist.GetYaxis()->GetBinCenter(hist.GetYaxis()->GetLast()) , y);
        y = max(hist.GetYaxis()->GetBinCenter(hist.GetYaxis()->GetFirst()), y);
        z = min(hist.GetZaxis()->GetBinCenter(hist.GetZaxis()->GetLast()) , z);
        z = max(hist.GetZaxis()->GetBinCenter(hist.GetZaxis()->GetFirst()), z);
        Fill3D(hist, x, y, z, w);
    }

    void Fill3D(TH3* hist_ptr, double x, double y, double z, double w)
    {   
        if (!hist_ptr)
        {
            cerr << "Warning: rt::Fill3D() -- hist pointer is NULL! Doing nothing." << endl;
            return;
        }
        Fill3D(*hist_ptr, x, y, z, w);
    }

    // fill the 3D hist with overflow bins
    void Fill3D(TH1* hist_ptr, double x, double y, double z, double w)
    {   
        if (!hist_ptr)
        {
            cerr << "Warning: rt::Fill3D() -- hist pointer is NULL! Doing nothing." << endl;
            return;
        }
        if (TH3* h3d = dynamic_cast<TH3*>(hist_ptr))
        {
            Fill3D(h3d, x, y, z, w);
        }
        else
        {
            throw runtime_error("ERROR: rt::Fill3D() -- hist pointer is not a TH3*!");
        }
        return;
    }

} // namespace rt
