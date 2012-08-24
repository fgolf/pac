#if !defined(__CINT__) || defined(__MAKECINT__)
#include "rt/MiscTools.hpp"
#include "rt/TH1Container.hpp"
#include <iostream>
#include "TSystem.h"
#include "TH1D.h"
#include "TH2D.h"
#endif

#ifndef __RTINT__
#include <functional>
#include "boost/bind.hpp"
#endif

// includes need by interpreter
#ifdef __CINT__
#include <stdexcept>
#endif


using namespace std;
using namespace rt;

void print_preprocessor_values()
{
// __RTINT__ is set
#ifdef __RTINT__ 
    cout << "__RTINT__ is defined" << endl;
#else
    cout << "__RTINT__ is NOT defined" << endl;
#endif

// CINT is set
#ifdef __CINT__
    cout << "__CINT__ is defined" << endl;
#else
    cout << "__CINT__ is NOT defined" << endl;
#endif

// MAKECINT is set
#ifdef __MAKECINT__
    cout << "__MAKECINT__ is defined" << endl;
#else
    cout << "__MAKECINT__ is NOT defined" << endl;
#endif

#if !defined(__CINT__) || defined(__MAKECINT__)
    cout << "!defined(__CINT__) || defined(__MAKECINT__) evaluates to TRUE" << endl;
#else
    cout << "!defined(__CINT__) || defined(__MAKECINT__) evaluates to FALSE" << endl;
#endif

#if !defined(__CINT__) && !defined(__MAKECINT__)
    cout << "!defined(__CINT__) && !defined(__MAKECINT__) evaluates to TRUE" << endl;
#else
    cout << "!defined(__CINT__) && !defined(__MAKECINT__) evaluates to FALSE" << endl;
#endif
}

template <typename T>
void print_vector(std::vector<T> v)
{
    for (typename std::vector<T>::iterator iter = v.begin(); iter != v.end(); iter++)
    {
        cout << *iter;
        if (iter != --v.end())
            cout << ", ";
    }
    cout << endl;
}

bool lt2(const int& value)
{
    return value < 2;
}

//template <typename T>
//struct greater_than
//{
//    greater_than(const T& value) : m_value(value) {}
//    bool operator() (const T& value) {return value < m_value;}
//    T m_value;
//};


