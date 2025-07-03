
//! \file

#ifndef Y_MKL_Pythagoras_Included
#define Y_MKL_Pythagoras_Included 1

#include "y/mkl/api/fabs.hpp"
#include "y/mkl/api/sqrt.hpp"
#include "y/check/static.hpp"
#include <cassert>

namespace Yttrium
{
    namespace MKL
    {


        template <typename T> T Pythagoras(const T a, const T b)
        {
            Y_STATIC_CHECK(IsScalarType<T>::Value,BadType);
            const T absa = Fabs<T>::Of(a);
            const T absb = Fabs<T>::Of(b);
            const T one(1);
            
            if (absa > absb)
            {
                const T rho  = absb/absa;
                const T arg  = one + rho*rho;
                return absa*Sqrt<T>::Of(arg);
            }
            else
            {
                assert(absa<=absb);
                const T zero(0);
                if( absb <= zero )
                    return zero;
                else
                {
                    const T rho  = absa/absb;
                    const T arg  = one + rho*rho;
                    return absb*Sqrt<T>::Of(arg);
                }
            }
        }

    }
}

#endif

