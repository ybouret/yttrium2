
#include "y/chemical/plexus/solver.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        xreal_t Solver:: affinity(const XReadable &C, const Level L)
        {
            if(plist->size<=0) return 0;

            xsum.ldz();
            
            for(const PNode *pn=plist->head;pn;pn=pn->next)
            {
                const Prospect &pro = **pn;
                const xreal_t   aff = pro.eq.affinity(xadd,pro.eK,C,L);
                xsum << aff * aff;
            }

            const xreal_t resSq = xsum.sum() /= psize;
            return resSq.sqrt();
        }

    }

}
