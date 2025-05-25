
//! \file

#ifndef Y_Memory_Arena_Included
#define Y_Memory_Arena_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {

        class Chunk;

        class Arena
        {
        public:
            static const char * const CallSign;
            
            Arena(const size_t userBlockSize,
                  const size_t userPageBytes);
            ~Arena() noexcept;

            
            const size_t   blockSize;
            const unsigned userShift;
            const uint8_t  numBlocks;
            const size_t   userBytes;
            
        private:
            Y_Disable_Copy_And_Assign(Arena);
        };
    }

}

#endif

