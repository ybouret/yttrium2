
#include "y/ascii/boolean.hpp"

namespace Yttrium
{

    namespace ASCII
    {
        const char * Boolean:: Text(const bool flag) noexcept
        {
            return flag ? "True" : "False";
        }

        const char * Boolean:: text(const bool flag) noexcept
        {
            return flag ? "true" : "false";
        }
    }

}

