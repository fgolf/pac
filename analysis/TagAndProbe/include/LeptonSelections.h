#ifndef LEPTONSELECTIONS_H
#define LEPTONSELECTIONS_H

namespace tp
{
    // DON'T CHANGE ORDER
    struct LeptonSelection
    {
        enum value_type
        {
            PassEleSC                       = 1UL<<0,  // 
            PassEleReco                     = 1UL<<1,  // 
            PassEleFO                       = 1UL<<2,  // 
            PassEleID                       = 1UL<<3,  // 
            PassEleIso                      = 1UL<<4,  //
            PassEleFOICHEP2012              = 1UL<<5,  // 
            PassEleIDICHEP2012              = 1UL<<6,  // 
            PassEleIsoICHEP2012             = 1UL<<7,  //
            PassMuCTFTrack                  = 1UL<<8,  // 
            PassMuGlobalMuon                = 1UL<<9,  // 
            PassMuTrackerMuon               = 1UL<<10, //
            PassMuIsPF                      = 1UL<<11, //
            PassMuIsHPASS                   = 1UL<<12, //
            PassMuIsPOGTight                = 1UL<<13, //
            PassMuIsPOGSoft                 = 1UL<<14, //
            PassMuFO                        = 1UL<<15, //
            PassMuID                        = 1UL<<16, //
            PassMuIso                       = 1UL<<17, //
            PassMuFOICHEP2012               = 1UL<<18, //
            PassMuIDICHEP2012               = 1UL<<19, //
            PassMuIsoICHEP2012              = 1UL<<20, //
            PassPhotonID                    = 1UL<<21, //
            PassPhotonIso                   = 1UL<<22  //
        };
    };

    struct EventSelection 
    {
        enum value_type
        {
            ZeeTagAndProbe                  = 1UL<<0,  // 
            ZmmTagAndProbe                  = 1UL<<1,  // 
            OniaEETagAndProbe               = 1UL<<2,  // 
            OniaMuMuTagAndProbe             = 1UL<<3,  // 
            QCDFakeEle                      = 1UL<<4,  //
            QCDFakeMu                       = 1UL<<5,  // 
            ZJetsFakeEleSelection           = 1UL<<6,  // 
            ZJetsFakeMuSelection            = 1UL<<7,  // 
            PhotonSelection                 = 1UL<<8   //
        };
    };

} // namespace tp

#endif // LEPTONSELECTIONS_H
