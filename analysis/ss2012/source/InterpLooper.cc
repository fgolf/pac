#include "InterpLooper.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <tr1/array>
#include <cmath>
#include "mcSelections.h"
#include "SSB2012.h"
#include "rt/RootTools.h"
#include "rt/is_equal.h"
#include "at/Predicates.h"
#include "at/VtxReweight.h"
#include "at/DileptonHypType.h"
#include "at/DileptonChargeType.h"
#include "SignalRegion.h"
#include "TTbarBreakDown.h"
#include "ScaleFactors.h"
#include "SignalBinInfo.h"
#include "at/PredSummary.h"
#include "at/FakeRatePrediction.h"
#include "at/FlipRatePrediction.h"
#include "SSB2012.h"
#include "CTable.h"
#include "TEfficiency.h"

typedef std::vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > > vecLorentzVector;

using namespace std;
using namespace at;
using namespace ss;

// construct:
InterpLooper::InterpLooper
(
    const std::string& root_file_name,
    Sample::value_type sample,
    std::vector<unsigned int> sr_nums,
    AnalysisType::value_type analysis_type,
    SignalRegionType::value_type signal_region_type,
    const std::string& fake_rate_file_name,
    const std::string& flip_rate_file_name,
    const std::string& den_hist_file_name,
    bool do_scale_factors,
    bool do_beff_sf,
    float sparm0,
    float sparm1,
    float sparm2,
    float sparm3,
    float sf_flip,
    float fr_unc,
    float fl_unc,
    float mc_unc,
    float lumi,
    bool verbose
)
    : at::AnalysisWithHist(root_file_name)
    , m_lumi(lumi)
    , m_verbose(verbose)
    , m_is_data(at::SampleIsData(sample))
    , m_do_scale_factors(do_scale_factors)
    , m_do_beff_sf(do_beff_sf)
    , m_sparm0(sparm0)
    , m_sparm1(sparm1)
    , m_sparm2(sparm2)
    , m_sparm3(sparm3)
    , m_scale1fb(-999999.0)
    , m_nevts(-999999)
    , m_sf_flip(sf_flip)
    , m_fr_unc(fr_unc)
    , m_fl_unc(fl_unc)
    , m_mc_unc(mc_unc)
    , m_sample(sample)
    , m_sr_nums(sr_nums)
    , m_analysis_type(analysis_type)
    , m_signal_region_type(signal_region_type)
{
    // set the fake rate histograms
    std::auto_ptr<TFile> fake_rate_file(rt::OpenRootFile(fake_rate_file_name));
    cout << "using FR file : " << fake_rate_file->GetName() << endl;
    string mufr_name = "";
    string elfr_name = "";
    switch (m_analysis_type)
    {
        case AnalysisType::high_pt:
            mufr_name = "h_mufr40c_ewkcor";
            elfr_name = "h_elfr40c_ewkcor";
            break;
        case AnalysisType::high_pt_eth:
            mufr_name = "h_mufr40c";
            elfr_name = "h_elfr40c";
            break;
        case AnalysisType::low_pt:
            mufr_name = "h_mufr40c_ewkcor";
            elfr_name = "h_elfr40c_noiso_ewkcor";
            break;
        case AnalysisType::vlow_pt:
            mufr_name = "h_mufr40c_iso_ewkcor";
            elfr_name = "h_elfr40c_noiso_ewkcor";
            break;
        case AnalysisType::higgsino:
            mufr_name = "h_mufr40c_ewkcor";
            elfr_name = "h_elfr40c_ewkcor";
            break;
        default:
            mufr_name = "h_mufr40c";
            elfr_name = "h_elfr40c";
            break;
    }
    h_mufr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get(mufr_name.c_str())->Clone()));
    h_elfr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get(elfr_name.c_str())->Clone()));
    if (not h_mufr) {throw std::runtime_error(Form("ERROR: InterpLooper: %s doesn't exist", mufr_name.c_str()));}
    if (not h_elfr) {throw std::runtime_error(Form("ERROR: InterpLooper: %s doesn't exist", elfr_name.c_str()));}
    h_mufr->SetDirectory(0);
    h_elfr->SetDirectory(0);

    cout << "using mu FR hist : " << h_mufr->GetName() << endl;
    cout << "using el FR hist : " << h_elfr->GetName() << endl;

    // set the fake rate histograms
    std::auto_ptr<TFile> flip_rate_file(rt::OpenRootFile(flip_rate_file_name));
    cout << "using FL file : " << flip_rate_file->GetName() << endl;
    h_flip.reset(dynamic_cast<TH2F*>(flip_rate_file->Get("flipRate")->Clone()));
    if (not h_flip) {throw std::runtime_error("ERROR: InterpLooper: flipRate doesn't exist");}
    h_flip->SetDirectory(0);

    // initialize counters
    for (size_t i = 0; i != m_count_ss.size(); i++) {m_count_ss[i]=0.0;}
    for (size_t i = 0; i != m_count_sf.size(); i++) {m_count_sf[i]=0.0;}
    for (size_t i = 0; i != m_count_df.size(); i++) {m_count_df[i]=0.0;}
    for (size_t i = 0; i != m_count_os.size(); i++) {m_count_os[i]=0.0;}

    // fake and flip rate binning
    m_fr_bin_info = GetFakeRateBinInfo();
    m_fl_bin_info = GetFlipRateBinInfo();

    // denominator hist
    //std::auto_ptr<TFile> den_hist_file(rt::OpenRootFile(den_hist_file_name));
    //cout << "using den hist file : " << den_hist_file->GetName() << endl;
    //h_den.reset(dynamic_cast<TH2F*>(den_hist_file->Get("h_gen_count")->Clone("h_den")));
    //if (not h_den) {throw std::runtime_error("ERROR: InterpLooper: h_den doesn't exist");}
    //h_den->SetDirectory(0);

    // begin job
    BeginJob();
}

// destroy:
InterpLooper::~InterpLooper()
{
}
        
// methods:
void InterpLooper::BeginJob()
{
    // book the histograms
    BookHists();
}

// end job
void InterpLooper::EndJob()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    if (m_verbose)
    {
        hc.List();
    }

    // Get the systematic uncertainty
    SetTotalSystematic();

    // Calcluate Efficiency
    CalculateEfficiency();

    // print raw yields
    CTable t_counts;
    t_counts.setTitle("counts for SS Analysis 2012");
    t_counts.useTitle();
    t_counts.setTable() (                      "mm",          "em",          "ee",         "all")
                        ("count ss" , m_count_ss[0], m_count_ss[1], m_count_ss[2], m_count_ss[3]) 
                        ("count sf" , m_count_sf[0], m_count_sf[1], m_count_sf[2], m_count_sf[3]) 
                        ("count df" , m_count_df[0], m_count_df[1], m_count_df[2], m_count_df[3])
                        ("count os" , m_count_os[0], m_count_os[1], m_count_os[2], m_count_os[3]); 
    cout << endl;
    t_counts.print();
}

