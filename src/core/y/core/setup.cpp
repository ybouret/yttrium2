#include "y/core/setup.hpp"
#include <iostream>

namespace Yttrium
{
    namespace Core
    {
        const char * const Success = "Success";
        const char * const Failure = "Failure";
        const char * const Unknown = "Unknown";

        std::ostream & Indent(std::ostream & os,
                                size_t       count,
                              const char     separator)
        {
            while(count-- > 0 ) os << separator;
            return os;
        }
    }
}
