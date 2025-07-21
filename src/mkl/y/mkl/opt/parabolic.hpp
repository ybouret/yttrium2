//! \file

#ifndef Y_MKL_OptimizeParabolic_Included
#define Y_MKL_OptimizeParabolic_Included 1

#include "y/mkl/triplet.hpp"
#include "y/mkl/function-wrapper-1d.hpp"

namespace Yttrium
{
    namespace MKL
    {

        
        //! Optimize API
        template <typename T>
        struct ParabolicOptimization
        {
            typedef Function<T,T> FunctionType; //!< alias

            //! shrink position around local minimun
            /**
             \param x initial increasing positions
             \param f initial local minimum
             \param F function to minimize
             */
            static void Step(Triplet<T> &   x,
                             Triplet<T> &   f,
                             FunctionType & F);

            //! wrapper
            /**
             \param F any compatible function
             \param x initial increasing positions
             \param f initial local minimum
             */
            template <typename FUNCTION> static inline
            void Step(FUNCTION &F, Triplet<T> &x, Triplet<T> &f)
            {
                Wrapper1D<T,T,FUNCTION> FW(F);
                Step(x,f,FW);
            }
        };

    }
}

#endif
