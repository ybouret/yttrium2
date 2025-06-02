
//! \file

#ifndef Y_Memory_Dyads_Included
#define Y_Memory_Dyads_Included 1

#include "y/memory/object/factory.hpp"
#include "y/concurrent/singleton/alias-lock-policy.hpp"

namespace Yttrium
{
    namespace Memory
    {
        typedef AliasLockPolicy<Object::Factory> DyadsLockPolicy;

        //! produce all possible power-of-two blocks
        class Dyads : public Singleton<Dyads,DyadsLockPolicy>
        {
        public:
            static const char * const CallSign;                            //!< "Memory::Dyads"
            static const Longevity    LifeTime = LifeTimeOf:: MemoryDyads; //!< life time
        private:
            Y_Disable_Copy_And_Assign(Dyads); //!< discarding
            explicit Dyads();                 //!< setup
            virtual ~Dyads() noexcept;        //!< cleanup

            friend class Singleton<Dyads,DyadsLockPolicy>;
        };


    }

}

#endif

