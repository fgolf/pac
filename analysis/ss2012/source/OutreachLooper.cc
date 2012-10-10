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
            }
            else
            {
                matched.push_back(false);
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
            }
            else
            {
                matched.push_back(false);
            }
        }
        matched.push_back(false);
    }
    return matched;
}

vector<float> GetFitParameters(TH1* hist)
{
	vector<float> params;

	// get fit function name
	string func_name = "";
	if      (rt::string_contains(hist->GetName(), "btagpt"   )) {func_name = "fitf_btag";}
	else if (rt::string_contains(hist->GetName(), "el_pt"    )) {func_name = "efitf";}
	else if (rt::string_contains(hist->GetName(), "mu_pt"    )) {func_name = "mfitf";}
	else if (rt::string_contains(hist->GetName(), "genmet30" )) {func_name = "fitf1";}
	else if (rt::string_contains(hist->GetName(), "genmet50" )) {func_name = "fitf2";}
	else if (rt::string_contains(hist->GetName(), "genmet120")) {func_name = "fitf3";}
	else if (rt::string_contains(hist->GetName(), "ht200"    )) {func_name = "fitf1";}
	else if (rt::string_contains(hist->GetName(), "ht320"    )) {func_name = "fitf2";}
	else
	{
		cout << "invalid hist (" << hist->GetName() << "). exiting" << endl;
		return params;
	}

	// get parameters
	TF1* func = hist->GetFunction(func_name.c_str());
    double* params_array = func->GetParameters(); 
	int num_params       = func->GetNpar(); 
	for (int i = 0; i != num_params; i++)
	{
		//cout << "parm " << i << " = " << params_array[i] << endl;
        params.push_back(static_cast<float>(params_array[i]));
	}

	return params;
}

float GetPtEfficiencyWeight(float pt, TH1* hist) 
{
    vector<float> pars = GetFitParameters(hist);
    float par0 = pars[0];
    float par1 = pars[1];
    float par2 = pars[2];

    float arg = (pt - 20.) / par2;
    float eff = par0 * TMath::Erf(arg) + par1 * (1. - TMath::Erf(arg));
    return eff;
}

float GetMETEfficiencyWeight(float met, TH1* hist) 
{
    vector<float> pars = GetFitParameters(hist);
    float par0 = pars[0];
    float par1 = pars[1];
    float par2 = pars[2];

    float arg = (met - par1) / par2;
    float eff = 0.5 * par0 * (1 + TMath::Erf(arg));
    return eff;
}

float GetHTEfficiencyWeight(float ht, TH1* hist) 
{
    vector<float> pars = GetFitParameters(hist);
    float par0 = pars[0];
    float par1 = pars[1];
    float par2 = pars[2];

    float arg = (ht - par1) / par2;
    float eff = 0.5 * par0 * (1 + TMath::Erf(arg));
    return eff;
}

float GetBtagEfficiency(float bpt, TH1* hist)
{
//------------------------------
// Stupid function:
// linear up to x1
// flat between x1 and x2
// linear again above x2
//------------------------------
    vector<float> pars = GetFitParameters(hist);
    float par0 = pars[0];
    float par1 = pars[1];
    float par2 = pars[2];

    static float x1  = 90.0;
    static float x2  = 170.0;
    static float eff = 0.0;
    
    if (bpt < x1)
        eff = (bpt - x1) * par0 + par1;
    else if (bpt < x2)
        eff = par1;
    else
        eff = par1 + (bpt - x2) * par2;

    return eff;
}

float GetBtagEfficiencyWeight(const std::vector<LorentzVector>& vgbs,  TH1* hist) 
{

    if (vgbs.size() == 2) 
    {
        float e0 = GetBtagEfficiency(vgbs.at(0).pt(), hist);
        float e1 = GetBtagEfficiency(vgbs.at(1).pt(), hist);
        float ineff = (1 - e0) * (1 - e1) + e0 * (1 - e1) + (1 - e0) * e1;

        return (1 - ineff);
    }
    else if (vgbs.size() == 3) 
    {
        float e0 = GetBtagEfficiency(vgbs.at(0).pt(), hist);
        float e1 = GetBtagEfficiency(vgbs.at(1).pt(), hist);
        float e2 = GetBtagEfficiency(vgbs.at(2).pt(), hist);
        float ineff = (1 - e0) * (1 - e1) * (1 - e2) 
            + e0 * (1 - e1) * (1 - e2) 
            + (1 - e0) * e1 * (1 - e2) 
            + (1 - e0) * (1 - e1) * e2;

        return (1 - ineff);
    }
    else if (vgbs.size() == 4) 
    {
        float e0 = GetBtagEfficiency(vgbs.at(0).pt(), hist);
        float e1 = GetBtagEfficiency(vgbs.at(1).pt(), hist);
        float e2 = GetBtagEfficiency(vgbs.at(2).pt(), hist);
        float e3 = GetBtagEfficiency(vgbs.at(3).pt(), hist);
        float ineff = (1 - e0) * (1 - e1) * (1 - e2) * (1 - e3) 
            + e0 * (1 - e1) * (1 - e2) * (1 - e3) 
            + (1 - e0) * e1 * (1 - e2) * (1 - e3) 
            + (1 - e0) * (1 - e1) * e2 * (1 - e3) 
            + (1 - e0) * (1 - e1) * (1 - e2) * e3;

        return (1 - ineff);
    }
    else if (vgbs.size() > 4) 
    {
        // std::cout << "FOUND AN EVENT WITH MORE THAN 4 B PARTONS AT STATUS 3!!!" << std::endl;
        return 1.0;
    }

    return 0.0;
}
        