const size_t max_sr = 1;

std::string GetSRLabel(ss::SignalRegion::value_type sr)
{
    const unsigned int sr_num = static_cast<unsigned int>(sr);
    return Form((sr < 10 ? "SR0%u_" : "SR%u_"), sr_num);
}

//const std::tr1::array<int, 27> sr_nums = {{ 0,  1,  2,  3,  4,  5,  6,  7,  8, 
//                                           10, 11, 12, 13, 14, 15, 16, 17, 18,
//                                           20, 21, 22, 23, 24, 25, 26, 27, 28}};
//
// const std::tr1::array<int, 3> sr_nums = {{ 0,  1,  21}}; 

// book hists 
void InterpLooper::BookHists()
{
    try
    {
        // convenience alias
        rt::TH1Container& hc = m_hist_container;

        // add denominator count
        //hc.Add(dynamic_cast<TH2F*>(h_den->Clone()));

        // integrated liminositry
        hc.Add(new TH1F("h_lumi", "integrated lumi used for these plots", 10000, 0, 100));

        // Prefix comes from the sample and it is passed to the scanning function
        // Suffix is "ee" "em" "em" "all" which depends on the final state
        // For example: histogram named tt_hnJet_ee would be the Njet distribution
        // for the ee final state in the ttbar sample.
        // MAKE SURE TO CAL SUMW2 FOR EACH 1D HISTOGRAM BEFORE FILLING!!!!!!
        TH1::SetDefaultSumw2(true);

        // bin and label the axes
        SignalBinInfo bi = GetSignalBinInfo(m_sample);
        const string bin_label = GetSignalBinHistLabel(m_sample);

        //for (size_t sr_num = 0; sr_num != max_sr+1; sr_num++)
        for (size_t i = 0; i != m_sr_nums.size(); i++)
        {
            const string sr = GetSRLabel(static_cast<ss::SignalRegion::value_type>(m_sr_nums.at(i))); 
//             cout << i << "\t" << m_sr_nums.at(i) << "\t" << sr << endl;

            hc.Add(new TH2F((sr+"nGenerated"         ).c_str(), (sr+"nGenerated "         +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"nPassing"           ).c_str(), (sr+"nPassing "           +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"effNormNice"        ).c_str(), (sr+"effNormNice "        +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"effNormNicePerc"    ).c_str(), (sr+"effNormNicePerc "    +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"nSF"                ).c_str(), (sr+"nSF "                +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"nDF"                ).c_str(), (sr+"nDF "                +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"nFakes"             ).c_str(), (sr+"nFakes "             +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));    
            hc.Add(new TH2F((sr+"nLepEffUP"          ).c_str(), (sr+"nLepEffUP "          +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"nLepEffDN"          ).c_str(), (sr+"nLepEffDN "          +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"nTrigEffUP"         ).c_str(), (sr+"nTrigEffUP "         +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"nTrigEffDN"         ).c_str(), (sr+"nTrigEffDN "         +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"nJESUP"             ).c_str(), (sr+"nJESUP "             +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"nJESDN"             ).c_str(), (sr+"nJESDN "             +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"nJER"               ).c_str(), (sr+"nJER "               +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"nBTAUP"             ).c_str(), (sr+"nBTAUP "             +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"nBTADN"             ).c_str(), (sr+"nBTADN "             +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"nMETUP"             ).c_str(), (sr+"nMETUP "             +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"nMETDN"             ).c_str(), (sr+"nMETDN "             +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"effErrJES"          ).c_str(), (sr+"effErrJES "          +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"effErrJESUP"        ).c_str(), (sr+"effErrJESUP "        +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"effErrJESDN"        ).c_str(), (sr+"effErrJESDN "        +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"effErrBTA"          ).c_str(), (sr+"effErrBTA "          +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"effErrBTAUP"        ).c_str(), (sr+"effErrBTAUP "        +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"effErrBTADN"        ).c_str(), (sr+"effErrBTADN "        +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"effErrJER"          ).c_str(), (sr+"effErrJER "          +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"effErrMET"          ).c_str(), (sr+"effErrMET "          +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"effErrMETUP"        ).c_str(), (sr+"effErrMETUP "        +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"effErrMETDN"        ).c_str(), (sr+"effErrMETDN "        +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"effErrLepEff"       ).c_str(), (sr+"effErrLepEff "       +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"effErrLepEffUP"     ).c_str(), (sr+"effErrLepEffUP "     +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"effErrLepEffDN"     ).c_str(), (sr+"effErrLepEffDN "     +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"effErrTrigEff"      ).c_str(), (sr+"effErrTrigEff "      +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"effErrTrigEffUP"    ).c_str(), (sr+"effErrTrigEffUP "    +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"effErrTrigEffDN"    ).c_str(), (sr+"effErrTrigEffDN "    +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"effErrTot"          ).c_str(), (sr+"effErrTot "          +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
            hc.Add(new TH2F((sr+"effErrStat"         ).c_str(), (sr+"effErrStat "         +bin_label).c_str(), bi.nbinsx, bi.xmin, bi.xmax, bi.nbinsy, bi.ymin, bi.ymax));
        }

//   KEY: TH2D	SR28_effErrMET;1	SR28_effErrMET
// *  KEY: TH2D	SR28_effErrJES;1	SR28_effErrJES
//   KEY: TH2D	SR28_effErrJER;1	SR28_effErrJER
// *  KEY: TH2D	SR28_effErrBTA;1	SR28_effErrBTA
//   KEY: TH2D	SR28_effErrTot;1	SR28_effErrTot
//   KEY: TH2D	SR28_effErrStat;1	SR28_effErrStat
// *  KEY: TH2D	SR28_effNormNice;1	SR28_effNormNice
//   KEY: TH2D	SR28_effNormNicePerc;1	SR28_effNormNicePerc
//   KEY: TH2D	SR28_effErrMETUP;1	SR28_effErrMETUP
//   KEY: TH2D	SR28_effErrMETDN;1	SR28_effErrMETDN
// *  KEY: TH2D	SR28_effErrJESUP;1	SR28_effErrJESUP
// *  KEY: TH2D	SR28_effErrJESDN;1	SR28_effErrJESDN
// *  KEY: TH2D	SR28_effErrBTAUP;1	SR28_effErrBTAUP
// *  KEY: TH2D	SR28_effErrBTADN;1	SR28_effErrBTADN
// *  KEY: TH2D	SR28_nGenerated;1	SR28_nGenerated
// *  KEY: TH2D	SR28_nPassing;1	SR28_nPassing
        

        return;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return;
    }
}

// main analysis function operator 
int InterpLooper::operator()(long event)
{
    using namespace std;
    using namespace ssb;

    try
    {
        // base analysis
        at::AnalysisWithHist::operator()(event);

        // convenience alias
        rt::TH1Container& hc = m_hist_container;

        // scale 1b (set before cuts) 
        m_scale1fb = scale1fb();
        m_nevts    = nevts();

        // print susy point for the event
        if (m_verbose)
        {
            cout << "SUSY point:" << endl; 
            if (sparm0_name().Length()>0) {cout << Form("%s = %1.2f", sparm0_name().Data(), sparm0()) << endl;}
            if (sparm1_name().Length()>0) {cout << Form("%s = %1.2f", sparm1_name().Data(), sparm1()) << endl;}
            if (sparm2_name().Length()>0) {cout << Form("%s = %1.2f", sparm2_name().Data(), sparm2()) << endl;}
            if (sparm3_name().Length()>0) {cout << Form("%s = %1.2f", sparm3_name().Data(), sparm3()) << endl;}
            cout << endl;
        }

        float mchi, m0, m12, mlsp;
        switch(m_sample)
        {
            case Sample::ttjets:
                m0   = 0.5; // put this in the one x bin
                m12  = 0.5; // put this in the one y bin
                mlsp = 0;
                break;
            case Sample::t1tttt:
                m0   = sparm0();
                m12  = sparm1();
                mlsp = sparm1();
                break;
            case Sample::sbottomtop:
                m0   = sparm0();
                m12  = sparm1();
                mchi = sparm1();
                mlsp = sparm2();
                break;
            case Sample::glusbottom:
                m0   = sparm0();
                m12  = sparm1();
                mchi = sparm2();
                mlsp = sparm3();
                break;
            case Sample::glustop:
                m0   = sparm0();
                m12  = sparm1();
                mchi = sparm2();
                mlsp = sparm2();
                break;
            default:
                m0   = -999999.0; 
                m12  = -999999.0;
                mchi = -999999.0;
                mlsp = -999999.0;
        }
           
        // dilepton hyp type: 1 mm, 2 em, 3 ee
        const at::DileptonHypType::value_type hyp_type = static_cast<at::DileptonHypType::value_type>(dilep_type());

        // selected sparms 
        // ---------------------------------------------------------------------------------------------------------------------------- //

        // if the value of m_m_sparm0 negative, this check is skipped
        if (m_sparm0 >= 0.0f && not rt::is_equal(m_sparm0, sparm0()))
        {
            if (m_verbose) {cout << Form("fails the sparm0 check: %s, %1.2f != %1.2f", sparm0_name().Data(), m_sparm0, sparm0()) << endl;}
            return 0;
        }

        // if the value of m_sparm1 is negative, this check is skipped
        if (m_sparm1 >= 0.0f && not rt::is_equal(m_sparm1, sparm1()))
        {
            if (m_verbose) {cout << Form("fails the sparm1 check: %s, %1.2f != %1.2f", sparm1_name().Data(), m_sparm1, sparm1()) << endl;}
            return 0;
        }

        // if the value of m_sparm2 is negative, this check is skipped
        if (m_sparm2 >= 0.0f && not rt::is_equal(m_sparm2, sparm2()))
        {
            if (m_verbose) {cout << Form("fails the sparm2 check: %s, %1.2f != %1.2f", sparm2_name().Data(), m_sparm2, sparm2()) << endl;}
            return 0;
        }

        // if the value of m_sparm3 is negative, this check is skipped
        if (m_sparm3 >= 0.0f && not rt::is_equal(m_sparm3, sparm3()))
        {
            if (m_verbose) {cout << Form("fails the sparm3 check: %s, %1.2f != %1.2f", sparm3_name().Data(), m_sparm3, sparm3()) << endl;}
            return 0;
        }

        // denominator histograms 
        // ---------------------------------------------------------------------------------------------------------------------------- //

        for (size_t i = 0; i != m_sr_nums.size(); i++)
        {
            const string sr = GetSRLabel(static_cast<ss::SignalRegion::value_type>(m_sr_nums.at(i))); 
            const bool is_signal = (GetSampleInfo(m_sample).type == SampleType::susy); 

            if (is_signal)
            {
                rt::Fill2D(hc[sr+"nGenerated"], m0, m12, 1.0);
            }
            else
            {
                if (event == 0)
                {
                    // full the number of genrated events from the ntuple 
                    // weight for W --> lnu branching fraction in FullLept decay sample
                    const float w = (rt::string_contains(ssb::dataset().Data(), "TTJets_FullLeptMGDecays_8TeV-madgraph") ? 1.0/(0.324*0.324) : 1.0);
                    const float den = nevts(); 
                    rt::Fill2D(hc[sr+"nGenerated"], m0, m12, den*w);
                }
            }
        }

        // selections 
        // ---------------------------------------------------------------------------------------------------------------------------- //

        // hyp type
        if (hyp_type == DileptonHypType::static_size)
        {
            if (m_verbose) {cout << "failing valid hyp type" << endl;}
            return 0;
        }

        // charge type
        DileptonChargeType::value_type charge_type = DileptonChargeType::static_size;
        if (is_ss()) {charge_type = DileptonChargeType::SS;}
        if (is_sf()) {charge_type = DileptonChargeType::SF;}
        if (is_df()) {charge_type = DileptonChargeType::DF;}
        if (is_os()) {charge_type = DileptonChargeType::OS;}  // dont' care about OS
        if (ssb::charge_type() < 0)
        {
            if (m_verbose) {cout << "failing valid hypothesis requirement\t" << ssb::charge_type() << endl;}
            return 0;
        }
        if (charge_type == DileptonChargeType::static_size)
        {
            if (m_verbose) {cout << "failing valid charge type" << endl;}
            return 0;
        }

        // lepton PT requirement
        float mu_min_pt = 0.0;
        float el_min_pt = 0.0;
        switch(m_analysis_type)
        {
            case AnalysisType::high_pt:
                mu_min_pt = 20.0;
                el_min_pt = 20.0;
                break;
            case AnalysisType::high_pt_eth:
                mu_min_pt = 20.0;
                el_min_pt = 20.0;
                break;
            case AnalysisType::hcp:
                mu_min_pt = 20.0;
                el_min_pt = 20.0;
                break;
            case AnalysisType::low_pt:
                mu_min_pt = 10.0;
                el_min_pt = 10.0;
                break;
            case AnalysisType::vlow_pt:
                mu_min_pt = 5.0;
                el_min_pt = 10.0;
                break;
            case AnalysisType::higgsino:
                mu_min_pt = 10.;
                el_min_pt = 10.;
                break;
            default:
                mu_min_pt = 20.0;
                el_min_pt = 20.0;
                break;
        }
        if (lep1_p4().pt() < (abs(lep1_pdgid()==11) ? el_min_pt : mu_min_pt))
        {
            if (m_verbose) {cout << "failing minimum lep1 pT" << endl;}
            return 0;
        }
        if (lep2_p4().pt() < (abs(lep2_pdgid()==11) ? el_min_pt : mu_min_pt))
        {
            if (m_verbose) {cout << "failing minimum lep2 pT" << endl;}
            return 0;
        }

        // only keep MC matched events (MC only)
        //const bool true_ss_event = ((lep1_is_fromw()==1) && (lep2_is_fromw()==1) && (lep1_mc3id()*lep2_mc3id()>0));
        const bool true_ss_event = ((lep1_is_fromw()==1) && (lep2_is_fromw()==1));
        //const bool true_ss_event = ((lep1_is_fromw()>0) && (lep2_is_fromw()>0) && (lep1_mcid()*lep2_mcid()>0));
        //const bool lep1_matched  = (abs(lep1_mc3id())==11 or abs(lep1_mc3id())==13 or abs(lep1_mc3id())==15);
        //const bool lep2_matched  = (abs(lep2_mc3id())==11 or abs(lep2_mc3id())==13 or abs(lep2_mc3id())==15);
        //const bool leps_ss_gen   = (lep1_matched && lep2_matched && lep1_mc3id()*lep2_mc3id()>0);
        //const bool true_ss_event = ((lep1_is_fromw()>0) && (lep2_is_fromw()>0) && (leps_ss_gen));
        if (not true_ss_event)
        {
            if (m_verbose) {cout << "failing MC truth matching" << endl;}
            return 0;
        }

        // count events
        if (dilep_type()==DileptonHypType::MUMU)
        {
            if(is_ss()) m_count_ss[0] += 1.0;
            if(is_sf()) m_count_sf[0] += 1.0;
            if(is_df()) m_count_df[0] += 1.0;
            if(is_os()) m_count_os[0] += 1.0;
        }
        else if (dilep_type()==DileptonHypType::EMU)
        {
            if(is_ss()) m_count_ss[1] += 1.0;
            if(is_sf()) m_count_sf[1] += 1.0;
            if(is_df()) m_count_df[1] += 1.0;
            if(is_os()) m_count_os[1] += 1.0;
        }
        else if (dilep_type()==DileptonHypType::EE)
        {
            if(is_ss()) m_count_ss[2] += 1.0;
            if(is_sf()) m_count_sf[2] += 1.0;
            if(is_df()) m_count_df[2] += 1.0;
            if(is_os()) m_count_os[2] += 1.0;
        }
        // count all 
        {
            if(is_ss()) m_count_ss[3] += 1.0;
            if(is_sf()) m_count_sf[3] += 1.0;
            if(is_df()) m_count_df[3] += 1.0;
            if(is_os()) m_count_os[3] += 1.0;
        }

        // Weight Factors
        // ----------------------------------------------------------------------------------------------------------------------------//

        // no scale factors
        //const float evt_weight = (is_real_data() ? 1.0 : m_lumi * scale1fb());
        float evt_weight = 1.0; 

        // scale
        float vtxw = 1.0;
        //if (m_do_vtx_reweight)
        //{
        //    vtxw = is_real_data() ? 1.0 : vtxweight_n(nvtxs(), is_real_data(), false);
        //}
        evt_weight *= vtxw;

        // apply scale factors
        float evt_weight_lepeff_up  = 0.0;
        float evt_weight_lepeff_dn  = 0.0;
        float evt_weight_trigeff_up = 0.0;
        float evt_weight_trigeff_dn = 0.0;

        if (m_do_scale_factors && not is_real_data())
        {
            // lepton efficiencies
            const float eta1      = (abs(lep1_pdgid()) == 13 ? lep1_p4().eta() : lep1_sc_p4().eta());
            const float eta2      = (abs(lep2_pdgid()) == 13 ? lep2_p4().eta() : lep2_sc_p4().eta());
            evt_weight *= DileptonTagAndProbeScaleFactor(lep1_pdgid(), lep1_p4().pt(), eta1, lep2_pdgid(), lep2_p4().pt(), eta2);

            // trigger scale factor
            evt_weight *= DileptonTriggerScaleFactor(hyp_type, m_analysis_type, lep2_p4());  

            // lepton efficiency systematic uncertainties
            const float lep_eff_syst_unc = DileptonTagAndProbeScaleFactorSystUnc(lep1_pdgid(), lep1_p4().pt(), eta1, lep2_pdgid(), lep2_p4().pt(), eta2);
            evt_weight_lepeff_up = evt_weight * (1.0 + lep_eff_syst_unc); 
            evt_weight_lepeff_dn = evt_weight * (1.0 - lep_eff_syst_unc); 

            // trigger efficiency systematic uncertainties
            const float trig_eff_syst_unc = DileptonTriggerScaleFactorSystUnc();
            evt_weight_trigeff_up = evt_weight * (1.0 + trig_eff_syst_unc); 
            evt_weight_trigeff_dn = evt_weight * (1.0 - trig_eff_syst_unc); 

            if (m_verbose) {cout << "applying event weight          = " << evt_weight << endl;}
            if (m_verbose) {cout << Form("applying event weight lep  %f * (1 +/- %f) = %f / %f", evt_weight,  lep_eff_syst_unc,  evt_weight_lepeff_up,  evt_weight_lepeff_dn)  << endl;}
            if (m_verbose) {cout << Form("applying event weight trig %f * (1 +/- %f) = %f / %f", evt_weight, trig_eff_syst_unc, evt_weight_trigeff_up, evt_weight_trigeff_dn)  << endl;}
        }

        // Fill hists
        // ------------------------------------------------------------------------------------//

        for (size_t i = 0; i != m_sr_nums.size(); i++)
        {
            ss::SignalRegion::value_type signal_region = static_cast<ss::SignalRegion::value_type>(m_sr_nums.at(i));
            const string sr = GetSRLabel(signal_region); 

            // hack for the ++ regions
            if (m_sample == Sample::ttjets && signal_region == ss::SignalRegion::sr31)
            {
                signal_region = ss::SignalRegion::sr30;
            }
            else if (m_sample == Sample::ttjets && signal_region == ss::SignalRegion::sr35)
            {
                signal_region = ss::SignalRegion::sr34;
            }

            if (is_ss()) 
            {
                // scaled numerator counts
                if (PassesSignalRegion(signal_region, m_analysis_type, m_signal_region_type, m_do_beff_sf, ss::SystematicType::None))
                {
                    rt::Fill2D(hc[sr+"nPassing"  ], m0, m12, evt_weight           );
                    rt::Fill2D(hc[sr+"nLepEffUP" ], m0, m12, evt_weight_lepeff_up );
                    rt::Fill2D(hc[sr+"nLepEffDN" ], m0, m12, evt_weight_lepeff_dn );
                    rt::Fill2D(hc[sr+"nTrigEffUP"], m0, m12, evt_weight_trigeff_up);
                    rt::Fill2D(hc[sr+"nTrigEffDN"], m0, m12, evt_weight_trigeff_dn);
                }

                // JEC scale up/scale down
                if (PassesSignalRegion(signal_region, m_analysis_type, m_signal_region_type, m_do_beff_sf, ss::SystematicType::JES_UP))
                {
                    rt::Fill2D(hc[sr+"nJESUP"], m0, m12, evt_weight);
                }

                if (PassesSignalRegion(signal_region, m_analysis_type, m_signal_region_type, m_do_beff_sf, ss::SystematicType::JES_DN))
                {
                    rt::Fill2D(hc[sr+"nJESDN"], m0, m12, evt_weight);
                }

                // JER scale up/scale down
                if (PassesSignalRegion(signal_region, m_analysis_type, m_signal_region_type, m_do_beff_sf, ss::SystematicType::JER))
                {
                    rt::Fill2D(hc[sr+"nJER"], m0, m12, evt_weight);
                }

                // Btag scale up/down
                if (PassesSignalRegion(signal_region, m_analysis_type, m_signal_region_type, m_do_beff_sf, ss::SystematicType::BEFF_UP))
                {
                    rt::Fill2D(hc[sr+"nBTAUP"], m0, m12, evt_weight);
                }

                if (PassesSignalRegion(signal_region, m_analysis_type, m_signal_region_type, m_do_beff_sf, ss::SystematicType::BEFF_DN))
                {
                    rt::Fill2D(hc[sr+"nBTADN"], m0, m12, evt_weight);
                }

                // Btag scale up/down
                if (PassesSignalRegion(signal_region, m_analysis_type, m_signal_region_type, m_do_beff_sf, ss::SystematicType::MET_UP))
                {
                    rt::Fill2D(hc[sr+"nMETUP"], m0, m12, evt_weight);
                }

                if (PassesSignalRegion(signal_region, m_analysis_type, m_signal_region_type, m_do_beff_sf, ss::SystematicType::MET_DN))
                {
                    rt::Fill2D(hc[sr+"nMETDN"], m0, m12, evt_weight);
                }
            }
             else if (is_sf())
             {
                 if (true_ss_event && PassesSignalRegion(signal_region, m_analysis_type, m_signal_region_type, YieldType::base))
                 {
                     const float fr1 = lep1_is_fo() * GetFakeRateValue(lep1_pdgid(), lep1_p4().pt(), lep1_p4().eta());
                     const float fr2 = lep2_is_fo() * GetFakeRateValue(lep2_pdgid(), lep2_p4().pt(), lep2_p4().eta());
                     const float sf_weight = fr1/(1.0 - fr1) + fr2/(1.0 - fr2); 
                     rt::Fill2D(hc[sr+"nSF"], m0, m12, evt_weight * sf_weight);
                 }
             }
             else if (true_ss_event && is_df())
             {
                 if (true_ss_event && PassesSignalRegion(signal_region, m_analysis_type, m_signal_region_type, YieldType::base))
                 {
                     const float fr1 = GetFakeRateValue(lep1_pdgid(), lep1_p4().pt(), lep1_p4().eta());
                     const float fr2 = GetFakeRateValue(lep2_pdgid(), lep2_p4().pt(), lep2_p4().eta());
                     const float df_weight = fr1/(1.0 - fr1) * fr2/(1.0 - fr2); 
                     rt::Fill2D(hc[sr+"nDF"], m0, m12, evt_weight * df_weight);
                 }
             }

        } // end loop over signal regions


        // done with event loop
    }
    catch (std::exception& e)
    {
        cout << e.what() << endl;
    }

    // analysis end
    return 0;
} 

float InterpLooper::GetFakeRateValue(int lep_id, float pt, float eta) const 
{
    using namespace tas;

    if (!h_mufr)
    {
        if (m_verbose) {std::cout << "h_mufr is NULL! returing zero..." << std::endl;}
        return 0.0;
    }

    if (!h_elfr)
    {
        if (m_verbose) {std::cout << "h_elfr is NULL! returing zero..." << std::endl;}
        return 0.0;
    }

    if (abs(lep_id)==13) 
    {
        float max_pt = h_mufr->GetYaxis()->GetXmax()-0.01;
        int pt_bin   = h_mufr->GetYaxis()->FindBin(min(pt, max_pt));
        int eta_bin  = h_mufr->GetXaxis()->FindBin(fabs(eta));
        return h_mufr->GetBinContent(eta_bin, pt_bin);
    }
    else if (abs(lep_id)==11) 
    {
        float max_pt = h_elfr->GetYaxis()->GetXmax()-0.01;
        int pt_bin   = h_elfr->GetYaxis()->FindBin(min(pt, max_pt));
        int eta_bin  = h_elfr->GetXaxis()->FindBin(fabs(eta));
        return h_elfr->GetBinContent(eta_bin, pt_bin);
    }
    return 0.0;
}

float InterpLooper::GetFakeRateError(int lep_id, float pt, float eta) const 
{
    using namespace tas;

    if (!h_mufr)
    {
        if (m_verbose) {std::cout << "h_mufr is NULL! returing zero..." << std::endl;}
        return 0.0;
    }

    if (!h_elfr)
    {
        if (m_verbose) {std::cout << "h_elfr is NULL! returing zero..." << std::endl;}
        return 0.0;
    }

    if (abs(lep_id)==13) 
    {
        float max_pt = h_mufr->GetYaxis()->GetXmax()-0.01;
        int pt_bin   = h_mufr->GetYaxis()->FindBin(min(pt, max_pt));
        int eta_bin  = h_mufr->GetXaxis()->FindBin(fabs(eta));
        return h_mufr->GetBinError(eta_bin, pt_bin);
    }
    else if (abs(lep_id)==11) 
    {
        float max_pt = h_elfr->GetYaxis()->GetXmax()-0.01;
        int pt_bin   = h_elfr->GetYaxis()->FindBin(min(pt, max_pt));
        int eta_bin  = h_elfr->GetXaxis()->FindBin(fabs(eta));
        return h_elfr->GetBinError(eta_bin, pt_bin);
    }
    return 0.0;
}

float InterpLooper::GetFlipRateValue(int lep_id, float pt, float eta) const 
{
    using namespace tas;

    // only applies to electrons
    if (abs(lep_id) != 11)
    {
        return 0.0;
    }

    if (!h_flip)
    {
        if (m_verbose) {std::cout << "h_flip is NULL! returing zero..." << std::endl;}
        return 0.0;
    }

    float max_pt = h_flip->GetYaxis()->GetXmax()-0.01;
    int pt_bin   = h_flip->GetYaxis()->FindBin(min(pt, max_pt));
    int eta_bin  = h_flip->GetXaxis()->FindBin(fabs(eta));
    return h_flip->GetBinContent(eta_bin, pt_bin);
}

float InterpLooper::GetFlipRateError(int lep_id, float pt, float eta) const 
{
    using namespace tas;

    // only applies to electrons
    if (abs(lep_id) != 11)
    {
        return 0.0;
    }

    if (!h_flip)
    {
        if (m_verbose) {std::cout << "h_flip is NULL! returing zero..." << std::endl;}
        return 0.0;
    }

    float max_pt = h_flip->GetYaxis()->GetXmax()-0.01;
    int pt_bin   = h_flip->GetYaxis()->FindBin(min(pt, max_pt));
    int eta_bin  = h_flip->GetXaxis()->FindBin(fabs(eta));
    return h_flip->GetBinError(eta_bin, pt_bin);
}

at::FakeRateBinInfo InterpLooper::GetFakeRateBinInfo() const
{
    const size_t num_mu_eta_bins = h_mufr->GetNbinsX();
    const float *mu_eta_bins = rt::ConvertDoubleArrayToFloatArray(h_mufr->GetXaxis()->GetXbins()->GetArray(), num_mu_eta_bins+1);

    const size_t num_mu_pt_bins = h_mufr->GetNbinsY();
    const float *mu_pt_bins = rt::ConvertDoubleArrayToFloatArray(h_mufr->GetYaxis()->GetXbins()->GetArray(), num_mu_pt_bins+1);

    const size_t num_el_eta_bins = h_elfr->GetNbinsX();
    const float *el_eta_bins = rt::ConvertDoubleArrayToFloatArray(h_elfr->GetXaxis()->GetXbins()->GetArray(), num_el_eta_bins+1);

    const size_t num_el_pt_bins = h_elfr->GetNbinsY();
    const float *el_pt_bins = rt::ConvertDoubleArrayToFloatArray(h_elfr->GetYaxis()->GetXbins()->GetArray(), num_el_pt_bins+1);

    at::FakeRateBinInfo tmp;
    tmp.vel_eta_bins.assign(el_eta_bins, el_eta_bins+num_el_eta_bins+1);
    tmp.vel_pt_bins .assign(el_pt_bins , el_pt_bins +num_el_pt_bins+1 );

    tmp.vmu_eta_bins.assign(mu_eta_bins, mu_eta_bins+num_mu_eta_bins+1);
    tmp.vmu_pt_bins .assign(mu_pt_bins , mu_pt_bins +num_mu_pt_bins+1 );

    return tmp;
}

at::FlipRateBinInfo InterpLooper::GetFlipRateBinInfo() const
{
    const size_t num_eta_bins = h_flip->GetNbinsX();
    const float *eta_bins = rt::ConvertDoubleArrayToFloatArray(h_flip->GetXaxis()->GetXbins()->GetArray(), num_eta_bins+1);

    const size_t num_pt_bins = h_flip->GetNbinsY();
    const float *pt_bins = rt::ConvertDoubleArrayToFloatArray(h_flip->GetYaxis()->GetXbins()->GetArray(), num_pt_bins+1);

    at::FlipRateBinInfo tmp;
    tmp.v_eta_bins.assign(eta_bins, eta_bins+num_eta_bins+1);
    tmp.v_pt_bins .assign(pt_bins , pt_bins +num_pt_bins+1 );

    return tmp;
}

void InterpLooper::SetJESSystematic()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    for (size_t i = 0; i != m_sr_nums.size(); i++)
    {
        const string sr = GetSRLabel(static_cast<ss::SignalRegion::value_type>(m_sr_nums.at(i))); 

        unsigned int nbinsx = hc[sr+"nPassing"]->GetNbinsX()+1;
        unsigned int nbinsy = hc[sr+"nPassing"]->GetNbinsY()+1;
        for (unsigned int ix = 1; ix < nbinsx; ix++) 
        {
            for (unsigned int iy = 1; iy < nbinsy; iy++) 
            {
                const float num      = hc[sr+"nPassing"  ]->GetBinContent(ix, iy);
                const float num_up   = hc[sr+"nJESUP"    ]->GetBinContent(ix, iy);
                const float num_down = hc[sr+"nJESDN"    ]->GetBinContent(ix, iy);            
                const float den      = hc[sr+"nGenerated"]->GetBinContent(ix, iy);

                float jec_syst_up = 0.0f;
                float jec_syst_dn = 0.0f;
                if (den > 0 && num > 0) 
                {
                    jec_syst_up = (num_up-num  ) / num;
                    jec_syst_dn = (num_down-num) / num;
                    hc[sr+"effErrJESUP"]->SetBinContent(ix, iy, 1.0 + jec_syst_up);
                    hc[sr+"effErrJESDN"]->SetBinContent(ix, iy, 1.0 + jec_syst_dn);
                }
                hc[sr+"effErrJES"]->SetBinContent(ix, iy, std::max(fabs(jec_syst_up), fabs(jec_syst_dn)));
            }
        }
    } // end sr loop
    return;
}

void InterpLooper::SetLepEffSystematic()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    for (size_t i = 0; i != m_sr_nums.size(); i++)
    {
        const string sr = GetSRLabel(static_cast<ss::SignalRegion::value_type>(m_sr_nums.at(i))); 

        unsigned int nbinsx = hc[sr+"nPassing"]->GetNbinsX()+1;
        unsigned int nbinsy = hc[sr+"nPassing"]->GetNbinsY()+1;
        for (unsigned int ix = 1; ix < nbinsx; ix++) 
        {
            for (unsigned int iy = 1; iy < nbinsy; iy++) 
            {
                const float num      = hc[sr+"nPassing"  ]->GetBinContent(ix, iy);
                const float num_up   = hc[sr+"nLepEffUP" ]->GetBinContent(ix, iy);
                const float num_down = hc[sr+"nLepEffDN" ]->GetBinContent(ix, iy);            
                const float den      = hc[sr+"nGenerated"]->GetBinContent(ix, iy);

                float lepeff_syst_up = 0.0f;
                float lepeff_syst_dn = 0.0f;
                if (den > 0 && num > 0) 
                {
                    lepeff_syst_up = (num_up-num  ) / num;
                    lepeff_syst_dn = (num_down-num) / num;
                    hc[sr+"effErrLepEffUP"]->SetBinContent(ix, iy, 1.0 + lepeff_syst_up);
                    hc[sr+"effErrLepEffDN"]->SetBinContent(ix, iy, 1.0 + lepeff_syst_dn);
                }
                hc[sr+"effErrLepEff"]->SetBinContent(ix, iy, std::max(fabs(lepeff_syst_up), fabs(lepeff_syst_dn)));
            }
        }
    } // end sr loop
    return;
}

void InterpLooper::SetTrigEffSystematic()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    for (size_t i = 0; i != m_sr_nums.size(); i++)
    {
        const string sr = GetSRLabel(static_cast<ss::SignalRegion::value_type>(m_sr_nums.at(i))); 

        unsigned int nbinsx = hc[sr+"nPassing"]->GetNbinsX()+1;
        unsigned int nbinsy = hc[sr+"nPassing"]->GetNbinsY()+1;
        for (unsigned int ix = 1; ix < nbinsx; ix++) 
        {
            for (unsigned int iy = 1; iy < nbinsy; iy++) 
            {
                const float num      = hc[sr+"nPassing"  ]->GetBinContent(ix, iy);
                const float num_up   = hc[sr+"nTrigEffUP"]->GetBinContent(ix, iy);
                const float num_down = hc[sr+"nTrigEffDN"]->GetBinContent(ix, iy);            
                const float den      = hc[sr+"nGenerated"]->GetBinContent(ix, iy);

                float trigeff_syst_up = 0.0f;
                float trigeff_syst_dn = 0.0f;
                if (den > 0 && num > 0) 
                {
                    trigeff_syst_up = (num_up-num  ) / num;
                    trigeff_syst_dn = (num_down-num) / num;
                    hc[sr+"effErrTrigEffUP"]->SetBinContent(ix, iy, 1.0 + trigeff_syst_up);
                    hc[sr+"effErrTrigEffDN"]->SetBinContent(ix, iy, 1.0 + trigeff_syst_dn);
                }
                hc[sr+"effErrTrigEff"]->SetBinContent(ix, iy, std::max(fabs(trigeff_syst_up), fabs(trigeff_syst_dn)));
            }
        }
    } // end sr loop
    return;
}


void InterpLooper::SetJERSystematic()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    for (size_t i = 0; i != m_sr_nums.size(); i++)
    {
        const string sr = GetSRLabel(static_cast<ss::SignalRegion::value_type>(m_sr_nums.at(i))); 

        unsigned int nbinsx = hc[sr+"nPassing"]->GetNbinsX()+1;
        unsigned int nbinsy = hc[sr+"nPassing"]->GetNbinsY()+1;
        for (unsigned int ix = 1; ix < nbinsx; ix++) 
        {
            for (unsigned int iy = 1; iy < nbinsy; iy++) 
            {
                const float num      = hc[sr+"nPassing"  ]->GetBinContent(ix, iy);
                const float num_up   = hc[sr+"nJER"      ]->GetBinContent(ix, iy);
                const float den      = hc[sr+"nGenerated"]->GetBinContent(ix, iy);

                if (den > 0 && num > 0) 
                {
                    const float jer_syst = (num_up-num) / num;
                    hc[sr+"effErrJER"]->SetBinContent(ix, iy, 1.0 + jer_syst);
//                     hc[sr+"effErrJER"]->SetBinContent(ix, iy, num_up/den);
                }
            }
        }
    } // end sr loop
    return;
}

