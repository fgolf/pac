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
    hc_sig.Add(new TH2F("h_sig_8tev"           , Form("Expected Significance (8 TeV) %s"     , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc_sig.Add(new TH2F("h_nsigma_8tev"        , Form("N Sigma (8 TeV) %s"                   , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc_sig.Add(new TH2F("h_sig_best_sr_8tev"   , Form("Best Signal Region (sig) (8 TeV) %s"   , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc_sig.Add(new TH2F("h_nsigma_best_sr_8tev", Form("Best Signal Region (nsigma) (8 TeV) %s", ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));

    hc_sig.Add(new TH2F("h_sig_14tev"           , Form("Expected Significance (14 TeV) %s"     , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc_sig.Add(new TH2F("h_nsigma_14tev"        , Form("N Sigma (14 TeV) %s"                   , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc_sig.Add(new TH2F("h_sig_best_sr_14tev"   , Form("Best Signal Region (sig) (14 TeV) %s"   , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc_sig.Add(new TH2F("h_nsigma_best_sr_14tev", Form("Best Signal Region (nsigma) (14 TeV) %s", ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    //for (size_t i = 0; i != sr_nums.size(); i++)
    //{
    //    const unsigned int sr_num = sr_nums.at(i);
    //    hc_sig.Add(new TH2F(Form("h_num_sr%d"   , sr_num), Form("Number of expected events SR%d %s", sr_num, ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    //    hc_sig.Add(new TH2F(Form("h_sig_sr%d"   , sr_num), Form("Expected Significance SR%d %s"    , sr_num, ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    //    hc_sig.Add(new TH2F(Form("h_nsigma_sr%d", sr_num), Form("N Sigma SR%d %s"                  , sr_num, ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    //}

    // looper over sparms
/*     int xbin = 1; */
/*     int ybin = 1; */
/*     const float sparm0 = 650.0; */
/*     const float sparm1 = 150.0; */
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
            std::pair<float, unsigned int> best_sr_sig_8tev(-99999.0, 0);
            std::pair<float, unsigned int> best_sr_nsigma_8tev(-99999.0, 0);
            std::pair<float, unsigned int> best_sr_sig_14tev(-99999.0, 0);
            std::pair<float, unsigned int> best_sr_nsigma_14tev(-99999.0, 0);

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

                // 8 TeV significane
                // -----------------------------// 

                const float xsec_8tev          = 1000.0 * rt::GetBinContent1D(h_xsec_8tev , sparm0); // fb
                const float lumi_8tev          = 19.5;
                const float n_signal_8tev      = lumi_8tev*xsec_8tev*GetValueFromScanHist(hc_interp[sr+"effNormNice"], sparm0, sparm1);
                const float n_bkgd_8tev        = yi.pred;
                const float unc_bkgd_8tev      = yi.pred_unc;
                const float frac_unc_bkgd_8tev = yi.pred_unc / yi.pred;
                const int n_exp_8tev           = static_cast<int>(n_signal_8tev + n_bkgd_8tev);

                // signficance
                const float sig_8tev    = at::SimpleSignificance(n_signal_8tev, n_bkgd_8tev, unc_bkgd_8tev);
/*                 const float nsigma_8tev = at::NSigma(n_bkgd_8tev, n_exp_8tev, frac_unc_bkgd_8tev); */
                const float nsigma_8tev = 9999.0;
                cout << "n_signal_8tev      = " << n_signal_8tev      << endl;
                cout << "n_bkgd_8tev        = " << n_bkgd_8tev        << endl;
                cout << "unc_bkgd_8tev      = " << unc_bkgd_8tev      << endl;
                cout << "frac_unc_bkgd_8tev = " << frac_unc_bkgd_8tev << endl;
                cout << "sig 8 = " << sig_8tev << "\t" << sr_num << "\t" << sparm0 << "\t" << sparm1 << endl;

                // save the significance
/*                 rt::SetBinContent2D(hc_sig[h_sig_sr_name], sparm0, sparm1, sig     ); */
/*                 rt::SetBinContent2D(hc_sig[h_num_sr_name], sparm0, sparm1, n_signal); */

                // test for the best SR sig (overwrite all results);
                if (best_sr_sig_8tev.first < sig_8tev)
                {
                    best_sr_sig_8tev = std::make_pair(sig_8tev, sr_num);
                }
                rt::SetBinContent2D(hc_sig["h_sig_8tev"        ], sparm0, sparm1, best_sr_sig_8tev.first );
                rt::SetBinContent2D(hc_sig["h_sig_best_sr_8tev"], sparm0, sparm1, best_sr_sig_8tev.second);

                // test for the best SR nsigma (overwrite all results);
                if (best_sr_nsigma_8tev.first < nsigma_8tev)
                {
                    best_sr_nsigma_8tev = std::make_pair(nsigma_8tev, sr_num);
                }
                rt::SetBinContent2D(hc_sig["h_nsigma_8tev"        ], sparm0, sparm1, best_sr_nsigma_8tev.first );
                rt::SetBinContent2D(hc_sig["h_nsigma_best_sr_8tev"], sparm0, sparm1, best_sr_nsigma_8tev.second);

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
/*                 const float scale_susy          = xsec_14tev/xsec_8tev; */
                const float scale_lumi          = lumi_14tev/lumi_8tev;
                const float n_bkgd_14tev        = scale_lumi*(scale_ttbar * yi.fake + scale_ttbar * yi.flip + scale_ttw *yi.rare);
                const float unc_bkgd_14tev      = scale_lumi*sqrt(pow(scale_ttbar * yi.fake_unc,2) + pow(scale_ttbar * yi.flip_unc, 2) + pow(scale_ttw * yi.rare_unc, 2));
                const float frac_unc_bkgd_14tev = unc_bkgd_14tev / n_bkgd_14tev;
                const int n_exp_14tev           = static_cast<int>(n_signal_14tev + n_bkgd_14tev);

                // signficance
                const float sig_14tev    = at::SimpleSignificance(n_signal_14tev, n_bkgd_14tev, unc_bkgd_14tev);
/*                 const float nsigma_14tev = at::NSigma(n_bkgd_14tev, n_exp_14tev, frac_unc_bkgd_14tev); */
                const float nsigma_14tev = 9999.0;
                cout << "n_signal_14tev      = " << n_signal_14tev      << endl;
                cout << "n_bkgd_14tev        = " << n_bkgd_14tev        << endl;
                cout << "unc_bkgd_14tev      = " << unc_bkgd_14tev      << endl;
                cout << "frac_unc_bkgd_14tev = " << frac_unc_bkgd_14tev << endl;
                cout << "scale_ttbar         = " << scale_ttbar         << endl;
                cout << "scale_ttw           = " << scale_ttw           << endl;
                cout << "sig 14 = " << sig_14tev << "\t" << sr_num << "\t" << sparm0 << "\t" << sparm1 << endl;

                // test for the best SR sig (overwrite all results);
                if (best_sr_sig_14tev.first < sig_14tev)
                {
                    best_sr_sig_14tev = std::make_pair(sig_14tev, sr_num);
                }
                rt::SetBinContent2D(hc_sig["h_sig_14tev"        ], sparm0, sparm1, best_sr_sig_14tev.first );
                rt::SetBinContent2D(hc_sig["h_sig_best_sr_14tev"], sparm0, sparm1, best_sr_sig_14tev.second);

                // test for the best SR nsigma (overwrite all results);
                if (best_sr_nsigma_14tev.first < nsigma_14tev)
                {
                    best_sr_nsigma_14tev = std::make_pair(nsigma_14tev, sr_num);
                }
                rt::SetBinContent2D(hc_sig["h_nsigma_14tev"        ], sparm0, sparm1, best_sr_nsigma_14tev.first );
                rt::SetBinContent2D(hc_sig["h_nsigma_best_sr_14tev"], sparm0, sparm1, best_sr_nsigma_14tev.second);

            } // end signal region loop
        } // end ybin loop 
    } // end xbin loop 

    // divide 14/8
    hc_sig.Add(rt::DivideHists(hc_sig["h_sig_14tev"], hc_sig["h_sig_8tev"], "h_sig_ratio", Form("Expected Significance ratio (14/8) %s", ss::GetSignalBinHistLabel(sample).c_str())));

    // write the histogram
    hc_sig.Write(output_file);
}

void PrintExpectedSignificanceHists(const std::string& input_file, const std::string& output_path, const std::string& suffix = "png")
{
    rt::TH1Container hc(input_file);
    hc.SetStats(false);

    gStyle->SetPaintTextFormat("1.0f");
    rt::Print(hc["h_sig_best_sr_8tev" ], output_path, suffix, "h_sig_best_sr_8tev" , "text", false);
    rt::Print(hc["h_sig_best_sr_14tev"], output_path, suffix, "h_sig_best_sr_14tev", "text", false);

    gStyle->SetPaintTextFormat("1.1f");
    rt::Print(hc["h_sig_8tev" ], output_path, suffix, "h_sig_8tev" , "text", false);
    rt::Print(hc["h_sig_14tev"], output_path, suffix, "h_sig_14tev", "text", false);
    rt::Print(hc["h_sig_ratio"], output_path, suffix, "h_sig_ratio", "text", false);

//     hc.SetOption("colz");
//     gStyle->SetPadRightMargin(0.15);
//     gStyle->SetPaintTextFormat("1.1f");
//     rt::mkdir(output_path, /*force=*/true);
//     hc.Print(output_path, suffix);
}
