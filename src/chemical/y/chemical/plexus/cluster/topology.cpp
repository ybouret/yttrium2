
#include "y/chemical/plexus/cluster.hpp"
#include "y/mkl/algebra/rank.hpp"

namespace Yttrium
{
    namespace Chemical
    {

        void Cluster:: buildTopology(XMLog &xml)
        {
            const size_t N = elist->size;
            const size_t M = slist->size;
            Y_XML_Section(xml,"Topology");
            {
                iMatrix & Nu = Coerce(iTopo).make(N,M);
                for(const ENode * en = elist->head;en;en=en->next)
                {
                    const Equilibrium &eq = **en;
                    if(xml.verbose) display(xml(),eq) << std::endl;
                    eq.topology(Nu[ eq.indx[SubLevel]], SubLevel);
                }
            }
            Y_XMLog(xml, "Nu=" << iTopo);
            const size_t rank = MKL::Rank::Of(iTopo);
            Y_XMLog(xml, "rank=" << rank);
            if(rank != N)
                throw Specific::Exception(CallSign,"found dependent equilibria");
        }

    }

}

