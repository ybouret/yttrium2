//! \file

#ifndef Y_MKL_OptimizeParabolic_Included
#define Y_MKL_OptimizeParabolic_Included 1

#include "y/mkl/triplet.hpp"
#include "y/mkl/function-wrapper-1d.hpp"

namespace Yttrium
{
    namespace MKL
    {

        extern bool ParabolicOptimizationVerbose;
        
        template <typename T>
        struct ParabolicOptimization
        {
            typedef Function<T,T> FunctionType;
            static void Step(Triplet<T> &   x,
                             Triplet<T> &   f,
                             FunctionType & F);

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
