
//! \file

#ifndef Y_Memory_Chunk_Included
#define Y_Memory_Chunk_Included 1

#include "y/memory/ownership.hpp"

namespace Yttrium
{
    namespace Memory
    {
        //______________________________________________________________________
        //
        //
        //
        //! Basic chunk to hold a limited count of blocks
        //
        //
        //______________________________________________________________________
        class Chunk
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const unsigned MinNumBlocks = 0x04;
            static const unsigned MaxNumBlocks = 0xff;
            static const size_t   MinUserBytes = 128;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            //! initialize provided memory
            /**
             \param blockAddr available memory >= numBlocks*blockSize
             \param numBlocks in 0:255
             \param blockSize positive blockSize
             */
            Chunk(void * const  blockAddr,
                  const uint8_t numBlocks,
                  const size_t  blockSize) noexcept;

            //! cleanup
            ~Chunk() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! acquire a clean block if possible
            /**
             \param blockSize the block size
             \return NULL if full or a zeroed block if found
             */
            void * acquire(const size_t blockSize) noexcept;

            //! release a previously acquire block
            /**
             \param p         a valid address
             \param blockSize with its block size
             */
            void  release(void * const p, const size_t blockSize) noexcept;


            //! number of blocks for a given memory amount
            /**
             \param userBytes memory amount
             \param blockSize block size to use
             \return truncated number of blocks
             */
            static uint8_t NumBlocksFor(const size_t userBytes,
                                        const size_t blockSize) noexcept;


            static unsigned BlockShiftFor(const size_t   blockSize,
                                          const size_t   pageBytes) noexcept;

            //! check address is within
            /**
             \param address the address
             \return address >= data && address < last
             */
            bool owns(const void * const address) const noexcept;

            //! check ownership
            /**
             \param address the address
             \return address position
             */
            Ownership whose(const void * const address) const noexcept;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            uint8_t * const       data;       //!< base address
            uint8_t               firstBlock; //!< first available block
            uint8_t               freeBlocks; //!< number of free blocks
            const uint8_t         userBlocks; //!< initial number of blocks
            const uint8_t * const last;       //!< first invalid address
            

        private:
            Y_Disable_Copy_And_Assign(Chunk); //!< discarding
        };
    }

}

#endif

