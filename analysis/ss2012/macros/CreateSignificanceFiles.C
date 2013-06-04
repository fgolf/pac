#include <iostream>
#include <fstream>
#include <string>

#include "rt/RootTools.h"
#include "at/Sample.h"
#include "SignalBinInfo.h"
//#include "/usr/local/lands/03.06.07/test/fitRvsCLs.C"
//#include "/home/users/rwkelley/code/LandS/03.06.07/test/fitRvsCLs.C"

using namespace std;
using namespace ss;

struct SigInfo
{
    float sparm0;
    float sparm1;
    double sig;
};

// sort by sparm0 and then sparm1
bool operator < (const SigInfo& lhs, const SigInfo& rhs)
{
    if (lhs.sparm0 < rhs.sparm0) {return true; }
    if (lhs.sparm0 > rhs.sparm0) {return false;}
    if (lhs.sparm1 < rhs.sparm1) {return true; }
    else {return false;}
}

struct SelectBySparms
{
    SelectBySparms(const float sparm0, const float sparm1) 
        : m_sparm0(sparm0)
        , m_sparm1(sparm1)
    {}
    const float m_sparm0;
    const float m_sparm1;

    bool operator () (const SigInfo& sig_info) const
    {
        return (rt::is_equal(sig_info.sparm0, m_sparm0) && rt::is_equal(sig_info.sparm1, m_sparm1));
    }
};


void CreateSignificanceHists
(
    const at::Sample::value_type sample,
    const std::string& input_file_path,
    const std::string& input_file_stem,
    const std::string& output_file = ""
)
{
    // store the lines
    vector<SigInfo> sig_infos;

    SignalBinInfo bin_info = GetSignalBinInfo(sample);
/*     TH1F* h_xsec = rt::GetHistFromRootFile<TH1F>("data/xsec/susy_xsec.root", Form("h_xsec_%s", at::GetSampleInfo(sample).name.c_str())); */

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
            SigInfo sig_info;
            sig_info.sparm0 = sparm0;
            sig_info.sparm1 = sparm1;
            sig_info.sig    = 0.0;

            // boundary conditions
            if (y > cond) {continue;}

            // extract file to process
            const string file_stem      = Form("%s_p%1.0f_p%1.0f", input_file_stem.c_str(), sparm0, sparm1);
            const string root_file_name = Form("%s/%s_frqObsPvalue.root", input_file_path.c_str(), file_stem.c_str());

            // check that file exists
            if (not rt::exists(root_file_name))
            {
                cout << "File " << root_file_name << " does not exist -- filling with bogus values." << endl;
                sig_infos.push_back(sig_info);
                continue;
            }

            cout << "extracting sigs for " << root_file_name << endl;

            // extract sigs
            TChain chain("T");
            chain.Add(root_file_name.c_str());

            // branches
            TBranch* b_sig = chain.GetBranch("significance"); b_sig->SetAddress(&sig_info.sig);  // observed signficance

            // only one entry
            chain.GetEntry(0);

            // save the sig for this mass point
            sig_infos.push_back(sig_info);

            // done with this sparm value
        }
    }

    // output the lines
    std::sort(sig_infos.begin(), sig_infos.end());

    // book hists
    rt::TH1Container hc;
    hc.Add(new TH2F("h_sig", Form("significance %s", ss::GetSignalBinHistLabel(sample).c_str()), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));

    // fill hists
    for (size_t xbin = 1; xbin != nbinsx+1; xbin++)
    {
        for (size_t ybin = 1; ybin != nbinsy+1; ybin++)
        {
            const float sparm0 = hc["h_sig"]->GetXaxis()->GetBinLowEdge(xbin);
            const float sparm1 = hc["h_sig"]->GetYaxis()->GetBinLowEdge(ybin);

            // store the output
            std::vector<SigInfo>::const_iterator sig_iter = std::find_if(sig_infos.begin(), sig_infos.end(), SelectBySparms(sparm0, sparm1));
            if (sig_iter != sig_infos.end())
            {
                const SigInfo& sig_info = *sig_iter;

                // set hists
                hc["h_sig"]->SetBinContent(xbin, ybin, sig_info.sig);
            }
        }
    }

    // same
    hc.Write(output_file);
}

void PrintSignificanceHists(const std::string& input_file, const std::string& output_path, const std::string& suffix = "png")
{
    rt::TH1Container hc(input_file);
    gStyle->SetPadRightMargin(0.15);
    gStyle->SetPaintTextFormat("1.2f");
    hc.SetStats(false);
    hc.SetOption("colz");
/*     hc["h_sig"]->SetOption("text"); */
    rt::mkdir(output_path, /*force=*/true);
    hc.Print(output_path, suffix);
}

