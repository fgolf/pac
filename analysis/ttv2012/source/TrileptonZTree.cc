#include "TrileptonZTree.h"

TrileptonZTree::TrileptonZTree ()
{
    dilep = DileptonTree("z");
    lep3 = SingleLeptonTree("w");
}

TrileptonZTree::TrileptonZTree (const std::string &prefix)
    : prefix_(prefix)
{
}

void TrileptonZTree::Reset()
{
    event_info.Reset();
    dilep.Reset();
    lep3.Reset();

    selection              = 0;
    clean                  = false;
    is_good_lumi           = true;
    njets30                = -999999;
    njets15                = -999999;
    nbtags_loose           = -999999;
    nbtags_tight           = -999999;
    vtxw                   = -999999.0;
    ht                     = -999999.0;
    rho                    = -999999.0;
    rho_iso                = -999999.0;
    sf_dileptrig           = 1.0;
    sf_lepeff              = 1.0;
    trig_mm                = false;
    trig_em                = false;
    trig_ee                = false;
    event_type             = ttv2012::EventType::static_size;
    njets30_dn             = -999999;
    njets30_up             = -999999;
    njets15_dn             = -999999;
    njets15_up             = -999999;
    nbtags_loose_dn        = -999999;
    nbtags_loose_up        = -999999;
    nbtags_tight_dn        = -999999;
    nbtags_tight_up        = -999999;
    ht_dn                  = -999999.;
    ht_up                  = -999999.;
    pfmet_dn               = -999999.;
    pfmet_up               = -999999.;
    pfmet_phi_dn           = -999999.;
    pfmet_phi_up           = -999999.;
    lep1_nearbjet_p4       = LorentzVector(0, 0, 0, 0);
    lep1_nearjet_p4        = LorentzVector(0, 0, 0, 0);
    lep1_nearlep_p4        = LorentzVector(0, 0, 0, 0);
    lep1_wfr               = -999999.0;
    lep1_nearbjet_dr       = -999999.0;
    lep1_nearjet_dr        = -999999.0;
    lep1_nearlep_dr        = -999999.0;
    lep1_nearlep_id        = -999999;
    lep1_passes_id_bitmask = 0;
    lep2_nearbjet_p4       = LorentzVector(0, 0, 0, 0);
    lep2_nearjet_p4        = LorentzVector(0, 0, 0, 0);
    lep2_nearlep_p4        = LorentzVector(0, 0, 0, 0);
    lep2_wfr               = -999999.0;
    lep2_nearbjet_dr       = -999999.0;
    lep2_nearjet_dr        = -999999.0;
    lep2_nearlep_id        = -999999;
    lep2_passes_id_bitmask = 0;
    lep3_nearbjet_p4       = LorentzVector(0, 0, 0, 0);
    lep3_nearjet_p4        = LorentzVector(0, 0, 0, 0);
    lep3_nearlep_p4        = LorentzVector(0, 0, 0, 0);
    lep3_wfr               = -999999.0;
    lep3_nearbjet_dr       = -999999.0;
    lep3_nearjet_dr        = -999999.0;
    lep1_ele_mva_trig      = -999999.0;
    lep2_ele_mva_trig      = -999999.0;
    lep3_ele_mva_trig      = -999999.0;
    lep1_ele_mva_nontrig   = -999999.0;
    lep2_ele_mva_nontrig   = -999999.0;
    lep3_ele_mva_nontrig   = -999999.0;
    lep3_nearlep_id        = -999999;
    lep3_passes_id_bitmask = 0;
    is_gen_z               = false;
    is_gen_w               = false;
    gen_nbtags             = -999999;
    gen_njets              = -999999;
    gen_ht                 = -999999.0;
    gen_nleps              = 0;
    sf_nbtag               = -999999.0;
    sf_nbtag2              = -999999.0;
    sf_unc_nbtag           = -999999.0;
    sf_unc_nbtag2          = -999999.0;
    bjets_dr12             = -999999.0;
    gen_lep1_p4            = LorentzVector(0, 0, 0, 0);
    gen_lep1_pdgid         = -999999;
    gen_lep2_p4            = LorentzVector(0, 0, 0, 0);
    gen_lep2_pdgid         = -999999;    
    gen_lep3_p4            = LorentzVector(0, 0, 0, 0);
    gen_mt                 = -999999.;
    gen_lep3_pdgid         = -999999;    
    gen_dilep_p4           = LorentzVector(0, 0, 0, 0);
    gen_dilep_type         = at::DileptonHypType::static_size;
    gen_dilep_mass         = -999999.0;
    gen_dilep_dphi         = -999999.0;
    gen_dilep_deta         = -999999.0;
    gen_dilep_dr           = -999999.0;    

    vgenb_p4.clear();
    vjets_p4.clear();
    vgenjets_p4.clear();
    vbjets_disc.clear();
    vbjets_p4.clear();
    vbtags_loose.clear();
    vbtags_tight.clear();
}

