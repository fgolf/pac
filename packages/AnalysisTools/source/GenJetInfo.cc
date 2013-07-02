#include "GenJetInfo.h"
#include "at/Predicates.h"
#include "CMS2.h"

using namespace tas;

namespace at
{
    std::vector<LorentzVector> GetGenJets(const float pt_cut, const float eta_cut)
    {

        std::vector<LorentzVector> gen_jets;
        for (size_t gidx = 0; gidx != genps_status().size(); gidx++)
        {
            if (genps_status().at(gidx) != 3)
                {continue;}
            if ((abs(genps_id().at(gidx)) < 1 || abs(genps_id().at(gidx)) > 5) && abs(genps_id().at(gidx)) != 21)
                {continue;}
            if (fabs(genps_p4().at(gidx).eta()) > eta_cut)
                {continue;}
            if (genps_p4().at(gidx).pt() < pt_cut)
                {continue;}

            gen_jets.push_back(genps_p4().at(gidx));
        }

        // done
        std::sort(gen_jets.begin(), gen_jets.end(), SortByPt<LorentzVector>());
        return gen_jets;
    }

    std::vector<LorentzVector> GetGenBJets(const float pt_cut, const float eta_cut)
    {
        std::vector<LorentzVector> gen_bjets;
        for (size_t gidx = 0; gidx != genps_status().size(); gidx++)
        {
            if (genps_status().at(gidx) != 3)
                {continue;}
            if (abs(genps_id().at(gidx)) != 5)
                {continue;}
            if (fabs(genps_p4().at(gidx).eta()) > eta_cut)
                {continue;}
            if (genps_p4().at(gidx).pt() < pt_cut)
                {continue;}

            gen_bjets.push_back(genps_p4().at(gidx));
        }

        std::sort(gen_bjets.begin(), gen_bjets.end(), SortByPt<LorentzVector>());
        return gen_bjets;
    }

    float GetGenHT(const float pt_cut, const float eta_cut)
    {
        std::vector<LorentzVector> gen_jets = GetGenJets(pt_cut, eta_cut);

        float ht = 0.;
        for(size_t idx = 0; idx != gen_jets.size(); idx++)
        {
            ht += gen_jets.at(idx).pt();
        }

        return ht;
    }

} // namespace at
