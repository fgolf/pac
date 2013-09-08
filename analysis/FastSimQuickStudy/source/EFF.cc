
#include "EFF.h"
#include <iostream>

// global object
EFF eff_obj;

// implementation of EFF
// ---------------------------------------------------------------------------------------------- //

EFF::EFF()
    : run_handle("run")
    , ls_handle("ls")
    , evt_handle("evt")
    , is_real_data_handle("is_real_data")
    , sample_handle("sample")
    , nvtxs_handle("nvtxs")
    , vtx_idx_handle("vtx_idx")
    , pfmet_handle("pfmet")
    , pfmet_phi_handle("pfmet_phi")
    , uncorpfmet_handle("uncorpfmet")
    , uncorpfmet_phi_handle("uncorpfmet_phi")
    , pu_nvtxs_handle("pu_nvtxs")
    , pu_ntrueint_handle("pu_ntrueint")
    , scale1fb_handle("scale1fb")
    , xsec_handle("xsec")
    , nevts_handle("nevts")
    , kfactor_handle("kfactor")
    , gen_met_handle("gen_met")
    , gen_met_phi_handle("gen_met_phi")
    , dataset_handle("dataset")
    , filename_handle("filename")
    , gen_nleps_handle("gen_nleps")
    , gen_nels_handle("gen_nels")
    , gen_nmus_handle("gen_nmus")
    , gen_ntaus_handle("gen_ntaus")
    , gen_nleps_with_fromtau_handle("gen_nleps_with_fromtau")
    , gen_nels_with_fromtau_handle("gen_nels_with_fromtau")
    , gen_nmus_with_fromtau_handle("gen_nmus_with_fromtau")
    , gen_ntaus_with_fromtau_handle("gen_ntaus_with_fromtau")
    , filt_csc_handle("filt_csc")
    , filt_hbhe_handle("filt_hbhe")
    , filt_hcallaser_handle("filt_hcallaser")
    , filt_ecallaser_handle("filt_ecallaser")
    , filt_ecaltp_handle("filt_ecaltp")
    , filt_trkfail_handle("filt_trkfail")
    , filt_eebadsc_handle("filt_eebadsc")
    , passes_metfilters_handle("passes_metfilters")
    , passes_id_handle("passes_id")
    , passes_iso_handle("passes_iso")
    , is_num_handle("is_num")
    , is_den_handle("is_den")
    , is_fo_handle("is_fo")
    , is_mu_handle("is_mu")
    , is_el_handle("is_el")
    , exists_handle("exists")
    , is_fromw_handle("is_fromw")
    , charge_handle("charge")
    , pdgid_handle("pdgid")
    , type_handle("type")
    , d0_handle("d0")
    , d0err_handle("d0err")
    , dz_handle("dz")
    , ip3d_handle("ip3d")
    , ip3derr_handle("ip3derr")
    , dzerr_handle("dzerr")
    , mt_handle("mt")
    , corpfiso_handle("corpfiso")
    , pfiso_handle("pfiso")
    , chiso_handle("chiso")
    , emiso_handle("emiso")
    , nhiso_handle("nhiso")
    , corpfiso04_handle("corpfiso04")
    , pfiso04_handle("pfiso04")
    , chiso04_handle("chiso04")
    , emiso04_handle("emiso04")
    , nhiso04_handle("nhiso04")
    , cordetiso_handle("cordetiso")
    , detiso_handle("detiso")
    , trkiso_handle("trkiso")
    , ecaliso_handle("ecaliso")
    , hcaliso_handle("hcaliso")
    , cordetiso04_handle("cordetiso04")
    , detiso04_handle("detiso04")
    , trkiso04_handle("trkiso04")
    , ecaliso04_handle("ecaliso04")
    , hcaliso04_handle("hcaliso04")
    , effarea_handle("effarea")
    , effarea04_handle("effarea04")
    , dbeta_handle("dbeta")
    , dbeta04_handle("dbeta04")
    , sf_lepeff_handle("sf_lepeff")
    , sf_trig_handle("sf_trig")
    , mcid_handle("mcid")
    , mc3id_handle("mc3id")
    , momid_handle("momid")
    , mc3_momid_handle("mc3_momid")
    , q3agree_handle("q3agree")
    , is_conv_handle("is_conv")
    , qsc_handle("qsc")
    , qctf_handle("qctf")
    , qgsf_handle("qgsf")
    , nmhits_handle("nmhits")
    , eleid_veto_handle("eleid_veto")
    , eleid_loose_handle("eleid_loose")
    , eleid_medium_handle("eleid_medium")
    , eleid_tight_handle("eleid_tight")
    , is_eleid_veto_handle("is_eleid_veto")
    , is_eleid_loose_handle("is_eleid_loose")
    , is_eleid_medium_handle("is_eleid_medium")
    , is_eleid_tight_handle("is_eleid_tight")
    , dphiin_handle("dphiin")
    , detain_handle("detain")
    , sieie_handle("sieie")
    , hoe_handle("hoe")
    , ooemoop_handle("ooemoop")
    , conv_dist_handle("conv_dist")
    , conv_dcot_handle("conv_dcot")
    , is_global_handle("is_global")
    , is_tracker_handle("is_tracker")
    , is_stamu_handle("is_stamu")
    , is_pfmu_handle("is_pfmu")
    , is_loosemu_handle("is_loosemu")
    , is_tightmu_handle("is_tightmu")
    , npixelhits_handle("npixelhits")
    , nsihits_handle("nsihits")
    , nsilayers_handle("nsilayers")
    , nstahits_handle("nstahits")
    , nstations_handle("nstations")
    , chi2_handle("chi2")
    , ndof_handle("ndof")
    , pterr_handle("pterr")
    , ecal_vetodep_handle("ecal_vetodep")
    , hcal_vetodep_handle("hcal_vetodep")
    , p4_handle("p4")
    , mcp4_handle("mcp4")
    , mc3p4_handle("mc3p4")
    , mc_momp4_handle("mc_momp4")
    , gsf_p4_handle("gsf_p4")
    , ctf_p4_handle("ctf_p4")
    , sc_p4_handle("sc_p4")
    , gfit_p4_handle("gfit_p4")
{
}

