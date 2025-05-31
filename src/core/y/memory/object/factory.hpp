//! \file

#ifndef Y_Memory_Object_Factory_Included
#define Y_Memory_Object_Factory_Included 1

#include "y/singleton.hpp"
#include "y/concurrent/singleton/broad-lock-policy.hpp"
#include "y/concurrent/life-time.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Object
        {

            
            class Factory : public Singleton<Factory,BroadLockPolicy>
            {
            public:
                static const char * const CallSign;
                static const Longevity    LifeTime = LifeTimeOf::MemoryObjectFactory;

            private:
                Y_Disable_Copy_And_Assign(Factory);
                friend class Singleton<Factory,BroadLockPolicy>;
                explicit Factory();
                virtual ~Factory() noexcept;

            };
        }
    }
}

#endif

