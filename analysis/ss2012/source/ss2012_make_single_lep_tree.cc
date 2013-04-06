// make the Tag & Probe plots 

// c++
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <tr1/memory>

// ROOT
#include "TChain.h"
#include "TH1F.h"
#include "Math/LorentzVector.h"

// BOOST
#include <boost/program_options.hpp>

// CMS2
#include "CMS2Wrapper.h"
#include "eventSelections.h"
#include "ssSelections.h"

// Tools
#include "rt/RootTools.h"
#include "at/MCBtagCount.h"
#include "at/Sample.h"
#include "at/ScanChain.h"
#include "at/AnalysisWithTree.h"
#include "at/Predicates.h"
#include "at/DileptonHypType.h"
#include "SingleLeptonTree.h"
#include "EventInfoTree.h"
#include "AnalysisType.h"
#include "ScaleFactors.h"

using namespace at;
using namespace std;
using namespace rt;
using namespace tas;

// SameSignSingleLeptonTree
// ---------------------------------------------------------------------- //

struct SameSignSingleLeptonTree : public SingleLeptonTree
{
    // construct:
    SameSignSingleLeptonTree();
    SameSignSingleLeptonTree(const std::string &prefix);
    
    // destroy:
    virtual ~SameSignSingleLeptonTree();

    // methods:
    void Reset();
    void SetBranches(TTree& tree);
    void SetAliases(TTree& tree) const;

    // members:

    EventInfoTree event_info;

    // event info
    float ht;
    int njets;
    int nbtags;
    int nbtags_reweighted;
    float wfr;
    float wflip;
};

// consturct:
SameSignSingleLeptonTree::SameSignSingleLeptonTree()
{
}

SameSignSingleLeptonTree::SameSignSingleLeptonTree(const std::string &prefix)
    : SingleLeptonTree(prefix)
{
}

// destroy:
SameSignSingleLeptonTree::~SameSignSingleLeptonTree()
{
}

// methods:
void SameSignSingleLeptonTree::SetBranches(TTree &tree)
{
    event_info.SetBranches(tree);
    SingleLeptonTree::SetBranches(tree);

    tree.Branch(Form("%swfr"   , prefix_.c_str()) , &wfr   , "wfr/F"   ); 
    tree.Branch(Form("%swflip" , prefix_.c_str()) , &wflip , "wflip/F" ); 

    tree.Branch("ht"                , &ht                , "ht/F"               );
    tree.Branch("njets"             , &njets             , "njets/I"            );
    tree.Branch("nbtags"            , &nbtags            , "nbtags/I"           );
    tree.Branch("nbtags_reweighted" , &nbtags_reweighted , "nbtags_reweighted/I");
}

void SameSignSingleLeptonTree::Reset()
{
    event_info.Reset();
    SingleLeptonTree::Reset();

    wfr    = -999999.0;
    wflip  = -999999.0;
    ht     = -999999.0;
    njets  = -999999;
    nbtags = -999999;
}


// SingleLeptonTreeLooper
// ---------------------------------------------------------------------- //

// construct:
class SingleLeptonTreeLooper : public AnalysisWithTree
{
	public:
        // construct:
		SingleLeptonTreeLooper
        (
            const std::string& file_name, 
            const std::string& fake_rate_file_name,
            const std::string& flip_rate_file_name,
            const at::Sample::value_type& sample,
            const ss::AnalysisType::value_type& analysis_type,
            const float lumi,
            const unsigned int njets,
            const float jet_pt_cut,
            const bool verbose
        ); 
        
        // methods:
		int operator() (long event, const std::string& filename);
		virtual void BeginJob();
		virtual void EndJob();

        float GetFakeRateValue(const int lep_id, const int lep_idx) const;
        float GetFlipRateValue(const int lep_id, const int lep_idx) const;

    private:
        // members:
        SameSignSingleLeptonTree m_evt;
        const at::Sample::value_type m_sample;
        const ss::AnalysisType::value_type m_analysis_type;
        const float m_lumi;
        const unsigned int m_njets;
        const float m_jet_pt_cut;
        const bool m_verbose;
    
        // counts
        unsigned int m_num_els_pass;
        unsigned int m_num_mus_pass;
        unsigned int m_num_pass;

