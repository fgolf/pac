#ifndef PREDSUMMARY_H
#define PREDSUMMARY_H

#include <string>

// struct to hold the value/error of the pred
// ----------------------------------------------------//

struct Pred
{
    Pred(float v, float e);
    float value;
    float error;

    // methods:
    Pred& operator+=(const Pred& rhs);
    Pred& operator-=(const Pred& rhs);
    std::string str(const std::string& format = "1.3") const;
};

// non member methods:
Pred operator*(float scale, const Pred& fp);
Pred operator-(const Pred& lhs, const Pred& rhs);
Pred operator+(const Pred& lhs, const Pred& rhs);
std::ostream& operator << (std::ostream& os, const Pred& p);

// struct to hold the different channels
// ----------------------------------------------------//

struct PredSummary
{
    PredSummary();
    PredSummary(const Pred& ee_, const Pred& mm_, const Pred& em_);
    Pred ee;
    Pred mm;
    Pred em;
    Pred ll;
};

#endif // PREDSUMMARY_H
