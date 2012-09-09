#include <bitset>
#include "MITConversionUtilities.h"
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
            cout << "\tpfiso        = " << samesign::electronIsolationPF2012(idx) << endl;
            cout << "\tpfiso_ch     = " << cms2.els_iso03_pf2012_ch().at(idx) << endl;
            cout << "\tpfiso_em     = " << cms2.els_iso03_pf2012_em().at(idx) << endl;
            cout << "\tpfiso_nh     = " << cms2.els_iso03_pf2012_nh().at(idx) << endl;
            cout << "\tpfiso_ch ext = " << cms2.els_iso03_pf2012ext_ch().at(idx) << endl;
            cout << "\tpfiso_em ext = " << cms2.els_iso03_pf2012ext_em().at(idx) << endl;
            cout << "\tpfiso_nh ext = " << cms2.els_iso03_pf2012ext_nh().at(idx) << endl;
            cout << "\trho          = " << cms2.evt_kt6pf_foregiso_rho() << endl;
            cout << "\tA_eff        = " << EffectiveArea(id, idx) << endl;
        }
        else if (abs(id) == 13)
        {
            cout << "Muon Iso variables:" << endl;
            cout << "\tpfiso    = " << muonIsoValuePF2012_deltaBeta(idx) << endl;
            cout << "\tpfiso_ch = " << cms2.mus_isoR03_pf_ChargedHadronPt().at(idx) << endl;
            cout << "\tpfiso_em = " << cms2.mus_isoR03_pf_PhotonEt().at(idx) << endl;
            cout << "\tpfiso_nh = " << cms2.mus_isoR03_pf_NeutralHadronEt().at(idx) << endl;
            cout << "\tdbeta = "    << cms2.mus_isoR03_pf_PUPt().at(idx) << endl; 
        }
    }


    void PrintIdInfo(int id, int idx)
    {
        using namespace tas;

        // electrons
        if (abs(id) == 11)
        {
            int vtxidx    = firstGoodVertex();
            int gsftrkidx = els_gsftrkidx().at(idx);
            int trkidx    = els_trkidx().at(idx);
            float d0corr = -9999.0;
            float z0corr = -9999.0;
            if (vtxidx >= 0 && gsftrkidx >= 0)
            {
                d0corr = fabs(gsftrks_d0_pv(gsftrkidx, vtxidx).first);
                z0corr = fabs(gsftrks_dz_pv(gsftrkidx, vtxidx).first);
            }
            else if (vtxidx >= 0 && trkidx >= 0)
            {
                d0corr = fabs(trks_d0_pv(trkidx, vtxidx).first);
                z0corr = fabs(trks_dz_pv(trkidx, vtxidx).first);
            }
            else
            {
                d0corr = fabs(els_d0corr().at(idx));
                z0corr = fabs(els_z0corr().at(idx));
            }
    
            // |1/E - 1/p|
            float ooemoop = fabs((1.0/els_ecalEnergy().at(idx)) - (els_eOverPIn().at(idx)/els_ecalEnergy().at(idx)));

            // MIT conversion
            bool vtxFitConversion = isMITConversion(idx, 0,   1e-6,   2.0,   true,  false);


            bool isEB = (els_fiduciality().at(idx) & (1 << ISEB));
            //cout << "electron ID variables:"                 << endl;
            //cout << "\tcharge = "                            << els_charge().at(idx) << endl;
            //cout << "\tpt = "                                << els_p4().at(idx).pt() << endl;
            //cout << "\t|eta| = "                             << fabs(els_p4().at(idx).eta()) << endl;
            //cout << "\t|eta| < 2.4 = "                       << (fabs(els_p4().at(idx).eta()) < 2.4) << endl;
            //cout << "\tnot 1.4442 < |eta| < 1.556 = "        << (not (fabs(els_p4().at(idx).eta()) < 1.4442 && fabs(els_p4().at(idx).eta()) > 1.556)) << endl;
            //cout << "\tany SS mu DR > 0.1 = "                << (electronId_noMuon_SS(idx)) << endl;
            //cout << "\t|deta_in| < (0.004, 0.007) = "        << els_dEtaIn().at(idx)                                                       
            //                                                 << "\tpasses = " << (isEB ? (els_dEtaIn().at(idx) < 0.004) : (els_dEtaIn().at(idx) < 0.007)) << endl;
            //cout << "\t|dphi_in| < (0.060, 0.030) = "        << els_dPhiIn().at(idx)                                                       
            //                                                 << "\tpasses = " << (isEB ? (els_dPhiIn().at(idx) < 0.060) : (els_dPhiIn().at(idx) < 0.030)) << endl;
            //cout << "\tsigma_ietaieta < (0.010, 0.030) = "   << els_sigmaIEtaIEta().at(idx) 
            //                                                 << "\tpasses = " << (isEB ? (els_sigmaIEtaIEta().at(idx) < 0.010) : (els_sigmaIEtaIEta().at(idx) < 0.030)) << endl;
            //cout << "\tH/E < (0.120, 0.100) = "              << els_hOverE().at(idx)
            //                                                 << "\tpasses = " << (isEB ? (els_hOverE().at(idx) < 0.120) : (els_hOverE().at(idx) < 0.100)) << endl;
            //cout << "\t|1/ECAL - 1/Pin| < (0.050, 0.050) = " << ooemoop << "\tpasses = " << (isEB ? (ooemoop  < 0.050) : (ooemoop < 0.050)) << endl;
            //cout << "\t|d0(PV)| < (0.020, 0.020) = "         << fabs(d0corr)  << "\tpasses = " << (fabs(d0corr) < 0.020) << endl;
            //cout << "\t|dz(PV)| < (0.100, 0.100) = "         << fabs(z0corr)  << "\tpasses = " << (fabs(z0corr) < 0.100) << endl;
            //cout << "\tH/E < (0.100, 0.075) = "              << els_hOverE().at(idx)
            //                                                 << "\tpasses = " << (isEB ? (els_hOverE().at(idx) < 0.100) : (els_hOverE().at(idx) < 0.075)) << endl;
            //cout << "\t# missing inner layers (<= 1, 1) = "  << els_exp_innerlayers().at(idx)
            //                                                 << "\tpasses = " << (els_exp_innerlayers().at(idx)==0)  << endl;
            //cout << "\tTriple charge agree = "               << (not isChargeFlip3agree(idx)) << endl;

            cuts_t cuts_passed = electronSelection(idx);
            //electronIdComponent_t wp2012_cuts = electronId_WP2012_v2(idx, MEDIUM);
            unsigned int wp2012_cuts = static_cast<unsigned int>(electronId_WP2012_v2(idx, MEDIUM));
            cout << sizeof(wp2012_cuts) << "\t" << sizeof(wp2012::DETAIN) << "\t" << sizeof(1) << endl;
            cout << "electron ID variables:"          << endl;
            cout << "\tpasses = "                     << samesign::isGoodLepton(id, idx) << endl;
            cout << "\tcut bits = "                   << bitset<64>(cuts_passed).to_string() << endl;
            cout << "\twp2012 bits = "                << bitset<64>(wp2012_cuts).to_string() << endl;
            cout << "\tcharge = "                     << els_charge().at(idx) << endl;
            cout << "\tpt = "                         << els_p4().at(idx).pt() << endl;
            cout << "\t|eta| = "                      << fabs(els_p4().at(idx).eta()) << endl;
            cout << "\tH/E < (0.120, 0.100)         = " << els_hOverE().at(idx) << "\tpasses = " << (isEB ? (els_hOverE().at(idx) < 0.10) : (els_hOverE().at(idx) < 0.075)) << endl;
            cout << "\tELEETA_240                   = " << static_cast<bool>(cuts_passed & (1ll << ELEETA_240                  ))  << endl;
            cout << "\tELENOMUON_010_SS             = " << static_cast<bool>(cuts_passed & (1ll << ELENOMUON_010_SS            ))  << endl;
            cout << "\tELENOTCONV_HITPATTERN_0MHITS = " << static_cast<bool>(cuts_passed & (1ll << ELENOTCONV_HITPATTERN_0MHITS))  << endl;
            cout << "\tELE_NOT_TRANSITION           = " << static_cast<bool>(cuts_passed & (1ll << ELE_NOT_TRANSITION          ))  << endl;
            cout << "\tELECHARGE_NOTFLIP3AGREE      = " << static_cast<bool>(cuts_passed & (1ll << ELECHARGE_NOTFLIP3AGREE     ))  << endl;
            cout << "\tELEID_WP2012_MEDIUM_NOISO    = " << static_cast<bool>(cuts_passed & (1ll << ELEID_WP2012_MEDIUM_NOISO   ))  << endl;
            cout << "\tELEID_WP2012_MEDIUM_NOISO::DETAIN        = " << static_cast<bool>(wp2012_cuts & (wp2012::DETAIN       )) << Form("\t%f < (0.004, 0.007)", els_dEtaIn().at(idx)) << endl;
            cout << "\tELEID_WP2012_MEDIUM_NOISO::DPHIIN        = " << static_cast<bool>(wp2012_cuts & (wp2012::DPHIIN       )) << Form("\t%f < (0.060, 0.030)", els_dPhiIn().at(idx)) << endl;
            cout << "\tELEID_WP2012_MEDIUM_NOISO::SIGMAIETAIETA = " << static_cast<bool>(wp2012_cuts & (wp2012::SIGMAIETAIETA)) << Form("\t%f < (0.010, 0.030)", els_sigmaIEtaIEta().at(idx)) << endl;
            cout << "\tELEID_WP2012_MEDIUM_NOISO::HOE           = " << static_cast<bool>(wp2012_cuts & (wp2012::HOE          )) << Form("\t%f < (0.120, 0.075)", els_hOverE().at(idx)) << endl;
            cout << "\tELEID_WP2012_MEDIUM_NOISO::OOEMOOP       = " << static_cast<bool>(wp2012_cuts & (wp2012::OOEMOOP      )) << Form("\t%f < (0.050, 0.050)", ooemoop) << endl;
            cout << "\tELEID_WP2012_MEDIUM_NOISO::D0VTX         = " << static_cast<bool>(wp2012_cuts & (wp2012::D0VTX        )) << Form("\t%f < (0.020, 0.020)", fabs(d0corr)) << endl;
            cout << "\tELEID_WP2012_MEDIUM_NOISO::DZVTX         = " << static_cast<bool>(wp2012_cuts & (wp2012::DZVTX        )) << Form("\t%f < (0.100, 0.100)", fabs(z0corr)) << endl;
            cout << "\tELEID_WP2012_MEDIUM_NOISO::VTXFIT        = " << static_cast<bool>(wp2012_cuts & (wp2012::VTXFIT       )) << Form("\t%d ", vtxFitConversion) << endl;
            cout << "\tELEID_WP2012_MEDIUM_NOISO::MHITS         = " << static_cast<bool>(wp2012_cuts & (wp2012::MHITS        )) << Form("\t%d == (0, 0)"       , els_exp_innerlayers().at(idx)) << endl;

            //* |eta| < 2.4
            //* not in trasistion region 1.4442 < |eta| < 1.556, where eta is from SC
            //* ∆R(e, µ) > 0.1 where µ is any muon passing SS selections above
            //* cut-based WP medium noise
            //   * |dη_in| < (0.004, 0.007)
            //   * |dφ_in| < (0.060, 0.030)
            //   * σ_iηiη < (0.010, 0.030)
            //   * H/E < (0.120, 0.100)
            //   * |1/ECAL - 1/Pin| < (0.050, 0.050)
            //   * |d0| < (0.020, 0.020)
            //   * |dz| < (0.100, 0.100)
            //   * vertex fit conversion is successful
            //   * # missing inner layers ≤ (1, 1)
            //   * p_T > 20 and pfiso (ρ*A_eff) < (0.150, 0.150)
            //   * p_T < 20 andpfiso (ρ*A_eff) <(0.100, 0.100)
            //* |d0_gsf_track(PV)| < 200 µm
            //* |dz_gsf_track(PV)| < 1 mm
            //* Conversion removal by veto of a good reconstructed conversion vertex
            //* # of missing exptec inner hits == 0
            //* triple charge agreement between CTF, GSF and Pixel-Super cluster charges
            //* H/E is required to be < 0.1 (0.075) in the barrel (end cap) to match the requirements of the trigger
            

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

            cout << "Muon ID variables:"             << endl;
            cout << "\tpasses = "                    << samesign::isGoodLepton(id, idx)                 << endl;
            cout << "\tcharge = "                    << mus_charge().at(idx)                            << endl;
            cout << "\tpt = "                        << mus_p4().at(idx).pt()                           << endl;
            cout << "\teta (< 2.4) = "               << mus_p4().at(idx).eta()                          << endl;
            cout << "\tglobal chi2/ndof (<10) = "    << mus_gfit_chi2().at(idx)/mus_gfit_ndof().at(idx) << endl;
            cout << "\tis global mu = "              << (((mus_type().at(idx)) & (1<<1)) != 0)          << endl;
            cout << "\tis PF mu = "                  << (mus_pid_PFMuon().at(idx)!=0)                   << endl;
            cout << "\thas a  matching track = "     << (trkidx >= 0)                                   << endl;
            cout << "\t# layers (>= 6) = "           << trks_nlayers().at(trkidx)                       << endl;
            cout << "\t# pixel hits (>=1) = "        << trks_valid_pixelhits().at(trkidx)               << endl;
            cout << "\t# valid stations (>=1) = "    << mus_gfit_validSTAHits().at(idx)                 << endl;
            cout << "\tECAL deposits (<4) = "        << mus_iso_ecalvetoDep().at(idx)                   << endl;
            cout << "\tHCAL deposits (<6) = "        << mus_iso_hcalvetoDep().at(idx)                   << endl;
            cout << "\td0 correct (< 0.02) = "       << d0corr                                          << endl;
            cout << "\tz0 correct (< 0.1) = "        << z0corr                                          << endl;
        }
        else
        {
            // not a valid id
            cout << "not a valid id: " << id << endl;
            return;
        }
    }
} // namespace at
