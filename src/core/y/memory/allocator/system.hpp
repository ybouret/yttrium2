
//! \file

#ifndef Y_Memory_System_Included
#define Y_Memory_System_Included 1

#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/memory/allocator.hpp"
#include "y/concurrent/singleton/giant-lock-policy.hpp"

namespace Yttrium
{
    namespace Memory
    {


        //______________________________________________________________________
        //
        //
        //
        //! calloc/free wrapper
        //
        //
        //______________________________________________________________________
        class System :
        public Singleton<System,GiantLockPolicy>,
        public Allocator
        {
        public:
            static const char * const CallSign;                            //!< "Memory::System"
            static const Longevity    LifeTime = LifeTimeOf::SystemMemory; //!< longevity
            const uint64_t            allocated;                           //!< currently allocated bytes

            virtual void display(std::ostream &,size_t) const;
            
        private:
            friend class Singleton<System,GiantLockPolicy>;
            Y_Disable_Copy_And_Assign(System); //!< discarding
            explicit System();                 //!< setup
            virtual ~System() noexcept;        //!< cleanup with warning if allocated>0

            virtual void * acquireBlock(size_t & blockSize);
            virtual void   releaseBlock(void * const blockAddr,
                                        const size_t blockSize) noexcept;
        };


    }

}

#endif

