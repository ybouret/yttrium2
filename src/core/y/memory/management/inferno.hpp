//! \file

#ifndef Y_Memory_Inferno_Included
#define Y_Memory_Inferno_Included 1

#include "y/memory/management/purgatory.hpp"
#include "y/singleton.hpp"
#include "y/memory/management/dead-pool.hpp"
#include "y/type/args.hpp"
#include "y/xml/attribute.hpp"

namespace Yttrium
{
    namespace Memory
    {

#define Y_Inferno_Recover(NEW_AT_ADDR) do { \
/**/  Y_Lock(access);\
/**/  void * const addr = deadPool.query();\
/**/    try {\
/**/      return NEW_AT_ADDR;\
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
            static const char * const              CallSign;
            using SingletonType::access;


            // interface
            inline virtual void zombify(T * const object) noexcept
            {
                Y_Lock(access);
                assert(0!=object);
                object->~T();
                deadPool.store( object );
            }

            inline virtual T * reenact(const T &object)
            {
                Y_Inferno_Recover( new (addr) T(object) );
            }

            inline virtual T * recover() {
                Y_Inferno_Recover( new (addr) T() );
            }

            virtual void display(std::ostream &os, const size_t indent) const
            {
                Y_Lock( Coerce(access) );
                this->initProlog(os,indent) << XML::Attribute("in_cache", deadPool.count());
                this->initEpilog(os,true);
            }

            virtual void gc(const uint8_t amount) noexcept
            {
                Y_Lock(access);
                deadPool.gc(amount);
            }

            virtual void cache(const size_t n)
            {
                Y_Lock(access);
                deadPool.cache(n);
            }

            virtual size_t count() const noexcept
            {
                Y_Lock( Coerce(access) );
                return deadPool.count();
            }


            // methods
            template <typename ARG1> inline
            T *  rebuild(typename TypeTraits<ARG1>::ParamType arg1) {
                Y_Inferno_Recover( new (addr) T(arg1) );
            }


        private:
            Y_Disable_Copy_And_Assign(Inferno);
            friend SingletonType;

            // C++
            inline explicit Inferno() :
            SingletonType(),
            Purgatory<T>(),
            deadPool( sizeof(T) )
            {
            }

            inline virtual ~Inferno() noexcept {}


            inline virtual T * produce( T * (*proc)(void *, void *), void * args)
            {
                assert(0!=proc);
                Y_Inferno_Recover( proc(addr,args) );
            }

            DeadPool deadPool;

        };
    }
}

#endif

