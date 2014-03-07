#include "DrellYanTree.h"

DrellYanTree::DrellYanTree()
    : DileptonTree()
{
}

void DrellYanTree::Reset()
{
    event_info.Reset();
    DileptonTree::Reset();
    charge_type  = -999999;
    vtxw         = -999999.0;
    rho          = -999999.0;
    rho_iso      = -999999.0;
    is_mm        = false;
    is_ee        = false;
    trig_mm      = false;
    trig_ee      = false;
    is_gen_z     = false;;
    gen_z_p4     = LorentzVector(0, 0, 0, 0);
    gen_d1_p4    = LorentzVector(0, 0, 0, 0);
    gen_d2_p4    = LorentzVector(0, 0, 0, 0);
    gen_z_type   = at::DileptonHypType::static_size;
    gen_d1_pdgid = -999999;;
    gen_d1_pdgid = -999999;;
    is_z_ee      = false;
    is_z_mm      = false;
    is_z_tt      = false;
    is_acc       = false;
    is_acc_ee    = false;
    is_acc_mm    = false;
}

void DrellYanTree::SetBranches(TTree &tree)
{
    event_info.SetBranches(tree);
    DileptonTree::SetBranches(tree);
    tree.Branch("charge_type"  , &charge_type    , "charge_type/I"  ); 
    tree.Branch("vtxw"         , &vtxw           , "vtxw/F"         ); 
    tree.Branch("rho"          , &rho            , "rho/F"          ); 
    tree.Branch("rho_iso"      , &rho_iso        , "rho_iso/F"      ); 
    tree.Branch("is_mm"        , &is_mm          , "is_mm/O"        ); 
    tree.Branch("is_em"        , &is_ee          , "is_ee/O"        ); 
    tree.Branch("trig_mm"      , &trig_mm        , "trig_mm/O"      ); 
    tree.Branch("trig_ee"      , &trig_ee        , "trig_ee/O"      ); 
    tree.Branch("is_gen_z"     , &is_gen_z       , "is_gen_z/O"     ); 
    tree.Branch("gen_z_p4"     , "LorentzVector" , &gen_z_p4        ); 
    tree.Branch("gen_d1_p4"    , "LorentzVector" , &gen_d1_p4       ); 
    tree.Branch("gen_d2_p4"    , "LorentzVector" , &gen_d2_p4       ); 
    tree.Branch("gen_z_type"   , &gen_z_type     , "gen_z_type/I"   ); 
    tree.Branch("gen_d1_pdgid" , &gen_d1_pdgid   , "gen_d1_pdgid/I" ); 
    tree.Branch("gen_d2_pdgid" , &gen_d2_pdgid   , "gen_d2_pdgid/I" ); 
    tree.Branch("is_z_ee"      , &is_z_ee        , "is_z_ee/O"      ); 
    tree.Branch("is_z_mm"      , &is_z_mm        , "is_z_mm/O"      ); 
    tree.Branch("is_z_tt"      , &is_z_tt        , "is_z_tt/O"      ); 
    tree.Branch("is_acc"       , &is_acc         , "is_acc/O"       ); 
    tree.Branch("is_acc_ee"    , &is_acc_ee      , "is_acc_ee/O"    ); 
    tree.Branch("is_acc_mm"    , &is_acc_mm      , "is_acc_mm/O"    ); 
}
