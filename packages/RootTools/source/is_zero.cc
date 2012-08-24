#include "rt/is_zero.h"
#include "rt/is_equal.h"

namespace rt
{
    bool is_zero(const int value)
    {
        return is_equal(value, 0);
    }

    bool is_zero(const long value)
    {
        return is_equal(value, 0l);
    }

    bool is_zero(const float value)
    {
        return is_equal(value, 0.0f);
    }

    bool is_zero(const double value)
    {
        return is_equal(value, 0.0);
    }

    bool is_zero(const long double value)
    {
        return is_equal(value, 0.0L);
    }


} // namespace rt

