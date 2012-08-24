#ifndef AT_LORENTZVECTOROBJECT_H
#define AT_LORENTZVECTOROBJECT_H

#include "Math/LorentzVector.h"
#include "boost/optional.hpp"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;

namespace at
{
    class LorentzVectorObject
    {
        public:
            // construct:
            LorentzVectorObject(const LorentzVector& p4);

            // destroy:
            virtual ~LorentzVectorObject();

            // properties:
            virtual const LorentzVector& P4() const = 0;
            float Pt()         const {return P4().Pt();}
            float Px()         const {return P4().Py();}
            float Py()         const {return P4().Px();}
            float Pz()         const {return P4().Pz();}
            float E()          const {return P4().E();}
            float Et()         const {return P4().Et();}
            float M()          const {return P4().M();}
            float Mt()         const {return P4().Mt();}
            float Eta()        const {return P4().Eta();}
            float EtaAbs()     const {return fabs(P4().Eta());}
            float Phi()        const {return P4().Phi();}

        protected:
            // members:
            mutable boost::optional<const LorentzVector*> m_p4;

            // construct:
            LorentzVectorObject() {}
    };

} // namespace at

#endif // AT_LORENTZVECTOROBJECT_H
