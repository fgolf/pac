#include "FakeRateBaby.h"
#include "FakeRateTrigStudy.h"
#include "mcSelections.h"
#include "rt/RootTools.h"
#include <iostream>
#include <algorithm>
#include <tr1/functional>
#include <cmath>
#include <vector>
#include "CTable.h" 

typedef std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > vecLorentzVector;
    
using namespace std;
using namespace frb;

// selection functions (to be moved to another file maybe)
float pfiso03_rho()
{
    return (ch_pfiso03() + max(0.0f, nh_pfiso03() + em_pfiso03() - (max(0.0f, rho())*el_effarea03())))/pt();
}

float pfiso03_db()
{
    return (ch_pfiso03() + max(0.0f, nh_pfiso03() + em_pfiso03() - (0.5f*pfpupt03())))/pt();
}

struct passes_window
{
    passes_window(float low, float high) : m_low(low), m_high(high) {}
    bool operator() (float value) {return value > m_low && value < m_high;}
    float m_low;
    float m_high;
};

// simple struct for cuts
struct category_t
{
    category_t(const std::string n, const std::string& t, std::tr1::function<bool()> c)
        : name(n), title(t), passes_cut(c)
    {} 
    std::string name;
    std::string title;
    std::tr1::function<bool()> passes_cut;
};

// muon cuts
// --------------------------------------------------------------------------------------------------------------------------------- //

// function objects for selections (muons)
struct mu_count   {bool operator() () {return (abs(id())==13);                                                                              }}; 
struct mu_kin     {bool operator() () {return (pt()>5 && pt()<35 && abs(eta())<2.4);                                                        }}; 
struct mu_pt20    {bool operator() () {return pt()>20;                                                                                      }}; 
struct mu_wveto   {bool operator() () {return (pfmet()<20 && pfmt()<25);                                                                    }}; 
struct mu_zveto   {bool operator() () {return ((mz_fo_ctf()<76.0 || mz_fo_ctf()>106.0) && (mupsilon_fo_mu()<8.0 || mupsilon_fo_mu()>12.0)); }}; 
struct mu_nFO     {bool operator() () {return (nFOmus()==0);                                                                                }}; 
struct mu_awayj20 {bool operator() () {return (ptpfcL1Fj1()>20);                                                                            }}; 
struct mu_awayj40 {bool operator() () {return (ptpfcL1Fj1()>40);                                                                            }}; 
struct mu_foid    {bool operator() () {return fo_mu_ssV5_noIso();                                                                           }}; 
struct mu_foiso   {bool operator() () {return pfiso03_db()<0.4;                                                                             }}; 
struct mu_numid   {bool operator() () {return num_mu_ssV5_noIso();                                                                          }}; 
struct mu_numiso  {bool operator() () {return pfiso03_db()<0.1;                                                                             }}; 

struct passes_mu_fo
{
    bool operator() () 
    {
        bool result = ( (abs(id())==13)                                                                              && 
                        (pt()>5 && pt()<35 && abs(eta())<2.4)                                                        && 
                        (pfmet()<20 && pfmt()<25)                                                                    && 
                        ((mz_fo_ctf()<76.0 || mz_fo_ctf()>106.0) && (mupsilon_fo_mu()<8.0 || mupsilon_fo_mu()>12.0)) && 
                        (nFOmus()==0)                                                                                && 
                        (ptpfcL1Fj1()>40)                                                                            && 
                        (fo_mu_ssV5_noIso())                                                                         && 
                        (pfiso03_db()<0.4));
        return result;
    }
};

struct passes_mu_num
{
    bool operator() () 
    {
        passes_mu_fo fo;
        bool result = (fo() && num_mu_ssV5_noIso() && (pfiso03_db()<0.1));
        return result;
    }
};

// function objects for triggers (muons)
bool mu5    ()      {return (mu5_vstar          ()>1);}
bool mu8    ()      {return (mu8_vstar          ()>1);}
bool mu12   ()      {return (mu12_vstar         ()>1);}
bool mu17   ()      {return (mu17_vstar         ()>1);}
bool mu15e21()      {return (mu15_eta2p1_vstar  ()>1);}
bool mu24e21()      {return (mu24_eta2p1_vstar  ()>1);}
bool mu30e21()      {return (mu30_eta2p1_vstar  ()>1);}
bool relIso1p0Mu5() {return (relIso1p0Mu5_vstar ()>1);}
bool relIso1p0Mu17(){return (relIso1p0Mu17_vstar()>1);}
bool relIso1p0Mu20(){return (relIso1p0Mu20_vstar()>1);}

