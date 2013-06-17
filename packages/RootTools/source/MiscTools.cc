#include "rt/MiscTools.h" 
#include "rt/TH1Container.h" 
#include "rt/TH1Overlay.h" 
#include "rt/is_equal.h" 

// c++ includes
#include <iostream>
#include <stdexcept>
#include <math.h>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include "Math/GenVector/VectorUtil.h"
//#include <stdio.h>

// Root includes
#include "TSystem.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TGaxis.h"
#include "TPaveStats.h"
#include "TMath.h"
#include "TFileMerger.h"
#include "TBranch.h"
#include "TBranchElement.h"
#include "TDirectory.h"
#include "TTree.h"

// boost includes
#define BOOST_FILESYSTEM_NO_DEPRECATED //  we don't want to use any deprecated features
#include "boost/filesystem.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/regex.hpp" 
#include "boost/lexical_cast.hpp"
#include "boost/algorithm/string.hpp"

using namespace std;
using namespace boost;

namespace rt
{
    // function definitions
    // ---------------------------------------------------------------------------------------- //

    // get a root file (throws if file not found)
    TFilePtr OpenRootFile(const string& file_name, const string& option)
    {
        TFilePtr file(TFile::Open(file_name.c_str(), option.c_str()));
        if (!file || file->IsZombie()) 
            throw runtime_error(string("rt::OpenRootFile() Error: '") + file_name + "' not found or empty.  Aborting!");
        return file;
    }

    // set statbox position
    void SetStatBoxPosition(TH1* hist_ptr, float x1, float y1,  float x2, float y2)
    {
        if (!hist_ptr)
        {
            std::cerr << "Warning: rt::SetStatBosPosition() -- hist pointer is NULL! Doing nothing." << endl;
            return;
        }

        hist_ptr->SetStats(true);
        hist_ptr->Draw(); // make sure the stat box exists
        gPad->Update();
        if (TPaveStats *statbox = dynamic_cast<TPaveStats*>(hist_ptr->FindObject("stats")))
        {
            statbox->SetLineColor(hist_ptr->GetLineColor());
            statbox->SetLineWidth(hist_ptr->GetLineWidth());
            statbox->SetLineStyle(hist_ptr->GetLineStyle());

            statbox->SetX1NDC(x1);
            statbox->SetY1NDC(y1);
            statbox->SetX2NDC(x2);
            statbox->SetY2NDC(y2);
        }
    }

    // scale the histogram to scale 
    void Scale(TH1* hist, double scale)
    {
        float integral = static_cast<float>(hist->Integral());
        if (integral > 0)
        {
            hist->Scale(scale/integral);
        }
    }

    // calculate the integral 1D hist
    double Integral(TH1* hist_ptr, const std::string& option)
    {
        if (!hist_ptr)
        {
            throw std::runtime_error("ERROR: rt::Integral() -- hist pointer is NULL!");
        }
        int max_bin   = hist_ptr->GetNbinsX()+1;
        int min_bin   = 0;
        return hist_ptr->Integral(min_bin, max_bin, option.c_str());
    }

    // calculate the integral 1D over a range
    double Integral(TH1* hist_ptr, float low, float high, const std::string& option)
    {
        if (!hist_ptr)
        {
            throw std::runtime_error("ERROR: rt::Integral() -- hist pointer is NULL!");
        }
        if (low > high)
        {
            throw std::runtime_error("ERROR: rt::Integral() -- low must > high!");
        }
        int left_bin  = hist_ptr->FindBin(low);
        int right_bin = hist_ptr->FindBin(high);
        if (is_equal(static_cast<double>(high), hist_ptr->GetXaxis()->GetBinLowEdge(right_bin)))
        {
            right_bin--;
        }
        return hist_ptr->Integral(left_bin, right_bin, option.c_str());
    }

    // calculate the integral 2D hist
    double Integral(TH2* hist_ptr, const std::string& option)
    {
        if (!hist_ptr)
        {
            throw std::runtime_error("ERROR: rt::Integral2D() -- hist pointer is NULL!");
        }
        int xmax_bin   = hist_ptr->GetNbinsX()+1;
        int xmin_bin   = 0;
        int ymax_bin   = hist_ptr->GetNbinsY()+1;
        int ymin_bin   = 0;
        return hist_ptr->Integral(xmin_bin, xmax_bin, ymin_bin, ymax_bin, option.c_str());
    }

    // calculate the integral 2D over a range
    double Integral(TH2* hist_ptr, float xlow, float xhigh, float ylow, float yhigh, const std::string& option)
    {
        if (!hist_ptr)
        {
            throw std::runtime_error("ERROR: rt::Integral2D() -- hist pointer is NULL!");
        }
        if ((xlow > xhigh) || (ylow > yhigh))
        {
            throw std::runtime_error("ERROR: rt::Integral2D() -- low must > high!");
        }
        int left_bin   = hist_ptr->GetXaxis()->FindBin(xlow);
        int right_bin  = hist_ptr->GetXaxis()->FindBin(xhigh);
        int bottom_bin = hist_ptr->GetYaxis()->FindBin(ylow);
        int top_bin    = hist_ptr->GetYaxis()->FindBin(yhigh);
        if (is_equal(static_cast<double>(xhigh), hist_ptr->GetXaxis()->GetBinLowEdge(right_bin)))
        {
            right_bin--;
        }
        if (is_equal(static_cast<double>(yhigh), hist_ptr->GetYaxis()->GetBinLowEdge(top_bin)))
        {
            top_bin--;
        }
        return hist_ptr->Integral(left_bin, right_bin, bottom_bin, top_bin, option.c_str());
    }

    // inflate the bin error by percentage of the bin value (used for systematic uncertainties)
    void SetSystematicUncertainty(TH1* h, float sys_unc)
    {
        for (int i = 0; i != h->GetNbinsX()+1; i++)
        {
            float v = h->GetBinContent(i);
            float e = h->GetBinError(i);
            float error = sqrt(e*e + sys_unc*sys_unc*v*v);
            h->SetBinError(i, error);
        }
        return;
    }

    // find the bin content  
    double GetBinContent1D(TH1* hist_ptr, const float x)
    {
        if (!hist_ptr)
        {
            throw std::runtime_error("ERROR: rt::GetBinContent1D() -- hist pointer is NULL!");
        }
        int bin = hist_ptr->GetXaxis()->FindBin(x);
        return hist_ptr->GetBinContent(bin);
    }

    //  find the bin content 
    double GetBinContent2D(TH2* hist_ptr, const float x, const float y)
    {
        if (!hist_ptr)
        {
            throw std::runtime_error("ERROR: rt::GetBinContent1D() -- hist pointer is NULL!");
        }
        int xbin = hist_ptr->GetXaxis()->FindBin(x);
        int ybin = hist_ptr->GetYaxis()->FindBin(y);
        return hist_ptr->GetBinContent(xbin, ybin);
    }

    // find the bin error 
    double GetBinError1D(TH1* hist_ptr, const float x)
    {
        if (!hist_ptr)
        {
            throw std::runtime_error("ERROR: rt::GetBinError1D() -- hist pointer is NULL!");
        }
        int bin = hist_ptr->GetXaxis()->FindBin(x);
        return hist_ptr->GetBinError(bin);
    }

    //  find the bin error
    double GetBinError2D(TH2* hist_ptr, const float x, const float y)
    {
        if (!hist_ptr)
        {
            throw std::runtime_error("ERROR: rt::GetBinError1D() -- hist pointer is NULL!");
        }
        int xbin = hist_ptr->GetXaxis()->FindBin(x);
        int ybin = hist_ptr->GetYaxis()->FindBin(y);
        return hist_ptr->GetBinError(xbin, ybin);
    }

    // set the bin content  
    void SetBinContent1D(TH1* hist_ptr, const float x, const float value)
    {
        if (!hist_ptr)
        {
            throw std::runtime_error("ERROR: rt::SetBinContent1D() -- hist pointer is NULL!");
        }
        int bin = hist_ptr->GetXaxis()->FindBin(x);
        hist_ptr->SetBinContent(bin, value);
    }

    // set the bin content  
    void SetBinContent1D(TH1* hist_ptr, const float x, const float value, const float error)
    {
        if (!hist_ptr)
        {
            throw std::runtime_error("ERROR: rt::SetBinContent1D() -- hist pointer is NULL!");
        }
        int bin = hist_ptr->GetXaxis()->FindBin(x);
        hist_ptr->SetBinContent(bin, value);
        hist_ptr->SetBinError(bin, error);
    }

