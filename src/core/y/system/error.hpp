
//! \file

#ifndef Y_System_Error_Included
#define Y_System_Error_Included 1


#include "y/system/platform.hpp"
#include "y/system/compiler.hpp"
#include "y/system/types.hpp"

namespace Yttrium
{
    namespace Libc
    {
        struct Error
        {
            typedef int Type;
            static char * Format(char * const errorBuffer,
                                 const size_t errorLength,
                                 const Type   errorCode) noexcept;
        };

    }

    namespace Windows
    {
        struct Error
        {
            typedef uint32_t Type;
            static char * Format(char * const errorBuffer,
                                 const size_t errorLength,
                                 const Type   errorCode) noexcept;
        };
    }

    namespace System
    {
#if defined(Y_BSD)
        typedef Libc::Error Error;
#endif

#if defined(Y_WIN)
        typedef Windows::Error Error;
#endif
    }


}

#endif

