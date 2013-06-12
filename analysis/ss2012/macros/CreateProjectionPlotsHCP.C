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

    Yield
    (
        const std::string& title_, 
        float ee_, 
        float dee_, 
        float see_, 
        float mm_, 
        float dmm_, 
        float smm_, 
        float em_, 
        float dem_, 
        float sem_, 
        float ll_,
        float dll_,
        float sll_ 
    )
        : title(title_)
        , ee  (ee_)
        , dee (dee_) 
        , see (see_)
        , mm  (mm_)  
        , dmm (dmm_) 
        , smm (smm_)
        , em  (em_)  
        , dem (dem_) 
        , sem (sem_)
        , ll (ll_) 
        , dll(dll_)
        , sll(sll_)
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

    float tee() const {return (sqrt(see*see + dee*dee));}
    float tmm() const {return (sqrt(smm*smm + dmm*dmm));}
    float tem() const {return (sqrt(sem*sem + dem*dem));}
    float tll() const {return (sqrt(sll*sll + dll*dll));}

    std::string GetLatex(const std::string& latex = "", bool print_sys_err = false) const;
    void Print(bool print_sys_err = false) const;

};

float DetermineError(float v1, float v2, float e1, float e2)
{
    // test for zero yield condition
    if (rt::is_zero(v1) && rt::is_zero(v2))
    {
        return std::max(e1, e2);    
    }
    else if (rt::is_zero(v1) && not rt::is_zero(v2))
    {
        return e2;
    }
    else if (not rt::is_zero(v1) && rt::is_zero(v2))
    {
        return e1;
    }
    else
    {
        return sqrt(e1*e1 + e2*e2);
    }
}

// non member methods
Yield operator-(const Yield& y1, const Yield& y2)
{
    Yield result("total", y1.ee - y2.ee, DetermineError(y1.ee, y2.ee, y1.dee, y2.dee), DetermineError(y1.ee, y2.ee, y1.see, y2.see), 
                          y1.mm - y2.mm, DetermineError(y1.mm, y2.mm, y1.dmm, y2.dmm), DetermineError(y1.mm, y2.mm, y1.smm, y2.smm), 
                          y1.em - y2.em, DetermineError(y1.em, y2.em, y1.dem, y2.dem), DetermineError(y1.em, y2.em, y1.sem, y2.sem), 
                          y1.ll - y2.ll, DetermineError(y1.ll, y2.ll, y1.dll, y2.dll), DetermineError(y1.ll, y2.ll, y1.sll, y2.sll));
    return result; 
}

Yield operator+(const Yield& y1, const Yield& y2)
{
    Yield result("total", y1.ee + y2.ee, DetermineError(y1.ee, y2.ee, y1.dee, y2.dee), DetermineError(y1.ee, y2.ee, y1.see, y2.see), 
                          y1.mm + y2.mm, DetermineError(y1.mm, y2.mm, y1.dmm, y2.dmm), DetermineError(y1.mm, y2.mm, y1.smm, y2.smm), 
                          y1.em + y2.em, DetermineError(y1.em, y2.em, y1.dem, y2.dem), DetermineError(y1.em, y2.em, y1.sem, y2.sem), 
                          y1.ll + y2.ll, DetermineError(y1.ll, y2.ll, y1.dll, y2.dll), DetermineError(y1.ll, y2.ll, y1.sll, y2.sll));
    return result; 
}

// add the uncertainties not worrying about whether the value is zero
Yield AddUncertaintiesAbsolute(const Yield& y1, const Yield& y2)
{
    Yield result(y1.title, y1.ee + y2.ee, sqrt(y1.dee*y1.dee + y2.dee*y2.dee), sqrt(y1.see*y1.see + y2.see*y2.see), 
                           y1.mm + y2.mm, sqrt(y1.dmm*y1.dmm + y2.dmm*y2.dmm), sqrt(y1.smm*y1.smm + y2.smm*y2.smm), 
                           y1.em + y2.em, sqrt(y1.dem*y1.dem + y2.dem*y2.dem), sqrt(y1.sem*y1.sem + y2.sem*y2.sem), 
                           y1.ll + y2.ll, sqrt(y1.dll*y1.dll + y2.dll*y2.dll), sqrt(y1.sll*y1.sll + y2.sll*y2.sll));
    return result; 
}

// members
Yield& Yield::operator+=(const Yield& y)
{
    //ee  += y.ee;
    //mm  += y.mm;
    //em  += y.em;
    //ll  += y.ll;
    //dee = sqrt(dee*dee + y.dee*y.dee); 
    //dmm = sqrt(dmm*dmm + y.dmm*y.dmm);
    //dem = sqrt(dem*dem + y.dem*y.dem);
    //dll = sqrt(dll*dll + y.dll*y.dll);
    //see = sqrt(see*see + y.see*y.see); 
    //smm = sqrt(smm*smm + y.smm*y.smm);
    //sem = sqrt(sem*sem + y.sem*y.sem);
    //sll = sqrt(sll*sll + y.sll*y.sll);
    string title_temp = this->title;
    Yield temp_yield = (*this) + y;
    *this = temp_yield;
    this->title = title_temp;
    return *this; 
}

