#include "rt/RootTools.h"
#include "at/Sample.h"
#include "SignalRegion.h"
#include "CTable.h"

using namespace std;

// a simple yield struct

struct Yield
{
    Yield() 
        : title("")
        , ee  (0.0)
        , dee (0.0)
        , see (0.0)
        , mm  (0.0)
        , dmm (0.0)
        , smm (0.0)
        , em  (0.0)
        , dem (0.0)
        , sem (0.0)
        , ll  (0.0)
        , dll (0.0)
        , sll (0.0)
    {}

    Yield(const std::string& title_) 
        : title(title_)
        , ee  (0.0)
        , dee (0.0)
        , see (0.0)
        , mm  (0.0)
        , dmm (0.0)
        , smm (0.0)
        , em  (0.0)
        , dem (0.0)
        , sem (0.0)
        , ll  (0.0)
        , dll (0.0)
        , sll (0.0)
    {}

    Yield
    (
        const std::string& title_, 
        const std::pair<float, float> ee_, 
        const std::pair<float, float> mm_, 
        const std::pair<float, float> em_, 
        const std::pair<float, float> ll_ 
    )
        : title(title_)
        , ee  (ee_.first)
        , dee (ee_.second)
        , see (0.0)
        , mm  (mm_.first)
        , dmm (mm_.second)
        , smm (0.0)
        , em  (em_.first)
        , dem (em_.second)
        , sem (0.0)
        , ll (ll_.first)
        , dll(ll_.second)
        , sll(0.0)
    {}

    Yield
    (
        const std::string& title_, 
        float ee_, 
        float dee_, 
        float mm_, 
        float dmm_, 
        float em_, 
        float dem_, 
        float ll_,
        float dll_ 
    )
        : title(title_)
        , ee  (ee_)
        , dee (dee_) 
        , see (0.0)
        , mm  (mm_)  
        , dmm (dmm_) 
        , smm (0.0)
        , em  (em_)  
        , dem (dem_) 
        , sem (0.0)
        , ll (ll_) 
        , dll(dll_)
        , sll(0.0)
    {}

    std::string title;
    float ee;
    float dee;
    float see;
    float mm;
    float dmm;
    float smm;
    float em;
    float dem;
    float sem;
    float ll;
    float dll;
    float sll;

    // methods:
    Yield& operator+=(const Yield& y);
    Yield& operator-=(const Yield& y);

    std::string GetLatex(const std::string& latex = "", bool print_sys_err = false) const;
    void Print(bool print_sys_err = false) const;

};

// members
Yield& Yield::operator+=(const Yield& y)
{
    ee  += y.ee;
    mm  += y.mm;
    em  += y.em;
    ll  += y.ll;
    dee = sqrt(dee*dee + y.dee*y.dee); 
    dmm = sqrt(dmm*dmm + y.dmm*y.dmm);
    dem = sqrt(dem*dem + y.dem*y.dem);
    dll = sqrt(dll*dll + y.dll*y.dll);
    see = sqrt(see*see + y.see*y.see); 
    smm = sqrt(smm*smm + y.smm*y.smm);
    sem = sqrt(sem*sem + y.sem*y.sem);
    sll = sqrt(sll*sll + y.sll*y.sll);
    return *this; 
}

Yield& Yield::operator-=(const Yield& y)
{
    ee  -= y.ee;
    mm  -= y.mm;
    em  -= y.em;
    ll  -= y.ll;
    dee = sqrt(dee*dee + y.dee*y.dee); 
    dmm = sqrt(dmm*dmm + y.dmm*y.dmm);
    dem = sqrt(dem*dem + y.dem*y.dem);
    dll = sqrt(dll*dll + y.dll*y.dll);
    see = sqrt(see*see + y.see*y.see); 
    smm = sqrt(smm*smm + y.smm*y.smm);
    sem = sqrt(sem*sem + y.sem*y.sem);
    sll = sqrt(sll*sll + y.sll*y.sll);
    return *this; 
}