struct mu5_cut           {bool operator() () {return (pt()>5  && mu5    ())      ;} };
struct mu8_cut           {bool operator() () {return (pt()>8  && mu8    ())      ;} };
struct mu12_cut          {bool operator() () {return (pt()>12 && mu12   ())      ;} };
struct mu17_cut          {bool operator() () {return (pt()>17 && mu17   ())      ;} };
struct mu15_eta2p1_cut   {bool operator() () {return (pt()>15 && mu15e21())      ;} };
struct mu24_eta2p1_cut   {bool operator() () {return (pt()>24 && mu24e21())      ;} };
struct mu30_eta2p1_cut   {bool operator() () {return (pt()>30 && mu30e21())      ;} };
struct relIso1p0Mu5_cut  {bool operator() () {return (pt()>5  && relIso1p0Mu5()); } };
struct relIso1p0Mu17_cut {bool operator() () {return (pt()>17 && relIso1p0Mu17());} };
struct relIso1p0Mu20_cut {bool operator() () {return (pt()>20 && relIso1p0Mu20());} };

// function objects for triggers exclusive (muons)
struct mu30_eta2p1_excut {bool operator() () {return (mu30e21());                                                                                  } };
struct mu24_eta2p1_excut {bool operator() () {return (mu24e21()  && !(mu30e21()));                                                                 } };
struct mu17_excut        {bool operator() () {return (mu17()     && !(mu24e21() || mu30e21()));                                                    } };
struct mu8_excut         {bool operator() () {return (mu8()      && !(mu17()    || mu24e21() || mu30e21()));                                       } };
struct mu12_excut        {bool operator() () {return (mu12()     && !(mu8()     || mu17()    || mu24e21() || mu30e21()));                          } };
struct mu5_excut         {bool operator() () {return (mu5()      && !(mu8()     || mu12()    || mu17()    || mu24e21() || mu30e21()));             } };
struct mu15_eta2p1_excut {bool operator() () {return (mu15e21()  && !(mu5()     || mu8()     || mu12()    || mu17()    || mu24e21() || mu30e21()));} };

// function objects for triggers exclusive (muons with iso)
struct relIso1p0Mu20_excut{bool operator() () {return (relIso1p0Mu20());                                         } };
struct relIso1p0Mu17_excut{bool operator() () {return (relIso1p0Mu17() && !(relIso1p0Mu20()));                   } };
struct relIso1p0Mu5_excut {bool operator() () {return (relIso1p0Mu5()  && !(relIso1p0Mu20() || relIso1p0Mu17()));} };

vector<category_t> MuAnalTypeFactory()
{
    vector<category_t> cats;
    cats.push_back(category_t("mu_count" , "mu count"       , mu_count()    ));
    cats.push_back(category_t("kin"      , "kin"            , mu_kin()      ));
    //cats.push_back(category_t("pt20"     , "$p_T > 20$"     , mu_pt20()     ));
    cats.push_back(category_t("wveto"    , "W veto"         , mu_wveto()    ));
    cats.push_back(category_t("zveto"    , "Z veto"         , mu_zveto()    ));
    cats.push_back(category_t("nFOmus"   , "nFO's"          , mu_nFO()      ));
    //cats.push_back(category_t("awayj20"  , "p^{j}_T > 20"   , mu_awayj20()  ));
    cats.push_back(category_t("awayj40"  , "p^{j}_T > 40"   , mu_awayj40()  ));
    cats.push_back(category_t("fo_id"    , "FO ID ssV5"     , mu_foid()     ));
    cats.push_back(category_t("fo_iso"   , "cpfiso03 < 0.4" , mu_foiso()    ));
    cats.push_back(category_t("num_id"   , "Num ID ssV5"    , mu_numid()    ));
    cats.push_back(category_t("num_iso"  , "cpfiso03 < 0.1" , mu_numiso()   ));
    return cats;
}

vector<category_t> MuNumDenFactory()
{
    vector<category_t> cats;
    cats.push_back(category_t("fo"       , "passes FO selection"  , passes_mu_fo() )); 
    cats.push_back(category_t("num"      , "passes num selection" , passes_mu_num())); 
    return cats;
}

vector<category_t> MuTrigTypeFactory()
{
    vector<category_t> cats;
    cats.push_back(category_t("mu5"          , "mu5_v*"          , mu5_cut        ()));
    cats.push_back(category_t("mu8"          , "mu8_v*"          , mu8_cut        ()));
    cats.push_back(category_t("mu12"         , "mu12_v*"         , mu12_cut       ()));
    cats.push_back(category_t("mu17"         , "mu17_v*"         , mu17_cut       ()));
    cats.push_back(category_t("mu15_eta2p1"  , "mu15_eta2p1_v*"  , mu15_eta2p1_cut()));
    cats.push_back(category_t("mu24_eta2p1"  , "mu24_eta2p1_v*"  , mu24_eta2p1_cut()));
    cats.push_back(category_t("mu30_eta2p1"  , "mu30_eta2p1_v*"  , mu30_eta2p1_cut()));
    //cats.push_back(category_t("relIso1p0Mu17", "relIso1p0Mu17_v*", relIso1p0Mu17_cut()));
    cats.push_back(category_t("relIso1p0Mu20", "relIso1p0Mu20_v*", relIso1p0Mu20_cut()));
    cats.push_back(category_t("relIso1p0Mu5" , "relIso1p0Mu5_v*" , relIso1p0Mu5_cut()));
    return cats;
}

