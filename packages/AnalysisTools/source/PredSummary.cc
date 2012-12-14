#include "at/PredSummary.h"
#include "rt/RootTools.h"

using namespace rt;
using namespace std;

namespace at
{
    // Pred implementation
    // ----------------------------------------------------//

    // construct
    Pred::Pred(float v, float e)
        : value(v)
        , error(e)
    {
    }

    Pred::Pred(const std::pair<float, float>& v)
        : value(v.first)
        , error(v.second)
    {
    }

    Pred::Pred(const std::pair<double, double>& v)
        : value(v.first)
        , error(v.second)
    {
    }

    // methods:
    Pred& Pred::operator+=(const Pred& rhs)
    {
        Pred temp(value + rhs.value, 0.0);
        if (rt::is_zero(value) && rt::is_zero(rhs.value))
        {
            temp.error = std::max(error, rhs.error);
        }
        else if (rt::is_zero(value))
        {
            temp.error = rhs.error;
        }
        else if (rt::is_zero(rhs.value))
        {
            temp.error = error;
        }
        else
        {
            temp.error = sqrt(error*error + rhs.error*rhs.error);
        }
        std::swap(*this, temp);
        return *this; 
    }

    Pred& Pred::operator-=(const Pred& rhs)
    {
        Pred temp(value - rhs.value, 0.0);
        if (rt::is_zero(value) && rt::is_zero(rhs.value))
        {
            temp.error = std::max(error, rhs.error);
        }
        else if (rt::is_zero(value))
        {
            temp.error = rhs.error;
        }
        else if (rt::is_zero(rhs.value))
        {
            temp.error = error;
        }
        else
        {
            temp.error = sqrt(error*error + rhs.error*rhs.error);
        }
        std::swap(*this, temp);
        return *this; 
    }

    string Pred::str(const string& format_string) const
    {
        return pm(value, error, format_string); 
    }


    // non member methods
    bool is_empty(const Pred& pred)
    {
        return rt::is_zero(pred.value) && rt::is_zero(pred.error);
    }

    Pred operator*(float scale, const Pred& fp)
    {
        Pred result(scale * fp.value, scale * fp.error);
        return result; 
    }

    Pred operator+(const Pred& lhs, const Pred& rhs)
    {
        return Pred(lhs) += rhs; 
    }

    Pred operator-(const Pred& lhs, const Pred& rhs)
    {
        return Pred(lhs) -= rhs; 
    }

    std::ostream& operator << (std::ostream& os, const Pred& p)
    {
        os << Form("%1.3f +/- %1.3f", p.value, p.error);
        return os;
    }

    // FakeRateSummary implementation
    // ----------------------------------------------------//

    // construct:
    PredSummary::PredSummary()
        : ee(0.0, 0.0)
        , mm(0.0, 0.0)
        , em(0.0, 0.0)
        , ll(0.0, 0.0)
        , em_mufo(0.0, 0.0)
        , em_elfo(0.0, 0.0)
    {
    }

    PredSummary::PredSummary(const Pred& ee_, const Pred& mm_, const Pred& em_)
        : ee(ee_)
        , mm(mm_)
        , em(em_)
        , ll(ee + mm + em)
        , em_mufo(0.0, 0.0)
        , em_elfo(0.0, 0.0)
    {
    }

    PredSummary::PredSummary(const Pred& ee_, const Pred& mm_, const Pred& em_, const Pred& me_)
        : ee(ee_)
        , mm(mm_)
        , em(em_ + me_)
        , ll(ee + mm + em)
        , em_mufo(me_)
        , em_elfo(em_)
    {
    }

    PredSummary& PredSummary::operator+=(const PredSummary& rhs)
    {
        PredSummary temp(this->ee + rhs.ee, this->mm + rhs.mm, this->em_elfo + rhs.em_elfo, this->em_mufo + this->em_mufo);
        std::swap(*this, temp);
        return *this; 
    }

    PredSummary& PredSummary::operator-=(const PredSummary& rhs)
    {
        PredSummary temp(this->ee - rhs.ee, this->mm - rhs.mm, this->em_elfo - rhs.em_elfo, this->em_mufo - this->em_mufo);
        std::swap(*this, temp);
        return *this; 
    }

    PredSummary operator+(const PredSummary& lhs, const PredSummary& rhs)
    {
        return PredSummary(lhs) += rhs; 
    }

    PredSummary operator-(const PredSummary& lhs, const PredSummary& rhs)
    {
        return PredSummary(lhs) -= rhs; 
    }

    std::ostream& operator << (std::ostream& os, const PredSummary& p)
    {
        os << "ee: " << p.ee << " em: " << p.em << " mm: " << p.mm << " ll: " << p.ll; 
        if (!is_empty(p.em_elfo))
        {
            os << " em (mu fake): " << p.em_mufo;
        }
        if (!is_empty(p.em_elfo))
        {
            os << " em (el fake): " << p.em_elfo;
        }
        return os;
    }

} // namespace at
