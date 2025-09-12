
#include "y/chemical/plexus/conservation/broken.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        namespace Conservation
        {
            Broken:: Broken(const Broken & _) noexcept :
            law(_.law),
            xs(_.xs)
            {

            }

            Broken:: Broken(const Law & _law, const xreal_t _xs) noexcept :
            law(_law),
            xs(_xs)
            {
            }

            Broken:: ~Broken() noexcept
            {
            }

            std::ostream & operator<<(std::ostream &os, const Broken &broken)
            {
                os << std::setw(22) << broken.xs << " @" << broken.law;
                return os;
            }

        }

    }

}
