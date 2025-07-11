
#include "y/apex/rational.hpp"

namespace Yttrium
{
    namespace Apex
    {
        Rational Rational:: Sub(const Rational &lhs, const Rational &rhs)
        {
            const Integer num = lhs.numer * rhs.denom - rhs.numer * lhs.denom;
            const Natural den = lhs.denom * rhs.denom;
            return Rational(num,den);
        }
    }

}

namespace Yttrium
{
    namespace Apex
    {
        Rational Rational:: Sub(const Rational &lhs, const Integer &rhs)
        {
            const Integer num = lhs.numer  - rhs * lhs.denom;
            return Rational(num,lhs.denom);
        }

        Rational Rational:: Sub(const Integer &lhs, const Rational &rhs)
        {
            return Sub(rhs,lhs).neg();
        }
    }

}

namespace Yttrium
{
    namespace Apex
    {
        Rational Rational:: Sub(const Rational &lhs, const Natural &rhs)
        {
            const Integer num = lhs.numer  - rhs * lhs.denom;
            return Rational(num,lhs.denom);
        }

        Rational Rational:: Sub(const Natural &lhs, const Rational &rhs)
        {
            return Sub(rhs,lhs).neg();
        }
    }

}

namespace Yttrium
{
    namespace Apex
    {
        Rational Rational:: Sub(const Rational &lhs, const integer_t rhs)
        {
            return Add(lhs,-rhs);
        }

        Rational Rational:: Sub(const integer_t lhs, const Rational &rhs)
        {
            return Add(-lhs,rhs).neg();
        }
    }

}

namespace Yttrium
{
    namespace Apex
    {
        Rational Rational:: operator-() const
        {
            Rational self(*this);
            return self.neg();
        }

        void Rational:: decr()
        {
            const Integer _ = numer - denom;
            Rational      q(_,denom);
            xch(q);
        }

        Rational & Rational:: operator--()
        {
            decr();
            return *this;
        }

        Rational   Rational:: operator--(int)
        {
            const Rational saved = *this;
            decr();
            return saved;
        }

    }

}