std::string Yield::GetLatex(const std::string& latex, bool print_sys_err) const
{
    string result;
    if (rt::string_contains(title, "data"))
    {
        const char* format = "%35s & %5.0f & %5.0f & %5.0f & %5.0f";
        result = Form(format, not latex.empty() ? latex.c_str() : title.c_str(), ee, mm, em, ll);
    }
    else
    {
        if (print_sys_err)
        {
            const char* format = "%35s & %5.3f $\\pm$ %5.3f $\\pm$ %5.3f & %5.3f $\\pm$ %5.3f $\\pm$ %5.3f & %5.3f $\\pm$ %5.3f $\\pm$ %5.3f & %5.3f $\\pm$ %5.3f $\\pm$ %5.3f";
            result = Form(format, not latex.empty() ? latex.c_str() : title.c_str(), ee, dee, see, mm, dmm, smm, em, dem, sem, ll, dll, sll);
        }
        else
        {
            const char* format = "%35s & %5.3f $\\pm$ %5.3f & %5.3f $\\pm$ %5.3f & %5.3f $\\pm$ %5.3f & %5.3f $\\pm$ %5.3f";
            result = Form(format, not latex.empty() ? latex.c_str() : title.c_str(), ee, dee, mm, dmm, em, dem, ll, dll);
        }
    }
    return result;
}

void Yield::Print(bool print_sys_err) const
{
    if (rt::string_contains(title, "data"))
    {
        const char* format = "%15s ee: %15.0f mm: %15.0f em: %15.0f ll: %15.0f";
        cout << Form(format, title.c_str(), ee, mm, em, ll) << endl;
    }
    else
    {
        if (print_sys_err)
        {
            const char* format = "%15s ee: %2.3f +/- %2.3f +/- %2.3f mm: %2.3f +/- %2.3f +/- %2.3f em: %2.3f +/- %2.3f +/- %2.3f ll: %2.3f +/- %2.3f +/- %2.3f";
            cout << Form(format, title.c_str(), ee, dee, see, mm, dmm, smm, em, dem, sem, ll, dll, sll) << endl;
        }
        else
        {
            const char* format = "%15s ee: %2.3f +/- %2.3f mm: %2.3f +/- %2.3f em: %2.3f +/- %2.3f ll: %2.3f +/- %2.3f";
            cout << Form(format, title.c_str(), ee, dee, mm, dmm, em, dem, ll, dll) << endl;
        }
    }
}

void SetErrorsToBogus(Yield& y)
{
    y.dee = 999;
    y.dmm = 999;
    y.dem = 999;
    y.dll = 999;
}

void SetSysUncertainties(Yield& y, float percent)
{
    y.see = y.ee * percent;
    y.smm = y.mm * percent;
    y.sem = y.em * percent;
    y.sll = y.ll * percent;
}


Yield operator*(float scale, const Yield& y)
{
    Yield result("total", scale * y.ee, scale * y.dee, 
                          scale * y.mm, scale * y.dmm, 
                          scale * y.em, scale * y.dem, 
                          scale * y.ll, scale * y.dll);
   return result; 
}

Yield operator-(const Yield& y1, const Yield& y2)
{
    Yield result("total", y1.ee - y2.ee, sqrt(y1.dee*y1.dee + y2.dee*y2.dee), 
                          y1.mm - y2.mm, sqrt(y1.dmm*y1.dmm + y2.dmm*y2.dmm), 
                          y1.em - y2.em, sqrt(y1.dem*y1.dem + y2.dem*y2.dem), 
                          y1.ll - y2.ll, sqrt(y1.dll*y1.dll + y2.dll*y2.dll));
   return result; 
}

Yield operator+(const Yield& y1, const Yield& y2)
{
    Yield result("total", y1.ee + y2.ee, sqrt(y1.dee*y1.dee + y2.dee*y2.dee), 
                          y1.mm + y2.mm, sqrt(y1.dmm*y1.dmm + y2.dmm*y2.dmm), 
                          y1.em + y2.em, sqrt(y1.dem*y1.dem + y2.dem*y2.dem), 
                          y1.ll + y2.ll, sqrt(y1.dll*y1.dll + y2.dll*y2.dll));
   return result; 
}



