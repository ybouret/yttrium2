
#include "y/system/wall-time.hpp"
#include "y/system/platform.hpp"

#if defined(Y_Darwin)
#include "wall-time/darwin.hxx"
#endif

namespace Yttrium
{
    namespace System
    {
        WallTime:: ~WallTime() noexcept
        {
        }
    }

}