Yield& Yield::operator-=(const Yield& y)
{
    //ee  -= y.ee;
    //mm  -= y.mm;
    //em  -= y.em;
    //ll  -= y.ll;
    //dee = sqrt(dee*dee + y.dee*y.dee); 
    //dmm = sqrt(dmm*dmm + y.dmm*y.dmm);
    //dem = sqrt(dem*dem + y.dem*y.dem);
    //dll = sqrt(dll*dll + y.dll*y.dll);
    //see = sqrt(see*see + y.see*y.see); 
    //smm = sqrt(smm*smm + y.smm*y.smm);
    //sem = sqrt(sem*sem + y.sem*y.sem);
    //sll = sqrt(sll*sll + y.sll*y.sll);
    //return *this; 
    string title_temp = this->title;
    Yield temp_yield = (*this) - y;
    *this = temp_yield;
    this->title = title_temp;
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
            const char* format = "%35s & %5.2f $\\pm$ %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f $\\pm$ %5.2f";
            result = Form(format, not latex.empty() ? latex.c_str() : title.c_str(), ee, dee, see, mm, dmm, smm, em, dem, sem, ll, dll, sll);
            if (rt::string_contains(title, "Flip"))
            {
                format = "%35s & %5.2f $\\pm$ %5.2f $\\pm$ %5.2f & - $\\pm$ - $\\pm$ - & %5.2f $\\pm$ %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f $\\pm$ %5.2f";
                result = Form(format, not latex.empty() ? latex.c_str() : title.c_str(), ee, dee, see, em, dem, sem, ll, dll, sll);
            }
        }
        else
        {
            const char* format = "%35s & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f";
            result = Form(format, not latex.empty() ? latex.c_str() : title.c_str(), ee, tee(), mm, tmm(), em, tem(), ll, tll());
            if (rt::string_contains(title, "Flip"))
            {
                format = "%35s & %5.2f $\\pm$ %5.2f & - $\\pm$ - & %5.2f $\\pm$ %5.2f & %5.2f $\\pm$ %5.2f";
                result = Form(format, not latex.empty() ? latex.c_str() : title.c_str(), ee, tee(), mm, tmm(), em, tem(), ll, tll());
            }
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
            const char* format = "%15s ee: %2.2f +/- %2.2f +/- %2.2f mm: %2.2f +/- %2.2f +/- %2.2f em: %2.2f +/- %2.2f +/- %2.2f ll: %2.2f +/- %2.2f +/- %2.2f";
            cout << Form(format, title.c_str(), ee, dee, see, mm, dmm, smm, em, dem, sem, ll, dll, sll) << endl;
        }
        else
        {
            const char* format = "%15s ee: %2.2f +/- %2.2f mm: %2.2f +/- %2.2f em: %2.2f +/- %2.2f ll: %2.2f +/- %2.2f";
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


// container getter 
rt::TH1Container GetSampleHists(const std::string sample_name, unsigned int signal_region_num, int charge_option, const std::string output_path)
{
    // charge option (1 == ++, -1 == --)
    std::string charge_stem = "";
    switch (charge_option)
    {
        case  1: charge_stem = "_pp"; break;
        case -1: charge_stem = "_mm"; break;
        default: {/*do nothing*/}
    }

    // hists  
    //std::string sr = ss::GetSignalRegionInfo(static_cast<ss::SignalRegion::value_type>(signal_region_num), ss::AnalysisType::hcp, ss::SignalRegionType::inclusive).name;
    const string filename = Form("plots/%s/sr%d/%s%s.root", output_path.c_str(), (signal_region_num), sample_name.c_str(), charge_stem.c_str());
    cout << "loading = " << filename << endl;
    rt::TH1Container hc(filename);
    return hc;
}

// get the yields per sample
Yield GetSSYield(const std::string sample_name, unsigned int signal_region_num = 0, int charge_option = 0, const std::string output_path = "")
{
    // hists  
    rt::TH1Container hc = GetSampleHists(sample_name, signal_region_num, charge_option, output_path);
    pair<double, double> ee = rt::IntegralAndError(hc["h_yield_ee"]);
    pair<double, double> mm = rt::IntegralAndError(hc["h_yield_mm"]);
    pair<double, double> em = rt::IntegralAndError(hc["h_yield_em"]);
    pair<double, double> ll = rt::IntegralAndError(hc["h_yield_ll"]);
    Yield yield(sample_name, ee, mm, em, ll);

    // done
    return yield;
}

// get the fake yields per sample
Yield GetDFYield(const std::string sample_name, unsigned int signal_region_num = 0, int charge_option = 0, const std::string output_path = "")
{
    // hists  
    rt::TH1Container hc = GetSampleHists(sample_name, signal_region_num, charge_option, output_path);
    pair<double, double> ee(hc["h_df_pred"]->GetBinContent(1), hc["h_df_pred"]->GetBinError(1));
    pair<double, double> mm(hc["h_df_pred"]->GetBinContent(2), hc["h_df_pred"]->GetBinError(2));
    pair<double, double> em(hc["h_df_pred"]->GetBinContent(3), hc["h_df_pred"]->GetBinError(3));
    pair<double, double> ll(hc["h_df_pred"]->GetBinContent(4), hc["h_df_pred"]->GetBinError(4));
    Yield yield("DF", ee, mm, em, ll);

    // done
    return yield;
}

// get the fake yields per sample
Yield GetSFYield(const std::string sample_name, unsigned int signal_region_num = 0, int charge_option = 0, const std::string output_path = "")
{
    // hists  
    rt::TH1Container hc = GetSampleHists(sample_name, signal_region_num, charge_option, output_path);
    pair<double, double> ee(hc["h_sf_pred"]->GetBinContent(1), hc["h_sf_pred"]->GetBinError(1));
    pair<double, double> mm(hc["h_sf_pred"]->GetBinContent(2), hc["h_sf_pred"]->GetBinError(2));
    pair<double, double> em(hc["h_sf_pred"]->GetBinContent(3), hc["h_sf_pred"]->GetBinError(3));
    pair<double, double> ll(hc["h_sf_pred"]->GetBinContent(4), hc["h_sf_pred"]->GetBinError(4));
    Yield yield("SF", ee, mm, em, ll);

    // done
    return yield;
}

// get the fake yields per sample
Yield GetFakeYield(const std::string sample_name, unsigned int signal_region_num = 0, int charge_option = 0, const std::string output_path = "")
{
    // hists  
    rt::TH1Container hc = GetSampleHists(sample_name, signal_region_num, charge_option, output_path);
    pair<double, double> ee(hc["h_fake_pred"]->GetBinContent(1), hc["h_fake_pred"]->GetBinError(1));
    pair<double, double> mm(hc["h_fake_pred"]->GetBinContent(2), hc["h_fake_pred"]->GetBinError(2));
    pair<double, double> em(hc["h_fake_pred"]->GetBinContent(3), hc["h_fake_pred"]->GetBinError(3));
    pair<double, double> ll(hc["h_fake_pred"]->GetBinContent(4), hc["h_fake_pred"]->GetBinError(4));
    Yield yield("Fakes", ee, mm, em, ll);

    // done
    return yield;
}

// get the fake yields per sample
Yield GetFlipYield(const std::string sample_name, unsigned int signal_region_num = 0, int charge_option = 0, const std::string output_path = "")
{
    // hists  
    rt::TH1Container hc = GetSampleHists(sample_name, signal_region_num, charge_option, output_path);
    pair<double, double> ee(hc["h_flip_pred"]->GetBinContent(1), hc["h_flip_pred"]->GetBinError(1));
    pair<double, double> mm(hc["h_flip_pred"]->GetBinContent(2), hc["h_flip_pred"]->GetBinError(2));
    pair<double, double> em(hc["h_flip_pred"]->GetBinContent(3), hc["h_flip_pred"]->GetBinError(3));
    pair<double, double> ll(hc["h_flip_pred"]->GetBinContent(4), hc["h_flip_pred"]->GetBinError(4));
    Yield yield("Flips", ee, mm, em, ll);

    // done
    return yield;
}


// print the summary table 
void CreateProjPlots(const std::string& output_path = "", int charge_option = 0, const std::string& suffix = "png")
{
/*     string title = "CMS Preliminary, #sqrt{s}=8 TeV, L_{int} = 10.5 fb^{-1}"; */
    string title = "CMS, #sqrt{s}=8 TeV, L_{int} = 10.5 fb^{-1}";

    const int n_met_bins = 4; const float met_bins[] = {0, 30, 50, 120, 200};
    const int n_ht_bins = 3;  const float ht_bins [] = {80, 200, 320, 800};

    // table for output
    TH1F* h_data_met = new TH1F("h_data_met", Form("%s;E^{miss}_{T} (GeV);Events/10 GeV", title.c_str()), n_met_bins, met_bins);
    TH1F* h_fake_met = new TH1F("h_fake_met", Form("%s;E^{miss}_{T} (GeV);Events/10 GeV", title.c_str()), n_met_bins, met_bins);
    TH1F* h_flip_met = new TH1F("h_flip_met", Form("%s;E^{miss}_{T} (GeV);Events/10 GeV", title.c_str()), n_met_bins, met_bins);
    TH1F* h_pred_met = new TH1F("h_pred_met", Form("%s;E^{miss}_{T} (GeV);Events/10 GeV", title.c_str()), n_met_bins, met_bins);
    TH1F* h_mc_met   = new TH1F("h_mc_met"  , Form("%s;E^{miss}_{T} (GeV);Events/10 GeV", title.c_str()), n_met_bins, met_bins);

    TH1F* h_data_ht = new TH1F("h_data_ht", Form("%s;H_{T} (GeV);Events/10 GeV", title.c_str()), n_ht_bins, ht_bins);
    TH1F* h_fake_ht = new TH1F("h_fake_ht", Form("%s;H_{T} (GeV);Events/10 GeV", title.c_str()), n_ht_bins, ht_bins);
    TH1F* h_flip_ht = new TH1F("h_flip_ht", Form("%s;H_{T} (GeV);Events/10 GeV", title.c_str()), n_ht_bins, ht_bins);
    TH1F* h_pred_ht = new TH1F("h_pred_ht", Form("%s;H_{T} (GeV);Events/10 GeV", title.c_str()), n_ht_bins, ht_bins);
    TH1F* h_mc_ht   = new TH1F("h_mc_ht"  , Form("%s;H_{T} (GeV);Events/10 GeV", title.c_str()), n_ht_bins, ht_bins);

    TH1F* h_data_njets = new TH1F("h_data_njets", Form("%s;number of jets;Events", title.c_str()), 8, 1.5, 9.5);
    TH1F* h_fake_njets = new TH1F("h_fake_njets", Form("%s;number of jets;Events", title.c_str()), 8, 1.5, 9.5);
    TH1F* h_flip_njets = new TH1F("h_flip_njets", Form("%s;number of jets;Events", title.c_str()), 8, 1.5, 9.5);
    TH1F* h_pred_njets = new TH1F("h_pred_njets", Form("%s;number of jets;Events", title.c_str()), 8, 1.5, 9.5);
    TH1F* h_mc_njets   = new TH1F("h_mc_njets"  , Form("%s;number of jets;Events", title.c_str()), 8, 1.5, 9.5);

    TH1F* h_data_nbtags = new TH1F("h_data_nbtags", Form("%s;number of b-tagged jets;Events", title.c_str()), 5, 1.5, 6.5);
    TH1F* h_fake_nbtags = new TH1F("h_fake_nbtags", Form("%s;number of b-tagged jets;Events", title.c_str()), 5, 1.5, 6.5);
    TH1F* h_flip_nbtags = new TH1F("h_flip_nbtags", Form("%s;number of b-tagged jets;Events", title.c_str()), 5, 1.5, 6.5);
    TH1F* h_pred_nbtags = new TH1F("h_pred_nbtags", Form("%s;number of b-tagged jets;Events", title.c_str()), 5, 1.5, 6.5);
    TH1F* h_mc_nbtags   = new TH1F("h_mc_nbtags"  , Form("%s;number of b-tagged jets;Events", title.c_str()), 5, 1.5, 6.5);

    TH1F* h_data_pt1 = new TH1F("h_data_pt1", Form("%s;p^{lep1}_{T} (GeV);Events", title.c_str()), 10, 0.0, 200.0);
    TH1F* h_fake_pt1 = new TH1F("h_fake_pt1", Form("%s;p^{lep1}_{T} (GeV);Events", title.c_str()), 10, 0.0, 200.0);
    TH1F* h_flip_pt1 = new TH1F("h_flip_pt1", Form("%s;p^{lep1}_{T} (GeV);Events", title.c_str()), 10, 0.0, 200.0);
    TH1F* h_pred_pt1 = new TH1F("h_pred_pt1", Form("%s;p^{lep1}_{T} (GeV);Events", title.c_str()), 10, 0.0, 200.0);
    TH1F* h_mc_pt1   = new TH1F("h_mc_pt1"  , Form("%s;p^{lep1}_{T} (GeV);Events", title.c_str()), 10, 0.0, 200.0);

    TH1F* h_data_pt2 = new TH1F("h_data_pt2", Form("%s;p^{lep2}_{T} (GeV);Events", title.c_str()), 10, 0.0, 200.0);
    TH1F* h_fake_pt2 = new TH1F("h_fake_pt2", Form("%s;p^{lep2}_{T} (GeV);Events", title.c_str()), 10, 0.0, 200.0);
    TH1F* h_flip_pt2 = new TH1F("h_flip_pt2", Form("%s;p^{lep2}_{T} (GeV);Events", title.c_str()), 10, 0.0, 200.0);
    TH1F* h_pred_pt2 = new TH1F("h_pred_pt2", Form("%s;p^{lep2}_{T} (GeV);Events", title.c_str()), 10, 0.0, 200.0);
    TH1F* h_mc_pt2   = new TH1F("h_mc_pt2"  , Form("%s;p^{lep2}_{T} (GeV);Events", title.c_str()), 10, 0.0, 200.0);

    // fill the columns
    int bin = 1;
    for (unsigned int signal_region_num = 16; signal_region_num != 56; signal_region_num++)
    {
        cout << "bin = " << bin << endl;
        Yield yield_data(GetSSYield  ("data", signal_region_num, charge_option, output_path));
        Yield yield_sf  (GetSFYield  ("data", signal_region_num, charge_option, output_path));
        Yield yield_df  (GetDFYield  ("data", signal_region_num, charge_option, output_path));
        Yield yield_fake(GetFakeYield("data", signal_region_num, charge_option, output_path));
        Yield yield_flip(GetFlipYield("data", signal_region_num, charge_option, output_path));
        if (signal_region_num == 2 || signal_region_num == 9)
        {
            yield_flip = 0.5*GetFlipYield("data", 1, 0, output_path);
            yield_flip.title = "Flips";
        }

        // handle ++/-- charge flip case
        if (charge_option == 1 || charge_option == -1)
        {
            yield_flip = 0.5*GetFlipYield("data", signal_region_num, /*charge_option=*/0, output_path);
            yield_flip.title = "Flips";
        }

        Yield yield_mc("total MC");
        vector<Yield> yields_bkgd;
        yields_bkgd.push_back(GetSSYield("wz"      , signal_region_num, charge_option, output_path));
        yields_bkgd.push_back(GetSSYield("zz"      , signal_region_num, charge_option, output_path));
        yields_bkgd.push_back(GetSSYield("ttg"     , signal_region_num, charge_option, output_path));
        yields_bkgd.push_back(GetSSYield("ttw"     , signal_region_num, charge_option, output_path));
        yields_bkgd.push_back(GetSSYield("ttww"    , signal_region_num, charge_option, output_path));
        yields_bkgd.push_back(GetSSYield("ttz"     , signal_region_num, charge_option, output_path));
        yields_bkgd.push_back(GetSSYield("wwg"     , signal_region_num, charge_option, output_path));
        yields_bkgd.push_back(GetSSYield("www"     , signal_region_num, charge_option, output_path));
        yields_bkgd.push_back(GetSSYield("wwz"     , signal_region_num, charge_option, output_path));
        yields_bkgd.push_back(GetSSYield("wzz"     , signal_region_num, charge_option, output_path));
        yields_bkgd.push_back(GetSSYield("zzz"     , signal_region_num, charge_option, output_path));
        yields_bkgd.push_back(GetSSYield("wgstar2e", signal_region_num, charge_option, output_path));
        yields_bkgd.push_back(GetSSYield("wgstar2m", signal_region_num, charge_option, output_path));
        yields_bkgd.push_back(GetSSYield("wgstar2t", signal_region_num, charge_option, output_path));
        yields_bkgd.push_back(GetSSYield("wmwmqq"  , signal_region_num, charge_option, output_path));
        yields_bkgd.push_back(GetSSYield("wpwpqq"  , signal_region_num, charge_option, output_path));
        yields_bkgd.push_back(GetSSYield("ww_ds"   , signal_region_num, charge_option, output_path));

        // add the backtrounds to get the totol MC and total prediction
        for (size_t i = 0; i != yields_bkgd.size(); i++)
        {
            yield_mc = AddUncertaintiesAbsolute(yield_mc, yields_bkgd.at(i));
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

        // fill hists
        if (bin <= 4)  // bin 1 - 4
        {
            cout << "creating met plot" << endl;
            float scale = h_data_met->GetBinWidth(bin)/10.0;
            cout << "bin = " << bin << "\t" << "scale = " << scale << endl;
            if(yield_data.ll > 0) h_data_met->SetBinContent(bin, yield_data.ll/scale);
            if(yield_fake.ll > 0) h_fake_met->SetBinContent(bin, yield_fake.ll/scale);
            if(yield_flip.ll > 0) h_flip_met->SetBinContent(bin, yield_flip.ll/scale);
            if(yield_pred.ll > 0) h_pred_met->SetBinContent(bin, yield_pred.ll/scale);
            if(yield_mc.ll   > 0) h_mc_met->SetBinContent  (bin, yield_mc.ll  /scale);
                                  
            if(yield_data.ll > 0) h_data_met->SetBinError(bin, yield_data.dll/scale);
            if(yield_fake.ll > 0) h_fake_met->SetBinError(bin, yield_fake.tll()/scale);
            if(yield_flip.ll > 0) h_flip_met->SetBinError(bin, yield_flip.tll()/scale);
            if(yield_pred.ll > 0) h_pred_met->SetBinError(bin, yield_pred.tll()/scale);
            if(yield_mc.ll   > 0) h_mc_met->SetBinError  (bin, yield_mc.tll()  /scale);
        }
        else if (bin >= 5 && bin <= 7)  // bin 5 - 7 
        {
            cout << "creating ht plot" << endl;
            int ht_bin = bin-4;
            float scale = h_data_ht->GetBinWidth(ht_bin)/10.0;
            cout << "bin = " << ht_bin << "\t" << "scale = " << scale << endl;
            if(yield_data.ll > 0) h_data_ht->SetBinContent(ht_bin, yield_data.ll/scale);
            if(yield_fake.ll > 0) h_fake_ht->SetBinContent(ht_bin, yield_fake.ll/scale);
            if(yield_flip.ll > 0) h_flip_ht->SetBinContent(ht_bin, yield_flip.ll/scale);
            if(yield_pred.ll > 0) h_pred_ht->SetBinContent(ht_bin, yield_pred.ll/scale);
            if(yield_mc.ll   > 0) h_mc_ht->SetBinContent  (ht_bin, yield_mc.ll  /scale);

            if(yield_data.ll > 0) h_data_ht->SetBinError(ht_bin, yield_data.dll  /scale);
            if(yield_fake.ll > 0) h_fake_ht->SetBinError(ht_bin, yield_fake.tll()/scale);
            if(yield_flip.ll > 0) h_flip_ht->SetBinError(ht_bin, yield_flip.tll()/scale);
            if(yield_pred.ll > 0) h_pred_ht->SetBinError(ht_bin, yield_pred.tll()/scale);
            if(yield_mc.ll   > 0) h_mc_ht->SetBinError  (ht_bin, yield_mc.tll()    /scale);
        }
        else if (bin >= 8 && bin <= 15)  // bin 8 - 15 
        {
            cout << "creating njets plot" << endl;
            int njet_bin = bin-7;
            if(yield_data.ll > 0) h_data_njets->SetBinContent(njet_bin, yield_data.ll);
            if(yield_fake.ll > 0) h_fake_njets->SetBinContent(njet_bin, yield_fake.ll);
            if(yield_flip.ll > 0) h_flip_njets->SetBinContent(njet_bin, yield_flip.ll);
            if(yield_pred.ll > 0) h_pred_njets->SetBinContent(njet_bin, yield_pred.ll);
            if(yield_mc.ll   > 0) h_mc_njets->SetBinContent  (njet_bin, yield_mc.ll  );

            if(yield_data.ll > 0) h_data_njets->SetBinError(njet_bin, yield_data.dll  );
            if(yield_fake.ll > 0) h_fake_njets->SetBinError(njet_bin, yield_fake.tll());
            if(yield_flip.ll > 0) h_flip_njets->SetBinError(njet_bin, yield_flip.tll());
            if(yield_pred.ll > 0) h_pred_njets->SetBinError(njet_bin, yield_pred.tll());
            if(yield_mc.ll   > 0) h_mc_njets->SetBinError  (njet_bin, yield_mc.tll()  );
        }
        else if (bin >= 16 && bin <= 21)  // bin 17 - 21 
        {
            cout << "creating nbtags plot" << endl;
            int nbtag_bin = bin-15;
            if(yield_data.ll > 0) h_data_nbtags->SetBinContent(nbtag_bin, yield_data.ll);
            if(yield_fake.ll > 0) h_fake_nbtags->SetBinContent(nbtag_bin, yield_fake.ll);
            if(yield_flip.ll > 0) h_flip_nbtags->SetBinContent(nbtag_bin, yield_flip.ll);
            if(yield_pred.ll > 0) h_pred_nbtags->SetBinContent(nbtag_bin, yield_pred.ll);
            if(yield_mc.ll   > 0) h_mc_nbtags->SetBinContent  (nbtag_bin, yield_mc.ll  );

            if(yield_data.ll > 0) h_data_nbtags->SetBinError(nbtag_bin, yield_data.dll  );
            if(yield_fake.ll > 0) h_fake_nbtags->SetBinError(nbtag_bin, yield_fake.tll());
            if(yield_flip.ll > 0) h_flip_nbtags->SetBinError(nbtag_bin, yield_flip.tll());
            if(yield_pred.ll > 0) h_pred_nbtags->SetBinError(nbtag_bin, yield_pred.tll());
            if(yield_mc.ll   > 0) h_mc_nbtags->SetBinError  (nbtag_bin, yield_mc.tll()  );
        }
        else if (bin >= 22 && bin <= 31)  // bin 22 - 31 
        {
            int pt1_bin = bin-21;
            cout << "creating pt1 plot: " << pt1_bin << endl;
            if(yield_data.ll > 0) h_data_pt1->SetBinContent(pt1_bin, yield_data.ll);
            if(yield_fake.ll > 0) h_fake_pt1->SetBinContent(pt1_bin, yield_fake.ll);
            if(yield_flip.ll > 0) h_flip_pt1->SetBinContent(pt1_bin, yield_flip.ll);
            if(yield_pred.ll > 0) h_pred_pt1->SetBinContent(pt1_bin, yield_pred.ll);
            if(yield_mc.ll   > 0) h_mc_pt1->SetBinContent  (pt1_bin, yield_mc.ll  );

            if(yield_data.ll > 0) h_data_pt1->SetBinError(pt1_bin, yield_data.dll  );
            if(yield_fake.ll > 0) h_fake_pt1->SetBinError(pt1_bin, yield_fake.tll());
            if(yield_flip.ll > 0) h_flip_pt1->SetBinError(pt1_bin, yield_flip.tll());
            if(yield_pred.ll > 0) h_pred_pt1->SetBinError(pt1_bin, yield_pred.tll());
            if(yield_mc.ll   > 0) h_mc_pt1->SetBinError  (pt1_bin, yield_mc.tll()  );
        }
        else if (bin >= 32 && bin <= 41)  // bin 32 - 41 
        {
            int pt2_bin = bin-31;
            cout << "creating pt2 plot: " << pt2_bin << endl;
            if(yield_data.ll > 0) h_data_pt2->SetBinContent(pt2_bin, yield_data.ll);
            if(yield_fake.ll > 0) h_fake_pt2->SetBinContent(pt2_bin, yield_fake.ll);
            if(yield_flip.ll > 0) h_flip_pt2->SetBinContent(pt2_bin, yield_flip.ll);
            if(yield_pred.ll > 0) h_pred_pt2->SetBinContent(pt2_bin, yield_pred.ll);
            if(yield_mc.ll   > 0) h_mc_pt2->SetBinContent  (pt2_bin, yield_mc.ll  );

            if(yield_data.ll > 0) h_data_pt2->SetBinError(pt2_bin, yield_data.dll  );
            if(yield_fake.ll > 0) h_fake_pt2->SetBinError(pt2_bin, yield_fake.tll());
            if(yield_flip.ll > 0) h_flip_pt2->SetBinError(pt2_bin, yield_flip.tll());
            if(yield_pred.ll > 0) h_pred_pt2->SetBinError(pt2_bin, yield_pred.tll());
            if(yield_mc.ll   > 0) h_mc_pt2->SetBinError  (pt2_bin, yield_mc.tll()  );
        }

        bin++;
    } // loop over SRs

    // set style
    rt::SetTDRStyle();
    gStyle->SetHatchesSpacing(1.00);

    // colors
    const Color_t data_color  = kBlack;
    const Color_t mc_color    = kCyan-5;
    const Color_t fake_color  = kRed-6;
    const Color_t flip_color  = kOrange-8;
    const Style_t data_marker = 20;
    const Style_t shade_style = 3335;
    const float text_size     = 0.035;
    const string flip_legend  = "Charge-flip";
    const string fake_legend  = "Fakes";
    const string rare_legend  = "Rare MC";
    const string data_legend  = "Observed";
    const string unc_legend   = "Total Uncertainty";

    // make marker larger
    h_data_ht->SetMarkerSize(2.0);
    h_data_met->SetMarkerSize(2.0);

    TCanvas* c1 = new TCanvas("c1", "c1");
    TLatex t1(0.5, 0.84, "E^{miss}_{T} > 0 GeV"); t1.SetTextSize(text_size);
    rt::TH1Overlay* p_ht = new rt::TH1Overlay("", "sb::off lg::top_right dt::stack");
    p_ht->Add(h_data_ht, /*no_stack=*/true, data_legend, data_color, 2, data_marker); 
    p_ht->Add(h_fake_ht, fake_legend      , fake_color); 
    p_ht->Add(h_flip_ht, flip_legend      , flip_color); 
    p_ht->Add(h_mc_ht  , rare_legend      , mc_color  ); 
    p_ht->Add(h_pred_ht, /*no_stack=*/true, unc_legend, 1, 2, 1, shade_style); 
    p_ht->AddText(t1);
    p_ht->Draw();

    TCanvas* c2 = new TCanvas("c2", "c2");
    TLatex t2(0.5, 0.84, "H_{T} > 80 GeV"); t2.SetTextSize(text_size);
    rt::TH1Overlay* p_met = new rt::TH1Overlay("", "sb::off lg::top_right dt::stack");
    p_met->Add(h_data_met, /*no_stack=*/true , data_legend, data_color, 2, data_marker); 
    p_met->Add(h_fake_met, fake_legend       , fake_color); 
    p_met->Add(h_flip_met, flip_legend       , flip_color); 
    p_met->Add(h_mc_met  , rare_legend       , mc_color  ); 
    p_met->Add(h_pred_met, /*no_stack=*/true , unc_legend, 1, 2, 1, shade_style); 
    p_met->AddText(t2);
    p_met->Draw();

    TCanvas* c3 = new TCanvas("c3", "c3");
    TLatex t3(0.5, 0.84, "H_{T} > 80 GeV"); t3.SetTextSize(text_size);
    TLatex t4(0.5, 0.79, "E^{miss}_{T} > 0 GeV"); t4.SetTextSize(text_size);
    rt::TH1Overlay* p_njets = new rt::TH1Overlay("", "sb::off lg::top_right dt::stack");
    p_njets->Add(h_data_njets, /*no_stack=*/true , data_legend, data_color, 2, data_marker); 
    p_njets->Add(h_fake_njets, fake_legend       , fake_color); 
    p_njets->Add(h_flip_njets, flip_legend       , flip_color); 
    p_njets->Add(h_mc_njets  , rare_legend       , mc_color  ); 
    p_njets->Add(h_pred_njets, /*no_stack=*/true , unc_legend, 1, 2, 1, shade_style); 
    p_njets->AddText(t3);
    p_njets->AddText(t4);
    p_njets->Draw();

    TCanvas* c4 = new TCanvas("c4", "c4");
    rt::TH1Overlay* p_nbtags = new rt::TH1Overlay("", "sb::off lg::top_right dt::stack");
    p_nbtags->Add(h_data_nbtags, /*no_stack=*/true , data_legend, data_color, 2, data_marker); 
    p_nbtags->Add(h_fake_nbtags, fake_legend       , fake_color); 
    p_nbtags->Add(h_flip_nbtags, flip_legend       , flip_color); 
    p_nbtags->Add(h_mc_nbtags  , rare_legend       , mc_color  ); 
    p_nbtags->Add(h_pred_nbtags, /*no_stack=*/true , unc_legend, 1, 2, 1, shade_style); 
    p_nbtags->AddText(t3);
    p_nbtags->AddText(t4);
    p_nbtags->Draw();

    TCanvas* c5 = new TCanvas("c5", "c5");
    rt::TH1Overlay* p_pt1 = new rt::TH1Overlay("", "sb::off lg::top_right dt::stack");
    p_pt1->Add(h_data_pt1, /*no_stack=*/true , data_legend, data_color, 2, data_marker); 
    p_pt1->Add(h_fake_pt1, fake_legend       , fake_color); 
    p_pt1->Add(h_flip_pt1, flip_legend       , flip_color); 
    p_pt1->Add(h_mc_pt1  , rare_legend       , mc_color  ); 
    p_pt1->Add(h_pred_pt1, /*no_stack=*/true , unc_legend, 1, 2, 1, shade_style); 
    p_pt1->AddText(t3);
    p_pt1->AddText(t4);
    p_pt1->Draw();

    TCanvas* c6 = new TCanvas("c6", "c6");
    rt::TH1Overlay* p_pt2 = new rt::TH1Overlay("", "sb::off lg::top_right dt::stack");
    p_pt2->Add(h_data_pt2, /*no_stack=*/true , data_legend, data_color, 2, data_marker); 
    p_pt2->Add(h_fake_pt2, fake_legend       , fake_color); 
    p_pt2->Add(h_flip_pt2, flip_legend       , flip_color); 
    p_pt2->Add(h_mc_pt2  , rare_legend       , mc_color  ); 
    p_pt2->Add(h_pred_pt2, /*no_stack=*/true , unc_legend, 1, 2, 1, shade_style); 
    p_pt2->AddText(t3);
    p_pt2->AddText(t4);
    p_pt2->Draw();

    // print
    if (!suffix.empty())
    {
        rt::mkdir("plots/paper_fixed_v2", /*force=*/true);
        c1->cd(); c1->Print(Form("plots/paper_fixed_v2/p_proj_ht.%s"    , suffix.c_str()));
        c1->cd(); c2->Print(Form("plots/paper_fixed_v2/p_proj_met.%s"   , suffix.c_str()));
        c3->cd(); c3->Print(Form("plots/paper_fixed_v2/p_proj_njets.%s" , suffix.c_str()));
        c4->cd(); c4->Print(Form("plots/paper_fixed_v2/p_proj_nbtags.%s", suffix.c_str()));
        c5->cd(); c5->Print(Form("plots/paper_fixed_v2/p_proj_pt1.%s"   , suffix.c_str()));
        c6->cd(); c6->Print(Form("plots/paper_fixed_v2/p_proj_pt2.%s"   , suffix.c_str()));
    }
}
