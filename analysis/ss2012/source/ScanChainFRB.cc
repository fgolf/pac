#include "ScanChainFRB.h"

// c++
#include <iostream>

// FakeRate baby 
#include "FakeRateBaby.h"

using namespace std;

// a simple function to test FakeRateScanChain
int ScanChainFRBTestAnalysis(long event)
{
    if (event%10000==0)
    {
        cout << "run = " <<  frb::run() << "\tevent = " << frb::evt() << endl;
    }
    return 0;
}
