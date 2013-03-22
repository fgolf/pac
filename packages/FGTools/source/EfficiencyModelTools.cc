#include "EfficiencyModelTools.h"

#include "CMS2.h"

#include "CORE/ssSelections.h"
#include "CORE/mcSelections.h"

#include "Math/VectorUtil.h"

using namespace at;

std::vector<unsigned int> efftools::getRecoJets () {

    const float mupt = 20.;
    const float elpt = 20.;
    
    std::vector<unsigned int> goodJets_;
    for (unsigned int jidx = 0; jidx < cms2.pfjets_p4().size(); jidx++) {
        
        float jet_eta = cms2.pfjets_p4().at(jidx).eta();
        float jet_pt  = cms2.pfjets_p4().at(jidx).pt() * cms2.pfjets_corL1FastL2L3().at(jidx);
        
        if (fabs(jet_eta) > 2.4)
            continue;
        if (jet_pt < 40.)
            continue;

        bool jetIsLep = false;
        for (unsigned int eidx = 0; eidx < cms2.els_p4().size(); eidx++) {
            
            if (cms2.els_p4().at(eidx).pt() < elpt)
                continue;
            if (fabs(cms2.els_p4().at(eidx).eta()) > 2.4)
                continue;
            if (!samesign::isNumeratorLepton(11, eidx))
                continue;

            if (ROOT::Math::VectorUtil::DeltaR(cms2.pfjets_p4().at(jidx), cms2.els_p4().at(eidx)) < 0.4) {
                jetIsLep = true;
                break;
            }
        }

        if (jetIsLep)
            continue;

        for (unsigned int midx = 0; midx < cms2.mus_p4().size(); midx++) {
            
            if (cms2.mus_p4().at(midx).pt() < mupt)
                continue;
            if (fabs(cms2.mus_p4().at(midx).eta()) > 2.4)
                continue;
            if (!samesign::isNumeratorLepton(13, midx))
                continue;

            if (ROOT::Math::VectorUtil::DeltaR(cms2.pfjets_p4().at(jidx), cms2.mus_p4().at(midx)) < 0.4) {
                jetIsLep = true;
                break;
            }
        }

        if (jetIsLep)
            continue;

        goodJets_.push_back(jidx);
    }

    return goodJets_;
}

std::vector<unsigned int> efftools::getRecoJets (const GenParticleStruct& struct1, const GenParticleStruct& struct2) {

    const float mupt = 20.;
    const float elpt = 20.;
    
    std::vector<unsigned int> goodJets_;
    for (unsigned int jidx = 0; jidx < cms2.pfjets_p4().size(); jidx++) {
        
        float jet_eta = cms2.pfjets_p4().at(jidx).eta();
        float jet_pt  = cms2.pfjets_p4().at(jidx).pt() * cms2.pfjets_corL1FastL2L3().at(jidx);
        
        if (fabs(jet_eta) > 2.4)
            continue;
        if (jet_pt < 40.)
            continue;

        std::pair<LorentzVector, int> recoLep1 = getRecoLepton(struct1);
        if (recoLep1.second > -1) {
            if (ROOT::Math::VectorUtil::DeltaR(cms2.pfjets_p4().at(jidx), recoLep1.first) < 0.4)
                continue;
        }

        std::pair<LorentzVector, int> recoLep2 = getRecoLepton(struct2);
        if (recoLep2.second > -1) {
            if (ROOT::Math::VectorUtil::DeltaR(cms2.pfjets_p4().at(jidx), recoLep2.first) < 0.4)
                continue;            
        }            

        bool jetIsLep = false;
        for (unsigned int eidx = 0; eidx < cms2.els_p4().size(); eidx++) {
            
            if (cms2.els_p4().at(eidx).pt() < elpt)
                continue;
            if (fabs(cms2.els_p4().at(eidx).eta()) > 2.4)
                continue;
            if (!samesign::isNumeratorLepton(11, eidx))
                continue;

            if (ROOT::Math::VectorUtil::DeltaR(cms2.pfjets_p4().at(jidx), cms2.els_p4().at(eidx)) < 0.4) {
                jetIsLep = true;
                break;
            }
        }

        if (jetIsLep)
            continue;

        for (unsigned int midx = 0; midx < cms2.mus_p4().size(); midx++) {
            
            if (cms2.mus_p4().at(midx).pt() < mupt)
                continue;
            if (fabs(cms2.mus_p4().at(midx).eta()) > 2.4)
                continue;
            if (!samesign::isNumeratorLepton(13, midx))
                continue;

            if (ROOT::Math::VectorUtil::DeltaR(cms2.pfjets_p4().at(jidx), cms2.mus_p4().at(midx)) < 0.4) {
                jetIsLep = true;
                break;
            }
        }

        if (jetIsLep)
            continue;

        goodJets_.push_back(jidx);
    }

    return goodJets_;
}

