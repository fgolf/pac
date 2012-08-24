#ifndef RT_IS_EQUAL_H
#define RT_IS_EQUAL_H

namespace rt
{
        bool is_equal(int lhs, int rhs);
        bool is_equal(long int lhs, long int rhs);
        bool is_equal(float lhs, float rhs);
        bool is_equal(double lhs, double rhs);
        bool is_equal(long double lhs, long double rhs);
        bool is_equal(float lhs, float rhs, float relative_tolerance, float absolute_tolerance);
        bool is_equal(double lhs, double rhs, double relative_tolerance, double absolute_tolerance);
        bool is_equal(long double lhs, long double rhs, long double relative_tolerance, long double absolute_tolerance);
} // namespace rt

#endif // RT_IS_EQUAL_H

