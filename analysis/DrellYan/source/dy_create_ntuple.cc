// c++
#include <stdexcept>
#include <algorithm>

// BOOST
#include <boost/program_options.hpp>

// cms2
#include "CMS2.h"
#include "CMS2Wrapper.h"
#include "dySelections.h"
#include "eventSelections.h"
#include "trackSelections.h"
#include "susySelections.h"

// Tools
#include "DrellYanTree.h"
#include "CTable.h"
#include "at/AnalysisWithTree.h"
#include "at/Sample.h"
#include "at/GoodRun.h"
#include "at/VtxReweight.h"
#include "at/DileptonHypType.h"
#include "at/DileptonChargeType.h"
#include "at/ScanChain.h"
#include "rt/RootTools.h"
#include "GenParticleStruct.h"
#include "EfficiencyModelTools.h"

// typdefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef std::vector<LorentzVector> vecLorentzVector;

using namespace tas;
using namespace std;
using namespace at;

class ZAnalysisNtupler : public at::AnalysisWithTree
{
public:
    // construct:
    ZAnalysisNtupler
    (
        const std::string& root_file_name,
        const at::Sample::value_type& sample,
        const std::string& vtxreweight_file_name = "",
        const std::string& goodrun_file_name = "",
        const double luminosity = 1.0,
        const bool verbose = false
    );

    // destroy:
    ~ZAnalysisNtupler();

    // function operator:
    int operator() (long event, const std::string& filename);

    // members:
    virtual void BeginJob();
    virtual void EndJob();
    int Analyze(const long event, const std::string& filename);

private:
    // members:
    const at::Sample::value_type m_sample;
    const double m_lumi;
    const bool m_verbose;
    unsigned int m_hyp_count;
    unsigned int m_count_ee;
    unsigned int m_count_mm;

    // struct to hold tree values
    DrellYanTree m_evt;
};

// construct:
ZAnalysisNtupler::ZAnalysisNtupler
(
    const std::string& root_file_name,
    const Sample::value_type& sample,
    const std::string& vtxreweight_file_name,
    const std::string& goodrun_file_name,
    const double luminosity,
    const bool verbose
)
    : AnalysisWithTree(root_file_name, "tree", "baby tree for Z tutorial analysis")
    , m_sample(sample)
    , m_lumi(luminosity)
    , m_verbose(verbose)
    , m_hyp_count(0)
    , m_count_ee(0)
    , m_count_mm(0)
{
    // set vertex weight file
    if (!vtxreweight_file_name.empty())
    {
        cout << "[ZAnalysisNtupler] using vertex reweight file : " << vtxreweight_file_name << endl;
        set_vtxreweight_rootfile(vtxreweight_file_name.c_str(), m_verbose);
    }

    // set the "good run" list 
    if (!goodrun_file_name.empty())
    {
        set_goodrun_file(goodrun_file_name.c_str());
    }

    // begin job
    BeginJob();
}

// destroy:
ZAnalysisNtupler::~ZAnalysisNtupler()
{
}

// function operator: operate on each event
int ZAnalysisNtupler::operator() (long event, const std::string& filename)
{
    // call base class operator
    return Analyze(event, filename);
}

// members:
void ZAnalysisNtupler::BeginJob()
{
    // initialize branches
    m_evt.Reset();
    m_evt.SetBranches(*m_tree);
}

void ZAnalysisNtupler::EndJob()
{
    cout << "Number of dilepton hypotheses passing :\t" << m_hyp_count << endl;

    CTable yield_table;
    yield_table.setTitle("yields for Zanalysis Analysis:");
    yield_table.useTitle();
    yield_table.setTable() (                "mm",        "ee",                  "all")
                           ("count" , m_count_mm, m_count_ee, m_count_ee + m_count_mm) 
                           ;
    yield_table.print();

    AnalysisWithTree::EndJob();
}

