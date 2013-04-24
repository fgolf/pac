#include "rt/RootTools.h"
#include "SignalRegion.h"
#include "ScaleFactors.h"
#include "TChain.h"
#include "CTable.h"
#include <utility>
#include <string>

/* float DileptonTagAndProbeScaleFactor */
/* ( */
/*     const int l1_id,  */
/*     const float l1_pt,  */
/*     const float l1_eta,  */
/*     const int l2_id,  */
/*     const float l2_pt,  */
/*     const float l2_eta  */
/* ); */
void LeptonSystematics()
{
    TChain ch_ttjets_os("tree");
    ch_ttjets_os.Add("babies/mc_os/ttjets_os.root");
    ss::SetSignalRegionAliases(ch_ttjets_os, ss::AnalysisType::high_pt, /*do btag sf=*/true);

    TChain ch_data("tree");
    ch_data.Add("babies/hpt/data.root");
    ss::SetSignalRegionAliases(ch_data, ss::AnalysisType::high_pt, /*do btag sf=*/false);

    // denominator
    // this is ttjets where it is forced to decay to dileptons.
    // The # generated will need to have the BR factored out
    // this is done by multiplying by the full sigma and dividing by 
    // the sigma*BR(W --> lv)^2
    const float den = 12119013.0/(0.324*0.324); 

    // passing
    TCut acceptance = "(is_ss && ex_sr30 && lep_is_fromw)*sf_dilepeff*sf_dileptrig";
    ch_ttjets_os.Draw("1>>h_npass", acceptance, "goff");
    TH1F* h_pass = dynamic_cast<TH1F*>(gDirectory->Get("h_npass"));
    const std::pair<float, float> num = rt::IntegralAndError(h_pass);
    ch_ttjets_os.Draw("1>>h_ll_syst", "(is_ss && ex_sr30 && lep_is_fromw)*DileptonTagAndProbeScaleFactorSystUnc(l1_id, l1_pt, l1_eta, l2_id, l2_pt, l2_eta)", "goff");
    TH1F* h_ll_syst = dynamic_cast<TH1F*>(gDirectory->Get("h_ll_syst"));
    const std::pair<float, float> ll_syst = rt::IntegralAndError(h_ll_syst);

    // acceptance
    const float num_value = 100*num.first;
    const float num_error = 100*num.second;
    const float acc_value = num_value/den;
    const float acc_error = num_error/den;
    const float ll_syst_error = ll_syst.first/(h_ll_syst->GetEntries());
    const std::pair<float, float> acc = std::make_pair(acc_value, acc_error); 

    CTable t;
    t.useTitle();
    t.setTitle("TTBar Acceptance");
    t.setTable() (                 "value")
        ("# generated", den               )
        ("# passing"  , rt::pm(num , "1.5"))
        ("acceptance" , rt::pm(acc , "1.5"))
        ("ll syst"    , h_ll_syst->GetEntries())
        ("ll syst"    , ll_syst.first);
   t.print();
}

struct value_t
{
    // construct:
    value_t() : value(0.0f), error(0.0f) {}
    value_t(const float v, const float e) : value(v), error(e) {}

    // methods:
//    std::string str(const std::string& precision = "1.2") const {return rt::pm(value, error, precision);}

    // members:
    float value;
    float error;
};

std::string pm(const value_t& v, const std::string& precision = "1.2f")
{
    const std::string format = Form("%%%s +/- %%%s", precision.c_str(), precision.c_str());
    return Form(format.c_str(), v.value, v.error);
}

// get the integral from histograms
value_t IntegralAndError(TH1* hist)
{
    value_t result(rt::IntegralAndError(hist).first, rt::IntegralAndError(hist).second);
    return result;
}

float GetSyst(const float num_up, const float num_dn, const float num)
{
    const float syst_up = 100*fabs(num_up - num)/num;
    const float syst_dn = 100*fabs(num_dn - num)/num;
    const float syst    = std::max(syst_up, syst_dn);
    return syst;
}

float GetSyst(const float num_up, const float num)
{
    const float syst = 100*(num_up - num)/num;
    return syst;
}

std::string GetSRLabel(ss::SignalRegion::value_type sr)
{
    const unsigned int sr_num = static_cast<unsigned int>(sr);
    return Form((sr < 10 ? "SR0%u_" : "SR%u_"), sr_num);
}

