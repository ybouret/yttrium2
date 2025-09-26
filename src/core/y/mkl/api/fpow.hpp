//! \file

#ifndef Y_MKL_FPow_Included
#define Y_MKL_FPow_Included 1

#include "y/mkl/xreal.hpp"
#include <cmath>

namespace Yttrium
{
    namespace MKL
    {
        //! power for floating point/floating point
        template <typename T> struct Fpow
        {
            //! \param x x \param a a \return x^a
            static inline T Of(const T x, const T a)
            {
                return std::pow(x,a);
            }
        };

        //! power for xfloating point/floating point
        template <typename T> struct Fpow< XReal<T> >
        {
            //! \param x x \param a a \return x^a
            static inline XReal<T> Of(const XReal<T> &x, const T a)
            {
                return x.pow(a);
            }
        };

    }

}

#endif // !Y_MKL_FPow_Included

