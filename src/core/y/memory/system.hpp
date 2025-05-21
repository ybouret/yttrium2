
//! \file

#ifndef Y_Memory_System_Included
#define Y_Memory_System_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {

        struct System
        {
            static void * Acquire(size_t &blockSize);
            static void   Release(void * &blockAddr, size_t &blockSize) noexcept;
        };

    }

}

#endif

