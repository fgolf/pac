#if !defined(__CINT__) || defined(__MAKECINT__)
#include "rt/MiscTools.hpp"
#include "rt/TH1Overlay.hpp"
#include <iostream>
#include "TSystem.h"
#include "TCanvas.h"
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

void test_constructors()
{
    cout << "testing constructors ..." << endl;

    // some junk hists
    TH1* h1 = new TH1F("h1", "histo from a gaussian", 100, -3, 3); h1->SetLineColor(4); h1->FillRandom("gaus", 10000);
    TH1* h2 = new TH1F("h2", "histo from a gaussian", 100, -3, 3); h2->SetLineColor(2); h2->FillRandom("gaus", 10000);
    
    // default constructor
    TCanvas* c = new TCanvas("c_test_constructors", "TH1Overlay:: Constructor Test", 10,0,600,900); c->Divide(1,2); c->cd(1);
    TH1Overlay* p1 = new TH1Overlay;
    p1->Add(h1);
    p1->Add(h2);
    p1->Draw();

    // constructor
    /*
        TH1Overlay
            (
                const std::string& title, 
                statbox_placement::value_type sb_place = statbox_placement::statbox_placement_default,
                legend_placement::value_type leg_place = legend_placement::legend_placement_default,
                draw_type::value_type draw_type = draw_type::draw_type_default
            );
    */
    c->cd(2);
    TH1Overlay* p2 = new TH1Overlay("non default constructor;x;y", sb::top_middle_right, lg::top_left, dt::normalize);
    p2->Add(h1);
    p2->Add(h2);
    p2->Draw();
}

void test_copying()
{
    cout << "testing copying ..." << endl;

    // some junk hists
    TH1* h1 = new TH1F("h1", "histo from a gaussian", 100, -3, 3); h1->SetLineColor(4); h1->FillRandom("gaus", 10000);
    TH1* h2 = new TH1F("h2", "histo from a gaussian", 100, -3, 3); h2->SetLineColor(2); h2->FillRandom("gaus", 10000);
    
    TCanvas* c = new TCanvas("c_test_copying", "TH1Overlay:: Copy Test", 30,20,600,900); c->Divide(1,2); c->cd(1);
    TH1Overlay* p1 = new TH1Overlay("orig overlay;x;y", sb::top_middle_right, lg::top_left, dt::normalize);
    p1->Add(h1);
    p1->Add(h2);
    p1->Draw();

    TH1Overlay* p2 = new TH1Overlay(*p1); p2->SetTitle("copy overlay");
    c->cd(2);
    p2->Draw();
}

void test_stacked()
{
    cout << "testing stacking ..." << endl;

    // some junk hists
    TH1* h1 = new TH1F("h1", "histo from a gaussian", 100, -3, 3); h1->SetLineColor(4); h1->FillRandom("gaus", 10000);
    TH1* h2 = new TH1F("h2", "histo from a gaussian", 100, -3, 3); h2->SetLineColor(2); h2->FillRandom("gaus", 10000);
    
    TCanvas* c = new TCanvas("c_test_copying", "TH1Overlay:: Copy Test", 30,20,600,900); c->Divide(1,2); c->cd(1);
    TH1Overlay* p1 = new TH1Overlay("orig overlay;x;y", "sb::top_right lg::top_left dt::stack logy");
    //p1->SetLogy(true);
    p1->Add(h1, "red" , kRed);
    p1->Add(h2, "blue", kBlue);
    p1->SetLegendOption("f");
    p1->Draw();
    c->cd(2);
    p1->SetLegendOption("l");
    p1->Draw("dt::norm");
}

void test_overlay()
{
    cout << "\n" << "--------------------------------------------------" << endl;
    cout << "testing class rt::TH1Overlay" << endl;
    cout << "--------------------------------------------------" << "\n" << endl;

    // test contructors
    //test_constructors();

    // test copying
    //test_copying();

    // test destructor
    // test Adding hist
    // test removing hist
    // test drawing 

    // test drawing stacked
    test_stacked();

    // test drawing normalized
    // test drawing profile
    // test legend
    // test statbox
    // test command line draw options
    // test write
    // test print

    // finished
    cout << "\n\n" << "--------------------------------------------------" << endl;
    cout << "finished" << endl;
    cout << "--------------------------------------------------" << "\n" << endl;
    return;
}

#ifndef __CINT__
int main()
{
    test_overlay();
}
#endif
