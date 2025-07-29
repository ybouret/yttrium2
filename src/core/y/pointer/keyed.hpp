//! \file

#ifndef Y_Pointer_Keyed_Included
#define Y_Pointer_Keyed_Included 1

#include "y/type/args.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! convert smart pointer into keyed-pointed
    //
    //
    //__________________________________________________________________________
    template<typename KEY, class PTR>
    class Keyed : public PTR
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Expose(KEY,Key);          //!< aliases
        typedef typename PTR::Type Type; //!< alias

        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________

        inline Keyed(Type * const obj) : PTR(obj) {} //!< assign \param obj for underlying pointer
        inline Keyed(const Keyed &ptr) : PTR(ptr) {} //!< copy   \param ptr another pointer

        //! assign \param ptr another pointer \return *this
        inline Keyed & operator=(const Keyed &ptr)
        {
            PTR &       lhs = *this;
            const PTR & rhs = ptr;
            lhs = rhs;
            return *this;
        }

        //! cleanup
        inline virtual ~Keyed() noexcept {}

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! \return forward call to pointee
        inline ConstKey & key() const noexcept { return (**this).key(); }

    };

}

#endif

