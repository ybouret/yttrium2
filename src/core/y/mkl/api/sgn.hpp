
//! \file

#ifndef Y_MKL_SGN_INCLUDED
#define Y_MKL_SGN_INCLUDED 1

#include "y/mkl/api/fabs.hpp"

namespace Yttrium
{
    namespace MKL
    {

        //! return the signed value of a w.r.t the sign of b
        template <typename T, typename U> inline
        T Sgn(T a, U b) {
            return Sign::GEQZ(b) ? Fabs<T>::Of(a) : -Fabs<T>::Of(a);
        }



    }
}

#endif

