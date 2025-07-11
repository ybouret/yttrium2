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



namespace Yttrium
{
    namespace Apex
    {
        Rational Rational:: Div(const Rational &lhs, const Integer &rhs)
        {
            switch(rhs.s)
            {
                case __Zero__:
                    break; // throw

                case Positive:
                {
                    const Natural den = lhs.denom * rhs.n;
                    return Rational(lhs.numer,den);
                }

                case Negative:
                {
                    const Natural den = lhs.denom * rhs.n;
                    return Rational(lhs.numer,den).neg();
                }

            }
            throw Libc::Exception(EDOM,"%s division by %s zero",CallSign,Integer::CallSign);
        }


        Rational Rational:: Div(const Integer  &lhs, const Rational &rhs)
        {

            switch( Sign::Pair(lhs.s,rhs.numer.s))
            {
                case Sign::ZZ:
                case Sign::PZ:
                case Sign::NZ:
                    throw Libc::Exception(EDOM,"%s division by %s zero",Integer::CallSign,CallSign);

                case Sign::ZN:
                case Sign::ZP:
                    break; // return 0

                case Sign::NN:
                case Sign::PP:
                {
                    const Natural num = lhs.n * rhs.denom;
                    return Rational(Positive,num,rhs.numer.n);
                }

                case Sign::NP:
                case Sign::PN:
                {
                    const Natural num = lhs.n * rhs.denom;
                    return Rational(Negative,num,rhs.numer.n);
                }


            }

            return Rational();
        }

    }

}


namespace Yttrium
{
    namespace Apex
    {
        Rational Rational:: Div(const Rational &lhs, const integer_t rhs)
        {
            const SignType rhs_s = Sign::Of(rhs);
            switch(rhs_s)
            {
                case __Zero__:
                    break; // throw

                case Positive:
                {
                    const Natural den = lhs.denom * natural_t(rhs);
                    return Rational(lhs.numer,den);
                }

                case Negative:
                {
                    const Natural den = lhs.denom * natural_t(-rhs);
                    return Rational(lhs.numer,den).neg();
                }

            }
            throw Libc::Exception(EDOM,"%s division by integral zero",CallSign);
        }

        Rational Rational:: Div(const integer_t lhs, const Rational &rhs)
        {
            const SignType lhs_s = Sign::Of(lhs);
            switch( Sign::Pair(lhs_s,rhs.numer.s))
            {
                case Sign::ZZ:
                case Sign::PZ:
                case Sign::NZ:
                    throw Libc::Exception(EDOM,"%s division by %s zero",Integer::CallSign,CallSign);

                case Sign::ZN:
                case Sign::ZP:
                    break; // return 0

                case Sign::NN:
                {
                    const Natural num = natural_t(-lhs) * rhs.denom;
                    return Rational(Positive,num,rhs.numer.n);
                }

                case Sign::PP:
                {
                    const Natural num = natural_t(lhs) * rhs.denom;
                    return Rational(Positive,num,rhs.numer.n);
                }

                case Sign::NP:
                {
                    const Natural num = natural_t(-lhs) * rhs.denom;
                    return Rational(Negative,num,rhs.numer.n);
                }

                case Sign::PN:
                {
                    const Natural num = natural_t(lhs) * rhs.denom;
                    return Rational(Negative,num,rhs.numer.n);
                }


            }

            return Rational();
        }
    }
}


namespace Yttrium
{
    namespace Apex
    {
        Rational Rational:: Div(const Rational &lhs, const Natural &rhs)
        {
            if(rhs.bits()<=0) throw Libc::Exception(EDOM,"%s division by %s zero",CallSign,Natural::CallSign);

            const Natural den = lhs.denom * rhs;
            return Rational(lhs.numer,den);
        }

        Rational Rational:: Div(const Natural &lhs, const Rational &rhs)
        {
            switch(rhs.numer.s)
            {
                case __Zero__:
                    break; // throw

                case Positive:
                    if(lhs.bits()<=0)
                        return Rational();
                    else
                    {
                        const  Natural num = lhs * rhs.denom;
                        return Rational(Positive,num,rhs.numer.n);
                    }

                case Negative:
                    if(lhs.bits()<=0)
                        return Rational();
                    else
                    {
                        const  Natural num = lhs * rhs.denom;
                        return Rational(Negative,num,rhs.numer.n);
                    }
            }
            throw Libc::Exception(EDOM,"%s division by %s zero",Natural::CallSign,CallSign);
        }


    }

}
