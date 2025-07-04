
#include "y/apex/natural.hpp"
#include "y/system/exception.hpp"
#include "y/apex/block/model.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Apex
    {
        void Natural:: Div_(Natural * const Q,
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
                    std::cerr << "division by 1" << std::endl;
                    if(Q) { *Q = numer; std::cerr << "copied numer" << std::endl; std::cerr << "*Q=" << *Q << std::endl; }
                    if(R)  R->ldz();
                    std::cerr << "done :)" << std::endl;
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

            if(R) { *R = numer - lower * denom; }
            if(Q) Q->xch(lower);

        }
    }

}

namespace Yttrium
{
    namespace Apex
    {
        Natural Natural:: Div(const Natural &numer, const Natural &denom)
        {
            Natural Q; Div_(&Q, 0, numer, denom); return Q;

        }

        Natural Natural:: Mod(const Natural &numer, const Natural &denom)
        {
            Natural R; Div_(0, &R, numer, denom); return R;
        }
    }
}