void InterpLooper::SetMETSystematic()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    for (size_t i = 0; i != m_sr_nums.size(); i++)
    {
        const string sr = GetSRLabel(static_cast<ss::SignalRegion::value_type>(m_sr_nums.at(i))); 

        unsigned int nbinsx = hc[sr+"nPassing"]->GetNbinsX()+1;
        unsigned int nbinsy = hc[sr+"nPassing"]->GetNbinsY()+1;
        for (unsigned int ix = 1; ix < nbinsx; ix++) 
        {
            for (unsigned int iy = 1; iy < nbinsy; iy++) 
            {
                const float num      = hc[sr+"nPassing"  ]->GetBinContent(ix, iy);
                const float num_up   = hc[sr+"nMETUP"    ]->GetBinContent(ix, iy);
                const float num_down = hc[sr+"nMETDN"    ]->GetBinContent(ix, iy);            
                const float den      = hc[sr+"nGenerated"]->GetBinContent(ix, iy);

                float met_syst_up = 0.0f;
                float met_syst_dn = 0.0f;
                if (den > 0 && num > 0) 
                {
                    met_syst_up = (num_up-num  ) / num;
                    met_syst_dn = (num_down-num) / num;
                    hc[sr+"effErrMETUP"]->SetBinContent(ix, iy, 1.0 + met_syst_up);
                    hc[sr+"effErrMETDN"]->SetBinContent(ix, iy, 1.0 + met_syst_dn);
                }
                hc[sr+"effErrMET"]->SetBinContent(ix, iy, std::max(fabs(met_syst_up), fabs(met_syst_dn)));
            }
        }
    } // end sr loop
    return;
}


