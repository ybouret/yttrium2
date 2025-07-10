
#include "y/apex/rational.hpp"

namespace Yttrium
{
    namespace Apex
    {
        Rational Rational:: abs() const
        {
            const Integer N = numer.abs();
            return Rational(N,denom);
        }
    }

}
