
//! \file

#ifndef Y_MKL_Optimize_Included
#define Y_MKL_Optimize_Included 1

#include "y/mkl/triplet.hpp"
#include "y/mkl/function-wrapper-1d.hpp"

namespace Yttrium
{
    namespace MKL
    {

        //! Optimize API
        template <typename T>
        struct Optimize
        {
            typedef Function<T,T> FunctionType; //!< alias

            //! run steps up to convergence
            /**
             \param x initial ordered positions
             \param f initial local minimum
             \param F function to minimize
             */
            static void Run(Triplet<T> &   x,
                            Triplet<T> &   f,
                            FunctionType & F);
        };

    }

}

#endif
