#include "DileptonTree.h"
#include "CMS2.h"
#include "Math/VectorUtil.h"

DileptonTree::DileptonTree ()
{
    lep1 = SingleLeptonTree("lep1_");
    lep2 = SingleLeptonTree("lep2_");
}

DileptonTree::DileptonTree(const std::string &prefix)
    : prefix_(prefix)
{
    lep1 = SingleLeptonTree("lep1_");
    lep2 = SingleLeptonTree("lep2_");
}

DileptonTree::Fiduciality::value_type DileptonTree::GetFiduciality (const LorentzVector &v1, const LorentzVector &v2)
{
    float eta1 = fabs(v1.eta());
    float eta2 = fabs(v2.eta());

    if (std::max(eta1, eta2) < 1.4442) {return Fiduciality::BB;}
    if (std::min(eta1, eta2) > 1.566 ) {return Fiduciality::EE;}
    if (eta1 < 1.4442 && eta2 > 1.566) {return Fiduciality::BE;}
    if (eta2 < 1.4442 && eta1 > 1.566) {return Fiduciality::BE;}

    return Fiduciality::static_size;
}

void DileptonTree::FillCommon (int idx)
{
    // sort the leptons by pt
    float lt_pt = cms2.hyp_lt_p4().at(idx).pt();
    float ll_pt = cms2.hyp_ll_p4().at(idx).pt();

    int lep1_id;
    int lep1_idx;
    int lep2_id;
    int lep2_idx;
    if (lt_pt > ll_pt)
    {
        lep1_id  = cms2.hyp_lt_id().at(idx);
        lep1_idx = cms2.hyp_lt_index().at(idx); 
        lep2_id  = cms2.hyp_ll_id().at(idx);    
        lep2_idx = cms2.hyp_ll_index().at(idx); 
    }
    else
    {
        lep1_id  = cms2.hyp_ll_id().at(idx);
        lep1_idx = cms2.hyp_ll_index().at(idx); 
        lep2_id  = cms2.hyp_lt_id().at(idx);    
        lep2_idx = cms2.hyp_lt_index().at(idx); 
    }

    // fill lepton branches
    lep1.FillCommon(lep1_id, lep1_idx);
    lep2.FillCommon(lep2_id, lep2_idx);

    // fill dilepton event branches
    dilep_p4   = cms2.hyp_p4().at(idx);
    os         = (lep1_id * lep2_id < 0);
    ss         = (lep1_id * lep2_id > 0);
    dilep_type = at::hyp_typeToHypType(cms2.hyp_type().at(idx));
    dilep_mass = std::sqrt(fabs(dilep_p4.mass2()));
    dilep_dphi = ROOT::Math::VectorUtil::DeltaPhi(lep1.p4, lep2.p4);
    dilep_deta = lep1.p4.eta() - lep2.p4.eta();
    dilep_dr   = ROOT::Math::VectorUtil::DeltaR(lep1.p4, lep2.p4);

    const LorentzVector& v1 = (abs(lep1_id) == 11) ? lep1.sc_p4 : lep1.p4;
    const LorentzVector& v2 = (abs(lep2_id) == 11) ? lep2.sc_p4 : lep2.p4;

	// convenience bools
	mm = (dilep_type == at::DileptonHypType::MUMU);
	ee = (dilep_type == at::DileptonHypType::EE);
	em = (dilep_type == at::DileptonHypType::EMU);

    fiduciality = GetFiduciality(v1, v2);

    // matched gen objects
    gen_lep1_p4    = tas::hyp_lt_mc_p4().at(idx);
    gen_lep1_pdgid = tas::hyp_lt_mc_id().at(idx);
    gen_lep2_p4    = tas::hyp_ll_mc_p4().at(idx);
    gen_lep2_pdgid = tas::hyp_ll_mc_id().at(idx);
    if (gen_lep1_p4.pt() < gen_lep2_p4.pt())
    {
        std::swap(gen_lep1_p4   , gen_lep2_p4   );
        std::swap(gen_lep1_pdgid, gen_lep2_pdgid);
    }

    // matched gen dilepton hyp
    gen_dilep_p4   = gen_lep1_p4 + gen_lep2_p4;
    gen_os         = (gen_lep1_pdgid*gen_lep2_pdgid < 0);
    gen_ss         = (gen_lep1_pdgid*gen_lep2_pdgid > 0);
    gen_ee         = (abs(gen_lep1_pdgid*gen_lep2_pdgid) == /*11*11=*/121);
    gen_em         = (abs(gen_lep1_pdgid*gen_lep2_pdgid) == /*11*13=*/143);
    gen_mm         = (abs(gen_lep1_pdgid*gen_lep2_pdgid) == /*13*13=*/169);
    gen_dilep_mass = gen_dilep_p4.mass();
    gen_dilep_dphi = ROOT::Math::VectorUtil::DeltaPhi(gen_lep1_p4, gen_lep2_p4);
    gen_dilep_deta = gen_lep1_p4.eta() - gen_lep2_p4.eta();
    gen_dilep_dr   = ROOT::Math::VectorUtil::DeltaR  (gen_lep1_p4, gen_lep2_p4);

    if (gen_ee) {gen_dilep_type = at::DileptonHypType::EE;  }
    if (gen_mm) {gen_dilep_type = at::DileptonHypType::MUMU;}
    if (gen_em) {gen_dilep_type = at::DileptonHypType::EMU; }
}

