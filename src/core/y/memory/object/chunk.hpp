
//! \file

#ifndef Y_Memory_Chunk_Included
#define Y_Memory_Chunk_Included 1

#include "y/memory/ownership.hpp"
#include "y/memory/limits.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Object
        {
            //__________________________________________________________________
            //
            //
            //
            //! Basic chunk to hold a limited count of blocks
            //
            //
            //__________________________________________________________________
            class Chunk
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                static const unsigned MinNumBlocks = 0x04;                   //!< minimal number of blocks per chunk
                static const unsigned MaxNumBlocks = 0xff;                   //!< maximum number of blocks per chunk
                static const size_t   MinUserBytes = Limits::MinBlockBytes;  //!< allows perfect match of 1-byte blocks
                static const size_t   MaxUserBytes = Limits::MaxBlockBytes;  //!< consistency

                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                //! initialize provided memory
                /**
                 \param userSpace available memory >= numBlocks*blockSize
                 \param numBlocks in 0:255
                 \param blockSize positive blockSize
                 */
                Chunk(void * const  userSpace,
                      const uint8_t numBlocks,
                      const size_t  blockSize) noexcept;

                //! cleanup
                ~Chunk() noexcept;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________

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
                 \return true if empty
                 */
                bool  release(void * const p, const size_t blockSize) noexcept;


                //! number of blocks for a given memory amount
                /**
                 \param blockSize block size to use
                 \param userBytes memory amount
                 \return truncated number of blocks
                 */
                static uint8_t NumBlocksFor(const size_t blockSize,
                                            const size_t userBytes) noexcept;


                //! computed once per block-size
                /**
                 Return 2^userShift that minimize the lost/data ratio
                 over MinNumBlocks and MaxNumBlocks,
                 - >= MinUserBytes
                 - <= pageBytes
                 \param blockSize object size
                 \param pageBytes default bytes per page
                 \param userShift log2 of returned value
                 \param numBlocks optimized numBlocks of blockSize
                 \return optimized bytes to allocate per chunk
                 */
                static size_t UserBytesFor(const size_t   blockSize,
                                           size_t         pageBytes,
                                           unsigned      &userShift,
                                           uint8_t       &numBlocks) noexcept;

                //! check address is within
                /**
                 \param address the address
                 \return address >= data && address < last
                 */
                bool owns(const void * const address) const noexcept;

                //! check ownership
                /**
                 \param address the address
                 \return address ownership
                 */
                Ownership whose(const void * const address) const noexcept;

                bool isUsed() const noexcept; //!< \return freeBlocks<userBlocks
                bool isFree() const noexcept; //!< \return freeBlocks>=userBlocks

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                uint8_t * const       data;                          //!< base address
                const uint8_t * const last;                          //!< first invalid address
                uint8_t               firstBlock;                    //!< first available block
                uint8_t               freeBlocks;                    //!< number of free blocks
                const uint8_t         userBlocks;                    //!< initial number of blocks
                const uint8_t         memoryVoid[2*sizeof(void*)-3]; //!< power of two alignment

            private:
                Y_Disable_Copy_And_Assign(Chunk); //!< discarding

            };
        }
    }

}

#endif

