#include "SingleLeptonTree.h"
#include "CMS2.h"
#include "CORE/eventSelections.h"
#include "CORE/electronSelections.h"
#include "CORE/muonSelections.h"
#include "CORE/mcSelections.h"
#include "CORE/eventSelections.h"
#include "CORE/trackSelections.h"
#include <algorithm>
#include <cmath>
#include "Math/GenVector/PtEtaPhiE4D.h"

SingleLeptonTree::SingleLeptonTree ()
{
}

SingleLeptonTree::SingleLeptonTree (const std::string &prefix)
  : prefix_(prefix)
{
}

//********************************************************//
//
// NOTE: This function only fills information that is
//       expected to be common to all analyses.
//
// The following information will need to be filled
// by the user for his specific analysis:
//
//      bool passes_id;
//      bool passes_iso;
//      bool is_num;
//      bool is_den;
//      bool is_fo;
//      float corpfiso, cordetiso, corpfiso04, cordetiso04;
//      float effarea, effarea04;
//      float sf_lepeff; (t&p scale factor)
//      float sf_trig; (trigger scale factor)
//      bool is_conv;
//      
//********************************************************//

void SingleLeptonTree::FillCommon (int id, int idx)
{
    if (idx < 0) return;

    int vtxidx = firstGoodVertex();
	is_fromw = not cms2.evt_isRealData() ? leptonIsFromW(idx, id, true) : -999999;

    if (abs(id) == 11)
    {
        p4     = cms2.els_p4().at(idx);
        charge = cms2.els_charge().at(idx);
        pdgid  = charge * -11;
        type   = cms2.els_type().at(idx);

        int gsfidx = cms2.els_gsftrkidx().at(idx);
        if (gsfidx >= 0 && vtxidx >= 0) {
            std::pair<float, float> cord0 = gsftrks_d0_pv(gsfidx, vtxidx);
            std::pair<float, float> cordz = gsftrks_dz_pv(gsfidx, vtxidx);
            d0 = cord0.first;
            dz = cordz.first;
            d0err = cord0.second;
            dzerr = cordz.second;
        }
		ip3d    = cms2.els_ip3d().at(idx);;
		ip3derr = cms2.els_ip3derr().at(idx);;

        if (!cms2.evt_isRealData()) {
            mcp4      = cms2.els_mc_p4().at(idx);
            mc_momp4  = cms2.els_mc_motherp4().at(idx);
            mcid      = cms2.els_mc_id().at(idx);
            momid     = cms2.els_mc_motherid().at(idx);
            mc3id     = cms2.els_mc3_id().at(idx);
            mc3_momid = cms2.els_mc3_motherid().at(idx);

            int mc3idx = cms2.els_mc3idx().at(idx);
            if (mc3idx >= 0) {
                mc3p4     = cms2.genps_p4().at(mc3idx);           
            }
        }

        gsf_p4 = cms2.els_trk_p4().at(idx);
        
        int ctfidx = cms2.els_trkidx().at(idx);
        if (ctfidx >= 0) {
            ctf_p4 = cms2.trks_trk_p4().at(ctfidx);
            qctf   = cms2.trks_charge().at(ctfidx);
        }
        
        float tmp_eta = cms2.els_etaSC().at(idx);
        float tmp_phi = cms2.els_phiSC().at(idx);
        float tmp_e   = cms2.els_eSC().at(idx);
        float tmp_pt  = tmp_e / cosh(tmp_eta);
        ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<float> > tmp_scp4(tmp_pt, tmp_eta, tmp_phi, tmp_e);
        sc_p4 = tmp_scp4;

        q3agree      = !isChargeFlip3agree(idx);
        qgsf         = cms2.els_trk_charge().at(idx);
        qsc          = cms2.els_sccharge().at(idx);
        nmhits       = cms2.els_exp_innerlayers().at(idx);
        eleid_veto   = cms2.els_id2012_veto().at(idx);
        eleid_loose  = cms2.els_id2012_loose().at(idx);
        eleid_medium = cms2.els_id2012_medium().at(idx);
        eleid_tight  = cms2.els_id2012_tight().at(idx);
        dphiin       = cms2.els_dPhiIn().at(idx);
        detain       = cms2.els_dEtaIn().at(idx);
        hoe          = cms2.els_hOverE().at(idx);
        sieie        = cms2.els_sigmaIEtaIEta().at(idx);
        ooemoop      = fabs( (1.0/cms2.els_ecalEnergy().at(idx)) - (cms2.els_eOverPIn().at(idx)/cms2.els_ecalEnergy().at(idx)) );
        conv_dist    = cms2.els_conv_dist().at(idx);
        conv_dcot    = cms2.els_conv_dcot().at(idx);

        trkiso  = cms2.els_tkIso().at(idx);
        ecaliso = cms2.els_ecalIso().at(idx);
        hcaliso = cms2.els_hcalIso().at(idx);
        detiso  = electronIsolation_rel_v1(idx, true);

        trkiso04  = cms2.els_tkIso04().at(idx);
        ecaliso04 = cms2.els_ecalIso04().at(idx);
        hcaliso04 = cms2.els_hcalIso04().at(idx);
        detiso04  = trkiso04 + hcaliso04 + ecaliso04;
        if (fabs(sc_p4.eta()) >= 1.479) detiso += cms2.els_ecalIso04().at(idx);
        else detiso += std::max(cms2.els_ecalIso04().at(idx) - 1., 0.0);
        detiso /= p4.pt();
        
        if (vtxidx >= 0) {
            electronIsoValuePF2012(chiso, emiso, nhiso, 0.3, idx, vtxidx);
            pfiso = (chiso + emiso + nhiso) / p4.pt();

            electronIsoValuePF2012(chiso04, emiso04, nhiso04, 0.4, idx, vtxidx);
            pfiso04 = (chiso04 + emiso04 + nhiso04) / p4.pt();
        }

    } // end electron block
    if (abs(id) == 13)
    {
        p4 = cms2.mus_p4().at(idx);
        charge = cms2.mus_charge().at(idx);
        pdgid = charge * -13;
        type = cms2.mus_type().at(idx);

        
        int trkidx = cms2.mus_trkidx().at(idx);
        if (trkidx >= 0 && vtxidx >= 0) {
            std::pair<float, float> cord0 = trks_d0_pv(trkidx, vtxidx);
            std::pair<float, float> cordz = trks_dz_pv(trkidx, vtxidx);
            d0 = cord0.first;
            dz = cordz.first;
            d0err = cord0.second;
            dzerr = cordz.second;
        }
		ip3d    = cms2.mus_ip3d().at(idx);;
		ip3derr = cms2.mus_ip3derr().at(idx);;

        if (!cms2.evt_isRealData()) {
            mcp4      = cms2.mus_mc_p4().at(idx);
            mc_momp4  = cms2.mus_mc_motherp4().at(idx);
            mcid      = cms2.mus_mc_id().at(idx);
            momid     = cms2.mus_mc_motherid().at(idx);
            mc3id     = cms2.mus_mc3_id().at(idx);
            mc3_momid = cms2.mus_mc3_motherid().at(idx);

            int mc3idx = cms2.mus_mc3idx().at(idx);
            if (mc3idx >= 0) {
                mc3p4     = cms2.genps_p4().at(mc3idx);
            }
        }

        gfit_p4    = cms2.mus_gfit_p4().at(idx);
        is_global  = ((cms2.mus_type().at(idx) & (1<<1)) != 0);
        is_tracker = ((cms2.mus_type().at(idx) & (1<<2)) != 0);
        is_stamu   = ((cms2.mus_type().at(idx) & (1<<3)) != 0);
        is_pfmu    = ((cms2.mus_type().at(idx) & (1<<5)) != 0);

        nsihits      = cms2.mus_validHits().at(idx);
        nstahits     = cms2.mus_gfit_validSTAHits().at(idx);
        nstations    = cms2.mus_numberOfMatchedStations().at(idx);
        chi2         = cms2.mus_gfit_chi2().at(idx);
        ndof         = cms2.mus_gfit_ndof().at(idx);
        pterr        = cms2.mus_ptErr().at(idx);
        ecal_vetodep = cms2.mus_iso_ecalvetoDep().at(idx);
        hcal_vetodep = cms2.mus_iso_hcalvetoDep().at(idx);

        int ctfidx = cms2.mus_trkidx().at(idx);
        if (ctfidx >= 0) {
            npixelhits = cms2.trks_valid_pixelhits().at(ctfidx);
            nsilayers  = cms2.trks_nlayers().at(ctfidx);            
        }

        if (vtxidx >= 0) {
            is_loosemu = passes_muid_wp2012(idx, mu2012_tightness::LOOSE);
            is_tightmu = passes_muid_wp2012(idx, mu2012_tightness::TIGHT);
        }

        trkiso  = cms2.mus_iso03_sumPt().at(idx);
        ecaliso = cms2.mus_iso03_emEt().at(idx);
        hcaliso = cms2.mus_iso03_hadEt().at(idx);
        detiso  = muonIsoValue(idx, false);

        chiso = cms2.mus_isoR03_pf_ChargedHadronPt().at(idx);
        emiso = cms2.mus_isoR03_pf_PhotonEt().at(idx);
        nhiso = cms2.mus_isoR03_pf_NeutralHadronEt().at(idx);
        pfiso = (chiso + emiso + nhiso) / p4.pt();
        dbeta = cms2.mus_isoR03_pf_PUPt().at(idx);

        chiso04 = cms2.mus_isoR04_pf_ChargedHadronPt().at(idx);
        emiso04 = cms2.mus_isoR04_pf_PhotonEt().at(idx);
        nhiso04 = cms2.mus_isoR04_pf_NeutralHadronEt().at(idx);
        pfiso04 = (chiso04 + emiso04 + nhiso04) / p4.pt();        
        dbeta04 = cms2.mus_isoR04_pf_PUPt().at(idx);

    } // end muon block

}