        // fake rate hists
        std::tr1::shared_ptr<TH2F> h_mufr;
        std::tr1::shared_ptr<TH2F> h_elfr;
        std::tr1::shared_ptr<TH2F> h_flip;

};

// construct:
SingleLeptonTreeLooper::SingleLeptonTreeLooper
(
    const std::string& file_name, 
    const std::string& fake_rate_file_name,
    const std::string& flip_rate_file_name,
    const at::Sample::value_type& sample,
    const ss::AnalysisType::value_type& analysis_type,
    const float lumi,
    const unsigned int njets,
    const float jet_pt_cut,
    const bool verbose
)
    : AnalysisWithTree(file_name, "tree", "single lepton baby tree for SS2012 analysis")
    , m_evt("lep_")
    , m_sample(sample)
    , m_analysis_type(analysis_type)
    , m_lumi(lumi)
    , m_njets(njets)
    , m_jet_pt_cut(jet_pt_cut)
    , m_verbose(verbose)
    , m_num_els_pass(0)
    , m_num_mus_pass(0)
    , m_num_pass(0)
{
    using namespace ss;

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
        case AnalysisType::low_pt:
            mufr_name = "h_mufr40c_ewkcor";
            elfr_name = "h_elfr40c_noiso_ewkcor";
            break;
        case AnalysisType::vlow_pt:
            mufr_name = "h_mufr40c_iso";    // need to update with ewk correction
            elfr_name = "h_elfr40c_noiso_ewkcor";
            break;
        case AnalysisType::high_pt_eth:
            mufr_name = "h_mufr40c";
            elfr_name = "h_elfr40c";
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
    if (not h_mufr) {throw std::runtime_error(Form("ERROR: SingleLeptonLooper: %s doesn't exist", mufr_name.c_str()));}
    if (not h_elfr) {throw std::runtime_error(Form("ERROR: SingleLeptonLooper: %s doesn't exist", elfr_name.c_str()));}
    h_mufr->SetDirectory(0);
    h_elfr->SetDirectory(0);

    cout << "[SingleLeptonLooper] using mu FR hist : " << h_mufr->GetName() << endl;
    cout << "[SingleLeptonLooper] using el FR hist : " << h_elfr->GetName() << endl;

    // set the flip rate histograms
    std::auto_ptr<TFile> flip_rate_file(rt::OpenRootFile(flip_rate_file_name));
    cout << "[SingleLeptonLooper] using FL file : " << flip_rate_file->GetName() << endl;
    h_flip.reset(dynamic_cast<TH2F*>(flip_rate_file->Get("flipRate")->Clone()));
    if (not h_flip) {throw std::runtime_error("ERROR: SingleLeptonLooper: flipRate doesn't exist");}
    h_flip->SetDirectory(0);

    cout << "[SingleLeptonLooper] using FL hist : " << h_flip->GetName() << endl;

	BeginJob();
}

void SingleLeptonTreeLooper::BeginJob()
{
    // initialize branches
    m_evt.Reset();
    m_evt.SetBranches(*m_tree);
}

void SingleLeptonTreeLooper::EndJob()
{
    cout << "[SingleLeptonLooper] number of passing els: " << m_num_els_pass << endl;
    cout << "[SingleLeptonLooper] number of passing mus: " << m_num_mus_pass << endl;
    cout << "[SingleLeptonLooper] number of passing    : " << m_num_pass     << endl;

    // call base class end job
    AnalysisWithTree::EndJob();
}

