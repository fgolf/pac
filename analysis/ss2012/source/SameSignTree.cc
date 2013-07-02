#include "SameSignTree.h"

SameSignTree::SameSignTree()
    : DileptonTree()
    , jet_info("")
    , jet_info_up("", "_jec_up")
    , jet_info_dn("", "_jec_dn")
    , jet_info_pt30("", "_pt30")
    , lep3("lep3_")
{
}

SameSignTree::SameSignTree(const std::string &prefix)
    : DileptonTree(prefix)
    , jet_info("")
    , jet_info_up("", "_jec_up")
    , jet_info_dn("", "_jec_dn")
    , jet_info_pt30("", "_pt30")
    , lep3("lep3_")
{
}

void SameSignTree::Reset()
{
    event_info.Reset();
    DileptonTree::Reset();
    jet_info.Reset();
    jet_info_up.Reset();
    jet_info_dn.Reset();
    jet_info_pt30.Reset();
    lep3.Reset();

    selection                                = 0;
    anal_type                                = -999999;
    is_good_lumi                             = true;
    charge_type                              = -999999;
    ttbar_bkdn                               = -999999;
    higgs_bkdn                               = -999999;
    higgs_decay                              = -999999;
    vtxw                                     = -999999.0;
    mt                                       = -999999.0;
    rho                                      = -999999.0;
    rho_iso                                  = -999999.0;
    sf_dileptrig                             = 1.0;
    sf_dileptrig_hpt                         = 1.0;
    sf_dileptrig_lpt                         = 1.0;
    sf_dileptrig_vpt                         = 1.0;
    sf_dilepeff                              = 1.0;
    trig_mm                                  = false;
    trig_em                                  = false;
    trig_ee                                  = false;
    trig_hpt                                 = false;
    trig_lpt                                 = false;
    trig_lpt_isomu                           = false;
    trig_mm_mu17_mu8                         = false;
    trig_mm_dmu8_m8_pfht175                  = false;
    trig_mm_dmu8_m8_pfnopuht175              = false;
    trig_mm_dreliso1p0mu5_m8_pfht175         = false;
    trig_mm_dreliso1p0mu5_m8_pfnopuht175     = false;
    trig_ee_el17_el8_id_iso                  = false;
    trig_ee_del8_id_m8_pfht175               = false;
    trig_ee_del8_id_m8_pfnopuht175           = false;
    trig_em_mu17_el8_id_iso                  = false;
    trig_em_mu8_el17_id_iso                  = false;
    trig_em_mu8_el8_id_m8_pfht175            = false;
    trig_em_mu8_el8_id_m8_pfnopuht175        = false;
    trig_em_riso1p0mu5_el8_id_m8_pfht175     = false;
    trig_em_riso1p0mu5_el8_id_m8_pfnopuht175 = false;
    njets_jer                                = -999999;
    nbtags_jer                               = -999999;
    nbtags_reweighted_jer                    = -999999;
    ht_jer                                   = -999999.;
    pfmet_jec_dn                             = -999999.;
    pfmet_jec_up                             = -999999.;
    pfmet_phi_jec_dn                         = -999999.;
    pfmet_phi_jec_up                         = -999999.;
    pfmet_jer                                = -999999.;
    pfmet_jer_phi                            = -999999.;
    pfmet_uncl_dn                            = -999999.;
    pfmet_uncl_up                            = -999999.;
    sparm0                                   = -999999.0;
    sparm1                                   = -999999.0;
    sparm2                                   = -999999.0;
    sparm3                                   = -999999.0;
    sparm0_name                              = "";
    sparm1_name                              = "";
    sparm2_name                              = "";
    sparm3_name                              = "";
    is_pp                                    = false;
    is_mm                                    = false;
    is_ss                                    = false;
    is_sf                                    = false;
    is_df                                    = false;
    is_os                                    = false;
    em_mufo                                  = false;
    em_elfo                                  = false;
    is_df                                    = false;
    is_gen_pp                                = false;
    is_gen_mm                                = false;
    no_extraz                                = false;
    no_extrag                                = false;
    clean                                    = false;
    hyp_good_vtx                             = false;
    presel                                   = false;
    lep1_nearbjet_p4                         = LorentzVector(0, 0, 0, 0);
    lep1_nearjet_p4                          = LorentzVector(0, 0, 0, 0);
    lep1_nearlep_p4                          = LorentzVector(0, 0, 0, 0);
    lep1_wfr                                 = -999999.0;
    lep1_wflip                               = -999999.0;
    lep1_nearbjet_dr                         = -999999.0;
    lep1_nearjet_dr                          = -999999.0;
    lep1_nearlep_dr                          = -999999.0;
    lep1_nearlep_id                          = -999999;
    lep2_nearbjet_p4                         = LorentzVector(0, 0, 0, 0);
    lep2_nearjet_p4                          = LorentzVector(0, 0, 0, 0);
    lep2_nearlep_p4                          = LorentzVector(0, 0, 0, 0);
    lep2_wfr                                 = -999999.0;
    lep2_wflip                               = -999999.0;
    lep2_nearbjet_dr                         = -999999.0;
    lep2_nearjet_dr                          = -999999.0;
    lep2_nearlep_id                          = -999999;
    sf_nbtag                                 = -999999.0;
    sf_nbtag3                                = -999999.0;
    sf_unc_nbtag                             = -999999.0;
    sf_unc_nbtag3                            = -999999.0;
    gen_lep1_p4                              = LorentzVector(0, 0, 0, 0);
    gen_lep1_pdgid                           = -999999;
    gen_lep2_p4                              = LorentzVector(0, 0, 0, 0);
    gen_lep2_pdgid                           = -999999;
    gen_dilep_p4                             = LorentzVector(0, 0, 0, 0);
    gen_dilep_type                           = at::DileptonHypType::static_size;
    gen_dilep_mass                           = -999999.0;
    gen_dilep_dphi                           = -999999.0;
    gen_dilep_deta                           = -999999.0;
    gen_dilep_dr                             = -999999.0;
    lep3_wfr                                 = -999999.0;
    lep3_wflip                               = -999999.0;
    pfTau15_leadPtcandID                     = -999999;
    pfTau_leadPtcandID                       = -999999;
    pfTauLoose_leadPtcandID                  = -999999;
    passes_tau_veto                          = false;
    passes_isotrk_veto                       = false;
    passes_3lep_veto                         = false;
    pfTau15                                  = LorentzVector(0, 0, 0, 0);
    pfTau15_leadPtcand                       = LorentzVector(0, 0, 0, 0);
    pfTau                                    = LorentzVector(0, 0, 0, 0);
    pfTau_leadPtcand                         = LorentzVector(0, 0, 0, 0);
    pfTauLoose                               = LorentzVector(0, 0, 0, 0);
    pfTauLoose_leadPtcand                    = LorentzVector(0, 0, 0, 0);
}