    // set the bin content 
    void SetBinContent2D(TH1* hist_ptr, const float x, const float y, const float value)
    {
        if (!hist_ptr)
        {
            throw std::runtime_error("ERROR: rt::SetBinContent2D() -- hist pointer is NULL!");
        }
        if (TH2* h = dynamic_cast<TH2*>(hist_ptr))
        {
            int xbin = h->GetXaxis()->FindBin(x);
            int ybin = h->GetYaxis()->FindBin(y);
            h->SetBinContent(xbin, ybin, value);
        }
        else
        {
            throw std::runtime_error("ERROR: rt::SetBinContent2D() -- hist pointer is not 2D!");
        }
    }

    // set the bin content 
    void SetBinContent2D(TH1* hist_ptr, const float x, const float y, const float value, const float error)
    {
        if (!hist_ptr)
        {
            throw std::runtime_error("ERROR: rt::SetBinContent2D() -- hist pointer is NULL!");
        }
        if (TH2* h = dynamic_cast<TH2*>(hist_ptr))
        {
            int xbin = h->GetXaxis()->FindBin(x);
            int ybin = h->GetYaxis()->FindBin(y);
            h->SetBinContent(xbin, ybin, value);
            h->SetBinError(xbin, ybin, error);
        }
        else
        {
            throw std::runtime_error("ERROR: rt::SetBinContent2D() -- hist pointer is not 2D!");
        }
    }

    // set the bin content 
    void SetBinContent2D(TH2* hist_ptr, const float x, const float y, const float value)
    {
        if (!hist_ptr)
        {
            throw std::runtime_error("ERROR: rt::SetBinContent2D() -- hist pointer is NULL!");
        }
        int xbin = hist_ptr->GetXaxis()->FindBin(x);
        int ybin = hist_ptr->GetYaxis()->FindBin(y);
        hist_ptr->SetBinContent(xbin, ybin, value);
    }

    // set the bin content 
    void SetBinContent2D(TH2* hist_ptr, const float x, const float y, const float value, const float error)
    {
        if (!hist_ptr)
        {
            throw std::runtime_error("ERROR: rt::SetBinContent1D() -- hist pointer is NULL!");
        }
        int xbin = hist_ptr->GetXaxis()->FindBin(x);
        int ybin = hist_ptr->GetYaxis()->FindBin(y);
        hist_ptr->SetBinContent(xbin, ybin, value);
        hist_ptr->SetBinError(xbin, ybin, error);
    }

    // calculate the integral and error
    std::pair<double, double> IntegralAndError(TH1* hist_ptr, const std::string& option)
    {
        if (!hist_ptr)
        {
            throw std::runtime_error("ERROR: rt::IntegralAndError() -- hist pointer is NULL!");
        }
        int max_bin  = hist_ptr->GetNbinsX()+1;
        int min_bin  = 0;
        double error = 0;
        double integral = hist_ptr->IntegralAndError(min_bin, max_bin, error, option.c_str());
        //double integral = hist_ptr->Integral(min_bin, max_bin, option.c_str());
        //double error = (hist_ptr->GetEntries() > 0 ) ? sqrt(hist_ptr->GetEntries() * pow(integral/hist_ptr->GetEntries(), 2)) : 0.0;
        return std::make_pair(integral, error);
    }

    // calculate the integral and error over a range
    std::pair<double, double> IntegralAndError(TH1* hist_ptr, float low, float high, const std::string& option)
    {
        if (!hist_ptr)
        {
            throw std::runtime_error("ERROR: rt::IntegralAndError() -- hist pointer is NULL!");
        }
        if (low > high)
        {
            throw std::runtime_error("ERROR: rt::IntegralAndError() -- low must > high!");
        }
        int left_bin  = hist_ptr->FindBin(low);
        int right_bin = hist_ptr->FindBin(high);
        if (is_equal(static_cast<double>(high), hist_ptr->GetXaxis()->GetBinLowEdge(right_bin)))
        {
            right_bin--;
        }
        double error = 0;
        double integral = hist_ptr->IntegralAndError(left_bin, right_bin, error, option.c_str());
        //double integral = hist_ptr->Integral(left_bin, right_bin, option.c_str());
        //double error = (hist_ptr->GetEntries() > 0 ) ? sqrt(hist_ptr->GetEntries() * pow(integral/hist_ptr->GetEntries(), 2)) : 0.0;
        return std::make_pair(integral, error);
    }

    // calculate the integral and error
    std::pair<double, double> EntriesAndError(TH1* hist_ptr, const std::string& option)
    {
        if (!hist_ptr)
        {
            throw std::runtime_error("ERROR: rt::EntriesAndError() -- hist pointer is NULL!");
        }
        double entries = hist_ptr->GetEntries(); 
        double error   = sqrt(entries); 
        return std::make_pair(entries, error);
    }

    // calculate the percent of integral 
    double CalcPercentOfIntegral(TH1* hist_ptr, float low, float high, const std::string& option)
    {
        if (!hist_ptr)
        {
            throw std::runtime_error("ERROR: rt::CalcPercentOfIntegral() -- hist pointer is NULL!");
        }
        return Integral(hist_ptr, low, high, option.c_str())/Integral(hist_ptr, option.c_str());
    }

    // Add with error
    std::pair<double, double> AddWithError(const std::pair<double, double>& v1, const std::pair<double, double>& v2)
    {
        double result = v1.first + v2.first;
        double error  = sqrt(pow(v1.second, 2) + pow(v2.second, 2));
        return std::make_pair(result, error);
    }

    std::pair<float, float> AddWithError(const std::pair<float, float>& v1, const std::pair<float, float>& v2)
    {
        std::pair<double, double> double_v1(v1.first, v1.second);
        std::pair<double, double> double_v2(v2.first, v2.second);
        std::pair<double, double> result = AddWithError(double_v1, double_v2);
        return std::make_pair(static_cast<float>(result.first), static_cast<float>(result.second));
    }

    // Subtract with error
    std::pair<double, double> SubtractWithError(const std::pair<double, double>& v1, const std::pair<double, double>& v2)
    {
        double result = v1.first - v2.first;
        double error  = sqrt(pow(v1.second, 2) + pow(v2.second, 2));
        return std::make_pair(result, error);
    }

    std::pair<float, float> SubtractWithError(const std::pair<float, float>& v1, const std::pair<float, float>& v2)
    {
        std::pair<double, double> double_v1(v1.first, v1.second);
        std::pair<double, double> double_v2(v2.first, v2.second);
        std::pair<double, double> result = SubtractWithError(double_v1, double_v2);
        return std::make_pair(static_cast<float>(result.first), static_cast<float>(result.second));
    }

    // Multiply with error
    std::pair<double, double> MultiplyWithError(const std::pair<double, double>& v1, const std::pair<double, double>& v2)
    {
        double result = v1.first * v2.first;
        double error  = std::abs(result) * sqrt(pow(v1.second/v1.first, 2) + pow(v2.second/v2.first, 2));
        return std::make_pair(result, error);
    }

    std::pair<float, float> MultiplyWithError(const std::pair<float, float>& v1, const std::pair<float, float>& v2)
    {
        std::pair<double, double> double_v1(v1.first, v1.second);
        std::pair<double, double> double_v2(v2.first, v2.second);
        std::pair<double, double> result = MultiplyWithError(double_v1, double_v2);
        return std::make_pair(static_cast<float>(result.first), static_cast<float>(result.second));
    }

    // Divide with error
    std::pair<double, double> DivideWithError(const std::pair<double, double>& v1, const std::pair<double, double>& v2)
    {
        if (is_equal(v2.first, 0.0))
        {
            throw std::runtime_error("rt::DivideWithError Error: attempting to divide by zero!");
        }
        double result = v1.first / v2.first;
        double error  = std::abs(result) * sqrt(pow(v1.second/v1.first, 2) + pow(v2.second/v2.first, 2));
        return std::make_pair(result, error);
    }

    std::pair<float, float> DivideWithError(const std::pair<float, float>& v1, const std::pair<float, float>& v2)
    {
        std::pair<double, double> double_v1(v1.first, v1.second);
        std::pair<double, double> double_v2(v2.first, v2.second);
        std::pair<double, double> result = DivideWithError(double_v1, double_v2);
        return std::make_pair(static_cast<float>(result.first), static_cast<float>(result.second));
    }