int ZAnalysisNtupler::Analyze(const long event, const std::string& filename)
{
    try
    {
        // Reset Tree Variables
        // --------------------------------------------------------------------------------------------------------- //

        m_evt.Reset();

        // Event Cleaning
        // --------------------------------------------------------------------------------------------------------- //

        // require at least 3 tracks in the event
        if (trks_trk_p4().size() < 3)
        {
            if (m_verbose) {std::cout << "fails # trks >= 3 requirement" << std::endl;}
            m_tree->Fill();
            return 0;
        }

        // require standard cleaning 
        if (!cleaning_standardNovember2011()) 
        {
            if (m_verbose) {std::cout << "fails November2011 cleaning requirement" << std::endl;}
            m_tree->Fill();
            return 0;
        }

        // fill the generated event count
        // --------------------------------------------------------------------------------------------------------- //

        if (not evt_isRealData())
        {
            // is this a Drell-yan MC event? 
            const bool is_gen_z = (m_sample == at::Sample::dy); 
            //         std::vector<int>::const_iterator z_iter = std::find(genps_id().begin(), genps_id().end(), 23);
            if (is_gen_z)
            {
                // index of generator level Z
                size_t gen_z_idx  = -999999;
                size_t gen_d1_idx = -999999;
                size_t gen_d2_idx = -999999;
                for (size_t i = 0; i != genps_id().size(); i++)
                {
                    if (genps_status().at(i) != 3) {continue;}

                    // z boson
                    if (genps_id().at(i) == 23)
                    {
                        gen_z_idx = i;
                    }

                    // leptons
                    if (abs(genps_id().at(i)) == 11 or abs(genps_id().at(i)) == 13 or abs(genps_id().at(i)) == 15)
                    {
                        if (gen_d1_idx == -999999)
                        {
                            gen_d1_idx = i;
                        }
                        else if (gen_d2_idx == -999999)
                        {
                            gen_d2_idx = i;
                        }
                    }

                    // all are set --> break out of loop
                    if (gen_z_idx  != -999999 && gen_d1_idx != -999999 && gen_d2_idx != -999999)
                    {
                        break;
                    }
                }

                // order leptons by pT
                if (genps_p4().at(gen_d1_idx).pt() < genps_p4().at(gen_d2_idx).pt())
                {
                    std::swap(gen_d1_idx, gen_d2_idx);
                }

                // fill Z-boson branches
                m_evt.is_gen_z     = true;
                m_evt.gen_z_p4     = genps_p4().at(gen_z_idx);
                m_evt.gen_d1_p4    = genps_p4().at(gen_d1_idx);
                m_evt.gen_d2_p4    = genps_p4().at(gen_d2_idx);
                m_evt.gen_d1_pdgid = genps_id().at(gen_d1_idx);
                m_evt.gen_d2_pdgid = genps_id().at(gen_d2_idx);
                m_evt.gen_z_type   = PdgidToHypType(m_evt.gen_d1_pdgid, m_evt.gen_d2_pdgid);
                m_evt.is_z_ee      = (m_evt.gen_d1_pdgid*m_evt.gen_d2_pdgid == -121);
                m_evt.is_z_mm      = (m_evt.gen_d1_pdgid*m_evt.gen_d2_pdgid == -169);
                m_evt.is_z_tt      = (m_evt.gen_d1_pdgid*m_evt.gen_d2_pdgid == -225);
                m_evt.is_acc       = (m_evt.gen_d1_p4.pt()<25 && m_evt.gen_d1_p4.pt()<25) &&
                                     (fabs(m_evt.gen_d1_p4.eta())<2.5 && fabs(m_evt.gen_d1_p4.eta())<2.5);
            }

        }

        // gen level hyps
//         if (not evt_isRealData())
//         {
//             for   
// 
//         }




//         // lepton variables
//         std::pair<GenParticleStruct, GenParticleStruct> best_gen_hyp = efftools::getGenHyp(25, 25, DileptonChargeType::static_size);
//         if (best_gen_hyp.first.id_ == 0 || best_gen_hyp.second.id_ == 0)
//         {
//             if (m_verbose) {cout << "does not have a good gen hyp" << endl;} 
//             m_evt.gen_dilep_type = at::DileptonHypType::static_size; 
//         }
//         else
//         {
//             int   id1  = abs(best_gen_hyp.first.id_ ) == 15 ? best_gen_hyp.first.did_   : best_gen_hyp.first.id_;
//             int   idx1 = abs(best_gen_hyp.first.id_ ) == 15 ? best_gen_hyp.first.didx_  : best_gen_hyp.first.idx_;
//             int   id2  = abs(best_gen_hyp.second.id_) == 15 ? best_gen_hyp.second.did_  : best_gen_hyp.second.id_;
//             int   idx2 = abs(best_gen_hyp.second.id_) == 15 ? best_gen_hyp.second.didx_ : best_gen_hyp.second.idx_;
// 
//             // get LorenzVectors
//             LorentzVector p41;
//             if (abs(best_gen_hyp.first.id_) == 15)
//             { 
//                 p41 = genps_lepdaughter_p4().at(best_gen_hyp.first.idx_).at(idx1);
//             }
//             else
//             {
//                 p41 = genps_p4().at(idx1);
//             }
// 
//             LorentzVector p42;
//             if (abs(best_gen_hyp.second.id_) == 15)
//             {
//                 p42 = genps_lepdaughter_p4().at(best_gen_hyp.second.idx_).at(idx2);
//             }
//             else
//             {
//                 p42 = genps_p4().at(idx2);
//             }
// 
//             m_evt.is_gen_pp      = id1<0 && id2<0;  // -11 is a positron, 11 is an electron
//             m_evt.is_gen_mm      = id1>0 && id2>0;  // -11 is a positron, 11 is an electron
//             m_evt.gen_lep1_p4    = p41.pt() > p42.pt() ? p41 : p42;
//             m_evt.gen_lep1_pdgid = p41.pt() > p42.pt() ? id1 : id1;
//             m_evt.gen_lep2_p4    = p41.pt() > p42.pt() ? p42 : p41;
//             m_evt.gen_lep2_pdgid = p41.pt() > p42.pt() ? id2 : id1;
//             m_evt.gen_dilep_p4   = (p41 + p42);
//             m_evt.gen_dilep_type = efftools::getHypType(id1, id2);
//             m_evt.gen_dilep_mass = m_evt.gen_dilep_p4.mass();
//             m_evt.gen_dilep_dphi = rt::DeltaPhi(p41, p42); 
//             m_evt.gen_dilep_deta = rt::DeltaEta(p41, p42); 
//             m_evt.gen_dilep_dr   = rt::DeltaR(p41, p42); 
//         }

        // Analysis Selections
        // --------------------------------------------------------------------------------------------------------- //

        int best_hyp = -99999;

        // loop over hypotheses
        for (size_t hyp_idx = 0; hyp_idx != hyp_type().size(); hyp_idx++)
        {                
            // leptons variables
            int lt_id  = hyp_lt_id().at(hyp_idx);
            int ll_id  = hyp_ll_id().at(hyp_idx);
            int lt_idx = hyp_lt_index().at(hyp_idx);
            int ll_idx = hyp_ll_index().at(hyp_idx);

            //// check if hyp passes trigger
            //if (evt_isRealData() && !dy::passesTrigger(hyp_type().at(hyp_idx)))
            //{
            //    if (m_verbose) {std::cout << "fails trigger requirement" << std::endl;}
            //    continue;
            //}            

            //// check that they are opposite sign
            //if ((hyp_lt_charge().at(hyp_idx) * hyp_ll_charge().at(hyp_idx)) > 0)
            //{
            //    if (m_verbose) {std::cout << "fails opposite sign requirement" << std::endl;}
            //    continue;
            //}

            //// check that they are the same flavor
            //const DileptonHypType::value_type flavor_type = hyp_typeToHypType(hyp_type().at(hyp_idx));
            //if (not(flavor_type == DileptonHypType::EE or flavor_type == DileptonHypType::MUMU))
            //{
            //    if (m_verbose) {std::cout << "fails same flavor requirement" << std::endl;}
            //    continue;
            //}

            //// check hyp mass (no low mass resonances)
            //const float dilep_mass = sqrt(fabs(hyp_p4().at(hyp_idx).mass2()));
            //if (not (60 < dilep_mass && dilep_mass < 120.0))
            //{
            //    if (m_verbose) {std::cout << "fails dilepton invariant mass requirement" << std::endl;}
            //    continue;
            //}

            //// check that lepton pass selections
            //if (not dy::isSelectedLepton(lt_id, lt_idx))
            //{
            //    if (m_verbose) {std::cout << "lt fails lepton selection" << std::endl;}
            //    continue;
            //}
            //if (not dy::isSelectedLepton(ll_id, ll_idx))
            //{
            //    if (m_verbose) {std::cout << "ll fails lepton selection" << std::endl;}
            //    continue;
            //}

            //// check that leptons are from the same vertex
            //if (!hypsFromFirstGoodVertex(hyp_idx))
            //{
            //    if (m_verbose) {std::cout << "fails leptons are from the first good vertex requirement" << std::endl;}
            //    continue;
            //}

            // choose the best hypothesis
            best_hyp = dy::ChooseBetterHypothesis(best_hyp, hyp_idx);

        } // end looper over hypothesis
        
        if (m_verbose) {std::cout << "end of hypothesis loop" << std::endl;}

        // do not fill if there is no good hypothesis 
        // --------------------------------------------------------------------------------------------------------- //

        // all: 0, mm: 1, em: 2, ee: 3
        const int hyp_idx = best_hyp;
        if (hyp_idx < 0)
        {
            if (m_verbose) {std::cout << "no good hypthesis chosen" << std::endl;}
            m_tree->Fill();
            return 0;
        }
        else
        {
            if (m_verbose) {std::cout << "hypthesis chosen: " << hyp_idx << " of " << hyp_p4().size() << std::endl;}
        }
        const DileptonHypType::value_type flavor_type = ((hyp_idx < 0 or hyp_p4().empty()) ? DileptonHypType::static_size : hyp_typeToHypType(hyp_type().at(hyp_idx)));
 
        // Set Tree Variables
        // --------------------------------------------------------------------------------------------------------- //

        // event wieghts 

        //const float vtxw  = evt_isRealData() ? 1.0 : vtxweight_n(numberOfGoodVertices(), evt_isRealData(), false);
//         const float vtxw  = 1.0;
//         const float scale1fb = evt_isRealData() ? 1.0 : m_evt.event_info.scale1fb;
        //float scale          = evt_isRealData() ? 1.0 : m_lumi * scale1fb * vtxw; 

        // fill event level info 
        m_evt.event_info.FillCommon(m_sample, filename);
        m_evt.event_info.uncorpfmet     = evt_pfmet();
        m_evt.event_info.uncorpfmet_phi = evt_pfmetPhi();
        const float met                 = m_evt.event_info.pfmet;
        const float met_phi             = m_evt.event_info.pfmet_phi;

        // fill the dilepton analysis independent variables 
        m_evt.FillCommon(hyp_idx);

        // DY specific event level info

        // set lepton info (lep1 is higher pT lepton, lep2 is lower pT lepton)
        int lep1_id;
        int lep1_idx;
        int lep2_id;
        int lep2_idx;
        if (hyp_lt_p4().at(hyp_idx).pt() > hyp_ll_p4().at(hyp_idx).pt())
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
        m_evt.lep1.corpfiso    = dy::leptonIsolation(lep1_id, lep1_idx);
        m_evt.lep1.corpfiso04  = (lep1_is_el) ? dy::electronIsolationPF2012_cone04(lep1_idx) : -999999.0;  
        m_evt.lep1.effarea     = dy::EffectiveArea03(lep1_id, lep1_idx); 
        m_evt.lep1.effarea04   = dy::EffectiveArea04(lep1_id, lep1_idx);
        m_evt.lep1.dbeta       = (lep1_is_mu) ? mus_isoR03_pf_PUPt().at(lep1_idx) : -99999.0;
        m_evt.lep1.dbeta04     = (lep1_is_mu) ? mus_isoR04_pf_PUPt().at(lep1_idx) : -99999.0;
        m_evt.lep1.mt          = rt::Mt(m_evt.lep1.p4, met, met_phi);
        m_evt.lep1.passes_id   = dy::isGoodLepton(lep1_id, lep1_idx);
        m_evt.lep1.passes_iso  = dy::isIsolatedLepton(lep1_id, lep1_idx);

        m_evt.lep2.cordetiso   = m_evt.lep2.detiso   - (log(m_evt.lep2.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep2.p4.pt()); // check that I have the correct formula 
        m_evt.lep2.cordetiso04 = m_evt.lep2.detiso04 - (log(m_evt.lep2.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep2.p4.pt()); // check that I have the correct formula 
        m_evt.lep2.corpfiso    = dy::leptonIsolation(lep2_id, lep2_idx);
        m_evt.lep2.corpfiso04  = (lep2_is_el) ? dy::electronIsolationPF2012_cone04(lep2_idx) : -999999.0;  
        m_evt.lep2.effarea     = dy::EffectiveArea03(lep2_id, lep2_idx);
        m_evt.lep2.effarea04   = dy::EffectiveArea04(lep2_id, lep2_idx);
        m_evt.lep2.dbeta       = (lep2_is_mu) ? mus_isoR03_pf_PUPt().at(lep2_idx) : -99999.0;
        m_evt.lep2.dbeta04     = (lep2_is_mu) ? mus_isoR04_pf_PUPt().at(lep2_idx) : -99999.0;
        m_evt.lep2.mt          = rt::Mt(m_evt.lep2.p4, met, met_phi);
        m_evt.lep2.passes_id   = dy::isGoodLepton(lep2_id, lep2_idx);
        m_evt.lep2.passes_iso  = dy::isIsolatedLepton(lep2_id, lep2_idx);

        // electron isolation correction variables
        m_evt.rho_iso = evt_kt6pf_foregiso_rho();
        m_evt.rho     = evt_ww_rho_vor(); 
//         m_evt.event_info.vtwx    = vtxw;
//         m_evt.event_info.lumi    = m_lumi;

        // flavor
        m_evt.is_mm = (flavor_type==DileptonHypType::MUMU);
        m_evt.is_ee = (flavor_type==DileptonHypType::EE);

        // Fill the tree
        m_tree->Fill();

        // counts for printout
        m_hyp_count++; 
        switch (flavor_type)
        {
            case DileptonHypType::MUMU: m_count_mm++; break;
            case DileptonHypType::EE  : m_count_ee++; break;
            default:
                if (m_verbose) {std::cout << "not ee or mm -- bug!!" << std:: endl;}
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


// -------------------------------------------------------------------------------------------------//
// main program
// -------------------------------------------------------------------------------------------------//

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
    std::string sample_name         = "";
    std::string vtxreweight_file    = "";
    std::string good_run_list       = "";
    int run                         = -1;
    int lumi                        = -1;
    int event                       = -1;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help"          , "print this menu")
        ("sample"        , po::value<std::string>(&sample_name)->required(), "REQUIRED: name of input sample (from at/Sample.h)"           )
        ("output"        , po::value<std::string>(&output_file)            , "output ROOT file for baby tree (default: <sample name>.root)")
        ("input"         , po::value<std::string>(&input_file)             , "input ntuple (default is determined by the sample used)"     )
        ("nev"           , po::value<long>(&number_of_events)              , "number of events to run on (-1 == all)"                      )
        ("verbose"       , po::value<bool>(&verbose)                       , "output debug info"                                           )
        ("lumi"          , po::value<double>(&luminosity)                  , "luminosity of analysis (1 fb^-1 default -- ignored for data)")
        ("ntuple_type"   , po::value<std::string>(&ntuple_type_name)       , "ntuple type name (cms2, ss_skim, ...) (from at/Sample.h)"    )
        ("vtx_file"      , po::value<std::string>(&vtxreweight_file)       , "ROOT file for the vertex reweight (ignored for data)"        )
        ("run_list"      , po::value<std::string>(&good_run_list)          , "Good Run list (no default)"                                  )
        ("run"           , po::value<int>(&run)                            , "select a specific run (negative numbers == all)"             )
        ("ls"            , po::value<int>(&lumi)                           , "sselect a specific lumi (negative numbers == all)"           )
        ("event"         , po::value<int>(&event)                          , "select a specific event (negative numbers == all)"           )
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
    cout << "ntuple_type_name   :\t" << ntuple_type_name    << endl;
    cout << "output_file        :\t" << output_file         << endl;
    cout << "input_file         :\t" << input_file          << endl;
    cout << "vtxreweight_file   :\t" << vtxreweight_file    << endl;
    cout << "good_run_list      :\t" << good_run_list       << endl;
    cout << "run                :\t" << run                 << endl;
    cout << "lumi               :\t" << lumi                << endl;
    cout << "event              :\t" << event               << endl;

    // test inputs boundary conditions
    // -------------------------------------------------------------------------------------------------//

    // check that vertex reweight file exists
    if (!vtxreweight_file.empty())
    { 
        //vtxreweight_file = analysis_path + "/" + vtxreweight_file; 
        if (!rt::exists(vtxreweight_file))
        {
            cout << "[dy_create_ntuple] Error: vertex reweight file " << vtxreweight_file << " not found" << endl;
            cout << desc << "\n";
            return 1;
        }
    }

    // check that good run file file exists
    if (!good_run_list.empty())
    {
        //good_run_list = analysis_path + "/" + good_run_list; 
        if (!rt::exists(good_run_list))
        {
            cout << "[dy_create_ntuple] Error: good run list file " << good_run_list << " not found" << endl;
            cout << desc << "\n";
            return 1;
        }
    }

    // do the main analysis
    // -------------------------------------------------------------------------------------------------//

    // input
    TChain* chain = NULL;
    at::Sample::value_type sample = at::Sample::static_size; 
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
            output_file = Form("babies/%s.root", sample_name.c_str());
        }
    }
    else
    {
        if (output_file.empty())
        {
            output_file = Form("babies/%s.root", rt::filename(sample_name).c_str());
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
        ZAnalysisNtupler  
        (
            output_file,
            sample,
            vtxreweight_file, 
            good_run_list,
            luminosity,
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
    cerr << "[dy_create_ntuple] Error: failed..." << endl;
    cerr << e.what() << endl;
    return 1;
}
