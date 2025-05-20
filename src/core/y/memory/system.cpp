
#include "y/memory/system.hpp"
#include "y/system/exception.hpp"
#include <cstdlib>
#include <cerrno>

namespace Yttrium
{
    namespace Memory
    {
        static uint64_t SystemMemory = 0;

        void * System:: Acquire(size_t &blockSize)
        {
            if(blockSize<=0)
            {
                return 0;
            }
            else
            {
                void * const blockAddr = calloc(1,blockSize);
                if(0==blockAddr)
                {
                    const size_t required = blockSize;
                    blockSize = 0;
                    throw Libc::Exception(ENOMEM,"System::Acquire(%lu)", (unsigned long) required);
                }
                SystemMemory += blockSize;
                return blockAddr;
            }
        }
    }

}

