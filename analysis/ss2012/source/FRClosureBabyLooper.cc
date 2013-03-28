#include "FRClosureBabyLooper.h"

// c++
#include <stdexcept>
#include <algorithm>
#include <fstream>

// cms2
#include "ssSelections.h"
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
#include "SameSignTree.h"
#include "at/Predicates.h"
#include "at/DileptonHypType.h"
#include "at/DileptonChargeType.h"
#include "at/VtxReweight.h"
#include "at/GoodRun.h"
#include "at/PrintIdIsoInfo.h"
#include "at/MCBtagCount.h"
#include "rt/RootTools.h"
#include "CTable.h"
#include "GenParticleStruct.h"
#include "EfficiencyModelTools.h"
#include "ScaleFactors.h"
#include "TTbarBreakDown.h"
#include "SignalBinInfo.h"

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
using namespace ss;

// get the best hyp
struct HypInfo
{
    HypInfo(int i, const at::DileptonChargeType::value_type& c, const at::DileptonHypType::value_type& h);
    int idx;
    at::DileptonChargeType::value_type charge_type;
    at::DileptonHypType::value_type hyp_type;

    // scalar sum pT between the two leptons
    float pt() const;

    // lower means higher priority
    bool operator < (const HypInfo& rhs) const;  
};

HypInfo::HypInfo(int i, const at::DileptonChargeType::value_type& c, const at::DileptonHypType::value_type& h)
    : idx(i)
    , charge_type(c)
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
    // charge type
    if (charge_type < rhs.charge_type) {return true;}
    if (charge_type > rhs.charge_type) {return false;}
    
    // hyp type 
    if (hyp_type < rhs.hyp_type) {return true;}
    if (hyp_type > rhs.hyp_type) {return false;}

    // sum pt
    if (pt() > rhs.pt())  {return true;}
    if (pt() <= rhs.pt()) {return false;}

    return false;
}

