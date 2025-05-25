#include "y/memory/object/chunk.hpp"
#include "y/check/usual.hpp"
#include "y/calculus/base2.hpp"
#include "y/calculus/gcd.hpp"
#include "y/type/sign.hpp"

#include <cstring>
#include <cstdlib>

#include <iostream>
#include <iomanip>

namespace Yttrium
{
    namespace Memory
    {
        uint8_t Chunk:: NumBlocksFor(const size_t blockSize,
                                     const size_t userBytes) noexcept
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
                size_t   numer;      //!< numerator   of lost/user
                size_t   denom;      //!< denominator of lost/user

                //! compare ratios
                static inline
                SignType CompareRatios(const ChunkMetrics &lhs,
                                       const ChunkMetrics &rhs) noexcept
                {
                    assert(lhs.denom>0);
                    assert(rhs.denom>0);
                    const uint64_t L = uint64_t(lhs.numer) * uint64_t(rhs.denom);
                    const uint64_t R = uint64_t(rhs.numer) * uint64_t(lhs.denom);
                    return Sign::Of(L,R);
                }


                //! compare by increasing ratios/decreasibg
                static inline
                int Compare(const void * const lhs, const void * const rhs) noexcept
                {
                    assert(0!=lhs);
                    assert(0!=rhs);
                    const ChunkMetrics &L = *static_cast<const ChunkMetrics *>(lhs);
                    const ChunkMetrics &R = *static_cast<const ChunkMetrics *>(rhs);

                    switch( CompareRatios(L,R) )
                    {
                        case Negative: return -1;
                        case Positive: return  1;
                        case __Zero__: break;
                    }

                    // decreasing user bytes
                    return int( Sign::Of(R.userBytes,L.userBytes) );

                }

            };
        }

        size_t Chunk:: UserBytesFor(const size_t blockSize,
                                    const size_t pageBytes,
                                    unsigned    &userShift,
                                    uint8_t     &numBlocks) noexcept
        {

            assert(blockSize>0);

            // construct all possible metrics from MinNumBlocks to 255
            ChunkMetrics cms[256];
            size_t       num = 0;
            memset(cms,0,sizeof(cms));

            for(unsigned nb=MinNumBlocks;nb<=MaxNumBlocks;++nb)
            {
                ChunkMetrics &cm = cms[num];
                const size_t requested = blockSize*nb;
                cm.numBlocks = nb;
                cm.userBytes = NextPowerOfTwo(requested,cm.userShift);
                if(cm.userBytes<MinUserBytes)
                {
                    // drop: too small
                    continue;
                }

                if(num>0 && cm.userBytes>pageBytes)
                {
                    // done : too big
                    break;
                }

                cm.lostBytes = cm.userBytes - requested;
                SimplifyByGCD(cm.numer = cm.lostBytes,cm.denom = cm.userBytes);
                ++num;
            }

            
            // order them by least lost ratio first,
            // then by decreasing data size
            qsort(cms,num, sizeof(ChunkMetrics), ChunkMetrics::Compare);


            for(unsigned i=0;i<num;++i)
            {
                const ChunkMetrics &cm = cms[i];
                std::cerr
                << " | numBlocks = " << std::setw(3) << cm.numBlocks
                << " | userBytes = " << std::setw(8) << cm.userBytes
                << " | lostBytes = " << std::setw(8) << cm.lostBytes
                << " @ 2^" << std::setw(2) << cms[i].userShift
                << " ratio=" << double(cm.numer)/double(cm.denom)
                << std::endl;
                break;
            }

            numBlocks = cms[0].numBlocks;
            userShift = cms[0].userShift;
            return      cms[0].userBytes;
        }



        Chunk:: Chunk(void * const  blockAddr,
                      const uint8_t numBlocks,
                      const size_t  blockSize) noexcept :
        data( static_cast<uint8_t *>(blockAddr) ),
        last( data + (blockSize * static_cast<size_t>(numBlocks)) ),
        firstBlock(0),
        freeBlocks(numBlocks),
        userBlocks(numBlocks),
        memoryVoid()
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