void EFF::Init(TTree& tree)
{
    run_handle.Init(tree);
    ls_handle.Init(tree);
    evt_handle.Init(tree);
    is_real_data_handle.Init(tree);
    sample_handle.Init(tree);
    nvtxs_handle.Init(tree);
    vtx_idx_handle.Init(tree);
    pfmet_handle.Init(tree);
    pfmet_phi_handle.Init(tree);
    uncorpfmet_handle.Init(tree);
    uncorpfmet_phi_handle.Init(tree);
    pu_nvtxs_handle.Init(tree);
    pu_ntrueint_handle.Init(tree);
    scale1fb_handle.Init(tree);
    xsec_handle.Init(tree);
    nevts_handle.Init(tree);
    kfactor_handle.Init(tree);
    gen_met_handle.Init(tree);
    gen_met_phi_handle.Init(tree);
    dataset_handle.Init(tree);
    filename_handle.Init(tree);
    gen_nleps_handle.Init(tree);
    gen_nels_handle.Init(tree);
    gen_nmus_handle.Init(tree);
    gen_ntaus_handle.Init(tree);
    gen_nleps_with_fromtau_handle.Init(tree);
    gen_nels_with_fromtau_handle.Init(tree);
    gen_nmus_with_fromtau_handle.Init(tree);
    gen_ntaus_with_fromtau_handle.Init(tree);
    filt_csc_handle.Init(tree);
    filt_hbhe_handle.Init(tree);
    filt_hcallaser_handle.Init(tree);
    filt_ecallaser_handle.Init(tree);
    filt_ecaltp_handle.Init(tree);
    filt_trkfail_handle.Init(tree);
    filt_eebadsc_handle.Init(tree);
    passes_metfilters_handle.Init(tree);
    passes_id_handle.Init(tree);
    passes_iso_handle.Init(tree);
    is_num_handle.Init(tree);
    is_den_handle.Init(tree);
    is_fo_handle.Init(tree);
    is_mu_handle.Init(tree);
    is_el_handle.Init(tree);
    exists_handle.Init(tree);
    is_fromw_handle.Init(tree);
    charge_handle.Init(tree);
    pdgid_handle.Init(tree);
    type_handle.Init(tree);
    d0_handle.Init(tree);
    d0err_handle.Init(tree);
    dz_handle.Init(tree);
    ip3d_handle.Init(tree);
    ip3derr_handle.Init(tree);
    dzerr_handle.Init(tree);
    mt_handle.Init(tree);
    corpfiso_handle.Init(tree);
    pfiso_handle.Init(tree);
    chiso_handle.Init(tree);
    emiso_handle.Init(tree);
    nhiso_handle.Init(tree);
    corpfiso04_handle.Init(tree);
    pfiso04_handle.Init(tree);
    chiso04_handle.Init(tree);
    emiso04_handle.Init(tree);
    nhiso04_handle.Init(tree);
    cordetiso_handle.Init(tree);
    detiso_handle.Init(tree);
    trkiso_handle.Init(tree);
    ecaliso_handle.Init(tree);
    hcaliso_handle.Init(tree);
    cordetiso04_handle.Init(tree);
    detiso04_handle.Init(tree);
    trkiso04_handle.Init(tree);
    ecaliso04_handle.Init(tree);
    hcaliso04_handle.Init(tree);
    effarea_handle.Init(tree);
    effarea04_handle.Init(tree);
    dbeta_handle.Init(tree);
    dbeta04_handle.Init(tree);
    sf_lepeff_handle.Init(tree);
    sf_trig_handle.Init(tree);
    mcid_handle.Init(tree);
    mc3id_handle.Init(tree);
    momid_handle.Init(tree);
    mc3_momid_handle.Init(tree);
    q3agree_handle.Init(tree);
    is_conv_handle.Init(tree);
    qsc_handle.Init(tree);
    qctf_handle.Init(tree);
    qgsf_handle.Init(tree);
    nmhits_handle.Init(tree);
    eleid_veto_handle.Init(tree);
    eleid_loose_handle.Init(tree);
    eleid_medium_handle.Init(tree);
    eleid_tight_handle.Init(tree);
    is_eleid_veto_handle.Init(tree);
    is_eleid_loose_handle.Init(tree);
    is_eleid_medium_handle.Init(tree);
    is_eleid_tight_handle.Init(tree);
    dphiin_handle.Init(tree);
    detain_handle.Init(tree);
    sieie_handle.Init(tree);
    hoe_handle.Init(tree);
    ooemoop_handle.Init(tree);
    conv_dist_handle.Init(tree);
    conv_dcot_handle.Init(tree);
    is_global_handle.Init(tree);
    is_tracker_handle.Init(tree);
    is_stamu_handle.Init(tree);
    is_pfmu_handle.Init(tree);
    is_loosemu_handle.Init(tree);
    is_tightmu_handle.Init(tree);
    npixelhits_handle.Init(tree);
    nsihits_handle.Init(tree);
    nsilayers_handle.Init(tree);
    nstahits_handle.Init(tree);
    nstations_handle.Init(tree);
    chi2_handle.Init(tree);
    ndof_handle.Init(tree);
    pterr_handle.Init(tree);
    ecal_vetodep_handle.Init(tree);
    hcal_vetodep_handle.Init(tree);
    p4_handle.Init(tree);
    mcp4_handle.Init(tree);
    mc3p4_handle.Init(tree);
    mc_momp4_handle.Init(tree);
    gsf_p4_handle.Init(tree);
    ctf_p4_handle.Init(tree);
    sc_p4_handle.Init(tree);
    gfit_p4_handle.Init(tree);

}

