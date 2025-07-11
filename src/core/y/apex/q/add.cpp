#include "y/apex/rational.hpp"

namespace Yttrium
{
    namespace Apex
    {
        Rational Rational::Add(const Rational &lhs, const Rational &rhs)
        {
            const Integer num = lhs.numer * rhs.denom + rhs.numer * lhs.denom;
            const Natural den = lhs.denom * rhs.denom;
            return Rational(num,den);
        }
    }

}

namespace Yttrium
{
    namespace Apex
    {
        Rational Rational::Add(const Rational &lhs, const Integer &rhs)
        {
            const Integer num = lhs.numer + rhs * lhs.denom;
            return Rational(num,lhs.denom);
        }

        Rational Rational::Add(const Integer &lhs, const Rational &rhs)
        {
            return Add(rhs,lhs);
        }

    }

}

namespace Yttrium
{
    namespace Apex
    {
        Rational Rational::Add(const Rational &lhs, const Natural &rhs)
        {
            const Natural _   = rhs * lhs.denom;
            const Integer num = lhs.numer + _;
            return Rational(num,lhs.denom);
        }

        Rational Rational::Add(const Natural &lhs, const Rational &rhs)
        {
            return Add(rhs,lhs);
        }
    }

}

namespace Yttrium
{
    namespace Apex
    {
        Rational Rational::Add(const Rational &lhs, const integer_t rhs)
        {

            switch( Sign::Of(rhs) )
            {
                case __Zero__:
                    break; // return lhs

                case Positive:
                {
                    const Natural _   = lhs.denom * natural_t(rhs);
                    const Integer num = lhs.numer + _;
                    return Rational(num,lhs.denom);
                }


                case Negative:
                {
                    const Natural _   = lhs.denom * natural_t(-rhs);
                    const Integer num = lhs.numer - _;
                    return Rational(num,lhs.denom);
                }

            }
            return lhs;
        }

        Rational Rational::Add(const integer_t lhs, const Rational &rhs)
        {
            return Add(rhs,lhs);
        }
    }

}


namespace Yttrium
{

    namespace Apex
    {
        Rational Rational:: operator+() const
        {
            return *this;
        }

        void Rational:: incr()
        {
            const Integer _ = numer + denom;
            Rational      q(_,denom);
            xch(q);
        }

        Rational & Rational:: operator++()
        {
            incr();
            return *this;
        }

        Rational   Rational:: operator++(int)
        {
            const Rational saved = *this;
            incr();
            return saved;
        }

    }

}
