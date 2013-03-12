#include "rt/RootTools.h"
#include "at/Sample.h"
//#include "at/DileptonChargeType.h"
//#include "at/DileptonHypType.h"
#include "AnalysisType.h"
#include "SignalRegion.h"
#include "at/MCBtagCount.h"
#include "SSB2012.h"
#include "CTable.h"
#include <string>
#include <fstream>
#include <iostream>
#include "TRandom.h"
//#include <boost/program_options.hpp>

using namespace std;

int main()
try
{
    using namespace ssb;
    using namespace rt;
    using namespace at;

    const ss::AnalysisType::value_type& anal_type              = ss::AnalysisType::high_pt;
    const ss::SignalRegion::value_type& signal_region          = ss::SignalRegion::sr0;
    const ss::SignalRegionType::value_type& signal_region_type = ss::SignalRegionType::inclusive;

    const ss::AnalysisTypeInfo at_info = ss::GetAnalysisTypeInfo(anal_type);
    const std::string srt_name         = ss::GetSignalRegionTypeName(signal_region_type);
    const ss::SignalRegionInfo sr_info = ss::GetSignalRegionInfo(signal_region, anal_type, signal_region_type);

    TH1Container hc;
    hc.Add(new TH1F("h_nbtags"       , "h_nbtags"      , 7, 0.0, 7.0));
    hc.Add(new TH1F("h_nbtags_sf"    , "h_nbtags_sf"   , 7, 0.0, 7.0));
    hc.Add(new TH1F("h_nbtags_sf_up" , "h_nbtags_sf_up", 7, 0.0, 7.0));
    hc.Add(new TH1F("h_nbtags_sf_dn" , "h_nbtags_sf_dn", 7, 0.0, 7.0));
    //hc.Sumw2();

    TChain chain("tree");
    const bool is_fastsim = false;
    const at::Sample::value_type sample = Sample::ttw;
    //chain.Add("output/ttw_5323.root");
    //chain.Add("babies/hpt/ttw.root");
    chain.Add("output/ttw_full.root");

    //const bool is_fastsim = true;
    //const at::Sample::value_type sample = Sample::sbottomtop;
    //chain.Add("babies/mc/sbottomtop.root");

    samesignbtag.Init(&chain);
    for (long entry = 0; entry != chain.GetEntries(); entry++)
    {
        // intialize event
        samesignbtag.GetEntry(entry);

        // selection
        if (not is_ss())                                                              {continue;}
        //if (njets() < 2)                                                              {continue;}
        if (not ss::PassesSignalRegion(signal_region, anal_type, signal_region_type)) {continue;}

        // new btag counts 
        int num_btags_sf    = MCBtagCount(vjets_p4(), vjets_btagged(), vjets_mcflavor_algo(), sample, is_fastsim, YieldType::base); 
        int num_btags_sf_dn = MCBtagCount(vjets_p4(), vjets_btagged(), vjets_mcflavor_algo(), sample, is_fastsim, YieldType::down);  
        int num_btags_sf_up = MCBtagCount(vjets_p4(), vjets_btagged(), vjets_mcflavor_algo(), sample, is_fastsim, YieldType::up  );  

        // fill
        hc["h_nbtags"      ]->Fill(nbtags()       );
        hc["h_nbtags_sf"   ]->Fill(num_btags_sf   );
        hc["h_nbtags_sf_up"]->Fill(num_btags_sf_up);
        hc["h_nbtags_sf_dn"]->Fill(num_btags_sf_dn);

    } // end events

    // print uncertainies
    cout << fixed << showpoint << setprecision(3);
    cout << "NBtag_Uncertainty_Up[Nbjet]   = {";
    for(int i=1; i != hc["h_nbtags"]->GetNbinsX(); i++)
    {
        cout << (hc["h_nbtags_sf_up"]->GetBinContent(i) - hc["h_nbtags_sf"]->GetBinContent(i))/hc["h_nbtags_sf"]->GetBinContent(i)<< "% , ";
    }

    cout << "\nNBtag_Uncertainty_Down[Nbjet] = {";
    for(int i=1; i != hc["h_nbtags"]->GetNbinsX(); i++)
    {
        cout << (hc["h_nbtags_sf_dn"]->GetBinContent(i) - hc["h_nbtags_sf"]->GetBinContent(i))/hc["h_nbtags_sf"]->GetBinContent(i)<< "% , ";
    }
    cout<< endl;
    
    CTable t;
    t.useTitle();
    t.setTitle("# btagged-jets");
    t.setTable() (                                            "# 0-btags")
                 ("unscaled"         , hc["h_nbtags"]->GetEntries()      )
                 ("rescaled"         , hc["h_nbtags_sf"]->GetEntries()   )
                 ("uncertainty up"   , hc["h_nbtags_sf_up"]->GetEntries())
                 ("uncertainty down" , hc["h_nbtags_sf_dn"]->GetEntries());
    t.print();

    // overlay
    hc.SetMarkerSize(1.8);
    hc.SetDrawOption("hist");
    hc["h_nbtags_sf_up"]->SetLineStyle(2);
    hc["h_nbtags_sf_dn"]->SetLineStyle(2);
    rt::TH1Overlay overlay("# btagged-jets;# btags;Events", "lg::top sb::right");
    overlay.Add(hc["h_nbtags"      ], "Unscaled"        , kBlack, 2, 20, 1);
    overlay.Add(hc["h_nbtags_sf"   ], "SF Applied"      , kRed  , 2, 22, 1);
    overlay.Add(hc["h_nbtags_sf_up"], "Uncertainty Up"  , kBlue , 2, 24, 2);
    overlay.Add(hc["h_nbtags_sf_dn"], "Uncertainty Down", kRed  , 2, 26, 2);


    // same output
    rt::SetStyle();
    //hc.Write("plots/btagsf_sbottomtop/btagsf_sbottomtop.root"); 
    //hc.Print("plots/btagsf_sbottomtop", "eps"); 
    //rt::Print(overlay, "plots/btagsf_sbottomtop/p_nbtags", "eps");
    hc.Write("plots/btagsf_ttw/btagsf_ttw.root"); 
    hc.Print("plots/btagsf_ttw", "eps"); 
    rt::Print(overlay, "plots/btagsf_ttw/p_nbtags", "eps");
}
catch (std::exception& e)
{
    cout << e.what() << endl;
}