void EFF::Init(TTree* const tree)
{
    Init(*tree);
}

void EFF::GetEntry(const unsigned int entry)
{
    run_handle.GetEntry(entry);
    ls_handle.GetEntry(entry);
    evt_handle.GetEntry(entry);
    is_real_data_handle.GetEntry(entry);
    sample_handle.GetEntry(entry);
    nvtxs_handle.GetEntry(entry);
    vtx_idx_handle.GetEntry(entry);
    pfmet_handle.GetEntry(entry);
    pfmet_phi_handle.GetEntry(entry);
    uncorpfmet_handle.GetEntry(entry);
    uncorpfmet_phi_handle.GetEntry(entry);
    pu_nvtxs_handle.GetEntry(entry);
    pu_ntrueint_handle.GetEntry(entry);
    scale1fb_handle.GetEntry(entry);
    xsec_handle.GetEntry(entry);
    nevts_handle.GetEntry(entry);
    kfactor_handle.GetEntry(entry);
    gen_met_handle.GetEntry(entry);
    gen_met_phi_handle.GetEntry(entry);
    dataset_handle.GetEntry(entry);
    filename_handle.GetEntry(entry);
    gen_nleps_handle.GetEntry(entry);
    gen_nels_handle.GetEntry(entry);
    gen_nmus_handle.GetEntry(entry);
    gen_ntaus_handle.GetEntry(entry);
    gen_nleps_with_fromtau_handle.GetEntry(entry);
    gen_nels_with_fromtau_handle.GetEntry(entry);
    gen_nmus_with_fromtau_handle.GetEntry(entry);
    gen_ntaus_with_fromtau_handle.GetEntry(entry);
    filt_csc_handle.GetEntry(entry);
    filt_hbhe_handle.GetEntry(entry);
    filt_hcallaser_handle.GetEntry(entry);
    filt_ecallaser_handle.GetEntry(entry);
    filt_ecaltp_handle.GetEntry(entry);
    filt_trkfail_handle.GetEntry(entry);
    filt_eebadsc_handle.GetEntry(entry);
    passes_metfilters_handle.GetEntry(entry);
    passes_id_handle.GetEntry(entry);
    passes_iso_handle.GetEntry(entry);
    is_num_handle.GetEntry(entry);
    is_den_handle.GetEntry(entry);
    is_fo_handle.GetEntry(entry);
    is_mu_handle.GetEntry(entry);
    is_el_handle.GetEntry(entry);
    exists_handle.GetEntry(entry);
    is_fromw_handle.GetEntry(entry);
    charge_handle.GetEntry(entry);
    pdgid_handle.GetEntry(entry);
    type_handle.GetEntry(entry);
    d0_handle.GetEntry(entry);
    d0err_handle.GetEntry(entry);
    dz_handle.GetEntry(entry);
    ip3d_handle.GetEntry(entry);
    ip3derr_handle.GetEntry(entry);
    dzerr_handle.GetEntry(entry);
    mt_handle.GetEntry(entry);
    corpfiso_handle.GetEntry(entry);
    pfiso_handle.GetEntry(entry);
    chiso_handle.GetEntry(entry);
    emiso_handle.GetEntry(entry);
    nhiso_handle.GetEntry(entry);
    corpfiso04_handle.GetEntry(entry);
    pfiso04_handle.GetEntry(entry);
    chiso04_handle.GetEntry(entry);
    emiso04_handle.GetEntry(entry);
    nhiso04_handle.GetEntry(entry);
    cordetiso_handle.GetEntry(entry);
    detiso_handle.GetEntry(entry);
    trkiso_handle.GetEntry(entry);
    ecaliso_handle.GetEntry(entry);
    hcaliso_handle.GetEntry(entry);
    cordetiso04_handle.GetEntry(entry);
    detiso04_handle.GetEntry(entry);
    trkiso04_handle.GetEntry(entry);
    ecaliso04_handle.GetEntry(entry);
    hcaliso04_handle.GetEntry(entry);
    effarea_handle.GetEntry(entry);
    effarea04_handle.GetEntry(entry);
    dbeta_handle.GetEntry(entry);
    dbeta04_handle.GetEntry(entry);
    sf_lepeff_handle.GetEntry(entry);
    sf_trig_handle.GetEntry(entry);
    mcid_handle.GetEntry(entry);
    mc3id_handle.GetEntry(entry);
    momid_handle.GetEntry(entry);
    mc3_momid_handle.GetEntry(entry);
    q3agree_handle.GetEntry(entry);
    is_conv_handle.GetEntry(entry);
    qsc_handle.GetEntry(entry);
    qctf_handle.GetEntry(entry);
    qgsf_handle.GetEntry(entry);
    nmhits_handle.GetEntry(entry);
    eleid_veto_handle.GetEntry(entry);
    eleid_loose_handle.GetEntry(entry);
    eleid_medium_handle.GetEntry(entry);
    eleid_tight_handle.GetEntry(entry);
    is_eleid_veto_handle.GetEntry(entry);
    is_eleid_loose_handle.GetEntry(entry);
    is_eleid_medium_handle.GetEntry(entry);
    is_eleid_tight_handle.GetEntry(entry);
    dphiin_handle.GetEntry(entry);
    detain_handle.GetEntry(entry);
    sieie_handle.GetEntry(entry);
    hoe_handle.GetEntry(entry);
    ooemoop_handle.GetEntry(entry);
    conv_dist_handle.GetEntry(entry);
    conv_dcot_handle.GetEntry(entry);
    is_global_handle.GetEntry(entry);
    is_tracker_handle.GetEntry(entry);
    is_stamu_handle.GetEntry(entry);
    is_pfmu_handle.GetEntry(entry);
    is_loosemu_handle.GetEntry(entry);
    is_tightmu_handle.GetEntry(entry);
    npixelhits_handle.GetEntry(entry);
    nsihits_handle.GetEntry(entry);
    nsilayers_handle.GetEntry(entry);
    nstahits_handle.GetEntry(entry);
    nstations_handle.GetEntry(entry);
    chi2_handle.GetEntry(entry);
    ndof_handle.GetEntry(entry);
    pterr_handle.GetEntry(entry);
    ecal_vetodep_handle.GetEntry(entry);
    hcal_vetodep_handle.GetEntry(entry);
    p4_handle.GetEntry(entry);
    mcp4_handle.GetEntry(entry);
    mc3p4_handle.GetEntry(entry);
    mc_momp4_handle.GetEntry(entry);
    gsf_p4_handle.GetEntry(entry);
    ctf_p4_handle.GetEntry(entry);
    sc_p4_handle.GetEntry(entry);
    gfit_p4_handle.GetEntry(entry);

}

