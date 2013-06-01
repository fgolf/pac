#include <iostream>
#include <fstream>
#include <string>

#include "rt/RootTools.h"
#include "at/Sample.h"
#include "SignalBinInfo.h"
#include "/usr/local/lands/03.06.07/test/fitRvsCLs.C"

using namespace std;
using namespace ss;

struct LimitInfo
{
    float sparm0;
    float sparm1;
    double xsec;
    double xsec_err;
    double obs;
    double obs_err;
    double exp;
    double exp_1sigma_up;
    double exp_1sigma_dn;
};

// sort by sparm0 and then sparm1
bool operator < (const LimitInfo& lhs, const LimitInfo& rhs)
{
    if (lhs.sparm0 < rhs.sparm0) {return true; }
    if (lhs.sparm0 > rhs.sparm0) {return false;}
    if (lhs.sparm1 < rhs.sparm1) {return true; }
    else {return false;}
}

ostream& operator << (ostream& os, const LimitInfo& limit_info)
{
    os << Form("%1.0f\t%1.0f\t%1.6f\t%1.6f\t%1.3f\t%1.3f\t%1.3f\t%1.3f\t%1.3f",
        limit_info.sparm0,
        limit_info.sparm1,
        limit_info.xsec,
        limit_info.xsec_err,
        limit_info.obs,
        limit_info.obs_err,
        limit_info.exp,
        limit_info.exp_1sigma_up,
        limit_info.exp_1sigma_dn);
    return os;
}

std::istream& operator >> (std::istream& in, LimitInfo& limit_info)
{
    in >> limit_info.sparm0;
    in >> limit_info.sparm1;
    in >> limit_info.xsec;
    in >> limit_info.xsec_err;
    in >> limit_info.obs;
    in >> limit_info.obs_err;
    in >> limit_info.exp;
    in >> limit_info.exp_1sigma_up;
    in >> limit_info.exp_1sigma_dn;
    return in;
};


struct SelectBySparms
{
    SelectBySparms(const float sparm0, const float sparm1) 
        : m_sparm0(sparm0)
        , m_sparm1(sparm1)
    {}
    const float m_sparm0;
    const float m_sparm1;

    bool operator () (const LimitInfo& limit_info) const
    {
        return (rt::is_equal(limit_info.sparm0, m_sparm0) && rt::is_equal(limit_info.sparm1, m_sparm1));
    }
};

void CreateLimitTextFile
(
    const at::Sample::value_type sample,
    const std::string& input_file_path,
    const std::string& input_file_stem,
    const std::string& output_file = ""
)
{
    // store the lines
    vector<LimitInfo> limit_infos;

    SignalBinInfo bin_info = GetSignalBinInfo(sample);
    TH1F* h_xsec = rt::GetHistFromRootFile<TH1F>("data/xsec/susy_xsec.root", Form("h_xsec_%s", at::GetSampleInfo(sample).name.c_str()));

    const size_t nbinsx = bin_info.nbinsx;
    const size_t nbinsy = bin_info.nbinsy;
    const float xmin    = bin_info.xmin;
    const float xmax    = bin_info.xmax;
    const float ymin    = bin_info.ymin + bin_info.ywidth + bin_info.offset;
    const float ymax    = bin_info.ymax + bin_info.ywidth;
    const float m       = (ymax - ymin)/(xmax - xmin);

    for (size_t xbin = 0; xbin != nbinsx; xbin++)
    {
        for (size_t ybin = 0; ybin != nbinsy; ybin++)
        {
            const float sparm0 = bin_info.xmin + xbin*bin_info.xwidth;
            const float sparm1 = bin_info.ymin + ybin*bin_info.ywidth;
            const float x      = bin_info.xmin + xbin*bin_info.xwidth;
            const float y      = bin_info.ymin + (ybin+1)*bin_info.ywidth;
            const float cond   = m*(x - xmin) + ymin;

            // store the output
            LimitInfo limit_info;
            limit_info.sparm0        = sparm0;
            limit_info.sparm1        = sparm1;
            limit_info.xsec          = 1000.0 * rt::GetBinContent1D(h_xsec, sparm0); // fb
            limit_info.xsec_err      = 1000.0 * rt::GetBinError1D(h_xsec, sparm0);   // fb
            limit_info.obs           = 0.0;
            limit_info.obs_err       = 0.0;
            limit_info.exp           = 0.0;
            limit_info.exp_1sigma_up = 0.0;
            limit_info.exp_1sigma_dn = 0.0;

            // boundary conditions
            if (y > cond) {continue;}

            // extract file to process
/*             const float sparm0 = 800; */
/*             const float sparm1 = 0; */
            const string file_stem      = Form("%s_p%1.0f_p%1.0f", input_file_stem.c_str(), sparm0, sparm1);
            const string root_file_name = Form("%s/%s_m2lnQ.root", input_file_path.c_str(), file_stem.c_str());
            //const string root_file_name = "cards/t1tttt_mglu800_mlsp0_m2lnQ.root"; 

            // check that file exists
            if (not rt::exists(root_file_name))
            {
                cout << "File " << root_file_name << " does not exist -- filling with bogus values." << endl;
                limit_infos.push_back(limit_info);
                continue;
            }

            cout << "extracting limits for " << root_file_name << endl;

            // run the limit code
            rt::mkdir("limits/tmp", /*force=*/true);
            string plot_name = Form("limits/tmp/%s_plots", file_stem.c_str());
            string band_name = Form("limits/tmp/%s_bands", file_stem.c_str());
            run(root_file_name.c_str(), plot_name.c_str(), band_name.c_str());

            // extract limits
            TChain chain("T");
            chain.Add(Form("%s.root", band_name.c_str()));

            // branches
            TBranch* b_obs     = chain.GetBranch("limit")   ; b_obs->SetAddress(&limit_info.obs)           ;  // observed limit
            TBranch* b_obs_err = chain.GetBranch("limitErr"); b_obs_err->SetAddress(&limit_info.obs_err)   ;  // observed limit error
            TBranch* b_rmedian = chain.GetBranch("rmedian") ; b_rmedian->SetAddress(&limit_info.exp)       ;  // expected median limit
            TBranch* b_rm1s    = chain.GetBranch("rm1s")    ; b_rm1s->SetAddress(&limit_info.exp_1sigma_up);  // expected median limit -1s 
            TBranch* b_rp1s    = chain.GetBranch("rp1s")    ; b_rp1s->SetAddress(&limit_info.exp_1sigma_dn);  // expected median limit +1s 

            // only one entry
            chain.GetEntry(0);

            // save the limit for this mass point
            limit_infos.push_back(limit_info);

            // cleanup files
            if (rt::exists("limits/tmp"))
            {
                rt::remove("limits/tmp", /*force=*/true);
            }

            // done with this sparm value
        }
    }

    // output the lines
    std::sort(limit_infos.begin(), limit_infos.end());

    // print it
    if (output_file.empty())
    {
        for (size_t i = 0; i != limit_infos.size(); i++)
        {
            cout << limit_infos.at(i) << endl;
        }
    }
    else
    {
        rt::mkdir(rt::dirname(output_file), /*force=*/true);
        std::ofstream out(output_file.c_str(), std::ofstream::out);
        for (size_t i = 0; i != limit_infos.size(); i++)
        {
            out << limit_infos.at(i) << endl;
        }
        out.close();
    }

    // cleanup
    delete h_xsec;
}

