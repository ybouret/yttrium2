#include "y/core/linked/info.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Core
    {

        LinkedInfo:: LinkedInfo() noexcept : size(0) {}

        LinkedInfo:: ~LinkedInfo() noexcept
        {
            assert(0==size);
        }
    }

}

