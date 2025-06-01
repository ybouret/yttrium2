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

            class Guild;

            class Factory : public FactoryAPI, public Singleton<Factory,BroadLockPolicy>
            {
            public:
                static const size_t PAGE_BYTES = 1000; //!< default page size

                virtual void display(std::ostream &,size_t) const;

                //! LOCKED
                void * acquireBlock(const size_t blockSize);

                //! LOCKED
                void   releaseBlock(void * const blockAddr, const size_t blockSize) noexcept;

                template <typename T> inline
                T *acquireBlockFor() { return static_cast<T *>(acquireBlock(sizeof(T))); }

                template <typename T> inline
                void releaseBlockFor( T * const zombi ) { releaseBlock(zombi,sizeof(T)); }



            private:
                Y_Disable_Copy_And_Assign(Factory); //!< discarding
                friend class Singleton<Factory,BroadLockPolicy>;
                friend class Guild;
                explicit Factory();          //!< setup
                virtual ~Factory() noexcept; //!< cleanup

            };
        }
    }
}

#endif

