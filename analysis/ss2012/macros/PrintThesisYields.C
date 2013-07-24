#include <fstream>
#include "rt/RootTools.h"
#include "at/Sample.h"
#include "SignalRegion.h"

using namespace std;

// simple struct to hold the data from the file
// ---------------------------------------------------------------------------- //
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

struct CompareSR
{
    CompareSR(const unsigned int sr_num) : m_sr_num(sr_num) {}
    bool operator () (const yield_info_t& yi) {return (yi.sr_num==m_sr_num);}
    const unsigned int m_sr_num;
};

// helper functions
// ---------------------------------------------------------------------------- //

std::string GetSigFigString(const float v, const float e, const int num_dec = 1)
{
    const string fmt1 = string("\%1.") + Form("%1d", num_dec  ) + "f";
    const string fmt2 = string("\%1.") + Form("%1d", num_dec-1) + "f";
    const std::string v_temp = (v < 10 ? Form(fmt1.c_str(), v): Form(fmt2.c_str(), v)); 
    const std::string e_temp = (v < 10 ? Form(fmt1.c_str(), e): Form(fmt2.c_str(), e)); 
    return (v_temp + " $\\pm$ " + e_temp);
}

void SetBinLabel(TH1F& hist, const int sr_offset = 0)
{
    hist.GetXaxis()->SetBinLabel(1, Form("SR%d", 1 + sr_offset));
    hist.GetXaxis()->SetBinLabel(2, Form("SR%d", 2 + sr_offset));
    hist.GetXaxis()->SetBinLabel(3, Form("SR%d", 3 + sr_offset));
    hist.GetXaxis()->SetBinLabel(4, Form("SR%d", 4 + sr_offset));
    hist.GetXaxis()->SetBinLabel(5, Form("SR%d", 5 + sr_offset));
    hist.GetXaxis()->SetBinLabel(6, Form("SR%d", 6 + sr_offset));
    hist.GetXaxis()->SetBinLabel(7, Form("SR%d", 7 + sr_offset));
    hist.GetXaxis()->SetBinLabel(8, Form("SR%d", 8 + sr_offset));
}

rt::TH1Overlay CreateOverlay
(
    TH1F& h_data, 
    TH1F& h_pred, 
    TH1F& h_fake, 
    TH1F& h_flip, 
    TH1F& h_rare, 
    const std::string& title, 
    const std::string& label = ""
)
{
    rt::TH1Overlay::legend_width_default            = 0.28;
    rt::TH1Overlay::legend_height_per_entry_default = 0.05;
    rt::TH1Overlay::legend_text_size_default        = 0.030;
    rt::TH1Overlay::legend_offset_default           = 0.010;

    // colors
    const Color_t data_color  = kBlack;
    const Color_t rare_color  = kCyan-5;
    const Color_t fake_color  = kRed-6;
    const Color_t flip_color  = kOrange-8;
    const Style_t data_marker = 20;
    const float marker_size   = 1.2;
    const Style_t shade_style = 3335;
    const string flip_legend  = "Charge MisID";
    const string fake_legend  = "Non-prompt e/#mu";
    const string rare_legend  = "Rare SM Processes";
    const string data_legend  = "Data";
    const string unc_legend   = "Total Bkgd Uncertainty";
    const std::string option  = "sb::off dt::stack lg::top_right B";
/*     const float width         = 0.6; */
/*     const float offset        = 0.2; */
    const float label_size    = 0.10;

    h_data.SetMarkerSize(marker_size);
    h_data.SetBarWidth(0);
/*     h_fake.SetBarWidth(width); */
/*     h_flip.SetBarWidth(width); */
/*     h_rare.SetBarWidth(width); */
/*     h_pred.SetBarWidth(width); */
/*     h_data.SetBarOffset(offset); */
/*     h_fake.SetBarOffset(offset); */
/*     h_flip.SetBarOffset(offset); */
/*     h_rare.SetBarOffset(offset); */
/*     h_pred.SetBarOffset(offset); */
    h_data.SetLabelSize(label_size);
    h_fake.SetLabelSize(label_size);
    h_flip.SetLabelSize(label_size);
    h_rare.SetLabelSize(label_size);
    h_pred.SetLabelSize(label_size);

    rt::TH1Overlay p(title, option);
    const float max = std::max(h_data.GetMaximum(), h_pred.GetMaximum());
    p.Add(&h_data, /*no_stack=*/true, data_legend, data_color, 2, data_marker);
    p.Add(&h_fake, fake_legend, fake_color);
    p.Add(&h_flip, flip_legend, flip_color);
    p.Add(&h_rare, rare_legend, rare_color);
    p.Add(&h_pred, /*no_stack=*/true, unc_legend, 1, 2, 1, shade_style);
    p.SetYAxisRange(0.0, max);
    if (not label.empty())
    {
        TLatex text(0.18, 0.825, label.c_str());
        text.SetTextSize(0.04);
        text.SetNDC();
        p.AddText(text);
    }

    return p;
}