// outreach looper implementation
// ------------------------------------------------------------------------------------------------ //

// construct:
OutreachLooper::OutreachLooper
(
    const std::string& root_file_name,
    const Sample::value_type& sample,
    double luminosity,
    const std::string& fit_eff_file,
    const std::string& vtxreweight_file_name,
    bool is_fastsim,
    bool sparms,
    bool verbose
)
    : AnalysisWithTree(root_file_name, "tree", "baby tree for SS2012 outreach")
    , m_sample(sample)
    , m_fit_sample_name(rt::string_remove_all(rt::basename(fit_eff_file), "_or"))
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

    // set the histograms
    if (not fit_eff_file.empty())
    {
        cout << "filling fit functions with " << fit_eff_file << endl;
        rt::TH1Container hc_temp(fit_eff_file);

        // btag
        h_btagpt.reset(dynamic_cast<TH1F*>(hc_temp[Form("h_eff_%s_btagpt", m_fit_sample_name.c_str())]->Clone())); 

        // lepton
        h_el_pt.reset(dynamic_cast<TH1F*>(hc_temp[Form("h_eff_%s_el_pt", m_fit_sample_name.c_str())]->Clone())); 
        h_mu_pt.reset(dynamic_cast<TH1F*>(hc_temp[Form("h_eff_%s_mu_pt", m_fit_sample_name.c_str())]->Clone())); 

        // met
        h_genmet30.reset( dynamic_cast<TH1F*>(hc_temp[Form("h_eff_%s_genmet30" , m_fit_sample_name.c_str())]->Clone())); 
        h_genmet50.reset( dynamic_cast<TH1F*>(hc_temp[Form("h_eff_%s_genmet50" , m_fit_sample_name.c_str())]->Clone()));
        h_genmet120.reset(dynamic_cast<TH1F*>(hc_temp[Form("h_eff_%s_genmet120", m_fit_sample_name.c_str())]->Clone())); 

        // ht
        h_ht200.reset(dynamic_cast<TH1F*>(hc_temp[Form("h_eff_%s_ht200", m_fit_sample_name.c_str())]->Clone())); 
        h_ht320.reset(dynamic_cast<TH1F*>(hc_temp[Form("h_eff_%s_ht320", m_fit_sample_name.c_str())]->Clone())); 

        // take ownership
        h_btagpt->SetDirectory(NULL);
        h_el_pt->SetDirectory(NULL);
        h_mu_pt->SetDirectory(NULL);
        h_genmet30->SetDirectory(NULL);
        h_genmet50->SetDirectory(NULL);
        h_genmet120->SetDirectory(NULL);
        h_ht200->SetDirectory(NULL);
        h_ht320->SetDirectory(NULL);
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

    // hists
    rt::TH1Container& hc = m_hist_container;

    hc.Add(new TH1F("h_bpt_num", "h_bpt_num", 8, 0, 400));
    hc.Add(new TH1F("h_bpt_den", "h_bpt_den", 8, 0, 400));

}

