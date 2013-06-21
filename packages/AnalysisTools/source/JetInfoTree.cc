#include "JetInfoTree.h"

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