void PrintSystematics(const std::string& filename, const unsigned int sr_num, const float scale_den = 1.0)
{
    const std::string sr = GetSRLabel(static_cast<ss::SignalRegion::value_type>(sr_num)); 

    // acceptance and systematic plots
    rt::TH1Container hc(filename);

    const float den = rt::Integral(hc[sr+"nGenerated"])*(scale_den);
    value_t num     = IntegralAndError(hc[sr+"nPassing"]);
    value_t eff(num.value/den, num.value/den * (rt::Integral(hc[sr+"effErrStat"])/num.value));
/*     eff.error       = eff.value * (rt::Integral(hc[sr+"effErrStat"])/num.value); */
/*     eff.error       = sqrt(eff.value*(1.0 - eff.value)/den); */
    value_t eff_per = eff;
    eff_per.value   *= 100;
    eff_per.error   *= 100;

    // systematics (percentage) 
    const float jer     = GetSyst(rt::Integral(hc[sr+"nJER"      ]), num.value);
    const float jes     = GetSyst(rt::Integral(hc[sr+"nJESUP"    ]), rt::Integral(hc[sr+"nJESDN"    ]), num.value);
    const float jes_up  = GetSyst(rt::Integral(hc[sr+"nJESUP"    ]), num.value);
    const float jes_dn  = GetSyst(rt::Integral(hc[sr+"nJESDN"    ]), num.value);
    const float beff    = GetSyst(rt::Integral(hc[sr+"nBTAUP"    ]), rt::Integral(hc[sr+"nBTADN"    ]), num.value);
    const float beff_up = GetSyst(rt::Integral(hc[sr+"nBTAUP"    ]), num.value);
    const float beff_dn = GetSyst(rt::Integral(hc[sr+"nBTADN"    ]), num.value);
    const float met     = GetSyst(rt::Integral(hc[sr+"nMETUP"    ]), rt::Integral(hc[sr+"nMETDN"    ]), num.value);
    const float met_up  = GetSyst(rt::Integral(hc[sr+"nMETUP"    ]), num.value);
    const float met_dn  = GetSyst(rt::Integral(hc[sr+"nMETDN"    ]), num.value);
    const float lep     = GetSyst(rt::Integral(hc[sr+"nLepEffUP" ]), rt::Integral(hc[sr+"nLepEffDN" ]), num.value);
    const float trig    = GetSyst(rt::Integral(hc[sr+"nTrigEffUP"]), rt::Integral(hc[sr+"nTrigEffDN"]), num.value);
    const float lumi    = 4.4;
    const float pdf     = 2.0;
    const float stat    = eff.error;
    const float total   = sqrt(pow(jes,2) + pow(jer,2) + pow(beff,2) + pow(met,2) + pow(lep,2) + pow(trig,2) + pow(lumi,2) + pow(pdf,2) + pow(stat,2));

    CTable t;
    t.useTitle();
    t.setTitle(Form("TTBar Acceptance SR %d", sr_num));
    t.setTable() (                    "value"  , "rel unc (1 + dx)"  )
        ("# generated"    , int(den)           , "NA"               )
        ("# passing"      , pm(num, "1.0f")    , "NA"               )
        ("acceptance"     , pm(eff, "1.5f")    , "NA"               )
        ("acceptance"     , pm(eff    , "1.2e"), "NA"               )
        ("acceptance (%)" , pm(eff_per, "1.5f"), "NA"               )
        ("JES        (%)" , jes                , 1.0 + 0.01*jes     )
        ("JES+       (%)" , jes_up             , 1.0 + 0.01*jes_up  )
        ("JES-       (%)" , jes_dn             , 1.0 + 0.01*jes_dn  )
        ("JER        (%)" , jer                , 1.0 + 0.01*jer     )
        ("Btag       (%)" , beff               , 1.0 + 0.01*beff    )
        ("Btag+      (%)" , beff_up            , 1.0 + 0.01*beff_up )
        ("Btag-      (%)" , beff_dn            , 1.0 + 0.01*beff_dn )
        ("MET        (%)" , met                , 1.0 + 0.01*met     )
        ("MET+       (%)" , met_up             , 1.0 + 0.01*met_up  )
        ("MET-       (%)" , met_dn             , 1.0 + 0.01*met_dn  )
        ("Trig       (%)" , trig               , 1.0 + 0.01*trig    )
        ("Lep        (%)" , lep                , 1.0 + 0.01*lep     )
        ("Lumi       (%)" , lumi               , 1.0 + 0.01*lumi    )
        ("Pdf        (%)" , pdf                , 1.0 + 0.01*pdf     )
        ("Stat       (%)" , Form("%1.2e", stat), Form("%1.2e", stat))
        ("Total      (%)" , total              , 1.0 + 0.01*total   )
        ;
    t.print();
    cout << endl;
}

void SSTop()
{
    const float scale = 1.0/(0.324*0.324);
    //const float scale = 1.0;
    PrintSystematics("plots/interp/sstop.root", 30, scale);
    PrintSystematics("plots/interp/sstop.root", 31, scale);
    PrintSystematics("plots/interp/sstop.root", 34, scale);
    PrintSystematics("plots/interp/sstop.root", 35, scale);
}

void TTTT()
{
/*     PrintSystematics("plots/interp/tttt.root", 20); */
    PrintSystematics("plots/interp/tttt.root", 21);
    PrintSystematics("plots/interp/tttt.root", 22);
    PrintSystematics("plots/interp/tttt.root", 23);
    PrintSystematics("plots/interp/tttt.root", 24);
    PrintSystematics("plots/interp/tttt.root", 25);
    PrintSystematics("plots/interp/tttt.root", 26);
    PrintSystematics("plots/interp/tttt.root", 27);
    PrintSystematics("plots/interp/tttt.root", 28);
}

void T1TTTT()
{
    PrintSystematics("plots/interp/t1tttt_hpt.root", 20);
    PrintSystematics("plots/interp/t1tttt_hpt.root", 21);
    PrintSystematics("plots/interp/t1tttt_hpt.root", 22);
    PrintSystematics("plots/interp/t1tttt_hpt.root", 23);
    PrintSystematics("plots/interp/t1tttt_hpt.root", 24);
    PrintSystematics("plots/interp/t1tttt_hpt.root", 25);
    PrintSystematics("plots/interp/t1tttt_hpt.root", 26);
    PrintSystematics("plots/interp/t1tttt_hpt.root", 27);
    PrintSystematics("plots/interp/t1tttt_hpt.root", 28);
}
