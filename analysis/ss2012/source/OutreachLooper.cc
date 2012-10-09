#include "OutreachLooper.h"

// c++
#include <stdexcept>
#include <algorithm>
#include <fstream>

// cms2
#include "CMS2.h"
#include "ssSelections.h"
#include "eventSelections.h"
#include "mcSelections.h"
#include "muonSelections.h"
#include "ssSelections.h"
//#include "trackSelections.h"
//#include "susySelections.h"
#include "mcbtagSFuncert.h"
//#include "electronSelections.h"

// Tools
#include "at/Predicates.h"
#include "at/DileptonHypType.h"
#include "at/DileptonChargeType.h"
#include "at/VtxReweight.h"
#include "rt/RootTools.h"
#include "GenParticleStruct.h"
#include "EfficiencyModelTools.h"
#include "ScaleFactors.h"

// ROOT
#include "Math/LorentzVector.h"

// typdefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef std::vector<LorentzVector> vecLorentzVector;

using namespace tas;
using namespace std;
using namespace efftools;
using namespace at;

// helper functions 
// ------------------------------------------------------------------------------------------------ //

// get the best hyp
void CompareHyps(std::pair<size_t, DileptonChargeType::value_type>& best_hyp, size_t hyp_idx, const DileptonChargeType::value_type& new_type)
{
    short current_type = best_hyp.second;
    float new_pt       = hyp_lt_p4().at(hyp_idx).pt() + hyp_ll_p4().at(hyp_idx).pt();
    float current_pt   = hyp_lt_p4().at(best_hyp.first).pt() + hyp_ll_p4().at(best_hyp.first).pt();

    if (current_type == DileptonChargeType::static_size)
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
            
vector<bool> MatchedGenJets(const vector<LorentzVector>& reco_vjets_p4, const vector<LorentzVector>& gen_vjets_p4)
{
    vector<bool> matched;
    for (size_t gidx = 0; gidx != gen_vjets_p4.size(); gidx++)
    {
        const LorentzVector gen_jet_p4 =  gen_vjets_p4.at(gidx);
        vector<LorentzVector> temp_reco_vjets_p4(reco_vjets_p4);
        if (not temp_reco_vjets_p4.empty())
        {
            std::sort(temp_reco_vjets_p4.begin(), temp_reco_vjets_p4.end(), SortByDeltaR<LorentzVector>(gen_jet_p4));
            const LorentzVector reco_jet_p4 = temp_reco_vjets_p4.front();
            float dr = rt::DeltaR(reco_jet_p4, gen_jet_p4);
            if (dr < 0.4)
            {
                matched.push_back(true);
                continue;
            }
        }
        matched.push_back(false);
    }
    return matched;
}

vector<bool> MatchedGenBjets(const vector<LorentzVector>& reco_vbjets_p4, const vector<LorentzVector>& gen_vbjets_p4)
{
    vector<bool> matched;
    for (size_t gidx = 0; gidx != gen_vbjets_p4.size(); gidx++)
    {
        const LorentzVector gen_jet_p4 =  gen_vbjets_p4.at(gidx);
        vector<LorentzVector> temp_reco_vbjets_p4(reco_vbjets_p4);
        if (not temp_reco_vbjets_p4.empty())
        {
            std::sort(temp_reco_vbjets_p4.begin(), temp_reco_vbjets_p4.end(), SortByDeltaR<LorentzVector>(gen_jet_p4));
            const LorentzVector reco_jet_p4 = temp_reco_vbjets_p4.front();
            float dr = rt::DeltaR(reco_jet_p4, gen_jet_p4);
            if (dr < 0.4)
            {
                matched.push_back(true);
                continue;
            }
        }
        matched.push_back(false);
    }
    return matched;
}

// outreach looper implementation
// ------------------------------------------------------------------------------------------------ //

// construct:
OutreachLooper::OutreachLooper
(
    const std::string& root_file_name,
    const Sample::value_type& sample,
    double luminosity,
    const std::string& vtxreweight_file_name,
    bool is_fastsim,
    bool sparms,
    bool verbose
)
    : AnalysisWithTree(root_file_name, "tree", "baby tree for SS2012 outreach")
    , m_sample(sample)
    , m_lumi(luminosity)
    , m_verbose(verbose)
    , m_is_fastsim(is_fastsim)
    , m_sparms(sparms)
{
    // set vertex weight file
    if (!vtxreweight_file_name.empty())
    {
        cout << "using vertex reweight file : " << vtxreweight_file_name << endl;
        set_vtxreweight_rootfile(vtxreweight_file_name.c_str(), m_verbose);
    }

    // begin job
    BeginJob();
}

// destroy:
OutreachLooper::~OutreachLooper()
{
    EndJob();
}

// function operator: operate on each event
int OutreachLooper::operator() (long event)
{
    // call base class operator
    return Analyze(event);
}

// members:
void OutreachLooper::BeginJob()
{
    // initialize branches
    m_evt.SetBranches(*m_tree);
    m_evt.Reset();
}

void OutreachLooper::EndJob()
{
}


int OutreachLooper::Analyze(long event)
{
    try
    {
        // Reset Tree Variables
        // --------------------------------------------------------------------------------------------------------- //

        m_evt.Reset();

        // basic selection
        // --------------------------------------------------------------------------------------------------------- //

        // Gen hypothesis
        std::pair<GenParticleStruct, GenParticleStruct> best_gen_hyp = getGenHyp(20.0, 20.0, DileptonChargeType::static_size);
        if (best_gen_hyp.first.id_ == 0 || best_gen_hyp.second.id_ == 0)
        {
            if (m_verbose) {cout << "OutreachLooper: does not have a good gen hyp" << endl;} 

            // Fill the tree (to preserve the number of events)
            // m_tree->Fill();

            // skip the rest of the event
            return 0;
        }

        // basic selection
        // --------------------------------------------------------------------------------------------------------- //

        // fill common
        m_evt.event_info.FillCommon(m_sample);

        // vertex re-weighting
        m_evt.nvtxs = numberOfGoodVertices(); 
        m_evt.vtxw  = 1.0; 
        //m_evt.vtxw  = evt_isRealData() ? 1.0 : vtxweight_n(m_evt.nvtxs, evt_isRealData(), false);

        // lepton variables
        int   id1  = abs(best_gen_hyp.first.id_ ) == 15 ? best_gen_hyp.first.did_   : best_gen_hyp.first.id_;
        int   idx1 = abs(best_gen_hyp.first.id_ ) == 15 ? best_gen_hyp.first.didx_  : best_gen_hyp.first.idx_;
        int   id2  = abs(best_gen_hyp.second.id_) == 15 ? best_gen_hyp.second.did_  : best_gen_hyp.second.id_;
        int   idx2 = abs(best_gen_hyp.second.id_) == 15 ? best_gen_hyp.second.didx_ : best_gen_hyp.second.idx_;

        // get gen LorenzVectors
        LorentzVector p41 = genps_p4().at(idx1);
        LorentzVector p42 = genps_p4().at(idx2);

        // gen lep type
        m_evt.gen_dilep_type = getHypType(id1, id2);

        // is os/ss
        m_evt.gen_is_ss = (id1 * id2 > 0);
        m_evt.gen_is_os = (id1 * id2 < 0);

        // sparms parameters
        if (m_sparms) 
        {
            int n_sparms = sparm_values().size();
            if (n_sparms > 0) m_evt.sparm0 = sparm_values().at(0);
            if (n_sparms > 1) m_evt.sparm1 = sparm_values().at(1);
            if (n_sparms > 2) m_evt.sparm2 = sparm_values().at(2);
            if (n_sparms > 3) m_evt.sparm3 = sparm_values().at(3);
        }

        // HT
        m_evt.gen_ht = getGenHT(40, 2.4);
        std::vector<unsigned int> indexJets = getRecoJets(best_gen_hyp.first, best_gen_hyp.second);

        // Now take care of gen b-jets 
        m_evt.gen_vbjets_p4 = getGenBjets(40.0, 2.4);
        m_evt.gen_nbtags    = m_evt.gen_vbjets_p4.size();

        // Now take care of gen jets
        m_evt.gen_vjets_p4 = getGenJets(40.0, 2.4);
        m_evt.gen_njets    = m_evt.gen_vbjets_p4.size(); 

        // leptons
        // --------------------------------------------------------------------------------------------------------- //

        // lep1
        m_evt.lep1_gen_p4    = p41;
        m_evt.lep1_gen_pdgid = id1;
        m_evt.lep1_from_tau  = abs(best_gen_hyp.first.id_) == 15;

        // lep2
        m_evt.lep2_gen_p4    = p42;
        m_evt.lep2_gen_pdgid = id2;
        m_evt.lep2_from_tau  = abs(best_gen_hyp.second.id_ ) == 15;


        // reco info
        // --------------------------------------------------------------------------------------------------------- //

        // jet type
        JetType jet_type = evt_isRealData() ? JETS_TYPE_PF_FAST_CORR_RESIDUAL : JETS_TYPE_PF_FAST_CORR;

        // loop over hypotheses
        pair<size_t, DileptonChargeType::value_type> best_hyp(0, DileptonChargeType::static_size);
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

            // check extra Z veto
            if (samesign::makesExtraZ(ihyp))
            {
                if (m_verbose) {std::cout << "fails btag extra Z veto requirement" << std::endl;}
                continue;
            }

            // check extra Gamma* veto
            if (samesign::makesExtraGammaStar(ihyp))
            {
                if (m_verbose) {std::cout << "fails btag extra Gamma* veto requirement" << std::endl;}
                continue;
            }

            // skip if both are not numerators
            if (!samesign::isDenominatorLepton(lt_id, lt_idx) || !samesign::isDenominatorLepton(ll_id, ll_idx))
            {
                if (m_verbose) {std::cout << "fails both leptons are at least denominator requirement" << std::endl;}
                continue;
            }

            // OS (Here a kludge by Claudio to quickly change the meaning of SS and OS .... useful for ttbar as sstop)
            int dummy = 1;
            int hyp_q = dummy * hyp_lt_charge().at(ihyp) * hyp_ll_charge().at(ihyp);
            if (hyp_q < 0)
            {
                if (!samesign::isNumeratorHypothesis(ihyp))
                {
                    if (m_verbose) {std::cout << "OS hyp doesn't pass ID/ISO requirement" << std::endl;}
                    continue; 
                }
                CompareHyps(best_hyp, ihyp, DileptonChargeType::OS);
            }
            // SS 
            else if (hyp_q > 0)
            {
                // same sign event (SS)
                if (samesign::isNumeratorHypothesis(ihyp))
                {
                    CompareHyps(best_hyp, ihyp, DileptonChargeType::SS);
                }
                // single fake event (SF)
                else if (samesign::isNumeratorLepton(lt_id, lt_idx) || samesign::isNumeratorLepton(ll_id, ll_idx))
                {
                    CompareHyps(best_hyp, ihyp, DileptonChargeType::SF);
                }
                // double fake event (DF)
                else
                {
                    CompareHyps(best_hyp, ihyp, DileptonChargeType::DF);
                }
            }

        } // end looper over hypothesis

        // Set Tree Variables
        // --------------------------------------------------------------------------------------------------------- //

        // best hyp index
        unsigned int hyp_idx = best_hyp.first;
        DileptonChargeType::value_type event_type = best_hyp.second;

        // all: 0, mm: 1, em: 2, ee: 3
        m_evt.dilep_type = hyp_p4().empty() ? DileptonHypType::static_size : hyp_typeToHypType(hyp_type().at(hyp_idx));

        // We don't have a good hypothesis selected 
        if (event_type == DileptonChargeType::static_size)
        {
            if (m_verbose) {std::cout << "fails good event type requirement" << std::endl;}

            // event variables
            std::vector<unsigned int> indexJets = getRecoJets(best_gen_hyp.first, best_gen_hyp.second);
            m_evt.reco_ht                       = getHT(indexJets);

            // Now take care of b-tagging
            for (size_t bidx = 0; bidx < m_evt.gen_vbjets_p4.size(); bidx++) 
            {
                int index = getRecoJet(m_evt.gen_vbjets_p4.at(bidx));
                if (index < 0)
                {
                    m_evt.gen_vbjets_matched.push_back(false);
                    continue;
                }

                if (cms2.pfjets_combinedSecondaryVertexBJetTag().at(index) > 0.679)
                {
                    m_evt.reco_vbjets_p4.push_back(pfjets_p4().at(bidx));
                    m_evt.gen_vbjets_matched.push_back(true);
                }
                else
                {
                    m_evt.gen_vbjets_matched.push_back(false);
                }
            }
            m_evt.reco_nbtags = m_evt.reco_vbjets_p4.size();

            // Now take care of jets
            for (size_t jidx = 0; jidx < m_evt.gen_vjets_p4.size(); jidx++) 
            {
                int index = getRecoJet(m_evt.gen_vjets_p4.at(jidx));
                if (index < 0)
                {
                    m_evt.gen_vjets_matched.push_back(false);
                    continue;
                }

                if (pfjets_p4().at(index).pt() > 40.0 && fabs(pfjets_p4().at(index).eta()) < 2.4)
                {
                    m_evt.reco_vjets_p4.push_back(pfjets_p4().at(jidx));
                    m_evt.gen_vjets_matched.push_back(true);
                }
                else
                {
                    m_evt.gen_vjets_matched.push_back(false);
                }
            }
            m_evt.reco_njets = m_evt.reco_vjets_p4.size();

            // the rest of the reco variables are set to the bobus default values
        }
        else
        {
            if (m_verbose) {std::cout << "passes good event type requirement" << std::endl;}

            // event variables
            m_evt.reco_ht        = samesign::sumJetPt(hyp_idx, jet_type,                      /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, 0);
            m_evt.reco_njets     = samesign::nJets(hyp_idx, jet_type,                         /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt2>*/20.0, 1.0, 0);
            m_evt.reco_nbtags    = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM,  /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, 0);
            m_evt.reco_vbjets_p4 = samesign::getBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, 0); 
            m_evt.reco_vjets_p4  = samesign::getJets(hyp_idx, jet_type,                       /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt2>*/20.0, 1.0, 0); 

            m_evt.gen_vjets_matched  = MatchedGenJets(m_evt.reco_vjets_p4, m_evt.gen_vjets_p4);
            m_evt.gen_vbjets_matched = MatchedGenBjets(m_evt.reco_vbjets_p4, m_evt.gen_vbjets_p4);

            // leptons variables
            const LorentzVector& lt_p4 = hyp_lt_p4().at(hyp_idx);
            const LorentzVector& ll_p4 = hyp_ll_p4().at(hyp_idx);
            int lt_id                  = hyp_lt_id().at(hyp_idx);
            int ll_id                  = hyp_ll_id().at(hyp_idx);
            int lt_idx                 = hyp_lt_index().at(hyp_idx);
            int ll_idx                 = hyp_ll_index().at(hyp_idx);

            m_evt.lep1_pdgid      = lt_id; 
            m_evt.lep1_p4         = lt_p4; 
            m_evt.lep1_passes_id  = samesign::isGoodLepton(lt_id, lt_idx);
            m_evt.lep1_passes_iso = samesign::isIsolatedLepton(lt_id, lt_idx);
            m_evt.lep1_num        = samesign::isNumeratorLepton(lt_id, lt_idx);
            m_evt.lep1_iso        = (abs(lt_id)==11) ? samesign::electronIsolationPF2012(lt_idx) : muonIsoValuePF2012_deltaBeta(lt_idx);

            m_evt.lep2_pdgid      = ll_id; 
            m_evt.lep2_p4         = ll_p4; 
            m_evt.lep2_passes_id  = samesign::isGoodLepton(ll_id, ll_idx);
            m_evt.lep2_passes_iso = samesign::isIsolatedLepton(ll_id, ll_idx);
            m_evt.lep2_num        = samesign::isNumeratorLepton(ll_id, ll_idx);
            m_evt.lep2_iso        = (abs(ll_id)==11) ? samesign::electronIsolationPF2012(ll_idx) : muonIsoValuePF2012_deltaBeta(ll_idx);

            // determine if matched to gen
            int matched_gen_lep1_idx = getRecoLepton(best_gen_hyp.first).second;
            int matched_gen_lep2_idx = getRecoLepton(best_gen_hyp.second).second;

            m_evt.lep1_matched = (matched_gen_lep1_idx == lt_idx || matched_gen_lep2_idx == lt_idx);
            m_evt.lep2_matched = (matched_gen_lep1_idx == ll_idx || matched_gen_lep2_idx == ll_idx);

            // classification
            m_evt.reco_is_ss = (event_type==DileptonChargeType::SS);
            m_evt.reco_is_os = (event_type==DileptonChargeType::OS);
        }

        m_evt.reco_met       = evt_pfmet_type1cor();   

        // scale factors
        // --------------------------------------------------------------------------------------------------------- //

        m_evt.sf_dileptrig = dilepTriggerScaleFactor(m_evt.dilep_type);
        m_evt.sf_lepeff    = 1.0; 

        // scale factor for # btags 
        m_evt.sf_nbtag  = 0.0;
        m_evt.sf_nbtag3 = 0.0;
        vector<LorentzVector> bjets(m_evt.reco_vbjets_p4); 
        //vector<LorentzVector> bjets = samesign::getBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, 0);
        std::sort(bjets.begin(), bjets.end(), SortByPt<LorentzVector>());
        if (bjets.size() == 2) 
        {
            m_evt.sf_nbtag = btagEventWeight(2, bjets.at(0).pt(), bjets.at(1).pt(), 0., 0., m_is_fastsim);
        }
        else if (bjets.size() == 3) 
        {
            m_evt.sf_nbtag  = btagEventWeight (3, bjets.at(0).pt(), bjets.at(1).pt(), bjets.at(2).pt(), 0., m_is_fastsim);
            m_evt.sf_nbtag3 = btagEventWeight3(3, bjets.at(0).pt(), bjets.at(1).pt(), bjets.at(2).pt(), 0., m_is_fastsim);
        }
        else if (bjets.size() > 3) 
        {
            m_evt.sf_nbtag  = btagEventWeight (4, bjets.at(0).pt(), bjets.at(1).pt(), bjets.at(2).pt(), bjets.at(3).pt(), m_is_fastsim);
            m_evt.sf_nbtag3 = btagEventWeight3(4, bjets.at(0).pt(), bjets.at(1).pt(), bjets.at(2).pt(), bjets.at(3).pt(), m_is_fastsim);
        }

        // done
        // --------------------------------------------------------------------------------------------------------- //

        // Fill the tree
        m_tree->Fill();
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


