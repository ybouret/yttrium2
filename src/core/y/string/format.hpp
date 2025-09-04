
//!\ file


#ifndef Y_String_Format_Included
#define Y_String_Format_Included 1

#include "y/string.hpp"
#include "y/check/printf.hpp"

namespace Yttrium
{

    //! formatted string
    struct Formatted
    {
        //! use snprintf \return formatted string
        static String Get(const char * const,...) Y_Printf_Check(1,2);

    };

}
#endif
