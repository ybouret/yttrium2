
#include "y/memory/allocator/system.hpp"
#include "y/system/exception.hpp"
#include "y/check/usual.hpp"
#include "y/memory/align.hpp"
#include "y/decimal.hpp"

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

        void System:: display(std::ostream &os, const size_t indent) const
        {
            initProlog(os,indent);
            os << " allocated=" << allocated;
            initEpilog(os,true) << std::endl;
        }

        System:: ~System() noexcept
        {
            if(allocated>0)
            {
                std::cerr << "*** " << CallSign << ": still allocated = " << allocated << std::endl;
            }
        }

        void * System:: acquireBlock(size_t &blockSize)
        {
            assert(blockSize>0);

            if(blockSize>Align::MaxBlockSize)
                throw Specific::Exception(CallSign,"blockSize=%s>%s", Decimal(blockSize).c_str(), Decimal(Align::MaxBlockSize).c_str());

            blockSize = Align::Compute::Ceil(blockSize);

            Y_Lock( access );
            // get system memory
            void * const blockAddr = calloc(1,blockSize);

            // check return
            if(0==blockAddr)
                throw Libc::Exception(ENOMEM,"%s::acquireBlock(%lu)", CallSign, (unsigned long) blockSize);


            // update state and return
            Coerce(allocated) += blockSize;
            return blockAddr;
        }

        void System:: releaseBlock(void *const blockAddr, const size_t blockSize) noexcept
        {
            Y_Lock( access );
            assert( 0 != blockAddr );
            assert( blockSize > 0  );
            assert( (blockSize <= allocated) || Die("corrupted allocation") );

            free(blockAddr);
            Coerce(allocated) -= blockSize;
        }

    }

}

