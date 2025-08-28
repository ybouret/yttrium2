

#include "y/chemical/plexus/conservation/law.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {
            Law:: ~Law() noexcept
            {
            }
            
            Law:: Law() : Actors(Actor::InConservation)
            {
                
            }

            std::ostream & operator<<(std::ostream &os, const Law &law)
            {
                os << "d_(" << law.name << ")";
                return os;
            }
        }
    }

}
