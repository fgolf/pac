#include "at/TrackIsoTools.h"
#include <set>
#include "CMS2.h"
#include "CORE/eventSelections.h"
#include "CORE/trackSelections.h"
#include "rt/MiscTools.h"

//
// code borrowed from 8 TeV single lepton stop analysis
//

namespace at
{
    struct at::myTrackIso  trackIso (int thisPf, float coneR, float dz_thresh, bool dovtxcut, float pt_thresh)
    {
        dovtxcut = false;

        struct at::myTrackIso iso;

        // no cuts  
        iso.iso_dr03_dz005_pt00 = 0.; // this one will be the default
  
        // dz variation                                                                                                                         
        iso.iso_dr03_dz020_pt00 = 0.;
        iso.iso_dr03_dz010_pt00 = 0.;
        iso.iso_dr03_dz000_pt00 = 0.;
  
        // isolation sum option
        iso.isoDir_dr03_dz005_pt00 = 0.;

        // cone04
        iso.iso_dr04_dz005_pt00 = 0.;

        // veto cone
        iso.iso_dr01503_dz005_pt00 = 0.; 
        iso.iso_dr0503_dz005_pt00 = 0.;

        //pt Variation                                                                                                                      
        iso.iso_dr03_dz005_pt01 = 0.;
        iso.iso_dr03_dz005_pt02 = 0.;
        iso.iso_dr03_dz005_pt03 = 0.;
        iso.iso_dr03_dz005_pt04 = 0.;
        iso.iso_dr03_dz005_pt05 = 0.;
        iso.iso_dr03_dz005_pt06 = 0.;
        iso.iso_dr03_dz005_pt07 = 0.;
        iso.iso_dr03_dz005_pt08 = 0.;
        iso.iso_dr03_dz005_pt09 = 0.;
        iso.iso_dr03_dz005_pt10 = 0.;

