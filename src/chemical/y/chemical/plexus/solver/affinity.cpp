
#include "y/chemical/plexus/solver.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        xreal_t Solver:: affinityRMS(const XReadable &C, const Level L)
        {
            if(plist->size<=0) return 0;

            xsum.ldz();

            for(const PNode *pn=plist->head;pn;pn=pn->next)
            {
                const Prospect    &pro = **pn;
                const Equilibrium &eq  = pro.eq;
                const xreal_t      aff = eq.affinity(xadd,pro.eK,C,L);
                xsum << aff * aff;
                //std::cerr << aff << ";";
            }
            //std::cerr << std::endl;

            const xreal_t resSq = xsum.sum() /= psize;
            return resSq.sqrt();
        }

        xreal_t Solver:: fullAffinityRMS(const XReadable &C, const Level L)
        {
            if(plist->size<=0) return 0;

            xsum.ldz();
            affinity.ld(zero);
            
            for(const PNode *pn=plist->head;pn;pn=pn->next)
            {
                const Prospect    &pro = **pn;
                const Equilibrium &eq  = pro.eq;
                const xreal_t      aff = eq.affinity(xadd,pro.eK,C,L);
                eq(affinity,SubLevel) = aff;
                xsum << aff * aff;
                //std::cerr << aff << ";";
            }
            //std::cerr << std::endl;

            const xreal_t resSq = xsum.sum() /= psize;
            return resSq.sqrt();
        }




        xreal_t Solver:: operator()(xreal_t u)
        {
            const XReadable &Cv = Csub;
            const XReadable &Cu = Cend;
            const xreal_t    v  = one - (u = Clamp(zero,u,one));

            for(size_t i=Cv.size();i>0;--i)
            {
                const xreal_t cv = Cv[i];
                const xreal_t cu = Cu[i];
                xreal_t cmin = cu, cmax = cv;
                if(cmin>cmax) Swap(cmin,cmax);
                Ctry[i] = Clamp(cmin, cu * u + cv * v, cmax);
            }
            return affinityRMS(Ctry,SubLevel);
        }


    }

}
