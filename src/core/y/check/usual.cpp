#include "y/check/usual.hpp"
#include <cstring>

namespace Yttrium
{
    bool Good(const void * const addr,
              const size_t       size) noexcept
    {
        return !(0==addr && size>0);
    }

    bool Die(const char * const) noexcept
    {
        return false;
    }

   
}
