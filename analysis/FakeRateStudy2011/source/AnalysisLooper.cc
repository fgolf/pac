#include "SS2012AnalysisLooper.hpp"
#include "ScaleFactors.h"

// c++
#include <stdexcept>
#include <algorithm>
#include <fstream>

// cms2
#include "CMS2.h"
#include "ssSelections.h"
#include "eventSelections.h"
#include "trackSelections.h"
#include "susySelections.h"
#include "DileptonHypType.h"
#include "vtxreweight.h"
#include "GenParticleStruct.h"
#include "EfficiencyModelTools.h"
#include "mcbtagSFuncert.h"
#include "mcSelections.h"

// Tools
#include "at/Predicates.hpp"
#include "rt/RootTools.hpp"
#include "CTable.h"

// ROOT
#include "Math/LorentzVector.h"
#include "TH2F.h"

// typdefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef std::vector<LorentzVector> vecLorentzVector;

// channel names
const size_t n_channel_names = 4; const std::string channel_names[n_channel_names] = {"All", "MuMu", "EMu", "EE"};

// event type names
static const char event_type_name[][128] = {"ss", "sf", "df", "os", "os_sf", "os_df"};
enum EventType { SS, SF, DF, OS, OS_SF, OS_DF, N_EVT_TYPES };

std::fstream fout("logs/sync.txt", fstream::out);
void PrintForSync(const EventInfo& evt)
{
    if (evt.isSS && evt.njets>1)
    {
        const std::string& channel = channel_names[evt.type];
        const std::string output = Form("%s: %u\t%u\t%u\t%u\t%u\t%4.3f\t%4.3f", channel.c_str(), evt.run, evt.ls, evt.evt, evt.njets, evt.nbtags, evt.ht, evt.pfmet);
        fout << output << std::endl;
    }
}

void CompareHyps(std::pair<size_t, EventType>& best_hyp, size_t hyp_idx, enum EventType new_type)
{
    short current_type = best_hyp.second;
    float new_pt       = cms2.hyp_lt_p4().at(hyp_idx).pt() + cms2.hyp_ll_p4().at(hyp_idx).pt();
    float current_pt   = cms2.hyp_lt_p4().at(best_hyp.first).pt() + cms2.hyp_ll_p4().at(best_hyp.first).pt();

    if (current_type == N_EVT_TYPES)
    {
        goto use_new_hyp;
    }
    else if (new_type < current_type)
    {
        goto use_new_hyp;
    }
    else if (new_type > current_type)
    {
        return;
    }
    else 
    {
        if (new_pt > current_pt)
        {
            goto use_new_hyp;
        }
        else
        {
            return;
        }
    }
    use_new_hyp:
    {
        best_hyp = make_pair(hyp_idx, new_type);    
        return;
    }
}

// set then numerator bool
bool IsNumerator(std::pair<size_t, EventType>& hyp, bool is_lt)
{
    if (hyp.second == N_EVT_TYPES)
    {
        return false;
    }
    switch (hyp.second)
    {
        case DF: return false; break;
        case SS: return true; break;
        case SF: 
        {
            bool lt_num = samesign::isNumeratorLepton(cms2.hyp_lt_id().at(hyp.first), cms2.hyp_lt_index().at(hyp.first));
            bool ll_num = samesign::isNumeratorLepton(cms2.hyp_ll_id().at(hyp.first), cms2.hyp_ll_index().at(hyp.first));
            if (lt_num && !ll_num)
            {
                return is_lt ? true : false;
            }
            if (!lt_num && ll_num)
            {
                return is_lt ? false : true;
            }
            break;
        }
        default: return false;
    }
    return false;
}

bool IsDenominator(std::pair<size_t, EventType>& hyp, bool is_lt)
{
    if (hyp.second == N_EVT_TYPES)
    {
        return false;
    }
    switch (hyp.second)
    {
        case DF: return true; break;
        case SS: return false; break;
        case SF: 
        {
            bool lt_num = samesign::isNumeratorLepton(cms2.hyp_lt_id().at(hyp.first), cms2.hyp_lt_index().at(hyp.first));
            bool ll_num = samesign::isNumeratorLepton(cms2.hyp_ll_id().at(hyp.first), cms2.hyp_ll_index().at(hyp.first));
            if (lt_num && !ll_num)
            {
                return is_lt ? false : true;
            }
            if (!lt_num && ll_num)
            {
                return is_lt ? true : false;
            }
            break;
        }
        default: return false;
    }
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
    vector<float>& btags = pfjets_combinedSecondaryVertexBJetTag();
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

void PrintJetInfo(const std::string& label, const vector<LorentzVector>& jets_p4, const vector<float>& jets_disc)
{
    cout << label << ":" << endl;
    for (size_t i = 0; i < jets_p4.size(); i++)
    {
        LorentzVector jet_p4 = jets_p4.at(i);
        float disc           = jets_disc.at(i);
        cout << Form("idx %d, pt %f, eta %f, phi %f, disc %f", (int)i, jet_p4.pt(), jet_p4.eta(), jet_p4.phi(), disc) << endl;
    }
}

void PrintJetInfo(const std::string& label, const vector<LorentzVector>& jets_p4, const vector<LorentzVector>& jets_nearjet_p4,  const vector<float>& jets_nearjet_dr, const vector<float>& jets_disc)
{
    cout << Form("%s: (%d, %d, %d)", label.c_str(), (int)jets_p4.size(), (int)jets_nearjet_dr.size(), (int)jets_nearjet_p4.size())  << endl;
    for (size_t i = 0; i < jets_p4.size(); i++)
    {
        LorentzVector jet_p4 = jets_p4.at(i);
        float disc           = jets_disc.at(i);
        float nj_pt          = jets_nearjet_p4.at(i).pt();
        float nj_dr          = jets_nearjet_dr.at(i);
        cout << Form("idx %d, pt %f, eta %f, phi %f, disc %f, nearjet pt %f, nearjet dr %f", (int)i, jet_p4.pt(), jet_p4.eta(), jet_p4.phi(), disc, nj_pt, nj_dr) << endl;
    }
}

// construct:
SSAnalysisLooper::SSAnalysisLooper
(
     const std::string& root_file_name,
     const std::string& fake_rate_file_name,
     const std::string& flip_rate_file_name,
     const std::string& fake_rate_hist_name,
     const std::string& vtxreweight_file_name,
     double luminosity,
     bool is_data,
     bool is_signal,
     bool gen_only,
     bool verbose,
     bool sparms,
     bool switchSigns,
     int  jetMetScale,
     bool isFastSim
)
    : at::AnalysisWithTree(root_file_name, "tree", "baby tree for SS2012 analysis")
    , m_lumi(luminosity)
    , m_is_data(is_data)
    , m_is_signal(is_signal)
    , m_gen_only(gen_only)
    , m_verbose(verbose)
    , m_sparms(sparms)
    , m_switchSigns(switchSigns)
    , m_jetMetScale(jetMetScale)
    , m_isFastSim(isFastSim)
{
    // set vertex weight file
    if (!vtxreweight_file_name.empty())
    {
        cout << "using vertex reweight file : " << vtxreweight_file_name << endl;
        set_vtxreweight_rootfile(vtxreweight_file_name.c_str(), m_verbose);
    }

    // initialize counters
    for (size_t i = 0; i != m_count_ss.size(); i++) {m_count_ss.at(i)=0.0;}
    for (size_t i = 0; i != m_count_sf.size(); i++) {m_count_sf.at(i)=0.0;}
    for (size_t i = 0; i != m_count_df.size(); i++) {m_count_df.at(i)=0.0;}
    for (size_t i = 0; i != m_count_os.size(); i++) {m_count_os.at(i)=0.0;}

    for (size_t i = 0; i != m_count_nobtag_ss.size(); i++) {m_count_nobtag_ss.at(i)=0.0;}
    for (size_t i = 0; i != m_count_nobtag_sf.size(); i++) {m_count_nobtag_sf.at(i)=0.0;}
    for (size_t i = 0; i != m_count_nobtag_df.size(); i++) {m_count_nobtag_df.at(i)=0.0;}
    for (size_t i = 0; i != m_count_nobtag_os.size(); i++) {m_count_nobtag_os.at(i)=0.0;}

    // set the fake rate histograms
    std::auto_ptr<TFile> fake_rate_file(rt::OpenRootFile(fake_rate_file_name));
    cout << "using FR file : " << fake_rate_file->GetName() << endl;
    h_mufr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get(fake_rate_hist_name.c_str())->Clone()));
    //h_mufr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get("h_mufr40c")->Clone()));
    h_elfr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get("h_elfr40c")->Clone()));
    if (not h_mufr) {throw std::runtime_error("ERROR: SSAnalysisLooper: h_mufr40c doesn't exist");}
    h_mufr->SetDirectory(0);
    if (not h_elfr) {throw std::runtime_error("ERROR: SSAnalysisLooper: h_elfr40c doesn't exist");}
    h_elfr->SetDirectory(0);

    cout << "using mu FR hist : " << h_mufr->GetName() << endl;
    cout << "using el FR hist : " << h_elfr->GetName() << endl;

    // set the fake rate histograms
    std::auto_ptr<TFile> flip_rate_file(rt::OpenRootFile(flip_rate_file_name));
    cout << "using FL file : " << flip_rate_file->GetName() << endl;
    h_flip.reset(dynamic_cast<TH2F*>(flip_rate_file->Get("flipRate")->Clone()));
    if (not h_flip) {throw std::runtime_error("ERROR: SSAnalysisLooper: flipRate doesn't exist");}
    h_flip->SetDirectory(0);

    // begin job
    BeginJob();
}

