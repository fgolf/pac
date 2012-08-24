#include "at/ScanChain.h"

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

//void progress(int nEventsTotal, int nEventsChain)
//{
//    int period = 1000;
//    if (nEventsTotal%1000 == 0) 
//    {
//        // xterm magic from L. Vacavant and A. Cerri
//        if (isatty(1)) 
//        {
//            if ((nEventsChain - nEventsTotal) > period)
//            {
//                float frac = (float)nEventsTotal/(nEventsChain*0.01);
//                printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%\033[0m\033[32m <---\033[0m\015", frac);
//                fflush(stdout);
//            }
//            else 
//            {
//                printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%\033[0m\033[32m <---\033[0m\015", 100.);
//                cout << endl;
//            }
//        }
//    }
//}

namespace at
{
    // a simple function to test ScanChain
    int ScanChainTestAnalysis(long event)
    {
        cout << "run = " <<  tas::evt_run() << "\tevent = " << tas::evt_event() << endl;
        return 0;
    }

} // namespace at

