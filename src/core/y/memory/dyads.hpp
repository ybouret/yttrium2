
//! \file

#ifndef Y_Memory_Dyads_Included
#define Y_Memory_Dyads_Included 1

#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/concurrent/singleton/broad-lock-policy.hpp"
//#include "y/concurrent/singleton/alias-lock-policy.hpp"

namespace Yttrium
{
    namespace Memory
    {

        //! produce all possible power-of-two blocks
        class Dyads : public Singleton<Dyads,BroadLockPolicy>
        {
        public:
            static const char * const CallSign;                            //!< "Memory::Dyads"
            static const Longevity    LifeTime = LifeTimeOf:: MemoryDyads; //!< life time
        private:
            Y_Disable_Copy_And_Assign(Dyads); //!< discarding
            explicit Dyads();                 //!< setup
            virtual ~Dyads() noexcept;        //!< cleanup
        };


    }

}

#endif