void DileptonTree::Reset()
{
    lep1.Reset();
    lep2.Reset();

    dilep_p4       = LorentzVector(0, 0, 0, 0);
    os             = false;
    ss             = false;
	mm			   = false;
	ee			   = false;
	em			   = false;
    dilep_type     = at::DileptonHypType::static_size;
    dilep_mass     = -999999.;
    dilep_dphi     = -999999.;
    dilep_deta     = -999999.;
    dilep_dr       = -999999.;
    fiduciality    = Fiduciality::static_size;

    gen_lep1_p4    = LorentzVector(0, 0, 0, 0);
    gen_lep1_pdgid = -999999;
    gen_lep2_p4    = LorentzVector(0, 0, 0, 0);
    gen_lep2_pdgid = -999999;
    gen_dilep_p4   = LorentzVector(0, 0, 0, 0);
    gen_os         = false;
    gen_ss         = false;
    gen_mm         = false;
    gen_ee         = false;
    gen_em         = false;
    gen_dilep_type = at::DileptonHypType::static_size;
    gen_dilep_mass = -999999.;
    gen_dilep_dphi = -999999.;
    gen_dilep_deta = -999999.;
    gen_dilep_dr   = -999999.;
}

void DileptonTree::SetBranches(TTree &tree)
{
    lep1.SetBranches(tree);
    lep2.SetBranches(tree);

    tree.Branch(Form("%sdilep_p4"           , prefix_.c_str()) , "LorentzVector"     , &dilep_p4              ); 
    tree.Branch(Form("%sos"                 , prefix_.c_str()) , &os                 , "os/O"                 ); 
    tree.Branch(Form("%sss"                 , prefix_.c_str()) , &ss                 , "ss/O"                 ); 
    tree.Branch(Form("%smm"                 , prefix_.c_str()) , &mm                 , "mm/O"                 ); 
    tree.Branch(Form("%see"                 , prefix_.c_str()) , &ee                 , "ee/O"                 ); 
    tree.Branch(Form("%sem"                 , prefix_.c_str()) , &em                 , "em/O"                 ); 
    tree.Branch(Form("%sdilep_type"         , prefix_.c_str()) , &dilep_type         , "dilep_type/I"         ); 
    tree.Branch(Form("%sdilep_mass"         , prefix_.c_str()) , &dilep_mass         , "dilep_mass/F"         ); 
    tree.Branch(Form("%sdilep_dphi"         , prefix_.c_str()) , &dilep_dphi         , "dilep_dphi/F"         ); 
    tree.Branch(Form("%sdilep_deta"         , prefix_.c_str()) , &dilep_deta         , "dilep_deta/F"         ); 
    tree.Branch(Form("%sdilep_dr"           , prefix_.c_str()) , &dilep_dr           , "dilep_dr/F"           ); 
    tree.Branch(Form("%sfiduciality"        , prefix_.c_str()) , &fiduciality        , "fiduciality/I"        ); 
    tree.Branch(Form("%sgen_lep1_p4"        , prefix_.c_str()) , "LorentzVector"     , &gen_lep1_p4           ); 
    tree.Branch(Form("%sgen_lep1_pdgid"     , prefix_.c_str()) , &gen_lep1_pdgid     , "gen_lep1_pdgid/I"     ); 
    tree.Branch(Form("%sgen_lep2_p4"        , prefix_.c_str()) , "LorentzVector"     , &gen_lep2_p4           ); 
    tree.Branch(Form("%sgen_lep2_pdgid"     , prefix_.c_str()) , &gen_lep2_pdgid     , "gen_lep2_pdgid/I"     ); 
    tree.Branch(Form("%sgen_dilep_p4"       , prefix_.c_str()) , "LorentzVector"     , &gen_dilep_p4          ); 
    tree.Branch(Form("%sgen_os"             , prefix_.c_str()) , &gen_os             , "gen_os/O"             ); 
    tree.Branch(Form("%sgen_ss"             , prefix_.c_str()) , &gen_ss             , "gen_ss/O"             ); 
    tree.Branch(Form("%sgen_mm"             , prefix_.c_str()) , &gen_mm             , "gen_mm/O"             ); 
    tree.Branch(Form("%sgen_ee"             , prefix_.c_str()) , &gen_ee             , "gen_ee/O"             ); 
    tree.Branch(Form("%sgen_em"             , prefix_.c_str()) , &gen_em             , "gen_em/O"             ); 
    tree.Branch(Form("%sgen_dilep_type"     , prefix_.c_str()) , &gen_dilep_type     , "gen_dilep_type/I"     ); 
    tree.Branch(Form("%sgen_dilep_mass"     , prefix_.c_str()) , &gen_dilep_mass     , "gen_dilep_mass/F"     ); 
    tree.Branch(Form("%sgen_dilep_dphi"     , prefix_.c_str()) , &gen_dilep_dphi     , "gen_dilep_dphi/F"     ); 
    tree.Branch(Form("%sgen_dilep_deta"     , prefix_.c_str()) , &gen_dilep_deta     , "gen_dilep_deta/F"     ); 
    tree.Branch(Form("%sgen_dilep_dr"       , prefix_.c_str()) , &gen_dilep_dr       , "gen_dilep_dr/F"       ); 
}
