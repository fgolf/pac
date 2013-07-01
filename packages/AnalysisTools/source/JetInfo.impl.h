#include "rt/MiscTools.h"
#include "boost/bind.hpp"

// implementation of templated functions

namespace at
{

// ----------------------------------------------------------------------------- //
// functions to return the indivdual components in the form of a std::vector 
// ----------------------------------------------------------------------------- //

    // get the jet corrected p4
    template <typename Function>
    std::vector<LorentzVector> GetJetsP4(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_args);   
        jet_infos = rt::filter_container(jet_infos, jet_selection);

        std::vector<LorentzVector> results;
        for (size_t i = 0; i != jet_infos.size(); i++) {results.push_back(jet_infos.at(i).CorrP4());}
        return results;
    }

    template <typename Function>
    std::vector<LorentzVector> GetBtaggedJetsP4(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        return GetJetsP4(jet_args, boost::bind<bool>(jet_selection, _1) && boost::bind(IsBtagged, _1));
    }

    // get the number of jets 
    template <typename Function>
    unsigned int NumJets(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_args);   
        jet_infos = rt::filter_container(jet_infos, jet_selection);
        return jet_infos.size();
    }

    template <typename Function>
    unsigned int NumBtaggedJets(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        return NumJets(jet_args, boost::bind<bool>(jet_selection, _1) && boost::bind(IsBtagged, _1));
    }

     // get the DR between  
     template <typename Function>
     float JetsDr12(const JetBaseSelectionArgs& jet_args, Function jet_selection)
     {
         std::vector<JetInfo> jet_infos = GetJetInfos(jet_args);   
         jet_infos = rt::filter_container(jet_infos, jet_selection);
         return ((jet_infos.size() >= 2) ? rt::DeltaR(jet_infos.at(0).CorrP4(), jet_infos.at(1).CorrP4()) : -999999.0);
     }

     template <typename Function>
     float BJetsDr12(const JetBaseSelectionArgs& jet_args, Function jet_selection)
     {
        return JetsDr12(jet_args, boost::bind<bool>(jet_selection, _1) && boost::bind(IsBtagged, _1));
     }

    // get the jet mc3 p4
    template <typename Function>
    std::vector<LorentzVector> GetJetsMC3P4(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_args);   
        jet_infos = rt::filter_container(jet_infos, jet_selection);

        std::vector<LorentzVector> results;
        for (size_t i = 0; i != jet_infos.size(); i++) {results.push_back(jet_infos.at(i).MC3P4());}
        return results;
    }

    template <typename Function>
    std::vector<LorentzVector> GetBtaggedJetsMC3P4(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        return GetJetsP4(jet_args, boost::bind<bool>(jet_selection, _1) && boost::bind(IsBtagged, _1));
    }

    // get the nearest jet p4
    template <typename Function>
    std::vector<LorentzVector> GetJetsNearjetP4(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_args);   
        jet_infos = rt::filter_container(jet_infos, jet_selection);

        std::vector<LorentzVector> results;
        for (size_t i = 0; i != jet_infos.size(); i++) {results.push_back(jet_infos.at(i).NearjetP4());}
        return results;
    }

    template <typename Function>
    std::vector<LorentzVector> GetBtaggedJetsNearjetP4(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        return GetJetsNearjetP4(jet_args, boost::bind<bool>(jet_selection, _1) && boost::bind(IsBtagged, _1));
    }

    // get the nearest jet DeltaR 
    template <typename Function>
    std::vector<float> GetJetsNearjetDr(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_args);   
        jet_infos = rt::filter_container(jet_infos, jet_selection);

        std::vector<float> results;
        for (size_t i = 0; i != jet_infos.size(); i++) {results.push_back(jet_infos.at(i).NearjetDr());}
        return results;
    }

    template <typename Function>
    std::vector<float> GetBtaggedJetsNearjetDr(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        return GetJetsNearjetDr(jet_args, boost::bind<bool>(jet_selection, _1) && boost::bind(IsBtagged, _1));
    }

    // get the nearest lepton p4
    template <typename Function>
    std::vector<LorentzVector> GetJetsNearlepP4(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_args);   
        jet_infos = rt::filter_container(jet_infos, jet_selection);

        std::vector<LorentzVector> results;
        for (size_t i = 0; i != jet_infos.size(); i++) {results.push_back(jet_infos.at(i).NearlepP4());}
        return results;
    }

    template <typename Function>
    std::vector<LorentzVector> GetBtaggedJetsNearlepP4(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        return GetJetsNearlepP4(jet_args, boost::bind<bool>(jet_selection, _1) && boost::bind(IsBtagged, _1));
    }

    // get the nearest lepton DeltaR 
    template <typename Function>
    std::vector<float> GetJetsNearlepDr(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_args);   
        jet_infos = rt::filter_container(jet_infos, jet_selection);

        std::vector<float> results;
        for (size_t i = 0; i != jet_infos.size(); i++) {results.push_back(jet_infos.at(i).NearlepDr());}
        return results;
    }

    template <typename Function>
    std::vector<float> GetBtaggedJetsNearlepDr(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        return GetJetsNearlepDr(jet_args, boost::bind<bool>(jet_selection, _1) && boost::bind(IsBtagged, _1));
    }

    // get the b-tag discriminator value
    template <typename Function>
    std::vector<float> GetJetsDisc(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_args);   
        jet_infos = rt::filter_container(jet_infos, jet_selection);

        std::vector<float> results;
        for (size_t i = 0; i != jet_infos.size(); i++) {results.push_back(jet_infos.at(i).BtagDisc());}
        return results;
    }

    template <typename Function>
    std::vector<float> GetBtaggedJetsDisc(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        return GetJetsDisc(jet_args, boost::bind<bool>(jet_selection, _1) && boost::bind(IsBtagged, _1));
    }

    // get the bools for whether the jet is b-tagged
    template <typename Function>
    std::vector<bool> GetJetsBtagged(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_args);   
        jet_infos = rt::filter_container(jet_infos, jet_selection);

        std::vector<bool> results;
        for (size_t i = 0; i != jet_infos.size(); i++) {results.push_back(jet_infos.at(i).IsBtagged());}
        return results;
    }

    // get the MC flavor physics
    template <typename Function>
    std::vector<int> GetJetsMCFlavorPhys(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_args);   
        jet_infos = rt::filter_container(jet_infos, jet_selection);

        std::vector<int> results;
        for (size_t i = 0; i != jet_infos.size(); i++) {results.push_back(jet_infos.at(i).MCFlavorPhys());}
        return results;
    }

    template <typename Function>
    std::vector<int> GetBtaggedJetsMCFlavorPhys(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        return GetJetsMCFlavorPhys(jet_args, boost::bind<bool>(jet_selection, _1) && boost::bind(IsBtagged, _1));
    }

    // get the MC flavor algorithm
    template <typename Function>
    std::vector<int> GetJetsMCFlavorAlgo(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_args);   
        jet_infos = rt::filter_container(jet_infos, jet_selection);

        std::vector<int> results;
        for (size_t i = 0; i != jet_infos.size(); i++) {results.push_back(jet_infos.at(i).MCFlavorAlgo());}
        return results;
    }

    template <typename Function>
    std::vector<int> GetBtaggedJetsMCFlavorAlgo(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        return GetJetsMCFlavorAlgo(jet_args, boost::bind<bool>(jet_selection, _1) && boost::bind(IsBtagged, _1));
    }

    // get the MC matched ID 
    template <typename Function>
    std::vector<int> GetJetsMC3Id(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_args);   
        jet_infos = rt::filter_container(jet_infos, jet_selection);

        std::vector<int> results;
        for (size_t i = 0; i != jet_infos.size(); i++) {results.push_back(jet_infos.at(i).MC3Id());}
        return results;
    }

    template <typename Function>
    std::vector<int> GetBtaggedJetsMC3Id(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        return GetJetsMC3Id(jet_args, boost::bind<bool>(jet_selection, _1) && boost::bind(IsBtagged, _1));
    }

    // get the MC matched mother ID
    template <typename Function>
    std::vector<int> GetJetsMomId(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_args);   
        jet_infos = rt::filter_container(jet_infos, jet_selection);

        std::vector<int> results;
        for (size_t i = 0; i != jet_infos.size(); i++) {results.push_back(jet_infos.at(i).MomId());}
        return results;
    }

    template <typename Function>
    std::vector<int> GetBtaggedJetsMomId(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        return GetJetsMomId(jet_args, boost::bind<bool>(jet_selection, _1) && boost::bind(IsBtagged, _1));
    }

} // namespace at
