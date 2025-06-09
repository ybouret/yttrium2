//! \file

#ifndef Y_Memory_Inferno_Included
#define Y_Memory_Inferno_Included 1

#include "y/memory/management/purgatory.hpp"
#include "y/singleton.hpp"
#include "y/memory/management/dead-pool.hpp"
#include "y/type/args.hpp"
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
        template <typename T,System::AtExit::Longevity LIFE_TIME>
        class Inferno :
        public Singleton<Inferno<T,LIFE_TIME>,ClassLockPolicy>,
        public Purgatory<T>
        {
        public:
            typedef Singleton<Inferno<T,LIFE_TIME>,ClassLockPolicy> SingletonType;
            static const System::AtExit::Longevity LifeTime = LIFE_TIME;
            static const char * const              CallSing;
            using SingletonType::access;


            // interface
            inline virtual void zombify(T * const object) noexcept
            {
                Y_Lock(access);
                deadPool.store( Destructed(object) );
            }

            inline virtual T * reenact(const T &object)
            {
                Y_Lock(access);
                Y_Inferno_Recover( T(object) );
            }

            inline virtual T * recover() {
                Y_Inferno_Recover( T() );
            }

            // methods
            template <typename ARG1> inline
            T * recover(typename TypeTraits<ARG1>::ParamType arg1) {
                Y_Lock(access);
                Y_Inferno_Recover( T(arg1) );
            }


        private:
            Y_Disable_Copy_And_Assign(Inferno);
            // C++
            inline explicit Inferno() :
            SingletonType(),
            Purgatory<T>(),
            deadPool( sizeof(T) )
            {
            }

            inline virtual ~Inferno() noexcept {}

            DeadPool deadPool;

        };
    }
}

#endif