// get the yields per sample

Yield GetSSYield(const std::string sample_name, unsigned int signal_region_num = 0, const std::string output_path = "")
{
    // sample
    //at::Sample::value_type sample = at::GetSampleFromName(sample_name);

    // signal region
    //SignalRegion::value_type signal_region = static_cast<SignalRegion::value_type>(signal_region_num); 

    // hists  

    rt::TH1Container hc(Form("plots/%s/sr%d/%s.root", output_path.c_str(), signal_region_num, sample_name.c_str()));

    pair<double, double> ee = rt::IntegralAndError(hc["h_yield_ee"]);
    pair<double, double> mm = rt::IntegralAndError(hc["h_yield_mm"]);
    pair<double, double> em = rt::IntegralAndError(hc["h_yield_em"]);
    pair<double, double> ll = rt::IntegralAndError(hc["h_yield_ll"]);
    Yield yield(sample_name, ee, mm, em, ll);

    // done
    return yield;
}

// get the fake yields per sample
Yield GetDFYield(const std::string sample_name, unsigned int signal_region_num = 0, const std::string output_path = "")
{
    // hists  
    rt::TH1Container hc(Form("plots/%s/sr%d/%s.root", output_path.c_str(), signal_region_num, sample_name.c_str()));

    pair<double, double> ee(hc["h_df_pred"]->GetBinContent(1), hc["h_df_pred"]->GetBinError(1));
    pair<double, double> mm(hc["h_df_pred"]->GetBinContent(2), hc["h_df_pred"]->GetBinError(2));
    pair<double, double> em(hc["h_df_pred"]->GetBinContent(3), hc["h_df_pred"]->GetBinError(3));
    pair<double, double> ll(hc["h_df_pred"]->GetBinContent(4), hc["h_df_pred"]->GetBinError(4));
    Yield yield("DF", ee, mm, em, ll);

    // done
    return yield;
}

// get the fake yields per sample
Yield GetSFYield(const std::string sample_name, unsigned int signal_region_num = 0, const std::string output_path = "")
{
    // hists  
    rt::TH1Container hc(Form("plots/%s/sr%d/%s.root", output_path.c_str(), signal_region_num, sample_name.c_str()));

    pair<double, double> ee(hc["h_sf_pred"]->GetBinContent(1), hc["h_sf_pred"]->GetBinError(1));
    pair<double, double> mm(hc["h_sf_pred"]->GetBinContent(2), hc["h_sf_pred"]->GetBinError(2));
    pair<double, double> em(hc["h_sf_pred"]->GetBinContent(3), hc["h_sf_pred"]->GetBinError(3));
    pair<double, double> ll(hc["h_sf_pred"]->GetBinContent(4), hc["h_sf_pred"]->GetBinError(4));
    Yield yield("SF", ee, mm, em, ll);

    // done
    return yield;
}

// get the fake yields per sample
Yield GetFakeYield(const std::string sample_name, unsigned int signal_region_num = 0, const std::string output_path = "")
{
    // hists  
    rt::TH1Container hc(Form("plots/%s/sr%d/%s.root", output_path.c_str(), signal_region_num, sample_name.c_str()));

    pair<double, double> ee(hc["h_fake_pred"]->GetBinContent(1), hc["h_fake_pred"]->GetBinError(1));
    pair<double, double> mm(hc["h_fake_pred"]->GetBinContent(2), hc["h_fake_pred"]->GetBinError(2));
    pair<double, double> em(hc["h_fake_pred"]->GetBinContent(3), hc["h_fake_pred"]->GetBinError(3));
    pair<double, double> ll(hc["h_fake_pred"]->GetBinContent(4), hc["h_fake_pred"]->GetBinError(4));
    Yield yield("Fakes", ee, mm, em, ll);

    // done
    return yield;
}

