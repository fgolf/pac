#include "SignalRegion.h"
#include "AnalysisType.h"
#include "at/Sample.h"
#include "rt/RootTools.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct value_t
{
    // construct:
    value_t() : value(0.0f), error(0.0f) {}
    value_t(const float v, const float e) : value(v), error(e) {}

    // methods:
    std::string str(const std::string& precision = "1.2") const {return rt::pm(value, error, precision);}

    // members:
    float value;
    float error;
};

std::string pm(const value_t& v, const std::string& precision = "1.2f")
{
    const std::string format = Form("%%%s +/- %%%s", precision.c_str(), precision.c_str());
    return Form(format.c_str(), v.value, v.error);
}

struct yield_info_t
{
    // construct:
    yield_info_t() : ttg(0,0), ttj(0,0), res(0,0), sf(0,0) {}

    // members:
    value_t ttg;
    value_t ttj;
    value_t res;
    value_t sf;
};

void CreateTTGammaScaleFactor
(
    const ss::AnalysisType::value_type anal_type = ss::AnalysisType::high_pt,
    const ss::SignalRegionType::value_type sr_type = ss::SignalRegionType::exclusive
)
{
    using namespace rt;
    using namespace ss;

    const unsigned int ttg_ngen = 71598;
    const float ttg_weight = 19.5*0.0302522;

    //const unsigned int ttj_ngen = 6923750;
    //const float ttj_weight = 19.5*0.0337967;
    const unsigned int ttj_ngen = 50000;
    const float ttj_weight = 19.5*0.0337967*(6923750/50000);

    // get the baby trees
    // --------------------------------------------------------- //

    const AnalysisTypeInfo at_info = GetAnalysisTypeInfo(anal_type);

    // ttgamma baby
    TChain ch_ttg("tree");
    ch_ttg.Add(Form("babies/mc/ttg_%s.root", at_info.short_name.c_str()));
    rt::PrintFilesFromTChain(ch_ttg);

    // ttgamma baby
    TChain ch_ttj("tree");
    ch_ttj.Add("babies/singlelep/ttjets.root");
    rt::PrintFilesFromTChain(ch_ttj);

    SetSignalRegionAliases(ch_ttg, anal_type, /*do_btag_sf=*/false);
    SetSignalRegionAliases(ch_ttj, anal_type, /*do_btag_sf=*/false);

    // lepton cuts alias (single lepton)
    switch (anal_type)
    {
        case AnalysisType::high_pt: ch_ttj.SetAlias("min_pt", "lep_p4.pt()>20"                                       ); break;
        case AnalysisType::low_pt : ch_ttj.SetAlias("min_pt", "lep_p4.pt()>10"                                       ); break;
        case AnalysisType::vlow_pt: ch_ttj.SetAlias("min_pt", "(abs(lep_pdgid)==11 ? lep_p4.pt()>10 : lep_p4.pt()>5)"); break;
        default: {/*do nothing*/} 
    }

    // selections 
    // --------------------------------------------------------- //

    std::string ss_matched  = "(lep1_is_fromw>=0 && lep2_is_fromw>=0) && (lep1_mc3id*lep2_mc3id>0)";
    std::string lep_sel     = "(lep_is_fromw==1) && (lep_is_num) && (min_pt)";
    std::string is_ss       = "is_ss && lep_pt";
    std::string ss_scale    = "scale1fb*19.5*lep1_sf_lepeff*lep2_sf_lepeff*sf_dileptrig";
    //std::string lep_scale   = "scale1fb*19.5*sf_lepeff*sf_trig";
    std::string lep_scale   = Form("%f*lep_sf_lepeff*lep_sf_trig", ttj_weight);

    vector<yield_info_t> y;
/*     size_t sr_num = 0; */
    for (size_t sr_num = 0; sr_num != 29; sr_num++)
    {
        // skip unused SRs
        if (sr_num == 9 or sr_num == 19) {continue;}

        yield_info_t yield_info;

        // selection
        std::string sr_cut = (sr_type == ss::SignalRegionType::exclusive ? Form("ex_sr%lu", sr_num) : Form("sr%lu", sr_num));

        TCut ttg_ss_sel = Form("(%s && %s && %s)*%s", is_ss.c_str(), ss_matched.c_str(), sr_cut.c_str(), ss_scale.c_str());
        TCut ttj_ss_sel = Form("(%s && %s)*%s", lep_sel.c_str(), sr_cut.c_str(), lep_scale.c_str());
        cout << ttg_ss_sel << endl;
        cout << ttj_ss_sel << endl;

        // ttg yeild
        TH1D h_ttg_yield("h_ttg_yield", "h_ttg_yield", 3, 0, 3); 
        ch_ttg.Draw("1>>h_ttg_yield", ttg_ss_sel, "goff"); 
        //cout << "ttg_raw = " << rt::pm(rt::IntegralAndError(&h_ttg_yield)) << endl;
        h_ttg_yield.SetBinError(2, ttg_weight * rt::GetClopperPearsonUncertainty(static_cast<int>(h_ttg_yield.GetEntries()), ttg_ngen));
        //cout << "ttg_yield = " << rt::pm(rt::IntegralAndError(&h_ttg_yield)) << endl;
        yield_info.ttg.value = rt::IntegralAndError(&h_ttg_yield).first;
        yield_info.ttg.error = rt::IntegralAndError(&h_ttg_yield).second;

        // ttj yeild
        TH1D h_ttj_yield("h_ttj_yield", "h_ttj_yield", 3, 0, 3); 
        ch_ttj.Draw("1>>h_ttj_yield", ttj_ss_sel, "goff"); 
/*         ch_ttj.Scan("lep_is_fromw==1:lep_is_num:min_pt:ex_sr0:lep_sf_lepeff:lep_sf_trig", ttj_ss_sel);  */
        //cout << "ttj_raw = " << rt::pm(rt::IntegralAndError(&h_ttj_yield)) << endl;
        h_ttj_yield.SetBinError(2, ttj_weight * rt::GetClopperPearsonUncertainty(static_cast<int>(h_ttj_yield.GetEntries()), ttj_ngen));
        //cout << "ttj_yield = " << rt::pm(rt::IntegralAndError(&h_ttj_yield)) << endl;
        yield_info.ttj.value = rt::IntegralAndError(&h_ttj_yield).first;
        yield_info.ttj.error = rt::IntegralAndError(&h_ttj_yield).second;

        // rescale
        if (sr_num > 0)
        {
            yield_info.sf = y[0].sf;
        }
        else
        {
            yield_info.sf.value = (yield_info.ttg.value / yield_info.ttj.value);
            yield_info.sf.error = yield_info.sf.value * sqrt(pow(yield_info.ttg.error/yield_info.ttg.error,2) + pow(yield_info.ttg.error/yield_info.ttg.error,2));
        }
        yield_info.res.value = yield_info.ttj.value * yield_info.sf.value;
        yield_info.res.error = yield_info.res.value * sqrt(pow(yield_info.ttj.error/yield_info.ttj.error,2) + pow(yield_info.sf.error/yield_info.sf.error,2));

        // done
        y.push_back(yield_info);
    }

    cout << endl;
    CTable t_result;
    t_result.useTitle();
    t_result.setTitle("ttgamma to ttbar scale factor");
    t_result.setTable() (          "N_ttg_SRx orig", "N_ttg_SRx rescaled", "N_ttbar_SRx",   "N_ttg_SR0", "N_ttbar_SR0", "N_ttg_SR0/N_ttb_0")
                        ("SR 0" ,     pm(y[ 0].ttg),       pm(y[ 0].res), pm(y[ 0].ttj), pm(y[ 0].ttg), pm(y[ 0].ttj), pm(y[ 0].sf, "1.2e"))
                        ("SR 1" ,     pm(y[ 1].ttg),       pm(y[ 1].res), pm(y[ 1].ttj), pm(y[ 1].ttg), pm(y[ 1].ttj), pm(y[ 1].sf, "1.2e"))
                        ("SR 2" ,     pm(y[ 2].ttg),       pm(y[ 2].res), pm(y[ 2].ttj), pm(y[ 2].ttg), pm(y[ 2].ttj), pm(y[ 2].sf, "1.2e"))
                        ("SR 3" ,     pm(y[ 3].ttg),       pm(y[ 3].res), pm(y[ 3].ttj), pm(y[ 3].ttg), pm(y[ 3].ttj), pm(y[ 3].sf, "1.2e"))
                        ("SR 4" ,     pm(y[ 4].ttg),       pm(y[ 4].res), pm(y[ 4].ttj), pm(y[ 4].ttg), pm(y[ 4].ttj), pm(y[ 4].sf, "1.2e"))
                        ("SR 5" ,     pm(y[ 5].ttg),       pm(y[ 5].res), pm(y[ 5].ttj), pm(y[ 5].ttg), pm(y[ 5].ttj), pm(y[ 5].sf, "1.2e"))
                        ("SR 6" ,     pm(y[ 6].ttg),       pm(y[ 6].res), pm(y[ 6].ttj), pm(y[ 6].ttg), pm(y[ 6].ttj), pm(y[ 6].sf, "1.2e"))
                        ("SR 7" ,     pm(y[ 7].ttg),       pm(y[ 7].res), pm(y[ 7].ttj), pm(y[ 7].ttg), pm(y[ 7].ttj), pm(y[ 7].sf, "1.2e"))
                        ("SR 8" ,     pm(y[ 8].ttg),       pm(y[ 8].res), pm(y[ 8].ttj), pm(y[ 8].ttg), pm(y[ 8].ttj), pm(y[ 8].sf, "1.2e"))
                        ("SR 10",     pm(y[10].ttg),       pm(y[10].res), pm(y[10].ttj), pm(y[10].ttg), pm(y[10].ttj), pm(y[10].sf, "1.2e"))
                        ("SR 11",     pm(y[11].ttg),       pm(y[11].res), pm(y[11].ttj), pm(y[11].ttg), pm(y[11].ttj), pm(y[11].sf, "1.2e"))
                        ("SR 12",     pm(y[12].ttg),       pm(y[12].res), pm(y[12].ttj), pm(y[12].ttg), pm(y[12].ttj), pm(y[12].sf, "1.2e"))
                        ("SR 13",     pm(y[13].ttg),       pm(y[13].res), pm(y[13].ttj), pm(y[13].ttg), pm(y[13].ttj), pm(y[13].sf, "1.2e"))
                        ("SR 14",     pm(y[14].ttg),       pm(y[14].res), pm(y[14].ttj), pm(y[14].ttg), pm(y[14].ttj), pm(y[14].sf, "1.2e"))
                        ("SR 15",     pm(y[15].ttg),       pm(y[15].res), pm(y[15].ttj), pm(y[15].ttg), pm(y[15].ttj), pm(y[15].sf, "1.2e"))
                        ("SR 16",     pm(y[16].ttg),       pm(y[16].res), pm(y[16].ttj), pm(y[16].ttg), pm(y[16].ttj), pm(y[16].sf, "1.2e"))
                        ("SR 17",     pm(y[17].ttg),       pm(y[17].res), pm(y[17].ttj), pm(y[17].ttg), pm(y[17].ttj), pm(y[17].sf, "1.2e"))
                        ("SR 18",     pm(y[18].ttg),       pm(y[18].res), pm(y[18].ttj), pm(y[18].ttg), pm(y[18].ttj), pm(y[18].sf, "1.2e"))
                        ("SR 20",     pm(y[20].ttg),       pm(y[20].res), pm(y[20].ttj), pm(y[20].ttg), pm(y[20].ttj), pm(y[20].sf, "1.2e"))
                        ("SR 21",     pm(y[21].ttg),       pm(y[21].res), pm(y[21].ttj), pm(y[21].ttg), pm(y[21].ttj), pm(y[21].sf, "1.2e"))
                        ("SR 22",     pm(y[22].ttg),       pm(y[22].res), pm(y[22].ttj), pm(y[22].ttg), pm(y[22].ttj), pm(y[22].sf, "1.2e"))
                        ("SR 23",     pm(y[23].ttg),       pm(y[23].res), pm(y[23].ttj), pm(y[23].ttg), pm(y[23].ttj), pm(y[23].sf, "1.2e"))
                        ("SR 24",     pm(y[24].ttg),       pm(y[24].res), pm(y[24].ttj), pm(y[24].ttg), pm(y[24].ttj), pm(y[24].sf, "1.2e"))
                        ("SR 25",     pm(y[25].ttg),       pm(y[25].res), pm(y[25].ttj), pm(y[25].ttg), pm(y[25].ttj), pm(y[25].sf, "1.2e"))
                        ("SR 26",     pm(y[26].ttg),       pm(y[26].res), pm(y[26].ttj), pm(y[26].ttg), pm(y[26].ttj), pm(y[26].sf, "1.2e"))
                        ("SR 27",     pm(y[27].ttg),       pm(y[27].res), pm(y[27].ttj), pm(y[27].ttg), pm(y[27].ttj), pm(y[27].sf, "1.2e"))
                        ("SR 28",     pm(y[28].ttg),       pm(y[28].res), pm(y[28].ttj), pm(y[28].ttg), pm(y[28].ttj), pm(y[28].sf, "1.2e"));
    t_result.print();
    cout << endl;
}
