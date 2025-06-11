//! \file

#ifndef Y_Concurrent_Inferno_Included
#define Y_Concurrent_Inferno_Included 1

#include "y/singleton.hpp"
#include "y/concurrent/data/dead-pool.hpp"
#include "y/type/args.hpp"
#include "y/xml/attribute.hpp"
#include "y/memory/page.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        typedef Memory::Page Wraith;

        //______________________________________________________________________
        //
        //
        //! two-sage build helper
        //
        //______________________________________________________________________
#define Y_Inferno_Recover(NEW_AT_ADDR) do { \
/**/  Y_Lock(access);                       \
/**/  void * const addr = deadPool.query(); \
/**/    try {                               \
/**/      return NEW_AT_ADDR;               \
/**/    }                                   \
/**/    catch(...)                          \
/**/    {                                   \
/**/      deadPool.store(addr);             \
/**/      throw;                            \
/**/  }                                     \
} while(false)



        //______________________________________________________________________
        //
        //
        //
        //! Top-Down Thread-Safe allocation of given type with cache
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Inferno :
        public Singleton<Inferno<T>,ClassLockPolicy>,
        public Caching
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef Singleton<Inferno<T>,ClassLockPolicy> SingletonType;   //!< alias
            static const System::AtExit::Longevity LifeTime = T::LifeTime; //!< alias
            static const char * const              CallSign;               //!< T::CallSing
            using SingletonType::access;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void display(std::ostream &os, size_t indent) const
            {
                Y_Lock( Coerce(access) );
                this->initProlog(os,indent) << XML::Attribute("in_cache", deadPool.count());
                this->initEpilog(os,true);
            }

            //! [Collectable] discard data \param amount amount of stored zombis
            virtual void gc(const uint8_t amount) noexcept
            {
                Y_Lock(access);
                deadPool.gc(amount);
            }

            //! [Caching] prefetch zombis \param n number of zombis to conjure
            virtual void cache(const size_t n)
            {
                Y_Lock(access);
                deadPool.cache(n);
            }

            //! [Caching] \return immediatly available zombis
            virtual size_t count() const noexcept
            {
                Y_Lock( Coerce(access) );
                return deadPool.count();
            }


            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            inline Wraith * conjure()
            {
                Y_Lock(access);
                return Wraith::Cast(deadPool.query());
            }

            inline void banish(Wraith * const wraith) noexcept
            {
                Y_Lock(access);
                deadPool.store( wraith );
            }



            //! zombify a live object \param object constructed object
            inline void zombify(T * const object) noexcept
            {
                Y_Lock(access);
                assert(0!=object);
                object->~T();
                deadPool.store( object );
            }

            //! \return a new object with default constructor
            inline T * recover() {
                Y_Inferno_Recover( new (addr) T() );
            }

            //! \param object source \return new T(object)
            inline T * reenact(const T &object)
            {
                Y_Inferno_Recover( new (addr) T(object) );
            }

            //! \param arg1 argument \return new T(arg1)
            template <typename ARG1>
            inline T *  produce(typename TypeTraits<ARG1>::ParamType arg1) {
                Y_Inferno_Recover( new (addr) T(arg1) );
            }

        private:
            Y_Disable_Copy_And_Assign(Inferno); //!< dicarding
            friend SingletonType;               //!< frienship

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup
            inline explicit Inferno() :
            SingletonType(),
            deadPool( sizeof(T) )
            {
            }

            //! cleanup
            inline virtual ~Inferno() noexcept {}

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            Concurrent::DeadPool deadPool; //!< private zombis
        };

        template <typename T>
        const char* const Inferno<T> ::CallSign = T::CallSign;


    }
}

#endif

