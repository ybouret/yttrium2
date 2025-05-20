//! \file

#ifndef Y_Memory_Stealth_Included
#define Y_Memory_Stealth_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {

        struct Stealth
        {

            static void *       Address(void * const       address) noexcept;
            static const void * Address(const void * const address) noexcept;

            static void *       Zero(void * const blockAddr,
                                     const size_t blockSize) noexcept;

            static bool         Are0(const void * const blockAddr,
                                     const size_t       blockSize) noexcept;
        };
    }

#define Y_Memory_BZero(BLOCK) Memory::Stealth::Zero(BLOCK,sizeof(BLOCK))

}

#endif

