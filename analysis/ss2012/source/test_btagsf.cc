#include "rt/RootTools.h"
//#include "at/Sample.h"
//#include "at/DileptonChargeType.h"
//#include "at/DileptonHypType.h"
//#include "AnalysisType.h"
#include "SignalRegion.h"
#include "SSB2012.h"
//#include "CTable.h"
#include <string>
#include <fstream>
#include <iostream>
#include "TRandom.h"
//#include <boost/program_options.hpp>

using namespace std;

bool applySF(bool isBTagged, float Btag_SF, float Btag_eff, float random);
double efficiency(int flavor, double jetpt, int uncertainty, int uncertaintyLight);
double scalefactor(int flavor, double jetpt, int uncertainty, int uncertaintyLight);


int main()
try
{
    using namespace ssb;
    using namespace rt;

    const ss::AnalysisType::value_type& anal_type              = ss::AnalysisType::hcp;
    const ss::SignalRegion::value_type& signal_region          = ss::SignalRegion::sr0;
    const ss::SignalRegionType::value_type& signal_region_type = ss::SignalRegionType::inclusive;

    const ss::AnalysisTypeInfo at_info = ss::GetAnalysisTypeInfo(anal_type);
    const std::string srt_name         = ss::GetSignalRegionTypeName(signal_region_type);
    const ss::SignalRegionInfo sr_info = ss::GetSignalRegionInfo(signal_region, anal_type, signal_region_type);

    TH1Container hc;
    hc.Add(new TH1F("h_nbtags"       , "h_nbtags"      , 5, 0.0, 5.0));
    hc.Add(new TH1F("h_nbtags_sf"    , "h_nbtags_sf"   , 5, 0.0, 5.0));
    hc.Add(new TH1F("h_nbtags_sf_up" , "h_nbtags_sf_up", 5, 0.0, 5.0));
    hc.Add(new TH1F("h_nbtags_sf_dn" , "h_nbtags_sf_dn", 5, 0.0, 5.0));
    //hc.Sumw2();

    TChain chain("tree");
    chain.Add("output/ttw_5321.root");

    TRandom random(123456);
    samesignbtag.Init(&chain);
    for (long entry = 0; entry != chain.GetEntries(); entry++)
    {
        // intialize event
        samesignbtag.GetEntry(entry);

        // selection
        if (not is_ss())                                                              {continue;}
        if (njets() < 2)                                                              {continue;}
        if (not ss::PassesSignalRegion(signal_region, anal_type, signal_region_type)) {continue;}

        // loop over jets
        int num_btags_sf    = 0; 
        int num_btags_sf_dn = 0; 
        int num_btags_sf_up = 0; 
        for (size_t jidx = 0; jidx != vjets_p4().size(); jidx++)
        {
            const bool btagged   = vjets_btagged().at(jidx);
            const int jet_flavor = vjets_mcflavor_algo().at(jidx);    
            const float pt       = vjets_p4().at(jidx).pt();

            // apply scale factor
            const float eff     = efficiency (jet_flavor, pt, 0, 0);
            const float sf      = scalefactor(jet_flavor, pt, 0, 0);
            float random_number = random.Uniform(0,1);
            if (applySF(btagged, sf, eff, random_number))
            {
                num_btags_sf++; 
            }

            // uncertainty up
            const float eff_up = efficiency (jet_flavor, pt, 1, 0);
            const float sf_up  = scalefactor(jet_flavor, pt, 1, 0);
            random_number      = random.Uniform(0,1);
            if (applySF(btagged, sf_up, eff_up, random_number))
            {
                num_btags_sf_up++; 
            }

            // uncertainty down
            const float eff_dn = efficiency (jet_flavor, pt, -1, 0);
            const float sf_dn  = scalefactor(jet_flavor, pt, -1, 0);
            random_number      = random.Uniform(0,1);
            if (applySF(btagged, sf_dn, eff_dn, random_number))
            {
                num_btags_sf_dn++; 
            }
        }

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

    // overlay
    hc.SetMarkerSize(1.8);
    hc.SetDrawOption("hist");
    hc["h_nbtags_sf_up"]->SetLineStyle(2);
    hc["h_nbtags_sf_dn"]->SetLineStyle(2);
    rt::TH1Overlay overlay("# btagged-jets;# btags;Events", "lg::top_right sb::off");
    overlay.Add(hc["h_nbtags"      ], "Raw"             , kBlack, 2, 20, 1);
    overlay.Add(hc["h_nbtags_sf"   ], "SF Applied"      , kRed  , 2, 22, 1);
    overlay.Add(hc["h_nbtags_sf_up"], "Uncertainty Up"  , kBlue , 2, 24, 2);
    overlay.Add(hc["h_nbtags_sf_dn"], "Uncertainty Down", kRed  , 2, 26, 2);


    // same output
    rt::SetStyle();
    hc.Print("plots/btagsf", "png"); 
    rt::Print(overlay, "plots/btagsf/p_nbtags", "png");
}
catch (std::exception& e)
{
    cout << e.what() << endl;
}


bool applySF(bool isBTagged, float Btag_SF, float Btag_eff, float random)
{
    bool newBTag = isBTagged;

    if (Btag_SF == 1) return newBTag; //no correction needed 
    if (Btag_SF > 1){                                                            // use this if SF>1

        if( !isBTagged ) {

            float mistagPercent = (1.0 - Btag_SF) / (1.0 - (Btag_SF/Btag_eff) );  //fraction of jets that need to be upgraded      
            if( random < mistagPercent ) newBTag = true;                          //upgrade to tagged

        }

    }else{                                                                    // use this if SF<1

        if( isBTagged && random > Btag_SF ) newBTag = false;                   //downgrade tagged to untagged

    }

    return newBTag;
}


double efficiency(int flavor, double jetpt, int uncertainty, int uncertaintyLight)
{
    if (abs(flavor)==5)      return 0.7195+uncertainty*(0.7665-0.7195);
    else if (abs(flavor)==4) return 0.19249+uncertainty*(0.7665 - 0.7195)/5;
    else                     return (0.0113428+(5.18983e-05*jetpt))+(-2.59881e-08*(jetpt*jetpt))*(1+uncertaintyLight*0.5);
}

double scalefactor(int flavor, double jetpt, int uncertainty, int uncertaintyLight)
{
    float ptmin[] = {30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500.600};
    int binnumber=0;
    for (int i=0;i<sizeof(ptmin)/sizeof(int)-1;i++){
        if(jetpt>ptmin[i] && jetpt<ptmin[i+1]) {
            binnumber=i;
            break;
        }
    }

    if (abs(flavor)==5) {
        double SFb = 0.6981*((1.+(0.414063*jetpt))/(1.+(0.300155*jetpt)));
        double SFb_error[] = {
            0.0295675,
            0.0295095,
            0.0210867,
            0.0219349,
            0.0227033,
            0.0204062,
            0.0185857,
            0.0256242,
            0.0383341,
            0.0409675,
            0.0420284,
            0.0541299,
            0.0578761,
            0.0655432 };
        return SFb+uncertainty*1.5*SFb_error[binnumber];
    }
    if (abs(flavor)==4) {
        double SFb = 0.6981*((1.+(0.414063*jetpt))/(1.+(0.300155*jetpt)));
        double SFb_error[] = {
            0.0295675,
            0.0295095,
            0.0210867,
            0.0219349,
            0.0227033,
            0.0204062,
            0.0185857,
            0.0256242,
            0.0383341,
            0.0409675,
            0.0420284,
            0.0541299,
            0.0578761,
            0.0655432 };
        return SFb+uncertainty*1.5*2*SFb_error[binnumber];   ///---? Where this come from 
    }

    else {
        double SF2012=1.10422 + -0.000523856*jetpt + 1.14251e-06*jetpt*jetpt;
        if(uncertaintyLight==-1){
            double SFmin = ((0.962627+(0.000448344*jetpt))+(-1.25579e-06*(jetpt*jetpt)))+(4.82283e-10*(jetpt*(jetpt*jetpt)));
            return SFmin*SF2012;
        }
        if(uncertaintyLight==1){
            double SFmax = ((1.12368+(0.00124806*jetpt))+(-3.9032e-06*(jetpt*jetpt)))+(2.80083e-09*(jetpt*(jetpt*jetpt)));
            return SFmax*SF2012;
        }
        else{
            double SFmean = ((1.04318+(0.000848162*jetpt))+(-2.5795e-06*(jetpt*jetpt)))+(1.64156e-09*(jetpt*(jetpt*jetpt)));
            return SFmean*SF2012;
        }
    }

}


