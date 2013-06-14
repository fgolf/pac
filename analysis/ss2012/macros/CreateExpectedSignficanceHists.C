#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "rt/RootTools.h"
#include "at/Sample.h"
#include "at/Significance.h"
#include "SignalBinInfo.h"
#include "SignalRegion.h"
#include "TGraph.h"
#include "TROOT.h"
#include "TList.h"
#include "TLegend.h"
#include "TF1.h"

using namespace std;

struct yield_info_t
{
    // mebers:
    unsigned int sr_num;
    unsigned int yield;
    float pred;
    float pred_unc;
    float fake;
    float fake_unc;
    float rare;
    float rare_unc;
    float flip;
    float flip_unc;

    // methods:
    friend std::istream& operator >> (std::istream& in, yield_info_t& yi);
    friend std::ostream& operator << (std::ostream& os, yield_info_t& yi);
};

std::istream& operator >> (std::istream& in, yield_info_t& yi)
{
    in >> yi.sr_num;
    in >> yi.yield;
    in >> yi.pred;
    in >> yi.pred_unc;
    in >> yi.fake;
    in >> yi.fake_unc;
    in >> yi.rare;
    in >> yi.rare_unc;
    in >> yi.flip;
    in >> yi.flip_unc;
    return in;
};

std::ostream& operator << (std::ostream& os, yield_info_t& yi)
{
    os << yi.sr_num;
    os << "\t" << yi.yield;
    os << "\t" << yi.pred;
    os << "\t" << yi.pred_unc;
    os << "\t" << yi.fake;
    os << "\t" << yi.fake_unc;
    os << "\t" << yi.rare;
    os << "\t" << yi.rare_unc;
    os << "\t" << yi.flip;
    os << "\t" << yi.flip_unc;
    return os;
};

struct CompareSR
{
    CompareSR(const unsigned int sr_num) : m_sr_num(sr_num) {}
    bool operator () (const yield_info_t& yi) {return (yi.sr_num==m_sr_num);}
    const unsigned int m_sr_num;
};

std::string GetSRLabel(const unsigned int sr_num)
{
    return Form((sr_num < 10 ? "SR0%u_" : "SR%u_"), sr_num);
}

float GetValueFromScanHist(TH1* const hist, const float sparm0, const float sparm1)
{
    TH2* const h2 = dynamic_cast<TH2*>(hist);
    const float value = rt::GetBinContent2D(h2, sparm0, sparm1);
    if (rt::is_zero(value)) {return 1.0;}
    else {return value;}
}

// simple class to hold the sign info
struct SRInfo
{
    // construct
    SRInfo()
        : sr(-1)
        , sig(-9999)
        , s(-9999)
        , b(-9999)
        , b_unc(-9999)
    {}
    SRInfo(const unsigned int sr_, const float sig_, const float s_, const float b_, const float db_) 
        : sr(sr_)
        , sig(sig_)
        , s(s_)
        , b(b_)
        , b_unc(db_)
    {}

    // members
    int sr;
    float sig;
    float s;
    float b;
    float b_unc;
};

