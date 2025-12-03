

//! \file

#ifndef Y_Calculus_Prime_Count_Included
#define Y_Calculus_Prime_Count_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Prime
    {
        //______________________________________________________________________
        //
        //
        //
        //! Prime Pi for powers of 10
        //
        //
        //______________________________________________________________________
        struct Count
        {
            static const size_t   For64Bits = 20;          //!< Pi(10^[0-20])
            static const uint64_t Leq10ToThe[For64Bits+1]; //!< Pi(10^n)
        };
    }

}

#endif // !Y_Calculus_Prime_Count_Included

