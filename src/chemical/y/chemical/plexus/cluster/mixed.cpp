
#include "y/chemical/plexus/cluster/mixed.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        MixedEquilibrium:: ~MixedEquilibrium() noexcept
        {
        }

        MixedEquilibrium:: MixedEquilibrium(const String &   eid,
                                            const size_t      top,
                                            const XReadable & tlk,
                                            WList &           wl,
                                            EList &           el) :
        Equilibrium(eid,top),
        topK(tlk),
        wlist(),
        elist(),
        numer(),
        denom()
        {
            Coerce(wlist).xch(wl);
            Coerce(elist).xch(el);
            assert(wlist->size==elist->size);
        }

        xreal_t MixedEquilibrium:: getK(const xreal_t)
        {
            numer.ld1();
            denom.ld1();

            const WNode * wn = wlist->head;
            for(const ENode * en=elist->head;en;en=en->next,wn=wn->next)
            {
                assert(en);
                assert(wn);
                const int     w = **wn;
                const xreal_t k = (**en)(topK,TopLevel);
                if(w>0)
                    numer.ipower(k, (unsigned) w);
                else
                    denom.ipower(k, (unsigned) -w);
            }


            return numer.product()/denom.product();
        }
    }

}

