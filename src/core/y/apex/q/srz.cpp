
#include "y/apex/rational.hpp"

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
    }

}

