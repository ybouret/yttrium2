#include "y/memory/chunk.hpp"
#include "y/check/usual.hpp"
#include "y/calculus/base2.hpp"
#include "y/type/sign.hpp"

#include <cstring>
#include <cstdlib>

#include <iostream>
#include <iomanip>

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


        namespace
        {
            struct ChunkMetrics
            {
                unsigned numBlocks;
                unsigned userShift;
                size_t   userBytes;
                size_t   lostBytes;

                //! compare by increasing lostBytes/decreasing userBytes
                static inline
                int Compare(const void * const lhs, const void * const rhs) noexcept
                {
                    assert(0!=lhs);
                    assert(0!=rhs);
                    const ChunkMetrics &L = *static_cast<const ChunkMetrics *>(lhs);
                    const ChunkMetrics &R = *static_cast<const ChunkMetrics *>(rhs);

                    if( L.lostBytes < R.lostBytes )
                        return -1;
                    else
                    {
                        if(R.lostBytes < L.lostBytes)
                            return 1;
                        else
                        {
                            // decreasing
                            return int( Sign::Of(R.userBytes,L.userBytes) );
                        }
                    }

                }




            };
        }

        unsigned Chunk:: BlockShiftFor(const size_t   blockSize,
                                       const unsigned pageShift) noexcept
        {
            assert(blockSize>0);
            assert(pageShift>=7);

            // construct all possible metrics from 1 to 255
            ChunkMetrics cms[256];
            memset(cms,0,sizeof(cms));

            for(unsigned numBlocks=0x01;numBlocks<=0xff;++numBlocks)
            {
                ChunkMetrics &cm = cms[numBlocks];
                const size_t requested = blockSize*numBlocks;
                cm.numBlocks = numBlocks;
                cm.userBytes = NextPowerOfTwo(requested,cm.userShift);
                cm.lostBytes = cm.userBytes - requested;
            }

            // order them
            qsort(cms+1,255, sizeof(ChunkMetrics), ChunkMetrics::Compare);

            for(unsigned i=0x01;i<=0xff;++i)
            {
                const ChunkMetrics &cm = cms[i];
                //if(cm.lostBytes>cms[1].lostBytes) break;
                std::cerr
                << "   numBlocks = " << std::setw(3) << cms[i].numBlocks
                << " | userBytes = " << std::setw(8) << cms[i].userBytes
                << " | lostBytes = " << std::setw(8) << cms[i].lostBytes
                << " @ 2^" << cms[i].userShift
                << std::endl;
            }


#if 0
            unsigned       maxIndex     = 1;
            {
                const size_t   minLostBytes = cms[1].lostBytes;
                {
                CHECK_NEXT:
                    const unsigned nextIndex = maxIndex+1;
                    if(nextIndex<=0xff && cms[nextIndex].lostBytes == minLostBytes )
                    {
                        maxIndex = nextIndex;
                        goto CHECK_NEXT;
                    }
                }



                for(unsigned i=1;i<=maxIndex;++i)
                {
                    std::cerr
                    << "   numBlocks = " << std::setw(3) << cms[i].numBlocks
                    << " | userBytes = " << std::setw(8) << cms[i].userBytes
                    << " | lostBytes = " << std::setw(8) << cms[i].lostBytes
                    << " @ 2^" << cms[i].userShift
                    << std::endl;
                }
            }
#endif

            return 0;
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
            const size_t    theOffset = static_cast<size_t>(toRelease-data);
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