    // create a CTable from a hist (1D and 2D only)                            
    CTable CreateTableFromHist                                                 
    (                                                                          
        TH1* hist,                                                             
        const std::string& title,                                              
        const std::string& xtitle,                                             
        const std::string& ytitle,                                             
        const std::string& xunit,                                              
        const std::string& yunit,                                              
        const std::string& precision,                                          
        const std::string& xprecision,                                         
        const std::string& yprecision,                                         
        const bool reverse_axis                                                
    )                                                                          
    {                                                                          
        using std::string;                                                     
                                                                               
        CTable table;                                                          
        if (not title.empty())                                                 
        {                                                                      
            table.useTitle();                                                  
            table.setTitle(title);                                             
        }                                                                      
                                                                               
        // NULL pointer --> throw exception                                    
        if (hist == NULL)                                                      
        {                                                                      
            throw std::invalid_argument("[CreateTableFromHist] Error: hist pointer is NULL"); 
        }                                                                      
                                                                               
        // 3D hist --> throw exception                                         
        if (dynamic_cast<TH3*>(hist))                                          
        {                                                                      
            throw std::invalid_argument("[CreateTableFromHist] Error: only supports TH2 or TH1"); 
        }                                                                      
                                                                               
        // 2D hist                                                             
        if (dynamic_cast<TH2*>(hist))                                          
        {                                                                      
            TAxis* const xaxis = (reverse_axis ? hist->GetYaxis() : hist->GetXaxis());
            TAxis* const yaxis = (reverse_axis ? hist->GetXaxis() : hist->GetYaxis());
                                                                               
            for (int xbin = 1; xbin != xaxis->GetNbins()+1; xbin++)            
            {                                                                  
                const int col = xbin-1;                                        
                const float xmin = xaxis->GetBinLowEdge(xbin);                 
                const float xmax = xaxis->GetBinUpEdge(xbin);                  
                                                                               
                // column label                                                
                string xlabel;                                                 
                if (not xtitle.empty())                                        
                {                                                              
                    if (not xunit.empty())                                     
                    {                                                          
                        string format = "%" + xprecision + "f " + xunit + " < \%s < %" + xprecision + "f " + xunit;
                        xlabel = Form(format.c_str(), xmin, xtitle.c_str(), xmax);
                    }                                                          
                    else                                                       
                    {                                                          
                        string format = "%" + xprecision + "f < \%s < %" + xprecision + "f";
                        xlabel = Form(format.c_str(), xmin, xtitle.c_str(), xmax);
                    }                                                          
                }                                                              
                else                                                           
                {                                                              
                    string format = "%" + xprecision + "f < \%s < %" + xprecision + "f";
                    xlabel = Form(format.c_str(), xmin, xaxis->GetTitle(), xmax);
                }                                                              
                table.setColLabel(xlabel, col);                                
                                                                               
                for (int ybin = 1; ybin != yaxis->GetNbins()+1; ybin++)        
                {                                                              
                    const int row = ybin-1;                                    
                    const float ymin = yaxis->GetBinLowEdge(ybin);             
                    const float ymax = yaxis->GetBinUpEdge(ybin);              
                                                                               
                    // row label                                               
                    string ylabel;                                             
                    if (not ytitle.empty())                                    
                    {                                                          
                        if (not yunit.empty())                                 
                        {                                                      
                            string format = "%" + yprecision + "f " + yunit + " < \%s < %" + yprecision + "f " + yunit;
                            ylabel = Form(format.c_str(), ymin, ytitle.c_str(), ymax);
                        }                                                      
                        else                                                   
                        {                                                      
                            string format = "%" + yprecision + "f < \%s < %" + yprecision + "f";
                            ylabel = Form(format.c_str(), ymin, ytitle.c_str(), ymax);
                        }                                                      
                    }                                                          
                    else                                                       
                    {                                                          
                        string format = "%" + yprecision + "f < \%s < %" + yprecision + "f";
                        ylabel = Form(format.c_str(), ymin, yaxis->GetTitle(), ymax);
                    }                                                          
                    table.setRowLabel(ylabel, row);                            
                                                                               
                    // set the cell                                            
                    string entry = (reverse_axis ? rt::pm(hist->GetBinContent(ybin, xbin), hist->GetBinError(ybin, xbin), precision) :
                                                   rt::pm(hist->GetBinContent(xbin, ybin), hist->GetBinError(xbin, ybin), precision));
                    table.setCell(entry, row, col);                            
                }                                                              
            }                                                                  
        }                                                                      
                                                                               
        // 1D hist                                                             
        else if (dynamic_cast<TH1*>(hist))                                     
        {                                                                      
            TAxis* const xaxis = hist->GetXaxis();                             
                                                                               
            for (int xbin = 1; xbin != xaxis->GetNbins()+1; xbin++)            
            {                                                                  
                const int row = xbin-1;                                        
                const float xmin = xaxis->GetBinLowEdge(xbin);                 
                const float xmax = xaxis->GetBinUpEdge(xbin);                  
                                                                               
                // column label                                                
                string xlabel;                                                 
                if (not xtitle.empty())                                        
                {                                                              
                    if (not xunit.empty())                                     
                    {                                                          
                        string format = "%" + xprecision + "f " + xunit + " < \%s < %" + xprecision + "f " + xunit;
                        xlabel = Form(format.c_str(), xmin, xtitle.c_str(), xmax);
                    }                                                          
                    else                                                       
                    {                                                          
                        string format = "%" + xprecision + "f < \%s < %" + xprecision + "f";
                        xlabel = Form(format.c_str(), xmin, xtitle.c_str(), xmax);
                    }                                                          
                }                                                              
                else                                                           
                {                                                              
                    string format = "%" + xprecision + "f < \%s < %" + xprecision + "f";
                    xlabel = Form(format.c_str(), xmin, xaxis->GetTitle(), xmax);
                }                                                              
                table.setRowLabel(xlabel, row);                                
                                                                               
                // set the cell                                                
                string entry = rt::pm(hist->GetBinContent(xbin), hist->GetBinError(xbin), precision);
                table.setCell(entry, row, 0);                                  
            }                                                                  
        }                                                                      
                                                                               
        return table;                                                          
    }                                                                          

    // print value and error with +/-
    std::string pm(double value, double error, const std::string& precision)
    {
        std::string format_string = "%" + precision + "f +/- %" + precision +"f";
        return std::string(Form(format_string.c_str(), value, error));
    }

    std::string pm(const std::pair<double, double>& value_pair, const std::string& precision)
    {
        std::string format_string = "%" + precision + "f +/- %" + precision +"f";
        return std::string(Form(format_string.c_str(), value_pair.first, value_pair.second));
    }
    
    std::string pm(const std::pair<float, float>& value_pair, const std::string& precision)
    {
        std::string format_string = "%" + precision + "f +/- %" + precision +"f";
        return std::string(Form(format_string.c_str(), value_pair.first, value_pair.second));
    }

    // print value and error with +/- in latex
    std::string pm_latex(double value, double error, const std::string& precision)
    {
        std::string format_string = "%" + precision + "f $\\pm$ %" + precision +"f";
        return std::string(Form(format_string.c_str(), value, error));
    }

    std::string pm_latex(const std::pair<double, double>& value_pair, const std::string& precision)
    {
        std::string format_string = "%" + precision + "f $\\pm$ %" + precision +"f";
        return std::string(Form(format_string.c_str(), value_pair.first, value_pair.second));
    }
    
    std::string pm_latex(const std::pair<float, float>& value_pair, const std::string& precision)
    {
        std::string format_string = "%" + precision + "f $\\pm$ %" + precision +"f";
        return std::string(Form(format_string.c_str(), value_pair.first, value_pair.second));
    }


    // calculate the Mt between two 4 vectors (The FGolf way)
    double Mt(const LorentzVector& p1, const LorentzVector& p2)
    {
        float phi1 = p1.Phi();
        float phi2 = p2.Phi();
        float Et1  = p1.Et();
        float Et2  = p2.Et();
        return sqrt(2*Et1*Et2*(1.0 - cos(phi1-phi2)));
    }

    // calulate Mt between LorentzVector and Missing ET
    double Mt(const LorentzVector& p4, double met, double met_phi)
    {
        float phi1 = p4.Phi();
        float phi2 = met_phi;
        float Et1  = p4.Et();
        float Et2  = met;
        return sqrt(2*Et1*Et2*(1.0 - cos(phi1-phi2)));
    }

    // calculate the Delta Phi between two angles 
    double DeltaPhi(double phi1, double phi2)
    {
        double dphi = phi1 - phi2;
        if (dphi < 0.0)         dphi = -1.0*dphi;
        if (dphi > TMath::Pi()) dphi = 2.0*TMath::Pi() - dphi;
        return dphi;
    }

    // calculate the Delta Phi between two 4 vectors 
    double DeltaPhi(const LorentzVector& p1, const LorentzVector& p2)
    {
        return ROOT::Math::VectorUtil::DeltaPhi(p1, p2); 
    }

