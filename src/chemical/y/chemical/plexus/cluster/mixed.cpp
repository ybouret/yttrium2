
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
        xmul()
        {
            Coerce(wlist).xch(wl);
            Coerce(elist).xch(el);
            assert(wlist->size==elist->size);
        }

        xreal_t MixedEquilibrium:: getK(const xreal_t)
        {
            
        }
    }

}

