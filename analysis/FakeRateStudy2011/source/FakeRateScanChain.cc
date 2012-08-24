#include "FakeRateScanChain.h"

// c++
#include <iostream>
#include <stdexcept>
#include <set>

// ROOT
#include "TChain.h"
#include "TTreeCache.h"
#include "TBenchmark.h"

// FakeRate baby 
#include "FakeRateBaby.h"

// tools
#include "rt/RootTools.h"

using namespace std;

// a simple function to test FakeRateScanChain
int FakeRateScanChainTestAnalysis(long event)
{
    if (event%10000==0)
    {
        cout << "run = " <<  frb::run() << "\tevent = " << frb::evt() << endl;
    }
    return 0;
}
