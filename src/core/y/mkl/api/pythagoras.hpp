
//! \file

#ifndef Y_MKL_Pythagoras_Included
#define Y_MKL_Pythagoras_Included 1

#include "y/sorting/sort3.hpp"
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

        template <typename T> T Pythagoras(const T a, const T b, const T c)
        {
            T absv[3] = { Fabs<T>::Of(a), Fabs<T>::Of(b), Fabs<T>::Of(c) };
            Sorting::Sort3(absv);
            const T zero(0);
            if(absv[2]<=zero) return zero;
            const T arg0 = absv[0]/absv[2];
            const T arg1 = absv[1]/absv[2];
            const T sarg = (arg0*arg0+arg1*arg1) + T(1);
            return absv[2] * Sqrt<T>::Of(sarg);
        }


    }
}

#endif

