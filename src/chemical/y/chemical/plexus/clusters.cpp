#include "y/chemical/plexus/clusters.hpp"


namespace Yttrium
{
    namespace Chemical
    {
        Y_Ingress_Impl(Clusters,list)
        
        Clusters:: ~Clusters() noexcept
        {
        }

        const char * const Clusters:: CallSign = "Clusters";
        
        Clusters:: Clusters(XMLog &xml, Equilibria &eqs) :
        list()
        {
            Y_XML_Section(xml,CallSign);
            for(Equilibria::Iterator it=eqs.begin();it!=eqs.end();++it)
            {
                Equilibrium &eq = **it;
                for(Cluster *cl = list.head; cl; cl=cl->next)
                {
                    if(cl->accepts(eq)) {
                        cl->attach(eq);
                        goto CHECK_FUSION;
                    }
                }

                // new cluster
                list.pushTail( new Cluster(eq) );
                continue;

                // check fusion of previous clusters
            CHECK_FUSION:
                ;
            }
        }
    }

}