// destroy:
SSAnalysisLooper::~SSAnalysisLooper()
{
    EndJob();
}

// function operator: operate on each event
int SSAnalysisLooper::operator() (long event)
{
    // call base class operator
    return Analyze(event);
}

// members:
void SSAnalysisLooper::BeginJob()
{
    // initialize branches
    m_evt.Reset();
    m_evt.SetBranches(m_tree);
}


void SSAnalysisLooper::EndJob()
{
    CTable yield_table;
    yield_table.setTitle("yields for SS Analysis 2012 (# btags >= 2)");
    yield_table.useTitle();
    yield_table.setTable() (                      "mm",         "em",          "ee",          "all")
                         ("count ss" , m_count_ss[0], m_count_ss[1], m_count_ss[2], m_count_ss[3]) 
                         ("count sf" , m_count_sf[0], m_count_sf[1], m_count_sf[2], m_count_sf[3]) 
                         ("count df" , m_count_df[0], m_count_df[1], m_count_df[2], m_count_df[3])
                         ("count os" , m_count_os[0], m_count_os[1], m_count_os[2], m_count_os[3]); 
    yield_table.print();

    CTable yield_table2;
    yield_table2.setTitle("yields for SS Analysis 2012 (no btags req)");
    yield_table2.useTitle();
    yield_table2.setTable() (                             "mm",                "em",                 "ee",                "all")
                          ("count ss" , m_count_nobtag_ss[0], m_count_nobtag_ss[1], m_count_nobtag_ss[2], m_count_nobtag_ss[3]) 
                          ("count sf" , m_count_nobtag_sf[0], m_count_nobtag_sf[1], m_count_nobtag_sf[2], m_count_nobtag_sf[3]) 
                          ("count df" , m_count_nobtag_df[0], m_count_nobtag_df[1], m_count_nobtag_df[2], m_count_nobtag_df[3])
                          ("count os" , m_count_nobtag_os[0], m_count_nobtag_os[1], m_count_nobtag_os[2], m_count_nobtag_os[3]); 
    yield_table2.print();

    // set aliases
    m_tree->SetAlias("phi1"    , "lep1_p4.Phi()"               ); 
    m_tree->SetAlias("phi2"    , "lep2_p4.Phi()"               ); 
    m_tree->SetAlias("l1_pt"   , "(pt1>pt2 ? pt1 : pt2)"       ); 
    m_tree->SetAlias("l2_pt"   , "(pt1>pt2 ? pt2 : pt1)"       ); 
    m_tree->SetAlias("l1_eta"  , "(pt1>pt2 ? eta1 : eta2)"     ); 
    m_tree->SetAlias("l2_eta"  , "(pt1>pt2 ? eta2 : eta1)"     ); 
    m_tree->SetAlias("l1_phi"  , "(pt1>pt2 ? phi1 : phi2)"     ); 
    m_tree->SetAlias("l2_phi"  , "(pt1>pt2 ? phi2 : phi1)"     ); 
    m_tree->SetAlias("l1_z0"   , "(pt1>pt2 ? z01 : z02)"       ); 
    m_tree->SetAlias("l2_z0"   , "(pt1>pt2 ? z02 : z01)"       ); 
    //m_tree->SetAlias("deta"    , "fabs(eta1-eta2)"             ); 
    //m_tree->SetAlias("dphi"    , "(acos(cos(phi1-phi2)))"      ); 
    //m_tree->SetAlias("dr"      , "sqrt(deta*deta + dphi*dphi)" ); 
    m_tree->SetAlias("dr_l1_bj", "lep1_nearbjet_dr"            ); 
    m_tree->SetAlias("dr_l2_bj", "lep2_nearbjet_dr"            ); 
    m_tree->SetAlias("dr_b1_b2", "bjets_dr12"                  ); 
    m_tree->SetAlias("dr_bj_nj", "bjets_nearjet_dr"            ); 
}

float EffectiveArea(int id, int idx)
{
    if (abs(id)!=11)
        return -999990.0;

    float etaAbs = fabs(cms2.els_etaSC()[idx]);

    // get effective area
    float AEff = 0.;
    if (etaAbs <= 1.0) AEff = 0.10;
    else if (etaAbs > 1.0 && etaAbs <= 1.479) AEff = 0.12;
    else if (etaAbs > 1.479 && etaAbs <= 2.0) AEff = 0.085;
    else if (etaAbs > 2.0 && etaAbs <= 2.2) AEff = 0.11;
    else if (etaAbs > 2.2 && etaAbs <= 2.3) AEff = 0.12;
    else if (etaAbs > 2.3 && etaAbs <= 2.4) AEff = 0.12;
    else if (etaAbs > 2.4) AEff = 0.13;
    return AEff;
}