void TrileptonZTree::SetBranches(TTree &tree)
{
    event_info.SetBranches(tree);
    dilep.SetBranches(tree);
    lep3.SetBranches(tree);

    tree.Branch(Form("%sselection"              , prefix_.c_str()), &selection              , "selection/i"              );
    tree.Branch(Form("%sclean"                  , prefix_.c_str()), &clean                  , "clean/O"                  );
    tree.Branch(Form("%sis_good_lumi"           , prefix_.c_str()), &is_good_lumi           , "is_good_lumi/O"           );
    tree.Branch(Form("%snjets15"                , prefix_.c_str()), &njets15                , "njets15/I"                );
    tree.Branch(Form("%snjets30"                , prefix_.c_str()), &njets30                , "njets30/I"                );
    tree.Branch(Form("%snbtags_loose"           , prefix_.c_str()), &nbtags_loose           , "nbtags_loose/I"           );
    tree.Branch(Form("%snbtags_loose"           , prefix_.c_str()), &nbtags_loose           , "nbtags_loose/I"           );
    tree.Branch(Form("%svtxw"                   , prefix_.c_str()), &vtxw                   , "vtxw/F"                   );
    tree.Branch(Form("%sht"                     , prefix_.c_str()), &ht                     , "ht/F"                     );
    tree.Branch(Form("%srho"                    , prefix_.c_str()), &rho                    , "rho/F"                    );
    tree.Branch(Form("%srho_iso"                , prefix_.c_str()), &rho_iso                , "rho_iso/F"                );
    tree.Branch(Form("%ssf_dileptrig"           , prefix_.c_str()), &sf_dileptrig           , "sf_dileptrig/F"           );
    tree.Branch(Form("%ssf_lepeff"              , prefix_.c_str()), &sf_lepeff              , "sf_lepeff/F"              );
    tree.Branch(Form("%strig_mm"                , prefix_.c_str()), &trig_mm                , "trig_mm/O"                );
    tree.Branch(Form("%strig_em"                , prefix_.c_str()), &trig_em                , "trig_em/O"                );
    tree.Branch(Form("%strig_ee"                , prefix_.c_str()), &trig_ee                , "trig_ee/O"                );
    tree.Branch(Form("%sevent_type"             , prefix_.c_str()), &event_type             , "event_type/I"             );
    tree.Branch(Form("%snjets30_dn"             , prefix_.c_str()), &njets30_dn             , "njets30_dn/I"             );
    tree.Branch(Form("%snjets30_up"             , prefix_.c_str()), &njets30_up             , "njets30_up/I"             );
    tree.Branch(Form("%snjets15_dn"             , prefix_.c_str()), &njets15_dn             , "njets15_dn/I"             );
    tree.Branch(Form("%snjets15_up"             , prefix_.c_str()), &njets15_up             , "njets15_up/I"             );
    tree.Branch(Form("%snbtags_loose_dn"        , prefix_.c_str()), &nbtags_loose_dn        , "nbtags_loose_dn/I"        );
    tree.Branch(Form("%snbtags_loose_up"        , prefix_.c_str()), &nbtags_loose_up        , "nbtags_loose_up/I"        );
    tree.Branch(Form("%sht_dn"                  , prefix_.c_str()), &ht_dn                  , "ht_dn/F"                  );
    tree.Branch(Form("%sht_up"                  , prefix_.c_str()), &ht_up                  , "ht_up/F"                  );
    tree.Branch(Form("%spfmet_dn"               , prefix_.c_str()), &pfmet_dn               , "pfmet_dn/F"               );
    tree.Branch(Form("%spfmet_up"               , prefix_.c_str()), &pfmet_up               , "pfmet_up/F"               );
    tree.Branch(Form("%spfmet_phi_dn"           , prefix_.c_str()), &pfmet_phi_dn           , "pfmet_phi_dn/F"           );
    tree.Branch(Form("%spfmet_phi_up"           , prefix_.c_str()), &pfmet_phi_up           , "pfmet_phi_up/F"           );
    tree.Branch(Form("%slep1_nearbjet_p4"       , prefix_.c_str()), "LorentzVector"         , &lep1_nearbjet_p4          );
    tree.Branch(Form("%slep1_nearjet_p4"        , prefix_.c_str()), "LorentzVector"         , &lep1_nearjet_p4           );
    tree.Branch(Form("%slep1_nearlep_p4"        , prefix_.c_str()), "LorentzVector"         , &lep1_nearlep_p4           );
    tree.Branch(Form("%slep1_wfr"               , prefix_.c_str()), &lep1_wfr               , "lep1_wfr/F"               );
    tree.Branch(Form("%slep1_nearbjet_dr"       , prefix_.c_str()), &lep1_nearbjet_dr       , "lep1_nearbjet_dr/F"       );
    tree.Branch(Form("%slep1_nearjet_dr"        , prefix_.c_str()), &lep1_nearjet_dr        , "lep1_nearjet_dr/F"        );
    tree.Branch(Form("%slep1_nearlep_dr"        , prefix_.c_str()), &lep1_nearlep_dr        , "lep1_nearlep_dr/F"        );
    tree.Branch(Form("%slep1_nearlep_id"        , prefix_.c_str()), &lep1_nearlep_id        , "lep1_nearlep_id/I"        );
    tree.Branch(Form("%slep1_passes_id_bitmask" , prefix_.c_str()), &lep1_passes_id_bitmask , "lep1_passes_id_bitmask/I" );
    tree.Branch(Form("%slep2_nearbjet_p4"       , prefix_.c_str()), "LorentzVector"         , &lep2_nearbjet_p4          );
    tree.Branch(Form("%slep2_nearjet_p4"        , prefix_.c_str()), "LorentzVector"         , &lep2_nearjet_p4           );
    tree.Branch(Form("%slep2_nearlep_p4"        , prefix_.c_str()), "LorentzVector"         , &lep2_nearlep_p4           );
    tree.Branch(Form("%slep2_wfr"               , prefix_.c_str()), &lep2_wfr               , "lep2_wfr/F"               );
    tree.Branch(Form("%slep2_nearbjet_dr"       , prefix_.c_str()), &lep2_nearbjet_dr       , "lep2_nearbjet_dr/F"       );
    tree.Branch(Form("%slep2_nearjet_dr"        , prefix_.c_str()), &lep2_nearjet_dr        , "lep2_nearjet_dr/F"        );
    tree.Branch(Form("%slep2_nearlep_dr"        , prefix_.c_str()), &lep2_nearlep_dr        , "lep2_nearlep_dr/F"        );
    tree.Branch(Form("%slep2_nearlep_id"        , prefix_.c_str()), &lep2_nearlep_id        , "lep2_nearlep_id/I"        );
    tree.Branch(Form("%slep2_passes_id_bitmask" , prefix_.c_str()), &lep2_passes_id_bitmask , "lep2_passes_id_bitmask/I" );
    tree.Branch(Form("%slep3_nearbjet_p4"       , prefix_.c_str()), "LorentzVector"         , &lep3_nearbjet_p4          );
    tree.Branch(Form("%slep3_nearjet_p4"        , prefix_.c_str()), "LorentzVector"         , &lep3_nearjet_p4           );
    tree.Branch(Form("%slep3_nearlep_p4"        , prefix_.c_str()), "LorentzVector"         , &lep3_nearlep_p4           );
    tree.Branch(Form("%slep3_wfr"               , prefix_.c_str()), &lep3_wfr               , "lep3_wfr/F"               );
    tree.Branch(Form("%slep3_nearbjet_dr"       , prefix_.c_str()), &lep3_nearbjet_dr       , "lep3_nearbjet_dr/F"       );
    tree.Branch(Form("%slep3_nearjet_dr"        , prefix_.c_str()), &lep3_nearjet_dr        , "lep3_nearjet_dr/F"        );
    tree.Branch(Form("%slep3_nearlep_dr"        , prefix_.c_str()), &lep3_nearlep_dr        , "lep3_nearlep_dr/F"        );
    tree.Branch(Form("%slep3_nearlep_id"        , prefix_.c_str()), &lep3_nearlep_id        , "lep3_nearlep_id/I"        );
    tree.Branch(Form("%slep3_passes_id_bitmask" , prefix_.c_str()), &lep3_passes_id_bitmask , "lep3_passes_id_bitmask/I" );
    tree.Branch(Form("%sis_gen_z"               , prefix_.c_str()), &is_gen_z               , "is_gen_z/O"               );
    tree.Branch(Form("%sis_gen_w"               , prefix_.c_str()), &is_gen_w               , "is_gen_w/O"               );
    tree.Branch(Form("%sgen_nbtags"             , prefix_.c_str()), &gen_nbtags             , "gen_nbtags/I"             );
    tree.Branch(Form("%sgen_njets"              , prefix_.c_str()), &gen_njets              , "gen_njets/I"              );
    tree.Branch(Form("%sgen_ht"                 , prefix_.c_str()), &gen_ht                 , "gen_ht/F"                 );
    tree.Branch(Form("%sgen_nleps"              , prefix_.c_str()), &gen_nleps              , "gen_nleps/F"              );
    tree.Branch(Form("%ssf_nbtag"               , prefix_.c_str()), &sf_nbtag               , "sf_nbtag/F"               );
    tree.Branch(Form("%ssf_nbtag2"              , prefix_.c_str()), &sf_nbtag2              , "sf_nbtag2/F"              );
    tree.Branch(Form("%ssf_unc_nbtag"           , prefix_.c_str()), &sf_unc_nbtag           , "sf_unc_nbtag/F"           );
    tree.Branch(Form("%ssf_unc_nbtag2"          , prefix_.c_str()), &sf_unc_nbtag2          , "sf_unc_nbtag2/F"          );
    tree.Branch(Form("%sbjets_dr12"             , prefix_.c_str()), &bjets_dr12             , "bjets_dr12/F"             );
    tree.Branch(Form("%svgenb_p4"               , prefix_.c_str()), "vecLorentzVector"      , &vgenb_p4                  );
    tree.Branch(Form("%svjets_p4"               , prefix_.c_str()), "vecLorentzVector"      , &vjets_p4                  );
    tree.Branch(Form("%svgenjets_p4"            , prefix_.c_str()), "vecLorentzVector"      , &vgenjets_p4               );
    tree.Branch(Form("%svbjets_p4"              , prefix_.c_str()), "vecLorentzVector"      , &vbjets_p4                 );
    tree.Branch(Form("%svbtags_loose"           , prefix_.c_str()), "std::vector<bool>"     , &vbtags_loose              );
    tree.Branch(Form("%svbtags_tight"           , prefix_.c_str()), "std::vector<bool>"     , &vbtags_tight              );
    tree.Branch(Form("%svbjets_disc"            , prefix_.c_str()), "vecd"                  , &vbjets_disc               );
    tree.Branch(Form("%sgen_lep1_p4"            , prefix_.c_str()), "LorentzVector"         , &gen_lep1_p4               );
    tree.Branch(Form("%sgen_lep1_pdgid"         , prefix_.c_str()), &gen_lep1_pdgid         , "gen_lep1_pdgid/I"         );
    tree.Branch(Form("%sgen_lep2_p4"            , prefix_.c_str()), "LorentzVector"         , &gen_lep2_p4               );
    tree.Branch(Form("%sgen_lep2_pdgid"         , prefix_.c_str()), &gen_lep2_pdgid         , "gen_lep2_pdgid/I"         );
    tree.Branch(Form("%sgen_lep3_p4"            , prefix_.c_str()), "LorentzVector"         , &gen_lep3_p4               );
    tree.Branch(Form("%sgen_mt"                 , prefix_.c_str()), &gen_mt                 , "gen_mt/F"                 );
    tree.Branch(Form("%sgen_lep3_pdgid"         , prefix_.c_str()), &gen_lep3_pdgid         , "gen_lep3_pdgid/I"         );
    tree.Branch(Form("%sgen_dilep_p4"           , prefix_.c_str()), "LorentzVector"         , &gen_dilep_p4              );
    tree.Branch(Form("%sgen_dilep_type"         , prefix_.c_str()), &gen_dilep_type         , "gen_dilep_type/I"         );
    tree.Branch(Form("%sgen_dilep_mass"         , prefix_.c_str()), &gen_dilep_mass         , "gen_dilep_mass/F"         );
    tree.Branch(Form("%sgen_dilep_dphi"         , prefix_.c_str()), &gen_dilep_dphi         , "gen_dilep_dphi/F"         );
    tree.Branch(Form("%sgen_dilep_deta"         , prefix_.c_str()), &gen_dilep_deta         , "gen_dilep_deta/F"         );
    tree.Branch(Form("%sgen_dilep_dr"           , prefix_.c_str()), &gen_dilep_dr           , "gen_dilep_dr/F"           );
    tree.Branch(Form("%slep1_ele_mva_trig"      , prefix_.c_str()), &lep1_ele_mva_trig      , "lep1_ele_mva_trig/F"      );
    tree.Branch(Form("%slep2_ele_mva_trig"      , prefix_.c_str()), &lep2_ele_mva_trig      , "lep2_ele_mva_trig/F"      );
    tree.Branch(Form("%slep3_ele_mva_trig"      , prefix_.c_str()), &lep3_ele_mva_trig      , "lep3_ele_mva_trig/F"      );
    tree.Branch(Form("%slep1_ele_mva_nontrig"   , prefix_.c_str()), &lep1_ele_mva_nontrig   , "lep1_ele_mva_nontrig/F"   );
    tree.Branch(Form("%slep2_ele_mva_nontrig"   , prefix_.c_str()), &lep2_ele_mva_nontrig   , "lep2_ele_mva_nontrig/F"   );
    tree.Branch(Form("%slep3_ele_mva_nontrig"   , prefix_.c_str()), &lep3_ele_mva_nontrig   , "lep3_ele_mva_nontrig/F"   );
}
