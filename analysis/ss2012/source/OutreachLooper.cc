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
#include "TH1F.h"
#include "TF1.h"

// typdefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef std::vector<LorentzVector> vecLorentzVector;

using namespace tas;
using namespace std;
using namespace efftools;
using namespace at;

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

        // sparms parameters
        if (m_sparms) 
        {
            int n_sparms = sparm_values().size();
            if (n_sparms > 0) m_evt.sparm0 = sparm_values().at(0);
            if (n_sparms > 1) m_evt.sparm1 = sparm_values().at(1);
            if (n_sparms > 2) m_evt.sparm2 = sparm_values().at(2);
            if (n_sparms > 3) m_evt.sparm3 = sparm_values().at(3);
        }

        // Fill the tree (to preserve the number of events)
        m_evt.event_info.FillCommon(m_sample);

        // Gen hypothesis
        std::pair<GenParticleStruct, GenParticleStruct> best_gen_hyp = getGenHyp(20.0, 20.0, DileptonChargeType::static_size);
        if (best_gen_hyp.first.id_ == 0 || best_gen_hyp.second.id_ == 0)
        {
            if (m_verbose) {cout << "OutreachLooper: does not have a good gen hyp" << endl;} 

            m_tree->Fill();

            // skip the rest of the event
            return 0;
        }

        // basic selection
        // --------------------------------------------------------------------------------------------------------- //

        // vertex re-weighting
        m_evt.nvtxs = numberOfGoodVertices(); 
        m_evt.vtxw  = 1.0; 
        //m_evt.vtxw  = evt_isRealData() ? 1.0 : vtxweight_n(m_evt.nvtxs, evt_isRealData(), false);

        // lepton variables
        bool from_tau1 = abs(best_gen_hyp.first.id_  ) == 15;
        bool from_tau2 = abs(best_gen_hyp.second.id_ ) == 15;
        int  id1  = from_tau1 ? best_gen_hyp.first.did_   : best_gen_hyp.first.id_;
        int  idx1 = from_tau1 ? best_gen_hyp.first.didx_  : best_gen_hyp.first.idx_;
        int  id2  = from_tau2 ? best_gen_hyp.second.did_  : best_gen_hyp.second.id_;
        int  idx2 = from_tau2 ? best_gen_hyp.second.didx_ : best_gen_hyp.second.idx_;
        GenParticleStruct gen1 = best_gen_hyp.first;
        GenParticleStruct gen2 = best_gen_hyp.second;

        // get gen LorenzVectors
        LorentzVector p41;
        if (from_tau1)
        {
            p41 = genps_lepdaughter_p4().at(gen1.idx_).at(idx1);
        }
        else
        {
            p41 = genps_p4().at(idx1);
        }

        LorentzVector p42;
        if (from_tau2)
        {
            p42 = genps_lepdaughter_p4().at(gen2.idx_).at(idx2);
        }
        else
        {
            p42 = genps_p4().at(idx2);
        }

        //// put in the order of increasing pT
        //if (genps_p4().at(idx1).pt() < genps_p4().at(idx2).pt())
        //{
        //    std::swap(id1 ,  id2);
        //    std::swap(idx1, idx2);
        //    std::swap(from_tau1, from_tau2);
        //    std::swap(gen1, gen2);
        //}

        // gen lep type
        m_evt.gen_dilep_type = getHypType(id1, id2);

        // is os/ss
        m_evt.gen_is_ss = (id1 * id2 > 0);
        m_evt.gen_is_os = (id1 * id2 < 0);

        // HT
        m_evt.gen_ht = getGenHT(40, 2.4);

        // leptons
        // --------------------------------------------------------------------------------------------------------- //

        // lep1
        m_evt.lep1_gen_p4         = p41;
        m_evt.lep1_gen_pdgid      = id1;
        m_evt.lep1_from_tau       = from_tau1;
		m_evt.lep1_gen_iso        = getGenIsolation(p41);
		m_evt.lep1_gen_nearjet_dr = getClosestParton(p41);

        // lep2
        m_evt.lep2_gen_p4     	  = p42;
        m_evt.lep2_gen_pdgid  	  = id2;
        m_evt.lep2_from_tau   	  = from_tau2;
		m_evt.lep2_gen_iso        = getGenIsolation(p42);
		m_evt.lep2_gen_nearjet_dr = getClosestParton(p42);

        // determine if matched to gen
        std::pair<LorentzVector, int> reco_lep1 = getRecoLepton(gen1);
        if (reco_lep1.second > -1 && reco_lep1.first.pt() > 20.0 && abs(reco_lep1.first.eta())<2.4) 
        {
            m_evt.lep1_matched    = true; 
            m_evt.lep1_p4         = reco_lep1.first;
            m_evt.lep1_num        = samesign::isNumeratorLepton(id1, reco_lep1.second);
            m_evt.lep1_passes_id  = samesign::isGoodLepton(id1, reco_lep1.second);
            m_evt.lep1_passes_iso = samesign::isIsolatedLepton(id1, reco_lep1.second);
            m_evt.lep1_iso        = (abs(id1)==11) ? samesign::electronIsolationPF2012(reco_lep1.second) 
                                                   : muonIsoValuePF2012_deltaBeta(reco_lep1.second);
        }

        std::pair<LorentzVector, int> reco_lep2 = getRecoLepton(gen2);
        if (reco_lep2.second > -1 && reco_lep2.first.pt() > 20.0 && abs(reco_lep2.first.eta())<2.4) 
        {
            m_evt.lep2_matched    = true; 
            m_evt.lep2_p4         = reco_lep2.first;
            m_evt.lep2_num        = samesign::isNumeratorLepton(id2, reco_lep2.second);
            m_evt.lep2_passes_id  = samesign::isGoodLepton(id2, reco_lep2.second);
            m_evt.lep2_passes_iso = samesign::isIsolatedLepton(id2, reco_lep2.second);
            m_evt.lep2_iso        = (abs(id2)==11) ? samesign::electronIsolationPF2012(reco_lep2.second)
                                                   : muonIsoValuePF2012_deltaBeta(reco_lep2.second);
        }

        // reco quantities 
        // --------------------------------------------------------------------------------------------------------- //

        // event variables
        std::vector<unsigned int> indexJets = getRecoJets(gen1, gen2);
        m_evt.reco_ht = getHT(indexJets);

        // Now take care of b-jets 
        m_evt.gen_vbjets_p4 = getGenBjets(40.0, 2.4);
        m_evt.gen_nbtags    = m_evt.gen_vbjets_p4.size();
        for (size_t bidx = 0; bidx < m_evt.gen_vbjets_p4.size(); bidx++) 
        {
            int index = getRecoJet(m_evt.gen_vbjets_p4.at(bidx));
            if (index < 0)
            {
                m_evt.gen_vbjets_matched.push_back(false);
                continue;
            }

            if (pfjets_p4().at(index).pt() > 40.0 && fabs(pfjets_p4().at(index).eta()) < 2.4 && 
				cms2.pfjets_combinedSecondaryVertexBJetTag().at(index) > 0.679)
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
        m_evt.gen_vjets_p4 = getGenJets(40.0, 2.4);
        m_evt.gen_njets    = m_evt.gen_vbjets_p4.size(); 

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

        // by constuction
        m_evt.dilep_type = m_evt.gen_dilep_type; 

        // reco met
        m_evt.reco_met = evt_pfmet_type1cor();   

        // scale factors
        // --------------------------------------------------------------------------------------------------------- //

        m_evt.sf_dileptrig = dilepTriggerScaleFactor(m_evt.dilep_type);
        m_evt.sf_lepeff    = 1.0; 

        // scale factor for # btags 
        m_evt.sf_nbtag  = 0.0;
        m_evt.sf_nbtag3 = 0.0;
        vector<LorentzVector> bjets(m_evt.reco_vbjets_p4); 
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

    gen_dilep_type      = at::DileptonHypType::static_size;
    gen_ht              = -99999.0;
    gen_nbtags          = -999999;
    gen_njets           = -999999;
    gen_is_ss           = false;
    gen_is_os           = false;
    dilep_type          = at::DileptonHypType::static_size;
    reco_ht             = -999999.0;
    reco_met            = -999999.0;
    reco_nbtags         = -999999;
    reco_njets          = -999999;
    reco_is_ss          = false;
    reco_is_os          = false;
    sf_dileptrig        = 1.0;
    sf_lepeff           = 1.0;
    sf_nbtag            = 1.0;
    sf_nbtag3           = 1.0;
    sparm0              = -999999.0;
    sparm1              = -999999.0;
    sparm2              = -999999.0;
    sparm3              = -999999.0;
    lep1_gen_pdgid      = -999999;
    lep1_pdgid          = -999999;
    lep1_matched        = false;
    lep1_from_tau       = false;
    lep1_passes_id      = false;
    lep1_passes_iso     = - false;
    lep1_num            = false;
    lep1_gen_nearjet_dr = -999999;
    lep1_gen_iso        = -999999;
    lep1_iso            = -999999.0;
    lep2_pdgid          = -999999;
    lep2_gen_pdgid      = -999999;
    lep2_matched        = false;
    lep2_from_tau       = false;
    lep2_passes_id      = false;
    lep2_passes_iso     = false;
    lep2_num            = false;
    lep2_gen_nearjet_dr = -999999;
    lep2_gen_iso        = -999999;
    lep2_iso            = -999999.0;

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
    tree.Branch("gen_dilep_type"      , &gen_dilep_type      , "gen_dilep_type/I"      ); 
    tree.Branch("gen_ht"              , &gen_ht              , "gen_ht/F"              ); 
    tree.Branch("gen_nbtags"          , &gen_nbtags          , "gen_nbtags/I"          ); 
    tree.Branch("gen_njets"           , &gen_njets           , "gen_njets/I"           ); 
    tree.Branch("gen_is_ss"           , &gen_is_ss           , "gen_is_ss/O"           ); 
    tree.Branch("gen_is_os"           , &gen_is_os           , "gen_is_os/O"           ); 
    tree.Branch("dilep_type"          , &dilep_type          , "dilep_type/I"          ); 
    tree.Branch("reco_ht"             , &reco_ht             , "reco_ht/F"             ); 
    tree.Branch("reco_met"            , &reco_met            , "reco_met/F"            ); 
    tree.Branch("reco_nbtags"         , &reco_nbtags         , "reco_nbtags/I"         ); 
    tree.Branch("reco_njets"          , &reco_njets          , "reco_njets/I"          ); 
    tree.Branch("reco_is_ss"          , &reco_is_ss          , "reco_is_ss/F"          ); 
    tree.Branch("reco_is_os"          , &reco_is_os          , "reco_is_os/F"          ); 
    tree.Branch("sf_dileptrig"        , &sf_dileptrig        , "sf_dileptrig/F"        ); 
    tree.Branch("sf_lepeff"           , &sf_lepeff           , "sf_lepeff/F"           ); 
    tree.Branch("sf_nbtag"            , &sf_nbtag            , "sf_nbtag/F"            ); 
    tree.Branch("sf_nbtag3"           , &sf_nbtag3           , "sf_nbtag3/F"           ); 
    tree.Branch("sparm0"              , &sparm0              , "sparm0/F"              ); 
    tree.Branch("sparm1"              , &sparm1              , "sparm1/F"              ); 
    tree.Branch("sparm2"              , &sparm2              , "sparm2/F"              ); 
    tree.Branch("sparm3"              , &sparm3              , "sparm3/F"              ); 
    tree.Branch("lep1_gen_pdgid"      , &lep1_gen_pdgid      , "lep1_gen_pdgid/I"      ); 
    tree.Branch("lep1_pdgid"          , &lep1_pdgid          , "lep1_pdgid/I"          ); 
    tree.Branch("lep1_matched"        , &lep1_matched        , "lep1_matched/O"        ); 
    tree.Branch("lep1_from_tau"       , &lep1_from_tau       , "lep1_from_tau/O"       ); 
    tree.Branch("lep1_passes_id"      , &lep1_passes_id      , "lep1_passes_id/O"      ); 
    tree.Branch("lep1_passes_iso"     , &lep1_passes_iso     , "lep1_passes_iso/O"     ); 
    tree.Branch("lep1_num"            , &lep1_num            , "lep1_num/O"            ); 
    tree.Branch("lep1_gen_nearjet_dr" , &lep1_gen_nearjet_dr , "lep1_gen_nearjet_dr/F" ); 
    tree.Branch("lep1_gen_iso"        , &lep1_gen_iso        , "lep1_gen_iso/F"        ); 
    tree.Branch("lep1_iso"            , &lep1_iso            , "lep1_iso/F"            ); 
    tree.Branch("lep2_pdgid"          , &lep2_pdgid          , "lep2_pdgid/I"          ); 
    tree.Branch("lep2_gen_pdgid"      , &lep2_gen_pdgid      , "lep2_gen_pdgid/I"      ); 
    tree.Branch("lep2_matched"        , &lep2_matched        , "lep2_matched/O"        ); 
    tree.Branch("lep2_from_tau"       , &lep2_from_tau       , "lep2_from_tau/O"       ); 
    tree.Branch("lep2_passes_id"      , &lep2_passes_id      , "lep2_passes_id/O"      ); 
    tree.Branch("lep2_passes_iso"     , &lep2_passes_iso     , "lep2_passes_iso/O"     ); 
    tree.Branch("lep2_num"            , &lep2_num            , "lep2_num/O"            ); 
    tree.Branch("lep2_gen_nearjet_dr" , &lep2_gen_nearjet_dr , "lep2_gen_nearjet_dr/F" ); 
    tree.Branch("lep2_gen_iso"        , &lep2_gen_iso        , "lep2_gen_iso/F"        ); 
    tree.Branch("lep2_iso"            , &lep2_iso            , "lep2_iso/F"            ); 

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
