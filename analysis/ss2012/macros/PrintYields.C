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
        , mm  (0.0)
        , dmm (0.0)
        , em  (0.0)
        , dem (0.0)
        , ll  (0.0)
        , dll (0.0)
    {}

    Yield(const std::string& title_) 
        : title(title_)
        , ee  (0.0)
        , dee (0.0)
        , mm  (0.0)
        , dmm (0.0)
        , em  (0.0)
        , dem (0.0)
        , ll  (0.0)
        , dll (0.0)
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
        , mm  (mm_.first)
        , dmm (mm_.second)
        , em  (em_.first)
        , dem (em_.second)
        , ll (ll_.first)
        , dll(ll_.second)
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
        , mm  (mm_)  
        , dmm (dmm_) 
        , em  (em_)  
        , dem (dem_) 
        , ll (ll_) 
        , dll(dll_)
    {}

    std::string title;
    float ee;
    float dee;
    float mm;
    float dmm;
    float em;
    float dem;
    float ll;
    float dll;

    // methods:
    Yield& operator+=(const Yield& y);
    Yield& operator-=(const Yield& y);

    void Print()
    {
        if (rt::string_contains(title, "data"))
        {
            const char* format = "%15s ee: %15.0f mm: %15.0f em: %15.0f ll: %15.0f";
            cout << Form(format, title.c_str(), ee, mm, em, ll) << endl;
        }
        else
        {
            const char* format = "%15s ee: %2.3f +/- %2.3f mm: %2.3f +/- %2.3f em: %2.3f +/- %2.3f ll: %2.3f +/- %2.3f";
            cout << Form(format, title.c_str(), ee, dee, mm, dmm, em, dem, ll, dll) << endl;
        }
    }
};

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
    return *this; 
}

void SetErrorsToBogus(Yield& y)
{
    y.dee = 999;
    y.dmm = 999;
    y.dem = 999;
    y.dll = 999;
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
    //yield.Print();

    // done
    return yield;
}

// get the fake yields per sample
Yield GetDFYield(const std::string sample_name, unsigned int signal_region_num = 0, const std::string output_path = "")
{
    // hists  
    rt::TH1Container hc(Form("plots/%s/sr%d/%s.root", output_path.c_str(), signal_region_num, sample_name.c_str()));

    pair<double, double> ee(hc["h_df_pred"]->GetBinContent(1), hc["h_df_pred"]->GetBinError(1));
    pair<double, double> em(hc["h_df_pred"]->GetBinContent(2), hc["h_df_pred"]->GetBinError(2));
    pair<double, double> mm(hc["h_df_pred"]->GetBinContent(3), hc["h_df_pred"]->GetBinError(3));
    pair<double, double> ll(hc["h_df_pred"]->GetBinContent(4), hc["h_df_pred"]->GetBinError(4));
    Yield yield("DF", ee, mm, em, ll);
    yield.title = "DF";

    // done
    return yield;
}

// get the fake yields per sample
Yield GetSFYield(const std::string sample_name, unsigned int signal_region_num = 0, const std::string output_path = "")
{
    // hists  
    rt::TH1Container hc(Form("plots/%s/sr%d/%s.root", output_path.c_str(), signal_region_num, sample_name.c_str()));

    pair<double, double> ee(hc["h_sf_pred"]->GetBinContent(1), hc["h_sf_pred"]->GetBinError(1));
    pair<double, double> em(hc["h_sf_pred"]->GetBinContent(2), hc["h_sf_pred"]->GetBinError(2));
    pair<double, double> mm(hc["h_sf_pred"]->GetBinContent(3), hc["h_sf_pred"]->GetBinError(3));
    pair<double, double> ll(hc["h_sf_pred"]->GetBinContent(4), hc["h_sf_pred"]->GetBinError(4));
    Yield yield("SF", ee, mm, em, ll);
    yield.title = "SF";

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
    yield.title = "Fakes";

    // done
    return yield;
}

