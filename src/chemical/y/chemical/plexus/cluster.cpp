#include "y/chemical/plexus/cluster.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        const char * const Cluster:: CallSign = "Cluster";

        Cluster:: ~Cluster() noexcept
        {
        }


        Cluster:: Cluster(Equilibrium &first) :
        Object(),
        elist(),
        slist(),
        next(0),
        prev(0)
        {
            attach(first);
        }

        Y_Ingress_Impl(Cluster,elist);


        void Cluster:: attach(const Species &sp)
        {
            if( !slist.found(sp) ) Coerce(slist) << sp;
        }


        void Cluster:: attach(Equilibrium &eq)
        {
            if(elist.found(eq)) throw Specific::Exception(CallSign,"multiple '%s'", eq.name.c_str());

            elist << eq;

            {
                SList stemp(slist);
                try {
                    for(const Actor *a=eq.prod->head;a;a=a->next) attach(a->sp);
                    for(const Actor *a=eq.reac->head;a;a=a->next) attach(a->sp);
                }
                catch(...)
                {
                    Coerce(slist).xch(stemp);
                    elist.popTail(); throw;
                }
            }

            update();

        }

        void Cluster:: update() noexcept
        {
            ListOps::Make(elist,SubLevel);
            ListOps::Make(Coerce(slist),SubLevel);
        }

        bool Cluster:: accepts(const Equilibrium &eq) const noexcept
        {
            assert( !elist.found(eq) );

            for(const ENode *node=elist->head;node;node=node->next)
            {
                if( eq.linkedTo( **node ) ) return true;
            }

            return false;
        }

        bool Cluster:: accepts(const Cluster &cl) const noexcept
        {
            for(const ENode *node=elist->head;node;node=node->next)
            {
                if(cl.accepts(**node))
                    return true;
            }
            return false;
        }

        void Cluster:: fusion(Cluster * const cl) noexcept
        {
            assert(cl);

            // merge equilibria
            (*elist).mergeTail( *(cl->elist) );

            // merge species
            while(cl->slist->size>0)
            {
                const Species &sp = **(cl->slist->head);
                if(slist.found(sp))
                    Coerce(cl->slist).popHead();
                else
                    Coerce(*slist).pushTail( Coerce(*cl->slist).popHead() );
            }
            delete cl;

            update();
        }


    }

}