int SSAnalysisLooper::Analyze(long event)
{
    using namespace tas;
    using namespace std;

    try
    {
        //// select specific events
        //if (evt_isRealData() && !(evt_run() == 195915 && evt_lumiBlock() == 636 && evt_event() == 928975370))
        //{
        //    return 0;
        //}
        //else
        //{
        //    cout << Form("run %d, ls %d, evt %d", evt_run(), evt_lumiBlock(), evt_event()) << endl; 
        //    //return 0; 
        //}


        // Reset Tree Variables
        // --------------------------------------------------------------------------------------------------------- //

        m_evt.Reset();

        // Gen Level
        // --------------------------------------------------------------------------------------------------------- //

        if (!evt_isRealData())
        {
            //if (not (static_cast<int>(sparm_values().front()) == 1000 && static_cast<int>(sparm_values().back()==400)))
            //{
            //    return 0;
            //}

            // gen Lep p4
            // NOTE: we fill the gen block if and only if BOTH leptons are matched 
            std::pair<GenParticleStruct, GenParticleStruct> gen_hyp = efftools::getGenHyp(/*pt1=*/20, /*pt2=*/20, DILEPTON_SS);
            if (gen_hyp.first.idx_  >= 0 && gen_hyp.second.idx_ >=0)
            {
                m_evt.gen_lep1_p4 = genps_p4().at(gen_hyp.first.idx_ );
                m_evt.gen_lep2_p4 = genps_p4().at(gen_hyp.second.idx_);
                m_evt.gen_type = efftools::getHypType(gen_hyp.first.id_, gen_hyp.second.id_);
                m_evt.gen_sign = (gen_hyp.first.id_ * gen_hyp.second.id_)/abs(gen_hyp.first.id_ * gen_hyp.second.id_);

                // gen HT
                m_evt.gen_ht = efftools::getGenHT(/*pt_cut=*/40.0, /*eta_cut=*/2.4);

                // gen b quarks
                std::vector<LorentzVector> gen_bjets = efftools::getGenBjets(/*pt_cut=*/40.0, /*eta_cut=*/2.4);
                if (gen_bjets.size()>0) m_evt.gen_b1_p4 = gen_bjets.at(0);
                if (gen_bjets.size()>1) m_evt.gen_b2_p4 = gen_bjets.at(1);
                if (gen_bjets.size()>2) m_evt.gen_b3_p4 = gen_bjets.at(2);
                if (gen_bjets.size()>3) m_evt.gen_b4_p4 = gen_bjets.at(3);

                // gen MET
                m_evt.gen_met = gen_met();

                if (m_gen_only)
                {
                    m_tree->Fill();
                    return 0;
                }
            }
            else
            {
                if (m_gen_only)
                {
                    return 0;
                }
            }
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

        // needs to be at least one good hypthesis
        if (hyp_type().empty())
        {
            if (m_verbose) {std::cout << "no good hypothesises" << std::endl;}
            return 0; 
        }

        // jet type
        JetType jet_type = evt_isRealData() ? JETS_TYPE_PF_FAST_CORR_RESIDUAL : JETS_TYPE_PF_FAST_CORR;

        // loop over hypotheses
        pair<size_t, EventType> best_hyp(0, N_EVT_TYPES);
        for (size_t ihyp = 0; ihyp != hyp_type().size(); ihyp++)
        {                
            // check hyp mass (no low mass resonances)
            float dilep_mass = sqrt(fabs(hyp_p4().at(ihyp).mass2()));
            if (dilep_mass < 8.0) 
            {
                if (m_verbose) {std::cout << "fails dilepton invariant mass requirement" << std::endl;}
                continue;
            }

            // check that leptons are from the same vertex
            if (!hypsFromFirstGoodVertex(ihyp))
            {
                if (m_verbose) {std::cout << "fails leptons are from the first good vertex requirement" << std::endl;}
                continue;
            }

            // check extra Z veto
            if (samesign::makesExtraZ(ihyp))
            {
                if (m_verbose) {std::cout << "fails btag extra Z veto requirement" << std::endl;}
                continue;
            }

            // check if hyp passes trigger
            if (!samesign::passesTrigger(hyp_type().at(ihyp)))
            {
                if (m_verbose) {std::cout << "fails trigger requirement" << std::endl;}
                continue;
            }

            // leptons variables
            const LorentzVector& lt_p4 = hyp_lt_p4().at(ihyp);
            const LorentzVector& ll_p4 = hyp_ll_p4().at(ihyp);
            int lt_id                  = hyp_lt_id().at(ihyp);
            int ll_id                  = hyp_ll_id().at(ihyp);
            int lt_idx                 = hyp_lt_index().at(ihyp);
            int ll_idx                 = hyp_ll_index().at(ihyp);

            // check if hyp passes lepton kinematics
            if (fabs(lt_p4.Eta())>2.4 || lt_p4.Pt()<20.0) continue;
            if (fabs(ll_p4.Eta())>2.4 || ll_p4.Pt()<20.0) continue;

            // check if event passes num_jet cut
            //int num_jets = samesign::nJets(ihyp, jet_type, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt2>*/20.0);
            //if (num_jets < 2)
            //{
            //    if (m_verbose) {std::cout << "fails # jets requirement" << std::endl;}
            //    continue;
            //}

            //// check if events passes num_btags cut
            //int num_btags = samesign::nBtaggedJets(ihyp, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0);
            //if (num_btags < 2)
            //{
            //    if (m_verbose) {std::cout << "fails # btags requirement" << std::endl;}
            //    //continue;
            //}

            // skip if both are not numerators
            if (!samesign::isDenominatorLepton(lt_id, lt_idx) || !samesign::isDenominatorLepton(ll_id, ll_idx))
            {
                if (m_verbose) {std::cout << "fails both leptons are at least denominator requirement" << std::endl;}
                continue;
            }

            // OS (Here a kludge by Claudio to quickly change the meaning of SS and OS .... useful for ttbar as sstop)
            int dummy = 1;
            if (m_switchSigns) dummy=-1;
            int hyp_q = dummy * hyp_lt_charge().at(ihyp) * hyp_ll_charge().at(ihyp);
            if (hyp_q < 0)
            {
                if (!samesign::isNumeratorHypothesis(ihyp))
                {
                    if (m_verbose) {std::cout << "OS hyp doesn't pass ID/ISO requirement" << std::endl;}
                    continue; 
                }
                CompareHyps(best_hyp, ihyp, OS);
            }
            // SS 
            else if (hyp_q > 0)
            {
                // same sign event (SS)
                if (samesign::isNumeratorHypothesis(ihyp))
                {
                    CompareHyps(best_hyp, ihyp, SS);
                }
                // single fake event (SF)
                else if (samesign::isNumeratorLepton(lt_id, lt_idx) || samesign::isNumeratorLepton(ll_id, ll_idx))
                {
                    CompareHyps(best_hyp, ihyp, SF);
                }
                // double fake event (DF)
                else
                {
                    CompareHyps(best_hyp, ihyp, DF);
                }
            }

        } // end looper over hypothesis

        // Set Tree Variables
        // --------------------------------------------------------------------------------------------------------- //

        // best hyp index
        unsigned int hyp_idx = best_hyp.first;
        EventType event_type = best_hyp.second;

        // don't write events to the tree that don't pass hypothesis
        if (event_type == N_EVT_TYPES)
        {
            if (m_verbose) {std::cout << "fails good event type requirement" << std::endl;}
            return 0;
        }

        // all: 0, mm: 1, em: 2, ee: 3
        DileptonHypType dilepton_type = hyp_typeToHypType(hyp_type().at(hyp_idx));

        // trigger info
        m_evt.trig_mm = passUnprescaledHLTTriggerPattern("HLT_Mu17_Mu8_v");
        m_evt.trig_em = passUnprescaledHLTTriggerPattern("HLT_Mu17_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v") || 
                        passUnprescaledHLTTriggerPattern("HLT_Mu8_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");
        m_evt.trig_ee = passUnprescaledHLTTriggerPattern("HLT_Ele17_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_Ele8_CaloIdT_CaloIsoVL_TrkIdVL_TrkIsoVL_v");

        // event wieghts 
        //float vtxw  = evt_isRealData() ? 1.0 : vtxweight_n(numberOfGoodVertices(), evt_isRealData(), false);
        float vtxw  = 1.0;
        float xsec  = evt_isRealData() ? 1.0 : evt_scale1fb();
        float scale = evt_isRealData() ? 1.0 : m_lumi * xsec * vtxw; 

        // set event id variables
        if(evt_dataset().empty())
        {
            if (m_verbose) {std::cout << "SSAnalysis Warning: evt_dataset() is empty" << std::endl;}
        }
        else
        {
            strcpy(m_evt.dataset, evt_dataset().front().Data());
        }
        m_evt.run      = evt_run();
        m_evt.ls       = evt_lumiBlock();
        m_evt.evt      = evt_event();
        m_evt.scale    = scale;
        m_evt.scale1fb = xsec;

        // the sparms
        if (m_sparms) {
            int n_sparms = sparm_values().size();
            if (n_sparms > 0) m_evt.sparm0 = sparm_values().at(0);
            if (n_sparms > 1) m_evt.sparm1 = sparm_values().at(1);
            if (n_sparms > 2) m_evt.sparm2 = sparm_values().at(2);
            if (n_sparms > 3) m_evt.sparm3 = sparm_values().at(3);
        }

        // set lepton info 
        int pvtx_idx = firstGoodVertex();
        int idx1 = hyp_lt_index().at(hyp_idx);
        m_evt.lep1_p4  = hyp_lt_p4().at(hyp_idx);
        m_evt.pt1      = m_evt.lep1_p4.Pt();
        m_evt.eta1     = m_evt.lep1_p4.Eta();
        m_evt.id1      = hyp_lt_id().at(hyp_idx);
        //m_evt.d01      = hyp_lt_d0().at(hyp_idx); 
        //m_evt.z01      = hyp_lt_z0().at(hyp_idx); 
        m_evt.d01      = abs(m_evt.id1)==11 ? gsftrks_d0_pv(els_gsftrkidx().at(idx1), pvtx_idx).first : trks_d0_pv(mus_trkidx().at(idx1), pvtx_idx).first;
        m_evt.z01      = abs(m_evt.id1)==11 ? gsftrks_dz_pv(els_gsftrkidx().at(idx1), pvtx_idx).first : trks_dz_pv(mus_trkidx().at(idx1), pvtx_idx).first;
        m_evt.q1       = hyp_lt_charge().at(hyp_idx);
        m_evt.num1     = IsNumerator  (best_hyp, /*is_lt=*/true);
        m_evt.iso1     = (abs(m_evt.id1)==11) ? samesign::electronIsolationPF2012(idx1) : muonIsoValuePF2012_deltaBeta(idx1);
        m_evt.iso_ch_1 = (abs(m_evt.id1)==11) ? els_iso03_pf2012_ch().at(idx1) : mus_isoR03_pf_ChargedHadronPt().at(idx1);
        m_evt.iso_nh_1 = (abs(m_evt.id1)==11) ? els_iso03_pf2012_nh().at(idx1) : mus_isoR03_pf_NeutralHadronEt().at(idx1);
        m_evt.iso_em_1 = (abs(m_evt.id1)==11) ? els_iso03_pf2012_em().at(idx1) : mus_isoR03_pf_PhotonEt().at(idx1);
        m_evt.aeff1    = EffectiveArea(m_evt.id1, idx1);
        m_evt.dbeta1   = (abs(m_evt.id1)==13) ? cms2.mus_isoR03_pf_PUPt().at(idx1) : -99999.0; 
        m_evt.fo1      = IsDenominator(best_hyp, /*is_lt=*/true);
        m_evt.wfr1     = GetFakeRateValue(m_evt.id1, idx1);
        m_evt.wflip1   = GetFlipRateValue(m_evt.id1, idx1);
        if (!evt_isRealData()) m_evt.leptru1 = leptonIsFromW(idx1, m_evt.id1, true);

        int idx2 = hyp_ll_index().at(hyp_idx);
        m_evt.lep2_p4  = hyp_ll_p4().at(hyp_idx);
        m_evt.pt2      = m_evt.lep2_p4.Pt();
        m_evt.eta2     = m_evt.lep2_p4.Eta();
        m_evt.id2      = hyp_ll_id().at(hyp_idx);
        //m_evt.d02      = hyp_ll_d0().at(hyp_idx); 
        //m_evt.z02      = hyp_ll_z0().at(hyp_idx); 
        m_evt.d02      = abs(m_evt.id2)==11 ? gsftrks_d0_pv(els_gsftrkidx().at(idx2), pvtx_idx).first : trks_d0_pv(mus_trkidx().at(idx2), pvtx_idx).first;
        m_evt.z02      = abs(m_evt.id2)==11 ? gsftrks_dz_pv(els_gsftrkidx().at(idx2), pvtx_idx).first : trks_dz_pv(mus_trkidx().at(idx2), pvtx_idx).first;
        m_evt.q2       = hyp_ll_charge().at(hyp_idx);
        m_evt.iso2     = (abs(m_evt.id2)==11) ? samesign::electronIsolationPF2012(idx2) : muonIsoValuePF2012_deltaBeta(idx2);
        m_evt.iso_ch_2 = (abs(m_evt.id2)==11) ? els_iso03_pf2012_ch().at(idx2) : mus_isoR03_pf_ChargedHadronPt().at(idx2);
        m_evt.iso_nh_2 = (abs(m_evt.id2)==11) ? els_iso03_pf2012_nh().at(idx2) : mus_isoR03_pf_NeutralHadronEt().at(idx2);
        m_evt.iso_em_2 = (abs(m_evt.id2)==11) ? els_iso03_pf2012_em().at(idx2) : mus_isoR03_pf_PhotonEt().at(idx2);
        m_evt.aeff2    = EffectiveArea(m_evt.id2, idx2);
        m_evt.dbeta2   = (abs(m_evt.id2)==13) ? cms2.mus_isoR03_pf_PUPt().at(idx2) : -99999.0; 
        m_evt.num2     = IsNumerator  (best_hyp, /*is_lt=*/false);
        m_evt.fo2      = IsDenominator(best_hyp, /*is_lt=*/false);
        m_evt.wfr2     = GetFakeRateValue(m_evt.id2, idx2);
        m_evt.wflip2   = GetFlipRateValue(m_evt.id2, idx2);
        if (!evt_isRealData()) m_evt.leptru2 = leptonIsFromW(idx2, m_evt.id2, true);

        // event info variables
        m_evt.type     = dilepton_type;
        m_evt.nvtxs    = numberOfGoodVertices();
        m_evt.vtxw     = vtxw;
        m_evt.njets    = samesign::nJets(hyp_idx, jet_type,                        /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt2>*/20.0, 1.0, m_jetMetScale);
        m_evt.njets20  = samesign::nJets(hyp_idx, jet_type,                        /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt2>*/20.0, 1.0, m_jetMetScale);
        m_evt.njets30  = samesign::nJets(hyp_idx, jet_type,                        /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt2>*/20.0, 1.0, m_jetMetScale);
        m_evt.nbtags   = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, m_jetMetScale);
        m_evt.nbtags20 = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, m_jetMetScale);
        m_evt.nbtags30 = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, m_jetMetScale);
        m_evt.ht       = samesign::sumJetPt(hyp_idx, jet_type,                     /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, m_jetMetScale);
        m_evt.ht20     = samesign::sumJetPt(hyp_idx, jet_type,                     /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, m_jetMetScale);
        m_evt.ht30     = samesign::sumJetPt(hyp_idx, jet_type,                     /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, m_jetMetScale);
        m_evt.mass     = hyp_p4().at(hyp_idx).mass();
        m_evt.mt       = rt::Mt((m_evt.pt1 > m_evt.pt2)? m_evt.lep1_p4 : m_evt.lep2_p4, evt_pfmet(), evt_pfmetPhi());
        m_evt.pfmet    = evt_pfmet_type1cor();

        // electron isolation correction variables
        m_evt.rho = evt_kt6pf_foregiso_rho();

        // lepton combo info
        m_evt.lep_dr   = rt::DeltaR  (m_evt.lep1_p4, m_evt.lep2_p4);
        m_evt.lep_deta = rt::DeltaEta(m_evt.lep1_p4, m_evt.lep2_p4);
        m_evt.lep_dphi = rt::DeltaPhi(m_evt.lep1_p4, m_evt.lep2_p4);
        if (m_evt.q1*m_evt.q1 > 0)
        {
            m_evt.qq = (m_evt.q1>0 && m_evt.q2>0) ? 1 : -1;
        }

        // should we recalculate the met??
        if (m_jetMetScale != 0) 
        {  
            float metx = evt_pfmet_type1cor() * cos(evt_pfmetPhi_type1cor());
            float mety = evt_pfmet_type1cor() * sin(evt_pfmetPhi_type1cor());
            // get uncorrected jets
            vector<LorentzVector> ujets = samesign::getJets(hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/10.0, /*|eta|<*/5.0, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, 0);
            for (unsigned u=0; u<ujets.size(); u++) {
                float px       = ujets.at(u).px();
                float py       = ujets.at(u).py();
                float thispt   = ujets.at(u).pt();
                float thiseta  = ujets.at(u).pt();
                float thisCorr = getJetMetSyst(m_jetMetScale, thispt, thiseta);
                metx = metx - (thisCorr-1.)*px;
                mety = mety - (thisCorr-1.)*py;
            }
            m_evt.pfmet    = sqrt(metx*metx + mety*mety);
            // cout << "old met= " << evt_pfmet_type1cor() << "    new met= " << m_evt.pfmet << endl;
        }

        // classification
        m_evt.isSS = (event_type==SS);
        m_evt.isSF = (event_type==SF);
        m_evt.isDF = (event_type==DF);
        m_evt.isOS = (event_type==OS);

        // eff and scale factors
        if (!evt_isRealData())
        {
            vector<LorentzVector> bjets = samesign::getBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, m_jetMetScale);
            std::sort(bjets.begin(), bjets.end(), at::SortByPt<LorentzVector>());
            m_evt.trig_eff     = dilepTriggerScaleFactor(hyp_idx);
            m_evt.scale_tap    = dileptonTagAndProbeScaleFactor(hyp_idx);
            // The code below is not correct (Claudio)
            //m_evt.scale_nbtag  = m_evt.nbtags >= 2 ? btagEventWeight (m_evt.nbtags, bjets.at(0).pt(), bjets.at(1).pt())                   : 0.0; 
            //m_evt.scale_nbtag3 = m_evt.nbtags >= 3 ? btagEventWeight3(m_evt.nbtags, bjets.at(0).pt(), bjets.at(1).pt(), bjets.at(2).pt()) : 0.0; 
            // Here is the fixed code
            m_evt.scale_nbtag  = 0.0;
            m_evt.scale_nbtag3 = 0.0;
            if (m_evt.nbtags == 2) m_evt.scale_nbtag = btagEventWeight(m_evt.nbtags, bjets.at(0).pt(), bjets.at(1).pt(), 0., 0., m_isFastSim);
            if (m_evt.nbtags == 3) {
                m_evt.scale_nbtag  = btagEventWeight (m_evt.nbtags, bjets.at(0).pt(), bjets.at(1).pt(), bjets.at(2).pt(), 0., m_isFastSim);
                m_evt.scale_nbtag3 = btagEventWeight3(m_evt.nbtags, bjets.at(0).pt(), bjets.at(1).pt(), bjets.at(2).pt(), 0., m_isFastSim);
            }
            if (m_evt.nbtags > 3) {
                m_evt.scale_nbtag  = btagEventWeight (4, bjets.at(0).pt(), bjets.at(1).pt(), bjets.at(2).pt(), bjets.at(3).pt(), m_isFastSim);
                m_evt.scale_nbtag3 = btagEventWeight3(4, bjets.at(0).pt(), bjets.at(1).pt(), bjets.at(2).pt(), bjets.at(3).pt(), m_isFastSim);
            }

            // Added the btag scale factor uncertainty (Claudio)
            // Note: pt and eta cuts, as necessary, will be made inside the code that calculates the scale factors
            // When there arent enough bquarks we put in some nominal bullshit value 
            std::vector<LorentzVector> gen_bjets = efftools::getGenBjets(/*pt_cut=*/0.001, /*eta_cut=*/2.5);
            std::sort(gen_bjets.begin(), gen_bjets.end(), at::SortByPt<LorentzVector>());
            if ( gen_bjets.size()==0 ) {
                m_evt.scale_unc_nbtag   = btagEventUncertainty( 2, 50., 0., 50., 0., 50., 0., 50., 0., m_isFastSim);
                m_evt.scale_unc_nbtag3  = btagEventUncertainty3(3, 50., 0., 50., 0., 50., 0., 50., 0., m_isFastSim);
            } else if ( gen_bjets.size()==1 ) {
                m_evt.scale_unc_nbtag  = btagEventUncertainty( 2, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), 50., 0., 50., 0., 50., 0, m_isFastSim);
                m_evt.scale_unc_nbtag3 = btagEventUncertainty3(3, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), 50., 0., 50., 0., 50., 0, m_isFastSim);
            } else if ( gen_bjets.size()==2 ) {
                m_evt.scale_unc_nbtag  = btagEventUncertainty( 2, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), gen_bjets.at(1).pt(), gen_bjets.at(1).eta(), 50., 0., 50., 0, m_isFastSim);
                m_evt.scale_unc_nbtag3 = btagEventUncertainty3(3, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), gen_bjets.at(1).pt(), gen_bjets.at(1).eta(), 50., 0., 50., 0, m_isFastSim);
            } else if ( gen_bjets.size()==3 ) {
                m_evt.scale_unc_nbtag  = btagEventUncertainty( 3, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), gen_bjets.at(1).pt(), gen_bjets.at(1).eta(),
                        gen_bjets.at(2).pt(), gen_bjets.at(2).eta(), 50., 0, m_isFastSim);
                m_evt.scale_unc_nbtag3 = btagEventUncertainty3(3, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), gen_bjets.at(1).pt(), gen_bjets.at(1).eta(),
                        gen_bjets.at(2).pt(), gen_bjets.at(2).eta(), 50., 0, m_isFastSim);
            } else if ( gen_bjets.size()>3 ) {
                m_evt.scale_unc_nbtag  = btagEventUncertainty( 4, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), gen_bjets.at(1).pt(), gen_bjets.at(1).eta(),
                        gen_bjets.at(2).pt(), gen_bjets.at(2).eta(), gen_bjets.at(3).pt(), gen_bjets.at(3).eta(), m_isFastSim);
                m_evt.scale_unc_nbtag3 = btagEventUncertainty3(4, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), gen_bjets.at(1).pt(), gen_bjets.at(1).eta(),
                        gen_bjets.at(2).pt(), gen_bjets.at(2).eta(), gen_bjets.at(3).pt(), gen_bjets.at(3).eta(), m_isFastSim);
            }
        }

        // only keep 2 jet events
        if (m_evt.njets < 2)
        {
            return 0;
        }

		// print bjets
		m_evt.bjets_p4 = samesign::getBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, m_jetMetScale); 
		m_evt.jets_p4  = samesign::getJets(hyp_idx, jet_type,                        /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt2>*/20.0, 1.0, m_jetMetScale); 

        SetBtagDiscriminator(m_evt.bjets_p4, m_evt.bjets_csv, JETS_BTAG_CSVM);
        SetBtagDiscriminator(m_evt.jets_p4 , m_evt.jets_csv , JETS_BTAG_CSVM);

        m_evt.bjets_dr12 = (m_evt.nbtags>=2) ? rt::DeltaR(m_evt.bjets_p4.at(0), m_evt.bjets_p4.at(1)) : -999999.0;
        m_evt.jets_dr12  = (m_evt.njets>=2 ) ? rt::DeltaR(m_evt.jets_p4.at(0) , m_evt.jets_p4.at(1) ) : -999999.0;

		//vector<LorentzVector> jets_p4    = getJets(hyp_idx, true, jet_type, JETS_CLEAN_HYP_E_MU, 0.4, 40, 2.4, 1.0, m_jetMetScale);
		
        vector<LorentzVector> temp_bjets_p4 = m_evt.bjets_p4;
        if (!temp_bjets_p4.empty())
        {
            // nearest to lep1
            std::sort(temp_bjets_p4.begin(), temp_bjets_p4.begin(), at::SortByDeltaR<LorentzVector>(m_evt.lep1_p4));
            m_evt.lep1_nearbjet_p4 = temp_bjets_p4.front();
            m_evt.lep1_nearbjet_dr = rt::DeltaR(m_evt.lep1_p4, temp_bjets_p4.front());

            // nearest to lep2
            std::sort(temp_bjets_p4.begin(), temp_bjets_p4.begin(), at::SortByDeltaR<LorentzVector>(m_evt.lep2_p4));
            m_evt.lep2_nearbjet_p4 = temp_bjets_p4.front();
            m_evt.lep2_nearbjet_dr = rt::DeltaR(m_evt.lep2_p4, temp_bjets_p4.front());
        }

        // get the list of selected jets with lower pT theshold
        //vector<LorentzVector> temp_jets_p4 = tas::pfjets_p4();
        //vector<float>& temp_jets_csv = cms2.pfjets_combinedSecondaryVertexBJetTag();
		//vector<LorentzVector> temp_jets_p4  = samesign::getJets(hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt2>*/20.0, 1.0, m_jetMetScale); 
        //vector<float> temp_jets_csv;
        //SetBtagDiscriminator(temp_jets_p4, temp_jets_csv, JETS_BTAG_CSVM);
        
		vector<LorentzVector> temp_jets_p4 = m_evt.jets_p4;  
        vector<float> temp_jets_csv        = m_evt.jets_csv;

        // get the untagged jets
        vector<LorentzVector> temp_jets_nontagged_p4;
        for (size_t i = 0; i != temp_jets_p4.size(); i++)
        {
            //temp_jets_p4.at(i) *= evt_isRealData() ? cms2.pfjets_corL1FastL2L3residual().at(i) : cms2.pfjets_corL1FastL2L3().at(i);
            if (temp_jets_csv.at(i) < 0.679)
            {
                temp_jets_nontagged_p4.push_back(temp_jets_p4.at(i));
            }
        }

        if (!temp_jets_p4.empty())
        {
            // nearjet jet to the btags
            for (size_t i = 0; i != m_evt.bjets_p4.size(); i++)
            {
                const LorentzVector& p4 = m_evt.bjets_p4.at(i);
                if (temp_jets_nontagged_p4.empty()) 
                {
                    m_evt.bjets_nearjet_p4.push_back(LorentzVector(0,0,0,0));
                    m_evt.bjets_nearjet_dr.push_back(-999999.0);
                    continue;
                }
                std::sort(temp_jets_nontagged_p4.begin(), temp_jets_nontagged_p4.end(), at::SortByDeltaR<LorentzVector>(p4));
                m_evt.bjets_nearjet_p4.push_back(temp_jets_nontagged_p4.front());
                m_evt.bjets_nearjet_dr.push_back(rt::DeltaR(p4, temp_jets_nontagged_p4.front()));
            }

            // nearjet jet to the selected jet
            for (size_t i = 0; i != m_evt.jets_p4.size(); i++)
            {
                if (temp_jets_nontagged_p4.empty()) 
                {
                    m_evt.jets_nearjet_p4.push_back(LorentzVector(0,0,0,0));
                    m_evt.jets_nearjet_dr.push_back(-999999.0);
                    continue;
                }
                const LorentzVector& p4 = m_evt.jets_p4.at(i);
                std::sort(temp_jets_nontagged_p4.begin(), temp_jets_nontagged_p4.end(), at::SortByDeltaR<LorentzVector>(p4));

                // check if closest is the same jet?
                if (rt::DeltaR(temp_jets_nontagged_p4.front(), p4) < 0.0001)
                {
                    if (temp_jets_nontagged_p4.size()>=2)
                    {
                        m_evt.jets_nearjet_p4.push_back(temp_jets_nontagged_p4.at(1));
                        m_evt.jets_nearjet_dr.push_back(rt::DeltaR(p4, temp_jets_nontagged_p4.at(1)));
                    }
                    else // fill with dummy values
                    {
                        m_evt.jets_nearjet_p4.push_back(LorentzVector(0,0,0,0));
                        m_evt.jets_nearjet_dr.push_back(-999999.0);
                    }
                }
                else
                {
                    m_evt.jets_nearjet_p4.push_back(temp_jets_nontagged_p4.front());
                    m_evt.jets_nearjet_dr.push_back(rt::DeltaR(p4, temp_jets_nontagged_p4.front()));
                }
            }
            
            // nearest to lep1
            std::sort(temp_jets_p4.begin(), temp_jets_p4.end(), at::SortByDeltaR<LorentzVector>(m_evt.lep1_p4));
            m_evt.lep1_nearjet_p4 = temp_jets_p4.front();
            m_evt.lep1_nearjet_dr = rt::DeltaR(m_evt.lep1_p4, temp_jets_p4.front());

            // nearest to lep2
            std::sort(temp_jets_p4.begin(), temp_jets_p4.end(), at::SortByDeltaR<LorentzVector>(m_evt.lep2_p4));
            m_evt.lep2_nearjet_p4 = temp_jets_p4.front();
            m_evt.lep2_nearjet_dr = rt::DeltaR(m_evt.lep2_p4, temp_jets_p4.front());
        }

        if (m_verbose)
        {
            PrintJetInfo("pfjets"         , pfjets_p4()    , cms2.pfjets_combinedSecondaryVertexBJetTag() ); 
            PrintJetInfo("selected bjets" , m_evt.bjets_p4 , m_evt.bjets_nearjet_p4, m_evt.bjets_nearjet_dr, m_evt.bjets_csv); 
            PrintJetInfo("selected jets"  , m_evt.jets_p4  , m_evt.jets_nearjet_p4 , m_evt.jets_nearjet_dr , m_evt.jets_csv ); 
        }

        // Fill the tree
        m_tree->Fill();

        // printout
        if (dilepton_type==DILEPTON_MUMU)
        {
            if(m_verbose) {cout << "type == mm" << endl;}
            if(event_type==SS) m_count_nobtag_ss[0] += scale;
            if(event_type==SF) m_count_nobtag_sf[0] += scale;
            if(event_type==DF) m_count_nobtag_df[0] += scale;
            if(event_type==OS) m_count_nobtag_os[0] += scale;
            if(event_type==SS && m_evt.nbtags > 1) m_count_ss[0] += scale;
            if(event_type==SF && m_evt.nbtags > 1) m_count_sf[0] += scale;
            if(event_type==DF && m_evt.nbtags > 1) m_count_df[0] += scale;
            if(event_type==OS && m_evt.nbtags > 1) m_count_os[0] += scale;
        }
        if (dilepton_type==DILEPTON_EMU)
        {
            if(m_verbose) {cout << "type == em" << endl;}
            if(event_type==SS) m_count_nobtag_ss[1] += scale;
            if(event_type==SF) m_count_nobtag_sf[1] += scale;
            if(event_type==DF) m_count_nobtag_df[1] += scale;
            if(event_type==OS) m_count_nobtag_os[1] += scale;
            if(event_type==SS && m_evt.nbtags > 1) m_count_ss[1] += scale;
            if(event_type==SF && m_evt.nbtags > 1) m_count_sf[1] += scale;
            if(event_type==DF && m_evt.nbtags > 1) m_count_df[1] += scale;
            if(event_type==OS && m_evt.nbtags > 1) m_count_os[1] += scale;
        }
        if (dilepton_type==DILEPTON_EE)
        {
            if(m_verbose) {cout << "type == ee" << endl;}
            if(event_type==SS) m_count_nobtag_ss[2] += scale;
            if(event_type==SF) m_count_nobtag_sf[2] += scale;
            if(event_type==DF) m_count_nobtag_df[2] += scale;
            if(event_type==OS) m_count_nobtag_os[2] += scale;
            if(event_type==SS && m_evt.nbtags > 1) m_count_ss[2] += scale;
            if(event_type==SF && m_evt.nbtags > 1) m_count_sf[2] += scale;
            if(event_type==DF && m_evt.nbtags > 1) m_count_df[2] += scale;
            if(event_type==OS && m_evt.nbtags > 1) m_count_os[2] += scale;
        }
        // count all 
        {
            if(event_type==SS) m_count_nobtag_ss[3] += scale;
            if(event_type==SF) m_count_nobtag_sf[3] += scale;
            if(event_type==DF) m_count_nobtag_df[3] += scale;
            if(event_type==OS) m_count_nobtag_os[3] += scale;
            if(event_type==SS && m_evt.nbtags > 1) m_count_ss[3] += scale;
            if(event_type==SF && m_evt.nbtags > 1) m_count_sf[3] += scale;
            if(event_type==DF && m_evt.nbtags > 1) m_count_df[3] += scale;
            if(event_type==OS && m_evt.nbtags > 1) m_count_os[3] += scale;
        }

        PrintForSync(m_evt);

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