// get the fake yields per sample
Yield GetFlipYield(const std::string sample_name, unsigned int signal_region_num = 0, const std::string output_path = "")
{
    // hists  
    rt::TH1Container hc(Form("plots/%s/sr%d/%s.root", output_path.c_str(), signal_region_num, sample_name.c_str()));

    //pair<double, double> ee = rt::IntegralAndError(hc["h_flip_pred_ee"]);
    //pair<double, double> mm = rt::IntegralAndError(hc["h_flip_pred_mm"]);
    //pair<double, double> em = rt::IntegralAndError(hc["h_flip_pred_em"]);
    //pair<double, double> ll = rt::IntegralAndError(hc["h_flip_pred_ll"]);
    pair<double, double> ee(hc["h_flip_pred"]->GetBinContent(1), hc["h_flip_pred"]->GetBinError(1));
    pair<double, double> mm(hc["h_flip_pred"]->GetBinContent(2), hc["h_flip_pred"]->GetBinError(2));
    pair<double, double> em(hc["h_flip_pred"]->GetBinContent(3), hc["h_flip_pred"]->GetBinError(3));
    pair<double, double> ll(hc["h_flip_pred"]->GetBinContent(4), hc["h_flip_pred"]->GetBinError(4));
    Yield yield("Flips", ee, mm, em, ll);
    yield.title = "Flips";

    // done
    return yield;
}


// print the yields
void PrintYields(unsigned int signal_region_num = 0, const std::string output_path = "")
{
    Yield yield_data(GetSSYield("data", signal_region_num, output_path));
    Yield yield_sf(GetSFYield("data", signal_region_num, output_path));
    Yield yield_df(GetDFYield("data", signal_region_num, output_path));
    Yield yield_fake(GetFakeYield("data", signal_region_num, output_path));
    Yield yield_flip(GetFlipYield("data", signal_region_num, output_path));

    // special case for SR2
    if (signal_region_num==2)
    {
        yield_flip = 0.5*GetFlipYield("data", 1, output_path);
        yield_flip.title = "Flip";
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

    for (size_t i = 0; i != yields_bkgd.size(); i++)
    {
        yield_mc += yields_bkgd[i];
        //yields_bkgd[i].Print(); 
    }
    Yield yield_pred = yield_mc;
    yield_pred.title = "pred";
    yield_pred += yield_fake;
    yield_pred += yield_flip;

    // set pred errors to zero to we know they are wrong 
    //SetErrorsToBogus(yield_sf);
    //SetErrorsToBogus(yield_df);
    //SetErrorsToBogus(yield_fake);
    //SetErrorsToBogus(yield_pred);

    // collect all the yields
    vector<Yield> yields;
    for (size_t i = 0; i != yields_bkgd.size(); i++)
    {
        yields.push_back(yields_bkgd[i]);
    }
    yields.push_back(yield_sf);
    yields.push_back(yield_df);
    yields.push_back(yield_fake);
    yields.push_back(yield_flip);
    yields.push_back(yield_mc);
    yields.push_back(yield_pred);
    yields.push_back(yield_data);

    // print the table
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
        t_yields.setRowLabel(y.title, i);
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
    //t_yields.saveTex("test.tex");
}

// print the summary table 
void PrintSummaryYields(const std::string output_path = "")
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

        // special case for SR2
        if (signal_region_num==2)
        {
            yield_flip = 0.5*GetFlipYield("data", 1, output_path);
            yield_flip.title = "Flip";
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
        for (size_t i = 0; i != yields_bkgd.size(); i++)
        {
            yield_mc += yields_bkgd[i];
        }
        Yield yield_pred = yield_mc;
        yield_pred.title = "pred";
        yield_pred += yield_fake;
        yield_pred += yield_flip;

        // collect all the yields
        vector<Yield> yields;
        yields.push_back(yield_fake);
        yields.push_back(yield_flip);
        yields.push_back(yield_mc);
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
                t_yields.setCell(rt::pm(y.ll, y.dll, "1.2"), i, signal_region_num);
            }
        }
        //t_yields.saveTex("test.tex");
    } // loop over SRs

    // print the table
    t_yields.print();
}