void SameSignTree::SetBranches(TTree &tree)
{
    event_info.SetBranches(tree);
    DileptonTree::SetBranches(tree);
    lep3.SetBranches(tree);
    jet_info.SetBranches(tree);
    jet_info_up.SetBranches(tree);
    jet_info_dn.SetBranches(tree);
    jet_info_pt30.SetBranches(tree);

    tree.Branch("selection"                                , &selection                                , "selection/i"                                ); 
    tree.Branch("anal_type"                                , &anal_type                                , "anal_type/I"                                ); 
    tree.Branch("is_good_lumi"                             , &is_good_lumi                             , "is_good_lumi/O"                             ); 
    tree.Branch("charge_type"                              , &charge_type                              , "charge_type/I"                              ); 
    tree.Branch("ttbar_bkdn"                               , &ttbar_bkdn                               , "ttbar_bkdn/I"                               ); 
    tree.Branch("higgs_bkdn"                               , &higgs_bkdn                               , "higgs_bkdn/I"                               ); 
    tree.Branch("higgs_decay"                              , &higgs_decay                              , "higgs_decay/I"                              ); 
    tree.Branch("vtxw"                                     , &vtxw                                     , "vtxw/F"                                     ); 
    tree.Branch("mt"                                       , &mt                                       , "mt/F"                                       ); 
    tree.Branch("rho"                                      , &rho                                      , "rho/F"                                      ); 
    tree.Branch("rho_iso"                                  , &rho_iso                                  , "rho_iso/F"                                  ); 
    tree.Branch("trig_mm"                                  , &trig_mm                                  , "trig_mm/O"                                  ); 
    tree.Branch("trig_em"                                  , &trig_em                                  , "trig_em/O"                                  ); 
    tree.Branch("trig_ee"                                  , &trig_ee                                  , "trig_ee/O"                                  ); 
    tree.Branch("trig_hpt"                                 , &trig_hpt                                 , "trig_hpt/O"                                 ); 
    tree.Branch("trig_lpt"                                 , &trig_lpt                                 , "trig_lpt/O"                                 ); 
    tree.Branch("trig_lpt_isomu"                           , &trig_lpt_isomu                           , "trig_lpt_isomu/O"                           ); 
    tree.Branch("trig_mm_mu17_mu8"                         , &trig_mm_mu17_mu8                         , "trig_mm_mu17_mu8/O"                         ); 
    tree.Branch("trig_mm_dmu8_m8_pfht175"                  , &trig_mm_dmu8_m8_pfht175                  , "trig_mm_dmu8_m8_pfht175/O"                  ); 
    tree.Branch("trig_mm_dmu8_m8_pfnopuht175"              , &trig_mm_dmu8_m8_pfnopuht175              , "trig_mm_dmu8_m8_pfnopuht175/O"              ); 
    tree.Branch("trig_mm_dreliso1p0mu5_m8_pfht175"         , &trig_mm_dreliso1p0mu5_m8_pfht175         , "trig_mm_dreliso1p0mu5_m8_pfht175/O"         ); 
    tree.Branch("trig_mm_dreliso1p0mu5_m8_pfnopuht175"     , &trig_mm_dreliso1p0mu5_m8_pfnopuht175     , "trig_mm_dreliso1p0mu5_m8_pfnopuht175/O"     ); 
    tree.Branch("trig_ee_el17_el8_id_iso"                  , &trig_ee_el17_el8_id_iso                  , "trig_ee_el17_el8_id_iso/O"                  ); 
    tree.Branch("trig_ee_del8_id_m8_pfht175"               , &trig_ee_del8_id_m8_pfht175               , "trig_ee_del8_id_m8_pfht175/O"               ); 
    tree.Branch("trig_ee_del8_id_m8_pfnopuht175"           , &trig_ee_del8_id_m8_pfnopuht175           , "trig_ee_del8_id_m8_pfnopuht175/O"           ); 
    tree.Branch("trig_em_mu17_el8_id_iso"                  , &trig_em_mu17_el8_id_iso                  , "trig_em_mu17_el8_id_iso/O"                  ); 
    tree.Branch("trig_em_mu8_el17_id_iso"                  , &trig_em_mu8_el17_id_iso                  , "trig_em_mu8_el17_id_iso/O"                  ); 
    tree.Branch("trig_em_mu8_el8_id_m8_pfht175"            , &trig_em_mu8_el8_id_m8_pfht175            , "trig_em_mu8_el8_id_m8_pfht175/O"            ); 
    tree.Branch("trig_em_mu8_el8_id_m8_pfnopuht175"        , &trig_em_mu8_el8_id_m8_pfnopuht175        , "trig_em_mu8_el8_id_m8_pfnopuht175/O"        ); 
    tree.Branch("trig_em_riso1p0mu5_el8_id_m8_pfht175"     , &trig_em_riso1p0mu5_el8_id_m8_pfht175     , "trig_em_riso1p0mu5_el8_id_m8_pfht175/O"     ); 
    tree.Branch("trig_em_riso1p0mu5_el8_id_m8_pfnopuht175" , &trig_em_riso1p0mu5_el8_id_m8_pfnopuht175 , "trig_em_riso1p0mu5_el8_id_m8_pfnopuht175/O" ); 
    tree.Branch("njets_jer"                                , &njets_jer                                , "njets_jer/I"                                ); 
    tree.Branch("ht_jer"                                   , &ht_jer                                   , "ht_jer/F"                                   ); 
    tree.Branch("nbtags_jer"                               , &nbtags_jer                               , "nbtags_jer/I"                               ); 
    tree.Branch("nbtags_reweighted_jer"                    , &nbtags_reweighted_jer                    , "nbtags_reweighted_jer/I"                    ); 
    tree.Branch("pfmet_jec_dn"                             , &pfmet_jec_dn                             , "pfmet_jec_dn/F"                             ); 
    tree.Branch("pfmet_jec_up"                             , &pfmet_jec_up                             , "pfmet_jec_up/F"                             ); 
    tree.Branch("pfmet_phi_jec_dn"                         , &pfmet_phi_jec_dn                         , "pfmet_phi_jec_dn/F"                         ); 
    tree.Branch("pfmet_phi_jec_up"                         , &pfmet_phi_jec_up                         , "pfmet_phi_jec_up/F"                         ); 
    tree.Branch("pfmet_jer"                                , &pfmet_jer                                , "pfmet_jer/F"                                ); 
    tree.Branch("pfmet_jer_phi"                            , &pfmet_jer_phi                            , "pfmet_jer_phi/F"                            ); 
    tree.Branch("pfmet_uncl_dn"                            , &pfmet_uncl_dn                            , "pfmet_uncl_dn/F"                            ); 
    tree.Branch("pfmet_uncl_up"                            , &pfmet_uncl_up                            , "pfmet_uncl_up/F"                            ); 
    tree.Branch("sf_dileptrig"                             , &sf_dileptrig                             , "sf_dileptrig/F"                             ); 
    tree.Branch("sf_dileptrig_hpt"                         , &sf_dileptrig_hpt                         , "sf_dileptrig_hpt/F"                         ); 
    tree.Branch("sf_dileptrig_lpt"                         , &sf_dileptrig_lpt                         , "sf_dileptrig_lpt/F"                         ); 
    tree.Branch("sf_dileptrig_vpt"                         , &sf_dileptrig_vpt                         , "sf_dileptrig_vpt/F"                         ); 
    tree.Branch("sf_dilepeff"                              , &sf_dilepeff                              , "sf_dilepeff/F"                              ); 
    tree.Branch("sparm0"                                   , &sparm0                                   , "sparm0/F"                                   ); 
    tree.Branch("sparm1"                                   , &sparm1                                   , "sparm1/F"                                   ); 
    tree.Branch("sparm2"                                   , &sparm2                                   , "sparm2/F"                                   ); 
    tree.Branch("sparm3"                                   , &sparm3                                   , "sparm3/F"                                   ); 
    tree.Branch("sparm0_name"                              , "TString"                                 , &sparm0_name                                 ); 
    tree.Branch("sparm1_name"                              , "TString"                                 , &sparm1_name                                 ); 
    tree.Branch("sparm2_name"                              , "TString"                                 , &sparm2_name                                 ); 
    tree.Branch("sparm3_name"                              , "TString"                                 , &sparm3_name                                 ); 
    tree.Branch("is_pp"                                    , &is_pp                                    , "is_pp/O"                                    ); 
    tree.Branch("is_mm"                                    , &is_mm                                    , "is_mm/O"                                    ); 
    tree.Branch("is_ss"                                    , &is_ss                                    , "is_ss/O"                                    ); 
    tree.Branch("is_sf"                                    , &is_sf                                    , "is_sf/O"                                    ); 
    tree.Branch("is_df"                                    , &is_df                                    , "is_df/O"                                    ); 
    tree.Branch("is_os"                                    , &is_os                                    , "is_os/O"                                    ); 
    tree.Branch("no_extraz"                                , &no_extraz                                , "no_extraz/O"                                ); 
    tree.Branch("no_extrag"                                , &no_extrag                                , "no_extrag/O"                                ); 
    tree.Branch("clean"                                    , &clean                                    , "clean/O"                                    ); 
    tree.Branch("presel"                                   , &presel                                   , "presel/O"                                   ); 
    tree.Branch("em_mufo"                                  , &em_mufo                                  , "em_mufo/O"                                  ); 
    tree.Branch("em_elfo"                                  , &em_elfo                                  , "em_elfo/O"                                  ); 
    tree.Branch("hyp_good_vtx"                             , &hyp_good_vtx                             , "hyp_good_vtx/O"                             ); 
    tree.Branch("is_gen_pp"                                , &is_gen_pp                                , "is_gen_pp/O"                                ); 
    tree.Branch("is_gen_mm"                                , &is_gen_mm                                , "is_gen_mm/O"                                ); 
    tree.Branch("lep1_nearbjet_p4"                         , "LorentzVector"                           , &lep1_nearbjet_p4                            ); 
    tree.Branch("lep1_nearjet_p4"                          , "LorentzVector"                           , &lep1_nearjet_p4                             ); 
    tree.Branch("lep1_nearlep_p4"                          , "LorentzVector"                           , &lep1_nearlep_p4                             ); 
    tree.Branch("lep1_wfr"                                 , &lep1_wfr                                 , "lep1_wfr/F"                                 ); 
    tree.Branch("lep1_wflip"                               , &lep1_wflip                               , "lep1_wflip/F"                               ); 
    tree.Branch("lep1_nearbjet_dr"                         , &lep1_nearbjet_dr                         , "lep1_nearbjet_dr/F"                         ); 
    tree.Branch("lep1_nearjet_dr"                          , &lep1_nearjet_dr                          , "lep1_nearjet_dr/F"                          ); 
    tree.Branch("lep1_nearlep_dr"                          , &lep1_nearlep_dr                          , "lep1_nearlep_dr/F"                          ); 
    tree.Branch("lep1_nearlep_id"                          , &lep1_nearlep_id                          , "lep1_nearlep_id/I"                          ); 
    tree.Branch("lep2_nearbjet_p4"                         , "LorentzVector"                           , &lep2_nearbjet_p4                            ); 
    tree.Branch("lep2_nearjet_p4"                          , "LorentzVector"                           , &lep2_nearjet_p4                             ); 
    tree.Branch("lep2_nearlep_p4"                          , "LorentzVector"                           , &lep2_nearlep_p4                             ); 
    tree.Branch("lep2_wfr"                                 , &lep2_wfr                                 , "lep2_wfr/F"                                 ); 
    tree.Branch("lep2_wflip"                               , &lep2_wflip                               , "lep2_wflip/F"                               ); 
    tree.Branch("lep2_nearbjet_dr"                         , &lep2_nearbjet_dr                         , "lep2_nearbjet_dr/F"                         ); 
    tree.Branch("lep2_nearjet_dr"                          , &lep2_nearjet_dr                          , "lep2_nearjet_dr/F"                          ); 
    tree.Branch("lep2_nearlep_dr"                          , &lep2_nearlep_dr                          , "lep2_nearlep_dr/F"                          ); 
    tree.Branch("lep2_nearlep_id"                          , &lep2_nearlep_id                          , "lep2_nearlep_id/I"                          ); 
    tree.Branch("sf_nbtag"                                 , &sf_nbtag                                 , "sf_nbtag/F"                                 ); 
    tree.Branch("sf_nbtag3"                                , &sf_nbtag3                                , "sf_nbtag3/F"                                ); 
    tree.Branch("sf_unc_nbtag"                             , &sf_unc_nbtag                             , "sf_unc_nbtag/F"                             ); 
    tree.Branch("sf_unc_nbtag3"                            , &sf_unc_nbtag3                            , "sf_unc_nbtag3/F"                            ); 
    tree.Branch("gen_lep1_p4"                              , "LorentzVector"                           , &gen_lep1_p4                                 ); 
    tree.Branch("gen_lep1_pdgid"                           , &gen_lep1_pdgid                           , "gen_lep1_pdgid/I"                           ); 
    tree.Branch("gen_lep2_p4"                              , "LorentzVector"                           , &gen_lep2_p4                                 ); 
    tree.Branch("gen_lep2_pdgid"                           , &gen_lep2_pdgid                           , "gen_lep2_pdgid/I"                           ); 
    tree.Branch("gen_dilep_p4"                             , "LorentzVector"                           , &gen_dilep_p4                                ); 
    tree.Branch("gen_dilep_type"                           , &gen_dilep_type                           , "gen_dilep_type/I"                           ); 
    tree.Branch("gen_dilep_mass"                           , &gen_dilep_mass                           , "gen_dilep_mass/F"                           ); 
    tree.Branch("gen_dilep_dphi"                           , &gen_dilep_dphi                           , "gen_dilep_dphi/F"                           ); 
    tree.Branch("gen_dilep_deta"                           , &gen_dilep_deta                           , "gen_dilep_deta/F"                           ); 
    tree.Branch("gen_dilep_dr"                             , &gen_dilep_dr                             , "gen_dilep_dr/F"                             ); 
    tree.Branch("lep3_wfr"                                 , &lep3_wfr                                 , "lep3_wfr/F"                                 ); 
    tree.Branch("lep3_wflip"                               , &lep3_wflip                               , "lep3_wflip/F"                               ); 
    tree.Branch("pfTau15_leadPtcandID"                     , &pfTau15_leadPtcandID                     , "pfTau15_leadPtcandID/I"                     ); 
    tree.Branch("pfTau_leadPtcandID"                       , &pfTau_leadPtcandID                       , "pfTau_leadPtcandID/I"                       ); 
    tree.Branch("pfTauLoose_leadPtcandID"                  , &pfTauLoose_leadPtcandID                  , "pfTauLoose_leadPtcandID/I"                  ); 
    tree.Branch("passes_tau_veto"                          , &passes_tau_veto                          , "passes_tau_veto/O"                          ); 
    tree.Branch("passes_isotrk_veto"                       , &passes_isotrk_veto                       , "passes_isotrk_veto/O"                       ); 
    tree.Branch("passes_3lep_veto"                         , &passes_3lep_veto                         , "passes_3lep_veto/O"                         ); 
    tree.Branch("pfTau15"                                  , "LorentzVector"                           , &pfTau15                                     ); 
    tree.Branch("pfTau15_leadPtcand"                       , "LorentzVector"                           , &pfTau15_leadPtcand                          ); 
    tree.Branch("pfTau"                                    , "LorentzVector"                           , &pfTau                                       ); 
    tree.Branch("pfTau_leadPtcand"                         , "LorentzVector"                           , &pfTau_leadPtcand                            ); 
    tree.Branch("pfTauLoose"                               , "LorentzVector"                           , &pfTauLoose                                  ); 
    tree.Branch("pfTauLoose_leadPtcand"                    , "LorentzVector"                           , &pfTauLoose_leadPtcand                       ); 
}
