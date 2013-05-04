#include "rt/RootTools.h"
#include "SignalRegion.h"
#include "TChain.h"
#include "CTable.h"
#include <string>
#include <iostream>

using namespace std;

struct value_t
{
    // construct:
    value_t() : value(0.0f), error(0.0f) {}
    value_t(const float v, const float e) : value(v), error(e) {}

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

void WJetsClosureTest(const std::string& filename)
{
    // get the Chain
    //TChain& e1("tree");
    //e1.Add(filename.c_str());
    TChain* chain = rt::CreateTChainFromCommaSeperatedList(filename, "tree");
    TChain& e1 = *chain;
    ss::SetSignalRegionAliases(e1, ss::AnalysisType::high_pt, /*beff_sf=*/false);
    cout << e1.GetEntries() << endl;
/*     e1.GetListOfBranches()->ls(); */
/*     e1.SetAlias("sf_matched", "((lep1_is_fromw>0 && lep2_is_fromw<1) || (lep2_is_fromw>0 && lep1_is_fromw<1))"); */

    // alias
    e1.SetAlias("obs"       , "gen_nleps_with_fromtau==1 && njets>=0 && (lep1_is_fromw>0 && lep1_is_num && lep2_is_num) || (lep2_is_fromw>0 && lep2_is_num && lep1_is_num)");
    e1.SetAlias("sf_matched", "gen_nleps_with_fromtau==1 && njets>=0 && (lep1_is_fromw<1 && lep1_is_fo) || (lep2_is_fromw<1 && lep2_is_fo)");
/*     e1.SetAlias("df_matched", "(lep1_is_fromw<1 && lep2_is_fromw<1)"); */

    // observed
    e1.Draw("1>>h_obs_ee", "ee && obs", "goff");
    TH1F* h_obs_ee = dynamic_cast<TH1F*>(gDirectory->Get("h_obs_ee"));
    value_t obs_ee = IntegralAndError(h_obs_ee); 

    e1.Draw("1>>h_obs_mm", "mm && obs", "goff");
    TH1F* h_obs_mm = dynamic_cast<TH1F*>(gDirectory->Get("h_obs_mm"));
    value_t obs_mm = IntegralAndError(h_obs_mm); 

    e1.Draw("1>>h_obs_em", "em && obs", "goff");
    TH1F* h_obs_em = dynamic_cast<TH1F*>(gDirectory->Get("h_obs_em"));
    value_t obs_em = IntegralAndError(h_obs_em); 

    e1.Draw("1>>h_obs_ll", "obs", "goff");
    TH1F* h_obs_ll = dynamic_cast<TH1F*>(gDirectory->Get("h_obs_ll"));
    value_t obs_ll = IntegralAndError(h_obs_ll); 

    // predicted SF
    e1.Draw("1>>h_sf_ee", "(ee && sf_matched)*sfw", "goff");
    TH1F* h_sf_ee = dynamic_cast<TH1F*>(gDirectory->Get("h_sf_ee"));
    const float sf_ee = h_sf_ee->GetEntries();
    value_t pred_sf_ee = IntegralAndError(h_sf_ee); 

    e1.Draw("1>>h_sf_mm", "(mm && sf_matched)*sfw", "goff");
    TH1F* h_sf_mm = dynamic_cast<TH1F*>(gDirectory->Get("h_sf_mm"));
    const float sf_mm = h_sf_mm->GetEntries();
    value_t pred_sf_mm = IntegralAndError(h_sf_mm); 

    e1.Draw("1>>h_sf_em", "(em && sf_matched)*sfw", "goff");
    TH1F* h_sf_em = dynamic_cast<TH1F*>(gDirectory->Get("h_sf_em"));
    const float sf_em = h_sf_em->GetEntries();
    value_t pred_sf_em = IntegralAndError(h_sf_em); 

    e1.Draw("1>>h_sf_ll", "(sf_matched)*sfw", "goff");
    TH1F* h_sf_ll = dynamic_cast<TH1F*>(gDirectory->Get("h_sf_ll"));
    const float sf_ll = h_sf_ll->GetEntries();
    value_t pred_sf_ll = IntegralAndError(h_sf_ll); 

/*     // predicted DF */
/*     e1.Draw("1>>h_df_ee", "(is_df && ee && df_matched)*dfw", "goff"); */
/*     TH1F* h_df_ee = dynamic_cast<TH1F*>(gDirectory->Get("h_df_ee")); */
/*     value_t pred_df_ee = IntegralAndError(h_df_ee);  */
/*  */
/*     e1.Draw("1>>h_df_mm", "(is_df && mm && df_matched)*dfw", "goff"); */
/*     TH1F* h_df_mm = dynamic_cast<TH1F*>(gDirectory->Get("h_df_mm")); */
/*     value_t pred_df_mm = IntegralAndError(h_df_mm);  */
/*  */
/*     e1.Draw("1>>h_df_em", "(is_df && em && df_matched)*dfw", "goff"); */
/*     TH1F* h_df_em = dynamic_cast<TH1F*>(gDirectory->Get("h_df_em")); */
/*     value_t pred_df_em = IntegralAndError(h_df_em);  */
/*  */
/*     e1.Draw("1>>h_df_ll", "(is_df && df_matched)*dfw", "goff"); */
/*     TH1F* h_df_ll = dynamic_cast<TH1F*>(gDirectory->Get("h_df_ll")); */
/*     value_t pred_df_ll = IntegralAndError(h_df_ll);  */

    // ratio
    // (p)/o
    cout << "pred ee:\t" << pm(pred_sf_ee) << endl;
    cout << "pred mm:\t" << pm(pred_sf_mm) << endl;
    cout << "pred em:\t" << pm(pred_sf_em) << endl;
    const value_t ratio_ee(pred_sf_ee.value/obs_ee.value, (pred_sf_ee.value/obs_ee.value) * sqrt(pow(pred_sf_ee.error/pred_sf_ee.value, 2) + pow(obs_ee.error/obs_ee.value, 2)));
    const value_t ratio_mm(pred_sf_mm.value/obs_mm.value, (pred_sf_mm.value/obs_mm.value) * sqrt(pow(pred_sf_mm.error/pred_sf_mm.value, 2) + pow(obs_mm.error/obs_mm.value, 2)));
    const value_t ratio_em(pred_sf_em.value/obs_em.value, (pred_sf_em.value/obs_em.value) * sqrt(pow(pred_sf_em.error/pred_sf_em.value, 2) + pow(obs_em.error/obs_em.value, 2)));
    const value_t ratio_ll(pred_sf_ll.value/obs_ll.value, (pred_sf_ll.value/obs_ll.value) * sqrt(pow(pred_sf_ll.error/pred_sf_ll.value, 2) + pow(obs_ll.error/obs_ll.value, 2)));

    // relative difference
    // (p - o)/p : error = d(1 - o/p) = d(o/p)
    const value_t rdiff_ee((pred_sf_ee.value - obs_ee.value)/obs_ee.value, (obs_ee.value/pred_sf_ee.value) * sqrt(pow(pred_sf_ee.error/pred_sf_ee.value, 2) + pow(obs_ee.error/obs_ee.value, 2)));
    const value_t rdiff_mm((pred_sf_mm.value - obs_mm.value)/obs_mm.value, (obs_mm.value/pred_sf_mm.value) * sqrt(pow(pred_sf_mm.error/pred_sf_mm.value, 2) + pow(obs_mm.error/obs_mm.value, 2)));
    const value_t rdiff_em((pred_sf_em.value - obs_em.value)/obs_em.value, (obs_em.value/pred_sf_em.value) * sqrt(pow(pred_sf_em.error/pred_sf_em.value, 2) + pow(obs_em.error/obs_em.value, 2)));
    const value_t rdiff_ll((pred_sf_ll.value - obs_ll.value)/obs_ll.value, (obs_ll.value/pred_sf_ll.value) * sqrt(pow(pred_sf_ll.error/pred_sf_ll.value, 2) + pow(obs_ll.error/obs_ll.value, 2)));

    // print results
    CTable t;
    t.setTitle("W+jets closure test results");
    t.useTitle();
    t.setTable()
        (                         "ee" , "mm"              , "em"              ,              "ll")
        ("FO count", (int)sf_ee        , (int)sf_mm        , (int)sf_em        , (int)sf_ll       )
        ("pred"    , pm(pred_sf_ee)    , pm(pred_sf_mm)    , pm(pred_sf_em)    , pm(pred_sf_ll)   )
        ("obs"     , (int)obs_ee.value , (int)obs_mm.value , (int)obs_em.value , (int)obs_ll.value)
        ("p/o"     , pm(ratio_ee)      , pm(ratio_mm)      , pm(ratio_em)      , pm(ratio_ll)     )
        ("(p-o)/p" , pm(rdiff_ee)      , pm(rdiff_mm)      , pm(rdiff_em)      , pm(rdiff_ll)     )
        ;
    t.print();

    // cleanup
    delete chain;
}
