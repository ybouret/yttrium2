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
        K(topK),
        maxOrder(0)
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
            size_t   ntot = 0;
            unsigned icl  = 0;
            for(Cluster *cl = list.head;cl;cl=cl->next,++icl)
            {
                cl->compile(xml,eqs,K);
                Coerce(cl->indx) = icl;
                ntot += (***cl).size;
                InSituMax( Coerce(maxOrder), cl->order.size() );
            }
            Y_XMLog(xml, "maxOrder=" << maxOrder);


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


#include "y/format/decimal.hpp"
#include "y/stream/libc/output.hpp"
#include "y/jive/vfs.hpp"
#include "y/vfs/local/fs.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        void Clusters:: viz(const String &root, const size_t numOrder) const
        {
            const String fileName = root + Decimal(numOrder).c_str() + ".dot";
            {
                OutputFile   fp(fileName);
                Vizible::Enter(fp);
                for(const Cluster *cl = list.head;cl;cl=cl->next)
                {
                    if(cl->order.size()<numOrder) continue;
                    cl->viz(fp,numOrder);
                }
                Vizible::Leave(fp);
            }
            Vizible::DotToPng(fileName);
        }

        using namespace Jive;
        void Clusters:: viz(const String &root) const
        {

            LocalFS & fs = LocalFS:: Instance();
            Matching matching = Pattern::Exact(root);
            
#if 0
            if( argc > 1 )
            {
                Matching matching  = argv[1];
                if(argc>2)
                {

                    _VFS::Apply(fs,
                                argv[1],
                                argv[1],
                                Matching::Exactly,
                                VFS::Entry::Path,
                                _VFS::Display);
                }
            }
#endif

            for(size_t numOrder=1;numOrder<=maxOrder;++numOrder)
            {
                viz(root,numOrder);
            }
        }
    }

}

