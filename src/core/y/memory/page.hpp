//! \file

#ifndef Y_Memory_Page_Included
#define Y_Memory_Page_Included


#include "y/system/compiler.hpp"

namespace Yttrium
{
    namespace Memory
    {
        struct Page
        {
            Page *next;
            Page *prev;
            static void * Addr(Page * const page, const size_t bytes) noexcept;
            static Page * Cast(void * const addr) noexcept;
        };
    }

}

#endif