    // calculate the Delta Phi between two 4 vectors 
    double DeltaEta(const LorentzVector& p1, const LorentzVector& p2)
    {
        return fabs(p1.Eta()-p2.Eta());
    }

    // calculate the DeltaR between two 4 vectors
    double DeltaR(const LorentzVector& p1, const LorentzVector& p2)
    {
        return ROOT::Math::VectorUtil::DeltaR(p1, p2); 
    }

    // get all the hists from a root file (given a file) in a map of hist pointers 
    // (give empty map if dir is incorrect or emptry)
    // (throws if file not found)
    // **************** needs work ***************************//
    map<string, rt::TH1Ptr> GetMapOfTH1s(const rt::TFilePtr& file, const string& root_file_dir)
    {
        using namespace std;

        if (file->IsZombie()) 
        {
            throw runtime_error(string("rt::GetMapOfTH1s() Error: '") + file->GetName() + "' not found or empty.  Aborting!");
        }

        map<string, rt::TH1Ptr> hist_map;
        if (!file->cd(root_file_dir.c_str()))
        {
            cout << "rt::GetMapOfTH1s() Warning: '" << root_file_dir 
                << " is not in the ROOT file (" << file->GetName() 
                << "). Returning empty map of hists" << endl;
            return hist_map;
        }
        for (TObjLink* link = gDirectory->GetListOfKeys()->FirstLink(); link != NULL; link = link->Next())
        {
            if (TH1* hist_ptr = dynamic_cast<TH1*>(gDirectory->Get(link->GetObject()->GetName())))
            {
#ifndef __RTINT__  // non interactive, I want to be in charge of deleting
                hist_ptr->SetDirectory(0);
#endif
                string name(hist_ptr->GetName());
                hist_map.insert(pair<string, rt::TH1Ptr>(name, rt::TH1Ptr(hist_ptr)));
            }
        }
        return hist_map;
    }

    // get all the hists from a root file (given a filename) in a map of hist pointers 
    // (give empty map if dir is incorrect or emptry)
    // (throws if file not found)
    map<string, rt::TH1Ptr> GetMapOfTH1s(const string& filename, const string& root_file_dir)
    {
        rt::TFilePtr file = rt::OpenRootFile(filename);
        return rt::GetMapOfTH1s(file, root_file_dir);
    }

    // get all the hists from a root file (given a file) in a map of hist pointers 
    // (give empty map if dir is incorrect or emptry)
    // (throws if file not found)
    vector<rt::TH1Ptr> GetVectorOfTH1s(const rt::TFilePtr& file, const string& root_file_dir)
    {
        using namespace std;

        if (file->IsZombie())
        {
            throw runtime_error(string("rt::GetVectorOfTH1s() Error: '") + file->GetName() + "' not found or empty.  Aborting!");
        }

        vector<rt::TH1Ptr> hist_vec;
        if (!file->cd(root_file_dir.c_str()))
        {
            cout << "rt::GetVectorOfTH1s() Warning: '" << root_file_dir 
                << " is not in the ROOT file (" << file->GetName() 
                << "). Returning empty vector of hists" << endl;
            return hist_vec;
        }
        for (TObjLink* link = gDirectory->GetListOfKeys()->FirstLink(); link != NULL; link = link->Next())
        {
            if (TH1* hist_ptr = dynamic_cast<TH1*>(gDirectory->Get(link->GetObject()->GetName())))
            {
#ifndef __RTINT__  // non interactive, I want to be in charge of deleting
                hist_ptr->SetDirectory(0);
#endif
                hist_vec.push_back(rt::TH1Ptr(hist_ptr));
            }
        }
        return hist_vec;
    }

    // get all the hists from a root file (given a filename) in a map of hist pointers 
    // (give empty map if dir is incorrect or emptry)
    // (throws if file not found)
    vector<rt::TH1Ptr> GetVectorOfTH1s(const string& filename, const string& root_file_dir)
    {
        rt::TFilePtr file = rt::OpenRootFile(filename);
        return rt::GetVectorOfTH1s(file, root_file_dir);
    }

    // print the histogram to eps/png/pdf 
    void Print
    (
        TH1* hist_ptr, 
        const string& dir_name, 
        const string& suffix,
        const string& file_name,
        const string& option,
        bool logy
    )
    {
        if (!( suffix == "eps" || suffix == "png" || suffix == "pdf" ))
        {
            cout << "suffix " << suffix << " not valid!  No print." << endl;
            return;
        }

        TCanvas c1("c1_Print_temp", "c1_Print_temp");
        c1.SetLogy(logy);
        c1.cd();

        rt::mkdir(dir_name, /*recursive=*/true);

        if (!hist_ptr)
        {
            cout << "rt::Print() Error: hist_ptr is NULL" << endl;
            return;
        }
        hist_ptr->Draw(option.c_str());
        std::string output_file_name = "";
        if (file_name.empty())
        {
            output_file_name = Form("%s/%s.%s", dir_name.c_str(), hist_ptr->GetName(), suffix.c_str());
        }
        else
        {
            output_file_name = Form("%s/%s.%s", dir_name.c_str(), file_name.c_str(), suffix.c_str());
        }
        c1.Print(output_file_name.c_str());
        rt::CopyIndexPhp(dir_name);
        return;
    }

#ifndef __RTINT__
    // print the histogram to eps/png/pdf
    void Print
    (
         const boost::shared_ptr<TH1>& hist_ptr, 
         const std::string& dir_name, 
         const std::string& suffix, 
         const std::string& file_name, 
         const std::string& option,
         bool logy
    )
    {
        Print(hist_ptr.get(), dir_name, suffix, file_name, option, logy);
    }
#endif // __RTINT__

    // print the plots to eps/png/pdf 
    void Print
    (
        map<string, rt::TH1Ptr>& hist_map, 
        const string& dir_name, 
        const string& suffix,
        const std::string& option,
        bool logy
    )
    {
        if (!( suffix == "eps" || suffix == "png" || suffix == "pdf" ))
        {
            cout << "suffix " << suffix << " not valid!  No print." << endl;
            return;
        }

        TCanvas c1("c1_Print_temp", "c1_Print_temp");
        c1.SetLogy(logy);
        c1.cd();

        rt::mkdir(dir_name, /*recursive=*/true);

        for (map<string, rt::TH1Ptr>::iterator itr = hist_map.begin(); itr != hist_map.end(); itr++)
        {
            if (!itr->second)
            {
                cout << "rt::Print() Warning: Object associated to " 
                    << itr->first << " is NULL -- skipping!" << endl;
                continue;
            }
            itr->second->Draw(option.c_str());
            c1.Print((dir_name + "/" + itr->first + "." + suffix).c_str());
        }
        rt::CopyIndexPhp(dir_name);
        return;
    }

    // print the plots to eps/png/pdf 
    void Print
    (
        vector<rt::TH1Ptr>& hist_vector, 
        const string& dir_name, 
        const string& suffix,
        const string& option,
        bool logy
    )
    {
        if (!( suffix == "eps" || suffix == "png" || suffix == "pdf" ))
        {
            cout << "suffix " << suffix << " not valid!  No print." << endl;
            return;
        }

        TCanvas c1("c1_Print_temp", "c1_Print_temp");
        c1.SetLogy(logy);
        c1.cd();

        rt::mkdir(dir_name, /*recursive=*/true);

        for(size_t i = 0; i < hist_vector.size(); i++)
        {
            if (!hist_vector[i])
            {
                cout << "rt::Print() Warning: Object is NULL -- skipping! " << endl;
                continue;
            }
            hist_vector[i]->Draw(option.c_str());
            c1.Print((dir_name + "/" +  hist_vector[i]->GetName() + "." + suffix).c_str());
        }
        rt::CopyIndexPhp(dir_name);
        return;
    }

    // save the contents of the map to a root file
    void Write
    (
        map<string, rt::TH1Ptr>& hist_map, 
        const string& file_name, 
        const string& root_file_dir,
        const string& option
    )
    {
        rt::mkdir(rt::dirname(file_name), /*recursive=*/true);

        rt::TFilePtr output_file(new TFile(file_name.c_str(), option.c_str()));
        output_file->cd("");
        if (!output_file->cd(root_file_dir.c_str()))
        {
            output_file->mkdir(root_file_dir.c_str());
        }
        output_file->cd(root_file_dir.c_str());

        for (map<string, rt::TH1Ptr>::iterator itr = hist_map.begin(); itr != hist_map.end(); itr++)
        {
            itr->second->Write(itr->first.c_str(), TObject::kOverwrite);
        }
        output_file->Close();
        return;
    }

