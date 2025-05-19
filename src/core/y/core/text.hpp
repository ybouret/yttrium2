//! \file

#ifndef Y_Core_Text_Included
#define Y_Core_Text_Included 1

#include "y/system/platform.hpp"
#include "y/system/types.hpp"


namespace Yttrium
{
    namespace Core
    {
        struct Text
        {
            static size_t  Length(const char * const text) noexcept;
            static char *  Copy(char * const       outputBuffer,
                                const size_t       outputLength,
                                const char * const text) noexcept;
        };
    }

}

#endif

