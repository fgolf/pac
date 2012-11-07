#ifndef FAKERATEBABYWRAPPER_H
#define FAKERATEBABYWRAPPER_H

// simple wrapper to fake_rate_baby to use with at::ScanChain()

class FakeRateBaby;

void Init(FakeRateBaby& fake_rate_baby, TTree* tree);
void GetEntry(FakeRateBaby& fake_rate_baby, long event);
bool IsRealData(FakeRateBaby& fake_rate_baby);
void LoadAllBranches(FakeRateBaby& fake_rate_baby);
unsigned int Run(FakeRateBaby& fake_rate_baby);
unsigned int LumiBlock(FakeRateBaby& fake_rate_baby);
unsigned int Event(FakeRateBaby& fake_rate_baby);

#endif //#efine FakeRateBabyWRAPPER_H
