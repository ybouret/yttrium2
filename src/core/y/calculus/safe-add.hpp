
//! \file

#ifndef Y_Calculus_SafeAdd_Included
#define Y_Calculus_SafeAdd_Included 1

#include "y/system/compiler.hpp"

namespace Yttrium
{

    namespace Calculus
    {
        //! safe add of two arguments
        /**
         \param lhs first
         \param rhs second
         \return sum iff no overflow
         */
        size_t SafeAdd(const size_t lhs, const size_t rhs);
    }


}

#endif

