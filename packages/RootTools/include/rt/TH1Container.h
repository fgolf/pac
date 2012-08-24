#ifndef RT_TH1CONTAINER_H
#define RT_TH1CONTAINER_H

// c++ includes
#include <string>
#include <memory>

// ROOT includes
#include "TFile.h"
#include "TH1.h"
#include "TDirectory.h"

namespace rt
{

class TH1Container
{
    public:
        
        // constructors
        TH1Container();
        ~TH1Container();
        TH1Container(const std::string& file_name, const std::string& root_file_dir = "");
        TH1Container(const TH1Container& rhs);
        TH1Container& operator=(const TH1Container& rhs);
        TH1Container operator+(const TH1Container& rhs);
        TH1Container& operator+=(const TH1Container& rhs);
        void Swap(TH1Container& other);
        
        // add a histogram to the container 
        // (default is to skip duplicates, set overwite to write over)
        void Add(TH1* hist_ptr, bool overwrite = false);
        void Add(TH1* hist_ptr, const std::string& option, bool overwrite = false);

        // set the directory of the hists (needed for draw)
        void SetDirectory(TDirectory* dir = NULL);
        void SetDirectory(const std::string& hist_name, TDirectory* dir = NULL);
        
        // remove a histogram
        void Remove(const std::string& hist_name);
        void Remove(const char* hist_name);
        void Remove(const TString& hist_name);
        void Remove(TH1* hist_ptr);
        
        // return a histogram (throws if not found)
        TH1* Hist(const std::string& hist_name) const;
        TH1* Hist(const char* hist_name) const;
        TH1* Hist(const TString& hist_name) const;
        TH1* operator [] (const std::string& hist_name) const;
        TH1* operator [] (const char* hist_name) const;
        TH1* operator [] (const TString& hist_name) const;
        
        // contains a hist?
        bool Contains(const std::string& hist_name) const;

        // load all the histograms from a root file
        void Load(const std::string& file_name, const std::string& root_file_dir = "");
        
        // list all the hist in the container
        void List() const;
        
#ifdef __RTINT__
        // a simple viewer function (only interactive version)
        void View();
#endif

        // scale all the histograms in the container 
        void Scale(double scale, const std::string& option = "");
        
        // call Sumw2() on each histogram
        void Sumw2();
        
        // histogram attributes (sets them all) 
        void SetLineColor(Color_t color);
        void SetLineStyle(Style_t style);
        void SetLineWidth(Width_t width);
        void SetMarkerColor(Color_t color = 1);
        void SetMarkerSize(Size_t size = 1);
        void SetMarkerStyle(Style_t style = 1);
        void SetOption(const std::string& option = "");
        void SetStats(bool stats = true);
        
        // write all histograms to a root file
        void Write(const std::string& file_name, const std::string& root_file_dir = "", const std::string& option = "UPDATE") const;
        void Write(TFile* root_file, const std::string& root_file_dir = "") const;
        
        // print all histograms to an (eps, png, pdf)
        void Print(const std::string& dir_name, const std::string& suffix = "png", const std::string& option = "", bool logy = false) const;
        
        // static methods
        static void SetVerbose(bool verbose = true);
        
    private:
        
        // data members
        struct impl;
        std::auto_ptr<impl> m_pimpl;
};


} // namespace rt


#endif // RT_TH1CONTAINER_H

