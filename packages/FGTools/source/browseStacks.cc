#include "browseStacks.h"
#include "TH2.h"
#include "THStack.h"
#include "TRegexp.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TObjArray.h"
#include "TText.h"
#include "TStyle.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Make the stacks and then browse them interactive
// if (makePictures==true), saves all plots to out/stacks.ps
// Also: make out_stacks_xx.png where xx is the page number 
// on the stack.ps file
//
// keep2D=false to skip the annoying 2D histograms
//

void browseStacks(vector<TString> v_samples, vector<Color_t> v_colors, TString outfile, vector<TString> v_legEntries, bool drawLogY, vector<Style_t> v_style, bool plotData) {
		     

    if (v_samples.size() != v_colors.size()) {
        cout << "Number of entries in the vector of samples is not the same as the number of entries in the vector of Color_t" << endl;
        return;
    }
  
    if (v_style.size() !=0 && v_style.size() != v_colors.size()) {
        cout << "Number of entries in the vector of styles is not the same as the number of entries in the vector of samples" << endl;
        return;
    }

    gStyle->SetOptTitle(0);
  
  
    // Find out what the names of the existing histograms are
    // The histogram names are XX_YY_ZZ, where XX is the sample,
    // eg, "tt", YY is the actual name, ZZ is the final state, eg, "ee"
    //exclude data if it is found
    bool keep2D = false;
    TObjArray* myNames = getMyHistosNames(v_samples.at(0).Data(),"ee",keep2D);  
    if(myNames->GetSize() == 0) {
        cout << "could not find the sample at the first point in the vector of samples. Exiting." << endl;
        return;
    }

    // debugging code to see what's in myNames
    std::cout << "Processing the following " << myNames->GetEntries() << " histograms: ";
    for (int i = 0; i < myNames->GetEntries(); i++)
    {
        if (i > 0)
            std::cout << ", ";
        else
            std::cout << "";

        std::cout << myNames->At(i)->GetName();
    }

    std::cout << std::endl;
    std::cout.flush();

    std::cout << "Processing the following " << v_samples.size() << " samples: ";
    for (unsigned int i = 0; i < v_samples.size(); i++)
    {
        if (i > 0)
            std::cout << ", ";
        else
            std::cout << "";

        std::cout << v_samples.at(i).Data();
    }

    std::cout << std::endl;
    std::cout.flush();

    // Now loop over histograms, and make stacks
    TCanvas *c = new TCanvas();  
    c->Divide(2,2);  
    vector<string> v_channel;
    v_channel.push_back("ee");
    v_channel.push_back("mm");
    v_channel.push_back("em");
    v_channel.push_back("all");
    for (int i=0; i<myNames->GetEntries(); i++) {
        for (int i_channel=0; i_channel<4; i_channel++) {
            vector<TH1F*> v_hists;
            TH1F *hdata = NULL;
            
            for(unsigned int i_prefix = 0; i_prefix < v_samples.size(); i_prefix++) {
	
                TString histoName = v_samples.at(i_prefix) + "_" + myNames->At(i)->GetName() + "_" + v_channel.at(i_channel);

                TObject *obj = gDirectory->Get(histoName.Data());
                if (!obj->InheritsFrom(TH1::Class())) 
                    continue;
	
                TH1F *htemp = dynamic_cast<TH1F*>(obj);
                    
                htemp->SetFillColor(v_colors.at(i_prefix));
                htemp->SetLineColor(kBlack);
                TString plot(myNames->At(i)->GetName());
                if(plot.Contains("jet") ||
                   plot.Contains("met") ||
                   plot.Contains("btag") ||
                   plot.Contains("ht") || 
                   plot.Contains("tch") ||
                   plot.Contains("mass"))
                {	  
                    string xtitle;
                    string ytitle;
                    if(plot.Contains("jet")) {
                        xtitle = "Number of jets";
                        ytitle = "Events";
                    } else if(plot.Contains("met")) {
                        xtitle = "#slash{E}_{T} (GeV)";
                        ytitle = "Events/(10 GeV)";
                    } else if(plot.Contains("ht")) {
                        xtitle = "H_{T} (GeV)";
                        ytitle = "Events/(10 GeV)";
                    } else if(plot.Contains("btag" || plot.Contains("tch")) ) {
                        xtitle = "Number of b-tagged jets";
                        ytitle = "Events";
                        // const char *jetbins[4] = {"0", "1", "2", "#geq 3"};
                        // for(int k = 0; k<4; k++) 
                        //     htemp->GetXaxis()->SetBinLabel(k+1, jetbins[k]);
                        // htemp->GetXaxis()->SetLabelSize(0.07);
                    } else if (plot.Contains("wmass")) {
                        xtitle = "M_{jj} (GeV)";
                        ytitle = "Events / (10 GeV)";
                    } else if(plot.Contains("dilMass")) {
                        xtitle = "Dilepton mass [GeV/c^{2}]";
                        ytitle = "Events/(5 GeV/c^{2})";
                    }
                    htemp->GetXaxis()->SetTitle(xtitle.c_str());
                    htemp->GetYaxis()->SetTitle(ytitle.c_str());
                    htemp->GetYaxis()->SetTitleOffset(1.5);
                    htemp->GetXaxis()->SetTitleSize(0.045);
                    htemp->GetYaxis()->SetTitleSize(0.045);	    
                }

                if (v_style.size() > 0) {
                    htemp->SetFillStyle(v_style.at(i_prefix));
                    if(v_samples.at(i_prefix) == "data") {
                        htemp->SetMarkerStyle(v_style.at(i_prefix));
                        htemp->SetMarkerColor(v_colors.at(i_prefix));
                    }
                }

                //don't add the data histogram to the stack
                if (v_samples.at(i_prefix) == "data") {
                    hdata = htemp;
                    continue;
                }

                if (i_prefix==0) {
                    v_hists.push_back(htemp);
                    continue;
                }
	
                htemp->Add(v_hists.back());
                v_hists.push_back(htemp);
            }//prefix loop			
               
            if (hdata != NULL)
                v_hists.push_back(hdata);

            c->cd(i_channel+1);

            //now set the Minimum if we want Log Scale
            float min = 0;
            if(drawLogY && i_channel != 2) 
                min = GetMinimum(v_hists);

            //set the minimum, before we pass the vector of hists to the legend function
            for(vector<TH1F*>::iterator it = v_hists.begin(); it != v_hists.end(); it++) 
                (*it)->SetMinimum(min);	

            TLegend *leg = NULL;
            if (i_channel == 3) {
                leg = makeLegend(v_hists, v_legEntries, drawLogY, TString(myNames->At(i)->GetName()));

            } else {
                float max = 0;
                for(vector<TH1F*>::iterator it = v_hists.begin(); it != v_hists.end(); it++) {
                    if((*it)->GetMaximum() > max)
                        max = (*it)->GetMaximum();
                }

                for(vector<TH1F*>::iterator it = v_hists.begin(); it != v_hists.end(); it++) {
                    if(drawLogY && i_channel != 2 )
                        (*it)->SetMaximum(50*max);
                    else 
                        (*it)->SetMaximum(1.5*max);
                }
            }

            //now we gotta draw, in reverse order
            bool data_is_first_and_skipped = false;
            for(vector<TH1F*>::reverse_iterator it = v_hists.rbegin(); it != v_hists.rend(); it++) {
	
                //do not draw if the histogram is empty...1e-6 should be good enough
                if(drawLogY && (*it)->GetMaximum() < 1e-6)
                    continue;

                if (i_channel == 3) {  
                    float max = 1.1*leg->GetY2();
                    if (drawLogY)
                        max = 5*leg->GetY2();
                    if (v_hists.back()->GetMaximum() < max) 
                        (*it)->SetMaximum(max);
                }	

                if (TString((*it)->GetName()).Contains("data")) {                    
                    hdata = (*it);
                    if (it == v_hists.rbegin() && plotData)
                        (*it)->Draw("Pe");	 
                    else if (it == v_hists.rbegin() && !plotData)
                        data_is_first_and_skipped = true;
                    else if (plotData)
                        (*it)->Draw("Pesame");
                } else {
                    if (it == v_hists.rbegin() || data_is_first_and_skipped) {
                        (*it)->Draw("hist");	 
                        data_is_first_and_skipped = false;
                    }
                    else 	  
                        (*it)->Draw("histsame");
                }
            }
      
            if(hdata != NULL && plotData) {
                hdata->Draw("Pesame");
            }

            gPad->RedrawAxis();	
            if(i_channel == 3)
                leg->Draw();

            //need to draw the first histogram in the stack again, because of the tickmarks
            //now set the Log scale, if desired
            if(drawLogY && i_channel!=2) 
                gPad->SetLogy(1);
      
            TPaveText *pt = getPaveText(v_hists, i_channel);
            pt->Draw();
      
        }//channel loop
        c->Modified();
        c->Update();

        TString tempstring = outfile.ReplaceAll(".root", "");
        if(i != myNames->GetEntries() - 1) 
            c->Print((tempstring + ".eps(").Data());
        else
            c->Print((tempstring + ".eps)").Data());

    }//histos loop

}

