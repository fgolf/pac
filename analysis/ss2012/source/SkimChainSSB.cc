#include "SkimChainSSB.h"

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

// a simple filter function to test SkimChainSSB
bool SkimChainSSBTestSelection(long event)
{
    if (event%10000==0)
    {
        cout << "run = " <<  ssb::run() << "\tevent = " << ssb::evt() << endl;
    }
    return true;
}
