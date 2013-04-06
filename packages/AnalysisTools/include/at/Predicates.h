#ifndef AT_PREDICATES_H
#define AT_PREDICATES_H

#include <cmath>
#include "Math/GenVector/VectorUtil.h"

namespace at
{
    // template function objects:
    template <typename T>
    struct SortByPt
    {
        bool operator () (const T& lhs, const T& rhs) const { return rhs.Pt() < lhs.Pt(); }
    };
    
    template <typename T>
    struct SortByDeltaM
    {
        SortByDeltaM(double M) : m_M(M) {}
        bool operator () (const T& lhs, const T& rhs) const { return fabs(lhs.M() - m_M) < fabs(rhs.M() - m_M); }
        double m_M;
    };
    
    template <typename T>
    struct SortByDeltaR
    {
        SortByDeltaR(const T& p4) : m_p4(p4) {}
        bool operator () (const T& lhs, const T& rhs) const 
        { 
            float delta_r1 = ROOT::Math::VectorUtil::DeltaR(lhs, m_p4); 
            float delta_r2 = ROOT::Math::VectorUtil::DeltaR(rhs, m_p4); 
            return delta_r1 < delta_r2; 
        }
        T m_p4;
    };
    
    template <typename T>
    struct ScalarSumPt
    {
        float operator () (const T& lhs, const T& rhs) const {return (rhs.Pt() + lhs.Pt());}
    };
    
    // function objects
    struct CompareCharPtrs
    {
        CompareCharPtrs(const char* value) : m_value(value) {}
        bool operator () (const char* value) {return strcmp(value, m_value)==0;}
        const char* m_value;
    };

	// template
    template <typename T>
	struct Initialize
	{
        Initialize(const T& value) : m_value(value) {}
        void operator () (T& value) {value = m_value;}
        T m_value;
	};
    
} // end namespace at

#endif // #define AT_PREDICATES_H