void test_root_tools()
{
    cout << "--------------------------------------------------" << endl;
    cout << "ROOT Tools test" << endl;
    cout << "--------------------------------------------------" << "\n" << endl;

    // set up the path
    const string PAC(gSystem->Getenv("PAC"));
    const string path = PAC + "/packages/root_tools/test";
    const string full_file_name = path + "/data/hsimple.root";


    cout << "--------------------------------------------------" << endl;
    cout << "preprocessor values" << endl;
    cout << "--------------------------------------------------" << "\n" << endl;
    print_preprocessor_values();


    cout << "\n\n" << "--------------------------------------------------" << endl;
    cout << "rt::OpenRootFile()" << endl;
    cout << "--------------------------------------------------" << "\n" << endl;

    // File
    cout << "Opening the file with bare ROOT" << endl;
    TFile* file1 = new TFile(full_file_name.c_str());
    file1->ls();

    // File with OpenRootFile() - good
    cout << "\nOpening the file with OpenRootFile()" << endl;
    rt::TFilePtr file2 = rt::OpenRootFile(full_file_name);
    file2->ls();

    // File with OpenRootFile() -- fail
    cout << "\nOpening the file with OpenRootFile() for non-existent file" << endl;
    try
    {
        rt::TFilePtr file3 = rt::OpenRootFile("bogus.root");
        file3->ls();
    }
    catch (std::exception& e)
    {
        cout << "catching excection for bogus file: " << e.what() << endl;
    }

//    cout << "\n\n" << "--------------------------------------------------" << endl;
//    cout << "rt::create_root_file_dir()" << endl;
//    cout << "--------------------------------------------------" << "\n" << endl;
//    try
//    {
//        rt::TFilePtr new_file = rt::OpenRootFile(path + "/data/new_dir_test.root", "RECREATE");
//        new_file->ls();
//        rt::TDirectoryPtr d1(create_root_file_dir(new_file, "d1/d2/d3"));
//        if (d1)
//        {
//            cout << "making new directory" << endl;
//            d1->ls();
//        }
//        else
//        {
//            cout << "failed to create dir" << endl;
//        }
//        new_file->Close();
//
//        //rt::TFilePtr new_file2 = rt::OpenRootFile(path + "/data/new_dir_test2.root", "RECREATE");
//        //rt::TDirectoryPtr d2(create_root_file_dir(new_file2, "d1/d2/d3"));
//        //if (d2)
//        //{
//        //    cout << "making new directory" << endl;
//        //    d2->ls();
//        //}
//        //else
//        //{
//        //    cout << "failed to create dir" << endl;
//        //}
//        //new_file2->Close();
//
//        //delete d1;
//        //delete d2;
//    }
//    catch (std::exception& e)
//    {
//        cout << e.what() << endl;
//    }



    cout << "\n\n" << "--------------------------------------------------" << endl;
    cout << "rt::GetMapOfTH1s()" << endl;
    cout << "--------------------------------------------------" << "\n" << endl;
    try
    {
        cout << "\nCout the hist from file with GetMapOfTH1s()" << endl;
        std::map<std::string, rt::TH1Ptr> hist = rt::GetMapOfTH1s(file2);
        for (std::map<std::string, rt::TH1Ptr>::iterator iter = hist.begin(); iter != hist.end(); iter++)
        {
            cout << "name\t" << iter->first << "\t" << iter->second->GetName() << endl;
        }
        file2->ls();
        
        cout << "\nCout the hist from filename with GetMapOfTH1s()" << endl;
        std::map<std::string, rt::TH1Ptr> hist2 = rt::GetMapOfTH1s(file2);
        for (std::map<std::string, rt::TH1Ptr>::iterator iter = hist2.begin(); iter != hist2.end(); iter++)
        {
            cout << "name\t" << iter->first << "\t" << iter->second->GetName() << endl;
        }
        file2->ls();
    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
    }
    
    cout << "\n\n" << "--------------------------------------------------" << endl;
    cout << "rt::GetVectorOfTH1s()" << endl;
    cout << "--------------------------------------------------" << "\n" << endl;
    try
    {
        cout << "\nCout the hist from file with GetVectorOfTH1s()" << endl;
        std::vector<rt::TH1Ptr> hist3 = rt::GetVectorOfTH1s(file2);
        for (size_t i = 0; i < hist3.size(); i++)
        {
            cout << "name\t" << hist3[i]->GetName() << endl;
        }
        
        cout << "\nCout the hist from filename with GetVectorOfTH1s()" << endl;
        std::vector<rt::TH1Ptr> hist4 = rt::GetVectorOfTH1s(file2);
        for (size_t i = 0; i < hist4.size(); i++)
        {
            cout << "name\t" << hist4[i]->GetName() << endl;
        }
    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
    }
    
    
    cout << "\n\n" << "--------------------------------------------------" << endl;
    cout << "rt::Print() (map)" << endl;
    cout << "--------------------------------------------------" << "\n" << endl;
    try
    {
        cout << "\nPrint the hist from file with Print()" << endl;
        std::map<std::string, rt::TH1Ptr> hist = rt::GetMapOfTH1s(file2);
        rt::Print(hist, path + "/data/hists/eps", "eps");
        rt::Print(hist, path + "/data/hists/pdf", "pdf");
        rt::Print(hist, path + "/data/hists/png", "png");
    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
    }
    
    
    cout << "\n\n" << "--------------------------------------------------" << endl;
    cout << "rt::Print() (vector)" << endl;
    cout << "--------------------------------------------------" << "\n" << endl;
    try
    {
        cout << "\nPrint the hist from file with Print()" << endl;
        std::map<std::string, rt::TH1Ptr> hist = rt::GetMapOfTH1s(file2);
        std::vector<rt::TH1Ptr> hist_vec;
        hist_vec.push_back(hist["hpx"]);
        hist_vec.push_back(hist["hpxpy"]);
        hist_vec.push_back(hist["hprof"]);
        rt::Print(hist, path + "/data/hists/eps", "eps");
        rt::Print(hist, path + "/data/hists/pdf", "pdf");
        rt::Print(hist, path + "/data/hists/png", "png");
    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
    }
    
    
    cout << "\n\n" << "--------------------------------------------------" << endl;
    cout << "rt::Write() (map)" << endl;
    cout << "--------------------------------------------------" << "\n" << endl;
    try
    {
        cout << "\nSave the the hist to a ROOT file with Write()" << endl;
        std::map<std::string, rt::TH1Ptr> hist5 = rt::GetMapOfTH1s(file2);
        rt::Write(hist5, path + "/data/hists/hsave.root");
        rt::TFilePtr fsave = rt::OpenRootFile(path + "/data/hists/hsave.root");
        fsave->ls();
    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
    }
    
    
    cout << "\n\n" << "--------------------------------------------------" << endl;
    cout << "rt::Write() (vector)" << endl;
    cout << "--------------------------------------------------" << "\n" << endl;
    try
    {
        cout << "\nSave the the hist to a ROOT file with Write()" << endl;
        std::map<std::string, rt::TH1Ptr> hist6 = rt::GetMapOfTH1s(file2);
        rt::Write(hist6, path + "/data/hists/hsave.root");
        rt::TFilePtr fsave = rt::OpenRootFile(path + "/data/hists/hsave.root");
        fsave->ls();
    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
    }
    
    
    cout << "\n\n" << "--------------------------------------------------" << endl;
    cout << "rt::copy_file()" << endl;
    cout << "--------------------------------------------------" << "\n" << endl;
    if(rt::copy_file(full_file_name, "/tmp/junk.root"))
    {
        cout << "rt::copy_file() was successful!" << endl;
    }
    else
    {
        cout << "rt::copy_file() failed!" << endl;
    }
    
    cout << "\n\n" << "--------------------------------------------------" << endl;
    cout << "rt::get_list_of_files()" << endl;
    cout << "--------------------------------------------------" << "\n" << endl;
    vector<string> file_list = rt::get_list_of_files(path + "/data");
    if (!file_list.empty())
    {
        cout << "rt::get_list_of_files() shows " << path << " contains:" << endl;
        for (size_t i = 0; i < file_list.size(); i++)
        {
            cout << file_list[i] << endl;
        }
    }
    else
    {
        cout << "rt::get_list_of_files() shows " << path << " is empty!" << endl;
    }
    
    cout << "\n\n" << "--------------------------------------------------" << endl;
    cout << "rt::get_list_of_files()" << endl;
    cout << "--------------------------------------------------" << "\n" << endl;
    cout << "rt::get_list_of_files_from_castor() is untested until access can be established!" << endl;
    
    cout << "\n\n" << "--------------------------------------------------" << endl;
    cout << "rt::basename()" << endl;
    cout << "--------------------------------------------------" << "\n" << endl;
    string basename = rt::basename(full_file_name);
    cout << "rt::basename(" << full_file_name << ") =  " << basename << endl;
    
    cout << "\n\n" << "--------------------------------------------------" << endl;
    cout << "rt::extension()" << endl;
    cout << "--------------------------------------------------" << "\n" << endl;
    string extension = rt::extension(full_file_name);
    cout << "rt::extension(" << full_file_name << ") =  " << extension << endl;
    
    cout << "\n\n" << "--------------------------------------------------" << endl;
    cout << "rt::filename()" << endl;
    cout << "--------------------------------------------------" << "\n" << endl;
    string filename = rt::filename(full_file_name);
    cout << "rt::filename(" << full_file_name << ") =  " << filename << endl;
    
    cout << "\n\n" << "--------------------------------------------------" << endl;
    cout << "rt::dirname()" << endl;
    cout << "--------------------------------------------------" << "\n" << endl;
    string mypath = rt::dirname(full_file_name);
    cout << "rt::dirname(" << full_file_name << ") =  " << mypath << endl;
    
#ifndef __CINT__
    cout << "\n\n" << "--------------------------------------------------" << endl;
    cout << "rt::filter_container()" << endl;
    cout << "--------------------------------------------------" << "\n" << endl;
    std::vector<int> v1;
    v1.push_back(0);
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    print_vector(v1);
#ifndef __RTINT__
    std::vector<int> v2 = rt::filter_container(v1, boost::bind(std::less<int>(), _1, 2)); // x < 2
#else
    std::vector<int> v2 = rt::filter_container(v1, lt2);
#endif //#ifndef __RTINT__
    print_vector(v2);
#endif //!defined(__CINT__) or defined(__MAKECINT__)
    
    cout << "\n\n" << "--------------------------------------------------" << endl;
    cout << "class rt::TH1Container" << endl;
    cout << "--------------------------------------------------" << "\n" << endl;
    
    {
        rt::TH1Container hc;
        cout << "\nmember rt::TH1Container::Add() " << endl;
        TH1* h1           = new TH1D("h1", "h1", 1, 0, 1); h1->SetDirectory(0);
        TH1* h2           = new TH2D("h2", "h2", 1, 0, 1, 1, 0, 1); h2->SetDirectory(0);
        TH1* h2_same_name = new TH2D("h2", "h2", 1, 0, 1, 1, 0, 1); h2->SetDirectory(0);
        try
        {
            hc.Add(h1);
            hc.Add(h2);
            hc.Add(h2);
            hc.Add(h2, true);
            hc.Add(h2_same_name);
            hc.Add(h2_same_name, true);
        }
        catch (std::exception& e)
        {
            cout << e.what() << endl;
        }
    }
    
    {
        rt::TH1Container hc;
        cout << "\nmember rt::TH1Container::Remove() " << endl;
        TH1* h1           = new TH1D("h1", "h1", 1, 0, 1); h1->SetDirectory(0);
        TH1* h2           = new TH2D("h2", "h2", 1, 0, 1, 1, 0, 1); h2->SetDirectory(0);
        try
        {
            hc.Add(h1);
            hc.Add(h2);
            hc.List();
            hc.Remove("h2");
            hc.List();
            hc.Remove("h2");
            hc.List();
        }
        catch (std::exception& e)
        {
            cout << e.what() << endl;
        }
    }
    
    {
        rt::TH1Container hc;
        cout << "\nmember rt::TH1Container::load() " << endl;
        try
        {
            hc.Load(full_file_name);
            hc.List();
        }
        catch (std::exception& e)
        {
            cout << e.what() << endl;
        }
    }
    
    //{
    //    cout << "\nload constructor rt::TH1Container::TH1Container(string, string)" << endl;
    //    try
    //    {
    //        rt::TH1Container hc(full_file_name);
    //        hc.List();
    //    }
    //    catch (std::exception& e)
    //    {
    //        cout << e.what() << endl;
    //    }
    //}
    {
        rt::TH1Container hc1;
        cout << "\nmember rt::TH1Container copy constructor" << endl;
        try
        {
            hc1.Load(full_file_name);
            rt::TH1Container hc2(hc1);
            cout << "hc2:" << endl;
            hc2.List();
            cout << "hc1:" << endl;
            hc1.List();
        }
        catch (std::exception& e)
        {
            cout << e.what() << endl;
        }
    }
    {
        rt::TH1Container hc1;
        cout << "\nmember rt::TH1Container::operator=" << endl;
        try
        {
            hc1.Load(full_file_name);
            rt::TH1Container hc2 = hc1;
            cout << "hc2:" << endl;
            hc2.List();
            cout << "hc1:" << endl;
            hc1.List();
        }
        catch (std::exception& e)
        {
            cout << e.what() << endl;
        }
    }
    
    {
        rt::TH1Container hc1;
        try
        {
            cout << "\nmember rt::TH1Container::Print() " << endl;
            hc1.Load(full_file_name);
            hc1.Print(path + "/data/TH1Container/png", "png");
            hc1.Print(path + "/data/TH1Container/eps", "eps");
            hc1.Print(path + "/data/TH1Container/pdf", "pdf");
            cout << "\nmember rt::TH1Container::write() " << endl;
            hc1.Write(path + "/data/TH1Container/write_test.root");
            rt::TFilePtr f1 = rt::OpenRootFile(path + "/data/TH1Container/write_test.root");
            f1->ls();
        }
        catch (std::exception& e)
        {
            cout << e.what() << endl;
        }
    }
    
    
    
    // finished
    cout << "\n\n" << "--------------------------------------------------" << endl;
    cout << "finished" << endl;
    cout << "--------------------------------------------------" << "\n" << endl;
    return;
}

#ifndef __CINT__
int main()
{
    test_root_tools();
}
#endif
