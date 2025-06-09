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
            inline explicit Inferno(size_t requested = 0) :
            deadPool( sizeof(T) ),
            blockSize( deadPool.blockSize() )
            {
                deadPool.cache(requested);
            }

            inline virtual ~Inferno() noexcept {}


            inline void zombify(T * const object) noexcept
            {
                deadPool.store( Destructed(object) );
            }

            inline T * reenact(const T &object)
            {
                Y_Inferno_Recover( T(object) );
            }

            inline T * recover() {
                Y_Inferno_Recover( T() );
            }

            template <typename ARG1> inline
            T * recover(typename TypeTraits<ARG1>::ParamType arg1) {
                Y_Inferno_Recover( T(arg1) );
            }


        private:
            Y_Disable_Copy_And_Assign(Inferno);
            inline ConstInterface & locus() const noexcept { return deadPool; }

            DeadPool deadPool;
        public:
            const size_t blockSize;
        };
    }
}

#endif

