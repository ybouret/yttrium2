
#include "y/apex/natural.hpp"
#include "y/system/exception.hpp"
#include "y/apex/block/model.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Apex
    {
        void Natural:: Div(Natural * const Q,
                           Natural * const R,
                           const Natural  &numer,
                           const Natural  &denom)
        {

            const size_t dbits = denom.code->bits;

            switch (dbits)
            {
                case 0: throw Libc::Exception(EDOM,"Apex::Division by zero");
                case 1:
                    assert(1==denom);
                    if(Q) *Q = numer;
                    if(R)  R->ldz();
                    return;

                default:
                    break;
            }
            assert(denom>1);

            switch( Compare(numer,denom) )
            {
                case Negative: assert(numer<denom);
                    if(Q)  Q->ldz();
                    if(R)  *R = numer;
                    return;

                case __Zero__: assert(numer==denom);
                    if(Q) Q->ld1();
                    if(R) R->ldz();
                    return;

                case Positive:
                    break;
            }

            assert(numer>denom);
            const size_t nbits = numer.code->bits; assert(nbits>=dbits);
            std::cerr << "nbits=" << nbits << " / dbits=" << dbits << std::endl;
            size_t       xp    = nbits-dbits;
            //Natural      lower(TwoToThePowerOf,xp);






        }
    }

}
