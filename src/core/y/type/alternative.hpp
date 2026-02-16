
//! \file

#ifndef Y_Type_Alternative_Included
#define Y_Type_Alternative_Included 1

#include "y/system/compiler.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //! default type alternative.
    //
    //__________________________________________________________________________
    template <
    const bool firstFlag,
    typename   First,
    const bool secondFlag,
    typename   Second,
    typename   Third> struct Alternative;

    //__________________________________________________________________________
    //
    //
    //! Alternative with first flag => First
    //
    //__________________________________________________________________________
    template <typename First, typename Second, typename Third>
    struct Alternative<true,First,true,Second,Third> {
        typedef First Type; //!< alias
    };

    //__________________________________________________________________________
    //
    //
    //! Alternative with first flag => First
    //
    //__________________________________________________________________________
    template <typename First, typename Second, typename Third>
    struct Alternative<true,First,false,Second,Third> {
        typedef First Type; //!< alias
    };


    //__________________________________________________________________________
    //
    //
    //! Alternative with second flag => Second
    //
    //__________________________________________________________________________
    template <typename First, typename Second, typename Third>
    struct Alternative<false,First,true,Second,Third> {
        typedef Second Type; //!< alias
    };

    //__________________________________________________________________________
    //
    //
    //! Alternative with no flag => Third
    //
    //__________________________________________________________________________
    template <typename First, typename Second, typename Third>
    struct Alternative<false,First,false,Second,Third> {
        typedef Third Type; //!< alias
    };


}

#endif // !Y_Type_Alternative_Included