void SingleLeptonTree::Reset()
{
    passes_id    = false;
    passes_iso   = false;
    is_num       = false;
    is_den       = false;
    is_fo        = false;
    is_fromw     = -999999;
    charge       = -999999;
    pdgid        = -999999;
    type         = -999999;
    d0           = -999999.;
    d0err        = -999999.;
    dz           = -999999.;
    dzerr        = -999999.;
    mt           = -999999.;
    corpfiso     = -999999.;
    pfiso        = -999999.;
    chiso        = -999999.;
    emiso        = -999999.;
    nhiso        = -999999.;
    corpfiso04   = -999999.;
    pfiso04      = -999999.;
    chiso04      = -999999.;
    emiso04      = -999999.;
    nhiso04      = -999999.;
    cordetiso    = -999999.;
    detiso       = -999999.;
    trkiso       = -999999.;
    ecaliso      = -999999.;
    hcaliso      = -999999.;
    cordetiso04  = -999999.;
    detiso04     = -999999.;
    trkiso04     = -999999.;
    ecaliso04    = -999999.;
    hcaliso04    = -999999.;
    effarea      = -999999.;
    effarea04    = -999999.;
    dbeta        = -999999.;
    dbeta04      = -999999.;
    sf_lepeff    = -999999.;
    sf_trig      = -999999.;
    mcid         = -999999;
    mc3id        = -999999;
    momid        = -999999;
    mc3_momid    = -999999;
    q3agree      = false;
    is_conv      = false;
    qsc          = -999999;
    qctf         = -999999;
    qgsf         = -999999;
    nmhits       = -999999;
    eleid_veto   = -999999;
    eleid_loose  = -999999;
    eleid_medium = -999999;
    eleid_tight  = -999999;
    dphiin       = -999999.;
    detain       = -999999.;
    sieie        = -999999.;
    hoe          = -999999.;
    ooemoop      = -999999.;
    conv_dist    = -999999.;
    conv_dcot    = -999999.;
    is_global    = false;
    is_tracker   = false;
    is_stamu     = false;
    is_pfmu      = false;
    is_loosemu   = false;
    is_tightmu   = false;
    npixelhits   = -999999;
    nsihits      = -999999;
    nsilayers    = -999999;
    nstahits     = -999999;
    nstations    = -999999;
    chi2         = -999999.;
    ndof         = -999999.;
    pterr        = -999999.;
    ecal_vetodep = -999999.;
    hcal_vetodep = -999999.;

    p4           = LorentzVector(0, 0, 0, 0);
    mcp4         = LorentzVector(0, 0, 0, 0);
    mc3p4        = LorentzVector(0, 0, 0, 0);
    mc_momp4     = LorentzVector(0, 0, 0, 0);
    gsf_p4       = LorentzVector(0, 0, 0, 0);
    ctf_p4       = LorentzVector(0, 0, 0, 0);
    sc_p4        = LorentzVector(0, 0, 0, 0);
    gfit_p4      = LorentzVector(0, 0, 0, 0);
}

