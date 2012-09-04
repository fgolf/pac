#include "at/PrintIdIsoInfo.h"
#include "CMS2.h"
#include "ssSelections.h"
#include "eventSelections.h"
#include "muonSelections.h"
#include "electronSelections.h"
#include "trackSelections.h"

float EffectiveArea(int id, int idx)
{
    if (abs(id)!=11)
        return -999990.0;

    float etaAbs = fabs(cms2.els_etaSC()[idx]);

    // get effective area
    float AEff = 0.;
    if (etaAbs <= 1.0) AEff = 0.10;
    else if (etaAbs > 1.0 && etaAbs <= 1.479) AEff = 0.12;
    else if (etaAbs > 1.479 && etaAbs <= 2.0) AEff = 0.085;
    else if (etaAbs > 2.0 && etaAbs <= 2.2) AEff = 0.11;
    else if (etaAbs > 2.2 && etaAbs <= 2.3) AEff = 0.12;
    else if (etaAbs > 2.3 && etaAbs <= 2.4) AEff = 0.12;
    else if (etaAbs > 2.4) AEff = 0.13;
    return AEff;
}

namespace at
{
    void PrintIsoInfo(int id, int idx)
    {
        using namespace tas;

        // electrons
        if (abs(id) == 11)
        {
            cout << "electron Iso variables:" << endl;
            cout << "pfiso        = " << samesign::electronIsolationPF2012(idx) << endl;
            cout << "pfiso_ch     = " << cms2.els_iso03_pf2012_ch().at(idx) << endl;
            cout << "pfiso_em     = " << cms2.els_iso03_pf2012_em().at(idx) << endl;
            cout << "pfiso_nh     = " << cms2.els_iso03_pf2012_nh().at(idx) << endl;
            cout << "pfiso_ch ext = " << cms2.els_iso03_pf2012ext_ch().at(idx) << endl;
            cout << "pfiso_em ext = " << cms2.els_iso03_pf2012ext_em().at(idx) << endl;
            cout << "pfiso_nh ext = " << cms2.els_iso03_pf2012ext_nh().at(idx) << endl;
            cout << "rho          = " << cms2.evt_kt6pf_foregiso_rho() << endl;
            cout << "A_eff        = " << EffectiveArea(id, idx) << endl;
        }
        else if (abs(id) == 13)
        {
            cout << "Muon Iso variables:" << endl;
            cout << "pfiso    = " << muonIsoValuePF2012_deltaBeta(idx) << endl;
            cout << "pfiso_ch = " << cms2.mus_isoR03_pf_ChargedHadronPt().at(idx) << endl;
            cout << "pfiso_em = " << cms2.mus_isoR03_pf_PhotonEt().at(idx) << endl;
            cout << "pfiso_nh = " << cms2.mus_isoR03_pf_NeutralHadronEt().at(idx) << endl;
            cout << "dbeta = "    << cms2.mus_isoR03_pf_PUPt().at(idx) << endl; 
        }
    }


    void PrintIdInfo(int id, int idx)
    {
        using namespace tas;

        // electrons
        if (abs(id) == 11)
        {
            cout << "electron ID variables:" << endl;
            cout << "charge = " << tas::els_charge().at(idx) << endl;
        }
        else if (abs(id) == 13)
        {
            int vtxidx = firstGoodVertex();
            int trkidx = mus_trkidx().at(idx);
            float d0corr;
            float z0corr;
            if (vtxidx < 0 || trkidx < 0)
            {
                d0corr = fabs(mus_d0corr().at(idx));
                z0corr = fabs(mus_z0corr().at(idx));
            }
            else
            {
                d0corr = fabs(trks_d0_pv(trkidx, vtxidx).first);
                z0corr = fabs(trks_dz_pv(trkidx, vtxidx).first);
            }

            //* |eta| < 2.4
            //* global chi2/ndof < 10
            //* global and PF µ
            //* # layers hits ≥ 6
            //* # pixel hits ≥ 1
            //* # valid STA hits ≥ 1
            //* ECAL deposits < 4
            //* HCAL deposits < 6
            //* |d0_inner_track(PV)| ≤ 200 µm
            //* |dz_inner_track(PV)| ≤ 1 mm

            cout << "Muon ID variables:"           << endl;
            cout << "passes = "                    << samesign::isGoodLepton(id, idx)                 << endl;
            cout << "charge = "                    << mus_charge().at(idx)                            << endl;
            cout << "pt = "                        << mus_p4().at(idx).pt()                           << endl;
            cout << "eta (< 2.4) = "               << mus_p4().at(idx).eta()                          << endl;
            cout << "global chi2/ndof (<10) = "    << mus_gfit_chi2().at(idx)/mus_gfit_ndof().at(idx) << endl;
            cout << "is global mu = "              << (((mus_type().at(idx)) & (1<<1)) != 0)          << endl;
            cout << "is PF mu = "                  << (mus_pid_PFMuon().at(idx)!=0)                   << endl;
            cout << "has a  matching track = "     << (trkidx >= 0)                                    << endl;
            cout << "# layers (>= 6) = "           << trks_nlayers().at(trkidx)                       << endl;
            cout << "# pixel hits (>=1) = "        << trks_valid_pixelhits().at(trkidx)               << endl;
            cout << "# valid stations (>=1) = "    << mus_gfit_validSTAHits().at(idx)                 << endl;
            cout << "ECAL deposits (<4) = "        << mus_iso_ecalvetoDep().at(idx)                   << endl;
            cout << "HCAL deposits (<6) = "        << mus_iso_hcalvetoDep().at(idx)                   << endl;
            cout << "d0 correct (< 0.02) = "       << d0corr                                          << endl;
            cout << "z0 correct (< 0.1) = "        << z0corr                                          << endl;
        }
        else
        {
            // not a valid id
            cout << "not a valid id: " << id << endl;
            return;
        }
    }
} // namespace at
