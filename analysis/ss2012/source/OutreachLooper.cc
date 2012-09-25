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
//#include "trackSelections.h"
//#include "susySelections.h"
//#include "mcbtagSFuncert.h"
//#include "electronSelections.h"

// Tools
//#include "SameSignTree.h"
//#include "at/Predicates.h"
#include "at/DileptonHypType.h"
#include "at/DileptonChargeType.h"
#include "at/VtxReweight.h"
//#include "at/GoodRun.h"
//#include "at/PrintIdIsoInfo.h"
#include "rt/RootTools.h"
//#include "CTable.h"
#include "GenParticleStruct.h"
#include "EfficiencyModelTools.h"
//#include "ScaleFactors.h"

// ROOT
#include "Math/LorentzVector.h"
//#include "Math/Vector2D.h"
//#include "TH2F.h"

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
    const std::string& cut_string,
    bool verbose
)
    : AnalysisWithTree(root_file_name, "tree", "baby tree for SS2012 outreach")
    , m_sample(sample)
    , m_lumi(luminosity)
    , m_verbose(verbose)
    , m_vcuts(rt::string_split(cut_string, ","))
    , m_useOS(false)                             
    , m_useSS(false)                             
    //, m_applyVertexMatching(false)                
    //, m_vetoLowMass(false)                        
    //, m_vetoJets(false)                           
    //, m_vetoMET(false)                            
    //, m_vetoHT(false)                             
    //, m_requireCleaning(false)                    
    //, m_vetoBjets(false)                          
    //, m_useVertexReweighting(false)               
    //, m_requireDilepHyp(false)                    
    //, m_removeLeptonsOverlappingWithPartons(false)
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

    //deal with the cuts
    m_useOS                               = find(m_vcuts.begin() , m_vcuts.end() , "useOS"                               ) != m_vcuts.end();
    m_useSS                               = find(m_vcuts.begin() , m_vcuts.end() , "useSS"                               ) != m_vcuts.end();
    //m_applyVertexMatching                 = find(m_vcuts.begin() , m_vcuts.end() , "applyVertexMatching"                 ) != m_vcuts.end();
    //m_vetoLowMass                         = find(m_vcuts.begin() , m_vcuts.end() , "vetoLowMass"                         ) != m_vcuts.end();
    //m_vetoJets                            = find(m_vcuts.begin() , m_vcuts.end() , "vetoJets"                            ) != m_vcuts.end();
    //m_vetoMET                             = find(m_vcuts.begin() , m_vcuts.end() , "vetoMET"                             ) != m_vcuts.end();
    //m_vetoHT                              = find(m_vcuts.begin() , m_vcuts.end() , "vetoHT"                              ) != m_vcuts.end();
    //m_requireCleaning                     = find(m_vcuts.begin() , m_vcuts.end() , "requireCleaning"                     ) != m_vcuts.end();
    //m_vetoBjets                           = find(m_vcuts.begin() , m_vcuts.end() , "vetoBjets"                           ) != m_vcuts.end();
    //m_useVertexReweighting                = find(m_vcuts.begin() , m_vcuts.end() , "useVertexReweighting"                ) != m_vcuts.end();
    //m_requireDilepHyp                     = find(m_vcuts.begin() , m_vcuts.end() , "requireDilepHyp"                     ) != m_vcuts.end();
    //m_removeLeptonsOverlappingWithPartons = find(m_vcuts.begin() , m_vcuts.end() , "removeLeptonsOverlappingWithPartons" ) != m_vcuts.end();
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
        DileptonChargeType::value_type charge_type = DileptonChargeType::static_size;
        if (m_useSS)            {charge_type = DileptonChargeType::SS;         }
        if (m_useOS)            {charge_type = DileptonChargeType::OS;         }
        if (m_useSS && m_useOS) {charge_type = DileptonChargeType::static_size;}

        std::pair<GenParticleStruct, GenParticleStruct> best_gen_hyp = getGenHyp(20.0, 20.0, charge_type);
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

        //did it pass all the good event cuts?
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
        m_evt.gen_dilep_type = getHypType(id1, id2);

        // scale factors
        // m_evt.sf_dileptrig *= dilepTriggerScaleFactor(id1, p41, id2, p42);
        // m_evt.sf_lepeff *= tagAndProbeScaleFactor(id1, pt1, eta1) * tagAndProbeScaleFactor(id2, pt2, eta2);
        m_evt.sf_dileptrig = 1.0; 
        m_evt.sf_lepeff    = 1.0; 
        m_evt.sf_nbtags    = 1.0;

        // HT
        m_evt.gen_ht = getGenHT(40, 2.4);
        std::vector<unsigned int> indexJets = getRecoJets(best_gen_hyp.first, best_gen_hyp.second);
        m_evt.ht = getHT(indexJets);

        // Now take care of b-tagging
        std::vector<LorentzVector> vgbjets = getGenBjets(40., 2.4);
        for (size_t bidx = 0; bidx < vgbjets.size(); bidx++) 
        {
            int index = getRecoJet(vgbjets.at(bidx));

            if (index < 0)
                continue;

            if (cms2.pfjets_combinedSecondaryVertexBJetTag().at(index) > 0.679)
            {
                m_evt.vbjets_p4.push_back(vgbjets.at(bidx));
            }
        }
        m_evt.gen_vbjets_p4 = vgbjets;
        m_evt.gen_nbjets    = vgbjets.size();
        m_evt.nbjets        = m_evt.vbjets_p4.size();

        // Now take care of jets
        std::vector<LorentzVector> vgjets = getGenJets(40.0, 2.4);
        for (size_t bidx = 0; bidx < vgjets.size(); bidx++) 
        {

            int index = getRecoJet(vgjets.at(bidx));

            if (index < 0)
                continue;

            if (pfjets_p4().at(index).pt() > 40.0 && fabs(pfjets_p4().at(index).eta()) < 2.4)
            {
                m_evt.vjets_p4.push_back(vgjets.at(bidx));
            }
        }
        m_evt.gen_vjets_p4 = vgjets;
        m_evt.gen_njets    = vgjets.size();
        m_evt.njets        = m_evt.vjets_p4.size();

        // leptons
        // --------------------------------------------------------------------------------------------------------- //

        // lep1
        m_evt.lep1_gen_p4   = p41;
        m_evt.lep1_gen_id   = id1;
        m_evt.lep1_from_tau = abs(best_gen_hyp.first.id_ ) == 15;

        // weight *= tagAndProbeScaleFactor(id1, pt1, eta1);
        // need to figure out how to apply trigger scale factor here

        std::pair<LorentzVector, int> reco_lep1 = getRecoLepton(best_gen_hyp.first);
        if (reco_lep1.second > -1) 
        {
            m_evt.lep1_p4         = reco_lep1.first;
            m_evt.lep1_id         = reco_lep1.second;
            m_evt.lep1_num        = samesign::isNumeratorLepton(id1, reco_lep1.second);
            m_evt.lep1_passes_id  = samesign::isGoodLepton(id1, reco_lep1.second);
            m_evt.lep1_passes_iso = samesign::isIsolatedLepton(id1, reco_lep1.second);
            m_evt.lep1_iso        = (abs(id1)==11) ? samesign::electronIsolationPF2012(reco_lep1.second) 
                                                   : muonIsoValuePF2012_deltaBeta(reco_lep1.second);
        }

        // lep2
        m_evt.lep2_gen_p4   = p42;
        m_evt.lep2_gen_id   = id2;
        m_evt.lep2_from_tau = abs(best_gen_hyp.second.id_ ) == 15;

        // weight *= tagAndProbeScaleFactor(id1, pt1, eta1);
        // need to figure out how to apply trigger scale factor here

        std::pair<LorentzVector, int> reco_lep2 = getRecoLepton(best_gen_hyp.second);
        if (reco_lep2.second > -1) 
        {
            m_evt.lep2_p4         = reco_lep2.first;
            m_evt.lep2_id         = reco_lep2.second;
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

    // reco event level
    ht                  = -999999.0;
    met                 = -999999.0;
    nbjets              = -999999;
    njets               = -999999;
    sf_dileptrig        = 1.0;
    sf_lepeff           = 1.0;
    sf_nbtags           = 1.0;
    nvtxs               = -999999;
    vtxw                = -999999.0;

    // gen event level
    gen_met             = -999999.0;
    gen_ht              = -999999.0;
    gen_nbjets          = -999999;
    gen_njets           = -999999;
    gen_dilep_type      = -999999;

    // gen level
    lep1_from_tau       = false;
    lep1_gen_id         = false;

    lep2_from_tau       = false;
    lep2_gen_id         = false;


    // reco level
    lep1_id             = -999999;
    lep1_passes_id      = false;
    lep1_passes_iso     = false;
    lep1_iso            = -999999.0;
    lep1_num            = false;

    lep2_id             = -999999;
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
    gen_vbjets_p4.clear();
    gen_vjets_p4.clear();
}

