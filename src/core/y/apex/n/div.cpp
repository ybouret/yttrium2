
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
            size_t       xp    = nbits-dbits;
            Natural      lower(TwoToThePowerOf,xp);
            {
                const Natural probe = lower * denom;
                switch( Compare(probe,numer) )
                {
                    case Negative:
                        ++xp;      // for upper
                        break;

                    case __Zero__: // exact match
                        if(Q) Q->xch(lower);
                        if(R) R->ldz();
                        return;

                    case Positive:
                        lower.shr(); // and upper will be 2^xp
                        break;
                }
            }
            assert(lower*denom<numer);
            {
                Natural      upper(TwoToThePowerOf,xp); assert(2*lower==upper);
                assert(upper*denom>=numer);

                while(true)
                {
                    {
                        Natural       middle = upper+lower; middle.shr();
                        const Natural probe = middle * denom;
                        switch( Compare(probe,numer) )
                        {
                            case Negative: lower.xch(middle); break;
                            case Positive: upper.xch(middle); break;
                            case __Zero__:
                                if(Q) Q->xch(middle);
                                if(R) R->ldz();
                                return;
                        }
                    }
                    const Natural delta = upper-lower;
                    if(delta.code->bits<=1)
                        break;
                }
            }

            if(R) { *R = numer-lower * denom; }
            if(Q) Q->xch(lower);

        }
    }

}
