#include "OSTree.h"

OSTree::OSTree ()
{
    lep3 = SingleLeptonTree("lep3_");
}

OSTree::OSTree (const std::string &prefix)
    : DileptonTree(prefix)
{
    lep3 = SingleLeptonTree("lep3_");
}

void OSTree::Reset()
{
    event_info.Reset();
    DileptonTree::Reset();
    lep3.Reset();

    selection                                = 0;
    is_good_lumi                             = true;
    njets                                    = -999999;
    nbtags_loose                             = -999999;
    nbtags_medium                            = -999999;
    nbtags_tight                             = -999999;
    ttbar_bkdn                               = -999999;
    vtxw                                     = -999999.0;
    mt2                                      = -999999.0;
    ht                                       = -999999.0;
    rho                                      = -999999.0;
    rho_iso                                  = -999999.0;
    sf_dileptrig                             = 1.0;
    sf_lepeff                                = 1.0;
    trig_mm                                  = false;
    trig_em                                  = false;
    trig_ee                                  = false;
    trig_mm_mu17_mu8                         = false;
    trig_ee_el17_el8_id_iso                  = false;
    trig_em_mu17_el8_id_iso                  = false;
    trig_em_mu8_el17_id_iso                  = false;
    njets_dn                                 = -999999;
    njets_up                                 = -999999;
    njets_jer                                = -999999;
    nbtags_dn                                = -999999;
    nbtags_up                                = -999999;
    nbtags_jer                               = -999999;
    nbtags_reweighted                        = -999999;
    nbtags_reweighted_dn                     = -999999;
    nbtags_reweighted_up                     = -999999;
    nbtags_reweighted_jer                    = -999999;
    nbtags_reweighted_jec_dn                 = -999999;
    nbtags_reweighted_jec_up                 = -999999;
    ht_dn                                    = -999999.;
    ht_up                                    = -999999.;
    ht_jer                                   = -999999.;
    pfmet_dn                                 = -999999.;
    pfmet_up                                 = -999999.;
    pfmet_phi_dn                             = -999999.;
    pfmet_phi_up                             = -999999.;
    pfmet_jer                                = -999999.;
    pfmet_jer_phi                            = -999999.;
    pfmet_uncl_dn                            = -999999.;
    pfmet_uncl_up                            = -999999.;
    clean                                    = false;
    hyp_good_vtx                             = false;
    presel                                   = false;
    gen_nbtags                               = -999999;
    gen_njets                                = -999999;
    gen_ht                                   = -999999.0;
    lep1_nearb_p4                            = LorentzVector(0, 0, 0, 0);
    lep1_nearlep_p4                          = LorentzVector(0, 0, 0, 0);
    lep1_nearb_dr                            = -999999.0;
    lep1_nearlep_dr                          = -999999.0;
    lep1_nearlep_id                          = -999999;
    lep2_nearb_p4                            = LorentzVector(0, 0, 0, 0);
    lep2_nearlep_p4                          = LorentzVector(0, 0, 0, 0);
    lep2_nearb_dr                            = -999999.0;
    lep2_nearlep_dr                          = -999999.0;
    lep2_nearlep_id                          = -999999;
    gen_lep1_p4                              = LorentzVector(0, 0, 0, 0);
    gen_lep1_pdgid                           = -999999;
    gen_lep2_p4                              = LorentzVector(0, 0, 0, 0);
    gen_lep2_pdgid                           = -999999;
    gen_lep3_p4                              = LorentzVector(0, 0, 0, 0);
    gen_lep3_pdgid                           = -999999;
    gen_dilep_p4                             = LorentzVector(0, 0, 0, 0);
    gen_dilep_type                           = at::DileptonHypType::static_size;
    gen_dilep_mass                           = -999999.0;
    gen_dilep_dphi                           = -999999.0;
    gen_dilep_deta                           = -999999.0;
    gen_dilep_dr                             = -999999.0;
    njets_pv_tight0                          = 0;
    njets_pv_tight1                          = 0;
    njets_pv_tight2                          = 0;

    vjets_p4.clear();
    vjets_p4_up.clear();
    vjets_p4_dn.clear();
    vjets_btagged_loose.clear();
    vjets_btagged_loose_up.clear();
    vjets_btagged_loose_dn.clear();
    vjets_btagged_medium.clear();
    vjets_btagged_medium_up.clear();
    vjets_btagged_medium_dn.clear();
    vjets_btagged_tight.clear();
    vjets_btagged_tight_up.clear();
    vjets_btagged_tight_dn.clear();
    vjets_mcflavor_phys.clear();
    vjets_mcflavor_algo.clear();
    vjets_mcflavor_phys_up.clear();
    vjets_mcflavor_algo_up.clear();
    vjets_mcflavor_phys_dn.clear();
    vjets_mcflavor_algo_dn.clear();
    vgenjets_p4.clear();
    vgenbs_p4.clear();
    vjets_mc3id.clear();
    vjets_momid.clear();
    vjets_mc3p4.clear();
    vjets_bdisc.clear();
    vjets_bdisc_up.clear();
    vjets_bdisc_dn.clear();

    pfjets_beta.clear();
    pfjets_beta2.clear();
    pfjets_beta_0p1.clear();
    pfjets_beta_0p2.clear();
    pfjets_beta2_0p1.clear();
    pfjets_beta2_0p5.clear();
    pfjets_mvaPUid.clear();
    pfjets_mva5xPUid.clear();
    pfjets_mvaBeta.clear();
}

