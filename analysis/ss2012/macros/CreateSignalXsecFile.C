#include <iostream>
#include "SignalBinInfo.h"
#include "at/Sample.h"
#include "rt/RootTools.h"

using namespace std;
using namespace at;

void SetBinContent(TH1* h, const float bin_value, const float xsec, const float xsec_unc_perc)
{
    int bin = h->FindBin(bin_value + 0.00001);
    h->SetBinContent(bin, xsec);
    h->SetBinError(bin, xsec*0.01*xsec_unc_perc);
    return;
}

// hard coded script to produce the xsec histogrmas
void CreateSignalXsecFile()
{
    rt::TH1Container hc;

    // sbottomtop (sbottom pair production -- T6ttWW)
    // --------------------------------------------------------------------------------- //
    // https://twiki.cern.ch/twiki/pub/CMS/SMST6ttWWMadgraph8TeV/Sbottom_8TeV_25GeV.txt
    ss::SignalBinInfo bin_info = ss::GetSignalBinInfo(at::Sample::sbottomtop);
    hc.Add(new TH1F ("h_xsec_sbottomtop", "Cross Section sbottom pair (T6ttWW);m_{#tilde{b}} (GeV); Cross Section (pb)", bin_info.nbinsx, bin_info.xmin, bin_info.xmax));
    SetBinContent(hc["h_xsec_sbottomtop"] , 325 , 1.25277   , 14.2875 ); 
    SetBinContent(hc["h_xsec_sbottomtop"] , 350 , 0.807323  , 14.3597 ); 
    SetBinContent(hc["h_xsec_sbottomtop"] , 375 , 0.531443  , 14.266  ); 
    SetBinContent(hc["h_xsec_sbottomtop"] , 400 , 0.35683   , 14.2848 ); 
    SetBinContent(hc["h_xsec_sbottomtop"] , 425 , 0.243755  , 14.0504 ); 
    SetBinContent(hc["h_xsec_sbottomtop"] , 450 , 0.169668  , 14.2368 ); 
    SetBinContent(hc["h_xsec_sbottomtop"] , 475 , 0.119275  , 14.6664 ); 
    SetBinContent(hc["h_xsec_sbottomtop"] , 500 , 0.0855847 , 14.9611 ); 
    SetBinContent(hc["h_xsec_sbottomtop"] , 525 , 0.0618641 , 15.4135 ); 
    SetBinContent(hc["h_xsec_sbottomtop"] , 550 , 0.0452067 , 15.8177 ); 
    SetBinContent(hc["h_xsec_sbottomtop"] , 575 , 0.0333988 , 16.2132 ); 
    SetBinContent(hc["h_xsec_sbottomtop"] , 600 , 0.0248009 , 16.6406 ); 
    SetBinContent(hc["h_xsec_sbottomtop"] , 625 , 0.0185257 , 17.0835 ); 
    SetBinContent(hc["h_xsec_sbottomtop"] , 650 , 0.0139566 , 17.56   ); 
    SetBinContent(hc["h_xsec_sbottomtop"] , 675 , 0.0106123 , 17.9891 ); 
    SetBinContent(hc["h_xsec_sbottomtop"] , 700 , 0.0081141 , 18.4146 ); 

    // t6ttww_x05 (sbottom pair production -- T6ttWW x=0.5)
    // --------------------------------------------------------------------------------- //
    // https://twiki.cern.ch/twiki/pub/CMS/SMST6ttWWScan2Madgraph8TeV/Sbottom_8TeV_25GeV.txt
    bin_info = ss::GetSignalBinInfo(at::Sample::t6ttww_x05);
    hc.Add(new TH1F ("h_xsec_t6ttww_x05", "Cross Section sbottom pair (T6ttWW, x=0.5);m_{#tilde{b}} (GeV); Cross Section (pb)", bin_info.nbinsx, bin_info.xmin, bin_info.xmax));
    SetBinContent(hc["h_xsec_t6ttww_x05"] , 200 , 18.5245   , 14.9147 );
    SetBinContent(hc["h_xsec_t6ttww_x05"] , 225 , 9.90959   , 14.9662 );
    SetBinContent(hc["h_xsec_t6ttww_x05"] , 250 , 5.57596   , 14.7529 );
    SetBinContent(hc["h_xsec_t6ttww_x05"] , 275 , 3.2781    , 14.7341 );
    SetBinContent(hc["h_xsec_t6ttww_x05"] , 300 , 1.99608   , 14.6905 );
    SetBinContent(hc["h_xsec_t6ttww_x05"] , 325 , 1.25277   , 14.2875 );
    SetBinContent(hc["h_xsec_t6ttww_x05"] , 350 , 0.807323  , 14.3597 );
    SetBinContent(hc["h_xsec_t6ttww_x05"] , 375 , 0.531443  , 14.266  );
    SetBinContent(hc["h_xsec_t6ttww_x05"] , 400 , 0.35683   , 14.2848 );
    SetBinContent(hc["h_xsec_t6ttww_x05"] , 425 , 0.243755  , 14.0504 );
    SetBinContent(hc["h_xsec_t6ttww_x05"] , 450 , 0.169668  , 14.2368 );
    SetBinContent(hc["h_xsec_t6ttww_x05"] , 475 , 0.119275  , 14.6664 );
    SetBinContent(hc["h_xsec_t6ttww_x05"] , 500 , 0.0855847 , 14.9611 );
    SetBinContent(hc["h_xsec_t6ttww_x05"] , 525 , 0.0618641 , 15.4135 );
    SetBinContent(hc["h_xsec_t6ttww_x05"] , 550 , 0.0452067 , 15.8177 );
    SetBinContent(hc["h_xsec_t6ttww_x05"] , 575 , 0.0333988 , 16.2132 );
    SetBinContent(hc["h_xsec_t6ttww_x05"] , 600 , 0.0248009 , 16.6406 );
    SetBinContent(hc["h_xsec_t6ttww_x05"] , 625 , 0.0185257 , 17.0835 );
    SetBinContent(hc["h_xsec_t6ttww_x05"] , 650 , 0.0139566 , 17.56   );
    SetBinContent(hc["h_xsec_t6ttww_x05"] , 675 , 0.0106123 , 17.9891 );
    SetBinContent(hc["h_xsec_t6ttww_x05"] , 700 , 0.0081141 , 18.4146 );

    // t6ttww_x08 (sbottom pair production -- T6ttWW x=0.8)
    // --------------------------------------------------------------------------------- //
    // https://twiki.cern.ch/twiki/pub/CMS/SMST6ttWWScan3Madgraph8TeV/Sbottom_8TeV_25GeV.txt
    bin_info = ss::GetSignalBinInfo(at::Sample::t6ttww_x08);
    hc.Add(new TH1F ("h_xsec_t6ttww_x08", "Cross Section sbottom pair (T6ttWW, x=0.8);m_{#tilde{b}} (GeV); Cross Section (pb)", bin_info.nbinsx, bin_info.xmin, bin_info.xmax));
    SetBinContent(hc["h_xsec_t6ttww_x08"] , 200 , 18.5245   , 14.9147 );
    SetBinContent(hc["h_xsec_t6ttww_x08"] , 225 , 9.90959   , 14.9662 );
    SetBinContent(hc["h_xsec_t6ttww_x08"] , 250 , 5.57596   , 14.7529 );
    SetBinContent(hc["h_xsec_t6ttww_x08"] , 275 , 3.2781    , 14.7341 );
    SetBinContent(hc["h_xsec_t6ttww_x08"] , 300 , 1.99608   , 14.6905 );
    SetBinContent(hc["h_xsec_t6ttww_x08"] , 325 , 1.25277   , 14.2875 );
    SetBinContent(hc["h_xsec_t6ttww_x08"] , 350 , 0.807323  , 14.3597 );
    SetBinContent(hc["h_xsec_t6ttww_x08"] , 375 , 0.531443  , 14.266  );
    SetBinContent(hc["h_xsec_t6ttww_x08"] , 400 , 0.35683   , 14.2848 );
    SetBinContent(hc["h_xsec_t6ttww_x08"] , 425 , 0.243755  , 14.0504 );
    SetBinContent(hc["h_xsec_t6ttww_x08"] , 450 , 0.169668  , 14.2368 );
    SetBinContent(hc["h_xsec_t6ttww_x08"] , 475 , 0.119275  , 14.6664 );
    SetBinContent(hc["h_xsec_t6ttww_x08"] , 500 , 0.0855847 , 14.9611 );
    SetBinContent(hc["h_xsec_t6ttww_x08"] , 525 , 0.0618641 , 15.4135 );
    SetBinContent(hc["h_xsec_t6ttww_x08"] , 550 , 0.0452067 , 15.8177 );
    SetBinContent(hc["h_xsec_t6ttww_x08"] , 575 , 0.0333988 , 16.2132 );
    SetBinContent(hc["h_xsec_t6ttww_x08"] , 600 , 0.0248009 , 16.6406 );
    SetBinContent(hc["h_xsec_t6ttww_x08"] , 625 , 0.0185257 , 17.0835 );
    SetBinContent(hc["h_xsec_t6ttww_x08"] , 650 , 0.0139566 , 17.56   );
    SetBinContent(hc["h_xsec_t6ttww_x08"] , 675 , 0.0106123 , 17.9891 );
    SetBinContent(hc["h_xsec_t6ttww_x08"] , 700 , 0.0081141 , 18.4146 );

    // T1tttt (sbottom pair production -- T1tttt)
    // --------------------------------------------------------------------------------- //
    // https://twiki.cern.ch/twiki/bin/view/LHCPhysics/SUSYCrossSections8TeVgluglu
    bin_info = ss::GetSignalBinInfo(at::Sample::t1tttt);
    hc.Add(new  TH1F("h_xsec_t1tttt", "Cross Section T1tttt;m_{#tilde{g}} (GeV); Cross Section (pb)", bin_info.nbinsx, bin_info.xmin, bin_info.xmax));
    SetBinContent(hc["h_xsec_t1tttt"] , 200  , 1010.1      , 15.3749 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 225  , 540.437     , 15.0907 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 250  , 302.3       , 14.8648 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 275  , 176.213     , 14.9861 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 300  , 106.269     , 14.848  ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 325  , 66.2653     , 14.9073 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 350  , 42.5663     , 14.9279 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 375  , 28.0354     , 15.0177 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 400  , 18.8721     , 15.0928 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 425  , 12.8817     , 14.8223 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 450  , 8.93257     , 15.0053 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 475  , 6.31553     , 15.3793 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 500  , 4.52485     , 15.7449 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 525  , 3.27008     , 16.1175 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 550  , 2.38869     , 16.4895 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 575  , 1.76075     , 16.8606 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 600  , 1.31429     , 17.2269 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 625  , 0.985407    , 17.5919 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 650  , 0.744472    , 18.0043 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 675  , 0.56624     , 18.3422 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 700  , 0.433971    , 18.6986 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 725  , 0.33408     , 19.0508 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 750  , 0.258598    , 19.4346 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 775  , 0.201354    , 19.7494 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 800  , 0.157399    , 20.1277 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 825  , 0.123451    , 20.6589 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 850  , 0.0966803   , 21.2994 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 875  , 0.0762312   , 22.019  ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 900  , 0.060276    , 22.6836 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 925  , 0.0478794   , 23.4801 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 950  , 0.0381246   , 24.1578 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 975  , 0.0304177   , 24.9003 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1000 , 0.0243547   , 25.6713 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1025 , 0.0195439   , 26.3787 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1050 , 0.0156931   , 26.929  ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1075 , 0.0126249   , 27.6365 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1100 , 0.0101744   , 28.3906 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1125 , 0.00823026  , 29.2287 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1150 , 0.00666673  , 30.0712 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1175 , 0.0054104   , 30.9359 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1200 , 0.00440078  , 31.7987 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1225 , 0.00357858  , 32.5751 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1250 , 0.00291565  , 33.6088 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1275 , 0.00238091  , 34.3786 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1300 , 0.00194443  , 35.3454 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1325 , 0.00158945  , 36.3322 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1350 , 0.00129951  , 37.0468 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1375 , 0.00106538  , 38.1495 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1400 , 0.000871201 , 38.9186 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1425 , 0.000714083 , 39.8536 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1450 , 0.00058599  , 40.8174 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1475 , 0.000481062 , 41.8322 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1500 , 0.000394612 , 42.8374 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1525 , 0.000323984 , 43.9886 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1550 , 0.000265533 , 45.1206 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1575 , 0.000218539 , 46.1454 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1600 , 0.000179423 , 47.269  ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1625 , 0.000147446 , 48.273  ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1650 , 0.000121361 , 49.3527 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1675 , 9.95545e-05 , 50.3339 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1700 , 8.17761e-05 , 51.3378 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1725 , 6.71419e-05 , 52.4157 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1750 , 5.51497e-05 , 53.4636 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1775 , 4.52786e-05 , 54.7372 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1800 , 3.71771e-05 , 55.8389 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1825 , 3.04796e-05 , 56.8583 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1850 , 2.50085e-05 , 58.2816 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1875 , 2.04823e-05 , 59.5237 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1900 , 1.67835e-05 , 60.518  ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1925 , 1.37589e-05 , 61.6823 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1950 , 1.12426e-05 , 62.789  ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 1975 , 9.20837e-06 , 64.0165 ); 
    SetBinContent(hc["h_xsec_t1tttt"] , 2000 , 7.52864e-06 , 65.128  ); 

    // T1tttt (sbottom pair production -- T1tttt scans)
    // --------------------------------------------------------------------------------- //
    // https://twiki.cern.ch/twiki/bin/view/LHCPhysics/SUSYCrossSections8TeVgluglu
    bin_info = ss::GetSignalBinInfo(at::Sample::t1tttt_scans);
    hc.Add(dynamic_cast<TH1F*>(hc["h_xsec_t1tttt"]->Clone("h_xsec_t1tttt_scans")));
    hc["h_xsec_t1tttt_scans"]->SetTitle("Cross Section T1tttt (scans);m_{#tilde{g}} (GeV); Cross Section (pb)");
   
    // T5tttt (sbottom pair production -- T5tttt)
    // --------------------------------------------------------------------------------- //
    // https://twiki.cern.ch/twiki/bin/view/LHCPhysics/SUSYCrossSections8TeVgluglu
    bin_info = ss::GetSignalBinInfo(at::Sample::t5tttt);
    hc.Add(new  TH1F("h_xsec_t5tttt", "Cross Section T5tttt;m_{#tilde{g}} (GeV); Cross Section (pb)", bin_info.nbinsx, bin_info.xmin, bin_info.xmax));
    SetBinContent(hc["h_xsec_t5tttt"] , 800  , 0.157399    , 20.1277 ); 
    SetBinContent(hc["h_xsec_t5tttt"] , 825  , 0.123451    , 20.6589 ); 
    SetBinContent(hc["h_xsec_t5tttt"] , 850  , 0.0966803   , 21.2994 ); 
    SetBinContent(hc["h_xsec_t5tttt"] , 875  , 0.0762312   , 22.019  ); 
    SetBinContent(hc["h_xsec_t5tttt"] , 900  , 0.060276    , 22.6836 ); 
    SetBinContent(hc["h_xsec_t5tttt"] , 925  , 0.0478794   , 23.4801 ); 
    SetBinContent(hc["h_xsec_t5tttt"] , 950  , 0.0381246   , 24.1578 ); 
    SetBinContent(hc["h_xsec_t5tttt"] , 975  , 0.0304177   , 24.9003 ); 
    SetBinContent(hc["h_xsec_t5tttt"] , 1000 , 0.0243547   , 25.6713 ); 
    SetBinContent(hc["h_xsec_t5tttt"] , 1025 , 0.0195439   , 26.3787 ); 
    SetBinContent(hc["h_xsec_t5tttt"] , 1050 , 0.0156931   , 26.929  ); 
    SetBinContent(hc["h_xsec_t5tttt"] , 1075 , 0.0126249   , 27.6365 ); 
    SetBinContent(hc["h_xsec_t5tttt"] , 1100 , 0.0101744   , 28.3906 ); 
    SetBinContent(hc["h_xsec_t5tttt"] , 1125 , 0.00823026  , 29.2287 ); 
    SetBinContent(hc["h_xsec_t5tttt"] , 1150 , 0.00666673  , 30.0712 ); 
    SetBinContent(hc["h_xsec_t5tttt"] , 1175 , 0.0054104   , 30.9359 ); 
    SetBinContent(hc["h_xsec_t5tttt"] , 1200 , 0.00440078  , 31.7987 ); 
    SetBinContent(hc["h_xsec_t5tttt"] , 1225 , 0.00357858  , 32.5751 ); 

    // TChiwz (chargino-neutralino production -- TChiwz)
    //https://twiki.cern.ch/twiki/pub/CMS/EwkinoSignalmodels/8TeVc1pn2_finer.xsec
    //https://twiki.cern.ch/twiki/pub/CMS/EwkinoSignalmodels/8TeVc1pn2_finer.xsec
    // --------------------------------------------------------------------------------- //

    bin_info = ss::GetSignalBinInfo(at::Sample::tchiwh);
    hc.Add(new TH1F ("h_xsec_tchiwh", "Cross Section TChiwz;m_{#tilde{3chi^{3pm}}} (GeV); Cross Section (pb)", bin_info.nbinsx, bin_info.xmin, bin_info.xmax));
    SetBinContent(hc["h_xsec_tchiwh"], 100  ,7.070000e+00 + 4.019153e+00, sqrt(pow(4.863176e-01,2) + pow(2.951105e-01,2))); 
    SetBinContent(hc["h_xsec_tchiwh"], 150  ,1.580000e+00 + 8.079838e-01, sqrt(pow(8.002465e-02,2) + pow(4.629344e-02,2))); 
    SetBinContent(hc["h_xsec_tchiwh"], 200  ,5.350000e-01 + 2.502323e-01, sqrt(pow(2.463968e-02,2) + pow(1.265101e-02,2))); 
    SetBinContent(hc["h_xsec_tchiwh"], 250  ,2.220000e-01 + 9.589456e-02, sqrt(pow(9.652981e-03,2) + pow(4.552337e-03,2))); 
    SetBinContent(hc["h_xsec_tchiwh"], 300  ,1.040000e-01 + 4.192331e-02, sqrt(pow(4.620926e-03,2) + pow(1.990183e-03,2))); 
    SetBinContent(hc["h_xsec_tchiwh"], 350  ,5.340000e-02 + 2.033198e-02, sqrt(pow(2.144587e-03,2) + pow(9.880333e-04,2))); 
    
    // done
    hc.Write("data/xsec/susy_xsec.root");
}