    void Write
    (
         std::map<std::string, TH1Ptr>& hist_map, 
         TFile* root_file,
         const std::string& root_file_dir
    )
    {
        if (root_file->IsZombie()) 
            throw runtime_error(string("rt::Write() Error: '") + root_file->GetName() + "' not found or empty.  Aborting!");

        root_file->cd("");
        if (!root_file->cd(root_file_dir.c_str()))
        {
            root_file->mkdir(root_file_dir.c_str());
        }
        root_file->cd(root_file_dir.c_str());

        for (map<string, rt::TH1Ptr>::iterator itr = hist_map.begin(); itr != hist_map.end(); itr++)
        {
            itr->second->Write(itr->first.c_str(), TObject::kOverwrite);
        }
        return;
    }


    // save the contents of the vector to a root file
    void Write
    (
        vector<rt::TH1Ptr>& hist_vector, 
        const string& file_name, 
        const string& root_file_dir,
        const string& option
    )
    {
        rt::mkdir(rt::dirname(file_name), /*recursive=*/true);

        rt::TFilePtr output_file(new TFile(file_name.c_str(), option.c_str()));
        output_file->cd("");
        if (!output_file->cd(root_file_dir.c_str()))
        {
            output_file->mkdir(root_file_dir.c_str());
        }
        output_file->cd(root_file_dir.c_str());

        for (vector<rt::TH1Ptr>::iterator itr = hist_vector.begin(); itr != hist_vector.end(); itr++)
        {
            (*itr)->Write((*itr)->GetName(), TObject::kOverwrite);
        }
        output_file->Close();
        return;
    }

    // save a histogram to a file 
    void Write
    (
        const rt::TH1Ptr& hist_ptr, 
        const string& file_name, 
        const string& root_file_dir,
        const string& option
    )
    {
        if (!hist_ptr)
        {
            throw std::runtime_error("rt::Write() Warning: histogram pointer is NULL!");
        }

        rt::mkdir(rt::dirname(file_name), /*recursive=*/true);
        rt::TFilePtr output_file(new TFile(file_name.c_str(), option.c_str()));
        output_file->cd("");
        if (!output_file->cd(root_file_dir.c_str()))
        {
            output_file->mkdir(root_file_dir.c_str());
        }
        output_file->cd(root_file_dir.c_str());

        hist_ptr->Write(hist_ptr->GetName(), TObject::kOverwrite);
        output_file->Close();
        return;
    }

    // a fix to the issue of the erros on the profile hists
    void CalcErrorsForProfile(TProfile* profile)
    {
        if (!profile)
        {
            cout << "rt::CalcErrorsForProfile() Warning: profile pointer is NULL -- skipping! " << endl;
            return;
        }
        profile->SetErrorOption(" ");
        for(size_t i = 0; i < profile->GetEntries(); i++)
        {
            double err = profile->GetBinError(i);
            double N   = profile->GetEntries();
            profile->SetBinError(i, err/sqrt(N));
        }
        return;
    }

    // maximum value in hist 
    double GetHistMaximumValue(TH1* hist_ptr, bool include_error)
    {
        if (!hist_ptr)
        {
            throw std::runtime_error("rt::GetHistMaximumValue() Warning: histogram pointer is NULL!");
        }
        double result = hist_ptr->GetMaximum();
        if (include_error)
        {
            result += hist_ptr->GetBinError(hist_ptr->GetMaximumBin());
        }
        return result;
    }

    // Minimum value in hist 
    double GetHistMinimumValue(TH1* hist_ptr, bool include_error)
    {
        if (!hist_ptr)
        {
            throw std::runtime_error("rt::GetHistMaximumValue() Warning: histogram pointer is NULL!");
        }
        double result = hist_ptr->GetMinimum();
        if (include_error)
        {
            result -= hist_ptr->GetBinError(hist_ptr->GetMinimumBin());
        }
        return result >= 0.0 ? result : 0.0; // what is a negative histogram value?
    }

    // print list of files in a TChain
    void PrintFilesFromTChain(const TChain& chain)
    {
        cout << "rt::PrintFilesFromTChain:\n" << chain.GetName() << "\t# entries:  " << chain.GetEntries() << endl;
        TObjArray* list = chain.GetListOfFiles();
        for (int i = 0; i < list->GetEntries(); i++)
        {
            cout << "  " << list->At(i)->GetTitle() << endl;
        }
        return;
    }

    // print list of files in a TChain
    void PrintFilesFromTChain(TChain* chain)
    {
        if (!chain)
        {
            cout << "rt::PrintFilesFromTChain ERROR:  chain is NULL" << endl;
            return;
        }
        PrintFilesFromTChain(*chain);
        return;
    }

    // print list of files in a vector of TChain
    void PrintFilesFromTChain(std::vector<TChain*> chains)
    {
        for (std::vector<TChain*>::const_iterator ichain = chains.begin(); ichain != chains.end(); ichain++)
        {
            PrintFilesFromTChain(*ichain);
        }
    }

    // resturn a vector of files in a TChain
    vector<string> GetFilesFromTChain(TChain* chain)
    {
        if (!chain)
        {
            throw runtime_error("rt::GetFilesFromTChain:  chain is NULL");
        }
        vector<string> result;
        TObjArray* list = chain->GetListOfFiles();
        for (int i = 0; i < list->GetEntries(); i++)
        {
            result.push_back(list->At(i)->GetTitle());
        }
        return result;
    }

    // make a chain from a path
    TChain* MakeTChain(const std::string& glob, const std::string& treename, TChain* chain_in, bool verbose)
    {
        std::string cmd = "ls ";
        cmd += glob;
        FILE *f = popen(cmd.c_str(), "r");
        if (!f) {
            perror("Opening pipe");
            return 0;
        }
        TChain *c = chain_in == 0 ? new TChain(treename.c_str()) : chain_in;
        int s;
        do {
            char fname[1024];
            s = fscanf(f, " %1024s\n", fname);
            if (s != 1) {
                if (s != EOF)
                    perror("scanning file list");
            } else {
                if (verbose)
                    printf("Adding %s\n", fname);
                c->Add(fname);
            }
        } while (s == 1);
        if (pclose(f) == -1) 
            perror("Closing pipe");
        return c;
    }


    // Calculate the uncertainty on the generated yields
    float GetClopperPearsonUncertainty(const int num_passed, const int num_generated, const float level, const bool use_upper)
    {
        if (num_generated <= 0) 
        {
            throw std::domain_error("[GetMCUncertainty]: num_generated must be greater than zero"); 
        }
    
        TEfficiency eff;
        const float upper = eff.ClopperPearson(num_generated, num_passed, level, use_upper);
        const float delta = upper - (static_cast<float>(num_passed)/static_cast<float>(num_generated));
        return (delta * static_cast<float>(num_generated));
    }


    // create a chain from a comma serperated list (e.g. "file1,file2,...")
    // NOTE: user is charge of deleting!
    TChain* CreateTChainFromCommaSeperatedList
    (
        const std::string& str, 
        const std::string& treename, 
        const std::string& prefix
    )
    {
        using namespace std;
        TChain* chain = NULL;
        vector<string> files = string_split(str, ",");    
        for (size_t i = 0; i != files.size(); i++)
        {
            std::string full_path = prefix+files.at(i);
            if (i == 0)
                chain = MakeTChain(full_path.c_str(), treename.c_str());
            else
                chain = MakeTChain(full_path.c_str(), treename.c_str(), chain);
        }

        // check the chain
        if (!chain)
        {
            throw std::runtime_error("ERROR RT::CreateTChainFromCommaSeperatedList -- chain is NULL");
        }
    
        return chain;
    }

    // create a Projection from 2D hist 
    TH1* MakeProjectionPlot
    (
        TH2* hist, 
        const std::string& axis, 
        const std::string& name, 
        const std::string& title, 
        double low, 
        double high,
        const std::string& option
    )
    {
        // check that hists are valid
        if (!hist)
        {
            throw runtime_error("rt::MakeProjectionPlot: the Histogram is NULL");
        }

        // check that axis is setup to an one of the apppriate values
        string axis_name = string_lower(axis);
        if (axis_name != "x" && axis_name != "y") 
        {
            throw runtime_error("rt::MakeProjectionPlot: Invalid axis choice (\"X\" or \"Y\")");
        }

        // get the appropriate bins
        TAxis* xaxis = (axis_name=="y") ? hist->GetYaxis() : hist->GetXaxis();
        TAxis* yaxis = (axis_name=="y") ? hist->GetXaxis() : hist->GetYaxis();
        int first_bin = 0;
        int last_bin  = yaxis->GetNbins()+1;
        if (high > low)
        {
            first_bin = yaxis->FindBin(low+0.00001);    
            last_bin  = yaxis->FindBin(high-0.00001);    
//             cout << "x1 = " << yaxis->GetBinCenter(first_bin) << endl;
//             cout << "x2 = " << yaxis->GetBinCenter(last_bin) << endl;
        }

        string hist_name  = name.empty() ? string(hist->GetName()) + "_proj" + axis : name;
        string hist_title = title.empty() ? string(hist->GetTitle()) + " " + axis + " projection" : title;
        TH1* result       = (axis_name=="y") ? hist->ProjectionY(hist_name.c_str(), first_bin, last_bin, option.c_str()) : 
                                               hist->ProjectionX(hist_name.c_str(), first_bin, last_bin, option.c_str());
        result->SetNameTitle(hist_name.c_str(), hist_title.c_str());
        result->GetXaxis()->ImportAttributes(xaxis);
        result->GetXaxis()->SetTitle(xaxis->GetTitle());
        if (!hist->GetSumw2N())
        {
            hist->Sumw2();
        }
        return result;
    }