vector<category_t> MuExTrigTypeFactory()
{
    vector<category_t> cats;
    cats.push_back(category_t("mu30_eta2p1", "mu30_eta2p1_v*", mu30_eta2p1_excut()));
    cats.push_back(category_t("mu24_eta2p1", "mu24_eta2p1_v*", mu24_eta2p1_excut()));
    cats.push_back(category_t("mu17"       , "mu17_v*"       , mu17_excut       ()));
    cats.push_back(category_t("mu8"        , "mu8_v*"        , mu8_excut        ()));
    cats.push_back(category_t("mu12"       , "mu12_v*"       , mu12_excut       ()));
    cats.push_back(category_t("mu5"        , "mu5_v*"        , mu5_excut        ()));
    cats.push_back(category_t("mu15_eta2p1", "mu15_eta2p1_v*", mu15_eta2p1_excut()));
    return cats;
}

vector<category_t> MuIsoExTrigTypeFactory()
{
    vector<category_t> cats;
    cats.push_back(category_t("relIso1p0Mu20", "relIso1p0Mu20_v*", relIso1p0Mu20_excut()));
    //cats.push_back(category_t("relIso1p0Mu17", "relIso1p0Mu17_v*", relIso1p0Mu17_excut()));
    cats.push_back(category_t("relIso1p0Mu5" , "relIso1p0Mu5_v*" , relIso1p0Mu5_excut() ));
    return cats;
}

// electron cuts
// --------------------------------------------------------------------------------------------------------------------------------- //

// function objects for selections (electrons)
struct el_count   {bool operator() () {return (abs(id())==11);                         }}; 
struct el_kin     {bool operator() () {return (pt()>10 && pt()<55 && abs(eta())<2.4);  }}; 
struct el_pt20    {bool operator() () {return pt()>20;                                 }}; 
struct el_wveto   {bool operator() () {return (pfmet()<20 && pfmt()<25);               }}; 
struct el_zveto   {bool operator() () {return (mz_fo_gsf()<76.0 || mz_fo_gsf()>106.0); }}; 
struct el_nFO     {bool operator() () {return (nFOels()==0);                           }}; 
struct el_awayj20 {bool operator() () {return (ptpfcL1Fj1()>20);                       }}; 
struct el_awayj40 {bool operator() () {return (ptpfcL1Fj1()>40);                       }}; 
struct el_foid    {bool operator() () {return v3_el_ssV7();                            }}; 
struct el_foiso   {bool operator() () {return pfiso03_rho()<0.6;                       }}; 
struct el_numid   {bool operator() () {return num_el_ssV7_noIso();                     }}; 
struct el_numiso  {bool operator() () {return pfiso03_rho()<0.09;                      }}; 

struct passes_el_fo
{
    bool operator() () 
    {
        bool result = ( (abs(id())==11)                         && 
                        (pt()>10 && pt()<55 && abs(eta())<2.4)  && 
                        (pfmet()<20 && pfmt()<25)               && 
                        (mz_fo_gsf()<76.0 || mz_fo_gsf()>106.0) && 
                        (nFOels()==0)                           && 
                        (ptpfcL1Fj1()>40)                       && 
                        (v3_el_ssV7())                          && 
                        (pfiso03_rho()<0.6));
        return result;
    }
};

struct passes_el_num
{
    bool operator() () 
    {
        passes_el_fo fo;
        bool result = (fo() && num_el_ssV7_noIso() && (pfiso03_rho()<0.09));
        return result;
    }
};

// function objects for triggers
bool ele8          () {return (ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar       ()>1);}
bool ele8_j30      () {return (ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar ()>1);}
bool ele17         () {return (ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_vstar      ()>1);}
bool ele17_j30     () {return (ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_vstar()>1);}
bool ele8_noiso    () {return (ele8_CaloIdT_TrkIdVL_Jet30_vstar                    ()>1);}
bool ele8_noiso_j30() {return (ele8_CaloIdT_TrkIdVL_vstar                          ()>1);}


struct ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_cut        {bool operator() () {return (pt()>8  && ele8          ());} };
struct ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_cut  {bool operator() () {return (pt()>8  && ele8_j30      ());} };
struct ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_cut       {bool operator() () {return (pt()>17 && ele17         ());} };
struct ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_cut {bool operator() () {return (pt()>17 && ele17_j30     ());} };
struct ele8_CaloIdT_TrkIdVL_cut                           {bool operator() () {return (pt()>8  && ele8_noiso    ());} };
struct ele8_CaloIdT_TrkIdVL_Jet30_cut                     {bool operator() () {return (pt()>8  && ele8_noiso_j30());} };