double GetMinimum(const vector<TH1F*> &v_hists) {

    TH1* h = NULL; //get the first non-empty histogram 
    for(unsigned int i = 0; v_hists.size(); i++) {
        h = v_hists.at(i);
        if(h->Integral() > 0)
            break;
    }
    if(h->GetMinimum()  < 5e-3)
        return 5e-3;
    else 
        return 
            0.5*(h->GetMinimum());

}
      
  

TLegend* makeLegend(const vector<TH1F*> &v_hists, vector<TString> v_legEntries, bool drawLogY, TString histName) {

    //Prefer to draw the Legend on the right half of the 
    //canvas, so only look at the right half
    int nbins = v_hists.at(0)->GetNbinsX();
    TH1F *hdata = NULL;
    TH1F *hmax = NULL;

    for(vector<TH1F*>::const_reverse_iterator rit = v_hists.rbegin(); rit != v_hists.rend(); rit++) {
        if(TString((*rit)->GetName()).Contains("data")) {
            hdata = *rit;
            break;
        }
    }

    for(vector<TH1F*>::const_reverse_iterator rit = v_hists.rbegin(); rit != v_hists.rend(); rit++) {
        if(TString((*rit)->GetName()).Contains("data")) 
            continue;
        hmax = *rit;
        break;
    }

    // std::cout << "determing x position of legend..." << std::endl;

    //want the legend to be on the right
    //start with the last but 1 bin, and let this be the highX bin
    //skip the last bin 'cause it has the overflow
    float rangeX = hmax->GetXaxis()->GetXmax() - hmax->GetXaxis()->GetXmin() - hmax->GetBinWidth(nbins);
    int highBinX = nbins - 1;
    float highX = hmax->GetBinLowEdge(nbins) - 0.01*rangeX;
    float lowX = hmax->GetXaxis()->GetXmin() + 0.75*rangeX; 
    int lowBinX = hmax->FindBin(lowX);

    // std::cout << "determing y position of legend..." << std::endl;

    //now we need to figure out what the maxY is in the range
    //and set the Y's of the legend to accomodate
    float max = 1e-6;
    float lowY, highY;
    float rangeY = hmax->GetYaxis()->GetXmax() - hmax->GetYaxis()->GetXmin();
    for(int bin = lowBinX; bin < highBinX+1; bin++) {
        if(hmax->GetBinContent(bin) >= hdata->GetBinContent(bin)) {
            if(max < hmax->GetBinContent(bin))
                max = hmax->GetBinContent(bin);
        } else {
            if(max < hdata->GetBinContent(bin))
                max = hdata->GetBinContent(bin);
        }
    }
      
    // std:: cout << "max: " << max << std::endl;
    rangeY = hdata->GetMinimum();
    if(hdata->GetMaximum() > hmax->GetMinimum())
        rangeY = hdata->GetMaximum() - rangeY;
    else 
        rangeY = hmax->GetMaximum() - rangeY;

    if(drawLogY) {
        lowY = 5*max;
        highY = lowY + 10*rangeY;
    } else {
        lowY = 1.2*max;
        highY = lowY + 0.3*rangeY;
    }
  
    //cout << "lowY, highY: "<< lowY << "," <<  highY << endl;
    TLegend *leg;
    if(drawLogY)
        leg = new TLegend(lowX,lowY,highX,highY, "", "br"); 
    else 
        leg = new TLegend(0.7, 0.58, 0.95, 0.92, "", "brNDC");
    if((histName.Contains("nJet") || histName.Contains("bTag")) && drawLogY) {
        int temp = hdata->GetNbinsX();
        leg = new TLegend(hdata->GetNbinsX()-1.1, lowY, temp - 0.05*hdata->GetBinWidth(temp), highY, "", "br");
          
    }

    leg->SetFillColor(kWhite);
    leg->SetBorderSize(0);
    leg->SetFillStyle(1001);    

    if(v_hists.size() != v_legEntries.size()) {
        cout << "the number of entries in the legend vector are not the same as the number"
             << " of entries in the hists vector. Returning a null TLegend. " << endl;
        return NULL;
    }
    vector<TH1F*>::const_reverse_iterator ritH  = v_hists.rbegin();
    vector<TString>::const_reverse_iterator ritE  = v_legEntries.rbegin();

    // std::cout << "filling legend..." << std::endl;

    for(; ritH != v_hists.rend(); ritH++, ritE++) {
        if(*ritE == "Data")
            leg->AddEntry(*ritH, *ritE, "P");
        else
            leg->AddEntry(*ritH, *ritE, "f");
    }




    return leg;
}





