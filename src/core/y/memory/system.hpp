
//! \file

#ifndef Y_Memory_System_Included
#define Y_Memory_System_Included 1

#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"

namespace Yttrium
{
    namespace Memory
    {


        class System : public Singleton<System,GiantLockPolicy>
        {
        public:
            static const char * const CallSign; //!< "Memory::System"
            static const Longevity    LifeTime = LifeTimeOf::SystemMemory;

            void * acquire(size_t &blockSize);
            void   release(void * &blockAddr, size_t &blockSize) noexcept;

            const uint64_t allocated;

        private:
            Y_Disable_Copy_And_Assign(System);
            friend class Singleton<System,GiantLockPolicy>;
            explicit System();
            virtual ~System() noexcept;
        };


    }

}

#endif

