
#include "y/chemical/plexus/conservation/act.hpp"
#include "y/chemical/type/list-ops.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {

            Y_Ingress_Impl(Act,list)

            Act:: ~Act() noexcept
            {
            }

            Act:: Act(const Law &first) :
            Object(),
            Ingress<const LList>(),
            list(),
            slist(),
            elist(),
            next(0),
            prev(0)
            {
                connect(first);
            }


            void Act:: connect(const Law &law)
            {
                assert( !list.found(law) );
                list << law;
                for(const Actor *a=law->head;a;a=a->next)
                {
                    Coerce(slist) |= a->sp;
                }
                ListOps::Make(Coerce(slist), AuxLevel);
            }

            void Act:: combine(Act &canon)
            {
                // fetch laws
                list->mergeTail( *(canon.list) );

                // merge species
                SList &target = Coerce(slist);
                SList &source = Coerce(canon.slist);
                while(source->size)
                {
                    if( target.found(**source->head) )
                        source.popHead();
                    else
                        target->pushTail(source->popHead());
                }

                ListOps::Make(Coerce(slist), AuxLevel);

            }

            bool Act:: accepts(const Law &law) const noexcept
            {
                for(const SNode *sn=slist->head;sn;sn=sn->next)
                {
                    if( law.got(**sn) ) return true;
                }
                return false;
            }

            bool Act:: accepts(const Act &act) const noexcept
            {
                assert(this != &act);
                for(const SNode *sn=act.slist->head;sn;sn=sn->next)
                {
                    if( slist.found(**sn) ) return true;
                }
                return false;
            }


        }

    }

}

