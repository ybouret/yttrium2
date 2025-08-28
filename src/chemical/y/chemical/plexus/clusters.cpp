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
        
        Clusters:: Clusters(XMLog &xml, Equilibria &eqs, const xreal_t t0) :
        list(),
        topK(0,0),
        K(topK)
        {
            Y_XML_Section(xml,CallSign);
            assert(!eqs.frozen());
            
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
                CxxListOf<Cluster> store;
                while(list.size>0)
                {
                    AutoPtr<Cluster> guest = list.popTail();
                    for(Cluster *host=store.head;host;host=host->next)
                    {
                        if(host->accepts(*guest))
                        {
                            host->fusion( guest.yield()) ;
                            break;
                        }
                    }
                    if(guest.isValid()) store.pushTail( guest.yield() );
                }
                store.swapListFor(list);
            }

            // compile all clusters
            size_t ntot = 0;
            for(Cluster *cl = list.head;cl;cl=cl->next)
            {
                cl->compile(xml,eqs,K);
                ntot += (***cl).size;
            }

            // prepare top level K
            {
                CxxArray<xreal_t> tmp(ntot,0);
                topK.xch(tmp);
            }

            // first initialization
            assert(ntot == K.size() );
            computeK(t0);

            // freeze equilibria
            eqs.freeze();
        }

        void Clusters:: computeK(const xreal_t t)
        {
            for(Cluster *cl = list.head;cl;cl=cl->next)
            {
                cl->compute(topK,t);
            }
        }

    }

}

