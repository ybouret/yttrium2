
#include "y/apex/rational.hpp"
#include "y/system/exception.hpp"
#include "y/random/bits.hpp"

namespace Yttrium
{
    namespace Apex
    {

        const char * const Rational:: CallSign = "apq";

        Rational:: Rational()   :
        Number(),
        numer(),
        denom(1)
        {
        }

        Rational:: ~Rational() noexcept
        {
        }

        Rational:: Rational(const Rational &q) :
        Number(),
        numer(q.numer),
        denom(q.denom)
        {
        }


        void Rational:: ldz() noexcept
        {
            Coerce(numer).ldz();
            Coerce(denom).ld1();
        }

        void Rational:: ld1() noexcept
        {
            Coerce(numer).ld1();
            Coerce(denom).ld1();
        }

        Rational & Rational:: neg() noexcept
        {
            Coerce(numer).neg();
            return *this;
        }

        void Rational:: simplify()
        {
            switch( denom.bits() )
            {
                case 0: throw Specific::Exception(CallSign,"zero denominator");
                case 1: return;
                default:
                    break;
            }
            const Natural g = Natural::GCD(numer.n,denom);
            if(g.bits()>1)
            {
                Natural nn = numer.n/g;
                Natural dd = denom/g;
                Coerce(numer.n).xch(nn);
                Coerce(denom).xch(dd);
            }

        }

        Rational & Rational:: xch(Rational &q) noexcept
        {
            Coerce(numer).xch( Coerce(q.numer) );
            Coerce(denom).xch( Coerce(q.denom) );
            return *this;
        }

        Rational & Rational:: operator=(const Rational &q)
        {
            Rational tmp(q);
            return xch(tmp);
        }

        Rational:: Rational(const integer_t N,const natural_t D) :
        Number(),
        numer(N),
        denom(D)
        {
            simplify();
        }

        Rational:: Rational(const Fraction &F) :
        Number(),
        numer(F.numer),
        denom(F.denom)
        {
            simplify();
        }

        Rational::Rational(const Integer &N, const Natural &D) :
        Number(),
        numer(N),
        denom(D)
        {
        }

        Rational:: Rational(const integer_t N) :
        Number(),
        numer(N),
        denom(1)
        {
        }



        Rational::Rational(const Integer &N) :
        Number(), numer(N), denom(1)
        {
        }

        Rational::Rational(const Natural &N) :
        Number(), numer(N), denom(1)
        {
        }

        Rational:: Rational(Random::Bits &ran,const size_t nbit, const size_t dbit) :
        Number(),
        numer(ran,nbit),
        denom(ran,dbit)
        {
            simplify();
        }

        Rational:: Rational(const SignType s, const Natural &n, const Natural &d) :
        Number(),
        numer(s,n),
        denom(d)
        {
            simplify();
        }

        Rational & Rational:: operator=(const Natural &N)
        {
            Integer nn(N);
            Coerce(numer).xch(nn);
            Coerce(denom).ld1();
            return *this;
        }

        Rational & Rational:: operator=(const Integer &N)
        {
            Integer nn(N);
            Coerce(numer).xch(nn);
            Coerce(denom).ld1();
            return *this;
        }


        Rational & Rational:: operator=(const integer_t N)
        {
            Integer nn(N);
            Coerce(numer).xch(nn);
            Coerce(denom).ld1();
            return *this;
        }

        Rational & Rational:: operator=(const Fraction f)
        {
            Rational q(f);
            return xch(q);
        }




        std::ostream & operator<<(std::ostream &os, const Rational &q)
        {
            if(q.denom.bits()<=1)
            {
                return os << q.numer;
            }
            else
            {
                os << '(' << q.numer << '/' << q.denom << ')';
            }
            return os;
        }

    }

}

