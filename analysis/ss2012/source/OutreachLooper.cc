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

        // check that the channel is correct
        int nels  = 0;
        int nmus  = 0;
        int ntaus = 0;
        leptonGenpCount_lepTauDecays(nels, nmus, ntaus);
        if (m_sample == Sample::dy && (nels != 2 || nmus != 2 || ntaus != 2)) 
        {
            if (m_verbose) {cout << "OutreachLooper: DY does not have 2 gen level leptons!" << endl;} 
            return 0;
        }

        // Gen hypothesis
        std::pair<GenParticleStruct, GenParticleStruct> best_gen_hyp = getGenHyp(20.0, 20.0, DileptonChargeType::static_size);
        if (best_gen_hyp.first.id_ == 0 || best_gen_hyp.second.id_ == 0)
        {
            if (m_verbose) {cout << "OutreachLooper: does not have a good gen hyp" << endl;} 
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

        // did it pass all the good event cuts?
        m_evt.clean = cleaning_standardNovember2011();

        // lepton variables
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

        // gen lep type
        at::DileptonHypType::value_type dilep_type = getHypType(id1, id2);
        m_evt.dilep_type = static_cast<unsigned int>(dilep_type);

        // scale factors
        m_evt.sf_dileptrig = dilepTriggerScaleFactor(dilep_type);
        // m_evt.sf_lepeff *= tagAndProbeScaleFactor(id1, pt1, eta1) * tagAndProbeScaleFactor(id2, pt2, eta2);
        m_evt.sf_lepeff    = 1.0; 

        // scale factor for # btags 
        m_evt.sf_nbtag  = 1.0;
        m_evt.sf_nbtag3 = 1.0;
        //JetType jet_type = evt_isRealData() ? JETS_TYPE_PF_FAST_CORR_RESIDUAL : JETS_TYPE_PF_FAST_CORR;
        //vector<LorentzVector> bjets = samesign::getBtaggedJets(dilep_type, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, 0);
        //std::sort(bjets.begin(), bjets.end(), SortByPt<LorentzVector>());
        //m_evt.sf_nbtag  = 0.0;
        //m_evt.sf_nbtag3 = 0.0;
        //if (bjets.size() == 2) 
        //{
        //    m_evt.sf_nbtag = btagEventWeight(bjets.size(), bjets.at(0).pt(), bjets.at(1).pt(), 0.0, 0.0, m_is_fastsim);
        //}
        //else if (bjets.size() == 3) 
        //{
        //    m_evt.sf_nbtag  = btagEventWeight (bjets.size(), bjets.at(0).pt(), bjets.at(1).pt(), bjets.at(2).pt(), 0., m_is_fastsim);
        //    m_evt.sf_nbtag3 = btagEventWeight3(bjets.size(), bjets.at(0).pt(), bjets.at(1).pt(), bjets.at(2).pt(), 0., m_is_fastsim);
        //}
        //else if (bjets.size() > 3) 
        //{
        //    m_evt.sf_nbtag  = btagEventWeight (bjets.size(), bjets.at(0).pt(), bjets.at(1).pt(), bjets.at(2).pt(), bjets.at(3).pt(), m_is_fastsim);
        //    m_evt.sf_nbtag3 = btagEventWeight3(bjets.size(), bjets.at(0).pt(), bjets.at(1).pt(), bjets.at(2).pt(), bjets.at(3).pt(), m_is_fastsim);
        //}

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
        m_evt.ht = getHT(indexJets);

        // Now take care of b-tagging
        std::vector<LorentzVector> vgbjets = getGenBjets(40.0, 2.4);
        m_evt.nbjets_num = 0; 
        for (size_t bidx = 0; bidx < vgbjets.size(); bidx++) 
        {
            int index = getRecoJet(vgbjets.at(bidx));
            if (index < 0)
            {
                m_evt.vjets_num.push_back(false);
                continue;
            }

            if (cms2.pfjets_combinedSecondaryVertexBJetTag().at(index) > 0.679)
            {
                m_evt.vbjets_num.push_back(true);
                m_evt.nbjets_num++;
            }
            else
            {
                m_evt.vbjets_num.push_back(false);
            }
        }
        m_evt.vbjets_p4 = vgbjets;
        m_evt.nbtags    = m_evt.vbjets_p4.size();

        // Now take care of jets
        std::vector<LorentzVector> vgjets = getGenJets(40.0, 2.4);
        m_evt.njets_num = 0; 
        for (size_t bidx = 0; bidx < vgjets.size(); bidx++) 
        {

            int index = getRecoJet(vgjets.at(bidx));
            if (index < 0)
            {
                m_evt.vjets_num.push_back(false);
                continue;
            }

            if (pfjets_p4().at(index).pt() > 40.0 && fabs(pfjets_p4().at(index).eta()) < 2.4)
            {
                m_evt.vjets_num.push_back(true);
                m_evt.njets_num++;
            }
            else
            {
                m_evt.vjets_num.push_back(false);
            }
        }
        m_evt.vjets_p4 = vgjets;
        m_evt.njets    = m_evt.vjets_p4.size();

        // leptons
        // --------------------------------------------------------------------------------------------------------- //

        // lep1
        m_evt.lep1_gen_p4   = p41;
        m_evt.lep1_pdgid    = id1;
        m_evt.lep1_from_tau = abs(best_gen_hyp.first.id_ ) == 15;

        // weight *= tagAndProbeScaleFactor(id1, pt1, eta1);
        // need to figure out how to apply trigger scale factor here

        std::pair<LorentzVector, int> reco_lep1 = getRecoLepton(best_gen_hyp.first);
        if (reco_lep1.second > -1) 
        {
            m_evt.lep1_matched    = true; 
            m_evt.lep1_p4         = reco_lep1.first;
            m_evt.lep1_num        = samesign::isNumeratorLepton(id1, reco_lep1.second);
            m_evt.lep1_passes_id  = samesign::isGoodLepton(id1, reco_lep1.second);
            m_evt.lep1_passes_iso = samesign::isIsolatedLepton(id1, reco_lep1.second);
            m_evt.lep1_iso        = (abs(id1)==11) ? samesign::electronIsolationPF2012(reco_lep1.second) 
                                                   : muonIsoValuePF2012_deltaBeta(reco_lep1.second);
        }

        // lep2
        m_evt.lep2_gen_p4   = p42;
        m_evt.lep2_pdgid    = id2;
        m_evt.lep2_from_tau = abs(best_gen_hyp.second.id_ ) == 15;

        // weight *= tagAndProbeScaleFactor(id1, pt1, eta1);
        // need to figure out how to apply trigger scale factor here

        std::pair<LorentzVector, int> reco_lep2 = getRecoLepton(best_gen_hyp.second);
        if (reco_lep2.second > -1) 
        {
            m_evt.lep2_matched    = true; 
            m_evt.lep2_p4         = reco_lep2.first;
            m_evt.lep2_num        = samesign::isNumeratorLepton(id2, reco_lep2.second);
            m_evt.lep2_passes_id  = samesign::isGoodLepton(id2, reco_lep2.second);
            m_evt.lep2_passes_iso = samesign::isIsolatedLepton(id2, reco_lep2.second);
            m_evt.lep2_iso        = (abs(id2)==11) ? samesign::electronIsolationPF2012(reco_lep2.second)
                                                   : muonIsoValuePF2012_deltaBeta(reco_lep2.second);
        }

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

    // event level
    ht                  = -999999.0;
    //met                 = -999999.0;
    nbtags              = -999999;
    njets               = -999999;
    nbjets_num          = -999999;
    njets_num           = -999999;
    sf_dileptrig        = 1.0;
    sf_lepeff           = 1.0;
    sf_nbtag            = 1.0;
    sf_nbtag3           = 1.0;
    nvtxs               = -999999;
    vtxw                = -999999.0;
    gen_ht              = -999999.0;
    dilep_type          = -999999;

    sparm0              = -999999.0;
    sparm1              = -999999.0;
    sparm2              = -999999.0;
    sparm3              = -999999.0;

    // lepton 
    lep1_from_tau       = false;
    lep1_pdgid          = -999999;
    lep1_matched        = false;
    lep1_passes_id      = false;
    lep1_passes_iso     = false;
    lep1_iso            = -999999.0;
    lep1_num            = false;

    lep2_from_tau       = false;
    lep2_pdgid          = -999999;
    lep2_matched        = false;
    lep2_passes_id      = false;
    lep2_passes_iso     = false;
    lep2_iso            = -999999.0;
    lep2_num            = false;

    // LorentzVectors
    lep1_gen_p4.SetXYZT(0,0,0,0);
    lep2_gen_p4.SetXYZT(0,0,0,0);
    lep2_p4.SetXYZT(0,0,0,0);
    lep2_p4.SetXYZT(0,0,0,0);

    // clear vectors
    vbjets_p4.clear();
    vjets_p4.clear();
    vbjets_num.clear();
    vjets_num.clear();
}

