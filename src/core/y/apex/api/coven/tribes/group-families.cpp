
#include "y/apex/api/coven/tribes.hpp"


namespace Yttrium
{

    namespace Coven
    {

        

        static inline
        void promoteReadyOf(Tribe * const tribe, const IList &peerBasis)
        {
            std::cerr << "Promoting ready=" << tribe->ready << " with " << peerBasis << std::endl;
        }

        static inline
        Tribe * findTarget(const Tribe * const source, Tribe::List &list) noexcept
        {
            for(Tribe *target=list.tail;target;target=target->prev)
            {
                if(*source->family == *target->family)
                    return target;
            }
            return 0;
        }

        void Tribes:: makeGroupFamilies()
        {

            Tribe::List list;

            while(size>0)
            {
                Tribe * const source = head;
                if(Apex::Ortho::Basis == source->family->quality)
                {
                    delete popHead();
                    continue;
                }


                Tribe *target = findTarget(source,list);
                if(!target)
                {
                    std::cerr << "no same family" << std::endl;
                    list.pushTail( popTail() );
                    continue;
                }

                if(source->basis == target->basis)
                {
                    std::cerr << "same basis..." << std::endl;
                    if(source->ready == target->ready)
                    {
                        // duplicate
                        std::cerr << "\tduplicate" << std::endl;
                        delete popHead();
                    }
                    else
                    {
                        // different ready order
                        std::cerr << "\tdifferent order" << std::endl;
                        list.pushTail( popTail() );
                    }
                    continue;
                }

                if(target)
                {
                    std::cerr << "---> same families!!" << std::endl;
                    std::cerr << *target << std::endl;
                    std::cerr << *source << std::endl;

                    const IList targetBasis = target->basis;
                    const IList sourceBasis = source->basis;

                    promoteReadyOf(target,sourceBasis);
                    promoteReadyOf(source,targetBasis);

                    exit(0);
                }

                list.pushTail( popTail() );
            }

            swapListFor(list);


#if 0
            for(Tribe *curr=head;curr;curr=curr->next)
            {
                for(Tribe *prev=curr->prev;prev;prev=prev->prev)
                {
                    if( !shouldGroupFamilies(curr,prev) ) continue;

                    std::cerr << "---> same families!!" << std::endl;
                    std::cerr << *curr << std::endl;
                    std::cerr << *prev << std::endl;
                    Tribe &lhs = *curr;
                    Tribe &rhs = *prev;
                    const IList lhsBasis = lhs.basis;
                    const IList rhsBasis = rhs.basis;
                    promoteReady(lhs,rhsBasis);
                    promoteReady(rhs,lhsBasis);
                    exit(0);
                }
            }
#endif
        }
    }

}