// OutreachTree 
// --------------------------------------------------------------------------------------------------------- //

OutreachTree::OutreachTree()
{
    event_info.Reset();
    Reset();
}

void OutreachTree::Reset()
{
    event_info.Reset();

    gen_dilep_type  = at::DileptonHypType::static_size;
    gen_ht          = -99999.0;
    gen_nbtags      = -999999;
    gen_njets       = -999999;
    gen_is_ss       = false;
    gen_is_os       = false;
    dilep_type      = at::DileptonHypType::static_size;
    reco_ht         = -999999.0;
    reco_met        = -999999.0;
    reco_nbtags     = -999999;
    reco_njets      = -999999;
    reco_is_ss      = false;
    reco_is_os      = false;
    sf_dileptrig    = 1.0;
    sf_lepeff       = 1.0;
    sf_nbtag        = 1.0;
    sf_nbtag3       = 1.0;
    sparm0          = -999999.0;
    sparm1          = -999999.0;
    sparm2          = -999999.0;
    sparm3          = -999999.0;
    lep1_gen_pdgid  = -999999;
    lep1_pdgid      = -999999;
    lep1_matched    = false;
    lep1_from_tau   = false;
    lep1_passes_id  = false;
    lep1_passes_iso = - false;
    lep1_num        = false;
    lep1_iso        = -999999.0;
    lep2_pdgid      = -999999;
    lep2_gen_pdgid  = -999999;
    lep2_matched    = false;
    lep2_from_tau   = false;
    lep2_passes_id  = false;
    lep2_passes_iso = false;
    lep2_num        = false;
    lep2_iso        = -999999.0;

    // lorentz vectors
    gen_vbjets_p4.clear();
    gen_vbjets_matched.clear();
    gen_vjets_p4.clear();
    gen_vjets_matched.clear();
    reco_vbjets_p4.clear();
    reco_vjets_p4.clear();
    lep1_p4.SetXYZT(0,0,0,0);
    lep1_gen_p4.SetXYZT(0,0,0,0);
    lep2_p4.SetXYZT(0,0,0,0);
    lep2_gen_p4.SetXYZT(0,0,0,0);
}

