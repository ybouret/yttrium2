
//! \file

#ifndef Y_Memory_Dyads_Included
#define Y_Memory_Dyads_Included 1

#include "y/singleton.hpp"
#include "y/calculus/base2.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/concurrent/singleton/broad-lock-policy.hpp"

namespace Yttrium
{
    namespace Memory
    {

        class Dyads : public Singleton<Dyads,BroadLockPolicy>
        {
        public:
            static const char * const CallSign;
            static const Longevity    LifeTime = LifeTimeOf:: MemoryDyads;
        private:
            Y_Disable_Copy_And_Assign(Dyads);
            explicit Dyads();
            virtual ~Dyads() noexcept;
        };


    }

}

#endif

