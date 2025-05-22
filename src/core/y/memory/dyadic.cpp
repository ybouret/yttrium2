
#include "y/memory/dyadic.hpp"
#include "y/system/exception.hpp"

#include <cstring>
#include <iostream>
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

        Dyadic:: ~Dyadic() noexcept
        {
            clear();
        }


        Dyadic:: Dyadic()  :
        Singleton<Dyadic, GiantLockPolicy>(),
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

            Y_Lock(access);
            void * const blockAddr = calloc(1,blockSize);
            if(0==blockAddr) throw Libc::Exception(ENOMEM,"%s::acquireBlock(%lu)",CallSign, (unsigned long)blockSize);
            
            return blockAddr;
        }

        void Dyadic:: releaseBlock(void * const blockAddr,
                                   const size_t blockSize) noexcept
        {
            assert(0!=blockAddr);
            assert(IsPowerOfTwo(blockSize));
            
        }
    }

}