void SingleLeptonTree::SetBranches(TTree &tree)
{
    tree.Branch(Form("%spasses_id"    , prefix_.c_str()) , &passes_id      );
    tree.Branch(Form("%spasses_iso"   , prefix_.c_str()) , &passes_iso     );
    tree.Branch(Form("%sis_num"       , prefix_.c_str()) , &is_num         );
    tree.Branch(Form("%sis_den"       , prefix_.c_str()) , &is_den         );
    tree.Branch(Form("%sis_fo"        , prefix_.c_str()) , &is_fo          );
    tree.Branch(Form("%sis_fromw"     , prefix_.c_str()) , &is_fromw       );
    tree.Branch(Form("%scharge"       , prefix_.c_str()) , &charge         );
    tree.Branch(Form("%spdgid"        , prefix_.c_str()) , &pdgid          );
    tree.Branch(Form("%stype"         , prefix_.c_str()) , &type           );
    tree.Branch(Form("%sd0"           , prefix_.c_str()) , &d0             );
    tree.Branch(Form("%sd0err"        , prefix_.c_str()) , &d0err          );
    tree.Branch(Form("%sdz"           , prefix_.c_str()) , &dz             );
    tree.Branch(Form("%sip3d"         , prefix_.c_str()) , &ip3d           );
    tree.Branch(Form("%sip3derr"      , prefix_.c_str()) , &ip3derr        );
    tree.Branch(Form("%sdzerr"        , prefix_.c_str()) , &dzerr          );
    tree.Branch(Form("%smt"           , prefix_.c_str()) , &mt             );
    tree.Branch(Form("%scorpfiso"     , prefix_.c_str()) , &corpfiso       );
    tree.Branch(Form("%spfiso"        , prefix_.c_str()) , &pfiso          );
    tree.Branch(Form("%schiso"        , prefix_.c_str()) , &chiso          );
    tree.Branch(Form("%semiso"        , prefix_.c_str()) , &emiso          );
    tree.Branch(Form("%snhiso"        , prefix_.c_str()) , &nhiso          );
    tree.Branch(Form("%scorpfiso04"   , prefix_.c_str()) , &corpfiso04     );
    tree.Branch(Form("%spfiso04"      , prefix_.c_str()) , &pfiso04        );
    tree.Branch(Form("%schiso04"      , prefix_.c_str()) , &chiso04        );
    tree.Branch(Form("%semiso04"      , prefix_.c_str()) , &emiso04        );
    tree.Branch(Form("%snhiso04"      , prefix_.c_str()) , &nhiso04        );
    tree.Branch(Form("%scordetiso"    , prefix_.c_str()) , &cordetiso      );
    tree.Branch(Form("%sdetiso"       , prefix_.c_str()) , &detiso         );
    tree.Branch(Form("%strkiso"       , prefix_.c_str()) , &trkiso         );
    tree.Branch(Form("%secaliso"      , prefix_.c_str()) , &ecaliso        );
    tree.Branch(Form("%shcaliso"      , prefix_.c_str()) , &hcaliso        );
    tree.Branch(Form("%scordetiso04"  , prefix_.c_str()) , &cordetiso04    );
    tree.Branch(Form("%sdetiso04"     , prefix_.c_str()) , &detiso04       );
    tree.Branch(Form("%strkiso04"     , prefix_.c_str()) , &trkiso04       );
    tree.Branch(Form("%secaliso04"    , prefix_.c_str()) , &ecaliso04      );
    tree.Branch(Form("%shcaliso04"    , prefix_.c_str()) , &hcaliso04      );
    tree.Branch(Form("%seffarea"      , prefix_.c_str()) , &effarea        );
    tree.Branch(Form("%seffarea04"    , prefix_.c_str()) , &effarea04      );
    tree.Branch(Form("%sdbeta"        , prefix_.c_str()) , &dbeta          );
    tree.Branch(Form("%sdbeta04"      , prefix_.c_str()) , &dbeta04        );
    tree.Branch(Form("%ssf_lepeff"    , prefix_.c_str()) , &sf_lepeff      );
    tree.Branch(Form("%ssf_trig"      , prefix_.c_str()) , &sf_trig        );
    tree.Branch(Form("%smcid"         , prefix_.c_str()) , &mcid           );
    tree.Branch(Form("%smc3id"        , prefix_.c_str()) , &mc3id          );
    tree.Branch(Form("%smomid"        , prefix_.c_str()) , &momid          );
    tree.Branch(Form("%smc3_momid"    , prefix_.c_str()) , &mc3_momid      );
    tree.Branch(Form("%sq3agree"      , prefix_.c_str()) , &q3agree        );
    tree.Branch(Form("%sis_conv"      , prefix_.c_str()) , &is_conv        );
    tree.Branch(Form("%sqsc"          , prefix_.c_str()) , &qsc            );
    tree.Branch(Form("%sqctf"         , prefix_.c_str()) , &qctf           );
    tree.Branch(Form("%sqgsf"         , prefix_.c_str()) , &qgsf           );
    tree.Branch(Form("%snmhits"       , prefix_.c_str()) , &nmhits         );
    tree.Branch(Form("%seleid_veto"   , prefix_.c_str()) , &eleid_veto     );
    tree.Branch(Form("%seleid_loose"  , prefix_.c_str()) , &eleid_loose    );
    tree.Branch(Form("%seleid_medium" , prefix_.c_str()) , &eleid_medium   );
    tree.Branch(Form("%seleid_tight"  , prefix_.c_str()) , &eleid_tight    );
    tree.Branch(Form("%sdphiin"       , prefix_.c_str()) , &dphiin         );
    tree.Branch(Form("%sdetain"       , prefix_.c_str()) , &detain         );
    tree.Branch(Form("%ssieie"        , prefix_.c_str()) , &sieie          );
    tree.Branch(Form("%shoe"          , prefix_.c_str()) , &hoe            );
    tree.Branch(Form("%sooemoop"      , prefix_.c_str()) , &ooemoop        );
    tree.Branch(Form("%sconv_dist"    , prefix_.c_str()) , &conv_dist      );
    tree.Branch(Form("%sconv_dcot"    , prefix_.c_str()) , &conv_dcot      );
    tree.Branch(Form("%sis_global"    , prefix_.c_str()) , &is_global      );
    tree.Branch(Form("%sis_tracker"   , prefix_.c_str()) , &is_tracker     );
    tree.Branch(Form("%sis_stamu"     , prefix_.c_str()) , &is_stamu       );
    tree.Branch(Form("%sis_pfmu"      , prefix_.c_str()) , &is_pfmu        );
    tree.Branch(Form("%sis_loosemu"   , prefix_.c_str()) , &is_loosemu     );
    tree.Branch(Form("%sis_tightmu"   , prefix_.c_str()) , &is_tightmu     );
    tree.Branch(Form("%snpixelhits"   , prefix_.c_str()) , &npixelhits     );
    tree.Branch(Form("%snsihits"      , prefix_.c_str()) , &nsihits        );
    tree.Branch(Form("%snsilayers"    , prefix_.c_str()) , &nsilayers      );
    tree.Branch(Form("%snstahits"     , prefix_.c_str()) , &nstahits       );
    tree.Branch(Form("%snstations"    , prefix_.c_str()) , &nstations      );
    tree.Branch(Form("%schi2"         , prefix_.c_str()) , &chi2           );
    tree.Branch(Form("%sndof"         , prefix_.c_str()) , &ndof           );
    tree.Branch(Form("%spterr"        , prefix_.c_str()) , &pterr          );
    tree.Branch(Form("%secal_vetodep" , prefix_.c_str()) , &ecal_vetodep   );
    tree.Branch(Form("%shcal_vetodep" , prefix_.c_str()) , &hcal_vetodep   );

    tree.Branch(Form("%sp4"      , prefix_.c_str()) , "LorentzVector" , &p4      );
    tree.Branch(Form("%smcp4"    , prefix_.c_str()) , "LorentzVector" , &mcp4    );
    tree.Branch(Form("%smc3p4"   , prefix_.c_str()) , "LorentzVector" , &mc3p4   );
    tree.Branch(Form("%smc_momp4", prefix_.c_str()) , "LorentzVector" , &mc_momp4);
    tree.Branch(Form("%sgsf_p4"  , prefix_.c_str()) , "LorentzVector" , &gsf_p4  );
    tree.Branch(Form("%sctf_p4"  , prefix_.c_str()) , "LorentzVector" , &ctf_p4  );
    tree.Branch(Form("%ssc_p4"   , prefix_.c_str()) , "LorentzVector" , &sc_p4   );
    tree.Branch(Form("%sgfit_p4" , prefix_.c_str()) , "LorentzVector" , &gfit_p4 );
}
