

//! \file

#ifndef Y_MKL_FPow_Included
#define Y_MKL_FPow_Included 1

#include "y/mkl/xreal.hpp"
#include <cmath>

namespace Yttrium
{
    namespace MKL
    {

        template <typename T> struct Fpow
        {
            static inline T Of(const T x, const T a)
            {
                return std::pow(x,a);
            }
        };

        template <typename T> struct Fpow< XReal<T> >
        {
            static inline XReal<T> Of(const XReal<T> &x, const T a)
            {
                return x.pow(a);
            }
        };

    }

}

#endif // !Y_MKL_FPow_Included