void OutreachTree::SetBranches(TTree &tree)
{
    event_info.SetBranches(tree);

    // reco event level
    tree.Branch("ht"              , &ht                , "ht/F"              ); 
    tree.Branch("sf_dileptrig"    , &sf_dileptrig      , "sf_dileptrig/F"    ); 
    tree.Branch("sf_lepeff"       , &sf_lepeff         , "sf_lepeff/F"       ); 
    tree.Branch("sf_nbtag"        , &sf_nbtag          , "sf_nbtag/F"        ); 
    tree.Branch("sf_nbtag3"       , &sf_nbtag3         , "sf_nbtag3/F"       ); 
    tree.Branch("nvtxs"           , &nvtxs             , "nvtxs/I"           ); 
    tree.Branch("nbtags"          , &nbtags            , "nbtags/I"          ); 
    tree.Branch("njets"           , &njets             , "njets/I"           ); 
    tree.Branch("nbjets_num"      , &nbjets_num        , "nbjets_num/I"      ); 
    tree.Branch("njets_num"       , &njets_num         , "njets_num/I"       ); 
    tree.Branch("vtxw"            , &vtxw              , "vtxw/F"            ); 
    tree.Branch("clean"           , &clean             , "clean/O"           ); 
    tree.Branch("gen_ht"          , &gen_ht            , "gen_ht/F"          ); 
    tree.Branch("dilep_type"      , &dilep_type        , "dilep_type/I"      ); 
    tree.Branch("lep1_from_tau"   , &lep1_from_tau     , "lep1_from_tau/O"   ); 
    tree.Branch("lep1_num"        , &lep1_num          , "lep1_num/O"        ); 
    tree.Branch("lep1_iso"        , &lep1_iso          , "lep1_iso/F"        ); 
    tree.Branch("lep1_pdgid"      , &lep1_pdgid        , "lep1_pdgid/I"      ); 
    tree.Branch("lep1_matched"    , &lep1_matched      , "lep1_matched/O"    ); 
    tree.Branch("lep1_passes_id"  , &lep1_passes_id    , "lep1_passes_id/O"  ); 
    tree.Branch("lep1_passes_iso" , &lep1_passes_iso   , "lep1_passes_iso/O" ); 
    tree.Branch("lep1_num"        , &lep1_num          , "lep1_num/O"        ); 
    tree.Branch("lep2_from_tau"   , &lep2_from_tau     , "lep2_from_tau/O"   ); 
    tree.Branch("lep2_num"        , &lep2_num          , "lep2_num/O"        ); 
    tree.Branch("lep2_iso"        , &lep2_iso          , "lep2_iso/F"        ); 
    tree.Branch("lep2_pdgid"      , &lep2_pdgid        , "lep2_pdgid/I"      ); 
    tree.Branch("lep2_matched"    , &lep2_matched      , "lep2_matched/O"    ); 
    tree.Branch("lep2_passes_id"  , &lep2_passes_id    , "lep2_passes_id/O"  ); 
    tree.Branch("lep2_passes_iso" , &lep2_passes_iso   , "lep2_passes_iso/O" ); 
    tree.Branch("lep2_num"        , &lep2_num          , "lep2_num/O"        ); 
    tree.Branch("sparm0"          , &sparm0            , "sparm0/O"          ); 
    tree.Branch("sparm1"          , &sparm1            , "sparm0/1"          ); 
    tree.Branch("sparm2"          , &sparm2            , "sparm0/2"          ); 
    tree.Branch("sparm3"          , &sparm3            , "sparm0/3"          ); 
    tree.Branch("lep1_gen_p4"     , "LorentzVector"    , &lep1_gen_p4        ); 
    tree.Branch("lep1_p4"         , "LorentzVector"    , &lep1_p4            ); 
    tree.Branch("lep2_gen_p4"     , "LorentzVector"    , &lep2_gen_p4        ); 
    tree.Branch("lep2_p4"         , "LorentzVector"    , &lep2_p4            ); 
    tree.Branch("vbjets_num"      , "std::vector<bool>", &vbjets_num          ); 
    tree.Branch("vjets_num"       , "std::vector<bool>", &vjets_num           ); 
    tree.Branch("vbjets_p4"       , "vecLorentzVector" , &vbjets_p4          ); 
    tree.Branch("vjets_p4"        , "vecLorentzVector" , &vjets_p4           ); 
}