void EFF::LoadAllBranches()
{
    run_handle.Load();
    ls_handle.Load();
    evt_handle.Load();
    is_real_data_handle.Load();
    sample_handle.Load();
    nvtxs_handle.Load();
    vtx_idx_handle.Load();
    pfmet_handle.Load();
    pfmet_phi_handle.Load();
    uncorpfmet_handle.Load();
    uncorpfmet_phi_handle.Load();
    pu_nvtxs_handle.Load();
    pu_ntrueint_handle.Load();
    scale1fb_handle.Load();
    xsec_handle.Load();
    nevts_handle.Load();
    kfactor_handle.Load();
    gen_met_handle.Load();
    gen_met_phi_handle.Load();
    dataset_handle.Load();
    filename_handle.Load();
    gen_nleps_handle.Load();
    gen_nels_handle.Load();
    gen_nmus_handle.Load();
    gen_ntaus_handle.Load();
    gen_nleps_with_fromtau_handle.Load();
    gen_nels_with_fromtau_handle.Load();
    gen_nmus_with_fromtau_handle.Load();
    gen_ntaus_with_fromtau_handle.Load();
    filt_csc_handle.Load();
    filt_hbhe_handle.Load();
    filt_hcallaser_handle.Load();
    filt_ecallaser_handle.Load();
    filt_ecaltp_handle.Load();
    filt_trkfail_handle.Load();
    filt_eebadsc_handle.Load();
    passes_metfilters_handle.Load();
    passes_id_handle.Load();
    passes_iso_handle.Load();
    is_num_handle.Load();
    is_den_handle.Load();
    is_fo_handle.Load();
    is_mu_handle.Load();
    is_el_handle.Load();
    exists_handle.Load();
    is_fromw_handle.Load();
    charge_handle.Load();
    pdgid_handle.Load();
    type_handle.Load();
    d0_handle.Load();
    d0err_handle.Load();
    dz_handle.Load();
    ip3d_handle.Load();
    ip3derr_handle.Load();
    dzerr_handle.Load();
    mt_handle.Load();
    corpfiso_handle.Load();
    pfiso_handle.Load();
    chiso_handle.Load();
    emiso_handle.Load();
    nhiso_handle.Load();
    corpfiso04_handle.Load();
    pfiso04_handle.Load();
    chiso04_handle.Load();
    emiso04_handle.Load();
    nhiso04_handle.Load();
    cordetiso_handle.Load();
    detiso_handle.Load();
    trkiso_handle.Load();
    ecaliso_handle.Load();
    hcaliso_handle.Load();
    cordetiso04_handle.Load();
    detiso04_handle.Load();
    trkiso04_handle.Load();
    ecaliso04_handle.Load();
    hcaliso04_handle.Load();
    effarea_handle.Load();
    effarea04_handle.Load();
    dbeta_handle.Load();
    dbeta04_handle.Load();
    sf_lepeff_handle.Load();
    sf_trig_handle.Load();
    mcid_handle.Load();
    mc3id_handle.Load();
    momid_handle.Load();
    mc3_momid_handle.Load();
    q3agree_handle.Load();
    is_conv_handle.Load();
    qsc_handle.Load();
    qctf_handle.Load();
    qgsf_handle.Load();
    nmhits_handle.Load();
    eleid_veto_handle.Load();
    eleid_loose_handle.Load();
    eleid_medium_handle.Load();
    eleid_tight_handle.Load();
    is_eleid_veto_handle.Load();
    is_eleid_loose_handle.Load();
    is_eleid_medium_handle.Load();
    is_eleid_tight_handle.Load();
    dphiin_handle.Load();
    detain_handle.Load();
    sieie_handle.Load();
    hoe_handle.Load();
    ooemoop_handle.Load();
    conv_dist_handle.Load();
    conv_dcot_handle.Load();
    is_global_handle.Load();
    is_tracker_handle.Load();
    is_stamu_handle.Load();
    is_pfmu_handle.Load();
    is_loosemu_handle.Load();
    is_tightmu_handle.Load();
    npixelhits_handle.Load();
    nsihits_handle.Load();
    nsilayers_handle.Load();
    nstahits_handle.Load();
    nstations_handle.Load();
    chi2_handle.Load();
    ndof_handle.Load();
    pterr_handle.Load();
    ecal_vetodep_handle.Load();
    hcal_vetodep_handle.Load();
    p4_handle.Load();
    mcp4_handle.Load();
    mc3p4_handle.Load();
    mc_momp4_handle.Load();
    gsf_p4_handle.Load();
    ctf_p4_handle.Load();
    sc_p4_handle.Load();
    gfit_p4_handle.Load();

}

