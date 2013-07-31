#include "EffAnalysisLooper.h"

// c++
#include <stdexcept>
#include <algorithm>
#include <fstream>

// cms2
//#include "CMS2.h"
#include "ssSelections.h"
#include "eventSelections.h"
//#include "trackSelections.h"
//#include "susySelections.h"
//#include "mcbtagSFuncert.h"
//#include "mcSelections.h"
//#include "electronSelections.h"
//#include "muonSelections.h"
//#include "jetSelections.h"
//#include "metSelections.h"
//#include "jetcorr/FactorizedJetCorrector.h"

// Tools
//#include "SameSignTree.h"
#include "at/Predicates.h"
#include "at/DileptonHypType.h"
//#include "at/DileptonChargeType.h"
//#include "at/VtxReweight.h"
//#include "at/GoodRun.h"
//#include "at/PrintIdIsoInfo.h"
//#include "rt/RootTools.h"
//#include "CTable.h"
//#include "GenParticleStruct.h"
//#include "EfficiencyModelTools.h"
//#include "ScaleFactors.h"
//#include "TTbarBreakDown.h"

// ROOT
#include "Math/LorentzVector.h"
//#include "Math/Vector2D.h"
#include "TH2F.h"

// typdefs
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
typedef std::vector<LorentzVector> vecLorentzVector;

using namespace tas;
using namespace std;
using namespace at;

// construct:
EffAnalysisLooper::EffAnalysisLooper
(
    const std::string& root_file_name,
    const Sample::value_type& sample,
    double luminosity,
    bool verbose
)
    : AnalysisWithTree(root_file_name, "tree", "baby tree for efficiency study")
    , m_sample(sample)
    , m_lumi(luminosity)
    , m_verbose(verbose)
{
    // begin job
    BeginJob();
}

// destroy:
EffAnalysisLooper::~EffAnalysisLooper()
{
}

// function operator: operate on each event
int EffAnalysisLooper::operator() (long event, const std::string& filename)
{
    // call base class operator
    return Analyze(event, filename);
}

// members:
void EffAnalysisLooper::BeginJob()
{
    // initialize branches
    m_evt.Reset();
    m_evt.SetBranches(*m_tree);
}

// get the best hyp
// criteria is closest to the zmass
struct CompareHyps
{
    bool operator() (size_t lhs, size_t rhs) const
    {
        const LorentzVector& lhs_p4 = tas::hyp_p4().at(lhs);
        const LorentzVector& rhs_p4 = tas::hyp_p4().at(rhs);
        return at::SortByDeltaM<LorentzVector>(91.1876)(lhs_p4, rhs_p4); 
    }
};

void EffAnalysisLooper::EndJob()
{
    // call base class end job
    AnalysisWithTree::EndJob();
}

int EffAnalysisLooper::Analyze(long event, const std::string& filename)
{
    try
    {
        // Reset Tree Variables
        // --------------------------------------------------------------------------------------------------------- //

        m_evt.Reset();

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

        // store the selected dilepton hypotheses
        vector<size_t> selected_hyps; 

        // loop over hypotheses
        if (m_verbose) {std::cout << "begin of hypothesis loop" << std::endl;}

        for (size_t ihyp = 0; ihyp != hyp_type().size(); ihyp++)
        {                
            // leptons variables
            //const LorentzVector& lt_p4 = hyp_lt_p4().at(ihyp);
            //const LorentzVector& ll_p4 = hyp_ll_p4().at(ihyp);
            const int lt_id                  = hyp_lt_id().at(ihyp);
            const int ll_id                  = hyp_ll_id().at(ihyp);
            const int lt_idx                 = hyp_lt_index().at(ihyp);
            const int ll_idx                 = hyp_ll_index().at(ihyp);
            const float dilep_mass           = hyp_p4().at(ihyp).M();

            // keep only mu mu events
            if (at::hyp_typeToHypType(hyp_type().at(ihyp)) != at::DileptonHypType::MUMU &&
                at::hyp_typeToHypType(hyp_type().at(ihyp)) != at::DileptonHypType::EE)
            {
                if (m_verbose) {std::cout << "hyp is not a mu mu event" << std::endl;}
                continue;
            }

            // require inside z-window
            if (dilep_mass < 71 || dilep_mass > 101)
            {
                if (m_verbose) {std::cout << "hyp fails inv mass cut" << std::endl;}
                continue;
            }

            // require ID
            if (not (samesign::isGoodLepton(lt_id, lt_idx) && samesign::isGoodLepton(ll_id, ll_idx)))
            {
                if (m_verbose) {std::cout << "hyp fails ID requirement" << std::endl;}
                continue;
            }

            // require truth matching
            if (not evt_isRealData()) 
            {
                const int lt_mc3_id    = abs(lt_id)==11 ? els_mc3_id().at(lt_idx)       : mus_mc3_id().at(lt_idx);
                const int ll_mc3_id    = abs(ll_id)==11 ? els_mc3_id().at(ll_idx)       : mus_mc3_id().at(ll_idx);
                const int lt_mc3_momid = abs(lt_id)==11 ? els_mc3_motherid().at(lt_idx) : mus_mc3_motherid().at(lt_idx);
                const int ll_mc3_momid = abs(ll_id)==11 ? els_mc3_motherid().at(ll_idx) : mus_mc3_motherid().at(ll_idx);

                // require OS SF matching
                bool ossf_matched = ((lt_mc3_id*ll_mc3_id) == /*13*-13=*/-169 || (lt_mc3_id*ll_mc3_id) == /*11*-11=*/-121);
                if (not ossf_matched)
                {
                    if (m_verbose) {std::cout << "hyp OSSF matching requirement" << std::endl;}
                    continue;
                }

                // require matched to Z
                bool z_matched = (lt_mc3_momid == 23 && ll_mc3_momid);
                if (not z_matched)
                {
                    if (m_verbose) {std::cout << "hyp Z matching requirement" << std::endl;}
                    continue;
                }
            }

            // if we got here, hyp is selected
            selected_hyps.push_back(ihyp);

        } // end looper over hypothesis

        if (m_verbose) {std::cout << "end of hypothesis loop" << std::endl;}

        if (selected_hyps.empty())
        {
            if (m_verbose) {std::cout << "no hyps to selected -- going to next event" << std::endl;}
            return 0;
        }

        // Set Tree Variables
        // --------------------------------------------------------------------------------------------------------- //

        // best hyp index
        std::sort(selected_hyps.begin(), selected_hyps.end(), CompareHyps());
        const size_t hyp_idx = selected_hyps.front(); 

        // trigger (use SS)
        m_evt.trig_hpt = samesign::passesTriggerHighPt(hyp_idx);
        m_evt.trig_lpt = samesign::passesTriggerLowPt(hyp_idx);
        m_evt.trig_vpt = samesign::passesTriggerVeryLowPt(hyp_idx);

        // fill the tree
        m_evt.event_info.FillCommon(m_sample, filename);
        m_evt.FillCommon(hyp_idx);
        m_tree->Fill();

        // go to the next event
        return 0;
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
