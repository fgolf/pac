#include <iostream>
#include "rt/RootTools.h"
#include "SignalRegion.h"
#include "TStyle.h"
#include "TCanvas.h"

using namespace std;

std::string GetSRLabel(ss::SignalRegion::value_type sr)
{
    const unsigned int sr_num = static_cast<unsigned int>(sr);
    return Form((sr < 10 ? "SR0%u_" : "SR%u_"), sr_num);
}

void PrintPlots
(
    const std::string& plot_name,
    const rt::TH1Container& hc1,
    const rt::TH1Container& hc2,
    const std::string& path,
    const std::string& suffix,
    const std::string& draw_option,
    const std::string& paint_text_option = "1.0f",
    const float zmin = 1.0f,
    const float zmax = -1.0f
)
{
    //TH1* h_diff = rt::SubtractHists(hc1[plot_name], hc2[plot_name], plot_name); 
    //h_diff->Divide(hc2[plot_name]);
    TH1* h_diff = rt::RelativeDiffHists(hc1[plot_name], hc2[plot_name], plot_name); 
    h_diff->Scale(100.0);
    h_diff->SetDirectory(NULL);

    TCanvas c1("c1", "c1", 1600, 1200);
    gStyle->SetPadRightMargin(0.10);
    if (rt::string_contains(draw_option, "colz"))
    {
        gStyle->SetPadRightMargin(0.15);
    }
    {
        gStyle->SetPaintTextFormat(paint_text_option.c_str());
    }
    if (zmax > zmin)
    {
        hc1[plot_name]->GetZaxis()->SetRangeUser(zmin, zmax);
        hc2[plot_name]->GetZaxis()->SetRangeUser(zmin, zmax);
    }
    hc1[plot_name]->Draw(draw_option.c_str()); c1.Print((path + "/" + plot_name + "_v1."   + suffix).c_str());
    hc2[plot_name]->Draw(draw_option.c_str()); c1.Print((path + "/" + plot_name + "_v2."   + suffix).c_str());

    gStyle->SetPaintTextFormat("1.2f");
    h_diff->Draw(draw_option.c_str());
    c1.Print((path + "/" + plot_name + "_diff." + suffix).c_str());
    
    delete h_diff;
}

void CompareSignal(const std::string& file1, const std::string& file2, const std::string& label, const int sr_num = -1, const std::string& draw_option = "text", const std::string& suffix = "eps")
{
    rt::TH1Container hc1(file1);
    rt::TH1Container hc2(file2);
    rt::TH1Container hcd; // diff

    gStyle->SetCanvasDefX(1600);
    gStyle->SetCanvasDefY(1200);

    // no stat boxes
    hc1.SetStats(false);
    hc2.SetStats(false);
    hcd.SetStats(false);

    std::string path = "plots/interp/" + label;
    rt::mkdir(path, true);

    if (sr_num < 0)
    {
        for (size_t nsr = 0; nsr != 29; nsr++)
        {
            // skip blank SRS
            if (nsr == 9 or nsr == 19) {continue;}

            // skip baseline regions
            if (nsr == 0 or nsr == 10 or nsr == 20) {continue;} 

            const string sr = GetSRLabel(static_cast<ss::SignalRegion::value_type>(nsr)); 

            PrintPlots(sr+"nGenerated"     , hc1, hc2, path, suffix, draw_option, "1.0f");
            PrintPlots(sr+"nPassing"       , hc1, hc2, path, suffix, draw_option, "1.1f");
            PrintPlots(sr+"effNormNice"    , hc1, hc2, path, suffix, draw_option, "1.3f", 0.00, 0.12);
            PrintPlots(sr+"effNormNicePerc", hc1, hc2, path, suffix, draw_option, "1.3f", 0.00, 0.12);
            PrintPlots(sr+"effErrJESUP"    , hc1, hc2, path, suffix, draw_option, "1.3f", 0.75, 1.25);
            PrintPlots(sr+"effErrJESDN"    , hc1, hc2, path, suffix, draw_option, "1.3f", 0.75, 1.25);
            PrintPlots(sr+"effErrBTAUP"    , hc1, hc2, path, suffix, draw_option, "1.3f", 0.55, 1.25);
            PrintPlots(sr+"effErrBTADN"    , hc1, hc2, path, suffix, draw_option, "1.3f", 0.55, 1.25);
            PrintPlots(sr+"effErrMETUP"    , hc1, hc2, path, suffix, draw_option, "1.3f", 0.85, 1.15);
            PrintPlots(sr+"effErrMETDN"    , hc1, hc2, path, suffix, draw_option, "1.3f", 0.85, 1.15);
            PrintPlots(sr+"effErrJER"      , hc1, hc2, path, suffix, draw_option, "1.3f", 0.80, 1.20);
/*             PrintPlots(sr+"effErrTot"      , hc1, hc2, path, suffix, draw_option, "1.3f"); */
            PrintPlots(sr+"effErrStat"     , hc1, hc2, path, suffix, draw_option, "1.3f");
        }
    }
    else
    {
        // skip blank SRS
        if (sr_num == 9 or sr_num == 19) {return;}

        // skip baseline regions
        if (sr_num == 0 or sr_num == 10 or sr_num == 20) {return;} 

        const string sr = GetSRLabel(static_cast<ss::SignalRegion::value_type>(sr_num)); 

        PrintPlots(sr+"nGenerated"     , hc1, hc2, path, suffix, draw_option, "1.0f");
        PrintPlots(sr+"nPassing"       , hc1, hc2, path, suffix, draw_option, "1.1f", 0.00, 1600);
        PrintPlots(sr+"effNormNice"    , hc1, hc2, path, suffix, draw_option, "1.3f", 0.00, 0.12);
        PrintPlots(sr+"effNormNicePerc", hc1, hc2, path, suffix, draw_option, "1.3f", 0.00, 0.12);
        PrintPlots(sr+"effErrJESUP"    , hc1, hc2, path, suffix, draw_option, "1.3f", 0.75, 1.25);
        PrintPlots(sr+"effErrJESDN"    , hc1, hc2, path, suffix, draw_option, "1.3f", 0.75, 1.25);
        PrintPlots(sr+"effErrBTAUP"    , hc1, hc2, path, suffix, draw_option, "1.3f", 0.55, 1.25);
        PrintPlots(sr+"effErrBTADN"    , hc1, hc2, path, suffix, draw_option, "1.3f", 0.55, 1.25);
        PrintPlots(sr+"effErrMETUP"    , hc1, hc2, path, suffix, draw_option, "1.3f", 0.85, 1.15);
        PrintPlots(sr+"effErrMETDN"    , hc1, hc2, path, suffix, draw_option, "1.3f", 0.85, 1.15);
        PrintPlots(sr+"effErrJER"      , hc1, hc2, path, suffix, draw_option, "1.3f", 0.80, 1.20);
/*         PrintPlots(sr+"effErrTot"      , hc1, hc2, path, suffix, draw_option, "1.3f"); */
        PrintPlots(sr+"effErrStat"     , hc1, hc2, path, suffix, draw_option, "1.3f");
    }
}
