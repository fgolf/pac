#ifndef SIGNALREGIONS_H
#define SIGNALREGIONS_H

#include <string>
#include "at/Sample.h"
#include "at/YieldType.h"
#include "AnalysisType.h"
#include "SystematicType.h"
#include "TTree.h"
#include "EWKINO2012_SS.h"

namespace ewkino
{
    struct SignalRegion
    {
        enum value_type
        {
            // inclusive
            sr0  = 0,  // baseline: pt > 20/20, njets_matched = 2,3 and MET > 30 GeV
            sr1  = 1,  // sr0 + pt>30/20 + MET > 80 + HT < 200 + min MT > 80 + 0 CSVM + <2 CSVL + 3rd lepton veto + iso track veto + tau veto + dijet pt < 160 + dR(jet1,jet2) < 3 + dEta(lep1,lep2) < 2. + dR(ll,jj) < 3.2
            sr2  = 2,  // sr1 + <= 1 CVSL b-tagged jets
            sr3  = 3,  // sr2 + max[ M(11,31), M(21,3l) ] < 10 GeV
            sr4  = 4,  // sr3 + jets from off-shell W 
            sr5  = 5,  // sr3 + jets from on-shell W
            sr6  = 6,  // sr5 + MET > 90 GeV
            sr7  = 7,  // sr6 + no third muon w/ pt > 5 + no third electron w/ pt > 10
            sr8  = 8,  // sr7 + |deta(lep1,lep2)| < 2.0
            sr9  = 9,  // sr8 + max(pt1,pt2) > 30
            sr10 = 10, // sr9 + ht < 160
            sr11 = 11, // sr10 + pfmet > 90
            sr12 = 12, // sr8 + max(lep1_mt,lep2_mt) > 70.
            sr13 = 13, // sr12 + 0.4 < min(jet1_pt,jet2_pt)/pt_jj < 1.1
            sr14 = 14, // sr0 + dR(j,j) < 3. && pt(jj) < 160 && ht < 200 && dR(ll) < 2.4 && met > 20
            sr15 = 15, // pt > 20/20, njets_matched = 2,3 and MET > 30 GeV
            sr16 = 16, // pt > 20/20, njets_matched = 2,3 and MET > 30 GeV
            // keep track of the size
            static_size
        };
    };

    // Signal Region Infomation
    struct SignalRegionInfo
    {
        std::string name;
        std::string title;
        std::string latex;
    };

    // Signal Region type (exclusive vs inclusive)
    struct SignalRegionType
    {
        enum value_type
        {
            inclusive, // inclusive signal region type
            exclusive, // exclusive signal region type
            static_size
        };
    };

    // Get the SignalRegion from a string
    SignalRegion::value_type GetSignalRegionFromName
    (
        const std::string& signal_region_name,
        const std::string& analysis_type_name,
        const std::string& signal_region_type_name = "inclusive"
    );

    // Get the info for the Signal region
    SignalRegionInfo GetSignalRegionInfo
    (
        const SignalRegion::value_type& signal_region,
        const AnalysisType::value_type anal_type,
        const SignalRegionType::value_type& signal_region_type = SignalRegionType::inclusive 
    );

    SignalRegionInfo GetSignalRegionInfo
    (
        const std::string& signal_region_name,
        const std::string& analysis_type_name,
        const std::string& signal_region_type_name = "inclusive" 
    );

    // Get the name of the SignalRegionType
    std::string GetSignalRegionTypeName(const SignalRegionType::value_type& signal_region_type);

    // Get the SignalRegionType from a string
    SignalRegionType::value_type GetSignalRegionTypeFromName(const std::string& signal_region_type_name);

    // passes signal region
    // automatically determine which met/ht/njets/nbtags to use
    bool PassesSignalRegion
    (
        const SignalRegion::value_type& signal_region,
        const AnalysisType::value_type& anal_type,
        const SignalRegionType::value_type& signal_region_type = SignalRegionType::inclusive,
        const bool do_beff_sf = true, // applied for MC only
        const SystematicType::value_type& syst_type = SystematicType::None,
        const at::Sample::value_type sample = at::Sample::data,
        const bool is_fast_sim = false
    );

    // passes signal region
    bool PassesSignalRegion
    (
        const float met,
        const float ht,
        const int njets,
        const int nbtags,
        const float l1_pt,
        const float l2_pt,
        const int l1_id,
        const int l2_id,
        const SignalRegion::value_type& signal_region,
        const AnalysisType::value_type& anal_type,
        const SignalRegionType::value_type& signal_region_type = SignalRegionType::inclusive
    );

    // set aliases for TTree
    void SetSignalRegionAliases(TTree& tree, const AnalysisType::value_type& anal_type, const bool do_btag_sf = true);
    void SetSignalRegionAliases(TTree* tree, const AnalysisType::value_type& anal_type, const bool do_btag_sf = true);

    // get matched jets
    bool passesMVAJetId(LorentzVector p4, float mva_value, int tightness);    
    std::vector<LorentzVector> getMatchedJets(int tightness);
    int nMatchedBtags(int mva_tightness, int btag_tightness);

} // namespace ss

#endif // SIGNALREGIONS_H
