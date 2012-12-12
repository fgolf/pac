#ifndef AT_PREDSUMMARY_H
#define AT_PREDSUMMARY_H

#include <string>
#include <utility>

namespace at
{
    // struct to hold the value/error of the pred
    // ----------------------------------------------------//

    struct Pred
    {
        Pred(float v, float e);
        Pred(const std::pair<float, float>& v);
        Pred(const std::pair<double, double>& v);
        float value;
        float error;

        // methods:
        Pred& operator+=(const Pred& rhs);
        Pred& operator-=(const Pred& rhs);
        std::string str(const std::string& format = "1.3") const;
    };

    // non member methods:
    bool is_empty(const Pred& p);
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
        PredSummary(const Pred& ee_, const Pred& mm_, const Pred& em_, const Pred& me_);
        PredSummary& operator+=(const PredSummary& rhs);
        PredSummary& operator-=(const PredSummary& rhs);

        Pred ee;
        Pred mm;
        Pred em;
        Pred ll;
        Pred em_mufo;  // optional: em channel where the muon is the FO
        Pred em_elfo;  // optional: em channel where the electron is the FO
    };

    // non member methods
    PredSummary operator-(const PredSummary& lhs, const PredSummary& rhs);
    PredSummary operator+(const PredSummary& lhs, const PredSummary& rhs);
    std::ostream& operator << (std::ostream& os, const PredSummary& p);

} // namepace at

#endif // AT_PREDSUMMARY_H
