#include "AnalysisLooper.h"

// c++
#include <stdexcept>
#include <algorithm>
#include <fstream>

// cms2
#include "CMS2.h"
#include "ssSelections.h"
#include "eventSelections.h"
#include "trackSelections.h"
#include "susySelections.h"
#include "mcbtagSFuncert.h"
#include "mcSelections.h"

// Tools
#include "SameSignTree.h"
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

// event type names
struct EventType
{
    enum value_type
    {
        SS,
        SF,
        DF,
        OS,
        static_size
    };
};


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

// set then numerator bool
bool IsNumerator(std::pair<size_t, DileptonChargeType::value_type>& hyp, bool is_lt)
{
    if (hyp.second == DileptonChargeType::static_size)
    {
        return false;
    }
    switch (hyp.second)
    {
        case DileptonChargeType::DF: return false; break;
        case DileptonChargeType::SS: return true; break;
        case DileptonChargeType::SF: 
        {
            bool lt_num = samesign::isNumeratorLepton(cms2.hyp_lt_id().at(hyp.first), cms2.hyp_lt_index().at(hyp.first));
            bool ll_num = samesign::isNumeratorLepton(cms2.hyp_ll_id().at(hyp.first), cms2.hyp_ll_index().at(hyp.first));
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

bool IsDenominator(std::pair<size_t, DileptonChargeType::value_type>& hyp, bool is_lt)
{
    if (hyp.second == DileptonChargeType::static_size)
    {
        return false;
    }
    switch (hyp.second)
    {
        case DileptonChargeType::DF: return false; break;
        case DileptonChargeType::SS: return true; break;
        case DileptonChargeType::SF: 
        {
            bool lt_num = samesign::isNumeratorLepton(cms2.hyp_lt_id().at(hyp.first), cms2.hyp_lt_index().at(hyp.first));
            bool ll_num = samesign::isNumeratorLepton(cms2.hyp_ll_id().at(hyp.first), cms2.hyp_ll_index().at(hyp.first));
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

// place holder until I figure out the right thing
float EffectiveArea04(int, int)
{
    return -99999.0;
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
    vector<float>& btags = pfjets_combinedSecondaryVertexBJetTag();
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

//void PrintJetInfo(const std::string& label, const vector<LorentzVector>& jets_p4, const vector<float>& jets_disc)
//{
//    cout << label << ":" << endl;
//    for (size_t i = 0; i < jets_p4.size(); i++)
//    {
//        LorentzVector jet_p4 = jets_p4.at(i);
//        float disc           = jets_disc.at(i);
//        cout << Form("idx %d, pt %f, eta %f, phi %f, disc %f", (int)i, jet_p4.pt(), jet_p4.eta(), jet_p4.phi(), disc) << endl;
//    }
//}
//
//void PrintJetInfo(const std::string& label, const vector<LorentzVector>& jets_p4, const vector<LorentzVector>& jets_nearjet_p4,  const vector<float>& jets_nearjet_dr, const vector<float>& jets_disc)
//{
//    cout << Form("%s: (%d, %d, %d)", label.c_str(), (int)jets_p4.size(), (int)jets_nearjet_dr.size(), (int)jets_nearjet_p4.size())  << endl;
//    for (size_t i = 0; i < jets_p4.size(); i++)
//    {
//        LorentzVector jet_p4 = jets_p4.at(i);
//        float disc           = jets_disc.at(i);
//        float nj_pt          = jets_nearjet_p4.at(i).pt();
//        float nj_dr          = jets_nearjet_dr.at(i);
//        cout << Form("idx %d, pt %f, eta %f, phi %f, disc %f, nearjet pt %f, nearjet dr %f", (int)i, jet_p4.pt(), jet_p4.eta(), jet_p4.phi(), disc, nj_pt, nj_dr) << endl;
//    }
//}

void PrintForSync(int ihyp, enum JetType jet_type, float jet_met_scale)
{
	// convenience
	const LorentzVector& lt_p4 = hyp_lt_p4().at(ihyp);
	const LorentzVector& ll_p4 = hyp_ll_p4().at(ihyp);
	int lt_id                  = hyp_lt_id().at(ihyp);
	int ll_id                  = hyp_ll_id().at(ihyp);
	int lt_idx                 = hyp_lt_index().at(ihyp);
	int ll_idx                 = hyp_ll_index().at(ihyp);
	bool lt_passes_id          = samesign::isGoodLepton(lt_id, lt_idx);
	bool ll_passes_id          = samesign::isGoodLepton(ll_id, ll_idx);
	float lt_iso               = (abs(lt_id) == 11) ? samesign::electronIsolationPF2012(lt_idx) : muonIsoValuePF2012_deltaBeta(lt_idx);
	float ll_iso               = (abs(ll_id) == 11) ? samesign::electronIsolationPF2012(ll_idx) : muonIsoValuePF2012_deltaBeta(ll_idx);

	// channel names
	const size_t n_channel_names = 4; 
	const std::string channel_names[n_channel_names] = {"All", "MM", "EM", "EE"};

	int num_jets = samesign::nJets(ihyp, jet_type, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt2>*/20.0);
	int num_btags = samesign::nBtaggedJets(ihyp, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0);

	// print the leptons sorted by pT
	LorentzVector l1_p4        = lt_p4;
	float         l1_pt        = lt_p4.pt();
	int           l1_id        = lt_id;
	int           l1_idx       = lt_idx;
	float         l1_iso       = lt_iso;
	bool          l1_passes_id = lt_passes_id;
	LorentzVector l2_p4        = ll_p4;
	float         l2_pt        = ll_p4.pt();
	int           l2_id        = ll_id;
	int           l2_idx       = ll_idx;
	float         l2_iso       = ll_iso;
	bool          l2_passes_id = ll_passes_id;
	if (l2_pt > l1_pt)
	{
		std::swap(l1_p4        ,l2_p4       );
		std::swap(l1_pt        ,l2_pt       );
		std::swap(l1_id        ,l2_id       );
		std::swap(l1_idx       ,l2_idx      );
		std::swap(l1_iso       ,l2_iso      );
		std::swap(l1_passes_id ,l2_passes_id);
	}

	float ht  = samesign::sumJetPt(ihyp, jet_type, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, jet_met_scale);
	float met = evt_pfmet_type1cor();
	int type  = at::hyp_typeToHypType(hyp_type().at(ihyp));

	if (samesign::isNumeratorHypothesis(ihyp))
	{
		//cout << "Run | LS | Event | channel | Lep1Pt | Lep1Eta | Lep1Phi | Lep1ID | Lep1Iso | Lep2Pt | Lep2Eta | Lep2Phi | Lep2ID | Lep1Iso | MET | HT | nJets | nbJets" << endl;
		cout << Form("%6u | %3u | %12u | %s | %4.3f | %2.3f | %2.3f | %u | %4.3f | %4.3f | %2.3f | %2.3f | %u | %4.3f | %4.3f | %4.3f | %u | %u",
				evt_run(), evt_lumiBlock(), evt_event(),
				channel_names[type].c_str(),
				l1_p4.pt(), l1_p4.eta(), l1_p4.phi(), l1_passes_id, l1_iso,
				l2_p4.pt(), l2_p4.eta(), l2_p4.phi(), l2_passes_id, l2_iso,
				met,
				ht,
				num_jets,
				num_btags) << endl;
	}
	else
	{
		cout << Form("%6u | %3u | %12u | %s | %4.3f | %2.3f | %2.3f | %u | %4.3f | %4.3f | %2.3f | %2.3f | %u | %4.3f | %4.3f | %s | %s | %s",
				evt_run(), evt_lumiBlock(), evt_event(),
				channel_names[type].c_str(),
				l1_p4.pt(), l1_p4.eta(), l1_p4.phi(), l1_passes_id, l1_iso,
				l2_p4.pt(), l2_p4.eta(), l2_p4.phi(), l2_passes_id, l2_iso,
				met,
				"-",
				"-",
				"-") << endl;
	}

	//if (evt_run() == 191247 && evt_lumiBlock() == 189 && evt_event() == 281392234)
	//if (evt_run() == 191247 && evt_lumiBlock() == 59 && evt_event() == 91075424)
	//if ((evt_run() == 191247 && evt_lumiBlock() == 59 && evt_event() == 91551153))
	//if ((evt_run() == 191247 && evt_lumiBlock() == 59 && evt_event() == 90509753))
	//if ((evt_run() == 190736 && evt_lumiBlock() == 143 && evt_event() == 147343009))
	//if ((evt_run() == 190736 && evt_lumiBlock() == 143 && evt_event() == 147655281))
	//if ((evt_run() == 191247 && evt_lumiBlock() == 60 && evt_event() == 93008232))
	//if ((evt_run() == 191247 && evt_lumiBlock() == 60 && evt_event() == 92441355))
	//if ((evt_run() == 191247 && evt_lumiBlock() == 60 && evt_event() == 93455346))
	//if ((evt_run() == 191247 && evt_lumiBlock() == 66 && evt_event() == 102084731))
	if ((evt_run() == 190736  && evt_lumiBlock() == 144 && evt_event() == 148335250))
	{
		cout << "ID lepton 1: "; PrintIdInfo(l1_id, l1_idx);
		cout << "ID lepton 2: "; PrintIdInfo(l2_id, l2_idx);
		cout << "ID iso 1: "; PrintIsoInfo(l1_id, l1_idx);
		cout << "ID iso 2: "; PrintIsoInfo(l2_id, l2_idx);
	}
}

// construct:
SSAnalysisLooper::SSAnalysisLooper
(
     const std::string& root_file_name,
     const Sample::value_type& sample,
     const std::string& fake_rate_file_name,
     const std::string& flip_rate_file_name,
     const std::string& fake_rate_hist_name,
     const std::string& goodrun_file_name,
     const std::string& vtxreweight_file_name,
     double luminosity,
     bool sparms,
     int  jetMetScale,
     bool is_fast_sim,
	 bool sync_print,
     bool verbose
)
    : AnalysisWithTree(root_file_name, "tree", "baby tree for SS2012 analysis")
    , m_sample(sample)
    , m_lumi(luminosity)
    , m_jetMetScale(jetMetScale)
    , m_is_fast_sim(is_fast_sim)
    , m_sparms(sparms)
	, m_sync_print(sync_print)
    , m_verbose(verbose)
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

    // initialize counters
    for (size_t i = 0; i != m_count_ss.size(); i++) {m_count_ss.at(i)=0.0;}
    for (size_t i = 0; i != m_count_sf.size(); i++) {m_count_sf.at(i)=0.0;}
    for (size_t i = 0; i != m_count_df.size(); i++) {m_count_df.at(i)=0.0;}
    for (size_t i = 0; i != m_count_os.size(); i++) {m_count_os.at(i)=0.0;}

    for (size_t i = 0; i != m_count_nobtag_ss.size(); i++) {m_count_nobtag_ss.at(i)=0.0;}
    for (size_t i = 0; i != m_count_nobtag_sf.size(); i++) {m_count_nobtag_sf.at(i)=0.0;}
    for (size_t i = 0; i != m_count_nobtag_df.size(); i++) {m_count_nobtag_df.at(i)=0.0;}
    for (size_t i = 0; i != m_count_nobtag_os.size(); i++) {m_count_nobtag_os.at(i)=0.0;}

    // set the fake rate histograms
    std::auto_ptr<TFile> fake_rate_file(rt::OpenRootFile(fake_rate_file_name));
    cout << "using FR file : " << fake_rate_file->GetName() << endl;
    h_mufr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get(fake_rate_hist_name.c_str())->Clone()));
    //h_mufr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get("h_mufr40c")->Clone()));
    h_elfr.reset(dynamic_cast<TH2F*>(fake_rate_file->Get("h_elfr40c")->Clone()));
    if (not h_mufr) {throw std::runtime_error("ERROR: SSAnalysisLooper: h_mufr40c doesn't exist");}
    h_mufr->SetDirectory(0);
    if (not h_elfr) {throw std::runtime_error("ERROR: SSAnalysisLooper: h_elfr40c doesn't exist");}
    h_elfr->SetDirectory(0);

    cout << "using mu FR hist : " << h_mufr->GetName() << endl;
    cout << "using el FR hist : " << h_elfr->GetName() << endl;

    // set the fake rate histograms
    std::auto_ptr<TFile> flip_rate_file(rt::OpenRootFile(flip_rate_file_name));
    cout << "using FL file : " << flip_rate_file->GetName() << endl;
    h_flip.reset(dynamic_cast<TH2F*>(flip_rate_file->Get("flipRate")->Clone()));
    if (not h_flip) {throw std::runtime_error("ERROR: SSAnalysisLooper: flipRate doesn't exist");}
    h_flip->SetDirectory(0);

    // begin job
    BeginJob();
}

// destroy:
SSAnalysisLooper::~SSAnalysisLooper()
{
    EndJob();
}

// function operator: operate on each event
int SSAnalysisLooper::operator() (long event)
{
    // call base class operator
    return Analyze(event);
}

// members:
void SSAnalysisLooper::BeginJob()
{
    // initialize branches
    m_evt.Reset();
    m_evt.SetBranches(*m_tree);

	if (m_sync_print)
	{
		cout << "Run | LS | Event | channel | " 
			    "Lep1Pt | Lep1Eta | Lep1Phi | Lep1ID | Lep1Iso | "
				"Lep2Pt | Lep2Eta | Lep2Phi | Lep2ID | Lep1Iso | "
				"MET | HT | nJets | nbJets" << endl;
	}
}


void SSAnalysisLooper::EndJob()
{
    CTable yield_table;
    yield_table.setTitle("yields for SS Analysis 2012 (# btags >= 2)");
    yield_table.useTitle();
    yield_table.setTable() (                      "mm",         "em",          "ee",          "all")
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
}

int SSAnalysisLooper::Analyze(long event)
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
        if (!(evt_run() == 190736  && evt_lumiBlock() == 144 && evt_event() == 148335250))
        {
            return 0;
        }

        // Reset Tree Variables
        // --------------------------------------------------------------------------------------------------------- //

        m_evt.Reset();

        // set good good runs 
        // --------------------------------------------------------------------------------------------------------- //

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

        // needs to be at least one good hypthesis
        if (hyp_type().empty())
        {
            if (m_verbose) {std::cout << "no good hypothesises" << std::endl;}
            return 0; 
        }

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

			// print for syncing
			if (m_sync_print)
			{
				PrintForSync(ihyp, jet_type, m_jetMetScale);
			}

            // check extra Z veto
            if (samesign::makesExtraZ(ihyp))
            {
                if (m_verbose) {std::cout << "fails btag extra Z veto requirement" << std::endl;}
                continue;
            }

            // check if event passes num_jet cut
            //int num_jets = samesign::nJets(ihyp, jet_type, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt2>*/20.0);
            //if (num_jets < 2)
            //{
            //    if (m_verbose) {std::cout << "fails # jets requirement" << std::endl;}
            //    continue;
            //}

            //// check if events passes num_btags cut
            //int num_btags = samesign::nBtaggedJets(ihyp, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0);
            //if (num_btags < 2)
            //{
            //    if (m_verbose) {std::cout << "fails # btags requirement" << std::endl;}
            //    //continue;
            //}

            // skip if both are not numerators
            if (!samesign::isDenominatorLepton(lt_id, lt_idx) || !samesign::isDenominatorLepton(ll_id, ll_idx))
            {
                if (m_verbose) {std::cout << "fails both leptons are at least denominator requirement" << std::endl;}
                continue;
            }

            // OS (Here a kludge by Claudio to quickly change the meaning of SS and OS .... useful for ttbar as sstop)
            int dummy = 1;
            //if (m_switchSigns) dummy=-1;
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

        // don't write events to the tree that don't pass hypothesis
        if (event_type == DileptonChargeType::static_size)
        {
            if (m_verbose) {std::cout << "fails good event type requirement" << std::endl;}
            return 0;
        }

        // all: 0, mm: 1, em: 2, ee: 3
        DileptonHypType::value_type dilepton_type = hyp_typeToHypType(hyp_type().at(hyp_idx));

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

        // fill the dilepton analysis independent variables 
        m_evt.FillCommon(hyp_idx);

        // fill analysis specific branches 
        m_evt.vtxw = vtxw;

        // sparms parameters
        if (m_sparms) 
        {
            int n_sparms = sparm_values().size();
            if (n_sparms > 0) m_evt.sparm0 = sparm_values().at(0);
            if (n_sparms > 1) m_evt.sparm1 = sparm_values().at(1);
            if (n_sparms > 2) m_evt.sparm2 = sparm_values().at(2);
            if (n_sparms > 3) m_evt.sparm3 = sparm_values().at(3);
        }

        // set lepton info (lep1 is higher pT lepton, lep2 is lower pT lepton)
        float lt_pt = hyp_lt_p4().at(hyp_idx).pt();
        float ll_pt = hyp_ll_p4().at(hyp_idx).pt();
        bool lt_fo  = IsDenominator(best_hyp, /*is_lt=*/true);  
        bool lt_num = IsNumerator  (best_hyp, /*is_lt=*/true);  
        bool ll_fo  = IsDenominator(best_hyp, /*is_lt=*/false);  
        bool ll_num = IsNumerator  (best_hyp, /*is_lt=*/false);  

        int lep1_id;
        int lep1_idx;
        int lep2_id;
        int lep2_idx;
        bool lep1_fo = false;
        bool lep1_num = false;
        bool lep2_fo = false;
        bool lep2_num = false;
        if (lt_pt > ll_pt)
        {
            lep1_id  = cms2.hyp_lt_id().at(hyp_idx);
            lep1_idx = cms2.hyp_lt_index().at(hyp_idx); 
            lep1_fo  = lt_fo;
            lep1_num = lt_num;
            lep2_id  = cms2.hyp_ll_id().at(hyp_idx);    
            lep2_idx = cms2.hyp_ll_index().at(hyp_idx); 
            lep2_fo  = ll_fo;
            lep2_num = ll_num;
        }
        else
        {
            lep1_id  = cms2.hyp_ll_id().at(hyp_idx);
            lep1_idx = cms2.hyp_ll_index().at(hyp_idx); 
            lep1_fo  = ll_fo;
            lep1_num = ll_num;
            lep2_id  = cms2.hyp_lt_id().at(hyp_idx);    
            lep2_idx = cms2.hyp_lt_index().at(hyp_idx); 
            lep2_fo  = lt_fo;
            lep2_num = lt_num;
        }

        m_evt.lep1.cordetiso   = m_evt.lep1.detiso   - (log(m_evt.lep1.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep1.p4.pt()); // check that I have the correct formula 
        m_evt.lep1.cordetiso04 = m_evt.lep1.detiso04 - (log(m_evt.lep1.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep1.p4.pt()); // check that I have the correct formula 
        m_evt.lep1.corpfiso    = (abs(lep1_id)==11) ? samesign::electronIsolationPF2012(lep1_idx) : muonIsoValuePF2012_deltaBeta(lep1_idx);
        m_evt.lep1.corpfiso04  = -999999.0;   // this is not implemented yet 
        m_evt.lep1.effarea     = EffectiveArea03(lep1_id, lep1_idx);  // is there a diffenece for different cone sizes? 
        m_evt.lep1.effarea04   = -999999.0;   // is there a diffenece for different cone sizes?
        m_evt.lep1.dbeta       = (abs(lep1_id)==13) ? mus_isoR03_pf_PUPt().at(lep1_idx) : -99999.0;
        m_evt.lep1.dbeta04     = (abs(lep1_id)==13) ? mus_isoR04_pf_PUPt().at(lep1_idx) : -99999.0;
        m_evt.lep1.is_fo       = lep1_fo;
        m_evt.lep1.is_num      = lep1_num;
        m_evt.lep1.is_conv     = false; 
        m_evt.lep1.is_loosemu  = false; 
        //m_evt.lep1.mt          = rt::Mt(m_evt.lep1.p4, evt_pfmet_type1cor(), evt_pfmetPhi_type1cor());
        m_evt.lep1.mt          = rt::Mt(m_evt.lep1.p4, evt_pfmet(), evt_pfmetPhi());
        m_evt.lep1.passes_id   = samesign::isGoodLepton(lep1_id, lep1_idx);
        m_evt.lep1.passes_iso  = samesign::isIsolatedLepton(lep1_id, lep1_idx);
        m_evt.lep1_wfr         = GetFakeRateValue(lep1_id, lep1_idx);
        m_evt.lep1_wflip       = GetFlipRateValue(lep1_id, lep1_idx);

        m_evt.lep2.cordetiso   = m_evt.lep2.detiso   - (log(m_evt.lep2.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep2.p4.pt()); // check that I have the correct formula 
        m_evt.lep2.cordetiso04 = m_evt.lep2.detiso04 - (log(m_evt.lep2.p4.pt())*numberOfGoodVertices())/(30.0*m_evt.lep2.p4.pt()); // check that I have the correct formula 
        m_evt.lep2.corpfiso    = (abs(lep2_id)==11) ? samesign::electronIsolationPF2012(lep2_idx) : muonIsoValuePF2012_deltaBeta(lep2_idx);
        m_evt.lep2.corpfiso04  = -999999.0;   // this is not implemented yet 
        m_evt.lep2.effarea     = EffectiveArea03(lep2_id, lep2_idx);  // is there a diffenece for different cone sizes? 
        m_evt.lep2.effarea04   = -999999.0;   // is there a diffenece for different cone sizes?
        m_evt.lep2.dbeta       = (abs(lep2_id)==13) ? mus_isoR03_pf_PUPt().at(lep2_idx) : -99999.0;
        m_evt.lep2.dbeta04     = (abs(lep2_id)==13) ? mus_isoR04_pf_PUPt().at(lep2_idx) : -99999.0;
        m_evt.lep2.is_fo       = lep2_fo; 
        m_evt.lep2.is_num      = lep2_num;
        m_evt.lep2.is_conv     = false; 
        m_evt.lep2.is_loosemu  = false; 
        m_evt.lep2.mt          = rt::Mt(m_evt.lep2.p4, evt_pfmet(), evt_pfmetPhi());
        m_evt.lep2.passes_id   = samesign::isGoodLepton(lep2_id, lep2_idx);
        m_evt.lep2.passes_iso  = samesign::isIsolatedLepton(lep2_id, lep2_idx);
        m_evt.lep2_wfr         = GetFakeRateValue(lep2_id, lep2_idx);
        m_evt.lep2_wflip       = GetFlipRateValue(lep2_id, lep2_idx);

        // event level info
        m_evt.event_info.pfmet        = evt_pfmet_type1cor();  // do we ever use the uncorrected pfmet?
        m_evt.event_info.pfmet_phi    = evt_pfmetPhi_type1cor();
        m_evt.event_info.corpfmet     = evt_pfmet_type1cor();
        m_evt.event_info.corpfmet_phi = evt_pfmetPhi_type1cor();
        
        // should we recalculate the met??
        if (m_jetMetScale != 0) 
        {  
            ROOT::Math::XYVector cmet;
            float metx = evt_pfmet_type1cor() * cos(evt_pfmetPhi_type1cor());
            float mety = evt_pfmet_type1cor() * sin(evt_pfmetPhi_type1cor());
            // get uncorrected jets
            vector<LorentzVector> ujets = samesign::getJets(hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/10.0, /*|eta|<*/5.0, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, 0);
            for (size_t u = 0; u != ujets.size(); u++) 
            {
                float px   = ujets.at(u).px();
                float py   = ujets.at(u).py();
                float pt   = ujets.at(u).pt();
                float eta  = ujets.at(u).pt();
                float corr = getJetMetSyst(m_jetMetScale, pt, eta);
                cmet.SetXY(metx - (corr-1.)*px, mety - (corr-1.)*py);
            }
            m_evt.event_info.corpfmet     = cmet.r(); 
            m_evt.event_info.corpfmet_phi = cmet.phi();
        }

        // SS specific event level info
        m_evt.ht           = samesign::sumJetPt(hyp_idx, jet_type,                     /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, m_jetMetScale);
        m_evt.ht20         = samesign::sumJetPt(hyp_idx, jet_type,                     /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, m_jetMetScale);
        m_evt.ht30         = samesign::sumJetPt(hyp_idx, jet_type,                     /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, m_jetMetScale);
        m_evt.njets        = samesign::nJets(hyp_idx, jet_type,                        /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt2>*/20.0, 1.0, m_jetMetScale);
        m_evt.njets20      = samesign::nJets(hyp_idx, jet_type,                        /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt2>*/20.0, 1.0, m_jetMetScale);
        m_evt.njets30      = samesign::nJets(hyp_idx, jet_type,                        /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt2>*/20.0, 1.0, m_jetMetScale);
        m_evt.nbtags       = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, m_jetMetScale);
        m_evt.nbtags20     = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, m_jetMetScale);
        m_evt.nbtags30     = samesign::nBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/30.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, m_jetMetScale);
        //m_evt.mt           = rt::Mt(m_evt.lep1.p4, evt_pfmet(), evt_pfmetPhi());  // calculated against the higher pT lepton
        m_evt.no_extraz    = (not samesign::makesExtraZ(hyp_idx));

        // Gen level info
        // NOTE: we fill the gen block if and only if BOTH leptons are matched 
        if (!evt_isRealData())
        {
            // gen Lep p4
            std::pair<GenParticleStruct, GenParticleStruct> gen_hyp = efftools::getGenHyp(/*pt1=*/20, /*pt2=*/20, DileptonChargeType::SS);
            if (gen_hyp.first.idx_!=999999 && gen_hyp.second.idx_!=999999)
            {
                m_evt.is_gen_mm = gen_hyp.first.id_>0 && gen_hyp.second.id_>0;
                m_evt.is_gen_pp = gen_hyp.first.id_<0 && gen_hyp.second.id_<0;

                // gen HT
                m_evt.gen_ht = efftools::getGenHT(/*pt_cut=*/40.0, /*eta_cut=*/2.4);

                // gen b quarks
                std::vector<LorentzVector> gen_bjets = efftools::getGenBjets(/*pt_cut=*/40.0, /*eta_cut=*/2.4);
                m_evt.gen_nbtags = gen_bjets.size();
                m_evt.vgenb_p4   = gen_bjets;

                // gen jets 
                std::vector<LorentzVector> gen_jets = efftools::getGenJets(/*pt_cut=*/40.0, /*eta_cut=*/2.4);
                m_evt.gen_njets   = gen_jets.size();
                m_evt.vgenjets_p4 = gen_jets;
            }
        }
        
        // classification
        m_evt.is_ss = (event_type==DileptonChargeType::SS);
        m_evt.is_sf = (event_type==DileptonChargeType::SF);
        m_evt.is_df = (event_type==DileptonChargeType::DF);
        m_evt.is_os = (event_type==DileptonChargeType::OS);
        m_evt.is_pp = hyp_lt_charge().at(hyp_idx)>0 && hyp_ll_charge().at(hyp_idx)>0; 
        m_evt.is_mm = hyp_lt_charge().at(hyp_idx)<0 && hyp_ll_charge().at(hyp_idx)<0; 

        // electron isolation correction variables
        m_evt.rho     = evt_kt6pf_foregiso_rho();
        m_evt.rho_iso = -999999.0;

        // eff and scale factors
        if (!evt_isRealData())
        {
            // scale factor for trigger efficiency
            m_evt.sf_trig        = dilepTriggerScaleFactor(hyp_idx);
            //m_evt.lep1.sf_trig   = triggerScaleFactor(TrigEffType::LeadDbl, lep1_id, m_evt.lep1.p4);  // this doesn't seem right
            //m_evt.lep2.sf_trig   = triggerScaleFactor(TrigEffType::LeadDbl, lep2_id, m_evt.lep2.p4);  // this doesn't seem right

            // scale factor for lepton reconstruction efficiency
            m_evt.sf_lepeff      = dileptonTagAndProbeScaleFactor(hyp_idx);
            m_evt.lep1.sf_lepeff = tagAndProbeScaleFactor(lep1_id, m_evt.lep1.p4.pt(), m_evt.lep1.p4.eta()); 
            m_evt.lep2.sf_lepeff = tagAndProbeScaleFactor(lep2_id, m_evt.lep2.p4.pt(), m_evt.lep2.p4.eta());

            // scale factor for # btags 
            vector<LorentzVector> bjets = samesign::getBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, m_jetMetScale);
            std::sort(bjets.begin(), bjets.end(), SortByPt<LorentzVector>());
            m_evt.sf_nbtag  = 0.0;
            m_evt.sf_nbtag3 = 0.0;
            if (m_evt.nbtags == 2) 
            {
                m_evt.sf_nbtag = btagEventWeight(m_evt.nbtags, bjets.at(0).pt(), bjets.at(1).pt(), 0., 0., m_is_fast_sim);
            }
            else if (m_evt.nbtags == 3) 
            {
                m_evt.sf_nbtag  = btagEventWeight (m_evt.nbtags, bjets.at(0).pt(), bjets.at(1).pt(), bjets.at(2).pt(), 0., m_is_fast_sim);
                m_evt.sf_nbtag3 = btagEventWeight3(m_evt.nbtags, bjets.at(0).pt(), bjets.at(1).pt(), bjets.at(2).pt(), 0., m_is_fast_sim);
            }
            else if (m_evt.nbtags > 3) 
            {
                m_evt.sf_nbtag  = btagEventWeight (4, bjets.at(0).pt(), bjets.at(1).pt(), bjets.at(2).pt(), bjets.at(3).pt(), m_is_fast_sim);
                m_evt.sf_nbtag3 = btagEventWeight3(4, bjets.at(0).pt(), bjets.at(1).pt(), bjets.at(2).pt(), bjets.at(3).pt(), m_is_fast_sim);
            }

            // Added the btag scale factor uncertainty (Claudio)
            // Note: pt and eta cuts, as necessary, will be made inside the code that calculates the scale factors
            // When there arent enough bquarks we put in some nominal bullshit value 
            std::vector<LorentzVector> gen_bjets = efftools::getGenBjets(/*pt_cut=*/0.001, /*eta_cut=*/2.5);
            std::sort(gen_bjets.begin(), gen_bjets.end(), SortByPt<LorentzVector>());
            if ( gen_bjets.size()==0) 
            {
                m_evt.sf_unc_nbtag   = btagEventUncertainty (2, 50.0, 0., 50.0, 0.0, 50.0, 0.0, 50.0, 0, m_is_fast_sim);
                m_evt.sf_unc_nbtag3  = btagEventUncertainty3(3, 50.0, 0., 50.0, 0.0, 50.0, 0.0, 50.0, 0, m_is_fast_sim);
            } 
            else if ( gen_bjets.size()==1) 
            {
                m_evt.sf_unc_nbtag  = btagEventUncertainty (2, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), 50.0, 0.0, 50.0, 0.0, 50.0, 0, m_is_fast_sim);
                m_evt.sf_unc_nbtag3 = btagEventUncertainty3(3, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), 50.0, 0.0, 50.0, 0.0, 50.0, 0, m_is_fast_sim);
            } 
            else if ( gen_bjets.size()==2) 
            {
                m_evt.sf_unc_nbtag  = btagEventUncertainty (2, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), gen_bjets.at(1).pt(), gen_bjets.at(1).eta(), 50.0, 0.0, 50.0, 0, m_is_fast_sim);
                m_evt.sf_unc_nbtag3 = btagEventUncertainty3(3, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), gen_bjets.at(1).pt(), gen_bjets.at(1).eta(), 50.0, 0.0, 50.0, 0, m_is_fast_sim);
            } 
            else if ( gen_bjets.size()==3) 
            {
                m_evt.sf_unc_nbtag  = btagEventUncertainty (3, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), gen_bjets.at(1).pt(), gen_bjets.at(1).eta(),
                                                                  gen_bjets.at(2).pt(), gen_bjets.at(2).eta(), 50., 0, m_is_fast_sim);
                m_evt.sf_unc_nbtag3 = btagEventUncertainty3(3, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), gen_bjets.at(1).pt(), gen_bjets.at(1).eta(),
                                                                  gen_bjets.at(2).pt(), gen_bjets.at(2).eta(), 50., 0, m_is_fast_sim);
            }
            else if ( gen_bjets.size()>3)
            {
                m_evt.sf_unc_nbtag  = btagEventUncertainty (4, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), gen_bjets.at(1).pt(), gen_bjets.at(1).eta(),
                                                                  gen_bjets.at(2).pt(), gen_bjets.at(2).eta(), gen_bjets.at(3).pt(), gen_bjets.at(3).eta(), m_is_fast_sim);
                m_evt.sf_unc_nbtag3 = btagEventUncertainty3(4, gen_bjets.at(0).pt(), gen_bjets.at(0).eta(), gen_bjets.at(1).pt(), gen_bjets.at(1).eta(),
                                                                  gen_bjets.at(2).pt(), gen_bjets.at(2).eta(), gen_bjets.at(3).pt(), gen_bjets.at(3).eta(), m_is_fast_sim);
            }
        }

        // only keep 2 jet events
        if (m_evt.njets < 2)
        {
            return 0;
        }

		// jet/bjet info 
		m_evt.vbjets_p4 = samesign::getBtaggedJets(hyp_idx, jet_type, JETS_BTAG_CSVM,     /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, m_jetMetScale); 
		m_evt.vjets_p4  = samesign::getJets(hyp_idx, jet_type,                            /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt2>*/20.0, 1.0, m_jetMetScale); 
        m_evt.vbtags    = samesign::getBtaggedJetFlags(hyp_idx, jet_type, JETS_BTAG_CSVM, /*dR=*/0.4, /*jet_pt>*/40.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt1>*/20.0, 1.0, m_jetMetScale);

        //SetBtagDiscriminator(m_evt.bjets_p4, m_evt.bjets_csv, JETS_BTAG_CSVM);
        //SetBtagDiscriminator(m_evt.vjets_p4, m_evt.bjets_csv, JETS_BTAG_CSVM);

        //m_evt.bjets_dr12 = (m_evt.nbtags>=2) ? rt::DeltaR(m_evt.bjets_p4.at(0), m_evt.bjets_p4.at(1)) : -999999.0;
        //m_evt.jets_dr12  = (m_evt.njets>=2 ) ? rt::DeltaR(m_evt.jets_p4.at(0) , m_evt.jets_p4.at(1) ) : -999999.0;

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

        // get the list of selected jets with lower pT theshold
        //vector<LorentzVector> temp_jets_p4 = tas::pfjets_p4();
        //vector<float>& temp_jets_csv = pfjets_combinedSecondaryVertexBJetTag();
        //vector<LorentzVector> temp_jets_p4  = samesign::getJets(hyp_idx, jet_type, /*dR=*/0.4, /*jet_pt>*/20.0, /*|eta|<*/2.4, /*pt1>*/20.0, /*pt2>*/20.0, 1.0, m_jetMetScale); 
        //vector<float> temp_jets_csv;
        //SetBtagDiscriminator(temp_jets_p4, temp_jets_csv, JETS_BTAG_CSVM);
        
		vector<LorentzVector> temp_jets_p4 = m_evt.vjets_p4;  
        //vector<float> temp_jets_csv        = m_evt.vjets_csv;

        // get the untagged jets
        vector<LorentzVector> temp_jets_nontagged_p4;
        for (size_t i = 0; i != temp_jets_p4.size(); i++)
        {
            //temp_jets_p4.at(i) *= evt_isRealData() ? pfjets_corL1FastL2L3residual().at(i) : pfjets_corL1FastL2L3().at(i);
            if (not m_evt.vbtags.at(i))
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

        // Fill the tree
        m_tree->Fill();

        // printout
        if (m_evt.is_good_lumi)
        {
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

float SSAnalysisLooper::GetFakeRateValue(int lep_id, int lep_idx) const 
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

float SSAnalysisLooper::GetFlipRateValue(int lep_id, int lep_idx) const 
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
