
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

    









    namespace Memory
    {


#define Y_Memory_Netherworld(RETURN_CODE)     \
/**/    do {                                  \
/**/        void * const addr = zombies.query();      \
/**/        try { RETURN_CODE;              } \
/**/        catch(...) { zombies.store(addr); throw;} \
/**/    } while(false)


#define Y_Memory_Netherworld_Lock() volatile Lock guard(*this)

        template <typename T, typename THREADING_POLICY>
        class Netherworld :  public THREADING_POLICY, public Caching
        {
        public:
            Y_ARGS_DECL(T,Type);
            typedef typename THREADING_POLICY::Lock Lock;

            inline explicit Netherworld() : THREADING_POLICY(), zombies( sizeof(T) ) {}
            inline virtual ~Netherworld() noexcept {}

            inline Type *conjure() {
                Y_Memory_Netherworld_Lock();
                Y_Memory_Netherworld( return new (addr) Type() );
            }

            template <typename U>
            inline Type * conjure( typename TypeTraits<U>::ParamType u )
            {
                Y_Memory_Netherworld_Lock();
                Y_Memory_Netherworld( return new (addr) Type(u) );
            }

            inline void banish(Type * const object) noexcept {
                Y_Memory_Netherworld_Lock();
                assert(0!=object);
                zombies.store( Destructed( (MutableType *)object ) );
            }

            inline Type *recover(ConstType &object)
            {
                Y_Memory_Netherworld_Lock();
                Y_Memory_Netherworld( return new (addr) Type(object) );
            }

            inline virtual void gc(const uint8_t amount) noexcept
            {
                Y_Memory_Netherworld_Lock();
                zombies.gc(amount);
            }

            inline virtual size_t count() const noexcept
            {
                Y_Memory_Netherworld_Lock();
                return zombies.count();
            }

            inline virtual void cache(const size_t n)
            {
                Y_Memory_Netherworld_Lock();
                zombies.cache(n);
            }

            inline void print() const { zombies.print(); }


        private:
            Y_Disable_Copy_And_Assign(Netherworld);
            Zombies zombies;
        };
    }

}
#endif

