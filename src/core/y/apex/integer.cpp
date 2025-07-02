#include "y/apex/integer.hpp"

namespace Yttrium
{

    namespace Apex
    {
        Integer:: Integer() :
        Number(),
        s(__Zero__),
        n()
        {}

        Integer:: ~Integer() noexcept {}


        Integer & Integer:: xch( Integer &z ) noexcept
        {
            CoerceSwap(s,z.s);
            Coerce(n).xch( Coerce(z.n) );
            return *this;
        }

        Integer:: Integer(const Integer &z) :
        Number(),
        s(z.s),
        n(z.n)
        {
        }

        Integer & Integer:: operator=(const Integer &z)
        {
            Integer tmp(z);
            return xch(tmp);
        }

        Integer:: Integer(const Natural &N) :
        Number(),
        s( N.bits() > 0 ? Positive : __Zero__),
        n(N)
        {
        }

        Integer:: Integer(const SignType _s, const Natural & _n) :
        Number(),
        s( _s ),
        n( _n )
        {
#if !defined(NDEBUG)
            switch(s)
            {
                case Negative: assert(n.bits() >  0); break;
                case __Zero__: assert(n.bits() == 0); break;
                case Positive: assert(n.bits() >  0); break;
            }
#endif
        }


        Integer:: Integer(const integer_t z) :
        Number(),
        s( Sign::Of(z) ),
         n( z >= 0 ? natural_t(z) : natural_t(-z) )
        {
        }

        Integer & Integer:: operator=(const integer_t z)
        {
            Integer tmp(z);
            return xch(tmp);
        }

        std::ostream & operator<<(std::ostream &os, const Integer &z)
        {
            String s;
            if(z.s==Negative) s << '-';
            s << z.n.hexString();
            return os << s;
        }

    }

}
