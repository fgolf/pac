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
    std::vector<LorentzVector> GetJets(const JetBaseSelectionArgs& jet_fun_args, Function selection)
    {
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_fun_args);   
        jet_infos = rt::filter_container(jet_infos, selection);

        std::vector<LorentzVector> results;
        for (size_t i = 0; i != jet_infos.size(); i++)
        {
            results.push_back(jet_infos.at(i).CorrP4());
        }
        return results;
    }

    // get the number of jets 
    template <typename Function>
    unsigned int NumJets(const JetBaseSelectionArgs& jet_fun_args, Function selection)
    {
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_fun_args);   
        jet_infos = rt::filter_container(jet_infos, selection);
        return jet_infos.size();
    }

    // get the btagged jet corrected p4
    template <typename Function>
    std::vector<LorentzVector> GetBtaggedJets(const JetBaseSelectionArgs& jet_fun_args, Function selection)
    {
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_fun_args);   
        jet_infos = rt::filter_container(jet_infos, boost::bind<bool>(selection, _1) && boost::bind(IsBtagged, _1));

        std::vector<LorentzVector> results;
        for (size_t i = 0; i != jet_infos.size(); i++)
        {
            results.push_back(jet_infos.at(i).CorrP4());
        }
        return results;
    }

    // get the number of btagged jets 
    template <typename Function>
    unsigned int NumBtaggedJets(const JetBaseSelectionArgs& jet_fun_args, Function selection)
    {
        std::vector<JetInfo> jet_infos = GetJetInfos(jet_fun_args);   
        jet_infos = rt::filter_container(jet_infos, boost::bind<bool>(selection, _1) && boost::bind(IsBtagged, _1));
        return jet_infos.size();
    }

} // namespace at
