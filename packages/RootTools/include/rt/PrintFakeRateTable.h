#ifndef RT_PRINTFAKERATETABLE_H
#define RT_PRINTFAKERATETABLE_H

#include <iostream>
class TH2;

namespace rt
{
    void PrintFakeRateTable(TH2* hist, std::ostream& out = std::cout);

} // namespace rt

#endif // RT_PRINTFAKERATETABLE_H

