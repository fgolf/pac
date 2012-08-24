#include "ScanChainSSB.h"

// c++
#include <iostream>
#include <stdexcept>
#include <set>

// ROOT
#include "TChain.h"
#include "TTreeCache.h"
#include "TBenchmark.h"

// SSB baby
#include "SSB2012.h"

// tools
#include "rt/RootTools.h"

using namespace std;

// a simple function to test ScanChainSSB
int ScanChainSSBTestAnalysis(long event)
{
    if (event%10000==0)
    {
        cout << "run = " <<  ssb::run() << "\tevent = " << ssb::evt() << endl;
    }
    return 0;
}
