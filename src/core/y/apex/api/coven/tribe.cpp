#include "y/apex/api/coven/tribe.hpp"


namespace Yttrium
{

    namespace Coven
    {

        Tribe:: ~Tribe() noexcept
        {
            quit();
        }
        
        std::ostream & operator<<(std::ostream &os, const Tribe &tribe)
        {
            os << "\t<Tribe basis=" << tribe.basis;
            if( tribe.ready->size) os << ":" << tribe.ready;
#if Y_Coven_Stamp
            os << " @" << tribe.stamp;
#endif
            os << ">" << std::endl;
            //os << *tribe.family << std::endl;
            if(tribe.family) os << *tribe.family << std::endl;
            os << "\t</Tribe>";
            return os;
        }


        void Tribe:: quit() noexcept
        {
            if(family) { fpool.store(family); Coerce(family) = 0; }
            basis.free();
            ready.free();
#if Y_Coven_Stamp
            stamp.free();
#endif
        }

        void Tribe:: remove(const size_t indx) noexcept
        {
            basis.remove(indx);
            ready.remove(indx);
#if Y_Coven_Stamp
            stamp.remove(indx);
#endif
        }


        SignType Tribe:: Compare(const Tribe * const lhs, const Tribe * const rhs) noexcept
        {
            assert(lhs);
            assert(rhs);
            return IList::Compare(lhs->basis,rhs->basis);
        }

    }

}
