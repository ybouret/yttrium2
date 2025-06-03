
//! \file

#ifndef Y_Memory_Dyadic_Included
#define Y_Memory_Dyadic_Included 1

#include "y/memory/allocator.hpp"
#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/concurrent/singleton/broad-lock-policy.hpp"

namespace Yttrium
{
    namespace Memory
    {

        class Pooled :
        public Singleton<Pooled,BroadLockPolicy>,
        public Allocator
        {
        public:
            static const char * const CallSign; //!< "Memory::Pooled"
            static const Longevity    LifeTime =  LifeTimeOf::PooledMemory;
            class Code;

            // Interface
            virtual void display(std::ostream &,size_t) const;

        private:
            Y_Disable_Copy_And_Assign(Pooled);
            friend class Singleton<Pooled,BroadLockPolicy>;
            Code * const code;

            explicit Pooled();
            virtual ~Pooled() noexcept;

            virtual void * acquireBlock(size_t &blockSize);
            virtual void   releaseBlock(void * const blockAddr,
                                        const size_t blockSize) noexcept;
        };

    }

}

#endif

