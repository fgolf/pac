#include "JetInfoTree.h"
#include "CORE/eventSelections.h"
#include "CORE/mcSelections.h"
#include "CORE/ssSelections.h"
#include "CMS2.h"
#include "at/CMS2Tag.h"
#include "at/JetInfo.h"

using namespace at;

// construct:
JetInfoTree::JetInfoTree()
{
}

JetInfoTree::JetInfoTree(const std::string& prefix, const std::string& postfix)
    : m_prefix(prefix)
    , m_postfix(postfix)
{
    Reset();
}

struct RemoveLeptonsSSID 
{
    RemoveLeptonsSSID(const float dr = 0.4, const float el_minpt = 20.0, const float mu_minpt = 20.0)
        : m_dr(dr)
        , m_el_minpt(el_minpt)
        , m_mu_minpt(mu_minpt)
    {}

    bool operator () (const JetInfo& jet_info)
    {
        using namespace tas;

        for (size_t eidx = 0; eidx < els_p4().size(); eidx++)
        {
            if (els_p4().at(eidx).pt() < m_el_minpt)                 {continue;}
            if (not samesign::isNumeratorLepton(11, eidx))           {continue;}
            if (rt::DeltaR(jet_info.P4(), els_p4().at(eidx)) > m_dr) {continue;}
            return false;
        }

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
    float m_dr;
    float m_el_minpt;
    float m_mu_minpt;
};

// methods:
void JetInfoTree::FillCommon(const std::vector<int>& mu_indices, const std::vector<int>& el_indices)
{
//     using namespace at;
    using namespace tas;

    at::JetType::value_type jet_type = (evt_isRealData() ? at::JetType::PF_FAST_CORR_RESIDUAL : at::JetType::PF_FAST_CORR);
    at::JetBaseSelectionArgs jet_args(jet_type, at::JetBtagType::CSVM, at::JetScaleType::NONE, mu_indices, el_indices, /*dr=*/0.4, /*min_pt=*/40.0, /*max_eta=*/2.4);
    RemoveLeptonsSSID selection(/*dr=*/0.4, /*el_pt>*/20.0, /*mu_pt>*/20.0);

    vjets_p4  = at::GetJets       (jet_args, selection);
    njets     = at::NumJets       (jet_args, selection);
    vbjets_p4 = at::GetBtaggedJets(jet_args, selection);
    nbtags    = at::NumBtaggedJets(jet_args, selection);
}

void JetInfoTree::FillCommon(int hyp_index)
{
    std::vector<int> el_indices;
    std::vector<int> mu_indices;

    // ll
    if (abs(tas::hyp_ll_id().at(hyp_index))==11)
    {
        el_indices.push_back(tas::hyp_ll_index().at(hyp_index));
    }
    else
    {
        mu_indices.push_back(tas::hyp_ll_index().at(hyp_index));
    }

    // lt
    if (abs(tas::hyp_lt_id().at(hyp_index))==11)
    {
        el_indices.push_back(tas::hyp_lt_index().at(hyp_index));
    }
    else
    {
        mu_indices.push_back(tas::hyp_lt_index().at(hyp_index));
    }

    FillCommon(mu_indices, el_indices);
}

void JetInfoTree::Reset()
{
    njets  = -99999.0;
    nbtags = -99999.0;

    vjets_p4.clear();
    vbjets_p4.clear();
}

void JetInfoTree::SetBranches(TTree& tree)
{
    tree.Branch(Form("%snjets%s" , m_prefix.c_str(), m_postfix.c_str()), &njets);
    tree.Branch(Form("%snbtags%s", m_prefix.c_str(), m_postfix.c_str()), &nbtags);

    tree.Branch(Form("%svjets_p4%s" , m_prefix.c_str(), m_postfix.c_str()), "vecLorentzVector", &vjets_p4 );
    tree.Branch(Form("%svbjets_p4%s", m_prefix.c_str(), m_postfix.c_str()), "vecLorentzVector", &vbjets_p4);
}

