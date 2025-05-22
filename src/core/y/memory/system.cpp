
#include "y/memory/system.hpp"
#include "y/system/exception.hpp"
#include "y/check/usual.hpp"

#include <cstdlib>
#include <cerrno>
#include <iostream>

namespace Yttrium
{
    namespace Memory
    {
        System:: System() :
        Singleton<System, GiantLockPolicy>(),
        Allocator(CallSign),
        allocated(0)
        {
        }

        const char * const System::CallSign = "Memory::System";
        System:: ~System() noexcept
        {
            if(allocated>0)
            {
                std::cerr << "*** " << CallSign << ": still allocated = " << allocated << std::endl;
            }
        }

        void * System:: acquireBlock(size_t &blockSize)
        {
            Y_Lock( access() );
            // get system memory
            assert(blockSize>0);
            void * const blockAddr = calloc(1,blockSize);

            // check return
            if(0==blockAddr)
            {
                const size_t requested = blockSize;
                blockSize = 0;
                throw Libc::Exception(ENOMEM,"%s::Acquire(%lu)", CallSign, (unsigned long) requested);
            }

            // update state and return
            Coerce(allocated) += blockSize;
            return blockAddr;
        }

        void System:: releaseBlock(void *const blockAddr, const size_t blockSize) noexcept
        {
            Y_Lock( access() );
            assert( 0 != blockAddr );
            assert( blockSize > 0  );
            assert( blockSize <= allocated || Die("corrupted allocation") );

            free(blockAddr);
            Coerce(allocated) -= blockSize;

        }



    }

}

#include "y/calculus/base2.hpp"

namespace Yttrium
{
    namespace Memory
    {
        void * System:: acquireDyadic(const unsigned shift)
        {
            static const unsigned MaxShift = Base2<size_t>::MaxShift;
            if(shift>MaxShift) throw Specific::Exception(CallSign, "acquireDyadic(%u>%u)", shift, MaxShift);

            Y_Lock(access());
            const size_t blockSize = Base2<size_t>::One << shift;
            return 0;
        }
    }

}
