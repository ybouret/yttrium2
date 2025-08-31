
#include "y/chemical/reactive/actor.hpp"
#include "y/string/format.hpp"
#include "y/core/utils.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        const char * const Actor:: CallSign = "Actor";
        
        Actor:: ~Actor() noexcept
        {
        }


        Actor:: Actor(const Actor &a) :
        Entity(a.name),
        sp(a.sp),
        nu(a.nu),
        xn(a.xn),
        nu1(a.nu1),
        next(0),
        prev(0),
        zero()
        {
        }
        

        Actor:: Actor(const unsigned n,
                      const Species &s,
                      const Role     r) :
        Entity(),
        sp(s),
        nu(n),
        xn(nu),
        nu1(nu-1),
        next(0),
        prev(0),
        zero()
        {
            if(nu<=0) throw Specific::Exception(CallSign,"null coefficient");
            String & id  = Coerce(name);
            if(nu>1) id += Formatted::Get("%u",nu);
            switch(r)
            {
                case InEquilibrium:  id += sp.name;        break;
                case InConservation: id += '[' + sp.name + ']'; break;
            }
        }


        void Actor:: massAction(XMul &X, const XReadable &C, const Level L) const
        {
            const xreal_t c = sp(C,L); assert(c>=zero);
            X.ipower(c,nu);
        }

        void Actor:: massAction(XMul &X, const XReadable &C, const Level L, const xreal_t xi) const
        {
            xreal_t c = sp(C,L) + xn * xi;
            InSituMax(c,zero);
            X.ipower(c,nu);
        }

        void Actor:: moveSafely(XWritable &   C,
                                const Level   L,
                                const xreal_t xi) const
        {
            xreal_t &c = sp(C,L);
            InSituMax(c += xi * xn,zero);
        }

        void Actor:: diffAction(XMul &X, const XReadable &C, const Level L) const
        {
            switch(nu1)
            {
                case 0: return;
                case 1: X << xn; return;
                default:
                    break;
            }
            const xreal_t c = sp(C,L); assert(c>=zero);
            X.ipower(c,nu1);
            X << xn;
        }



    }

}
