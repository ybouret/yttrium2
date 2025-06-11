
//! \file

#ifndef Y_Memory_Netherworld_Included
#define Y_Memory_Netherworld_Included

#include "y/memory/io/zombies.hpp"
#include "y/type/args.hpp"
#include "y/type/destruct.hpp"

#include "y/concurrent/mutex.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{

    

    namespace Concurrent
    {
        template <typename CLASS>
        class Locker
        {
        public:
            inline  Locker(const CLASS &obj) noexcept : host(Coerce(obj)) { obj.access->lock(); }
            inline ~Locker() noexcept { host.access->unlock(); }
        private:
            CLASS & host;
        };
    };

    

    class MultiThreadedObject
    {
    public:
        typedef Concurrent::Locker<MultiThreadedObject> Lock;

        explicit MultiThreadedObject() : access( new Concurrent::Mutex() ) {}
        virtual ~MultiThreadedObject() noexcept { Destroy(access); }

    private:
        Y_Disable_Copy_And_Assign(MultiThreadedObject);
        friend Lock;
        Lockable * const access;
    };





    template <typename SINGLETON>
    class MultiThreadedHandle
    {
    public:
        typedef Concurrent::Locker<MultiThreadedHandle> Lock;

        inline explicit MultiThreadedHandle() : access( & SINGLETON::Instance().access ) {}
        inline virtual ~MultiThreadedHandle() noexcept { Coerce(access) = 0; }
    private:
        Y_Disable_Copy_And_Assign(MultiThreadedHandle);
        friend Lock;
        Lockable * const access;
    };


    namespace Memory
    {


#define Y_Memory_Netherworld(RETURN_CODE)     \
/**/    do {                                  \
/**/        void * const addr = query();      \
/**/        try { RETURN_CODE;              } \
/**/        catch(...) { store(addr); throw;} \
/**/    } while(false)

        

        template <typename T, typename THREADING_POLICY>
        class Netherworld : public Zombies, public THREADING_POLICY
        {
        public:
            Y_ARGS_DECL(T,Type);
            typedef typename THREADING_POLICY::Lock Lock;

            inline explicit Netherworld() : Zombies( sizeof(T) ) {}
            inline virtual ~Netherworld() noexcept {}

            inline Type *conjure() {
                volatile Lock guard(*this);
                Y_Memory_Netherworld( return new (addr) Type() );
            }

            template <typename U>
            inline Type * conjure( typename TypeTraits<U>::ParamType u )
            {
                Y_Memory_Netherworld( return new (addr) Type(u) );
            }

            inline void banish(Type * const object) noexcept {
                assert(0!=object);
                store( Destructed( (MutableType *)object ) );
            }

            inline Type *recover(ConstType &object)
            {
                Y_Memory_Netherworld( return new (addr) Type(object) );
            }


        private:
            Y_Disable_Copy_And_Assign(Netherworld);
        };
    }

}
#endif

