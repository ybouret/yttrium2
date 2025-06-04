// !\file

#ifndef Y_Type_Moniker_Included
#define Y_Type_Moniker_Included 1

#include "y/type/args.hpp"
#include "y/calculus/alignment.hpp"
#include "y/memory/stealth.hpp"
#include "y/type/copy-of.hpp"
#include "y/type/destruct.hpp"

namespace Yttrium
{

    template <typename T>
    class Moniker
    {
    public:
        Y_ARGS_DECL(T,Type);

        inline Moniker() :
        wksp(), data( new ( Y_Memory_BZero(wksp) ) MutableType() )
        {
        }

        inline ~Moniker() noexcept
        {
            Memory::Stealth::Zero( Destructed(data), sizeof(wksp) );
        }

        inline Moniker(ParamType arg) :
        wksp(), data( new ( Y_Memory_BZero(wksp) ) MutableType(arg) )
        {
        }

        inline Moniker(const Moniker &other) :
        wksp(),
        data( new ( Y_Memory_BZero(wksp) ) MutableType(*other) )
        {
        }

        template <typename ARG>
        inline Moniker(const CopyOf_ &, ARG &arg) :
        wksp(),
        data( new ( Y_Memory_BZero(wksp) ) MutableType(arg) )
        {
        }

        inline friend
        std::ostream & operator<<(std::ostream &os, const Moniker &self)
        {
            return os << *self;
        }


        inline ConstType & operator*() const noexcept { assert(0!=data); return *data; }
        inline Type      & operator*()       noexcept { assert(0!=data); return *data; }



    private:
        Y_Disable_Assign(Moniker);
        void *              wksp[ Alignment::WordsFor<Type>::Count ];
        MutableType * const data;

    };

}

#endif