// compute the significance
// using inclusive yields
void CreateExpectedSignificanceHists
(
    const at::Sample::value_type sample,
    const std::string& interp_file,
    const std::string& yield_file,
    const std::string& output_file
/*     const std::string& analysis_type_name = "high_pt", */
)
{
    // parse the inputs 
    // ------------------------------------------------------------------------------ //

    // get the predictions and yields 
    vector<yield_info_t> yield_infos;
    if (not yield_file.empty() && rt::exists(yield_file))
    {
        std::ifstream fin;
        fin.open(yield_file.c_str(), std::ifstream::in);
        while (fin.good())
        {
            yield_info_t yield_info;
            fin >> yield_info;
            yield_infos.push_back(yield_info);
            //cout << yield_info << endl;
        }
    }
    else
    {
        cout << "[CreateExpectedSignificanceHists] Error -- yield and prediction file not given or does not exist.  Exiting" << endl;
        return;
    }

    // signal regions to process
    std::vector<unsigned int> sr_nums;
    switch (sample)
    {
        case at::Sample::sbottomtop:
            {
                const unsigned int values[] = {11, 12, 13, 14, 15, 16, 17, 18, 21, 22, 23, 24, 25, 26, 27, 28};
                sr_nums.assign(values, values+16);
            }
            break;
        case at::Sample::t1tttt:
            {
                const unsigned int values[] = {21, 22, 23, 24, 25, 26, 27, 28};
                sr_nums.assign(values, values+8);
            }
            break;
        default:
            cout << "[CreateExpectedSignificanceHists] Error -- Sample not supported yet.  Exiting" << endl;
            return;
    }

    // get the signal yield hits
    if (interp_file.empty() || not rt::exists(interp_file))
    {
        cout << "[CreateExpectedSignificanceHists] Error -- interpretation file not given or does not exist.  Exiting" << endl;
        return;
    }
    rt::TH1Container hc_interp(interp_file);

    // get the xsec hist 
    const std::string sample_name = at::GetSampleInfo(sample).name;
    rt::TH1Container hc_xsec("data/xsec/susy_xsec.root");
    rt::TH1Container hc_xsec_14tev("data/xsec/susy_xsec_14tev.root");
    TH1* h_xsec_8tev  = hc_xsec      [Form("h_xsec_%s", sample_name.c_str())]; 
    TH1* h_xsec_14tev = hc_xsec_14tev[Form("h_xsec_%s", sample_name.c_str())]; 

    // calculate the significance 
    // ------------------------------------------------------------------------------ //

    // bin info (sample dependent)
    ss::SignalBinInfo bin_info = ss::GetSignalBinInfo(sample);

    // resulting histograms
    rt::TH1Container hc_sig;
    hc_sig.Add(new TH2F("h_s_8tev"             , Form("Signal yield (8 TeV) %s;significance"          , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc_sig.Add(new TH2F("h_b_8tev"             , Form("Background estimate (8 TeV) %s;significance"   , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc_sig.Add(new TH2F("h_sig_8tev"           , Form("Expected Significance (8 TeV) %s;significance" , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc_sig.Add(new TH2F("h_sig_best_sr_8tev"   , Form("Best Signal Region (sig) (8 TeV) %s;best SR"   , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));

    hc_sig.Add(new TH2F("h_s_8tev_opt"           , Form("Signal yield (8 TeV, optimistic) %s;significance"         , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc_sig.Add(new TH2F("h_b_8tev_opt"           , Form("Background estimate (8 TeV, optimistic) %s;significance"  , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc_sig.Add(new TH2F("h_sig_8tev_opt"         , Form("Expected Significance (8 TeV, optimistic) %s;significance", ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc_sig.Add(new TH2F("h_sig_best_sr_8tev_opt" , Form("Best Signal Region (sig) (8 TeV, optimistic) %s;best SR"  , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));

    hc_sig.Add(new TH2F("h_s_14tev"             , Form("Signal yield (14 TeV) %s;significance"          , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc_sig.Add(new TH2F("h_b_14tev"             , Form("Background estimate (14 TeV) %s;significance"   , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc_sig.Add(new TH2F("h_sig_14tev"           , Form("Expected Significance (14 TeV) %s;significance" , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc_sig.Add(new TH2F("h_sig_best_sr_14tev"   , Form("Best Signal Region (sig) (14 TeV) %s;best SR"   , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));

    hc_sig.Add(new TH2F("h_s_14tev_opt"           , Form("Signal yield (14 TeV, optimistic) %s;significance"         , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc_sig.Add(new TH2F("h_b_14tev_opt"           , Form("Background estimate (14 TeV, optimistic) %s;significance"  , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc_sig.Add(new TH2F("h_sig_14tev_opt"         , Form("Expected Significance (14 TeV, optimistic) %s;significance", ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc_sig.Add(new TH2F("h_sig_best_sr_14tev_opt" , Form("Best Signal Region (sig) (14 TeV, optimistic) %s;best SR"  , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    //for (size_t i = 0; i != sr_nums.size(); i++)
    //{
    //    const unsigned int sr_num = sr_nums.at(i);
    //    hc_sig.Add(new TH2F(Form("h_num_sr%d"   , sr_num), Form("Number of expected events SR%d %s", sr_num, ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    //    hc_sig.Add(new TH2F(Form("h_sig_sr%d"   , sr_num), Form("Expected Significance SR%d %s"    , sr_num, ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    //}

    // looper over sparms
    const size_t nbinsx = bin_info.nbinsx;
    const size_t nbinsy = bin_info.nbinsy;
    const float xmin    = bin_info.xmin;
    const float xmax    = bin_info.xmax;
    const float ymin    = bin_info.ymin + bin_info.ywidth + bin_info.offset;
    const float ymax    = bin_info.ymax + bin_info.ywidth;
    const float m       = (ymax - ymin)/(xmax - xmin);

/*     cout << xmin << "\t" << xmax << endl; */
/*     cout << ymin << "\t" << ymax << endl; */

    for (size_t i = 0; i != nbinsx; i++)
    {
        for (size_t j = 0; j != nbinsy; j++)
        {
            const float sparm0 = bin_info.xmin + i*bin_info.xwidth;
            const float sparm1 = bin_info.ymin + j*bin_info.ywidth;
            const float x      = bin_info.xmin + i*bin_info.xwidth;
            const float y      = bin_info.ymin + (j+1)*bin_info.ywidth;
            const float cond   = m*(x - xmin) + ymin;
/*             const unsigned int xbin = i+1; */
/*             const unsigned int ybin = j+1; */

            // boundary conditions
            if (y > cond) {continue;}
/*             if (not (rt::is_equal(sparm0, 600.0f) && rt::is_equal(sparm1, 150.0f))) {continue;} */
/*             cout << sparm0 << "\t" << sparm1 << "\t" << xbin << "\t" << ybin << endl; */

            // store the best SR per sparm
            SRInfo best_sr_sig_8tev;
            SRInfo best_sr_sig_8tev_optimistic;
            SRInfo best_sr_sig_14tev;
            SRInfo best_sr_sig_14tev_optimistic;

            // loop over signal regions
            for (size_t k = 0; k != sr_nums.size(); k++)
            {
                const unsigned int sr_num = sr_nums.at(k);
                const std::string sr = GetSRLabel(sr_num);
                const std::string h_sig_sr_name = Form("h_sig_sr%d", sr_num);
                const std::string h_num_sr_name = Form("h_num_sr%d", sr_num);
/*                 if (sr_num != 28) {continue;} */

                // yield_info object
                const yield_info_t& yi = *std::find_if(yield_infos.begin(), yield_infos.end(), CompareSR(sr_num));

                // -----------------------------// 
                // 8 TeV significane
                // -----------------------------// 

                const float xsec_8tev          = 1000.0 * rt::GetBinContent1D(h_xsec_8tev, sparm0); // fb
                const float lumi_8tev          = 19.5;
                const float n_signal_8tev      = lumi_8tev*xsec_8tev*GetValueFromScanHist(hc_interp[sr+"effNormNice"], sparm0, sparm1);
                const float n_bkgd_8tev        = yi.pred;
                const float unc_bkgd_8tev      = yi.pred_unc;
                const float frac_unc_bkgd_8tev = yi.pred_unc / yi.pred;
                cout << "xsec_8tev = " << xsec_8tev << endl;

                // signficance
                const float sig_8tev    = at::SimpleSignificance(n_signal_8tev, n_bkgd_8tev, unc_bkgd_8tev);
                cout << "n_signal_8tev      = " << n_signal_8tev      << endl;
                cout << "n_bkgd_8tev        = " << n_bkgd_8tev        << endl;
                cout << "unc_bkgd_8tev      = " << unc_bkgd_8tev      << endl;
                cout << "frac_unc_bkgd_8tev = " << frac_unc_bkgd_8tev << endl;
                cout << "sig 8 = " << sig_8tev << "\t" << sr_num << "\t" << sparm0 << "\t" << sparm1 << endl;

                // test for the best SR sig (overwrite old results);
                if (best_sr_sig_8tev.sig < sig_8tev)
                {
                    best_sr_sig_8tev = SRInfo(sr_num, sig_8tev, n_signal_8tev, n_bkgd_8tev, unc_bkgd_8tev);
                }
                rt::SetBinContent2D(hc_sig["h_sig_8tev"        ], sparm0, sparm1, best_sr_sig_8tev.sig);
                rt::SetBinContent2D(hc_sig["h_sig_best_sr_8tev"], sparm0, sparm1, best_sr_sig_8tev.sr );
                rt::SetBinContent2D(hc_sig["h_s_8tev"          ], sparm0, sparm1, best_sr_sig_8tev.s  );
                rt::SetBinContent2D(hc_sig["h_b_8tev"          ], sparm0, sparm1, best_sr_sig_8tev.b  , best_sr_sig_8tev.b_unc);

                // -----------------------------// 
                // 8 TeV significane -- optimistic scenario
                // -----------------------------// 

                // Rare Prediction Uncertainty:
                // Assume the statistical uncertainty on the rare MC is negligable
                // Assume the systematic uncertainty on the rare MC is improved to 30%
                const float rare_unc_8tev_optimistic = 0.30 * yi.rare;

                // Fake Prediction Uncertainty:
                // Assume the systematic uncertainty on the fake is improved to 40% (from 50%)
                // The uncertainty is dominated by the statistcal term --> scale the total uncertainty by 0.8
                const float fake_unc_8tev_optimistic = 0.80 * yi.fake_unc;

                // scale background unc
                const float unc_bkgd_8tev_optimistic = sqrt(pow(fake_unc_8tev_optimistic,2) + pow(yi.flip_unc, 2) + pow(rare_unc_8tev_optimistic, 2));
                cout << "fake_unc_8tev_optimistic       = " << fake_unc_8tev_optimistic        << endl;
                cout << "rare_unc_8tev_optimistic       = " << rare_unc_8tev_optimistic        << endl;
                cout << "unc_bkgd_8tev_optimistic  = " << unc_bkgd_8tev_optimistic  << endl;

                // significance
                const float sig_8tev_optimistic = at::SimpleSignificance(n_signal_8tev, n_bkgd_8tev, unc_bkgd_8tev_optimistic);

                // test for the best SR sig (overwrite old results);
                if (best_sr_sig_8tev_optimistic.sig < sig_8tev_optimistic)
                {
                    best_sr_sig_8tev_optimistic = SRInfo(sr_num, sig_8tev_optimistic, n_signal_8tev, n_bkgd_8tev, unc_bkgd_8tev_optimistic);
                }
                rt::SetBinContent2D(hc_sig["h_sig_8tev_opt"        ], sparm0, sparm1, best_sr_sig_8tev_optimistic.sig);
                rt::SetBinContent2D(hc_sig["h_sig_best_sr_8tev_opt"], sparm0, sparm1, best_sr_sig_8tev_optimistic.sr );
                rt::SetBinContent2D(hc_sig["h_s_8tev_opt"          ], sparm0, sparm1, best_sr_sig_8tev_optimistic.s  );
                rt::SetBinContent2D(hc_sig["h_b_8tev_opt"          ], sparm0, sparm1, best_sr_sig_8tev_optimistic.b  , best_sr_sig_8tev_optimistic.b_unc);
                cout << "sig 8 = " << sig_8tev_optimistic << "\t" << sr_num << "\t" << sparm0 << "\t" << sparm1 << endl;

                // -----------------------------// 
                // 14 TeV significane
                // -----------------------------// 

                // signal predicctions
                const float xsec_14tev          = 1000.0 * rt::GetBinContent1D(h_xsec_14tev, sparm0); // fb
                const float lumi_14tev          = 300.0;
                const float n_signal_14tev      = lumi_14tev*xsec_14tev*GetValueFromScanHist(hc_interp[sr+"effNormNice"], sparm0, sparm1);

                // scale up background prediction
                // ttbar: https://twiki.cern.ch/twiki/bin/view/CMS/StandardModelCrossSectionForSUSYProjections
                // ttw: http://arxiv.org/pdf/1204.5678v1.pdf table 1 
                // susy: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SUSYCrossSectionsForProjections
                const float xsec_ttbar_8tev     = 1000.0 * 234; // fb
                const float xsec_ttbar_14tev    = 1000.0 * 965; // fb
                const float xsec_ttw_8tev       = 1000.0 * (0.161 + 0.071);  // fb
                const float xsec_ttw_14tev      = 1000.0 * (0.507 + 0.262); // fb
                const float scale_ttbar         = xsec_ttbar_14tev/xsec_ttbar_8tev;
                const float scale_ttw           = xsec_ttw_14tev/xsec_ttw_8tev;
                const float scale_lumi          = lumi_14tev/lumi_8tev;
                const float n_bkgd_14tev        = scale_lumi*(scale_ttbar * yi.fake + scale_ttbar * yi.flip + scale_ttw *yi.rare);
                const float unc_bkgd_14tev      = scale_lumi*sqrt(pow(scale_ttbar * yi.fake_unc,2) + pow(scale_ttbar * yi.flip_unc, 2) + pow(scale_ttw * yi.rare_unc, 2));
                const float frac_unc_bkgd_14tev = unc_bkgd_14tev / n_bkgd_14tev;

                // signficance
                const float sig_14tev    = at::SimpleSignificance(n_signal_14tev, n_bkgd_14tev, unc_bkgd_14tev);
                cout << "n_signal_14tev      = " << n_signal_14tev      << endl;
                cout << "n_bkgd_14tev        = " << n_bkgd_14tev        << endl;
                cout << "unc_bkgd_14tev      = " << unc_bkgd_14tev      << endl;
                cout << "frac_unc_bkgd_14tev = " << frac_unc_bkgd_14tev << endl;
                cout << "scale_ttbar         = " << scale_ttbar         << endl;
                cout << "scale_ttw           = " << scale_ttw           << endl;
                cout << "sig 14 = " << sig_14tev << "\t" << sr_num << "\t" << sparm0 << "\t" << sparm1 << endl;

                // test for the best SR sig (overwrite old results);
                if (best_sr_sig_14tev.sig < sig_14tev)
                {
                    best_sr_sig_14tev = SRInfo(sr_num, sig_14tev, n_signal_14tev, n_bkgd_14tev, unc_bkgd_14tev);
                }
                rt::SetBinContent2D(hc_sig["h_sig_14tev"        ], sparm0, sparm1, best_sr_sig_14tev.sig);
                rt::SetBinContent2D(hc_sig["h_sig_best_sr_14tev"], sparm0, sparm1, best_sr_sig_14tev.sr );
                rt::SetBinContent2D(hc_sig["h_s_14tev"          ], sparm0, sparm1, best_sr_sig_14tev.s  );
                rt::SetBinContent2D(hc_sig["h_b_14tev"          ], sparm0, sparm1, best_sr_sig_14tev.b  , best_sr_sig_14tev.b_unc);

                // -----------------------------// 
                // 14 TeV significane -- optimistic scenario
                // -----------------------------// 

                // Rare Prediction Uncertainty:
                // Assume the statistical uncertainty on the rare MC is negligable
                // Assume the systematic uncertainty on the rare MC is improved to 30%
                const float rare_unc_14tev_optimistic = 0.30 * yi.rare;

                // Fake Prediction Uncertainty:
                // Assume the stastical unc on the FR is constant (time driven by pre-scaled triggers).  Assume its about 15%. 
                // Assume the stastical unc on the SB count is reduced with more statistics (reduced by factor of sqrt(300/19.5) ~ 8).
                // --> call statistical on the fake prediction about 20%.
                // Assume the systematic uncertainty on the fake is improved to 40%
                const float fake_unc_14tev_optimistic = sqrt(0.40*0.40 + 0.20*0.20) * yi.fake;

                // scale background unc
                const float unc_bkgd_14tev_optimistic = scale_lumi*sqrt(pow(scale_ttbar * fake_unc_14tev_optimistic,2) + pow(scale_ttbar * yi.flip_unc, 2) + pow(scale_ttw * rare_unc_14tev_optimistic, 2));
                cout << "fake_unc_optimistic       = " << fake_unc_14tev_optimistic << endl;
                cout << "rare_unc_optimistic       = " << rare_unc_14tev_optimistic << endl;
                cout << "unc_bkgd_14tev_optimistic = " << unc_bkgd_14tev_optimistic << endl;

                // significance
                const float sig_14tev_optimistic = at::SimpleSignificance(n_signal_14tev, n_bkgd_14tev, unc_bkgd_14tev_optimistic);

                // test for the best SR sig (overwrite old results);
                if (best_sr_sig_14tev_optimistic.sig < sig_14tev_optimistic)
                {
                    best_sr_sig_14tev_optimistic = SRInfo(sr_num, sig_14tev_optimistic, n_signal_14tev, n_bkgd_14tev, unc_bkgd_14tev_optimistic);
                }
                rt::SetBinContent2D(hc_sig["h_sig_14tev_opt"        ], sparm0, sparm1, best_sr_sig_14tev_optimistic.sig);
                rt::SetBinContent2D(hc_sig["h_sig_best_sr_14tev_opt"], sparm0, sparm1, best_sr_sig_14tev_optimistic.sr );
                rt::SetBinContent2D(hc_sig["h_s_14tev_opt"          ], sparm0, sparm1, best_sr_sig_14tev_optimistic.s  );
                rt::SetBinContent2D(hc_sig["h_b_14tev_opt"          ], sparm0, sparm1, best_sr_sig_14tev_optimistic.b  , best_sr_sig_14tev_optimistic.b_unc);
                cout << "sig 14 = " << sig_14tev_optimistic << "\t" << sr_num << "\t" << sparm0 << "\t" << sparm1 << "\t" << n_bkgd_14tev << "\t" << unc_bkgd_14tev_optimistic << endl;

            } // end signal region loop
        } // end ybin loop 
    } // end xbin loop 

    // divide 14/8
    hc_sig.Add(rt::DivideHists(hc_sig["h_sig_14tev"    ], hc_sig["h_sig_8tev"], "h_sig_ratio_14tev"    , Form("Expected Significance ratio (14/8) %s;ratio"           , ss::GetSignalBinHistLabel(sample).c_str())));
    hc_sig.Add(rt::DivideHists(hc_sig["h_sig_14tev_opt"], hc_sig["h_sig_8tev"], "h_sig_ratio_14tev_opt", Form("Expected Significance ratio (14 optimistic/8) %s;ratio", ss::GetSignalBinHistLabel(sample).c_str())));
    hc_sig.Add(rt::DivideHists(hc_sig["h_sig_8tev_opt" ], hc_sig["h_sig_8tev"], "h_sig_ratio_8tev_opt" , Form("Expected Significance ratio (8 optimistic/8) %s;ratio" , ss::GetSignalBinHistLabel(sample).c_str())));

    // write the histogram
    hc_sig.Write(output_file);
}

TGraph* GetContourTGraph(TH1* hist, const double level = 5.0)
{
    TCanvas c("c_GetContourTGraph_temp", "c_GetContourTGraph_temp");
    const float min   = hist->GetMinimum();
    const float max   = hist->GetMaximum();
    double contours[] = {min, level, max};
    hist->SetContour(2, contours);
    hist->Draw("CONT Z LIST");
    c.Update();

    TObjArray* array = dynamic_cast<TObjArray*>(gROOT->GetListOfSpecials()->FindObject("contours"));
    TList *list      = dynamic_cast<TList*>(array->First());
    TGraph* curve    = dynamic_cast<TGraph*>(list->First()->Clone()); 

    // reset the contours
    hist->SetContour(static_cast<int>(max-min)+1);
    return curve;
}

void PrintSignificancePlot(TH1* hist, const std::string& output_file_name)
{
    // Draw the hist and curve
    gStyle->SetPadRightMargin(0.15);
    gStyle->SetPaintTextFormat("1.1f");
    TGraph* curve = GetContourTGraph(hist, 5.0);
    TCanvas c("c_PrintSignificancePlot_temp", "c_PrintSignificancePlot_temp");
    hist->Draw("colz");
    curve->SetLineWidth(3);
    curve->Draw("C");

    // Draw the legend
    TLegend leg(0.15, 0.75, 0.5, 0.89);
    leg.AddEntry(curve, "5#sigma signficance", "L");
    leg.SetFillColor(0);  // 0 makes it the background clear on the pad
    leg.SetFillStyle(0);
    leg.SetBorderSize(0);
    leg.Draw();

    c.Print(output_file_name.c_str());
}

void CreateSbottomProjectionHists(const std::string& input_file, const std::string& output_path = "plots/sig/t6ttww", const float max_msbottom = 900)
{
    // ------------------------------------------------- //
    // get the inputs 
    // ------------------------------------------------- //

    // get the xsec hist 
    TH1* h_xsec_14tev = rt::GetHistFromRootFile<TH1>("data/xsec/susy_xsec_14tev.root", "h_xsec_sbottomtop"); 

    // get the efficiency plots
    TH2F* h_eff_perc = rt::GetHistFromRootFile<TH2F>(input_file, "SR28_effNormNicePerc"); 

    // project to get the lowest bin in m_chargino
    // I have to copy the hist because something is wrong with the projectioned hist (not sure why)
    TH1* h_eff_perc_vs_msb_temp = rt::MakeProjectionPlot(h_eff_perc, "x", "h_eff_perc_vs_msb_temp", "h_eff_perc_vs_msb_temp", 150, 175);
    TH1* h_eff_perc_vs_msb      = new TH1F("h_eff_perc_vs_msb", "Signal efficiency percentage vs m_{#tilde{b}} (8 TeV, m_{#tilde{#chi}^{#pm}} = 150 GeV);m_{#tilde{b}} (GeV);efficiency (perc)", 16, 325, 725);
    for (int bin = 1; bin != h_eff_perc_vs_msb->GetNbinsX()+1; bin++)
    {
        h_eff_perc_vs_msb->SetBinContent(bin, h_eff_perc_vs_msb_temp->GetBinContent(bin));
    }

    // ------------------------------------------------- //
    // fit the efficiency to make the projection function 
    // ------------------------------------------------- //

    // fit to a line
    TF1* f_linear = new TF1("f_linear", "x*[0]+[1]", 325, 725);
    f_linear->SetParameters((0.62-0.08)/(700.0-350.0),-0.45); // initial guess
    h_eff_perc_vs_msb->Fit(f_linear, "R+");

    // print the fit parameters
    cout << "The fit: x*p0 + p1:" << endl;
    cout << "p0 = " << f_linear->GetParameter(0) << endl;
    cout << "p1 = " << f_linear->GetParameter(1) << endl;

    // ------------------------------------------------- //
    // calculate the signficance 
    // ------------------------------------------------- //

    // hard code the background for signal region 28
    const float lumi     = 300.0;
    const float n_bkgd   = 115.165;
    const float unc_bkgd = 28.3332;

    // mass points to consider
    vector<float> v_msb;
    for (float msb = 700; msb < max_msbottom+0.001; msb += 25.0)
    {
        v_msb.push_back(msb);
    }

    // histograms to visualize
    TH1* h_eff_proj_vs_msb           = new TH1F("h_eff_proj_vs_msb"          , "Signal efficiency projection vs m_{#tilde{b}} (8 TeV, m_{#tilde{#chi}^{#pm}} = 150 GeV);m_{#tilde{b}} (GeV);efficiency (perc)"   , v_msb.size(), 700, max_msbottom);
    TH1* h_s_proj_14tev_opt_vs_msb   = new TH1F("h_s_proj_14tev_opt_vs_msb"  , "Signal yield projection vs m_{#tilde{b}} (14 TeV, optimistic, m_{#tilde{#chi}^{#pm}} = 150 GeV);m_{#tilde{b}} (GeV);N_{signal}"  , v_msb.size(), 700, max_msbottom);
    TH1* h_sig_proj_14tev_opt_vs_msb = new TH1F("h_sig_proj_14tev_opt_vs_msb", "Significance projection vs m_{#tilde{b}} (14 TeV, optimistic, m_{#tilde{#chi}^{#pm}} = 150 GeV);m_{#tilde{b}} (GeV);significance", v_msb.size(), 700, max_msbottom);

    // calc the significance for each point
    for (size_t i = 0; i != v_msb.size(); i++)
    {
        const int bin        = i+1;
        const float msb      = v_msb.at(i);
        const float xsec     = 1000.0 * rt::GetBinContent1D(h_xsec_14tev, msb); 
        const float eff      = f_linear->Eval(msb)/100.0;  // reported as percentage
        const float n_signal = lumi * xsec * eff;
        const float sig      = at::SimpleSignificance(n_signal, n_bkgd, unc_bkgd);

        // fill hists
        h_eff_proj_vs_msb->SetBinContent(bin, eff*100.0);
        h_s_proj_14tev_opt_vs_msb->SetBinContent(bin, n_signal);
        h_sig_proj_14tev_opt_vs_msb->SetBinContent(bin, sig);
    }

    // ------------------------------------------------- //
    // save and print the output 
    // ------------------------------------------------- //

    const std::string& suffix = "eps"; 
    gStyle->SetPaintTextFormat("1.2f");

    // output
    TCanvas* c1 = new TCanvas("c1", "c1");
    h_eff_perc->SetStats(0);
    h_eff_perc->Draw("text");
    c1->Print(Form("%s/h_eff_perc.%s", output_path.c_str(), suffix.c_str())); 

    rt::SetStatBoxPosition(h_eff_perc_vs_msb, 0.1, 0.65, 0.3, 0.9);
    h_eff_perc_vs_msb->GetYaxis()->SetRangeUser(0.0, 0.8);
    h_eff_perc_vs_msb->SetLineWidth(2);
    h_eff_perc_vs_msb->Draw("text hist");
    f_linear->Draw("same");
    c1->Print(Form("%s/h_eff_perc_vs_msb.%s", output_path.c_str(), suffix.c_str())); 

    h_eff_proj_vs_msb->SetStats(false);
    h_eff_proj_vs_msb->SetLineWidth(2);
    h_eff_proj_vs_msb->GetYaxis()->SetRangeUser(0.6, 1.0);
    h_eff_proj_vs_msb->Draw("text hist");
    c1->Print(Form("%s/h_eff_proj_vs_msb.%s", output_path.c_str(), suffix.c_str())); 

    h_s_proj_14tev_opt_vs_msb->SetStats(false);
    h_s_proj_14tev_opt_vs_msb->SetLineWidth(2);
    h_s_proj_14tev_opt_vs_msb->GetYaxis()->SetRangeUser(0.0, 180.0);
    h_s_proj_14tev_opt_vs_msb->Draw("hist text");
    c1->Print(Form("%s/h_s_proj_14tev_opt_vs_msb.%s", output_path.c_str(), suffix.c_str())); 

    h_sig_proj_14tev_opt_vs_msb->SetStats(false);
    h_sig_proj_14tev_opt_vs_msb->SetLineWidth(2);
    h_sig_proj_14tev_opt_vs_msb->GetYaxis()->SetRangeUser(0.0, 6.0);
    h_sig_proj_14tev_opt_vs_msb->Draw("hist text");
    c1->Print(Form("%s/h_sig_proj_14tev_opt_vs_msb.%s", output_path.c_str(), suffix.c_str())); 

    // write to file
    rt::TH1Container hc;
    hc.Add(h_eff_perc);
    hc.Add(h_eff_perc_vs_msb);
    hc.Add(h_eff_proj_vs_msb);
    hc.Add(h_s_proj_14tev_opt_vs_msb);
    hc.Add(h_sig_proj_14tev_opt_vs_msb);
    hc.Write(Form("%s/t6ttww_msb_proj.root", output_path.c_str()));

    // done
    return;
}

void PrintExpectedSignificanceHists(const std::string& input_file, const std::string& output_path, const std::string& suffix = "png")
{
    rt::TH1Container hc(input_file);
    hc.SetStats(false);
    TCanvas c1("c1", "c1");

    gStyle->SetPaintTextFormat("1.1f");
    rt::Print(hc["h_s_8tev"             ], output_path, suffix, "h_s_8tev_text"             , "text", false);
    rt::Print(hc["h_b_8tev"             ], output_path, suffix, "h_b_8tev_text"             , "texte", false);
    rt::Print(hc["h_sig_8tev"           ], output_path, suffix, "h_sig_8tev_text"           , "text", false);
    rt::Print(hc["h_sig_8tev_opt"       ], output_path, suffix, "h_sig_8tev_opt_text"       , "text", false);
    rt::Print(hc["h_s_8tev_opt"         ], output_path, suffix, "h_s_8tev_opt_text"         , "text", false);
    rt::Print(hc["h_b_8tev_opt"         ], output_path, suffix, "h_b_8tev_opt_text"         , "texte", false);
    gStyle->SetPaintTextFormat("1.1f");
    rt::Print(hc["h_sig_14tev"          ], output_path, suffix, "h_sig_14tev_text"          , "text", false);
    rt::Print(hc["h_s_14tev"            ], output_path, suffix, "h_s_14tev_text"            , "text", false);
    rt::Print(hc["h_b_14tev"            ], output_path, suffix, "h_b_14tev_text"            , "texte", false);
    rt::Print(hc["h_sig_ratio_14tev"    ], output_path, suffix, "h_sig_ratio_14tev_text"    , "text", false);
    rt::Print(hc["h_s_14tev_opt"        ], output_path, suffix, "h_s_14tev_opt_text"        , "text", false);
    rt::Print(hc["h_b_14tev_opt"        ], output_path, suffix, "h_b_14tev_opt_text"        , "texte", false);
    rt::Print(hc["h_sig_14tev_opt"      ], output_path, suffix, "h_sig_14tev_opt_text"      , "text", false);
    rt::Print(hc["h_sig_ratio_14tev_opt"], output_path, suffix, "h_sig_ratio_14tev_opt_text", "text", false);

    gStyle->SetPadRightMargin(0.15);
    gStyle->SetPaintTextFormat("1.0f");
    hc["h_sig_best_sr_8tev"     ]->GetZaxis()->SetRangeUser(17, 29);
    hc["h_sig_best_sr_8tev_opt" ]->GetZaxis()->SetRangeUser(18, 29);
    hc["h_sig_best_sr_14tev"    ]->GetZaxis()->SetRangeUser(23, 29);
    hc["h_sig_best_sr_14tev_opt"]->GetZaxis()->SetRangeUser(23, 29);
    hc["h_sig_best_sr_8tev"     ]->SetContour(29-17);
    hc["h_sig_best_sr_8tev_opt" ]->SetContour(29-18);
    hc["h_sig_best_sr_14tev"    ]->SetContour(29-23);
    hc["h_sig_best_sr_14tev_opt"]->SetContour(29-23);
    rt::Print(hc["h_sig_best_sr_8tev"     ], output_path, suffix, "h_sig_best_sr_8tev"     , "text colz", false);
    rt::Print(hc["h_sig_best_sr_8tev_opt" ], output_path, suffix, "h_sig_best_sr_8tev_opt" , "text colz", false);
    rt::Print(hc["h_sig_best_sr_14tev"    ], output_path, suffix, "h_sig_best_sr_14tev"    , "text colz", false);
    rt::Print(hc["h_sig_best_sr_14tev_opt"], output_path, suffix, "h_sig_best_sr_14tev_opt", "text colz", false);

    rt::Print(hc["h_sig_8tev"           ], output_path, suffix, "h_sig_8tev_col"           , "colz", false);
    rt::Print(hc["h_sig_8tev_opt"       ], output_path, suffix, "h_sig_8tev_opt_col"       , "colz", false);
    rt::Print(hc["h_sig_14tev"          ], output_path, suffix, "h_sig_14tev_col"          , "colz", false);
    rt::Print(hc["h_sig_ratio_14tev"    ], output_path, suffix, "h_sig_ratio_14tev_col"    , "colz", false);
    rt::Print(hc["h_sig_14tev_opt"      ], output_path, suffix, "h_sig_14tev_opt_col"      , "colz", false);
    rt::Print(hc["h_sig_ratio_14tev_opt"], output_path, suffix, "h_sig_ratio_14tev_opt_col", "colz", false);

    // pretty versions
    PrintSignificancePlot(hc["h_sig_8tev"     ], Form("%s/h_sig_8tev_curve.%s"     , output_path.c_str(), suffix.c_str()));
    PrintSignificancePlot(hc["h_sig_8tev_opt" ], Form("%s/h_sig_8tev_opt_curve.%s" , output_path.c_str(), suffix.c_str()));
    PrintSignificancePlot(hc["h_sig_14tev"    ], Form("%s/h_sig_14tev_curve.%s"    , output_path.c_str(), suffix.c_str()));
    PrintSignificancePlot(hc["h_sig_14tev_opt"], Form("%s/h_sig_14tev_opt_curve.%s", output_path.c_str(), suffix.c_str()));

    // summary plot
    TGraph* curve_8tev = GetContourTGraph(hc["h_sig_8tev"]);
    curve_8tev->SetLineWidth(3);
    curve_8tev->SetLineColor(kBlack);
    curve_8tev->SetLineStyle(1);

    TGraph* curve_8tev_opt = GetContourTGraph(hc["h_sig_8tev_opt"]);
    curve_8tev_opt->SetLineWidth(3);
    curve_8tev_opt->SetLineColor(kGreen+2);
    curve_8tev_opt->SetLineStyle(2);

    TGraph* curve_14tev = GetContourTGraph(hc["h_sig_14tev"]);
    curve_14tev->SetLineWidth(3);
    curve_14tev->SetLineColor(kRed);
    curve_14tev->SetLineStyle(3);

    TGraph* curve_14tev_opt = GetContourTGraph(hc["h_sig_14tev_opt"]);
    curve_14tev_opt->SetLineWidth(3);
    curve_14tev_opt->SetLineColor(kBlue);
    curve_14tev_opt->SetLineStyle(4);

    gStyle->SetPadRightMargin(0.10);
    TH1* h_temp = dynamic_cast<TH1*>(hc["h_sig_8tev"]->Clone("h_temp"));
    h_temp->SetTitle("Expected 5#sigma discovery reach");
    h_temp->Draw("axis");
    curve_8tev->Draw("C");
    curve_8tev_opt->Draw("C");
    curve_14tev->Draw("C");
    curve_14tev_opt->Draw("C");

    TLegend leg(0.15, 0.70, 0.5, 0.89);
    leg.AddEntry(curve_8tev     , "20 fb^{-1}, #sqrt{s} = 8 TeV"                , "L");
    leg.AddEntry(curve_8tev_opt , "20 fb^{-1}, #sqrt{s} = 8 TeV (optimistic)"   , "L");
    leg.AddEntry(curve_14tev    , "300 fb^{-1}, #sqrt{s} = 14 TeV (pessimistic)", "L");
    leg.AddEntry(curve_14tev_opt, "300 fb^{-1}, #sqrt{s} = 14 TeV (optimistic)" , "L");
    leg.SetFillColor(0);  // 0 makes it the background clear on the pad
    leg.SetFillStyle(0);
    leg.SetBorderSize(0);
    leg.Draw();
    c1.Print(Form("%s/h_summary_curve.%s", output_path.c_str(), suffix.c_str()));
}

void PrintSbottomTopXsecOverlay()
{
    rt::TH1Container hc_xsec("data/xsec/susy_xsec.root");
    rt::TH1Container hc_xsec_14tev("data/xsec/susy_xsec_14tev.root");
    TH1* h_xsec_8tev  = hc_xsec      ["h_xsec_sbottomtop"]; 
    TH1* h_xsec_14tev = hc_xsec_14tev["h_xsec_sbottomtop"]; 

    TH1* h_xsec_ratio = rt::DivideHists(h_xsec_14tev, h_xsec_8tev, "h_xsec_ratio", "Ratio of Cross Sections for T6ttWW (14 TeV/8TeV);m_{#tilde{b}} (GeV);Ratio");
    h_xsec_ratio->SetLineWidth(2);
    h_xsec_ratio->SetStats(false);
    h_xsec_ratio->Draw("hist");
}

void MassProjection()
{
}
