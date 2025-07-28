
#include "y/apex/api/coven/tribes.hpp"


namespace Yttrium
{

    namespace Coven
    {

        static inline bool shouldGroupFamilies(const Tribe * const lhs,
                                               const Tribe * const rhs) noexcept
        {
            return (lhs->basis != rhs->basis) && ( *lhs->family == *rhs->family);
        }

        static inline
        void promoteReady(Tribe &tribe, const IList &basis)
        {

        }

        void Tribes:: makeGroupFamilies()
        {
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
        }
    }

}


