
#include "y/chemical/plexus/solver.hpp"
#include "y/stream/libc/output.hpp"
#include "y/mkl/numeric.hpp"
#include "y/mkl/api/almost-equal.hpp"
#include "y/mkl/opt/optimize.hpp"

#include "y/container/algorithm/for-each.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        void Solver:: kinetic(XMLog & xml)
        {
            Y_XML_Section(xml, "kinetic");

            // computing xkin
            Algo::ForEach(xkin, & XAdd::ldz );
            for(const PNode *pn=plist->head;pn;pn=pn->next)
            {
                const Prospect    &pro = **pn;
                const Equilibrium &eq  = pro.eq;
                const xreal_t      xi  = pro.xi;
                for(const Actor *a=eq.prod->head;a;a=a->next) a->sp(xkin,SubLevel) <<  (xi * a->xn);
                for(const Actor *a=eq.reac->head;a;a=a->next) a->sp(xkin,SubLevel) << -(xi * a->xn);
            }

        }

    }

}

