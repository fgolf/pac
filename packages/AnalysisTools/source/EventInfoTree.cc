#include "EventInfoTree.h"
#include "CORE/eventSelections.h"
#include "CMS2.h"

using namespace at;

EventInfoTree::EventInfoTree ()
{
}

EventInfoTree::EventInfoTree (const std::string &prefix)
    : prefix_(prefix)
{
}

void EventInfoTree::FillCommon (Sample::value_type sample_)
{
    run          = cms2.evt_run();
    ls           = cms2.evt_lumiBlock();
    evt          = cms2.evt_event();
    sample       = sample_;
    is_real_data = cms2.evt_isRealData();
    nvtxs        = numberOfGoodVertices();
    vtx_idx      = firstGoodVertex();
    pfmet        = cms2.evt_pfmet();
    pfmet_phi    = cms2.evt_pfmetPhi();
    corpfmet     = cms2.evt_pfmet_type1cor();
    corpfmet_phi = cms2.evt_pfmetPhi_type1cor();
    strcpy(dataset, cms2.evt_dataset().at(0).Data());

    if (!cms2.evt_isRealData()) {
        scale1fb    = cms2.evt_scale1fb();
        xsec        = cms2.evt_xsec_incl();
        kfactor     = cms2.evt_kfactor();
        gen_met     = cms2.gen_met();
        gen_met_phi = cms2.gen_metPhi();
    }
}

void EventInfoTree::Reset()
{
    run          = 0;
    ls           = 0;
    evt          = 0;
    is_real_data = false;
    sample       = Sample::static_size;
    nvtxs        = -999999;
    vtx_idx      = -999999;
    pfmet        = -999999.;
    pfmet_phi    = -999999.;
    corpfmet     = -999999.;
    corpfmet_phi = -999999.;
    scale1fb     = 1.;
    xsec         = -999999.;
    kfactor      = -999999.;
    gen_met      = -999999.;
    gen_met_phi  = -999999.;
    memset(dataset, '\0', 200);
}

void EventInfoTree::SetBranches(TTree &tree)
{
    tree.Branch(Form("%srun"          , prefix_.c_str()) , &run          , "run/i"          );
    tree.Branch(Form("%sls"           , prefix_.c_str()) , &ls           , "ls/i"           );
    tree.Branch(Form("%sevt"          , prefix_.c_str()) , &evt          , "evt/i"          );
    tree.Branch(Form("%sis_real_data" , prefix_.c_str()) , &is_real_data , "is_real_data/O" );
    tree.Branch(Form("%ssample"       , prefix_.c_str()) , &sample       , "sample/I"       );
    tree.Branch(Form("%snvtxs"        , prefix_.c_str()) , &nvtxs        , "nvtxs/I"        );
    tree.Branch(Form("%svtx_idx"      , prefix_.c_str()) , &vtx_idx      , "vtx_idx/I"      );
    tree.Branch(Form("%spfmet"        , prefix_.c_str()) , &pfmet        , "pfmet/F"        );
    tree.Branch(Form("%spfmet_phi"    , prefix_.c_str()) , &pfmet_phi    , "pfmet_phi/F"    );
    tree.Branch(Form("%scorpfmet"     , prefix_.c_str()) , &corpfmet     , "corpfmet/F"     );
    tree.Branch(Form("%scorpfmet_phi" , prefix_.c_str()) , &corpfmet_phi , "corpfmet_phi/F" );
    tree.Branch(Form("%sscale1fb"     , prefix_.c_str()) , &scale1fb     , "scale1fb/F"     );
    tree.Branch(Form("%sxsec"         , prefix_.c_str()) , &xsec         , "xsec/F"         );
    tree.Branch(Form("%skfactor"      , prefix_.c_str()) , &kfactor      , "kfactor/F"      );
    tree.Branch(Form("%sgen_met"      , prefix_.c_str()) , &gen_met      , "gen_met/F"      );
    tree.Branch(Form("%sgen_met_phi"  , prefix_.c_str()) , &gen_met_phi  , "gen_met_phi/F"  );
    tree.Branch(Form("%sdataset"      , prefix_.c_str()) , &dataset      , "dataset[200]/C" );
}

