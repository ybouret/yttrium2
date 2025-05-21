
//! \file

#ifndef Y_Memory_System_Included
#define Y_Memory_System_Included 1

#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/memory/allocator.hpp"

namespace Yttrium
{
    namespace Memory
    {


        class System :
        public Singleton<System,GiantLockPolicy>,
        public Allocator
        {
        public:
            static const char * const CallSign; //!< "Memory::System"
            static const Longevity    LifeTime = LifeTimeOf::SystemMemory;


            const uint64_t allocated;

        private:
            Y_Disable_Copy_And_Assign(System);
            friend class Singleton<System,GiantLockPolicy>;
            explicit System();
            virtual ~System() noexcept;

            virtual void * acquireBlock(size_t & blockSize);
            virtual void   releaseBlock(void * const blockAddr,
                                        const size_t blockSize) noexcept;
        };


    }

}

#endif