    // create a Projection from num and den hists 
    TH1* MakeEfficiencyProjectionPlot
    (
        TH2* num_hist, 
        TH2* den_hist, 
        const std::string& axis, 
        const std::string& name, 
        const std::string& title, 
        double low, 
        double high,
        const std::string& option
    )
    {
        // check that hists are valid
        if (!num_hist || !den_hist)
        {
            throw runtime_error("rt::MakeEfficiencyProjectionPlot: one of the Histograms are NULL");
        }

        // check that axis is setup to an one of the apppriate values
        string axis_name = string_lower(axis);
        if (axis_name != "x" && axis_name != "y") 
        {
            throw runtime_error("rt::MakeEfficiencyProjectionPlot: Invalid axis choice (\"X\" or \"Y\")");
        }

        TH1* h_num = MakeProjectionPlot(num_hist, axis_name, Form("%s_num", name.c_str()), title, low, high, option.c_str());  
        TH1* h_den = MakeProjectionPlot(den_hist, axis_name, Form("%s_den", name.c_str()), title, low, high, option.c_str());  
        TH1* h_eff = MakeEfficiencyPlot(h_num, h_den, name, title);  
        h_eff->SetNameTitle(name.c_str(), title.empty() ? name.c_str() : title.c_str());
        delete h_num;
        delete h_den;
        return h_eff;
    }

    // create a Projection from num and den hists 
    // this version for convenience (num and den hist must be castable to TH2*)
    TH1* MakeEfficiencyProjectionPlot
    (
        TH1* num_hist, 
        TH1* den_hist, 
        const std::string& axis, 
        const std::string& name, 
        const std::string& title, 
        double low, 
        double high,
        const std::string& option
    )
    {
        TH2* num_hist_temp = dynamic_cast<TH2*>(num_hist);
        TH2* den_hist_temp = dynamic_cast<TH2*>(den_hist);

        // check that hists are valid after cast
        if (!num_hist_temp || !den_hist_temp)
        {
            throw runtime_error("rt::MakeEfficiencyProjectionPlot: one of the Histograms are NULL or not castable to a TH2*");
        }
        return MakeEfficiencyProjectionPlot(num_hist_temp, den_hist_temp, axis, name, title, low, high, option);
    }

    // make an efficiency plot by dividing the two histograms 
    TH1* MakeEfficiencyPlot(TH1* num_hist, TH1* den_hist, const std::string& name, const std::string& title)
    {
        // check that hists are valid
        if (!num_hist || !den_hist)
        {
            throw runtime_error("rt::MakeEfficiencyPlot: one of the Histograms are NULL");
        }

        // verify that all histograms have same binning
        if (den_hist->GetNbinsX() != num_hist->GetNbinsX()) 
        {
            throw runtime_error("rt::MakeEfficiencyPlot: Histograms must have same number of bins");
        }

        // get the new histogram
        TH1F* temp = (TH1F*) num_hist->Clone(name.c_str());
        temp->SetTitle(title.empty() ? name.c_str() : title.c_str());
        temp->Reset();
        if (!temp->GetSumw2N())
        {
            temp->Sumw2();
        }

        // Do the calculation
        temp->Divide(num_hist, den_hist, 1.0, 1.0, "B");

        // Done
        return temp;
    }

    // make a 2D efficiency plot by dividing the two histograms 
    TH2* MakeEfficiencyPlot2D(TH1* num_hist, TH1* den_hist, const std::string& name, const std::string& title)
    {
        TH2* num_hist_temp = dynamic_cast<TH2*>(num_hist);
        TH2* den_hist_temp = dynamic_cast<TH2*>(den_hist);

        // check that hists are valid after cast
        if (!num_hist_temp || !den_hist_temp)
        {
            throw runtime_error("rt::MakeEfficiencyPlot2D: one of the Histograms are NULL or not castable to a TH2*");
        }
        return MakeEfficiencyPlot2D(num_hist_temp, den_hist_temp, name, title);
    }

    TH2* MakeEfficiencyPlot2D(TH2* num_hist, TH2* den_hist, const std::string& name, const std::string& title)
    {
        // check that hists are valid
        if (!num_hist || !den_hist)
        {
            throw runtime_error("rt::MakeEfficiencyPlot2D: one of the Histograms are NULL");
        }

        // verify that all histograms have same binning
        if ((den_hist->GetNbinsX() != num_hist->GetNbinsX()) && (den_hist->GetNbinsY() != num_hist->GetNbinsY())) 
        {
            throw runtime_error("rt::MakeEfficiencyPlot2D: Histograms must have same number of bins");
        }

        // get the new histogram
        TH2F* temp = dynamic_cast<TH2F*>(num_hist->Clone(name.c_str()));
        temp->SetTitle(title.empty() ? name.c_str() : title.c_str());
        temp->Reset();
        if (!temp->GetSumw2N())
        {
            temp->Sumw2();
        }

        // Do the calculation
        temp->Divide(num_hist, den_hist, 1.0, 1.0, "B");

        // Done
        return temp;
    }

    // Subtract Hists and return new hist (client is owner of the TH1*)
    TH1* SubtractHists(TH1* h1, TH1* h2, const std::string& name, const std::string& title)
    {
        // check that hists are valid
        if (!h1 || !h2)
        {
            throw runtime_error("rt::SubtractHists: at least one of the Histograms are NULL");
        }

        TH1* h_result = dynamic_cast<TH1*>(h1->Clone(name.c_str()));
        if (not title.empty())
        {
            h_result->SetTitle(title.c_str());
        }
        h_result->Add(h1, h2, 1.0, -1.0);
        return h_result;
    }

    // Add Hists and return new hist (client is owner of the TH1*)
    TH1* AddHists(TH1* h1, TH1* h2, const std::string& name, const std::string& title)
    {
        // check that hists are valid
        if (!h1 || !h2)
        {
            throw runtime_error("rt::AddHists: at least one of the Histograms are NULL");
        }

        TH1* h_result = dynamic_cast<TH1*>(h1->Clone(name.c_str()));
        if (not title.empty())
        {
            h_result->SetTitle(title.c_str());
        }
        h_result->Add(h1, h2, 1.0, 1.0);
        return h_result;
    }

    // Add Hists and return new hist (client is owner of the TH1*)
    TH1* AddHists(TH1* h1, TH1* h2, TH1* h3, const std::string& name, const std::string& title)
    {
        // check that hists are valid
        if (!h1 || !h2 || !h3)
        {
            throw runtime_error("rt::AddHists: at least one of the Histograms are NULL");
        }

        TH1* h_result = dynamic_cast<TH1*>(h1->Clone(name.c_str()));
        if (not title.empty())
        {
            h_result->SetTitle(title.c_str());
        }
        h_result->Add(h1, h2, 1.0, 1.0);
        h_result->Add(h3, 1.0);
        return h_result;
    }

    // Divide Hists and return new hist (client is owner of the TH1*)
    TH1* DivideHists(TH1* h_num, TH1* h_den, const std::string& name, const std::string& title, const std::string& option)
    {
        // check that hists are valid
        if (!h_num || !h_den)
        {
            throw runtime_error("rt::DivideHists: at least one of the Histograms are NULL");
        }

        TH1* h_result = dynamic_cast<TH1*>(h_num->Clone(name.c_str()));
        if (not title.empty())
        {
            h_result->SetTitle(title.c_str());
        }
        h_result->Divide(h_num, h_den, 1.0, 1.0, option.c_str());
        return h_result;
    }