void OSTree::SetBranches(TTree &tree)
{
    event_info.SetBranches(tree);
    DileptonTree::SetBranches(tree);
    lep3.SetBranches(tree);

    tree.Branch("selection"                , &selection                , "selection/i"                ); 
    tree.Branch("is_good_lumi"             , &is_good_lumi             , "is_good_lumi/O"             ); 
    tree.Branch("njets"                    , &njets                    , "njets/I"                    ); 
    tree.Branch("nbtags_loose"             , &nbtags_loose             , "nbtags_loose/I"             ); 
    tree.Branch("nbtags_medium"            , &nbtags_medium            , "nbtags_medium/I"            ); 
    tree.Branch("nbtags_tight"             , &nbtags_tight             , "nbtags_tight/I"             ); 
    tree.Branch("ttbar_bkdn"               , &ttbar_bkdn               , "ttbar_bkdn/I"               ); 
    tree.Branch("vtxw"                     , &vtxw                     , "vtxw/F"                     ); 
    tree.Branch("mt2"                      , &mt2                      , "mt2/F"                      ); 
    tree.Branch("ht"                       , &ht                       , "ht/F"                       ); 
    tree.Branch("rho"                      , &rho                      , "rho/F"                      ); 
    tree.Branch("rho_iso"                  , &rho_iso                  , "rho_iso/F"                  ); 
    tree.Branch("trig_mm"                  , &trig_mm                  , "trig_mm/O"                  ); 
    tree.Branch("trig_em"                  , &trig_em                  , "trig_em/O"                  ); 
    tree.Branch("trig_ee"                  , &trig_ee                  , "trig_ee/O"                  ); 
    tree.Branch("trig_mm_mu17_mu8"         , &trig_mm_mu17_mu8         , "trig_mm_mu17_mu8/O"         ); 
    tree.Branch("trig_ee_el17_el8_id_iso"  , &trig_ee_el17_el8_id_iso  , "trig_ee_el17_el8_id_iso/O"  ); 
    tree.Branch("trig_em_mu17_el8_id_iso"  , &trig_em_mu17_el8_id_iso  , "trig_em_mu17_el8_id_iso/O"  ); 
    tree.Branch("trig_em_mu8_el17_id_iso"  , &trig_em_mu8_el17_id_iso  , "trig_em_mu8_el17_id_iso/O"  ); 
    tree.Branch("njets_dn"                 , &njets_dn                 , "njets_dn/I"                 ); 
    tree.Branch("njets_up"                 , &njets_up                 , "njets_up/I"                 ); 
    tree.Branch("njets_jer"                , &njets_jer                , "njets_jer/I"                ); 
    tree.Branch("nbtags_dn"                , &nbtags_dn                , "nbtags_dn/I"                ); 
    tree.Branch("nbtags_up"                , &nbtags_up                , "nbtags_up/I"                ); 
    tree.Branch("nbtags_jer"               , &nbtags_jer               , "nbtags_jer/I"               ); 
    tree.Branch("ht_dn"                    , &ht_dn                    , "ht_dn/F"                    ); 
    tree.Branch("ht_up"                    , &ht_up                    , "ht_up/F"                    ); 
    tree.Branch("ht_jer"                   , &ht_jer                   , "ht_jer/F"                   ); 
    tree.Branch("nbtags_reweighted"        , &nbtags_reweighted        , "nbtags_reweighted/I"        ); 
    tree.Branch("nbtags_reweighted_dn"     , &nbtags_reweighted_dn     , "nbtags_reweighted_dn/I"     ); 
    tree.Branch("nbtags_reweighted_up"     , &nbtags_reweighted_up     , "nbtags_reweighted_up/I"     ); 
    tree.Branch("nbtags_reweighted_jer"    , &nbtags_reweighted_jer    , "nbtags_reweighted_jer/I"    ); 
    tree.Branch("nbtags_reweighted_jec_dn" , &nbtags_reweighted_jec_dn , "nbtags_reweighted_jec_dn/I" ); 
    tree.Branch("nbtags_reweighted_jec_up" , &nbtags_reweighted_jec_up , "nbtags_reweighted_jec_up/I" ); 
    tree.Branch("pfmet_dn"                 , &pfmet_dn                 , "pfmet_dn/F"                 ); 
    tree.Branch("pfmet_up"                 , &pfmet_up                 , "pfmet_up/F"                 ); 
    tree.Branch("pfmet_phi_dn"             , &pfmet_phi_dn             , "pfmet_phi_dn/F"             ); 
    tree.Branch("pfmet_phi_up"             , &pfmet_phi_up             , "pfmet_phi_up/F"             ); 
    tree.Branch("pfmet_jer"                , &pfmet_jer                , "pfmet_jer/F"                ); 
    tree.Branch("pfmet_jer_phi"            , &pfmet_jer_phi            , "pfmet_jer_phi/F"            ); 
    tree.Branch("pfmet_uncl_dn"            , &pfmet_uncl_dn            , "pfmet_uncl_dn/F"            ); 
    tree.Branch("pfmet_uncl_up"            , &pfmet_uncl_up            , "pfmet_uncl_up/F"            ); 
    tree.Branch("sf_dileptrig"             , &sf_dileptrig             , "sf_dileptrig/F"             ); 
    tree.Branch("sf_lepeff"                , &sf_lepeff                , "sf_lepeff/F"                ); 
    tree.Branch("clean"                    , &clean                    , "clean/O"                    ); 
    tree.Branch("presel"                   , &presel                   , "presel/O"                   ); 
    tree.Branch("hyp_good_vtx"             , &hyp_good_vtx             , "hyp_good_vtx/O"             ); 
    tree.Branch("gen_njets"                , &gen_njets                , "gen_njets/I"                ); 
    tree.Branch("gen_ht"                   , &gen_ht                   , "gen_ht/F"                   ); 
    tree.Branch("lep1_nearb_p4"            , "LorentzVector"           , &lep1_nearb_p4               ); 
    tree.Branch("lep1_nearlep_p4"          , "LorentzVector"           , &lep1_nearlep_p4             ); 
    tree.Branch("lep1_nearb_dr"            , &lep1_nearb_dr            , "lep1_nearb_dr/F"            ); 
    tree.Branch("lep1_nearlep_id"          , &lep1_nearlep_id          , "lep1_nearlep_id/I"          ); 
    tree.Branch("lep1_nearlep_dr"          , &lep1_nearlep_dr          , "lep1_nearlep_dr/F"          ); 
    tree.Branch("lep2_nearb_p4"            , "LorentzVector"           , &lep2_nearb_p4               ); 
    tree.Branch("lep2_nearlep_p4"          , "LorentzVector"           , &lep2_nearlep_p4             ); 
    tree.Branch("lep2_nearb_dr"            , &lep2_nearb_dr            , "lep2_nearb_dr/F"            ); 
    tree.Branch("lep2_nearlep_dr"          , &lep2_nearlep_dr          , "lep2_nearlep_dr/F"          ); 
    tree.Branch("lep2_nearlep_id"          , &lep2_nearlep_id          , "lep2_nearlep_id/I"          ); 
    tree.Branch("vjets_p4"                 , "vecLorentzVector"        , &vjets_p4                    ); 
    tree.Branch("vjets_p4_up"              , "vecLorentzVector"        , &vjets_p4_up                 ); 
    tree.Branch("vjets_p4_dn"              , "vecLorentzVector"        , &vjets_p4_dn                 ); 
    tree.Branch("vjets_btagged_loose"      , "std::vector<bool>"       , &vjets_btagged_loose         ); 
    tree.Branch("vjets_btagged_loose_up"   , "std::vector<bool>"       , &vjets_btagged_loose_up      ); 
    tree.Branch("vjets_btagged_loose_dn"   , "std::vector<bool>"       , &vjets_btagged_loose_dn      ); 
    tree.Branch("vjets_btagged_medium"     , "std::vector<bool>"       , &vjets_btagged_medium        ); 
    tree.Branch("vjets_btagged_medium_up"  , "std::vector<bool>"       , &vjets_btagged_medium_up     ); 
    tree.Branch("vjets_btagged_medium_dn"  , "std::vector<bool>"       , &vjets_btagged_medium_dn     ); 
    tree.Branch("vjets_btagged_tight"      , "std::vector<bool>"       , &vjets_btagged_tight         ); 
    tree.Branch("vjets_btagged_tight_up"   , "std::vector<bool>"       , &vjets_btagged_tight_up      ); 
    tree.Branch("vjets_btagged_tight_dn"   , "std::vector<bool>"       , &vjets_btagged_tight_dn      ); 
    tree.Branch("vjets_mcflavor_phys"      , "veci"                    , &vjets_mcflavor_phys         ); 
    tree.Branch("vjets_mcflavor_algo"      , "veci"                    , &vjets_mcflavor_algo         ); 
    tree.Branch("vjets_mcflavor_phys_up"   , "veci"                    , &vjets_mcflavor_phys_up      ); 
    tree.Branch("vjets_mcflavor_algo_up"   , "veci"                    , &vjets_mcflavor_algo_up      ); 
    tree.Branch("vjets_mcflavor_phys_dn"   , "veci"                    , &vjets_mcflavor_phys_dn      ); 
    tree.Branch("vjets_mcflavor_algo_dn"   , "veci"                    , &vjets_mcflavor_algo_dn      ); 
    tree.Branch("vjets_mc3p4"              , "vecLorentzVector"        , &vjets_mc3p4                 ); 
    tree.Branch("vgenjets_p4"              , "vecLorentzVector"        , &vgenjets_p4                 ); 
    tree.Branch("vgenbs_p4"                , "vecLorentzVector"        , &vgenbs_p4                   ); 
    tree.Branch("vjets_mc3id"              , "veci"                    , &vjets_mc3id                 ); 
    tree.Branch("vjets_momid"              , "veci"                    , &vjets_momid                 ); 
    tree.Branch("vjets_bdisc"              , "vecd"                    , &vjets_bdisc                 );
    tree.Branch("vjets_bdisc_up"           , "vecd"                    , &vjets_bdisc_up              );
    tree.Branch("vjets_bdisc_dn"           , "vecd"                    , &vjets_bdisc_dn              );
    tree.Branch("gen_lep1_p4"              , "LorentzVector"           , &gen_lep1_p4                 ); 
    tree.Branch("gen_lep1_pdgid"           , &gen_lep1_pdgid           , "gen_lep1_pdgid/I"           ); 
    tree.Branch("gen_lep2_p4"              , "LorentzVector"           , &gen_lep2_p4                 ); 
    tree.Branch("gen_lep2_pdgid"           , &gen_lep2_pdgid           , "gen_lep2_pdgid/I"           ); 
    tree.Branch("gen_lep3_p4"              , "LorentzVector"           , &gen_lep3_p4                 ); 
    tree.Branch("gen_lep3_pdgid"           , &gen_lep3_pdgid           , "gen_lep3_pdgid/I"           ); 
    tree.Branch("gen_dilep_p4"             , "LorentzVector"           , &gen_dilep_p4                ); 
    tree.Branch("gen_dilep_type"           , &gen_dilep_type           , "gen_dilep_type/I"           ); 
    tree.Branch("gen_dilep_mass"           , &gen_dilep_mass           , "gen_dilep_mass/F"           ); 
    tree.Branch("gen_dilep_dphi"           , &gen_dilep_dphi           , "gen_dilep_dphi/F"           ); 
    tree.Branch("gen_dilep_deta"           , &gen_dilep_deta           , "gen_dilep_deta/F"           ); 
    tree.Branch("gen_dilep_dr"             , &gen_dilep_dr             , "gen_dilep_dr/F"             ); 

    tree.Branch("pfjets_beta"              , "vecd"                    , &pfjets_beta                 );
    tree.Branch("pfjets_beta2"             , "vecd"                    , &pfjets_beta2                );
    tree.Branch("pfjets_beta_0p1"          , "vecd"                    , &pfjets_beta_0p1             );
    tree.Branch("pfjets_beta_0p2"          , "vecd"                    , &pfjets_beta_0p2             );
    tree.Branch("pfjets_beta2_0p1"         , "vecd"                    , &pfjets_beta2_0p1            );
    tree.Branch("pfjets_beta2_0p5"         , "vecd"                    , &pfjets_beta2_0p5            );
    tree.Branch("pfjets_mvaPUid"           , "vecd"                    , &pfjets_mvaPUid              );
    tree.Branch("pfjets_mva5xPUid"         , "vecd"                    , &pfjets_mva5xPUid            );
    tree.Branch("pfjets_mvaBeta"           , "vecd"                    , &pfjets_mvaBeta              );
    tree.Branch("njets_pv_tight0"          , &njets_pv_tight0          , "njets_pv_tight0/I"          );
    tree.Branch("njets_pv_tight1"          , &njets_pv_tight1          , "njets_pv_tight1/I"          );
    tree.Branch("njets_pv_tight2"          , &njets_pv_tight2          , "njets_pv_tight2/I"          );
}

void OSTree::SetBitMask ()
{
    selection = 0;

    return;
}
