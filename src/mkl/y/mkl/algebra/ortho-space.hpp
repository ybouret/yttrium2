
//! \file

#ifndef Y_MKL_OrthoSpace_Included
#define Y_MKL_OrthoSpace_Included 1

#include "y/container/matrix.hpp"
#include "y/apex/rational.hpp"

namespace Yttrium
{
    namespace MKL
    {

        //______________________________________________________________________
        //
        //
        //
        //! computing orthonal spaces
        //
        //
        //______________________________________________________________________
        struct OrthoSpace
        {
            //! compute row vectors of orthogonal space
            /**
             \param P source row vectors
             \return a matrix of orthogonal row vectors
             */
            static Matrix<apz> Compute(const Matrix<apz> &P);

            //! compute row vectors of orthogonal space
            /**
             \param P compatible matrix
             \return a matrix of orthogonal row vectors
             */
            template <typename T> static inline
            Matrix<apz> Of(const Matrix<T> &P)
            {
                const Matrix<apz> P_(CopyOf,P);
                return Compute(P_);
            }
        };
    }

}

#endif

