
//! \file

#ifndef Y_Memory_Limbo_Included
#define Y_Memory_Limbo_Included

#include "y/memory/io/zombies.hpp"
#include "y/threading/single-threaded-class.hpp"
#include "y/type/args.hpp"
#include "y/type/destruct.hpp"


namespace Yttrium
{

    namespace Memory
    {

        //! helper for object construction
#define Y_Memory_Limbo(RETURN_CODE)     \
/**/    do {                                  \
/**/        void * const addr = zombies.query();      \
/**/        try { RETURN_CODE;              } \
/**/        catch(...) { zombies.store(addr); throw;} \
/**/    } while(false)



        template <typename T, typename THREADING_POLICY = SingleThreadedClass>
        class Limbo :  public THREADING_POLICY, public Caching
        {
        public:
            Y_ARGS_DECL(T,Type);
            typedef typename THREADING_POLICY::Lock Lock;

            inline explicit Limbo() : THREADING_POLICY(), zombies( sizeof(T) ) {}

            template <typename ARGS>
            inline explicit Limbo(ARGS &args) : THREADING_POLICY(args), zombies( sizeof(T) ) {}

            inline virtual ~Limbo() noexcept {}

            inline Type *conjure() {
                Y_Must_Lock();
                Y_Memory_Limbo( return new (addr) Type() );
            }

            template <typename U>
            inline Type * conjure( typename TypeTraits<U>::ParamType u )
            {
                Y_Must_Lock();
                Y_Memory_Limbo( return new (addr) Type(u) );
            }

            inline void banish(Type * const object) noexcept {
                Y_Must_Lock();
                assert(0!=object);
                zombies.store( Destructed( (MutableType *)object ) );
            }
            
            inline void remove(Type * const object) noexcept
            {
                Y_Must_Lock();
                assert(0!=object);
                zombies.purge( Destructed( (MutableType *)object ) );
            }




            inline Type *recover(ConstType &object)
            {
                Y_Must_Lock();
                Y_Memory_Limbo( return new (addr) Type(object) );
            }

            inline virtual void gc(const uint8_t amount) noexcept
            {
                Y_Must_Lock();
                zombies.gc(amount);
            }

            inline virtual size_t count() const noexcept
            {
                Y_Must_Lock();
                return zombies.count();
            }

            inline virtual void cache(const size_t n)
            {
                Y_Must_Lock();
                zombies.cache(n);
            }

        protected:
            Zombies zombies;
            
        private:
            Y_Disable_Copy_And_Assign(Limbo);
        };
    }

}
#endif

