#if 0
#include "y/cameo/summator/aproxy.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Cameo
    {
        void AProxySummatorInfo:: Overflow()
        {
            throw Libc::Exception(ERANGE,"AProxySummator overflow");
        }
    }
}

#endif

