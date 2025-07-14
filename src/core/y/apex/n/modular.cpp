
#include "y/apex/n/modular.hpp"
#include "y/apex/integer.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{
    namespace Apex
    {
        Natural Modular::Exp(const Natural &b,
                             const Natural &e,
                             const Natural &modulus)
        {

            Natural base     = b;
            Natural exponent = e;

            Natural result   = 1;
            base %= modulus;
            while(exponent.bits()>0)
            {
                if(exponent.isOdd())
                    result = (result * base) % modulus;
                exponent.shr();
                base = base.sqr() % modulus;
            }
            return result % modulus;
        }


#if 1
        Natural Modular::Inv(const Natural &a, const Natural &n)
        {
            Integer t=0,newt=1;
            Natural r=n,newr=a;


            while(newr.bits()>0)
            {
                Natural quotient;
                Natural remainder;
                Natural::Div_( &quotient, &remainder, r, newr);
                {
                    Integer _ = t - quotient * newt;
                    t.xch(newt);
                    newt.xch(_);
                }
                r.xch(newr);
                newr.xch(remainder);
            }

            if(r>1)
                throw Specific::Exception("Modular::Inv","Singular Value");

            while(t.s != Positive) t += n;
            return t.n;
        }
#endif

    }

}


