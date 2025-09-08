
#include "y/apex/integer.hpp"
#include "y/calculus/iabs.hpp"
#include "y/exception.hpp"
#include "y/random/bits.hpp"

namespace Yttrium
{

    namespace Apex
    {

        const char * const Integer:: CallSign = "apz";

        const char * Integer:: callSign() const noexcept { return CallSign; }

        Integer::  Integer() : s(__Zero__), n() {}
        Integer:: ~Integer() noexcept {}

        void Integer:: ldz() noexcept
        {
            Coerce(s) = __Zero__;
            Coerce(n).ldz();
        }

        void Integer:: ld1() noexcept
        {
            Coerce(s) = Positive;
            Coerce(n).ld1();
        }

        void   Integer::ldm1() noexcept
        {
            Coerce(s) = Negative;;
            Coerce(n).ld1();
        }


        String Integer:: str() const
        {
            switch(s)
            {
                case __Zero__: return '0';
                case Positive: return n.decString();
                case Negative:
                    break;
            }
            return '-' + n.decString();
        }

        std::ostream & operator<<(std::ostream &os, const Integer &z)
        {
            return os << z.str();
        }

        Integer:: Integer(const Integer &z) :
        Number(),
        s(z.s),
        n(z.n)
        {
        }

        Integer:: Integer(Random::Bits &ran, const size_t nbit) :
        Number(),
        s(nbit>0?Positive:__Zero__),
        n(ran,nbit)
        {
            if(ran.choice()) (void) neg();
        }


        Integer & Integer:: xch(Integer &z) noexcept
        {
            CoerceSwap(s,z.s);
            Coerce(n).xch( Coerce(z.n) );
            return *this;
        }

        Integer & Integer:: operator=(const Integer &z)
        {
            Integer tmp(z);
            return  xch(tmp);
        }

        Integer:: Integer(const integer_t z) :
        Number(),
        s( Sign::Of(z)   ),
        n( natural_t(z>=0?z:-z) )
        {

        }

        Integer:: Integer(const SignType S, const Natural & N) :
        Number(),
        s(S),
        n(N)
        {
            static const char fn[] = "apz(s,n)";
            switch(s)
            {
                case Negative:
                case Positive:
                    if(n.bits()<=0) throw Specific::Exception(fn,"n=zero, sign=%s",Sign::HumanReadable(s));
                    break;
                case __Zero__:
                    if(n.bits()>0) throw Specific::Exception(fn,"n>0 for sign=%s",Sign::HumanReadable(s));
                    break;

            }
        }


        Integer & Integer:: operator=( const integer_t z ) noexcept
        {
            switch( Sign::Of(z) )
            {
                case __Zero__: ldz(); break;
                case Positive: Coerce(s) = Positive; Coerce(n) = natural_t(z);  break;
                case Negative: Coerce(s) = Negative; Coerce(n) = natural_t(-z); break;
            }
            return *this;
        }

        Integer & Integer:: operator=(const Natural &N)
        {
            Integer z(N);
            return xch(z);
        }


        Integer:: Integer(const Natural &N) :
        Number(),
        s(N.bits() <= 0 ? __Zero__ : Positive),
        n(N)
        {
        }
        



    }

}



