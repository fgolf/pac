#include "FakeRateType.h"
#include <stdlib.h>

enum FakeRateType getFakeRateType (int eormu1, bool lep1isFO, bool lep1isNum, int eormu2, bool lep2isFO, bool lep2isNum) {
    if (lep1isNum && lep2isNum)
        return NUM;
    else if (lep1isFO && lep2isNum) {
        if (abs(eormu1) == 11)
            return E_FAKE;
        else
            return MU_FAKE;
    }
    else if (lep1isNum && lep2isFO) {
        if (abs(eormu2) == 11)
            return E_FAKE;
        else
            return MU_FAKE;
    }
    else {
        if (abs(eormu1) == 11 && abs(eormu2) == 11)
            return EE_FAKE;
        else if (abs(eormu1) == 13 && abs(eormu2) == 13)
            return MUMU_FAKE;
        else
            return EMU_FAKE;
    }        
}
