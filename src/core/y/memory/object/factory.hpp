//! \file

#ifndef Y_Memory_Object_Factory
#define Y_Memory_Object_Factory 1

#include "y/singleton.hpp"
#include "y/concurrent/life-time.hpp"
#include "y/concurrent/singleton/broad-lock-policy.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Object
        {

            class FactoryAPI
            {
            public:
                static const char * const              CallSign; //!< "Memory::Object::Factory"
                static const System::AtExit::Longevity LifeTime = LifeTimeOf::MemoryObjectFactory;

                virtual ~FactoryAPI() noexcept;

            protected:
                explicit FactoryAPI(const size_t pageBytes,
                                    const size_t maxBlockSize);
            private:
                Y_Disable_Copy_And_Assign(FactoryAPI);
            };

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

