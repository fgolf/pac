#include "at/GenJetInfo.h"
#include "at/YieldType.h"
#include "at/MCBtagCount.h"
#include "mcbtagSFuncert.h"
#include "CMS2.h"

// templated function implementation for JetInfoTree 

template <typename Function>
void JetInfoTree::FillCommon
(
    const at::Sample::value_type sample,
    const bool is_fast_sim,
    const at::JetBaseSelectionArgs& jet_args,
    Function jet_selection
)
{
    using namespace tas;

    // jets 
    njets               = at::NumJets            (jet_args, jet_selection);
    ht                  = at::SumJetPt           (jet_args, jet_selection);
    jets_dr12           = at::JetsDr12           (jet_args, jet_selection);
    vjets_p4            = at::GetJetsP4          (jet_args, jet_selection);
    vjets_mc3p4         = at::GetJetsMC3P4       (jet_args, jet_selection);
    vjets_nearjet_p4    = at::GetJetsNearjetP4   (jet_args, jet_selection);
    vjets_nearjet_dr    = at::GetJetsNearjetDr   (jet_args, jet_selection);
    vjets_disc          = at::GetJetsDisc        (jet_args, jet_selection);
    vjets_btagged       = at::GetJetsBtagged     (jet_args, jet_selection);
    vjets_mcflavor_phys = at::GetJetsMCFlavorPhys(jet_args, jet_selection);
    vjets_mcflavor_algo = at::GetJetsMCFlavorAlgo(jet_args, jet_selection);
    vjets_mc3id         = at::GetJetsMC3Id       (jet_args, jet_selection);
    vjets_momid         = at::GetJetsMomId       (jet_args, jet_selection);

    // b-tagged jets
    nbtags               = at::NumBtaggedJets            (jet_args, jet_selection);
    bjets_dr12           = at::BJetsDr12                 (jet_args, jet_selection);
    vbjets_p4            = at::GetBtaggedJetsP4          (jet_args, jet_selection);
    vbjets_mc3p4         = at::GetBtaggedJetsMC3P4       (jet_args, jet_selection);
    vbjets_nearjet_p4    = at::GetBtaggedJetsNearjetP4   (jet_args, jet_selection);
    vbjets_nearjet_dr    = at::GetBtaggedJetsNearjetDr   (jet_args, jet_selection);
    vbjets_mcflavor_phys = at::GetBtaggedJetsMCFlavorPhys(jet_args, jet_selection);
    vbjets_mcflavor_algo = at::GetBtaggedJetsMCFlavorAlgo(jet_args, jet_selection);
    vbjets_mc3id         = at::GetBtaggedJetsMC3Id       (jet_args, jet_selection);
    vbjets_momid         = at::GetBtaggedJetsMomId       (jet_args, jet_selection);

    if (not evt_isRealData())
    {
        // generator level "jets"
        gen_vjets_p4 = at::GetGenJets(jet_args.min_pt, jet_args.max_eta);
        gen_njets    = gen_vjets_p4.size(); 
        gen_ht       = at::GetGenHT(jet_args.min_pt, jet_args.max_eta); 

        // generator level "b jets"
        gen_vbjets_p4 = at::GetGenBJets(jet_args.min_pt, jet_args.max_eta);
        gen_nbjets    = gen_vbjets_p4.size(); 
    }

    // # btags reweighted
    const unsigned int seed = tas::evt_event();
    nbtags_reweighted         = at::MCBtagCount(jet_args.btag_type, vjets_p4, vjets_btagged, vjets_mcflavor_algo, sample, is_fast_sim, at::YieldType::base, seed);
    nbtags_reweighted_beff_up = at::MCBtagCount(jet_args.btag_type, vjets_p4, vjets_btagged, vjets_mcflavor_algo, sample, is_fast_sim, at::YieldType::up  , seed);
    nbtags_reweighted_beff_dn = at::MCBtagCount(jet_args.btag_type, vjets_p4, vjets_btagged, vjets_mcflavor_algo, sample, is_fast_sim, at::YieldType::down, seed);
}