// NOT SURE if this is right -- ask FG
void InterpLooper::SetBtagSystematic()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    for (size_t i = 0; i != m_sr_nums.size(); i++)
    {
        const string sr = GetSRLabel(static_cast<ss::SignalRegion::value_type>(m_sr_nums.at(i))); 

        unsigned int nbinsx = hc[sr+"nPassing"]->GetNbinsX()+1;
        unsigned int nbinsy = hc[sr+"nPassing"]->GetNbinsY()+1;
        for (unsigned int ix = 1; ix < nbinsx; ix++)
        {
            for (unsigned int iy = 1; iy < nbinsy; iy++)
            {
                const float num      = hc[sr+"nPassing"  ]->GetBinContent(ix, iy);
                const float num_up   = hc[sr+"nBTAUP"    ]->GetBinContent(ix, iy);
                const float num_down = hc[sr+"nBTADN"    ]->GetBinContent(ix, iy);            
                const float den      = hc[sr+"nGenerated"]->GetBinContent(ix, iy);

                float btag_syst_up = 0.0f;
                float btag_syst_dn = 0.0f;
                if (den > 0 && num > 0) 
                {
                    btag_syst_up = (num_up-num  ) / num;
                    btag_syst_dn = (num_down-num) / num;
                    hc[sr+"effErrBTAUP"]->SetBinContent(ix, iy, 1.0 + btag_syst_up);
                    hc[sr+"effErrBTADN"]->SetBinContent(ix, iy, 1.0 + btag_syst_dn);
                }
                hc[sr+"effErrBTA"]->SetBinContent(ix, iy, std::max(fabs(btag_syst_up), fabs(btag_syst_dn)));
            }
        }
    } // end sr loop
    return;
}

