//! \file

#ifndef Y_Memory_Object_Factory_Included
#define Y_Memory_Object_Factory_Included 1

#include "y/memory/object/factory/api.hpp"
#include "y/singleton.hpp"
#include "y/concurrent/singleton/broad-lock-policy.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Object
        {


            class Factory : public Singleton<Factory,BroadLockPolicy>
            {
            public:

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

