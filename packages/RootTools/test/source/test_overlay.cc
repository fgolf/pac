#if !defined(__CINT__) || defined(__MAKECINT__)
#include "rt/MiscTools.h"
#include "rt/TH1Overlay.h"
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
    TH1* h1 = new TH1F("h1", "histo from a gaussian", 100, -3, 3); h1->SetLineColor(4); h1->Sumw2(); h1->FillRandom("gaus", 10000);
    TH1* h2 = new TH1F("h2", "histo from a gaussian", 100, -3, 3); h2->SetLineColor(2); h2->Sumw2(); h2->FillRandom("gaus", 10000);
    TH1* h3 = new TH1F("h3", "histo from a gaussian", 100, -3, 3); h3->SetLineColor(1); h3->Sumw2(); h3->FillRandom("gaus", 15000);
    
    TCanvas* c = new TCanvas("c_test_stacked", "TH1Overlay Stack Test", 1200,900); c->Divide(2,2); c->cd(1);

    // simple overlay
    TH1Overlay* p1 = new TH1Overlay("orig overlay;x;y", "sb::right lg::top_left");
    p1->Add(h1, "red" , kRed);
    p1->Add(h2, "blue", kBlue);
    p1->Add(h3, /*no_stack=*/true, "black", kBlack, 2, 0);
    p1->SetLegendOption("f");
    p1->SetTitle("dt::none");
    p1->Draw("dt::none");

    // test dt::stack_norm
    c->cd(2);
    TH1Overlay* p2 = new TH1Overlay(*p1);
    p2->SetTitle("dt::stack_norm");
    p2->Draw("dt::stack_norm");

    // test dt::norm
    c->cd(3);
    TH1Overlay* p3 = new TH1Overlay(*p1);
    p3->SetTitle("dt::norm");
    p3->Draw("dt::norm");

    // test dt::stack
    c->cd(4);
    TH1Overlay* p4 = new TH1Overlay(*p1);
    p4->SetTitle("dt::stack");
    p4->Draw("dt::stack hist");

    c->Print("test_stacked.png");
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
