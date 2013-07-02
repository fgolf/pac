#include "rt/MiscTools.h"
#include "boost/bind.hpp"

// implementation of templated functions

namespace at
{

// ----------------------------------------------------------------------------- //
// JetInfo non-member function templates
// ----------------------------------------------------------------------------- //

    // get the nearest jet p4 to the given p4 
    template <typename Function>
    JetInfo NearestJet(const LorentzVector& p4, const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_args);   
        jet_infos = rt::filter_container(jet_infos, jet_selection);
        if (jet_infos.empty())
        {
            // return bogus jet info is no match
            return JetInfo();
        }

        // sort by DeltR(p4, jet_info.CorrP4())
        std::sort(jet_infos.begin(), jet_infos.end(), SortByDeltaRToCorrP4(p4));

        // if the first jet_info is the same p4, then return the next one
        if (JetCorrespondsToP4(jet_infos.front(), p4))
        {
            if (jet_infos.size() < 2)
            {
                // return bogus jet info is no match
                return JetInfo();
            }
            else
            {
                return jet_infos.at(1);
            }
        }

        // if we're here, then the 1st element is the nearest jet
        return jet_infos.front();
    }

    // get the nearest btagged jet p4 to the given p4 
    template <typename Function>
    JetInfo NearestBtaggedJet(const LorentzVector& p4, const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        return NearestJet(p4, jet_args, boost::bind<bool>(jet_selection, _1) && boost::bind(IsBtagged, _1));
    }

    // get the nearest non-btagged jet p4 to the given p4 
    template <typename Function>
    JetInfo NearestNonBtaggedJet(const LorentzVector& p4, const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        return NearestJet(p4, jet_args, boost::bind<bool>(jet_selection, _1) && not boost::bind(IsBtagged, _1));
    }

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

    // get the sum pt of the jets
    template <typename Function>
    float SumJetPt(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_args);   
        jet_infos = rt::filter_container(jet_infos, jet_selection);

        float result = 0.0;
        for (size_t i = 0; i != jet_infos.size(); i++) {result += jet_infos.at(i).CorrPt();}
        return result;
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
        return GetJetsMC3P4(jet_args, boost::bind<bool>(jet_selection, _1) && boost::bind(IsBtagged, _1));
    }

    // get the nearest non-tagged jet p4
    template <typename Function>
    std::vector<LorentzVector> GetJetsNearjetP4(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_args);   
        jet_infos = rt::filter_container(jet_infos, jet_selection);

        std::vector<LorentzVector> results;
        for (size_t i = 0; i != jet_infos.size(); i++)
        {
            JetInfo nearest_jet = NearestNonBtaggedJet(jet_infos.at(i).CorrP4(), jet_args, jet_selection);
            results.push_back(nearest_jet.CorrP4());
        }
        return results;
    }

    template <typename Function>
    std::vector<LorentzVector> GetBtaggedJetsNearjetP4(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_args);   
        jet_infos = rt::filter_container(jet_infos, boost::bind<bool>(jet_selection, _1) && boost::bind(IsBtagged, _1));

        std::vector<LorentzVector> results;
        for (size_t i = 0; i != jet_infos.size(); i++)
        {
            JetInfo nearest_jet = NearestNonBtaggedJet(jet_infos.at(i).CorrP4(), jet_args, jet_selection);
            results.push_back(nearest_jet.CorrP4());
        }
        return results;
    }

    // get the nearest non-tagged jet DeltaR 
    template <typename Function>
    std::vector<float> GetJetsNearjetDr(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_args);   
        jet_infos = rt::filter_container(jet_infos, jet_selection);

        std::vector<float> results;
        for (size_t i = 0; i != jet_infos.size(); i++)
        {
            JetInfo nearest_jet = NearestBtaggedJet(jet_infos.at(i).CorrP4(), jet_args, jet_selection);
            const float dr = ROOT::Math::VectorUtil::DeltaR(nearest_jet, jet_infos.at(i).CorrP4());
            results.push_back(dr);
        }
        return results;
    }

    template <typename Function>
    std::vector<float> GetBtaggedJetsNearjetDr(const JetBaseSelectionArgs& jet_args, Function jet_selection)
    {
        return GetJetsNearjetDr(jet_args, boost::bind<bool>(jet_selection, _1) && boost::bind(IsBtagged, _1));
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