// function objects for triggers exclusive
struct ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_excut      {bool operator() () {return (ele17());                                           } }; 
struct ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_excut{bool operator() () {return (ele17_j30()    && !(ele17()));                      } }; 
struct ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_excut       {bool operator() () {return (ele8()     && !(ele17() || ele17_j30()));           } }; 
struct ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_excut {bool operator() () {return (ele8_j30() && !(ele8()  || ele17() || ele17_j30()));} }; 

// function objects for triggers exclusive (no iso)
struct ele8_CaloIdT_TrkIdVL_cut_excut                       {bool operator() () {return (ele8_noiso());                       } };
struct ele8_CaloIdT_TrkIdVL_Jet30_cut_excut                 {bool operator() () {return (ele8_noiso_j30() && !(ele8_noiso()));} };

vector<category_t> ElAnalTypeFactory()
{
    vector<category_t> cats;
    cats.push_back(category_t("el_count" , "e count"         , el_count() ));
    cats.push_back(category_t("kin"      , "kin"             , el_kin()      ));
    //cats.push_back(category_t("awayj20"  , "p^{j)_T > 20"    , el_awayj20()  ));
    cats.push_back(category_t("fo_id"    , "FO ID ssV7"      , el_foid()     ));
    cats.push_back(category_t("fo_iso"   , "cpfiso03 < 0.6"  , el_foiso()    ));
    cats.push_back(category_t("awayj40"  , "p^{j)_T > 40"    , el_awayj40()  ));
    cats.push_back(category_t("nFOels"   , "nFO's"           , el_nFO()      ));
    //cats.push_back(category_t("pt20"     , "$p_T > 20$"      , el_pt20()     ));
    cats.push_back(category_t("wveto"    , "W veto"          , el_wveto()    ));
    cats.push_back(category_t("zveto"    , "Z veto"          , el_zveto()    ));
    cats.push_back(category_t("num_id"   , "Num ID ssV7"     , el_numid()    ));
    cats.push_back(category_t("num_iso"  , "cpfiso03 < 0.09" , el_numiso()   ));
    return cats;
}

vector<category_t> ElNumDenFactory()
{
    vector<category_t> cats;
    cats.push_back(category_t("fo"       , "passes FO selection"  , passes_el_fo() )); 
    cats.push_back(category_t("num"      , "passes num selection" , passes_el_num())); 
    return cats;
}

vector<category_t> ElTrigTypeFactory()
{
    vector<category_t> cats;
    cats.push_back(category_t("ele8_CaloIdT_TrkIdVL"                           , "ele8_CaloIdT_TrkIdVL_v*"                           , ele8_CaloIdT_TrkIdVL_cut                           ())); 
    cats.push_back(category_t("ele8_CaloIdT_TrkIdVL_Jet30"                     , "ele8_CaloIdT_TrkIdVL_Jet30_v*"                     , ele8_CaloIdT_TrkIdVL_Jet30_cut                     ())); 
    cats.push_back(category_t("ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"        , "ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*"        , ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_cut        ())); 
    cats.push_back(category_t("ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30"  , "ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v*"  , ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_cut  ())); 
    cats.push_back(category_t("ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"       , "ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*"       , ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_cut       ())); 
    cats.push_back(category_t("ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30" , "ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v*" , ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_cut ())); 
    return cats;
}

vector<category_t> ElExTrigTypeFactory()
{
    vector<category_t> cats;
    cats.push_back(category_t("ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"      , "ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*"      , ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_excut      ()));
    cats.push_back(category_t("ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30", "ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v*", ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_excut()));
    cats.push_back(category_t("ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL"       , "ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v*"       , ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_excut       ()));
    cats.push_back(category_t("ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30" , "ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_v*" , ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Jet30_excut ()));
    return cats;
}

vector<category_t> ElNoIsoExTrigTypeFactory()
{
    vector<category_t> cats;
    cats.push_back(category_t("ele8_CaloIdT_TrkIdVL"                           , "ele8_CaloIdT_TrkIdVL_v*"                           , ele8_CaloIdT_TrkIdVL_cut                           ())); 
    cats.push_back(category_t("ele8_CaloIdT_TrkIdVL_Jet30"                     , "ele8_CaloIdT_TrkIdVL_Jet30_v*"                     , ele8_CaloIdT_TrkIdVL_Jet30_cut                     ())); 
    return cats;
}

// looper implementation
// --------------------------------------------------------------------------------------------------------------------------------- //

