
#include "y/memory/allocator/dyadic.hpp"
#include "y/system/exception.hpp"
#include "y/check/usual.hpp"

#include <cstring>
#include <iostream>
#include <iomanip>
#include <cstdlib>

namespace Yttrium
{
    namespace Memory
    {
        const char * const Dyadic:: CallSign = "Memory::Dyadic";


        void Dyadic:: clear() noexcept
        {
            memset(Coerce(allocated),0,sizeof(allocated));
        }

        void Dyadic:: display(std::ostream &os) const
        {
            os << '<' << CallSign  << '>' << std::endl;
            for(unsigned shift=MinBlockShift;shift<=MaxBlockShift;++shift)
            {
                const size_t &n = allocated[shift]; if(n<=0) continue;
                os << "\t|2^"
                << std::setw(2) << shift
                << "| = |" << std::setw(6) << (Base2<size_t>::One<<shift) << "| = "
                << n << std::endl;
            }
            os << '<' << CallSign  << '/' << '>' << std::endl;
        }

        Dyadic:: ~Dyadic() noexcept
        {
            for(unsigned shift=MinBlockShift;shift<=MaxBlockShift;++shift)
            {
                const size_t &n = allocated[shift]; if(n<=0) continue;
                std::cerr << "*** " << CallSign 
                << " missing |2^"
                << std::setw(2) << shift
                << "| = |" << std::setw(6) << (Base2<size_t>::One<<shift) << "| = "
                << n << std::endl;
            }
            clear();
        }


        Dyadic:: Dyadic()  :
        Singleton<Dyadic, GiantLockPolicy>(),
        Allocator(CallSign),
        allocated()
        {
            clear();
        }


        void * Dyadic:: acquireBlock(size_t & blockSize)
        {
            if(blockSize>MaxBlockBytes) throw Specific::Exception(CallSign,"blockSize=%lu > %lu", (unsigned long)blockSize, (unsigned long)MaxBlockBytes);
            if(blockSize<MinBlockBytes) blockSize = MinBlockBytes;
            unsigned blockShift = 0;
            blockSize = NextPowerOfTwo(blockSize,blockShift);
            assert(blockShift<=MaxBlockShift);
            assert(blockShift>=MinBlockShift);

            Y_Lock(access);
            void * const blockAddr = calloc(1,blockSize);
            if(0==blockAddr) throw Libc::Exception(ENOMEM,"%s::acquireBlock(%lu)",CallSign, (unsigned long)blockSize);

            ++Coerce(allocated[blockShift]);
            return blockAddr;
        }

        void Dyadic:: releaseBlock(void * const blockAddr,
                                   const size_t blockSize) noexcept
        {
            assert(0!=blockAddr);
            assert(IsPowerOfTwo(blockSize));
            const unsigned blockShift = Base2<size_t>::ExactLog(blockSize);
            assert(blockShift>=MinBlockShift);
            assert(blockShift<=MaxBlockShift);

            Y_Lock(access);
            assert( allocated[blockShift] > 0 || Die("corrupted release") );
            free(blockAddr);
            --Coerce(allocated[blockShift]);
        }

        void * Dyadic:: acquireDyadic(const unsigned blockShift)
        {
            static const size_t _1 = 1;
            assert(blockShift<=MaxBlockShift);
            assert(blockShift>=MinBlockShift);
            const size_t blockSize = _1 << blockShift;

            Y_Lock(access);
            void * const blockAddr = calloc(1,blockSize);
            if(0==blockAddr) throw Libc::Exception(ENOMEM,"%s::acquireDyadic(2^%u)",CallSign,blockShift);
            
            ++Coerce(allocated[blockShift]);
            return blockAddr;
        }

    }

}


