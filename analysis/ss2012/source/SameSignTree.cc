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

    selection        = 0;
    is_good_lumi     = false;
    njets            = -999999;
    njets20          = -999999;
    njets30          = -999999;
    nbtags           = -999999;
    nbtags20         = -999999;
    nbtags30         = -999999;
    vtxw             = -999999.0;
    ht               = -999999.0;
    ht20             = -999999.0;
    ht30             = -999999.0;
    rho              = -999999.0;
    rho_iso          = -999999.0;
	sf_trig			 = 1.0;
	sf_lepeff		 = 1.0;
    trig_mm          = false;
    trig_em          = false;
    trig_ee          = false;
    sparm0           = -999999.0;
    sparm1           = -999999.0;
    sparm2           = -999999.0;
    sparm3           = -999999.0;
    is_pp            = false;
    is_mm            = false;
    is_ss            = false;
    is_sf            = false;
    is_df            = false;
    is_os            = false;
    is_gen_pp        = false;
    is_gen_mm        = false;
    no_extraz        = false;
    gen_nbtags       = -999999;
    gen_njets        = -999999;
    gen_ht           = -999999.0;
    lep1_nearbjet_p4 = LorentzVector(0, 0, 0, 0);
    lep1_nearjet_p4  = LorentzVector(0, 0, 0, 0);
    lep1_wfr         = -999999.0;
    lep1_wflip       = -999999.0;
    lep1_nearbjet_dr = -999999.0;
    lep1_nearjet_dr  = -999999.0;
    lep2_nearbjet_p4 = LorentzVector(0, 0, 0, 0);
    lep2_nearjet_p4  = LorentzVector(0, 0, 0, 0);
    lep2_wfr         = -999999.0;
    lep2_wflip       = -999999.0;
    lep2_nearbjet_dr = -999999.0;
    lep2_nearjet_dr  = -999999.0;
    sf_nbtag         = -999999.0;
    sf_nbtag3        = -999999.0;
    sf_unc_nbtag     = -999999.0;
    sf_unc_nbtag3    = -999999.0;
    jets_dr12        = -999999.0;
    bjets_dr12       = -999999.0;

    vgenb_p4.clear();
    vjets_p4.clear();
    vgenjets_p4.clear();
    vjets_nearjet_p4.clear();
    vbjets_p4.clear();
    vbjets_nearjet_p4.clear();
    vbtags.clear();
    vbjets_nearjet_dr.clear();
}
void SameSignTree::SetBranches(TTree &tree)
{
    event_info.SetBranches(tree);
    DileptonTree::SetBranches(tree);

    tree.Branch(Form("%sselection"         , prefix_.c_str()) , &selection                  , "selection/i"        );
    tree.Branch(Form("%sis_good_lumi"      , prefix_.c_str()) , &is_good_lumi               , "is_good_lumi/O"     );
    tree.Branch(Form("%snjets"             , prefix_.c_str()) , &njets                      , "njets/I"            );
    tree.Branch(Form("%snjets20"           , prefix_.c_str()) , &njets20                    , "njets20/I"          );
    tree.Branch(Form("%snjets30"           , prefix_.c_str()) , &njets30                    , "njets30/I"          );
    tree.Branch(Form("%snbtags"            , prefix_.c_str()) , &nbtags                     , "nbtags/I"           );
    tree.Branch(Form("%snbtags20"          , prefix_.c_str()) , &nbtags20                   , "nbtags20/I"         );
    tree.Branch(Form("%snbtags30"          , prefix_.c_str()) , &nbtags30                   , "nbtags30/I"         );
    tree.Branch(Form("%svtxw"              , prefix_.c_str()) , &vtxw                       , "vtxw/F"             );
    tree.Branch(Form("%sht"                , prefix_.c_str()) , &ht                         , "ht/F"               );
    tree.Branch(Form("%sht20"              , prefix_.c_str()) , &ht20                       , "ht20/F"             );
    tree.Branch(Form("%sht30"              , prefix_.c_str()) , &ht30                       , "ht30/F"             );
    tree.Branch(Form("%srho"               , prefix_.c_str()) , &rho                        , "rho/F"              );
    tree.Branch(Form("%srho_iso"           , prefix_.c_str()) , &rho_iso                    , "rho_iso/F"          );
    tree.Branch(Form("%strig_mm"           , prefix_.c_str()) , &trig_mm                    , "trig_mm/O"          );
    tree.Branch(Form("%strig_em"           , prefix_.c_str()) , &trig_em                    , "trig_em/O"          );
    tree.Branch(Form("%strig_ee"           , prefix_.c_str()) , &trig_ee                    , "trig_ee/O"          );
    tree.Branch(Form("%ssf_trig"           , prefix_.c_str()) , &sf_trig                    , "sf_trig/F"          );
    tree.Branch(Form("%ssf_lepeff"         , prefix_.c_str()) , &sf_lepeff                  , "sf_lepeff/F"        );
    tree.Branch(Form("%ssparm0"            , prefix_.c_str()) , &sparm0                     , "sparm0/F"           );
    tree.Branch(Form("%ssparm1"            , prefix_.c_str()) , &sparm1                     , "sparm1/F"           );
    tree.Branch(Form("%ssparm2"            , prefix_.c_str()) , &sparm2                     , "sparm2/F"           );
    tree.Branch(Form("%ssparm3"            , prefix_.c_str()) , &sparm3                     , "sparm3/F"           );
    tree.Branch(Form("%sis_pp"             , prefix_.c_str()) , &is_pp                      , "is_pp/O"            );
    tree.Branch(Form("%sis_mm"             , prefix_.c_str()) , &is_mm                      , "is_mm/O"            );
    tree.Branch(Form("%sis_sf"             , prefix_.c_str()) , &is_sf                      , "is_sf/O"            );
    tree.Branch(Form("%sis_df"             , prefix_.c_str()) , &is_df                      , "is_df/O"            );
    tree.Branch(Form("%sno_extraz"         , prefix_.c_str()) , &no_extraz                  , "no_extraz/O"        );
    tree.Branch(Form("%sis_gen_pp"         , prefix_.c_str()) , &is_gen_pp                  , "is_gen_pp/O"        );
    tree.Branch(Form("%sis_gen_mm"         , prefix_.c_str()) , &is_gen_mm                  , "is_gen_mm/O"        );
    tree.Branch(Form("%sgen_nbtags"        , prefix_.c_str()) , &gen_nbtags                 , "gen_nbtags/I"       );
    tree.Branch(Form("%sgen_njets"         , prefix_.c_str()) , &gen_njets                  , "gen_njets/I"        );
    tree.Branch(Form("%sgen_ht"            , prefix_.c_str()) , &gen_ht                     , "gen_ht/F"           );
    tree.Branch(Form("%slep1_nearbjet_p4"  , prefix_.c_str()) , "LorentzVector"             , &lep1_nearbjet_p4    );
    tree.Branch(Form("%slep1_nearjet_p4"   , prefix_.c_str()) , "LorentzVector"             , &lep1_nearjet_p4     );
    tree.Branch(Form("%slep1_wfr"          , prefix_.c_str()) , &lep1_wfr                   , "lep1_wfr/F"         );
    tree.Branch(Form("%slep1_wflip"        , prefix_.c_str()) , &lep1_wflip                 , "lep1_wflip/F"       );
    tree.Branch(Form("%slep1_nearbjet_dr"  , prefix_.c_str()) , &lep1_nearbjet_dr           , "lep1_nearbjet_dr/F" );
    tree.Branch(Form("%slep1_nearjet_dr"   , prefix_.c_str()) , &lep1_nearjet_dr            , "lep1_nearjet_dr/F"  );
    tree.Branch(Form("%slep2_nearbjet_p4"  , prefix_.c_str()) , "LorentzVector"             , &lep2_nearbjet_p4    );
    tree.Branch(Form("%slep2_nearjet_p4"   , prefix_.c_str()) , "LorentzVector"             , &lep2_nearjet_p4     );
    tree.Branch(Form("%slep2_wfr"          , prefix_.c_str()) , &lep2_wfr                   , "lep2_wfr/F"         );
    tree.Branch(Form("%slep2_wflip"        , prefix_.c_str()) , &lep2_wflip                 , "lep2_wflip/F"       );
    tree.Branch(Form("%slep2_nearbjet_dr"  , prefix_.c_str()) , &lep2_nearbjet_dr           , "lep2_nearbjet_dr/F" );
    tree.Branch(Form("%slep2_nearjet_dr"   , prefix_.c_str()) , &lep2_nearjet_dr            , "lep2_nearjet_dr/F"  );
    tree.Branch(Form("%ssf_nbtag"          , prefix_.c_str()) , &sf_nbtag                   , "sf_nbtag/F"         );
    tree.Branch(Form("%ssf_nbtag3"         , prefix_.c_str()) , &sf_nbtag3                  , "sf_nbtag3/F"        );
    tree.Branch(Form("%ssf_unc_nbtag"      , prefix_.c_str()) , &sf_unc_nbtag               , "sf_unc_nbtag/F"     );
    tree.Branch(Form("%ssf_unc_nbtag3"     , prefix_.c_str()) , &sf_unc_nbtag3              , "sf_unc_nbtag3/F"    );
    tree.Branch(Form("%sjets_dr12"         , prefix_.c_str()) , &jets_dr12                  , "jets_dr12/F"        );
    tree.Branch(Form("%sbjets_dr12"        , prefix_.c_str()) , &bjets_dr12                 , "bjets_dr12/F"       );
    tree.Branch(Form("%svgenb_p4"          , prefix_.c_str()) , "vecLorentzVector"          , &vgenb_p4            );
    tree.Branch(Form("%svjets_p4"          , prefix_.c_str()) , "vecLorentzVector"          , &vjets_p4            );
    tree.Branch(Form("%svgenjets_p4"       , prefix_.c_str()) , "vecLorentzVector"          , &vgenjets_p4         );
    tree.Branch(Form("%svjets_nearjet_p4"  , prefix_.c_str()) , "vecLorentzVector"          , &vjets_nearjet_p4    );
    tree.Branch(Form("%svbjets_p4"         , prefix_.c_str()) , "vecLorentzVector"          , &vbjets_p4           );
    tree.Branch(Form("%svbjets_nearjet_p4" , prefix_.c_str()) , "vecLorentzVector"          , &vbjets_nearjet_p4   );
    tree.Branch(Form("%svbtags"            , prefix_.c_str()) , "std::vector<bool>"         , &vbtags              );
    tree.Branch(Form("%svbjets_nearjet_dr" , prefix_.c_str()) , "vecd"                      , &vbjets_nearjet_dr   );
}

