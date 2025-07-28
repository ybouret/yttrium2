
#include "y/apex/api/coven/tribes.hpp"


namespace Yttrium
{

    namespace Coven
    {
#if 0
        Tribes:: ~Tribes() noexcept
        {
            while(size>0)
            {
                tc.banish(popTail());
            }
        }

        void Tribes:: finish(const IList &toRemove) noexcept
        {
            for(Tribe *tr=head;tr;tr=tr->next)
            {
                for(const INode *node=toRemove->head;node;node=node->next)
                {
                    tr->remove(**node);
                }
                std::cerr << *tr << std::endl;
            }
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

#endif
    }

}
