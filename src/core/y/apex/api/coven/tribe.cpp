#include "y/apex/api/coven/tribe.hpp"


namespace Yttrium
{

    namespace Coven
    {

        Tribe:: ~Tribe() noexcept
        {

        }


        std::ostream & operator<<(std::ostream &os, const Tribe &tribe)
        {
            os << "<Tribe basis=" << tribe.basis;
            if( tribe.ready->size) os << ":" << tribe.ready;
            os << " @" << tribe.stamp;
            os << "/>";
            return os;
            
            os << "</Tribe>";
            return os;
        }
    }

}
