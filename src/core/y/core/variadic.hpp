//! \file


#ifndef Y_Core_Variadic_Included
#define Y_Core_Variadic_Included 1

#include "y/check/printf.hpp"
#include <cstdlib>

namespace Yttrium
{
    namespace Core
    {
        struct Variadic
        {
            static int Format(char * const buf,
                              const size_t len,
                              const char * const fmt,
                              void * const       ptr) noexcept;

            static int Sprintf(char * const       buf,
                               const size_t       len,
                               const char * const fmt,
                              ...) noexcept Y_Printf_Check(3,4);
         };
    }
}

#endif

