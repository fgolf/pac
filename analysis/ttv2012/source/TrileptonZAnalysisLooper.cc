#include "TrileptonZAnalysisLooper.h"

// c++
#include <stdexcept>
#include <algorithm>
#include <fstream>

// cms2
//#include "CMS2.h"
#include "ssSelections.h"
#include "ttvSelections.h"
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

// Tools
#include "TrileptonZTree.h"
#include "at/Predicates.h"
#include "at/DileptonHypType.h"
#include "at/DileptonChargeType.h"
#include "at/VtxReweight.h"
#include "at/GoodRun.h"
#include "at/PrintIdIsoInfo.h"
#include "rt/RootTools.h"
#include "CTable.h"
#include "GenParticleStruct.h"
#include "EfficiencyModelTools.h"
#include "ScaleFactors.h"
#include "EGammaMvaEleEstimator.h"

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

float EffectiveArea03(int id, int idx)
{
    if (abs(id)!=11)
        return -999990.0;

    float etaAbs = fabs(els_etaSC()[idx]);

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

float EffectiveArea04(int id, int idx)
{
    if (abs(id)!=11)
        return -999990.0;

    float etaAbs = fabs(els_etaSC()[idx]);

    // get effective area
    float AEff = 0.;
    if (etaAbs <= 1.0) AEff = 0.19;
    else if (etaAbs > 1.0 && etaAbs <= 1.479) AEff = 0.25;
    else if (etaAbs > 1.479 && etaAbs <= 2.0) AEff = 0.12;
    else if (etaAbs > 2.0 && etaAbs <= 2.2) AEff = 0.21;
    else if (etaAbs > 2.2 && etaAbs <= 2.3) AEff = 0.27;
    else if (etaAbs > 2.3 && etaAbs <= 2.4) AEff = 0.44;
    else if (etaAbs > 2.4) AEff = 0.52;
    return AEff;
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

// construct:
TrileptonZAnalysisLooper::TrileptonZAnalysisLooper
(
    const std::string& root_file_name,
    const Sample::value_type& sample,
    const std::string& fake_rate_file_name,
    const std::string& mfake_rate_hist_name,
    const std::string& efake_rate_hist_name,
    const std::string& vtxreweight_file_name,
    const std::string& goodrun_file_name,
    double luminosity,
    int njets,
    int nbtags,
    int  jetMetScale,
    bool sync_print,
    bool verbose,
    bool gen_only,
    const std::string apply_jec_otf,
    const std::string ele_mva_path
    )
    : AnalysisWithTree(root_file_name, "tree", "baby tree for TTZ2012 analysis")
    , m_sample(sample)
    , m_lumi(luminosity)
    , m_njets(njets)   
    , m_nbtags(nbtags)
    , m_jetMetScale(jetMetScale)
    , m_sync_print(sync_print)
    , m_verbose(verbose)
    , m_gen_only(gen_only)
    , jet_corrector(NULL)
    , met_corrector(NULL)
    , trigEleMVA(NULL)
    , nontrigEleMVA(NULL)
    , zmass(91.)
    , mu_eta(2.4)
    , ele_eta(2.5)
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

        std::string path = rt::getenv("PAC");
        if (!path.empty())
        {
            path += "/externals/source/cms2_core/HEAD/CORE/jetcorr/data/";
            m_list_of_jec_filenames.push_back(Form("%s/%s_L1FastJet_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            m_list_of_jec_filenames.push_back(Form("%s/%s_L2Relative_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            m_list_of_jec_filenames.push_back(Form("%s/%s_L3Absolute_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            if (m_sample <= at::Sample::datame)
                m_list_of_jec_filenames.push_back(Form("%s/%s_L2L3Residual_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
        }
        else
        {
            path = "./";
            m_list_of_jec_filenames.push_back(Form("%s/%s_L1FastJet_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            m_list_of_jec_filenames.push_back(Form("%s/%s_L2Relative_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            m_list_of_jec_filenames.push_back(Form("%s/%s_L3Absolute_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            if (m_sample <= at::Sample::datame)
                m_list_of_jec_filenames.push_back(Form("%s/%s_L2L3Residual_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
        }

        printf("[TrileptonZAnalysisLooper] making jet and MET correctors with: \n");
        for (unsigned int idx = 0; idx < m_list_of_jec_filenames.size(); idx++)
        {
            if (rt::exists(m_list_of_jec_filenames.at(idx)))
                printf("\t%s\n", m_list_of_jec_filenames.at(idx).c_str());
            else
                printf("\tFILE %s doesn't exist.\n", m_list_of_jec_filenames.at(idx).c_str());
        }
        
        jet_corrector = makeJetCorrector(m_list_of_jec_filenames);
        if (not jet_corrector)
        {
            throw std::runtime_error("ERROR: TrileptonZAnalysisLooper: unable to create jet_corrector");
        }
        met_corrector = new MetCorrector(m_list_of_jec_filenames);
        if (not met_corrector)
        {
            throw std::runtime_error("ERROR: TrileptonZAnalysisLooper: unable to create met_corrector");
        }
    }

    // setup MVAs for electron ID
    std::vector<std::string> trigEleWeights;
    trigEleWeights.push_back(Form("%s/Electrons_BDTG_TrigV0_Cat1.weights.xml", ele_mva_path.c_str()));
    trigEleWeights.push_back(Form("%s/Electrons_BDTG_TrigV0_Cat2.weights.xml", ele_mva_path.c_str())); 
    trigEleWeights.push_back(Form("%s/Electrons_BDTG_TrigV0_Cat3.weights.xml", ele_mva_path.c_str())); 
    trigEleWeights.push_back(Form("%s/Electrons_BDTG_TrigV0_Cat4.weights.xml", ele_mva_path.c_str())); 
    trigEleWeights.push_back(Form("%s/Electrons_BDTG_TrigV0_Cat5.weights.xml", ele_mva_path.c_str())); 
    trigEleWeights.push_back(Form("%s/Electrons_BDTG_TrigV0_Cat6.weights.xml", ele_mva_path.c_str())); 
    trigEleMVA = new EGammaMvaEleEstimator();
    trigEleMVA->initialize("BDT", EGammaMvaEleEstimator::kTrig, true, trigEleWeights);

    std::vector<std::string> nontrigEleWeights;
    nontrigEleWeights.push_back(Form("%s/Electrons_BDTG_NonTrigV0_Cat1.weights.xml", ele_mva_path.c_str()));
    nontrigEleWeights.push_back(Form("%s/Electrons_BDTG_NonTrigV0_Cat2.weights.xml", ele_mva_path.c_str())); 
    nontrigEleWeights.push_back(Form("%s/Electrons_BDTG_NonTrigV0_Cat3.weights.xml", ele_mva_path.c_str())); 
    nontrigEleWeights.push_back(Form("%s/Electrons_BDTG_NonTrigV0_Cat4.weights.xml", ele_mva_path.c_str())); 
    nontrigEleWeights.push_back(Form("%s/Electrons_BDTG_NonTrigV0_Cat5.weights.xml", ele_mva_path.c_str())); 
    nontrigEleWeights.push_back(Form("%s/Electrons_BDTG_NonTrigV0_Cat6.weights.xml", ele_mva_path.c_str()));    
    nontrigEleMVA = new EGammaMvaEleEstimator();
    nontrigEleMVA->initialize("BDT", EGammaMvaEleEstimator::kNonTrig, true, nontrigEleWeights);

    // initialize counters
    for (size_t i = 0; i != m_count.size(); i++) {m_count[i]   =0.0;}
    for (size_t i = 0; i != m_count.size(); i++) {m_count_sf[i]=0.0;}
    for (size_t i = 0; i != m_count.size(); i++) {m_count_df[i]=0.0;}
    for (size_t i = 0; i != m_count.size(); i++) {m_count_tf[i]=0.0;}

    for (size_t i = 0; i != m_count_nobtag.size(); i++) {m_count_nobtag[i]   =0.0;}
    for (size_t i = 0; i != m_count_nobtag.size(); i++) {m_count_nobtag_sf[i]=0.0;}
    for (size_t i = 0; i != m_count_nobtag.size(); i++) {m_count_nobtag_df[i]=0.0;}
    for (size_t i = 0; i != m_count_nobtag.size(); i++) {m_count_nobtag_tf[i]=0.0;}

    // set the fake rate histograms
    std::auto_ptr<TFile> fake_rate_file(rt::OpenRootFile(fake_rate_file_name));
    cout << "using FR file : " << fake_rate_file->GetName() << endl;
    h_mufr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get(mfake_rate_hist_name.c_str())->Clone()));
    h_elfr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get(efake_rate_hist_name.c_str())->Clone()));
    if (not h_mufr) {throw std::runtime_error("ERROR: TrileptonZAnalysisLooper: h_mufr40c doesn't exist");}
    h_mufr->SetDirectory(0);
    if (not h_elfr) {throw std::runtime_error("ERROR: TrileptonZAnalysisLooper: h_elfr40c doesn't exist");}
    h_elfr->SetDirectory(0);

    cout << "using mu FR hist : " << h_mufr->GetName() << endl;
    cout << "using el FR hist : " << h_elfr->GetName() << endl;

    // begin job
    BeginJob();
}

// destroy:
TrileptonZAnalysisLooper::~TrileptonZAnalysisLooper()
{
    delete jet_corrector;
    delete met_corrector;
    delete trigEleMVA;
    delete nontrigEleMVA;
}

// function operator: operate on each event
int TrileptonZAnalysisLooper::operator() (long event)
{
    // call base class operator
    return Analyze(event);
}

// members:
void TrileptonZAnalysisLooper::BeginJob()
{
    // initialize branches
    m_evt.Reset();
    m_evt.SetBranches(*m_tree);

    if (m_sync_print)
    {
        cout << "Run | LS | Event | channel | " 
            "Lep1Pt | Lep1Eta | Lep1Phi | Lep1ID | Lep1Iso | "
            "Lep2Pt | Lep2Eta | Lep2Phi | Lep2ID | Lep1Iso | "
            "Lep2Pt | Lep2Eta | Lep2Phi | Lep2ID | Lep1Iso | "
            "MET | HT | nJets | nbJets" << endl;
    }
}


void TrileptonZAnalysisLooper::EndJob()
{
    CTable yield_table;
    yield_table.setTitle("yields for TrileptonZ Analysis 2012");
    yield_table.useTitle();
    yield_table.setTable() (   "eee",         "eem",          "mme",          "mmm",        "all")
        ("count" , m_count[0], m_count[1], m_count[2], m_count[3], m_count[0]+m_count[1]+m_count[2]+m_count[3]);
    yield_table.print();

    // call base class end job to save the tree
    AnalysisWithTree::EndJob();
}

int TrileptonZAnalysisLooper::SetJetCorrector(std::vector<std::string> &list_of_filenames)
{
    printf("[TrileptonZAnalysisLooper] making jet corrector with: \n");
    for (unsigned int idx = 0; idx < list_of_filenames.size(); idx++)
    {
        printf("\t%s\n", list_of_filenames.at(idx).c_str());
    }
    
    jet_corrector = makeJetCorrector(list_of_filenames);
    met_corrector = new MetCorrector(list_of_filenames);
    if (!jet_corrector && !met_corrector) return 1;
    return 0;
}

int TrileptonZAnalysisLooper::SetTriggeringElectronMVA(std::vector<std::string> &list_of_filenames)
{
    printf("[TrileptonZAnalysisLooper] making triggering electron MVA with: \n");
    for (unsigned int idx = 0; idx < list_of_filenames.size(); idx++)
    {
        printf("\t%s\n", list_of_filenames.at(idx).c_str());
    }

    trigEleMVA = new EGammaMvaEleEstimator();
    trigEleMVA->initialize("BDT", EGammaMvaEleEstimator::kTrig, true, list_of_filenames);
    if (!trigEleMVA) return 1;
    return 0;
}

int TrileptonZAnalysisLooper::SetNonTriggeringElectronMVA(std::vector<std::string> &list_of_filenames)
{
    printf("[TrileptonZAnalysisLooper] making non-triggering electron MVA with: \n");
    for (unsigned int idx = 0; idx < list_of_filenames.size(); idx++)
    {
        printf("\t%s\n", list_of_filenames.at(idx).c_str());
    }

    nontrigEleMVA = new EGammaMvaEleEstimator();
    nontrigEleMVA->initialize("BDT", EGammaMvaEleEstimator::kNonTrig, true, list_of_filenames);
    if (!nontrigEleMVA) return 1;
    return 0;
}

int TrileptonZAnalysisLooper::Analyze(long event)
{
    try
    {
        // select specific events
        //if (!(evt_run() == 191247 && evt_lumiBlock() == 189 && evt_event() == 281392234))
        //if (!(evt_run() == 191247 && evt_lumiBlock() == 59 && evt_event() == 91075424))
        //if (!(evt_run() == 191247 && evt_lumiBlock() == 59 && evt_event() == 90509753))
        //if (!(evt_run() == 190736 && evt_lumiBlock() == 143 && evt_event() == 147343009))
        //if (!(evt_run() == 190736 && evt_lumiBlock() == 143 && evt_event() == 147655281))
        //if (!(evt_run() == 191247 && evt_lumiBlock() == 60 && evt_event() == 93008232))  no good vtx
        //if (!(evt_run() == 191247 && evt_lumiBlock() == 60 && evt_event() == 92441355))
        //if (!(evt_run() == 191247 && evt_lumiBlock() == 60 && evt_event() == 93455346))
        //if (!(evt_run() == 191247 && evt_lumiBlock() == 66 && evt_event() == 102084731))
        //if (!(evt_run() == 190736  && evt_lumiBlock() == 144 && evt_event() == 148335250))
        //if 
        //(
        //    not
        //    (
        //        evt_event() == 75924510  || // --> ee event, probably 2012B 13Jul2012 
        //        evt_event() == 58926598  || // --> ee event, probably 2012B 13Jul2012
        //        evt_event() == 261675757 || // , em event, probably 2012B 13Jul2012
        //        evt_event() == 341568433 || // , em event, probably 2012B 13Jul2012
        //        evt_event() == 113167649 || // , em 2021Cv2 
        //        evt_event() == 27490600  || // , ee 2021Cv2 
        //        evt_event() == 663249061    // , ee 2021Cv2 
        //    )
        //)
        //{
        //    return 0;
        //}

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
                    if (m_verbose) {cout << "Bad run and lumi:\t" << tas::evt_run() << ", " << tas::evt_lumiBlock() << endl;}
                    //return 0;
                    m_evt.is_good_lumi = false;
                }
                else
                {
                    m_evt.is_good_lumi = true;
                    if (m_verbose) {cout << "Good run and lumi:\t" << tas::evt_run() << ", " << tas::evt_lumiBlock() << endl;}
                }
            }
        }

        // gen level  
        // --------------------------------------------------------------------------------------------------------- //

        // gen jet info
        if (!evt_isRealData())
        {
            // lepton variables

            int ngen_trilep_hyps = GetGenTrilepHyp();
            if (ngen_trilep_hyps > 0)
            {
                m_evt.gen_dilep_p4   = (m_evt.gen_lep1_p4 + m_evt.gen_lep2_p4);
                m_evt.gen_dilep_mass = m_evt.gen_dilep_p4.mass();
                m_evt.gen_dilep_dphi = rt::DeltaPhi(m_evt.gen_lep1_p4, m_evt.gen_lep2_p4); 
                m_evt.gen_dilep_deta = rt::DeltaEta(m_evt.gen_lep1_p4, m_evt.gen_lep2_p4); 
                m_evt.gen_dilep_dr   = rt::DeltaR(m_evt.gen_lep1_p4, m_evt.gen_lep2_p4);
                m_evt.gen_dilep_type = efftools::getHypType(m_evt.gen_lep1_pdgid, m_evt.gen_lep2_pdgid);
            }

            // gen jets
            m_evt.vgenb_p4       = efftools::getGenBjets(15.0, 2.4);
            m_evt.vgenjets_p4    = efftools::getGenJets(15.0, 2.4);
            m_evt.gen_nbtags     = m_evt.vgenb_p4.size();
            m_evt.gen_njets      = m_evt.vgenjets_p4.size();
            m_evt.gen_ht         = efftools::getGenHT(15.0, 2.4);
            m_evt.vgenjets_p4    = efftools::getGenJets(15.0, 2.4);
        }

        if (m_gen_only)
        {
            // fill event level info 
            m_evt.event_info.FillCommon(m_sample);

            // fill the tree
            m_tree->Fill();

            // continue to next event
            return 0;
        }

        // Event Cleaning
        // --------------------------------------------------------------------------------------------------------- //

        // require standard cleaning 
        if (!cleaning_standardNovember2011()) 
        {
            if (m_verbose) {std::cout << "fails November2011 cleaning requirement" << std::endl;}
            //return 0;
        }

        // Analysis Selections
        // --------------------------------------------------------------------------------------------------------- //

        // jet type
        JetType jet_type = evt_isRealData() ? JETS_TYPE_PF_FAST_CORR_RESIDUAL : JETS_TYPE_PF_FAST_CORR;

        // loop over hypotheses
        std::vector<int> good_hyps;
        for (size_t ihyp = 0; ihyp != hyp_type().size(); ihyp++)
        {                
            // we're looking for Z canddiates, so veto em
            // at::DileptonHypType hyptype = at::hyp_typeToHypType(hyp_type().at(ihyp));
            // if (hyptype == at::DileptonChargeType::EMU)
            //     continue;

            // check hyp mass (no low mass resonances)
            float dilep_mass = sqrt(fabs(hyp_p4().at(ihyp).mass2()));
            if (dilep_mass < 50.0) 
            {
                if (m_verbose) {std::cout << "fails dilepton invariant mass requirement" << std::endl;}
                continue;
            }

            // // check if hyp passes trigger
            // if (!ttv::passesTrigger(hyp_type().at(ihyp)))
            // {
            //     if (m_verbose) {std::cout << "fails trigger requirement" << std::endl;}
            //     continue;
            // }

            // leptons variables
            const LorentzVector& lt_p4 = hyp_lt_p4().at(ihyp);
            const LorentzVector& ll_p4 = hyp_ll_p4().at(ihyp);
            int lt_id = hyp_lt_id().at(ihyp);
            int ll_id = hyp_ll_id().at(ihyp);
            int lt_idx = hyp_lt_index().at(ihyp);
            int ll_idx = hyp_ll_index().at(ihyp);

            // check if hyp passes lepton kinematics
            if (min(lt_p4.pt(), ll_p4.pt()) < 10.0) continue;
            if (!LepPassesEta(lt_id, lt_idx)) continue;
            if (!LepPassesEta(ll_id, ll_idx)) continue;

            // require OS
            if (hyp_lt_charge().at(ihyp) * hyp_ll_charge().at(ihyp) > 0)
            {
                if (m_verbose) {std::cout << "dilepton hypothesis fails as it is same-sign" << std::endl;}
                continue;
            }

            // require hyp to at least pass the FO definition
            if (!isDenominatorLepton(lt_id, lt_idx, ttv::LeptonType::LOOSE)) continue;
            if (!isDenominatorLepton(ll_id, ll_idx, ttv::LeptonType::LOOSE)) continue;
            
            // if we got here, we have a good Z candidate
            good_hyps.push_back(ihyp);
            // print for syncing
            // if (m_sync_print)
            // {
            //     cout << "printing for hyp index " << ihyp << endl;
            //     PrintForSync(ihyp, jet_type, m_jetMetScale, jet_corrector, met_corrector);
            // }

        } // end looper over hypothesis

        // if we don't have a good Z candidate, move onto the next event
        if (good_hyps.size() == 0)
        {
            if (m_verbose) {std::cout << "event fails as it has no Z candidate" << std::endl;}
            return 0;
        }

        // if we're here, we have a Z candidate; let's look for a third lepton candidate
        std::vector<ttv::TrileptonInfo> good_trileps;
        for (unsigned int hidx = 0; hidx < good_hyps.size(); hidx++)
        {
            unsigned int ihyp = good_hyps.at(hidx);
            int lt_id = hyp_lt_id().at(ihyp);
            int ll_id = hyp_ll_id().at(ihyp);
            unsigned int lt_idx = hyp_lt_index().at(ihyp);
            unsigned int ll_idx = hyp_ll_index().at(ihyp);

            // muons first
            for (unsigned int midx = 0; midx < mus_p4().size(); midx++)
            {
                int lep3_id = -13 * mus_charge().at(midx);

                if (mus_p4().at(midx).pt() < 10.) continue;
                if (fabs(mus_p4().at(midx).eta()) > mu_eta) continue;
                if (abs(lt_id) == 13 && lt_idx == midx) continue;
                if (abs(ll_id) == 13 && ll_idx == midx) continue;
                if (!isDenominatorLepton(lep3_id, midx, ttv::LeptonType::LOOSE)) continue;

                // if we made it here, we have a trilepton hypothesis, store it
                ttv::TrileptonInfo good_trilep(ihyp, lep3_id, midx);
                good_trileps.push_back(good_trilep);
            }

            // now electrons
            for (unsigned int eidx = 0; eidx < els_p4().size(); eidx++)
            {
                int lep3_id = -11 * els_charge().at(eidx);

                if (els_p4().at(eidx).pt() < 10.) continue;
                if (fabs(els_p4().at(eidx).eta()) > ele_eta) continue;
                if (abs(lt_id) == 11 && lt_idx == eidx) continue;
                if (abs(ll_id) == 11 && ll_idx == eidx) continue;
                if (!isDenominatorLepton(lep3_id, eidx, ttv::LeptonType::LOOSE)) continue;

                // if we made it here, we have a trilepton hypothesis, store it
                ttv::TrileptonInfo good_trilep(ihyp, lep3_id, eidx);
                good_trileps.push_back(good_trilep);
            }
        }
        
        // if we don't have a trilepton candidate, move onto the next event
        if (good_trileps.size() == 0)
        {
            if (m_verbose) {std::cout << "event fails as it has no trilepton candidate" << std::endl;}
            return 0;
        }
        
        // loop over trilepton candidates and find the best one
        int best_trilep_index = -1;
        for (unsigned int tidx = 0; tidx < good_trileps.size();  tidx++)
        {
            ttv::TrileptonInfo trilep_cand = good_trileps.at(tidx);

            // require trilepton candidate passes trigger
            if (!ttv::passesTrigger(trilep_cand)) continue;

            if (best_trilep_index < 0)
            {
                best_trilep_index = tidx;
                continue;
            }

            // choose Z-->ee/mm over em
            bool best_pair = (abs(good_trileps.at(best_trilep_index).z.lep1.id) == abs(good_trileps.at(best_trilep_index).z.lep2.id));
            bool current_pair = (abs(trilep_cand.z.lep1.id) == abs(trilep_cand.z.lep2.id));
            if (current_pair && !best_pair)
            {
                best_trilep_index = tidx;
                continue;
            }

            // choose best Z candidate (i.e. closetst to Z mass)
            float best_diff    = fabs(good_trileps.at(best_trilep_index).z.mass() - zmass);
            float current_diff = fabs(trilep_cand.z.mass() - zmass);            
            if (current_diff < best_diff)
            {
                best_trilep_index = tidx;
                continue;
            }

            // choose W-->munu over W-->enu
            if (abs(trilep_cand.w.id) > abs(good_trileps.at(best_trilep_index).w.id))
            {
                best_trilep_index = tidx;
                continue;
            }
            else if (abs(trilep_cand.w.id) < abs(good_trileps.at(best_trilep_index).w.id))
                continue;
            else
            {
                if (trilep_cand.sumpt() > good_trileps.at(best_trilep_index).sumpt())
                {
                    best_trilep_index = tidx;
                    continue;
                }
                else continue;
            }
        }
        
        if (best_trilep_index < 0)
        {
            if (m_verbose) {std::cout << "ERROR: didn't find best trilepton hypothesis even though there was at least one candidate!" << std::endl;}
            return 0;
        }
        
        ttv::TrileptonInfo best_trilep_hyp = good_trileps.at(best_trilep_index);
        
        //
        // now we have our trilepton hypothesis
        // set tree variables
        //
        // --------------------------------------------------------------------------------------------------------- //

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

        // fill event level info 
        m_evt.event_info.FillCommon(m_sample);

        // fill the dilepton and single lepton independent variables 
        m_evt.dilep.FillCommon(best_trilep_hyp.z.hyp_index);
        m_evt.lep3.FillCommon(best_trilep_hyp.w.id, best_trilep_hyp.w.idx);

        // fill analysis specific branches 
        m_evt.vtxw = vtxw;

        // event level info
        if (not jet_corrector)
        {
            m_evt.event_info.pfmet          = evt_pfmet_type1cor();  // do we ever use the uncorrected pfmet?
            m_evt.event_info.pfmet_phi      = evt_pfmetPhi_type1cor();
        }
        else
        {
            std::pair<float, float> pcor_met = met_corrector->getCorrectedMET();
            m_evt.event_info.pfmet = pcor_met.first;
            m_evt.event_info.pfmet_phi = pcor_met.second;
        }
        m_evt.event_info.uncorpfmet     = evt_pfmet();
        m_evt.event_info.uncorpfmet_phi = evt_pfmetPhi();
        const float met                 = m_evt.event_info.pfmet;
        const float met_phi             = m_evt.event_info.pfmet_phi;
        
        // SS specific event level info
        m_evt.dilep.lep1.mt   = rt::Mt(m_evt.dilep.lep1.p4, met, met_phi);  // calculated against the higher pT lepton
        m_evt.dilep.lep2.mt   = rt::Mt(m_evt.dilep.lep2.p4, met, met_phi);  // calculated against the higher pT lepton
        m_evt.lep3.mt   = rt::Mt(m_evt.lep3.p4, met, met_phi);  // calculated against the higher pT lepton

        // need to get vector of good leptons for overlap removal
        std::vector<LorentzVector> good_leps = ttv::getGoodLeptons(ttv::LeptonType::LOOSE, /*pt=*/ 20.0, /*mu_eta=*/ 2.4, /*ele_eta=*/ 2.5);
        
        // now need to push back the p4s for the trilepton hypothesis
        good_leps.push_back(best_trilep_hyp.z.lep1.p4());
        good_leps.push_back(best_trilep_hyp.z.lep2.p4());
        good_leps.push_back(best_trilep_hyp.w.p4());

        if (not jet_corrector)
        {
            m_evt.ht           = ttv::sumJetPt(good_leps , jet_type , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/0);
            m_evt.njets15      = ttv::nJets   (good_leps , jet_type , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/0);
            m_evt.njets30      = ttv::nJets   (good_leps , jet_type , /*dR=*/0.5 , /*jet_pt>*/30.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/0);
            m_evt.nbtags_loose = ttv::nBtaggedJets(good_leps , jet_type , JETS_BTAG_CSVL , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/0);
            m_evt.nbtags_tight = ttv::nBtaggedJets(good_leps , jet_type , JETS_BTAG_CSVM , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/0);
        }
        else
        {
            m_evt.ht           = ttv::sumJetPt(good_leps , jet_corrector , jet_type , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/0);
            m_evt.njets15      = ttv::nJets   (good_leps , jet_corrector , jet_type , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/0);
            m_evt.njets30      = ttv::nJets   (good_leps , jet_corrector , jet_type , /*dR=*/0.5 , /*jet_pt>*/30.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/0);
            m_evt.nbtags_loose = ttv::nBtaggedJets(good_leps , jet_corrector , jet_type , JETS_BTAG_CSVL , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/0);
            m_evt.nbtags_tight = ttv::nBtaggedJets(good_leps , jet_corrector , jet_type , JETS_BTAG_CSVM , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/0);
        }

        m_evt.clean        = cleaning_standardNovember2011();

        // let's set remaining single lepton variables
        // first for lepton 1
        m_evt.dilep.lep1.passes_id  = ttv::isGoodLepton(best_trilep_hyp.z.lep1.id, best_trilep_hyp.z.lep1.idx, ttv::LeptonType::LOOSE);
        m_evt.dilep.lep1.passes_iso = ttv::isIsolatedLepton(best_trilep_hyp.z.lep1.id, best_trilep_hyp.z.lep1.idx, ttv::LeptonType::LOOSE);
        m_evt.dilep.lep1.is_num     = ttv::isNumeratorLepton(best_trilep_hyp.z.lep1.id, best_trilep_hyp.z.lep1.idx, ttv::LeptonType::LOOSE);
        m_evt.dilep.lep1.is_fo      = ttv::isDenominatorLepton(best_trilep_hyp.z.lep1.id, best_trilep_hyp.z.lep1.idx, ttv::LeptonType::LOOSE) && !m_evt.dilep.lep1.is_num;
        int lep1_id_bitmask_tmp = 0;
        if (ttv::isDenominatorLepton(best_trilep_hyp.z.lep1.id, best_trilep_hyp.z.lep1.idx, ttv::LeptonType::LOOSE)) lep1_id_bitmask_tmp |= (1<<TrileptonZTree::LeptonType::LOOSE_DENOM);
        if (ttv::isDenominatorLepton(best_trilep_hyp.z.lep1.id, best_trilep_hyp.z.lep1.idx, ttv::LeptonType::TIGHT)) lep1_id_bitmask_tmp |= (1<<TrileptonZTree::LeptonType::TIGHT_DENOM);
        if (ttv::isGoodLepton(best_trilep_hyp.z.lep1.id, best_trilep_hyp.z.lep1.idx, ttv::LeptonType::LOOSE)) lep1_id_bitmask_tmp |= (1<<TrileptonZTree::LeptonType::LOOSE_NUM);
        if (ttv::isGoodLepton(best_trilep_hyp.z.lep1.id, best_trilep_hyp.z.lep1.idx, ttv::LeptonType::TIGHT)) lep1_id_bitmask_tmp |= (1<<TrileptonZTree::LeptonType::TIGHT_NUM);
        m_evt.lep1_id_bitmask = lep1_id_bitmask_tmp;

        // for lepton 2
        m_evt.dilep.lep2.passes_id  = ttv::isGoodLepton(best_trilep_hyp.z.lep2.id, best_trilep_hyp.z.lep2.idx, ttv::LeptonType::LOOSE);
        m_evt.dilep.lep2.passes_iso = ttv::isIsolatedLepton(best_trilep_hyp.z.lep2.id, best_trilep_hyp.z.lep2.idx, ttv::LeptonType::LOOSE);
        m_evt.dilep.lep2.is_num     = ttv::isNumeratorLepton(best_trilep_hyp.z.lep2.id, best_trilep_hyp.z.lep2.idx, ttv::LeptonType::LOOSE);
        m_evt.dilep.lep2.is_fo      = ttv::isDenominatorLepton(best_trilep_hyp.z.lep2.id, best_trilep_hyp.z.lep2.idx, ttv::LeptonType::LOOSE) && !m_evt.dilep.lep2.is_num;
        int lep2_id_bitmask_tmp = 0;
        if (ttv::isDenominatorLepton(best_trilep_hyp.z.lep2.id, best_trilep_hyp.z.lep2.idx, ttv::LeptonType::LOOSE)) lep2_id_bitmask_tmp |= (1<<TrileptonZTree::LeptonType::LOOSE_DENOM);
        if (ttv::isDenominatorLepton(best_trilep_hyp.z.lep2.id, best_trilep_hyp.z.lep2.idx, ttv::LeptonType::TIGHT)) lep2_id_bitmask_tmp |= (1<<TrileptonZTree::LeptonType::TIGHT_DENOM);
        if (ttv::isGoodLepton(best_trilep_hyp.z.lep2.id, best_trilep_hyp.z.lep2.idx, ttv::LeptonType::LOOSE)) lep2_id_bitmask_tmp |= (1<<TrileptonZTree::LeptonType::LOOSE_NUM);
        if (ttv::isGoodLepton(best_trilep_hyp.z.lep2.id, best_trilep_hyp.z.lep2.idx, ttv::LeptonType::TIGHT)) lep2_id_bitmask_tmp |= (1<<TrileptonZTree::LeptonType::TIGHT_NUM);
        m_evt.lep2_id_bitmask = lep2_id_bitmask_tmp;

        // and finally for lepton 3
        m_evt.lep3.passes_id  = ttv::isGoodLepton(best_trilep_hyp.w.id, best_trilep_hyp.w.idx, ttv::LeptonType::LOOSE);
        m_evt.lep3.passes_iso = ttv::isIsolatedLepton(best_trilep_hyp.w.id, best_trilep_hyp.w.idx, ttv::LeptonType::LOOSE);
        m_evt.lep3.is_num     = ttv::isNumeratorLepton(best_trilep_hyp.w.id, best_trilep_hyp.w.idx, ttv::LeptonType::LOOSE);
        m_evt.lep3.is_fo      = ttv::isDenominatorLepton(best_trilep_hyp.w.id, best_trilep_hyp.w.idx, ttv::LeptonType::LOOSE) && !m_evt.lep3.is_num;
        int lep3_id_bitmask_tmp = 0;
        if (ttv::isDenominatorLepton(best_trilep_hyp.w.id, best_trilep_hyp.w.idx, ttv::LeptonType::LOOSE)) lep3_id_bitmask_tmp |= (1<<TrileptonZTree::LeptonType::LOOSE_DENOM);
        if (ttv::isDenominatorLepton(best_trilep_hyp.w.id, best_trilep_hyp.w.idx, ttv::LeptonType::TIGHT)) lep3_id_bitmask_tmp |= (1<<TrileptonZTree::LeptonType::TIGHT_DENOM);
        if (ttv::isGoodLepton(best_trilep_hyp.w.id, best_trilep_hyp.w.idx, ttv::LeptonType::LOOSE)) lep3_id_bitmask_tmp |= (1<<TrileptonZTree::LeptonType::LOOSE_NUM);
        if (ttv::isGoodLepton(best_trilep_hyp.w.id, best_trilep_hyp.w.idx, ttv::LeptonType::TIGHT)) lep3_id_bitmask_tmp |= (1<<TrileptonZTree::LeptonType::TIGHT_NUM);
        m_evt.lep3_id_bitmask = lep3_id_bitmask_tmp;

        if (m_evt.dilep.lep1.is_num && m_evt.dilep.lep1.is_num && m_evt.lep3.is_num) m_evt.event_type = ttv2012::EventType::TRILEPTONZ;
        else if (m_evt.dilep.lep1.is_fo && m_evt.dilep.lep1.is_fo && m_evt.lep3.is_fo) m_evt.event_type = ttv2012::EventType::TRILEPTONZ_TF;
        else if (m_evt.dilep.lep1.is_num && m_evt.dilep.lep1.is_num && m_evt.lep3.is_fo ||
                 m_evt.dilep.lep1.is_num && m_evt.dilep.lep1.is_fo && m_evt.lep3.is_num ||
                 m_evt.dilep.lep1.is_fo && m_evt.dilep.lep1.is_num && m_evt.lep3.is_num) m_evt.event_type = ttv2012::EventType::TRILEPTONZ_SF;
        else if (m_evt.dilep.lep1.is_num && m_evt.dilep.lep1.is_fo && m_evt.lep3.is_fo ||
                 m_evt.dilep.lep1.is_fo && m_evt.dilep.lep1.is_fo && m_evt.lep3.is_num ||
                 m_evt.dilep.lep1.is_fo && m_evt.dilep.lep1.is_num && m_evt.lep3.is_fo) m_evt.event_type = ttv2012::EventType::TRILEPTONZ_DF;
        

        m_evt.dilep.lep1.cordetiso   = m_evt.dilep.lep1.detiso   - (log(m_evt.dilep.lep1.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.dilep.lep1.p4.pt()); // check that I have the correct formula 
        m_evt.dilep.lep1.cordetiso04 = m_evt.dilep.lep1.detiso04 - (log(m_evt.dilep.lep1.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.dilep.lep1.p4.pt()); // check that I have the correct formula 
        m_evt.dilep.lep1.corpfiso    = (abs(best_trilep_hyp.z.lep1.id)==11) ? samesign::electronIsolationPF2012(best_trilep_hyp.z.lep1.idx) : muonIsoValuePF2012_deltaBeta(best_trilep_hyp.z.lep1.idx);
        m_evt.dilep.lep1.corpfiso04  = -999999.0;   // this is not implemented yet 
        m_evt.dilep.lep1.effarea     = EffectiveArea03(best_trilep_hyp.z.lep1.id, best_trilep_hyp.z.lep1.idx);
        m_evt.dilep.lep1.effarea04   = EffectiveArea04(best_trilep_hyp.z.lep1.id, best_trilep_hyp.z.lep1.idx);
        m_evt.dilep.lep1.dbeta       = (abs(best_trilep_hyp.z.lep1.id)==13) ? mus_isoR03_pf_PUPt().at(best_trilep_hyp.z.lep1.idx) : -99999.0;
        m_evt.dilep.lep1.dbeta04     = (abs(best_trilep_hyp.z.lep1.id)==13) ? mus_isoR04_pf_PUPt().at(best_trilep_hyp.z.lep1.idx) : -99999.0;
        m_evt.dilep.lep1.is_conv     = (abs(best_trilep_hyp.z.lep1.id)==11) ? isFromConversionMIT(best_trilep_hyp.z.lep1.idx) : false;
        m_evt.lep1_wfr               = GetFakeRateValue(best_trilep_hyp.z.lep1.id, best_trilep_hyp.z.lep1.idx);
        m_evt.lep1_ele_mva_trig      = (abs(best_trilep_hyp.z.lep1.id)==11) ? trigEleMVA->mvaValue(best_trilep_hyp.z.lep1.idx, false) : -99999.0;
        m_evt.lep1_ele_mva_nontrig   = (abs(best_trilep_hyp.z.lep1.id)==11) ? nontrigEleMVA->mvaValue(best_trilep_hyp.z.lep1.idx, false) : -99999.0;

        m_evt.dilep.lep2.cordetiso   = m_evt.dilep.lep2.detiso   - (log(m_evt.dilep.lep2.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.dilep.lep2.p4.pt()); // check that I have the correct formula 
        m_evt.dilep.lep2.cordetiso04 = m_evt.dilep.lep2.detiso04 - (log(m_evt.dilep.lep2.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.dilep.lep2.p4.pt()); // check that I have the correct formula 
        m_evt.dilep.lep2.corpfiso    = (abs(best_trilep_hyp.z.lep2.id)==11) ? samesign::electronIsolationPF2012(best_trilep_hyp.z.lep2.idx) : muonIsoValuePF2012_deltaBeta(best_trilep_hyp.z.lep2.idx);
        m_evt.dilep.lep2.corpfiso04  = -999999.0;   // this is not implemented yet 
        m_evt.dilep.lep2.effarea     = EffectiveArea03(best_trilep_hyp.z.lep2.id, best_trilep_hyp.z.lep2.idx);
        m_evt.dilep.lep2.effarea04   = EffectiveArea04(best_trilep_hyp.z.lep2.id, best_trilep_hyp.z.lep2.idx);
        m_evt.dilep.lep2.dbeta       = (abs(best_trilep_hyp.z.lep2.id)==13) ? mus_isoR03_pf_PUPt().at(best_trilep_hyp.z.lep2.idx) : -99999.0;
        m_evt.dilep.lep2.dbeta04     = (abs(best_trilep_hyp.z.lep2.id)==13) ? mus_isoR04_pf_PUPt().at(best_trilep_hyp.z.lep2.idx) : -99999.0;
        m_evt.dilep.lep2.is_conv     = (abs(best_trilep_hyp.z.lep2.id)==11) ? isFromConversionMIT(best_trilep_hyp.z.lep2.idx) : false;
        m_evt.lep2_wfr               = GetFakeRateValue(best_trilep_hyp.z.lep2.id, best_trilep_hyp.z.lep2.idx);
        m_evt.lep2_ele_mva_trig      = (abs(best_trilep_hyp.z.lep2.id)==11) ? trigEleMVA->mvaValue(best_trilep_hyp.z.lep2.idx, false) : -99999.0;
        m_evt.lep2_ele_mva_nontrig   = (abs(best_trilep_hyp.z.lep2.id)==11) ? nontrigEleMVA->mvaValue(best_trilep_hyp.z.lep2.idx, false) : -99999.0;

        m_evt.lep3.cordetiso         = m_evt.lep3.detiso   - (log(m_evt.lep3.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep3.p4.pt()); // check that I have the correct formula 
        m_evt.lep3.cordetiso04       = m_evt.lep3.detiso04 - (log(m_evt.lep3.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep3.p4.pt()); // check that I have the correct formula 
        m_evt.lep3.corpfiso          = (abs(best_trilep_hyp.w.id)==11) ? samesign::electronIsolationPF2012(best_trilep_hyp.w.idx) : muonIsoValuePF2012_deltaBeta(best_trilep_hyp.w.idx);
        m_evt.lep3.corpfiso04        = -999999.0;   // this is not implemented yet 
        m_evt.lep3.effarea           = EffectiveArea03(best_trilep_hyp.w.id, best_trilep_hyp.w.idx);
        m_evt.lep3.effarea04         = EffectiveArea04(best_trilep_hyp.w.id, best_trilep_hyp.w.idx);
        m_evt.lep3.dbeta             = (abs(best_trilep_hyp.w.id)==13) ? mus_isoR03_pf_PUPt().at(best_trilep_hyp.w.idx) : -99999.0;
        m_evt.lep3.dbeta04           = (abs(best_trilep_hyp.w.id)==13) ? mus_isoR04_pf_PUPt().at(best_trilep_hyp.w.idx) : -99999.0;
        m_evt.lep3.is_conv           = (abs(best_trilep_hyp.w.id)==11) ? isFromConversionMIT(best_trilep_hyp.w.idx) : false;
        m_evt.lep3_wfr               = GetFakeRateValue(best_trilep_hyp.w.id, best_trilep_hyp.w.idx);
        m_evt.lep3_ele_mva_trig      = (abs(best_trilep_hyp.w.id)==11) ? trigEleMVA->mvaValue(best_trilep_hyp.w.idx, false) : -99999.0;
        m_evt.lep3_ele_mva_nontrig   = (abs(best_trilep_hyp.w.id)==11) ? nontrigEleMVA->mvaValue(best_trilep_hyp.w.idx, false) : -99999.0;

        if (not jet_corrector)
        {
            m_evt.ht           = ttv::sumJetPt(good_leps , jet_type , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/0);
            m_evt.njets15      = ttv::nJets   (good_leps , jet_type , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/0);
            m_evt.njets30      = ttv::nJets   (good_leps , jet_type , /*dR=*/0.5 , /*jet_pt>*/30.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/0);
            m_evt.nbtags_loose = ttv::nBtaggedJets(good_leps , jet_type , JETS_BTAG_CSVL , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/0);
            m_evt.nbtags_tight = ttv::nBtaggedJets(good_leps , jet_type , JETS_BTAG_CSVM , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/0);
        }
        else
        {
            m_evt.ht           = ttv::sumJetPt(good_leps , jet_corrector , jet_type , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/0);
            m_evt.njets15      = ttv::nJets   (good_leps , jet_corrector , jet_type , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/0);
            m_evt.njets30      = ttv::nJets   (good_leps , jet_corrector , jet_type , /*dR=*/0.5 , /*jet_pt>*/30.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/0);
            m_evt.nbtags_loose = ttv::nBtaggedJets(good_leps , jet_corrector , jet_type , JETS_BTAG_CSVL , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/0);
            m_evt.nbtags_tight = ttv::nBtaggedJets(good_leps , jet_corrector , jet_type , JETS_BTAG_CSVM , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/0);
        }

        // njets, nbtags, HT and MET for JES systematics
        if (!evt_isRealData()) 
        {
            if (not jet_corrector || not met_corrector)
            {
                m_evt.ht_up           = ttv::sumJetPt(good_leps , jet_type , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/1);
                m_evt.njets15_up      = ttv::nJets   (good_leps , jet_type , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/1);
                m_evt.njets30_up      = ttv::nJets   (good_leps , jet_type , /*dR=*/0.5 , /*jet_pt>*/30.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/1);
                m_evt.nbtags_loose_up = ttv::nBtaggedJets(good_leps , jet_type , JETS_BTAG_CSVL , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/1);
                m_evt.nbtags_tight_up = ttv::nBtaggedJets(good_leps , jet_type , JETS_BTAG_CSVM , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/1);

                m_evt.ht_dn           = ttv::sumJetPt(good_leps , jet_type , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/-1);
                m_evt.njets15_dn      = ttv::nJets   (good_leps , jet_type , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/-1);
                m_evt.njets30_dn      = ttv::nJets   (good_leps , jet_type , /*dR=*/0.5 , /*jet_pt>*/30.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/-1);
                m_evt.nbtags_loose_dn = ttv::nBtaggedJets(good_leps , jet_type , JETS_BTAG_CSVL , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/-1);
                m_evt.nbtags_tight_dn = ttv::nBtaggedJets(good_leps , jet_type , JETS_BTAG_CSVM , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/-1);

                // MET
                ROOT::Math::XYVector cmet_up;
                ROOT::Math::XYVector cmet_dn;
                float metx_up = evt_pfmet_type1cor() * cos(evt_pfmetPhi_type1cor());
                float metx_dn = evt_pfmet_type1cor() * cos(evt_pfmetPhi_type1cor());
                float mety_up = evt_pfmet_type1cor() * sin(evt_pfmetPhi_type1cor());
                float mety_dn = evt_pfmet_type1cor() * sin(evt_pfmetPhi_type1cor());
                // get uncorrected jets
                vector<LorentzVector> ujets = ttv::getJets(good_leps, jet_type, /*dR=*/0.5, /*jet_pt>*/10.0, /*|eta|<*/5.0, 1.0, 0);
                for (size_t u = 0; u != ujets.size(); u++) 
                {
                    float px   = ujets.at(u).px();
                    float py   = ujets.at(u).py();
                    float pt   = ujets.at(u).pt();
                    float eta  = ujets.at(u).pt();
                    float corr_up = getJetMetSyst(/*jetMetScale=*/ 1, pt, eta);
                    float corr_dn = getJetMetSyst(/*jetMetScale=*/-1, pt, eta);
                    metx_up = metx_up - (corr_up-1.0)*px;
                    mety_up = mety_up - (corr_up-1.0)*py;
                    metx_dn = metx_dn - (corr_dn-1.0)*px;
                    mety_dn = mety_dn - (corr_dn-1.0)*py;
                }
                cmet_up.SetXY(metx_up, mety_up);
                cmet_dn.SetXY(metx_dn, mety_dn);
                m_evt.pfmet_up = cmet_up.r(); 
                m_evt.pfmet_phi_up  = cmet_up.phi();
                m_evt.pfmet_dn = cmet_dn.r(); 
                m_evt.pfmet_phi_dn = cmet_dn.phi();
            }
            else
            {
                m_evt.ht_up           = ttv::sumJetPt(good_leps , jet_corrector , jet_type , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/1);
                m_evt.njets15_up      = ttv::nJets   (good_leps , jet_corrector , jet_type , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/1);
                m_evt.njets30_up      = ttv::nJets   (good_leps , jet_corrector , jet_type , /*dR=*/0.5 , /*jet_pt>*/30.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/1);
                m_evt.nbtags_loose_up = ttv::nBtaggedJets(good_leps , jet_corrector , jet_type , JETS_BTAG_CSVL , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/1);
                m_evt.nbtags_tight_up = ttv::nBtaggedJets(good_leps , jet_corrector , jet_type , JETS_BTAG_CSVM , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/1);

                m_evt.ht_dn           = ttv::sumJetPt(good_leps , jet_corrector , jet_type , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/-1);
                m_evt.njets15_dn      = ttv::nJets   (good_leps , jet_corrector , jet_type , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/-1);
                m_evt.njets30_dn      = ttv::nJets   (good_leps , jet_corrector , jet_type , /*dR=*/0.5 , /*jet_pt>*/30.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/-1);
                m_evt.nbtags_loose_dn = ttv::nBtaggedJets(good_leps , jet_corrector , jet_type , JETS_BTAG_CSVL , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/-1);
                m_evt.nbtags_tight_dn = ttv::nBtaggedJets(good_leps , jet_corrector , jet_type , JETS_BTAG_CSVM , /*dR=*/0.5 , /*jet_pt>*/15.0 , /*|eta|<*/2.4 , /*rescale=*/1.0 , /*systFlag=*/-1);

                // MET
                ROOT::Math::XYVector cmet_up;
                ROOT::Math::XYVector cmet_dn;
                float metx_up = met * cos(met_phi);
                float metx_dn = met * cos(met_phi);
                float mety_up = met * sin(met_phi);
                float mety_dn = met * sin(met_phi);
                // get uncorrected jets
                vector<LorentzVector> ujets = ttv::getJets(good_leps, jet_corrector, jet_type, /*dR=*/0.5, /*jet_pt>*/10.0, /*|eta|<*/5.0, 1.0, 0);
                for (size_t u = 0; u != ujets.size(); u++) 
                {
                    float px   = ujets.at(u).px();
                    float py   = ujets.at(u).py();
                    float pt   = ujets.at(u).pt();
                    float eta  = ujets.at(u).pt();
                    float corr_up = getJetMetSyst(/*jetMetScale=*/ 1, pt, eta);
                    float corr_dn = getJetMetSyst(/*jetMetScale=*/-1, pt, eta);
                    metx_up = metx_up - (corr_up-1.0)*px;
                    mety_up = mety_up - (corr_up-1.0)*py;
                    metx_dn = metx_dn - (corr_dn-1.0)*px;
                    mety_dn = mety_dn - (corr_dn-1.0)*py;
                }
                cmet_up.SetXY(metx_up, mety_up);
                cmet_dn.SetXY(metx_dn, mety_dn);
                m_evt.pfmet_up = cmet_up.r(); 
                m_evt.pfmet_phi_up  = cmet_up.phi();
                m_evt.pfmet_dn = cmet_dn.r(); 
                m_evt.pfmet_phi_dn = cmet_dn.phi();
            }
        }

        // electron isolation correction variables
        m_evt.rho     = evt_ww_rho_vor();
        m_evt.rho_iso = evt_kt6pf_foregiso_rho();

        // eff and scale factors
        if (!evt_isRealData())
        {
            // scale factor for trigger efficiency
            m_evt.sf_dileptrig = dilepTriggerScaleFactor(best_trilep_hyp.z.hyp_index);

            // scale factor for lepton reconstruction efficiency
            // m_evt.sf_lepeff      = dileptonTagAndProbeScaleFactor(hyp_idx);
            m_evt.dilep.lep1.sf_lepeff = tagAndProbeScaleFactor(m_evt.dilep.lep1.pdgid, m_evt.dilep.lep1.p4.pt(), m_evt.dilep.lep1.p4.eta());
            m_evt.dilep.lep2.sf_lepeff = tagAndProbeScaleFactor(m_evt.dilep.lep2.pdgid, m_evt.dilep.lep2.p4.pt(), m_evt.dilep.lep2.p4.eta());
            m_evt.lep3.sf_lepeff       = tagAndProbeScaleFactor(m_evt.lep3.pdgid, m_evt.lep3.p4.pt(), m_evt.lep3.p4.eta());
        }

        // jet/bjet info 
        if (not jet_corrector)
        {
            m_evt.vjets_p4  = ttv::getJets(good_leps, jet_type,                            /*dR=*/0.5, /*jet_pt>*/15.0, /*|eta|<*/2.4, /*rescale=*/1.0, /*systFlag=*/m_jetMetScale);
            m_evt.vbjets_p4 = ttv::getBtaggedJets(good_leps, jet_type, JETS_BTAG_CSVL,     /*dR=*/0.5, /*jet_pt>*/15.0, /*|eta|<*/2.4, /*rescale=*/1.0, /*systFlag=*/m_jetMetScale);
        }
        else
        {
            m_evt.vjets_p4  = ttv::getJets(good_leps, jet_corrector, jet_type,                            /*dR=*/0.5, /*jet_pt>*/15.0, /*|eta|<*/2.4, /*rescale=*/1.0, /*systFlag=*/m_jetMetScale);
            m_evt.vbjets_p4 = ttv::getBtaggedJets(good_leps, jet_corrector, jet_type, JETS_BTAG_CSVL,     /*dR=*/0.5, /*jet_pt>*/15.0, /*|eta|<*/2.4, /*rescale=*/1.0, /*systFlag=*/m_jetMetScale);
        }

        SetBtagDiscriminator(m_evt.vjets_p4, m_evt.vbjets_disc, JETS_BTAG_CSVL);
        m_evt.bjets_dr12 = (m_evt.nbtags_loose>=2) ? rt::DeltaR(m_evt.vbjets_p4.at(0), m_evt.vbjets_p4.at(1)) : -999999.0;

        vector<LorentzVector> temp_bjets_p4 = m_evt.vbjets_p4;
        if (!temp_bjets_p4.empty())
        {
            // nearest to lep1
            std::sort(temp_bjets_p4.begin(), temp_bjets_p4.begin(), SortByDeltaR<LorentzVector>(m_evt.dilep.lep1.p4));
            m_evt.lep1_nearbjet_p4 = temp_bjets_p4.front();
            m_evt.lep1_nearbjet_dr = rt::DeltaR(m_evt.dilep.lep1.p4, temp_bjets_p4.front());

            // nearest to lep2
            std::sort(temp_bjets_p4.begin(), temp_bjets_p4.begin(), SortByDeltaR<LorentzVector>(m_evt.dilep.lep2.p4));
            m_evt.lep2_nearbjet_p4 = temp_bjets_p4.front();
            m_evt.lep2_nearbjet_dr = rt::DeltaR(m_evt.dilep.lep2.p4, temp_bjets_p4.front());

            // nearest to lep3
            std::sort(temp_bjets_p4.begin(), temp_bjets_p4.begin(), SortByDeltaR<LorentzVector>(m_evt.lep3.p4));
            m_evt.lep3_nearbjet_p4 = temp_bjets_p4.front();
            m_evt.lep3_nearbjet_dr = rt::DeltaR(m_evt.lep3.p4, temp_bjets_p4.front());
        }

        vector<LorentzVector> temp_jets_p4 = m_evt.vjets_p4;
        if (!temp_jets_p4.empty())
        {            
            // nearest to lep1
            std::sort(temp_jets_p4.begin(), temp_jets_p4.end(), SortByDeltaR<LorentzVector>(m_evt.dilep.lep1.p4));
            m_evt.lep1_nearjet_p4 = temp_jets_p4.front();
            m_evt.lep1_nearjet_dr = rt::DeltaR(m_evt.dilep.lep1.p4, temp_jets_p4.front());

            // nearest to lep2
            std::sort(temp_jets_p4.begin(), temp_jets_p4.end(), SortByDeltaR<LorentzVector>(m_evt.dilep.lep2.p4));
            m_evt.lep2_nearjet_p4 = temp_jets_p4.front();
            m_evt.lep2_nearjet_dr = rt::DeltaR(m_evt.dilep.lep2.p4, temp_jets_p4.front());

            // nearest to lep3
            std::sort(temp_jets_p4.begin(), temp_jets_p4.end(), SortByDeltaR<LorentzVector>(m_evt.lep3.p4));
            m_evt.lep3_nearjet_p4 = temp_jets_p4.front();
            m_evt.lep3_nearjet_dr = rt::DeltaR(m_evt.lep3.p4, temp_jets_p4.front());
        }

        if (abs(m_evt.dilep.lep1.pdgid) == 11) {
            std::pair<int,double> closest_el = std::make_pair(-1, 99.);
            for (unsigned int eidx = 0; eidx < els_p4().size(); eidx++) {
                
                if (els_p4().at(eidx).pt() < 5.) continue;
                if (fabs(els_p4().at(eidx).eta()) > 2.5) continue;
                if (m_evt.dilep.lep1.charge * els_charge().at(eidx) > 0) continue;

                double iso_val = samesign::electronIsolationPF2012(eidx);
                if (iso_val > 0.2) continue;

                using namespace wp2012;
                electronIdComponent_t passAllVetoCuts = DETAIN | DPHIIN | SIGMAIETAIETA | HOE | D0VTX | DZVTX;
                electronIdComponent_t vetoid = electronId_WP2012(eidx, VETO);
                if ((passAllVetoCuts & vetoid) != passAllVetoCuts)
                    continue;

                double dr = rt::DeltaR(els_p4().at(eidx), m_evt.dilep.lep1.p4);
                if (dr < closest_el.second)
                    closest_el = std::make_pair(eidx, dr);
            }

            if (closest_el.first >= 0) {
                m_evt.lep1_nearlep_p4 = els_p4().at(closest_el.first);
                m_evt.lep1_nearlep_id = -11 * els_charge().at(closest_el.first);
                m_evt.lep1_nearlep_dr = closest_el.second;
            }                
        }

        if (abs(m_evt.dilep.lep2.pdgid) == 11) {
            std::pair<int,double> closest_el = std::make_pair(-1, 99.);
            for (unsigned int eidx = 0; eidx < els_p4().size(); eidx++) {
                
                if (els_p4().at(eidx).pt() < 5.) continue;
                if (fabs(els_p4().at(eidx).eta()) > 2.5) continue;
                if (m_evt.dilep.lep2.charge * els_charge().at(eidx) > 0) continue;

                double iso_val = samesign::electronIsolationPF2012(eidx);
                if (iso_val > 0.2) continue;

                using namespace wp2012;
                electronIdComponent_t passAllVetoCuts = DETAIN | DPHIIN | SIGMAIETAIETA | HOE | D0VTX | DZVTX;
                electronIdComponent_t vetoid = electronId_WP2012(eidx, VETO);
                if ((passAllVetoCuts & vetoid) != passAllVetoCuts)
                    continue;

                double dr = rt::DeltaR(els_p4().at(eidx), m_evt.dilep.lep2.p4);
                if (dr < closest_el.second)
                    closest_el = std::make_pair(eidx, dr);
            }

            if (closest_el.first >= 0) {
                m_evt.lep2_nearlep_p4 = els_p4().at(closest_el.first);
                m_evt.lep2_nearlep_id = -11 * els_charge().at(closest_el.first);
                m_evt.lep2_nearlep_dr = closest_el.second;
            }                
        }

        if (abs(m_evt.lep3.pdgid) == 11) {
            std::pair<int,double> closest_el = std::make_pair(-1, 99.);
            for (unsigned int eidx = 0; eidx < els_p4().size(); eidx++) {
                
                if (els_p4().at(eidx).pt() < 5.) continue;
                if (fabs(els_p4().at(eidx).eta()) > 2.5) continue;
                if (m_evt.lep3.charge * els_charge().at(eidx) > 0) continue;

                double iso_val = samesign::electronIsolationPF2012(eidx);
                if (iso_val > 0.2) continue;

                using namespace wp2012;
                electronIdComponent_t passAllVetoCuts = DETAIN | DPHIIN | SIGMAIETAIETA | HOE | D0VTX | DZVTX;
                electronIdComponent_t vetoid = electronId_WP2012(eidx, VETO);
                if ((passAllVetoCuts & vetoid) != passAllVetoCuts)
                    continue;

                double dr = rt::DeltaR(els_p4().at(eidx), m_evt.lep3.p4);
                if (dr < closest_el.second)
                    closest_el = std::make_pair(eidx, dr);
            }

            if (closest_el.first >= 0) {
                m_evt.lep3_nearlep_p4 = els_p4().at(closest_el.first);
                m_evt.lep3_nearlep_id = -11 * els_charge().at(closest_el.first);
                m_evt.lep3_nearlep_dr = closest_el.second;
            }                
        }

        if (abs(m_evt.dilep.lep1.pdgid) == 13) {
            std::pair<int,double> closest_mu = std::make_pair(-1, 99.);
            for (unsigned int midx = 0; midx < mus_p4().size(); midx++) {
                
                if (mus_p4().at(midx).pt() < 5.) continue;
                if (fabs(mus_p4().at(midx).eta()) > 2.4) continue;
                if (m_evt.dilep.lep1.charge * mus_charge().at(midx) > 0) continue;

                double iso_val = muonIsoValuePF2012_deltaBeta(midx);
                if (iso_val > 0.2) continue;

                if (!passes_muid_wp2012(midx, mu2012_tightness::LOOSE))
                    continue;

                // make a dz cut
                int vtxidx = firstGoodVertex();
                int ctfidx = mus_trkidx().at(midx);
                if (ctfidx < 0) return false;
                std::pair<double, double> cordz = trks_dz_pv(ctfidx, vtxidx);
                if (fabs(cordz.first) > 0.2) continue; // same as for electrons
                
                double dr = rt::DeltaR(mus_p4().at(midx), m_evt.dilep.lep1.p4);
                if (dr < closest_mu.second)
                    closest_mu = std::make_pair(midx, dr);
            }

            if (closest_mu.first >= 0) {
                m_evt.lep1_nearlep_p4 = mus_p4().at(closest_mu.first);
                m_evt.lep1_nearlep_id = -13 * mus_charge().at(closest_mu.first);
                m_evt.lep1_nearlep_dr = closest_mu.second;
            }                
        }

        if (abs(m_evt.dilep.lep2.pdgid) == 13) {
            std::pair<int,double> closest_mu = std::make_pair(-1, 99.);
            for (unsigned int midx = 0; midx < mus_p4().size(); midx++) {
                
                if (mus_p4().at(midx).pt() < 5.) continue;
                if (fabs(mus_p4().at(midx).eta()) > 2.4) continue;
                if (m_evt.dilep.lep2.charge * mus_charge().at(midx) > 0) continue;

                double iso_val = muonIsoValuePF2012_deltaBeta(midx);
                if (iso_val > 0.2) continue;

                if (!passes_muid_wp2012(midx, mu2012_tightness::LOOSE))
                    continue;

                // make a dz cut
                int vtxidx = firstGoodVertex();
                int ctfidx = mus_trkidx().at(midx);
                if (ctfidx < 0) return false;
                std::pair<double, double> cordz = trks_dz_pv(ctfidx, vtxidx);
                if (fabs(cordz.first) > 0.2) continue; // same as for electrons
                
                double dr = rt::DeltaR(mus_p4().at(midx), m_evt.dilep.lep2.p4);
                if (dr < closest_mu.second)
                    closest_mu = std::make_pair(midx, dr);
            }

            if (closest_mu.first >= 0) {
                m_evt.lep2_nearlep_p4 = mus_p4().at(closest_mu.first);
                m_evt.lep2_nearlep_id = -13 * mus_charge().at(closest_mu.first);
                m_evt.lep2_nearlep_dr = closest_mu.second;
            }                
        }

        if (abs(m_evt.lep3.pdgid) == 13) {
            std::pair<int,double> closest_mu = std::make_pair(-1, 99.);
            for (unsigned int midx = 0; midx < mus_p4().size(); midx++) {
                
                if (mus_p4().at(midx).pt() < 5.) continue;
                if (fabs(mus_p4().at(midx).eta()) > 2.4) continue;
                if (m_evt.lep3.charge * mus_charge().at(midx) > 0) continue;

                double iso_val = muonIsoValuePF2012_deltaBeta(midx);
                if (iso_val > 0.2) continue;

                if (!passes_muid_wp2012(midx, mu2012_tightness::LOOSE))
                    continue;

                // make a dz cut
                int vtxidx = firstGoodVertex();
                int ctfidx = mus_trkidx().at(midx);
                if (ctfidx < 0) return false;
                std::pair<double, double> cordz = trks_dz_pv(ctfidx, vtxidx);
                if (fabs(cordz.first) > 0.2) continue; // same as for electrons
                
                double dr = rt::DeltaR(mus_p4().at(midx), m_evt.lep3.p4);
                if (dr < closest_mu.second)
                    closest_mu = std::make_pair(midx, dr);
            }

            if (closest_mu.first >= 0) {
                m_evt.lep3_nearlep_p4 = mus_p4().at(closest_mu.first);
                m_evt.lep3_nearlep_id = -13 * mus_charge().at(closest_mu.first);
                m_evt.lep3_nearlep_dr = closest_mu.second;
            }                
        }

        // Fill the tree
        m_tree->Fill();

        // printout
        if (m_evt.is_good_lumi)
        {
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

float TrileptonZAnalysisLooper::GetFakeRateValue(int lep_id, int lep_idx) const 
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

int TrileptonZAnalysisLooper::GetGenTrilepHyp(float zwin)
{
    std::vector<std::pair<std::pair<int, int>, LorentzVector> > vgenps; // stores pdgid, index into genps block, p4
    for (unsigned int idx = 0; idx < cms2.genps_p4().size(); idx++)
    {
        if (cms2.genps_status().at(idx) != 3) continue;
        int id = cms2.genps_id().at(idx);
        int absid = abs(id);
        if (absid != 11 && absid != 13 && absid != 15) continue;
        if (absid == 11 || absid == 13)
        {
            std::pair<int, int> tmp_pair = std::make_pair(id, idx);
            vgenps.push_back(std::make_pair(tmp_pair, cms2.genps_p4().at(idx)));
        }
        else
        {
            int idx_ = -1;
            int id_ = 0;
            LorentzVector p4 = LorentzVector(0,0,0,0);
            for (unsigned int didx = 0; didx < cms2.genps_lepdaughter_id().at(idx).size(); didx++)
            {
                int did = cms2.genps_lepdaughter_id().at(idx).at(didx);
                int absdid = abs(did);
                if (absdid != 11 && absdid != 13) continue;
                if (cms2.genps_lepdaughter_p4().at(idx).at(didx).pt() < p4.pt()) continue;
                p4 = cms2.genps_lepdaughter_p4().at(idx).at(didx);
                idx_ = didx;
                id_ = did;
            }
            if (idx_ >= 0)
            {
                std::pair<int, int> tmp_pair = std::make_pair(id_, idx_);
                vgenps.push_back(std::make_pair(tmp_pair, p4));
            }
        }
    }
    
    if (vgenps.size() < 3) return 0;

    std::vector<std::pair<std::pair<int, int>, int> > trilep_cands; // stores index into vgenps vector of 3 gen particles making trilep hypothesis
    for (unsigned int idx = 0; idx < vgenps.size(); idx++)
    {        
        int first_id = vgenps.at(idx).first.first;
        LorentzVector first_p4 = vgenps.at(idx).second;

        std::vector<int> zcands;
        for (unsigned int sidx = idx+1; sidx < vgenps.size(); sidx++)
        {
            int second_id = vgenps.at(sidx).first.first;
            LorentzVector second_p4 = vgenps.at(sidx).second;            
            
            if (first_id * second_id != -121 && first_id * second_id != 169) continue;
            LorentzVector zcand = first_p4 + second_p4;
            if (fabs(zcand.mass() - zmass) > zwin) continue;

            //
            // if we made it here, we have a zcand, let's store it
            //
            zcands.push_back(sidx);
        }

        for (unsigned int zidx = 0; zidx < zcands.size(); zidx++)
        {
            for (unsigned int widx = idx+1; widx < vgenps.size(); widx++)
            {
                if (widx == (unsigned int)zcands.at(zidx)) continue;
                std::pair<int, int> tmp_pair = std::make_pair(idx, zcands.at(zidx));
                trilep_cands.push_back(std::make_pair(tmp_pair, widx));
            }
        }
    }

    int nels, nmus, ntaus;
    m_evt.gen_nleps = leptonGenpCount_lepTauDecays(nels, nmus, ntaus);
    
    if (trilep_cands.size() == 0) return 0;
    if (trilep_cands.size() == 1)
    {
        m_evt.gen_lep1_p4    = vgenps.at(trilep_cands.at(0).first.first).second;
        m_evt.gen_lep2_p4    = vgenps.at(trilep_cands.at(0).first.second).second;
        m_evt.gen_lep3_p4    = vgenps.at(trilep_cands.at(0).second).second;            
        m_evt.gen_mt         = rt::Mt(m_evt.gen_lep3_p4, gen_met(), gen_metPhi());
        m_evt.gen_lep1_pdgid = vgenps.at(trilep_cands.at(0).first.first).first.first;
        m_evt.gen_lep2_pdgid = vgenps.at(trilep_cands.at(0).first.second).first.first;
        m_evt.gen_lep3_pdgid = vgenps.at(trilep_cands.at(0).second).first.first;

        // set parentage information
        m_evt.is_gen_w = abs(genps_id_mother().at(vgenps.at(trilep_cands.at(0).second).first.second)) == 24;
        m_evt.is_gen_z = abs(genps_id_mother().at(vgenps.at(trilep_cands.at(0).first.first).first.second)) == 23
            && abs(genps_id_mother().at(vgenps.at(trilep_cands.at(0).first.second).first.second)) == 23;            
    }
        
    //
    // if there is more than 1, things get a bit messier now
    // to simplify, we only support there being two for now
    //
    if (trilep_cands.size() == 2)
    {
        int good_index = 0;

        LorentzVector tmp1_lep1_p4    = vgenps.at(trilep_cands.at(0).first.first).second;
        LorentzVector tmp1_lep2_p4    = vgenps.at(trilep_cands.at(0).first.second).second;
        LorentzVector tmp1_lep3_p4    = vgenps.at(trilep_cands.at(0).second).second;            

        LorentzVector tmp2_lep1_p4    = vgenps.at(trilep_cands.at(1).first.first).second;
        LorentzVector tmp2_lep2_p4    = vgenps.at(trilep_cands.at(1).first.second).second;
        LorentzVector tmp2_lep3_p4    = vgenps.at(trilep_cands.at(1).second).second;                        

        //
        // if one has leptons out of acceptance and other doesn't
        // we'll take the one with leptons in acceptance
        //
        int tmp1_lep_in_acc = 0;
        int tmp2_lep_in_acc = 0;
        if (tmp1_lep1_p4.pt() > 20. && fabs(tmp1_lep1_p4.eta()) < 2.4) ++tmp1_lep_in_acc;
        if (tmp1_lep2_p4.pt() > 20. && fabs(tmp1_lep2_p4.eta()) < 2.4) ++tmp1_lep_in_acc;
        if (tmp1_lep3_p4.pt() > 20. && fabs(tmp1_lep3_p4.eta()) < 2.4) ++tmp1_lep_in_acc;
        if (tmp2_lep1_p4.pt() > 20. && fabs(tmp2_lep1_p4.eta()) < 2.4) ++tmp2_lep_in_acc;
        if (tmp2_lep2_p4.pt() > 20. && fabs(tmp2_lep2_p4.eta()) < 2.4) ++tmp2_lep_in_acc;
        if (tmp2_lep3_p4.pt() > 20. && fabs(tmp2_lep3_p4.eta()) < 2.4) ++tmp2_lep_in_acc;

        if (tmp1_lep_in_acc > tmp2_lep_in_acc) good_index = 0;
        else if (tmp2_lep_in_acc > tmp1_lep_in_acc) good_index = 1;
        else
        {
            LorentzVector z1 = tmp1_lep1_p4 + tmp1_lep2_p4;
            float diff1 = fabs(z1.mass()-zmass);
            LorentzVector z2 = tmp2_lep1_p4 + tmp2_lep2_p4;
            float diff2 = fabs(z2.mass()-zmass);
            if (diff1 < diff2) good_index = 0;
            else if (diff2 < diff1) good_index = 1;
            else
            {
                float sumpt1 = tmp1_lep1_p4.pt() + tmp1_lep2_p4.pt() + tmp1_lep3_p4.pt();
                float sumpt2 = tmp2_lep1_p4.pt() + tmp2_lep2_p4.pt() + tmp2_lep3_p4.pt();
                if (sumpt1 > sumpt2) good_index = 0;
                else if (sumpt2 > sumpt1) good_index = 1;
            }
        }
            
        m_evt.gen_lep1_p4    = vgenps.at(trilep_cands.at(good_index).first.first).second;
        m_evt.gen_lep2_p4    = vgenps.at(trilep_cands.at(good_index).first.second).second;
        m_evt.gen_lep3_p4    = vgenps.at(trilep_cands.at(good_index).second).second;            
        m_evt.gen_mt         = rt::Mt(m_evt.gen_lep3_p4, gen_met(), gen_metPhi());
        m_evt.gen_lep1_pdgid = vgenps.at(trilep_cands.at(good_index).first.first).first.first;
        m_evt.gen_lep2_pdgid = vgenps.at(trilep_cands.at(good_index).first.second).first.first;
        m_evt.gen_lep3_pdgid = vgenps.at(trilep_cands.at(good_index).second).first.first;            

        // set parentage information
        m_evt.is_gen_w = abs(genps_id_mother().at(vgenps.at(trilep_cands.at(good_index).second).first.second)) == 24;
        m_evt.is_gen_z = abs(genps_id_mother().at(vgenps.at(trilep_cands.at(good_index).first.first).first.second)) == 23
            && abs(genps_id_mother().at(vgenps.at(trilep_cands.at(good_index).first.second).first.second)) == 23;            
    }

    return trilep_cands.size();
}

bool TrileptonZAnalysisLooper::LepPassesEta(int id, int index)
{
    if (abs(id) == 11)
        return (fabs(els_p4().at(index).eta()) < ele_eta);
    else if (abs(id) == 13)
        return (fabs(mus_p4().at(index).eta()) < mu_eta);
    else
        return false;
}
