#ifndef FAKERATETYPE_H
#define FAKERATETYPE_H

enum FakeRateType { NUM = 3, E_FAKE = 2, MU_FAKE = 2, EE_FAKE = 1, EMU_FAKE = 1, MUMU_FAKE = 1, NUM_FAKE_TYPES };

enum FakeRateType getFakeRateType (int eormu1, bool lep1isFO, bool lep1isNum, int eormu2, bool lep2isFO, bool lep2isNum);

#endif