void InterpLooper::SetTotalSystematic()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    SetJESSystematic();
    SetJERSystematic();
    SetMETSystematic();
    SetBtagSystematic();
    SetLepEffSystematic();
    SetTrigEffSystematic();

    // taken as constant
    const double lumi = 0.045;
//     const double lep  = 0.05; // not doing low pT analysis yet
//     const double trig = 0.06; // not doing low pT analysis yet
    const double pdf  = 0.02;

    for (size_t i = 0; i != m_sr_nums.size(); i++)
    {
        const string sr = GetSRLabel(static_cast<ss::SignalRegion::value_type>(m_sr_nums.at(i))); 

        unsigned int nbinsx = hc[sr+"nPassing"]->GetNbinsX()+1;
        unsigned int nbinsy = hc[sr+"nPassing"]->GetNbinsY()+1;
        for (unsigned int ix = 1; ix < nbinsx; ix++)
        {
            for (unsigned int iy = 1; iy < nbinsy; iy++)
            {
                const float den        = hc[sr+"nGenerated"]->GetBinContent(ix, iy);
                if (den > 0)
                {
                    const float num        = hc[sr+"nPassing"]->GetBinContent(ix, iy);
                    //const float eff        = num/den;
                    const float jes_syst   = hc[sr+"effErrJES"    ]->GetBinContent(ix, iy);
                    const float jer_syst   = hc[sr+"effErrJER"    ]->GetBinContent(ix, iy);
                    const float met_syst   = hc[sr+"effErrMET"    ]->GetBinContent(ix, iy);
                    const float btag_syst  = hc[sr+"effErrBTA"    ]->GetBinContent(ix, iy);
                    const float lep_syst   = hc[sr+"effErrLepEff" ]->GetBinContent(ix, iy);
                    const float trig_syst  = hc[sr+"effErrTrigEff"]->GetBinContent(ix, iy);
                    const float syst_error = std::sqrt(pow(lumi, 2) + pow(lep_syst, 2) + pow(trig_syst, 2) + pow(pdf, 2) + pow(jes_syst, 2) + pow(jer_syst, 2) + pow(met_syst, 2) + pow(btag_syst, 2));
                    //const float stat_error = (num > 0 ? sqrt(eff*(1.0-eff)/den) : 0); 
                    const float stat_error = rt::GetClopperPearsonUncertainty(static_cast<int>(num), static_cast<int>(den));
                    hc[sr+"effErrTot" ]->SetBinContent(ix, iy, syst_error);
                    hc[sr+"effErrStat"]->SetBinContent(ix, iy, stat_error);
                    if (m_verbose) {cout << "jes, btag, total: " << jes_syst << ", " << btag_syst << ", " << syst_error << endl;}
                }
            }
        }
    } // end sr loop
    return;
}

