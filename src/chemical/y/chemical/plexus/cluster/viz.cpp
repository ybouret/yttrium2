
#include "y/chemical/plexus/cluster.hpp"
#include "y/stream/output.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        void Cluster:: vizSpecies(OutputStream &fp) const
        {
            for(const SNode *sn=slist->head;sn;sn=sn->next)
            {
                const Species &sp = **sn;
                const char * const style = conserved.found(sp) ? "solid" : "dashed";
                const String       color = cs[ sp.indx[TopLevel] ];
                sp.viz(fp,color,style);
            }
        }


        OutputStream & Cluster:: viz(OutputStream &fp, const size_t numOrder) const
        {
            assert(numOrder>0);
            assert(numOrder<=order.size());

            fp("subgraph cluster_%u {\n",indx);
            
            vizSpecies(fp);
            


            return fp  << "}\n";
        }
    }

}

