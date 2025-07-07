
#include "y/apex/k/device.hpp"

namespace Yttrium
{
    namespace Apex
    {
        void Device:: shr() noexcept
        {
            Coerce(bits) = api->shr( sync[plan] );
        }
    }
}


