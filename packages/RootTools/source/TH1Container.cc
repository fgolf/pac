#include "rt/TH1Container.h"

// c++ includes
#include <iostream>
#include <iomanip>
#include <string>

// Root includes
#include "TClass.h"
#include "TDirectory.h"
#include "TPad.h"

// boost includes
#include <boost/shared_ptr.hpp>

// other includes
#include "rt/MiscTools.h"
#include "rt/Keyboard.h"


// helper functions
// ---------------------------------------------------------------------------------------- //

#if __RTINT__
template <typename T> T* get(T *p) {return p;}
#else
template <typename T> T* get(const boost::shared_ptr<T> &p) {return p.get();}
#endif


using namespace std;

typedef const boost::shared_ptr<TH1> TH1Ptr;
//typedef const TH1* TH1Ptr;

namespace rt
{

// declare data struct
// ---------------------------------------------------------------------------------------- //

struct TH1Container::impl
{
    static bool verbose;
    map<string, TH1Ptr> hist_map;
};

// constructor
// ---------------------------------------------------------------------------------------- //

TH1Container::TH1Container()
    : m_pimpl(new TH1Container::impl)
{
}


TH1Container::TH1Container(const std::string& file_name, const std::string& root_file_dir)
    : m_pimpl(new TH1Container::impl)
{
    Load(file_name, root_file_dir);
}


TH1Container::~TH1Container()
{
//#ifdef __RTINT__
//    for (map<string, TH1Ptr>::const_iterator iter = m_pimpl->hist_map.begin(); iter != m_pimpl->hist_map.end(); iter++)
//    {
//        delete iter->second; 
//    }
//#endif
}


TH1Container::TH1Container(const TH1Container& rhs)
    : m_pimpl(new TH1Container::impl)
{
    for (map<string, TH1Ptr>::const_iterator iter = rhs.m_pimpl->hist_map.begin(); iter != rhs.m_pimpl->hist_map.end(); iter++)
    {
        m_pimpl->hist_map[iter->first] = TH1Ptr(dynamic_cast<TH1*>(iter->second->Clone()));   
    }
    return;
}


void TH1Container::Swap(TH1Container& rhs)
{
    std::swap(m_pimpl->verbose , rhs.m_pimpl->verbose );
    std::swap(m_pimpl->hist_map, rhs.m_pimpl->hist_map);
    return;
}


TH1Container& TH1Container::operator=(const TH1Container& rhs)
{
    TH1Container temp(rhs);
    Swap(temp);
    return *this;
}


// members
// ---------------------------------------------------------------------------------------- //


TH1Container TH1Container::operator+(const TH1Container& rhs)
{
    TH1Container temp(*this);
    for (map<string, TH1Ptr>::const_iterator iter = rhs.m_pimpl->hist_map.begin(); iter != rhs.m_pimpl->hist_map.end(); iter++)
    {
        if(temp.Contains(iter->first))
            temp[iter->first]->Add(get(iter->second));
        else
            temp.Add(get(iter->second));
    }
    return temp;
}


TH1Container& TH1Container::operator+=(const TH1Container& rhs)
{
    TH1Container temp = this->operator+(rhs);
    Swap(temp);
    return *this;
}


void TH1Container::Add(TH1* hist_ptr, bool overwrite)
{
    // do we already have the histogram?
    string name = hist_ptr->GetName();
    bool hist_name_used = m_pimpl->hist_map.end() != m_pimpl->hist_map.find(name);
    if (hist_name_used)
    {
        try
        {
            bool same_pointer = (hist_ptr == get(m_pimpl->hist_map.at(name)));
            if (overwrite && !same_pointer)
            {
                cout << "TH1Container::add() Warning: '" << name << "' already exists.  Overwriting!" << endl;
            }
            else if (overwrite && same_pointer)
            {
                cout << "TH1Container::add() Warning: '" << name << "' already exists.  Leaving it alone!" << endl;
                return;
            }
            else
            {
                cout << "TH1Container::add() Warning: '" << name << "' already exists.  Skipping!" << endl;
                return;
            }
        }
        catch(exception& e)
        {
            cout << "rt::TH1Container::add() Error " << e.what() << endl;
        }
    }
    if (m_pimpl->verbose)
    {
        cout << "TH1Container::add(): Adding " << name << endl;
    }

//#ifndef __RTINT__  
//#endif
    // I want to be in charge of deleting
    hist_ptr->SetDirectory(0);
    m_pimpl->hist_map.insert(pair<string, TH1Ptr>(name, TH1Ptr(hist_ptr)));
    return;
}

void TH1Container::Add(TH1* hist_ptr, const std::string& option, bool overwrite)
{
    hist_ptr->SetOption(option.c_str());
	Add(hist_ptr, overwrite);
}

void TH1Container::Add(const TH1& hist, bool overwrite)
{
    Add(dynamic_cast<TH1*>(hist.Clone()), overwrite);
}

void TH1Container::Add(const TH1& hist, const std::string& option, bool overwrite)
{
    Add(dynamic_cast<TH1*>(hist.Clone()), option, overwrite);
}

// set the directory of the hists (needed for draw)
void TH1Container::SetDirectory(TDirectory* dir)
{
    for (map<string, TH1Ptr>::const_iterator iter = m_pimpl->hist_map.begin(); iter != m_pimpl->hist_map.end(); iter++)
    {
        iter->second->SetDirectory(dir);
    }
}

void TH1Container::SetDirectory(const std::string& hist_name, TDirectory* dir)
{
    Hist(hist_name)->SetDirectory(dir);
}


// remove a histogram
void TH1Container::Remove(const string& hist_name)
{
    m_pimpl->hist_map.erase(hist_name);
}


void TH1Container::Remove(const char* hist_name)
{
    remove(static_cast<string>(hist_name));
}


void TH1Container::Remove(const TString& hist_name)
{
    remove(static_cast<string>(hist_name.Data()));
}


void TH1Container::Remove(TH1* hist_ptr)
{
    remove(string(hist_ptr->GetName()));
}


// return a histogram (throws if not found)
TH1* TH1Container::Hist(const std::string& hist_name) const
{
    try
    {
        return get(m_pimpl->hist_map.at(hist_name));
    }
    catch(exception& e)
    {
        throw(std::domain_error("rt::TH1Container::hist() Error: " + hist_name + " not found!  Aborting."));
    }
}


TH1* TH1Container::Hist(const char* hist_name) const
{
    return Hist(static_cast<string>(hist_name));
}


TH1* TH1Container::Hist(const TString& hist_name) const
{
    return Hist(static_cast<string>(hist_name.Data()));
}


TH1* TH1Container::operator [] (const std::string& hist_name) const
{
    return Hist(hist_name);
}


TH1* TH1Container::operator [] (const char* hist_name) const
{
    return Hist(static_cast<string>(hist_name));
}


TH1* TH1Container::operator [] (const TString& hist_name) const
{
    return Hist(static_cast<string>(hist_name.Data()));
}

bool TH1Container::Contains(const std::string& hist_name) const
{
    return m_pimpl->hist_map.find(hist_name) != m_pimpl->hist_map.end();
}

void TH1Container::Load(const std::string& file_name, const std::string& root_file_dir)
{
    using namespace std;
    
    // file load
    auto_ptr<TFile> file(new TFile(file_name.c_str()));
    if (file->IsZombie()) 
    {
        throw runtime_error(string("rt::GetMapOfTH1s() Error: '") + file->GetName() + "' not found or empty.  Aborting!");
    }
    if (!file->cd(root_file_dir.c_str()))
    {
        cout << "rt::TH1Container::Load() Warning: '" << root_file_dir 
             << " is not in the ROOT file (" << file->GetName() 
             << ").  Doing nothing." << endl;
        return;
    }

    // get the hists
    for (TObjLink* link = gDirectory->GetListOfKeys()->FirstLink(); link != NULL; link = link->Next())
    {
        if (TH1* hist_ptr = dynamic_cast<TH1*>(gDirectory->Get(link->GetObject()->GetName())))
        {
            // I want to be in charge of deleting
            hist_ptr->SetDirectory(0);
            string name(hist_ptr->GetName());
            m_pimpl->hist_map.insert(pair<string, TH1Ptr>(name, TH1Ptr(hist_ptr)));
        }
    }
    file->Close();
    return;
}


void TH1Container::List() const
{
    cout << "TH1Container::List(): listing all histograms in the container" << endl;
    cout <<  "  " << setw(15) << left << "Hist Type" << "\t" << setw(15) << left << "Hist Name" << "\t" << "Hist Title" << endl; 
    cout <<  "-----------------------------------------------------------------------" << endl; 
    for (map<string, TH1Ptr>::const_iterator iter = m_pimpl->hist_map.begin(); iter != m_pimpl->hist_map.end(); iter++)
    {
        cout <<  "  " << setw(15) << left << iter->second->ClassName() << "\t" << setw(15) << left << iter->first 
             << "\t" << iter->second->GetTitle() << endl;
    }
}

#ifdef __RTINT__
void usage()
{
    cout << "TH1Container::view() usage:" << endl;
    cout << "up   --> draw next histogram" << endl;
    cout << "down --> draw previous histogram" << endl;
    cout << "q    --> quit the viewer" << endl;
}


void draw(TH1* h)
{
    if (h)
    {
        h->Draw();
        gPad->Update();
        cout << "drawing:\t" << h->GetName() << endl;
    }
    else
    {
        cout << "histogram is NULL" << endl;
    }
}


// viewing the histograms
void TH1Container::View()
{
    usage();
    map<string, TH1Ptr>::const_iterator begin_iter = m_pimpl->hist_map.begin();
    map<string, TH1Ptr>::const_iterator end_iter   = m_pimpl->hist_map.end();
    map<string, TH1Ptr>::const_iterator iter       = begin_iter;

    // draw the first one
    draw(iter->second);

    rt::key::value_type input = rt::key::null;
    while(input != rt::key::q)
    {
		input = rt::get_character_from_keyboard();
        // process input
        switch(input)
        {
            case rt::key::up: 
                iter++; 
                if (iter == end_iter)
                {
                    iter = begin_iter;
                }
                break;
            case rt::key::down: 
                if (iter == begin_iter)
                {
                    iter = end_iter;
                }
                iter--; 
                break;
            case rt::key::q: 
                cout << "quiting TH1Container::view()" << endl;
				continue;
                break;
            default: usage(); continue;
        }

        // draw the current one 
        draw(iter->second);
    }
}
#endif


void TH1Container::Scale(double scale, const std::string& option)
{
    for (map<string, TH1Ptr>::const_iterator iter = m_pimpl->hist_map.begin(); iter != m_pimpl->hist_map.end(); iter++)
    {
        iter->second->Scale(scale, option.c_str());
    }
}


void TH1Container::Normalize(double value)
{
    for (map<string, TH1Ptr>::const_iterator iter = m_pimpl->hist_map.begin(); iter != m_pimpl->hist_map.end(); iter++)
    {
		rt::Scale(get(iter->second), value);
    }
}


void TH1Container::Sumw2()
{
    for (map<string, TH1Ptr>::const_iterator iter = m_pimpl->hist_map.begin(); iter != m_pimpl->hist_map.end(); iter++)
    {
        if (!iter->second->GetSumw2N())
        {
            iter->second->Sumw2();
        }
    }
}


void TH1Container::SetLineColor(Color_t color)
{
    for (map<string, TH1Ptr>::const_iterator iter = m_pimpl->hist_map.begin(); iter != m_pimpl->hist_map.end(); iter++)
    {
        iter->second->SetLineColor(color);
    }
}


void TH1Container::SetLineStyle(Style_t style)
{
    for (map<string, TH1Ptr>::const_iterator iter = m_pimpl->hist_map.begin(); iter != m_pimpl->hist_map.end(); iter++)
    {
        iter->second->SetLineStyle(style);
    }
}


void TH1Container::SetLineWidth(Width_t width)
{
    for (map<string, TH1Ptr>::const_iterator iter = m_pimpl->hist_map.begin(); iter != m_pimpl->hist_map.end(); iter++)
    {
        iter->second->SetLineWidth(width);
    }
}


void TH1Container::SetMarkerColor(Color_t color)
{
    for (map<string, TH1Ptr>::const_iterator iter = m_pimpl->hist_map.begin(); iter != m_pimpl->hist_map.end(); iter++)
    {
        iter->second->SetMarkerColor(color);
    }
}


void TH1Container::SetMarkerSize(Size_t size)
{
    for (map<string, TH1Ptr>::const_iterator iter = m_pimpl->hist_map.begin(); iter != m_pimpl->hist_map.end(); iter++)
    {
        iter->second->SetMarkerSize(size);
    }
}


void TH1Container::SetMarkerStyle(Style_t style)
{
    for (map<string, TH1Ptr>::const_iterator iter = m_pimpl->hist_map.begin(); iter != m_pimpl->hist_map.end(); iter++)
    {
        iter->second->SetMarkerStyle(style);
    }
}
        

void TH1Container::SetOption(const std::string& option)
{
    for (map<string, TH1Ptr>::const_iterator iter = m_pimpl->hist_map.begin(); iter != m_pimpl->hist_map.end(); iter++)
    {
        iter->second->SetOption(option.c_str());
    }
}


void TH1Container::SetStats(bool stats)
{
    for (map<string, TH1Ptr>::const_iterator iter = m_pimpl->hist_map.begin(); iter != m_pimpl->hist_map.end(); iter++)
    {
        iter->second->SetStats(stats);
    }
}


void TH1Container::Write(const std::string& file_name, const std::string& root_file_dir, const std::string& option) const
{
    rt::Write(m_pimpl->hist_map, file_name, root_file_dir, option);
}

void TH1Container::Write(TFile* root_file, const std::string& root_file_dir) const
{
    rt::Write(m_pimpl->hist_map, root_file, root_file_dir);
}


void TH1Container::Print(const std::string& dir_name, const std::string& suffix, const std::string& option, bool logy) const
{
    rt::Print(m_pimpl->hist_map, dir_name, suffix, option, logy);
}


// verbosity setting
#ifdef __RTINT__  
//bool  TH1Container::impl::verbose = true;
bool  TH1Container::impl::verbose = false;
#else
bool  TH1Container::impl::verbose = false;
#endif
void TH1Container::SetVerbose(bool verbose)
{
    TH1Container::impl::verbose = verbose;        
}


} // namespace rt