// set then numerator bool
bool IsNumerator(const HypInfo& hyp, bool is_lt, bool use_el_eta)
{
    if (hyp.charge_type == DileptonChargeType::static_size)
    {
        return false;
    }
    switch (hyp.charge_type)
    {
    case DileptonChargeType::DF: return false; break;
    case DileptonChargeType::SS: return true; break;
    case DileptonChargeType::SF: 
    {
        bool lt_num = samesign::isNumeratorLepton(cms2.hyp_lt_id().at(hyp.idx), cms2.hyp_lt_index().at(hyp.idx), use_el_eta);
        bool ll_num = samesign::isNumeratorLepton(cms2.hyp_ll_id().at(hyp.idx), cms2.hyp_ll_index().at(hyp.idx), use_el_eta);
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

bool IsDenominator(const HypInfo& hyp, bool is_lt, bool use_el_eta)
{
    if (hyp.charge_type == DileptonChargeType::static_size)
    {
        return false;
    }
    switch (hyp.charge_type)
    {
    case DileptonChargeType::DF: return true; break;
    case DileptonChargeType::SS: return false; break;
    case DileptonChargeType::SF: 
    {
        bool lt_num = samesign::isNumeratorLepton(cms2.hyp_lt_id().at(hyp.idx), cms2.hyp_lt_index().at(hyp.idx), use_el_eta);
        bool ll_num = samesign::isNumeratorLepton(cms2.hyp_ll_id().at(hyp.idx), cms2.hyp_ll_index().at(hyp.idx), use_el_eta);
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

bool passesETHfo(int lep_id, int lep_idx, bool use_el_eta)
{
    if (abs(lep_id) == 13)
    {
        if (!samesign::isGoodLepton(lep_id, lep_idx, use_el_eta)) return false;
        if (muonIsoValuePF2012_deltaBeta(lep_idx) > 1.0) return false;
        return true;
    }
    // NOTE: this is the wrong definition of the electron FO
    // it's here as a place holder
    // see AN-2011/466 v6 for the correct definition
    else if (abs(lep_id) == 11)
    {
        if (!samesign::isGoodLepton(lep_id, lep_idx, use_el_eta)) return false;
        if (samesign::electronIsolationPF2012(lep_idx) > 0.6) return false;
        return true;
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
FRClosureBabyLooper::FRClosureBabyLooper
(
    const std::string& root_file_name,
    const Sample::value_type& sample,
    const AnalysisType::value_type& analysis_type,
    const std::string& fake_rate_file_name,
    const std::string& fake_rate_hist_name,
    const std::string& vtxreweight_file_name,
    int njets,
    int jetMetScale,
    bool use_el_eta,
    bool verbose,
    const std::string apply_jec_otf,
    double jet_pt_cut
)
    : AnalysisWithTree(root_file_name, "tree", "baby tree for SS2012 analysis")
    , m_sample(sample)
    , m_analysis_type(analysis_type)
    , m_njets(njets)
    , m_jetMetScale(jetMetScale)
    , m_use_el_eta(use_el_eta)
    , m_verbose(verbose)
    , m_jet_pt_cut(jet_pt_cut) 
    , m_hyp_count(0)
    , m_jet_corrector(NULL)
    , m_met_corrector(NULL)
{
    // set vertex weight file
    if (!vtxreweight_file_name.empty())
    {
        cout << "using vertex reweight file : " << vtxreweight_file_name << endl;
        set_vtxreweight_rootfile(vtxreweight_file_name.c_str(), m_verbose);
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
            if (m_sample <= at::Sample::datame)
            {
                m_list_of_jec_filenames.push_back(Form("%s/%s_L2L3Residual_AK5PF.txt", path.c_str(), temp_jec_string.c_str()));
            }
        }

        printf("[FRClosureBabyLooper] making jet and MET correctors with: \n");
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
        
        m_jet_corrector = makeJetCorrector(m_list_of_jec_filenames);
        if (not m_jet_corrector)
        {
            throw std::runtime_error("ERROR: FRClosureBabyLooper: unable to create jet_corrector");
        }
        m_met_corrector = new MetCorrector(m_list_of_jec_filenames);
        if (not m_met_corrector)
        {
            throw std::runtime_error("ERROR: FRClosureBabyLooper: unable to create met_corrector");
        }
    }

    // initialize counters
    for (size_t i = 0; i != m_count_ss.size(); i++) {m_count_ss[i]=0.0;}
    for (size_t i = 0; i != m_count_sf.size(); i++) {m_count_sf[i]=0.0;}
    for (size_t i = 0; i != m_count_df.size(); i++) {m_count_df[i]=0.0;}
    for (size_t i = 0; i != m_count_os.size(); i++) {m_count_os[i]=0.0;}

    for (size_t i = 0; i != m_count_nobtag_ss.size(); i++) {m_count_nobtag_ss[i]=0.0;}
    for (size_t i = 0; i != m_count_nobtag_sf.size(); i++) {m_count_nobtag_sf[i]=0.0;}
    for (size_t i = 0; i != m_count_nobtag_df.size(); i++) {m_count_nobtag_df[i]=0.0;}
    for (size_t i = 0; i != m_count_nobtag_os.size(); i++) {m_count_nobtag_os[i]=0.0;}

    // set the fake rate histograms
    std::auto_ptr<TFile> fake_rate_file(rt::OpenRootFile(fake_rate_file_name));
    cout << "using FR file : " << fake_rate_file->GetName() << endl;
    string mufr_name = "";
    string elfr_name = "";
    switch (m_analysis_type)
    {
        case AnalysisType::high_pt:
            mufr_name = "h_mufr40c";
            elfr_name = "h_elfr40c";
            break;
        case AnalysisType::low_pt:
            mufr_name = "h_mufr40c";
            elfr_name = "h_elfr40c_noiso";  // need to update with ewk correction
            break;
        case AnalysisType::vlow_pt:
            mufr_name = "h_mufr40c_iso";    // need to update with ewk correction
            elfr_name = "h_elfr40c_noiso";  // need to update with ewk correction
            break;
        case AnalysisType::high_pt_eth:
            mufr_name = "h_mufr40c";
            elfr_name = "h_elfr40c";
            break;
        case AnalysisType::higgsino:
            mufr_name = "h_mufr40c";
            elfr_name = "h_elfr40c";
            break;
        default:
            mufr_name = "h_mufr40c";
            elfr_name = "h_elfr40c";
            break;
    }
    h_mufr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get(mufr_name.c_str())->Clone()));
    h_elfr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get(elfr_name.c_str())->Clone()));
    if (not h_mufr) {throw std::runtime_error(Form("ERROR: FRClosureBabyLooper: %s doesn't exist", mufr_name.c_str()));}
    if (not h_elfr) {throw std::runtime_error(Form("ERROR: FRClosureBabyLooper: %s doesn't exist", elfr_name.c_str()));}
    h_mufr->SetDirectory(0);
    h_elfr->SetDirectory(0);

    cout << "using mu FR hist : " << h_mufr->GetName() << endl;
    cout << "using el FR hist : " << h_elfr->GetName() << endl;

    // get jet pt cut
    if (m_jet_pt_cut < 0.0f)
    {
        if (m_analysis_type == ss::AnalysisType::higgsino) m_jet_pt_cut = 20.0f;
        else m_jet_pt_cut = 40.0f;
    }

    // begin job
    BeginJob();
}

// destroy:
FRClosureBabyLooper::~FRClosureBabyLooper()
{
    delete m_jet_corrector;
    delete m_met_corrector;
}

// function operator: operate on each event
int FRClosureBabyLooper::operator() (long event, const std::string& filename)
{
    // call base class operator
    return Analyze(event, filename);
}

// members:
void FRClosureBabyLooper::BeginJob()
{
    // initialize hists
    BookHists();

    // initialize branches
    m_evt.Reset();
    m_evt.SetBranches(*m_tree);
}

void FRClosureBabyLooper::BookHists()
{
}


void FRClosureBabyLooper::EndJob()
{
    cout << "Number of dilepton hypotheses passing pT > 20, 20; |eta| < 2.4, 2.4; SS:\t" << m_hyp_count << endl;

    CTable yield_table;
    yield_table.setTitle("yields for SS Analysis 2012 (# btags >= 2)");
    yield_table.useTitle();
    yield_table.setTable() (                      "mm",          "em",          "ee",         "all")
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

    // call base class end job
    AnalysisWithTree::EndJob();
}

int FRClosureBabyLooper::SetJetCorrector(std::vector<std::string> &list_of_filenames)
{
    printf("[FRClosureBabyLooper] making jet corrector with: \n");
    for (unsigned int idx = 0; idx < list_of_filenames.size(); idx++)
    {
        printf("\t%s\n", list_of_filenames.at(idx).c_str());
    }

    m_jet_corrector = makeJetCorrector(list_of_filenames);
    m_met_corrector = new MetCorrector(list_of_filenames);
    if (!m_jet_corrector && !m_met_corrector) return 1;
    return 0;
}

int FRClosureBabyLooper::Analyze(long event, const std::string& filename)
{
    try
    {
        // Reset Tree Variables
        // --------------------------------------------------------------------------------------------------------- //

        m_evt.Reset();

        // event logic variables 
        // --------------------------------------------------------------------------------------------------------- //

        // lepton pT cut values
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
                mu_min_pt = 10.0;
                el_min_pt = 10.0;
                break;
            default:
                mu_min_pt = 20.0;
                el_min_pt = 20.0;
                break;
        }
        //const float min_pt = std::min(mu_min_pt, el_min_pt);

        // gen level  
        // --------------------------------------------------------------------------------------------------------- //
        m_evt.vgenb_p4    = efftools::getGenBjets(m_jet_pt_cut, 2.4);
        m_evt.vgenjets_p4 = efftools::getGenJets(m_jet_pt_cut, 2.4);
        m_evt.gen_ht      = efftools::getGenHT(m_jet_pt_cut, 2.4);
        m_evt.gen_nbtags  = m_evt.vgenb_p4.size();
        m_evt.gen_njets   = m_evt.vgenjets_p4.size();
        m_evt.gen_nleps   = leptonGenpCount_lepTauDecays(m_evt.gen_nels, m_evt.gen_nmus, m_evt.gen_ntaus);
        
        // require standard cleaning 
        if (!cleaning_standardNovember2011()) 
        {
            if (m_verbose) {std::cout << "fails November2011 cleaning requirement" << std::endl;}
            return 0;
        }

        // Analysis Selections
        // --------------------------------------------------------------------------------------------------------- //

        // jet type
        JetType jet_type = JETS_TYPE_PF_FAST_CORR;

        // loop over hypotheses
        HypInfo best_hyp(0, DileptonChargeType::static_size, DileptonHypType::static_size);
        for (size_t ihyp = 0; ihyp != hyp_type().size(); ihyp++)
        {                
            // leptons variables
            const LorentzVector& lt_p4 = hyp_lt_p4().at(ihyp);
            const LorentzVector& ll_p4 = hyp_ll_p4().at(ihyp);
            int lt_id                  = hyp_lt_id().at(ihyp);
            int ll_id                  = hyp_ll_id().at(ihyp);
            int lt_idx                 = hyp_lt_index().at(ihyp);
            int ll_idx                 = hyp_ll_index().at(ihyp);

            const float lt_min_pt = abs(lt_id)==11 ? el_min_pt : mu_min_pt;
            const float ll_min_pt = abs(ll_id)==11 ? el_min_pt : mu_min_pt;

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

            // check that leptons are from the same vertex
            if (!hypsFromFirstGoodVertex(ihyp))
            {
                if (m_verbose) {std::cout << "fails leptons are from the first good vertex requirement" << std::endl;}
                continue;
            }

            // check if event passes num_jet cut (hard coded to 2)
            int num_jets = samesign::nJets(ihyp, jet_type, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt);
            if (num_jets < m_njets)
            {
                if (m_verbose) {std::cout << "fails # jets >= " << m_njets << " requirement with " << num_jets << " jets" << std::endl;}
                continue;
            }

            // OK, now we make special lepton selections specific to the closure test
            // for increased stats, we're not going to require the lepton matched to a W to pass any requirements
            int lt_isFromW = leptonIsFromW(lt_idx, lt_id);
            int ll_isFromW = leptonIsFromW(ll_idx, ll_id);

            // skip events if neither lepton is prompt
            if (lt_isFromW < 1 && ll_isFromW < 1) continue;

            // skip events if both leptons are prompt
            if (lt_isFromW > 0 && lt_isFromW > 0) continue;

            // skip event if non-prompt lepton fails denominator
            if (m_analysis_type == AnalysisType::high_pt_eth)
            {
                if ((lt_isFromW < 1 &&  not passesETHfo(lt_id, lt_idx, m_use_el_eta))
                    || (ll_isFromW < 1 && not passesETHfo(ll_id, ll_idx, m_use_el_eta))) continue;
            }
            else{
                if ((lt_isFromW < 1 &&  not samesign::isDenominatorLepton(lt_id, lt_idx, m_use_el_eta))
                    || (ll_isFromW < 1 && not samesign::isDenominatorLepton(ll_id, ll_idx, m_use_el_eta))) continue;
            }

            // get the hyp type
            DileptonHypType::value_type type = hyp_typeToHypType(hyp_type().at(ihyp));

            // if non-prompt lepton is numerator, mark as SS event, otherwise, mark as SF event
            if ((lt_isFromW < 1 &&  samesign::isNumeratorLepton(lt_id, lt_idx, m_use_el_eta))
                || (ll_isFromW < 1 && samesign::isNumeratorLepton(ll_id, ll_idx, m_use_el_eta)))
            {
                best_hyp = std::min(best_hyp, HypInfo(ihyp, DileptonChargeType::SS, type));
            }
            else
            {
                best_hyp = std::min(best_hyp, HypInfo(ihyp, DileptonChargeType::SF, type));
            }

        } // end looper over hypothesis
        
        if (m_verbose) {std::cout << "end of hypothesis loop" << std::endl;}

        // Set Tree Variables
        // --------------------------------------------------------------------------------------------------------- //

        // best hyp index
        unsigned int hyp_idx = best_hyp.idx;
        DileptonChargeType::value_type event_type = best_hyp.charge_type;

        // all: 0, mm: 1, em: 2, ee: 3
        DileptonHypType::value_type dilepton_type = hyp_p4().empty() ? DileptonHypType::static_size : hyp_typeToHypType(hyp_type().at(hyp_idx));

        if (event_type == DileptonChargeType::static_size) return 0;

        if (m_verbose) {std::cout << "passes good dilepton type requirement: " << at::GetDileptonHypTypeName(dilepton_type) << std::endl;}
        if (m_verbose) {std::cout << "passes good charge type requirement:  "  << at::GetDileptonChargeTypeName(event_type) << std::endl;}
        if (m_verbose) {std::cout << "good hyp index is : " << hyp_idx << std::endl;}

        // event wieghts 
        float vtxw  = 1.0;
        float xsec  = evt_scale1fb();
        float scale = xsec * vtxw; 

        // fill event level info 
        m_evt.event_info.FillCommon(m_sample, filename);

        // fill the dilepton analysis independent variables 
        m_evt.FillCommon(hyp_idx);

        // ttbar breakdown: ttdil = 0, ttotr = 1, ttslb = 2, ttslo = 3, not set = 4
        m_evt.ttbar_bkdn = GetTTbarBreakDown(m_sample, m_evt.lep1.is_fromw, m_evt.lep2.is_fromw); 
        
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
        
        // SS specific event level info
        m_evt.mt           = rt::Mt(m_evt.lep1.p4, met, met_phi);  // calculated against the higher pT lepton
        m_evt.no_extraz    = (not samesign::makesExtraZ(hyp_idx));

        if (not m_jet_corrector)
        {
            m_evt.ht           = samesign::sumJetPt(hyp_idx, jet_type,                     /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.ht20         = samesign::sumJetPt(hyp_idx, jet_type,                     /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.ht30         = samesign::sumJetPt(hyp_idx, jet_type,                     /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.njets        = samesign::nJets(hyp_idx, jet_type,                        /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.njets20      = samesign::nJets(hyp_idx, jet_type,                        /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.njets30      = samesign::nJets(hyp_idx, jet_type,                        /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nbtags       = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nbtags20     = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nbtags30     = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
        }
        else
        {
            m_evt.ht           = samesign::sumJetPt(hyp_idx, m_jet_corrector, jet_type,                     /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.ht20         = samesign::sumJetPt(hyp_idx, m_jet_corrector, jet_type,                     /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.ht30         = samesign::sumJetPt(hyp_idx, m_jet_corrector, jet_type,                     /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.njets        = samesign::nJets(hyp_idx, m_jet_corrector, jet_type,                        /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.njets20      = samesign::nJets(hyp_idx, m_jet_corrector, jet_type,                        /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.njets30      = samesign::nJets(hyp_idx, m_jet_corrector, jet_type,                        /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nbtags       = samesign::nBtaggedJets(hyp_idx, m_jet_corrector, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nbtags20     = samesign::nBtaggedJets(hyp_idx, m_jet_corrector, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/20.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
            m_evt.nbtags30     = samesign::nBtaggedJets(hyp_idx, m_jet_corrector, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/30.0,         /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, 0);
        }

        m_evt.no_extrag    = (not samesign::makesExtraGammaStar(hyp_idx));
        m_evt.hyp_good_vtx = hypsFromFirstGoodVertex(hyp_idx);
        m_evt.clean        = cleaning_standardNovember2011(); 
        m_evt.presel       = (m_evt.no_extraz && m_evt.no_extrag && m_evt.clean && m_evt.hyp_good_vtx);

        // set lepton info (lep1 is higher pT lepton, lep2 is lower pT lepton)
        float lt_pt = hyp_lt_p4().at(hyp_idx).pt();
        float ll_pt = hyp_ll_p4().at(hyp_idx).pt();

        bool lt_num = samesign::isNumeratorLepton(cms2.hyp_lt_id().at(best_hyp.idx), cms2.hyp_lt_index().at(best_hyp.idx), m_use_el_eta);
        bool ll_num = samesign::isNumeratorLepton(cms2.hyp_ll_id().at(best_hyp.idx), cms2.hyp_ll_index().at(best_hyp.idx), m_use_el_eta);
        bool lt_fo  = samesign::isDenominatorLepton(cms2.hyp_lt_id().at(best_hyp.idx), cms2.hyp_lt_index().at(best_hyp.idx), m_use_el_eta) && !lt_num;
        bool ll_fo  = samesign::isDenominatorLepton(cms2.hyp_ll_id().at(best_hyp.idx), cms2.hyp_ll_index().at(best_hyp.idx), m_use_el_eta) && !ll_num;        

        int lep1_id;
        int lep1_idx;
        int lep2_id;
        int lep2_idx;
        bool lep1_fo  = false;
        bool lep1_num = false;
        bool lep2_fo  = false;
        bool lep2_num = false;
        // for now, lepton from W automatically has is_num = true and is_fo = false
        if (lt_pt > ll_pt)
        {
            lep1_id  = cms2.hyp_lt_id().at(hyp_idx);
            lep1_idx = cms2.hyp_lt_index().at(hyp_idx); 
            lep1_fo  = (m_evt.lep1.is_fromw > 0) ? false : lt_fo;
            lep1_num = (m_evt.lep1.is_fromw > 0) ? true : lt_num;
            lep2_id  = cms2.hyp_ll_id().at(hyp_idx);    
            lep2_idx = cms2.hyp_ll_index().at(hyp_idx); 
            lep2_fo  = (m_evt.lep2.is_fromw > 0) ? false : ll_fo;
            lep2_num = (m_evt.lep2.is_fromw > 0) ? true : ll_num;
        }
        else
        {
            lep1_id  = cms2.hyp_ll_id().at(hyp_idx);
            lep1_idx = cms2.hyp_ll_index().at(hyp_idx); 
            lep1_fo  = (m_evt.lep1.is_fromw > 0) ? false : ll_fo;
            lep1_num = (m_evt.lep1.is_fromw > 0) ? true : ll_num;
            lep2_id  = cms2.hyp_lt_id().at(hyp_idx);    
            lep2_idx = cms2.hyp_lt_index().at(hyp_idx); 
            lep2_fo  = (m_evt.lep2.is_fromw > 0) ? false : lt_fo;
            lep2_num = (m_evt.lep2.is_fromw > 0) ? true : lt_num;
        }
        bool lep1_is_mu = (abs(lep1_id)==13);
        bool lep1_is_el = (abs(lep1_id)==11);
        bool lep2_is_mu = (abs(lep2_id)==13);
        bool lep2_is_el = (abs(lep2_id)==11);

        m_evt.lep1.cordetiso   = m_evt.lep1.detiso   - (log(m_evt.lep1.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep1.p4.pt()); // check that I have the correct formula 
        m_evt.lep1.cordetiso04 = m_evt.lep1.detiso04 - (log(m_evt.lep1.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep1.p4.pt()); // check that I have the correct formula 
        m_evt.lep1.corpfiso    = samesign::leptonIsolation(lep1_id, lep1_idx);
        m_evt.lep1.corpfiso04  = (lep1_is_el) ? samesign::electronIsolationPF2012_cone04(lep1_idx) : -999999.0;  
        m_evt.lep1.effarea     = samesign::EffectiveArea03(lep1_id, lep1_idx); 
        m_evt.lep1.effarea04   = samesign::EffectiveArea04(lep1_id, lep1_idx);
        m_evt.lep1.dbeta       = (lep1_is_mu) ? mus_isoR03_pf_PUPt().at(lep1_idx) : -99999.0;
        m_evt.lep1.dbeta04     = (lep1_is_mu) ? mus_isoR04_pf_PUPt().at(lep1_idx) : -99999.0;
        m_evt.lep1.is_fo       = lep1_fo;
        m_evt.lep1.is_num      = lep1_num;
        //m_evt.lep1.is_conv     = false; 
        m_evt.lep1.mt          = rt::Mt(m_evt.lep1.p4, met, met_phi);
        m_evt.lep1.mt          = rt::Mt(m_evt.lep1.p4, evt_pfmet(), evt_pfmetPhi());
        m_evt.lep1.passes_id   = samesign::isGoodLepton(lep1_id, lep1_idx, m_use_el_eta);
        m_evt.lep1.passes_iso  = samesign::isIsolatedLepton(lep1_id, lep1_idx);
        m_evt.lep1_wfr         = GetFakeRateValue(lep1_id, lep1_idx);

        m_evt.lep2.cordetiso   = m_evt.lep2.detiso   - (log(m_evt.lep2.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep2.p4.pt()); // check that I have the correct formula 
        m_evt.lep2.cordetiso04 = m_evt.lep2.detiso04 - (log(m_evt.lep2.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep2.p4.pt()); // check that I have the correct formula 
        m_evt.lep2.corpfiso    = samesign::leptonIsolation(lep2_id, lep2_idx);
        m_evt.lep2.corpfiso04  = (lep2_is_el) ? samesign::electronIsolationPF2012_cone04(lep2_idx) : -999999.0;  
        m_evt.lep2.effarea     = samesign::EffectiveArea03(lep2_id, lep2_idx);
        m_evt.lep2.effarea04   = samesign::EffectiveArea04(lep2_id, lep2_idx);
        m_evt.lep2.dbeta       = (lep2_is_mu) ? mus_isoR03_pf_PUPt().at(lep2_idx) : -99999.0;
        m_evt.lep2.dbeta04     = (lep2_is_mu) ? mus_isoR04_pf_PUPt().at(lep2_idx) : -99999.0;
        m_evt.lep2.is_fo       = lep2_fo; 
        m_evt.lep2.is_num      = lep2_num;
        //m_evt.lep2.is_conv     = false; 
        m_evt.lep2.mt          = rt::Mt(m_evt.lep2.p4, met, met_phi);
        m_evt.lep2.passes_id   = samesign::isGoodLepton(lep2_id, lep2_idx, m_use_el_eta);
        m_evt.lep2.passes_iso  = samesign::isIsolatedLepton(lep2_id, lep2_idx);
        m_evt.lep2_wfr         = GetFakeRateValue(lep2_id, lep2_idx);

        // classification
        m_evt.is_ss   = (event_type==DileptonChargeType::SS);
        m_evt.is_sf   = (event_type==DileptonChargeType::SF);
        m_evt.is_df   = (event_type==DileptonChargeType::DF);
        m_evt.is_os   = (event_type==DileptonChargeType::OS);
        m_evt.em_mufo = m_evt.em && ((lep1_fo && lep1_is_mu) || (lep2_fo && lep2_is_mu));  
        m_evt.em_elfo = m_evt.em && ((lep1_fo && lep1_is_el) || (lep2_fo && lep2_is_el));
        m_evt.is_pp   = hyp_lt_charge().at(hyp_idx)>0 && hyp_ll_charge().at(hyp_idx)>0; 
        m_evt.is_mm   = hyp_lt_charge().at(hyp_idx)<0 && hyp_ll_charge().at(hyp_idx)<0; 

        // electron isolation correction variables
        m_evt.rho_iso = evt_kt6pf_foregiso_rho();
        m_evt.rho     = evt_ww_rho_vor(); 

        // jet/bjet info 
        vector<bool> jet_flags;
        vector<bool> bjet_flags;
        if (not m_jet_corrector)
        {
            m_evt.vbjets_p4 = samesign::getBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM,     /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale); 
            m_evt.vjets_p4  = samesign::getJets(hyp_idx, jet_type,                            /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale); 
            bjet_flags      = samesign::getBtaggedJetFlags(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
            jet_flags       = samesign::getJetFlags(hyp_idx, jet_type,                        /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
        }
        else
        {
            m_evt.vbjets_p4 = samesign::getBtaggedJets(hyp_idx, m_jet_corrector, jet_type, JETS_BTAG_CSVM,     /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale); 
            m_evt.vjets_p4  = samesign::getJets(hyp_idx, m_jet_corrector, jet_type,                            /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale); 
            bjet_flags      = samesign::getBtaggedJetFlags(hyp_idx, m_jet_corrector, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
            jet_flags       = samesign::getJetFlags(hyp_idx, m_jet_corrector, jet_type,                        /*dR=*/0.4, /*jet_pt>*/m_jet_pt_cut, /*|eta|<*/2.4, mu_min_pt, el_min_pt, 1.0, m_jetMetScale);
        }

        // jet btag flag and mc flavor matching
        for (size_t jidx = 0; jidx != jet_flags.size(); jidx++)
        {
            // jets
            if (not jet_flags.at(jidx)) {continue;}
            if (not evt_isRealData() && (evt_CMS2tag().at(0)=="V05-03-23" || evt_CMS2tag().at(0)=="V05-03-24"))
            {
                m_evt.vjets_mcflavor_phys.push_back(pfjets_mcflavorPhys().at(jidx));
                m_evt.vjets_mcflavor_algo.push_back(pfjets_mcflavorAlgo().at(jidx));
            }

            // btags
            m_evt.vjets_btagged.push_back(bjet_flags.at(jidx));
            if (not bjet_flags.at(jidx)) {continue;}
            if (not evt_isRealData() && (evt_CMS2tag().at(0)=="V05-03-23" || evt_CMS2tag().at(0)=="V05-03-24"))
            {
                m_evt.vbjets_mcflavor_phys.push_back(pfjets_mcflavorPhys().at(jidx));
                m_evt.vbjets_mcflavor_algo.push_back(pfjets_mcflavorAlgo().at(jidx));
            }
        }

        m_evt.bjets_dr12 = (m_evt.nbtags>=2) ? rt::DeltaR(m_evt.vbjets_p4.at(0), m_evt.vbjets_p4.at(1)) : -999999.0;
        m_evt.jets_dr12  = (m_evt.njets>=2 ) ? rt::DeltaR(m_evt.vjets_p4.at(0) , m_evt.vjets_p4.at(1) ) : -999999.0;

        vector<LorentzVector> temp_bjets_p4 = m_evt.vbjets_p4;
        if (!temp_bjets_p4.empty())
        {
            // nearest to lep1
            std::sort(temp_bjets_p4.begin(), temp_bjets_p4.begin(), SortByDeltaR<LorentzVector>(m_evt.lep1.p4));
            m_evt.lep1_nearbjet_p4 = temp_bjets_p4.front();
            m_evt.lep1_nearbjet_dr = rt::DeltaR(m_evt.lep1.p4, temp_bjets_p4.front());

            // nearest to lep2
            std::sort(temp_bjets_p4.begin(), temp_bjets_p4.begin(), SortByDeltaR<LorentzVector>(m_evt.lep2.p4));
            m_evt.lep2_nearbjet_p4 = temp_bjets_p4.front();
            m_evt.lep2_nearbjet_dr = rt::DeltaR(m_evt.lep2.p4, temp_bjets_p4.front());
        }

        vector<LorentzVector> temp_jets_p4 = m_evt.vjets_p4;  

        // get the untagged jets
        vector<LorentzVector> temp_jets_nontagged_p4;
        for (size_t i = 0; i != temp_jets_p4.size(); i++)
        {
            //temp_jets_p4.at(i) *= evt_isRealData() ? pfjets_corL1FastL2L3residual().at(i) : pfjets_corL1FastL2L3().at(i);
            if (not bjet_flags.at(i))
            {
                temp_jets_nontagged_p4.push_back(temp_jets_p4.at(i));
            }
        }

        if (!temp_jets_p4.empty())
        {
            // nearest untagged jet to the btags
            for (size_t i = 0; i != m_evt.vbjets_p4.size(); i++)
            {
                const LorentzVector& p4 = m_evt.vbjets_p4.at(i);
                if (temp_jets_nontagged_p4.empty()) 
                {
                    m_evt.vbjets_nearjet_p4.push_back(LorentzVector(0,0,0,0));
                    m_evt.vbjets_nearjet_dr.push_back(-999999.0);
                    continue;
                }
                std::sort(temp_jets_nontagged_p4.begin(), temp_jets_nontagged_p4.end(), SortByDeltaR<LorentzVector>(p4));
                m_evt.vbjets_nearjet_p4.push_back(temp_jets_nontagged_p4.front());
                m_evt.vbjets_nearjet_dr.push_back(rt::DeltaR(p4, temp_jets_nontagged_p4.front()));
            }

            // nearest jet to the selected jet
            for (size_t i = 0; i != m_evt.vjets_p4.size(); i++)
            {
                if (temp_jets_nontagged_p4.empty()) 
                {
                    m_evt.vjets_nearjet_p4.push_back(LorentzVector(0,0,0,0));
                    m_evt.vjets_nearjet_dr.push_back(-999999.0);
                    continue;
                }
                const LorentzVector& p4 = m_evt.vjets_p4.at(i);
                std::sort(temp_jets_nontagged_p4.begin(), temp_jets_nontagged_p4.end(), SortByDeltaR<LorentzVector>(p4));

                // check if closest is the same jet?
                if (rt::DeltaR(temp_jets_nontagged_p4.front(), p4) < 0.0001)
                {
                    if (temp_jets_nontagged_p4.size()>=2)
                    {
                        m_evt.vjets_nearjet_p4.push_back(temp_jets_nontagged_p4.at(1));
                        m_evt.vjets_nearjet_dr.push_back(rt::DeltaR(p4, temp_jets_nontagged_p4.at(1)));
                    }
                    else // fill with dummy values
                    {
                        m_evt.vjets_nearjet_p4.push_back(LorentzVector(0,0,0,0));
                        m_evt.vjets_nearjet_dr.push_back(-999999.0);
                    }
                }
                else
                {
                    m_evt.vjets_nearjet_p4.push_back(temp_jets_nontagged_p4.front());
                    m_evt.vjets_nearjet_dr.push_back(rt::DeltaR(p4, temp_jets_nontagged_p4.front()));
                }
            }
            
            // nearest to lep1
            std::sort(temp_jets_p4.begin(), temp_jets_p4.end(), SortByDeltaR<LorentzVector>(m_evt.lep1.p4));
            m_evt.lep1_nearjet_p4 = temp_jets_p4.front();
            m_evt.lep1_nearjet_dr = rt::DeltaR(m_evt.lep1.p4, temp_jets_p4.front());

            // nearest to lep2
            std::sort(temp_jets_p4.begin(), temp_jets_p4.end(), SortByDeltaR<LorentzVector>(m_evt.lep2.p4));
            m_evt.lep2_nearjet_p4 = temp_jets_p4.front();
            m_evt.lep2_nearjet_dr = rt::DeltaR(m_evt.lep2.p4, temp_jets_p4.front());
        }

        if (abs(m_evt.lep1.pdgid) == 11) {
            std::pair<int,double> closest_el = std::make_pair(-1, 99.);
            for (unsigned int eidx = 0; eidx < cms2.els_p4().size(); eidx++) {
                
                if (cms2.els_p4().at(eidx).pt() < 5.) continue;
                if (fabs(cms2.els_p4().at(eidx).eta()) > 2.5) continue;
                if (m_evt.lep1.charge * cms2.els_charge().at(eidx) > 0) continue;

                double iso_val = samesign::electronIsolationPF2012(eidx);
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

                double iso_val = samesign::electronIsolationPF2012(eidx);
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

            // b-tagged jets
            for (size_t i = 0; i != m_evt.vbjets_p4.size(); i++)
            {
                const LorentzVector bjet_p4 = m_evt.vbjets_p4.at(i);
                int idx = efftools::getGenParton(bjet_p4, /*use status3 =*/true);
                int mc3id = idx>= 0 ? tas::genps_id().at(idx) : -999999;
                int momid = idx>= 0 ? tas::genps_id_mother().at(idx) : -999999;
                LorentzVector mc3p4 = idx>= 0 ? tas::genps_p4().at(idx) : LorentzVector(0,0,0,0);
                m_evt.vbjets_mc3id.push_back(mc3id);
                m_evt.vbjets_momid.push_back(momid);
                m_evt.vbjets_mc3p4.push_back(mc3p4);
            }
        }

        // Fill the tree
        m_tree->Fill();

        // printout
        m_evt.is_good_lumi = true;
        if (m_evt.is_good_lumi && m_evt.njets >= m_njets)
        {
            scale = 1.0;
            if (dilepton_type==DileptonHypType::MUMU)
            {
                if(m_verbose) {cout << "type == mm" << endl;}
                if(event_type==DileptonChargeType::SS) m_count_nobtag_ss[0] += scale;
                if(event_type==DileptonChargeType::SF) m_count_nobtag_sf[0] += scale;
                if(event_type==DileptonChargeType::DF) m_count_nobtag_df[0] += scale;
                if(event_type==DileptonChargeType::OS) m_count_nobtag_os[0] += scale;
                if(event_type==DileptonChargeType::SS && m_evt.nbtags > 1) m_count_ss[0] += scale;
                if(event_type==DileptonChargeType::SF && m_evt.nbtags > 1) m_count_sf[0] += scale;
                if(event_type==DileptonChargeType::DF && m_evt.nbtags > 1) m_count_df[0] += scale;
                if(event_type==DileptonChargeType::OS && m_evt.nbtags > 1) m_count_os[0] += scale;
            }
            if (dilepton_type==DileptonHypType::EMU)
            {
                if(m_verbose) {cout << "type == em" << endl;}
                if(event_type==DileptonChargeType::SS) m_count_nobtag_ss[1] += scale;
                if(event_type==DileptonChargeType::SF) m_count_nobtag_sf[1] += scale;
                if(event_type==DileptonChargeType::DF) m_count_nobtag_df[1] += scale;
                if(event_type==DileptonChargeType::OS) m_count_nobtag_os[1] += scale;
                if(event_type==DileptonChargeType::SS && m_evt.nbtags > 1) m_count_ss[1] += scale;
                if(event_type==DileptonChargeType::SF && m_evt.nbtags > 1) m_count_sf[1] += scale;
                if(event_type==DileptonChargeType::DF && m_evt.nbtags > 1) m_count_df[1] += scale;
                if(event_type==DileptonChargeType::OS && m_evt.nbtags > 1) m_count_os[1] += scale;
            }
            if (dilepton_type==DileptonHypType::EE)
            {
                if(m_verbose) {cout << "type == ee" << endl;}
                if(event_type==DileptonChargeType::SS) m_count_nobtag_ss[2] += scale;
                if(event_type==DileptonChargeType::SF) m_count_nobtag_sf[2] += scale;
                if(event_type==DileptonChargeType::DF) m_count_nobtag_df[2] += scale;
                if(event_type==DileptonChargeType::OS) m_count_nobtag_os[2] += scale;
                if(event_type==DileptonChargeType::SS && m_evt.nbtags > 1) m_count_ss[2] += scale;
                if(event_type==DileptonChargeType::SF && m_evt.nbtags > 1) m_count_sf[2] += scale;
                if(event_type==DileptonChargeType::DF && m_evt.nbtags > 1) m_count_df[2] += scale;
                if(event_type==DileptonChargeType::OS && m_evt.nbtags > 1) m_count_os[2] += scale;
            }
            // count all 
            {
                if(event_type==DileptonChargeType::SS) m_count_nobtag_ss[3] += scale;
                if(event_type==DileptonChargeType::SF) m_count_nobtag_sf[3] += scale;
                if(event_type==DileptonChargeType::DF) m_count_nobtag_df[3] += scale;
                if(event_type==DileptonChargeType::OS) m_count_nobtag_os[3] += scale;
                if(event_type==DileptonChargeType::SS && m_evt.nbtags > 1) m_count_ss[3] += scale;
                if(event_type==DileptonChargeType::SF && m_evt.nbtags > 1) m_count_sf[3] += scale;
                if(event_type==DileptonChargeType::DF && m_evt.nbtags > 1) m_count_df[3] += scale;
                if(event_type==DileptonChargeType::OS && m_evt.nbtags > 1) m_count_os[3] += scale;
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

float FRClosureBabyLooper::GetFakeRateValue(int lep_id, int lep_idx) const 
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
