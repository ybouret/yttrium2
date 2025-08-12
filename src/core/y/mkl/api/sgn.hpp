
//! \file

#ifndef Y_MKL_SGN_INCLUDED
#define Y_MKL_SGN_INCLUDED 1

#include "y/mkl/api/fabs.hpp"

namespace Yttrium
{
    namespace MKL
    {

        //! signed return
        /**
         \param a value to return
         \param b sign to return
         \return return sign(b) * |a|
         */
        template <typename T, typename U> inline
        T Sgn(T a, U b) {
            return Sign::GEQZ(b) ? Fabs<T>::Of(a) : -Fabs<T>::Of(a);
        }



    }
}

#endif

