
#include "y/apex/integer.hpp"
#include "y/calculus/iabs.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

namespace Yttrium
{

    namespace Apex
    {
        Integer   Integer:: abs()      const
        {
            switch(s)
            {
                case __Zero__: break;
                case Positive: return *this;
                case Negative: { Integer a(*this); Coerce(a.s) = Positive; return a; }
            }
            return Integer();
        }


        Integer & Integer:: neg() noexcept
        {
            Sign::MakeOpposite( Coerce(s) );
            return *this;
        }

        Integer Integer:: sqr() const
        {
            switch(s)
            {
                case __Zero__: return Integer();
                case Negative:
                case Positive:
                    break;
            }
            const Natural n2 = n.sqr();
            return Integer(Positive,n2);
        }



        Integer   Integer:: sqrt()      const
        {
            switch(s)
            {
                case __Zero__: break;
                case Positive: { const Natural S = n.sqrt(); return Integer(S); }
                case Negative: throw Libc::Exception(EDOM,"sqrt of negative %s",CallSign);
            }
            return Integer();
        }

        void Integer:: shr() noexcept
        {
            if(__Zero__==s) return;
            Coerce(n).shr();
            if(n.bits()<=0) Coerce(s) = __Zero__;
        }
    }

}

