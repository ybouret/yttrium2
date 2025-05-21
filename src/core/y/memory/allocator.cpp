
#include "y/memory/allocator.hpp"
#include "y/memory/align.hpp"
#include "y/system/exception.hpp"
#include "y/memory/stealth.hpp"

namespace Yttrium
{
    namespace Memory
    {

        Allocator:: ~Allocator() noexcept
        {

        }

        Allocator:: Allocator(const char * const persistentCallSign) noexcept :
        CallSign_(persistentCallSign)
        {
            assert(0!=CallSign_);
        }



        void * Allocator:: acquire(size_t &blockSize)
        {
            if(blockSize<=0)
            {
                return 0;
            }
            else
            {
                // align and keep requested bytes
                if(blockSize>Align::MaxBlockSize)
                    throw Specific::Exception(CallSign_, "blockSize overflow");
                blockSize = Align::Compute::Ceil(blockSize);
                const size_t requested = blockSize;

                // safe allocation with check
                try {
                    void * const blockAddr = acquireBlock(blockSize);
                    if(blockSize < requested)
                    {
                        releaseBlock(blockAddr,blockSize);
                        throw Specific::Exception(CallSign_,"corrupted acquireBlock");
                    }

                    assert( Memory::Stealth::Are0(blockAddr,blockSize) );
                    return blockAddr;
                }
                catch(...)
                {
                    blockSize = 0;
                    throw;
                }
            }
        }

        void Allocator:: release(void * & blockAddr, size_t & blockSize) noexcept
        {
            if(0==blockAddr)
            {
                assert(0==blockSize);
                return;
            }
            else
            {
                releaseBlock(blockAddr,blockSize);
                blockAddr = 0;
                blockSize = 0;
            }
        }



    }

}
