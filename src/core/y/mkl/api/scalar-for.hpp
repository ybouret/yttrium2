
//! \file

#ifndef Y_MKL_ScalarFor_Included
#define Y_MKL_ScalarFor_Included 1

#include "y/mkl/complex.hpp"

namespace Yttrium
{
    namespace MKL
    {

        template <typename T> struct ScalarFor;

        template <typename T>
        struct ScalarFor< Complex<T> >
        {
            typedef T Type;
        };

        template <typename T>
        struct ScalarFor
        {
            typedef T Type;
        };

    }

}

#endif