float SSAnalysisLooper::GetFakeRateValue(int lep_id, int lep_idx) const 
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
        float pt     = mus_p4().at(lep_idx).pt();
        float eta    = mus_p4().at(lep_idx).eta();
        float max_pt = h_mufr->GetYaxis()->GetXmax()-0.01;
        int pt_bin   = h_mufr->GetYaxis()->FindBin(min(pt, max_pt));
        int eta_bin  = h_mufr->GetXaxis()->FindBin(fabs(eta));
        return h_mufr->GetBinContent(eta_bin, pt_bin);
    }
    else if (abs(lep_id)==11) 
    {
        float pt     = els_p4().at(lep_idx).pt();
        float eta    = els_p4().at(lep_idx).eta();
        float max_pt = h_elfr->GetYaxis()->GetXmax()-0.01;
        int pt_bin   = h_elfr->GetYaxis()->FindBin(min(pt, max_pt));
        int eta_bin  = h_elfr->GetXaxis()->FindBin(fabs(eta));
        return h_elfr->GetBinContent(eta_bin, pt_bin);
    }
    return 0.0;
}

float SSAnalysisLooper::GetFlipRateValue(int lep_id, int lep_idx) const 
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

    float pt     = els_p4().at(lep_idx).pt();
    float eta    = els_p4().at(lep_idx).eta();
    float max_pt = h_flip->GetYaxis()->GetXmax()-0.01;
    int pt_bin   = h_flip->GetYaxis()->FindBin(min(pt, max_pt));
    int eta_bin  = h_flip->GetXaxis()->FindBin(fabs(eta));
    return h_flip->GetBinContent(eta_bin, pt_bin);
}


