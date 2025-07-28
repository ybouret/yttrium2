
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
                // std::cerr << *tr << std::endl;
            }
        }


        void Tribes:: makeNoReplica()
        {
            std::cerr << "No Replica" << std::endl;
            Tribe::List target;
            while(size>0)
            {
                if(target.size<=0)
                {
                    target.pushTail( popHead() );
                    continue;
                }

                assert(target.tail!=0);
                Tribe &lhs = *target.tail;
                Tribe &rhs = *head;

                if(lhs.basis==rhs.basis && lhs.ready == rhs.ready)
                {
#if 0
                    std::cerr
                    <<
                    "Found same " << lhs << std::endl <<
                    " and       " << rhs << std::endl;
#endif
                    delete popHead();
                    continue;
                }

                target.pushTail( popHead() );
            }

            swapListFor(target);
            

        }

    }

}