void OutreachLooper::EndJob()
{
    m_hist_container.Write("plots/outreach2/btag_test.root");
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
        bool from_tau1 = abs(best_gen_hyp.first.id_  ) == 15;
        bool from_tau2 = abs(best_gen_hyp.second.id_ ) == 15;
        int  id1  = from_tau1 ? best_gen_hyp.first.did_   : best_gen_hyp.first.id_;
        int  idx1 = from_tau1 ? best_gen_hyp.first.didx_  : best_gen_hyp.first.idx_;
        int  id2  = from_tau2 ? best_gen_hyp.second.did_  : best_gen_hyp.second.id_;
        int  idx2 = from_tau2 ? best_gen_hyp.second.didx_ : best_gen_hyp.second.idx_;
        GenParticleStruct gen1 = best_gen_hyp.first;
        GenParticleStruct gen2 = best_gen_hyp.second;

        // put in the order of increasing pT
        if (genps_p4().at(idx1).pt() < genps_p4().at(idx2).pt())
        {
            std::swap(id1 ,  id2);
            std::swap(idx1, idx2);
            std::swap(from_tau1, from_tau2);
            std::swap(gen1, gen2);
        }

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
        if (abs(best_gen_hyp.second.id_) == 15)
        {
            p42 = genps_lepdaughter_p4().at(gen2.idx_).at(idx2);
        }
        else
        {
            p42 = genps_p4().at(idx2);
        }
        
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
        std::vector<unsigned int> indexJets = getRecoJets(gen1, gen2);

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
        m_evt.lep1_from_tau  = from_tau1;

        // lep2
        m_evt.lep2_gen_p4    = p42;
        m_evt.lep2_gen_pdgid = id2;
        m_evt.lep2_from_tau  = from_tau2;

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
            std::vector<unsigned int> indexJets = getRecoJets(gen1, gen2);
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
            //m_evt.reco_ht        = samesign::sumJetPt(hyp_idx, jet_type,                      /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, 0);
            //m_evt.reco_njets     = samesign::nJets(hyp_idx, jet_type,                         /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt2>*/20.0, 1.0, 0);
            //m_evt.reco_nbtags    = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM,  /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, 0);
            //m_evt.reco_vbjets_p4 = samesign::getBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM,/*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, 0); 
            //m_evt.reco_vjets_p4  = samesign::getJets(hyp_idx, jet_type,                       /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt2>*/20.0, 1.0, 0); 

            //m_evt.gen_vjets_matched  = MatchedGenJets(m_evt.reco_vjets_p4, m_evt.gen_vjets_p4);
            //m_evt.gen_vbjets_matched = MatchedGenBjets(m_evt.reco_vbjets_p4, m_evt.gen_vbjets_p4);
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


            // classification
            m_evt.reco_is_ss = (event_type==DileptonChargeType::SS);
            m_evt.reco_is_os = (event_type==DileptonChargeType::OS);

            // leptons variables
            LorentzVector l1_p4 = hyp_lt_p4().at(hyp_idx);
            LorentzVector l2_p4 = hyp_ll_p4().at(hyp_idx);
            int l1_id           = hyp_lt_id().at(hyp_idx);
            int l2_id           = hyp_ll_id().at(hyp_idx);
            int l1_idx          = hyp_lt_index().at(hyp_idx);
            int l2_idx          = hyp_ll_index().at(hyp_idx);

            // order leptons by pT
            if (l1_p4.pt() < l2_p4.pt())
            {
                std::swap(l1_p4 , l2_p4 );
                std::swap(l1_id , l2_id );
                std::swap(l1_idx, l2_idx);
            }

            m_evt.lep1_pdgid      = l1_id; 
            m_evt.lep1_p4         = l1_p4; 
            m_evt.lep1_passes_id  = samesign::isGoodLepton(l1_id, l1_idx);
            m_evt.lep1_passes_iso = samesign::isIsolatedLepton(l1_id, l1_idx);
            m_evt.lep1_num        = samesign::isNumeratorLepton(l1_id, l1_idx);
            m_evt.lep1_iso        = (abs(l1_id)==11) ? samesign::electronIsolationPF2012(l1_idx) : muonIsoValuePF2012_deltaBeta(l1_idx);

            m_evt.lep2_pdgid      = l2_id; 
            m_evt.lep2_p4         = l2_p4; 
            m_evt.lep2_passes_id  = samesign::isGoodLepton(l2_id, l2_idx);
            m_evt.lep2_passes_iso = samesign::isIsolatedLepton(l2_id, l2_idx);
            m_evt.lep2_num        = samesign::isNumeratorLepton(l2_id, l2_idx);
            m_evt.lep2_iso        = (abs(l2_id)==11) ? samesign::electronIsolationPF2012(l2_idx) : muonIsoValuePF2012_deltaBeta(l2_idx);

            // determine if matched to gen
            int matched_gen_lep1_idx = getRecoLepton(gen1).second;
            int matched_gen_lep2_idx = getRecoLepton(gen2).second;
            //m_evt.lep1_matched = (m_evt.lep1_gen_pdgid == m_evt.lep1_pdgid && matched_gen_lep1_idx == l1_idx);
            //m_evt.lep2_matched = (m_evt.lep2_gen_pdgid == m_evt.lep2_pdgid && matched_gen_lep2_idx == l2_idx);
            m_evt.lep1_matched = (matched_gen_lep1_idx>-1);
            m_evt.lep2_matched = (matched_gen_lep2_idx>-1);

            if (m_verbose)
            {
                cout << Form("lep1: gen id %d, gen pt %f, reco id %d, reco pt %f, matched %d, dr %f", m_evt.lep1_gen_pdgid, m_evt.lep1_gen_p4.pt(), l1_id, l1_p4.pt(), m_evt.lep1_matched, rt::DeltaR(m_evt.lep1_gen_p4, l1_p4)) << endl;  
                cout << Form("lep2: gen id %d, gen pt %f, reco id %d, reco pt %f, matched %d, dr %f", m_evt.lep2_gen_pdgid, m_evt.lep2_gen_p4.pt(), l2_id, l2_p4.pt(), m_evt.lep2_matched, rt::DeltaR(m_evt.lep2_gen_p4, l2_p4)) << endl;  
                cout << endl;
            }

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

        // weights
        // --------------------------------------------------------------------------------------------------------- //

        // met
        m_evt.metw30  = h_genmet30  ? GetMETEfficiencyWeight(m_evt.event_info.gen_met, h_genmet30.get())  : -999999.0; 
        m_evt.metw50  = h_genmet50  ? GetMETEfficiencyWeight(m_evt.event_info.gen_met, h_genmet50.get())  : -999999.0;
        m_evt.metw120 = h_genmet120 ? GetMETEfficiencyWeight(m_evt.event_info.gen_met, h_genmet120.get()) : -999999.0; 

        // ht
        m_evt.htw200 = h_ht200 ? GetHTEfficiencyWeight(m_evt.gen_ht, h_ht200.get()) : -999999.0; 
        m_evt.htw320 = h_ht320 ? GetHTEfficiencyWeight(m_evt.gen_ht, h_ht320.get()) : -999999.0; 

        // btag
        m_evt.btagw = h_btagpt ? GetBtagEfficiencyWeight(m_evt.gen_vbjets_p4, h_btagpt.get()) : -999999.0; 

        // lepton
        if (abs(m_evt.lep1_gen_pdgid)==11) { m_evt.pt1w = h_el_pt ? GetPtEfficiencyWeight(m_evt.lep1_gen_p4.pt(), h_el_pt.get()) : -999999.0; }
        if (abs(m_evt.lep2_gen_pdgid)==11) { m_evt.pt2w = h_el_pt ? GetPtEfficiencyWeight(m_evt.lep2_gen_p4.pt(), h_el_pt.get()) : -999999.0; }
        if (abs(m_evt.lep1_gen_pdgid)==13) { m_evt.pt1w = h_mu_pt ? GetPtEfficiencyWeight(m_evt.lep1_gen_p4.pt(), h_mu_pt.get()) : -999999.0; }
        if (abs(m_evt.lep2_gen_pdgid)==13) { m_evt.pt2w = h_mu_pt ? GetPtEfficiencyWeight(m_evt.lep2_gen_p4.pt(), h_mu_pt.get()) : -999999.0; }

        // test
        // --------------------------------------------------------------------------------------------------------- //

        rt::TH1Container& hc = m_hist_container;

        // btag eff
        if (m_evt.event_info.gen_met>50 && m_evt.gen_ht>200 && m_evt.gen_nbtags>=2)
        {
            for (size_t i = 0; i != m_evt.gen_vbjets_p4.size(); i++)
            {
                hc["h_bpt_den"]->Fill(m_evt.gen_vbjets_p4.at(i).pt(), m_evt.btagw);
                if (m_evt.gen_vbjets_matched.at(i))
                {
                    hc["h_bpt_num"]->Fill(m_evt.gen_vbjets_p4.at(i).pt(), 1.0);
                }
            }
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
    metw30          = -999999.0;
    metw50          = -999999.0;
    metw120         = -999999.0;
    btagw           = -999999.0;
    pt1w            = -999999.0;
    pt2w            = -999999.0;
    htw             = -999999.0;
    htw200          = -999999.0;
    htw320          = -999999.0;


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
    tree.Branch("metw30"          , &metw30          , "metw30/F"          );
    tree.Branch("metw50"          , &metw50          , "metw50/F"          );
    tree.Branch("metw120"         , &metw120         , "metw120/F"         );
    tree.Branch("btagw"           , &btagw           , "btagw/F"           );
    tree.Branch("pt1w"            , &pt1w            , "pt1w/F"            );
    tree.Branch("pt2w"            , &pt2w            , "pt2w/F"            );
    tree.Branch("htw200"          , &htw200          , "htw200/F"          );
    tree.Branch("htw320"          , &htw320          , "htw320/F"          );

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