void OutreachTree::SetBranches(TTree &tree)
{
    event_info.SetBranches(tree);

    // reco event level
    tree.Branch("gen_dilep_type"  , &gen_dilep_type    , "gen_dilep_type/I"  ); 
    tree.Branch("gen_ht"          , &gen_ht            , "gen_ht/F"          ); 
    tree.Branch("gen_nbtags"      , &gen_nbtags        , "gen_nbtags/I"      ); 
    tree.Branch("gen_njets"       , &gen_njets         , "gen_njets/I"       ); 
    tree.Branch("gen_is_ss"       , &gen_is_ss         , "gen_is_ss/O"       ); 
    tree.Branch("gen_is_os"       , &gen_is_os         , "gen_is_os/O"       ); 
    tree.Branch("dilep_type"      , &dilep_type        , "dilep_type/I"      ); 
    tree.Branch("reco_ht"         , &reco_ht           , "reco_ht/F"         ); 
    tree.Branch("reco_met"        , &reco_met          , "reco_met/F"        ); 
    tree.Branch("reco_nbtags"     , &reco_nbtags       , "reco_nbtags/I"     ); 
    tree.Branch("reco_njets"      , &reco_njets        , "reco_njets/I"      ); 
    tree.Branch("reco_is_ss"      , &reco_is_ss        , "reco_is_ss/F"      ); 
    tree.Branch("reco_is_os"      , &reco_is_os        , "reco_is_os/F"      ); 
    tree.Branch("sf_dileptrig"    , &sf_dileptrig      , "sf_dileptrig/F"    ); 
    tree.Branch("sf_lepeff"       , &sf_lepeff         , "sf_lepeff/F"       ); 
    tree.Branch("sf_nbtag"        , &sf_nbtag          , "sf_nbtag/F"        ); 
    tree.Branch("sf_nbtag3"       , &sf_nbtag3         , "sf_nbtag3/F"       ); 
    tree.Branch("sparm0"          , &sparm0            , "sparm0/F"          ); 
    tree.Branch("sparm1"          , &sparm1            , "sparm1/F"          ); 
    tree.Branch("sparm2"          , &sparm2            , "sparm2/F"          ); 
    tree.Branch("sparm3"          , &sparm3            , "sparm3/F"          ); 
    tree.Branch("lep1_gen_pdgid"  , &lep1_gen_pdgid    , "lep1_gen_pdgid/I"  ); 
    tree.Branch("lep1_pdgid"      , &lep1_pdgid        , "lep1_pdgid/I"      ); 
    tree.Branch("lep1_matched"    , &lep1_matched      , "lep1_matched/O"    ); 
    tree.Branch("lep1_from_tau"   , &lep1_from_tau     , "lep1_from_tau/O"   ); 
    tree.Branch("lep1_passes_id"  , &lep1_passes_id    , "lep1_passes_id/O"  ); 
    tree.Branch("lep1_passes_iso" , &lep1_passes_iso   , "lep1_passes_iso/O" ); 
    tree.Branch("lep1_num"        , &lep1_num          , "lep1_num/O"        ); 
    tree.Branch("lep1_iso"        , &lep1_iso          , "lep1_iso/F"        ); 
    tree.Branch("lep2_pdgid"      , &lep2_pdgid        , "lep2_pdgid/I"      ); 
    tree.Branch("lep2_gen_pdgid"  , &lep2_gen_pdgid    , "lep2_gen_pdgid/I"  ); 
    tree.Branch("lep2_matched"    , &lep2_matched      , "lep2_matched/O"    ); 
    tree.Branch("lep2_from_tau"   , &lep2_from_tau     , "lep2_from_tau/O"   ); 
    tree.Branch("lep2_passes_id"  , &lep2_passes_id    , "lep2_passes_id/O"  ); 
    tree.Branch("lep2_passes_iso" , &lep2_passes_iso   , "lep2_passes_iso/O" ); 
    tree.Branch("lep2_num"        , &lep2_num          , "lep2_num/O"        ); 
    tree.Branch("lep2_iso"        , &lep2_iso          , "lep2_iso/F"        ); 

    tree.Branch("lep1_gen_p4"         , "LorentzVector"     , &lep1_gen_p4       ); 
    tree.Branch("lep1_p4"             , "LorentzVector"     , &lep1_p4           ); 
    tree.Branch("lep2_gen_p4"         , "LorentzVector"     , &lep2_gen_p4       ); 
    tree.Branch("lep2_p4"             , "LorentzVector"     , &lep2_p4           ); 
    tree.Branch("gen_vbjets_p4"       , "vecLorentzVector"  , &gen_vbjets_p4     ); 
    tree.Branch("gen_vbjets_matched"  , "std::vector<bool>" , &gen_vbjets_matched); 
    tree.Branch("gen_vjets_p4"        , "vecLorentzVector"  , &gen_vjets_p4      ); 
    tree.Branch("gen_vjets_matched"   , "std::vector<bool>" , &gen_vjets_matched ); 
    tree.Branch("reco_vbjets_p4"      , "vecLorentzVector"  , &reco_vbjets_p4    ); 
    tree.Branch("reco_vjets_p4"       , "vecLorentzVector"  , &reco_vjets_p4     ); 
}
