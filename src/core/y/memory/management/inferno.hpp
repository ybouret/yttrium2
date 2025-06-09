//! \file

#ifndef Y_Memory_Inferno_Included
#define Y_Memory_Inferno_Included 1

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

        //! Thread-Safe allocation
        template <typename T>
        class Inferno :
        public Singleton<Inferno<T>,ClassLockPolicy>
        {
        public:
            typedef Singleton<Inferno<T>,ClassLockPolicy> SingletonType;
            static const System::AtExit::Longevity LifeTime = T::LifeTime;
            static const char * const              CallSign;
            using SingletonType::access;


            // interface

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
            inline void zombify(T * const object) noexcept
            {
                Y_Lock(access);
                assert(0!=object);
                object->~T();
                deadPool.store( object );
            }

            inline T * recover() {
                Y_Inferno_Recover( new (addr) T() );
            }

            inline T * reenact(const T &object)
            {
                Y_Inferno_Recover( new (addr) T(object) );
            }

            template <typename ARG1>
            inline T *  produce(typename TypeTraits<ARG1>::ParamType arg1) {
                Y_Inferno_Recover( new (addr) T(arg1) );
            }

        private:
            Y_Disable_Copy_And_Assign(Inferno);
            friend SingletonType;

            // C++
            inline explicit Inferno() :
            SingletonType(),
            deadPool( sizeof(T) )
            {
            }

            inline virtual ~Inferno() noexcept {}

            DeadPool deadPool;
        };

        template <typename T>
        const char * const Inferno<T> :: CallSign = T::CallSign;


    }
}

#endif

