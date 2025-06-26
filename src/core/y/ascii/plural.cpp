
#include "y/ascii/plural.hpp"

namespace Yttrium
{

    namespace ASCII
    {
        const char * Plural:: s(const size_t n) noexcept
        {
            return n > 1 ? "s" : "";
        }

        const char * Plural:: S(const size_t n) noexcept
        {
            return n > 1 ? "S" : "";
        }



    }

}


