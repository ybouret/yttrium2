
#include "y/apex/api/coven/tribes.hpp"


namespace Yttrium
{

    namespace Coven
    {


        Tribes:: ~Tribes() noexcept
        {

        }

        std::ostream & operator<<(std::ostream &os, const Tribes &tribes)
        {
            os << "<Tribes size=" << tribes.size << ">" << std::endl;
            for(const Tribe *tr=tribes.head;tr;tr=tr->next)
            {
                os << *tr << std::endl;
            }
            return os << "</Tribes>" << std::endl;
        }


        bool Tribes:: colinearity() const noexcept
        {
            assert(tail!=0);
            assert(1==tail->family->size());
            assert(0!=tail->family->lastVec);
            const QVector &lhs = * tail->family->lastVec;
            for(const Tribe *prev=tail->prev;prev;prev=prev->prev)
            {
                assert(1==prev->family->size());
                assert(0!=prev->family->lastVec);
                const QVector &rhs = * prev->family->lastVec;
                if(lhs==rhs)
                {
                    std::cerr << "colinear rows" << std::endl;
                    return true;
                }
            }
            return false;
        }

        void Tribes:: finish(const IList &toRemove) noexcept
        {
            for(Tribe *tr=head;tr;tr=tr->next)
            {
                for(const INode *node=toRemove->head;node;node=node->next)
                {
                    tr->remove(**node);
                }
            }
        }

#if 0
        static inline
        void promoteReadyOf(Tribe * const tribe, const IList &peerBasis)
        {
            //std::cerr << "Promote " << *tribe << " with " << peerBasis << std::endl;

            {
                IList ready(peerBasis.pool);
                while(tribe->ready->size)
                {
                    INode * const node = tribe->ready->popHead();
                    if(peerBasis.has(**node))
                    {
                        tribe->basis.sorted(node);
                    }
                    else
                        ready->pushTail(node);
                }

                (*tribe->ready).swapListFor(*ready);
            }


        }
#endif

        void Tribes:: shrink()
        {
            assert(isOrderedBy(Tribe::Compare,Sign::LooselyIncreasing));
            Tribe::List list;

            while(size>0)
            {
                Tribe * const source = head;
                if(source->stalled()) goto DROP;


                for(Tribe *target=list.tail;target;target=target->prev)
                {
                    if(target->basis == source->basis)
                    {
                        if(target->ready == source->ready)
                        {
                            assert( __Zero__ == Tribe::Compare(source,target) );
                            goto DROP; // replica
                        }
                        goto KEEP;     // for next generation
                    }
                }

            KEEP:
                list.pushTail( popHead() );
                continue;

            DROP:
                delete popHead();
                continue;
            }
            swapListFor(list);
            
            assert(isOrderedBy(Tribe::Compare,Sign::LooselyIncreasing));
        }


    }

}