    // Muilplty Hists and return new hist (client is owner of the TH1*)
    TH1* MultiplyHists(TH1* h1, TH1* h2, const std::string& name, const std::string& title, const std::string& option)
    {
        // check that hists are valid
        if (!h1 || !h2)
        {
            throw runtime_error("rt::DivideHists: at least one of the Histograms are NULL");
        }

        TH1* h_result = dynamic_cast<TH1*>(h1->Clone(name.c_str()));
        if (not title.empty())
        {
            h_result->SetTitle(title.c_str());
        }
        h_result->Multiply(h1, h2, 1.0, 1.0, option.c_str());
        return h_result;
    }

    // Subtract Hists and then divide by the first and return new hist (client is owner of the TH1*)
    // rel diff = (h1 - h2)/h1
    TH1* RelativeDiffHists(TH1* h1, TH1* h2, const std::string& name, const std::string& title)
    {
        // check that hists are valid
        if (!h1 || !h2)
        {
            throw runtime_error("rt::RelativeDiffHist: at least one of the Histograms are NULL");
        }

        TH1* h_unity  = dynamic_cast<TH1*>(h1->Clone("h_unity"));
        if (not h_unity->GetSumw2())
        {
            h_unity->Sumw2();
        }
        h_unity->Divide(h_unity, h_unity, 1.0, 1.0, "B"); // zero outs the error
        TH1* h_result = dynamic_cast<TH1*>(h1->Clone(name.c_str()));
        if (not title.empty())
        {
            h_result->SetTitle(title.c_str());
        }
        h_result->Divide(h2, h1, 1.0, 1.0);
        h_result->Add(h_unity, h_result, 1.0, -1.0);
        return h_result;
    }

    // mask off all values that are in the range and set the values to zero 
    void MaskHist2D(TH1* hist, std::string axis_label, const float low, const float high)
    {
        // check that hists are valid
        if (!hist)
        {
            throw runtime_error("rt::MaskHist2D: Histograms are NULL");
        }
        if (!dynamic_cast<TH2*>(hist))
        {
            throw runtime_error("rt::MaskHist2D: Histograms is not 2D");
        }

        // check that axis is setup to an one of the apppriate values
        axis_label = string_lower(axis_label);
        if (axis_label != "x" && axis_label != "y") 
        {
            throw runtime_error("rt::MaskHist2D: Invalid axis choice (\"X\" or \"Y\")");
        }

        for (int xbin = 1; xbin != hist->GetXaxis()->GetNbins()+1; xbin++)
        {
            const float xvalue = hist->GetXaxis()->GetBinCenter(xbin);
            for (int ybin = 1; ybin != hist->GetYaxis()->GetNbins()+1; ybin++)
            {
                const float yvalue = hist->GetYaxis()->GetBinCenter(ybin);
                if (axis_label == "x" && low <= xvalue && xvalue <= high)
                {
                    hist->SetBinContent(xbin, ybin, 0.0f);
                    hist->SetBinError(xbin, ybin, 0.0f);
                }
                if (axis_label == "y" && low <= yvalue && yvalue <= high)
                {
                    hist->SetBinContent(xbin, ybin, 0.0f);
                    hist->SetBinError(xbin, ybin, 0.0f);
                }
            }
        }
        return;
    }

    // copy the index.php file to dirname
    void CopyIndexPhp(const std::string& target_dir)
    {
        if (!exists(dirname(target_dir)))
        {
            throw runtime_error("rt::CopyIndexPhp: destination directory doesn't exist");
        }
        string source = Form("%s/tools/index.php", gSystem->Getenv("PAC"));
        copy_file(source, target_dir + "/index.php");
        return;
    }

    // wrapper around TTree::Draw to manange underflow and overflow bins
    long TTreeDraw1D
    (
        TTree* const tree, 
        TH1* hist_ptr, 
        const std::string& varexp, 
        const TCut& selection, 
        const std::string& option, 
        long nentries, 
        long firstentry
    )
    {
        if (!hist_ptr)
        {
            throw std::runtime_error("rt::TTreeDraw1D() Error: histogram pointer is NULL!");
        }
        if (!tree)
        {
            throw std::runtime_error("rt::TTreeDraw1D() Error: tree pointer is NULL!");
        }

        // parse the varexp
        bool append = string_contains(varexp, ">>+");
        string varexp_temp(varexp);
        if (append)
        {
            varexp_temp = string_remove_all(varexp, ">>+");
        }

        const TAxis& axis     = *hist_ptr->GetXaxis();
        int last_bin          = axis.GetLast();
        int first_bin         = axis.GetFirst();
        float last_bin_width  = axis.GetBinWidth(last_bin);
        float first_bin_width = axis.GetBinWidth(last_bin);
        float right_edge      = axis.GetBinUpEdge(last_bin) - 0.1*last_bin_width;
        float left_edge       = axis.GetBinLowEdge(first_bin) + 0.1*first_bin_width;
        const string varexp_formated = append ? Form("max(%f, min(%f, %s))>>+%s", left_edge, right_edge, varexp_temp.c_str(), hist_ptr->GetName()) :
                                                Form("max(%f, min(%f, %s))>>%s" , left_edge, right_edge, varexp_temp.c_str(), hist_ptr->GetName());
        //cout << varexp_formated << endl;
        return tree->Draw(varexp_formated.c_str(), selection, option.c_str(), nentries, firstentry); 
    }

    long TTreeDraw1D
    (
        TTree* const tree, 
        TH1* hist_ptr, 
        const std::string& varexp, 
        const std::string& selection, 
        const std::string& option, 
        long nentries, 
        long firstentry
    )
    {
        return TTreeDraw1D(tree, hist_ptr, varexp, TCut(selection.c_str()), option, nentries, firstentry);
    }

    // add root files (returns 0 if successful) -- lower case to match the utility name
    int hadd(const std::string& target, const std::vector<std::string>& sources)
    {
        // create the target folder (if it doesn't exist)
        if (!exists(dirname(target)))
        {
            mkdir(dirname(target));
        }

        // test if its has valid root files -- if not, then quit
        if(sources.empty())
        {
            cout << "ERROR: rt::hadd() No sources to process.  Exiting..." << endl;
            return 1;
        }

        // build merger
        TFileMerger file_merger;
        for (size_t i = 0, size = sources.size(); i != size; i++) 
        { 
            file_merger.AddFile(sources.at(i).c_str());
        }

        // open output file
        bool opened = file_merger.OutputFile(target.c_str());
        if (not opened)
        {
            cout << "ERROR: rt::hadd() opening target failed.  Exiting...\n" << endl;
            return 1;
        }

        // merge
        bool merged = file_merger.Merge();
        if (not merged)
        {
            cout << "ERROR: rt::hadd() merge failed.  Exiting...\n" << endl;
            return 1;
        }

        return 0;
    }

    ostream& operator << (ostream& os, const LorentzVector& p4)
    {
        os << "(" 
            << p4.Px() << ", " 
            << p4.Py() << ", " 
            << p4.Pz() << ", " 
            << p4.E()  << ")"; 
        return os;
    }

    // format the float to a string
    std::string fmt(const float value, const std::string& format)
    {
        std::string format_string = "%" + format;
        return std::string(Form(format_string.c_str(), value));
    }

    // get an environment variable
    std::string getenv(const std::string& name)
    {
        if (name.empty())
        {
            std::cerr << "WARNING: rt::genenv: input is NULL.  Did you forget to set the env var?" << std::endl;
            return "";
        }

        // need the :: to access getenv in global namespace (from cstdlib)
        string result(::getenv(name.c_str()));
        return result;
    }

    // get a root file
    bool copy_file(const string& source, const string& destination)
    {
        // TODO --> use boost
        return gSystem->Exec(("cp " + source + " " + destination).c_str()) == 0;
    }

    // get a root file
    bool move_file(const string& source, const string& destination)
    {
        // TODO --> use boost
        return gSystem->Exec(("mv " + source + " " + destination).c_str()) == 0;
    }

    // Get a vector of the filenames in a directory
    vector<string> get_list_of_files(const string &path, bool show_hidden_files)
    {
        namespace fs = boost::filesystem;

        vector<string> result;
        if (fs::exists(path))
        {
            if (fs::is_directory(path))
            {
                // for each filesystem object in this directory
                // (directories, files, other)
                for (fs::directory_iterator dir_itr(path), dir_end; dir_itr != dir_end; ++dir_itr)
                {
                    // if its a file, add it to our list
                    if (fs::is_regular_file(dir_itr->status()))
                    {
                        string file_name = dir_itr->path().filename().string();
                        // kludge until i figure out the more general way
                        if (show_hidden_files)  
                        {
                            result.push_back(path + "/" + file_name);
                        }
                        else
                        {
                            if (file_name.at(0) != '.')  
                            {
                                result.push_back(path + "/" + file_name);
                            }
                        }
                    }
                }
            }
            else // not a directory, must be a file
            {
                result.push_back(path);
            }
        }
        return result;
    }

