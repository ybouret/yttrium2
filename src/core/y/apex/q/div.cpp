#include "y/apex/rational.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Apex
    {

        Rational Rational:: Div(const Rational &lhs, const Rational &rhs)
        {
            switch( Sign::Pair(lhs.numer.s,rhs.numer.s))
            {
                case Sign::ZZ:
                case Sign::NZ:
                case Sign::PZ:
                    throw Libc::Exception(EDOM,"%s division by %s zero",CallSign,CallSign);

                case Sign::ZN:
                case Sign::ZP:
                    break; // return 0

                case Sign::NN:
                case Sign::PP:
                {
                    const Natural num = lhs.numer.n * rhs.denom;
                    const Natural den = rhs.numer.n * lhs.denom;
                    return Rational(Positive,num,den);
                }

                case Sign::NP:
                case Sign::PN:
                {
                    const Natural num = lhs.numer.n * rhs.denom;
                    const Natural den = rhs.numer.n * lhs.denom;
                    return Rational(Negative,num,den);
                }


            }

            return Rational();
        }
    }

}
