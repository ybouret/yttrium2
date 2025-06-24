
//!\ file


#ifndef Y_String_Format_Included
#define Y_String_Format_Included 1

#include "y/string.hpp"
#include "y/check/printf.hpp"

namespace Yttrium
{

    struct Formatted
    {
        static String Get(const char * const fmt,...) Y_Printf_Check(1,2);
    };

}
#endif
