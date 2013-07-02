#ifndef REMOVELEPTONSSSID_H
#define REMOVELEPTONSSSID_H

#include "CMS2.h"
#include "ssSelections.h"
#include "rt/RootTools.h"
#include "at/JetInfo.h"
#include "at/ConvertHypIndexToVectors.h"
#include <vector>


struct RemoveLeptonsSSID 
{
    RemoveLeptonsSSID(const int hyp_idx, const float dr = 0.4, const float mu_minpt = 20.0, const float el_minpt = 20.0)
        : m_hyp_idx(hyp_idx)
        , m_dr(dr)
        , m_mu_minpt(mu_minpt)
        , m_el_minpt(el_minpt)
    {}

    bool operator () (const at::JetInfo& jet_info) const
    {
        using namespace tas;
        using namespace at;

        std::vector<int> el_indices;
        std::vector<int> mu_indices;
        at::ConvertHypIndexToVectors(m_hyp_idx, mu_indices, el_indices);

        // selected electrons
        for (size_t i = 0; i != el_indices.size(); i++)
        {
            const LorentzVector& el_p4 = tas::els_p4().at(el_indices.at(i));
            if (rt::DeltaR(jet_info.CorrP4(), el_p4) < m_dr) {return false;}
        }

        // selected muons
        for (size_t i = 0; i != mu_indices.size(); i++)
        {
            const LorentzVector& mu_p4 = tas::mus_p4().at(mu_indices.at(i));
            if (rt::DeltaR(jet_info.CorrP4(), mu_p4) < m_dr) {return false;}
        }

        // other electrons
        for (size_t eidx = 0; eidx < els_p4().size(); eidx++)
        {
            if (els_p4().at(eidx).pt() < m_el_minpt)                 {continue;}
            if (not samesign::isNumeratorLepton(11, eidx))           {continue;}
            if (rt::DeltaR(jet_info.P4(), els_p4().at(eidx)) > m_dr) {continue;}
            return false;
        }

        // other muons
        for (size_t midx = 0; midx < mus_p4().size(); midx++)
        {
            if (mus_p4().at(midx).pt() < m_mu_minpt)                 {continue;}
            if (not samesign::isNumeratorLepton(13, midx))           {continue;}
            if (rt::DeltaR(jet_info.P4(), mus_p4().at(midx)) > m_dr) {continue;}
            return false;
        }

        // if here, then its selected
        return true;
    }

    // members
    int m_hyp_idx;
    float m_dr;
    float m_mu_minpt;
    float m_el_minpt;
};


#endif // REMOVELEPTONSSID_H