// construct:
FakeRateTrigStudy::FakeRateTrigStudy
(
     const std::string& root_file_name,
     const fr::Sample::value_type& sample,
     const std::string& lepton,
     float lumi,
     bool verbose,
     bool print,
     const std::string& suffix
)
    : at::AnalysisWithHist(root_file_name, print, suffix)
    , m_sample(sample)
    , m_lepton(lepton)
    , m_lumi(lumi)
    , m_verbose(verbose)
{
    // begin job
    BeginJob();
}

// destroy:
FakeRateTrigStudy::~FakeRateTrigStudy()
{
    // end  job
    EndJob();
}

// methods:
void FakeRateTrigStudy::BeginJob()
{
    BookHists();
}

// end job
void FakeRateTrigStudy::EndJob()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    if (m_lepton=="mu")
    {
        vector<category_t> mu_trig_sel       = MuTrigTypeFactory();
        vector<category_t> mu_anal_sel       = MuAnalTypeFactory();
        vector<category_t> mu_extrig_sel     = MuExTrigTypeFactory();
        vector<category_t> mu_iso_extrig_sel = MuIsoExTrigTypeFactory();
        vector<category_t> mu_numden_sel     = MuNumDenFactory();

		// muon cut flow table
        CTable t_mu_flow;
        t_mu_flow.setTitle("Cut Flow Table for muons triggers");
        t_mu_flow.useTitle();
        for (size_t itrig = 0; itrig != mu_trig_sel.size(); itrig++)
        {
            category_t& trig = mu_trig_sel.at(itrig);
            t_mu_flow.setRowLabel(trig.title, itrig);
            for (size_t ianal = 0; ianal != mu_anal_sel.size(); ianal++)
            {
                category_t& anal = mu_anal_sel.at(ianal);
                t_mu_flow.setColLabel(anal.title, ianal);
                t_mu_flow.setCell(hc["h_mu_flow_count"]->GetBinContent(ianal+1, itrig+1), itrig, ianal);
            }
        }
        t_mu_flow.print();
        cout << endl;

        CTable t_mu_flow_percent;
        t_mu_flow_percent.setTitle("Cut Flow Table for muon triggers (percentage rmuative to previous cut)");
        t_mu_flow_percent.useTitle();
        for (size_t itrig = 0; itrig != mu_trig_sel.size(); itrig++)
        {
            category_t& trig = mu_trig_sel.at(itrig);
            t_mu_flow_percent.setRowLabel(trig.title, itrig);
            for (size_t ianal = 0; ianal != mu_anal_sel.size(); ianal++)
            {
                category_t& anal = mu_anal_sel.at(ianal);
                t_mu_flow_percent.setColLabel(anal.title, ianal);
				float current  = hc["h_mu_flow_count"]->GetBinContent(ianal+1, itrig+1);
				float percent  = current;
				if (ianal > 0)
				{
					float previous = hc["h_mu_flow_count"]->GetBinContent(ianal, itrig+1);
					percent = 100.0 * (current/previous);
				}
                t_mu_flow_percent.setCell(Form("%1.1f", percent), itrig, ianal);
            }
        }
        t_mu_flow_percent.print();
        cout << endl;

        CTable t_mu_flow_precent_abs;
        t_mu_flow_precent_abs.setTitle("Cut Flow Table for muon triggers (percentage relative to total trigger count)");
        t_mu_flow_precent_abs.useTitle();
        for (size_t itrig = 0; itrig != mu_trig_sel.size(); itrig++)
        {
            category_t& trig = mu_trig_sel.at(itrig);
            t_mu_flow_precent_abs.setRowLabel(trig.title, itrig);
			float total = hc["h_mu_flow_count"]->GetBinContent(1, itrig+1);
            for (size_t ianal = 0; ianal != mu_anal_sel.size(); ianal++)
            {
                category_t& anal = mu_anal_sel.at(ianal);
                t_mu_flow_precent_abs.setColLabel(anal.title, ianal);
				float current  = hc["h_mu_flow_count"]->GetBinContent(ianal+1, itrig+1);
				float percent = 100.0 * (current/total);
                t_mu_flow_precent_abs.setCell(Form("%1.1f", percent), itrig, ianal);
            }
        }
        t_mu_flow_precent_abs.print();
        cout << endl;

		// muon trig count table
        CTable t_mu_count;
        t_mu_count.setTitle("Count Table for muons triggers");
        t_mu_count.useTitle();
        for (size_t itrig = 0; itrig != mu_extrig_sel.size(); itrig++)
        {
            category_t& trig = mu_extrig_sel.at(itrig);
            t_mu_count.setRowLabel(trig.title, itrig);
            for (size_t ianal = 0; ianal != mu_numden_sel.size(); ianal++)
            {
                category_t& anal = mu_numden_sel.at(ianal);
                t_mu_count.setColLabel(anal.title, ianal);
                t_mu_count.setCell(hc["h_mu_trig_count"]->GetBinContent(ianal+1, itrig+1), itrig, ianal);
            }
        }
        t_mu_count.print();
        cout << endl;

		// muon iso trig count table
        CTable t_mu_iso_count;
        t_mu_iso_count.setTitle("Count Table for muons iso triggers");
        t_mu_iso_count.useTitle();
        for (size_t itrig = 0; itrig != mu_iso_extrig_sel.size(); itrig++)
        {
            category_t& trig = mu_iso_extrig_sel.at(itrig);
            t_mu_iso_count.setRowLabel(trig.title, itrig);
            for (size_t ianal = 0; ianal != mu_numden_sel.size(); ianal++)
            {
                category_t& anal = mu_numden_sel.at(ianal);
                t_mu_iso_count.setColLabel(anal.title, ianal);
                t_mu_iso_count.setCell(hc["h_mu_iso_trig_count"]->GetBinContent(ianal+1, itrig+1), itrig, ianal);
            }
        }
        t_mu_iso_count.print();
        cout << endl;
    }

    if (m_lepton=="el")
    {
        vector<category_t> el_trig_sel         = ElTrigTypeFactory();
        vector<category_t> el_anal_sel         = ElAnalTypeFactory();
        vector<category_t> el_extrig_sel       = ElExTrigTypeFactory();
        vector<category_t> el_noiso_extrig_sel = ElNoIsoExTrigTypeFactory();
        vector<category_t> el_numden_sel       = ElNumDenFactory();

        CTable t_el_flow;
        t_el_flow.setTitle("Cut Flow Table for electron triggers");
        t_el_flow.useTitle();
        for (size_t itrig = 0; itrig != el_trig_sel.size(); itrig++)
        {
            category_t& trig = el_trig_sel.at(itrig);
            t_el_flow.setRowLabel(trig.title, itrig);
            for (size_t ianal = 0; ianal != el_anal_sel.size(); ianal++)
            {
                category_t& anal = el_anal_sel.at(ianal);
                t_el_flow.setColLabel(anal.title, ianal);
                t_el_flow.setCell(hc["h_el_flow_count"]->GetBinContent(ianal+1, itrig+1), itrig, ianal);
            }
        }
        t_el_flow.print();
        cout << endl;

        CTable t_el_flow_percent;
        t_el_flow_percent.setTitle("Cut Flow Table for electron triggers (percentage relative to previous cut)");
        t_el_flow_percent.useTitle();
        for (size_t itrig = 0; itrig != el_trig_sel.size(); itrig++)
        {
            category_t& trig = el_trig_sel.at(itrig);
            t_el_flow_percent.setRowLabel(trig.title, itrig);
            for (size_t ianal = 0; ianal != el_anal_sel.size(); ianal++)
            {
                category_t& anal = el_anal_sel.at(ianal);
                t_el_flow_percent.setColLabel(anal.title, ianal);
				float current  = hc["h_el_flow_count"]->GetBinContent(ianal+1, itrig+1);
				float percent  = current;
				if (ianal > 0)
				{
					float previous = hc["h_el_flow_count"]->GetBinContent(ianal, itrig+1);
					percent = 100.0 * (current/previous);
				}
                t_el_flow_percent.setCell(Form("%1.1f", percent), itrig, ianal);
            }
        }
        t_el_flow_percent.print();
        cout << endl;

        CTable t_el_flow_precent_abs;
        t_el_flow_precent_abs.setTitle("Cut Flow Table for electron triggers (percentage relative to total trigger count)");
        t_el_flow_precent_abs.useTitle();
        for (size_t itrig = 0; itrig != el_trig_sel.size(); itrig++)
        {
            category_t& trig = el_trig_sel.at(itrig);
            t_el_flow_precent_abs.setRowLabel(trig.title, itrig);
			float total = hc["h_el_flow_count"]->GetBinContent(1, itrig+1);
            for (size_t ianal = 0; ianal != el_anal_sel.size(); ianal++)
            {
                category_t& anal = el_anal_sel.at(ianal);
                t_el_flow_precent_abs.setColLabel(anal.title, ianal);
				float current  = hc["h_el_flow_count"]->GetBinContent(ianal+1, itrig+1);
				float percent = 100.0 * (current/total);
                t_el_flow_precent_abs.setCell(Form("%1.1f", percent), itrig, ianal);
            }
        }
        t_el_flow_precent_abs.print();
        cout << endl;


        CTable t_el_count;
        t_el_count.setTitle("Trigger Count Table for electron triggers");
        t_el_count.useTitle();
        for (size_t itrig = 0; itrig != el_extrig_sel.size(); itrig++)
        {
            category_t& trig = el_extrig_sel.at(itrig);
            t_el_count.setRowLabel(trig.title, itrig);
            for (size_t ianal = 0; ianal != el_numden_sel.size(); ianal++)
            {
                category_t& anal = el_numden_sel.at(ianal);
                t_el_count.setColLabel(anal.title, ianal);
                t_el_count.setCell(hc["h_el_trig_count"]->GetBinContent(ianal+1, itrig+1), itrig, ianal);
            }
        }
        t_el_count.print();
        cout << endl;

        CTable t_el_noiso_count;
        t_el_noiso_count.setTitle("Trigger Count Table for electron triggers with no iso");
        t_el_noiso_count.useTitle();
        for (size_t itrig = 0; itrig != el_noiso_extrig_sel.size(); itrig++)
        {
            category_t& trig = el_noiso_extrig_sel.at(itrig);
            t_el_noiso_count.setRowLabel(trig.title, itrig);
            for (size_t ianal = 0; ianal != el_numden_sel.size(); ianal++)
            {
                category_t& anal = el_numden_sel.at(ianal);
                t_el_noiso_count.setColLabel(anal.title, ianal);
                t_el_noiso_count.setCell(hc["h_el_noiso_trig_count"]->GetBinContent(ianal+1, itrig+1), itrig, ianal);
            }
        }
        t_el_noiso_count.print();
        cout << endl;
    }
}