TPaveText *getPaveText(const vector<TH1F*> &v_hists, int i_channel) {

    if(v_hists.size() == 0)
        return NULL;
  

    /*
    //all the histograms should have the same Y range
    TH1F *temp = dynamic_cast<TH1F*>(v_hists.at(0)->Clone());
    float lowX, lowY;
    float highX, highY;
    float rangeX = temp->GetXaxis()->GetXmax() - temp->GetXaxis()->GetXmin();
    float rangeY = temp->GetMaximum() - temp->GetMinimum();
    lowX = temp->GetXaxis()->GetXmin() + 0.05*rangeX;
    highX = lowX + 0.2*rangeX;
    lowY = temp->GetMinimum() + 0.85*rangeY;
    highY = temp->GetMinimum() + 0.98*rangeY;
  
    cout << "lowX, highX: "<< lowX << "," <<  highX << endl;
    cout << "lowY, highY: "<< lowY << "," <<  highY << endl;

    TPaveText *pt1 = new TPaveText(lowX, lowY, highX, highY, "br");
    */


    /*
    //used for iso, id plots
    TPaveText *pt1 = new TPaveText(0.3, 0.77, 0.5, 0.90, "brNDC"); 
    if(i_channel == 2) {
    pt1 = new TPaveText(0.62, 0.77, 0.82, 0.90, "brNDC");
    }
    */


    /*
    //for full analysis cut plots
    TPaveText *pt1 = new TPaveText(0.20, 0.77, 0.40, 0.90, "brNDC");
    if(i_channel == 2) {
    pt1 = new TPaveText(0.58, 0.77, 0.78, 0.90, "brNDC"); //used for iso, id plots
    }
    */


    /*
    //for the NJet plot, after the Z veto and the met cut
    TPaveText *pt1 = new TPaveText(0.25, 0.77, 0.45, 0.90, "brNDC");  
    if(i_channel != 3)
    pt1 = new TPaveText(0.62, 0.77, 0.82, 0.90, "brNDC");
    */

  
    //for the MET plot, after the Zveto and the 2jet cut
    TPaveText *pt1 = new TPaveText(0.62, 0.77, 0.82, 0.90, "brNDC");
    if(i_channel == 3)
        pt1 = new TPaveText(0.2, 0.77, 0.4, 0.90, "brNDC");
  

    pt1->SetName("pt1name");
    pt1->SetBorderSize(0);
    pt1->SetFillStyle(0);
  

    TText *blah = pt1->AddText("CMS Preliminary");
    blah->SetTextSize(0.032);
    blah->SetTextAlign(11);
    blah = pt1->AddText("4.7 fb^{-1} at #sqrt{s}=7 TeV");
    blah->SetTextSize(0.032);       
    blah->SetTextAlign(11);

    if(i_channel==0)
        blah = pt1->AddText("Events with ee");
    if(i_channel == 1)
        blah = pt1->AddText("Events with #mu#mu");
    if(i_channel == 2)
        blah = pt1->AddText("Events with e#mu");
    if(i_channel == 3)
        blah = pt1->AddText("Events with ee/#mu#mu/e#mu");  
    blah->SetTextSize(0.032);
    blah->SetTextAlign(11);


    return pt1;
}
