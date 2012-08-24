#include "at/LorentzVectorObject.h"

namespace at
{
    // class LorentzVectorObject 
    // constuct:
    LorentzVectorObject::LorentzVectorObject(const LorentzVector& p4)
        : m_p4(&p4)
    {
    }

    // destroy:
    LorentzVectorObject::~LorentzVectorObject() 
    {
    }

} // namespace at

