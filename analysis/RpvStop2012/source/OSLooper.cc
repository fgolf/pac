#include "OSLooper.h"

// c++
#include <stdexcept>
#include <algorithm>
#include <fstream>

// cms2
#include "osSelections.h"
#include "eventSelections.h"
#include "trackSelections.h"
#include "susySelections.h"
#include "mcbtagSFuncert.h"
#include "mcSelections.h"
#include "electronSelections.h"
#include "muonSelections.h"
#include "jetSelections.h"
#include "metSelections.h"
#include "jetcorr/FactorizedJetCorrector.h"
#include "jetcorr/JetCorrectionUncertainty.h"
#include "MT2/MT2.h"

// Tools
#include "OSTree.h"
#include "at/Predicates.h"
#include "at/DileptonHypType.h"
#include "at/DileptonChargeType.h"
#include "at/VtxReweight.h"
#include "at/GoodRun.h"
#include "at/PrintIdIsoInfo.h"
#include "at/MCBtagCount.h"
#include "at/CMS2Tag.h"
#include "at/TrackIsoTools.h"
#include "rt/RootTools.h"
#include "CTable.h"
#include "GenParticleStruct.h"
#include "EfficiencyModelTools.h"
#include "ScaleFactors.h"
#include "TTbarBreakDown.h"

// ROOT
#include "Math/LorentzVector.h"
#include "Math/Vector2D.h"
#include "TH2F.h"

// typdefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef std::vector<LorentzVector> vecLorentzVector;

using namespace tas;
using namespace std;
using namespace at;
using namespace rpv_stop;

// get the best hyp
struct HypInfo
{
    HypInfo(int i, const at::DileptonHypType::value_type& h);
    int idx;
    at::DileptonHypType::value_type hyp_type;

    // scalar sum pT between the two leptons
    float pt() const;

    // lower means higher priority
    bool operator < (const HypInfo& rhs) const;  
};

HypInfo::HypInfo(int i, const at::DileptonHypType::value_type& h)
    : idx(i)
    , hyp_type(h)
{
}

float HypInfo::pt() const
{
    if (idx < 0)
    {
        return -999999.0;
    }
    if (static_cast<size_t>(idx) >= hyp_lt_p4().size())
    {
        return -999999.0;
    }
    return (hyp_lt_p4().at(idx).pt() + hyp_ll_p4().at(idx).pt());
}
    
bool HypInfo::operator < (const HypInfo& rhs) const
{
    // hyp type 
    if (hyp_type < rhs.hyp_type) {return true;}
    if (hyp_type > rhs.hyp_type) {return false;}

    // sum pt
    if (pt() > rhs.pt())  {return true;}
    if (pt() <= rhs.pt()) {return false;}

    return false;
}

// use delta R to match
void SetBtagDiscriminator(const vector<LorentzVector>& jets_p4, vector<float>& jets_disc, enum BtagType btag_type)
{
    using namespace tas;

    if (jets_p4.empty())
    {
        return;
    }
    jets_disc.clear();
    const vector<float>& btags = pfjets_combinedSecondaryVertexBJetTag();
    for (size_t j = 0; j < jets_p4.size(); j++)
    {
        for (size_t i = 0; i < pfjets_p4().size(); i++)
        { 
            if (rt::DeltaR(pfjets_p4().at(i), jets_p4.at(j)) < 0.0001) 
            {
                jets_disc.push_back(btags.at(i));
                break;
            }
        }
    }
    return;
}

void PrintJetInfo(const std::string& label, const vector<LorentzVector>& jets_p4)
{
    cout << label << ":" << endl;
    for (size_t i = 0; i < jets_p4.size(); i++)
    {
        LorentzVector jet_p4 = jets_p4.at(i);
        cout << Form("idx %d, pt %f, eta %f, phi %f", (int)i, jet_p4.pt(), jet_p4.eta(), jet_p4.phi()) << endl;
    }
}