int SingleLeptonTreeLooper::operator() (long event, const std::string& filename)
{
    using namespace ss;

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
                mu_min_pt = 10.;
                el_min_pt = 10.;
                break;
            default:
                mu_min_pt = 20.0;
                el_min_pt = 20.0;
                break;
        }
        //const float min_pt = std::min(mu_min_pt, el_min_pt);

        // event level 
        // --------------------------------------------------------------------------------------------------------- //

        // fill event level info 
        m_evt.event_info.FillCommon(m_sample, filename);

        // lepton level 
        // --------------------------------------------------------------------------------------------------------- //

        // select the highest pT lepton
        std::vector<std::pair<LorentzVector, unsigned int> > els = samesign::getNumeratorElectrons(el_min_pt);	 
        std::vector<std::pair<LorentzVector, unsigned int> > mus = samesign::getNumeratorMuons(mu_min_pt);	 
        int lep_idx = -1;
        int lep_id  = -1;
        LorentzVector lep_p4;
        if (!els.empty() && !mus.empty())
        {
            if (els.front().first.pt() > mus.front().first.pt())
            {
                lep_idx = els.front().second;
                lep_id  = -11 * els_charge().at(lep_idx);
                lep_p4  = els_p4().at(lep_idx);
                m_num_els_pass++;
            }
            else
            {
                lep_idx = mus.front().second;
                lep_id  = -13 * mus_charge().at(lep_idx);
                lep_p4  = mus_p4().at(lep_idx);
                m_num_mus_pass++;
            }
            m_num_pass++;
        }
        else if (!els.empty() && mus.empty())
        {
            lep_idx = els.front().second;
            lep_id  = -11 * els_charge().at(lep_idx);
            lep_p4  = els_p4().at(lep_idx);
            m_num_els_pass++;
            m_num_pass++;
        }
        else if (els.empty() && !mus.empty())
        {
            lep_idx = mus.front().second;
            lep_id  = -13 * mus_charge().at(lep_idx);
            lep_p4  = mus_p4().at(lep_idx);
            m_num_mus_pass++;
            m_num_pass++;
        }
        else
        {
            if (m_verbose) {cout << "no leptons selected.  going to next event" << endl;}
            m_tree->Fill(); // keep the event for the record
            return 0;
        }

        // fill lepton level info 
        // --------------------------------------------------------------------------------------------------------- //

        // basic variables
        m_evt.FillCommon(lep_id, lep_idx);

        const bool lep_is_mu = (abs(lep_id)==13);
        const bool lep_is_el = (abs(lep_id)==11);

        // assign variables that are analysis specific
        m_evt.sf_lepeff   = TagAndProbeScaleFactor(lep_id, lep_p4.pt(), (lep_is_el ? m_evt.sc_p4.eta(): lep_p4.eta())); 
        m_evt.sf_trig     = 1.0 - 0.5*(1.0 - DileptonTriggerScaleFactor((lep_is_mu ? at::DileptonHypType::MUMU : at::DileptonHypType::EE), m_analysis_type, lep_p4));  // this is a hack since we didn't measure this per lepton
        m_evt.cordetiso   = m_evt.detiso   - (log(m_evt.p4.pt())*numberOfGoodVertices())/(30.0*lep_p4.pt());
        m_evt.cordetiso04 = m_evt.detiso04 - (log(m_evt.p4.pt())*numberOfGoodVertices())/(30.0*lep_p4.pt());
        m_evt.corpfiso    = samesign::leptonIsolation(lep_id, lep_idx);
        m_evt.corpfiso04  = (lep_is_el) ? samesign::electronIsolationPF2012_cone04(lep_idx) : -999999.0;   // ∆R=0.4 not implemented for muons
        m_evt.effarea     = samesign::EffectiveArea03(lep_id, lep_idx); 
        m_evt.effarea04   = samesign::EffectiveArea04(lep_id, lep_idx);
        m_evt.dbeta       = (lep_is_mu) ? mus_isoR03_pf_PUPt().at(lep_idx) : -99999.0; // ∆R=0.4 not implemented for muons
        m_evt.dbeta04     = (lep_is_mu) ? mus_isoR04_pf_PUPt().at(lep_idx) : -99999.0; // ∆R=0.4 not implemented for muons
        m_evt.is_fo       = samesign::isDenominatorLepton(lep_id, lep_idx) && not samesign::isNumeratorLepton(lep_id, lep_idx);
        m_evt.is_num      = samesign::isNumeratorLepton(lep_id, lep_idx);
        m_evt.is_den      = samesign::isDenominatorLepton(lep_id, lep_idx);
        m_evt.mt          = rt::Mt(lep_p4, m_evt.event_info.pfmet, m_evt.event_info.pfmet_phi);
        m_evt.passes_id   = samesign::isGoodLepton(lep_id, lep_idx);
        m_evt.passes_iso  = samesign::isIsolatedLepton(lep_id, lep_idx);
        m_evt.wfr         = GetFakeRateValue(lep_id, lep_idx);
        m_evt.wflip       = GetFlipRateValue(lep_id, lep_idx);

        // jet related info
        // --------------------------------------------------------------------------------------------------------- //

        const JetType jet_type        = evt_isRealData() ? JETS_TYPE_PF_FAST_CORR_RESIDUAL : JETS_TYPE_PF_FAST_CORR;
        const CleaningType clean_type = (lep_is_mu ? JETS_CLEAN_SINGLE_MU : JETS_CLEAN_SINGLE_E);
        std::vector<bool> jet_flags   = getJetFlags       (lep_idx, jet_type, clean_type,                 /*dR=*/0.4, /*pt>*/0.0, /*eta>*/2.4);
        std::vector<bool> bjet_flags  = getBtaggedJetFlags(lep_idx, jet_type, clean_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*pt>*/0.0, /*eta>*/2.4);

        std::vector<LorentzVector> vjets_p4;
        std::vector<LorentzVector> vbjets_p4;
        std::vector<bool> vjets_btagged; 
        std::vector<int> vjets_mcflavor_phys;
        std::vector<int> vjets_mcflavor_algo;
        for (size_t jidx = 0; jidx != jet_flags.size(); jidx++)
        {
            // jets
            if (not jet_flags.at(jidx)) {continue;}

            // corrected the pt
            LorentzVector jet_cor_p4 = cms2.pfjets_p4().at(jidx) * cms2.pfjets_corL1FastL2L3().at(jidx);

            if (jet_cor_p4.pt() < 40.0) {continue;}

            // veto jets close to leptons
            bool jet_is_lep = false;
            for (size_t eidx = 0; eidx < els_p4().size(); eidx++)
            {
                if (els_p4().at(eidx).pt() < el_min_pt)                                  {continue;}
                if (!samesign::isNumeratorLepton(11, eidx))                              {continue;}
                if (ROOT::Math::VectorUtil::DeltaR(jet_cor_p4, els_p4().at(eidx)) > 0.4) {continue;}
                jet_is_lep = true;
                break;
            }
            if (jet_is_lep) {continue;}

            for (size_t midx = 0; midx < mus_p4().size(); midx++) 
            {
                if (mus_p4().at(midx).pt() < mu_min_pt)                                  {continue;}
                if (!samesign::isNumeratorLepton(13, midx))                              {continue;}
                if (ROOT::Math::VectorUtil::DeltaR(jet_cor_p4, mus_p4().at(midx)) > 0.4) {continue;}
                jet_is_lep = true;
                break;
            }            
            if (jet_is_lep) {continue;}
            //cout << "selecting jet " << jidx << " with pt = " << jet_cor_p4.pt() << endl;

            vjets_p4.push_back(jet_cor_p4);
            vjets_mcflavor_phys.push_back(pfjets_mcflavorPhys().at(jidx));
            vjets_mcflavor_algo.push_back(pfjets_mcflavorAlgo().at(jidx));

            // btags
            vjets_btagged.push_back(bjet_flags.at(jidx));
            if (not bjet_flags.at(jidx)) {continue;}
            vbjets_p4.push_back(jet_cor_p4);
        }

        m_evt.ht = 0.0; for (size_t jidx = 0; jidx != vjets_p4.size(); jidx++) {m_evt.ht += vjets_p4.at(jidx).pt();}
        m_evt.njets             = vjets_p4.size();
        m_evt.nbtags            = vbjets_p4.size();
        m_evt.nbtags_reweighted = at::MCBtagCount(vjets_p4, vjets_btagged, vjets_mcflavor_algo, m_sample, /*is_fast_sim=*/false);

        // save the result to the tree 
        // --------------------------------------------------------------------------------------------------------- //

        m_tree->Fill();
    }
    catch (std::exception& e)
    {
        cout << Form("Fatal error on run %d, ls %d, event %d", tas::evt_run(), tas::evt_lumiBlock(), tas::evt_event()) << endl;
        cout << e.what() << endl;
        cout << "Exiting..." << endl;
        exit(1);
    }

    // done
    return 0;
}

