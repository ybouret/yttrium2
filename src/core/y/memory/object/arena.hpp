
//! \file

#ifndef Y_Memory_Arena_Included
#define Y_Memory_Arena_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Object
        {

            class Chunk;
            class Book;

            //__________________________________________________________________
            //
            //
            //
            //! Arena of Chunks of  blockSize
            //
            //
            //__________________________________________________________________
            class Arena
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const char * const CallSign; //!< "Memory::Arena"

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________

                //! initialize
                /**
                 \param userBlockSize a positive block size
                 \param userPageBytes will be set above Limits::MinBlockBytes
                 */
                Arena(const size_t userBlockSize,
                      const size_t userPageBytes);

                //! cleanup
                ~Arena() noexcept;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

                void  * acquire();                //!< \return a zeroed blockSize
                void    release(void *) noexcept; //!< release a prevously acquired block
                bool    isValid() const noexcept; //!< \return various validity tests

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
            private:
                size_t         available; //!< available blocks bookeeping
                Chunk *        acquiring; //!< cache for acquiring chunk
                Chunk *        releasing; //!< cache for releasing chunk
                Chunk *        freeChunk; //!< if a freeChunk exists
                Chunk *        workspace; //!< chunk workspace
                size_t         occupied;  //!< number of occupied chunks
                size_t         capacity;  //!< maximum number of active chunks
                size_t         memBytes;  //!< bytes used to hold workspace
                unsigned       memShift;  //!< memBytes=2^memShift


            public:
                const size_t   blockSize; //!< for all Chunks
                const unsigned userShift; //!< metrics for Chunk userBytes = 2^userShift
                const uint8_t  numBlocks; //!< metrics for Chunk constructor
                const size_t   userBytes; //!< metrics for Chunk memory
                Book &         book;      //!< memory manager
                Arena *        next;      //!< for list
                Arena *        prev;      //!< for list

            private:
                Y_Disable_Copy_And_Assign(Arena); //!< discarding

                //! allocate and format a chunk at a given pre-allocated address
                /**
                 \return a valid chunk with numBlocks available
                 */
                Chunk *makeInPlaceChunk(void * const);
                void   releaseAllChunks() noexcept; //!< release all chunks
                void   releaseWorkspace() noexcept; //!< release workspace
                void   newChunkRequired();          //!< when a new chunk is required
            };
        }
    }

}

#endif

