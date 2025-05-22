#include "y/memory/chunk.hpp"
#include "y/check/usual.hpp"

#include <cstring>

namespace Yttrium
{
    namespace Memory
    {
        uint8_t Chunk:: NumBlocksFor(const size_t userBytes,
                                     const size_t blockSize) noexcept
        {
            assert(blockSize>0);
            const size_t res = userBytes/blockSize;
            if(res<=0xff) return static_cast<uint8_t>(res); else return 0xff;
        }


        Chunk:: Chunk(void * const  blockAddr,
                      const uint8_t numBlocks,
                      const size_t  blockSize) noexcept :
        data( static_cast<uint8_t *>(blockAddr) ),
        firstBlock(0),
        freeBlocks(numBlocks),
        userBlocks(numBlocks),
        last( data + (blockSize * static_cast<size_t>(numBlocks)) )
        {
            assert(Good(blockAddr,numBlocks));
            uint8_t *p=data;
            for(uint8_t i=0;i!=numBlocks;p += blockSize)
            {
                *p = ++i;
            }
        }


        Chunk:: ~Chunk() noexcept
        {
            assert(freeBlocks<=userBlocks);
        }


        bool Chunk:: owns(const void * const address) const noexcept
        {
            return (address >= data) && (address < last);
        }

        Ownership Chunk:: whose(const void * const address) const noexcept
        {
            if(address<data)       return OwnedByPrev;
            if(address>=last)      return OwnedByNext;
            assert(owns(address)); return OwnedByCurr;
        }


        void * Chunk:: acquire(const size_t blockSize) noexcept
        {
            if(freeBlocks<=0) return 0;
            uint8_t * const p = &data[ firstBlock * blockSize ];
            firstBlock = *p;
            --freeBlocks;
            return memset(p,0,blockSize);
        }

        void Chunk:: release(void * const p, const size_t blockSize) noexcept
        {
            assert(0!=p);
            assert(freeBlocks<userBlocks);
            uint8_t * const toRelease = static_cast<uint8_t *>(p);
            const size_t    theOffset = toRelease-data;
            assert( toRelease >= data );
            assert( toRelease <  last );
            assert( 0 == theOffset % blockSize );
            *toRelease = firstBlock;
            const size_t deltaBlocks = theOffset/blockSize; assert(deltaBlocks<=0xff);
            firstBlock = static_cast<uint8_t>(deltaBlocks);
            ++freeBlocks;
        }

    }

}


