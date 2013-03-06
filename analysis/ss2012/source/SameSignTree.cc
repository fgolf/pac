#include "SameSignTree.h"

SameSignTree::SameSignTree ()
{
}

SameSignTree::SameSignTree (const std::string &prefix)
    : DileptonTree(prefix)
{
}

void SameSignTree::Reset()
{
    event_info.Reset();
    DileptonTree::Reset();

    selection                                = 0;
    is_good_lumi                             = true;
    njets                                    = -999999;
    njets20                                  = -999999;
    njets30                                  = -999999;
    nbtags                                   = -999999;
    nbtags20                                 = -999999;
    nbtags30                                 = -999999;
    ttbar_bkdn                               = -999999;
    vtxw                                     = -999999.0;
    mt                                       = -999999.0;
    ht                                       = -999999.0;
    ht20                                     = -999999.0;
    ht30                                     = -999999.0;
    rho                                      = -999999.0;
    rho_iso                                  = -999999.0;
    sf_dileptrig                             = 1.0;
    sf_lepeff                                = 1.0;
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
    njets_dn                                 = -999999;
    njets_up                                 = -999999;
    nbtags_dn                                = -999999;
    nbtags_up                                = -999999;
    nbtags_reweighted                        = -999999;
    nbtags_reweighted_dn                     = -999999;
    nbtags_reweighted_up                     = -999999;
    ht_dn                                    = -999999.;
    ht_up                                    = -999999.;
    njets20_dn                               = -999999;
    njets20_up                               = -999999;
    nbtags20_dn                              = -999999;
    nbtags20_up                              = -999999;
    ht20_dn                                  = -999999.;
    ht20_up                                  = -999999.;
    njets30_dn                               = -999999;
    njets30_up                               = -999999;
    nbtags30_dn                              = -999999;
    nbtags30_up                              = -999999;
    ht30_dn                                  = -999999.;
    ht30_up                                  = -999999.;
    pfmet_dn                                 = -999999.;
    pfmet_up                                 = -999999.;
    pfmet_phi_dn                             = -999999.;
    pfmet_phi_up                             = -999999.;
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
    gen_nbtags                               = -999999;
    gen_njets                                = -999999;
    gen_nleps                                = -999999;
    gen_nmus                                 = -999999;
    gen_nels                                 = -999999;
    gen_ntaus                                = -999999;
    gen_ht                                   = -999999.0;
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
    jets_dr12                                = -999999.0;
    bjets_dr12                               = -999999.0;
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

    vgenb_p4.clear();
    vjets_p4.clear();
    vjets_btagged.clear();
    vjets_mcflavor_phys.clear();
    vjets_mcflavor_algo.clear();
    vgenjets_p4.clear();
    vjets_nearjet_p4.clear();
    vjets_mc3id.clear();
    vjets_momid.clear();
    vjets_mc3p4.clear();
    vbjets_p4.clear();
    vbjets_nearjet_p4.clear();
    vbjets_nearjet_dr.clear();
    vbjets_mcflavor_phys.clear();
    vbjets_mcflavor_algo.clear();
    vbjets_mc3id.clear();
    vbjets_momid.clear();
    vbjets_mc3p4.clear();
}

