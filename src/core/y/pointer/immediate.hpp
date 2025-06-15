
//! \file

#ifndef Y_Pointer_Immediate_Included
#define Y_Pointer_Immediate_Included 1

#include "y/type/args.hpp"
#include <cassert>

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! Immediate access with operator->
    //
    //
    //__________________________________________________________________________
    template <class T> class Immediate
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_ARGS_EXPOSE(T,Type);               //!< aliases
        typedef Type *      ReturnType;      //!< alias
        typedef ConstType * ConstReturnType; //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________
        inline virtual ~Immediate() noexcept {} //!< cleanup
    protected:
        inline explicit Immediate() noexcept {} //!< setup

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! \return ptr \param ptr object address
        inline ReturnType      fetch(Type       * const ptr)       noexcept { assert(0!=ptr); return ptr; }

        //! \return const ptr \param ptr object address
        inline ConstReturnType fetch(const Type * const ptr) const noexcept { assert(0!=ptr); return ptr; }

    private:
        Y_Disable_Copy_And_Assign(Immediate); //!< discarding
    };

}

#endif