// branch accessor methods:
const unsigned int& EFF::run() {return run_handle.get();}
const unsigned int& EFF::ls() {return ls_handle.get();}
const unsigned int& EFF::evt() {return evt_handle.get();}
const bool& EFF::is_real_data() {return is_real_data_handle.get();}
const int& EFF::sample() {return sample_handle.get();}
const int& EFF::nvtxs() {return nvtxs_handle.get();}
const int& EFF::vtx_idx() {return vtx_idx_handle.get();}
const float& EFF::pfmet() {return pfmet_handle.get();}
const float& EFF::pfmet_phi() {return pfmet_phi_handle.get();}
const float& EFF::uncorpfmet() {return uncorpfmet_handle.get();}
const float& EFF::uncorpfmet_phi() {return uncorpfmet_phi_handle.get();}
const float& EFF::pu_nvtxs() {return pu_nvtxs_handle.get();}
const float& EFF::pu_ntrueint() {return pu_ntrueint_handle.get();}
const float& EFF::scale1fb() {return scale1fb_handle.get();}
const float& EFF::xsec() {return xsec_handle.get();}
const unsigned int& EFF::nevts() {return nevts_handle.get();}
const float& EFF::kfactor() {return kfactor_handle.get();}
const float& EFF::gen_met() {return gen_met_handle.get();}
const float& EFF::gen_met_phi() {return gen_met_phi_handle.get();}
const TString& EFF::dataset() {return dataset_handle.get();}
const TString& EFF::filename() {return filename_handle.get();}
const int& EFF::gen_nleps() {return gen_nleps_handle.get();}
const int& EFF::gen_nels() {return gen_nels_handle.get();}
const int& EFF::gen_nmus() {return gen_nmus_handle.get();}
const int& EFF::gen_ntaus() {return gen_ntaus_handle.get();}
const int& EFF::gen_nleps_with_fromtau() {return gen_nleps_with_fromtau_handle.get();}
const int& EFF::gen_nels_with_fromtau() {return gen_nels_with_fromtau_handle.get();}
const int& EFF::gen_nmus_with_fromtau() {return gen_nmus_with_fromtau_handle.get();}
const int& EFF::gen_ntaus_with_fromtau() {return gen_ntaus_with_fromtau_handle.get();}
const bool& EFF::filt_csc() {return filt_csc_handle.get();}
const bool& EFF::filt_hbhe() {return filt_hbhe_handle.get();}
const bool& EFF::filt_hcallaser() {return filt_hcallaser_handle.get();}
const bool& EFF::filt_ecallaser() {return filt_ecallaser_handle.get();}
const bool& EFF::filt_ecaltp() {return filt_ecaltp_handle.get();}
const bool& EFF::filt_trkfail() {return filt_trkfail_handle.get();}
const bool& EFF::filt_eebadsc() {return filt_eebadsc_handle.get();}
const bool& EFF::passes_metfilters() {return passes_metfilters_handle.get();}
const bool& EFF::passes_id() {return passes_id_handle.get();}
const bool& EFF::passes_iso() {return passes_iso_handle.get();}
const bool& EFF::is_num() {return is_num_handle.get();}
const bool& EFF::is_den() {return is_den_handle.get();}
const bool& EFF::is_fo() {return is_fo_handle.get();}
const bool& EFF::is_mu() {return is_mu_handle.get();}
const bool& EFF::is_el() {return is_el_handle.get();}
const bool& EFF::exists() {return exists_handle.get();}
const int& EFF::is_fromw() {return is_fromw_handle.get();}
const int& EFF::charge() {return charge_handle.get();}
const int& EFF::pdgid() {return pdgid_handle.get();}
const int& EFF::type() {return type_handle.get();}
const float& EFF::d0() {return d0_handle.get();}
const float& EFF::d0err() {return d0err_handle.get();}
const float& EFF::dz() {return dz_handle.get();}
const float& EFF::ip3d() {return ip3d_handle.get();}
const float& EFF::ip3derr() {return ip3derr_handle.get();}
const float& EFF::dzerr() {return dzerr_handle.get();}
const float& EFF::mt() {return mt_handle.get();}
const float& EFF::corpfiso() {return corpfiso_handle.get();}
const float& EFF::pfiso() {return pfiso_handle.get();}
const float& EFF::chiso() {return chiso_handle.get();}
const float& EFF::emiso() {return emiso_handle.get();}
const float& EFF::nhiso() {return nhiso_handle.get();}
const float& EFF::corpfiso04() {return corpfiso04_handle.get();}
const float& EFF::pfiso04() {return pfiso04_handle.get();}
const float& EFF::chiso04() {return chiso04_handle.get();}
const float& EFF::emiso04() {return emiso04_handle.get();}
const float& EFF::nhiso04() {return nhiso04_handle.get();}
const float& EFF::cordetiso() {return cordetiso_handle.get();}
const float& EFF::detiso() {return detiso_handle.get();}
const float& EFF::trkiso() {return trkiso_handle.get();}
const float& EFF::ecaliso() {return ecaliso_handle.get();}
const float& EFF::hcaliso() {return hcaliso_handle.get();}
const float& EFF::cordetiso04() {return cordetiso04_handle.get();}
const float& EFF::detiso04() {return detiso04_handle.get();}
const float& EFF::trkiso04() {return trkiso04_handle.get();}
const float& EFF::ecaliso04() {return ecaliso04_handle.get();}
const float& EFF::hcaliso04() {return hcaliso04_handle.get();}
const float& EFF::effarea() {return effarea_handle.get();}
const float& EFF::effarea04() {return effarea04_handle.get();}
const float& EFF::dbeta() {return dbeta_handle.get();}
const float& EFF::dbeta04() {return dbeta04_handle.get();}
const float& EFF::sf_lepeff() {return sf_lepeff_handle.get();}
const float& EFF::sf_trig() {return sf_trig_handle.get();}
const int& EFF::mcid() {return mcid_handle.get();}
const int& EFF::mc3id() {return mc3id_handle.get();}
const int& EFF::momid() {return momid_handle.get();}
const int& EFF::mc3_momid() {return mc3_momid_handle.get();}
const bool& EFF::q3agree() {return q3agree_handle.get();}
const bool& EFF::is_conv() {return is_conv_handle.get();}
const int& EFF::qsc() {return qsc_handle.get();}
const int& EFF::qctf() {return qctf_handle.get();}
const int& EFF::qgsf() {return qgsf_handle.get();}
const int& EFF::nmhits() {return nmhits_handle.get();}
const int& EFF::eleid_veto() {return eleid_veto_handle.get();}
const int& EFF::eleid_loose() {return eleid_loose_handle.get();}
const int& EFF::eleid_medium() {return eleid_medium_handle.get();}
const int& EFF::eleid_tight() {return eleid_tight_handle.get();}
const bool& EFF::is_eleid_veto() {return is_eleid_veto_handle.get();}
const bool& EFF::is_eleid_loose() {return is_eleid_loose_handle.get();}
const bool& EFF::is_eleid_medium() {return is_eleid_medium_handle.get();}
const bool& EFF::is_eleid_tight() {return is_eleid_tight_handle.get();}
const float& EFF::dphiin() {return dphiin_handle.get();}
const float& EFF::detain() {return detain_handle.get();}
const float& EFF::sieie() {return sieie_handle.get();}
const float& EFF::hoe() {return hoe_handle.get();}
const float& EFF::ooemoop() {return ooemoop_handle.get();}
const float& EFF::conv_dist() {return conv_dist_handle.get();}
const float& EFF::conv_dcot() {return conv_dcot_handle.get();}
const bool& EFF::is_global() {return is_global_handle.get();}
const bool& EFF::is_tracker() {return is_tracker_handle.get();}
const bool& EFF::is_stamu() {return is_stamu_handle.get();}
const bool& EFF::is_pfmu() {return is_pfmu_handle.get();}
const bool& EFF::is_loosemu() {return is_loosemu_handle.get();}
const bool& EFF::is_tightmu() {return is_tightmu_handle.get();}
const int& EFF::npixelhits() {return npixelhits_handle.get();}
const int& EFF::nsihits() {return nsihits_handle.get();}
const int& EFF::nsilayers() {return nsilayers_handle.get();}
const int& EFF::nstahits() {return nstahits_handle.get();}
const int& EFF::nstations() {return nstations_handle.get();}
const float& EFF::chi2() {return chi2_handle.get();}
const float& EFF::ndof() {return ndof_handle.get();}
const float& EFF::pterr() {return pterr_handle.get();}
const float& EFF::ecal_vetodep() {return ecal_vetodep_handle.get();}
const float& EFF::hcal_vetodep() {return hcal_vetodep_handle.get();}
const LorentzVector& EFF::p4() {return p4_handle.get();}
const LorentzVector& EFF::mcp4() {return mcp4_handle.get();}
const LorentzVector& EFF::mc3p4() {return mc3p4_handle.get();}
const LorentzVector& EFF::mc_momp4() {return mc_momp4_handle.get();}
const LorentzVector& EFF::gsf_p4() {return gsf_p4_handle.get();}
const LorentzVector& EFF::ctf_p4() {return ctf_p4_handle.get();}
const LorentzVector& EFF::sc_p4() {return sc_p4_handle.get();}
const LorentzVector& EFF::gfit_p4() {return gfit_p4_handle.get();}