void CreateLimitHists
(
    const at::Sample::value_type sample,
    const std::string& input_file,
    const std::string& output_file
)
{
    // extract the values 
    vector<LimitInfo> limit_infos;
    if (not input_file.empty())
    {
        std::ifstream fin;
        fin.open(input_file.c_str(), std::ifstream::in);
        while (fin.good())
        {
            LimitInfo limit_info;
            fin >> limit_info;
            limit_infos.push_back(limit_info);
        }
    }

    // bin info
    SignalBinInfo bin_info = GetSignalBinInfo(sample);
    const size_t nbinsx = bin_info.nbinsx;
    const size_t nbinsy = bin_info.nbinsy;
/*     const float xmin    = bin_info.xmin; */
/*     const float ymin    = bin_info.ymin + bin_info.offset; */
/*     const float xmax    = bin_info.xmax - bin_info.xwidth; */
/*     const float ymax    = bin_info.ymax; */
/*     const float m       = (ymax - ymin)/(xmax - xmin); */

    // book hists
    rt::TH1Container hc;
    hc.Add(new TH2I("h_xsec_exclusion"          , Form("xsec exlusion %s"                    , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc.Add(new TH2F("h_xsec_theory"             , Form("theoretical xsec %s"                 , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc.Add(new TH2F("h_xsec_limit_obs"          , Form("Observed xsec at 95%% CL %s"         , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc.Add(new TH2F("h_xsec_limit_exp"          , Form("Expected xsec at 95%% CL %s"         , ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc.Add(new TH2F("h_xsec_limit_exp_1sigma_up", Form("Expected xsec + #sigma at 95%% CL %s", ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    hc.Add(new TH2F("h_xsec_limit_exp_1sigma_dn", Form("Expected xsec - #sigma at 95%% CL %s", ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));

    // fill hists
    for (size_t xbin = 1; xbin != nbinsx+1; xbin++)
    {
        for (size_t ybin = 1; ybin != nbinsy+1; ybin++)
        {
            const float sparm0 = hc["h_xsec_limit_obs"]->GetXaxis()->GetBinLowEdge(xbin);
            const float sparm1 = hc["h_xsec_limit_obs"]->GetYaxis()->GetBinLowEdge(ybin);

            // store the output
            std::vector<LimitInfo>::const_iterator limit_iter = std::find_if(limit_infos.begin(), limit_infos.end(), SelectBySparms(sparm0, sparm1));
            if (limit_iter != limit_infos.end())
            {
                const LimitInfo& limit_info = *limit_iter;

                // set hists
                hc["h_xsec_theory"             ]->SetBinContent(xbin, ybin, limit_info.xsec    );
                hc["h_xsec_theory"             ]->SetBinError  (xbin, ybin, limit_info.xsec_err);
                hc["h_xsec_limit_obs"          ]->SetBinContent(xbin, ybin, limit_info.obs          );
                hc["h_xsec_limit_obs"          ]->SetBinError  (xbin, ybin, limit_info.obs_err      );
                hc["h_xsec_limit_exp"          ]->SetBinContent(xbin, ybin, limit_info.exp          );
                hc["h_xsec_limit_exp_1sigma_up"]->SetBinContent(xbin, ybin, limit_info.exp_1sigma_up);
                hc["h_xsec_limit_exp_1sigma_dn"]->SetBinContent(xbin, ybin, limit_info.exp_1sigma_dn);
                hc["h_xsec_exclusion"          ]->SetBinContent(xbin, ybin, static_cast<int>(limit_info.xsec > limit_info.exp));
            }
        }
    }

    // same
    hc.Write(output_file);
}

// print the files for viewing
void PrintLimitHists(const std::string& input_file, const std::string& output_path, const std::string& suffix = "png")
{
    rt::TH1Container hc(input_file);
    gStyle->SetPadRightMargin(0.15);
    hc.SetStats(false);
    hc.SetOption("colz");
    hc["h_xsec_exclusion"]->SetOption("text");
    rt::mkdir(output_path, /*force=*/true);
    hc.Print(output_path, suffix);
}