float SingleLeptonTreeLooper::GetFakeRateValue(const int lep_id, const int lep_idx) const 
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

float SingleLeptonTreeLooper::GetFlipRateValue(const int lep_id, const int lep_idx) const 
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

// the main program 
// ---------------------------------------------------------------------- //

int main(int argc, char* argv[])
try
{
    // inputs
    // -------------------------------------------------------------------------------------------------//

    long number_of_events           = -1;
    bool verbose                    = false;
    double luminosity               = 1.0;
    std::string output_file         = "";
    std::string input_file          = "";
    std::string ntuple_type_name    = "cms2";
    std::string fake_rate_file_name = "data/fake_rates/ssFR_data_ewkcor_26Feb2013.root";
    std::string flip_rate_file_name = "data/flip_rates/ssFL_data_standard_02222013.root";
    std::string sample_name         = "";
    std::string analysis_type_name  = "high_pt";
    std::string good_run_list       = "";
    int num_jets                    = 2;
//     std::string apply_jec_otf       = "";
    double jet_pt_cut               = -1;
    int run                         = -1;
    int lumi                        = -1;
    int event                       = -1;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"          , "print this menu")
        ("sample"        , po::value<std::string>(&sample_name)->required(), "REQUIRED: name of input sample (from at/Sample.h)"                                     )
        ("output"        , po::value<std::string>(&output_file)            , "output ROOT file for baby tree (default: <sample name>.root)"                          )
        ("input"         , po::value<std::string>(&input_file)             , "input ntuple (default is determined by the sample used)"                               )
        ("anal_type"     , po::value<std::string>(&analysis_type_name)     , "name of input sample (from AnalysisType.h)"                                            )
        ("nev"           , po::value<long>(&number_of_events)              , "number of events to run on (-1 == all)"                                                )
        ("verbose"       , po::value<bool>(&verbose)                       , "output debug info"                                                                     )
        ("lumi"          , po::value<double>(&luminosity)                  , "luminosity of analysis (1 fb^-1 default -- ignored for data)"                          )
        ("ntuple_type"   , po::value<std::string>(&ntuple_type_name)       , "ntuple type name (cms2, ss_skim, ...) (from at/Sample.h)"                              )
        ("fr"            , po::value<std::string>(&fake_rate_file_name)    , Form("fake rate file name (default: %s)", fake_rate_file_name.c_str())                  )
        ("fl"            , po::value<std::string>(&flip_rate_file_name)    , Form("flip rate file name (default: %s)", flip_rate_file_name.c_str())                  )
        ("run_list"      , po::value<std::string>(&good_run_list)          , "Good Run list (no default)"                                                            )
        ("njets"         , po::value<int>(&num_jets)                       , "minimum # of jets to select (default is 2)"                                            )
//         ("apply_jec_otf" , po::value<std::string>(&apply_jec_otf)          , "apply JEC on-the-fly using the specified global tag"                                   )
        ("jet_pt_cut"    , po::value<double>(&jet_pt_cut)                  , "jet pt threshold"                                                                      )
        ("run"           , po::value<int>(&run)                            , "select a specific run (negative numbers == all)"                                       )
        ("lumi"          , po::value<int>(&lumi)                           , "select a specific lumi (negative numbers == all)"                                      )
        ("event"         , po::value<int>(&event)                          , "select a specific event (negative numbers == all)"                                     )
        ;

    // parse it
    try
    {
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);

        if (vm.count("help")) 
        {
            cout << desc << "\n";
            return 1;
        }

        po::notify(vm);
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << "\nexiting" << endl;
        cout << desc << "\n";
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown error!" << "\n";
        return false;
    }

    cout << "inputs:" << endl;
    cout << "number_of_events   :\t" << number_of_events    << endl;
    cout << "luminosity         :\t" << luminosity          << endl;
    cout << "verbose            :\t" << verbose             << endl;
    cout << "sample_name        :\t" << sample_name         << endl;
    cout << "analysis_type_name :\t" << analysis_type_name  << endl;
    cout << "ntuple_type_name   :\t" << ntuple_type_name    << endl;
    cout << "output_file        :\t" << output_file         << endl;
    cout << "input_file         :\t" << input_file          << endl;
    cout << "fake_rate_file_name:\t" << fake_rate_file_name << endl;
    cout << "flip_rate_file_name:\t" << flip_rate_file_name << endl;
    cout << "good_run_list      :\t" << good_run_list       << endl;
    cout << "num_jets           :\t" << num_jets            << endl;
