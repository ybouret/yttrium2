
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

            /**
             \param userBlockSize a positive block size
             \param userPageBytes will be set above Limits::MinBlockBytes
             */
            Arena(const size_t userBlockSize,
                  const size_t userPageBytes);
            ~Arena() noexcept;

            void  * acquire();

            bool    isValid() const noexcept;

        private:
            size_t         available; //!< available blocks
            Chunk *        acquiring;
            Chunk *        releasing;
            Chunk *        chunk;
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

            Chunk *makeInPlaceChunk(void * const);
            void   releaseAllChunks() noexcept;
            void   releaseWorkspace() noexcept;
            void   newChunkRequired();
        };
    }

}

#endif

