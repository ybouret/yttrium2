
//! \file

#ifndef Y_MKL_Rank_Included
#define Y_MKL_Rank_Included 1

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
        //! Computing ranks of matrices
        //
        //
        //______________________________________________________________________
        struct Rank
        {
            //! compute rank of matrix
            /**
             \param Q rational matrix, destroyed
             \return rank(Q)
             */
            static size_t Compute(Matrix<apq> &Q);

            //! copy compatible matrix and compute its rank
            /**
             \param M matrix<int|apn|apz|apq>
             \return rank(M)
             */
            template <typename T> static inline
            size_t Of(const Matrix<T> &M)
            {
                Matrix<apq> Q(CopyOf,M);
                return Compute(Q);
            }


        };

    }

}

#endif