        for (int ipf = 0; ipf < (int)cms2.pfcands_p4().size(); ipf++)
        {
            if (ipf == thisPf) continue; // skip this PFCandidate
                                                                                                               
            if (cms2.pfcands_charge().at(ipf) == 0 ) continue; // skip neutrals                                                                                                                          

            // when we want to find the second isolated muon and electron
            // we do not use the electron and muon in the isolation sum,                                                                                              
            // to avoid overlap with the other lepton in the event
            //
            // IS THIS WHAT WE WANT TO DO?
            //
            if ((abs(cms2.pfcands_particleId().at(thisPf))==13 || abs(cms2.pfcands_particleId().at(thisPf))==11) && abs(cms2.pfcands_particleId().at(ipf))==13) continue;
            if ((abs(cms2.pfcands_particleId().at(thisPf))==13 || abs(cms2.pfcands_particleId().at(thisPf))==11) && abs(cms2.pfcands_particleId().at(ipf))==11) continue;                                                                   

            //----------------------------------------                                                                                                                                                   
            // find closest PV and dz w.r.t. that PV                                                                                                                                                     
            //----------------------------------------                                                                                                                                                   

            float mindz = 999.;
            int vtxi    = -1;

            if (dovtxcut)
            {
                for (unsigned int ivtx = 0; ivtx < cms2.vtxs_position().size(); ivtx++)
                {
                    int itrk = cms2.pfcands_trkidx().at(ipf);

                    if (itrk >= (int)cms2.trks_trk_p4().size() || itrk < 0 )
                    {
                        //note: this should only happen for electrons which do not have a matched track                                                                                                            
                        //currently we are just ignoring these guys                                                                                                                                                
                        continue;
                    }

                    ////////

                    if (!isGoodVertex(ivtx)) continue;

                    float mydz = trks_dz_pv(itrk,ivtx).first;

                    if (fabs(mydz) < fabs(mindz))
                    {
                        mindz = mydz;
                        vtxi = ivtx;
                    }

                }

                //----------------------------------------------------------------------------                                                                                                               
                // require closest PV is signal PV, dz cut, exclude tracks near hyp leptons                                                                                                                  
                //----------------------------------------------------------------------------                                                                                                               

                if (vtxi != 0) continue;
            }
            else
            {
                int itrk = -1;

                if (abs(cms2.pfcands_particleId().at(ipf)) != 11)
                {
                    itrk = cms2.pfcands_trkidx().at(ipf);
                    if (itrk >= (int)cms2.trks_trk_p4().size() || itrk < 0) continue;
                    mindz = trks_dz_pv(itrk,0).first;
                }

                if (abs(cms2.pfcands_particleId().at(ipf)) == 11 && cms2.pfcands_pfelsidx().at(ipf) >= 0)
                {
                    itrk = cms2.els_gsftrkidx().at(cms2.pfcands_pfelsidx().at(ipf));
                    if (itrk >= (int)cms2.gsftrks_p4().size() || itrk < 0) continue;
                    mindz = gsftrks_dz_pv(itrk,0).first;
                }
            }

            //---------------------------------------                                                                                                                                     
            // passes cuts, add up isolation value                                                                                                                                        
            //---------------------------------------                                                                                                                                                    

            coneR = 0.3;    
            double dr = rt::DeltaR(cms2.pfcands_p4().at(ipf) , cms2.pfcands_p4().at(thisPf));
            if (dr > coneR) continue; // skip pfcands outside the cone                                     

            // this is the default
            if (cms2.pfcands_p4().at(ipf).pt()>=0.0 && fabs(mindz) <= 0.05) iso.iso_dr03_dz005_pt00+= cms2.pfcands_p4().at(ipf).pt();

            // veto Cone 0.05 // this hould be ok for the taus
            if (cms2.pfcands_p4().at(ipf).pt()>=0.0 && fabs(mindz) <= 0.05 && dr >= 0.05) iso.iso_dr0503_dz005_pt00 += cms2.pfcands_p4().at(ipf).pt();

            // veto Cone 0.015 // this should be ok for the electron in the endcap
            if (cms2.pfcands_p4().at(ipf).pt()>=0.0 && fabs(mindz) <= 0.05 && dr >= 0.015) iso.iso_dr01503_dz005_pt00 += cms2.pfcands_p4().at(ipf).pt();

            // this is the iso-sum option
            if (cms2.pfcands_p4().at(ipf).pt()>=0.0 && fabs(mindz) <= 0.05) iso.isoDir_dr03_dz005_pt00 +=cms2.pfcands_p4().at(ipf).pt()*(1-3*dr);

            // some dz variation
            if (cms2.pfcands_p4().at(ipf).pt()>=0.0 && fabs(mindz) <= 0.00) iso.iso_dr03_dz000_pt00 += cms2.pfcands_p4().at(ipf).pt(); 
            if (cms2.pfcands_p4().at(ipf).pt()>=0.0 && fabs(mindz) <= 0.10) iso.iso_dr03_dz010_pt00 += cms2.pfcands_p4().at(ipf).pt();     
            if (cms2.pfcands_p4().at(ipf).pt()>=0.0 && fabs(mindz) <= 0.20) iso.iso_dr03_dz020_pt00 += cms2.pfcands_p4().at(ipf).pt();
    
            // some pt variation
            if (cms2.pfcands_p4().at(ipf).pt() >= 0.1 && fabs(mindz) <= 0.05) iso.iso_dr03_dz005_pt01 += cms2.pfcands_p4().at(ipf).pt();
            if (cms2.pfcands_p4().at(ipf).pt() >= 0.2 && fabs(mindz) <= 0.05) iso.iso_dr03_dz005_pt02 += cms2.pfcands_p4().at(ipf).pt();
            if (cms2.pfcands_p4().at(ipf).pt() >= 0.3 && fabs(mindz) <= 0.05) iso.iso_dr03_dz005_pt03 += cms2.pfcands_p4().at(ipf).pt();
            if (cms2.pfcands_p4().at(ipf).pt() >= 0.4 && fabs(mindz) <= 0.05) iso.iso_dr03_dz005_pt04 += cms2.pfcands_p4().at(ipf).pt();
            if (cms2.pfcands_p4().at(ipf).pt() >= 0.5 && fabs(mindz) <= 0.05) iso.iso_dr03_dz005_pt05 += cms2.pfcands_p4().at(ipf).pt();
            if (cms2.pfcands_p4().at(ipf).pt() >= 0.6 && fabs(mindz) <= 0.05) iso.iso_dr03_dz005_pt06 += cms2.pfcands_p4().at(ipf).pt();
            if (cms2.pfcands_p4().at(ipf).pt() >= 0.7 && fabs(mindz) <= 0.05) iso.iso_dr03_dz005_pt07 += cms2.pfcands_p4().at(ipf).pt();
            if (cms2.pfcands_p4().at(ipf).pt() >= 0.8 && fabs(mindz) <= 0.05) iso.iso_dr03_dz005_pt08 += cms2.pfcands_p4().at(ipf).pt();
            if (cms2.pfcands_p4().at(ipf).pt() >= 0.9 && fabs(mindz) <= 0.05) iso.iso_dr03_dz005_pt09 += cms2.pfcands_p4().at(ipf).pt();
            if (cms2.pfcands_p4().at(ipf).pt() >= 1.0 && fabs(mindz) <= 0.05) iso.iso_dr03_dz005_pt10 += cms2.pfcands_p4().at(ipf).pt();    
      
        } // end loop of the cand 

        return iso;
    }
} // namespace at
