
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

namespace Yttrium
{
    namespace Apex
    {
        SignType Rational:: Compare(const Rational &lhs, const Integer &rhs)
        {
            switch( Sign::Pair(lhs.numer.s,rhs.s))
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

            const Integer R = rhs * lhs.denom;
            return (lhs.numer-R).s;
        }

        SignType Rational:: Compare(const Integer &lhs, const Rational &rhs)
        {
            return Sign::Opposite( Compare(rhs,lhs) );
        }

    }

}

namespace Yttrium
{
    namespace Apex
    {
        SignType Rational:: Compare(const Rational &lhs, const Natural &rhs)
        {

            switch(lhs.numer.s)
            {
                case Negative: return Negative;
                case __Zero__: return rhs.bits()>0 ? Negative : __Zero__;
                case Positive:
                    break;
            }
            const Integer R = rhs * lhs.denom;
            return (lhs.numer-R).s;
        }

        SignType Rational:: Compare(const Natural &lhs, const Rational &rhs)
        {
            return Sign::Opposite( Compare(rhs,lhs) );
        }
    }

}

namespace Yttrium
{
    namespace Apex
    {
        SignType Rational:: Compare(const Rational &lhs, const integer_t rhs)
        {
            const SignType rhs_s = Sign::Of(rhs);
            switch( Sign::Pair(lhs.numer.s,rhs_s))
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

            //const Integer R = rhs * lhs.denom;
            //return (lhs.numer-R).s;
        }


        SignType Rational:: Compare(const integer_t lhs, const Rational &rhs)
        {
            return Sign::Opposite( Compare(rhs,lhs) );

        }
    }

}