std::vector<unsigned int> efftools::getRecoJets (unsigned int hidx) {

    const float mupt = 20.;
    const float elpt = 20.;
    
    std::vector<unsigned int> goodJets_;
    for (unsigned int jidx = 0; jidx < cms2.pfjets_p4().size(); jidx++) {
        
        float jet_eta = cms2.pfjets_p4().at(jidx).eta();
        float jet_pt  = cms2.pfjets_p4().at(jidx).pt() * cms2.pfjets_corL1FastL2L3().at(jidx);
        
        if (fabs(jet_eta) > 2.4)
            continue;
        if (jet_pt < 40.)
            continue;

        if (ROOT::Math::VectorUtil::DeltaR(cms2.pfjets_p4().at(jidx), cms2.hyp_lt_p4().at(hidx)) < 0.4)
            continue;
        if (ROOT::Math::VectorUtil::DeltaR(cms2.pfjets_p4().at(jidx), cms2.hyp_ll_p4().at(hidx)) < 0.4)
            continue;

        bool jetIsLep = false;
        for (unsigned int eidx = 0; eidx < cms2.els_p4().size(); eidx++) {
            
            if (cms2.els_p4().at(eidx).pt() < elpt)
                continue;
            if (fabs(cms2.els_p4().at(eidx).eta()) > 2.4)
                continue;
            if (!samesign::isNumeratorLepton(11, eidx))
                continue;

            if (ROOT::Math::VectorUtil::DeltaR(cms2.pfjets_p4().at(jidx), cms2.els_p4().at(eidx)) < 0.4) {
                jetIsLep = true;
                break;
            }
        }

        if (jetIsLep)
            continue;

        for (unsigned int midx = 0; midx < cms2.mus_p4().size(); midx++) {
            
            if (cms2.mus_p4().at(midx).pt() < mupt)
                continue;
            if (fabs(cms2.mus_p4().at(midx).eta()) > 2.4)
                continue;
            if (!samesign::isNumeratorLepton(13, midx))
                continue;

            if (ROOT::Math::VectorUtil::DeltaR(cms2.pfjets_p4().at(jidx), cms2.mus_p4().at(midx)) < 0.4) {
                jetIsLep = true;
                break;
            }
        }

        if (jetIsLep)
            continue;

        goodJets_.push_back(jidx);
    }

    return goodJets_;
}

float efftools::getHT (std::vector<unsigned int>& jets) {
    
    float ht_ = 0;
    for (unsigned int jidx = 0; jidx < jets.size();  jidx++)
        ht_ += cms2.pfjets_p4().at(jets.at(jidx)).pt() * cms2.pfjets_corL1FastL2L3().at(jets.at(jidx));

    return ht_;
}

float efftools::getGenIsolation(const LorentzVector& p4, float parton_pt, float dr)
{
	float iso = 0.0;
    for (unsigned int idx = 0; idx < cms2.genps_p4().size(); idx++) 
	{
        if (cms2.genps_status().at(idx) != 3)
            {continue;}
        if ((abs(cms2.genps_id().at(idx)) < 1 || abs(cms2.genps_id().at(idx)) > 5) && abs(cms2.genps_id().at(idx)) != 21) // require a quark or gluon
            {continue;}
        if (cms2.genps_p4().at(idx).pt() < parton_pt)
            {continue;}
        if (ROOT::Math::VectorUtil::DeltaR(cms2.genps_p4().at(idx), p4) < dr)
            {iso += cms2.genps_p4().at(idx).pt();}
	}
	return iso;
}

