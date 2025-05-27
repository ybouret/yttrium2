
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
            static const char * const CallSign; //!< "Memory::Arena"

            //! initialize
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
            Chunk *        acquiring; //!< cache for acquiring chunk
            Chunk *        releasing; //!< cache for releasing chunk
            Chunk *        workspace; //!< chunk workspace
            size_t         count;     //!< number of active chunks
            size_t         capacity;  //!< maximum number of active chunks
            Chunk *        endChunk;  //!< first invalid chunk address
            size_t         memBytes;  //!< bytes used to hold workspace
            unsigned       memShift;  //!< memBytes=2^memShift


        public:
            const size_t   blockSize; //!< for all Chunks
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