// book hists
 void FakeRateTrigStudy::BookHists()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    if (m_lepton=="el")
    {
        vector<category_t> el_trig_sel         = ElTrigTypeFactory();
        vector<category_t> el_anal_sel         = ElAnalTypeFactory();
        vector<category_t> el_extrig_sel       = ElExTrigTypeFactory();
        vector<category_t> el_noiso_extrig_sel = ElNoIsoExTrigTypeFactory();
        vector<category_t> el_numden_sel       = ElNumDenFactory();

        // flow counts
        hc.Add(new TH2I("h_el_flow_count"      , "Electron Flow Count; analysis cuts; trigger cuts"   , el_anal_sel.size()  , 0, el_anal_sel.size()  , el_trig_sel.size()        , 0, el_trig_sel.size()        ));
        hc.Add(new TH2I("h_el_trig_count"      , "Electron Trigger Count; analysis cuts; trigger cuts", el_numden_sel.size(), 0, el_numden_sel.size(), el_extrig_sel.size()      , 0, el_extrig_sel.size()      ));
        hc.Add(new TH2I("h_el_noiso_trig_count", "Electron Trigger Count; analysis cuts; trigger cuts", el_numden_sel.size(), 0, el_numden_sel.size(), el_noiso_extrig_sel.size(), 0, el_noiso_extrig_sel.size()));
    }

    if (m_lepton=="mu")
    {
        vector<category_t> mu_trig_sel       = MuTrigTypeFactory();
        vector<category_t> mu_anal_sel       = MuAnalTypeFactory();
        vector<category_t> mu_extrig_sel     = MuExTrigTypeFactory();
        vector<category_t> mu_iso_extrig_sel = MuIsoExTrigTypeFactory();
        vector<category_t> mu_numden_sel     = MuNumDenFactory();

        // counts
        hc.Add(new TH2I("h_mu_flow_count"    , "Muon Flow Count; analysis cuts; trigger cuts"       , mu_anal_sel.size()  , 0, mu_anal_sel.size()  , mu_trig_sel.size()      , 0, mu_trig_sel.size()      ));
        hc.Add(new TH2I("h_mu_trig_count"    , "Muon Trigger Count; analysis cuts; trigger cuts"    , mu_numden_sel.size(), 0, mu_numden_sel.size(), mu_extrig_sel.size()    , 0, mu_extrig_sel.size()    ));
        hc.Add(new TH2I("h_mu_iso_trig_count", "Muon Iso Trigger Count; analysis cuts; trigger cuts", mu_numden_sel.size(), 0, mu_numden_sel.size(), mu_iso_extrig_sel.size(), 0, mu_iso_extrig_sel.size()));
    }


    hc.Sumw2();
    return;
}

    // main analysis function operator
