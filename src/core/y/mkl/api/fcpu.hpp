
//! \file

#ifndef Y_MKL_FCPU_Included
#define Y_MKL_FCPU_Included 1

#include "y/mkl/xreal.hpp"

namespace Yttrium
{
    namespace MKL
    {
        template <typename T>
        struct FCPU
        {
            typedef T Type;
        };

        template <typename T>
        struct FCPU< XReal<T> >
        {
            typedef T Type;
        };
    }

}

#endif // !Y_MKL_FCPU_Included

