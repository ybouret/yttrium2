
//! \file

#ifndef Y_Memory_Arena_Included
#define Y_Memory_Arena_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {

        class Chunk;
        class Book;

        class Arena
        {
        public:
            static const char * const CallSign;
            
            Arena(const size_t userBlockSize,
                  const size_t userPageBytes);
            ~Arena() noexcept;

        private:
            Chunk * const  chunk;
            size_t         count;
            size_t         capacity;
            size_t         memSpace;
            unsigned       memShift;


        public:
            const size_t   blockSize;
            const unsigned userShift; //!< metrics for Chunk userBytes = 2^userShift
            const uint8_t  numBlocks; //!< metrics for Chunk constructor
            const size_t   userBytes; //!< metrics for Chunk memory
            Book          &book;      //!< memory manager
            
        private:
            Y_Disable_Copy_And_Assign(Arena);
        };
    }

}

#endif

