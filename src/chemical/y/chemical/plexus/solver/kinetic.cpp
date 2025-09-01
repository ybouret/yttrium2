
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
            Y_XML_Section(xml, kineticName);

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

            {
                xreal_t scale(10);
                bool    wasCut = false;
                // loading dC
                for(const SNode *sn=cluster.slist->head;sn;sn=sn->next)
                {
                    const Species &sp = **sn;
                    const size_t   j  = sp.indx[SubLevel];
                    const xreal_t  dc = (dC[j]   = xkin[j].sum());
                    if(dc<zero)
                    {
                        InSituMin(scale,Csub[j]/(-dc));
                        wasCut = true;
                    }
                }
                std::cerr << "wasCut=" << wasCut << std::endl;
                if(wasCut) scale *= 0.98;
                std::cerr << "scale="  << scale.str() << std::endl;

                for(size_t j=dC.size();j>0;--j)
                {
                    Cend[j] = Csub[j] + scale * dC[j];
                }
                
            }

            {
                savePro(kineticName, 500);
            }

            if(xml.verbose) xml() << kineticName;
            minimize(xml,Wsub,affinityRMS(Cend,SubLevel));

            if(xml.verbose)
            {
                gnuplot += ", '" + kineticName << ".dat' w lp";
                xml() << "\t" << gnuplot << std::endl;
            }





        }

    }

}

