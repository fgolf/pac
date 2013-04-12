#include "rt/RootTools.h"

using namespace std;

std::string b(TH1* hist, const int binx, const int biny, const std::string& precision = "1.3")
{
    const float v = hist->GetBinContent(binx, biny); 
    const float e = hist->GetBinError(binx, biny); 
    std::string result = rt::pm_latex(v, e, precision);
    return result;
}

void MakeEffTable(const std::string& label, const bool is_el = true)
{
    rt::TH1Container hc_both(Form("plots/fits/%s/both/results.root", label.c_str()));
    TH1* hde = hc_both["h_data_eff"];
    TH1* hme = hc_both["h_mc_eff" ];
    TH1* hsf = hc_both["h_sf"     ];

    std::string latex;
    if (is_el)
    {
        latex.append(     "\\begin{table}[hb]\n"                                                                                                                                                                                           ); 
        latex.append(     "\\begin{center}\n"                                                                                                                                                                                              ); 
        latex.append(     "{\\footnotesize\n"                                                                                                                                                                                              ); 
        latex.append(     "\\begin{tabular}{|c|c|c|c|c|c|c|c|}\n"                                                                                                                                                                          ); 
        latex.append(     "\\hline\n"                                                                                                                                                                                                      ); 
        latex.append(     "\\backslashbox{\\aeta}{\\pt}   &         & $10-15$ \\GeV & $15-20$ \\GeV & $20-30$ \\GeV & $30-40$ \\GeV & $40-50$ \\GeV & $50-200$ \\GeV \\\\ \\hline\n"                                                       ); 
        latex.append(Form("\\multirow{3}{*}{$0.0-0.8$}    & MC      & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hme,1,1).c_str(), b(hme,1,2).c_str(), b(hme,1,3).c_str(), b(hme,1,4).c_str(), b(hme,1,5).c_str(), b(hme,1,6).c_str()) ); 
        latex.append(Form("                               & Data    & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hde,1,1).c_str(), b(hde,1,2).c_str(), b(hde,1,3).c_str(), b(hde,1,4).c_str(), b(hde,1,5).c_str(), b(hde,1,6).c_str()) ); 
        latex.append(Form("                               & Data/MC & %s & %s & %s & %s & %s & %s \\\\ \\hline\n", b(hsf,1,1).c_str(), b(hsf,1,2).c_str(), b(hsf,1,3).c_str(), b(hsf,1,4).c_str(), b(hsf,1,5).c_str(), b(hsf,1,6).c_str()) ); 
        latex.append(Form("\\multirow{3}{*}{$0.8-1.4442$} & MC      & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hme,2,1).c_str(), b(hme,2,2).c_str(), b(hme,2,3).c_str(), b(hme,2,4).c_str(), b(hme,2,5).c_str(), b(hme,2,6).c_str()) ); 
        latex.append(Form("                               & Data    & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hde,2,1).c_str(), b(hde,2,2).c_str(), b(hde,2,3).c_str(), b(hde,2,4).c_str(), b(hde,2,5).c_str(), b(hde,2,6).c_str()) ); 
        latex.append(Form("                               & Data/MC & %s & %s & %s & %s & %s & %s \\\\ \\hline\n", b(hsf,2,1).c_str(), b(hsf,2,2).c_str(), b(hsf,2,3).c_str(), b(hsf,2,4).c_str(), b(hsf,2,5).c_str(), b(hsf,2,6).c_str()) ); 
        latex.append(Form("\\multirow{3}{*}{$1.566-2.0$}  & MC      & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hme,4,1).c_str(), b(hme,4,2).c_str(), b(hme,4,3).c_str(), b(hme,4,4).c_str(), b(hme,4,5).c_str(), b(hme,4,6).c_str()) ); 
        latex.append(Form("                               & Data    & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hde,4,1).c_str(), b(hde,4,2).c_str(), b(hde,4,3).c_str(), b(hde,4,4).c_str(), b(hde,4,5).c_str(), b(hde,4,6).c_str()) ); 
        latex.append(Form("                               & Data/MC & %s & %s & %s & %s & %s & %s \\\\ \\hline\n", b(hsf,4,1).c_str(), b(hsf,4,2).c_str(), b(hsf,4,3).c_str(), b(hsf,4,4).c_str(), b(hsf,4,5).c_str(), b(hsf,4,6).c_str()) ); 
        latex.append(Form("\\multirow{3}{*}{$2.0-2.5$}    & MC      & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hme,5,1).c_str(), b(hme,5,2).c_str(), b(hme,5,3).c_str(), b(hme,5,4).c_str(), b(hme,5,5).c_str(), b(hme,5,6).c_str()) ); 
        latex.append(Form("                               & Data    & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hde,5,1).c_str(), b(hde,5,2).c_str(), b(hde,5,3).c_str(), b(hde,5,4).c_str(), b(hde,5,5).c_str(), b(hde,5,6).c_str()) ); 
        latex.append(Form("                               & Data/MC & %s & %s & %s & %s & %s & %s \\\\ \\hline\n", b(hsf,5,1).c_str(), b(hsf,5,2).c_str(), b(hsf,5,3).c_str(), b(hsf,5,4).c_str(), b(hsf,5,5).c_str(), b(hsf,5,6).c_str()) ); 
        latex.append(     "\\end{tabular}\n"                                                                                                                                                                                               ); 
        latex.append(     "}\n"                                                                                                                                                                                                            ); 
        latex.append(     "\\label{tab:tnp_el_eff}\n"                                                                                                                                                                                      ); 
        latex.append(     "\\caption{Electron efficiencies measured using the \\tnp~method.  The uncertainties are statistical only.}\n"                                                                                                   ); 
        latex.append(     "\\end{center}\n"                                                                                                                                                                                                ); 
        latex.append(     "\\end{table}\n"                                                                                                                                                                                                 ); 
    }
    else 
    {
        latex.append(     "\\begin{table}[hb]\n"                                                                                                                                                                                           ); 
        latex.append(     "\\begin{center}\n"                                                                                                                                                                                              ); 
        latex.append(     "{\\footnotesize\n"                                                                                                                                                                                              ); 
        latex.append(     "\\begin{tabular}{|c|c|c|c|c|c|c|c|}\n"                                                                                                                                                                          ); 
        latex.append(     "\\hline\n"                                                                                                                                                                                                      ); 
        latex.append(     "\\backslashbox{\\aeta}{\\pt}   &         & $10-15$ \\GeV & $15-20$ \\GeV & $20-30$ \\GeV & $30-40$ \\GeV & $40-50$ \\GeV & $50-200$ \\GeV \\\\ \\hline\n"                                                       ); 
        latex.append(Form("\\multirow{3}{*}{$0.0-1.2$}    & MC      & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hme,1,1).c_str(), b(hme,1,2).c_str(), b(hme,1,3).c_str(), b(hme,1,4).c_str(), b(hme,1,5).c_str(), b(hme,1,6).c_str()) ); 
        latex.append(Form("                               & Data    & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hde,1,1).c_str(), b(hde,1,2).c_str(), b(hde,1,3).c_str(), b(hde,1,4).c_str(), b(hde,1,5).c_str(), b(hde,1,6).c_str()) ); 
        latex.append(Form("                               & Data/MC & %s & %s & %s & %s & %s & %s \\\\ \\hline\n", b(hsf,1,1).c_str(), b(hsf,1,2).c_str(), b(hsf,1,3).c_str(), b(hsf,1,4).c_str(), b(hsf,1,5).c_str(), b(hsf,1,6).c_str()) ); 
        latex.append(Form("\\multirow{3}{*}{$1.2-2.5$}    & MC      & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hme,2,1).c_str(), b(hme,2,2).c_str(), b(hme,2,3).c_str(), b(hme,2,4).c_str(), b(hme,2,5).c_str(), b(hme,2,6).c_str()) ); 
        latex.append(Form("                               & Data    & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hde,2,1).c_str(), b(hde,2,2).c_str(), b(hde,2,3).c_str(), b(hde,2,4).c_str(), b(hde,2,5).c_str(), b(hde,2,6).c_str()) ); 
        latex.append(Form("                               & Data/MC & %s & %s & %s & %s & %s & %s \\\\ \\hline\n", b(hsf,2,1).c_str(), b(hsf,2,2).c_str(), b(hsf,2,3).c_str(), b(hsf,2,4).c_str(), b(hsf,2,5).c_str(), b(hsf,2,6).c_str()) ); 
        latex.append(     "\\end{tabular}\n"                                                                                                                                                                                               ); 
        latex.append(     "}\n"                                                                                                                                                                                                            ); 
        latex.append(     "\\label{tab:tnp_mu_eff}\n"                                                                                                                                                                                      ); 
        latex.append(     "\\caption{Muon efficiencies measured using the \\tnp~method.  The uncertainties are statistical only.}\n"                                                                                                       ); 
        latex.append(     "\\end{center}\n"                                                                                                                                                                                                ); 
        latex.append(     "\\end{table}\n"                                                                                                                                                                                                 ); 
    }

    cout << latex << endl;
}

void MakeFactorizationTable(const std::string& label, const bool is_el = true)
{
    rt::TH1Container hc_id  (Form("plots/fits/%s/id/results.root"  , label.c_str()));
    rt::TH1Container hc_iso (Form("plots/fits/%s/iso/results.root" , label.c_str()));
    rt::TH1Container hc_both(Form("plots/fits/%s/both/results.root", label.c_str()));

    TH1* hb = hc_both["h_sf"];
    TH1* hp = rt::MultiplyHists(hc_id["h_sf"], hc_iso["h_sf"], "h_sf");
    TH1* hd = rt::RelativeDiffHists(hb, hp, "h_diff");

    std::string latex;
    if (is_el)
    {
        latex.append(     "\\begin{table}[hb]\n"                                                                                                                                                                                      ); 
        latex.append(     "\\begin{center}\n"                                                                                                                                                                                         ); 
        latex.append(     "{\\footnotesize\n"                                                                                                                                                                                         ); 
        latex.append(     "\\begin{tabular}{|c|c|c|c|c|c|c|c|}\n"                                                                                                                                                                     ); 
        latex.append(     "\\hline\n"                                                                                                                                                                                                 ); 
        latex.append(     "\\backslashbox{\\aeta}{\\pt}   &          & $10-15$ \\GeV & $15-20$ \\GeV & $20-30$ \\GeV & $30-40$ \\GeV & $40-50$ \\GeV & $50-200$ \\GeV \\\\ \\hline\n"                                                 ); 
        latex.append(Form("\\multirow{3}{*}{$0.0-0.8$}    & ID*ISO   & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hp,1,1).c_str(), b(hp,1,2).c_str(), b(hp,1,3).c_str(), b(hp,1,4).c_str(), b(hp,1,5).c_str(), b(hp,1,6).c_str()) ); 
        latex.append(Form("                               & ID+ISO   & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hb,1,1).c_str(), b(hb,1,2).c_str(), b(hb,1,3).c_str(), b(hb,1,4).c_str(), b(hb,1,5).c_str(), b(hb,1,6).c_str()) ); 
        latex.append(Form("                               & rel diff & %s & %s & %s & %s & %s & %s \\\\ \\hline\n", b(hd,1,1).c_str(), b(hd,1,2).c_str(), b(hd,1,3).c_str(), b(hd,1,4).c_str(), b(hd,1,5).c_str(), b(hd,1,6).c_str()) ); 
        latex.append(Form("\\multirow{3}{*}{$0.8-1.4442$} & ID*ISO   & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hp,2,1).c_str(), b(hp,2,2).c_str(), b(hp,2,3).c_str(), b(hp,2,4).c_str(), b(hp,2,5).c_str(), b(hp,2,6).c_str()) ); 
        latex.append(Form("                               & ID+ISO   & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hb,2,1).c_str(), b(hb,2,2).c_str(), b(hb,2,3).c_str(), b(hb,2,4).c_str(), b(hb,2,5).c_str(), b(hb,2,6).c_str()) ); 
        latex.append(Form("                               & rel diff & %s & %s & %s & %s & %s & %s \\\\ \\hline\n", b(hd,2,1).c_str(), b(hd,2,2).c_str(), b(hd,2,3).c_str(), b(hd,2,4).c_str(), b(hd,2,5).c_str(), b(hd,2,6).c_str()) ); 
        latex.append(Form("\\multirow{3}{*}{$1.566-2.0$}  & ID*ISO   & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hp,4,1).c_str(), b(hp,4,2).c_str(), b(hp,4,3).c_str(), b(hp,4,4).c_str(), b(hp,4,5).c_str(), b(hp,4,6).c_str()) ); 
        latex.append(Form("                               & ID+ISO   & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hb,4,1).c_str(), b(hb,4,2).c_str(), b(hb,4,3).c_str(), b(hb,4,4).c_str(), b(hb,4,5).c_str(), b(hb,4,6).c_str()) ); 
        latex.append(Form("                               & rel diff & %s & %s & %s & %s & %s & %s \\\\ \\hline\n", b(hd,4,1).c_str(), b(hd,4,2).c_str(), b(hd,4,3).c_str(), b(hd,4,4).c_str(), b(hd,4,5).c_str(), b(hd,4,6).c_str()) ); 
        latex.append(Form("\\multirow{3}{*}{$2.0-2.5$}    & ID*ISO   & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hp,5,1).c_str(), b(hp,5,2).c_str(), b(hp,5,3).c_str(), b(hp,5,4).c_str(), b(hp,5,5).c_str(), b(hp,5,6).c_str()) ); 
        latex.append(Form("                               & ID+ISO   & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hb,5,1).c_str(), b(hb,5,2).c_str(), b(hb,5,3).c_str(), b(hb,5,4).c_str(), b(hb,5,5).c_str(), b(hb,5,6).c_str()) ); 
        latex.append(Form("                               & rel diff & %s & %s & %s & %s & %s & %s \\\\ \\hline\n", b(hd,5,1).c_str(), b(hd,5,2).c_str(), b(hd,5,3).c_str(), b(hd,5,4).c_str(), b(hd,5,5).c_str(), b(hd,5,6).c_str()) ); 
        latex.append(     "\\end{tabular}\n"                                                                                                                                                                                          ); 
        latex.append(     "}\n"                                                                                                                                                                                                       ); 
        latex.append(     "\\label{tab:tnp_el_fac}\n"                                                                                                                                                                                 ); 
        latex.append(     "\\caption{Electron efficiency data/MC scale factors measured using the \\tnp~method.  The uncertainties are statistical only.}\n"                                                                          ); 
        latex.append(     "\\end{center}\n"                                                                                                                                                                                           ); 
        latex.append(     "\\end{table}\n"                                                                                                                                                                                            ); 
    }
    else 
    {
        latex.append(     "\\begin{table}[hb]\n"                                                                                                                                                                                    ); 
        latex.append(     "\\begin{center}\n"                                                                                                                                                                                       ); 
        latex.append(     "{\\footnotesize\n"                                                                                                                                                                                       ); 
        latex.append(     "\\begin{tabular}{|c|c|c|c|c|c|c|c|}\n"                                                                                                                                                                   ); 
        latex.append(     "\\hline\n"                                                                                                                                                                                               ); 
        latex.append(     "\\backslashbox{\\aeta}{\\pt} &          & $10-15$ \\GeV & $15-20$ \\GeV & $20-30$ \\GeV & $30-40$ \\GeV & $40-50$ \\GeV & $50-200$ \\GeV \\\\ \\hline\n"                                                 ); 
        latex.append(Form("\\multirow{3}{*}{$0.0-1.2$}  & ID*ISO   & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hp,1,1).c_str(), b(hp,1,2).c_str(), b(hp,1,3).c_str(), b(hp,1,4).c_str(), b(hp,1,5).c_str(), b(hp,1,6).c_str()) ); 
        latex.append(Form("                             & ID+ISO   & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hb,1,1).c_str(), b(hb,1,2).c_str(), b(hb,1,3).c_str(), b(hb,1,4).c_str(), b(hb,1,5).c_str(), b(hb,1,6).c_str()) ); 
        latex.append(Form("                             & rel diff & %s & %s & %s & %s & %s & %s \\\\ \\hline\n", b(hd,1,1).c_str(), b(hd,1,2).c_str(), b(hd,1,3).c_str(), b(hd,1,4).c_str(), b(hd,1,5).c_str(), b(hd,1,6).c_str()) ); 
        latex.append(Form("\\multirow{3}{*}{$1.2-2.5$}  & ID*ISO   & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hp,2,1).c_str(), b(hp,2,2).c_str(), b(hp,2,3).c_str(), b(hp,2,4).c_str(), b(hp,2,5).c_str(), b(hp,2,6).c_str()) ); 
        latex.append(Form("                             & ID+ISO   & %s & %s & %s & %s & %s & %s \\\\\n"        , b(hb,2,1).c_str(), b(hb,2,2).c_str(), b(hb,2,3).c_str(), b(hb,2,4).c_str(), b(hb,2,5).c_str(), b(hb,2,6).c_str()) ); 
        latex.append(Form("                             & rel diff & %s & %s & %s & %s & %s & %s \\\\ \\hline\n", b(hd,2,1).c_str(), b(hd,2,2).c_str(), b(hd,2,3).c_str(), b(hd,2,4).c_str(), b(hd,2,5).c_str(), b(hd,2,6).c_str()) ); 
        latex.append(     "\\end{tabular}\n"                                                                                                                                                                                        ); 
        latex.append(     "}\n"                                                                                                                                                                                                     ); 
        latex.append(     "\\label{tab:tnp_mu_fac}\n"                                                                                                                                                                               ); 
        latex.append(     "\\caption{Muon efficiency data/MC scale factors measured using the \\tnp~method.  The uncertainties are statistical only.}\n"                                                                            ); 
        latex.append(     "\\end{center}\n"                                                                                                                                                                                         ); 
        latex.append(     "\\end{table}\n"                                                                                                                                                                                          ); 
    }

    cout << latex << endl;
}