// get the fake yields per sample
Yield GetFlipYield(const std::string sample_name, unsigned int signal_region_num = 0, const std::string output_path = "")
{
    // hists  
    rt::TH1Container hc(Form("plots/%s/sr%d/%s.root", output_path.c_str(), signal_region_num, sample_name.c_str()));

    pair<double, double> ee(hc["h_flip_pred"]->GetBinContent(1), hc["h_flip_pred"]->GetBinError(1));
    pair<double, double> mm(hc["h_flip_pred"]->GetBinContent(2), hc["h_flip_pred"]->GetBinError(2));
    pair<double, double> em(hc["h_flip_pred"]->GetBinContent(3), hc["h_flip_pred"]->GetBinError(3));
    pair<double, double> ll(hc["h_flip_pred"]->GetBinContent(4), hc["h_flip_pred"]->GetBinError(4));
    Yield yield("Flips", ee, mm, em, ll);

    // done
    return yield;
}


// print the yields
void PrintYields(unsigned int signal_region_num = 0, const std::string output_path = "", bool print_latex = false)
{
    Yield yield_data(GetSSYield("data", signal_region_num, output_path));
    Yield yield_sf(GetSFYield("data", signal_region_num, output_path));
    Yield yield_df(GetDFYield("data", signal_region_num, output_path));
    Yield yield_fake(GetFakeYield("data", signal_region_num, output_path));
    Yield yield_flip(GetFlipYield("data", signal_region_num, output_path));
    if (signal_region_num == 2)
    {
        yield_flip = 0.5*GetFlipYield("data", 1, output_path);
        yield_flip.title = "Flips";
    }

    // The order matters for the formated tex table.
    Yield yield_mc("Total MC");
    vector<Yield> yields_bkgd;
    yields_bkgd.push_back(GetSSYield("wz"      , signal_region_num, output_path));
    yields_bkgd.push_back(GetSSYield("zz"      , signal_region_num, output_path));
    yields_bkgd.push_back(GetSSYield("ttg"     , signal_region_num, output_path));
    yields_bkgd.push_back(GetSSYield("ttw"     , signal_region_num, output_path));
    yields_bkgd.push_back(GetSSYield("ttww"    , signal_region_num, output_path));
    yields_bkgd.push_back(GetSSYield("ttz"     , signal_region_num, output_path));
    yields_bkgd.push_back(GetSSYield("wwg"     , signal_region_num, output_path));
    yields_bkgd.push_back(GetSSYield("www"     , signal_region_num, output_path));
    yields_bkgd.push_back(GetSSYield("wwz"     , signal_region_num, output_path));
    yields_bkgd.push_back(GetSSYield("wzz"     , signal_region_num, output_path));
    yields_bkgd.push_back(GetSSYield("zzz"     , signal_region_num, output_path));
    yields_bkgd.push_back(GetSSYield("wgstar2e", signal_region_num, output_path));
    yields_bkgd.push_back(GetSSYield("wgstar2m", signal_region_num, output_path));
    yields_bkgd.push_back(GetSSYield("wgstar2t", signal_region_num, output_path));
    yields_bkgd.push_back(GetSSYield("wmwmqq"  , signal_region_num, output_path));
    yields_bkgd.push_back(GetSSYield("wpwpqq"  , signal_region_num, output_path));
    yields_bkgd.push_back(GetSSYield("ww_ds"   , signal_region_num, output_path));

    // add the backtrounds to get the totol MC and total prediction
    for (size_t i = 0; i != yields_bkgd.size(); i++)
    {
        yield_mc += yields_bkgd[i];
    }
    Yield yield_mc_pred = yield_mc;
    yield_mc_pred.title = "MC Pred";

    // set systematic uncertainties
    SetSysUncertainties(yield_fake   , 0.5);
    SetSysUncertainties(yield_flip   , 0.2);
    SetSysUncertainties(yield_mc_pred, 0.5);

    // total predition
    Yield yield_pred    = yield_mc_pred;
    yield_pred.title    = "pred";
    yield_pred += yield_fake;
    yield_pred += yield_flip;

    // collect all the yields
    vector<Yield> yields;
    for (size_t i = 0; i != yields_bkgd.size(); i++)
    {
        yields.push_back(yields_bkgd[i]);
    }
    yields.push_back(yield_mc);
    yields.push_back(yield_sf);
    yields.push_back(yield_df);
    yields.push_back(yield_fake);
    yields.push_back(yield_flip);
    yields.push_back(yield_mc_pred);
    yields.push_back(yield_pred);
    yields.push_back(yield_data);

    // print the table
    if (print_latex)
    {
        // before table
        string latex("\\begin{table}[ht!]\n"                                       ); 
        latex.append("\\begin{center}\n"                                           ); 
        latex.append("\\begin{tabular}{l|llll} \\hline\\hline\n"                   ); 
        latex.append("source & $ee$ & $\\mu\\mu$ & $e\\mu$ & $\\ell\\ell $ \\\\\n" ); 
        latex.append("\\hline\n"                                                   ); 

        // loop over datasets
        for (size_t i = 0; i != yields.size(); i++)
        {
            Yield& y = yields[i];

            // handle title explicitly 
            string latex_name = y.title;
            if      (y.title == "SF"      ) {latex_name = "SF";          }
            else if (y.title == "DF"      ) {latex_name = "DF";          }
            else if (y.title == "Fakes"   ) {latex_name = "SF + DF";     }
            else if (y.title == "Flips"   ) {latex_name = "Charge Flips";}
            else if (y.title == "Total MC") {latex_name = "Total MC";    }
            else if (y.title == "MC Pred" ) {latex_name = "MC Pred";     }
            else if (y.title == "pred"    ) {latex_name = "Total Pred";  }
            else
            {
                latex_name = at::GetSampleInfo(y.title).latex;
            }

            //if      (y.title == "Fakes"   ) {latex.append(y.GetLatex(latex_name, /*print_sys_err=*/true));} 
            //else if (y.title == "Flips"   ) {latex.append(y.GetLatex(latex_name, /*print_sys_err=*/true));} 
            //else if (y.title == "MC Pred" ) {latex.append(y.GetLatex(latex_name, /*print_sys_err=*/true));} 
            //else if (y.title == "pred"    ) {latex.append(y.GetLatex(latex_name, /*print_sys_err=*/true));} 
            //else                            {latex.append(y.GetLatex(latex_name));}
            latex.append(y.GetLatex(latex_name));
            latex.append(" \\\\\n");

            // add the line between sections
            if (y.title == "zz"      ) {latex.append("\\hline\n"        );} 
            if (y.title == "zzz"     ) {latex.append("\\hline\n"        );} 
            if (y.title == "ww_ds"   ) {latex.append("\\hline\n"        );} 
            if (y.title == "Total MC") {latex.append("\\hline\\hline\n" );} 
            if (y.title == "DF"      ) {latex.append("\\hline\n"        );} 
            if (y.title == "Fakes"   ) {latex.append("\\hline\\hline\n" );} 
            if (y.title == "Flips"   ) {latex.append("\\hline\n"        );} 
            if (y.title == "MC Pred" ) {latex.append("\\hline\\hline\n" );} 
            if (y.title == "pred"    ) {latex.append("\\hline\\hline\n" );} 
        }

        // after table
        latex.append("\\hline\\hline\n" ); 
        latex.append("\\end{tabular}\n" ); 
        latex.append("\\end{center}\n"  ); 
        latex.append("\\end{table}\n"   ); 
        cout << latex << endl;
    }
    else
    {
        CTable t_yields;
        t_yields.useTitle();
        t_yields.setTitle(Form("yields for SS 2012 SR %d (%s)", signal_region_num, ss::GetSignalRegionInfo(signal_region_num).title.c_str()));
        t_yields.setColLabel("ee", 0);
        t_yields.setColLabel("mm", 1);
        t_yields.setColLabel("em", 2);
        t_yields.setColLabel("ll", 3);

        for (size_t i = 0; i != yields.size(); i++)
        {
            const Yield& y = yields[i];

            // handle title explicitly 
            string title = y.title;
            if      (title == "SF"      ) {title = "SF";          }
            else if (title == "DF"      ) {title = "DF";          }
            else if (title == "Fakes"   ) {title = "SF + DF";     }
            else if (title == "Flips"   ) {title = "Charge Flips";}
            else if (title == "Total MC") {title = "Total MC";    }
            else if (title == "pred"    ) {title = "Total Pred";  }

            t_yields.setRowLabel(title, i);
            if (y.title == "data")
            {
                t_yields.setCell(static_cast<int>(y.ee), i, 0);
                t_yields.setCell(static_cast<int>(y.mm), i, 1);
                t_yields.setCell(static_cast<int>(y.em), i, 2);
                t_yields.setCell(static_cast<int>(y.ll), i, 3);
            }
            else 
            {
                t_yields.setCell(rt::pm(y.ee, y.dee, "1.3"), i, 0);
                t_yields.setCell(rt::pm(y.mm, y.dmm, "1.3"), i, 1);
                t_yields.setCell(rt::pm(y.em, y.dem, "1.3"), i, 2);
                t_yields.setCell(rt::pm(y.ll, y.dll, "1.3"), i, 3);
            }
        }
        t_yields.print();
    }

/* uses Ian's table class
    CTable t_yields;
    t_yields.useTitle();
    t_yields.setTitle(Form("yields for SS 2012 SR %d (%s)", signal_region_num, ss::GetSignalRegionInfo(signal_region_num).title.c_str()));
    if (!print_latex)
    {
        t_yields.setColLabel("ee", 0);
        t_yields.setColLabel("mm", 1);
        t_yields.setColLabel("em", 2);
        t_yields.setColLabel("ll", 3);
    }
    else
    {
        t_yields.setColLabel("$ee$"         , 0);
        t_yields.setColLabel("$\\mu\\mu$"   , 1);
        t_yields.setColLabel("$e\\mu$"      , 2);
        t_yields.setColLabel("$\\ell\\ell$" , 3);
    }
    for (size_t i = 0; i != yields.size(); i++)
    {
        const Yield& y = yields[i];

        // handle title explicitly 
        string title = y.title;
        if      (title == "SF"      ) {title = "SF";          }
        else if (title == "DF"      ) {title = "DF";          }
        else if (title == "Fakes"   ) {title = "SF + DF";     }
        else if (title == "Flips"   ) {title = "Charge Flips";}
        else if (title == "Total MC") {title = "Total MC";    }
        else if (title == "pred"    ) {title = "Total Pred";  }
        else if (print_latex)
        {
            title = at::GetSampleInfo(y.title).latex;
        }
        else 
        {
            title = y.title;
        }

        t_yields.setRowLabel(title, i);
        if (y.title == "data")
        {
            t_yields.setCell(static_cast<int>(y.ee), i, 0);
            t_yields.setCell(static_cast<int>(y.mm), i, 1);
            t_yields.setCell(static_cast<int>(y.em), i, 2);
            t_yields.setCell(static_cast<int>(y.ll), i, 3);
        }
        else 
        {
            t_yields.setCell(rt::pm(y.ee, y.dee, "1.3"), i, 0);
            t_yields.setCell(rt::pm(y.mm, y.dmm, "1.3"), i, 1);
            t_yields.setCell(rt::pm(y.em, y.dem, "1.3"), i, 2);
            t_yields.setCell(rt::pm(y.ll, y.dll, "1.3"), i, 3);
        }
    }
    
    if (print_latex)
    {
        t_yields.printTex();
    }
    else
    {
        t_yields.print();
    }
*/
}

