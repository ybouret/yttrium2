
#include "y/apex/rational.hpp"

namespace Yttrium
{
    namespace Apex
    {
        Rational Rational::Mul(const Rational &lhs, const Rational &rhs)
        {
            const Integer num = lhs.numer * rhs.numer;
            const Natural den = lhs.denom * rhs.denom;
            return Rational(num,den);
        }
    }

}

namespace Yttrium
{
    namespace Apex
    {
        Rational Rational::Mul(const Rational &lhs, const Integer &rhs)
        {
            const Integer num = lhs.numer * rhs;
            return Rational(num,lhs.denom);
        }

        Rational Rational::Mul(const Integer &lhs, const Rational &rhs)
        {
            return Mul(rhs,lhs);
        }

    }
}

namespace Yttrium
{
    namespace Apex
    {
        Rational Rational::Mul(const Rational &lhs, const Natural &rhs)
        {
            const Integer num = lhs.numer * rhs;
            return Rational(num,lhs.denom);
        }

        Rational Rational::Mul(const Natural &lhs, const Rational &rhs)
        {
            return Mul(rhs,lhs);
        }

    }
}
