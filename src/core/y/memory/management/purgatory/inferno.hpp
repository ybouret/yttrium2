//! \file

#ifndef Y_Memory_Inferno_Included
#define Y_Memory_Inferno_Included 1


#include "y/memory/management/purgatory.hpp"
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

        //!
        template <typename T>
        class Inferno : public Purgatory<T>, public Ingress<Caching>
        {
        public:
            // C++
            inline explicit Inferno() :
            deadPool( sizeof(T) )
            {
            }

            inline virtual ~Inferno() noexcept {}


            // interface
            inline virtual void zombify(T * const object) noexcept
            {
                deadPool.store( Destructed(object) );
            }

            inline virtual T * reenact(const T &object)
            {
                Y_Inferno_Recover( T(object) );
            }

            inline virtual T * recover() {
                Y_Inferno_Recover( T() );
            }

            // methods
            template <typename ARG1> inline
            T * recover(typename TypeTraits<ARG1>::ParamType arg1) {
                Y_Inferno_Recover( T(arg1) );
            }


        private:
            Y_Disable_Copy_And_Assign(Inferno);
            inline ConstInterface & locus() const noexcept { return deadPool; }
            DeadPool deadPool;

        };
    }
}

#endif