/*static*/ void EFF::progress(const int nEventsTotal, const int nEventsChain)
{
    int period = 1000;
    if (nEventsTotal%1000 == 0)
    {
        // xterm magic from L. Vacavant and A. Cerri
        if (isatty(1))
        {
            if ((nEventsChain - nEventsTotal) > period)
            {
                float frac = (float)nEventsTotal/(nEventsChain*0.01);
                printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%\033[0m\033[32m <---\033[0m\015", frac);
                fflush(stdout);
            }
            else
            {
                printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%\033[0m\033[32m <---\033[0m\015", 100.0);
                std::cout << std::endl;
            }
        }
    }
}
namespace eff
{

    const unsigned int& run() {return eff_obj.run();}
    const unsigned int& ls() {return eff_obj.ls();}
    const unsigned int& evt() {return eff_obj.evt();}
    const bool& is_real_data() {return eff_obj.is_real_data();}
    const int& sample() {return eff_obj.sample();}
    const int& nvtxs() {return eff_obj.nvtxs();}
    const int& vtx_idx() {return eff_obj.vtx_idx();}
    const float& pfmet() {return eff_obj.pfmet();}
    const float& pfmet_phi() {return eff_obj.pfmet_phi();}
    const float& uncorpfmet() {return eff_obj.uncorpfmet();}
    const float& uncorpfmet_phi() {return eff_obj.uncorpfmet_phi();}
    const float& pu_nvtxs() {return eff_obj.pu_nvtxs();}
    const float& pu_ntrueint() {return eff_obj.pu_ntrueint();}
    const float& scale1fb() {return eff_obj.scale1fb();}
    const float& xsec() {return eff_obj.xsec();}
    const unsigned int& nevts() {return eff_obj.nevts();}
    const float& kfactor() {return eff_obj.kfactor();}
    const float& gen_met() {return eff_obj.gen_met();}
    const float& gen_met_phi() {return eff_obj.gen_met_phi();}
    const TString& dataset() {return eff_obj.dataset();}
    const TString& filename() {return eff_obj.filename();}
    const int& gen_nleps() {return eff_obj.gen_nleps();}
    const int& gen_nels() {return eff_obj.gen_nels();}
    const int& gen_nmus() {return eff_obj.gen_nmus();}
    const int& gen_ntaus() {return eff_obj.gen_ntaus();}
    const int& gen_nleps_with_fromtau() {return eff_obj.gen_nleps_with_fromtau();}
    const int& gen_nels_with_fromtau() {return eff_obj.gen_nels_with_fromtau();}
    const int& gen_nmus_with_fromtau() {return eff_obj.gen_nmus_with_fromtau();}
    const int& gen_ntaus_with_fromtau() {return eff_obj.gen_ntaus_with_fromtau();}
    const bool& filt_csc() {return eff_obj.filt_csc();}
    const bool& filt_hbhe() {return eff_obj.filt_hbhe();}
    const bool& filt_hcallaser() {return eff_obj.filt_hcallaser();}
    const bool& filt_ecallaser() {return eff_obj.filt_ecallaser();}
    const bool& filt_ecaltp() {return eff_obj.filt_ecaltp();}
    const bool& filt_trkfail() {return eff_obj.filt_trkfail();}
    const bool& filt_eebadsc() {return eff_obj.filt_eebadsc();}
    const bool& passes_metfilters() {return eff_obj.passes_metfilters();}
    const bool& passes_id() {return eff_obj.passes_id();}
    const bool& passes_iso() {return eff_obj.passes_iso();}
    const bool& is_num() {return eff_obj.is_num();}
    const bool& is_den() {return eff_obj.is_den();}
    const bool& is_fo() {return eff_obj.is_fo();}
    const bool& is_mu() {return eff_obj.is_mu();}
    const bool& is_el() {return eff_obj.is_el();}
    const bool& exists() {return eff_obj.exists();}
    const int& is_fromw() {return eff_obj.is_fromw();}
    const int& charge() {return eff_obj.charge();}
    const int& pdgid() {return eff_obj.pdgid();}
    const int& type() {return eff_obj.type();}
    const float& d0() {return eff_obj.d0();}
    const float& d0err() {return eff_obj.d0err();}
    const float& dz() {return eff_obj.dz();}
    const float& ip3d() {return eff_obj.ip3d();}
    const float& ip3derr() {return eff_obj.ip3derr();}
    const float& dzerr() {return eff_obj.dzerr();}
    const float& mt() {return eff_obj.mt();}
    const float& corpfiso() {return eff_obj.corpfiso();}
    const float& pfiso() {return eff_obj.pfiso();}
    const float& chiso() {return eff_obj.chiso();}
    const float& emiso() {return eff_obj.emiso();}
    const float& nhiso() {return eff_obj.nhiso();}
    const float& corpfiso04() {return eff_obj.corpfiso04();}
    const float& pfiso04() {return eff_obj.pfiso04();}
    const float& chiso04() {return eff_obj.chiso04();}
    const float& emiso04() {return eff_obj.emiso04();}
    const float& nhiso04() {return eff_obj.nhiso04();}
    const float& cordetiso() {return eff_obj.cordetiso();}
    const float& detiso() {return eff_obj.detiso();}
    const float& trkiso() {return eff_obj.trkiso();}
    const float& ecaliso() {return eff_obj.ecaliso();}
    const float& hcaliso() {return eff_obj.hcaliso();}
    const float& cordetiso04() {return eff_obj.cordetiso04();}
    const float& detiso04() {return eff_obj.detiso04();}
    const float& trkiso04() {return eff_obj.trkiso04();}
    const float& ecaliso04() {return eff_obj.ecaliso04();}
    const float& hcaliso04() {return eff_obj.hcaliso04();}
    const float& effarea() {return eff_obj.effarea();}
    const float& effarea04() {return eff_obj.effarea04();}
    const float& dbeta() {return eff_obj.dbeta();}
    const float& dbeta04() {return eff_obj.dbeta04();}
    const float& sf_lepeff() {return eff_obj.sf_lepeff();}
    const float& sf_trig() {return eff_obj.sf_trig();}
    const int& mcid() {return eff_obj.mcid();}
    const int& mc3id() {return eff_obj.mc3id();}
    const int& momid() {return eff_obj.momid();}
    const int& mc3_momid() {return eff_obj.mc3_momid();}
    const bool& q3agree() {return eff_obj.q3agree();}
    const bool& is_conv() {return eff_obj.is_conv();}
    const int& qsc() {return eff_obj.qsc();}
    const int& qctf() {return eff_obj.qctf();}
    const int& qgsf() {return eff_obj.qgsf();}
    const int& nmhits() {return eff_obj.nmhits();}
    const int& eleid_veto() {return eff_obj.eleid_veto();}
    const int& eleid_loose() {return eff_obj.eleid_loose();}
    const int& eleid_medium() {return eff_obj.eleid_medium();}
    const int& eleid_tight() {return eff_obj.eleid_tight();}
    const bool& is_eleid_veto() {return eff_obj.is_eleid_veto();}
    const bool& is_eleid_loose() {return eff_obj.is_eleid_loose();}
    const bool& is_eleid_medium() {return eff_obj.is_eleid_medium();}
    const bool& is_eleid_tight() {return eff_obj.is_eleid_tight();}
    const float& dphiin() {return eff_obj.dphiin();}
    const float& detain() {return eff_obj.detain();}
    const float& sieie() {return eff_obj.sieie();}
    const float& hoe() {return eff_obj.hoe();}
    const float& ooemoop() {return eff_obj.ooemoop();}
    const float& conv_dist() {return eff_obj.conv_dist();}
    const float& conv_dcot() {return eff_obj.conv_dcot();}
    const bool& is_global() {return eff_obj.is_global();}
    const bool& is_tracker() {return eff_obj.is_tracker();}
    const bool& is_stamu() {return eff_obj.is_stamu();}
    const bool& is_pfmu() {return eff_obj.is_pfmu();}
    const bool& is_loosemu() {return eff_obj.is_loosemu();}
    const bool& is_tightmu() {return eff_obj.is_tightmu();}
    const int& npixelhits() {return eff_obj.npixelhits();}
    const int& nsihits() {return eff_obj.nsihits();}
    const int& nsilayers() {return eff_obj.nsilayers();}
    const int& nstahits() {return eff_obj.nstahits();}
    const int& nstations() {return eff_obj.nstations();}
    const float& chi2() {return eff_obj.chi2();}
    const float& ndof() {return eff_obj.ndof();}
    const float& pterr() {return eff_obj.pterr();}
    const float& ecal_vetodep() {return eff_obj.ecal_vetodep();}
    const float& hcal_vetodep() {return eff_obj.hcal_vetodep();}
    const LorentzVector& p4() {return eff_obj.p4();}
    const LorentzVector& mcp4() {return eff_obj.mcp4();}
    const LorentzVector& mc3p4() {return eff_obj.mc3p4();}
    const LorentzVector& mc_momp4() {return eff_obj.mc_momp4();}
    const LorentzVector& gsf_p4() {return eff_obj.gsf_p4();}
    const LorentzVector& ctf_p4() {return eff_obj.ctf_p4();}
    const LorentzVector& sc_p4() {return eff_obj.sc_p4();}
    const LorentzVector& gfit_p4() {return eff_obj.gfit_p4();}

} // namespace eff
