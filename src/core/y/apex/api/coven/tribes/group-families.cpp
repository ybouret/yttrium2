
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

        

        void Tribes:: makeGroupFamilies()
        {
            for(const Tribe *curr=head;curr;curr=curr->next)
            {
                for(const Tribe *prev=curr->prev;prev;prev=prev->prev)
                {
                    if( !shouldGroupFamilies(curr,prev) ) continue;

                    std::cerr << "---> same families!!" << std::endl;
                    std::cerr << *curr << std::endl;
                    std::cerr << *prev << std::endl;

                    exit(0);
                }
            }
        }
    }

}