void InterpLooper::SetTotalSignalContamination()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    for (size_t i = 0; i != m_sr_nums.size(); i++)
    {
        const string sr = GetSRLabel(static_cast<ss::SignalRegion::value_type>(m_sr_nums.at(i))); 

        // Total signal contamination from fakes
        // total fakes = SF - DF
        hc[sr+"nFakes"]->Add(hc[sr+"nSF"], hc[sr+"nDF"], 1.0, -1.0);
    }
    return;
}

void InterpLooper::CalculateEfficiency()
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    // get signal contamination
    SetTotalSignalContamination();

    for (size_t i = 0; i != m_sr_nums.size(); i++)
    {
        const string sr = GetSRLabel(static_cast<ss::SignalRegion::value_type>(m_sr_nums.at(i))); 

        unsigned int nbinsx = hc[sr + "nGenerated"]->GetNbinsX()+1;
        unsigned int nbinsy = hc[sr + "nGenerated"]->GetNbinsY()+1;
        for (unsigned int ix = 1; ix < nbinsx; ix++)
        {
            for (unsigned int iy = 1; iy < nbinsy; iy++)
            {
                const float num   = hc[sr+"nPassing"  ]->GetBinContent(ix, iy);
                //const float fakes = hc[sr+"nFakes"    ]->GetBinContent(ix ,iy);
                const float den   = hc[sr+"nGenerated"]->GetBinContent(ix ,iy);

                if (den > 0.0) 
                {
                    float eff = 0.0;
                    if (num >= 0.0)
                    {
                        //eff = fabs(num - fakes) / den;  // central value of eps*A*BR
                        eff = fabs(num) / den;  // central value of eps*A*BR
                    }
                    hc[sr+"effNormNice"    ]->SetBinContent(ix, iy, eff      );
                    hc[sr+"effNormNicePerc"]->SetBinContent(ix, iy, eff*100.0);
                }
                else
                {
                    hc[sr+"effNormNice"    ]->SetBinContent(ix, iy, 0.0);
                    hc[sr+"effNormNicePerc"]->SetBinContent(ix, iy, 0.0);
                }
            }
        }
    } // end sr loop
    return;
}

//void makeTextFile::getUpperLimits (enum SignalRegion signal_region) {
//
//    unsigned int sid = (unsigned int)signal_region;
//    if (signal_region == HIGH_M0)
//        sid = (unsigned int)LOW_M0;
//    else if (signal_region == LOW_M0)
//        sid = (unsigned int)HIGH_M0;
//    sid++;
//    
//    unsigned int nbinsx = hsyst->GetNbinsX()+1;
//    unsigned int nbinsy = hsyst->GetNbinsY()+1;
//    for (unsigned int ix = 1; ix < nbinsx; ix++) {
//        for (unsigned int iy = 1; iy < nbinsy; iy++) {
//            
//            float syst = hsyst->GetBinContent(ix, iy);
//
//            float exp = getLimitSSb(sid, syst, false);
//            float obs = getLimitSSb(sid, syst, true);
//
//            hexp->SetBinContent(ix, iy, exp);
//            hobs->SetBinContent(ix, iy, obs);
//        }
//    }
//    
//    return;    
//}