// Event struct definition
// --------------------------------------------------------------------------------------------------------- //

// construct:
EventInfo::EventInfo()
    : dataset          (            ) 
    , run              ( 0          ) 
    , ls               ( 0          ) 
    , evt              ( 0          ) 
    , scale            ( 1.0        ) 
    , scale1fb         ( 1.0        ) 
    , type             ( 999999     ) 
    , nvtxs            ( 999999     ) 
    , vtxw             ( 1.0        ) 
    , njets            ( 999999     ) 
    , njets20          ( 999999     ) 
    , njets30          ( 999999     ) 
    , nbtags           ( 999999     ) 
    , nbtags20         ( 999999     ) 
    , nbtags30         ( 999999     ) 
    , pfmet            ( -999999.0  ) 
    , ht               ( -999999.0  ) 
    , ht20             ( -999999.0  ) 
    , ht30             ( -999999.0  ) 
    , mass             ( -999999.0  ) 
    , mt               ( -999999.0  ) 
    , rho              ( -999999.0  )
    , trig_mm          ( false      )
    , trig_em          ( false      )
    , trig_ee          ( false      )
    , gen_sign         ( 0          ) 
    , gen_type         ( -999999    ) 
    , gen_ht           ( -999999.0  ) 
    , gen_met          ( -999999.0  ) 
    , gen_lep1_p4      ( 0, 0, 0, 0 ) 
    , gen_lep2_p4      ( 0, 0, 0, 0 ) 
    , gen_b1_p4        ( 0, 0, 0, 0 ) 
    , gen_b2_p4        ( 0, 0, 0, 0 ) 
    , gen_b3_p4        ( 0, 0, 0, 0 ) 
    , gen_b4_p4        ( 0, 0, 0, 0 ) 
    , lep1_p4          ( 0, 0, 0, 0 ) 
    , pt1              ( -999999.0  ) 
    , eta1             ( -999999.0  ) 
    , d01              ( -999999.0  ) 
    , z01              ( -999999.0  ) 
    , id1              ( -999999    ) 
    , q1               ( -999999    ) 
    , iso1             ( -999999.0  ) 
    , iso_ch_1         ( -999999.0  ) 
    , iso_nh_1         ( -999999.0  ) 
    , iso_em_1         ( -999999.0  ) 
    , aeff1            ( -999999.0  )
    , dbeta1           ( -999999.0  )
    , num1             ( false      ) 
    , fo1              ( false      ) 
    , wfr1             ( 0          ) 
    , wflip1           ( 0          ) 
    , leptru1          ( -99        ) 
    , lep1_nearbjet_p4 ( 0, 0, 0 ,0 ) 
    , lep1_nearjet_p4  ( 0, 0, 0 ,0 ) 
    , lep1_nearbjet_dr ( -999999.0  ) 
    , lep1_nearjet_dr  ( -999999.0  ) 
    , lep2_p4          ( 0, 0, 0 ,0 ) 
    , pt2              ( -999999.0  ) 
    , eta2             ( -999999.0  ) 
    , d02              ( -999999.0  ) 
    , z02              ( -999999.0  ) 
    , id2              ( -999999    ) 
    , q2               ( -999999    ) 
    , iso2             ( -999999.0  ) 
    , iso_ch_2         ( -999999.0  ) 
    , iso_nh_2         ( -999999.0  ) 
    , iso_em_2         ( -999999.0  ) 
    , aeff2            ( -999999.0  )
    , dbeta2           ( -999999.0  )
    , num2             ( false      ) 
    , fo2              ( false      ) 
    , wfr2             ( 0          ) 
    , wflip2           ( 0          ) 
    , leptru2          ( -99        ) 
    , lep2_nearbjet_p4 ( 0, 0, 0 ,0 ) 
    , lep2_nearjet_p4  ( 0, 0, 0 ,0 ) 
    , lep2_nearbjet_dr ( -999999.0  ) 
    , lep2_nearjet_dr  ( -999999.0  ) 
    , lep_dr           ( -999999.0  )
    , lep_deta         ( -999999.0  )
    , lep_dphi         ( -999999.0  )
    , qq               ( -999999    ) 
    , isSS             ( false      ) 
    , isSF             ( false      ) 
    , isDF             ( false      ) 
    , isOS             ( false      ) 
    , trig_eff         ( 1.0        )
    , scale_nbtag      ( 1.0        )
    , scale_nbtag3     ( 1.0        )
    , scale_unc_nbtag  ( 0.0        )
    , scale_unc_nbtag3 ( 0.0        )
    , scale_tap        ( 1.0        )
    , sparm0           ( 0.0        )
    , sparm1           ( 0.0        )
    , sparm2           ( 0.0        )
    , sparm3           ( 0.0        )
    , bjets_p4         (            )
    , bjets_nearjet_p4 (            )
    , bjets_nearjet_dr (            )
    , bjets_csv        (            )
    , jets_p4          (            )
    , jets_nearjet_p4  (            )
    , jets_nearjet_dr  (            )
    , jets_csv         (            )
{
    memset(dataset, '\0', 200);
}       

