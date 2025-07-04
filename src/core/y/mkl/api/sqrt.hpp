
//! \file

#ifndef Y_MKL_Sqrt_Included
#define Y_MKL_Sqrt_Included 1

#include "y/mkl/api/selector.hpp"
#include "y/calculus/isqrt.hpp"
#include <cmath>

namespace Yttrium
{
    namespace MKL
    {

        namespace Kernel
        {
            //! \param x value \return integer x^(1/2)
            template <typename T> inline
            T Sqrt(const T x, const IntegralAPI &)
            {
                return IntegerSquareRoot(x);
            }

            //! \param x value \return   x^(1/2)
            template <typename T> inline
            T Sqrt(const T x, const FloatingAPI &)
            {
                return std::sqrt(x);
            }

            //! \param x value \return integer x.sqrt()
            template <typename T> inline
            T Sqrt(const T &x, const MustCallAPI &)
            {
                return x.sqrt();
            }



        }

        //! sqrt selector for types
        template <typename T> struct Sqrt
        {
            Y_Args_Declare(T,Type); //!< aliases

            //! \param x value \return |x|
            static inline Type Of(ParamType x)
            {
                static const typename API_Select<T>::Choice choice = {};
                return Kernel::Sqrt<T>(x,choice);
            }
        };


    }

}

#endif

