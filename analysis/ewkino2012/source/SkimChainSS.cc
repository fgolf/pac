#include "SkimChainSS.impl.h"

// c++
#include <iostream>
#include <stdexcept>
#include <set>

// ROOT
#include "TChain.h"
#include "TTreeCache.h"
#include "TBenchmark.h"

// SSB baby
#include "EWKINO2012_SS.h"

// tools
#include "rt/RootTools.h"

using namespace std;

// a simple filter function to test SkimChainSSB
bool SkimChainSSTestSelection(long event)
{
    if (event%10000==0)
    {
        cout << "run = " <<  ewkino_ss::run() << "\tevent = " << ewkino_ss::evt() << endl;
    }
    return true;
}