int FakeRateTrigStudy::operator()(long event)
{
    using namespace std;
    using namespace frb;

    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    try
    {
        // base analysis
        at::AnalysisWithHist::operator()(event);

        if (m_lepton=="mu")
        {
            // selections
        	static vector<category_t> mu_trig_sel       = MuTrigTypeFactory();
        	static vector<category_t> mu_anal_sel       = MuAnalTypeFactory();
        	static vector<category_t> mu_extrig_sel     = MuExTrigTypeFactory();
        	static vector<category_t> mu_iso_extrig_sel = MuIsoExTrigTypeFactory();
        	static vector<category_t> mu_numden_sel     = MuNumDenFactory();

            // fill flow counts
            for (size_t itrig = 0; itrig != mu_trig_sel.size(); itrig++)
            {
                category_t& trig = mu_trig_sel.at(itrig);
                if (!trig.passes_cut())
                {
                    // we're done with this trigger
                    continue;
                }

                for (size_t ianal = 0; ianal != mu_anal_sel.size(); ianal++)
                {
                    category_t& anal = mu_anal_sel.at(ianal);
                    if (!anal.passes_cut())
                    {
                        // we're done with this lepton
                        break;
                    }

                    if (m_verbose) {cout << trig.name << "\t" << anal.name << endl;}

                    rt::Fill2D(hc["h_mu_flow_count"], ianal, itrig, 1.0);
                }
            }

            // fill trig counts
            for (size_t itrig = 0; itrig != mu_extrig_sel.size(); itrig++)
            {
                category_t& trig = mu_extrig_sel.at(itrig);
                if (!trig.passes_cut())
                {
                    // we're done with this trigger
                    continue;
                }

                for (size_t ianal = 0; ianal != mu_numden_sel.size(); ianal++)
                {
                    category_t& anal = mu_numden_sel.at(ianal);
                    if (!anal.passes_cut())
                    {
                        // we're done with this lepton
                        break;
                    }

                    if (m_verbose) {cout << trig.name << "\t" << anal.name << endl;}

                    rt::Fill2D(hc["h_mu_trig_count"], ianal, itrig, 1.0);
                }
            }

            // fill iso trig counts
            for (size_t itrig = 0; itrig != mu_iso_extrig_sel.size(); itrig++)
            {
                category_t& trig = mu_iso_extrig_sel.at(itrig);
                if (!trig.passes_cut())
                {
                    // we're done with this trigger
                    continue;
                }

                for (size_t ianal = 0; ianal != mu_numden_sel.size(); ianal++)
                {
                    category_t& anal = mu_numden_sel.at(ianal);
                    if (!anal.passes_cut())
                    {
                        // we're done with this lepton
                        break;
                    }

                    if (m_verbose) {cout << trig.name << "\t" << anal.name << endl;}

                    rt::Fill2D(hc["h_mu_iso_trig_count"], ianal, itrig, 1.0);
                }
            }
        }


        if (m_lepton=="el")
        {
            // selections
            static vector<category_t> el_trig_sel         = ElTrigTypeFactory();
            static vector<category_t> el_anal_sel         = ElAnalTypeFactory();
            static vector<category_t> el_extrig_sel       = ElExTrigTypeFactory();
            static vector<category_t> el_noiso_extrig_sel = ElNoIsoExTrigTypeFactory();
            static vector<category_t> el_numden_sel       = ElNumDenFactory();

            // fill flow counts
            for (size_t itrig = 0; itrig != el_trig_sel.size(); itrig++)
            {
                category_t& trig = el_trig_sel.at(itrig);
                if (!trig.passes_cut())
                {
                    // we're done with this trigger
                    continue;
                }

                for (size_t ianal = 0; ianal != el_anal_sel.size(); ianal++)
                {
                    category_t& anal = el_anal_sel.at(ianal);
                    if (!anal.passes_cut())
                    {
                        // we're done with this lepton
                        break;
                    }

                    if (m_verbose) {cout << trig.name << "\t" << anal.name << endl;}

                    rt::Fill2D(hc["h_el_flow_count"], ianal, itrig, 1.0);
                }
            }

            // fill trig counts
            for (size_t itrig = 0; itrig != el_extrig_sel.size(); itrig++)
            {
                category_t& trig = el_extrig_sel.at(itrig);
                if (!trig.passes_cut())
                {
                    // we're done with this trigger
                    continue;
                }

                for (size_t ianal = 0; ianal != el_numden_sel.size(); ianal++)
                {
                    category_t& anal = el_numden_sel.at(ianal);
                    if (!anal.passes_cut())
                    {
                        // we're done with this lepton
                        break;
                    }

                    if (m_verbose) {cout << trig.name << "\t" << anal.name << endl;}

                    rt::Fill2D(hc["h_el_trig_count"], ianal, itrig, 1.0);
                }
            }

            // fill trig counts (no iso)
            for (size_t itrig = 0; itrig != el_noiso_extrig_sel.size(); itrig++)
            {
                category_t& trig = el_noiso_extrig_sel.at(itrig);
                if (!trig.passes_cut())
                {
                    // we're done with this trigger
                    continue;
                }

                for (size_t ianal = 0; ianal != el_numden_sel.size(); ianal++)
                {
                    category_t& anal = el_numden_sel.at(ianal);
                    if (!anal.passes_cut())
                    {
                        // we're done with this lepton
                        break;
                    }

                    if (m_verbose) {cout << trig.name << "\t" << anal.name << endl;}

                    rt::Fill2D(hc["h_el_noiso_trig_count"], ianal, itrig, 1.0);
                }
            }
        }


    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
    }

    // analysis end
    return 0;
} 