// methods:
void EventInfo::Reset()
{
    memset(dataset, '\0', 200);
    run              = 0;
    ls               = 0;
    evt              = 0;
    scale            = 1.0;
    scale1fb         = 1.0;
    type             = 999999;
    nvtxs            = 999999;
    vtxw             = 1.0;
    njets            = 999999;
    njets20          = 999999;
    njets30          = 999999;
    nbtags           = 999999;
    nbtags20         = 999999;
    nbtags30         = 999999;
    pfmet            = -999999.0;
    ht               = -999999.0;
    ht20             = -999999.0;
    ht30             = -999999.0;
    mass             = -999999.0;
    mt               = -999999.0;
    trig_mm          = false;
    trig_em          = false;
    trig_ee          = false;
    gen_sign         = 0;
    gen_type         = -999999;
    gen_ht           = -999999.0;
    gen_met          = -999999.0;
    rho              = -999999.0;
    pt1              = -999999.0;
    eta1             = -999999.0;
    d01              = -999999.0;
    z01              = -999999.0;
    id1              = -999999;
    q1               = -999999;
    iso1             = -999999.0;
    iso_ch_1         = -999990.0;
    iso_nh_1         = -999990.0;
    iso_em_1         = -999990.0;
    aeff1            = -999999.0;
    dbeta1           = -999999.0;
    num1             = false;
    fo1              = false;
    wfr1             = 0;
    wflip1           = 0;
    leptru1          = -999;
    lep1_nearbjet_dr = -999999.0;
    lep1_nearjet_dr  = -999999.0;
    pt2              = -999999.0;
    eta2             = -999999.0;
    d02              = -999999.0;
    z02              = -999999.0;
    id2              = -999999;
    q2               = -999999;
    iso2             = -999999.0;
    iso_ch_2         = -999990.0;
    iso_nh_2         = -999990.0;
    iso_em_2         = -999990.0;
    aeff2            = -999999.0;
    dbeta2           = -999999.0;
    num2             = false;
    fo2              = false;
    wfr2             = 0;
    wflip2           = 0;
    leptru2          = -999;
    lep2_nearbjet_dr = -999999.0;
    lep2_nearjet_dr  = -999999.0;
    lep_dr           = -999999.0;
    lep_deta         = -999999.0;
    lep_dphi         = -999999.0;
    qq               = -999999;
    isSS             = false;
    isSF             = false;
    isDF             = false;
    isOS             = false;
    trig_eff         = 1.0;
    scale_nbtag      = 1.0;
    scale_nbtag3     = 1.0;
    scale_unc_nbtag  = 1.0;
    scale_unc_nbtag3 = 1.0;
    scale_tap        = 1.0;
    sparm0           = 0.0;
    sparm1           = 0.0;
    sparm2           = 0.0;
    sparm3           = 0.0;
    bjets_dr12       = -999999.0;
    jets_dr12        = -999999.0;

    gen_lep1_p4.SetPxPyPzE(0, 0, 0, 0 ); 
    gen_lep2_p4.SetPxPyPzE(0, 0, 0, 0 );
    gen_b1_p4.SetPxPyPzE(0, 0, 0, 0 );
    gen_b2_p4.SetPxPyPzE(0, 0, 0, 0 );
    gen_b3_p4.SetPxPyPzE(0, 0, 0, 0 );
    gen_b4_p4.SetPxPyPzE(0, 0, 0, 0 );
    lep1_p4.SetPxPyPzE(0, 0, 0 ,0);  
    lep2_p4.SetPxPyPzE(0, 0, 0 ,0);  
    lep1_nearbjet_p4.SetPxPyPzE(0, 0, 0 ,0);  
    lep2_nearbjet_p4.SetPxPyPzE(0, 0, 0 ,0);  
    lep1_nearjet_p4.SetPxPyPzE(0, 0, 0 ,0);  
    lep2_nearjet_p4.SetPxPyPzE(0, 0, 0 ,0);  

    bjets_p4.clear();
    bjets_nearjet_p4.clear();
    bjets_nearjet_dr.clear();
    bjets_csv.clear();

    jets_p4.clear();
    jets_nearjet_p4.clear();
    jets_nearjet_dr.clear();
    jets_csv.clear();
};


