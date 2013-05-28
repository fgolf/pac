#include "SkimChainOS.impl.h"

// c++
#include <iostream>
#include <stdexcept>
#include <set>

// ROOT
#include "TChain.h"
#include "TTreeCache.h"
#include "TBenchmark.h"

// SSB baby
#include "RPVSTOP2012_OS.h"

// tools
#include "rt/RootTools.h"

using namespace std;

// a simple filter function to test SkimChainSSB
bool SkimChainOSTestSelection(long event)
{
    if (event%10000==0)
    {
        cout << "run = " <<  rpvstop_os::run() << "\tevent = " << rpvstop_os::evt() << endl;
    }
    return true;
}
