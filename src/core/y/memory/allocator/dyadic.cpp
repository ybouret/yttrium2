
#include "y/memory/allocator/dyadic.hpp"
#include "y/system/exception.hpp"
#include "y/check/usual.hpp"
#include "y/decimal.hpp"

#include <cstring>
#include <iostream>
#include <iomanip>
#include <cstdlib>

namespace Yttrium
{
    namespace Memory
    {
        const char * const Dyadic:: CallSign = "Memory::Dyadic";

        const size_t Dyadic::MaxBlockBytes;

        void Dyadic:: clear() noexcept
        {
            memset(Coerce(allocated),0,sizeof(allocated));
        }

        void Dyadic:: display(std::ostream &os, const size_t indent) const
        {
            init(os,indent) << std::endl;
            bool         hasData = false;
            const size_t sub = indent+1;
            for(unsigned shift=MinBlockShift;shift<=MaxBlockShift;++shift)
            {
                const size_t &n = allocated[shift]; if(n<=0) continue;
                hasData = true;
                XML::Indent(os,sub) << "|2^"
                << std::setw(2) << shift
                << "| = |" << std::setw(6) << (Base2<size_t>::One<<shift) << "| : # "
                << n << std::endl;
            }
            if(!hasData) XML::Indent(os,sub) << "Empty..." << std::endl;;
            quit(os,indent) << std::endl;
        }

        Dyadic:: ~Dyadic() noexcept
        {
            for(unsigned shift=MinBlockShift;shift<=MaxBlockShift;++shift)
            {
                const size_t &n = allocated[shift]; if(n<=0) continue;
                std::cerr << "*** " << CallSign 
                << " missing |2^"
                << std::setw(2) << shift
                << "| = |" << std::setw(6) << (Base2<size_t>::One<<shift) << "| : # "
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
            if(blockSize>MaxBlockBytes) throw Specific::Exception(CallSign,"blockSize=%s > %s", Decimal(blockSize).c_str(), Decimal(MaxBlockBytes).c_str());
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
            --Coerce(allocated[blockShift]);
            free( memset(blockAddr,0,blockSize) );
        }


        void * Dyadic:: acquireUnlockedDyadic(const unsigned blockShift)
        {
            static const size_t _1 = 1;
            assert(blockShift<=MaxBlockShift);
            assert(blockShift>=MinBlockShift);
            const size_t blockSize = _1 << blockShift;

            void * const blockAddr = calloc(1,blockSize);
            if(0==blockAddr) throw Libc::Exception(ENOMEM,"%s::acquireDyadic(2^%u)",CallSign,blockShift);

            ++Coerce(allocated[blockShift]);
            return blockAddr;
        }

        void * Dyadic:: acquireDyadic(const unsigned blockShift)
        {
            Y_Lock(access);
            return acquireUnlockedDyadic(blockShift);
        }

        void  Dyadic:: releaseUnlockedDyadic(void *const blockAddr, const unsigned int blockShift) noexcept
        {
            static const size_t _1 = 1;
            assert(0 != blockAddr);
            assert(blockShift<=MaxBlockShift);
            assert(blockShift>=MinBlockShift);
            assert( allocated[blockShift] > 0 || Die("corrupted release") );


            --Coerce(allocated[blockShift]);
            free( memset(blockAddr,0,_1<<blockShift) );
        }

        void  Dyadic:: releaseDyadic(void *const blockAddr, const unsigned int blockShift) noexcept
        {
            Y_Lock(access);
            return releaseUnlockedDyadic(blockAddr,blockShift);
        }
    }

}


