#include <iostream>
#include <iostream>
#include <fstream>
#include <string>

#include "rt/RootTools.h"
#include "at/Sample.h"
#include "at/Significance.h"
#include "SignalBinInfo.h"
#include "SignalRegion.h"

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
void CreateExpectedSignficanceHists
(
    const at::Sample::value_type sample,
    const std::string& interp_file,
    const std::string& yield_file,
    const std::string& output_file,
    const std::string& analysis_type_name = "high_pt",
    const float lumi = 19.5
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
    TH1* h_xsec_8tev = hc_xsec[Form("h_xsec_%s", sample_name.c_str())]; 

    // calculate the significance 
    // ------------------------------------------------------------------------------ //

    // bin info (sample dependent)
    ss::SignalBinInfo bin_info = ss::GetSignalBinInfo(sample);

    // resulting histograms
    rt::TH1Container hc_sig;
    hc_sig.Add(new TH2F("h_sig"    , Form("Expected Significance %s", ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc_sig.Add(new TH2F("h_best_sr", Form("Best Signal Region %s"   , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    for (size_t i = 0; i != sr_nums.size(); i++)
    {
        const unsigned int sr_num = sr_nums.at(i);
        hc_sig.Add(new TH2F(Form("h_sig_sr%d", sr_num), Form("Expected Significance SR%d %s"    , sr_num, ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
        hc_sig.Add(new TH2F(Form("h_num_sr%d", sr_num), Form("Number of expected events SR%d %s", sr_num, ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    }

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

    cout << xmin << "\t" << xmax << endl;
    cout << ymin << "\t" << ymax << endl;

    for (size_t i = 0; i != nbinsx; i++)
    {
        for (size_t j = 0; j != nbinsy; j++)
        {
            const float sparm0 = bin_info.xmin + i*bin_info.xwidth;
            const float sparm1 = bin_info.ymin + j*bin_info.ywidth;
            const float x      = bin_info.xmin + i*bin_info.xwidth;
            const float y      = bin_info.ymin + (j+1)*bin_info.ywidth;
            const float cond   = m*(x - xmin) + ymin;
            const unsigned int xbin = i+1;
            const unsigned int ybin = j+1;

            // boundary conditions
            if (y > cond) {continue;}
            cout << sparm0 << "\t" << sparm1 << "\t" << xbin << "\t" << ybin << endl;

            // store the best SR per sparm
            std::pair<float, unsigned int> best_sr(-99999.0, 0);

            // loop over signal regions
            for (size_t k = 0; k != sr_nums.size(); k++)
            {
                const unsigned int sr_num = sr_nums.at(k);
                const std::string sr = GetSRLabel(sr_num);
                const std::string h_sig_sr_name = Form("h_sig_sr%d", sr_num);
                const std::string h_num_sr_name = Form("h_num_sr%d", sr_num);

                // yield_info object
                yield_info_t yi = *std::find_if(yield_infos.begin(), yield_infos.end(), CompareSR(sr_num));

                const float xsec_8tev = 1000.0 * rt::GetBinContent1D(h_xsec_8tev, sparm0); // fb
                const float n_signal  = lumi*xsec_8tev*GetValueFromScanHist(hc_interp[sr+"effNormNice"], sparm0, sparm1);
                const float n_bkgd    = yi.pred;
                const float unc_bkgd  = yi.pred_unc;
                //cout << n_signal << endl;

                const float sig = at::SimpleSignficance(n_signal, n_bkgd, unc_bkgd);
/*                 cout << "simple significance = " << sig << "\t" << sr_num << "\t" << sparm0 << "\t" << sparm1 << endl; */

                // save the significance
                rt::SetBinContent2D(hc_sig[h_sig_sr_name], sparm0, sparm1, sig     );
                rt::SetBinContent2D(hc_sig[h_num_sr_name], sparm0, sparm1, n_signal);

                // test for the best SR (overwrite all results);
                if (best_sr.first < sig)
                {
                    best_sr = std::make_pair(sig, sr_num);
                }
                rt::SetBinContent2D(hc_sig["h_sig"    ], sparm0, sparm1, best_sr.first );
                rt::SetBinContent2D(hc_sig["h_best_sr"], sparm0, sparm1, best_sr.second);

            } // end signal region loop
        } // end ybin loop 
    } // end xbin loop 

    // write the histogram
    hc_sig.Write(output_file);
}

void PrintExpectedSignficanceHists(const std::string& input_file, const std::string& output_path, const std::string& suffix = "png")
{
    rt::TH1Container hc(input_file);
    gStyle->SetPadRightMargin(0.15);
    gStyle->SetPaintTextFormat("1.0f");
    hc.SetStats(false);
    hc.SetOption("colz");
    hc["h_best_sr"]->SetOption("text");
    rt::mkdir(output_path, /*force=*/true);
    hc.Print(output_path, suffix);
}
