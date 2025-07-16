
#include "y/cameo/genus/aproxy.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Cameo
    {
        AProxyGenus:: AProxyGenus() noexcept
        {
        }

        AProxyGenus:: ~AProxyGenus() noexcept
        {
        }

        const char * const AProxyGenus:: CallSign = "AProxy";

        void AProxyGenus:: Overflow()
        {
            throw Libc::Exception(ERANGE,"AProxy Overflow");
        }
    }

}
