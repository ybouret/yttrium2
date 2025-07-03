

//! \file

#ifndef Y_MKL_Fabs_Included
#define Y_MKL_Fabs_Included 1

#include "y/mkl/api/selector.hpp"
#include "y/mkl/api/scalar-for.hpp"
#include "y/calculus/iabs.hpp"
#include <cmath>

namespace Yttrium
{
    namespace MKL
    {
        
        namespace Kernel
        {
            template <typename T>
            inline T Fabs(const T x, const IntegralAPI &) noexcept
            {
                return IntegerAbs(x);
            }

            template <typename T>
            inline T Fabs(const T x, const FloatingAPI &) noexcept
            {
                return std::fabs(x);
            }

            template <typename T>
            inline typename ScalarFor<T>::Type  Fabs(const T &x, const MustCallAPI &) noexcept
            {
                return x.abs();
            }

        }

        //! wrapper to select fabs()
        template <typename T> struct Fabs
        {
            Y_Args_Declare(T,Type);                                   //!< aliases
            typedef typename ScalarFor<MutableType>::Type ScalarType; //!< alias

            //! \param x value \return |x|
            static inline ScalarType Of(ParamType x)
            {
                static const typename API_Select<T>::Choice choice = {};
                return Kernel::Fabs<T>(x,choice);
            }
        };

    }

}

#endif

