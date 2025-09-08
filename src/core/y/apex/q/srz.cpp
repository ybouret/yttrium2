
#include "y/apex/rational.hpp"
#include "y/exception.hpp"

namespace Yttrium
{
    namespace Apex
    {
        size_t Rational:: serialize(OutputStream &fp) const
        {
            if(numer.s==__Zero__)
            {
                return numer.serialize(fp);
            }
            else
            {
                const size_t res = numer.serialize(fp);
                return res+denom.serialize(fp);
            }
        }

        Rational:: Rational(InputStream &fp,const char * const varName) :
        Number(),
        numer(),
        denom()
        {
            apz z(fp,varName);
            if(z.s != __Zero__)
            {
                apn n(fp,varName);
                const char * const id = varName ? varName : "variable";
                if(n.bits()<=0)               throw Specific::Exception(CallSign,"%s has zero denominator",id);
                if(apn::GCD(z.n,n).bits()>1)  throw Specific::Exception(CallSign,"%s is not reduced",id);
                
                Coerce(numer).xch(z);
                Coerce(denom).xch(n);
            }
            
        }


    }

}

