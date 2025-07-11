#include "y/cameo/multiplier/aproxy.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Cameo
    {
        void AProxyMultiplierInfo:: Overflow()
        {
            throw Libc::Exception(ERANGE,"AProxyMultiplier overflow");
        }
    }
}


