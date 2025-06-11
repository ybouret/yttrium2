
//! \file

#ifndef Y_Memory_Netherworld_Included
#define Y_Memory_Netherworld_Included

#include "y/memory/io/zombies.hpp"
#include "y/type/args.hpp"
#include "y/type/destruct.hpp"

namespace Yttrium
{
    namespace Memory
    {
#define Y_Memory_Netherworld(RETURN_CODE)     \
/**/    do {                                  \
/**/        void * const addr = query();      \
/**/        try { RETURN_CODE;              } \
/**/        catch(...) { store(addr); throw;} \
/**/    } while(false)

        template <typename T>
        class Netherworld : public Zombies
        {
        public:
            Y_ARGS_DECL(T,Type);

            inline explicit Netherworld() : Zombies( sizeof(T) ) {}
            inline virtual ~Netherworld() noexcept {}

            inline Type *conjure() {
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

