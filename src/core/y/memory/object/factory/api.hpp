
//! \file

#ifndef Y_Memory_Object_Factory_API_Included
#define Y_Memory_Object_Factory_API_Included 1

#include "y/concurrent/life-time.hpp"

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
                explicit FactoryAPI(const size_t userPageBytes,
                                    const size_t userMaxBlockSize);


            private:
                Y_Disable_Copy_And_Assign(FactoryAPI);
            };

        }
    }

}

#endif

