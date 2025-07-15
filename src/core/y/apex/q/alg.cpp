
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

        Rational Rational:: sqrt() const
        {
            const Integer n = numer.sqrt();
            Natural       d = denom.sqrt();
            const Natural & N = numer.n;
            const Natural & D = denom;
            const Natural   threshold = D * n.n.sqr();
            while( d.sqr() * N < threshold) ++d;
            return Rational(n,d);
        }
    }

}