    // helper function for below
    std::string to_regex_copy(std::string mask)
    {
        std::string rv = boost::regex_replace(boost::regex_replace(boost::regex_replace(mask, boost::regex( "\\." ), "\\\\."), boost::regex("\\?"), "\\."), boost::regex("\\*"), "\\.*");
        return rv ;
    }

    // simple ls function
    vector<string> ls(const string& pcszMask)
    {
        namespace fs = boost::filesystem;
        boost::filesystem::path path;
        boost::regex mask;
        if (fs::is_directory(pcszMask))
        {
            path = pcszMask;
            mask = ".*" ;
        }
        else
        {
            path = fs::path(pcszMask).remove_filename();
            mask = to_regex_copy(fs::path(pcszMask).filename().string());
        }

        std::vector<std::string> rv;
        try
        {
            for (fs::directory_iterator dir_itr(path), dir_end; dir_itr != dir_end; ++dir_itr)
            {
                string file_name = dir_itr->path().filename().string();
                if (boost::regex_match(file_name, mask))
                {
                    rv.push_back(dir_itr->path().string());
                }
            }
        }
        catch(...)
        {
            // do nothing
        }

        return rv;
    }

    // Get a vector of the filenames in a directory from CASTOR
    vector<string> get_list_of_files_from_castor(const string &path)
    {
        vector<string> result;
        FILE * file = gSystem->OpenPipe(("nsls " + path).c_str(), "r");
        const size_t line_size = 1024;
        char line[line_size];

        if (file == NULL) 
        {
            throw runtime_error(string("rt::get_list_of_file() Error: '") + path + "' not found or empty.  Aborting!");
        }
        else
        {
            while (fgets(line, sizeof(line), file) != NULL)
            {
                string filename = string(line);
                filename = filename.substr(0,filename.find("\n"));
                result.push_back("rfio:" + path + "/" + filename); 
            }
            fclose(file);
        }
        return result;
    }

    // get the base name of file from a full path (i.e. /path/to/file.txt --> file) 
    string basename(const string& full_name)
    {
        namespace fs = boost::filesystem;
        return fs::path(full_name).stem().string();
    }

    // get the extension  name of file from a full path (i.e. /path/to/file.txt --> .txt) 
    string extension(const string& full_name)
    {
        namespace fs = boost::filesystem;
        return fs::path(full_name).extension().string();
    }

    // get the filename file from a full path (i.e. /path/to/file.txt --> file.txt) 
    string filename(const string& full_name)
    {
        namespace fs = boost::filesystem;
        return fs::path(full_name).filename().string();
    }

    // get the path from a full path (i.e. /path/to/file.txt --> /path/to) 
    string dirname(const string& full_name)
    {
        namespace fs = boost::filesystem;
        return fs::path(full_name).parent_path().string();
    }

    // create a folder 
    bool mkdir(const string& path_name, bool force)
    {
        namespace fs = boost::filesystem;
        fs::path p = fs::path(path_name);
        if (!fs::exists(p))
        {
            try
            {
                if (force)
                    return fs::create_directories(p);
                else
                    return fs::create_directory(p);
            }
            catch(std::exception& e)
            {
                cout << e.what() << endl;
                return false;
            }
        }
        else
        {
            if (!force)
                cout << "rt::mkdir Warning: " << path_name << " already exists!" << endl;
            return false;
        }
    }

    // create a folder from the file_name 
    string mkdir_from_filename(const std::string& file_name, bool force)
    {
        string path = rt::dirname(file_name);
        if (path.empty())
        {
            return file_name;
        }
        if (!rt::exists(path))
        {
            if(!rt::mkdir(path, force))
            {
                throw runtime_error(string("rt::mkdir_from_file() Error: '") + path + "' cannot be created.  Aborting!");
            }
        }
        return file_name;
    }

    // remove a file 
    void remove(const string& file_name, bool force)
    {
        namespace fs = boost::filesystem;
        fs::path p = fs::path(file_name);
        if (force)
            fs::remove_all(p);
        else
            fs::remove(p);
        return;
    }

    // does file exist?
    bool exists(const string& file_name) 
    {
        namespace fs = boost::filesystem;
        return fs::exists(fs::path(file_name));
    }

    // does str contain sub_str?
    bool string_contains(const std::string& str, const std::string& sub_str)
    {
        return std::string::npos != str.find(sub_str);
    }

    // split the string into a vector of string based on the deliminator 
    std::vector<std::string> string_split(const std::string& str, const std::string& delim)
    {
        std::vector<std::string> str_vector;
        boost::split(str_vector, str, boost::is_any_of(delim));
        return str_vector; 
    }

    // remove all occurrences of sub_str from str
    std::string string_remove_all(const std::string& str, const std::string& sub_str)
    {
        std::string result(str);
        while(string_contains(result, sub_str))
        {
            size_t pos = result.find(sub_str);
            result.erase(pos, sub_str.size());
        }
        return result;
    }

    // replace all occurrences of sub_str from str with new_sub_str
    std::string string_replace_all(const std::string& str, const std::string& sub_str, const std::string& new_sub_str)
    {
        std::string result(str);
        boost::replace_all(result, sub_str, new_sub_str); 
        return result;
    }

    // replace first occurrence of sub_str from str with new_sub_str
    std::string string_replace_first(const std::string& str, const std::string& sub_str, const std::string& new_sub_str)
    {
        std::string result(str);
        boost::replace_first(result, sub_str, new_sub_str); 
        return result;
    }

    // replace last occurrence of sub_str from str with new_sub_str
    std::string string_replace_last(const std::string& str, const std::string& sub_str, const std::string& new_sub_str)
    {
        std::string result(str);
        boost::replace_first(result, sub_str, new_sub_str); 
        return result;
    }

    // replace all upper case characters to lower case 
    std::string string_lower(const std::string& str)
    {
        std::string result(str);
        boost::to_lower(result);
        return result;
    }

    // replace all lower case characters to upper case 
    std::string string_upper(const std::string& str)
    {
        std::string result(str);
        boost::to_upper(result);
        return result;
    }

    // character is space
    bool is_space(char c)
    {
        return static_cast<bool>(isspace(c));
    }

    // character is not a space
    bool not_space(char c)
    {
        return !is_space(c);
    }

    // get an array of floats from an array of doubles
    float* ConvertDoubleArrayToFloatArray(const double *d, size_t n)
    {
        float* f = new float[n];
        for (size_t i=0; i != n; ++i) 
        {
            f[i] = static_cast<float>(d[i]);
        }
        return f;
    }

    // set style
    void SetStyle(const string& option)
    {
        TStyle *myStyle = gROOT->GetStyle("Plain");
        TGaxis::SetMaxDigits(5);
        myStyle->SetPaintTextFormat("1.3f");
        myStyle->SetOptStat(option.c_str());
        myStyle->SetOptFit(1111);
        myStyle->SetTitleBorderSize(0);
        myStyle->SetTitleFillColor(0);
        myStyle->SetTitleStyle(0);
        //myStyle->SetTitleX( 0.5 - 2.0*myStyle->GetTitleXSize() );
        //myStyle->SetTitleX( 0.05 );
        //myStyle->SetTitleY( 0.96 );
        //myStyle->SetTitleAlign(22);
        myStyle->SetLegendBorderSize(0);
#if ROOT_VERSION_CODE >= ROOT_VERSION(5,30,0)
        myStyle->SetLegendFillColor(0);
#endif

        //myStyle->SetTitleY(0.985);
        myStyle->SetHistLineColor(kBlue);
        myStyle->SetHistLineWidth(1);
        myStyle->SetPadGridX(1);
        myStyle->SetPadGridY(1);
        myStyle->SetGridColor(kGray+1);
        myStyle->SetCanvasDefW(600);
        myStyle->SetCanvasDefH(600);
        myStyle->SetStatH(0.09);
        myStyle->SetStatW(0.2);
        myStyle->SetStatX(0.99);
        myStyle->SetStatY(0.99);
        myStyle->SetStatBorderSize(myStyle->GetHistLineWidth());
        myStyle->SetStatTextColor(kBlack);
        myStyle->SetStatColor(0);
        //myStyle->SetStatStyle(Style_t style = 1001);
        //void SetStatBoxPosition(TH1* hist_ptr, float x1 = 0.8, float y1 = 0.8, float x2 = 1.0, float y2 = 1.0);

        myStyle->SetTitleOffset(1.2, "Y");
        myStyle->SetLabelSize(0.035, "Y");
        myStyle->SetLabelSize(0.035, "X");
        myStyle->cd();
        gStyle = myStyle;
    }

} // end namespace rt

