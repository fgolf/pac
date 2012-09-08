#include "at/SkimChain.h"

// c++
#include <iostream>
#include <stdexcept>
#include <set>

// ROOT
#include "TChain.h"
#include "TTreeCache.h"
#include "TBenchmark.h"

// CMS2
#include "CMS2.h"

// tools
#include "rt/RootTools.h"

using namespace std;

// a simple filter function to test SkimChain
bool SkimChainTestSelection(long event)
{
    if (event%10000==0)
    {
        cout << "run = " <<  tas::evt_run() << "\tevent = " << tas::evt_event() << endl;
    }
    return true;
}