float efftools::getClosestParton(const LorentzVector& p4, float parton_pt)
{
	float prev_dr = 999999.0;
    for (unsigned int idx = 0; idx < cms2.genps_p4().size(); idx++) 
	{
        if (cms2.genps_status().at(idx) != 3)
            {continue;}
        if ((abs(cms2.genps_id().at(idx)) < 1 || abs(cms2.genps_id().at(idx)) > 5) && abs(cms2.genps_id().at(idx)) != 21) // require a quark or gluon
            {continue;}
        if (cms2.genps_p4().at(idx).pt() < parton_pt)
            {continue;}
		float current_dr = ROOT::Math::VectorUtil::DeltaR(cms2.genps_p4().at(idx), p4);
		if (current_dr < prev_dr)
		{
			prev_dr   = current_dr;
		}
	}
	return prev_dr;
}

std::pair<LorentzVector, int> efftools::getRecoLepton (const GenParticleStruct& struct1) {

    const float mupt = 20.;
    const float elpt = 20.;
    
    int id = abs(struct1.id_) == 15 ? struct1.did_ : struct1.id_;
    int idx = abs(struct1.id_) == 15 ? struct1.didx_ : struct1.idx_;

    if (abs(id) == 11) {
        for (unsigned int eidx = 0; eidx < cms2.els_p4().size(); eidx++) {
            
            if (fabs(cms2.els_p4().at(eidx).eta()) > 2.4)
                continue;
            if (cms2.els_p4().at(eidx).pt() < elpt)
                continue;
            if (leptonIsFromW(eidx, 11, true) < 1)
                continue;
            if (mc3idx_eormu(11, eidx, 0.3, elpt) == idx)
                return std::make_pair(cms2.els_p4().at(eidx), eidx);
        }
    }

    if (abs(id) == 13) {
        for (unsigned int midx = 0; midx < cms2.mus_p4().size(); midx++) {
            
            if (fabs(cms2.mus_p4().at(midx).eta()) > 2.4)
                continue;
            if (cms2.mus_p4().at(midx).pt() < mupt)
                continue;
            if (leptonIsFromW(midx, 13, true) < 1)
                continue;
            if (mc3idx_eormu(13, midx, 0.3, mupt) == idx)
                return std::make_pair(cms2.mus_p4().at(midx), midx);
        }
    }

    return std::make_pair(LorentzVector(0., 0., 0., 0.), -1);
}

std::vector<std::pair<GenParticleStruct, GenParticleStruct> > efftools::makeGenHyps (float eta_cut, bool removeLeptonsOverlappingWithPartons) {

    //
    // loop over gen particles
    //            
    std::vector<GenParticleStruct> gleps;
    for (unsigned int gidx = 0; gidx < cms2.genps_p4().size(); gidx++) {

        if (cms2.genps_status().at(gidx) != 3)
        {
            continue;
        }

        int id    = cms2.genps_id().at(gidx);
        float pt  = cms2.genps_p4().at(gidx).pt();
        float eta = cms2.genps_p4().at(gidx).eta();

        if (fabs(eta) > eta_cut)
        {
            continue;
        }

        if (abs(id) == 11 || abs(id) == 13) {
            if (removeLeptonsOverlappingWithPartons && leptonOverlapsWithParton(cms2.genps_p4().at(gidx)))
            {
                continue;
            }

            gleps.push_back(GenParticleStruct(id, gidx, pt, eta, -999, 999, -999., -999.));   
        }

        //
        // need to add protection here to not get more than one lepton from the same tau
        //

        if (abs(id) == 15) {

            GenParticleStruct tmp_gp = GenParticleStruct(0, 0, 0, 0, 0, 0, 0, 0);                    
            for (unsigned int didx = 0; didx < cms2.genps_lepdaughter_id().at(gidx).size(); didx++) {

                int did = cms2.genps_lepdaughter_id().at(gidx).at(didx);
                if (abs(did) != 11 && abs(did) != 13)
                {
                    continue;
                }

                if (fabs(cms2.genps_lepdaughter_p4().at(gidx).at(didx).eta()) > eta_cut)
                {
                    continue;
                }

                if (removeLeptonsOverlappingWithPartons && leptonOverlapsWithParton(cms2.genps_lepdaughter_p4().at(gidx).at(didx)))
                {
                    continue;            
                }

                float dpt  = cms2.genps_lepdaughter_p4().at(gidx).at(didx).pt();
                float deta = cms2.genps_lepdaughter_p4().at(gidx).at(didx).eta();
                if (dpt > tmp_gp.dpt_)
                {
                    tmp_gp = GenParticleStruct(id, gidx, pt, eta, did, didx, dpt, deta); 
                }
            }

            if (tmp_gp.dpt_ > 0.1)
            {
                gleps.push_back(tmp_gp);
            }

        } // end tau block

    } // end loop over gen particles


    //
    // now make gen hyps
    //
    std::vector<std::pair<GenParticleStruct, GenParticleStruct> > glepPairs;
    for (unsigned int idx1 = 0; idx1 < gleps.size(); idx1++) {
        for (unsigned int idx2 = idx1 + 1; idx2 < gleps.size(); idx2++) {
            glepPairs.push_back(make_pair(gleps.at(idx1), gleps.at(idx2)));
        }
    } // loop to make gen pairs

    return glepPairs;
}

