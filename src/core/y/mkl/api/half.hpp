


//! \file

#ifndef Y_MKL_Half_Included
#define Y_MKL_Half_Included 1

#include "y/mkl/api/selector.hpp"

namespace Yttrium
{
    namespace MKL
    {

        namespace Kernel
        {
            //! \param x value \return integer |x|
            template <typename T>
            inline T Half(const T x, const IntegralAPI &) noexcept
            {
                return x/2;
            }

            //! \param x value \return 0.5*x
            template <typename T>
            inline T Half(const T x, const FloatingAPI &) noexcept
            {
                static const T half = (T)(0.5);
                return x*half;
            }

            //! \param x value \return x.shr
            template <typename T>
            inline T  Half(const T &x, const MustCallAPI &) noexcept
            {
                T res(x);
                res.shr();
                return res;
            }

        }

        //! wrapper to select fabs()
        template <typename T> struct Half
        {
            Y_Args_Declare(T,Type);                                   //!< aliases

            //! \param x value \return x/2
            static inline Type Of(ParamType x)
            {
                static const typename API_Select<T>::Choice choice = {};
                return Kernel::Half<T>(x,choice);
            }

            //! \param x value \param y value \return (x+y)/2
            static inline Type Of(ParamType x, ParamType y)
            {
                static const typename API_Select<T>::Choice choice = {};
                ConstType sum = x+y;
                return Kernel::Half<T>(sum,choice);
            }
        };

    }

}

#endif

