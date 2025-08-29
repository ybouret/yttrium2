#include "y/chemical/plexus/cluster.hpp"


namespace Yttrium
{
    namespace Chemical
    {

        SignType ListOps:: Compare(const Indexed & lhs, const Indexed & rhs) noexcept
        {
            return Sign::Of( lhs.indx[TopLevel], rhs.indx[TopLevel] );
        }

        const char * const Cluster:: CallSign = "Cluster";

        Cluster:: ~Cluster() noexcept
        {
        }


        Cluster:: Cluster(Equilibrium &first) :
        Object(),
        elist(),
        slist(),
        iTopo(),
        uCLaw(),
        claws(),
        conserved(),
        unbounded(),
        standard(),
        prodOnly(),
        reacOnly(),
        nebulous(),
        order(0),
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
            enroll(eq);

        }

        void Cluster:: update() noexcept
        {
            ListOps::Make(elist,SubLevel);
            ListOps::Make(Coerce(slist),SubLevel);
        }

        bool Cluster:: accepts(const Equilibrium &eq) const noexcept
        {
            assert( !elist.found(eq) );
            for(const SNode *sn=slist->head;sn;sn=sn->next)
            {
                if( eq.has( **sn ) ) return true;
            }

            return false;
        }

        bool Cluster:: accepts(const Cluster &cl) const noexcept
        {
            for(const SNode *sn = cl.slist->head;sn;sn=sn->next)
            {
                if( slist.found(**sn) ) return true;
            }
            return false;
        }

        void Cluster:: fusion(Cluster * const cl) noexcept
        {

            assert(cl);

            // merge equilibria
            {
                Core::ListOf<ENode> &source = *(cl->elist);
                Core::ListOf<ENode> &target = *elist;
                while(source.size)
                {
                    enroll( **target.pushTail( source.popHead() ) );
                }
            }

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


        std::ostream & operator<<(std::ostream &os, const Cluster &cl)
        {
            os << '{' << std::endl;
            for( const ENode *en = (**cl).head; en; en=en->next)
            {
                const Equilibrium &eq = **en;
                cl.display(os << "  ",eq);
                const xreal_t eK = Coerce(eq).K(0);
                os << " '10^(" << eK.log10() << ")'";
                os << std::endl;
            }
            os << '}' << '@';
            os << cl.slist;
            return os;
        }


        void Cluster:: compile(XMLog &xml, Equilibria &eqs, const XReadable &tlK)
        {
            const size_t N = elist->size;
            const size_t M = slist->size;
            Y_XML_Section_Attr(xml,CallSign,Y_XML_Attr(N) << Y_XML_Attr(M));

            buildTopology(xml);
            buildConservations(xml);
            buildCombinatorics(xml,eqs,tlK);
            
            // dispatching
            for(const ENode *en=elist->head;en;en=en->next)
            {
                const Equilibrium &eq = **en;
                if(eq.flow == ProdOnly) {
                    Coerce(prodOnly) << eq;
                    continue;
                }

                if(eq.flow == ReacOnly) {
                    Coerce(reacOnly) << eq;
                    continue;
                }

                if( eq.reac.gotOneOf(conserved) && eq.prod.gotOneOf(conserved) )
                {
                    Coerce(standard) << eq;
                    continue;
                }

                Coerce(nebulous) << eq;

            }

            {
                Y_XML_Section(xml, "Summary");
                {
                    Y_XML_Section(xml,Equilibria::CallSign);
                    for(size_t i=1;i<=order.size();++i)
                    {
                        const size_t n = order[i]->size; if(n<=0) continue;
                        Y_XMLog(xml, "#order " << std::setw(2) << i << " = " << std::setw(4) << n);
                    }
                    Y_XMLog(xml, "#total    = " <<  std::setw(4) << elist->size );
                }
                {
                    Y_XML_Section(xml,"Species");
                    if(conserved->size) Y_XMLog(xml, "conserved = " << conserved);
                    if(unbounded->size) Y_XMLog(xml, "unbounded = " << unbounded);
                }
                
                {
                    Y_XML_Section(xml,"Classification");
                    if(standard->size) Y_XMLog(xml, "standard = " << standard);
                    if(prodOnly->size) Y_XMLog(xml, "prodOnly = " << prodOnly);
                    if(reacOnly->size) Y_XMLog(xml, "reacOnly = " << reacOnly);
                    if(nebulous->size) Y_XMLog(xml, "nebulous = " << nebulous);
                }


            }

        }

        void Cluster:: compute(XWritable &K, const xreal_t t)
        {
            for(ENode *en=elist->head;en;en=en->next)
            {
                Equilibrium &eq = **en;
                eq(K,TopLevel) = eq.K(t);
            }
        }


        void Cluster:: copy(XWritable &C, const Level L, const XReadable &C0, const Level L0) const
        {
            ListOps:: Copy(slist, C, L, C0, L0);
        }

    }

}


