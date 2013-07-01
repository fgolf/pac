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
    njets  = -99999;
    jets_dr12 = -999999.0;
    vjets_p4.clear();
    vjets_mc3p4.clear();
    vjets_nearjet_p4.clear();
    vjets_nearjet_dr.clear();
    vjets_disc.clear();
    vjets_btagged.clear();
    vjets_mcflavor_phys.clear();
    vjets_mcflavor_algo.clear();
    vjets_momid.clear();
    vjets_mc3id.clear();

    nbtags = -99999;
    bjets_dr12 = -999999.0;
    vbjets_p4.clear();
    vbjets_mc3p4.clear();
    vbjets_nearjet_p4.clear();
    vbjets_nearjet_dr.clear();
    vbjets_mcflavor_phys.clear();
    vbjets_mcflavor_algo.clear();
    vbjets_disc.clear();
    vbjets_momid.clear();
    vbjets_mc3id.clear();
}

void JetInfoTree::SetBranches(TTree& tree)
{
    tree.Branch(Form("%snjets%s"      , m_prefix.c_str() , m_postfix.c_str()) , &njets      ); 
    tree.Branch(Form("%sjets_dr12%s"  , m_prefix.c_str() , m_postfix.c_str()) , &jets_dr12  ); 
    tree.Branch(Form("%snbtags%s"     , m_prefix.c_str() , m_postfix.c_str()) , &nbtags     ); 
    tree.Branch(Form("%sbjets_dr12%s" , m_prefix.c_str() , m_postfix.c_str()) , &bjets_dr12 ); 

    tree.Branch(Form("%svjets_p4%s"            , m_prefix.c_str() , m_postfix.c_str()) , "vecLorentzVector" , &vjets_p4            ); 
    tree.Branch(Form("%svjets_mc3p4%s"         , m_prefix.c_str() , m_postfix.c_str()) , "vecLorentzVector" , &vjets_mc3p4         ); 
    tree.Branch(Form("%svjets_nearjet_p4%s"    , m_prefix.c_str() , m_postfix.c_str()) , "vecLorentzVector" , &vjets_nearjet_p4    ); 
    tree.Branch(Form("%svjets_nearjet_dr%s"    , m_prefix.c_str() , m_postfix.c_str()) , "vecd"             , &vjets_nearjet_dr    ); 
    tree.Branch(Form("%svjets_disc%s"          , m_prefix.c_str() , m_postfix.c_str()) , "vecd"             , &vjets_disc          ); 
    tree.Branch(Form("%svjets_btagged%s"       , m_prefix.c_str() , m_postfix.c_str()) , "vecb"             , &vjets_btagged       ); 
    tree.Branch(Form("%svjets_mcflavor_phys%s" , m_prefix.c_str() , m_postfix.c_str()) , "veci"             , &vjets_mcflavor_phys ); 
    tree.Branch(Form("%svjets_mcflavor_algo%s" , m_prefix.c_str() , m_postfix.c_str()) , "veci"             , &vjets_mcflavor_algo ); 
    tree.Branch(Form("%svjets_momid%s"         , m_prefix.c_str() , m_postfix.c_str()) , "veci"             , &vjets_momid         ); 
    tree.Branch(Form("%svjets_mc3id%s"         , m_prefix.c_str() , m_postfix.c_str()) , "veci"             , &vjets_mc3id         ); 

    tree.Branch(Form("%svbjets_p4%s"            , m_prefix.c_str() , m_postfix.c_str()) , "vecLorentzVector" , &vbjets_p4            ); 
    tree.Branch(Form("%svbjets_mc3p4%s"         , m_prefix.c_str() , m_postfix.c_str()) , "vecLorentzVector" , &vbjets_mc3p4         ); 
    tree.Branch(Form("%svbjets_nearjet_p4%s"    , m_prefix.c_str() , m_postfix.c_str()) , "vecLorentzVector" , &vbjets_nearjet_p4    ); 
    tree.Branch(Form("%svbjets_nearjet_dr%s"    , m_prefix.c_str() , m_postfix.c_str()) , "vecd"             , &vbjets_nearjet_dr    ); 
    tree.Branch(Form("%svbjets_mcflavor_phys%s" , m_prefix.c_str() , m_postfix.c_str()) , "veci"             , &vbjets_mcflavor_phys ); 
    tree.Branch(Form("%svbjets_mcflavor_algo%s" , m_prefix.c_str() , m_postfix.c_str()) , "veci"             , &vbjets_mcflavor_algo ); 
    tree.Branch(Form("%svbjets_momid%s"         , m_prefix.c_str() , m_postfix.c_str()) , "veci"             , &vbjets_momid         ); 
    tree.Branch(Form("%svbjets_mc3id%s"         , m_prefix.c_str() , m_postfix.c_str()) , "veci"             , &vbjets_mc3id         ); 
}
