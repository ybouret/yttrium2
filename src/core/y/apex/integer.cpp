
#include "y/apex/integer.hpp"
#include "y/calculus/iabs.hpp"

namespace Yttrium
{

    namespace Apex
    {

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

        String Integer:: toString() const
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
            return os << z.toString();
        }

        Integer:: Integer(const Integer &z) :
        Number(),
        s(z.s),
        n(z.n)
        {
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
        n( IntegerAbs(z) )
        {

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


        Integer:: Integer(const Natural &N) :
        Number(),
        s(N.bits() <= 0 ? __Zero__ : Positive),
        n(N)
        {
        }
        



    }

}
