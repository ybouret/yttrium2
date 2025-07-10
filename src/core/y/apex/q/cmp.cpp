
#include "y/apex/rational.hpp"

namespace Yttrium
{
    namespace Apex
    {

        SignType Rational:: Compare(const Rational &lhs, const Rational &rhs)
        {
            const Integer L = lhs.numer * rhs.denom;
            const Integer R = rhs.numer * lhs.denom;
            return (L-R).s;
        }


    }

}
