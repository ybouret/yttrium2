//! \file

#ifndef Y_Memory_Dead_Pool_Included
#define Y_Memory_Dead_Pool_Included 1

#include "y/type/ingress.hpp"
#include "y/memory/page.hpp"
#include "y/core/linked/pool.hpp"
#include "y/memory/small/guild.hpp"
#include "y/ability/collectable.hpp"

namespace Yttrium
{
    namespace Memory
    {

        class DeadPool : public Collectable, public Ingress<const Core::LinkedInfo>
        {
        public:
            explicit DeadPool(const size_t blockSize);
            virtual ~DeadPool() noexcept;


            // Interface
            virtual void   gc(const uint8_t) noexcept;

            // Methods
            void * query();
            void   store(void * const zombi) noexcept;
            void   cache(size_t n);

        private:
            Y_Disable_Copy_And_Assign(DeadPool);
            Y_Ingress_Decl();
            Core::PoolOf<Page>    zpool;
            const size_t          bytes;
            Memory::Object::Guild guild;


        };
    }
}

#endif

