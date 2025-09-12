
#include "y/chemical/plexus/conservation/broken.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {
            Broken:: Broken(const Broken & _) noexcept :
            law(_.law),
            xs(_.xs),
            dc(_.dc)
            {

            }

            Broken:: Broken(const Law & _law, const xreal_t _xs) noexcept :
            law(_law),
            xs(_xs),
            dc(xs/law.norm)
            {
            }

            Broken:: ~Broken() noexcept
            {
            }

            std::ostream & operator<<(std::ostream &os, const Broken &broken)
            {
                os << std::setw(22) << broken.dc.str() << " @" << broken.law;
                return os;
            }


            SignType Broken:: Compare(const Broken &lhs, const Broken &rhs) noexcept
            {
                return Sign::Of(lhs.dc,rhs.dc);
            }
        }

    }

}
