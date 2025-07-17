
//! \file


#ifndef Y_MKL_AlmostEqual_Included
#define Y_MKL_AlmostEqual_Included 1

#include "y/mkl/api/fabs.hpp"
#include "y/mkl/numeric.hpp"
#include "y/core/utils.hpp"

namespace Yttrium
{
    namespace MKL
    {

        namespace Kernel
        {
            template <typename T> inline
            bool ScalarAreAlmostEqual(const T &x,
                                      const T &y) noexcept
            {
                static const T & ftol  = Numeric<T>::EPSILON;
                static const T & ztol  = Numeric<T>::MIN;
                const T          vmin  = Min(MKL::Fabs<T>::Of(x),MKL::Fabs<T>::Of(y));
                const T          delta = x-y;

                if(vmin<=0.0) {
                    return MKL::Fabs<T>::Of(delta)<=ztol;
                }

                return (MKL::Fabs<T>::Of((delta)/Max(ztol,vmin)))<=ftol;
            }

        }



    }
}

#endif

