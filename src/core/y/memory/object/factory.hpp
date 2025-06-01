//! \file

#ifndef Y_Memory_Object_Factory_Included
#define Y_Memory_Object_Factory_Included 1

#include "y/singleton.hpp"
#include "y/concurrent/singleton/broad-lock-policy.hpp"
#include "y/memory/object/factory/api.hpp"

namespace Yttrium
{
    namespace Memory
    {
        namespace Object
        {

            class Factory : public FactoryAPI, public Singleton<Factory,BroadLockPolicy>
            {
            public:
                static const size_t PAGE_BYTES = 1000; //!< default page size

                virtual void display(std::ostream &,size_t) const;

                void * acquireBlock(const size_t blockSize);
                void   releaseBlock(void * const blockAddr, const size_t blockSize) noexcept;
                

            private:
                Y_Disable_Copy_And_Assign(Factory); //!< discarding
                friend class Singleton<Factory,BroadLockPolicy>;
                explicit Factory();          //!< setup
                virtual ~Factory() noexcept; //!< cleanup

            };
        }
    }
}

#endif

