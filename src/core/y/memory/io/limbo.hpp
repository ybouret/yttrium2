
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


        //______________________________________________________________________
        //
        //
        //
        //! wrapper for Zombies, for any type
        //
        //
        //______________________________________________________________________
        template <typename T, typename THREADING_POLICY = SingleThreadedClass>
        class Limbo :  public THREADING_POLICY, public Caching
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            Y_ARGS_DECL(T,Type);                          //!< aliases
            typedef typename THREADING_POLICY::Lock Lock; //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup with no argument
            inline explicit Limbo() : THREADING_POLICY(), zombies( sizeof(T) ) {}

            //! setup with argument for policy
            template <typename ARGS>
            inline explicit Limbo(ARGS &args) : THREADING_POLICY(args), zombies( sizeof(T) ) {}

            //! cleanup
            inline virtual ~Limbo() noexcept {}

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! create type with no argument \return live object
            inline Type *summon() {
                Y_Must_Lock();
                Y_Memory_Limbo( return new (addr) Type() );
            }

            //! create type with one argument \param u parameter \return live object
            template <typename U>
            inline Type * summon( typename TypeTraits<U>::ParamType u )
            {
                Y_Must_Lock();
                Y_Memory_Limbo( return new (addr) Type(u) );
            }

            //!  return to zombies \param object live object
            inline void banish(Type * const object) noexcept {
                Y_Must_Lock();
                assert(0!=object);
                zombies.store( Destructed( (MutableType *)object ) );
            }

            //! return to inner Memory::Guild \param object live object
            inline void remove(Type * const object) noexcept
            {
                Y_Must_Lock();
                assert(0!=object);
                zombies.purge( Destructed( (MutableType *)object ) );
            }


            //! duplicate \param object live object \return duplicate
            inline Type *mirror(ConstType &object)
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
            Zombies zombies; //!< inner zombies

        private:
            Y_Disable_Copy_And_Assign(Limbo); //!< discarding
        };
    }

}
#endif