// construct:
RpvStopOSAnalysisLooper::RpvStopOSAnalysisLooper
(
    const std::string& root_file_name,
    const Sample::value_type& sample,
    const AnalysisType::value_type& analysis_type,
    const std::string& vtxreweight_file_name,
    const std::string& goodrun_file_name,
    const double luminosity,
    const int jetMetScale,
    const bool is_fast_sim,
    const bool sync_print,
    const bool verbose,
    const std::string apply_jec_otf,
    const std::string apply_jec_unc,
    const double jet_pt_cut
)
    : AnalysisWithTreeAndHist(root_file_name, "tree", "baby tree for EWKINO 2012 SS analysis")
    , m_sample(sample)
    , m_analysis_type(analysis_type)
    , m_lumi(luminosity)
    , m_jetMetScale(jetMetScale)
    , m_is_fast_sim(is_fast_sim)
    , m_filter_bad_runs(false)
    , m_sync_print(sync_print)
    , m_verbose(verbose || sync_print)
    , m_jet_pt_cut(jet_pt_cut) 
    , m_hyp_count(0)
{
    // set vertex weight file
    if (!vtxreweight_file_name.empty())
    {
        cout << "using vertex reweight file : " << vtxreweight_file_name << endl;
        set_vtxreweight_rootfile(vtxreweight_file_name.c_str(), m_verbose);
    }

    // set the "good run" list 
    if (!goodrun_file_name.empty())
    {
        m_filter_bad_runs = true;
        set_goodrun_file(goodrun_file_name.c_str());
        //set_goodrun_file_json(goodrun_file_name.c_str());
    }

    // set the "on-the-fly" JEC
    if (!apply_jec_otf.empty())
    {
        m_list_of_jec_filenames.clear();

        std::string temp_jec_string = rt::string_upper(apply_jec_otf);
        temp_jec_string = rt::string_remove_all(temp_jec_string, "::ALL");
        const at::SampleType::value_type sample_type = at::GetSampleInfo(m_sample).type;

        std::string path = rt::getenv("CMS2_CORE");
        if (!path.empty())
        {
            path += "/jetcorr/data/";
            m_list_of_jec_filenames.push_back(Form("%s/%s_L1FastJet_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            m_list_of_jec_filenames.push_back(Form("%s/%s_L2Relative_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            m_list_of_jec_filenames.push_back(Form("%s/%s_L3Absolute_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            if (sample_type == at::SampleType::data)
            {
                m_list_of_jec_filenames.push_back(Form("%s/%s_L2L3Residual_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            }
        }
        else
        {
            path = "./";
            m_list_of_jec_filenames.push_back(Form("%s/%s_L1FastJet_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            m_list_of_jec_filenames.push_back(Form("%s/%s_L2Relative_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            m_list_of_jec_filenames.push_back(Form("%s/%s_L3Absolute_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            if (sample_type == at::SampleType::data)
            {
                m_list_of_jec_filenames.push_back(Form("%s/%s_L2L3Residual_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            }
        }

        printf("[RpvStopOSAnalysisLooper] making jet and MET correctors with: \n");
        for (unsigned int idx = 0; idx < m_list_of_jec_filenames.size(); idx++)
        {
            if (rt::exists(m_list_of_jec_filenames.at(idx)))
            {
                printf("\t%s\n", m_list_of_jec_filenames.at(idx).c_str());
            }
            else
            {
                printf("\tFILE %s doesn't exist.\n", m_list_of_jec_filenames.at(idx).c_str());
            }
        }
        
        m_jet_corrector.reset(makeJetCorrector(m_list_of_jec_filenames));
        if (not m_jet_corrector)
        {
            throw std::runtime_error("ERROR: RpvStopOSAnalysisLooper: unable to create jet_corrector");
        }
        m_met_corrector.reset(new MetCorrector(m_list_of_jec_filenames));
        if (not m_met_corrector)
        {
            throw std::runtime_error("ERROR: RpvStopOSAnalysisLooper: unable to create met_corrector");
        }
    }

    // set the "on-the-fly" Uncertainty
    if (!apply_jec_unc.empty())
    {
        std::string temp_jec_string = rt::string_upper(apply_jec_unc);
        temp_jec_string = rt::string_remove_all(temp_jec_string, "::ALL");

        std::string path = rt::getenv("CMS2CORE");
        if (!path.empty())
        {
            path += "/jetcorr/data";
        }
        else
        {
            path = "./";
        }
        printf("[RpvStopOSAnalysisLooper] making jet and MET correctors uncertainties with: \n");
        const string jes_unc_file = Form("%s/%s_Uncertainty_AK5PF.txt", path.c_str(), temp_jec_string.c_str());
        if (rt::exists(jes_unc_file))
        {
            printf("\t%s\n", jes_unc_file.c_str());
        }
        else
        {
            printf("\tFILE %s doesn't exist.\nUsing default values hard coded in jetSelections.cc", jes_unc_file.c_str());
        }
        m_jet_corr_unc.reset(new JetCorrectionUncertainty(jes_unc_file));
        if (not m_jet_corr_unc)
        {
            throw std::runtime_error("ERROR: RpvStopOSAnalysisLooper: unable to create jet_corr_unc");
        }
    }

    // initialize counters
    for (size_t i = 0; i != m_count_os.size(); i++) {m_count_os[i]=0.0;}
    for (size_t i = 0; i != m_count_nobtag_os.size(); i++) {m_count_nobtag_os[i]=0.0;}

    cout << "sample: " << m_sample << endl;
    cout << "analysis: " << m_analysis_type << endl;
    cout.flush();

    // get jet pt cut
    if (m_jet_pt_cut < 0.0f)
    {
        m_jet_pt_cut = 30.0f;
    }

    cout << "[RpvStopOSAnalysisLooper] using jet pT cut : " << m_jet_pt_cut << endl;

    // begin job
    BeginJob();
}

// destroy:
RpvStopOSAnalysisLooper::~RpvStopOSAnalysisLooper()
{
//     delete m_jet_corrector;
//     delete m_met_corrector;
}

// function operator: operate on each event
int RpvStopOSAnalysisLooper::operator() (long event, const std::string& filename)
{
    // call base class operator
    return Analyze(event, filename);
}

// members:
void RpvStopOSAnalysisLooper::BeginJob()
{
    // initialize hists
    BookHists();

    // initialize branches
    m_evt.Reset();
    m_evt.SetBranches(*m_tree);

    if (m_sync_print)
    {
        cout << "Run | LS | Event | channel | dilep Mass | " 
                "Lep1Pt | Lep1Eta | Lep1Phi | Lep1ID | Lep1Iso | "
                "Lep2Pt | Lep2Eta | Lep2Phi | Lep2ID | Lep1Iso | "
                "MET | HT | nJets | nbJets" 
             << endl;
    }
}

void RpvStopOSAnalysisLooper::BookHists()
{
    rt::TH1Container& hc = m_hist_container;

    // // generated event count hist
    // if (m_sparms)
    // {
    //     rpv_stop::SignalBinInfo bin_info = rpv_stop::GetSignalBinInfo(m_sample);
    //     const std::string title = Form("# of Generated Events - %s", rpv_stop::GetSignalBinHistLabel(m_sample).c_str());
    //     hc.Add(new TH2F("h_gen_count", title.c_str(), bin_info.nbinsx, bin_info.xmin, bin_info.xmax, bin_info.nbinsy, bin_info.ymin, bin_info.ymax));
    // }
}


void RpvStopOSAnalysisLooper::EndJob()
{
    cout << "Number of dilepton hypotheses passing pT > 20, 20; |eta| < 2.4, 2.4; OS:\t" << m_hyp_count << endl;

    CTable yield_table;
    yield_table.setTitle("yields for RPV STOP 2012 OS Analysis (baseline)");
    yield_table.useTitle();
    yield_table.setTable() (                      "mm",          "em",          "ee",         "all")
                           ("count os" , m_count_os[0], m_count_os[1], m_count_os[2], m_count_os[3]); 
    yield_table.print();

    // call base class end job
    rt::TH1Container& hc = m_hist_container;
    if (m_verbose)
    {
        hc.List();
    }
    
    AnalysisWithTreeAndHist::EndJob();
}

int RpvStopOSAnalysisLooper::SetJetCorrector(std::vector<std::string> &list_of_filenames)
{
    printf("[RpvStopOSAnalysisLooper] making jet corrector with: \n");
    for (unsigned int idx = 0; idx < list_of_filenames.size(); idx++)
    {
        printf("\t%s\n", list_of_filenames.at(idx).c_str());
    }

    m_jet_corrector.reset(makeJetCorrector(list_of_filenames));
    m_met_corrector.reset(new MetCorrector(list_of_filenames));
    if (!m_jet_corrector && !m_met_corrector) return 1;
    return 0;
}

int RpvStopOSAnalysisLooper::Analyze(const long event, const std::string& filename)
{
    // convenience alias
    rt::TH1Container& hc = m_hist_container;

    try
    {
        // Reset Tree Variables
        // --------------------------------------------------------------------------------------------------------- //

        m_evt.Reset();

        // set good good runs 
        // --------------------------------------------------------------------------------------------------------- //

        // default is true since it means we're not applying a good run list
        if (m_filter_bad_runs)
        {
            if (tas::evt_isRealData())
            {
                // check for good run and events
                if(!goodrun(tas::evt_run(), tas::evt_lumiBlock())) 
                    //if(!goodrun_json(tas::evt_run(), tas::evt_lumiBlock())) 
                {
                    //if (m_verbose) {cout << "Bad run and lumi:\t" << tas::evt_run() << ", " << tas::evt_lumiBlock() << endl;}
                    //return 0;
                    m_evt.is_good_lumi = false;
                }
                else
                {
                    //if (m_verbose) {cout << "Good run and lumi:\t" << tas::evt_run() << ", " << tas::evt_lumiBlock() << endl;}
                    m_evt.is_good_lumi = true;
                }
            }
        }

        // event logic variables 
        // --------------------------------------------------------------------------------------------------------- //

        // trigger options 
        int trigger_option = -999999;
        switch (m_analysis_type)
        {
            case AnalysisType::mmbb    : trigger_option = 0; break;
            case AnalysisType::static_size: break; // no default is intentional so that compiler issues a warning if you don't handle all the cases
        }

        // lepton pT cut values
        float min_lep_pt = 0.0;
        switch(m_analysis_type)
        {
            case AnalysisType::mmbb:
                min_lep_pt = 20.0;
                break;
            default:
                min_lep_pt = 20.0;
                break;
        }

        // gen level  
        // --------------------------------------------------------------------------------------------------------- //

        if (not evt_isRealData())
        {
            // sparms parameters
            // if (m_sparms) 
            // {
            //     const size_t n_sparms = sparm_values().size();
            //     if (n_sparms > 0) {m_evt.sparm0 = sparm_values().at(0); m_evt.sparm0_name = static_cast<TString>(sparm_names().at(0));}
            //     if (n_sparms > 1) {m_evt.sparm1 = sparm_values().at(1); m_evt.sparm1_name = static_cast<TString>(sparm_names().at(1));}
            //     if (n_sparms > 2) {m_evt.sparm2 = sparm_values().at(2); m_evt.sparm2_name = static_cast<TString>(sparm_names().at(2));}
            //     if (n_sparms > 3) {m_evt.sparm3 = sparm_values().at(3); m_evt.sparm3_name = static_cast<TString>(sparm_names().at(3));}

            //     // fill the generated event count
            //     // --------------------------------------------------------------------------------------------------------- //
            //     hc["h_gen_count"]->Fill(m_evt.sparm0, m_evt.sparm1);
            // }

            // lepton variables
            std::pair<GenParticleStruct, GenParticleStruct> best_gen_hyp = efftools::getGenHyp(min_lep_pt, min_lep_pt, DileptonChargeType::OS);
            if (best_gen_hyp.first.id_ == 0 || best_gen_hyp.second.id_ == 0)
            {
                if (m_verbose) {cout << "AnalysisLooper: does not have a good gen hyp" << endl;} 
                m_evt.gen_dilep_type = at::DileptonHypType::static_size; 
            }
            else
            {
                int   id1  = abs(best_gen_hyp.first.id_ ) == 15 ? best_gen_hyp.first.did_   : best_gen_hyp.first.id_;
                int   idx1 = abs(best_gen_hyp.first.id_ ) == 15 ? best_gen_hyp.first.didx_  : best_gen_hyp.first.idx_;
                int   id2  = abs(best_gen_hyp.second.id_) == 15 ? best_gen_hyp.second.did_  : best_gen_hyp.second.id_;
                int   idx2 = abs(best_gen_hyp.second.id_) == 15 ? best_gen_hyp.second.didx_ : best_gen_hyp.second.idx_;

                // get LorenzVectors
                LorentzVector p41;
                if (abs(best_gen_hyp.first.id_) == 15)
                { 
                    p41 = genps_lepdaughter_p4().at(best_gen_hyp.first.idx_).at(idx1);
                }
                else
                {
                    p41 = genps_p4().at(idx1);
                }

                LorentzVector p42;
                if (abs(best_gen_hyp.second.id_) == 15)
                {
                    p42 = genps_lepdaughter_p4().at(best_gen_hyp.second.idx_).at(idx2);
                }
                else
                {
                    p42 = genps_p4().at(idx2);
                }

                m_evt.gen_lep1_p4    = p41.pt() > p42.pt() ? p41 : p42;
                m_evt.gen_lep1_pdgid = p41.pt() > p42.pt() ? id1 : id1;
                m_evt.gen_lep2_p4    = p41.pt() > p42.pt() ? p42 : p41;
                m_evt.gen_lep2_pdgid = p41.pt() > p42.pt() ? id2 : id1;
                m_evt.gen_dilep_p4   = (p41 + p42);
                m_evt.gen_dilep_type = efftools::getHypType(id1, id2);
                m_evt.gen_dilep_mass = m_evt.gen_dilep_p4.mass();
                m_evt.gen_dilep_dphi = rt::DeltaPhi(p41, p42); 
                m_evt.gen_dilep_deta = rt::DeltaEta(p41, p42); 
                m_evt.gen_dilep_dr   = rt::DeltaR(p41, p42); 

                //
                // store info for third gen lepton, if it exists
                //
                for (unsigned int gidx = 0; gidx < cms2.genps_p4().size(); gidx++)
                {
                    if (gidx == idx1 || gidx == idx2) continue;
                    if (cms2.genps_status().at(gidx) != 3) continue;
                    if (cms2.genps_p4().at(gidx).pt() < m_evt.gen_lep3_p4.pt()) continue;
                    unsigned int gid = abs(cms2.genps_id().at(gidx));
                    if (gid != 11 && gid != 13 && gid != 15) continue;
                    if (gid == 15)
                    {
                        float pt = -999.;
                        int good_idx = -1;
                        for (unsigned int didx = 0; didx < cms2.genps_lepdaughter_p4().at(gidx).size(); didx++)
                        {
                            unsigned int did = abs(cms2.genps_lepdaughter_id().at(gidx).at(didx));
                            if (did != 11 && did != 13) continue;
                            if (cms2.genps_lepdaughter_p4().at(gidx).at(didx).pt() > pt)
                            {
                                pt = cms2.genps_lepdaughter_p4().at(gidx).at(didx).pt();
                                good_idx = didx;
                            }
                        }
                        if (good_idx >= 0)
                        {
                            m_evt.gen_lep3_pdgid = cms2.genps_lepdaughter_id().at(gidx).at(good_idx);
                            m_evt.gen_lep3_p4    = cms2.genps_lepdaughter_p4().at(gidx).at(good_idx);
                        }
                    }

                    m_evt.gen_lep3_pdgid = cms2.genps_id().at(gidx);
                    m_evt.gen_lep3_p4    = cms2.genps_p4().at(gidx);
                }
            }

            // gen jets
            m_evt.vgenjets_p4 = efftools::getGenJets(m_jet_pt_cut, 2.4);
            m_evt.gen_ht      = efftools::getGenHT(m_jet_pt_cut, 2.4);
            m_evt.gen_njets   = m_evt.vgenjets_p4.size();
        }
        

        // Event Cleaning
        // --------------------------------------------------------------------------------------------------------- //

        // require at least 3 tracks in the event
        //if (trks_trk_p4().size() < 3)
        //{
        //    if (m_verbose) {std::cout << "fails # trks >= 3 requirement" << std::endl;}
        //    return 0;
        //}

        // require standard cleaning 
        if (!cleaning_standardNovember2011()) 
        {
            if (m_verbose) {std::cout << "fails November2011 cleaning requirement" << std::endl;}
            return 0;
        }

        // Analysis Selections
        // --------------------------------------------------------------------------------------------------------- //

        // jet type
        JetType jet_type = evt_isRealData() ? JETS_TYPE_PF_FAST_CORR_RESIDUAL : JETS_TYPE_PF_FAST_CORR;

        if (m_sync_print)
        {
            cout << "number of dilep pairs: " << hyp_type().size() << endl;
        }

        // loop over hypotheses
        HypInfo best_hyp((hyp_type().empty() ? -1 : 0), DileptonHypType::static_size);
        for (size_t ihyp = 0; ihyp != hyp_type().size(); ihyp++)
        {                
            // leptons variables
            const LorentzVector& lt_p4 = hyp_lt_p4().at(ihyp);
            const LorentzVector& ll_p4 = hyp_ll_p4().at(ihyp);

            const float lt_min_pt = min_lep_pt;
            const float ll_min_pt = min_lep_pt;

            // print for syncing
            // if (m_sync_print)
            // {
            //     cout << "printing for hyp index " << ihyp << endl;
            //     PrintForSync(ihyp, mu_min_pt, el_min_pt, jet_type, m_jetMetScale, m_jet_corrector.get(), m_met_corrector.get());
            // }

            // for now, require OS
            if (hyp_lt_charge().at(ihyp) * hyp_ll_charge().at(ihyp) > 0)
            {
                if (m_verbose) {std::cout << "hyp fails OS requirement" << std::endl;}
                continue;
            }

            // check if hyp passes lepton kinematics
            if (fabs(lt_p4.Eta())>2.4 || lt_p4.pt()<lt_min_pt) 
            {
                if (m_verbose) {std::cout << "lt fails lepton kinematics cut" << std::endl;}
                continue;
            }
            if (fabs(ll_p4.Eta())>2.4 || ll_p4.pt()<ll_min_pt) 
            {
                if (m_verbose) {std::cout << "ll fails lepton kinematics cut" << std::endl;}
                continue;
            }

            // check hyp mass (no low mass resonances)
            float dilep_mass = sqrt(fabs(hyp_p4().at(ihyp).mass2()));
            if (dilep_mass < 8.0) 
            {
                if (m_verbose) {std::cout << "fails dilepton invariant mass requirement" << std::endl;}
                continue;
            }

            // check if hyp passes trigger
            if (evt_isRealData() && !os2012::passesTrigger(hyp_type().at(ihyp), trigger_option))
            {
                if (m_verbose) {std::cout << "fails trigger requirement" << std::endl;}
                continue;
            }            

            // check that leptons are from the same vertex
            if (!hypsFromFirstGoodVertex(ihyp))
            {
                if (m_verbose) {std::cout << "fails leptons are from the first good vertex requirement" << std::endl;}
                continue;
            }

            // get the hyp type
            DileptonHypType::value_type type = hyp_typeToHypType(hyp_type().at(ihyp));

            if (!os2012::isNumeratorHypothesis(ihyp))
            {
                if (m_verbose) {std::cout << "OS hyp doesn't pass ID/ISO requirement" << std::endl;}
                continue; 
            }

            best_hyp = std::min(best_hyp, HypInfo(ihyp, type));

        } // end looper over hypothesis
        
        if (m_verbose) {std::cout << "end of hypothesis loop" << std::endl;}

        // Set Tree Variables
        // --------------------------------------------------------------------------------------------------------- //

        // best hyp index
        int hyp_idx = best_hyp.idx;

        // all: 0, mm: 1, em: 2, ee: 3
        const DileptonHypType::value_type dilepton_type = ((hyp_idx < 0 or hyp_p4().empty()) ? DileptonHypType::static_size : hyp_typeToHypType(hyp_type().at(hyp_idx)));

        // write events to the tree for book keeping
        if (hyp_idx < 0 or hyp_p4().empty())
        {
            if (m_verbose) {std::cout << "fails good event type requirement" << std::endl;}

            // fill event level info 
            m_evt.dilep_type = DileptonHypType::static_size;
            m_evt.event_info.FillCommon(m_sample, filename);

            // fill the dilepton analysis independent variables 
            if (not hyp_p4().empty())
            {
                m_evt.FillCommon(hyp_idx);

                // ttbar breakdown: ttdil = 0, ttotr = 1, ttslb = 2, ttslo = 3, not set = 4
                m_evt.ttbar_bkdn = GetTTbarBreakDown(m_sample, m_evt.lep1.is_fromw, m_evt.lep2.is_fromw); 
            }

            // set the selection bit mask
            m_evt.SetBitMask();

            // fill the tree with what we have
            m_tree->Fill();

            // go to the next event
            return 0;
        }
        else
        {
            if (m_verbose) {std::cout << "passes good dilepton type requirement: " << at::GetDileptonHypTypeName(dilepton_type) << std::endl;}
            if (m_verbose) {std::cout << "good hyp index is : " << hyp_idx << std::endl;}
        }

        // convenience trigger info
        switch(m_analysis_type)
        {
            case AnalysisType::mmbb:
                m_evt.trig_mm = passUnprescaledHLTTriggerPattern("HLT_Mu17_Mu8_v");
                m_evt.trig_em = passUnprescaledHLTTriggerPattern("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v") || 
                                passUnprescaledHLTTriggerPattern("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
                m_evt.trig_ee = passUnprescaledHLTTriggerPattern("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
                break;
            default: {/*do nothing*/}
        }

        // individual triggers: mm
        m_evt.trig_mm_mu17_mu8        = passUnprescaledHLTTriggerPattern("HLT_Mu17_Mu8_v");

        // individual triggers: ee
        m_evt.trig_ee_el17_el8_id_iso = passUnprescaledHLTTriggerPattern("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");

        // individual triggers: em
        m_evt.trig_em_mu17_el8_id_iso = passUnprescaledHLTTriggerPattern("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
        m_evt.trig_em_mu8_el17_id_iso = passUnprescaledHLTTriggerPattern("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");

        // event wieghts 
        //float vtxw  = evt_isRealData() ? 1.0 : vtxweight_n(numberOfGoodVertices(), evt_isRealData(), false);
        float vtxw  = 1.0;
        float xsec  = evt_isRealData() ? 1.0 : evt_scale1fb();
        float scale = evt_isRealData() ? 1.0 : m_lumi * xsec * vtxw; 

        // fill event level info 
        m_evt.event_info.FillCommon(m_sample, filename);

        // fill the dilepton analysis independent variables 
        m_evt.FillCommon(hyp_idx);

        // ttbar breakdown: ttdil = 0, ttotr = 1, ttslb = 2, ttslo = 3, not set = 4
        m_evt.ttbar_bkdn = GetTTbarBreakDown(m_sample, m_evt.lep1.is_fromw, m_evt.lep2.is_fromw); 

        // fill analysis specific branches 
        m_evt.vtxw = vtxw;

        // event level info
        if (not m_jet_corrector)
        {
            m_evt.event_info.pfmet          = evt_pfmet_type1cor();  // do we ever use the uncorrected pfmet?
            m_evt.event_info.pfmet_phi      = evt_pfmetPhi_type1cor();
        }
        else
        {
            std::pair<float, float> pcor_met = m_met_corrector->getCorrectedMET();
            m_evt.event_info.pfmet = pcor_met.first;
            m_evt.event_info.pfmet_phi = pcor_met.second;
        }
        m_evt.event_info.uncorpfmet     = evt_pfmet();
        m_evt.event_info.uncorpfmet_phi = evt_pfmetPhi();
        const float met                 = m_evt.event_info.pfmet;
        const float met_phi             = m_evt.event_info.pfmet_phi;

        //
        // to calculate MT2, need mass of invisible particle
        //
        m_evt.mt2 = MT2(met_phi, met, m_evt.lep1.p4, m_evt.lep2.p4);
        
        if (not m_jet_corrector)
        {
            m_evt.ht            = os2012::sumJetPt    (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, /*systFlag=*/0);
            m_evt.njets         = os2012::nJets       (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, /*systFlag=*/0);
            m_evt.nbtags_loose  = os2012::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVL, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, /*systFlag=*/0);
            m_evt.nbtags_medium = os2012::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, /*systFlag=*/0);
            m_evt.nbtags_tight  = os2012::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVT, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, /*systFlag=*/0);
        }
        else
        {
            FactorizedJetCorrector* const jc = m_jet_corrector.get();
            m_evt.ht            = os2012::sumJetPt    (hyp_idx, jc, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, /*systFlag=*/0);
            m_evt.njets         = os2012::nJets       (hyp_idx, jc, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, /*systFlag=*/0);
            m_evt.nbtags_loose  = os2012::nBtaggedJets(hyp_idx, jc, jet_type, JETS_BTAG_CSVL, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, /*systFlag=*/0);
            m_evt.nbtags_medium = os2012::nBtaggedJets(hyp_idx, jc, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, /*systFlag=*/0);
            m_evt.nbtags_tight  = os2012::nBtaggedJets(hyp_idx, jc, jet_type, JETS_BTAG_CSVT, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, /*systFlag=*/0);
        }

        m_evt.hyp_good_vtx = hypsFromFirstGoodVertex(hyp_idx);
        m_evt.clean        = cleaning_standardNovember2011(); 
        m_evt.presel       = (m_evt.clean && m_evt.hyp_good_vtx);

        // set lepton info (lep1 is higher pT lepton, lep2 is lower pT lepton)
        float lt_pt = hyp_lt_p4().at(hyp_idx).pt();
        float ll_pt = hyp_ll_p4().at(hyp_idx).pt();

        int lep1_id;
        int lep1_idx;
        int lep2_id;
        int lep2_idx;
        if (lt_pt > ll_pt)
        {
            lep1_id  = cms2.hyp_lt_id().at(hyp_idx);
            lep1_idx = cms2.hyp_lt_index().at(hyp_idx); 
            lep2_id  = cms2.hyp_ll_id().at(hyp_idx);    
            lep2_idx = cms2.hyp_ll_index().at(hyp_idx); 
        }
        else
        {
            lep1_id  = cms2.hyp_ll_id().at(hyp_idx);
            lep1_idx = cms2.hyp_ll_index().at(hyp_idx); 
            lep2_id  = cms2.hyp_lt_id().at(hyp_idx);    
            lep2_idx = cms2.hyp_lt_index().at(hyp_idx); 
        }
        bool lep1_is_mu = (abs(lep1_id)==13);
        bool lep1_is_el = (abs(lep1_id)==11);
        bool lep2_is_mu = (abs(lep2_id)==13);
        bool lep2_is_el = (abs(lep2_id)==11);

        m_evt.lep1.cordetiso   = m_evt.lep1.detiso   - (log(m_evt.lep1.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep1.p4.pt()); // check that I have the correct formula 
        m_evt.lep1.cordetiso04 = m_evt.lep1.detiso04 - (log(m_evt.lep1.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep1.p4.pt()); // check that I have the correct formula 
        m_evt.lep1.corpfiso    = os2012::leptonIsolation(lep1_id, lep1_idx);
        m_evt.lep1.corpfiso04  = (lep1_is_el) ? os2012::electronIsolationPF2012_cone04(lep1_idx) : -999999.0;  
        m_evt.lep1.effarea     = os2012::EffectiveArea03(lep1_id, lep1_idx); 
        m_evt.lep1.effarea04   = os2012::EffectiveArea04(lep1_id, lep1_idx);
        m_evt.lep1.dbeta       = (lep1_is_mu) ? mus_isoR03_pf_PUPt().at(lep1_idx) : -99999.0;
        m_evt.lep1.dbeta04     = (lep1_is_mu) ? mus_isoR04_pf_PUPt().at(lep1_idx) : -99999.0;
        //m_evt.lep1.is_conv     = false; 
        m_evt.lep1.mt          = rt::Mt(m_evt.lep1.p4, met, met_phi);
        m_evt.lep1.passes_id   = os2012::isGoodLepton(lep1_id, lep1_idx);
        m_evt.lep1.passes_iso  = os2012::isIsolatedLepton(lep1_id, lep1_idx);

        m_evt.lep2.cordetiso   = m_evt.lep2.detiso   - (log(m_evt.lep2.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep2.p4.pt()); // check that I have the correct formula 
        m_evt.lep2.cordetiso04 = m_evt.lep2.detiso04 - (log(m_evt.lep2.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep2.p4.pt()); // check that I have the correct formula 
        m_evt.lep2.corpfiso    = os2012::leptonIsolation(lep2_id, lep2_idx);
        m_evt.lep2.corpfiso04  = (lep2_is_el) ? os2012::electronIsolationPF2012_cone04(lep2_idx) : -999999.0;  
        m_evt.lep2.effarea     = os2012::EffectiveArea03(lep2_id, lep2_idx);
        m_evt.lep2.effarea04   = os2012::EffectiveArea04(lep2_id, lep2_idx);
        m_evt.lep2.dbeta       = (lep2_is_mu) ? mus_isoR03_pf_PUPt().at(lep2_idx) : -99999.0;
        m_evt.lep2.dbeta04     = (lep2_is_mu) ? mus_isoR04_pf_PUPt().at(lep2_idx) : -99999.0;
        //m_evt.lep2.is_conv     = false; 
        m_evt.lep2.mt          = rt::Mt(m_evt.lep2.p4, met, met_phi);
        m_evt.lep2.passes_id   = os2012::isGoodLepton(lep2_id, lep2_idx);
        m_evt.lep2.passes_iso  = os2012::isIsolatedLepton(lep2_id, lep2_idx);

        // njets, nbtags, HT and MET for JES systematics
        if (!evt_isRealData()) 
        {
            if (not m_jet_corrector || not m_met_corrector)
            {
                if (not m_jet_corr_unc)
                {
                    m_evt.ht_up     = os2012::sumJetPt    (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, /*jetMetScale*/1);
                    m_evt.njets_up  = os2012::nJets       (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, /*jetMetScale*/1);
                    m_evt.nbtags_up = os2012::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, /*jetMetScale*/1);

                    m_evt.ht_dn     = os2012::sumJetPt    (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, /*jetMetScale*/-1);
                    m_evt.njets_dn  = os2012::nJets       (hyp_idx, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, /*jetMetScale*/-1);
                    m_evt.nbtags_dn = os2012::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, /*jetMetScale*/-1);
                }
                else
                {
                    JetCorrectionUncertainty* jcu = m_jet_corr_unc.get();
                    enum JetScaleType scale_up = JETS_SCALE_UP;
                    enum JetScaleType scale_dn = JETS_SCALE_DOWN;

                    m_evt.ht_up     = os2012::sumJetPt    (hyp_idx, jcu, scale_up, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt);
                    m_evt.njets_up  = os2012::nJets       (hyp_idx, jcu, scale_up, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt);
                    m_evt.nbtags_up = os2012::nBtaggedJets(hyp_idx, jcu, scale_up, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt);

                    m_evt.ht_dn     = os2012::sumJetPt    (hyp_idx, jcu, scale_dn, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt);
                    m_evt.njets_dn  = os2012::nJets       (hyp_idx, jcu, scale_dn, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt);
                    m_evt.nbtags_dn = os2012::nBtaggedJets(hyp_idx, jcu, scale_dn, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt);
                }

                ROOT::Math::XYVector cmet_up;
                ROOT::Math::XYVector cmet_dn;
                float metx_up = evt_pfmet_type1cor() * cos(evt_pfmetPhi_type1cor());
                float metx_dn = evt_pfmet_type1cor() * cos(evt_pfmetPhi_type1cor());
                float mety_up = evt_pfmet_type1cor() * sin(evt_pfmetPhi_type1cor());
                float mety_dn = evt_pfmet_type1cor() * sin(evt_pfmetPhi_type1cor());
                // get uncorrected jets
                vector<LorentzVector> ujets = os2012::getJets(hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/10.0, /*|eta|<*/5.0, min_lep_pt, /*systFlag=*/0);
                for (size_t u = 0; u != ujets.size(); u++) 
                {
                    float px   = ujets.at(u).px();
                    float py   = ujets.at(u).py();
                    float pt   = ujets.at(u).pt();
                    float eta  = ujets.at(u).eta();
                    float corr_up = 0.0;
                    float corr_dn = 0.0;
                    if (m_jet_corr_unc)
                    {
                        m_jet_corr_unc->setJetPt(pt);	 
                        m_jet_corr_unc->setJetEta(eta);	 
                        float jet_cor = m_jet_corr_unc->getUncertainty(true);	 
                        corr_up = (1. + jet_cor);
                        corr_dn = (1. - jet_cor);
                    }
                    else
                    {
                        corr_up = getJetMetSyst(/*jetMetScale=*/ 1, pt, eta);
                        corr_dn = getJetMetSyst(/*jetMetScale=*/-1, pt, eta);
                    }
                    metx_up = metx_up - (corr_up-1.0)*px;
                    mety_up = mety_up - (corr_up-1.0)*py;
                    metx_dn = metx_dn - (corr_dn-1.0)*px;
                    mety_dn = mety_dn - (corr_dn-1.0)*py;
                }
                cmet_up.SetXY(metx_up, mety_up);
                cmet_dn.SetXY(metx_dn, mety_dn);
                m_evt.pfmet_up     = cmet_up.r(); 
                m_evt.pfmet_phi_up = cmet_up.phi();
                m_evt.pfmet_dn     = cmet_dn.r(); 
                m_evt.pfmet_phi_dn = cmet_dn.phi();
            }
            else
            {
                if (not m_jet_corr_unc)
                {
                    m_evt.ht_up       = os2012::sumJetPt    (hyp_idx, m_jet_corrector.get(), jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, /*jetMetScale*/1);
                    m_evt.njets_up    = os2012::nJets       (hyp_idx, m_jet_corrector.get(), jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, /*jetMetScale*/1);
                    m_evt.nbtags_up   = os2012::nBtaggedJets(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, /*jetMetScale*/1);

                    m_evt.ht_dn       = os2012::sumJetPt    (hyp_idx, m_jet_corrector.get(), jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, /*jetMetScale*/-1);
                    m_evt.njets_dn    = os2012::nJets       (hyp_idx, m_jet_corrector.get(), jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, /*jetMetScale*/-1);
                    m_evt.nbtags_dn   = os2012::nBtaggedJets(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, /*jetMetScale*/-1);
                }
                else
                {
                    FactorizedJetCorrector* jc    = m_jet_corrector.get();
                    JetCorrectionUncertainty* jcu = m_jet_corr_unc.get();
                    enum JetScaleType scale_up = JETS_SCALE_UP;
                    enum JetScaleType scale_dn = JETS_SCALE_DOWN;

                    m_evt.ht_up       = os2012::sumJetPt    (hyp_idx, jc, jcu, scale_up, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt);
                    m_evt.njets_up    = os2012::nJets       (hyp_idx, jc, jcu, scale_up, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt);
                    m_evt.nbtags_up   = os2012::nBtaggedJets(hyp_idx, jc, jcu, scale_up, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt);

                    m_evt.ht_dn       = os2012::sumJetPt    (hyp_idx, jc, jcu, scale_dn, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt);
                    m_evt.njets_dn    = os2012::nJets       (hyp_idx, jc, jcu, scale_dn, jet_type,                 /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt);
                    m_evt.nbtags_dn   = os2012::nBtaggedJets(hyp_idx, jc, jcu, scale_dn, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt);
                }

                // MET
                ROOT::Math::XYVector cmet_up;
                ROOT::Math::XYVector cmet_dn;
                float metx_up = met * cos(met_phi);
                float metx_dn = met * cos(met_phi);
                float mety_up = met * sin(met_phi);
                float mety_dn = met * sin(met_phi);
                // get uncorrected jets
                vector<LorentzVector> ujets = os2012::getJets(hyp_idx, m_jet_corrector.get(), jet_type, /*dR=*/0.4, /*jet_pt>*/10.0, /*|eta|<*/5.0, min_lep_pt, /*systFlag=*/0);
                for (size_t u = 0; u != ujets.size(); u++) 
                {
                    float px   = ujets.at(u).px();
                    float py   = ujets.at(u).py();
                    float pt   = ujets.at(u).pt();
                    float eta  = ujets.at(u).eta();
                    float corr_up = 0.0;
                    float corr_dn = 0.0;
                    if (m_jet_corr_unc)
                    {
                        m_jet_corr_unc->setJetPt(pt);	 
                        m_jet_corr_unc->setJetEta(eta);	 
                        float jet_cor = m_jet_corr_unc->getUncertainty(true);	 
                        corr_up = (1. + jet_cor);
                        corr_dn = (1. - jet_cor);
                    }
                    else
                    {
                        corr_up = getJetMetSyst(/*jetMetScale=*/ 1, pt, eta);
                        corr_dn = getJetMetSyst(/*jetMetScale=*/-1, pt, eta);
                    }
                    metx_up = metx_up - (corr_up-1.0)*px;
                    mety_up = mety_up - (corr_up-1.0)*py;
                    metx_dn = metx_dn - (corr_dn-1.0)*px;
                    mety_dn = mety_dn - (corr_dn-1.0)*py;
                }
                cmet_up.SetXY(metx_up, mety_up);
                cmet_dn.SetXY(metx_dn, mety_dn);
                m_evt.pfmet_up     = cmet_up.r();
                m_evt.pfmet_phi_up = cmet_up.phi();
                m_evt.pfmet_dn     = cmet_dn.r();
                m_evt.pfmet_phi_dn = cmet_dn.phi();
            }
        }

        // Gen level info
        // NOTE: we fill the gen block if and only if BOTH leptons are matched 
        if (!evt_isRealData())
        {
            // gen Lep p4
            std::pair<GenParticleStruct, GenParticleStruct> gen_hyp = efftools::getGenHyp(/*pt1=*/min_lep_pt, /*pt2=*/min_lep_pt, DileptonChargeType::OS);
            if (gen_hyp.first.idx_!=999999 && gen_hyp.second.idx_!=999999)
            {
                // gen HT
                m_evt.gen_ht = efftools::getGenHT(/*pt_cut=*/m_jet_pt_cut, /*eta_cut=*/2.4);

                // gen dilep hyp
                m_evt.gen_lep1_p4    = (abs(gen_hyp.first.id_) == 15) ? cms2.genps_lepdaughter_p4().at(gen_hyp.first.idx_).at(gen_hyp.first.didx_) : cms2.genps_p4().at(gen_hyp.first.idx_);
                m_evt.gen_lep1_pdgid = (abs(gen_hyp.first.id_) == 15) ? gen_hyp.first.did_ : gen_hyp.first.id_;

                m_evt.gen_lep2_p4    = (abs(gen_hyp.second.id_) == 15) ? cms2.genps_lepdaughter_p4().at(gen_hyp.second.idx_).at(gen_hyp.second.didx_) : cms2.genps_p4().at(gen_hyp.second.idx_);
                m_evt.gen_lep2_pdgid = (abs(gen_hyp.second.id_) == 15) ? gen_hyp.second.did_ : gen_hyp.second.id_;

                m_evt.gen_dilep_p4 = m_evt.gen_lep1_p4 + m_evt.gen_lep2_p4;
                m_evt.gen_dilep_mass = m_evt.gen_dilep_p4.mass();

                if (abs(m_evt.gen_lep1_pdgid*m_evt.gen_lep2_pdgid) == 121)
                    m_evt.gen_dilep_type = at::DileptonHypType::EE;
                else if (abs(m_evt.gen_lep1_pdgid*m_evt.gen_lep2_pdgid) == 169)
                    m_evt.gen_dilep_type = at::DileptonHypType::MUMU;
                else if (abs(m_evt.gen_lep1_pdgid*m_evt.gen_lep2_pdgid) == 143)
                    m_evt.gen_dilep_type = at::DileptonHypType::EMU;

                m_evt.gen_dilep_dphi = rt::DeltaPhi(m_evt.gen_lep1_p4, m_evt.gen_lep2_p4);
                m_evt.gen_dilep_deta = rt::DeltaEta(m_evt.gen_lep1_p4, m_evt.gen_lep2_p4);
                m_evt.gen_dilep_dr   = rt::DeltaR(m_evt.gen_lep1_p4, m_evt.gen_lep2_p4);
            }
        }

        // selected only triggered events
        if (not((m_evt.ee && m_evt.trig_ee) || (m_evt.em && m_evt.trig_em) || (m_evt.mm && m_evt.trig_mm)))
        {
            if (m_verbose) {cout << "fails trigger selection" << endl;}
            //return 0;
        }

        // electron isolation correction variables
        m_evt.rho_iso = evt_kt6pf_foregiso_rho();
        m_evt.rho     = evt_ww_rho_vor(); 

        // eff and scale factors
        if (!evt_isRealData())
        {
            // scale factor for trigger efficiency
            m_evt.sf_dileptrig   = DileptonTriggerScaleFactor(dilepton_type, m_analysis_type, m_evt.lep2.p4);
            m_evt.lep1.sf_trig   = -999999; // not done 
            m_evt.lep2.sf_trig   = -999999; // not done

            // scale factor for lepton reconstruction efficiency
            const float eta1 = (abs(lep1_id) == 13 ? m_evt.lep1.p4.eta() : m_evt.lep1.sc_p4.eta());
            const float eta2 = (abs(lep2_id) == 13 ? m_evt.lep2.p4.eta() : m_evt.lep2.sc_p4.eta());
            m_evt.sf_lepeff      = DileptonTagAndProbeScaleFactor(lep1_id, m_evt.lep1.p4.pt(), eta1, lep2_id, m_evt.lep2.p4.pt(), eta2);
            m_evt.lep1.sf_lepeff = TagAndProbeScaleFactor(lep1_id, m_evt.lep1.p4.pt(), eta1); 
            m_evt.lep2.sf_lepeff = TagAndProbeScaleFactor(lep2_id, m_evt.lep2.p4.pt(), eta2);
        }

        // jet/bjet info 
        vector<bool> jet_flags;
        vector<bool> jet_flags_up;
        vector<bool> jet_flags_dn;
        vector<LorentzVector> bjets;
        vector<bool> bjet_flags;
        vector<bool> bjet_flags_up;
        vector<bool> bjet_flags_dn;
        vector<bool> bjet_flags_loose;
        vector<bool> bjet_flags_loose_up;
        vector<bool> bjet_flags_loose_dn;
        vector<bool> bjet_flags_tight;
        vector<bool> bjet_flags_tight_up;
        vector<bool> bjet_flags_tight_dn;
        vector<LorentzVector> all_jet_p4s;
        vector<LorentzVector> all_jet_p4s_up;
        vector<LorentzVector> all_jet_p4s_dn;
        bool sort_all_jet_pts = false;
        if (not m_jet_corrector)
        {
            all_jet_p4s          = os2012::getJets(hyp_idx, jet_type, /*dR=*/0.0, /*jet_pt>*/-9999., /*|eta|<*/9999., /*min_lep_pt=*/9999., m_jetMetScale, sort_all_jet_pts);
            all_jet_p4s_up       = os2012::getJets(hyp_idx, jet_type, /*dR=*/0.0, /*jet_pt>*/-9999., /*|eta|<*/9999., /*min_lep_pt=*/9999., 1, sort_all_jet_pts);
            all_jet_p4s_dn       = os2012::getJets(hyp_idx, jet_type, /*dR=*/0.0, /*jet_pt>*/-9999., /*|eta|<*/9999., /*min_lep_pt=*/9999., -1, sort_all_jet_pts);

            m_evt.vjets_p4       = os2012::getJets(hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, m_jetMetScale);
            m_evt.vjets_p4_up    = os2012::getJets(hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, 1); 
            m_evt.vjets_p4_dn    = os2012::getJets(hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, -1);

            jet_flags            = os2012::getJetFlags(hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, m_jetMetScale);
            jet_flags_up         = os2012::getJetFlags(hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, 1);
            jet_flags_dn         = os2012::getJetFlags(hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, -1);

            m_evt.vjets_bdisc    = os2012::getJetBtagDiscriminators(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, m_jetMetScale);
            m_evt.vjets_bdisc_up = os2012::getJetBtagDiscriminators(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, 1);
            m_evt.vjets_bdisc_dn = os2012::getJetBtagDiscriminators(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, -1);

            bjets                = os2012::getBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, m_jetMetScale);

            bjet_flags           = os2012::getBtaggedJetFlags(hyp_idx, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, m_jetMetScale);
            bjet_flags_up        = os2012::getBtaggedJetFlags(hyp_idx, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, 1);
            bjet_flags_dn        = os2012::getBtaggedJetFlags(hyp_idx, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, -1);

            bjet_flags_loose     = os2012::getBtaggedJetFlags(hyp_idx, jet_type, JETS_BTAG_CSVL,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, m_jetMetScale);
            bjet_flags_loose_up  = os2012::getBtaggedJetFlags(hyp_idx, jet_type, JETS_BTAG_CSVL,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, 1);
            bjet_flags_loose_dn  = os2012::getBtaggedJetFlags(hyp_idx, jet_type, JETS_BTAG_CSVL,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, -1);

            bjet_flags_tight     = os2012::getBtaggedJetFlags(hyp_idx, jet_type, JETS_BTAG_CSVT,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, m_jetMetScale);
            bjet_flags_tight_up  = os2012::getBtaggedJetFlags(hyp_idx, jet_type, JETS_BTAG_CSVT,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, 1);
            bjet_flags_tight_dn  = os2012::getBtaggedJetFlags(hyp_idx, jet_type, JETS_BTAG_CSVT,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, -1);
        }
        else
        {
            all_jet_p4s          = os2012::getJets(hyp_idx, m_jet_corrector.get(), jet_type, /*dR=*/0.0, /*jet_pt>*/-9999., /*|eta|<*/9999., /*min_lep_pt=*/9999., m_jetMetScale, sort_all_jet_pts);
            all_jet_p4s_up       = os2012::getJets(hyp_idx, m_jet_corrector.get(), jet_type, /*dR=*/0.0, /*jet_pt>*/-9999., /*|eta|<*/9999., /*min_lep_pt=*/9999., 1, sort_all_jet_pts);
            all_jet_p4s_dn       = os2012::getJets(hyp_idx, m_jet_corrector.get(), jet_type, /*dR=*/0.0, /*jet_pt>*/-9999., /*|eta|<*/9999., /*min_lep_pt=*/9999., -1, sort_all_jet_pts);

            m_evt.vjets_p4       = os2012::getJets(hyp_idx, m_jet_corrector.get(), jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, m_jetMetScale);
            m_evt.vjets_p4_up    = os2012::getJets(hyp_idx, m_jet_corrector.get(), jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, 1); 
            m_evt.vjets_p4_dn    = os2012::getJets(hyp_idx, m_jet_corrector.get(), jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, -1);

            jet_flags            = os2012::getJetFlags(hyp_idx, m_jet_corrector.get(), jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, m_jetMetScale);
            jet_flags_up         = os2012::getJetFlags(hyp_idx, m_jet_corrector.get(), jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, 1);
            jet_flags_dn         = os2012::getJetFlags(hyp_idx, m_jet_corrector.get(), jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, -1);

            m_evt.vjets_bdisc    = os2012::getJetBtagDiscriminators(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, m_jetMetScale);
            m_evt.vjets_bdisc_up = os2012::getJetBtagDiscriminators(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, 1);
            m_evt.vjets_bdisc_dn = os2012::getJetBtagDiscriminators(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, -1);

            bjets                = os2012::getBtaggedJets(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, m_jetMetScale);

            bjet_flags           = os2012::getBtaggedJetFlags(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, m_jetMetScale);
            bjet_flags_up        = os2012::getBtaggedJetFlags(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, 1);
            bjet_flags_dn        = os2012::getBtaggedJetFlags(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, -1);

            bjet_flags_loose     = os2012::getBtaggedJetFlags(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVL,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, m_jetMetScale);
            bjet_flags_loose_up  = os2012::getBtaggedJetFlags(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVL,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, 1);
            bjet_flags_loose_dn  = os2012::getBtaggedJetFlags(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVL,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, -1);

            bjet_flags_tight     = os2012::getBtaggedJetFlags(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVT,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, m_jetMetScale);
            bjet_flags_tight_up  = os2012::getBtaggedJetFlags(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVT,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, 1);
            bjet_flags_tight_dn  = os2012::getBtaggedJetFlags(hyp_idx, m_jet_corrector.get(), jet_type, JETS_BTAG_CSVT,/*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, min_lep_pt, -1);
        }

        assert(jet_flags.size() == bjet_flags.size());
        assert(jet_flags_up.size() == bjet_flags_up.size());
        assert(jet_flags_dn.size() == bjet_flags_dn.size());

        assert(m_evt.vjets_bdisc.size() == m_evt.vjets_p4.size());
        assert(m_evt.vjets_bdisc_up.size() == m_evt.vjets_p4_up.size());
        assert(m_evt.vjets_bdisc_dn.size() == m_evt.vjets_p4_dn.size());

        m_evt.vjets_btagged_loose    = sortBtaggedFlags(all_jet_p4s, jet_flags   , bjet_flags_loose   );
        m_evt.vjets_btagged_loose_up = sortBtaggedFlags(all_jet_p4s, jet_flags_up, bjet_flags_loose_up);
        m_evt.vjets_btagged_loose_dn = sortBtaggedFlags(all_jet_p4s, jet_flags_dn, bjet_flags_loose_dn);

        m_evt.vjets_btagged_medium    = sortBtaggedFlags(all_jet_p4s, jet_flags   , bjet_flags   );
        m_evt.vjets_btagged_medium_up = sortBtaggedFlags(all_jet_p4s, jet_flags_up, bjet_flags_up);
        m_evt.vjets_btagged_medium_dn = sortBtaggedFlags(all_jet_p4s, jet_flags_dn, bjet_flags_dn);

        m_evt.vjets_btagged_tight    = sortBtaggedFlags(all_jet_p4s, jet_flags   , bjet_flags_tight   );
        m_evt.vjets_btagged_tight_up = sortBtaggedFlags(all_jet_p4s, jet_flags_up, bjet_flags_tight_up);
        m_evt.vjets_btagged_tight_dn = sortBtaggedFlags(all_jet_p4s, jet_flags_dn, bjet_flags_tight_dn);

        assert(m_evt.vjets_p4.size()    == m_evt.vjets_btagged_loose.size());
        assert(m_evt.vjets_p4_up.size() == m_evt.vjets_btagged_loose_up.size());
        assert(m_evt.vjets_p4_dn.size() == m_evt.vjets_btagged_loose_dn.size());

        assert(m_evt.vjets_p4.size()    == m_evt.vjets_btagged_medium.size());
        assert(m_evt.vjets_p4_up.size() == m_evt.vjets_btagged_medium_up.size());
        assert(m_evt.vjets_p4_dn.size() == m_evt.vjets_btagged_medium_dn.size());

        assert(m_evt.vjets_p4.size()    == m_evt.vjets_btagged_tight.size());
        assert(m_evt.vjets_p4_up.size() == m_evt.vjets_btagged_tight_up.size());
        assert(m_evt.vjets_p4_dn.size() == m_evt.vjets_btagged_tight_dn.size());

        // jet btag flag and mc flavor matching
        const CMS2Tag cms2_tag = at::GetCMS2Tag();
        if (cms2_tag.version > 21 && not evt_isRealData())
        {
            m_evt.vjets_mcflavor_phys = getJetMcPhysMatch(hyp_idx, /*systFlag=*/0, /*sort_by_pt=*/true);
            m_evt.vjets_mcflavor_algo = getJetMcAlgoMatch(hyp_idx, /*systFlag=*/0, /*sort_by_pt=*/true);

            m_evt.vjets_mcflavor_phys_up = getJetMcPhysMatch(hyp_idx, /*systFlag=*/1, /*sort_by_pt=*/true);
            m_evt.vjets_mcflavor_algo_up = getJetMcAlgoMatch(hyp_idx, /*systFlag=*/1, /*sort_by_pt=*/true);

            m_evt.vjets_mcflavor_phys_dn = getJetMcPhysMatch(hyp_idx, /*systFlag=*/-1, /*sort_by_pt=*/true);
            m_evt.vjets_mcflavor_algo_dn = getJetMcAlgoMatch(hyp_idx, /*systFlag=*/-1, /*sort_by_pt=*/true);
        }

        assert(m_evt.vjets_mcflavor_algo.size()    == m_evt.vjets_p4.size());
        assert(m_evt.vjets_mcflavor_algo_up.size() == m_evt.vjets_p4_up.size());
        assert(m_evt.vjets_mcflavor_algo_dn.size() == m_evt.vjets_p4_dn.size());

        // set the seed
        const unsigned int seed = evt_event();

        // calculate the "reweighted" MC btag yields
        if (not evt_isRealData() && (cms2_tag.version > 21))
        {
            // # btags reweighted
            m_evt.nbtags_reweighted    = at::MCBtagCount(m_evt.vjets_p4, m_evt.vjets_btagged_medium, m_evt.vjets_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            m_evt.nbtags_reweighted_up = at::MCBtagCount(m_evt.vjets_p4, m_evt.vjets_btagged_medium, m_evt.vjets_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::up  , seed);
            m_evt.nbtags_reweighted_dn = at::MCBtagCount(m_evt.vjets_p4, m_evt.vjets_btagged_medium, m_evt.vjets_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::down, seed);

            // # btags reweighted and JES +/-
            m_evt.nbtags_reweighted_jec_up = at::MCBtagCount(m_evt.vjets_p4_up, m_evt.vjets_btagged_medium_up, m_evt.vjets_mcflavor_algo_up, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            m_evt.nbtags_reweighted_jec_dn = at::MCBtagCount(m_evt.vjets_p4_dn, m_evt.vjets_btagged_medium_dn, m_evt.vjets_mcflavor_algo_dn, m_sample, m_is_fast_sim, at::YieldType::base, seed);
        }

        // scale the JER 
        if (not evt_isRealData() && (cms2_tag.version > 21))
        {
            // set initial values
            m_evt.ht_jer        = m_evt.ht;
            m_evt.pfmet_jer     = met;
            m_evt.pfmet_jer_phi = met_phi;
            vector<LorentzVector> vjets_jer_p4  = m_evt.vjets_p4;
            vector<LorentzVector> tmp_vbjets_p4;
            for (unsigned int ib = 0; ib < m_evt.vjets_p4.size(); ib++)
            {
                if (m_evt.vjets_btagged_medium.at(ib)) tmp_vbjets_p4.push_back(m_evt.vjets_p4.at(ib));
            }
            vector<LorentzVector> vbjets_jer_p4 = tmp_vbjets_p4;

            // update the values by scaling the JER
            os2012::smearJETScaleJetsMetHt(vjets_jer_p4, m_evt.pfmet_jer, m_evt.pfmet_jer_phi, m_evt.ht_jer, hyp_idx, jet_type, seed, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, /*min_lep_pt>*/min_lep_pt);
            vector<LorentzVector> vbjets_reweighted_jer_p4 = at::RecountedBjets(m_evt.vjets_p4, m_evt.vjets_btagged_medium, m_evt.vjets_mcflavor_algo, m_sample, m_is_fast_sim, at::YieldType::base, seed);
            os2012::smearJETScaleJets(vbjets_jer_p4, seed);
            os2012::smearJETScaleJets(vbjets_reweighted_jer_p4, seed);

            // set the branches 
            m_evt.njets_jer             = vjets_jer_p4.size();
            m_evt.nbtags_jer            = vbjets_jer_p4.size();
            m_evt.nbtags_reweighted_jer = vbjets_reweighted_jer_p4.size();
        }

        // scale the unclustered MET
        m_evt.pfmet_uncl_up = os2012::scaleMET(met, met_phi, hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/10, /*|eta|<*/2.5, /*min_lep_pt>*/min_lep_pt, /*scale_type=*/1 , /*scale=*/0.1);
        m_evt.pfmet_uncl_dn = os2012::scaleMET(met, met_phi, hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/10, /*|eta|<*/2.5, /*min_lep_pt>*/min_lep_pt, /*scale_type=*/-1, /*scale=*/0.1);
        
        vector<LorentzVector> temp_jets_p4 = m_evt.vjets_p4;

        // get the untagged jets
        vector<LorentzVector> temp_jets_tagged_p4;
        for (size_t i = 0; i != temp_jets_p4.size(); i++)
        {
            if (!m_evt.vjets_btagged_medium.at(i)) continue;
            temp_jets_tagged_p4.push_back(temp_jets_p4.at(i));
        }

        if (!temp_jets_tagged_p4.empty())
        {            
            // nearest to lep1
            std::sort(temp_jets_tagged_p4.begin(), temp_jets_tagged_p4.end(), SortByDeltaR<LorentzVector>(m_evt.lep1.p4));
            m_evt.lep1_nearb_p4 = temp_jets_tagged_p4.front();
            m_evt.lep1_nearb_dr = rt::DeltaR(m_evt.lep1.p4, temp_jets_tagged_p4.front());

            // nearest to lep2
            std::sort(temp_jets_tagged_p4.begin(), temp_jets_tagged_p4.end(), SortByDeltaR<LorentzVector>(m_evt.lep2.p4));
            m_evt.lep2_nearb_p4 = temp_jets_tagged_p4.front();
            m_evt.lep2_nearb_dr = rt::DeltaR(m_evt.lep2.p4, temp_jets_tagged_p4.front());
        }

        if (abs(m_evt.lep1.pdgid) == 11) {
            std::pair<int,double> closest_el = std::make_pair(-1, 99.);
            for (unsigned int eidx = 0; eidx < cms2.els_p4().size(); eidx++) {
                
                if (cms2.els_p4().at(eidx).pt() < 5.) continue;
                if (fabs(cms2.els_p4().at(eidx).eta()) > 2.5) continue;
                if (m_evt.lep1.charge * cms2.els_charge().at(eidx) > 0) continue;

                double iso_val = os2012::electronIsolationPF2012(eidx);
                if (iso_val > 0.2) continue;

                using namespace wp2012;
                electronIdComponent_t passAllVetoCuts = DETAIN | DPHIIN | SIGMAIETAIETA | HOE | D0VTX | DZVTX;
                electronIdComponent_t vetoid = electronId_WP2012(eidx, VETO);
                if ((passAllVetoCuts & vetoid) != passAllVetoCuts)
                    continue;

                double dr = rt::DeltaR(cms2.els_p4().at(eidx), m_evt.lep1.p4);
                if (dr < closest_el.second)
                    closest_el = std::make_pair(eidx, dr);
            }

            if (closest_el.first >= 0) {
                m_evt.lep1_nearlep_p4 = cms2.els_p4().at(closest_el.first);
                m_evt.lep1_nearlep_id = -11 * cms2.els_charge().at(closest_el.first);
                m_evt.lep1_nearlep_dr = closest_el.second;
            }                
        }

        if (abs(m_evt.lep2.pdgid) == 11) {
            std::pair<int,double> closest_el = std::make_pair(-1, 99.);
            for (unsigned int eidx = 0; eidx < cms2.els_p4().size(); eidx++) {
                
                if (cms2.els_p4().at(eidx).pt() < 5.) continue;
                if (fabs(cms2.els_p4().at(eidx).eta()) > 2.5) continue;
                if (m_evt.lep2.charge * cms2.els_charge().at(eidx) > 0) continue;

                double iso_val = os2012::electronIsolationPF2012(eidx);
                if (iso_val > 0.2) continue;

                using namespace wp2012;
                electronIdComponent_t passAllVetoCuts = DETAIN | DPHIIN | SIGMAIETAIETA | HOE | D0VTX | DZVTX;
                electronIdComponent_t vetoid = electronId_WP2012(eidx, VETO);
                if ((passAllVetoCuts & vetoid) != passAllVetoCuts)
                    continue;

                double dr = rt::DeltaR(cms2.els_p4().at(eidx), m_evt.lep2.p4);
                if (dr < closest_el.second)
                    closest_el = std::make_pair(eidx, dr);
            }

            if (closest_el.first >= 0) {
                m_evt.lep2_nearlep_p4 = cms2.els_p4().at(closest_el.first);
                m_evt.lep2_nearlep_id = -11 * cms2.els_charge().at(closest_el.first);
                m_evt.lep2_nearlep_dr = closest_el.second;
            }                
        }

        if (abs(m_evt.lep1.pdgid) == 13) {
            std::pair<int,double> closest_mu = std::make_pair(-1, 99.);
            for (unsigned int midx = 0; midx < cms2.mus_p4().size(); midx++) {
                
                if (cms2.mus_p4().at(midx).pt() < 5.) continue;
                if (fabs(cms2.mus_p4().at(midx).eta()) > 2.5) continue;
                if (m_evt.lep1.charge * cms2.mus_charge().at(midx) > 0) continue;

                double iso_val = muonIsoValuePF2012_deltaBeta(midx);
                if (iso_val > 0.2) continue;

                if (!passes_muid_wp2012(midx, mu2012_tightness::LOOSE))
                    continue;

                double dr = rt::DeltaR(cms2.mus_p4().at(midx), m_evt.lep1.p4);
                if (dr < closest_mu.second)
                    closest_mu = std::make_pair(midx, dr);
            }

            if (closest_mu.first >= 0) {
                m_evt.lep1_nearlep_p4 = cms2.mus_p4().at(closest_mu.first);
                m_evt.lep1_nearlep_id = -13 * cms2.mus_charge().at(closest_mu.first);
                m_evt.lep1_nearlep_dr = closest_mu.second;
            }                
        }

        if (abs(m_evt.lep2.pdgid) == 13) {
            std::pair<int,double> closest_mu = std::make_pair(-1, 99.);
            for (unsigned int midx = 0; midx < cms2.mus_p4().size(); midx++) {
                
                if (cms2.mus_p4().at(midx).pt() < 5.) continue;
                if (fabs(cms2.mus_p4().at(midx).eta()) > 2.5) continue;
                if (m_evt.lep2.charge * cms2.mus_charge().at(midx) > 0) continue;

                double iso_val = muonIsoValuePF2012_deltaBeta(midx);
                if (iso_val > 0.2) continue;

                if (!passes_muid_wp2012(midx, mu2012_tightness::LOOSE))
                    continue;

                double dr = rt::DeltaR(cms2.mus_p4().at(midx), m_evt.lep2.p4);
                if (dr < closest_mu.second)
                    closest_mu = std::make_pair(midx, dr);
            }

            if (closest_mu.first >= 0) {
                m_evt.lep2_nearlep_p4 = cms2.mus_p4().at(closest_mu.first);
                m_evt.lep2_nearlep_id = -13 * cms2.mus_charge().at(closest_mu.first);
                m_evt.lep2_nearlep_dr = closest_mu.second;
            }                
        }

        // match njets/btags to MC truth
        if (not tas::evt_isRealData())
        {
            // jets
            for (size_t i = 0; i != m_evt.vjets_p4.size(); i++)
            {
                const LorentzVector jet_p4 = m_evt.vjets_p4.at(i);
                int idx = efftools::getGenParton(jet_p4, /*use status3 =*/true);
                int mc3id = idx>= 0 ? tas::genps_id().at(idx) : -999999;
                int momid = idx>= 0 ? tas::genps_id_mother().at(idx) : -999999;
                LorentzVector mc3p4 = idx>= 0 ? tas::genps_p4().at(idx) : LorentzVector(0,0,0,0);
                m_evt.vjets_mc3id.push_back(mc3id);
                m_evt.vjets_momid.push_back(momid);
                m_evt.vjets_mc3p4.push_back(mc3p4);
            }
        }

        //
        // jet-PV matching
        //
        for (size_t pfjidx = 0; pfjidx < jet_flags.size(); pfjidx++)
        {
            if (jet_flags.at(pfjidx) == 0) continue;
            m_evt.pfjets_beta     .push_back ( pfjet_beta( pfjidx, 1)       );
            m_evt.pfjets_beta2    .push_back ( pfjet_beta( pfjidx, 2)       );
            m_evt.pfjets_beta_0p1 .push_back ( pfjet_beta( pfjidx, 1, 0.1 ) );
            m_evt.pfjets_beta_0p2 .push_back ( pfjet_beta( pfjidx, 1, 0.2 ) );
            m_evt.pfjets_beta2_0p1.push_back ( pfjet_beta( pfjidx, 2, 0.1 ) );
            m_evt.pfjets_beta2_0p5.push_back ( pfjet_beta( pfjidx, 2, 0.5 ) );

            m_evt.pfjets_mvaPUid.push_back  ( cms2.pfjets_full53xmvavalue().at(pfjidx));
            m_evt.pfjets_mva5xPUid.push_back( cms2.pfjets_full5xmvavalue() .at(pfjidx));
            m_evt.pfjets_mvaBeta.push_back  ( cms2.pfjets_full53xmva_beta().at(pfjidx));
        }

        // assert(m_evt.vjets_p4.size() == m_evt.pfjets_mva5xPUid.size());
        
        //
        // store info for third lepton (choose highest pt, separated from hyp leptons by dR=0.1)
        //
        int lep3idx = -1;
        int lep3id  = 0;
        float lep3pt = -999999.;
        for (unsigned int el3idx = 0; el3idx < cms2.els_p4().size(); el3idx++)
        {
            if (cms2.els_p4().at(el3idx).pt() < 5.) continue;
            if (rt::DeltaR(cms2.els_p4().at(el3idx),m_evt.lep1.p4) < 0.1) continue;
            if (rt::DeltaR(cms2.els_p4().at(el3idx),m_evt.lep2.p4) < 0.1) continue;
            if (cms2.els_p4().at(el3idx).pt() > lep3pt)
            {
                lep3idx = el3idx;
                lep3id  = -11 * cms2.els_charge().at(el3idx);
                lep3pt  = cms2.els_p4().at(el3idx).pt();
            }
        }

        for (unsigned int mu3idx = 0; mu3idx < cms2.mus_p4().size(); mu3idx++)
        {
            if (cms2.mus_p4().at(mu3idx).pt() < 5.) continue;
            if (rt::DeltaR(cms2.mus_p4().at(mu3idx),m_evt.lep1.p4) < 0.1) continue;
            if (rt::DeltaR(cms2.mus_p4().at(mu3idx),m_evt.lep2.p4) < 0.1) continue;
            if (cms2.mus_p4().at(mu3idx).pt() > lep3pt)
            {
                lep3idx = mu3idx;
                lep3id  = -13 * cms2.mus_charge().at(mu3idx);
                lep3pt  = cms2.mus_p4().at(mu3idx).pt();
            }
        }

        m_evt.lep3.FillCommon(lep3id, lep3idx);

        //
        // add branches for convenience
        //
        int njets_pv_tmp0 = 0;
        int njets_pv_tmp1 = 0;
        int njets_pv_tmp2 = 0;
        for (unsigned int jetpvidx = 0; jetpvidx < m_evt.vjets_p4.size(); jetpvidx++)
        {
            if (passesMVAJetId(m_evt.vjets_p4.at(jetpvidx), m_evt.pfjets_mva5xPUid.at(jetpvidx), 0)) ++njets_pv_tmp0;
            if (passesMVAJetId(m_evt.vjets_p4.at(jetpvidx), m_evt.pfjets_mva5xPUid.at(jetpvidx), 1)) ++njets_pv_tmp1;
            if (passesMVAJetId(m_evt.vjets_p4.at(jetpvidx), m_evt.pfjets_mva5xPUid.at(jetpvidx), 2)) ++njets_pv_tmp2;
        }

        m_evt.njets_pv_tight0 = njets_pv_tmp0;
        m_evt.njets_pv_tight1 = njets_pv_tmp1;
        m_evt.njets_pv_tight2 = njets_pv_tmp2;        

        // Fill the tree
        m_tree->Fill();

        // printout
        if (m_evt.is_good_lumi && m_evt.njets >= 2)
        {
            scale = 1.0;
            if (dilepton_type==DileptonHypType::MUMU)
            {
                if (m_verbose) {cout << "type == mm" << endl;}
                m_count_nobtag_os[0] += scale;
                if (m_evt.nbtags_medium > 1) m_count_os[0] += scale;
            }
            if (dilepton_type==DileptonHypType::EMU)
            {
                if (m_verbose) {cout << "type == em" << endl;}
                m_count_nobtag_os[1] += scale;
                if (m_evt.nbtags_medium > 1) m_count_os[1] += scale;
            }
            if (dilepton_type==DileptonHypType::EE)
            {
                if (m_verbose) {cout << "type == ee" << endl;}
                m_count_nobtag_os[2] += scale;
                if (m_evt.nbtags_medium > 1) m_count_os[2] += scale;
            }
            // count all 
            {
                m_count_nobtag_os[3] += scale;
                if (m_evt.nbtags_medium > 1) m_count_os[3] += scale;
            }
        }
    }
    catch (std::exception& e)
    {
        cout << Form("Fatal error on run %d, ls %d, event %d", evt_run(), evt_lumiBlock(), evt_event()) << endl;
        cout << e.what() << endl;
        cout << "Exiting..." << endl;
        exit(1);
    }

    // done
    return 0;
}

bool RpvStopOSAnalysisLooper::passesMVAJetId(LorentzVector p4, float mva_value, int tightness)
{
    if (tightness < 0 || tightness > 2)
    {
        std::cout << "ERROR : tightness should be 0, 1, or 2. " << std::endl;
        return false;
    }

    float fMVACut[3][4][4];

    /*
    // working points from full_53x_wp defined in 
    // http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/CMG/CMGTools/External/python/JetIdParams_cfi.py?revision=1.12&view=markup

    //Tight Id
    fMVACut[0][0][0] = -0.83; fMVACut[0][0][1] = -0.81; fMVACut[0][0][2] = -0.74; fMVACut[0][0][3] = -0.81;
    fMVACut[0][1][0] = -0.83; fMVACut[0][1][1] = -0.81; fMVACut[0][1][2] = -0.74; fMVACut[0][1][3] = -0.81;
    fMVACut[0][2][0] = -0.38; fMVACut[0][2][1] = -0.32; fMVACut[0][2][2] = -0.14; fMVACut[0][2][3] = -0.48;
    fMVACut[0][3][0] = -0.38; fMVACut[0][3][1] = -0.32; fMVACut[0][3][2] = -0.14; fMVACut[0][3][3] = -0.48;
    //Medium id
    fMVACut[1][0][0] = -0.83; fMVACut[1][0][1] = -0.92; fMVACut[1][0][2] = -0.90; fMVACut[1][0][3] = -0.92;
    fMVACut[1][1][0] = -0.83; fMVACut[1][1][1] = -0.92; fMVACut[1][1][2] = -0.90; fMVACut[1][1][3] = -0.92;
    fMVACut[1][2][0] = -0.40; fMVACut[1][2][1] = -0.49; fMVACut[1][2][2] = -0.50; fMVACut[1][2][3] = -0.65;
    fMVACut[1][3][0] = -0.40; fMVACut[1][3][1] = -0.49; fMVACut[1][3][2] = -0.50; fMVACut[1][3][3] = -0.65;
    //Loose Id 
    fMVACut[2][0][0] = -0.95; fMVACut[2][0][1] = -0.96; fMVACut[2][0][2] = -0.94; fMVACut[2][0][3] = -0.95;
    fMVACut[2][1][0] = -0.95; fMVACut[2][1][1] = -0.96; fMVACut[2][1][2] = -0.94; fMVACut[2][1][3] = -0.95;
    fMVACut[2][2][0] = -0.80; fMVACut[2][2][1] = -0.74; fMVACut[2][2][2] = -0.68; fMVACut[2][2][3] = -0.77;
    fMVACut[2][3][0] = -0.80; fMVACut[2][3][1] = -0.74; fMVACut[2][3][2] = -0.68; fMVACut[2][3][3] = -0.77;
    */

    // working points from full_5x_wp defined in 
    // http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/CMG/CMGTools/External/python/JetIdParams_cfi.py?revision=1.12&view=markup
    //Tight Id                                                                                                                                                                       
    fMVACut[0][0][0] = -0.47; fMVACut[0][0][1] = -0.92; fMVACut[0][0][2] = -0.92; fMVACut[0][0][3] = -0.94;
    fMVACut[0][1][0] = -0.47; fMVACut[0][1][1] = -0.92; fMVACut[0][1][2] = -0.92; fMVACut[0][1][3] = -0.94;
    fMVACut[0][2][0] = +0.32; fMVACut[0][2][1] = -0.49; fMVACut[0][2][2] = -0.61; fMVACut[0][2][3] = -0.74;
    fMVACut[0][3][0] = +0.32; fMVACut[0][3][1] = -0.49; fMVACut[0][3][2] = -0.61; fMVACut[0][3][3] = -0.74;
    //Medium id
    fMVACut[1][0][0] = -0.83; fMVACut[1][0][1] = -0.96; fMVACut[1][0][2] = -0.95; fMVACut[1][0][3] = -0.96;
    fMVACut[1][1][0] = -0.83; fMVACut[1][1][1] = -0.96; fMVACut[1][1][2] = -0.95; fMVACut[1][1][3] = -0.96;
    fMVACut[1][2][0] = -0.40; fMVACut[1][2][1] = -0.74; fMVACut[1][2][2] = -0.76; fMVACut[1][2][3] = -0.81;
    fMVACut[1][3][0] = -0.40; fMVACut[1][3][1] = -0.74; fMVACut[1][3][2] = -0.76; fMVACut[1][3][3] = -0.81;
    //Loose Id 
    fMVACut[2][0][0] = -0.95; fMVACut[2][0][1] = -0.97; fMVACut[2][0][2] = -0.97; fMVACut[2][0][3] = -0.97;
    fMVACut[2][1][0] = -0.95; fMVACut[2][1][1] = -0.97; fMVACut[2][1][2] = -0.97; fMVACut[2][1][3] = -0.97;
    fMVACut[2][2][0] = -0.80; fMVACut[2][2][1] = -0.85; fMVACut[2][2][2] = -0.84; fMVACut[2][2][3] = -0.85;
    fMVACut[2][3][0] = -0.80; fMVACut[2][3][1] = -0.85; fMVACut[2][3][2] = -0.84; fMVACut[2][3][3] = -0.85;


    // pT categorization
    int ptId = 0;
    if (p4.pt() > 10 && p4.pt() < 20) ptId = 1;
    if (p4.pt() > 20 && p4.pt() < 30) ptId = 2;
    if (p4.pt() > 30                ) ptId = 3;

    // eta categorization
    int etaId = 0;
    if (fabs(p4.eta()) > 2.5  && fabs(p4.eta()) < 2.75) etaId = 1;
    if (fabs(p4.eta()) > 2.75 && fabs(p4.eta()) < 3.0 ) etaId = 2;
    if (fabs(p4.eta()) > 3.0  && fabs(p4.eta()) < 5.0 ) etaId = 3;

    // return  
    if (mva_value > fMVACut[tightness][ptId][etaId]) return true;
    return false;
}

std::vector<int> RpvStopOSAnalysisLooper::getJetMcAlgoMatch(const unsigned int best_hyp_idx, int systFlag, bool sort_by_pt)
{
    //
    // this is kind of a hacky way to do it
    // but for now, just copy over what we
    // have from above
    //
    float min_lep_pt = 0.0;
    switch(m_analysis_type)
    {
    case AnalysisType::mmbb:
        min_lep_pt = 20.0;
        break;
    default:
        min_lep_pt = 20.0;
        break;
    }

    JetType jet_type = evt_isRealData() ? JETS_TYPE_PF_FAST_CORR_RESIDUAL : JETS_TYPE_PF_FAST_CORR;

    //
    // get appropriate jet flags
    //
    std::vector<LorentzVector> tmp_jet_p4s = os2012::getJets(best_hyp_idx, jet_type,/*deltaR=*/0.4, m_jet_pt_cut, /*max_eta=*/2.4, min_lep_pt, systFlag, /*sort_by_pt=*/false);
    std::vector<bool> tmp_jet_flags = os2012::getJetFlags(best_hyp_idx, jet_type, /*deltaR=*/0.4, m_jet_pt_cut, /*max_eta=*/2.4, min_lep_pt, systFlag);

    assert(tmp_jet_flags.size() == pfjets_mcflavorAlgo().size());

    std::vector<std::pair<LorentzVector, int> > tmp_p4_match;
    unsigned int good_jidx = 0;
    for (unsigned int jidx = 0; jidx < tmp_jet_flags.size(); jidx++)
    {
        if (!tmp_jet_flags.at(jidx)) continue;
        tmp_p4_match.push_back(std::make_pair(tmp_jet_p4s.at(good_jidx), pfjets_mcflavorAlgo().at(jidx)));
        good_jidx++;
    }

    if (systFlag == 0)
        assert(tmp_p4_match.size() == m_evt.vjets_p4.size());
    else if (systFlag == 1)
        assert(tmp_p4_match.size() == m_evt.vjets_p4_up.size());
    else
        assert(tmp_p4_match.size() == m_evt.vjets_p4_dn.size());

    if (sort_by_pt)
        sort(tmp_p4_match.begin(), tmp_p4_match.end(), SortByPt());

    std::vector<int> ret;
    for (unsigned int idx = 0; idx < tmp_p4_match.size(); idx++)
    {
        ret.push_back(tmp_p4_match.at(idx).second);
    }

    return ret;
}

std::vector<int> RpvStopOSAnalysisLooper::getJetMcPhysMatch(const unsigned int best_hyp_idx, int systFlag, bool sort_by_pt)
{
    //
    // this is kind of a hacky way to do it
    // but for now, just copy over what we
    // have from above
    //
    float min_lep_pt = 0.0;
    switch(m_analysis_type)
    {
    case AnalysisType::mmbb:
        min_lep_pt = 20.0;
        break;
    default:
        min_lep_pt = 20.0;
        break;
    }

    JetType jet_type = evt_isRealData() ? JETS_TYPE_PF_FAST_CORR_RESIDUAL : JETS_TYPE_PF_FAST_CORR;

    //
    // get appropriate jet flags
    //
    std::vector<LorentzVector> tmp_jet_p4s = os2012::getJets(best_hyp_idx, jet_type,/*deltaR=*/0.4, m_jet_pt_cut, /*max_eta=*/2.4, min_lep_pt, systFlag, /*sort_by_pt=*/false);
    std::vector<bool> tmp_jet_flags = os2012::getJetFlags(best_hyp_idx, jet_type, /*deltaR=*/0.4, m_jet_pt_cut, /*max_eta=*/2.4, min_lep_pt, systFlag);

    assert(tmp_jet_flags.size() == pfjets_mcflavorPhys().size());

    std::vector<std::pair<LorentzVector, int> > tmp_p4_match;
    unsigned int good_jidx = 0;
    for (unsigned int jidx = 0; jidx < tmp_jet_flags.size(); jidx++)
    {
        if (!tmp_jet_flags.at(jidx)) continue;
        tmp_p4_match.push_back(std::make_pair(tmp_jet_p4s.at(good_jidx), pfjets_mcflavorPhys().at(jidx)));
        good_jidx++;
    }

    if (systFlag == 0)
        assert(tmp_p4_match.size() == m_evt.vjets_p4.size());
    else if (systFlag == 1)
        assert(tmp_p4_match.size() == m_evt.vjets_p4_up.size());
    else
        assert(tmp_p4_match.size() == m_evt.vjets_p4_dn.size());

    if (sort_by_pt)
        sort(tmp_p4_match.begin(), tmp_p4_match.end(), SortByPt());

    std::vector<int> ret;
    for (unsigned int idx = 0; idx < tmp_p4_match.size(); idx++)
    {
        ret.push_back(tmp_p4_match.at(idx).second);
    }

    return ret;
}

std::vector<bool> RpvStopOSAnalysisLooper::sortBtaggedFlags(const std::vector<LorentzVector>& all_jet_p4s, const std::vector<bool>& all_jet_flags, const std::vector<bool>& all_bjet_flags)
{
    // some sanity checks
    assert(all_jet_p4s.size() == all_jet_flags.size());
    assert(all_jet_flags.size() == all_bjet_flags.size());

    std::vector<std::pair<LorentzVector, bool> > tmp_p4_flags;
    for (unsigned int idx = 0; idx < all_jet_flags.size(); idx++)
    {
        if (!all_jet_flags.at(idx)) continue;
        tmp_p4_flags.push_back(std::make_pair(all_jet_p4s.at(idx), all_bjet_flags.at(idx)));
    }

    sort(tmp_p4_flags.begin(), tmp_p4_flags.end(), SortByPt());
    
    std::vector<bool> ret;    
    for(unsigned int idx = 0; idx < tmp_p4_flags.size(); idx++)
    {
        ret.push_back(tmp_p4_flags.at(idx).second);
    }

    return ret;
}
