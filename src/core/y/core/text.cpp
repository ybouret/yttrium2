#include "y/core/text.hpp"
#include <cstring>

namespace Yttrium
{
    namespace Core
    {
        size_t Text:: Length(const char * const text) noexcept
        {
            return 0 != text ? strlen(text) : 0;
        }
    }

}
