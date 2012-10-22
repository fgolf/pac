#include "rt/RootTools.h"
#include "at/DileptonHypType.h"
#include "TH1.h"
#include "TCanvas.h"
#include <string>

using namespace at;
using namespace std;

void Print(TH1* hist, const std::string& file_name)
{
    TCanvas c1("c1", "c1", 700, 500);
    hist->SetStats(false);
    hist->GetZaxis()->SetRangeUser(0.8, 1.2);
    hist->Draw("colz");
    c1.Print(Form("plots/outreach/closure_plots/%s.pdf", file_name.c_str()));
    c1.Print(Form("plots/outreach/closure_plots/%s.png", file_name.c_str()));
    c1.Print(Form("plots/outreach/closure_plots/%s.eps", file_name.c_str()));
}


void Outreach2DPlots(const std::string& sample_name)
{
    rt::mkdir("plots/outreach/closure_plots/", true);
    rt::TH1Container hc(Form("plots/outreach/closure/%s.root", sample_name.c_str()));
    Print(hc["h_sparm_ratio"     ], Form("h_outreach_ratio_%s"     , sample_name.c_str()));
    Print(hc["h_sparm_ratio_ht"  ], Form("h_outreach_ratio_ht_%s"  , sample_name.c_str()));
    Print(hc["h_sparm_ratio_met" ], Form("h_outreach_ratio_met_%s" , sample_name.c_str()));
    Print(hc["h_sparm_ratio_btag"], Form("h_outreach_ratio_btag_%s", sample_name.c_str()));

    for (size_t i = 0; i != DileptonHypType::static_size; i++)
    {
        std::string ch = GetDileptonHypTypeName(i);
        Print(hc["h_sparm_ratio_lep_"+ch], Form("h_outreach_ratio_lep_%s_%s" , ch.c_str(), sample_name.c_str()));
        Print(hc["h_sparm_ratio_iso_"+ch], Form("h_outreach_ratio_iso_%s_%s" , ch.c_str(), sample_name.c_str()));
        Print(hc["h_sparm_ratio_id_" +ch], Form("h_outreach_ratio_id_%s_%s"  , ch.c_str(), sample_name.c_str()));
    }
    rt::CopyIndexPhp("plots/outreach/closure_plots");
}

void AllOutreach2DPlots()
{
    Outreach2DPlots("t1tttt");
    Outreach2DPlots("sbottomtop");
    Outreach2DPlots("glustop");
    Outreach2DPlots("glusbottom");
}