//     cout << "apply_jec_otf      :\t" << apply_jec_otf       << endl;
    cout << "jet_pt_cut         :\t" << jet_pt_cut          << endl;
    cout << "run                :\t" << run                 << endl;
    cout << "lumi               :\t" << lumi                << endl;
    cout << "event              :\t" << event               << endl;

    // test inputs boundary conditions
    // -------------------------------------------------------------------------------------------------//

//     // check that good run file file exists
//     if (!good_run_list.empty())
//     {
//         //good_run_list = analysis_path + "/" + good_run_list; 
//         if (!rt::exists(good_run_list))
//         {
//             cout << "[ss2012_make_single_lep_tree] Error: good run list file " << good_run_list << " not found" << endl;
//             cout << desc << "\n";
//             return 1;
//         }
//     }

    // check that fake rate root file exists 
    if (!fake_rate_file_name.empty())
    {
        //fake_rate_file_name = analysis_path + "/" + fake_rate_file_name; 
        if (!rt::exists(fake_rate_file_name))
        {
            cout << "[ss2012_make_single_lep_tree] Error: fake rate root file " << fake_rate_file_name << " not found" << endl;
            cout << desc << "\n";
            return 1;
        }
    }
    else
    {
        cout << "[ss2012_make_single_lep_tree] Error: fake rate root file not specified! Exiting..." << endl;
        cout << desc << "\n";
    }
 
    // check that flip rate root file exists 
    if (!flip_rate_file_name.empty())
    {
        //flip_rate_file_name = analysis_path + "/" + flip_rate_file_name; 
        if (!rt::exists(flip_rate_file_name))
        {
            cout << "[ss2012_make_single_lep_tree] Error: fake rate root file " << flip_rate_file_name << " not found" << endl;
            cout << desc << "\n";
            return 1;
        }
    }
    else
    {
        cout << "[ss2012_make_single_lep_tree] Error: fake rate root file not specified! Exiting..." << endl;
        cout << desc << "\n";
    }

    // do the main analysis
    // -------------------------------------------------------------------------------------------------//

    // input
    TChain* chain  = NULL;
    at::Sample::value_type sample = at::Sample::static_size; 
    ss::AnalysisType::value_type analysis_type = ss::GetAnalysisTypeFromName(analysis_type_name); 
	if (not sample_name.empty())
	{
        cout << "processing "  << sample_name << endl;
        sample = at::GetSampleFromName(sample_name);
	}
	else
	{
        cout << "no sample name given." << endl;
	}
    if (input_file.empty())
    {
        chain = at::GetSampleTChain(sample, at::GetNtupleTypeFromName(ntuple_type_name));
        if (output_file.empty())
        {
            output_file = Form("babies/singlelep/%s.root", sample_name.c_str());
        }
    }
    else
    {
        if (output_file.empty())
        {
            output_file = Form("babies/singlelep/%s.root", rt::filename(sample_name).c_str());
        }
        chain = rt::CreateTChainFromCommaSeperatedList(input_file, "Events");
    }

    cout << "sample has " << chain->GetEntries() << " entries" << endl;
    cout << "sample has " << chain->GetListOfFiles()->GetEntries() << " files" << endl;
    if (verbose) {rt::PrintFilesFromTChain(chain);}

    // scan the chain
    at::ScanChainWithFilename<CMS2>
    (
        chain, 
        SingleLeptonTreeLooper
        (
            output_file, 
            fake_rate_file_name,
            flip_rate_file_name,
            sample,
            analysis_type,
            luminosity,
            num_jets,
            jet_pt_cut,
            verbose
        ),
        cms2,
        number_of_events,
        good_run_list,
        /*fast=*/true,
        verbose,
        run,
        lumi,
        event
    ); 

    // cleanup
    delete chain;

    // done
    return 0;
}
catch (std::exception& e)
{
    cerr << "[ss2012_make_single_lep_tree] Error: failed..." << endl;
    cerr << e.what() << endl;
    return 1;
}