// initialize branches
void EventInfo::SetBranches(TTree* tree)
{
    // protection for NULL pointer
    if (!tree)
    {
        std::cout << "Warning: EventInfo::SetBranches: tree is NULL.  No branches set. " << std::endl;
        return;
    }

    // built in types
    tree->Branch("dataset"         , &dataset         , "dataset[200]/C"     );
    tree->Branch("run"             , &run             , "run/i"              );
    tree->Branch("ls"              , &ls              , "ls/i"               );
    tree->Branch("evt"             , &evt             , "evt/i"              );
    tree->Branch("scale"           , &scale           , "scale/F"            );
    tree->Branch("scale1fb"        , &scale1fb        , "scale1fb/F"         );
    tree->Branch("type"            , &type            , "type/i"             );
    tree->Branch("nvtxs"           , &nvtxs           , "nvtxs/i"            );
    tree->Branch("vtxw"            , &vtxw            , "vtxw/F"             );
    tree->Branch("njets"           , &njets           , "njets/i"            );
    tree->Branch("njets20"         , &njets20         , "njets20/i"          );
    tree->Branch("njets30"         , &njets30         , "njets30/i"          );
    tree->Branch("nbtags"          , &nbtags          , "nbtags/i"           );
    tree->Branch("nbtags20"        , &nbtags20        , "nbtags20/i"         );
    tree->Branch("nbtags30"        , &nbtags30        , "nbtags30/i"         );
    tree->Branch("pfmet"           , &pfmet           , "pfmet/F"            );
    tree->Branch("ht"              , &ht              , "ht/F"               );
    tree->Branch("ht20"            , &ht20            , "ht20/F"             );
    tree->Branch("ht30"            , &ht30            , "ht30/F"             );
    tree->Branch("mass"            , &mass            , "mass/F"             );
    tree->Branch("mt"              , &mt              , "mt/F"               );
    tree->Branch("trig_mm"         , &trig_mm         , "trig_mm/O"          );
    tree->Branch("trig_em"         , &trig_em         , "trig_em/O"          );
    tree->Branch("trig_ee"         , &trig_ee         , "trig_ee/O"          );
    tree->Branch("gen_sign"        , &gen_sign        , "gen_sign/I"         );
    tree->Branch("gen_type"        , &gen_type        , "gen_type/I"         );
    tree->Branch("gen_ht"          , &gen_ht          , "gen_ht/F"           );
    tree->Branch("gen_met"         , &gen_met         , "gen_met/F"          );
    tree->Branch("rho"             , &rho             , "rho/F"              );
    tree->Branch("pt1"             , &pt1             , "pt1/F"              );
    tree->Branch("eta1"            , &eta1            , "eta1/F"             );
    tree->Branch("d01"             , &d01             , "d01/F"              );
    tree->Branch("z01"             , &z01             , "z01/F"              );
    tree->Branch("id1"             , &id1             , "id1/I"              );
    tree->Branch("q1"              , &q1              , "q1/I"               );
    tree->Branch("iso1"            , &iso1            , "iso1/F"             );
    tree->Branch("iso_ch_1"        , &iso_ch_1        , "iso_ch_1/F"         );
    tree->Branch("iso_em_1"        , &iso_em_1        , "iso_em_1/F"         );
    tree->Branch("iso_nh_1"        , &iso_nh_1        , "iso_nh_1/F"         );
    tree->Branch("aeff1"           , &aeff1           , "aeff1/F"            );
    tree->Branch("dbeta1"          , &dbeta1          , "dbeta1/F"           );
    tree->Branch("num1"            , &num1            , "num1/O"             );
    tree->Branch("fo1"             , &fo1             , "fo1/O"              );
    tree->Branch("wfr1"            , &wfr1            , "wfr1/F"             );
    tree->Branch("wflip1"          , &wflip1          , "wflip1/F"           );
    tree->Branch("leptru1"         , &leptru1         , "leptru1/I"          );
    tree->Branch("pt2"             , &pt2             , "pt2/F"              );
    tree->Branch("eta2"            , &eta2            , "eta2/F"             );
    tree->Branch("d02"             , &d02             , "d02/F"              );
    tree->Branch("z02"             , &z02             , "z02/F"              );
    tree->Branch("iso2"            , &iso2            , "iso2/F"             );
    tree->Branch("iso_ch_2"        , &iso_ch_2        , "iso_ch_2/F"         );
    tree->Branch("iso_em_2"        , &iso_em_2        , "iso_em_2/F"         );
    tree->Branch("iso_nh_2"        , &iso_nh_2        , "iso_nh_2/F"         );
    tree->Branch("aeff2"           , &aeff2           , "aeff2/I"            );
    tree->Branch("dbeta2"          , &dbeta2          , "dbeta2/F"           );
    tree->Branch("num2"            , &num2            , "num2/O"             );
    tree->Branch("fo2"             , &fo2             , "fo2/O"              );
    tree->Branch("id2"             , &id2             , "id2/I"              );
    tree->Branch("q2"              , &q2              , "q2/I"               );
    tree->Branch("wfr2"            , &wfr2            , "wfr2/F"             );
    tree->Branch("wflip2"          , &wflip2          , "wflip2/F"           );
    tree->Branch("leptru2"         , &leptru2         , "leptru2/I"          );
    tree->Branch("lep_dr"          , &lep_dr          , "lep_dr/F"           );
    tree->Branch("lep_deta"        , &lep_deta        , "lep_deta/F"         );
    tree->Branch("lep_dphi"        , &lep_dphi        , "lep_dphi/F"         );
    tree->Branch("qq"              , &qq              , "qq/I"               );
    tree->Branch("isSS"            , &isSS            , "isSS/O"             );
    tree->Branch("isSF"            , &isSF            , "isSF/O"             );
    tree->Branch("isDF"            , &isDF            , "isDF/O"             );
    tree->Branch("isOS"            , &isOS            , "isOS/O"             );
    tree->Branch("trig_eff"        , &trig_eff        , "trig_eff/F"         );
    tree->Branch("scale_nbtag"     , &scale_nbtag     , "scale_nbtag/F"      );
    tree->Branch("scale_nbtag3"    , &scale_nbtag3    , "scale_nbtag3/F"     );
    tree->Branch("scale_unc_nbtag" , &scale_unc_nbtag , "scale_unc_nbtag/F"  );
    tree->Branch("scale_unc_nbtag3", &scale_unc_nbtag3, "scale_unc_nbtag3/F" );
    tree->Branch("scale_tap"       , &scale_tap       , "scale_tap/F"        );
    tree->Branch("sparm0"          , &sparm0          , "sparm0/F"           );
    tree->Branch("sparm1"          , &sparm1          , "sparm1/F"           );
    tree->Branch("sparm2"          , &sparm2          , "sparm2/F"           );
    tree->Branch("sparm3"          , &sparm3          , "sparm3/F"           );
    tree->Branch("bjets_dr12"      , &bjets_dr12      , "bjets_dr12/F"       );
    tree->Branch("jets_dr12"       , &jets_dr12       , "jets_dr12/F"        );
    tree->Branch("lep1_nearbjet_dr", &lep1_nearbjet_dr, "lep1_nearbjet_dr/F" ); 
    tree->Branch("lep1_nearjet_dr" , &lep1_nearjet_dr , "lep1_nearjet_dr/F"  ); 
    tree->Branch("lep2_nearbjet_dr", &lep2_nearbjet_dr, "lep2_nearbjet_dr/F" ); 
    tree->Branch("lep2_nearjet_dr" , &lep2_nearjet_dr , "lep2_nearjet_dr/F"  ); 

    // class types
    tree->Branch("gen_lep1_p4"      , "LorentzVector" , &gen_lep1_p4      ); 
    tree->Branch("gen_lep2_p4"      , "LorentzVector" , &gen_lep2_p4      ); 
    tree->Branch("gen_b1_p4"        , "LorentzVector" , &gen_b1_p4        ); 
    tree->Branch("gen_b2_p4"        , "LorentzVector" , &gen_b2_p4        ); 
    tree->Branch("gen_b3_p4"        , "LorentzVector" , &gen_b3_p4        ); 
    tree->Branch("gen_b4_p4"        , "LorentzVector" , &gen_b4_p4        ); 
    tree->Branch("lep1_p4"          , "LorentzVector" , &lep1_p4          ); 
    tree->Branch("lep2_p4"          , "LorentzVector" , &lep2_p4          ); 
    tree->Branch("lep1_nearbjet_p4" , "LorentzVector" , &lep1_nearbjet_p4 ); 
    tree->Branch("lep2_nearbjet_p4" , "LorentzVector" , &lep2_nearbjet_p4 ); 
    tree->Branch("lep1_nearjet_p4"  , "LorentzVector" , &lep1_nearjet_p4  ); 
    tree->Branch("lep2_nearjet_p4"  , "LorentzVector" , &lep2_nearjet_p4  ); 

    tree->Branch("bjets_p4"         , "vecLorentzVector" , &bjets_p4         ); 
    tree->Branch("bjets_nearjet_p4" , "vecLorentzVector" , &bjets_nearjet_p4 ); 
    tree->Branch("bjets_nearjet_dr" , "vector<float>"    , &bjets_nearjet_dr ); 
    tree->Branch("bjets_csv"        , "vector<float>"    , &bjets_csv        ); 

    tree->Branch("jets_p4"         , "vecLorentzVector" , &jets_p4         ); 
    tree->Branch("jets_nearjet_p4" , "vecLorentzVector" , &jets_nearjet_p4 ); 
    tree->Branch("jets_nearjet_dr" , "vector<float>"    , &jets_nearjet_dr ); 
    tree->Branch("jets_csv"        , "vector<float>"    , &jets_csv        ); 
}