void OutreachTree::SetBranches(TTree &tree)
{
    event_info.SetBranches(tree);

    // reco event level
    tree.Branch("ht"              , &ht                , "ht/F"              ); 
    tree.Branch("met"             , &met               , "met/F"             ); 
    tree.Branch("sf_dileptrig"    , &sf_dileptrig      , "sf_dileptrig/F"    ); 
    tree.Branch("sf_lepeff"       , &sf_lepeff         , "sf_lepeff/F"       ); 
    tree.Branch("sf_nbtags"       , &sf_nbtags         , "sf_nbtags/F"       ); 
    tree.Branch("nvtxs"           , &nvtxs             , "nvtxs/I"           ); 
    tree.Branch("nbjets"          , &nbjets            , "nbjets/I"          ); 
    tree.Branch("njets"           , &njets             , "njets/I"           ); 
    tree.Branch("vtxw"            , &vtxw              , "vtxw/F"            ); 
    tree.Branch("clean"           , &clean             , "clean/F"           ); 
    tree.Branch("gen_met"         , &gen_met           , "gen_met/F"         ); 
    tree.Branch("gen_ht"          , &gen_ht            , "gen_ht/F"          ); 
    tree.Branch("gen_nbjets"      , &gen_nbjets        , "gen_nbjets/I"      ); 
    tree.Branch("gen_njets"       , &gen_njets         , "gen_njets/I"       ); 
    tree.Branch("gen_dilep_type"  , &gen_dilep_type    , "gen_dilep_type/O"  ); 
    tree.Branch("lep1_from_tau"   , &lep1_from_tau     , "lep1_from_tau/O"   ); 
    tree.Branch("lep1_gen_id"     , &lep1_gen_id       , "lep1_gen_id/I"     ); 
    tree.Branch("lep1_num"        , &lep1_num          , "lep1_num/O"        ); 
    tree.Branch("lep1_iso"        , &lep1_iso          , "lep1_iso/F"        ); 
    tree.Branch("lep1_id"         , &lep1_id           , "lep1_id/I"         ); 
    tree.Branch("lep1_passes_id"  , &lep1_passes_id    , "lep1_passes_id/I"  ); 
    tree.Branch("lep1_passes_iso" , &lep1_passes_iso   , "lep1_passes_iso/I" ); 
    tree.Branch("lep1_num"        , &lep1_num          , "lep1_num/O"        ); 
    tree.Branch("lep2_from_tau"   , &lep2_from_tau     , "lep2_from_tau/O"   ); 
    tree.Branch("lep2_gen_id"     , &lep2_gen_id       , "lep2_gen_id/I"     ); 
    tree.Branch("lep2_num"        , &lep2_num          , "lep2_num/O"        ); 
    tree.Branch("lep2_iso"        , &lep2_iso          , "lep2_iso/F"        ); 
    tree.Branch("lep2_id"         , &lep2_id           , "lep2_id/I"         ); 
    tree.Branch("lep2_passes_id"  , &lep2_passes_id    , "lep2_passes_id/I"  ); 
    tree.Branch("lep2_passes_iso" , &lep2_passes_iso   , "lep2_passes_iso/I" ); 
    tree.Branch("lep2_num"        , &lep2_num          , "lep2_num/O"        ); 
    tree.Branch("lep1_gen_p4"     , "LorentzVector"    , &lep1_gen_p4        ); 
    tree.Branch("lep1_p4"         , "LorentzVector"    , &lep1_p4            ); 
    tree.Branch("lep2_gen_p4"     , "LorentzVector"    , &lep2_gen_p4        ); 
    tree.Branch("lep2_p4"         , "LorentzVector"    , &lep2_p4            ); 
    tree.Branch("vbjets_p4"       , "vecLorentzVector" , &vbjets_p4          ); 
    tree.Branch("vjets_p4"        , "vecLorentzVector" , &vjets_p4           ); 
    tree.Branch("gen_vbjets_p4"   , "vecLorentzVector" , &gen_vbjets_p4      ); 
    tree.Branch("gen_vjets_p4"    , "vecLorentzVector" , &gen_vjets_p4       ); 
}
