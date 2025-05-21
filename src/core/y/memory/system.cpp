
#include "y/memory/system.hpp"
#include "y/system/exception.hpp"
#include <cstdlib>
#include <cerrno>
#include <iostream>

namespace Yttrium
{
    namespace Memory
    {
        System:: System() :
        Singleton<System, GiantLockPolicy>(),
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

        void * System:: acquire(size_t &blockSize)
        {
            if(blockSize<=0)
            {
                return 0;
            }
            else
            {
                void * const blockAddr = calloc(1,blockSize);
                assert( Memory::Stealth::Are0(blockAddr,blockSize) );
                if(0==blockAddr)
                {
                    const size_t required = blockSize;
                    blockSize = 0;
                    throw Libc::Exception(ENOMEM,"System::Acquire(%lu)", (unsigned long) required);
                }
                Coerce(allocated) += blockSize;
                return blockAddr;
            }
        }
    }

}