std::pair<GenParticleStruct, GenParticleStruct> efftools::getGenHyp (float pt1_cut, float pt2_cut, at::DileptonChargeType::value_type hypType) {

    float min_pt = std::min(pt1_cut, pt2_cut);
    float max_pt = std::max(pt1_cut, pt2_cut);
    
    std::vector<std::pair<GenParticleStruct, GenParticleStruct> > glepPairs = makeGenHyps();
    unsigned int npairs = glepPairs.size();

    GenParticleStruct gp = GenParticleStruct(0, 999999, 0., 0., 0, 999999, 0., 0.);
    std::pair<GenParticleStruct, GenParticleStruct> good_gen_hyp = std::make_pair(gp, gp);
    DileptonHypType::value_type good_hyp_type = DileptonHypType::ALL;
    for (unsigned int idx = 0; idx < npairs; idx++) {
        
        GenParticleStruct gp1 = glepPairs.at(idx).first;
        GenParticleStruct gp2 = glepPairs.at(idx).second;

        float gpt1  = (abs(gp1.id_) == 15) ? gp1.dpt_  : gp1.pt_;
        int gid1    = (abs(gp1.id_) == 15) ? gp1.did_  : gp1.id_;
        float gpt2  = (abs(gp2.id_) == 15) ? gp2.dpt_  : gp2.pt_;
        int gid2    = (abs(gp2.id_) == 15) ? gp2.did_  : gp2.id_;

        // require SS
        if (gid1 * gid2 < 0 && hypType == at::DileptonChargeType::SS)
            continue;
        else if (gid1 * gid2 > 0 && hypType == at::DileptonChargeType::OS)
            continue;

        if (std::min(gpt1, gpt2) < min_pt)
            continue;

        if (std::max(gpt1, gpt2) < max_pt)
            continue;

        DileptonHypType::value_type tmp_type = getHypType(gid1, gid2);
        if (tmp_type == DileptonHypType::ALL)
            continue;

        if (good_hyp_type == DileptonHypType::ALL) {
            good_hyp_type = tmp_type;
            good_gen_hyp = glepPairs.at(idx);
        }
        else if (tmp_type < good_hyp_type) {
            good_hyp_type = tmp_type;
            good_gen_hyp = glepPairs.at(idx);            
        }
        else if (tmp_type == good_hyp_type) {

            float ggpt1 = (abs(good_gen_hyp.first.id_) == 15) ? good_gen_hyp.first.dpt_ : good_gen_hyp.first.pt_;
            float ggpt2 = (abs(good_gen_hyp.second.id_) == 15) ? good_gen_hyp.second.dpt_ : good_gen_hyp.second.pt_;           

            if ( (gpt1+gpt2) > (ggpt1+ggpt2) ) {
                good_hyp_type = tmp_type;
                good_gen_hyp = glepPairs.at(idx);                
            }
        }
    } // end loop over gen hyps

    return good_gen_hyp;
}

int efftools::getRecoJet (const LorentzVector& p4) {

    float tmp_dr = 99.;
    int b_index = -1;
    for (unsigned int jidx = 0; jidx < cms2.pfjets_p4().size(); jidx++) {

        if (fabs(cms2.pfjets_p4().at(jidx).eta()) > 2.4)
            continue;

        float jet_pt  = cms2.pfjets_p4().at(jidx).pt() * cms2.pfjets_corL1FastL2L3().at(jidx);
        if (jet_pt < 40.)
            continue;
        if (!passesPFJetID(jidx))
            continue;

        if (ROOT::Math::VectorUtil::DeltaR(cms2.pfjets_p4().at(jidx), p4) < tmp_dr) {
            tmp_dr = ROOT::Math::VectorUtil::DeltaR(cms2.pfjets_p4().at(jidx), p4);
            b_index = jidx;
        }                            
    }

    return b_index;
}