// do it
// ---------------------------------------------------------------------------- //
void PrintThesisYields
(
    const std::string& output_path, 
    const std::string& analysis_type_name, 
    const std::string& signal_region_type_name = "exclusive" 
)
{
    using namespace at;

    const ss::AnalysisType::value_type analysis_type = ss::GetAnalysisTypeFromName(analysis_type_name);
    const ss::AnalysisTypeInfo at_info               = ss::GetAnalysisTypeInfo(analysis_type);
/*     const ss::SignalRegionType::value_type signal_region_type = ss::GetSignalRegionTypeFromName(signal_region_type_name); */

    // yield and predictions 

    // check that input file exists
    const std::string yield_file = Form("tables/%s/yields_and_pred_%s_%s_%s.txt", output_path.c_str(), analysis_type_name.c_str(), signal_region_type_name.c_str(), output_path.c_str());
    if (!rt::exists(yield_file))
    {
        cout << "[PrintThesisYields] ERROR: yield/pred file " << yield_file << " not found" << endl;
        return;
    }

    // parse the file 
    vector<yield_info_t> yield_infos;
    if (not yield_file.empty())
    {
        std::ifstream fin(yield_file.c_str());
        std::copy(std::istream_iterator<yield_info_t>(fin), std::istream_iterator<yield_info_t>(), std::back_inserter(yield_infos));
    }
    else
    {
        cout << "[PrintThesisYields] ERROR: yield/pred file " << yield_file << " empty or cannot be open" << endl;
        return;
    }

    // print tex
    std::vector<unsigned int> sr_nums;
    sr_nums.clear();
    const unsigned int values[] = { 1,  2,  3,  4,  5,  6,  7,  8,
                                   11, 12, 13, 14, 15, 16, 17, 18,
                                   21, 22, 23, 24, 25, 26, 27, 28};
    sr_nums.assign(values, values+24);

    string latex;
    latex.append("\\begin{tabular}{c|c|ccc|c}\n");
    latex.append("\\hline \\hline \n");
    latex.append("Search Region & Observed & Fake Leptons & Incorrect Charge & Simulation & Total Prediction \\\\ \\hline\n");
    for (size_t i = 0; i != sr_nums.size(); i++)
    {
        const unsigned int sr_num = sr_nums.at(i);

        yield_info_t yi = *std::find_if(yield_infos.begin(), yield_infos.end(), CompareSR(sr_num));
        const std::string& s_pred = GetSigFigString(yi.pred, yi.pred_unc, 1);  
        const std::string& s_rare = GetSigFigString(yi.rare, yi.rare_unc, 1);  
        const std::string& s_fake = GetSigFigString(yi.fake, yi.fake_unc, 1);  
        const std::string& s_flip = GetSigFigString(yi.flip, yi.flip_unc, 2);  

        if (sr_num==8 or sr_num==18)
        {
            latex.append(Form("%d & %d & %s & %s & %s & %s \\\\ \\hline\n", sr_num, yi.yield, s_fake.c_str(), s_flip.c_str(), s_rare.c_str(), s_pred.c_str()));
        }
        else
        {
            latex.append(Form("%d & %d & %s & %s & %s & %s \\\\        \n", sr_num, yi.yield, s_fake.c_str(), s_flip.c_str(), s_rare.c_str(), s_pred.c_str()));
        }
    }
    latex.append("\\hline \\hline\n");
    latex.append("\\end{tabular}\n");

    // print summary

    // book
    TH1F h_data_nb0("h_data_nb0", "h_data_nb0", 8, 0, 8); SetBinLabel(h_data_nb0, 0);
    TH1F h_pred_nb0("h_pred_nb0", "h_pred_nb0", 8, 0, 8); SetBinLabel(h_pred_nb0, 0);
    TH1F h_fake_nb0("h_fake_nb0", "h_fake_nb0", 8, 0, 8); SetBinLabel(h_fake_nb0, 0);
    TH1F h_flip_nb0("h_flip_nb0", "h_flip_nb0", 8, 0, 8); SetBinLabel(h_flip_nb0, 0);
    TH1F h_rare_nb0("h_rare_nb0", "h_rare_nb0", 8, 0, 8); SetBinLabel(h_rare_nb0, 0);

    TH1F h_data_nb1("h_data_nb1", "h_data_nb1", 8, 0, 8); SetBinLabel(h_data_nb1, 10);
    TH1F h_pred_nb1("h_pred_nb1", "h_pred_nb1", 8, 0, 8); SetBinLabel(h_pred_nb1, 10);
    TH1F h_fake_nb1("h_fake_nb1", "h_fake_nb1", 8, 0, 8); SetBinLabel(h_fake_nb1, 10);
    TH1F h_flip_nb1("h_flip_nb1", "h_flip_nb1", 8, 0, 8); SetBinLabel(h_flip_nb1, 10);
    TH1F h_rare_nb1("h_rare_nb1", "h_rare_nb1", 8, 0, 8); SetBinLabel(h_rare_nb1, 10);

    TH1F h_data_nb2("h_data_nb2", "h_data_nb1", 8, 0, 8); SetBinLabel(h_data_nb2, 20);
    TH1F h_pred_nb2("h_pred_nb2", "h_pred_nb1", 8, 0, 8); SetBinLabel(h_pred_nb2, 20);
    TH1F h_fake_nb2("h_fake_nb2", "h_fake_nb1", 8, 0, 8); SetBinLabel(h_fake_nb2, 20);
    TH1F h_flip_nb2("h_flip_nb2", "h_flip_nb1", 8, 0, 8); SetBinLabel(h_flip_nb2, 20);
    TH1F h_rare_nb2("h_rare_nb2", "h_rare_nb1", 8, 0, 8); SetBinLabel(h_rare_nb2, 20);

    // fill
    for (size_t i = 0; i != sr_nums.size(); i++)
    {
        const unsigned int sr_num = sr_nums.at(i);
        yield_info_t yi = *std::find_if(yield_infos.begin(), yield_infos.end(), CompareSR(sr_num));
        
        if (1 <= sr_num && sr_num <= 8)
        {
            int bin = sr_num;
            h_data_nb0.SetBinContent(bin, yi.yield); h_data_nb0.SetBinError(bin, sqrt(yi.yield));
            h_pred_nb0.SetBinContent(bin, yi.pred ); h_data_nb0.SetBinError(bin, yi.pred_unc   );
            h_fake_nb0.SetBinContent(bin, yi.fake ); h_data_nb0.SetBinError(bin, yi.fake_unc   );
            h_flip_nb0.SetBinContent(bin, yi.flip ); h_data_nb0.SetBinError(bin, yi.flip_unc   );
            h_rare_nb0.SetBinContent(bin, yi.rare ); h_data_nb0.SetBinError(bin, yi.rare_unc   );
        }
        if (11 <= sr_num && sr_num <= 18)
        {
            int bin = sr_num - 10;
            h_data_nb1.SetBinContent(bin, yi.yield); h_data_nb1.SetBinError(bin, sqrt(yi.yield));
            h_pred_nb1.SetBinContent(bin, yi.pred ); h_data_nb1.SetBinError(bin, yi.pred_unc   );
            h_fake_nb1.SetBinContent(bin, yi.fake ); h_data_nb1.SetBinError(bin, yi.fake_unc   );
            h_flip_nb1.SetBinContent(bin, yi.flip ); h_data_nb1.SetBinError(bin, yi.flip_unc   );
            h_rare_nb1.SetBinContent(bin, yi.rare ); h_data_nb1.SetBinError(bin, yi.rare_unc   );
        }
        if (21 <= sr_num && sr_num <= 28)
        {
            int bin = sr_num - 20;
            h_data_nb2.SetBinContent(bin, yi.yield); h_data_nb2.SetBinError(bin, sqrt(yi.yield));
            h_pred_nb2.SetBinContent(bin, yi.pred ); h_data_nb2.SetBinError(bin, yi.pred_unc   );
            h_fake_nb2.SetBinContent(bin, yi.fake ); h_data_nb2.SetBinError(bin, yi.fake_unc   );
            h_flip_nb2.SetBinContent(bin, yi.flip ); h_data_nb2.SetBinError(bin, yi.flip_unc   );
            h_rare_nb2.SetBinContent(bin, yi.rare ); h_data_nb2.SetBinError(bin, yi.rare_unc   );
        }
    }

    // overlay
    rt::SetTDRStyle();
    std::map<std::string, rt::TH1Overlay> p;
    const std::string stem  = Form("%s_%s", at_info.short_name.c_str(), signal_region_type_name.c_str());
    const std::string title = "Summary, #sqrt{s} = 8 TeV, L_{int} = 19.5 fb^{-1};Search Region;Events/bin";

    p[Form("p_yields_%s_nb0", stem.c_str())] = CreateOverlay
    (
        h_data_nb0, 
        h_pred_nb0, 
        h_fake_nb0, 
        h_flip_nb0, 
        h_rare_nb0, 
        title,
        Form("%s leptons with 0 b-tags", at_info.title.c_str())
    );

    p[Form("p_yields_%s_nb1", stem.c_str())] = CreateOverlay
    (
        h_data_nb1, 
        h_pred_nb1, 
        h_fake_nb1, 
        h_flip_nb1, 
        h_rare_nb1, 
        title,
        Form("%s leptons with 1 b-tag", at_info.title.c_str())
    );

    p[Form("p_yields_%s_nb2", stem.c_str())] = CreateOverlay
    (
        h_data_nb2, 
        h_pred_nb2, 
        h_fake_nb2, 
        h_flip_nb2, 
        h_rare_nb2, 
        title,
        Form("%s leptons with #geq 2 b-tags", at_info.title.c_str())
    );

    // print
    rt::Print(p, "plots/thesis/pdf", "pdf");
    
    ofstream out(Form("tables/thesis/summary_%s.tex", stem.c_str()));
    out << latex << endl;

    // done
    return;
}
