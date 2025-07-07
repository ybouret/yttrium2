

//! \file

#ifndef Y_System_Endian_Included
#define Y_System_Endian_Included 1


#include "y/system/compiler.hpp"
#include "y/system/platform.hpp"

namespace Yttrium
{
    struct Endian
    {
        static bool Little() noexcept;
        static bool Big()    noexcept;
        static const char * HumanReadable()  noexcept;
    };
}

#endif