std::vector<LorentzVector> efftools::getGenBjets (float pt_cut, float eta_cut) {

    std::vector<LorentzVector> tmp_vec;
    tmp_vec.clear();
    for (unsigned int gidx = 0; gidx < cms2.genps_status().size(); gidx++) {
        if (cms2.genps_status().at(gidx) != 3)
            continue;
        if (abs(cms2.genps_id().at(gidx)) != 5)
            continue;
        if (fabs(cms2.genps_p4().at(gidx).eta()) > eta_cut)
            continue;
        if (cms2.genps_p4().at(gidx).pt() < pt_cut)
            continue;
        
        tmp_vec.push_back(cms2.genps_p4().at(gidx));
    }

    return tmp_vec;
}

std::vector<LorentzVector> efftools::getGenJets (float pt_cut, float eta_cut) {
    
    std::vector<LorentzVector> tmp_vec;
    tmp_vec.clear();
    for (unsigned int gidx = 0; gidx < cms2.genps_status().size(); gidx++) {
        if (cms2.genps_status().at(gidx) != 3)
            continue;
        if ((abs(cms2.genps_id().at(gidx)) < 1 || abs(cms2.genps_id().at(gidx)) > 5) && abs(cms2.genps_id().at(gidx)) != 21)
            continue;
        if (fabs(cms2.genps_p4().at(gidx).eta()) > eta_cut)
            continue;
        if (cms2.genps_p4().at(gidx).pt() < pt_cut)
            continue;
        
        tmp_vec.push_back(cms2.genps_p4().at(gidx));
    }

    return tmp_vec;
}

float efftools::getGenHT(float pt_cut, float eta_cut) {

    std::vector<LorentzVector> tmp_vec = getGenJets(pt_cut, eta_cut);

    float tmp_ht = 0.;
    for(unsigned int idx = 0; idx < tmp_vec.size(); idx++) {
        tmp_ht += tmp_vec.at(idx).pt();
    }

    return tmp_ht;
}

bool efftools::leptonOverlapsWithParton(const LorentzVector& p4, float parton_pt, float dr) {
    
    for (unsigned int idx = 0; idx < cms2.genps_p4().size(); idx++) {
        
        if (cms2.genps_status().at(idx) != 3)
            continue;
        if ((abs(cms2.genps_id().at(idx)) < 1 || abs(cms2.genps_id().at(idx)) > 5) && abs(cms2.genps_id().at(idx)) != 21) // require a quark or gluon
            continue;
        if (cms2.genps_p4().at(idx).pt() < parton_pt)
            continue;
        if (ROOT::Math::VectorUtil::DeltaR(cms2.genps_p4().at(idx), p4) < dr)
            return true;
    }

    return false;
}

DileptonHypType::value_type efftools::getHypType (int id1, int id2) {
    
    if (abs(id1) != 11 && abs(id1) != 13)
        return DileptonHypType::ALL;
    if (abs(id2) != 11 && abs(id2) != 13)
        return DileptonHypType::ALL;

    if (abs(id1) == 11 && abs(id2) == 11)
        return DileptonHypType::EE;
    else if (abs(id1) == 13 && abs(id2) == 13)
        return DileptonHypType::MUMU;
    else
        return DileptonHypType::EMU;
}


int efftools::getGenParton (const LorentzVector& p4, bool use_status3_only) {

    float tmp_dr = 99.;
    int index = -999999;
    for (unsigned int idx = 0; idx < cms2.genps_p4().size(); idx++) {

        if (use_status3_only && cms2.genps_status().at(idx) != 3)
            continue;
        if (fabs(cms2.genps_p4().at(idx).eta()) > 2.4)
            continue;
        if (cms2.genps_p4().at(idx).pt() < 40.)
            continue;

        if (ROOT::Math::VectorUtil::DeltaR(cms2.genps_p4().at(idx), p4) < tmp_dr) {
            tmp_dr = ROOT::Math::VectorUtil::DeltaR(cms2.genps_p4().at(idx), p4);
            index = idx;
        }                            
    }

    return index;    
}