// print the summary table 
void PrintSummaryYields(const std::string output_path = "", bool print_latex = false)
{
    // table for output
    CTable t_yields;
    t_yields.useTitle();
    t_yields.setTitle("summary table for SS 2012 yields and background predictions");

    // fill the columns
    for (unsigned int signal_region_num = 0; signal_region_num != 9; signal_region_num++)
    {
        Yield yield_data(GetSSYield  ("data", signal_region_num, output_path));
        Yield yield_sf  (GetSFYield  ("data", signal_region_num, output_path));
        Yield yield_df  (GetDFYield  ("data", signal_region_num, output_path));
        Yield yield_fake(GetFakeYield("data", signal_region_num, output_path));
        Yield yield_flip(GetFlipYield("data", signal_region_num, output_path));
        if (signal_region_num == 2)
        {
            yield_flip = 0.5*GetFlipYield("data", 1, output_path);
            yield_flip.title = "Flips";
        }

        Yield yield_mc("total MC");
        vector<Yield> yields_bkgd;
        yields_bkgd.push_back(GetSSYield("wz"      , signal_region_num, output_path));
        yields_bkgd.push_back(GetSSYield("zz"      , signal_region_num, output_path));
        yields_bkgd.push_back(GetSSYield("ttg"     , signal_region_num, output_path));
        yields_bkgd.push_back(GetSSYield("ttw"     , signal_region_num, output_path));
        yields_bkgd.push_back(GetSSYield("ttww"    , signal_region_num, output_path));
        yields_bkgd.push_back(GetSSYield("ttz"     , signal_region_num, output_path));
        yields_bkgd.push_back(GetSSYield("wwg"     , signal_region_num, output_path));
        yields_bkgd.push_back(GetSSYield("www"     , signal_region_num, output_path));
        yields_bkgd.push_back(GetSSYield("wwz"     , signal_region_num, output_path));
        yields_bkgd.push_back(GetSSYield("wzz"     , signal_region_num, output_path));
        yields_bkgd.push_back(GetSSYield("zzz"     , signal_region_num, output_path));
        yields_bkgd.push_back(GetSSYield("wgstar2e", signal_region_num, output_path));
        yields_bkgd.push_back(GetSSYield("wgstar2m", signal_region_num, output_path));
        yields_bkgd.push_back(GetSSYield("wgstar2t", signal_region_num, output_path));
        yields_bkgd.push_back(GetSSYield("wmwmqq"  , signal_region_num, output_path));
        yields_bkgd.push_back(GetSSYield("wpwpqq"  , signal_region_num, output_path));
        yields_bkgd.push_back(GetSSYield("ww_ds"   , signal_region_num, output_path));

        // add the backtrounds to get the totol MC and total prediction
        for (size_t i = 0; i != yields_bkgd.size(); i++)
        {
            yield_mc += yields_bkgd[i];
        }
        Yield yield_mc_pred = yield_mc;
        yield_mc_pred.title = "MC Pred";

        // set systematic uncertainties
        SetSysUncertainties(yield_fake, 0.5);
        SetSysUncertainties(yield_flip, 0.2);
        SetSysUncertainties(yield_mc  , 0.5);

        // total predition
        Yield yield_pred    = yield_mc_pred;
        yield_pred.title    = "pred";
        yield_pred += yield_fake;
        yield_pred += yield_flip;

        // collect all the yields
        vector<Yield> yields;
        yields.push_back(yield_mc);
        yields.push_back(yield_fake);
        yields.push_back(yield_flip);
        yields.push_back(yield_pred);
        yields.push_back(yield_data);

        // print the table
        t_yields.setColLabel(Form("sr%u", signal_region_num), signal_region_num);
        for (size_t i = 0; i != yields.size(); i++)
        {
            const Yield& y = yields[i];
            t_yields.setRowLabel(y.title, i);
            if (y.title == "data")
            {
                t_yields.setCell(static_cast<int>(y.ll), i, signal_region_num);
            }
            else 
            {
                if (print_latex)
                {
                    t_yields.setCell(Form("%1.2f $\\pm$ %1.2f", y.ll, y.dll), i, signal_region_num);
                }
                else
                {
                    t_yields.setCell(rt::pm(y.ll, y.dll, "1.2"), i, signal_region_num);
                }
            }
        }
        //t_yields.saveTex("test.tex");
    } // loop over SRs

    // print the table
    if (print_latex)
    {
        t_yields.printTex();
    }
    else
    {
        t_yields.print();
    }
}
