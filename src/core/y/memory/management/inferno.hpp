//! \file

#ifndef Y_Memory_Inferno_Included
#define Y_Memory_Inferno_Included 1


#include "y/memory/management/dead-pool.hpp"
#include "y/type/ingress.hpp"
#include "y/type/destruct.hpp"

namespace Yttrium
{
    namespace Memory
    {
#define Y_Inferno_Recover(BUILD) do { \
/**/  void * const addr = deadPool.query();\
/**/    try {\
/**/      return new (addr) BUILD;\
/**/    }\
/**/    catch(...)\
/**/    {\
/**/      deadPool.store(addr);\
/**/      throw;\
/**/  }\
} while(false)

        template <typename T>
        class Inferno : public Ingress<Caching>
        {
        public:
            inline explicit Inferno(size_t requested = 0) : deadPool( sizeof(T) )
            {
                deadPool.cache(requested);
            }

            inline virtual ~Inferno() noexcept {}


            inline void zombify(T * const object) noexcept
            {
                deadPool.store( Destructed(object) );
            }

            inline T * recover() {
                Y_Inferno_Recover( T() );
            }


        private:
            Y_Disable_Copy_And_Assign(Inferno);
            DeadPool deadPool;

            inline ConstInterface & locus() const noexcept { return deadPool; }
        };
    }
}

#endif