void SameSignTree::SetBranches(TTree &tree)
{
    event_info.SetBranches(tree);
    DileptonTree::SetBranches(tree);

    tree.Branch("selection"                                , &selection                                , "selection/i"                                ); 
    tree.Branch("is_good_lumi"                             , &is_good_lumi                             , "is_good_lumi/O"                             ); 
    tree.Branch("njets"                                    , &njets                                    , "njets/I"                                    ); 
    tree.Branch("njets20"                                  , &njets20                                  , "njets20/I"                                  ); 
    tree.Branch("njets30"                                  , &njets30                                  , "njets30/I"                                  ); 
    tree.Branch("nbtags"                                   , &nbtags                                   , "nbtags/I"                                   ); 
    tree.Branch("nbtags20"                                 , &nbtags20                                 , "nbtags20/I"                                 ); 
    tree.Branch("nbtags30"                                 , &nbtags30                                 , "nbtags30/I"                                 ); 
    tree.Branch("ttbar_bkdn"                               , &ttbar_bkdn                               , "ttbar_bkdn/I"                               ); 
    tree.Branch("vtxw"                                     , &vtxw                                     , "vtxw/F"                                     ); 
    tree.Branch("mt"                                       , &mt                                       , "mt/F"                                       ); 
    tree.Branch("ht"                                       , &ht                                       , "ht/F"                                       ); 
    tree.Branch("ht20"                                     , &ht20                                     , "ht20/F"                                     ); 
    tree.Branch("ht30"                                     , &ht30                                     , "ht30/F"                                     ); 
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
    tree.Branch("njets_dn"                                 , &njets_dn                                 , "njets_dn/I"                                 ); 
    tree.Branch("njets_up"                                 , &njets_up                                 , "njets_up/I"                                 ); 
    tree.Branch("nbtags_dn"                                , &nbtags_dn                                , "nbtags_dn/I"                                ); 
    tree.Branch("nbtags_up"                                , &nbtags_up                                , "nbtags_up/I"                                ); 
    tree.Branch("ht_dn"                                    , &ht_dn                                    , "ht_dn/F"                                    ); 
    tree.Branch("ht_up"                                    , &ht_up                                    , "ht_up/F"                                    ); 
    tree.Branch("njets20_dn"                               , &njets20_dn                               , "njets20_dn/I"                               ); 
    tree.Branch("njets20_up"                               , &njets20_up                               , "njets20_up/I"                               ); 
    tree.Branch("nbtags20_dn"                              , &nbtags20_dn                              , "nbtags20_dn/I"                              ); 
    tree.Branch("nbtags20_up"                              , &nbtags20_up                              , "nbtags20_up/I"                              ); 
    tree.Branch("ht20_dn"                                  , &ht20_dn                                  , "ht20_dn/F"                                  ); 
    tree.Branch("ht20_up"                                  , &ht20_up                                  , "ht20_up/F"                                  ); 
    tree.Branch("njets30_dn"                               , &njets30_dn                               , "njets30_dn/I"                               ); 
    tree.Branch("njets30_up"                               , &njets30_up                               , "njets30_up/I"                               ); 
    tree.Branch("nbtags30_dn"                              , &nbtags30_dn                              , "nbtags30_dn/I"                              ); 
    tree.Branch("nbtags30_up"                              , &nbtags30_up                              , "nbtags30_up/I"                              ); 
    tree.Branch("nbtags_reweighted"                        , &nbtags_reweighted                        , "nbtags_reweighted/I"                        ); 
    tree.Branch("nbtags_reweighted_dn"                     , &nbtags_reweighted_dn                     , "nbtags_reweighted_dn/I"                     ); 
    tree.Branch("nbtags_reweighted_up"                     , &nbtags_reweighted_up                     , "nbtags_reweighted_up/I"                     ); 
    tree.Branch("ht30_dn"                                  , &ht30_dn                                  , "ht30_dn/F"                                  ); 
    tree.Branch("ht30_up"                                  , &ht30_up                                  , "ht30_up/F"                                  ); 
    tree.Branch("pfmet_dn"                                 , &pfmet_dn                                 , "pfmet_dn/F"                                 ); 
    tree.Branch("pfmet_up"                                 , &pfmet_up                                 , "pfmet_up/F"                                 ); 
    tree.Branch("pfmet_phi_dn"                             , &pfmet_phi_dn                             , "pfmet_phi_dn/F"                             ); 
    tree.Branch("pfmet_phi_up"                             , &pfmet_phi_up                             , "pfmet_phi_up/F"                             ); 
    tree.Branch("sf_dileptrig"                             , &sf_dileptrig                             , "sf_dileptrig/F"                             ); 
    tree.Branch("sf_lepeff"                                , &sf_lepeff                                , "sf_lepeff/F"                                ); 
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
    tree.Branch("is_sf"                                    , &is_sf                                    , "is_sf/O"                                    ); 
    tree.Branch("is_df"                                    , &is_df                                    , "is_df/O"                                    ); 
    tree.Branch("no_extraz"                                , &no_extraz                                , "no_extraz/O"                                ); 
    tree.Branch("no_extrag"                                , &no_extrag                                , "no_extrag/O"                                ); 
    tree.Branch("clean"                                    , &clean                                    , "clean/O"                                    ); 
    tree.Branch("presel"                                   , &presel                                   , "presel/O"                                   ); 
    tree.Branch("em_mufo"                                  , &em_mufo                                  , "em_mufo/O"                                  ); 
    tree.Branch("em_elfo"                                  , &em_elfo                                  , "em_elfo/O"                                  ); 
    tree.Branch("hyp_good_vtx"                             , &hyp_good_vtx                             , "hyp_good_vtx/O"                             ); 
    tree.Branch("is_gen_pp"                                , &is_gen_pp                                , "is_gen_pp/O"                                ); 
    tree.Branch("is_gen_mm"                                , &is_gen_mm                                , "is_gen_mm/O"                                ); 
    tree.Branch("gen_nbtags"                               , &gen_nbtags                               , "gen_nbtags/I"                               ); 
    tree.Branch("gen_njets"                                , &gen_njets                                , "gen_njets/I"                                ); 
    tree.Branch("gen_nleps"                                , &gen_nleps                                , "gen_nleps/I"                                ); 
    tree.Branch("gen_nmus"                                 , &gen_nmus                                 , "gen_nmus/I"                                 ); 
    tree.Branch("gen_nels"                                 , &gen_nels                                 , "gen_nels/I"                                 ); 
    tree.Branch("gen_ntaus"                                , &gen_ntaus                                , "gen_ntaus/I"                                ); 
    tree.Branch("gen_ht"                                   , &gen_ht                                   , "gen_ht/F"                                   ); 
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
    tree.Branch("jets_dr12"                                , &jets_dr12                                , "jets_dr12/F"                                ); 
    tree.Branch("bjets_dr12"                               , &bjets_dr12                               , "bjets_dr12/F"                               ); 
    tree.Branch("vgenb_p4"                                 , "vecLorentzVector"                        , &vgenb_p4                                    ); 
    tree.Branch("vjets_p4"                                 , "vecLorentzVector"                        , &vjets_p4                                    ); 
    tree.Branch("vjets_btagged"                            , "std::vector<bool>"                       , &vjets_btagged                               ); 
    tree.Branch("vjets_mcflavor_phys"                      , "veci"                                    , &vjets_mcflavor_phys                         ); 
    tree.Branch("vjets_mcflavor_algo"                      , "veci"                                    , &vjets_mcflavor_algo                         ); 
    tree.Branch("vjets_mc3p4"                              , "vecLorentzVector"                        , &vjets_mc3p4                                 ); 
    tree.Branch("vgenjets_p4"                              , "vecLorentzVector"                        , &vgenjets_p4                                 ); 
    tree.Branch("vjets_mc3id"                              , "veci"                                    , &vjets_mc3id                                 ); 
    tree.Branch("vjets_momid"                              , "veci"                                    , &vjets_momid                                 ); 
    tree.Branch("vjets_nearjet_p4"                         , "vecLorentzVector"                        , &vjets_nearjet_p4                            ); 
    tree.Branch("vbjets_p4"                                , "vecLorentzVector"                        , &vbjets_p4                                   ); 
    tree.Branch("vbjets_mcflavor_phys"                     , "veci"                                    , &vbjets_mcflavor_phys                        ); 
    tree.Branch("vbjets_mcflavor_algo"                     , "veci"                                    , &vbjets_mcflavor_algo                        ); 
    tree.Branch("vbjets_mc3p4"                             , "vecLorentzVector"                        , &vbjets_mc3p4                                ); 
    tree.Branch("vbjets_nearjet_p4"                        , "vecLorentzVector"                        , &vbjets_nearjet_p4                           ); 
    tree.Branch("vbjets_nearjet_dr"                        , "vecd"                                    , &vbjets_nearjet_dr                           ); 
    tree.Branch("vbjets_mc3id"                             , "veci"                                    , &vbjets_mc3id                                ); 
    tree.Branch("vbjets_momid"                             , "veci"                                    , &vbjets_momid                                ); 
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
}
