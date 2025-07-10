
#include "y/apex/rational.hpp"

namespace Yttrium
{
    namespace Apex
    {

        SignType Rational:: Compare(const Rational &lhs, const Rational &rhs)
        {
            switch( Sign::Pair(lhs.numer.s,rhs.numer.s))
            {
                case Sign::ZZ:
                    return __Zero__;

                case Sign::NZ:
                case Sign::NP:
                case Sign::ZP:
                    return Negative;

                case Sign::PZ:
                case Sign::PN:
                case Sign::ZN:
                    return Positive;

                case Sign::NN:
                case Sign::PP:
                    break;
            }

            const Integer L = lhs.numer * rhs.denom;
            const Integer R = rhs.numer * lhs.denom;
            return (L-R).s;
        }


    }

}
