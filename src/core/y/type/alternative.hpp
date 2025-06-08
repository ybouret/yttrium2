
//! \file

#ifndef Y_Type_Alternative_Included
#define Y_Type_Alternative_Included 1

#include "y/system/compiler.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //! default type alternative.
    //__________________________________________________________________________
    template <
    const bool firstFlag,
    typename   First,
    const bool secondFlag,
    typename   Second,
    typename   Third> struct Alternative;

    template <typename First, typename Second, typename Third>
    struct Alternative<true,First,true,Second,Third> {
        typedef First Type;
    };

    template <typename First, typename Second, typename Third>
    struct Alternative<true,First,false,Second,Third> {
        typedef First Type;
    };


    template <typename First, typename Second, typename Third>
    struct Alternative<false,First,true,Second,Third> {
        typedef Second Type;
    };

    template <typename First, typename Second, typename Third>
    struct Alternative<false,First,false,Second,Third> {
        typedef Third Type;
    };


}

#endif
